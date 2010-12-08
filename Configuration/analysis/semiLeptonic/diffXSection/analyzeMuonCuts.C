#include "styleHelper.h"
///////////////////////////////////////////////////////////////////////////////////////////
////  This Macro analyzes all cut variables:number of valid Trackerhits, chi^2, dB,    ////
////  energy deposit in ecal and hcal, pt and eta, relIso and the multiplicity of the  //// 
////  final muon collection. All important jet quantities are also plotted. This is    ////
////  done within ttbar(semilept.mu + others), w+jets, z+jets and QCD-sample.          ////
////  Additionally data points can be filled in for comparism.                         //// 
///////////////////////////////////////////////////////////////////////////////////////////

//enum styles {kSignal, kBackground, kZjets, kWjets, kQCD, kData};

void canvasStyle(TCanvas& canv);

template <class T>
void axesStyle(T& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.07, float yTitleOffset=1.2);
void drawcutline(double cutval, double maximum);
//TPaveLabel* label(TString text="", double xmin=0.38, double ymin=0.79, double xmax=0.56, double ymax=1.0, double size=0.26);
int roundToInt(double value, bool roundDown=false);
TString getTStringFromInt(int i);
TString getTStringFromDouble(double d);

void analyzeMuonCuts(double luminosity = 34716, bool save = false, TString dataFile="./diffXSecFromSignal/data/data0309/DiffXSecData_Nov5PF.root", TString plots = "NminusOne", TString jetTyp = "PF")
{
  // ---
  //    main function parameters
  // ---
  // save:       choose whether you want to save every plot as png and all within one ps file
  // textoutput: choose whether you want to save the estimated number of QCD events for data 
  //             in .txt file to share it with other parts of the Analysis
  // luminosity: choose luminosity for scaling of event numbers 
  //             lum is derived from this and used for legend as entry
  //TString lum = getTStringFromDouble(luminosity/1000);
  TString lum = getTStringFromInt(roundToInt(luminosity/1000));
  TString lum2 = getTStringFromInt(roundToInt(luminosity));
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
  for(int ienum = 0; ienum<6; ienum++){
    if(ienum==kSig)files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecSigMadSpring10"+jetTyp+".root"    ) );
    if(ienum==kBkg)files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecBkgMadSpring10"+jetTyp+".root"    ) );
    //   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecSigNloSpring10.root"    ) );
    //   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecBkgNloSpring10.root"    ) );
    if(ienum==kZjets)files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecZjetsMadSpring10"+jetTyp+".root"  ) );
    if(ienum==kWjets)files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecWjetsMadSpring10"+jetTyp+".root"  ) );
    if(ienum==kQCD)  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecQCDPythiaSpring10"+jetTyp+".root" ) );
    if(ienum==kData) files_.push_back(new TFile(dataFile                                                             ) );
  }
  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;
  // add scaling factors here!

  // 7 TeV Monte Carlo spring 10 samples
  // -----------------------------------
  // for current ttbar(lept.mu on gen level and other) Madgraph 
  lumiweight.push_back(0.000000106*(double)luminosity);
  lumiweight.push_back(0.000000106*(double)luminosity);
  // for current ttbar(lept.mu on gen level and other) Mc@Nlo 
  //   lumiweight.push_back(0.000000159*(double)luminosity);
  //   lumiweight.push_back(0.000000159*(double)luminosity);
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
    if(jetTyp==""){
      emf_       .push_back( (TH1F*)files_[idx]->Get(thoseCollections[13]+"JetQuality/emf"         )->Clone() );
      fhpd_      .push_back( (TH1F*)files_[idx]->Get(thoseCollections[14]+"JetQuality/fHPD_"       )->Clone() );
      n90hits_   .push_back( (TH1F*)files_[idx]->Get(thoseCollections[15]+"JetQuality/n90Hits_"    )->Clone() );
    }
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
    if(jetTyp==""){
      emf_       [idx]->Scale(lumiweight[idx]);
      fhpd_      [idx]->Scale(lumiweight[idx]);
      n90hits_   [idx]->Scale(lumiweight[idx]);
    }
    nJets_     [idx]->Scale(lumiweight[idx]);
    bdiscr_   [idx]->Scale(lumiweight[idx]);
    nbJets_   [idx]->Scale(lumiweight[idx]);
    bdiscrPre_[idx]->Scale(lumiweight[idx]);
    nVetoMu_ [idx]->Scale(lumiweight[idx]);
    nVetoE_  [idx]->Scale(lumiweight[idx]);
    etVetoE_ [idx]->Scale(lumiweight[idx]);
    etaVetoE_[idx]->Scale(lumiweight[idx]);
    relIsoVetoE_[idx]->Scale(lumiweight[idx]);
  }

  // ---
  //    print out # events ( MC / Data)
  // ---
  // loop jet multiplicities
  for(int mult=2; mult<=10; ++mult){
   std::cout << "---------------------" << std::endl;
    std::cout << "number of entries =="+getTStringFromInt(mult-1)+" jets" << std::endl;
    std::cout << "ttbar sig : " << nJets_[kSig  ]->GetBinContent(mult) << std::endl;
    std::cout << "ttbar bkg : " << nJets_[kBkg  ]->GetBinContent(mult) << std::endl;
    std::cout << "QCD : "       << nJets_[kQCD  ]->GetBinContent(mult) << std::endl;
    std::cout << "Z+jets : "    << nJets_[kZjets]->GetBinContent(mult) << std::endl;
    std::cout << "W+jets : "    << nJets_[kWjets]->GetBinContent(mult) << std::endl;
    std::cout << "all MC: " << nJets_[kSig]->GetBinContent(mult)+nJets_[kBkg]->GetBinContent(mult)+nJets_[kQCD]->GetBinContent(mult)+nJets_[kZjets]->GetBinContent(mult)+nJets_[kWjets]->GetBinContent(mult) << std::endl;
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
  THStack *relIsoVetoE= new THStack("relIsoVetoE","");

  for(unsigned int idx=0; idx<=kData; ++idx) {
    // choose styling options
    histogramStyle(*pt_     [idx], idx);
    histogramStyle(*eta_    [idx], idx);
    histogramStyle(*nHit_   [idx], idx);
    histogramStyle(*chi2_   [idx], idx);
    histogramStyle(*d0_     [idx], idx);
    histogramStyle(*dz_     [idx], idx);
    histogramStyle(*ecalEn_ [idx], idx);
    histogramStyle(*hcalEn_ [idx], idx);
    histogramStyle(*dR_     [idx], idx);
    histogramStyle(*relIso_ [idx], idx);
    histogramStyle(*n_      [idx], idx);
    histogramStyle(*etaJets_   [idx], idx);
    histogramStyle(*ptlead1Jet_[idx], idx);
    histogramStyle(*ptlead2Jet_[idx], idx);
    histogramStyle(*ptlead3Jet_[idx], idx);
    histogramStyle(*ptlead4Jet_[idx], idx);
    if(jetTyp==""){
      histogramStyle(*emf_       [idx], idx);
      histogramStyle(*fhpd_      [idx], idx);
      histogramStyle(*n90hits_   [idx], idx);
    }
    histogramStyle(*nJets_     [idx], idx);
    histogramStyle(*bdiscr_    [idx], idx);
    histogramStyle(*bdiscrPre_ [idx], idx);
    histogramStyle(*nbJets_    [idx], idx);
    histogramStyle(*nVetoMu_ [idx], idx);
    histogramStyle(*nVetoE_  [idx], idx);
    histogramStyle(*etVetoE_ [idx], idx);
    histogramStyle(*etaVetoE_[idx], idx);
    histogramStyle(*relIsoVetoE_[idx], idx);
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
      if(jetTyp==""){
	emf       ->Add(emf_       [idx]);
	fhpd      ->Add(fhpd_      [idx]);
	n90hits   ->Add(n90hits_   [idx]);
      }
      nJets     ->Add(nJets_     [idx]);
      bdiscr    ->Add(bdiscr_    [idx]);
      bdiscrPre ->Add(bdiscrPre_ [idx]);
      nbJets    ->Add(nbJets_    [idx]);
      nVetoMu ->Add(nVetoMu_ [idx]);
      nVetoE  ->Add(nVetoE_  [idx]);
      etVetoE ->Add(etVetoE_ [idx]);
      etaVetoE->Add(etaVetoE_[idx]);
      relIsoVetoE->Add(relIsoVetoE_[idx]);
    }
  }

  // ---
  //    create legends
  // ---
  // samples: separate canvas
  TLegend *leg0 = new TLegend(0.08, 0.19, 0.94, 0.88);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->AddEntry( nHit_  [kData ] , "Data ("+lum+" pb ^{-1})"    , "PL");
  leg0->AddEntry( nHit_  [kSig  ] , "t#bar{t} signal"                 , "F" ); 
  leg0->AddEntry( nHit_  [kBkg  ] , "t#bar{t} other"                  , "F" );
  leg0->AddEntry( nHit_  [kQCD  ] , "QCD"                             , "F" );
  leg0->AddEntry( nHit_  [kWjets] , "W#rightarrowl#nu"              , "F" );
  leg0->AddEntry( nHit_  [kZjets] , "Z/#gamma*#rightarrowl^{+}l^{-}", "F" );
 
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

