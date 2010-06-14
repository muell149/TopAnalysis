#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TPaveLabel.h>

///////////////////////////////////////////////////////////////////////////////////////////
////  This Macro analyzes all cut variables:number of valid Trackerhits, chi^2, dB,    ////
////  energy deposit in ecal and hcal, pt and eta, relIso and the multiplicity of the  //// 
////  final muon collection. This is done within ttbar(semilept.mu + others), w+jets,  ////
////  z+jets and QCD-sample.                                                           ////
////  In default configuration each plot is done before the corresponding cut is       ////
////  applied. Event weights for a normalization concerning luminosity have to be      ////
////  filled in by hand.                                                               ////
///////////////////////////////////////////////////////////////////////////////////////////

enum styles {kSignal, kBackground, kWjets, kZjets, kQCD};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.07, float yTitleOffset=1.2);
void drawcutline(double cutval, double maximum);
double maximum(std::vector<TH1F*> histos_);

void analyzeMuonCuts(TString whichMuons = "", TString whichJets = "")  //  "golden" // "tight" // "loose" // "track" // "good" // "combined" // "unselected"
{
  // ---
  //    set root style 
  // ---

  gROOT->cd();
  gROOT->SetStyle("Plain");

  // choose whether you want to save (every plot as png and all within one ps file)
  bool save = false;
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/cutMonitoring/";
  // choose luminosity for scaling of event numbers and for legend as entry
  int luminosity = 50;
  TString lum = "50";
  // choose "cutflow" or "N-1" for the plots you want to see
  TString plots = "cutflow";

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/spring10Samples/spring10SelV2Sync";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigNloSpring10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgNloSpring10.root"    ) );
//   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigMadSpring10.root"    ) );
//   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgMadSpring10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecWjetsMadSpring10.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecZjetsMadSpring10.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecQCDPythiaSpring10.root" ) );

  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;
  // add scaling factors here!

  // 7 TeV Monte Carlo spring 10 samples
  // -----------------------------------
  // for current ttbar(lept.mu on gen level) Mc@Nlo 
  lumiweight.push_back(0.00831910/50.0*(double)luminosity);
  // for current ttbar(non lept.mu on gen level) Mc@Nlo
  lumiweight.push_back(0.00831910/50.0*(double)luminosity);
