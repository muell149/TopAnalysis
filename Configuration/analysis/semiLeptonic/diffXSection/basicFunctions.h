#ifndef basicFunctions_h
#define basicFunctions_h

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
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

                 /*0:*/  /*1:*/  /*2:*/    /*3:*/    /*4:*/   /*5:*/    /*6:*/  /*7:*/  /*8,  9,  10*/ /* 11   ,  12     ,   13:  */
enum samples    {kSig  , kBkg  , kZjets  , kWjets  , kQCD   , kSTop   , kDiBos, kData , kWW, kWZ, kZZ, kSTops  , kSTopt  , kSToptW };
int color_ [] = {kRed+1, kRed-7, kAzure-2, kGreen-3, kYellow, kMagenta, 10    , kBlack, 10 , 10 , 10 , kMagenta, kMagenta, kMagenta};
int marker_[] = {20    , 22    , 29      , 23      , 21     , 27      , 28    , 20    , 28 , 28 , 28 , 27      , 27      , 27      };
enum systematicVariation {/* 0:*/sysNo          , /* 1:*/sysLumiUp       , /* 2:*/sysLumiDown       , /* 3:*/sysJESUp     , 
			  /* 4:*/sysJESDown     , /* 5:*/sysJERUp        , /* 6:*/sysJERDown        , /* 7:*/sysTopScaleUp, 
			  /* 8:*/sysTopScaleDown, /* 9:*/sysVBosonScaleUp, /*10:*/sysVBosonScaleDown, /*11:*/sysTopMatchUp, 
			  /*12:*/sysTopMatchDown, /*13:*/sysVBosonMatchUp, /*14:*/sysVBosonMatchDown, /*15:*/sysMuEffSFup , 
			  /*16:*/sysMuEffSFdown , /*17:*/sysISRFSRup     , /*18:*/sysISRFSRdown     , /*19:*/sysPileUp    ,
			  /*20:*/sysQCDup       , /*21:*/sysQCDdown };

double effSFAB(int sys=sysNo)
{
  // this function returns the muon eff SF 
  // as derived from Z->mumu tag and probe method
  // modified quantities: NONE
  // used functions: NONE
  // used enumerators: NONE
  // "sys": if sysMuEffSFup/sysMuEffSFdown is
  // chosen, the corresponding systematic shifted
  // SF is returned

  // combined single muon SF Run A+B from tag and probe
  double result = 0.964155;
  // errors for the derived SF
  double errorUp   = 0.03*result;
  double errorDown = 0.03*result;
  // return requestet SF
  if(sys==sysMuEffSFup  ) result+=errorUp;
  if(sys==sysMuEffSFdown) result-=errorDown;
  return result;
}

// BR correction for ttbar->lnuqq'bb'
double BRcorrectionSemileptonic = 0.985608;

void histogramStyle(TH1& hist, int sampleTyp, bool filled=true) 
{
  // this function configures the style of a TH1 histogram "hist"
  // using "sampleTyp" to identify the corresponding sample from
  // the enumerator samples definition and assign the corresponding
  // marker and color
  // modified quantities: hist
  // used functions: marker_, color_
  // used enumerators: samples
  // "filled": = 0: line only, =1: area under plot filled

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
  // this function configures the style of a TH2 histogram "hist"
  // modified quantities: hist
  // used functions: NONE
  // used enumerators: NONE
  // "titleHisto": set tite of the histo (drawn in upper left)
  // "titleX": title of the x-axis
  // "titleY": title of the y-axis

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
  // this function to reads and returns a double value 
  // from a specific line "line" of the .txt-like file "file"
  // modified quantities: NONE
  // used functions: NONE
  // used enumerators: NONE

  // define variables
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
  // this function does the standard style 
  // configuration for the TCanvas "canv"
  // modified quantities: canv
  // used functions: NONE
  // used enumerators: NONE

  canv.SetFillStyle   ( 4000 );
  canv.SetLeftMargin  ( 0.20 );
  canv.SetRightMargin ( 0.05 );
  canv.SetBottomMargin( 0.15 );
  canv.SetTopMargin   ( 0.05 );
}

