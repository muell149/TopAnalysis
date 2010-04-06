#include "TopAnalysis/TopFilter/plugins/PtHatFilter.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "FWCore/Framework/interface/Event.h"

PtHatFilter::PtHatFilter(const edm::ParameterSet& cfg):
  minPtHat_      ( cfg.getParameter<double>       ("minPtHat"      ) ),
  maxPtHat_      ( cfg.getParameter<double>       ("maxPtHat"      ) ),
  useEventWeight_( cfg.getParameter<bool>         ("useEventWeight") ),
  weight_        ( cfg.getParameter<edm::InputTag>("weight"        ) ),
  beforeCut_( 0 ), afterCut_( 0 ), beforeCutWeighted_( 0. ), afterCutWeighted_( 0. )
{
}

bool PtHatFilter::filter(edm::Event& event, const edm::EventSetup& setup)
{
  double weight = 1.;
  if(useEventWeight_) { 
    edm::Handle<double> weightHandle;
    event.getByLabel(weight_, weightHandle);
    weight = *weightHandle;
  }

  ++beforeCut_;
  beforeCutWeighted_ += weight;

  bool pass = false;

  edm::Handle<GenEventInfoProduct> GenEventInfoProduct;
  event.getByLabel( "generator", GenEventInfoProduct );

  //if(GenEventInfoProduct!=0){
    if((*GenEventInfoProduct).binningValues().size()>0){
      if( minPtHat_ < (*GenEventInfoProduct).binningValues()[0] && maxPtHat_ > (*GenEventInfoProduct).binningValues()[0] ){
	
	pass=true;

	++afterCut_;
	afterCutWeighted_ += weight;
      }
    }
  //}

  return pass;
}

void PtHatFilter::beginJob()
{
}

void PtHatFilter::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( PtHatFilter );
