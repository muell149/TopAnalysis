#include "TLorentzVector.h"
#include "TopAnalysis/TopAnalyzer/plugins/QCDBgEstimator.h"

/// default constructor
QCDBgEstimator::QCDBgEstimator(const edm::ParameterSet& cfg):
  muons_      ( cfg.getParameter<edm::InputTag>        ( "muons"          ) ), 
  isoBins_    ( cfg.getParameter<std::vector<double> > ( "isoBins"        ) ),
  massBins_   ( cfg.getParameter<std::vector<double> > ( "massBins"       ) )   
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
    TH1D* hist;
    TString strRC = "dimassRC_";
    strRC += i;
    TString strWC = "dimassWC_"; 
    strWC += i; 
    hist = fs->make<TH1D>(strRC, strRC, 300, 0, 300);
    dimassRCIsoBinsLowMass_.push_back(hist); 
    hist = fs->make<TH1D>(strRC, strRC, 300, 0, 300);
    dimassRCIsoBinsPeakMass_.push_back(hist);      
    hist = fs->make<TH1D>(strRC, strRC, 300, 0, 300);
    dimassRCIsoBinsHighMass_.push_back(hist);     
    
    hist = fs->make<TH1D>(strWC, strWC, 300, 0, 300);
    dimassWCIsoBinsLowMass_.push_back(hist); 
    hist = fs->make<TH1D>(strWC, strWC, 300, 0, 300);
    dimassWCIsoBinsPeakMass_.push_back(hist);    
    hist = fs->make<TH1D>(strWC, strWC, 300, 0, 300);
    dimassWCIsoBinsHighMass_.push_back(hist);               
  }  
}

/// everything which has to be done during the event loop: analyze and fill histos
void
QCDBgEstimator::analyze(const edm::Event& evt, const edm::EventSetup&)
{
  // get handle on muon collection
  edm::Handle<PatMuonCollection> muons; 
  evt.getByLabel(muons_, muons); 
   
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
        
  double combIso1 = (mu1.trackIso()+mu1.caloIso())/std::max(mu1.pt(),20.);
  double combIso2 = (mu2.trackIso()+mu2.caloIso())/std::max(mu2.pt(),20.);     
  
  double worseIso = std::max(combIso1,combIso2);
  

  
  // fill dilepmass histograms in bins of diCombIso
  for(size_t i=0; i<isoBins_.size()-1; ++i){  
    if(worseIso>isoBins_[i] && worseIso<isoBins_[i+1]){ // check for iso bin
      if(dilepMass<massBins_[0]) continue;
      else if(dilepMass<massBins_[1]){
        if(!isWrongCharge) 
          dimassRCIsoBinsLowMass_[i] ->Fill(dilepMass);
        else
          dimassWCIsoBinsLowMass_[i] ->Fill(dilepMass);      
      }
      else if(dilepMass<massBins_[2]){
        if(!isWrongCharge) 
          dimassRCIsoBinsPeakMass_[i] ->Fill(dilepMass);
        else
          dimassWCIsoBinsPeakMass_[i] ->Fill(dilepMass);        
      } 
      else{
        if(!isWrongCharge) 
          dimassRCIsoBinsHighMass_[i] ->Fill(dilepMass);
        else
          dimassWCIsoBinsHighMass_[i] ->Fill(dilepMass);       
      }
    }  
  }    
}

/// everything which has to be done during the event loop: analyze and fill histos: empty
void
QCDBgEstimator::endJob()
{
  
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( QCDBgEstimator );
