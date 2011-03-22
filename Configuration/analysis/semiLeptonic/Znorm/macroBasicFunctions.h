#ifndef macroBasicFunctions_h
#define macroBasicFunctions_h

#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <iomanip>
#include <cmath>

#include <TH1F.h>
#include <TH2F.h>
#include <TGraphErrors.h>
#include <THStack.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMath.h>

#include <TLine.h>
#include <TPaveLabel.h>
#include <TStyle.h>
#include <typeinfo>
#include <TF1.h>
#include <TBox.h>

enum styles         {kZMuMu  , kZTauTau  , kTTbar  , kWjets  , kQCD   , kSTop   , kDiBos, kData , kWW, kWZ, kZZ, kSTops  , kSTopt  , kSToptW };
int color_ [ 14 ] = {kAzure-2, kAzure+8  , kRed+1  , kGreen-3, kYellow, kMagenta, 10    , kBlack, 10 , 10 , 10 , kMagenta, kMagenta, kMagenta};
int marker_[ 14 ] = {29      , 22        , 20      , 23      , 21     , 27      , 28    , 20    , 28 , 28 , 28 , 27      , 27      , 27      };

TString sys_        [] = {/* 0:*/"sysNo"          , /* 1:*/"sysLumiUp"       , /* 2:*/"sysLumiDown"       , /* 3:*/"sysJESUp"     , 
			  /* 4:*/"sysJESDown"     , /* 5:*/"sysJERUp"        , /* 6:*/"sysJERDown"        , /* 7:*/"sysTopScaleUp", 
			  /* 8:*/"sysTopScaleDown", /* 9:*/"sysVBosonScaleUp", /*10:*/"sysVBosonScaleDown", /*11:*/"sysTopMatchUp", 
			  /*12:*/"sysTopMatchDown", /*13:*/"sysVBosonMatchUp", /*14:*/"sysVBosonMatchDown", /*15:*/"sysMuEffSFup" , 
			  /*16:*/"sysMuEffSFdown" , /*17:*/"sysISRFSRup"     , /*18:*/"sysISRFSRdown"     , /*19:*/"sysPileUp"    ,
			  /*20:*/"sysQCDup"       , /*21:*/"sysQCDdown"      , /*22:*/"sysSTopUp"         , /*23:*/"sysSTopDown"  ,
			  /*24:*/"sysDiBosUp"     , /*25:*/"sysDiBosDown"    , /*26:*/"sysTTbarUp"        , /*27:*/"sysTTbarDown",
			  /*28:*/"sysWjetsUp"     , /*29:*/"sysWjetsDown"    , /*30:*/"sysZTauTauUp"      , /*31:*/"sysZTauTauDown",
			  /*32:*/"sysMuEffSFIsoIDup"  , /*33:*/"sysMuEffSFIsoIDdown", /*34:*/"sysMuEffSFTrigUp", /*35:*/"sysMuEffSFTrigDown",
			  /*36:*/"sysMuEffSFPreTrigUp", /*37:*/"sysMuEffSFPreTrigDown" };
unsigned int Nsys = sizeof(sys_)/sizeof(TString);

//-------------------------------------------------------------------------------------------
// constants
//-------------------------------------------------------------------------------------------

// array with ttbar cross section for all variations (order like TString [] sys_)
// ATTENTION: no pre-trigger eff. correction expected at this stage !!!
//            this will be handled during filling the map
double xSecTTbarInclArray_ [] = {/*0*/171.570, 164.829, 178.873, 148.596, 199.295, 173.121, 170.027, 180.750, 157.065, 202.927, /*10*/151.327, 173.872, 168.379, 184.558, 164.590, 166.465, 176.991, 178.815, 171.824, 171.153, /*20*/175.415, 167.725, 169.545, 173.595, 171.436, 171.704, 175.058, 168.082, 171.570, 171.570, /*30*/171.570, 171.570,
                                      171.054, 172.089, 171.217, 171.925, 171.054, 172.089};
