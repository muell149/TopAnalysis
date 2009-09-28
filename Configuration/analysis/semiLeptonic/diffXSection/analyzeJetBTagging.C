#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>

enum styles {kLightQ, kBottom};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);


void analyzeJetBTagging(TString selection = "all")
{
  // ---
  //    set root style 
  // ---
  //gROOT->cd();
  //gROOT->SetStyle("Plain");

  // ---
  //    open input file
  // ---
  TFile* file = new TFile("./rootfiles/analyzeSemiLeptonicSelection_"+selection+".root");

  std::vector<TString> jet_B_or_not_jet_B_;
  jet_B_or_not_jet_B_.push_back("tightMatchedLightQJetQuality");
  jet_B_or_not_jet_B_.push_back("tightMatchedBJetQuality");

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> btag0_, btag1_, btag2_, btag3_;
  for(unsigned int idx=0; idx<jet_B_or_not_jet_B_.size(); ++idx) {
    btag0_.push_back( (TH1F*)file->Get(jet_B_or_not_jet_B_[idx]+"/btagSimpleSecVtx_"    )->Clone() );
    btag1_.push_back( (TH1F*)file->Get(jet_B_or_not_jet_B_[idx]+"/btagSimpleSecVtxNeg_" )->Clone() );
    btag2_.push_back( (TH1F*)file->Get(jet_B_or_not_jet_B_[idx]+"/btagTrkCntHighEff_"   )->Clone() );
    btag3_.push_back( (TH1F*)file->Get(jet_B_or_not_jet_B_[idx]+"/btagTrkCntHighPurity" )->Clone() );
  }

  // ---
  //    close input file
  // ---
  //file->Close();

  
  // ---
  //    configure histograms
  // ---

  // btag0_
  histogramStyle(*btag0_  [kLightQ    ], kLightQ    );
  histogramStyle(*btag0_  [kBottom], kBottom);

  // btag1_
  histogramStyle(*btag1_ [kLightQ    ], kLightQ    );
  histogramStyle(*btag1_ [kBottom], kBottom);

  // btag2_
  histogramStyle(*btag2_[kLightQ    ], kLightQ    );
  histogramStyle(*btag2_[kBottom], kBottom);

  // btag3_
  histogramStyle(*btag3_[kLightQ    ], kLightQ    );
  histogramStyle(*btag3_[kBottom], kBottom);

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.67, 1.05, 0.92);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  leg0->AddEntry( btag0_[kLightQ] , "light quarks"  , "FL" );
  leg0->AddEntry( btag0_[kBottom] , "bottom quarks" , "FL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.67, 1.05, 0.92);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  leg1->AddEntry( btag0_[kLightQ] , "light quarks"  , "FL" );
  leg1->AddEntry( btag0_[kBottom] , "bottom quarks" , "FL" );

  // ---
  //    do the printing for Simple Secondary Vtx
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  
  // draw canvas
  canv0->cd(0)->SetLogy();
  axesStyle(*btag0_[kLightQ], "BTag(Simple Secondary Vtx)", "events");
//   btag0_[kLightQ       ]->SetMinimum(0.);
  btag0_[kLightQ]->SetMaximum( 3.3* btag0_[kLightQ]->GetMaximum() );
  btag0_[kLightQ]->Draw();
  btag0_[kBottom]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for Simple Secondary VtxNeg
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  axesStyle(*btag1_[kLightQ], "BTag_{Neg}(Simple Secondary Vtx)", "events");
  btag1_[kLightQ    ]->SetMaximum( 1.3* btag1_[kLightQ]->GetMaximum() );
  btag1_[kLightQ    ]->Draw();
  btag1_[kBottom]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for Track Counting high eff
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  axesStyle(*btag2_[kLightQ], "BTag_{Eff}(Track Counting)", "events");
  btag2_[kLightQ]->SetMinimum( 0 );
  btag2_[kLightQ]->SetMaximum( 1.3* btag2_[kLightQ]->GetMaximum() );
  btag2_[kLightQ]->Draw();
  btag2_[kBottom]->Draw("same");
  leg1->Draw("same");

  // ---
  //    do the printing for Track Counting high pure
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  axesStyle(*btag3_[kLightQ], "BTag_{Pure}(Track Counting)", "events");
  btag3_[kLightQ]->SetMinimum( 0 );
  btag3_[kLightQ]->SetMaximum( 1.3* btag3_[kLightQ]->GetMaximum() );
  btag3_[kLightQ]->Draw();
  btag3_[kBottom]->Draw("same");
  leg1->Draw("same");
}

void canvasStyle(TCanvas& canv) 
{
  canv.SetFillStyle   ( 4000);
  canv.SetLeftMargin  ( 0.20);
  canv.SetRightMargin ( 0.05);
  canv.SetBottomMargin( 0.15);
  canv.SetTopMargin   ( 0.05);
}

void histogramStyle(TH1& hist, unsigned int style) 
{
  // pre-defined line style
  std::vector<int> color;
  color.push_back( kBlue );
  color.push_back( kRed  ); 

  // pre-defined fill style
  std::vector<int> fill;
  fill.push_back(3005);
  fill.push_back(3004); 

  // set line width
  hist.SetLineWidth(3);

  hist.SetStats(kFALSE);
  hist.SetLineColor  (color[style]);
  hist.SetFillColor  (color[style]);
  hist.SetMarkerColor(color[style]);
  hist.SetFillStyle  (fill [style]);
}

void axesStyle(TH1& hist, const char* titleX, const char* titleY) 
{
  hist.SetTitle("");

  hist.GetXaxis()->SetTitle(titleX);
  hist.GetXaxis()->CenterTitle();
  hist.GetXaxis()->SetTitleSize  ( 0.06);
  hist.GetXaxis()->SetTitleColor (    1);
  hist.GetXaxis()->SetTitleOffset(  0.9);
  hist.GetXaxis()->SetTitleFont  (   62);
  hist.GetXaxis()->SetLabelSize  ( 0.05);
  hist.GetXaxis()->SetLabelFont  (   62);
  hist.GetXaxis()->SetNdivisions (  505);
  
  hist.GetYaxis()->SetTitle(titleY);
  hist.GetYaxis()->SetTitleSize  ( 0.07);
  hist.GetYaxis()->SetTitleColor (    1);
  hist.GetYaxis()->SetTitleOffset(  1.2);
  hist.GetYaxis()->SetTitleFont  (   62);
  hist.GetYaxis()->SetLabelSize  ( 0.04);
  hist.GetYaxis()->SetLabelFont  (   62);
}
