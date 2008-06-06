#ifndef EventFilter_h
#define EventFilter_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


template <typename Collection, typename Filter> 
class EventFilter : public edm::EDFilter {

 public:

  explicit EventFilter(const edm::ParameterSet&);
  ~EventFilter(){};
  
 private:

  virtual void beginJob(const edm::EventSetup&);
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob(){filter_.summarize();};

 private:
  
  std::vector<edm::InputTag> src_;

 private:
  
  Filter filter_;
};

template <typename Collection, typename Filter> 
EventFilter<Collection, Filter>::EventFilter(const edm::ParameterSet& cfg):
  src_( cfg.getParameter<std::vector<edm::InputTag> >( "input" ) ), filter_( cfg )
{
}

template <typename Collection, typename Filter> 
bool EventFilter<Collection, Filter>::filter(edm::Event& evt, const edm::EventSetup& setup)
{
  std::vector<Collection> objs;
  for(std::vector<edm::InputTag>::const_iterator tag = src_.begin(); 
      tag!=src_.end(); ++tag){
    edm::Handle<Collection> src;
    evt.getByLabel(*tag, src);
    objs.push_back(*src);
  }
  return filter_(evt, objs);
}

template <typename Collection, typename Filter> 
void EventFilter<Collection, Filter>::beginJob(const edm::EventSetup& setup)
{
}

#endif
  
