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

void poisson(const std::map< TString, std::map <unsigned int, TH1F*> > histo_, const std::vector<TString> plotList_, const std::string decayChannel, TFile& outputfile, const int luminosity, const unsigned int verbose=1, bool smear=1, bool useReweightedTop=0, double avReweight=1, bool useZprime=0, double zPrimeLumiWeight=1);

void createPseudoData(double luminosity= 1143.22, const std::string decayChannel="muon", bool zprime=false, bool useReweightedTop=true){
  // "verbose": set detail level of output ( 0: no output, 1: std output 2: output for debugging )
  int verbose=2;
  // "smear": say if you want to do a poisson smearing for each bin or just a combination for the different samples 
  bool smear=false;
  // "dataFile": absolute path of data file, used to define plots of interest
  TString dataFile= "";
  if(decayChannel.compare("electron")==0) dataFile="/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/analyzeDiffXData2011A_Elec_160404_167913_1fb_withVTXDistributions.root";
  else dataFile="/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/analyzeDiffXData2011A_Muon_160404_167913_1fb_withVTXDistributions.root";
  // "useReweightedTop": use parton level reweighted ttbar signal file in pseudo data?
  TString rewVar="ttbarMassUp";
  // "zprime": include additional Zprime in pseudo data?
  if(useReweightedTop) zprime=false;
  TString outNameExtension="";
  //  ---
  //     create container for histos and files
  //  ---
  std::map<unsigned int, TFile*> files_;
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, std::map <unsigned int, TH2F*> > histo2_;

  //  ---
  //     parton level reweighted top distribution
  //  ---
  // a) name and path of rootfile
  TString nameTtbarReweighted="/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/";
  if(decayChannel.compare("electron")==0) nameTtbarReweighted+="elecDiffXSec";
  else                                    nameTtbarReweighted+="muonDiffXSec";
  nameTtbarReweighted+="SigMadD6TSummer11Reweighted"+rewVar+"PF.root";
  if(useReweightedTop) outNameExtension="Reweighted"+rewVar;
  // b) get average weight of reweighting
  double avWeight=1;
  if(useReweightedTop){
    TFile* ttbarRewfile = new (TFile)(nameTtbarReweighted);
    TString weightPlot="eventWeightDileptonModelVariation/modelWeightSum";
    weightPlot.ReplaceAll("Up"  ,"");
    weightPlot.ReplaceAll("Down","");
    histo_["avWeight"][kSig] = (TH1F*)(ttbarRewfile->Get(weightPlot));
    avWeight=histo_ ["avWeight"][kSig]->GetBinContent(2)/histo_ ["avWeight"][kSig]->GetBinContent(1);
    histo_["avWeight"].erase(kSig);
    //std::cout << "histo ratio: " << avWeight << std::endl;
    TFile* sigfile = new (TFile)("/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/"+TopFilename(kSig, sysNo, decayChannel));
    TString partonPlot="analyzeTopPartonLevelKinematics/ttbarMass";
    histo_["parton"   ][kSig] = (TH1F*)(sigfile     ->Get(partonPlot));
    histo_["partonRew"][kSig] = (TH1F*)(ttbarRewfile->Get(partonPlot));
    double avWeight2  = histo_["partonRew"][kSig]->Integral(0, histo_["partonRew"][kSig]->GetNbinsX()+1);
    avWeight2        /= histo_["parton"   ][kSig]->Integral(0, histo_["parton"   ][kSig]->GetNbinsX()+1);
    //std::cout << "area ratio: "<< avWeight2 << std::endl;
    delete ttbarRewfile;
    delete sigfile;
  }

  //  ---
  //     Z prime 
  //  ---
  TString zprimeMass="750";
  TString nameZprime="/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun/";
  if(decayChannel.compare("electron")==0) nameZprime+="elec";
  else nameZprime+="muon";
  nameZprime+="DiffXSecZPrime_M"+zprimeMass+"_W"+zprimeMass+"0_MadSummer11PF.root";
  double zPrimeLumiWeight=1;
  if     (zprimeMass=="500") zPrimeLumiWeight=(10*16.2208794979645*luminosity)/232074;
  else if(zprimeMass=="750") zPrimeLumiWeight=(10*3.16951400706147*luminosity)/206525;
  if(zprime) outNameExtension="and"+zprimeMass+"GeVZprime";
  unsigned int kLast=kSAToptW;
  unsigned int kZprime=kSAToptW+1;
  if(zprime) kLast=kZprime;

  if(zprime&&zPrimeLumiWeight==1){
    exit(0);
    std::cout << "ERROR: chosen zprime weight is exactly 1!" << std::endl;
  }

  // -------------------------
  // !!! choose luminosity !!!
  // -------------------------
  TString lum = getTStringFromInt(roundToInt(luminosity));
  // -----------------------------------------
  // !!! add all contributing samples here !!!
  // -----------------------------------------
  TString inputFolder = "/afs/naf.desy.de/group/cms/scratch/tophh/TOP2011/110819_AnalysisRun";
  // save all default top analysis samples in files_
  files_ = getStdTopAnalysisFiles(inputFolder, sysNo, dataFile, decayChannel);
  // remove single Top (combined), DiBoson (combined) and data
  if(files_.count(kSTop )>0)files_.erase(kSTop );
  if(files_.count(kDiBos)>0)files_.erase(kDiBos);
  //if(files_.count(kData )>0)files_.erase(kData ); // data file needed for list of plots
  // remove combined QCD file for electron channel
  if(decayChannel.compare("electron")==0&&files_.count(kQCD)>0) files_.erase(kQCD);
  // add zprime
  if(zprime) files_[kZprime]=new (TFile)(nameZprime);
  // change ttbar signal file for reweighted distributions
  if(useReweightedTop) files_[kSig]=new (TFile)(nameTtbarReweighted);

  //  -----------------------------------------
  //     get list of all plots to be considered
  //  -----------------------------------------
  std::vector<TString> plotList_;
  TString currentFolder ="";
  TString currentPlot = "";
  if(verbose>0) std::cout << std::endl << "searching for all plots in file " << files_[kData]->GetName() << std::endl;
  // go to data file for getting plot names
  files_[kData]->cd();
  // loop objects in file
  TIter fileIterator(gDirectory->GetListOfKeys());
  if(verbose>2){
    std::cout << "looping objects in in ";
    gDirectory->pwd();
  }
  TKey *fileKey;
  int count=0;
  while( (fileKey = (TKey*)fileIterator()) ){
    ++count;
    if(verbose>2) std::cout << "folderObject #" << count;
    TObject *fileObject = fileKey->ReadObj(); 
    // check if object is a directory
    if(!(fileObject->InheritsFrom("TDirectory"))&&(verbose>2)) std::cout << " is no directory" << count << std::endl;
    if(fileObject->InheritsFrom("TDirectory")){
      currentFolder = (TString)fileObject->GetName();
      if(verbose>2) std::cout << " ("+currentFolder+")" << std::endl;
      // go to directory
      ((TDirectory*)fileObject)->cd();
      if(verbose>2){
	std::cout << "looping objects in in ";
	gDirectory->pwd();
      }
      // loop objects in directory
      //TList* folderList = gDirectory->GetListOfKeys();
      //TIter folderIterator=folderList->MakeIterator();
      TIter folderIterator(gDirectory->GetListOfKeys());
      TKey *folderKey;// = (TKey*)folderIterator();
      int count2=0;
      while( (folderKey = (TKey*)folderIterator()) ) {
	++count2;
	TObject *folderObject = folderKey->ReadObj(); 
	currentPlot = (TString)folderObject->GetName();
	if(verbose>2) std::cout << "plotObject #" << count2 << " ("+currentPlot+")" << std::endl;
	// check if object is a TH1 
	if(folderObject->InheritsFrom("TH1")){
	  if(verbose>2) std::cout << "inherits from TH1";
	  // check if TH2 and neglect because a simple 
	  // resmearing here is not possible
	  if((folderObject->InheritsFrom("TH2"))&&(verbose>2)) std::cout << " and from TH2" << std::endl;
	  else{
	    if(verbose>2) std::cout << " and NOT from TH2" << std::endl;
	    // add to list of plots
	    if(verbose>2) std::cout << "will be added to list of output plots" << std::endl;
	    plotList_.push_back(currentFolder+"/"+currentPlot);
	  }
	}
      }
    }
  }
  // close data file for getting plot names
  files_[kData]->Close();
  // remove data file from list of considered files
  if(files_.count(kData )>0)files_.erase(kData );
  // print list of files considered
  if(verbose>0){
    std::cout << std::endl << "the following files will be considered: " << std::endl;
    // loop files
    for(int sample = kSig; sample<=kLast; sample++){
      // check existence of folder in all existing files
      if(files_.count(sample)>0){
	std::cout << files_[sample]->GetName() << std::endl;
      }
    }
  }
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
  // a) for std analysis file
  getAllPlots(files_, plotList_, histo_, histo2_, N1Dplots, Nplots, verbose-1);
  std::cout << Nplots << " plots loaded from " << plotList_.size();
  std::cout << " requested" << std::endl << "empty plots are not counted" << std::endl;
  // b) for zprime
  if(zprime){ 
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      histo_[plotList_[plot]][kZprime] = (TH1F*)(files_[kZprime]->Get(plotList_[plot]));
    }
  }

  // ---------------------------------------
  // !!! definition of output file(name) !!!
  // ---------------------------------------
  TString outputfile="./"+(TString)decayChannel+"PseudoData"+lum+"pb"+outNameExtension+"7TeV.root";
  TFile* out = new TFile(outputfile, "recreate");
  if(verbose>0) std::cout << std::endl << "outputfile: " << outputfile << std::endl;
  poisson(histo_, plotList_, decayChannel, *out, luminosity, verbose, smear, useReweightedTop, avWeight, zprime, zPrimeLumiWeight);
  out->Close();
}

