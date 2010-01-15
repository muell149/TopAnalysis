#include "TopAnalysis/TopAnalyzer/plugins/JetEnergyResolutionBiasAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"

#include "TH1F.h"
#include "TH2F.h"

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

  hists_["eta"] = fs->make<TH1F>("eta", "eta", 30, -3.,   3.);
  hists_["pt" ] = fs->make<TH1F>("pt" , "pt" , 50,  0., 250.);

  hists_["resp_0" ] = fs->make<TH1F>("resp_0" , "resp_0" , 51, 0., 2.);
  hists_["resp_10"] = fs->make<TH1F>("resp_10", "resp_10", 51, 0., 2.);
  hists_["resp_20"] = fs->make<TH1F>("resp_20", "resp_20", 51, 0., 2.);
  hists_["resp_30"] = fs->make<TH1F>("resp_30", "resp_30", 51, 0., 2.);
  hists_["resp_40"] = fs->make<TH1F>("resp_40", "resp_40", 51, 0., 2.);
  hists_["resp_50"] = fs->make<TH1F>("resp_50", "resp_50", 51, 0., 2.);

  hists_["respPt_0" ] = fs->make<TH2F>("respPt_0" , "respPt_0" , 50, 0., 250., 51, 0., 2.);
  hists_["respPt_10"] = fs->make<TH2F>("respPt_10", "respPt_10", 50, 0., 250., 51, 0., 2.);
  hists_["respPt_20"] = fs->make<TH2F>("respPt_20", "respPt_20", 50, 0., 250., 51, 0., 2.);
  hists_["respPt_30"] = fs->make<TH2F>("respPt_30", "respPt_30", 50, 0., 250., 51, 0., 2.);
  hists_["respPt_40"] = fs->make<TH2F>("respPt_40", "respPt_40", 50, 0., 250., 51, 0., 2.);
  hists_["respPt_50"] = fs->make<TH2F>("respPt_50", "respPt_50", 50, 0., 250., 51, 0., 2.);

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

  hists_.find("pt" )->second->Fill( vecB.Pt() );
  hists_.find("pt" )->second->Fill( vecP.Pt() );
  hists_.find("pt" )->second->Fill( vecQ.Pt() );

  smearPt(vecB);
  smearPt(vecP);
  smearPt(vecQ);

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

    TString name = "resp_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecB.Pt() / hadB->pt() );
    hists_.find((std::string)name)->second->Fill( vecP.Pt() / hadP->pt() );
    hists_.find((std::string)name)->second->Fill( vecQ.Pt() / hadQ->pt() );

    name = "respPt_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( hadB->pt(), vecB.Pt() / hadB->pt() );
    hists_.find((std::string)name)->second->Fill( hadP->pt(), vecP.Pt() / hadP->pt() );
    hists_.find((std::string)name)->second->Fill( hadQ->pt(), vecQ.Pt() / hadQ->pt() );

    name = "massW_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecW.M() );

    name = "massWzoom_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecW.M() );

    name = "massT_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecT.M() );

    name = "massTzoom_"; name += ptcut;
    hists_.find((std::string)name)->second->Fill( vecT.M() );

  }

}

void
JetEnergyResolutionBiasAnalyzer::endJob() 
{
  delete randNumGen_;
}
					 
void
JetEnergyResolutionBiasAnalyzer::smearPt(TLorentzVector &vec)
{
  vec *= randNumGen_->Gaus(1., resFact_ * sqrt(resParS_*resParS_ / (vec.Pt()*vec.Pt())
					       + resParN_*resParN_ / vec.Pt() + resParC_*resParC_) );
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(JetEnergyResolutionBiasAnalyzer);
