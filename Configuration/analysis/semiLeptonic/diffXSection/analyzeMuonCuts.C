#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <THStack.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TPaveLabel.h>
#include <TStyle.h>
#include <typeinfo>

///////////////////////////////////////////////////////////////////////////////////////////
////  This Macro analyzes all cut variables:number of valid Trackerhits, chi^2, dB,    ////
////  energy deposit in ecal and hcal, pt and eta, relIso and the multiplicity of the  //// 
////  final muon collection. All important jet quantities are also plotted. This is    ////
////  done within ttbar(semilept.mu + others), w+jets, z+jets and QCD-sample.          ////
////  Additionally data points can be filled in for comparism.                         //// 
///////////////////////////////////////////////////////////////////////////////////////////

enum styles {kSignal, kBackground, kZjets, kWjets, kQCD, kData};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0, int fillStyle=1001); 
template <class T>
void axesStyle(T& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.07, float yTitleOffset=1.2);
void drawcutline(double cutval, double maximum);
TPaveLabel* label(TString text="", double xmin=0.38, double ymin=0.79, double xmax=0.56, double ymax=1.0, double size=0.26);
int roundToInt(double value);
TString getTStringFromInt(int i);

void analyzeMuonCuts(double luminosity = 840.0, bool save = false, TString dataFile="./diffXSecFromSignal/data/data1808json/analyzeDiffXData_840nb.root", TString plots = "cutflow")
{
  // ---
  //    main function parameters
  // ---
  // save:       choose whether you want to save every plot as png and all within one ps file
  // textoutput: choose whether you want to save the estimated number of QCD events for data 
  //             in .txt file to share it with other parts of the Analysis
  // luminosity: choose luminosity for scaling of event numbers 
  //             lum is derived from this and used for legend as entry
  TString lum = getTStringFromInt(roundToInt(luminosity));
  // plots:      choosee "cutflow" or "NminusOne" for the plots you want to see 
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/earlyData/";
  if(plots=="cutflow")saveTo+="cutMonitoring/";
  if(plots=="NminusOne")saveTo+="NminusOneDistributions/";

  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0); 
  
  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/spring10Samples/spring10SelV2Sync";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigNloSpring10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgNloSpring10.root"    ) );
  //   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigMadSpring10.root"    ) );
  //   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgMadSpring10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecZjetsMadSpring10.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecWjetsMadSpring10.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecQCDPythiaSpring10.root" ) );
  files_.push_back(new TFile(dataFile                                                             ) );

  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;
  // add scaling factors here!

  // 7 TeV Monte Carlo spring 10 samples
  // -----------------------------------
  // for current ttbar(lept.mu on gen level and other) Mc@Nlo 
  lumiweight.push_back(0.000000159*(double)luminosity);
  lumiweight.push_back(0.000000159*(double)luminosity);
  // for current ttbar(lept.mu on gen level and other) Madgraph 
  //   lumiweight.push_back(0.000000106*(double)luminosity);
  //   lumiweight.push_back(0.000000106*(double)luminosity);
  // for current Z+jets MADGRAPH sample
  lumiweight.push_back(0.000002809*(double)luminosity);
  // for current W+jets MADGRAPH sample
  lumiweight.push_back(0.000003110*(double)luminosity);
  // for current QCD PYTHIA sample
  lumiweight.push_back(0.000018205*(double)luminosity);
  // for data
  lumiweight.push_back(1.0);

  // ---
  //    get histograms
  // ---
  std::vector<TString> thoseCollections;
  // choose the collections to monitor
  // a) NminusOne
  if(plots=="NminusOne"){
    thoseCollections.push_back("noPt"     );
    thoseCollections.push_back("noEta"    );
    thoseCollections.push_back("noTrkHits");
    thoseCollections.push_back("noChi2"   );
    thoseCollections.push_back("noDb"     );   
    thoseCollections.push_back("tight"    );
    thoseCollections.push_back("tight"    );
    thoseCollections.push_back("tight"    );
    thoseCollections.push_back("noDR"     );
    thoseCollections.push_back("noIso"    );
    thoseCollections.push_back("tight"    );
    thoseCollections.push_back("noEta"    );
    thoseCollections.push_back("noPt"     );
    thoseCollections.push_back("noEm"     );
    thoseCollections.push_back("nofHPD"   );
    thoseCollections.push_back("noN90Hits");
    thoseCollections.push_back("tight"    );
    thoseCollections.push_back("tight"    );
    thoseCollections.push_back("bottom"   );
  }
   // b) cutflow
  if(plots=="cutflow"){
    thoseCollections.push_back("combined" );
    thoseCollections.push_back("highPt"   );
    thoseCollections.push_back("kinematic");
    thoseCollections.push_back("kinematic");
    thoseCollections.push_back("kinematic");   
    thoseCollections.push_back("tight"    );
    thoseCollections.push_back("tight"    );
    thoseCollections.push_back("tight"    );
    thoseCollections.push_back("track"    );
    thoseCollections.push_back("golden"   );
    thoseCollections.push_back("tight"    );
    thoseCollections.push_back("pat"      );
    thoseCollections.push_back("central"  );
    thoseCollections.push_back("reliable" );
    thoseCollections.push_back("reliable" );
    thoseCollections.push_back("reliable" );
    thoseCollections.push_back("tight"    );
    thoseCollections.push_back("tight"    );
    thoseCollections.push_back("bottom"   );
  }  

  std::vector<TH1F*> pt_, eta_, nHit_, chi2_, d0_, dz_, ecalEn_, hcalEn_, dR_, relIso_, n_;
  std::vector<TH1F*> etaJets_, ptlead1Jet_, ptlead2Jet_, ptlead3Jet_, ptlead4Jet_, emf_ , fhpd_, n90hits_, nJets_;
  std::vector<TH1F*> bdiscr_, bdiscrPre_, nbJets_;
  std::vector<TH1F*> nVetoMu_, nVetoE_, etVetoE_, etaVetoE_, relIsoVetoE_;
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
    etaJets_   .push_back( (TH1F*)files_[idx]->Get(thoseCollections[11]+"JetKinematics/eta"      )->Clone() );
    ptlead1Jet_.push_back( (TH1F*)files_[idx]->Get(thoseCollections[12]+"Lead_0_JetKinematics/pt")->Clone() );
    ptlead2Jet_.push_back( (TH1F*)files_[idx]->Get(thoseCollections[12]+"Lead_1_JetKinematics/pt")->Clone() );
    ptlead3Jet_.push_back( (TH1F*)files_[idx]->Get(thoseCollections[12]+"Lead_2_JetKinematics/pt")->Clone() );
    ptlead4Jet_.push_back( (TH1F*)files_[idx]->Get(thoseCollections[12]+"Lead_3_JetKinematics/pt")->Clone() );
    emf_       .push_back( (TH1F*)files_[idx]->Get(thoseCollections[13]+"JetQuality/emf"         )->Clone() );
    fhpd_      .push_back( (TH1F*)files_[idx]->Get(thoseCollections[14]+"JetQuality/fHPD_"       )->Clone() );
    n90hits_   .push_back( (TH1F*)files_[idx]->Get(thoseCollections[15]+"JetQuality/n90Hits_"    )->Clone() );
    nJets_     .push_back( (TH1F*)files_[idx]->Get(thoseCollections[16]+"JetKinematics/n"        )->Clone() );
    // btag plots
    bdiscr_    .push_back( (TH1F*)files_[idx]->Get(thoseCollections[17]+"JetQuality/btagTrkCntHighEff_"             )->Clone() );
    nbJets_    .push_back( (TH1F*)files_[idx]->Get(thoseCollections[18]+"JetKinematics/n"                           )->Clone() );
    bdiscrPre_ .push_back( (TH1F*)files_[idx]->Get(thoseCollections[17]+"JetQualityBeforeJetCuts/btagTrkCntHighEff_")->Clone() );
    // veto collection plots
    nVetoMu_.push_back    ( (TH1F*)files_[idx]->Get("looseVetoMuonKinematics/n"    )->Clone() );
    nVetoE_ .push_back    ( (TH1F*)files_[idx]->Get("looseVetoElectronKinematics/n")->Clone() );
    etVetoE_ .push_back   ( (TH1F*)files_[idx]->Get("patVetoElectronKinematics/et" )->Clone() );
    etaVetoE_.push_back   ( (TH1F*)files_[idx]->Get("patVetoElectronKinematics/eta")->Clone() );
    relIsoVetoE_.push_back( (TH1F*)files_[idx]->Get("patVetoElectronQuality/relIso")->Clone() );
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
    dz_    [idx]->Rebin();
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
    bdiscr_   [idx]->Scale(lumiweight[idx]);
    nbJets_   [idx]->Scale(lumiweight[idx]);
    bdiscrPre_[idx]->Scale(lumiweight[idx]);
    nVetoMu_ [idx]->Scale(lumiweight[idx]);
    nVetoE_  [idx]->Scale(lumiweight[idx]);
    etVetoE_ [idx]->Scale(lumiweight[idx]);
    etaVetoE_[idx]->Scale(lumiweight[idx]);
  }

  // ---
  //    print out # events ( MC / Data)
  // ---
  // loop jet multiplicities
  for(int mult=2; mult<=10; ++mult){
   std::cout << "---------------------" << std::endl;
    std::cout << "number of entries =="+getTStringFromInt(mult-1)+" jets" << std::endl;
    std::cout << "ttbar sig : " << nJets_[kSignal    ]->GetBinContent(mult) << std::endl;
    std::cout << "ttbar bkg : " << nJets_[kBackground]->GetBinContent(mult) << std::endl;
    std::cout << "QCD : "       << nJets_[kQCD       ]->GetBinContent(mult) << std::endl;
    std::cout << "Z+jets : "    << nJets_[kZjets     ]->GetBinContent(mult) << std::endl;
    std::cout << "W+jets : "    << nJets_[kWjets     ]->GetBinContent(mult) << std::endl;
    std::cout << "all MC: " << nJets_[kSignal]->GetBinContent(mult)+nJets_[kBackground]->GetBinContent(mult)+nJets_[kQCD]->GetBinContent(mult)+nJets_[kZjets]->GetBinContent(mult)+nJets_[kWjets]->GetBinContent(mult) << std::endl;
    std::cout << "data : "      << nJets_[kData      ]->GetBinContent(mult) << std::endl<< std::endl;
  }
  
  // ---
  //    configure histogram style & create stack plots
  // ---
  THStack *pt         = new THStack("pt"    ,"");
  THStack *eta        = new THStack("eta"   ,""); 
  THStack *nHit       = new THStack("nHit"  ,""); 
  THStack *chi2       = new THStack("chi2"  ,""); 
  THStack *d0         = new THStack("d0"    ,""); 
  THStack *dz         = new THStack("dz"    ,""); 
  THStack *ecalEn     = new THStack("ecalEn",""); 
  THStack *hcalEn     = new THStack("hcalEn",""); 
  THStack *dR         = new THStack("dR"    ,""); 
  THStack *relIso     = new THStack("relIso",""); 
  THStack *n          = new THStack("n"     ,""); 
  THStack *etaJets    = new THStack("etaJets"   ,"");
  THStack *ptlead1Jet = new THStack("ptlead1Jet","");
  THStack *ptlead2Jet = new THStack("ptlead2Jet","");
  THStack *ptlead3Jet = new THStack("ptlead3Jet","");
  THStack *ptlead4Jet = new THStack("ptlead4Jet","");
  THStack *emf        = new THStack("emf"       ,"");
  THStack *fhpd       = new THStack("fhpd"      ,"");
  THStack *n90hits    = new THStack("n90hits"   ,"");
  THStack *nJets      = new THStack("nJets"     ,"");
  THStack *bdiscr     = new THStack("bdiscr"    ,"");
  THStack *bdiscrPre  = new THStack("bdiscrPre" ,"");
  THStack *nbJets     = new THStack("nbJets"    ,""); 
  THStack *nVetoMu    = new THStack("nVetoMu" ,"");
  THStack *nVetoE     = new THStack("nVetoE"  ,"");
  THStack *etVetoE    = new THStack("etVetoE" ,"");
  THStack *etaVetoE   = new THStack("etaVetoE","");

  for(unsigned int idx=0; idx<=kData; ++idx) {
    // define sample specific draw options
    int color =0;
    int fillstyle = 1001;
    int filled =1;
    double markerSize=1.0;
    int markerStyle=20;
    if(idx==kSignal){
      color =kRed;
      fillstyle = 3006;
    }
    if(idx==kBackground){
      color =kBlue;
      fillstyle = 3007;
    }
    if(idx==kWjets){
      color =8;
      fillstyle = 3004;
    }
    if(idx==kZjets){
      color =6;
      fillstyle = 3005;
    }
    if(idx==kQCD){
      color =17;
      fillstyle = 1001;
    }
    if(idx==kData){      
      color = kBlack;
      filled = 0;
      markerSize=1.5;
      markerStyle=22;
    }
    // choose styling options
    histogramStyle(*pt_     [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*eta_    [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*nHit_   [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*chi2_   [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*d0_     [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*dz_     [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*ecalEn_ [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*hcalEn_ [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*dR_     [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*relIso_ [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*n_      [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*etaJets_   [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*ptlead1Jet_[idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*ptlead2Jet_[idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*ptlead3Jet_[idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*ptlead4Jet_[idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*emf_       [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*fhpd_      [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*n90hits_   [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle); 
    histogramStyle(*nJets_     [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*bdiscr_    [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*bdiscrPre_ [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*nbJets_    [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*nVetoMu_ [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*nVetoE_  [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*etVetoE_ [idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    histogramStyle(*etaVetoE_[idx], color, 1 ,markerStyle, markerSize, filled, fillstyle);
    // create stack plots
    if(idx!=kData){
      pt    ->Add(pt_     [idx]);
      eta   ->Add(eta_    [idx]);
      nHit  ->Add(nHit_   [idx]);
      chi2  ->Add(chi2_   [idx]);
      d0    ->Add(d0_     [idx]);
      dz    ->Add(dz_     [idx]);
      ecalEn->Add(ecalEn_ [idx]);
      hcalEn->Add(hcalEn_ [idx]);
      dR    ->Add(dR_     [idx]);
      relIso->Add(relIso_ [idx]);
      n     ->Add(n_      [idx]);
      etaJets   ->Add(etaJets_   [idx]);
      ptlead1Jet->Add(ptlead1Jet_[idx]);
      ptlead2Jet->Add(ptlead2Jet_[idx]);
      ptlead3Jet->Add(ptlead3Jet_[idx]);
      ptlead4Jet->Add(ptlead4Jet_[idx]);
      emf       ->Add(emf_       [idx]);
      fhpd      ->Add(fhpd_      [idx]);
      n90hits   ->Add(n90hits_   [idx]);
      nJets     ->Add(nJets_     [idx]);
      bdiscr    ->Add(bdiscr_    [idx]);
      bdiscrPre ->Add(bdiscrPre_ [idx]);
      nbJets    ->Add(nbJets_    [idx]);
      nVetoMu ->Add(nVetoMu_ [idx]);
      nVetoE  ->Add(nVetoE_  [idx]);
      etVetoE ->Add(etVetoE_ [idx]);
      etaVetoE->Add(etaVetoE_[idx]);
    }
  }

  // ---
  //    create legends
  // ---
  // samples: separate canvas
  TLegend *leg0 = new TLegend(0.08, 0.19, 0.94, 0.88);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("MC "+lum+" nb^{-1} @7TeV");
  leg0->AddEntry( nHit_  [kSignal    ] , "ttbar s.lep.(#mu) MC@NLO", "F" ); 
  leg0->AddEntry( nHit_  [kBackground] , "ttbar other MC@NLO"      , "F" );
  leg0->AddEntry( nHit_  [kQCD       ] , "QCD PYTHIA"              , "F" );
  leg0->AddEntry( nHit_  [kWjets     ] , "W+jets MADGRAPH"         , "F" );
  leg0->AddEntry( nHit_  [kZjets     ] , "Z+jets MADGRAPH"         , "F" );
  leg0->AddEntry( nHit_  [kData      ] , "2010 data"               , "PL");
 
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
  TLegend *leg23= (TLegend*)(leg2->Clone());
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
  leg13->SetHeader(""+thoseCollections[11]+" jets");
  leg14->SetHeader(""+thoseCollections[12]+" jets");
  leg15->SetHeader(""+thoseCollections[13]+" jets");
  leg18->SetHeader(""+thoseCollections[14]+" jets");
  leg19->SetHeader(""+thoseCollections[15]+" jets");
  leg20->SetHeader(thoseCollections[16]+" jets");
  leg21->SetHeader(""+thoseCollections[17]+" jets");
  leg22->SetHeader(thoseCollections[18]+" jets");
  leg16->SetHeader("looseMuons");
  leg17->SetHeader("looseElectrons");
  leg23->SetHeader("patElectrons");

  // label indicating cutstep
  TPaveLabel *cut0 = label("(hltMu9 ev. sel.)"          , 0.73, 0.87, 0.9, 1.0);
  TPaveLabel *cut1 = label("(#mu ev. sel.)"             , 0.73, 0.87, 0.9, 1.0);
  TPaveLabel *cut2 = label("(#mu & veto ev. sel.)"      , 0.73, 0.87, 0.9, 1.0);
  TPaveLabel *cut3 = label("(#mu & veto & jet ev. sel.)", 0.73, 0.87, 0.9, 1.0);

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<28; idx++){ 
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
  MyCanvas[0]->SetTitle("ptLeading"+thoseCollections[0]+"MuonsLum"+lum+"nb@7TeV");
  pt        ->Draw("");
  pt_[kData]->Draw("EPsame");
  pt        ->Draw("AXISsame");
  axesStyle(*pt, "p_{t} ( lead #mu ) [GeV]", "events", 0.1/840*luminosity, 5.0*pt->GetMaximum()/12.38*luminosity  );
  //  leg2      ->Draw("same");
  cut0      ->Draw("same");
  drawcutline(20.5, 0.05*pt->GetMaximum()*luminosity);

  // ---
  //    do the printing for eta_
  // ---
  MyCanvas[1]->cd(0);
  MyCanvas[1]->SetLogy(1);
  MyCanvas[1]->SetTitle("etaLeading"+thoseCollections[1]+"MuonsLum"+lum+"nb@7TeV");
  eta        ->Draw("");
  eta_[kData]->Draw("EPsame");
  eta        ->Draw("AXISsame");
  //leg3       ->Draw("same");
  cut0       ->Draw("same");
  axesStyle(*eta, "#eta ( lead #mu )", "events", 0.1/840*luminosity, 0.1*eta->GetMaximum()*luminosity );
  drawcutline(-2.1, 0.01* eta->GetMaximum()*luminosity);
  drawcutline( 2.1, 0.01* eta->GetMaximum()*luminosity);

  // ---
  //    do the printing for nHit_
  // ---
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetLogy(1);
  MyCanvas[2]->SetTitle("trackerHitsLeading"+thoseCollections[2]+"MuonsLum"+lum+"nb@7TeV");
  nHit        ->Draw("");
  axesStyle(*nHit, "N_{Hits trk} ( lead #mu )", "events", 0.1/840*luminosity, 0.1*nHit->GetMaximum()*luminosity );
  nHit_[kData]->Draw("EPsame");
  nHit        ->Draw("AXISsame");
  //  leg4        ->Draw("same");
  cut0        ->Draw("same");
  drawcutline(10.5, 0.01*nHit->GetMaximum()*luminosity);

  // ---
  //    do the printing for chi2_
  // ---
  MyCanvas[3]->cd(0);
  MyCanvas[3]->SetLogy(1);
  MyCanvas[3]->SetTitle("chi2Leading"+thoseCollections[3]+"MuonsLum"+lum+"nb@7TeV");
  chi2        ->Draw("");
  axesStyle(*chi2, "#chi^{2} ( lead #mu )", "events", 0.001/840*luminosity, 0.1*chi2->GetMaximum()*luminosity );
  chi2_[kData]->Draw("EPsame");
  chi2        ->Draw("AXISsame");
  //  leg5        ->Draw("same");
  cut0        ->Draw("same");
  drawcutline(10., 0.01*chi2->GetMaximum()*luminosity);

  // ---
  //    do the printing for d0_
  // ---
  MyCanvas[4]->cd(0);
  MyCanvas[4]->SetTitle("dBLeading"+thoseCollections[4]+"MuonsLum"+lum+"nb@7TeV");
  MyCanvas[4]->SetLogy(1);
  axesStyle(*d0_[kData], "d_{B} ( lead #mu ) [cm]", "events", 0.001/840*luminosity, 0.1*d0->GetMaximum()*luminosity );
  d0_[kData]->GetXaxis()->SetRangeUser(0.,0.2);
  d0_[kData]->Draw("AXIS");
  d0        ->Draw("same");
  d0_[kData]->Draw("EPsame");
  //  leg6      ->Draw("same");
  cut0      ->Draw("same");
  d0_[kData]->Draw("AXIS same");
  drawcutline(0.02, 0.01*d0->GetMaximum()*luminosity);

  // ---
  //    do the printing for dz_
  // ---
  MyCanvas[5]->cd(0);
  MyCanvas[5]->SetLogy(1);
  MyCanvas[5]->SetTitle("dzLeading"+thoseCollections[5]+"MuonsLum"+lum+"nb@7TeV");
  axesStyle(*dz_[kData], "d_{z} ( lead #mu )", "events", 0.1/840*luminosity, 0.01*dz->GetMaximum()*luminosity );
  dz_[kData]->Draw("AXIS"  );
  dz        ->Draw("same"  );
  dz_[kData]->Draw("EPsame");
  //  leg7      ->Draw("same");
  cut0      ->Draw("same");

  // ---
  //    do the printing for ecalEn_
  // ---
  MyCanvas[6]->cd(0);
  MyCanvas[6]->SetLogy(1);
  MyCanvas[6]->SetTitle("ecalEnLeading"+thoseCollections[6]+"MuonsLum"+lum+"nb@7TeV");
  ecalEn        ->Draw();
  axesStyle(*ecalEn, "E_{Ecal} ( lead #mu ) [GeV]", "events" , 0.001/840*luminosity, 0.1*ecalEn->GetMaximum()*luminosity);
  ecalEn_[kData]->Draw("EPsame");
  ecalEn        ->Draw("AXISsame");
  //  leg8          ->Draw("same");
  cut0          ->Draw("same");
  
  // ---
  //    do the printing for hcalEn_
  // ---
  MyCanvas[7]->cd(0);
  MyCanvas[7]->SetLogy(1);
  MyCanvas[7]->SetTitle("hcalEnLeading"+thoseCollections[7]+"MuonsLum"+lum+"nb@7TeV");
  hcalEn        ->Draw();
  axesStyle(*hcalEn, "E_{Hcal} ( lead #mu ) [GeV]", "events", 0.01/840*luminosity, 0.1*hcalEn->GetMaximum()*luminosity );
  hcalEn_[kData]->Draw("EPsame");
  hcalEn        ->Draw("AXISsame");
  //  leg9          ->Draw("same");
  cut0          ->Draw("same");

  // ---
  //    do the printing for dR_
  // ---
  MyCanvas[8]->cd(0);
  MyCanvas[8]->SetLogy(1);
  MyCanvas[8]->SetTitle("distance"+thoseCollections[8]+"MuonsVetoJetsLum"+lum+"nb@7TeV");
  dR        ->Draw();
  axesStyle(*dR, "#DeltaR ( lead #mu - tight jet )", "events", 0.1/840*luminosity, 0.1*dR->GetMaximum()*luminosity );
  dR_[kData]->Draw("EPsame");
  dR        ->Draw("AXISsame");
  //  leg10     ->Draw("same");
  cut0      ->Draw("same");
  drawcutline(0.3, 0.001*dR->GetMaximum()*luminosity);

  // ---
  //    do the printing for relIso_
  // ---
  MyCanvas[9]->cd(0);
  MyCanvas[9]->SetLogy(1);
  MyCanvas[9]->SetTitle("relIsoLeading"+thoseCollections[9]+"MuonsLum"+lum+"nb@7TeV");
  relIso        ->Draw();
  axesStyle(*relIso, "relIso ( lead #mu )", "events", 0.01/840*luminosity, 0.1*relIso->GetMaximum()*luminosity );
  relIso_[kData]->Draw("EPsame");
  relIso        ->Draw("AXISsame");
  //  leg11         ->Draw("same");
  cut0          ->Draw("same");
  drawcutline(0.05, 0.01*relIso->GetMaximum()*luminosity);

  // ---
  //    do the printing for n_
  // ---
  MyCanvas[10]->cd(0);
  MyCanvas[10]->SetLogy(1);
  MyCanvas[10]->SetTitle("multiplicity"+thoseCollections[10]+"MuonsLum"+lum+"nb@7TeV");
  axesStyle(*n_[kData], "multiplicity ( #mu )", "events", 0.1/840*luminosity, n->GetMaximum()*luminosity );
  n_[kData]->GetXaxis()->SetRangeUser(0.,3.);
  n_[kData]->Draw("AXIS"  );
  n        ->Draw("same"  );
  n_[kData]->Draw("EPsame");
  //  leg12    ->Draw("same");
  label("muon selection")->Draw("same");
  cut0     ->Draw("same");
  n_[kData]->Draw("AXIS same");
  drawcutline(0.5, 0.01*n->GetMaximum()*luminosity);
  drawcutline(1.5, 0.01*n->GetMaximum()*luminosity);

  // ---
  //    do the printing for etaJets_
  // ---
  MyCanvas[11]->cd(0);
  MyCanvas[11]->SetLogy(1);
  MyCanvas[11]->SetTitle("etaAll"+thoseCollections[11]+"JetsLum"+lum+"nb@7TeV");
  etaJets        ->Draw();
  axesStyle(*etaJets, "#eta (all jets)", "events", 1.0/840*luminosity, 0.1*etaJets->GetMaximum()*luminosity );
  etaJets_[kData]->Draw("EPsame");
  etaJets        ->Draw("Axis same"); 
  //  leg13          ->Draw("same");
  cut2           ->Draw("same");
  drawcutline(-2.4, 0.01*etaJets->GetMaximum()*luminosity);
  drawcutline( 2.4, 0.01*etaJets->GetMaximum()*luminosity);

  // ---
  //    do the printing for ptlead1Jet_
  // ---
  MyCanvas[12]->cd(0);
  MyCanvas[12]->SetLogy(1);
  MyCanvas[12]->SetTitle("pt1stLeading"+thoseCollections[12]+"JetLum"+lum+"nb@7TeV");
  ptlead1Jet        ->Draw(); 
  axesStyle(*ptlead1Jet, "p_{t} ( lead jet ) [GeV]", "events", 0.01/840*luminosity,  1.0*ptlead1Jet->GetMaximum()*luminosity );
  ptlead1Jet_[kData]->Draw("EPsame");
  ptlead1Jet        ->Draw("Axis same");
  //  leg14             ->Draw("same");
  cut2              ->Draw("same");
  drawcutline(30.0, 0.01*ptlead1Jet->GetMaximum()*luminosity);

  // ---
  //    do the printing for ptlead2Jet_
  // ---
  MyCanvas[13]->cd(0);
  MyCanvas[13]->SetLogy(1);
  MyCanvas[13]->SetTitle("pt2ndLeading"+thoseCollections[12]+"JetLum"+lum+"nb@7TeV");
  ptlead2Jet        ->Draw();
  axesStyle(*ptlead2Jet, "p_{t} ( 2^{nd} lead jet ) [GeV]", "events", 0.01/840*luminosity, 0.2*ptlead2Jet->GetMaximum()*luminosity );
  ptlead2Jet_[kData]->Draw("EPsame");
  ptlead2Jet        ->Draw("Axis same");
  //  leg14             ->Draw("same");
  cut2              ->Draw("same");
  drawcutline(30.0, 0.01*ptlead2Jet->GetMaximum()*luminosity);

  // ---
  //    do the printing for ptlead3Jet_
  // ---
  MyCanvas[14]->cd(0);
  MyCanvas[14]->SetLogy(1);
  MyCanvas[14]->SetTitle("pt3rdLeading"+thoseCollections[12]+"JetLum"+lum+"nb@7TeV");
  ptlead3Jet        ->Draw();
  axesStyle(*ptlead3Jet, "p_{t} ( 3^{rd} lead jet ) [GeV]", "events", 0.01/840*luminosity, 1.0*ptlead3Jet->GetMaximum()*luminosity );
  ptlead3Jet_[kData]->Draw("EPsame");
  ptlead3Jet        ->Draw("Axis same");
  //  leg14             ->Draw("same");
  cut2              ->Draw("same");
  drawcutline(30.0, 0.01*ptlead3Jet->GetMaximum()*luminosity);

  // ---
  //    do the printing for ptlead4Jet_
  // ---
  MyCanvas[15]->cd(0);
  MyCanvas[15]->SetLogy(1);
  MyCanvas[15]->SetTitle("pt4thLeading"+thoseCollections[12]+"JetLum"+lum+"nb@7TeV");
  ptlead4Jet        ->Draw();
  axesStyle(*ptlead4Jet, "p_{t} ( 4^{th} lead jet ) [GeV]", "events", 0.01/840*luminosity, 0.5*ptlead4Jet->GetMaximum()*luminosity );
  ptlead4Jet_[kData]->Draw("EPsame");
  ptlead4Jet        ->Draw("Axis same");
  //  leg14             ->Draw("same");
  cut2              ->Draw("same");
  drawcutline(30.0, 0.01*ptlead4Jet->GetMaximum()*luminosity);

  // ---
  //    do the printing for emf_
  // ---
  MyCanvas[16]->cd(0);
  MyCanvas[16]->SetLogy(1);
  MyCanvas[16]->SetTitle("electromagneticFraction"+thoseCollections[13]+"JetsLum"+lum+"nb@7TeV");
  emf        ->Draw();
  axesStyle(*emf, "electromagnetic fraction", "events", 0.1/840*luminosity, 1.0*emf->GetMaximum()*luminosity );
  emf_[kData]->Draw("EPsame");
  emf        ->Draw("Axis same");
  //  leg15      ->Draw("same");
  cut2       ->Draw("same");
  drawcutline(0.95, 0.05*emf->GetMaximum()*luminosity);

  // ---
  //    do the printing for nVetoMu_
  // ---
  MyCanvas[17]->cd(0);
  MyCanvas[17]->SetLogy(1);
  MyCanvas[17]->SetTitle("multiplicityLooseMuonsLum"+lum+"nb@7TeV");
  axesStyle(*nVetoMu_[kData], "multiplicity ( #mu )", "events", 1.0/840*luminosity , 1.0*nVetoMu->GetMaximum()*luminosity );
  nVetoMu_[kData]->GetXaxis()->SetRangeUser(0.,3.);
  nVetoMu_[kData]->Draw("Axis");
  nVetoMu        ->Draw("same");
  nVetoMu_[kData]->Draw("EPsame");
  //  leg16          ->Draw("same");
  label("muon veto")->Draw("same");
  cut1           ->Draw("same");
  nVetoMu_[kData]->Draw("Axis same");
  drawcutline(0.5, 0.01*nVetoMu->GetMaximum()*luminosity);
  drawcutline(1.5, 0.01*nVetoMu->GetMaximum()*luminosity);

  // ---
  //    do the printing for nVetoE_
  // ---
  MyCanvas[18]->cd(0);
  MyCanvas[18]->SetLogy(1);
  MyCanvas[18]->SetTitle("multiplicityLooseElectronsLum"+lum+"nb@7TeV");
  axesStyle(*nVetoE_[kData], "multiplicity ( e )", "events", 0.01/840*luminosity, 1.0*nVetoE->GetMaximum()*luminosity );
  nVetoE_[kData]->GetXaxis()->SetRangeUser(-0.5, 2.5);
  nVetoE_[kData]->Draw("Axis");
  nVetoE        ->Draw("same");
  nVetoE_[kData]->Draw("EPsame");
  //  leg17         ->Draw("same");
  label("electron veto")->Draw("same");
  cut1                  ->Draw("same");
  nVetoE_[kData]->Draw("Axis same");
  drawcutline(0.5, 0.01*nVetoE->GetMaximum()*luminosity);

  // ---
  //    do the printing for fhpd_
  // ---
  MyCanvas[19]->cd(0);
  MyCanvas[19]->SetLogy(1);
  MyCanvas[19]->SetTitle("fHPD"+thoseCollections[14]+"JetsLum"+lum+"nb@7TeV");
  fhpd        ->Draw();
  axesStyle(*fhpd, "fHPD", "events", 0.01/840*luminosity, 1.0*fhpd->GetMaximum()*luminosity );
  fhpd_[kData]->Draw("EPsame");
  fhpd        ->Draw("Axis same");
  //  leg18       ->Draw("same");
  cut2        ->Draw("same");
  drawcutline(0.98, 0.01*fhpd->GetMaximum()*luminosity);

  // ---
  //    do the printing for n90hits_
  // ---
  MyCanvas[20]->cd(0);
  MyCanvas[20]->SetLogy(1);
  MyCanvas[20]->SetTitle("n90hits"+thoseCollections[15]+"JetsLum"+lum+"nb@7TeV");
  n90hits        ->Draw();
  axesStyle(*n90hits, "n90Hits", "events", 0.01/840*luminosity, 0.1*n90hits->GetMaximum()*luminosity );
  n90hits_[kData]->Draw("EPsame");
  n90hits        ->Draw("Axis same");
  //  leg19          ->Draw("same");
  cut2           ->Draw("same");
  drawcutline(1.0, 0.01*n90hits->GetMaximum()*luminosity);

  // ---
  //    do the printing for nJets_
  // ---
  MyCanvas[21]->cd(0);
  MyCanvas[21]->SetLogy(1);
  MyCanvas[21]->SetTitle("nJets"+thoseCollections[16]+"JetsLum"+lum+"nb@7TeV");
  axesStyle(*nJets_[kData], "jet Multiplicity", "events", 0.1/840*luminosity, nJets->GetMaximum()*luminosity );
  nJets_[kData]->GetXaxis()->CenterLabels();
  nJets_[kData]->GetXaxis()->SetNdivisions(510);
  nJets_[kData]->Draw("AXIS"  );
  nJets        ->Draw("same"  );
  nJets_[kData]->Draw("EPsame");
  //  leg20        ->Draw("same");
  label("jet selection")->Draw("same");
  cut2         ->Draw("same");
  nJets_[kData]->Draw("AXIS same");
  drawcutline(4.0, 0.01*nJets->GetMaximum()*luminosity);

  // ---
  //    do the printing for bdiscr_
  // ---
  MyCanvas[22]->cd(0);
  MyCanvas[22]->SetLogy(1);
  MyCanvas[22]->SetTitle("bdiscr"+thoseCollections[17]+"JetsLum"+lum+"nb@7TeV");
  axesStyle(*bdiscr_[kData], "b-discr. (tche)", "events", 0.1/840*luminosity, 0.1*bdiscr->GetMaximum()*luminosity );
  bdiscr_[kData]->Draw("Axis");
  bdiscr        ->Draw("same");
  bdiscr_[kData]->Draw("EPsame");
  //  leg21         ->Draw("same");
  cut3          ->Draw("same");
  bdiscr_[kData]->Draw("Axis same");
  drawcutline(3.3, 0.01*bdiscr->GetMaximum()*luminosity);

  // ---
  //    do the printing for bdiscrPre_
  // ---
  MyCanvas[23]->cd(0);
  MyCanvas[23]->SetLogy(1);
  MyCanvas[23]->SetTitle("bdiscrPre"+thoseCollections[17]+"JetsLum"+lum+"nb@7TeV");
  bdiscrPre        ->Draw();
  axesStyle(*bdiscrPre, "b-discr. (tche)", "events", 0.1/840*luminosity, bdiscr->GetMaximum()*luminosity );
  bdiscrPre_[kData]->Draw("EPsame");
  bdiscrPre        ->Draw("Axis same");
  //  leg21            ->Draw("same");
  cut0             ->Draw("same");
  drawcutline(3.3, 0.01*bdiscrPre->GetMaximum()*luminosity);

  // ---
  //    do the printing for nbJets_
  // ---
  MyCanvas[24]->cd(0);
  MyCanvas[24]->SetLogy(1);
  MyCanvas[24]->SetTitle("nbJets"+thoseCollections[18]+"JetsLum"+lum+"nb@7TeV");
  axesStyle(*nbJets_[kData], "b-jet multiplicity (tche-mWP)", "events", 0.1/840*luminosity, 0.1*nbJets->GetMaximum()*luminosity );
  nbJets_[kData]->GetXaxis()->SetRangeUser(0.,3.);
  nbJets_[kData]->GetXaxis()->CenterLabels();
  nbJets_[kData]->Draw("Axis");
  nbJets        ->Draw("same");
  nbJets_[kData]->Draw("EPsame");
  //  leg22         ->Draw("same");
  cut3          ->Draw("same");
  nbJets_[kData]->Draw("Axis same");
  drawcutline(1.0, 0.01*nbJets->GetMaximum()*luminosity);

  // ---
  //    do the printing for common event Selection legend
  // ---
  MyCanvas[25]->cd(0);
  MyCanvas[25]->SetTitle("legendEventSelectionLum"+lum+"nb@7TeV");
  leg0->Draw("");

  // ---
  //    do the printing for etVetoE_
  // ---
  MyCanvas[26]->cd(0);
  MyCanvas[26]->SetLogy(1);
  MyCanvas[26]->SetTitle("ptPatVetoElectronsLum"+lum+"nb@7TeV");
  etVetoE     ->Draw();
  axesStyle(*etVetoE, "E_{t} ( e ) [GeV]", "events", 0.01/840*luminosity, 0.1*etVetoE->GetMaximum()*luminosity );
  etVetoE_[kData]->Draw("EPsame");
  etVetoE        ->Draw("Axis same");
  cut1           ->Draw("same");
  //  leg23          ->Draw("same");
  drawcutline(15., 0.01*etVetoE->GetMaximum()*luminosity);

  // ---
  //    do the printing for etaVetoE_
  // ---
  MyCanvas[27]->cd(0);
  MyCanvas[27]->SetLogy(1);
  MyCanvas[27]->SetTitle("etaPatVetoElectronsLum"+lum+"nb@7TeV");
  etaVetoE    ->Draw();
  axesStyle(*etaVetoE, "#eta ( e )", "events", 0.01/840*luminosity, 1.0*etaVetoE->GetMaximum()*luminosity );
  if(etaVetoE->GetMinimum()/12.38*luminosity==0)etaVetoE->SetMinimum(0.01);
  etaVetoE_[kData]->Draw("EPsame");
  etaVetoE        ->Draw("Axis same");
  //  leg23           ->Draw("same");
  cut1            ->Draw("same");
  drawcutline( 2.5, 0.01*etaVetoE->GetMaximum()*luminosity); 
  drawcutline(-2.5, 0.01*etaVetoE->GetMaximum()*luminosity);

  // ---
  // saving
  // ---

  if(save){  
    // ps
    MyCanvas[0]->Print(saveTo+plots+"7TeV"+lum+"nb.pdf(", "pdf");
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+plots+"7TeV"+lum+"nb.pdf", "pdf");
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+plots+"7TeV"+lum+"nb.pdf)", "pdf");
 
    // png
    for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
      MyCanvas[idx]->Print(saveTo+(TString)(MyCanvas[idx]->GetTitle())+".png"); 
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

void histogramStyle(TH1& hist, int color, int lineStyle, int markerStyle, float markersize, int filled, int fillStyle) 
{
  hist.SetLineWidth(4);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color);
  hist.SetMarkerColor(color);  
  hist.SetMarkerStyle(markerStyle);
  hist.SetMarkerSize(markersize);
  hist.SetLineStyle(lineStyle);
  if(filled==1){
  hist.SetFillColor(color);
  hist.SetFillStyle(fillStyle);
  }
  else{
    hist.SetFillStyle(0);
  }
}

template <class T>
void axesStyle(T& hist, const char* titleX, const char* titleY, float yMin, float yMax, float yTitleSize, float yTitleOffset) 
{
  hist.SetTitle("");
  hist.GetXaxis()->SetTitle(titleX);
  hist.GetXaxis()->CenterTitle();
  hist.GetXaxis()->SetTitleSize  ( 0.06);
  hist.GetXaxis()->SetTitleColor (    1);
  hist.GetXaxis()->SetTitleOffset(  1.0);
  hist.GetXaxis()->SetTitleFont  (   62);
  if((TString)typeid(hist).name()=="4TH1F"){
    hist.GetXaxis()->SetLabelSize  ( 0.05);
    hist.GetXaxis()->SetLabelFont  (   62);
    hist.GetXaxis()->SetNdivisions (  505);
  }
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

TPaveLabel* label(TString text, double xmin, double ymin, double xmax, double ymax, double size){
  // label indicating cutstep
  TPaveLabel *label = new TPaveLabel(xmin, ymin, xmax, ymax, text, "br NDC");
  label->SetFillStyle(0);
  label->SetBorderSize(0);
  label->SetTextSize(size);
  return label;
}

int roundToInt(double value){
  int result=0;
  // take care of negative numbers
  if(value<0){
    std::cout << "no negative numbers allowed in roundToInt" << std::endl;
    return 0;
  }
  // get [value]
  for(int x=0; value>x; ++x){
    result=x;
  }
  // see if rest is > 0.5
  //  value-result >=0.5 ? return result+1 : return result;
  if((value-result) >=0.5) return (result+1);
  return result;
}

TString getTStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return (TString)result;
}
