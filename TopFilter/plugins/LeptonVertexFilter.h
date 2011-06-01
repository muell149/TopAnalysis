#ifndef LeptonVertexFilter_h
#define LeptonVertexFilter_h

#include <vector>

#include "TH1.h"

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h" 
#include "DataFormats/MuonReco/interface/MuonEnergy.h"
#include "DataFormats/MuonReco/interface/MuonIsolation.h"

#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/ElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

/**
   \class   LeptonVertexFilter LeptonVertexFilter.h "TopAnalysis/TopFilter/plugins/LeptonVertexFilter.h"

   \brief   EDFilter to select events where leptons are associated to primary vertex

   EDFilter to select events where leptons are associated to primary vertex
   it returns if there is at least one good vertex and all leptons are within given z distance
*/

using namespace std;
using namespace edm;

class LeptonVertexFilter : public EDFilter {

  public:
    /// default constructor
    explicit LeptonVertexFilter(const ParameterSet&);
    /// default destructor
    ~LeptonVertexFilter();
    
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
    /// input electron collection
    InputTag elecs_;

    /// ndof criterium for good vrtx
    unsigned int ndof_;
    /// rho criterium for good vrtx
    double rho_; 
    /// z criterium for good vrtx
    double z_; 
    /// maximum allowed distance between lepton and vrtx
    double zdist_;   
    
    typedef std::vector<reco::Vertex> VertexCollection;
    typedef std::vector<const reco::RecoCandidate*> RecoCandidateCollection;

};

#endif
