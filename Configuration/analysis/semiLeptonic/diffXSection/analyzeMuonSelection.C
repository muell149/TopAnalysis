#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>

  // ---
  //  introduction
  // ---
  //  This Macro analyzes some mu-Cut variables like number of valid Trackerhits,
  //  chi^2, d0, energies in ecal and hcal and relIso within ttbarsignal, qcd, wmunu and zmumu-sample  
  //  default: nhit, chi^2 and d0, dz for trigger mu, ecal und hcal deposit for good mu and relIso for golden mu
  // ---

enum styles {kAll, kSignal, kBackground, kQCD, kWmunu, kZmumu, kBoson};

void canvasStyle(TCanvas* canv);
void histogramStyle(TH1* hist, unsigned int style);
void axesStyle(TH1* hist, const char* titleX, const char* titleY);
void drawcutline(double cutval, double maximum);

void analyzeMuonSelection(TString whichMuons = "", TString whichsample = "pythia10")  //  "golden" // "tight" // "loose" // "track" // "good" // "combined" // "unselected"
{
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

  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;

  // add scaling factors here!

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
  std::vector<TString> thoseMuons;
  if(whichMuons != ""){
    for(int i=0; i<6; i++){
      thoseMuons.push_back(whichMuons);
    }
  }
  else{
       for(int i=0; i<4; i++){
         thoseMuons.push_back("trigger");
    }
    for(int i=0; i<2; i++){
      thoseMuons.push_back("good");
    }
    thoseMuons.push_back("golden");
    
  }

  std::vector<TH1F*> nHit_, chi2_, d0_, ecalEn_, hcalEn_, relIso_, dz_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    nHit_  .push_back( (TH1F*)files_[idx]->Get(thoseMuons[0]+"MuonQuality/nHit"  )->Clone() );
    chi2_  .push_back( (TH1F*)files_[idx]->Get(thoseMuons[1]+"MuonQuality/chi2"  )->Clone() );
    d0_    .push_back( (TH1F*)files_[idx]->Get(thoseMuons[2]+"MuonQuality/dB"    )->Clone() );
    dz_    .push_back( (TH1F*)files_[idx]->Get(thoseMuons[2]+"MuonQuality/dz"    )->Clone() );
    ecalEn_.push_back( (TH1F*)files_[idx]->Get(thoseMuons[3]+"MuonQuality/ecalEn")->Clone() );
    hcalEn_.push_back( (TH1F*)files_[idx]->Get(thoseMuons[4]+"MuonQuality/hcalEn")->Clone() );
    relIso_.push_back( (TH1F*)files_[idx]->Get(thoseMuons[5]+"MuonQuality/relIso")->Clone() );
  }

  // ---
  //    close input files
  // ---
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    //files_[idx]->Close();
  }
  
  // ---
  // Normalization and adding Vektor Bosons
  // ---
  nHit_[kWmunu]->Scale(lumiweight[kWmunu]);
  nHit_[kZmumu]->Scale(lumiweight[kZmumu]);
  nHit_.push_back( (TH1F*)nHit_[kWmunu]->Clone());
  nHit_[kBoson]->Add(nHit_[kZmumu]);
  nHit_[kQCD]->Scale(lumiweight[kQCD]);  
  //  nHit_[kAll]->Scale(lumiweight[kAll]);  
  nHit_[kSignal]->Scale(lumiweight[kSignal]); 
  nHit_[kBackground]->Scale(lumiweight[kBackground]); 

  chi2_[kWmunu]->Scale(lumiweight[kWmunu]);
  chi2_[kZmumu]->Scale(lumiweight[kZmumu]);
  chi2_.push_back( (TH1F*)chi2_[kWmunu]->Clone());
  chi2_[kBoson]->Add(chi2_[kZmumu]);
  chi2_[kQCD]->Scale(lumiweight[kQCD]);  
  //  chi2_[kAll]->Scale(lumiweight[kAll]);  
  chi2_[kSignal]->Scale(lumiweight[kSignal]); 
  chi2_[kBackground]->Scale(lumiweight[kBackground]); 

  d0_[kWmunu]->Scale(lumiweight[kWmunu]);
  d0_[kZmumu]->Scale(lumiweight[kZmumu]);
  d0_.push_back( (TH1F*)d0_[kWmunu]->Clone());
  d0_[kBoson]->Add(d0_[kZmumu]);
  d0_[kQCD]->Scale(lumiweight[kQCD]);  
  //  d0_[kAll]->Scale(lumiweight[kAll]);  
  d0_[kSignal]->Scale(lumiweight[kSignal]); 
  d0_[kBackground]->Scale(lumiweight[kBackground]); 

  dz_[kWmunu]->Scale(lumiweight[kWmunu]);
  dz_[kZmumu]->Scale(lumiweight[kZmumu]);
  dz_.push_back( (TH1F*)dz_[kWmunu]->Clone());
  dz_[kBoson]->Add(dz_[kZmumu]);
  dz_[kQCD]->Scale(lumiweight[kQCD]);  
  //  dz_[kAll]->Scale(lumiweight[kAll]);  
  dz_[kSignal]->Scale(lumiweight[kSignal]); 
  dz_[kBackground]->Scale(lumiweight[kBackground]);

  ecalEn_[kWmunu]->Scale(lumiweight[kWmunu]);
  ecalEn_[kZmumu]->Scale(lumiweight[kZmumu]);
  ecalEn_.push_back( (TH1F*)ecalEn_[kWmunu]->Clone());
  ecalEn_[kBoson]->Add(ecalEn_[kZmumu]);
  ecalEn_[kQCD]->Scale(lumiweight[kQCD]);  
  //  ecalEn_[kAll]->Scale(lumiweight[kAll]);  
  ecalEn_[kSignal]->Scale(lumiweight[kSignal]); 
  ecalEn_[kBackground]->Scale(lumiweight[kBackground]); 

  hcalEn_[kWmunu]->Scale(lumiweight[kWmunu]);
  hcalEn_[kZmumu]->Scale(lumiweight[kZmumu]);
  hcalEn_.push_back( (TH1F*)hcalEn_[kWmunu]->Clone());
  hcalEn_[kBoson]->Add(hcalEn_[kZmumu]);
  hcalEn_[kQCD]->Scale(lumiweight[kQCD]);  
  //  hcalEn_[kAll]->Scale(lumiweight[kAll]);  
  hcalEn_[kSignal]->Scale(lumiweight[kSignal]); 
  hcalEn_[kBackground]->Scale(lumiweight[kBackground]); 

  relIso_[kWmunu]->Scale(lumiweight[kWmunu]);
  relIso_[kZmumu]->Scale(lumiweight[kZmumu]);
  relIso_.push_back( (TH1F*)relIso_[kWmunu]->Clone());
  relIso_[kBoson]->Add(relIso_[kZmumu]);
  relIso_[kQCD]->Scale(lumiweight[kQCD]);  
  //  relIso_[kAll]->Scale(lumiweight[kAll]);  
  relIso_[kSignal]->Scale(lumiweight[kSignal]); 
  relIso_[kBackground]->Scale(lumiweight[kBackground]);

  // ---
  //    configure histograms
  // ---

  // nHit_
  histogramStyle(nHit_  [kSignal     ], kSignal     );
  histogramStyle(nHit_  [kQCD        ], kQCD        );
  //  histogramStyle(nHit_  [kWmunu      ], kWmunu      );
  //  histogramStyle(nHit_  [kZmumu      ], kZmumu      );
  histogramStyle(nHit_  [kBackground ], kBackground );
  histogramStyle(nHit_  [kBoson      ], kBoson      );

  // chi2_
  histogramStyle(chi2_ [kSignal     ], kSignal     );
  histogramStyle(chi2_ [kQCD        ], kQCD        );
  //  histogramStyle(chi2_ [kWmunu      ], kWmunu      );
  //  histogramStyle(chi2_ [kZmumu      ], kZmumu      );
  histogramStyle(chi2_ [kBackground ], kBackground );
  histogramStyle(chi2_ [kBoson      ], kBoson      );

  // d0_
  histogramStyle(d0_[kSignal     ], kSignal     );
  histogramStyle(d0_[kQCD        ], kQCD        );
  //  histogramStyle(d0_[kWmunu      ], kWmunu      );
  //  histogramStyle(d0_[kZmumu      ], kZmumu      );
  histogramStyle(d0_[kBackground ], kBackground );
  histogramStyle(d0_[kBoson      ], kBoson      );

  // dz_
  //  histogramStyle(dz_[kAll     ], kAll           );
  histogramStyle(dz_[kSignal     ], kSignal     );
  histogramStyle(dz_[kQCD        ], kQCD        );
  histogramStyle(dz_[kWmunu      ], kWmunu      );
  histogramStyle(dz_[kZmumu      ], kZmumu      );
  histogramStyle(dz_[kBackground ], kBackground );
  //  histogramStyle(dz_[kBoson      ], kBoson      );

  // ecalEn_
  histogramStyle(ecalEn_[kSignal     ], kSignal     );
  histogramStyle(ecalEn_[kQCD        ], kQCD        );
  //  histogramStyle(ecalEn_[kWmunu      ], kWmunu      );
  //  histogramStyle(ecalEn_[kZmumu      ], kZmumu      ); 
  histogramStyle(ecalEn_[kBackground ], kBackground );
  histogramStyle(ecalEn_[kBoson      ], kBoson      );

  // hcalEn_

  histogramStyle(hcalEn_[kSignal     ], kSignal     );
  histogramStyle(hcalEn_[kQCD        ], kQCD        );
  //  histogramStyle(hcalEn_[kWmunu      ], kWmunu      );
  //  histogramStyle(hcalEn_[kZmumu      ], kZmumu      ); 
  histogramStyle(hcalEn_[kBackground ], kBackground );
  histogramStyle(hcalEn_[kBoson      ], kBoson      );

  // relIso_
  histogramStyle(relIso_[kSignal     ], kSignal     );
  histogramStyle(relIso_[kQCD        ], kQCD        );
  //  histogramStyle(relIso_[kWmunu      ], kWmunu      );
  //  histogramStyle(relIso_[kZmumu      ], kZmumu      ); 
  histogramStyle(relIso_[kBackground ], kBackground );
  histogramStyle(relIso_[kBoson      ], kBoson      );

  // ---
  //    create legends depending on the used sample
  // ---

  TLegend *leg0 = new TLegend(0.50, 0.65, 1.00, 0.9);
  TLegend *leg1 = new TLegend(0.35, 0.65, 0.95, 0.9);

 if( whichsample == "pythia10"){    
    // create a legend (in upper right corner)
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("Top-Antitop(Phythia, 10TeV)");
    //  leg0->AddEntry( nHit_[kAll       ] , "inclusive"         , "PL" );
    leg0->AddEntry( nHit_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg0->AddEntry( nHit_[kBackground] , "other decays"      , "PL" );
    leg0->AddEntry( nHit_  [kQCD       ] , "QCD"               , "PL" );
    //  leg0->AddEntry( nHit_  [kWmunu     ] , "Wmunu"             , "PL" );
    //  leg0->AddEntry( nHit_  [kZmumu     ] , "Zmumu"             , "PL" );
    leg0->AddEntry( nHit_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );
    
    // create a legend (in upper center)
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("Top-Antitop(Phythia, 10TeV)");
    //  leg1->AddEntry( nHit_[kAll       ] , "inclusive"         , "PL" );
    leg1->AddEntry( nHit_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg1->AddEntry( nHit_[kBackground] , "other decays"      , "PL" );
    leg1->AddEntry( nHit_[kQCD     ] , "QCD"               , "PL" );
    //  leg1->AddEntry( nHit_  [kWmunu     ] , "Wmunu"             , "PL" );
    //  leg1->AddEntry( nHit_  [kZmumu     ] , "Zmumu"             , "PL" );
    leg1->AddEntry( nHit_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );
  }
  
 if( whichsample == "madgraph10"){

    // create a legend (in upper right corner)
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("Top-Antitop(Madgraph, 10TeV)");
    //  leg0->AddEntry( nHit_[kAll       ] , "inclusive"         , "PL" );
    leg0->AddEntry( nHit_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg0->AddEntry( nHit_[kBackground] , "other decays"      , "PL" );
    leg0->AddEntry( nHit_[kQCD       ] , "QCD (Pythia)"        , "PL" );
    //  leg0->AddEntry( nHit_  [kWmunu     ] , "W+jets"             , "PL" );
    //  leg0->AddEntry( nHit_  [kZmumu     ] , "Z+jets"             , "PL" );
    leg0->AddEntry( nHit_  [kBoson]      , "Wjets + Zjets", "PL"  );
    
    // create a legend (in upper center)
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("Top-Antitop(Madgraph, 10TeV)");
    //  leg1->AddEntry( nHit_[kAll       ] , "inclusive"         , "PL" );
    leg1->AddEntry( nHit_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg1->AddEntry( nHit_[kBackground] , "other decays"      , "PL" );
    leg1->AddEntry( nHit_[kQCD     ] , "QCD (Pythia)"               , "PL" );
    //  leg1->AddEntry( nHit_  [kWmunu     ] , "W+jets"             , "PL" );
    //  leg1->AddEntry( nHit_  [kZmumu     ] , "Z+jets"             , "PL" );
    leg1->AddEntry( nHit_  [kBoson]      , "Wjets + Zjets", "PL"  );
  }

 if( whichsample == "nlo10"){

    // create a legend (in upper right corner)
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("Top-Antitop(Mc@NLO, 10TeV)");
    //  leg0->AddEntry( nHit_[kAll       ] , "inclusive"         , "PL" );
    leg0->AddEntry( nHit_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg0->AddEntry( nHit_[kBackground] , "other decays"      , "PL" );
    leg0->AddEntry( nHit_[kQCD       ] , "QCD (Pythia)"        , "PL" );
    //  leg0->AddEntry( nHit_  [kWmunu     ] , "W+jets (Madgraph)"             , "PL" );
    //  leg0->AddEntry( nHit_  [kZmumu     ] , "Z+jets (Madgraph)"             , "PL" );
    leg0->AddEntry( nHit_  [kBoson]      , "Wjets + Zjets (Madgraph)", "PL"  );
    
    // create a legend (in upper center)
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("Top-Antitop(Mc@NLO, 10TeV)");
    //  leg1->AddEntry( nHit_[kAll       ] , "inclusive"         , "PL" );
    leg1->AddEntry( nHit_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg1->AddEntry( nHit_[kBackground] , "other decays"      , "PL" );
    leg1->AddEntry( nHit_[kQCD     ] , "QCD (Pythia)"               , "PL" );
    //  leg1->AddEntry( nHit_  [kWmunu     ] , "W+jets (Madgraph)"             , "PL" );
    //  leg1->AddEntry( nHit_  [kZmumu     ] , "Z+jets (Madgraph)"             , "PL" );
    leg1->AddEntry( nHit_  [kBoson]      , "Wjets + Zjets (Madgraph)", "PL"  );
  }
 if( whichsample == "pythia7"){

    // create a legend (in upper right corner)
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("Top-Antitop(Phythia, 7TeV)");
    //  leg0->AddEntry( nHit_[kAll       ] , "inclusive"         , "PL" );
    leg0->AddEntry( nHit_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg0->AddEntry( nHit_[kBackground] , "other decays"      , "PL" );
    leg0->AddEntry( nHit_  [kQCD       ] , "QCD"               , "PL" );
    //  leg0->AddEntry( nHit_  [kWmunu     ] , "Wmunu"             , "PL" );
    //  leg0->AddEntry( nHit_  [kZmumu     ] , "Zmumu"             , "PL" );
    leg0->AddEntry( nHit_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );
    
    // create a legend (in upper center)
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("Top-Antitop(Phythia, 7TeV)");
    //  leg1->AddEntry( nHit_[kAll       ] , "inclusive"         , "PL" );
    leg1->AddEntry( nHit_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg1->AddEntry( nHit_[kBackground] , "other decays"      , "PL" );
    leg1->AddEntry( nHit_[kQCD     ] , "QCD"               , "PL" );
    //  leg1->AddEntry( nHit_  [kWmunu     ] , "Wmunu"             , "PL" );
    //  leg1->AddEntry( nHit_  [kZmumu     ] , "Zmumu"             , "PL" );
    leg1->AddEntry( nHit_  [kBoson]      , "W#mu#nu + Z#mu#mu", "PL"  );
  }
  
 if( whichsample == "madgraph7"){

    // create a legend (in upper right corner)
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("Top-Antitop(Madgraph, 7TeV)");
    //  leg0->AddEntry( nHit_[kAll       ] , "inclusive"         , "PL" );
    leg0->AddEntry( nHit_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg0->AddEntry( nHit_[kBackground] , "other decays"      , "PL" );
    leg0->AddEntry( nHit_[kQCD       ] , "QCD (Pythia)"        , "PL" );
    //  leg0->AddEntry( nHit_  [kWmunu     ] , "W+jets"             , "PL" );
    //  leg0->AddEntry( nHit_  [kZmumu     ] , "Z+jets"             , "PL" );
    leg0->AddEntry( nHit_  [kBoson]      , "Wjets + Zjets", "PL"  );
    
    // create a legend (in upper center)
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("Top-Antitop(Madgraph, 7TeV)");
    //  leg1->AddEntry( nHit_[kAll       ] , "inclusive"         , "PL" );
    leg1->AddEntry( nHit_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg1->AddEntry( nHit_[kBackground] , "other decays"      , "PL" );
    leg1->AddEntry( nHit_[kQCD     ] , "QCD (Pythia)"               , "PL" );
    //  leg1->AddEntry( nHit_  [kWmunu     ] , "W+jets"             , "PL" );
    //  leg1->AddEntry( nHit_  [kZmumu     ] , "Z+jets"             , "PL" );
    leg1->AddEntry( nHit_  [kBoson]      , "Wjets + Zjets", "PL"  );
  }

 if( whichsample == "nlo7"){

    // create a legend (in upper right corner)
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("Top-Antitop(Mc@NLO, 7TeV)");
    //  leg0->AddEntry( nHit_[kAll       ] , "inclusive"         , "PL" );
    leg0->AddEntry( nHit_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg0->AddEntry( nHit_[kBackground] , "other decays"      , "PL" );
    leg0->AddEntry( nHit_[kQCD       ] , "QCD (Pythia)"        , "PL" );
    //  leg0->AddEntry( nHit_  [kWmunu     ] , "W+jets (Madgraph)"             , "PL" );
    //  leg0->AddEntry( nHit_  [kZmumu     ] , "Z+jets (Madgraph)"             , "PL" );
    leg0->AddEntry( nHit_  [kBoson]      , "Wjets + Zjets (Madgraph)", "PL"  );
    
    // create a legend (in upper center)
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("Top-Antitop(Mc@NLO, 7TeV)");
    //  leg1->AddEntry( nHit_[kAll       ] , "inclusive"         , "PL" );
    leg1->AddEntry( nHit_[kSignal    ] , "semi-lep. ( #mu )" , "PL" );
    leg1->AddEntry( nHit_[kBackground] , "other decays"      , "PL" );
    leg1->AddEntry( nHit_[kQCD     ] , "QCD (Pythia)"               , "PL" );
    //  leg1->AddEntry( nHit_  [kWmunu     ] , "W+jets (Madgraph)"             , "PL" );
    //  leg1->AddEntry( nHit_  [kZmumu     ] , "Z+jets (Madgraph)"             , "PL" );
    leg1->AddEntry( nHit_  [kBoson]      , "Wjets + Zjets (Madgraph)", "PL"  );
  }

  // create an info legend containig the used mu-collection
   TLegend *leg2 = new TLegend(0.228, 0.912, 0.7818, 0.997);
  leg2->SetFillStyle(3001);
  leg2->SetBorderSize(0);
  leg2->SetHeader(whichMuons+" #mu");
 
  // create legends containig the used mu-collections for default configuration
  TLegend *leg3 = new TLegend(0.228, 0.912, 0.7818, 0.997);
  leg3->SetFillStyle(3001);
  leg3->SetBorderSize(0);
  leg3->SetHeader("trigger  #mu");
    
  TLegend *leg4 = new TLegend(0.228, 0.912, 0.7818, 0.997);
  leg4->SetFillStyle(3001);
  leg4->SetBorderSize(0);
  leg4->SetHeader("good  #mu");

  TLegend *leg5 = new TLegend(0.228, 0.912, 0.7818, 0.997);
  leg5->SetFillStyle(3001);
  leg5->SetBorderSize(0);
  leg5->SetHeader("golden  #mu");

  // ---
  //    do the printing for nHit_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(canv0);

  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  canv0->SetTitle("TrackerHits leading " +whichMuons+" #mu");
  axesStyle(nHit_  [kSignal], "N_{Hits trk}( lead #mu )", "events");
  double max=nHit_[kSignal]->GetMaximum();
  if(max<nHit_[kQCD       ]->GetMaximum())max=nHit_[kQCD]       ->GetMaximum();
  if(max<nHit_[kBackground]->GetMaximum())max=nHit_[kBackground]->GetMaximum();
  if(max<nHit_[kBoson     ]->GetMaximum())max=nHit_[kBoson     ]->GetMaximum();
  nHit_  [kSignal    ]->SetMaximum( 10000.0* max );
  nHit_  [kSignal    ]->SetMinimum(1.);
  nHit_  [kSignal    ]->Draw();
  nHit_  [kBackground]->Draw("same");
  nHit_  [kQCD       ]->Draw("same");
  nHit_  [kBoson     ]->Draw("same");
  //  nHit_  [kWmunu ]->Draw("same");
  //  nHit_  [kZmumu ]->Draw("same");
  leg0                ->Draw("same");
  if(whichMuons==""){
    canv0->SetTitle("TrackerHits leading trigger #mu");
    leg3->Draw("same");
  }
  else{
    leg2->Draw("same");
  }
  drawcutline(10.5,0.4* max);

  // ---
  //    do the printing for chi2_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetLogy(1);
  canv1->SetTitle("#chi^{2} leading "+whichMuons+" #mu");
  axesStyle(chi2_ [kSignal], "#chi^{2} ( lead #mu ) [GeV]", "events");
  max=chi2_[kSignal]       ->GetMaximum();
  if(max<chi2_[kQCD       ]->GetMaximum())max=chi2_[kQCD]       ->GetMaximum();
  if(max<chi2_[kBackground]->GetMaximum())max=chi2_[kBackground]->GetMaximum();
  if(max<chi2_[kBoson     ]->GetMaximum())max=chi2_[kZmumu]     ->GetMaximum();
  chi2_ [kSignal    ]->SetMaximum( 1.7* max );
  chi2_ [kSignal    ]->SetMinimum(1.);
  chi2_ [kSignal    ]->Draw();
  chi2_ [kBackground]->Draw("same");
  chi2_ [kQCD       ]->Draw("same");
  chi2_ [kBoson     ]->Draw("same");
  //  chi2_ [kWmunu ]->Draw("same");
  //  chi2_ [kZmumu ]->Draw("same");
  leg0                   ->Draw("same");
  if(whichMuons==""){
    canv1->SetTitle("#chi^{2} leading trigger #mu");
    leg3->Draw("same");
  }
  else{
    leg2->Draw("same");
  }
    drawcutline(10., 0.6*max);

  // ---
  //    do the printing for d0_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetLogy(1);
  canv2->SetTitle("d_{B} leading "+whichMuons+" #mu");
  axesStyle(d0_[kSignal], "d_{B} ( lead #mu )", "events");
   d0_[kSignal]->SetAxisRange(0.,0.1 ,"X");
  max=d0_[kSignal]       ->GetMaximum();
  if(max<d0_[kQCD]       ->GetMaximum())max=d0_[kQCD]       ->GetMaximum();
  if(max<d0_[kBackground]->GetMaximum())max=d0_[kBackground]->GetMaximum();
  if(max<d0_[kBoson]     ->GetMaximum())max=d0_[kBoson]     ->GetMaximum();
  d0_[kSignal    ]->SetMaximum( 10* max );
  d0_[kSignal    ]->SetMinimum( 1 );
  d0_[kSignal    ]->Draw();
  d0_[kBackground]->Draw("same");
  d0_[kQCD       ]->Draw("same");
  d0_[kBoson     ]->Draw("same");
  //  d0_[kWmunu ]->Draw("same");
  //  d0_[kZmumu ]->Draw("same");
  leg0            ->Draw("same");
  if(whichMuons==""){
    canv2->SetTitle("d_{B} leading trigger #mu");
    leg3->Draw("same");
  }
  else{
    leg2->Draw("same");
  }
  drawcutline(0.02, max);

  // ---
  //    do the printing for ecalEn_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(canv3);

  // draw canvas
  canv3->cd(0);
  canv3->SetLogy(1);
  canv3->SetTitle("Ecaldeposit leading "+whichMuons+" #mu");
  axesStyle(ecalEn_[kSignal], "E_{Cal} Energy Deposit ( lead #mu ) [GeV]", "events");
  max=ecalEn_[kSignal   ]->GetMaximum();
  if(max<ecalEn_[kQCD        ]->GetMaximum())max=ecalEn_[kQCD       ]->GetMaximum();
  if(max<ecalEn_[kBackground ]->GetMaximum())max=ecalEn_[kBackground]->GetMaximum();
  if(max<ecalEn_[kBoson      ]->GetMaximum())max=ecalEn_[kBoson     ]->GetMaximum();
  ecalEn_[kSignal    ]->SetMaximum( 20.0* max );
  ecalEn_[kSignal    ]->SetMinimum( 1 );
  ecalEn_[kSignal    ]->Draw();
  ecalEn_[kBackground]->Draw("same");
  ecalEn_[kQCD       ]->Draw("same");
  ecalEn_[kBoson     ]->Draw("same");
  //  ecalEn_[kWmunu ]->Draw("same");
  //  ecalEn_[kZmumu ]->Draw("same");
  leg0                ->Draw("same");
  if(whichMuons==""){
    canv3->SetTitle("Ecaldeposit leading good #mu");
    leg4->Draw("same");
  }
  else{
    leg2->Draw("same");
  }
  drawcutline(4., 0.8*max);

  // ---
  //    do the printing for hcalEn_
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(canv4);

  // draw canvas
  canv4->cd(0);
  canv4->SetLogy(1);
  canv4->SetTitle("Hcaldeposit leading "+whichMuons+" #mu");  
  axesStyle(hcalEn_[kSignal], "H_{Cal} Energy Deposit ( lead #mu ) [GeV]", "events");
  hcalEn_[kSignal       ]->SetMinimum( 1 );
  max=hcalEn_[kSignal  ]->GetMaximum();
  if(max<hcalEn_[kQCD       ]->GetMaximum())max=hcalEn_[kQCD       ]->GetMaximum();
  if(max<hcalEn_[kBackground]->GetMaximum())max=hcalEn_[kBackground]->GetMaximum();
  if(max<hcalEn_[kBoson     ]->GetMaximum())max=hcalEn_[kBoson     ]->GetMaximum();
  hcalEn_[kSignal    ]->SetMaximum( 200.0* max );
  hcalEn_[kSignal    ]->Draw();
  hcalEn_[kBackground]->Draw("same");
  hcalEn_[kQCD       ]->Draw("same");
  hcalEn_[kBoson     ]->Draw("same");
  //  hcalEn_[kWmunu ]->Draw("same");
  //  hcalEn_[kZmumu ]->Draw("same");
  leg0                ->Draw("same");
  if(whichMuons==""){
    canv4->SetTitle("Hcaldeposit leading good #mu");
    leg4->Draw("same");
  }
  else{
    leg2->Draw("same");
  }
  drawcutline(6., 0.2*max);

  // ---
  //    do the printing for relIso_
  // ---
  TCanvas* canv5 = new TCanvas("canv5", "canv5", 600, 600); canvasStyle(canv5);

  // draw canvas
  canv5->cd(0);
  canv5->SetLogy(1);
  canv5->SetTitle("relIso leading "+whichMuons+" #mu");  
  axesStyle(relIso_[kSignal], "relIso ( lead #mu )", "events");
  max=relIso_[kSignal  ]->GetMaximum();
  if(max<relIso_[kQCD       ]->GetMaximum())max=relIso_[kQCD       ]->GetMaximum();
  if(max<relIso_[kBackground]->GetMaximum())max=relIso_[kBackground]->GetMaximum();
  if(max<relIso_[kBoson     ]->GetMaximum())max=relIso_[kBoson     ]->GetMaximum();
  relIso_[kSignal    ]->SetMaximum( 200.0* max );
  relIso_[kSignal    ]->SetMinimum( 1 );
  relIso_[kSignal    ]->Draw();
  relIso_[kBackground]->Draw("same");
  relIso_[kQCD       ]->Draw("same");
  relIso_[kBoson     ]->Draw("same");
  //  relIso_[kWmunu     ]->Draw("same");
  //  relIso_[kZmumu     ]->Draw("same");
  leg0                ->Draw("same");
  if(whichMuons==""){
    canv5->SetTitle("relIso leading golden #mu");
    leg5->Draw("same");
    drawcutline(0.05, 10.0*max);
  }
  else{
    leg2->Draw("same");
  }

  // ---
  //    do the printing for dz_
  // ---
  TCanvas* canv6 = new TCanvas("canv6", "canv6", 600, 600); canvasStyle(canv6);

  // draw canvas
  canv6->cd(0);
  canv6->SetLogy(1);
  canv6->SetTitle("d_{z} leading "+whichMuons+" mu");
  axesStyle(dz_[kSignal], "d_{z} ( #mu )", "events");
   dz_[kSignal]->SetAxisRange(-15.,15 ,"X");
  max=dz_[kSignal]       ->GetMaximum();
  if(max<dz_[kQCD]       ->GetMaximum())max=dz_[kQCD]       ->GetMaximum();
  if(max<dz_[kBackground]->GetMaximum())max=dz_[kBackground]->GetMaximum();
  if(max<dz_[kBoson]     ->GetMaximum())max=dz_[kBoson]     ->GetMaximum();
  dz_[kSignal    ]->SetMaximum( 1000* max );
  dz_[kSignal    ]->SetMinimum( 1 );
  dz_[kSignal    ]->Draw();
  dz_[kBackground]->Draw("same");
  dz_[kQCD       ]->Draw("same");
  dz_[kBoson     ]->Draw("same");
  //  dz_[kWmunu ]->Draw("same");
  //  dz_[kZmumu ]->Draw("same");
  leg0            ->Draw("same");
  if(whichMuons==""){
    canv5->SetTitle("dz leading trigger #mu");
    leg3->Draw("same");
  }
  else{
    leg2->Draw("same");
  }

  // ---
  // saving
  // ---





  if(whichMuons==""){
    
    //  pictures
    canv0->Print("./analyzeMuonCutflow/trackerHitstriggerMuons"+whichsample+".png");
    canv1->Print("./analyzeMuonCutflow/chi2triggerMuons"+whichsample+".png"       );
    canv2->Print("./analyzeMuonCutflow/dBtriggerMuons"+whichsample+".png"         );
    canv6->Print("./analyzeMuonCutflow/dztriggerMuons"+whichsample+".png"         );
    canv3->Print("./analyzeMuonCutflow/eCalEnDepositgoodMuons"+whichsample+".png" );
    canv4->Print("./analyzeMuonCutflow/hCalEnDepositgoodMuons"+whichsample+".png" );
    canv5->Print("./analyzeMuonCutflow/relIsogoldenMuons"+whichsample+".png"      );
     
     //  psfile
    canv0->Print("./analyzeMuonCutflow/SelectionVariablesOfMuonsBeforeCutApplied"+whichsample+".ps(");
    canv1->Print("./analyzeMuonCutflow/SelectionVariablesOfMuonsBeforeCutApplied"+whichsample+".ps" );
    canv2->Print("./analyzeMuonCutflow/SelectionVariablesOfMuonsBeforeCutApplied"+whichsample+".ps" );
    canv6->Print("./analyzeMuonCutflow/SelectionVariablesOfMuonsBeforeCutApplied"+whichsample+".ps" );
    canv3->Print("./analyzeMuonCutflow/SelectionVariablesOfMuonsBeforeCutApplied"+whichsample+".ps" );
    canv4->Print("./analyzeMuonCutflow/SelectionVariablesOfMuonsBeforeCutApplied"+whichsample+".ps" );
    canv5->Print("./analyzeMuonCutflow/SelectionVariablesOfMuonsBeforeCutApplied"+whichsample+".ps)");

  }
  
  else{
    
    //  pictures
    canv0->Print("./analyzeMuonCutflow/trackerHits"+whichMuons+"Muons"+whichsample+".png"  );
    canv1->Print("./analyzeMuonCutflow/chi2"+whichMuons+"Muons"+whichsample+".png"         );
    canv2->Print("./analyzeMuonCutflow/dB"+whichMuons+"Muons"+whichsample+".png"           );
    canv6->Print("./analyzeMuonCutflow/dz"+whichMuons+"Muons"+whichsample+".png"           );
    canv3->Print("./analyzeMuonCutflow/eCalEnDeposit"+whichMuons+"Muons"+whichsample+".png");
    canv4->Print("./analyzeMuonCutflow/hCalEnDeposit"+whichMuons+"Muons"+whichsample+".png");
    canv5->Print("./analyzeMuonCutflow/relIso"+whichMuons+"Muons"+whichsample+".png"       );
    
    //  psfile
    canv0->Print("./analyzeMuonCutflow/Selection"+whichMuons+"Muons"+whichsample+".ps(");
    canv1->Print("./analyzeMuonCutflow/Selection"+whichMuons+"Muons"+whichsample+".ps" );
    canv2->Print("./analyzeMuonCutflow/Selection"+whichMuons+"Muons"+whichsample+".ps" );
    canv6->Print("./analyzeMuonCutflow/Selection"+whichMuons+"Muons"+whichsample+".ps" );
    canv3->Print("./analyzeMuonCutflow/Selection"+whichMuons+"Muons"+whichsample+".ps" );
    canv4->Print("./analyzeMuonCutflow/Selection"+whichMuons+"Muons"+whichsample+".ps" );
    canv5->Print("./analyzeMuonCutflow/Selection"+whichMuons+"Muons"+whichsample+".ps)");
  }

  cout << "you can switch muon collection via whichMuons-TString" << endl;
  cout << "you can look at the plots at different steps of event selection by changing the CutStep-Tstring in the file" << endl;
  cout << "you can change the inputsample via the whichsample-TString in the file (pythia,madgraph,mc@nlo for 7 and 10 TeV)" << endl;

}

void drawcutline(double cutval, double maximum)
{
  TLine *cut = new TLine();
  cut->SetLineWidth(3);
  cut->SetLineStyle(2);
  cut->SetLineColor(2);
  cut->DrawLine(cutval,0.,cutval,maximum);
}

void canvasStyle(TCanvas* canv) 
{
  canv->SetFillStyle   ( 4000);
  canv->SetLeftMargin  ( 0.20);
  canv->SetRightMargin ( 0.05);
  canv->SetBottomMargin( 0.15);
  canv->SetTopMargin   ( 0.05);
}

void histogramStyle(TH1* hist, unsigned int style) 
{
  // pre-defined line style
  std::vector<int> color;
  color.push_back( kRed   ); 
  color.push_back( kRed   ); 
  color.push_back( kBlue  );
  color.push_back( kGreen );
  color.push_back(   5    );
  color.push_back(  46    );
  color.push_back( kBlack );

  // pre-defined fill style
  std::vector<int> fill;
  fill.push_back( 1   ); 
  fill.push_back( 3004); 
  fill.push_back( 1   );
  fill.push_back( 1   );
  fill.push_back( 1   );
  fill.push_back( 1   );
  fill.push_back( 1   );

  // pre-defined marker style
  std::vector<int> marker;
  marker.push_back( 20);

  // set line width
  style==kSignal ? hist->SetLineWidth(6) : hist->SetLineWidth(3);
  
  hist->SetStats(kFALSE);
  hist->SetLineColor  (color[style]);
  hist->SetFillColor  (color[style]);
  hist->SetMarkerColor(color[style]);
  hist->SetFillStyle  (fill [style]);

  if(style==kSignal){
    hist->SetMarkerStyle(marker[style]);
    hist->SetMarkerSize(1.4);
  }
}

void axesStyle(TH1* hist, const char* titleX, const char* titleY) 
{
  hist->SetTitle("");

  hist->GetXaxis()->SetTitle(titleX);
  hist->GetXaxis()->CenterTitle();
  hist->GetXaxis()->SetTitleSize  ( 0.05);
  hist->GetXaxis()->SetTitleColor (    1);
  hist->GetXaxis()->SetTitleOffset(  1.0);
  hist->GetXaxis()->SetTitleFont  (   62);
  hist->GetXaxis()->SetLabelSize  ( 0.05);
  hist->GetXaxis()->SetLabelFont  (   62);
  hist->GetXaxis()->SetNdivisions (  505);
  
  hist->GetYaxis()->SetTitle(titleY);
  hist->GetYaxis()->SetTitleSize  ( 0.07);
  hist->GetYaxis()->SetTitleColor (    1);
  hist->GetYaxis()->SetTitleOffset(  1.2);
  hist->GetYaxis()->SetTitleFont  (   62);
  hist->GetYaxis()->SetLabelSize  ( 0.04);
  hist->GetYaxis()->SetLabelFont  (   62);
  hist->GetYaxis()->CenterTitle   ( true);
}
