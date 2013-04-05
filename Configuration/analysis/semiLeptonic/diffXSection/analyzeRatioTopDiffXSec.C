#include "basicFunctions.h"

// Enumerator to assign an unique integer value to each systematic variation (includes 7 and 8 TeV) systematics
enum systematicVariation78 { /* 0:*/ sysNo78,
			     /* 1:*/ sysLumiUp78,                  /* 2:*/ sysLumiDown78,                
			     /* 3:*/ sysPUUp78,                    /* 4:*/ sysPUDown78,                  
			     /* 5:*/ sysJESUp78,                   /* 6:*/ sysJESDown78,                 
			     /* 7:*/ sysJERUp78,                   /* 8:*/ sysJERDown78,                 
			     /* 9:*/ sysLepEffSFNormUp78,          /*10:*/ sysLepEffSFNormDown78,        
			     /*11:*/ sysLepEffSFShapeUpEta78,      /*12:*/ sysLepEffSFShapeDownEta78,
			     /*13:*/ sysLepEffSFShapeUpPt78,       /*14:*/ sysLepEffSFShapeDownPt78,  
			     /*15:*/ sysTriggerEffSFJetNormUp78,   /*16:*/ sysTriggerEffSFJetNormDown78,
			     /*17:*/ sysTriggerEffSFJetShapeUp78,  /*18:*/ sysTriggerEffSFJetShapeDown78,    
			     /*19:*/ sysBtagSFUp78,                /*20:*/ sysBtagSFDown78, 
			     /*21:*/ sysBtagSFShapeUpPt6578,       /*22:*/ sysBtagSFShapeDownPt6578,
			     /*23:*/ sysBtagSFShapeUpEta0p778,     /*24:*/ sysBtagSFShapeDownEta0p778,
			     /*25:*/ sysMisTagSFUp78,              /*26:*/ sysMisTagSFDown78,
			     /*27:*/ sysTopScaleUp78,              /*28:*/ sysTopScaleDown78,            
			     /*29:*/ sysVBosonScaleUp78,           /*30:*/ sysVBosonScaleDown78,          
			     /*31:*/ sysSingleTopScaleUp78,        /*32:*/ sysSingleTopScaleDown78,     
			     /*33:*/ sysTopMatchUp78,              /*34:*/ sysTopMatchDown78,            
			     /*35:*/ sysVBosonMatchUp78,           /*36:*/ sysVBosonMatchDown78,         
			     /*37:*/ sysTopMassUp78,               /*38:*/ sysTopMassDown78,            
			     /*39:*/ sysQCDUp78,                   /*40:*/ sysQCDDown78,                 
			     /*41:*/ sysSTopUp78,                  /*42:*/ sysSTopDown78,               
			     /*43:*/ sysDiBosUp78,                 /*44:*/ sysDiBosDown78,              
			     /*45:*/ sysPDFUp78,                   /*46:*/ sysPDFDown78,
			     /*47:*/ sysHadUp78,                   /*48:*/ sysHadDown78,
			     /*49:*/ sysGenMCatNLO78,              /*50:*/ sysGenPowheg78,
			     /*51:*/ ENDOFSYSENUM78,               };


TH1F* getPlot(TFile* file, TString canvName, TString plotName);
TString sysLabel78(unsigned int sys);
TGraphAsymmErrors *convertToAsym(TH1F* input);

