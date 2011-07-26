#include "basicFunctions.h"

void bothDecayChannelsCombination(double luminosity=1090, bool save=true, unsigned int verbose=0){
	
  // ---
  //    Setup
  // ---
  // set root style
	
  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  myStyle.cd();
  TGaxis::SetMaxDigits(2);
  gROOT->SetStyle("HHStyle");

  // choose if xSec are extrapolated to whole phase space
  bool extrapolate=false;
  TString PS="";
  if(!extrapolate)PS="PhaseSpace";
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
  TString xSecVariables[] ={"topPt", "topY", "ttbarPt", "ttbarMass", "ttbarY", "topPtNorm", "topYNorm", "ttbarPtNorm", "ttbarMassNorm", "ttbarYNorm"};
  xSecVariables_.insert( xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString) );
  // create plot container for combined e+#mu plots
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, std::map <unsigned int, TCanvas*> > canvas_;
  // ---
  //    Combination for all kinematic variables x systematic variations available
  // ---
  // loop systematic variations
  for(unsigned int sys=sysNo; sys<=sysDiBosDown; ++sys){
    TString subfolder=sysLabel(sys);
    // loop variables
    for(unsigned int i=0; i<xSecVariables_.size(); ++i){
      // get canvas
      TCanvas* canvasMu   = (TCanvas*)(files_[kMuon    ]->Get(xSecFolder+"/"+subfolder+"/"+xSecVariables_[i]));
      TCanvas* canvasTheo = (TCanvas*)(files_[kMuon    ]->Get(xSecFolder+"/"+sysLabel(sysNo)+"/"+xSecVariables_[i]));
      TCanvas* canvasEl   = (TCanvas*)(files_[kElectron]->Get(xSecFolder+"/"+subfolder+"/"+xSecVariables_[i]));
      if(canvasMu&&canvasEl){
	// get data plots for all systematics
	TString plotName = xSecVariables_[i];
	plotName.ReplaceAll("Norm","");
	TH1F* plotMu   = (TH1F*)canvasMu  ->GetPrimitive(plotName+"kData");
	TH1F* plotTheo = (TH1F*)canvasTheo->GetPrimitive(plotName        );
	TH1F* plotEl   = (TH1F*)canvasEl  ->GetPrimitive(plotName+"kData");
	if(plotMu&&plotEl){ 
	  if(verbose>1){
	    std::cout << "plot "+plotName+"kData in "+xSecFolder+"/"+subfolder+"/"+xSecVariables_[i];
	    std::cout << " for both channels found!" << std::endl;
	  }
	  // combine the results
	  TH1F* plotCombination=(TH1F*)(plotMu->Clone());
	  plotCombination->Scale(0.0);
	  // loop bins
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
	  // adapt plot style
	  double max = plotTheo->GetMaximum();
	  max*=1.5;
	  plotTheo->GetXaxis()->SetNoExponent(true);
	  if(max>1&&max<100) plotTheo->GetYaxis()->SetNoExponent(true);
	  else plotTheo->GetYaxis()->SetNoExponent(false);
	  TString yTitle=plotTheo->GetYaxis()->GetTitle();
	  if(verbose>1)std::cout << "original title: " << yTitle  << std::endl;
	  yTitle.ReplaceAll("muon"," l = e,#mu");
	  if(verbose>1)std::cout << "new title: " << yTitle  << std::endl;
	  plotTheo->GetYaxis()->SetTitle(yTitle);
	  // create Canvas
	  TCanvas* combicanvas = new TCanvas("combicanvas", "combicanvas", 600, 600);
	  //canvasStyle(*combicanvas);
	  // plot into canvas
	  combicanvas->cd(0);
	  combicanvas->SetBottomMargin(myStyle.GetPadBottomMargin());
	  combicanvas->SetLeftMargin(myStyle.GetPadLeftMargin());
	  gStyle->SetEndErrorSize(8);
	  plotTheo->Draw("hist");
	  // get unbinned Madgraph theory curve
	  // add muon and electron channel to
	  // minimize statistical fluctuations
	  TH1F* unbinnedTheory = getTheoryPrediction("analyzeTopPartonLevelKinematics"+PS+"/"+plotName,"./diffXSecFromSignal/analysisRootFilesWithKinFit/"+TopFilename(kSig, 0, "muon"));
	  unbinnedTheory->Add(getTheoryPrediction("analyzeTopPartonLevelKinematics"+PS+"/"+plotName,"./diffXSecFromSignal/analysisRootFilesWithKinFit/"+TopFilename(kSig, 0, "electron")));
	  // normalize to unsit area fordiff. norm. plots
	  if(xSecVariables_[i].Contains("Norm")){
	    unbinnedTheory->Rebin(10);
	    unbinnedTheory->Scale(1.0/(unbinnedTheory->Integral(1,unbinnedTheory->GetNbinsX()+1)));
	    unbinnedTheory->Scale(0.1);
	  }
	  // take into account that e and mu channel were added 
	  else{
	    unbinnedTheory->Scale(0.5);
	  }
	  histogramStyle(*unbinnedTheory, kSig, false);
	  unbinnedTheory->Smooth(5);
	  unbinnedTheory->Draw("c same");
	  plotCombination->Draw("e1 same");
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
    for(unsigned int sys=sysNo; sys<=sysDiBosDown; ++sys){
      if(histo_[xSecVariables_[i]][sys]){
	saveToRootFile("diffXSecTopSemiLep.root", canvas_[xSecVariables_[i]][sys], true, verbose,"xSec/"+sysLabel(sys));
      }
    }
  }
}

