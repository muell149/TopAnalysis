#include "TH1.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


/**
   \class   TagAndProbeAnalyzer TagAndProbeAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/TagAndProbeAnalyzer.h"

   \brief   Plugin to fill histograms for the determination of tag and probe efficiencies

   Add some more detailed documentation here...
*/

class TagAndProbeAnalyzer : public edm::EDAnalyzer {
 public:
  /// default constructor
   explicit TagAndProbeAnalyzer(const edm::ParameterSet& cfg);
  /// default destructor
    ~TagAndProbeAnalyzer();
  
  
 private:
  /// ...
  virtual void beginJob();
  /// ...
  virtual void analyze(const edm::Event& evt, const edm::EventSetup& setup);
  /// ...
  virtual void endJob();

 private:
  /// ...
  edm::InputTag probes_;
  edm::InputTag tests_;
  edm::InputTag jets_;  

  /// tag and probe histogram
  std::map<std::string, TH1F*> hists_;
};

