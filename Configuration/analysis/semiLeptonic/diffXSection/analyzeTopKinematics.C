#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>

enum styles {kGen, kGenMatch, kKinFit};

std::vector<TH1F*> topPt_,     topY_,      topPhi_; 
std::vector<TH1F*> ttbarPt_,   ttbarY_,    ttbarPhi_;
std::vector<TH1F*> ttbarMass_, ttbarDelY_, ttbarSumY_, ttbarDelPhi_;

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);
void fillHistograms(std::vector<TFile*>& files_, const char* directory);

void fillHistograms(std::vector<TFile*>& files_, const char* directories_)
{
  std::string directory = directories_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    // fill the generator information 
    topPt_      .push_back( (TH1F*)files_[idx]->Get( (directory+"/topPt").c_str()       ) );
    topY_       .push_back( (TH1F*)files_[idx]->Get( (directory+"/topY").c_str()        ) );
    topPhi_     .push_back( (TH1F*)files_[idx]->Get( (directory+"/topPhi").c_str()      ) );
    ttbarPt_    .push_back( (TH1F*)files_[idx]->Get( (directory+"/ttbarPt").c_str()     ) );
    ttbarY_     .push_back( (TH1F*)files_[idx]->Get( (directory+"/ttbarY").c_str()      ) );
    ttbarPhi_   .push_back( (TH1F*)files_[idx]->Get( (directory+"/ttbarPhi").c_str()    ) );
    ttbarMass_  .push_back( (TH1F*)files_[idx]->Get( (directory+"/ttbarMass").c_str()   ) );
    ttbarDelY_  .push_back( (TH1F*)files_[idx]->Get( (directory+"/ttbarDelY").c_str()   ) );
    ttbarSumY_  .push_back( (TH1F*)files_[idx]->Get( (directory+"/ttbarSumY").c_str()   ) );
    ttbarDelPhi_.push_back( (TH1F*)files_[idx]->Get( (directory+"/ttbarDelPhi").c_str() ) );
  }
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
  files_.push_back(new TFile("./analyzeTopQuarks.root") );

  // ---
  //    get histograms
  // ---
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    // fill the generator information 
    fillHistograms(files_, "analyzeTopGenKinematics"          );
    fillHistograms(files_, "analyzeTopRecoKinematicsGenMatch" );
    fillHistograms(files_, "analyzeTopRecoKinematicsKinFit"   );
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

  // topY_
  histogramStyle(*topY_  [kGen       ], kGen       );
  histogramStyle(*topY_  [kGenMatch  ], kGenMatch  );
  histogramStyle(*topY_  [kKinFit    ], kKinFit);

  // topPhi_
  histogramStyle(*topPhi_  [kGen       ], kGen       );
  histogramStyle(*topPhi_  [kGenMatch  ], kGenMatch  );
  histogramStyle(*topPhi_  [kKinFit    ], kKinFit);

  // ttbarPt_
  histogramStyle(*ttbarPt_  [kGen       ], kGen       );
  histogramStyle(*ttbarPt_  [kGenMatch  ], kGenMatch  );
  histogramStyle(*ttbarPt_  [kKinFit    ], kKinFit);

  // ttbarY_
  histogramStyle(*ttbarY_  [kGen       ], kGen       );
  histogramStyle(*ttbarY_  [kGenMatch  ], kGenMatch  );
  histogramStyle(*ttbarY_  [kKinFit    ], kKinFit);

  // ttbarMass_
  histogramStyle(*ttbarMass_  [kGen       ], kGen       );
  histogramStyle(*ttbarMass_  [kGenMatch  ], kGenMatch  );
  histogramStyle(*ttbarMass_  [kKinFit    ], kKinFit);

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(after selection)");
  leg0->AddEntry( topPt_  [kGen       ] , "generated"         , "PL" );
  leg0->AddEntry( topPt_  [kGenMatch    ] , "reco(matched)" , "FL" );
  leg0->AddEntry( topPt_  [kKinFit] , "reco(kin. fit)"      , "FL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(after selection)");
  leg1->AddEntry( topPt_  [kGen       ] , "generated"         , "PL" );
  leg1->AddEntry( topPt_  [kGenMatch    ] , "reco(matched)" , "FL" );
  leg1->AddEntry( topPt_  [kKinFit] , "reco(kin. fit)"      , "FL" );

  // ---
  //    do the printing for topPt_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  
  // draw canvas
  canv0->cd(0);
  //canv0->SetLogy(1);
  axesStyle(*topPt_  [kGen], "pt(Top Quark) [GeV]", "candidates");
  topPt_  [kGen     ]->SetMinimum(0.);
  topPt_  [kGen     ]->SetMaximum( 1.7* topPt_[kGen]->GetMaximum() );
  topPt_  [kGen     ]->Draw();
  topPt_  [kGenMatch]->Draw("same");
  topPt_  [kKinFit  ]->Draw("same");
  //topPt_  [kGen       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for topY_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);
  
  // draw canvas
  canv1->cd(0);
  //canv0->SetLogy(1);
  axesStyle(*topY_  [kGen], "Rapidity(Top Quark)", "candidates");
  topY_  [kGen     ]->SetMinimum(0.);
  topY_  [kGen     ]->SetMaximum( 2.5* topY_[kGen]->GetMaximum() );
  topY_  [kGen     ]->Draw();
  topY_  [kGenMatch]->Draw("same");
  topY_  [kKinFit  ]->Draw("same");
  //topY_  [kGen       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for topPhi_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);
  
  // draw canvas
  canv2->cd(0);
  //canv0->SetLogy(1);
  axesStyle(*topPhi_  [kGen], "#phi(Top Quark)", "candidates");
  topPhi_  [kGen     ]->SetMinimum(0.);
  topPhi_  [kGen     ]->SetMaximum( 2.5* topPhi_[kGen]->GetMaximum() );
  topPhi_  [kGen     ]->Draw();
  topPhi_  [kGenMatch]->Draw("same");
  topPhi_  [kKinFit  ]->Draw("same");
  //topPhi_  [kGen       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for ttbarPt_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);
  
  // draw canvas
  canv3->cd(0);
  //canv0->SetLogy(1);
  axesStyle(*ttbarPt_  [kGen], "pt(Top-Antitop) [GeV]", "candidates");
  ttbarPt_  [kGen     ]->SetMinimum(0.);
  ttbarPt_  [kGen     ]->SetMaximum( 1.7* ttbarPt_[kGen]->GetMaximum() );
  ttbarPt_  [kGen     ]->Draw();
  ttbarPt_  [kGenMatch]->Draw("same");
  ttbarPt_  [kKinFit  ]->Draw("same");
  //ttbarPt_  [kGen       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for ttbarY_
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(*canv4);
  
  // draw canvas
  canv4->cd(0);
  //canv0->SetLogy(1);
  axesStyle(*ttbarY_  [kGen], "Rapidity(Top-Antitop)", "candidates");
  ttbarY_  [kGen     ]->SetMinimum(0.);
  ttbarY_  [kGen     ]->SetMaximum( 2.5* ttbarY_[kGen]->GetMaximum() );
  ttbarY_  [kGen     ]->Draw();
  ttbarY_  [kGenMatch]->Draw("same");
  ttbarY_  [kKinFit  ]->Draw("same");
  //ttbarY_  [kGen       ]->Draw("esame");
  leg0->Draw("same");

  // ---
  //    do the printing for ttbarMass_
  // ---
  TCanvas* canv5 = new TCanvas("canv5", "canv5", 600, 600); canvasStyle(*canv5);
  
  // draw canvas
  canv5->cd(0);
  //canv0->SetLogy(1);
  axesStyle(*ttbarMass_  [kGen], "Mass(Top-Antitop) [GeV]", "candidates");
  ttbarMass_  [kGen     ]->SetMinimum(0.);
  ttbarMass_  [kGen     ]->SetMaximum( 1.7* ttbarMass_[kGen]->GetMaximum() );
  ttbarMass_  [kGen     ]->Draw();
  ttbarMass_  [kGenMatch]->Draw("same");
  ttbarMass_  [kKinFit  ]->Draw("same");
  //ttbarMass_  [kGen       ]->Draw("esame");
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
  style==kGen ? hist.SetLineWidth(6) : hist.SetLineWidth(3);

  hist.SetStats(kFALSE);
  hist.SetLineColor  (color[style]);
  hist.SetFillColor  (color[style]);
  hist.SetMarkerColor(color[style]);
  hist.SetFillStyle  (fill [style]);

  if(style==kGen){
    hist.SetMarkerStyle(marker[style]);
    hist.SetMarkerSize(1.4);
  }

  //special treatment for the xsec histograms
  for(int bin=1; bin<=hist.GetNbinsX(); ++bin){
    hist.SetBinContent(bin, hist.GetBinContent(bin)/hist.GetXaxis()->GetBinWidth(bin));
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
