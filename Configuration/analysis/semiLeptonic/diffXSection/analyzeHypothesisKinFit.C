#include "basicFunctions.h"

void analyzeHypothesisKinFit(double luminosity = 35900, bool save = false, int systematicVariation=sysNo, TString dataFile= "./diffXSecFromSignal/data/oldDataNoL1/DiffXSecData_Nov15PF.root")
{
  //  ---
  //     options
  //  ---
  // a) options directly entered when calling function
  /* systematicVariation: which systematic shift do you want to make? from basicFunctions.h:
     0:sysNo              1:sysLumiUp          2:sysLumiDown          3:sysJESUp      
     4:sysJESDown         5:sysJERUp           6:sysJERDown           7:sysTopScaleUp 
     8:sysTopScaleDown    9:sysVBosonScaleUp  10:sysVBosonScaleDown  11:sysTopMatchUp 
     12:sysTopMatchDown  13:sysVBosonMatchUp  14:sysVBosonMatchDown  15:sysMuEffSFup  
     16:sysMuEffSFdown   17:sysISRFSRup       18:sysISRFSRdown       19:sysPileUp    
     20:sysQCDup         21:sysQCDdown
  */
  // save: save plots?
  // data file: relative path of .root file
  // luminosity: [/nb]
  TString lumi = getTStringFromInt(roundToInt((0.001*luminosity), false));
  // b) options to be configured only once
  // get the .root files from the following folder:
  TString inputFolder = "./diffXSecFromSignal/analysisRootFilesWithKinFit";
  // save all plots into the following folder
  TString outputFolder = "./diffXSecFromSignal/plots/kinFit/";
  // choose name of the output .pdf file
  TString pdfName="kinFit"+lumi+"Hypothesis";
  // set detail level of output 
  // 0: no output, 1: std output 2: output for debugging
  unsigned int verbose=2;
  // c) set root style
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetEndErrorSize (8);
  gStyle->SetPalette(1);
  //  gStyle->SetErrorX(0); 

  //  ---
  //     choose plots
  //  ---
  // a) list plots you would like to see ("folder/plotName") - same as in .root files (for 1D and 2D)
  TString plots1D[ ] = { "analyzeHypoKinFit/prob"       , 
			 "analyzeHypoKinFit/chi2"       , 
			 "analyzeHypoKinFit/hadBQuark"  , 
			 "analyzeHypoKinFit/lepBQuark"  , 
			 "analyzeHypoKinFit/lightQuark" , 
			 "analyzeHypoKinFit/delChi2"    ,
			 "analyzeHypoKinFit/wrongAssign",
                         "analyzeTopRecoKinematicsKinFit/ttbarMass" 
                       };
  TString plots2D[ ] = { "analyzeHypoKinFit/mapKinFit_" };
  // b) list plot axes style
  // 1D: "x-axis title"/"y-axis title"/log
  // log = 0 or 1 for linear or logarithmic axis 
  TString axisLabel1D[ ] = { "probability (best fit hypothesis)/events/0"                   , 
			     "#chi^{2} (best fit hypothesis)/events/0"                      ,
			     "i(genMatch - kinFit), hadronic b-quark/events/0"              , 
			     "i (genMatch - kinFit), leptonic b-quark/events/0"             , 
			     "i(genMatch - kinFit), light quarks/events/0"                  , 
			     "#Delta#chi^{2} (1^{st} - 2^{nd} best fit hypothesis)/events/0", 
			     "N(wrong assigned jets)/events/0"                              , 
                             "m(t#bar{t})/events/0"
                           };
  // 2D: "x-axis title"/"y-axis title"
  TString axisLabel2D[ ] = {"jet hypothesis/generator truth"};

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
  plotList_.insert( plotList_.end(), plots2D, plots2D + sizeof(plots2D)/sizeof(TString) );
  // count #1D plots
  unsigned int N1Dplots = sizeof(plots1D)/sizeof(TString);
  // container for all histos (1D&2D)
  // example for acess: histo_["plotName"][sampleNr]
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, std::map <unsigned int, TH2F*> > histo2_;
  // total # plots 
  int Nplots=0;
  // save all histos from plotList_ that exist in files_ into 
  // histo_ and histo2_ and count total # of plots as Nplots
  getAllPlots( files_, plotList_, histo_, histo2_, N1Dplots, Nplots, verbose);

  // ---
  //    lumiweighting for choosen luminosity
  // ---
  // scale every histo in histo_ and histo2_ to the corresponding luminosity
  // Additionally the mu eff SF is applied
  // NOTE: luminosity [/pb]
  scaleByLuminosity(plotList_, histo_, histo2_, N1Dplots, 0.001*luminosity, verbose, systematicVariation);

  // ---
  //    add single top channels and DiBoson contributions
  // ---
  // if combined SingleTop and DiBoson samples do not exist as combined 
  // .root file, every plot existing in each sTop/ diBoson file
  // will be combined and saved in the histo_ and histo2_ map
  AddSingleTopAndDiBoson(plotList_, histo_, histo2_, N1Dplots, verbose);

  // ---
  //    change 1D plots into stack plots
  // ---
  // loop plots -> all 1D plots will become stacked plots
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    createStackPlot(plotList_, histo_, plot, N1Dplots, verbose);
  }
  if(verbose>1) std::cout << std::endl;

  // ---
  //    configure histograms
  // ---
  // needs: plotList_, histo_, histo2_, N1Dplots, axisLabel_, axisLabel1D, axisLabel2D
  std::vector<TString> axisLabel_;
  axisLabel_.insert( axisLabel_.begin(), axisLabel1D, axisLabel1D + sizeof(axisLabel1D)/sizeof(TString) );
  axisLabel_.insert( axisLabel_.end()  , axisLabel2D, axisLabel2D + sizeof(axisLabel2D)/sizeof(TString) );
  if(verbose>1){
    std::cout << "(plot, x Axis label , y Axis label , log scale?):" << std::endl;
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      std::cout << plotList_[plot] << ": " << getStringEntry(axisLabel_[plot],1);
      std::cout << " , " << getStringEntry(axisLabel_[plot], 2);
      if(plot<N1Dplots) std::cout<< " , " << getStringEntry(axisLabel_[plot], 3);
      std::cout << std::endl;
    }
  }
  // loop samples
  for(unsigned int sample=kSig; sample<=kData; ++sample){
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      // a) 1D
      if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)) histogramStyle( *histo_[plotList_[plot]][sample], sample, true );
      // b) 2D
      if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)) histStyle2D( *histo2_[plotList_[plot]][sample], sampleLabel(sample), getStringEntry(axisLabel_[plot],1), getStringEntry(axisLabel_[plot],2));
    }
  }

  // ---
  //    create one legend for all 1D histos
  // ---
  int Nlegends=0;  
  TLegend *leg0 = new TLegend(0.05, 0.15, 1.05, 0.9);
  ++Nlegends;
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Kin. Fit (after selection)");
  // fill in contributing sample
  // loop samples
  for(unsigned int sample=kSig; sample<=kData; ++sample){
    // check if sampe exists in at least one plot
    bool exit=false;
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      // if found: add entry to legend
      if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)&&(!exit)){
	if(sample==kData) leg0->AddEntry(histo_[plotList_[plot]][sample], sampleLabel(sample)+", "+lumi+" pb^{-1}", "PL");
	else leg0->AddEntry(histo_[plotList_[plot]][sample], sampleLabel(sample), "F");
	exit=true;
      }
    }
  }

  // ---
  //    create canvas
  // ---
  std::vector<TCanvas*> plotCanvas_;
  if(verbose>1) std::cout << std::endl << "#plots: 1D +2D = " << plotList_.size() << " ( " << N1Dplots << " + " << plotList_.size()-N1Dplots << " )" << std::endl;
  if(verbose>1) std::cout << std::endl << "#Canvas: " << Nplots << std::endl;
  // a) create canvas for all plots + legends
  for(int sample=0; sample<Nplots+Nlegends; sample++){
    char canvname[10];
    sprintf(canvname,"canv%i",sample);    
    plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*plotCanvas_[sample]);
  }

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
    plotCanvas_[canvasNumber]->SetTitle(getStringEntry(plotList_[plot]));
    // loop samples
    for(unsigned int sample=kSig; sample<=kData; ++sample){
      // a1) for 1D plots (existing)
      if(plot<N1Dplots){
	// check if plot is existing
	if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)){
	  if(verbose>0) std::cout << "plotting " << plotList_[plot] << " from sample " << sampleLabel(sample) << " to canvas " << canvasNumber << " ( " << plotCanvas_[canvasNumber]->GetTitle() << " )" << std::endl;
	  // first plot
	  if(first){
	    // min / max
	    double max = 1.2*histo_[plotList_[plot]][sample]->GetMaximum();
	    double min = 0;
	    // log plots
	    if(getStringEntry(axisLabel_[plot],3)=="1"){
	      plotCanvas_[canvasNumber]->SetLogy(1);
	      min=1;
	      max=exp(1.2*(std::log(max)-std::log(min))+std::log(min));
	    }
	    // axes and drawing
	    axesStyle(*histo_[plotList_[plot]][sample], getStringEntry(axisLabel_[plot],1), getStringEntry(axisLabel_[plot],2), 0, 1.2*histo_[plotList_[plot]][sample]->GetMaximum());
	    histo_[plotList_[plot]][sample]->Draw("");
	    histo_[plotList_[plot]][42] = (TH1F*)(histo_[plotList_[plot]][sample]->Clone());
	  }
	  // draw other plots into same canvas, draw data as points
	  else{ 
	    if(sample!=kData) histo_[plotList_[plot]][sample]->Draw("same");
	    if(sample==kData) histo_[plotList_[plot]][sample]->Draw("p X0 same");
	  }
	  first=false;
	}
	// redraw axis at the end
	if((histo_.count(plotList_[plot])>0)&&(sample==kData)) histo_[plotList_[plot]][42]->Draw("axis same");
      }
      // a2) for 2D plots
      if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)){
	// new Canvas for every plot
	plotCanvas_[canvasNumber]->cd(0);
	plotCanvas_[canvasNumber]->SetTitle(getStringEntry(plotList_[plot],2)+getTStringFromInt(sample));
	if(verbose>1) std::cout << "plotting " << plotList_[plot] << " from sample " << sampleLabel(sample) << " to canvas " << canvasNumber  << " ( " << plotCanvas_[canvasNumber]->GetTitle() << " )"  << std::endl;
	++canvasNumber;
	// draw histo
	histo2_[plotList_[plot]][sample]->Draw("colz");
      }
    }
    // for 1D hists: next canvas
    if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)) ++canvasNumber;
  }
  // b) for legends
  plotCanvas_[canvasNumber]->cd(0);
  plotCanvas_[canvasNumber]->SetTitle("legendHypoKinFit");
  leg0->Draw("");
  ++canvasNumber;

  // ---
  // saving
  // ---
  if(save) saveCanvas(plotCanvas_, outputFolder, pdfName);
}