void poisson(std::map< TString, std::map <unsigned int, TH1F*> > histo_, std::vector<TString> plotList_, const std::string decayChannel, TFile& outputfile, int luminosity, const unsigned int verbose, bool smear, bool useReweightedTop, double avReweight, bool useZprime, double zPrimeLumiWeight){
  unsigned int kCombined=111;
  
  if(verbose>1){
    std::cout << "running function poisson" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "luminosity: " << luminosity << std::endl;
    std::cout << "decayChannel: " << decayChannel << std::endl;
    std::cout << "smear: " << smear << std::endl;
    std::cout << "useReweightedTop: " << useReweightedTop << std::endl;
    std::cout << "avReweight: " << avReweight << std::endl;
    std::cout << "useZprime: " << useZprime << std::endl;
    std::cout << "zPrimeLumiWeight: " << zPrimeLumiWeight << std::endl;
    sleep(5);
  }
  // upper bound for looping events: in/exclude zprime
  unsigned int kLast=kSAToptW;
  unsigned int kZprime=kSAToptW+1;
  if(useZprime) kLast=kZprime;

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
    for(int sample = kSig; sample<=kLast; sample++){
      // check if plot exists
      if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample))){
	// take care of non existing plots
	if(!(useZprime&&sample==kZprime&&plotList_[plot].Contains("PUControlDistributions"))){
	  // do lumiweighting
	  if     (useZprime       &&sample==kZprime) histo_[plotList_[plot]][sample]->Scale(zPrimeLumiWeight);
	  else histo_[plotList_[plot]][sample]->Scale(lumiweight(sample, luminosity, sysNo, decayChannel));
	  if(useReweightedTop&&sample==kSig   ) histo_[plotList_[plot]][sample]->Scale(1.0/avReweight);
	  // first subsample (should be ttbar signal)
	  // -> create histogram map entry
	  if(first){ 
	    histo_[plotList_[plot]][kCombined] = (TH1F*)(histo_[plotList_[plot]][sample]->Clone());
	    first=false;
	  }
	  // add other subsample
	  else histo_[plotList_[plot]][kCombined]->Add((TH1F*)(histo_[plotList_[plot]][sample]->Clone()),1.0);
	  if(verbose>1){ 
	    if(useZprime&&sample==kZprime) std::cout << "z prime, weight " << zPrimeLumiWeight << std::endl;
	    else if(useReweightedTop&&sample==kSig)  std::cout << "reweighted ttbar signal, weight " << 1.0/avReweight << std::endl;
	    else std::cout << sampleLabel(sample) << ", weight " << lumiweight(sample, luminosity, sysNo, decayChannel) << std::endl;
	  }
	}
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
      if(verbose>1) std::cout << "plot " << plotList_[plot] << std::endl;
      // do the poisson smearing
      if(smear){
	TRandom3 rnd(0);
	for(int ibin=0; ibin<=histo_[plotList_[plot]][kCombined]->GetNbinsX()+1; ++ibin){
	  int evts=histo_[plotList_[plot]][kCombined]->GetBinContent(ibin);
	  evts=rnd.Poisson(histo_[plotList_[plot]][kCombined]->GetBinContent(ibin));
	  histo_[plotList_[plot]][kCombined]->SetBinContent(ibin, evts);
	  histo_[plotList_[plot]][kCombined]->SetBinError(ibin, sqrt(evts));
	}
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

