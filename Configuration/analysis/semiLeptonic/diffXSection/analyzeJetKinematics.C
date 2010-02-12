#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>

enum styles {kAll, kSignal, kBackground, kQCD, kWmunu, kZmumu, kBoson};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);
void drawcutline(double cutval, double maximum);

void analyzeJetKinematics(TString whichJets = "")
  // choose whichJets = unselected, central, reliable, tight for different steps in jetcuts
  
{
  // switch to b-jet by setting true:
  bool runOnBTaggedJets=false;


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
//   lumiweight.push_back(1.0);
//   lumiweight.push_back(1.0);
//   lumiweight.push_back(1.0);
//   lumiweight.push_back(1.0);
//   lumiweight.push_back(1.0);
//   lumiweight.push_back(1.0);

  // ttbar (all, bg, sg - coming from the same sample)
   lumiweight.push_back(0.039);
   lumiweight.push_back(0.039);
   lumiweight.push_back(0.039);
   //  QCD
   lumiweight.push_back(1.1161);
   //  Wmunu
   lumiweight.push_back(0.2212);
   //  Zmumu
   lumiweight.push_back(0.0458);


  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> n_, pt_, eta_, phi_;
  std::vector<TString> thoseJets;

  if( runOnBTaggedJets==false ){
    
    if(whichJets != ""){
      for(int i=0; i<4; i++){
	std::cout << "monitoring for " << whichJets << "jets" << endl;
	thoseJets.push_back(whichJets);
      }
    }
    else{
      std::cout << "monitoring of variables before cut" << endl;
      thoseJets.push_back("unselected");
      thoseJets.push_back("unselected");
      thoseJets.push_back("tight");
      thoseJets.push_back("tight");	
    }
    
  }


  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    if( runOnBTaggedJets==false ){

      eta_.push_back( (TH1F*)files_[idx]->Get(thoseJets[0]+"LeadingJetKinematics/eta")->Clone() );
      pt_ .push_back( (TH1F*)files_[idx]->Get(thoseJets[1]+"LeadingJetKinematics/pt" )->Clone() );
      n_  .push_back( (TH1F*)files_[idx]->Get(thoseJets[2]+"LeadingJetKinematics/n"  )->Clone() );
      phi_.push_back( (TH1F*)files_[idx]->Get(thoseJets[3]+"LeadingJetKinematics/phi")->Clone() );
      }

    else{
      std::cout << "monitoring for bjets" << endl;
      n_  .push_back( (TH1F*)files_[idx]->Get(whichJets+"BottomJetKinematics/n"  ) );
      pt_ .push_back( (TH1F*)files_[idx]->Get(whichJets+"BottomJetKinematics/pt" ) );
      eta_.push_back( (TH1F*)files_[idx]->Get(whichJets+"BottomJetKinematics/eta") );
      phi_.push_back( (TH1F*)files_[idx]->Get(whichJets+"BottomJetKinematics/phi") );
    }


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
  phi_[kBoson]->Add(phi_[kZmumu]);
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
  //  histogramStyle(*pt_ [kAll       ], kAll       );
  histogramStyle(*pt_ [kSignal    ], kSignal    );
  histogramStyle(*pt_ [kBackground], kBackground);
  histogramStyle(*pt_ [kQCD]       , kQCD       );
  //  histogramStyle(*pt_ [kWmunu]     , kWmunu     );
  //  histogramStyle(*pt_ [kZmumu]     , kZmumu     );
  histogramStyle(*pt_ [kBoson]     ,   kBoson    );

  // eta_
  //  histogramStyle(*eta_[kAll       ], kAll       );
  histogramStyle(*eta_[kSignal    ], kSignal    );
  histogramStyle(*eta_[kBackground], kBackground);
  histogramStyle(*eta_[kQCD       ], kQCD       );
  //  histogramStyle(*eta_ [kWmunu]     , kWmunu     );
  //  histogramStyle(*eta_ [kZmumu]     , kZmumu     );
  histogramStyle(*eta_ [kBoson]     ,   kBoson    );

  // phi_
  //  histogramStyle(*phi_[kAll       ], kAll       );
  histogramStyle(*phi_[kSignal    ], kSignal    );
  histogramStyle(*phi_[kBackground], kBackground);
  histogramStyle(*phi_[kQCD]       , kQCD       );
  // histogramStyle(*phi_[kWmunu]     , kWmunu     );
  // histogramStyle(*phi_[kZmumu]     , kZmumu     );
  histogramStyle(*phi_[kBoson]       , kBoson   );

  // ---
  //    create legends
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  //  leg0->AddEntry( n_  [kAll       ] , "inclusive"         , "PL" );
  leg0->AddEntry( n_  [kSignal    ] , "semi-lep. ( #mu )" , "PL" );
  leg0->AddEntry( n_  [kBackground] , "other decays"      , "PL" );
  leg0->AddEntry( n_  [kQCD       ] , "QCD"               , "PL" );
  //  leg0->AddEntry( n_  [kWmunu     ] , "Wmunu"             , "PL" );
  //  leg0->AddEntry( n_  [kZmumu     ] , "Zmumu"             , "PL" );
  leg0->AddEntry( n_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  //  leg1->AddEntry( n_  [kAll       ] , "inclusive"         , "PL" );
  leg1->AddEntry( n_  [kSignal    ] , "semi-lep. ( #mu )" , "PL" );
  leg1->AddEntry( n_  [kBackground] , "other decays"      , "PL" );
  leg1->AddEntry( n_  [kQCD       ] , "QCD"               , "PL" );
  //  leg1->AddEntry( n_  [kWmunu     ] , "Wmunu"             , "PL" );
  //  leg1->AddEntry( n_  [kZmumu     ] , "Zmumu"             , "PL" );
  leg1->AddEntry( n_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );

  // create a legend indicating the used jetcuts
  TLegend *leg2 = new TLegend(0.29, 0.92, 0.81, 0.99);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  TLegend *leg3 = new TLegend(0.29, 0.92, 0.81, 0.99);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  TLegend *leg4 = new TLegend(0.29, 0.92, 0.81, 0.99);
  leg4->SetFillStyle(0);
  leg4->SetBorderSize(0);
  if(runOnBTaggedJets==false){   
    leg2->SetHeader(thoseJets[0]+" Jets");
    leg3->SetHeader(thoseJets[1]+" Jets");
    leg4->SetHeader(thoseJets[2]+" Jets");
  }
  // prepare axes labels
  if( !runOnBTaggedJets ){
    axesStyle(*n_  [kSignal], "N_{Jet}(pt>30 GeV, |#eta|<2.4)", "events" );
    axesStyle(*pt_ [kSignal], "pt( Jet ) [GeV]", "events" );
    axesStyle(*eta_[kSignal], "#eta( Jet )", "events" );
    axesStyle(*phi_[kSignal], "#phi( Jet )", "events");
  }
  else{
    axesStyle(*n_  [kSignal], "N_{B-Jet}(pt>30 GeV, |#eta|<2.4)", "events");
    axesStyle(*pt_ [kSignal], "pt( B-Jet ) [GeV]", "events");
    axesStyle(*eta_[kSignal], "#eta( B-Jet )", "events");
    axesStyle(*phi_[kSignal], "#phi( B-Jet )", "events");
  }

  // ---
  //    do the printing for n_
  // ---
  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  n_  [kSignal    ]->SetMinimum(1.);
  n_  [kSignal    ]->SetMaximum( 5000* n_  [kQCD]->GetMaximum() );
  //  n_  [kAll       ]->Draw();
  n_  [kSignal    ]->Draw();
  n_  [kBackground]->Draw("same");
  n_  [kQCD       ]->Draw("same");
  n_  [kBoson     ]->Draw("same");
  //n_  [kAll       ]->Draw("esame");
  drawcutline(4., 0.00005*n_[kSignal]->GetMaximum());
  leg0->Draw("same");
  leg4->Draw("same");

  // ---
  //    do the printing for pt_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetLogy(1);
  pt_[kSignal    ]->SetMinimum( 1 );
  pt_ [kSignal    ]->SetMaximum( 100.5* pt_ [kQCD]->GetMaximum() );
  //  pt_ [kAll     ]->Draw();
  pt_ [kSignal    ]->Draw();
  pt_ [kBackground]->Draw("same");
  pt_ [kQCD       ]->Draw("same");
  pt_ [kBoson       ]->Draw("same");
  //pt_ [kAll       ]->Draw("same");
  drawcutline(30., 0.05*pt_[kSignal]->GetMaximum());
  leg0->Draw("same");
  leg3->Draw("same");
  // ---
  //    do the printing for eta_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetLogy(1);
  eta_[kSignal    ]->SetMinimum( 1 );
  eta_[kSignal    ]->SetMaximum( 5000.0* eta_[kQCD]->GetMaximum() );
  //  eta_[kAll       ]->Draw();
  eta_[kSignal    ]->Draw();
  eta_[kBackground]->Draw("same");
  eta_[kQCD       ]->Draw("same");
  eta_[kBoson     ]->Draw("same");
  //eta_[kAll       ]->Draw("same");
  drawcutline( 2.4, 0.005*eta_[kSignal]->GetMaximum());
  drawcutline(-2.4, 0.005*eta_[kSignal]->GetMaximum());
  leg1->Draw("same");
  leg2->Draw("same");

  // ---
  //    do the printing for phi_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  canv3->SetLogy(1);
  phi_[kSignal    ]->SetMinimum( 1 );
  phi_[kSignal    ]->SetMaximum( 2000.0* phi_[kQCD]->GetMaximum() );
  //  phi_[kAll       ]->Draw();
  phi_[kSignal    ]->Draw();
  phi_[kBackground]->Draw("same");
  phi_[kQCD       ]->Draw("same");
  phi_[kBoson     ]->Draw("same");
  //phi_[kAll       ]->Draw("same");
  leg1->Draw("same");
  leg4->Draw("same");

// saving 


  if(runOnBTaggedJets==false){

    if(whichJets==""){
      
      // 1.as picture 
      canv0->Print("./analyzeJetQuantities/"+thoseJets[3]+"JetMultiplicity.png");
      canv1->Print("./analyzeJetQuantities/"+thoseJets[1]+"JetPt.png"          );
      canv2->Print("./analyzeJetQuantities/"+thoseJets[0]+"JetEta.png"         );
      canv3->Print("./analyzeJetQuantities/"+thoseJets[3]+"JetPhi.png"         );
      
      // 2.as ps-file			 
      canv0->Print("./analyzeJetQuantities/"+thoseJets[3]+"JetKinematics.ps(");
      canv1->Print("./analyzeJetQuantities/"+thoseJets[1]+"JetKinematics.ps" );
      canv2->Print("./analyzeJetQuantities/"+thoseJets[0]+"JetKinematics.ps" );
      canv3->Print("./analyzeJetQuantities/"+thoseJets[3]+"JetKinematics.ps)");  

    }
    else{
  
      // 1.as picture 
      canv0->Print("./analyzeJetQuantities/"+whichJets+"JetMultiplicity.png");
      canv1->Print("./analyzeJetQuantities/"+whichJets+"JetPt.png"          );
      canv2->Print("./analyzeJetQuantities/"+whichJets+"JetEta.png"         );
      canv3->Print("./analyzeJetQuantities/"+whichJets+"JetPhi.png"         );
      
      // 2.as ps-file			 
      canv0->Print("./analyzeJetQuantities/"+whichJets+"JetKinematics.ps(");
      canv1->Print("./analyzeJetQuantities/"+whichJets+"JetKinematics.ps" );
      canv2->Print("./analyzeJetQuantities/"+whichJets+"JetKinematics.ps" );
      canv3->Print("./analyzeJetQuantities/"+whichJets+"JetKinematics.ps)");
    }


  }
  if(runOnBTaggedJets==true){
    // 1.as picture 
    canv0->Print("./analyzeJetQuantities/BtaggedJetMultiplicity.png");
    canv1->Print("./analyzeJetQuantities/BtaggedJetPt.png"          );
    canv2->Print("./analyzeJetQuantities/BtaggedJetEta.png"         );
    canv3->Print("./analyzeJetQuantities/BtaggedJetPhi.png"         );

    // 2.as ps-file
    canv0->Print("./analyzeJetQuantities/BtaggedJetKinematics.ps(");
    canv1->Print("./analyzeJetQuantities/BtaggedJetKinematics.ps" );
    canv2->Print("./analyzeJetQuantities/BtaggedJetKinematics.ps" );
    canv3->Print("./analyzeJetQuantities/BtaggedJetKinematics.ps)");
  }
    cout << "you have the option to choose runOnBTaggedJets=true or runOnBTaggedJets=false in the file" << endl;
    cout << "choose unselected, central, reliable or tight for different jet collections" << endl;
}

void drawcutline(double cutval, double maximum)
{
  TLine *cut = new TLine();
  cut->SetLineWidth(3);
  cut->SetLineStyle(2);
  cut->SetLineColor(2);
  cut->DrawLine(cutval,0.,cutval,maximum);
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
  hist.GetYaxis()->CenterTitle   ( true);
}
