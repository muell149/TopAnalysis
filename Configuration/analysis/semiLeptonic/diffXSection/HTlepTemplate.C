#include <iostream>
#include <iomanip>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include "TROOT.h"
#include "TFile.h"
#include "TH2.h"
#include "TF1.h"
#include "TTree.h"
#include "TLegend.h"
#include "THStack.h"
#include "TMath.h"

using namespace std;
TH1F* HTlep_ttbar;
TH1F* HTlep_wjets;
TH1F* HTlep_zjets;
TH1F* HTlep_antiRelIso;
TH1F* HTlep_qcd;
TH1F* HTlep_qcdAnti;
TH1F* HTlep_qcdFit;
TH1F* HTlep_fitHisto;

enum sample {kData, kWjets, kZjets, kQCD, kTTbar};

Double_t ttbarFit(Double_t *x, Double_t *par);
Double_t wjetsFit(Double_t *x, Double_t *par);
Double_t zjetsFit(Double_t *x, Double_t *par);
Double_t AntiRelIsoFit(Double_t *x, Double_t *par);
Double_t fitFunction(Double_t *x, Double_t *par);

void HTlepTemplate(Int_t jetNumber = 1, TString qcdTyp = "Data", Double_t zFix = 1., double includeTTbar = 1., TString particleFlow = "", TString lowerBound = "0.5", TString upperBound = "2.0")
{
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);

  TString templateVar = "HTlep"; // "MT";
  bool simplyDrawQCD = false; // true;
  //TString particleFlow = "Pf";
  //bool includeTTbar = false;
  //int jetNumber = 1;
  double upperFitEdge = 150.+jetNumber*50.;
  if(templateVar=="MT")upperFitEdge=160.;
  //TString qcdTyp = "Data"; // "mc"; // "mcAnti";
  //double lumi = 10.927;
  //double lumi = 15.078;
  //double lumi = 21.885;
  double lumi = 34.716;
  int binWidth = 1.;
  if(jetNumber)binWidth = 5.*jetNumber;
  int numberOfParameters = 4;
  //if(includeTTbar)numberOfParameters = 4;
  if(simplyDrawQCD)upperFitEdge=100.+jetNumber*10.;

  std::vector<TString> whichSample;
  for(int i=0; i<=numberOfParameters; i++){
    if(i==kData)whichSample.push_back("_data");
    if(i==kWjets)whichSample.push_back("_wjets");
    if(i==kZjets)whichSample.push_back("_zjets");
    if(i==kQCD)whichSample.push_back("_qcd");
    if(i==kTTbar)whichSample.push_back("_ttbar");
  }

  int numberOfBins = int(upperFitEdge/binWidth);
  TString numberOfJets = ""; numberOfJets+=jetNumber;

  std::vector<TFile*> files_;
  for(UInt_t i = 0; i < whichSample.size(); i++){
    files_.push_back(new TFile("HTlep"+whichSample[i]+".root"  ) );
  }

  vector<TTree*> tree;
  for(UInt_t i = 0; i < whichSample.size(); i++){
    tree.push_back((TTree*)files_[i]->Get("HTlep"+particleFlow+numberOfJets+"/HTleptree"));
  }

  vector<TTree*> treeTemp;
  for(UInt_t i = 0; i < whichSample.size(); i++){
    treeTemp.push_back((TTree*)files_[i]->Get("HTlepTemplate"+particleFlow+numberOfJets+"/HTleptree"));
  }

  TCanvas *canv2 = new TCanvas("canv2","HTlepTemplate",10,10,900,500);
  //canv->Divide(1,1);
  canv2->cd(1);
  canv2->cd(1)->SetBottomMargin(0.14);
  TH1F* axisHist = new TH1F("axisHist","axisHist",1,15.,upperFitEdge);
  TH1F* HTlep = new TH1F("HTlep","HTlep",numberOfBins,20.,upperFitEdge);
  HTlep_antiRelIso = new TH1F("HTlep_antiRelIso","HTlep_antiRelIso",numberOfBins,20.,upperFitEdge);
  HTlep_wjets = new TH1F("HTlep_wjets","HTlep_wjets",numberOfBins,20.,upperFitEdge);
  HTlep_zjets = new TH1F("HTlep_zjets","HTlep_zjets",numberOfBins,20.,upperFitEdge);
  HTlep_qcd = new TH1F("HTlep_qcd","HTlep_qcd",numberOfBins,20.,upperFitEdge);
  HTlep_qcdAnti = new TH1F("HTlep_qcdAnti","HTlep_qcdAnti",numberOfBins,20.,upperFitEdge);
  HTlep_qcdFit = new TH1F("HTlep_qcdFit","HTlep_qcdFit",numberOfBins,20.,upperFitEdge);
  HTlep_ttbar = new TH1F("HTlep_ttbar","HTlep_ttbar",numberOfBins,20.,upperFitEdge);

  tree[kData]->Draw(templateVar+">>HTlep","relIso<0.05","0");
  treeTemp[kData]->Draw(templateVar+">>HTlep_antiRelIso","relIso>"+lowerBound+" && relIso<"+upperBound,"0");
  tree[kWjets]->Draw(templateVar+">>HTlep_wjets","relIso<0.05","0");
  tree[kZjets]->Draw(templateVar+">>HTlep_zjets","relIso<0.05","0");
  tree[kQCD]->Draw(templateVar+">>HTlep_qcd","relIso<0.05","0");
  treeTemp[kQCD]->Draw(templateVar+">>HTlep_qcdAnti","relIso>"+lowerBound+" && relIso<"+upperBound,"0");
  if(qcdTyp=="Data")treeTemp[kData]->Draw(templateVar+">>HTlep_qcdFit","relIso>"+lowerBound+" && relIso<"+upperBound,"0");
  else if(qcdTyp=="mc")tree[kQCD]->Draw(templateVar+">>HTlep_qcdFit","relIso<0.05","0");
  else if(qcdTyp=="mcAnti")treeTemp[kQCD]->Draw(templateVar+">>HTlep_qcdFit","relIso>"+lowerBound+" && relIso<"+upperBound,"0");
  else std::cout<<"zonk"<<std::endl;
  tree[kTTbar]->Draw(templateVar+">>HTlep_ttbar","relIso<0.05","0");

  int smooth = 0;
  HTlep->SetMarkerStyle(20);
  HTlep_antiRelIso->Scale((lumi*0.910264515/50.0)*HTlep_qcd->Integral(1,numberOfBins)/HTlep_antiRelIso->Integral(1,numberOfBins));
  HTlep_antiRelIso->Smooth(smooth);
  HTlep_wjets->Scale(lumi*0.155498692/50.0);
  HTlep_wjets->Smooth(smooth);
  HTlep_zjets->Scale(lumi*0.140471057/50.0);
  HTlep_zjets->Smooth(smooth);
  HTlep_ttbar->Scale(lumi*0.005308736/50.0);
  HTlep_ttbar->Smooth(smooth);
  HTlep_qcdAnti->Scale((lumi*0.910264515/50.0)*HTlep_qcd->Integral(1,numberOfBins)/HTlep_qcdAnti->Integral(1,numberOfBins));
  HTlep_qcdAnti->Smooth(smooth);
  HTlep_qcdFit->Scale((lumi*0.910264515/50.0)*HTlep_qcd->Integral(1,numberOfBins)/HTlep_qcdFit->Integral(1,numberOfBins));
  HTlep_qcdFit->Smooth(smooth);
  HTlep_qcd->Scale(lumi*0.910264515/50.0);
  HTlep_qcd->Smooth(smooth);

  TF1* mixFunction = new TF1("fitFunction",fitFunction,20.-(20%binWidth),upperFitEdge-0.0001,numberOfParameters);
  for(int i=0; i<numberOfParameters; i++){
    mixFunction->SetParameter(i,1.);
    mixFunction->SetParLimits(i,0.,100.);
    mixFunction->SetParName(i,"Scale"+whichSample[i+1]);
  }
  if(zFix>=0)mixFunction->FixParameter(kZjets-1,zFix);
  if(includeTTbar>=0)mixFunction->FixParameter(kTTbar-1,includeTTbar);


  HTlep->Fit(mixFunction,"0LQ");

  axisHist->GetXaxis()->SetTitle("H_{T}^{lep} [GeV]");
  axisHist->GetYaxis()->SetTitle("Events");
  axisHist->GetXaxis()->SetLabelSize(0.06);
  axisHist->GetYaxis()->SetLabelSize(0.06);
  axisHist->GetXaxis()->SetTitleSize(0.06);
  axisHist->GetYaxis()->SetTitleSize(0.06);
  axisHist->GetYaxis()->SetTitleOffset(0.9);

  HTlep_antiRelIso->Scale(mixFunction->GetParameter(kQCD-1));
  HTlep_wjets->Scale(mixFunction->GetParameter(kWjets-1));
  HTlep_ttbar->Scale(mixFunction->GetParameter(kTTbar-1));
  HTlep_zjets->Scale(mixFunction->GetParameter(kZjets-1)*mixFunction->GetParameter(kWjets-1));
  HTlep_qcd->Scale(mixFunction->GetParameter(kQCD-1));
  HTlep_qcdAnti->Scale(mixFunction->GetParameter(kQCD-1));
  HTlep_qcdFit->Scale(mixFunction->GetParameter(kQCD-1));
  for(int i=1; i<=numberOfBins; i++){
    HTlep_fitHisto = (TH1F*)HTlep_wjets->Clone();
    HTlep_fitHisto->Add(HTlep_ttbar);
    HTlep_fitHisto->Add(HTlep_zjets);
    HTlep_fitHisto->Add(HTlep_qcdFit);
  }

  if(simplyDrawQCD){
    axisHist->SetMaximum(HTlep_qcd->GetMaximum()*1.1);
    axisHist->DrawClone("axis");
  }
  else{
    axisHist->SetMaximum((HTlep->GetMaximum()+sqrt(HTlep->GetMaximum()))*1.1);
    axisHist->DrawClone("axis");
    HTlep->DrawClone("e1 X0 same");
    HTlep_fitHisto->SetLineWidth(3);
    HTlep_fitHisto->DrawClone("C same");
  }

  //HTlep_antiRelIso->SetLineStyle(2);
  HTlep_antiRelIso->SetLineWidth(2);
  HTlep_antiRelIso->SetLineColor(kYellow+1);
  //if(!simplyDrawQCD)HTlep_antiRelIso->DrawClone("same");
  if(simplyDrawQCD)HTlep_antiRelIso->DrawClone("same e");

  HTlep_wjets->SetLineStyle(3);
  HTlep_wjets->SetLineWidth(2);
  HTlep_wjets->SetLineColor(kGreen-3);
  if(!simplyDrawQCD)HTlep_wjets->DrawClone("same");

  HTlep_ttbar->SetLineStyle(2);
  HTlep_ttbar->SetLineWidth(2);
  HTlep_ttbar->SetLineColor(kRed+1);
  if(includeTTbar!=0. && !simplyDrawQCD)HTlep_ttbar->DrawClone("same");

  HTlep_zjets->SetLineStyle(4);
  HTlep_zjets->SetLineWidth(2);
  HTlep_zjets->SetLineColor(kAzure-2);
  if(!simplyDrawQCD)HTlep_zjets->DrawClone("same");

  //HTlep_qcd->SetLineStyle(2);
  HTlep_qcd->SetLineWidth(2);
  //HTlep_qcd->SetLineColor(kYellow+1);
  HTlep_qcd->SetLineColor(kPink);
  //if(!simplyDrawQCD)HTlep_qcd->DrawClone("same");
  if(simplyDrawQCD)HTlep_qcd->DrawClone("same e");

  //HTlep_qcdAnti->SetLineStyle(2);
  HTlep_qcdAnti->SetLineWidth(2);
  HTlep_qcdAnti->SetLineColor(kOrange);
  //if(!simplyDrawQCD)HTlep_qcdAnti->DrawClone("same");
  if(simplyDrawQCD)HTlep_qcdAnti->DrawClone("same e");

  HTlep_qcdFit->SetLineWidth(2);
  HTlep_qcdFit->SetLineColor(kYellow+1);
  if(!simplyDrawQCD)HTlep_qcdFit->DrawClone("same");

  TString qcdfracstrg;
  Char_t mychar[10];
  double fullScale = mixFunction->GetParameter(kWjets-1)*HTlep_wjets->Integral()/(lumi*0.155498692/50.0)+mixFunction->GetParameter(kQCD-1)*HTlep_qcdFit->Integral()/(lumi*0.910264515/50.0)+mixFunction->GetParameter(kZjets-1)*HTlep_zjets->Integral()/(lumi*0.140471057/50.0)+mixFunction->GetParameter(kTTbar-1)*HTlep_ttbar->Integral()/(lumi*0.005308736/50.0);
  //double fullScale = mixFunction->GetParameter(0)+mixFunction->GetParameter(1)+mixFunction->GetParameter(2);
  double qcdfrac = mixFunction->GetParameter(kQCD-1)*(HTlep_qcdFit->Integral()/(lumi*0.910264515/50.0))/fullScale;
  double qcdfracError = mixFunction->GetParError(kQCD-1)*(HTlep_qcdFit->Integral()/(lumi*0.910264515/50.0))/fullScale;
  sprintf(mychar,"%1.1f #pm %1.1f",100*qcdfrac,100*qcdfracError);
  qcdfracstrg=mychar;
  Char_t mychar2[10];
  TString mylumi;
  sprintf(mychar2,"%1.0f",lumi);
  mylumi=mychar2;

  TLegend *leg = new TLegend(0.53, 0.4, 0.97, 0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.06);
  leg->SetHeader("#geq"+numberOfJets+" jets");
  if(!simplyDrawQCD){
    leg->AddEntry( HTlep,  "Data ("+mylumi+"pb^{-1})", "PL" );
    //leg->AddEntry( HTlep_antiRelIso, "QCD antiIso (Data)", "L" );
    //leg->AddEntry( HTlep_qcd, "QCD signal (MC)", "L" );
    //leg->AddEntry( HTlep_qcdAnti, "QCD antiIso (MC)", "L" );
    leg->AddEntry( HTlep_qcdFit, "QCD", "L" );
    leg->AddEntry( HTlep_wjets, "W+jets", "L" );
    leg->AddEntry( HTlep_zjets, "Z+jets", "L" );
    if(includeTTbar!=0.)leg->AddEntry( HTlep_ttbar, "t#bar{t}", "L" );
    leg->AddEntry( mixFunction, "Fit", "L" );
  }
  else{
    leg->AddEntry( HTlep_antiRelIso, "QCD antiIso region (Data)", "L" );
    //leg->AddEntry( HTlep_antiRelIso, "QCD AntiRelIso (Data) "+qcdfracstrg+"%", "L" );
    leg->AddEntry( HTlep_qcd, "QCD signal region (MC)", "L" );
    leg->AddEntry( HTlep_qcdAnti, "QCD antiIso region (MC)", "L" );
    leg->SetX1(0.4);
    leg->SetY1(0.55);
  }
  leg->Draw("same");

  std::cout<<"qcd scale: "<<setprecision(3)<<mixFunction->GetParameter(kQCD-1)<<" $\\pm$ "<<setprecision(2)<<mixFunction->GetParError(kQCD-1)<<std::endl;
  std::cout<<"wjets scale: "<<setprecision(3)<<mixFunction->GetParameter(kWjets-1)<<" +- "<<setprecision(2)<<mixFunction->GetParError(kWjets-1)<<std::endl;
  std::cout<<"zjets scale: "<<setprecision(3)<<mixFunction->GetParameter(kZjets-1)<<" +- "<<setprecision(2)<<mixFunction->GetParError(kZjets-1)<<std::endl;
  std::cout<<"ttbar scale: "<<setprecision(3)<<mixFunction->GetParameter(kTTbar-1)<<" +- "<<setprecision(2)<<mixFunction->GetParError(kTTbar-1)<<std::endl;

  //std::cout<<"QCD fraction: "<<qcdfrac<<" +- "<<qcdfracError<<std::endl;
  axisHist->Reset();
  HTlep->Reset();
  HTlep_ttbar->Reset();
  HTlep_wjets->Reset();
  HTlep_zjets->Reset();
  HTlep_antiRelIso->Reset();
  HTlep_qcd->Reset();
  HTlep_qcdAnti->Reset();
  HTlep_qcdFit->Reset();
}

