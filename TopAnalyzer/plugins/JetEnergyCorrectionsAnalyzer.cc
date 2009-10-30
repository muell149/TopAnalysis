#include "TopAnalysis/TopAnalyzer/plugins/JetEnergyCorrectionsAnalyzer.h"

#include "DataFormats/JetReco/interface/Jet.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "AnalysisDataFormats/TopObjects/interface/TtSemiLepEvtPartons.h"
#include "AnalysisDataFormats/TopObjects/interface/TtSemiLeptonicEvent.h"

/// default constructor
JetEnergyCorrectionsAnalyzer::JetEnergyCorrectionsAnalyzer(const edm::ParameterSet& cfg) :
  semiLepEvt_    (cfg.getParameter<edm::InputTag>("semiLepEvt"    )),
  hypoKey_       (cfg.getParameter<std::string  >("hypoKey"       )),
  genJets_       (cfg.getParameter<edm::InputTag>("genJets"       )),
  genJetMatching_(cfg.getParameter<edm::InputTag>("genJetMatching"))
{ 
}

/// histogramm booking
void JetEnergyCorrectionsAnalyzer::beginJob(const edm::EventSetup&)
{
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  double binningLogPt[15] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
			     120, 150, 200, 250, 300};

  hists_["mW"  ] = fs->make<TH1F>("mW"  , "mW"  , 28, 0., 140.);
  hists_["mTop"] = fs->make<TH1F>("mTop", "mTop", 60, 0., 300.);

  hists_["mW_Pt1" ] = fs->make<TH2F>("mW_Pt1" , "mW_Pt1" , 14, binningLogPt, 41, 0., 160.);
  hists_["mW_Pt2" ] = fs->make<TH2F>("mW_Pt2" , "mW_Pt2" , 14, binningLogPt, 41, 0., 160.);
  hists_["mW_PtW" ] = fs->make<TH2F>("mW_PtW" , "mW_PtW" , 14, binningLogPt, 41, 0., 160.);
  hists_["mW_Eta1"] = fs->make<TH2F>("mW_Eta1", "mW_Eta1", 30, -3., 3.     , 41, 0., 160.);
  hists_["mW_Eta2"] = fs->make<TH2F>("mW_Eta2", "mW_Eta2", 30, -3., 3.     , 41, 0., 160.);
  hists_["mW_EtaW"] = fs->make<TH2F>("mW_EtaW", "mW_EtaW", 30, -3., 3.     , 41, 0., 160.);

  hists_["mTop_Pt1"   ] = fs->make<TH2F>("mTop_Pt1"   , "mTop_Pt1"   , 14, binningLogPt, 51, 0., 350.);
  hists_["mTop_Pt2"   ] = fs->make<TH2F>("mTop_Pt2"   , "mTop_Pt2"   , 14, binningLogPt, 51, 0., 350.);
  hists_["mTop_PtB"   ] = fs->make<TH2F>("mTop_PtB"   , "mTop_PtB"   , 14, binningLogPt, 51, 0., 350.);
  hists_["mTop_PtTop" ] = fs->make<TH2F>("mTop_PtTop" , "mTop_PtTop" , 14, binningLogPt, 51, 0., 350.);
  hists_["mTop_Eta1"  ] = fs->make<TH2F>("mTop_Eta1"  , "mTop_Eta1"  , 30, -3., 3.     , 51, 0., 350.);
  hists_["mTop_Eta2"  ] = fs->make<TH2F>("mTop_Eta2"  , "mTop_Eta2"  , 30, -3., 3.     , 51, 0., 350.);
  hists_["mTop_EtaB"  ] = fs->make<TH2F>("mTop_EtaB"  , "mTop_EtaB"  , 30, -3., 3.     , 51, 0., 350.);
  hists_["mTop_EtaTop"] = fs->make<TH2F>("mTop_EtaTop", "mTop_EtaTop", 30, -3., 3.     , 51, 0., 350.);

  hists_["mW_barrel"  ] = fs->make<TH1F>("mW_barrel"  , "mW_barrel"  , 28, 0., 140.);
  hists_["mTop_barrel"] = fs->make<TH1F>("mTop_barrel", "mTop_barrel", 60, 0., 300.);

  hists_["deltaM_PtB" ] = fs->make<TH2F>("deltaM_PtB" , "deltaM_PtB" , 14, binningLogPt, 41, 0., 180.);
  hists_["deltaM_EtaB"] = fs->make<TH2F>("deltaM_EtaB", "deltaM_EtaB", 30, -3., 3.     , 41, 0., 180.);

  // response light jets

  hists_["responseLGenJetPtGenJet"       ] = fs->make<TH2F>("responseLGenJetPtGenJet",
							    "responseLGenJetPtGenJet",
							    14, binningLogPt, 51, 0., 2.);

  hists_["responseLGenJetPtGenJet_barrel"] = fs->make<TH2F>("responseLGenJetPtGenJet_barrel",
							    "responseLGenJetPtGenJet_barrel",
							    14, binningLogPt, 51, 0., 2.);

  hists_["responseLGenJetEta"            ] = fs->make<TH2F>("responseLGenJetEta",
							    "responseLGenJetEta",
							    30, -3., 3. , 51, 0., 2.);

  hists_["responseLPartonPtParton"       ] = fs->make<TH2F>("responseLPartonPtParton",
							    "responseLPartonPtParton",
							    14, binningLogPt, 51, 0., 2.);

  hists_["responseLPartonPtParton_barrel"] = fs->make<TH2F>("responseLPartonPtParton_barrel",
							    "responseLPartonPtParton_barrel",
							    14, binningLogPt, 51, 0., 2.);

  hists_["responseLPartonEta"            ] = fs->make<TH2F>("responseLPartonEta",
							    "responseLPartonEta",
							    30, -3., 3. , 51, 0., 2.);

  // response b jets

  hists_["responseBGenJetPtGenJet"       ] = fs->make<TH2F>("responseBGenJetPtGenJet",
							    "responseBGenJetPtGenJet",
							    14, binningLogPt, 51, 0., 2.);

  hists_["responseBGenJetPtGenJet_barrel"] = fs->make<TH2F>("responseBGenJetPtGenJet_barrel",
							    "responseBGenJetPtGenJet_barrel",
							    14, binningLogPt, 51, 0., 2.);

  hists_["responseBGenJetEta"            ] = fs->make<TH2F>("responseBGenJetEta",
							    "responseBGenJetEta",
							    30, -3., 3. , 51, 0., 2.);

  hists_["responseBPartonPtParton"       ] = fs->make<TH2F>("responseBPartonPtParton",
							    "responseBPartonPtParton",
							    14, binningLogPt, 51, 0., 2.);

  hists_["responseBPartonPtParton_barrel"] = fs->make<TH2F>("responseBPartonPtParton_barrel",
							    "responseBPartonPtParton_barrel",
							    14, binningLogPt, 51, 0., 2.);

  hists_["responseBPartonEta"            ] = fs->make<TH2F>("responseBPartonEta",
							    "responseBPartonEta",
							    30, -3., 3. , 51, 0., 2.);

  hists_["pdgIdLJet"] = fs->make<TH1F>("pdgIdLJet", "pdgIdLJet", 25, 0., 25.);
  hists_["pdgIdBJet"] = fs->make<TH1F>("pdgIdBJet", "pdgIdBJet", 25, 0., 25.);

  hists_["ptJetUDS"] = fs->make<TH1F>("ptJetUDS", "ptJetUDS", 60, 0., 300.);
  hists_["ptJetC"  ] = fs->make<TH1F>("ptJetC"  , "ptJetC"  , 60, 0., 300.);
  hists_["ptJetB"  ] = fs->make<TH1F>("ptJetB"  , "ptJetB"  , 60, 0., 300.);
  hists_["ptJetG"  ] = fs->make<TH1F>("ptJetG"  , "ptJetG"  , 60, 0., 300.);

}

