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

void analyzeMuonKinematics(TString whichMuons = "unselected")  //  "tight" // "loose" // "track" // "good" // "combined" // "unselected"
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
  //  lumiweight.push_back(0.0156);
  //  lumiweight.push_back(0.0156);
  //  lumiweight.push_back(0.0156);
  // QCD
  //  lumiweight.push_back(1.1161);
  // Wmunu
  //  lumiweight.push_back(0.2212);
  // Zmumu
  //  lumiweight.push_back(0.0458);


  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> n_, pt_, eta_, phi_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    n_  .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonKinematics/n"    )->Clone() );
    pt_ .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonKinematics/pt"   )->Clone() );
    eta_.push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonKinematics/eta"  )->Clone() );
    phi_.push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonKinematics/phi"  )->Clone() );
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

  pt_[kWmunu]->Scale(lumiweight[kWmunu]);
  pt_[kZmumu]->Scale(lumiweight[kZmumu]);
  pt_.push_back( (TH1F*)pt_[kWmunu]->Clone());
  pt_[kBoson]->Add(pt_[kZmumu]);
  pt_[kQCD]->Scale(lumiweight[kQCD]);  
  pt_[kAll]->Scale(lumiweight[kAll]);  
  pt_[kSignal]->Scale(lumiweight[kSignal]); 
  pt_[kBackground]->Scale(lumiweight[kBackground]); 

  eta_[kWmunu]->Scale(lumiweight[kWmunu]);
  eta_[kZmumu]->Scale(lumiweight[kZmumu]);
  eta_.push_back( (TH1F*)eta_[kWmunu]->Clone());
  eta_[kBoson]->Add(eta_[kZmumu]);
  eta_[kQCD]->Scale(lumiweight[kQCD]);  
  eta_[kAll]->Scale(lumiweight[kAll]);  
  eta_[kSignal]->Scale(lumiweight[kSignal]); 
  eta_[kBackground]->Scale(lumiweight[kBackground]);

  phi_[kWmunu]->Scale(lumiweight[kWmunu]);
  phi_[kZmumu]->Scale(lumiweight[kZmumu]);
  phi_.push_back( (TH1F*)phi_[kWmunu]->Clone());
  phi_[kBoson]->Add(eta_[kZmumu]);
  phi_[kQCD]->Scale(lumiweight[kQCD]);  
  phi_[kAll]->Scale(lumiweight[kAll]);  
  phi_[kSignal]->Scale(lumiweight[kSignal]); 
  phi_[kBackground]->Scale(lumiweight[kBackground]);

  // ---
  //    configure histograms
  // ---

  // n_
  //  histogramStyle(*n_  [kAll       ], kAll       );
  histogramStyle(*n_  [kSignal    ], kSignal    );
  histogramStyle(*n_  [kBackground], kBackground);
  histogramStyle(*n_  [kQCD]       , kQCD       );
  //  histogramStyle(*n_  [kWmunu]     , kWmunu     );
  //  histogramStyle(*n_  [kZmumu]     , kZmumu     );
  histogramStyle(*n_  [kBoson]     ,   kBoson   );

  // pt_
  histogramStyle(*pt_ [kAll       ], kAll       );
  histogramStyle(*pt_ [kSignal    ], kSignal    );
  histogramStyle(*pt_ [kBackground], kBackground);
  histogramStyle(*pt_ [kQCD]       , kQCD       );
  histogramStyle(*pt_ [kWmunu]     , kWmunu     );
  histogramStyle(*pt_ [kZmumu]     , kZmumu     );
  //  histogramStyle(*pt_ [kBoson]     ,   kBoson    );

  // eta_
  histogramStyle(*eta_[kAll       ], kAll       );
  histogramStyle(*eta_[kSignal    ], kSignal    );
  histogramStyle(*eta_[kBackground], kBackground);
  histogramStyle(*eta_[kQCD]       , kQCD       );
  //  histogramStyle(*eta_[kWmunu]     , kWmunu     );
  //  histogramStyle(*eta_[kZmumu]     , kZmumu     );
  histogramStyle(*eta_ [kBoson]     ,   kBoson    );

  // phi_
  histogramStyle(*phi_[kAll       ], kAll       );
  histogramStyle(*phi_[kSignal    ], kSignal    );
  histogramStyle(*phi_[kBackground], kBackground);
  histogramStyle(*phi_[kQCD]       , kQCD       );
  histogramStyle(*phi_[kWmunu]     , kWmunu     );
  histogramStyle(*phi_[kZmumu]     , kZmumu     );

   // ---
  //    do the printing for n_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");  
  //  leg0->AddEntry( n_  [kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( n_  [kSignal    ] , "semi-lep. ( #mu )" , "PL" );
  leg0->AddEntry( n_  [kBackground] , "other decays ttbar", "PL" );
  leg0->AddEntry( n_  [kQCD       ] , "QCD"               , "PL" );
  //  leg0->AddEntry( n_  [kWmunu     ] , "Wmunu"             , "FL" );
  //  leg0->AddEntry( n_  [kZmumu     ] , "Zmumu"             , "FL" );
  leg0->AddEntry( n_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.40, 0.75, 1.05, 0.95);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  //  leg1->AddEntry( n_  [kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( n_  [kSignal    ] , "semi-lep. ( #mu )" , "PL" );
  leg1->AddEntry( n_  [kBackground] , "other decays"      , "PL" );
  leg1->AddEntry( n_  [kQCD       ] , "QCD"               , "PL" );
  //  leg1->AddEntry( n_  [kWmunu     ] , "Wmunu"             , "FL" );
  //  leg1->AddEntry( n_  [kZmumu     ] , "Zmumu"             , "FL" );
  leg1->AddEntry( n_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );

  // create an info legend containig the used mu-cut
  TLegend *leg2 = new TLegend(0.15, 1.15, 0.40, 0.80);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetHeader(whichMuons+" #mu");

  TLegend *leg3 = new TLegend(0.25, 1.15, 0.50, 0.80);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  leg3->SetHeader(whichMuons+" #mu");

  // create a legend for Wmunu and Zmumu separately (in upper right corner)
  TLegend *leg4 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg4->SetFillStyle(0);
  leg4->SetBorderSize(0);
  leg4->SetHeader("Top-Antitop(Phythia)");  
  //  leg0->AddEntry( n_  [kAll       ] , "inclusive"         , "PL" );
  leg4->AddEntry( pt_  [kSignal    ] , "semi-lep. ( #mu )" , "PL" );
  leg4->AddEntry( pt_  [kBackground] , "other decays ttbar", "PL" );
  leg4->AddEntry( pt_  [kQCD       ] , "QCD"               , "PL" );
  leg4->AddEntry( pt_  [kWmunu     ] , "Wmunu"             , "PL" );
  leg4->AddEntry( pt_  [kZmumu     ] , "Zmumu"             , "PL" );
  //  leg4->AddEntry( pt_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );

  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  canv0->SetTitle("MuonMultiplicity " +whichMuons+" #mu");

  // Set axis style for different collections
  if(whichMuons=="unselected"){
  axesStyle(*n_  [kSignal], "N_{#mu}: leading #mu", "events");
    n_[kSignal]->GetXaxis()->SetTitleOffset(1.1);
  }
  if(whichMuons=="combined"){
  axesStyle(*n_  [kSignal], "N_{#mu}: Tracker and #mu-chamber", "events");
    n_[kSignal]->GetXaxis()->SetTitleOffset(1.1);
  }

  if(whichMuons=="trigger"){
  axesStyle(*n_  [kSignal], "N_{#mu}:combined #mu, p_{t}>10, |#eta|<2.5", "events");
     n_[kSignal]->GetXaxis()->SetTitleOffset(1.1);
  }

  if(whichMuons=="track"){
  axesStyle(*n_  [kSignal], "N_{#mu}: nhit>10, #chi^{2}<10, d_{0}<0.02, |#eta|<2.5, p_{t}>10 ", "events");
  n_[kSignal]->GetXaxis()->SetTitleSize(0.04);
  n_[kSignal]->GetXaxis()->SetTitleOffset(1.3);
  }

  if(whichMuons=="loose"){
  axesStyle(*n_  [kSignal], "N_{#mu}: Track #mu, relIso<0.2", "events");
  n_[kSignal]->GetXaxis()->SetTitleOffset(1.1);
  }

  if(whichMuons=="good"){
  axesStyle(*n_  [kSignal], "N_{#mu}: Track #mu, p_{t}>20, |#eta|<2.1", "events");
  n_[kSignal]->GetXaxis()->SetTitleOffset(1.1);
  }

  if(whichMuons=="golden"){
  axesStyle(*n_  [kSignal], "N_{#mu}: good #mu, MIP", "events");
  n_[kSignal]->GetXaxis()->SetTitleOffset(1.1);
  }

  if(whichMuons=="tight"){
  axesStyle(*n_  [kSignal], "N_{#mu}: good #mu, MIP, relIso<0.05", "events");
  n_[kSignal]->GetXaxis()->SetTitleOffset(1.1);
  }


  n_  [kSignal       ]->SetNdivisions(10);
  n_  [kSignal       ]->SetMinimum(1.);
  n_  [kSignal       ]->SetMaximum( 25* n_  [kBoson]->GetMaximum() );
  //  n_  [kAll       ]->Draw();
  n_  [kSignal    ]->Draw();
  n_  [kBackground]->Draw("same");
  n_  [kQCD       ]->Draw("same");
  //  n_  [kWmunu     ]->Draw("same");
  //  n_  [kZmumu     ]->Draw("same");
  n_ [kBoson         ]->Draw("same");
  //n_  [kAll       ]->Draw("esame");
  leg0->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for pt_
  // ---

  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);
  // draw canvas
  canv1->cd(0);
  canv1->SetLogy(1);
  canv1->SetTitle("Muon p_{t} " +whichMuons+" # mu");
  if(whichMuons=="loose"){
  axesStyle(*pt_ [kSignal], "p_{t}( lead #mu ) [GeV]", "events");
  }
  else{
    axesStyle(*pt_ [kSignal], "p_{t}( lead #mu ) [GeV]", "events");
  }
  pt_[kSignal    ]->SetMaximum( 250* pt_ [kBoson]->GetMaximum() );
  pt_[kSignal    ]->SetMinimum( 1 );
  pt_[kSignal]->GetXaxis()->SetTitleOffset(1.1);
  //  pt_[kAll       ]->Draw();
  pt_[kSignal    ]->Draw();
  pt_[kBackground]->Draw("same");
  pt_[kQCD       ]->Draw("same");
  pt_[kWmunu     ]->Draw("same");
  pt_[kZmumu     ]->Draw("same");
  //  pt_[kBoson     ]->Draw("same");
  leg2->Draw("same");
  leg4->Draw("same");

  // ---
  //    do the printing for eta_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  //  canv2->SetLogy(1);
  canv2->SetTitle("#eta " +whichMuons+" #mu");
  axesStyle(*eta_[kSignal], "#eta( #mu )", "events");
  eta_[kSignal       ]->SetMinimum( 1 );
  eta_[kSignal       ]->SetMaximum( 1.8* eta_[kQCD]->GetMaximum() ); //180.0 kBoson
  //  eta_[kAll       ]->Draw();
  eta_[kSignal    ]->Draw();
  eta_[kBackground]->Draw("same");
  eta_[kQCD       ]->Draw("same");
  //  eta_[kWmunu     ]->Draw("same");
  //  eta_[kZmumu     ]->Draw("same");
  eta_[kBoson     ]->Draw("same");
  //eta_[kAll       ]->Draw("same");
  leg1->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for phi_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  axesStyle(*phi_[kAll], "#phi( #mu )", "events");
  phi_[kSignal       ]->SetMinimum( 0 );
  phi_[kSignal       ]->SetMaximum( 1.2* phi_[kWmunu]->GetMaximum() );
  //  phi_[kAll       ]->Draw();
  phi_[kSignal    ]->Draw();
  phi_[kBackground]->Draw("same");
  phi_[kQCD       ]->Draw("same");
  phi_[kWmunu     ]->Draw("same");
  phi_[kZmumu     ]->Draw("same");
  //phi_[kAll       ]->Draw("same");
  leg1->Draw("same");
  leg2->Draw("same");

