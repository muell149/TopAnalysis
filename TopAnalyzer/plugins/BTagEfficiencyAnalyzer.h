#include "TH1.h"
#include <string>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


/**
   \class   BTagEfficiencyAnalyzer BTagEfficiencyAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/BTagEfficiencyAnalyzer.h"

   \brief   Plugin to fill histograms for the determination of b tag efficiencies (for b, c and l jets) from MC
   
   /// Overall efficiency and dependence on pt and eta is calculated.

*/

class BTagEfficiencyAnalyzer : public edm::EDAnalyzer {
 public:
  /// default constructor
   explicit BTagEfficiencyAnalyzer(const edm::ParameterSet& cfg);
  /// default destructor
    ~BTagEfficiencyAnalyzer();
  
  
 private:
  /// ...
  virtual void beginJob();
  /// ...
  virtual void analyze(const edm::Event& evt, const edm::EventSetup& setup);
  /// ...
  virtual void endJob();

 private:
  /// ...
  edm::InputTag jets_;
  std::string bTagAlgo_;
  double bTagDiscrCut_;
  std::vector<double> binsPt_;
  std::vector<double> binsEta_;

  /// tag and probe histogram
  std::map<std::string, TH1F*> hists_;
};
