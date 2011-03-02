#include "basicFunctions.h"

void analyzeHypothesisKinFit(double luminosity = 36100, bool save = false, TString dataFile= "./diffXSecFromSignal/data/oldDataNoL1/DiffXSecData_Nov15PF.root")
{
    // luminosity
    TString lumi = getTStringFromInt(roundToInt((0.001*luminosity), false));
    // save all plots into the following folder
    TString saveTo = "./diffXSecFromSignal/plots/kinFit/";
    // detailed output for debugging
    bool outPutForDebugging=true;
    
  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/analysisRootFilesWithKinFit";
  TString fileName;
  for(int ienum = kSig; ienum<=kSToptW; ienum++){
    if((ienum!=kSTop)&&(ienum!=kWW)&&(ienum!=kWZ)&&(ienum!=kZZ)){
      fileName = "./diffXSecFromSignal"+whichSample+"/muonDiffXSec";
      if(ienum==kSig)   fileName += "SigMadD6TFall10";
      if(ienum==kBkg)   fileName += "BkgMadD6TFall10";
      if(ienum==kWjets) fileName += "WjetsMadD6TFall10";
      if(ienum==kZjets) fileName += "ZjetsMadD6TFall10";
      if(ienum==kDiBos) fileName += "VVPytia6Z2Fall10";
      if(ienum==kQCD)   fileName += "QCDPythiaZ2Fall10";
      if(ienum==kSToptW)fileName += "SingleTopTWchannelMadZ2Fall10";
      if(ienum==kSTops) fileName += "SingleTopSchannelMadZ2Fall10";
      if(ienum==kSTopt) fileName += "SingleTopTchannelMadZ2Fall10";
      fileName += "PF.root";
      if(ienum==kData)  fileName = dataFile;
      files_.push_back(new TFile(fileName));
    }
  }

  // ---
  //    get histograms
  // ---
  // a) setup structure
  // create container for all histos (1D&2D)
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, std::map <unsigned int, TH2F*> > histo2_;
  // example: histo_["plotName"][sampleNr]
  // set plot names - same as in .root files (for 1D and 2D)
  TString plots1D[ 5 ] = { "analyzeHypoKinFit/prob"     , "analyzeHypoKinFit/chi2"      , "analyzeHypoKinFit/hadBQuark",
			   "analyzeHypoKinFit/lepBQuark", "analyzeHypoKinFit/lightQuark" };
  TString plots2D[ 1 ] = { "analyzeHypoKinFit/mapKinFit_" };
  // collect all plot names in vector (first 1D, then 2D), count #1D plots
  std::vector<TString> plots_;
  plots_.insert( plots_.begin(), plots1D, plots1D + 5 );
  unsigned int N1Dplots = plots_.size();
  plots_.insert( plots_.end(), plots2D, plots2D + 1 );

  // b) get histos from files
  // needs: plots_, histo_, histo2_, N1Dplots
  int Nplots=0;
  // loop plots
  for(unsigned int plot=0; plot<plots_.size(); ++plot){    
    // loop sample
    for(unsigned int idx=kSig; idx<=kSToptW; ++idx) {
      if(idx==kSig){
	// create plot container
	TH1* targetPlot;
	//	if(plot>=N1Dplots) (TH2F*)targetPlot;
	files_[idx]->GetObject(plots_[plot], targetPlot);
	// Check if plot exits
	if(targetPlot){
	  // save plot in corresponding map
	  if(plot<N1Dplots ) histo_ [plots_[plot]][idx] = (TH1F*)files_[idx]->Get(plots_[plot]);
	  if(plot>=N1Dplots) histo2_[plots_[plot]][idx] = (TH2F*)files_[idx]->Get(plots_[plot]);
	  // count every 2D plot (every sample is counted separetly as it will be drawn into an own canvas)
	  if(plot>=N1Dplots) Nplots++;
	}
	else std::cout << "can not find plot "+plots_[plot] << " in file "+(TString)(files_[idx]->GetName()) << std::endl;
      }
    }
    // count every type of 1D plots (neglect #samples here as they well be drawn into the same canvas)
    if((plot<N1Dplots)&&(histo_.count(plots_[plot])>0)) Nplots++;
  }
  
  // ---
  //    lumiweighting for choosen luminosity
  // ---
  // needs: plots_, histo_, histo2_, N1Dplots
  // loop samples
  for(unsigned int idx=kSig; idx<=kSToptW; ++idx) {
    // loop plots 
    for(unsigned int plot=0; plot<plots_.size(); ++plot){
      // a) 1D
      // check if plot exists
      if((plot<N1Dplots)&&(histo_.count(plots_[plot])>0)&&(histo_[plots_[plot]].count(idx)>0)){
	if(outPutForDebugging) std::cout << std::endl << "plot: "+plots_[plot] << " for sample " << sampleLabel(idx) << ":" << std::endl;
	if(outPutForDebugging) std::cout << "#events before weighting: " << histo_[plots_[plot]][idx]->Integral(0, histo_[plots_[plot]][idx]->GetNbinsX()+1) << std::endl;
	// scale MC samples to same luminosity
	double weight = lumiweight(idx, 0.001*luminosity);
	histo_[plots_[plot]][idx]->Scale(weight);
	if(outPutForDebugging) std::cout << "weight: " << weight << std::endl;
	if(outPutForDebugging) std::cout << "#events after weighting: " << histo_[plots_[plot]][idx]->Integral(0, histo_[plots_[plot]][idx]->GetNbinsX()+1) << std::endl;
	// apply eff. SF for MC
	if(idx!=kData) histo_[plots_[plot]][idx]->Scale(effSFAB);
      }
      // b) 2D
      // check if plot exists
      if((plot>=N1Dplots)&&(histo2_.count(plots_[plot])>0)&&(histo2_[plots_[plot]].count(idx)>0)){
	if(outPutForDebugging) std::cout << std::endl << "plot: "+plots_[plot] << " for sample " << sampleLabel(idx) << ":" << std::endl;
	if(outPutForDebugging) std::cout << "#events before weighting: " << histo2_[plots_[plot]][idx]->Integral(0, histo2_[plots_[plot]][idx]->GetNbinsX()+1, 0, histo2_[plots_[plot]][idx]->GetNbinsY()+1) << std::endl;
	// scale MC samples to same luminosity
	double weight = lumiweight(idx, 0.001*luminosity);
	histo2_[plots_[plot]][idx]->Scale(weight);
	if(outPutForDebugging) std::cout << "weight: " << weight << std::endl;
	if(outPutForDebugging) std::cout << "#events after weighting: " << histo2_[plots_[plot]][idx]->Integral(0, histo2_[plots_[plot]][idx]->GetNbinsX()+1, 0, histo2_[plots_[plot]][idx]->GetNbinsY()+1) << std::endl;
	// apply eff. SF for MC
	if(idx!=kData) histo2_[plots_[plot]][idx]->Scale(effSFAB);
      }
    }
  }

  // ---
  //    add single top and DiBoson 
  // ---
  // needs: plots_, histo_, histo2_, N1Dplots
  // loop plots 
  for(unsigned int plot=0; plot<plots_.size(); ++plot){
    // a) 1D
    if((plot<N1Dplots)){
      // a.1) single Top
      if((histo_[plots_[plot]].count(kSTops)>0)&&(histo_[plots_[plot]].count(kSTopt)>0)&&(histo_[plots_[plot]].count(kSToptW)>0)){
	histo_[plots_[plot]][kSTop]  =   (TH1F*)histo_[plots_[plot]][kSTops ]->Clone();
	histo_[plots_[plot]][kSTop]->Add((TH1F*)histo_[plots_[plot]][kSTopt ]->Clone());
	histo_[plots_[plot]][kSTop]->Add((TH1F*)histo_[plots_[plot]][kSToptW]->Clone());
      }
      // a.2) DiBoson
      if((histo_[plots_[plot]].count(kWW)>0)&&(histo_[plots_[plot]].count(kWZ)>0)&&(histo_[plots_[plot]].count(kZZ)>0)){
	histo_[plots_[plot]][kDiBos]  =   (TH1F*)histo_[plots_[plot]][kWW]->Clone();
	histo_[plots_[plot]][kDiBos]->Add((TH1F*)histo_[plots_[plot]][kWZ]->Clone());
	histo_[plots_[plot]][kDiBos]->Add((TH1F*)histo_[plots_[plot]][kZZ]->Clone());
      }
    }
    // b) 2D
    if((plot>=N1Dplots)){
      // b.1) single Top
      if((histo2_[plots_[plot]].count(kSTops)>0)&&(histo2_[plots_[plot]].count(kSTopt)>0)&&(histo2_[plots_[plot]].count(kSToptW)>0)){
	histo2_[plots_[plot]][kSTop]  =   (TH2F*)histo2_[plots_[plot]][kSTops ]->Clone();
	histo2_[plots_[plot]][kSTop]->Add((TH2F*)histo2_[plots_[plot]][kSTopt ]->Clone());
	histo2_[plots_[plot]][kSTop]->Add((TH2F*)histo2_[plots_[plot]][kSToptW]->Clone());
      }
      // b.2) DiBoson
      if((histo2_[plots_[plot]].count(kWW)>0)&&(histo2_[plots_[plot]].count(kWZ)>0)&&(histo2_[plots_[plot]].count(kZZ)>0)){
	histo2_[plots_[plot]][kDiBos]  =   (TH2F*)histo2_[plots_[plot]][kWW]->Clone();
	histo2_[plots_[plot]][kDiBos]->Add((TH2F*)histo2_[plots_[plot]][kWZ]->Clone());
	histo2_[plots_[plot]][kDiBos]->Add((TH2F*)histo2_[plots_[plot]][kZZ]->Clone());
      }
    }
  }

  // ---
  //    change 1D plots into stack plots
  // ---
  // needs: plots_, histo_, N1Dplots
  // loop plots 
  for(unsigned int plot=0; plot<plots_.size(); ++plot){
    // loop samples backwards
    for(int idx=kDiBos; idx>=kSig; --idx){
      // check if plot exists
      if((plot<N1Dplots)&&(histo_.count(plots_[plot])>0)&&(histo_[plots_[plot]].count(idx)>0)){
	// check if previous plot also exists
	if(histo_[plots_[plot]].count(idx+1)>0){
	  histo_[plots_[plot]][idx]->Add((TH1F*)histo_[plots_[plot]][idx+1]->Clone());
	    if(outPutForDebugging) std::cout << "add "+plots_[plot] << " plot for " << sampleLabel(idx) << " and " << sampleLabel(idx+1) << std::endl;
	    if(outPutForDebugging) std::cout << "this new stacked plot contains now " <<  histo_[plots_[plot]][idx]->Integral(0, histo_[plots_[plot]][idx]->GetNbinsX()+1) << " events" << std::endl;
	}
      }
    }
  }
  if(outPutForDebugging)  std::cout << std::endl;

  // ---
  //    configure histograms
  // ---
  // needs: plots_, histo_, histo2_, N1Dplots, xAxisLabel_
  // set x axis label
  TString xAxisLabel[ 6 ] = { "probability (best fit hypothesis)", "#chi^{2} (best fit hypothesis)", "i(genMatch - kinFit), hadronic b-quark", "i (genMatch - kinFit), leptonic b-quark", "i(genMatch - kinFit), light quarks", "jet hypothesis vs. generator truth" };
  std::vector<TString> xAxisLabel_;
  xAxisLabel_.insert( xAxisLabel_.begin(), xAxisLabel, xAxisLabel + 6 );
  if(outPutForDebugging){
    std::cout << "x Axis labels: " << std::endl;
    // loop plots
    for(unsigned int plot=0; plot<plots_.size(); ++plot){
      std::cout << xAxisLabel_[plot] << " ";
    }
    std::cout << std::endl;
  }
  // loop samples
  for(unsigned int idx=kSig; idx<=kData; ++idx){
    // loop plots
    for(unsigned int plot=0; plot<plots_.size(); ++plot){
      // a) 1D
      if((plot<N1Dplots)&&(histo_.count(plots_[plot])>0)&&(histo_[plots_[plot]].count(idx)>0)) histogramStyle( *histo_[plots_[plot]][idx], idx, true );
      // b) 2D
      if((plot>=N1Dplots)&&(histo2_.count(plots_[plot])>0)&&(histo2_[plots_[plot]].count(idx)>0)) histStyle2D( *histo2_[plots_[plot]][idx], sampleLabel(idx), xAxisLabel_[plot], "");
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
  for(unsigned int idx=kSig; idx<=kData; ++idx){
    // check if sampe exists in at least one plot
    bool exit=false;
    // loop plots
    for(unsigned int plot=0; plot<plots_.size(); ++plot){
      // if found: add entry to legend
      if((histo_.count(plots_[plot])>0)&&(histo_[plots_[plot]].count(idx)>0)&&(!exit)){
	if(idx==kData) leg0->AddEntry(histo_[plots_[plot]][idx], sampleLabel(idx)+", "+lumi+" pb^{-1}", "PL");
	else leg0->AddEntry(histo_[plots_[plot]][idx], sampleLabel(idx), "F");
	exit=true;
      }
    }
  }

  // ---
  //    create canvas
  // ---
  std::vector<TCanvas*> MyCanvas;
    if(outPutForDebugging) std::cout << std::endl << "#plots: 1D +2D = " << plots_.size() << " ( " << N1Dplots << " + " << plots_.size()-N1Dplots << " )" << std::endl;
    if(outPutForDebugging) std::cout << std::endl << "#Canvas: " << Nplots << std::endl;
  // a) create canvas for all plots + legends
  for(int idx=0; idx<Nplots+Nlegends; idx++){
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ---
  //    do the printing
  // ---
  // a) for plots
  int canvasNumber=0;
  // loop plots
  for(unsigned int plot=0; plot<plots_.size(); ++plot){
    bool first=true;
    // open canvas and set titel corresponding to plotname in .root file
    MyCanvas[canvasNumber]->cd(0);
    MyCanvas[canvasNumber]->SetTitle(getNameAfterSlash(plots_[plot]));
    // loop samples
    for(unsigned int idx=kSig; idx<=kData; ++idx){
      // a1) for 1D plots (existing)
      if(plot<N1Dplots){
	// check if plot is existing
	if((histo_.count(plots_[plot])>0)&&(histo_[plots_[plot]].count(idx)>0)){
	  if(outPutForDebugging) std::cout << "plotting " << plots_[plot] << " from sample " << sampleLabel(idx) << " to canvas " << canvasNumber << " ( " << MyCanvas[canvasNumber]->GetTitle() << " )" << std::endl;
	  // axes style and drawing for first plot
	  if(first){
	    axesStyle(*histo_[plots_[plot]][idx], xAxisLabel_[plot], "events", 0, 1.2*histo_[plots_[plot]][idx]->GetMaximum());
	    histo_[plots_[plot]][idx]->Draw("");
	    histo_[plots_[plot]][42] = (TH1F*)(histo_[plots_[plot]][idx]->Clone());
	  }
	  // draw other plots into same canvas
	  else histo_[plots_[plot]][idx]->Draw("same");
	  first=false;
	}
	// redraw axis at the end
	if((histo_.count(plots_[plot])>0)&&(idx==kData)) histo_[plots_[plot]][42]->Draw("axis same");
      }
      // a2) for 2D plots
      if((plot>=N1Dplots)&&(histo2_.count(plots_[plot])>0)&&(histo2_[plots_[plot]].count(idx)>0)){
	// new Canvas for every plot
	MyCanvas[canvasNumber]->cd(0);
	MyCanvas[canvasNumber]->SetTitle(getNameAfterSlash(plots_[plot])+getTStringFromInt(idx));
	if(outPutForDebugging) std::cout << "plotting " << plots_[plot] << " from sample " << sampleLabel(idx) << " to canvas " << canvasNumber  << " ( " << MyCanvas[canvasNumber]->GetTitle() << " )"  << std::endl;
	++canvasNumber;
	// draw histo
	histo2_[plots_[plot]][idx]->Draw("BOX");
      }
    }
    // for 1D hists: next canvas
    if((plot<N1Dplots)&&(histo_.count(plots_[plot])>0)) ++canvasNumber;
  }
  // b) for legends
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("legendHypoKinFit");
  leg0->Draw("");
  ++canvasNumber;

  // ---
  // saving
  // ---
  if(save){
    // save all plots in one pdf
    MyCanvas[0]->Print(saveTo+"kinFit"+lumi+"Hypothesis.pdf(", "pdf");
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+"kinFit"+lumi+"Hypothesis.pdf", "pdf");   
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+"kinFit"+lumi+"Hypothesis.pdf)", "pdf");
    // save every plot as png
    for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
      MyCanvas[idx]->Print(saveTo+(TString)(MyCanvas[idx]->GetTitle())+".png");      
    }
  }

}
