#include "basicFunctions.h"

TCanvas* getRatio(TString plotName, int verbose, TString outputFile){
  // ============================
  //  Set Root Style
  // ============================

  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  TGaxis::SetMaxDigits(2);
  myStyle.cd();
  gROOT->SetStyle("HHStyle");
  
  // open file
  TFile* file = TFile::Open(outputFile, "READ");
  // dont associate new objects with file to be able to close it in the end
  gROOT->cd();
  // get canvas for chosen cross section
  TCanvas* canvas = (TCanvas*)(file->Get("finalXSec/"+plotName+"Norm")->Clone());
  // GET DATA: with final errors from canvas
  TGraphAsymmErrors* dataRaw  = (TGraphAsymmErrors*)canvas->GetPrimitive("dataTotalError");
  //TGraphAsymmErrors* dataStat = (TGraphAsymmErrors*)canvas->GetPrimitive("dataStatError");
  // GET DATA: create rebinned histo
  std::map< TString, std::vector<double> > binning_ = makeVariableBinning();
  int Nbins = std::abs(binning_[plotName][binning_[plotName].size()-1]-binning_[plotName][0])*10;
  if(verbose>1) std::cout << Nbins << std::endl;
  TH1F* datatemp= new TH1F("data"+plotName, "data"+plotName, Nbins, binning_[plotName][0], binning_[plotName][binning_[plotName].size()-1]);
  reBinTH1F(*datatemp, binning_[plotName], 0);
  // GET DATA: refill TGraphAsymmErrors to rebinned histo
  for(int bin=1; bin<=datatemp->GetNbinsX(); ++bin){
    if(verbose>1) std::cout << "bin: " << bin << std::endl;
    if(verbose>1) std::cout << dataRaw->GetY()[bin];
    datatemp->SetBinContent(bin, dataRaw->GetY()[bin]);
    double err=dataRaw->GetErrorYhigh(bin);
    if(err<dataRaw->GetErrorYlow(bin)) err=dataRaw->GetErrorYlow(bin);
    if(verbose>1) std::cout << " +- " << err << std::endl;
    datatemp->SetBinError(bin, err);
  }
  // GET DATA: delete empty bins
  TH1F* data=killEmptyBins((TH1F*)datatemp->Clone(), verbose);
  if(verbose>1){
    for(int bin=1; bin<=data->GetNbinsX(); ++bin){
      std::cout << "bin: " << bin << std::endl;
      std::cout << data->GetBinContent(bin) << " +- " << data->GetBinError(bin) << std::endl;
    }
  }

  // GET THEORY: binned curves from canvas
  TH1F* plotNNLO     = (TH1F*)canvas->GetPrimitive(plotName+"nnlo"   );
  TH1F* plotMadGraph = (TH1F*)canvas->GetPrimitive(plotName          );
  TH1F* plotmcatnlo  = (TH1F*)canvas->GetPrimitive(plotName+"MC@NLO2");
  if(!plotmcatnlo) plotmcatnlo  = (TH1F*)canvas->GetPrimitive(plotName+"MC@NLO");
  TH1F* plotpowheg   = (TH1F*)canvas->GetPrimitive(plotName+"POWHEG");
  std::vector<TH1F*>hist_;
  // GET THEORY: delete empty bins
  if(plotmcatnlo ) hist_.push_back( killEmptyBins(plotmcatnlo , verbose) );
  if(plotpowheg  ) hist_.push_back( killEmptyBins(plotpowheg  , verbose) );
  if(plotMadGraph) hist_.push_back( killEmptyBins(plotMadGraph, verbose) );
  if(plotNNLO    ) hist_.push_back( killEmptyBins(plotNNLO    , verbose) );
  
  // create ratio canvas
  std::vector<TCanvas*> plotCanvas_;
  double max= plotName.Contains("ttbarMass") ? 2.9 : 1.7;
  double min= plotName.Contains("ttbarMass") ? 0 : 0.3;
  plotCanvas_.push_back(drawFinalResultRatio(data, min, max, myStyle, 0, hist_, (TCanvas*)(canvas->Clone())));
  plotCanvas_[0]->Draw();
  plotCanvas_[0]->Update();
  // close file
  file->Close();
  // return
  return plotCanvas_[0];
}

void createTheoryDataRatios(bool extrapolate=true, bool hadron=false, int verbose=0){

  // list all variables you want to create a ratio for
  std::vector<TString> xSecVariables_;
  TString xSecVariables[] ={"topPt", "topY", "ttbarPt", "ttbarY", "ttbarMass", "lepPt", "lepEta", "bqPt", "bqEta"};
  xSecVariables_.insert( xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString));

  // get correct names
  TString PS = extrapolate ? "" : "PhaseSpace";
  TString LV="Parton";
  if(!extrapolate&&hadron) LV="Hadron";
  TString outputFolder="./diffXSecFromSignal/plots/combined/2011/xSec/";
  TString outputFile="diffXSecTopSemiLep"+LV+PS+".root";

  // loop variables
  for(unsigned int i=0; i<xSecVariables_.size(); ++i){
    TString variable=xSecVariables_[i];
    // create ratio canvas
    TCanvas*canv=getRatio(variable, verbose, outputFile);
    // save ratio plots
    if(canv){
      int initialIgnoreLevel=gErrorIgnoreLevel;
      if(verbose==0) gErrorIgnoreLevel=kWarning;
      canv->Print(outputFolder+"ratioFinalXSec"+variable+"NormCombined"+LV+PS+".eps");
      canv->Print(outputFolder+"ratioFinalXSec"+variable+"NormCombined"+LV+PS+".png");
      if(i==0)     canv->Print(outputFolder+"ratioFinalXSecNormCombined"+LV+PS+".pdf(");
      else if(i==(xSecVariables_.size()-1))canv->Print(outputFolder+"ratioFinalXSecNormCombined"+LV+PS+".pdf)");
      else canv->Print(outputFolder+"ratioFinalXSecNormCombined"+LV+PS+".pdf");
      gErrorIgnoreLevel=initialIgnoreLevel;
      saveToRootFile(outputFile, canv, true, verbose,"ratio/"+variable);
    }
    // delete ratio canvas
    delete canv;
  }
}