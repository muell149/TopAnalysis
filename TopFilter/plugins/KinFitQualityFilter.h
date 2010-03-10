#ifndef KinFitQualityFilter_h
#define KinFitQualityFilter_h

#include <TString.h>

#include "FWCore/Framework/interface/EDFilter.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullHadronicEvent.h"

class KinFitQualityFilter : public edm::EDFilter {

 public:

  explicit KinFitQualityFilter(const edm::ParameterSet&);
  ~KinFitQualityFilter(){};
  
 private:

  virtual void beginJob();
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob();

 private:
  
  edm::InputTag srcA_;
  edm::InputTag srcB_;
  int whichFit_;
  double maxChi2_;
  double minChi2_;
  double maxProb_;
  double minProb_;
  double maxbQuarkPt_;
  double minbQuarkPt_;
  double maxbQuarkEta_;
  double minbQuarkEta_;
  double maxbQuarkPhi_;
  double minbQuarkPhi_;
  double maxlightQuarkPt_;
  double minlightQuarkPt_;
  double maxlightQuarkEta_;
  double minlightQuarkEta_;
  double maxlightQuarkPhi_;
  double minlightQuarkPhi_;
  bool useEventWeight_;
  edm::InputTag weight_;

  unsigned int beforeCut_;
  unsigned int afterCut_;
  double beforeCutWeighted_;
  double afterCutWeighted_;
};

#endif
