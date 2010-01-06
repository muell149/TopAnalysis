#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>

  // ---
  //  introduction
  // ---
  //  this makro analyzes the emf and number of constituents of jets for ttbar 
  //  and different BG-sample in different steps of the jet-cuts
  //  do not use n60 and n90 !!!
  // ---

enum styles {kAll, kSignal, kBackground, kQCD, kWmunu, kZmumu, kBoson};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);


void analyzeJetQuality(TString whichJets = "reliable")
  // choose whichJets = unselected, central, reliable, tight for different steps in jetcuts
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
  files_.push_back(new TFile("./analyzeSemiLeptonicSelection_all.root"  ) );
  files_.push_back(new TFile("./analyzeSemiLeptonicSelection_sig.root"  ) );
  files_.push_back(new TFile("./analyzeSemiLeptonicSelection_bkg.root"  ) );
  files_.push_back(new TFile("./analyzeSemiLeptonicSelection_QCD.root"  ) );
  files_.push_back(new TFile("./analyzeSemiLeptonicSelection_Wmunu.root") );
  files_.push_back(new TFile("./analyzeSemiLeptonicSelection_Zmumu.root") );

  // histogram scaling because of lumiweighting
  std::vector<double> lumiweight;


  // add scaling factors here!!!
  lumiweight.push_back(1.0);
  lumiweight.push_back(1.0);
  lumiweight.push_back(1.0);
  lumiweight.push_back(1.0);
  lumiweight.push_back(1.0);
  lumiweight.push_back(1.0);

  // ttbar (all, bg, sg - coming from the same sample)
