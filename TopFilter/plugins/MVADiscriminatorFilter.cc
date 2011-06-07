#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "TopAnalysis/TopFilter/plugins/MVADiscriminatorFilter.h"

MVADiscriminatorFilter::MVADiscriminatorFilter(const edm::ParameterSet& cfg):
  src_    ( cfg.getParameter<edm::InputTag>("src"    ) ),
  minDisc_( cfg.getParameter<double       >("minDisc") ),
  maxDisc_( cfg.getParameter<double       >("maxDisc") )
{
}

bool MVADiscriminatorFilter::filter(edm::Event& event, const edm::EventSetup& setup)
{

  edm::Handle<double> disc;
  event.getByLabel(src_, disc);
  
  return (*disc >= minDisc_ && *disc <= maxDisc_);
}

void MVADiscriminatorFilter::beginJob()
{
}

void MVADiscriminatorFilter::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( MVADiscriminatorFilter );
