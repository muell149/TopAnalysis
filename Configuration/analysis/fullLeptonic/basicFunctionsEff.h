#ifndef basicFunctionsEff_h
#define basicFunctionsEff_h

#include <iostream>
#include "TH1.h"
#include "TTree.h"
#include "TF1.h"
#include "TFile.h"
#include "TString.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TMath.h"
#include "TCut.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"

#include "../semiLeptonic/diffXSection/basicFunctions.h"

int iHis=0; // workaround to give every histo a new identifier for its name

/// ---
/// mathematical functions
/// ---
// BreitWigner
// [0] = normalisation, [1]=mean (peak mass), [2]= gamma (width)
TF1 *fBreitWigner = new TF1("fBreitWigner","[0]*TMath::BreitWigner(x, [1], [2])",60.,120.);
// fBreitWigner->SetParNames("Norm","Mean","Gamma");
// fBreitWigner->SetParameters(1, 91, 5);

// BreitWigner + exp. background
TF1 *fBreitWignerExpBkg = new TF1("fBreitWignerExpBkg","[0]*TMath::BreitWigner(x, [1], [2]) + [3]*TMath::Exp([4]*x)",60.,120.);
// fBreitWigner->SetParNames("BWNorm","BWMean","BWGamma","ExpNorm","ExpScale");
// fBreitWigner->SetParameters(1, 91, 5, 1, -1);

// Voigt = BreitWigner (convlt.) Gauss
// [0] = normalisation, [1]=mean (peak mass), [2]= gamma (width), [3]=sigma (gauss width)
TF1 *fVoigt = new TF1("fVoigt","[0]*TMath::Voigt( (x-[1]), [3], [2])",60.,120.);
// fBreitWigner->SetParNames("VNorm","BWMean","BWGamma", "GSigma");
// fBreitWigner->SetParameters(1, 91, 5, 5);

// Voigt + exp. background
// TF1 *fVoigtExpBkg = new TF1("fVoigtExpBkg","[0]*TMath::Voigt( (x-[1]), [3], [2]) + [4]*TMath::Exp([5]*(x-50))",40.,140.);
TF1 *fVoigtExpBkg = new TF1("fVoigtExpBkg","[0]*TMath::Voigt( (x-[1]), [3], [2]) + [4]*TMath::Exp([5]*(x-50))",40.,140.);
// fBreitWigner->SetParNames("VNorm","BWMean","BWGamma", "GSigma","ExpNorm","ExpScale");
   //fBreitWigner->SetParameters(1, 91, 5, 5, 1, -1);

/// ---
/// structure to keep features of each type of histo plot, like its TH1D, the plotted variable, cuts to apply etc.
/// ---

struct eff{
  // constructor for initialisation
  eff(TString iniVar, TCut iniCuts, int iniBinMode, std::vector<double> iniBins, TString iniTitles, double iniYLo=-9999., double iniYHi=-9999., double iniXLo=-9999., double iniXHi=-9999., bool iniDrawLegend=false, TString iniErrorOpt="cp")
  {
    var=iniVar; cuts=iniCuts; binMode=iniBinMode; bins=iniBins; titles=iniTitles; xLo=iniXLo; xHi=iniXHi; yLo=iniYLo; yHi=iniYHi;  drawLegend=iniDrawLegend; errorOpt = iniErrorOpt;
  }
  // members:
  // map of eff. histos: eff=pass/all (only used if errorOpt==normalBinomial)
   std::map<TString, TH1D*> his;
  // map of eff. TGraphAsymmErrors: eff=pass/all (used if errorOpt!=normalBinomial)
  std::map<TString, TGraphAsymmErrors*> graphEff;
  // map of SF TGraphAsymmErrors (used if errorOpt!=normalBinomial)
  std::map<TString, TGraphAsymmErrors*> graphSF;
  // map of histo with events passing
  std::map<TString, TH1D*> hisPass;
  // map of histo with all events
  std::map<TString, TH1D*> hisAll;
  // name of variable in root file (i.e. tree or histo)
  TString var;
  // optional cuts if a tree is used
  TCut cuts;
  // binning if a tree is used or rebinning for histo
  int binMode;
  std::vector<double> bins;
  // string with title/x-axis title/ y-axis title (separated by "/")
  TString titles;
  // x- and y-axis range (low, high)
  double xLo, xHi, yLo, yHi;
  // draw legend?
  bool drawLegend;
  // option for TGraphError
  TString errorOpt;
};


/// ---
/// structure to keep features of each type of method (e.g. different samples), like draw options, style, legend etc.
/// ---
struct method{
   // constructor for initialisation
  method(TString iniFileName, TString iniLegName, int iniLineStyle, int iniLineColor, int iniMarkerStyle, int iniMarkerColor, TString iniDrawOpt, TString iniLepOpt, TString iniSource="tree", TCut iniCuts="", TString iniWeightTag="", TString iniMIDnorm="")
  {
    fileName    =iniFileName;
    if(fileName!="") file        = new TFile(fileName);
    legName     =iniLegName;
    lineStyle   =iniLineStyle;
    lineColor   =iniLineColor;
    markerStyle =iniMarkerStyle;
    markerColor =iniMarkerColor;
    drawOpt     =iniDrawOpt;
    legOpt      =iniLepOpt;
    source      =iniSource;
    cuts        =iniCuts;
    weightTag   =iniWeightTag;
    mIDnorm     =iniMIDnorm;
    
  }
  // members:
  // root file with trees/histos
  TFile* file;
  // filename
  TString fileName;
  // legend
  TString legName;
  // histo draw styles
  int lineStyle;
  int lineColor;
  int markerStyle;
  int markerColor;
  TString drawOpt;
  TString legOpt;
  // define if the source is a histo ("histo" or "histoRebin" in case rebinning desired) 
  // or tree ("tree" or optional "treeWeight" if variable weight should be used)
  TString source;
  TCut cuts;
  TString weightTag;
  TString mIDnorm;
};


/// ---
/// define binning of histos
/// ---
// bin or rebin mode:  -1 for variable (re)binning; >1 for fixed binning: nBins; >1 for rebinning: nRebin
int mBinsControl= 1;
int mBinsPt     = -1;
//int mBinsEta    = -1;
int mBinsEta    = 20;
int mBinsEtaEle = -1;
int mBinsPhi    = 10;
int mBinsMult   = 10;
int mBinsRelIso = 8;
//int mBinsRelIso = 20;
int mBinsAbsIso = 100;
int mBinsMinDR  = -1;
int mBinsLepMult= 10;
int mBinsPVMult = -1;
int mBinsLepLepMass = 100;

int mBinsJetPt     = -1;
int mBinsJetEta    = -1;
int mBinsJetAbsEta    = -1;

//modified
//int mBinsMult   = 1;
//  int mBinsRelIso = 80;
//int mBinsRelIso = -1;


double binsControl[]={0.,2.};
std::vector<double> binsControl_(binsControl, binsControl + sizeof(binsControl)/sizeof(double));
// leptons
// double binsPt[]     = {  0.,10.,20.,30.,40.,50.,75.,100.,150. };
// std::vector<double> binsPt_(binsPt, binsPt + sizeof(binsPt)/sizeof(double));
// double binsEta[]    = { -3.,-2.55,-2.1,-1.65,-1.2,-0.9,-0.45,0.,0.45,0.9,1.2,1.65,2.1,2.55,3. };
double binsEta[]    = { -3., 3. };
std::vector<double> binsEta_(binsEta, binsEta + sizeof(binsEta)/sizeof(double));
// double binsEtaEle[]    = { -3.,-2.5,-2.0,-1.566,-1.4442,-1.0,-0.5,0.,0.5,1.0,1.4442,1.566,2.0,2.5,3. };
double binsEtaEle[]    = { -3.,-2.5,-2.,-1.5,-1.0,-0.5,0.,0.5,1.0,1.5,2.,2.5,3. };
std::vector<double> binsEtaEle_(binsEtaEle, binsEtaEle + sizeof(binsEtaEle)/sizeof(double));
double binsEtaEle2[]    = { -2.5,-2.1,-1.5,-1.0,-0.5,0.,0.5,1.0,1.5,2.1,2.5};
std::vector<double> binsEtaEle2_(binsEtaEle2, binsEtaEle2 + sizeof(binsEtaEle2)/sizeof(double));
double binsPhi[]    = { -3.14,   3.14};
std::vector<double> binsPhi_(binsPhi, binsPhi + sizeof(binsPhi)/sizeof(double));
double binsMult[]   = {  0.  ,  10.  };
std::vector<double> binsMult_(binsMult, binsMult + sizeof(binsMult)/sizeof(double));
 double binsRelIso[] = {  0.  ,  0.2  };
