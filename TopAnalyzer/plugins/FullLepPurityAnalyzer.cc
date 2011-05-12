#include "TopAnalysis/TopAnalyzer/plugins/FullLepPurityAnalyzer.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "CommonTools/CandUtils/interface/AddFourMomenta.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

/// default constructor
FullLepPurityAnalyzer::FullLepPurityAnalyzer(const edm::ParameterSet& cfg):
  FullLepEvt_      (cfg.getParameter<edm::InputTag>   ("FullLepEvent") ),
  hypoKey_         (cfg.getParameter<edm::InputTag>   ("hypoKey"     ) ),
  
  lepEtaBins_      ( cfg.getParameter<std::vector<double> >( "lepEtaBins"      ) ),
  lepRapidityBins_ ( cfg.getParameter<std::vector<double> >( "lepRapidityBins" ) ),  
  lepPhiBins_      ( cfg.getParameter<std::vector<double> >( "lepPhiBins"      ) ),  
  lepPtBins_       ( cfg.getParameter<std::vector<double> >( "lepPtBins"       ) ),  

  lepBarEtaBins_      ( cfg.getParameter<std::vector<double> >( "lepBarEtaBins"      ) ),
  lepBarRapidityBins_ ( cfg.getParameter<std::vector<double> >( "lepBarRapidityBins" ) ),  
  lepBarPhiBins_      ( cfg.getParameter<std::vector<double> >( "lepBarPhiBins"      ) ),  
  lepBarPtBins_       ( cfg.getParameter<std::vector<double> >( "lepBarPtBins"       ) ),   

  lepPairEtaBins_      ( cfg.getParameter<std::vector<double> >( "lepPairEtaBins"      ) ),
  lepPairRapidityBins_ ( cfg.getParameter<std::vector<double> >( "lepPairRapidityBins" ) ),
  lepPairPhiBins_      ( cfg.getParameter<std::vector<double> >( "lepPairPhiBins"      ) ),
  lepPairPtBins_       ( cfg.getParameter<std::vector<double> >( "lepPairPtBins"       ) ),
  lepPairMassBins_     ( cfg.getParameter<std::vector<double> >( "lepPairMassBins"     ) ), 
  
  bEtaBins_      ( cfg.getParameter<std::vector<double> >( "bEtaBins"      ) ),
  bRapidityBins_ ( cfg.getParameter<std::vector<double> >( "bRapidityBins" ) ),  
  bPhiBins_      ( cfg.getParameter<std::vector<double> >( "bPhiBins"      ) ),  
  bPtBins_       ( cfg.getParameter<std::vector<double> >( "bPtBins"       ) ),  

  bBarEtaBins_      ( cfg.getParameter<std::vector<double> >( "bBarEtaBins"      ) ),
  bBarRapidityBins_ ( cfg.getParameter<std::vector<double> >( "bBarRapidityBins" ) ),  
  bBarPhiBins_      ( cfg.getParameter<std::vector<double> >( "bBarPhiBins"      ) ),  
  bBarPtBins_       ( cfg.getParameter<std::vector<double> >( "bBarPtBins"       ) ),     
  
  topEtaBins_      ( cfg.getParameter<std::vector<double> >( "topEtaBins"      ) ),
  topRapidityBins_ ( cfg.getParameter<std::vector<double> >( "topRapidityBins" ) ),  
  topPhiBins_      ( cfg.getParameter<std::vector<double> >( "topPhiBins"      ) ),  
  topPtBins_       ( cfg.getParameter<std::vector<double> >( "topPtBins"       ) ),  

  topBarEtaBins_      ( cfg.getParameter<std::vector<double> >( "topBarEtaBins"      ) ),
  topBarRapidityBins_ ( cfg.getParameter<std::vector<double> >( "topBarRapidityBins" ) ),  
  topBarPhiBins_      ( cfg.getParameter<std::vector<double> >( "topBarPhiBins"      ) ),  
  topBarPtBins_       ( cfg.getParameter<std::vector<double> >( "topBarPtBins"       ) ),   
  
  TtBarEtaBins_      ( cfg.getParameter<std::vector<double> >( "TtBarEtaBins"      ) ),
  TtBarRapidityBins_ ( cfg.getParameter<std::vector<double> >( "TtBarRapidityBins" ) ),  
  TtBarPhiBins_      ( cfg.getParameter<std::vector<double> >( "TtBarPhiBins"      ) ),  
  TtBarPtBins_       ( cfg.getParameter<std::vector<double> >( "TtBarPtBins"       ) ),  
  TtBarMassBins_     ( cfg.getParameter<std::vector<double> >( "TtBarMassBins"     ) )  
{
}

/// default destructor
FullLepPurityAnalyzer::~FullLepPurityAnalyzer()
{
}


