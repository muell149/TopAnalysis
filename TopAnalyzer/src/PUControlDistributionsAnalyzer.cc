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
  inTag_defaultEventWeight      = iConfig.getParameter<edm::InputTag>("DefEventWeight"); 
  inTag_MCSampleTag             = iConfig.getParameter<std::string>("MCSampleTag");     
}

PUControlDistributionsAnalyzer::~PUControlDistributionsAnalyzer(){}

// =============================

void PUControlDistributionsAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;

  // Histograms for PU Events

  histoNPU = fs->make<TH1F>("pileup",";Number of PU Events (Unweighted);Frequency",710,0.,71);
  histoNPU -> SetFillColor(2);  

  histoNPUReweighted = fs->make<TH1F>("pileup_reweighted",";Number of PU Events (Reweighted);Frequency",710,0.,71.);
  histoNPUReweighted -> SetFillColor(2);

  histoNPUReweightedScaleUp = fs->make<TH1F>("pileup_reweighted_up",";Number of PU Events (Reweighted, Scale Up);Frequency",710,0.,71.);
  histoNPUReweightedScaleUp -> SetFillColor(2);

  histoNPUReweightedScaleDown = fs->make<TH1F>("pileup_reweighted_down",";Number of PU Events (Reweighted, Scale Down);Frequency",710,0.,71.);
  histoNPUReweightedScaleDown -> SetFillColor(2);

  // Histograms for Primary Vertices

  histoNPVertex = fs->make<TH1F>("npvertex",";Number of Primary Vertices (Unweighted);Frequency",710,0.,71.);
  histoNPVertex -> SetFillColor(2);

  histoNPVertexReweighted = fs->make<TH1F>("npvertex_reweighted",";Number of Primary Vertices (Reweighted);Frequency",710,0.,71.);
  histoNPVertexReweighted -> SetFillColor(2);  

  histoNPVertexReweightedScaleUp = fs->make<TH1F>("npvertex_reweighted_up",";Number of Primary Vertices (Reweighted, Scale Up);Frequency",710,0.,71.);
  histoNPVertexReweightedScaleUp -> SetFillColor(2);

  histoNPVertexReweightedScaleDown = fs->make<TH1F>("npvertex_reweighted_down",";Number of Primary Vertices (Reweighted, Scale Down);Frequency",710,0.,71.);
  histoNPVertexReweightedScaleDown -> SetFillColor(2);

  // Histograms for Event Weights

  histoEventWeights = fs->make<TH1F>("eventweights",";Event Weights;Frequency",300,-1,5); 
  histoEventWeights -> SetFillColor(2);

  histoEventWeightsUp = fs->make<TH1F>("eventweights_up",";Event Weight (Scale Up);Frequency",300,-1,5); 
  histoEventWeightsUp -> SetFillColor(2);

  histoEventWeightsDown = fs->make<TH1F>("eventweights_down",";Event Weight (Scale Down);Frequency",300,-1,5); 
  histoEventWeightsDown -> SetFillColor(2);

  // Histograms for correlations between PU events and number of vertices

  histoNPUvsNPVertex = fs->make<TH2F>("pileup_vs_npvertex",";Number of PU Events (Unweighted) versus Number of Primary Vertices (Unweighted);Frequency",71,0.,71.,71,0.,71.);
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
    
    // FIXME DEBUG MARTIN
    //if(weight==1.0) std::cout << "NONPUweight=1!!!!" << std::endl;

    histoNPVertex -> Fill(pPVertex->size(),weight);

    if (pPUInfo.isValid())
    {
      edm::Handle<double> pPUEventWeight;
      iEvent.getByLabel(inTag_PUEventWeightSource, pPUEventWeight);

      edm::Handle<double> pPUEventWeightUp;
      iEvent.getByLabel(inTag_PUEventWeightUpSource, pPUEventWeightUp);
      
      edm::Handle<double> pPUEventWeightDown;
      iEvent.getByLabel(inTag_PUEventWeightDownSource, pPUEventWeightDown); 

      double PUEventWeight        = (pPUEventWeight.isValid())        ? (*pPUEventWeight)        : 1.0;     
      double PUEventWeightUp      = (pPUEventWeightUp.isValid())      ? (*pPUEventWeightUp)      : 1.0;     
      double PUEventWeightDown    = (pPUEventWeightDown.isValid())    ? (*pPUEventWeightDown)    : 1.0;     

      // FIXME DEBUG MARTIN
      //if(PUEventWeight==1.0) std::cout << "PUEventWeight=1!!!!" << std::endl;
      edm::View<PileupSummaryInfo>::const_iterator iterPU;

      double NPUEvents;

      for(iterPU = pPUInfo->begin(); iterPU != pPUInfo->end(); ++iterPU)
      {    
	if (iterPU->getBunchCrossing()==0) // -1: previous BX, 0: current BX,  1: next BX
	{

	  histoNPVertexReweighted          -> Fill(pPVertex->size(),weight*PUEventWeight);
	  histoNPVertexReweightedScaleUp   -> Fill(pPVertex->size(),weight*PUEventWeightUp);
	  histoNPVertexReweightedScaleDown -> Fill(pPVertex->size(),weight*PUEventWeightDown);

	  if      (inTag_MCSampleTag == "Fall11" || inTag_MCSampleTag == "Summer12") NPUEvents = iterPU->getTrueNumInteractions();
	  else if (inTag_MCSampleTag == "Summer11") NPUEvents = iterPU->getPU_NumInteractions(); 
	  else NPUEvents = -1;

	  histoNPU                    -> Fill(NPUEvents,weight);
	  histoNPUReweighted          -> Fill(NPUEvents,weight*PUEventWeight);
	  histoNPUReweightedScaleUp   -> Fill(NPUEvents,weight*PUEventWeightUp);
	  histoNPUReweightedScaleDown -> Fill(NPUEvents,weight*PUEventWeightDown);

	  histoEventWeights     -> Fill(PUEventWeight,weight);
	  histoEventWeightsUp   -> Fill(PUEventWeightUp,weight);
	  histoEventWeightsDown -> Fill(PUEventWeightDown,weight);  

	  histoNPUvsNPVertex    -> Fill(NPUEvents,pPVertex->size());
	}
      }
    }
  }
}

// =============================

void PUControlDistributionsAnalyzer::endJob(){}

#endif
