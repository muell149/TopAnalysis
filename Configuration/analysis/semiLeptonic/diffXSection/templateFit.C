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
#include <TPaveLabel.h>

using namespace std;
TH1F* axisHist;
TH1F* HTlep;
TH1F* HTlep_ttbar;
TH1F* HTlep_stop;
TH1F* HTlep_stopS;
TH1F* HTlep_stopT;
TH1F* HTlep_stopTW;
TH1F* HTlep_wjets;
TH1F* HTlep_wjetsAnti;
TH1F* HTlep_zjets;
TH1F* HTlep_zjetsAnti;
TH1F* HTlep_antiRelIso;
TH1F* HTlep_qcd;
TH1F* HTlep_qcdAnti;
TH1F* HTlep_qcdFit;
THStack* HTlep_fitHisto;
TH1F* HTlep_qcdDirty;

enum sample {kData, kWjets, kStopS, kStopT, kStopTW, kZjets, kQCD, kTTbar};

Double_t fitTemplate(Double_t *x, Double_t *par, TH1F* hist);
Double_t fitFunction(Double_t *x, Double_t *par);
std::vector<double> templateFit(Int_t jetNumber = 1, TString qcdTyp = "Data", Double_t zFix = 1., double ttbarFix = 1., TString JES = "", TString particleFlow = "Pf", TString lowerBound = "0.5", TString upperBound = "1.0", TString diffVar = "lepET", TString lowerBinEdge = "20", TString upperBinEdge = "35");

void templateFitSyst()
{
  for(int i=1; i<=4; i++){
    std::vector<double> std = templateFit(i);
    double TtErr = (TMath::Abs(templateFit(i,"Data",1.,0.)[0]-std[0])+TMath::Abs(templateFit(i,"Data",1.,2.)[0]-std[0]))/2;
    double RelIsoErr = (TMath::Abs(templateFit(i,"Data",1.,1.,"","Pf","0.3","0.5")[0]-std[0])+TMath::Abs(templateFit(i,"Data",1.,1.,"","Pf","1.0","2.0")[0]-std[0]))/2;
    double ShapeErr = TMath::Abs(templateFit(i,"mc")[0]-templateFit(i,"mcAnti")[0]);
    double JES = (TMath::Abs(templateFit(i,"Data",1.,1.,"JESup")[0]-std[0])+TMath::Abs(templateFit(i,"Data",1.,1.,"JESdown")[0]-std[0]))/2;
    //double Zerr = (TMath::Abs(templateFit(i,"Data",0.7,1.)[0]-std[0])+TMath::Abs(templateFit(i,"Data",1.3,1.)[0]-std[0]))/2;//not needed, Z error in Xsec is enough
    double syst = sqrt(TtErr*TtErr+RelIsoErr*RelIsoErr+ShapeErr*ShapeErr);
    cout<<setprecision(3)<<std[0]<<"+-"<<setprecision(2)<<std[1]<<"(stat)+-"<<syst<<"(syst) ["<<TtErr<<"(TT)+-"<<ShapeErr<<"(Shape)+-"<<RelIsoErr<<"(RelIso)+-"<<JES<<"(JES)]"<<endl;
  }
}