void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2, float xLabelSize = 0.06)
{
  // this function configures the axis style of a TH1 histogram "hist"
  // modified quantities: hist
  // used functions: NONE
  // used enumerators: NONE
  // "titleX": title of the x-axis
  // "titleY": title of the y-axis
  // "yMin": minimum of the y axis
  // "yMax": maximum of the y axis
  // "yTitleSize": caption size of the y axis title
  // "yTitleOffset": offste of the y axis title
  // "xLabelSize": caption size of the y axis label

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
  // this function writes the content of "output"
  // into "file" which is of a type like .txt
  // "output" might be of type TString or double
  // modified quantities: file
  // used functions: NONE
  // used enumerators: NONE
  // "append": if false, "file" will be recreated and 
  // the existing "file" will be deleted

  // a) write into file
  if(!append){
    std::ofstream fout(file);
    fout << output << std::endl;
    fout.close();
  }
  // b) add output to the end of the file  
  if(append){
    std::ofstream fapp(file, ios::app);
    fapp << output << std::endl;;
    fapp.close();
  }
 }

int roundToInt(double value, bool roundDown=0)
{
  // function to round an double "value" 
  // to an int and return this one
  // modified quantities: NONE
  // used functions: NONE
  // used enumerators: NONE
  // "roundDown": choose if you always want to round down

  // create output
  int outputInt=0;
  // take care of negative numbers
  if(value<0){
    std::cout << "no negative numbers allowed in roundToInt" << std::endl;
    return 0;
  }
  // get number before the digit
  for(int x=0; value>x; ++x){
    outputInt=x;
  }
  // see if the number behind the digit is > 0.5
  if((roundDown==false)&&(value-outputInt) >=0.5) return (outputInt+1);
  // return result
  return outputInt;
}

TString getTStringFromInt(int i)
{
  // function to convert an int "i" to 
  // a TString and return this one
  // modified quantities: NONE
  // used functions: NONE
  // used enumerators: NONE
  char result[20];
  sprintf(result, "%i", i);
  return (TString)result;
}

TString sampleLabel(unsigned int sample)
{
  // this function returns the name of the entered MC process
  // corresponding to the enumerator entry "sample" as defined in samples
  // modified quantities: NONE
  // used functions: NONE
  // used enumerators: samples

  // create output
  TString MCprocess;
  // list all MC process/sample names
  if(sample==kSig    ) MCprocess="t#bar{t} (#mu prompt)";
  if(sample==kBkg    ) MCprocess="t#bar{t} other";
  if(sample==kSTop   ) MCprocess="single top";
  if(sample==kSToptW ) MCprocess="single top tW";
  if(sample==kSTops  ) MCprocess="single top s";
  if(sample==kSTopt  ) MCprocess="single top t";
  if(sample==kWjets  ) MCprocess="W+jets";
  if(sample==kZjets  ) MCprocess="Z+jets";
  if(sample==kDiBos  ) MCprocess="DiBoson";
  if(sample==kWW     ) MCprocess="WW";
  if(sample==kWZ     ) MCprocess="WZ";
  if(sample==kZZ     ) MCprocess="ZZ";
  if(sample==kQCD    ) MCprocess="QCD";
  if(sample==kData   ) MCprocess="2010 data";
  // return result
  return MCprocess;
}