// fill in map
std::map< TString, double > xSecTTbarIncl_;
double const effSFABPreTrigSingleMu = 0.995;
void fillXSecTTbarIncl_()
{
  for(unsigned int iSys=0; iSys<Nsys; iSys++){
    // ATTENTION: pre-trigger eff. correction here !!!
    xSecTTbarIncl_[sys_[iSys]] = xSecTTbarInclArray_[iSys] / effSFABPreTrigSingleMu;
  }
}

// ttbar cross section variations
// bin 2 (line 2 in file ./systematicVariations/topXSecInclusive2...)
// JES: +/- (|148.596 - 171.570|+|199.295 - 171.570|) / 2 = 25.349 = 14.775%
// JER: +/- (|173.121 - 171.570|+|170.027 - 171.570|) / 2 = 1.547 = 0.902%
// lumi: +/- (|164.829 - 171.570|+|178.873 - 171.570|) / 2 = 7.022 = 4.093%
// SF: +/- (|166.465 - 171.570|+|176.991 - 171.570|) / 2 = 5.263 = 3.068%
// TopMC: +/- |168.861-171.570| = 2.709 = 1.579%
// QCDestimation: +/- (|175.415 - 171.570|+|167.725 - 171.570|) / 2 = 3.845 = 2.241%
// top estimate (in W calc): +/- (|175.058 - 171.570|+|168.082 - 171.570|) / 2 = 3.488 = 2.033%
// single top estimation: +/- (|169.545 - 171.570|+|173.595 - 171.570|) / 2 = 2.025 = 1.180%
// DiBoson estimation: +/- (|171.436 - 171.570|+|171.704 - 171.570|) / 2 = 0.134 = 0.078%
// Z+jets estimation: +/- (|171.087 - 171.570|+|172.075 - 171.570|) / 2 = 0.494 = 0.288%
// PileUp: +/- |171.153-171.570| = 0.417 = 0.243%
// (Scale W/Z: +/- (|202.927 - 171.570|+|151.327 - 171.570|) / 2 = 25.800 = 15.038%)
// (Scale Top: +/- (|180.750 - 171.570|+|157.065 - 171.570|) / 2 = 11.843 = 6.902%)
// Scale: +/- sqrt(25.800^2 + 11.843^2) = 28.388 = 16.546%
// (Match W/Z: +/- (|184.558 - 171.570|+|164.590 - 171.570|) / 2 = 9.984 = 5.819%)
// (Match Top: +/- (|173.872 - 171.570|+|168.379 - 171.570|) / 2 = 2.747 = 1.601%)
// Match: +/- sqrt(9.984^2 + 2.747^2) = 10.355 = 6.035%
// (ISR/FSR Top: +/- (|178.815 - 171.570|+|171.824 - 171.570|) / 2 = 3.750 = 2.185%)
// total systematic error: +/- 40.481 = 23.594%
// total lumi error: +/- 7.022 = 4.093%
// combined error: sqrt( 15.064^2 + 40.481^2 + 7.022^2 ) = 43.760 = 25.506%



// luminosity in pb
double const luminosity_ = 35.9;
// relative lumiErr [% * 100]
double const lumiErr    = 0.04;
double luminosity = luminosity_;

// Efficiency scale factors for Run A and B combined (for single and di muon selection)
double const effSFABSingleMu = 0.964155;
//  Efficiency scale factor Iso/ID and abs. Error
double const effSFABIsoIDDiMu    = 0.990025;
double const effSFABIsoIDDiMuErr = 0.00597;
//  Efficiency scale factor Trigger and abs. Error
double const effSFABTrigDiMu    = 0.9962928;
double const effSFABTrigDiMuErr = 0.0006279;
//  Efficiency scale factor Pre-Trigger and abs. Error
double const effSFABPreTrigDiMu    = 0.990025;
double const effSFABPreTrigDiMuErr = 0.00597;
// Total efficiency SF incl. pre-trigger eff.
double const effSFABDiMu = 0.976515897;
// absolute error on effSFABDiMu
double const effSFABDiMuErr = 0.00835;
// This SF will be finally used for scaling. Set to 1 if no scaling of histos desired
double effSFAB = effSFABDiMu;
// ratio of acceptance between Powheg and Madgraph for central value
double effAccRatioPowOverMad = 1.039723051;