std::vector<double> templateFit(Int_t jetNumber, TString qcdTyp, Double_t zFix, double ttbarFix, TString JES, TString particleFlow, TString lowerBound, TString upperBound, TString diffVar, TString lowerBinEdge, TString upperBinEdge)
{
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);

  TString templateVar = "MET"; // "HTlep"; // "MT";
  //TString qcdTyp = "Data"; // "mc"; // "mcAnti"; // "mcSmeared";
  //TString particleFlow = "Pf"; // "";
  double lumi = 36.145;

  int binWidth = 1.;
  if(jetNumber)binWidth = 5.*jetNumber-4.;
  int numberOfParameters = 7;
  double lowerFitEdge = 20.;
  double upperFitEdge = 150.+jetNumber*50.;
  if(templateVar=="MET"){
    lowerFitEdge = 0.;
    upperFitEdge = 120.+jetNumber*10.;
  }
  if(templateVar=="MT")upperFitEdge=160.;

  std::vector<TString> whichSample;
  for(int i=0; i<=numberOfParameters; i++){
    if(i==kData)whichSample.push_back("_data_v5");
    if(i==kStopS)whichSample.push_back("_stopS");
    if(i==kStopT)whichSample.push_back("_stopT");
    if(i==kStopTW)whichSample.push_back("_stopTW");
    if(i==kWjets)whichSample.push_back("_wjets"+JES);
    if(i==kZjets)whichSample.push_back("_zjets"+JES);
    if(i==kQCD)whichSample.push_back("_qcd");
    if(i==kTTbar)whichSample.push_back("_ttbar");
  }

  int numberOfBins = int((upperFitEdge/binWidth)+0.9999);
  TString numberOfJets = ""; numberOfJets+=jetNumber;

  std::vector<TFile*> files_;
  for(UInt_t i = 0; i < whichSample.size(); i++){
    files_.push_back(new TFile("/scratch/hh/current/cms/user/henderle/TemplateTree"+whichSample[i]+".root"  ) );
  }

  vector<TTree*> tree;
  for(UInt_t i = 0; i < whichSample.size(); i++){
    tree.push_back((TTree*)files_[i]->Get("TemplateTree"+particleFlow+numberOfJets+"/templateTree"));
  }

  vector<TTree*> treeTemp;
  for(UInt_t i = 0; i < whichSample.size(); i++){
    treeTemp.push_back((TTree*)files_[i]->Get("TemplateTreeControl"+particleFlow+numberOfJets+"/templateTree"));
  }

  TCanvas *canv1 = new TCanvas("canv1","templateFit",10,10,600,600);
  //canv->Divide(1,1);
  canv1->cd(1);
  canv1->cd(1)->SetLeftMargin  (0.15);
  canv1->cd(1)->SetRightMargin (0.05);
  canv1->cd(1)->SetBottomMargin(0.15);
  canv1->cd(1)->SetTopMargin   (0.05);

  axisHist = new TH1F("axisHist","axisHist",1,lowerFitEdge*0.75,upperFitEdge+100*binWidth);
  HTlep = new TH1F("HTlep","HTlep",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_antiRelIso = new TH1F("HTlep_antiRelIso","HTlep_antiRelIso",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_stop = new TH1F("HTlep_stop","HTlep_stop",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_stopS = new TH1F("HTlep_stopS","HTlep_stopS",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_stopT = new TH1F("HTlep_stopT","HTlep_stopT",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_stopTW = new TH1F("HTlep_stopTW","HTlep_stopTW",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_wjets = new TH1F("HTlep_wjets","HTlep_wjets",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_wjetsAnti = new TH1F("HTlep_wjetsAnti","HTlep_wjetsAnti",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_zjets = new TH1F("HTlep_zjets","HTlep_zjets",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_zjetsAnti = new TH1F("HTlep_zjetsAnti","HTlep_zjetsAnti",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_qcd = new TH1F("HTlep_qcd","HTlep_qcd",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_qcdAnti = new TH1F("HTlep_qcdAnti","HTlep_qcdAnti",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_qcdFit = new TH1F("HTlep_qcdFit","HTlep_qcdFit",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_ttbar = new TH1F("HTlep_ttbar","HTlep_ttbar",numberOfBins+100,lowerFitEdge,upperFitEdge+100*binWidth);
  HTlep_fitHisto = new THStack("HTlep_fitHisto","test stacked histograms");

  //ptBins -> 20., 35., 50., 70., 95., 200.
  //etaBins -> -2.1, -0.75, 0.0, 0.75, 2.1
  //phiBins -> -3., -2., -1., 0., 1., 2., 3.
  //TString lowerBinEdge = "20";
  //TString upperBinEdge = "35";
  //TString diffVar = "lepET";

  tree[kData]->Draw(templateVar+">>HTlep","relIso<0.05 && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  treeTemp[kData]->Draw(templateVar+">>HTlep_antiRelIso","relIso>"+lowerBound+" && relIso<"+upperBound+" && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  tree[kStopS]->Draw(templateVar+">>HTlep_stopS","relIso<0.05 && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  tree[kStopT]->Draw(templateVar+">>HTlep_stopT","relIso<0.05 && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  tree[kStopTW]->Draw(templateVar+">>HTlep_stopTW","relIso<0.05 && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  tree[kWjets]->Draw(templateVar+">>HTlep_wjets","relIso<0.05 && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  treeTemp[kWjets]->Draw(templateVar+">>HTlep_wjetsAnti","relIso>"+lowerBound+" && relIso<"+upperBound+" && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  tree[kZjets]->Draw(templateVar+">>HTlep_zjets","relIso<0.05 && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  treeTemp[kZjets]->Draw(templateVar+">>HTlep_zjetsAnti","relIso>"+lowerBound+" && relIso<"+upperBound+" && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  tree[kQCD]->Draw(templateVar+">>HTlep_qcd","relIso<0.05 && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  treeTemp[kQCD]->Draw(templateVar+">>HTlep_qcdAnti","relIso>"+lowerBound+" && relIso<"+upperBound+" && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  if(qcdTyp=="Data"){
    if(diffVar=="lepET")treeTemp[kData]->Draw(templateVar+">>HTlep_qcdFit","relIso>"+lowerBound+" && relIso<"+upperBound+" && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
    else treeTemp[kData]->Draw(templateVar+">>HTlep_qcdFit","relIso>"+lowerBound+" && relIso<"+upperBound,"0");
  }
  else if(qcdTyp=="mc")
    tree[kQCD]->Draw(templateVar+">>HTlep_qcdFit","relIso<0.05 && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  else if(qcdTyp=="mcSmeared")
    tree[kQCD]->Draw(templateVar+"*1.1+1.1*0.1*(MET-genMET)>>HTlep_qcdFit","relIso<0.05 && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  else if(qcdTyp=="mcAnti")
    treeTemp[kQCD]->Draw(templateVar+">>HTlep_qcdFit","relIso>"+lowerBound+" && relIso<"+upperBound+" && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");
  else std::cout<<"zonk"<<std::endl;
  tree[kTTbar]->Draw(templateVar+">>HTlep_ttbar","relIso<0.05 && "+diffVar+">"+lowerBinEdge+" && "+diffVar+"<"+upperBinEdge+"","0");

  int smooth = 0;
  HTlep->SetMarkerStyle(20);
  HTlep_antiRelIso->Scale((lumi*0.143500567/50.0)*HTlep_qcd->Integral()/HTlep_antiRelIso->Integral());
  HTlep_antiRelIso->Smooth(smooth);
  HTlep_stopS->Scale(lumi*0.324*0.000464677/50.0);
  HTlep_stopT->Scale(lumi*0.324*0.006672727/50.0);
  HTlep_stopTW->Scale(lumi*0.001070791/50.0);
  HTlep_wjets->Scale(lumi*0.105750913/50.0);
  HTlep_wjets->Smooth(smooth);
  HTlep_zjets->Scale(lumi*0.05991209/50.0);
  HTlep_zjets->Smooth(smooth);
  HTlep_ttbar->Scale(lumi*0.006029022/50.0);
  HTlep_ttbar->Smooth(smooth);
  HTlep_qcdAnti->Scale((lumi*0.143500567/50.0)*HTlep_qcd->Integral()/HTlep_qcdAnti->Integral());
  HTlep_qcdAnti->Smooth(smooth);
  HTlep_qcdFit->Scale((lumi*0.143500567/50.0)*HTlep_qcd->Integral()/HTlep_qcdFit->Integral());
  HTlep_qcdFit->Smooth(smooth);
  HTlep_qcd->Scale(lumi*0.143500567/50.0);
  HTlep_qcd->Smooth(smooth);

  HTlep_stop = (TH1F*)HTlep_stopS->Clone();
  HTlep_stop->Add((TH1F*)HTlep_stopT->Clone());
  HTlep_stop->Add((TH1F*)HTlep_stopTW->Clone());

  TF1* mixFunction = new TF1("fitFunction",fitFunction,lowerFitEdge-(int(lowerFitEdge)%binWidth),upperFitEdge-0.0001,numberOfParameters);
  for(int i=0; i<numberOfParameters; i++){
    mixFunction->SetParameter(i,1.);
    mixFunction->SetParLimits(i,0.,100.);
    mixFunction->SetParName(i,"Scale"+whichSample[i+1]);
  }
  mixFunction->FixParameter(kStopS-1,1.);
  mixFunction->FixParameter(kStopT-1,1.);
  mixFunction->FixParameter(kStopTW-1,1.);
  if(zFix>=0)mixFunction->FixParameter(kZjets-1,zFix);
  if(ttbarFix>=0)mixFunction->FixParameter(kTTbar-1,ttbarFix);

  HTlep->Fit(mixFunction,"0LQR");
  std::vector<double> QCDscale;
  QCDscale.push_back(mixFunction->GetParameter(kQCD-1));
  QCDscale.push_back(mixFunction->GetParError(kQCD-1));
  delete mixFunction;
  delete axisHist;
  delete HTlep;
  delete HTlep_antiRelIso;
  delete HTlep_stop;
  delete HTlep_stopS;
  delete HTlep_stopT;
  delete HTlep_stopTW;
  delete HTlep_wjets;
  delete HTlep_wjetsAnti;
  delete HTlep_zjets;
  delete HTlep_zjetsAnti;
  delete HTlep_qcd;
  delete HTlep_qcdAnti;
  delete HTlep_qcdFit;
  delete HTlep_ttbar;     
  delete HTlep_fitHisto;
  delete canv1;
  for(UInt_t i = 0; i < whichSample.size(); i++){
    delete files_[i];
  }

  return QCDscale;
}

Double_t fitTemplate(Double_t *x, Double_t *par, TH1F* hist)
{
  Double_t arg = 0;
  arg = hist->GetBinContent(hist->GetXaxis()->FindBin(x[0]));
  Double_t fitval = 0;
  fitval = par[0]*arg;
  return fitval;
}

Double_t fitFunction(Double_t *x, Double_t *par)
{
  return fitTemplate(x,&par[kWjets-1],HTlep_wjets) + 
         par[kWjets-1]*fitTemplate(x,&par[kZjets-1],HTlep_zjets) + 
         fitTemplate(x,&par[kQCD-1],HTlep_qcdFit) + 
         fitTemplate(x,&par[kTTbar-1],HTlep_ttbar) + 
         par[kTTbar-1]*fitTemplate(x,&par[kStopS-1],HTlep_stopS) + 
         par[kTTbar-1]*fitTemplate(x,&par[kStopT-1],HTlep_stopT) + 
         par[kTTbar-1]*fitTemplate(x,&par[kStopTW-1],HTlep_stopTW);
}