TH1F* divideByBinwidth(TH1F* histo, bool calculateError=1)
{
  // function divides the #entries in every bin of the input plot "histo" 
  // by its binwidth and returns the result
  // the errors are recalculated if "calculateError"=1 is choosen
  // careful: not done for underflow/overflow
  // modified quantities: NONE
  // used functions: NONE
  // used enumerators: NONE

  // create output histo
  TH1F* outputHisto = (TH1F*)histo->Clone();
  // loop bins, excluding underflow and overflow
  for(int i=1; i<= histo->GetNbinsX(); i++){
    // recalculate error
    double error = (double)(histo->GetBinError(i)) / (double)(histo->GetBinWidth(i));
    // recalculate bin content
    outputHisto->SetBinContent(i, ( (double)(histo->GetBinContent(i))/(double)(histo->GetBinWidth(i)) )  );
    if(calculateError) outputHisto->SetBinError(i, error);
  }
  // return result
  return outputHisto;
 }

void DrawLabel(TString text, const double x1, const double y1, const double x2, const double y2, double textSize)
{
  // function to directly draw a label into the active canvas
  // the coordinates of the window are: "x1", "y1", "x2", "y2"
  // the label will contain the text "text" and the textsize is "textSize"
  // modified quantities: the active canvas
  // used functions: NONE
  // used enumerators: NONE

  TPaveLabel *label = new TPaveLabel(x1, y1, x2, y2, text, "br NDC");
  label->SetFillStyle(0);
  label->SetBorderSize(0);
  label->SetTextSize(textSize);
  label->SetTextAlign(12);
  label->Draw("same");
}

void scaleByFactor(TH1F*& histo, const double scaleValue)
{
  // function to scale the TH1F plot "histo" and its errors 
  // by an entered "scaleValue" correctly for each bin 
  // N'=N/L, sN'=sN/L
  // modified quantities: histo
  // used functions: NONE
  // used enumerators: NONE

  // scaling factor = 0?
  if(scaleValue==0) std::cout << "WARNING: scaling histogram by 0" << std::endl;
  // loop bins (including underflow and overflow)
  for(int bin=0; bin<=histo->GetNbinsX()+1; ++bin){
    double oldError = histo->GetBinError(bin);
    // scale bin value and error
    histo->SetBinContent(bin, histo->GetBinContent(bin)/scaleValue);
    histo->SetBinError  (bin, oldError                 /scaleValue);
  }
}

double lumiweight(unsigned int sample, double luminosity)
{
  // this function derives the lumiweight for every standard MC 
  // sample "sample" based on the theoretical cross section, the 
  // number of generated events and the chosen "luminosity"
  // Furthermore, the BR correction is considered for ttbar signal
  // NOTE: enter luminosity IN / pb!!!!
  // modified quantities: NONE
  // used functions: BRcorrectionSemileptonic
  // used enumerators: samples

  // a) check if input is valid
  // sample existing?
  if(sample>kSToptW){
    std::cout << "ERROR: invalid sample label for lumiweight calculation, no scaling will be done" << std::endl;
    return 1.;
  }
  // valid luminosity entered?
  if(luminosity<=0){
    std::cout << "ERROR: chosen luminosity for lumiweight calculation is <= 0, no scaling will be done" << std::endl;
    return 1.;
  }
  // b) define in/output for weight calculation
  double crossSection=1;
  double Nevents=0;
  double weight =0;

  // c) fill #events in sample and cross sections (in / pb)
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
  // d) calculate weight
  weight = luminosity / ( Nevents / crossSection );
  // for ttbar->lnu: BR correction
  if(sample==kSig) weight *= BRcorrectionSemileptonic;
  // return result
  return weight;
}