// Cross Section Parameters
// theoretical Z cross section in pb
double const xSecZTheo = 972.;
// top cross section from AN 2010-090 (pre-tagged without pre-trigger correction)
double const xSecTTbarInclusive    = 171.570;
// absolute uncertainty without lumi error (stat.+sys.)
double const xSecTTbarInclusiveErr = 43.19;
double const xSecTTbarVisible      = 9.612;


//-------------------------------------------------------------------------------------------
// systematic variations: lumi and SF
//-------------------------------------------------------------------------------------------

void applySystematicVariations(TString sys="sysNo")
{
  // recalculates the lumi and effSF in case of their systematic variations
  //if     (sys=="sysNo")                 return;
  if     (sys=="sysNo")                 effSFAB     = effSFABIsoIDDiMu *
                                                      effSFABTrigDiMu * effSFABPreTrigDiMu;
  else if(sys=="sysLumiUp")             luminosity  = luminosity_ * (1+lumiErr);
  else if(sys=="sysLumiDown")           luminosity  = luminosity_ * (1-lumiErr);
  else if(sys=="sysMuEffSFIsoIDup")     effSFAB     = (effSFABIsoIDDiMu + effSFABIsoIDDiMuErr) *
                                                       effSFABTrigDiMu * effSFABPreTrigDiMu;
  else if(sys=="sysMuEffSFIsoIDdown")   effSFAB     = (effSFABIsoIDDiMu - effSFABIsoIDDiMuErr) *
                                                       effSFABTrigDiMu * effSFABPreTrigDiMu;
  else if(sys=="sysMuEffSFTrigUp")      effSFAB     = effSFABIsoIDDiMu *
                                                     (effSFABTrigDiMu + effSFABTrigDiMuErr) * effSFABPreTrigDiMu;
  else if(sys=="sysMuEffSFTrigDown")    effSFAB     = effSFABIsoIDDiMu *
                                                     (effSFABTrigDiMu - effSFABTrigDiMuErr) * effSFABPreTrigDiMu;
  else if(sys=="sysMuEffSFPreTrigUp")   effSFAB     = effSFABIsoIDDiMu *
                                                      effSFABTrigDiMu * (effSFABPreTrigDiMu + effSFABPreTrigDiMuErr);
  else if(sys=="sysMuEffSFPreTrigDown") effSFAB     = effSFABIsoIDDiMu *
                                                      effSFABTrigDiMu * (effSFABPreTrigDiMu - effSFABPreTrigDiMuErr);
  else                                  effSFAB     = effSFABIsoIDDiMu *
                                                      effSFABTrigDiMu * effSFABPreTrigDiMu;
}

//-------------------------------------------------------------------------------------------
// "systematic variations: background scaling
//-------------------------------------------------------------------------------------------
void sysBgScaling(TH1F* histo, int sample, TString sys="sysNo")
{
  if(sample==kQCD){
    if(sys=="sysCDup")       histo->Scale(1.5);
    if(sys=="sysQCDdown")     histo->Scale(0.5);
  }
  if(sample==kSTops || sample==kSTopt || sample==kSToptW){
    if(sys=="sysSTopUp")      histo->Scale(1.3);
    if(sys=="sysSTopDown")    histo->Scale(0.7);
  }
  if(sample==kWW || sample==kWZ || sample==kZZ){
    if(sys=="sysDiBosUp")     histo->Scale(1.3);
    if(sys=="sysDiBosDown")   histo->Scale(0.7);
  }
  if(sample==kTTbar){
    if(sys=="sysTTbarUp")     histo->Scale(1 + xSecTTbarInclusiveErr / xSecTTbarInclusive);
    if(sys=="sysTTbarDown")   histo->Scale(1 - xSecTTbarInclusiveErr / xSecTTbarInclusive);
  }
  if(sample==kWjets){
    if(sys=="sysWjetsUp")     histo->Scale(1.1);
    if(sys=="sysWjetsDown")   histo->Scale(0.9);
  }
  if(sample==kZTauTau){
    if(sys=="sysZTauTauUp")   histo->Scale(1.1);
    if(sys=="sysZTauTauDown") histo->Scale(0.9);
  }
}

