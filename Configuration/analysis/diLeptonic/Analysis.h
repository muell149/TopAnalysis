//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Nov 23 17:17:11 2011 by ROOT version 5.27/06b
// from TTree NTuple/NTuple
// found on file: mergedRoot/mumu/ttbarsignal.root
//////////////////////////////////////////////////////////

#ifndef Analysis_h
#define Analysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TH1.h>
#include "plotterclass.h"

   const Int_t kMaxlepton = 99;
   const Int_t kMaxjet = 99;
   const Int_t kMaxgenJet = 99;
   const Int_t kMaxHypTop = 99;
   const Int_t kMaxHypAntiTop = 99;
   const Int_t kMaxHypLepton = 99;
   const Int_t kMaxHypAntiLepton = 99;
   const Int_t kMaxHypNeutrino = 99;
   const Int_t kMaxHypAntiNeutrino = 99;
   const Int_t kMaxHypB = 99;
   const Int_t kMaxHypAntiB = 99;
   const Int_t kMaxHypWPlus = 99;
   const Int_t kMaxHypWMinus = 99;

using namespace std;

class Analysis : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           EventCounter;
   Int_t           lepton_;
   Double_t        leptonpX[kMaxlepton];   //[lepton_]
   Double_t        leptonpY[kMaxlepton];   //[lepton_]
   Double_t        leptonpZ[kMaxlepton];   //[lepton_]
   Double_t        leptonE[kMaxlepton];   //[lepton_]
   vector<int>     *lepQ;
   vector<int>     *lepType;
   vector<double>  *lepPfIso;
   vector<double>  *lepCombIso;
   Int_t           jet_;
   Double_t        jetpX[kMaxjet];   //[jet_]
   Double_t        jetpY[kMaxjet];   //[jet_]
   Double_t        jetpZ[kMaxjet];   //[jet_]
   Double_t        jetE[kMaxjet];   //[jet_]
   vector<double>  *jetBTagTCHE;
   vector<double>  *jetBTagSSVHE;
   Int_t           genJet_;
   Double_t        genJetpX[kMaxgenJet];   //[genJet_]
   Double_t        genJetpY[kMaxgenJet];   //[genJet_]
   Double_t        genJetpZ[kMaxgenJet];   //[genJet_]
   Double_t        genJetE[kMaxgenJet];   //[genJet_]
   vector<double>  *metEt;
   vector<double>  *metPhi;
   Int_t           runNumber;
   Int_t           lumiBlock;
   Int_t           eventNumber;
   vector<string>  *dataType;
   Double_t        weightPU;
   Double_t        weightPU_Up;
   Double_t        weightPU_Down;
   Double_t        weightLepSF;
   Double_t        weightKinFit;
   Double_t        weightTotal;
   Int_t           vertMulti;

   Double_t        phonebook;
   Double_t        GenWPluspX;
   Double_t        GenWPluspY;
   Double_t        GenWPluspZ;
   Double_t        GenWPlusE;
   Double_t        GenWMinuspX;
   Double_t        GenWMinuspY;
   Double_t        GenWMinuspZ;
   Double_t        GenWMinusE;
   Double_t        GenNeutrinopX;
   Double_t        GenNeutrinopY;
   Double_t        GenNeutrinopZ;
   Double_t        GenNeutrinoE;
   Double_t        GenAntiNeutrinopX;
   Double_t        GenAntiNeutrinopY;
   Double_t        GenAntiNeutrinopZ;
   Double_t        GenAntiNeutrinoE;
   Double_t        GenBpX;
   Double_t        GenBpY;
   Double_t        GenBpZ;
   Double_t        GenBE;
   Double_t        GenAntiBpX;
   Double_t        GenAntiBpY;
   Double_t        GenAntiBpZ;
   Double_t        GenAntiBE;
   Double_t        GenLeptonpX;
   Double_t        GenLeptonpY;
   Double_t        GenLeptonpZ;
   Double_t        GenLeptonE;
   Double_t        GenAntiLeptonpX;
   Double_t        GenAntiLeptonpY;
   Double_t        GenAntiLeptonpZ;
   Double_t        GenAntiLeptonE;
   Double_t        GenToppX;
   Double_t        GenToppY;
   Double_t        GenToppZ;
   Double_t        GenTopE;
   Double_t        GenAntiToppX;
   Double_t        GenAntiToppY;
   Double_t        GenAntiToppZ;
   Double_t        GenAntiTopE;

   Int_t           HypTop_;
   Double_t        HypToppX[kMaxHypTop];   //[HypTop_]
   Double_t        HypToppY[kMaxHypTop];   //[HypTop_]
   Double_t        HypToppZ[kMaxHypTop];   //[HypTop_]
   Double_t        HypTopE[kMaxHypTop];   //[HypTop_]
   Int_t           HypAntiTop_;
   Double_t        HypAntiToppX[kMaxHypAntiTop];   //[HypAntiTop_]
   Double_t        HypAntiToppY[kMaxHypAntiTop];   //[HypAntiTop_]
   Double_t        HypAntiToppZ[kMaxHypAntiTop];   //[HypAntiTop_]
   Double_t        HypAntiTopE[kMaxHypAntiTop];   //[HypAntiTop_]
   Int_t           HypLepton_;
   Double_t        HypLeptonpX[kMaxHypLepton];   //[HypLepton_]
   Double_t        HypLeptonpY[kMaxHypLepton];   //[HypLepton_]
   Double_t        HypLeptonpZ[kMaxHypLepton];   //[HypLepton_]
   Double_t        HypLeptonE[kMaxHypLepton];   //[HypLepton_]
   Int_t           HypAntiLepton_;
   Double_t        HypAntiLeptonpX[kMaxHypAntiLepton];   //[HypAntiLepton_]
   Double_t        HypAntiLeptonpY[kMaxHypAntiLepton];   //[HypAntiLepton_]
   Double_t        HypAntiLeptonpZ[kMaxHypAntiLepton];   //[HypAntiLepton_]
   Double_t        HypAntiLeptonE[kMaxHypAntiLepton];   //[HypAntiLepton_]
   Int_t           HypNeutrino_;
   Double_t        HypNeutrinopX[kMaxHypNeutrino];   //[HypNeutrino_]
   Double_t        HypNeutrinopY[kMaxHypNeutrino];   //[HypNeutrino_]
   Double_t        HypNeutrinopZ[kMaxHypNeutrino];   //[HypNeutrino_]
   Double_t        HypNeutrinoE[kMaxHypNeutrino];   //[HypNeutrino_]
   Int_t           HypAntiNeutrino_;
   Double_t        HypAntiNeutrinopX[kMaxHypAntiNeutrino];   //[HypAntiNeutrino_]
   Double_t        HypAntiNeutrinopY[kMaxHypAntiNeutrino];   //[HypAntiNeutrino_]
   Double_t        HypAntiNeutrinopZ[kMaxHypAntiNeutrino];   //[HypAntiNeutrino_]
   Double_t        HypAntiNeutrinoE[kMaxHypAntiNeutrino];   //[HypAntiNeutrino_]
   Int_t           HypB_;
   Double_t        HypBpX[kMaxHypB];   //[HypB_]
   Double_t        HypBpY[kMaxHypB];   //[HypB_]
   Double_t        HypBpZ[kMaxHypB];   //[HypB_]
   Double_t        HypBE[kMaxHypB];   //[HypB_]
   Int_t           HypAntiB_;
   Double_t        HypAntiBpX[kMaxHypAntiB];   //[HypAntiB_]
   Double_t        HypAntiBpY[kMaxHypAntiB];   //[HypAntiB_]
   Double_t        HypAntiBpZ[kMaxHypAntiB];   //[HypAntiB_]
   Double_t        HypAntiBE[kMaxHypAntiB];   //[HypAntiB_]
   Int_t           HypWPlus_;
   Double_t        HypWPluspX[kMaxHypWPlus];   //[HypWPlus_]
   Double_t        HypWPluspY[kMaxHypWPlus];   //[HypWPlus_]
   Double_t        HypWPluspZ[kMaxHypWPlus];   //[HypWPlus_]
   Double_t        HypWPlusE[kMaxHypWPlus];   //[HypWPlus_]
   Int_t           HypWMinus_;
   Double_t        HypWMinuspX[kMaxHypWMinus];   //[HypWMinus_]
   Double_t        HypWMinuspY[kMaxHypWMinus];   //[HypWMinus_]
   Double_t        HypWMinuspZ[kMaxHypWMinus];   //[HypWMinus_]
   Double_t        HypWMinusE[kMaxHypWMinus];   //[HypWMinus_]
   vector<int>     *HypJet0index;
   vector<int>     *HypJet1index;
   Int_t           decayMode;
   Double_t        btagSF;
   Double_t        trigEFF;
   string          *channel;
   string          *MCSample;
   string          systematic;
   Double_t        lumiWeight;
   


   // List of branches
   TBranch        *b_lepton_;   //!
   TBranch        *b_leptonpX;   //!
   TBranch        *b_leptonpY;   //!
   TBranch        *b_leptonpZ;   //!
   TBranch        *b_leptonE;   //!
   TBranch        *b_lepQ;   //!
   TBranch        *b_lepType;   //!
   TBranch        *b_lepPfIso;   //!
   TBranch        *b_lepCombIso;   //!
   TBranch        *b_jet_;   //!
   TBranch        *b_jetpX;   //!
   TBranch        *b_jetpY;   //!
   TBranch        *b_jetpZ;   //!
   TBranch        *b_jetE;   //!
   TBranch        *b_jetBTagTCHE;   //!
   TBranch        *b_jetBTagSSVHE;   //!
   TBranch        *b_genJet_;   //!
   TBranch        *b_genJetpX;   //!
   TBranch        *b_genJetpY;   //!
   TBranch        *b_genJetpZ;   //!
   TBranch        *b_genJetE;   //!
   TBranch        *b_metEt;   //!
   TBranch        *b_metPhi;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_dataType;   //!
   TBranch        *b_weightPU;   //!
   TBranch        *b_weightPU_Up;   //!
   TBranch        *b_weightPU_Down;   //!
   TBranch        *b_weightLepSF;   //!
   TBranch        *b_weightKinFit;   //!
   TBranch        *b_weightTotal;   //!
   TBranch        *b_vertMulti;   //!


   TBranch        *b_GenToppX;   //!
   TBranch        *b_GenToppY;   //!
   TBranch        *b_GenToppZ;   //!
   TBranch        *b_GenTopE;   //!
   TBranch        *b_GenAntiToppX;   //!
   TBranch        *b_GenAntiToppY;   //!
   TBranch        *b_GenAntiToppZ;   //!
   TBranch        *b_GenAntiTopE;   //!
   TBranch        *b_GenLeptonpX;   //!
   TBranch        *b_GenLeptonpY;   //!
   TBranch        *b_GenLeptonpZ;   //!
   TBranch        *b_GenLeptonE;   //!
   TBranch        *b_GenAntiLeptonpX;   //!
   TBranch        *b_GenAntiLeptonpY;   //!
   TBranch        *b_GenAntiLeptonpZ;   //!
   TBranch        *b_GenAntiLeptonE;   //!
   TBranch        *b_GenNeutrinopX;   //!
   TBranch        *b_GenNeutrinopY;   //!
   TBranch        *b_GenNeutrinopZ;   //!
   TBranch        *b_GenNeutrinoE;   //!
   TBranch        *b_GenAntiNeutrinopX;   //!
   TBranch        *b_GenAntiNeutrinopY;   //!
   TBranch        *b_GenAntiNeutrinopZ;   //!
   TBranch        *b_GenAntiNeutrinoE;   //!
   TBranch        *b_GenBpX;   //!
   TBranch        *b_GenBpY;   //!
   TBranch        *b_GenBpZ;   //!
   TBranch        *b_GenBE;   //!
   TBranch        *b_GenAntiBpX;   //!
   TBranch        *b_GenAntiBpY;   //!
   TBranch        *b_GenAntiBpZ;   //!
   TBranch        *b_GenAntiBE;   //!
   TBranch        *b_GenWPluspX;   //!
   TBranch        *b_GenWPluspY;   //!
   TBranch        *b_GenWPluspZ;   //!
   TBranch        *b_GenWPlusE;   //!
   TBranch        *b_GenWMinuspX;   //!
   TBranch        *b_GenWMinuspY;   //!
   TBranch        *b_GenWMinuspZ;   //!
   TBranch        *b_GenWMinusE;   //!


   TBranch        *b_HypTop_;   //!
   TBranch        *b_HypToppX;   //!
   TBranch        *b_HypToppY;   //!
   TBranch        *b_HypToppZ;   //!
   TBranch        *b_HypTopE;   //!
   TBranch        *b_HypAntiTop_;   //!
   TBranch        *b_HypAntiToppX;   //!
   TBranch        *b_HypAntiToppY;   //!
   TBranch        *b_HypAntiToppZ;   //!
   TBranch        *b_HypAntiTopE;   //!
   TBranch        *b_HypLepton_;   //!
   TBranch        *b_HypLeptonpX;   //!
   TBranch        *b_HypLeptonpY;   //!
   TBranch        *b_HypLeptonpZ;   //!
   TBranch        *b_HypLeptonE;   //!
   TBranch        *b_HypAntiLepton_;   //!
   TBranch        *b_HypAntiLeptonpX;   //!
   TBranch        *b_HypAntiLeptonpY;   //!
   TBranch        *b_HypAntiLeptonpZ;   //!
   TBranch        *b_HypAntiLeptonE;   //!
   TBranch        *b_HypNeutrino_;   //!
   TBranch        *b_HypNeutrinopX;   //!
   TBranch        *b_HypNeutrinopY;   //!
   TBranch        *b_HypNeutrinopZ;   //!
   TBranch        *b_HypNeutrinoE;   //!
   TBranch        *b_HypAntiNeutrino_;   //!
   TBranch        *b_HypAntiNeutrinopX;   //!
   TBranch        *b_HypAntiNeutrinopY;   //!
   TBranch        *b_HypAntiNeutrinopZ;   //!
   TBranch        *b_HypAntiNeutrinoE;   //!
   TBranch        *b_HypB_;   //!
   TBranch        *b_HypBpX;   //!
   TBranch        *b_HypBpY;   //!
   TBranch        *b_HypBpZ;   //!
   TBranch        *b_HypBE;   //!
   TBranch        *b_HypAntiB_;   //!
   TBranch        *b_HypAntiBpX;   //!
   TBranch        *b_HypAntiBpY;   //!
   TBranch        *b_HypAntiBpZ;   //!
   TBranch        *b_HypAntiBE;   //!
   TBranch        *b_HypWPlus_;   //!
   TBranch        *b_HypWPluspX;   //!
   TBranch        *b_HypWPluspY;   //!
   TBranch        *b_HypWPluspZ;   //!
   TBranch        *b_HypWPlusE;   //!
   TBranch        *b_HypWMinus_;   //!
   TBranch        *b_HypWMinuspX;   //!
   TBranch        *b_HypWMinuspY;   //!
   TBranch        *b_HypWMinuspZ;   //!
   TBranch        *b_HypWMinusE;   //!
   TBranch        *b_HypJet0index;   //!
   TBranch        *b_HypJet1index;   //!
   TBranch        *b_decayMode;   //!
   TBranch        *b_btagSF;   //!
   TBranch        *b_trigEFF;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_MCSample;   //!
   TBranch        *b_lumiWeight;   //!

   Analysis(TTree * /*tree*/ =0) { }
   virtual ~Analysis() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   void GetAllBranches(Long64_t &);
   void GetSignalBranches(Long64_t &);
   TH2D *h_GenRecoLeptonpT,*h_GenRecoAntiLeptonpT,*h_GenRecoLeptonEta,*h_GenRecoAntiLeptonEta, *h_GenRecoLLBarMass, *h_GenRecoLLBarpT, ;
   TH2D *h_GenRecoToppT,*h_GenRecoAntiToppT,*h_GenRecoTopRapidity,*h_GenRecoAntiTopRapidity, *h_GenRecoTTBarMass, *h_GenRecoTTBarpT, *h_GenRecoTTBarRapidity;
   
   TH1D *h_NJetMatching;

   TH1D *Looseh1, *Allh1, *Zh1, *TTh1, *h_GenAll, *h_jetMulti, *h_BjetMulti,*h_jetMultiXSec,*h_jetMultiAll, *h_jetMultiNoPU, *h_jetMultiVisTop, *h_VisGenAll, *h_diLepMassFull;

   TH1D *h_HypTTBarMass, *h_HypTTBarRapidity, *h_HypTTBarpT;
   TH1D *h_HypLLBarMass, *h_HypLLBarpT;
   TH1D *h_GenTTBarMass, *h_GenTTBarRapidity, *h_GenTTBarpT;
   TH1D *h_GenLLBarMass, *h_GenLLBarpT;

   TH1D *h_VisGenTTBarMass,*h_VisGenTTBarRapidity,*h_VisGenTTBarpT;
   TH1D *h_VisGenTopRapidity,*h_VisGenAntiTopRapidity;
   TH1D *h_VisGenLLBarMass,*h_VisGenLLBarpT;

   TH1D *h_RecoTTBarMass, *h_RecoTTBarRapidity,*h_RecoTTBarpT;
   TH1D *h_RecoToppT,*h_RecoAntiToppT,*h_RecoTopRapidity,*h_RecoAntiTopRapidity;
   TH1D *h_RecoLLBarMass, *h_RecoLLBarpT;
   TH1D *h_RecoLeptonpT,*h_RecoAntiLeptonpT,*h_RecoLeptonEta,*h_RecoAntiLeptonEta;

   TH1D *h_vertMulti, *h_MET;

   TH1D *h_jetpT,*h_jetHT;
   TH1D *h_MuonpT, *h_MuonEta, *h_MuonE;
   TH1D *h_ElectronpT, *h_ElectronEta, *h_ElectronE;
   TH1D *h_LeptonpT, *h_LeptonEta, *h_LeptonE;
   TH1D *h_AntiLeptonpT, *h_AntiLeptonEta, *h_AntiLeptonE;

   TH1D *h_HypAntiToppT, *h_HypAntiTopEta, *h_HypAntiTopE, *h_HypAntiTopMass,*h_HypAntiTopRapidity;
   TH1D *h_HypToppT, *h_HypTopEta, *h_HypTopE,*h_HypTopMass, *h_HypTopRapidity ;

   TH1D *h_HypWPluspT, *h_HypWPlusEta, *h_HypWPlusE;
   TH1D *h_HypWMinuspT, *h_HypWMinusEta, *h_HypWMinusE;

   TH1D *h_HypAntiBpT, *h_HypAntiBEta, *h_HypAntiBE;
   TH1D *h_HypBpT, *h_HypBEta, *h_HypBE;

   TH1D *h_HypAntiLeptonpT, *h_HypAntiLeptonEta, *h_HypAntiLeptonE;
   TH1D *h_HypLeptonpT, *h_HypLeptonEta, *h_HypLeptonE;

   TH1D *h_HypAntiNeutrinopT, *h_HypAntiNeutrinoEta, *h_HypAntiNeutrinoE;
   TH1D *h_HypNeutrinopT, *h_HypNeutrinoEta, *h_HypNeutrinoE;

   TH1D *h_VisGenAntiToppT, *h_VisGenAntiTopEta, *h_VisGenAntiTopE;
   TH1D *h_VisGenToppT, *h_VisGenTopEta, *h_VisGenTopE;

   TH1D *h_VisGenWPluspT, *h_VisGenWPlusEta, *h_VisGenWPlusE;
   TH1D *h_VisGenWMinuspT, *h_VisGenWMinusEta, *h_VisGenWMinusE;

   TH1D *h_VisGenAntiBpT, *h_VisGenAntiBEta, *h_VisGenAntiBE;
   TH1D *h_VisGenBpT, *h_VisGenBEta, *h_VisGenBE;

   TH1D *h_VisGenAntiLeptonpT, *h_VisGenAntiLeptonEta, *h_VisGenAntiLeptonE;
   TH1D *h_VisGenLeptonpT, *h_VisGenLeptonEta, *h_VisGenLeptonE;

   TH1D *h_VisGenAntiNeutrinopT, *h_VisGenAntiNeutrinoEta, *h_VisGenAntiNeutrinoE;
   TH1D *h_VisGenNeutrinopT, *h_VisGenNeutrinoEta, *h_VisGenNeutrinoE;

   TH1D *h_GenAntiToppT, *h_GenAntiTopEta, *h_GenAntiTopE, *h_GenAntiTopRapidity;
   TH1D *h_GenToppT, *h_GenTopEta, *h_GenTopE, *h_GenTopRapidity;

   TH1D *h_GenWPluspT, *h_GenWPlusEta, *h_GenWPlusE;
   TH1D *h_GenWMinuspT, *h_GenWMinusEta, *h_GenWMinusE;

   TH1D *h_GenAntiBpT, *h_GenAntiBEta, *h_GenAntiBE;
   TH1D *h_GenBpT, *h_GenBEta, *h_GenBE;

   TH1D *h_GenAntiLeptonpT, *h_GenAntiLeptonEta, *h_GenAntiLeptonE;
   TH1D *h_GenLeptonpT, *h_GenLeptonEta, *h_GenLeptonE;

   TH1D *h_GenAntiNeutrinopT, *h_GenAntiNeutrinoEta, *h_GenAntiNeutrinoE;
   TH1D *h_GenNeutrinopT, *h_GenNeutrinoEta, *h_GenNeutrinoE;

   ClassDef(Analysis,0);
};

