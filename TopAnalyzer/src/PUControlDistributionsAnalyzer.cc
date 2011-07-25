#ifndef PUControlDistributionsAnalyzer_cc_
#define PUControlDistributionsAnalyzer_cc_

#include "TopAnalysis/TopAnalyzer/interface/PUControlDistributionsAnalyzer.h"

// =============================
//  constructors and destructor
// =============================

PUControlDistributionsAnalyzer::PUControlDistributionsAnalyzer(const edm::ParameterSet& iConfig)
{
  inTag_PUSource                = iConfig.getParameter<edm::InputTag>("PUSource");  
  inTag_PVertexSource           = iConfig.getParameter<edm::InputTag>("PVertexSource");  
  inTag_PUEventWeightSource     = iConfig.getParameter<edm::InputTag>("PUEventWeightSource");  
  inTag_PUEventWeightUpSource   = iConfig.getParameter<edm::InputTag>("PUEventWeightUpSource");   
  inTag_PUEventWeightDownSource = iConfig.getParameter<edm::InputTag>("PUEventWeightDownSource");  
}

PUControlDistributionsAnalyzer::~PUControlDistributionsAnalyzer(){}

// =============================

void PUControlDistributionsAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;

  // Histograms for PU Events

  histoNPU = fs->make<TH1F>("pileup","Number of PU Events (Unweighted)",71,-0.5,70.5);
  histoNPU -> SetTitle("");
  histoNPU -> GetXaxis() -> SetTitle("Number of PU Events (Unweighted)");
  histoNPU -> GetYaxis() -> SetTitle("Frequency");
  histoNPU -> SetFillColor(2);  

  histoNPUReweighted = fs->make<TH1F>("pileup_reweighted","Number of PU Events (Reweighted)",71,-0.5,70.5);
  histoNPUReweighted -> SetTitle("");
  histoNPUReweighted -> GetXaxis() -> SetTitle("Number of PU Events (Reweighted)");
  histoNPUReweighted -> GetYaxis() -> SetTitle("Frequency");
  histoNPUReweighted -> SetFillColor(2);

  histoNPUReweightedScaleUp = fs->make<TH1F>("pileup_reweighted_up","Number of PU Events (Reweighted, Scale Up)",71,-0.5,70.5);
  histoNPUReweightedScaleUp -> SetTitle("");
  histoNPUReweightedScaleUp -> GetXaxis() -> SetTitle("Number of PU Events (Reweighted, Scale Up)");
  histoNPUReweightedScaleUp -> GetYaxis() -> SetTitle("Frequency");
  histoNPUReweightedScaleUp -> SetFillColor(2);

  histoNPUReweightedScaleDown = fs->make<TH1F>("pileup_reweighted_down","Number of PU Events (Reweighted, Scale Down)",71,-0.5,70.5);
  histoNPUReweightedScaleDown -> SetTitle("");
  histoNPUReweightedScaleDown -> GetXaxis() -> SetTitle("Number of PU Events (Reweighted, Scale Down)");
  histoNPUReweightedScaleDown -> GetYaxis() -> SetTitle("Frequency");
  histoNPUReweightedScaleDown -> SetFillColor(2);

  // Histograms for Primary Vertices

  histoNPVertex = fs->make<TH1F>("npvertex","Number of Primary Vertices (Unweighted)",71,-0.5,70.5);
  histoNPVertex -> SetTitle("");
  histoNPVertex -> GetXaxis() -> SetTitle("Number of Primary Vertices (Unweighted)");
  histoNPVertex -> GetYaxis() -> SetTitle("Frequency");
  histoNPVertex -> SetFillColor(2);

  histoNPVertexReweighted = fs->make<TH1F>("npvertex_reweighted","Number of Primary Vertices (Reweighted)",71,-0.5,70.5);
  histoNPVertexReweighted -> SetTitle("");
  histoNPVertexReweighted -> GetXaxis() -> SetTitle("Number of Primary Vertices (Reweighted)");
  histoNPVertexReweighted -> GetYaxis() -> SetTitle("Frequency");
  histoNPVertexReweighted -> SetFillColor(2);  

  histoNPVertexReweightedScaleUp = fs->make<TH1F>("npvertex_reweighted_up","Number of Primary Vertices (Reweighted, Scale Up)",71,-0.5,70.5);
  histoNPVertexReweightedScaleUp -> SetTitle("");
  histoNPVertexReweightedScaleUp -> GetXaxis() -> SetTitle("Number of Primary Vertices (Reweighted, Scale Up)");
  histoNPVertexReweightedScaleUp -> GetYaxis() -> SetTitle("Frequency");
  histoNPVertexReweightedScaleUp -> SetFillColor(2);

  histoNPVertexReweightedScaleDown = fs->make<TH1F>("npvertex_reweighted_down","Number of Primary Vertices (Reweighted, Scale Down)",71,-0.5,70.5);
  histoNPVertexReweightedScaleDown -> SetTitle("");
  histoNPVertexReweightedScaleDown -> GetXaxis() -> SetTitle("Number of Primary Vertices (Reweighted, Scale Down)");
  histoNPVertexReweightedScaleDown -> GetYaxis() -> SetTitle("Frequency");
  histoNPVertexReweightedScaleDown -> SetFillColor(2);

  // Histograms for Event Weights

  histoEventWeights = fs->make<TH1F>("eventweights","Event Weights",200,-1,3); 
  histoEventWeights -> SetTitle("");
  histoEventWeights -> GetXaxis() -> SetTitle("Event Weight");
  histoEventWeights -> GetYaxis() -> SetTitle("Frequency");
  histoEventWeights -> SetFillColor(2);

  histoEventWeightsUp = fs->make<TH1F>("eventweights_up","Event Weight (Scale Up)",200,-1,3); 
  histoEventWeightsUp -> SetTitle("");
  histoEventWeightsUp -> GetXaxis() -> SetTitle("Event Weight (Scale Up)");
  histoEventWeightsUp -> GetYaxis() -> SetTitle("Frequency");
  histoEventWeightsUp -> SetFillColor(2);

  histoEventWeightsDown = fs->make<TH1F>("eventweights_down","Event Weight (Scale Down)",200,-1,3); 
  histoEventWeightsDown -> SetTitle("");
  histoEventWeightsDown -> GetXaxis() -> SetTitle("Event Weight (Scale Down)");
  histoEventWeightsDown -> GetYaxis() -> SetTitle("Frequency");
  histoEventWeightsDown -> SetFillColor(2);

}

