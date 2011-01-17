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

enum styles              {kDiBos, kSig,   kBkg,   kZjets,   kSTops  , kSTopt  , kSToptW , kWjets,   kQCD,    kData,  kLepJets, kAllMC, kSTop   , kABCD,  kGenSig, kGenBkg, kGenW, kGenSTop, kGenSTops, kGenSTopt, kGenSToptW};
int color_      [ 14 ] = {10,     kRed+1, kRed-7, kAzure-2, kMagenta, kMagenta, kMagenta, kGreen-3, kYellow, kBlack, kRed,     kBlack, kMagenta, kBlack, };
int markerStyle_[ 14 ] = {28,     20,     22,     29,       27      , 27      , 27      , 23,       21,      20,     23,       23,     27      , 22,     };

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
    if(sampleTyp==kDiBos){
      hist.SetLineColor(kGray);
      hist.SetMarkerColor(kGray);
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
  
double getMaxValue(TH1& histo, const TString variable = "", bool systematics = false, const TString plot = "", const int jetMultiplicity = 6, TString up = "JES105", TString down = "JES095"){
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
  if(variable=="Njets")lastBin=4;
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
      double std        = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdSampleWeightStd.txt" );
      double lumiUp     = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiUpEffStdSampleWeightStd.txt"      );
      double lumiDown   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiDownEffStdSampleWeightStd.txt"    );
      double MG         = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdSampleWeightStd.txt" );
      double JESUp      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMC"+up+"LumiNominalEffStdSampleWeightStd.txt");
      double JESDown    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMC"+down+"LumiNominalEffStdSampleWeightStd.txt");
      double JERUp      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCJERupLumiNominalEffStdSampleWeightStd.txt");
      double JERDown    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCJERdownLumiNominalEffStdSampleWeightStd.txt");
      double EffUp      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffUpSampleWeightStd.txt"  );
      double EffDown    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffDownSampleWeightStd.txt");
      double QCDUp      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdQCDestimationUp.txt"  );
      double QCDDown    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdQCDestimationDown.txt");
      double WUp        = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdWjetsEstimationUp.txt"  );
      double WDown      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdWjetsEstimationDown.txt");
      double PileUp     = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCPileUpLumiNominalEffStdSampleWeightStd.txt");
      double ScaleUpV   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCScaleUpVonlyLumiNominalEffStdSampleWeightStd.txt");
      double ScaleUpT   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCScaleUpTTonlyLumiNominalEffStdSampleWeightStd.txt");
      double ScaleDownV = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCScaleDownVonlyLumiNominalEffStdSampleWeightStd.txt");
      double ScaleDownT = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCScaleDownTTonlyLumiNominalEffStdSampleWeightStd.txt");
      double MatchUpV   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCMatchUpVonlyLumiNominalEffStdSampleWeightStd.txt");
      double MatchUpT   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCMatchUpTTonlyLumiNominalEffStdSampleWeightStd.txt");
      double MatchDownV = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCMatchDownVonlyLumiNominalEffStdSampleWeightStd.txt");
      double MatchDownT = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCMatchDownTTonlyLumiNominalEffStdSampleWeightStd.txt");
      double ISRFSRUpT  = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCISRFSRupTTonlyLumiNominalEffStdSampleWeightStd.txt");
      double ISRFSRDownT= readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCISRFSRdownTTonlyLumiNominalEffStdSampleWeightStd.txt");
      double sTopUp     = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdsTopEstimationUp.txt"  );
      double sTopDown   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdsTopEstimationDown.txt");
      double DiBosUp    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdDiBosEstimationUp.txt"  );
      double DiBosDown  = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdDiBosEstimationDown.txt");
      double ZjetsUp    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdZjetsEstimationUp.txt"  );
      double ZjetsDown  = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdZjetsEstimationDown.txt");
      // calculate and print out all systematic errors
      double JESError  = ( std::abs(JESUp-std ) + std::abs(JESDown-std ) ) / 2.0;
      double JERError  = ( std::abs(JERUp-std ) + std::abs(JERDown-std ) ) / 2.0;
      double LumiError = ( std::abs(lumiUp-std) + std::abs(lumiDown-std) ) / 2.0;
      double EffError  = ( std::abs(EffUp-std ) + std::abs(EffDown-std ) ) / 2.0;
      double TopMCError= std::abs(MG-std);
      double QCDError=   ( std::abs(QCDUp-std ) + std::abs(QCDDown-std ) ) / 2.0;
      double WError=   ( std::abs(WUp-std ) + std::abs(WDown-std ) ) / 2.0;
      double sTopError=   ( std::abs(sTopUp-std ) + std::abs(sTopDown-std ) ) / 2.0;
      double DiBosError=   ( std::abs(DiBosUp-std ) + std::abs(DiBosDown-std ) ) / 2.0;
      double ZjetsError=   ( std::abs(ZjetsUp-std ) + std::abs(ZjetsDown-std ) ) / 2.0;
      double PileUpError =  std::abs(PileUp-std);
      double ScaleVError=   ( std::abs(ScaleUpV-std ) + std::abs(ScaleDownV-std ) ) / 2.0;
      double ScaleTError=   ( std::abs(ScaleUpT-std ) + std::abs(ScaleDownT-std ) ) / 2.0;
      double ScaleError= std::sqrt( ScaleVError*ScaleVError + ScaleTError*ScaleTError );
      double MatchVError=   ( std::abs(MatchUpV-std ) + std::abs(MatchDownV-std ) ) / 2.0;
      double MatchTError=   ( std::abs(MatchUpT-std ) + std::abs(MatchDownT-std ) ) / 2.0;
      double MatchError= std::sqrt( MatchVError*MatchVError + MatchTError*MatchTError );
      double ISRFSRError=   ( std::abs(ISRFSRUpT-std ) + std::abs(ISRFSRDownT-std ) ) / 2.0;
      // calculate the combined systematic error
      double sysError=sqrt(JESError*JESError+JERError*JERError+LumiError*LumiError+TopMCError*TopMCError+EffError*EffError+QCDError*QCDError+WError*WError+sTopError*sTopError+DiBosError*DiBosError+ZjetsError*ZjetsError+PileUpError*PileUpError+ScaleError*ScaleError+MatchError*MatchError+ISRFSRError*ISRFSRError);
      // combine systematic and statistic error, add bin content and compare with other bins
      double combinedError = sqrt(statError*statError+sysError*sysError);
      value = histo.GetBinContent(bin)+combinedError;
    }
    else value = histo.GetBinContent(bin)+statError;
    if(value>maxValue)maxValue=value;
  }
  return maxValue;
}

