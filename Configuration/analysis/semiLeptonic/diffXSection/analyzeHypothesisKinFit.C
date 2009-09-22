#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>

enum styles {kAll, kSignal};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);


void analyzeHypothesisKinFit()
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
  files_.push_back(new TFile("analyzeHypothesisKinFit_test.root") );
  files_.push_back(new TFile("analyzeHypothesisKinFit_test.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH2F*> jetHypo_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    jetHypo_.push_back( (TH2F*)files_[idx]->Get("analyzeHypothesisKinFit/jetHypo_"     ) );
  }

  std::vector<TH1F*> prob_, chi2_, hadBQuark_, lepBQuark_, lightQuark_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    prob_      .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/prob"      ) );
    chi2_      .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/chi2"      ) );
    hadBQuark_ .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/hadBQuark" ) );
    lepBQuark_ .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/lepBQuark" ) );
    lightQuark_.push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/lightQuark") );
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

  // kAll
  histogramStyle( *prob_      [kAll   ] , kAll    );
  histogramStyle( *chi2_      [kAll   ] , kAll    );
  histogramStyle( *hadBQuark_ [kAll   ] , kAll    );
  histogramStyle( *lepBQuark_ [kAll   ] , kAll    );
  histogramStyle( *lightQuark_[kAll   ] , kAll    );

  // kSignal
  histogramStyle( *prob_      [kSignal] , kSignal );
  histogramStyle( *chi2_      [kSignal] , kSignal );
  histogramStyle( *hadBQuark_ [kSignal] , kSignal );
  histogramStyle( *lepBQuark_ [kSignal] , kSignal );
  histogramStyle( *lightQuark_[kSignal] , kSignal );


  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  leg0->AddEntry( prob_[kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( prob_[kSignal    ] , "semi-lep. ( #mu )" , "FL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  leg1->AddEntry( prob_[kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( prob_[kSignal    ] , "semi-lep. ( #mu )" , "FL" );

  // ---
  //    do the printing for prob_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  
  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  axesStyle(*prob_[kAll], "Fit Probability", "events");
  //prob_[kAll       ]->SetMinimum(1.);
  prob_[kAll       ]->SetMaximum( 2.5* prob_[kAll]->GetMaximum() );
  prob_[kAll       ]->Draw();
  prob_[kSignal    ]->Draw("same");
  //prob_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for chi2_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetLogy(1);
  axesStyle(*chi2_ [kAll], "#chi^{2}/ndof", "events");
  chi2_ [kAll       ]->SetMaximum( 2.5* chi2_ [kAll]->GetMaximum() );
  chi2_ [kAll       ]->Draw();
  chi2_ [kSignal    ]->Draw("same");
  //chi2_ [kAll       ]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for hadBQuark_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  //canv2->SetLogy(1);
  axesStyle(*hadBQuark_ [kAll], "#Delta Index(genMatch, KinFit)_{hadB}", "events");
  //hadBQuark_ [kAll       ]->SetMinimum(1.);
  hadBQuark_ [kAll       ]->SetMaximum( 1.7* hadBQuark_ [kAll]->GetMaximum() );
  hadBQuark_ [kAll       ]->Draw();
  hadBQuark_ [kSignal    ]->Draw("same");
  //hadBQuark_ [kAll       ]->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for lepBQuark_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  //canv3->SetLogy(1);
  axesStyle(*lepBQuark_[kAll], "#Delta Index(genMatch, KinFit)_{lepB}", "events");
  //lepBQuark_[kAll       ]->SetMinimum(1.);
  lepBQuark_[kAll       ]->SetMaximum( 1.7* lepBQuark_[kAll]->GetMaximum() );
  lepBQuark_[kAll       ]->Draw();
  lepBQuark_[kSignal    ]->Draw("same");
  //lepBQuark_[kAll       ]->Draw("same");
  leg1->Draw("same");

  // ---
  //    do the printing for lightQuark_
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(*canv4);

  // draw canvas
  canv4->cd(0);
  //canv4->SetLogy(1);
  axesStyle(*lightQuark_[kAll], "#Delta Index(genMatch, KinFit)_{lightQ}", "events");
  //lightQuark_[kAll       ]->SetMinimum( 1.);
  lightQuark_[kAll       ]->SetMaximum( 1.7* lightQuark_[kAll]->GetMaximum() );
  lightQuark_[kAll       ]->Draw();
  lightQuark_[kSignal    ]->Draw("same");
  //lightQuark_[kAll       ]->Draw("same");
  leg1->Draw("same");

  // ---
  //    do the printing for lightQuakr_
  // ---
  TCanvas* canv5 = new TCanvas("canv5", "canv5", 600, 600); canvasStyle(*canv5);

  // draw canvas
  canv5->cd(0);
  //canv4->SetLogy(1);
  jetHypo_[kAll]->SetTitle("");
  jetHypo_[kAll]->GetXaxis( )->SetTitle();
  jetHypo_[kAll]->GetXaxis( )->SetBinLabel( 1, "lighQ"     );
  jetHypo_[kAll]->GetXaxis( )->SetBinLabel( 2, "lighQBar"  );
  jetHypo_[kAll]->GetXaxis( )->SetBinLabel( 3, "hadronicB" );
  jetHypo_[kAll]->GetXaxis( )->SetBinLabel( 4, "leptonicB" );
  jetHypo_[kAll]->GetXaxis( )->SetLabelColor(      1   );
  jetHypo_[kAll]->GetXaxis( )->SetLabelFont (     62   );
  jetHypo_[kAll]->GetXaxis( )->SetLabelSize (   0.06   );
  jetHypo_[kAll]->GetXaxis()->SetTickLength (     0.   );
  jetHypo_[kAll]->SetLabelOffset            (   .02    );
  jetHypo_[kAll]->LabelsOption              ( "u", "X" );

  jetHypo_[kAll]->GetYaxis( )->SetTitle( "Index in Jet Collection" );
  jetHypo_[kAll]->GetYaxis()->SetTitleSize  ( 0.07);
  jetHypo_[kAll]->GetYaxis()->SetTitleColor (    1);
  jetHypo_[kAll]->GetYaxis()->SetTitleOffset(  0.7);
  jetHypo_[kAll]->GetYaxis()->SetTitleFont  (   62);
  jetHypo_[kAll]->GetYaxis()->SetLabelSize  ( 0.04);
  jetHypo_[kAll]->GetYaxis()->SetLabelFont  (   62);
  jetHypo_[kAll]->GetYaxis()->SetNdivisions (  505);

  jetHypo_[kAll]->SetStats(kFALSE);
  jetHypo_[kAll]->SetFillColor( kBlue );
  jetHypo_[kAll]->Draw("box");
  //leg1->Draw("same");
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
  color.push_back( kBlue ); 
  color.push_back( kRed  );

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
