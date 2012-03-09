#include "TH1.h"
#include "TH2.h"
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
  edm::InputTag vertices_;
  std::string bTagAlgo_;
  double bTagDiscrCut_;
  std::vector<double> binsPtB_;
  std::vector<double> binsEtaB_;
  std::vector<double> binsPtL_;
  std::vector<double> binsEtaL_;
  
  edm::InputTag weightTag_;

  /// b tag eff. histogram
  std::map<std::string, TH1F*> hists_;
  /// b tag eff. histogram
  std::map<std::string, TH2F*> hists2D_;
};
