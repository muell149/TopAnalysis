#include <TCanvas.h>
#include <TF1.h>
#include <TFile.h>
#include <TGaxis.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TSystem.h>

#include <iostream>
#include <stdlib.h>

#include "cloneObjectFromFile.h"

void setPadStyle()
{

  gPad->SetBorderMode(0);
  gPad->SetLeftMargin(.2);
  gPad->SetRightMargin(.1);
  gPad->SetBottomMargin(.21);
  gPad->SetTopMargin(.1);
  TGaxis::SetMaxDigits(3);

}

void setAxisStyle(TH1* hist)
{

  hist->GetXaxis()->SetNdivisions(505);
  hist->GetXaxis()->SetLabelSize(0.07);
  hist->GetXaxis()->SetTitleSize(0.07);
  hist->GetXaxis()->SetTitleOffset(1.2);
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->SetNdivisions(505);
  hist->GetYaxis()->SetLabelSize(0.07);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetTitleOffset(1.4);
  hist->GetYaxis()->CenterTitle();

}

void drawHLine(TH1 *thisHisto, Double_t y,
	       Style_t lstyle = 2, Width_t lwidth = 1, Color_t lcolor = kBlack)
{
  Double_t xmin = thisHisto->GetXaxis()->GetXmin();
  Double_t xmax = thisHisto->GetXaxis()->GetXmax();
  TString height = ""; height += y;
  TF1 *f = new TF1("f", height.Data(), xmin, xmax);
  f->SetLineStyle(lstyle);
  f->SetLineWidth(lwidth);
  f->SetLineColor(lcolor);
  f->Draw("L same");
}

void drawWithRatio(TH1F* hist1, TH1F* hist2,
		   const TString xTitle, const TString yTitle = "a.u.", const TString title = "")
{
  setPadStyle();
  gPad->SetBottomMargin(0.45);

  hist1->SetStats(kFALSE);
  setAxisStyle(hist1);
  hist1->SetTitle(title);
  hist1->SetXTitle(xTitle);
  hist1->SetYTitle(yTitle);

  TH1F* ratio = (TH1F*) hist1->Clone();
  ratio->Divide(hist2);

  hist1->GetXaxis()->SetLabelSize(0.0);
  hist1->DrawCopy("hist");
  hist2->DrawCopy("hist same");

  TPad* rPad = new TPad("rPad","",0,0,1,1);
  rPad->SetFillStyle(0);
  rPad->Draw();

  rPad->cd();
  setPadStyle();
  rPad->SetTopMargin(0.55);
  ratio->SetYTitle("ratio");
  ratio->SetMaximum(1.19);
  ratio->SetMinimum(0.81);
  ratio->SetMarkerStyle(8);
  ratio->SetMarkerSize(0.5);
  ratio->SetLineColor(kBlack);
  ratio->DrawCopy("p");
  drawHLine(ratio, 1.15, 3);
  drawHLine(ratio, 1.10, 1);
  drawHLine(ratio, 1.05, 3);
  drawHLine(ratio, 1.00, 1);
  drawHLine(ratio, 0.95, 3);
  drawHLine(ratio, 0.90, 1);
  drawHLine(ratio, 0.85, 3);
}

void normToUnitArea(TH1F* hist)
{
  hist->Sumw2();
  hist->Scale(1. / hist->Integral());
}

void setDrawStyles(TH1F* hist1, TH1F* hist2)
{
  hist1->SetFillColor(kGray);
  hist1->SetLineColor(kGray);
  hist2->SetLineColor(kBlue);
  hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
}