TString getStringEntry(const TString inputTString, unsigned int entry=42, const TString seperateBy="/")
{ 
  // this function devides "inputTString" using "seperateBy" 
  // as seperator and returns the "entry"-th element
  // 42: default, means last element after seperator
  // modified quantities: NONE
  // used functions: NONE
  // used enumerators: NONE
  char *path, *element;
  // enable output for debugging
  bool verbose=0;
  // save inputstring in char* path
  string inputString=(std::string)inputTString;
  path = new char [inputString.size()+1];
  strcpy (path, inputString.c_str());
  //  path = (char*)inputTString.Data();
  // get pointer element to elements of path using seperateBy as seperator
  element=strtok (path,(char*)(seperateBy.Data()));
  // get vector with splittet elements
  std::vector<TString> result_;
  if(verbose){
  std::cout << "input: " << inputTString << std::endl;
  std::cout << "seperator: " << seperateBy << std::endl;
  std::cout << "splitted in the following elements:" << std::endl;
  }
  while(element!=NULL){
    if(verbose) std::cout << element << std::endl;
    string output="";
    output=output+element;
    result_.push_back((TString)output);
    element=strtok(NULL,(char*)(seperateBy.Data()));
  }
  delete[] path;
  delete[] element;
  // default configuration: get last entry
  if(entry==42) entry = (result_.size());
  // get requestet element
  if(verbose) std::cout << "requested " << "element #" << entry << " of " << result_.size() << std::endl;
  TString result="";
  // check if element exists
  if(entry<=result_.size()) result=result_[entry-1];
  else{
    std::cout << "warning - the requested element (" << entry <<") does not exist" << std::endl;
    std::cout << "the string "  << inputTString << " with seperator " << seperateBy << " gives only " <<  result_.size() << "elements!" << std::endl;
  }
  if(verbose) std::cout << "will return: " <<  result_[entry-1] << std::endl;
  // return output
  return result_[entry-1];
}

TString TopFilename(unsigned int sample, unsigned int sys)
{
  // this function contains the basic convention for the MC 
  // .root files and returns the correct names for choosen sample "sample" 
  // and systematic variation "sys"
  // modified quantities: NONE
  // used functions: NONE
  // used enumerators: samples, systematicVariation 

  TString fileName ="muonDiffXSec";
  // name of data file is given directly in the .C file
  if(sample==kData) return ""; 
  // standard MC filenames
  if(sample==kSig   )fileName += "SigMadD6TFall10";
  if(sample==kBkg   )fileName += "BkgMadD6TFall10";
  if(sample==kWjets )fileName += "WjetsMadD6TFall10";
  if(sample==kZjets )fileName += "ZjetsMadD6TFall10";
  if(sample==kWW    )fileName += "WWPytia6Z2Fall10";
  if(sample==kWZ    )fileName += "WZPytia6Z2Fall10";
  if(sample==kZZ    )fileName += "ZZPytia6Z2Fall10";
  if(sample==kDiBos )fileName += "VVPytia6Z2Fall10";
  if(sample==kQCD   )fileName += "QCDPythiaZ2Fall10";
  if(sample==kSToptW)fileName += "SingleTopTWchannelMadZ2Fall10";
  if(sample==kSTops )fileName += "SingleTopSchannelMadZ2Fall10";
  if(sample==kSTopt )fileName += "SingleTopTchannelMadZ2Fall10";
  if(sample==kSTop  )fileName += "SingleTopMadD6TFall10";
  // take care of systematic variations
  // at the moment: no variation for QCD
  if(sample!=kQCD){
  // JES
  if(sys==sysJESUp  ) fileName += "JESup";
  if(sys==sysJESDown) fileName += "JESdown";
  // JER
  if(sys==sysJERUp  ) fileName += "JESup";
  if(sys==sysJERDown) fileName += "JERdown";
  // Pile Up
  if(sys==sysPileUp) fileName += "PileUp";
  // larger ISR/FSR (top only)
  if((sys==sysISRFSRup  )&&((sample==kSig)||(sample==kBkg))) fileName += "ISRFSRup";
  if((sys==sysISRFSRdown)&&((sample==kSig)||(sample==kBkg))) fileName += "ISRFSRdown";
  // Scale
  // a) top
  if((sys==sysTopScaleUp  )&&((sample==kSig)||(sample==kBkg))) fileName+="ScaleUp";
  if((sys==sysTopScaleDown)&&((sample==kSig)||(sample==kBkg))) fileName+="ScaleDown";
  // b) V+jets
  if((sys==sysVBosonScaleUp  )&&((sample==kWjets)||(sample==kZjets))) fileName+="ScaleUp";
  if((sys==sysVBosonScaleDown)&&((sample==kWjets)||(sample==kZjets))) fileName+="ScaleDown";
  // Match
  // a) top
  if((sys==sysTopMatchUp  )&&((sample==kSig)||(sample==kBkg))) fileName+="MatchUp";
  if((sys==sysTopMatchDown)&&((sample==kSig)||(sample==kBkg))) fileName+="MatchDown";
  // b) V+jets
  if((sys==sysVBosonMatchUp  )&&((sample==kWjets)||(sample==kZjets))) fileName+="MatchUp";
  if((sys==sysVBosonMatchDown)&&((sample==kWjets)||(sample==kZjets))) fileName+="MatchDown";
  }
  fileName+="PF.root";
  // return output
  return fileName;
}

