#ifndef styleHelper_h
#define styleHelper_h

#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <iomanip>
#include <cmath>

#include <TH1F.h>
#include <TH2F.h>
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

enum styles              {kSig,   kBkg,   kZjets,   kWjets,   kQCD,    kData,  kLepJets, kAllMC, kABCD, kGenSig, kGenBkg, kGenW};
int color_      [ 11 ] = {kRed+1, kRed-7, kAzure-2, kGreen-3, kYellow, kBlack, kRed,     kBlack, kBlack};
int markerStyle_[ 11 ] = {20,     22,     29,       23,       21,      20,     23,       23,     22,   };

void histogramStyle(TH1& hist, int sampleTyp, bool filled=true) 
{
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
    hist.SetMarkerStyle(markerStyle_[sampleTyp]);
    hist.SetMarkerSize(1.8);
    hist.SetFillStyle(0);
  }
  else{
    hist.SetLineColor(kBlack);
    hist.SetFillColor(color_[sampleTyp]);
    hist.SetFillStyle(1001);
  }
}

double readLineFromFile(int line, TString file="crossSectionCalculation.txt"){
  // introduce function to read a double value drom a specific line of a file
  std::ifstream finDouble (file);
  std::string readIn;
  // check if file exists
  if (!finDouble){
    std::cout << "can not open file" << std::endl;
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
  std::cout << "can not find line" << std::endl;
  return -1.;  
}
  
double getMaxValue(TH1& histo, const TString variable = "", bool systematics = false, const TString plot = "", const int jetMultiplicity = 6){
  // ---
  //    determine the maximum value of bin content + combined error
  // ---
  // the following variations are considered: JES +/- 10%, efficiencies +/- 5%, 
  // ttbar MC-model( MG / NLO ), QCD BKG estimation: +/- 10%, luminosity: +/- 10%
  // the calculation is based on the values saved within the .txt files 
  //-----------------------------------------------------------------------------
  // create jet multiplicity indicator
  std::vector<TString> Njets_;
  TString jets[ 9 ] = { ", Njets1", ", Njets2", ", Njets3", ", Njets4", ", Njets4Btag", ", Njets3Btag", " [Njets]", "", ""};
  Njets_.insert( Njets_.begin(), jets, jets + 9 );
  // get line where value is saved
  int line=2;
  // get firstBin, lastBin and binRange(needed to skip between different jet multiplicities)
  int firstBin=1;
  int lastBin=histo.GetNbinsX(); 
  if(variable=="pt" ) firstBin=2;
  //if(variable=="eta") lastBin=4;
  //if(variable=="Njets"){
  //  firstBin=1;
  //  lastBin=4;
  //}
  if(variable=="1") firstBin=lastBin=1;
  if(variable=="2") firstBin=lastBin=2;
  int binRange=lastBin-firstBin+2;
  // consider chosen jet multiplicity
  if(jetMultiplicity<=5) line +=jetMultiplicity*binRange;
  // calculation for each bin
  int count=-1;
  double maxValue = 0.;
  for(int bin=firstBin; bin<=lastBin; ++bin){
    ++count;
    if((variable=="Njets")&&(bin>firstBin)) ++count;
    double value = 0.;
    double statError = histo.GetBinError(bin);
    if(systematics){
      // load values for all variations                
      double std     = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdQCDestimationStdWjetsEstimationStd.txt" );
      double lumiUp  = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiUpEffStdQCDestimationStdWjetsEstimationStd.txt"      );
      double lumiDown= readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiDownEffStdQCDestimationStdWjetsEstimationStd.txt"    );
      double MG      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdQCDestimationStdWjetsEstimationStd.txt" );
      double JESUp   = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCJES11LumiNominalEffStdQCDestimationStdWjetsEstimationStd.txt");
      double JESDown = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCJES09LumiNominalEffStdQCDestimationStdWjetsEstimationStd.txt");
      double EffUp   = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffUpQCDestimationStdWjetsEstimationStd.txt"  );
      double EffDown = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffDownQCDestimationStdWjetsEstimationStd.txt");
      double QCDUp   = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdQCDestimationUpWjetsEstimationStd.txt"  );
      double QCDDown = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdQCDestimationDownWjetsEstimationStd.txt");
      double WUp     = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdQCDestimationStdWjetsEstimationUp.txt"  );
      double WDown   = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdQCDestimationStdWjetsEstimationDown.txt");
      // calculate and print out all systematic errors
      double JESError  = ( std::abs(JESUp-std ) + std::abs(JESDown-std ) ) / 2.0;
      double LumiError = ( std::abs(lumiUp-std) + std::abs(lumiDown-std) ) / 2.0;
      double EffError  = ( std::abs(EffUp-std ) + std::abs(EffDown-std ) ) / 2.0;
      double TopMCError= std::abs(MG-std);
      double QCDError=   ( std::abs(QCDUp-std ) + std::abs(QCDDown-std ) ) / 2.0;
      double WError=   ( std::abs(WUp-std ) + std::abs(WDown-std ) ) / 2.0;
      // calculate the combined systematic error
      double sysError=sqrt(JESError*JESError+LumiError*LumiError+TopMCError*TopMCError+EffError*EffError+QCDError*QCDError+WError*WError);
      // combine systematic and statistic error, add bin content and compare with other bins
      double combinedError = sqrt(statError*statError+sysError*sysError);
      value = histo.GetBinContent(bin)+combinedError;
    }
    else value = histo.GetBinContent(bin)+statError;
    if(value>maxValue)maxValue=value;
  }
  return maxValue;
}

#endif
