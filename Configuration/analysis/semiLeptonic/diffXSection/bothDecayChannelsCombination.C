#include "basicFunctions.h"

void bothDecayChannelsCombination(double luminosity=4980, bool save=true, unsigned int verbose=0, TString inputFolderName="RecentAnalysisRun", bool pTPlotsLog=false, bool extrapolate=true, bool hadron=false){
    
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
  TString xSecVariables[] ={"topPt", "topY", "ttbarPt", "ttbarY", "ttbarMass", "lepPt" ,"lepEta", "bqPt", "bqEta", "topPtNorm", "topYNorm", "ttbarPtNorm", "ttbarYNorm", "ttbarMassNorm", "lepPtNorm" ,"lepEtaNorm", "bqPtNorm", "bqEtaNorm"};
  xSecVariables_.insert( xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString) );
  
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
  
  // choose additional theory curves to plot
  bool DrawSmoothMadgraph = false;
  bool DrawMCAtNLOPlot    = false;
  bool DrawPOWHEGPlot     = false;
  bool DrawNNLOPlot       = false;
  // smooth instead of binned theory curves
  bool smoothcurves=true;
  if(smoothcurves){
    DrawSmoothMadgraph = true;
    DrawPOWHEGPlot     = true;
    DrawMCAtNLOPlot    = true;
	// FIXME: no smooth mc@nlo curve for hadron PS at the moment
    if(hadron) DrawMCAtNLOPlot = false;
  }	
  // add kidonakis plots for full PS
  if(extrapolate&&smoothcurves) DrawNNLOPlot=true;
  
  //if(extrapolate==false&&hadron==false){
  //  DrawSmoothMadgraph = true;
  //  DrawMCAtNLOPlot = true;
  //  DrawPOWHEGPlot = true;
  //}
  
  // GOSSIE quick fix: cut of m(ttbar) below 345 GeV
  bool cutTtbarMass=false;
  
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
	  // loop bins
	  if(verbose>1) std::cout << std::endl << xSecVariables_[i] << ":" << std::endl;
	  for(int bin=1; bin<=plotCombination->GetNbinsX(); ++bin){
	    if(verbose>1){
	      std::cout << ", bin" << bin << ":" << std::endl;
	      std::cout << "(" << plotCombination->GetBinLowEdge(bin) << " .... " << plotCombination->GetBinLowEdge(bin+1) << ")" << std::endl;
	    }
	    // consider only non-empty bins
	    if(plotMu->GetBinContent(bin)!=0&&plotEl->GetBinContent(bin)!=0){
	      double xSecMu     =plotMu->GetBinContent(bin);
	      double xSecEl     =plotEl->GetBinContent(bin);
	      double xSecErrorMu=plotMu->GetBinError  (bin);
	      double xSecErrorEl=plotEl->GetBinError  (bin);
	      double combinedxSec=(xSecMu/(xSecErrorMu*xSecErrorMu)+xSecEl/(xSecErrorEl*xSecErrorEl));
	      combinedxSec/=(1/(xSecErrorMu*xSecErrorMu)+1/(xSecErrorEl*xSecErrorEl));
	      double combinedxSecError=sqrt(1/(1/(xSecErrorMu*xSecErrorMu)+1/(xSecErrorEl*xSecErrorEl)));
	      plotCombination->SetBinContent(bin, combinedxSec     );
	      plotCombination->SetBinError  (bin, combinedxSecError);
	      if(verbose>1){
		std::cout << "muon:     " << xSecMu       << " +/- " << xSecErrorMu       << std::endl;
		std::cout << "elec:     " << xSecEl       << " +/- " << xSecErrorEl       << std::endl;
		std::cout << "combined: " << combinedxSec << " +/- " << combinedxSecError << std::endl;
	      }
	    }
	  }
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
	  // create Canvas
	  TCanvas* combicanvas = new TCanvas("combicanvas", "combicanvas", 600, 600);
	  // get style from old canvas
	  combicanvas->SetLogy(canvasMu->GetLogy());
	  if(normalize){
	    if (pTPlotsLog && xSecVariables_[i].Contains("Pt") ){
	      plotTheo->SetMinimum(0.0001);
	      if      (plotName=="topPt"  ) plotTheo->SetMaximum(0.02);
	      else if (plotName=="ttbarPt") plotTheo->SetMaximum(0.07);
	      else if (plotName=="lepPt"  ) plotTheo->SetMaximum(0.07);
	      combicanvas->SetLogy(1);
	    }
	    else{
	      if      (plotName=="topPt"  ) plotTheo->SetMaximum(0.01);
	      else if (plotName=="ttbarPt") plotTheo->SetMaximum(0.02);
	      else if (plotName=="lepPt"  ) plotTheo->SetMaximum(0.03);
	    }
	    // adjust max
	    if(plotName=="lepEta"||plotName=="topY") plotTheo->GetYaxis()->SetNoExponent(true);
	    
	    if      (plotName=="topY"   ) plotTheo->SetMaximum(0.6);
	    else if (plotName=="ttbarY" ) plotTheo->SetMaximum(0.8);
	    else if (plotName=="lepEta" ) plotTheo->SetMaximum(0.6);
	    else if (plotName=="bqEta"  ) plotTheo->SetMaximum(0.55);
	  }
	  
	  // activate canvas
	  combicanvas->cd(0);
	  combicanvas->SetBottomMargin(myStyle.GetPadBottomMargin());
	  combicanvas->SetLeftMargin(myStyle.GetPadLeftMargin());
	  gStyle->SetEndErrorSize(8);
	  
	  // =====================
	  //  Theory Curves
	  // =====================
	  
	  //TH1F* plotTheo2=(TH1F*)plotTheo->Clone();
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
	    if(cutTtbarMass){rangeLow=330.0; rangeHigh=1200.0;}}
	  else if(xSecVariables_[i].Contains("lepPt"    )){ smoothFactor = 10; rebinFactor =  1; errorRebinFactor =  0; errorSmoothFactor =  2; plotNameMCAtNLO="h"+PSlabel+"LepPt"  ;}
	  else if(xSecVariables_[i].Contains("lepEta"   )){ smoothFactor = 10; rebinFactor = 20; errorRebinFactor = 20; errorSmoothFactor = 10; plotNameMCAtNLO="h"+PSlabel+"LepEta" ;}
	  else if(xSecVariables_[i].Contains("bqPt"     )){ smoothFactor = 10; rebinFactor =  2; errorRebinFactor =  5; errorSmoothFactor = 10; plotNameMCAtNLO="" ;}
	  else if(xSecVariables_[i].Contains("bqEta"    )){ smoothFactor = 10; rebinFactor =  2; errorRebinFactor =  5; errorSmoothFactor = 10; plotNameMCAtNLO="" ;}
	  else{
	    std::cout << "unknown variable " << xSecVariables_[i] << std::endl;
	    // close file and delete pointer
	    closeStdTopAnalysisFiles(files_);
	    exit(-3);
	  }
	  
	  bool errorbands=true; // error band for MCatNLO curves
	  if(xSecVariables_[i].Contains("bqPt")||xSecVariables_[i].Contains("bqEta")) errorbands=false;
	  if (DrawMCAtNLOPlot2) DrawTheoryCurve("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/ttbarNtupleCteq6m.root", plotNameMCAtNLO, normalize, smoothFactor, rebinFactor, kAzure, 1, rangeLow, rangeHigh, errorbands, errorRebinFactor, errorSmoothFactor, verbose-1, true, false, "mcatnlo", smoothcurves2);
	  if (DrawMCAtNLOPlot2) DrawTheoryCurve("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/ttbarNtupleCteq6m.root", plotNameMCAtNLO, normalize, smoothFactor, rebinFactor, kAzure, 1, rangeLow, rangeHigh, false, errorRebinFactor, errorSmoothFactor, verbose-1, false, false, "mcatnlo", smoothcurves2);
	  //plotNameMCAtNLO="analyzeTopPartonLevelKinematicsPhaseSpace/"+xSecVariables_[i];
	  //plotNameMCAtNLO.ReplaceAll("Norm","");
	  //DrawTheoryCurve("/afs/naf.desy.de/group/cms/scratch/tophh/tmp/topkinematics_combined_mcatnlo.root", plotNameMCAtNLO, normalize, smoothFactor, rebinFactor, kAzure+5, 7, rangeLow, rangeHigh, false, errorRebinFactor, errorSmoothFactor, verbose-1, false, false);
	  
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
	  rangeLow=-1.;
	  rangeHigh=-1.;
	  if     (xSecVariables_[i].Contains("topPt"    )){ smoothFactor = 10; rebinFactor=10; }
	  else if(xSecVariables_[i].Contains("topY"     )){ smoothFactor =  3; rebinFactor= 1; }
	  else if(xSecVariables_[i].Contains("ttbarPt"  )){ smoothFactor = 10; rebinFactor= 2; }
	  else if(xSecVariables_[i].Contains("ttbarY"   )){ smoothFactor =  5; rebinFactor= 1; }
	  else if(xSecVariables_[i].Contains("ttbarMass")){ smoothFactor =  5; rebinFactor= 1; if(cutTtbarMass){rangeLow=300.; rangeHigh=1200.;}}
	  else if(xSecVariables_[i].Contains("lepPt"    )){ smoothFactor =  2; rebinFactor= 1; }
	  else if(xSecVariables_[i].Contains("lepEta"   )){ smoothFactor = 10; rebinFactor= 2; }
	  else if(xSecVariables_[i].Contains("bqPt"     )){ smoothFactor = 10; rebinFactor= 2; }
	  else if(xSecVariables_[i].Contains("bqEta"    )){ smoothFactor = 10; rebinFactor= 2; }
	  // draw curve
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
	  rangeLow=-1.;
	  rangeHigh=-1.;
	  if     (xSecVariables_[i].Contains("topPt"    )){ smoothFactor = 10; rebinFactor = 10; }
	  else if(xSecVariables_[i].Contains("topY"     )){ smoothFactor =  5; rebinFactor =  1; }
	  else if(xSecVariables_[i].Contains("ttbarPt"  )){ smoothFactor =  5; rebinFactor =  1; }
	  else if(xSecVariables_[i].Contains("ttbarY"   )){ smoothFactor =  2; rebinFactor =  1; }
	  else if(xSecVariables_[i].Contains("ttbarMass")){ smoothFactor = 10; rebinFactor =  1; if(cutTtbarMass){rangeLow=325.; rangeHigh=1200.;} }
	  else if(xSecVariables_[i].Contains("lepPt"    )){ smoothFactor =  2; rebinFactor =  1; }
	  else if(xSecVariables_[i].Contains("lepEta"   )){ smoothFactor =  4; rebinFactor =  1; }
	  else if(xSecVariables_[i].Contains("bqPt"     )){ smoothFactor = 10; rebinFactor =  2; }
	  else if(xSecVariables_[i].Contains("bqEta"    )){ smoothFactor =  2; rebinFactor =  1; }
	  if(DrawSmoothMadgraph2) DrawTheoryCurve("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/"+TopFilename(kSig, 0, "muon").ReplaceAll("muon", "combined"), plotNameMadgraph, normalize, smoothFactor, rebinFactor, kRed+1, 1, rangeLow, rangeHigh, false, 1., 1., verbose-1, false, false, "madgraph");
	  
	  // h) draw NNLO curve for topPt (normalized) and topY (normalized)
	  if(DrawNNLOPlot&&(xSecVariables_[i].Contains("topPtNorm")||xSecVariables_[i].Contains("topYNorm"))){
	    TFile *file = new TFile("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/kidonakisNNLO.root");
	    TString nnloplotname=xSecVariables_[i];
	    nnloplotname.ReplaceAll("Norm", "");
	    TH1F *plotnnlo= (TH1F*)(file->Get(nnloplotname)->Clone(nnloplotname+"nnlo"));
	    if(plotnnlo){
	      plotnnlo->GetXaxis()->SetRange(0, plotnnlo->GetNbinsX()-1);
	      plotnnlo->SetMarkerColor(kOrange);
	      plotnnlo->SetMarkerStyle(21);
	      plotnnlo->SetMarkerSize(0.7);
	      plotnnlo->Draw("p same");		
	    }
	  }
	  
	  // i) re-draw binned MADGRAPH theory curve
	  //plotTheo2->Draw("hist same");
	  plotTheo->Draw("hist same");
	  
	  // ==============
	  //  Legend
	  // ==============
	  
	  TLegend *leg = new TLegend();
	  legendStyle(*leg,"");
	  leg->SetTextSize(0.04);
	  
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
	    curveName+="POWHEG";
	    TH1F* powhegcurve =(TH1F*)combicanvas->GetPrimitive(curveName);
	    if(powhegcurve) leg->AddEntry(powhegcurve, "POWHEG  ", "L");
	  }
	  
	  // e) Legend - Theory prediction - NNLO
	  if(DrawNNLOPlot){
	    TH1F* nnlocurve = 0;
	    if      (xSecVariables_[i].Contains("topPtNorm")){nnlocurve =(TH1F*)combicanvas->GetPrimitive("topPtnnlo");}
	    else if (xSecVariables_[i].Contains("topYNorm" )){nnlocurve =(TH1F*)combicanvas->GetPrimitive("topYnnlo"); }
	    if(nnlocurve) leg->AddEntry(nnlocurve, "NNLO", "P");
	  }
	  
	  // f) Legend - Closure test(s)
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
	  DrawCMSLabels(true,luminosity);
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
