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
  inTag_PUEventWeight3BXSource     = iConfig.getParameter<edm::InputTag>("PUEventWeight3BXSource");  
  inTag_PUEventWeight3BXUpSource   = iConfig.getParameter<edm::InputTag>("PUEventWeight3BXUpSource");   
  inTag_PUEventWeight3BXDownSource = iConfig.getParameter<edm::InputTag>("PUEventWeight3BXDownSource");
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

  histoNPUReweighted3BX = fs->make<TH1F>("pileup_reweighted3BX",";Number of PU Events (Reweighted 3BX);Frequency",71,-0.5,70.5);
  histoNPUReweighted3BX -> SetFillColor(2);

  histoNPUReweighted3BXScaleUp = fs->make<TH1F>("pileup_reweighted3BX_up",";Number of PU Events (Reweighted 3BX, Scale Up);Frequency",71,-0.5,70.5);
  histoNPUReweighted3BXScaleUp -> SetFillColor(2);

  histoNPUReweighted3BXScaleDown = fs->make<TH1F>("pileup_reweighted3BX_down",";Number of PU Events (Reweighted 3BX, Scale Down);Frequency",71,-0.5,70.5);
  histoNPUReweighted3BXScaleDown -> SetFillColor(2);

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

  histoNPVertexReweighted3BX = fs->make<TH1F>("npvertex_reweighted3BX",";Number of Primary Vertices (Reweighted 3BX);Frequency",71,-0.5,70.5);
  histoNPVertexReweighted3BX -> SetFillColor(2);  

  histoNPVertexReweighted3BXScaleUp = fs->make<TH1F>("npvertex_reweighted3BX_up",";Number of Primary Vertices (Reweighted 3BX, Scale Up);Frequency",71,-0.5,70.5);
  histoNPVertexReweighted3BXScaleUp -> SetFillColor(2);

  histoNPVertexReweighted3BXScaleDown = fs->make<TH1F>("npvertex_reweighted3BX_down",";Number of Primary Vertices (Reweighted 3BX, Scale Down);Frequency",71,-0.5,70.5);
  histoNPVertexReweighted3BXScaleDown -> SetFillColor(2);

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

  histoEventWeights3BX = fs->make<TH1F>("eventweights3BX",";Event Weights 3BX ;Frequency",200,-1,3); 
  histoEventWeights3BX -> SetFillColor(2);
		   
  histoEventWeights3BXUp = fs->make<TH1F>("eventweights3BX_up",";Event Weight 3BX (Scale Up);Frequency",200,-1,3); 
  histoEventWeights3BXUp -> SetFillColor(2);
		   
  histoEventWeights3BXDown = fs->make<TH1F>("eventweights3BX_down",";Event Weight 3BX (Scale Down);Frequency",200,-1,3); 
  histoEventWeights3BXDown -> SetFillColor(2); 

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
    double weight = (pDefEventWeight.isValid()) ? (*pDefEventWeight) : 1;

    histoNPVertex -> Fill(pPVertex->size(),weight);

    if (pPUInfo.isValid())
    {
      edm::Handle<double> pPUEventWeight;
      iEvent.getByLabel(inTag_PUEventWeightSource, pPUEventWeight);
      
      edm::Handle<double> pPUEventWeightUp;
      iEvent.getByLabel(inTag_PUEventWeightUpSource, pPUEventWeightUp);
      
      edm::Handle<double> pPUEventWeightDown;
      iEvent.getByLabel(inTag_PUEventWeightDownSource, pPUEventWeightDown); 

      edm::Handle<double> pPUEventWeight3BX;
      iEvent.getByLabel(inTag_PUEventWeight3BXSource, pPUEventWeight3BX);
      
      edm::Handle<double> pPUEventWeight3BXUp;
      iEvent.getByLabel(inTag_PUEventWeight3BXUpSource, pPUEventWeight3BXUp);
      
      edm::Handle<double> pPUEventWeight3BXDown;
      iEvent.getByLabel(inTag_PUEventWeight3BXDownSource, pPUEventWeight3BXDown);   

      edm::Handle<double> pPUEventWeight3D;
      iEvent.getByLabel(inTag_PUEventWeight3DSource, pPUEventWeight3D);
      
      edm::Handle<double> pPUEventWeight3DUp;
      iEvent.getByLabel(inTag_PUEventWeight3DUpSource, pPUEventWeight3DUp);
      
      edm::Handle<double> pPUEventWeight3DDown;
      iEvent.getByLabel(inTag_PUEventWeight3DDownSource, pPUEventWeight3DDown);  
      
      edm::View<PileupSummaryInfo>::const_iterator iterPU;
  
      for(iterPU = pPUInfo->begin(); iterPU != pPUInfo->end(); ++iterPU)
      {    
	if (iterPU->getBunchCrossing()==0) // -1: previous BX, 0: current BX,  1: next BX
	{
	  histoNPVertexReweighted          -> Fill(pPVertex->size(),weight*(*pPUEventWeight));
	  histoNPVertexReweightedScaleUp   -> Fill(pPVertex->size(),weight*(*pPUEventWeightUp));
	  histoNPVertexReweightedScaleDown -> Fill(pPVertex->size(),weight*(*pPUEventWeightDown));

	  histoNPVertexReweighted3BX          -> Fill(pPVertex->size(),weight*(*pPUEventWeight3BX));
	  histoNPVertexReweighted3BXScaleUp   -> Fill(pPVertex->size(),weight*(*pPUEventWeight3BXUp));
	  histoNPVertexReweighted3BXScaleDown -> Fill(pPVertex->size(),weight*(*pPUEventWeight3BXDown));

	  histoNPVertexReweighted3D          -> Fill(pPVertex->size(),weight*(*pPUEventWeight3D));
	  histoNPVertexReweighted3DScaleUp   -> Fill(pPVertex->size(),weight*(*pPUEventWeight3DUp));
	  histoNPVertexReweighted3DScaleDown -> Fill(pPVertex->size(),weight*(*pPUEventWeight3DDown));
	  
	  histoNPU                    -> Fill(iterPU->getPU_NumInteractions(),weight);
	  histoNPUReweighted          -> Fill(iterPU->getPU_NumInteractions(),weight*(*pPUEventWeight));
	  histoNPUReweightedScaleUp   -> Fill(iterPU->getPU_NumInteractions(),weight*(*pPUEventWeightUp));
	  histoNPUReweightedScaleDown -> Fill(iterPU->getPU_NumInteractions(),weight*(*pPUEventWeightDown));

	  histoNPUReweighted3BX          -> Fill(iterPU->getPU_NumInteractions(),weight*(*pPUEventWeight3BX));
	  histoNPUReweighted3BXScaleUp   -> Fill(iterPU->getPU_NumInteractions(),weight*(*pPUEventWeight3BXUp));
	  histoNPUReweighted3BXScaleDown -> Fill(iterPU->getPU_NumInteractions(),weight*(*pPUEventWeight3BXDown));

	  histoNPUReweighted3D          -> Fill(iterPU->getPU_NumInteractions(),weight*(*pPUEventWeight3D));
	  histoNPUReweighted3DScaleUp   -> Fill(iterPU->getPU_NumInteractions(),weight*(*pPUEventWeight3DUp));
	  histoNPUReweighted3DScaleDown -> Fill(iterPU->getPU_NumInteractions(),weight*(*pPUEventWeight3DDown));
	  
	  histoEventWeights     -> Fill((*pPUEventWeight),weight);
	  histoEventWeightsUp   -> Fill((*pPUEventWeightUp),weight);
	  histoEventWeightsDown -> Fill((*pPUEventWeightDown),weight);  
	  
	  histoEventWeights3BX     -> Fill((*pPUEventWeight3BX),weight);
	  histoEventWeights3BXUp   -> Fill((*pPUEventWeight3BXUp),weight);
	  histoEventWeights3BXDown -> Fill((*pPUEventWeight3BXDown),weight);
 
	  histoEventWeights3D     -> Fill((*pPUEventWeight3D),weight);
	  histoEventWeights3DUp   -> Fill((*pPUEventWeight3DUp),weight);
	  histoEventWeights3DDown -> Fill((*pPUEventWeight3DDown),weight);	  

	  histoNPUvsNPVertex    -> Fill(iterPU->getPU_NumInteractions(),pPVertex->size());
	}
      }
    }
  }
}

// =============================

void PUControlDistributionsAnalyzer::endJob(){}

#endif
