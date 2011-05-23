#ifndef VertexAnalyzer_h
#define VertexAnalyzer_h

#include <vector>

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

/**
   \class   VertexFilter VertexFilter.h "TopAnalysis/TopFilter/plugins/VertexFilter.h"

   \brief   EDFilter to select events where the objects of a collection are associated to one primary vertex

   EDFilter to select events where the objects of a collection are associated to primary vertex.
   It returns true if there is at least one good vertex and all objects are within given z distance.
   The identified vertex is added to the event.
*/

using namespace std;
using namespace edm;

template <typename Collection>
class VertexFilter : public EDFilter {

public:
  /// default constructor
  explicit VertexFilter(const ParameterSet&);
  /// default destructor
  ~VertexFilter();

private:
  /// initiate n_TrigPaths
  virtual void beginJob();
  /// look which triggers have fired and compare to given set of triggers
  virtual bool filter(Event&, const EventSetup&);
  /// empty
  virtual void endJob();

  /// input vertex collection
  InputTag vertices_;
  /// input input collection
  InputTag src_;
  /// only take into account first n_leps leptons from input collection
  unsigned int nleps_;

  /// ndof criterium for good vrtx
  unsigned int ndof_;
  /// rho criterium for good vrtx
  double rho_;
  /// z criterium for good vrtx
  double z_;
  /// maximum allowed distance between objects and vrtx
  double zdist_;

  typedef std::vector<reco::Vertex> VertexCollection;

};


template <typename Collection>
VertexFilter<Collection>::VertexFilter(const ParameterSet& cfg)
{
  vertices_  = cfg.getParameter<InputTag>("vertices"  );
  src_       = cfg.getParameter<InputTag>("src"       );
  nleps_     = cfg.getParameter<unsigned int>("n_leps");
  ndof_      = cfg.getParameter<unsigned int>("ndof"  );
  rho_       = cfg.getParameter<double>("rho"         );
  z_         = cfg.getParameter<double>("z"           );
  zdist_     = cfg.getParameter<double>("z_dist"      );

  if (cfg.existsAs<InputTag>("muons")) {
    edm::LogWarning("VertexFilter") << " VertexFilter is templetized, now. Please use src instead of muons as InputTag in your python file!" << std::endl;
    src_     = cfg.getParameter<InputTag>("muons");
  }

  produces<std::vector<reco::Vertex> >();

}

template <typename Collection>
VertexFilter<Collection>::~VertexFilter() {
}

template <typename Collection>
void VertexFilter<Collection>::beginJob() {
}


template <typename Collection>
void VertexFilter<Collection>::endJob() {
}


template <typename Collection>
bool
VertexFilter<Collection>::filter(Event& evt, const EventSetup&)
{
  Handle<std::vector<reco::Vertex> > vertices;
  evt.getByLabel(vertices_, vertices);
  std::auto_ptr<std::vector<reco::Vertex> > goodVertices( new std::vector<reco::Vertex>);


  Handle<std::vector<Collection> > inputCollection;
  evt.getByLabel(src_, inputCollection);

  bool pass = false;

  for(VertexCollection::const_iterator vrtx = vertices->begin(); vrtx!= vertices->end(); ++vrtx) {

    if(!(vrtx->isFake()) && vrtx->ndof()>ndof_ && fabs(vrtx->position().z())<z_ && vrtx->position().rho()<rho_){
      unsigned int i=0;
      for(typename std::vector<Collection>::const_iterator object = inputCollection->begin(); object != inputCollection->end(); ++object) {
        ++i;
	if(i>nleps_)
	  break;
	  
        if(fabs(object->vz()-vrtx->position().z())>zdist_){
          pass = false;
          break;
        }
        pass = true;
        goodVertices->push_back(*vrtx);
      }
      // matching PV found
      if(pass) break;
    }
  }

  evt.put(goodVertices);

  return pass;
}


#endif
