#ifndef TriggerAnalyzer_h
#define TriggerAnalyzer_h

#include <string>
#include <vector>

#include "TH1.h"
#include "TH2.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

/**
   \class   TriggerAnalyzer TriggerAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/TriggerAnalyzer.h"

   \brief   EDAnalyzer for trigger rates

   This analyzer takes a set of HLT triggers as input from the config file. For these triggers the 
   trigger rate is filled into a histogram. An other hisogram shows the number of all events that 
   have passed any trigger vs. the number of rejected events. 
*/

class TriggerAnalyzer : public edm::EDAnalyzer {

  public:
    /// default constructor
    explicit TriggerAnalyzer(const edm::ParameterSet&);
    /// default destructor
    ~TriggerAnalyzer();
    
  private:
    /// initiate histograms
    virtual void beginJob();
    /// analyze triggers and fill histograms
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    /// empty
    virtual void endJob();
    /// function to calculate binomial statistics error (needed for trigger efficiency hist)
    double binomialError(double, double);
        
    /// triger result input collection	
    edm::InputTag trigResults_;
    /// muon input collection
    edm::InputTag muons_;    
    /// triggers to be studied given in config
    std::vector<std::string> hltPaths_;
    /// for this trigger extra histos are plotted (pt and eta)
    std::string mainTrigger_;
    
    /// number of trigger paths given in config
    int n_TrigPaths;
    /// number of processed evts
    double n_evts;
    /// shows for each trigger fraction of evts that have fired that trigger
    TH1D* FiredTrigs_; 
    /// shows fraction evts that have passed one of the triggers
    TH1D* Passed_; 
    /// shows how many evts have fired two triggers
    TH2D* Correlations_;                   
};

#endif
