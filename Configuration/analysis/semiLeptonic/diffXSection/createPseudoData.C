
// ---------description---------------------------------------
// -----------------------------------------------------------
// this Makro creates pseudo data by taking the same plot from 
// various MC samples, weighting them concerning luminosity, 
// adding them and applies a poisson smearing for every point
// -----------------------------------------------------------
  
#include <vector>
#include <iostream>
#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TRandom3.h>

void smearing(TH1F& src, TH1F& data);
void loadingFiles();
void loadingHists(TString plot);
void combineFiles(float luminosity);
void poisson(TString directory, TString plot, TFile& outputfile);

std::vector<float> lumiweight_;
std::vector<TH1F*> hists_;
std::vector<TFile*> files_;

void createPseudoData(){
  // get the files
  loadingFiles(); 
  // definition of output file
  TFile f("./pseudoData7TeV50pb.root", "recreate");
  // list of plots you want to add and their directories within the input samples
  poisson("analyzeTightMuonCrossSection", "pt"        , f);
  poisson("analyzeTightMuonCrossSection", "eta"       , f);
  poisson("analyzeTightMuonCrossSection", "phi"       , f);
  poisson("analyzeTightMuonCrossSection", "ptMuPlus"  , f);
  poisson("analyzeTightMuonCrossSection", "etaMuPlus" , f);
  poisson("analyzeTightMuonCrossSection", "phiMuPlus" , f);
  poisson("analyzeTightMuonCrossSection", "ptMuMinus" , f);
  poisson("analyzeTightMuonCrossSection", "etaMuMinus", f);
  poisson("analyzeTightMuonCrossSection", "phiMuMinus", f);
  f.Close();
}

void poisson(TString directory, TString plot, TFile& outputfile)
{
  // get the histograms, erase existing at the beginning
  hists_.clear();
  loadingHists(directory+"/"+plot);  
  // define output plot
  TH1F* pseudoData=(TH1F*)hists_[0]->Clone(); pseudoData->Clear();
  // normalize to luminosity and add all samples
  combineFiles(50.0);
  // apply the poisson smearing COMMENT OUT IF YOU JUST WANT TO COMBINE PLOTS
  smearing(*hists_[files_.size()], *pseudoData);
  // write output to directory
  if(outputfile.GetDirectory(directory)==0){
    outputfile.mkdir(directory);
    outputfile.cd(directory);
  }
  pseudoData->Write(plot);  
}

void loadingFiles()
{
  // add all contributing samples here
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecSigMcAtNlo7TeV.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecWjetsMadgraph7TeV.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecBkgMcAtNlo7TeV.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecZjetsMadgraph7TeV.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecQCDPythia7TeV.root"     ) );
}

void loadingHists(TString plot)
{  
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    hists_ .push_back( (TH1F*)files_[idx]->Get(plot) );
  }
}

void smearing(TH1F& src, TH1F& data)
{
  TRandom3 rnd(0);
 for(int ibin=0; ibin<=src.GetNbinsX(); ++ibin){
   unsigned int evts=rnd.Poisson(src.GetBinContent(ibin));
   data.SetBinContent(ibin, evts);
   data.SetBinError(ibin, sqrt(evts));
 }
}

void combineFiles(float luminosity)
{
  // define weights concerning luminosity 
  // actually done for 50 pb-1 @ 7TeV with full statistic
  
  lumiweight_.push_back( (0.0083/50)*luminosity );
  lumiweight_.push_back( (0.1231/50)*luminosity );
  lumiweight_.push_back( (0.0083/50)*luminosity );
  lumiweight_.push_back( (0.1310/50)*luminosity );
  lumiweight_.push_back( (1.0286/50)*luminosity );

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    hists_ [idx]->Scale(lumiweight_[idx]);
  }

  hists_ .push_back(hists_[0]);

  for(unsigned int idx=1; idx<files_.size(); ++idx) {
    hists_[files_.size()]->Add(hists_[idx]);
  }

}
