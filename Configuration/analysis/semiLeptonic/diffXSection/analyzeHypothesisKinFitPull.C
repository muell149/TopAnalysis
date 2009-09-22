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


void analyzeHypothesisKinFitPull()
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
  files_.push_back(new TFile("~rwolf/public/rootfiles/analyzeHypothesisKinFit_test1.root") );
  files_.push_back(new TFile("~rwolf/public/rootfiles/analyzeHypothesisKinFit_test1.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> hadBQuarkPt_, hadBQuarkEta_, hadBQuarkPhi_, lepBQuarkPt_, lepBQuarkEta_, lepBQuarkPhi_, lightQuarkPt_, lightQuarkEta_, lightQuarkPhi_, leptonPt_, leptonEta_, leptonPhi_, neutrinoPt_, neutrinoEta_, neutrinoPhi_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    hadBQuarkPt_  .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/hadBQuarkPt"  ) );
    hadBQuarkEta_ .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/hadBQuarkEta" ) );
    hadBQuarkPhi_ .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/hadBQuarkPhi" ) );
    lepBQuarkPt_  .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/lepBQuarkPt"  ) );
    lepBQuarkEta_ .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/lepBQuarkEta" ) );
    lepBQuarkPhi_ .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/lepBQuarkPhi" ) );
    lightQuarkPt_ .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/lightQuarkPt" ) );
    lightQuarkEta_.push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/lightQuarkEta") );
    lightQuarkPhi_.push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/lightQuarkPhi") );
    leptonPt_     .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/leptonPt"     ) );
    leptonEta_    .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/leptonEta"    ) );
    leptonPhi_    .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/leptonPhi"    ) );
    neutrinoPt_   .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/neutrinoPt"   ) );
    neutrinoEta_  .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/neutrinoEta"  ) );
    neutrinoPhi_  .push_back( (TH1F*)files_[idx]->Get("analyzeHypothesisKinFit/neutrinoPhi"  ) );
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
  histogramStyle( *hadBQuarkPt_  [kAll   ] , kAll    );
  histogramStyle( *hadBQuarkEta_ [kAll   ] , kAll    );
  histogramStyle( *hadBQuarkPhi_ [kAll   ] , kAll    );
  histogramStyle( *lepBQuarkPt_  [kAll   ] , kAll    );
  histogramStyle( *lepBQuarkEta_ [kAll   ] , kAll    );
  histogramStyle( *lepBQuarkPhi_ [kAll   ] , kAll    );
  histogramStyle( *lightQuarkPt_ [kAll   ] , kAll    );
  histogramStyle( *lightQuarkEta_[kAll   ] , kAll    );
  histogramStyle( *lightQuarkPhi_[kAll   ] , kAll    );
  histogramStyle( *leptonPt_     [kAll   ] , kAll    );
  histogramStyle( *leptonEta_    [kAll   ] , kAll    );
  histogramStyle( *leptonPhi_    [kAll   ] , kAll    );
  histogramStyle( *neutrinoPt_   [kAll   ] , kAll    );
  histogramStyle( *neutrinoEta_  [kAll   ] , kAll    );
  histogramStyle( *neutrinoPhi_  [kAll   ] , kAll    );

  // kSignal
  histogramStyle( *hadBQuarkPt_  [kSignal] , kSignal );
  histogramStyle( *hadBQuarkEta_ [kSignal] , kSignal );
  histogramStyle( *hadBQuarkPhi_ [kSignal] , kSignal );
  histogramStyle( *lepBQuarkPt_  [kSignal] , kSignal );
  histogramStyle( *lepBQuarkEta_ [kSignal] , kSignal );
  histogramStyle( *lepBQuarkPhi_ [kSignal] , kSignal );
  histogramStyle( *lightQuarkPt_ [kSignal] , kSignal );
  histogramStyle( *lightQuarkEta_[kSignal] , kSignal );
  histogramStyle( *lightQuarkPhi_[kSignal] , kSignal );
  histogramStyle( *leptonPt_     [kSignal] , kSignal );
  histogramStyle( *leptonEta_    [kSignal] , kSignal );
  histogramStyle( *leptonPhi_    [kSignal] , kSignal );
  histogramStyle( *neutrinoPt_   [kSignal] , kSignal );
  histogramStyle( *neutrinoEta_  [kSignal] , kSignal );
  histogramStyle( *neutrinoPhi_  [kSignal] , kSignal );


  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  leg0->AddEntry( hadBQuarkPt_[kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( hadBQuarkPt_[kSignal    ] , "semi-lep. ( #mu )" , "FL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  leg1->AddEntry( hadBQuarkPt_[kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( hadBQuarkPt_[kSignal    ] , "semi-lep. ( #mu )" , "FL" );

  // ---
  //    do the printing for hadBQuarkPt_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  
  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(0);
  axesStyle(*hadBQuarkPt_[kAll], "hadronic b quark: pull of p_{t}", "events");
  //hadBQuarkPt_[kAll       ]->SetMinimum(1.);
  hadBQuarkPt_[kAll       ]->SetMaximum( 1.7* hadBQuarkPt_[kAll]->GetMaximum() );
  hadBQuarkPt_[kAll       ]->Draw();
  hadBQuarkPt_[kSignal    ]->Draw("same");
  //hadBQuarkPt_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for hadBQuarkEta_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);
  
  // draw canvas
  canv1->cd(0);
  canv1->SetLogy(0);
  axesStyle(*hadBQuarkEta_[kAll], "hadronic b quark: pull of #eta", "events");
  //hadBQuarkEta_[kAll       ]->SetMinimum(1.);
  hadBQuarkEta_[kAll       ]->SetMaximum( 1.7* hadBQuarkEta_[kAll]->GetMaximum() );
  hadBQuarkEta_[kAll       ]->Draw();
  hadBQuarkEta_[kSignal    ]->Draw("same");
  //hadBQuarkEta_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for hadBQuarkPhi_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);
  
  // draw canvas
  canv2->cd(0);
  canv2->SetLogy(0);
  axesStyle(*hadBQuarkPhi_[kAll], "hadronic b quark: pull of #phi", "events");
  //hadBQuarkPhi_[kAll       ]->SetMinimum(1.);
  hadBQuarkPhi_[kAll       ]->SetMaximum( 1.7* hadBQuarkPhi_[kAll]->GetMaximum() );
  hadBQuarkPhi_[kAll       ]->Draw();
  hadBQuarkPhi_[kSignal    ]->Draw("same");
  //hadBQuarkPhi_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for lepBQuarkPt_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);
  
  // draw canvas
  canv3->cd(0);
  canv3->SetLogy(0);
  axesStyle(*lepBQuarkPt_[kAll], "leptonic b quark: pull of p_{t}", "events");
  //lepBQuarkPt_[kAll       ]->SetMinimum(1.);
  lepBQuarkPt_[kAll       ]->SetMaximum( 1.7* lepBQuarkPt_[kAll]->GetMaximum() );
  lepBQuarkPt_[kAll       ]->Draw();
  lepBQuarkPt_[kSignal    ]->Draw("same");
  //lepBQuarkPt_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for lepBQuarkEta_
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(*canv4);
  
  // draw canvas
  canv4->cd(0);
  canv4->SetLogy(0);
  axesStyle(*lepBQuarkEta_[kAll], "leptonic b quark: pull of #eta", "events");
  //lepBQuarkEta_[kAll       ]->SetMinimum(1.);
  lepBQuarkEta_[kAll       ]->SetMaximum( 1.7* lepBQuarkEta_[kAll]->GetMaximum() );
  lepBQuarkEta_[kAll       ]->Draw();
  lepBQuarkEta_[kSignal    ]->Draw("same");
  //lepBQuarkEta_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for lepBQuarkPhi_
  // ---
  TCanvas* canv5 = new TCanvas("canv5", "canv5", 600, 600); canvasStyle(*canv5);
  
  // draw canvas
  canv5->cd(0);
  canv5->SetLogy(0);
  axesStyle(*lepBQuarkPhi_[kAll], "leptonic b quark: pull of #phi", "events");
  //lepBQuarkPhi_[kAll       ]->SetMinimum(1.);
  lepBQuarkPhi_[kAll       ]->SetMaximum( 1.7* lepBQuarkPhi_[kAll]->GetMaximum() );
  lepBQuarkPhi_[kAll       ]->Draw();
  lepBQuarkPhi_[kSignal    ]->Draw("same");
  //lepBQuarkPhi_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for lightQuarkPt_
  // ---
  TCanvas* canv6 = new TCanvas("canv6", "canv6", 600, 600); canvasStyle(*canv6);
  
  // draw canvas
  canv6->cd(0);
  canv6->SetLogy(0);
  axesStyle(*lightQuarkPt_[kAll], "light quark: pull of p_{t}", "events");
  //lightQuarkPt_[kAll       ]->SetMinimum(1.);
  lightQuarkPt_[kAll       ]->SetMaximum( 1.7* lightQuarkPt_[kAll]->GetMaximum() );
  lightQuarkPt_[kAll       ]->Draw();
  lightQuarkPt_[kSignal    ]->Draw("same");
  //lightQuarkPt_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for lightQuarkEta_
  // ---
  TCanvas* canv7 = new TCanvas("canv7", "canv7", 600, 600); canvasStyle(*canv7);
  
  // draw canvas
  canv7->cd(0);
  canv7->SetLogy(0);
  axesStyle(*lightQuarkEta_[kAll], "light quark: pull of #eta", "events");
  //lightQuarkEta_[kAll       ]->SetMinimum(1.);
  lightQuarkEta_[kAll       ]->SetMaximum( 1.7* lightQuarkEta_[kAll]->GetMaximum() );
  lightQuarkEta_[kAll       ]->Draw();
  lightQuarkEta_[kSignal    ]->Draw("same");
  //lightQuarkEta_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for lightQuarkPhi_
  // ---
  TCanvas* canv8 = new TCanvas("canv8", "canv8", 600, 600); canvasStyle(*canv8);
  
  // draw canvas
  canv8->cd(0);
  canv8->SetLogy(0);
  axesStyle(*lightQuarkPhi_[kAll], "light quark: pull of #phi", "events");
  //lightQuarkPhi_[kAll       ]->SetMinimum(1.);
  lightQuarkPhi_[kAll       ]->SetMaximum( 1.7* lightQuarkPhi_[kAll]->GetMaximum() );
  lightQuarkPhi_[kAll       ]->Draw();
  lightQuarkPhi_[kSignal    ]->Draw("same");
  //lightQuarkPhi_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for leptonPt_
  // ---
  TCanvas* canv9 = new TCanvas("canv9", "canv9", 600, 600); canvasStyle(*canv9);
  
  // draw canvas
  canv9->cd(0);
  canv9->SetLogy(0);
  axesStyle(*leptonPt_[kAll], "lepton: pull of p_{t}", "events");
  //leptonPt_[kAll       ]->SetMinimum(1.);
  leptonPt_[kAll       ]->SetMaximum( 1.7* leptonPt_[kAll]->GetMaximum() );
  leptonPt_[kAll       ]->Draw();
  leptonPt_[kSignal    ]->Draw("same");
  //leptonPt_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for leptonEta_
  // ---
  TCanvas* canv10 = new TCanvas("canv10", "canv10", 600, 600); canvasStyle(*canv10);
  
  // draw canvas
  canv10->cd(0);
  canv10->SetLogy(0);
  axesStyle(*leptonEta_[kAll], "lepton: pull of #eta", "events");
  //leptonEta_[kAll       ]->SetMinimum(1.);
  leptonEta_[kAll       ]->SetMaximum( 1.7* leptonEta_[kAll]->GetMaximum() );
  leptonEta_[kAll       ]->Draw();
  leptonEta_[kSignal    ]->Draw("same");
  //leptonEta_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for leptonPhi_
  // ---
  TCanvas* canv11 = new TCanvas("canv11", "canv11", 600, 600); canvasStyle(*canv11);
  
  // draw canvas
  canv11->cd(0);
  canv11->SetLogy(0);
  axesStyle(*leptonPhi_[kAll], "lepton: pull of #phi", "events");
  //leptonPhi_[kAll       ]->SetMinimum(1.);
  leptonPhi_[kAll       ]->SetMaximum( 1.7* leptonPhi_[kAll]->GetMaximum() );
  leptonPhi_[kAll       ]->Draw();
  leptonPhi_[kSignal    ]->Draw("same");
  //leptonPhi_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for neutrinoPt_
  // ---
  TCanvas* canv12 = new TCanvas("canv12", "canv12", 600, 600); canvasStyle(*canv12);
  
  // draw canvas
  canv12->cd(0);
  canv12->SetLogy(0);
  axesStyle(*neutrinoPt_[kAll], "neutrino: pull of p_{t}", "events");
  //neutrinoPt_[kAll       ]->SetMinimum(1.);
  neutrinoPt_[kAll       ]->SetMaximum( 1.7* neutrinoPt_[kAll]->GetMaximum() );
  neutrinoPt_[kAll       ]->Draw();
  neutrinoPt_[kSignal    ]->Draw("same");
  //neutrinoPt_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for neutrinoEta_
  // ---
  TCanvas* canv13 = new TCanvas("canv13", "canv13", 600, 600); canvasStyle(*canv13);
  
  // draw canvas
  canv13->cd(0);
  canv13->SetLogy(0);
  axesStyle(*neutrinoEta_[kAll], "neutrino: pull of #eta", "events");
  //neutrinoEta_[kAll       ]->SetMinimum(1.);
  neutrinoEta_[kAll       ]->SetMaximum( 1.7* neutrinoEta_[kAll]->GetMaximum() );
  neutrinoEta_[kAll       ]->Draw();
  neutrinoEta_[kSignal    ]->Draw("same");
  //neutrinoEta_[kAll       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for neutrinoPhi_
  // ---
  TCanvas* canv14 = new TCanvas("canv14", "canv14", 600, 600); canvasStyle(*canv14);
  
  // draw canvas
  canv14->cd(0);
  canv14->SetLogy(0);
  axesStyle(*neutrinoPhi_[kAll], "neutrino: pull of #phi", "events");
  //neutrinoPhi_[kAll       ]->SetMinimum(1.);
  neutrinoPhi_[kAll       ]->SetMaximum( 1.7* neutrinoPhi_[kAll]->GetMaximum() );
  neutrinoPhi_[kAll       ]->Draw();
  neutrinoPhi_[kSignal    ]->Draw("same");
  //neutrinoPhi_[kAll       ]->Draw("esame");
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
