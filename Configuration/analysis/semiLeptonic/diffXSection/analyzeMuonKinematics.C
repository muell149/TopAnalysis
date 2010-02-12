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
  //  this makro plots the Multiplizity, pt, eta and phi distributions 
  //  of different Muon Collections for ttbar and different
  //  BG-sample in different steps of the cutflow
  // ---

enum styles {kAll, kSignal, kBackground, kQCD, kWmunu, kZmumu, kBoson};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);

void analyzeMuonKinematics(TString whichMuons = "tight", TString whichsample = "pythia10")  //  "tight" // "loose" // "track" // "good" // "combined" // "unselected" // ...
{

  // set the certain step in cutflow when monitoring is applied
  TString CutStep = "";
  // ""       : before jet cuts are applied, before  muon cuts and Veto Cuts are applied
  // "After"  : after  jet cuts are applied, after   muon cuts and Veto Cuts are applied

  // choose the sample
  // "pythia10" // "madgraph10" // "nlo10"
  // "pythia7"  // "madgraph7"  // "nlo7"

  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  files_.push_back(new TFile("./"+whichsample+"/analyzeSemiLeptonicSelection_all.root"  ) );
  files_.push_back(new TFile("./"+whichsample+"/analyzeSemiLeptonicSelection_sig.root"  ) );
  files_.push_back(new TFile("./"+whichsample+"/analyzeSemiLeptonicSelection_bkg.root"  ) );
  if(whichsample == "pythia10" || whichsample == "madgraph10" || whichsample == "nlo10" ){
    files_.push_back(new TFile("./pythia10/analyzeSemiLeptonicSelection_QCD.root"       ) );
  }
  else{
    files_.push_back(new TFile("./pythia7/analyzeSemiLeptonicSelection_QCD.root"        ) );
  }
  if(whichsample == "nlo10" || whichsample == "nlo7"){
    if(whichsample == "nlo10"){
      files_.push_back(new TFile("./madgraph10/analyzeSemiLeptonicSelection_Wmunu.root") );
      files_.push_back(new TFile("./madgraph10/analyzeSemiLeptonicSelection_Zmumu.root") );  
    }
    if(whichsample == "nlo7"){
      files_.push_back(new TFile("./madgraph7/analyzeSemiLeptonicSelection_Wmunu.root") );
      files_.push_back(new TFile("./madgraph7/analyzeSemiLeptonicSelection_Zmumu.root") );  
    }
  }
  else{
  files_.push_back(new TFile("./"+whichsample+"/analyzeSemiLeptonicSelection_Wmunu.root") );
  files_.push_back(new TFile("./"+whichsample+"/analyzeSemiLeptonicSelection_Zmumu.root") );
  }

  // histogram scaling because of lumiweighting
  std::vector<double> lumiweight;

  // add scaling factors here!!!
//   lumiweight.push_back(1.0);
//   lumiweight.push_back(1.0);
//   lumiweight.push_back(1.0);
//   lumiweight.push_back(1.0);
//   lumiweight.push_back(1.0);
//   lumiweight.push_back(1.0);

  // for current 10 TeV Pythia sample
  if( whichsample == "pythia10"){
    //ttbar (all, bg, sg - coming from the same sample)
    lumiweight.push_back(0.0391);
    lumiweight.push_back(0.0391);
    lumiweight.push_back(0.0391);
    //  QCD
    lumiweight.push_back(1.1161);
    //  Wmunu
    lumiweight.push_back(0.2522);
    //  Zmumu
    lumiweight.push_back(0.0351);
  }

  // for current 10 TeV Madgraph sample
  if( whichsample == "madgraph10"){
    //ttbar+jets (all, bg, sg - coming from the same sample)
    lumiweight.push_back(0.0192);
    lumiweight.push_back(0.0192);
    lumiweight.push_back(0.0192);
    //  QCD PYTHIA!!!!!!!
    lumiweight.push_back(1.1161);
    //  W+jets
    lumiweight.push_back(0.2068);
    //  Z+jets
    lumiweight.push_back(0.2262);
  }

  // for current 10 TeV Mc@NLO sample
  if( whichsample == "nlo10"){
    //ttbar (all, bg, sg - coming from the same sample)
    lumiweight.push_back(0.0208);
    lumiweight.push_back(0.0208);
    lumiweight.push_back(0.0208);
    //  QCD PYTHIA!!!!!!!
    lumiweight.push_back(1.1161);
    //  W+jets MADGRAPH!!!!!!!
    lumiweight.push_back(0.2068);
    //  Z+jets MADGRAPH!!!!!!!
    lumiweight.push_back(0.2262);
  }

 // for current 7 TeV Pythia sample
  if( whichsample == "pythia7"){
    //ttbar (all, bg, sg - coming from the same sample)
    lumiweight.push_back(0.0149);
    lumiweight.push_back(0.0149);
    lumiweight.push_back(0.0149);
    //  QCD
    lumiweight.push_back(1.0286);
    //  Wmunu
    lumiweight.push_back(0.1632);
    //  Zmumu
    lumiweight.push_back(0.0212);
  }

  // for current 7 TeV Madgraph sample
  if( whichsample == "madgraph7"){
    //ttbar (all, bg, sg - coming from the same sample)
    lumiweight.push_back(0.0088);
    lumiweight.push_back(0.0088);
    lumiweight.push_back(0.0088);
    //  QCD PYTHIA!!!!!!!
    lumiweight.push_back(1.0286);
    //  W+jets 
    lumiweight.push_back(0.1202);
    //  Z+jets
    lumiweight.push_back(0.1227);
  }

  // for current 7 TeV NLO sample
  if( whichsample == "nlo7"){
    //ttbar (all, bg, sg - coming from the same sample)
    lumiweight.push_back(0.0094);
    lumiweight.push_back(0.0094);
    lumiweight.push_back(0.0094);
    //  QCD PYTHIA!!!!!!!
    lumiweight.push_back(1.0286);
    //  W+jets MADGRAPH!!!!
    lumiweight.push_back(0.1202);
    //  Z+jets MADGRAPH!!!!
    lumiweight.push_back(0.1227);
  }

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> n_, pt_, eta_, phi_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    n_  .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonKinematics"+CutStep+"/n"    )->Clone() );
    pt_ .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonKinematics"+CutStep+"/pt"   )->Clone() );
    eta_.push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonKinematics"+CutStep+"/eta"  )->Clone() );
    phi_.push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonKinematics"+CutStep+"/phi"  )->Clone() );
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
  histogramStyle(*pt_ [kAll       ], kAll       );
  histogramStyle(*pt_ [kSignal    ], kSignal    );
  histogramStyle(*pt_ [kBackground], kBackground);
  histogramStyle(*pt_ [kQCD]       , kQCD       );
  //  histogramStyle(*pt_ [kWmunu]     , kWmunu     );
  //  histogramStyle(*pt_ [kZmumu]     , kZmumu     );
  histogramStyle(*pt_ [kBoson]     ,   kBoson    );

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
  //  histogramStyle(*phi_[kWmunu]     , kWmunu     );
  //  histogramStyle(*phi_[kZmumu]     , kZmumu     );
  histogramStyle(*phi_[kBoson]     , kBoson     );


  // ---
  //    create legends depending on the used sample
  // ---

  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  TLegend *leg1 = new TLegend(0.40, 0.75, 1.05, 0.95);

 if( whichsample == "pythia10"){    
    // create a legend (in upper right corner)
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("Top-Antitop(Phythia, 10TeV)");
    //  leg0->AddEntry( n_[kAll       ] , "inclusive"         , "PL" );
    leg0->AddEntry( n_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg0->AddEntry( n_[kBackground] , "other decays"      , "PL" );
    leg0->AddEntry( n_  [kQCD       ] , "QCD"               , "PL" );
    //  leg0->AddEntry( n_  [kWmunu     ] , "Wmunu"             , "PL" );
    //  leg0->AddEntry( n_  [kZmumu     ] , "Zmumu"             , "PL" );
    leg0->AddEntry( n_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );
    
    // create a legend (in upper center)
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("Top-Antitop(Phythia, 10TeV)");
    //  leg1->AddEntry( n_[kAll       ] , "inclusive"         , "PL" );
    leg1->AddEntry( n_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg1->AddEntry( n_[kBackground] , "other decays"      , "PL" );
    leg1->AddEntry( n_[kQCD     ] , "QCD"               , "PL" );
    //  leg1->AddEntry( n_  [kWmunu     ] , "Wmunu"             , "PL" );
    //  leg1->AddEntry( n_  [kZmumu     ] , "Zmumu"             , "PL" );
    leg1->AddEntry( n_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );
  }
  
 if( whichsample == "madgraph10"){

    // create a legend (in upper right corner)
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("Top-Antitop(Madgraph, 10TeV)");
    //  leg0->AddEntry( n_[kAll       ] , "inclusive"         , "PL" );
    leg0->AddEntry( n_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg0->AddEntry( n_[kBackground] , "other decays"      , "PL" );
    leg0->AddEntry( n_[kQCD       ] , "QCD (Pythia)"        , "PL" );
    //  leg0->AddEntry( n_  [kWmunu     ] , "W+jets"             , "PL" );
    //  leg0->AddEntry( n_  [kZmumu     ] , "Z+jets"             , "PL" );
    leg0->AddEntry( n_  [kBoson]      , "Wjets + Zjets", "PL"  );
    
    // create a legend (in upper center)
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("Top-Antitop(Madgraph, 10TeV)");
    //  leg1->AddEntry( n_[kAll       ] , "inclusive"         , "PL" );
    leg1->AddEntry( n_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg1->AddEntry( n_[kBackground] , "other decays"      , "PL" );
    leg1->AddEntry( n_[kQCD     ] , "QCD (Pythia)"               , "PL" );
    //  leg1->AddEntry( n_  [kWmunu     ] , "W+jets"             , "PL" );
    //  leg1->AddEntry( n_  [kZmumu     ] , "Z+jets"             , "PL" );
    leg1->AddEntry( n_  [kBoson]      , "Wjets + Zjets", "PL"  );
  }

 if( whichsample == "nlo10"){

    // create a legend (in upper right corner)
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("Top-Antitop(Mc@NLO, 10TeV)");
    //  leg0->AddEntry( n_[kAll       ] , "inclusive"         , "PL" );
    leg0->AddEntry( n_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg0->AddEntry( n_[kBackground] , "other decays"      , "PL" );
    leg0->AddEntry( n_[kQCD       ] , "QCD (Pythia)"        , "PL" );
    //  leg0->AddEntry( n_  [kWmunu     ] , "W+jets (Madgraph)"             , "PL" );
    //  leg0->AddEntry( n_  [kZmumu     ] , "Z+jets (Madgraph)"             , "PL" );
    leg0->AddEntry( n_  [kBoson]      , "Wjets + Zjets (Madgraph)", "PL"  );
    
    // create a legend (in upper center)
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("Top-Antitop(Mc@NLO, 10TeV)");
    //  leg1->AddEntry( n_[kAll       ] , "inclusive"         , "PL" );
    leg1->AddEntry( n_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg1->AddEntry( n_[kBackground] , "other decays"      , "PL" );
    leg1->AddEntry( n_[kQCD     ] , "QCD (Pythia)"               , "PL" );
    //  leg1->AddEntry( n_  [kWmunu     ] , "W+jets (Madgraph)"             , "PL" );
    //  leg1->AddEntry( n_  [kZmumu     ] , "Z+jets (Madgraph)"             , "PL" );
    leg1->AddEntry( n_  [kBoson]      , "Wjets + Zjets (Madgraph)", "PL"  );
  }
 if( whichsample == "pythia7"){

    // create a legend (in upper right corner)
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("Top-Antitop(Phythia, 7TeV)");
    //  leg0->AddEntry( n_[kAll       ] , "inclusive"         , "PL" );
    leg0->AddEntry( n_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg0->AddEntry( n_[kBackground] , "other decays"      , "PL" );
    leg0->AddEntry( n_  [kQCD       ] , "QCD"               , "PL" );
    //  leg0->AddEntry( n_  [kWmunu     ] , "Wmunu"             , "PL" );
    //  leg0->AddEntry( n_  [kZmumu     ] , "Zmumu"             , "PL" );
    leg0->AddEntry( n_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );
    
    // create a legend (in upper center)
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("Top-Antitop(Phythia, 7TeV)");
    //  leg1->AddEntry( n_[kAll       ] , "inclusive"         , "PL" );
    leg1->AddEntry( n_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg1->AddEntry( n_[kBackground] , "other decays"      , "PL" );
    leg1->AddEntry( n_[kQCD     ] , "QCD"               , "PL" );
    //  leg1->AddEntry( n_  [kWmunu     ] , "Wmunu"             , "PL" );
    //  leg1->AddEntry( n_  [kZmumu     ] , "Zmumu"             , "PL" );
    leg1->AddEntry( n_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );
  }
  
 if( whichsample == "madgraph7"){

    // create a legend (in upper right corner)
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("Top-Antitop(Madgraph, 7TeV)");
    //  leg0->AddEntry( n_[kAll       ] , "inclusive"         , "PL" );
    leg0->AddEntry( n_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg0->AddEntry( n_[kBackground] , "other decays"      , "PL" );
    leg0->AddEntry( n_[kQCD       ] , "QCD (Pythia)"        , "PL" );
    //  leg0->AddEntry( n_  [kWmunu     ] , "W+jets"             , "PL" );
    //  leg0->AddEntry( n_  [kZmumu     ] , "Z+jets"             , "PL" );
    leg0->AddEntry( n_  [kBoson]      , "Wjets + Zjets", "PL"  );
    
    // create a legend (in upper center)
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("Top-Antitop(Madgraph, 7TeV)");
    //  leg1->AddEntry( n_[kAll       ] , "inclusive"         , "PL" );
    leg1->AddEntry( n_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg1->AddEntry( n_[kBackground] , "other decays"      , "PL" );
    leg1->AddEntry( n_[kQCD     ] , "QCD (Pythia)"               , "PL" );
    //  leg1->AddEntry( n_  [kWmunu     ] , "W+jets"             , "PL" );
    //  leg1->AddEntry( n_  [kZmumu     ] , "Z+jets"             , "PL" );
    leg1->AddEntry( n_  [kBoson]      , "Wjets + Zjets", "PL"  );
  }

 if( whichsample == "nlo7"){

    // create a legend (in upper right corner)
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("Top-Antitop(Mc@NLO, 7TeV)");
    //  leg0->AddEntry( n_[kAll       ] , "inclusive"         , "PL" );
    leg0->AddEntry( n_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg0->AddEntry( n_[kBackground] , "other decays"      , "PL" );
    leg0->AddEntry( n_[kQCD       ] , "QCD (Pythia)"        , "PL" );
    //  leg0->AddEntry( n_  [kWmunu     ] , "W+jets (Madgraph)"             , "PL" );
    //  leg0->AddEntry( n_  [kZmumu     ] , "Z+jets (Madgraph)"             , "PL" );
    leg0->AddEntry( n_  [kBoson]      , "Wjets + Zjets (Madgraph)", "PL"  );
    
    // create a legend (in upper center)
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("Top-Antitop(Mc@NLO, 7TeV)");
    //  leg1->AddEntry( n_[kAll       ] , "inclusive"         , "PL" );
    leg1->AddEntry( n_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg1->AddEntry( n_[kBackground] , "other decays"      , "PL" );
    leg1->AddEntry( n_[kQCD     ] , "QCD (Pythia)"               , "PL" );
    //  leg1->AddEntry( n_  [kWmunu     ] , "W+jets (Madgraph)"             , "PL" );
    //  leg1->AddEntry( n_  [kZmumu     ] , "Z+jets (Madgraph)"             , "PL" );
    leg1->AddEntry( n_  [kBoson]      , "Wjets + Zjets (Madgraph)", "PL"  );
  }

  // create an info legend containig the used mu-collection
  TLegend *leg2 = new TLegend(0.15, 1.15, 0.40, 0.80);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetHeader(whichMuons+" #mu");

  TLegend *leg3 = new TLegend(0.25, 1.15, 0.50, 0.80);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  leg3->SetHeader(whichMuons+" #mu");

   // ---
  //    do the printing for n_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  canv0->SetTitle("MuonMultiplicity " +whichMuons+" #mu");

  // Set axis style for different collections
  if(whichMuons=="unselected"){
  axesStyle(*n_  [kSignal], "N_{#mu}: hltMu9 #mu", "events");
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
  double max=n_[kSignal]->GetMaximum();
  if(max<n_[kQCD       ]->GetMaximum())max=n_[kQCD]       ->GetMaximum();
  if(max<n_[kBackground]->GetMaximum())max=n_[kBackground]->GetMaximum();
  if(max<n_[kBoson     ]->GetMaximum())max=n_[kBoson     ]->GetMaximum();
  n_  [kSignal       ]->SetMaximum( 250* max );
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
  max=pt_[kSignal]->GetMaximum();
  if(max<pt_[kQCD       ]->GetMaximum())max=pt_[kQCD]       ->GetMaximum();
  if(max<pt_[kBackground]->GetMaximum())max=pt_[kBackground]->GetMaximum();
  if(max<pt_[kBoson     ]->GetMaximum())max=pt_[kBoson     ]->GetMaximum();
  pt_[kSignal    ]->SetMaximum( 250* max );
  pt_[kSignal    ]->SetMinimum( 1 );
  pt_[kSignal]->GetXaxis()->SetTitleOffset(1.1);
  //  pt_[kAll       ]->Draw();
  pt_[kSignal    ]->Draw();
  pt_[kBackground]->Draw("same");
  pt_[kQCD       ]->Draw("same");
  //  pt_[kWmunu     ]->Draw("same");
  //  pt_[kZmumu     ]->Draw("same");
  pt_[kBoson     ]->Draw("same");
  leg2->Draw("same");
  leg0->Draw("same");

  // ---
  //    do the printing for eta_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetLogy(1);
  //  canv2->SetLogy(1);
  canv2->SetTitle("#eta " +whichMuons+" #mu");
  axesStyle(*eta_[kSignal], "#eta( #mu )", "events");
  eta_[kSignal       ]->SetMinimum( 1 );
  max=eta_[kSignal]->GetMaximum();
  if(max<eta_[kQCD       ]->GetMaximum())max=eta_[kQCD]       ->GetMaximum();
  if(max<eta_[kBackground]->GetMaximum())max=eta_[kBackground]->GetMaximum();
  if(max<eta_[kBoson     ]->GetMaximum())max=eta_[kBoson     ]->GetMaximum();
  eta_[kSignal       ]->SetMaximum( 180* max );
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
  canv3->SetLogy(1);
  axesStyle(*phi_[kSignal], "#phi( #mu )", "events");
  phi_[kSignal       ]->SetMinimum( 1 );
  max=phi_[kSignal]->GetMaximum();
  if(max<phi_[kQCD       ]->GetMaximum())max=phi_[kQCD]       ->GetMaximum();
  if(max<phi_[kBackground]->GetMaximum())max=phi_[kBackground]->GetMaximum();
  if(max<phi_[kBoson     ]->GetMaximum())max=phi_[kBoson     ]->GetMaximum();
  phi_[kSignal       ]->SetMaximum( 50.0* max );
  //  phi_[kAll       ]->Draw();
  phi_[kSignal    ]->Draw();
  phi_[kBackground]->Draw("same");
  phi_[kQCD       ]->Draw("same");
  //  phi_[kWmunu     ]->Draw("same");
  //  phi_[kZmumu     ]->Draw("same");
  phi_[kBoson       ]->Draw("same");
  //phi_[kAll       ]->Draw("same");
  leg1->Draw("same");
  leg2->Draw("same");

// saving 

// 1.as picture 
canv0->Print("./analyzeMuonCutflow/Multiplicity"+whichMuons+"Muons"+CutStep+whichsample+".png");
canv1->Print("./analyzeMuonCutflow/Pt"+whichMuons+"Muons"+CutStep+whichsample+".png"          );
canv2->Print("./analyzeMuonCutflow/Eta"+whichMuons+"Muons"+CutStep+whichsample+".png"         );
canv3->Print("./analyzeMuonCutflow/Phi"+whichMuons+"Muons"+CutStep+whichsample+".png"         );

//2.as ps-file
canv0->Print("./analyzeMuonCutflow/Kinematics"+whichMuons+"Muons"+CutStep+whichsample+".ps(");
canv1->Print("./analyzeMuonCutflow/Kinematics"+whichMuons+"Muons"+CutStep+whichsample+".ps" );
canv2->Print("./analyzeMuonCutflow/Kinematics"+whichMuons+"Muons"+CutStep+whichsample+".ps)");
//canv3->Print("./analyzeMuonCutflow/Kinematics"+whichMuons+"Muons"+CutStep+whichsample+".ps)");



 cout << "you can choose between muon collections via whichMuons-TString" << endl;
 cout << "you can look at the plots at different steps of event selection by changing the CutStep-Tstring in the file" << endl;
 cout << "you can change the inputsample via the whichsample-TString in the file (pythia,madgraph,mc@nlo for 7 and 10 TeV)" << endl;

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

