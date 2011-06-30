#include <iostream>
#include "TH1.h"
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"

void tagAndProbePlotsRun2011AIsoMu(bool save=false)
{
  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetPadBottomMargin(0.11);
  gStyle->SetLabelSize(0.05,"XY");
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetFillColor(0);
  /// path where input files are stored
  //char inputPath[]="/rdata2/uhh-cms019/data/jlange/top/CMSSW_3_6_1/src";
  char inputPath[]=".";
  TString outputFolder   = "/afs/desy.de/user/j/jlange/analysis/tagAndProbe/plots/2011/singleMu";
  TString outputFileName = "/efficiencyIsoMu_";
  
  /// if set to 0: effHistos from files are taken, to 1: effHistos are recalculated
  int recalculateEffHistos = 1;
  /// if set to 0: all plots (probe, test, eff) are drawn; to 1: only eff plots
  int onlyEffPlots =1;
  /// index of MC file to normalise scale factors to
  int idxSFnorm = 0;

  /// definition of methods (e.g. Tag and Probe MC tapMC, tapData, ...
  const int methodNum=2;
  //TString methods[methodNum]={"tapMC"};
  //TString methods[100]={"Spring11 MC Mu9", "2011A Mu15", "2011A Mu17emu", "2011A Mu20","2010B2 Mu15","Z genMu match Mu9"};
  TString methods[100]={"2011A IsoMu17","2011A IsoMu17 MinJet4", "Spring11 MC Mu9", "2011A Mu15", "2011A Mu17emu", "2011A Mu20","2011A IsoMu17","Z genMu match Mu9"};
  //TString methods[100]={"T&P MC", "T&P 2010A+B", "Z matched mu", "W matched mu","t matched mu"};
  //TString methods[100]={"Run2010AOldReco no cuts", "Run2010A","Run2010AOldReco","",""};
  TFile* files[100];
  //files[0]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeMCFall10PF_cfg/analyzeZMuMuTagAndProbeMCFall10PF.root",inputPath)); /// Tag and Probe from MC
  //files[0]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeMCSpring11_HLT_Mu9_cfg/analyzeZMuMuTagAndProbeMCSpring11_HLT_Mu9.root",inputPath)); /// Tag and Probe from MC
  files[0]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeRun2011AV1andV2_HLT_IsoMu17_cfg/analyzeZMuMuTagAndProbeRun2011AV1andV2_HLT_IsoMu17.root",inputPath)); /// Tag and Probe from data
  files[1]=new TFile(Form("%s/test.root",inputPath)); /// Tag and Probe from data
  //files[2]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeMCSpring11_HLT_Mu15_cfg/analyzeZMuMuTagAndProbeMCSpring11_HLT_Mu15.root",inputPath)); /// Tag and Probe from MC
  //files[2]=new TFile(Form("%s/2010/analyzeZMuMuTagAndProbeRun2010AandB_HLT_Mu9and15_Nov4ReRecoPF_hadd.root",inputPath)); /// Tag and Probe from data
  //files[1]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeRun2011Av2_HLT_Mu15_Mu17TriJet_cfg/analyzeZMuMuTagAndProbeRun2011Acomb_HLT_Mu15_Mu17TriJet.root",inputPath)); /// Tag and Probe from data
  //files[2]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeRun2011Av2_HLT_Mu17emu_Mu17TriJet_cfg/analyzeZMuMuTagAndProbeRun2011Acomb_HLT_Mu17emu_Mu17TriJet.root",inputPath)); /// Tag and Probe from data
  //files[3]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeRun2011Av2_HLT_Mu20_Mu17TriJet_cfg/analyzeZMuMuTagAndProbeRun2011Acomb_HLT_Mu20_Mu17TriJet.root",inputPath)); /// Tag and Probe from data
  //files[4]=new TFile(Form("%s/2010/analyzeZMuMuTagAndProbeRun2010B2_Nov4ReRecoPF_HLT_Mu15_hadd.root",inputPath)); /// Tag and Probe from data
  //files[4]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeRun2011AV1andV2_HLT_IsoMu17_cfg/analyzeZMuMuTagAndProbeRun2011AV1andV2_HLT_IsoMu17.root",inputPath)); /// Tag and Probe from data
  //files[3]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeRun2011A_HLT_Mu17_TriCentralJet30_cfg/analyzeZMuMuTagAndProbeRun2011A_HLT_Mu17_TriCentralJet30.root",inputPath)); /// Tag and Probe from data
  
  /// different tap studies (different efficiencies)
  const int folderNum=5;
  TString folders[]={"tapTrkQ", "tapIso", "tapMinDR", "tapTotalSelection", "tapTrigger"};
  TString foldersTitle[]={"Track Quality", "Isolation", "#DeltaR (after Iso Cut)","Overall Selection", "Trigger"};
  
  //TString folders[]={"tapTrigger"};
  //TString foldersTitle[]={ "Trigger"};

  TH1F* probeControl [methodNum][folderNum];
  TH1F* probePt      [methodNum][folderNum];
  TH1F* probeEta     [methodNum][folderNum];
  TH1F* probeRelIso     [methodNum][folderNum];
  TH1F* probeMult    [methodNum][folderNum];
  TH1F* probeMinDR   [methodNum][folderNum];
  TH1F* testControl  [methodNum][folderNum];
  TH1F* testPt       [methodNum][folderNum];
  TH1F* testEta      [methodNum][folderNum];
  TH1F* testRelIso      [methodNum][folderNum];
  TH1F* testMult     [methodNum][folderNum];
  TH1F* testMinDR    [methodNum][folderNum];
  TH1F* effControl   [methodNum][folderNum];
  TH1F* effPt        [methodNum][folderNum];
  TH1F* effEta       [methodNum][folderNum];
  TH1F* effRelIso       [methodNum][folderNum];
  TH1F* effMult      [methodNum][folderNum];
  TH1F* effMinDR     [methodNum][folderNum];
  TH1F* effSFControl [methodNum][folderNum]; //scale factors
  TH1F* effSFPt      [methodNum][folderNum];
  TH1F* effSFEta     [methodNum][folderNum];
  TH1F* effSFRelIso     [methodNum][folderNum];
  TH1F* effSFMult    [methodNum][folderNum];
  TH1F* effSFMinDR   [methodNum][folderNum];

for(int iMethod=0; iMethod<methodNum; iMethod++){
 for(int iFolder=0; iFolder<folderNum; iFolder++) {
   probeControl[iMethod][iFolder]=(TH1F*) files[iMethod]->Get(folders[iFolder]+"/probeControl")->Clone();
   probePt[iMethod][iFolder]=    (TH1F*) files[iMethod]->Get(folders[iFolder]+"/probePt")->Clone();
   probeEta[iMethod][iFolder]=   (TH1F*) files[iMethod]->Get(folders[iFolder]+"/probeEta")->Clone();
   probeRelIso[iMethod][iFolder]=   (TH1F*) files[iMethod]->Get(folders[iFolder]+"/probeRelIso")->Clone();
   probeMult[iMethod][iFolder]=  (TH1F*) files[iMethod]->Get(folders[iFolder]+"/probeMult")->Clone();
   probeMinDR[iMethod][iFolder]= (TH1F*) files[iMethod]->Get(folders[iFolder]+"/probeMinDR")->Clone();
   testControl[iMethod][iFolder]=(TH1F*) files[iMethod]->Get(folders[iFolder]+"/testControl")->Clone();
   testPt[iMethod][iFolder]=     (TH1F*) files[iMethod]->Get(folders[iFolder]+"/testPt")->Clone();
   testEta[iMethod][iFolder]=    (TH1F*) files[iMethod]->Get(folders[iFolder]+"/testEta")->Clone();
   testRelIso[iMethod][iFolder]=    (TH1F*) files[iMethod]->Get(folders[iFolder]+"/testRelIso")->Clone();
   testMult[iMethod][iFolder]=   (TH1F*) files[iMethod]->Get(folders[iFolder]+"/testMult")->Clone();
   testMinDR[iMethod][iFolder]=  (TH1F*) files[iMethod]->Get(folders[iFolder]+"/testMinDR")->Clone();
   effControl[iMethod][iFolder]= (TH1F*) files[iMethod]->Get(folders[iFolder]+"/effControl")->Clone();
   effPt[iMethod][iFolder]=      (TH1F*) files[iMethod]->Get(folders[iFolder]+"/effPt")->Clone();
   effEta[iMethod][iFolder]=     (TH1F*) files[iMethod]->Get(folders[iFolder]+"/effEta")->Clone();
   effRelIso[iMethod][iFolder]=     (TH1F*) files[iMethod]->Get(folders[iFolder]+"/effRelIso")->Clone();
   effMult[iMethod][iFolder]=    (TH1F*) files[iMethod]->Get(folders[iFolder]+"/effMult")->Clone();
   effMinDR[iMethod][iFolder]=   (TH1F*) files[iMethod]->Get(folders[iFolder]+"/effMinDR")->Clone();
   
   //optional recalculating of efficienies
   if(recalculateEffHistos == 1){
     //std::cout<<"Efficiency histos are recalculated"<<std::endl;
     effControl[iMethod][iFolder]->Reset();
     effPt[iMethod][iFolder]     ->Reset();
     effEta[iMethod][iFolder]    ->Reset();
     effRelIso[iMethod][iFolder]    ->Reset();
     effMult[iMethod][iFolder]   ->Reset();
     effMinDR[iMethod][iFolder]  ->Reset();
     effControl[iMethod][iFolder]-> Divide(testControl[iMethod][iFolder], probeControl[iMethod][iFolder], 1, 1, "B");
     effPt[iMethod][iFolder]     -> Divide(testPt[iMethod][iFolder], probePt[iMethod][iFolder], 1, 1, "B");
     effEta[iMethod][iFolder]    -> Divide(testEta[iMethod][iFolder], probeEta[iMethod][iFolder], 1, 1, "B");
     effRelIso[iMethod][iFolder]    -> Divide(testRelIso[iMethod][iFolder], probeRelIso[iMethod][iFolder], 1, 1, "B");
     effMult[iMethod][iFolder]   -> Divide(testMult[iMethod][iFolder], probeMult[iMethod][iFolder], 1, 1, "B");
     effMinDR[iMethod][iFolder]  -> Divide(testMinDR[iMethod][iFolder], probeMinDR[iMethod][iFolder], 1, 1, "B");
   }
 }
}

for(int iMethod=0; iMethod<methodNum; iMethod++){
 for(int iFolder=0; iFolder<folderNum; iFolder++) {
   ///calculate scale factors (SF)
   //if(iMethod!=idxSFnorm){}
   effSFControl[iMethod][iFolder] = (TH1F*)effControl[iMethod][iFolder]->Clone();
   effSFPt[iMethod][iFolder]      = (TH1F*)effPt[iMethod][iFolder]->Clone();
   effSFEta[iMethod][iFolder]     = (TH1F*)effEta[iMethod][iFolder]->Clone();
   effSFRelIso[iMethod][iFolder]     = (TH1F*)effRelIso[iMethod][iFolder]->Clone();
   effSFMult[iMethod][iFolder]    = (TH1F*)effMult[iMethod][iFolder]->Clone();
   effSFMinDR[iMethod][iFolder]   = (TH1F*)effMinDR[iMethod][iFolder]->Clone();
   effSFControl[iMethod][iFolder] -> Reset(); effSFControl[iMethod][iFolder]->SetTitle("effSF");
   effSFPt[iMethod][iFolder]      -> Reset(); effSFPt[iMethod][iFolder]->SetTitle("effSF pt");
   effSFRelIso[iMethod][iFolder]     -> Reset(); effSFEta[iMethod][iFolder]->SetTitle("effSF eta");
   effSFEta[iMethod][iFolder]     -> Reset(); effSFRelIso[iMethod][iFolder]->SetTitle("effSF phi");
   effSFMult[iMethod][iFolder]    -> Reset(); effSFMult[iMethod][iFolder]->SetTitle("effSF mult");
   effSFMinDR[iMethod][iFolder]   -> Reset(); effSFMinDR[iMethod][iFolder]->SetTitle("effSF minDR");
   effSFControl[iMethod][iFolder]->Divide(effControl[iMethod][iFolder], effControl[idxSFnorm][iFolder]);
   effSFPt[iMethod][iFolder]   ->Divide(effPt[iMethod][iFolder], effPt[idxSFnorm][iFolder]);
   effSFEta[iMethod][iFolder]  ->Divide(effEta[iMethod][iFolder], effEta[idxSFnorm][iFolder]);
   effSFRelIso[iMethod][iFolder]  ->Divide(effRelIso[iMethod][iFolder], effRelIso[idxSFnorm][iFolder]);
   effSFMult[iMethod][iFolder] ->Divide(effMult[iMethod][iFolder], effMult[idxSFnorm][iFolder]);
   effSFMinDR[iMethod][iFolder]->Divide(effMinDR[iMethod][iFolder], effMinDR[idxSFnorm][iFolder]);
   

   /// output of control plots
   std::cout<<methods[iMethod]<<" " <<folders[iFolder]
     <<" probe: "<<probeControl[iMethod][iFolder]->GetBinContent(1)
     <<" test: " <<testControl[iMethod][iFolder]->GetBinContent(1)
     <<" eff: "  <<100*effControl[iMethod][iFolder]->GetBinContent(1)
     <<" +/- "  <<100*effControl[iMethod][iFolder]->GetBinError(1)
     <<" eff SF: "  <<effSFControl[iMethod][iFolder]->GetBinContent(1)
     <<" +/- "  <<effSFControl[iMethod][iFolder]->GetBinError(1)
     <<std::endl;

   /// efficiency cross check: calculate total eff. from differential eff.
   double totalEffPt =0, totalProbePt=0, totalTestPt=0;
   double PtCut = 20;
   for (int iBin =1; iBin <= probePt[iMethod][iFolder]->GetNbinsX(); iBin++) {
     if(probePt[iMethod][iFolder]->GetBinCenter(iBin) > PtCut) {
       totalProbePt+=probePt[iMethod][iFolder]->GetBinContent(iBin);
       totalTestPt +=testPt [iMethod][iFolder]->GetBinContent(iBin);
     }
   }
   totalEffPt = totalTestPt / totalProbePt;
   
   double totalEffEta =0, totalProbeEta=0, totalTestEta=0;
   double EtaCut = 2.1;
   for (int iBin =1; iBin <= probeEta[iMethod][iFolder]->GetNbinsX(); iBin++) {
     if(fabs(probeEta[iMethod][iFolder]->GetBinCenter(iBin)) < EtaCut) {
       totalProbeEta+=probeEta[iMethod][iFolder]->GetBinContent(iBin);
       totalTestEta +=testEta [iMethod][iFolder]->GetBinContent(iBin);
     }
   }
   totalEffEta = totalTestEta / totalProbeEta;
   
   double totalEffRelIso =0;
   totalEffRelIso = testRelIso[iMethod][iFolder]->GetEntries() / probeRelIso[iMethod][iFolder]->GetEntries();
   
   double totalEffMult =0;
   totalEffMult  = testMult [iMethod][iFolder]->GetEntries() / probeMult [iMethod][iFolder]->GetEntries();
   
   double totalEffMinDR =0, totalProbeMinDR=0, totalTestMinDR=0;
   for (int iBin =1; iBin <= probeMinDR[iMethod][iFolder]->GetNbinsX(); iBin++) {
       totalProbeMinDR+=probeMinDR[iMethod][iFolder]->GetBinContent(iBin);
       totalTestMinDR +=testMinDR [iMethod][iFolder]->GetBinContent(iBin);
   }
   totalEffMinDR = totalTestMinDR / totalProbeMinDR;
   
   std::cout<<"Eff. comp.: control="<<effControl[iMethod][iFolder]->GetBinContent(1)
            <<"; pt="<<totalEffPt<<"; eta="<<totalEffEta<<"; phi="<<totalEffRelIso
            <<"; mult="<<totalEffMult<<"; minDR="<<totalEffMinDR<<std::endl;
 }  
}   

 /// Draw one Canvas for each folder comparing different methods.
 /// Each canvas shows test (1st row) and probe collection (2nd) and efficiency (3rd) for different variables (columns)
 TCanvas* CanvComp [folderNum];
 TCanvas* CanvSFComp [folderNum];
 TCanvas* CanvLeg = new TCanvas("CanvLeg", "CanvLeg", 350,200);
  /// Define histo and legend styles and options
  int lineStyle   []= {1,1,1,1,1};
  int lineColor   []= {2,1,4,kGreen+2,kGray+2};
  int markerStyle []={1,1,20,21,22,1};
  int markerColor []= {2,1,4,kGreen+2,kGray+2};
  TString drawOpt []= {"","E P same","E X0 P same","E X0 same","E X0 same","E same"};
  TString legOpt  []= {"L","L","P","P","P"};
  TLegend* leg [2*folderNum];//= new TLegend(0.6,0.6,0.8,0.8);
  bool legOnPlot = false;

for(int iFolder=0; iFolder<folderNum; iFolder++) {

  CanvComp[iFolder] = new TCanvas("Comparison"+folders[iFolder], "Comparison"+folders[iFolder], 1000,700);
  CanvSFComp[iFolder] = new TCanvas("Comparison SF "+folders[iFolder], "Comparison SF "+folders[iFolder], 1000,700);
  if(onlyEffPlots==1) CanvComp[iFolder]->Divide(3,2);
  else                CanvComp[iFolder]->Divide(6,3);
  CanvSFComp[iFolder]->Divide(3,2);
  
  for(int iMethod=0; iMethod<methodNum; iMethod++){
  
  if(onlyEffPlots==1){
    /// draw only eff plots
    if(iMethod==0){
      if(legOnPlot) leg[2*iFolder]=new TLegend(0.6,0.6,0.8,0.8);
      else leg[2*iFolder]=new TLegend(0,0,1,1);
    }
    leg[2*iFolder]->AddEntry(effMinDR[iMethod][iFolder],methods[iMethod],legOpt[iMethod]);
    
    CanvComp[iFolder]->cd(1);
    effControl[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    if(legOnPlot) leg[2*iFolder]->Draw();
    CanvComp[iFolder]->cd(2);
    effPt[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    if(legOnPlot) leg[2*iFolder]->Draw();
    CanvComp[iFolder]->cd(3);
    effEta[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    if(legOnPlot) leg[2*iFolder]->Draw();
    CanvComp[iFolder]->cd(4);
    effRelIso[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    if(legOnPlot) leg[2*iFolder]->Draw();
    CanvComp[iFolder]->cd(5);
    effMult[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    if(legOnPlot) leg[2*iFolder]->Draw();
    CanvComp[iFolder]->cd(6);
    effMinDR[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    if(legOnPlot) leg[2*iFolder]->Draw();
    
    /// draw eff SF plots
    CanvSFComp[iFolder]->cd(1);
    effSFControl[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    if(legOnPlot) leg[2*iFolder]->Draw();
    CanvSFComp[iFolder]->cd(2);
    effSFPt[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    if(legOnPlot) leg[2*iFolder]->Draw();
    CanvSFComp[iFolder]->cd(3);
    effSFEta[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    if(legOnPlot) leg[2*iFolder]->Draw();
    CanvSFComp[iFolder]->cd(4);
    effSFRelIso[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    if(legOnPlot) leg[2*iFolder]->Draw();
    CanvSFComp[iFolder]->cd(5);
    effSFMult[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    if(legOnPlot) leg[2*iFolder]->Draw();
    CanvSFComp[iFolder]->cd(6);
    effSFMinDR[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    if(iMethod==0) leg[2*iFolder+1]=new TLegend(0.6,0.6,0.8,0.8);
    leg[2*iFolder+1]->AddEntry(effMinDR[iMethod][iFolder],methods[iMethod],legOpt[iMethod]);
    if(legOnPlot) leg[2*iFolder+1]->Draw();
  }
  else {
    /// draw test, probe, eff plots
    //std::cout<<"onlyEffPlots==else start"<<std::endl;
    CanvComp[iFolder]->cd(1);
    testControl[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    CanvComp[iFolder]->cd(7);
    probeControl[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    CanvComp[iFolder]->cd(13);
    effControl[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    
    CanvComp[iFolder]->cd(2);
    testPt[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    CanvComp[iFolder]->cd(8);
    probePt[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    CanvComp[iFolder]->cd(14);
    effPt[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    
    CanvComp[iFolder]->cd(3);
    testEta[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    CanvComp[iFolder]->cd(9);
    probeEta[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    CanvComp[iFolder]->cd(15);
    effEta[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    
    CanvComp[iFolder]->cd(4);
    testRelIso[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    CanvComp[iFolder]->cd(10);
    probeRelIso[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    CanvComp[iFolder]->cd(16);
    effRelIso[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    
    CanvComp[iFolder]->cd(5);
    testMult[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    CanvComp[iFolder]->cd(11);
    probeMult[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    CanvComp[iFolder]->cd(17);
    effMult[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    
    CanvComp[iFolder]->cd(6);
    testMinDR[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    CanvComp[iFolder]->cd(12);
    probeMinDR[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    CanvComp[iFolder]->cd(18);
    effMinDR[iMethod][iFolder]->Draw(drawOpt[iMethod].Data());
    //std::cout<<"onlyEffPlots==else end"<<std::endl;
  }
  //if(iFolder==0) leg->AddEntry(effMinDR[iMethod][iFolder],methods[iMethod],legOpt[iMethod]);

  /// Set histo styles
  probeControl[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);
  probePt[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);   
  probeEta[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);
  probeRelIso[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]); 
  probeMult[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]); 
  probeMinDR[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);
  testControl[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);
  testPt[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);    
  testEta[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);   
  testRelIso[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);   
  testMult[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);  
  testMinDR[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]); 
  effControl[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);
  effPt[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);     
  effEta[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);    
  effRelIso[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);    
  effMult[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);   
  effMinDR[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);
  effSFControl[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);
  effSFPt[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);     
  effSFEta[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);    
  effSFRelIso[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);    
  effSFMult[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);   
  effSFMinDR[iMethod][iFolder]->SetLineStyle(lineStyle[iMethod]);  
  
  probeControl[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);
  probePt[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);   
  probeEta[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);
  probeRelIso[iMethod][iFolder]->SetLineColor(lineColor[iMethod]); 
  probeMult[iMethod][iFolder]->SetLineColor(lineColor[iMethod]); 
  probeMinDR[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);
  testControl[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);
  testPt[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);    
  testEta[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);   
  testRelIso[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);   
  testMult[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);  
  testMinDR[iMethod][iFolder]->SetLineColor(lineColor[iMethod]); 
  effControl[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);
  effPt[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);     
  effEta[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);    
  effRelIso[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);    
  effMult[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);   
  effMinDR[iMethod][iFolder]->SetLineColor(lineColor[iMethod]); 
  effSFControl[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);
  effSFPt[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);     
  effSFEta[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);    
  effSFRelIso[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);    
  effSFMult[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);   
  effSFMinDR[iMethod][iFolder]->SetLineColor(lineColor[iMethod]);  
  
  probeControl[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);
  probePt[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);   
  probeEta[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);
  probeRelIso[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]); 
  probeMult[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]); 
  probeMinDR[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);
  testControl[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);
  testPt[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);    
  testEta[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);   
  testRelIso[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);   
  testMult[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);  
  testMinDR[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]); 
  effControl[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]); 
  effPt[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);     
  effEta[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);    
  effRelIso[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);    
  effMult[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);   
  effMinDR[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]); 
  effSFControl[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]); 
  effSFPt[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);     
  effSFEta[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);    
  effSFRelIso[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);    
  effSFMult[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);   
  effSFMinDR[iMethod][iFolder]->SetMarkerStyle(markerStyle[iMethod]);  
  
  probeControl[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);
  probePt[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);   
  probeEta[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);
  probeRelIso[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]); 
  probeMult[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]); 
  probeMinDR[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);
  testControl[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);
  testPt[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);    
  testEta[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);   
  testRelIso[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);   
  testMult[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);  
  testMinDR[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]); 
  effControl[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);
  effPt[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);     
  effEta[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);    
  effRelIso[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);    
  effMult[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);   
  effMinDR[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);
  effSFControl[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);
  effSFPt[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);     
  effSFEta[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);    
  effSFRelIso[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);    
  effSFMult[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);   
  effSFMinDR[iMethod][iFolder]->SetMarkerColor(markerColor[iMethod]);

  effControl[iMethod][iFolder]->SetTitle(foldersTitle[iFolder]+" Overall Efficiency");
  effPt[iMethod][iFolder]->SetTitle(foldersTitle[iFolder]+" Efficiency");     
  effEta[iMethod][iFolder]->SetTitle(foldersTitle[iFolder]+" Efficiency");    
  effRelIso[iMethod][iFolder]->SetTitle(foldersTitle[iFolder]+" Efficiency");    
  effMult[iMethod][iFolder]->SetTitle(foldersTitle[iFolder]+" Efficiency");   
  effMinDR[iMethod][iFolder]->SetTitle(foldersTitle[iFolder]+" Efficiency");
  effSFControl[iMethod][iFolder]->SetTitle(foldersTitle[iFolder]+"Overall Scale Factor");
  effSFPt[iMethod][iFolder]->SetTitle(foldersTitle[iFolder]+" SF");     
  effSFEta[iMethod][iFolder]->SetTitle(foldersTitle[iFolder]+" SF");    
  effSFRelIso[iMethod][iFolder]->SetTitle(foldersTitle[iFolder]+" SF");    
  effSFMult[iMethod][iFolder]->SetTitle(foldersTitle[iFolder]+" SF");   
  effSFMinDR[iMethod][iFolder]->SetTitle(foldersTitle[iFolder]+" SF");
     
  effControl[iMethod][iFolder]->GetXaxis()->SetNdivisions(0);
  effRelIso[iMethod][iFolder]->GetXaxis()->SetNdivisions(505);
  effPt[iMethod][iFolder]->GetXaxis()->SetTitle("p_{T} [GeV]");     
  effEta[iMethod][iFolder]->GetXaxis()->SetTitle("#eta");    
  effRelIso[iMethod][iFolder]->GetXaxis()->SetTitle("RelIso");    
  effMult[iMethod][iFolder]->GetXaxis()->SetTitle("Jet Multiplicity");   
  effMinDR[iMethod][iFolder]->GetXaxis()->SetTitle("Minimum #DeltaR(#mu,jet)");
  
  effControl[iMethod][iFolder]->GetXaxis()->SetTitleSize(0.05);
  effPt[iMethod][iFolder]->GetXaxis()->SetTitleSize(0.05);     
  effEta[iMethod][iFolder]->GetXaxis()->SetTitleSize(0.05);    
  effRelIso[iMethod][iFolder]->GetXaxis()->SetTitleSize(0.05);    
  effMult[iMethod][iFolder]->GetXaxis()->SetTitleSize(0.05);   
  effMinDR[iMethod][iFolder]->GetXaxis()->SetTitleSize(0.05);
  
  effControl[iMethod][iFolder]->GetXaxis()->SetLabelSize(0.05);
  effPt[iMethod][iFolder]->GetXaxis()->SetLabelSize(0.05);     
  effEta[iMethod][iFolder]->GetXaxis()->SetLabelSize(0.05);    
  effRelIso[iMethod][iFolder]->GetXaxis()->SetLabelSize(0.05);    
  effMult[iMethod][iFolder]->GetXaxis()->SetLabelSize(0.05);   
  effMinDR[iMethod][iFolder]->GetXaxis()->SetLabelSize(0.05);
  
  effControl[iMethod][iFolder]->GetYaxis()->SetTitleSize(0.05);
  effPt[iMethod][iFolder]->GetYaxis()->SetTitleSize(0.05);     
  effEta[iMethod][iFolder]->GetYaxis()->SetTitleSize(0.05);    
  effRelIso[iMethod][iFolder]->GetYaxis()->SetTitleSize(0.05);    
  effMult[iMethod][iFolder]->GetYaxis()->SetTitleSize(0.05);   
  effMinDR[iMethod][iFolder]->GetYaxis()->SetTitleSize(0.05);
  
  effControl[iMethod][iFolder]->GetYaxis()->SetLabelSize(0.05);
  effPt[iMethod][iFolder]->GetYaxis()->SetLabelSize(0.05);     
  effEta[iMethod][iFolder]->GetYaxis()->SetLabelSize(0.05);    
  effRelIso[iMethod][iFolder]->GetYaxis()->SetLabelSize(0.05);    
  effMult[iMethod][iFolder]->GetYaxis()->SetLabelSize(0.05);   
  effMinDR[iMethod][iFolder]->GetYaxis()->SetLabelSize(0.05);

//   effControl[iMethod][iFolder]->GetYaxis()->SetTitle("Trigger Efficiency"); 
//   effPt[iMethod][iFolder]->GetYaxis()->SetTitle("TrEfficiency");     
//   effEta[iMethod][iFolder]->GetYaxis()->SetTitle("Efficiency");    
//   effRelIso[iMethod][iFolder]->GetYaxis()->SetTitle("Efficiency");    
//   effMult[iMethod][iFolder]->GetYaxis()->SetTitle("Efficiency");   
//   effMinDR[iMethod][iFolder]->GetYaxis()->SetTitle("Efficiency");
  
  effControl[iMethod][iFolder]->GetYaxis()->SetRangeUser(0.7,1);
  effPt[iMethod][iFolder]->GetYaxis()->SetRangeUser(0.7,1);
  effEta[iMethod][iFolder]->GetYaxis()->SetRangeUser(0.7,1);
  effRelIso[iMethod][iFolder]->GetYaxis()->SetRangeUser(0.7,1);
  effMult[iMethod][iFolder]->GetYaxis()->SetRangeUser(0.7,1);
  effMinDR[iMethod][iFolder]->GetYaxis()->SetRangeUser(0.7,1);
  
  effSFControl[iMethod][iFolder]->GetXaxis()->SetNdivisions(0);
  effSFRelIso[iMethod][iFolder]->GetXaxis()->SetNdivisions(505);
  effSFPt[iMethod][iFolder]->GetXaxis()->SetTitle("p_{T} [GeV]");     
  effSFEta[iMethod][iFolder]->GetXaxis()->SetTitle("#eta");    
  effSFRelIso[iMethod][iFolder]->GetXaxis()->SetTitle("RelIso");    
  effSFMult[iMethod][iFolder]->GetXaxis()->SetTitle("Jet Multiplicity");   
  effSFMinDR[iMethod][iFolder]->GetXaxis()->SetTitle("Minimum #DeltaR(#mu,jet)");
  
  effSFControl[iMethod][iFolder]->GetXaxis()->SetTitleSize(0.05);
  effSFPt[iMethod][iFolder]->GetXaxis()->SetTitleSize(0.05);     
  effSFEta[iMethod][iFolder]->GetXaxis()->SetTitleSize(0.05);    
  effSFRelIso[iMethod][iFolder]->GetXaxis()->SetTitleSize(0.05);    
  effSFMult[iMethod][iFolder]->GetXaxis()->SetTitleSize(0.05);   
  effSFMinDR[iMethod][iFolder]->GetXaxis()->SetTitleSize(0.05);
  
  effSFControl[iMethod][iFolder]->GetXaxis()->SetLabelSize(0.05);
  effSFPt[iMethod][iFolder]->GetXaxis()->SetLabelSize(0.05);     
  effSFEta[iMethod][iFolder]->GetXaxis()->SetLabelSize(0.05);    
  effSFRelIso[iMethod][iFolder]->GetXaxis()->SetLabelSize(0.05);    
  effSFMult[iMethod][iFolder]->GetXaxis()->SetLabelSize(0.05);   
  effSFMinDR[iMethod][iFolder]->GetXaxis()->SetLabelSize(0.05);
  
  effSFControl[iMethod][iFolder]->GetYaxis()->SetTitleSize(0.05);
  effSFPt[iMethod][iFolder]->GetYaxis()->SetTitleSize(0.05);     
  effSFEta[iMethod][iFolder]->GetYaxis()->SetTitleSize(0.05);    
  effSFRelIso[iMethod][iFolder]->GetYaxis()->SetTitleSize(0.05);    
  effSFMult[iMethod][iFolder]->GetYaxis()->SetTitleSize(0.05);   
  effSFMinDR[iMethod][iFolder]->GetYaxis()->SetTitleSize(0.05);
  
  effSFControl[iMethod][iFolder]->GetYaxis()->SetLabelSize(0.05);
  effSFPt[iMethod][iFolder]->GetYaxis()->SetLabelSize(0.05);     
  effSFEta[iMethod][iFolder]->GetYaxis()->SetLabelSize(0.05);    
  effSFRelIso[iMethod][iFolder]->GetYaxis()->SetLabelSize(0.05);    
  effSFMult[iMethod][iFolder]->GetYaxis()->SetLabelSize(0.05);   
  effSFMinDR[iMethod][iFolder]->GetYaxis()->SetLabelSize(0.05);
  
  effSFControl[iMethod][iFolder]->GetYaxis()->SetRangeUser(0.8,1.2);
  effSFPt[iMethod][iFolder]->GetYaxis()->SetRangeUser(0.8,1.2);
  effSFEta[iMethod][iFolder]->GetYaxis()->SetRangeUser(0.8,1.2);
  effSFRelIso[iMethod][iFolder]->GetYaxis()->SetRangeUser(0.8,1.2);
  effSFMult[iMethod][iFolder]->GetYaxis()->SetRangeUser(0.8,1.2);
  effSFMinDR[iMethod][iFolder]->GetYaxis()->SetRangeUser(0.8,1.2);
  
  
 }
 CanvLeg->cd();
 leg[0]->Draw();
 
 if(save){
   CanvComp[iFolder]->Print(outputFolder+outputFileName+folders[iFolder]+"_overview.png");
   CanvComp[iFolder]->cd(2)->Print(outputFolder+outputFileName+folders[iFolder]+"_Pt.png");
   CanvComp[iFolder]->cd(3)->Print(outputFolder+outputFileName+folders[iFolder]+"_Eta.png");
   CanvComp[iFolder]->cd(4)->Print(outputFolder+outputFileName+folders[iFolder]+"_RelIso.png");
   CanvComp[iFolder]->cd(5)->Print(outputFolder+outputFileName+folders[iFolder]+"_Njets.png");
   CanvComp[iFolder]->cd(6)->Print(outputFolder+outputFileName+folders[iFolder]+"_DeltaR.png");
   CanvSFComp[iFolder]->Print(outputFolder+outputFileName+folders[iFolder]+"_SF_overview.png");
   CanvSFComp[iFolder]->cd(2)->Print(outputFolder+outputFileName+folders[iFolder]+"_SF_Pt.png");
   CanvSFComp[iFolder]->cd(3)->Print(outputFolder+outputFileName+folders[iFolder]+"_SF_Eta.png");
   CanvSFComp[iFolder]->cd(4)->Print(outputFolder+outputFileName+folders[iFolder]+"_SF_RelIso.png");
   CanvSFComp[iFolder]->cd(5)->Print(outputFolder+outputFileName+folders[iFolder]+"_SF_Njets.png");
   CanvSFComp[iFolder]->cd(6)->Print(outputFolder+outputFileName+folders[iFolder]+"_SF_DeltaR.png");
   CanvLeg->Print(outputFolder+outputFileName+"_Legend.png");
   std::cout<<"Canvas with plots is saved in "<<outputFolder<<std::endl;
 }
 }
}