int compareSamples(TString fileName1, TString fileName2)
{

  TFile* file[2];
  file[0] = TFile::Open(fileName1);
  file[1] = TFile::Open(fileName2);

  TH1F* ptL [2];
  TH1F* ptB [2];
  TH1F* etaL[2];
  TH1F* etaB[2];
  TH1F* mW  [2];
  TH1F* mT  [2];

  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);

  TString inDir = "analyzeJetEnergyGenMatch_abs";

  for(unsigned i=0; i < 2; ++i) {
    if(!file[i])
      abort();

    ptL [i] = cloneObjectFromFile<TH1F*>(file[i], inDir + "/ptJetUDS"  );
    ptB [i] = cloneObjectFromFile<TH1F*>(file[i], inDir + "/ptJetB"    );
    etaL[i] = cloneObjectFromFile<TH1F*>(file[i], inDir + "/etaJetUDSC");
    etaB[i] = cloneObjectFromFile<TH1F*>(file[i], inDir + "/etaJetB"   );
    mW  [i] = cloneObjectFromFile<TH1F*>(file[i], inDir + "/mW"        );
    mT  [i] = cloneObjectFromFile<TH1F*>(file[i], inDir + "/mTop"      );

    ptL[i]->Add( (TH1F*) file[i]->Get(inDir + "/ptJetC") );

    file[i]->Close();

    etaL[i]->Rebin(2);
    etaB[i]->Rebin(2);
    mT  [i]->Rebin(2);

    normToUnitArea(ptL [i]);
    normToUnitArea(ptB [i]);
    normToUnitArea(etaL[i]);
    normToUnitArea(etaB[i]);
    normToUnitArea(mW  [i]);
    normToUnitArea(mT  [i]);
  }

  ptL [0]->GetXaxis()->SetRangeUser(30., 150.);
  ptB [0]->GetXaxis()->SetRangeUser(30., 150.);
  mW  [0]->GetXaxis()->SetRangeUser(40., 140.);
  mT  [0]->GetXaxis()->SetRangeUser(100., 250.);

  setDrawStyles(ptL [0], ptL [1]);
  setDrawStyles(ptB [0], ptB [1]);
  setDrawStyles(etaL[0], etaL[1]);
  setDrawStyles(etaB[0], etaB[1]);
  setDrawStyles(mW  [0], mW  [1]);
  setDrawStyles(mT  [0], mT  [1]);

  TLegend* legend = new TLegend(0.7, 0.8, 1., 1.);
  legend->SetFillColor(0);
  legend->AddEntry(ptL[0], "Madgraph", "F");
  legend->AddEntry(ptL[1], "MC@NLO", "F");

  TString outDir = "compareJetEnergyCorrectionSamples";
  gSystem->mkdir(outDir);

  TCanvas* canvas = new TCanvas("canvas", "canvas", 600, 900);
  canvas->Divide(2,3);

  canvas->cd(1);
  drawWithRatio(ptL[0], ptL[1], "p_{T,j} [GeV]");
  legend->Draw();
  canvas->cd(1);
  gPad->Print(outDir+"/ptL.eps");

  canvas->cd(2);
  drawWithRatio(ptB[0], ptB[1], "p_{T,b} [GeV]");
  legend->Draw();
  canvas->cd(2);
  gPad->Print(outDir+"/ptB.eps");

  canvas->cd(3);
  drawWithRatio(etaL[0], etaL[1], "#eta_{j}");
  legend->Draw();
  canvas->cd(3);
  gPad->Print(outDir+"/etaL.eps");

  canvas->cd(4);
  drawWithRatio(etaB[0], etaB[1], "#eta_{b}");
  legend->Draw();
  canvas->cd(4);
  gPad->Print(outDir+"/etaB.eps");

  canvas->cd(5);
  drawWithRatio(mW[0], mW[1], "m_{jj} [GeV]");
  legend->Draw();
  canvas->cd(5);
  gPad->Print(outDir+"/mW.eps");

  canvas->cd(6);
  drawWithRatio(mT[0], mT[1], "m_{jjb} [GeV]");
  legend->Draw();
  canvas->cd(6);
  gPad->Print(outDir+"/mT.eps");

  TString psName = outDir + "/catalog.ps";
  canvas->Print(psName);

  return 0;

}

int main(int argc, char** argv)
{
  return compareSamples(argv[1], argv[2]);
}
