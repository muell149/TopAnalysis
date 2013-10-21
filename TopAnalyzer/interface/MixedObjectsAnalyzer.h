#ifndef MixedObjectsAnalyzer_h
#define MixedObjectsAnalyzer_h

#include <map>
#include <vector>
#include <string>

#include "TTree.h"
#include "TH1F.h"
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "TString.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/CompositePtrCandidate.h"

/**
   \class   MixedObjectsAnalyzer MixedObjectsAnalyzer.h "TopAnalysis/TopAnalyzer/interface/MixedObjectsAnalyzer.h"

   \brief   EDAnalyzer dealing with variables computed from different object types

   Computes quantities arising from different analysis objects such as invariant masses of jets, leptons and MET, etc. save them within a tree as well as histogram for flexible analysis input
*/

class MixedObjectsAnalyzer : public edm::EDAnalyzer {

 public:
  /// default constructor
  explicit MixedObjectsAnalyzer(const edm::ParameterSet& cfg);
  /// default destructor
  ~MixedObjectsAnalyzer();

 private:

  /// initiate histograms
  virtual void beginJob();
  /// produce n-tuple
  virtual void analyze(const edm::Event& event, const edm::EventSetup& iSetup);
  /// empty
  virtual void endJob();
  /// helper function to deal with abs(deltaphi) > pi
  double modTwoPi(double DeltaPhi);
  /// helper function to find to find non-ttbar jets
  bool findAncestor(const reco::Candidate* cand, TString decaychain);
    
  /// src's for the different infos
  edm::InputTag JetSrc_, METSrc_, MuonSrc_, ElectronSrc_,  GenJetSrc_, addGenJetSrc_, GenMETSrc_, GenLepSrc_, ingenPS_, weight_, VertexSrc_, semiLepEvt_;

  // class key of kinfit hypothesis
  std::string hypoKey_, btagAlgo_;

  /// event weight
  double weight;

  /// event identifiers
  unsigned int runNumber, luminosityBlockNumber, eventNumber;

  /// define Tree for event content
  TTree * tree;

  /// doubles
  double btagDiscr_, MuNu4J, ElNu4J, mJJ, mWJJ, mWFitJJ, mHbb, leadNonttjetPt, leadNonttjetY, leadNonttjetEta;
  double addJetPt_;
  double bqhadPtPre, bqhadEtaPre, bqhadPhiPre, bqlepPtPre, bqlepEtaPre, bqlepPhiPre, lqPtPre, lqEtaPre, lqPhiPre, lqbarPtPre, lqbarEtaPre, lqbarPhiPre, nuPtPre, nuEtaPre, nuPhiPre, lepPtPre, lepEtaPre, lepPhiPre;
  double bqhadPtFit, bqhadEtaFit, bqhadPhiFit, bqlepPtFit, bqlepEtaFit, bqlepPhiFit, lqPtFit, lqEtaFit, lqPhiFit, lqbarPtFit, lqbarEtaFit, lqbarPhiFit, nuPtFit, nuEtaFit, nuPhiFit, lepPtFit, lepEtaFit, lepPhiFit;
  double nuPtTrue, nuEtaTrue, nuPhiTrue, lepPtTrue, lepEtaTrue, lepPhiTrue, sumEtPre, sumEtTrue;
  double nPV;
  double ttbarJetMass, ttbarJetMassTrue, rhos, rhosTrue;
  double leadNonttjetPtTrue, leadNonttjetYTrue, leadNonttjetEtaTrue;
  double topPtLepFit, topPtHadFit, topYLepFit, topYHadFit, ttbarMassFit, ttbarYFit, ttbarPtFit;
  double topPtLepTrue, topPtHadTrue, topYLepTrue, topYHadTrue, ttbarMassTrue, ttbarYTrue, ttbarPtTrue;
  bool inVisPS;

  /// ints
  int BindexA, BindexB, BindexC, BindexD, Nbjets, Njets, NjetsTrue, leadNonttjetIX;

  /// histo container
  std::map< std::string, TH1F* > hists_;
  std::map< std::string, TH2F* > hists2D_;
};

#endif
