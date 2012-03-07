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
#include <math.h>
#include <algorithm>

#include <TROOT.h>
#include <TSystem.h>

#include <TH1F.h>
#include <TH2F.h>
#include <TGraphErrors.h>
#include <THStack.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TKey.h>
#include <TGraphAsymmErrors.h>
#include <TString.h>

#include <TLine.h>
#include <TBox.h>
#include <TPaveLabel.h>
#include <TPaveText.h>
#include <TLatex.h>
#include <TStyle.h>
#include <typeinfo>
#include <TF1.h>
#include <TBox.h>
#include <TGaxis.h>
#include <TError.h>
#include <TMath.h>

#include "HHStyle.h"

#ifdef DILEPTON_MACRO
namespace semileptonic {
#endif

                   /*0:*/    /*1:*/    /*2:*/    /*3:*/    
  enum samples    {kSig    , kBkg    , kZjets  , kWjets  , 
		   /*4:*/    /*5:*/    /*6:*/    /*7:*/  
		   kQCD    , kSTop   , kDiBos  , kData,   
		   /*8*/     /*9*/     /*10*/    /*11*/    /*12*/    /*13*/
		   kQCDEM1 , kQCDEM2 , kQCDEM3 , kQCDBCE1, kQCDBCE2, kQCDBCE3,  
		   /*14*/    /*15*/    /*16*/
		   kWW     , kWZ     , kZZ     , 
		   /*17*/    /*18*/    /*19*/    /*20*/    /*21*/    /*22*/
		   kSTops  , kSATops , kSTopt  , kSATopt , kSToptW , kSAToptW };

  int color_ [] =  {kRed+1 , kRed-7  , kAzure-2, kGreen-3, 
		   kYellow , kMagenta, 10      , kBlack  , 
		   kYellow , kYellow , kYellow , kYellow , kYellow , kYellow ,
		   10      , 10      , 10      , 
		   kMagenta, kMagenta, kMagenta, kMagenta, kMagenta, kMagenta };

  int marker_[] = {20, 22, 29, 23, 
		   21, 27, 28, 20, 
		   21, 21, 21, 21, 21, 21,
		   28, 28, 28,
		   27, 27, 27, 27, 27, 27};

  enum systematicVariation { /* 0:*/ sysNo,
			     /* 1:*/ sysLumiUp,                  /* 2:*/ sysLumiDown,                
			     /* 3:*/ sysPUUp,                    /* 4:*/ sysPUDown,                  
			     /* 5:*/ sysJESUp,                   /* 6:*/ sysJESDown,                 
			     /* 7:*/ sysJERUp,                   /* 8:*/ sysJERDown,                 
			     /* 9:*/ sysTrigEffSFNormUp,         /*10:*/ sysTrigEffSFNormDown,        
			     /*11:*/ sysTriggerEffSFShapeUpEta,  /*12:*/ sysTriggerEffSFShapeDownEta,
			     /*13:*/ sysTriggerEffSFShapeUpPt,   /*14:*/ sysTriggerEffSFShapeDownPt,  
			     //      sysTriggerEffSFShapeUpPt40,         sysTriggerEffSFShapeDownPt40,  
			     /*15:*/ sysMuEffSFUp,               /*16:*/ sysMuEffSFDown, 
			     // old: sysBtagSFUp,                        sysBtagSFDown,  
			     //      sysBtagSFShapeUpPt100,              sysBtagSFShapeDownPt100,
			     //      sysBtagSFShapeUpEta1p2,             sysBtagSFShapeDownEta1p2,
			     /*17:*/ sysBtagSFShapeUpPt65,       /*18:*/ sysBtagSFShapeDownPt65,
			     /*19:*/ sysBtagSFShapeUpEta0p7,     /*20:*/ sysBtagSFShapeDownEta0p7,
			     /*21:*/ sysMisTagSFUp,              /*22:*/ sysMisTagSFDown,
			     /*23:*/ sysTopScaleUp,              /*24:*/ sysTopScaleDown,            
			     /*25:*/ sysVBosonScaleUp,           /*26:*/ sysVBosonScaleDown,          
			     /*27:*/ sysSingleTopScaleUp,        /*28:*/ sysSingleTopScaleDown,     
			     /*29:*/ sysTopMatchUp,              /*20:*/ sysTopMatchDown,            
			     /*31:*/ sysVBosonMatchUp,           /*32:*/ sysVBosonMatchDown,         
			     /*33:*/ sysTopMassUp,               /*34:*/ sysTopMassDown,            
			     /*35:*/ sysQCDUp,                   /*36:*/ sysQCDDown,                 
			     /*37:*/ sysSTopUp,                  /*38:*/ sysSTopDown,               
			     /*39:*/ sysDiBosUp,                 /*40:*/ sysDiBosDown,              
			     /*41:*/ sysPDFUp,                   /*42:*/ sysPDFDown,
			     /*43:*/ sysHadUp,                   /*44:*/ sysHadDown,      
			     /*45:*/ sysShapeUp,                 /*46:*/ sysShapeDown,
			     /*47:*/ ENDOFSYSENUM};

  double ttbarCrossSection=164.4;                                // combined 2011 CMS XSec
  double ttbarCrossSectionError=sqrt(2.8*2.8+11.9*11.9+7.4*7.4); // combined 2011 CMS XSec error 
                                                                 // --> should contain luminosity error
                                                                 // --> for MC error bands: luminosity error is subtracted in analyzeTopDiffXSecMonitoring.C

  double SF_TopMassUncertainty=0.9/3.0; // scale factor for top mass uncertainty
                                        // --> world average is presently known at +/-0.9 GeV (arXiv:1107.5255v3 [hep-ex])
                                        // --> systematic samples are varied by +/-3.0 GeV 
                                        // --> linearily rescale uncertainty on top mass in combineTopDiffXSecUncertainties.C

  double constHadUncertainty   = 0.050; // relative uncertainty // outdated and only used as placeholder for bquark quantities
  double globalLumiUncertainty = 0.045; // relative uncertainty

  TString sysLabel(unsigned int sys)
  {
    // this function returns a TString that corresponds
    // to the systematic variation "sys" of the enumerator "systematicVariation"
    // modified quantities: none
    // used functions: none
    // used enumerators: none (label correspond to systematicVariation)

    switch (sys)
    {
      case sysNo                       : return "sysNo";
      case sysLumiUp                   : return "sysLumiUp";
      case sysLumiDown                 : return "sysLumiDown";                
      case sysPUUp                     : return "sysPUUp";                  
      case sysPUDown                   : return "sysPUDown";                  
      case sysJESUp                    : return "sysJESUp";
      case sysJESDown                  : return "sysJESDown";
      case sysJERUp                    : return "sysJERUp";                 
      case sysJERDown                  : return "sysJERDown";                
      case sysTrigEffSFNormUp          : return "sysTrigEffSFNormUp";
      case sysTrigEffSFNormDown        : return "sysTrigEffSFNormDown";
      case sysTriggerEffSFShapeUpEta   : return "sysTriggerEffSFShapeUpEta";
      case sysTriggerEffSFShapeDownEta : return "sysTriggerEffSFShapeDownEta";
      case sysTriggerEffSFShapeUpPt    : return "sysTriggerEffSFShapeUpPt";
      case sysTriggerEffSFShapeDownPt  : return "sysTriggerEffSFShapeDownPt"; 
   // case sysTriggerEffSFShapeUpPt40  : return "sysTriggerEffSFShapeUpPt40";
   // case sysTriggerEffSFShapeDownPt40: return "sysTriggerEffSFShapeDownPt40";  
      case sysMuEffSFUp                : return "sysMuEffSFUp";            
      case sysMuEffSFDown              : return "sysMuEffSFDown";
//old case sysBtagSFUp                 : return "sysBtagSFUp";
//old case sysBtagSFDown               : return "sysBtagSFDown";
   // case sysBtagSFShapeUpPt100       : return "sysBtagSFShapeUpPt100";
   // case sysBtagSFShapeDownPt100     : return "sysBtagSFShapeDownPt100";
   // case sysBtagSFShapeUpEta1p2      : return "sysBtagSFShapeUpEta1p2";
   // case sysBtagSFShapeDownEta1p2    : return "sysBtagSFShapeDownEta1p2";
      case sysBtagSFShapeUpPt65        : return "sysBtagSFShapeUpPt65";
      case sysBtagSFShapeDownPt65      : return "sysBtagSFShapeDownPt65";
      case sysBtagSFShapeUpEta0p7      : return "sysBtagSFShapeUpEta0p7";
      case sysBtagSFShapeDownEta0p7    : return "sysBtagSFShapeDownEta0p7";  
      case sysMisTagSFUp               : return "sysMisTagSFUp";
      case sysMisTagSFDown             : return "sysMisTagSFDown";
      case sysTopScaleUp               : return "sysTopScaleUp";
      case sysTopScaleDown             : return "sysTopScaleDown";
      case sysVBosonScaleUp            : return "sysVBosonScaleUp";
      case sysVBosonScaleDown          : return "sysVBosonScaleDown";
      case sysSingleTopScaleUp         : return "sysSingleTopScaleUp";
      case sysSingleTopScaleDown       : return "sysSingleTopScaleDown";
      case sysTopMatchUp               : return "sysTopMatchUp";
      case sysTopMatchDown             : return "sysTopMatchDown";            
      case sysVBosonMatchUp            : return "sysVBosonMatchUp";          
      case sysVBosonMatchDown          : return "sysVBosonMatchDown";
      case sysTopMassUp                : return "sysTopMassUp";  
      case sysTopMassDown              : return "sysTopMassDown";            
      case sysQCDUp                    : return "sysQCDUp";           
      case sysQCDDown                  : return "sysQCDDown";
      case sysSTopUp                   : return "sysSTopUp";               
      case sysSTopDown                 : return "sysSTopDown";
      case sysDiBosUp                  : return "sysDiBosUp";              
      case sysDiBosDown                : return "sysDiBosDown";
      case sysPDFUp                    : return "sysPDFUp";              
      case sysPDFDown                  : return "sysPDFDown";
      case sysHadUp                    : return "sysHadronizationUp";
      case sysHadDown                  : return "sysHadronizationDown"; 
      case sysShapeUp                  : return "sysShapeUp";              
      case sysShapeDown                : return "sysShapeDown"; 
      default                          : std::cout << "ERROR: the chosen input for function sysLabel is not valid" << std::endl;
                                         std::cout << "chosen systematic variation:  " << sys            << std::endl;
                                         std::cout << "maximum systematic variation: " << ENDOFSYSENUM-1 << std::endl;
                                         return "";
    }
  }

  TString sampleLabel(unsigned int sample)
  {
    // this function returns a TString that corresponds
    // to the enumerator entry "sample" in enum samples
    // modified quantities: none
    // used functions: none
    // used enumerators: none (label correspond to samples)

    TString sampleLabel="";
    if(sample==kSig)     sampleLabel="ttbar prompt lepton";
    if(sample==kBkg)     sampleLabel="ttbar other";
    if(sample==kZjets)   sampleLabel="Z+jets";
    if(sample==kWjets)   sampleLabel="W+jets";
    if(sample==kQCD)     sampleLabel="combined QCD multijet";
    if(sample==kSTop)    sampleLabel="combined single top";
    if(sample==kDiBos)   sampleLabel="combined diboson";
    if(sample==kData)    sampleLabel="data";
    if(sample==kQCDEM1)  sampleLabel="QCD electromagnetic enriched 1";
    if(sample==kQCDEM2)  sampleLabel="QCD electromagnetic enriched 2";
    if(sample==kQCDEM3)  sampleLabel="QCD electromagnetic enriched 3";
    if(sample==kQCDBCE1) sampleLabel="QCD heavy quark to electron enriched 1";
    if(sample==kQCDBCE2) sampleLabel="QCD heavy quark to electron enriched 2";
    if(sample==kQCDBCE3) sampleLabel="QCD heavy quark to electron enriched 3";
    if(sample==kWW)      sampleLabel="WW";
    if(sample==kWZ)      sampleLabel="WZ";
    if(sample==kZZ)      sampleLabel="ZZ";
    if(sample==kSTops)   sampleLabel="single top production s channel";
    if(sample==kSATops)  sampleLabel="single anti top production s channel";
    if(sample==kSTopt)   sampleLabel="single top production t channel";
    if(sample==kSATopt)  sampleLabel="single anti top production t channel";
    if(sample==kSToptW)  sampleLabel="single top production tW channel";
    if(sample==kSAToptW) sampleLabel="single anti top production tW channel";
    return sampleLabel;
}

  double effSFAB(int sys=sysNo, std::string decayChannel="unset")
  {
    // this function returns the muon eff SF
    // as derived from Z->mumu tag and probe method
    // modified quantities: NONE
    // used functions: NONE
    // used enumerators: NONE
    // "sys": if sysMuEffSFup/sysMuEffSFdown is
    // chosen, the corresponding systematic shifted
    // SF is returned

    if(sys>=ENDOFSYSENUM){
      std::cout << "ERROR in effSFAB:" << std::endl;
      std::cout << "sys must be smaller than " << ENDOFSYSENUM << std::endl;
    }

    // SF is now applied as event weight in analyzer
    //return 1.0;

    // combined single muon SF Run A+B from tag and probe
    double result = -1.;
    if (decayChannel.compare("muon")==0) {
      result = 1.0; // SF is now applied as event weight in analyzer
    }
    else if (decayChannel.compare("electron")==0) {
      // result = 0.9658; 
      result = 1.0; // SF is now applied as event weight in analyzer
    }
    // errors for the derived SF
    //double errorUp   = 0.03*result;
    //double errorDown = 0.03*result;
    // return requestet SF
    // SF uncertainty is now applied as event weight in analyzer
    //if(sys==sysMuEffSFUp  ) result+=errorUp;
    //if(sys==sysMuEffSFDown) result-=errorDown;
    return result;
  }
  
  // BR correction for ttbar->lnuqq'bb'
  // used for ttbar SG and BG (which is mainly from tau decays)
  double BRcorrectionSemileptonic = 0.985608;
  
