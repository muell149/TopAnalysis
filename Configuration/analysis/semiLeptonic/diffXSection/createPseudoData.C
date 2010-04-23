
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
void combineFiles(double luminosity);
void poisson(TString directory, TString plot, int lumi, TFile& outputfile);

std::vector<float> lumiweight_;
std::vector<TH1F*> hists_;
std::vector<TFile*> files_;

void createPseudoData(){
  // !!! choose luminosity !!!
  int luminosity= 50;
  // get the files
  loadingFiles(); 
  // definition of output file
  TFile f("./pseudoData7TeV"+(TString)luminosity+"pb.root", "recreate");
  // list of plots you want to add and their directories within the input samples
  poisson("analyzeTightMuonCrossSectionRecNjets1", "pt"      , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets1", "eta"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets1", "phi"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets1", "ptPlus"  , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets1", "etaPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets1", "phiPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets1", "ptMinus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets1", "etaMinus", luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets1", "phiMinus", luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets2", "pt"      , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets2", "eta"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets2", "phi"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets2", "ptPlus"  , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets2", "etaPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets2", "phiPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets2", "ptMinus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets2", "etaMinus", luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets2", "phiMinus", luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3", "pt"      , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3", "eta"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3", "phi"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3", "ptPlus"  , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3", "etaPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3", "phiPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3", "ptMinus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3", "etaMinus", luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3", "phiMinus", luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4", "pt"      , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4", "eta"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4", "phi"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4", "ptPlus"  , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4", "etaPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4", "phiPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4", "ptMinus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4", "etaMinus", luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4", "phiMinus", luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecBtag", "pt"      , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecBtag", "eta"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecBtag", "phi"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecBtag", "ptPlus"  , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecBtag", "etaPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecBtag", "phiPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecBtag", "ptMinus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecBtag", "etaMinus", luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecBtag", "phiMinus", luminosity, f);
  //  poisson("analyzeTightMuonCrossSectionRecNjets1", "muonPt_"   , luminosity, f);
  //  poisson("analyzeTightMuonCrossSectionRecNjets2", "muonPt_"   , luminosity, f);
  //  poisson("analyzeTightMuonCrossSectionRecNjets3", "muonPt_"   , luminosity, f);
  //  poisson("analyzeTightMuonCrossSectionRecNjets4", "muonPt_"   , luminosity, f);
  //  poisson("analyzeTightMuonCrossSectionRecBtag",   "muonPt_"   , luminosity, f);

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
   // CHANGE src.GetBinContent(ibin) TO 0. IF YOU JUST WANT TO COMBINE PLOTS
   unsigned int evts=rnd.Poisson(src.GetBinContent(ibin));
   data.SetBinContent(ibin, evts);
   data.SetBinError(ibin, sqrt(evts));
 }
}

void combineFiles(double luminosity)
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