void analyzeRatioTopDiffXSec(bool save=true, unsigned int verbose=1, TString inputFolderName7="tmp/2011/",
			     TString inputFolderName8="tmp/2012/",
			     bool extrapolate=false){
  // ==================================
  //  Set Root Style and Configuration
  // ==================================
  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  myStyle.cd();
  TGaxis::SetMaxDigits(2);
  gROOT->SetStyle("HHStyle");
  // run automatically in batch mode
  //gROOT->SetBatch();
  gStyle->SetEndErrorSize(8);
  myStyle.SetEndErrorSize(8);

  // ============================
  //  List Relevant Variables
  // ============================
  std::vector<TString> xSecVariables_;
  // a) top and ttbar quantities
  if(extrapolate) xSecVariables_.insert(xSecVariables_.end(), xSecVariablesKinFitNorm    , xSecVariablesKinFitNorm     + sizeof(xSecVariablesKinFitNorm)    /sizeof(TString));
  // b) lepton and b-jet quantities
  else            xSecVariables_.insert(xSecVariables_.end(), xSecVariablesFinalStateNorm, xSecVariablesFinalStateNorm + sizeof(xSecVariablesFinalStateNorm)/sizeof(TString));
  // exclude variables which are not present in 7 and 8 TeV
  for(int i=0; i<int(xSecVariables_.size()); ++i){
    if(verbose>1) std::cout << i << ": " << xSecVariables_[i] << std::endl; 
    if(xSecVariables_.at(i).Contains("bbbar")){ 
      xSecVariables_.erase(xSecVariables_.begin()+i); // delete entry
      i-=1; // the next entries are shifted backwards by 1
      if(verbose>2) std::cout << "erasing" << std::endl;}
  }
  
  // printout
  if(verbose>0){
    std::cout << "PS: extrapolate? "<< extrapolate << std::endl;
    std::cout << "considered vaiables: " << std::endl;
    for(int i=0; i<int(xSecVariables_.size()); ++i){ std::cout << " " << xSecVariables_[i] << std::endl; }
  }

  // ===========================================
  //  List of Systematics that should be ignored 
  // ===========================================  
  // for 8TeV only
  std::vector<TString> ignoreFor8_;
  ignoreFor8_.push_back(sysLabel78(sysTriggerEffSFJetNormUp78   ));
  ignoreFor8_.push_back(sysLabel78(sysTriggerEffSFJetNormDown78 ));
  ignoreFor8_.push_back(sysLabel78(sysTriggerEffSFJetShapeUp78  ));
  ignoreFor8_.push_back(sysLabel78(sysTriggerEffSFJetShapeDown78));
  // for 7 TeV only
  std::vector<TString> ignoreFor7_;
  // for the final error
  std::vector<TString> ignoreCompletely_;
  ignoreCompletely_.push_back(sysLabel78(sysGenMCatNLO78));
  ignoreCompletely_.push_back(sysLabel78(sysGenPowheg78));

  // ============================
  //  Open Rootfiles
  // ============================
  // names
  TString outPath="diffXSecFromSignal/plots/combined/2012/xSecRatio/";
  TString inPath="/afs/naf.desy.de/group/cms/scratch/tophh/";  
  TString name7= (extrapolate) ? "diffXSecTopSemiLepParton.root" : "diffXSecTopSemiLepHadronPhaseSpace.root";
  TString name8= (extrapolate) ? "diffXSecTopSemiLepParton.root" : "diffXSecTopSemiLepHadronPhaseSpace.root";
  // info
  if(verbose>0){
    std::cout << "get 7 TeV results from " << inPath+inputFolderName7+name7 << std::endl;
    std::cout << "get 8 TeV results from " << inPath+inputFolderName8+name8 << std::endl;
  }
  // files
  TFile* file8 = new TFile(inPath+inputFolderName8+name8, "OPEN");
  TFile* file7 = new TFile(inPath+inputFolderName7+name7, "OPEN");
  // check
  if(!file7||file7->IsZombie()){ std::cout << " " << inPath+inputFolderName7+name7 << std::endl; exit(0); }
  if(!file8||file8->IsZombie()){ std::cout << " " << inPath+inputFolderName8+name8 << std::endl; exit(0); }


  // ============================
  //  Loop plots
  // ============================
  // store ratios and canvas
  std::vector<TCanvas*> plotCanvas_;
  std::map<TString,TH1F*> ratioDataSys_;
  // loop
  for(int i=0; i<int(xSecVariables_.size()); ++i){
    // info
    if(verbose>0) std::cout << std::endl << "processing variable " << " \033[1;31m " << xSecVariables_[i] << " \033[0m\ " << std::endl;

    // ============================
    //  Loop systematics
    // ============================
    for(int systematics=sysNo78; systematics<ENDOFSYSENUM78; ++systematics){

      // ============================
      //  Get Histos
      // ============================
      // systematic names
      TString sys=sysLabel78(systematics);
      TString sys7=sys;
      TString sys8=sys;
      // take care of uncertainties that are unique in one analysis
      for(int j=0; j<int(ignoreFor7_.size()); ++j){
	if(ignoreFor7_[j]==sys7) sys7="sysNo";
      }
      for(int j=0; j<int(ignoreFor8_.size()); ++j){
	if(ignoreFor8_[j]==sys8) sys8="sysNo";
      }
      // take care of hadronization uncertainty
      // which is MC@NLO vs POWHEG and has no own xSec results (folder)
      if(systematics==sysHadUp78||systematics==sysHadDown78){
	sys7="sysNo";
	sys8="sysNo";
      }
      // paths and names
      TString canvpath7="xSec/"+sys7+"/"+xSecVariables_[i];
      TString canvpath8="xSec/"+sys8+"/"+xSecVariables_[i];
      TString plotName =xSecVariables_[i];
      plotName.ReplaceAll("Norm","");
      if(verbose>2||sys=="sysNo") std::cout << "canvas for " << sys << " (7;8): " << canvpath7 << " ; " << canvpath8 << std::endl;
      // data
      TString plotNameData=plotName+"kData";
      if(verbose>2) std::cout << "data: " << plotNameData << std::endl;
      TH1F* data7 = getPlot(file7,canvpath7,plotNameData);
      TH1F* data8 = getPlot(file8,canvpath8,plotNameData);
      // MadGraph
      TString plotNameMad=plotName;
      if(verbose>2) std::cout << "MadGraph: " << plotNameMad << std::endl;
      TH1F* mad7 = (sys=="sysNo") ? getPlot(file7,canvpath7,plotNameMad) : 0;
      TH1F* mad8 = (sys=="sysNo") ? getPlot(file8,canvpath8,plotNameMad) : 0;
      // MC@NLO
      TString plotNameMca=plotName+"MC@NLO";
      if(verbose>2) std::cout << "MC@NLO: " << plotNameMca << std::endl;
      TH1F* mca7 = (sys=="sysNo") ? getPlot(file7,canvpath7,plotNameMca) : 0;
      TH1F* mca8 = (sys=="sysNo") ? getPlot(file8,canvpath8,plotNameMca) : 0;
      // POWHEG
      TString plotNamePow=plotName+"POWHEG";
      if(verbose>2) std::cout << "POWHEG: " << plotNamePow << std::endl;
      TH1F* pow7 = (sys=="sysNo") ? getPlot(file7,canvpath7,plotNamePow) : 0;
      TH1F* pow8 = (sys=="sysNo") ? getPlot(file8,canvpath8,plotNamePow) : 0;
      // approx. NNLO
      TString plotNameNNLO=plotName+"nnlo";
      if((xSecVariables_[i].Contains("topPt")||xSecVariables_[i].Contains("topY"))&&verbose>2) std::cout << "approx NNLO: " << plotNameNNLO << std::endl;
      TH1F* nnlo7 = (sys=="sysNo"&&(xSecVariables_[i].Contains("topPt")||xSecVariables_[i].Contains("topY"))) ? getPlot(file7,canvpath7,plotNameNNLO) : 0;
      TH1F* nnlo8 = (sys=="sysNo"&&(xSecVariables_[i].Contains("topPt")||xSecVariables_[i].Contains("topY"))) ? getPlot(file8,canvpath8,plotNameNNLO) : 0;
   
      // ============================
      // Build ratios: 8/7 TeV
      // ============================
      // data
      TH1F* ratioData=data8 ? (TH1F*)(data8->Clone()) : 0;
      if(data7&&data8) ratioData->Divide(data7);
      ratioDataSys_[sys]=(TH1F*)(ratioData->Clone());
      // debug info: value from 7 and 8 TeV plot in 1st bin and their ratio
      if(verbose>3){
	std::cout << "7: " << data7->GetBinContent(1) << std::endl;
	std::cout << "8: " << data8->GetBinContent(1) << std::endl;
	std::cout << "ratio: " << data8->GetBinContent(1)/data7->GetBinContent(1) << std::endl;
      }
      // MadGraph
      TH1F* ratioMad =mad8  ? (TH1F*)(mad8 ->Clone()) : 0;
      if(mad7&&mad8  ) ratioMad ->Divide(mad7 );
      // MC@NLO
      TH1F* ratioMca =mca8  ? (TH1F*)(mca8 ->Clone()) : 0;
      if(mca7&&mca8  ) ratioMca ->Divide(mca7 );
      // POWHEG
      TH1F* ratioPow =pow8  ? (TH1F*)(pow8 ->Clone()) : 0;
      if(pow7&&pow8  ) ratioPow ->Divide(pow7 );
      // approx. NNLO
      TH1F* ratioNNLO=nnlo8 ? (TH1F*)(nnlo8->Clone()) : 0;
      if(nnlo7&&nnlo8) ratioNNLO->Divide(nnlo7);    
      // save data plots
      if(save) saveToRootFile("8over7TeVRatios.root", ratioData, true, verbose-1, sysLabel78(systematics));
      // drawing only for central values
      if(systematics==sysNo78){ 
	if(!ratioData||(!ratioMad&&!ratioMca&&!ratioPow&&!ratioNNLO)){
	  std::cout << "ERROR: no central prediction for data or all theorie ratios could be determined!" << std::endl;
	  exit(0);
	}
	if(verbose>0) std::cout << "drawing central ratios into canvas" << std::endl;
	// ====================================
	// Drawing Central Curves into Canvas
	// ====================================
	TString plotname=xSecVariables_[i];
	plotname.ReplaceAll("Norm","");
	// create canvas
	addCanvas(plotCanvas_);
	plotCanvas_[plotCanvas_.size()-1]->cd(0);
	plotCanvas_[plotCanvas_.size()-1]->SetTitle(plotname+"NormRatio78TeV");
	plotCanvas_[plotCanvas_.size()-1]->SetLeftMargin(plotCanvas_[plotCanvas_.size()-1]->GetLeftMargin()+0.015);
	// configure axis
	setXAxisRange(ratioData,plotname);
	double xmin=0.6;
	double xmax=1.6;
	ratioData->GetYaxis()->SetRangeUser(xmin,xmax);
	ratioData->GetXaxis()->SetTitle(xSecLabelName(plotname));
	ratioData->GetXaxis()->SetNoExponent(true);
	ratioData->GetYaxis()->SetNoExponent(true);
	TString ylabel="#left(#frac{1}{#sigma} #frac{d#sigma}{d"+xSecLabelName(plotname, true)+"}#right)_{#sqrt{s} = 8 TeV}";
	ylabel+="   #lower[0.4]{#scale[2.0]{/}}   #left(#frac{1}{#sigma} #frac{d#sigma}{d"+xSecLabelName(plotname, true)+"}#right)_{#sqrt{s} = 7 TeV}";
	ratioData->GetYaxis()->SetTitle(ylabel);
	ratioData->GetYaxis()->SetTitleOffset(1.9);
	// draw axis
	ratioData->Draw("AXIS");
	// configure style
	ratioData->SetLineWidth(6.5);
	// draw theory curves
	if(ratioMad ) DrawSteps(ratioMad ,"hist same");
	if(ratioMca ) DrawSteps(ratioMca ,"hist same");
	if(ratioPow ) DrawSteps(ratioPow ,"hist same");
	if(ratioNNLO) DrawSteps(ratioNNLO,"hist same");
	// draw data points with statistical errors
	if(ratioData) ratioData->Draw("e p X0 same");
	// draw cms label
	TPaveText *label = new TPaveText();
	label -> SetX1NDC(gStyle->GetPadLeftMargin());
	label -> SetY1NDC(1.0-gStyle->GetPadTopMargin());
	label -> SetX2NDC(1.0-gStyle->GetPadRightMargin());
	label -> SetY2NDC(1.0);
	label -> SetTextFont(42);
	label -> AddText("CMS Preliminary, 5/12 fb^{-1} at #sqrt{s} = 7/8 TeV");
	label->SetFillStyle(0);
	label->SetBorderSize(0);
	label->SetTextSize(0.04);
	label->SetTextAlign(32);
	label-> Draw("same");
	// draw x grid for binning
	for(int bin=2; bin<=ratioData->GetNbinsX(); ++bin){
	  double xBorder=ratioData->GetBinLowEdge(bin);
	  drawLine(xBorder, ratioData->GetMinimum(), xBorder, ratioData->GetMaximum(), kBlack, 1, 3);
	}
	// draw y grid in 0.1 steps
	for( double k=0; k<=(ratioData->GetMaximum()-ratioData->GetMinimum())/0.1; ++k){
	  double yline=ratioData->GetMinimum()+k*0.1;
	  drawLine(ratioData->GetXaxis()->GetXmin(), yline, ratioData->GetXaxis()->GetXmax(), yline, kBlack, 1, 3);
	}

        // ============================
        // Draw Legend
        // ============================
	TLegend *leg = new TLegend();
	leg->SetX1NDC(0.22);
	leg->SetY1NDC(0.66);
	leg->SetX2NDC(0.6);
	leg->SetY2NDC(0.88);
	legendStyle(*leg,"",0.04);
	leg->AddEntry(ratioDataSys_[sys], "data"    , "LP");
	if(ratioMad ) leg->AddEntry(ratioMad , "MadGraph"  , "L");
	if(ratioPow ) leg->AddEntry(ratioPow , "Powheg  "  , "L");
	if(ratioMca ) leg->AddEntry(ratioMca , "MC@NLO  "  , "L");
	if(ratioNNLO) leg->AddEntry(ratioNNLO,"approx.NNLO", "L");
	leg->Draw("same");


      } // end if sysNo
  
      // ===================================
      // Combination of systematic errors
      // ===================================
      // done for last systematics
      else if (systematics==ENDOFSYSENUM78-1){
	// info: processing status
	if(verbose>0) std::cout << "calculate systematics for ratio" << std::endl; 
	// central ratio plot
	TH1F* ratioSysNo=ratioDataSys_["sysNo"];
	// ratio plot inclusing systematics
	ratioDataSys_["allUnc"]=(TH1F*)(ratioSysNo->Clone());
	// loop bins
	for(int bin=1; bin<=ratioSysNo->GetNbinsX(); ++bin){
	  // info: actual bin
	  if(verbose>0) std::cout << std::endl << " bin " << bin << " [" << ratioSysNo->GetBinLowEdge(bin) << ".." << ratioSysNo->GetBinLowEdge(bin+1) << "]: " << std::endl;
	  double sysUncCombSquared=0;
	  // central ratio value
	  double stdBinValue  =ratioSysNo->GetBinContent(bin);
	  // loop systematics
	  for(int subSys=sysNo78+1; subSys<ENDOFSYSENUM78; ++subSys){
	    bool harmonize=false;
	    TString sysNow=sysLabel78(subSys);
	    // load uncertainty varied values for this bin and subuncertainty
	    double sysBinValueUp=ratioDataSys_[sysNow]->GetBinContent(bin);
	    double sysBinValueDn=sysBinValueUp;
	    // take care of hadronization uncertainty
	    // which is MC@NLO vs POWHEG and has no own xSec results (folder)
	    if(systematics==sysHadUp78||systematics==sysHadDown78){
	      stdBinValue  =ratioDataSys_[sysLabel78(sysGenMCatNLO78)]->GetBinContent(bin);
	      sysBinValueUp=ratioDataSys_[sysLabel78(sysGenPowheg78 )]->GetBinContent(bin);
	      sysBinValueDn=sysBinValueUp;
	      sysNow=sysNow.ReplaceAll("Up","");
	    }	    
	    // check if dealing with Up/Dn uncertainty that needs to be harmonized
	    else if(sysNow.Contains("Up")&&sysLabel78(subSys+1).Contains("Down")&&(sysLabel78(subSys).ReplaceAll("Up","")==sysLabel78(subSys+1).ReplaceAll("Down",""))){
	      sysNow=sysNow.ReplaceAll("Up","");
	      sysBinValueDn=ratioDataSys_[sysLabel78(subSys+1)]->GetBinContent(bin);
	      harmonize=true;
	    }
	    // calculate uncertainty
	    double diff=0.5*(std::abs(sysBinValueUp-stdBinValue)+std::abs(sysBinValueDn-stdBinValue));
	    double diffRel=diff/stdBinValue;
	    // check if uncertainty should be considered 
	    bool consider=true;
	    for(int ign=0; ign<int(ignoreCompletely_.size()); ++ign){
	      if(sysLabel78(subSys)==ignoreCompletely_[ign]) consider=false;
	    } // end for ignore systematic 
	    // add subuncertainty
	    if(consider) sysUncCombSquared+=diff*diff;
	    // info: print uncertainty for subsystematic
	    if(verbose>1){
	      std::cout << "  " << sysNow << ": ";
	      if(harmonize) std::cout << " (0.5*[|" << sysBinValueUp << "-" << stdBinValue << "|+|" << sysBinValueDn << "-" << stdBinValue << "|])" << std::endl; 
	      else std::cout << " (" << sysBinValueUp << "-" << stdBinValue << ")" << std::endl; 
	      std::cout << "     -> " << diffRel*100 << "%";
	      if(!consider) std::cout << " (IGNORED)";
	      std::cout << std::endl;
	    } // if verbose
	    // skip next uncertainty if it was already considered in harmonization process
	    if(harmonize) subSys++;
	  } // end loop sub systematics for error combination
	  // info: print uncertainty for subsystematic
	  double sysUncComb=sqrt(sysUncCombSquared);
	  double statUnc   =ratioSysNo->GetBinError(bin);
	  double uncComb=sqrt(sysUncCombSquared+statUnc*statUnc);
	  if(verbose>0){
	    std::cout << "  --> 8/7TeV: " << stdBinValue << std::endl;
	    std::cout << "      +/- " << statUnc    << " ("<< statUnc/stdBinValue*100    << "% stat.)" << std::endl;
	    std::cout << "      +/- " << sysUncComb << " ("<< sysUncComb/stdBinValue*100 << "% sys. )" << std::endl;
	    std::cout << "      +/- " << uncComb    << " ("<< uncComb/stdBinValue*100    << "% tot. )" << std::endl;
	  } // if verbose	  
	  // add combined error of this bin to the stat+sys data histo	  
	  ratioDataSys_["allUnc"]->SetBinError(bin, uncComb);
	} // end loop bins for error combination

        // ============================
        // Draw combined error
        // ============================
	if(ratioDataSys_.count("allUnc")>0){
	  // info: processing status
	  if(verbose>0) std::cout << "draw data stat+sys ratio" << std::endl; 
	  // plot data stat+sys into same canvas
	  plotCanvas_[plotCanvas_.size()-1]->cd(0);
	  ratioDataSys_["allUnc"]->Draw("][ p z x0 same");
	}

	// ============================
	//  Saving
	// ============================
	if(save){
	  // info
	  if(verbose>0) std::cout << "saving will be done" << std::endl; 
	  // as eps
	  plotCanvas_[plotCanvas_.size()-1]->Print(outPath+(TString)(plotCanvas_[plotCanvas_.size()-1]->GetTitle())+".eps");
	  // in rootfile
	  TString ratiofolder = extrapolate ? "fullPS" : "visiblePS";
	  saveToRootFile("8over7TeVRatios.root", plotCanvas_[plotCanvas_.size()-1], true, verbose-1, ratiofolder);
	} // end if save
      } // end last systematic
    } // end loop systematics 
  } // end loop plots
}


