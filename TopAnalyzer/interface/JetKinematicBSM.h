#ifndef JetKinematicBSM_h
#define JetKinematicBSM_h

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"



#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "AnalysisDataFormats/TopObjects/interface/TtDilepEvtSolution.h"
#include "TopAnalysis/TopAnalyzer/interface/TtDiMuonTopObjAna.h"
#include "TopAnalysis/TopAnalyzer/interface/TtDiMuonGenEvtAna.h"
#include "TopAnalysis/TopAnalyzer/interface/TtDiMuonKinSolAna.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopUtils/interface/RootSystem.h"
#include "TopAnalysis/TopUtils/interface/RootHistograms.h"



class JetKinematicBSM{

 public:

  explicit JetKinematicBSM(const edm::ParameterSet&, int);
  explicit JetKinematicBSM(const edm::ParameterSet&);
  ~JetKinematicBSM(){};

  void book();
  void book(edm::Service<TFileService>&);
  void book(edm::Service<TFileService>&, ofstream&);
  void fill(const edm::Event&, const std::vector<pat::Jet>&, const double&);
  void fill(const edm::Event&, const std::vector<pat::Jet>&, const std::vector<pat::MET>&, const double&);
  void norm(){};  
  void write(const char*, const char*);

 private:

  // additional evt content/steerings
  int nJets_;
  edm::InputTag metSource_;

  TH1F *mult_;
  TH1F *n10_;
  TH1F *n20_;
  TH1F *n30_;
  TH1F *n40_;
  TH1F *n50_;
  TH1F *n60_;
  TH1F *n70_;
  TH1F *n80_;
  TH1F *n90_;
  TH1F *n100_;

  TH1F *allEn_;
  TH1F *allEt_;
  TH1F *allEta_;
  TH1F *allPhi_;
  TH1F *scalSum_;
  TH1F *scalSum3_;
  TH1F *scalSum4_;
  TH1F *scalSum5_;
  TH1F *scalSum6_;

  std::vector<TH1F*> en_;
  std::vector<TH1F*> et_;
  std::vector<TH1F*> eta_;
  std::vector<TH1F*> phi_;

  std::vector<TH2F*> MET_JetET_;

  TH2F* MET_n30_;
  TH2F* MET_n40_;
  TH2F* MET_n50_;
  TH2F* MET_n60_;

};

#endif