//double binsRelIso[] = {  0.  ,  1  };
std::vector<double> binsRelIso_(binsRelIso, binsRelIso + sizeof(binsRelIso)/sizeof(double));
double binsAbsIso[] = {  0.  ,  10.  };
std::vector<double> binsAbsIso_(binsAbsIso, binsAbsIso + sizeof(binsAbsIso)/sizeof(double));
double binsMinDR[]  = { 0.,0.3,0.7,1.,1.5,2.,2.5,3.,3.7,5., };
std::vector<double> binsMinDR_(binsMinDR, binsMinDR + sizeof(binsMinDR)/sizeof(double));
// double binsPVMult[] = {  0.,1.,2.,3.,4.,5.,6.,7.,8.,10.,15.,20. };
//double binsPVMult[] = {  0.,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.,16.,17.,18.,19.,20.,21.,22.,23.,24.,25.,26.,27.,28.,29.,30. };
double binsPVMult[] = {  0.,1.,5.,8.,10.,12.,14.,16.,18.,20.,22.,24.,27.,30.,35., 40.,45.,50.};
std::vector<double> binsPVMult_(binsPVMult, binsPVMult + sizeof(binsPVMult)/sizeof(double));
double binsLepLepMass[] = {  41.  ,  141.  };
std::vector<double> binsLepLepMass_(binsLepLepMass, binsLepLepMass + sizeof(binsLepLepMass)/sizeof(double));


// double binsPt[]     = {  0.,10.,20.,25., 30.,32., 37., 42.,50.,75.,100.,150. };
// std::vector<double> binsPt_(binsPt, binsPt + sizeof(binsPt)/sizeof(double));

double binsPt[]     = {  0.,10.,20.,25., 30., 35., 40.,50.,75.,125.,200.};
std::vector<double> binsPt_(binsPt, binsPt + sizeof(binsPt)/sizeof(double));

// double binsPtAN[]   = {0., 30., 35., 40., 45., 50., 60., 70., 80., 100., 120., 150., 200., 275., 400., 1200.};
double binsPtAN[]   = {0., 30., 35., 40., 45., 50., 60., 70., 80., 100., 130., 200., 275., 400., 1200.};
std::vector<double> binsPtAN_(binsPtAN, binsPtAN + sizeof(binsPtAN)/sizeof(double));
double binsPtMedian[]   = {0., 30., 55., 200., 275.};
std::vector<double> binsPtMedian_(binsPtMedian, binsPtMedian + sizeof(binsPtMedian)/sizeof(double));
double binsPt3bins[]   = {0., 30., 45., 60., 200., 275.};
std::vector<double> binsPt3bins_(binsPt3bins, binsPt3bins + sizeof(binsPt3bins)/sizeof(double));


// double binsPt[]     = {  0.,10.,20.,25., 30.,50.,150. };
// std::vector<double> binsPt_(binsPt, binsPt + sizeof(binsPt)/sizeof(double));
// 
// double binsEtaEle[]    = { -3.,-2.55,-2.1,-1.65,-1.2,-0.9,-0.45,0.,0.45,0.9,1.2,1.65,2.1,2.55,3. };
// std::vector<double> binsEtaEle_(binsEtaEle, binsEtaEle + sizeof(binsEtaEle)/sizeof(double));

//double binsRelIso[] = {  0.  , 0.2, 1., 2.  };
// double binsRelIso[] = {  0.  ,  2.  };
// std::vector<double> binsRelIso_(binsRelIso, binsRelIso + sizeof(binsRelIso)/sizeof(double));

//  double binsMinDR[]  = { 0.,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,1.,1.5,2.,2.5,3.,4.,5.,6. };
//  std::vector<double> binsMinDR_(binsMinDR, binsMinDR + sizeof(binsMinDR)/sizeof(double));

// jets
// double binsJetPt[]     = {  0.,10.,20.,25., 30., 35., 40.,50.,75.,100.,150. };
double binsJetPt[]     = {  0.,10.,20.,25., 30., 35., 40., 45., 50., 60.,70.,95.,120.,150. };
std::vector<double> binsJetPt_(binsJetPt, binsJetPt + sizeof(binsJetPt)/sizeof(double));
double binsJetPt4[]     = {  0.,10.,20.,25., 30., 40.,50.,70.,120.,150. };
std::vector<double> binsJetPt4_(binsJetPt4, binsJetPt4 + sizeof(binsJetPt4)/sizeof(double));
// double binsJetEta[]    = {-3.5,-2.4,-1.8,-1.2,-0.6,0.,0.6,1.2,1.8,2.4,3.5 };
double binsJetEta[]    = {-3.5,-2.4,-1.4,-0.7,0.,0.7,1.4,2.4,3.5 };
std::vector<double> binsJetEta_(binsJetEta, binsJetEta + sizeof(binsJetEta)/sizeof(double));
double binsJetAbsEta[]    = {0.,1.4,2.4,3.5 };
std::vector<double> binsJetAbsEta_(binsJetAbsEta, binsJetAbsEta + sizeof(binsJetAbsEta)/sizeof(double));

double binsJetPVMult[] = {  0.,1.,5.,7.,9.,11.,13.,16.,20.,21.,22.,23.,24.,25.,26.,27.,28.,29.,30. };
std::vector<double> binsJetPVMult_(binsJetPVMult, binsJetPVMult + sizeof(binsJetPVMult)/sizeof(double));



/// ---
/// histo (or graph) style
/// T can be e.g. THX or TGraphX
/// ---
template <class T>
void setHistoStyle(T* his, TString titles, int lineStyle, int lineColor, int markerStyle, int markerColor, double yLo=-9999., double yHi=-9999., double xLo=-9999., double xHi=-9999)
{
  his->SetTitle(getStringEntry(titles, 1));
  his->GetXaxis()->SetTitle(getStringEntry(titles, 2));
  his->GetYaxis()->SetTitle(getStringEntry(titles, 3));
//   his->GetXaxis()->SetTitleSize(0.05);
//   his->GetXaxis()->SetLabelSize(0.05);
//   his->GetYaxis()->SetTitleSize(0.05);
//   his->GetYaxis()->SetLabelSize(0.05);
  if(xLo!=-9999. && xHi!=-9999.) his->GetXaxis()->SetRangeUser(xLo,xHi);
  if(yLo!=-9999. && yHi!=-9999.) his->GetYaxis()->SetRangeUser(yLo,yHi);
  if(getStringEntry(titles, 2)=="relIso") his->GetXaxis()->SetNdivisions(509);
  his->SetLineStyle(lineStyle);
  his->SetLineColor(lineColor);
  his->SetMarkerStyle(markerStyle);
  his->SetMarkerColor(markerColor);
}


/// ---
/// get histo from tree (optionally weighted) or from histo in root file
/// ---
void getHisto(TH1D*& his, TString var, TFile* file, TString folder, int binMode, std::vector<double> bins, TCut cuts="", TString source="tree", TString weightTag="")
{
  TString varString = var;
  varString.ReplaceAll("(","");
  varString.ReplaceAll(")","");
  varString.ReplaceAll(":","");
  file->cd();
  TString hisName = "hnew"+varString+(Long_t)iHis; // create unique name for each histo
  if(source=="tree" || (source=="treeV2" && weightTag=="")){
    TH1D* hnew;
    // fixed binning
    if(binMode>0) hnew = new TH1D (hisName, hisName, binMode, bins[0], bins[1]);
    // variable binning
    else          hnew = new TH1D (hisName, hisName, bins.size()-1, &bins[0]);
    //if(var=="Control") var="RelIso"; // for control overall eff. integrate relIso distrb
    TTree *tree =(TTree*) file->Get(folder+"/tree")->Clone();
    tree -> Draw(var+">>"+hisName, cuts);
    his = (TH1D*) gDirectory->Get(hisName);
    //delete hnew;
  }
  else if(source=="treeWeight" || (source=="treeV2" && weightTag!="")){
    std::cout<<source<<" chosen! weightTag="<<weightTag<<std::endl;
    if(source=="treeWeight") weightTag="weight";
    TH1D* hnew;
    // fixed binning
    if(binMode>0) hnew = new TH1D (hisName, hisName, binMode, bins[0], bins[1]);
    // variable binning
    else          hnew = new TH1D (hisName, hisName, bins.size()-1, &bins[0]);
    //if(var=="Control") var="RelIso"; // for control overall eff. integrate relIso distrb
    TTree *tree =(TTree*) file->Get(folder+"/tree")->Clone();
    tree -> Draw(var+">>"+hisName, weightTag*cuts);
    his = (TH1D*) gDirectory->Get(hisName);
    //delete hnew;
  }
  else if(source=="histo" || source=="histoRebin"){
    his = (TH1D*) file->Get(folder+"/"+var)->Clone(hisName);
    if (source=="histoRebin"){
      // rebin with fixed rebin factor
      if(binMode>0)   his->Rebin(binMode);
      // rebin with variable binning
     // if(binMode==-1) reBinTH1F(*his, bins);
    }
  }
  else std::cout<<"WARNING!!! Source not chosen correctly!"<<std::endl;
  his->Sumw2();
  iHis++;
  return;
}

/// ---
/// get histo from tree
/// ---
void getHisto(TH1D*& his, TString var, TTree* tree, int binMode, std::vector<double> bins, TCut cuts="", TString source="tree")
{
  // create new histo
  TString hisName = "hnew"+var+(Long_t)iHis; // create unique name for each histo
  TH1D* hnew;
  // fixed binning
  if(binMode>0) hnew = new TH1D (hisName, hisName, binMode, bins[0], bins[1]);
  // variable binning
  else          hnew = new TH1D (hisName, hisName, bins.size()-1, &bins[0]);
  if(var=="Control") var="Mult"; // for control overall eff. integrate jet multiplicity
  
  // get histo from tree
  if(source=="tree"){
  tree -> Draw(var+">>"+hisName, cuts);
  }
  else if(source=="treeWeight"){
    if(var=="Control") var="Mult"; // for control overall eff. integrate jet multiplicity
    tree -> Draw(var+">>"+hisName, "weight"*cuts);
  }
  his = (TH1D*) gDirectory->Get(hisName);
  iHis++;
  return;
}

