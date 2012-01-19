#include "basicFunctions.h"

void bothDecayChannelsCombination(double luminosity=1143, bool save=true, unsigned int verbose=0, TString inputFolderName="TOP2011/110819_AnalysisRun"){
	
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

  // say if closure test with reweighted m(ttbar) on parton level is done
  // will plot additionally the modified diff. norm. xSec on parton level
  bool reweightClosure=false;
  // Zprime pseudo data test
  // choose "", "500" or "750"
  TString zprime="";
  // adjust data label
  TString dataLabel= (reweightClosure||zprime!="") ? "Pseudo-Data": "Data"; 
  // choose if xSec are extrapolated to whole phase space
  bool extrapolate=false;
  TString PS="";
  if(!extrapolate)PS="PhaseSpace";
  // choose if hadron or parton level xSec is taken
  bool hadron=false;
  TString state="";
  if(hadron) state="Hadron";
  else state="Parton";
  // choose additional theory curves to plot
  bool DrawMCAtNLOPlot = true;
  bool DrawPOWHEGPlot = true;
  // GOSSIE quick fix: cut of m(ttbar) below 354 GeV
  bool cutTtbarMass=false;
  // decay channels
  enum channel {kMuon, kElectron};
  // define folders where XSec plots are stored
  TString xSecFolder = "xSec";
  // get right file by luminosity
  TString dataSample="";
  if(luminosity<50) dataSample="2010";
  if(luminosity>50) dataSample="2011";
  // define muon and electron input rootfile
  std::map<unsigned int, TFile*> files_;
  files_[kMuon    ] = new (TFile)("diffXSecTopSemiMu"  +dataSample+".root");
  files_[kElectron] = new (TFile)("diffXSecTopSemiElec"+dataSample+".root");
  // define variables for combination
  // NOTE: these must be included in xSecVariables_ 
  // in analyzeHypothesisKinFit.C and combineTopDiffXSecUncertainties.C
  std::vector<TString> xSecVariables_;
  TString xSecVariables[] ={"topPt", "topY", "ttbarPt", "ttbarMass", "ttbarY", "lepPt" ,"lepEta", "bqPt", "bqEta", "topPtNorm", "topYNorm", "ttbarPtNorm", "ttbarMassNorm", "ttbarYNorm", "lepPtNorm" ,"lepEtaNorm", "bqPtNorm", "bqEtaNorm"};
  xSecVariables_.insert( xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString) );
  // create plot container for combined e+#mu plots
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, std::map <unsigned int, TCanvas*> > canvas_;
  // ---
  //    Combination for all kinematic variables x systematic variations available
  // ---
  // loop systematic variations
  for(unsigned int sys=sysNo; sys<ENDOFSYSENUM; ++sys){
    TString subfolder=sysLabel(sys);
    // loop variables
    for(unsigned int i=0; i<xSecVariables_.size(); ++i){
      // get canvas
      TCanvas* canvasMu   = (TCanvas*)(files_[kMuon    ]->Get(xSecFolder+"/"+subfolder+"/"+xSecVariables_[i]));
      TCanvas* canvasTheo = (TCanvas*)(files_[kMuon    ]->Get(xSecFolder+"/"+sysLabel(sysNo)+"/"+xSecVariables_[i]));
      TCanvas* canvasEl   = (TCanvas*)(files_[kElectron]->Get(xSecFolder+"/"+subfolder+"/"+xSecVariables_[i]));
      if(canvasMu&&canvasEl&&canvasTheo){
	// get data plots for all systematics
	TString plotName = xSecVariables_[i];
	plotName.ReplaceAll("Norm","");
	TH1F* plotMu   = (TH1F*)canvasMu  ->GetPrimitive(plotName+"kData");
	TH1F* plotTheo = (TH1F*)canvasTheo->GetPrimitive(plotName        );
	TH1F* plotEl   = (TH1F*)canvasEl  ->GetPrimitive(plotName+"kData");
	if(plotMu&&plotEl&&plotTheo){ 
	  if(verbose>1){
	    std::cout << "plot "+plotName+"kData in "+xSecFolder+"/"+subfolder+"/"+xSecVariables_[i];
	    std::cout << " for both channels found!" << std::endl;
	  }
	  //
	  // !!!! PLEASE READ !!!!
	  //
	  // - mcatnlo error bands and central curve are derived from the low statistics file at the moment!
	  // - special treatment for b quark quantities: missing theory curves
	  bool DrawMCAtNLOPlot2 = DrawMCAtNLOPlot;
	  bool DrawPOWHEGPlot2  = DrawPOWHEGPlot;
	  if(plotName=="bqPt"||plotName=="bqEta"){
	    //DrawPOWHEGPlot2=false;
	    DrawMCAtNLOPlot2=false;
	  }
	  // combine the results
	  TH1F* plotCombination=(TH1F*)(plotMu->Clone());
	  plotCombination->Scale(0.0);
	  // loopins
	  for(int bin=1; bin<=plotCombination->GetNbinsX(); ++bin){
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
		std::cout << xSecVariables_[i] << ", bin" << bin << ":" << std::endl;
		std::cout << "mu: " << xSecMu << " +/- " << xSecErrorMu << std::endl;
		std::cout << "el: " << xSecEl << " +/- " << xSecErrorEl << std::endl;
		std::cout << "combined: " << combinedxSec << " +/- " << combinedxSecError << std::endl;
	      }
	    }
	  }
	  // ---
	  //    additional histos for reweighting closure test
	  // ---
	  if(reweightClosure&&sys==sysNo){
	    // get reweighted samples
	    TString muReweighted="/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/muonDiffXSecSigMadD6TSummer11ReweightedttbarMassUpPF.root";
	    TString elReweighted="/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/elecDiffXSecSigMadD6TSummer11ReweightedttbarMassUpPF.root";
	    TFile* mufile = new (TFile)(muReweighted);
	    TFile* elfile = new (TFile)(elReweighted);
	    // get plot
	    TString partonPlot="analyzeTop"+state+"LevelKinematics"+PS+"/"+plotName;
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
	  // ---
	  //    additional histos for z prime closure test
	  // ---
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
	    TString partonPlot="analyzeTop"+state+"LevelKinematics"+PS+"/"+plotName;
	    histo_["modified"+plotName           ][kSig] = (TH1F*)(muSigfile   ->Get(partonPlot)->Clone("modified"+plotName));
	    histo_["modified"+plotName+"ElSig"   ][kSig] = (TH1F*)(elSigfile   ->Get(partonPlot)->Clone("elSig"+plotName   ));
	    histo_["modified"+plotName+"muZprime"][kSig] = (TH1F*)(muZprimefile->Get(partonPlot)->Clone("zprime"+plotName  ));
	    histo_["modified"+plotName+"ElZprime"][kSig] = (TH1F*)(elZprimefile->Get(partonPlot)->Clone("zprime"+plotName  ));
	    // relative apply lumiweight- needed because these are different samples
	    histo_["modified"+plotName           ][kSig]->Scale(lumiweight(kSig, luminosity, 0, "muon"    ));
	    histo_["modified"+plotName+"ElSig"   ][kSig]->Scale(lumiweight(kSig, luminosity, 0, "electron"));
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
	  // adapt plot style
	  double max = plotTheo->GetMaximum();
	  max*=1.5;
	  plotTheo->GetXaxis()->SetNoExponent(true);
	  if(max>1&&max<100) plotTheo->GetYaxis()->SetNoExponent(true);
	  else plotTheo->GetYaxis()->SetNoExponent(false);
	  TString yTitle=plotTheo->GetYaxis()->GetTitle();
	  TString xTitle=plotTheo->GetXaxis()->GetTitle();
	  if(verbose>1)std::cout << "original title: " << yTitle  << std::endl;
	  yTitle.ReplaceAll("#mu","l");
	  xTitle.ReplaceAll("#mu","l");
	  if(verbose>1)std::cout << "new title: " << yTitle  << std::endl;
	  plotTheo->GetYaxis()->SetTitle(yTitle);
	  plotTheo->GetXaxis()->SetTitle(xTitle);
	  // create Canvas
	  TCanvas* combicanvas = new TCanvas("combicanvas", "combicanvas", 600, 600);
	  // get style from old canvas
	  combicanvas->SetLogy(canvasMu->GetLogy());
	  // adjust max
	  if (xSecVariables_[i].Contains("Norm")){
	    if(plotName=="lepEta"||plotName=="topY") plotTheo->GetYaxis()->SetNoExponent(true);
	    if(plotName=="topY"   ) plotTheo->SetMaximum(0.6);
	    if(plotName=="topPt"  ) plotTheo->SetMaximum(0.008);
	    if(plotName=="ttbarPt") plotTheo->SetMaximum(0.02);
	    if(plotName=="ttbarY" ) plotTheo->SetMaximum(0.8);
	    if(plotName=="lepPt"  ) plotTheo->SetMaximum(0.03);
	    if(plotName=="lepEta" ) plotTheo->SetMaximum(0.6);
	    if(plotName=="bqEta"  ) plotTheo->SetMaximum(0.55);
	  }
	  // activate canvas
	  combicanvas->cd(0);
	  combicanvas->SetBottomMargin(myStyle.GetPadBottomMargin());
	  combicanvas->SetLeftMargin(myStyle.GetPadLeftMargin());
	  gStyle->SetEndErrorSize(8);
	  // draw binned MADGRAPH curve
	  plotTheo->Draw("AXIS");
	  // get unbinned Madgraph theory curve
	  TString theofolder="analyzeTop"+state+"LevelKinematics"+PS;
	  TH1F* unbinnedTheory = getTheoryPrediction(""+theofolder+"/"+plotName,"/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/"+TopFilename(kSig, 0, "muon"));
	  // add muon and electron channel to
	  // minimize statistical fluctuations
	  unbinnedTheory->Add(getTheoryPrediction(""+theofolder+"/"+plotName,"/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/"+TopFilename(kSig, 0, "electron")));
	  // keep control curve without smoothing and rebinning
	  TH1F* unbinnedTheory2 = (TH1F*)unbinnedTheory->Clone();
	  // A) for normalized cross sections:
	  if(xSecVariables_[i].Contains("Norm")){
	    // rebinning to avoid statistical fluctuations
	    if(     xSecVariables_[i].Contains("ttbarMass")) unbinnedTheory->Rebin(6 );
	    else if(xSecVariables_[i].Contains("topPt"    )) unbinnedTheory->Rebin(10);
	    else if(xSecVariables_[i].Contains("bqPt"     )) unbinnedTheory->Rebin(2);
	    // else if(xSecVariables_[i].Contains("bqEta"    )) unbinnedTheory->Rebin();
	    // else if(xSecVariables_[i].Contains("ttbarY"   )) unbinnedTheory->Rebin();
	    // else if(xSecVariables_[i].Contains("ttbarPt"  )) unbinnedTheory->Rebin();
	    // else if(xSecVariables_[i].Contains("topY"     )) unbinnedTheory->Rebin();
	    // else if(xSecVariables_[i].Contains("lepPt"    )) unbinnedTheory->Rebin();
	    // else if(xSecVariables_[i].Contains("lepEta"   )) unbinnedTheory->Rebin();
	    // divide by area and binwidth
	    unbinnedTheory ->Scale(1.0/(unbinnedTheory ->Integral(0,unbinnedTheory->GetNbinsX()+1)));
	    unbinnedTheory ->Scale(1.0/(unbinnedTheory ->GetBinWidth(1)));
	    unbinnedTheory2->Scale(1.0/(unbinnedTheory2->Integral(0,unbinnedTheory2->GetNbinsX()+1)));
	    unbinnedTheory2->Scale(1.0/(unbinnedTheory2->GetBinWidth(1)));
	  }
	  // b) for absolut differential cross sections:
	  else{
	    // take into account that e and mu channel were added 
	    unbinnedTheory->Scale(0.5);
	    unbinnedTheory2->Scale(0.5);
	    // scale by absolute xSec
	    unbinnedTheory->Scale(lumiweight(kSig, luminosity, 0, "muon"));
	    unbinnedTheory->Scale(1/luminosity);
	    unbinnedTheory2->Scale(lumiweight(kSig, luminosity, 0, "muon"));
	    unbinnedTheory2->Scale(1/luminosity);
	    // divide by binwidth
	    unbinnedTheory->Scale(1.0/(unbinnedTheory->GetBinWidth(1)));
	    unbinnedTheory2->Scale(1.0/(unbinnedTheory2->GetBinWidth(1)));
	  }
	  // choose style
	  histogramStyle(*unbinnedTheory        , kSig, false, 1.2, kRed+1); 
	  histogramStyle(*unbinnedTheory2       , kSig, false, 1.2, kRed+1);
	  // do smoothing
	  if(     xSecVariables_[i].Contains("ttbarY"   )) unbinnedTheory->Smooth(2);
	  else if(xSecVariables_[i].Contains("ttbarPt"  )) unbinnedTheory->Smooth(30);
	  else if(xSecVariables_[i].Contains("ttbarMass")) unbinnedTheory->Smooth(100);
	  else if(xSecVariables_[i].Contains("topPt"    )) unbinnedTheory->Smooth(10);
	  else if(xSecVariables_[i].Contains("topY"     )) unbinnedTheory->Smooth(10);
	  else if(xSecVariables_[i].Contains("bqEta"    )) unbinnedTheory->Smooth(2);
	  else if(xSecVariables_[i].Contains("bqPt"     )) unbinnedTheory->Smooth(10);
	  else if(xSecVariables_[i].Contains("lepEta"   )) unbinnedTheory->Smooth(4);
	  else if(xSecVariables_[i].Contains("lepPt"    )) unbinnedTheory->Smooth(10);
	  if(xSecVariables_[i].Contains("Norm")){
	    // draw binned theory curves
	    plotTheo->Draw("hist same");
	    // draw smoothed theory curves
	    // a) MC@NLO
	    int smoothFactor=0;
	    int rebinFactor=0;
	    int errorRebinFactor=0; 
	    int errorSmoothFactor=0;
	    TString plotNameMCAtNLO="";
	    double rangeLow=-1.;
	    double rangeHigh=-1.;
	    if(     xSecVariables_[i].Contains("ttbarMass")){ smoothFactor=200; rebinFactor=2; errorRebinFactor =  5 ; errorSmoothFactor =   10 ; plotNameMCAtNLO="hVisTTbarM" ; 
	      if(/*cutTtbarMass*/true){rangeLow=330. ; rangeHigh=1200.;} }
	    else if(xSecVariables_[i].Contains("ttbarY"   )){ smoothFactor=3 ; rebinFactor=20; errorRebinFactor =  5 ; errorSmoothFactor =   10 ; plotNameMCAtNLO="hVisTTbarY" ;}
	    else if(xSecVariables_[i].Contains("ttbarPt"  )){ smoothFactor=10; rebinFactor=2 ; errorRebinFactor =  2 ; errorSmoothFactor =    5 ; plotNameMCAtNLO="hVisTTbarPt";}
	    else if(xSecVariables_[i].Contains("topPt"    )){ smoothFactor=10; rebinFactor=10; errorRebinFactor = 10 ; errorSmoothFactor =   10 ; plotNameMCAtNLO="hVisTopPt"  ;}
	    else if(xSecVariables_[i].Contains("topY"     )){ smoothFactor=3 ; rebinFactor=20; errorRebinFactor =  5 ; errorSmoothFactor =   10 ; plotNameMCAtNLO="hVisTopY"   ;}
	    else if(xSecVariables_[i].Contains("lepPt"    )){ smoothFactor=10; rebinFactor=1 ; errorRebinFactor =  0 ; errorSmoothFactor =   10 ; plotNameMCAtNLO="hVisLepPt"  ;}
	    else if(xSecVariables_[i].Contains("lepEta"   )){ smoothFactor=10; rebinFactor=20; errorRebinFactor = 20 ; errorSmoothFactor =   10 ; plotNameMCAtNLO="hVisLepEta" ;}
	    else if(xSecVariables_[i].Contains("bqPt"     )){ smoothFactor=10; rebinFactor=2 ; errorRebinFactor =  5 ; errorSmoothFactor =   10 ; plotNameMCAtNLO="" ;}
	    else if(xSecVariables_[i].Contains("bqEta"    )){ smoothFactor=10; rebinFactor=2 ; errorRebinFactor =  5 ; errorSmoothFactor =   10 ; plotNameMCAtNLO="" ;}
	    else {std::cout << "unknow variable " << xSecVariables_[i] << std::endl; exit(0);}
	    bool error=true;
	    if(xSecVariables_[i].Contains("bqPt")||xSecVariables_[i].Contains("bqEta")) error=false;
	    if (DrawMCAtNLOPlot2) DrawNormTheoryCurve("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/ttbarNtupleCteq6m.root", plotNameMCAtNLO, smoothFactor, rebinFactor, kAzure, rangeLow, rangeHigh, error, errorRebinFactor, errorSmoothFactor, verbose-1, true, false);
	    plotTheo->Draw("hist same");
	    if (DrawMCAtNLOPlot2) DrawNormTheoryCurve("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/ttbarNtupleCteq6m.root", plotNameMCAtNLO, smoothFactor, rebinFactor, kAzure, rangeLow, rangeHigh, false, errorRebinFactor, errorSmoothFactor, verbose-1, false, false);
	    //plotNameMCAtNLO="analyzeTopPartonLevelKinematicsPhaseSpace/"+xSecVariables_[i];
	    //plotNameMCAtNLO.ReplaceAll("Norm","");
	    //DrawNormTheoryCurve("/afs/naf.desy.de/group/cms/scratch/tophh/tmp/topkinematics_combined_mcatnlo.root", plotNameMCAtNLO, smoothFactor, rebinFactor, kAzure+5, rangeLow, rangeHigh, false, errorRebinFactor, errorSmoothFactor, verbose-1, false, false);
	    // b) POWHEG
	    // configure configuration
	    smoothFactor=0;
	    rebinFactor=0;
	    TString plotNamePOWHEG="analyzeTop"+state+"LevelKinematics"+PS+"/"+xSecVariables_[i];
	    plotNamePOWHEG.ReplaceAll("Norm","");
	    rangeLow=-1.;
	    rangeHigh=-1.;
	    if(xSecVariables_[i].Contains("ttbarMass")){ smoothFactor=500; rebinFactor=5; 
	      if(cutTtbarMass){rangeLow=300.; rangeHigh=1200.;} }
	    else if(xSecVariables_[i].Contains("ttbarY"   )){ smoothFactor=3 ; rebinFactor=2 ; }
	    else if(xSecVariables_[i].Contains("ttbarPt"  )){ smoothFactor=10; rebinFactor=2 ; }
	    else if(xSecVariables_[i].Contains("topPt"    )){ smoothFactor=10; rebinFactor=10; }
	    else if(xSecVariables_[i].Contains("topY"     )){ smoothFactor=3 ; rebinFactor=2 ; }
	    else if(xSecVariables_[i].Contains("lepPt"    )){ smoothFactor=10; rebinFactor=1 ; }
	    else if(xSecVariables_[i].Contains("lepEta"   )){ smoothFactor=10; rebinFactor=2 ; }
	    else if(xSecVariables_[i].Contains("bqPt"     )){ smoothFactor=10; rebinFactor=2 ; }
	    else if(xSecVariables_[i].Contains("bqEta"    )){ smoothFactor=10; rebinFactor=2 ; }
	    // draw curve
	    if(DrawPOWHEGPlot2) DrawNormTheoryCurve("/afs/naf.desy.de/group/cms/scratch/tophh/tmp/topkinematics_combined_powheg.root", plotNamePOWHEG, smoothFactor, rebinFactor, kGreen+2, -1./*rangeLow*/, -1./*rangeHigh*/, false, 1., 1., verbose-1, false, false);
	    // c) reweighted histos for closure test
	    if(reweightClosure&&sys==sysNo){
	      histo_["reweighted"+plotName][kSig]->Draw("hist same");
	    }
	    // d) draw distorted parton truth histo including zprime
	    if(zprime!=""&&sys==sysNo){
	      histo_["modified"+plotName][kSig]->Draw("hist same");
	    }
	    // e) MADGRAPH
	    // GOSSIE quick fix
	    if(cutTtbarMass&&xSecVariables_[i].Contains("ttbarMass")) {
	      unbinnedTheory->GetXaxis()->SetRangeUser(325.,1200.);
	    }
	    unbinnedTheory->Draw("c same");
	    // set up legend
	    TLegend *leg = new TLegend();
	    leg->SetTextFont(42);
	    leg->SetTextSize(0.04);
	    leg->SetFillStyle(0);
	    leg->SetBorderSize(0);
	    leg->SetTextAlign(12);
	    // add data label to legend
	    leg->AddEntry(plotCombination  , dataLabel , "P" );
	    // add theory predictions to legend
	    // a) MADGRAPH
	    leg->AddEntry(unbinnedTheory   , "MadGraph", "L" );
	    // b) MC@NLO
	    if(DrawMCAtNLOPlot2){
	      //leg->AddEntry(errorBandsMCatNLO, "MC@NLO  ", "FL");
	      TString curveName=plotNameMCAtNLO;
	      curveName.ReplaceAll("Norm","");
	      curveName+="MC@NLOerrorBand";
	      TGraphAsymmErrors * mcatnlocurve =(TGraphAsymmErrors*)combicanvas->GetPrimitive(curveName);
	      if(mcatnlocurve) leg->AddEntry(mcatnlocurve, "MC@NLO  ", "FL");
	      else{
		if(verbose>0){
		  std::cout << "curve " << curveName << " not found. ";
		  curveName.ReplaceAll("erorBand","");
		  std::cout << "Will add " << curveName << " instead to the legend" << std::endl;
		}
		TH1F* mcatnlocurve2 =(TH1F*)combicanvas->GetPrimitive(curveName);
		if(mcatnlocurve2) leg->AddEntry(mcatnlocurve2, "MC@NLO  ", "L");	
	      }
	    }
	    // c) POWHEG
	    if(DrawPOWHEGPlot2){
	      TString curveName=xSecVariables_[i];
	      curveName.ReplaceAll("Norm","");
	      curveName+="POWHEG";
	      TH1F* powhegcurve =(TH1F*)combicanvas->GetPrimitive(curveName);
	      if(powhegcurve) leg->AddEntry(powhegcurve, "POWHEG  ", "L");
	    }
	    leg->Draw("same");
	    // add additional labels for closure test(s)
	    if(reweightClosure&&sys==sysNo) leg->AddEntry(histo_["reweighted"+plotName][kSig], "MadGraph Reweighted", "L");
	    if(zprime!=""     &&sys==sysNo) leg->AddEntry(histo_["modified"+plotName][kSig], "t#bar{t} & "+zprime+" GeV Z'", "L");
	    leg->SetX1NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength() -0.25);
	    leg->SetY1NDC(1.0 - gStyle->GetPadTopMargin()   - gStyle->GetTickLength() -0.05 - (double)leg->GetNRows()*0.04);
	    leg->SetX2NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength());
	    leg->SetY2NDC(1.0 - gStyle->GetPadTopMargin()   - gStyle->GetTickLength());
	    

	  }
	  plotCombination->Draw("e same");
          gPad->RedrawAxis(); 
	  DrawCMSLabels(true,luminosity);
	  DrawDecayChLabel("e/#mu + Jets Combined");
	  histo_[xSecVariables_[i]][sys]=(TH1F*)(plotCombination->Clone());
	  // save combined e+mu plot for systematic error calculation afterwards
	  canvas_[xSecVariables_[i]][sys]=(TCanvas*)(combicanvas->Clone());
	  canvas_[xSecVariables_[i]][sys]->SetTitle(xSecVariables_[i]);
	  canvas_[xSecVariables_[i]][sys]->SetName(xSecVariables_[i]);
	  if(save&&sys==sysNo){
	    int initialIgnoreLevel=gErrorIgnoreLevel;
	    if(verbose==0) gErrorIgnoreLevel=kWarning;
	    combicanvas->Print("./diffXSecFromSignal/plots/combined/"+dataSample+"/xSec/xSec"+xSecVariables_[i]+".eps"); 
	    combicanvas->Print("./diffXSecFromSignal/plots/combined/"+dataSample+"/xSec/xSec"+xSecVariables_[i]+".png");
	    gErrorIgnoreLevel=initialIgnoreLevel;
	  }
	  // close Canvas
	  combicanvas->Close();
	  //delete combicanvas;
	  delete combicanvas;
	}
	if(!(plotMu||plotEl)&&verbose>1){ 
	  std::cout << "ERROR: plot " << xSecVariables_[i]+"kData" << " not found in ";
	  std::cout << xSecFolder+"/"+subfolder+"/"+xSecVariables_[i];
	  std::cout << " for decay channel ";
	  if(!plotMu) std::cout << "muon";
	  if(!plotEl) std::cout << " electron";
	  std::cout << std::endl;
	}
      }
      if(!(canvasMu||canvasEl)&&verbose>1) std::cout << "ERROR: canvas " << xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << " not found in either one or both decay channels!" << std::endl;
    }
  }
  // ---
  //    save combined #mu+e plots to an .root file
  // ---
  // loop variables
  for(unsigned int i=0; i<xSecVariables_.size(); ++i){
    // loop systematic variations
    for(unsigned int sys=sysNo; sys<ENDOFSYSENUM; ++sys){
      if(histo_[xSecVariables_[i]][sys]){
	saveToRootFile("diffXSecTopSemiLep.root", canvas_[xSecVariables_[i]][sys], true, verbose,""+xSecFolder+"/"+sysLabel(sys));
      }
    }
  }
  // delete pointer
  closeStdTopAnalysisFiles(files_);
}
