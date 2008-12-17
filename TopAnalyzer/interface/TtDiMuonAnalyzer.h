#ifndef TtDimuonAnalyzer_h
#define TtDimuonAnalyzer_h

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TString.h"
#include "TFile.h"
#include "TH1F.h"
#include "TMath.h"

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

#include "TopAnalysis/TopUtils/interface/NameScheme.h"
#include "TopAnalysis/TopUtils/interface/RootSystem.h"
#include "TopAnalysis/TopUtils/interface/RootHistograms.h"


class TtDiMuonAnalyzer : public edm::EDAnalyzer {

 public:

  explicit TtDiMuonAnalyzer(const edm::ParameterSet&);
  ~TtDiMuonAnalyzer();
  
 private:

  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  std::string hist_;

  bool  doTopObj_;
  bool  doGenEvt_;
  bool  doKin_;
  bool  doKinFit_;   

  TtDiMuonTopObjAna *obj_;
  TtDiMuonGenEvtAna *gen_;
  TtDiMuonKinSolAna *kin_;    
};

#endif
