#include "TROOT.h"
#include "TStyle.h"
#include <vector>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TMath.h"
#include "TCanvas.h"

double getSoB(TH1F* sig, TH1F* bkg, double probCut, TString opt);

void optimizeProbCut(TString optimize = "#frac{sig}{#sqrt{sig+bkg}}", TString lep = "both")
{
  // configure style
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);

  // set optimization parameter
  // TString optimize = "#frac{sig}{#sqrt{bkg}}"; // "#frac{sig}{#sqrt{sig+bkg}}"

  // read files
  TString path1 = "/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/";
  TString path2 = "/scratch/hh/current/cms/user/henderle/";
  std::vector<TFile*> files_;
  if(lep=="both" || lep=="muon")files_.push_back(new TFile(path2+"20120313T181125_naf_MuttbarSG/muonDiffXSecSigFall11PF.root"));
  if(lep=="both" || lep=="electron")  files_.push_back(new TFile(path2+"20120314T101158_naf_ElttbarSG/elecDiffXSecSigFall11PF.root"));
  if(lep=="both" || lep=="muon")  files_.push_back(new TFile(path1+"HighStatsSamples/muonDiffXSecBkgFall11PF.root"));
  if(lep=="both" || lep=="electron")  files_.push_back(new TFile(path1+"HighStatsSamples/elecDiffXSecBkgFall11PF.root"));

  // get trees
  vector<TTree*> trees_;
  float decayChannel;
  float prob;
  float qAssignment;
  float weight;
  for(UInt_t i = 0; i < files_.size(); i++){
    trees_.push_back((TTree*)files_[i]->Get("analyzeTopRecoKinematicsKinFitBeforeProbSel/tree"));
    trees_[i]->SetBranchAddress("decayChannel",&decayChannel);
    trees_[i]->SetBranchAddress("prob",&prob);
    trees_[i]->SetBranchAddress("qAssignment",&qAssignment);
    trees_[i]->SetBranchAddress("weight",&weight);
  }

  // initialize histograms
  TH1F* sigHisto = new TH1F("probHistSig","signal probability",1000000,0.,1.);
  TH1F* bkgHisto = new TH1F("probHistBkg","background probability",1000000,0.,1.);

  // fill histograms
  Long64_t nevent = 0;
  for(UInt_t i = 0; i < files_.size(); i++)
    {
      nevent = (Long64_t)trees_[i]->GetEntries();
      for(Long64_t ientry = 0; ientry < nevent; ++ientry){
	trees_[i]->GetEntry(ientry);
	if(qAssignment==0)sigHisto->Fill(prob,weight);
	else bkgHisto->Fill(prob,weight);
      }
    }

  // find optimal probability cut
  double goldSec     = (3.-sqrt(5.))/2.;
  double optimalProb = -1.;
  double optimalSoB  = -1.;
  double optimalEff  = -1.;
  double SoBLowProb  = 0.;
  double SoBHighProb = 0.;
  double lowProb     = 0.;
  double highProb    = 1.;
  double newLowProb  = goldSec;
  double newHighProb = 1 - goldSec;
  double sigEvents   = sigHisto->Integral();
  vector<double> probVec;
  vector<double> SoBVec;
  vector<double> SeffVec;

  // calculate some points for the plots
  for ( int i = 0 ; i < 100 ; i++ ) {
    probVec.push_back(i/100.);
    SoBVec.push_back(getSoB(sigHisto,bkgHisto,i/100.,optimize));
    SeffVec.push_back(sigHisto->Integral(sigHisto->FindBin(i/100.),sigHisto->GetNbinsX()+1)/sigEvents);
  }

  // golden section search for optimal cut value
  for ( int i = 0 ; i < 100 ; i++ ) {
    if( optimalProb!=newLowProb ){
      // calculate s/sqrt(s+b) for lowProb
      SoBLowProb = getSoB(sigHisto,bkgHisto,newLowProb,optimize);
      probVec.push_back(newLowProb);
      SoBVec.push_back(SoBLowProb);
      SeffVec.push_back(sigHisto->Integral(sigHisto->FindBin(newLowProb),sigHisto->GetNbinsX()+1)/sigEvents);
      cout << "newLowProb: " << newLowProb << " -> s/sqrt(s+b): " << SoBLowProb << endl;
    }
    if(optimalProb!=newHighProb){
      // calculate s/sqrt(s+b) for highProb
      SoBHighProb = getSoB(sigHisto,bkgHisto,newHighProb,optimize);
      probVec.push_back(newHighProb);
      SoBVec.push_back(SoBHighProb);
      SeffVec.push_back(sigHisto->Integral(sigHisto->FindBin(newHighProb),sigHisto->GetNbinsX()+1)/sigEvents);
      cout << "newHighProb: " << newHighProb << " -> s/sqrt(s+b): " << SoBHighProb << endl;
    }
    if(SoBLowProb>SoBHighProb){
      highProb=newHighProb;
      optimalProb=newLowProb;
      optimalSoB=SoBLowProb;
      newHighProb=newLowProb;
      optimalEff=sigHisto->Integral(sigHisto->FindBin(newLowProb),sigHisto->GetNbinsX()+1)/sigEvents;
      if(TMath::Abs(SoBLowProb-SoBHighProb)/(SoBLowProb+SoBHighProb)<0.0000001)break;
      SoBHighProb=SoBLowProb;
      newLowProb=lowProb+goldSec*(highProb-lowProb);
    } else {
      lowProb=newLowProb;
      optimalProb=newHighProb;
      optimalSoB=SoBHighProb;
      newLowProb=newHighProb;
      optimalEff=sigHisto->Integral(sigHisto->FindBin(newHighProb),sigHisto->GetNbinsX()+1)/sigEvents;
      if(TMath::Abs(SoBLowProb-SoBHighProb)/(SoBLowProb+SoBHighProb)<0.0000001)break;
      SoBLowProb=SoBHighProb;
      newHighProb=highProb-goldSec*(highProb-lowProb);
    }
  }
  cout << "Optimal probability cut at " << optimalProb << " -> signal efficiency: " << optimalEff << endl;

  // set up canvas
  TCanvas *canv = new TCanvas("canv","probability cut optimisation",10,10,1200,600);
  canv->Divide(2,1);
  canv->cd(1)->SetLeftMargin  (0.15);
  canv->cd(1)->SetRightMargin (0.03);
  canv->cd(1)->SetBottomMargin(0.10);
  canv->cd(1)->SetTopMargin   (0.05);
  canv->cd(2)->SetLeftMargin  (0.15);
  canv->cd(2)->SetRightMargin (0.03);
  canv->cd(2)->SetBottomMargin(0.10);
  canv->cd(2)->SetTopMargin   (0.05);

  // draw graph s/sqrt(s+b) or s/sqrt(+b) vs probability
  canv->cd(1);
  TGraph* optSoB = new TGraph((int)probVec.size(),&probVec.front(),&SoBVec.front());
  optSoB->SetMarkerStyle(20);
  sigHisto->SetMaximum(1.1*optimalSoB);
  sigHisto->GetXaxis()->SetTitle("probability");
  sigHisto->GetYaxis()->SetTitle(optimize);
  sigHisto->GetYaxis()->SetTitleOffset(1.65);
  sigHisto->DrawClone("axis");
  optSoB->Draw("p same");

  // draw graph signal efficiency vs probability
  canv->cd(2);
  TGraph* eff = new TGraph((int)probVec.size(),&probVec.front(),&SeffVec.front());
  eff->SetMarkerStyle(20);
  sigHisto->SetMaximum(1.);
  sigHisto->GetYaxis()->SetTitle("signal efficiency");
  sigHisto->Draw("axis");
  eff->Draw("p same");
}

// calculate s/sqrt(s+b) or s/sqrt(+b)
double getSoB(TH1F* sig, TH1F* bkg, double probCut, TString opt)
{
  double signal = sig->Integral(sig->FindBin(probCut),sig->GetNbinsX()+1);
  double backgr = bkg->Integral(sig->FindBin(probCut),sig->GetNbinsX()+1);
  double result = 0.;
  if(opt=="#frac{sig}{#sqrt{bkg}}")result = signal/TMath::Sqrt(backgr);
  if(opt=="#frac{sig}{#sqrt{sig+bkg}}")result = signal/TMath::Sqrt(signal+backgr);
  return result;
}