// =============================

void PUControlDistributionsAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<edm::View<PileupSummaryInfo> > pPUInfo;
  iEvent.getByLabel(inTag_PUSource, pPUInfo);

  edm::Handle<edm::View<reco::Vertex> > pPVertex;
  iEvent.getByLabel(inTag_PVertexSource, pPVertex);

  edm::Handle<double> pPUEventWeight;
  iEvent.getByLabel(inTag_PUEventWeightSource, pPUEventWeight);

  edm::Handle<double> pPUEventWeightUp;
  iEvent.getByLabel(inTag_PUEventWeightUpSource, pPUEventWeightUp);

  edm::Handle<double> pPUEventWeightDown;
  iEvent.getByLabel(inTag_PUEventWeightDownSource, pPUEventWeightDown);

  edm::View<PileupSummaryInfo>::const_iterator iterPU;
  
  for(iterPU = pPUInfo->begin(); iterPU != pPUInfo->end(); ++iterPU)
  {    
    if (iterPU->getBunchCrossing()==0) // -1: previous BX, 0: current BX,  1: next BX
    {
      histoNPVertex                    -> Fill(pPVertex->size());
      histoNPVertexReweighted          -> Fill(pPVertex->size(),(*pPUEventWeight));
      histoNPVertexReweightedScaleUp   -> Fill(pPVertex->size(),(*pPUEventWeightUp));
      histoNPVertexReweightedScaleDown -> Fill(pPVertex->size(),(*pPUEventWeightDown));
      
      histoNPU                    -> Fill(iterPU->getPU_NumInteractions());
      histoNPUReweighted          -> Fill(iterPU->getPU_NumInteractions(),(*pPUEventWeight));
      histoNPUReweightedScaleUp   -> Fill(iterPU->getPU_NumInteractions(),(*pPUEventWeightUp));
      histoNPUReweightedScaleDown -> Fill(iterPU->getPU_NumInteractions(),(*pPUEventWeightDown));
      
      histoEventWeights     -> Fill((*pPUEventWeight));
      histoEventWeightsUp   -> Fill((*pPUEventWeightUp));
      histoEventWeightsDown -> Fill((*pPUEventWeightDown));
    }
  }
}

// =============================

void PUControlDistributionsAnalyzer::endJob(){}

DEFINE_FWK_MODULE(PUControlDistributionsAnalyzer);

#endif
