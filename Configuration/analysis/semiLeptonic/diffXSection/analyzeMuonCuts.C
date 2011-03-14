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

void analyzeMuonCuts(double luminosity = 35900, bool save = false, TString dataFile="./diffXSecFromSignal/data/DiffXSecData_L1OffPF.root", TString plots = "NminusOne", TString jetTyp = "PF")
{
  // ---
  //    main function parameters
  // ---
  // save:       choose whether you want to save every plot as eps and all within one ps file
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
  TString whichSample = "/analysisRootFiles";
  for(int ienum = 0; ienum<10; ienum++){
    if(ienum==kSig)files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecSigMadD6TFall10"+jetTyp+".root"    ) );
    if(ienum==kBkg)files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecBkgMadD6TFall10"+jetTyp+".root"    ) );
    //   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecSigNloFall10.root"    ) );
    //   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecBkgNloFall10.root"    ) );
    if(ienum==kSToptW)files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecSingleTopTWchannelMadZ2Fall10"+jetTyp+".root"   ) );
    if(ienum==kSTops) files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecSingleTopSchannelMadZ2Fall10"+jetTyp+".root"   ) );
    if(ienum==kSTopt) files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecSingleTopTchannelMadZ2Fall10"+jetTyp+".root"   ) );
    if(ienum==kZjets)files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecZjetsMadD6TFall10"+jetTyp+".root"  ) );
    if(ienum==kWjets)files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecWjetsMadD6TFall10"+jetTyp+".root"  ) );
    if(ienum==kDiBos)files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecVVPytia6Z2Fall10"+jetTyp+".root"  ) );
    if(ienum==kQCD)  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecQCDPythiaZ2Fall10"+jetTyp+".root" ) );
    if(ienum==kData) files_.push_back(new TFile(dataFile                                                             ) );
  }
  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight_;
  // add scaling factors here!

  // 7 TeV Monte Carlo fall 10 samples
  // -----------------------------------
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    // for current ttbar(lept.mu on gen level and other) Madgraph 
    if(idx==kSig || idx==kBkg)lumiweight_.push_back(0.000006029022/50.0*luminosity);
    // for current W+jets MADGRAPH sample
    if(idx==kWjets)lumiweight_.push_back(0.000105750913/50.0*luminosity);
    // for current Z+jets MADGRAPH sample
    if(idx==kZjets)lumiweight_.push_back(0.000059912090/50.0*luminosity);
    // for current DiBoson PYTHIA sample
    if(idx==kDiBos)lumiweight_.push_back(0.001/50.0*luminosity);
    // for current single top MADGRAPH Z2 samples
    if(idx==kSTops)lumiweight_.push_back(0.324*0.000000464677/50.0*luminosity);
    if(idx==kSTopt)lumiweight_.push_back(0.324*0.000006672727/50.0*luminosity);
    if(idx==kSToptW)lumiweight_.push_back(0.000001070791/50.0*luminosity);
    // for current QCD PYTHIA sample
    if(idx==kQCD)lumiweight_.push_back(0.000002870*(double)luminosity);
  }

  // ---
  //    get histograms
  // ---

  // choose the collections to monitor don't change order
  std::vector<TString> thoseCollections_;
  TString thoseCollectionsNminus1[34] = {"noPt", "noEta", "noTrkHits", "noChi2", "noDb", "tight", "tight", "tight", "noDR", "noIso", "tight", "noEta", "noPt", "noPt", "noPt", "noPt", "tight", "noEm", "nofHPD", "noN90Hits", "reliable", "reliable", "reliable", "reliable", "reliable", "reliable", "tight", "bottom", "tight", "loose", "loose", "pat", "pat", "pat"};
  TString thoseCollectionsCutFlow[34] = {"combined", "highPt", "kinematic", "kinematic", "kinematic", "tight", "tight", "tight", "track", "golden", "tight", "pat", "central", "central", "central", "central", "tight", "reliable", "reliable", "reliable", "reliable", "reliable", "reliable", "reliable", "reliable", "reliable", "tight", "bottom", "tight", "loose", "loose", "pat", "pat", "pat"};
  // a) NminusOne
  if(plots=="NminusOne"){
    thoseCollections_.insert( thoseCollections_.begin(), thoseCollectionsNminus1, thoseCollectionsNminus1 + 34 );
  }
  // b) cutflow
  if(plots=="cutflow"){
    thoseCollections_.insert( thoseCollections_.begin(), thoseCollectionsCutFlow, thoseCollectionsCutFlow + 34 );
  }  

  // create variable indicator  don't change order
  std::vector<TString> variables_;
  TString variables[ 34 ] = { "MuonKinematics/pt", "MuonKinematics/eta", "MuonQuality/nHit", "MuonQuality/chi2", "MuonQuality/dB", "MuonQuality/dz", "MuonQuality/ecalEn", "MuonQuality/hcalEn", "MuonVetoJetsKinematics/dist30_", "MuonQuality/relIso", "MuonKinematics/n", "JetKinematics/eta", "Lead_0_JetKinematics/pt", "Lead_1_JetKinematics/pt", "Lead_2_JetKinematics/pt", "Lead_3_JetKinematics/pt", "JetKinematics/n", "JetQuality/emf", "JetQuality/fhpd_", "JetQuality/n90hits_", "JetQuality/chf", "JetQuality/nhf", "JetQuality/cef", "JetQuality/nef", "JetQuality/ncp", "JetQuality/n_", "JetQuality/btagTrkCntHighEff_", "JetKinematics/n", "JetQualityBeforeJetCuts/btagTrkCntHighEff_", "VetoMuonKinematics/n", "VetoElectronKinematics/n", "VetoElectronKinematics/et", "VetoElectronKinematics/eta", "VetoElectronQuality/relIso" };
  variables_.insert( variables_.begin(), variables, variables + 34 );
  // create container for all histos
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  // create container for stack histos
  std::map< TString, THStack*> stack_;
  // loop variables
  for(unsigned int var=0; var<variables_.size(); ++var){
    histo_[thoseCollections_[var]+variables_[var]][kSTop] = 0;
    stack_[thoseCollections_[var]+variables_[var]] = new THStack( thoseCollections_[var]+variables_[var],"");
    // loop samples
    int STopCount = 0;
    for(unsigned int idx=0; idx<files_.size(); ++idx) {
      // a) reco
      if((jetTyp=="PF" && (var>=17 && var<=19)) || (jetTyp=="" && (var>=20 && var<=25)))continue;
      // allocate histograms
      histo_[thoseCollections_[var]+variables_[var]][idx] = (TH1F*)files_[idx]->Get(thoseCollections_[var]+variables_[var]);
      // histogram styles
      histogramStyle(*histo_[thoseCollections_[var]+variables_[var]][idx], idx);
      if(idx!=kData){
	// normalize histograms to lumi
	histo_[thoseCollections_[var]+variables_[var]][idx]->Scale(lumiweight_[idx]);
	// combine single top histograms
	if(idx==kSTops || idx==kSTopt || idx==kSToptW){
	  STopCount++;
	  if(!histo_[thoseCollections_[var]+variables_[var]][kSTop])histo_[thoseCollections_[var]+variables_[var]][kSTop] = (TH1F*)histo_[thoseCollections_[var]+variables_[var]][idx]->Clone();
	  else histo_[thoseCollections_[var]+variables_[var]][kSTop]->Add(histo_[thoseCollections_[var]+variables_[var]][idx]);
	  if(STopCount==3)stack_[thoseCollections_[var]+variables_[var]]->Add(histo_[thoseCollections_[var]+variables_[var]][kSTop]);
	}
	// create stacks
	else stack_[thoseCollections_[var]+variables_[var]]->Add(histo_[thoseCollections_[var]+variables_[var]][idx]);
      }
    }
  }

  // get number of events after muon selection and lepton veto
  // loop sample
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    // get histo
    histo_["eventsAfterLeptonVeto"   ][idx] = (TH1F*)files_[idx]->Get("bottomJetKinematicsBeforeJetCuts/n");
    histo_["eventsAfterMuonSelection"][idx] = (TH1F*)files_[idx]->Get("tightMuonKinematics/n"             );
    // weight histo
    if(idx!=kData){
      histo_["eventsAfterLeptonVeto"   ][idx]->Scale(lumiweight_[idx]);
      //      histo_["eventsAfterMuonSelection"][idx]->Scale(lumiweight_[idx]); 
      // -> already done above!!!!
    }
  }

  // ---
  //    print out # events ( MC / Data)
  // ---
  // a) after muon selection
  std::cout << "---------------------" << std::endl;
  std::cout << "number of entries == 1 muon" << std::endl;
  std::cout << "ttbar sig : " << histo_["eventsAfterMuonSelection"][kSig  ]->GetBinContent(2) << std::endl;
  std::cout << "ttbar bkg : " << histo_["eventsAfterMuonSelection"][kBkg  ]->GetBinContent(2) << std::endl;
  std::cout << "QCD : "       << histo_["eventsAfterMuonSelection"][kQCD  ]->GetBinContent(2) << std::endl;
  std::cout << "Z+jets : "    << histo_["eventsAfterMuonSelection"][kZjets]->GetBinContent(2) << std::endl;
  std::cout << "W+jets : "    << histo_["eventsAfterMuonSelection"][kWjets]->GetBinContent(2) << std::endl;
  std::cout << "DiBoson : "   << histo_["eventsAfterMuonSelection"][kDiBos]->GetBinContent(2) << std::endl;
  std::cout << "single top : "<< (histo_["eventsAfterMuonSelection"][kSTops]->GetBinContent(2))+(histo_["eventsAfterMuonSelection"][kSTopt]->GetBinContent(2))+(histo_["eventsAfterMuonSelection"][kSToptW]->GetBinContent(2)) << std::endl;
  std::cout << "all MC: " << histo_["eventsAfterMuonSelection"][kSig]->GetBinContent(2)+histo_["eventsAfterMuonSelection"][kBkg]->GetBinContent(2)+histo_["eventsAfterMuonSelection"][kQCD]->GetBinContent(2)+histo_["eventsAfterMuonSelection"][kZjets]->GetBinContent(2)+histo_["eventsAfterMuonSelection"][kWjets]->GetBinContent(2)+histo_["eventsAfterMuonSelection"][kDiBos]->GetBinContent(2)+histo_["eventsAfterMuonSelection"][kSTops]->GetBinContent(2)+histo_["eventsAfterMuonSelection"][kSTopt]->GetBinContent(2)+histo_["eventsAfterMuonSelection"][kSToptW]->GetBinContent(2) << std::endl;
  std::cout << "data : "      << histo_["eventsAfterMuonSelection"][kData ]->GetBinContent(2) << std::endl<< std::endl;
  // b) after lepton veto
  std::cout << "---------------------" << std::endl;
  std::cout << "number of entries after lepton veto" << std::endl;
  std::cout << "ttbar sig : " << histo_["eventsAfterLeptonVeto"][kSig  ]->Integral(0,histo_["eventsAfterLeptonVeto"][kSig]->GetNbinsX()+1) << std::endl;
  std::cout << "ttbar bkg : " << histo_["eventsAfterLeptonVeto"][kBkg  ]->Integral(0,histo_["eventsAfterLeptonVeto"][kBkg]->GetNbinsX()+1) << std::endl;
  std::cout << "QCD : "       << histo_["eventsAfterLeptonVeto"][kQCD  ]->Integral(0,histo_["eventsAfterLeptonVeto"][kQCD]->GetNbinsX()+1) << std::endl;
  std::cout << "Z+jets : "    << histo_["eventsAfterLeptonVeto"][kZjets]->Integral(0,histo_["eventsAfterLeptonVeto"][kZjets]->GetNbinsX()+1) << std::endl;
  std::cout << "W+jets : "    << histo_["eventsAfterLeptonVeto"][kWjets]->Integral(0,histo_["eventsAfterLeptonVeto"][kWjets]->GetNbinsX()+1) << std::endl;
  std::cout << "DiBoson : "   << histo_["eventsAfterLeptonVeto"][kDiBos]->Integral(0,histo_["eventsAfterLeptonVeto"][kDiBos]->GetNbinsX()+1) << std::endl;
  std::cout << "single top : "<< (histo_["eventsAfterLeptonVeto"][kSTops]->Integral(0,histo_["eventsAfterLeptonVeto"][kSTops]->GetNbinsX()+1))+(histo_["eventsAfterLeptonVeto"][kSTopt]->Integral(0,histo_["eventsAfterLeptonVeto"][kSTopt]->GetNbinsX()+1))+(histo_["eventsAfterLeptonVeto"][kSToptW]->Integral(0,histo_["eventsAfterLeptonVeto"][kSToptW]->GetNbinsX()+1)) << std::endl;
  std::cout << "all MC: " << histo_["eventsAfterLeptonVeto"][kSig]->Integral(0,histo_["eventsAfterLeptonVeto"][kSig]->GetNbinsX()+1)+histo_["eventsAfterLeptonVeto"][kBkg]->Integral(0,histo_["eventsAfterLeptonVeto"][kBkg]->GetNbinsX()+1)+histo_["eventsAfterLeptonVeto"][kQCD]->Integral(0,histo_["eventsAfterLeptonVeto"][kQCD]->GetNbinsX()+1)+histo_["eventsAfterLeptonVeto"][kZjets]->Integral(0,histo_["eventsAfterLeptonVeto"][kZjets]->GetNbinsX()+1)+histo_["eventsAfterLeptonVeto"][kWjets]->Integral(0,histo_["eventsAfterLeptonVeto"][kWjets]->GetNbinsX()+1)+histo_["eventsAfterLeptonVeto"][kDiBos]->Integral(0,histo_["eventsAfterLeptonVeto"][kDiBos]->GetNbinsX()+1)+histo_["eventsAfterLeptonVeto"][kSTops]->Integral(0,histo_["eventsAfterLeptonVeto"][kSTops]->GetNbinsX()+1)+histo_["eventsAfterLeptonVeto"][kSTopt]->Integral(0,histo_["eventsAfterLeptonVeto"][kSTopt]->GetNbinsX()+1)+histo_["eventsAfterLeptonVeto"][kSToptW]->Integral(0,histo_["eventsAfterLeptonVeto"][kSToptW]->GetNbinsX()+1) << std::endl;
  std::cout << "data : "      << histo_["eventsAfterLeptonVeto"][kData ]->Integral(0,histo_["eventsAfterLeptonVeto"][kData]->GetNbinsX()+1) << std::endl<< std::endl;
  // c) jet multiplicities
  for(int mult=2; mult<=10; ++mult){
   std::cout << "---------------------" << std::endl;
    std::cout << "number of entries =="+getTStringFromInt(mult-1)+" jets" << std::endl;
    std::cout << "ttbar sig : " << histo_["tightJetKinematics/n"][kSig  ]->GetBinContent(mult) << std::endl;
    std::cout << "ttbar bkg : " << histo_["tightJetKinematics/n"][kBkg  ]->GetBinContent(mult) << std::endl;
    std::cout << "QCD : "       << histo_["tightJetKinematics/n"][kQCD  ]->GetBinContent(mult) << std::endl;
    std::cout << "Z+jets : "    << histo_["tightJetKinematics/n"][kZjets]->GetBinContent(mult) << std::endl;
    std::cout << "W+jets : "    << histo_["tightJetKinematics/n"][kWjets]->GetBinContent(mult) << std::endl;
    std::cout << "DiBoson : "   << histo_["tightJetKinematics/n"][kDiBos]->GetBinContent(mult) << std::endl;
    std::cout << "single top : "<< histo_["tightJetKinematics/n"][kSTop ]->GetBinContent(mult) << std::endl;
    std::cout << "all MC: " << histo_["tightJetKinematics/n"][kSig]->GetBinContent(mult)+histo_["tightJetKinematics/n"][kBkg]->GetBinContent(mult)+histo_["tightJetKinematics/n"][kQCD]->GetBinContent(mult)+histo_["tightJetKinematics/n"][kZjets]->GetBinContent(mult)+histo_["tightJetKinematics/n"][kWjets]->GetBinContent(mult)+histo_["tightJetKinematics/n"][kSTop]->GetBinContent(mult)+histo_["tightJetKinematics/n"][kDiBos]->GetBinContent(mult) << std::endl;
    std::cout << "data : "      << histo_["tightJetKinematics/n"][kData      ]->GetBinContent(mult) << std::endl<< std::endl;
  }

  // ---
  //    create legend
  // ---
  // samples: separate canvas
  TLegend *leg0 = new TLegend(0.08, 0.19, 0.94, 0.88);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->AddEntry( histo_["tightJetKinematics/n"][kData ] , "Data ("+lum+" pb ^{-1})"       , "PL");
  leg0->AddEntry( histo_["tightJetKinematics/n"][kQCD  ] , "QCD"                           , "F" );
  leg0->AddEntry( histo_["tightJetKinematics/n"][kWjets] , "W#rightarrowl#nu"              , "F" );
  leg0->AddEntry( histo_["tightJetKinematics/n"][kSTop ] , "Single-Top", "F" );
  leg0->AddEntry( histo_["tightJetKinematics/n"][kZjets] , "Z/#gamma*#rightarrowl^{+}l^{-}", "F" );
  leg0->AddEntry( histo_["tightJetKinematics/n"][kBkg  ] , "t#bar{t} other"                , "F" );
  leg0->AddEntry( histo_["tightJetKinematics/n"][kSig  ] , "t#bar{t} signal ( #mu prompt )"  , "F" );
  leg0->AddEntry( histo_["tightJetKinematics/n"][kDiBos] , "VV"                            , "F" );

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;
  //int nCanvas = 34;
  //if(jetTyp=="PF") nCanvas+=3;
  for(unsigned int idx=0; idx<=variables_.size(); idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ---
  //    do the printing
  // ---
  std::vector<TString> plotNames_;// don't change order
  TString plotNames[ 34 ] = { "ptLeading","etaLeading","trackerHitsLeading","chi2Leading","dBLeading","dzLeading","ecalEnLeading","hcalEnLeading","distance","relIsoLeading","multiplicity","etaAll","pt1stLeading","pt2ndLeading","pt3rdLeading","pt4thLeading","nJets","electromagneticFraction","fHPD","n90hits","chf","nhf","cef","nef","cmult","nConst","bdiscr","nbJets","bdiscrPre","multiplicity","multiplicity","pt","eta","relIso" };
  plotNames_.insert( plotNames_.begin(), plotNames, plotNames + 34 );
  std::vector<TString> axisTitle_;// don't change order
  TString axisTitle[ 34 ] = { "p_{T}(#mu) [GeV]","#eta(#mu)","N_{Hits trk}(#mu)","#chi^{2}(#mu)","d_{B}(#mu) [cm]","d_{z}(#mu)","E_{Ecal}(#mu) [GeV]","E_{Hcal}(#mu) [GeV]","#DeltaR(#mu - jet(p_{T}>30GeV))","relIso(#mu)","N_{#mu}(p_{T}>20GeV)","#eta (all jets)","p_{T}(jet 1) [GeV]","p_{T}(jet 2) [GeV]","p_{T}(jet 3) [GeV]","p_{T}(jet 4) [GeV]","N_{jets}(p_{T}>30GeV)","em fraction","fHPD","n90Hits","E_{had charged} / E","E_{had neutral} / E","E_{em charged} / E","E_{em neutral} / E","N(charged particles)","N(jet constituents)","b-discr.(tche)","N_{b-jets}(tche-mWP)","b-discr.(tche)","N_{#mu}(p_{T}>10GeV)","N_{e}(p_{T}>15GeV)","E_{T}(e) [GeV]","#eta ( e )","relIso(e)" };
  axisTitle_.insert( axisTitle_.begin(), axisTitle, axisTitle + 34 );
  std::vector<double> min_; // don't change order
  double minimum[ 34 ] = { 1,0,1,0.01,0.01,0.1,0.01,0.1,0.1,0.1,0.1,0,0.1,0.1,0.1,0.1,1,0.1/840*luminosity,0.01/840*luminosity,0.1/840*luminosity,1,0.1,0.1,1,1,1,1,1,1,1,1,0.1,0,1};
  min_.insert( min_.begin(), minimum, minimum + 34 );
  // loop variables
  for(unsigned int var=0; var<variables_.size(); ++var){
    // skip calo plots for PF jets
    if((var==17)&&(jetTyp=="PF")) var+=3;
    // skip PF plots for calo jets
    if((var==20)&&(jetTyp!="PF")) var+=6;
    double min = min_[var];
    double max = getMaxValue(*histo_[thoseCollections_[var]+variables_[var]][kData], "");
    if((jetTyp=="PF" && (var>=17 && var<=19)) || (jetTyp=="" && (var>=20 && var<=25)))continue;
    MyCanvas[var]->cd(0);
    if(!variables_[var].Contains("eta"))MyCanvas[var]->SetLogy(1);
    max = getMaxValue(*histo_[thoseCollections_[var]+variables_[var]][kData], "");
    if(variables_[var].Contains("MuonVetoJets"))
      MyCanvas[var]->SetTitle(plotNames_[var]+thoseCollections_[var]+"MuonsVetoJets@7TeV");
    else if(variables_[var].Contains("Lead"))
      MyCanvas[var]->SetTitle(plotNames_[var]+thoseCollections_[var]+"Jet@7TeV");
    else if(variables_[var].Contains("VetoMuon"))MyCanvas[var]->SetTitle(plotNames_[var]+"LooseMuons@7TeV");
    else if(variables_[var].Contains("VetoElectron")){
      if(thoseCollections_[var]=="loose")MyCanvas[var]->SetTitle(plotNames_[var]+"LooseElectrons@7TeV");
      else MyCanvas[var]->SetTitle(plotNames_[var]+"PatVetoElectrons@7TeV");
    }
    else if(variables_[var].Contains("Jet")){
      if(thoseCollections_[var]=="reliable")MyCanvas[var]->SetTitle(plotNames_[var]+"ReliableJets@7TeV");
      else MyCanvas[var]->SetTitle(plotNames_[var]+thoseCollections_[var]+"Jets@7TeV");
    }
    else if(variables_[var].Contains("Muon"))
      MyCanvas[var]->SetTitle(plotNames_[var]+thoseCollections_[var]+"Muons@7TeV");
    if(MyCanvas[var]->GetLogy())axesStyle(*histo_[thoseCollections_[var]+variables_[var]][kData], axisTitle[var], "events", min, exp(1.15*(std::log(max)-std::log(min))+std::log(min)) );
    else axesStyle(*histo_[thoseCollections_[var]+variables_[var]][kData], axisTitle[var], "events", min, 1.15*max );
    // restrict axes (ptmu,nbjets,dB,nmuons,ptlead4jets)
    if(variables_[var]=="MuonKinematics/pt")histo_[thoseCollections_[var]+variables_[var]][kData]->GetXaxis()->SetRangeUser(20.,150.);
    if(var==27)histo_[thoseCollections_[var]+variables_[var]][kData]->GetXaxis()->SetRangeUser(0.,3.  );
    if(var==4 )histo_[thoseCollections_[var]+variables_[var]][kData]->GetXaxis()->SetRangeUser(0.,0.2 );
    if(var==10)histo_[thoseCollections_[var]+variables_[var]][kData]->GetXaxis()->SetRangeUser(1.,3.  );
    if((var==12)||(var==13))histo_[thoseCollections_[var]+variables_[var]][kData]->GetXaxis()->SetRangeUser(0.,400.);
    if((var==14)||(var==15))histo_[thoseCollections_[var]+variables_[var]][kData]->GetXaxis()->SetRangeUser(0.,150.);
    if(var==16)histo_[thoseCollections_[var]+variables_[var]][kData]->GetXaxis()->SetRangeUser(0,9);
    if(var==29)histo_[thoseCollections_[var]+variables_[var]][kData]->GetXaxis()->SetRangeUser(0.,3. );
    if(var==30)histo_[thoseCollections_[var]+variables_[var]][kData]->GetXaxis()->SetRangeUser(-0.5,2.5);

    histo_[thoseCollections_[var]+variables_[var]][kData]->Draw("EP");
    stack_[thoseCollections_[var]+variables_[var]]       ->Draw("same");
    histo_[thoseCollections_[var]+variables_[var]][kData]->Draw("EPsame");
    histo_[thoseCollections_[var]+variables_[var]][kData]->Draw("AXISsame");
  }

  // ---
  //    do the printing for common event Selection legend
  // ---
  MyCanvas[34]->cd(0);
  MyCanvas[34]->SetTitle("legendEventSelection@7TeV");
  leg0->Draw("");

  // ---
  // saving
  // ---
  if(save){
    // pdf
    MyCanvas[0]->Print(saveTo+plots+"7TeV"+lum2+"nb.pdf(", "pdf");
    for(unsigned int var=1; var<MyCanvas.size()-1; var++){
      if((jetTyp=="PF" && (var>=17 && var<=19)) || (jetTyp=="" && (var>=20 && var<=25)))continue;
      MyCanvas[var]->Print(saveTo+plots+"7TeV"+lum2+"nb.pdf", "pdf");
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+plots+"7TeV"+lum2+"nb.pdf)", "pdf");
    // eps
    for(unsigned int var=0; var<MyCanvas.size(); var++){
      if((jetTyp=="PF" && (var>=17 && var<=19)) || (jetTyp=="" && (var>=20 && var<=25)))continue;
      MyCanvas[var]->Print(saveTo+(TString)(MyCanvas[var]->GetTitle())+".eps"); 
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