//-------------------------------------------------------------------------------------------
// folders etc.
//-------------------------------------------------------------------------------------------

  // folder of lumiweighted histos and efficiency histos
  TString folderResults = "./Analysis/results/";
  // save all plots into the following folder
  TString folderPlots = "./Analysis/plots/";
  TString whichFile = "analyzeMuonZNorm";
  // definition of a tab
  char const tab[]="\t";

//-------------------------------------------------------------------------------------------
// functions
//-------------------------------------------------------------------------------------------

void histogramStyle(TH1& hist, int sampleTyp, bool filled=true) 
{
  // function for default style configuration of 1D histograms
  hist.SetStats(kFALSE);
  hist.SetLineWidth(1);
  hist.SetLineStyle(1);
  if(sampleTyp==kData || !filled){
    if(!filled)hist.SetLineWidth(3);
    hist.SetLineColor(color_[sampleTyp]);
    hist.SetMarkerColor(color_[sampleTyp]);
    if(sampleTyp==kQCD){
      hist.SetLineColor(kYellow+1);
      hist.SetMarkerColor(kYellow+1);
    }
    if(sampleTyp==kDiBos){
      hist.SetLineColor(kGray);
      hist.SetMarkerColor(kGray);
    }
    hist.SetMarkerStyle(marker_[sampleTyp]);
    hist.SetMarkerSize(1.8);
    hist.SetFillStyle(0);
  }
  else{
    hist.SetLineColor(kBlack);
    hist.SetFillColor(color_[sampleTyp]);
    hist.SetFillStyle(1001);
  }
}

void histStyle2D(TH2& hist, const TString titleHisto, const TString titleX, const TString titleY) 
{
  // function for default style configuration of 2D histograms
  hist.SetTitle(titleHisto);
  if(titleX!="") hist.GetXaxis()->SetTitle(titleX);
  hist.GetXaxis()->SetTitleSize ( 0.05 );
  hist.GetXaxis()->SetLabelColor(  1   );
  hist.GetXaxis()->SetLabelFont ( 62   );
  hist.GetXaxis()->SetLabelSize ( 0.04 );
  hist.GetXaxis()->SetNdivisions(  505 );
  hist.GetXaxis()->CenterTitle  ( true );
  if(titleY!="") hist.GetYaxis()->SetTitle(titleY);
  hist.GetYaxis()->SetTitleSize  ( 0.05 );
  hist.GetYaxis()->SetTitleColor (    1 );
  hist.GetYaxis()->SetTitleOffset(  1.1 );
  hist.GetYaxis()->SetTitleFont  (   62 );
  hist.GetYaxis()->SetLabelSize  ( 0.04 );
  hist.GetYaxis()->SetLabelFont  (   62 );
  hist.GetYaxis()->SetNdivisions (  505 );
  hist.GetYaxis()->CenterTitle   ( true );
  hist.SetStats(kFALSE);
}

