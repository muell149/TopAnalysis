#include "TopAnalysis/TopAnalyzer/plugins/JetEnergyResolutionBiasAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"

/// default constructor
JetEnergyResolutionBiasAnalyzer::JetEnergyResolutionBiasAnalyzer(const edm::ParameterSet& cfg):
  etaCut_ (cfg.getParameter<double>("etaCut" )),
  resFact_(cfg.getParameter<double>("resFact")),
  resParS_(cfg.getParameter<double>("resParS")),
  resParN_(cfg.getParameter<double>("resParN")),
  resParC_(cfg.getParameter<double>("resParC"))
{ 
}

/// histogramm booking
void JetEnergyResolutionBiasAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  if( !fs ) throw edm::Exception( edm::errors::Configuration, "TFile Service is not registered in cfg file" );

  double binningLogPt[14] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
			     120, 150, 200, 250};

  hists_["eta"] = fs->make<TH1F>("eta", "eta", 50, -2.5, 2.5);

  hists_["ptL"     ] = fs->make<TH1F>("ptL"     , "ptL"     , 50,  0., 250.);
  hists_["ptLSmear"] = fs->make<TH1F>("ptLSmear", "ptLSmear", 50,  0., 250.);
  hists_["ptB"     ] = fs->make<TH1F>("ptB"     , "ptB"     , 50,  0., 250.);
  hists_["ptBSmear"] = fs->make<TH1F>("ptBSmear", "ptBSmear", 50,  0., 250.);
  hists_["enL"     ] = fs->make<TH1F>("enL"     , "enL"     , 50,  0., 250.);
  hists_["enLSmear"] = fs->make<TH1F>("enLSmear", "enLSmear", 50,  0., 250.);
  hists_["enB"     ] = fs->make<TH1F>("enB"     , "enB"     , 50,  0., 250.);
  hists_["enBSmear"] = fs->make<TH1F>("enBSmear", "enBSmear", 50,  0., 250.);

  hists_.find("ptL"     )->second->StatOverflows(kTRUE);
  hists_.find("ptLSmear")->second->StatOverflows(kTRUE);
  hists_.find("ptB"     )->second->StatOverflows(kTRUE);
  hists_.find("ptBSmear")->second->StatOverflows(kTRUE);
  hists_.find("enL"     )->second->StatOverflows(kTRUE);
  hists_.find("enLSmear")->second->StatOverflows(kTRUE);
  hists_.find("enB"     )->second->StatOverflows(kTRUE);
  hists_.find("enBSmear")->second->StatOverflows(kTRUE);

  hists_["theta"] = fs->make<TH1F>("theta", "theta", 21, 0., 3.15);

  hists_["enSmearVsGen"] = fs->make<TH2F>("enSmearVsGen", "enSmearVsGen",
					  50, 0., 250., 51, 0., 2.);

  hists_["respL_0" ] = fs->make<TH1F>("respL_0" , "respL_0" , 201, 0., 2.);
  hists_["respL_10"] = fs->make<TH1F>("respL_10", "respL_10", 201, 0., 2.);
  hists_["respL_20"] = fs->make<TH1F>("respL_20", "respL_20", 201, 0., 2.);
  hists_["respL_30"] = fs->make<TH1F>("respL_30", "respL_30", 201, 0., 2.);
  hists_["respL_40"] = fs->make<TH1F>("respL_40", "respL_40", 201, 0., 2.);
  hists_["respL_50"] = fs->make<TH1F>("respL_50", "respL_50", 201, 0., 2.);

  hists_["respLPt_0" ] = fs->make<TH2F>("respLPt_0" , "respLPt_0" , 13, binningLogPt, 201, 0., 2.);
  hists_["respLPt_10"] = fs->make<TH2F>("respLPt_10", "respLPt_10", 13, binningLogPt, 201, 0., 2.);
  hists_["respLPt_20"] = fs->make<TH2F>("respLPt_20", "respLPt_20", 13, binningLogPt, 201, 0., 2.);
  hists_["respLPt_30"] = fs->make<TH2F>("respLPt_30", "respLPt_30", 13, binningLogPt, 201, 0., 2.);
  hists_["respLPt_40"] = fs->make<TH2F>("respLPt_40", "respLPt_40", 13, binningLogPt, 201, 0., 2.);
  hists_["respLPt_50"] = fs->make<TH2F>("respLPt_50", "respLPt_50", 13, binningLogPt, 201, 0., 2.);

  hists_["respLPtSmear_0" ] = fs->make<TH2F>("respLPtSmear_0" , "respLPtSmear_0" , 13, binningLogPt, 201, 0., 2.);
  hists_["respLPtSmear_10"] = fs->make<TH2F>("respLPtSmear_10", "respLPtSmear_10", 13, binningLogPt, 201, 0., 2.);
  hists_["respLPtSmear_20"] = fs->make<TH2F>("respLPtSmear_20", "respLPtSmear_20", 13, binningLogPt, 201, 0., 2.);
  hists_["respLPtSmear_30"] = fs->make<TH2F>("respLPtSmear_30", "respLPtSmear_30", 13, binningLogPt, 201, 0., 2.);
  hists_["respLPtSmear_40"] = fs->make<TH2F>("respLPtSmear_40", "respLPtSmear_40", 13, binningLogPt, 201, 0., 2.);
  hists_["respLPtSmear_50"] = fs->make<TH2F>("respLPtSmear_50", "respLPtSmear_50", 13, binningLogPt, 201, 0., 2.);

  hists_["respB_0" ] = fs->make<TH1F>("respB_0" , "respB_0" , 201, 0., 2.);
  hists_["respB_10"] = fs->make<TH1F>("respB_10", "respB_10", 201, 0., 2.);
  hists_["respB_20"] = fs->make<TH1F>("respB_20", "respB_20", 201, 0., 2.);
  hists_["respB_30"] = fs->make<TH1F>("respB_30", "respB_30", 201, 0., 2.);
  hists_["respB_40"] = fs->make<TH1F>("respB_40", "respB_40", 201, 0., 2.);
  hists_["respB_50"] = fs->make<TH1F>("respB_50", "respB_50", 201, 0., 2.);

  hists_["respBPt_0" ] = fs->make<TH2F>("respBPt_0" , "respBPt_0" , 13, binningLogPt, 201, 0., 2.);
  hists_["respBPt_10"] = fs->make<TH2F>("respBPt_10", "respBPt_10", 13, binningLogPt, 201, 0., 2.);
  hists_["respBPt_20"] = fs->make<TH2F>("respBPt_20", "respBPt_20", 13, binningLogPt, 201, 0., 2.);
  hists_["respBPt_30"] = fs->make<TH2F>("respBPt_30", "respBPt_30", 13, binningLogPt, 201, 0., 2.);
  hists_["respBPt_40"] = fs->make<TH2F>("respBPt_40", "respBPt_40", 13, binningLogPt, 201, 0., 2.);
  hists_["respBPt_50"] = fs->make<TH2F>("respBPt_50", "respBPt_50", 13, binningLogPt, 201, 0., 2.);

  hists_["respBPtSmear_0" ] = fs->make<TH2F>("respBPtSmear_0" , "respBPtSmear_0" , 13, binningLogPt, 201, 0., 2.);
  hists_["respBPtSmear_10"] = fs->make<TH2F>("respBPtSmear_10", "respBPtSmear_10", 13, binningLogPt, 201, 0., 2.);
  hists_["respBPtSmear_20"] = fs->make<TH2F>("respBPtSmear_20", "respBPtSmear_20", 13, binningLogPt, 201, 0., 2.);
  hists_["respBPtSmear_30"] = fs->make<TH2F>("respBPtSmear_30", "respBPtSmear_30", 13, binningLogPt, 201, 0., 2.);
  hists_["respBPtSmear_40"] = fs->make<TH2F>("respBPtSmear_40", "respBPtSmear_40", 13, binningLogPt, 201, 0., 2.);
  hists_["respBPtSmear_50"] = fs->make<TH2F>("respBPtSmear_50", "respBPtSmear_50", 13, binningLogPt, 201, 0., 2.);

  hists_["massW_0" ] = fs->make<TH1F>("massW_0 ", "massW_0 ", 140, 0., 140.);
  hists_["massW_10"] = fs->make<TH1F>("massW_10", "massW_10", 140, 0., 140.);
  hists_["massW_20"] = fs->make<TH1F>("massW_20", "massW_20", 140, 0., 140.);
  hists_["massW_30"] = fs->make<TH1F>("massW_30", "massW_30", 140, 0., 140.);
  hists_["massW_40"] = fs->make<TH1F>("massW_40", "massW_40", 140, 0., 140.);
  hists_["massW_50"] = fs->make<TH1F>("massW_50", "massW_50", 140, 0., 140.);

  hists_["massWzoom_0" ] = fs->make<TH1F>("massWzoom_0 ", "massWzoom_0 ", 80, 60., 100.);
  hists_["massWzoom_10"] = fs->make<TH1F>("massWzoom_10", "massWzoom_10", 80, 60., 100.);
  hists_["massWzoom_20"] = fs->make<TH1F>("massWzoom_20", "massWzoom_20", 80, 60., 100.);
  hists_["massWzoom_30"] = fs->make<TH1F>("massWzoom_30", "massWzoom_30", 80, 60., 100.);
  hists_["massWzoom_40"] = fs->make<TH1F>("massWzoom_40", "massWzoom_40", 80, 60., 100.);
  hists_["massWzoom_50"] = fs->make<TH1F>("massWzoom_50", "massWzoom_50", 80, 60., 100.);

  hists_["massWPt_0" ] = fs->make<TH2F>("massWPt_0 ", "massWPt_0 ", 13, binningLogPt, 140, 0., 140.);
  hists_["massWPt_10"] = fs->make<TH2F>("massWPt_10", "massWPt_10", 13, binningLogPt, 140, 0., 140.);
  hists_["massWPt_20"] = fs->make<TH2F>("massWPt_20", "massWPt_20", 13, binningLogPt, 140, 0., 140.);
  hists_["massWPt_30"] = fs->make<TH2F>("massWPt_30", "massWPt_30", 13, binningLogPt, 140, 0., 140.);
  hists_["massWPt_40"] = fs->make<TH2F>("massWPt_40", "massWPt_40", 13, binningLogPt, 140, 0., 140.);
  hists_["massWPt_50"] = fs->make<TH2F>("massWPt_50", "massWPt_50", 13, binningLogPt, 140, 0., 140.);

  hists_["massWPtSmear_0" ] = fs->make<TH2F>("massWPtSmear_0 ", "massWPtSmear_0 ", 13, binningLogPt, 140, 0., 140.);
  hists_["massWPtSmear_10"] = fs->make<TH2F>("massWPtSmear_10", "massWPtSmear_10", 13, binningLogPt, 140, 0., 140.);
  hists_["massWPtSmear_20"] = fs->make<TH2F>("massWPtSmear_20", "massWPtSmear_20", 13, binningLogPt, 140, 0., 140.);
  hists_["massWPtSmear_30"] = fs->make<TH2F>("massWPtSmear_30", "massWPtSmear_30", 13, binningLogPt, 140, 0., 140.);
  hists_["massWPtSmear_40"] = fs->make<TH2F>("massWPtSmear_40", "massWPtSmear_40", 13, binningLogPt, 140, 0., 140.);
  hists_["massWPtSmear_50"] = fs->make<TH2F>("massWPtSmear_50", "massWPtSmear_50", 13, binningLogPt, 140, 0., 140.);

  hists_["massT_0" ] = fs->make<TH1F>("massT_0 ", "massT_0 ", 300, 0., 300.);
  hists_["massT_10"] = fs->make<TH1F>("massT_10", "massT_10", 300, 0., 300.);
  hists_["massT_20"] = fs->make<TH1F>("massT_20", "massT_20", 300, 0., 300.);
  hists_["massT_30"] = fs->make<TH1F>("massT_30", "massT_30", 300, 0., 300.);
  hists_["massT_40"] = fs->make<TH1F>("massT_40", "massT_40", 300, 0., 300.);
  hists_["massT_50"] = fs->make<TH1F>("massT_50", "massT_50", 300, 0., 300.);

  hists_["massTzoom_0" ] = fs->make<TH1F>("massTzoom_0 ", "massTzoom_0 ", 200, 150., 200.);
  hists_["massTzoom_10"] = fs->make<TH1F>("massTzoom_10", "massTzoom_10", 200, 150., 200.);
  hists_["massTzoom_20"] = fs->make<TH1F>("massTzoom_20", "massTzoom_20", 200, 150., 200.);
  hists_["massTzoom_30"] = fs->make<TH1F>("massTzoom_30", "massTzoom_30", 200, 150., 200.);
  hists_["massTzoom_40"] = fs->make<TH1F>("massTzoom_40", "massTzoom_40", 200, 150., 200.);
  hists_["massTzoom_50"] = fs->make<TH1F>("massTzoom_50", "massTzoom_50", 200, 150., 200.);

  hists_["massTPt_0" ] = fs->make<TH2F>("massTPt_0 ", "massTPt_0 ", 13, binningLogPt, 300, 0., 300.);
  hists_["massTPt_10"] = fs->make<TH2F>("massTPt_10", "massTPt_10", 13, binningLogPt, 300, 0., 300.);
  hists_["massTPt_20"] = fs->make<TH2F>("massTPt_20", "massTPt_20", 13, binningLogPt, 300, 0., 300.);
  hists_["massTPt_30"] = fs->make<TH2F>("massTPt_30", "massTPt_30", 13, binningLogPt, 300, 0., 300.);
  hists_["massTPt_40"] = fs->make<TH2F>("massTPt_40", "massTPt_40", 13, binningLogPt, 300, 0., 300.);
  hists_["massTPt_50"] = fs->make<TH2F>("massTPt_50", "massTPt_50", 13, binningLogPt, 300, 0., 300.);

  hists_["massTPtZoom_0" ] = fs->make<TH2F>("massTPtZoom_0 ", "massTPtZoom_0 ", 13, binningLogPt, 200, 150., 200.);
  hists_["massTPtZoom_10"] = fs->make<TH2F>("massTPtZoom_10", "massTPtZoom_10", 13, binningLogPt, 200, 150., 200.);
  hists_["massTPtZoom_20"] = fs->make<TH2F>("massTPtZoom_20", "massTPtZoom_20", 13, binningLogPt, 200, 150., 200.);
  hists_["massTPtZoom_30"] = fs->make<TH2F>("massTPtZoom_30", "massTPtZoom_30", 13, binningLogPt, 200, 150., 200.);
  hists_["massTPtZoom_40"] = fs->make<TH2F>("massTPtZoom_40", "massTPtZoom_40", 13, binningLogPt, 200, 150., 200.);
  hists_["massTPtZoom_50"] = fs->make<TH2F>("massTPtZoom_50", "massTPtZoom_50", 13, binningLogPt, 200, 150., 200.);

  hists_["massTPtSmear_0" ] = fs->make<TH2F>("massTPtSmear_0 ", "massTPtSmear_0 ", 13, binningLogPt, 300, 0., 300.);
  hists_["massTPtSmear_10"] = fs->make<TH2F>("massTPtSmear_10", "massTPtSmear_10", 13, binningLogPt, 300, 0., 300.);
  hists_["massTPtSmear_20"] = fs->make<TH2F>("massTPtSmear_20", "massTPtSmear_20", 13, binningLogPt, 300, 0., 300.);
  hists_["massTPtSmear_30"] = fs->make<TH2F>("massTPtSmear_30", "massTPtSmear_30", 13, binningLogPt, 300, 0., 300.);
  hists_["massTPtSmear_40"] = fs->make<TH2F>("massTPtSmear_40", "massTPtSmear_40", 13, binningLogPt, 300, 0., 300.);
  hists_["massTPtSmear_50"] = fs->make<TH2F>("massTPtSmear_50", "massTPtSmear_50", 13, binningLogPt, 300, 0., 300.);

  hists_["massTPtSmearZoom_0" ] = fs->make<TH2F>("massTPtSmearZoom_0 ", "massTPtSmearZoom_0 ", 13, binningLogPt, 200, 150., 200.);
  hists_["massTPtSmearZoom_10"] = fs->make<TH2F>("massTPtSmearZoom_10", "massTPtSmearZoom_10", 13, binningLogPt, 200, 150., 200.);
  hists_["massTPtSmearZoom_20"] = fs->make<TH2F>("massTPtSmearZoom_20", "massTPtSmearZoom_20", 13, binningLogPt, 200, 150., 200.);
  hists_["massTPtSmearZoom_30"] = fs->make<TH2F>("massTPtSmearZoom_30", "massTPtSmearZoom_30", 13, binningLogPt, 200, 150., 200.);
  hists_["massTPtSmearZoom_40"] = fs->make<TH2F>("massTPtSmearZoom_40", "massTPtSmearZoom_40", 13, binningLogPt, 200, 150., 200.);
  hists_["massTPtSmearZoom_50"] = fs->make<TH2F>("massTPtSmearZoom_50", "massTPtSmearZoom_50", 13, binningLogPt, 200, 150., 200.);

  hists_["respLEta"] = fs->make<TH2F>("respLEta", "respLEta", 12, -2.4, 2.4, 201, 0., 2.);
  hists_["respBEta"] = fs->make<TH2F>("respBEta", "respBEta", 12, -2.4, 2.4, 201, 0., 2.);
  hists_["massWEta"] = fs->make<TH2F>("massWEta", "massWEta", 12, -2.4, 2.4, 140, 0., 140.);
  hists_["massTEta"] = fs->make<TH2F>("massTEta", "massTEta", 12, -2.4, 2.4, 300, 0., 300.);
  hists_["massTEtaZoom"] = fs->make<TH2F>("massTEtaZoom", "massTEtaZoom", 12, -2.4, 2.4, 200, 150., 200.);

  std::string name = "massWPt1SmearPt2Smear";
  hists3d_[name] = fs->make<TH3F>(name.c_str(), name.c_str(), 50, 0., 250., 50, 0., 250., 28, 0., 140.);
  name = "massWE1SmearE2Smear";
  hists3d_[name] = fs->make<TH3F>(name.c_str(), name.c_str(), 50, 0., 250., 50, 0., 250., 28, 0., 140.);
  name = "ptWPt1SmearPt2Smear";
  hists3d_[name] = fs->make<TH3F>(name.c_str(), name.c_str(), 50, 0., 250., 50, 0., 250., 28, 0., 140.);
  name = "ptWE1SmearE2Smear";
  hists3d_[name] = fs->make<TH3F>(name.c_str(), name.c_str(), 50, 0., 250., 50, 0., 250., 28, 0., 140.);

  randNumGen_ = new TRandom3(0);
}

