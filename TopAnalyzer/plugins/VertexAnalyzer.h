#ifndef VertexAnalyzer_h
#define VertexAnalyzer_h

#include <string>
#include <vector>

#include "TH1.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

/**
   \class   VertexAnalyzer VertexAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/VertexAnalyzer.h"

   \brief   EDAnalyzer to to plot properties of primary vertex

   EDAnalyzer to to plot properties of primary vertex
*/

using namespace std;
using namespace edm;

class VertexAnalyzer : public EDAnalyzer {

  public:
    /// default constructor
    explicit VertexAnalyzer(const ParameterSet&);
    /// default destructor
    ~VertexAnalyzer();
    
  private:
    /// initiate n_TrigPaths
    virtual void beginJob();
    /// look which triggers have fired and compare to given set of triggers
    virtual void analyze(const Event&, const EventSetup&);
    /// empty
    virtual void endJob();
        
     /// input vertex collection
    InputTag vertices_;
    
    TH1I* isFake_;
    TH1D* posX_;
    TH1D* posY_;    
    TH1D* posZ_;  
    TH1I* nTracks_;      
};

#endif