//   // for current ttbar(lept.mu on gen level) Madgraph 
//   lumiweight.push_back(0.00556153/50.0*(double)luminosity);
//   // for current ttbar(non lept.mu on gen level) Madraph
//   lumiweight.push_back(0.00556153/50.0*(double)luminosity);
  // for current W+jets MADGRAPH sample
  lumiweight.push_back(0.13904207/50.0*(double)luminosity);
  // for current Z+jets MADGRAPH sample
  lumiweight.push_back(0.14332841/50.0*(double)luminosity);
  // for current QCD PYTHIA sample
  lumiweight.push_back(1.25483558/50.0*(double)luminosity);

  // ---
  //    get histograms
  // ---
  std::vector<TString> thoseCollections;
  if(whichMuons != ""){
    for(int i=0; i<6; i++){
      thoseCollections.push_back(whichMuons);
    }
  }
  else{
    // N-1
    if(plots=="N-1"){
      thoseCollections.push_back("noPt"  );
      thoseCollections.push_back("noEta" );
      thoseCollections.push_back("noTrkHits");
      thoseCollections.push_back("noChi2");
      thoseCollections.push_back("noDb"  );   
      thoseCollections.push_back("tight" );
      thoseCollections.push_back("tight" );
      thoseCollections.push_back("tight" );
      thoseCollections.push_back("noDR"  );
      thoseCollections.push_back("noIso" );
      thoseCollections.push_back("tight" );
    }
    if(plots=="cutflow"){
      // cutflow
      thoseCollections.push_back("combined");
      thoseCollections.push_back("combined");
      thoseCollections.push_back("trigger" );
      thoseCollections.push_back("trigger" );
      thoseCollections.push_back("trigger" );   
      thoseCollections.push_back("tight"   );
      thoseCollections.push_back("tight"   );
      thoseCollections.push_back("tight"   );
      thoseCollections.push_back("good"    );
      thoseCollections.push_back("golden"  );
      thoseCollections.push_back("tight"   );
    }
  }
  if(whichJets != ""){
    for(int i=0; i<2; i++){
      thoseCollections.push_back(whichJets);
    }
  }
  else{
    // N-1
    if(plots=="N-1"){
      thoseCollections.push_back("noEta");
      thoseCollections.push_back("noPt");
      thoseCollections.push_back("noEm");
      thoseCollections.push_back("nofHPD");
      thoseCollections.push_back("noN90Hits");
      thoseCollections.push_back("tight");
      thoseCollections.push_back("tight");
      thoseCollections.push_back("bottom");
    }
    if(plots=="cutflow"){
      // cutflow
      thoseCollections.push_back("pat");
      thoseCollections.push_back("central");
      thoseCollections.push_back("reliable");
      thoseCollections.push_back("reliable");
      thoseCollections.push_back("reliable");
      thoseCollections.push_back("tight");
      thoseCollections.push_back("tight");
      thoseCollections.push_back("bottom");
    }
  }

  std::vector<TH1F*> pt_, eta_, nHit_, chi2_, d0_, dz_, ecalEn_, hcalEn_, dR_, relIso_, n_;
  std::vector<TH1F*> etaJets_, ptlead1Jet_, ptlead2Jet_, ptlead3Jet_, ptlead4Jet_, emf_ , fhpd_, n90hits_, nJets_;
  std::vector<TH1F*> bdiscr_, nbJets_;
  std::vector<TH1F*> nVetoMu_, nVetoE_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    // muon plots
    pt_    .push_back( (TH1F*)files_[idx]->Get(thoseCollections[0]+"MuonKinematics/pt" )->Clone() );
    eta_   .push_back( (TH1F*)files_[idx]->Get(thoseCollections[1]+"MuonKinematics/eta")->Clone() );
    nHit_  .push_back( (TH1F*)files_[idx]->Get(thoseCollections[2]+"MuonQuality/nHit"  )->Clone() );
    chi2_  .push_back( (TH1F*)files_[idx]->Get(thoseCollections[3]+"MuonQuality/chi2"  )->Clone() );
    d0_    .push_back( (TH1F*)files_[idx]->Get(thoseCollections[4]+"MuonQuality/dB"    )->Clone() );
    dz_    .push_back( (TH1F*)files_[idx]->Get(thoseCollections[5]+"MuonQuality/dz"    )->Clone() );
    ecalEn_.push_back( (TH1F*)files_[idx]->Get(thoseCollections[6]+"MuonQuality/ecalEn")->Clone() );
    hcalEn_.push_back( (TH1F*)files_[idx]->Get(thoseCollections[7]+"MuonQuality/hcalEn")->Clone() );
    dR_    .push_back( (TH1F*)files_[idx]->Get(thoseCollections[8]+"MuonVetoJetsKinematics/dist30_")->Clone() );
    relIso_.push_back( (TH1F*)files_[idx]->Get(thoseCollections[9]+"MuonQuality/relIso")->Clone() );
    n_     .push_back( (TH1F*)files_[idx]->Get(thoseCollections[10]+"MuonKinematics/n" )->Clone() );
    // jet plots
    etaJets_   .push_back( (TH1F*)files_[idx]->Get(thoseCollections[11]+"JetKinematics/eta")->Clone() );
    ptlead1Jet_.push_back( (TH1F*)files_[idx]->Get(thoseCollections[12]+"Lead_0_JetKinematics/pt")->Clone() );
    ptlead2Jet_.push_back( (TH1F*)files_[idx]->Get(thoseCollections[12]+"Lead_1_JetKinematics/pt")->Clone() );
    ptlead3Jet_.push_back( (TH1F*)files_[idx]->Get(thoseCollections[12]+"Lead_2_JetKinematics/pt")->Clone() );
    ptlead4Jet_.push_back( (TH1F*)files_[idx]->Get(thoseCollections[12]+"Lead_3_JetKinematics/pt")->Clone() );
    emf_       .push_back( (TH1F*)files_[idx]->Get(thoseCollections[13]+"JetQuality/emf"    )->Clone() );
    fhpd_      .push_back( (TH1F*)files_[idx]->Get(thoseCollections[14]+"JetQuality/fHPD_"   )->Clone() );
    n90hits_   .push_back( (TH1F*)files_[idx]->Get(thoseCollections[15]+"JetQuality/n90Hits_")->Clone() );
    nJets_     .push_back( (TH1F*)files_[idx]->Get(thoseCollections[16]+"JetKinematics/n")->Clone() );
    bdiscr_    .push_back( (TH1F*)files_[idx]->Get(thoseCollections[17]+"JetQuality/btagTrkCntHighPurity")->Clone() );
    nbJets_    .push_back( (TH1F*)files_[idx]->Get(thoseCollections[18]+"JetKinematics/n")->Clone() );
    // veto collection plots
    nVetoMu_.push_back( (TH1F*)files_[idx]->Get("looseVetoMuonKinematics/n"    )->Clone() );
    nVetoE_ .push_back( (TH1F*)files_[idx]->Get("looseVetoElectronKinematics/n")->Clone() );
  }

  // ---
  // Normalization
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    pt_    [idx]->Scale(lumiweight[idx]);
    eta_   [idx]->Scale(lumiweight[idx]);
    nHit_  [idx]->Scale(lumiweight[idx]);
    chi2_  [idx]->Scale(lumiweight[idx]);
    d0_    [idx]->Scale(lumiweight[idx]);
    dz_    [idx]->Scale(lumiweight[idx]);
    ecalEn_[idx]->Scale(lumiweight[idx]);
    hcalEn_[idx]->Scale(lumiweight[idx]);
    dR_    [idx]->Scale(lumiweight[idx]);
    relIso_[idx]->Scale(lumiweight[idx]);
    n_     [idx]->Scale(lumiweight[idx]);
    etaJets_   [idx]->Scale(lumiweight[idx]);
    ptlead1Jet_[idx]->Scale(lumiweight[idx]);
    ptlead2Jet_[idx]->Scale(lumiweight[idx]);
    ptlead3Jet_[idx]->Scale(lumiweight[idx]);
    ptlead4Jet_[idx]->Scale(lumiweight[idx]);
    emf_       [idx]->Scale(lumiweight[idx]);
    fhpd_      [idx]->Scale(lumiweight[idx]);
    n90hits_   [idx]->Scale(lumiweight[idx]); 
    nJets_     [idx]->Scale(lumiweight[idx]);
    bdiscr_    [idx]->Scale(lumiweight[idx]);
    nbJets_    [idx]->Scale(lumiweight[idx]);
    nVetoMu_ [idx]->Scale(lumiweight[idx]);
    nVetoE_  [idx]->Scale(lumiweight[idx]);
  }

  // ---
  //    configure histogram style
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    //choose colors
    int color =0;
    if(idx==kSignal)     color =kRed  ;
    if(idx==kBackground) color =kBlue ;
    if(idx==kWjets)      color =8     ;
    if(idx==kZjets)      color =6     ;
    if(idx==kQCD  )      color =14    ;
    // choose styling options
    histogramStyle(*pt_     [idx], color);
    histogramStyle(*eta_    [idx], color);
    histogramStyle(*nHit_   [idx], color);
    histogramStyle(*chi2_   [idx], color);
    histogramStyle(*d0_     [idx], color);
    histogramStyle(*dz_     [idx], color);
    histogramStyle(*ecalEn_ [idx], color);
    histogramStyle(*hcalEn_ [idx], color);
    histogramStyle(*dR_     [idx], color);
    histogramStyle(*relIso_ [idx], color);
    histogramStyle(*n_      [idx], color);
    histogramStyle(*etaJets_   [idx], color);
    histogramStyle(*ptlead1Jet_[idx], color);
    histogramStyle(*ptlead2Jet_[idx], color);
    histogramStyle(*ptlead3Jet_[idx], color);
    histogramStyle(*ptlead4Jet_[idx], color);
    histogramStyle(*emf_       [idx], color);
    histogramStyle(*fhpd_      [idx], color);
    histogramStyle(*n90hits_   [idx], color); 
    histogramStyle(*nJets_     [idx], color);
    histogramStyle(*bdiscr_    [idx], color);
    histogramStyle(*nbJets_    [idx], color);
    histogramStyle(*nVetoMu_[idx], color);
    histogramStyle(*nVetoE_ [idx], color);
  }

  // ---
  //    create legends
  // ---

  // samples: in upper right corner  
  //  TLegend *leg0 = new TLegend(0.46, 0.65, 0.96, 0.90);
  TLegend *leg0 = new TLegend(0.08, 0.19, 0.94, 0.88);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("MC "+lum+" pb^{-1} @7TeV");
  leg0->AddEntry( nHit_  [kSignal    ] , "ttbar s.lep.(#mu) MC@NLO", "L" );
  leg0->AddEntry( nHit_  [kBackground] , "ttbar other MC@NLO"           , "L" );
  leg0->AddEntry( nHit_  [kQCD       ] , "QCD PYTHIA"                   , "L" );
  leg0->AddEntry( nHit_  [kWjets     ] , "W+jets MADGRAPH"              , "L" );
  leg0->AddEntry( nHit_  [kZjets     ] , "Z+jets MADGRAPH"              , "L" );

  // samples: in upper center
  TLegend *leg1 = new TLegend(0.35, 0.65, 0.95, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("MC "+lum+" pb^{-1} @7TeV");
  leg1->AddEntry( nHit_  [kSignal    ] , "ttbar semi-lep.( #mu ) MC@NLO", "L" );
  leg1->AddEntry( nHit_  [kBackground] , "ttbar other MC@NLO"           , "L" );
  leg1->AddEntry( nHit_  [kQCD       ] , "QCD PYTHIA"                   , "L" );
  leg1->AddEntry( nHit_  [kWjets     ] , "W+jets MADGRAPH"              , "L" );
  leg1->AddEntry( nHit_  [kZjets     ] , "Z+jets MADGRAPH"              , "L" );  

  // containig the used mu-collection
  TLegend *leg2 = new TLegend(0.228, 0.912, 0.7818, 0.997);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  TLegend *leg3 = (TLegend*)(leg2->Clone());
  TLegend *leg4 = (TLegend*)(leg2->Clone());
  TLegend *leg5 = (TLegend*)(leg2->Clone());
  TLegend *leg6 = (TLegend*)(leg2->Clone());
  TLegend *leg7 = (TLegend*)(leg2->Clone());
  TLegend *leg8 = (TLegend*)(leg2->Clone());
  TLegend *leg9 = (TLegend*)(leg2->Clone());
  TLegend *leg10= (TLegend*)(leg2->Clone());
  TLegend *leg11= (TLegend*)(leg2->Clone());
  TLegend *leg12= (TLegend*)(leg2->Clone());
  TLegend *leg13= (TLegend*)(leg2->Clone());
  TLegend *leg14= (TLegend*)(leg2->Clone());
  TLegend *leg15= (TLegend*)(leg2->Clone());
  TLegend *leg16= (TLegend*)(leg2->Clone());
  TLegend *leg17= (TLegend*)(leg2->Clone());
  TLegend *leg18= (TLegend*)(leg2->Clone());
  TLegend *leg19= (TLegend*)(leg2->Clone());
  TLegend *leg20= (TLegend*)(leg2->Clone());
  TLegend *leg21= (TLegend*)(leg2->Clone());
  TLegend *leg22= (TLegend*)(leg2->Clone());
  leg2 ->SetHeader(""+thoseCollections[0]+" muons");
  leg3 ->SetHeader(""+thoseCollections[1]+" muons");
  leg4 ->SetHeader(""+thoseCollections[2]+" muons");
  leg5 ->SetHeader(""+thoseCollections[3]+" muons");
  leg6 ->SetHeader(""+thoseCollections[4]+" muons");
  leg7 ->SetHeader(""+thoseCollections[5]+" muons");
  leg8 ->SetHeader(""+thoseCollections[6]+" muons");
  leg9 ->SetHeader(""+thoseCollections[7]+" muons");
  leg10->SetHeader(""+thoseCollections[8]+" muons");
  leg11->SetHeader(""+thoseCollections[9]+" muons");
  leg12->SetHeader(""+thoseCollections[10]+" muons");
  leg13->SetHeader("leading "+thoseCollections[11]+" jets");
  leg14->SetHeader("leading "+thoseCollections[12]+" jets");
  leg15->SetHeader("leading "+thoseCollections[13]+" jets");
  leg18->SetHeader("leading "+thoseCollections[14]+" jets");
  leg19->SetHeader("leading "+thoseCollections[15]+" jets");
  leg20->SetHeader(thoseCollections[16]+" jets");
  leg21->SetHeader("leading "+thoseCollections[17]+" jets");
  leg22->SetHeader(thoseCollections[18]+" jets");
  leg16->SetHeader("looseMuons");
  leg17->SetHeader("looseElectrons");

  // label indicating cutstep
  TPaveLabel *cut0 = new TPaveLabel(0.73, 0.87, 0.9, 1.0, "(hltMu9 ev. sel.)", "br NDC");
  cut0->SetFillStyle(0);
  cut0->SetBorderSize(0);
  cut0->SetTextSize(0.26);
  TPaveLabel *cut1= (TPaveLabel*)(cut0->Clone());
  TPaveLabel *cut2= (TPaveLabel*)(cut0->Clone()); 
  TPaveLabel *cut3= (TPaveLabel*)(cut0->Clone());
  cut1->SetLabel("(#mu ev. sel.)");
  cut2->SetLabel("(#mu & veto ev. sel.)");
  cut3->SetLabel("(#mu & veto & jet ev. sel.)");

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<25; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ---
  //    do the printing for pt_
  // ---
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetLogy(1);
  MyCanvas[0]->SetTitle("ptLeading"+thoseCollections[0]+"MuonsLum"+lum+"pb@7TeV");
  axesStyle(*pt_  [kSignal], "p_{t} ( lead #mu ) [GeV]", "events", 1., 500.0* maximum(pt_) );
  pt_  [kSignal    ]->Draw();
  pt_  [kBackground]->Draw("same");
  pt_  [kQCD       ]->Draw("same");
  pt_  [kWjets     ]->Draw("same");
  pt_  [kZjets     ]->Draw("same");
  //  leg0              ->Draw("same");
  leg2              ->Draw("same");
  cut0              ->Draw("same");
  drawcutline(20.5, 0.01* maximum(pt_));

  // ---
  //    do the printing for eta_
  // ---
  MyCanvas[1]->cd(0);
  MyCanvas[1]->SetLogy(1);
  MyCanvas[1]->SetTitle("etaLeading"+thoseCollections[0]+"MuonsLum"+lum+"pb@7TeV");
  axesStyle(*eta_  [kSignal], "#eta ( lead #mu )", "events", 1., 1000.0* maximum(eta_) );
  eta_  [kSignal    ]->Draw();
  eta_  [kBackground]->Draw("same");
  eta_  [kQCD       ]->Draw("same");
  eta_  [kWjets     ]->Draw("same");
  eta_  [kZjets     ]->Draw("same");
  //  leg0               ->Draw("same");
  leg3               ->Draw("same");
  cut0               ->Draw("same");
  drawcutline(-2.1, 0.001* maximum(eta_));
  drawcutline( 2.1, 0.001* maximum(eta_));

  // ---
  //    do the printing for nHit_
  // ---
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetLogy(1);
  MyCanvas[2]->SetTitle("trackerHitsLeading"+thoseCollections[1]+"MuonsLum"+lum+"pb@7TeV");
  axesStyle(*nHit_  [kSignal], "N_{Hits trk} ( lead #mu )", "events", 1., 500.0* maximum(nHit_) );
  nHit_  [kSignal    ]->Draw();
  nHit_  [kBackground]->Draw("same");
  nHit_  [kQCD       ]->Draw("same");
  nHit_  [kWjets     ]->Draw("same");
  nHit_  [kZjets     ]->Draw("same");
  //  leg1                ->Draw("same");
  leg4                ->Draw("same");
  cut0                ->Draw("same");
  drawcutline(10.5, 0.001* maximum(nHit_));

  // ---
  //    do the printing for chi2_
  // ---
  MyCanvas[3]->cd(0);
  MyCanvas[3]->SetLogy(1);
  MyCanvas[3]->SetTitle("chi2Leading"+thoseCollections[1]+"MuonsLum"+lum+"pb@7TeV");
  axesStyle(*chi2_  [kSignal], "#chi^{2} ( lead #mu )", "events", 0.01,  200.0* maximum(chi2_) );
  chi2_  [kSignal    ]->Draw();
  chi2_  [kBackground]->Draw("same");
  chi2_  [kQCD       ]->Draw("same");
  chi2_  [kWjets     ]->Draw("same");
  chi2_  [kZjets     ]->Draw("same");
  //  leg0                ->Draw("same");
  leg5                ->Draw("same");
  cut0                ->Draw("same");
  drawcutline(10., 0.002* maximum(chi2_));

  // ---
  //    do the printing for d0_
  // ---
  MyCanvas[4]->cd(0);
  MyCanvas[4]->SetLogy(1);
  MyCanvas[4]->SetTitle("dBLeading"+thoseCollections[1]+"MuonsLum"+lum+"pb@7TeV");
  axesStyle(*d0_  [kSignal], "d_{B} ( lead #mu ) [cm]", "events", 0.01, 2000.0* maximum(d0_) );
  d0_  [kSignal    ]->SetAxisRange(0.,0.2 ,"X");
  d0_  [kSignal    ]->Draw();
  d0_  [kBackground]->Draw("same");
  d0_  [kQCD       ]->Draw("same");
  d0_  [kWjets     ]->Draw("same");
  d0_  [kZjets     ]->Draw("same");
  //  leg1              ->Draw("same");
  leg6              ->Draw("same");
  cut0              ->Draw("same");
  drawcutline(0.02, 0.08*maximum(d0_));

  // ---
  //    do the printing for dz_
  // ---
  MyCanvas[5]->cd(0);
  MyCanvas[5]->SetLogy(1);
  MyCanvas[5]->SetTitle("dzLeading"+thoseCollections[1]+"MuonsLum"+lum+"pb@7TeV");
  axesStyle(*dz_  [kSignal], "d_{z} ( lead #mu )", "events", 1., 500.0* maximum(dz_) );
  dz_  [kSignal    ]->SetAxisRange(-20.,20 ,"X");
  dz_  [kSignal    ]->Draw();
  dz_  [kBackground]->Draw("same");
  dz_  [kQCD       ]->Draw("same");
  dz_  [kWjets     ]->Draw("same");
  dz_  [kZjets     ]->Draw("same");
  //  leg0              ->Draw("same");
  leg7              ->Draw("same");
  cut0              ->Draw("same");

  // ---
  //    do the printing for ecalEn_
  // ---
  MyCanvas[6]->cd(0);
  MyCanvas[6]->SetLogy(1);
  MyCanvas[6]->SetTitle("ecalEnLeading"+thoseCollections[3]+"MuonsLum"+lum+"pb@7TeV");
  axesStyle(*ecalEn_  [kSignal], "E_{Ecal} ( lead #mu ) [GeV]", "events" , 0.01, 100.0* maximum(ecalEn_));
  ecalEn_  [kSignal    ]->Draw();
  ecalEn_  [kBackground]->Draw("same");
  ecalEn_  [kQCD       ]->Draw("same");
  ecalEn_  [kWjets     ]->Draw("same");
  ecalEn_  [kZjets     ]->Draw("same");
  //  leg1                  ->Draw("same");
  leg8                  ->Draw("same");
  cut0                  ->Draw("same");
  
  // ---
  //    do the printing for hcalEn_
  // ---
  MyCanvas[7]->cd(0);
  MyCanvas[7]->SetLogy(1);
  MyCanvas[7]->SetTitle("hcalEnLeading"+thoseCollections[3]+"MuonsLum"+lum+"pb@7TeV");
  axesStyle(*hcalEn_  [kSignal], "E_{Hcal} ( lead #mu ) [GeV]", "events", 0.01, 100.0* maximum(hcalEn_) );
  hcalEn_  [kSignal    ]->Draw();
  hcalEn_  [kBackground]->Draw("same");
  hcalEn_  [kQCD       ]->Draw("same");
  hcalEn_  [kWjets     ]->Draw("same");
  hcalEn_  [kZjets     ]->Draw("same");
  //  leg0                  ->Draw("same");
  leg9                  ->Draw("same");
  cut0                  ->Draw("same");

  // ---
  //    do the printing for dR_
  // ---
  MyCanvas[8]->cd(0);
  MyCanvas[8]->SetLogy(1);
  MyCanvas[8]->SetTitle("distance"+thoseCollections[4]+"MuonsVetoJetsLum"+lum+"pb@7TeV");
  axesStyle(*dR_  [kSignal], "dR ( lead #mu )", "events", 1., 50.0* maximum(dR_) );
  dR_  [kSignal    ]->Draw();
  dR_  [kBackground]->Draw("same");
  dR_  [kQCD       ]->Draw("same");
  dR_  [kWjets     ]->Draw("same");
  dR_  [kZjets     ]->Draw("same");
  //  leg1              ->Draw("same");
  leg10             ->Draw("same");
  cut0              ->Draw("same");
  drawcutline(0.3, 0.01*maximum(dR_));

  // ---
  //    do the printing for relIso_
  // ---
  MyCanvas[9]->cd(0);
  MyCanvas[9]->SetLogy(1);
  MyCanvas[9]->SetTitle("relIsoLeading"+thoseCollections[4]+"MuonsLum"+lum+"pb@7TeV");
  axesStyle(*relIso_  [kSignal], "relIso ( lead #mu )", "events", 0.1, 50.0* maximum(relIso_) );
  relIso_  [kSignal    ]->Draw();
  relIso_  [kBackground]->Draw("same");
  relIso_  [kQCD       ]->Draw("same");
  relIso_  [kWjets     ]->Draw("same");
  relIso_  [kZjets     ]->Draw("same");
  //  leg1                  ->Draw("same");
  leg11                 ->Draw("same");
  cut0                  ->Draw("same");
  drawcutline(0.05, 0.1*maximum(relIso_));

  // ---
  //    do the printing for n_
  // ---
  MyCanvas[10]->cd(0);
  MyCanvas[10]->SetLogy(1);
  MyCanvas[10]->SetTitle("multiplicity"+thoseCollections[5]+"MuonsLum"+lum+"pb@7TeV");
  axesStyle(*n_  [kSignal], "multiplicity ( #mu )", "events", 0.01, 1000.0* maximum(n_) );
  n_  [kSignal    ]->SetAxisRange(0.,5.,"X");
  n_  [kSignal    ]->Draw();
  n_  [kBackground]->Draw("same");
  n_  [kQCD       ]->Draw("same");
  n_  [kWjets     ]->Draw("same");
  n_  [kZjets     ]->Draw("same");
  // leg0             ->Draw("same");
  leg12            ->Draw("same");
  cut0             ->Draw("same");
  drawcutline(0.5, 0.01*maximum(n_));
  drawcutline(1.5, 0.01*maximum(n_));

  // ---
  //    do the printing for etaJets_
  // ---
  MyCanvas[11]->cd(0);
  MyCanvas[11]->SetLogy(1);
  MyCanvas[11]->SetTitle("etaAll"+thoseCollections[11]+"JetsLum"+lum+"pb@7TeV");
  axesStyle(*etaJets_  [kSignal], "#eta", "events", 1., 15000.0* maximum(etaJets_) );
  etaJets_  [kSignal    ]->Draw();
  etaJets_  [kBackground]->Draw("same");
  etaJets_  [kQCD       ]->Draw("same");
  etaJets_  [kWjets     ]->Draw("same");
  etaJets_  [kZjets     ]->Draw("same");
  //  leg1                   ->Draw("same");
  leg13                  ->Draw("same");
  //  cut2                   ->Draw("same");
  drawcutline(-2.4, 0.0003*maximum(etaJets_));
  drawcutline( 2.4, 0.0003*maximum(etaJets_));

  // ---
  //    do the printing for ptlead1Jet_
  // ---
  MyCanvas[12]->cd(0);
  MyCanvas[12]->SetLogy(1);
  MyCanvas[12]->SetTitle("ptstLeading"+thoseCollections[12]+"JetLum"+lum+"pb@7TeV");
  axesStyle(*ptlead1Jet_  [kSignal], "p_{t} ( lead jet ) [GeV]", "events", 1., 100.0* maximum(ptlead1Jet_) );
  ptlead1Jet_  [kSignal    ]->Draw();
  ptlead1Jet_  [kBackground]->Draw("same");
  ptlead1Jet_  [kQCD       ]->Draw("same");
  ptlead1Jet_  [kWjets     ]->Draw("same");
  ptlead1Jet_  [kZjets     ]->Draw("same");
  //  leg0                      ->Draw("same");
  leg14                     ->Draw("same");
  cut2                      ->Draw("same");
  drawcutline(30.0, 0.01*maximum(ptlead1Jet_));

  // ---
  //    do the printing for ptlead2Jet_
  // ---
  MyCanvas[13]->cd(0);
  MyCanvas[13]->SetLogy(1);
  MyCanvas[13]->SetTitle("pt2ndLeading"+thoseCollections[12]+"JetLum"+lum+"pb@7TeV");
  axesStyle(*ptlead2Jet_  [kSignal], "p_{t} ( 2^{nd} lead jet ) [GeV]", "events", 0.1, 1000.0* maximum(ptlead2Jet_) );
  ptlead2Jet_  [kSignal    ]->Draw();
  ptlead2Jet_  [kBackground]->Draw("same");
  ptlead2Jet_  [kQCD       ]->Draw("same");
  ptlead2Jet_  [kWjets     ]->Draw("same");
  ptlead2Jet_  [kZjets     ]->Draw("same");
  //  leg0                      ->Draw("same");
  leg14                     ->Draw("same");
  cut2                      ->Draw("same");
  drawcutline(30.0, 0.002*maximum(ptlead2Jet_));

  // ---
  //    do the printing for ptlead3Jet_
  // ---
  MyCanvas[14]->cd(0);
  MyCanvas[14]->SetLogy(1);
  MyCanvas[14]->SetTitle("pt3rdLeading"+thoseCollections[12]+"JetLum"+lum+"pb@7TeV");
  axesStyle(*ptlead3Jet_  [kSignal], "p_{t} ( 3^{rd} lead jet ) [GeV]", "events", 0.1, 100.0* maximum(ptlead3Jet_) );
  ptlead3Jet_  [kSignal    ]->Draw();
  ptlead3Jet_  [kBackground]->Draw("same");
  ptlead3Jet_  [kQCD       ]->Draw("same");
  ptlead3Jet_  [kWjets     ]->Draw("same");
  ptlead3Jet_  [kZjets     ]->Draw("same");
  //  leg0                      ->Draw("same");
  leg14                     ->Draw("same");
  cut2                      ->Draw("same");
  drawcutline(30.0, 0.06*maximum(ptlead3Jet_));

  // ---
  //    do the printing for ptlead4Jet_
  // ---
  MyCanvas[15]->cd(0);
  MyCanvas[15]->SetLogy(1);
  MyCanvas[15]->SetTitle("pt4thLeading"+thoseCollections[12]+"JetLum"+lum+"pb@7TeV");
  axesStyle(*ptlead4Jet_  [kSignal], "p_{t} ( 4^{th} lead jet ) [GeV]", "events", 0.01, 100.0* maximum(ptlead4Jet_) );
  ptlead4Jet_  [kSignal    ]->Draw();
  ptlead4Jet_  [kBackground]->Draw("same");
  ptlead4Jet_  [kQCD       ]->Draw("same");
  ptlead4Jet_  [kWjets     ]->Draw("same");
  ptlead4Jet_  [kZjets     ]->Draw("same");
  //  leg0                      ->Draw("same");
  leg14                     ->Draw("same");
  cut2                      ->Draw("same");
  drawcutline(30.0, 0.005*maximum(ptlead4Jet_));

  // ---
  //    do the printing for emf_
  // ---
  MyCanvas[16]->cd(0);
  MyCanvas[16]->SetLogy(1);
  MyCanvas[16]->SetTitle("electromagneticFraction"+thoseCollections[13]+"JetsLum"+lum+"pb@7TeV");
  axesStyle(*emf_  [kSignal], "electromagnetic fraction", "events", 1., 1000.0* maximum(emf_) );
  emf_  [kSignal    ]->Draw();
  emf_  [kBackground]->Draw("same");
  emf_  [kQCD       ]->Draw("same");
  emf_  [kWjets     ]->Draw("same");
  emf_  [kZjets     ]->Draw("same");
  //  leg0               ->Draw("same");
  leg15              ->Draw("same");
    cut2               ->Draw("same");
  drawcutline(0.95, 0.005*maximum(emf_));

  // ---
  //    do the printing for nVetoMu_
  // ---
  MyCanvas[17]->cd(0);
  MyCanvas[17]->SetLogy(1);
  MyCanvas[17]->SetTitle("multiplicityLooseMuonsLum"+lum+"pb@7TeV");
  axesStyle(*nVetoMu_  [kSignal], "multiplicity ( #mu )", "events", 1., 100.0* maximum(nVetoMu_) );
  nVetoMu_  [kSignal    ]->SetAxisRange(0.,5.,"X");
  nVetoMu_  [kSignal    ]->Draw();
  nVetoMu_  [kBackground]->Draw("same");
  nVetoMu_  [kQCD       ]->Draw("same");
  nVetoMu_  [kWjets     ]->Draw("same");
  nVetoMu_  [kZjets     ]->Draw("same");
  //  leg0                   ->Draw("same");
  leg16                  ->Draw("same");
  cut1                   ->Draw("same");
  drawcutline(0.5, 0.06*maximum(nVetoMu_));
  drawcutline(1.5, 0.06*maximum(nVetoMu_));

  // ---
  //    do the printing for nVetoE_
  // ---
  MyCanvas[18]->cd(0);
  MyCanvas[18]->SetLogy(1);
  MyCanvas[18]->SetTitle("multiplicityLooseElectronsLum"+lum+"pb@7TeV");
  axesStyle(*nVetoE_  [kSignal], "multiplicity ( e )", "events", 1., 100.0* maximum(nVetoE_) );
  nVetoE_  [kSignal    ]->SetAxisRange(0.,5.,"X");
  nVetoE_  [kSignal    ]->Draw();
  nVetoE_  [kBackground]->Draw("same");
  nVetoE_  [kQCD       ]->Draw("same");
  nVetoE_  [kWjets     ]->Draw("same");
  nVetoE_  [kZjets     ]->Draw("same");
  //  leg0                  ->Draw("same");
  leg17                 ->Draw("same");
  cut1                  ->Draw("same");
  drawcutline(0.5, 0.06*maximum(nVetoE_));

  // ---
  //    do the printing for fhpd_
  // ---
  MyCanvas[19]->cd(0);
  MyCanvas[19]->SetLogy(1);
  MyCanvas[19]->SetTitle("fHPD"+thoseCollections[14]+"JetsLum"+lum+"pb@7TeV");
  axesStyle(*fhpd_  [kSignal], "fHPD", "events", 1., 10000.0* maximum(fhpd_) );
  fhpd_[kSignal    ]->Draw();
  fhpd_[kBackground]->Draw("same");
  fhpd_[kQCD       ]->Draw("same");
  fhpd_[kWjets     ]->Draw("same");
  fhpd_[kZjets     ]->Draw("same");
  //  leg0               ->Draw("same");
  leg18              ->Draw("same");
  cut2               ->Draw("same");
  drawcutline(0.98, 0.001*maximum(fhpd_));

  // ---
  //    do the printing for n90hits_
  // ---
  MyCanvas[20]->cd(0);
  //  MyCanvas[20]->SetLogy(1);
  MyCanvas[20]->SetTitle("n90hits"+thoseCollections[15]+"JetsLum"+lum+"pb@7TeV");
  axesStyle(*n90hits_  [kSignal], "n90Hits", "events", 0., 5.0* maximum(n90hits_) );
  n90hits_[kSignal    ]->Draw();
  n90hits_[kBackground]->Draw("same");
  n90hits_[kQCD       ]->Draw("same");
  n90hits_[kWjets     ]->Draw("same");
  n90hits_[kZjets     ]->Draw("same");
  //  leg0               ->Draw("same");
  leg19              ->Draw("same");
  cut2               ->Draw("same");
  drawcutline(1.0, 0.001*maximum(n90hits_));

  // ---
  //    do the printing for nJets_
  // ---
  MyCanvas[21]->cd(0);
  MyCanvas[21]->SetLogy(1);
  MyCanvas[21]->SetTitle("nJets"+thoseCollections[16]+"JetsLum"+lum+"pb@7TeV");
  axesStyle(*nJets_  [kSignal], "jet Multiplicity", "events", 1., 10000.0* maximum(nJets_) );
  nJets_[kSignal    ]->Draw();
  nJets_[kBackground]->Draw("same");
  nJets_[kQCD       ]->Draw("same");
  nJets_[kWjets     ]->Draw("same");
  nJets_[kZjets     ]->Draw("same");
  //  leg0               ->Draw("same");
  leg20              ->Draw("same");
  cut2               ->Draw("same");
  drawcutline(4.0, 0.001*maximum(nJets_));

  // ---
  //    do the printing for bdiscr_
  // ---
  MyCanvas[22]->cd(0);
  MyCanvas[22]->SetLogy(1);
  MyCanvas[22]->SetTitle("bdiscr"+thoseCollections[17]+"JetsLum"+lum+"pb@7TeV");
  axesStyle(*bdiscr_  [kSignal], "b-discr.(trkCountHighPur)", "events", 0.1, 15.0* maximum(bdiscr_) );
  bdiscr_[kSignal    ]->Draw();
  bdiscr_[kBackground]->Draw("same");
  bdiscr_[kQCD       ]->Draw("same");
  bdiscr_[kWjets     ]->Draw("same");
  bdiscr_[kZjets     ]->Draw("same");
  //  leg0               ->Draw("same");
  leg21              ->Draw("same");
  cut3               ->Draw("same");
  drawcutline(2.17, 0.05*maximum(bdiscr_));

  // ---
  //    do the printing for nbJets_
  // ---
  MyCanvas[23]->cd(0);
  MyCanvas[23]->SetLogy(1);
  MyCanvas[23]->SetTitle("nbJets"+thoseCollections[18]+"JetsLum"+lum+"pb@7TeV");
  axesStyle(*nbJets_  [kSignal], "b-jet Multiplicity", "events", 1., 80.0* maximum(nbJets_) );
  nbJets_[kSignal    ]->Draw();
  nbJets_[kBackground]->Draw("same");
  nbJets_[kQCD       ]->Draw("same");
  nbJets_[kWjets     ]->Draw("same");
  nbJets_[kZjets     ]->Draw("same");
  //  leg0               ->Draw("same");
  leg22              ->Draw("same");
  cut3               ->Draw("same");
  drawcutline(1.0, 0.05*maximum(nbJets_));

  // ---
  //    do the printing for common event Selection legend
  // ---
  MyCanvas[24]->cd(0);
  MyCanvas[24]->SetTitle("legendEventSelectionLum"+lum+"pb@7TeV");
  leg0->Draw("");


  // ---
  // saving
  // ---

  if(save){  
    // ps
    MyCanvas[0]->Print(saveTo+"cutMonitoring7TeV"+lum+"pb.ps("  );
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+"cutMonitoring7TeV"+plots+lum+"pb.ps"  );
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+"cutMonitoring7TeV"+lum+"pb.ps)"  );
 
    // png
    for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
      MyCanvas[idx]->Print(saveTo+(TString)(MyCanvas[idx]->GetTitle())+".png"  ); 
    }
  } 
}

