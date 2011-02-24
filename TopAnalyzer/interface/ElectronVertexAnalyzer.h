#ifndef ElectronVertexAnalyzer_h
#define ElectronVertexAnalyzer_h

#include <vector>

#include "TH1D.h"
#include "TH3D.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

/**
   \class   VertexAnalyzer VertexAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/VertexAnalyzer.h"

   \brief   EDAnalyzer to to plot properties of primary vertex

   EDAnalyzer to to plot properties of primary vertex
*/

using namespace std;
using namespace edm;

class ElectronVertexAnalyzer : public EDAnalyzer {

  public:
    /// default constructor
    explicit ElectronVertexAnalyzer(const ParameterSet&);
    /// default destructor
    ~ElectronVertexAnalyzer();
    
  private:
    /// initiate n_TrigPaths
    virtual void beginJob();
    /// look which triggers have fired and compare to given set of triggers
    virtual void analyze(const Event&, const EventSetup&);
    /// empty
    virtual void endJob();
        
     /// input vertex collection
    InputTag vertices_;    
     /// input electron collection
    InputTag electrons_;    
     /// input beamspot collection
    InputTag beamspot_;    
    
    /// ndof criterium for good vrtx
    unsigned int ndof_;
    /// rho criterium for good vrtx
    double rho_; 
    /// z criterium for good vrtx
    double z_;     
    
    typedef std::vector<reco::Vertex> VertexCollection; 
    
    TH1D* multi_;
    TH1D* goodMulti_;
    TH1D* posX_;
    TH1D* posY_;    
    TH1D* posZ_;
    TH1D* posRho_;    
    TH1D* posXerr_;
    TH1D* posYerr_;    
    TH1D* posZerr_;              
    TH1D* nTracks_;
    TH1D* nDof_;
    TH1D* chi2_; 
    TH1D* nchi2_; 
    TH1D* dzEl_; 
    TH1D* dxyEl_;
    
    TH3D* position3D_;        
};

#endif
