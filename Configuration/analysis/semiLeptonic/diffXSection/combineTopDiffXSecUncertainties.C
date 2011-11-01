#include "basicFunctions.h"
#include "BCC.h"

void combineTopDiffXSecUncertainties(double luminosity=1143, bool save=true, unsigned int verbose=1, TString inputFolderName="TOP2011/110819_AnalysisRun", TString decayChannel="muon"){

  // ============================
  //  Systematic Variations:
  // ============================
  
  //      0: sysNo
  //      1: sysLumiUp                  2: sysLumiDown                
  //      3: sysPUUp                    4: sysPUDown                  
  //      5: sysJESUp                   6: sysJESDown                 
  //      7: sysJERUp                   8: sysJERDown                 
  //      9: sysTrigEffSFNormUp        10: sysTrigEffSFNormDown        
  //     11: sysTriggerEffSFShapeUpEta 12: sysTriggerEffSFShapeDownEta
  //     13: sysTriggerEffSFShapeUpPt  14: sysTriggerEffSFShapeDownPt  
  //     15: sysMuEffSFUp              16: sysMuEffSFDown 
  //     17: sysBtagSFUp               18: sysBtagSFDown  
  //     19: sysMisTagSFUp             20: sysMisTagSFDown  
  //     21: sysTopScaleUp             22: sysTopScaleDown            
  //     23: sysVBosonScaleUp          24: sysVBosonScaleDown          
  //     25: sysSingleTopScaleUp       26: sysSingleTopScaleDown     
  //     27: sysTopMatchUp             28: sysTopMatchDown            
  //     29: sysVBosonMatchUp          30: sysVBosonMatchDown         
  //     31: sysTopMassUp              32: sysTopMassDown            
  //     33: sysQCDUp                  34: sysQCDDown                 
  //     35: sysSTopUp                 36: sysSTopDown               
  //     37: sysDiBosUp                38: sysDiBosDown              
  //     39: sysShapeUp                40: sysShapeDown   
  //     41: sysPDFUp                  42: sysPDFDown  
  //     43: sysHadUp                  44: sysHadDown
  //     45: ENDOFSYSENUM
  //

  // ============================
  //  Set Root Style
  // ============================

  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  TGaxis::SetMaxDigits(2);
  myStyle.cd();
  gROOT->SetStyle("HHStyle");

  // ============================
  //  Parameter Configuration
  // ============================

  // set detail level of ouStput 
  // 0: no output, 1: std output 2: output for debugging
  // save: enable saving
  // dataSample: see if its "2010" or "2011" data
  TString dataSample="2011";
  if(luminosity<50.) dataSample="2010";
  // outputFile: target rootfile
  // NOTE: this must be identical with TString outputFileName 
  // in analyzeHypothesisKinFit.C
  TString outputFile="diffXSecTopSemi";
  if(decayChannel=="muon"    ) outputFile+="Mu"+dataSample;
  if(decayChannel=="electron") outputFile+="Elec"+dataSample;
  if(decayChannel=="combined"){
    outputFile+="Lep";
  }
  outputFile+=".root";
  // define folder where XSec plots are stored
  TString xSecFolder = "xSec";
  // save all plots into the following folder
  TString outputFolder = "./diffXSecFromSignal/plots/"+decayChannel+"/";
  if(dataSample!="") outputFolder+=dataSample;
  
  // ==========================================
  //  Basic Printout and Variable Definitions
  // ==========================================
  // define variables for combination
  // NOTE: these must be identical to those defined in 
  // xSecVariables_ in analyzeHypothesisKinFit.C
  std::vector<TString> xSecVariables_;
  TString xSecVariables[] ={"topPt", "topY", "ttbarPt", "ttbarMass", "ttbarY", "lepPt", "lepEta", "topPtNorm", "topYNorm", "ttbarPtNorm", "ttbarMassNorm", "ttbarYNorm", "lepPtNorm", "lepEtaNorm", "inclusive"};
  xSecVariables_.insert( xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString) );
  // chose min/max value[%] for relative uncertainty plots
  double errMax=40.0;
  double errMin= 0.0;
  // create plot container
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, std::map <unsigned int, TH1F*> > relativeUncertainties_;
  // create container to indicate that plots have been found 
  // and therefor systematics will be calculated
  std::map<TString, std::map<unsigned int, bool> > calculateError_;
  // create container for combined Errors
  std::map<TString, TGraphAsymmErrors*> totalErrors_;

  // ===================================
  //  Bin Center Corrections
  // ===================================

  //  basic configuration

  bool mergeLepAndHadTop=true;
  std::vector<TString> xSecVariableBranchNames_;
  for(unsigned int i=0; i<xSecVariables_.size(); ++i){
    if(!xSecVariables_[i].Contains("Norm")&&xSecVariables_[i]!="inclusive"){
      if(xSecVariables_[i].Contains("top")){
	xSecVariableBranchNames_.push_back(xSecVariables_[i]+"Had");
	xSecVariableBranchNames_.push_back(xSecVariables_[i]+"Lep");
      }
      else xSecVariableBranchNames_.push_back(xSecVariables_[i]);
    }
  }

  // parameter printout

  if(verbose>0){
    std::cout << std::endl << "executing combineTopDiffXSecUncertainties with " << dataSample << " data" << std::endl << std::endl;
    std::cout << "target file: " << outputFile << std::endl;
    std::cout << "target variables for cross sections:" << std::endl;

    // loop variables
    for(unsigned int i=0; i<xSecVariables_.size(); ++i){
      std::cout << xSecVariables_[i]; 
      if(i<xSecVariables_.size()-1) std::cout << ", ";
      else std::cout << std::endl;
    }
    std::cout << "target folder containing cross section plots: " << xSecFolder << std::endl;
    if(save) std::cout << "final plots will be saved in " << outputFile << " and as .eps in " << outputFolder << std::endl;
  }

  // loading bin center corrections
  std::cout << " Loading and calculating bin center corrections .... " << std::endl;
  BCC b("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/"+TopFilename(kSig, 0, (std::string)decayChannel),"analyzeTopPartonLevelKinematicsPhaseSpace",xSecVariableBranchNames_,mergeLepAndHadTop);
  b.runBCCCalculation();
  std::map<TString, std::vector<double> > correctedCenters_ = b.getMapWithCorrectedCentersInX();
  std::map<TString, std::vector<double> > corrCenterErrors_ = b.getMapWithCenterErrorsInX();
  // Output of results
  if(verbose>1){
    for (std::map<TString, std::vector<double> >::iterator iter1 = correctedCenters_.begin(); iter1 !=  correctedCenters_.end(); iter1++ ){
      std::cout << iter1->first << ": ";
      for (std::vector<double>::iterator iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++){
	std::cout << (*iter2) << " ";
      }
      std::cout << std::endl;
    }    
    for (std::map<TString, std::vector<double> >::iterator iter1 = corrCenterErrors_.begin(); iter1 != corrCenterErrors_.end(); iter1++ ){
      std::cout << iter1->first << ": ";
      for (std::vector<double>::iterator iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++){
	std::cout << (*iter2) << " ";
      }
      std::cout << std::endl;
    }
  }
  std::cout << " .... Executing bin center corrections finished." << std::endl;

  // ---
  //  Open rootfile
  // ---

  TFile* file = TFile::Open(outputFile, "UPDATE");
  if(verbose>1) std::cout << "opened file "+outputFile << std::endl;

  // check if file exist
  if(file&&!file->IsZombie()){
    if(verbose>0) std::cout << "target file found!" << std::endl;

    // ===============================================================
    //  Part A: get all data xSec with all systematic variations
    // ===============================================================

    if(verbose>0) std::cout << std::endl << "part A: loading plots" << std::endl;
    // loop systematic variations
    for(unsigned int sys=sysNo; sys<ENDOFSYSENUM; ++sys){
      TString subfolder=sysLabel(sys);      
      // loop variables
      for(unsigned int i=0; i<xSecVariables_.size(); ++i){
	// get canvas       
	TCanvas* canvas = (TCanvas*)file->Get(xSecFolder+"/"+subfolder+"/"+xSecVariables_[i]);
	if(canvas){
	  // get data plot for all systematics
	  TString plotName = xSecVariables_[i];
	  plotName.ReplaceAll("Norm","");
	  TH1F* plot= (TH1F*)canvas->GetPrimitive(plotName+"kData");
	  if(plot){ 
	    if(verbose>1) std::cout << "plot "+plotName+"kData in "+xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << " found!" << std::endl;
	    // go to root directory, keep plot when closing rootfile
	    gROOT->cd();
	    histo_[xSecVariables_[i]][sys]=(TH1F*)(plot->Clone());
	    calculateError_[xSecVariables_[i]][sys]=true;
	  }
	  if(!plot&&verbose>1){ 
	    std::cout << "ERROR: plot " << xSecVariables_[i]+"kData" << " not found in ";
	    std::cout << xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << std::endl;
	  }
	  // get MC prediction plot without systematic variation
	  if(sys==sysNo){
	    TH1F* MCplot= (TH1F*)canvas->GetPrimitive(plotName);
	    if(MCplot){ 
	      if(verbose>1) std::cout << "MC plot "+plotName+" in "+xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << " found!" << std::endl;
	      // go to root directory, keep plot when closing rootfile
	      gROOT->cd();
	      histo_[xSecVariables_[i]+"MC"][sys]=(TH1F*)(MCplot->Clone());
	    }
	  }
	}	
	else if(verbose>1) std::cout << "ERROR: canvas " << xSecFolder+"/"+subfolder+"/"+xSecVariables_[i] << " not found!" << std::endl;
      }
    }
    
    // ===============================================================
    //  Part B: calculate combined systematic+statistic error
    // ===============================================================

    if(verbose>0) std::cout << std::endl << "part B: calculate systematic errors for all variables and bins" << std::endl;
    // loop variables
    for(unsigned int i=0; i<xSecVariables_.size(); ++i){
      if(verbose>0) std::cout << std::endl << "variable: " << xSecVariables_[i] << std::endl;
      // check if any plot of the chosen variable has been found
      if(calculateError_.count(xSecVariables_[i])>0&&calculateError_[xSecVariables_[i]][sysNo]==true){
	// define object to save uncertainties
	int Nbins=histo_[xSecVariables_[i]][sysNo]->GetNbinsX();
	TGraphAsymmErrors* combinedErrors= new TGraphAsymmErrors(Nbins);
	// get plot without variation
	TH1F* noSysPlot=(TH1F*)histo_[xSecVariables_[i]][sysNo]->Clone();
	// loop bins
	for(int bin=1; bin<=noSysPlot->GetNbinsX(); ++bin){
	  double totalSystematicError = 0;
	  double stdBinXSecValue      = histo_[xSecVariables_[i]][sysNo]->GetBinContent(bin);
	  double MCpredBinVar         = (decayChannel=="combined") ? histo_[xSecVariables_[i]+"MC"][sysNo]->GetBinContent(bin) : -1.0;
	  // jump to bin without vanishing bin content
	  while(stdBinXSecValue==0&&bin<Nbins){
	    if(verbose>1) std::cout << "bin #" << bin << "/" << Nbins << " has bin content == 0, will be skipped!" << std::endl;
	    ++bin;
	    stdBinXSecValue=histo_[xSecVariables_[i]][sysNo]->GetBinContent(bin);
	  }
	  // if last bin is empty -> stop looping, next variable
	  if(bin==histo_[xSecVariables_[i]][sysNo]->GetNbinsX()&&stdBinXSecValue==0){
	    if(verbose>1){
	      std::cout << "bin #" << bin << "/" << Nbins << " has bin content == 0, will be skipped!" << std::endl;
	      std::cout << "last bin reached" << std::endl;
	    }
	  }
	  // else: continue with calculation
	  else{
	    if(verbose>0){ 
	      std::cout << std::endl << xSecVariables_[i] << " bin #" << bin << "/" << Nbins;
	      std::cout << "std value[pb/binwidth]: " << std::endl;
	      std::cout << "a) data   : " << stdBinXSecValue << std::endl;
	      std::cout << "b) MC pred: " << MCpredBinVar << std::endl;
	    }
	    // create plot that indicates all relative uncertainties
	    // one plot for every variable in every bin
	    unsigned int nSysTypes = 0;
	    unsigned int nSysCnt   = 0;
	    bool setNewLabel       = 0;
	    TString label="";
	    for(unsigned int sys=sysNo+1; sys<ENDOFSYSENUM; ++sys){
	      label = sysLabel(sys);
	      // Systemtatic uncertainties are symmetrized later:
	      // --> take only one into account if 'up' and 'down' variations exist
	      // --> take in any case into account if not distinguished between 'up' and 'down' 
	      if      (  label.Contains("Up")   || label.Contains("up"))    nSysTypes++;
	      else if (!(label.Contains("Down") || label.Contains("down"))) nSysTypes++;
	    }	    
	    TH1F* relSysPlot = new TH1F("relSysPlotBin"+getTStringFromInt(bin)+xSecVariables_[i], "relSysPlotBin"+getTStringFromInt(bin)+xSecVariables_[i], nSysTypes+3, 0.5, 0.5+nSysTypes+3);
	    relSysPlot->GetXaxis()->SetLabelSize(0.025);
	    // loop systematic variations
	    for(unsigned int sys=sysNo+1; sys<ENDOFSYSENUM; ++sys){
	      // set labels for relative uncertainties for bin & variable in map relativeUncertainties_
	      label = sysLabel(sys).ReplaceAll("sys","");
	      if      (  label.Contains("Up")){nSysCnt++; setNewLabel=1; label = label.ReplaceAll("Up","");}
	      else if (  label.Contains("up")){nSysCnt++; setNewLabel=1; label = label.ReplaceAll("up","");}
	      else if (!(label.Contains("Down") || label.Contains("down"))){nSysCnt++; setNewLabel=1;}
	      else setNewLabel=0;
	      if (setNewLabel){
		relSysPlot->GetXaxis()->SetBinLabel(nSysCnt,label);
		setNewLabel=0;
	      }
	      // create plot that indicates the relative systematic uncertainty
	      double sysDiff=0;
	      if(verbose>1) std::cout << sysLabel(sys);
	      // check if chosen systematic variation of chosen variable has been found and std value is nonzero
	      if(calculateError_[xSecVariables_[i]].count(sys)<=0||stdBinXSecValue==0){
		if(verbose>1){
		  if(stdBinXSecValue!=0) std::cout << ": not found" << std::endl;
		  else std::cout << ": std value is 0" << std::endl;
		}
	      }
	      else{
		// check if variable has to be considerered for total systematic error
		if(calculateError_[xSecVariables_[i]][sys]==true){
		  if(verbose>1) std::cout << "(considered): ";
		  double sysBinXSecValue=histo_[xSecVariables_[i]][sys]->GetBinContent(bin);
		  sysDiff=fabs(sysBinXSecValue-stdBinXSecValue);
		  if(sys==sysTopMassUp||sys==sysTopMassDown) sysDiff *= SF_TopMassUncertainty;                // SF_TopMassUncertainty: defined in basicFunctions.h
		  if(sys==sysHadUp    ||sys==sysHadDown )    sysDiff += constHadUncertainty*stdBinXSecValue;  // constHadUncertainty:   defined in basicFunctions.h
		}
		else if(verbose>1) std::cout << "(not considered): ";
		// print single systematic uncertainty absolut and relative for bin & variable
		if(verbose>1) std::cout << sysDiff << " ( = " << 100*sysDiff/stdBinXSecValue << "% )" << std::endl;
		// save relative systematic uncertainties for bin & variable (weight 0.5 due to error symmetrization)
		relSysPlot->Fill(nSysCnt, 100.0*0.5*sysDiff/stdBinXSecValue);
	      }
	      // for last systematic 
	      if(sys==ENDOFSYSENUM-1){
		// calculate total systematic error
		for (unsigned int n=0; n<nSysTypes; n++) totalSystematicError += pow(stdBinXSecValue*relSysPlot->GetBinContent(n+1)/100.0,2);
		totalSystematicError = sqrt(totalSystematicError);
		// go to root directory keep plot when closing rootfile
		gROOT->cd();
		// finally save relative uncertainties in map relativeUncertainties_
		relativeUncertainties_[xSecVariables_[i]][bin]=(TH1F*)relSysPlot->Clone();
		// get statistical and total uncertainties
		double statErrorBinVar     = noSysPlot->GetBinError(bin);
		double combinedErrorBinVar = sqrt(totalSystematicError*totalSystematicError + statErrorBinVar*statErrorBinVar);
		// print statistical, systematic and total uncertainties, absolut and relative for bin & variable
		if(verbose>0){
		  std::cout << "total statistic uncertainty:  " << " +/- " << statErrorBinVar      << " (" << 100*statErrorBinVar/stdBinXSecValue      << "% )" << std::endl;
		  std::cout << "total systematic uncertainty: " << " +/- " << totalSystematicError << " (" << 100*totalSystematicError/stdBinXSecValue << "% )" << std::endl;
		  std::cout << "total uncertainty:            " << " +/- " << combinedErrorBinVar  << " (" << 100*combinedErrorBinVar/stdBinXSecValue  << "% )" << std::endl;
		}
		// print MC prediction value and difference in std variations
		double xSecDiff=stdBinXSecValue-MCpredBinVar;
		double absError=combinedErrorBinVar;
		double relativeDifference=xSecDiff/absError; 
		if(verbose>0){
		  std::cout << "difference data-MC = " << xSecDiff << " pb" << std::endl;
		  std::cout << " ( = " << (xSecDiff/stdBinXSecValue)*100 << "% )" << std::endl;
		  std::cout << " ( = " << relativeDifference << " std variations )" << std::endl;
		}
		// save relative uncertainties for bin & variable in map relativeUncertainties_
		// a) statistic uncertainty
		relativeUncertainties_[xSecVariables_[i]][bin]->SetBinContent(nSysTypes+1, 100*statErrorBinVar/stdBinXSecValue);
		relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->SetBinLabel(nSysTypes+1, "statistical");
		// b) total systematic uncertainty
		relativeUncertainties_[xSecVariables_[i]][bin]->SetBinContent(nSysTypes+2, 100*totalSystematicError/stdBinXSecValue);
		relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->SetBinLabel(nSysTypes+2, "total syst.");
		// c) total stat+systematic uncertainty
		relativeUncertainties_[xSecVariables_[i]][bin]->SetBinContent(nSysTypes+3, 100*combinedErrorBinVar/stdBinXSecValue);
		relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->SetBinLabel(nSysTypes+3, "total");
		// set combined errors for final xSec plot
		double pointXValue = histo_[xSecVariables_[i]][sysNo]->GetBinCenter(bin);
		double pointXError = 0;
		if(decayChannel=="combined"&&xSecVariables_[i]!="inclusive"){
		  TString plotName=xSecVariables_[i];
		  plotName.ReplaceAll("Norm","");
		  pointXValue = correctedCenters_[plotName].at(bin-1);
		  pointXError = corrCenterErrors_[plotName].at(bin-1);
		  pointXError=0;
		}
		combinedErrors->SetPoint(0, 0, -1000);
		combinedErrors->SetPoint(bin, pointXValue, histo_[xSecVariables_[i]][sysNo]->GetBinContent(bin));
		combinedErrors->SetPointError(bin, pointXError, pointXError, combinedErrorBinVar, combinedErrorBinVar);
		// define style for relative error plots, uncertainties are only plotted positively after implementing the symmetrization
		histogramStyle(*relativeUncertainties_[xSecVariables_[i]][bin], kSig, true, 2.0, kBlack); 
		relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->LabelsOption("v");
		relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->SetLabelSize(0.05);
		relativeUncertainties_[xSecVariables_[i]][bin]->SetMaximum(errMax);
		relativeUncertainties_[xSecVariables_[i]][bin]->SetMinimum(errMin);
		double histMax = relativeUncertainties_[xSecVariables_[i]][bin]->GetBinContent(relativeUncertainties_[xSecVariables_[i]][bin]->GetMaximumBin());
		if (histMax>errMax){
		  relativeUncertainties_[xSecVariables_[i]][bin]->SetMaximum(1.2*histMax);
		}
		relativeUncertainties_[xSecVariables_[i]][bin]->SetStats(kFALSE);
		relativeUncertainties_[xSecVariables_[i]][bin]->GetYaxis()->SetTitle("Relative Uncertainty (symmetrized) [%]");
		relativeUncertainties_[xSecVariables_[i]][bin]->GetYaxis()->SetTitleOffset(1.2);
		// save asymmetric errors in map totalErrors_
		combinedErrors->SetLineWidth(1.0);
		combinedErrors->SetLineColor(histo_[xSecVariables_[i]][sysNo]->GetLineColor());
		totalErrors_[xSecVariables_[i]]=(TGraphAsymmErrors*)(combinedErrors->Clone());
		whipEmptyBinsAway(totalErrors_[xSecVariables_[i]], verbose);
		// remove ugly first point in m(ttbar)
		if(xSecVariables_[i].Contains("ttbarMass")){
		  totalErrors_[xSecVariables_[i]]->SetPoint(1, 0, -1000);
		}
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
    
    // ===============================================================
    //  Part C: draw plot with combined systematic+statistic error
    //          in new cross section plot
    // ===============================================================

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
	      //canvasStyle(*relUnCertaintyCanvas);
	      relUnCertaintyCanvas->SetBottomMargin(0.30);
	      relUnCertaintyCanvas->SetLeftMargin(0.10);
	      relUnCertaintyCanvas->SetRightMargin(0.10);
	      relUnCertaintyCanvas->SetTopMargin(0.07);
	      relUnCertaintyCanvas->cd(0);
	      relUnCertaintyCanvas->SetGrid(1,1);
	      // draw plot into canvas
	      relativeUncertainties_[xSecVariables_[i]][bin]->Draw("hist");
	      relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->SetTickLength(0.0);
	      // draw axis also on the right side of canvas, uncertainties are only plotted positively after implementing the symmetrization
	      double xPosition = relativeUncertainties_[xSecVariables_[i]][bin]->GetXaxis()->GetXmax();
	      double histMax   = relativeUncertainties_[xSecVariables_[i]][bin]->GetBinContent(relativeUncertainties_[xSecVariables_[i]][bin]->GetMaximumBin());
	      double max       = ( errMax>histMax ) ? errMax : 1.2*histMax;
	      double min       = errMin;
	      TGaxis *axis = new TGaxis(xPosition,min,xPosition,max,min,max,relativeUncertainties_[xSecVariables_[i]][bin]->GetYaxis()->GetNdivisions(),"+L");
	      axis->SetLabelSize(myStyle.GetLabelSize());
	      axis->SetLabelFont(myStyle.GetLabelFont());
	      axis->SetLabelOffset(myStyle.GetLabelOffset());
	      axis->Draw("same");
	      // draw every systematic variation with different color
	      TH1F* relUnCertaintyCopy = (TH1F*)relativeUncertainties_[xSecVariables_[i]][bin]->Clone();
	      int colourCounter=1;
	      unsigned int colour=kBlack;
	      for(int sys=1; sys<=relativeUncertainties_[xSecVariables_[i]][bin]->GetNbinsX(); ++sys, ++colourCounter){
		colour = (colourCounter%2==0) ? kYellow-7 : 8;
		relUnCertaintyCopy->Scale(0.);
		relUnCertaintyCopy->SetBinContent(sys, relativeUncertainties_[xSecVariables_[i]][bin]->GetBinContent(sys));
		// single systematic uncertainties
		if(sys<=relativeUncertainties_[xSecVariables_[i]][bin]->GetNbinsX()-3){
		  relUnCertaintyCopy->SetFillColor(colour);
		  relUnCertaintyCopy->DrawCopy("hist same");
		}
		// statistical uncertainty
		else if(sys==relativeUncertainties_[xSecVariables_[i]][bin]->GetNbinsX()-2){
		  relUnCertaintyCopy->SetFillColor(kRed-7);
		  relUnCertaintyCopy->DrawCopy("hist same");
		}
		// total systematic uncertainty
		else if(sys==relativeUncertainties_[xSecVariables_[i]][bin]->GetNbinsX()-1){
		  relUnCertaintyCopy->SetFillColor(kRed+2);
		  relUnCertaintyCopy->DrawCopy("hist same");
		}
		// total uncertainty
		else if(sys==relativeUncertainties_[xSecVariables_[i]][bin]->GetNbinsX()){
		  relUnCertaintyCopy->SetFillColor(38);
		  relUnCertaintyCopy->DrawCopy("hist same");
		  gPad->RedrawAxis();
		}
	      }
	      // save canvas to file
	      if(save) saveToRootFile( outputFile, relUnCertaintyCanvas, true, verbose, "relativeUncertainties/"+xSecVariables_[i]);
	      // save canvas as eps
	      int initialIgnoreLevel=gErrorIgnoreLevel;
	      if(verbose==0) gErrorIgnoreLevel=kWarning;
	      if(save){
		TString saveName=outputFolder+"/uncertainties/relativeUncertainties"+xSecVariables_[i]+"Bin"+getTStringFromInt(bin);
		if(decayChannel=="combined") saveName+="Combined";
		relUnCertaintyCanvas->Print(saveName+".eps");
		relUnCertaintyCanvas->Print(saveName+".png");
	      }
	      gErrorIgnoreLevel=initialIgnoreLevel;
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
	    // for inclusive xSecs
	    if(xSecVariables_[i].Contains("inclusive")){
	      TCanvas* canvas2 = new TCanvas(xSecVariables_[i], xSecVariables_[i], 600, 600);
	      //canvasStyle(*canvas2);
	      canvas2->SetLeftMargin(0.05);
	      canvas2->cd();
	      canvas2->SetTitle(xSecVariables_[i]);
	      //canvas2->SetGrid(1,0);
	      // draw xSec 
	      int NxSecBins=3000;
	      double xSecMax=300.0;
	      double xSecMin=0.;
	      TH1F* finalInclusiveXSec = new TH1F( "finalInclusive", "finalInclusive", NxSecBins, xSecMin, xSecMax);
	      // x axis as xSec[pb] indicator
	      int xSecBin=roundToInt(histo_["inclusive"][sysNo]->GetBinContent(1)*((double)NxSecBins)/xSecMax)+1;
	      finalInclusiveXSec->SetBinContent(xSecBin, 1);
	      finalInclusiveXSec->SetBinError(xSecBin, 0);
	      histogramStyle(*finalInclusiveXSec, kData , false);
	      axesStyle(*finalInclusiveXSec, "#sigma(t#bar{t}#rightarrowX) [pb]", " ", 0, 4);
	      finalInclusiveXSec->GetYaxis()->SetNdivisions(0);
	      finalInclusiveXSec->GetXaxis()->SetNdivisions(510);
	      finalInclusiveXSec->GetXaxis()->SetNoExponent(true);
	      finalInclusiveXSec->GetYaxis()->SetTitleSize(0.0);							
	      finalInclusiveXSec->Draw("axis");
	      // draw Theory expectation     
	      double theoryXSecNLL=165.0;
	      double theoryXSecNLO=157.5;
	      double theoryErrorNLOUp  =23.2;
	      double theoryErrorNLODown=24.4;
	      double theoryErrorNLLUp  =sqrt(5*5+9*9);
	      double theoryErrorNLLDown=sqrt(9*9+9*9);
	      TBox* TheoryError = new TBox(theoryXSecNLO-theoryErrorNLODown, 0.0, theoryXSecNLO+theoryErrorNLOUp, 4.0);
	      TBox* TheoryError2= new TBox(theoryXSecNLL-theoryErrorNLLDown, 0.0 ,theoryXSecNLL+theoryErrorNLLUp, 4.0);
	      TheoryError->SetFillColor(kGray);
	      TheoryError2->SetFillColor(kGray+1);
	      TheoryError->Draw ("same");
	      TheoryError2->Draw("same");
	      // our Analysis result
	      double xSecValue=histo_["inclusive"][sysNo]->GetBinContent(1);
	      double xSecError=histo_["inclusive"][sysNo]->GetBinError(1);
	      double totalErrorUp  = totalErrors_[xSecVariables_[i]]->GetErrorYhigh(1);
	      double totalErrorDown= totalErrors_[xSecVariables_[i]]->GetErrorYlow(1);
	      // 2010 CMS result
	      double cms2010xSecValue=158.;
	      double cms2010ErrorUp  =sqrt(10.*10.+6.*6.+15.*15.);
	      double cms2010ErrorDown=sqrt(10.*10.+6.*6.+15.*15.);
	      double cms2010StatError=10;
	      // 2011 CMS result - semleptonic TOP-11-003
	      double cms2011xSecValue=164.0;
	      double cms2011ErrorUp  =sqrt(3.0*3.0+12.0*12.0+7.0*7.0);
	      double cms2011ErrorDown=sqrt(3.0*3.0+12.0*12.0+7.0*7.0);
	      double cms2011StatError=3.0;
	      if(verbose>0){
		std::cout << "xSec:            " << xSecValue      << std::endl;
		std::cout << "stat. error: +/- " << xSecError      << " (" << xSecError/xSecValue      << ")" << std::endl;
		std::cout << "tot. error up  : " << totalErrorUp   << " (" << totalErrorUp/xSecValue   << ")" << std::endl;	      
		std::cout << "tot. error down: " << totalErrorDown << " (" << totalErrorDown/xSecValue << ")" << std::endl;
	      }
	      totalErrors_[xSecVariables_[i]+"AllInclusive"] = new TGraphAsymmErrors(3);  // number of data point as argument to constructor
	      totalErrors_[xSecVariables_[i]+"AllInclusive"]->SetPoint(0, xSecValue,        1);
	      totalErrors_[xSecVariables_[i]+"AllInclusive"]->SetPoint(1, cms2011xSecValue, 2);
	      totalErrors_[xSecVariables_[i]+"AllInclusive"]->SetPoint(2, cms2010xSecValue, 3);
	      totalErrors_[xSecVariables_[i]+"AllInclusive"]->SetPointError(0, totalErrorDown,   totalErrorUp,   0, 0);
	      totalErrors_[xSecVariables_[i]+"AllInclusive"]->SetPointError(1, cms2011ErrorDown, cms2011ErrorUp, 0, 0);
	      totalErrors_[xSecVariables_[i]+"AllInclusive"]->SetPointError(2, cms2010ErrorDown, cms2010ErrorUp, 0, 0);
	      totalErrors_[xSecVariables_[i]+"AllInclusive"]->SetLineWidth(3);
	      totalErrors_[xSecVariables_[i]+"AllInclusive"]->SetMarkerSize(1.5);
	      totalErrors_[xSecVariables_[i]+"AllInclusive"]->SetMarkerStyle(20);
	      totalErrors_[xSecVariables_[i]+"AllInclusive"]->SetMarkerColor(kRed+1);
	      totalErrors_[xSecVariables_[i]+"AllInclusive"]->SetLineColor(kRed+1);
	      finalInclusiveXSec->Draw("axis same");
	      drawLine(xSecValue-xSecError,               1.0, xSecValue+xSecError,               1.0, kRed+1, 6, 1);
	      drawLine(cms2011xSecValue-cms2011StatError, 2.0, cms2011xSecValue+cms2011StatError, 2.0, kRed+1, 6, 1);	  
	      drawLine(cms2010xSecValue-cms2010StatError, 3.0, cms2010xSecValue+cms2010StatError, 3.0, kRed+1, 6, 1);
	      totalErrors_[xSecVariables_[i]+"AllInclusive"]->Draw("p same");
	      //Labels
	      DrawLabel("CMS 2010 combined" , 0.07, 0.70, 0.4, 0.75); 
	      DrawLabel("2010 data, 36/pb"  , 0.07, 0.65, 0.4, 0.70);
	      DrawLabel("(arXiv:1108.3773)" , 0.07, 0.60, 0.4, 0.65);

	      DrawLabel("CMS 2011 (l + Jets)   " , 0.07, 0.50, 0.4, 0.55); 
	      DrawLabel("2011 Data, 0.8-1.09/fb" , 0.07, 0.45, 0.4, 0.50);
	      DrawLabel("(TOP-11-003)"           , 0.07, 0.40, 0.4, 0.45);

	      TString channelLabel="unknown";
	      TString dataLabel=Form(dataSample+" data, %2.1f fb^{-1}",luminosity/1000);
	      if(decayChannel.Contains("mu")) channelLabel="#mu + Jets";
	      if(decayChannel.Contains("el")) channelLabel="e + Jets";
	      DrawLabel(channelLabel, 0.07, 0.30, 0.4, 0.35);
	      DrawLabel(dataLabel,    0.07, 0.25, 0.4, 0.30);
	      canvas=(TCanvas*)canvas2->Clone();
	    }
	    // for differential xSecs
	    else{
	      canvas->cd();
	      canvas->SetTitle(xSecVariables_[i]);
	      // unset exp xaxis
	      totalErrors_[xSecVariables_[i]]->GetXaxis()->SetNoExponent(true);
	      double max=totalErrors_[xSecVariables_[i]]->GetMaximum();
	      max*=1.3;
	      if(max>1&&max<100) totalErrors_[xSecVariables_[i]]->GetYaxis()->SetNoExponent(false);
	      else totalErrors_[xSecVariables_[i]]->GetYaxis()->SetNoExponent(true);
	      // for combined cross sections:
	      // change TH1F with statistical errors into 
	      // TGraphAsymmErrors with bin center corrections
	      if(decayChannel=="combined"&&xSecVariables_[i]!="inclusive"){
		TString plotName = xSecVariables_[i];
		std::cout << "shifted stat value for: variable " << plotName << std::endl;
		plotName.ReplaceAll("Norm","");
		// get data plot
		TH1F* dataStat = (TH1F*)canvas->GetPrimitive(plotName+"kData");
		// convert to TGraphAsymmErrors
		TGraphAsymmErrors* statErrors= new TGraphAsymmErrors(dataStat->GetNbinsX());
		statErrors->SetLineWidth(1.0) ; // totalErrors_[xSecVariables_[i]]->GetLineWidth());
		statErrors->SetLineColor(totalErrors_[xSecVariables_[i]]->GetLineColor());
		for(int bin=1; bin<=dataStat->GetNbinsX(); ++bin){
		  if(dataStat->GetBinWidth(bin)!=0){
		    double pointXValue = correctedCenters_[plotName].at(bin-1);
		    double pointXError = corrCenterErrors_[plotName].at(bin-1);
		    double pointYError = dataStat->GetBinError(bin);
		    statErrors->SetPoint(bin, pointXValue, dataStat->GetBinContent(bin));
		    statErrors->SetPoint(0, 0, -1000);
		    pointXError=0;
		    statErrors->SetPointError(bin, pointXError, pointXError, pointYError, pointYError);
		  }
		}
		whipEmptyBinsAway(statErrors, verbose);
		// print new object
		statErrors->Draw("p same");
		// delete (old) TH1F plot from canvas
		canvas->GetListOfPrimitives()->Remove(canvas->GetPrimitive(plotName+"kData"));
	      }
	      // Draw errors into Canvas
	      totalErrors_[xSecVariables_[i]]->Draw("p Z same");
	      canvas->SetName (xSecVariables_[i]);
	    }
	    // save Canvas
	    int initialIgnoreLevel=gErrorIgnoreLevel;
	    if(verbose==0) gErrorIgnoreLevel=kWarning;
	    // a) within rootFile
	    if(save) saveToRootFile(outputFile, canvas, true, verbose, "finalXSec");
	    // b) as eps and png
	    if(save){
	      TString saveName=outputFolder+"/xSec/finalXSec"+xSecVariables_[i];
	      if(decayChannel=="combined") saveName+="Combined";
	      canvas->Print(saveName+".eps");
	      canvas->Print(saveName+".png");
	    }
	    gErrorIgnoreLevel=initialIgnoreLevel;
	    //delete statErrors;
	  }
	}
      }
    }
  }
  else std::cout << std::endl << "ERROR:target file does not exist or is broken!" << std::endl;

  // close file
  file->Close();
}