/// histogram filling
void
JetEnergyCorrectionsAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& setup)
{
  // get ttSemiLeptonicEvent
  edm::Handle<TtSemiLeptonicEvent> semiLepEvt;
  event.getByLabel(semiLepEvt_, semiLepEvt);

  // check if event hypothesis is valid
  if( !semiLepEvt->isHypoValid(hypoKey_) )
    return;

  // invariant mass of W and top

  const reco::Candidate* jet1 = semiLepEvt->hadronicDecayQuark   (hypoKey_);
  const reco::Candidate* jet2 = semiLepEvt->hadronicDecayQuarkBar(hypoKey_);
  const reco::Candidate* jetB = semiLepEvt->hadronicDecayB       (hypoKey_);

  if(jet1->pt() < jet2->pt()) {
    jet1 = semiLepEvt->hadronicDecayQuarkBar(hypoKey_);
    jet2 = semiLepEvt->hadronicDecayQuark   (hypoKey_);    
  }

  double mW   = semiLepEvt->hadronicDecayW  (hypoKey_)->mass();
  double mTop = semiLepEvt->hadronicDecayTop(hypoKey_)->mass();

  hists_.find("mW"  )->second->Fill( mW   );
  hists_.find("mTop")->second->Fill( mTop );

  hists_.find("mW_Pt1")->second->Fill( jet1->pt(), mW );
  hists_.find("mW_Pt2")->second->Fill( jet2->pt(), mW );
  hists_.find("mW_PtW")->second->Fill( semiLepEvt->hadronicDecayW(hypoKey_)->pt(), mW );

  hists_.find("mW_Eta1")->second->Fill( jet1->eta(), mW );
  hists_.find("mW_Eta2")->second->Fill( jet2->eta(), mW );
  hists_.find("mW_EtaW")->second->Fill( semiLepEvt->hadronicDecayW(hypoKey_)->eta(), mW );

  hists_.find("mTop_Pt1"  )->second->Fill( jet1->pt(), mTop );
  hists_.find("mTop_Pt2"  )->second->Fill( jet2->pt(), mTop );
  hists_.find("mTop_PtB"  )->second->Fill( jetB->pt(), mTop );
  hists_.find("mTop_PtTop")->second->Fill( semiLepEvt->hadronicDecayTop(hypoKey_)->pt(), mTop );

  hists_.find("mTop_Eta1")->second->Fill( jet1->eta(), mTop );
  hists_.find("mTop_Eta2")->second->Fill( jet2->eta(), mTop );
  hists_.find("mTop_EtaB")->second->Fill( jetB->eta(), mTop );
  hists_.find("mTop_EtaTop")->second->Fill( semiLepEvt->hadronicDecayTop(hypoKey_)->eta(), mTop );

  double deltaM = mTop - mW;

  hists_.find("deltaM_PtB" )->second->Fill( jetB->pt() , deltaM );
  hists_.find("deltaM_EtaB")->second->Fill( jetB->eta(), deltaM );

  // in the barrel only

  if( std::abs(semiLepEvt->hadronicDecayQuark   (hypoKey_)->eta()) < 1.3 &&
      std::abs(semiLepEvt->hadronicDecayQuarkBar(hypoKey_)->eta()) < 1.3 ) {

    hists_.find("mW_barrel")->second->Fill( semiLepEvt->hadronicDecayW(hypoKey_)->mass() );

    if( std::abs(semiLepEvt->hadronicDecayB(hypoKey_)->eta()) < 1.3 ) {
      hists_.find("mTop_barrel")->second->Fill( semiLepEvt->hadronicDecayTop(hypoKey_)->mass() );
    }

  }

  ////////////////////////////////////////////////////////////////////////////////////////
  // do the rest only in case of the GenMatch hypothesis
  ////////////////////////////////////////////////////////////////////////////////////////
  if(hypoKey_ != "kGenMatch")
    return;

  // quarks from W

  hists_.find("pdgIdLJet")->second->Fill( abs(semiLepEvt->hadronicDecayQuark()   ->pdgId()) );
  hists_.find("pdgIdLJet")->second->Fill( abs(semiLepEvt->hadronicDecayQuarkBar()->pdgId()) );

  analyzeFlavorComposition(*semiLepEvt->hadronicDecayQuark(hypoKey_),
			   *semiLepEvt->hadronicDecayQuark());
  analyzeFlavorComposition(*semiLepEvt->hadronicDecayQuarkBar(hypoKey_),
			   *semiLepEvt->hadronicDecayQuarkBar());

  // b quarks

  hists_.find("pdgIdBJet")->second->Fill( abs(semiLepEvt->hadronicDecayB()->pdgId()) );

  analyzeFlavorComposition(*semiLepEvt->hadronicDecayB(hypoKey_),
			   *semiLepEvt->hadronicDecayB());

  // get genJets
  edm::Handle<edm::View<reco::Jet> > genJets;
  event.getByLabel(genJets_, genJets);

  // get genJet matching
  edm::Handle< std::vector< std::vector<int> > > genJetMatchingHandle;
  event.getByLabel(genJetMatching_, genJetMatchingHandle);
  std::vector<int> genJetMatching = *(genJetMatchingHandle->begin());

  // outlier rejection w.r.t. genJet-parton matching
  for(unsigned int i=0; i<genJetMatching.size(); i++)
    if(genJetMatching[i] < 0 && genJetMatching[i] != -3)
      return;

  const reco::Jet genJetLightQ    = (*genJets)[genJetMatching[TtSemiLepEvtPartons::LightQ   ]];
  const reco::Jet genJetLightQBar = (*genJets)[genJetMatching[TtSemiLepEvtPartons::LightQBar]];
  const reco::Jet genJetHadronicB = (*genJets)[genJetMatching[TtSemiLepEvtPartons::HadB     ]];
  const reco::Jet genJetLeptonicB = (*genJets)[genJetMatching[TtSemiLepEvtPartons::LepB     ]];

  analyzeLightJetResponse( *semiLepEvt->hadronicDecayQuark(hypoKey_), genJetLightQ,
			   *semiLepEvt->hadronicDecayQuark() );
			  
  analyzeLightJetResponse( *semiLepEvt->hadronicDecayQuarkBar(hypoKey_), genJetLightQBar,
			   *semiLepEvt->hadronicDecayQuarkBar() );

  analyzeBJetResponse( *semiLepEvt->hadronicDecayB(hypoKey_), genJetHadronicB,
		       *semiLepEvt->hadronicDecayB() );

  analyzeBJetResponse( *semiLepEvt->leptonicDecayB(hypoKey_), genJetLeptonicB,
		       *semiLepEvt->leptonicDecayB() );

}

