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

void smearing(TH1F& src, TH1F& data);
void loadingFiles();
void loadingHists(TString plot);
void combineFiles(double luminosity);
void poisson(TString directory, TString plot, int lumi, TFile& outputfile);

std::vector<float> lumiweight_;
std::vector<TH1F*> hists_;
std::vector<TFile*> files_;

void createPseudoData(){
  // -------------------------
  // !!! choose luminosity !!!
  // -------------------------
  int luminosity= 50;
  TString lum="50";
  // get the files
  loadingFiles(); 

  // ---------------------------------------
  // !!! definition of output file(name) !!!
  // ---------------------------------------
    TFile f("./diffXSecFromSignal/spring10Samples/recoAndGenFromPATtuplesWithSummer09JEC/spring10PseudoData7TeV"+lum+"pb.root", "recreate");

  // ---------------------------------------------------------
  // !!! list of plots you want to combine !!!
  // and their directories within the input samples
  // example: poisson("MyPlotFolder", "MyPlot", luminosity, f)
  // ---------------------------------------------------------
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

  poisson("analyzeTightMuonCrossSectionRecNjets4Btag", "pt"      , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4Btag", "eta"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4Btag", "phi"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4Btag", "ptPlus"  , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4Btag", "etaPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4Btag", "phiPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4Btag", "ptMinus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4Btag", "etaMinus", luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets4Btag", "phiMinus", luminosity, f);

  poisson("analyzeTightMuonCrossSectionRecNjets3Btag", "pt"      , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3Btag", "eta"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3Btag", "phi"     , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3Btag", "ptPlus"  , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3Btag", "etaPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3Btag", "phiPlus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3Btag", "ptMinus" , luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3Btag", "etaMinus", luminosity, f);
  poisson("analyzeTightMuonCrossSectionRecNjets3Btag", "phiMinus", luminosity, f);

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
  // -----------------------------------------
  // !!! add all contributing samples here !!!
  // -----------------------------------------

  TString whichSample = "/spring10Samples/recoAndGenFromPATtuplesWithSummer09JEC";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigNloSpring10.root"    ) );
//   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigMadSpring10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecWjetsMadSpring10.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgNloSpring10.root"    ) );
//   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgMadSpring10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecZjetsMadSpring10.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecQCDPythiaSpring10.root" ) );

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
   // !!! IF YOU JUST WANT TO COMBINE PLOTS !!!
   // CHANGE src.GetBinContent(ibin) TO 0.
   unsigned int evts=rnd.Poisson(src.GetBinContent(ibin));
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
  std::vector<double> lumiweight;  
  // 7 TeV Monte Carlo spring 10 samples
  // -----------------------------------

  lumiweight_.push_back(0.00831910/50.0*(double)luminosity);
//   lumiweight_.push_back(0.00556153/50.0*(double)luminosity);
  lumiweight_.push_back(0.13904207/50.0*(double)luminosity);
  lumiweight_.push_back(0.00831910/50.0*(double)luminosity);
//   lumiweight_.push_back(0.00556153/50.0*(double)luminosity);
  lumiweight_.push_back(0.14332841/50.0*(double)luminosity);
  lumiweight_.push_back(1.25483558/50.0*(double)luminosity);

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    hists_ [idx]->Scale(lumiweight_[idx]);
  }

  hists_ .push_back(hists_[0]);

  for(unsigned int idx=1; idx<files_.size(); ++idx) {
    hists_[files_.size()]->Add(hists_[idx]);
  }

}