//    lumiweight.push_back(0.039);
//    lumiweight.push_back(0.039);
//    lumiweight.push_back(0.039 );
//    //  QCD
//    lumiweight.push_back(1.1161);
//    //  Wmunu
//    lumiweight.push_back(0.2212);
//    //  Zmumu
//    lumiweight.push_back(0.0458);


  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> emf_, n_, n90_, n60_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    emf_.push_back( (TH1F*)files_[idx]->Get(whichJets+"LeadingJetQuality/emf"  ) );
    n_.push_back  ( (TH1F*)files_[idx]->Get(whichJets+"LeadingJetQuality/n_"   ) );
    n90_.push_back( (TH1F*)files_[idx]->Get(whichJets+"LeadingJetQuality/n90_" ) );
    n60_.push_back( (TH1F*)files_[idx]->Get(whichJets+"LeadingJetQuality/n60_" ) );
  }

  // ---
  //    close input files
  // ---
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    //files_[idx]->Close();
  }
  

  // Normalization and adding Vektor Bosons

  n_[kWmunu]->Scale(lumiweight[kWmunu]);
  n_[kZmumu]->Scale(lumiweight[kZmumu]);
  n_.push_back( (TH1F*)n_[kWmunu]->Clone());
  n_[kBoson]->Add(n_[kZmumu]);
  n_[kQCD]->Scale(lumiweight[kQCD]);  
  n_[kAll]->Scale(lumiweight[kAll]);  
  n_[kSignal]->Scale(lumiweight[kSignal]); 
  n_[kBackground]->Scale(lumiweight[kBackground]); 

  emf_[kWmunu]->Scale(lumiweight[kWmunu]);
  emf_[kZmumu]->Scale(lumiweight[kZmumu]);
  emf_.push_back( (TH1F*)emf_[kWmunu]->Clone());
  emf_[kBoson]->Add(emf_[kZmumu]);
  emf_[kQCD]->Scale(lumiweight[kQCD]);  
  emf_[kAll]->Scale(lumiweight[kAll]);  
  emf_[kSignal]->Scale(lumiweight[kSignal]); 
  emf_[kBackground]->Scale(lumiweight[kBackground]); 

  n60_[kWmunu]->Scale(lumiweight[kWmunu]);
  n60_[kZmumu]->Scale(lumiweight[kZmumu]);
  n60_.push_back( (TH1F*)n60_[kWmunu]->Clone());
  n60_[kBoson]->Add(n60_[kZmumu]);
  n60_[kQCD]->Scale(lumiweight[kQCD]);  
  n60_[kAll]->Scale(lumiweight[kAll]);  
  n60_[kSignal]->Scale(lumiweight[kSignal]); 
  n60_[kBackground]->Scale(lumiweight[kBackground]);

  n90_[kWmunu]->Scale(lumiweight[kWmunu]);
  n90_[kZmumu]->Scale(lumiweight[kZmumu]);
  n90_.push_back( (TH1F*)n90_[kWmunu]->Clone());
  n90_[kBoson]->Add(n90_[kZmumu]);
  n90_[kQCD]->Scale(lumiweight[kQCD]);  
  n90_[kAll]->Scale(lumiweight[kAll]);  
  n90_[kSignal]->Scale(lumiweight[kSignal]); 
  n90_[kBackground]->Scale(lumiweight[kBackground]);



  // ---
  //    configure histograms
  // ---

  // emf_
  //  histogramStyle(*emf_  [kAll       ], kAll       );
  histogramStyle(*emf_  [kSignal    ], kSignal    );
  histogramStyle(*emf_  [kBackground], kBackground);
  histogramStyle(*emf_  [kQCD]       , kQCD       );
  //  histogramStyle(*emf_  [kWmunu]     , kWmunu     );
  //  histogramStyle(*emf_  [kZmumu]     , kZmumu     );
  histogramStyle(*emf_  [kBoson]     ,   kBoson   );

  // n_
  //  histogramStyle(*n_ [kAll       ], kAll       );
  histogramStyle(*n_ [kSignal    ], kSignal    );
  histogramStyle(*n_ [kBackground], kBackground);
  histogramStyle(*n_  [kQCD]       , kQCD       );
  //  histogramStyle(*n_  [kWmunu]     , kWmunu     );
  //  histogramStyle(*n_  [kZmumu]     , kZmumu     );
  histogramStyle(*n_  [kBoson]     ,   kBoson   );

  // n90_
  //  histogramStyle(*n90_ [kAll       ], kAll       );
  histogramStyle(*n90_ [kSignal    ], kSignal    );
  histogramStyle(*n90_ [kBackground], kBackground);
  histogramStyle(*n90_  [kQCD]       , kQCD       );
  //  histogramStyle(*n90_  [kWmunu]     , kWmunu     );
  //  histogramStyle(*n90_  [kZmumu]     , kZmumu     );
  histogramStyle(*n90_  [kBoson]     ,   kBoson   );

  // n60_
  // histogramStyle(*n60_ [kAll       ], kAll       );
  histogramStyle(*n60_ [kSignal    ], kSignal    );
  histogramStyle(*n60_ [kBackground], kBackground);
  histogramStyle(*n60_ [kQCD]       , kQCD       );
  //  histogramStyle(*n60_  [kWmunu]     , kWmunu     );
  //  histogramStyle(*n60_  [kZmumu]     , kZmumu     );
  histogramStyle(*n60_  [kBoson]     ,   kBoson   );

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  //  leg0->AddEntry( emf_[kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( emf_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
  leg0->AddEntry( emf_[kBackground] , "other decays"      , "PL" );
  leg0->AddEntry( emf_  [kQCD       ] , "QCD"               , "PL" );
  //  leg0->AddEntry( emf_  [kWmunu     ] , "Wmunu"             , "PL" );
  //  leg0->AddEntry( emf_  [kZmumu     ] , "Zmumu"             , "PL" );
  leg0->AddEntry( emf_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  //  leg1->AddEntry( emf_[kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( emf_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
  leg1->AddEntry( emf_[kBackground] , "other decays"      , "PL" );
  leg1->AddEntry( emf_  [kQCD       ] , "QCD"               , "PL" );
  //  leg1->AddEntry( emf_  [kWmunu     ] , "Wmunu"             , "PL" );
  //  leg1->AddEntry( emf_  [kZmumu     ] , "Zmumu"             , "PL" );
  leg1->AddEntry( emf_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );

  // create a legend indicating the used jetcuts
  TLegend *leg2 = new TLegend(0.29, 0.92, 0.81, 0.99);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetHeader(whichJets+" Jets");

  // ---
  //    do the printing for emf_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  
  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  axesStyle(*emf_[kSignal], "Electromagnetic Fraction", "events");
  emf_[kSignal       ]->SetMinimum(1.);
  emf_[kSignal       ]->SetMaximum( 1700* emf_[kQCD]->GetMaximum() );
  //  emf_[kAll       ]->Draw();
  emf_[kSignal    ]->Draw();
  emf_[kBackground]->Draw("same");
  emf_[kQCD       ]->Draw("same");
  emf_[kBoson     ]->Draw("same");
  //emf_  [kAll       ]->Draw("esame");
  leg0->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for n_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetLogy(1);
  axesStyle(*n_[kSignal], "Number of Constituents", "events");
  n_[kSignal       ]->SetMaximum( 1300* n_[kQCD]->GetMaximum() );
  //  n_[kAll       ]->Draw();
  n_[kSignal    ]->Draw();
  n_[kBackground]->Draw("same");
  n_[kQCD       ]->Draw("same");
  n_[kBoson     ]->Draw("same");
  //n_ [kAll       ]->Draw("same");
  leg0->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for n90_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetLogy(1);
  axesStyle(*n90_[kSignal], "Number of Constituents n90", "events");
  n90_[kSignal       ]->SetMaximum( 1.3* n90_[kQCD]->GetMaximum() );
  //  n90_[kAll       ]->Draw();
  n90_[kSignal    ]->Draw();
  n90_[kBackground]->Draw("same");
  n90_[kQCD       ]->Draw("same");
  n90_[kBoson     ]->Draw("same");
  //n90_ [kAll       ]->Draw("same");
  leg0->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for n60_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  canv3->SetLogy(1);
  axesStyle(*n60_[kSignal], "Number of Constituents n60", "events");
  n60_[kSignal       ]->SetMaximum( 1.3* n60_[kQCD]->GetMaximum() );
  //  n60_[kAll       ]->Draw();
  n60_[kSignal    ]->Draw();
  n60_[kBackground]->Draw("same");
  n60_[kQCD       ]->Draw("same");
  n60_[kBoson     ]->Draw("same");
  //n60_ [kAll       ]->Draw("same");
  leg0->Draw("same");
  leg2->Draw("same");

// saving 


  // 1.as picture 
  canv0->Print("./analyzeJetQuantities/"+whichJets+"JetEmf.png"            );
  canv1->Print("./analyzeJetQuantities/"+whichJets+"JetNumConstituents.png");
  //  canv2->Print("./analyzeJetQuantities/"+whichJets+"JetN90.png"            );
  //  canv3->Print("./analyzeJetQuantities/"+whichJets+"JetN60.png"            );
  
  // 2.as ps-file
  canv0->Print("./analyzeJetQuantities/"+whichJets+"JetQualities.ps(");
  canv1->Print("./analyzeJetQuantities/"+whichJets+"JetQualities.ps)" );
  //  canv2->Print("./analyzeJetQuantities/"+whichJets+"JetQualities.ps" );
  //  canv3->Print("./analyzeJetQuantities/"+whichJets+"JetQualities.ps)");
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
  color.push_back( kGreen); 
  color.push_back( kBlack); 
  color.push_back(  28   );
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
  hist.GetYaxis()->CenterTitle   ( true);
}