TH1F* getPlot(TFile* file, TString canvName, TString plotName){
  gStyle->SetEndErrorSize(8);
  // check file
  if(!file||file->IsZombie()){ 
    std::cout << "ERROR in function getPlot: file " << file->GetName();
    std::cout << " does not exist" << std::endl; 
    return 0;
  }
  // get canvas
  TCanvas* canvas = (TCanvas*)(file->Get(canvName)->Clone());
  if(!canvas){
    std::cout << "ERROR in function getPlot: plot " << plotName;
    std::cout << " does not exist in file " << file->GetName() << std::endl;
    return 0;
  }
  // get plot
  TH1F* result=(TH1F*)canvas->GetPrimitive(plotName);
  // check if plot exists
  if(!result){
    std::cout << "ERROR in function getPlot: plot " << plotName;
    std::cout << " does not exist in file " << file->GetName() << std::endl;
    return 0;
  }
  gROOT->cd();
  // return plot
  return result;
}

TString sysLabel78(unsigned int sys)
{
  gStyle->SetEndErrorSize(8);
  // this function returns a TString that corresponds
  // to the systematic variation "sys" of the enumerator "systematicVariation"
  // modified quantities: none
  // used functions: none
  // used enumerators: none (label correspond to systematicVariation)

  switch (sys)
    {
    case sysNo78                       : return "sysNo";
    case sysLumiUp78                   : return "sysLumiUp";
    case sysLumiDown78                 : return "sysLumiDown";                
    case sysPUUp78                     : return "sysPUUp";                  
    case sysPUDown78                   : return "sysPUDown";                  
    case sysJESUp78                    : return "sysJESUp";
    case sysJESDown78                  : return "sysJESDown";
    case sysJERUp78                    : return "sysJERUp";                 
    case sysJERDown78                  : return "sysJERDown";                
    case sysLepEffSFNormUp78           : return "sysLepEffSFNormUp";
    case sysLepEffSFNormDown78         : return "sysLepEffSFNormDown";
    case sysLepEffSFShapeUpEta78       : return "sysLepEffSFShapeUpEta";
    case sysLepEffSFShapeDownEta78     : return "sysLepEffSFShapeDownEta";
    case sysLepEffSFShapeUpPt78        : return "sysLepEffSFShapeUpPt";
    case sysLepEffSFShapeDownPt78      : return "sysLepEffSFShapeDownPt"; 
    case sysTriggerEffSFJetNormUp78    : return "sysTriggerEffSFJetNormUp";
    case sysTriggerEffSFJetNormDown78  : return "sysTriggerEffSFJetNormDown";
    case sysTriggerEffSFJetShapeUp78   : return "sysTriggerEffSFJetShapeUp";
    case sysTriggerEffSFJetShapeDown78 : return "sysTriggerEffSFJetShapeDown"; 
    case sysBtagSFUp78                 : return "sysBtagSFUp";
    case sysBtagSFDown78               : return "sysBtagSFDown";
    case sysBtagSFShapeUpPt6578        : return "sysBtagSFShapeUpPt65";
    case sysBtagSFShapeDownPt6578      : return "sysBtagSFShapeDownPt65";
    case sysBtagSFShapeUpEta0p778      : return "sysBtagSFShapeUpEta0p7";
    case sysBtagSFShapeDownEta0p778    : return "sysBtagSFShapeDownEta0p7"; 
    case sysMisTagSFUp78               : return "sysMisTagSFUp";
    case sysMisTagSFDown78             : return "sysMisTagSFDown";
    case sysTopScaleUp78               : return "sysTopScaleUp";
    case sysTopScaleDown78             : return "sysTopScaleDown";
    case sysVBosonScaleUp78            : return "sysVBosonScaleUp";
    case sysVBosonScaleDown78          : return "sysVBosonScaleDown";
    case sysSingleTopScaleUp78         : return "sysSingleTopScaleUp";
    case sysSingleTopScaleDown78       : return "sysSingleTopScaleDown";
    case sysTopMatchUp78               : return "sysTopMatchUp";
    case sysTopMatchDown78             : return "sysTopMatchDown";            
    case sysVBosonMatchUp78            : return "sysVBosonMatchUp";          
    case sysVBosonMatchDown78          : return "sysVBosonMatchDown";
    case sysTopMassUp78                : return "sysTopMassUp";  
    case sysTopMassDown78              : return "sysTopMassDown";            
    case sysQCDUp78                    : return "sysQCDUp";           
    case sysQCDDown78                  : return "sysQCDDown";
    case sysSTopUp78                   : return "sysSTopUp";               
    case sysSTopDown78                 : return "sysSTopDown";
    case sysDiBosUp78                  : return "sysDiBosUp";              
    case sysDiBosDown78                : return "sysDiBosDown";
    case sysPDFUp78                    : return "sysPDFUp";              
    case sysPDFDown78                  : return "sysPDFDown";
    case sysHadUp78                    : return "sysHadronizationUp";
    case sysHadDown78                  : return "sysHadronizationDown";
    case sysGenMCatNLO78               : return "sysGenMCatNLO";
    case sysGenPowheg78                : return "sysGenPowheg";  
    default                          : std::cout << "ERROR: the chosen input for function sysLabel78 is not valid" << std::endl;
      std::cout << "chosen systematic variation:  " << sys            << std::endl;
      std::cout << "maximum systematic variation: " << ENDOFSYSENUM-1 << std::endl;
      return "";
    }
}

TGraphAsymmErrors *convertToAsym(TH1F* input){
  gStyle->SetEndErrorSize(8);
  // create tGraph
  double Nbins=input->GetNbinsX();
  TGraphAsymmErrors *output = new TGraphAsymmErrors(Nbins+1);
  // loop bins
  for(int bin=1; bin<=Nbins; ++bin){
    output->SetPoint     (bin, input->GetBinCenter(bin), input->GetBinContent(bin));
    double yerr=input->GetBinError(bin);
    //std::cout << yerr << std::endl;
    output->SetPointError(bin, 0., 0., yerr, yerr);
  }
  whipEmptyBinsAway(output);
  output->SetName("statData");
  //output->SetLineWidth(4);
  //output->SetLineColor(kRed);
  //output->SetMarkerColor(kRed);

  return output;
}
