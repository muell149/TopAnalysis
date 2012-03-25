#define Analysis_cxx

#include "Analysis.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include "TLorentzVector.h"
#include <fstream>
#include <iostream>
#include <TMath.h>
#include <TSystem.h>
#include <set>


void Analysis::Begin(TTree * /*tree*/)
{

  TString option = GetOption();
  //  totalEventCount=0;

  EventCounter=0;

  ifstream insample("syst.txt",std::ios::in);
  insample>>systematic;

  ifstream inviatau("viaTau.txt",std::ios::in);
  inviatau>>viaTau;

  gStyle->SetOptStat(0);

  h_jetMultiAll = new TH1D("HypjetMultiAll", "Jet Multiplicity (AllJets)", 10, 0, 10);
  h_jetMultiXSec = new TH1D("HypjetMultiXSec", "Jet Multiplicity (for cross-section)", 10, 0, 10);
  h_jetMulti = new TH1D("HypjetMulti", "Jet Multiplicity", 10, 0, 10);
  h_jetMultiNoPU = new TH1D("HypjetMultiNoPU", "Jet Multiplicity (No Pileup or lumi weight)", 10, 0, 10);
  h_jetMultiVisTop = new TH1D("HypjetMultiVisTop", "Jet Multiplicity for Visible Top (No Pileup or lumi Weight)", 10, 0, 10);
  h_BjetMulti = new TH1D("HypBjetMulti", "B-Jet Multiplicity", 10, 0, 10);

  h_HypTTBarRapidity = new TH1D("HypTTBarRapidity","Rapidity of TTbar System (HYP)",50,-5,5);
  h_HypTTBarpT = new TH1D("HypTTBarpT","pT of TTbar System (HYP)",100,0,500);
  h_HypTTBarMass = new TH1D("HypTTBarMass","Mass of TTbar System (HYP)",400,0,2000);
  h_HypLLBarMass = new TH1D("HypLLBarMass","Mass of LLbar System (HYP)",500,0,1000);
  h_HypLLBarpT = new TH1D("HypLLBarpT","pT of LLbar System (HYP)",500,0,1000);

  h_GenTTBarMass = new TH1D("GenTTBarMass","Mass of TTbar System(GEN)",240,0,1200);
  h_GenTTBarRapidity = new TH1D("GenTTBarRapidity","Rapidity of TTbar System(GEN)",50,-5,5);
  h_GenTTBarpT = new TH1D("GenTTBarpT","pT of TTbar System(GEN)",240,0,1200);
  h_GenLLBarpT = new TH1D("GenLLBarpT","pT of LLbar System(GEN)",500,0,1000);
  h_GenLLBarMass = new TH1D("GenLLBarMass","Mass of LLbar System(GEN)",500,0,1000);

  h_VisGenTTBarMass = new TH1D("VisGenTTBarMass","Mass of TTbar System(VisGEN)",240,0,1200);
  h_VisGenTTBarRapidity = new TH1D("VisGenTTBarRapidity","Rapidity of TTbar System(VisGEN)",50,-5,5);
  h_VisGenTTBarpT = new TH1D("VisGenTTBarpT","pT of TTbar System(VisGEN)",240,0,1200);
  h_VisGenTopRapidity = new TH1D("VisGenTopRapidity","Rapidity of Top(VisGEN)",100,-5,5);
  h_VisGenAntiTopRapidity = new TH1D("VisGenAntiTopRapidity","Rapidity of AntiTop(VisGEN)",50,-5,5);

  h_VisGenLLBarpT = new TH1D("VisGenLLBarpT","pT of LLbar System(VisGEN)",500,0,1000);
  h_VisGenLLBarMass = new TH1D("VisGenLLBarMass","Mass of LLbar System(VisGEN)",500,0,1000);

  h_RecoTTBarMass = new TH1D("RecoTTBarMass","Mass of TTbar System (HYP)",240,0,1200);
  h_RecoTTBarRapidity = new TH1D("RecoTTBarRapidity","Rapidity of TTbar System (HYP)",50,-5,5);
  h_RecoTTBarpT = new TH1D("RecoTTBarpT","pT of TTbar System (HYP)",240,0,1200);
  h_RecoToppT = new TH1D("RecoToppT","pT of Top (HYP)",240,0,1200);
  h_RecoAntiToppT = new TH1D("RecoAntiToppT","pT of AntiTop (HYP)",240,0,1200);
  h_RecoTopRapidity = new TH1D("RecoTopRapidity","Rapidity of Top (HYP)",50,-5,5);
  h_RecoAntiTopRapidity = new TH1D("RecoAntiTopRapidity","Rapidity of AntiTop (HYP)",50,-5,5);

  h_RecoBJetpT = new TH1D("RecoBJetpT","pT of Top (HYP)",240,0,1200);
  h_RecoAntiBJetpT = new TH1D("RecoAntiBJetpT","pT of AntiTop (HYP)",240,0,1200);
  h_RecoBJetRapidity = new TH1D("RecoBJetRapidity","Rapidity of Top (HYP)",50,-5,5);
  h_RecoAntiBJetRapidity = new TH1D("RecoAntiBJetRapidity","Rapidity of AntiTop (HYP)",50,-5,5);

  h_RecoLLBarMass = new TH1D("RecoLLBarMass","Mass of LLbar System (HYP)",500,0,1000);
  h_RecoLLBarpT = new TH1D("RecoLLBarpT","pT of LLbar System (HYP)",500,0,1000);
  h_RecoLeptonpT = new TH1D("RecoLeptonpT","pT of Lepton (HYP)",240,0,1200);
  h_RecoAntiLeptonpT = new TH1D("RecoAntiLeptonpT","pT of AntiLepton (HYP)",240,0,1200);
  h_RecoLeptonEta = new TH1D("RecoLeptonEta","Eta of Lepton (HYP)",80,-4,4);
  h_RecoAntiLeptonEta = new TH1D("RecoAntiLeptonEta","Eta of AntiLepton (HYP)",80,-4,4);

  h_VisGenAll = new TH1D("VisGenAll","All Visible Generated particles (IM)",40,0,400);
  h_GenAll = new TH1D("GenAll","AllGenerated particles (IM)",40,0,400);
  Allh1 = new TH1D("Allh1","DiLepton Mass",40,0,400);
  h_diLepMassFull = new TH1D("DIMFull","DiLepton Mass (Full Range)",100,0,300);
  Looseh1 = new TH1D("Looseh1","DiLepton Mass",40,0,400);
  Zh1 = new TH1D("Zh1","DiLepton Mass in Z Window",40,0,400);
  TTh1 = new TH1D("TTh1","DiLepton Mass out of Z Window",40,0,400);

  h_vertMulti = new TH1D("vertMulti", "Primary Vertex Multiplicity", 30, 0, 30);
  h_MET = new TH1D("MET", "Missing Transverse Energy", 80, 0, 400);
  h_jetpT = new TH1D("jetpT", "jet pT", 80, 0, 400);  
  h_jetHT = new TH1D("jetHT", "jet HT", 80, 0, 1000);  

  h_MuonpT = new TH1D("MuonpT","Muon pT (emu channel)",80,0,400);
  h_MuonEta = new TH1D("MuonEta","Muon Eta (emu channel)",80,-4,4);
  h_ElectronpT = new TH1D("ElectronpT","Electron pT (emu channel)",80,0,400);
  h_ElectronEta = new TH1D("ElectronEta","Electron Eta (emu channel)",80,-4,4);

  h_LeptonpT = new TH1D("LeptonpT","Lepton pT",80,0,400);
  h_LeptonEta = new TH1D("LeptonEta","Lepton Eta",80,-4,4);

  h_AntiLeptonpT = new TH1D("AntiLeptonpT","AntiLepton pT",80,0,400);
  h_AntiLeptonEta = new TH1D("AntiLeptonEta","AntiLepton Eta",80,-4,4);

  h_HypToppT = new TH1D("HypToppT","Top pT",80,0,400);
  h_HypTopEta = new TH1D("HypTopEta","Top pT",80,-4,4);
  h_HypTopMass = new TH1D("HypTopMass","Top Mass",80,0,400);
  h_HypTopRapidity = new TH1D("HypTopRapidity","Top Rapidity",100,-5,5);

  h_HypAntiToppT = new TH1D("HypAntiToppT","AntiTop pT",80,0,400);
  h_HypAntiTopEta = new TH1D("HypAntiTopEta","AntiTop pT",80,-4,4);
  h_HypAntiTopMass = new TH1D("HypAntiTopMass","AntiTop Mass",80,0,400);
  h_HypAntiTopRapidity = new TH1D("HypAntiTopRapidity","Top Rapidity",50,-5,5);

  h_HypLeptonpT = new TH1D("HypLeptonpT","Lepton Hypothesis pT",80,0,400);
  h_HypLeptonEta = new TH1D("HypLeptonEta","Lepton Eta",80,-4,4);

  h_HypAntiLeptonpT = new TH1D("HypAntiLeptonpT","AntiLepton Hypothesis pT",80,0,400);
  h_HypAntiLeptonEta = new TH1D("HypAntiLeptonEta","AntiLepton Hypothesis Eta",80,-4,4);

  h_HypBJetpT = new TH1D("HypBJetpT","B Hypothesis pT",80,0,400);
  h_HypBJetEta = new TH1D("HypBJetEta","B Hypothesis Eta",80,-4,4);
  h_HypBJetRapidity = new TH1D("HypBJetRapidity","B Hypothesis Eta",50,-5,5);

  h_HypAntiBJetpT = new TH1D("HypAntiBJetpT","AntiB Hypothesis pT",80,0,400);
  h_HypAntiBJetEta = new TH1D("HypAntiBJetEta","AntiB Hypothesis Eta",80,-4,4);
  h_HypAntiBJetRapidity = new TH1D("HypAntiBJetRapidity","AntiB Hypothesis Eta",50,-5,5);

  h_VisGenToppT = new TH1D("VisGenToppT","Top pT (VisGen)",80,0,400);
  h_VisGenTopEta = new TH1D("VisGenTopEta","Top Eta (VisGen)",80,-4,4);

  h_VisGenAntiToppT = new TH1D("VisGenAntiToppT","AntiTop pT (VisGen)",80,0,400);
  h_VisGenAntiTopEta = new TH1D("VisGenAntiTopEta","AntiTop pT (VisGen)",80,-4,4);

  h_VisGenLeptonpT = new TH1D("VisGenLeptonpT","Lepton VisGenothesis pT",80,0,400);
  h_VisGenLeptonEta = new TH1D("VisGenLeptonEta","Lepton Eta",80,-4,4);

  h_VisGenAntiLeptonpT = new TH1D("VisGenAntiLeptonpT","AntiLepton VisGenothesis pT",80,0,400);
  h_VisGenAntiLeptonEta = new TH1D("VisGenAntiLeptonEta","AntiLepton VisGenothesis Eta",80,-4,4);

  h_VisGenBJetpT = new TH1D("VisGenBJetpT","B VisGenothesis pT",80,0,400);
  h_VisGenBJetEta = new TH1D("VisGenBJetEta","B VisGenothesis Eta",80,-4,4);
  h_VisGenBJetRapidity = new TH1D("VisGenBJetRapidity","B VisGenothesis Rapidity",100,-5,5);

  h_VisGenAntiBJetpT = new TH1D("VisGenAntiBJetpT","AntiB VisGenothesis pT",80,0,400);
  h_VisGenAntiBJetEta = new TH1D("VisGenAntiBJetEta","AntiB VisGenothesis Eta",80,-4,4);
  h_VisGenAntiBJetRapidity = new TH1D("VisGenAntiBJetRapidity","AntiB VisGenothesis Rapidity",100,-5,5);

  h_VisGenBQuarkpT = new TH1D("VisGenBQuarkpT","B Quark VisGenothesis pT",80,0,400);
  h_VisGenBQuarkEta = new TH1D("VisGenBQuarkEta","B Quark VisGenothesis Eta",80,-4,4);
  h_VisGenBQuarkRapidity = new TH1D("VisGenBQuarkRapidity","B Quark VisGenothesis Rapidity",100,-5,5);

  h_VisGenAntiBQuarkpT = new TH1D("VisGenAntiBQuarkpT","AntiB Quark VisGenothesis pT",80,0,400);
  h_VisGenAntiBQuarkEta = new TH1D("VisGenAntiBQuarkEta","AntiB Quark VisGenothesis Eta",80,-4,4);
  h_VisGenAntiBQuarkRapidity = new TH1D("VisGenAntiBQuarkRapidity","AntiB Quark VisGenothesis Rapidity",100,-5,5);

  h_GenToppT = new TH1D("GenToppT","Top pT (Gen)",80,0,400);
  h_GenTopEta = new TH1D("GenTopEta","Top Eta (Gen)",80,-4,4);
  h_GenTopRapidity = new TH1D("GenTopRapidity","Top Rapidity (Gen)",100,-5,5);
  
  h_GenAntiToppT = new TH1D("GenAntiToppT","AntiTop pT (Gen)",80,0,400);
  h_GenAntiTopEta = new TH1D("GenAntiTopEta","AntiTop Eta (Gen)",80,-4,4);
  h_GenAntiTopRapidity = new TH1D("GenAntiTopRapidity","AntiTop Rapidity (Gen)",100,-5,5);

  h_GenLeptonpT = new TH1D("GenLeptonpT","Lepton Genothesis pT",80,0,400);
  h_GenLeptonEta = new TH1D("GenLeptonEta","Lepton Eta",80,-4,4);

  h_GenAntiLeptonpT = new TH1D("GenAntiLeptonpT","AntiLepton Genothesis pT",80,0,400);
  h_GenAntiLeptonEta = new TH1D("GenAntiLeptonEta","AntiLepton Genothesis Eta",80,-4,4);

  h_GenBQuarkpT = new TH1D("GenBQuarkpT","B Quark Genothesis pT",80,0,400);
  h_GenBQuarkEta = new TH1D("GenBQuarkEta","B Quark Genothesis Eta",80,-4,4);
  h_GenBQuarkRapidity = new TH1D("GenBQuarkRapidity","B Quark Genothesis Rapidity",100,-5,5);

  h_GenAntiBQuarkpT = new TH1D("GenAntiBQuarkpT","AntiB Quark Genothesis pT",80,0,400);
  h_GenAntiBQuarkEta = new TH1D("GenAntiBQuarkEta","AntiB Quark Genothesis Eta",80,-4,4);
  h_GenAntiBQuarkRapidity = new TH1D("GenAntiBQuarkRapidity","AntiB Quark Genothesis Rapidity",100,-5,5);
  
  h_GenBJetpT = new TH1D("GenBJetpT","B Genothesis pT",80,0,400);
  h_GenBJetEta = new TH1D("GenBJetEta","B Genothesis Eta",80,-4,4);
  h_GenBJetRapidity = new TH1D("GenBJetRapidity","B Genothesis Rapidity",100,-5,5);

  h_GenAntiBJetpT = new TH1D("GenAntiBJetpT","AntiB Genothesis pT",80,0,400);
  h_GenAntiBJetEta = new TH1D("GenAntiBJetEta","AntiB Genothesis Eta",80,-4,4);
  h_GenAntiBJetRapidity = new TH1D("GenAntiBJetRapidity","Anti B Genothesis Rapidity",100,-5,5);

  h_GenRecoBJetpT = new TH2D("GenRecoBJetpT", "Gen/Reco Matching", 80,0,400,80,0,400);
  h_GenRecoBJetEta = new TH2D("GenRecoBJetEta", "Gen/Reco Matching", 100,-5,5,100,-5,5);
  h_GenRecoBJetRapidity = new TH2D("GenRecoBJetRapidity", "Gen/Reco Matching", 100,-5,5,100,-5,5);

  h_GenRecoAntiBJetpT = new TH2D("GenRecoAntiBJetpT", "Gen/Reco Matching", 80,0,400,80,0,400);
  h_GenRecoAntiBJetEta = new TH2D("GenRecoAntiBJetEta", "Gen/Reco Matching", 100,-5,5,100,-5,5);
  h_GenRecoAntiBJetRapidity = new TH2D("GenRecoAntiBJetRapidity", "Gen/Reco Matching", 100,-5,5,100,-5,5);
  
  h_GenRecoLeptonEta = new TH2D("GenRecoLeptonEta", "Gen/Reco Matching", 100,-5,5,100,-5,5);
  h_GenRecoAntiLeptonEta = new TH2D("GenRecoAntiLeptonEta", "Gen/Reco Matching", 100,-5,5,100,-5,5);
  h_GenRecoLeptonpT = new TH2D("GenRecoLeptonpT", "Gen/Reco Matching", 80,0,400,80,0,400);
  h_GenRecoAntiLeptonpT = new TH2D("GenRecoAntiLeptonpT", "Gen/Reco Matching", 80,0,400,80,0,400);

  h_GenRecoTopRapidity = new TH2D("GenRecoTopRapidity", "Gen/Reco Matching", 100,-5,5,100,-5,5);
  h_GenRecoAntiTopRapidity = new TH2D("GenRecoAntiTopRapidity", "Gen/Reco Matching", 100,-5,5,100,-5,5);
  h_GenRecoToppT = new TH2D("GenRecoToppT", "Gen/Reco Matching", 80,0,400,80,0,400);
  h_GenRecoAntiToppT = new TH2D("GenRecoAntiToppT", "Gen/Reco Matching", 80,0,400,80,0,400);

  h_GenRecoTTBarRapidity = new TH2D("GenRecoTTBarRapidity","Rapidity of TTbar System (HYP)",100,-5,5,100,-5,5);
  h_GenRecoTTBarpT = new TH2D("GenRecoTTBarpT","pT of TTbar System (HYP)",50,0,500,50,0,500);
  h_GenRecoTTBarMass = new TH2D("GenRecoTTBarMass","Mass of TTbar System (HYP)",100,0,2000,100,0,2000);
  h_GenRecoLLBarMass = new TH2D("GenRecoLLBarMass","Mass of LLbar System (HYP)",500,0,1000,500,0,1000);
  h_GenRecoLLBarpT = new TH2D("GenRecoLLBarpT","pT of LLbar System (HYP)",500,0,1000,500,0,1000);


  h_NJetMatching = new TH1D("NJetMatching", "NJet Gen/Reco Matching",5,0,5);
  
}

