#include "TLorentzVector.h"
#include "TopAnalysis/TopAnalyzer/plugins/DimuonAnalyzer.h"
#include "DataFormats/Math/interface/deltaR.h"

/// default constructor
DimuonAnalyzer::DimuonAnalyzer(const edm::ParameterSet& cfg):
  muons_        ( cfg.getParameter<edm::InputTag>        ( "muons"          ) ), 
  massBins_     ( cfg.getParameter<std::vector<double> > ( "massBins"       ) ),  
  useEvtWgt_    ( cfg.getParameter<bool>                 ( "useEventWeight" ) ),
  correct2width_( cfg.getParameter<bool>                 ( "correctToWidth" ) ) 
{
}

/// default destructor
DimuonAnalyzer::~DimuonAnalyzer()
{
}

/// everything which has to be done before the event loop: book fileservice and histograms
void
DimuonAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ){
    throw edm::Exception( edm::errors::Configuration,
                          "TFile Service is not registered in cfg file" );
  }

  // define logarithmic bins for a histogram with 50 bins going from 10^0 to 10^2.4 =~ 250
  const int nbins = 50;
  double logmin = -0.7;
  double logmax =  3.0;
  double bins[nbins+1];
  for (int i = 0; i <= nbins; i++) {
    double log = logmin + (logmax-logmin)*i/nbins;
    bins[i] = std::pow(10.0, log);
  }
  /**
     histogram definitions
  **/ 
  // invariant muon muon mass for right charge  
  dimassRC_= fs->make<TH1F>( "dimassRC", "dimassRC", nbins, bins);
  dimassRC_->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
  dimassRC_->GetYaxis()->SetTitle("N / 1GeV");
  
  // invariant muon muon mass for wrong charge   
  dimassWC_= fs->make<TH1F>( "dimassWC", "dimassWC", nbins, bins);
  dimassWC_->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
  dimassWC_->GetYaxis()->SetTitle("N / 1GeV");  
  
  // correlation between invariant mass and absolute combined isolation        
  isoDimassCorrelation_ = fs->make<TH2F>( "isoDimassCorrelation", "isoDimassCorrelation", 10,   0.,   200., 10, 0., 1.);
  
  // absolute isolation efficiency
  absCount_    = fs->make<TH1F>( "absCount"   , "absCount"    ,100,  0.,  50.0); 
  // relative isolation efficiency       
  relCount_    = fs->make<TH1F>( "relCount"   , "relCount"    ,100,  0.,   5.0); 
  // combined isolation efficiency
  combCount_   = fs->make<TH1F>( "combCount"  , "combCount"   ,100,  0.0,  5.0); 
  // quadratically added combined isolation
  diCombCount_ = fs->make<TH1F>( "diCombCount", "diCombCount" ,100,  0.0,  7.5);  
  
  // counts number of entries in given bins of invariant mass
  nEntries_ = fs->make<TH1F>( "nEntries", "nEntries" ,massBins_.size(), massBins_[0], massBins_[massBins_.size()-1]);      
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
  
  double combIso1 = (mu1.trackIso()+mu1.caloIso())/mu1.pt();
  double combIso2 = (mu2.trackIso()+mu2.caloIso())/mu2.pt();     
  
  double diCombIso = sqrt(combIso1*combIso1+combIso2*combIso2);
  
  // fill dimass-isolation correlation hist  
  isoDimassCorrelation_->Fill( dilepMass, combIso1, weight);  
  isoDimassCorrelation_->Fill( dilepMass, combIso2, weight);
  
  // fill isolation efficiency hists    
  for(int i=1;i<=100;++i){
    if(diCombIso<0.075*i){
      diCombCount_->SetBinContent(i,diCombCount_->GetBinContent(i)+1);
    }
    if(combIso1<0.05*i && combIso2<0.05*i){
      combCount_->SetBinContent(i,combCount_->GetBinContent(i)+1);
    }
    if(relTrackIso1<(0.05*i) && relCaloIso1<(0.05*i) && relTrackIso2<(0.05*i) && relCaloIso2<(0.05*i)){
      relCount_->SetBinContent(i,relCount_->GetBinContent(i)+1);
    }
    if(absTrackIso1<(0.5*i) && absCaloIso1<(0.5*i) && absTrackIso2<(0.5*i) && absCaloIso2<(0.5*i)){
      absCount_->SetBinContent(i,absCount_->GetBinContent(i)+1);
    }      
  }
  
  // fill nEntries_
  for(int i=massBins_.size()-1; i>=0; --i){    
    if(isWrongCharge) continue;
    if(dilepMass > massBins_[i]){
      nEntries_->SetBinContent(i+1,nEntries_->GetBinContent(i+1)+1.);
      break;
    }
  }
  
//   std::cout << "++++++++++++++++++++++++++++" << std::endl;
//   std::cout << "Run # = " << evt.id().run()   << std::endl;
//   std::cout << "Evt # = " << evt.id().event() << std::endl;
//   if(isWrongCharge){
//     std::cout << "Like sign muon combination!" << std::endl;    
//   }
//   std::cout << "invariant mass = " << dilepMass << std::endl;
//   std::cout << "++++++++++++++++++++++++++++" << std::endl;   
      
}

/// everything which has to be done during the event loop: analyze and fill histos: empty
void
DimuonAnalyzer::endJob()
{
  // correct entries in dimuon mass histograms to bin width
  if(!correct2width_) return;
  
  for(int i=1; i<=dimassRC_->GetNbinsX(); ++i){
    dimassRC_->SetBinContent(i,dimassRC_->GetBinContent(i)/dimassRC_->GetBinWidth(i));
    dimassWC_->SetBinContent(i,dimassWC_->GetBinContent(i)/dimassWC_->GetBinWidth(i));
  }
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( DimuonAnalyzer );
