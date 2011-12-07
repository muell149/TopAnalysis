#define Analysis_cxx

#include "Analysis.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include "TLorentzVector.h"
#include "rescaleFunctions.h"
#include <fstream>
#include <iostream>
#include <TMath.h>
#include <TSystem.h>

void Analysis::Begin(TTree * /*tree*/)
{

  TString option = GetOption();
  //  totalEventCount=0;

  

   ///init counters
  //  ifstream insample("samples.txt",std::ios::in);
  //insample>>sample;

   TString dataset="ee";

  
   /*   AllDIM.setDataSet(dataset);
   AllDIM.setOptions("AllDIM","AllDIM","Events",50,0,400,1);
   InDIM.setDataSet(dataset);
   InDIM.setOptions("InDIM","InDIM","Events",50,0,400,1);
   OutDIM.setDataSet(dataset);
   OutDIM.setOptions("OutDIM","OutDIM","Events",50,0,400,1);
   */
   gStyle->SetOptStat(0);

   h_jetMulti = new TH1D("jetMulti", "Jet Multiplicity", 10, 0, 10);
   h_jetMultiNoPU = new TH1D("jetMultiNoPU", "Jet Multiplicity (No Pileup or lumi weight)", 10, 0, 10);
   h_jetMultiVisTop = new TH1D("jetMultiVisTop", "Jet Multiplicity for Visible Top (No Pileup or lumi Weight)", 10, 0, 10);
   h_HypTTBarMass = new TH1D("HypTTBarMass","Mass of TTbar System (HYP)",240,0,1200);
   h_RecoTTBarMass = new TH1D("RecoTTBarMass","Mass of TTbar System (HYP)",240,0,1200);
   h_GenTTBarMass = new TH1D("GenTTBarMass","Mass of TTbar System(GEN)",240,0,1200);
   h_VisGenTTBarMass = new TH1D("VisGenTTBarMass","Mass of TTbar System(VisGEN)",240,0,1200);

   h_VisGenAll = new TH1D("VisGenAll","All Visible Generated particles (IM)",50,0,400);
   h_GenAll = new TH1D("GenAll","AllGenerated particles (IM)",50,0,400);
   Allh1 = new TH1D("Allh1","DiLepton Mass",50,0,400);
   Zh1 = new TH1D("Zh1","DiLepton Mass in Z Window",50,0,400);
   TTh1 = new TH1D("TTh1","DiLepton Mass out of Z Window",50,0,400);

   h_Lep1pT = new TH1D("Lep1pT","Leading LeptonpT",50,0,400);
   h_Lep1Eta = new TH1D("Lep1Eta","Leading Lepton Eta",50,-5,5);
   h_Lep1E = new TH1D("Lep1E","Leading Lepton Energy",50,0,400);

   h_HypToppT = new TH1D("HypToppT","Top pT",50,0,400);
   h_HypTopEta = new TH1D("HypTopEta","Top pT",50,-5,5);
   h_HypTopE = new TH1D("HypTopE","Top Eneregy",50,0,400);
   h_HypTopMass = new TH1D("HypTopMass","Top Mass",50,0,400);

   h_HypAntiToppT = new TH1D("HypAntiToppT","AntiTop pT",50,0,400);
   h_HypAntiTopEta = new TH1D("HypAntiTopEta","AntiTop pT",50,-5,5);
   h_HypAntiTopE = new TH1D("HypAntiTopE","AntiTop Energy",50,0,400);
   h_HypAntiTopMass = new TH1D("HypAntiTopMass","AntiTop Mass",50,0,400);

   h_HypLeptonpT = new TH1D("HypLeptonpT","Lepton Hypothesis pT",50,0,400);
   h_HypLeptonEta = new TH1D("HypLeptonEta","Lepton Eta",50,-5,5);
   h_HypLeptonE = new TH1D("HypLeptonE","Lepton Energy",50,0,400);

   h_HypAntiLeptonpT = new TH1D("HypAntiLeptonpT","AntiLepton Hypothesis pT",50,0,400);
   h_HypAntiLeptonEta = new TH1D("HypAntiLeptonEta","AntiLepton Hypothesis Eta",50,-5,5);
   h_HypAntiLeptonE = new TH1D("HypAntiLeptonE","AntiLepton Hypothesis Energy",50,0,400);

   h_HypBpT = new TH1D("HypBpT","B Hypothesis pT",50,0,400);
   h_HypBEta = new TH1D("HypBEta","B Eta",50,-5,5);
   h_HypBE = new TH1D("HypBE","B Energy",50,0,400);

   h_HypAntiBpT = new TH1D("HypAntiBpT","AntiB Hypothesis pT",50,0,400);
   h_HypAntiBEta = new TH1D("HypAntiBEta","AntiB Hypothesis Eta",50,-5,5);
   h_HypAntiBE = new TH1D("HypAntiBE","AntiB Hypothesis Energy",50,0,400);

   h_HypNeutrinopT = new TH1D("HypNeutrinopT","Neutrino Hypothesis pT",50,0,400);
   h_HypNeutrinoEta = new TH1D("HypNeutrinoEta","Neutrino Eta",50,-5,5);
   h_HypNeutrinoE = new TH1D("HypNeutrinoE","Neutrino Energy",50,0,400);

   h_HypAntiNeutrinopT = new TH1D("HypAntiNeutrinopT","AntiNeutrino Hypothesis pT",50,0,400);
   h_HypAntiNeutrinoEta = new TH1D("HypAntiNeutrinoEta","AntiNeutrino Hypothesis Eta",50,-5,5);
   h_HypAntiNeutrinoE = new TH1D("HypAntiNeutrinoE","AntiNeutrino Hypothesis Energy",50,0,400);

   h_HypWPluspT = new TH1D("HypWPluspT","WPlus Hypothesis pT",50,0,400);
   h_HypWPlusEta = new TH1D("HypWPlusEta","WPlus Eta",50,-5,5);
   h_HypWPlusE = new TH1D("HypWPlusE","WPlus Energy",50,0,400);

   h_HypWMinuspT = new TH1D("HypWMinuspT","WMinus Hypothesis pT",50,0,400);
   h_HypWMinusEta = new TH1D("HypWMinusEta","WMinus Hypothesis Eta",50,-5,5);
   h_HypWMinusE = new TH1D("HypWMinusE","WMinus Hypothesis Energy",50,0,400);


   h_VisGenToppT = new TH1D("VisGenToppT","Top pT",50,0,400);
   h_VisGenTopEta = new TH1D("VisGenTopEta","Top pT",50,-5,5);
   h_VisGenTopE = new TH1D("VisGenTopE","Top pT",50,0,400);

   h_VisGenAntiToppT = new TH1D("VisGenAntiToppT","AntiTop pT",50,0,400);
   h_VisGenAntiTopEta = new TH1D("VisGenAntiTopEta","AntiTop pT",50,-5,5);
   h_VisGenAntiTopE = new TH1D("VisGenAntiTopE","AntiTop pT",50,0,400);

   h_VisGenLeptonpT = new TH1D("VisGenLeptonpT","Lepton VisGenothesis pT",50,0,400);
   h_VisGenLeptonEta = new TH1D("VisGenLeptonEta","Lepton Eta",50,-5,5);
   h_VisGenLeptonE = new TH1D("VisGenLeptonE","Lepton Energy",50,0,400);

   h_VisGenAntiLeptonpT = new TH1D("VisGenAntiLeptonpT","AntiLepton VisGenothesis pT",50,0,400);
   h_VisGenAntiLeptonEta = new TH1D("VisGenAntiLeptonEta","AntiLepton VisGenothesis Eta",50,-5,5);
   h_VisGenAntiLeptonE = new TH1D("VisGenAntiLeptonE","AntiLepton VisGenothesis Energy",50,0,400);

   h_VisGenBpT = new TH1D("VisGenBpT","B VisGenothesis pT",50,0,400);
   h_VisGenBEta = new TH1D("VisGenBEta","B Eta",50,-5,5);
   h_VisGenBE = new TH1D("VisGenBE","B Energy",50,0,400);

   h_VisGenAntiBpT = new TH1D("VisGenAntiBpT","AntiB VisGenothesis pT",50,0,400);
   h_VisGenAntiBEta = new TH1D("VisGenAntiBEta","AntiB VisGenothesis Eta",50,-5,5);
   h_VisGenAntiBE = new TH1D("VisGenAntiBE","AntiB VisGenothesis Energy",50,0,400);

   h_VisGenNeutrinopT = new TH1D("VisGenNeutrinopT","Neutrino VisGenothesis pT",50,0,400);
   h_VisGenNeutrinoEta = new TH1D("VisGenNeutrinoEta","Neutrino Eta",50,-5,5);
   h_VisGenNeutrinoE = new TH1D("VisGenNeutrinoE","Neutrino Energy",50,0,400);

   h_VisGenAntiNeutrinopT = new TH1D("VisGenAntiNeutrinopT","AntiNeutrino VisGenothesis pT",50,0,400);
   h_VisGenAntiNeutrinoEta = new TH1D("VisGenAntiNeutrinoEta","AntiNeutrino VisGenothesis Eta",50,-5,5);
   h_VisGenAntiNeutrinoE = new TH1D("VisGenAntiNeutrinoE","AntiNeutrino VisGenothesis Energy",50,0,400);

   h_VisGenWPluspT = new TH1D("VisGenWPluspT","WPlus VisGenothesis pT",50,0,400);
   h_VisGenWPlusEta = new TH1D("VisGenWPlusEta","WPlus Eta",50,-5,5);
   h_VisGenWPlusE = new TH1D("VisGenWPlusE","WPlus Energy",50,0,400);

   h_VisGenWMinuspT = new TH1D("VisGenWMinuspT","WMinus VisGenothesis pT",50,0,400);
   h_VisGenWMinusEta = new TH1D("VisGenWMinusEta","WMinus VisGenothesis Eta",50,-5,5);
   h_VisGenWMinusE = new TH1D("VisGenWMinusE","WMinus VisGenothesis Energy",50,0,400);

   h_GenToppT = new TH1D("GenToppT","Top pT",50,0,400);
   h_GenTopEta = new TH1D("GenTopEta","Top pT",50,-5,5);
   h_GenTopE = new TH1D("GenTopE","Top pT",50,0,400);

   h_GenAntiToppT = new TH1D("GenAntiToppT","AntiTop pT",50,0,400);
   h_GenAntiTopEta = new TH1D("GenAntiTopEta","AntiTop pT",50,-5,5);
   h_GenAntiTopE = new TH1D("GenAntiTopE","AntiTop pT",50,0,400);

   h_GenLeptonpT = new TH1D("GenLeptonpT","Lepton Genothesis pT",50,0,400);
   h_GenLeptonEta = new TH1D("GenLeptonEta","Lepton Eta",50,-5,5);
   h_GenLeptonE = new TH1D("GenLeptonE","Lepton Energy",50,0,400);

   h_GenAntiLeptonpT = new TH1D("GenAntiLeptonpT","AntiLepton Genothesis pT",50,0,400);
   h_GenAntiLeptonEta = new TH1D("GenAntiLeptonEta","AntiLepton Genothesis Eta",50,-5,5);
   h_GenAntiLeptonE = new TH1D("GenAntiLeptonE","AntiLepton Genothesis Energy",50,0,400);

   h_GenBpT = new TH1D("GenBpT","B Genothesis pT",50,0,400);
   h_GenBEta = new TH1D("GenBEta","B Eta",50,-5,5);
   h_GenBE = new TH1D("GenBE","B Energy",50,0,400);

   h_GenAntiBpT = new TH1D("GenAntiBpT","AntiB Genothesis pT",50,0,400);
   h_GenAntiBEta = new TH1D("GenAntiBEta","AntiB Genothesis Eta",50,-5,5);
   h_GenAntiBE = new TH1D("GenAntiBE","AntiB Genothesis Energy",50,0,400);

   h_GenNeutrinopT = new TH1D("GenNeutrinopT","Neutrino Genothesis pT",50,0,400);
   h_GenNeutrinoEta = new TH1D("GenNeutrinoEta","Neutrino Eta",50,-5,5);
   h_GenNeutrinoE = new TH1D("GenNeutrinoE","Neutrino Energy",50,0,400);

   h_GenAntiNeutrinopT = new TH1D("GenAntiNeutrinopT","AntiNeutrino Genothesis pT",50,0,400);
   h_GenAntiNeutrinoEta = new TH1D("GenAntiNeutrinoEta","AntiNeutrino Genothesis Eta",50,-5,5);
   h_GenAntiNeutrinoE = new TH1D("GenAntiNeutrinoE","AntiNeutrino Genothesis Energy",50,0,400);

   h_GenWPluspT = new TH1D("GenWPluspT","WPlus Genothesis pT",50,0,400);
   h_GenWPlusEta = new TH1D("GenWPlusEta","WPlus Eta",50,-5,5);
   h_GenWPlusE = new TH1D("GenWPlusE","WPlus Energy",50,0,400);

   h_GenWMinuspT = new TH1D("GenWMinuspT","WMinus Genothesis pT",50,0,400);
   h_GenWMinusEta = new TH1D("GenWMinusEta","WMinus Genothesis Eta",50,-5,5);
   h_GenWMinusE = new TH1D("GenWMinusE","WMinus Genothesis Energy",50,0,400);
   //   h1 = new TH1D("h1","h1",60,-3,3);
   //h1 = new TH1D("h1","h1",100,0,400);

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
  if(MCSample->find("ttbarsignal")!=string::npos){ Analysis::GetSignalBranches(entry);}

  weightLepSF = 1.0; //needs to be filled properly in Ntuple. Okay for now
  float dimass=100;
  std::vector<float> VLepton;

  std::vector<TLorentzVector> LVlepton;
  std::vector<TLorentzVector> LVjet;

  std::vector<TLorentzVector> LVHypTop;
  std::vector<TLorentzVector> LVHypAntiTop;
  std::vector<TLorentzVector> LVHypNeutrino;
  std::vector<TLorentzVector> LVHypAntiNeutrino;
  std::vector<TLorentzVector> LVHypB;
  std::vector<TLorentzVector> LVHypAntiB;
  std::vector<TLorentzVector> LVHypLepton;
  std::vector<TLorentzVector> LVHypAntiLepton;
  std::vector<TLorentzVector> LVHypWPlus;
  std::vector<TLorentzVector> LVHypWMinus;

  for(int i=0; i<HypTop_;i++){ 
    TLorentzVector antitoptemp(HypAntiToppX[i], HypAntiToppY[i], HypAntiToppZ[i], HypAntiTopE[i]);
    LVHypAntiTop.push_back(antitoptemp);
    TLorentzVector toptemp(HypToppX[i], HypToppY[i], HypToppZ[i], HypTopE[i]);
    LVHypTop.push_back(toptemp);
    TLorentzVector antineutrinotemp(HypAntiNeutrinopX[i], HypAntiNeutrinopY[i], HypAntiNeutrinopZ[i], HypAntiNeutrinoE[i]);
    LVHypAntiNeutrino.push_back(antineutrinotemp);
    TLorentzVector neutrinotemp(HypNeutrinopX[i], HypNeutrinopY[i], HypNeutrinopZ[i], HypNeutrinoE[i]);
    LVHypNeutrino.push_back(neutrinotemp);
    TLorentzVector antibtemp(HypAntiBpX[i], HypAntiBpY[i], HypAntiBpZ[i], HypAntiBE[i]);
    LVHypAntiB.push_back(antibtemp);
    TLorentzVector btemp(HypBpX[i], HypBpY[i], HypBpZ[i], HypBE[i]);
    LVHypB.push_back(btemp);
    TLorentzVector antileptontemp(HypAntiLeptonpX[i], HypAntiLeptonpY[i], HypAntiLeptonpZ[i], HypAntiLeptonE[i]);
    LVHypAntiLepton.push_back(antileptontemp);
    TLorentzVector leptontemp(HypLeptonpX[i], HypLeptonpY[i], HypLeptonpZ[i], HypLeptonE[i]);
    LVHypLepton.push_back(leptontemp);
    TLorentzVector wplustemp(HypWPluspX[i], HypWPluspY[i], HypWPluspZ[i], HypWPlusE[i]);
    LVHypWPlus.push_back(wplustemp);
    TLorentzVector wminustemp(HypWMinuspX[i], HypWMinuspY[i], HypWMinuspZ[i], HypWMinusE[i]);
    LVHypWMinus.push_back(wminustemp);
 }


  TLorentzVector LVGenAntiTop(GenAntiToppX, GenAntiToppY, GenAntiToppZ, GenAntiTopE);
  TLorentzVector LVGenTop(GenToppX, GenToppY, GenToppZ, GenTopE);    
  TLorentzVector LVGenAntiNeutrino(GenAntiNeutrinopX, GenAntiNeutrinopY, GenAntiNeutrinopZ, GenAntiNeutrinoE);    
  TLorentzVector LVGenNeutrino(GenNeutrinopX, GenNeutrinopY, GenNeutrinopZ, GenNeutrinoE);    
  TLorentzVector LVGenAntiB(GenAntiBpX, GenAntiBpY, GenAntiBpZ, GenAntiBE);    
  TLorentzVector LVGenB(GenBpX, GenBpY, GenBpZ, GenBE);    
  TLorentzVector LVGenAntiLepton(GenAntiLeptonpX, GenAntiLeptonpY, GenAntiLeptonpZ, GenAntiLeptonE);    
  TLorentzVector LVGenLepton(GenLeptonpX, GenLeptonpY, GenLeptonpZ, GenLeptonE);    
  TLorentzVector LVGenWPlus(GenWPluspX, GenWPluspY, GenWPluspZ, GenWPlusE);
  TLorentzVector LVGenWMinus(GenWMinuspX, GenWMinuspY, GenWMinuspZ, GenWMinusE);
  for(int i=0; i<lepton_;i++){
    TLorentzVector leptemp(leptonpX[i], leptonpY[i], leptonpZ[i], leptonE[i]);
    LVlepton.push_back(leptemp);
  }
  
  for(int i=0; i<jet_;i++){
    TLorentzVector jettemp(jetpX[i], jetpY[i], jetpZ[i], jetE[i]);
    LVlepton.push_back(jettemp);
  }
 double BtagWP = 1.7; 
  int NJets =0;
  vector<int> BJetIndex;
  for(vector<double>::iterator it = jetBTagTCHE->begin(); it<jetBTagTCHE->end(); it++){
    if(*it > 0)NJets++;
    if(*it > BtagWP){
      BJetIndex.push_back(*it);
    }    
  }
  
  //  BtagWP = 0;
  //Should we just look for two Bjets above 1.7 or the two highest bjets?:: Make this a function
  int solutionIndex = 0;
  bool oneTag = false;
  for(int i =0; i<HypTop_; i++){
    if((*jetBTagTCHE)[(*HypJet0index)[i]] > BtagWP && (*jetBTagTCHE)[(*HypJet1index)[i]]>BtagWP){
      solutionIndex = i; 
      break;
    }
    if(oneTag == false && ((*jetBTagTCHE)[(*HypJet0index)[i]] > BtagWP || (*jetBTagTCHE)[(*HypJet1index)[i]]>BtagWP)){solutionIndex = i; oneTag=true;}

  }  

  //  if(HypTop_){
  // cout<<"SolutionIndex: "<<solutionIndex<<endl;
  // cout<< "BJetTCHE[HypJet0index[solutionIndex]]: "<<(*jetBTagTCHE)[(*HypJet0index)[solutionIndex]]<<endl;
  // cout<< "BJetTCHE[HypJet1index[solutionIndex]]: "<<(*jetBTagTCHE)[(*HypJet1index)[solutionIndex]]<<endl<<endl;
  //}
  
  if(MCSample->find("ttbarsignal")!=string::npos){  
    h_GenAll->Fill(LVGenTop.M(),1);
    if (LVGenLepton.Pt()>20 && LVGenAntiLepton.Pt()>20 && abs(LVGenLepton.Eta())<2.4 && abs(LVGenAntiLepton.Eta())<2.4){
      if (LVGenB.Pt()>30 && LVGenAntiB.Pt()>30 && abs(LVGenB.Eta())<2.4 && abs(LVGenAntiB.Eta())<2.4){
	
	h_VisGenAll->Fill(LVGenTop.M(),1); 
        double VisGenTTBarMass = (LVGenTop+ LVGenAntiTop).M();
	h_VisGenTTBarMass->Fill(VisGenTTBarMass,1);
	h_VisGenToppT->Fill(LVGenTop.Pt(),weightLepSF*btagSF*trigEFF);
	h_VisGenAntiToppT->Fill(LVGenAntiTop.Pt(),weightLepSF*btagSF*trigEFF);
	h_VisGenWMinuspT->Fill(LVGenWMinus.Pt(),weightLepSF*btagSF*trigEFF);
	h_VisGenWPluspT->Fill(LVGenWPlus.Pt(),weightLepSF*btagSF*trigEFF);
	h_VisGenBpT->Fill(LVGenB.Pt(),weightLepSF*btagSF*trigEFF);
	h_VisGenAntiBpT->Fill(LVGenAntiB.Pt(),weightLepSF*btagSF*trigEFF);
	h_VisGenLeptonpT->Fill(LVGenLepton.Pt(),weightLepSF*btagSF*trigEFF);
	h_VisGenAntiLeptonpT->Fill(LVGenAntiLepton.Pt(),weightLepSF*btagSF*trigEFF);
	h_VisGenNeutrinopT->Fill(LVGenNeutrino.Pt(),weightLepSF*btagSF*trigEFF);
	h_VisGenAntiNeutrinopT->Fill(LVGenAntiNeutrino.Pt(),weightLepSF*btagSF*trigEFF);
	
	h_VisGenTopEta->Fill(LVGenTop.Eta(),weightLepSF*btagSF*trigEFF);
	h_VisGenAntiTopEta->Fill(LVGenAntiTop.Eta(),weightLepSF*btagSF*trigEFF);
	h_VisGenWMinusEta->Fill(LVGenWMinus.Eta(),weightLepSF*btagSF*trigEFF);
	h_VisGenWPlusEta->Fill(LVGenWPlus.Eta(),weightLepSF*btagSF*trigEFF);
	h_VisGenBEta->Fill(LVGenB.Eta(),weightLepSF*btagSF*trigEFF);
	h_VisGenAntiBEta->Fill(LVGenAntiB.Eta(),weightLepSF*btagSF*trigEFF);
	h_VisGenLeptonEta->Fill(LVGenLepton.Eta(),weightLepSF*btagSF*trigEFF);
	h_VisGenAntiLeptonEta->Fill(LVGenAntiLepton.Eta(),weightLepSF*btagSF*trigEFF);
	h_VisGenNeutrinoEta->Fill(LVGenNeutrino.Eta(),weightLepSF*btagSF*trigEFF);
	h_VisGenAntiNeutrinoEta->Fill(LVGenAntiNeutrino.Eta(),weightLepSF*btagSF*trigEFF);
	
	h_VisGenTopE->Fill(LVGenTop.E(),weightLepSF*btagSF*trigEFF);
	h_VisGenAntiTopE->Fill(LVGenAntiTop.E(),weightLepSF*btagSF*trigEFF);
	h_VisGenWMinusE->Fill(LVGenWMinus.E(),weightLepSF*btagSF*trigEFF);
	h_VisGenWPlusE->Fill(LVGenWPlus.E(),weightLepSF*btagSF*trigEFF);
	h_VisGenBE->Fill(LVGenB.E(),weightLepSF*btagSF*trigEFF);
	h_VisGenAntiBE->Fill(LVGenAntiB.E(),weightLepSF*btagSF*trigEFF);
	h_VisGenLeptonE->Fill(LVGenLepton.E(),weightLepSF*btagSF*trigEFF);
	h_VisGenAntiLeptonE->Fill(LVGenAntiLepton.E(),weightLepSF*btagSF*trigEFF);
	h_VisGenNeutrinoE->Fill(LVGenNeutrino.E(),weightLepSF*btagSF*trigEFF);
	h_VisGenAntiNeutrinoE->Fill(LVGenAntiNeutrino.E(),weightLepSF*btagSF*trigEFF);
      }    
    }
  }//for visible top events	  

  if(lepton_>1){  //two isolated leptons create dimass out of highest pt pair
    dimass = (LVlepton[0]+LVlepton[1]).M();
    
    //    if(*(metEt->begin()) > 30 && dimass>12 && jet_>1){//Analysis step 6
    //if(*(metEt->begin()) > 30 && dimass>12 && jet_>1 && BJetIndex.size()>0){//Analysis step 8?
    if(*(metEt->begin()) > 30 && dimass>12 && jet_>1 && BJetIndex.size()>0 && HypTop_){//Analysis step 9?
      Allh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
      if (dimass < 106 && dimass > 76 ){
      	Zh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
      }else{
	h_jetMulti->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	h_jetMultiNoPU->Fill(jet_,weightLepSF*btagSF*trigEFF);
      	TTh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	if(MCSample->find("ttbarsignal")!=string::npos){

	  if (LVGenLepton.Pt()>20 && LVGenAntiLepton.Pt()>20 && abs(LVGenLepton.Eta())<2.4 && abs(LVGenAntiLepton.Eta())<2.4){
	    if (LVGenB.Pt()>30 && LVGenAntiB.Pt()>30 && abs(LVGenB.Eta())<2.4 && abs(LVGenAntiB.Eta())<2.4){
	      h_jetMultiVisTop->Fill(jet_,weightLepSF*btagSF*trigEFF); 
	    }
	  }//for visible top events
	  
	  double GenTTBarMass = (LVGenTop+ LVGenAntiTop).M();
	  h_GenTTBarMass->Fill(GenTTBarMass,1);
	  h_GenToppT->Fill(LVGenTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenAntiToppT->Fill(LVGenAntiTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenWMinuspT->Fill(LVGenWMinus.Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenWPluspT->Fill(LVGenWPlus.Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenBpT->Fill(LVGenB.Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenAntiBpT->Fill(LVGenAntiB.Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenLeptonpT->Fill(LVGenLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenAntiLeptonpT->Fill(LVGenAntiLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenNeutrinopT->Fill(LVGenNeutrino.Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenAntiNeutrinopT->Fill(LVGenAntiNeutrino.Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  
	  h_GenTopEta->Fill(LVGenTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenAntiTopEta->Fill(LVGenAntiTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenWMinusEta->Fill(LVGenWMinus.Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenWPlusEta->Fill(LVGenWPlus.Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenBEta->Fill(LVGenB.Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenAntiBEta->Fill(LVGenAntiB.Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenLeptonEta->Fill(LVGenLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenAntiLeptonEta->Fill(LVGenAntiLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenNeutrinoEta->Fill(LVGenNeutrino.Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenAntiNeutrinoEta->Fill(LVGenAntiNeutrino.Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);

	  h_GenTopE->Fill(LVGenTop.E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenAntiTopE->Fill(LVGenAntiTop.E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenWMinusE->Fill(LVGenWMinus.E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenWPlusE->Fill(LVGenWPlus.E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenBE->Fill(LVGenB.E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenAntiBE->Fill(LVGenAntiB.E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenLeptonE->Fill(LVGenLepton.E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenAntiLeptonE->Fill(LVGenAntiLepton.E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenNeutrinoE->Fill(LVGenNeutrino.E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_GenAntiNeutrinoE->Fill(LVGenAntiNeutrino.E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	}
	   
	if(HypTop_){
	  //	  cout<<"SolutionIndex: "<<solutionIndex<<endl;
	  //cout<< "BJetTCHE[HypJet0index[solutionIndex]]: "<<(*jetBTagTCHE)[(*HypJet0index)[solutionIndex]]<<endl;
	  //cout<< "BJetTCHE[HypJet1index[solutionIndex]]: "<<(*jetBTagTCHE)[(*HypJet1index)[solutionIndex]]<<endl<<endl;
	  double HypTTBarMass = (LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).M();
	  h_RecoTTBarMass->Fill(HypTTBarMass,1);
	  h_HypTTBarMass->Fill(HypTTBarMass,weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypTopMass->Fill(LVHypTop[solutionIndex].M(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiTopMass->Fill(LVHypAntiTop[solutionIndex].M(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypToppT->Fill(LVHypTop[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypWMinuspT->Fill(LVHypWMinus[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypWPluspT->Fill(LVHypWPlus[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypBpT->Fill(LVHypB[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiBpT->Fill(LVHypAntiB[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypNeutrinopT->Fill(LVHypNeutrino[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiNeutrinopT->Fill(LVHypAntiNeutrino[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  
	  h_HypTopEta->Fill(LVHypTop[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiTopEta->Fill(LVHypAntiTop[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypWMinusEta->Fill(LVHypWMinus[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypWPlusEta->Fill(LVHypWPlus[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypBEta->Fill(LVHypB[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiBEta->Fill(LVHypAntiB[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypNeutrinoEta->Fill(LVHypNeutrino[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiNeutrinoEta->Fill(LVHypAntiNeutrino[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	     
	  h_HypTopE->Fill(LVHypTop[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiTopE->Fill(LVHypAntiTop[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypWMinusE->Fill(LVHypWMinus[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypWPlusE->Fill(LVHypWPlus[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypBE->Fill(LVHypB[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiBE->Fill(LVHypAntiB[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypLeptonE->Fill(LVHypLepton[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiLeptonE->Fill(LVHypAntiLepton[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypNeutrinoE->Fill(LVHypNeutrino[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
	  h_HypAntiNeutrinoE->Fill(LVHypAntiNeutrino[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSF*trigEFF);
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


  string f_savename = "selectionRoot/";
  gSystem->MakeDirectory(f_savename.c_str());
  f_savename.append(*channel); 
  gSystem->MakeDirectory(f_savename.c_str());
  f_savename.append("/");
  f_savename.append(*MCSample);
  f_savename.append(".root");
  

  std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!Finishing: "<<*MCSample<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl<<std:: endl;

  TFile *f = new TFile(f_savename.c_str(),"RECREATE");

  //AllDIM.write();
  //InDIM.writeone();
  //OutDIM.writeone();

  Allh1->Write();
  h_GenAll->Write();
  h_VisGenAll->Write();
  h_jetMulti->Write();
  h_jetMultiNoPU->Write();
  Zh1->Write();
  TTh1->Write();
  h_HypTTBarMass->Write();
  h_GenTTBarMass->Write();
  h_RecoTTBarMass->Write();
  h_VisGenTTBarMass->Write();

  h_VisGenNeutrinopT->Write();
  h_VisGenAntiNeutrinopT->Write();
  h_VisGenNeutrinoEta->Write();
  h_VisGenAntiNeutrinoEta->Write();
  h_VisGenNeutrinoE->Write();
  h_VisGenAntiNeutrinoE->Write();

  h_VisGenBpT->Write();
  h_VisGenAntiBpT->Write();
  h_VisGenBEta->Write();
  h_VisGenAntiBEta->Write();
  h_VisGenBE->Write();
  h_VisGenAntiBE->Write();

  h_VisGenLeptonpT->Write();
  h_VisGenAntiLeptonpT->Write();
  h_VisGenLeptonEta->Write();
  h_VisGenAntiLeptonEta->Write();
  h_VisGenLeptonE->Write();
  h_VisGenAntiLeptonE->Write();

  h_VisGenWPluspT->Write();
  h_VisGenWMinuspT->Write();
  h_VisGenWPlusEta->Write();
  h_VisGenWMinusEta->Write();
  h_VisGenWPlusE->Write();
  h_VisGenWMinusE->Write();

  h_VisGenToppT->Write();
  h_VisGenAntiToppT->Write();
  h_VisGenTopEta->Write();
  h_VisGenAntiTopEta->Write();
  h_VisGenTopE->Write();
  h_VisGenAntiTopE->Write();

  h_GenNeutrinopT->Write();
  h_GenAntiNeutrinopT->Write();
  h_GenNeutrinoEta->Write();
  h_GenAntiNeutrinoEta->Write();
  h_GenNeutrinoE->Write();
  h_GenAntiNeutrinoE->Write();

  h_GenBpT->Write();
  h_GenAntiBpT->Write();
  h_GenBEta->Write();
  h_GenAntiBEta->Write();
  h_GenBE->Write();
  h_GenAntiBE->Write();

  h_GenLeptonpT->Write();
  h_GenAntiLeptonpT->Write();
  h_GenLeptonEta->Write();
  h_GenAntiLeptonEta->Write();
  h_GenLeptonE->Write();
  h_GenAntiLeptonE->Write();

  h_GenWPluspT->Write();
  h_GenWMinuspT->Write();
  h_GenWPlusEta->Write();
  h_GenWMinusEta->Write();
  h_GenWPlusE->Write();
  h_GenWMinusE->Write();

  h_GenToppT->Write();
  h_GenAntiToppT->Write();
  h_GenTopEta->Write();
  h_GenAntiTopEta->Write();
  h_GenTopE->Write();
  h_GenAntiTopE->Write();

  h_HypNeutrinopT->Write();
  h_HypAntiNeutrinopT->Write();
  h_HypNeutrinoEta->Write();
  h_HypAntiNeutrinoEta->Write();
  h_HypNeutrinoE->Write();
  h_HypAntiNeutrinoE->Write();

  h_HypBpT->Write();
  h_HypAntiBpT->Write();
  h_HypBEta->Write();
  h_HypAntiBEta->Write();
  h_HypBE->Write();
  h_HypAntiBE->Write();

  h_HypLeptonpT->Write();
  h_HypAntiLeptonpT->Write();
  h_HypLeptonEta->Write();
  h_HypAntiLeptonEta->Write();
  h_HypLeptonE->Write();
  h_HypAntiLeptonE->Write();

  h_HypWPluspT->Write();
  h_HypWMinuspT->Write();
  h_HypWPlusEta->Write();
  h_HypWMinusEta->Write();
  h_HypWPlusE->Write();
  h_HypWMinusE->Write();

  h_HypTopMass->Write();
  h_HypAntiTopMass->Write();
  h_HypToppT->Write();
  h_HypAntiToppT->Write();
  h_HypTopEta->Write();
  h_HypAntiTopEta->Write();
  h_HypTopE->Write();
  h_HypAntiTopE->Write();

  f->Close();
}