  void histogramStyle(TH1& hist, int sampleType, bool filled=true, double markersize=1.2, unsigned int color=0)
  {
    // this function configures the style of a TH1 histogram "hist"
    // using "sampleTyp" to identify the corresponding sample from
    // the enumerator samples definition and assign the corresponding
    // marker and color
    // modified quantities: hist
    // used functions: marker_, color_
    // used enumerators: samples
    // "filled": 0 - line only
    //           1 - area under plot filled

    hist.SetStats(kFALSE);
    if(sampleType==kData || !filled){
      if(!filled)hist.SetLineWidth(2);
      hist.SetLineColor(color_[sampleType]);
      hist.SetMarkerColor(color_[sampleType]);
      if(sampleType==kQCD){
	hist.SetLineColor(kYellow+1);
	hist.SetMarkerColor(kYellow+1);
      }
      if(sampleType==kDiBos){
	hist.SetLineColor(kGray);
	hist.SetMarkerColor(kGray);
      }
      hist.SetMarkerStyle(marker_[sampleType]);
      hist.SetMarkerSize(markersize);
      hist.SetFillStyle(0);
    }
    else{
      hist.SetFillColor(color_[sampleType]);
    }
    if(color!=0){
      hist.SetLineColor(color);
      hist.SetFillColor(color);
      hist.SetMarkerColor(color);
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
    if(titleY!="") hist.GetYaxis()->SetTitle(titleY);
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

  //void canvasStyle(TCanvas& canv) re-definition of header to avoid warnings when compiling, must be changed once function body is not empty anymore
  void canvasStyle()
  {
    // function is not called anymore - just kept if indiviudal configurations might be required
    // could be considered to be deleted
  }

  void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123)
  {
    // this function configures the axis style of a TH1 histogram "hist"
    // modified quantities: hist
    // used functions: NONE
    // used enumerators: NONE
    // "titleX": title of the x-axis
    // "titleY": title of the y-axis
    // "yMin": minimum of the y axis
    // "yMax": maximum of the y axis

    hist.SetTitle("");
    hist.GetXaxis()->SetTitle(titleX);
    hist.GetYaxis()->SetTitle(titleY);
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
	std::ofstream fapp(file, std::ios::app);
	fapp << output << std::endl;;
	fapp.close();
      }
    }

  void drawLine(const double xmin, const double ymin, const double xmax, const double ymax, const unsigned int color=kBlack, const double lineWidth=2, const unsigned int lineStyle=1)
  {
    // this function draws a line withe the chosen coordinates,
    // color and width into the active canvas
    // modified quantities: NONE
    // used functions: NONE
    // used enumerators: NONE
    TLine *line = new TLine();
    line->SetLineWidth(lineWidth);
    line->SetLineStyle(lineStyle);
    line->SetLineColor(color);
    line->DrawLine(xmin, ymin, xmax, ymax);
  }

  int roundToInt(double value, bool roundDown=false)
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

  TString sampleLabel(unsigned int sample, const std::string decayChannel, bool TwoThousandEleven=true)
  {
    // this function returns the name of the entered MC process
    // corresponding to the enumerator entry "sample" as defined in samples
    // modified quantities: NONE
    // used functions: NONE
    // used enumerators: samples

    // create output
    TString MCprocess;
    // list all MC process/sample names
    if(sample==kSig && decayChannel.compare("electron")==0) MCprocess="t#bar{t} (e prompt)";
    if(sample==kSig && decayChannel.compare("muon"    )==0) MCprocess="t#bar{t} (#mu prompt)";
    if(sample==kBkg    ) MCprocess="t#bar{t} other";
    if(sample==kSTop   ) MCprocess="Single Top";
    if(sample==kSToptW ) MCprocess="Single Top tW";
    if(sample==kSTops  ) MCprocess="Single Top s";
    if(sample==kSTopt  ) MCprocess="Single Top t";
    if(sample==kSAToptW) MCprocess="Single Anti Top tW";
    if(sample==kSATops ) MCprocess="Single Anti Top s";
    if(sample==kSATopt ) MCprocess="Single Anti Top t";
    if(sample==kWjets  ) MCprocess="W+Jets";
    if(sample==kZjets  ) MCprocess="Z+Jets";
    if(sample==kDiBos  ) MCprocess="Diboson";
    if(sample==kWW     ) MCprocess="WW";
    if(sample==kWZ     ) MCprocess="WZ";
    if(sample==kZZ     ) MCprocess="ZZ";
    if(sample==kQCD    ) MCprocess="QCD Multijet";
    if(sample==kQCDEM1 ) MCprocess="QCDEM1";
    if(sample==kQCDEM2 ) MCprocess="QCDEM2";
    if(sample==kQCDEM3 ) MCprocess="QCDEM3";
    if(sample==kQCDBCE1) MCprocess="QCDBCE1"; 
    if(sample==kQCDBCE2) MCprocess="QCDBCE2";
    if(sample==kQCDBCE3) MCprocess="QCDBCE3"; 
    if(sample==kData&&!TwoThousandEleven) MCprocess="Data 2010";
    if(sample==kData&& TwoThousandEleven) MCprocess="Data";
    // return result
    return MCprocess;
  }

