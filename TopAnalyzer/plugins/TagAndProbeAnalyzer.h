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
  edm::InputTag muons_;
  edm::InputTag jets_;  

  /// tag and probe histograms
  TH1F* pt;
  TH1F* eta;
  TH1F* phi;
  TH1F* minDR_Hist;
  TH1F* mult_Hist;
};

