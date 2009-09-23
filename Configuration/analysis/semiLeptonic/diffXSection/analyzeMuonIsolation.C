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


void analyzeMuonIsolation()
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
  std::vector<TH1F*> relIso_, trkIso_, calIso_, trkIsoN_, eclIsoN_, hclIsoN_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    relIso_ .push_back( (TH1F*)files_[idx]->Get("goldenMuonQuality/relIso"  ) );
    trkIso_ .push_back( (TH1F*)files_[idx]->Get("goldenMuonQuality/trkIso_" ) );
    calIso_ .push_back( (TH1F*)files_[idx]->Get("goldenMuonQuality/calIso_" ) );
    trkIsoN_.push_back( (TH1F*)files_[idx]->Get("goldenMuonQuality/trkIsoN_") );
    eclIsoN_.push_back( (TH1F*)files_[idx]->Get("goldenMuonQuality/eclIsoN_") );
    hclIsoN_.push_back( (TH1F*)files_[idx]->Get("goldenMuonQuality/hclIsoN_") );
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

  // relIso_
  histogramStyle(*relIso_ [kAll       ], kAll       );
  histogramStyle(*relIso_ [kSignal    ], kSignal    );
  histogramStyle(*relIso_ [kBackground], kBackground);

  // trkIso_
  histogramStyle(*trkIso_ [kAll       ], kAll       );
  histogramStyle(*trkIso_ [kSignal    ], kSignal    );
  histogramStyle(*trkIso_ [kBackground], kBackground);

  // calIso_
  histogramStyle(*calIso_ [kAll       ], kAll       );
  histogramStyle(*calIso_ [kSignal    ], kSignal    );
  histogramStyle(*calIso_ [kBackground], kBackground);

  // trkIsoN_
  histogramStyle(*trkIsoN_[kAll       ], kAll       );
  histogramStyle(*trkIsoN_[kSignal    ], kSignal    );
  histogramStyle(*trkIsoN_[kBackground], kBackground);

  // eclIsoN_
  histogramStyle(*eclIsoN_[kAll       ], kAll       );
  histogramStyle(*eclIsoN_[kSignal    ], kSignal    );
  histogramStyle(*eclIsoN_[kBackground], kBackground);

  // hclIsoN_
  histogramStyle(*hclIsoN_[kAll       ], kAll       );
  histogramStyle(*hclIsoN_[kSignal    ], kSignal    );
  histogramStyle(*hclIsoN_[kBackground], kBackground);

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  leg0->AddEntry( relIso_ [kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( relIso_ [kSignal    ] , "semi-lep. ( #mu )" , "FL" );
  leg0->AddEntry( relIso_ [kBackground] , "other decays"      , "FL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  leg1->AddEntry( relIso_ [kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( relIso_ [kSignal    ] , "semi-lep. ( #mu )" , "FL" );
  leg1->AddEntry( relIso_ [kBackground] , "other decays"      , "FL" );

  // ---
  //    do the printing for relIso_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  
  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  axesStyle(*relIso_ [kAll], "(#Sigma pt_{trk}+ #Sigma pt_{cal} )/pt(#mu)", "events");
  relIso_ [kAll       ]->SetMinimum(1.);
  relIso_ [kAll       ]->SetMaximum( 2.5* relIso_  [kAll]->GetMaximum() );
  relIso_ [kAll       ]->Draw();
  relIso_ [kSignal    ]->Draw("same");
  relIso_ [kBackground]->Draw("same");
  //relIso_ [kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for trkIso_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetLogy(1);
  axesStyle(*trkIso_ [kAll], "#Sigma pt_{trk}  [GeV]", "events");
  trkIso_ [kAll       ]->SetMinimum(1.);
  trkIso_ [kAll       ]->SetMaximum( 2.5* trkIso_ [kAll]->GetMaximum() );
  trkIso_ [kAll       ]->Draw();
  trkIso_ [kSignal    ]->Draw("same");
  trkIso_ [kBackground]->Draw("same");
  //trkIso_ [kAll       ]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for calIso_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetLogy(1);
  axesStyle(*calIso_ [kAll], "#Sigma pt_{cal}  [GeV]", "events");
  calIso_ [kAll       ]->SetMinimum(1.);
  calIso_ [kAll       ]->SetMaximum( 2.5* calIso_ [kAll]->GetMaximum() );
  calIso_ [kAll       ]->Draw();
  calIso_ [kSignal    ]->Draw("same");
  calIso_ [kBackground]->Draw("same");
  //calIso_ [kAll       ]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for trkIsoN_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  canv3->SetLogy(1);
  axesStyle(*trkIsoN_[kAll], "#Sigma N_{trk}", "events");
  trkIsoN_[kAll       ]->SetMinimum(1.);
  trkIsoN_[kAll       ]->SetMaximum( 10.0* trkIsoN_[kAll]->GetMaximum() );
  trkIsoN_[kAll       ]->Draw();
  trkIsoN_[kSignal    ]->Draw("same");
  trkIsoN_[kBackground]->Draw("same");
  //trkIsoN_[kAll       ]->Draw("same");
  leg1->Draw("same");

  // ---
  //    do the printing for eclIsoN_
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(*canv4);

  // draw canvas
  canv4->cd(0);
  canv4->SetLogy(1);
  axesStyle(*eclIsoN_[kAll], "#Sigma N_{ecal}", "events");
  eclIsoN_[kAll       ]->SetMinimum( 1.);
  eclIsoN_[kAll       ]->SetMaximum( 5.0* eclIsoN_[kAll]->GetMaximum() );
  eclIsoN_[kAll       ]->Draw();
  eclIsoN_[kSignal    ]->Draw("same");
  eclIsoN_[kBackground]->Draw("same");
  //eclIsoN_[kAll       ]->Draw("same");
  leg1->Draw("same");

  // ---
  //    do the printing for hclIsoN_
  // ---
  TCanvas* canv5 = new TCanvas("canv5", "canv5", 600, 600); canvasStyle(*canv5);

  // draw canvas
  canv5->cd(0);
  canv5->SetLogy(1);
  axesStyle(*hclIsoN_[kAll], "#Sigma N_{hcal}", "events");
  hclIsoN_[kAll       ]->SetMinimum( 1.);
  hclIsoN_[kAll       ]->SetMaximum( 2.5* hclIsoN_[kAll]->GetMaximum() );
  hclIsoN_[kAll       ]->Draw();
  hclIsoN_[kSignal    ]->Draw("same");
  hclIsoN_[kBackground]->Draw("same");
  //hclIsoN_[kAll       ]->Draw("same");
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