  TH1F* divideByBinwidth(TH1F* histo, bool calculateError=true)
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
	double binwidth=(double)(histo->GetBinWidth(i));
	// take care of bins width width 0
	// (these could not be filled and
	// exist because of technical reasons only)
	if(binwidth==0)binwidth=1;
	// recalculate error
	double error = (double)(histo->GetBinError(i)) / binwidth;
	// recalculate bin content
	outputHisto->SetBinContent(i, ( (double)(histo->GetBinContent(i)) / binwidth) );
	if(calculateError) outputHisto->SetBinError(i, error);
      }
      // return result
      return outputHisto;
    }

  void DrawDecayChLabel(TString decaychannel="", double textSize=0.04)
  {
    // Draw label for Decay Channel in upper left corner of plot

    TPaveText *decch = new TPaveText();

    decch -> AddText(decaychannel);

    decch -> SetX1NDC(      gStyle->GetPadLeftMargin() + gStyle->GetTickLength()        );
    decch -> SetY1NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength() - 0.05 );
    decch -> SetX2NDC(      gStyle->GetPadLeftMargin() + gStyle->GetTickLength() + 0.15 );
    decch -> SetY2NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength()        );

    decch -> SetFillStyle(0);
    decch -> SetBorderSize(0);
    if(textSize!=0) decch->SetTextSize(textSize);
    decch -> SetTextAlign(12);
    decch -> Draw("same");
  }

  void DrawCMSLabels(bool cmsprelim=true, double luminosity=0.0, double textSize=0.04)
  {
    // Draw official labels (CMS Preliminary, luminosity and CM energy) above plot

    TPaveText *label = new TPaveText();

    label -> SetX1NDC(gStyle->GetPadLeftMargin());
    label -> SetY1NDC(1.0-gStyle->GetPadTopMargin());
    label -> SetX2NDC(1.0-gStyle->GetPadRightMargin());
    label -> SetY2NDC(1.0);
    label -> SetTextFont(42);

    if (cmsprelim)
      {
	label -> AddText(Form("CMS Preliminary, %3.2f fb^{-1} at #sqrt{s}=7 TeV",luminosity/1000));
      }
    else
      {
	label -> AddText(Form("CMS Work in progress, %3.2f fb^{-1} at #sqrt{s}=7 TeV",luminosity/1000));
      }

    label->SetFillStyle(0);
    label->SetBorderSize(0);
    if(textSize!=0) label->SetTextSize(textSize);
    label->SetTextAlign(32);
    label->Draw("same");
  }

  void DrawLabel(TString text, const double x1, const double y1, const double x2, const double y2, int centering=12, double textSize=0.04)
  {
    // function to directly draw a label into the active canvas
    // the coordinates of the window are: "x1", "y1", "x2", "y2"
    // the label will contain the text "text" and the textsize is "textSize"
    // modified quantities: the active canvas
    // used functions: NONE
    // used enumerators: NONE

    TPaveText *label = new TPaveText(x1, y1, x2, y2, "br NDC");
    label->AddText(text);
    label->SetFillStyle(0);
    label->SetBorderSize(0);
    if(textSize!=0) label->SetTextSize(textSize);
    label->SetTextAlign(centering);
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

  double lumiweight(unsigned int sample, double luminosity, unsigned int kSys, const std::string decayChannel)
  {
    // this function derives the lumiweight for every standard MC
    // sample "sample" based on the theoretical cross section, the
    // number of generated events and the chosen "luminosity"
    // Furthermore, the BR correction is considered for ttbar signal
    // NOTE: enter luminosity IN / pb!!!!
    // modified quantities: NONE
    // used functions: BRcorrectionSemileptonic
    // used enumerators: samples, systematicVariation

    // function internal detail level of text output
    int verbose=0;
    // a) check if input is valid
    // sample existing?
    if(sample>kSAToptW){
      std::cout << "ERROR: invalid sample label for lumiweight calculation, no scaling will be done" << std::endl;
      return 1.;
    }
    // valid luminosity entered?
    if(luminosity<=0){
      std::cout << "ERROR: chosen luminosity for lumiweight calculation is <= 0, no scaling will be done" << std::endl;
      return 1.;
    }
    // valid decayChannel entered?
    if(!(decayChannel.compare("muon")==0 || decayChannel.compare("electron")==0)){
      std::cout << "ERROR: chosen decaychannel does not correspond to electron or muon, no scaling will be done" << std::endl;
      return 1.;
    }
    // b) define in/output for weight calculation
    double crossSection=1;
    double Nevents=0;
    double weight =0;

    // c) fill #events in sample and cross sections (in / pb)
    // 2*ttbar MADGRAPH
    if((sample==kSig)||(sample==kBkg)){
      crossSection=ttbarCrossSection; 
      // Z2 Summer11
      //Nevents = (sample == kSig) ? 3701947 : 3581947 ;
      Nevents = 3697693; // after kinematics filter
      // Summer11 systematic samples
      if(kSys==sysTopScaleUp  ) Nevents=929319;//930483;  
      if(kSys==sysTopScaleDown) Nevents=966082;//967055;  
      if(kSys==sysTopMatchUp  ) Nevents=1061531;//1062792; 
      if(kSys==sysTopMatchDown) Nevents=1064250;//1065232;  
      if(kSys==sysTopMassUp   ) Nevents=1536566;//1538301; 
      if(kSys==sysTopMassDown ) Nevents=1604710;//1606570; 
    }
    // W->lnu+jets MADGRAPH
    else if(sample==kWjets){
      crossSection=31314.;
      // Z2 Summer11
      //Nevents=81352581;
      Nevents = 81178819; // after kinematics filter
      // Summer11 systematic samples:
      if(kSys==sysVBosonScaleUp  ) Nevents=9761537;//9784907;  
      if(kSys==sysVBosonScaleDown) Nevents=10075524;//10092532;
      if(kSys==sysVBosonMatchUp  ) Nevents=10438789;//10461655; 
      if(kSys==sysVBosonMatchDown) Nevents=9936639;//9956679;  
    }
    // DY->ll+jets MADGRAPH
    else if(sample==kZjets){
      crossSection=3048.;
      // Z2 Summer11
      //Nevents=35101516;
      Nevents = 35032553; // after kinematics filter
      // Summer11 systematic samples:
      if(kSys==sysVBosonScaleUp  ) Nevents=1589496;//1593052;
      if(kSys==sysVBosonScaleDown) Nevents=1656321;//1658995;
      if(kSys==sysVBosonMatchUp  ) Nevents=1638100;//1641367;
      if(kSys==sysVBosonMatchDown) Nevents=1612036;//1615032;
    }
    // QCD Mu enriched PYTHIA6
    else if(sample==kQCD&&decayChannel.compare("muon")==0){
      // Z2 Summer11
      crossSection=296600000.*0.0002855; // generator crossSection * prefilter efficiency
      Nevents     =20416038.;
    }
    // QCD e+jets channel 
    // a) subsamples
    else if(sample==kQCDEM1){
      crossSection=0.0106*236100000; // generator prefilter efficiency * LO PYTHIA crossSection
      Nevents     =35729669;
    }
    else if(sample==kQCDEM2){
      crossSection=0.061*59440000; // generator prefilter efficiency * LO PYTHIA crossSection
      Nevents     =70392060;
    }
    else if(sample==kQCDEM3){
      crossSection=0.159*898200; // generator prefilter efficiency * LO PYTHIA crossSection
      Nevents     =8150672;
    }
    else if(sample==kQCDBCE1){
      crossSection=0.00059*236100000; // generator prefilter efficiency * LO PYTHIA crossSection
      Nevents     =2081560;
    }
    else if(sample==kQCDBCE2){
      crossSection=0.00242*59440000; // generator prefilter efficiency * LO PYTHIA crossSection
      Nevents     =2030033;
    }
    else if(sample==kQCDBCE3){
      crossSection=0.0105*898200; // generator prefilter efficiency * LO PYTHIA crossSection
      Nevents     =1082691;
    }
    // b)combined
    else if(sample==kQCD&&decayChannel.compare("electron")==0){
      // Z2 Summer11: already added in combineMCsamples.C
      // with cross section as weight, only
      // lumi normalization is done here
      Nevents     =1.;
      crossSection=1;
    }
    // singleTop POWHEG samples
    // a) subsamples
    else if(sample==kSATops){
      crossSection=1.44;
      //Nevents     =137980;
      Nevents = 137662; // after kinematics filter
      // scale variation
      if(kSys==sysTopScaleUp  ) Nevents =153584;//153981;
      if(kSys==sysTopScaleDown) Nevents =153650;//153971;
    }
    else if(sample==kSTops){
      crossSection=3.19;
      //Nevents     =259971; 
      Nevents = 259595; // after kinematics filter
      // scale variation
      if(kSys==sysTopScaleUp  ) Nevents =285513;//285972;
      if(kSys==sysTopScaleDown) Nevents =285182;//285602;
    }
    else if(sample==kSATopt){
      crossSection=22.65;
      //Nevents     =1944826;
      Nevents = 1939703; // after kinematics filter
      // scale variation
      if(kSys==sysTopScaleUp  ) Nevents =563929;//565520;
      if(kSys==sysTopScaleDown) Nevents =564169;//565454;
    }
    else if(sample==kSTopt){
      crossSection=41.92;
      //Nevents     =3900171;
      Nevents = 3891841; // after kinematics filter
      // scale variation
      // FIXME MARTIN: t channel single top scale samples still missing 
      // if(kSys==sysTopScaleUp  ) Nevents =;
      // if(kSys==sysTopScaleDown) Nevents =;
    }
    else if(sample==kSAToptW){
      crossSection=7.87;
      //Nevents     =809984;
      Nevents = 808200; // after kinematics filter
      // scale variation
      if(kSys==sysTopScaleUp  ) Nevents =436750;//437798;
      if(kSys==sysTopScaleDown) Nevents =437007;//437863;
    }
    else if(sample==kSToptW){
      crossSection=7.87;
      //Nevents     =814390;
      Nevents = 812600; // after kinematics filter
      // scale variation
      if(kSys==sysTopScaleUp  ) Nevents =436656;//437736;
      if(kSys==sysTopScaleDown) Nevents =436986;//437819;
    }
    // b) combined single top sample
    else if(sample==kSTop){
      // Summer11 Z2: already added in combineMCsamples.C
      // with cross section as weight,
      // lumi normalization is done here
      Nevents=1;
      crossSection=1.;
    }
    // DiBoson PYTHIA6 Z2
    // a) subsamples
    else if(sample==kWW){
      crossSection=43.0;
      // Summer11 Z2
      Nevents=4225916;
    }
    else if(sample==kWZ){
      crossSection=18.2;
      // Summer11 Z2
      Nevents=4265243;
    }
    else if(sample==kZZ){
      crossSection=5.9;
      // Summer11 Z2
      Nevents=4187885;
    }
    // b) combined diboson: WW,WZ,ZZ
    else if(sample==kDiBos){
      // Summer11 Z2: already added in combineMCsamples.C
      // with cross section as weight,
      // lumi normalization is done here
      crossSection=1.;
      Nevents=1;
    }
    // Data
    else if(sample==kData){
      return 1.;
      // this leads to a weight
      // of 1.0 as data needs no weight
    }
    // unknown input
    else{
      std::cout << "ERROR: unknown configuration sample=" << sample;
      std::cout << ", decayChannel=" << decayChannel << std::endl;
      exit(0);
    }
    // d) calculate weight
    weight = effSFAB(kSys,decayChannel) * luminosity / ( Nevents / crossSection );
    if(verbose>0){
      std::cout << "sample: " << sampleLabel(sample,decayChannel) << std::endl;
      std::cout << "systematic var.: " << sysLabel(kSys) << std::endl;
    }
    // e) systematic shifts
    double weight2=weight;
    if(verbose>1) std::cout << "weight before scaling: " << weight2 << std::endl;
    // e1) for ttbar->lnu: BR correction
    if(sample==kSig) weight *= BRcorrectionSemileptonic;
    // e2) systematic higher/lower BG
    double scale=0;
    // (i) more/less DiBoson
    if(sample==kWW||sample==kWZ||sample==kZZ||sample==kDiBos){
      scale=0.3;
      if(kSys==sysDiBosUp  ) weight*=(1.0+scale);
      if(kSys==sysDiBosDown) weight*=(1.0-scale);
    }
    // (ii) more/less QCD
    if(sample==kQCD){
      scale=0.5;
      if(kSys==sysQCDUp  ) weight*=(1.0+scale);
      if(kSys==sysQCDDown) weight*=(1.0-scale);
    }
    // (iii) more/less single top
    if(sample==kSATops||sample==kSATopt||sample==kSAToptW||sample==kSTops||sample==kSTopt||sample==kSToptW||sample==kSTop){
      scale=0.3;
      if(kSys==sysSTopUp  ) weight*=(1.0+scale);
      if(kSys==sysSTopDown) weight*=(1.0-scale);
    }
    if(scale!=0&&verbose>0) std::cout << "possible scale factor: " << scale << std::endl;
    // printout for systematic variation
    if(verbose==1){
      std::cout << "weight";
      if(verbose>1){
	if(weight!=weight2) std::cout << "(scaled)";
	if(weight==weight2) std::cout << "(not scaled)";
      }
      std::cout << ": " << weight << std::endl;
      if(verbose>1) std::cout << "ratio: " << weight/weight2 << std::endl;
      if(weight!=weight2&&sample==kSig) std::cout << "(BR correction applied)" << std::endl;
    }
    // return result
    if(sample!=kData&&weight==1){
      std::cout << "WARNING: function lumiweight";
      std::cout << " gives result 1 for sample:" << std::endl;
      std::cout << sampleLabel(sample) << ", " << decayChannel << " channel" << std::endl;
      std::cout << "used xSec:       " << crossSection << std::endl;
      std::cout << "used Nevents:    " << Nevents      << std::endl;
      std::cout << "used luminosity: " << luminosity   << std::endl;
    }
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
    bool verbose=false;
    // save inputstring in char* path
    std::string inputString=(std::string)inputTString;
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
      std::string output="";
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

  TString TopFilename(unsigned int sample, unsigned int sys, const std::string decayChannel)
  {
    // this function contains the basic convention for the MC
    // .root files and returns the correct names for choosen samplesample"
    // and systematic variation "sys"
    // modified quantities: NONE
    // used functions: NONE
    // used enumerators: samples, systematicVariation

    TString fileName = "decayChannel_undefined" ;
    if      (decayChannel.compare("electron")==0) fileName ="elecDiffXSec";
    else if (decayChannel.compare("muon")==0)     fileName ="muonDiffXSec";
    else if (decayChannel.compare("combined")==0) fileName ="combinedDiffXSec"; 
    else fileName ="muonDiffXSec"; // default
    // name of data file is given directly in the .C file
    if(sample==kData) return "";
    // standard MC filenames
    if(sample==kSig  )fileName += "SigMadD6T";
    if(sample==kBkg  )fileName += "BkgMadD6T";
    if(sample==kWjets)fileName += "WjetsMadD6T";
    if(sample==kZjets)fileName += "ZjetsMadD6T";
    if(sample==kDiBos)fileName += "VVPytia6Z2";
    if(sample==kQCD  )fileName += "QCDPythiaZ2";
    if(sample==kSTop )fileName += "SingleTopMadZ2";
    // subsamples are all located in subfolder called "MergedFiles"
    if(sample==kWW     )fileName = "MergedFiles/"+fileName+"WWPytia6Z2";
    if(sample==kWZ     )fileName = "MergedFiles/"+fileName+"WZPytia6Z2";
    if(sample==kZZ     )fileName = "MergedFiles/"+fileName+"ZZPytia6Z2";
    if(sample==kQCDEM1 )fileName = "MergedFiles/"+fileName+"QCDPythiaEM1Z2";
    if(sample==kQCDEM2 )fileName = "MergedFiles/"+fileName+"QCDPythiaEM2Z2";
    if(sample==kQCDEM3 )fileName = "MergedFiles/"+fileName+"QCDPythiaEM3Z2";
    if(sample==kQCDBCE1)fileName = "MergedFiles/"+fileName+"QCDPythiaBCE1Z2"; 
    if(sample==kQCDBCE2)fileName = "MergedFiles/"+fileName+"QCDPythiaBCE2Z2";
    if(sample==kQCDBCE3)fileName = "MergedFiles/"+fileName+"QCDPythiaBCE3Z2";  
    if(sample==kSToptW )fileName = "MergedFiles/"+fileName+"SingleTopTWchannelMadZ2";
    if(sample==kSTops  )fileName = "MergedFiles/"+fileName+"SingleTopSchannelMadZ2";
    if(sample==kSTopt  )fileName = "MergedFiles/"+fileName+"SingleTopTchannelMadZ2";
    if(sample==kSAToptW)fileName = "MergedFiles/"+fileName+"SingleAntiTopTWchannelMadZ2";
    if(sample==kSATops )fileName = "MergedFiles/"+fileName+"SingleAntiTopSchannelMadZ2";
    if(sample==kSATopt )fileName = "MergedFiles/"+fileName+"SingleAntiTopTchannelMadZ2";
    // label for MC production cycle
    fileName += "Summer11";
    // take care of systematic variations
    // they are located in dedicated subfolders
    // JES
    if(sys==sysJESUp  ) fileName = "JESUp/"+fileName+"JESup";
    if(sys==sysJESDown) fileName = "JESDown/"+fileName+"JESdown";
    // JER
    if(sys==sysJERUp  ) fileName = "JERUp/"+fileName+"JERup"; 
    if(sys==sysJERDown) fileName = "JERDown/"+fileName+"JERdown";
    // Shape variation
    // only for new MC and ttbar signal
    if(sample==kSig){
      if(sys==sysShapeUp  ) fileName = "MCShapeUp/"+fileName+"MCShapeVarUp";
      if(sys==sysShapeDown) fileName = "MCShapeDown/"+fileName+"MCShapeVarDown";
    }
    // Shape variation
    // only for new MC and ttbar signal
    if(sample==kSig){
      if(sys==sysPDFUp  ) fileName = "PDFUp/"+fileName+"PdfVarUp";
      if(sys==sysPDFDown) fileName = "PDFDown/"+fileName+"PdfVarDown";
    }
    // Scale
    // (a) top
    if((sys==sysTopScaleUp  )&&((sample==kSig)||(sample==kBkg)||(sample==kSTop)||(sample==kSToptW)||(sample==kSTops)||(sample==kSTopt)||(sample==kSAToptW)||(sample==kSATops)||(sample==kSATopt))) fileName = "ScaleUp/"+fileName+"ScaleUp";
    if((sys==sysTopScaleDown)&&((sample==kSig)||(sample==kBkg)||(sample==kSTop)||(sample==kSToptW)||(sample==kSTops)||(sample==kSTopt)||(sample==kSAToptW)||(sample==kSATops)||(sample==kSATopt))) fileName = "ScaleDown/"+fileName+"ScaleDown";
    // (b) V+jets
    if((sys==sysVBosonScaleUp  )&&((sample==kWjets)||(sample==kZjets))) fileName = "ScaleUp/"+fileName+"ScaleUp";
    if((sys==sysVBosonScaleDown)&&((sample==kWjets)||(sample==kZjets))) fileName = "ScaleDown/"+fileName+"ScaleDown";  
    // (c) SingleTop
    if((sys==sysSingleTopScaleUp)  &&(sample==kSTop)) fileName = "ScaleUp/"+fileName+"ScaleUp";
    if((sys==sysSingleTopScaleDown)&&(sample==kSTop)) fileName = "ScaleDown/"+fileName+"ScaleDown";  
    // (a) top   
    if((sys==sysTopMatchUp  )&&((sample==kSig)||(sample==kBkg))) fileName = "MatchUp/"+fileName+"MatchUp";
    if((sys==sysTopMatchDown)&&((sample==kSig)||(sample==kBkg))) fileName = "MatchDown/"+fileName+"MatchDown";
    // (b) V+jets
    if((sys==sysVBosonMatchUp  )&&((sample==kWjets)||(sample==kZjets))) fileName = "MatchUp/"+fileName+"MatchUp";
    if((sys==sysVBosonMatchDown)&&((sample==kWjets)||(sample==kZjets))) fileName = "MatchDown/"+fileName+"MatchDown";
    // Top Mass
    if((sys==sysTopMassUp  )&&((sample==kSig)||(sample==kBkg))) fileName = "TopMassUp/"+fileName+"TopMassUp";
    if((sys==sysTopMassDown)&&((sample==kSig)||(sample==kBkg))) fileName = "TopMassDown/"+fileName+"TopMassDown";
    // Hadronization
    if((sys==sysHadUp  )&&((sample==kSig)||(sample==kBkg))) fileName = "HadronizationUp/"+fileName+"HadUp";
    if((sys==sysHadDown)&&((sample==kSig)||(sample==kBkg))) fileName = "HadronizationDown/"+fileName+"HadDown";
    fileName+="PF.root";
    // return output
    return fileName;
  }

  void saveCanvas(const std::vector<TCanvas*> MyCanvas, const TString outputFolder, const TString pdfName, const bool savePdf=true, const bool saveEps=true )
  {
    // introduce function that saves every single canvas in
    // MyCanvas as ./outputFolder/CanvasTitle.eps and in addition
    // all in one rootFile: ./outputFolder/pdfName.pdf
    // modified quantities: NONE
    // used functions: NONE
    // used enumerators: NONE

    // a) save all plots in one pdf
    if(savePdf){
      MyCanvas[0]->Print(outputFolder+pdfName+".pdf(", "pdf");
      for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
	MyCanvas[idx]->Print(outputFolder+pdfName+".pdf", "pdf");
      }
      MyCanvas[MyCanvas.size()-1]->Print(outputFolder+pdfName+".pdf)", "pdf");
    }
    // b) save every plot as pdf with title as name
    if(saveEps){
      for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
	MyCanvas[idx]->Print(outputFolder+(TString)(MyCanvas[idx]->GetTitle())+".eps");
      }
    }
  }

  std::map<unsigned int, TFile*> getStdTopAnalysisFiles( const TString inputFolder, const unsigned int systematicVariation, const TString dataFile, const std::string decayChannel)
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
      for(int sample = kSig; sample<=kSAToptW; sample++){
	// there are no QCD subsamples for muon channel
	if(!(sample>=kQCDEM1&&sample<=kQCDBCE3&&decayChannel.compare("muon")==0)){
	  TString fileName;
	  if(sample!=kData) fileName = inputFolder+"/"+TopFilename(sample, systematicVariation, decayChannel);
	  if(sample==kData) fileName = dataFile;
	  // if file exists - save in map
	  if((fileName!="no")&&(fileName!="")){
	    TFile* file = TFile::Open(fileName);
	    if(file&&!(file->IsZombie())) files_[sample]= file;
	  }
	}
      }
      return files_;
    }

    void getAllPlots( std::map<unsigned int, TFile*> files_, const std::vector<TString> plotList_,  std::map< TString, std::map <unsigned int, TH1F*> >& histo_, std::map< TString, std::map <unsigned int, TH2F*> >& histo2_, const unsigned int N1Dplots, int& Nplots, const int verbose=0, const std::string decayChannel = "unset", std::vector<TString> *vecRedundantPartOfNameInData = 0 )
  {
    // this function searches for every plot listed in "plotList_" in all files listed in "files_",
    // saves all 1D histos into "histo_" and all 2D histos into "histo2_"
    // empty plots will be neglected
    // modified quantities: "histo_", "histo2_", "Nplots"
    // used functions: sampleLabel
    // used enumerators: samples
    // "N1Dplots": the #1D plots is needed as input to destinguish between 1D and 2D plots
    // "Nplots": the total # of plots is calclated
    // "verbose": set detail level of output ( 0: no output, 1: std output 2: output for debugging )
    // "redundantPartOfNameInData": delete this part in the (folder)name when loading the plots from data
    // (needed to handle systematic variations where foldername in data and MC is different)

    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      // check if plot exists in any sample
      bool existsInAnySample=false;
      // loop samples
      for(unsigned int sample=kSig; sample<=kSAToptW; ++sample){
	// check existence of sample
	if(files_.count(sample)!=0){
	  // create plot container
	  TH1* targetPlot;
	  // delete additional part of MC foldername
	  // that does not exist in data 
	  TString plotname=plotList_[plot];
	  if(sample==kData){
	    if (vecRedundantPartOfNameInData != 0 && vecRedundantPartOfNameInData->size() != 0){
	      std::vector<TString>::iterator iter;
	      for (iter = (vecRedundantPartOfNameInData->begin()); iter != (vecRedundantPartOfNameInData->end()); iter++){
		plotname.ReplaceAll((*iter), ""); 
	      }
	    }
	  }
	  files_[sample]->GetObject(plotList_[plot], targetPlot);
	  // Check existence of plot
	  if(targetPlot){ 
	    existsInAnySample=true;
	    // go to end of loop
	    sample=kSAToptW;
	  }
	}
      }
      // end program and draw error if plot does not exist at all
      if(!existsInAnySample){
	std::cout << "ERROR: plot "+plotList_[plot]+" does not exist in any file!" << std::endl;
	exit(1);
      }
      else{
	// otherwise: get plots from sample
	// loop samples
	for(unsigned int sample=kSig; sample<=kSAToptW; ++sample){
	  // delete additional part of MC foldername
	  // that does not exist in data 
	  TString plotname=plotList_[plot];
	  if(sample==kData){
	    if (vecRedundantPartOfNameInData != 0 && vecRedundantPartOfNameInData->size() != 0){
	      std::vector<TString>::iterator iter;
	      for (iter = (vecRedundantPartOfNameInData->begin()); iter != (vecRedundantPartOfNameInData->end()); iter++){
		plotname.ReplaceAll((*iter), ""); 
	      }
	    }
	  }
	  // check if file exists
	  // give warning if file does not exist
	  if((files_.count(sample)==0)&&(plot==0)&&(verbose>0)) std::cout << "file for " << sampleLabel(sample,decayChannel) << " does not exist- continue and neglect this sample" << std::endl;
	  if(files_.count(sample)>0){
	    // create plot container
	    TH1* targetPlot;
	    if(verbose>1){
	      std::cout << std::endl << "sample: " << sample << ", " << files_[sample]->GetName() << std::endl;
	      std::cout << "plot: " << plot << ", " << plotname << std::endl;
	    }
	    files_[sample]->GetObject(plotname, targetPlot);
	    // Check if plot exits
	    // give warning if plot does not exist
	    if((!targetPlot)&&(verbose>0)) std::cout << "can not find plot "+plotname << " in file "+(TString)(files_[sample]->GetName()) << " - continue and neglect this plot" << std::endl;
	    if(targetPlot){
	      // check if plot is empty
	      bool emptyPlot=false;
	      if((plot<N1Dplots )&&((((TH1*)(files_[sample]->Get(plotname)))->GetEntries())==0.)) emptyPlot=true;
	      if((plot>=N1Dplots)&&((((TH2*)(files_[sample]->Get(plotname)))->GetEntries())==0.)) emptyPlot=true;
	      if(emptyPlot && verbose>1) std::cout << "plot "+plotList_[plot] << " in file "+(TString)(files_[sample]->GetName()) << " is empty- continue and neglect this plot" << std::endl;
	      // to avoid problems with samples where no event is passing the selection we will drop this requirement by now
	      emptyPlot=false;
	      if(!emptyPlot){
		// save plot in corresponding map
		if(plot<N1Dplots ) histo_ [plotList_[plot]][sample] = (TH1F*)(files_[sample]->Get(plotname));
		if(plot>=N1Dplots) histo2_[plotList_[plot]][sample] = (TH2F*)(files_[sample]->Get(plotname));
		// count every existing 2D plot (every sample is counted separetly as it will be drawn into an own canvas)
		if(plot>=N1Dplots) Nplots++;
	      }
	    }
	  }
	}
	// count every existing type of 1D plots (neglect #samples here as they well be drawn into the same canvas)
	if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)) Nplots++;
      }
    }
  }

  void scaleByLuminosity(const std::vector<TString> plotList_,  std::map< TString, std::map <unsigned int, TH1F*> >& histo_, std::map< TString, std::map <unsigned int, TH2F*> >& histo2_, const unsigned int N1Dplots, const double luminosity, const int verbose=1, const int systematicVariation=sysNo, const std::string decayChannel = "unset")
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
    for(unsigned int sample=kSig; sample<=kSAToptW; ++sample) {
      // loop plots
      for(unsigned int plot=0; plot<plotList_.size(); ++plot){
	// a) 1D
	// check if 1D plot exists
	if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)){
	  if(verbose>1) std::cout << std::endl << "plot: "+plotList_[plot] << " for sample " << sampleLabel(sample,decayChannel) << ":" << std::endl;
	  if(verbose>1) std::cout << "#events before weighting: " << histo_[plotList_[plot]][sample]->Integral(0, histo_[plotList_[plot]][sample]->GetNbinsX()+1) << std::endl;
	  // scale MC samples to same luminosity
	  double weight = lumiweight(sample, luminosity, systematicVariation, decayChannel);
	  histo_[plotList_[plot]][sample]->Scale(weight);
	  if(verbose>1) std::cout << "weight: " << weight << std::endl;
	  if(verbose>1) std::cout << "#events after weighting: " << histo_[plotList_[plot]][sample]->Integral(0, histo_[plotList_[plot]][sample]->GetNbinsX()+1) << std::endl;
	  // apply eff. SF for MC
	  //if(sample!=kData) histo_[plotList_[plot]][sample]->Scale(effSFAB(systematicVariation,decayChannel));
	}
	// b) 2D
	// check if 2D plot exists
	if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)){
	  if(verbose>1) std::cout << std::endl << "plot: "+plotList_[plot] << " for sample " << sampleLabel(sample,decayChannel) << ":" << std::endl;
	  if(verbose>1) std::cout << "#events before weighting: " << histo2_[plotList_[plot]][sample]->Integral(0, histo2_[plotList_[plot]][sample]->GetNbinsX()+1, 0, histo2_[plotList_[plot]][sample]->GetNbinsY()+1) << std::endl;
	  // scale MC samples to same luminosity
	  double weight = lumiweight(sample, luminosity, systematicVariation, decayChannel);
	  histo2_[plotList_[plot]][sample]->Scale(weight);
	  if(verbose>1) std::cout << "weight: " << weight << std::endl;
	  if(verbose>1) std::cout << "#events after weighting: " << histo2_[plotList_[plot]][sample]->Integral(0, histo2_[plotList_[plot]][sample]->GetNbinsX()+1, 0, histo2_[plotList_[plot]][sample]->GetNbinsY()+1) << std::endl;
	  // apply eff. SF for MC
	  //if(sample!=kData) histo2_[plotList_[plot]][sample]->Scale(effSFAB(systematicVariation,decayChannel));
	}
      }
    }
  }

  void AddSingleTopAndDiBoson(const std::vector<TString> plotList_,  std::map< TString, std::map <unsigned int, TH1F*> >& histo_, std::map< TString, std::map <unsigned int, TH2F*> >& histo2_, const unsigned int N1Dplots, const int verbose=1, bool reCreate=false, const std::string decayChannel = "unset")
  {
    // this function creates plots for all diboson and all single
    // top samples combined if the combined SingleTop and DiBoson
    // samples do not exist as .root file.
    // Every plot in "plotList_" existing in each of the three
    // sTop/ diBoson files will be combined and saved in the histo_
    // and histo2_ maps
    // NOTE: all plots from the samples are considered to be weighted
    // to the same luminosity before
    // modified quantities: "histo_", "histo2_"
    // used functions: sampleLabel
    // used enumerators: samples
    // "N1Dplots": the #1D plots is needed as input to destinguish between 1D and 2D plots
    // "verbose": set detail level of output ( 0: no output, 1: std output 2: output for debugging )
    // "reCreate": choose if you want to create the combined plot from the
    // single plots if it alredy exists. Careful: the old one will be deleted

    if(verbose>0) std::cout << std::endl;
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      // loop STop and DiBoson
      for(unsigned int sample=kSTop; sample<=kDiBos; ++sample){
	if(verbose>1) std::cout << "plot " << plotList_[plot] << ": " << std::endl;
	// mark first plot found
	bool first=true;
	// check that combined plot does not already exist
	// if existing and reCreate==1, it will be overwritten
	bool combinedplotExists=false;
	if((plot<N1Dplots )&&(histo_ [plotList_[plot]].count(sample)>0)) combinedplotExists=true;
	if((plot>=N1Dplots)&&(histo2_[plotList_[plot]].count(sample)>0)) combinedplotExists=true;
	if(reCreate==1) combinedplotExists=false;
	if((combinedplotExists==true)&&(verbose>0)){
	  std::cout << "combined plot " << plotList_[plot];
	  std::cout << " for sample " << sampleLabel(sample,decayChannel);
	  std::cout << " already exists, will keep this one" << std::endl;
	}
	if(!combinedplotExists){
	  // loop all three subchannels
	  unsigned int firstSubChannel=kSTops;
	  if(sample==kDiBos) firstSubChannel=kWW;
	  for(unsigned int subSample=firstSubChannel; subSample<=firstSubChannel+5; ++subSample){
	    // single top has 6, diboson only 2 subsamples
	    if((sample==kDiBos&&subSample<firstSubChannel+3)||sample==kSTop){
	      // check if plot exists for the subchannel
	      bool subPlotExists=false;
	      if((plot<N1Dplots )&&(histo_ [plotList_[plot]].count(subSample)>0)) subPlotExists=true;
	      if((plot>=N1Dplots)&&(histo2_[plotList_[plot]].count(subSample)>0)) subPlotExists=true;
	      if((subPlotExists==false)&&(verbose>0)){
		std::cout << "plot " << plotList_[plot];
		std::cout << " does not exist for subSample ";
		std::cout << sampleLabel(subSample,decayChannel) << std::endl;
	      }
	      if(subPlotExists){
		// add histo
		// a) 1D
		if(plot<N1Dplots){
		  if(first ) histo_[plotList_[plot]][sample]   =  (TH1F*)histo_[plotList_[plot]][subSample]->Clone();
		  if(!first) histo_[plotList_[plot]][sample]->Add((TH1F*)histo_[plotList_[plot]][subSample]->Clone());
		}
		// b) 2D
		if(plot>=N1Dplots){
		  if(first ) histo2_[plotList_[plot]][sample]   =  (TH2F*)histo2_[plotList_[plot]][subSample]->Clone();
		  if(!first) histo2_[plotList_[plot]][sample]->Add((TH2F*)histo2_[plotList_[plot]][subSample]->Clone());
		}
		// indicate that already one plot is found
		first=0;
		// print out information
		if(verbose>0){
		  std::cout << "will add " << plotList_[plot];
		  std::cout << " from " << sampleLabel(subSample,decayChannel) << std::endl;
		}
	      }
	    }
	  }
	}
      }
    }
  }

  void createStackPlot(const std::vector<TString> plotList_, std::map< TString, std::map <unsigned int, TH1F*> >& histo_, const unsigned int plot, const unsigned int N1Dplots, const int verbose=1, const std::string decayChannel="muon")
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
	  if(verbose>1) std::cout << "add "+plotList_[plot] << " plot for " << sampleLabel(sample,decayChannel) << " and " << sampleLabel(sample+1,decayChannel) << std::endl;
	  if(verbose>1) std::cout << "this new stacked plot contains now " <<  histo_[plotList_[plot]][sample]->Integral(0, histo_[plotList_[plot]][sample]->GetNbinsX()+1) << " events" << std::endl;
	}
      }
    }
  }

  float modulo(const float a, const float b)
  {
    // this function calculates a modulo b
    // where a and b are float
    // modified quantities: none
    // used functions: none
    // used enumerators: none
    // "a": dividend
    // "b": divisor

    // round a and b to the 3rd decimal place
    // this should prevent errors due to rounding effects
    float astar=ceil(a*1000.-0.5)/1000.;
    float bstar=ceil(b*1000.-0.5)/1000.;
    //  std::cout << std::endl << astar << " modulo ";
    //  std::cout << bstar << std::endl;
    float rest=astar-bstar;
    if(rest<0){
      std::cout << "can not compute " << astar << " modulo " << bstar << std::endl;
      std::cout << "because " << astar << " < " << bstar << std::endl;
      exit(1);
    }
    for(float n=1.; rest>0.; n++){
      rest=astar-n*bstar;
      if(rest<0){
	// allow some precision tolerance because of rounding effects
	if(rest>-0.000001) rest=0;
	else rest = astar-(n-1.)*bstar;
	break;
      }
    }
    return rest;
  }

  void reBinTH1F(TH1F& histoUnbinned, const std::vector<double> &binlowerEdges_, const int verbose=0)
  {
    // this function rebins an histogram using a variable binning
    // modified quantities: "histoUnbinned"
    // ATTENTION: histoUnbinned needs to have an initial equidistant binning
    // used functions: modulo
    // used enumerators: none
    // "histoUnbinned": plot to be binned
    // "binlowerEdges": vector containing all lower bin edges starting at xaxis.min, ending with xaxis.max
    // "verbose": set detail level of output ( 0: no output, 1: std output 2: output for debugging )

    unsigned int NinitialBins=histoUnbinned.GetNbinsX();
    double xMin=histoUnbinned.GetBinLowEdge(1);
    double xMax=histoUnbinned.GetBinLowEdge(NinitialBins+1);
    if(verbose>1){
      std::cout << "plot: "  << histoUnbinned.GetName() << std::endl;
      std::cout << "min: " << xMin << std::endl;
      std::cout << "max: " << xMax << std::endl;
      std::cout << "N(initial bins): " << NinitialBins << std::endl;
    }
    // check if chosen binning is valid
    // 1) N(bins)
    if(NinitialBins<=binlowerEdges_.size()){
      std::cout << "histo " << histoUnbinned.GetName() << " can not be rebinned" << std::endl;
      std::cout << "N(chosen bins) < N(initial bins)!" << std::endl;
      exit(1);
    }
    // 2) coarseness of chosen binning
    //  double initialBinWidth=(xMax-xMin)/(double)NinitialBins;
    double initialBinWidth = (double)(roundToInt(10000.*histoUnbinned.GetBinWidth(1)))/10000.;

    if(verbose>1) std::cout << "initial binwidth: " << initialBinWidth << std::endl;
    if(binlowerEdges_.size()>1){
      for(unsigned int finalBin=1; finalBin<binlowerEdges_.size()-1; ++finalBin){
	double finalBinWidth=binlowerEdges_[finalBin]-binlowerEdges_[finalBin-1];
	if(verbose>1){
	  std::cout << "bin #" << finalBin << ": ";
	  std::cout << std::setprecision(20) << std::fixed << finalBinWidth << " modulo ";
	  std::cout << std::setprecision(20) << std::fixed << initialBinWidth;
	  std::cout << " = " << modulo(finalBinWidth, initialBinWidth) << std::endl;
	}
	if(modulo(finalBinWidth, initialBinWidth)!=0){
	  std::cout << "histo " << histoUnbinned.GetName() << " can not be rebinned" << std::endl;
	  std::cout << "the ininital binning is to coarse for the chosen binning!" << std::endl;
	  std::cout << "attention: probably error in modulo function," << std::endl;
	  std::cout << "bin #" << finalBin << " of the choosen binning has ";
	  std::cout << "finalBinWidth modulo initialBinWidth of:" <<std::endl;
	  std::cout << std::setprecision(20) << std::fixed << finalBinWidth;
	  std::cout << " modulo " << std::setprecision(20) << std::fixed << initialBinWidth << " = ";
	  std::cout << std::setprecision(20) << std::fixed << modulo(finalBinWidth,initialBinWidth) << std::endl;
	  exit(1);
	}
      }
    }
    // fill vector entries in array
    // because TH1F constructer needs an array
    unsigned int arraySize=42;
    double * binLowerEdgeArray = new double[arraySize];
    if(binlowerEdges_.size()>arraySize){
      std::cout << "histo " << histoUnbinned.GetName() << " can not be rebinned" << std::endl;
      std::cout << "the function reBinTH1F can deal with at most " << arraySize << " bins" << std::endl;
      exit(1);
    }
    for(unsigned int arrayEntry=0; arrayEntry<arraySize; ++arrayEntry){
      if(arrayEntry<binlowerEdges_.size()){
	binLowerEdgeArray[arrayEntry]=binlowerEdges_[arrayEntry];
	if(verbose>1) std::cout << "array entry #" << arrayEntry << ": " << binLowerEdgeArray[arrayEntry] << " ";
      }
      else binLowerEdgeArray[arrayEntry]=binlowerEdges_[binlowerEdges_.size()-1];
    }
    if(verbose>1) std::cout << std::endl;
    // TH1F* histoBinned = new TH1F( histoUnbinned.GetName(), histoUnbinned.GetTitle(), arraySize-1, binLowerEdgeArray);
    if(verbose>1) std::cout << "N(bins) before rebinning: " << histoUnbinned.GetNbinsX() << std::endl;
    histoUnbinned = *(TH1F*)histoUnbinned.Rebin(arraySize-1, histoUnbinned.GetName(), binLowerEdgeArray);
    if(verbose>1){
      std::cout << "N(bins) after rebinning: " << histoUnbinned.GetNbinsX() << " (should be " << arraySize-1 << ")" << std::endl;
      std::cout << "from which only " << binlowerEdges_.size() << " bins are used" << std::endl;
      std::cout << "the rest will be ignored and exists only for technical reasons" << std::endl;
    }
    delete binLowerEdgeArray;
  }

  bool plotExists(std::map< TString, std::map <unsigned int, TH1F*> > histo_, const TString plotName, const unsigned int sample)
  {
    // this function checks the existence of an specific
    // entry "histo_[plotName][sample]" in the map "histo_"
    // that contains all 1D plots
    // modified quantities: none
    // used functions: none
    // used enumerators: none

    bool result=false;
    if((histo_.count(plotName)>0)&&(histo_[plotName].count(sample)>0)){
      result=true;
    }
    return result;
  }

  bool plotExists(std::map< TString, std::map <unsigned int, TH2F*> > histo_, const TString plotName, const unsigned int sample)
  {
    // this function checks the existence of an specific
    // entry "histo_[plotName][sample]" in the map "histo_"
    // that contains all 1D plots
    // modified quantities: none
    // used functions: none
    // used enumerators: none

    bool result=false;
    if((histo_.count(plotName)>0)&&(histo_[plotName].count(sample)>0)){
      result=true;
    }
    return result;
  }

  void equalReBinTH1(const int reBinFactor, std::map< TString, std::map <unsigned int, TH1F*> > histo_, const TString plotName, const unsigned int sample)
  {
    // this uses an equal rebinning (factor "reBinFactor")
    // for an specific entry "histo_[plotName][sample]"
    // in the map "histo_" that contains all 1D plots
    // modified quantities: histo_[plotName][sample]
    // used functions: plotExists
    // used enumerators: none

    if(plotExists(histo_, plotName, sample)){
      (histo_[plotName][sample])->Rebin(reBinFactor);
    }

  }

  std::map<TString, std::vector<double> > makeVariableBinning()
    {
      // this function creates a map with the hard coded
      // bin values for variable binning
      // NOTE: it is important to quote the overflow bin
      // of the initial binning as last bin here!!!
      // otherwise dividing per binwidth function
      // might later give nan and histo wouldn't be drawn
      // modified quantities: none
      // used functions: none
      // used enumerators: none

      std::map<TString, std::vector<double> > result;
      std::vector<double> bins_;


      // pt(top)
      double topPtBins[]={0., 60., 120., 200., 280., 400., 800.};
      bins_.insert( bins_.begin(), topPtBins, topPtBins + sizeof(topPtBins)/sizeof(double) );
      result["topPt"]=bins_;
      //  result["analyzeTopPartonLevelKinematics/topPt"  ]=bins_;
      bins_.clear();
      // y(top)
      double topYBins[]={-5., -2.5, -1.5, -1., -0.5, 0., 0.5, 1., 1.5, 2.5, 5.};
      bins_.insert( bins_.begin(), topYBins, topYBins + sizeof(topYBins)/sizeof(double) );
      result["topY"]=bins_;
      //  result["analyzeTopPartonLevelKinematics/topY"  ]=bins_;
      bins_.clear();
      // pt(ttbar)
      double ttbarPtBins[]={0., 20., 60., 110., 200., 300.};
      bins_.insert( bins_.begin(), ttbarPtBins, ttbarPtBins + sizeof(ttbarPtBins)/sizeof(double) );
      result["ttbarPt"]=bins_;
      //  result["analyzeTopPartonLevelKinematics/ttbarPt"  ]=bins_;
      bins_.clear();
      // y(ttbar)
      double ttbarYBins[]={-5., -1.3, -0.9, -0.6, -0.3, 0., 0.3, 0.6, 0.9, 1.3, 5.};
      bins_.insert( bins_.begin(), ttbarYBins, ttbarYBins + sizeof(ttbarYBins)/sizeof(double) );
      result["ttbarY"]=bins_;
      //  result["analyzeTopPartonLevelKinematics/ttbarY"  ]=bins_;
      bins_.clear();
      // m(ttbar)
      double ttbarMassBins[]={0., 345., 410., 480., 580., 750., 1200.};
      bins_.insert( bins_.begin(), ttbarMassBins, ttbarMassBins + sizeof(ttbarMassBins)/sizeof(double) );
      result["ttbarMass"]=bins_;
      //  result["analyzeTopPartonLevelKinematics/ttbarMass"  ]=bins_;
      bins_.clear();
      // pt(lepton)
      double lepPtBins[]={0., 30., 35., 40., 45., 50., 60., 70., 80., 100., 120., 150., 200., 275., 400., 1200.};
      bins_.insert( bins_.begin(), lepPtBins, lepPtBins + sizeof(lepPtBins)/sizeof(double) );
      result["lepPt"]=bins_;
      bins_.clear();
      // eta(lepton)
      double lepEtaBins[]={-5., -2.1, -1.8, -1.5, -1.2, -0.9, -0.6, -0.3, 0., 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 5.};
      bins_.insert( bins_.begin(), lepEtaBins, lepEtaBins + sizeof(lepEtaBins)/sizeof(double) );
      result["lepEta"]=bins_;
      bins_.clear();
      // pt(bquark)
      double bqPtBins[]={0., 30., 60., 95., 140., 200., 400., 1200.};
      bins_.insert( bins_.begin(), bqPtBins, bqPtBins + sizeof(bqPtBins)/sizeof(double) );
      result["bqPt"]=bins_;
      bins_.clear();
      // eta(bquark)
      double bqEtaBins[]={-5., -2.4, -1.5, -1, -0.5, 0., 0.5, 1., 1.5, 2.4, 5};
      bins_.insert( bins_.begin(), bqEtaBins, bqEtaBins + sizeof(bqEtaBins)/sizeof(double) );
      result["bqEta"]=bins_;
      bins_.clear();
      return result;
    }
    
    void setXAxisRange(TH1F*& his, TString variable)
    {
      // this function restricts the drawn range of the x axis in the differential variable
      // modified quantities: xAxis of his
      // used functions: none
      // used enumerators: none
      
      // restrict axis
      if(variable=="topPt")       his->GetXaxis()->SetRange(1,5);
      else if(variable=="topY")   his->GetXaxis()->SetRange(2,9);
      else if(variable=="lepEta") his->GetXaxis()->SetRange(2, his->GetNbinsX()-2);
      else if(variable=="bqPt")   his->GetXaxis()->SetRange(2,6);
      else if(variable=="bqEta")  his->GetXaxis()->SetRange(2,9);
    }

  template <class T>
    unsigned int positionInVector(std::vector<T> vec_, T object)
    {
      // this function returns the position
      // of element object in vector vec_
      // modified quantities: none
      // used functions: none
      // used enumerators: none

      // loop vector elements
      for(unsigned int element=0; element<vec_.size(); ++element)
	{
	  // ask for requested element
	  if(vec_[element]==object){
	    return element;
	  }
	}
      // return -1 if requested element is not found
      std::cout << "requested element " << object << " is not found in  vector" << std::endl;
      return -1;
    }

  void DivideYieldByEfficiencyAndLumi(TH1F* yield, TH1F* efficiency, double luminosity, bool includeEffError)
  {
    // this function divides yield by efficiency
    // and calculates the correct error in each bin based
    // on gaussian error propagation
    // modified quantities: yield
    // used functions: none
    // used enumerators: none

    // check if #bins are the same
    if(yield->GetNbinsX()!=efficiency->GetNbinsX()){
      std::cout << "#bins in yield and efficiency plots are not the same!" << std::endl;
      exit(1);
    }
    // loop all bins
    for(int bin=1; bin<=yield->GetNbinsX(); ++bin){
      double content  = yield     ->GetBinContent(bin);
      double eff      = efficiency->GetBinContent(bin);
      double binwidth = yield     ->GetBinWidth  (bin);
      if(binwidth==0) binwidth=1;
      double events   = binwidth*content;
      // value (events/binwidth/eff/lumi)
      double xSec = content/(eff*luminosity);
      // error
      double effError=efficiency->GetBinError(bin);
      if(!includeEffError) effError=0;
      double xSecError = 1/(binwidth*luminosity)*sqrt( ((events)/(eff*eff)) + ((events*effError)/(eff*eff))* ((events*effError)/(eff*eff)) );
      // check if efficiency is 0
      if(eff==0){
	xSec=0;
	xSecError=0;
      }
      // set value and error
      yield->SetBinContent(bin, xSec     );
      yield->SetBinError  (bin, xSecError);
    }
  }

  template <class T>
    void saveToRootFile(const TString& outputFile, const T& object, const bool& overwrite=false, const int& verbose=1, const TString& folder="")
    {
      // this function saves objects of class T
      // (such as TH1) in an output rootfile with name outputFile
      // modified quantities: outputFile
      // used functions: none
      // used enumerators: none

      bool saveObject=true;
      // check if file exist
      TFile* file = TFile::Open(outputFile, "UPDATE");
      // if not exist: create
      if(!file){
	if(verbose>1) std::cout << "file " << outputFile << " does not exist, will be created" << std::endl;
	file = new TFile(outputFile, "RECREATE");
      }
      // check if file is broken
      if(file->IsZombie()){
	std:: cout << "file " << outputFile << " is broken" << std::endl;
	// if broken: don't save object
	saveObject=false;
      }
      else{
	// if not broken: open file
	file->cd();
	// create folder if it does not exist
	if(folder!=""){
	  if(verbose>1) std::cout << "check existence of directory " << folder << std::endl;
	  // see how many subfolders are within folder
	  unsigned int Nfolders=folder.CountChar(*"/")+1;
	  if(verbose>1) std::cout << "these are " << Nfolders << " subdirectories" << std::endl;
	  // loop subdirectories
	  for(unsigned int subfolderNumber=1; subfolderNumber<=Nfolders; ++subfolderNumber){
	    TString subfolder= getStringEntry(folder, subfolderNumber, "/");
	    if(gDirectory->GetDirectory(subfolder)==0){
	      if(verbose>1) std::cout << "subfolder " << subfolder  << " not existing - will create it" << std::endl;
	      gDirectory->mkdir(subfolder);
	    }
	    else if(verbose>1) std::cout << "subfolder " << subfolder  << " is already existing" << std::endl;
	    // go to directory
	    gDirectory->cd(subfolder);
	  }
	}
	// if you don't want to overwrite, check if object exists
	int count=-1;
	if(!overwrite){
	  TString saveObjectName=(TString)object->GetTitle();
	  if(verbose>1) std::cout << "searching for object " << saveObjectName << std::endl;
	  // loop all objects in file
	  TList * list = gDirectory->GetListOfKeys();
	  while( list->At( count+1 ) != list->Last()){
	    ++count;
	    TObject *folderObject = list->At(count);
	    TString folderObjectName = (TString)folderObject->GetName();
	    if(verbose>1) std::cout << "candidate #" << count+1 << ": " << folderObjectName << std::endl;
	    // check if object you want to save is already existing
	    // by comparing the names
	    if(folderObjectName==saveObjectName){
	      if(verbose>1){
		std::cout << "already exists in file " << outputFile << std::endl;
		std::cout << "will keep the old one!" << std::endl << std::endl;
	      }
	      saveObject=false;
	      break;
	    }
	  }
	}
      }
      // save object
      if(saveObject){
	if(verbose>0){
	  std::cout << "saving object " << (TString)object->GetTitle();
	  std::cout << " to file " << outputFile;
	  if(folder!="") std::cout << " ( folder " << folder << " )";
	  std::cout << std::endl << std::endl;
	}
	// overwrite existing
	object->Write(object->GetTitle(), TObject::kOverwrite);
      }
      // close file
      file->Close();
    }

  template <class T>
    void saveToRootFileAll(const TString& outputFile, const std::vector< std::pair< T*,TString > > &objects_, const bool& overwrite=false, const int& verbose=1)
    {
      // this function saves all objects of class T in saveCanvas_
      // (such as TH1) in an output rootfile with name outputFile
      // modified quantities: outputFile
      // used functions: none
      // used enumerators: none

      bool saveObject=true;
      // check if file exist
      TFile* file = TFile::Open(outputFile, "UPDATE");
      // if not exist: create
      if(!file){
	if(verbose>1) std::cout << "file " << outputFile << " does not exist, will be created" << std::endl;
	file = new TFile(outputFile, "RECREATE");
      }
      // check if file is broken
      if(file->IsZombie()){
	std:: cout << "file " << outputFile << " is broken" << std::endl;
	// if broken: don't save object
	saveObject=false;
      }
      else{
	// if not broken: open file
	file->cd();
	// loop list of plots to be saved
	for(unsigned int idx=0; idx<objects_.size(); ++idx){  
	  //get object and folder
	  TString folder=(TString)(objects_[idx].second);
	  T* object=(T*)(objects_[idx].first);
	  // create folder if it does not exist
	  if(folder!=""){
	    if(verbose>1) std::cout << "check existence of directory " << folder << std::endl;
	    // see how many subfolders are within folder
	    unsigned int Nfolders=folder.CountChar(*"/")+1;
	    if(verbose>1) std::cout << "these are " << Nfolders << " subdirectories" << std::endl;
	    // loop subdirectories
	    for(unsigned int subfolderNumber=1; subfolderNumber<=Nfolders; ++subfolderNumber){
	      TString subfolder= getStringEntry(folder, subfolderNumber, "/");
	      if(gDirectory->GetDirectory(subfolder)==0){
		if(verbose>1) std::cout << "subfolder " << subfolder  << " not existing - will create it" << std::endl;
		gDirectory->mkdir(subfolder);
	      }
	      else if(verbose>1) std::cout << "subfolder " << subfolder  << " is already existing" << std::endl;
	      // go to directory
	      gDirectory->cd(subfolder);
	    }
	  }
	  // if you don't want to overwrite, check if object exists
	  int count=-1;
	  if(!overwrite){
	    TString saveObjectName=(TString)object->GetTitle();
	    if(verbose>1) std::cout << "searching for object " << saveObjectName << std::endl;
	    // loop all objects in file
	    TList * list = gDirectory->GetListOfKeys();
	    while( list->At( count+1 ) != list->Last()){
	      ++count;
	      TObject *folderObject = list->At(count);
	      TString folderObjectName = (TString)folderObject->GetName();
	      if(verbose>1) std::cout << "candidate #" << count+1 << ": " << folderObjectName << std::endl;
	      // check if object you want to save is already existing
	      // by comparing the names
	      if(folderObjectName==saveObjectName){
		if(verbose>1){
		  std::cout << "already exists in file " << outputFile << std::endl;
		  std::cout << "will keep the old one!" << std::endl << std::endl;
		}
		saveObject=false;
		break;
	      }
	    }
	  }
	  // save object
	  if(saveObject){
	    if(verbose>0){
	      std::cout << "saving object " << (TString)object->GetTitle();
	      std::cout << " to file " << outputFile;
	      if(folder!="") std::cout << " ( folder " << folder << " )";
	      std::cout << std::endl << std::endl;
	    }
	    // overwrite existing
	    object->Write(object->GetTitle(), TObject::kOverwrite);
	  }
	  // return to main folder
	  for(int nfolder=1; nfolder<=folder.CountChar(*"/")+1; ++nfolder){
	    gDirectory->cd("..");
	  }
	}
      }
      // close file
      file->Close();
    }

  void drawRatio(const TH1* histNumerator, TH1* histDenominator, const Double_t& ratioMin, const Double_t& ratioMax, TStyle myStyle, int verbose=0, const std::vector<double> err_=std::vector<double>(0))
  {
    // this function draws a pad with the ratio of 'histNumerator' and 'histDenominator'
    // the range of the ratio is 'ratioMin' to 'ratioMax'
    // to the systematic variation "sys" of the enumerator "systematicVariation"
    // per default only the gaussian error of the 'histNumerator' is considered:
    // (error(bin i) = sqrt(histNumerator->GetBinContent(i))/histDenominator->GetBinContent(i))
    // if 'err_' is present and its size equals the number of bins in the histos,
    // its valus are considered as error for the ratio
    // NOTE: x Axis is transferred from histDenominator to the bottom of the canvas
    // modified quantities: none
    // used functions: none
    // used enumerators: none

    // check that histos have the same binning
    if(histNumerator->GetNbinsX()!=histDenominator->GetNbinsX()){
      std::cout << "error when calling drawRatio - histos have different number of bins" << std::endl;
      return;
    }
    if(verbose>1){
      std::cout << "building ratio plot of " << histNumerator->GetName();
      std::cout << " and " << histDenominator->GetName() << std::endl;
    }
    // create ratio
    TH1F* ratio = (TH1F*)histNumerator->Clone();
    ratio->Divide(histDenominator);
    // calculate error for ratio
    // a) from err_
    if(err_.size()==(unsigned int)histNumerator->GetNbinsX()){
      if(verbose>0) std::cout << "ratio error from vector" << std::endl;
      for(int bin=1; bin<=histNumerator->GetNbinsX(); bin++){
	ratio->SetBinError(bin, err_[bin-1]);
      }
    }
    else{
      // b) default: only gaussian error of histNumerator
      if(verbose>0) std::cout << "ratio error from statistical error of " << histNumerator->GetName() << " only" << std::endl;
      for(int bin=1; bin<=histNumerator->GetNbinsX(); bin++){
	ratio->SetBinError(bin, sqrt(histNumerator->GetBinContent(bin))/histDenominator->GetBinContent(bin));
      }
    }
    // get some values from old pad
    //Int_t    logx = gPad->GetLogx();
    //Double_t left = gPad->GetLeftMargin();
    //Double_t right = gPad->GetRightMargin();

    Int_t    logx  = myStyle.GetOptLogx();
    Double_t left  = myStyle.GetPadLeftMargin();
    Double_t right = myStyle.GetPadRightMargin();

    // y:x size ratio for canvas
    double canvAsym = 4./3.;
    // ratio size of pad with plot and pad with ratio
    double ratioSize = 0.36;
    // change old pad
    gPad->SetBottomMargin(ratioSize);
    gPad->SetRightMargin(right);
    gPad->SetLeftMargin(left);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(0);
    gPad->SetFillColor(10);
    // create new pad for ratio plot
    TPad *rPad;
    rPad = new TPad("rPad","",0,0,1,ratioSize+0.001);
#ifdef DILEPTON_MACRO
    rPad->SetFillColor(10);
#else
    rPad->SetFillStyle(0);
    rPad->SetFillColor(0);
#endif
    rPad->SetBorderSize(0);
    rPad->SetBorderMode(0);
    rPad->Draw();
    rPad->cd();
    rPad->SetLogy(0);
    rPad->SetLogx(logx);
    rPad->SetTicky(1);
    // configure ratio plot
    double scaleFactor = 1./(canvAsym*ratioSize);
    ratio->SetStats(kFALSE);
    ratio->SetTitle("");
    ratio->SetMaximum(ratioMax);
    ratio->SetMinimum(ratioMin);
    ratio->SetLineWidth(1);
    // configure axis of ratio plot
    ratio->GetXaxis()->SetTitleSize(histDenominator->GetXaxis()->GetTitleSize()*scaleFactor*1.3);
    ratio->GetXaxis()->SetTitleOffset(histDenominator->GetXaxis()->GetTitleOffset()*0.9);
    ratio->GetXaxis()->SetLabelSize(histDenominator->GetXaxis()->GetLabelSize()*scaleFactor*1.4);
    ratio->GetXaxis()->SetTitle(histDenominator->GetXaxis()->GetTitle());
    ratio->GetXaxis()->SetNdivisions(histDenominator->GetNdivisions());
    ratio->GetYaxis()->CenterTitle();
    ratio->GetYaxis()->SetTitle("#frac{N_{data}}{N_{MC}}");
    ratio->GetYaxis()->SetTitleSize(histDenominator->GetYaxis()->GetTitleSize()*scaleFactor);
    ratio->GetYaxis()->SetTitleOffset(histDenominator->GetYaxis()->GetTitleOffset()/scaleFactor);
    ratio->GetYaxis()->SetLabelSize(histDenominator->GetYaxis()->GetLabelSize()*scaleFactor);
    ratio->GetYaxis()->SetLabelOffset(histDenominator->GetYaxis()->GetLabelOffset()*3.3);
    ratio->GetYaxis()->SetTickLength(0.03);
    ratio->GetYaxis()->SetNdivisions(505);
    ratio->GetXaxis()->SetRange(histDenominator->GetXaxis()->GetFirst(), histDenominator->GetXaxis()->GetLast());
    // delete axis of initial plot
    histDenominator->GetXaxis()->SetLabelSize(0);
    histDenominator->GetXaxis()->SetTitleSize(0);
    // draw ratio plot
    ratio->DrawClone("p e X0");
    ratio->SetMarkerSize(1.2);
    ratio->DrawClone("p e X0 same");
    rPad->SetTopMargin(0.0);
    rPad->SetBottomMargin(0.15*scaleFactor);
    rPad->SetRightMargin(right);
    gPad->SetLeftMargin(left);
    gPad->RedrawAxis();
    // draw grid
    rPad->SetGrid(1,1);

    // draw a horizontal lines on a given histogram
    // a) at 1
    Double_t xmin = ratio->GetXaxis()->GetXmin();
    Double_t xmax = ratio->GetXaxis()->GetXmax();
    TString height = ""; height += 1;
    TF1 *f = new TF1("f", height, xmin, xmax);
    f->SetLineStyle(1);
    f->SetLineWidth(1);
    f->SetLineColor(kBlack);
    f->Draw("L same");
    // b) at upper end of ratio pad
    TString height2 = ""; height2 += ratioMax;
    TF1 *f2 = new TF1("f2", height2, xmin, xmax);
    f2->SetLineStyle(1);
    f2->SetLineWidth(1);
    f2->SetLineColor(kBlack);
    f2->Draw("L same");
  }

  double getInclusiveXSec(TH1* hist, int verbose=0)
  {
    // this function integrates a given
    // histogramm 'hist' by summing up the product
    // of binwidth and bincontent for all bins.
    // NOTE: binwidth==0 is treated as binwidth==1
    // modified quantities: none
    // used functions: none
    // used enumerators: none
    double value=0;
    if(verbose>0) std::cout << "histo: " << hist->GetTitle() << std::endl;
    for(int bin=0; bin<=hist->GetNbinsX()+1; ++bin){
      double binWidth=hist->GetBinWidth(bin);
      if(binWidth==0.) binWidth=1.;
      double thisBin=binWidth*hist->GetBinContent(bin);
      value+=thisBin;
      if(verbose>1) std::cout << "xSec bin" << bin << ": " << thisBin << std::endl;
    }
    if(verbose>0) std::cout << "integrated xSec: " << value << std::endl;
    return value;
  }


  void whipEmptyBinsAway(TGraphAsymmErrors* hist, int verbose=0)
  {
    // this function shifts all unset points
    // (at x,y=0,0 with error 0,0)
    // out of sight to 0, -1000
    // modified quantities: none
    // used functions: none
    // used enumerators: none
    if(verbose>1) std::cout << "checking " << hist->GetName() << " for empty bins" << std::endl;
    // loop points
    for(int bin=0; bin<=hist->GetN()-1; ++bin){
      // search for unset points
      if( hist->GetX()[bin]==0 &&
	  hist->GetY()[bin]==0 &&
	  hist->GetErrorXhigh(bin)==0 &&
	  hist->GetErrorXlow (bin)==0 &&
	  hist->GetErrorYhigh(bin)==0 &&
	  hist->GetErrorYlow (bin)==0 ){
	hist->SetPoint(bin, 0, -1000);
	if(verbose>1) std::cout << "bin #" << bin << " set to 0,-1000" << std::endl;
      }
    }
  }

  TH1F* getTheoryPrediction(TString plotName="", TString fileName="")
  {

    // check if input is valid
    if(plotName==""||fileName==""){
      std::cout << "ERROR: no plotName or filename chosen in function getTheoryPrediction" << std::endl;
      exit(0);
    }
    // load file
    TFile* file = new (TFile)(fileName);
    // check if file is valid
    if(file->IsZombie()){
      std::cout << "ERROR: input file " << fileName << " in function getTheoryPrediction is zombie" << std::endl;
      exit(0);
    }
    // get plot
    TH1* targetPlot;
    file->GetObject(plotName, targetPlot);
    // check if plot exists
    if(!targetPlot){
      std::cout << "ERROR in function getTheoryPrediction: plot " << plotName;
      std::cout << " does not exist in file " << fileName << std::endl;
      exit(0);
    }
    gROOT->cd();
    TH1F* result = (TH1F*)(targetPlot->Clone());
    file->Close();
    delete file;
    return result;
  }

  double signum(double value){
    // this function is a
    // simple signum function
    // modified quantities: none
    // used functions: none
    // used enumerators: none

    if(value>0) return  1.0;
    if(value<0) return -1.0;
    return 0;
  }

  void closeStdTopAnalysisFiles(std::map<unsigned int, TFile*> files_)
    {
      // this function closes and deletes the files saved in "files_"
      // modified quantities: files_
      // used functions: NONE
      // used enumerators: NONE

      // close and delete input files
      for(std::map<unsigned int, TFile*>::const_iterator file=files_.begin(); file!=files_.end(); ++file){
	file->second->Close();
	delete file->second;
      }
    }

  void makeUncertaintyBands(std::map< TString, std::map <unsigned int, TH1F*> >& histo_,
			    std::map< TString, TH1F* >& histoErrorBand_,
			    std::vector<TString>& plotList_,
			    unsigned int& Nplots)
  {
    
    for(unsigned int plot=0; plot<Nplots; ++plot){
      
      TString plotName     = plotList_[plot];
      
      // Initialize and reset histograms
      
      TH1F* histoSumRef       = (TH1F*)histo_[plotName][kSig]->Clone();
      TH1F* histoSumTTbarOnly = (TH1F*)histo_[plotName][kSig]->Clone();
      
      histoSumRef       -> Reset("ICESM");
      histoSumTTbarOnly -> Reset("ICESM");
      
      // Integral over all samples before accessing the differences
      
      for(unsigned int sample=kSig; sample<kData; ++sample){

	if((plot<Nplots)&&(plotExists(histo_, plotName, sample))){

	  histoSumRef -> Add(histo_[plotName][sample]);

	  if (sample == kSig || sample == kBkg) 
	    histoSumTTbarOnly -> Add(histo_[plotName][sample]);
	}
      }
      
      // Compare summed histograms, symmetrize deviations and store relative deviation to error histogram after adding constant contributions
      
      double relXSecError = sqrt(pow(ttbarCrossSectionError/ttbarCrossSection,2)-pow(globalLumiUncertainty,2));  // to avoid double counting of luminosity error
      
      for (int bin = 0; bin < histoSumRef->GetNbinsX(); bin++){

	double xSecError       = (histoSumTTbarOnly->GetBinContent(bin+1))*relXSecError;
	double luminosityError = (histoSumRef->GetBinContent(bin+1))*globalLumiUncertainty;
	
	double totalError      = sqrt(xSecError*xSecError+luminosityError*luminosityError);
	
	histoSumRef->SetBinError(bin+1,totalError);
      }
      
      histoErrorBand_[plotName] = (TH1F*)histoSumRef->Clone();
    }
  
  }
  
  void addCanvas(std::vector<TCanvas*> &plotCanvas_){
    // this function adds a new canvas to the vector of canvas "plotCanvas_"
    // modified quantities: plotCanvas_
    // used functions: NONE
    // used enumerators: NONE
    char canvname[10];
    int number =plotCanvas_.size()+1;
    sprintf(canvname,"canv%i",number);    
    plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );
    //canvasStyle(*plotCanvas_[number-1]);
  }

  TH1F* useFittedFunctions(TH1F* input, TString model="", TString plotname="", int verbose=0){
    // this function modifys "input" in a way that wiggly parts 
    // with large uncertainties are replaced by fitted functions
    // modified quantities: input
    // used functions: NONE
    // used enumerators: NONE
    // input: fine binned theory curve
    // model: indicates theory (madgraph, powheg or mcatnalo)
    // verbose: level of output
    int initialIgnoreLevel=gErrorIgnoreLevel;
    if(verbose==0) gErrorIgnoreLevel=kFatal;
    if(verbose>1) std::cout << plotname << "(" << model << ")" << std::endl;
    // clone histo for output
    TH1F* result=(TH1F*)input->Clone();
    // define fit function A
    double fitLowEdge=0;
    double fitHighEdge=0;
    TString def="";
    double a=0.;
    double b=0.;
    double c=0.;
    double d=0.;
    double e=0.;
    TString addOpt="";
    // define fit function B
    double fitLowEdgeB=0;
    double fitHighEdgeB=0;
    TString defB="";
    double aB=0.;
    double bB=0.;
    double cB=0.;
    double dB=0.;
    double eB=0.;
    TString addOptB="";
    // define fit function C
    double fitLowEdgeC=0;
    double fitHighEdgeC=0;
    TString defC="";
    double aC=0.;
    double bC=0.;
    double cC=0.;
    double dC=0.;
    double eC=0.;
    TString addOptC="";
    // configure parameter for all specific plots
    if(model=="mcatnlo"){
      if(plotname.Contains("TTbarM")){
	//tail:
	fitLowEdge=430.;
	fitHighEdge=1200.;
	def="[0]*exp([1]*x)+[2]";
	a=0.11;
	b=-0.0074;
	c=0.00001;
	addOpt="LL";
	// start:
	fitLowEdgeB=345.;
	fitHighEdgeB=400.;
	defB="TMath::GammaDist(x,[0],[1],[2])";
	aB=1.53;
	bB=345.;
	cB=96.2;
	addOptB="LL";
	// very early start:
	fitLowEdgeC=317.;
	fitHighEdgeC=336.;
	defC="[0]*exp([1]*x)+[2]";
	aC=0.00000373757;
	bC=0.0125775;
	cC=-0.000194989;
	addOptC="LL";
      }
      else if(plotname.Contains("TTbarPt")){
	//tail:
	fitLowEdge=50.;
	fitHighEdge=300.;
	def="[0]*exp([1]*x)+[2]*x+[3]*x*x+[4]";
	a= 0.0214186;
	b=-0.0274519;
	c=-0.0000135818;
	d= 0.0000000213453;
	e= 0.00227380;
	addOpt="LL";
      }
     else if(plotname.Contains("TTbarY")){
	fitLowEdge=-1.5;
	fitHighEdge=1.5;
	def="TMath::Exp(x*x*[0]+x*x*x*x*[1]+x*x*x*x*x*x*[2])*[3]";
	a=-0.658848;
	b=-0.0509368;
	c=-0.0320204;
	d=0.00513375;
	addOpt="LL";
      }
     else if(plotname.Contains("TopY")){
       //tail:
       fitLowEdge=-1.;
       fitHighEdge=1.;
       def="[0]*TMath::Gaus(x,0,[1])";
       a=0.00402075;
       b=1.14871;
       addOpt="LL";
     }
     else if(plotname.Contains("LepPt")){
       fitLowEdge=45.;
       fitHighEdge=210.;
       def="TMath::Exp(x*[0]+x*x*[1])*[2]";
       a=-0.0414389;
       b=0.0000334359;
       c=0.133893;
     }
    }
    else if(model=="madgraph"){
      if(plotname.Contains("ttbarMass")){
	//tail:
	fitLowEdge=430.;
	fitHighEdge=1200.;
	def="[0]*exp([1]*x)+[2]";
	a=28165.;
	b=-0.00756;
	c=2.77;
	addOpt="LL";
	// start:
	fitLowEdgeB=345.;
	fitHighEdgeB=400.;
	defB="[3]*TMath::GammaDist(x,[0],[1],[2])";
	aB=1.56;
	bB=344.8;
	cB=80.8;
	dB=216786.;
	addOptB="LL";
      }
      else if(plotname.Contains("ttbarPt")){
	//tail:
	fitLowEdge=50.;
	fitHighEdge=300.;
	def="[0]*exp([1]*x)+[2]*x+[3]*x*x+[4]";
	a= 5180.;
	b=-0.03;
	c=-4.48;
	d= 0.007;
	e= 745.5;
	addOpt="LL";
      }
      else if(plotname.Contains("topY")){
	//tail:
	fitLowEdge=-1.;
	fitHighEdge=1.;
	def="[0]*TMath::Gaus(x,0,[1])";
	a=19845.2;
	b=1.09186;
	addOpt="LL";
      }
      else if(plotname.Contains("ttbarY")){
	fitLowEdge=-1.5;
	fitHighEdge=1.5;
	def="TMath::Exp(x*x*[0]+x*x*x*x*[1]+x*x*x*x*x*x*[2])*[3]";
	a=-0.658848;
	b=-0.0509368;
	c=-0.0320204;
	d=12297.7;
	addOpt="LL";
      }
      else if(plotname.Contains("lepPt")){
	fitLowEdge=45.;
	fitHighEdge=210.;
	def="TMath::Exp(x*[0]+x*x*[1])*[2]";
	a=-0.0414389;
	b=0.0000334359;
	c=0.133893;
      }
    }
    else if(model=="powheg"){
      if(plotname.Contains("ttbarMass")){
      fitLowEdge=480.;
      fitHighEdge=1200.;
      def="[0]*exp([1]*x)+[2]";
      a=40556.;
      b=-0.007;
      c=3.1;
      addOpt="LL";
      // start:
      fitLowEdgeB=345.;
      fitHighEdgeB=500.;
      defB="[3]*TMath::GammaDist(x,[0],[1],[2])";
      aB=1.58;
      bB=344.;
      cB=86.6;
      dB=234473.;
      addOptB="LL";
      // very early start:
      fitLowEdgeC=295.;
      fitHighEdgeC=337.;
      defC="[0]*exp([1]*x)+[2]";
      aC=0.000000000530501;
      bC=0.075;
      cC=3.81;
      addOptC="LL";
      }
      else if(plotname.Contains("ttbarPt")){
	//tail:
	fitLowEdge=50.;
	fitHighEdge=300.;
	def="[0]*exp([1]*x)+[2]*x+[3]*x*x+[4]";
	a= 5180.;
	b=-0.03;
	c=-4.48;
	d= 0.007;
	e= 745.5;
	addOpt="LL";
      }
     else if(plotname.Contains("ttbarY")){
	fitLowEdge=-1.5;
	fitHighEdge=1.5;
	def="TMath::Exp(x*x*[0]+x*x*x*x*[1]+x*x*x*x*x*x*[2])*[3]";
	a=-0.598570;
	b=-0.120246;
	c=-0.00770785;
	d=12987.6;
	addOpt="LL";
      }
     else if(plotname.Contains("lepPt")){
       fitLowEdge=45.;
       fitHighEdge=210.;
       def="TMath::Exp(x*[0]+x*x*[1])*[2]";
       a=-0.0414389;
       b=0.0000334359;
       c=0.133893;
     }
    }
    // use fit function A
    if(def!=""&&fitLowEdge!=fitHighEdge){
      if(verbose>0) std::cout << "will perform fit" << std::endl;
      // empty bins within fit range for output histo
      bool lastBin=false;
      for(int bin=1; bin<=result->GetNbinsX()+1; ++bin){
	bool thisBin=false;
	double binX=result->GetBinCenter(bin);
	if(binX>=fitLowEdge&&binX<=fitHighEdge){ 
	  result->SetBinContent(bin, 0.);
	  thisBin=true;
	}
	// adapt fit range to binning
	// low
	if(lastBin==false&&thisBin==true) fitLowEdge=result->GetBinLowEdge(bin);
	// high
	if(lastBin==true&&thisBin==false) fitHighEdge=result->GetBinLowEdge(bin);	
	lastBin=thisBin;
      }
      if(verbose>0){
	std::cout << "fitting " << def << " in: " << fitLowEdge << ".." << fitHighEdge << std::endl;
	if(a!=0) std::cout << "start value [0]:" << a << std::endl;
	if(b!=0) std::cout << "start value [1]:" << b << std::endl;
	if(c!=0) std::cout << "start value [2]:" << c << std::endl;
	if(d!=0) std::cout << "start value [3]:" << d << std::endl;
	if(e!=0) std::cout << "start value [4]:" << e << std::endl;
      }
      // perform fit
      TF1* function=new TF1("function",def,fitLowEdge, fitHighEdge);
      if(a!=0.){
	function->SetParameter(0,a);
	//if(def.Contains("GammaDist")) function->SetParLimits(0,0.6*a,1.4*a);
      }
      if(b!=0.){
	function->SetParameter(1,b);
	if(def.Contains("GammaDist")) function->SetParLimits(1,0.85*b,1.15*b);
      }
      if(c!=0.){
	function->SetParameter(2,c);
	//if(def.Contains("GammaDist")) function->SetParLimits(2,0.6*c,1.4*c);
      }
      if(d!=0.){
	function->SetParameter(3,d);
	//if(def.Contains("GammaDist")) function->SetParLimits(3,0.6*d,1.4*d);
      }
      if(e!=0.){
	function->SetParameter(4,e);
	//if(def.Contains("GammaDist")) function->SetParLimits(4,0.6*e,1.4*e);
      }
      TString option="Q";
      if(verbose>0)option="";
      if(verbose>1)option="V";
      option+="N";
      option+=addOpt;
      option+="R";
      //option+="M";
      input->Fit(function,option,"same",fitLowEdge, fitHighEdge);
      // add part from fit
      result->Add(function);
    }
    // use fit function B
    if(defB!=""&&fitLowEdgeB!=fitHighEdgeB){
      if(verbose>0) std::cout << "will perform fit" << std::endl;
      // empty bins within fit range for output histo
      bool lastBin=false;
      for(int bin=1; bin<=result->GetNbinsX()+1; ++bin){
	bool thisBin=false;
	double binX=result->GetBinCenter(bin);
	if(binX>=fitLowEdgeB&&binX<=fitHighEdgeB){ 
	  result->SetBinContent(bin, 0.);
	  thisBin=true;
	}
	// adapt fit range to binning
	// low
	if(lastBin==false&&thisBin==true) fitLowEdgeB=result->GetBinLowEdge(bin);
	// high
	if(lastBin==true&&thisBin==false) fitHighEdgeB=result->GetBinLowEdge(bin);	
	lastBin=thisBin;
      }
      if(verbose>0){
	std::cout << "fitting " << defB << " in: " << fitLowEdgeB << ".." << fitHighEdgeB << std::endl;
	if(aB!=0) std::cout << "start value [0]:" << aB << std::endl;
	if(bB!=0) std::cout << "start value [1]:" << bB << std::endl;
	if(cB!=0) std::cout << "start value [2]:" << cB << std::endl;
	if(dB!=0) std::cout << "start value [3]:" << dB << std::endl;
	if(eB!=0) std::cout << "start value [4]:" << eB << std::endl;
      }
      // perform fit
      TF1* functionB=new TF1("functionB",defB,fitLowEdgeB, fitHighEdgeB);
      if(aB!=0.){
	functionB->SetParameter(0,aB);
	if(defB.Contains("GammaDist")){
	  if(aB<0.)functionB->SetParLimits(0,1.4*aB,0.6*aB);
	  if(aB>0.)functionB->SetParLimits(0,0.6*aB,1.4*aB);	  
	}
      }
      if(bB!=0.){
	functionB->SetParameter(1,bB);
	if(defB.Contains("GammaDist")){
	  if(bB<0.) functionB->SetParLimits(1,1.15*bB,0.85*bB);
	  if(bB>0.) functionB->SetParLimits(1,0.85*bB,1.15*bB);
	}
      }
      if(cB!=0.){
	functionB->SetParameter(2,cB);
	if(defB.Contains("GammaDist")){
	  if(cB<0.) functionB->SetParLimits(2,1.4*cB,0.6*cB);
	  if(cB>0.) functionB->SetParLimits(2,0.6*cB,1.4*cB);
	}
      }
      if(dB!=0.){
	functionB->SetParameter(3,dB);
	if(defB.Contains("GammaDist")){
	  if(dB<0.) functionB->SetParLimits(3,1.4*dB,0.6*dB);
	  if(dB>0.) functionB->SetParLimits(3,0.6*dB,1.4*dB);
	}
      }
      if(eB!=0.){
	functionB->SetParameter(4,eB);
	if(defB.Contains("GammaDist")){
	  if(eB<0.) functionB->SetParLimits(4,1.4*eB,0.6*eB);
	  if(eB>0.) functionB->SetParLimits(4,0.6*eB,1.4*eB);
	}
      }
      TString option="Q";
      if(verbose>0)option="";
      if(verbose>1)option="V";
      option+="N";
      option+=addOptB;
      option+="R";
      //option+="M";
      input->Fit(functionB,option,"same",fitLowEdgeB, fitHighEdgeB);
      // add part from fit
      result->Add(functionB);
    }
   // use fit function C
    if(defC!=""&&fitLowEdgeC!=fitHighEdgeC){
      if(verbose>0) std::cout << "will perform fit" << std::endl;
      // empty bins within fit range for output histo
      bool lastBin=false;
      for(int bin=1; bin<=result->GetNbinsX()+1; ++bin){
	bool thisBin=false;
	double binX=result->GetBinCenter(bin);
	if(binX>=fitLowEdgeC&&binX<=fitHighEdgeC){ 
	  result->SetBinContent(bin, 0.);
	  thisBin=true;
	}
	// adapt fit range to binning
	// low
	if(lastBin==false&&thisBin==true) fitLowEdgeC=result->GetBinLowEdge(bin);
	// high
	if(lastBin==true&&thisBin==false) fitHighEdgeC=result->GetBinLowEdge(bin);	
	lastBin=thisBin;
      }
      if(verbose>0){
	std::cout << "fitting " << defC << " in: " << fitLowEdgeC << ".." << fitHighEdgeC << std::endl;
	if(aC!=0) std::cout << "start value [0]:" << aC << std::endl;
	if(bC!=0) std::cout << "start value [1]:" << bC << std::endl;
	if(cC!=0) std::cout << "start value [2]:" << cC << std::endl;
	if(dC!=0) std::cout << "start value [3]:" << dC << std::endl;
	if(eC!=0) std::cout << "start value [4]:" << eC << std::endl;
      }
      // perform fit
      TF1* functionC=new TF1("functionC",defC,fitLowEdgeC, fitHighEdgeC);
      if(aC!=0.){
	functionC->SetParameter(0,aC);
	if(defC.Contains("GammaDist")) functionC->SetParLimits(0,0.6*aC,1.4*aC);
      }
      if(bC!=0.){
	functionC->SetParameter(1,bC);
	if(defC.Contains("GammaDist")) functionC->SetParLimits(1,0.85*bC,1.15*bC);
      }
      if(cC!=0.){
	functionC->SetParameter(2,cC);
	if(defC.Contains("GammaDist")) functionC->SetParLimits(2,0.6*cC,1.4*cC);
      }
      if(dC!=0.){
	functionC->SetParameter(3,dC);
	if(defC.Contains("GammaDist")) functionC->SetParLimits(3,0.6*dC,1.4*dC);
      }
      if(eC!=0.){
	functionC->SetParameter(4,eC);
	if(defC.Contains("GammaDist")) functionC->SetParLimits(4,0.6*eC,1.4*eC);
      }
      TString option="Q";
      if(verbose>0)option="";
      if(verbose>1)option="V";
      option+="N";
      option+=addOptC;
      option+="R";
      //option+="M";
      input->Fit(functionC,option,"same",fitLowEdgeC, fitHighEdgeC);
      // add part from fit
      result->Add(functionC);
    }
    gErrorIgnoreLevel=initialIgnoreLevel;
    // return result
    return result;
  }

  void DrawNormTheoryCurve(TString filename="", TString plotname="", int smoothFactor=0, int rebinFactor=0, int color=kBlack, int linestyle=1, double rangeLow=-1., double rangeHigh=-1., bool errorbands=false, int errorRebinFactor=0, int errorSmoothFactor=0, int verbose=0, bool drawOnlyErrors=false, bool drawRawPlot=false, TString model="")
  {
    // this function draws "plot" from "file" into the active canvas
    // modified quantities: NONE
    // used functions: getTheoryPrediction, histogramStyle, useFittedFunctions
    // used enumerators: NONE
    // filename: name of input file
    // plotname: name of histogram
    // smoothFactor: argument of ->Smooth()
    // rebinFactor:  argument of ->Rebin()
    // color: color of histogram
    // rangeLow:  lower plot range of histo
    // rangeHigh: upper plot range of histo
    // errorbands: additional errorbands are calculated and drawn
    // INFORMATION: if errorbands==true is chosen, the varied up/down plots are expected
    //              to have the same name with an additional "_Up"/"_Down" in the end
    // errorRebinFactor: argument of ->Rebin()
    // errorSmoothFactor: argument of ->Smooth()
    // verbose: level of output
    // drawOnlyErrors: draw only error bands but no central curve
    // drawRawPlot: draw in addition the unbinned and unsmoothed plot 
    //              to see whether rebinning and smoothing has changed the shape 
    // model: indicates theory (madgraph, powheg or mcatnalo)

    // output
    if(verbose>0){
      std::cout << "variable: " << plotname << std::endl;
      if(rangeLow!=-1.||rangeHigh!=-1.) std::cout << "range: " << rangeLow << ".." << rangeHigh << std::endl;
      std::cout << "file: " << filename << std::endl;
      std::cout << "smoothFactor: " << smoothFactor << std::endl;
      std::cout << "rebinFactor: " << rebinFactor << std::endl;
      std::cout << "color: " << color << std::endl;
      std::cout << "draw errorbands? " << errorbands << std::endl;
      if(errorbands){
	std::cout << "errorRebinFactor: " << errorRebinFactor << std::endl;
	std::cout << "errorSmoothFactor: " << errorSmoothFactor << std::endl;
      }
    }
    // draw raw plot to estimate effect of rebinning and smoothing
    if(drawRawPlot){
      TH1F* raw=getTheoryPrediction(plotname, filename);
      // add muon and electron channel to
      // minimize statistical fluctuations
      if(model=="madgraph"){
	TString filenameEl = filename;
	filenameEl.ReplaceAll("muon", "elec");
	raw->Add(getTheoryPrediction(plotname, filenameEl));
      }
      raw->SetMarkerColor(color);
      raw->SetLineColor(color);
      //raw->SetMarkerSize(2);
      //raw->SetMarkerStyle(29);
      raw->Scale(1./(raw->Integral(0,raw->GetNbinsX()+1)));
      raw->Scale(1./(raw->GetBinWidth(1)));
      raw->Draw("c same"); 
    }
    // get plot
    TH1F* result=getTheoryPrediction(plotname, filename);
    // add muon and electron channel to
    // minimize statistical fluctuations
    if(model=="madgraph"){
      TString filenameEl = filename;
      filenameEl.ReplaceAll("muon", "elec");
      result->Add(getTheoryPrediction(plotname, filenameEl));
    }
    // replace low statistic parts with fitted curve
    result=useFittedFunctions(result, model, plotname, verbose);
    // rename
    TString name=plotname;
    name.ReplaceAll("analyzeTopPartonLevelKinematicsPhaseSpace/","");
    if(model=="powheg") name+="POWHEG";
    else if(model=="mcatnlo"){
      if(filename.Contains("mcatnlo" )) name+="MC@NLO";
      else if(filename.Contains("NtupleCteq6m" )) name+="MC@NLO2";
    }
    else if(model=="madgraph") name+="MADGRAPH";
    if(verbose>0) std::cout << "name of theory curve: " << name << std::endl;
    result->SetName(name);
    // configure style
    histogramStyle(*result, kSig, false, 1.2, color);
    result->SetLineStyle(linestyle);
    // smoothing 1
    if(smoothFactor) result->Smooth(smoothFactor);
    // rebinning
    if(rebinFactor) result->Rebin(rebinFactor);
    // normalize to area
    result->Scale(1./(result->Integral(0,result->GetNbinsX()+1)));
    // divide by binwidth
    result->Scale(1.0/result->GetBinWidth(1));
    // smoothing 2
    if(smoothFactor) result->Smooth(smoothFactor);
    // set range
    if(rangeLow!=-1.&&rangeHigh!=-1.) result->GetXaxis()->SetRangeUser(rangeLow, rangeHigh);
    // error bands
    if(errorbands){
      // get values
      TH1F* central   =getTheoryPrediction(plotname        , filename);
      TH1F* ErrorUp   =getTheoryPrediction(plotname+"_Up"  , filename);
      TH1F* ErrorDown =getTheoryPrediction(plotname+"_Down", filename);
      // replace low statistic parts with fitted curve
      central=useFittedFunctions(central, model, plotname, verbose);
      ErrorUp=useFittedFunctions(ErrorUp, model, plotname+"_Up", verbose);
      ErrorDown=useFittedFunctions(ErrorDown, model, plotname+"_Down", verbose);
      // smoothing 1
      if(errorSmoothFactor){
	central  ->Smooth(errorSmoothFactor);
	ErrorUp  ->Smooth(errorSmoothFactor);
	ErrorDown->Smooth(errorSmoothFactor);
      }
      // rebinning
      if(errorRebinFactor){ 
	central  ->Rebin(errorRebinFactor);
	ErrorUp  ->Rebin(errorRebinFactor);
	ErrorDown->Rebin(errorRebinFactor);
      }
      // normalize to area
      central  ->Scale(1./(central  ->Integral(0,central  ->GetNbinsX()+1)));
      ErrorUp  ->Scale(1./(central  ->Integral(0,central  ->GetNbinsX()+1)));
      ErrorDown->Scale(1./(central  ->Integral(0,central  ->GetNbinsX()+1)));
      // divide by binwidth
      central  ->Scale(1.0/central  ->GetBinWidth(1));
      ErrorUp  ->Scale(1.0/ErrorUp  ->GetBinWidth(1));
      ErrorDown->Scale(1.0/ErrorDown->GetBinWidth(1));
      // smoothing 2
      if(errorSmoothFactor){
	central  ->Smooth(errorSmoothFactor);
	ErrorUp  ->Smooth(errorSmoothFactor);
	ErrorDown->Smooth(errorSmoothFactor);
      }
      // create errorbands
      TGraphAsymmErrors * errorBands = new TGraphAsymmErrors(central->GetNbinsX()-1);
      TString errorBandName=name;
      errorBandName.ReplaceAll("2","");
      errorBandName+="errorBand";
      if(verbose>0) std::cout << "name of error bands: " << errorBandName << std::endl;
      errorBands->SetName(errorBandName);
      // loop bins
      for(Int_t iBin=1; iBin<central->GetNbinsX(); iBin++){
	Double_t centralValue = central  ->GetBinContent(iBin);
	Double_t maxValue     = ErrorUp  ->GetBinContent(iBin);
	Double_t minValue     = ErrorDown->GetBinContent(iBin);
	// take care of points outside x-plotrange
	if((rangeLow!=-1.&&central->GetBinCenter(iBin)<rangeLow)||(rangeHigh!=-1.&&central->GetBinCenter(iBin)>rangeHigh)){
	  errorBands->SetPoint      (iBin, central->GetBinCenter(iBin), 0.);
	  errorBands->SetPointEXlow (iBin, 0.);
	  errorBands->SetPointEXhigh(iBin, 0.);
	}
	else {
	  errorBands->SetPoint      (iBin, central->GetBinCenter(iBin), centralValue  );
	  errorBands->SetPointEXlow (iBin, central->GetXaxis()->GetBinLowEdge(iBin)   );
	  errorBands->SetPointEXhigh(iBin, central->GetXaxis()->GetBinUpEdge (iBin)   );
	}
	// symmetrize errors 
	//double difference=std::abs((maxValue-minValue)*0.5);
	//if((maxValue>centralValue&&minValue>centralValue)||(maxValue<centralValue&&minValue<centralValue)){
	//  difference=(std::abs((maxValue-centralValue))+std::abs((minValue-centralValue)))*0.5;
	//}
	if((maxValue>centralValue&&minValue>centralValue)||(maxValue<centralValue&&minValue<centralValue)){
	  double larger = (minValue > maxValue) ? minValue : maxValue;
	  maxValue=larger;
	  minValue=centralValue - (larger - centralValue); 
	}
	errorBands->SetPointEYhigh(iBin, maxValue-centralValue);
	errorBands->SetPointEYlow (iBin, centralValue-minValue);
	// per bin output
	if(verbose>1){
	  std::cout << "bin " << iBin << std::endl;
	  std::cout << "central TH1: " << std::endl;
	  std::cout << "(<x>,y)= (" << result->GetBinCenter(iBin) << "," << result->GetBinContent(iBin) << ")" << std::endl;
	  std::cout << "error input:" << std::endl;
	  std::cout << "central, min, max: " << central->GetBinContent(iBin);
	  std::cout << ", " << ErrorDown->GetBinContent(iBin) << ", ";
	  std::cout <<  ErrorUp->GetBinContent(iBin) << std::endl;
	  std::cout << "error band" << std::endl;
	  std::cout << "(x,y): (" << *errorBands->GetX() << "," << *errorBands->GetY() << ")" << std::endl;
	  std::cout << "error xlow:  " << errorBands->GetErrorXlow(iBin)  << std::endl;
	  std::cout << "error xhigh: " << errorBands->GetErrorXhigh(iBin) << std::endl;
	  std::cout << "error ylow:  " << errorBands->GetErrorYlow(iBin)  << std::endl;
	  std::cout << "error yhigh: " << errorBands->GetErrorYhigh(iBin) << std::endl;
	}
      }
      // plotstyle for error bands
      errorBands->SetFillColor(kGray);
      errorBands->SetFillStyle(1001); // NB: explicitly needed, otherwise filling invisible due to default "0"
      errorBands->SetLineColor  (result->GetLineColor());
      errorBands->SetLineWidth  (result->GetLineWidth());
      errorBands->SetMarkerColor(result->GetMarkerColor());
      // draw error bands
      errorBands->Draw("e3 same");
    }
    //draw central value
    if(!drawOnlyErrors) result->Draw("hist c same"); 
  }

  double regParameter(TString variable, TString decayChannel, int verbose=0, bool tau=false){
    // this function returns k/value for SVD 
    // unfolding for the corresponding variable
    // modified quantities: NONE
    // used functions: NONE
    // used enumerators: NONE
    // variable: name of variable
    // verbose: level of output
    
    // NB: k-value should be independent from decay channel
    // NB: at the moment k=N(bins) is used!
    double k=-1.;
    if(     variable.Contains("ttbarMass")){ 
      if(decayChannel.Contains("muon")){
	k=5; 
	// Optimal Tau
	if(tau) k=1.35725;
      }
      else if(decayChannel.Contains("electron")){
	k=5; 
	// Optimal Tau
	if(tau) k=1.42188 ;
      }
    }
    else if(variable.Contains("ttbarPt"  )){ 
      if(decayChannel.Contains("muon")){
	k=5; 
	// Optimal Tau
	if(tau) k=1.22257;
      }
      else if(decayChannel.Contains("electron")){
	k=5; 
	// Optimal Tau
	if(tau) k=1.28078 ;
      }
    }
    else if(variable.Contains("ttbarY"   )){ 
      if(decayChannel.Contains("muon")){
	k=8; 
	// Optimal Tau
	if(tau) k=1.22837;
      }
      else if(decayChannel.Contains("electron")){
	k=8; 
	// Optimal Tau
	if(tau) k=1.28686;
      }
    }
    else if(variable.Contains("topPt"    )){ 
      if(decayChannel.Contains("muon")){
	k=5; 
	// Optimal Tau
	if(tau) k=2.16919;
      }
      else if(decayChannel.Contains("electron")){
	k=5; 
	// Optimal Tau
	if(tau) k=2.49404;
      }
    }
    else if(variable.Contains("topY"     )){ 
      if(decayChannel.Contains("muon")){
	k=8; 
	// Optimal Tau
	if(tau) k=1.87786;
      }
      else if(decayChannel.Contains("electron")){
	k=8; 
	// Optimal Tau
	if(tau) k=1.79251;
      }
    }
    else if(variable.Contains("lepPt"    )){ 
      if(decayChannel.Contains("muon")){
	k=13;
	// Optimal Tau
	if(tau) k=0.240889;
      }
      else if(decayChannel.Contains("electron")){
	k=13; 
	// Optimal Tau
	if(tau) k=0.22994;
      }
    }
    else if(variable.Contains("lepEta"   )){ 
      if(decayChannel.Contains("muon")){
	k=14;
	// Optimal Tau
	if(tau) k=0.599823;
      }
      else if(decayChannel.Contains("electron")){
	k=14; 
	// Optimal Tau
	if(tau) k=0.475349;
      }
    }
    else if(variable.Contains("bqPt"     )){ 
      if(decayChannel.Contains("muon")){
	k=5; 
	// Optimal Tau
	if(tau) k=1.26626;
      }
      else if(decayChannel.Contains("electron")){
	k=5; 
	// Optimal Tau
	if(tau) k=1.45589;
      }
    }
    else if(variable.Contains("bqEta"    )){ 
      if(decayChannel.Contains("muon")){
	k=8; 
	// Optimal Tau
	if(tau) k=1.59257;
      }
      else if(decayChannel.Contains("electron")){
	k=8; 
	// Optimal Tau
	if(tau) k=1.6684;
      }
    }
    // output
    if(verbose>1){
      if(tau) std::cout << "tau";
      else std::cout << "k";
      std::cout << "(" << variable << ") = " << k << std::endl;
    }
    // check result
    if(k<0.){
      std::cout << "ERROR in regParameter:" << std::endl; 
      std::cout << "invalid k=" << k << " for variable " << variable << std::endl;
      std::cout << "unknown variable " << variable << " or decayChannel " << decayChannel << std::endl;
    }
    // return result
    return k;
  }

#ifdef DILEPTON_MACRO
}
#endif

#endif