/// ---
/// gets efficiencies from two histograms stored in a root file
/// Eff = pass / all
/// ---
void getEfficiencies(TH1D*& histoEff, TString var, TFile* file, TString folderPass, TString folderAll)
{
  TH1D* histoPass = (TH1D*) file->Get(folderPass+"/"+var)->Clone();
  histoPass->Sumw2();
  
  TH1D* histoAll  = (TH1D*) file->Get(folderAll+"/"+var)->Clone();
  histoAll->Sumw2();
  
  histoEff  = (TH1D*) histoAll->Clone("histoEff"+var);
  histoEff->Reset();
  histoEff -> Divide(histoPass, histoAll, 1, 1, "B");
  return;
}

/// ---
/// gets efficiencies from a tree stored in a root file
/// Eff = pass / all
/// ---
// void getEfficiencies(TH1D*& histoEff, TString var, TFile* file, TString folderPass, TString folderAll, TString titles, TString bins, TString cuts)
// {
//   file->cd();
//   TTree *treePass =(TTree*) file->Get(folderPass+"/tree")->Clone();
//   treePass -> Draw(var+">>hnewPass"+var+bins, cuts);
//   TH1D* histoPass = (TH1D*) gDirectory->Get("hnewPass"+var);
//   histoPass->Sumw2();
//   
//   TTree *treeAll =(TTree*) file->Get(folderAll+"/tree")->Clone();
//   treeAll -> Draw(var+">>hnewAll"+var+bins, cuts);
//   TH1D* histoAll = (TH1D*) gDirectory->Get("hnewAll"+var);
//   histoAll->Sumw2();
//   
//   histoEff  = (TH1D*) histoAll->Clone("histoEff"+var);
//   histoEff->Reset();
//   histoEff -> Divide(histoPass, histoAll, 1, 1, "B");
//   return;
// }

/// ---
/// gets efficiencies and histos with all and passing events from a tree or histo stored in a root file
/// Eff = pass / all
/// uses HISTOS for eff, i.e. only normalBinomial errors possible
/// ---
void getEfficiencies(TH1D*& histoEff, TH1D*& histoPass, TH1D*& histoAll, TString var, TFile* file, TString folderPass, TString folderAll, TString titles, int binMode, std::vector<double> bins, TCut cuts="", int lineStyle=1, int lineColor=1, int markerStyle=1, int markerColor=1, double xLo=-9999., double xHi=-9999., double yLo=-9999., double yHi=-9999., TString source="tree", TString weightTag="")
{
  file->cd();
  if(folderAll==folderPass){ // this is used for T&P
    if(source=="treeV2"){ // this is the new tree version that saves only the kinematic variable for probes + info if passed
      // gets histo with passing events from tree or histo
      TCut cutPass = cuts && "pass";
      // if the combined selection and trigger efficiency is desired:
      if     (folderAll=="tapAll")   {folderAll="tapTotalSelection"; folderPass="tapTrigger";}
      else if(folderAll=="tapAllEle"){folderAll="tapTotalSelectionEle"; folderPass="tapTriggerEle";}
      
      getHisto(histoPass, "probe"+var, file, folderPass, binMode, bins, cutPass, source, weightTag);
      // gets histo with all events from tree
      getHisto(histoAll, "probe"+var, file, folderAll, binMode, bins, cuts, source, weightTag);
    }
    else{ 
      // gets histo with passing events from tree or histo
      getHisto(histoPass, "test"+var, file, folderPass, binMode, bins, cuts, source);
      // gets histo with all events from tree or histo
      getHisto(histoAll, "probe"+var, file, folderAll, binMode, bins, cuts, source);
    }
  }
  else{ // this is used for two analyzers: before and after cuts
    // gets histo with passing events from tree or histo
    getHisto(histoPass, var, file, folderPass, binMode, bins, cuts, source, weightTag);
    // gets histo with all events from tree
    getHisto(histoAll, var, file, folderAll, binMode, bins, cuts, source, weightTag);
  }
  // set histo style
  setHistoStyle(histoPass, getStringEntry(titles, 1)+"/"+getStringEntry(titles, 2)+"/N_{pass}", lineStyle, lineColor, markerStyle, markerColor, yLo, yHi, xLo, xHi);
  setHistoStyle(histoAll, getStringEntry(titles, 1)+"/"+getStringEntry(titles, 2)+"/N_{all}", lineStyle, lineColor, markerStyle, markerColor, yLo, yHi, xLo, xHi);
  // calculates eff. histo
  histoEff  = (TH1D*) histoAll->Clone("histoEff"+var);
  histoEff->Reset();
  histoEff -> Divide(histoPass, histoAll, 1, 1, "B");
  setHistoStyle(histoEff, titles, lineStyle, lineColor, markerStyle, markerColor, yLo, yHi, xLo, xHi);
  
  std::cout<<"his Title: " <<histoPass->GetTitle() <<" Nbins pass: "<<histoPass->GetNbinsX() << " Nbins all " << histoAll->GetNbinsX() <<std::endl;
  std::cout<<"before putStats histoPass N: "<<histoPass->GetEntries() << " histoAll N " << histoAll->GetEntries() <<std::endl;
  return;
}

