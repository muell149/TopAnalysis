#include "TLorentzVector.h"
#include "TopAnalysis/TopAnalyzer/plugins/QCDBgEstimator.h"

/// default constructor
QCDBgEstimator::QCDBgEstimator(const edm::ParameterSet& cfg):
  muons_      ( cfg.getParameter<edm::InputTag>        ( "muons"          ) ), 
  useEvtWgt_  ( cfg.getParameter<bool>                 ( "useEventWeight" ) ),
  isoBins_    ( cfg.getParameter<std::vector<double> > ( "isoBins"        ) )
   
{
}

/// default destructor
QCDBgEstimator::~QCDBgEstimator()
{
}

/// everything which has to be done before the event loop: book fileservice and histograms
void
QCDBgEstimator::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }
  
  for(size_t i=0; i<isoBins_.size()-1; ++i){ 
    TH1F* hist;
    TString strRC = "dimassRC_";
    strRC += i;
    TString strWC = "dimassWC_"; 
    strWC += i; 
    hist = fs->make<TH1F>(strRC, strRC, 150, 0, 300);
    dimassRCIsoBins_.push_back(hist);  
    hist = fs->make<TH1F>(strWC, strWC, 150, 0, 300);
    dimassWCIsoBins_.push_back(hist);        
  }  
  
  // histogram for the normalization factors
  norm_ = fs->make<TH1F>( "norm", "Normalization Factor" ,isoBins_.size()-1, isoBins_[0], isoBins_[isoBins_.size()-1]);
}

/// everything which has to be done during the event loop: analyze and fill histos
void
QCDBgEstimator::analyze(const edm::Event& evt, const edm::EventSetup&)
{
  // get handle on muon collection
  edm::Handle<PatMuonCollection> muons; 
  evt.getByLabel(muons_, muons); 
   
  // get weight when indicated, else weight is 1               
  double weight = 1.;
  if(useEvtWgt_){ 
    edm::Handle<double> weightHandle; 
    evt.getByLabel("eventWeight", weightHandle); 
    weight = *weightHandle;
  }
  // test if muon collection contains at least two muons
  if(muons->size()<2) return;
  
  // get leading muons      
  PatMuonCollection::const_reference mu1 = muons->at(0);
  PatMuonCollection::const_reference mu2 = muons->at(1);     
  
  // calculate dimass    
  TLorentzVector diLepLVector = TLorentzVector(mu1.px()+mu2.px(), mu1.py()+mu2.py(), 
                                               mu1.pz()+mu2.pz(), mu1.energy()+mu2.energy());   
  double dilepMass = (diLepLVector).M();
     
  // wrong or right charge?
  isWrongCharge = false;
  if(mu1.charge()*mu2.charge()>0.) isWrongCharge = true;
        
  double combIso1 = (mu1.trackIso()+mu1.caloIso())/mu1.pt();
  double combIso2 = (mu2.trackIso()+mu2.caloIso())/mu2.pt();     
  
  double worseIso = std::max(combIso1,combIso2);
  

  
  // fill dilepmass histograms in bins of diCombIso
  for(size_t i=0; i<isoBins_.size()-1; ++i){  
    if(worseIso>isoBins_[i] && worseIso<isoBins_[i+1]){
      if(!isWrongCharge) 
        dimassRCIsoBins_[i] ->Fill(dilepMass, weight);
      else
        dimassWCIsoBins_[i] ->Fill(dilepMass, weight);	
    }  
  }    
}

/// everything which has to be done during the event loop: analyze and fill histos: empty
void
QCDBgEstimator::endJob()
{
  // fill norm factor histogram
  for(size_t i=0; i<isoBins_.size()-1; ++i){
    if(dimassWCIsoBins_[i]->GetEntries()>0)
      norm_->SetBinContent(i+1,dimassRCIsoBins_[i]->GetEntries()/dimassWCIsoBins_[i]->GetEntries());
  }  
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( QCDBgEstimator );