void drawcutline(double cutval, double maximum)
{
  TLine *cut = new TLine();
  cut->SetLineWidth(5);
  cut->SetLineStyle(2);
  cut->SetLineColor(1);
  cut->DrawLine(cutval, 0.,cutval, maximum);
}

void canvasStyle(TCanvas& canv) 
{
  canv.SetFillStyle   ( 4000);
  canv.SetLeftMargin  ( 0.20);
  canv.SetRightMargin ( 0.05);
  canv.SetBottomMargin( 0.15);
  canv.SetTopMargin   ( 0.05);
}

double maximum(std::vector<TH1F*> histos_)
{
  double max=histos_[0]->GetMaximum();
  for(unsigned idx=1; idx<histos_.size(); idx++){
    if(max<histos_[idx]->GetMaximum()) max=histos_[idx]->GetMaximum();
  }
  return max;  
}

void histogramStyle(TH1& hist, int color, int lineStyle, int markerStyle, float markersize, int filled) 
{
  hist.SetLineWidth(3);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color);
  hist.SetMarkerColor(color);  
  hist.SetMarkerStyle(markerStyle);
  hist.SetMarkerSize(markersize);
  hist.SetLineStyle(lineStyle);
  if(filled==1){
  hist.SetFillStyle(1001);
  hist.SetFillColor(color);
  }
  else{
    hist.SetFillStyle(0);
  }
}

