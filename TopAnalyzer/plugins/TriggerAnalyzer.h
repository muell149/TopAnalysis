#ifndef TriggerAnalyzer_h
#define TriggerAnalyzer_h

#include <string>
#include <cstring>
#include <vector>

#include "TH1.h"
#include "TH2.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/TriggerNames.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

/**
   \class   TriggerAnalyzer TriggerAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/TriggerAnalyzer.h"

   \brief   EDAnalyzer for trigger rates

   This analyzer takes a set of HLT triggers as input from the config file. For these triggers the 
   trigger rate is filled into a histogram. An other hisogram shows the number of all events that 
   have passed any trigger vs. the number of rejected events. 
*/

using namespace std;
using namespace edm;

class TriggerAnalyzer : public EDAnalyzer {

  public:
    /// default constructor
    explicit TriggerAnalyzer(const ParameterSet&);
    /// default destructor
    ~TriggerAnalyzer();
    
  private:
    /// initiate histograms
    virtual void beginJob();
    /// analyze triggers and fill histograms
    virtual void analyze(const Event&, const EventSetup&);
    /// empty
    virtual void endJob();
        
    /// triger result input collection	
    InputTag trigResults_;
    /// triggers to be studied given in config
    vector<string> hltPaths_L3_;
    
    /// number of trigger paths given in config
    int n_TrigPaths;
    /// shows for each trigger how many evts have fired that trigger
    TH1F* FiredTrigs_; 
    /// shows how many evts have passed one of the triggers
    TH1F* Passed_; 
    /// shows how many evts have fired two triggers
    TH2F* Correlations_;   
};

#endif
