#include "TopAnalysis/TopFilter/plugins/MuonVertexDistanceSelector.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

MuonVertexDistanceSelector::MuonVertexDistanceSelector(const edm::ParameterSet& cfg):
  src_          (cfg.getParameter<edm::InputTag>("src"          )),
  primaryVertex_(cfg.getParameter<edm::InputTag>("primaryVertex"))
{
  produces<std::vector<pat::Muon> >();
}

void
MuonVertexDistanceSelector::produce(edm::Event& evt, const edm::EventSetup& setup)
{
  edm::Handle<std::vector<pat::Muon> > src; 
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

  std::auto_ptr<std::vector<pat::Muon> > selectedMuons(new std::vector<pat::Muon>());
  for(std::vector<pat::Muon>::const_iterator muon=src->begin(); muon!=src->end(); ++muon) {
    if(std::abs(muon->vertex().z() - primaryVertex->begin()->z()) < 1)
      selectedMuons->push_back(*muon);
  }
  evt.put(selectedMuons);
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(MuonVertexDistanceSelector);