/// ---
/// gets efficiencies and histos with all and passing events from a tree or histo stored in a root file
/// Eff = pass / all
/// ---
void getEfficiencies(TGraphAsymmErrors*& graphEff, TH1D*& histoPass, TH1D*& histoAll, TString var, TFile* file, TString folderPass, TString folderAll, TString titles, int binMode, std::vector<double> bins, TCut cuts="", int lineStyle=1, int lineColor=1, int markerStyle=1, int markerColor=1, double xLo=-9999., double xHi=-9999., double yLo=-9999., double yHi=-9999., TString source="tree", TString weightTag="", TString errorOpt="cp")
{
  file->cd();
  if(folderAll==folderPass){ // this is used for T&P
    if(source=="treeV2"){ // this is the new tree version that saves only the kinematic variable for probes + info if passed
      // add "probe" to name if not lepLepMass
      if(var!="lepLepMass") var="probe"+var;
      // if the combined selection and trigger efficiency is desired:
      if     (folderAll=="tapAll")   {folderAll="tapTotalSelection"; folderPass="tapTrigger";}
      else if(folderAll=="tapAllEle"){folderAll="tapTotalSelectionEle"; folderPass="tapTriggerEle";}
      
      // gets histo with passing events from tree or histo
      TCut cutPass = cuts && "pass==1";
      getHisto(histoPass, var, file, folderPass, binMode, bins, cutPass, source, weightTag);
      // gets histo with all events from tree
      getHisto(histoAll, var, file, folderAll, binMode, bins, cuts, source, weightTag);
//       std::cout<<"CutPass: "<<cutPass<<std::endl;
//       std::cout<<"CutAll: "<<cuts<<std::endl;
    }
    else{ 
      std::cout<<"T&P"<<std::endl;
      // gets histo with passing events from tree or histo
      getHisto(histoPass, "test"+var, file, folderPass, binMode, bins, cuts, source);
      // gets histo with all events from tree or histo
      getHisto(histoAll, "probe"+var, file, folderAll, binMode, bins, cuts, source);
    }
  }
  else{ // this is used for two analyzers: before and after cuts
    // gets histo with passing events from tree or histo
    if(var=="Pt") var="pt";
    else if(var=="Eta") var="eta";
    getHisto(histoPass, var, file, folderPass, binMode, bins, cuts, source, weightTag);
    // gets histo with all events from tree
    getHisto(histoAll, var, file, folderAll, binMode, bins, cuts, source, weightTag);
  }
  // set histo style
  setHistoStyle(histoPass, getStringEntry(titles, 1)+"/"+getStringEntry(titles, 2)+"/N_{pass}", lineStyle, lineColor, markerStyle, markerColor, yLo, yHi, xLo, xHi);
  setHistoStyle(histoAll, getStringEntry(titles, 1)+"/"+getStringEntry(titles, 2)+"/N_{all}", lineStyle, lineColor, markerStyle, markerColor, yLo, yHi, xLo, xHi);
  
  // calculates eff. histo
 // print test output
//   std::cout<<"-----------------------"<<std::endl;
  std::cout<<"-----------------------"<<std::endl;
  std::cout<<"Titles: "<<titles<<std::endl;
//   std::cout<<"before consistency check"<<std::endl;
//   std::cout<<"redo histo with int"<<std::endl;
  
  //set underflow and overflow bins to 0 to avoid consistency error
//   histoPass->SetBinContent(0,0);
//   histoPass->SetBinContent(histoPass->GetNbinsX()+1,0);
//   histoAll->SetBinContent(0,0);
//   histoAll->SetBinContent(histoAll->GetNbinsX()+1,0);
  
  // create new histos with integer numbers to avoid problems after reweighting
  TH1* histoPassBuff = (TH1*) histoPass->Clone();
  TH1* histoAllBuff  = (TH1*) histoAll->Clone();
  
  histoPassBuff->Reset();
  histoAllBuff ->Reset();
  
  histoPassBuff->Sumw2();
  histoAllBuff ->Sumw2();
  
  // switch to include under/ overflow bins: 1= include, 0=not include
  int underOverFlow = 1;
  
  // fill histo with rounded integer numbers
  for(int iBin=1-underOverFlow; iBin<=histoPass->GetNbinsX()+underOverFlow; iBin++){
    int binContent=0;
    double binCenter=0.;
    binContent = (histoPass->GetBinContent(iBin)+0.5);
    binCenter = histoPass->GetBinCenter(iBin);
    for(int j=0; j<binContent; j++) histoPassBuff->Fill(binCenter);
    //histoPassBuff->SetBinContent(iBin,binContent);
    binContent = (histoAll->GetBinContent(iBin)+0.5);
    binCenter = histoAll->GetBinCenter(iBin);
    for(int j=0; j<binContent; j++) histoAllBuff->Fill(binCenter);
    //histoAllBuff->SetBinContent(iBin,binContent);
    
//     std::cout<<"Not rounded bin eff.: Eff    ="<<histoPass->GetBinContent(iBin)/histoAll->GetBinContent(iBin)    
// 	<<" NPass    ="<<histoPass->GetBinContent(iBin)    <<" NAll    ="<<histoAll->GetBinContent(iBin)    <<std::endl;
//     std::cout<<"    rounded bin eff.: EffBuff="<<histoPassBuff->GetBinContent(iBin)/histoAllBuff->GetBinContent(iBin)
// 	<<" NPassBuff="<<histoPassBuff->GetBinContent(iBin)<<" NAllBuff="<<histoAllBuff->GetBinContent(iBin)<<std::endl;
  }
  
  // calculate control efficiency integrated over full range for rounded and not rounded numbers
  double NPass      = histoPass->Integral(1-underOverFlow,histoPass->GetNbinsX()+underOverFlow);
  double NAll       = histoAll->Integral(1-underOverFlow,histoAll->GetNbinsX()+underOverFlow);
  double eff        = NPass / NAll;
  double NPassBuff  = histoPassBuff->Integral(1-underOverFlow,histoPassBuff->GetNbinsX()+underOverFlow);
  double NAllBuff   = histoAllBuff->Integral(1-underOverFlow,histoAllBuff->GetNbinsX()+underOverFlow);
  double effBuff    = NPassBuff / NAllBuff;
  
  std::cout<<"Include under/overflow: " <<underOverFlow <<std::endl;
  std::cout<<"Not rounded control eff.: Eff    ="<<eff    <<" NPass    ="<<NPass    <<" NAll    ="<<NAll    <<std::endl;
  std::cout<<"    rounded control eff.: EffBuff="<<effBuff<<" NPassBuff="<<NPassBuff<<" NAllBuff="<<NAllBuff<<std::endl;
  
   // needs trick to pretend that weights are 1 even if they are not 
//   double stats[10]={0.};
//   double stats2[10]={0.};
//   //set sumw and sumw2 to total histo entries -> as if no weights had been applied
//   stats[0]=histoPassBuff->Integral();
//   std::cout<<"pass stats[0] " << stats[0] <<std::endl;
//   stats[1]=histoPassBuff->Integral();
//   std::cout<<"pass stats[1] " << stats[1] <<std::endl;
//   histoPassBuff->PutStats(stats);
//   stats[0]=histoAllBuff->Integral();
//   std::cout<<"all stats[0] " << stats[0] <<std::endl;
//   stats[1]=histoAllBuff->Integral();
//   std::cout<<"all stats[1] " << stats[1] <<std::endl;
//   histoAllBuff->PutStats(stats);
  

//   histoPassBuff->GetStats(stats2);
//   std::cout<<"stats pass 0-1: " << stats2[0]<< " " <<stats2[1] << std::endl;
//   histoAllBuff->GetStats(stats2);
//   std::cout<<"stats all 0-1: " << stats2[0]<< " " <<stats2[1] << std::endl;
//   std::cout<<" histoPassBuff Int. " << histoPassBuff->Integral() << " histoAllBuff Int. " << histoAllBuff->Integral() <<std::endl;
//   
//   std::cout<<"-----------------------"<<std::endl;
//   std::cout<<"Check consistency" <<std::endl;
//   TEfficiency* tEff = new TEfficiency();
//   tEff->CheckConsistency(*histoPassBuff,*histoAllBuff);
//   tEff->CheckEntries(*histoPassBuff,*histoAllBuff);
//   for(Int_t i = 0; i < histoPassBuff->GetNbinsX()+2; ++i) {
//     std::cout<<"Bin "<<i<<"; pass: "<<histoPassBuff->GetBinContent(i)<<"; all: " << histoAllBuff->GetBinContent(i)<<std::endl;
//     if(histoPassBuff->GetBinContent(i) > histoAllBuff->GetBinContent(i)) {
//       std::cout<<"!!!!!!!pass > total Bin "<<i<<std::endl;
//     }
//   }
//   std::cout<<"-----------------------"<<std::endl;
//   std::cout<<"after consistency check"<<std::endl;
//   histoPassBuff->GetStats(stats2);
//   std::cout<<"stats pass 0-1: " << stats2[0]<< " " <<stats2[1] << std::endl;
//   histoAllBuff->GetStats(stats2);
//   std::cout<<"stats all 0-1: " << stats2[0]<< " " <<stats2[1] << std::endl;
//   std::cout<<" histoPassBuff Int. " << histoPassBuff->Integral() << " histoAllBuff Int. " << histoAllBuff->Integral() <<std::endl;
//   std::cout<<"-----------------------"<<std::endl;
  
  graphEff  = new TGraphAsymmErrors(histoPassBuff, histoAllBuff, errorOpt.Data());
  // just print points
//   for (int iPoint=0; iPoint < graphEff->GetN(); iPoint++){
//     std::cout<<"    graph bin eff.: " << graphEff->GetY()[iPoint] <<std::endl;
//   }
  setHistoStyle(graphEff, titles, lineStyle, lineColor, markerStyle, markerColor, yLo, yHi, xLo, xHi);
  return;
}

/// ---
/// same as above but only needs eff struct and then calls above function
/// ---
void getEfficiencies(eff*& eff1, method*& method1, TString methodID, TString folderPass, TString folderAll)
{
  if(eff1->errorOpt=="normalBinomial") getEfficiencies(eff1->his[methodID], eff1->hisPass[methodID], eff1->hisAll[methodID], eff1->var, method1->file, folderPass, folderAll, eff1->titles, eff1->binMode, eff1->bins, eff1->cuts && method1->cuts, method1->lineStyle, method1->lineColor, method1->markerStyle, method1->markerColor, eff1->xLo, eff1->xHi, eff1->yLo, eff1->yHi, method1->source, method1->weightTag);
  
  else getEfficiencies(eff1->graphEff[methodID], eff1->hisPass[methodID], eff1->hisAll[methodID], eff1->var, method1->file, folderPass, folderAll, eff1->titles, eff1->binMode, eff1->bins, eff1->cuts && method1->cuts, method1->lineStyle, method1->lineColor, method1->markerStyle, method1->markerColor, eff1->xLo, eff1->xHi, eff1->yLo, eff1->yHi, method1->source, method1->weightTag, eff1->errorOpt);
  return;
}

/// ---
/// averages two efficiencies according to the fraction f of their composition:
/// eff.(av) = f*eff1 + (1-f)*eff2, where f = Nall1/(Nall1+Nall2)
/// It is assumed that effAve has already a graph in the structurein the same format 
/// as eff1 and eff2 (ideally initialise it with either eff1 or eff2 before)
/// ---
void averageEfficiencies(eff*& eff1, TString methodIDAve, TString methodID1, TString methodID2, double f1, double f2)
{
   // get points and their asymm. errors for first and second efficiency
  int N                    = eff1->graphEff[methodIDAve]->GetN();
  double * effAveX         = eff1->graphEff[methodIDAve]->GetX();
  double * eff1Y           = eff1->graphEff[methodID1]  ->GetY();
  double * eff2Y           = eff1->graphEff[methodID2]  ->GetY();
  double * eff1YH          = eff1->graphEff[methodID1]  ->GetEYhigh();
  double * eff1YL          = eff1->graphEff[methodID1]  ->GetEYlow();
  double * eff2YH          = eff1->graphEff[methodID2]  ->GetEYhigh();
  double * eff2YL          = eff1->graphEff[methodID2]  ->GetEYlow();
  
  // check if effAve, eff1 and eff2 have the same bin numbers
  if(N!=eff1->graphEff[methodID1]->GetN() && N!=eff1->graphEff[methodID2]->GetN()){
    std::cout<<"ERROR!!! Number of Points of effAve ("<<N<<"), eff1 ("<<eff1->graphEff[methodID1]->GetN()<<") and eff2 ("<<eff1->graphEff[methodID2]->GetN()<<" different!!!"<<std::endl;
    std::cout<<"The averaging of efficiencies is interrupted!!!"<<std::endl;
	return;
  }
      // set points and errors of average graph
  double ave     = -1., aveErrH = -1., aveErrL = -1.;
  for(int iPoint=0; iPoint< N ; iPoint++){
    // central value combination
    ave     = f1*eff1Y[iPoint] + f2*eff2Y[iPoint];
    // error: just Gaussian propagation, no proper treatment of asymm. errors
    aveErrH = TMath::Sqrt(f1*f1*eff1YH[iPoint]*eff1YH[iPoint] + f2*f2*eff2YH[iPoint]*eff2YH[iPoint]);
    aveErrL = TMath::Sqrt(f1*f1*eff1YL[iPoint]*eff1YL[iPoint] + f2*f2*eff2YL[iPoint]*eff2YL[iPoint]);
    // re-set points of effAve	
    eff1->graphEff[methodIDAve]->SetPoint      (iPoint, effAveX[iPoint], ave);
    eff1->graphEff[methodIDAve]->SetPointEYhigh(iPoint, aveErrH);
    eff1->graphEff[methodIDAve]->SetPointEYlow (iPoint, aveErrL);
  }
}

