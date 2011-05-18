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
  
  jetPairEtaBins_      ( cfg.getParameter<std::vector<double> >( "jetPairEtaBins"      ) ),
  jetPairRapidityBins_ ( cfg.getParameter<std::vector<double> >( "jetPairRapidityBins" ) ),
  jetPairPhiBins_      ( cfg.getParameter<std::vector<double> >( "jetPairPhiBins"      ) ),
  jetPairPtBins_       ( cfg.getParameter<std::vector<double> >( "jetPairPtBins"       ) ),
  jetPairMassBins_     ( cfg.getParameter<std::vector<double> >( "jetPairMassBins"     ) ),        
  
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
  
  
  NameScheme nsRecGen("RecGen");
  lepEtaRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "lepEta" ),      "#eta(l^{-})",  lepEtaBins_.size()-1,      &lepEtaBins_.front()      );
  lepRapidityRecGenCounters_  = fs->make<TH1D>(nsRecGen.name( "lepRapidity" ), "y(l^{-})",     lepRapidityBins_.size()-1, &lepRapidityBins_.front() );
  lepPhiRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "lepPhi" ),      "#phi(l^{-})",  lepPhiBins_.size()-1,      &lepPhiBins_.front()      );
  lepPtRecGenCounters_        = fs->make<TH1D>(nsRecGen.name( "lepPt" ),       "p_{T}(l^{-})", lepPtBins_.size()-1,       &lepPtBins_.front()       );
  
  lepBarEtaRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "lepBarEta" ),      "#eta(l^{+})",  lepBarEtaBins_.size()-1,      &lepBarEtaBins_.front()      );
  lepBarRapidityRecGenCounters_  = fs->make<TH1D>(nsRecGen.name( "lepBarRapidity" ), "y(l^{+})",     lepBarRapidityBins_.size()-1, &lepBarRapidityBins_.front() );
  lepBarPhiRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "lepBarPhi" ),      "#phi(l^{+})",  lepBarPhiBins_.size()-1,      &lepBarPhiBins_.front()      );
  lepBarPtRecGenCounters_        = fs->make<TH1D>(nsRecGen.name( "lepBarPt" ),       "p_{T}(l^{+})", lepBarPtBins_.size()-1,       &lepBarPtBins_.front()       );

  lepPairEtaRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "lepPairEta" ),      "#eta(l^{+}l^{-})",  lepPairEtaBins_.size()-1,      &lepPairEtaBins_.front()      );
  lepPairRapidityRecGenCounters_  = fs->make<TH1D>(nsRecGen.name( "lepPairRapidity" ), "y(l^{+}l^{-})",     lepPairRapidityBins_.size()-1, &lepPairRapidityBins_.front() );
  lepPairPhiRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "lepPairPhi" ),      "#phi(l^{+}l^{-})",  lepPairPhiBins_.size()-1,      &lepPairPhiBins_.front()      );
  lepPairPtRecGenCounters_        = fs->make<TH1D>(nsRecGen.name( "lepPairPt" ),       "p_{T}(l^{+}l^{-})", lepPairPtBins_.size()-1,       &lepPairPtBins_.front()       );  
  lepPairMassRecGenCounters_      = fs->make<TH1D>(nsRecGen.name( "lepPairMass" ),     "M(l^{+}l^{-})",     lepPairMassBins_.size()-1,     &lepPairMassBins_.front()     ); 
  
  bEtaRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "bEta" ),      "#eta(b)",  bEtaBins_.size()-1,      &bEtaBins_.front()      );
  bRapidityRecGenCounters_  = fs->make<TH1D>(nsRecGen.name( "bRapidity" ), "y(b)",     bRapidityBins_.size()-1, &bRapidityBins_.front() );
  bPhiRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "bPhi" ),      "#phi(b)",  bPhiBins_.size()-1,      &bPhiBins_.front()      );
  bPtRecGenCounters_        = fs->make<TH1D>(nsRecGen.name( "bPt" ),       "p_{T}(b)", bPtBins_.size()-1,       &bPtBins_.front()       );
  
  bBarEtaRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "bBarEta" ),      "#eta(#bar{b})",  bBarEtaBins_.size()-1,      &bBarEtaBins_.front()      );
  bBarRapidityRecGenCounters_  = fs->make<TH1D>(nsRecGen.name( "bBarRapidity" ), "y(#bar{b})",     bBarRapidityBins_.size()-1, &bBarRapidityBins_.front() );
  bBarPhiRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "bBarPhi" ),      "#phi(#bar{b})",  bBarPhiBins_.size()-1,      &bBarPhiBins_.front()      );
  bBarPtRecGenCounters_        = fs->make<TH1D>(nsRecGen.name( "bBarPt" ),       "p_{T}(#bar{b})", bBarPtBins_.size()-1,       &bBarPtBins_.front()       );  
  
  jetPairEtaRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "jetPairEta" ),      "#eta(jj)",  jetPairEtaBins_.size()-1,      &jetPairEtaBins_.front()      );
  jetPairRapidityRecGenCounters_  = fs->make<TH1D>(nsRecGen.name( "jetPairRapidity" ), "y(jj)",     jetPairRapidityBins_.size()-1, &jetPairRapidityBins_.front() );
  jetPairPhiRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "jetPairPhi" ),      "#phi(jj)",  jetPairPhiBins_.size()-1,      &jetPairPhiBins_.front()      );
  jetPairPtRecGenCounters_        = fs->make<TH1D>(nsRecGen.name( "jetPairPt" ),       "p_{T}(jj)", jetPairPtBins_.size()-1,       &jetPairPtBins_.front()       );  
  jetPairMassRecGenCounters_      = fs->make<TH1D>(nsRecGen.name( "jetPairMass" ),     "M(jj)",     jetPairMassBins_.size()-1,     &jetPairMassBins_.front()     );   

  topEtaRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "topEta" ),      "#eta(t)",  topEtaBins_.size()-1,      &topEtaBins_.front()      );
  topRapidityRecGenCounters_  = fs->make<TH1D>(nsRecGen.name( "topRapidity" ), "y(t)",     topRapidityBins_.size()-1, &topRapidityBins_.front() );
  topPhiRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "topPhi" ),      "#phi(t)",  topPhiBins_.size()-1,      &topPhiBins_.front()      );
  topPtRecGenCounters_        = fs->make<TH1D>(nsRecGen.name( "topPt" ),       "p_{T}(t)", topPtBins_.size()-1,       &topPtBins_.front()       );
  
  topBarEtaRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "topBarEta" ),      "#eta(#bar{t})",  topBarEtaBins_.size()-1,      &topBarEtaBins_.front()      );
  topBarRapidityRecGenCounters_  = fs->make<TH1D>(nsRecGen.name( "topBarRapidity" ), "y(#bar{t})",     topBarRapidityBins_.size()-1, &topBarRapidityBins_.front() );
  topBarPhiRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "topBarPhi" ),      "#phi(#bar{t})",  topBarPhiBins_.size()-1,      &topBarPhiBins_.front()      );
  topBarPtRecGenCounters_        = fs->make<TH1D>(nsRecGen.name( "topBarPt" ),       "p_{T}(#bar{t})", topBarPtBins_.size()-1,       &topBarPtBins_.front()       );
  
  TtBarEtaRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "TtBarEta" ),      "#eta(t#bar{t})",  TtBarEtaBins_.size()-1,      &TtBarEtaBins_.front()      );
  TtBarRapidityRecGenCounters_  = fs->make<TH1D>(nsRecGen.name( "TtBarRapidity" ), "y(t#bar{t})",     TtBarRapidityBins_.size()-1, &TtBarRapidityBins_.front() );
  TtBarPhiRecGenCounters_       = fs->make<TH1D>(nsRecGen.name( "TtBarPhi" ),      "#phi(t#bar{t})",  TtBarPhiBins_.size()-1,      &TtBarPhiBins_.front()      );
  TtBarPtRecGenCounters_        = fs->make<TH1D>(nsRecGen.name( "TtBarPt" ),       "p_{T}(t#bar{t})", TtBarPtBins_.size()-1,       &TtBarPtBins_.front()       );  
  TtBarMassRecGenCounters_      = fs->make<TH1D>(nsRecGen.name( "TtBarMass" ),     "M(t#bar{t})",     TtBarMassBins_.size()-1,     &TtBarMassBins_.front()     ); 

  
  NameScheme nsRec("Rec");
  lepEtaRecCounters_       = fs->make<TH1D>(nsRec.name( "lepEta" ),      "#eta(l^{-})",  lepEtaBins_.size()-1,      &lepEtaBins_.front()      );
  lepRapidityRecCounters_  = fs->make<TH1D>(nsRec.name( "lepRapidity" ), "y(l^{-})",     lepRapidityBins_.size()-1, &lepRapidityBins_.front() );
  lepPhiRecCounters_       = fs->make<TH1D>(nsRec.name( "lepPhi" ),      "#phi(l^{-})",  lepPhiBins_.size()-1,      &lepPhiBins_.front()      );
  lepPtRecCounters_        = fs->make<TH1D>(nsRec.name( "lepPt" ),       "p_{T}(l^{-})", lepPtBins_.size()-1,       &lepPtBins_.front()       );
  
  lepBarEtaRecCounters_       = fs->make<TH1D>(nsRec.name( "lepBarEta" ),      "#eta(l^{+})",  lepBarEtaBins_.size()-1,      &lepBarEtaBins_.front()      );
  lepBarRapidityRecCounters_  = fs->make<TH1D>(nsRec.name( "lepBarRapidity" ), "y(l^{+})",     lepBarRapidityBins_.size()-1, &lepBarRapidityBins_.front() );
  lepBarPhiRecCounters_       = fs->make<TH1D>(nsRec.name( "lepBarPhi" ),      "#phi(l^{+})",  lepBarPhiBins_.size()-1,      &lepBarPhiBins_.front()      );
  lepBarPtRecCounters_        = fs->make<TH1D>(nsRec.name( "lepBarPt" ),       "p_{T}(l^{+})", lepBarPtBins_.size()-1,       &lepBarPtBins_.front()       );

  lepPairEtaRecCounters_       = fs->make<TH1D>(nsRec.name( "lepPairEta" ),      "#eta(l^{+}l^{-})",  lepPairEtaBins_.size()-1,      &lepPairEtaBins_.front()      );
  lepPairRapidityRecCounters_  = fs->make<TH1D>(nsRec.name( "lepPairRapidity" ), "y(l^{+}l^{-})",     lepPairRapidityBins_.size()-1, &lepPairRapidityBins_.front() );
  lepPairPhiRecCounters_       = fs->make<TH1D>(nsRec.name( "lepPairPhi" ),      "#phi(l^{+}l^{-})",  lepPairPhiBins_.size()-1,      &lepPairPhiBins_.front()      );
  lepPairPtRecCounters_        = fs->make<TH1D>(nsRec.name( "lepPairPt" ),       "p_{T}(l^{+}l^{-})", lepPairPtBins_.size()-1,       &lepPairPtBins_.front()       );  
  lepPairMassRecCounters_      = fs->make<TH1D>(nsRec.name( "lepPairMass" ),     "M(l^{+}l^{-})",     lepPairMassBins_.size()-1,     &lepPairMassBins_.front()     ); 
  
  bEtaRecCounters_       = fs->make<TH1D>(nsRec.name( "bEta" ),      "#eta(b)",  bEtaBins_.size()-1,      &bEtaBins_.front()      );
  bRapidityRecCounters_  = fs->make<TH1D>(nsRec.name( "bRapidity" ), "y(b)",     bRapidityBins_.size()-1, &bRapidityBins_.front() );
  bPhiRecCounters_       = fs->make<TH1D>(nsRec.name( "bPhi" ),      "#phi(b)",  bPhiBins_.size()-1,      &bPhiBins_.front()      );
  bPtRecCounters_        = fs->make<TH1D>(nsRec.name( "bPt" ),       "p_{T}(b)", bPtBins_.size()-1,       &bPtBins_.front()       );
  
  bBarEtaRecCounters_       = fs->make<TH1D>(nsRec.name( "bBarEta" ),      "#eta(#bar{b})",  bBarEtaBins_.size()-1,      &bBarEtaBins_.front()      );
  bBarRapidityRecCounters_  = fs->make<TH1D>(nsRec.name( "bBarRapidity" ), "y(#bar{b})",     bBarRapidityBins_.size()-1, &bBarRapidityBins_.front() );
  bBarPhiRecCounters_       = fs->make<TH1D>(nsRec.name( "bBarPhi" ),      "#phi(#bar{b})",  bBarPhiBins_.size()-1,      &bBarPhiBins_.front()      );
  bBarPtRecCounters_        = fs->make<TH1D>(nsRec.name( "bBarPt" ),       "p_{T}(#bar{b})", bBarPtBins_.size()-1,       &bBarPtBins_.front()       );
  
  jetPairEtaRecCounters_       = fs->make<TH1D>(nsRec.name( "jetPairEta" ),      "#eta(jj)",  jetPairEtaBins_.size()-1,      &jetPairEtaBins_.front()      );
  jetPairRapidityRecCounters_  = fs->make<TH1D>(nsRec.name( "jetPairRapidity" ), "y(jj)",     jetPairRapidityBins_.size()-1, &jetPairRapidityBins_.front() );
  jetPairPhiRecCounters_       = fs->make<TH1D>(nsRec.name( "jetPairPhi" ),      "#phi(jj)",  jetPairPhiBins_.size()-1,      &jetPairPhiBins_.front()      );
  jetPairPtRecCounters_        = fs->make<TH1D>(nsRec.name( "jetPairPt" ),       "p_{T}(jj)", jetPairPtBins_.size()-1,       &jetPairPtBins_.front()       );  
  jetPairMassRecCounters_      = fs->make<TH1D>(nsRec.name( "jetPairMass" ),     "M(jj)",     jetPairMassBins_.size()-1,     &jetPairMassBins_.front()     );    

  topEtaRecCounters_       = fs->make<TH1D>(nsRec.name( "topEta" ),      "#eta(t)",  topEtaBins_.size()-1,      &topEtaBins_.front()      );
  topRapidityRecCounters_  = fs->make<TH1D>(nsRec.name( "topRapidity" ), "y(t)",     topRapidityBins_.size()-1, &topRapidityBins_.front() );
  topPhiRecCounters_       = fs->make<TH1D>(nsRec.name( "topPhi" ),      "#phi(t)",  topPhiBins_.size()-1,      &topPhiBins_.front()      );
  topPtRecCounters_        = fs->make<TH1D>(nsRec.name( "topPt" ),       "p_{T}(t)", topPtBins_.size()-1,       &topPtBins_.front()       );
  
  topBarEtaRecCounters_       = fs->make<TH1D>(nsRec.name( "topBarEta" ),      "#eta(#bar{t})",  topBarEtaBins_.size()-1,      &topBarEtaBins_.front()      );
  topBarRapidityRecCounters_  = fs->make<TH1D>(nsRec.name( "topBarRapidity" ), "y(#bar{t})",     topBarRapidityBins_.size()-1, &topBarRapidityBins_.front() );
  topBarPhiRecCounters_       = fs->make<TH1D>(nsRec.name( "topBarPhi" ),      "#phi(#bar{t})",  topBarPhiBins_.size()-1,      &topBarPhiBins_.front()      );
  topBarPtRecCounters_        = fs->make<TH1D>(nsRec.name( "topBarPt" ),       "p_{T}(#bar{t})", topBarPtBins_.size()-1,       &topBarPtBins_.front()       );
  
  TtBarEtaRecCounters_       = fs->make<TH1D>(nsRec.name( "TtBarEta" ),      "#eta(t#bar{t})",  TtBarEtaBins_.size()-1,      &TtBarEtaBins_.front()      );
  TtBarRapidityRecCounters_  = fs->make<TH1D>(nsRec.name( "TtBarRapidity" ), "y(t#bar{t})",     TtBarRapidityBins_.size()-1, &TtBarRapidityBins_.front() );
  TtBarPhiRecCounters_       = fs->make<TH1D>(nsRec.name( "TtBarPhi" ),      "#phi(t#bar{t})",  TtBarPhiBins_.size()-1,      &TtBarPhiBins_.front()      );
  TtBarPtRecCounters_        = fs->make<TH1D>(nsRec.name( "TtBarPt" ),       "p_{T}(t#bar{t})", TtBarPtBins_.size()-1,       &TtBarPtBins_.front()       );  
  TtBarMassRecCounters_      = fs->make<TH1D>(nsRec.name( "TtBarMass" ),     "M(t#bar{t})",     TtBarMassBins_.size()-1,     &TtBarMassBins_.front()     ); 
  
  
  NameScheme nsGen("Gen");
  lepEtaGenCounters_       = fs->make<TH1D>(nsGen.name( "lepEta" ),      "#eta(l^{-})",  lepEtaBins_.size()-1,      &lepEtaBins_.front()      );
  lepRapidityGenCounters_  = fs->make<TH1D>(nsGen.name( "lepRapidity" ), "y(l^{-})",     lepRapidityBins_.size()-1, &lepRapidityBins_.front() );
  lepPhiGenCounters_       = fs->make<TH1D>(nsGen.name( "lepPhi" ),      "#phi(l^{-})",  lepPhiBins_.size()-1,      &lepPhiBins_.front()      );
  lepPtGenCounters_        = fs->make<TH1D>(nsGen.name( "lepPt" ),       "p_{T}(l^{-})", lepPtBins_.size()-1,       &lepPtBins_.front()       );
  
  lepBarEtaGenCounters_       = fs->make<TH1D>(nsGen.name( "lepBarEta" ),      "#eta(l^{+})",  lepBarEtaBins_.size()-1,      &lepBarEtaBins_.front()      );
  lepBarRapidityGenCounters_  = fs->make<TH1D>(nsGen.name( "lepBarRapidity" ), "y(l^{+})",     lepBarRapidityBins_.size()-1, &lepBarRapidityBins_.front() );
  lepBarPhiGenCounters_       = fs->make<TH1D>(nsGen.name( "lepBarPhi" ),      "#phi(l^{+})",  lepBarPhiBins_.size()-1,      &lepBarPhiBins_.front()      );
  lepBarPtGenCounters_        = fs->make<TH1D>(nsGen.name( "lepBarPt" ),       "p_{T}(l^{+})", lepBarPtBins_.size()-1,       &lepBarPtBins_.front()       );

  lepPairEtaGenCounters_       = fs->make<TH1D>(nsGen.name( "lepPairEta" ),      "#eta(l^{+}l^{-})",  lepPairEtaBins_.size()-1,      &lepPairEtaBins_.front()      );
  lepPairRapidityGenCounters_  = fs->make<TH1D>(nsGen.name( "lepPairRapidity" ), "y(l^{+}l^{-})",     lepPairRapidityBins_.size()-1, &lepPairRapidityBins_.front() );
  lepPairPhiGenCounters_       = fs->make<TH1D>(nsGen.name( "lepPairPhi" ),      "#phi(l^{+}l^{-})",  lepPairPhiBins_.size()-1,      &lepPairPhiBins_.front()      );
  lepPairPtGenCounters_        = fs->make<TH1D>(nsGen.name( "lepPairPt" ),       "p_{T}(l^{+}l^{-})", lepPairPtBins_.size()-1,       &lepPairPtBins_.front()       );  
  lepPairMassGenCounters_      = fs->make<TH1D>(nsGen.name( "lepPairMass" ),     "M(l^{+}l^{-})",     lepPairMassBins_.size()-1,     &lepPairMassBins_.front()     ); 
  
  bEtaGenCounters_       = fs->make<TH1D>(nsGen.name( "bEta" ),      "#eta(b)",  bEtaBins_.size()-1,      &bEtaBins_.front()      );
  bRapidityGenCounters_  = fs->make<TH1D>(nsGen.name( "bRapidity" ), "y(b)",     bRapidityBins_.size()-1, &bRapidityBins_.front() );
  bPhiGenCounters_       = fs->make<TH1D>(nsGen.name( "bPhi" ),      "#phi(b)",  bPhiBins_.size()-1,      &bPhiBins_.front()      );
  bPtGenCounters_        = fs->make<TH1D>(nsGen.name( "bPt" ),       "p_{T}(b)", bPtBins_.size()-1,       &bPtBins_.front()       );
  
  bBarEtaGenCounters_       = fs->make<TH1D>(nsGen.name( "bBarEta" ),      "#eta(#bar{b})",  bBarEtaBins_.size()-1,      &bBarEtaBins_.front()      );
  bBarRapidityGenCounters_  = fs->make<TH1D>(nsGen.name( "bBarRapidity" ), "y(#bar{b})",     bBarRapidityBins_.size()-1, &bBarRapidityBins_.front() );
  bBarPhiGenCounters_       = fs->make<TH1D>(nsGen.name( "bBarPhi" ),      "#phi(#bar{b})",  bBarPhiBins_.size()-1,      &bBarPhiBins_.front()      );
  bBarPtGenCounters_        = fs->make<TH1D>(nsGen.name( "bBarPt" ),       "p_{T}(#bar{b})", bBarPtBins_.size()-1,       &bBarPtBins_.front()       );
  
  jetPairEtaGenCounters_       = fs->make<TH1D>(nsGen.name( "jetPairEta" ),      "#eta(jj)",  jetPairEtaBins_.size()-1,      &jetPairEtaBins_.front()      );
  jetPairRapidityGenCounters_  = fs->make<TH1D>(nsGen.name( "jetPairRapidity" ), "y(jj)",     jetPairRapidityBins_.size()-1, &jetPairRapidityBins_.front() );
  jetPairPhiGenCounters_       = fs->make<TH1D>(nsGen.name( "jetPairPhi" ),      "#phi(jj)",  jetPairPhiBins_.size()-1,      &jetPairPhiBins_.front()      );
  jetPairPtGenCounters_        = fs->make<TH1D>(nsGen.name( "jetPairPt" ),       "p_{T}(jj)", jetPairPtBins_.size()-1,       &jetPairPtBins_.front()       );  
  jetPairMassGenCounters_      = fs->make<TH1D>(nsGen.name( "jetPairMass" ),     "M(jj)",     jetPairMassBins_.size()-1,     &jetPairMassBins_.front()     );    

  topEtaGenCounters_       = fs->make<TH1D>(nsGen.name( "topEta" ),      "#eta(t)",  topEtaBins_.size()-1,      &topEtaBins_.front()      );
  topRapidityGenCounters_  = fs->make<TH1D>(nsGen.name( "topRapidity" ), "y(t)",     topRapidityBins_.size()-1, &topRapidityBins_.front() );
  topPhiGenCounters_       = fs->make<TH1D>(nsGen.name( "topPhi" ),      "#phi(t)",  topPhiBins_.size()-1,      &topPhiBins_.front()      );
  topPtGenCounters_        = fs->make<TH1D>(nsGen.name( "topPt" ),       "p_{T}(t)", topPtBins_.size()-1,       &topPtBins_.front()       );
  
  topBarEtaGenCounters_       = fs->make<TH1D>(nsGen.name( "topBarEta" ),      "#eta(#bar{t})",  topBarEtaBins_.size()-1,      &topBarEtaBins_.front()      );
  topBarRapidityGenCounters_  = fs->make<TH1D>(nsGen.name( "topBarRapidity" ), "y(#bar{t})",     topBarRapidityBins_.size()-1, &topBarRapidityBins_.front() );
  topBarPhiGenCounters_       = fs->make<TH1D>(nsGen.name( "topBarPhi" ),      "#phi(#bar{t})",  topBarPhiBins_.size()-1,      &topBarPhiBins_.front()      );
  topBarPtGenCounters_        = fs->make<TH1D>(nsGen.name( "topBarPt" ),       "p_{T}(#bar{t})", topBarPtBins_.size()-1,       &topBarPtBins_.front()       );
  
  TtBarEtaGenCounters_       = fs->make<TH1D>(nsGen.name( "TtBarEta" ),      "#eta(t#bar{t})",  TtBarEtaBins_.size()-1,      &TtBarEtaBins_.front()      );
  TtBarRapidityGenCounters_  = fs->make<TH1D>(nsGen.name( "TtBarRapidity" ), "y(t#bar{t})",     TtBarRapidityBins_.size()-1, &TtBarRapidityBins_.front() );
  TtBarPhiGenCounters_       = fs->make<TH1D>(nsGen.name( "TtBarPhi" ),      "#phi(t#bar{t})",  TtBarPhiBins_.size()-1,      &TtBarPhiBins_.front()      );
  TtBarPtGenCounters_        = fs->make<TH1D>(nsGen.name( "TtBarPt" ),       "p_{T}(t#bar{t})", TtBarPtBins_.size()-1,       &TtBarPtBins_.front()       );  
  TtBarMassGenCounters_      = fs->make<TH1D>(nsGen.name( "TtBarMass" ),     "M(t#bar{t})",     TtBarMassBins_.size()-1,     &TtBarMassBins_.front()     );   
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
  
  // combined jet pair object 
  reco::CompositeCandidate* jetPair = new reco::CompositeCandidate();
  jetPair->addDaughter(*b);
  jetPair->addDaughter(*bBar);  
  addFourMomenta.set(*jetPair);  
  
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
  
  // combined jet pair object 
  reco::CompositeCandidate* genJetPair = new reco::CompositeCandidate();
  genJetPair->addDaughter(*genB);
  genJetPair->addDaughter(*genBBar);
  addFourMomenta.set(*genJetPair);  

  // count events where given quantity is generated AND reconstructed inside a certain bin
  countRecGen(lep->eta(),      genLep->eta(),	   *lepEtaRecGenCounters_      );
  countRecGen(lep->rapidity(), genLep->rapidity(), *lepRapidityRecGenCounters_ );
  countRecGen(lep->phi(),      genLep->phi(),	   *lepPhiRecGenCounters_      );
  countRecGen(lep->pt(),       genLep->pt(),	   *lepPtRecGenCounters_       );

  countRecGen(lepBar->eta(),	  genLepBar->eta(),	 *lepBarEtaRecGenCounters_	);
  countRecGen(lepBar->rapidity(), genLepBar->rapidity(), *lepBarRapidityRecGenCounters_ );
  countRecGen(lepBar->phi(),	  genLepBar->phi(),	 *lepBarPhiRecGenCounters_	);
  countRecGen(lepBar->pt(),	  genLepBar->pt(),	 *lepBarPtRecGenCounters_	);
  
  countRecGen(lepPair->eta(),      genLepPair->eta(),      *lepPairEtaRecGenCounters_	   );
  countRecGen(lepPair->rapidity(), genLepPair->rapidity(), *lepPairRapidityRecGenCounters_ );
  countRecGen(lepPair->phi(),      genLepPair->phi(),      *lepPairPhiRecGenCounters_	   );
  countRecGen(lepPair->pt(),       genLepPair->pt(),       *lepPairPtRecGenCounters_	   );  
  countRecGen(lepPair->mass(),     genLepPair->mass(),     *lepPairMassRecGenCounters_     );	

  countRecGen(b->eta(),      genB->eta(),      *bEtaRecGenCounters_	 );
  countRecGen(b->rapidity(), genB->rapidity(), *bRapidityRecGenCounters_ );
  countRecGen(b->phi(),      genB->phi(),      *bPhiRecGenCounters_	 );
  countRecGen(b->pt(),       genB->pt(),       *bPtRecGenCounters_	 );
  
  countRecGen(bBar->eta(),	genBBar->eta(),      *bBarEtaRecGenCounters_	  );
  countRecGen(bBar->rapidity(), genBBar->rapidity(), *bBarRapidityRecGenCounters_ );
  countRecGen(bBar->phi(),	genBBar->phi(),      *bBarPhiRecGenCounters_	  );
  countRecGen(bBar->pt(),	genBBar->pt(),       *bBarPtRecGenCounters_	  );
  
  countRecGen(jetPair->eta(),      genJetPair->eta(),      *jetPairEtaRecGenCounters_	   );
  countRecGen(jetPair->rapidity(), genJetPair->rapidity(), *jetPairRapidityRecGenCounters_ );
  countRecGen(jetPair->phi(),      genJetPair->phi(),      *jetPairPhiRecGenCounters_	   );
  countRecGen(jetPair->pt(),       genJetPair->pt(),       *jetPairPtRecGenCounters_	   );  
  countRecGen(jetPair->mass(),     genJetPair->mass(),     *jetPairMassRecGenCounters_     );	  
  
  countRecGen(top->eta(),      genTop->eta(),	   *topEtaRecGenCounters_      );
  countRecGen(top->rapidity(), genTop->rapidity(), *topRapidityRecGenCounters_ );
  countRecGen(top->phi(),      genTop->phi(),	   *topPhiRecGenCounters_      );
  countRecGen(top->pt(),       genTop->pt(),	   *topPtRecGenCounters_       );
  
  countRecGen(topBar->eta(),	  genTopBar->eta(),	 *topBarEtaRecGenCounters_	);
  countRecGen(topBar->rapidity(), genTopBar->rapidity(), *topBarRapidityRecGenCounters_ );
  countRecGen(topBar->phi(),	  genTopBar->phi(),	 *topBarPhiRecGenCounters_	);
  countRecGen(topBar->pt(),	  genTopBar->pt(),	 *topBarPtRecGenCounters_	);  
  
  countRecGen(TtBar->eta(),	 genTtBar->eta(),      *TtBarEtaRecGenCounters_      );
  countRecGen(TtBar->rapidity(), genTtBar->rapidity(), *TtBarRapidityRecGenCounters_ );
  countRecGen(TtBar->phi(),	 genTtBar->phi(),      *TtBarPhiRecGenCounters_      );
  countRecGen(TtBar->pt(),	 genTtBar->pt(),       *TtBarPtRecGenCounters_       );  
  countRecGen(TtBar->mass(),	 genTtBar->mass(),     *TtBarMassRecGenCounters_     );    


  // count events where given quantity is reconstructed inside a certain bin    
  lepEtaRecCounters_     ->Fill(lep->eta()     );
  lepRapidityRecCounters_->Fill(lep->rapidity());
  lepPhiRecCounters_     ->Fill(lep->phi()     );
  lepPtRecCounters_      ->Fill(lep->pt()      );
  
  lepBarEtaRecCounters_     ->Fill(lepBar->eta()     );
  lepBarRapidityRecCounters_->Fill(lepBar->rapidity());
  lepBarPhiRecCounters_     ->Fill(lepBar->phi()     );
  lepBarPtRecCounters_      ->Fill(lepBar->pt()      );
  
  lepPairEtaRecCounters_     ->Fill(lepPair->eta()     );
  lepPairRapidityRecCounters_->Fill(lepPair->rapidity());
  lepPairPhiRecCounters_     ->Fill(lepPair->phi()     );
  lepPairPtRecCounters_      ->Fill(lepPair->pt()      ); 
  lepPairMassRecCounters_    ->Fill(lepPair->mass()    );    

  bEtaRecCounters_     ->Fill(b->eta()     );
  bRapidityRecCounters_->Fill(b->rapidity());
  bPhiRecCounters_     ->Fill(b->phi()     );
  bPtRecCounters_      ->Fill(b->pt()      );
  
  bBarEtaRecCounters_     ->Fill(bBar->eta()     );
  bBarRapidityRecCounters_->Fill(bBar->rapidity());
  bBarPhiRecCounters_     ->Fill(bBar->phi()     );
  bBarPtRecCounters_      ->Fill(bBar->pt()      );
  
  jetPairEtaRecCounters_     ->Fill(jetPair->eta()     );
  jetPairRapidityRecCounters_->Fill(jetPair->rapidity());
  jetPairPhiRecCounters_     ->Fill(jetPair->phi()     );
  jetPairPtRecCounters_      ->Fill(jetPair->pt()      ); 
  jetPairMassRecCounters_    ->Fill(jetPair->mass()    );    
    
  topEtaRecCounters_     ->Fill(top->eta()     );
  topRapidityRecCounters_->Fill(top->rapidity());
  topPhiRecCounters_     ->Fill(top->phi()     );
  topPtRecCounters_      ->Fill(top->pt()      );
  
  topBarEtaRecCounters_     ->Fill(topBar->eta()     );
  topBarRapidityRecCounters_->Fill(topBar->rapidity());
  topBarPhiRecCounters_     ->Fill(topBar->phi()     );
  topBarPtRecCounters_      ->Fill(topBar->pt()      ); 
  
  TtBarEtaRecCounters_     ->Fill(TtBar->eta()     );
  TtBarRapidityRecCounters_->Fill(TtBar->rapidity());
  TtBarPhiRecCounters_     ->Fill(TtBar->phi()     );
  TtBarPtRecCounters_      ->Fill(TtBar->pt()      );
  TtBarMassRecCounters_    ->Fill(TtBar->mass()    );


  // count events where given quantity is generated inside a certain bin    
  lepEtaGenCounters_     ->Fill(genLep->eta()     );
  lepRapidityGenCounters_->Fill(genLep->rapidity());
  lepPhiGenCounters_     ->Fill(genLep->phi()     );
  lepPtGenCounters_      ->Fill(genLep->pt()      );
  
  lepBarEtaGenCounters_     ->Fill(genLepBar->eta()     );
  lepBarRapidityGenCounters_->Fill(genLepBar->rapidity());
  lepBarPhiGenCounters_     ->Fill(genLepBar->phi()     );
  lepBarPtGenCounters_      ->Fill(genLepBar->pt()      );
  
  lepPairEtaGenCounters_     ->Fill(genLepPair->eta()     );
  lepPairRapidityGenCounters_->Fill(genLepPair->rapidity());
  lepPairPhiGenCounters_     ->Fill(genLepPair->phi()     );
  lepPairPtGenCounters_      ->Fill(genLepPair->pt()      ); 
  lepPairMassGenCounters_    ->Fill(genLepPair->mass()    );    

  bEtaGenCounters_     ->Fill(genB->eta()     );
  bRapidityGenCounters_->Fill(genB->rapidity());
  bPhiGenCounters_     ->Fill(genB->phi()     );
  bPtGenCounters_      ->Fill(genB->pt()      );
  
  bBarEtaGenCounters_     ->Fill(genBBar->eta()     );
  bBarRapidityGenCounters_->Fill(genBBar->rapidity());
  bBarPhiGenCounters_     ->Fill(genBBar->phi()     );
  bBarPtGenCounters_      ->Fill(genBBar->pt()      );
  
  jetPairEtaGenCounters_     ->Fill(genJetPair->eta()     );
  jetPairRapidityGenCounters_->Fill(genJetPair->rapidity());
  jetPairPhiGenCounters_     ->Fill(genJetPair->phi()     );
  jetPairPtGenCounters_      ->Fill(genJetPair->pt()      ); 
  jetPairMassGenCounters_    ->Fill(genJetPair->mass()    );     
  
  topEtaGenCounters_     ->Fill(genTop->eta()     );
  topRapidityGenCounters_->Fill(genTop->rapidity());
  topPhiGenCounters_     ->Fill(genTop->phi()     );
  topPtGenCounters_      ->Fill(genTop->pt()      );
  
  topBarEtaGenCounters_     ->Fill(genTopBar->eta()     );
  topBarRapidityGenCounters_->Fill(genTopBar->rapidity());
  topBarPhiGenCounters_     ->Fill(genTopBar->phi()     );
  topBarPtGenCounters_      ->Fill(genTopBar->pt()      ); 
  
  TtBarEtaGenCounters_     ->Fill(genTtBar->eta()     );
  TtBarRapidityGenCounters_->Fill(genTtBar->rapidity());
  TtBarPhiGenCounters_     ->Fill(genTtBar->phi()     );
  TtBarPtGenCounters_      ->Fill(genTtBar->pt()      );
  TtBarMassGenCounters_    ->Fill(genTtBar->mass()    );
}


/// everything that has to be done after the event loop
void
FullLepPurityAnalyzer::endJob() 
{
}


void 
FullLepPurityAnalyzer::countRecGen(const double& rec, const double& gen, TH1D& hist)
{
  for(int i=1; i<=hist.GetXaxis()->GetNbins(); ++i){
    if( (rec > hist.GetXaxis()->GetBinLowEdge(i) && rec < hist.GetXaxis()->GetBinUpEdge(i) ) 
     &&  (gen > hist.GetXaxis()->GetBinLowEdge(i) && gen < hist.GetXaxis()->GetBinUpEdge(i) ) ){
      hist.Fill(rec);    
    }
  }
}


#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( FullLepPurityAnalyzer );
