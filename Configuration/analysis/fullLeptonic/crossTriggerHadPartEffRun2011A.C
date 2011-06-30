// This macro calculates the efficiency of the hadronic part of a lepton-hadron cross-trigger,
// e.g. of the TriCentralJet30 part wrt Mu17 for the HLT_Mu17_TriCentralJet30 trigger

#include <iostream>
#include "TH1.h"
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"

void crossTriggerHadPartEffRun2011A(bool save=false)
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
  TString outputFolder   = "/afs/desy.de/user/j/jlange/analysis/tagAndProbe/plots/2011";
  TString outputFileName = "/triggerEffHadPartMu15_Mu17-TriJet30_MinJet3_3rdJet";
  //TString outputFileName = "/triggerEffHadPartMu15_Mu17-TriJet30_MinJet4_4thJet";
 
  /// if set to 0: all plots (probe, test, eff) are drawn; to 1: only eff plots
  int onlyEffPlots =1;

  /// definition of methods (e.g. Tag and Probe MC tapMC, tapData, ...
  const int methodNum=1;
  //TString methods[methodNum]={"tapMC"};
  TString methods[100]={"Control trigger: Mu15","Control trigger: Mu17emu" ,"Control trigger: Mu20","2010B2 Mu15","Z genMu match Mu9"};
  TFile* files[100];
  /*files[0]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeRun2011Av2_HLT_Mu15_Mu17TriJet_cfg/analyzeZMuMuTagAndProbeRun2011Acomb_HLT_Mu15_Mu17TriJet.root",inputPath)); /// Tag and Probe from data
  files[1]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeRun2011Av2_HLT_Mu17emu_Mu17TriJet_cfg/analyzeZMuMuTagAndProbeRun2011Acomb_HLT_Mu17emu_Mu17TriJet.root",inputPath)); /// Tag and Probe from data
  files[2]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeRun2011Av2_HLT_Mu20_Mu17TriJet_cfg/analyzeZMuMuTagAndProbeRun2011Acomb_HLT_Mu20_Mu17TriJet.root",inputPath));*/ /// Tag and Probe from data
  
  files[0]=new TFile(Form("%s/naf_analyzeZMuMuTagAndProbeRun2011Av2_HLT_Mu15_Mu17TriJet_JetMin3_cfg/analyzeZMuMuTagAndProbeRun2011Acomb_HLT_Mu15_Mu17TriJet_JetMin3.root",inputPath)); /// Tag and Probe from data

  /// different tap studies (different efficiencies)
  const int folderNum=2;
  TString folders[]={"analyzeJet2Trig1AfterCut", "analyzeJet2Trig2AfterCut"};
  //TString folders[]={"analyzeJet3Trig1AfterCut", "analyzeJet3Trig2AfterCut"};
 
  TH1F* nControl [methodNum][folderNum];
  TH1F* nNjets   [methodNum][folderNum];
  TH1F* nPt      [methodNum][folderNum];
  TH1F* nEta     [methodNum][folderNum];
  TH1F* effControl [methodNum];
  TH1F* effNjets   [methodNum];
  TH1F* effPt      [methodNum];
  TH1F* effEta     [methodNum];