void Analysis::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

}

Bool_t Analysis::Process(Long64_t entry)
{
  Analysis::GetAllBranches(entry);
  //initial check to see if we are doing the signal via tau (which is now background)
  if(viaTau=="viaTau"){
    if((MCSample->find("ttbarsignal")!=string::npos) && (decayMode>40 || (decayMode%10 > 4))){
      MCSample->clear();
      MCSample->append("ttbarbgviatau");
    }else{
      return kTRUE;
    }
  }else if(viaTau == "Nominal"){
    if((MCSample->find("ttbarsignal")!=string::npos) &&(decayMode>40 || (decayMode%10 > 4))){
      return kTRUE;
    }
  }else{
    cout<<"Something went wrong"<<endl;
  }
  if(MCSample->find("ttbarsignal")!=string::npos){ Analysis::GetSignalBranches(entry);}
  if(MCSample->find("run")!=string::npos){ weightLepSF = 1.0;}
  EventCounter++;
  if(EventCounter % 10000 == 0){cout<<"Event Counter: "<<EventCounter<<endl;}
  float dimass=0.;
  double btagSFuse=1.0;//only use the btag SF when applying b-tagging
  double weightKinFituse = 1.0;//only use the kin fit SF when using the kinematic reconstruction
  if(systematic=="PU_UP"){weightPU = weightPU_Up;}//only for PU systematic run
  if(systematic=="PU_DOWN"){weightPU = weightPU_Down;}//only for PU systematic run
  std::vector<float> VLepton;

  std::vector<TLorentzVector> LVlepton;
  std::vector<TLorentzVector> LVjet;
  

  std::vector<TLorentzVector> LVHypTop;
  std::vector<TLorentzVector> LVHypAntiTop;
  std::vector<TLorentzVector> LVHypBJet;
  std::vector<TLorentzVector> LVHypAntiBJet;
  std::vector<TLorentzVector> LVHypLepton;
  std::vector<TLorentzVector> LVHypAntiLepton;

  for(int i=0; i<jet_; i++){
    TLorentzVector jettemp(jetpX[i],jetpY[i],jetpZ[i],jetE[i]);
    LVjet.push_back(jettemp);
  }

  for(int i=0; i<HypTop_;i++){ 
    TLorentzVector antitoptemp(HypAntiToppX[i], HypAntiToppY[i], HypAntiToppZ[i], HypAntiTopE[i]);
    LVHypAntiTop.push_back(antitoptemp);
    TLorentzVector toptemp(HypToppX[i], HypToppY[i], HypToppZ[i], HypTopE[i]);
    LVHypTop.push_back(toptemp);
    TLorentzVector antibtemp(HypAntiBpX[i], HypAntiBpY[i], HypAntiBpZ[i], HypAntiBE[i]);
    LVHypAntiBJet.push_back(antibtemp);
    TLorentzVector btemp(HypBpX[i], HypBpY[i], HypBpZ[i], HypBE[i]);
    LVHypBJet.push_back(btemp);
    TLorentzVector antileptontemp(HypAntiLeptonpX[i], HypAntiLeptonpY[i], HypAntiLeptonpZ[i], HypAntiLeptonE[i]);
    LVHypAntiLepton.push_back(antileptontemp);
    TLorentzVector leptontemp(HypLeptonpX[i], HypLeptonpY[i], HypLeptonpZ[i], HypLeptonE[i]);
    LVHypLepton.push_back(leptontemp);
  }


  TLorentzVector LVGenAntiTop(GenAntiToppX, GenAntiToppY, GenAntiToppZ, GenAntiTopE);
  TLorentzVector LVGenTop(GenToppX, GenToppY, GenToppZ, GenTopE);    
  TLorentzVector LVGenAntiBQuark(GenAntiBpX, GenAntiBpY, GenAntiBpZ, GenAntiBE);    
  TLorentzVector LVGenBQuark(GenBpX, GenBpY, GenBpZ, GenBE);    
  TLorentzVector LVGenAntiLepton(GenAntiLeptonpX, GenAntiLeptonpY, GenAntiLeptonpZ, GenAntiLeptonE);    
  TLorentzVector LVGenLepton(GenLeptonpX, GenLeptonpY, GenLeptonpZ, GenLeptonE);
  std::vector<TLorentzVector> LVGenJets;
  set<int> BHadIndex;

  std::vector<TLorentzVector> LVBHadrons;
  std::vector<TLorentzVector> LVAntiBHadrons;
  TLorentzVector LVBHadronGenJet;
  TLorentzVector LVAntiBHadronGenJet;
  
  for(int i=0; i<lepton_;i++){
    TLorentzVector leptemp(leptonpX[i], leptonpY[i], leptonpZ[i], leptonE[i]);
    LVlepton.push_back(leptemp);
  }

  if(MCSample->find("ttbarsignal")!=string::npos){
    
    for(int i=0; i<allGenJets_;i++){
      TLorentzVector genjettemp(allGenJetspX[i], allGenJetspY[i], allGenJetspZ[i], allGenJetsE[i]);
      LVGenJets.push_back(genjettemp);
    }
    
    for(int i=0; i<BHadrons_;i++){
      TLorentzVector bhadrontemp(BHadronspX[i], BHadronspY[i], BHadronspZ[i], BHadronsE[i]);
      LVBHadrons.push_back(bhadrontemp);
    }
    
    for(int i=0; i<AntiBHadrons_;i++){
      TLorentzVector antibhadrontemp(AntiBHadronspX[i], AntiBHadronspY[i], AntiBHadronspZ[i], AntiBHadronsE[i]);
      LVAntiBHadrons.push_back(antibhadrontemp);
    }
    
    std::vector<int> idx_bHadJet;
    std::vector<int> idx_antibHadJet;
    //To avoid recopying may code lines, we select HERE the BHadron JET Indices to cut on.
    int BHadronIndex;
    int AntiBHadronIndex;
  
    LVBHadronGenJet =  TLorentzVector(BHadronJetpX, BHadronJetpY, BHadronJetpZ, BHadronJetE);
    LVAntiBHadronGenJet = TLorentzVector(AntiBHadronJetpX, AntiBHadronJetpY, AntiBHadronJetpZ, AntiBHadronJetE);
    
  
    
    for(int i=0; i<(int) BHadJetIndex->size(); i++){	BHadIndex.insert((*BHadJetIndex)[i]);	}
    for(int i=0; i<(int) AntiBHadJetIndex->size(); i++){	BHadIndex.insert((*AntiBHadJetIndex)[i]);	}
    
    //time to choose which genJet we actually want  
    idx_bHadJet.insert(idx_bHadJet.begin(), 4, -1);
    idx_antibHadJet.insert(idx_antibHadJet.begin(), 4, -1);
    /*
      idx_bHadJet will have 4 jet indices 
      [0] is the highest pT jet with a B-Hadron
      [1] is the highest pT jet with a B-Hadron also matched to a top quark
      [2] highest pT jet of those matched closest (in DeltaR) to the B-Hadron
      [3] highest pT jet of those matched closest (in DeltaR) to the B-Hadron also matched to a top quark
    */
    
    bool BHadhighpTjet = false;
    bool BHadhighpTjetfromtop = false;
    bool AntiBHadhighpTjet = false;
    bool AntiBHadhighpTjetfromtop = false;

    //Case 1: highest pT genJet matched to a BHadron
    for(int genJet=0; genJet<allGenJets_; genJet++){
      for(int bHadron=0; bHadron<BHadrons_; bHadron++){
	if((*BHadronVsJet)[genJet*BHadrons_+bHadron]==1 && (BHadhighpTjet ==false || BHadhighpTjetfromtop == false)){
	  if(BHadhighpTjet==false){
	    idx_bHadJet[0] = genJet;
	    BHadhighpTjet = true;
	    if((*BHadronFromTopB)[bHadron] == true){
	      idx_bHadJet[1] = genJet;
	      BHadhighpTjetfromtop = true;
	    }
	  }else if(BHadhighpTjetfromtop == false){
	    if((*BHadronFromTopB)[bHadron] == true){
	      idx_bHadJet[1] = genJet;
	      BHadhighpTjetfromtop = true;
	    }
	  }
	}      
      }

      for(int antibHadron=0; antibHadron<AntiBHadrons_; antibHadron++){
	if((*AntiBHadronVsJet)[genJet*AntiBHadrons_+antibHadron]==1 && (AntiBHadhighpTjet ==false || AntiBHadhighpTjetfromtop == false)){
	  if(AntiBHadhighpTjet==false){
	    idx_antibHadJet[0] = genJet;
	    AntiBHadhighpTjet = true;
	    if((*AntiBHadronFromTopB)[antibHadron] == true){
	      idx_antibHadJet[1] = genJet;
	      AntiBHadhighpTjetfromtop = true;
	    }
	  }else if(AntiBHadhighpTjetfromtop == false){
	    if((*AntiBHadronFromTopB)[antibHadron] == true){
	      idx_antibHadJet[1] = genJet;
	      AntiBHadhighpTjetfromtop = true;
	    }
	  }
	}
      }

    }
    
    //Case 2: highest pT genJets matched closest to a BHadron
    //BHadJetIndex: vector containing the GetJet indices matched, in DeltaR, to a BHadron. Starting from the highest pT jet.
    if (BHadJetIndex->size() != 0) idx_bHadJet[2] = (*BHadJetIndex)[0];
    for (int i=0; i<(int) BHadJetIndex->size(); ++i){ 
      //Only search for those jets matched in DeltaR with a BHadron
      for(int j=0; j<BHadrons_ ; ++j){
	//if ((*BHadronVsJet)[i*BHadrons_+j] == 1 && (*BHadronFromTopB)[j] == true) {idx_bHadJet[3] = (*BHadJetIndex)[i];}
	if ((*BHadronVsJet)[((*BHadJetIndex)[i])*BHadrons_+j] == 1 && (*BHadronFromTopB)[j] == true) {idx_bHadJet[3] = (*BHadJetIndex)[i];}
      }
    }
    
    //AntiBHadJetIndex: vector containing the GetJet indices matched, in DeltaR, to a AntiBHadron. Starting from the highest pT jet.
    if (AntiBHadJetIndex->size() != 0) idx_antibHadJet[2] = (*AntiBHadJetIndex)[0];
    for (int i=0; i<(int) AntiBHadJetIndex->size(); ++i){ 
      //Only search for those jets matched in DeltaR with a AntiBHadron
      for(int j=0; j<AntiBHadrons_ ; ++j){
	//if ((*AntiBHadronVsJet)[i*AntiBHadrons_+j] == 1 && (*AntiBHadronFromTopB)[j] == true) {idx_antibHadJet[3] = (*AntiBHadJetIndex)[i];}
	if ((*AntiBHadronVsJet)[((*AntiBHadJetIndex)[i])*AntiBHadrons_+j] == 1 && (*AntiBHadronFromTopB)[j] == true) {idx_antibHadJet[3] = (*AntiBHadJetIndex)[i];}
      }
    }

//     if(EventCounter % 1000 == 0 ){//&& idx_bHadJet.size()>1 && idx_antibHadJet.size()>1){
//       cout<<"-----------------"<<endl;
//       cout<<"idx_bHadJet.size(): "<<idx_bHadJet.size()<<endl;
//       cout<<"idx_bHadJet[0]: "<<idx_bHadJet[0]<<endl;
//       cout<<"idx_bHadJet[1]: "<<idx_bHadJet[1]<<endl;
//       cout<<"idx_bHadJet[2]: "<<idx_bHadJet[2]<<endl;
//       cout<<"idx_bHadJet[3]: "<<idx_bHadJet[3]<<endl;
//       cout<<"idx_antibHadJet.size()"<<idx_antibHadJet.size()<<endl;
//       cout<<"idx_antibHadJet[0]: "<<idx_antibHadJet[0]<<endl;
//       cout<<"idx_antibHadJet[1]: "<<idx_antibHadJet[1]<<endl;
//       cout<<"idx_antibHadJet[2]: "<<idx_antibHadJet[2]<<endl;
//       cout<<"idx_antibHadJet[3]: "<<idx_antibHadJet[3]<<endl;
//     }
    
    
//     //To avoid recopying many code lines, we select HERE the BHadron JET Indices to cut on.
//     int BHadronIndex;
//     int AntiBHadronIndex;
    //Case 1A: highest pT genJet matched to a BHadron
//     BHadronIndex = idx_bHadJet[0];
//     AntiBHadronIndex = idx_antibHadJet[0];
//   
  //   //Case 1B: highest pT genJet matched to a BHadron from Top
//     BHadronIndex = idx_bHadJet[1];
//     AntiBHadronIndex = idx_antibHadJet[1];
    
  //   //Case 2A: highest pT genJets matched closest to a BHadron
// //     BHadronIndex = idx_bHadJet[2];
// //     AntiBHadronIndex = idx_antibHadJet[2];
  //   
  //   //Case 2B: highest pT genJets matched closest to a BHadron from Top
    BHadronIndex = idx_bHadJet[3];
    AntiBHadronIndex = idx_antibHadJet[3];


  }
  
  double BtagWP = 0.244; //CSV Loose working point
  vector<int> BJetIndex;
  for(vector<double>::iterator it = jetBTagCSV->begin(); it<jetBTagCSV->end(); it++){
    if(*it > BtagWP){
      BJetIndex.push_back(*it);
    }    
  }

  
  
  //Should we just look for two Bjets above 0.244 or the two highest bjets?:: Make this a function
  int solutionIndex = 0;
  bool oneTag = false;
  bool twoTag = false;
  for(int i =0; i<HypTop_; i++){
    if((*jetBTagCSV)[(*HypJet0index)[i]] > BtagWP && (*jetBTagCSV)[(*HypJet1index)[i]]>BtagWP){
      solutionIndex = i; 
      twoTag = true;
      break;
    }
    if(oneTag == false && ((*jetBTagCSV)[(*HypJet0index)[i]] > BtagWP || (*jetBTagCSV)[(*HypJet1index)[i]]>BtagWP)){
      solutionIndex = i; 
      oneTag=true;
    }
  }  
  //solutionIndex = 0;

  
  if(MCSample->find("ttbarsignal")!=string::npos){  
    
    h_GenAll->Fill(LVGenTop.M(),1);
    if (LVGenLepton.Pt()>20 && LVGenAntiLepton.Pt()>20 && abs(LVGenLepton.Eta())<2.4 && abs(LVGenAntiLepton.Eta())<2.4){
     //Comment the next 2 lines and uncomment the 3rd one for gen-level Vis PS cuts
       if (LVGenBQuark.Pt()>30 && LVGenAntiBQuark.Pt()>30 && abs(LVGenBQuark.Eta())<2.4 && abs(LVGenAntiBQuark.Eta())<2.4){
//       if (BHadIndex.size() >= 2 && LVGenJets[*(BHadIndex.begin())].Pt()>30 && LVGenJets[*(++BHadIndex.begin())].Pt()>30 &&
// 	  abs(LVGenJets[*(BHadIndex.begin())].Eta())<2.4 && abs(LVGenJets[*(++BHadIndex.begin())].Eta())<2.4){
//       if(BHadronIndex != -1 && LVGenJets[BHadronIndex].Pt()>30 && abs(LVGenJets[BHadronIndex].Eta())<2.4 &&
// 	AntiBHadronIndex != -1 && LVGenJets[AntiBHadronIndex].Pt()>30 && abs(LVGenJets[AntiBHadronIndex].Eta())<2.4 ){
//       if(LVBHadronGenJet.Pt()>30 && abs(LVBHadronGenJet.Eta())<2.4 &&
// 	LVAntiBHadronGenJet.Pt()>30 && abs(LVAntiBHadronGenJet.Eta())<2.4){
  
	h_VisGenAll->Fill(LVGenTop.M(),1); 
        double VisGenTTBarMass = (LVGenTop+ LVGenAntiTop).M();
	h_VisGenTTBarMass->Fill(VisGenTTBarMass,1);
	h_VisGenTTBarRapidity->Fill((LVGenTop+ LVGenAntiTop).Rapidity(),1);
	h_VisGenTTBarpT->Fill((LVGenTop+ LVGenAntiTop).Pt(),1);
	h_VisGenTopRapidity->Fill(LVGenTop.Rapidity(),1);
	h_VisGenAntiTopRapidity->Fill(LVGenAntiTop.Rapidity(),1);

	h_VisGenLLBarpT->Fill((LVGenLepton+ LVGenAntiLepton).Pt(),1);
	h_VisGenLLBarMass->Fill((LVGenLepton+ LVGenAntiLepton).M(),1);
	
	h_VisGenToppT->Fill(LVGenTop.Pt(),1);
	h_VisGenAntiToppT->Fill(LVGenAntiTop.Pt(),1);
	h_VisGenBQuarkpT->Fill(LVGenBQuark.Pt(),1);
	h_VisGenAntiBQuarkpT->Fill(LVGenAntiBQuark.Pt(),1);
	h_VisGenLeptonpT->Fill(LVGenLepton.Pt(),1);
	h_VisGenAntiLeptonpT->Fill(LVGenAntiLepton.Pt(),1);
// 	h_VisGenBJetpT->Fill(LVGenJets[BHadronIndex].Pt(),1);
// 	h_VisGenAntiBJetpT->Fill(LVGenJets[AntiBHadronIndex].Pt(),1);
	h_VisGenBJetpT->Fill(LVBHadronGenJet.Pt(),1);
	h_VisGenAntiBJetpT->Fill(LVAntiBHadronGenJet.Pt(),1);
// 	h_VisGenBJetpT->Fill(LVGenJets[*(BHadIndex.begin())].Pt(),1);
// 	h_VisGenAntiBJetpT->Fill(LVGenJets[*(++BHadIndex.begin())].Pt(),1);
	
	h_VisGenTopEta->Fill(LVGenTop.Eta(),1);
	h_VisGenAntiTopEta->Fill(LVGenAntiTop.Eta(),1);
	h_VisGenBQuarkEta->Fill(LVGenBQuark.Eta(),1);
	h_VisGenAntiBQuarkEta->Fill(LVGenAntiBQuark.Eta(),1);
	h_VisGenLeptonEta->Fill(LVGenLepton.Eta(),1);
	h_VisGenAntiLeptonEta->Fill(LVGenAntiLepton.Eta(),1);
// 	h_VisGenBJetEta->Fill(LVGenJets[*(BHadIndex.begin())].Eta(),1);
// 	h_VisGenAntiBJetEta->Fill(LVGenJets[*(++BHadIndex.begin())].Eta(),1);
	
// 	h_VisGenTopE->Fill(LVGenTop.E(),1);
// 	h_VisGenAntiTopE->Fill(LVGenAntiTop.E(),1);
// 	h_VisGenBQuarkE->Fill(LVGenBQuark.E(),1);
// 	h_VisGenAntiBQuarkE->Fill(LVGenAntiBQuark.E(),1);
// 	h_VisGenLeptonE->Fill(LVGenLepton.E(),1);
// 	h_VisGenAntiLeptonE->Fill(LVGenAntiLepton.E(),1);
//  	h_VisGenBJetE->Fill(LVGenJets[*(BHadIndex.begin())].E(),1);
//  	h_VisGenAntiBJetE->Fill(LVGenJets[*(++BHadIndex.begin())].E(),1);
// 
// 	h_VisGenBJetRapidity->Fill(LVGenJets[*(BHadIndex.begin())].Rapidity(),1);
// 	h_VisGenAntiBJetRapidity->Fill(LVGenJets[*(++BHadIndex.begin())].Rapidity(),1);
// 	h_VisGenBQuarkRapidity->Fill(LVGenBQuark.Rapidity(),1);
// 	h_VisGenAntiBQuarkRapidity->Fill(LVGenAntiBQuark.Rapidity(),1);

      }    
    }
  }//for visible top events

  //check triggers for ttbarsignal
  if(MCSample->find("ttbarsignal")!=string::npos){  
    if(channel->find("emu")!=string::npos && ((triggerBits & 0x1000) || (triggerBits & 0x100) || (triggerBits & 0x200))){
      int emutrig;
    }
    else if(channel->find("ee")!=string::npos && ((triggerBits & 0x40000))){
      int eetrig;
    }
    else if(channel->find("mumu")!=string::npos && ((triggerBits & 2))){
      int eetrig;
    }
    else{
      return kTRUE;
    }
  }

  int LeadLeptonNumber = 0;
  int NLeadLeptonNumber = 0;
  if(lepton_>1){
    if(channel->find("emu")!=string::npos){//quick and DIRTY!
      for(int i = 1; i<lepton_; i++){
	if(((*lepQ)[0]!=(*lepQ)[i]) && ((*lepType)[0]!=(*lepType)[i])){
	  LeadLeptonNumber = 0;
	  NLeadLeptonNumber = i;
	  break;
	}
      }//set dimass to first two highest pT oppositely charged leptons
    }
    if(channel->find("ee")!=string::npos){//quick and DIRTY!
      for(int i = 0; i<lepton_; i++){
	if((*lepType)[i]<0){
	  LeadLeptonNumber=i;	  
	  break;
	}
      }
      for(int i = LeadLeptonNumber+1; i<lepton_; i++){
	if(((*lepQ)[LeadLeptonNumber]!=(*lepQ)[i]) && (*lepType)[i]<0){
	  NLeadLeptonNumber = i;
	  break;
	}
      }//set dimass to first two highest pT oppositely charged leptons
    }
    if(channel->find("mumu")!=string::npos){//quick and DIRTY!
      for(int i = 0; i<lepton_; i++){
	if((*lepType)[i]>0){
	  LeadLeptonNumber=i;	  
	  break;
	}
      }
      for(int i = LeadLeptonNumber+1; i<lepton_; i++){
	if(((*lepQ)[LeadLeptonNumber]!=(*lepQ)[i]) && (*lepType)[i]>0){
	  NLeadLeptonNumber = i;
	  break;
	}
      }//set dimass to first two highest pT oppositely charged leptons
    }
    dimass = (LVlepton[LeadLeptonNumber]+LVlepton[NLeadLeptonNumber]).M();
    h_vertMulti->Fill(vertMulti,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
  }
  
 

  //Cross-section Plots
  if(lepton_>1 && dimass>12 && jet_>1 && BJetIndex.size()>0 && HypTop_){
    if(channel->find("emu")!=string::npos){//quick and DIRTY!
      h_jetMultiXSec->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSF*trigEFF*weightKinFit);
      h_jetMultiNoPU->Fill(jet_,weightLepSF*btagSF*trigEFF*weightKinFit);
    }else{
      if(*(metEt->begin()) > 30 && (dimass < 76 || dimass >106)){
	h_jetMultiXSec->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSF*trigEFF*weightKinFit);
	h_jetMultiNoPU->Fill(jet_,weightLepSF*btagSF*trigEFF*weightKinFit);
      }  
    }
  }
  //Control plots
  
  if(lepton_>1){  //two isolated leptons create dimass out of highest pt pair
    if(dimass>12.0 && NLeadLeptonNumber!=0){
      h_diLepMassFull->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
      if(channel->find("emu")!=string::npos){//quick and DIRTY!
	if(dimass>12.0 && jet_>1){
	  h_BjetMulti->Fill(BJetIndex.size(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_jetMulti->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  double jetHT = 0;
	  for(int i=0; i<jet_;i++){	    
	    jetHT+=LVjet[i].Pt();
	  }
	  h_jetHT->Fill(jetHT,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  for(int i=0; i<2;i++){
	    h_jetpT->Fill(LVjet[i].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  
	  if((*lepQ)[LeadLeptonNumber]==1){
	    h_LeptonpT->Fill(LVlepton[NLeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonpT->Fill(LVlepton[LeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_LeptonEta->Fill(LVlepton[NLeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonEta->Fill(LVlepton[LeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }else{
	    h_LeptonpT->Fill(LVlepton[LeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonpT->Fill(LVlepton[NLeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_LeptonEta->Fill(LVlepton[LeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonEta->Fill(LVlepton[NLeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }	
	  h_MET->Fill(*(metEt->begin()),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  if((*lepType)[LeadLeptonNumber]==-1){
	    h_ElectronpT->Fill(LVlepton[LeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_ElectronEta->Fill(LVlepton[LeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  if((*lepType)[NLeadLeptonNumber]==-1){
	    h_ElectronpT->Fill(LVlepton[NLeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_ElectronEta->Fill(LVlepton[NLeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  if((*lepType)[LeadLeptonNumber]==1){
	    h_MuonpT->Fill(LVlepton[LeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_MuonEta->Fill(LVlepton[LeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  if((*lepType)[NLeadLeptonNumber]==1){
	    h_MuonpT->Fill(LVlepton[NLeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_MuonEta->Fill(LVlepton[NLeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	}
      }else{
	if (dimass> 12.0 && (dimass<76.0 || dimass > 106.0) && jet_>1 && *(metEt->begin()) > 30){
	  h_BjetMulti->Fill(BJetIndex.size(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_jetMulti->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  double jetHT = 0;
	  for(int i=0; i<jet_;i++){	    
	    jetHT+=LVjet[i].Pt();
	  }
	  h_jetHT->Fill(jetHT,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  for(int i=0; i<2;i++){
	    h_jetpT->Fill(LVjet[i].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  if((*lepQ)[LeadLeptonNumber]==1){
	    h_LeptonpT->Fill(LVlepton[NLeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonpT->Fill(LVlepton[LeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_LeptonEta->Fill(LVlepton[NLeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonEta->Fill(LVlepton[LeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  else{
	    h_LeptonpT->Fill(LVlepton[LeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonpT->Fill(LVlepton[NLeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_LeptonEta->Fill(LVlepton[LeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonEta->Fill(LVlepton[NLeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }	
	  h_MET->Fill(*(metEt->begin()),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  if(*(metEt->begin()) > 30){
	    if((*lepType)[LeadLeptonNumber]==-1){
	      h_ElectronpT->Fill(LVlepton[LeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_ElectronEta->Fill(LVlepton[LeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    }
	    if((*lepType)[NLeadLeptonNumber]==-1){
	      h_ElectronpT->Fill(LVlepton[NLeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_ElectronEta->Fill(LVlepton[NLeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    }
	    if((*lepType)[LeadLeptonNumber]==1){
	      h_MuonpT->Fill(LVlepton[LeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_MuonEta->Fill(LVlepton[LeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    }
	    if((*lepType)[NLeadLeptonNumber]==1){
	      h_MuonpT->Fill(LVlepton[NLeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_MuonEta->Fill(LVlepton[NLeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    }
	  } 
	}
      }      
    } //
    if (dimass>76.0 && dimass < 106.0)Looseh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
    
    //if(dimass>12 && NLeadLeptonNumber>0){//Analysis step 6
    //if(dimass>12 && jet_>1 && NLeadLeptonNumber>0){//Analysis step 7
    //if(dimass>12 && jet_>1 && BJetIndex.size()>0 && NLeadLeptonNumber>0){btagSFuse=btagSF;//Analysis step 8?
    if(dimass>12.0 && jet_>1 && BJetIndex.size()>0 && HypTop_ && NLeadLeptonNumber>0){btagSFuse=btagSF; weightKinFituse=weightKinFit;//Analysis step 9?
      
      if(channel->find("emu")!=string::npos){//quick and DIRTY!
	Allh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	if (dimass < 106.0 && dimass > 76.0 ){
	  Zh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	}
	else{
	  TTh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	}
	
	
	if(MCSample->find("ttbarsignal")!=string::npos){
	  if (LVGenLepton.Pt()>20 && LVGenAntiLepton.Pt()>20 && abs(LVGenLepton.Eta())<2.4 && abs(LVGenAntiLepton.Eta())<2.4){
//Comment the next 2 lines and uncomment the 3rd one for gen-level Vis PS cuts
	    if (LVGenBQuark.Pt()>30 && LVGenAntiBQuark.Pt()>30 && abs(LVGenBQuark.Eta())<2.4 && abs(LVGenAntiBQuark.Eta())<2.4){
//       if (BHadIndex.size() >= 2 && LVGenJets[*(BHadIndex.begin())].Pt()>30 && LVGenJets[*(++BHadIndex.begin())].Pt()>30 &&
// 	  abs(LVGenJets[*(BHadIndex.begin())].Eta())<2.4 && abs(LVGenJets[*(++BHadIndex.begin())].Eta())<2.4){
//       if(BHadronIndex != -1 && LVGenJets[BHadronIndex].Pt()>30 && abs(LVGenJets[BHadronIndex].Eta())<2.4 &&
// 	AntiBHadronIndex != -1 && LVGenJets[AntiBHadronIndex].Pt()>30 && abs(LVGenJets[AntiBHadronIndex].Eta())<2.4 ){
//            if(LVBHadronGenJet.Pt()>30 && abs(LVBHadronGenJet.Eta())<2.4 &&
// 	    LVAntiBHadronGenJet.Pt()>30 && abs(LVAntiBHadronGenJet.Eta())<2.4){
	
	      h_jetMultiVisTop->Fill(jet_,weightLepSF*btagSF*trigEFF*weightKinFit); 
	    }
	  }//for visible top events
	  if(HypTop_){
	    h_GenRecoLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),LVGenLepton.Eta());
	    h_GenRecoAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),LVGenAntiLepton.Eta());
	    h_GenRecoLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),LVGenLepton.Pt());
	    h_GenRecoAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),LVGenAntiLepton.Pt());
	    
	    h_GenRecoTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),LVGenTop.Rapidity());
	    h_GenRecoAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),LVGenAntiTop.Rapidity());
	    h_GenRecoToppT->Fill(LVHypTop[solutionIndex].Pt(),LVGenTop.Pt());
	    h_GenRecoAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),LVGenAntiTop.Pt());
// 	    h_GenRecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),LVGenJets[BHadronIndex].Pt());
// 	    h_GenRecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),LVGenJets[AntiBHadronIndex].Pt());
	    h_GenRecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),LVBHadronGenJet.Pt());
	    h_GenRecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),LVAntiBHadronGenJet.Pt());
// 	    h_GenRecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),LVGenJets[*(BHadIndex.begin())].Pt());
// 	    h_GenRecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),LVGenJets[*(++BHadIndex.begin())].Pt());
// 	    h_GenRecoBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),LVGenJets[*(BHadIndex.begin())].Rapidity());
// 	    h_GenRecoAntiBJetRapidity->Fill(LVHypAntiBJet[solutionIndex].Rapidity(),LVGenJets[*(++BHadIndex.begin())].Rapidity());
// 	    h_GenRecoBJetEta->Fill(LVHypBJet[solutionIndex].Eta(),LVGenJets[*(BHadIndex.begin())].Eta());
// 	    h_GenRecoAntiBJetEta->Fill(LVHypAntiBJet[solutionIndex].Eta(),LVGenJets[*(++BHadIndex.begin())].Eta());
// 	    h_GenRecoBJetE->Fill(LVHypBJet[solutionIndex].E(),LVGenJets[*(BHadIndex.begin())].E());
// 	    h_GenRecoAntiBJetE->Fill(LVHypAntiBJet[solutionIndex].E(),LVGenJets[*(++BHadIndex.begin())].E());
// 	    
	    h_GenRecoLLBarMass->Fill((LVHypLepton[solutionIndex]+LVHypAntiLepton[solutionIndex]).M(),(LVGenLepton+LVGenAntiLepton).M());
	    h_GenRecoLLBarpT->Fill((LVHypLepton[solutionIndex]+LVHypAntiLepton[solutionIndex]).Pt(),(LVGenLepton+LVGenAntiLepton).Pt());

	    h_GenRecoTTBarMass->Fill((LVHypTop[solutionIndex]+LVHypAntiTop[solutionIndex]).M(),(LVGenTop+LVGenAntiTop).M());
	    h_GenRecoTTBarpT->Fill((LVHypTop[solutionIndex]+LVHypAntiTop[solutionIndex]).Pt(),(LVGenTop+LVGenAntiTop).Pt());
	    h_GenRecoTTBarRapidity->Fill((LVHypTop[solutionIndex]+LVHypAntiTop[solutionIndex]).Rapidity(),(LVGenTop+LVGenAntiTop).Rapidity());
	    
	  }//for purity stability calculations
	  double GenTTBarMass = (LVGenTop+ LVGenAntiTop).M();
	  h_GenTTBarMass->Fill(GenTTBarMass,1);
	  h_GenToppT->Fill(LVGenTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiToppT->Fill(LVGenAntiTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenLeptonpT->Fill(LVGenLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiLeptonpT->Fill(LVGenAntiLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenBQuarkpT->Fill(LVGenBQuark.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiBQuarkpT->Fill(LVGenAntiBQuark.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenBJetpT->Fill(LVBHadronGenJet.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiBJetpT->Fill(LVAntiBHadronGenJet.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
//        h_GenBJetpT->Fill(LVGenJets[BHadronIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
//        h_GenAntiBJetpT->Fill(LVGenJets[AntiBHadronIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenBJetpT->Fill(LVGenJets[*(BHadIndex.begin())].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenAntiBJetpT->Fill(LVGenJets[*(++BHadIndex.begin())].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  
	  h_GenTopEta->Fill(LVGenTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiTopEta->Fill(LVGenAntiTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenBQuarkEta->Fill(LVGenBQuark.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiBQuarkEta->Fill(LVGenAntiBQuark.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenLeptonEta->Fill(LVGenLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiLeptonEta->Fill(LVGenAntiLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenBJetEta->Fill(LVGenJets[*(BHadIndex.begin())].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenAntiBJetEta->Fill(LVGenJets[*(++BHadIndex.begin())].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

// 	  h_GenTopE->Fill(LVGenTop.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenAntiTopE->Fill(LVGenAntiTop.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenBQuarkE->Fill(LVGenBQuark.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenAntiBQuarkE->Fill(LVGenAntiBQuark.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenLeptonE->Fill(LVGenLepton.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenAntiLeptonE->Fill(LVGenAntiLepton.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenBJetE->Fill(LVGenJets[*(BHadIndex.begin())].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenAntiBJetE->Fill(LVGenJets[*(++BHadIndex.begin())].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  
// 	  h_GenBJetRapidity->Fill(LVGenJets[*(BHadIndex.begin())].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenAntiBJetRapidity->Fill(LVGenJets[*(++BHadIndex.begin())].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenBQuarkRapidity->Fill(LVGenBQuark.Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenAntiBQuarkRapidity->Fill(LVGenAntiBQuark.Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	
	  
	}
	if(HypTop_){
	  //h_jetMulti->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  //	  cout<<"SolutionIndex: "<<solutionIndex<<endl;
	  double HypTTBarMass = (LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).M();
	  h_RecoTTBarMass->Fill(HypTTBarMass,1);
	  h_RecoTTBarRapidity->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Rapidity(),1);
	  h_RecoTTBarpT->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Pt(),1);
	  h_RecoToppT->Fill(LVHypTop[solutionIndex].Pt(),1);
	  h_RecoAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),1);
	  h_RecoTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),1);
	  h_RecoAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),1);

	  h_RecoLLBarMass->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).M(),1);
	  h_RecoLLBarpT->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).Pt(),1);
	  h_RecoLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),1);
	  h_RecoAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),1);
	  h_RecoLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),1);
	  h_RecoAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),1);

	  h_RecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),1);
	  h_RecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),1);
	  h_RecoBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),1);
	  h_RecoAntiBJetRapidity->Fill(LVHypAntiBJet[solutionIndex].Rapidity(),1);

	  h_HypTTBarMass->Fill(HypTTBarMass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypTTBarRapidity->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypTTBarpT->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  h_HypLLBarMass->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypLLBarpT->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  h_HypTopMass->Fill(LVHypTop[solutionIndex].M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiTopMass->Fill(LVHypAntiTop[solutionIndex].M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypToppT->Fill(LVHypTop[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  h_HypBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiBJetRapidity->Fill(LVHypAntiBJet[solutionIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  h_HypTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  
	  h_HypTopEta->Fill(LVHypTop[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiTopEta->Fill(LVHypAntiTop[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypBJetEta->Fill(LVHypBJet[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiBJetEta->Fill(LVHypAntiBJet[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	     
// 	  h_HypTopE->Fill(LVHypTop[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_HypAntiTopE->Fill(LVHypAntiTop[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_HypBJetE->Fill(LVHypBJet[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_HypAntiBJetE->Fill(LVHypAntiBJet[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_HypLeptonE->Fill(LVHypLepton[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_HypAntiLeptonE->Fill(LVHypAntiLepton[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	}
      }else if(*(metEt->begin()) > 30){
	
	Allh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	if (dimass < 106.0 && dimass > 76.0 ){
	  Zh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	}
	else{
	  TTh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	}
	
	if(dimass<76.0 || dimass>106.0){ 
	  //h_jetMulti->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  //TTh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  if(MCSample->find("ttbarsignal")!=string::npos){
	    
	    if (LVGenLepton.Pt()>20 && LVGenAntiLepton.Pt()>20 && abs(LVGenLepton.Eta())<2.4 && abs(LVGenAntiLepton.Eta())<2.4){
//Comment the next 2 lines and uncomment the 3rd one for gen-level Vis PS cuts
	    if (LVGenBQuark.Pt()>30 && LVGenAntiBQuark.Pt()>30 && abs(LVGenBQuark.Eta())<2.4 && abs(LVGenAntiBQuark.Eta())<2.4){
//       if (BHadIndex.size() >= 2 && LVGenJets[*(BHadIndex.begin())].Pt()>30 && LVGenJets[*(++BHadIndex.begin())].Pt()>30 &&
// 	  abs(LVGenJets[*(BHadIndex.begin())].Eta())<2.4 && abs(LVGenJets[*(++BHadIndex.begin())].Eta())<2.4){
//       if(BHadronIndex != -1 && LVGenJets[BHadronIndex].Pt()>30 && abs(LVGenJets[BHadronIndex].Eta())<2.4 &&
// 	AntiBHadronIndex != -1 && LVGenJets[AntiBHadronIndex].Pt()>30 && abs(LVGenJets[AntiBHadronIndex].Eta())<2.4 ){
//            if(LVBHadronGenJet.Pt()>30 && abs(LVBHadronGenJet.Eta())<2.4 &&
// 	    LVAntiBHadronGenJet.Pt()>30 && abs(LVAntiBHadronGenJet.Eta())<2.4){

		
		h_jetMultiVisTop->Fill(jet_,weightLepSF*btagSF*trigEFF*weightKinFit); 
	      }
	    }//for visible top events

	    if(HypTop_){
	      h_GenRecoLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),LVGenLepton.Eta());
	      h_GenRecoAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),LVGenAntiLepton.Eta());
	      h_GenRecoLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),LVGenLepton.Pt());
	      h_GenRecoAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),LVGenAntiLepton.Pt());
	    
	      h_GenRecoTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),LVGenTop.Rapidity());
	      h_GenRecoAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),LVGenAntiTop.Rapidity());
	      h_GenRecoToppT->Fill(LVHypTop[solutionIndex].Pt(),LVGenTop.Pt());
	      h_GenRecoAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),LVGenAntiTop.Pt());

//            h_GenRecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),LVGenJets[BHadronIndex].Pt());
//            h_GenRecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),LVGenJets[AntiBHadronIndex].Pt());
	      h_GenRecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),LVBHadronGenJet.Pt());
	      h_GenRecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),LVAntiBHadronGenJet.Pt());
// 	      h_GenRecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),LVGenJets[*(BHadIndex.begin())].Pt());
// 	      h_GenRecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),LVGenJets[*(++BHadIndex.begin())].Pt());
// 	      h_GenRecoBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),LVGenJets[*(BHadIndex.begin())].Rapidity());
// 	      h_GenRecoAntiBJetRapidity->Fill(LVHypAntiBJet[solutionIndex].Rapidity(),LVGenJets[*(++BHadIndex.begin())].Rapidity());
// 	      h_GenRecoBJetEta->Fill(LVHypBJet[solutionIndex].Eta(),LVGenJets[*(BHadIndex.begin())].Eta());
// 	      h_GenRecoAntiBJetEta->Fill(LVHypAntiBJet[solutionIndex].Eta(),LVGenJets[*(++BHadIndex.begin())].Eta());
// 	      h_GenRecoBJetE->Fill(LVHypBJet[solutionIndex].E(),LVGenJets[*(BHadIndex.begin())].E());
// 	      h_GenRecoAntiBJetE->Fill(LVHypAntiBJet[solutionIndex].E(),LVGenJets[*(++BHadIndex.begin())].E());
	      
	      h_GenRecoLLBarMass->Fill((LVHypLepton[solutionIndex]+LVHypAntiLepton[solutionIndex]).M(),(LVGenLepton+LVGenAntiLepton).M());
	      h_GenRecoLLBarpT->Fill((LVHypLepton[solutionIndex]+LVHypAntiLepton[solutionIndex]).Pt(),(LVGenLepton+LVGenAntiLepton).Pt());

	      h_GenRecoTTBarMass->Fill((LVHypTop[solutionIndex]+LVHypAntiTop[solutionIndex]).M(),(LVGenTop+LVGenAntiTop).M());
	      h_GenRecoTTBarpT->Fill((LVHypTop[solutionIndex]+LVHypAntiTop[solutionIndex]).Pt(),(LVGenTop+LVGenAntiTop).Pt());
	      h_GenRecoTTBarRapidity->Fill((LVHypTop[solutionIndex]+LVHypAntiTop[solutionIndex]).Rapidity(),(LVGenTop+LVGenAntiTop).Rapidity());
	    
	    }//for purity stability calculations
	  
	    double GenTTBarMass = (LVGenTop+ LVGenAntiTop).M();
	    h_GenTTBarMass->Fill(GenTTBarMass,1);
	    h_GenToppT->Fill(LVGenTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenAntiToppT->Fill(LVGenAntiTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenLeptonpT->Fill(LVGenLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenAntiLeptonpT->Fill(LVGenAntiLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenBQuarkpT->Fill(LVGenBQuark.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenAntiBQuarkpT->Fill(LVGenAntiBQuark.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenBJetpT->Fill(LVBHadronGenJet.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenAntiBJetpT->Fill(LVAntiBHadronGenJet.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
//          h_GenBJetpT->Fill(LVGenJets[BHadronIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
//          h_GenAntiBJetpT->Fill(LVGenJets[AntiBHadronIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenBJetpT->Fill(LVGenJets[*(BHadIndex.begin())].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenAntiBJetpT->Fill(LVGenJets[*(++BHadIndex.begin())].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	    h_GenTopEta->Fill(LVGenTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenAntiTopEta->Fill(LVGenAntiTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenBQuarkEta->Fill(LVGenBQuark.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenAntiBQuarkEta->Fill(LVGenAntiBQuark.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenLeptonEta->Fill(LVGenLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenAntiLeptonEta->Fill(LVGenAntiLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenBJetEta->Fill(LVGenJets[*(BHadIndex.begin())].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenAntiBJetEta->Fill(LVGenJets[*(++BHadIndex.begin())].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    
// 	    h_GenTopE->Fill(LVGenTop.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenAntiTopE->Fill(LVGenAntiTop.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenBQuarkE->Fill(LVGenBQuark.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenAntiBQuarkE->Fill(LVGenAntiBQuark.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenLeptonE->Fill(LVGenLepton.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenAntiLeptonE->Fill(LVGenAntiLepton.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenBJetE->Fill(LVGenJets[*(BHadIndex.begin())].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenAntiBJetE->Fill(LVGenJets[*(++BHadIndex.begin())].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    
//     	    h_GenBJetRapidity->Fill(LVGenJets[*(BHadIndex.begin())].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenAntiBJetRapidity->Fill(LVGenJets[*(++BHadIndex.begin())].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenBQuarkRapidity->Fill(LVGenBQuark.Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenAntiBQuarkRapidity->Fill(LVGenAntiBQuark.Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    
	  }
	   
	  if(HypTop_){
	    //	  cout<<"SolutionIndex: "<<solutionIndex<<endl;
	    double HypTTBarMass = (LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).M();
	    h_RecoTTBarMass->Fill(HypTTBarMass,1);
	    h_RecoTTBarRapidity->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Rapidity(),1);
	    h_RecoTTBarpT->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Pt(),1);
	    h_RecoToppT->Fill(LVHypTop[solutionIndex].Pt(),1);
	    h_RecoAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),1);
	    h_RecoTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),1);
	    h_RecoAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),1);

	    h_RecoLLBarMass->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).M(),1);
	    h_RecoLLBarpT->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).Pt(),1);
	    h_RecoLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),1);
	    h_RecoAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),1);
	    h_RecoLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),1);
	    h_RecoAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),1);

	    h_RecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),1);
	    h_RecoAntiBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),1);
	    h_RecoBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),1);
	    h_RecoAntiBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),1);

	    h_HypLLBarMass->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypLLBarpT->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	    h_HypTTBarMass->Fill(HypTTBarMass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypTTBarRapidity->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypTTBarpT->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	    h_HypTopMass->Fill(LVHypTop[solutionIndex].M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypAntiTopMass->Fill(LVHypAntiTop[solutionIndex].M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypToppT->Fill(LVHypTop[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	    h_HypBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypAntiBJetRapidity->Fill(LVHypAntiBJet[solutionIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	    h_HypTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  
	    h_HypTopEta->Fill(LVHypTop[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypAntiTopEta->Fill(LVHypAntiTop[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypBJetEta->Fill(LVHypBJet[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypAntiBJetEta->Fill(LVHypAntiBJet[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	     
// 	    h_HypTopE->Fill(LVHypTop[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_HypAntiTopE->Fill(LVHypAntiTop[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_HypBJetE->Fill(LVHypBJet[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_HypAntiBJetE->Fill(LVHypAntiBJet[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_HypLeptonE->Fill(LVHypLepton[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_HypAntiLeptonE->Fill(LVHypAntiLepton[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	}
      }
    }      
  }

  return kTRUE;
}


void Analysis::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void Analysis::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  if(viaTau=="viaTau"){
    MCSample->clear();
    MCSample->append("ttbarbgviatau");
  }

  string f_savename = "selectionRoot/";
  gSystem->MakeDirectory(f_savename.c_str());
  f_savename.append(systematic); 
  gSystem->MakeDirectory(f_savename.c_str());
  f_savename.append("/");
  f_savename.append(*channel); 
  gSystem->MakeDirectory(f_savename.c_str());
  f_savename.append("/");
  f_savename.append(*MCSample);
  f_savename.append(".root");
  

  std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!Finishing: "<<*MCSample<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;

  TFile *f = new TFile(f_savename.c_str(),"RECREATE");

  //AllDIM.write();
  //InDIM.writeone();
  //OutDIM.writeone();

  h_GenRecoLeptonEta->Write();
  h_GenRecoAntiLeptonEta->Write();
  h_GenRecoLeptonpT->Write();
  h_GenRecoAntiLeptonpT->Write();

  h_GenRecoBJetpT->Write();
  h_GenRecoAntiBJetpT->Write();
  h_GenRecoBJetRapidity->Write();
  h_GenRecoAntiBJetRapidity->Write();
  h_GenRecoBJetEta->Write();
  h_GenRecoAntiBJetEta->Write();
//   h_GenRecoBJetE->Write();
//   h_GenRecoAntiBJetE->Write();
  
  h_GenRecoTopRapidity->Write();
  h_GenRecoAntiTopRapidity->Write();
  h_GenRecoToppT->Write();
  h_GenRecoAntiToppT->Write();

  h_GenRecoLLBarpT->Write();
  h_GenRecoLLBarMass->Write();
  h_GenRecoTTBarpT->Write();
  h_GenRecoTTBarMass->Write();
  h_GenRecoTTBarRapidity->Write();

  h_NJetMatching->Write();
  h_diLepMassFull->Write();
  Allh1->Write();
  Looseh1->Write();
  h_GenAll->Write();
  h_VisGenAll->Write();
  h_vertMulti->Write();
  h_jetMulti->Write();
  h_BjetMulti->Write();
  h_jetMultiXSec->Write();
  h_jetMultiNoPU->Write();
  Zh1->Write();
  TTh1->Write();

  h_HypTTBarpT->Write();
  h_HypTTBarRapidity->Write();
  h_HypTTBarMass->Write();
  h_HypLLBarpT->Write();
  h_HypLLBarMass->Write();

  h_GenTTBarMass->Write();
  h_GenTTBarRapidity->Write();
  h_GenTTBarpT->Write();
  h_GenLLBarpT->Write();
  h_GenLLBarMass->Write();

  h_VisGenTTBarMass->Write();
  h_VisGenTTBarRapidity->Write();
  h_VisGenTTBarpT->Write();
  h_VisGenLLBarpT->Write();
  h_VisGenLLBarMass->Write();

  h_RecoTTBarMass->Write();
  h_RecoTTBarRapidity->Write();
  h_RecoTTBarpT->Write();
  h_RecoToppT->Write();
  h_RecoAntiToppT->Write();
  h_RecoTopRapidity->Write();
  h_RecoAntiTopRapidity->Write();

  h_RecoLLBarMass->Write();
  h_RecoLLBarpT->Write();
  h_RecoLeptonpT->Write();
  h_RecoAntiLeptonpT->Write();
  h_RecoLeptonEta->Write();
  h_RecoAntiLeptonEta->Write();

  h_RecoBJetpT->Write();
  h_RecoAntiBJetpT->Write();
  h_RecoBJetRapidity->Write();
  h_RecoAntiBJetRapidity->Write();

  h_jetpT->Write();
  h_jetHT->Write();
  h_MET->Write();
  h_LeptonpT->Write();
  h_LeptonEta->Write();
  h_AntiLeptonpT->Write();
  h_AntiLeptonEta->Write();
  h_ElectronpT->Write();
  h_ElectronEta->Write();
  h_MuonpT->Write();
  h_MuonEta->Write();

  h_VisGenBJetpT->Write();
  h_VisGenAntiBJetpT->Write();
  h_VisGenBJetRapidity->Write();
  h_VisGenAntiBJetRapidity->Write();
  h_VisGenBJetEta->Write();
  h_VisGenAntiBJetEta->Write();

  h_VisGenBQuarkpT->Write();
  h_VisGenAntiBQuarkpT->Write();
  h_VisGenBQuarkRapidity->Write();
  h_VisGenAntiBQuarkRapidity->Write();
  h_VisGenBQuarkEta->Write();
  h_VisGenAntiBQuarkEta->Write();
  
  h_VisGenLeptonpT->Write();
  h_VisGenAntiLeptonpT->Write();
  h_VisGenLeptonEta->Write();
  h_VisGenAntiLeptonEta->Write();

  h_VisGenToppT->Write();
  h_VisGenAntiToppT->Write();
  h_VisGenTopEta->Write();
  h_VisGenAntiTopEta->Write();
  h_VisGenTopRapidity->Write();
  h_VisGenAntiTopRapidity->Write();

  h_GenBJetpT->Write();
  h_GenAntiBJetpT->Write();
  h_GenBJetRapidity->Write();
  h_GenAntiBJetRapidity->Write();
  h_GenBJetEta->Write();
  h_GenAntiBJetEta->Write();

  h_GenLeptonpT->Write();
  h_GenAntiLeptonpT->Write();
  h_GenLeptonEta->Write();
  h_GenAntiLeptonEta->Write();

  h_GenToppT->Write();
  h_GenAntiToppT->Write();
  h_GenTopEta->Write();
  h_GenAntiTopEta->Write();
  h_GenTopRapidity->Write();
  h_GenAntiTopRapidity->Write();

  h_GenBQuarkpT->Write();
  h_GenAntiBQuarkpT->Write();
  h_GenBQuarkRapidity->Write();
  h_GenAntiBQuarkRapidity->Write();
  h_GenBQuarkEta->Write();
  h_GenAntiBQuarkEta->Write();
  
  h_HypBJetpT->Write();
  h_HypAntiBJetpT->Write();
  h_HypBJetRapidity->Write();
  h_HypAntiBJetRapidity->Write();
  h_HypBJetEta->Write();
  h_HypAntiBJetEta->Write();

  h_HypLeptonpT->Write();
  h_HypAntiLeptonpT->Write();
  h_HypLeptonEta->Write();
  h_HypAntiLeptonEta->Write();

  h_HypTopRapidity->Write();
  h_HypAntiTopRapidity->Write();

  h_HypTopMass->Write();
  h_HypAntiTopMass->Write();
  h_HypToppT->Write();
  h_HypAntiToppT->Write();
  h_HypTopEta->Write();
  h_HypAntiTopEta->Write();

  
  f->Close();
  cout<<"Created: "<<f_savename<<endl;
}