/// fill histograms related to the response of light jets
void
JetEnergyCorrectionsAnalyzer::analyzeLightJetResponse(const reco::Candidate& recJet,
						      const reco::Candidate& genJet,
						      const reco::GenParticle& parton)
{

  // genJet response

  double response = recJet.pt() / genJet.pt();

  hists_.find("responseLGenJetPtGenJet")->second->Fill( genJet.pt() , response );
  hists_.find("responseLGenJetEta"     )->second->Fill( genJet.eta(), response );

  if( std::abs(genJet.eta()) < 1.3 )
    hists_.find("responseLGenJetPtGenJet_barrel")->second->Fill( genJet.pt(), response );

  // parton response

  response = recJet.pt() / parton.pt();

  hists_.find("responseLPartonPtParton")->second->Fill( parton.pt() , response );
  hists_.find("responseLPartonEta"     )->second->Fill( parton.eta(), response );
  
  if( std::abs(parton.eta()) < 1.3 )
    hists_.find("responseLPartonPtParton_barrel")->second->Fill( parton.pt(), response );

}

/// fill histograms related to the response of b jets
void
JetEnergyCorrectionsAnalyzer::analyzeBJetResponse(const reco::Candidate& recJet,
						  const reco::Candidate& genJet,
						  const reco::GenParticle& parton)
{

  // genJet response

  double response = recJet.pt() / genJet.pt();

  hists_.find("responseBGenJetPtGenJet")->second->Fill( genJet.pt() , response );
  hists_.find("responseBGenJetEta"     )->second->Fill( genJet.eta(), response );

  if( std::abs(genJet.eta()) < 1.3 )
    hists_.find("responseBGenJetPtGenJet_barrel")->second->Fill( genJet.pt(), response );

  // parton response

  response = recJet.pt() / parton.pt();

  hists_.find("responseBPartonPtParton")->second->Fill( parton.pt() , response );
  hists_.find("responseBPartonEta"     )->second->Fill( parton.eta(), response );
  
  if( std::abs(parton.eta()) < 1.3 )
    hists_.find("responseBPartonPtParton_barrel")->second->Fill( parton.pt(), response );

}

/// fill pdgId specific histograms
void
JetEnergyCorrectionsAnalyzer::analyzeFlavorComposition(const reco::Candidate& jet, const reco::GenParticle& parton)
{

  // uds
  if( abs(parton.pdgId()) >= 1 && abs(parton.pdgId()) <= 3 )
    hists_.find("ptJetUDS")->second->Fill( jet.pt() );
  // c
  else if( abs(parton.pdgId()) == 4 )
    hists_.find("ptJetC"  )->second->Fill( jet.pt() );
  // b
  else if( abs(parton.pdgId()) == 5 )
    hists_.find("ptJetB"  )->second->Fill( jet.pt() );
  // gluon
  else if( abs(parton.pdgId()) == 21 )
    hists_.find("ptJetG"  )->second->Fill( jet.pt() );

}

void
JetEnergyCorrectionsAnalyzer::endJob() 
{
}
