#include "basicFunctions.h"

void bothDecayChannelsCombination(double luminosity=4980, bool save=false, unsigned int verbose=0, TString inputFolderName="RecentAnalysisRun",
				  bool pTPlotsLog=false, bool extrapolate=true, bool hadron=false, bool versionNNLO=true){

  // run automatically in batch mode
  gROOT->SetBatch();
    
  // ============================
  //  Set Root Style
  // ============================
  
  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  myStyle.cd();
  TGaxis::SetMaxDigits(2);
  gROOT->SetStyle("HHStyle");
  
  // ============================
  //  Setup
  // ============================
  
  // decay channels
  enum channel {kMuon, kElectron};
    
  // Define variables for combination
  // NOTE: these must also be included in xSecVariables_ in analyzeHypothesisKinFit.C and combineTopDiffXSecUncertainties.C
  std::vector<TString> xSecVariables_;
  //TString xSecVariables[] ={"topPt", "topPtNorm"};
  TString xSecVariables[] ={"topPt", "topY", "ttbarPt", "ttbarY", "ttbarMass", "lepPt" ,"lepEta", "bqPt", "bqEta", "topPtNorm", "topYNorm", "ttbarPtNorm", "ttbarYNorm", "ttbarMassNorm", "lepPtNorm" ,"lepEtaNorm", "bqPtNorm", "bqEtaNorm"};
  xSecVariables_.insert( xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString) );
  
  // ---
  //    create list of systematics to be treated as uncorrelated between electron and muon channel
  // ---
  std::vector<int> uncorrSys_;
  // trigger 
  uncorrSys_.push_back(sysTrigEffSFNormUp         );   
  uncorrSys_.push_back(sysTrigEffSFNormDown       );    
  uncorrSys_.push_back(sysTriggerEffSFShapeUpEta  );
  uncorrSys_.push_back(sysTriggerEffSFShapeDownEta);
  uncorrSys_.push_back(sysTriggerEffSFShapeUpPt   );
  uncorrSys_.push_back(sysTriggerEffSFShapeDownPt );
  // lepton eff
  uncorrSys_.push_back(sysMuEffSFUp               );
  uncorrSys_.push_back(sysMuEffSFDown             ); 

  // Label for datasample
  TString dataSample="2011";
  
  // Choose phase space
    // a) for full PS use extrapolate=true;
  TString PS = extrapolate ? "" : "PhaseSpace";
  // b) for restricted phase space:
  // b1) parton PS: hadron=false
  // b2) hadron PS: hadron=true
  TString LV="Parton";
  if(!extrapolate&&hadron) LV="Hadron";
  if(verbose>1){
    if(extrapolate) std::cout << "full Phase Space will be used!" << std::endl; 
    else std::cout << LV << " level Phase Space will be used!" << std::endl; 
  }
  TString universalplotLabel = extrapolate ? "FullPS" : LV+"LvPS";
  
  // Choose additional theory curves to plot
  // Version 1: data, MadGraph, MC@NLO, POWHEG, NNLO (Kidonakis)
  bool DrawSmoothMadgraph = true;
  bool DrawMCAtNLOPlot    = true;
  bool DrawPOWHEGPlot     = true;
  bool DrawNNLOPlot       = versionNNLO;
  bool DrawMCFMPlot       = false;
  // smooth instead of binned theory curves
  bool smoothcurves=false;
  if(smoothcurves&&!versionNNLO){
    DrawSmoothMadgraph = true;
    DrawPOWHEGPlot     = true;
    DrawMCAtNLOPlot    = true;
	// FIXME: no smooth mc@nlo curve for hadron PS at the moment
    if(hadron) DrawMCAtNLOPlot = false;
  }	
  // add kidonakis plots for full PS
  //if(extrapolate&&smoothcurves) DrawNNLOPlot=true;
  
  //if(extrapolate==false&&hadron==false){
  //  DrawSmoothMadgraph = true;
  //  DrawMCAtNLOPlot = true;
  //  DrawPOWHEGPlot = true;
  //}
  
  // GOSSIE quick fix: cut of m(ttbar) below 345 GeV
  bool cutTtbarMass=true;
  const double constMassRangeLow  =  345.0;
  const double constMassRangeHigh = 1200.0;
  
  // Closure test with reweighted m(ttbar) on parton level
  // will plot additionally the modified diff. norm. xSec on parton level
  bool reweightClosure=false;
  // Zprime pseudo data test: "", "500" or "750"
  TString zprime="";
  // adjust data label
  TString dataLabel = (reweightClosure||zprime!="") ? "Pseudo-Data " : "Data "+dataSample; 
  
  //  Define muon and electron input rootfiles
  std::map<unsigned int, TFile*> files_;
  files_[kMuon    ] = new (TFile)("diffXSecTopSemiMu"  +dataSample+LV+PS+".root");
  files_[kElectron] = new (TFile)("diffXSecTopSemiElec"+dataSample+LV+PS+".root");
  
  // define folders where XSec plots are stored
  TString xSecFolder = "xSec";
  
  // create plot container for combined e+#mu plots
  std::map< TString, std::map <unsigned int, TH1F*> >    histo_;
  std::map< TString, std::map <unsigned int, TCanvas*> > canvas_;
  
  // =============================================================================
  //  Combination for all kinematic variables x systematic variations available
  // =============================================================================
  
  // loop systematic variations
  for(unsigned int sys=sysNo; sys<ENDOFSYSENUM; ++sys){
    TString subfolder=sysLabel(sys);
    // loop variables
    for(unsigned int i=0; i<xSecVariables_.size(); ++i){
      // get canvas
      TCanvas* canvasMu   = (TCanvas*)(files_[kMuon    ]->Get(xSecFolder+"/"+subfolder+"/"+xSecVariables_[i]));
      TCanvas* canvasEl   = (TCanvas*)(files_[kElectron]->Get(xSecFolder+"/"+subfolder+"/"+xSecVariables_[i]));
      TCanvas* canvasTheo = (TCanvas*)(files_[kMuon    ]->Get(xSecFolder+"/"+sysLabel(sysNo)+"/"+xSecVariables_[i]));
      if(canvasMu&&canvasEl&&canvasTheo){
	// get data plots for all systematics
	TString plotName = xSecVariables_[i];
	plotName.ReplaceAll("Norm","");
	TH1F* plotMu   = (TH1F*)canvasMu  ->GetPrimitive(plotName+"kData");
	TH1F* plotEl   = (TH1F*)canvasEl  ->GetPrimitive(plotName+"kData");
	TH1F* plotTheo = (TH1F*)canvasTheo->GetPrimitive(plotName);
	if(!plotTheo){
	  // take care of differing naming convention for hadron level plots
	  if(hadron) plotTheo = (TH1F*)canvasTheo->GetPrimitive(plotName+"Gen");
	  // if theory is not found, load parton level theory plots directly
	  else plotTheo = (TH1F*)canvasTheo->GetPrimitive("analyzeTop"+LV+"LevelKinematics"+PS+"/"+plotName);
	  if(plotTheo) plotTheo->SetName(plotName);
	}
	
	if(plotMu&&plotEl&&plotTheo){ 
	  if(verbose>1){
	    std::cout << "plot "+plotName+"kData in "+xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << " for both channels found!" << std::endl;
	  }
	  
	  // Store information if variable should be drawn normalized
	  bool normalize=xSecVariables_[i].Contains("Norm");
	  
	  // combine the results
	  TH1F* plotCombination=(TH1F*)(plotMu->Clone());
	  plotCombination->Reset("ICESM");
	  if(xSecVariables_[i].Contains("ttbarY")) plotCombination->GetXaxis()->SetRangeUser(-2.49,2.49);
	  if(verbose>1) std::cout << std::endl << xSecVariables_[i] << ":" << std::endl;
	  // check correlation of systematic variation
	  bool correlated=true;
	  for(int j =0; j<uncorrSys_.size(); ++j){
	    if(uncorrSys_[j]==sys&&sys!=sysNo) correlated=false;
	  }
	  // (i) hadronization uncertainty: use Powhwg+Herwig vs McatNlo+Pythia 
	  if (sys==sysHadUp||sys==sysHadDown){
	    errorWeightedMeanCombination(*plotMu, * plotEl, *plotCombination, verbose);
	  }
	  // (ii) uncorrelated uncertainties 
	  if(!correlated){
	    // get standard xSec histos
	    // a) canvas
	    TCanvas* canvasMuStd = (TCanvas*)(files_[kMuon    ]->Get(xSecFolder+"/"+sysLabel(sys)+"/"+xSecVariables_[i]));
	    TCanvas* canvasElStd = (TCanvas*)(files_[kElectron]->Get(xSecFolder+"/"+sysLabel(sys)+"/"+xSecVariables_[i]));
	    // b) plots
	    if(canvasMuStd&&canvasElStd){
	      TH1F* plotMuStd = (TH1F*)canvasMuStd->GetPrimitive(plotName+"kData");
	      TH1F* plotElStd = (TH1F*)canvasElStd->GetPrimitive(plotName+"kData");    
	      // keep one decay channel constant and vary the other one
	      TH1F* plotMuConstElecVaried=(TH1F*)(plotMu->Clone());
	      errorWeightedMeanCombination(*plotMuStd, * plotEl   , *plotMuConstElecVaried, verbose);
	      TH1F* plotMuVariedElecConst=(TH1F*)(plotMu->Clone());
	      errorWeightedMeanCombination(*plotMu   , * plotElStd, *plotMuVariedElecConst, verbose);
	      // loop all bins
	      for(int bin=1; bin<=plotCombination->GetNbinsX(); ++bin){
		// central combined value for this bin
		double stdValue = histo_[xSecVariables_[i]][sysNo]->GetBinContent(bin);
		// calculate relative shift for both channels wrt. central combined value
		double shiftEl=plotMuConstElecVaried->GetBinContent(bin)-stdValue;
		double shiftMu=plotMuVariedElecConst->GetBinContent(bin)-stdValue;
		// add seperate variations in quadrature
		double totalShift=sqrt(shiftEl*shiftEl+shiftMu*shiftMu);
		// save this absolute error wrt. central combined value as final systematic shifted plot
		plotCombination->SetBinContent(bin, stdValue+totalShift);
	      }
	    }
	  }
	  // (iii)other correlated uncertainties: just do error weighted mean
	  else errorWeightedMeanCombination(*plotMu, * plotEl, *plotCombination, verbose);
	  
	  // =================================================
	  //  Additional histos for reweighting closure test
	  // =================================================
	  if(reweightClosure&&sys==sysNo){
	    // get reweighted samples
	    TString muReweighted="/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/muonDiffXSecSigMadD6TSummer11ReweightedttbarMassUpPF.root";
	    TString elReweighted="/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/elecDiffXSecSigMadD6TSummer11ReweightedttbarMassUpPF.root";
	    TFile* mufile = new (TFile)(muReweighted);
	    TFile* elfile = new (TFile)(elReweighted);
	    // get plot
	    TString partonPlot="analyzeTop"+LV+"LevelKinematics"+PS+"/"+plotName;
	    histo_["reweighted"+plotName     ][kSig] = (TH1F*)(mufile->Get(partonPlot)->Clone("mu"+plotName));
	    histo_["reweighted"+plotName+"El"][kSig] = (TH1F*)(elfile->Get(partonPlot)->Clone("el"+plotName));
	    histo_["reweighted"+plotName     ][kSig]->Add(histo_["reweighted"+plotName+"El"][kSig]);
	    // apply standard rebinning
	    std::map<TString, std::vector<double> > binning_ = makeVariableBinning();
	    reBinTH1F(*histo_["reweighted"+plotName][kSig], binning_[plotName], verbose-1);
	    // scale to unit area
	    histo_["reweighted"+plotName][kSig]->Scale(1/histo_["reweighted"+plotName][kSig]->Integral(0,histo_["reweighted"+plotName][kSig]->GetNbinsX()+1));
	    // divide by binwidth
	    histo_["reweighted"+plotName][kSig]=divideByBinwidth(histo_["reweighted"+plotName][kSig], verbose-1);
	    //set style
	    histogramStyle(*histo_["reweighted"+plotName][kSig], kSig, false, 1.2, kRed+1);
	    histo_["reweighted"+plotName][kSig]->SetLineColor(kMagenta);
	  }
	  // =================================================
	  //  Additional histos for z prime closure test
	  // =================================================
	  if(zprime!=""&&sys==sysNo){
	    TString muSig="/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/muonDiffXSecSigMadD6TSummer11PF.root";
	    TString elSig="/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/elecDiffXSecSigMadD6TSummer11PF.root";
	    TString muZprime="/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/muonDiffXSecZPrime_M"+zprime+"_W"+zprime+"0_MadSummer11PF.root";
	    TString elZprime="/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/elecDiffXSecZPrime_M"+zprime+"_W"+zprime+"0_MadSummer11PF.root";
	    TFile* muSigfile = new (TFile)(muSig);
	    TFile* elSigfile = new (TFile)(elSig);
	    TFile* muZprimefile = new (TFile)(muZprime);
	    TFile* elZprimefile = new (TFile)(elZprime);
	    // get plot
	    TString partonPlot="analyzeTop"+LV+"LevelKinematics"+PS+"/"+plotName;
	    histo_["modified"+plotName           ][kSig] = (TH1F*)(muSigfile   ->Get(partonPlot)->Clone("modified"+plotName));
	    histo_["modified"+plotName+"ElSig"   ][kSig] = (TH1F*)(elSigfile   ->Get(partonPlot)->Clone("elSig"+plotName   ));
	    histo_["modified"+plotName+"muZprime"][kSig] = (TH1F*)(muZprimefile->Get(partonPlot)->Clone("zprime"+plotName  ));
	    histo_["modified"+plotName+"ElZprime"][kSig] = (TH1F*)(elZprimefile->Get(partonPlot)->Clone("zprime"+plotName  ));
	    // relative apply lumiweight- needed because these are different samples (lumi-values defined in basicFunction.h)
	    histo_["modified"+plotName           ][kSig]->Scale(lumiweight(kSig, constLumiMuon, 0, "muon"    ));
	    histo_["modified"+plotName+"ElSig"   ][kSig]->Scale(lumiweight(kSig, constLumiElec, 0, "electron"));
	    double zPrimeLumiWeight=1;
	    if     (zprime=="500") zPrimeLumiWeight=(10*16.2208794979645*luminosity)/232074;
	    else if(zprime=="750") zPrimeLumiWeight=(10*3.16951400706147*luminosity)/206525;
	    histo_["modified"+plotName+"muZprime"][kSig]->Scale(zPrimeLumiWeight);
	    histo_["modified"+plotName+"ElZprime"][kSig]->Scale(zPrimeLumiWeight);
	    // add plots
	    histo_["modified"+plotName][kSig]->Add(histo_["modified"+plotName+"ElSig"   ][kSig]);
	    histo_["modified"+plotName][kSig]->Add(histo_["modified"+plotName+"muZprime"][kSig]);
	    histo_["modified"+plotName][kSig]->Add(histo_["modified"+plotName+"ElZprime"][kSig]);
	    // apply standard rebinning
	    std::map<TString, std::vector<double> > binning_ = makeVariableBinning();
	    reBinTH1F(*histo_["modified"+plotName][kSig], binning_[plotName], verbose-1);
	    // scale to unit area
	    histo_["modified"+plotName][kSig]->Scale(1/histo_["modified"+plotName][kSig]->Integral(0,histo_["modified"+plotName][kSig]->GetNbinsX()+1));
	    // divide by binwidth
	    histo_["modified"+plotName][kSig]=divideByBinwidth(histo_["modified"+plotName][kSig], verbose-1);
	    // set style
	    histogramStyle(*histo_["modified"+plotName][kSig], kSig, false, 1.2, kRed+1);
	    histo_["modified"+plotName][kSig]->SetLineColor(kMagenta);
	  }

	  // =====================
	  //  Adapt plot styles
	  // =====================
	  
	  double max = plotTheo->GetMaximum();
	  
	  max*=1.5;
	  plotTheo->GetXaxis()->SetNoExponent(true);
	  if(max>1&&max<100) plotTheo->GetYaxis()->SetNoExponent(true);
	  else plotTheo->GetYaxis()->SetNoExponent(false);
	  TString yTitle=plotTheo->GetYaxis()->GetTitle();
	  TString xTitle=plotTheo->GetXaxis()->GetTitle();
	  if(verbose>1) std::cout << "original title: " << yTitle  << std::endl;
	  xTitle.ReplaceAll("#mu","l");
	  yTitle.ReplaceAll("#mu","l");
	  if(verbose>1) std::cout << "new title: " << yTitle  << std::endl;
	  plotTheo->GetXaxis()->SetTitle(xTitle);
	  plotTheo->GetYaxis()->SetTitle(yTitle);
	  // Create canvases
	  TCanvas* combicanvas = new TCanvas("combicanvasStd", "combicanvasStd",  600, 600);
	  // get style from old canvas
	  combicanvas ->SetLogy(canvasMu->GetLogy());
	  if(normalize){
	    if (pTPlotsLog && xSecVariables_[i].Contains("Pt") ){
	      plotTheo->SetMinimum(0.0001);
	      if      (plotName=="topPt"  ) plotTheo->SetMaximum(0.02);
	      else if (plotName=="ttbarPt") plotTheo->SetMaximum(0.07);
	      else if (plotName=="lepPt"  ) plotTheo->SetMaximum(0.07);
	      combicanvas    ->SetLogy(1);
	    }
	    else{
	      if      (plotName=="topPt"  ) plotTheo->SetMaximum(0.01);
	      else if (plotName=="ttbarPt") plotTheo->SetMaximum(0.025);
	      else if (plotName=="lepPt"  ) plotTheo->SetMaximum(0.03);
	    }
	    // adjust max
	    if(plotName=="lepEta"||plotName=="topY"||plotName=="ttbarY") plotTheo->GetYaxis()->SetNoExponent(true);
	    
	    if      (plotName=="topY"   ) plotTheo->SetMaximum(0.6);
	    else if (plotName=="ttbarY" ) plotTheo->SetMaximum(0.8);
	    else if (plotName=="lepEta" ) plotTheo->SetMaximum(0.6);
	    else if (plotName=="bqEta"  ) plotTheo->SetMaximum(0.55);
	  }
	  
	  // activate canvas
	  gStyle->SetEndErrorSize(8);
	  
	  combicanvas->cd(0);
	  combicanvas->SetBottomMargin(myStyle.GetPadBottomMargin());
	  combicanvas->SetLeftMargin(myStyle.GetPadLeftMargin());
	  gStyle->SetEndErrorSize(8);
	  
	  // =====================
	  //  Theory Curves
	  // =====================
	  
	  bool DrawMCAtNLOPlot2    = DrawMCAtNLOPlot;
	  bool DrawPOWHEGPlot2     = DrawPOWHEGPlot;
	  bool smoothcurves2       = smoothcurves;
	  bool DrawSmoothMadgraph2 = DrawSmoothMadgraph;
	  
	  // ============================
	  //    !!!! PLEASE READ !!!!
	  // ============================
	  
	  // NO MCatNLO CURVES for b quark quantities
	  if(plotName=="bqPt"||plotName=="bqEta"){
	    DrawMCAtNLOPlot2=false;
	  }
	  
	  // Adjust drawing paramters for theory curves
	  if (normalize){
	    smoothcurves2=smoothcurves;
	  }
	  else{
	    // no theory curves for absolute xSecs at the moment
	    DrawMCAtNLOPlot2    = false;
	    DrawPOWHEGPlot2     = false;
	    smoothcurves2       = false;  
	    DrawSmoothMadgraph2 = false;
	  }
	  
	  // a) draw axis of binned MadGraph curve
	  if(xSecVariables_[i].Contains("ttbarY")) plotTheo->GetXaxis()->SetRangeUser(-2.49,2.49);
	  plotTheo->Draw("AXIS");
	  //if(xSecVariables_[i].Contains("Norm")){
	  
	  // b) binned MadGraph curve
	  plotTheo->Draw("hist same");
	  
	  // draw smoothed theory curves
	  // c) MCatNLO
	  int smoothFactor=0;
	  int rebinFactor=0;
	  int errorRebinFactor=0; 
	  int errorSmoothFactor=0;
	  
	  TString plotNameMCAtNLO="";
	  double rangeLow  = -1.0;
	  double rangeHigh = -1.0;
	  TString PSlabel = (extrapolate) ? "" : "Vis";
	  
	  if     (xSecVariables_[i].Contains("topPt"    )){ smoothFactor = 10; rebinFactor = 10; errorRebinFactor = 10; errorSmoothFactor = 10; plotNameMCAtNLO="h"+PSlabel+"TopPt"  ;}
	  else if(xSecVariables_[i].Contains("topY"     )){ smoothFactor =  5; rebinFactor =  1; errorRebinFactor =  1; errorSmoothFactor =  5; plotNameMCAtNLO="h"+PSlabel+"TopY"   ;}
	  else if(xSecVariables_[i].Contains("ttbarPt"  )){ smoothFactor = 10; rebinFactor =  1; errorRebinFactor =  1; errorSmoothFactor = 10; plotNameMCAtNLO="h"+PSlabel+"TTbarPt";}
	  else if(xSecVariables_[i].Contains("ttbarY"   )){ smoothFactor =  5; rebinFactor =  1; errorRebinFactor =  5; errorSmoothFactor = 10; plotNameMCAtNLO="h"+PSlabel+"TTbarY" ;}
	  else if(xSecVariables_[i].Contains("ttbarMass")){ smoothFactor =  5; rebinFactor =  1; errorRebinFactor =  1; errorSmoothFactor =  5; plotNameMCAtNLO="h"+PSlabel+"TTbarM" ;
	      if(cutTtbarMass){rangeLow=constMassRangeLow; rangeHigh=constMassRangeHigh;}}
	  else if(xSecVariables_[i].Contains("lepPt"    )){ smoothFactor = 10; rebinFactor =  1; errorRebinFactor =  0; errorSmoothFactor =  2; plotNameMCAtNLO="h"+PSlabel+"LepPt"  ;}
	  else if(xSecVariables_[i].Contains("lepEta"   )){ smoothFactor = 10; rebinFactor = 20; errorRebinFactor = 20; errorSmoothFactor = 10; plotNameMCAtNLO="h"+PSlabel+"LepEta" ;}
	  else if(xSecVariables_[i].Contains("bqPt"     )){ smoothFactor = 10; rebinFactor =  2; errorRebinFactor =  5; errorSmoothFactor = 10; plotNameMCAtNLO="" ;}
	  else if(xSecVariables_[i].Contains("bqEta"    )){ smoothFactor = 10; rebinFactor =  2; errorRebinFactor =  5; errorSmoothFactor = 10; plotNameMCAtNLO="" ;}
	  else{
	    std::cout << " ERROR - Unknown variable " << xSecVariables_[i] << std::endl;
	    // close file and delete pointer
	    closeStdTopAnalysisFiles(files_);
	    exit(-3);
	  }
	  
	  bool errorbands=true; // error band for MCatNLO curves
	  if(xSecVariables_[i].Contains("bqPt")||xSecVariables_[i].Contains("bqEta")) errorbands=false;
	  if (DrawMCAtNLOPlot2) DrawTheoryCurve("/afs/naf.desy.de/group/cms/scratch/tophh/CommonFiles/ttbarNtupleCteq6m.root", plotNameMCAtNLO, normalize, smoothFactor, rebinFactor, kAzure, 1, rangeLow, rangeHigh, errorbands, errorRebinFactor, errorSmoothFactor, verbose-1, true, false, "mcatnlo", smoothcurves2);
	  if (DrawMCAtNLOPlot2) DrawTheoryCurve("/afs/naf.desy.de/group/cms/scratch/tophh/CommonFiles/ttbarNtupleCteq6m.root", plotNameMCAtNLO, normalize, smoothFactor, rebinFactor, kAzure, 1, rangeLow, rangeHigh, false, errorRebinFactor, errorSmoothFactor, verbose-1, false, false, "mcatnlo", smoothcurves2);
	  
	  // d) POWHEG
	  // configure configuration
	  smoothFactor=0;
	  rebinFactor=0;
	  TString hadLevelExtend = "";
	  TString hadLevelPlotExtend = "";
	  if(hadron){
	      if(xSecVariables_[i].Contains("lep")) hadLevelExtend="Lepton";
	      if(xSecVariables_[i].Contains("bq" )) hadLevelExtend="Bjets" ;
	      if(xSecVariables_[i].Contains("lep")||xSecVariables_[i].Contains("bq")) hadLevelPlotExtend="Gen";
	  }
	  TString plotNamePOWHEG="analyzeTop"+LV+"LevelKinematics"+hadLevelExtend+PS+"/"+xSecVariables_[i]+hadLevelPlotExtend;
	  plotNamePOWHEG.ReplaceAll("Norm","");
	  rangeLow  = -1.0;
	  rangeHigh = -1.0;
	  if     (xSecVariables_[i].Contains("topPt"    )){ smoothFactor = 10; rebinFactor=10; }
	  else if(xSecVariables_[i].Contains("topY"     )){ smoothFactor =  3; rebinFactor= 1; }
	  else if(xSecVariables_[i].Contains("ttbarPt"  )){ smoothFactor = 10; rebinFactor= 2; }
	  else if(xSecVariables_[i].Contains("ttbarY"   )){ smoothFactor =  5; rebinFactor= 1; }
	  else if(xSecVariables_[i].Contains("ttbarMass")){ smoothFactor =  5; rebinFactor= 1; if(cutTtbarMass){rangeLow=constMassRangeLow; rangeHigh=constMassRangeHigh;}}
	  else if(xSecVariables_[i].Contains("lepPt"    )){ smoothFactor =  2; rebinFactor= 1; }
	  else if(xSecVariables_[i].Contains("lepEta"   )){ smoothFactor = 10; rebinFactor= 2; }
	  else if(xSecVariables_[i].Contains("bqPt"     )){ smoothFactor = 10; rebinFactor= 2; }
	  else if(xSecVariables_[i].Contains("bqEta"    )){ smoothFactor = 10; rebinFactor= 2; }
	  // draw curve	 
	  std::cout << plotNamePOWHEG << std::endl;
	  if(DrawPOWHEGPlot2) DrawTheoryCurve("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/combinedDiffXSecSigPowhegFall11PF.root", plotNamePOWHEG, normalize, smoothFactor, rebinFactor, kGreen+1, 1, -1./*rangeLow*/, -1./*rangeHigh*/, false, 1., 1., verbose-1, false, false, "powheg", smoothcurves2);
	  
	  // e) reweighted histos for closure test
	  if(reweightClosure&&sys==sysNo){
	      histo_["reweighted"+plotName][kSig]->Draw("hist same");
	  }
	  
	  // f) distorted parton truth histo including zprime
	  if(zprime!=""&&sys==sysNo){
	      histo_["modified"+plotName][kSig]->Draw("hist same");
	  }	    
	  
	  // g) smooth MadGraph Theory curve
	  smoothFactor=0;
	  rebinFactor=0;
	  TString plotNameMadgraph="analyzeTop"+LV+"LevelKinematics"+hadLevelExtend+PS+"/"+plotName+hadLevelPlotExtend;
	  plotNameMadgraph.ReplaceAll("Norm","");
	  rangeLow  = -1.0;
	  rangeHigh = -1.0;
	  if     (xSecVariables_[i].Contains("topPt"    )){ smoothFactor = 10; rebinFactor = 10; }
	  else if(xSecVariables_[i].Contains("topY"     )){ smoothFactor =  5; rebinFactor =  1; }
	  else if(xSecVariables_[i].Contains("ttbarPt"  )){ smoothFactor =  5; rebinFactor =  1; }
	  else if(xSecVariables_[i].Contains("ttbarY"   )){ smoothFactor =  2; rebinFactor =  1; }
	  else if(xSecVariables_[i].Contains("ttbarMass")){ smoothFactor = 10; rebinFactor =  1; if(cutTtbarMass){rangeLow=constMassRangeLow; rangeHigh=constMassRangeHigh;}}
	  else if(xSecVariables_[i].Contains("lepPt"    )){ smoothFactor =  2; rebinFactor =  1; }
	  else if(xSecVariables_[i].Contains("lepEta"   )){ smoothFactor =  4; rebinFactor =  1; }
	  else if(xSecVariables_[i].Contains("bqPt"     )){ smoothFactor = 10; rebinFactor =  2; }
	  else if(xSecVariables_[i].Contains("bqEta"    )){ smoothFactor =  2; rebinFactor =  1; }
	  if(DrawSmoothMadgraph2) DrawTheoryCurve("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/"+TopFilename(kSig, 0, "muon").ReplaceAll("muon", "combined"), plotNameMadgraph, normalize, smoothFactor, rebinFactor, kRed+1, 1, rangeLow, rangeHigh, false, 1., 1., verbose-1, false, false, "madgraph");
	  
	  // h) draw NNLO curve for topPt (normalized) and topY (normalized) and/or MCFM curves
	  if(DrawNNLOPlot || DrawMCFMPlot){ 
	    
	    TString plotname=xSecVariables_[i];	   
	    plotname.ReplaceAll("Norm", "");
	    std::map<TString, std::vector<double> > binning_ = makeVariableBinning();

	    // h1) draw NNLO curve for topPt (normalized) and topY (normalized)

	    if(DrawNNLOPlot&&(xSecVariables_[i].Contains("topPtNorm")||xSecVariables_[i].Contains("topYNorm"))){
	    
	      TFile *file = new TFile("/afs/naf.desy.de/group/cms/scratch/tophh/CommonFiles/kidonakisNNLO.root");
	      TH1F *plotnnlo= (TH1F*)(file->Get(plotname)->Clone(plotname+"nnlo"));
	      if(plotnnlo){ 		
		TH1F *newPlotNNLO = reBinTH1FIrregularNewBinning(plotnnlo,binning_[plotname],plotname,true);
		newPlotNNLO->SetName(plotname+"nnlo"); 
		newPlotNNLO->GetXaxis()->SetRange(0, plotnnlo->GetNbinsX()-1);
		newPlotNNLO->SetLineColor(kOrange);
		newPlotNNLO->SetLineWidth(2);
		newPlotNNLO->Draw("same");		
	      }	     	     
	    }
	  
	    // h2) MCFM curves

	    if (DrawMCFMPlot&&xSecVariables_[i].Contains("Norm")){

	      TString mcfmplotname = "";
	      
	      if      (plotname=="topPt")     mcfmplotname = "pt_t";
	      else if (plotname=="topY")      mcfmplotname = "y_t";
	      else if (plotname=="ttbarPt")   mcfmplotname = "pt_tt";
	      else if (plotname=="ttbarY")    mcfmplotname = "y_tt";
	      else if (plotname=="ttbarMass") mcfmplotname = "m_tt";
	      else if (plotname=="lepPt")     mcfmplotname = "pt_l";
	      else if (plotname=="lepEta")    mcfmplotname = "eta_l";

	      if (mcfmplotname!=""){
		TFile *fileMCFM1 = new TFile("/afs/naf.desy.de/group/cms/scratch/tophh/CommonFiles/diffCrossSections_normalized_tt_bbh_todk_MSTW200_172_172_ful_central.root","READ");
		TFile *fileMCFM2 = new TFile("/afs/naf.desy.de/group/cms/scratch/tophh/CommonFiles/diffCrossSections_normalized_tt_bbh_todk_MSTW200_172_172_ful_charCon.root","READ");
		
		if (fileMCFM1 || fileMCFM1){
		  TH1F *plotMCFM1= (TH1F*)(fileMCFM1->Get(mcfmplotname)->Clone(plotname+"MCFM1"));
		  TH1F *plotMCFM2= (TH1F*)(fileMCFM2->Get(mcfmplotname)->Clone(plotname+"MCFM2"));
		  
		  if (plotMCFM1){
		    TH1F *newPlotMCFM1 = reBinTH1FIrregularNewBinning(plotMCFM1,binning_[plotname],mcfmplotname,true);
		    
		    newPlotMCFM1->SetName(plotname+"MCFM1"); 
		    newPlotMCFM1->GetXaxis()->SetRange(0, newPlotMCFM1->GetNbinsX()-1);
		    newPlotMCFM1->SetLineColor(kMagenta);
		    newPlotMCFM1->SetLineWidth(2);
		    newPlotMCFM1->Draw("same");
		  }
		  
		  if (plotMCFM2){
		    TH1F *newPlotMCFM2 = reBinTH1FIrregularNewBinning(plotMCFM2,binning_[plotname],mcfmplotname,true);
		    
		    newPlotMCFM2->SetName(plotname+"MCFM2"); 
		    newPlotMCFM2->GetXaxis()->SetRange(0, newPlotMCFM2->GetNbinsX()-1);
		    newPlotMCFM2->SetLineColor(kBlue);
		    newPlotMCFM2->SetLineWidth(1);
		    newPlotMCFM2->Draw("same");
		  }
		}
	      }	
	      else std::cout << " Unknown variable for MCFM plot - skipping this part for " << plotname << std::endl;
	    }
	  }
	  // j) re-draw binned MADGRAPH theory curve
	  plotTheo->Draw("hist same");
	  	  
	  // ==============
	  //  Legend
	  // ==============
	  
	  TLegend *leg = new TLegend();
	  legendStyle(*leg,"",0.04);
	  
	  // a) Legend - Data label
	  leg->AddEntry(plotCombination, dataLabel, "P");
	  
	  // b) Legend - Theory prediction - MADGRAPH
	  TString nameMADGRAPHcurve=plotName;
	  nameMADGRAPHcurve.ReplaceAll("Norm","");
	  TH1F* madgraphcurve =(TH1F*)combicanvas->GetPrimitive(nameMADGRAPHcurve);
	  if(madgraphcurve) leg->AddEntry(madgraphcurve, "MadGraph", "L" );
	  
	  // c) Legend - Theory prediction - MCatNLO
	  if(DrawMCAtNLOPlot2){
	    //leg->AddEntry(errorBandsMCatNLO, "MC@NLO  ", "FL");
	    TString curveName=xSecVariables_[i];
	    curveName.ReplaceAll("Norm","");
	    //curveName.ReplaceAll("MCatNLO","MCatNLO2");
	    curveName+="MC@NLOerrorBand";
	    TGraphAsymmErrors *mcatnlocurve =(TGraphAsymmErrors*)combicanvas->GetPrimitive(curveName);
	    if(mcatnlocurve) leg->AddEntry(mcatnlocurve, "MC@NLO  ", "FL");
	    else{
	      if(verbose>0){
		std::cout << "curve " << curveName << " not found. ";
		curveName.ReplaceAll("errorBand","");
		std::cout << "Will add " << curveName << " instead to the legend" << std::endl;
	      }
	      TH1F* mcatnlocurve2 =(TH1F*)combicanvas->GetPrimitive(curveName);
	      if(mcatnlocurve2) leg->AddEntry(mcatnlocurve2, "MC@NLO  ", "L");	
	    }
	  }
	  
	  // d) Legend - Theory prediction - POWHEG
	  if(DrawPOWHEGPlot2){
	    TString curveName=xSecVariables_[i];
	    curveName.ReplaceAll("Norm","");
	    if(curveName.Contains("lep")||curveName.Contains("bq")) curveName+="Gen";
	    curveName+="POWHEG";
	    TH1F* powhegcurve =(TH1F*)combicanvas->GetPrimitive(curveName);
	    if(powhegcurve) leg->AddEntry(powhegcurve, "POWHEG  ", "L");
	  }
	  
	  // e) Legend - Theory prediction - NNLO
	  if(DrawNNLOPlot){
	    TH1F* nnlocurve = 0;
	    if      (xSecVariables_[i].Contains("topPtNorm")){nnlocurve =(TH1F*)combicanvas->GetPrimitive("topPtnnlo");}
	    else if (xSecVariables_[i].Contains("topYNorm" )){nnlocurve =(TH1F*)combicanvas->GetPrimitive("topYnnlo"); }
	    if(nnlocurve) leg->AddEntry(nnlocurve, "Approx. NNLO", "L");
	  }

	  // f) Legend - Theory prediction - MCFM
	  if(DrawNNLOPlot){
	    TH1F* mcfmcurve = 0;
	    TString curveName=xSecVariables_[i];
	    curveName.ReplaceAll("Norm","");
	    curveName+="MCFM1";
	    mcfmcurve =(TH1F*)combicanvas->GetPrimitive(curveName);
	    if(mcfmcurve) leg->AddEntry(mcfmcurve, "MCFM", "L");
	  }
	  
	  // g) Legend - Closure test(s)
	  if(reweightClosure&&sys==sysNo) leg->AddEntry(histo_["reweighted"+plotName][kSig], "MadGraph Reweighted", "L");
	  if(zprime!=""     &&sys==sysNo) leg->AddEntry(histo_["modified"+plotName][kSig], "t#bar{t} & "+zprime+" GeV Z'", "L");
	  
	  leg->SetX1NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength() - 0.30);
	  leg->SetY1NDC(1.0 - gStyle->GetPadTopMargin()   - gStyle->GetTickLength() - 0.04 * (double)(leg->GetNRows()));
	  leg->SetX2NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength());
	  leg->SetY2NDC(1.0 - gStyle->GetPadTopMargin()   - gStyle->GetTickLength());
	  
	  //}

	  plotCombination->Draw("e X0 same"); 
	  leg->Draw("same");  
	  gPad->RedrawAxis(); 
	  DrawCMSLabels(false,luminosity);
	  DrawDecayChLabel("e/#mu + Jets Combined");
	  histo_[xSecVariables_[i]][sys]=(TH1F*)(plotCombination->Clone());
	  
	  // save combined e+mu plot for systematic error calculation afterwards
	  canvas_[xSecVariables_[i]][sys]=(TCanvas*)(combicanvas->Clone());
	  canvas_[xSecVariables_[i]][sys]->SetTitle(xSecVariables_[i]);
	  canvas_[xSecVariables_[i]][sys]->SetName(xSecVariables_[i]);
	  if(save&&sys==sysNo){
	    if(verbose>0) std::cout << "saving" << std::endl;
	    int initialIgnoreLevel=gErrorIgnoreLevel;
	    if(verbose==0) gErrorIgnoreLevel=kWarning;
	    combicanvas->Print("./diffXSecFromSignal/plots/combined/"+dataSample+"/xSec/xSec"+xSecVariables_[i]+universalplotLabel+".eps"); 
	    combicanvas->Print("./diffXSecFromSignal/plots/combined/"+dataSample+"/xSec/xSec"+xSecVariables_[i]+universalplotLabel+".png");
	    gErrorIgnoreLevel=initialIgnoreLevel;
	  }
	  // close Canvas
	  combicanvas->Close();
	  //delete combicanvas;
	  delete leg;
	  delete combicanvas;
	}
	else{ 
	  std::cout << " ERROR in bothDecayChannelsCombination.C! " << std::endl;
	  std::cout << " plot " << xSecVariables_[i]+"kData" << " not found in ";
	  std::cout << xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << " for:" << std::endl;
	  if(!plotMu)   std::cout << "muon channel data"     << std::endl;
	  if(!plotEl)   std::cout << "electron channel data" << std::endl;
	  if(!plotTheo) std::cout << "theory"                << std::endl;
	  // close file and delete pointer
	  closeStdTopAnalysisFiles(files_);
	  exit(-2);
	}
      }
      else{
	std::cout << " ERROR in bothDecayChannelsCombination.C! " << std::endl;
	if(!canvasMu||!canvasEl) std::cout << " canvas " << xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << " not found in ";
	if(!canvasMu) std::cout << "diffXSecTopSemiMu"  +dataSample+LV+PS+".root (muon file)"     << std::endl;
	if(!canvasEl) std::cout << "diffXSecTopSemiElec"+dataSample+LV+PS+".root (electron file)" << std::endl;
	if(!canvasTheo){ 
	  std::cout << " theory canvas " << xSecFolder+"/"+sysLabel(sysNo)+"/"+xSecVariables_[i] << " not found in diffXSecTopSemiMu"+dataSample+LV+PS+".root" << std::endl;
	}
	// close file and delete pointer
	closeStdTopAnalysisFiles(files_);
	exit(-1);
      }
    }
  }
  
  // =================================================
  //  Save combined mu+e plots to ROOT-file
  // =================================================
  
  // loop variables
  for(unsigned int i=0; i<xSecVariables_.size(); ++i){
    // loop systematic variations
    for(unsigned int sys=sysNo; sys<ENDOFSYSENUM; ++sys){
      if(histo_[xSecVariables_[i]][sys]){
	saveToRootFile("diffXSecTopSemiLep"+LV+PS+".root", canvas_[xSecVariables_[i]][sys], true, verbose,""+xSecFolder+"/"+sysLabel(sys));
      }
    }
  }
  
  // close file and delete pointer
  closeStdTopAnalysisFiles(files_);
}
