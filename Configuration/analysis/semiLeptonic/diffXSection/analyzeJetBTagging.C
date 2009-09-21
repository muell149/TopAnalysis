#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>

enum styles {kAll, kSignal, kBackground};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);


void analyzeJetBTagging()
{
  // ---
  //    set root style 
  // ---
  //gROOT->cd();
  //gROOT->SetStyle("Plain");

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  files_.push_back(new TFile("~rwolf/public/rootfiles/analyzeSemiLeptonicSelection_all_0_ttbarx09.root") );
  files_.push_back(new TFile("~rwolf/public/rootfiles/analyzeSemiLeptonicSelection_sig_0_ttbarx09.root") );
  files_.push_back(new TFile("~rwolf/public/rootfiles/analyzeSemiLeptonicSelection_bkg_0_ttbarx09.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> btag0_, btag1_, btag2_, btag3_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    btag0_.push_back( (TH1F*)files_[idx]->Get("tightLeadingJetQuality/btagSimpleSecVtx_"    ) );
    btag1_.push_back( (TH1F*)files_[idx]->Get("tightLeadingJetQuality/btagSimpleSecVtxNeg_" ) );
    btag2_.push_back( (TH1F*)files_[idx]->Get("tightLeadingJetQuality/btagTrkCntHighEff_"   ) );
    btag3_.push_back( (TH1F*)files_[idx]->Get("tightLeadingJetQuality/btagTrkCntHighPurity" ) );
  }

  // bugfix for in between
  btag0_[kAll]->Add( btag0_[kSignal] );
  btag1_[kAll]->Add( btag1_[kSignal] );
  btag2_[kAll]->Add( btag2_[kSignal] );
  btag3_[kAll]->Add( btag3_[kSignal] );

  // ---
  //    close input files
  // ---
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    //files_[idx]->Close();
  }
  
  // ---
  //    configure histograms
  // ---

  // btag0_
  histogramStyle(*btag0_  [kAll       ], kAll       );
  histogramStyle(*btag0_  [kSignal    ], kSignal    );
  histogramStyle(*btag0_  [kBackground], kBackground);


  // btag1_
  histogramStyle(*btag1_ [kAll       ], kAll       );
  histogramStyle(*btag1_ [kSignal    ], kSignal    );
  histogramStyle(*btag1_ [kBackground], kBackground);

  // btag2_
  histogramStyle(*btag2_[kAll       ], kAll       );
  histogramStyle(*btag2_[kSignal    ], kSignal    );
  histogramStyle(*btag2_[kBackground], kBackground);

  // btag3_
  histogramStyle(*btag3_[kAll       ], kAll       );
  histogramStyle(*btag3_[kSignal    ], kSignal    );
  histogramStyle(*btag3_[kBackground], kBackground);

  // ---
  //    do the printing for n_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  leg0->AddEntry( btag0_[kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( btag0_[kSignal    ] , "semi-lep. ( #mu )" , "FL" );
  leg0->AddEntry( btag0_[kBackground] , "other decays"      , "FL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  leg1->AddEntry( btag0_[kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( btag0_[kSignal    ] , "semi-lep. ( #mu )" , "FL" );
  leg1->AddEntry( btag0_[kBackground] , "other decays"      , "FL" );
  
  // draw canvas
  canv0->cd(0);
  axesStyle(*btag0_[kAll], "BTag(Simple Secondary Vtx)", "events");
  btag0_[kAll       ]->SetMinimum(0.);
  btag0_[kAll       ]->SetMaximum( 1.3* btag0_[kAll]->GetMaximum() );
  btag0_[kAll       ]->Draw();
  btag0_[kSignal    ]->Draw("same");
  btag0_[kBackground]->Draw("same");
  //btag0_  [kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for pt_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  axesStyle(*btag1_[kAll], "BTag_{Neg}(Simple Secondary Vtx)", "events");
  btag1_[kAll       ]->SetMaximum( 1.3* btag1_[kAll]->GetMaximum() );
  btag1_[kAll       ]->Draw();
  btag1_[kSignal    ]->Draw("same");
  btag1_[kBackground]->Draw("same");
  //btag1_ [kAll       ]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for eta_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  axesStyle(*btag2_[kAll], "BTag_{Eff}(Track Counting)", "events");
  btag2_[kAll       ]->SetMinimum( 0 );
  btag2_[kAll       ]->SetMaximum( 1.3* btag2_[kAll]->GetMaximum() );
  btag2_[kAll       ]->Draw();
  btag2_[kSignal    ]->Draw("same");
  btag2_[kBackground]->Draw("same");
  //eta_[kAll       ]->Draw("same");
  leg1->Draw("same");

  // ---
  //    do the printing for phi_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  axesStyle(*btag3_[kAll], "BTag_{Pure}(Track Counting)", "events");
  btag3_[kAll       ]->SetMinimum( 0 );
  btag3_[kAll       ]->SetMaximum( 1.3* btag3_[kAll]->GetMaximum() );
  btag3_[kAll       ]->Draw();
  btag3_[kSignal    ]->Draw("same");
  btag3_[kBackground]->Draw("same");
  //btag3_[kAll       ]->Draw("same");
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
  color.push_back( kBlack); 
  color.push_back( kRed  ); 
  color.push_back( kBlue );

  // pre-defined fill style
  std::vector<int> fill;
  fill.push_back(   1); 
  fill.push_back(3004); 
  fill.push_back(3005);

  // pre-defined marker style
  std::vector<int> marker;
  marker.push_back( 20);

  // set line width
  style==kAll ? hist.SetLineWidth(6) : hist.SetLineWidth(3);

  hist.SetStats(kFALSE);
  hist.SetLineColor  (color[style]);
  hist.SetFillColor  (color[style]);
  hist.SetMarkerColor(color[style]);
  hist.SetFillStyle  (fill [style]);

  if(style==kAll){
    hist.SetMarkerStyle(marker[style]);
    hist.SetMarkerSize(1.4);
  }
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