for(int iMethod=0; iMethod<methodNum; iMethod++){
 for(int iFolder=0; iFolder<folderNum; iFolder++) {
   nNjets  [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(folders[iFolder]+"/n")->Clone();
   nNjets  [iMethod][iFolder]->Sumw2();
   nPt [iMethod][iFolder] = (TH1F*) files[iMethod]->Get(folders[iFolder]+"/pt")->Clone();
   nPt  [iMethod][iFolder]->Sumw2();
   nEta[iMethod][iFolder] = (TH1F*) files[iMethod]->Get(folders[iFolder]+"/eta")->Clone();
   //change the binning
   double newBins[] = {-3.5,-2.4,-1.8,-1.2,-0.6,0.,0.6,1.2,1.8,2.4,3.5};
   nEta  [iMethod][iFolder] = (TH1F*) nEta  [iMethod][iFolder]->
       Rebin(10,Form("%s_new",nEta[iMethod][iFolder]->GetName()),newBins);
   nEta  [iMethod][iFolder]->Sumw2();
   nControl[iMethod][iFolder] = new TH1F ("control"+methods[iMethod]+folders[iFolder],"control", 1,0,2 );
   nControl[iMethod][iFolder]->Sumw2();
   for(int i=0; i<nPt [iMethod][iFolder]->GetEntries(); i++) nControl[iMethod][iFolder]->Fill(1);
 }

   effNjets[iMethod] = (TH1F*) nNjets [iMethod][0]->Clone();
   effPt[iMethod]    = (TH1F*) nPt    [iMethod][0]->Clone();
   effEta[iMethod]   = (TH1F*) nEta   [iMethod][0]->Clone();
   effControl[iMethod]   = (TH1F*) nControl   [iMethod][0]->Clone();
     effNjets[iMethod]  ->Reset();
     effPt[iMethod]     ->Reset();
     effEta[iMethod]    ->Reset();
     effControl[iMethod]->Reset();
     effNjets[iMethod]  -> Divide(nNjets[iMethod][1],   nNjets[iMethod][0], 1, 1, "B");
     effPt[iMethod]     -> Divide(nPt[iMethod][1],      nPt[iMethod][0], 1, 1, "B");
     effEta[iMethod]    -> Divide(nEta[iMethod][1],     nEta[iMethod][0], 1, 1, "B");
     effControl[iMethod]-> Divide(nControl[iMethod][1], nControl[iMethod][0], 1, 1, "B");
     //effNjets[iMethod]  -> SetTitle("Trigger Efficiency Mu17_TriCentralJet30 (1 #mu, #geq 4 PF jets)");
     //effPt[iMethod]     -> SetTitle("Trigger Efficiency Mu17_TriCentralJet30 (1 #mu, #geq 4 PF jets), 4th jet");
     //effEta[iMethod]    -> SetTitle("Trigger Efficiency Mu17_TriCentralJet30 (1 #mu, #geq 4 PF jets), 4th jet");
     //effControl[iMethod]-> SetTitle("Trigger Efficiency Mu17_TriCentralJet30 (1 #mu, #geq 4 PF jets)");
     effNjets[iMethod]  -> SetTitle("Trigger Efficiency Mu17_TriCentralJet30 (1 #mu, #geq 3 PF jets)");
     effPt[iMethod]     -> SetTitle("Trigger Efficiency Mu17_TriCentralJet30 (1 #mu, #geq 3 PF jets), 3rd jet");
     effEta[iMethod]    -> SetTitle("Trigger Efficiency Mu17_TriCentralJet30 (1 #mu, #geq 3 PF jets), 3rd jet");
     effControl[iMethod]-> SetTitle("Trigger Efficiency Mu17_TriCentralJet30 (1 #mu, #geq 3 PF jets)");



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
   for (int iBin =1; iBin <= nPt[iMethod][0]->GetNbinsX(); iBin++) {
     if(nPt[iMethod][0]->GetBinCenter(iBin) > PtCut) {
       totalProbePt+=nPt[iMethod][0]->GetBinContent(iBin);
       totalTestPt +=nPt[iMethod][1]->GetBinContent(iBin);
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
  int lineStyle   []= {1,1,1,1};
  int lineColor   []= {2,1,4,kGreen+2,kGray+2};
  int markerStyle []={1,20,21,22,1};
  int markerColor []= {2,1,4,kGreen+2,kGray+2};
  TString drawOpt []= {"","E X0 P same","E X0 P same","E X0 same","E same"};
  TString legOpt  []= {"L","P","P","P","L"};
  double setRangeUserLow = 0.5;

  TCanvas* CanvComp = new TCanvas("Comparison", "Comparison", 1200,900);
  TCanvas* CanvLeg = new TCanvas("CanvLeg", "CanvLeg", 1);
  if(onlyEffPlots) CanvComp ->Divide(2,2);
  else             CanvComp ->Divide(4,2);
  TLegend* leg=new TLegend(0.45,0.16,0.87,0.48);
  //TLegend* leg=new TLegend(0.4,0.2,0.85,0.6);
  
  for(int iMethod=0; iMethod<methodNum; iMethod++){
  /// Set histo styles
  effControl[iMethod] ->SetLineStyle(lineStyle[iMethod]);     
  effPt[iMethod] ->SetLineStyle(lineStyle[iMethod]);     
  effEta[iMethod]->SetLineStyle(lineStyle[iMethod]);    
  effNjets[iMethod]->SetLineStyle(lineStyle[iMethod]);
      
  effControl[iMethod] ->SetLineColor(lineColor[iMethod]);     
  effPt[iMethod] ->SetLineColor(lineColor[iMethod]);     
  effEta[iMethod]->SetLineColor(lineColor[iMethod]);    
  effNjets[iMethod]->SetLineColor(lineColor[iMethod]);
     
  effControl[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);     
  effPt[iMethod] ->SetMarkerStyle(markerStyle[iMethod]);     
  effEta[iMethod]->SetMarkerStyle(markerStyle[iMethod]);    
  effNjets[iMethod]->SetMarkerStyle(markerStyle[iMethod]);
  
  effControl[iMethod]   ->SetMarkerColor(markerColor[iMethod]);     
  effPt[iMethod]   ->SetMarkerColor(markerColor[iMethod]);     
  effEta[iMethod]  ->SetMarkerColor(markerColor[iMethod]);    
  effNjets[iMethod]->SetMarkerColor(markerColor[iMethod]);
  
  effControl[iMethod]   ->GetYaxis()->SetRangeUser(setRangeUserLow,1);     
  effPt[iMethod]   ->GetYaxis()->SetRangeUser(setRangeUserLow,1);    
  effEta[iMethod]  ->GetYaxis()->SetRangeUser(setRangeUserLow,1);
  effNjets[iMethod]->GetYaxis()->SetRangeUser(setRangeUserLow,1);
  
  effPt[iMethod]   ->GetXaxis()->SetRangeUser(0,150);
  effNjets[iMethod]->GetXaxis()->SetRangeUser(0,10);
     
  effControl[iMethod]->GetXaxis()->SetNdivisions(0);
  effControl[iMethod]->GetXaxis()->SetTitle("Overall"); 
  effPt[iMethod]->GetXaxis()->SetTitle("p_{T} [GeV]");     
  effEta[iMethod]->GetXaxis()->SetTitle("#eta");    
  effNjets[iMethod]->GetXaxis()->SetTitle("Jet Multiplicity");    
  
  effPt[iMethod]      ->GetXaxis()->SetTitleSize(0.05);     
  effEta[iMethod]      ->GetXaxis()->SetTitleSize(0.05);    
  effNjets[iMethod]   ->GetXaxis()->SetTitleSize(0.05);
  
  effPt[iMethod]   ->GetXaxis()->SetLabelSize(0.05);
  effEta[iMethod]  ->GetXaxis()->SetLabelSize(0.05);     
  effNjets[iMethod]->GetXaxis()->SetLabelSize(0.05);    
  
  effPt[iMethod]    ->GetYaxis()->SetTitleSize(0.05);
  effEta[iMethod]   ->GetYaxis()->SetTitleSize(0.05);     
  effNjets[iMethod] ->GetYaxis()->SetTitleSize(0.05);    

  effPt[iMethod]   ->GetYaxis()->SetLabelSize(0.05);
  effEta[iMethod]  ->GetYaxis()->SetLabelSize(0.05);     
  effNjets[iMethod]->GetYaxis()->SetLabelSize(0.05);
  
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
      effPt[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      CanvComp->cd(4);
      effEta[iMethod]->Draw(drawOpt[iMethod].Data());
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
	nPt[iMethod][0]->Draw("hist");
	nPt[iMethod][1]->Draw("same hist");
	nPt[iMethod][0]->GetXaxis()->SetRangeUser(0,150);
	nPt[iMethod][1]->SetLineStyle(2);
	nPt[iMethod][1]->SetLineColor(4);
	nPt[iMethod][0]->GetXaxis()->SetTitleSize(0.05);
	nPt[iMethod][0]->GetXaxis()->SetTitle("p_{T} [GeV]");
	nPt[iMethod][0]->GetXaxis()->SetLabelSize(0.05);
	nPt[iMethod][0]->GetYaxis()->SetTitleSize(0.05);
	nPt[iMethod][0]->GetYaxis()->SetLabelSize(0.05);
	//leg2->Draw();
	CanvComp->cd(4);
	nEta[iMethod][0]->Draw("hist");
	nEta[iMethod][1]->Draw("same hist");
	nEta[iMethod][1]->SetLineStyle(2);
	nEta[iMethod][1]->SetLineColor(4);
	nEta[iMethod][0]->GetXaxis()->SetTitle("#eta");
	nEta[iMethod][0]->GetXaxis()->SetTitleSize(0.05);
	nEta[iMethod][0]->GetXaxis()->SetLabelSize(0.05);
	nEta[iMethod][0]->GetYaxis()->SetTitleSize(0.05);
	nEta[iMethod][0]->GetYaxis()->SetLabelSize(0.05);
        //leg2->Draw();
      }
      effPt[iMethod]   ->SetTitle("Trigger Efficiency");     
      effEta[iMethod]  ->SetTitle("Trigger Efficiency");    
      effNjets[iMethod]->SetTitle("Trigger Efficiency");
      effControl[iMethod]->SetTitle("Trigger Efficiency");    
      
      CanvComp->cd(5);
      effControl[iMethod]->Draw(drawOpt[iMethod].Data());
      leg->Draw();
      CanvComp->cd(6);
      effNjets[iMethod]->Draw(drawOpt[iMethod].Data());
      //leg->Draw();
      CanvComp->cd(7);
      effPt[iMethod]->Draw(drawOpt[iMethod].Data());
      //leg->Draw();
      CanvComp->cd(8);
      effEta[iMethod]->Draw(drawOpt[iMethod].Data());
      //leg->Draw();
    }
    CanvLeg->cd();
    leg->Draw();
    if(save){
      CanvComp->Print(outputFolder+outputFileName+"_overview.png");
      CanvComp->cd(2)->Print(outputFolder+outputFileName+"_Njets.png");
      CanvComp->cd(3)->Print(outputFolder+outputFileName+"_Pt.png");
      CanvComp->cd(4)->Print(outputFolder+outputFileName+"_Eta.png");
      CanvLeg->Print(outputFolder+outputFileName+"_Legend.png");
      std::cout<<"Canvas with plots is saved in "<<outputFolder<<std::endl;
    }
    

 //leg->Draw();
  }
}
