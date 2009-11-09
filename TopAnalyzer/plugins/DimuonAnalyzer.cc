#include "TLorentzVector.h"
#include "TopAnalysis/TopAnalyzer/plugins/DimuonAnalyzer.h"

/// default constructor
DimuonAnalyzer::DimuonAnalyzer(const edm::ParameterSet& cfg):
  muons_      ( cfg.getParameter<edm::InputTag>        ( "muons"          ) ), 
  useEvtWgt_  ( cfg.getParameter<bool>                 ( "useEventWeight" ) ),
  isoBins_    ( cfg.getParameter<std::vector<double> > ( "isoBins"        ) )
   
{
}

/// default destructor
DimuonAnalyzer::~DimuonAnalyzer()
{
}

/// everything which has to be done before the event loop: book fileservice and histograms
void
DimuonAnalyzer::beginJob(const edm::EventSetup&)
{
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }

  // define logarithmic bins for a histogram with 50 bins going from 10^0 to 10^2.4 =~ 250
  const int nbins = 50;
  double logmin =  0.0;
  double logmax =  2.4;
  double bins[nbins+1];
  for (int i = 0; i <= nbins; i++) {
    double log = logmin + (logmax-logmin)*i/nbins;
    bins[i] = std::pow(10.0, log);
  }
  /**
     histogram definitions
  **/ 
  // invariant muon muon mass for right charge  
  dimassRC_    = fs->make<TH1F>( "dimassRC", "dimassRC", nbins, bins);
  // invariant muon muon mass for wrong charge   
  dimassWC_    = fs->make<TH1F>( "dimassWC", "dimassWC", nbins, bins);
  // correlation between invariant mass and absolute combined isolation        
  isoDimassCorrelation_ = fs->make<TH2F>( "isoDimassCorrelation", "isoDimassCorrelation", 10,   0.,   200., 10, 0., 1.);
  
  // absolute isolation efficiency
  absCount_    = fs->make<TH1F>( "absCount"   , "absCount"    ,100,  0.,  50.0); 
  // relative isolation efficiency       
  relCount_    = fs->make<TH1F>( "relCount"   , "relCount"    ,100,  0.,   5.0); 
  // combined isolation efficiency
  combCount_   = fs->make<TH1F>( "combCount"  , "combCount"   ,100,  0.0,  1.0); 
  // quadratically added combined isolation
  diCombCount_ = fs->make<TH1F>( "diCombCount", "diCombCount" ,100,  0.0,  2.0);
  
  for(size_t i=0; i<isoBins_.size()-1; ++i){ 
    TH1F* hist;
    TString strRC = "dimassRC_";
    strRC += i;
    TString strWC = "dimassWC_"; 
    strWC += i; 
    hist = fs->make<TH1F>(strRC, strRC, 20, 5, 255);
    dimassRCIsoBins_.push_back(hist);  
    hist = fs->make<TH1F>(strWC, strWC, 20, 5, 255);
    dimassWCIsoBins_.push_back(hist);        
  }  
}

/// everything which has to be done during the event loop: analyze and fill histos
void
DimuonAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup&)
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
     
       
  // fill dimuon mass histograms:
  //right charge
  if(!isWrongCharge)  
    dimassRC_  ->Fill( dilepMass, weight);    
  // wrong charge
  else 
    dimassWC_  ->Fill( dilepMass, weight);    
     
  // get different isos  
  double absTrackIso1 = mu1.trackIso();
  double absTrackIso2 = mu2.trackIso();
  
  double absCaloIso1 = mu1.caloIso();
  double absCaloIso2 = mu2.caloIso();  
  
  double relTrackIso1 = mu1.trackIso()/mu1.pt();
  double relTrackIso2 = mu2.trackIso()/mu2.pt();
  
  double relCaloIso1 = mu1.caloIso()/mu1.pt();
  double relCaloIso2 = mu2.caloIso()/mu2.pt();  
  
  double combIso1 = mu1.pt()/(mu1.pt()+mu1.trackIso()+mu1.caloIso());
  double combIso2 = mu2.pt()/(mu2.pt()+mu2.trackIso()+mu2.caloIso());     
  
  double diCombIso = sqrt(combIso1*combIso1+combIso2*combIso2);
  
  // fill dimass-isolation correlation hist  
  isoDimassCorrelation_->Fill( dilepMass, combIso1, weight);  
  isoDimassCorrelation_->Fill( dilepMass, combIso2, weight);
  
  // fill isolation efficiency hists    
  for(int i=1;i<=100;++i){
    if(diCombIso>0.02*i){
      diCombCount_->SetBinContent(i,diCombCount_->GetBinContent(i)+1);
    }
    if(combIso1>0.01*i && combIso2>0.01*i){
      combCount_->SetBinContent(i,combCount_->GetBinContent(i)+1);
    }
    if(relTrackIso1<(0.05*i) && relCaloIso1<(0.05*i) && relTrackIso2<(0.05*i) && relCaloIso2<(0.05*i)){
      relCount_->SetBinContent(i,relCount_->GetBinContent(i)+1);
    }
    if(absTrackIso1<(0.5*i) && absCaloIso1<(0.5*i) && absTrackIso2<(0.5*i) && absCaloIso2<(0.5*i)){
      absCount_->SetBinContent(i,absCount_->GetBinContent(i)+1);
    }      
  }
  
  // fill dilepmass histograms in bins of diCombIso
  for(size_t i=0; i<isoBins_.size()-1; ++i){  
    if(diCombIso>isoBins_[i] && diCombIso<isoBins_[i+1]){
      if(!isWrongCharge) 
        dimassRCIsoBins_[i] ->Fill(dilepMass, weight);
      else
        dimassWCIsoBins_[i] ->Fill(dilepMass, weight);	
    }  
  }    
}

/// everything which has to be done during the event loop: analyze and fill histos: empty
void
DimuonAnalyzer::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( DimuonAnalyzer );
