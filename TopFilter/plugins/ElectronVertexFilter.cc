#include "TopAnalysis/TopFilter/plugins/ElectronVertexFilter.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/EDMException.h"

ElectronVertexFilter::ElectronVertexFilter(const ParameterSet& cfg)
{
  vertices_ = cfg.getParameter<InputTag>("vertices"),
  electrons_    = cfg.getParameter<InputTag>("electrons"   ),  
  ndof_     = cfg.getParameter<unsigned int>("ndof"),  
  rho_      = cfg.getParameter<double>("rho"       ),  
  z_        = cfg.getParameter<double>("z"         ), 
  zdist_    = cfg.getParameter<double>("z_dist"    );
}

ElectronVertexFilter::~ElectronVertexFilter()
{
}

void
ElectronVertexFilter::beginJob()
{
}

bool
ElectronVertexFilter::filter(Event& evt, const EventSetup&)
{
  Handle<std::vector<reco::Vertex> > vertices; 
  evt.getByLabel(vertices_, vertices); 

  Handle<std::vector<pat::Electron> > electrons; 
  evt.getByLabel(electrons_, electrons);  
  
  bool pass = false;
  
  for(VertexCollection::const_iterator vrtx = vertices->begin(); vrtx!= vertices->end(); ++vrtx) { 
      
    if(!(vrtx->isFake()) && vrtx->ndof()>ndof_ && abs(vrtx->position().z())<z_ && vrtx->position().rho()<rho_){      
    
      for(std::vector<pat::Electron>::const_iterator electron = electrons->begin(); electron!= electrons->end(); ++electron) {  
        if(abs(electron->vz()-vrtx->position().z())>zdist_){ 
	  pass = false;
	  break;
	}  
	pass = true;
      }
      // matching PV found
      if(pass) break;  
    }   
  }
  return pass;
}

void
ElectronVertexFilter::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( ElectronVertexFilter );
