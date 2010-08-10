#ifndef METKinFitAnalyzer_h
#define METKinFitAnalyzer_h

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
   \class   METKinFitAnalyzer METKinFitAnalyzer.h "TopAnalysis/TopAnalyzer/interface/METKinFitAnalyzer.h"

   \brief   EDAnalyzer for QuadJetXX trigger efficiency

   The structure keeps control histograms to analyze impact of KinFit on MET.
*/

class METKinFitAnalyzer : public edm::EDAnalyzer {

 public:
  /// default constructor
  explicit METKinFitAnalyzer(const edm::ParameterSet& configFile);
  /// default destructor
  ~METKinFitAnalyzer(){};

 private:

  /// initiate histograms
  virtual void beginJob();
  /// analyze triggers and fill histograms
  virtual void analyze(const edm::Event& event, const edm::EventSetup&);
  /// empty
  virtual void endJob();
        
  /// src's for the different infos
  edm::InputTag METSrc_;
  edm::InputTag JetSrc_;
  edm::InputTag FitSrc_;

  /// container to keep all histogramms
  std::map<std::string, TH1*> hists_;
};

#endif