void saveCanvas(const std::vector<TCanvas*> MyCanvas, const TString outputFolder, const TString pdfName)
{
  // introduce function that saves every single canvas in 
  // MyCanvas as ./outputFolder/CanvasTitle.eps and in addition 
  // all in one rootFile: ./outputFolder/pdfName.pdf
  // modified quantities: NONE
  // used functions: NONE
  // used enumerators: NONE

  // a) save all plots in one pdf
  MyCanvas[0]->Print(outputFolder+pdfName+".pdf(", "pdf");
  for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
    MyCanvas[idx]->Print(outputFolder+pdfName+".pdf", "pdf");   
  }
  MyCanvas[MyCanvas.size()-1]->Print(outputFolder+pdfName+".pdf)", "pdf");
  // b) save every plot as pdf with title as name
  for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
    MyCanvas[idx]->Print(outputFolder+(TString)(MyCanvas[idx]->GetTitle())+".eps");      
  }
}

std::map<unsigned int, TFile*> getStdTopAnalysisFiles( const TString inputFolder, const unsigned int systematicVariation, const TString dataFile)
{
  // this function returns a map containing all existing .root in "inputFolder"
  // corresponding to the choosen systematic variation "systematicVariation"
  // and the data file "dataFile" for which the direct path/name.root is needed 
  // The MC .root file names correspond to the standard names as defined in the 
  // function TopFilename
  // modified quantities: NONE
  // used functions: TopFilename
  // used enumerators: samples

  // open our standard analysis files and save them in a map
  std::map<unsigned int, TFile*> files_;
  // loop samples
  for(int sample = kSig; sample<=kSToptW; sample++){
    TString fileName;
    if(sample!=kData) fileName = inputFolder+"/"+TopFilename(sample, systematicVariation);
    if(sample==kData) fileName = dataFile; 
    // if file exists - save in map
    TFile* file = new (TFile)(fileName);
    if(!(file->IsZombie())) files_[sample]= file;
  }
  return files_;
}

