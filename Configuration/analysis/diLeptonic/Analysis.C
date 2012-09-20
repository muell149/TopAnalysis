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

  h_step5 = new TH1D("step5", "event count at step 5",10,0,10);
  h_step6 = new TH1D("step6", "event count at step 6",10,0,10);
  h_step7 = new TH1D("step7", "event count at step 7",10,0,10);
  h_step8 = new TH1D("step8", "event count at step 8",10,0,10);
  h_step9 = new TH1D("step9", "event count at step 9",10,0,10);

  h_jetMultiAll = new TH1D("HypjetMultiAll", "Jet Multiplicity (AllJets)", 10, -0.5, 9.5);
  h_jetMultiXSec = new TH1D("HypjetMultiXSec", "Jet Multiplicity (for cross-section)", 10, -0.5, 9.5);
  h_jetMulti = new TH1D("HypjetMulti", "Jet Multiplicity", 10, -0.5, 9.5);
  h_jetMulti_diLep = new TH1D("HypjetMulti_diLep", "Jet Multiplicity (after dilepton)", 10, -0.5, 9.5);
  h_jetMultiNoPU = new TH1D("HypjetMultiNoPU", "Jet Multiplicity (No Pileup or lumi weight)", 10, -0.5, 9.5);
  h_jetMultiVisTop = new TH1D("HypjetMultiVisTop", "Jet Multiplicity for Visible Top (No Pileup or lumi Weight)", 10, -0.5, 9.5);
  h_BjetMulti = new TH1D("HypBjetMulti", "B-Jet Multiplicity", 10, -0.5, 9.5);
  
  h_HypTTBarRapidity = new TH1D("HypTTBarRapidity","Rapidity of TTbar System (HYP)",100,-5,5);
  h_HypTTBarpT = new TH1D("HypTTBarpT","pT of TTbar System (HYP)",500,0,500);
  h_HypTTBarMass = new TH1D("HypTTBarMass","Mass of TTbar System (HYP)",2000,0,2000);
  h_HypLLBarMass = new TH1D("HypLLBarMass","Mass of LLbar System (HYP)",500,0,1000);
  h_HypLLBarpT = new TH1D("HypLLBarpT","pT of LLbar System (HYP)",200,0,1000);

  h_GenTTBarMass = new TH1D("GenTTBarMass","Mass of TTbar System(GEN)",1200,0,1200);
  h_GenTTBarRapidity = new TH1D("GenTTBarRapidity","Rapidity of TTbar System(GEN)",100,-5,5);
  h_GenTTBarpT = new TH1D("GenTTBarpT","pT of TTbar System(GEN)",1200,0,1200);
  h_GenLLBarpT = new TH1D("GenLLBarpT","pT of LLbar System(GEN)",200,0,1000);
  h_GenLLBarMass = new TH1D("GenLLBarMass","Mass of LLbar System(GEN)",500,0,1000);

  h_VisGenTTBarMass = new TH1D("VisGenTTBarMass","Mass of TTbar System(VisGEN)",1200,0,1200);
  h_VisGenTTBarRapidity = new TH1D("VisGenTTBarRapidity","Rapidity of TTbar System(VisGEN)",100,-5,5);
  h_VisGenTTBarpT = new TH1D("VisGenTTBarpT","pT of TTbar System(VisGEN)",1200,0,1200);
  h_VisGenTopRapidity = new TH1D("VisGenTopRapidity","Rapidity of Top(VisGEN)",100,-5,5);
  h_VisGenAntiTopRapidity = new TH1D("VisGenAntiTopRapidity","Rapidity of AntiTop(VisGEN)",100,-5,5);

  h_VisGenLLBarpT = new TH1D("VisGenLLBarpT","pT of LLbar System(VisGEN)",200,0,1000);
  h_VisGenLLBarMass = new TH1D("VisGenLLBarMass","Mass of LLbar System(VisGEN)",500,0,1000);

  h_RecoTTBarMass = new TH1D("RecoTTBarMass","Mass of TTbar System (HYP)",1200,0,1200);
  h_RecoTTBarRapidity = new TH1D("RecoTTBarRapidity","Rapidity of TTbar System (HYP)",100,-5,5);
  h_RecoTTBarpT = new TH1D("RecoTTBarpT","pT of TTbar System (HYP)",1200,0,1200);
  h_RecoToppT = new TH1D("RecoToppT","pT of Top (HYP)",1200,0,1200);
  h_RecoAntiToppT = new TH1D("RecoAntiToppT","pT of AntiTop (HYP)",1200,0,1200);
  h_RecoTopRapidity = new TH1D("RecoTopRapidity","Rapidity of Top (HYP)",100,-5,5);
  h_RecoAntiTopRapidity = new TH1D("RecoAntiTopRapidity","Rapidity of AntiTop (HYP)",100,-5,5);

  h_RecoBJetpT = new TH1D("RecoBJetpT","pT of BJet (HYP)",80,0,400);
  h_RecoAntiBJetpT = new TH1D("RecoAntiBJetpT","pT of AntiBJet (HYP)",80,0,400);
  h_RecoBJetRapidity = new TH1D("RecoBJetRapidity","Rapidity of BJet (HYP)",100,-5,5);
  h_RecoAntiBJetRapidity = new TH1D("RecoAntiBJetRapidity","Rapidity of AntiBJet (HYP)",100,-5,5);
  h_RecoBJetEta = new TH1D("RecoBJetEta","#eta of BJet (HYP)",100,-5,5);
  h_RecoAntiBJetEta = new TH1D("RecoAntiBJetEta","#eta of AntiBJet (HYP)",100,-5,5);

  h_RecoLLBarMass = new TH1D("RecoLLBarMass","Mass of LLbar System (HYP)",500,0,1000);
  h_RecoLLBarpT = new TH1D("RecoLLBarpT","pT of LLbar System (HYP)",200,0,1000);
  h_RecoLeptonpT = new TH1D("RecoLeptonpT","pT of Lepton (HYP)",240,0,1200);
  h_RecoAntiLeptonpT = new TH1D("RecoAntiLeptonpT","pT of AntiLepton (HYP)",240,0,1200);
  h_RecoLeptonEta = new TH1D("RecoLeptonEta","Eta of Lepton (HYP)",100,-5,5);
  h_RecoAntiLeptonEta = new TH1D("RecoAntiLeptonEta","Eta of AntiLepton (HYP)",100,-5,5);

  h_VisGenAll = new TH1D("VisGenAll","All Visible Generated particles (IM)",40,0,400);
  h_GenAll = new TH1D("GenAll","AllGenerated particles (IM)",40,0,400);
  Allh1 = new TH1D("Allh1","DiLepton Mass",40,0,400);
  h_diLepMassFull = new TH1D("DIMFull","DiLepton Mass (Full Range)",100,0,300);
  h_diLepMassFull_fullSel = new TH1D("DIMFull_fullSel","DiLepton Mass (Full Range)",100,0,300);
  Looseh1 = new TH1D("Looseh1","DiLepton Mass",40,0,400);
  Zh1 = new TH1D("Zh1","DiLepton Mass in Z Window",40,0,400);
  TTh1 = new TH1D("TTh1","DiLepton Mass out of Z Window",40,0,400);

  h_vertMulti = new TH1D("vertMulti", "Primary Vertex Multiplicity", 30, 0, 30);
  h_vertMulti_noPU = new TH1D("vertMulti_noPU", "Primary Vertex Multiplicity (no Pileup)", 30, 0, 30);
  h_MET = new TH1D("MET", "Missing Transverse Energy", 80, 0, 400);
  h_jetpT = new TH1D("jetpT", "jet pT", 80, 0, 400);  
  h_jetHT = new TH1D("jetHT", "jet HT", 80, 0, 1000);  

  h_MuonpT = new TH1D("MuonpT","Muon pT (emu channel)",80,0,400);
  h_MuonEta = new TH1D("MuonEta","Muon Eta (emu channel)",100,-5,5);
  h_ElectronpT = new TH1D("ElectronpT","Electron pT (emu channel)",80,0,400);
  h_ElectronEta = new TH1D("ElectronEta","Electron Eta (emu channel)",100,-5,5);

  h_LeptonpT = new TH1D("LeptonpT","Lepton pT",80,0,400);
  h_LeptonEta = new TH1D("LeptonEta","Lepton Eta",100,-5,5);
  h_LeptonpT_diLep = new TH1D("LeptonpT_diLep","Lepton pT (after dilepton cut)",80,0,400);
  h_LeptonEta_diLep = new TH1D("LeptonEta_diLep","Lepton Eta (after dilepton cut)",100,-5,5);

  h_AntiLeptonpT = new TH1D("AntiLeptonpT","AntiLepton pT",80,0,400);
  h_AntiLeptonEta = new TH1D("AntiLeptonEta","AntiLepton Eta",100,-5,5);
  h_AntiLeptonpT_diLep = new TH1D("AntiLeptonpT_diLep","Lepton pT (after dilepton cut)",80,0,400);
  h_AntiLeptonEta_diLep = new TH1D("AntiLeptonEta_diLep","Lepton Eta (after dilepton cut)",100,-5,5);

  h_HypToppT = new TH1D("HypToppT","Top pT",400,0,400);
  h_HypTopEta = new TH1D("HypTopEta","Top pT",100,-5,5);
  h_HypTopMass = new TH1D("HypTopMass","Top Mass",80,0,400);
  h_HypTopRapidity = new TH1D("HypTopRapidity","Top Rapidity",100,-5,5);

  h_HypAntiToppT = new TH1D("HypAntiToppT","AntiTop pT",400,0,400);
  h_HypAntiTopEta = new TH1D("HypAntiTopEta","AntiTop pT",100,-5,5);
  h_HypAntiTopMass = new TH1D("HypAntiTopMass","AntiTop Mass",80,0,400);
  h_HypAntiTopRapidity = new TH1D("HypAntiTopRapidity","Top Rapidity",100,-5,5);

  h_HypLeptonpT = new TH1D("HypLeptonpT","Lepton Hypothesis pT",80,0,400);
  h_HypLeptonEta = new TH1D("HypLeptonEta","Lepton Eta",100,-5,5);

  h_HypAntiLeptonpT = new TH1D("HypAntiLeptonpT","AntiLepton Hypothesis pT",80,0,400);
  h_HypAntiLeptonEta = new TH1D("HypAntiLeptonEta","AntiLepton Hypothesis Eta",100,-5,5);

  h_HypBJetpT = new TH1D("HypBJetpT","B Hypothesis pT",80,0,400);
  h_HypBJetEta = new TH1D("HypBJetEta","B Hypothesis Eta",100,-5,5);
  h_HypBJetRapidity = new TH1D("HypBJetRapidity","B Hypothesis Eta",100,-5,5);

  h_HypAntiBJetpT = new TH1D("HypAntiBJetpT","AntiB Hypothesis pT",80,0,400);
  h_HypAntiBJetEta = new TH1D("HypAntiBJetEta","AntiB Hypothesis Eta",100,-5,5);
  h_HypAntiBJetRapidity = new TH1D("HypAntiBJetRapidity","AntiB Hypothesis Eta",100,-5,5);

  h_VisGenToppT = new TH1D("VisGenToppT","Top pT (VisGen)",400,0,400);
  h_VisGenTopEta = new TH1D("VisGenTopEta","Top Eta (VisGen)",100,-5,5);

  h_VisGenAntiToppT = new TH1D("VisGenAntiToppT","AntiTop pT (VisGen)",400,0,400);
  h_VisGenAntiTopEta = new TH1D("VisGenAntiTopEta","AntiTop pT (VisGen)",100,-5,5);

  h_VisGenLeptonpT = new TH1D("VisGenLeptonpT","Lepton VisGenothesis pT",80,0,400);
  h_VisGenLeptonEta = new TH1D("VisGenLeptonEta","Lepton Eta",100,-5,5);

  h_VisGenAntiLeptonpT = new TH1D("VisGenAntiLeptonpT","AntiLepton VisGenothesis pT",80,0,400);
  h_VisGenAntiLeptonEta = new TH1D("VisGenAntiLeptonEta","AntiLepton VisGenothesis Eta",100,-5,5);

  h_VisGenBJetpT = new TH1D("VisGenBJetpT","B VisGenothesis pT",80,0,400);
  h_VisGenBJetEta = new TH1D("VisGenBJetEta","B VisGenothesis Eta",100,-5,5);
  h_VisGenBJetRapidity = new TH1D("VisGenBJetRapidity","B VisGenothesis Rapidity",100,-5,5);

  h_VisGenAntiBJetpT = new TH1D("VisGenAntiBJetpT","AntiB VisGenothesis pT",80,0,400);
  h_VisGenAntiBJetEta = new TH1D("VisGenAntiBJetEta","AntiB VisGenothesis Eta",100,-5,5);
  h_VisGenAntiBJetRapidity = new TH1D("VisGenAntiBJetRapidity","AntiB VisGenothesis Rapidity",100,-5,5);
  
  /*  h_VisGenBQuarkpT = new TH1D("VisGenBQuarkpT","B Quark VisGenothesis pT",80,0,400);
  h_VisGenBQuarkEta = new TH1D("VisGenBQuarkEta","B Quark VisGenothesis Eta",100,-5,5);
  h_VisGenBQuarkRapidity = new TH1D("VisGenBQuarkRapidity","B Quark VisGenothesis Rapidity",100,-5,5);

  h_VisGenAntiBQuarkpT = new TH1D("VisGenAntiBQuarkpT","AntiB Quark VisGenothesis pT",80,0,400);
  h_VisGenAntiBQuarkEta = new TH1D("VisGenAntiBQuarkEta","AntiB Quark VisGenothesis Eta",100,-5,5);
  h_VisGenAntiBQuarkRapidity = new TH1D("VisGenAntiBQuarkRapidity","AntiB Quark VisGenothesis Rapidity",100,-5,5);
  */
  /*h_GenToppT = new TH1D("GenToppT","Top pT (Gen)",80,0,400);
  h_GenTopEta = new TH1D("GenTopEta","Top Eta (Gen)",100,-5,5);
  h_GenTopRapidity = new TH1D("GenTopRapidity","Top Rapidity (Gen)",100,-5,5);
  
  h_GenAntiToppT = new TH1D("GenAntiToppT","AntiTop pT (Gen)",80,0,400);
  h_GenAntiTopEta = new TH1D("GenAntiTopEta","AntiTop Eta (Gen)",100,-5,5);
  h_GenAntiTopRapidity = new TH1D("GenAntiTopRapidity","AntiTop Rapidity (Gen)",100,-5,5);

  h_GenLeptonpT = new TH1D("GenLeptonpT","Lepton Genothesis pT",80,0,400);
  h_GenLeptonEta = new TH1D("GenLeptonEta","Lepton Eta",100,-5,5);

  h_GenAntiLeptonpT = new TH1D("GenAntiLeptonpT","AntiLepton Genothesis pT",80,0,400);
  h_GenAntiLeptonEta = new TH1D("GenAntiLeptonEta","AntiLepton Genothesis Eta",100,-5,5);

  h_GenBQuarkpT = new TH1D("GenBQuarkpT","B Quark Genothesis pT",80,0,400);
  h_GenBQuarkEta = new TH1D("GenBQuarkEta","B Quark Genothesis Eta",100,-5,5);
  h_GenBQuarkRapidity = new TH1D("GenBQuarkRapidity","B Quark Genothesis Rapidity",100,-5,5);

  h_GenAntiBQuarkpT = new TH1D("GenAntiBQuarkpT","AntiB Quark Genothesis pT",80,0,400);
  h_GenAntiBQuarkEta = new TH1D("GenAntiBQuarkEta","AntiB Quark Genothesis Eta",100,-5,5);
  h_GenAntiBQuarkRapidity = new TH1D("GenAntiBQuarkRapidity","AntiB Quark Genothesis Rapidity",100,-5,5);
  
  h_GenBJetpT = new TH1D("GenBJetpT","B Genothesis pT",80,0,400);
  h_GenBJetEta = new TH1D("GenBJetEta","B Genothesis Eta",100,-5,5);
  h_GenBJetRapidity = new TH1D("GenBJetRapidity","B Genothesis Rapidity",100,-5,5);

  h_GenAntiBJetpT = new TH1D("GenAntiBJetpT","AntiB Genothesis pT",80,0,400);
  h_GenAntiBJetEta = new TH1D("GenAntiBJetEta","AntiB Genothesis Eta",100,-5,5);
  h_GenAntiBJetRapidity = new TH1D("GenAntiBJetRapidity","Anti B Genothesis Rapidity",100,-5,5);
  */
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
  h_GenRecoToppT = new TH2D("GenRecoToppT", "Gen/Reco Matching", 400,0,400,400,0,400);
  h_GenRecoAntiToppT = new TH2D("GenRecoAntiToppT", "Gen/Reco Matching", 400,0,400,400,0,400);

  h_GenRecoTTBarRapidity = new TH2D("GenRecoTTBarRapidity","Rapidity of TTbar System (HYP)",100,-5,5,100,-5,5);
  h_GenRecoTTBarpT = new TH2D("GenRecoTTBarpT","pT of TTbar System (HYP)",500,0,500,500,0,500);
  h_GenRecoTTBarMass = new TH2D("GenRecoTTBarMass","Mass of TTbar System (HYP)",2000,0,2000,2000,0,2000);
  h_GenRecoLLBarMass = new TH2D("GenRecoLLBarMass","Mass of LLbar System (HYP)",500,0,1000,500,0,1000);
  h_GenRecoLLBarpT = new TH2D("GenRecoLLBarpT","pT of LLbar System (HYP)",200,0,1000,200,0,1000);

  h_NJetMatching = new TH1D("NJetMatching", "NJet Gen/Reco Matching",5,0,5);

  h_GenRecoLLBarDPhi         = new TH2D("GenRecoLLBarDPhi",  "Gen/Reco Matching", 112, -0.1, 3.25, 112, -0.1, 3.25);
  h_GenRecoLeptonantiBjetMass= new TH2D("GenRecoLeptonantiBjetMass", "Gen/Reco Matching", 500, 0, 1000, 500, 0, 1000);
  h_GenRecoAntiLeptonBjetMass= new TH2D("GenRecoAntiLeptonBjetMass", "Gen/Reco Matching", 500, 0, 1000, 500, 0, 1000);
  h_GenRecoJetMult           = new TH2D("GenRecoJetMult",         "Gen/REco Matching", 26, -0.5, 25.5, 26, -0.5, 25.5);
  
  h_RecoLLBarDPhi	   = new TH1D("RecoLLBarDPhi",  "#Delta#phi(Lep, AntiLep) (HYP)", 112, -0.1, 3.25);
  h_RecoLeptonantiBjetMass = new TH1D("RecoLeptonantiBjetMass", "Mass(Lep, AntiBJet) (HYP)", 500, 0, 1000);
  h_RecoAntiLeptonBjetMass = new TH1D("RecoAntiLeptonBjetMass", "Mass(AntiLep, BJet) (HYP)", 500, 0, 1000);
  h_RecoJetMult		   = new TH1D("RecoJetMult",         "Jet Multiplicity (HYP)", 26, -0.5, 25.5);
  
  h_HypLLBarDPhi	  = new TH1D("HypLLBarDPhi",  "#Delta#phi(Lep, AntiLep) (HYP)", 111, -0.1, 3.2);
  h_HypLeptonantiBjetMass = new TH1D("HypLeptonantiBjetMass", "Mass(Lep, AntiBJet) (HYP)", 500, 0, 1000);
  h_HypAntiLeptonBjetMass = new TH1D("HypAntiLeptonBjetMass", "Mass(AntiLep, BJet) (HYP)", 500, 0, 1000);
  h_HypJetMult		  = new TH1D("HypJetMult",         "Jet Multiplicity (HYP)", 26, -0.5, 25.5);
  
  h_GenLLBarDPhi	  = new TH1D("GenLLBarDPhi",  "#Delta#phi(Lep, AntiLep) (GEN)", 111, -0.1, 3.2);
  h_GenLeptonantiBjetMass = new TH1D("GenLeptonantiBjetMass", "Mass(Lep, AntiBJet) (GEN)", 500, 0, 1000);
  h_GenAntiLeptonBjetMass = new TH1D("GenAntiLeptonBjetMass", "Mass(AntiLep, BJet) (GEN)", 500, 0, 1000);
  h_GenJetMult		  = new TH1D("GenJetMult",         "Jet Multiplicty (GEN)", 26, -0.5, 25.5);
  
  h_VisGenLLBarDPhi	    = new TH1D("VisGenLLBarDPhi",  "#Delta #Phi (Lep, AntiLep) (VisGEN)", 112, -0.1, 3.25);
  h_VisGenLeptonantiBjetMass= new TH1D("VisGenLeptonantiBjetMass", "M(Lep, AntiBJet) (VisGEN)", 500, 0, 1000);
  h_VisGenAntiLeptonBjetMass= new TH1D("VisGenAntiLeptonBjetMass", "M(AntiLep, BJet) (VisGEN)", 500, 0, 1000);
  h_VisGenJetMult	    = new TH1D("VisGenJetMult",         "Jet Multiplicty (VisGEN)", 26, -0.5, 25.5);
  
  h_HypLLBarpTDPhi = new TH2D ("HypLLBarpTDPhi", "DiLep: pT(ll) vs DPhi(ll)", 500,0,1000, 112, -0.1, 3.25);
  
  // BEGIN: BTag SF calculation neccessary stuff
  //Histograms to fill the per-event SF!!
  h_BTagSF = new TH1D("BTagSF", "BTagging SF per event", 100 , 0.95,1.05);      h_BTagSF->Sumw2();
  h_BTagEvtSF = new TH1D("BTagEvtSF", "Event's BTagging SF", 2.2e6, 0, 2.2e6);  h_BTagEvtSF->Sumw2();
  h_BTagSF_Pt_Up = new TH1D("BTagSFPtUp", "BTagging SF Pt Up variation per event", 100 , 0.95,1.05);      h_BTagSF_Pt_Up->Sumw2();
  h_BTagEvtSF_Pt_Up = new TH1D("BTagEvtSFPtUp", "Event's BTagging SF Pt Up variation", 2.2e6, 0, 2.2e6);  h_BTagEvtSF_Pt_Up->Sumw2();
  h_BTagSF_Pt_Down = new TH1D("BTagSFPtDown", "BTagging SF Pt Down variation per event", 100 , 0.95,1.05);      h_BTagSF_Pt_Down->Sumw2();
  h_BTagEvtSF_Pt_Down = new TH1D("BTagEvtSFPtDown", "Event's BTagging SF Pt Down variation", 2.2e6, 0, 2.2e6);  h_BTagEvtSF_Pt_Down->Sumw2();
  h_BTagSF_Eta_Up = new TH1D("BTagSFEtaUp", "BTagging SF Eta Up variation per event", 100 , 0.95,1.05);      h_BTagSF_Eta_Up->Sumw2();
  h_BTagEvtSF_Eta_Up = new TH1D("BTagEvtSFEtaUp", "Event's BTagging SF Eta Up variation", 2.2e6, 0, 2.2e6);  h_BTagEvtSF_Eta_Up->Sumw2();
  h_BTagSF_Eta_Down = new TH1D("BTagSFEtaDown", "BTagging SF Eta Down variation per event", 100 , 0.95,1.05);      h_BTagSF_Eta_Down->Sumw2();
  h_BTagEvtSF_Eta_Down = new TH1D("BTagEvtSFEtaDown", "Event's BTagging SF Eta Down variation", 2.2e6, 0, 2.2e6);  h_BTagEvtSF_Eta_Down->Sumw2();
  h_BTagSF_Up = new TH1D("BTagSFUp", "BTagging SF Up variation per event", 100 , 0.95,1.05);      h_BTagSF_Up->Sumw2();
  h_BTagEvtSF_Up = new TH1D("BTagEvtSFUp", "Event's BTagging SF Up variation", 2.2e6, 0, 2.2e6);  h_BTagEvtSF_Up->Sumw2();
  h_BTagSF_Down = new TH1D("BTagSFDown", "BTagging SF Down variation per event", 100 , 0.95,1.05);      h_BTagSF_Down->Sumw2();
  h_BTagEvtSF_Down = new TH1D("BTagEvtSFDown", "Event's BTagging Pt Down variation", 2.2e6, 0, 2.2e6);  h_BTagEvtSF_Down->Sumw2();

  //pt efficiency median value can be obtained running and reading the output of: root -l -b -q CalcMedian.C
  //By now defined the per-jet SFs vary according to:
  //   BTag_Up   ==> pt>ptmedian vary DOWN, pt<ptmedian vary UP
  //   BTag_Down ==> pt>ptmedian vary UP, pt<ptmedian vary DOWN
  ptmedian=65.;
  etamedian=0.75;
  
  //load per-jet efficienciies file and Histograms
  TFile *bEfficiencies;
  if(option!=""){bEfficiencies=TFile::Open(option);}
  else {cout<<"WARNING!!! Provide 'channel' option to the file for running"<<endl; return;}
  
  if (bEfficiencies->IsZombie()) {cout<<"File "<<bEfficiencies->GetName()<<" is zombie. Check that!!!"<<endl; return;}
  bEff = (TH2D*) bEfficiencies->Get("BEffPerJet"); if (bEff->IsZombie()){cout<<"Histogram bEff is not in the file "<<bEfficiencies->GetName();return;}
  cEff = (TH2D*) bEfficiencies->Get("CEffPerJet"); if (cEff->IsZombie()){cout<<"Histogram cEff is not in the file "<<bEfficiencies->GetName();return;}
  lEff = (TH2D*) bEfficiencies->Get("LEffPerJet"); if (lEff->IsZombie()){cout<<"Histogram lEff is not in the file "<<bEfficiencies->GetName();return;}
  
  for(int i=1; i<=(1+(int)bEff->GetXaxis()->GetNbins()); ++i){ptbinning.push_back(bEff->GetXaxis()->GetBinLowEdge(i));}
  for(int i=1; i<=(1+(int)bEff->GetYaxis()->GetNbins()); ++i){etabinning.push_back(bEff->GetYaxis()->GetBinLowEdge(i));}
  
  //load the histograms in memory, to avoid memory leaks
  bEff->SetDirectory(0);  cEff->SetDirectory(0);  lEff->SetDirectory(0);
  bEfficiencies->Close();   bEfficiencies->Delete();
  // END: BTag SF calculation neccessary stuff
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

  //We must correct for the madGraph branching fraction beins 1/9 for dileptons (PDG average is .108)
  if((MCSample->find("ttbarsignal")!=string::npos) ||(MCSample->find("ttbarbg")!=string::npos)){
    if(decayMode==11){//all hadronic decay
      lumiWeight=lumiWeight*(0.676*1.5)*(0.676*1.5);
    } else if(decayMode<20 || (decayMode%10==1)){//semileptonic Decay
      lumiWeight=lumiWeight*(0.108*9.)*(0.676*1.5);
    } else {//dileptonic decay (including taus!)
      lumiWeight=lumiWeight*(0.108*9.)*(0.108*9.);
    }
  }

  if(MCSample->find("ttbarsignal")!=string::npos){ Analysis::GetSignalBranches(entry);}
  if(MCSample->find("run")!=string::npos){ weightLepSF = 1.0;}
  EventCounter++;
  if(EventCounter % 100000 == 0){cout<<"Event Counter: "<<EventCounter<<endl;}
  float dimass=0.;
  double btagSFuse=1.0;//only use the btag SF when applying b-tagging
  double weightKinFituse = 1.0;//only use the kin fit SF when using the kinematic reconstruction
  double trigEFF = 1.0;//set trigger efficiency scale factor to 1. 
  if(systematic=="PU_UP"){weightPU = weightPU_Up;}//only for PU systematic run
  if(systematic=="PU_DOWN"){weightPU = weightPU_Down;}//only for PU systematic run
  if(systematic=="MCATNLO"){weightPU = weightPU*weightMCatNLO;}//only for PU systematic run
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

  
  int BHadronIndex=-1;
  int AntiBHadronIndex=-1;
  
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
    
    std::vector<int> idx_leadbHadJet;
    std::vector<int> idx_nleadbHadJet;
    //To avoid recopying may code lines, we select HERE the BHadron JET Indices to cut on.
  
    //    LVBHadronGenJet =  TLorentzVector(BHadronJetpX, BHadronJetpY, BHadronJetpZ, BHadronJetE);
    //LVAntiBHadronGenJet = TLorentzVector(AntiBHadronJetpX, AntiBHadronJetpY, AntiBHadronJetpZ, AntiBHadronJetE);
    
    
    
    for(int i=0; i<(int) BHadJetIndex->size(); i++){	BHadIndex.insert((*BHadJetIndex)[i]);	}
    
    for(int i=0; i<(int) AntiBHadJetIndex->size(); i++){	BHadIndex.insert((*AntiBHadJetIndex)[i]);	}
    
    
    //time to choose which genJet we actually want  
    
    idx_leadbHadJet.insert(idx_leadbHadJet.begin(), 4, -1);
    idx_nleadbHadJet.insert(idx_nleadbHadJet.begin(), 4, -1);
    /*
      idx_bHadJet will have 4 jet indices 
      [0] is the highest pT jet with a B-Hadron
      [1] is the highest pT jet with a B-Hadron also matched to a top quark
      [2] highest pT jet of those matched closest (in DeltaR) to the B-Hadron
      [3] highest pT jet of those matched closest (in DeltaR) to the B-Hadron also matched to a top quark
    */
    
    bool LeadBHadhighpTjet = false;
    bool LeadBHadhighpTjetfromtop = false;
    bool NLeadBHadhighpTjet = false;
    bool NLeadBHadhighpTjetfromtop = false;

    bool LeadBHadhighDRjet = false;
    bool LeadBHadhighDRjetfromtop = false;
    bool NLeadBHadhighDRjet = false;
    bool NLeadBHadhighDRjetfromtop = false;

    int leadHadron = -1;
    int hadron_index = -1;
    int antihadron_index = -1;
    int hadrontop_index = -1;
    int antihadrontop_index = -1;
    //Case 1: highest pT genJet matched to a BHadron
    for(int genJet=0; genJet<allGenJets_; genJet++){
      if(LVGenJets[genJet].Pt()<30){break;}
      for(int bHadron=0; bHadron<BHadrons_; bHadron++){
	if((*BHadronVsJet)[genJet*BHadrons_+bHadron]==1 && (LeadBHadhighpTjet ==false || LeadBHadhighpTjetfromtop == false || NLeadBHadhighpTjet ==false || NLeadBHadhighpTjetfromtop == false)){
	  if(LeadBHadhighpTjet==false){	    
	    idx_leadbHadJet[0] = genJet;
	    LeadBHadhighpTjet = true;
	    hadron_index = bHadron;
	    if((*BHadronFromTopB)[bHadron] == true){
	      idx_leadbHadJet[1] = genJet;
	      LeadBHadhighpTjetfromtop = true;
	      hadrontop_index = bHadron;
	    }
	  }else if(LeadBHadhighpTjetfromtop == false){
	    if((*BHadronFromTopB)[bHadron] == true){
	      idx_leadbHadJet[1] = genJet;
	      LeadBHadhighpTjetfromtop = true;
	      hadrontop_index = bHadron;	      
	    }
	  }else if(NLeadBHadhighpTjet==false && bHadron!=hadron_index && idx_leadbHadJet[0] != genJet){
	    idx_nleadbHadJet[0] = genJet;
	    NLeadBHadhighpTjet = true;
	    if((*BHadronFromTopB)[bHadron] == true && bHadron!=hadrontop_index && idx_leadbHadJet[1] != genJet){
	      idx_nleadbHadJet[1] = genJet;
	      NLeadBHadhighpTjetfromtop = true;
	    }
	  }else if(NLeadBHadhighpTjetfromtop == false && bHadron!=hadrontop_index && idx_leadbHadJet[1] != genJet){
	    if((*BHadronFromTopB)[bHadron] == true){
	      idx_nleadbHadJet[1] = genJet;
	      LeadBHadhighpTjetfromtop = true;
	    }
	  }//series of if statements to find highest pT jet
	}      
      }
      for(int antibHadron=0; antibHadron<AntiBHadrons_; antibHadron++){
	if((*AntiBHadronVsJet)[genJet*AntiBHadrons_+antibHadron]==1 && (LeadBHadhighpTjet ==false || LeadBHadhighpTjetfromtop == false || NLeadBHadhighpTjet ==false || NLeadBHadhighpTjetfromtop == false) && idx_leadbHadJet[0] != genJet){
	  if(LeadBHadhighpTjet==false){
	    idx_leadbHadJet[0] = genJet;
	    LeadBHadhighpTjet = true;
	    antihadron_index = antibHadron;
	    if((*AntiBHadronFromTopB)[antibHadron] == true){
	      idx_leadbHadJet[1] = genJet;
	      LeadBHadhighpTjetfromtop = true;
	      antihadrontop_index = antibHadron;
	    }
	  }else if(LeadBHadhighpTjetfromtop == false){
	    if((*AntiBHadronFromTopB)[antibHadron] == true){
	      idx_leadbHadJet[1] = genJet;
	      LeadBHadhighpTjetfromtop = true;
	      antihadrontop_index = antibHadron;	      
	    }
	  }else if(NLeadBHadhighpTjet==false && antibHadron!=antihadron_index && idx_leadbHadJet[0] != genJet){
	    idx_nleadbHadJet[0] = genJet;
	    NLeadBHadhighpTjet = true;
	    if((*AntiBHadronFromTopB)[antibHadron] == true && antibHadron!=antihadrontop_index && idx_leadbHadJet[1] != genJet){
	      idx_nleadbHadJet[1] = genJet;
	      NLeadBHadhighpTjetfromtop = true;
	    }
	  }else if(NLeadBHadhighpTjetfromtop == false && antibHadron!=antihadrontop_index && idx_leadbHadJet[1] != genJet){
	    if((*AntiBHadronFromTopB)[antibHadron] == true){
	      idx_nleadbHadJet[1] = genJet;
	      LeadBHadhighpTjetfromtop = true;
	    }
	  }
	}      
      }    
    }
    /*
    //Older version
    for(int genJet=0; genJet<allGenJets_; genJet++){
      for(int bHadron=0; bHadron<BHadrons_; bHadron++){
	if((*BHadronVsJet)[genJet*BHadrons_+bHadron]==1 && (LeadBHadhighpTjet ==false || LeadBHadhighpTjetfromtop == false)){
	  if(LeadBHadhighpTjet==false){
	    idx_leadbHadJet[0] = genJet;
	    LeadBHadhighpTjet = true;
	    if((*BHadronFromTopB)[bHadron] == true){
	      idx_leadbHadJet[1] = genJet;
	      LeadBHadhighpTjetfromtop = true;
	    }
	  }else if(LeadBHadhighpTjetfromtop == false){
	    if((*BHadronFromTopB)[bHadron] == true){
	      idx_leadbHadJet[1] = genJet;
	      LeadBHadhighpTjetfromtop = true;
	    }
	  }
	}      
      }

      for(int antibHadron=0; antibHadron<AntiBHadrons_; antibHadron++){
	if((*AntiBHadronVsJet)[genJet*AntiBHadrons_+antibHadron]==1 && (NLeadBHadhighpTjet ==false || NLeadBHadhighpTjetfromtop == false)){
	  if(NLeadBHadhighpTjet==false){
	    idx_nleadbHadJet[0] = genJet;
	    NLeadBHadhighpTjet = true;
	    if((*AntiBHadronFromTopB)[antibHadron] == true){
	      idx_nleadbHadJet[1] = genJet;
	      NLeadBHadhighpTjetfromtop = true;
	    }
	  }else if(NLeadBHadhighpTjetfromtop == false){
	    if((*AntiBHadronFromTopB)[antibHadron] == true){
	      idx_nleadbHadJet[1] = genJet;
	      NLeadBHadhighpTjetfromtop = true;
	    }
	  }
	}
      }
    }
    */    
    //Case 2: highest pT genJets matched closest to a BHadron
    //BHadJetIndex: vector containing the GetJet indices matched, in DeltaR, to a BHadron. Starting from the highest pT jet.
    if (BHadJetIndex->size() != 0) idx_leadbHadJet[2] = (*BHadJetIndex)[0];
    for (int i=0; i<(int) BHadJetIndex->size(); ++i){ 
      //Only search for those jets matched in DeltaR with a BHadron
      for(int j=0; j<BHadrons_ ; ++j){
	//if ((*BHadronVsJet)[i*BHadrons_+j] == 1 && (*BHadronFromTopB)[j] == true) {idx_bHadJet[3] = (*BHadJetIndex)[i];}
	if ((*BHadronVsJet)[((*BHadJetIndex)[i])*BHadrons_+j] == 1 && (*BHadronFromTopB)[j] == true) {idx_leadbHadJet[3] = (*BHadJetIndex)[i];}
      }
    }
        
    //AntiBHadJetIndex: vector containing the GetJet indices matched, in DeltaR, to a AntiBHadron. Starting from the highest pT jet.
    if (AntiBHadJetIndex->size() != 0) idx_nleadbHadJet[2] = (*AntiBHadJetIndex)[0];
    for (int i=0; i<(int) AntiBHadJetIndex->size(); ++i){ 
      //Only search for those jets matched in DeltaR with a AntiBHadron
      for(int j=0; j<AntiBHadrons_ ; ++j){
	//if ((*AntiBHadronVsJet)[i*AntiBHadrons_+j] == 1 && (*AntiBHadronFromTopB)[j] == true) {idx_antibHadJet[3] = (*AntiBHadJetIndex)[i];}
	if ((*AntiBHadronVsJet)[((*AntiBHadJetIndex)[i])*AntiBHadrons_+j] == 1 && (*AntiBHadronFromTopB)[j] == true) {idx_nleadbHadJet[3] = (*AntiBHadJetIndex)[i];}
      }
    }
        
    //    if(EventCounter % 1000 == 0 && idx_leadbHadJet[0]!=idx_leadbHadJet[1]){//&& idx_bHadJet.size()>1 && idx_antibHadJet.size()>1){
    /*if(idx_leadbHadJet[0]!=idx_leadbHadJet[1]){//&& idx_bHadJet.size()>1 && idx_antibHadJet.size()>1){
      cout<<"-----------------"<<endl;
      cout<<"idx_leadbHadJet.size(): "<<idx_leadbHadJet.size()<<endl;
      cout<<"idx_leadbHadJet[0]: "<<idx_leadbHadJet[0]<<endl;
      cout<<"idx_leadbHadJet[1]: "<<idx_leadbHadJet[1]<<endl;
      cout<<"idx_leadbHadJet[2]: "<<idx_leadbHadJet[2]<<endl;
      cout<<"idx_leadbHadJet[3]: "<<idx_leadbHadJet[3]<<endl;
      cout<<"idx_nleadbHadJet.size()"<<idx_nleadbHadJet.size()<<endl;
      cout<<"idx_nleadbHadJet[0]: "<<idx_nleadbHadJet[0]<<endl;
      cout<<"idx_nleadbHadJet[1]: "<<idx_nleadbHadJet[1]<<endl;
      cout<<"idx_nleadbHadJet[2]: "<<idx_nleadbHadJet[2]<<endl;
      cout<<"idx_nleadbHadJet[3]: "<<idx_nleadbHadJet[3]<<endl;
      }*/
        
    
