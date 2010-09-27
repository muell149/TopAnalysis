#include "TopAnalysis/TopFilter/plugins/TriggerFilter.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

using namespace edm;

TriggerFilter::TriggerFilter(const edm::ParameterSet& cfg)
{
  trigResults_ = cfg.getParameter<edm::InputTag>       ("TriggerResults");
  hltPaths_    = cfg.getParameter<std::vector<std::string> >("hltPaths" );
  vetoPaths_   = cfg.getParameter<std::vector<std::string> >("vetoPaths");  
}

TriggerFilter::~TriggerFilter()
{
}

void
TriggerFilter::beginJob()
{
    n_TrigPaths = hltPaths_.size(); 
    n_VetoPaths = vetoPaths_.size();     
}

bool
TriggerFilter::filter(edm::Event& evt, const edm::EventSetup&)
{
  Handle<TriggerResults> trigResults; 
  evt.getByLabel(trigResults_, trigResults); 

  if(trigResults.failedToGet()) return false;
  
  bool pass = false;
  int n_Triggers = trigResults->size();

  TriggerNames trigName = evt.triggerNames(*trigResults);

  for(int i_Trig = 0; i_Trig<n_Triggers; ++i_Trig){  
    // triggers which have not fired are not of interest -> contiue  
    if(!trigResults.product()->accept(i_Trig)) continue;
    // look if one of the HLT paths from config is among the paths having fired            
    for(int i = 0; i<n_TrigPaths; i++){
      if(!(trigName.triggerName(i_Trig)== hltPaths_[i])) continue; 	    	    	    	    
      pass = true;     	        
    } 
    // don't pass the event if veto trigger has fired
    for(int i = 0; i<n_VetoPaths; i++){
      if(!(trigName.triggerName(i_Trig)== vetoPaths_[i])) continue; 	    	    	    	    
      pass = false;     	        
    }          
  }  
  return pass;
}

void
TriggerFilter::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( TriggerFilter );
