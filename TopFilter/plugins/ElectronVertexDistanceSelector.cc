#include "TopAnalysis/TopFilter/plugins/ElectronVertexDistanceSelector.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

ElectronVertexDistanceSelector::ElectronVertexDistanceSelector(const edm::ParameterSet& cfg):
  src_          (cfg.getParameter<edm::InputTag>("src"          )),
  primaryVertex_(cfg.getParameter<edm::InputTag>("primaryVertex"))
{
  produces<std::vector<pat::Electron> >();
}

void
ElectronVertexDistanceSelector::produce(edm::Event& evt, const edm::EventSetup& setup)
{
  edm::Handle<std::vector<pat::Electron> > src; 
  evt.getByLabel(src_, src);

  edm::Handle<reco::VertexCollection> primaryVertex;
  evt.getByLabel(primaryVertex_, primaryVertex);

//  for(reco::VertexCollection::const_iterator vtx=primaryVertex->begin(); vtx!=primaryVertex->end(); ++vtx) {
//    std::cout << "vtx->isFake:ndof:z:rho : "
//	      << vtx->isFake() << ":"
//	      << vtx->ndof() << ":"
//	      << vtx->z() << ":"
//	      << vtx->position().Rho() << std::endl;
//  }

  std::auto_ptr<std::vector<pat::Electron> > selectedElectrons(new std::vector<pat::Electron>());
  for(std::vector<pat::Electron>::const_iterator elec=src->begin(); elec!=src->end(); ++elec) {
    if(std::abs(elec->vertex().z() - primaryVertex->begin()->z()) < 1)
      selectedElectrons->push_back(*elec);
  }
  evt.put(selectedElectrons);
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(ElectronVertexDistanceSelector);
