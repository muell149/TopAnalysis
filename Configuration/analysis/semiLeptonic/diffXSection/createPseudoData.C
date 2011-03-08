// ---------description----------------------------------------
// ------------------------------------------------------------
// this Makro creates pseudo data by taking the same plot from 
// various MC samples, weighting them concerning luminosity, 
// adding them and applies a poisson smearing for every point
// ------------------------------------------------------------
// adaptions are necessary within areas marked via !!! ... !!! 
// ------------------------------------------------------------

#include "basicFunctions.h"
#include <TFile.h>
#include <TRandom3.h>
#include <TKey.h>
#include <TDirectory.h>

void poisson(const std::map< TString, std::map <unsigned int, TH1F*> > histo_, const std::vector<TString> plotList_, TFile& outputfile, const int luminosity, const unsigned int verbose=1, bool smear=1);

void createPseudoData(double luminosity= 35.9){
  // "verbose": set detail level of output ( 0: no output, 1: std output 2: output for debugging )
  int verbose=0;
  // "smear": say if you want to do a poisson smearing for each bin or just a combination for the different samples 
  bool smear=true;
  //  ---
  //     create container for histos and files
  //  ---
  std::map<unsigned int, TFile*> files_;
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, std::map <unsigned int, TH2F*> > histo2_;
  // -------------------------
  // !!! choose luminosity !!!
  // -------------------------
  TString lum = getTStringFromInt((int)luminosity);
  // -----------------------------------------
  // !!! add all contributing samples here !!!
  // -----------------------------------------
  TString inputFolder = "./diffXSecFromSignal/analysisRootFilesWithKinFit";
  // save all default top analysis samples in files_
  files_ = getStdTopAnalysisFiles(inputFolder, sysNo, "no");
  // remove single Top (combined), DiBoson (combined) and data
  if(files_.count(kSTop )>0)files_.erase(kSTop );
  if(files_.count(kDiBos)>0)files_.erase(kDiBos);
  if(files_.count(kData )>0)files_.erase(kData );
  // print list of files considered
  if(verbose>0){
    std::cout << std::endl << "the following files will be considered: " << std::endl;
    // loop files
    for(int sample = kSig; sample<=kSToptW; sample++){
      // check existence of folder in all existing files
      if(files_.count(sample)>0){
	std::cout << files_[sample]->GetName() << std::endl;
      }
    }
  }
  //  -----------------------------------------
  //     get list of all plots to be considered
  //  -----------------------------------------
  std::vector<TString> plotList_;
  TString currentFolder ="";
  TString currentPlot = "";
  // search for the first file existing to get list of plots from
  unsigned int existingFile=111;
  for(unsigned int sample = kSig; sample<=kSToptW; ++sample){
    if((files_.count(sample)>0)&&(existingFile==111)) existingFile=sample;
  }    
  if(existingFile==111){
    std::cout << std::endl << "ERROR: no valid inputfile found" << std::endl;
    exit(0);
  }
  if(verbose>0) std::cout << std::endl << "searching for all plots in file " << files_[existingFile]->GetName() << std::endl;
  // go to existing file for getting plot names
  files_[existingFile]->cd();
  // loop objects in file
  TIter fileIterator(gDirectory->GetListOfKeys());
  if(verbose>1){
    std::cout << "looping objects in in ";
    gDirectory->pwd();
  }
  TKey *fileKey;
  int count=0;
  while( (fileKey = (TKey*)fileIterator()) ){
    ++count;
    if(verbose>1) std::cout << "folderObject #" << count;
    TObject *fileObject = fileKey->ReadObj(); 
    // check if object is a directory
    if(!(fileObject->InheritsFrom("TDirectory"))&&(verbose>1)) std::cout << " is no directory" << count << std::endl;
    if(fileObject->InheritsFrom("TDirectory")){
      currentFolder = (TString)fileObject->GetName();
      if(verbose>1) std::cout << " ("+currentFolder+")" << std::endl;
      // check existence of folder in all existing files
      bool folderExistsInAllFiles=true;
      // loop files
      for(int sample = kSig; sample<=kSToptW; sample++){
	// check existence of folder in all existing file
	if((files_.count(sample)>0)&&(files_[sample]->GetDirectory(currentFolder))==0){
	  folderExistsInAllFiles=false;
	    if(verbose>1){
	      std::cout << " does NOT exist in " << files_[sample]->GetName();
	      std::cout << " will be neglected" << std::endl;
	    }
	  break;
	}
      }
      // if existing in all files, continue
      if(folderExistsInAllFiles){
	if(verbose>1) std::cout << " exist in all input files" << std::endl;
	// go to directory
	((TDirectory*)fileObject)->cd();
	if(verbose>1){
	  std::cout << "looping objects in in ";
	  gDirectory->pwd();
	}
	// loop objects in directory
	TIter folderIterator(gDirectory->GetListOfKeys());
	TKey *folderKey = (TKey*)folderIterator();
	int count2=0;
	while( (folderKey = (TKey*)folderIterator()) ) {
	  ++count2;
	  TObject *folderObject = folderKey->ReadObj(); 
	  currentPlot = (TString)folderObject->GetName();
	  if(verbose>1) std::cout << "plotObject #" << count2 << " ("+currentPlot+")" << std::endl;
	  // check if object is a TH1 
	  if(folderObject->InheritsFrom("TH1")){
	    if(verbose>1) std::cout << "inherits from TH1";
	    // check if TH2 and neglect because a simple 
	    // resmearing here is not possible
	    if((folderObject->InheritsFrom("TH2"))&&(verbose>1)) std::cout << " and from TH2" << std::endl;
	    else{
	      if(verbose>1) std::cout << " and NOT from TH2" << std::endl;
	      // check if this plot exists in all files
	      bool plotExistsInAllFiles=true;
	      // loop files
	      for(int sample = kSig; sample<=kSToptW; sample++){
		// check existence of plot in all existing files
		if((files_.count(sample)>0)){
		  TH1* targetPlot;
		  files_[sample]->GetObject(currentFolder+"/"+currentPlot, targetPlot);
		  // if not existing in all files, neglect
		  if(!targetPlot){
		    plotExistsInAllFiles=false;
		      if(verbose>1){
			std::cout << " does NOT exist in " << files_[sample]->GetName();
			std::cout << " will be neglected" << std::endl;
		      }
		    break;
		  }
		}
	      }
	      // if existing in all files, add to list of plots
	      if(plotExistsInAllFiles){
		if(verbose>1) std::cout << "will be added to list of output plots" << std::endl;
		plotList_.push_back(currentFolder+"/"+currentPlot);
	      }
	    }
	  }
	}
      }
    }
  }
  // close existing file for getting plot names
  files_[existingFile]->Close(); 
  // print out the name of all plots
  if(verbose>0){
    std::cout << std::endl << "list of all plots to be considered: " << std::endl;
    // loop list of plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      std::cout << "\"" << plotList_[plot] << "\"" << std::endl;
    }
    std::cout << plotList_.size() << " plots in total" << std::endl;
  }
  // ---------------------------------------
  // !!! load all hists !!!
  // ---------------------------------------
  unsigned int N1Dplots=plotList_.size();
  int Nplots=0;
  std::cout << std::endl << "loading plots: " << std::endl;
  getAllPlots(files_, plotList_, histo_, histo2_, N1Dplots, Nplots, verbose);
  std::cout << Nplots << " plots loaded from " << plotList_.size();
  std::cout << " requested" << std::endl << "empty plots are not counted" << std::endl;
  // ---------------------------------------
  // !!! definition of output file(name) !!!
  // ---------------------------------------
  TString outputfile="./diffXSecFromSignal/analysisRootFilesWithKinFit/Fall10PseudoData7TeV"+lum+"pb.root";
  TFile* out = new TFile(outputfile, "recreate");
  if(verbose>0) std::cout << std::endl << "outputfile: " << outputfile << std::endl;
  poisson(histo_, plotList_, *out, luminosity, verbose, smear);
  out->Close();
}