/// everything that has to be done before the event loop: books histograms
void 
FullLepPurityAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );
  
  // apend counter reading = 0 for each bin to the vectors of counters
  initiateCounter(lepEtaBins_,      lepEtaRecGenCounters_,      lepEtaRecCounters_,      lepEtaGenCounters_     );
  initiateCounter(lepRapidityBins_, lepRapidityRecGenCounters_, lepRapidityRecCounters_, lepRapidityGenCounters_);
  initiateCounter(lepPhiBins_,      lepPhiRecGenCounters_,      lepPhiRecCounters_,      lepPhiGenCounters_     );
  initiateCounter(lepPtBins_,       lepPtRecGenCounters_,       lepPtRecCounters_,       lepPtGenCounters_      );
  
  initiateCounter(lepBarEtaBins_,      lepBarEtaRecGenCounters_,      lepBarEtaRecCounters_,      lepBarEtaGenCounters_     );
  initiateCounter(lepBarRapidityBins_, lepBarRapidityRecGenCounters_, lepBarRapidityRecCounters_, lepBarRapidityGenCounters_);
  initiateCounter(lepBarPhiBins_,      lepBarPhiRecGenCounters_,      lepBarPhiRecCounters_,      lepBarPhiGenCounters_     );
  initiateCounter(lepBarPtBins_,       lepBarPtRecGenCounters_,       lepBarPtRecCounters_,       lepBarPtGenCounters_      );

  initiateCounter(lepPairEtaBins_,      lepPairEtaRecGenCounters_,      lepPairEtaRecCounters_,      lepPairEtaGenCounters_     );
  initiateCounter(lepPairRapidityBins_, lepPairRapidityRecGenCounters_, lepPairRapidityRecCounters_, lepPairRapidityGenCounters_);
  initiateCounter(lepPairPhiBins_,      lepPairPhiRecGenCounters_,      lepPairPhiRecCounters_,      lepPairPhiGenCounters_     );
  initiateCounter(lepPairPtBins_,       lepPairPtRecGenCounters_,       lepPairPtRecCounters_,       lepPairPtGenCounters_      );
  initiateCounter(lepPairMassBins_,     lepPairMassRecGenCounters_,     lepPairMassRecCounters_,     lepPairMassGenCounters_    );
  
  initiateCounter(bEtaBins_,      bEtaRecGenCounters_,      bEtaRecCounters_,      bEtaGenCounters_     );
  initiateCounter(bRapidityBins_, bRapidityRecGenCounters_, bRapidityRecCounters_, bRapidityGenCounters_);
  initiateCounter(bPhiBins_,      bPhiRecGenCounters_,      bPhiRecCounters_,      bPhiGenCounters_     );
  initiateCounter(bPtBins_,       bPtRecGenCounters_,       bPtRecCounters_,       bPtGenCounters_      );
  
  initiateCounter(bBarEtaBins_,      bBarEtaRecGenCounters_,      bBarEtaRecCounters_,      bBarEtaGenCounters_     );
  initiateCounter(bBarRapidityBins_, bBarRapidityRecGenCounters_, bBarRapidityRecCounters_, bBarRapidityGenCounters_);
  initiateCounter(bBarPhiBins_,      bBarPhiRecGenCounters_,      bBarPhiRecCounters_,      bBarPhiGenCounters_     );
  initiateCounter(bBarPtBins_,       bBarPtRecGenCounters_,       bBarPtRecCounters_,       bBarPtGenCounters_      );
  
  initiateCounter(topEtaBins_,      topEtaRecGenCounters_,      topEtaRecCounters_,      topEtaGenCounters_     );
  initiateCounter(topRapidityBins_, topRapidityRecGenCounters_, topRapidityRecCounters_, topRapidityGenCounters_);
  initiateCounter(topPhiBins_,      topPhiRecGenCounters_,      topPhiRecCounters_,      topPhiGenCounters_     );
  initiateCounter(topPtBins_,       topPtRecGenCounters_,       topPtRecCounters_,       topPtGenCounters_      );
  
  initiateCounter(topBarEtaBins_,      topBarEtaRecGenCounters_,      topBarEtaRecCounters_,      topBarEtaGenCounters_     );
  initiateCounter(topBarRapidityBins_, topBarRapidityRecGenCounters_, topBarRapidityRecCounters_, topBarRapidityGenCounters_);
  initiateCounter(topBarPhiBins_,      topBarPhiRecGenCounters_,      topBarPhiRecCounters_,      topBarPhiGenCounters_     );
  initiateCounter(topBarPtBins_,       topBarPtRecGenCounters_,       topBarPtRecCounters_,       topBarPtGenCounters_      );    
  
  initiateCounter(TtBarEtaBins_,      TtBarEtaRecGenCounters_,      TtBarEtaRecCounters_,      TtBarEtaGenCounters_     );
  initiateCounter(TtBarRapidityBins_, TtBarRapidityRecGenCounters_, TtBarRapidityRecCounters_, TtBarRapidityGenCounters_);
  initiateCounter(TtBarPhiBins_,      TtBarPhiRecGenCounters_,      TtBarPhiRecCounters_,      TtBarPhiGenCounters_     );
  initiateCounter(TtBarPtBins_,       TtBarPtRecGenCounters_,       TtBarPtRecCounters_,       TtBarPtGenCounters_      );
  initiateCounter(TtBarMassBins_,     TtBarMassRecGenCounters_,     TtBarMassRecCounters_,     TtBarMassGenCounters_    );

  
  NameScheme nsp("purity");
  lepEtaPurity_       = fs->make<TH1D>(nsp.name( "lepEta" ),      "purity #eta(l^{-})",  lepEtaBins_.size()-1,      &lepEtaBins_.front()      );
  lepRapidityPurity_  = fs->make<TH1D>(nsp.name( "lepRapidity" ), "purity y(l^{-})",     lepRapidityBins_.size()-1, &lepRapidityBins_.front() );
  lepPhiPurity_       = fs->make<TH1D>(nsp.name( "lepPhi" ),      "purity #phi(l^{-})",  lepPhiBins_.size()-1,      &lepPhiBins_.front()      );
  lepPtPurity_        = fs->make<TH1D>(nsp.name( "lepPt" ),       "purity p_{T}(l^{-})", lepPtBins_.size()-1,       &lepPtBins_.front()       );
  
  lepBarEtaPurity_       = fs->make<TH1D>(nsp.name( "lepBarEta" ),      "purity #eta(l^{+})",  lepBarEtaBins_.size()-1,      &lepBarEtaBins_.front()      );
  lepBarRapidityPurity_  = fs->make<TH1D>(nsp.name( "lepBarRapidity" ), "purity y(l^{+})",     lepBarRapidityBins_.size()-1, &lepBarRapidityBins_.front() );
  lepBarPhiPurity_       = fs->make<TH1D>(nsp.name( "lepBarPhi" ),      "purity #phi(l^{+})",  lepBarPhiBins_.size()-1,      &lepBarPhiBins_.front()      );
  lepBarPtPurity_        = fs->make<TH1D>(nsp.name( "lepBarPt" ),       "purity p_{T}(l^{+})", lepBarPtBins_.size()-1,       &lepBarPtBins_.front()       );

  lepPairEtaPurity_       = fs->make<TH1D>(nsp.name( "lepPairEta" ),      "purity #eta(l^{+}l^{-})",  lepPairEtaBins_.size()-1,      &lepPairEtaBins_.front()      );
  lepPairRapidityPurity_  = fs->make<TH1D>(nsp.name( "lepPairRapidity" ), "purity y(l^{+}l^{-})",     lepPairRapidityBins_.size()-1, &lepPairRapidityBins_.front() );
  lepPairPhiPurity_       = fs->make<TH1D>(nsp.name( "lepPairPhi" ),      "purity #phi(l^{+}l^{-})",  lepPairPhiBins_.size()-1,      &lepPairPhiBins_.front()      );
  lepPairPtPurity_        = fs->make<TH1D>(nsp.name( "lepPairPt" ),       "purity p_{T}(l^{+}l^{-})", lepPairPtBins_.size()-1,       &lepPairPtBins_.front()       );  
  lepPairMassPurity_      = fs->make<TH1D>(nsp.name( "lepPairMass" ),     "purity M(l^{+}l^{-})",     lepPairMassBins_.size()-1,     &lepPairMassBins_.front()     ); 
  
  bEtaPurity_       = fs->make<TH1D>(nsp.name( "bEta" ),      "purity #eta(b)",  bEtaBins_.size()-1,      &bEtaBins_.front()      );
  bRapidityPurity_  = fs->make<TH1D>(nsp.name( "bRapidity" ), "purity y(b)",     bRapidityBins_.size()-1, &bRapidityBins_.front() );
  bPhiPurity_       = fs->make<TH1D>(nsp.name( "bPhi" ),      "purity #phi(b)",  bPhiBins_.size()-1,      &bPhiBins_.front()      );
  bPtPurity_        = fs->make<TH1D>(nsp.name( "bPt" ),       "purity p_{T}(b)", bPtBins_.size()-1,       &bPtBins_.front()       );
  
  bBarEtaPurity_       = fs->make<TH1D>(nsp.name( "bBarEta" ),      "purity #eta(#bar{b})",  bBarEtaBins_.size()-1,      &bBarEtaBins_.front()      );
  bBarRapidityPurity_  = fs->make<TH1D>(nsp.name( "bBarRapidity" ), "purity y(#bar{b})",     bBarRapidityBins_.size()-1, &bBarRapidityBins_.front() );
  bBarPhiPurity_       = fs->make<TH1D>(nsp.name( "bBarPhi" ),      "purity #phi(#bar{b})",  bBarPhiBins_.size()-1,      &bBarPhiBins_.front()      );
  bBarPtPurity_        = fs->make<TH1D>(nsp.name( "bBarPt" ),       "purity p_{T}(#bar{b})", bBarPtBins_.size()-1,       &bBarPtBins_.front()       );  

  topEtaPurity_       = fs->make<TH1D>(nsp.name( "topEta" ),      "purity #eta(t)",  topEtaBins_.size()-1,      &topEtaBins_.front()      );
  topRapidityPurity_  = fs->make<TH1D>(nsp.name( "topRapidity" ), "purity y(t)",     topRapidityBins_.size()-1, &topRapidityBins_.front() );
  topPhiPurity_       = fs->make<TH1D>(nsp.name( "topPhi" ),      "purity #phi(t)",  topPhiBins_.size()-1,      &topPhiBins_.front()      );
  topPtPurity_        = fs->make<TH1D>(nsp.name( "topPt" ),       "purity p_{T}(t)", topPtBins_.size()-1,       &topPtBins_.front()       );
  
  topBarEtaPurity_       = fs->make<TH1D>(nsp.name( "topBarEta" ),      "purity #eta(#bar{t})",  topBarEtaBins_.size()-1,      &topBarEtaBins_.front()      );
  topBarRapidityPurity_  = fs->make<TH1D>(nsp.name( "topBarRapidity" ), "purity y(#bar{t})",     topBarRapidityBins_.size()-1, &topBarRapidityBins_.front() );
  topBarPhiPurity_       = fs->make<TH1D>(nsp.name( "topBarPhi" ),      "purity #phi(#bar{t})",  topBarPhiBins_.size()-1,      &topBarPhiBins_.front()      );
  topBarPtPurity_        = fs->make<TH1D>(nsp.name( "topBarPt" ),       "purity p_{T}(#bar{t})", topBarPtBins_.size()-1,       &topBarPtBins_.front()       );
  
  TtBarEtaPurity_       = fs->make<TH1D>(nsp.name( "TtBarEta" ),      "purity #eta(t#bar{t})",  TtBarEtaBins_.size()-1,      &TtBarEtaBins_.front()      );
  TtBarRapidityPurity_  = fs->make<TH1D>(nsp.name( "TtBarRapidity" ), "purity y(t#bar{t})",     TtBarRapidityBins_.size()-1, &TtBarRapidityBins_.front() );
  TtBarPhiPurity_       = fs->make<TH1D>(nsp.name( "TtBarPhi" ),      "purity #phi(t#bar{t})",  TtBarPhiBins_.size()-1,      &TtBarPhiBins_.front()      );
  TtBarPtPurity_        = fs->make<TH1D>(nsp.name( "TtBarPt" ),       "purity p_{T}(t#bar{t})", TtBarPtBins_.size()-1,       &TtBarPtBins_.front()       );  
  TtBarMassPurity_      = fs->make<TH1D>(nsp.name( "TtBarMass" ),     "purity M(t#bar{t})",     TtBarMassBins_.size()-1,     &TtBarMassBins_.front()     ); 

  
  NameScheme nss("stability");  
  lepEtaStability_       = fs->make<TH1D>(nss.name( "lepEta" ),      "stability #eta(l^{-})",  lepEtaBins_.size()-1,      &lepEtaBins_.front()      );
  lepRapidityStability_  = fs->make<TH1D>(nss.name( "lepRapidity" ), "stability y(l^{-})",     lepRapidityBins_.size()-1, &lepRapidityBins_.front() );
  lepPhiStability_       = fs->make<TH1D>(nss.name( "lepPhi" ),      "stability #phi(l^{-})",  lepPhiBins_.size()-1,      &lepPhiBins_.front()      );
  lepPtStability_        = fs->make<TH1D>(nss.name( "lepPt" ),       "stability p_{T}(l^{-})", lepPtBins_.size()-1,       &lepPtBins_.front()       );
  
  lepBarEtaStability_       = fs->make<TH1D>(nss.name( "lepBarEta" ),      "stability #eta(l^{+})",  lepBarEtaBins_.size()-1,      &lepBarEtaBins_.front()      );
  lepBarRapidityStability_  = fs->make<TH1D>(nss.name( "lepBarRapidity" ), "stability y(l^{+})",     lepBarRapidityBins_.size()-1, &lepBarRapidityBins_.front() );
  lepBarPhiStability_       = fs->make<TH1D>(nss.name( "lepBarPhi" ),      "stability #phi(l^{+})",  lepBarPhiBins_.size()-1,      &lepBarPhiBins_.front()      );
  lepBarPtStability_        = fs->make<TH1D>(nss.name( "lepBarPt" ),       "stability p_{T}(l^{+})", lepBarPtBins_.size()-1,       &lepBarPtBins_.front()       );

  lepPairEtaStability_       = fs->make<TH1D>(nss.name( "lepPairEta" ),      "stability #eta(l^{+}l^{-})",  lepPairEtaBins_.size()-1,      &lepPairEtaBins_.front()      );
  lepPairRapidityStability_  = fs->make<TH1D>(nss.name( "lepPairRapidity" ), "stability y(l^{+}l^{-})",     lepPairRapidityBins_.size()-1, &lepPairRapidityBins_.front() );
  lepPairPhiStability_       = fs->make<TH1D>(nss.name( "lepPairPhi" ),      "stability #phi(l^{+}l^{-})",  lepPairPhiBins_.size()-1,      &lepPairPhiBins_.front()      );
  lepPairPtStability_        = fs->make<TH1D>(nss.name( "lepPairPt" ),       "stability p_{T}(l^{+}l^{-})", lepPairPtBins_.size()-1,       &lepPairPtBins_.front()       );  
  lepPairMassStability_      = fs->make<TH1D>(nss.name( "lepPairMass" ),     "stability M(l^{+}l^{-})",     lepPairMassBins_.size()-1,     &lepPairMassBins_.front()     ); 
  
  bEtaStability_       = fs->make<TH1D>(nss.name( "bEta" ),      "stability #eta(b)",  bEtaBins_.size()-1,      &bEtaBins_.front()      );
  bRapidityStability_  = fs->make<TH1D>(nss.name( "bRapidity" ), "stability y(b)",     bRapidityBins_.size()-1, &bRapidityBins_.front() );
  bPhiStability_       = fs->make<TH1D>(nss.name( "bPhi" ),      "stability #phi(b)",  bPhiBins_.size()-1,      &bPhiBins_.front()      );
  bPtStability_        = fs->make<TH1D>(nss.name( "bPt" ),       "stability p_{T}(b)", bPtBins_.size()-1,       &bPtBins_.front()       );
  
  bBarEtaStability_       = fs->make<TH1D>(nss.name( "bBarEta" ),      "stability #eta(#bar{b})",  bBarEtaBins_.size()-1,      &bBarEtaBins_.front()      );
  bBarRapidityStability_  = fs->make<TH1D>(nss.name( "bBarRapidity" ), "stability y(#bar{b})",     bBarRapidityBins_.size()-1, &bBarRapidityBins_.front() );
  bBarPhiStability_       = fs->make<TH1D>(nss.name( "bBarPhi" ),      "stability #phi(#bar{b})",  bBarPhiBins_.size()-1,      &bBarPhiBins_.front()      );
  bBarPtStability_        = fs->make<TH1D>(nss.name( "bBarPt" ),       "stability p_{T}(#bar{b})", bBarPtBins_.size()-1,       &bBarPtBins_.front()       );  

  topEtaStability_       = fs->make<TH1D>(nss.name( "topEta" ),      "stability #eta(t)",  topEtaBins_.size()-1,      &topEtaBins_.front()      );
  topRapidityStability_  = fs->make<TH1D>(nss.name( "topRapidity" ), "stability y(t)",     topRapidityBins_.size()-1, &topRapidityBins_.front() );
  topPhiStability_       = fs->make<TH1D>(nss.name( "topPhi" ),      "stability #phi(t)",  topPhiBins_.size()-1,      &topPhiBins_.front()      );
  topPtStability_        = fs->make<TH1D>(nss.name( "topPt" ),       "stability p_{T}(t)", topPtBins_.size()-1,       &topPtBins_.front()       );
  
  topBarEtaStability_       = fs->make<TH1D>(nss.name( "topBarEta" ),      "stability #eta(#bar{t})",  topBarEtaBins_.size()-1,      &topBarEtaBins_.front()      );	
  topBarRapidityStability_  = fs->make<TH1D>(nss.name( "topBarRapidity" ), "stability y(#bar{t})",     topBarRapidityBins_.size()-1, &topBarRapidityBins_.front() );
  topBarPhiStability_       = fs->make<TH1D>(nss.name( "topBarPhi" ),      "stability #phi(#bar{t})",  topBarPhiBins_.size()-1,      &topBarPhiBins_.front()      );
  topBarPtStability_        = fs->make<TH1D>(nss.name( "topBarPt" ),       "stability p_{T}(#bar{t})", topBarPtBins_.size()-1,       &topBarPtBins_.front()       );

  TtBarEtaStability_       = fs->make<TH1D>(nss.name( "TtBarEta" ),      "stability #eta(t#bar{t})",  TtBarEtaBins_.size()-1,      &TtBarEtaBins_.front()      );
  TtBarRapidityStability_  = fs->make<TH1D>(nss.name( "TtBarRapidity" ), "stability y(t#bar{t})",     TtBarRapidityBins_.size()-1, &TtBarRapidityBins_.front() );
  TtBarPhiStability_       = fs->make<TH1D>(nss.name( "TtBarPhi" ),      "stability #phi(t#bar{t})",  TtBarPhiBins_.size()-1,      &TtBarPhiBins_.front()      );
  TtBarPtStability_        = fs->make<TH1D>(nss.name( "TtBarPt" ),       "stability p_{T}(t#bar{t})", TtBarPtBins_.size()-1,       &TtBarPtBins_.front()       ); 
  TtBarMassStability_      = fs->make<TH1D>(nss.name( "TtBarMass" ),     "stability M(t#bar{t})",     TtBarMassBins_.size()-1,     &TtBarMassBins_.front()     );     
}