/// ---
/// draw efficiency plots of one variable for all methods, incl. legend
/// ---
void drawEfficiencies(eff* eff1, std::map<TString, method*> method1, std::vector<TString> mID, double legXlo, double legYlo, double legXhi, double legYhi, bool drawLeg=true)
{
  TObject *his;
  TString drawOpt="";
  
  TLegend leg(legXlo, legYlo, legXhi, legYhi);
  leg.SetFillStyle(0);
  
  for(unsigned int iMethod=0; iMethod<mID.size(); iMethod++){
    if(eff1->errorOpt=="normalBinomial") {
      his = eff1->his[mID[iMethod]];
      if(iMethod==0) drawOpt = method1[mID[iMethod]]->drawOpt;
      else           drawOpt = method1[mID[iMethod]]->drawOpt+" same";
    }
    else {
      his = eff1->graphEff[mID[iMethod]];
      if(iMethod==0) drawOpt = "PA";
      else           drawOpt = "P same";
      
      // set x errors to 0 if desired (needs to be done manually for TGraphAsymmErrors)
      if(method1[mID[iMethod]]->drawOpt.Contains("X0")){
	for(int iPoint=0; iPoint< eff1->graphEff[mID[iMethod]]->GetN() ; iPoint++){
	  eff1->graphEff[mID[iMethod]]->SetPointEXhigh(iPoint,0);
	  eff1->graphEff[mID[iMethod]]->SetPointEXlow(iPoint,0);
        }
      }
    }
    
    his->Draw(drawOpt.Data());
    // legend
    if(method1[mID[iMethod]]->legOpt!="") leg.AddEntry(his, method1[mID[iMethod]]->legName, method1[mID[iMethod]]->legOpt);
  }
  if(drawLeg) leg.DrawClone();
}

/// ---
/// draw legend
/// ---
void drawLegend(eff* eff1, std::map<TString, method*> method1, std::vector<TString> mID, double legXlo, double legYlo, double legXhi, double legYhi)
{
  TObject *his;
  
  TLegend leg2(legXlo, legYlo, legXhi, legYhi);
  leg2.SetFillStyle(0);
  
  for(unsigned int iMethod=0; iMethod<mID.size(); iMethod++){
    if(eff1->errorOpt=="normalBinomial") his = eff1->his[mID[iMethod]];
    else                                 his = eff1->graphEff[mID[iMethod]];
    // legend
//     if(iMethod==0) eff1->graphEff[mID[iMethod]]->Draw("PA");
//     else eff1->graphEff[mID[iMethod]]->Draw("same");
    if(method1[mID[iMethod]]->legOpt!="") leg2.AddEntry(his, method1[mID[iMethod]]->legName, method1[mID[iMethod]]->legOpt);
  }
  //gPad->Clear();
  leg2.DrawClone();
}

/// ---
/// SF!!
/// calculate and draw efficiency scale factor plots of one variable for all methods, incl. legend
/// ---
void drawSF(eff*& eff1, std::map<TString, method*> method1, std::vector<TString> mID, TString mIDnorm, double legXlo, double legYlo, double legXhi, double legYhi, bool drawLeg=true, double yLo=-9999., double yHi=-9999., double xLo=-9999., double xHi=-9999.)
{
  /// if mIDnorm is specified in eff structure, i.e.!="", it is taken for normalisation;
  /// otherwise mIDnorm from the list of arguments of this function is taken
  TLegend leg(legXlo, legYlo, legXhi, legYhi);
  leg.SetFillStyle(0);
  
  TH1D* SFhis;
  TGraphAsymmErrors* SFgraph;
  TString drawOpt="";
  
  for(unsigned int iMethod=0; iMethod<mID.size(); iMethod++){
    // check if method contains mIDnorm: then overwrite mIDnorm from function argument
    if(method1[mID[iMethod]]->mIDnorm!="") mIDnorm = method1[mID[iMethod]]->mIDnorm;
    std::cout<<"Method ID: "<<mID[iMethod] <<"; normalised to " << mIDnorm <<std::endl;
    // calculate SF
    // if histo with normalBinomial errors is desired
    if(eff1->errorOpt=="normalBinomial"){
      SFhis = (TH1D*)eff1->his[mID[iMethod]]->Clone("SF");
      SFhis -> Reset();
      SFhis ->SetTitle(Form("%s SF", eff1->his[mID[iMethod]]->GetTitle()));
      SFhis ->Divide(eff1->his[mID[iMethod]], eff1->his[mIDnorm]);
      // set y errors to 0 for reference SF
      if(mID[iMethod]==mIDnorm){
	double yErr0[100]={0.};
	SFhis->SetError(yErr0);
      }
      // draw SF
      if(iMethod==0){
	if(xLo!=-9999. && xHi!=-9999.) SFhis->GetXaxis()->SetRangeUser(xLo,xHi);
	if(yLo!=-9999. && yHi!=-9999.) SFhis->GetYaxis()->SetRangeUser(yLo,yHi);
	drawOpt= method1[mID[iMethod]]->drawOpt;
      }
      else drawOpt=method1[mID[iMethod]]->drawOpt+" same";
      SFhis->DrawCopy(drawOpt.Data());
      // legend
      if(method1[mID[iMethod]]->legOpt!="") leg.AddEntry(eff1->his[mID[iMethod]], method1[mID[iMethod]]->legName, method1[mID[iMethod]]->legOpt);
    }
    
    // if other error options are desired, which require TGraphAsymm
    else{
      SFgraph = (TGraphAsymmErrors*) eff1->graphEff[mID[iMethod]]->Clone(Form("%s SF", eff1->graphEff[mID[iMethod]]->GetTitle()));
      SFgraph ->SetTitle(Form("%s SF", eff1->graphEff[mID[iMethod]]->GetTitle()));
      // get points and their asymm. errors for numerator (eff_data) and denom. (eff_MC)
      int N                  = eff1->graphEff[mID[iMethod]]->GetN();
      double * numerator     = eff1->graphEff[mID[iMethod]]->GetY();
      double * denom         = eff1->graphEff[mIDnorm]->GetY();
      double * numeratorErrH = eff1->graphEff[mID[iMethod]]->GetEYhigh();
      double * numeratorErrL = eff1->graphEff[mID[iMethod]]->GetEYlow();
      double * denomErrH     = eff1->graphEff[mIDnorm]->GetEYhigh();
      double * denomErrL     = eff1->graphEff[mIDnorm]->GetEYlow();
      double * numeratorX    = eff1->graphEff[mID[iMethod]]->GetX();
      double * denomX        = eff1->graphEff[mIDnorm]->GetX();
      double * numeratorErrXH = eff1->graphEff[mID[iMethod]]->GetEXhigh();
      double * numeratorErrXL = eff1->graphEff[mID[iMethod]]->GetEXlow();
      double * denomErrXH     = eff1->graphEff[mIDnorm]->GetEXhigh();
      double * denomErrXL     = eff1->graphEff[mIDnorm]->GetEXlow();
      // check if numerator and denominator have the same bin numbers
      if(N!=eff1->graphEff[mIDnorm]->GetN()){
	std::cout<<"WARNING!!! Number of Points of numerator ("<<N<<") and denominator ("<<eff1->graphEff[mIDnorm]->GetN()<<") different!!!"<<std::endl;
	std::cout<<"SF for method "<<mID[iMethod] <<" for titles "<< eff1->titles<<" is only calculated for numerator points!!!"<<std::endl;
	//continue;
      }
      // set points and errors of SF graph
      double SF     = -1., SFErrH = -1., SFErrL = -1.;
      for(int iPointNum=0; iPointNum< N ; iPointNum++){
	// loop over denominator points to find the matching point
	for(int iPointDenom=iPointNum; iPointDenom < eff1->graphEff[mIDnorm]->GetN(); iPointDenom++){
	  // check if binning is the same: either bin boundaries the same or point itself
	  if((numeratorX[iPointNum]-numeratorErrXL[iPointNum] == denomX[iPointDenom]-denomErrXL[iPointDenom] && numeratorX[iPointNum]+numeratorErrXH[iPointNum] == denomX[iPointDenom]+denomErrXH[iPointDenom]) || numeratorX[iPointNum]==denomX[iPointDenom]){
	    SF     = numerator[iPointNum]/denom[iPointDenom];
	    // calculate asymmetric errors
	    SFErrH = SF*TMath::Sqrt(numeratorErrH[iPointNum]*numeratorErrH[iPointNum] / (numerator[iPointNum]*numerator[iPointNum]) + denomErrL[iPointDenom]*denomErrL[iPointDenom]/(denom[iPointDenom]*denom[iPointDenom]));
	    SFErrL = SF*TMath::Sqrt(numeratorErrL[iPointNum]*numeratorErrL[iPointNum] / (numerator[iPointNum]*numerator[iPointNum]) + denomErrH[iPointDenom]*denomErrH[iPointDenom]/(denom[iPointDenom]*denom[iPointDenom]));
	    SFgraph -> SetPoint(iPointNum, numeratorX[iPointNum], SF);
	    double xErrH=0;
	    double xErrL=0;
	    // set x errors if desired
	    if(!method1[mID[iMethod]]->drawOpt.Contains("X0")){
	      xErrH=numeratorErrXH[iPointNum];
	      xErrL=numeratorErrXL[iPointNum];
	    }
	    // set y errors to 0 for reference SF
	    if(mID[iMethod]==mIDnorm){
	      SFErrH=0;
	      SFErrL=0;
	    }
	    SFgraph -> SetPointError(iPointNum, xErrL, xErrH, SFErrL, SFErrH);
	    break;
	  }
	  if(iPointDenom==eff1->graphEff[mIDnorm]->GetN()-1) std::cout<< "WARNING!!!! For numerator point x="<<numeratorX[iPointDenom]<<" no denominator found!!!"<<std::endl;
	}
    }
      // set axis titles
      SFgraph->GetXaxis()->SetTitle( eff1->graphEff[mID[iMethod]]->GetXaxis()->GetTitle() );
      SFgraph->GetYaxis()->SetTitle( eff1->graphEff[mID[iMethod]]->GetYaxis()->GetTitle() );
      if((TString)(SFgraph->GetXaxis()->GetTitle())=="relIso") SFgraph->GetXaxis()->SetNdivisions(509);
      // Print efficiency and SF
      if(eff1->var=="Control"){
	std::cout<< SFgraph ->GetTitle() << "SF. = " << numerator[0] <<"+" <<numeratorErrH[0] << "-" <<numeratorErrL[0] <<
	    " / " << denom[0] <<"+" <<denomErrH[0] << "-" <<denomErrL[0] << 
	    " = " << SF     <<"+" <<SFErrH << "-" <<SFErrL << std::endl; 
      }
      // draw graph
      if(iMethod==0){
	if(xLo!=-9999. && xHi!=-9999.) SFgraph->GetXaxis()->SetRangeUser(xLo,xHi);
	if(yLo!=-9999. && yHi!=-9999.) SFgraph->GetYaxis()->SetRangeUser(yLo,yHi);
	drawOpt="P A";
      }
      else drawOpt="P same";
      SFgraph->DrawClone(drawOpt.Data());
       // legend
      if(method1[mID[iMethod]]->legOpt!="") leg.AddEntry(SFgraph, method1[mID[iMethod]]->legName, method1[mID[iMethod]]->legOpt);
      
      /// assign the graph to the eff structure
      eff1->graphSF[mID[iMethod]]=SFgraph;
    }
  }
  if(drawLeg) leg.DrawClone();
  
}

