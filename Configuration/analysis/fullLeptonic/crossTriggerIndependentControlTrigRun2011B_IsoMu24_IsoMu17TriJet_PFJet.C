// This macro calculates the efficiency of the hadronic part of a lepton-hadron cross-trigger,
// e.g. of the TriCentralJet30 part wrt Mu17 for the HLT_Mu17_TriCentralJet30 trigger

#include <iostream>
#include "TH1.h"
#include "TF1.h"
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TMath.h"

void crossTriggerIndependentControlTrigRun2011B_IsoMu24_IsoMu17TriJet_PFJet(bool save=false)
{
  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetPadBottomMargin(0.11);
  gStyle->SetLabelSize(0.05,"XY");
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetFillColor(0);
  /// path where output files are stored
  TString outputFolder   = "/afs/desy.de/user/j/jlange/analysis/tagAndProbe/plots/2011/MuHad/PF2PAT/IsoMu24_IsoMu17_TriJetPFJet";
  TString outputFileName = "/triggerEffIndpendentControl_IsoMu24_IsoMu17_TriJetPFJet";
  
  char inputPath42[]="/afs/naf.desy.de/user/j/jlange/nafscratch/top/CMSSW_4_2_4/src/TopAnalysis/Configuration/analysis/fullLeptonic";
 
  /// if set to 0: all plots (probe, test, eff) are drawn; to 1: only eff plots
  int onlyEffPlots =1;

  /// definition of methods (e.g. Tag and Probe MC tapMC, tapData, ...
  const int methodNum=2;
  //TString methods[methodNum]={"tapMC"};
  TString methods[100]={ "IsoMu17TriJet30", "IsoMu17TriPFJet30", "2011AReRecoV1 IsoEle27_Ele25TriJet", "2011APromptRecoV4 SingleMu_Ele25TriJet", "2011APromptRecoV4 SingleMu_IsoEle25TriJet","2011AReRecoV1 SingleMu_Ele25TriJet NoVetoes", "Summer11 ttbar IsoEle27_Ele25TriJet","2011ReRecoV1 IsoEle27_Ele25TriJet", "2011AReRecoV4 Mu15", "2011PromptV4 Mu15",  "2011APromptV1+2 Mu15", "2011A IsoMu17 MinJet4", "Spring11 MC Mu9", "2011A Mu15", "2011A Mu17emu", "2011A Mu20","2011A IsoMu17","Z genMu match Mu9"};
  TFile* files[100];

  //files[0]=new TFile(Form("%s/naf_analyzeCrossTriggerRatiosRun2011BPromptReco3e33_IsoMu24_IsoMu17TriJet_MinJet3_cfg/analyzeCrossTriggerRatiosRun2011BPromptReco5e33_IsoMu24_IsoMu17TriJet_MinJet3.root",inputPath42));
  //files[1]=new TFile(Form("%s/naf_analyzeCrossTriggerRatiosRun2011BPromptReco5e33_IsoMu24_IsoMu17TriPFJet_MinJet3_cfg/analyzeCrossTriggerRatiosRun2011BPromptReco5e33_IsoMu24_IsoMu17TriPFJet_MinJet3.root",inputPath42));
  files[0]=new TFile(Form("%s/naf_analyzeCrossTriggerRatiosRun2011BPromptReco3e33_IsoMu24_IsoMu17TriJet_MinJet0_cfg/analyzeCrossTriggerRatiosRun2011BPromptReco3e33_IsoMu24_IsoMu17TriJet_MinJet0.root",inputPath42));
  files[1]=new TFile(Form("%s/naf_analyzeCrossTriggerRatiosRun2011BPromptReco5e33_IsoMu24_IsoMu17TriPFJet_MinJet0_cfg/analyzeCrossTriggerRatiosRun2011BPromptReco5e33_IsoMu24_IsoMu17TriPFJet_MinJet0.root",inputPath42));

  
  // eff. is multiplied with scale factor
//   double SF[100]={0.};
//   SF[0]=1.;
//   SF[1]=1.;


  /// different tap studies (different efficiencies)
  const int folderNum=2;
  //TString folders[]={"analyzeJet2Trig1AfterCut", "analyzeJet2Trig2AfterCut"};
  TString foldersJet[]={"analyzeJet2Trig1AfterCut", "analyzeJet2Trig2AfterCut"};
  TString foldersJetDiffMult[]={"analyzeJetDiffMultTrig1AfterCut", "analyzeJetDiffMultTrig2AfterCut"};
  TString foldersLeptonKinematics[]={"analyzeMuonKinematicsTrig1", "analyzeMuonKinematicsTrig2"};
  TString foldersLeptonQuality[]={"analyzeMuonQualityTrig1", "analyzeMuonQualityTrig2"};
 
  TH1F* nControl [methodNum][folderNum];
  TH1F* nNjets   [methodNum][folderNum];
  TH1F* nJetPt      [methodNum][folderNum];
  TH1F* nJetEta     [methodNum][folderNum];
  TH1F* nLeptonPt      [methodNum][folderNum];
  TH1F* nLeptonEta     [methodNum][folderNum];
  TH1F* nLeptonRelIso  [methodNum][folderNum];
  TH1F* nJet1PtMult1      [methodNum][folderNum];
//  TH1F* nJet1EtaMult1     [methodNum][folderNum];
  TH1F* nJet2PtMult2      [methodNum][folderNum];
//  TH1F* nJet2EtaMult2     [methodNum][folderNum];
  TH1F* nJet3PtMult3      [methodNum][folderNum];
  TH1F* nJet3EtaMult3     [methodNum][folderNum];
  TH1F* nJet4PtMult4      [methodNum][folderNum];
//  TH1F* nJet4EtaMult4     [methodNum][folderNum];
  TH1F* nJet5PtMult5      [methodNum][folderNum];
//  TH1F* nJet5EtaMult5     [methodNum][folderNum];
  TH1F* nJet6PtMult6Incl  [methodNum][folderNum];
//  TH1F* nJet6EtaMult6Incl [methodNum][folderNum];
  TH1F* effControl [methodNum];
  TH1F* effNjets   [methodNum];
  TH1F* effJetPt      [methodNum];
  TH1F* effJetEta     [methodNum];
  TH1F* effLeptonPt      [methodNum];
  TH1F* effLeptonEta     [methodNum];
  TH1F* effLeptonRelIso  [methodNum];
  TH1F* effJet1PtMult1      [methodNum];
//  TH1F* effJet1EtaMult1     [methodNum];
  TH1F* effJet2PtMult2      [methodNum];
//  TH1F* effJet2EtaMult2     [methodNum];
  TH1F* effJet3PtMult3      [methodNum];
  TH1F* effJet3EtaMult3     [methodNum];
  TH1F* effJet4PtMult4      [methodNum];
//  TH1F* effJet4EtaMult4     [methodNum];
  TH1F* effJet5PtMult5      [methodNum];
//  TH1F* effJet5EtaMult5     [methodNum];
  TH1F* effJet6PtMult6Incl  [methodNum];
//  TH1F* effJet6EtaMult6Incl [methodNum];

for(int iMethod=0; iMethod<methodNum; iMethod++){
 for(int iFolder=0; iFolder<folderNum; iFolder++) {
   /// jet histos
   std::cout<<"Hallo :" << iMethod << std::endl;
   nNjets  [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersJet[iFolder]+"/n")->Clone();
   nNjets  [iMethod][iFolder]->Sumw2();
   std::cout<<"Hallo 2: " << iMethod << std::endl;
   nJetPt [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersJet[iFolder]+"/pt")->Clone();
   nJetPt  [iMethod][iFolder]->Sumw2();
   nJet1PtMult1 [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersJetDiffMult[iFolder]+"/pt1")->Clone();
   nJet1PtMult1  [iMethod][iFolder]->Sumw2();
   nJet2PtMult2 [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersJetDiffMult[iFolder]+"/pt2")->Clone();
   nJet2PtMult2  [iMethod][iFolder]->Sumw2();
   nJet3PtMult3 [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersJetDiffMult[iFolder]+"/pt3")->Clone();
   nJet3PtMult3  [iMethod][iFolder]->Sumw2();
   nJet4PtMult4 [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersJetDiffMult[iFolder]+"/pt4")->Clone();
   nJet4PtMult4  [iMethod][iFolder]->Sumw2();
   nJet5PtMult5 [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersJetDiffMult[iFolder]+"/pt5")->Clone();
   nJet5PtMult5  [iMethod][iFolder]->Sumw2();
   nJet6PtMult6Incl [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersJetDiffMult[iFolder]+"/pt6Incl")->Clone();
   nJet6PtMult6Incl  [iMethod][iFolder]->Sumw2();
   nJetEta[iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersJet[iFolder]+"/eta")->Clone();
   nJet3EtaMult3 [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersJetDiffMult[iFolder]+"/eta3")->Clone();
   nJet3EtaMult3  [iMethod][iFolder]->Sumw2();
   //change the binning
   double newBins[] = {-3.5,-2.4,-1.8,-1.2,-0.6,0.,0.6,1.2,1.8,2.4,3.5};
   nJetEta  [iMethod][iFolder] = (TH1F*) nJetEta  [iMethod][iFolder]->
       Rebin(10,Form("%s_new",nJetEta[iMethod][iFolder]->GetName()),newBins);
   nJet3EtaMult3  [iMethod][iFolder] = (TH1F*) nJet3EtaMult3  [iMethod][iFolder]->
       Rebin(10,Form("%s_new",nJet3EtaMult3[iMethod][iFolder]->GetName()),newBins);
   nJetEta  [iMethod][iFolder]->Sumw2();
   
   /// lepton kin. + Qual. histos
   nLeptonPt [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersLeptonKinematics[iFolder]+"/pt")->Clone();
   nLeptonPt  [iMethod][iFolder]->Sumw2();
   nLeptonEta [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersLeptonKinematics[iFolder]+"/eta")->Clone();
   nLeptonEta  [iMethod][iFolder]->Sumw2();
   nLeptonRelIso [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(foldersLeptonQuality[iFolder]+"/relIso")->Clone();
   nLeptonRelIso  [iMethod][iFolder]->Sumw2();
   
   nControl[iMethod][iFolder] = new TH1F ("control"+methods[iMethod]+foldersJet[iFolder],"control", 1,0,2 );
   nControl[iMethod][iFolder]->Sumw2();
   for(int i=0; i<nJetPt [iMethod][iFolder]->GetEntries(); i++) nControl[iMethod][iFolder]->Fill(1);
 }
 
//  nNjets    [iMethod][0]->Scale(1/SF[iMethod]);
//  nJetPt    [iMethod][0]->Scale(1/SF[iMethod]);
//  nJetEta   [iMethod][0]->Scale(1/SF[iMethod]);
//  nControl   [iMethod][0]->Scale(1/SF[iMethod]);
//  nLeptonPt    [iMethod][0]->Scale(1/SF[iMethod]);
//  nLeptonEta   [iMethod][0]->Scale(1/SF[iMethod]);
//  nLeptonRelIso   [iMethod][0]->Scale(1/SF[iMethod]);
 
 nNjets    [iMethod][0]->Sumw2();
 nJetPt    [iMethod][0]->Sumw2();
 nJet1PtMult1    [iMethod][0]->Sumw2();
 nJet2PtMult2    [iMethod][0]->Sumw2();
 nJet3PtMult3    [iMethod][0]->Sumw2();
 nJet4PtMult4    [iMethod][0]->Sumw2();
 nJet5PtMult5    [iMethod][0]->Sumw2();
 nJet6PtMult6Incl[iMethod][0]->Sumw2();
 nJetEta   [iMethod][0]->Sumw2();
 nControl   [iMethod][0]->Sumw2();
 nLeptonPt    [iMethod][0]->Sumw2();
 nLeptonEta   [iMethod][0]->Sumw2();
 nJet3EtaMult3    [iMethod][0]->Sumw2();
 nLeptonRelIso   [iMethod][0]->Sumw2();
 
   effNjets[iMethod] = (TH1F*) nNjets [iMethod][0]->Clone();
   effJetPt[iMethod]    = (TH1F*) nJetPt    [iMethod][0]->Clone();
   effJet1PtMult1[iMethod]    = (TH1F*) nJet1PtMult1    [iMethod][0]->Clone();
   effJet2PtMult2[iMethod]    = (TH1F*) nJet2PtMult2    [iMethod][0]->Clone();
   effJet3PtMult3[iMethod]    = (TH1F*) nJet3PtMult3    [iMethod][0]->Clone();
   effJet4PtMult4[iMethod]    = (TH1F*) nJet4PtMult4    [iMethod][0]->Clone();
   effJet5PtMult5[iMethod]    = (TH1F*) nJet5PtMult5    [iMethod][0]->Clone();
   effJet6PtMult6Incl[iMethod]= (TH1F*) nJet6PtMult6Incl[iMethod][0]->Clone();
   effJetEta[iMethod]   = (TH1F*) nJetEta   [iMethod][0]->Clone();
   effJet3EtaMult3[iMethod]    = (TH1F*) nJet3EtaMult3    [iMethod][0]->Clone();
   effControl[iMethod]   = (TH1F*) nControl   [iMethod][0]->Clone();
   effLeptonPt[iMethod]    = (TH1F*) nLeptonPt    [iMethod][0]->Clone();
   effLeptonEta[iMethod]   = (TH1F*) nLeptonEta   [iMethod][0]->Clone();
   effLeptonRelIso[iMethod]   = (TH1F*) nLeptonRelIso   [iMethod][0]->Clone();
     effNjets[iMethod]  ->Reset();
     effJetPt[iMethod]     ->Reset();
     effJet1PtMult1[iMethod]     ->Reset();
     effJet2PtMult2[iMethod]     ->Reset();
     effJet3PtMult3[iMethod]     ->Reset();
     effJet3EtaMult3[iMethod]     ->Reset();
     effJet4PtMult4[iMethod]     ->Reset();
     effJet5PtMult5[iMethod]     ->Reset();
     effJet6PtMult6Incl[iMethod] ->Reset();
     effJetEta[iMethod]    ->Reset();
     effControl[iMethod]->Reset();
     effLeptonPt[iMethod]     ->Reset();
     effLeptonEta[iMethod]    ->Reset();
     effLeptonRelIso[iMethod]     ->Reset();
     effNjets[iMethod]  -> Divide(nNjets[iMethod][1],   nNjets[iMethod][0], 1, 1, "B");
     effJetPt[iMethod]     -> Divide(nJetPt[iMethod][1],      nJetPt[iMethod][0], 1, 1, "B");
     effJet1PtMult1[iMethod]     -> Divide(nJet1PtMult1[iMethod][1],      nJet1PtMult1[iMethod][0], 1, 1, "B");
     effJet2PtMult2[iMethod]     -> Divide(nJet2PtMult2[iMethod][1],      nJet2PtMult2[iMethod][0], 1, 1, "B");
     effJet3PtMult3[iMethod]     -> Divide(nJet3PtMult3[iMethod][1],      nJet3PtMult3[iMethod][0], 1, 1, "B");
     effJet4PtMult4[iMethod]     -> Divide(nJet4PtMult4[iMethod][1],      nJet4PtMult4[iMethod][0], 1, 1, "B");
     effJet5PtMult5[iMethod]     -> Divide(nJet5PtMult5[iMethod][1],      nJet5PtMult5[iMethod][0], 1, 1, "B");
     effJet6PtMult6Incl[iMethod]     -> Divide(nJet6PtMult6Incl[iMethod][1],      nJet6PtMult6Incl[iMethod][0], 1, 1, "B");
     effJetEta[iMethod]    -> Divide(nJetEta[iMethod][1],     nJetEta[iMethod][0], 1, 1, "B");
     effJet3EtaMult3[iMethod]     -> Divide(nJet3EtaMult3[iMethod][1],      nJet3EtaMult3[iMethod][0], 1, 1, "B");
     effControl[iMethod]-> Divide(nControl[iMethod][1], nControl[iMethod][0], 1, 1, "B");
     effLeptonPt[iMethod]     -> Divide(nLeptonPt[iMethod][1],      nLeptonPt[iMethod][0], 1, 1, "B");
     effLeptonEta[iMethod]    -> Divide(nLeptonEta[iMethod][1],     nLeptonEta[iMethod][0], 1, 1, "B");
     effLeptonRelIso[iMethod]     -> Divide(nLeptonRelIso[iMethod][1],      nLeptonRelIso[iMethod][0], 1, 1, "B");
     effNjets[iMethod]  -> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, #geq 3 PF jets)");
     effJetPt[iMethod]     -> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, #geq 3 PF jets), 3rd jet");
     effJet1PtMult1[iMethod]-> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, 1 PF jet), 1st jet");
     effJet2PtMult2[iMethod]-> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, 2 PF jets), 2nd jet");
     effJet3PtMult3[iMethod]-> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, 3 PF jets), 3rd jet");
     effJet4PtMult4[iMethod]-> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, 4 PF jets), 4th jet");
     effJet5PtMult5[iMethod]-> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, 5 PF jets), 5th jet");
     effJet6PtMult6Incl[iMethod]-> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, #geq 6 PF jets), 6th jet");
     effJetEta[iMethod]    -> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, #geq 3 PF jets), 3rd jet");
     effJet3EtaMult3[iMethod]-> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, 3 PF jets), 3rd jet");
     effControl[iMethod]-> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, #geq 3 PF jets)");
     effLeptonPt[iMethod]     -> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, #geq 3 PF jets)");
     effLeptonEta[iMethod]    -> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, #geq 3 PF jets)");
     effLeptonRelIso[iMethod]     -> SetTitle("Trigger Efficiency IsoMu17Tri(PF)Jet wrt. IsoMu24 (1 #mu, #geq 3 PF jets)");