double readLineFromFile(int line, TString file="crossSectionCalculation.txt")
{
  // introduce function to read a double value drom a specific line of a file
  std::ifstream finDouble (file);
  std::string readIn;
  // check if file exists
  if (!finDouble){
    std::cout << "can not open file " << file << std::endl;
    return -1;
  }
  // loop lines of the file
  for(int l=1; !finDouble.eof(); ++l){
    // save line content in readIn
    getline(finDouble, readIn);
    // convert your chosen line into double and return it
    if(l==line) return atof(readIn.c_str()); 
  }
  // if line is not found
  std::cout << "can not find line" << line << std::endl;
  return -1.;  
}

void canvasStyle(TCanvas& canv)
{
  // function for default style configuration of TCanvas
  canv.SetFillStyle   ( 4000 );
  canv.SetLeftMargin  ( 0.20 );
  canv.SetRightMargin ( 0.05 );
  canv.SetBottomMargin( 0.15 );
  canv.SetTopMargin   ( 0.05 );
}

void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2, float xLabelSize = 0.06)
{
  // function for the configuration of axis of a TH1 histogram
  hist.SetTitle("");
  hist.GetXaxis()->SetTitle(titleX);
  //hist.GetXaxis()->CenterTitle();
  hist.GetXaxis()->SetTitleSize  ( 0.05);
  hist.GetXaxis()->SetTitleColor (    1);
  hist.GetXaxis()->SetTitleOffset(  1.1);
  hist.GetXaxis()->SetTitleFont  (   62);
  hist.GetXaxis()->SetLabelSize  ( xLabelSize);
  hist.GetXaxis()->SetLabelFont  (   62);
  hist.GetXaxis()->SetNdivisions (  505);
  hist.GetYaxis()->SetTitle(titleY);
  hist.GetYaxis()->SetTitleSize  ( yTitleSize );
  hist.GetYaxis()->SetTitleColor (    1);
  hist.GetYaxis()->SetTitleOffset(yTitleOffset);
  hist.GetYaxis()->SetTitleFont  (   62);
  hist.GetYaxis()->SetLabelSize  ( 0.05);
  hist.GetYaxis()->SetLabelFont  (   62);
  //hist.GetYaxis()->CenterTitle   ( true);
  if(yMin!=-123) hist.SetMinimum(yMin);
  if(yMax!=-123) hist.SetMaximum(yMax);
}

template <class T>
void writeToFile(T output, TString file, bool append)
{
  // introduce function to write in file
  // a) write into file
  if(!append){
    std::ofstream fout(file);
    fout << output << std::endl;
    fout.close();
  }
  // b) write to the end of the file  
  if(append){
    std::ofstream fapp(file, ios::app);
    fapp << output << std::endl;;
    fapp.close();
  }
 }

int roundToInt(double value, bool roundDown)
{
  // function to round an double to an int
  int result=0;
  // take care of negative numbers
  if(value<0){
    std::cout << "no negative numbers allowed in roundToInt" << std::endl;
    return 0;
  }
  // get [value]
  for(int x=0; value>x; ++x){
    result=x;
  }
  // see if rest is > 0.5
  if(roundDown==false&&(value-result) >=0.5) return (result+1);
  return result;
}

TString getTStringFromInt(int i)
{
  // function to convert an int to a TString
  char result[20];
  sprintf(result, "%i", i);
  return (TString)result;
}

TString sampleLabel(unsigned int sample)
{
  // based on the enumerator on top this function provides the corresponding sample name as TString
  TString result;
  if(sample==kZMuMu    ) result="Z/#gamma*#rightarrow#mu^{+}#mu^{-}";
  if(sample==kZTauTau    ) result="Z/#gamma*#rightarrow#tau^{+}#tau^{-}";
  if(sample==kSToptW ) result="single top tW";
  if(sample==kSTops  ) result="single top s";
  if(sample==kSTopt  ) result="single top t";
  if(sample==kSTop  )  result="Single-Top";
  if(sample==kWjets  ) result="W+jets";
  if(sample==kTTbar  ) result="t#bar{t}";
  if(sample==kDiBos  ) result="DiBoson";
  if(sample==kWW  )    result="WW";
  if(sample==kWZ  )    result="WZ";
  if(sample==kZZ  )    result="ZZ";
  if(sample==kQCD    ) result="QCD";
  if(sample==kData   ) result="2010 data";
  return result;
}

