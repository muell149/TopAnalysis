#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>

enum styles {kGen, kGenMatch, kKinFit};

std::vector<TH1F*> topPt_,     topY_,      topPhi_, 
std::vector<TH1F*> ttbarPt_,   ttbarEta_,  ttbarPhi_;
std::vector<TH1F*> ttbarMass_, ttbarDelY_, ttbarSumY_, ttbarDelPhi_;

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);


void fillHistograms(const char* directory)
{
  std::string directory = directory;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    // fill the generator information 
    topPt_      .push_back( (TH1F*)files_[idx]->Get( directory+"/topPt"._str()       ) );
    topY_       .push_back( (TH1F*)files_[idx]->Get( directory+"/topY"._str()        ) );
    topPhi_     .push_back( (TH1F*)files_[idx]->Get( directory+"/topPhi"._str()      ) );
    ttbarPt_    .push_back( (TH1F*)files_[idx]->Get( directory+"/ttbarPt"._str()     ) );
    ttbarEta_   .push_back( (TH1F*)files_[idx]->Get( directory+"/ttbarY"._str()      ) );
    ttbarPhi_   .push_back( (TH1F*)files_[idx]->Get( directory+"/ttbarPhi"._str()    ) );
    ttbarMass_  .push_back( (TH1F*)files_[idx]->Get( directory+"/ttbarMass"._str()   ) );
    ttbarDelY_  .push_back( (TH1F*)files_[idx]->Get( directory+"/ttbarDelY"._str()   ) );
    ttbarSumY_  .push_back( (TH1F*)files_[idx]->Get( directory+"/ttbarSumY"._str()   ) );
    ttbarDelPhi_.push_back( (TH1F*)files_[idx]->Get( directory+"/ttbarDelPhi"._str() ) );
}

void analyzeTopKinematics()
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
  files_.push_back(new TFile("") );

  // ---
  //    get histograms
  // ---
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    // fill the generator information 
    fillHistograms("analyzeTopGenKinematics"          );
    fillHistograms("analyzeRecoGenKinematicsGenMatch" );
    fillHistograms("analyzeRecoGenKinematicsKinFit"   );
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

  // topPt_
  histogramStyle(*topPt_  [kGen       ], kGen       );
  histogramStyle(*topPt_  [kGenMatch  ], kGenMatch  );
  histogramStyle(*topPt_  [kKinFit    ], kKinFit);


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
  
  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  axesStyle(*n_  [kAll], "N_{#mu}(pt>20 GeV, |#eta|<2.1)", "events");
  n_  [kAll       ]->SetMinimum(1.);
  n_  [kAll       ]->SetMaximum( 2.5* n_  [kAll]->GetMaximum() );
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
  axesStyle(*pt_ [kAll], "pt( #mu ) [GeV]", "events");
  pt_ [kAll       ]->SetMaximum( 1.2* pt_ [kAll]->GetMaximum() );
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
  axesStyle(*eta_[kAll], "#eta( #mu )", "events");
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
  axesStyle(*phi_[kAll], "#phi( #mu )", "events");
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