void poisson(std::map< TString, std::map <unsigned int, TH1F*> > histo_, std::vector<TString> plotList_, TFile& outputfile, int luminosity, const unsigned int verbose, bool smear){
  unsigned int kCombined=111;
  // go to output file
  outputfile.cd();
  //  ---
  //     combine plot from all files   
  //  ---
  if(verbose>0) std::cout << "start to combine plots " << std::endl;
  // loop plots
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    if(verbose>1){
      std::cout << "plot " << plotList_[plot] << std::endl;
      std::cout << "considered samples: " << std::endl;
    }
    // indicate first plot existing in sample
    bool first=true;
    // loop samples
    for(int sample = kSig; sample<=kSToptW; sample++){
      // check if plot exists
      if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample))){
	// do lumiweighting
	histo_[plotList_[plot]][sample]->Scale(lumiweight(sample, luminosity));
	// add all plots
	if(first ) histo_[plotList_[plot]][kCombined]  =   (TH1F*)(histo_[plotList_[plot]][sample]->Clone());
	if(!first) histo_[plotList_[plot]][kCombined]->Add((TH1F*)(histo_[plotList_[plot]][sample]->Clone()));
	if(verbose>1) std::cout << sampleLabel(sample) << std::endl;
      }
    }
  }

  //  ---
  //     poisson smearing   
  //  ---
  if(verbose>0) std::cout << "start to do the poisson smearing plots " << std::endl;
  // loop plots
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    // check if plot exists
    if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(kCombined))){
      histo_[plotList_[plot]][kCombined];
      if(verbose>1) std::cout << "plot " << plotList_[plot] << std::endl;
      // do the poisson smearing
      TRandom3 rnd(0);
      for(int ibin=0; ibin<=histo_[plotList_[plot]][kCombined]->GetNbinsX()+1; ++ibin){
	int evts=histo_[plotList_[plot]][kCombined]->GetBinContent(ibin);
	if(smear) evts=rnd.Poisson(histo_[plotList_[plot]][kCombined]->GetBinContent(ibin));
	histo_[plotList_[plot]][kCombined]->SetBinContent(ibin, evts);
	histo_[plotList_[plot]][kCombined]->SetBinError(ibin, sqrt(evts));
      }
      // do the saving
      // use the same directory as in the input files
      TString directory=getStringEntry(plotList_[plot], 1);
      TString plotName=getStringEntry(plotList_[plot], 2);
      if(verbose>1) std::cout << "check existence of directory " << directory << std::endl;
      if((outputfile.GetDirectory(directory)!=0)&&(verbose>1)) std::cout << "already existing" << std::endl;
      if(outputfile.GetDirectory(directory)==0){
	if(verbose>1) std::cout << "not existing - will create it" << directory << std::endl;
	outputfile.mkdir(directory);
      }
      outputfile.cd(directory);
      if(verbose>1) std::cout << "save plot" << directory << std::endl;
      // save plot
      histo_[plotList_[plot]][kCombined]->Write(plotName);
    }
  }
}
