#ifndef FullHadEventMixer_h
#define FullHadEventMixer_h

//#include "TH1F.h"
//#include "TH2F.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "TRandom3.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CommonTools/Utils/interface/PtComparator.h"

//#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TopQuarkAnalysis/TopKinFitter/interface/TtFullHadKinFitter.h"

/**
   \class   FullHadEventMixer FullHadEventMixer.h "TopAnalysis/TopAnalyzer/interface/FullHadEventMixer.h"

   \brief   Brief description

   Full comment
*/

class FullHadEventMixer : public edm::EDAnalyzer {

 public:
  /// default constructor for full fw
  explicit FullHadEventMixer(const edm::ParameterSet& configFile);
  /// default destructor
  ~FullHadEventMixer(){};

 private:
  /// initiate histograms
  virtual void beginJob();
  /// produce n-tuple
  virtual void analyze(const edm::Event& event, const edm::EventSetup& iSetup);
  /// empty
  virtual void endJob();

  /*
  /// book histograms or tree variables
  void bookVariable(edm::Service<TFileService>& fs, const char * variable,
		    unsigned int binsX, float lowX, float upX, unsigned int binsY, float lowY, float upY,
		    bool useTree);
  void bookVariable(edm::Service<TFileService>& fs, const char * variable, unsigned int binsX, float lowX, float upX, bool useTree);
  void bookVariable(edm::Service<TFileService>& fs, const char * variable);
  /// fill values into map for histograms or tree
  void fillValue(std::string variable, double value1, const double& weight);
  */

  /// do the kinematic fit and save results
  void doFitting(const std::vector<pat::Jet>& myJets);
  /// comparison of pat::Jets needed for sorting
  GreaterByPt<pat::Jet> pTComparator_;

  /// src's for the different infos
  edm::InputTag JetSrc_, METSrc_, MuonSrc_, ElectronSrc_, FitSrc_, VertexSrc_; //, MultiJetMVADiscSrc_;

  /*
  /// produce a TTree as output instead of histograms
  bool useTree_;
  */

  /// b-tagging algo and working point to be used
  std::string bTagAlgo_;
  double minBTagValueBJet_, maxBTagValueNonBJet_;
  /// store resolutions for the kinematic fit
  std::vector<edm::ParameterSet> udscResolutions_;
  std::vector<edm::ParameterSet> bResolutions_;

  std::vector<double> jetEnergyResolutionScaleFactors_;
  std::vector<double> jetEnergyResolutionEtaBinning_;

  // jet ennergy correction level
  std::string jetCorrectionLevel_;

  /// number of events to be mixed
  const unsigned int nMix_;

  /// speed up factor used to randomly selected 1:speedUp_ events
  const double speedUp_;

  /// weight of MC sample
  double MCweight_;

  /// current MVA discriminator
  //std::vector<double> currMVADiscs_;

  /// save jets for every nMix_ events
  std::vector<std::vector<pat::Jet> > oldJets_;

  /// kinematic fit interface
  TtFullHadKinFitter::KinFit* kinFitter;

  /// random generator for speed increase
  TRandom3 * myRand;

  /// histogram container
  /*
  std::map<std::string, TH1*> hists_;
  std::map<std::string, TH2*> hists2D_;
  std::map<std::string, double> treeVars_;
  */
  TTree * tree;

  // max possible number of jets in events
  const unsigned short kMAX;

  // max possible number of permutations per event
  const unsigned int kMAXCombo;

  // shorts
  //short * fitAssigns;
  short nVertex;
  short fitExitCode;
  short nPU   , nPUnext   , nPUprev   ;
  short nPUTru, nPUnextTru, nPUprevTru;

  // ints
  int Njet;
  // unsigend ints
  unsigned int nCombos;
  unsigned int runNumber, luminosityBlockNumber, eventNumber;

  // floats
  float * bTag_TCHE, * bTag_TCHP, * bTag_SSVHE, * bTag_SSVHP, * bTag_CSV, * bTag_CSVMVA;

  float * ttDetFrame, * bbDetFrame, * bbTtbarFrame, * WWTtbarFrame, * tBBranch1TtbarFrame, * tBBranch2TtbarFrame, * bWBranch1TtbarFrame, * bWBranch2TtbarFrame, * tWBranch1TopInTtbarFrameWInTopFrame, * tWBranch2TopInTtbarFrameWInTopFrame, * qQbarTopFrame, * qQbarDetFrame, * pPbarTopFrame, * pQbarTtbarFrame, * pQTtbarFrame, * pbarQbarTtbarFrame, * pbarQTtbarFrame, * bhad1QTopFrame, * bhad1QbarTopFrame, * bhad1PTtbarFrame, * bhad1PbarTtbarFrame, * bhad2QTtbarFrame, * bhad2QbarTtbarFrame, * bhad2PTopFrame, * bhad2PbarTopFrame, * qInW1FrameW1InDetFrame, * qbarInW1FrameW1InDetFrame, * pInW2FrameW2InDetFrame, * pbarInW2FrameW2InDetFrame;
  float * dRbb;

  // doubles
  double MCweight;
  double prob, chi2, topMass, ttMass, ttPt;
  double * probs, * chi2s, * topMasses, * w1Mass, * w2Mass;

  // TClonesArray(TLorentzVectors)
  TClonesArray * jets, * MET, * muons, * electrons;//, * fitVecs;
};
/*
/// book histograms or tree variables
void FullHadEventMixer::bookVariable(edm::Service<TFileService>& fs, const char * variable,
					unsigned int binsX, float lowX, float upX, unsigned int binsY, float lowY, float upY,
					bool useTree=false)
{
  if(useTree && !binsY){
    //std::cout << "Adding *" << variable << "* to TTree" << std::endl;
    if(!tree){
      tree = fs->make<TTree>("tree","tree",0);
      treeVars_["weight"];
      tree->Branch("weight", &treeVars_["weight"], (std::string("weight") + "/D").c_str());
    }
    treeVars_[variable];
    tree->Branch(variable, &treeVars_[variable], (std::string(variable) + "/D").c_str());
  }
  else{
    //std::cout << "Adding *" << variable << "* to Histograms" << std::endl;
    if     (!binsY &&  !lowY && !upY )  hists_  [variable] = fs->make<TH1F>( variable, variable, binsX, lowX, upX );
    else if( binsY && ( lowY ||  upY )) hists2D_[variable] = fs->make<TH2F>( variable, variable, binsX, lowX, upX, binsY, lowY, upY );
  }
}

void FullHadEventMixer::bookVariable(edm::Service<TFileService>& fs, const char * variable,
					unsigned int binsX, float lowX, float upX, bool useTree=false)
{
  bookVariable( fs, variable, binsX, lowX, upX, 0, 0, 0, useTree);
}

void FullHadEventMixer::bookVariable(edm::Service<TFileService>& fs, const char * variable)
{
  bookVariable( fs, variable, 0, 0, 0, 0, 0, 0, true);
}

void FullHadEventMixer::fillValue(std::string variable, double value, const double& weight=1.)
{
  if(treeVars_.find(variable) != treeVars_.end()){
    treeVars_.find(variable)->second = value;
    treeVars_.find("weight")->second = weight;
  }
  if(hists_.find(variable) != hists_.end()){
    hists_.find(variable)->second->Fill(value, weight);
  }
}
*/
#endif