TString sampleEnum(unsigned int sample)
{
  // based on the enumerator on top this function provides the corresponding sample name as TString
  TString result;
  if(sample==kZMuMu    ) result="ZMuMu";
  if(sample==kZTauTau    ) result="ZTauTau";
  if(sample==kSToptW ) result="SToptW";
  if(sample==kSTops  ) result="STops";
  if(sample==kSTopt  ) result="STopt";
  if(sample==kSTop  )  result="STop";
  if(sample==kWjets  ) result="Wjets";
  if(sample==kTTbar  ) result="TTbar";
  if(sample==kDiBos  ) result="DiBos";
  if(sample==kWW  )    result="WW";
  if(sample==kWZ  )    result="WZ";
  if(sample==kZZ  )    result="ZZ";
  if(sample==kQCD    ) result="QCD";
  if(sample==kData   ) result="Data";
  return result;
}

TH1F* divideByBinwidth(TH1F* histo, bool calculateError)
{
  // divide entries in every bin by its binwidth
  // careful: not done for underflow/overflow
  TH1F* result = (TH1F*)histo->Clone();
  for(int i=1; i<= histo->GetNbinsX(); i++){
    double error = (double)(histo->GetBinError(i)) / (double)(histo->GetBinWidth(i));
    result->SetBinContent(i, ( (double)(histo->GetBinContent(i))/(double)(histo->GetBinWidth(i)) )  );
    if(calculateError) result->SetBinError(i, error);
  }
  return result;
 }

void DrawLabel(TString text, const double x1, const double y1, const double x2, const double y2, double textSize)
{
  // function to directly draw a label into the active canvas
  TPaveLabel *label = new TPaveLabel(x1, y1, x2, y2, text, "br NDC");
  label->SetFillStyle(0);
  label->SetBorderSize(0);
  label->SetTextSize(textSize);
  label->SetTextAlign(12);
  label->Draw("same");
}

void scaleByLumi(TH1F* histo, double lumiweight)
{
  // function to scale a TH1F and its errors correctly
  // for each bin N'=N/L, sN'=sN/L
  if(lumiweight==0){
    std::cout << "luminosity ==0 not allowed for scaling" << std::endl;
    return;
  }
  for(int bin=0; bin<=histo->GetNbinsX()+1; ++bin){
    histo->SetBinContent(bin, histo->GetBinContent(bin)/lumiweight);
    histo->SetBinError  (bin, histo->GetBinError  (bin)/lumiweight);
  }
}

