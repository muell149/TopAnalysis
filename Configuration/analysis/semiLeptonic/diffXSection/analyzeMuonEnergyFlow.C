#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>


///   ---  ///
// This macro shows MuonCutflow Variables like the averaged number of Trackerhits,
// summed pt in tracker, number of activated hcall-cells, number of activated 
// ecal-cells and edeposit in calorimeter as a function of the distance to the 
// reconstructed muon (differential)
///   ---  ///

enum styles {kAll, kSignal, kBackground, kQCD, kWmunu, kZmumu, kBoson};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);


void analyzeMuonEnergyFlow(TString whichMuons = "tight") // choose between "unselected", "combined", "trigger", "track", "good", "golden", "tight" 
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
  files_.push_back(new TFile("analyzeSemiLeptonicSelection_all.root"  ) );
  files_.push_back(new TFile("analyzeSemiLeptonicSelection_sig.root"  ) );
  files_.push_back(new TFile("analyzeSemiLeptonicSelection_bkg.root"  ) );
  files_.push_back(new TFile("analyzeSemiLeptonicSelection_QCD.root"  ) );
  files_.push_back(new TFile("analyzeSemiLeptonicSelection_Wmunu.root") );
  files_.push_back(new TFile("analyzeSemiLeptonicSelection_Zmumu.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> norm_, trkDRN_, trkDR_, eclDRN_, hclDRN_, calDR_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    norm_  .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonQuality/norm_"   ) );
    trkDRN_.push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonQuality/trkDRN_" ) );
    trkDR_ .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonQuality/trkDR_"  ) );
    eclDRN_.push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonQuality/eclDRN_" ) );
    hclDRN_.push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonQuality/hclDRN_" ) );
    calDR_ .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonQuality/calDR_"  ) );
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

// ---
// adding Vector Bosons
// ---
  trkDRN_.push_back( (TH1F*)trkDRN_[kWmunu]->Clone());
  trkDRN_[kBoson]->Add(trkDRN_[kZmumu]);

  trkDR_.push_back( (TH1F*)trkDR_[kWmunu]->Clone());
  trkDR_[kBoson]->Add(trkDR_[kZmumu]);

  eclDRN_.push_back( (TH1F*)eclDRN_[kWmunu]->Clone());
  eclDRN_[kBoson]->Add(eclDRN_[kZmumu]);

  hclDRN_.push_back( (TH1F*)hclDRN_[kWmunu]->Clone());
  hclDRN_[kBoson]->Add(hclDRN_[kZmumu]);

  calDR_.push_back( (TH1F*)calDR_[kWmunu]->Clone());
  calDR_[kBoson]->Add(calDR_[kZmumu]);

