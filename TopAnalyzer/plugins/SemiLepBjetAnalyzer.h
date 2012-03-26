#ifndef SemiLepBjetAnalyzer_h
#define SemiLepBjetAnalyzer_h

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"

#include "DataFormats/JetReco/interface/GenJet.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"


/**
   \class   SemiLepBjetAnalyzer.cc SemiLepBjetAnalyzer.h "TopAnalysis/TopAnalyzer/interface/SemiLepBjetAnalyzer.h"

   \brief   Derived class to analyze the kinematics of b-jets on reconstruction level (kinfit output) and generator level (genjets from)
   
   The structure keeps histograms for the kinematics of bjets. These histograms are filled either from the TtSemiLeptonicEvent class (reconstruction level) or from the specified genjet collection. In the latter case the identification as done in the GenLevelBJetProducer (from TopAnalysis/TopUtils) is used. Furthermore, also the correlation plot between reconstructed and generated quantity is filled. The lepton charge is used to identify the b and bbar jets from the kinematic fit output. Both (b and bbar) are always drawn in the same histogram.   
*/

class SemiLepBjetAnalyzer : public edm::EDAnalyzer {

 public:

  explicit SemiLepBjetAnalyzer(const edm::ParameterSet&);
  ~SemiLepBjetAnalyzer(){};
  
 private:

  // ---
  //    functions
  // ---  
  // default (framework)
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  // helper functions to get b and bbar jet 
  // a) from kinfit hypothesis
  std::pair<const reco::Candidate*,const reco::Candidate*> getbJets(const edm::Handle<TtSemiLeptonicEvent> semiLepEvt, const std::string hypoKey_);
  // b) from genJet collection
  const reco::GenJet* getJetFromCollection(const reco::GenJetCollection& genJets, int IX);
  // ---
  //    inputs
  // ---
  // kinfit output
  edm::InputTag semiLepEvt_;
  // class key of kinfit hypothesis
  std::string hypoKey_;
  // genJet collection 
  edm::InputTag genJets_;
  // output manager
  int verbose;
  // event weight
  edm::InputTag weight_;
  // create gen plots?
  bool genPlots_;
  // create rec plots?
  bool recPlots_;
  // from gen level b-jet identification  
  edm::InputTag bHadJetIdx_, antibHadJetIdx_;

  // ---
  //    define Tree for event content
  // ---
  TTree * tree;
  bool useTree_;
  unsigned int runNumber, luminosityBlockNumber, eventNumber;
  double valueBqPtRec;
  double valueBqPtGen;
  double valueBqEtaRec;
  double valueBqEtaGen;
  double valueBqYRec;
  double valueBqYGen;
  double valueBbarqPtRec;
  double valueBbarqPtGen;
  double valueBbarqEtaRec;
  double valueBbarqEtaGen;
  double valueBbarqYRec;
  double valueBbarqYGen;

  // ---
  //    histos
  // ---
  TH1F* bqPtRec;
  TH1F* bqPtGen;

  TH1F* bqEtaRec;
  TH1F* bqEtaGen;

  TH1F* bqYRec;
  TH1F* bqYGen;

  TH2F* bqPt_;
  TH2F* bqEta_;
  TH2F* bqY_;

};

#endif
