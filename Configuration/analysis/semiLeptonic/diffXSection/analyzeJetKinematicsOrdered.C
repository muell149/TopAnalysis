#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>

enum styles {kAll, kSignal, kBackground, kQCD, kWmunu, kZmumu, kBoson};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);


void analyzeJetKinematicsOrdered(bool plotEta=false, TString whichJets = "tight")
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

  // for current 10 TeV Pythia sample: ttbar (all, bg, sg - coming from the same sample)
//    lumiweight.push_back(0.039);
//    lumiweight.push_back(0.039);
//    lumiweight.push_back(0.039);
//    //  QCD
//    lumiweight.push_back(1.1161);
//    //  Wmunu
//    lumiweight.push_back(0.2212);
//    //  Zmumu
//    lumiweight.push_back(0.0458);

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> lead0_, lead1_, lead2_, lead3_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    if( !plotEta ){
      lead0_.push_back( (TH1F*)files_[idx]->Get(whichJets+"Lead_0_JetKinematicsAfter/pt") );
      lead1_.push_back( (TH1F*)files_[idx]->Get(whichJets+"Lead_1_JetKinematicsAfter/pt") );
      lead2_.push_back( (TH1F*)files_[idx]->Get(whichJets+"Lead_2_JetKinematicsAfter/pt") );
      lead3_.push_back( (TH1F*)files_[idx]->Get(whichJets+"Lead_3_JetKinematicsAfter/pt") );
    }
    else{
      lead0_.push_back( (TH1F*)files_[idx]->Get(whichJets+"Lead_0_JetKinematicsAfter/eta") );
      lead1_.push_back( (TH1F*)files_[idx]->Get(whichJets+"Lead_1_JetKinematicsAfter/eta") );
      lead2_.push_back( (TH1F*)files_[idx]->Get(whichJets+"Lead_2_JetKinematicsAfter/eta") );
      lead3_.push_back( (TH1F*)files_[idx]->Get(whichJets+"Lead_3_JetKinematicsAfter/eta") );
    }
  }

  // ---
  //    close input files
  // ---
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    //files_[idx]->Close();
  }
  
  // Normalization and adding Vektor Bosons

  lead0_[kWmunu]->Scale(lumiweight[kWmunu]);
  lead0_[kZmumu]->Scale(lumiweight[kZmumu]);
  lead0_.push_back( (TH1F*)lead0_[kWmunu]->Clone());
  lead0_[kBoson]->Add(lead0_[kZmumu]);
  lead0_[kQCD]->Scale(lumiweight[kQCD]);  
  lead0_[kAll]->Scale(lumiweight[kAll]);  
  lead0_[kSignal]->Scale(lumiweight[kSignal]); 
  lead0_[kBackground]->Scale(lumiweight[kBackground]); 

  lead1_[kWmunu]->Scale(lumiweight[kWmunu]);
  lead1_[kZmumu]->Scale(lumiweight[kZmumu]);
  lead1_.push_back( (TH1F*)lead1_[kWmunu]->Clone());
  lead1_[kBoson]->Add(lead1_[kZmumu]);
  lead1_[kQCD]->Scale(lumiweight[kQCD]);  
  lead1_[kAll]->Scale(lumiweight[kAll]);  
  lead1_[kSignal]->Scale(lumiweight[kSignal]); 
  lead1_[kBackground]->Scale(lumiweight[kBackground]); 

  lead2_[kWmunu]->Scale(lumiweight[kWmunu]);
  lead2_[kZmumu]->Scale(lumiweight[kZmumu]);
  lead2_.push_back( (TH1F*)lead2_[kWmunu]->Clone());
  lead2_[kBoson]->Add(lead2_[kZmumu]);
  lead2_[kQCD]->Scale(lumiweight[kQCD]);  
  lead2_[kAll]->Scale(lumiweight[kAll]);  
  lead2_[kSignal]->Scale(lumiweight[kSignal]); 
  lead2_[kBackground]->Scale(lumiweight[kBackground]);

  lead3_[kWmunu]->Scale(lumiweight[kWmunu]);
  lead3_[kZmumu]->Scale(lumiweight[kZmumu]);
  lead3_.push_back( (TH1F*)lead3_[kWmunu]->Clone());
  lead3_[kBoson]->Add(lead3_[kZmumu]);
  lead3_[kQCD]->Scale(lumiweight[kQCD]);  
  lead3_[kAll]->Scale(lumiweight[kAll]);  
  lead3_[kSignal]->Scale(lumiweight[kSignal]); 
  lead3_[kBackground]->Scale(lumiweight[kBackground]);


  // ---
  //    configure histograms
  // ---

  // lead0_
  //  histogramStyle(*lead0_[kAll       ], kAll       );
  histogramStyle(*lead0_[kSignal    ], kSignal    );
  histogramStyle(*lead0_[kBackground], kBackground);
  histogramStyle(*lead0_  [kQCD]       , kQCD     );
  //  histogramStyle(*lead0_  [kWmunu]     , kWmunu     );
  //  histogramStyle(*lead0_  [kZmumu]     , kZmumu     );
  histogramStyle(*lead0_  [kBoson]     ,   kBoson );

  // lead1_
  //  histogramStyle(*lead1_[kAll       ], kAll       );
  histogramStyle(*lead1_[kSignal    ], kSignal    );
  histogramStyle(*lead1_[kBackground], kBackground);
  histogramStyle(*lead1_  [kQCD]       , kQCD     );
  //  histogramStyle(*lead1_  [kWmunu]     , kWmunu     );
  //  histogramStyle(*lead1_  [kZmumu]     , kZmumu     );
  histogramStyle(*lead1_  [kBoson]     ,   kBoson );

  // lead2_
  //  histogramStyle(*lead2_[kAll       ], kAll       );
  histogramStyle(*lead2_[kSignal    ], kSignal    );
  histogramStyle(*lead2_[kBackground], kBackground);
  histogramStyle(*lead2_  [kQCD]       , kQCD     );
  //  histogramStyle(*lead2_  [kWmunu]     , kWmunu     );
  //  histogramStyle(*lead2_  [kZmumu]     , kZmumu     );
  histogramStyle(*lead2_  [kBoson]     ,   kBoson );

  // lead3_
  //  histogramStyle(*lead3_[kAll       ], kAll       );
  histogramStyle(*lead3_[kSignal    ], kSignal    );
  histogramStyle(*lead3_[kBackground], kBackground);
  histogramStyle(*lead3_  [kQCD]       , kQCD     );
  //  histogramStyle(*lead3_  [kWmunu]     , kWmunu     );
  //  histogramStyle(*lead3_  [kZmumu]     , kZmumu     );
  histogramStyle(*lead3_  [kBoson]     ,   kBoson );

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.53, 0.63, 0.99, 0.94);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  //  leg0->AddEntry( lead0_[kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( lead0_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
  leg0->AddEntry( lead0_[kBackground] , "other decays"      , "PL" );
  leg0->AddEntry( lead0_  [kQCD       ] , "QCD"               , "PL" );
  //  leg0->AddEntry( lead0_  [kWmunu     ] , "Wmunu"             , "PL" );
  //  leg0->AddEntry( lead0_  [kZmumu     ] , "Zmumu"             , "PL" );
  leg0->AddEntry( lead0_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  //  leg1->AddEntry( lead0_[kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( lead0_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
  leg1->AddEntry( lead0_[kBackground] , "other decays"      , "PL" );
  leg1->AddEntry( lead0_  [kQCD     ] , "QCD"               , "PL" );
  //  leg1->AddEntry( lead0_  [kWmunu     ] , "Wmunu"             , "PL" );
  //  leg1->AddEntry( lead0_  [kZmumu     ] , "Zmumu"             , "PL" );
  leg1->AddEntry( lead0_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );

  // create a legend indicating the used jetcuts
  TLegend *leg2 = new TLegend(0.29, 0.92, 0.81, 0.99);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetHeader(whichJets+" Jets");

  // prepare axes labels
  if( !plotEta ){
    axesStyle(*lead0_[kSignal], "pt( 1. Leading Jet ) [GeV]", "events" );
    axesStyle(*lead1_[kSignal], "pt( 2. Leading Jet ) [GeV]", "events" );
    axesStyle(*lead2_[kSignal], "pt( 3. Leading Jet ) [GeV]", "events" );
    axesStyle(*lead3_[kSignal], "pt( 4. Leading Jet ) [GeV]", "events");
  }
  else{
    axesStyle(*lead0_[kSignal], "#eta( 1. Leading Jet )", "events");
    axesStyle(*lead1_[kSignal], "#eta( 2. Leading Jet )", "events");
    axesStyle(*lead2_[kSignal], "#eta( 3. Leading Jet )", "events");
    axesStyle(*lead3_[kSignal], "#eta( 4. Leading Jet )", "events");
  }

  // ---
  //    do the printing for lead0_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  lead0_[kSignal    ]->SetMinimum(1.);
  lead0_[kSignal    ]->SetMaximum(175 * lead0_[kQCD]->GetMaximum() );
  //  lead0_[kAll       ]->Draw();
  lead0_[kSignal    ]->Draw();
  lead0_[kBackground]->Draw("same");
  lead0_[kQCD       ]->Draw("same");
  lead0_[kBoson     ]->Draw("same");
  //lead0_[kAll       ]->Draw("esame");
  leg0->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for lead1_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetLogy(1);
  lead1_[kSignal    ]->SetMinimum(1.);
  lead1_[kSignal    ]->SetMaximum( 175 * lead1_[kQCD]->GetMaximum() );
  //  lead1_[kAll       ]->Draw();
  lead1_[kSignal    ]->Draw();
  lead1_[kBackground]->Draw("same");
  lead1_[kQCD       ]->Draw("same");
  lead1_[kBoson     ]->Draw("same");
  //lead1_[kAll       ]->Draw("same");
  leg0->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for lead2_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetLogy(1);
  lead2_[kSignal    ]->SetMinimum( 1.);
  lead2_[kSignal    ]->SetMaximum( 175 * lead2_[kQCD]->GetMaximum() );
  //  lead2_[kAll       ]->Draw();
  lead2_[kSignal    ]->Draw();
  lead2_[kBackground]->Draw("same");
  lead2_[kQCD       ]->Draw("same");
  lead2_[kBoson     ]->Draw("same");
  //lead2_[kAll       ]->Draw("same");
  leg0->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for lead3_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  canv3->SetLogy(1);
  lead3_[kSignal    ]->SetMinimum( 1.);
  lead3_[kSignal    ]->SetMaximum( 175 * lead3_[kQCD]->GetMaximum() );
  // lead3_[kAll       ]->Draw();
  lead3_[kSignal    ]->Draw();
  lead3_[kBackground]->Draw("same");
  lead3_[kQCD       ]->Draw("same");
  lead3_[kBoson     ]->Draw("same");
  //lead3_[kAll       ]->Draw("same");
  leg0->Draw("same");
  leg2->Draw("same");



// saving 


  if(plotEta==false){
    // 1.as picture 
    canv0->Print("./analyzeJetQuantities/PtLeading"+whichJets+"tJetAfter.png"   );
    canv1->Print("./analyzeJetQuantities/Pt2ndLeading"+whichJets+"JetAfter.png");
    canv2->Print("./analyzeJetQuantities/Pt3rdLeading"+whichJets+"JetAfter.png");
    canv3->Print("./analyzeJetQuantities/Pt4thLeading"+whichJets+"JetAfter.png");

    // 2.as ps-file
    canv0->Print("./analyzeJetQuantities/PtOfThe4Leading"+whichJets+"JetsAfter.ps(");
    canv1->Print("./analyzeJetQuantities/PtOfThe4Leading"+whichJets+"JetsAfter.ps" );
    canv2->Print("./analyzeJetQuantities/PtOfThe4Leading"+whichJets+"JetsAfter.ps" );
    canv3->Print("./analyzeJetQuantities/PtOfThe4Leading"+whichJets+"JetsAfter.ps)");
  }

  if(plotEta==true){
    // 1.as picture 
    canv0->Print("./analyzeJetQuantities/EtaLeading"+whichJets+"JetAfter.png"   );
    canv1->Print("./analyzeJetQuantities/Eta2ndLeading"+whichJets+"JetAfter.png");
    canv2->Print("./analyzeJetQuantities/Eta3rdLeading"+whichJets+"JetAfter.png");
    canv3->Print("./analyzeJetQuantities/Eta4thLeading"+whichJets+"JetAfter.png");

    // 2.as ps-file
    canv0->Print("./analyzeJetQuantities/EtaOfThe4Leading"+whichJets+"JetsAfter.ps(");
    canv1->Print("./analyzeJetQuantities/EtaOfThe4Leading"+whichJets+"JetsAfter.ps" );
    canv2->Print("./analyzeJetQuantities/EtaOfThe4Leading"+whichJets+"JetsAfter.ps" );
    canv3->Print("./analyzeJetQuantities/EtaOfThe4Leading"+whichJets+"JetsAfter.ps)");
  }
    cout << "you have the option to choose plotEta=false or plotEta=true" << endl;
    cout << "you can choose the between jet-collection unselected, central, reliable, tight" << endl;
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