void getAllPlots( std::map<unsigned int, TFile*> files_, const std::vector<TString> plotList_,  std::map< TString, std::map <unsigned int, TH1F*> >& histo_, std::map< TString, std::map <unsigned int, TH2F*> >& histo2_, const unsigned int N1Dplots, int& Nplots, const unsigned int verbose=0)
{
  // this function searches for every plot listed in "plotList_" in all files listed in "files_",
  // saves all 1D histos into "histo_" and all 2D histos into "histo2_"
  // modified quantities: "histo_", "histo2_", "Nplots"
  // used functions: sampleLabel
  // used enumerators: samples
  // "N1Dplots": the #1D plots is needed as input to destinguish between 1D and 2D plots
  // "Nplots": the total # of plots is calclated
  // "verbose": set detail level of output ( 0: no output, 1: std output 2: output for debugging )

  // loop plots
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){    
    // loop samples
    for(unsigned int sample=kSig; sample<=kSToptW; ++sample) {
      // check if file exists
      if(files_.count(sample)>0){
	// create plot container
	TH1* targetPlot;
	files_[sample]->GetObject(plotList_[plot], targetPlot);
	// Check if plot exits
	if(targetPlot){
	  // save plot in corresponding map
	  if(plot<N1Dplots ) histo_ [plotList_[plot]][sample] = (TH1F*)(files_[sample]->Get(plotList_[plot]));
	  if(plot>=N1Dplots) histo2_[plotList_[plot]][sample] = (TH2F*)(files_[sample]->Get(plotList_[plot]));
	  // count every existing 2D plot (every sample is counted separetly as it will be drawn into an own canvas)
	  if(plot>=N1Dplots) Nplots++;
	}
	// give warning if plot does not exist
	if((!targetPlot)&&(verbose>0)) std::cout << "can not find plot "+plotList_[plot] << " in file "+(TString)(files_[sample]->GetName()) << " - continue and neglect this plot" << std::endl;
      }
      // give warning if file does not exist
      if((files_.count(sample)==0)&&(plot==0)&&(verbose>0)) std::cout << "file for " << sampleLabel(sample) << " does not exist- continue and neglect this plots" << std::endl;
    }
    // count every existing type of 1D plots (neglect #samples here as they well be drawn into the same canvas)
    if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)) Nplots++;
  }
}

void scaleByLuminosity(const std::vector<TString> plotList_,  std::map< TString, std::map <unsigned int, TH1F*> >& histo_, std::map< TString, std::map <unsigned int, TH2F*> >& histo2_, const unsigned int N1Dplots, const double luminosity, const unsigned int verbose=1, const int systematicVariation=sysNo)
{
  // this function scales every histo in histo_ and histo2_ to the corresponding luminosity
  // Additionally the mu eff SF is applied
  // modified quantities: "histo_", "histo2_"
  // used functions: sampleLabel, effSFAB 
  // used enumerators: samples
  // "N1Dplots": the #1D plots is needed as input to destinguish between 1D and 2D plots
  // "verbose": set detail level of output ( 0: no output, 1: std output 2: output for debugging )
  // "luminosity": [/pb]
  // "systematicVariation": specify systematic variation corresponding to enum systematicVariation

  // loop samples
  for(unsigned int sample=kSig; sample<=kSToptW; ++sample) {
    // loop plots 
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      // a) 1D
      // check if 1D plot exists
      if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)){
	if(verbose>1) std::cout << std::endl << "plot: "+plotList_[plot] << " for sample " << sampleLabel(sample) << ":" << std::endl;
	if(verbose>1) std::cout << "#events before weighting: " << histo_[plotList_[plot]][sample]->Integral(0, histo_[plotList_[plot]][sample]->GetNbinsX()+1) << std::endl;
	// scale MC samples to same luminosity
	double weight = lumiweight(sample, luminosity);
	histo_[plotList_[plot]][sample]->Scale(weight);
	if(verbose>1) std::cout << "weight: " << weight << std::endl;
	if(verbose>1) std::cout << "#events after weighting: " << histo_[plotList_[plot]][sample]->Integral(0, histo_[plotList_[plot]][sample]->GetNbinsX()+1) << std::endl;
	// apply eff. SF for MC
	if(sample!=kData) histo_[plotList_[plot]][sample]->Scale(effSFAB(systematicVariation));
      }
      // b) 2D
      // check if 2D plot exists
      if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)){
	if(verbose>1) std::cout << std::endl << "plot: "+plotList_[plot] << " for sample " << sampleLabel(sample) << ":" << std::endl;
	if(verbose>1) std::cout << "#events before weighting: " << histo2_[plotList_[plot]][sample]->Integral(0, histo2_[plotList_[plot]][sample]->GetNbinsX()+1, 0, histo2_[plotList_[plot]][sample]->GetNbinsY()+1) << std::endl;
	// scale MC samples to same luminosity
	double weight = lumiweight(sample, luminosity);
	histo2_[plotList_[plot]][sample]->Scale(weight);
	if(verbose>1) std::cout << "weight: " << weight << std::endl;
	if(verbose>1) std::cout << "#events after weighting: " << histo2_[plotList_[plot]][sample]->Integral(0, histo2_[plotList_[plot]][sample]->GetNbinsX()+1, 0, histo2_[plotList_[plot]][sample]->GetNbinsY()+1) << std::endl;
	// apply eff. SF for MC
	if(sample!=kData) histo2_[plotList_[plot]][sample]->Scale(effSFAB(systematicVariation));
      }
    }
  }
}