// saving 

// 1.as picture 
canv0->Print("./analyzeMuonCutflow/Multiplicity"+whichMuons+"Muons.png");
canv1->Print("./analyzeMuonCutflow/Pt"+whichMuons+"Muons.png"          );
canv2->Print("./analyzeMuonCutflow/Eta"+whichMuons+"Muons.png"         );
canv3->Print("./analyzeMuonCutflow/Phi"+whichMuons+"Muons.png"         );

//2.as ps-file
canv0->Print("./analyzeMuonCutflow/Kinematics"+whichMuons+"Muons.ps(");
canv1->Print("./analyzeMuonCutflow/Kinematics"+whichMuons+"Muons.ps" );
canv2->Print("./analyzeMuonCutflow/Kinematics"+whichMuons+"Muons.ps)");
canv3->Print("./analyzeMuonCutflow/Kinematics"+whichMuons+"Muons.ps)"       );

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
  hist.GetXaxis()->SetNdivisions (  210);
  
  hist.GetYaxis()->SetTitle(titleY);
  hist.GetYaxis()->SetTitleSize  ( 0.07);
  hist.GetYaxis()->SetTitleColor (    1);
  hist.GetYaxis()->SetTitleOffset(  1.4);
  hist.GetYaxis()->SetTitleFont  (   62);
  hist.GetYaxis()->SetLabelSize  ( 0.04);
  hist.GetYaxis()->SetLabelFont  (   62);
  hist.GetYaxis()->CenterTitle  ( true);
}