/// everything that has to be done during the event loop: filling plots
void
FullLepPurityAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{
  edm::Handle<TtFullLeptonicEvent> FullLepEvt;
  evt.getByLabel(FullLepEvt_, FullLepEvt);

  edm::Handle<int> hypoKeyHandle;
  evt.getByLabel(hypoKey_, hypoKeyHandle);
  TtEvent::HypoClassKey& hypoKey = (TtEvent::HypoClassKey&) *hypoKeyHandle;

  // -----------------------
  // check if hypothesis is valid in this event
  // and if it satisfies some quality criteria
  // -----------------------
         
  if( !FullLepEvt->isHypoAvailable(hypoKey) ){
    edm::LogInfo ( "NonValidHyp" ) << "Hypothesis not available for this event";
    return;
  }
  
  if( !FullLepEvt->isHypoValid(hypoKey) ){  
    edm::LogInfo ( "NonValidHyp" ) << "Hypothesis not valid for this event";
    return;  // return if any of the hypotheses is not valid
  }  

  if( !FullLepEvt->genEvent() || !FullLepEvt->genEvent()->isFullLeptonic()){
    edm::LogInfo ( "NonValidHyp" ) << "No Dileptonic Generator Event";
    return;  
  }
  
  const reco::Candidate* top    = FullLepEvt->top(hypoKey);
  const reco::Candidate* b      = FullLepEvt->b(hypoKey);
  const reco::Candidate* lepBar = FullLepEvt->leptonBar(hypoKey);  
  const reco::Candidate* topBar = FullLepEvt->topBar(hypoKey);
  const reco::Candidate* bBar   = FullLepEvt->bBar(hypoKey);
  const reco::Candidate* lep    = FullLepEvt->lepton(hypoKey);

  AddFourMomenta addFourMomenta;
  
  // combined top pair object
  reco::CompositeCandidate* TtBar = new reco::CompositeCandidate();
  TtBar->addDaughter(*top);
  TtBar->addDaughter(*topBar);
  addFourMomenta.set(*TtBar);
  
  // combined lepton pair object 
  reco::CompositeCandidate* lepPair = new reco::CompositeCandidate();
  lepPair->addDaughter(*lep);
  lepPair->addDaughter(*lepBar);  
  addFourMomenta.set(*lepPair);
  
  const reco::Candidate* genTop    = FullLepEvt->genTop();
  const reco::Candidate* genB      = FullLepEvt->genB();
  const reco::Candidate* genLepBar = FullLepEvt->genLeptonBar();
  const reco::Candidate* genTopBar = FullLepEvt->genTopBar();
  const reco::Candidate* genBBar   = FullLepEvt->genBBar();
  const reco::Candidate* genLep    = FullLepEvt->genLepton();

  // combined top pair object
  reco::CompositeCandidate* genTtBar = new reco::CompositeCandidate();
  genTtBar->addDaughter(*genTop);
  genTtBar->addDaughter(*genTopBar);  
  addFourMomenta.set(*genTtBar);
  
  // combined lepton pair object 
  reco::CompositeCandidate* genLepPair = new reco::CompositeCandidate();
  genLepPair->addDaughter(*genLep);
  genLepPair->addDaughter(*genLepBar);
  addFourMomenta.set(*genLepPair);

  // count events where given quantity is generated AND reconstructed inside a certain bin
  countRecGen(lep->eta(),      genLep->eta(),	    lepEtaBins_,      lepEtaRecGenCounters_	 );
  countRecGen(lep->rapidity(), genLep->rapidity(),  lepRapidityBins_, lepRapidityRecGenCounters_ );
  countRecGen(lep->phi(),      genLep->phi(),	    lepPhiBins_,      lepPhiRecGenCounters_	 );
  countRecGen(lep->pt(),       genLep->pt(),	    lepPtBins_,       lepPtRecGenCounters_	 );

  countRecGen(lepBar->eta(),	  genLepBar->eta(),	 lepBarEtaBins_,      lepBarEtaRecGenCounters_      );
  countRecGen(lepBar->rapidity(), genLepBar->rapidity(), lepBarRapidityBins_, lepBarRapidityRecGenCounters_ );
  countRecGen(lepBar->phi(),	  genLepBar->phi(),	 lepBarPhiBins_,      lepBarPhiRecGenCounters_      );
  countRecGen(lepBar->pt(),	  genLepBar->pt(),	 lepBarPtBins_,       lepBarPtRecGenCounters_	    );
  
  countRecGen(lepPair->eta(),      genLepPair->eta(),      lepPairEtaBins_,      lepPairEtaRecGenCounters_      );
  countRecGen(lepPair->rapidity(), genLepPair->rapidity(), lepPairRapidityBins_, lepPairRapidityRecGenCounters_ );
  countRecGen(lepPair->phi(),      genLepPair->phi(),      lepPairPhiBins_,      lepPairPhiRecGenCounters_      );
  countRecGen(lepPair->pt(),       genLepPair->pt(),       lepPairPtBins_,       lepPairPtRecGenCounters_       );  
  countRecGen(lepPair->mass(),     genLepPair->mass(),     lepPairMassBins_,     lepPairMassRecGenCounters_     );   

  countRecGen(b->eta(),      genB->eta(),      bEtaBins_,      bEtaRecGenCounters_      );
  countRecGen(b->rapidity(), genB->rapidity(), bRapidityBins_, bRapidityRecGenCounters_ );
  countRecGen(b->phi(),      genB->phi(),      bPhiBins_,      bPhiRecGenCounters_      );
  countRecGen(b->pt(),       genB->pt(),       bPtBins_,       bPtRecGenCounters_       );
  
  countRecGen(bBar->eta(),	genBBar->eta(),      bBarEtaBins_,	bBarEtaRecGenCounters_      );
  countRecGen(bBar->rapidity(), genBBar->rapidity(), bBarRapidityBins_, bBarRapidityRecGenCounters_ );
  countRecGen(bBar->phi(),	genBBar->phi(),      bBarPhiBins_,	bBarPhiRecGenCounters_      );
  countRecGen(bBar->pt(),	genBBar->pt(),       bBarPtBins_,	bBarPtRecGenCounters_	    );
  
  countRecGen(top->eta(),      genTop->eta(),	   topEtaBins_,      topEtaRecGenCounters_	);
  countRecGen(top->rapidity(), genTop->rapidity(), topRapidityBins_, topRapidityRecGenCounters_ );
  countRecGen(top->phi(),      genTop->phi(),	   topPhiBins_,      topPhiRecGenCounters_	);
  countRecGen(top->pt(),       genTop->pt(),	   topPtBins_,       topPtRecGenCounters_	);
  
  countRecGen(topBar->eta(),	  genTopBar->eta(),	 topBarEtaBins_,      topBarEtaRecGenCounters_      );
  countRecGen(topBar->rapidity(), genTopBar->rapidity(), topBarRapidityBins_, topBarRapidityRecGenCounters_ );
  countRecGen(topBar->phi(),	  genTopBar->phi(),	 topBarPhiBins_,      topBarPhiRecGenCounters_      );
  countRecGen(topBar->pt(),	  genTopBar->pt(),	 topBarPtBins_,       topBarPtRecGenCounters_	    );  
  
  countRecGen(TtBar->eta(),	 genTtBar->eta(),      TtBarEtaBins_,	   TtBarEtaRecGenCounters_	);
  countRecGen(TtBar->rapidity(), genTtBar->rapidity(), TtBarRapidityBins_, TtBarRapidityRecGenCounters_ );
  countRecGen(TtBar->phi(),	 genTtBar->phi(),      TtBarPhiBins_,	   TtBarPhiRecGenCounters_	);
  countRecGen(TtBar->pt(),	 genTtBar->pt(),       TtBarPtBins_,	   TtBarPtRecGenCounters_	);  
  countRecGen(TtBar->mass(),	 genTtBar->mass(),     TtBarMassBins_,     TtBarMassRecGenCounters_	);    


  // count events where given quantity is reconstructed inside a certain bin    
  countRec(lep->eta(),      lepEtaBins_,      lepEtaRecCounters_      );
  countRec(lep->rapidity(), lepRapidityBins_, lepRapidityRecCounters_ );
  countRec(lep->phi(),      lepPhiBins_,      lepPhiRecCounters_      );
  countRec(lep->pt(),	    lepPtBins_,       lepPtRecCounters_       );
  
  countRec(lepBar->eta(),      lepBarEtaBins_,      lepBarEtaRecCounters_      );
  countRec(lepBar->rapidity(), lepBarRapidityBins_, lepBarRapidityRecCounters_ );
  countRec(lepBar->phi(),      lepBarPhiBins_,      lepBarPhiRecCounters_      );
  countRec(lepBar->pt(),       lepBarPtBins_,	    lepBarPtRecCounters_       );
  
  countRec(lepPair->eta(),	lepPairEtaBins_,      lepPairEtaRecCounters_	  );
  countRec(lepPair->rapidity(), lepPairRapidityBins_, lepPairRapidityRecCounters_ );
  countRec(lepPair->phi(),	lepPairPhiBins_,      lepPairPhiRecCounters_	  );
  countRec(lepPair->pt(),	lepPairPtBins_,       lepPairPtRecCounters_	  );  
  countRec(lepPair->mass(),	lepPairMassBins_,     lepPairMassRecCounters_	  );   

  countRec(b->eta(),	  bEtaBins_,	  bEtaRecCounters_      );
  countRec(b->rapidity(), bRapidityBins_, bRapidityRecCounters_ );
  countRec(b->phi(),	  bPhiBins_,	  bPhiRecCounters_      );
  countRec(b->pt(),	  bPtBins_,	  bPtRecCounters_       );
  
  countRec(bBar->eta(),      bBarEtaBins_,	bBarEtaRecCounters_	 );
  countRec(bBar->rapidity(), bBarRapidityBins_, bBarRapidityRecCounters_ );
  countRec(bBar->phi(),      bBarPhiBins_,	bBarPhiRecCounters_	 );
  countRec(bBar->pt(),       bBarPtBins_,	bBarPtRecCounters_       );
  
  countRec(top->eta(),      topEtaBins_,      topEtaRecCounters_      );
  countRec(top->rapidity(), topRapidityBins_, topRapidityRecCounters_ );
  countRec(top->phi(),      topPhiBins_,      topPhiRecCounters_      );
  countRec(top->pt(),	    topPtBins_,       topPtRecCounters_       );
  
  countRec(topBar->eta(),      topBarEtaBins_,      topBarEtaRecCounters_      );
  countRec(topBar->rapidity(), topBarRapidityBins_, topBarRapidityRecCounters_ );
  countRec(topBar->phi(),      topBarPhiBins_,      topBarPhiRecCounters_      );
  countRec(topBar->pt(),       topBarPtBins_,	    topBarPtRecCounters_       );  
  
  countRec(TtBar->eta(),      TtBarEtaBins_,	  TtBarEtaRecCounters_      );
  countRec(TtBar->rapidity(), TtBarRapidityBins_, TtBarRapidityRecCounters_ );
  countRec(TtBar->phi(),      TtBarPhiBins_,	  TtBarPhiRecCounters_      );
  countRec(TtBar->pt(),       TtBarPtBins_,	  TtBarPtRecCounters_	    );  
  countRec(TtBar->mass(),     TtBarMassBins_,	  TtBarMassRecCounters_     );


  // count events where given quantity is generated inside a certain bin    
  countGen(genLep->eta(),      lepEtaBins_,	 lepEtaGenCounters_	 );
  countGen(genLep->rapidity(), lepRapidityBins_, lepRapidityGenCounters_ );
  countGen(genLep->phi(),      lepPhiBins_,	 lepPhiGenCounters_	 );
  countGen(genLep->pt(),       lepPtBins_,	 lepPtGenCounters_	 );
  
  countGen(genLepBar->eta(),	  lepBarEtaBins_,      lepBarEtaGenCounters_	  );
  countGen(genLepBar->rapidity(), lepBarRapidityBins_, lepBarRapidityGenCounters_ );
  countGen(genLepBar->phi(),	  lepBarPhiBins_,      lepBarPhiGenCounters_	  );
  countGen(genLepBar->pt(),	  lepBarPtBins_,       lepBarPtGenCounters_	  );
  
  countGen(genLepPair->eta(),	   lepPairEtaBins_,	 lepPairEtaGenCounters_      );
  countGen(genLepPair->rapidity(), lepPairRapidityBins_, lepPairRapidityGenCounters_ );
  countGen(genLepPair->phi(),	   lepPairPhiBins_,	 lepPairPhiGenCounters_      );
  countGen(genLepPair->pt(),	   lepPairPtBins_,	 lepPairPtGenCounters_       );  
  countGen(genLepPair->mass(),     lepPairMassBins_,	 lepPairMassGenCounters_     );   

  countGen(genB->eta(),      bEtaBins_,      bEtaGenCounters_	   );
  countGen(genB->rapidity(), bRapidityBins_, bRapidityGenCounters_ );
  countGen(genB->phi(),      bPhiBins_,      bPhiGenCounters_	   );
  countGen(genB->pt(),       bPtBins_,       bPtGenCounters_	   );
  
  countGen(genBBar->eta(),      bBarEtaBins_,	   bBarEtaGenCounters_      );
  countGen(genBBar->rapidity(), bBarRapidityBins_, bBarRapidityGenCounters_ );
  countGen(genBBar->phi(),      bBarPhiBins_,	   bBarPhiGenCounters_      );
  countGen(genBBar->pt(),       bBarPtBins_,	   bBarPtGenCounters_	    );
  
  countGen(genTop->eta(),      topEtaBins_,	 topEtaGenCounters_	 );
  countGen(genTop->rapidity(), topRapidityBins_, topRapidityGenCounters_ );
  countGen(genTop->phi(),      topPhiBins_,	 topPhiGenCounters_	 );
  countGen(genTop->pt(),       topPtBins_,	 topPtGenCounters_	 );
  
  countGen(genTopBar->eta(),	  topBarEtaBins_,      topBarEtaGenCounters_	  );
  countGen(genTopBar->rapidity(), topBarRapidityBins_, topBarRapidityGenCounters_ );
  countGen(genTopBar->phi(),	  topBarPhiBins_,      topBarPhiGenCounters_	  );
  countGen(genTopBar->pt(),	  topBarPtBins_,       topBarPtGenCounters_	  );  
  
  countGen(genTtBar->eta(),	 TtBarEtaBins_,      TtBarEtaGenCounters_      );
  countGen(genTtBar->rapidity(), TtBarRapidityBins_, TtBarRapidityGenCounters_ );
  countGen(genTtBar->phi(),	 TtBarPhiBins_,      TtBarPhiGenCounters_      );
  countGen(genTtBar->pt(),	 TtBarPtBins_,	     TtBarPtGenCounters_       );  
  countGen(genTtBar->mass(),	 TtBarMassBins_,     TtBarMassGenCounters_     );
}


