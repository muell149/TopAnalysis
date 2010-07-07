#ifndef FullLepHypothesesFilter_h
#define FullLepHypothesesFilter_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "AnalysisDataFormats/TopObjects/interface/TtFullLeptonicEvent.h"

/**
   \class   FullLepHypothesesFilter FullLepHypothesesFilter.h "TopAnalysis/TopFilter/plugins/FullLepHypothesesFilter.h"

   \brief   Filter on FullLeptonicEvent hypotheses cuts on invariant lepton lepton mass or b-tags can be applied

   The class vetos events without valid solution for the event hypothesis. It also allows to veto on events where the 
   invariant mass of the two leptons from the event solution lies between two values given in the config-file or with 
   an invariant mass lower than a certain value. A cut on the b-tagging discriminator of one or both jets can be applied. 
   The b-tagging algorithm as the cut(s) can be steered in the config-file
*/

class FullLepHypothesesFilter : public edm::EDFilter {

 public:
  /// default constructor
  explicit FullLepHypothesesFilter(const edm::ParameterSet&);
  /// default destructor
  ~FullLepHypothesesFilter(){};
  
 private:
  /// prints out a summary of the applied cuts if 'topFilter' is appended to message logger
  virtual void beginJob();
  /// filters events on validity, invariant dilepton mass and b-taggging 
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  /// gives a summary of how many events passed each cut if 'topFilter' is appended to message logger 
  virtual void endJob();

 private:
  /// choose in config file which hypothesis type you want to be filtered
  edm::InputTag hypoKey_;  
  /// input is the ttFullLepEvent 
  edm::InputTag FullLepEvt_;
  /// event weight (needed for ouput summary)
  edm::InputTag wgt_;
  /// needed for b-tagging cuts and has to be the same collection which has been used for event  reconstruction
  edm::InputTag jets_;
  
  /// veto cut on low mass resonances like J/Psi, default is 20GeV
  double qcdCut_;
  /// veto cuts on Z-mass, default values are (80GeV, 105GeV)
  std::vector<double> zCut_;
  /// b-Tagging to be used, default is 'simpleSecondaryVertexBJetTags'  
  std::string bAlgo_;
  /// cut value(s) of the b-tagging discriminator, default is 1 (only one tag required with simpleSV)
  std::vector<double> bDisc_; 

  /// event counter for events before cuts are applied
  unsigned int beforeCuts_;
  /// event counter for events with valid event solution
  unsigned int validCounter_;  
  /// event counter for events which pass the dilepton mass cut
  unsigned int betweenCuts_;  
  /// event counter for events after all cuts
  unsigned int afterCuts_;
  
  /// event counter for weighted number of events before cuts are applied
  double beforeCutsWeighted_;
  /// event counter for weighted number of events with valid event solution
  double validCounterWeighted_;  
  /// event counter for weighted number of events which pass the dilepton mass cut
  double betweenCutsWeighted_;
  /// event counter for weighted number of events after all cuts
  double afterCutsWeighted_;
};

#endif