double canvAsym = 4./3.;
double ratioSize = 0.36;

void ratio_smal(TH1* hist1,TH1* hist2,Double_t max,Double_t min,std::vector<double> statErr)
{
  Int_t logx = gPad->GetLogx();
  Double_t left = gPad->GetLeftMargin();
  Double_t right = gPad->GetRightMargin();
  //Double_t bottom = gPad->GetBottomMargin();
  //Int_t logy = gPad->GetLogy();

  //  Double_t xmin = hist1->GetXaxis()->GetXmin();
  //  Double_t xmax = hist1->GetXmax();
  //  cout << hist1->GetName() <<  "  xmin " << xmin << endl;

  TH1F* ratio = (TH1F*)hist1->Clone();
  ratio->Divide(hist1,hist2, 1.0, 1.0);
  TH1F* ratio2 = (TH1F*)ratio->Clone();

  for(int i=1; i<=hist1->GetNbinsX(); i++)
    {
      ratio->SetBinError(i,statErr[i-1]/hist2->GetBinContent(i));
    }
  for(int i=1; i<=hist1->GetNbinsX(); i++)
   {
     ratio2->SetBinError(i,hist1->GetBinError(i)/hist2->GetBinContent(i));
   }

  //gPad->SetTopMargin(0.06);
  gPad->SetBottomMargin(ratioSize);
  gPad->SetRightMargin(right);
  gPad->SetLeftMargin(left);
  gPad->SetBorderMode(0);
  gPad->SetBorderSize(0);
  gPad->SetFillColor(10);


  TPad *rPad;
  rPad = new TPad("rPad","",0,0,1,ratioSize+0.001);
  rPad->SetFillStyle(0);
  rPad->SetFillColor(0);
  rPad->SetBorderSize(0);
  rPad->SetBorderMode(0);
  rPad->Draw();
  rPad->cd();
  rPad->SetLogy(0);
  rPad->SetLogx(logx);
  rPad->SetTicky(1);

  ratio->SetTitle("");
  ratio->SetMaximum(max);
  ratio->SetMinimum(min);
  //  ratio->GetXaxis()->SetNdivisions(505);
  ratio->GetYaxis()->SetNdivisions(505);

  ratio->SetLineWidth(1);

  double scaleFactor = 1./(canvAsym*ratioSize);//(canvAsym/(1-ratioSize));

  ratio->SetStats(kFALSE);
//   ratio->GetXaxis()->SetTitle(x_Axis);
  ratio->GetXaxis()->SetTitleSize(hist1->GetXaxis()->GetTitleSize()*scaleFactor);
  ratio->GetXaxis()->SetTitleOffset(hist1->GetXaxis()->GetTitleOffset());
  ratio->GetXaxis()->SetLabelSize(hist1->GetXaxis()->GetLabelSize()*scaleFactor);
  ratio->GetYaxis()->CenterTitle();
  //ratio->GetYaxis()->SetTitle("ratio");
  //ratio->GetYaxis()->SetTitle("#frac{Data}{MC}");
  ratio->GetYaxis()->SetTitle("Data/MC");
  ratio->GetYaxis()->SetTitleSize(hist1->GetYaxis()->GetTitleSize()*scaleFactor);
  ratio->GetYaxis()->SetTitleOffset(hist1->GetYaxis()->GetTitleOffset()/scaleFactor);
  ratio->GetYaxis()->SetLabelSize(hist1->GetYaxis()->GetLabelSize()*scaleFactor); // 0.06
  ratio->GetYaxis()->SetLabelOffset(hist1->GetYaxis()->GetLabelOffset()*3.4);
  ratio->GetYaxis()->SetTickLength(0.03);
  hist1->GetXaxis()->SetLabelSize(0);
  hist1->GetXaxis()->SetTitleSize(0);
  ratio->SetMarkerSize(0.1);
  ratio->DrawClone("pe1 X0");
  ratio->SetMarkerSize(1.8);
  ratio->DrawClone("pe1 X0 same");
  ratio2->SetMarkerSize(0.1);
  ratio2->DrawClone("pe X0 same");
  ratio2->SetMarkerSize(1.8);
  ratio2->DrawClone("pe X0 same");

  //TF1* fitFunction = new TF1("fitFunction","[0]*TMath::Power([1],x)");
  //TF1* fitFunction = new TF1("fitFunction","pol1");
  //fitFunction->SetParameter(0,1);
  //fitFunction->SetParameter(1,1);
  //fitFunction->SetRange(1,3);
  //ratio2->Fit("fitFunction","QR0");
  //fitFunction->SetRange(1,4);
  //fitFunction->Draw("same");
/*   error1->SetFillColor(kYellow-9); */
/*   error1->SetLineWidth(0); */
/*   error1->SetLineColor(0); */
/*   error2->SetFillColor(10); */
/*   error2->SetLineWidth(0); */
/*   error2->SetLineColor(0); */
/*   error1->DrawCopy("same"); */
/*   error2->DrawCopy("same"); */
/*   ratio->DrawCopy("hist same"); */
  //rPad->SetTopMargin(0.03);
  rPad->SetTopMargin(0.0);
  //  rPad->SetBottomMargin(0.17);
  rPad->SetBottomMargin(0.15*scaleFactor);
  rPad->SetRightMargin(right);
  gPad->SetLeftMargin(left);
  gPad->RedrawAxis();

  //
  // draw a horizontal line on a given histogram
  //
  Double_t xmin = ratio->GetXaxis()->GetXmin();
  Double_t xmax = ratio->GetXaxis()->GetXmax();
  TString height = ""; height += 1;
  TF1 *f = new TF1("f", height, xmin, xmax);
  f->SetLineStyle(1);
  f->SetLineWidth(1);
  //  f->SetLineColor(lcolor);
  f->Draw("L same");

  TString height2 = ""; height2 += max;
  TF1 *f2 = new TF1("f2", height2, xmin, xmax);
  f2->SetLineStyle(1);
  f2->SetLineWidth(1);
  //  f2->SetLineColor(lcolor);
  f2->Draw("L same");
}

#endif
