#ifndef TemplateTreeWriter_h
#define TemplateTreeWriter_h

#include <vector>

#include "TTree.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

/**
   \class   TemplateTreeWriter TemplateTreeWriter.h "TopAnalysis/TopAnalyzer/plugins/TemplateTreeWriter.h"

   \brief   EDAnalyzer to to plot properties of primary vertex

   EDAnalyzer to fill a tree for template fitting
*/

using namespace std;
using namespace edm;

class TemplateTreeWriter : public EDAnalyzer {

  public:
    /// default constructor
    explicit TemplateTreeWriter(const ParameterSet&);
    /// default destructor
    ~TemplateTreeWriter();
    
  private:
    /// initiate n_TrigPaths
    virtual void beginJob();
    /// look which triggers have fired and compare to given set of triggers
    virtual void analyze(const Event&, const EventSetup&);
    /// empty
    virtual void endJob();
        
     /// input MET collection
    InputTag MET_;    
     /// input tight muon collection
    InputTag muons_;    
     /// input all muon collection
    InputTag allMuons_;    
    
    /// ndof criterium for good vrtx
    //unsigned int ndof_;
    
    //typedef std::vector<reco::Vertex> VertexCollection; 
    
    TTree* tree;
    float MET;
    float genMET;
    float lepET;
    float lepEta;
    float lepPhi;
    float HTlep;
    float relIso;
    float MT;
    float mMuMu;
};

#endif
