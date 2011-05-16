#include "basicFunctions.h"

void analyzeTopDiffXSecMonitoring(double luminosity = 35.9, bool save = true, TString dataFile= "./diffXSecFromSignal/analysisRootFilesWithKinFit/muonDiffXSec2010Data36pbNov4ReRecoNov12Json.root")
{
  //  ---
  //     name conventions
  //  ---
  // a) enumerator sample convention (as defined in basicFunctions.h)
     /*0:*/  /*1:*/  /*2:*/    /*3:*/    /*4:*/   /*5:*/    /*6:*/  /*7:*/  /*8,  9,  10*/ /* 11   ,  12     ,   13:  */
  // kSig  , kBkg  , kZjets  , kWjets  , kQCD   , kSTop   , kDiBos, kData , kWW, kWZ, kZZ, kSTops  , kSTopt  , kSToptW 

  // b) file name convention (implemented in basicFunctions.h)
  // "muonDiffXSec"+sampleName+GeneratorName+GeneratorTune+MCProductionCycle+systematicVariation+"PF.root"
  // sampleName = "Sig", "Bkg", Wjets", "Zjets", "WW", "WZ", "ZZ", "VV", "SingleTopSchannel", 
  //              "SingleTopTchannel", "SingleTopTWchannel", "QCD"
  // GeneratorName= "Mad", "Pythia6"
  // GeneratorTune= "Z2", "D6T"
  // MCProductionCycle= "Fall10"

  //  ---
  //     options
  //  ---
  // a) options directly entered when calling function
  // save: save plots?
  // luminosity: [/pb]
  TString lumi = getTStringFromInt(roundToInt((luminosity), false));
  // b) options to be configured only once
  // get the .root files from the following folder:
  TString inputFolder = "./diffXSecFromSignal/analysisRootFilesWithKinFit";
  // save all plots into the following folder
  TString outputFolder = "./diffXSecFromSignal/plots/kinFit/";
  // save all plots within a root file named:
  TString outputFileName="diffXSecTopSemiMu.root";
  // choose name of the output .pdf file
  TString pdfName="differentialXSecMonitoring"+lumi+"pb";
  /* systematicVariation: which systematic shift do you want to make? from basicFunctions.h:
     0:sysNo              1:sysLumiUp          2:sysLumiDown          3:sysJESUp      
     4:sysJESDown         5:sysJERUp           6:sysJERDown           7:sysTopScaleUp 
     8:sysTopScaleDown    9:sysVBosonScaleUp  10:sysVBosonScaleDown  11:sysTopMatchUp 
     12:sysTopMatchDown  13:sysVBosonMatchUp  14:sysVBosonMatchDown  15:sysMuEffSFup  
     16:sysMuEffSFdown   17:sysISRFSRup       18:sysISRFSRdown       19:sysPileUp    
     20:sysQCDup         21:sysQCDdown
  */
  int systematicVariation=sysNo;
  // set detail level of output 
  // 0: no output, 1: std output 2: output for debugging
  unsigned int verbose=0;
  // c) set root style
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetEndErrorSize(8);
  gStyle->SetPalette(1);
  //  gStyle->SetErrorX(0); 

  //  ---
  //     choose plots
  //  ---
  // a) list plots you would like to see ("folder/plotName") - same as in .root files (for 1D and 2D)
  TString plots1D[ ] = { // before btagging
                         "tightJetQuality/btagTrkCntHighEff_"
			 // after btagging 
                       };
  TString plots2D[ ] = { 
                       };

  // b) list plot axes style
  // 1D: "x-axis title"/"y-axis title"/log/rebin-factor
  // log = 0 or 1 for linear or logarithmic axis 

  TString axisLabel1D[ ] = { // before btagging
                             "b-discr.(TCHE)/events/0/10"
			     // after btagging 
                           };
  // 2D: "x-axis title"/"y-axis title"
  TString axisLabel2D[ ] = {
                           };
  // count # plots
  unsigned int N1Dplots = sizeof(plots1D)/sizeof(TString);
  unsigned int N2Dplots = sizeof(plots2D)/sizeof(TString);
  // check if all axis labels exist
  if(N1Dplots != sizeof(axisLabel1D)/sizeof(TString)) std::cout << "ERROR: some 1D plots or axis label are missing" << std::endl;
  if(N2Dplots != sizeof(axisLabel2D)/sizeof(TString)) std::cout << "ERROR: some 2D plots or axis label are missing" << std::endl;
  if((N1Dplots != sizeof(axisLabel1D)/sizeof(TString))||(N2Dplots != sizeof(axisLabel2D)/sizeof(TString))) exit (1);

  // ---
  //    open our standard analysis files
  // ---
  std::map<unsigned int, TFile*> files_ = getStdTopAnalysisFiles(inputFolder, systematicVariation, dataFile);
  
  // ---
  //    loading histos
  // ---
  // collect all plot names in vector (first 1D, then 2D)
  std::vector<TString> plotList_;
  plotList_.insert( plotList_.begin(), plots1D, plots1D + sizeof(plots1D)/sizeof(TString) );
  plotList_.insert( plotList_.end()  , plots2D, plots2D + sizeof(plots2D)/sizeof(TString) );
  // container for all histos (1D&2D)
  // example for acess: histo_["plotName"][sampleNr]
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, std::map <unsigned int, TH2F*> > histo2_;
  // total # plots 
  int Nplots=0;
  // save all histos from plotList_ that exist in files_ into 
  // histo_ and histo2_ and count total # of plots as Nplots
  if(verbose>0) std::cout << std::endl;
  getAllPlots( files_, plotList_, histo_, histo2_, N1Dplots, Nplots, verbose);

  // ---
  //    lumiweighting for choosen luminosity
  // ---
  // scale every histo in histo_ and histo2_ to the corresponding luminosity
  // Additionally the mu eff SF is applied
  // NOTE: luminosity [/pb]
  scaleByLuminosity(plotList_, histo_, histo2_, N1Dplots, luminosity, verbose, systematicVariation);

  // ---
  //    add single top channels and DiBoson contributions
  // ---
  // for SingleTop and DiBoson samples:
  // every plot plotList_ existing in sTop/ diBoson .root file
  // will be combined and saved in the histo_ and histo2_ map
  // reCreate: reCreate combined plots if they are already existing
  bool reCreate=true;
  AddSingleTopAndDiBoson(plotList_, histo_, histo2_, N1Dplots, verbose, reCreate);

  // ---
  //    configure histograms
  // ---
  // needs: plotList_, histo_, histo2_, N1Dplots, axisLabel_, axisLabel1D, axisLabel2D
  std::vector<TString> axisLabel_;
  axisLabel_.insert( axisLabel_.begin(), axisLabel1D, axisLabel1D + sizeof(axisLabel1D)/sizeof(TString) );
  axisLabel_.insert( axisLabel_.end()  , axisLabel2D, axisLabel2D + sizeof(axisLabel2D)/sizeof(TString) );
  if(verbose>1){
    std::cout << "(plot, x Axis label , y Axis label , log scale?, rebinning factor):" << std::endl;
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      std::cout << plotList_[plot] << ": " << getStringEntry(axisLabel_[plot],1);
      std::cout << " , " << getStringEntry(axisLabel_[plot], 2);
      if(plot<N1Dplots){
	std::cout<< " , " << getStringEntry(axisLabel_[plot], 3);
	std::cout<< " , " << getStringEntry(axisLabel_[plot], 4);
      }
      std::cout << std::endl;
    }
  }
  // loop samples
  for(unsigned int sample=kSig; sample<=kData; ++sample){
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      // a) 1D
      if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)){ 
	// default
	histogramStyle( *histo_[plotList_[plot]][sample], sample, true );
	// special configurations
	if(getStringEntry(plotList_[plot], 2)=="PartonJetDRall")histo_[plotList_[plot]][sample]->SetNdivisions(816);
      }
      // b) 2D
      if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)) histStyle2D( *histo2_[plotList_[plot]][sample], sampleLabel(sample), getStringEntry(axisLabel_[plot],1), getStringEntry(axisLabel_[plot],2));
    }
  }

  // ---
  //    rebinning 1D histograms
  // ---
  // loop samples
  for(unsigned int sample=kSig; sample<=kData; ++sample){
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      TString plotName=plotList_[plot];
      // check if plot exists and is 1D
      if((plot<N1Dplots)&&(plotExists(histo_, plotName, sample))){
	// equidistant binning
	double reBinFactor = atof(((string)getStringEntry(axisLabel_[plot],4)).c_str());
	if(reBinFactor>1){
	  equalReBinTH1(reBinFactor, histo_, plotName, sample);
	}
      }
    }
  }

  // ---
  //    create legends
  // ---
  unsigned int Nlegends=0;  
  TLegend *leg0 = new TLegend(0.05, 0.15, 1.05, 0.9);
  TLegend *leg1 = new TLegend(0.05, 0.15, 1.05, 0.9);
  Nlegends+=2;
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("after selection, before b-tagging");
  leg1->SetHeader("after selection & b-tagging");
  // fill in contributing sample
  // loop samples
  for(unsigned int sample=kSig; sample<=kData; ++sample){
    // check if sampe exists in at least one plot
    bool exit=false;
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      // if found: add entry to legend
      if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)&&(!exit)){
	bool TwoThousandElevenData=false;
	if(luminosity>36.0) TwoThousandElevenData=true;
	if(sample==kData){
	  leg0->AddEntry(histo_[plotList_[plot]][sample], sampleLabel(sample,TwoThousandElevenData)+", "+lumi+" pb^{-1}", "PL");
	  leg1->AddEntry(histo_[plotList_[plot]][sample], sampleLabel(sample,TwoThousandElevenData)+", "+lumi+" pb^{-1}", "PL");
	}
	else{
	  leg0->AddEntry(histo_[plotList_[plot]][sample], sampleLabel(sample), "F");
	  leg1->AddEntry(histo_[plotList_[plot]][sample], sampleLabel(sample), "F");
	}
	exit=true;
      }
    }
  }

  // ---
  //    create canvas
  // ---
  std::vector<TCanvas*> plotCanvas_;
  //  int NCanvas = Nplots+Nlegends;
  // a) create canvas for all plots + legends
  //  for(int sample=0; sample<NCanvas; sample++){
  for(unsigned int sample=0; sample<N1Dplots+N2Dplots+Nlegends; sample++){
    char canvname[10];
    sprintf(canvname,"canv%i",sample);    
    plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*plotCanvas_[sample]);
  }

  // ---
  //    change 1D plots into stack plots
  // ---
  // loop plots -> all 1D plots will become stacked plots
  if(verbose>1) std::cout << std::endl;
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    createStackPlot(plotList_, histo_, plot, N1Dplots, verbose);
  }
  if(verbose>1) std::cout << std::endl;

  // ---
  //    do the printing
  // ---
  // a) for plots
  int canvasNumber=0;
  // loop plots
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    bool first=true;
    // open canvas and set titel corresponding to plotname in .root file
    plotCanvas_[canvasNumber]->cd(0);
    plotCanvas_[canvasNumber]->SetTitle(getStringEntry(plotList_[plot], 2)+getStringEntry(plotList_[plot], 1));
    // loop samples
    for(unsigned int sample=kSig; sample<=kData; ++sample){
      // a1) for 1D event yields, efficiency and cross section plots (existing)
      if((plot<N1Dplots)||(plot>=N1Dplots+N2Dplots)){
	// check if plot is existing
	if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)){
	  if(verbose>0){
	    std::cout << "plotting " << plotList_[plot];
	    std::cout << " from sample " << sampleLabel(sample);
	    std::cout << " to canvas " << canvasNumber << " ( ";
	    std::cout << plotCanvas_[canvasNumber]->GetTitle() << " )" << std::endl;
	  }
	  // first plot
	  if(first){
	    // min / max
	    double max = 1.3*histo_[plotList_[plot]][sample]->GetMaximum();
	    // if data file exists
	    if(histo_[plotList_[plot]].count(kData)>0){
	      // and has larger maximum
	      if(max < 1.3*histo_[plotList_[plot]][kData]->GetMaximum()){
		// take this maximum
		max = 1.3*histo_[plotList_[plot]][kData]->GetMaximum();
		if(verbose>1) std:: cout << "take max from data! " << std::endl;
	      }
	    }
	    double min = 0;
	    // log plots
	    if(getStringEntry(axisLabel_[plot],3)=="1"){
	      plotCanvas_[canvasNumber]->SetLogy(1);
	      min=1;
	      max=exp(1.3*(std::log(max)-std::log(min))+std::log(min));
	      if(plotList_[plot]=="analyzeTopRecoKinematicsKinFit/prob") min=0.1; 
	    }
	    // get nicer int values if maximum is large enough
	    if(max>3) max = (double)roundToInt(max);
	    // axis style
	    axesStyle(*histo_[plotList_[plot]][sample], getStringEntry(axisLabel_[plot],1), getStringEntry(axisLabel_[plot],2), min, max); 
	    // draw histos (as stack)
	    histo_[plotList_[plot]][sample]->Draw("hist");
	    histo_[plotList_[plot]][42] = (TH1F*)(histo_[plotList_[plot]][sample]->Clone());
	  }
	  // draw other plots into same canvas
	  else{ 
	    // draw data as points
	    if(sample==kData) histo_[plotList_[plot]][sample]->Draw("p e1 X0 same");
	    // draw others as histo (stack)
	    else histo_[plotList_[plot]][sample]->Draw("hist same");
	  }
	  first=false;
	  // redraw axis at the end
	  if((histo_.count(plotList_[plot])>0)&&(sample==kData)) histo_[plotList_[plot]][42]->Draw("axis same");
	}
      }
      // a3) for 2D plots
      if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)){
	// new Canvas for every plot
	plotCanvas_[canvasNumber]->cd(0);
	plotCanvas_[canvasNumber]->SetRightMargin ( 0.15 );
	plotCanvas_[canvasNumber]->SetTitle(getStringEntry(plotList_[plot],2)+getStringEntry(plotList_[plot],1)+getTStringFromInt(sample)); 
	if(verbose>1){
	  std::cout << "plotting " << plotList_[plot];
	  std::cout << " from sample " << sampleLabel(sample);
	  std::cout << " to canvas " << canvasNumber  << " ( ";
	  std::cout << plotCanvas_[canvasNumber]->GetTitle() << " )"  << std::endl;
	}
	++canvasNumber;
	// draw histo
	histo2_[plotList_[plot]][sample]->Draw("colz");
	// print correlation factor
	double d = histo2_[plotList_[plot]][sample]->GetCorrelationFactor();
	char correlation[20];
	sprintf(correlation, "%f", d);
        TString corr = (TString)correlation;
	DrawLabel("correlation: "+corr, 0.35, 0.92, 0.75, 0.99, 0.7);
      }
    }
    // for 1D hists: next canvas
    if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)) ++canvasNumber;
  }
  // b) for legends
  // b1) before btagging
  plotCanvas_[canvasNumber]->cd(0);
  plotCanvas_[canvasNumber]->SetTitle("legendMonitoringBeforeBtagging");
  leg0->Draw("");
  ++canvasNumber;
  // b2) after btagging
  plotCanvas_[canvasNumber]->cd(0);
  plotCanvas_[canvasNumber]->SetTitle("legendMonitoringAfterBtagging");
  leg1->Draw("");
  ++canvasNumber;

  // ---
  // saving
  // ---
  if(save){
    // pdf and eps
    saveCanvas(plotCanvas_, outputFolder, pdfName);
    // root file
    std::cout << "will create outputfile named " << outputFileName << std::endl;
    for(unsigned int idx=0; idx<plotCanvas_.size(); ++idx){
      saveToRootFile(outputFileName, plotCanvas_[idx], true, verbose, "monitoring");
    }
  }
}
