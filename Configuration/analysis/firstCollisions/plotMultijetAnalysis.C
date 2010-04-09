#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>
#include <TGaxis.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TSystem.h>

#include <iostream>
#include <iomanip>
#include <stdlib.h>

TString outDir = "multijetAnalysis";

template <typename T>
T cloneObjectFromFile(TFile* file, TString name)
{
  if(!file->Get(name)) {
    std::cout << "Failed to get object with name " << name << " from file " << file->GetName() << std::endl;
    abort();
  }
  T obj = (T) file->Get(name);
  for(unsigned i=0; i<999999; i++) {
    TString cloneName = (TString) obj->GetName() + "_clone_";
    cloneName += i;
    if(!gDirectory->Get(cloneName)) {
      return (T) file->Get(name)->Clone(cloneName);
    }
  }
  std::cout << "Already more than 999999 clones from object with name " << obj->GetName() << std::endl
	    << "If this is really what you want, you have to increase this hard-coded limit in the macro." << std::endl;
  abort();
}

void setPadStyle()
{
  gPad->SetBorderMode(0);
  gPad->SetLeftMargin(.21);
  gPad->SetRightMargin(.07);
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

void drawHistos(TH1F** hist, const TString xTitle, TString figName, TString yTitle = "events", bool logY = true)
{

  double scaleFactor = hist[0]->GetEntries() / hist[1]->GetEntries();
  hist[1]->Scale( scaleFactor );

  setAxisStyle(hist[1]);
  hist[1]->SetTitle("");
  hist[1]->SetXTitle(xTitle);
  hist[1]->SetYTitle(yTitle);
  hist[1]->SetStats(kFALSE);
  if(logY)
    hist[1]->SetMinimum(0.11);

  if(figName == "eta")
    hist[1]->SetMaximum(90.);
  else if(figName == "phi") {
    hist[1]->SetMaximum(130.);
    hist[1]->SetMinimum(0.);
  }

  gPad->SetLogy(logY);
  setPadStyle();
  hist[1]->SetFillColor(kYellow);
  hist[1]->DrawCopy("");
  hist[0]->SetMarkerStyle(20);
  hist[0]->DrawCopy("pe same");
  gPad->Print(outDir + "/" + figName + ".eps");

}

int plotMultijetAnalysis(TString name1 = "analyzeMultijet_new.root",
			 TString name2 = "analyzeMultijet_MC_new.root")
{

  TFile* file[2];
  file[0] = TFile::Open(name1);
  file[1] = TFile::Open(name2);

  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFontSize(.05);
  gStyle->SetTitleX(.4);
  gStyle->SetTitleY(.995);
  gStyle->SetErrorX(0.);

  TH1F* zvtx  [2];
  TH1F* met   [2];
  TH1F* nHpTrk[2];
  TH1F* fHpTrk[2];

  TH1F* nJet   [2];
  TH1F* ptJet  [2];
  TH1F* etaJet [2];
  TH1F* phiJet [2];
  TH1F* emfJet [2];
  TH1F* fHpdJet[2];
  TH1F* n90Jet [2];

  for(unsigned i = 0; i < 2; ++i) {
  
    if(!file[i])
      abort();
    
    TString inDirBase = "analyzeEventBasics";

    zvtx  [i] = cloneObjectFromFile<TH1F*>(file[i], inDirBase + "/z_vtx");
    met   [i] = cloneObjectFromFile<TH1F*>(file[i], inDirBase + "/met");
    nHpTrk[i] = cloneObjectFromFile<TH1F*>(file[i], inDirBase + "/n_hpTrk");
    fHpTrk[i] = cloneObjectFromFile<TH1F*>(file[i], inDirBase + "/f_hpTrk");

    inDirBase = "analyzeJetQuality";

    emfJet [i] = cloneObjectFromFile<TH1F*>(file[i], inDirBase + "/emf");
    fHpdJet[i] = cloneObjectFromFile<TH1F*>(file[i], inDirBase + "/fHPD_");
    n90Jet [i] = cloneObjectFromFile<TH1F*>(file[i], inDirBase + "/n90_");

    inDirBase = "analyzeJetKinematics";

    nJet   [i] = cloneObjectFromFile<TH1F*>(file[i], inDirBase + "/n");
    ptJet  [i] = cloneObjectFromFile<TH1F*>(file[i], inDirBase + "/pt");
    etaJet [i] = cloneObjectFromFile<TH1F*>(file[i], inDirBase + "/eta");
    phiJet [i] = cloneObjectFromFile<TH1F*>(file[i], inDirBase + "/phi");

    file[i]->Close();

  }

  gSystem->mkdir(outDir);

  TCanvas* canvas = new TCanvas("canvas", "canvas", 900, 900);
  canvas->Divide(3,3);

  canvas->cd(1);
  drawHistos(zvtx, "z_{vertex} [cm]", "zvtx");

  canvas->cd(2);
  drawHistos(met, "MET [GeV]", "met");

  canvas->cd(4);
  drawHistos(nHpTrk, "number of high purity tracks", "nHpTrk");

  canvas->cd(5);
  drawHistos(fHpTrk, "fraction of high purity tracks", "fHpTrk");

  TCanvas* canvas2 = new TCanvas("canvas2", "canvas2", 900, 900);
  canvas2->Divide(3,3);

  canvas2->cd(1);
  drawHistos(emfJet, "electromagnetic fraction", "emf", "jets");

  canvas2->cd(2);
  drawHistos(n90Jet, "n90Hits", "n90", "jets");

  canvas2->cd(3);
  drawHistos(fHpdJet, "fHPD", "fHPD", "jets");

  canvas2->cd(4);
  drawHistos(nJet, "number of jets", "nJet");

  canvas2->cd(5);
  drawHistos(ptJet, "p_{T} [GeV]", "pt", "jets");

  canvas2->cd(6);
  drawHistos(etaJet, "#eta", "eta", "jets", false);

  canvas2->cd(7);
  drawHistos(phiJet, "#phi", "phi", "jets", false);

  TString psName = outDir + "/catalog.ps";
  canvas ->Print(psName + ")");
  canvas2->Print(psName + "(");

  return 0;
}