double lumiweight(unsigned int sample, double luminosity, TString sys="sysNo")
{
  // this function derives the lumiweight for every standard MC based
  // on the theoretical cross section, the number of generated events 
  // and the chosen luminosity (IN / pb!!!!)
  // Attention: the same sample types have different Nevents for different systematic variations!

  // check if input is valid
  if(sample>kSToptW){
    std::cout << "ERROR: invalid sample label for lumiweight calculation" << std::endl;
    return 1.;
  }
  if(luminosity<=0){
    std::cout << "ERROR: chosen luminosity for lumiweight calculation is <= 0" << std::endl;
    return 1.;
  }
  // a) define in/output for weight calculation
  double crossSection=1;
  double Nevents=0;
  double weight =0;

  // b) fill #events in sample and cross sections (in / pb)
  // 2*DY->ll+jets MADGRAPH D6T Fall10
  if((sample==kZMuMu)||(sample==kZTauTau)){
    crossSection=3048.;
    if      (sys=="sysVBosonScaleUp"  )   Nevents = 1329028.;
    else if (sys=="sysVBosonScaleDown"  ) Nevents = 1436150.;
    else if (sys=="sysVBosonMatchUp"  )   Nevents = 1667367.;
    else if (sys=="sysVBosonMatchDown"  ) Nevents = 1662884.;
    else Nevents     =2543727.;
  }
  // W->lnu+jets MADGRAPH D6T Fall10
  if(sample==kWjets){
    crossSection=31314.;
    if      (sys=="sysVBosonScaleUp"  )   Nevents = 6118255.;
    else if (sys=="sysVBosonScaleDown"  ) Nevents = 4842219.;
    else if (sys=="sysVBosonMatchUp"  )   Nevents = 10370368.;
    else if (sys=="sysVBosonMatchDown"  ) Nevents = 2706986.;
    else Nevents     =14805546.;
  }
  // ttbar MADGRAPH D6T Fall10
  if(sample==kTTbar){
    crossSection=xSecTTbarInclusive; //NLO prediction: 157.5;
    if      (sys=="sysTopScaleUp"  )   Nevents = 1153236.;
    else if (sys=="sysTopScaleDown"  ) Nevents = 1098971.;
    else if (sys=="sysTopMatchUp"  )   Nevents = 1036492.;
    else if (sys=="sysTopMatchDown"  ) Nevents = 938005.;
    else Nevents     =1306182.;
  }
  // QCD PYTHIA6 Z2 Fall10 
  if(sample==kQCD){
    crossSection=296600000.*0.00028550; // generator crossSection * prefilter efficiency
    Nevents     =29504866.;
  }
  // single top->lnu (added singleTop, s,t,tW channel) MADGRAPH Z2 Fall10 
  if(sample==kSTop){
    crossSection=1.;         // this leads to a weight
    Nevents     =luminosity; // of 1.0 as kSTop is already weighted
  }
  if(sample==kSTops){
    crossSection=4.6*0.108*3; // correct theory XSec for leptonic decay only
    Nevents     =494967.;
  }
  if(sample==kSTopt){
    crossSection=64.6*0.108*3; // correct theory XSec for leptonic decay only
    Nevents     =484060.;
  }
  if(sample==kSToptW){
    crossSection=10.6;
    Nevents     =494961.;
  }
  // DiBoson (added diboson,WW,WZ,ZZ) PYTHIA6 Z2 Fall10
  if(sample==kDiBos){
    crossSection=1.;         // this leads to a weight
    Nevents     =luminosity; // of 1.0 as kDiBos is already weighted
  }
  if(sample==kWW){
    crossSection=43.0;
    Nevents     =2061760;
  }
  if(sample==kWZ){
    crossSection=18.2;
    Nevents     =2194752;
  }
  if(sample==kZZ){
    crossSection=5.9;
    Nevents     =2113368;
  }
  // Data 
  if(sample==kData){
    crossSection=1.;         // this leads to a weight
    Nevents     =luminosity; // of 1.0 as data needs no weight
  }
  
  // c) calculate weight
  weight = luminosity / ( Nevents / crossSection );
  return weight;
}

TString getNameAfterSlash(const TString inputTString)
{ 
  // this function returns the part after / of a given TString
  std::string path = (string)(inputTString);
  size_t separator = path.find_last_of("/");
  TString name = (TString)(path.substr(separator+1));
  return name;
}

TString replaceCharInTString(TString inputTString, char* s1, char* s2)
{
  return inputTString.ReplaceAll(s1, s2);
}

double make1BinEffHisto(TH1F*& effHisto, TString effHistoName, double numerator, double denominator, bool debug)
{
  // this function calculates the efficiency from numerator and denominator and stores it in a simple
  // 1-bin histo;
  // returns the efficiency as double
  // expects a histo pointer that has not been created with "new" before
  effHisto = new TH1F(effHistoName,effHistoName+";;Efficiency",1,0,1);
  double eff =-1;
  if (denominator>0 && numerator>=0) eff = numerator / denominator;
  else if (numerator==0 && denominator==0) eff=0;
  else std::cout<<"ERROR: Numerator ("<<numerator<<") or denominator ("<<denominator<<"<=0."<<std::endl;
  effHisto->SetBinContent(1, eff);
  
  if(debug) std::cout<<"Eff("<<effHistoName<<")="<<numerator<<"/"<<denominator<<"="<<eff<<std::endl;
  return eff;
}

