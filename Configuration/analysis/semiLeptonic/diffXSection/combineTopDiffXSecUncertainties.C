#include "basicFunctions.h"

void combineTopDiffXSecUncertainties(){
  /* systematicVariation: which systematic shift do you want to make? from basicFunctions.h:
     0:sysNo              1:sysLumiUp          2:sysLumiDown          3:sysJESUp      
     4:sysJESDown         5:sysJERUp           6:sysJERDown           7:sysTopScaleUp 
     8:sysTopScaleDown    9:sysVBosonScaleUp  10:sysVBosonScaleDown  11:sysTopMatchUp 
     12:sysTopMatchDown  13:sysVBosonMatchUp  14:sysVBosonMatchDown  15:sysMuEffSFup  
     16:sysMuEffSFdown   17:sysISRFSRup       18:sysISRFSRdown       19:sysPileUp    
     20:sysQCDup         21:sysQCDdown
  */

  // ---
  //    parameter Configuration
  // ---
  // set detail level of output 
  // 0: no output, 1: std output 2: output for debugging
  unsigned int verbose=0;
  // enable saving
  bool save=true;
  // see if its 2010 or 2011 data
  TString dataSample="2010";
  // target rootfile
  // NOTE: this must be identical with TString outputFileName 
  // in analyzeHypothesisKinFit.C
  TString outputFile="diffXSecTopSemiMu"+dataSample+".root";
  // define folder where XSec plots are stored
  TString xSecFolder = "xSec";
  // save all plots into the following folder
  TString outputFolder = "./diffXSecFromSignal/plots/kinFit/";
  if(dataSample!="") outputFolder+=dataSample+"/";
  // define some rootstyle options
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetEndErrorSize(8);
  
  // ---
  //    basic printout and variable definitions
  // ---
  // define variables for combination
  // NOTE: these must be identical to those defined in 
  // xSecVariables_ in analyzeHypothesisKinFit.C
  std::vector<TString> xSecVariables_;
  TString xSecVariables[] ={"topPt", "topY", "ttbarPt", "ttbarMass", "ttbarY"};
  xSecVariables_.insert( xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString) );
  // chose min/max value[%] for relative uncertainty plots
  double errMax=100.;
  double errMin=-1*errMax;
  // create plot container
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, std::map <unsigned int, TH1F*> > relativeUncertainties_;
  // create container to indicate that plots have been found 
  // and therefor systematics will be calculated
  std::map<TString, std::map<unsigned int, bool> > calculateError_;
  // create container for combined Errors
  std::map<TString, TGraphAsymmErrors*> totalErrors_;
  // parameter printout
  if(verbose>0) std::cout << std::endl << "executing combineTopDiffXSecUncertainties with " << dataSample << " data" << std::endl << std::endl;
  if(verbose>0) std::cout << "target file: " << outputFile << std::endl;
  if(verbose>0) std::cout << "target variables for cross sections:" << std::endl;
  // loop variables
  for(unsigned int i=0; i<xSecVariables_.size(); ++i){
    if(verbose>0){
      std::cout << xSecVariables_[i]; 
      if(i<xSecVariables_.size()-1) std::cout << ", ";
      else std::cout << std::endl;
    }
  }
  if(verbose>0) std::cout << "target folder containing cross section plots: " << xSecFolder << std::endl;
  if(verbose>0&&save) std::cout << "final plots will be saved in " << outputFile << " and as .eps in " << outputFolder << std::endl;

  // ---
  //    open rootfile
  // ---
  TFile* file = TFile::Open(outputFile, "UPDATE");
  // check if file exist
  if(file&&!file->IsZombie()){
    if(verbose>0) std::cout << "target file found!" << std::endl;
    // ---
    //    part A: get all data xSec with all systematic variations
    // ---
    if(verbose>0) std::cout << std::endl << "part A: loading plots" << std::endl;
    // loop systematic variations
    for(unsigned int sys=sysNo; sys<=sysDiBosDown; ++sys){
      TString subfolder=sysLabel(sys);
      // loop variables
      for(unsigned int i=0; i<xSecVariables_.size(); ++i){
	// get canvas
	TCanvas* canvas = (TCanvas*)file->Get(xSecFolder+"/"+subfolder+"/"+xSecVariables_[i]);
	if(canvas){
	  // get data plot for all systematics
	  TH1F* plot= (TH1F*)canvas->GetPrimitive(xSecVariables_[i]+"kData");
	  if(plot){ 
	    if(verbose>1) std::cout << "plot "+xSecVariables_[i]+"kData in "+xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << " found!" << std::endl;
	    // got to root directory keep plot when closing rootfile
	    gROOT->cd();
	    histo_[xSecVariables_[i]][sys]=(TH1F*)(plot->Clone());
	    calculateError_[xSecVariables_[i]][sys]=true;
	  }
	  if(!plot&&verbose>1){ 
	    std::cout << "ERROR: plot " << xSecVariables_[i]+"kData" << " not found in ";
	    std::cout << xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << std::endl;
	  }
	}
	if(!canvas&&verbose>1) std::cout << "ERROR: canvas " << xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << " not found!" << std::endl;
      }
    }
    
    // ---
    //    part B:calculate combined systematic+statistic error
    // ---
    if(verbose>0) std::cout << std::endl << "part B: calculate systematic errors for all variables and bins" << std::endl;
    // loop variables
    for(unsigned int i=0; i<xSecVariables_.size(); ++i){
      if(verbose>0) std::cout << std::endl << "variable: " << xSecVariables_[i] << std::endl;
      double totalSystematicErrorUp  =0;
      double totalSystematicErrorDown=0;
      // check if any plot of the chosen variable has been found
      if(calculateError_.count(xSecVariables_[i])>0&&calculateError_[xSecVariables_[i]][sysNo]==true){
	// define object to save asymmetric errors
	int Nbins=histo_[xSecVariables_[i]][sysNo]->GetNbinsX();
	TGraphAsymmErrors* combinedErrors= new TGraphAsymmErrors(Nbins);
	// get plot without variation
	TH1F* noSysPlot=(TH1F*)histo_[xSecVariables_[i]][sysNo]->Clone();
	// loop bins
	for(int bin=1; bin<=noSysPlot->GetNbinsX(); ++bin){
	  double stdBinXSecValue=histo_[xSecVariables_[i]][sysNo]->GetBinContent(bin);
	  // jump to bin without vanishing bin content
	  while(stdBinXSecValue==0&&bin<Nbins){
	    if(verbose>1) std::cout << "bin #" << bin << "/" << Nbins << " has bin content ==0, will be skipped!" << std::endl;
	    ++bin;
	    stdBinXSecValue=histo_[xSecVariables_[i]][sysNo]->GetBinContent(bin);
	  }
	  // if last bin is empty -> stop looping, next variable
	  if(bin==histo_[xSecVariables_[i]][sysNo]->GetNbinsX()&&stdBinXSecValue==0){
	    if(verbose>1){
	      std::cout << "bin #" << bin << "/" << Nbins << " has bin content ==0, will be skipped!" << std::endl;
	      std::cout << "last bin reached" << std::endl;
	    }
	  }
	  // else: continue with calculation
	  else{
	    if(verbose>0){ 
	      std::cout << std::endl << xSecVariables_[i] << " bin #" << bin << "/" << Nbins;
	      std::cout << " ( std value[pb/binwidth]: " << stdBinXSecValue << " )" << std::endl;
	    }
	    // create plot that indicates all relative uncertainties
	    // one plot for every variable in every bin
	    TH1F* relSysPlot = new TH1F("relSysPlotBin"+getTStringFromInt(bin)+xSecVariables_[i], "relSysPlotBin"+getTStringFromInt(bin)+xSecVariables_[i], sysDiBosDown+5, sysNo, sysDiBosDown+5);
	    relSysPlot->GetXaxis()->SetLabelSize(0.025);
	    // loop systematic variations
	    for(unsigned int sys=sysNo+1; sys<=sysDiBosDown; ++sys){
	      // set labels for relative uncertainties for bin & variable in map relativeUncertainties_
	      relSysPlot->GetXaxis()->SetBinLabel(sys, sysLabel(sys).ReplaceAll("sys",""));
	      // create plot that indicates the relative systematic uncertainty
	      double sysDiff=0;
	      if(verbose>0) std::cout << sysLabel(sys);
	      // check if chosen systematic variation of chosen variable has been found and std value is nonzero
	      if(calculateError_[xSecVariables_[i]].count(sys)<=0||stdBinXSecValue==0){
		if(verbose>0){
		  if(stdBinXSecValue!=0) std::cout << ": not found" << std::endl;
		  else std::cout << ": std value is 0" << std::endl;
		}
	      }
	      else{
		// check if variable has to be considerered for total systematic error
		if(calculateError_[xSecVariables_[i]][sys]==true){
		  if(verbose>0) std::cout << "(considered): ";
		  double sysBinXSecValue=histo_[xSecVariables_[i]][sys]->GetBinContent(bin);
		  sysDiff=sysBinXSecValue-stdBinXSecValue;
		  // asymmetric errors
		  if(sysDiff>0) totalSystematicErrorUp  +=sysDiff*sysDiff;
		  if(sysDiff<0) totalSystematicErrorDown+=sysDiff*sysDiff;
		}
		else{ 
		  if(verbose>0) std::cout << "(not considered): ";
		}
		// print single systematic uncertainty absolut and relative for bin & variable
		if(verbose>0) std::cout << sysDiff << " ( = " << 100*sysDiff/stdBinXSecValue << "% )" << std::endl;
		// save relative systematic uncertainties for bin & variable
		relSysPlot->SetBinContent(sys, 100*sysDiff/stdBinXSecValue);
	      }
	      // for last systematic 
	      if(sys==sysDiBosDown){
		// got to root directory keep plot when closing rootfile
		gROOT->cd();
		// finally save relative uncertainties in map relativeUncertainties_
		relativeUncertainties_[xSecVariables_[i]][bin]=(TH1F*)relSysPlot->Clone();
		// print total systematic uncertainty absolut and relative for bin & variable
		if(verbose>0){
		  std::cout << "total systematic uncertainty: " << std::endl;
		  std::cout << " +" << sqrt(totalSystematicErrorUp)   << " ( =";
		  std::cout << 100*sqrt(totalSystematicErrorUp  )/stdBinXSecValue << "% )" << std::endl;
		  std::cout << " -" << sqrt(totalSystematicErrorDown) << " ( =";
		  std::cout << 100*sqrt(totalSystematicErrorDown)/stdBinXSecValue << "% )" << std::endl;
		}
		// get statistical error
		double statErrorBinVar = noSysPlot->GetBinError(bin);
		double combinedErrorUpBinVar   = sqrt(totalSystematicErrorUp  +statErrorBinVar*statErrorBinVar);
		double combinedErrorDownBinVar = sqrt(totalSystematicErrorDown+statErrorBinVar*statErrorBinVar);
		// print statistical uncertainty absolut and relative for bin & variable
		if(verbose>0){
		  std::cout << "total statistic uncertainty: " << std::endl;
		  std::cout << " +/- " << statErrorBinVar << " ( =";
		  std::cout << 100*statErrorBinVar/stdBinXSecValue << "% )" << std::endl;
		}
		// save relative uncertainties for bin & variable in map relativeUncertainties_
		// a) statistic uncertainty
		relativeUncertainties_[xSecVariables_[i]][bin]->SetBinContent(sysDiBosDown+1, 100*statErrorBinVar/stdBinXSecValue);
		relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->SetBinLabel(sysDiBosDown+1, "statistical");
		// b) total systematic uncertainty up
		relativeUncertainties_[xSecVariables_[i]][bin]->SetBinContent(sysDiBosDown+2, 100*sqrt(totalSystematicErrorUp  )/stdBinXSecValue);
		relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->SetBinLabel(sysDiBosDown+2, "total syst. Up");
		// c) total systematic uncertainty down
		relativeUncertainties_[xSecVariables_[i]][bin]->SetBinContent(sysDiBosDown+3, -100*sqrt(totalSystematicErrorDown)/stdBinXSecValue);
		relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->SetBinLabel(sysDiBosDown+3, "total syst. Down");
		// d) total stat+systematic uncertainty up
		relativeUncertainties_[xSecVariables_[i]][bin]->SetBinContent(sysDiBosDown+4, 100*combinedErrorUpBinVar/stdBinXSecValue);
		relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->SetBinLabel(sysDiBosDown+4, "total Up");
		// e) total stat+systematic uncertainty down
		relativeUncertainties_[xSecVariables_[i]][bin]->SetBinContent(sysDiBosDown+5, -100*combinedErrorDownBinVar/stdBinXSecValue);
		relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->SetBinLabel(sysDiBosDown+5, "total Down");
		// set combined errors for final xSec plot
		combinedErrors->SetPoint(bin, histo_[xSecVariables_[i]][sysNo]->GetBinCenter(bin), histo_[xSecVariables_[i]][sysNo]->GetBinContent(bin));
		combinedErrors->SetPointError(bin, 0,0, combinedErrorDownBinVar, combinedErrorUpBinVar);
		// define style for relative error plots
		histogramStyle(*relativeUncertainties_[xSecVariables_[i]][bin], kData, false, 2.0); 
		relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->LabelsOption("v");
		relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->SetLabelSize(0.05);
		relativeUncertainties_[xSecVariables_[i]][bin]->SetMaximum(errMax);
		relativeUncertainties_[xSecVariables_[i]][bin]->SetMinimum(errMin);
		relativeUncertainties_[xSecVariables_[i]][bin]->SetStats(kFALSE);
		relativeUncertainties_[xSecVariables_[i]][bin]->GetYaxis()->SetTitle("rel. uncertainty (%)");
		relativeUncertainties_[xSecVariables_[i]][bin]->GetYaxis()->SetTitleOffset(1.2);
		// save asymmetric errors in map totalErrors_
		combinedErrors->SetLineWidth(histo_[xSecVariables_[i]][sysNo]->GetLineWidth());
		combinedErrors->SetLineColor(histo_[xSecVariables_[i]][sysNo]->GetLineColor());
		totalErrors_[xSecVariables_[i]]=(TGraphAsymmErrors*)(combinedErrors->Clone());
	      }
	    }
	    delete relSysPlot;
	  }
	}
      }
    }
    // close file
    // needed to be able to use the saveToRootFile function 
    // which also opens the file
    file->Close();

    // ---
    //    part C:draw plot with combined systematic+statistic error
    //           in new cross section plot
    // ---
    if(save){
      if(verbose>0) std::cout << std::endl << "part C: save xSec plots with stat.+sys. errors and plots with relative uncertainties" << std::endl;
      // loop variables
      for(unsigned int i=0; i<xSecVariables_.size(); ++i){
	// check if total combined errors are available
	if(totalErrors_.count(xSecVariables_[i])>0){
	  if(verbose>0) std::cout << std::endl << "variable: " << xSecVariables_[i] << std::endl;
	  // save rel uncertainties plot for all variables and bins
	  // loop bins
	  for(int bin=0; bin<=histo_[xSecVariables_[i]][sysNo]->GetNbinsX(); ++bin){
	    // make sure that plot exists
	    if(relativeUncertainties_.count(xSecVariables_[i])>0&&relativeUncertainties_[xSecVariables_[i]].count(bin)>0){
	      // create canvas for plot
	      TCanvas* relUnCertaintyCanvas = new TCanvas(relativeUncertainties_[xSecVariables_[i]][bin]->GetName() ,relativeUncertainties_[xSecVariables_[i]][bin]->GetTitle(), 600, 600);
	      canvasStyle(*relUnCertaintyCanvas);
	      relUnCertaintyCanvas->SetBottomMargin(0.30);
	      relUnCertaintyCanvas->SetLeftMargin(0.10);
	      relUnCertaintyCanvas->SetRightMargin(0.10);
	      relUnCertaintyCanvas->SetTopMargin   (0.07);
	      relUnCertaintyCanvas->cd(0);
	      relUnCertaintyCanvas->SetGrid(1,1);
	      // draw plot into canvas
	      relativeUncertainties_[xSecVariables_[i]][bin]->Draw("hist");
	      // draw axis also on the right side of canvas
	      TGaxis *axis = new TGaxis(30,errMin,30,errMax,errMin,errMax,relativeUncertainties_[xSecVariables_[i]][bin]->GetYaxis()->GetNdivisions(),"+L");
	      axis->Draw("same");
	      // redraw to have statistical error as +/-
	      TH1F* relUnCertaintyCopy = (TH1F*)relativeUncertainties_[xSecVariables_[i]][bin]->Clone();
	      relUnCertaintyCopy->SetBinContent(sysDiBosDown+1, (-1.)*(relUnCertaintyCopy->GetBinContent(sysDiBosDown+1)));
	      relUnCertaintyCopy->Draw("hist same");
	      // save canvas to file
	      if(save) saveToRootFile( outputFile, relUnCertaintyCanvas, true, verbose, "relativeUncertainties/"+xSecVariables_[i]);
	      // save canvas as eps
	      if(save) relUnCertaintyCanvas->Print(outputFolder+"/uncertainties/relativeUncertainties"+xSecVariables_[i]+"Bin"+getTStringFromInt(bin)+".eps");
	      // delete canvas
	      delete relUnCertaintyCanvas;
	      delete relUnCertaintyCopy;
	      delete axis;
	    }
	  }
	  // open file to get xSec canvas from it
	  file = TFile::Open(outputFile, "UPDATE");
	  // get Canvas
	  TCanvas* canvas = (TCanvas*)(file->Get(xSecFolder+"/sysNo/"+xSecVariables_[i])->Clone());
	  // close file
	  // needed to be able to use the saveToRootFile function 
	  // which also opens the file
	  file->Close();
	  if(canvas){
	    // Draw errors into Canvas
	    canvas->cd();
	    totalErrors_[xSecVariables_[i]]->Draw("p same");
	    canvas->SetTitle(xSecVariables_[i]);
	    canvas->SetName (xSecVariables_[i]);	  
	    // save Canvas
	    // a) within rootFile
	    if(save) saveToRootFile(outputFile, canvas, true, verbose, "finalXSec");
	    // b) as eps
	    if(save) canvas->Print(outputFolder+"/xSec/finalXSec"+xSecVariables_[i]+".eps");
	  }
	}
      }
    }
  }
  else std::cout << std::endl << "ERROR:target file does not exist or is broken!" << std::endl;
  // close file
  file->Close();
}
