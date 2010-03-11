#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>

#include "TROOT.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TRandom3.h"

#include "TH1F.h"
#include "TFile.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TPaveText.h"

void measurement(TH1F& src, TH1F& data)
{
  TRandom3 rnd;
  for(int ibin=0; ibin<src.GetNbinsX(); ++ibin){
    unsigned int evts=rnd.Poisson(src.GetBinContent(ibin));
    data.SetBinContent(ibin, evts);
    data.SetBinError(ibin, sqrt(evts));
  }
}

int combine(const char* directory, const char* hist, const char* label="", unsigned int logY=0, unsigned int lumiPb=1)
{
  gStyle->SetOptStat(0);
  gStyle->SetHatchesLineWidth(1.5);

  std::vector<TFile*> files_;
  std::vector<TH1F* > hists_; 
  
  // set the scene
  files_.push_back(new TFile("validate_qcd09_pat7.root"   )); // [0]
  files_.push_back(new TFile("validate_wjets09_pat7.root" )); // [1]
  files_.push_back(new TFile("validate_zjets09_pat7.root" )); // [2]
  files_.push_back(new TFile("validate_ttbarx09_nlo7.root")); // [3]

  // normaization to pb-1
  float norm[]={296900000*0.00037/5340172, // QCD(mu incl)		
		28000./11377412          , // W+Jets 
		3110./1068735            , // Z+Jets
		165./993455};              // TTbar(MC@NLO)

  std::string name(directory); name+="/"; name+=hist;
  for(unsigned int idx=0; idx<files_.size();++idx){
    TH1F* buffer = (TH1F*)files_[idx]->Get(name.c_str());
    if( buffer ){
      buffer->Scale(lumiPb*norm[idx]);
      // successively stack the histograms
      for(unsigned int jdx=0; jdx<hists_.size();++jdx){
	hists_[jdx]->Add(buffer);
      }
      // and add them to the list
      hists_.push_back(buffer);
    }
    else{
      std::cout << "histogram not found -- please check name" << std::endl;
      std::cout << "hist: " << files_[idx]->GetName() << " :: " << name << std::endl;
      return -1;
    }
  }
  TH1F* data_=(TH1F*)hists_[0]->Clone(); data_->Clear();
  measurement(*hists_[0], *data_);

  TCanvas *canv = new TCanvas("canv", "histograms", 600, 600);
  canv->SetFillStyle(4000.);
  canv->SetLeftMargin( 0.20);
  canv->SetRightMargin( 0.05);
  canv->SetBottomMargin( 0.15);
  canv->SetTopMargin( 0.05);

  TLegend* leg = new TLegend(0.60, 0.65, 0.95, 0.85);
  leg->SetFillStyle( 0);
  leg->SetFillColor( 0);
  leg->SetBorderSize(0);
  char entry_[50];
  sprintf(entry_, "Data(%d pb^{-1})", lumiPb);
  leg->AddEntry(data_    , entry_   ,   "P" );
  leg->AddEntry(hists_[0], "All"    ,   "FL");
  leg->AddEntry(hists_[1], "V+Jets" ,   "FL");
  leg->AddEntry(hists_[2], "Ttbar"  ,   "FL");

  
  std::string label_(label);
  float leftX= label_.length()<20 ? 0.48 : 0.38;
  TPaveText* text  = new TPaveText(leftX, 0.83, 0.98, 0.98, "NDC");
  text->SetBorderSize(   0 );
  text->SetFillStyle(    0 );
  text->SetTextAlign(   12 );
  text->SetTextSize ( 0.06 );
  text->SetTextColor(    1 );
  text->SetTextFont (   62 );

  //char labelname[100];
  //sprintf(labelname, label, fitter[ 1 ]->GetNDstar(), fitter[ 1 ]->GetNDstarErr() );
  text->AddText(label);

  canv->SetLogy(logY);
  logY==0 ? hists_[0]->SetMinimum(0.) :  hists_[0]->SetMinimum(0.1);
  hists_[0]->SetMaximum(2.5*hists_[0]->GetMaximum());
  hists_[0]->GetXaxis()->SetTitle(hists_[0]->GetTitle());
  hists_[0]->SetTitle("");
  hists_[0]->SetLineWidth(5);
  hists_[0]->SetLineColor(1);
  hists_[0]->SetFillColor(1);
  hists_[0]->SetFillStyle(3553);
  hists_[0]->Draw();
  hists_[2]->SetLineWidth(3);
  hists_[2]->SetLineColor(2);
  hists_[2]->SetFillColor(2);
  hists_[2]->SetFillStyle(3005);
  hists_[2]->Draw("same");
  hists_[3]->SetLineWidth(3);
  hists_[3]->SetLineColor(4);
  hists_[3]->SetFillColor(4);
  hists_[3]->SetFillStyle(3004);
  hists_[3]->Draw("same");
  data_->SetMarkerStyle(20.);
  data_->SetMarkerColor(1.);
  data_->SetMarkerSize(1.5);
  data_->SetLineColor(1.);
  data_->SetLineWidth(5.);
  data_->Draw("same");

  text->Draw("same");
  leg->Draw();

  std::string out(directory); out+="_"; out+=hist; out+=".eps";
  std::cout << out << std::endl;
  canv->Print(out.c_str());
  return 0;
}

/* to be called like this from batch mode:
root -l -b -q 'combine.C++("MuonQuality4", "trkIso_")'
*/