TString getFilename(unsigned int sample, TString whichFile, TString sys="sysNo")
{
  // this function contains the basic convention for the MC 
  // .root files and returns the correct names for choosen sample "sample" 
  // and systematic variation "sys"
  // modified quantities: NONE
  // used functions: NONE
  // used enumerators: samples, systematicVariation 

  TString whichSample;
  // name of data file is given directly in the .C file
  if(sample==kData)    return "./Analysis/RunAandB/analyzeMuonZNorm_RunAandB.root"; 
  if(sample==kZMuMu)   whichSample= "DYD6TMuMu"    ;
  if(sample==kZTauTau) whichSample= "DYD6TTauTau"  ;
  if(sample==kWjets)   whichSample= "WLNuD6T"      ;
  if(sample==kTTbar)   whichSample= "ttbarMadD6TSG";
  if(sample==kWW)      whichSample= "WWPythia6Z2"  ;
  if(sample==kWZ)      whichSample= "WZPythia6Z2"  ;
  if(sample==kZZ)      whichSample= "ZZPythia6Z2"  ;
  if(sample==kQCD)     whichSample= "QCDPythiaZ2"  ;
  if(sample==kSToptW)  whichSample= "singleTopTWchannelZ2";
  if(sample==kSTops)   whichSample= "singleTopSchannelZ2" ;
  if(sample==kSTopt)   whichSample= "singleTopTchannelZ2" ;
  // take care of systematic variations
  // at the moment: no variation for QCD
  if(sample!=kQCD){
  // JES
  //if(sys=="sysJESUp"  ) whichSample += "JESup";
  //if(sys=="sysJESDown") whichSample += "JESdown";
  // JER
  //if(sys=="sysJERUp"  ) whichSample += "JERup";
  //if(sys=="sysJERDown") whichSample += "JERdown";
  // Pile Up
  //if(sys=="sysPileUp") whichSample += "PileUp";
  // larger ISR/FSR (top only)
  //if(sys=="sysISRFSRup"   && sample==kTTbar) whichSample += "ISRFSRup";
  //if(sys=="sysISRFSRdown" && sample==kTTbar) whichSample += "ISRFSRdown";
  // Scale
  // a) top
  if((sys=="sysTopScaleUp"  ) && sample==kTTbar) whichSample+="ScaleUp";
  if((sys=="sysTopScaleDown") && sample==kTTbar) whichSample+="ScaleDown";
  // b) V+jets
  if((sys=="sysVBosonScaleUp"  ) && (sample==kWjets || sample==kZMuMu || sample==kZTauTau )) whichSample+="ScaleUp";
  if((sys=="sysVBosonScaleDown") && (sample==kWjets || sample==kZMuMu || sample==kZTauTau )) whichSample+="ScaleDown";
  // Match
  // a) top
  if(sys=="sysTopMatchUp"   && sample==kTTbar) whichSample+="MatchingUp";
  if(sys=="sysTopMatchDown" && sample==kTTbar) whichSample+="MatchingDown";
  // b) V+jets
  if((sys=="sysVBosonMatchUp"  )&& (sample==kWjets || sample==kZMuMu || sample==kZTauTau )) whichSample+="MatchingUp";
  if((sys=="sysVBosonMatchDown")&& (sample==kWjets || sample==kZMuMu || sample==kZTauTau )) whichSample+="MatchingDown";
  }
  return "./Analysis/"+whichSample+"/res/"+whichFile+"_"+whichSample+".root";
}

  // luminosity to string
  TString lumi = getTStringFromInt(roundToInt(luminosity, false));




#endif
