#ifndef EventWeightAnalyzer_cc_
#define EventWeightAnalyzer_cc_

#include "TopAnalysis/TopAnalyzer/interface/EventWeightAnalyzer.h"

// =============================
//  constructors and destructor
// =============================

EventWeightAnalyzer::EventWeightAnalyzer(const edm::ParameterSet& iConfig)
{
  inTag_EventWeight                = iConfig.getParameter<edm::InputTag>("EventWeightSrc");  
}

EventWeightAnalyzer::~EventWeightAnalyzer(){}

// =============================

void EventWeightAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;

  // Histograms for PU Events

  histoEventWeightAbs  = fs->make<TH1F>("histoEventWeightAbs" ,";Event Weights;Frequency",2001, -1000. , 1000. );
  histoEventWeightAbs  -> Sumw2();  

  histoEventWeightNorm = fs->make<TH1F>("histoEventWeightNorm",";Event Weights;Frequency",   3,    -1.5,    1.5);
  histoEventWeightNorm -> Sumw2();  


}

// =============================

void EventWeightAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<double> pEventWeight;
  iEvent.getByLabel(inTag_EventWeight, pEventWeight);

  double weightAbs  = (pEventWeight.isValid()) ? (*pEventWeight)                     : 0.;
  double weightNorm = (pEventWeight.isValid()) ? (*pEventWeight)/fabs(*pEventWeight) : 0.;

  histoEventWeightAbs  -> Fill( weightAbs , 1.);
  histoEventWeightNorm -> Fill( weightNorm, 1.);

}

// =============================

void EventWeightAnalyzer::endJob(){}

#endif
