#include "TH1.h"
#include "TH2.h"
#include "TTree.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


/**
   \class   TagAndProbeAnalyzer TagAndProbeAnalyzer.h "TopAnalysis/TopAnalyzer/plugins/TagAndProbeAnalyzer.h"

   \brief   Plugin to fill histograms for the determination of tag and probe efficiencies

   Can be used for muons or electrons
*/

class TagAndProbeAnalyzer : public edm::EDAnalyzer {
 public:
  /// default constructor
   explicit TagAndProbeAnalyzer(const edm::ParameterSet& cfg);
  /// default destructor
    ~TagAndProbeAnalyzer();
  
  
 private:
  /// ...
  virtual void beginJob();
  /// ...
  virtual void analyze(const edm::Event& evt, const edm::EventSetup& setup);
  /// ...
  virtual void endJob();
  /// ...
  void bookTree(TString varName, TString varType); 
  void fillHistoAndTree(TString varName, float varValue, float weight);
  void fillHisto(TString varName, float varValue, float weight);
  void fillTree(TString varName, double varValue);
  void fillTree(TString varName, int varValue);
  void initializeTrees(float value);
  double minDR(edm::View<reco::Candidate>::const_iterator firstJet, edm::View<reco::Candidate>::const_iterator lastJet, edm::View<reco::Candidate>::const_iterator muon);

 private:
  /// ...
  edm::InputTag vertices_;
  edm::InputTag tags_;
  edm::InputTag probes_;
  edm::InputTag tests_;
  edm::InputTag jets_;  
  
  /// mass and deltaM
  double mass_;
  double deltaM_;

  /// tag and probe histogram
  std::map<TString, TH1F*> hists_;
  /// tag and probe 2D histogram
  std::map<TString, TH2F*> hists2D_;
  /// tree
  TTree * tree;
  std::map<TString, float> treeVarsFloat_;
  std::map<TString, int>   treeVarsInt_;

  
  
  /// counts number of events
  double evtNum_;
  /// variable (true) or fixed (false) bins
  //bool varBins_;
  /// variables for cut on pt and eta: pt cut is not applied on pt-histo, eta cut is not applied on eta-histo
  /// both cuts are applied on all other histos 
  double ptCut_;
  double etaCut_;
  /// nBins of histos
  int nBinsPt_;
  int nBinsEta_;
  int nBinsPhi_;
  int nBinsMult_;
  int nBinsRelIso_;
  int nBinsAbsIso_;
  int nBinsMinDR_;
  int nBinsLepMult_;
  int nBinsPVMult_;
  /// in case of fixed bins: 1st vector entry=xlow, 2nd vector entry=xup (left and right edges of histo)
  /// in case of variable bins: vector of low-edges for each bin
  std::vector<double> binsPt_;
  std::vector<double> binsEta_;
  std::vector<double> binsPhi_;
  std::vector<double> binsMult_;
  std::vector<double> binsRelIso_;
  std::vector<double> binsAbsIso_;
  std::vector<double> binsMinDR_;
  std::vector<double> binsLepMult_;
  std::vector<double> binsPVMult_;
  /// switch between detector based and PF relIso
  bool pfRelIso_;
  bool noWeightHisto_;
  /// event weights
  std::vector<edm::InputTag> weightTags_;

};

inline
double TagAndProbeAnalyzer::minDR(edm::View<reco::Candidate>::const_iterator firstJet, edm::View<reco::Candidate>::const_iterator lastJet, edm::View<reco::Candidate>::const_iterator muon)
{
  double minDR=-1;
  for(edm::View<reco::Candidate>::const_iterator jet=firstJet; jet!=lastJet; ++jet){
    if(minDR<0 || deltaR(jet->eta(), jet->phi(), muon->eta(), muon->phi())<minDR){
      minDR=deltaR(jet->eta(), jet->phi(), muon->eta(), muon->phi());
    }
  }
  return minDR;
}

/// method to book the tree
inline
void 
    TagAndProbeAnalyzer::bookTree(TString varName, TString varType="/F") 
{
  if(varType=="/F"){
    treeVarsFloat_[varName];
    tree->Branch(varName, &treeVarsFloat_[varName], varName + varType);
  }
  else if(varType=="/I"){
    treeVarsInt_[varName];
    tree->Branch(varName, &treeVarsInt_[varName], varName + varType);
  }
  else std::cout<<"WARNING!!!!! varType "<<varType<< " not found!!!"<<std::endl;
}

/// method to fill the histo and tree
inline
void 
    TagAndProbeAnalyzer::fillHistoAndTree(TString varName, float varValue, float weight) 
{
  hists_.find(varName)->second->Fill( varValue, weight );
  treeVarsFloat_[varName] = varValue;
}

inline
    void 
    TagAndProbeAnalyzer::fillHisto(TString varName, float varValue, float weight) 
{
  hists_.find(varName)->second->Fill( varValue, weight );
}

inline
    void 
    TagAndProbeAnalyzer::fillTree(TString varName, double varValue) 
{
  treeVarsFloat_[varName] = varValue;
}

inline
    void 
    TagAndProbeAnalyzer::fillTree(TString varName, int varValue) 
{
  treeVarsInt_[varName] = varValue;
}

inline
    void TagAndProbeAnalyzer::initializeTrees(float value=-9999.)
{
  // loop all branches in the tree (float)
  for(std::map<TString, float>::iterator treeEntry=treeVarsFloat_.begin(); treeEntry!=treeVarsFloat_.end(); ++treeEntry){
    treeEntry->second = value;
  }
  // loop all branches in the tree (int)
  for(std::map<TString, int>::iterator treeEntry=treeVarsInt_.begin(); treeEntry!=treeVarsInt_.end(); ++treeEntry){
    treeEntry->second = value;
  }
}
