#include "basicFunctions.h"
#include "BCC.h"

void combineTopDiffXSecUncertainties(double luminosity=4980, bool save=true, unsigned int verbose=1, TString inputFolderName="RecentAnalysisRun", TString decayChannel="electron", bool exclShapeVar="true", bool extrapolate=false, bool hadron=false){

  // ============================
  //  Systematic Variations:
  // ============================
 
  //  0: noSys                                                      
  //  1: sysLumiUp                   2: sysLumiDown                               
  //  3: sysPUUp                     4: sysPUDown                   
  //  5: sysJESUp                    6: sysJESDown                  
  //  7: sysJERUp                    8: sysJERDown                  
  //  9: sysTrigEffSFNormUp         10: sysTrigEffSFNormDown         
  // 11: sysTriggerEffSFShapeUpEta  12: sysTriggerEffSFShapeDownEta 
  // 13: sysTriggerEffSFShapeUpPt   14: sysTriggerEffSFShapeDownPt  
  // 15: sysMuEffSFUp               16: sysMuEffSFDown              
  // 17: sysBtagSFShapeUpPt65       18: sysBtagSFShapeDownPt65  
  // 19: sysBtagSFShapeUpEta0p7     20: sysBtagSFShapeDownEta0p7
  // 21: sysMisTagSFUp              22: sysMisTagSFDown             
  // 23: sysTopScaleUp              24: sysTopScaleDown             
  // 25: sysVBosonScaleUp           26: sysVBosonScaleDown           
  // 27: sysSingleTopScaleUp        28: sysSingleTopScaleDown       
  // 29: sysTopMatchUp              20: sysTopMatchDown             
  // 31: sysVBosonMatchUp           32: sysVBosonMatchDown          
  // 33: sysTopMassUp               34: sysTopMassDown              
  // 35: sysQCDUp                   36: sysQCDDown                  
  // 37: sysSTopUp                  38: sysSTopDown                 
  // 39: sysDiBosUp                 40: sysDiBosDown                
  // 41: sysPDFUp                   42: sysPDFDown                  
  // 43: sysHadUp                   44: sysHadDown                  
  // 45: sysShapeUp                 46: sysShapeDown                
  // 47: ENDOFSYSENUM
 
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

  // verbose: set detail level of output 
  // 0: no output, 1: std output 2: output for debugging
  // save: enable saving
  // take care that prescaling of muon channel for full 2011 datset was taken into account
  if(luminosity==4980&&decayChannel=="muon"    ) luminosity=4955;
  if(luminosity==4955&&decayChannel=="electron") luminosity=4980;
  // choose phase space
  TString PS="";
  // a) for full PS use extrapolate=true;
  if(!extrapolate) PS="PhaseSpace";
  // b) for restricted phase space:
  // b1) parton PS: hadron=false
  // b2) hadron PS: hadron=true
  TString LV="Parton";
  if(!extrapolate&&hadron) LV="Hadron";
  if(verbose>1){
    if(extrapolate) std::cout << "full Phase Space will be used!" << std::endl; 
    else std::cout << LV << " level Phase Space will be used!" << std::endl; 
  }
  TString universalplotLabel="";
  if(extrapolate) universalplotLabel="FullPS";
  else universalplotLabel=LV+"LvPS";
  // dataSample: see if its "2010" or "2011" data
  TString dataSample="2011";
  if(luminosity<50.) dataSample="2010";
  // outputFile: target rootfile
  // NOTE: this must be identical with TString outputFileName 
  // in analyzeHypothesisKinFit.C
  TString outputFile="diffXSecTopSemi";
  if(decayChannel=="muon"    ) outputFile+="Mu"+dataSample;
  if(decayChannel=="electron") outputFile+="Elec"+dataSample;
  if(decayChannel=="combined") outputFile+="Lep";
  outputFile+=LV+PS+".root";
  // define folder where XSec plots are stored
  TString xSecFolder = "xSec";
  // save all plots into the following folder
  TString outputFolder = "./diffXSecFromSignal/plots/"+decayChannel+"/";
  if(dataSample!="") outputFolder+=dataSample;
  // use BCC values?
  bool useBCC=false;
  unsigned int shapeVarIdx = sysShapeDown/2; // index variable (bin number!) to track shape variations index among all uncertainties, 
                                             // value might change later, sysShapeDown/2 is the default
  
  // ==========================================
  //  Basic Printout and Variable Definitions
  // ==========================================
  // define variables for combination
  // NOTE: these must be identical to those defined in 
  // xSecVariables_ in analyzeHypothesisKinFit.C
  std::vector<TString> xSecVariables_;
  TString xSecVariables[] ={"topPt", "topY", "ttbarPt", "ttbarMass", "ttbarY", "lepPt", "lepEta", "bqPt", "bqEta", "topPtNorm", "topYNorm", "ttbarPtNorm", "ttbarMassNorm", "ttbarYNorm", "lepPtNorm", "lepEtaNorm", "bqPtNorm", "bqEtaNorm", "inclusive"};
  xSecVariables_.insert( xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString) );
  // chose min/max value[%] for relative uncertainty plots
  double errMax=40.0;
  double errMin= 0.0;
  // create plot container
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, std::map <unsigned int, TH1F*> > relativeUncertainties_;
  std::map< TString, std::map <unsigned int, TH1F*> > relUncertDistributions_;  // 1st: type of uncertainty, 2nd: xSec variable, 3rd: uncertainty value  
  std::map< TString, std::vector<double> > binning_ = makeVariableBinning();
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
      if(xSecVariables_[i].Contains("top") || xSecVariables_[i].Contains("bq")){
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
  
  // ============================
  //  Bin Center Corrections
  // ============================
  std::map<TString, std::vector<double> > correctedCenters_;
  std::map<TString, std::vector<double> > corrCenterErrors_;

  if(useBCC){
    std::cout << " Loading and calculating bin center corrections .... " << std::endl;

    BCC b("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/"+TopFilename(kSig, 0, (std::string)decayChannel),"analyzeTop"+LV+"LevelKinematics"+PS,xSecVariableBranchNames_,mergeLepAndHadTop);

    b.runBCCCalculation();
    correctedCenters_ = b.getMapWithCorrectedCentersInX();
    corrCenterErrors_ = b.getMapWithCenterErrorsInX();

    // Output of results

    if(verbose>1){
      for (std::map<TString, std::vector<double> >::iterator iter1 = correctedCenters_.begin(); iter1 != correctedCenters_.end(); iter1++ ){
	std::cout << iter1->first << ": ";
	for (std::vector<double>::iterator iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++)	std::cout << (*iter2) << " ";
	std::cout << std::endl;
      }    
      for (std::map<TString, std::vector<double> >::iterator iter1 = corrCenterErrors_.begin(); iter1 != corrCenterErrors_.end(); iter1++ ){
	std::cout << iter1->first << ": ";
	for (std::vector<double>::iterator iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++) std::cout << (*iter2) << " ";
	std::cout << std::endl;
      }
    }

    std::cout << " .... Executing bin center corrections finished." << std::endl;
  }

  // ============================
  //  Open rootfile
  // ============================

  TFile* file = TFile::Open(outputFile, "UPDATE");
  if(verbose>1) std::cout << "opened file "+outputFile << std::endl;

  // check if file exist
  if(file&&!file->IsZombie()){
    if(verbose>0) std::cout << "target file found!" << std::endl;

    // =================================
    //  Load hadronization uncertainties
    // =================================
    // container for hadronization uncertainties
    std::map< TString, TH1F*> hadUnc_;
    // get file 
    TFile* hadfile=TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/ttbarNtupleCteq6mHadronUncert.root", "OPEN");
    if(!hadfile||hadfile->IsZombie()){
      std::cout << "corrupt or missing file " << "/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/ttbarNtupleCteq6mHadronUncert.root" << std::endl;
      exit(0);
    }
    // loop quantities 
    for(unsigned int var=0; var<xSecVariables_.size(); ++var){
      // exclude inclusive cross section
      // FIXME: exclude bquark quantities for the moment
      if(!xSecVariables_[var].Contains("inclusive")&&!xSecVariables_[var].Contains("bq")){
	TString name=xSecVariables_[var];       
	name.ReplaceAll("Norm","");
	// get plot 
	hadUnc_[xSecVariables_[var]]=(TH1F*)(hadfile->Get(name)->Clone());
	calculateError_[xSecVariables_[var]][sysHadUp  ]=true; 
	calculateError_[xSecVariables_[var]][sysHadDown]=true; 
      }
    }
    
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
	TGraphAsymmErrors* combinedErrors = new TGraphAsymmErrors(Nbins);
	// get plot without variation
	TH1F* noSysPlot=(TH1F*)histo_[xSecVariables_[i]][sysNo]->Clone();
	// loop bins
	for(int bin=1; bin<=noSysPlot->GetNbinsX(); ++bin){
	  double totalSystematicError = 0;
	  double stdBinXSecValue      = histo_[xSecVariables_[i]][sysNo]->GetBinContent(bin);
	  double binEdgeDown          = histo_[xSecVariables_[i]][sysNo]->GetBinLowEdge(bin);
	  double binEdgeUp            = histo_[xSecVariables_[i]][sysNo]->GetBinLowEdge(bin+1);
	  double MCpredBinVar         = (decayChannel=="combined") ? histo_[xSecVariables_[i]+"MC"][sysNo]->GetBinContent(bin) : -1.0;
	  // jump to bin without vanishing bin content
	  while(stdBinXSecValue==0&&bin<Nbins){
	    if(verbose>1) std::cout << "bin #" << bin << "/" << Nbins << " has bin content == 0, will be skipped!" << std::endl;
	    ++bin;
	    stdBinXSecValue=histo_[xSecVariables_[i]][sysNo]->GetBinContent(bin);
	    binEdgeDown          = histo_[xSecVariables_[i]][sysNo]->GetBinLowEdge(bin);
	    binEdgeUp            = histo_[xSecVariables_[i]][sysNo]->GetBinLowEdge(bin+1);
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
	      std::cout << std::endl << xSecVariables_[i] << " bin #" << bin << "/" << Nbins << std::endl;
	      std::cout << "( range " << binEdgeDown << " .. " << binEdgeUp << ")" << std::endl;
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
		if (exclShapeVar && label=="Shape"){
		  shapeVarIdx=nSysCnt;
		  label="("+label+")";		  
		}
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
		  if(sys==sysHadUp||sys==sysHadDown){
		    // placeholder for bquark quantities and inclusive xSec
		    if(xSecVariables_[i].Contains("bq")||xSecVariables_[i].Contains("inclusive")){
		      sysBinXSecValue=(1.+std::abs(constHadUncertainty))*stdBinXSecValue;
		    }
		    // otherwise from external studies
		    else{
		      double unc=hadUnc_[xSecVariables_[i]]->GetBinContent(bin);
		      sysBinXSecValue = (1.+std::abs(unc))*stdBinXSecValue;
		    }
		  }

		  sysDiff=std::abs(sysBinXSecValue-stdBinXSecValue);
		  if      (sys==sysTopMassUp)   sysDiff *= SF_TopMassUpUncertainty;   // SF_TopMassUpUncertainty: defined in basicFunctions.h
		  else if (sys==sysTopMassDown) sysDiff *= SF_TopMassDownUncertainty; // SF_TopMassDownUncertainty: defined in basicFunctions.h
		}
		else if(verbose>1) std::cout << "(not considered): ";
		// print single systematic uncertainty absolut and relative for bin & variable
		if(verbose>1) std::cout << sysDiff << " ( = " << 100*sysDiff/stdBinXSecValue << "% )" << std::endl;
		// save relative systematic uncertainties for bin & variable (weight 0.5 due to error symmetrization)
		relSysPlot->Fill(nSysCnt, 100.0*0.5*sysDiff/stdBinXSecValue);
	      }
	      // for last systematic 
	      if(sys==ENDOFSYSENUM-1){
		// calculate total systematic uncertainty
		for (unsigned int n=0; n<nSysTypes-1; n++) // -1 due to conversion between loop index and bin number
		  if (exclShapeVar && n==shapeVarIdx) std::cout << "Shape uncertainties are excluded from total systematic uncertainty" << std::endl;
		  else totalSystematicError += pow(stdBinXSecValue*relSysPlot->GetBinContent(n+1)/100.0,2);
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
		  std::cout << "total statistic uncertainty:  " << " +/- " << statErrorBinVar      << " (" << 100*statErrorBinVar/stdBinXSecValue      << "%)" << std::endl;
		  std::cout << "total systematic uncertainty: " << " +/- " << totalSystematicError << " (" << 100*totalSystematicError/stdBinXSecValue << "%)" << std::endl;
		  std::cout << "total uncertainty:            " << " +/- " << combinedErrorBinVar  << " (" << 100*combinedErrorBinVar/stdBinXSecValue  << "%)" << std::endl;
		}
		// print MC prediction value and difference in std variations
		double xSecDiff=stdBinXSecValue-MCpredBinVar;
		double absError=combinedErrorBinVar;
		double relativeDifference=xSecDiff/absError; 
		if(verbose>0){
		  std::cout << "difference data-MC = " << xSecDiff << " pb" << std::endl;
		  std::cout << " (" << (xSecDiff/stdBinXSecValue)*100 << "%)" << std::endl;
		  std::cout << " (" << relativeDifference << " std variations)" << std::endl;
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
		if(useBCC&&decayChannel=="combined"&&xSecVariables_[i]!="inclusive"){
		  TString plotName=xSecVariables_[i];
		  plotName.ReplaceAll("Norm","");
		  if(verbose>1){ 
		    std::cout << "try to access BCC result map for " << plotName << " (bin " << bin << ")" << std::endl;
		    for(std::map<TString, std::vector<double> >::const_iterator val=correctedCenters_.begin(); val!=correctedCenters_.end(); ++val){
		      std::cout << "found entry " << val->first << " (size " << val->second.size() << ", ";
		      std::cout << "center (bin " << bin << ") " << ((int)val->second.size() >= bin ? val->second.at(bin-1) : -1.) << ")" << std::endl;
		    }
		  }
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
    // Create plot to show distribution of uncertainties per xSec variable

    for(unsigned int i=0; i<xSecVariables_.size(); ++i){

      std::map<TString, std::map<unsigned int, TH1F*> >::const_iterator outerIter = relativeUncertainties_.find(xSecVariables_[i]);

      if (outerIter == relativeUncertainties_.end()){
	std::cout << "Variable '" << xSecVariables_[i] << "' not found to build uncertainty distributions." << std::endl;
      }
      else{
	std::cout << "Building uncertainty distributions for '" << xSecVariables_[i] << "'." << std::endl;

	TString plotNameForBinning = xSecVariables_[i];
	plotNameForBinning.ReplaceAll("Norm","");
	// int NBINS = histo_[xSecVariables_[i]][sysNo]->GetNbinsX();
	int NBINS = binning_[plotNameForBinning].size()-1;

	std::map<unsigned int, TH1F*>::const_iterator innerIter = outerIter->second.begin();
	int NSYSTYPES = innerIter->second->GetNbinsX() - 3;

	for (int binUnc=0; binUnc<NSYSTYPES; ++binUnc){

	  TCanvas *canvasUncertaintyDistributions = new TCanvas("canvasUncertaintyDistributions","canvasUncertaintyDistributions",800,600);

	  TString label = sysLabel(2*binUnc);
	  
	  if (calculateError_[xSecVariables_[i]][2*binUnc] && label != "sysNo"){

	    TH1F* tempResult = new TH1F(xSecVariables_[i]+"_"+label,xSecVariables_[i]+"_"+label,NBINS,0.5,NBINS+0.5);
	    tempResult->GetXaxis()->SetTitle("Bin Number ("+xSecVariables_[i]+")");
	    tempResult->GetYaxis()->SetTitle(label.ReplaceAll("Down","")+" Relative Uncertainty [%]"); 
	    tempResult->SetFillColor(38);
	    tempResult->SetNdivisions(10,"X");

	    int binCounter = 1;

	    for (std::map<unsigned int, TH1F*>::const_iterator histoIter = outerIter->second.begin(); histoIter != outerIter->second.end();){
	      
	      // jump over leading empty bins
	      
	      if (histo_[xSecVariables_[i]][sysNo]->GetBinContent(binCounter) == 0)
		binCounter++;
		
	      else
	      {
		double value = histoIter->second->GetBinContent(binUnc); 
		tempResult->Fill(binCounter,value);
		
		binCounter++;
		histoIter++;
	      }

	      if (binCounter>NBINS) break;  // to avoid endless loop for empty histogrammes
	    }    

	    tempResult->SetMaximum(((int)(tempResult->GetMaximum()/5)+1)*5);

	    relUncertDistributions_[xSecVariables_[i]][binUnc] = (TH1F*)tempResult->Clone();
	    canvasUncertaintyDistributions->cd();
	    tempResult->Draw();

	    int initialIgnoreLevel=gErrorIgnoreLevel;
	    if(verbose==0) gErrorIgnoreLevel=kWarning;
	    // a) save to rootFile
	    //if(save) saveToRootFile(outputFile, canvasUncertaintyDistributions, true, verbose, "uncertaintyDistributions");
	    // b) save as eps and png
	    if(save){
		TString saveName=outputFolder+"/uncertaintyDistributions/relativeUncertainties"+xSecVariables_[i]+"_"+label;
		if(decayChannel=="combined") saveName+="Combined";
		saveName+=universalplotLabel;
		canvasUncertaintyDistributions->Print(saveName+".eps");
		canvasUncertaintyDistributions->Print(saveName+".png");
	    }
	    gErrorIgnoreLevel=initialIgnoreLevel;
	  
	    delete tempResult; tempResult = NULL;
	  }	  
	  delete canvasUncertaintyDistributions; canvasUncertaintyDistributions=NULL;
	}
      }
    }
  
    // close file
    // needed to be able to use the saveToRootFile function, which also opens the file
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
	      // draw plot into canvas (transparent) for having axis AND grid
	      relativeUncertainties_[xSecVariables_[i]][bin]->SetFillColor(10);
	      relativeUncertainties_[xSecVariables_[i]][bin]->SetLineColor(10);
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
	      int colourCounter =    1;
	      int fillStyle     = 1001;
	      unsigned int colour=kBlack;
	      for(int sys=1; sys<=relativeUncertainties_[xSecVariables_[i]][bin]->GetNbinsX(); ++sys, ++colourCounter){
		colour = (colourCounter%2==0) ? kYellow-7 : 8;
		if (exclShapeVar && (unsigned int)sys==shapeVarIdx){
		  colour=kGray;
		  fillStyle=3002;
		}
		else{
		  colour = (colourCounter%2==0) ? kYellow-7 : 8;
		  fillStyle = 1001;
		}	   
		relUnCertaintyCopy->Reset("ICEMS");
		relUnCertaintyCopy->SetBinContent(sys, relativeUncertainties_[xSecVariables_[i]][bin]->GetBinContent(sys));
		relUnCertaintyCopy->SetFillStyle(fillStyle);
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
		saveName+=universalplotLabel;
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
		  // exclude over/underflow bins with empty bin content or zero width 
		  if(dataStat->GetBinWidth(bin)!=0&&dataStat->GetBinContent(bin)!=0){
		    if(useBCC && verbose>1){ 
		      std::cout << "try to access BCC result map for " << plotName << " (bin " << bin << ")" << std::endl;
		      for(std::map<TString, std::vector<double> >::const_iterator val=correctedCenters_.begin(); val!=correctedCenters_.end(); ++val){
			std::cout << "found entry " << val->first << " (size " << val->second.size() << ", ";
			std::cout << "center (bin " << bin << ") " << ((int)val->second.size() >= bin ? val->second.at(bin-1) : -1.) << ")" << std::endl;
		      }
		    }
		    double pointXValue = useBCC ? correctedCenters_[plotName].at(bin-1): histo_[xSecVariables_[i]][sysNo]->GetBinCenter(bin);
		    double pointXError = useBCC ? corrCenterErrors_[plotName].at(bin-1): 0;
		    double pointYError = dataStat->GetBinError(bin);
		    statErrors->SetPoint(bin, pointXValue, dataStat->GetBinContent(bin));
		    statErrors->SetPoint(0, 0, -1000);
		    pointXError=0;
		    statErrors->SetPointError(bin, pointXError, pointXError, pointYError, pointYError);
		  }
		}
		whipEmptyBinsAway(statErrors, verbose);
		// print new object
		statErrors->SetMarkerSize(0.01);
		statErrors->Draw("e p same");
		// delete (old) TH1F plot from canvas
		canvas->GetListOfPrimitives()->Remove(canvas->GetPrimitive(plotName+"kData"));
	      }
	      // Draw errors into Canvas
	      totalErrors_[xSecVariables_[i]]->Draw("p Z same");
	      canvas->SetName(xSecVariables_[i]);
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
	      saveName+=universalplotLabel;
	      canvas->Print(saveName+".eps");
	      canvas->Print(saveName+".png");
	    }
	    gErrorIgnoreLevel=initialIgnoreLevel;
	    //delete statErrors;
	  }
	}
      }
    }
    // close file
    hadfile->Close();
  }
  else std::cout << std::endl << "ERROR:target file does not exist or is broken!" << std::endl;

  // close file
  file->Close();
}
