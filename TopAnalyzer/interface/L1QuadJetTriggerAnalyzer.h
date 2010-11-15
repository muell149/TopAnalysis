#ifndef L1QuadJetTriggerAnalyzer_h
#define L1QuadJetTriggerAnalyzer_h

#include <string>
#include <cstring>
#include <vector>
#include <map>

#include "TH1.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

/**
   \class   L1QuadJetTriggerAnalyzer L1QuadJetTriggerAnalyzer.h "TopAnalysis/TopAnalyzer/interface/L1QuadJetTriggerAnalyzer.h"

   \brief   EDAnalyzer for L1_QuadJetXX trigger efficiency

   The structure keeps control histograms to analyze L1 QuadJet trigger
*/

class L1QuadJetTriggerAnalyzer : public edm::EDAnalyzer {

 public:
  /// default constructor
  explicit L1QuadJetTriggerAnalyzer(const edm::ParameterSet& configFile);
  /// default destructor
  ~L1QuadJetTriggerAnalyzer(){};

 private:

  /// initiate histograms
  virtual void beginJob();
  /// analyze triggers and fill histograms
  virtual void analyze(const edm::Event& event, const edm::EventSetup&);
  /// empty
  virtual void endJob();
        
  /// src's for the different infos
  edm::InputTag patTriggerEvent_;

  /// container to keep all histogramms
  std::map<std::string, TH1*> hists_;
};

#endif
