#ifndef PUControlDistributionsAnalyzer_cc_
#define PUControlDistributionsAnalyzer_cc_

#include "TopAnalysis/TopAnalyzer/interface/PUControlDistributionsAnalyzer.h"

// =============================
//  constructors and destructor
// =============================

PUControlDistributionsAnalyzer::PUControlDistributionsAnalyzer(const edm::ParameterSet& iConfig)
{
  inTag_PUSource                   = iConfig.getParameter<edm::InputTag>("PUSource");  
  inTag_PVertexSource              = iConfig.getParameter<edm::InputTag>("PVertexSource");  
  inTag_PUEventWeightSource        = iConfig.getParameter<edm::InputTag>("PUEventWeightSource");  
  inTag_PUEventWeightUpSource      = iConfig.getParameter<edm::InputTag>("PUEventWeightUpSource");   
  inTag_PUEventWeightDownSource    = iConfig.getParameter<edm::InputTag>("PUEventWeightDownSource");  
  inTag_PUEventWeight3DSource      = iConfig.getParameter<edm::InputTag>("PUEventWeight3DSource");  
  inTag_PUEventWeight3DUpSource    = iConfig.getParameter<edm::InputTag>("PUEventWeight3DUpSource");   
  inTag_PUEventWeight3DDownSource  = iConfig.getParameter<edm::InputTag>("PUEventWeight3DDownSource");
  inTag_defaultEventWeight         = iConfig.getParameter<edm::InputTag>("DefEventWeight"); 
}

PUControlDistributionsAnalyzer::~PUControlDistributionsAnalyzer(){}

// =============================

void PUControlDistributionsAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;

  // Histograms for PU Events

  histoNPU = fs->make<TH1F>("pileup",";Number of PU Events (Unweighted);Frequency",71,-0.5,70.5);
  histoNPU -> SetFillColor(2);  

  histoNPUReweighted = fs->make<TH1F>("pileup_reweighted",";Number of PU Events (Reweighted);Frequency",71,-0.5,70.5);
  histoNPUReweighted -> SetFillColor(2);

  histoNPUReweightedScaleUp = fs->make<TH1F>("pileup_reweighted_up",";Number of PU Events (Reweighted, Scale Up);Frequency",71,-0.5,70.5);
  histoNPUReweightedScaleUp -> SetFillColor(2);

  histoNPUReweightedScaleDown = fs->make<TH1F>("pileup_reweighted_down",";Number of PU Events (Reweighted, Scale Down);Frequency",71,-0.5,70.5);
  histoNPUReweightedScaleDown -> SetFillColor(2);

  histoNPUReweighted3D = fs->make<TH1F>("pileup_reweighted3D",";Number of PU Events (Reweighted 3D);Frequency",71,-0.5,70.5);
  histoNPUReweighted3D -> SetFillColor(2);

  histoNPUReweighted3DScaleUp = fs->make<TH1F>("pileup_reweighted3D_up",";Number of PU Events (Reweighted 3D, Scale Up);Frequency",71,-0.5,70.5);
  histoNPUReweighted3DScaleUp -> SetFillColor(2);

  histoNPUReweighted3DScaleDown = fs->make<TH1F>("pileup_reweighted3D_down",";Number of PU Events (Reweighted 3D, Scale Down);Frequency",71,-0.5,70.5);
  histoNPUReweighted3DScaleDown -> SetFillColor(2);

  // Histograms for Primary Vertices

  histoNPVertex = fs->make<TH1F>("npvertex",";Number of Primary Vertices (Unweighted);Frequency",71,-0.5,70.5);
  histoNPVertex -> SetFillColor(2);

  histoNPVertexReweighted = fs->make<TH1F>("npvertex_reweighted",";Number of Primary Vertices (Reweighted);Frequency",71,-0.5,70.5);
  histoNPVertexReweighted -> SetFillColor(2);  

  histoNPVertexReweightedScaleUp = fs->make<TH1F>("npvertex_reweighted_up",";Number of Primary Vertices (Reweighted, Scale Up);Frequency",71,-0.5,70.5);
  histoNPVertexReweightedScaleUp -> SetFillColor(2);

  histoNPVertexReweightedScaleDown = fs->make<TH1F>("npvertex_reweighted_down",";Number of Primary Vertices (Reweighted, Scale Down);Frequency",71,-0.5,70.5);
  histoNPVertexReweightedScaleDown -> SetFillColor(2);

  histoNPVertexReweighted3D = fs->make<TH1F>("npvertex_reweighted3D",";Number of Primary Vertices (Reweighted 3D);Frequency",71,-0.5,70.5);
  histoNPVertexReweighted3D -> SetFillColor(2);  

  histoNPVertexReweighted3DScaleUp = fs->make<TH1F>("npvertex_reweighted3D_up",";Number of Primary Vertices (Reweighted 3D, Scale Up);Frequency",71,-0.5,70.5);
  histoNPVertexReweighted3DScaleUp -> SetFillColor(2);

  histoNPVertexReweighted3DScaleDown = fs->make<TH1F>("npvertex_reweighted3D_down",";Number of Primary Vertices (Reweighted 3D, Scale Down);Frequency",71,-0.5,70.5);
  histoNPVertexReweighted3DScaleDown -> SetFillColor(2);

  // Histograms for Event Weights

  histoEventWeights = fs->make<TH1F>("eventweights",";Event Weights;Frequency",200,-1,3); 
  histoEventWeights -> SetFillColor(2);

  histoEventWeightsUp = fs->make<TH1F>("eventweights_up",";Event Weight (Scale Up);Frequency",200,-1,3); 
  histoEventWeightsUp -> SetFillColor(2);

  histoEventWeightsDown = fs->make<TH1F>("eventweights_down",";Event Weight (Scale Down);Frequency",200,-1,3); 
  histoEventWeightsDown -> SetFillColor(2);

  histoEventWeights3D = fs->make<TH1F>("eventweights3D",";Event Weights 3D ;Frequency",200,-1,3); 
  histoEventWeights3D -> SetFillColor(2);
		   
  histoEventWeights3DUp = fs->make<TH1F>("eventweights3D_up",";Event Weight 3D (Scale Up);Frequency",200,-1,3); 
  histoEventWeights3DUp -> SetFillColor(2);
		   
  histoEventWeights3DDown = fs->make<TH1F>("eventweights3D_down",";Event Weight 3D (Scale Down);Frequency",200,-1,3); 
  histoEventWeights3DDown -> SetFillColor(2);

  // Histograms for correlations between PU events and number of vertices

  histoNPUvsNPVertex = fs->make<TH2F>("pileup_vs_npvertex",";Number of PU Events (Unweighted) versus Number of Primary Vertices (Unweighted);Frequency",71,-0.5,70.5,71,-0.5,70.5);
  histoNPUvsNPVertex -> SetFillColor(2);    
}

// =============================

void PUControlDistributionsAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<edm::View<PileupSummaryInfo> > pPUInfo;
  iEvent.getByLabel(inTag_PUSource, pPUInfo); 

  edm::Handle<edm::View<reco::Vertex> > pPVertex;
  iEvent.getByLabel(inTag_PVertexSource, pPVertex);

  edm::Handle<double> pDefEventWeight;
  iEvent.getByLabel(inTag_defaultEventWeight, pDefEventWeight);

  if (pPVertex.isValid())
  {
    double weight = (pDefEventWeight.isValid()) ? (*pDefEventWeight) : 1.0;

    histoNPVertex -> Fill(pPVertex->size(),weight);

    if (pPUInfo.isValid())
    {
      edm::Handle<double> pPUEventWeight;
      iEvent.getByLabel(inTag_PUEventWeightSource, pPUEventWeight);

      edm::Handle<double> pPUEventWeightUp;
      iEvent.getByLabel(inTag_PUEventWeightUpSource, pPUEventWeightUp);
      
      edm::Handle<double> pPUEventWeightDown;
      iEvent.getByLabel(inTag_PUEventWeightDownSource, pPUEventWeightDown); 

      edm::Handle<double> pPUEventWeight3D;
      iEvent.getByLabel(inTag_PUEventWeight3DSource, pPUEventWeight3D);
      
      edm::Handle<double> pPUEventWeight3DUp;
      iEvent.getByLabel(inTag_PUEventWeight3DUpSource, pPUEventWeight3DUp);
     
      edm::Handle<double> pPUEventWeight3DDown;
      iEvent.getByLabel(inTag_PUEventWeight3DDownSource, pPUEventWeight3DDown);  

      double PUEventWeight        = (pPUEventWeight.isValid())        ? (*pPUEventWeight)        : 1.0;     
      double PUEventWeightUp      = (pPUEventWeightUp.isValid())      ? (*pPUEventWeightUp)      : 1.0;     
      double PUEventWeightDown    = (pPUEventWeightDown.isValid())    ? (*pPUEventWeightDown)    : 1.0;     
      double PUEventWeight3D      = (pPUEventWeight3D.isValid())      ? (*pPUEventWeight3D)      : 1.0;     
      double PUEventWeight3DUp    = (pPUEventWeight3DUp.isValid())    ? (*pPUEventWeight3DUp)    : 1.0;     
      double PUEventWeight3DDown  = (pPUEventWeight3DDown.isValid())  ? (*pPUEventWeight3DDown)  : 1.0;         

      edm::View<PileupSummaryInfo>::const_iterator iterPU;
  
      for(iterPU = pPUInfo->begin(); iterPU != pPUInfo->end(); ++iterPU)
      {    
	if (iterPU->getBunchCrossing()==0) // -1: previous BX, 0: current BX,  1: next BX
	{
	  histoNPVertexReweighted          -> Fill(pPVertex->size(),weight*PUEventWeight);
	  histoNPVertexReweightedScaleUp   -> Fill(pPVertex->size(),weight*PUEventWeightUp);
	  histoNPVertexReweightedScaleDown -> Fill(pPVertex->size(),weight*PUEventWeightDown);

	  histoNPVertexReweighted3D          -> Fill(pPVertex->size(),weight*PUEventWeight3D);
	  histoNPVertexReweighted3DScaleUp   -> Fill(pPVertex->size(),weight*PUEventWeight3DUp);
	  histoNPVertexReweighted3DScaleDown -> Fill(pPVertex->size(),weight*PUEventWeight3DDown);
	  
	  histoNPU                    -> Fill(iterPU->getTrueNumInteractions(),weight);
	  histoNPUReweighted          -> Fill(iterPU->getTrueNumInteractions(),weight*PUEventWeight);
	  histoNPUReweightedScaleUp   -> Fill(iterPU->getTrueNumInteractions(),weight*PUEventWeightUp);
	  histoNPUReweightedScaleDown -> Fill(iterPU->getTrueNumInteractions(),weight*PUEventWeightDown);

	  histoNPUReweighted3D          -> Fill(iterPU->getTrueNumInteractions(),weight*PUEventWeight3D);
	  histoNPUReweighted3DScaleUp   -> Fill(iterPU->getTrueNumInteractions(),weight*PUEventWeight3DUp);
	  histoNPUReweighted3DScaleDown -> Fill(iterPU->getTrueNumInteractions(),weight*PUEventWeight3DDown);
	  
	  histoEventWeights     -> Fill(PUEventWeight,weight);
	  histoEventWeightsUp   -> Fill(PUEventWeightUp,weight);
	  histoEventWeightsDown -> Fill(PUEventWeightDown,weight);  
	  
	  histoEventWeights3D     -> Fill(PUEventWeight3D,weight);
	  histoEventWeights3DUp   -> Fill(PUEventWeight3DUp,weight);
	  histoEventWeights3DDown -> Fill(PUEventWeight3DDown,weight);	  

	  histoNPUvsNPVertex    -> Fill(iterPU->getTrueNumInteractions(),pPVertex->size());
	}
      }
    }
  }
}

// =============================

void PUControlDistributionsAnalyzer::endJob(){}

#endif
