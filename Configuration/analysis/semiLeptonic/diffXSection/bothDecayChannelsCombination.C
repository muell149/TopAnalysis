#include "basicFunctions.h"

void bothDecayChannelsCombination(double luminosity=191, bool save=true, unsigned int verbose=2){

  // set root style
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetEndErrorSize(8);
  gStyle->SetPalette(1);
  TGaxis::SetMaxDigits(2);
  // decay channels
  enum channel {kMuon, kElectron};
  // define folder where XSec plots are stored
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
  // loop systematic variations
  for(unsigned int sys=sysNo; sys<=sysDiBosDown; ++sys){
    TString subfolder=sysLabel(sys);
    // loop variables
    for(unsigned int i=0; i<xSecVariables_.size(); ++i){
      // get canvas
      TCanvas* canvasMu = (TCanvas*)(files_[kMuon    ]->Get(xSecFolder+"/"+subfolder+"/"+xSecVariables_[i]));
      TCanvas* canvasEl = (TCanvas*)(files_[kElectron]->Get(xSecFolder+"/"+subfolder+"/"+xSecVariables_[i]));
      if(canvasMu&&canvasEl){
	// get data plots for all systematics
	TString plotName = xSecVariables_[i];
	plotName.ReplaceAll("Norm","");
	TH1F* plotMu= (TH1F*)canvasMu->GetPrimitive(plotName+"kData");
	TH1F* plotTheo=(TH1F*)canvasMu->GetPrimitive(plotName);
	TH1F* plotEl= (TH1F*)canvasEl->GetPrimitive(plotName+"kData");
	if(plotMu&&plotEl){ 
	  if(verbose>1) std::cout << "plot "+plotName+"kData in "+xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << " for both channels found!" << std::endl;
	  // combine the results
	  TH1F* plotCombination=(TH1F*)(plotMu->Clone());
	  plotCombination->Scale(0.);
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
	  plotTheo->GetXaxis()->SetNoExponent(true);
	  if(max>1&&max<100) plotTheo->GetYaxis()->SetNoExponent(true);
	  TString yTitle=plotTheo->GetYaxis()->GetTitle();
	  std::cout << yTitle  << std::endl;
	  yTitle.ReplaceAll("muon"," l = e,#mu");
	  std::cout << yTitle  << std::endl;
	  plotTheo->GetYaxis()->SetTitle(yTitle);
	  // create Canvas
	  TCanvas* combicanvas = new TCanvas("combicanvas", "combicanvas", 600, 600);
	  canvasStyle(*combicanvas);
	  // plot into canvas
	  combicanvas->cd(0);
	  plotTheo->Draw("hist");
	  plotCombination->Draw("e same");
	  // save the final plot
	  if(save){
	    combicanvas->Print("./diffXSecFromSignal/plots/kinFit/"+dataSample+"/combinedXSec/xSec"+xSecVariables_[i]+".eps"); 
	    combicanvas->Print("./diffXSecFromSignal/plots/kinFit/"+dataSample+"/combinedXSec/xSec"+xSecVariables_[i]+".png");
	  }
	  // close Canvas
	  combicanvas->Close();
	  //delete combicanvas;
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
}
