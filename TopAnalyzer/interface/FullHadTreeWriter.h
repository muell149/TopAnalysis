#ifndef FullHadTreeWriter_h
#define FullHadTreeWriter_h

#include <map>
#include <vector>

#include "TTree.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "FWCore/Framework/interface/MakerMacros.h"
//#include "FWCore/ServiceRegistry/interface/Service.h"
//#include "FWCore/Utilities/interface/EDMException.h"

#include "AnalysisDataFormats/TopObjects/interface/TtFullHadronicEvent.h"

#include "RecoBTag/Records/interface/BTagPerformanceRecord.h"
#include "RecoBTag/PerformanceDB/interface/BtagPerformance.h"
#include "CondFormats/PhysicsToolsObjects/interface/BinningPointByMap.h"

/**
   \class   FullHadTreeWriter FullHadTreeWriter.h "TopAnalysis/TopAnalyzer/interface/FullHadTreeWriter.h"

   \brief   EDAnalyzer to produce TTrees with important variables for faster analysis

   Produce TTrees for faster analysis with fully hadronic ttbar events
*/

class FullHadTreeWriter : public edm::EDAnalyzer {

 public:
  /// default constructor
  explicit FullHadTreeWriter(const edm::ParameterSet& cfg);
  /// default destructor
  ~FullHadTreeWriter();

 private:

  /// initiate histograms
  virtual void beginJob();
  /// produce n-tuple
  virtual void analyze(const edm::Event& event, const edm::EventSetup& iSetup);
  /// empty
  virtual void endJob();

  /// function to find types of jet-combinations in KinFits (1 right, 2 branches right, but inner-branche particles mixup, 3 inter-branch mixup, 4 missing jet)
  int comboType(edm::Handle<TtFullHadronicEvent> fullHadEvent_h);

  /// src's for the different infos
  edm::InputTag JetSrc_, FitSrc_, GenSrc_;

  /// bTag infos
  std::vector<std::string> bTagName_, bTagVal_;
  std::map<std::string,PerformanceResult::ResultType> measureMap;

  /// define Tree for event content
  TTree * tree;

  // Max possible number of jets in events
  const unsigned short kMAX;

  // Max entries in bTag array of jets in events
  unsigned int kBTagMAX;

  /// define variables for tree
  
  // bools
  bool doPDFUncertainty;

  // shorts
  short * fitAssigns;
  short * pdgId;
  short * partonFlavour;
  short comboTypeValue;

  // unsigned shorts

  // ints
  int Njet;
  int id1, id2;

  // unsigend ints
  unsigned int runNumber, luminosityBlockNumber, eventNumber;

  // longs

  // unsigend longs

  // floats
  float weight;
  float *bTag_TCHE, * bTag_TCHP, * bTag_SSVHE, * bTag_SSVHP, * bTag_CSV, * bTag_CSVMVA;
  float prob, chi2, topMass;
  float Q;

  // doubles
  double x1, x2;

  // TClonesArray(TLorentzVectors)
  TClonesArray * jets, * fitVecs;

};

#endif