/// everything that has to be done after the event loop
void
FullLepPurityAnalyzer::endJob() 
{
  // evaluate purities
  evaluate(*lepEtaPurity_,      lepEtaRecGenCounters_,      lepEtaRecCounters_      );
  evaluate(*lepRapidityPurity_, lepRapidityRecGenCounters_, lepRapidityRecCounters_ );  
  evaluate(*lepPhiPurity_,      lepPhiRecGenCounters_,      lepPhiRecCounters_      );
  evaluate(*lepPtPurity_,       lepPtRecGenCounters_,       lepPtRecCounters_       );  
  
  evaluate(*lepBarEtaPurity_,      lepBarEtaRecGenCounters_,      lepBarEtaRecCounters_      );
  evaluate(*lepBarRapidityPurity_, lepBarRapidityRecGenCounters_, lepBarRapidityRecCounters_ );
  evaluate(*lepBarPhiPurity_,      lepBarPhiRecGenCounters_,      lepBarPhiRecCounters_      );
  evaluate(*lepBarPtPurity_,       lepBarPtRecGenCounters_,       lepBarPtRecCounters_       );  
  
  evaluate(*lepPairEtaPurity_,	    lepPairEtaRecGenCounters_,      lepPairEtaRecCounters_      );
  evaluate(*lepPairRapidityPurity_, lepPairRapidityRecGenCounters_, lepPairRapidityRecCounters_ );
  evaluate(*lepPairPhiPurity_,	    lepPairPhiRecGenCounters_,      lepPairPhiRecCounters_      );
  evaluate(*lepPairPtPurity_,	    lepPairPtRecGenCounters_,       lepPairPtRecCounters_       );  
  evaluate(*lepPairMassPurity_,	    lepPairMassRecGenCounters_,     lepPairMassRecCounters_     );    
  
  evaluate(*bEtaPurity_,      bEtaRecGenCounters_,      bEtaRecCounters_      );
  evaluate(*bRapidityPurity_, bRapidityRecGenCounters_, bRapidityRecCounters_ );
  evaluate(*bPhiPurity_,      bPhiRecGenCounters_,      bPhiRecCounters_      );
  evaluate(*bPtPurity_,       bPtRecGenCounters_,       bPtRecCounters_       );
  
  evaluate(*bBarEtaPurity_,      bBarEtaRecGenCounters_,      bBarEtaRecCounters_      );
  evaluate(*bBarRapidityPurity_, bBarRapidityRecGenCounters_, bBarRapidityRecCounters_ );
  evaluate(*bBarPhiPurity_,      bBarPhiRecGenCounters_,      bBarPhiRecCounters_      );
  evaluate(*bBarPtPurity_,       bBarPtRecGenCounters_,       bBarPtRecCounters_       );
    
  evaluate(*topEtaPurity_,      topEtaRecGenCounters_,      topEtaRecCounters_      );
  evaluate(*topRapidityPurity_, topRapidityRecGenCounters_, topRapidityRecCounters_ );
  evaluate(*topPhiPurity_,      topPhiRecGenCounters_,      topPhiRecCounters_      );
  evaluate(*topPtPurity_,       topPtRecGenCounters_,       topPtRecCounters_       );
  
  evaluate(*topBarEtaPurity_,      topBarEtaRecGenCounters_,      topBarEtaRecCounters_      );
  evaluate(*topBarRapidityPurity_, topBarRapidityRecGenCounters_, topBarRapidityRecCounters_ );
  evaluate(*topBarPhiPurity_,      topBarPhiRecGenCounters_,      topBarPhiRecCounters_      );
  evaluate(*topBarPtPurity_,       topBarPtRecGenCounters_,       topBarPtRecCounters_       );  
  
  evaluate(*TtBarEtaPurity_,	  TtBarEtaRecGenCounters_,      TtBarEtaRecCounters_	  );
  evaluate(*TtBarRapidityPurity_, TtBarRapidityRecGenCounters_, TtBarRapidityRecCounters_ );
  evaluate(*TtBarPhiPurity_,	  TtBarPhiRecGenCounters_,      TtBarPhiRecCounters_	  );
  evaluate(*TtBarPtPurity_,	  TtBarPtRecGenCounters_,       TtBarPtRecCounters_	  );  
  evaluate(*TtBarMassPurity_,	  TtBarMassRecGenCounters_,     TtBarMassRecCounters_	  );  


  // evaluate stabilities
  evaluate(*lepEtaStability_,      lepEtaRecGenCounters_,      lepEtaGenCounters_      );
  evaluate(*lepRapidityStability_, lepRapidityRecGenCounters_, lepRapidityGenCounters_ );  
  evaluate(*lepPhiStability_,      lepPhiRecGenCounters_,      lepPhiGenCounters_      );
  evaluate(*lepPtStability_,       lepPtRecGenCounters_,       lepPtGenCounters_       );  
  
  evaluate(*lepBarEtaStability_,      lepBarEtaRecGenCounters_,      lepBarEtaGenCounters_      );
  evaluate(*lepBarRapidityStability_, lepBarRapidityRecGenCounters_, lepBarRapidityGenCounters_ );
  evaluate(*lepBarPhiStability_,      lepBarPhiRecGenCounters_,      lepBarPhiGenCounters_      );
  evaluate(*lepBarPtStability_,       lepBarPtRecGenCounters_,       lepBarPtGenCounters_       );  
  
  evaluate(*lepPairEtaStability_,      lepPairEtaRecGenCounters_,      lepPairEtaGenCounters_	   );
  evaluate(*lepPairRapidityStability_, lepPairRapidityRecGenCounters_, lepPairRapidityGenCounters_ );
  evaluate(*lepPairPhiStability_,      lepPairPhiRecGenCounters_,      lepPairPhiGenCounters_	   );
  evaluate(*lepPairPtStability_,       lepPairPtRecGenCounters_,       lepPairPtGenCounters_	   );
  evaluate(*lepPairMassStability_,     lepPairMassRecGenCounters_,     lepPairMassGenCounters_     );
  
  evaluate(*bEtaStability_,      bEtaRecGenCounters_,      bEtaGenCounters_      );
  evaluate(*bRapidityStability_, bRapidityRecGenCounters_, bRapidityGenCounters_ );
  evaluate(*bPhiStability_,      bPhiRecGenCounters_,      bPhiGenCounters_      );
  evaluate(*bPtStability_,       bPtRecGenCounters_,       bPtGenCounters_       );
  
  evaluate(*bBarEtaStability_,      bBarEtaRecGenCounters_,      bBarEtaGenCounters_      );
  evaluate(*bBarRapidityStability_, bBarRapidityRecGenCounters_, bBarRapidityGenCounters_ );
  evaluate(*bBarPhiStability_,      bBarPhiRecGenCounters_,      bBarPhiGenCounters_      );
  evaluate(*bBarPtStability_,       bBarPtRecGenCounters_,       bBarPtGenCounters_       );
    
  evaluate(*topEtaStability_,      topEtaRecGenCounters_,      topEtaGenCounters_      );
  evaluate(*topRapidityStability_, topRapidityRecGenCounters_, topRapidityGenCounters_ );
  evaluate(*topPhiStability_,      topPhiRecGenCounters_,      topPhiGenCounters_      );
  evaluate(*topPtStability_,       topPtRecGenCounters_,       topPtGenCounters_       );
  
  evaluate(*topBarEtaStability_,      topBarEtaRecGenCounters_,      topBarEtaGenCounters_      );
  evaluate(*topBarRapidityStability_, topBarRapidityRecGenCounters_, topBarRapidityGenCounters_ );
  evaluate(*topBarPhiStability_,      topBarPhiRecGenCounters_,      topBarPhiGenCounters_      );
  evaluate(*topBarPtStability_,       topBarPtRecGenCounters_,       topBarPtGenCounters_       );  
  
  evaluate(*TtBarEtaStability_,	     TtBarEtaRecGenCounters_,         TtBarEtaGenCounters_      );
  evaluate(*TtBarRapidityStability_, TtBarRapidityRecGenCounters_,    TtBarRapidityGenCounters_ );
  evaluate(*TtBarPhiStability_,	     TtBarPhiRecGenCounters_,         TtBarPhiGenCounters_      );
  evaluate(*TtBarPtStability_,	     TtBarPtRecGenCounters_,          TtBarPtGenCounters_       );  
  evaluate(*TtBarMassStability_,     TtBarMassRecGenCounters_,        TtBarMassGenCounters_     );  
}