/// ---
/// Eff. and SF as ratio plots under it !!!
/// calculate and draw efficiency scale factor plots of one variable for all methods, incl. legend
/// ---
void drawEffAndSFinOne(eff*& eff1, std::map<TString, method*> method1, std::vector<TString> mID, TString mIDnorm, double legXlo, double legYlo, double legXhi, double legYhi, bool drawLeg=true, double yLo=-9999., double yHi=-9999., double xLo=-9999., double xHi=-9999.)
{
  /// --------------------------------------
  /// 1st step: draw Efficiency!!!
  /// --------------------------------------
  
  // get Canvas
  TCanvas *mainpad = (TCanvas*)gPad->GetPad(0);
 // std::cout << "mainpad->GetName()= " << mainpad->GetName() << std::endl;
  TAxis *mainaxis=0;
  TGraph *his0=0;
  
  TGraph *his;
  TString drawOpt="";
  
  TLegend leg(legXlo, legYlo, legXhi, legYhi);
  leg.SetFillStyle(0);
  
  for(unsigned int iMethod=0; iMethod<mID.size(); iMethod++){
    if(eff1->errorOpt=="normalBinomial") {
      his = (TGraph*)eff1->his[mID[iMethod]]->Clone(Form("clone%i",iMethod));
      if(iMethod==0) drawOpt = method1[mID[iMethod]]->drawOpt;
      else           drawOpt = method1[mID[iMethod]]->drawOpt+" same";
    }
    else {
      his = (TGraph*)eff1->graphEff[mID[iMethod]]->Clone(Form("clone%i",iMethod));
      if(iMethod==0) drawOpt = "PA";
      else           drawOpt = "P same";
      
      // set x errors to 0 if desired (needs to be done manually for TGraphAsymmErrors)
      if(method1[mID[iMethod]]->drawOpt.Contains("X0")){
	for(int iPoint=0; iPoint< eff1->graphEff[mID[iMethod]]->GetN() ; iPoint++){
	  eff1->graphEff[mID[iMethod]]->SetPointEXhigh(iPoint,0);
	  eff1->graphEff[mID[iMethod]]->SetPointEXlow(iPoint,0);
	}
      }
    }
    his->GetXaxis()->SetTitleColor(0);
    his->GetXaxis()->SetLabelColor(0);
    his->DrawClone(drawOpt.Data());
    if(iMethod==0) {mainaxis = (TAxis*) ((TGraph*)his)->GetYaxis(); his0=his;}
    
    // legend
    if(method1[mID[iMethod]]->legOpt!="") leg.AddEntry(his, method1[mID[iMethod]]->legName, method1[mID[iMethod]]->legOpt);
  }
  if(drawLeg) leg.DrawClone();
  
  /// --------------------------------------
  /// 2nd step: calculate and draw SF !!!
  /// --------------------------------------
  
  /// prepare 2nd pad for ratio plot
   // get some values from old pad
    Int_t    logx = gPad->GetLogx();
    Double_t left = gPad->GetLeftMargin();
    Double_t right = gPad->GetRightMargin();

    // y:x size ratio for canvas
    double canvAsym = 5./4.;
    // ratio size of pad with plot and pad with ratio
  double ratioSize = 0.42;
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
  rPad->SetFillStyle(0);
  rPad->SetFillColor(0);
  rPad->SetBorderSize(0);
  rPad->SetBorderMode(0);
  rPad->Draw();
    // configure ratio plot
  rPad->cd();
  double scaleFactor = 1./(canvAsym*ratioSize);

    
  /// if mIDnorm is specified in eff structure, i.e.!="", it is taken for normalisation;
  /// otherwise mIDnorm from the list of arguments of this function is taken
  
  TH1D* SFhis;
  TGraphAsymmErrors* SFgraph;
  drawOpt="";
  
  for(unsigned int iMethod=0; iMethod<mID.size(); iMethod++){
    // check if method contains mIDnorm: then overwrite mIDnorm from function argument
    if(method1[mID[iMethod]]->mIDnorm!="") mIDnorm = method1[mID[iMethod]]->mIDnorm;
    std::cout<<"Method ID: "<<mID[iMethod] <<"; normalised to " << mIDnorm <<std::endl;
    // calculate SF
    // if histo with normalBinomial errors is desired
    if(eff1->errorOpt=="normalBinomial"){
      SFhis = (TH1D*)eff1->his[mID[iMethod]]->Clone("SF");
      SFhis -> Reset();
      SFhis ->SetTitle(Form("%s SF", eff1->his[mID[iMethod]]->GetTitle()));
      SFhis ->Divide(eff1->his[mID[iMethod]], eff1->his[mIDnorm]);
      // set y errors to 0 for reference SF
      if(mID[iMethod]==mIDnorm){
	double yErr0[100]={0.};
	SFhis->SetError(yErr0);
      }
      // draw SF
      if(iMethod==0){
	if(xLo!=-9999. && xHi!=-9999.) SFhis->GetXaxis()->SetRangeUser(xLo,xHi);
	if(yLo!=-9999. && yHi!=-9999.) SFhis->GetYaxis()->SetRangeUser(yLo,yHi);
	drawOpt= method1[mID[iMethod]]->drawOpt;
      }
      else drawOpt=method1[mID[iMethod]]->drawOpt+" same";
      SFhis->DrawCopy(drawOpt.Data());
      // legend
      if(method1[mID[iMethod]]->legOpt!="") leg.AddEntry(eff1->his[mID[iMethod]], method1[mID[iMethod]]->legName, method1[mID[iMethod]]->legOpt);
    }
    
    // if other error options are desired, which require TGraphAsymm
    else{
      SFgraph = (TGraphAsymmErrors*) eff1->graphEff[mID[iMethod]]->Clone(Form("%s SF", eff1->graphEff[mID[iMethod]]->GetTitle()));
      SFgraph ->SetTitle("");
      // get points and their asymm. errors for numerator (eff_data) and denom. (eff_MC)
      int N                  = eff1->graphEff[mID[iMethod]]->GetN();
      double * numerator     = eff1->graphEff[mID[iMethod]]->GetY();
      double * denom         = eff1->graphEff[mIDnorm]->GetY();
      double * numeratorErrH = eff1->graphEff[mID[iMethod]]->GetEYhigh();
      double * numeratorErrL = eff1->graphEff[mID[iMethod]]->GetEYlow();
      double * denomErrH     = eff1->graphEff[mIDnorm]->GetEYhigh();
      double * denomErrL     = eff1->graphEff[mIDnorm]->GetEYlow();
      double * numeratorX    = eff1->graphEff[mID[iMethod]]->GetX();
      double * denomX        = eff1->graphEff[mIDnorm]->GetX();
      double * numeratorErrXH = eff1->graphEff[mID[iMethod]]->GetEXhigh();
      double * numeratorErrXL = eff1->graphEff[mID[iMethod]]->GetEXlow();
      double * denomErrXH     = eff1->graphEff[mIDnorm]->GetEXhigh();
      double * denomErrXL     = eff1->graphEff[mIDnorm]->GetEXlow();
      // check if numerator and denominator have the same bin numbers
      if(N!=eff1->graphEff[mIDnorm]->GetN()){
	std::cout<<"WARNING!!! Number of Points of numerator ("<<N<<") and denominator ("<<eff1->graphEff[mIDnorm]->GetN()<<") different!!!"<<std::endl;
	std::cout<<"SF for method "<<mID[iMethod] <<" for titles "<< eff1->titles<<" is only calculated for numerator points!!!"<<std::endl;
	//continue;
      }
      // set points and errors of SF graph
      double SF     = -1., SFErrH = -1., SFErrL = -1.;
      for(int iPointNum=0; iPointNum< N ; iPointNum++){
	// loop over denominator points to find the matching point
	for(int iPointDenom=iPointNum; iPointDenom < eff1->graphEff[mIDnorm]->GetN(); iPointDenom++){
	  // check if binning is the same: either bin boundaries the same or point itself
	  if((numeratorX[iPointNum]-numeratorErrXL[iPointNum] == denomX[iPointDenom]-denomErrXL[iPointDenom] && numeratorX[iPointNum]+numeratorErrXH[iPointNum] == denomX[iPointDenom]+denomErrXH[iPointDenom]) || numeratorX[iPointNum]==denomX[iPointDenom]){
	    SF     = numerator[iPointNum]/denom[iPointDenom];
	    // calculate asymmetric errors
	    SFErrH = SF*TMath::Sqrt(numeratorErrH[iPointNum]*numeratorErrH[iPointNum] / (numerator[iPointNum]*numerator[iPointNum]) + denomErrL[iPointDenom]*denomErrL[iPointDenom]/(denom[iPointDenom]*denom[iPointDenom]));
	    SFErrL = SF*TMath::Sqrt(numeratorErrL[iPointNum]*numeratorErrL[iPointNum] / (numerator[iPointNum]*numerator[iPointNum]) + denomErrH[iPointDenom]*denomErrH[iPointDenom]/(denom[iPointDenom]*denom[iPointDenom]));
	    SFgraph -> SetPoint(iPointNum, numeratorX[iPointNum], SF);
	    double xErrH=0;
	    double xErrL=0;
	    // set x errors if desired
	    if(!method1[mID[iMethod]]->drawOpt.Contains("X0")){
	      xErrH=numeratorErrXH[iPointNum];
	      xErrL=numeratorErrXL[iPointNum];
	    }
	    // set y errors to 0 for reference SF
	    if(mID[iMethod]==mIDnorm){
	      SFErrH=0;
	      SFErrL=0;
	    }
	    SFgraph -> SetPointError(iPointNum, xErrL, xErrH, SFErrL, SFErrH);
	    break;
	  }
	  if(iPointDenom==eff1->graphEff[mIDnorm]->GetN()-1) std::cout<< "WARNING!!!! For numerator point x="<<numeratorX[iPointDenom]<<" no denominator found!!!"<<std::endl;
	}
      }
      
      // Print efficiency and SF
      if(eff1->var=="Control"){
	std::cout<< SFgraph ->GetTitle() << "SF. = " << numerator[0] <<"+" <<numeratorErrH[0] << "-" <<numeratorErrL[0] <<
	    " / " << denom[0] <<"+" <<denomErrH[0] << "-" <<denomErrL[0] << 
	    " = " << SF     <<"+" <<SFErrH << "-" <<SFErrL << std::endl; 
      }

      if(iMethod==0){
	if(xLo!=-9999. && xHi!=-9999.) SFgraph->GetXaxis()->SetRangeUser(xLo,xHi);
	if(yLo!=-9999. && yHi!=-9999.) SFgraph->GetYaxis()->SetRangeUser(yLo,yHi);
	drawOpt="P A";
      }
      else drawOpt="P same";
      /// specific ratio plot configuration
    // configure axis of ratio plot
//     SFgraph->GetXaxis()->SetTitleSize(eff1->graphEff[mID[iMethod]]->GetXaxis()->GetTitleSize()*scaleFactor);
//     SFgraph->GetXaxis()->SetTitleOffset(eff1->graphEff[mID[iMethod]]->GetXaxis()->GetTitleOffset());
//     SFgraph->GetXaxis()->SetLabelSize(eff1->graphEff[mID[iMethod]]->GetXaxis()->GetLabelSize()*scaleFactor);
    SFgraph->GetXaxis()->SetTitleSize(0.1);
    SFgraph->GetXaxis()->SetTitleOffset(1.15);
    SFgraph->GetXaxis()->SetLabelSize(0.1);
    SFgraph->GetXaxis()->SetLabelOffset(0.02);
    SFgraph->GetXaxis()->SetTitle( eff1->graphEff[mID[iMethod]]->GetXaxis()->GetTitle() );
    SFgraph->GetXaxis()->SetNdivisions(eff1->graphEff[mID[iMethod]]->GetXaxis()->GetNdivisions());
    if((TString)(SFgraph->GetXaxis()->GetTitle())=="relIso") SFgraph->GetXaxis()->SetNdivisions(509);
    
    SFgraph->GetYaxis()->CenterTitle();
    SFgraph->GetYaxis()->SetTitle("SF");
    SFgraph->GetYaxis()->SetTitleSize(0.1);
    SFgraph->GetYaxis()->SetTitleOffset(0.5);
    SFgraph->GetYaxis()->SetLabelSize(0.1);
   // SFgraph->GetYaxis()->SetLabelOffset(eff1->graphEff[mID[iMethod]]->GetYaxis()->GetLabelOffset()*3.3);
    SFgraph->GetYaxis()->SetTickLength(0.03);
    SFgraph->GetYaxis()->SetNdivisions(505);
    //SFgraph->GetXaxis()->SetRange(eff1->graphEff[mID[iMethod]]->GetXaxis()->GetFirst(), eff1->graphEff[mID[iMethod]]->GetXaxis()->GetLast());
    // delete axis of initial plot
   //eff1->graphEff[mID[iMethod]]->GetXaxis()->SetLabelSize(0);
   //eff1->graphEff[mID[iMethod]]->GetXaxis()->SetTitleSize(0);
 
      SFgraph->DrawClone(drawOpt.Data());
      /// assign the graph to the eff structure
      eff1->graphSF[mID[iMethod]]=SFgraph;
    }
  }
  
  /// operate at pad after drawing
  // create pad to hide old axis
  TPad *whitebox = new TPad("whitebox","",0,0.9,0.098,1.);
  whitebox->SetFillColor(10);
  whitebox->SetFillStyle(1001);
  whitebox->SetBorderSize(0);
  whitebox->SetBorderMode(0);
  whitebox->Draw("");
//   TPad *whitebox2 = new TPad("whitebox2","",0,0.2,0.09,0.4);
//   whitebox2->SetFillColor(10);
//   whitebox2->SetFillStyle(1001);
//   whitebox2->SetBorderSize(0);
//   whitebox2->SetBorderMode(0);
//   whitebox2->Draw("");
  rPad->SetTopMargin(0.0);
  rPad->SetBottomMargin(0.15*scaleFactor);
  rPad->SetRightMargin(right);
  gPad->SetLeftMargin(left);
  //gPad->RedrawAxis();
  gPad->cd();
  rPad->Draw();
  
 //  mainpad->cd();
//   mainpad->RedrawAxis();
 //  his0->Draw("");
//   leg.DrawClone();
    // draw grid
//    rPad->SetGrid(1,1);
  
}

