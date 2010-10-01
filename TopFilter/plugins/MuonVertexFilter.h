#ifndef VertexAnalyzer_h
#define VertexAnalyzer_h

#include <vector>

#include "TH1.h"

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

/**
   \class   MuonVertexFilter MuonVertexFilter.h "TopAnalysis/TopFilter/plugins/MuonVertexFilter.h"

   \brief   EDFilter to select events where muons are associated to primary vertex

   EDFilter to select events where muons are associated to primary vertex
   it returns if there is at least one good vertex and all muons are within given z distance
*/

using namespace std;
using namespace edm;

class MuonVertexFilter : public EDFilter {

  public:
    /// default constructor
    explicit MuonVertexFilter(const ParameterSet&);
    /// default destructor
    ~MuonVertexFilter();
    
  private:
    /// initiate n_TrigPaths
    virtual void beginJob();
    /// look which triggers have fired and compare to given set of triggers
    virtual bool filter(Event&, const EventSetup&);
    /// empty
    virtual void endJob();
        
     /// input vertex collection
    InputTag vertices_;    
     /// input muon collection
    InputTag muons_; 
    
    /// ndof criterium for good vrtx
    unsigned int ndof_;
    /// rho criterium for good vrtx
    double rho_; 
    /// z criterium for good vrtx
    double z_; 
    /// maximum allowed distance between muon and vrtx
    double zdist_;   
    
    typedef std::vector<reco::Vertex> VertexCollection; 
        
};

#endif