void
FullLepPurityAnalyzer::initiateCounter(const std::vector<double>& bins, std::vector<int>& c1, std::vector<int>& c2, std::vector<int>& c3)
{
  for(size_t i=0;i<bins.size()-1;++i){
    c1.push_back(0);
    c2.push_back(0);    
    c3.push_back(0);    
  }
}

void 
FullLepPurityAnalyzer::countRecGen(const double& rec, const double& gen, std::vector<double>& bins, std::vector<int>& counters)
{
  for(size_t i=0; i<bins.size()-1; ++i){
    if( (rec > bins[i] && rec < bins[i+1]) &&  (gen > bins[i] && gen < bins[i+1]) ){
      counters[i]++;    
    }
  }
}


void 
FullLepPurityAnalyzer::countRec(const double& rec, std::vector<double>& bins, std::vector<int>& counters)
{
  for(size_t i=0; i<bins.size()-1; ++i){
    if(rec > bins[i] && rec < bins[i+1]){
      counters[i]++;    
    }
  }
}


void 
FullLepPurityAnalyzer::countGen(const double& gen, std::vector<double>& bins, std::vector<int>& counters)
{
  for(size_t i=0; i<bins.size()-1; ++i){
    if(gen > bins[i] && gen < bins[i+1]){
      counters[i]++;    
    }
  }
}

void 
FullLepPurityAnalyzer::evaluate(TH1D& hist, std::vector<int>& nominators , std::vector<int>& denominators)
{
  for(size_t i=0; i<denominators.size(); ++i){
    // purity and stability can only be calculated if denominator > 0 
    if(denominators[i] == 0) continue;    
    // purity/stability value
    double v = (double)nominators[i]/(double)denominators[i];
    // purity/stability error
    double e = sqrt( (v*(1-v)) / denominators[i]); 
    
    hist.SetBinContent(i+1,v);
    hist.SetBinError  (i+1,e);    
  }
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( FullLepPurityAnalyzer );