/// histogram filling
void
JetEnergyResolutionBiasAnalyzer::analyze(const edm::Event& event, const edm::EventSetup& setup)
{

  edm::Handle<TtGenEvent> genEvent;
  event.getByLabel("genEvt", genEvent);

  if( !genEvent->isSemiLeptonic() )
    return;

  const reco::GenParticle* hadB = genEvent->hadronicDecayB();
  const reco::GenParticle* hadP = genEvent->hadronicDecayQuark();
  const reco::GenParticle* hadQ = genEvent->hadronicDecayQuarkBar();

  if( !hadB || !hadP || !hadQ )
    return;

  if( fabs(hadB->eta()) > etaCut_ ||
      fabs(hadP->eta()) > etaCut_ ||
      fabs(hadQ->eta()) > etaCut_ ) return;

  TLorentzVector vecB(hadB->px(), hadB->py(), hadB->pz(), hadB->energy());
  TLorentzVector vecP(hadP->px(), hadP->py(), hadP->pz(), hadP->energy());
  TLorentzVector vecQ(hadQ->px(), hadQ->py(), hadQ->pz(), hadQ->energy());

  hists_.find("eta")->second->Fill( vecB.Eta() );
  hists_.find("eta")->second->Fill( vecP.Eta() );
  hists_.find("eta")->second->Fill( vecQ.Eta() );

  hists_.find("ptB")->second->Fill( vecB.Pt() );
  hists_.find("ptL")->second->Fill( vecP.Pt() );
  hists_.find("ptL")->second->Fill( vecQ.Pt() );

  hists_.find("enB")->second->Fill( vecB.E() );
  hists_.find("enL")->second->Fill( vecP.E() );
  hists_.find("enL")->second->Fill( vecQ.E() );

  hists_.find("theta")->second->Fill( vecP.Angle(vecQ.Vect()) );

  smearEnergy(vecB);
  smearEnergy(vecP);
  smearEnergy(vecQ);

  hists_.find("ptBSmear")->second->Fill( vecB.Pt() );
  hists_.find("ptLSmear")->second->Fill( vecP.Pt() );
  hists_.find("ptLSmear")->second->Fill( vecQ.Pt() );

  hists_.find("enBSmear")->second->Fill( vecB.E() );
  hists_.find("enLSmear")->second->Fill( vecP.E() );
  hists_.find("enLSmear")->second->Fill( vecQ.E() );

  hists_.find("enSmearVsGen")->second->Fill( hadB->energy(), vecB.Energy() / hadB->energy() );
  hists_.find("enSmearVsGen")->second->Fill( hadP->energy(), vecP.Energy() / hadP->energy() );
  hists_.find("enSmearVsGen")->second->Fill( hadQ->energy(), vecQ.Energy() / hadQ->energy() );

  TLorentzVector vecW = vecP + vecQ;
  TLorentzVector vecT = vecB + vecW;

//  std::cout << "======================================" << std::endl;
//  std::cout << "mqq  = " << vecW.M() << std::endl;
//  std::cout << "mW   = " << genEvent->hadronicDecayW()  ->mass() << std::endl;
//  std::cout << "mqqb = " << vecT.M() << std::endl;
//  std::cout << "mtop = " << genEvent->hadronicDecayTop()->mass() << std::endl;
//  std::cout << "======================================" << std::endl;

  for(Long_t ptcut = 0; ptcut <= 50; ptcut += 10) {

    if( vecB.Pt() < ptcut ) continue;
    if( vecP.Pt() < ptcut ) continue;
    if( vecQ.Pt() < ptcut ) continue;

    // fill light response plots

    TString name = "respL_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecP.Pt() / hadP->pt() );
    hists_.find((std::string)name)->second->Fill( vecQ.Pt() / hadQ->pt() );

    name = "respLPt_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( hadP->pt(), vecP.Pt() / hadP->pt() );
    hists_.find((std::string)name)->second->Fill( hadQ->pt(), vecQ.Pt() / hadQ->pt() );

    name = "respLPtSmear_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecP.Pt(), vecP.Pt() / hadP->pt() );
    hists_.find((std::string)name)->second->Fill( vecQ.Pt(), vecQ.Pt() / hadQ->pt() );

    // fill b response plots

    name = "respB_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecB.Pt() / hadB->pt() );

    name = "respBPt_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( hadB->pt(), vecB.Pt() / hadB->pt() );

    name = "respBPtSmear_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecB.Pt(), vecB.Pt() / hadB->pt() );

    // fill W mass plots

    name = "massW_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecW.M() );

    name = "massWzoom_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecW.M() );

    name = "massWPt_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( hadP->pt(), vecW.M() );
    hists_.find((std::string)name)->second->Fill( hadQ->pt(), vecW.M() );

    name = "massWPtSmear_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecP.Pt(), vecW.M() );
    hists_.find((std::string)name)->second->Fill( vecQ.Pt(), vecW.M() );

    hists3d_.find("massWPt1SmearPt2Smear")->second->Fill( vecP.Pt(), vecQ.Pt(), vecW.M()  );
    hists3d_.find("massWE1SmearE2Smear"  )->second->Fill( vecP.E() , vecQ.E() , vecW.M()  );
    hists3d_.find("ptWPt1SmearPt2Smear"  )->second->Fill( vecP.Pt(), vecQ.Pt(), vecW.Pt() );
    hists3d_.find("ptWE1SmearE2Smear"    )->second->Fill( vecP.E() , vecQ.E() , vecW.Pt() );

    // fill top mass plots

    name = "massT_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecT.M() );

    name = "massTzoom_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecT.M() );

    name = "massTPt_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( hadB->pt(), vecT.M() );

    name = "massTPtSmear_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecB.Pt(), vecT.M() );

    name = "massTPtZoom_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( hadB->pt(), vecT.M() );

    name = "massTPtSmearZoom_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecB.Pt(), vecT.M() );

    // eta plots only for ptcut = 30 GeV

    if(ptcut == 30) {
      hists_.find("respLEta")->second->Fill( hadP->eta(), vecP.Pt() / hadP->pt() );
      hists_.find("respLEta")->second->Fill( hadQ->eta(), vecQ.Pt() / hadQ->pt() );

      hists_.find("respBEta")->second->Fill( hadB->eta(), vecB.Pt() / hadB->pt() );

      hists_.find("massWEta")->second->Fill( hadP->eta(), vecW.M() );
      hists_.find("massWEta")->second->Fill( hadQ->eta(), vecW.M() );

      hists_.find("massTEta")->second->Fill( hadB->eta(), vecT.M() );

      hists_.find("massTEtaZoom")->second->Fill( hadB->eta(), vecT.M() );
    }

  }

}

void
JetEnergyResolutionBiasAnalyzer::endJob() 
{
  delete randNumGen_;
}
					 
void
JetEnergyResolutionBiasAnalyzer::smearEnergy(TLorentzVector &vec)
{
  double factor = randNumGen_->Gaus(1., resFact_ * sqrt(resParN_*resParN_ / (vec.E()*vec.E())
							+ resParS_*resParS_ / vec.E() + resParC_*resParC_) );

  if(factor < 0.)
    factor = 0.;

  vec *= factor;
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(JetEnergyResolutionBiasAnalyzer);
