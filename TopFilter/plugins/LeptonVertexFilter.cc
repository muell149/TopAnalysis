
#include "TopAnalysis/TopFilter/plugins/LeptonVertexFilter.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Utilities/interface/EDMException.h"

LeptonVertexFilter::LeptonVertexFilter(const ParameterSet& cfg) {

  vertices_ = cfg.getParameter<InputTag>("vertices");
  muons_    = cfg.getParameter<InputTag>("muons"   );
  elecs_    = cfg.getParameter<InputTag>("elecs"   );
  ndof_     = cfg.getParameter<unsigned int>("ndof");  
  rho_      = cfg.getParameter<double>("rho"       );  
  z_        = cfg.getParameter<double>("z"         ); 
  zdist_    = cfg.getParameter<double>("z_dist"    );

}

LeptonVertexFilter::~LeptonVertexFilter()
{
}

void
LeptonVertexFilter::beginJob()
{
}

bool LeptonVertexFilter::filter(Event& evt, const EventSetup&) {

  Handle<std::vector<reco::Vertex> > vertices; 
  evt.getByLabel(vertices_, vertices); 

  Handle<std::vector<pat::Muon> > muons; 
  evt.getByLabel(muons_, muons);
  
  Handle<std::vector<pat::Electron> > elecs; 
  evt.getByLabel(elecs_, elecs);

  RecoCandidateCollection leptons;


  for( std::vector<pat::Muon>::const_iterator muon = muons->begin(); muon!= muons->end(); ++muon ) {

    leptons.push_back(&(*muon));

  }


  for( std::vector<pat::Electron>::const_iterator elec = elecs->begin(); elec!= elecs->end(); ++elec ) {

    leptons.push_back(&(*elec));

  }

  bool pass = false;
  
  for( VertexCollection::const_iterator vrtx = vertices->begin(); vrtx!= vertices->end(); ++vrtx ) {

    if( !(vrtx->isFake()) && (vrtx->ndof() > ndof_) && (abs(vrtx->position().z()) < z_) && (vrtx->position().rho() < rho_) ) {

      for( RecoCandidateCollection::const_iterator lepton = leptons.begin(); lepton!= leptons.end(); ++lepton ) {

        if( abs((*lepton)->vz() - vrtx->position().z()) > zdist_ ) {

	  pass = false;
	  break;

	}  

	else pass = true;

      }

      // matching PV found

      if( pass )  break;

    }

  }

  return pass;

}

void
LeptonVertexFilter::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( LeptonVertexFilter );
