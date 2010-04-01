#ifndef RunEventFilter_h
#define RunEventFilter_h

#include <string>
#include <vector>

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/EDMException.h"

/**
   \class   RunEventFilter RunEventFilter.h "TopAnalysis/TopFilter/plugins/RunEventFilter.h"

   \brief   EDFilter to select or reject single events and runs in your data

   This filter can be used to select or reject single events and runs in your data. In your config
   file you give a list of selected runs and or or run ranges as string. If you select a long range
   of runs you can additionally give a list of excluded runs which you want to be removed from this 
   run range.
   For each run you can add a pset containing the run number as an unsigned integer and a string 
   contaning a list of events or event ranges. In this case only the these events are selected what
   is e.g. usefull to select single events for the event display.
   If you begin the event list with a '!' the events in the list are rejected e.g. to use with single 
   bad events causing errors.
*/

using namespace std;
using namespace edm;

class RunEventFilter : public EDFilter {

  public:
    /// constructor: read config
    explicit RunEventFilter(const ParameterSet&);
    /// default destructor
    ~RunEventFilter();
    
  private:
    /// parses the given run and event strings from config to uint numbers using the Parse* functions
    virtual void beginJob();
    /// get event and run number and look if the event is selected in config
    virtual bool filter(Event&, const EventSetup&);
    /// empty
    virtual void endJob();
     
    /// config string containing the selected runs 
    string runStr_; 
    /// config string containing the excluded runs
    string excludedRuns_;  
    /// config psets contain run number as uint and a string with selected or rejected evts         
    vector<edm::ParameterSet> psets_;     
    
    /// runlist is stored as struct containing run number, evts, evt_ranges and if evts are to be selected or rejected
    struct runStruct{
      unsigned int run;
      vector<unsigned int> evts;
      vector<pair<unsigned int, unsigned int> > evt_ranges;
      bool reject;
    };
    
    /// vector contains all runs to be selected
    vector<runStruct> runlist;
    
    /// transforms the runlist string into a vector which contains the run numbers as integers
    vector<unsigned int> ParseRunString(string);
    /// transforms the events string into a pair of vectors
    /// the first vector contains single events
    /// the second vector contains event ranges as pair: first event, last event
    pair<vector<unsigned int>, vector<pair<unsigned int, unsigned int> > > ParseEventString(string);
    /// is wrong if the string contains a symble which is not element of {1234567890-,} 
    bool isValid(const string&);
};

#endif
