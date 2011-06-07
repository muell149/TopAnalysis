#ifndef MVADiscriminatorFilter_h
#define MVADiscriminatorFilter_h

#include <TString.h>

#include "FWCore/Framework/interface/EDFilter.h"

class MVADiscriminatorFilter : public edm::EDFilter {

 public:

  explicit MVADiscriminatorFilter(const edm::ParameterSet&);
  ~MVADiscriminatorFilter(){};
  
 private:

  virtual void beginJob();
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

 private:
  
  edm::InputTag src_;
  double minDisc_;
  double maxDisc_;
};

#endif
