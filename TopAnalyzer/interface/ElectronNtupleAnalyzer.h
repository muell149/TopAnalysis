#ifndef ElectronNtupleAnalyzer_h
#define ElectronNtupleAnalyzer_h

#include "TH1D.h"
#include "TTree.h"
#include "TVector2.h"
#include "TLorentzVector.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Candidate/interface/Particle.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class ElectronNtupleAnalyzer : public edm::EDAnalyzer {

 public:

  explicit ElectronNtupleAnalyzer(const edm::ParameterSet&);
  ~ElectronNtupleAnalyzer();
  
 private:

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  edm::InputTag electrons_;
  edm::InputTag jets_;
  edm::InputTag mets_;   
  edm::InputTag primaryVertex_;


  typedef std::vector<pat::Electron> PatElectronCollection; 
  typedef std::vector<pat::Jet>  PatJetCollection; 
  typedef std::vector<pat::MET>  PatMETCollection; 

  TH1D* Nprimary_;  
  TH1D* Zvertex_;

  TH1D* ut_;
  TH1D* upar_;
  TH1D* uperp_;


  // declarations for sum of four-momenta
  TVector2 ptZVec;
  TVector2 ptJetVec;
  TVector2 ptMetVec;


  // declarations for tree
  TTree* Ntuple_;
  int irun;
  int ilumi;
  int ievent;
  int nprimary;
  double zvertex;
  //
  double METet;
  double METphi;
  double METpx;
  double METpy;
  double METSumEt;
  double METut;
  double METutpar;
  double METutperp;
  double METut2;
  //
  double ptel1;
  double phiel1;
  double etael1;
  double chargeel1;
  double trkisoel1;
  double ecalisoel1;
  double hcalisoel1;
  double ptel2;
  double phiel2;
  double etael2;
  double chargeel2;
  double trkisoel2;
  double ecalisoel2;
  double hcalisoel2;
  double dimass;
  //
  double ptjet1;
  double phijet1;
  double etajet1;
  double TCHEdiscr1;
  double SVHEdiscr1;
  double jetflavour1;
  double ptjet2;
  double phijet2;
  double etajet2;
  double TCHEdiscr2;
  double SVHEdiscr2;
  double jetflavour2;
  double dimassjet;

};

#endif
