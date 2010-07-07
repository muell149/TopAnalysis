#ifndef TriggerFilter_h
#define TriggerFilter_h

#include <string>
#include <vector>

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/EDMException.h"

/**
   \class   TriggerFilter TriggerFilter.h "TopAnalysis/TopFilter/plugins/TriggerFilter.h"

   \brief   EDFilter for trigger 

   This filter filters for triggers given in the config file. 
*/

using namespace std;
using namespace edm;

class TriggerFilter : public EDFilter {

  public:
    /// default constructor
    explicit TriggerFilter(const ParameterSet&);
    /// default destructor
    ~TriggerFilter();
    
  private:
    /// initiate n_TrigPaths
    virtual void beginJob();
    /// look which triggers have fired and compare to given set of triggers
    virtual bool filter(Event&, const EventSetup&);
    /// empty
    virtual void endJob();
        
     /// triger result input collection	
    InputTag trigResults_;
    /// triggers to be studied given in config
    vector<string> hltPaths_;
    /// number of trigger paths given in config
    int n_TrigPaths;      
};

#endif
