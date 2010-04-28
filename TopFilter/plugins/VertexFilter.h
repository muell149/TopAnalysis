#ifndef VertexFilter_h
#define VertexFilter_h

#include <string>
#include <vector>


#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

/**
   \class   VertexFilter VertexFilter.h "TopAnalysis/TopFilter/plugins/VertexFilter.h"

   \brief   EDFilter to make cuts on primary vertex

   This filter filters on vertex position, and number of tracks
*/

using namespace std;
using namespace edm;

class VertexFilter : public EDFilter {

  public:
    /// default constructor
    explicit VertexFilter(const ParameterSet&);
    /// default destructor
    ~VertexFilter();
    
  private:
    /// sanity check
    virtual void beginJob();
    /// filter on fake vertices, position and number of tracks
    virtual bool filter(Event&, const EventSetup&);
    /// empty
    virtual void endJob();
        
     /// input vertex collection
    InputTag vertices_;
    /// 3 cut values for x, y, z coordinate of the primary vertex
    vector<double> positionCuts_;
    /// number of tracks from vertex
    unsigned int nTracksCut_;    
};

#endif
