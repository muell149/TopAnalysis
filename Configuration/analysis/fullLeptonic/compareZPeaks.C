#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"

#include <iostream>

void compareZPeaks()
{

  TFile* file[6];
  TH1F*  hist[6];
  TString title[6];

  file[0] = new TFile("/afs/naf.desy.de/user/w/wbehrenh/cms/1fbJul19/ee_200rereco.root", "READ");
  file[1] = new TFile("/afs/naf.desy.de/user/w/wbehrenh/cms/1fbJul19/ee_800prompt.root", "READ");
  file[2] = new TFile("/afs/naf.desy.de/user/w/wbehrenh/cms/1fbJul19/ee_dyee50inf.root", "READ");
  file[3] = new TFile("/afs/naf.desy.de/user/w/wbehrenh/cms/1fbJul19/mumu_200rereco.root", "READ");
  file[4] = new TFile("/afs/naf.desy.de/user/w/wbehrenh/cms/1fbJul19/mumu_800prompt.root", "READ");
  file[5] = new TFile("/afs/naf.desy.de/user/w/wbehrenh/cms/1fbJul19/mumu_dymumu50inf.root", "READ");

  title[0] = "ReReco Data (0.2/fb)";
  title[1] = "PromptReco Data (0.8/fb)";
  title[2] = "MC (DY 50-Inf)";
  title[3] = "ReReco Data (0.2/fb)";
  title[4] = "PromptReco Data (0.8/fb)";
  title[5] = "MC (DY 50-Inf)";

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(2210);
  gStyle->SetStatW(0.5);

  TCanvas* canvas = new TCanvas("canvas", "canvas", 10, 10, 900, 600);
  canvas->Divide(3,2);
  
  for(unsigned i=0; i<6; i++) {
    if(i<3) {
      hist[i] = (TH1F*) file[i]->Get("analyzeLeptonPair3/DimassRC_EE");
      hist[i]->GetXaxis()->SetTitle("M_{ee} [Gev]");
    }
    else {
      hist[i] = (TH1F*) file[i]->Get("analyzeLeptonPair3/DimassRC_MM");
      hist[i]->GetXaxis()->SetTitle("M_{#mu#mu} [Gev]");
    }

    canvas->cd(i+1);

    hist[i]->SetTitle(title[i]);
    //    hist[i]->GetXaxis()->SetRangeUser(50,130);
    hist[i]->GetXaxis()->SetRangeUser(76,106);

    hist[i]->Draw();
  }

  canvas->Print("zPeaks.ps");

  for(unsigned i=0; i<6; i++) {
    file[i]->Close();
    delete file[i];
  }
  delete canvas;

}
