
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

std::vector<float> lumiweight_;
std::vector<TH1F*> hists_;
std::vector<TFile*> files_;


void createPseudoData()
{

  // get the files
  loadingFiles(); 

  // get the histograms
  loadingHists("analyzeTightMuonCrossSection/pt");  

  // define output
  TH1F* pseudoData=(TH1F*)hists_[0]->Clone(); pseudoData->Clear();
  
  // normalize to luminosity and add all samples
  combineFiles(50.0);
  
  // apply the poisson smearing
  smearing(*hists_[files_.size()], *pseudoData);
  
  // write output
  TFile f("pseudoData7TeV50pb2.root", "recreate");  
  pseudoData->Write();
  
}


void loadingFiles()
{
  // add all contributing sampe here
  
  files_.push_back(new TFile("./diffXSecFromSignal/fullMCStatistics/diffXSecSigMcAtNlo7TeV.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal/fullMCStatistics/diffXSecBkgMcAtNlo7TeV.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal/fullMCStatistics/diffXSecWjetsMadgraph7.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal/fullMCStatistics/diffXSecZjetsMadgraph7.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal/fullMCStatistics/diffXSecQCDPythia7TeV.root"  ) );
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

void loadingHists(TString plot)
{  
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    hists_ .push_back( (TH1F*)files_[idx]->Get(plot) );
  }
}


void combineFiles(float luminosity)
{
  // define weights concerning luminosity 
  // actually done for 50 pb-1 @ 7TeV with full statistic
  
  lumiweight_.push_back( (0.0083/50)*luminosity );
  lumiweight_.push_back( (0.0083/50)*luminosity );
  lumiweight_.push_back( (0.1231/50)*luminosity );
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
