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


void analyzeJetQuality()
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
  files_.push_back(new TFile("./rootfiles/analyzeJets_all.root") );
  files_.push_back(new TFile("./rootfiles/analyzeJets_sig.root") );
  files_.push_back(new TFile("./rootfiles/analyzeJets_bkg.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> emf_, n_, n90_, n60_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    emf_.push_back( (TH1F*)files_[idx]->Get("reliableJetQuality/emf" ) );
    n_.push_back( (TH1F*)files_[idx]->Get("reliableJetQuality/n_" ) );
    n90_.push_back( (TH1F*)files_[idx]->Get("reliableJetQuality/n90_" ) );
    n60_.push_back( (TH1F*)files_[idx]->Get("reliableJetQuality/n60_" ) );
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

  // emf_
  histogramStyle(*emf_  [kAll       ], kAll       );
  histogramStyle(*emf_  [kSignal    ], kSignal    );
  histogramStyle(*emf_  [kBackground], kBackground);

  // n_
  histogramStyle(*n_ [kAll       ], kAll       );
  histogramStyle(*n_ [kSignal    ], kSignal    );
  histogramStyle(*n_ [kBackground], kBackground);

  // n90_
  histogramStyle(*n90_ [kAll       ], kAll       );
  histogramStyle(*n90_ [kSignal    ], kSignal    );
  histogramStyle(*n90_ [kBackground], kBackground);

  // n60_
  histogramStyle(*n60_ [kAll       ], kAll       );
  histogramStyle(*n60_ [kSignal    ], kSignal    );
  histogramStyle(*n60_ [kBackground], kBackground);

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  leg0->AddEntry( emf_[kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( emf_[kSignal    ] , "semi-lep. ( #mu )" , "FL" );
  leg0->AddEntry( emf_[kBackground] , "other decays"      , "FL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  leg1->AddEntry( emf_[kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( emf_[kSignal    ] , "semi-lep. ( #mu )" , "FL" );
  leg1->AddEntry( emf_[kBackground] , "other decays"      , "FL" );

  // ---
  //    do the printing for emf_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  
  // draw canvas
  canv0->cd(0);
  axesStyle(*emf_[kAll], "Electromagnetic Fraction", "events");
  emf_[kAll       ]->SetMinimum(0.);
  emf_[kAll       ]->SetMaximum( 1.7* emf_[kAll]->GetMaximum() );
  emf_[kAll       ]->Draw();
  emf_[kSignal    ]->Draw("same");
  emf_[kBackground]->Draw("same");
  //emf_  [kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for n_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  axesStyle(*n_[kAll], "Number of Constituents", "events");
  n_[kAll       ]->SetMaximum( 1.3* n_[kAll]->GetMaximum() );
  n_[kAll       ]->Draw();
  n_[kSignal    ]->Draw("same");
  n_[kBackground]->Draw("same");
  //n_ [kAll       ]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for n90_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  axesStyle(*n90_[kAll], "Number of Constituents", "events");
  n90_[kAll       ]->SetMaximum( 1.3* n90_[kAll]->GetMaximum() );
  n90_[kAll       ]->Draw();
  n90_[kSignal    ]->Draw("same");
  n90_[kBackground]->Draw("same");
  //n90_ [kAll       ]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for n60_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  axesStyle(*n60_[kAll], "Number of Constituents", "events");
  n60_[kAll       ]->SetMaximum( 1.3* n60_[kAll]->GetMaximum() );
  n60_[kAll       ]->Draw();
  n60_[kSignal    ]->Draw("same");
  n60_[kBackground]->Draw("same");
  //n60_ [kAll       ]->Draw("same");
  leg0->Draw("same");
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
