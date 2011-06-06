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

void MCPileUp::beginJob()
{
  histo_NPUEvents = new TH1F("pileup","pileup",71,-0.5,70.5);
  histo_NPUEvents -> SetTitle("");
  histo_NPUEvents -> GetXaxis() -> SetTitle("Number of PU Events");
  histo_NPUEvents -> GetYaxis() -> SetTitle("Frequency");
  histo_NPUEvents -> SetFillColor(2);
}

void MCPileUp::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   Handle<std::vector<PileupSummaryInfo> > pPUInfo;
   iEvent.getByLabel(inTag_PUSource, pPUInfo);

   std::vector<PileupSummaryInfo>::const_iterator iterPU;

   for(iterPU = pPUInfo->begin(); iterPU != pPUInfo->end(); ++iterPU)
   { 
     histo_NPUEvents->Fill(iterPU->getPU_NumInteractions());
   }
}

void MCPileUp::endJob()
{
  TFile *outfile = new TFile("MC_PUDist.root","RECREATE");
  histo_NPUEvents -> Write();
  outfile->Close();
}

void MCPileUp::beginRun(edm::Run const&, edm::EventSetup const&) {}

void MCPileUp::endRun(edm::Run const&, edm::EventSetup const&) {}

void MCPileUp::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

void MCPileUp::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

void MCPileUp::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MCPileUp);

#endif