/// ---
/// draw raw N_event plots for all and pass histos of one variable for all methods, incl. legend
/// ---
void drawEventHistos(eff* eff1, std::map<TString, method*> method1, std::vector<TString> mID, double legXlo, double legYlo, double legXhi, double legYhi, bool drawLeg=true, TString normalize="")
{
  TH1 *hisPass;
  TH1 *hisAll;
  TString drawOpt="";
  TString legTitle="";
  
  TLegend leg(legXlo, legYlo, legXhi, legYhi);
  leg.SetFillStyle(0);
  
  for(unsigned int iMethod=0; iMethod<mID.size(); iMethod++){
    hisPass = (TH1D*) eff1->hisPass[mID[iMethod]]->Clone("newHisPass");
    hisPass->SetLineStyle(2);
    hisAll = (TH1D*) eff1->hisAll[mID[iMethod]]->Clone("newHisAll");
    hisAll->SetLineStyle(1);
    
    // normalize if desired
    if(normalize=="normMax"){
//       std::cout<<"Event number histos are normalized to their maxima"<<std::endl;
//       std::cout<<"Maximum hisPass: "<<hisPass->GetBinContent(hisPass->GetMaximumBin())<<std::endl;
//       std::cout<<"Maximum hisAll: " <<hisAll ->GetBinContent(hisAll ->GetMaximumBin())<<std::endl;
      hisPass->Scale(1./hisPass->GetBinContent(hisPass->GetMaximumBin()));
      hisAll ->Scale(1./hisAll ->GetBinContent(hisAll->GetMaximumBin()));
    }
    else if(normalize=="normInt"){
//       std::cout<<"Event number histos are normalized to their integral"<<std::endl;
//       std::cout<<"Maximum hisPass: "<<hisPass->GetBinContent(hisPass->GetMaximumBin())<<std::endl;
//       std::cout<<"Maximum hisAll: " <<hisAll ->GetBinContent(hisAll ->GetMaximumBin())<<std::endl;
      hisPass->Scale(1./hisPass->Integral(1,hisPass->GetNbinsX()));
      hisAll ->Scale(1./hisAll ->Integral(1,hisAll ->GetNbinsX()));
    }
    
    if(iMethod==0) drawOpt = "L";
    else           drawOpt = "L same";
    
    hisAll ->Draw(drawOpt.Data());
    //hisPass->Draw("same");
    // legend
    legTitle=method1[mID[iMethod]]->legName + " all";
    if(method1[mID[iMethod]]->legOpt!="") leg.AddEntry(hisAll, legTitle, method1[mID[iMethod]]->legOpt);
    legTitle=method1[mID[iMethod]]->legName + " pass";
    //if(method1[mID[iMethod]]->legOpt!="") leg.AddEntry(hisPass, legTitle, method1[mID[iMethod]]->legOpt);
  }
  if(drawLeg) leg.DrawClone();
}

