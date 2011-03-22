#include "macroBasicFunctions.h"

void macroMuonZNorm(TString sys="sysNo", bool saveHistos = true, bool drawPlots = false, bool savePlots = false)
{
    // detailed output for debugging
    int verbose=1;
    applySystematicVariations(sys);
    if(verbose) std::cout<<"lumi="<<luminosity<<"; effSF="<<effSFAB<<std::endl;
    
  // ------------------------------------------------------------------------------------
  //    open input files
  // ------------------------------------------------------------------------------------
  std::map<unsigned int, TFile*> files_;
  TString fileName;
  for(int idx = kZMuMu; idx<=kSToptW; idx++){
    if((idx!=kSTop)&&(idx!=kDiBos)) {
      fileName=getFilename(idx, whichFile, sys);
      files_[idx]=new TFile(fileName);
      if(verbose) std::cout<<"Filename "<<fileName<<" opened"<<std::endl;
    }
  }

  // ------------------------------------------------------------------------------------
  //    get histograms
  // ------------------------------------------------------------------------------------
  // a) setup structure
  // create container for all histos
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  // example: histo_["plotName"][sampleNr]
  // set plot names - same as in .root files
  TString plots_[] = { "tightMuonPair/dimassRC", "tightMuonPair/dimassWC", "tightMuonPair/nMu", "tightMuonPair2ZRes/nMu",
                       "tightAllMuonKinematics2ZRes/pt", "tightAllMuonKinematics2ZRes/eta", "tightAllMuonKinematics2ZRes/phi",
                       "tightLeadingMuonKinematics2ZRes/pt", "tightLeadingMuonKinematics2ZRes/eta", "tightLeadingMuonKinematics2ZRes/phi",
    "tightJetKinematicsZRes/n" };
  // set x axis label
  TString xAxisLabel_[] = { "M_{#mu#mu} [GeV]", "M_{#mu#mu} [GeV]", "N_{#mu}", "N_{#mu}", 
	                    "p_{T}", "#eta", "#Phi",
                            "p_{T}", "#eta", "#Phi",
                            "N_{jets}" };
  // set canvas to log style if logY_>0 (default=0); set logY_ to x axis minimum (!=0 for log scale)
  double logY_[1000] = {0.}; logY_[0]=0.1;

  // collect all plot names in vector (first 1D, then 2D), count #1D plots
  //std::vector<TString> plots_;
  //plots_.insert( plots_.begin(), plots1D, plots1D + 11 );
  //unsigned int Nplots = Nplots;
  unsigned int Nplots = sizeof(plots_)/sizeof(TString);
  std::cout << "size of plots_ array: " << Nplots << std::endl;

  // b) get histos from files
  // needs: plots_, histo_
  // loop plots
  for(unsigned int plot=0; plot<Nplots; ++plot){    
    // loop sample
    for(unsigned int idx=kZMuMu; idx<=kSToptW; ++idx) {
        // kSTop and kDiBos do not have primary root files
        if((idx!=kSTop)&&(idx!=kDiBos)) {
	  // create plot container
	  TH1* targetPlot;
	  if(files_.count(idx)){
	    files_[idx]->GetObject(plots_[plot], targetPlot);
	    // Check if plot exits
	    if(targetPlot){
	      // save plot in corresponding map
	      histo_ [plots_[plot]][idx] = (TH1F*)files_[idx]->Get(plots_[plot]);
	    }
	    else std::cout << "can not find plot "+plots_[plot] << " in file "+(TString)(files_[idx]->GetName()) << std::endl;
          }
          else std::cout << "can not find files_["<<idx<<"]" << std::endl;
       }
    }
  }
  
  // ------------------------------------------------------------------------------------
  //    lumiweighting for chosen luminosity, effSF and systematic variations for BG
  // ------------------------------------------------------------------------------------
  // needs: plots_, histo_
  // loop samples
  for(unsigned int idx=kZMuMu; idx<=kSToptW; ++idx) {
    // loop plots 
    for(unsigned int plot=0; plot<Nplots; ++plot){
      // a) 1D
      // check if plot exists
      if((histo_.count(plots_[plot])>0)&&(histo_[plots_[plot]].count(idx)>0)){
	if(verbose>1) std::cout << std::endl << "plot: "+plots_[plot] << " for sample " << sampleLabel(idx) << ":" << std::endl;
	if(verbose>1) std::cout << "#events before weighting: " << histo_[plots_[plot]][idx]->Integral(0, histo_[plots_[plot]][idx]->GetNbinsX()+1) << std::endl;
	// scale MC samples to same luminosity
	double weight = lumiweight(idx, luminosity, sys);
	histo_[plots_[plot]][idx]->Scale(weight);
	if(verbose>1) std::cout << "weight: " << weight << std::endl;
	if(verbose>1) std::cout << "#events after weighting: " << histo_[plots_[plot]][idx]->Integral(0, histo_[plots_[plot]][idx]->GetNbinsX()+1);
	// apply eff. SF for MC
	if(idx!=kData) histo_[plots_[plot]][idx]->Scale(effSFAB);
	if(verbose>1) std::cout << "; # after effSF cor: " << histo_[plots_[plot]][idx]->Integral(0, histo_[plots_[plot]][idx]->GetNbinsX()+1);
	// apply background scaling in case of systematic variations
	sysBgScaling(histo_[plots_[plot]][idx], idx, sys);
	if(verbose>1) std::cout << "; # after bg scaling: " << histo_[plots_[plot]][idx]->Integral(0, histo_[plots_[plot]][idx]->GetNbinsX()+1) << std::endl;
      }
    }
  }

  // ------------------------------------------------------------------------------------
  //    add single top and DiBoson 
  // ------------------------------------------------------------------------------------
  // needs: plots_, histo_
  // loop plots 
  for(unsigned int plot=0; plot<Nplots; ++plot){
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
  
  // ------------------------------------------------------------------------------------
  //    save lumiweighted and added histograms
  // ------------------------------------------------------------------------------------
  
  // save histos in root file:
  // at the moment only one histo (enough for XSec determination)
  if(saveHistos){
    TFile fOut(folderResults+whichFile+"_lumiweightedAndAddedHistos.root", "recreate");
      for(int idx=kZMuMu; idx<=kSToptW; idx++){
	if (histo_.count("tightMuonPair2ZRes/nMu")>0 && histo_["tightMuonPair2ZRes/nMu"].count(idx)>0)
	  histo_["tightMuonPair2ZRes/nMu"][idx]->Write(sampleEnum(idx)+"_"+"tightMuonPair2ZRes_nMu");
      }
    if(verbose) std::cout<<folderResults<<whichFile<<"_lumiweightedAndAddedHistos.root written"<<std::endl;
    fOut.Close();
  }
  
  // ------------------------------------------------------------------------------------
  //    section to build and draw stack plots if flag is set
  // ------------------------------------------------------------------------------------
  
  if(drawPlots){
  // ------------------------------------------------------------------------------------
  //    build custom stack plots
  // ------------------------------------------------------------------------------------
  // needs: plots_, histo_, N1Dplots
  // loop plots 
  for(unsigned int plot=0; plot<Nplots; ++plot){
    // loop samples backwards
    for(int idx=kDiBos-1; idx>=kZMuMu; --idx){
      // check if plot exists
      if((histo_.count(plots_[plot])>0)&&(histo_[plots_[plot]].count(idx)>0)){
	// check if previous plot also exists
	if(histo_[plots_[plot]].count(idx+1)>0){
	  histo_[plots_[plot]][idx]->Add((TH1F*)histo_[plots_[plot]][idx+1]->Clone());
	    if(verbose) std::cout << "add "+plots_[plot] << " plot for " << sampleLabel(idx) << " and " << sampleLabel(idx+1) << std::endl;
	    if(verbose) std::cout << "this new stacked plot contains now " <<  histo_[plots_[plot]][idx]->Integral(0, histo_[plots_[plot]][idx]->GetNbinsX()+1) << " events" << std::endl;
	}
      }
    }
  }
  if(verbose)  std::cout << std::endl;
  
  // ------------------------------------------------------------------------------------
  //    configure histograms
  // ------------------------------------------------------------------------------------
  // needs: plots_, histo_, xAxisLabel_
  if(verbose){
    std::cout << "x Axis labels: " << std::endl;
    // loop plots
    for(unsigned int plot=0; plot<Nplots; ++plot){
      std::cout << xAxisLabel_[plot] << " ";
    }
    std::cout << std::endl;
  }
  // loop samples
  for(unsigned int idx=kZMuMu; idx<=kData; ++idx){
    // loop plots
    for(unsigned int plot=0; plot<Nplots; ++plot){
      if((histo_.count(plots_[plot])>0)&&(histo_[plots_[plot]].count(idx)>0)) histogramStyle( *histo_[plots_[plot]][idx], idx, true );
    }
  }
  
  // ------------------------------------------------------------------------------------
  //    create one legend for all 1D histos
  // ------------------------------------------------------------------------------------
  int Nlegends=0;  
  TLegend *leg0 = new TLegend(0.05, 0.15, 1.05, 0.9);
  ++Nlegends;
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  //leg0->SetHeader("Kin. Fit (after selection)");
  // fill in contributing sample
  // loop samples
  for(unsigned int idx=kZMuMu; idx<=kData; ++idx){
    // check if sampe exists in at least one plot
    bool exit=false;
    // loop plots
    for(unsigned int plot=0; plot<Nplots; ++plot){
      // if found: add entry to legend
      if((histo_.count(plots_[plot])>0)&&(histo_[plots_[plot]].count(idx)>0)&&(!exit)){
	if(idx==kData) leg0->AddEntry(histo_[plots_[plot]][idx], sampleLabel(idx)+", "+lumi+" pb^{-1}", "PL");
	else leg0->AddEntry(histo_[plots_[plot]][idx], sampleLabel(idx), "F");
	exit=true;
      }
    }
  }
  
  // ------------------------------------------------------------------------------------
  //    create canvas
  // ------------------------------------------------------------------------------------
  std::vector<TCanvas*> MyCanvas;
    if(verbose) std::cout << std::endl << "#plots: " << Nplots  << std::endl;
    if(verbose) std::cout << std::endl << "#Canvas: " << Nplots << std::endl;
  // a) create canvas for all plots + legends
  for(unsigned int idx=0; idx<Nplots+Nlegends; idx++){
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ------------------------------------------------------------------------------------
  //    do the printing
  // ------------------------------------------------------------------------------------
  // a) for plots
  int canvasNumber=0;
  // loop plots
  for(unsigned int plot=0; plot<Nplots; ++plot){
    bool first=true;
    // open canvas and set titel corresponding to plotname in .root file
    MyCanvas[canvasNumber]->cd(0);
    MyCanvas[canvasNumber]->SetTitle(plots_[plot]);
    // loop samples
    for(unsigned int idx=kZMuMu; idx<=kData; ++idx){
      // a
	// check if plot is existing
	if((histo_.count(plots_[plot])>0)&&(histo_[plots_[plot]].count(idx)>0)){
	  if(verbose) std::cout << "plotting " << plots_[plot] << " from sample " << sampleLabel(idx) << " to canvas " << canvasNumber << " ( " << MyCanvas[canvasNumber]->GetTitle() << " )" << std::endl;
	  // axes style and drawing for first plot
	  if(first){
	    axesStyle(*histo_[plots_[plot]][idx], xAxisLabel_[plot], "events", 0, 1.2*histo_[plots_[plot]][idx]->GetMaximum());
	    // switch to log scale if desired
	    if(logY_[plot]!=0){
              histo_[plots_[plot]][idx]->SetMinimum(logY_[plot]);
	      MyCanvas[canvasNumber]->SetLogy();
	      if(verbose) std::cout<<"log scale for canvas:" << 
	                                         MyCanvas[canvasNumber]->GetTitle()<<std::endl;
	    }
	    histo_[plots_[plot]][idx]->Draw("");
	    histo_[plots_[plot]][42] = (TH1F*)(histo_[plots_[plot]][idx]->Clone());
	    
	  }
	  // draw other plots into same canvas
	  else if(idx!=kData) histo_[plots_[plot]][idx]->Draw("same");
	  else histo_[plots_[plot]][idx]->Draw("same P E X0");
	  first=false;
	}
	// redraw axis at the end
	if((histo_.count(plots_[plot])>0)&&(idx==kData)) histo_[plots_[plot]][42]->Draw("axis same");
    }
    // for 1D hists: next canvas
    if(histo_.count(plots_[plot])>0) ++canvasNumber;
  }
  // b) for legends
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("legend");
  leg0->Draw("");
  ++canvasNumber;
  
  // ------------------------------------------------------------------------------------
  // saving
  // ------------------------------------------------------------------------------------
  if(savePlots){
    // save all plots in one pdf
    MyCanvas[0]->Print(folderPlots+whichFile+lumi+"plots.pdf(", "pdf");
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(folderPlots+whichFile+lumi+"plots.pdf", "pdf");   
    }
    MyCanvas[MyCanvas.size()-1]->Print(folderPlots+whichFile+lumi+"plots.pdf)", "pdf");
    // save every plot as png and root
    for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
      MyCanvas[idx]->Print(folderPlots+((TString)(MyCanvas[idx]->GetTitle())).ReplaceAll("/","_")+".png");
      MyCanvas[idx]->Print(folderPlots+((TString)(MyCanvas[idx]->GetTitle())).ReplaceAll("/","_")+".root"); 
    }
  }
 }

}
