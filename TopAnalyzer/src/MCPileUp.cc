#ifndef MCPileUp_cc_
#define MCPileUp_cc_

#include "TopAnalysis/TopAnalyzer/interface/MCPileUp.h"

// =============================
//  constructors and destructor
// =============================

MCPileUp::MCPileUp(const edm::ParameterSet& iConfig)
{
  inTag_PUSource = iConfig.getParameter<edm::InputTag>("PUSource");  
}

MCPileUp::~MCPileUp(){}

// =============================

void MCPileUp::beginJob()
{
  edm::Service<TFileService> fs;

  histoNPUEvents = fs->make<TH1F>("pileup","Number of PU Events",71,-0.5,70.5);
  histoNPUEvents -> SetTitle("");
  histoNPUEvents -> GetXaxis() -> SetTitle("Number of PU Events");
  histoNPUEvents -> GetYaxis() -> SetTitle("Frequency");
  histoNPUEvents -> SetFillColor(2);

  histoNPUEvents3BX = fs->make<TH1F>("pileup3BX","Number of PU Events (Average over 3 BXs)",71,-0.5,70.5);
  histoNPUEvents3BX -> SetTitle("");
  histoNPUEvents3BX -> GetXaxis() -> SetTitle("Number of PU Events (Average over 3 BXs)");
  histoNPUEvents3BX -> GetYaxis() -> SetTitle("Frequency");
  histoNPUEvents3BX -> SetFillColor(2);
}

// =============================

void MCPileUp::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<edm::View<PileupSummaryInfo> > pPUInfo;
   iEvent.getByLabel(inTag_PUSource, pPUInfo);

   edm::View<PileupSummaryInfo>::const_iterator iterPU;

   float sum_nvtx = 0;

   for(iterPU = pPUInfo->begin(); iterPU != pPUInfo->end(); ++iterPU)
   { 
     sum_nvtx += iterPU->getPU_NumInteractions();

     if (iterPU->getBunchCrossing()==0) // -1: previous BX, 0: current BX,  1: next BX
     {
       histoNPUEvents->Fill(iterPU->getPU_NumInteractions());
     }
   }

   histoNPUEvents3BX->Fill(sum_nvtx/3.0);
}

// =============================

void MCPileUp::endJob(){}

#endif