void AddSingleTopAndDiBoson(const std::vector<TString> plotList_,  std::map< TString, std::map <unsigned int, TH1F*> >& histo_, std::map< TString, std::map <unsigned int, TH2F*> >& histo2_, const unsigned int N1Dplots, const unsigned int verbose=1)
{
  // this function creates plots for all diboson and all single 
  // top samples combined if the combined SingleTop and DiBoson 
  // samples do not exist as .root file. 
  // every plot in "plotList_" existing in each of the three 
  // sTop/ diBoson files will be combined and saved in the histo_ 
  // and histo2_ maps
  // NOTE: all plots from the samples are considered to be weighted 
  // to the same luminosity before 
  // modified quantities: "histo_", "histo2_"
  // used functions: sampleLabel
  // used enumerators: samples
  // "N1Dplots": the #1D plots is needed as input to destinguish between 1D and 2D plots
  // "verbose": set detail level of output ( 0: no output, 1: std output 2: output for debugging )

  // loop plots 
  std::cout << std::endl;
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    // a) 1D
    if((plot<N1Dplots)){
      // a.1) single Top
      // check that combined plot does not exist
      if(histo_[plotList_[plot]].count(kSTops)==0){
	// check that single plots exist
	if((histo_[plotList_[plot]].count(kSTops)>0)&&(histo_[plotList_[plot]].count(kSTopt)>0)&&(histo_[plotList_[plot]].count(kSToptW)>0)){
	  histo_[plotList_[plot]][kSTop]  =   (TH1F*)histo_[plotList_[plot]][kSTops ]->Clone();
	  histo_[plotList_[plot]][kSTop]->Add((TH1F*)histo_[plotList_[plot]][kSTopt ]->Clone());
	  histo_[plotList_[plot]][kSTop]->Add((TH1F*)histo_[plotList_[plot]][kSToptW]->Clone());
	  // print out information 
	  if(verbose>0) std::cout << "will add single Top Files" << std::endl;
	}	
	else if(verbose>0) std::cout << "plot " << plotList_[plot] << " does not exit in all single Top files" << std::endl;
      }
      else if(verbose>1) std::cout << "combined plot " << plotList_[plot] << " for single Top already exists" << std::endl;
      // a.2) DiBoson
      // check that combined plot does not exist
      if(histo_[plotList_[plot]].count(kDiBos)==0){
	// check that single plots exist
	if((histo_[plotList_[plot]].count(kWW)>0)&&(histo_[plotList_[plot]].count(kWZ)>0)&&(histo_[plotList_[plot]].count(kZZ)>0)){
	  histo_[plotList_[plot]][kDiBos]  =   (TH1F*)histo_[plotList_[plot]][kWW]->Clone();
	  histo_[plotList_[plot]][kDiBos]->Add((TH1F*)histo_[plotList_[plot]][kWZ]->Clone());
	  histo_[plotList_[plot]][kDiBos]->Add((TH1F*)histo_[plotList_[plot]][kZZ]->Clone());
	  // print out information 
	  if(verbose>0) std::cout << "will add DiBoson Files" << std::endl;
	}
	else if(verbose>0) std::cout << "plot " << plotList_[plot] << " does not exit in all DiBoson files" << std::endl;
      }
      else if(verbose>1) std::cout << "combined plot " << plotList_[plot] << " for Diboson already exists" << std::endl;
    }
    // b) 2D
    if((plot>=N1Dplots)){
      // b.1) single Top
      // check that combined plot does not exist
      if(histo_[plotList_[plot]].count(kSTops)==0){
	// check that single plots exist
	if((histo2_[plotList_[plot]].count(kSTops)>0)&&(histo2_[plotList_[plot]].count(kSTopt)>0)&&(histo2_[plotList_[plot]].count(kSToptW)>0)){
	  histo2_[plotList_[plot]][kSTop]  =   (TH2F*)histo2_[plotList_[plot]][kSTops ]->Clone();
	  histo2_[plotList_[plot]][kSTop]->Add((TH2F*)histo2_[plotList_[plot]][kSTopt ]->Clone());
	  histo2_[plotList_[plot]][kSTop]->Add((TH2F*)histo2_[plotList_[plot]][kSToptW]->Clone());
	  // print out information 
	  if(verbose>0) std::cout << "will add single Top Files" << std::endl;
	}
	else if(verbose>0) std::cout << "plot " << plotList_[plot] << " does not exit in all single Top files" << std::endl;
      }
      else if(verbose>1) std::cout << "combined plot " << plotList_[plot] << " for single Top already exists" << std::endl;
      // b.2) DiBoson
      // check that combined plot does not exist
      if(histo_[plotList_[plot]].count(kDiBos)==0){
	// check that single plots exist
	if((histo2_[plotList_[plot]].count(kWW)>0)&&(histo2_[plotList_[plot]].count(kWZ)>0)&&(histo2_[plotList_[plot]].count(kZZ)>0)){
	  histo2_[plotList_[plot]][kDiBos]  =   (TH2F*)histo2_[plotList_[plot]][kWW]->Clone();
	  histo2_[plotList_[plot]][kDiBos]->Add((TH2F*)histo2_[plotList_[plot]][kWZ]->Clone());
	  histo2_[plotList_[plot]][kDiBos]->Add((TH2F*)histo2_[plotList_[plot]][kZZ]->Clone());
	  // print out information 
	  if(verbose>0) std::cout << "will add DiBoson Files" << std::endl;
	}
	else if(verbose>0) std::cout << "plot " << plotList_[plot] << " does not exit in all DiBoson files" << std::endl;
      }
      else if(verbose>1) std::cout << "combined plot " << plotList_[plot] << " for Diboson already exists" << std::endl;
    }
  }
  std::cout << std::endl;
}
		       
