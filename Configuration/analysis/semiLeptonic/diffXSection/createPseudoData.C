// ---------description----------------------------------------
// ------------------------------------------------------------
// this Makro creates pseudo data by taking the same plot from 
// various MC samples, weighting them concerning luminosity, 
// adding them and applies a poisson smearing for every point
// ------------------------------------------------------------
// adaptions are necessary within areas marked via !!! ... !!! 
// ------------------------------------------------------------

#include <vector>
#include <iostream>
#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TRandom3.h>
#include <TKey.h>
#include <TDirectory.h>

void smearing(TH1F& src, TH1F& data);
void loadingFiles(TString jetType);
void loadingHists(TString plot);
void combineFiles(double luminosity);
void poisson(TString directory, TString plot, int lumi, TFile& outputfile);
TString getTStringFromInt(int i);
bool checkExistence(TString folder);

std::vector<TH1F*> hists_;
std::vector<TFile*> files_;

void createPseudoData(double luminosity= 50.0, TString jetType = "PF"){
  // -------------------------
  // !!! choose luminosity !!!
  // -------------------------
  TString lum = getTStringFromInt((int)luminosity);
  // get the files
  loadingFiles(jetType); 

  // ---------------------------------------
  // !!! definition of output file(name) !!!
  // ---------------------------------------
  TFile f("./diffXSecFromSignal/spring10Samples/spring10SelV2Sync/spring10PseudoData7TeV"+lum+"pb.root", "recreate");
  // ---------------------------------------------------------
  // !!! list of plots you want to combine !!!
  // and their directories within the input samples
  // example: addAndWeight("MyPlotFolder", "MyPlot", luminosity, f)
  // ---------------------------------------------------------
  TString folder ="";
  TString plot = "";
  // go to file
  files_[0]->cd();
  // loop objects in file
  TIter fileIterator(gDirectory->GetListOfKeys());
  TKey *fileKey;
  while( (fileKey = (TKey*)fileIterator()) ){
    TObject *fileObject = fileKey->ReadObj(); 
    // check if object is a directory
    if(fileObject->InheritsFrom("TDirectory")){
      folder = (TString)fileObject->GetName();
      std::cout << std::endl << " - folder: " << folder;
      // go to directory
      ((TDirectory*)fileObject)->cd();
      // loop objects in directory
      TIter folderIterator(gDirectory->GetListOfKeys());
      TKey *folderKey;
      // check if folder exists in all files
      if(checkExistence(folder)){
	folderKey = (TKey*)folderIterator();
	while( (folderKey = (TKey*)folderIterator()) ) {
	  TObject *folderObject = folderKey->ReadObj(); 
	  // check if object is a TH1 or TH2
	  if( (folderObject->InheritsFrom("TH1")) ){
	    plot = folderObject->GetName();
	    poisson(folder, plot, luminosity, f);
	  }
	}
      }
    }
  }
  files_[0]->Close(); 
  // close rootfile
  f.Close();
}

void poisson(TString directory, TString plot, int lumi, TFile& outputfile)
{
  // get the histograms, erase existing at the beginning
  hists_.clear();
  loadingHists(directory+"/"+plot);
  // define output plot
  TH1F* pseudoData=(TH1F*)hists_[0]->Clone(); pseudoData->Clear();
  // normalize to luminosity and add all samples
  combineFiles((double)lumi);
  // apply the poisson smearing 
  smearing(*hists_[files_.size()], *pseudoData);
  // write output to directory
  if(outputfile.GetDirectory(directory)==0){
    outputfile.mkdir(directory);
    outputfile.cd(directory);
  }
  pseudoData->Write(plot);
  std::cout << " " << plot;
}


void loadingFiles(TString jetType)
{
  // -----------------------------------------
  // !!! add all contributing samples here !!!
  // -----------------------------------------

  TString whichSample = "/analysisRootFiles";
  files_.clear();
  //files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecSigNloFall10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecSigMadD6TFall10"+jetType+".root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecWjetsMadD6TFall10"+jetType+".root"  ) );
  //files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecBkgNloFall10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecBkgMadD6TFall10"+jetType+".root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecZjetsMadD6TFall10"+jetType+".root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecQCDPythiaZ2Fall10"+jetType+".root" ) );

}

void loadingHists(TString plot)
{  
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    hists_ .push_back( (TH1F*)files_[idx]->Get(plot) );
  }
}

bool checkExistence(TString folder)
{
  bool value = true;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    if(files_[idx]->GetDirectory(folder)==0){
      value = false;
    }
  }
  if(value) std::cout << " (exists in all files)" << std::endl << "   plots: ";
  else  std::cout << " (NOT existing in all files - not added!)";
  return value;
}

void smearing(TH1F& src, TH1F& data)
{
  TRandom3 rnd(0);
  for(int ibin=0; ibin<=src.GetNbinsX()+1; ++ibin){
   // !!! IF YOU JUST WANT TO COMBINE PLOTS !!!
   // CHANGE rnd.Poisson(src.GetBinContent(ibin)) TO src.GetBinContent(ibin)
   // unsigned int evts=rnd.Poisson(src.GetBinContent(ibin));
    int evts=src.GetBinContent(ibin);
    data.SetBinContent(ibin, evts);
    data.SetBinError(ibin, sqrt(evts));
  }
}

void combineFiles(double luminosity)
{
  // --------------------------------------------
  // !!! define weights concerning luminosity !!!
  // --------------------------------------------
  // done for "luminosity" pb-1 @ 7TeV
  std::vector<double> lumiweight_;  
  // 7 TeV Monte Carlo spring 10 samples
  // -----------------------------------

  //lumiweight_.push_back(0.00831910/50.0*(double)luminosity);
  lumiweight_.push_back(0.006029022/50.0*(double)luminosity);
  lumiweight_.push_back(0.105750913/50.0*(double)luminosity);
  //lumiweight_.push_back(0.00831910/50.0*(double)luminosity);
  lumiweight_.push_back(0.006029022/50.0*(double)luminosity);
  lumiweight_.push_back(0.059912090/50.0*(double)luminosity);
  lumiweight_.push_back(0.143500567/50.0*(double)luminosity);

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    hists_ [idx]->Scale(lumiweight_[idx]);
  }

  hists_ .push_back(hists_[0]);

  for(unsigned int idx=1; idx<files_.size(); ++idx) {
    hists_[files_.size()]->Add(hists_[idx]);
  }

}

TString getTStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return (TString)result;
}
