#ifndef TriggerEfficiency_h
#define TriggerEfficiency_h

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
   \class   TriggerEfficiency TriggerEfficiency.h "TopAnalysis/TopAnalyzer/interface/TriggerEfficiency.h"

   \brief   EDAnalyzer for QuadJetXX trigger efficiency

   The structure keeps control histograms to analyze QuadJetXX triggers. These histograms are to be
   filled from the trigger::TriggerEvent.
*/

class TriggerEfficiency : public edm::EDAnalyzer {

 public:
  /// default constructor
  explicit TriggerEfficiency(const edm::ParameterSet& configFile);
  /// default destructor
  ~TriggerEfficiency(){};

 private:

  /// initiate histograms
  virtual void beginJob();
  /// analyze triggers and fill histograms
  virtual void analyze(const edm::Event& event, const edm::EventSetup&);
  /// empty
  virtual void endJob();
        
  /// pat trigger event
  edm::InputTag patTriggerEvent_;

  /// container to keep all histogramms
  std::map<std::string, TH1*> hists_;
};

#endif
