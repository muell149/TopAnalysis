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

  /// function to find types of jet-combinations in KinFits (1 right, 2 one branche right, other branch inner-branch mixup, 3 both branches inner-branch mixup, 4 cross-branch mixup, -1 to -6 number of falsely picked jets)
  short comboType(short comboTypeID);
  short comboTypeIDCalculator(edm::Handle<TtFullHadronicEvent> fullHadEvent_h, unsigned int whichCombo = 0);
  short comboTypeAlgo(std::vector<int> jetIndexFit, std::vector<int> jetIndexGen);
  std::vector<int> comboTypeAlgoInverted(std::vector<int> jetIndexGen, short comboType);
  void TEST();
  short TESTHelper(int genArray[6]);

  /// src's for the different infos
  edm::InputTag JetSrc_, METSrc_, MuonSrc_, ElectronSrc_, GluonTagSrc_, /*GenJetSrc_, GenPartonSrc_,*/ FitSrc_, GenMatch2Src_, MultiJetMVADiscSrc_, GenSrc_, PUSrc_, VertexSrc_, PUWeightSrc_;

  /// MC weight
  double MCweight_;

  /// bTag infos
  std::vector<std::string> bTagName_, bTagVal_;
  std::map<std::string,PerformanceResult::ResultType> measureMap;

  /// define Tree for event content
  TTree * tree;

  // should variables for pdf uncertainties be saved to the tree
  bool DoPDFUncertainty_;

  // max possible number of jets in events
  const unsigned short kMAX;

  // max possible number of permutations per event
  const unsigned int kMAXCombo;

  // check if jet is a PFJet
  bool checkedIsPFJet, isPFJet;

  // check if jet has L7Parton corrections
  bool checkedHasL7PartonCor, hasL7PartonCor;

  // check if QGTag is embedded into the jet
  bool checkedQGTag, hasQGTag;

  /// define variables for tree
  
  // bools

  // shorts
  short * fitAssigns;
  short * pdgId;
  short * partonFlavour;
  short * jetConst;
  short * chargeMulti;
  short * comboTypes;
  short * comboTypeIDs;
  short comboTypeID;
  short comboTypeValue;
  short nPU   , nPUnext   , nPUprev   ;
  short nPUTru, nPUnextTru, nPUprevTru;
  short nVertex;
  short eventType;

  // unsigned shorts
  unsigned short TCHE_Bjets, TCHP_Bjets, SSVHE_Bjets, SSVHP_Bjets, CSV_Bjets, CSVMVA_Bjets, SM_Bjets;

  // ints
  int Njet;
  int id1, id2;

  // unsigend ints
  unsigned int nCombos;
  unsigned int runNumber, luminosityBlockNumber, eventNumber;

  // longs

  // unsigend longs

  // floats
  float * bTag_TCHE      , * bTag_TCHP      , * bTag_SSVHE      , * bTag_SSVHP      , * bTag_CSV, * bTag_CSVMVA;
  float * bTag_TCHE_SF   , * bTag_TCHP_SF   , * bTag_SSVHE_SF   , * bTag_SSVHP_SF   , * bTag_CSV_SF;   
  float * bTag_TCHE_SF_Un, * bTag_TCHP_SF_Un, * bTag_SSVHE_SF_Un, * bTag_SSVHP_SF_Un, * bTag_CSV_SF_Un;
  float * mTag_TCHE_SF   , * mTag_TCHP_SF   , * mTag_SSVHE_SF   , * mTag_SSVHP_SF   , * mTag_CSV_SF;   
  float * mTag_TCHE_SF_Un, * mTag_TCHP_SF_Un, * mTag_SSVHE_SF_Un, * mTag_SSVHP_SF_Un, * mTag_CSV_SF_Un;
  float * charge, * fChHad, * fNeHad, * fChEm, * fNeEm, * fElec, * fPhot, * fMuon;
  float Q;

  float * gluonTag;

  float H, Ht, Ht123, Ht3jet, sqrt_s, Et56, M3;

  float * EtSin2Theta    , * theta    , * sinTheta    , * EtStar    , * thetaStar    , * sinThetaStar;
  float   EtSin2Theta3jet,   theta3jet,   sinTheta3jet,   EtStar3jet,   thetaStar3jet,   sinThetaStar3jet;
							     
  float pt1_pt6, pt1_pt5, pt1_pt4, pt1_pt3, pt1_pt2;
  float pt2_pt6, pt2_pt5, pt2_pt4, pt2_pt3;
  float pt3_pt6, pt3_pt5, pt3_pt4;
  float pt4_pt6, pt4_pt5;
  float pt5_pt6;
  float pt1_pt6_norm, pt1_pt5_norm, pt1_pt4_norm, pt1_pt3_norm, pt1_pt2_norm;
  float pt2_pt6_norm, pt2_pt5_norm, pt2_pt4_norm, pt2_pt3_norm;
  float pt3_pt6_norm, pt3_pt5_norm, pt3_pt4_norm;
  float pt4_pt6_norm, pt4_pt5_norm;
  float pt5_pt6_norm;

  float jet1_etaetaMoment, jet2_etaetaMoment, jet3_etaetaMoment, jet4_etaetaMoment, jet5_etaetaMoment, jet6_etaetaMoment;
  float jet1_etaphiMoment, jet2_etaphiMoment, jet3_etaphiMoment, jet4_etaphiMoment, jet5_etaphiMoment, jet6_etaphiMoment;
  float jet1_phiphiMoment, jet2_phiphiMoment, jet3_phiphiMoment, jet4_phiphiMoment, jet5_phiphiMoment, jet6_phiphiMoment;

  float jet1_etaetaMomentMoment, jet2_etaetaMomentMoment, jet3_etaetaMomentMoment, jet4_etaetaMomentMoment, jet5_etaetaMomentMoment, jet6_etaetaMomentMoment;
  float jet1_etaphiMomentMoment, jet2_etaphiMomentMoment, jet3_etaphiMomentMoment, jet4_etaphiMomentMoment, jet5_etaphiMomentMoment, jet6_etaphiMomentMoment;
  float jet1_phiphiMomentMoment, jet2_phiphiMomentMoment, jet3_phiphiMomentMoment, jet4_phiphiMomentMoment, jet5_phiphiMomentMoment, jet6_phiphiMomentMoment;

  float jets_etaetaMoment, jets_etaphiMoment, jets_phiphiMoment;

  float jet1_etaetaMomentLogEt, jet2_etaetaMomentLogEt, jet3_etaetaMomentLogEt, jet4_etaetaMomentLogEt, jet5_etaetaMomentLogEt, jet6_etaetaMomentLogEt;
  float jet1_etaphiMomentLogEt, jet2_etaphiMomentLogEt, jet3_etaphiMomentLogEt, jet4_etaphiMomentLogEt, jet5_etaphiMomentLogEt, jet6_etaphiMomentLogEt;
  float jet1_phiphiMomentLogEt, jet2_phiphiMomentLogEt, jet3_phiphiMomentLogEt, jet4_phiphiMomentLogEt, jet5_phiphiMomentLogEt, jet6_phiphiMomentLogEt;

  float jet1_etaetaMomentMomentLogEt, jet2_etaetaMomentMomentLogEt, jet3_etaetaMomentMomentLogEt, jet4_etaetaMomentMomentLogEt, jet5_etaetaMomentMomentLogEt, jet6_etaetaMomentMomentLogEt;
  float jet1_etaphiMomentMomentLogEt, jet2_etaphiMomentMomentLogEt, jet3_etaphiMomentMomentLogEt, jet4_etaphiMomentMomentLogEt, jet5_etaphiMomentMomentLogEt, jet6_etaphiMomentMomentLogEt;
  float jet1_phiphiMomentMomentLogEt, jet2_phiphiMomentMomentLogEt, jet3_phiphiMomentMomentLogEt, jet4_phiphiMomentMomentLogEt, jet5_phiphiMomentMomentLogEt, jet6_phiphiMomentMomentLogEt;

  float jets_etaetaMomentLogEt, jets_etaphiMomentLogEt, jets_phiphiMomentLogEt;

  float aplanarity      , sphericity      , circularity      , isotropy      , C      , D      ;
  float aplanarityAll   , sphericityAll   , circularityAll   , isotropyAll   , CAll   , DAll   ;
  float aplanarityAllCMS, sphericityAllCMS, circularityAllCMS, isotropyAllCMS, CAllCMS, DAllCMS;

  float centrality, centralityAlt;

  float thrust, thrustCMS;

  float ptAsy, ptAsyBar;

  float ttDetFrame                          ;
  float bbDetFrame                          ;
  float bbTtbarFrame                        ;
  float WWTtbarFrame                        ;
  float tBBranch1TtbarFrame                 ;
  float tBBranch2TtbarFrame                 ;
  float bWBranch1TtbarFrame                 ;
  float bWBranch2TtbarFrame                 ;
  float tWBranch1TopInTtbarFrameWInTopFrame ;
  float tWBranch2TopInTtbarFrameWInTopFrame ;
  float qQbarTopFrame                       ;
  float qQbarDetFrame                       ;
  float pPbarTopFrame                       ;
  float pQbarTtbarFrame                     ;
  float pQTtbarFrame                        ;
  float pbarQbarTtbarFrame                  ;
  float pbarQTtbarFrame                     ;
  float bhad1QTopFrame                      ;
  float bhad1QbarTopFrame                   ;
  float bhad1PTtbarFrame                    ;
  float bhad1PbarTtbarFrame                 ;
  float bhad2QTtbarFrame                    ;
  float bhad2QbarTtbarFrame                 ;
  float bhad2PTopFrame                      ;
  float bhad2PbarTopFrame                   ;
  float qInW1FrameW1InDetFrame              ;
  float qbarInW1FrameW1InDetFrame           ;
  float pInW2FrameW2InDetFrame              ;
  float pbarInW2FrameW2InDetFrame           ;

  float dRbb;

  // doubles
  double MCweight, PUweight;
  double prob, chi2, topMass, ttMass;
  double * probs, * chi2s, * topMasses, * w1Mass, * w2Mass;
  double multiJetMVADisc;
  double x1, x2;
  double ptHat;
  double * L7PartonCorrection;
  
  // TClonesArray(TLorentzVectors)
  TClonesArray * jets, * genJets, * genPartons, * MET, * muons, * electrons, * fitVecs;

};

#endif