Double_t ttbarFit(Double_t *x, Double_t *par)
{
  Double_t arg = 0;
  arg = HTlep_ttbar->GetBinContent(HTlep_ttbar->GetXaxis()->FindBin(x[0]));
  Double_t fitval4 = 0;
  fitval4 = par[0]*arg;
  return fitval4;
}

Double_t wjetsFit(Double_t *x, Double_t *par)
{
  Double_t arg = 0;
  arg = HTlep_wjets->GetBinContent(HTlep_wjets->GetXaxis()->FindBin(x[0]));
  Double_t fitval1 = 0;
  fitval1 = par[0]*arg;
  return fitval1;
}

Double_t zjetsFit(Double_t *x, Double_t *par)
{
  Double_t arg = 0;
  arg = HTlep_zjets->GetBinContent(HTlep_zjets->GetXaxis()->FindBin(x[0]));
  Double_t fitval2 = 0;
  fitval2 = par[0]*arg;
  return fitval2;
}

Double_t AntiRelIsoFit(Double_t *x, Double_t *par)
{
  Double_t arg = 0;
  arg = HTlep_qcdFit->GetBinContent(HTlep_qcdFit->GetXaxis()->FindBin(x[0]));
  Double_t fitval3 = 0;
  fitval3 = par[0]*arg;
  return fitval3;
}

Double_t fitFunction(Double_t *x, Double_t *par)
{
  return wjetsFit(x,&par[kWjets-1]) + par[kZjets-1]*zjetsFit(x,&par[kWjets-1]) + AntiRelIsoFit(x,&par[kQCD-1]) + ttbarFit(x,&par[kTTbar-1]);
}
