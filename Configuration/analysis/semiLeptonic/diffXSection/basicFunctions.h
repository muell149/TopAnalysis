#ifndef basicFunctions_h
#define basicFunctions_h

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

#include <TLine.h>
#include <TPaveLabel.h>
#include <TStyle.h>
#include <typeinfo>
#include <TF1.h>
#include <TBox.h>

enum styles         {kSig  , kBkg  , kZjets  , kWjets  , kQCD   , kSTop   , kDiBos, kData , kWW, kWZ, kZZ, kSTops  , kSTopt  , kSToptW };
int color_ [ 14 ] = {kRed+1, kRed-7, kAzure-2, kGreen-3, kYellow, kMagenta, 10    , kBlack, 10 , 10 , 10 , kMagenta, kMagenta, kMagenta};
int marker_[ 14 ] = {20    , 22    , 29      , 23      , 21     , 27      , 28    , 20    , 28 , 28 , 28 , 27      , 27      , 27      };

double effSFAB = 0.98323995;

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
  if(sample==kSig    ) result="t#bar{t} (#mu prompt)";
  if(sample==kBkg    ) result="t#bar{t} other";
  if(sample==kSToptW ) result="single top tW";
  if(sample==kSTops  ) result="single top s";
  if(sample==kSTopt  ) result="single top t";
  if(sample==kWjets  ) result="W+jets";
  if(sample==kZjets  ) result="Z+jets";
  if(sample==kDiBos  ) result="DiBoson";
  if(sample==kQCD    ) result="QCD";
  if(sample==kData   ) result="2010 data";
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

double lumiweight(unsigned int sample, double luminosity)
{
  // this function derives the lumiweight for every standard MC based
  // on the theoretical cross section, the number of generated events 
  // and the chosen luminosity (IN / pb!!!!)

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
  // 2*ttbar MADGRAPH D6T Fall10
  if((sample==kSig)||(sample==kBkg)){
    crossSection=157.5;
    Nevents     =1306182.;
  }
  // W->lnu+jets MADGRAPH D6T Fall10
  if(sample==kWjets){
    crossSection=31314.;
    Nevents     =14805546.;
  }
  // DY->ll+jets MADGRAPH D6T Fall10
  if(sample==kZjets){
    crossSection=3048.;
    Nevents     =2543727.;
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



#endif
