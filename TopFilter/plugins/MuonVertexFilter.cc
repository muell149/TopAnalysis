#include "TopAnalysis/TopFilter/plugins/MuonVertexFilter.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/EDMException.h"

MuonVertexFilter::MuonVertexFilter(const ParameterSet& cfg)
{
  vertices_ = cfg.getParameter<InputTag>("vertices"),
  muons_    = cfg.getParameter<InputTag>("muons"   ),  
  ndof_     = cfg.getParameter<unsigned int>("ndof"),  
  rho_      = cfg.getParameter<double>("rho"       ),  
  z_        = cfg.getParameter<double>("z"         ), 
  zdist_    = cfg.getParameter<double>("z_dist"    );
}

MuonVertexFilter::~MuonVertexFilter()
{
}

void
MuonVertexFilter::beginJob()
{
}

bool
MuonVertexFilter::filter(Event& evt, const EventSetup&)
{
  Handle<std::vector<reco::Vertex> > vertices; 
  evt.getByLabel(vertices_, vertices); 

  Handle<std::vector<pat::Muon> > muons; 
  evt.getByLabel(muons_, muons);  
  
  bool pass = false;
  
  for(VertexCollection::const_iterator vrtx = vertices->begin(); vrtx!= vertices->end(); ++vrtx) { 
      
    if(!(vrtx->isFake()) && vrtx->ndof()>ndof_ && abs(vrtx->position().z())<z_ && vrtx->position().rho()<rho_){      
    
      for(std::vector<pat::Muon>::const_iterator muon = muons->begin(); muon!= muons->end(); ++muon) {  
        if(abs(muon->vz()-vrtx->position().z())>zdist_){ 
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
MuonVertexFilter::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( MuonVertexFilter );