//      effNjets[iMethod]  -> SetTitle("Trigger Efficiency Mu17_TriCentralJet30 (1 #mu, #geq 3 PF jets)");
//      effJetPt[iMethod]     -> SetTitle("Trigger Efficiency Mu17_TriCentralJet30 (1 #mu, #geq 3 PF jets), 3rd jet");
//      effJetEta[iMethod]    -> SetTitle("Trigger Efficiency Mu17_TriCentralJet30 (1 #mu, #geq 3 PF jets), 3rd jet");
//      effControl[iMethod]-> SetTitle("Trigger Efficiency Mu17_TriCentralJet30 (1 #mu, #geq 3 PF jets)");



   /// output of control plots
   std::cout<<methods[iMethod]<<" "
       <<" probe: "<<nControl[iMethod][0]->GetBinContent(1)
       <<" test: " <<nControl[iMethod][1]->GetBinContent(1)
       <<" eff: "  <<100*effControl[iMethod]->GetBinContent(1)
       <<" +/- "  <<100*effControl[iMethod]->GetBinError(1)
     <<std::endl;

   /// efficiency cross check: calculate total eff. from differential eff.
   double totalEffPt =0, totalProbePt=0, totalTestPt=0;
   double PtCut = 30;
   for (int iBin =1; iBin <= nJetPt[iMethod][0]->GetNbinsX(); iBin++) {
     if(nJetPt[iMethod][0]->GetBinCenter(iBin) > PtCut) {
       totalProbePt+=nJetPt[iMethod][0]->GetBinContent(iBin);
       totalTestPt +=nJetPt[iMethod][1]->GetBinContent(iBin);
     }
   }
   totalEffPt = totalTestPt / totalProbePt;
   
   /// efficiency cross check: calculate total eff. from differential eff.
   double totalEffNjets3 =0, totalProbeNjets3=0, totalTestNjets3=0;
   double NjetsCut3 = 3;
   for (int iBin =1; iBin <= nNjets[iMethod][0]->GetNbinsX(); iBin++) {
     if(nNjets[iMethod][0]->GetBinCenter(iBin) > NjetsCut3) {
       totalProbeNjets3+=nNjets[iMethod][0]->GetBinContent(iBin);
       totalTestNjets3 +=nNjets[iMethod][1]->GetBinContent(iBin);
     }
   }
   totalEffNjets3 = totalTestNjets3 / totalProbeNjets3;
   
   /// efficiency cross check: calculate total eff. from differential eff.
   double totalEffNjets4 =0, totalProbeNjets4=0, totalTestNjets4=0;
   double NjetsCut4 = 4;
   for (int iBin =1; iBin <= nNjets[iMethod][0]->GetNbinsX(); iBin++) {
     if(nNjets[iMethod][0]->GetBinCenter(iBin) > NjetsCut4) {
       totalProbeNjets4+=nNjets[iMethod][0]->GetBinContent(iBin);
       totalTestNjets4 +=nNjets[iMethod][1]->GetBinContent(iBin);
     }
   }
   totalEffNjets4 = totalTestNjets4 / totalProbeNjets4;
   /*
   double totalEffEta =0, totalProbeEta=0, totalTestEta=0;
   double EtaCut = 2.1;
   for (int iBin =1; iBin <= probeEta[iMethod][iFolder]->GetNbinsX(); iBin++) {
     if(fabs(probeEta[iMethod][iFolder]->GetBinCenter(iBin)) < EtaCut) {
       totalProbeEta+=probeEta[iMethod][iFolder]->GetBinContent(iBin);
       totalTestEta +=testEta [iMethod][iFolder]->GetBinContent(iBin);
     }
   }
   totalEffEta = totalTestEta / totalProbeEta;
 
   double totalEffPhi =0;
   totalEffPhi = testPhi[iMethod][iFolder]->GetEntries() / probePhi[iMethod][iFolder]->GetEntries();
   
   double totalEffMult =0;
   totalEffMult  = testMult [iMethod][iFolder]->GetEntries() / probeMult [iMethod][iFolder]->GetEntries();
   
   double totalEffMinDR =0, totalProbeMinDR=0, totalTestMinDR=0;
   for (int iBin =1; iBin <= probeMinDR[iMethod][iFolder]->GetNbinsX(); iBin++) {
       totalProbeMinDR+=probeMinDR[iMethod][iFolder]->GetBinContent(iBin);
       totalTestMinDR +=testMinDR [iMethod][iFolder]->GetBinContent(iBin);
   }
   totalEffMinDR = totalTestMinDR / totalProbeMinDR;
   */
   std::cout<<"Eff. comp.: control="<<effControl[iMethod]->GetBinContent(1)
            <<"; pt="<<totalEffPt
            <<"; Njets3="<<totalEffNjets3 <<"; Njets4="<<totalEffNjets4<<std::endl;
   
}

 /// Draw one Canvas for each folder comparing different methods.
 /// Each canvas shows test (1st row) and probe collection (2nd) and efficiency (3rd) for different variables (columns)
  /// Define histo and legend styles and options
  int lineStyle   []= {1,1,1,1,1,1};
  int lineColor   []= {2,1,4,kGreen+2,kGray+2,8};
  int markerStyle []={1,1,20,21,22,1,23};
  int markerColor []= {2,1,4,kGreen+2,kGray+2,8};
  TString drawOpt []= {"","E same","E X0 P same","E X0 same","E same","E X0 same"};
  TString legOpt  []= {"L","L","P","P","P","L","P"};
  double setRangeUserLow = 0.5;
  double setRangeUserHigh = 1.1;

  TCanvas* CanvComp = new TCanvas("Comparison", "Comparison", 1200,900);
  TCanvas* CanvCompDiffMultPt = new TCanvas("ComparisonDiffMultPt", "ComparisonDiffMultPt", 1200,900);
  TCanvas* CanvCompDiffMultEta = new TCanvas("ComparisonDiffMultEta", "ComparisonDiffMultEta", 1200,900);
  TCanvas* CanvCompLep = new TCanvas("ComparisonLep", "ComparisonLep", 1200,900);
  TCanvas* CanvLeg = new TCanvas("CanvLeg", "CanvLeg", 1);
  if(onlyEffPlots) CanvComp ->Divide(2,2);
  else             CanvComp ->Divide(4,2);
  //if(onlyEffPlots) CanvCompDiffMultPt->Divide(3,2);
  if(onlyEffPlots) CanvCompDiffMultPt->Divide(2,2);
  else             CanvCompDiffMultPt ->Divide(6,2);
  if(onlyEffPlots) CanvCompDiffMultEta->Divide(2,2);
  else             CanvCompDiffMultEta ->Divide(6,2);
  if(onlyEffPlots) CanvCompLep ->Divide(2,2);
  else             CanvCompLep ->Divide(4,2);
  //TLegend* leg=new TLegend(0.45,0.16,0.87,0.48);
  TLegend* leg=new TLegend(0.36,0.13,0.75,0.43);
  //TLegend* leg=new TLegend(0.4,0.2,0.85,0.6);
  
  leg->SetFillStyle(0);
  
  for(int iMethod=0; iMethod<methodNum; iMethod++){
  /// Set histo styles
  effControl[iMethod] ->SetLineStyle(lineStyle[iMethod]);     
  effJetPt[iMethod] ->SetLineStyle(lineStyle[iMethod]);     
  effJet1PtMult1[iMethod] ->SetLineStyle(lineStyle[iMethod]);
  effJet2PtMult2[iMethod] ->SetLineStyle(lineStyle[iMethod]);
  effJet3PtMult3[iMethod] ->SetLineStyle(lineStyle[iMethod]);
  effJet4PtMult4[iMethod] ->SetLineStyle(lineStyle[iMethod]);
  effJet5PtMult5[iMethod] ->SetLineStyle(lineStyle[iMethod]);
  effJet6PtMult6Incl[iMethod] ->SetLineStyle(lineStyle[iMethod]);
  effJetEta[iMethod]->SetLineStyle(lineStyle[iMethod]);    
  effJet3EtaMult3[iMethod] ->SetLineStyle(lineStyle[iMethod]);
  effNjets[iMethod]->SetLineStyle(lineStyle[iMethod]);
  effLeptonPt[iMethod]    ->SetLineStyle(lineStyle[iMethod]);     
  effLeptonEta[iMethod]   ->SetLineStyle(lineStyle[iMethod]);    
  effLeptonRelIso[iMethod]->SetLineStyle(lineStyle[iMethod]);
      
  effControl[iMethod] ->SetLineColor(lineColor[iMethod]);     
  effJetPt[iMethod] ->SetLineColor(lineColor[iMethod]);     
  effJet1PtMult1[iMethod] ->SetLineColor(lineColor[iMethod]);
  effJet2PtMult2[iMethod] ->SetLineColor(lineColor[iMethod]);
  effJet3PtMult3[iMethod] ->SetLineColor(lineColor[iMethod]);
  effJet4PtMult4[iMethod] ->SetLineColor(lineColor[iMethod]);
  effJet5PtMult5[iMethod] ->SetLineColor(lineColor[iMethod]);
  effJet6PtMult6Incl[iMethod] ->SetLineColor(lineColor[iMethod]);
  effJetEta[iMethod]->SetLineColor(lineColor[iMethod]);    
  effJet3EtaMult3[iMethod] ->SetLineColor(lineColor[iMethod]);
  effNjets[iMethod] ->SetLineColor(lineColor[iMethod]); 
  effLeptonPt[iMethod]    ->SetLineColor(lineColor[iMethod]);
  effLeptonEta[iMethod]   ->SetLineColor(lineColor[iMethod]);
  effLeptonRelIso[iMethod]->SetLineColor(lineColor[iMethod]);
     
  effControl[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);     
  effJetPt[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);     
  effJet1PtMult1[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);
  effJet2PtMult2[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);
  effJet3PtMult3[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);
  effJet4PtMult4[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);
  effJet5PtMult5[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);
  effJet6PtMult6Incl[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);
  effJetEta[iMethod]->SetMarkerStyle(markerStyle[iMethod]);    
  effJet3EtaMult3[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);
  effNjets[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);
  effLeptonPt[iMethod]     ->SetMarkerStyle(markerStyle[iMethod]);
  effLeptonEta[iMethod]    ->SetMarkerStyle(markerStyle[iMethod]);
  effLeptonRelIso[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);
  
  effControl[iMethod]   ->SetMarkerColor(markerColor[iMethod]);     
  effJetPt[iMethod]   ->SetMarkerColor(markerColor[iMethod]);     
  effJet1PtMult1[iMethod] ->SetMarkerColor(markerColor[iMethod]);
  effJet2PtMult2[iMethod] ->SetMarkerColor(markerColor[iMethod]);
  effJet3PtMult3[iMethod] ->SetMarkerColor(markerColor[iMethod]);
  effJet4PtMult4[iMethod] ->SetMarkerColor(markerColor[iMethod]);
  effJet5PtMult5[iMethod] ->SetMarkerColor(markerColor[iMethod]);
  effJet6PtMult6Incl[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);
  effJetEta[iMethod]  ->SetMarkerColor(markerColor[iMethod]);    
  effJet3EtaMult3[iMethod] ->SetMarkerColor(markerColor[iMethod]);
  effNjets[iMethod]   ->SetMarkerColor(markerColor[iMethod]);
  effLeptonPt[iMethod]    ->SetMarkerColor(markerColor[iMethod]);
  effLeptonEta[iMethod]   ->SetMarkerColor(markerColor[iMethod]);
  effLeptonRelIso[iMethod]->SetMarkerColor(markerColor[iMethod]);
  
  effControl[iMethod]   ->GetYaxis()->SetRangeUser(setRangeUserLow, setRangeUserHigh);     
  effJetPt[iMethod]   ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);
  effJet1PtMult1[iMethod]   ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);
  effJet2PtMult2[iMethod]   ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);
  effJet3PtMult3[iMethod]   ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);   
  effJet4PtMult4[iMethod]   ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);      
  effJet5PtMult5[iMethod]   ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);       
  effJet6PtMult6Incl[iMethod]   ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);                                
  effJetEta[iMethod]  ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);
  effJet3EtaMult3[iMethod]   ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);   
  effNjets[iMethod]   ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);
  effLeptonPt[iMethod]     ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);
  effLeptonEta[iMethod]    ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);
  effLeptonRelIso[iMethod] ->GetYaxis()->SetRangeUser(setRangeUserLow,setRangeUserHigh);
  
  effJetPt[iMethod]   ->GetXaxis()->SetRangeUser(0,150);
  effJet1PtMult1[iMethod]   ->GetXaxis()->SetRangeUser(0,150);
  effJet2PtMult2[iMethod]   ->GetXaxis()->SetRangeUser(0,150);
  effJet3PtMult3[iMethod]   ->GetXaxis()->SetRangeUser(0,150);
  effJet4PtMult4[iMethod]   ->GetXaxis()->SetRangeUser(0,150);
  effJet5PtMult5[iMethod]   ->GetXaxis()->SetRangeUser(0,150);
  effJet6PtMult6Incl[iMethod]   ->GetXaxis()->SetRangeUser(0,150);
  effNjets[iMethod]->GetXaxis()->SetRangeUser(0,10);
     
  effControl[iMethod]->GetXaxis()->SetNdivisions(0);
  effControl[iMethod]->GetXaxis()->SetTitle("Overall"); 
  effJetPt[iMethod] ->GetXaxis()->SetTitle("Jet p_{T} [GeV]");
  effJet1PtMult1[iMethod] ->GetXaxis()->SetTitle("p_{T} 1st Jet [GeV]");
  effJet2PtMult2[iMethod] ->GetXaxis()->SetTitle("p_{T} 2nd Jet [GeV]");    
  effJet3PtMult3[iMethod] ->GetXaxis()->SetTitle("p_{T} 3rd Jet [GeV]");  
  effJet4PtMult4[iMethod] ->GetXaxis()->SetTitle("p_{T} 4th Jet [GeV]");  
  effJet5PtMult5[iMethod] ->GetXaxis()->SetTitle("p_{T} 5th Jet [GeV]");   
  effJet6PtMult6Incl[iMethod] ->GetXaxis()->SetTitle("p_{T} 6th Jet [GeV]");         
  effJetEta[iMethod]->GetXaxis()->SetTitle("Jet #eta");    
  effJet3EtaMult3[iMethod] ->GetXaxis()->SetTitle("#eta 3rd Jet"); 
  effNjets[iMethod] ->GetXaxis()->SetTitle("Jet Multiplicity");
  effLeptonPt[iMethod]    ->GetXaxis()->SetTitle("Lepton p_{T}");         
  effLeptonEta[iMethod]   ->GetXaxis()->SetTitle("Lepton #eta");    
  effLeptonRelIso[iMethod]->GetXaxis()->SetTitle("relIso");
  
  effJetPt[iMethod]      ->GetXaxis()->SetTitleSize(0.05);
  effJet1PtMult1[iMethod]      ->GetXaxis()->SetTitleSize(0.05);
  effJet2PtMult2[iMethod]      ->GetXaxis()->SetTitleSize(0.05); 
  effJet3PtMult3[iMethod]      ->GetXaxis()->SetTitleSize(0.05);          
  effJet4PtMult4[iMethod]      ->GetXaxis()->SetTitleSize(0.05);          
  effJet5PtMult5[iMethod]      ->GetXaxis()->SetTitleSize(0.05);          
  effJet6PtMult6Incl[iMethod]  ->GetXaxis()->SetTitleSize(0.05);                             
  effJetEta[iMethod]      ->GetXaxis()->SetTitleSize(0.05);    
  effJet3EtaMult3[iMethod]      ->GetXaxis()->SetTitleSize(0.05);        
  effNjets[iMethod]      ->GetXaxis()->SetTitleSize(0.05);
  effLeptonPt[iMethod]    ->GetXaxis()->SetTitleSize(0.05);
  effLeptonEta[iMethod]    ->GetXaxis()->SetTitleSize(0.05);
  effLeptonRelIso[iMethod] ->GetXaxis()->SetTitleSize(0.05);
  
  effJetPt[iMethod]   ->GetXaxis()->SetLabelSize(0.05);
  effJet1PtMult1[iMethod]  ->GetXaxis()->SetLabelSize(0.05);
  effJet2PtMult2[iMethod]  ->GetXaxis()->SetLabelSize(0.05);
  effJet3PtMult3[iMethod]  ->GetXaxis()->SetLabelSize(0.05);
  effJet4PtMult4[iMethod]  ->GetXaxis()->SetLabelSize(0.05);
  effJet5PtMult5[iMethod]  ->GetXaxis()->SetLabelSize(0.05);
  effJet6PtMult6Incl[iMethod]  ->GetXaxis()->SetLabelSize(0.05);
  effJetEta[iMethod]  ->GetXaxis()->SetLabelSize(0.05);          
  effJet3EtaMult3[iMethod]  ->GetXaxis()->SetLabelSize(0.05);
  effNjets[iMethod]   ->GetXaxis()->SetLabelSize(0.05);
  effLeptonPt[iMethod]      ->GetXaxis()->SetLabelSize(0.05);  
  effLeptonEta[iMethod]     ->GetXaxis()->SetLabelSize(0.05);
  effLeptonRelIso[iMethod]  ->GetXaxis()->SetLabelSize(0.05);
  
  effJetPt[iMethod]    ->GetYaxis()->SetTitleSize(0.05);
  effJet1PtMult1[iMethod]    ->GetYaxis()->SetTitleSize(0.05);
  effJet2PtMult2[iMethod]    ->GetYaxis()->SetTitleSize(0.05);
  effJet3PtMult3[iMethod]    ->GetYaxis()->SetTitleSize(0.05);
  effJet4PtMult4[iMethod]    ->GetYaxis()->SetTitleSize(0.05);
  effJet5PtMult5[iMethod]    ->GetYaxis()->SetTitleSize(0.05);
  effJet6PtMult6Incl[iMethod]    ->GetYaxis()->SetTitleSize(0.05);
  effJetEta[iMethod]   ->GetYaxis()->SetTitleSize(0.05);     
  effJet3EtaMult3[iMethod]    ->GetYaxis()->SetTitleSize(0.05);
  effNjets[iMethod]    ->GetYaxis()->SetTitleSize(0.05);
  effLeptonPt[iMethod]     ->GetYaxis()->SetTitleSize(0.05);   
  effLeptonEta[iMethod]    ->GetYaxis()->SetTitleSize(0.05);
  effLeptonRelIso[iMethod] ->GetYaxis()->SetTitleSize(0.05);

  effJetPt[iMethod]   ->GetYaxis()->SetLabelSize(0.05);
  effJet1PtMult1[iMethod]   ->GetYaxis()->SetLabelSize(0.05);
  effJet2PtMult2[iMethod]   ->GetYaxis()->SetLabelSize(0.05);
  effJet3PtMult3[iMethod]   ->GetYaxis()->SetLabelSize(0.05);
  effJet4PtMult4[iMethod]   ->GetYaxis()->SetLabelSize(0.05);
  effJet5PtMult5[iMethod]   ->GetYaxis()->SetLabelSize(0.05);
  effJet6PtMult6Incl[iMethod]   ->GetYaxis()->SetLabelSize(0.05);
  effJetEta[iMethod]  ->GetYaxis()->SetLabelSize(0.05);     
  effJet3EtaMult3[iMethod]   ->GetYaxis()->SetLabelSize(0.05);
  effNjets[iMethod]   ->GetYaxis()->SetLabelSize(0.05);
  effLeptonPt[iMethod]    ->GetYaxis()->SetLabelSize(0.05);
  effLeptonEta[iMethod]   ->GetYaxis()->SetLabelSize(0.05);
  effLeptonRelIso[iMethod]->GetYaxis()->SetLabelSize(0.05);
  
  
  
     /// draw only eff plots
    leg->AddEntry(effNjets[iMethod],methods[iMethod],legOpt[iMethod]);
    
    if(onlyEffPlots){
      CanvComp->cd(1);
      effControl[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      CanvComp->cd(2);
      effNjets[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      CanvComp->cd(3);
      effJetPt[iMethod]->Draw(drawOpt[iMethod].Data());
      TF1 *f1 = new TF1("f1", "(1 - [0]*TMath::Exp(-[1]*(x-[2])))", 30, 150);
      //effJetPt[iMethod]->Fit(f1,"RW","same");
      leg->Draw();
      CanvComp->cd(4);
      effJetEta[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      
//       CanvCompDiffMultPt->cd(1);
//       effJet1PtMult1[iMethod]->Draw(drawOpt[iMethod].Data());
//       leg->Draw();
//       CanvCompDiffMultPt->cd(2);
//       effJet2PtMult2[iMethod]->Draw(drawOpt[iMethod].Data());
//       leg->Draw();
      CanvCompDiffMultPt->cd(1);
      effJet3PtMult3[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      CanvCompDiffMultPt->cd(2);
      effJet4PtMult4[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      CanvCompDiffMultPt->cd(3);
      effJet5PtMult5[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      CanvCompDiffMultPt->cd(4);
      effJet6PtMult6Incl[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      
      CanvCompDiffMultEta->cd(1);
      effJet3EtaMult3[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      
      CanvCompLep->cd(1);
      effControl[iMethod]->DrawCopy(drawOpt[iMethod].Data());
      leg->Draw();
      CanvCompLep->cd(2);
      effLeptonRelIso[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      CanvCompLep->cd(3);
      effLeptonPt[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      CanvCompLep->cd(4);
      effLeptonEta[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      
    }
    else{
      if(iMethod==0){
	TLegend* leg2=new TLegend(0.6,0.6,0.8,0.8);
	CanvComp->cd(1);
	nControl[iMethod][0]->Draw("hist");
	nControl[iMethod][1]->Draw("same hist");
	nControl[iMethod][1]->SetLineStyle(2);
	nControl[iMethod][1]->SetLineColor(4);
	nControl[iMethod][0]->GetXaxis()->SetNdivisions(0);
	nControl[iMethod][0]->GetXaxis()->SetTitle("Overall");
	nControl[iMethod][0]->GetXaxis()->SetTitleSize(0.05);
	nControl[iMethod][0]->GetXaxis()->SetLabelSize(0.05);
	nControl[iMethod][0]->GetYaxis()->SetTitleSize(0.05);
	nControl[iMethod][0]->GetYaxis()->SetLabelSize(0.05);
	leg2->AddEntry(nControl[iMethod][0], "Probe, "+methods[0], "L");
	leg2->AddEntry(nControl[iMethod][1], "Test, "+methods[0], "L");
	leg2->Draw();
	CanvComp->cd(2);
	nNjets[iMethod][0]->Draw("hist");
	nNjets[iMethod][1]->Draw("same hist");
	nNjets[iMethod][0]->GetXaxis()->SetRangeUser(0,10);
	nNjets[iMethod][1]->SetLineStyle(2);
	nNjets[iMethod][1]->SetLineColor(4);
	nNjets[iMethod][0]->GetXaxis()->SetTitle("Jet Multiplicity");
	nNjets[iMethod][0]->GetXaxis()->SetTitleSize(0.05);
	nNjets[iMethod][0]->GetXaxis()->SetLabelSize(0.05);
	nNjets[iMethod][0]->GetYaxis()->SetTitleSize(0.05);
	nNjets[iMethod][0]->GetYaxis()->SetLabelSize(0.05);
	//leg2->Draw();
	CanvComp->cd(3);
	nJetPt[iMethod][0]->Draw("hist");
	nJetPt[iMethod][1]->Draw("same hist");
	nJetPt[iMethod][0]->GetXaxis()->SetRangeUser(0,150);
	nJetPt[iMethod][1]->SetLineStyle(2);
	nJetPt[iMethod][1]->SetLineColor(4);
	nJetPt[iMethod][0]->GetXaxis()->SetTitleSize(0.05);
	nJetPt[iMethod][0]->GetXaxis()->SetTitle("p_{T} [GeV]");
	nJetPt[iMethod][0]->GetXaxis()->SetLabelSize(0.05);
	nJetPt[iMethod][0]->GetYaxis()->SetTitleSize(0.05);
	nJetPt[iMethod][0]->GetYaxis()->SetLabelSize(0.05);
	//leg2->Draw();
	CanvComp->cd(4);
	nJetEta[iMethod][0]->Draw("hist");
	nJetEta[iMethod][1]->Draw("same hist");
	nJetEta[iMethod][1]->SetLineStyle(2);
	nJetEta[iMethod][1]->SetLineColor(4);
	nJetEta[iMethod][0]->GetXaxis()->SetTitle("#eta");
	nJetEta[iMethod][0]->GetXaxis()->SetTitleSize(0.05);
	nJetEta[iMethod][0]->GetXaxis()->SetLabelSize(0.05);
	nJetEta[iMethod][0]->GetYaxis()->SetTitleSize(0.05);
	nJetEta[iMethod][0]->GetYaxis()->SetLabelSize(0.05);
        //leg2->Draw();
      }
      effJetPt[iMethod]   ->SetTitle("Trigger Efficiency");     
      effJetEta[iMethod]  ->SetTitle("Trigger Efficiency");    
      effNjets[iMethod]->SetTitle("Trigger Efficiency");
      effControl[iMethod]->SetTitle("Trigger Efficiency");    
      
      CanvComp->cd(5);
      effControl[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      CanvComp->cd(6);
      effNjets[iMethod]->Draw(drawOpt[iMethod].Data());
      //leg->Draw();
      CanvComp->cd(7);
      effJetPt[iMethod]->Draw(drawOpt[iMethod].Data());
      //leg->Draw();
      CanvComp->cd(8);
      effJetEta[iMethod]->Draw(drawOpt[iMethod].Data());
      //leg->Draw();
    }
    CanvLeg->cd();
    leg->Draw();
    

    

 //leg->Draw();
  }
  
  if(save){
    CanvComp->Print(outputFolder+outputFileName+"_JetOverview.png");
    CanvComp->cd(2)->Print(outputFolder+outputFileName+"_Njets.png");
    CanvComp->cd(3)->Print(outputFolder+outputFileName+"_JetPt.png");
    CanvComp->cd(4)->Print(outputFolder+outputFileName+"_JetEta.png");
      
//       CanvCompDiffMultPt->cd(1)->Print(outputFolder+outputFileName+"_Jet1PtMult1.png");
//       CanvCompDiffMultPt->cd(2)->Print(outputFolder+outputFileName+"_Jet2PtMult2.png");
    CanvCompDiffMultPt->cd(1)->Print(outputFolder+outputFileName+"_Jet3PtMult3.png");
    CanvCompDiffMultPt->cd(2)->Print(outputFolder+outputFileName+"_Jet4PtMult4.png");
    CanvCompDiffMultPt->cd(3)->Print(outputFolder+outputFileName+"_Jet5PtMult5.png");
    CanvCompDiffMultPt->cd(4)->Print(outputFolder+outputFileName+"_Jet6PtMult6Incl.png");
    
    CanvCompDiffMultEta->cd(1)->Print(outputFolder+outputFileName+"_Jet3EtaMult3.png","png");
      
    CanvCompLep->Print(outputFolder+outputFileName+"_LeptonOverview.png");
    CanvCompLep->cd(2)->Print(outputFolder+outputFileName+"_relIso.png");
    CanvCompLep->cd(3)->Print(outputFolder+outputFileName+"_LeptonPt.png");
    CanvCompLep->cd(4)->Print(outputFolder+outputFileName+"_LeptonEta.png");
      
    CanvLeg->Print(outputFolder+outputFileName+"_Legend.png");
    std::cout<<"Canvas with plots is saved in "<<outputFolder<<std::endl;
  }
}