// ---
// setting histogramm style
// ---
  // trkDRN_
  //  histogramStyle(*trkDRN_[kAll       ], kAll       );
  histogramStyle(*trkDRN_[kSignal    ], kSignal    );
  histogramStyle(*trkDRN_[kBackground], kBackground);
  histogramStyle(*trkDRN_[kQCD       ], kQCD       );
  histogramStyle(*trkDRN_[kBoson     ], kBoson     );

  // trkDR_
  //  histogramStyle(*trkDR_ [kAll       ], kAll       );
  histogramStyle(*trkDR_ [kSignal    ], kSignal    );
  histogramStyle(*trkDR_ [kBackground], kBackground);
  histogramStyle(*trkDR_ [kQCD       ], kQCD       );
  histogramStyle(*trkDR_ [kBoson     ], kBoson     );

  // eclDRN_
  //  histogramStyle(*eclDRN_[kAll       ], kAll       );
  histogramStyle(*eclDRN_[kSignal    ], kSignal    );
  histogramStyle(*eclDRN_[kBackground], kBackground);
  histogramStyle(*eclDRN_[kQCD       ], kQCD       );
  histogramStyle(*eclDRN_[kBoson     ], kBoson     );

  // hclDRN_
  //  histogramStyle(*hclDRN_[kAll       ], kAll       );
  histogramStyle(*hclDRN_[kSignal    ], kSignal    );
  histogramStyle(*hclDRN_[kBackground], kBackground);
  histogramStyle(*hclDRN_[kQCD       ], kQCD       );
  histogramStyle(*hclDRN_[kBoson     ], kBoson     );

  // calDR_
  //  histogramStyle(*calDR_ [kAll       ], kAll       );
  histogramStyle(*calDR_ [kSignal    ], kSignal    );
  histogramStyle(*calDR_ [kBackground], kBackground);
  histogramStyle(*calDR_ [kQCD       ], kQCD       );
  histogramStyle(*calDR_ [kBoson     ], kBoson     );


  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  //  leg0->AddEntry( trkDRN_[kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( trkDRN_[kSignal    ] , "semi-lep. ( #mu )"   , "PL" );
  leg0->AddEntry( trkDRN_[kBackground] , "other ttbar decays"  , "PL" );
  leg0->AddEntry( trkDRN_[kQCD       ] , "QCD"                 , "PL" );
  leg0->AddEntry( trkDRN_[kBoson    ] , "W#mu#nu + Z#mu#mu"   , "PL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  //  leg1->AddEntry( trkDRN_[kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( trkDRN_[kSignal    ] , "semi-lep. ( #mu )"   , "PL" );
  leg1->AddEntry( trkDRN_[kBackground] , "other ttbar decays"  , "PL" );
  leg1->AddEntry( trkDRN_[kQCD       ] , "QCD"                 , "PL" );
  leg1->AddEntry( trkDRN_[kBoson     ] , "W#mu#nu + Z#mu#mu"   , "PL" );

  // create an info legend containig the used mu-cut
  TLegend *leg2 = new TLegend(0.228, 0.912, 0.7818, 0.997);
  leg2->SetFillStyle (0);
  leg2->SetBorderSize(0);
  leg2->SetHeader(whichMuons+" #mu");


  // ---
  //    do the printing for trkDRN_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  
  // draw canvas
  canv0->cd(0);
  canv0->SetTitle("<number of tracks> as a function of #deltaR (differential)"+whichMuons+"# mu");
  //canv0->SetLogy(1);
  axesStyle(*trkDRN_[kSignal], "#Delta R (#mu, track)", "#left(#frac{1}{N_{#mu}}#right) #Sigma N_{trk}");
  trkDRN_[kSignal       ]->SetMinimum(0.);
  trkDRN_[kSignal       ]->SetMaximum( 1.4 );
  //  trkDRN_[kAll       ]->Draw();
  trkDRN_[kSignal    ]->Draw("");
  trkDRN_[kBackground]->Draw("same");
  trkDRN_[kQCD       ]->Draw("same");
  trkDRN_[kBoson     ]->Draw("same");
  //trkDRN_[kAll       ]->Draw("esame");
  leg0->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for trkDR_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetTitle("<summed pt of tracks> as a function of #deltaR (differential)"+whichMuons+"# mu");
  //canv1->SetLogy(1);
  axesStyle(*trkDR_ [kSignal], "#Delta R (#mu, track)", "#left(#frac{1}{N_{#mu}}#right) #Sigma pt_{trk} [GeV]");
  trkDR_ [kSignal       ]->SetMinimum(0.);
  trkDR_ [kSignal       ]->SetMaximum( 1.7 );
  //  trkDR_ [kAll       ]->Draw();
  trkDR_ [kSignal    ]->Draw("");
  trkDR_ [kBackground]->Draw("same");
  trkDR_ [kQCD       ]->Draw("same");
  trkDR_ [kBoson     ]->Draw("same");
  //trkDR_ [kAll       ]->Draw("same");
  leg0->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for eclDRN_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetTitle("<number of ecal crystals above noise threshold> as a function of #deltaR (differential)"+whichMuons+"# mu");
  //canv2->SetLogy(1);
  axesStyle(*eclDRN_ [kSignal], "#Delta R (#mu, deposit)", "#left(#frac{1}{N_{#mu}}#right) #Sigma N_{ecal}");
  eclDRN_ [kSignal       ]->SetMinimum(0.);
  eclDRN_ [kSignal       ]->SetMaximum( 1.8 );
  //  eclDRN_ [kAll       ]->Draw();
  eclDRN_ [kSignal    ]->Draw("");
  eclDRN_ [kBackground]->Draw("same");
  eclDRN_ [kQCD       ]->Draw("same");
  eclDRN_ [kBoson     ]->Draw("same");
  //eclDRN_ [kAll       ]->Draw("same");
  leg0->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for hclDRN_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  canv3->SetTitle("<number of hcal towers above noise threshold> as a function of #deltaR (differential)"+whichMuons+"# mu");
  //canv3->SetLogy(1);
  axesStyle(*hclDRN_[kSignal], "#Delta R (#mu, deposit)", "#left(#frac{1}{N_{#mu}}#right)  #Sigma N_{hcal}");
  hclDRN_[kAll       ]->SetMinimum(0.);
  hclDRN_[kSignal       ]->SetMaximum( 0.8);
  //  hclDRN_[kAll       ]->Draw();
  hclDRN_[kSignal    ]->Draw("");
  hclDRN_[kBackground]->Draw("same");
  hclDRN_[kQCD       ]->Draw("same");
  hclDRN_[kBoson     ]->Draw("same");
  //hclDRN_[kAll       ]->Draw("same");
  leg0->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for calDR_
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(*canv4);

  // draw canvas
  canv4->cd(0);
  canv4->SetTitle("<summed crystal and tower energies above noise threshold> as a function of deltaR (differential)"+whichMuons+"# mu");
  //canv4->SetLogy(1);
  axesStyle(*calDR_[kSignal], "#Delta R (#mu, deposit)", "#left(#frac{1}{N_{#mu}}#right) #Sigma pt_{calo}");
  //calDR_[kAll       ]->SetMinimum( 1.);
  calDR_[kSignal       ]->SetMaximum( 4.5 );
  //  calDR_[kAll       ]->Draw();
  calDR_[kSignal    ]->Draw("");
  calDR_[kBackground]->Draw("same");
  calDR_[kQCD       ]->Draw("same");
  calDR_[kBoson     ]->Draw("same");
  //calDR_[kAll       ]->Draw("same");
  leg0->Draw("same");
  leg2->Draw("same");

  //---
  // saving
  //---

  //  pictures

//   canv0->Print("./analyzeMuonCutflow/trkDRN"+whichMuons+"Muons.png");
//   canv1->Print("./analyzeMuonCutflow/trkDR"+whichMuons+"Muons.png" );
//   canv2->Print("./analyzeMuonCutflow/eclDRN"+whichMuons+"Muons.png");
//   canv3->Print("./analyzeMuonCutflow/hclDR"+whichMuons+"Muons.png" );
//   canv4->Print("./analyzeMuonCutflow/calDR"+whichMuons+"Muons.png" );
  
  //  psfile

  canv0->Print("./analyzeMuonCutflow/EnergyFlow"+whichMuons+"Muons.ps(");
  canv1->Print("./analyzeMuonCutflow/EnergyFlow"+whichMuons+"Muons.ps" );
  canv2->Print("./analyzeMuonCutflow/EnergyFlow"+whichMuons+"Muons.ps" );
  canv3->Print("./analyzeMuonCutflow/EnergyFlow"+whichMuons+"Muons.ps" );
  canv4->Print("./analyzeMuonCutflow/EnergyFlow"+whichMuons+"Muons.ps)");

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
  color.push_back( 6     ); 
  color.push_back( kRed  ); 
  color.push_back( kBlue );
  color.push_back( kGreen);
  color.push_back( 5     );
  color.push_back( 7     );
  color.push_back( kBlack);

  // pre-defined fill style
  std::vector<int> fill;
  fill.push_back(   1); 
  fill.push_back(3004); 
  fill.push_back(   1);
  fill.push_back(   1);
  fill.push_back(   1);
  fill.push_back(   1);
  fill.push_back(   1);

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