#endif

#ifdef Analysis_cxx
void Analysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   lepQ = 0;
   lepType = 0;
   lepPfIso = 0;
   lepCombIso = 0;
   jetBTagTCHE = 0;
   jetBTagSSVHE = 0;
   metEt = 0;
   metPhi = 0;
   dataType = 0;
   HypJet0index = 0;
   HypJet1index = 0;
   channel = 0;
   MCSample = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);
   fChain->SetBranchAddress("lepton", &lepton_, &b_lepton_);
   fChain->SetBranchAddress("lepton.fCoordinates.fX", leptonpX, &b_leptonpX);
   fChain->SetBranchAddress("lepton.fCoordinates.fY", leptonpY, &b_leptonpY);
   fChain->SetBranchAddress("lepton.fCoordinates.fZ", leptonpZ, &b_leptonpZ);
   fChain->SetBranchAddress("lepton.fCoordinates.fT", leptonE, &b_leptonE);
   fChain->SetBranchAddress("lepQ", &lepQ, &b_lepQ);
   fChain->SetBranchAddress("lepType", &lepType, &b_lepType);
   fChain->SetBranchAddress("lepPfIso", &lepPfIso, &b_lepPfIso);
   fChain->SetBranchAddress("lepCombIso", &lepCombIso, &b_lepCombIso);
   fChain->SetBranchAddress("jet", &jet_, &b_jet_);
   fChain->SetBranchAddress("jet.fCoordinates.fX", jetpX, &b_jetpX);
   fChain->SetBranchAddress("jet.fCoordinates.fY", jetpY, &b_jetpY);
   fChain->SetBranchAddress("jet.fCoordinates.fZ", jetpZ, &b_jetpZ);
   fChain->SetBranchAddress("jet.fCoordinates.fT", jetE, &b_jetE);
   fChain->SetBranchAddress("jetBTagTCHE", &jetBTagTCHE, &b_jetBTagTCHE);
   fChain->SetBranchAddress("jetBTagSSVHE", &jetBTagSSVHE, &b_jetBTagSSVHE);
   fChain->SetBranchAddress("genJet", &genJet_, &b_genJet_);
   fChain->SetBranchAddress("genJet.fCoordinates.fX", genJetpX, &b_genJetpX);
   fChain->SetBranchAddress("genJet.fCoordinates.fY", genJetpY, &b_genJetpY);
   fChain->SetBranchAddress("genJet.fCoordinates.fZ", genJetpZ, &b_genJetpZ);
   fChain->SetBranchAddress("genJet.fCoordinates.fT", genJetE, &b_genJetE);
   fChain->SetBranchAddress("metEt", &metEt, &b_metEt);
   fChain->SetBranchAddress("metPhi", &metPhi, &b_metPhi);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("lumiBlock", &lumiBlock, &b_lumiBlock);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("dataType", &dataType, &b_dataType);
   fChain->SetBranchAddress("weightPU", &weightPU, &b_weightPU);
   fChain->SetBranchAddress("weightPU_Up", &weightPU_Up, &b_weightPU_Up);
   fChain->SetBranchAddress("weightPU_Down", &weightPU_Down, &b_weightPU_Down);
   fChain->SetBranchAddress("weightLepSF", &weightLepSF, &b_weightLepSF);
   fChain->SetBranchAddress("weightKinFit", &weightKinFit, &b_weightKinFit);
   fChain->SetBranchAddress("weightTotal", &weightTotal, &b_weightTotal);
   fChain->SetBranchAddress("vertMulti", &vertMulti, &b_vertMulti);


   fChain->SetBranchAddress("HypTop", &HypTop_, &b_HypTop_);
   fChain->SetBranchAddress("HypTop.fCoordinates.fX", HypToppX, &b_HypToppX);
   fChain->SetBranchAddress("HypTop.fCoordinates.fY", HypToppY, &b_HypToppY);
   fChain->SetBranchAddress("HypTop.fCoordinates.fZ", HypToppZ, &b_HypToppZ);
   fChain->SetBranchAddress("HypTop.fCoordinates.fT", HypTopE, &b_HypTopE);
   fChain->SetBranchAddress("HypAntiTop", &HypAntiTop_, &b_HypAntiTop_);
   fChain->SetBranchAddress("HypAntiTop.fCoordinates.fX", HypAntiToppX, &b_HypAntiToppX);
   fChain->SetBranchAddress("HypAntiTop.fCoordinates.fY", HypAntiToppY, &b_HypAntiToppY);
   fChain->SetBranchAddress("HypAntiTop.fCoordinates.fZ", HypAntiToppZ, &b_HypAntiToppZ);
   fChain->SetBranchAddress("HypAntiTop.fCoordinates.fT", HypAntiTopE, &b_HypAntiTopE);
   fChain->SetBranchAddress("HypLepton", &HypLepton_, &b_HypLepton_);
   fChain->SetBranchAddress("HypLepton.fCoordinates.fX", HypLeptonpX, &b_HypLeptonpX);
   fChain->SetBranchAddress("HypLepton.fCoordinates.fY", HypLeptonpY, &b_HypLeptonpY);
   fChain->SetBranchAddress("HypLepton.fCoordinates.fZ", HypLeptonpZ, &b_HypLeptonpZ);
   fChain->SetBranchAddress("HypLepton.fCoordinates.fT", HypLeptonE, &b_HypLeptonE);
   fChain->SetBranchAddress("HypAntiLepton", &HypAntiLepton_, &b_HypAntiLepton_);
   fChain->SetBranchAddress("HypAntiLepton.fCoordinates.fX", HypAntiLeptonpX, &b_HypAntiLeptonpX);
   fChain->SetBranchAddress("HypAntiLepton.fCoordinates.fY", HypAntiLeptonpY, &b_HypAntiLeptonpY);
   fChain->SetBranchAddress("HypAntiLepton.fCoordinates.fZ", HypAntiLeptonpZ, &b_HypAntiLeptonpZ);
   fChain->SetBranchAddress("HypAntiLepton.fCoordinates.fT", HypAntiLeptonE, &b_HypAntiLeptonE);
   fChain->SetBranchAddress("HypNeutrino", &HypNeutrino_, &b_HypNeutrino_);
   fChain->SetBranchAddress("HypNeutrino.fCoordinates.fX", HypNeutrinopX, &b_HypNeutrinopX);
   fChain->SetBranchAddress("HypNeutrino.fCoordinates.fY", HypNeutrinopY, &b_HypNeutrinopY);
   fChain->SetBranchAddress("HypNeutrino.fCoordinates.fZ", HypNeutrinopZ, &b_HypNeutrinopZ);
   fChain->SetBranchAddress("HypNeutrino.fCoordinates.fT", HypNeutrinoE, &b_HypNeutrinoE);
   fChain->SetBranchAddress("HypAntiNeutrino", &HypAntiNeutrino_, &b_HypAntiNeutrino_);
   fChain->SetBranchAddress("HypAntiNeutrino.fCoordinates.fX", HypAntiNeutrinopX, &b_HypAntiNeutrinopX);
   fChain->SetBranchAddress("HypAntiNeutrino.fCoordinates.fY", HypAntiNeutrinopY, &b_HypAntiNeutrinopY);
   fChain->SetBranchAddress("HypAntiNeutrino.fCoordinates.fZ", HypAntiNeutrinopZ, &b_HypAntiNeutrinopZ);
   fChain->SetBranchAddress("HypAntiNeutrino.fCoordinates.fT", HypAntiNeutrinoE, &b_HypAntiNeutrinoE);
   fChain->SetBranchAddress("HypB", &HypB_, &b_HypB_);
   fChain->SetBranchAddress("HypB.fCoordinates.fX", HypBpX, &b_HypBpX);
   fChain->SetBranchAddress("HypB.fCoordinates.fY", HypBpY, &b_HypBpY);
   fChain->SetBranchAddress("HypB.fCoordinates.fZ", HypBpZ, &b_HypBpZ);
   fChain->SetBranchAddress("HypB.fCoordinates.fT", HypBE, &b_HypBE);
   fChain->SetBranchAddress("HypAntiB", &HypAntiB_, &b_HypAntiB_);
   fChain->SetBranchAddress("HypAntiB.fCoordinates.fX", HypAntiBpX, &b_HypAntiBpX);
   fChain->SetBranchAddress("HypAntiB.fCoordinates.fY", HypAntiBpY, &b_HypAntiBpY);
   fChain->SetBranchAddress("HypAntiB.fCoordinates.fZ", HypAntiBpZ, &b_HypAntiBpZ);
   fChain->SetBranchAddress("HypAntiB.fCoordinates.fT", HypAntiBE, &b_HypAntiBE);
   fChain->SetBranchAddress("HypWPlus", &HypWPlus_, &b_HypWPlus_);
   fChain->SetBranchAddress("HypWPlus.fCoordinates.fX", HypWPluspX, &b_HypWPluspX);
   fChain->SetBranchAddress("HypWPlus.fCoordinates.fY", HypWPluspY, &b_HypWPluspY);
   fChain->SetBranchAddress("HypWPlus.fCoordinates.fZ", HypWPluspZ, &b_HypWPluspZ);
   fChain->SetBranchAddress("HypWPlus.fCoordinates.fT", HypWPlusE, &b_HypWPlusE);
   fChain->SetBranchAddress("HypWMinus", &HypWMinus_, &b_HypWMinus_);
   fChain->SetBranchAddress("HypWMinus.fCoordinates.fX", HypWMinuspX, &b_HypWMinuspX);
   fChain->SetBranchAddress("HypWMinus.fCoordinates.fY", HypWMinuspY, &b_HypWMinuspY);
   fChain->SetBranchAddress("HypWMinus.fCoordinates.fZ", HypWMinuspZ, &b_HypWMinuspZ);
   fChain->SetBranchAddress("HypWMinus.fCoordinates.fT", HypWMinusE, &b_HypWMinusE);

   fChain->SetBranchAddress("HypJet0index", &HypJet0index, &b_HypJet0index);
   fChain->SetBranchAddress("HypJet1index", &HypJet1index, &b_HypJet1index);
   fChain->SetBranchAddress("decayMode", &decayMode, &b_decayMode);
   fChain->SetBranchAddress("btagSF", &btagSF, &b_btagSF);
   fChain->SetBranchAddress("trigEFF", &trigEFF, &b_trigEFF);
   fChain->SetBranchAddress("channel", &channel, &b_channel);
   fChain->SetBranchAddress("MCSample", &MCSample, &b_MCSample);
   fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
}

