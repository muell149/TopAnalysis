#include "TopAnalysis/TopFilter/plugins/VertexFilter.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/Utilities/interface/EDMException.h"

VertexFilter::VertexFilter(const ParameterSet& cfg)
{
  vertices_     = cfg.getParameter<InputTag>("vertices");
  positionCuts_ = cfg.getParameter<vector<double> >("position_cuts");
  nTracksCut_   = cfg.getParameter<unsigned int>("n_tracks");  
}

VertexFilter::~VertexFilter()
{
}

void
VertexFilter::beginJob()
{
  /// check for correct size of postionCuts_
  if(positionCuts_.size()!=3) 
    throw edm::Exception( edm::errors::Configuration, "position_cuts has wrong size! 3 coordinates required!" );       
}

bool
VertexFilter::filter(Event& evt, const EventSetup&)
{
  Handle<std::vector<reco::Vertex> > vertices; 
  evt.getByLabel(vertices_, vertices); 

  reco::Vertex primaryVertex = vertices->front();

  /// check for fake vertex
  if(primaryVertex.isFake()){ 
    //cout << "IS FAKE" << endl;
    return false;
  }
  
  vector<double> position(3);
  position[0]=primaryVertex.x();
  position[1]=primaryVertex.y();  
  position[2]=primaryVertex.z();  
        
  /// check for vertex position
  for(int i=0;i<3;++i){
    if(abs(position[i])>positionCuts_[i]){
      //cout << "Position " << i << " = " << position[i] << endl;
      return false;
    }
  }
  
  /// check for number of tracks
  if(primaryVertex.tracksSize()<nTracksCut_){
    //cout << "Number of tracks is " << primaryVertex.tracksSize() << endl;
    return false;
  }
  
  return true;
}

void
VertexFilter::endJob()
{
}

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( VertexFilter );