void createStackPlot(const std::vector<TString> plotList_, std::map< TString, std::map <unsigned int, TH1F*> >& histo_, const unsigned int plot, const unsigned int N1Dplots, const unsigned int verbose=1)
{
  // this function will transform the histogram "plotList_"["plot"] 
  // within "histo_" into stacked plots. 
  // modified quantities: "histo_"
  // used functions: sampleLabel
  // used enumerators: samples
  // "verbose": set detail level of output ( 0: no output, 1: std output 2: output for debugging )
  // "N1Dplots": the #1D plots is needed as input to destinguish between 1D and 2D plots

  // loop samples backwards
  for(int sample=kDiBos-1; sample>=kSig; --sample){
    // check if plot exists
    if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)){
      // check if previous plot also exists
      if(histo_[plotList_[plot]].count(sample+1)>0){
	histo_[plotList_[plot]][sample]->Add((TH1F*)histo_[plotList_[plot]][sample+1]->Clone());
	if(verbose>1) std::cout << "add "+plotList_[plot] << " plot for " << sampleLabel(sample) << " and " << sampleLabel(sample+1) << std::endl;
	if(verbose>1) std::cout << "this new stacked plot contains now " <<  histo_[plotList_[plot]][sample]->Integral(0, histo_[plotList_[plot]][sample]->GetNbinsX()+1) << " events" << std::endl;
      }
    }
  }
}

#endif
