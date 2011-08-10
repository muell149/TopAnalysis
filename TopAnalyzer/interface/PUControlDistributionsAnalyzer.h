#ifndef PUControlDistributionsAnalyzer_h_
#define PUControlDistributionsAnalyzer_h_

#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/View.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include <TROOT.h>
#include <TObject.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>

class PUControlDistributionsAnalyzer : public edm::EDAnalyzer {

   public:
      explicit PUControlDistributionsAnalyzer(const edm::ParameterSet&);
      ~PUControlDistributionsAnalyzer();

   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data --------------------------- 

      TH1F* histoNPU;
      TH1F* histoNPUReweighted;
      TH1F* histoNPUReweightedScaleUp;
      TH1F* histoNPUReweightedScaleDown; 
      
      TH1F* histoNPUReweighted3BX;
      TH1F* histoNPUReweighted3BXScaleUp;
      TH1F* histoNPUReweighted3BXScaleDown;


      TH1F* histoNPVertex;
      TH1F* histoNPVertexReweighted; 
      TH1F* histoNPVertexReweightedScaleUp;
      TH1F* histoNPVertexReweightedScaleDown;  
      
      TH1F* histoNPVertexReweighted3BX; 
      TH1F* histoNPVertexReweighted3BXScaleUp;
      TH1F* histoNPVertexReweighted3BXScaleDown;

      TH1F* histoEventWeights;
      TH1F* histoEventWeightsUp;
      TH1F* histoEventWeightsDown;
      
      TH1F* histoEventWeights3BX;
      TH1F* histoEventWeights3BXUp;
      TH1F* histoEventWeights3BXDown;   

      TH2F* histoNPUvsNPVertex;

      edm::InputTag inTag_PUSource;
      edm::InputTag inTag_PUEventWeightSource;
      edm::InputTag inTag_PUEventWeightUpSource;
      edm::InputTag inTag_PUEventWeightDownSource;    
      edm::InputTag inTag_PUEventWeight3BXSource;
      edm::InputTag inTag_PUEventWeight3BXUpSource;
      edm::InputTag inTag_PUEventWeight3BXDownSource;
      edm::InputTag inTag_PVertexSource; 
      edm::InputTag inTag_defaultEventWeight;
};

#endif