Bool_t Analysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


void Analysis::GetAllBranches(Long64_t & entry)
{

  b_metEt->GetEntry(entry);   //!
  b_eventNumber->GetEntry(entry);   //!
  b_lepton_->GetEntry(entry);   //!
  b_jet_->GetEntry(entry);   //!
  b_lepQ->GetEntry(entry);   //!
  b_lepType->GetEntry(entry);   //!
  b_lepPfIso->GetEntry(entry);   //!
  b_lepCombIso->GetEntry(entry);   //!
  b_jetBTagTCHE->GetEntry(entry);   //!
  b_jetBTagSSVHE->GetEntry(entry);   //!
  b_metPhi->GetEntry(entry);   //!
  b_runNumber->GetEntry(entry);   //!
  b_lumiBlock->GetEntry(entry);   //!
  b_weightPU->GetEntry(entry);   //!
  b_weightPU_Up->GetEntry(entry);   //!
  b_weightPU_Down->GetEntry(entry);   //!
  b_weightLepSF->GetEntry(entry);   //!
  b_weightKinFit->GetEntry(entry);   //!
  b_weightTotal->GetEntry(entry);   //!
  b_vertMulti->GetEntry(entry);   //!
  b_lumiWeight->GetEntry(entry);   //!
  b_trigEFF->GetEntry(entry);   //!
  b_btagSF->GetEntry(entry);   //!
  b_channel->GetEntry(entry);   //!
  b_MCSample->GetEntry(entry);   //!
  
  b_genJet_->GetEntry(entry);   //!
  b_genJetpX->GetEntry(entry);   //!
  b_genJetpY->GetEntry(entry);   //!
  b_genJetpZ->GetEntry(entry);   //!
  b_genJetE->GetEntry(entry);   //!
  
  
  b_HypTop_->GetEntry(entry);   //!
  b_HypToppX->GetEntry(entry);   //!
  b_HypToppY->GetEntry(entry);   //!
  b_HypToppZ->GetEntry(entry);   //!
  b_HypTopE->GetEntry(entry);   //!

  b_HypAntiTop_->GetEntry(entry);   //!
  b_HypAntiToppX->GetEntry(entry);   //!
  b_HypAntiToppY->GetEntry(entry);   //!
  b_HypAntiToppZ->GetEntry(entry);   //!
  b_HypAntiTopE->GetEntry(entry);   //!

  b_HypLepton_->GetEntry(entry);   //!
  b_HypLeptonpX->GetEntry(entry);   //!
  b_HypLeptonpY->GetEntry(entry);   //!
  b_HypLeptonpZ->GetEntry(entry);   //!
  b_HypLeptonE->GetEntry(entry);   //!

  b_HypAntiLepton_->GetEntry(entry);   //!
  b_HypAntiLeptonpX->GetEntry(entry);   //!
  b_HypAntiLeptonpY->GetEntry(entry);   //!
  b_HypAntiLeptonpZ->GetEntry(entry);   //!
  b_HypAntiLeptonE->GetEntry(entry);   //!

  b_HypB_->GetEntry(entry);   //!
  b_HypBpX->GetEntry(entry);   //!
  b_HypBpY->GetEntry(entry);   //!
  b_HypBpZ->GetEntry(entry);   //!
  b_HypBE->GetEntry(entry);   //!

  b_HypAntiB_->GetEntry(entry);   //!
  b_HypAntiBpX->GetEntry(entry);   //!
  b_HypAntiBpY->GetEntry(entry);   //!
  b_HypAntiBpZ->GetEntry(entry);   //!
  b_HypAntiBE->GetEntry(entry);   //!

  b_HypNeutrino_->GetEntry(entry);   //!
  b_HypNeutrinopX->GetEntry(entry);   //!
  b_HypNeutrinopY->GetEntry(entry);   //!
  b_HypNeutrinopZ->GetEntry(entry);   //!
  b_HypNeutrinoE->GetEntry(entry);   //!

  b_HypAntiNeutrino_->GetEntry(entry);   //!
  b_HypAntiNeutrinopX->GetEntry(entry);   //!
  b_HypAntiNeutrinopY->GetEntry(entry);   //!
  b_HypAntiNeutrinopZ->GetEntry(entry);   //!
  b_HypAntiNeutrinoE->GetEntry(entry);   //!

  b_HypWPlus_->GetEntry(entry);   //!
  b_HypWPluspX->GetEntry(entry);   //!
  b_HypWPluspY->GetEntry(entry);   //!
  b_HypWPluspZ->GetEntry(entry);   //!
  b_HypWPlusE->GetEntry(entry);   //!

  b_HypWMinus_->GetEntry(entry);   //!
  b_HypWMinuspX->GetEntry(entry);   //!
  b_HypWMinuspY->GetEntry(entry);   //!
  b_HypWMinuspZ->GetEntry(entry);   //!
  b_HypWMinusE->GetEntry(entry);   //!  

  b_HypJet0index->GetEntry(entry);
  b_HypJet1index->GetEntry(entry);
  b_decayMode->GetEntry(entry);
  
}

