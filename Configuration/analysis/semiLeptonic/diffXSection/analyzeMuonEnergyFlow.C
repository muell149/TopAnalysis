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


void analyzeMuonEnergyFlow()
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
  files_.push_back(new TFile("./rootfiles/analyzeSelection_all.root") );
  files_.push_back(new TFile("./rootfiles/analyzeSelection_sig.root") );
  files_.push_back(new TFile("./rootfiles/analyzeSelection_bkg.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> norm_, trkDRN_, trkDR_, eclDRN_, hclDRN_, calDR_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    norm_  .push_back( (TH1F*)files_[idx]->Get("goldenMuonQuality/norm_"   ) );
    trkDRN_.push_back( (TH1F*)files_[idx]->Get("goldenMuonQuality/trkDRN_" ) );
    trkDR_ .push_back( (TH1F*)files_[idx]->Get("goldenMuonQuality/trkDR_"  ) );
    eclDRN_.push_back( (TH1F*)files_[idx]->Get("goldenMuonQuality/eclDRN_" ) );
    hclDRN_.push_back( (TH1F*)files_[idx]->Get("goldenMuonQuality/hclDRN_" ) );
    calDR_ .push_back( (TH1F*)files_[idx]->Get("goldenMuonQuality/calDR_"  ) );
  }

  // ---
  //    close input files
  // ---
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    //files_[idx]->Close();
  }
  
  // ---
  //    configure histograms
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    trkDRN_[idx]->Scale(1./norm_[idx]->Integral());  
    trkDR_ [idx]->Scale(1./norm_[idx]->Integral());  
    eclDRN_[idx]->Scale(1./norm_[idx]->Integral());  
    hclDRN_[idx]->Scale(1./norm_[idx]->Integral());  
    calDR_ [idx]->Scale(1./norm_[idx]->Integral());  
  }

  // trkDRN_
  histogramStyle(*trkDRN_[kAll       ], kAll       );
  histogramStyle(*trkDRN_[kSignal    ], kSignal    );
  histogramStyle(*trkDRN_[kBackground], kBackground);

  // trkDR_
  histogramStyle(*trkDR_ [kAll       ], kAll       );
  histogramStyle(*trkDR_ [kSignal    ], kSignal    );
  histogramStyle(*trkDR_ [kBackground], kBackground);

  // eclDRN_
  histogramStyle(*eclDRN_[kAll       ], kAll       );
  histogramStyle(*eclDRN_[kSignal    ], kSignal    );
  histogramStyle(*eclDRN_[kBackground], kBackground);

  // hclDRN_
  histogramStyle(*hclDRN_[kAll       ], kAll       );
  histogramStyle(*hclDRN_[kSignal    ], kSignal    );
  histogramStyle(*hclDRN_[kBackground], kBackground);

  // calDR_
  histogramStyle(*calDR_ [kAll       ], kAll       );
  histogramStyle(*calDR_ [kSignal    ], kSignal    );
  histogramStyle(*calDR_ [kBackground], kBackground);

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  leg0->AddEntry( trkDRN_[kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( trkDRN_[kSignal    ] , "semi-lep. ( #mu )" , "FL" );
  leg0->AddEntry( trkDRN_[kBackground] , "other decays"      , "FL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  leg1->AddEntry( trkDRN_[kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( trkDRN_[kSignal    ] , "semi-lep. ( #mu )" , "FL" );
  leg1->AddEntry( trkDRN_[kBackground] , "other decays"      , "FL" );

  // ---
  //    do the printing for trkDRN_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  
  // draw canvas
  canv0->cd(0);
  //canv0->SetLogy(1);
  axesStyle(*trkDRN_[kAll], "#Delta R (#mu, track)", "1/N_{#mu} #Sigma N_{trk}");
  //trkDRN_[kAll       ]->SetMinimum(1.);
  trkDRN_[kAll       ]->SetMaximum( 1.7* trkDRN_[kAll]->GetMaximum() );
  trkDRN_[kAll       ]->Draw();
  trkDRN_[kSignal    ]->Draw("same");
  trkDRN_[kBackground]->Draw("same");
  //trkDRN_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for trkDR_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  //canv1->SetLogy(1);
  axesStyle(*trkDR_ [kAll], "#Delta R (#mu, track)", "1/N_{#mu} #Sigma pt_{trk} [GeV]");
  //trkDR_ [kAll       ]->SetMinimum(1.);
  trkDR_ [kAll       ]->SetMaximum( 1.7* trkDR_ [kAll]->GetMaximum() );
  trkDR_ [kAll       ]->Draw();
  trkDR_ [kSignal    ]->Draw("same");
  trkDR_ [kBackground]->Draw("same");
  //trkDR_ [kAll       ]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for eclDRN_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  //canv2->SetLogy(1);
  axesStyle(*eclDRN_ [kAll], "#Delta R (#mu, deposit)", "1/N_{#mu} #Sigma N_{ecal}");
  //eclDRN_ [kAll       ]->SetMinimum(1.);
  eclDRN_ [kAll       ]->SetMaximum( 1.7* eclDRN_ [kAll]->GetMaximum() );
  eclDRN_ [kAll       ]->Draw();
  eclDRN_ [kSignal    ]->Draw("same");
  eclDRN_ [kBackground]->Draw("same");
  //eclDRN_ [kAll       ]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for hclDRN_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  //canv3->SetLogy(1);
  axesStyle(*hclDRN_[kAll], "#Delta R (#mu, deposit)", "1/N_{#mu} #Sigma N_{hcal}");
  //hclDRN_[kAll       ]->SetMinimum(1.);
  hclDRN_[kAll       ]->SetMaximum( 1.7* hclDRN_[kAll]->GetMaximum() );
  hclDRN_[kAll       ]->Draw();
  hclDRN_[kSignal    ]->Draw("same");
  hclDRN_[kBackground]->Draw("same");
  //hclDRN_[kAll       ]->Draw("same");
  leg1->Draw("same");

  // ---
  //    do the printing for calDR_
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(*canv4);

  // draw canvas
  canv4->cd(0);
  //canv4->SetLogy(1);
  axesStyle(*calDR_[kAll], "#Delta R (#mu, deposit)", "1/N_{#mu} #Sigma pt_{calo}");
  //calDR_[kAll       ]->SetMinimum( 1.);
  calDR_[kAll       ]->SetMaximum( 1.7* calDR_[kAll]->GetMaximum() );
  calDR_[kAll       ]->Draw();
  calDR_[kSignal    ]->Draw("same");
  calDR_[kBackground]->Draw("same");
  //calDR_[kAll       ]->Draw("same");
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
  hist.GetXaxis()->SetTitleOffset(  0.8);
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
