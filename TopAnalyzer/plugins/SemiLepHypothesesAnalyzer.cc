#include "TopAnalysis/TopAnalyzer/plugins/SemiLepHypothesesAnalyzer.h"

#include "AnalysisDataFormats/TopObjects/interface/TtSemiEvent.h"

SemiLepHypothesesAnalyzer::SemiLepHypothesesAnalyzer(const edm::ParameterSet& cfg):
  semiEvt_(cfg.getParameter<edm::InputTag>("semiEvent"))
{
}

void
SemiLepHypothesesAnalyzer::analyze(const edm::Event& evt, const edm::EventSetup& setup)
{

  edm::Handle<TtSemiEvent> semiEvt;
  evt.getByLabel(semiEvt_, semiEvt);

  std::cout << "numberOfAvailableHypos = " << semiEvt->numberOfAvailableHypos() << std::endl;

}

void 
SemiLepHypothesesAnalyzer::beginJob(const edm::EventSetup&)
{
}

void
SemiLepHypothesesAnalyzer::endJob() 
{
}
