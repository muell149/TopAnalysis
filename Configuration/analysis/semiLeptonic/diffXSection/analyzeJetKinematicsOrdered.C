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


void analyzeJetKinematicsOrdered(bool plotEta=false)
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
  std::vector<TH1F*> lead0_, lead1_, lead2_, lead3_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    if( !plotEta ){
      lead0_.push_back( (TH1F*)files_[idx]->Get("tightLead_0_JetKinematics/pt") );
      lead1_.push_back( (TH1F*)files_[idx]->Get("tightLead_1_JetKinematics/pt") );
      lead2_.push_back( (TH1F*)files_[idx]->Get("tightLead_2_JetKinematics/pt") );
      lead3_.push_back( (TH1F*)files_[idx]->Get("tightLead_3_JetKinematics/pt") );
    }
    else{
      lead0_.push_back( (TH1F*)files_[idx]->Get("tightLead_0_JetKinematics/eta") );
      lead1_.push_back( (TH1F*)files_[idx]->Get("tightLead_1_JetKinematics/eta") );
      lead2_.push_back( (TH1F*)files_[idx]->Get("tightLead_2_JetKinematics/eta") );
      lead3_.push_back( (TH1F*)files_[idx]->Get("tightLead_3_JetKinematics/eta") );
    }
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

  // lead0_
  histogramStyle(*lead0_[kAll       ], kAll       );
  histogramStyle(*lead0_[kSignal    ], kSignal    );
  histogramStyle(*lead0_[kBackground], kBackground);

  // lead1_
  histogramStyle(*lead1_[kAll       ], kAll       );
  histogramStyle(*lead1_[kSignal    ], kSignal    );
  histogramStyle(*lead1_[kBackground], kBackground);

  // lead2_
  histogramStyle(*lead2_[kAll       ], kAll       );
  histogramStyle(*lead2_[kSignal    ], kSignal    );
  histogramStyle(*lead2_[kBackground], kBackground);

  // lead3_
  histogramStyle(*lead3_[kAll       ], kAll       );
  histogramStyle(*lead3_[kSignal    ], kSignal    );
  histogramStyle(*lead3_[kBackground], kBackground);

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  leg0->AddEntry( lead0_[kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( lead0_[kSignal    ] , "semi-lep. ( #mu )" , "FL" );
  leg0->AddEntry( lead0_[kBackground] , "other decays"      , "FL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  leg1->AddEntry( lead0_[kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( lead0_[kSignal    ] , "semi-lep. ( #mu )" , "FL" );
  leg1->AddEntry( lead0_[kBackground] , "other decays"      , "FL" );
  
  // prepare axes labels
  if( !plotEta ){
    axesStyle(*lead0_[kAll], "pt( 1. Leading Jet ) [GeV]", "events" );
    axesStyle(*lead1_[kAll], "pt( 2. Leading Jet ) [GeV]", "events" );
    axesStyle(*lead2_[kAll], "pt( 3. Leading Jet ) [GeV]", "events" );
    axesStyle(*lead3_[kAll], "pt( 4. Leading Jet ) [GeV]", "events");
  }
  else{
    axesStyle(*lead0_[kAll], "#eta( 1. Leading Jet )", "events");
    axesStyle(*lead1_[kAll], "#eta( 2. Leading Jet )", "events");
    axesStyle(*lead2_[kAll], "#eta( 3. Leading Jet )", "events");
    axesStyle(*lead3_[kAll], "#eta( 4. Leading Jet )", "events");
  }

  // ---
  //    do the printing for lead0_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // draw canvas
  canv0->cd(0);
  lead0_[kAll       ]->SetMinimum(0.);
  lead0_[kAll       ]->SetMaximum(1.75 * lead0_[kAll]->GetMaximum() );
  lead0_[kAll       ]->Draw();
  lead0_[kSignal    ]->Draw("same");
  lead0_[kBackground]->Draw("same");
  //lead0_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for lead1_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  lead1_[kAll       ]->SetMinimum(0.);
  lead1_[kAll       ]->SetMaximum( 1.75 * lead1_[kAll]->GetMaximum() );
  lead1_[kAll       ]->Draw();
  lead1_[kSignal    ]->Draw("same");
  lead1_[kBackground]->Draw("same");
  //lead1_[kAll       ]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for lead2_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  lead2_[kAll       ]->SetMinimum( 0 );
  lead2_[kAll       ]->SetMaximum( 1.75 * lead2_[kAll]->GetMaximum() );
  lead2_[kAll       ]->Draw();
  lead2_[kSignal    ]->Draw("same");
  lead2_[kBackground]->Draw("same");
  //lead2_[kAll       ]->Draw("same");
  leg1->Draw("same");

  // ---
  //    do the printing for lead3_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  lead3_[kAll       ]->SetMinimum( 0 );
  lead3_[kAll       ]->SetMaximum( 1.75 * lead3_[kAll]->GetMaximum() );
  lead3_[kAll       ]->Draw();
  lead3_[kSignal    ]->Draw("same");
  lead3_[kBackground]->Draw("same");
  //lead3_[kAll       ]->Draw("same");
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