void Analysis::GetSignalBranches(Long64_t & entry)
{
   fChain->SetBranchAddress("GenTop.fCoordinates.fX", &GenToppX, &b_GenToppX);
   fChain->SetBranchAddress("GenTop.fCoordinates.fY", &GenToppY, &b_GenToppY);
   fChain->SetBranchAddress("GenTop.fCoordinates.fZ", &GenToppZ, &b_GenToppZ);
   fChain->SetBranchAddress("GenTop.fCoordinates.fT", &GenTopE, &b_GenTopE);
   fChain->SetBranchAddress("GenAntiTop.fCoordinates.fX", &GenAntiToppX, &b_GenAntiToppX);
   fChain->SetBranchAddress("GenAntiTop.fCoordinates.fY", &GenAntiToppY, &b_GenAntiToppY);
   fChain->SetBranchAddress("GenAntiTop.fCoordinates.fZ", &GenAntiToppZ, &b_GenAntiToppZ);
   fChain->SetBranchAddress("GenAntiTop.fCoordinates.fT", &GenAntiTopE, &b_GenAntiTopE);
   fChain->SetBranchAddress("GenLepton.fCoordinates.fX", &GenLeptonpX, &b_GenLeptonpX);
   fChain->SetBranchAddress("GenLepton.fCoordinates.fY", &GenLeptonpY, &b_GenLeptonpY);
   fChain->SetBranchAddress("GenLepton.fCoordinates.fZ", &GenLeptonpZ, &b_GenLeptonpZ);
   fChain->SetBranchAddress("GenLepton.fCoordinates.fT", &GenLeptonE, &b_GenLeptonE);
   fChain->SetBranchAddress("GenAntiLepton.fCoordinates.fX", &GenAntiLeptonpX, &b_GenAntiLeptonpX);
   fChain->SetBranchAddress("GenAntiLepton.fCoordinates.fY", &GenAntiLeptonpY, &b_GenAntiLeptonpY);
   fChain->SetBranchAddress("GenAntiLepton.fCoordinates.fZ", &GenAntiLeptonpZ, &b_GenAntiLeptonpZ);
   fChain->SetBranchAddress("GenAntiLepton.fCoordinates.fT", &GenAntiLeptonE, &b_GenAntiLeptonE);
   fChain->SetBranchAddress("GenNeutrino.fCoordinates.fX", &GenNeutrinopX, &b_GenNeutrinopX);
   fChain->SetBranchAddress("GenNeutrino.fCoordinates.fY", &GenNeutrinopY, &b_GenNeutrinopY);
   fChain->SetBranchAddress("GenNeutrino.fCoordinates.fZ", &GenNeutrinopZ, &b_GenNeutrinopZ);
   fChain->SetBranchAddress("GenNeutrino.fCoordinates.fT", &GenNeutrinoE, &b_GenNeutrinoE);
   fChain->SetBranchAddress("GenAntiNeutrino.fCoordinates.fX", &GenAntiNeutrinopX, &b_GenAntiNeutrinopX);
   fChain->SetBranchAddress("GenAntiNeutrino.fCoordinates.fY", &GenAntiNeutrinopY, &b_GenAntiNeutrinopY);
   fChain->SetBranchAddress("GenAntiNeutrino.fCoordinates.fZ", &GenAntiNeutrinopZ, &b_GenAntiNeutrinopZ);
   fChain->SetBranchAddress("GenAntiNeutrino.fCoordinates.fT", &GenAntiNeutrinoE, &b_GenAntiNeutrinoE);
   fChain->SetBranchAddress("GenB.fCoordinates.fX", &GenBpX, &b_GenBpX);
   fChain->SetBranchAddress("GenB.fCoordinates.fY", &GenBpY, &b_GenBpY);
   fChain->SetBranchAddress("GenB.fCoordinates.fZ", &GenBpZ, &b_GenBpZ);
   fChain->SetBranchAddress("GenB.fCoordinates.fT", &GenBE, &b_GenBE);
   fChain->SetBranchAddress("GenAntiB.fCoordinates.fX", &GenAntiBpX, &b_GenAntiBpX);
   fChain->SetBranchAddress("GenAntiB.fCoordinates.fY", &GenAntiBpY, &b_GenAntiBpY);
   fChain->SetBranchAddress("GenAntiB.fCoordinates.fZ", &GenAntiBpZ, &b_GenAntiBpZ);
   fChain->SetBranchAddress("GenAntiB.fCoordinates.fT", &GenAntiBE, &b_GenAntiBE);
   fChain->SetBranchAddress("GenWPlus.fCoordinates.fX", &GenWPluspX, &b_GenWPluspX);
   fChain->SetBranchAddress("GenWPlus.fCoordinates.fY", &GenWPluspY, &b_GenWPluspY);
   fChain->SetBranchAddress("GenWPlus.fCoordinates.fZ", &GenWPluspZ, &b_GenWPluspZ);
   fChain->SetBranchAddress("GenWPlus.fCoordinates.fT", &GenWPlusE, &b_GenWPlusE);
   fChain->SetBranchAddress("GenWMinus.fCoordinates.fX", &GenWMinuspX, &b_GenWMinuspX);
   fChain->SetBranchAddress("GenWMinus.fCoordinates.fY", &GenWMinuspY, &b_GenWMinuspY);
   fChain->SetBranchAddress("GenWMinus.fCoordinates.fZ", &GenWMinuspZ, &b_GenWMinuspZ);
   fChain->SetBranchAddress("GenWMinus.fCoordinates.fT", &GenWMinusE, &b_GenWMinusE);
  
  b_GenToppX->GetEntry(entry,1);   //!
  b_GenToppY->GetEntry(entry,1);   //!
  b_GenToppZ->GetEntry(entry,1);   //!
  b_GenTopE->GetEntry(entry,1);   //!

  b_GenAntiToppX->GetEntry(entry);   //!
  b_GenAntiToppY->GetEntry(entry);   //!
  b_GenAntiToppZ->GetEntry(entry);   //!
  b_GenAntiTopE->GetEntry(entry);   //!

  b_GenLeptonpX->GetEntry(entry);   //!
  b_GenLeptonpY->GetEntry(entry);   //!
  b_GenLeptonpZ->GetEntry(entry);   //!
  b_GenLeptonE->GetEntry(entry);   //!

  b_GenAntiLeptonpX->GetEntry(entry);   //!
  b_GenAntiLeptonpY->GetEntry(entry);   //!
  b_GenAntiLeptonpZ->GetEntry(entry);   //!
  b_GenAntiLeptonE->GetEntry(entry);   //!

  b_GenBpX->GetEntry(entry);   //!
  b_GenBpY->GetEntry(entry);   //!
  b_GenBpZ->GetEntry(entry);   //!
  b_GenBE->GetEntry(entry);   //!

  b_GenAntiBpX->GetEntry(entry);   //!
  b_GenAntiBpY->GetEntry(entry);   //!
  b_GenAntiBpZ->GetEntry(entry);   //!
  b_GenAntiBE->GetEntry(entry);   //!

  b_GenNeutrinopX->GetEntry(entry);   //!
  b_GenNeutrinopY->GetEntry(entry);   //!
  b_GenNeutrinopZ->GetEntry(entry);   //!
  b_GenNeutrinoE->GetEntry(entry);   //!

  b_GenAntiNeutrinopX->GetEntry(entry);   //!
  b_GenAntiNeutrinopY->GetEntry(entry);   //!
  b_GenAntiNeutrinopZ->GetEntry(entry);   //!
  b_GenAntiNeutrinoE->GetEntry(entry);   //!

  b_GenWPluspX->GetEntry(entry);   //!
  b_GenWPluspY->GetEntry(entry);   //!
  b_GenWPluspZ->GetEntry(entry);   //!
  b_GenWPlusE->GetEntry(entry);   //!

  b_GenWMinuspX->GetEntry(entry);   //!
  b_GenWMinuspY->GetEntry(entry);   //!
  b_GenWMinuspZ->GetEntry(entry);   //!
  b_GenWMinusE->GetEntry(entry);   //!  
}
#endif // #ifdef Analysis_cxx