void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin, float yMax, float yTitleSize, float yTitleOffset) 
{
  hist.SetTitle("");
  hist.GetXaxis()->SetTitle(titleX);
  hist.GetXaxis()->CenterTitle();
  hist.GetXaxis()->SetTitleSize  ( 0.06);
  hist.GetXaxis()->SetTitleColor (    1);
  hist.GetXaxis()->SetTitleOffset(  1.0);
  hist.GetXaxis()->SetTitleFont  (   62);
  hist.GetXaxis()->SetLabelSize  ( 0.05);
  hist.GetXaxis()->SetLabelFont  (   62);
  hist.GetXaxis()->SetNdivisions (  505);
  hist.GetYaxis()->SetTitle(titleY);
  hist.GetYaxis()->SetTitleSize  ( yTitleSize );
  hist.GetYaxis()->SetTitleColor (    1);
  hist.GetYaxis()->SetTitleOffset(yTitleOffset);
  hist.GetYaxis()->SetTitleFont  (   62);
  hist.GetYaxis()->SetLabelSize  ( 0.04);
  hist.GetYaxis()->SetLabelFont  (   62);
  hist.GetYaxis()->CenterTitle   ( true);
  if(yMin!=-123) hist.SetMinimum(yMin);
  if(yMax!=-123) hist.SetMaximum(yMax);
}
