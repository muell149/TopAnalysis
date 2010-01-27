#include "TopAnalysis/TopAnalyzer/plugins/JetEnergyResolutionBiasAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

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

  double binningLogPt[15] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
			     120, 150, 200, 250, 300};

  hists_["eta"      ] = fs->make<TH1F>("eta"      , "eta"      , 30, -3.,   3.);
  hists_["pt"       ] = fs->make<TH1F>("pt"       , "pt"       , 50,  0., 250.);
  hists_["ptSmeared"] = fs->make<TH1F>("ptSmeared", "ptSmeared", 50,  0., 250.);

  hists_["energy"       ] = fs->make<TH1F>("energy"       , "energy"       , 50,  0., 250.);
  hists_["energySmeared"] = fs->make<TH1F>("energySmeared", "energySmeared", 50,  0., 250.);

  hists_["theta"] = fs->make<TH1F>("theta", "theta", 21, 0., 3.15);

  hists_["energySmearedOverGen" ] = fs->make<TH2F>("energySmearedOverGen", "energySmearedOverGen",
						   50, 0., 250., 51, 0., 2.);

  hists_["resp_0" ] = fs->make<TH1F>("resp_0" , "resp_0" , 51, 0., 2.);
  hists_["resp_10"] = fs->make<TH1F>("resp_10", "resp_10", 51, 0., 2.);
  hists_["resp_20"] = fs->make<TH1F>("resp_20", "resp_20", 51, 0., 2.);
  hists_["resp_30"] = fs->make<TH1F>("resp_30", "resp_30", 51, 0., 2.);
  hists_["resp_40"] = fs->make<TH1F>("resp_40", "resp_40", 51, 0., 2.);
  hists_["resp_50"] = fs->make<TH1F>("resp_50", "resp_50", 51, 0., 2.);

  hists_["respPt_0" ] = fs->make<TH2F>("respPt_0" , "respPt_0" , 14, binningLogPt, 51, 0., 2.);
  hists_["respPt_10"] = fs->make<TH2F>("respPt_10", "respPt_10", 14, binningLogPt, 51, 0., 2.);
  hists_["respPt_20"] = fs->make<TH2F>("respPt_20", "respPt_20", 14, binningLogPt, 51, 0., 2.);
  hists_["respPt_30"] = fs->make<TH2F>("respPt_30", "respPt_30", 14, binningLogPt, 51, 0., 2.);
  hists_["respPt_40"] = fs->make<TH2F>("respPt_40", "respPt_40", 14, binningLogPt, 51, 0., 2.);
  hists_["respPt_50"] = fs->make<TH2F>("respPt_50", "respPt_50", 14, binningLogPt, 51, 0., 2.);

  hists_["respPtSmear_0" ] = fs->make<TH2F>("respPtSmear_0" , "respPtSmear_0" , 14, binningLogPt, 51, 0., 2.);
  hists_["respPtSmear_10"] = fs->make<TH2F>("respPtSmear_10", "respPtSmear_10", 14, binningLogPt, 51, 0., 2.);
  hists_["respPtSmear_20"] = fs->make<TH2F>("respPtSmear_20", "respPtSmear_20", 14, binningLogPt, 51, 0., 2.);
  hists_["respPtSmear_30"] = fs->make<TH2F>("respPtSmear_30", "respPtSmear_30", 14, binningLogPt, 51, 0., 2.);
  hists_["respPtSmear_40"] = fs->make<TH2F>("respPtSmear_40", "respPtSmear_40", 14, binningLogPt, 51, 0., 2.);
  hists_["respPtSmear_50"] = fs->make<TH2F>("respPtSmear_50", "respPtSmear_50", 14, binningLogPt, 51, 0., 2.);

  hists_["massW_0" ] = fs->make<TH1F>("massW_0 ", "massW_0 ", 28, 0., 140.);
  hists_["massW_10"] = fs->make<TH1F>("massW_10", "massW_10", 28, 0., 140.);
  hists_["massW_20"] = fs->make<TH1F>("massW_20", "massW_20", 28, 0., 140.);
  hists_["massW_30"] = fs->make<TH1F>("massW_30", "massW_30", 28, 0., 140.);
  hists_["massW_40"] = fs->make<TH1F>("massW_40", "massW_40", 28, 0., 140.);
  hists_["massW_50"] = fs->make<TH1F>("massW_50", "massW_50", 28, 0., 140.);

  hists_["massWzoom_0" ] = fs->make<TH1F>("massWzoom_0 ", "massWzoom_0 ", 80, 60., 100.);
  hists_["massWzoom_10"] = fs->make<TH1F>("massWzoom_10", "massWzoom_10", 80, 60., 100.);
  hists_["massWzoom_20"] = fs->make<TH1F>("massWzoom_20", "massWzoom_20", 80, 60., 100.);
  hists_["massWzoom_30"] = fs->make<TH1F>("massWzoom_30", "massWzoom_30", 80, 60., 100.);
  hists_["massWzoom_40"] = fs->make<TH1F>("massWzoom_40", "massWzoom_40", 80, 60., 100.);
  hists_["massWzoom_50"] = fs->make<TH1F>("massWzoom_50", "massWzoom_50", 80, 60., 100.);

  hists_["massWPt_0" ] = fs->make<TH2F>("massWPt_0 ", "massWPt_0 ", 14, binningLogPt, 28, 0., 140.);
  hists_["massWPt_10"] = fs->make<TH2F>("massWPt_10", "massWPt_10", 14, binningLogPt, 28, 0., 140.);
  hists_["massWPt_20"] = fs->make<TH2F>("massWPt_20", "massWPt_20", 14, binningLogPt, 28, 0., 140.);
  hists_["massWPt_30"] = fs->make<TH2F>("massWPt_30", "massWPt_30", 14, binningLogPt, 28, 0., 140.);
  hists_["massWPt_40"] = fs->make<TH2F>("massWPt_40", "massWPt_40", 14, binningLogPt, 28, 0., 140.);
  hists_["massWPt_50"] = fs->make<TH2F>("massWPt_50", "massWPt_50", 14, binningLogPt, 28, 0., 140.);

  hists_["massWPtSmear_0" ] = fs->make<TH2F>("massWPtSmear_0 ", "massWPtSmear_0 ", 14, binningLogPt, 28, 0., 140.);
  hists_["massWPtSmear_10"] = fs->make<TH2F>("massWPtSmear_10", "massWPtSmear_10", 14, binningLogPt, 28, 0., 140.);
  hists_["massWPtSmear_20"] = fs->make<TH2F>("massWPtSmear_20", "massWPtSmear_20", 14, binningLogPt, 28, 0., 140.);
  hists_["massWPtSmear_30"] = fs->make<TH2F>("massWPtSmear_30", "massWPtSmear_30", 14, binningLogPt, 28, 0., 140.);
  hists_["massWPtSmear_40"] = fs->make<TH2F>("massWPtSmear_40", "massWPtSmear_40", 14, binningLogPt, 28, 0., 140.);
  hists_["massWPtSmear_50"] = fs->make<TH2F>("massWPtSmear_50", "massWPtSmear_50", 14, binningLogPt, 28, 0., 140.);

  hists_["massT_0" ] = fs->make<TH1F>("massT_0 ", "massT_0 ", 60, 0., 300.);
  hists_["massT_10"] = fs->make<TH1F>("massT_10", "massT_10", 60, 0., 300.);
  hists_["massT_20"] = fs->make<TH1F>("massT_20", "massT_20", 60, 0., 300.);
  hists_["massT_30"] = fs->make<TH1F>("massT_30", "massT_30", 60, 0., 300.);
  hists_["massT_40"] = fs->make<TH1F>("massT_40", "massT_40", 60, 0., 300.);
  hists_["massT_50"] = fs->make<TH1F>("massT_50", "massT_50", 60, 0., 300.);

  hists_["massTzoom_0" ] = fs->make<TH1F>("massTzoom_0 ", "massTzoom_0 ", 100, 150., 200.);
  hists_["massTzoom_10"] = fs->make<TH1F>("massTzoom_10", "massTzoom_10", 100, 150., 200.);
  hists_["massTzoom_20"] = fs->make<TH1F>("massTzoom_20", "massTzoom_20", 100, 150., 200.);
  hists_["massTzoom_30"] = fs->make<TH1F>("massTzoom_30", "massTzoom_30", 100, 150., 200.);
  hists_["massTzoom_40"] = fs->make<TH1F>("massTzoom_40", "massTzoom_40", 100, 150., 200.);
  hists_["massTzoom_50"] = fs->make<TH1F>("massTzoom_50", "massTzoom_50", 100, 150., 200.);

  hists_["massTPt_0" ] = fs->make<TH2F>("massTPt_0 ", "massTPt_0 ", 14, binningLogPt, 60, 0., 300.);
  hists_["massTPt_10"] = fs->make<TH2F>("massTPt_10", "massTPt_10", 14, binningLogPt, 60, 0., 300.);
  hists_["massTPt_20"] = fs->make<TH2F>("massTPt_20", "massTPt_20", 14, binningLogPt, 60, 0., 300.);
  hists_["massTPt_30"] = fs->make<TH2F>("massTPt_30", "massTPt_30", 14, binningLogPt, 60, 0., 300.);
  hists_["massTPt_40"] = fs->make<TH2F>("massTPt_40", "massTPt_40", 14, binningLogPt, 60, 0., 300.);
  hists_["massTPt_50"] = fs->make<TH2F>("massTPt_50", "massTPt_50", 14, binningLogPt, 60, 0., 300.);

  hists_["massTPtSmear_0" ] = fs->make<TH2F>("massTPtSmear_0 ", "massTPtSmear_0 ", 14, binningLogPt, 60, 0., 300.);
  hists_["massTPtSmear_10"] = fs->make<TH2F>("massTPtSmear_10", "massTPtSmear_10", 14, binningLogPt, 60, 0., 300.);
  hists_["massTPtSmear_20"] = fs->make<TH2F>("massTPtSmear_20", "massTPtSmear_20", 14, binningLogPt, 60, 0., 300.);
  hists_["massTPtSmear_30"] = fs->make<TH2F>("massTPtSmear_30", "massTPtSmear_30", 14, binningLogPt, 60, 0., 300.);
  hists_["massTPtSmear_40"] = fs->make<TH2F>("massTPtSmear_40", "massTPtSmear_40", 14, binningLogPt, 60, 0., 300.);
  hists_["massTPtSmear_50"] = fs->make<TH2F>("massTPtSmear_50", "massTPtSmear_50", 14, binningLogPt, 60, 0., 300.);

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

  //  std::cout << genEvent->semiLeptonicChannel() << std::endl;

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

  hists_.find("pt")->second->Fill( vecB.Pt() );
  hists_.find("pt")->second->Fill( vecP.Pt() );
  hists_.find("pt")->second->Fill( vecQ.Pt() );

  hists_.find("energy")->second->Fill( vecB.E() );
  hists_.find("energy")->second->Fill( vecP.E() );
  hists_.find("energy")->second->Fill( vecQ.E() );

  hists_.find("theta")->second->Fill( vecP.Angle(vecQ.Vect()) );

  smearEnergy(vecB);
  smearEnergy(vecP);
  smearEnergy(vecQ);

  hists_.find("ptSmeared")->second->Fill( vecB.Pt() );
  hists_.find("ptSmeared")->second->Fill( vecP.Pt() );
  hists_.find("ptSmeared")->second->Fill( vecQ.Pt() );

  hists_.find("energySmeared")->second->Fill( vecB.E() );
  hists_.find("energySmeared")->second->Fill( vecP.E() );
  hists_.find("energySmeared")->second->Fill( vecQ.E() );

  hists_.find("energySmearedOverGen")->second->Fill( hadB->energy(), vecB.Energy() / hadB->energy() );
  hists_.find("energySmearedOverGen")->second->Fill( hadP->energy(), vecP.Energy() / hadP->energy() );
  hists_.find("energySmearedOverGen")->second->Fill( hadQ->energy(), vecQ.Energy() / hadQ->energy() );

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

    // fill response plots

    TString name = "resp_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecB.Pt() / hadB->pt() );
    hists_.find((std::string)name)->second->Fill( vecP.Pt() / hadP->pt() );
    hists_.find((std::string)name)->second->Fill( vecQ.Pt() / hadQ->pt() );

    name = "respPt_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( hadB->pt(), vecB.Pt() / hadB->pt() );
    hists_.find((std::string)name)->second->Fill( hadP->pt(), vecP.Pt() / hadP->pt() );
    hists_.find((std::string)name)->second->Fill( hadQ->pt(), vecQ.Pt() / hadQ->pt() );

    name = "respPtSmear_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecB.Pt(), vecB.Pt() / hadB->pt() );
    hists_.find((std::string)name)->second->Fill( vecP.Pt(), vecP.Pt() / hadP->pt() );
    hists_.find((std::string)name)->second->Fill( vecQ.Pt(), vecQ.Pt() / hadQ->pt() );

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
    hists_.find((std::string)name)->second->Fill( hadP->pt(), vecT.M() );
    hists_.find((std::string)name)->second->Fill( hadQ->pt(), vecT.M() );

    name = "massTPtSmear_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecB.Pt(), vecT.M() );
    hists_.find((std::string)name)->second->Fill( vecP.Pt(), vecT.M() );
    hists_.find((std::string)name)->second->Fill( vecQ.Pt(), vecT.M() );

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