/// ---
/// FIT method for efficiency determination
/// pass eff_[lepLepMass] to eff1
/// ---
void getEffFromFit(eff* eff1, std::map<TString, method*> method1, std::vector<TString> mID, TCanvas *& Canv, double legXlo, double legYlo, double legXhi, double legYhi, bool drawLeg=true)
{
  TH1 *hisPass;
  TH1 *hisAll;
  TString drawOpt="";
  TString legTitle="";
  
  int mIDNum = mID.size();
  Canv->Divide(mIDNum/2+1, 2);
  
  TLegend leg(legXlo, legYlo, legXhi, legYhi);
  leg.SetFillStyle(0);
  
  std::cout << "-------" << std::endl;
  std::cout << "!!!!!!!!!!! Fits for " << mID.size() <<" methods " <<std::endl;
   for(unsigned int iMethod=0; iMethod<mID.size(); iMethod++){
    std::cout << "!!!! iMethod" << iMethod <<" mID "<< mID[iMethod] <<std::endl;
    Canv->cd(iMethod+1);
    hisPass = (TH1D*) eff1->hisPass[mID[iMethod]]->Clone("newHisPass");
    hisPass->SetLineColor(2);
    hisPass->SetLineStyle(1);
    hisAll = (TH1D*) eff1->hisAll[mID[iMethod]]->Clone("newHisAll");
    hisAll->SetLineColor(1);
    hisAll->SetLineStyle(1);
    
    hisAll ->Draw("L");
    hisPass->Draw("same");
    // legend
    legTitle=method1[mID[iMethod]]->legName + " all";
    if(method1[mID[iMethod]]->legOpt!="") leg.AddEntry(hisAll, legTitle, method1[mID[iMethod]]->legOpt);
    legTitle=method1[mID[iMethod]]->legName + " pass";
    //if(method1[mID[iMethod]]->legOpt!="") leg.AddEntry(hisPass, legTitle, method1[mID[iMethod]]->legOpt);
    
    // Fit!!!
//     fVoigtExpBkg->SetParameters(5e4, 91., 2.5, 2., 100., -100.);
    fVoigtExpBkg->SetParameters(5e4, 91., 2.5, 2., 40., -0.005);
    //fVoigtExpBkg->FixParameter(2,2.5);
//     fVoigtExpBkg->FixParameter(4.,0.);
//     fVoigtExpBkg->FixParameter(5.,1.);
    
    // unique name for each iMethod
    TString namefVoigtExpBkgAll  = Form("fVoigtExpBkgAll%i",iMethod);
    TString namefVoigtExpBkgPass = Form("fVoigtExpBkgPass%i",iMethod);
    
    TF1 * fVoigtExpBkgAll  = (TF1*)fVoigtExpBkg->Clone(namefVoigtExpBkgAll);
    TF1 * fVoigtExpBkgPass = (TF1*)fVoigtExpBkg->Clone(namefVoigtExpBkgPass);
    TF1 * fExpBkgAll  = new TF1("fExpBkgAll","[0]*TMath::Exp([1]*(x-60))",60.,140.);
    TF1 * fExpBkgPass = new TF1("fExpBkgPass","[0]*TMath::Exp([1]*(x-60))",60.,140.);
    fVoigtExpBkgPass->SetLineStyle(2);
    fVoigtExpBkgPass->SetLineColor(4);
    
    std::cout << "Fitting hisAll" << std::endl;
    hisAll -> Fit(namefVoigtExpBkgAll,"","same", 61.,121.);
    fExpBkgAll->SetParameter(0,fVoigtExpBkgAll->GetParameter(4));
    fExpBkgAll->SetParameter(1,fVoigtExpBkgAll->GetParameter(5));
    fExpBkgAll->SetLineStyle(2);
    fExpBkgAll->SetLineColor(8);
    fExpBkgAll->Draw("same");
    
    fExpBkgPass->SetParameter(0,fVoigtExpBkgPass->GetParameter(4));
    fExpBkgPass->SetParameter(1,fVoigtExpBkgPass->GetParameter(5));
    fExpBkgPass->SetLineStyle(2);
    fExpBkgPass->SetLineColor(8);
    fExpBkgPass->Draw("same");
    
    std::cout << "Fitting hisPass" << std::endl;
    hisPass -> Fit(namefVoigtExpBkgPass,"","same", 61.,121.);
    
    // take integral of fit curve to count number of events
    double NevtsFitAll  = fVoigtExpBkgAll ->Integral(76.,106.);
    double NevtsFitPass = fVoigtExpBkgPass->Integral(76.,106.);
    double NevtsBGAll   = fExpBkgAll      ->Integral(76.,106.);
    double NevtsBGPass  = fExpBkgPass     ->Integral(76.,106.);
    double effFit       = (NevtsFitPass-NevtsBGPass)/(NevtsFitAll-NevtsBGAll);
    
    
    // print integral for different ranges
    std::cout << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << "Integral interv.: 76-106; NevtsFitAll = " << NevtsFitAll << "; NevtsFitPass = " << NevtsFitPass << "; effFit = " << effFit << std::endl;
    std::cout << "Integral interv.: 76-106; NevtsBGAll = " << NevtsBGAll << "; NevtsBGPass = " << NevtsBGPass << std::endl;
    std::cout << "Integral interv.: 71-111; NevtsFitAll = " << fVoigtExpBkgAll ->Integral(71.,111.) << "; NevtsFitPass = " << fVoigtExpBkgPass->Integral(71.,111.) << "; effFit = " << fVoigtExpBkgPass->Integral(71.,111.)/fVoigtExpBkgAll->Integral(71.,111.) << std::endl;
    std::cout << "Integral interv.: 81-101; NevtsFitAll = " << fVoigtExpBkgAll ->Integral(81.,101.) << "; NevtsFitPass = " << fVoigtExpBkgPass->Integral(81.,101.) << "; effFit = " << fVoigtExpBkgPass->Integral(81.,101.)/fVoigtExpBkgAll->Integral(81.,101.) << std::endl;
    std::cout << "Integral interv.: 61-121; NevtsFitAll = " << fVoigtExpBkgAll ->Integral(61.,121.) << "; NevtsFitPass = " << fVoigtExpBkgPass->Integral(61.,121.) << "; effFit = " << fVoigtExpBkgPass->Integral(61.,121.)/fVoigtExpBkgAll->Integral(61.,121.) << std::endl;
    std::cout << "Integral interv.: 83.5-98.5; NevtsFitAll = " << fVoigtExpBkgAll ->Integral(83.5,98.5) << "; NevtsFitPass = " << fVoigtExpBkgPass->Integral(83.5,98.5) << "; effFit = " << fVoigtExpBkgPass->Integral(83.5,98.5)/fVoigtExpBkgAll->Integral(83.5,98.5) << std::endl;
    std::cout << "-------" << std::endl;
    
    
  }
  if(drawLeg) leg.DrawClone();
}

#endif