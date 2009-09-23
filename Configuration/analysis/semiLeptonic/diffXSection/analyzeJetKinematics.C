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


void analyzeJetKinematics(bool runOnBTaggedJets=false)
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
  std::vector<TH1F*> n_, pt_, eta_, phi_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    if( !runOnBTaggedJets ){
      n_  .push_back( (TH1F*)files_[idx]->Get("tightLeadingJetKinematics/n"  ) );
      pt_ .push_back( (TH1F*)files_[idx]->Get("tightLeadingJetKinematics/pt" ) );
      eta_.push_back( (TH1F*)files_[idx]->Get("tightLeadingJetKinematics/eta") );
      phi_.push_back( (TH1F*)files_[idx]->Get("tightLeadingJetKinematics/phi") );
    }
    else{
      n_  .push_back( (TH1F*)files_[idx]->Get("tightBottomJetKinematics/n"  ) );
      pt_ .push_back( (TH1F*)files_[idx]->Get("tightBottomJetKinematics/pt" ) );
      eta_.push_back( (TH1F*)files_[idx]->Get("tightBottomJetKinematics/eta") );
      phi_.push_back( (TH1F*)files_[idx]->Get("tightBottomJetKinematics/phi") );
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

  // n_
  histogramStyle(*n_  [kAll       ], kAll       );
  histogramStyle(*n_  [kSignal    ], kSignal    );
  histogramStyle(*n_  [kBackground], kBackground);


  // pt_
  histogramStyle(*pt_ [kAll       ], kAll       );
  histogramStyle(*pt_ [kSignal    ], kSignal    );
  histogramStyle(*pt_ [kBackground], kBackground);

  // eta_
  histogramStyle(*eta_[kAll       ], kAll       );
  histogramStyle(*eta_[kSignal    ], kSignal    );
  histogramStyle(*eta_[kBackground], kBackground);

  // phi_
  histogramStyle(*phi_[kAll       ], kAll       );
  histogramStyle(*phi_[kSignal    ], kSignal    );
  histogramStyle(*phi_[kBackground], kBackground);


  // ---
  //    do the printing for n_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  leg0->AddEntry( n_  [kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( n_  [kSignal    ] , "semi-lep. ( #mu )" , "FL" );
  leg0->AddEntry( n_  [kBackground] , "other decays"      , "FL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  leg1->AddEntry( n_  [kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( n_  [kSignal    ] , "semi-lep. ( #mu )" , "FL" );
  leg1->AddEntry( n_  [kBackground] , "other decays"      , "FL" );
  
  // prepare axes labels
  if( !runOnBTaggedJets ){
    axesStyle(*n_  [kAll], "N_{Jet}(pt>30 GeV, |#eta|<2.4)", "events" );
    axesStyle(*pt_ [kAll], "pt( Jet ) [GeV]", "events" );
    axesStyle(*eta_[kAll], "#eta( Jet )", "events" );
    axesStyle(*phi_[kAll], "#phi( Jet )", "events");
  }
  else{
    axesStyle(*n_  [kAll], "N_{B-Jet}(pt>30 GeV, |#eta|<2.4)", "events");
    axesStyle(*pt_ [kAll], "pt( B-Jet ) [GeV]", "events");
    axesStyle(*eta_[kAll], "#eta( B-Jet )", "events");
    axesStyle(*phi_[kAll], "#phi( B-Jet )", "events");
  }

  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  n_  [kAll       ]->SetMinimum(1.);
  n_  [kAll       ]->SetMaximum( 5000* n_  [kAll]->GetMaximum() );
  n_  [kAll       ]->Draw();
  n_  [kSignal    ]->Draw("same");
  n_  [kBackground]->Draw("same");
  //n_  [kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for pt_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  pt_ [kAll       ]->SetMaximum( 1.75* pt_ [kAll]->GetMaximum() );
  pt_ [kAll       ]->Draw();
  pt_ [kSignal    ]->Draw("same");
  pt_ [kBackground]->Draw("same");
  //pt_ [kAll       ]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for eta_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  eta_[kAll       ]->SetMinimum( 0 );
  eta_[kAll       ]->SetMaximum( 1.7* eta_[kAll]->GetMaximum() );
  eta_[kAll       ]->Draw();
  eta_[kSignal    ]->Draw("same");
  eta_[kBackground]->Draw("same");
  //eta_[kAll       ]->Draw("same");
  leg1->Draw("same");

  // ---
  //    do the printing for phi_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  phi_[kAll       ]->SetMinimum( 0 );
  phi_[kAll       ]->SetMaximum( 2.0* phi_[kAll]->GetMaximum() );
  phi_[kAll       ]->Draw();
  phi_[kSignal    ]->Draw("same");
  phi_[kBackground]->Draw("same");
  //phi_[kAll       ]->Draw("same");
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