//     //To avoid recopying many code lines, we select HERE the BHadron JET Indices to cut on.
//     int BHadronIndex;
//     int AntiBHadronIndex;
    //Case 1A: highest pT genJet matched to a BHadron
    BHadronIndex = idx_leadbHadJet[0];
    AntiBHadronIndex = idx_nleadbHadJet[0];
//   
  //   //Case 1B: highest pT genJet matched to a BHadron from Top
    //BHadronIndex = idx_bHadJet[1];
    //AntiBHadronIndex = idx_antibHadJet[1];
    
  //   //Case 2A: highest pT genJets matched closest to a BHadron
    //BHadronIndex = idx_bHadJet[2];
    //AntiBHadronIndex = idx_antibHadJet[2];
  //   
  //   //Case 2B: highest pT genJets matched closest to a BHadron from Top
    //    BHadronIndex = idx_leadbHadJet[3];
    //AntiBHadronIndex = idx_nleadbHadJet[3];


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
    
    h_GenAll->Fill(LVGenTop.M(),weightPU*lumiWeight);
    if (LVGenLepton.Pt()>20 && LVGenAntiLepton.Pt()>20 && abs(LVGenLepton.Eta())<2.4 && abs(LVGenAntiLepton.Eta())<2.4){
      //if (LVGenBQuark.Pt()>30 && LVGenAntiBQuark.Pt()>30 && abs(LVGenBQuark.Eta())<2.4 && abs(LVGenAntiBQuark.Eta())<2.4){
      if(BHadronIndex != -1 	&&   AntiBHadronIndex != -1){
	if(LVGenJets[BHadronIndex].Pt()>30 && abs(LVGenJets[BHadronIndex].Eta())<2.4 &&
	   LVGenJets[AntiBHadronIndex].Pt()>30 && abs(LVGenJets[AntiBHadronIndex].Eta())<2.4){
	  
	  
	  h_VisGenAll->Fill(LVGenTop.M(),weightPU*lumiWeight); 
	  
	  h_VisGenLLBarpT->Fill((LVGenLepton+ LVGenAntiLepton).Pt(),weightPU*lumiWeight);
	  h_VisGenLLBarMass->Fill((LVGenLepton+ LVGenAntiLepton).M(),weightPU*lumiWeight);
	  
	  
	  h_VisGenLeptonpT->Fill(LVGenLepton.Pt(),weightPU*lumiWeight);
	  h_VisGenAntiLeptonpT->Fill(LVGenAntiLepton.Pt(),weightPU*lumiWeight);
	  
	  h_VisGenLeptonEta->Fill(LVGenLepton.Eta(),weightPU*lumiWeight);
	  h_VisGenAntiLeptonEta->Fill(LVGenAntiLepton.Eta(),weightPU*lumiWeight);
	  
	  h_VisGenBJetEta->Fill(LVGenJets[BHadronIndex].Eta(),weightPU*lumiWeight);
	  h_VisGenAntiBJetEta->Fill(LVGenJets[AntiBHadronIndex].Eta(),weightPU*lumiWeight);
	  h_VisGenBJetRapidity->Fill(LVGenJets[BHadronIndex].Rapidity(),weightPU*lumiWeight);
	  h_VisGenAntiBJetRapidity->Fill(LVGenJets[AntiBHadronIndex].Rapidity(),weightPU*lumiWeight);
	  h_VisGenBJetpT->Fill(LVGenJets[BHadronIndex].Pt(),weightPU*lumiWeight);
	  h_VisGenAntiBJetpT->Fill(LVGenJets[AntiBHadronIndex].Pt(),weightPU*lumiWeight);
	  
	  h_VisGenLLBarDPhi->Fill(TMath::Abs(LVGenLepton.DeltaPhi(LVGenAntiLepton)),weightPU*lumiWeight);
	  h_VisGenLeptonantiBjetMass->Fill( (LVGenLepton+LVGenJets[AntiBHadronIndex]).M(),weightPU*lumiWeight);
	  h_VisGenAntiLeptonBjetMass->Fill( (LVGenAntiLepton+LVGenJets[BHadronIndex]).M(),weightPU*lumiWeight);
	  h_VisGenJetMult->Fill(allGenJets_,weightPU*lumiWeight);
	  
	}
      }
    }    
    double VisGenTTBarMass = (LVGenTop+ LVGenAntiTop).M();
    h_VisGenTTBarMass->Fill(VisGenTTBarMass,weightPU*lumiWeight);
    h_VisGenTTBarRapidity->Fill((LVGenTop+ LVGenAntiTop).Rapidity(),weightPU*lumiWeight);
    h_VisGenTTBarpT->Fill((LVGenTop+ LVGenAntiTop).Pt(),weightPU*lumiWeight);
    
    h_VisGenToppT->Fill(LVGenTop.Pt(),weightPU*lumiWeight);
    h_VisGenAntiToppT->Fill(LVGenAntiTop.Pt(),weightPU*lumiWeight);
    h_VisGenTopRapidity->Fill(LVGenTop.Rapidity(),weightPU*lumiWeight);
    h_VisGenAntiTopRapidity->Fill(LVGenAntiTop.Rapidity(),weightPU*lumiWeight);
    h_VisGenTopEta->Fill(LVGenTop.Eta(),weightPU*lumiWeight);
    h_VisGenAntiTopEta->Fill(LVGenAntiTop.Eta(),weightPU*lumiWeight);
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
    h_vertMulti_noPU->Fill(vertMulti,weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
  }
  
  //Do the b-Tag SF calculation!! 
  double btagSF_Pt_Up = 1.0, btagSF_Pt_Down = 1.0, btagSF_Eta_Up = 1.0, btagSF_Eta_Down = 1.0;//shape unceratinty SF
  double btagSF_Up = 1.0, btagSF_Down = 1.0;//Normalization unceratinty SF
  btagSF = 1.0;
  //only for NON data samples
  if(MCSample->find("run201") == string::npos){
    //Only for events passing our selection criteria
    if(lepton_>1 && dimass>12.0 && NLeadLeptonNumber!=0 && jet_>1 && BJetIndex.size()>0 && HypTop_){
        if ((int) LVjet.size()!=(int) jet_ || (int) LVjet.size()!=(int) (*jetBTagCSV).size() || (int) jet_!=(int) (*jetBTagCSV).size()){
            cout<<"WARNING!!!!!"<<endl;
            cout<<"LVjet.size() != jet_     OR     LVjet.size() != jetBTagCSV.size()    OR    jet_!= jetBTagCSV.size()"<<endl;
            return kTRUE;
        }
        //emu channel
        if (channel->find("emu")!=string::npos){
            double OneMinusEff=1;
            double OneMinusSEff=1, OneMinusSEff_PtUp=1, OneMinusSEff_PtDown=1, OneMinusSEff_EtaUp=1, OneMinusSEff_EtaDown=1; //shape variation uncertainty
            double OneMinusSEff_Up=1, OneMinusSEff_Down=1; //Normalization uncertainty
            double SFPerJet=1, eff=1;
            double SFPerJet_Up=0.0, SFPerJet_Down=0.0;
            for (int i=0; i< (int) jet_; ++i){
                double pt=0.0, eta=0.0;
                int ptbin=0, etabin=0;
                double SF_Error=0.0;
                if (LVjet[i].Pt()>30 && TMath::Abs(LVjet[i].Eta())<2.4){
                    pt= LVjet[i].Pt();   eta=abs(LVjet[i].Eta());
                    //select pt & eta bin to take information from per-jet-efficiency histograms
                    for (int iter=0; iter<(int)ptbinning.size(); iter++){
                        if(pt<ptbinning[iter]){continue;}
                        else if (pt> 670.){ptbin = iter+1;}
                        else {ptbin = iter+1;}
                    }
                    for (int iter=0; iter<(int)etabinning.size(); iter++){
                        if(eta<etabinning[iter]){continue;}
                        else {etabin = iter+1;}
                    }
                    //do the type-jet selection & Eff and SF obtention
                    if((*jetType)[i] == 2){//b-quark
                        eff=bEff->GetBinContent(ptbin, etabin);     
                        if (eff <= 0.) eff = 1.;                                     
                        SFPerJet=Analysis::BJetSF(pt, eta);
//                         SFPerJet_Up  = SFPerJet+0.5*Analysis::BJetSFAbsErr(ptbin);
//                         SFPerJet_Down= SFPerJet-0.5*Analysis::BJetSFAbsErr(ptbin);
                        SF_Error = Analysis::BJetSFAbsErr(ptbin);
                    }
                    else if((*jetType)[i] == 1){//c-quark
                        SFPerJet=Analysis::CJetSF(pt, eta);
                        SFPerJet_Up=SFPerJet;
                        SFPerJet_Down=SFPerJet;
                        eff=cEff->GetBinContent(ptbin, etabin);
                        if (eff <= 0.) eff = 1.;                  
                        SF_Error = 0.0;
                    }
                    else if((*jetType)[i] == 0){//l-quark
                        SFPerJet=Analysis::LJetSF(pt, eta);
                        SFPerJet_Up=SFPerJet;
                        SFPerJet_Down=SFPerJet;
                        eff=lEff->GetBinContent(ptbin, etabin);
                        if (eff <= 0.) eff = 1.;                  
                        SF_Error = 0.0;
                    }
                    else {cout<<"I found a jet in event "<<eventNumber<<" which is not b, c nor ligth"<<endl; return kFALSE;}
                    //calculate both numerator and denominator for per-event SF calculation
                    //consider also the UP and DOWN variation for systematics calculation. Same procedure as PU
                    OneMinusEff = OneMinusEff*(1-eff);
                    OneMinusSEff= OneMinusSEff*(1-SFPerJet*eff);
                    if(systematic=="BTAG_UP"){
                        OneMinusSEff_Up= OneMinusSEff_Up*(1-eff*(SFPerJet+SF_Error));
                    }
                    if(systematic=="BTAG_DOWN"){
                        OneMinusSEff_Down= OneMinusSEff_Down*(1-eff*(SFPerJet-SF_Error));
                    }
                    if(systematic=="BTAG_PT_UP"){
                        if (pt>ptmedian)  {OneMinusSEff_PtUp= OneMinusSEff_PtUp*(1-eff*(SFPerJet-0.5*SF_Error));}
                        if (pt<ptmedian)  {OneMinusSEff_PtUp= OneMinusSEff_PtUp*(1-eff*(SFPerJet+0.5*SF_Error));}
                        if (pt==ptmedian) {OneMinusSEff_PtUp= OneMinusSEff_PtUp*(1-eff*SFPerJet);}
                    }
                    if(systematic=="BTAG_PT_DOWN"){
                        if (pt>ptmedian)  {OneMinusSEff_PtDown= OneMinusSEff_PtDown*(1-eff*(SFPerJet+0.5*SF_Error));}
                        if (pt<ptmedian)  {OneMinusSEff_PtDown= OneMinusSEff_PtDown*(1-eff*(SFPerJet-0.5*SF_Error));}
                        if (pt==ptmedian) {OneMinusSEff_PtDown= OneMinusSEff_PtDown*(1-eff*SFPerJet);}
                    }
                    if(systematic=="BTAG_ETA_UP"){
                        if (eta>etamedian)  {OneMinusSEff_EtaUp= OneMinusSEff_EtaUp*(1-eff*(SFPerJet-0.5*SF_Error));}
                        if (eta<etamedian)  {OneMinusSEff_EtaUp= OneMinusSEff_EtaUp*(1-eff*(SFPerJet+0.5*SF_Error));}
                        if (eta==etamedian) {OneMinusSEff_EtaUp= OneMinusSEff_EtaUp*(1-eff*SFPerJet);}
                    }
                    if(systematic=="BTAG_ETA_DOWN"){
                        if (eta>etamedian)  {OneMinusSEff_EtaDown= OneMinusSEff_EtaDown*(1-eff*(SFPerJet+0.5*SF_Error));}
                        if (eta<etamedian)  {OneMinusSEff_EtaDown= OneMinusSEff_EtaDown*(1-eff*(SFPerJet-0.5*SF_Error));}
                        if (eta==etamedian) {OneMinusSEff_EtaDown= OneMinusSEff_EtaDown*(1-eff*SFPerJet);}
                    }
                }
            };
             //per-event SF calculation (also the UP and DOWN variations)
            btagSF      = (1.-OneMinusSEff)/(1.-OneMinusEff);
            btagSF_Pt_Up   = (1.-OneMinusSEff_PtUp)/(1.-OneMinusEff);
            btagSF_Pt_Down = (1.-OneMinusSEff_PtDown)/(1.-OneMinusEff);
            btagSF_Eta_Up   = (1.-OneMinusSEff_EtaUp)/(1.-OneMinusEff);
            btagSF_Eta_Down = (1.-OneMinusSEff_EtaDown)/(1.-OneMinusEff);
            btagSF_Up   = (1.-OneMinusSEff_Up)/(1.-OneMinusEff);
            btagSF_Down = (1.-OneMinusSEff_Down)/(1.-OneMinusEff);
            
        }
        //ee && mumu channels
        else if ((dimass<76.0 || dimass > 106.0) && *(metEt->begin()) > 30 ){
            double OneMinusEff=1;
            double OneMinusSEff=1, OneMinusSEff_PtUp=1, OneMinusSEff_PtDown=1, OneMinusSEff_EtaUp=1, OneMinusSEff_EtaDown=1; //shape variation uncertainty
            double OneMinusSEff_Up=1, OneMinusSEff_Down=1; //Normalization uncertainty
            double SFPerJet=1, eff=1;
            double SFPerJet_Up=0.0, SFPerJet_Down=0.0;
            for (int i=0; i< (int) jet_; ++i){
                double pt=0.0, eta=0.0;
                int ptbin=0, etabin=0;
                double SF_Error=0.0;
                if (LVjet[i].Pt()>30 && TMath::Abs(LVjet[i].Eta())<2.4){
                    pt= LVjet[i].Pt();   eta=abs(LVjet[i].Eta());
                    //select pt & eta bin to take information from per-jet-efficiency histograms
                    for (int iter=0; iter<(int)ptbinning.size(); iter++){
                        if(pt<ptbinning[iter]){continue;}
                        else if (pt> 670.){ptbin = iter+1;}
                        else {ptbin = iter+1;}
                    }
                    for (int iter=0; iter<(int)etabinning.size(); iter++){
                        if(eta<etabinning[iter]){continue;}
                        else {etabin = iter+1;}
                    }
                    //do the type-jet selection & Eff and SF obtention
                    if((*jetType)[i] == 2){//b-quark
                        eff=bEff->GetBinContent(ptbin, etabin);  
                        if (eff <= 0.) eff = 1.;                      
                        SFPerJet=Analysis::BJetSF(pt, eta);
//                         SFPerJet_Up  = SFPerJet+0.5*Analysis::BJetSFAbsErr(ptbin);
//                         SFPerJet_Down= SFPerJet-0.5*Analysis::BJetSFAbsErr(ptbin);
                        SF_Error = Analysis::BJetSFAbsErr(ptbin);
                    }
                    else if((*jetType)[i] == 1){//c-quark
                        SFPerJet=Analysis::CJetSF(pt, eta);
                        SFPerJet_Up=SFPerJet;
                        SFPerJet_Down=SFPerJet;
                        eff=cEff->GetBinContent(ptbin, etabin);
                        if (eff <= 0.) eff = 1.;                  
                        SF_Error = 0.0;
                    }
                    else if((*jetType)[i] == 0){//l-quark
                        SFPerJet=Analysis::LJetSF(pt, eta);
                        SFPerJet_Up=SFPerJet;
                        SFPerJet_Down=SFPerJet;
                        eff=lEff->GetBinContent(ptbin, etabin);
                        if (eff <= 0.) eff = 1.;                  
                        SF_Error = 0.0;
                    }
                    else {cout<<"I found a jet in event "<<eventNumber<<" which is not b, c nor ligth"<<endl; return kFALSE;}
                    //calculate both numerator and denominator for per-event SF calculation
                    //consider also the UP and DOWN variation for systematics calculation. Same procedure as PU
                    OneMinusEff = OneMinusEff*(1-eff);
                    OneMinusSEff= OneMinusSEff*(1-SFPerJet*eff);
                    if(systematic=="BTAG_UP"){
                        OneMinusSEff_Up= OneMinusSEff_Up*(1-eff*(SFPerJet+SF_Error));
                    }
                    if(systematic=="BTAG_DOWN"){
                        OneMinusSEff_Down= OneMinusSEff_Down*(1-eff*(SFPerJet-SF_Error));
                    }
                    if(systematic=="BTAG_PT_UP"){
                        if (pt>ptmedian)  {OneMinusSEff_PtUp= OneMinusSEff_PtUp*(1-eff*(SFPerJet-0.5*SF_Error));}
                        if (pt<ptmedian)  {OneMinusSEff_PtUp= OneMinusSEff_PtUp*(1-eff*(SFPerJet+0.5*SF_Error));}
                        if (pt==ptmedian) {OneMinusSEff_PtUp= OneMinusSEff_PtUp*(1-eff*SFPerJet);}
                    }
                    if(systematic=="BTAG_PT_DOWN"){
                        if (pt>ptmedian)  {OneMinusSEff_PtDown= OneMinusSEff_PtDown*(1-eff*(SFPerJet+0.5*SF_Error));}
                        if (pt<ptmedian)  {OneMinusSEff_PtDown= OneMinusSEff_PtDown*(1-eff*(SFPerJet-0.5*SF_Error));}
                        if (pt==ptmedian) {OneMinusSEff_PtDown= OneMinusSEff_PtDown*(1-eff*SFPerJet);}
                    }
                    if(systematic=="BTAG_ETA_UP"){
                        if (eta>etamedian)  {OneMinusSEff_EtaUp= OneMinusSEff_EtaUp*(1-eff*(SFPerJet-0.5*SF_Error));}
                        if (eta<etamedian)  {OneMinusSEff_EtaUp= OneMinusSEff_EtaUp*(1-eff*(SFPerJet+0.5*SF_Error));}
                        if (eta==etamedian) {OneMinusSEff_EtaUp= OneMinusSEff_EtaUp*(1-eff*SFPerJet);}
                    }
                    if(systematic=="BTAG_ETA_DOWN"){
                        if (eta>etamedian)  {OneMinusSEff_EtaDown= OneMinusSEff_EtaDown*(1-eff*(SFPerJet+0.5*SF_Error));}
                        if (eta<etamedian)  {OneMinusSEff_EtaDown= OneMinusSEff_EtaDown*(1-eff*(SFPerJet-0.5*SF_Error));}
                        if (eta==etamedian) {OneMinusSEff_EtaDown= OneMinusSEff_EtaDown*(1-eff*SFPerJet);}
                    }
                }
            };
             //per-event SF calculation (also the UP and DOWN variations)
            btagSF      = (1.-OneMinusSEff)/(1.-OneMinusEff);
            btagSF_Pt_Up   = (1.-OneMinusSEff_PtUp)/(1.-OneMinusEff);
            btagSF_Pt_Down = (1.-OneMinusSEff_PtDown)/(1.-OneMinusEff);
            btagSF_Eta_Up   = (1.-OneMinusSEff_EtaUp)/(1.-OneMinusEff);
            btagSF_Eta_Down = (1.-OneMinusSEff_EtaDown)/(1.-OneMinusEff);
            btagSF_Up   = (1.-OneMinusSEff_Up)/(1.-OneMinusEff);
            btagSF_Down = (1.-OneMinusSEff_Down)/(1.-OneMinusEff);
        }
    }
  }
  //End of b-Tag SF calculation!!

  //Set the Btag SF for each of the cases: shape (Nominal, systUp, systDown) and normalization(up and down)
  if(systematic=="BTAG_PT_UP") btagSF=btagSF_Pt_Up;
  else if(systematic=="BTAG_PT_DOWN") btagSF=btagSF_Pt_Down;
  else if(systematic=="BTAG_ETA_UP") btagSF=btagSF_Eta_Up;
  else if(systematic=="BTAG_ETA_DOWN") btagSF=btagSF_Eta_Down;
  else if(systematic=="BTAG_UP") btagSF=btagSF_Up;
  else if(systematic=="BTAG_DOWN") btagSF=btagSF_Down;
  
  h_BTagSF->Fill(btagSF);
  h_BTagEvtSF->Fill(EventCounter, btagSF);

  h_BTagSF_Pt_Up->Fill(btagSF_Pt_Up);
  h_BTagEvtSF_Pt_Up->Fill(EventCounter, btagSF_Pt_Up);
  h_BTagSF_Pt_Down->Fill(btagSF_Pt_Down);
  h_BTagEvtSF_Pt_Down->Fill(EventCounter, btagSF_Pt_Down);
  h_BTagSF_Eta_Up->Fill(btagSF_Eta_Up);
  h_BTagEvtSF_Eta_Up->Fill(EventCounter, btagSF_Eta_Up);
  h_BTagSF_Eta_Down->Fill(btagSF_Eta_Down);
  h_BTagEvtSF_Eta_Down->Fill(EventCounter, btagSF_Eta_Down);
  h_BTagSF_Up->Fill(btagSF_Up);
  h_BTagEvtSF_Up->Fill(EventCounter, btagSF_Up);
  h_BTagSF_Down->Fill(btagSF_Down);
  h_BTagEvtSF_Down->Fill(EventCounter, btagSF_Down);
  
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
      h_jetMulti_diLep->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
      h_diLepMassFull->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
      if(channel->find("emu")!=string::npos){//quick and DIRTY!
	h_step5->Fill(1,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	if((*lepQ)[LeadLeptonNumber]==1){
	  h_LeptonpT_diLep->Fill(LVlepton[NLeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_AntiLeptonpT_diLep->Fill(LVlepton[LeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_LeptonEta_diLep->Fill(LVlepton[NLeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_AntiLeptonEta_diLep->Fill(LVlepton[LeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	}else{
	  h_LeptonpT_diLep->Fill(LVlepton[LeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_AntiLeptonpT_diLep->Fill(LVlepton[NLeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_LeptonEta_diLep->Fill(LVlepton[LeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_AntiLeptonEta_diLep->Fill(LVlepton[NLeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	}		
	if(dimass>12.0 && jet_>1){
	  h_step6->Fill(1,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_step7->Fill(1,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  
	  if(BJetIndex.size()>0){btagSFuse=btagSF;
	    h_step8->Fill(1,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);	    
	    if(HypTop_){weightKinFituse=weightKinFit;
	      h_step9->Fill(1,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);	    
	      h_diLepMassFull_fullSel->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    }
	    
	    //btagSFuse=1.0;
	    weightKinFituse=1.0;
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
	}
      }else{
	if (dimass> 12.0 && (dimass<76.0 || dimass > 106.0)){
	  h_step5->Fill(1,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  if((*lepQ)[LeadLeptonNumber]==1){
	    h_LeptonpT_diLep->Fill(LVlepton[NLeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonpT_diLep->Fill(LVlepton[LeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_LeptonEta_diLep->Fill(LVlepton[NLeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonEta_diLep->Fill(LVlepton[LeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }else{
	    h_LeptonpT_diLep->Fill(LVlepton[LeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonpT_diLep->Fill(LVlepton[NLeadLeptonNumber].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_LeptonEta_diLep->Fill(LVlepton[LeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonEta_diLep->Fill(LVlepton[NLeadLeptonNumber].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }	
	  if(jet_>1){
	    h_step6->Fill(1,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    if(*(metEt->begin()) > 30){
	      h_step7->Fill(1,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      if(BJetIndex.size()>0){btagSFuse=btagSF;
		h_step8->Fill(1,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);	    
		if(HypTop_){weightKinFituse=weightKinFit;
		  h_step9->Fill(1,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);	    
		  h_diLepMassFull_fullSel->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);	
		}
	      }
	    }
	  }
	}
	//	btagSFuse=1.0;
	weightKinFituse=1.0;
	if (dimass> 12.0 && (dimass<76.0 || dimass > 106.0) && jet_>1 && *(metEt->begin()) > 30 && BJetIndex.size()>0){
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
	    //if (LVGenBQuark.Pt()>30 && LVGenAntiBQuark.Pt()>30 && abs(LVGenBQuark.Eta())<2.4 && abs(LVGenAntiBQuark.Eta())<2.4){
	    if(BHadronIndex != -1 && LVGenJets[BHadronIndex].Pt()>30 && abs(LVGenJets[BHadronIndex].Eta())<2.4 &&
	       AntiBHadronIndex != -1 && LVGenJets[AntiBHadronIndex].Pt()>30 && abs(LVGenJets[AntiBHadronIndex].Eta())<2.4 ){
	      //            if(LVBHadronGenJet.Pt()>30 && abs(LVBHadronGenJet.Eta())<2.4 &&
	      // 	    LVAntiBHadronGenJet.Pt()>30 && abs(LVAntiBHadronGenJet.Eta())<2.4){
	      
	      h_jetMultiVisTop->Fill(jet_,weightLepSF*btagSF*trigEFF*weightKinFit); 
	    }
	  }//for visible top events
	  //	  if(HypTop_ && BHadronIndex>=0 && AntiBHadronIndex>=0){
	  if(HypTop_){ 
	    h_GenRecoLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),LVGenLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	    h_GenRecoAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),LVGenAntiLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenRecoLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),LVGenLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenRecoAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),LVGenAntiLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    
	    h_GenRecoTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),LVGenTop.Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenRecoAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),LVGenAntiTop.Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenRecoToppT->Fill(LVHypTop[solutionIndex].Pt(),LVGenTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenRecoAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),LVGenAntiTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    
	    h_GenRecoLLBarDPhi->Fill(TMath::Abs(LVHypLepton[solutionIndex].DeltaPhi(LVHypAntiLepton[solutionIndex])),TMath::Abs(LVGenLepton.DeltaPhi(LVGenAntiLepton)),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    
	    if ( BHadronIndex>=0 ) {
	      h_GenRecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),LVGenJets[BHadronIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),LVGenJets[BHadronIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoBJetEta->Fill(LVHypBJet[solutionIndex].Eta(),LVGenJets[BHadronIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoAntiLeptonBjetMass->Fill((LVHypAntiLepton[solutionIndex]+LVHypBJet[solutionIndex]).M(),(LVGenAntiLepton+LVGenJets[BHadronIndex]).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    } else {
	      h_GenRecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoBJetEta->Fill(LVHypBJet[solutionIndex].Eta(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
              h_GenRecoAntiLeptonBjetMass->Fill((LVHypAntiLepton[solutionIndex]+LVHypBJet[solutionIndex]).M(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    }
	    if ( AntiBHadronIndex>=0 ) { 
	      h_GenRecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),LVGenJets[AntiBHadronIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);  
	      h_GenRecoAntiBJetRapidity->Fill(LVHypAntiBJet[solutionIndex].Rapidity(),LVGenJets[AntiBHadronIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse); 
	      h_GenRecoAntiBJetEta->Fill(LVHypAntiBJet[solutionIndex].Eta(),LVGenJets[AntiBHadronIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
              h_GenRecoLeptonantiBjetMass->Fill((LVHypLepton[solutionIndex]+LVHypAntiBJet[solutionIndex]).M(),(LVGenLepton+LVGenJets[AntiBHadronIndex]).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    } else {
	      h_GenRecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);  
	      h_GenRecoAntiBJetRapidity->Fill(LVHypAntiBJet[solutionIndex].Rapidity(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse); 
	      h_GenRecoAntiBJetEta->Fill(LVHypAntiBJet[solutionIndex].Eta(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
              h_GenRecoLeptonantiBjetMass->Fill((LVHypLepton[solutionIndex]+LVHypAntiBJet[solutionIndex]).M(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    }
	    
	    if(BHadronIndex>=0 && AntiBHadronIndex>=0){h_GenRecoJetMult->Fill(jet_, allGenJets_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);}
	    else{h_GenRecoJetMult->Fill(jet_, -1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);}
	    
	    h_GenRecoLLBarMass->Fill((LVHypLepton[solutionIndex]+LVHypAntiLepton[solutionIndex]).M(),(LVGenLepton+LVGenAntiLepton).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenRecoLLBarpT->Fill((LVHypLepton[solutionIndex]+LVHypAntiLepton[solutionIndex]).Pt(),(LVGenLepton+LVGenAntiLepton).Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	    h_GenRecoTTBarMass->Fill((LVHypTop[solutionIndex]+LVHypAntiTop[solutionIndex]).M(),(LVGenTop+LVGenAntiTop).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenRecoTTBarpT->Fill((LVHypTop[solutionIndex]+LVHypAntiTop[solutionIndex]).Pt(),(LVGenTop+LVGenAntiTop).Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenRecoTTBarRapidity->Fill((LVHypTop[solutionIndex]+LVHypAntiTop[solutionIndex]).Rapidity(),(LVGenTop+LVGenAntiTop).Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    
	  }//for purity stability calculations
	  double GenTTBarMass = (LVGenTop+ LVGenAntiTop).M();
	  h_GenTTBarMass->Fill(GenTTBarMass,1);
	  /*h_GenToppT->Fill(LVGenTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiToppT->Fill(LVGenAntiTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenLeptonpT->Fill(LVGenLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiLeptonpT->Fill(LVGenAntiLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  //h_GenBQuarkpT->Fill(LVGenBQuark.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  //h_GenAntiBQuarkpT->Fill(LVGenAntiBQuark.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

//	  h_GenBJetpT->Fill(LVBHadronGenJet.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
//	  h_GenAntiBJetpT->Fill(LVAntiBHadronGenJet.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenBJetpT->Fill(LVGenJets[BHadronIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiBJetpT->Fill(LVGenJets[AntiBHadronIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenBJetEta->Fill(LVGenJets[BHadronIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
 	  h_GenAntiBJetEta->Fill(LVGenJets[AntiBHadronIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
 	  h_GenBJetRapidity->Fill(LVGenJets[BHadronIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
 	  h_GenAntiBJetRapidity->Fill(LVGenJets[AntiBHadronIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  
	  h_GenTopEta->Fill(LVGenTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiTopEta->Fill(LVGenAntiTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  //h_GenBQuarkEta->Fill(LVGenBQuark.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  //h_GenAntiBQuarkEta->Fill(LVGenAntiBQuark.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenLeptonEta->Fill(LVGenLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiLeptonEta->Fill(LVGenAntiLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenBQuarkRapidity->Fill(LVGenBQuark.Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	  h_GenAntiBQuarkRapidity->Fill(LVGenAntiBQuark.Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	
*/
	}
	if(HypTop_){
	  //h_jetMulti->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  //	  cout<<"SolutionIndex: "<<solutionIndex<<endl;
	  double HypTTBarMass = (LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).M();
	  h_RecoTTBarMass->Fill(HypTTBarMass,weightPU*lumiWeight); 
	  h_RecoTTBarRapidity->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Rapidity(),weightPU*lumiWeight); 
	  h_RecoTTBarpT->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Pt(),weightPU*lumiWeight); 
	  h_RecoToppT->Fill(LVHypTop[solutionIndex].Pt(),weightPU*lumiWeight); 
	  h_RecoAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),weightPU*lumiWeight); 
	  h_RecoTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),weightPU*lumiWeight); 
	  h_RecoAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),weightPU*lumiWeight); 

	  h_RecoLLBarMass->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).M(),weightPU*lumiWeight); 
	  h_RecoLLBarpT->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).Pt(),weightPU*lumiWeight); 
	  h_RecoLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),weightPU*lumiWeight); 
	  h_RecoAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),weightPU*lumiWeight); 
	  h_RecoLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),weightPU*lumiWeight); 
	  h_RecoAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),weightPU*lumiWeight); 

	  h_RecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),weightPU*lumiWeight); 
	  h_RecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),weightPU*lumiWeight); 
	  h_RecoBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),weightPU*lumiWeight); 
	  h_RecoAntiBJetRapidity->Fill(LVHypAntiBJet[solutionIndex].Rapidity(),weightPU*lumiWeight); 
	  h_RecoBJetEta->Fill(LVHypBJet[solutionIndex].Eta(),weightPU*lumiWeight); 
	  h_RecoAntiBJetEta->Fill(LVHypAntiBJet[solutionIndex].Eta(),weightPU*lumiWeight);
	  
	  h_RecoLLBarDPhi->Fill(TMath::Abs(LVHypLepton[solutionIndex].DeltaPhi(LVHypAntiLepton[solutionIndex])),weightPU*lumiWeight);
          h_RecoLeptonantiBjetMass->Fill((LVHypLepton[solutionIndex]+LVHypAntiBJet[solutionIndex]).M(),weightPU*lumiWeight);
          h_RecoAntiLeptonBjetMass->Fill((LVHypAntiLepton[solutionIndex]+LVHypBJet[solutionIndex]).M(),weightPU*lumiWeight);
          h_RecoJetMult->Fill(jet_,weightPU*lumiWeight);

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

	  h_HypLLBarDPhi->Fill(TMath::Abs(LVHypLepton[solutionIndex].DeltaPhi(LVHypAntiLepton[solutionIndex])),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypLeptonantiBjetMass->Fill((LVHypLepton[solutionIndex] + LVHypAntiBJet[solutionIndex]).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiLeptonBjetMass->Fill((LVHypAntiLepton[solutionIndex] + LVHypBJet[solutionIndex]).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypJetMult->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

          h_HypLLBarpTDPhi->Fill((LVHypLepton[solutionIndex] + LVHypAntiBJet[solutionIndex]).Pt(), TMath::Abs(LVHypLepton[solutionIndex].DeltaPhi(LVHypAntiLepton[solutionIndex])), 1);
          
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
	      //if (LVGenBQuark.Pt()>30 && LVGenAntiBQuark.Pt()>30 && abs(LVGenBQuark.Eta())<2.4 && abs(LVGenAntiBQuark.Eta())<2.4){
	      if(BHadronIndex != -1 && LVGenJets[BHadronIndex].Pt()>30 && abs(LVGenJets[BHadronIndex].Eta())<2.4 &&
		 AntiBHadronIndex != -1 && LVGenJets[AntiBHadronIndex].Pt()>30 && abs(LVGenJets[AntiBHadronIndex].Eta())<2.4 ){
		//            if(LVBHadronGenJet.Pt()>30 && abs(LVBHadronGenJet.Eta())<2.4 &&
		// 	    LVAntiBHadronGenJet.Pt()>30 && abs(LVAntiBHadronGenJet.Eta())<2.4){
		
		
		h_jetMultiVisTop->Fill(jet_,weightLepSF*btagSF*trigEFF*weightKinFit); 
	      }
	    }//for visible top events

	    if(HypTop_){
	      h_GenRecoLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),LVGenLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	      h_GenRecoAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),LVGenAntiLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),LVGenLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),LVGenAntiLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    
	      h_GenRecoTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),LVGenTop.Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),LVGenAntiTop.Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoToppT->Fill(LVHypTop[solutionIndex].Pt(),LVGenTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),LVGenAntiTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

              h_GenRecoLLBarDPhi->Fill(TMath::Abs(LVHypLepton[solutionIndex].DeltaPhi(LVHypAntiLepton[solutionIndex])),TMath::Abs(LVGenLepton.DeltaPhi(LVGenAntiLepton)),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    
	    
		    if ( BHadronIndex>=0 ) {
		      h_GenRecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),LVGenJets[BHadronIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
		      h_GenRecoBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),LVGenJets[BHadronIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
		      h_GenRecoBJetEta->Fill(LVHypBJet[solutionIndex].Eta(),LVGenJets[BHadronIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
		      h_GenRecoAntiLeptonBjetMass->Fill((LVHypAntiLepton[solutionIndex]+LVHypBJet[solutionIndex]).M(),(LVGenAntiLepton+LVGenJets[BHadronIndex]).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
		    } else {
		      h_GenRecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
		      h_GenRecoBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
		      h_GenRecoBJetEta->Fill(LVHypBJet[solutionIndex].Eta(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
                      h_GenRecoAntiLeptonBjetMass->Fill((LVHypAntiLepton[solutionIndex]+LVHypBJet[solutionIndex]).M(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
		    }
		    if ( AntiBHadronIndex>=0 ) { 
		      h_GenRecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),LVGenJets[AntiBHadronIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);  
		      h_GenRecoAntiBJetRapidity->Fill(LVHypAntiBJet[solutionIndex].Rapidity(),LVGenJets[AntiBHadronIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse); 
		      h_GenRecoAntiBJetEta->Fill(LVHypAntiBJet[solutionIndex].Eta(),LVGenJets[AntiBHadronIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
		      h_GenRecoLeptonantiBjetMass->Fill((LVHypLepton[solutionIndex]+LVHypAntiBJet[solutionIndex]).M(),(LVGenLepton+LVGenJets[AntiBHadronIndex]).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
		    } else {
		      h_GenRecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);  
		      h_GenRecoAntiBJetRapidity->Fill(LVHypAntiBJet[solutionIndex].Rapidity(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse); 
		      h_GenRecoAntiBJetEta->Fill(LVHypAntiBJet[solutionIndex].Eta(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
		      h_GenRecoLeptonantiBjetMass->Fill((LVHypLepton[solutionIndex]+LVHypAntiBJet[solutionIndex]).M(),-1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
		    }
		    
		    if(BHadronIndex>=0 && AntiBHadronIndex>=0){h_GenRecoJetMult->Fill(jet_, allGenJets_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);}
		    else{h_GenRecoJetMult->Fill(jet_, -1000.,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);}
		    
//	      h_GenRecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),LVBHadronGenJet.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
//	      h_GenRecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),LVAntiBHadronGenJet.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	      
	      h_GenRecoLLBarMass->Fill((LVHypLepton[solutionIndex]+LVHypAntiLepton[solutionIndex]).M(),(LVGenLepton+LVGenAntiLepton).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoLLBarpT->Fill((LVHypLepton[solutionIndex]+LVHypAntiLepton[solutionIndex]).Pt(),(LVGenLepton+LVGenAntiLepton).Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	      h_GenRecoTTBarMass->Fill((LVHypTop[solutionIndex]+LVHypAntiTop[solutionIndex]).M(),(LVGenTop+LVGenAntiTop).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoTTBarpT->Fill((LVHypTop[solutionIndex]+LVHypAntiTop[solutionIndex]).Pt(),(LVGenTop+LVGenAntiTop).Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	      h_GenRecoTTBarRapidity->Fill((LVHypTop[solutionIndex]+LVHypAntiTop[solutionIndex]).Rapidity(),(LVGenTop+LVGenAntiTop).Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    
	    }//for purity stability calculations
	  
	    double GenTTBarMass = (LVGenTop+ LVGenAntiTop).M();
	    h_GenTTBarMass->Fill(GenTTBarMass,1);
	    /*	    h_GenToppT->Fill(LVGenTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenAntiToppT->Fill(LVGenAntiTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenLeptonpT->Fill(LVGenLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenAntiLeptonpT->Fill(LVGenAntiLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    //h_GenBQuarkpT->Fill(LVGenBQuark.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    //h_GenAntiBQuarkpT->Fill(LVGenAntiBQuark.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    
	    //	    h_GenBJetpT->Fill(LVBHadronGenJet.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    //h_GenAntiBJetpT->Fill(LVAntiBHadronGenJet.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenBJetpT->Fill(LVGenJets[BHadronIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenAntiBJetpT->Fill(LVGenJets[AntiBHadronIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
 	    h_GenBJetEta->Fill(LVGenJets[BHadronIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
 	    h_GenAntiBJetEta->Fill(LVGenJets[AntiBHadronIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse); 	    
     	    h_GenBJetRapidity->Fill(LVGenJets[BHadronIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
 	    h_GenAntiBJetRapidity->Fill(LVGenJets[AntiBHadronIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	    h_GenTopEta->Fill(LVGenTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenAntiTopEta->Fill(LVGenAntiTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    //h_GenBQuarkEta->Fill(LVGenBQuark.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    //h_GenAntiBQuarkEta->Fill(LVGenAntiBQuark.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenLeptonEta->Fill(LVGenLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_GenAntiLeptonEta->Fill(LVGenAntiLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenBQuarkRapidity->Fill(LVGenBQuark.Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
// 	    h_GenAntiBQuarkRapidity->Fill(LVGenAntiBQuark.Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
*/
	  }
	   
	  if(HypTop_){
	    //	  cout<<"SolutionIndex: "<<solutionIndex<<endl;
	    double HypTTBarMass = (LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).M();
	    h_RecoTTBarMass->Fill(HypTTBarMass,weightPU*lumiWeight); 
	    h_RecoTTBarRapidity->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Rapidity(),weightPU*lumiWeight); 
	    h_RecoTTBarpT->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Pt(),weightPU*lumiWeight); 
	    h_RecoToppT->Fill(LVHypTop[solutionIndex].Pt(),weightPU*lumiWeight); 
	    h_RecoAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),weightPU*lumiWeight); 
	    h_RecoTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),weightPU*lumiWeight); 
	    h_RecoAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),weightPU*lumiWeight); 

	    h_RecoLLBarMass->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).M(),weightPU*lumiWeight); 
	    h_RecoLLBarpT->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).Pt(),weightPU*lumiWeight); 
	    h_RecoLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),weightPU*lumiWeight); 
	    h_RecoAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),weightPU*lumiWeight); 
	    h_RecoLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),weightPU*lumiWeight); 
	    h_RecoAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),weightPU*lumiWeight); 

	    h_RecoBJetpT->Fill(LVHypBJet[solutionIndex].Pt(),weightPU*lumiWeight); 
	    h_RecoAntiBJetpT->Fill(LVHypAntiBJet[solutionIndex].Pt(),weightPU*lumiWeight); 
	    h_RecoBJetRapidity->Fill(LVHypBJet[solutionIndex].Rapidity(),weightPU*lumiWeight); 
	    h_RecoAntiBJetRapidity->Fill(LVHypAntiBJet[solutionIndex].Rapidity(),weightPU*lumiWeight); 
	    h_RecoBJetEta->Fill(LVHypBJet[solutionIndex].Eta(),weightPU*lumiWeight); 
	    h_RecoAntiBJetEta->Fill(LVHypAntiBJet[solutionIndex].Eta(),weightPU*lumiWeight); 

	    h_RecoLLBarDPhi->Fill(TMath::Abs(LVHypLepton[solutionIndex].DeltaPhi(LVHypAntiLepton[solutionIndex])),weightPU*lumiWeight);
	    h_RecoLeptonantiBjetMass->Fill((LVHypLepton[solutionIndex]+LVHypAntiBJet[solutionIndex]).M(),weightPU*lumiWeight);
	    h_RecoAntiLeptonBjetMass->Fill((LVHypAntiLepton[solutionIndex]+LVHypBJet[solutionIndex]).M(),weightPU*lumiWeight);
	    h_RecoJetMult->Fill(jet_,weightPU*lumiWeight);

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
	    
	    h_HypLLBarDPhi->Fill(TMath::Abs(LVHypLepton[solutionIndex].DeltaPhi(LVHypAntiLepton[solutionIndex])),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypLeptonantiBjetMass->Fill((LVHypLepton[solutionIndex] + LVHypAntiBJet[solutionIndex]).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypAntiLeptonBjetMass->Fill((LVHypAntiLepton[solutionIndex] + LVHypBJet[solutionIndex]).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_HypJetMult->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	     
            h_HypLLBarpTDPhi->Fill((LVHypLepton[solutionIndex] + LVHypAntiBJet[solutionIndex]).Pt(), TMath::Abs(LVHypLepton[solutionIndex].DeltaPhi(LVHypAntiLepton[solutionIndex])), 1);
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
  
  h_GenRecoTopRapidity->Write();
  h_GenRecoAntiTopRapidity->Write();
  h_GenRecoToppT->Write();
  h_GenRecoAntiToppT->Write();

  h_GenRecoLLBarpT->Write();
  h_GenRecoLLBarMass->Write();
  h_GenRecoTTBarpT->Write();
  h_GenRecoTTBarMass->Write();
  h_GenRecoTTBarRapidity->Write();
  
  h_GenRecoLLBarDPhi->Write(); 
  h_GenRecoLeptonantiBjetMass->Write();
  h_GenRecoAntiLeptonBjetMass->Write();
  h_GenRecoJetMult->Write();

  h_NJetMatching->Write();
  h_diLepMassFull->Write();
  h_diLepMassFull_fullSel->Write();
  Allh1->Write();
  Looseh1->Write();
  h_GenAll->Write();
  h_VisGenAll->Write();
  h_vertMulti->Write();
  h_vertMulti_noPU->Write();
  h_jetMulti->Write();
  h_jetMulti_diLep->Write();
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
  h_RecoBJetEta->Write();
  h_RecoAntiBJetEta->Write();

  h_RecoLLBarDPhi->Write();
  h_RecoLeptonantiBjetMass->Write();
  h_RecoAntiLeptonBjetMass->Write();
  h_RecoJetMult->Write();

  h_jetpT->Write();
  h_jetHT->Write();
  h_MET->Write();
  h_LeptonpT->Write();
  h_LeptonpT_diLep->Write();
  h_LeptonEta_diLep->Write();
  h_AntiLeptonpT_diLep->Write();
  h_AntiLeptonEta_diLep->Write();
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

  /*  h_VisGenBQuarkpT->Write();
  h_VisGenAntiBQuarkpT->Write();
  h_VisGenBQuarkRapidity->Write();
  h_VisGenAntiBQuarkRapidity->Write();
  h_VisGenBQuarkEta->Write();
  h_VisGenAntiBQuarkEta->Write();
  */
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
  
  h_VisGenLLBarDPhi->Write();
  h_VisGenLeptonantiBjetMass->Write();
  h_VisGenAntiLeptonBjetMass->Write();
  h_VisGenJetMult->Write();

  /*  h_GenBJetpT->Write();
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
  
  h_GenLLBarDPhi->Write();
  h_GenLeptonantiBjetMass->Write();
  h_GenAntiLeptonBjetMass->Write();
  h_GenJetMult->Write();

  h_GenBQuarkpT->Write();
  h_GenAntiBQuarkpT->Write();
  h_GenBQuarkRapidity->Write();
  h_GenAntiBQuarkRapidity->Write();
  h_GenBQuarkEta->Write();
  h_GenAntiBQuarkEta->Write();
  */
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
  
  h_HypLLBarDPhi->Write();
  h_HypLeptonantiBjetMass->Write();
  h_HypAntiLeptonBjetMass->Write();
  h_HypJetMult->Write();

  h_step5->Write();
  h_step6->Write();
  h_step7->Write();
  h_step8->Write();
  h_step9->Write();
  
  
  h_BTagSF->Write();
  h_BTagEvtSF->Write();
  h_BTagSF_Pt_Up->Write();
  h_BTagEvtSF_Pt_Up->Write();
  h_BTagSF_Pt_Down->Write();
  h_BTagEvtSF_Pt_Down->Write();
  h_BTagSF_Eta_Up->Write();
  h_BTagEvtSF_Eta_Up->Write();
  h_BTagSF_Eta_Down->Write();
  h_BTagEvtSF_Eta_Down->Write();
  h_BTagSF_Up->Write();
  h_BTagEvtSF_Up->Write();
  h_BTagSF_Down->Write();
  h_BTagEvtSF_Down->Write();
  
  h_HypLLBarpTDPhi->Write();
  
  f->Close();
  cout<<"Created: "<<f_savename<<endl;
}