//   // label indicating cutstep
//   TPaveLabel *cut0 = label("(hltMu9 ev. sel.)"          , 0.73, 0.87, 0.9, 1.0);
//   TPaveLabel *cut1 = label("(#mu ev. sel.)"             , 0.73, 0.87, 0.9, 1.0);
//   TPaveLabel *cut2 = label("(#mu & veto ev. sel.)"      , 0.73, 0.87, 0.9, 1.0);
//   TPaveLabel *cut3 = label("(#mu & veto & jet ev. sel.)", 0.73, 0.87, 0.9, 1.0);

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<29; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }
  bool cutLine = false;
  double min = 0.;
  double max = 0.;
  // ---
  //    do the printing for pt_
  // ---
  min = 0.1/840*luminosity;
  max = getMaxValue(*pt_[kData], "");
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetLogy(1);
  MyCanvas[0]->SetTitle("ptLeading"+thoseCollections[0]+"Muons@7TeV");
  pt        ->Draw("");
  pt_[kData]->Draw("EPsame");
  pt        ->Draw("AXISsame");
  axesStyle(*pt, "p_{t}(#mu) [GeV]", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  //  leg2      ->Draw("same");
  //cut0      ->Draw("same");
  if(cutLine)drawcutline(20.5, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for eta_
  // ---
  max = getMaxValue(*eta_[kData], "");
  MyCanvas[1]->cd(0);
  //  MyCanvas[1]->SetLogy(1);
  MyCanvas[1]->SetTitle("etaLeading"+thoseCollections[1]+"Muons@7TeV");
  eta        ->Draw("");
  eta_[kData]->Draw("EPsame");
  eta        ->Draw("AXISsame");
  //leg3       ->Draw("same");
  //cut0       ->Draw("same");
  //  axesStyle(*eta, "#eta ( lead #mu )", "events", 0.1/840*luminosity, 0.1*eta->GetMaximum()*luminosity );
  axesStyle(*eta, "#eta(#mu)", "events", 0, 1.1*max );
  if(cutLine)drawcutline(-2.1, 1.05*1.1*max);
  if(cutLine)drawcutline( 2.1, 1.05*1.1*max);

  // ---
  //    do the printing for nHit_
  // ---
  min = 0.1/840*luminosity;
  max = getMaxValue(*nHit_[kData], "");
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetLogy(1);
  MyCanvas[2]->SetTitle("trackerHitsLeading"+thoseCollections[2]+"Muons@7TeV");
  nHit        ->Draw("");
  axesStyle(*nHit, "N_{Hits trk}(#mu)", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  nHit_[kData]->Draw("EPsame");
  nHit        ->Draw("AXISsame");
  //  leg4        ->Draw("same");
  //cut0        ->Draw("same");
  if(cutLine)drawcutline(10.5, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for chi2_
  // ---
  min = 0.001/840*luminosity;
  max = getMaxValue(*chi2_[kData], "");
  MyCanvas[3]->cd(0);
  MyCanvas[3]->SetLogy(1);
  MyCanvas[3]->SetTitle("chi2Leading"+thoseCollections[3]+"Muons@7TeV");
  chi2        ->Draw("");
  axesStyle(*chi2, "#chi^{2}(#mu)", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  chi2_[kData]->Draw("EPsame");
  chi2        ->Draw("AXISsame");
  //  leg5        ->Draw("same");
  //cut0        ->Draw("same");
  if(cutLine)drawcutline(10., exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for d0_
  // ---
  min = 0.001/840*luminosity;
  max = getMaxValue(*d0_[kData], "");
  MyCanvas[4]->cd(0);
  MyCanvas[4]->SetTitle("dBLeading"+thoseCollections[4]+"Muons@7TeV");
  MyCanvas[4]->SetLogy(1);
  axesStyle(*d0_[kData], "d_{B}(#mu) [cm]", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  d0_[kData]->GetXaxis()->SetRangeUser(0.,0.2);
  d0_[kData]->Draw("AXIS");
  d0        ->Draw("same");
  d0_[kData]->Draw("EPsame");
  //  leg6      ->Draw("same");
  //cut0      ->Draw("same");
  d0_[kData]->Draw("AXIS same");
  if(cutLine)drawcutline(0.02, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for dz_
  // ---
  min = 0.1/840*luminosity;
  max = getMaxValue(*dz_[kData], "");
  MyCanvas[5]->cd(0);
  MyCanvas[5]->SetLogy(1);
  MyCanvas[5]->SetTitle("dzLeading"+thoseCollections[5]+"Muons@7TeV");
  axesStyle(*dz_[kData], "d_{z}(#mu)", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  dz_[kData]->Draw("AXIS"  );
  dz        ->Draw("same"  );
  dz_[kData]->Draw("EPsame");
  //  leg7      ->Draw("same");
  //cut0      ->Draw("same");

  // ---
  //    do the printing for ecalEn_
  // ---
  min = 0.001/840*luminosity;
  max = getMaxValue(*ecalEn_[kData], "");
  MyCanvas[6]->cd(0);
  MyCanvas[6]->SetLogy(1);
  MyCanvas[6]->SetTitle("ecalEnLeading"+thoseCollections[6]+"Muons@7TeV");
  ecalEn        ->Draw();
  axesStyle(*ecalEn, "E_{Ecal}(#mu) [GeV]", "events" , min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  ecalEn_[kData]->Draw("EPsame");
  ecalEn        ->Draw("AXISsame");
  //  leg8          ->Draw("same");
  //cut0          ->Draw("same");
  
  // ---
  //    do the printing for hcalEn_
  // ---
  min = 0.01/840*luminosity;
  max = getMaxValue(*hcalEn_[kData], "");
  MyCanvas[7]->cd(0);
  MyCanvas[7]->SetLogy(1);
  MyCanvas[7]->SetTitle("hcalEnLeading"+thoseCollections[7]+"Muons@7TeV");
  hcalEn        ->Draw();
  axesStyle(*hcalEn, "E_{Hcal}(#mu) [GeV]", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  hcalEn_[kData]->Draw("EPsame");
  hcalEn        ->Draw("AXISsame");
  //  leg9          ->Draw("same");
  //cut0          ->Draw("same");

  // ---
  //    do the printing for dR_
  // ---
  min = 0.0025*luminosity/1000.;
  max = getMaxValue(*dR_[kData], "");
  MyCanvas[8]->cd(0);
  MyCanvas[8]->SetLogy(1);
  MyCanvas[8]->SetTitle("distance"+thoseCollections[8]+"MuonsVetoJets@7TeV");
  dR        ->Draw();
  axesStyle(*dR, "#DeltaR(#mu - jet(p_{t}>30GeV))", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  dR_[kData]->Draw("EPsame");
  dR        ->Draw("AXISsame");
  //  leg10     ->Draw("same");
  //cut0      ->Draw("same");
  if(cutLine)drawcutline(0.3, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for relIso_
  // ---
  min = 0.01/840*luminosity;
  max = getMaxValue(*relIso_[kData], "");
  MyCanvas[9]->cd(0);
  MyCanvas[9]->SetLogy(1);
  MyCanvas[9]->SetTitle("relIsoLeading"+thoseCollections[9]+"Muons@7TeV");
  relIso        ->Draw();
  axesStyle(*relIso, "relIso(#mu)", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  relIso_[kData]->Draw("EPsame");
  relIso        ->Draw("AXISsame");
  //  leg11         ->Draw("same");
  //cut0          ->Draw("same");
  if(cutLine)drawcutline(0.05, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for n_
  // ---
  min = 0.1/840*luminosity;
  max = getMaxValue(*n_[kData], "");
  MyCanvas[10]->cd(0);
  MyCanvas[10]->SetLogy(1);
  MyCanvas[10]->SetTitle("multiplicity"+thoseCollections[10]+"Muons@7TeV");
  axesStyle(*n_[kData], "N_{#mu}(p_{t}>20GeV)", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  n_[kData]->GetXaxis()->SetRangeUser(0.,3.);
  n_[kData]->Draw("AXIS"  );
  n        ->Draw("same"  );
  n_[kData]->Draw("EPsame");
  //  leg12    ->Draw("same");
  //label("muon selection")->Draw("same");
  //cut0     ->Draw("same");
  n_[kData]->Draw("AXIS same");
  if(cutLine)drawcutline(0.5, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));
  if(cutLine)drawcutline(1.5, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for etaJets_
  // ---
  max = getMaxValue(*etaJets_[kData], "");
  MyCanvas[11]->cd(0);
  //  MyCanvas[11]->SetLogy(1);
  MyCanvas[11]->SetTitle("etaAll"+thoseCollections[11]+"Jets@7TeV");
  //  axesStyle(*etaJets, "#eta (all jets)", "events", 1.0/840*luminosity, 0.1*etaJets->GetMaximum()*luminosity );
  axesStyle(*etaJets_[kData], "#eta(all jets)", "events", 0., 1.1*max );
  etaJets_[kData]->Draw("AXIS");
  etaJets        ->Draw("same"); 
  etaJets_[kData]->Draw("EPsame");
  //  leg13          ->Draw("same");
  //cut2           ->Draw("same");
  etaJets_[kData]->Draw("AXIS same");
  if(cutLine)drawcutline(-2.4, 1.1*max);
  if(cutLine)drawcutline( 2.4, 1.1*max);

  // ---
  //    do the printing for ptlead1Jet_
  // ---
  min = 0.01*luminosity/1000.;
  max = getMaxValue(*ptlead1Jet_[kData], "");
  MyCanvas[12]->cd(0);
  MyCanvas[12]->SetLogy(1);
  MyCanvas[12]->SetTitle("pt1stLeading"+thoseCollections[12]+"Jet@7TeV");
  ptlead1Jet_[kData]->GetXaxis()->SetRangeUser(0.,400.); 
  axesStyle(*ptlead1Jet_[kData], "p_{t}(jet 1) [GeV]", "events", min, exp(1.05*(std::log(max)-std::log(min))+std::log(min)) );
  ptlead1Jet_[kData]->Draw("EP");
  ptlead1Jet        ->Draw("same"); 
  ptlead1Jet_[kData]->Draw("EPsame");
  //  leg14             ->Draw("same");
  //cut2              ->Draw("same");
  if(cutLine)drawcutline(30.0, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for ptlead2Jet_
  // ---
  min = 0.01*luminosity/1000.;
  max = getMaxValue(*ptlead2Jet_[kData], "");
  MyCanvas[13]->cd(0);
  MyCanvas[13]->SetLogy(1);
  MyCanvas[13]->SetTitle("pt2ndLeading"+thoseCollections[12]+"Jet@7TeV");
  ptlead2Jet_[kData]->GetXaxis()->SetRangeUser(0.,400.); 
  axesStyle(*ptlead2Jet_[kData], "p_{t}(jet 2) [GeV]", "events", min, exp(1.05*(std::log(max)-std::log(min))+std::log(min)) );
  ptlead2Jet_[kData]->Draw("EP");
  ptlead2Jet        ->Draw("same");
  ptlead2Jet_[kData]->Draw("EPsame");
  //  leg14             ->Draw("same");
  //cut2              ->Draw("same");
  if(cutLine)drawcutline(30.0, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for ptlead3Jet_
  // ---
  min = 0.01*luminosity/1000.;
  max = getMaxValue(*ptlead3Jet_[kData], "");
  MyCanvas[14]->cd(0);
  MyCanvas[14]->SetLogy(1);
  MyCanvas[14]->SetTitle("pt3rdLeading"+thoseCollections[12]+"Jet@7TeV");
  ptlead3Jet_[kData]->GetXaxis()->SetRangeUser(0.,150.); 
  axesStyle(*ptlead3Jet_[kData], "p_{t}(jet 3) [GeV]", "events", min, exp(1.05*(std::log(max)-std::log(min))+std::log(min)) );
  ptlead3Jet_[kData]->Draw("EP");
  ptlead3Jet        ->Draw("same");
  ptlead3Jet_[kData]->Draw("EPsame");
  //  leg14             ->Draw("same");
  //cut2              ->Draw("same");
  if(cutLine)drawcutline(30.0, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for ptlead4Jet_
  // ---
  min = 0.01*luminosity/1000.;
  max = getMaxValue(*ptlead4Jet_[kData], "");
  MyCanvas[15]->cd(0);
  MyCanvas[15]->SetLogy(1);
  MyCanvas[15]->SetTitle("pt4thLeading"+thoseCollections[12]+"Jet@7TeV");
  ptlead4Jet_[kData]->GetXaxis()->SetRangeUser(0.,150.);
  axesStyle(*ptlead4Jet_[kData], "p_{t}(jet 4) [GeV]", "events", min, exp(1.05*(std::log(max)-std::log(min))+std::log(min)) );
  ptlead4Jet_[kData]->Draw("EP");
  ptlead4Jet        ->Draw("same"); 
  ptlead4Jet_[kData]->Draw("EPsame");
  //  leg14             ->Draw("same");
  //cut2              ->Draw("same");
  if(cutLine)drawcutline(30.0, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for emf_
  // ---
  if(jetTyp==""){
    min = 0.1/840*luminosity;
    max = getMaxValue(*emf_[kData], "");
    MyCanvas[16]->cd(0);
    MyCanvas[16]->SetLogy(1);
    MyCanvas[16]->SetTitle("electromagneticFraction"+thoseCollections[13]+"Jets@7TeV");
    emf        ->Draw();
    axesStyle(*emf, "em fraction", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
    emf_[kData]->Draw("EPsame");
    emf        ->Draw("Axis same");
    //  leg15      ->Draw("same");
    //cut2       ->Draw("same");
    if(cutLine)drawcutline(0.01, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));
  }
  // ---
  //    do the printing for nVetoMu_
  // ---
  min = 0.1/840*luminosity;
  max = getMaxValue(*nVetoMu_[kData], "");
  MyCanvas[17]->cd(0);
  MyCanvas[17]->SetLogy(1);
  MyCanvas[17]->SetTitle("multiplicityLooseMuons@7TeV");
  axesStyle(*nVetoMu_[kData], "N_{#mu}(p_{t}>10GeV)", "events",  min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  nVetoMu_[kData]->GetXaxis()->SetRangeUser(0.,3.);
  nVetoMu_[kData]->Draw("Axis");
  nVetoMu        ->Draw("same");
  nVetoMu_[kData]->Draw("EPsame");
  //  leg16          ->Draw("same");
  //label("muon veto")->Draw("same");
  //cut1           ->Draw("same");
  nVetoMu_[kData]->Draw("Axis same");
  if(cutLine)drawcutline(0.5, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));
  if(cutLine)drawcutline(1.5, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for nVetoE_
  // ---
  min = 0.01/840*luminosity;
  max = getMaxValue(*nVetoE_[kData], "");
  MyCanvas[18]->cd(0);
  MyCanvas[18]->SetLogy(1);
  MyCanvas[18]->SetTitle("multiplicityLooseElectrons@7TeV");
  axesStyle(*nVetoE_[kData], "N_{e}(p_{t}>15GeV)", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  nVetoE_[kData]->GetXaxis()->SetRangeUser(-0.5, 2.5);
  nVetoE_[kData]->Draw("Axis");
  nVetoE        ->Draw("same");
  nVetoE_[kData]->Draw("EPsame");
  //  leg17         ->Draw("same");
  //label("electron veto")->Draw("same");
  //cut1                  ->Draw("same");
  nVetoE_[kData]->Draw("Axis same");
  if(cutLine)drawcutline(0.5, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  if(jetTyp==""){
    // ---
    //    do the printing for fhpd_
    // ---
    min = 0.01/840*luminosity;
    max = getMaxValue(*fhpd_[kData], "");
    MyCanvas[19]->cd(0);
    MyCanvas[19]->SetLogy(1);
    MyCanvas[19]->SetTitle("fHPD"+thoseCollections[14]+"Jets@7TeV");
    fhpd        ->Draw();
    axesStyle(*fhpd, "fHPD", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
    fhpd_[kData]->Draw("EPsame");
    fhpd        ->Draw("Axis same");
    //  leg18       ->Draw("same");
    //cut2        ->Draw("same");
    if(cutLine)drawcutline(0.98, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));
    
    // ---
    //    do the printing for n90hits_
    // ---
    min = 0.01/840*luminosity;
    max = getMaxValue(*n90hits_[kData], "");
    MyCanvas[20]->cd(0);
    MyCanvas[20]->SetLogy(1);
    MyCanvas[20]->SetTitle("n90hits"+thoseCollections[15]+"Jets@7TeV");
    n90hits        ->Draw();
    axesStyle(*n90hits, "n90Hits", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
    n90hits_[kData]->Draw("EPsame");
    n90hits        ->Draw("Axis same");
    //  leg19          ->Draw("same");
    //cut2           ->Draw("same");
    if(cutLine)drawcutline(1.0, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));
  }
  // ---
  //    do the printing for nJets_
  // ---
  min = 0.99;
  max = getMaxValue(*nJets_[kData], "");
  MyCanvas[21]->cd(0);
  MyCanvas[21]->SetLogy(1);
  MyCanvas[21]->SetTitle("nJets"+thoseCollections[16]+"Jets@7TeV");
  axesStyle(*nJets_[kData], "N_{jets}(p_{t}>30GeV)", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  nJets_[kData]->GetXaxis()->CenterLabels();
  nJets_[kData]->GetXaxis()->SetNdivisions(510);
  nJets_[kData]->Draw("AXIS"  );
  nJets        ->Draw("same"  );
  nJets_[kData]->Draw("EPsame");
  //  leg20        ->Draw("same");
  //label("jet selection")->Draw("same");
  //cut2         ->Draw("same");
  nJets_[kData]->Draw("AXIS same");
  if(cutLine)drawcutline(4.0, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for bdiscr_
  // ---
  min = 0.1/840*luminosity;
  max = getMaxValue(*bdiscr_[kData], "");
  MyCanvas[22]->cd(0);
  MyCanvas[22]->SetLogy(1);
  MyCanvas[22]->SetTitle("bdiscr"+thoseCollections[17]+"Jets@7TeV");
  axesStyle(*bdiscr_[kData], "b-discr.(tche)", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  bdiscr_[kData]->Draw("Axis");
  bdiscr        ->Draw("same");
  bdiscr_[kData]->Draw("EPsame");
  //  leg21         ->Draw("same");
  //cut3          ->Draw("same");
  bdiscr_[kData]->Draw("Axis same");
  if(cutLine)drawcutline(3.3, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for bdiscrPre_
  // ---
  min = 0.1/840*luminosity;
  max = getMaxValue(*bdiscrPre_[kData], "");
  MyCanvas[23]->cd(0);
  MyCanvas[23]->SetLogy(1);
  MyCanvas[23]->SetTitle("bdiscrPre"+thoseCollections[17]+"Jets@7TeV");
  bdiscrPre        ->Draw();
  axesStyle(*bdiscrPre, "b-discr.(tche)", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  bdiscrPre_[kData]->Draw("EPsame");
  bdiscrPre        ->Draw("Axis same");
  //  leg21            ->Draw("same");
  //cut0             ->Draw("same");
  if(cutLine)drawcutline(3.3, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for nbJets_
  // ---
  min = 0.1/840*luminosity;
  max = getMaxValue(*nbJets_[kData], "");
  MyCanvas[24]->cd(0);
  MyCanvas[24]->SetLogy(1);
  MyCanvas[24]->SetTitle("nbJets"+thoseCollections[18]+"Jets@7TeV");
  axesStyle(*nbJets_[kData], "N_{b-jets}(tche-mWP)", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  nbJets_[kData]->GetXaxis()->SetRangeUser(0.,3.);
  nbJets_[kData]->GetXaxis()->CenterLabels();
  nbJets_[kData]->Draw("Axis");
  nbJets        ->Draw("same");
  nbJets_[kData]->Draw("EPsame");
  //  leg22         ->Draw("same");
  //cut3          ->Draw("same");
  nbJets_[kData]->Draw("Axis same");
  if(cutLine)drawcutline(1.0, exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for common event Selection legend
  // ---
  MyCanvas[25]->cd(0);
  MyCanvas[25]->SetTitle("legendEventSelection@7TeV");
  leg0->Draw("");

  // ---
  //    do the printing for etVetoE_
  // ---
  min = 0.01/840*luminosity;
  max = getMaxValue(*etVetoE_[kData], "");
  MyCanvas[26]->cd(0);
  MyCanvas[26]->SetLogy(1);
  MyCanvas[26]->SetTitle("ptPatVetoElectrons@7TeV");
  etVetoE     ->Draw();
  axesStyle(*etVetoE, "E_{t}(e) [GeV]", "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
  etVetoE_[kData]->Draw("EPsame");
  etVetoE        ->Draw("Axis same");
  //cut1           ->Draw("same");
  //  leg23          ->Draw("same");
  if(cutLine)drawcutline(15., exp(1.15*(std::log(max)-std::log(min))+std::log(min)));

  // ---
  //    do the printing for etaVetoE_
  // ---
  max = getMaxValue(*etaVetoE_[kData], "");
  MyCanvas[27]->cd(0);
  //  MyCanvas[27]->SetLogy(1);
  MyCanvas[27]->SetTitle("etaPatVetoElectrons@7TeV");
  etaVetoE    ->Draw();
  //  axesStyle(*etaVetoE, "#eta ( e )", "events", 0.01/840*luminosity, 1.0*etaVetoE->GetMaximum()*luminosity );
  axesStyle(*etaVetoE, "#eta(e)", "events", 0., 1.1*max );
  //  if(etaVetoE->GetMinimum()/12.38*luminosity==0)etaVetoE->SetMinimum(0.01);
  etaVetoE_[kData]->Draw("EPsame");
  etaVetoE        ->Draw("Axis same");
  //  leg23           ->Draw("same");
  //cut1            ->Draw("same");
  if(cutLine)drawcutline( 2.5, 1.1*max); 
  if(cutLine)drawcutline(-2.5, 1.1*max);

  // ---
  //    do the printing for relIsoVetoE_
  // ---
  max = getMaxValue(*relIsoVetoE_[kData], "");
  MyCanvas[28]->cd(0);
  //  MyCanvas[28]->SetLogy(1);
  MyCanvas[28]->SetTitle("relIsoPatVetoElectrons@7TeV");
  relIsoVetoE    ->Draw();
  axesStyle(*relIsoVetoE, "relIso(e)", "events", 0., 1.1*max );
  relIsoVetoE_[kData]->Draw("EPsame");
  relIsoVetoE        ->Draw("Axis same");

  // ---
  // saving
  // ---

  if(save){
    // ps
    MyCanvas[0]->Print(saveTo+plots+"7TeV"+lum2+"nb.pdf(", "pdf");
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+plots+"7TeV"+lum2+"nb.pdf", "pdf");
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+plots+"7TeV"+lum2+"nb.pdf)", "pdf");
 
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

template <class T>
void axesStyle(T& hist, const char* titleX, const char* titleY, float yMin, float yMax, float yTitleSize, float yTitleOffset) 
{
  hist.SetTitle("");
  hist.GetXaxis()->SetTitle(titleX);
  //hist.GetXaxis()->CenterTitle();
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
  //hist.GetYaxis()->CenterTitle   ( true);
  if(yMin!=-123) hist.SetMinimum(yMin);
  if(yMax!=-123) hist.SetMaximum(yMax);
}

// TPaveLabel* label(TString text, double xmin, double ymin, double xmax, double ymax, double size){
//   // label indicating cutstep
//   TPaveLabel *label = new TPaveLabel(xmin, ymin, xmax, ymax, text, "br NDC");
//   label->SetFillStyle(0);
//   label->SetBorderSize(0);
//   label->SetTextSize(size);
//   return label;
// }

int roundToInt(double value, bool roundDown){
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
  if(roundDown==false&&(value-result) >=0.5) return (result+1);
  return result;
}

TString getTStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return (TString)result;
}

TString getTStringFromDouble(double d){
  int roundedInt = roundToInt(d, true);
  TString number = getTStringFromInt(roundedInt);
  int decimal1   = roundToInt((d-(double)roundedInt)*10);
  TString dec1    = getTStringFromInt(decimal1);
  TString result = number+"."+dec1;
  return result;
}
