#ifndef plotterclass_h
#define plotterclass_h

#include "THStack.h"
#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TH1F.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "TCanvas.h"
#include "TLegend.h"
#include "TSystem.h"
#include "TExec.h"
#include "TStyle.h"
#include "TMath.h"
#include "TROOT.h"
#include <sstream>
#include "basicFunctions.h"
#include "HHStyle.h"
#include "TGraphAsymmErrors.h"
class Plotter {

 public:
  Plotter();
  Plotter(TString, TString, TString, double, double);
  ~Plotter();
  void   setOptions(TString, TString, TString, bool, bool, double, double, double, double, int, std::vector<double>, std::vector<double>);
  void   setDataSet(std::vector<TString>, std::vector<double>, std::vector<TString>, std::vector<int>, TString);
  void   setDataSet(TString);
  void   setSystDataSet(TString);
  void   fillSystHisto();
  void   fillHisto();
  void setStyle(TH1D&, unsigned int);
  void setStyle(TH1&, unsigned int);
  void   write();
  double CalcXSec();
  void PlotXSec();
  void PlotDiffXSec();
  void DYScaleFactor();
  void CalcInclSystematics(TString Systematic, int syst_number);
  void CalcDiffSystematics(TString Systematic, int syst_number);
  void InclFlatSystematics(int syst_number);
  void DiffFlatSystematics(int syst_number,  int nbins);
  TLegend* getNewLegend();
  TH1* GetNloCurve(const char *particle, const char *quantity, const char *generator);
 private:
  TString name;
  int bins;
  double rangemin, rangemax, ymin, ymax;
  std::vector<TFile> files, filesUp, filesDown;
  std::vector<TString> dataset, datasetUp, datasetDown;
  std::vector<double> scales;
  std::vector<TString> legends, legendsUp, legendsDown;
  std::vector<int> colors, colorsUp, colorsDown;
  std::vector<double> XAxisbins, XAxisbinCenters;
  double DYScale[4];
  TString DYEntry;
  TString YAxis;
  TString XAxis;
  TString channel;
  int channelType; //0=ee 1==mumu 2==emu 3==combined  
  TH1D onehist;
  std::vector<TH1D> hists;
  std::vector<TH1D> systhistsUp;
  std::vector<TH1D> systhistsDown;
  bool initialized, logX, logY;
  int lumi;
  TString channelLabel[4];
  double InclusiveXsection[4];
  double InclusiveXsectionStatError[4];
  double InclusiveXsectionTotalError[4];
  double InclusiveXsectionSysError[4];
  double InclusiveXsectionSysErrorBySyst[4][15];
  double DiffXSec[4][10];//the differential X-section per channel by bin [channel][bin]
  double DiffXSecStatError[4][10];//the differential X-section Error per channel by bin [channel][bin]
  double DiffXSecSysError[4][10];//the differential X-section Error per channel by bin [channel][bin]
  double DiffXSecSysErrorBySyst[4][10][15];//the differential X-section Error per channel by bin [channel][bin][systematic]
  double DiffXSecTotalError[4][10];//the differential X-section Error per channel by bin [channel][bin]
  double VisXsection[4][10];//needed for bin-by-bin corrections to combination [channel][bin]
  double VisXsectionError[4][10];//needed for bin-by-bin corrections to combination [channel][bin]
  double GenDiffXSec[4][10];//the differential X-section per channel by bin [channel][bin]
  double GenDiffXSecError[4][10];//the differential X-section Error per channel by bin [channel][bin]

};


void Plotter::DYScaleFactor(){
  TH1::AddDirectory(kFALSE);
  ifstream FileList("HistoFileList_combined.txt");
  TString filename;
  
  double NoutEEDYMC=0, NinEEDYMC=0, NoutMuMuDYMC=0, NinMuMuDYMC=0;//Number of events in/out of z-veto region for the DY MC
  double NinEE=0, NinMuMu=0, NinEMu=0;//Number of events in z-veto region for data
  double NinEEloose=0, NinMuMuloose=0;//Number of data events in Z-Veto region with MET cut
  double NinEEMC=0, NinMuMuMC=0;//All other MC events
  
  while(!FileList.eof()){
    FileList>>filename;
    
    if(filename!=""){
      if(filename.Contains("ee")){
	if(filename.Contains("run")){
	  TH1D *htemp = (TH1D*)TFile::Open(filename)->Get("Zh1"); NinEE+=htemp->Integral();
	  TH1D *htemp1 = (TH1D*)TFile::Open(filename)->Get("Looseh1"); NinEEloose+=htemp1->Integral();	  
	}
	else if(filename.Contains("dy")){
	  if(filename.Contains("50inf")){
	    TH1D *htemp = (TH1D*)TFile::Open(filename)->Get("Zh1"); NinEEDYMC+=htemp->Integral();
	    TH1D *htemp1 = (TH1D*)TFile::Open(filename)->Get("TTh1"); NoutEEDYMC+=htemp1->Integral();
	  }
	  else{TH1D *htemp = (TH1D*)TFile::Open(filename)->Get("TTh1"); NoutEEDYMC+=htemp->Integral();}
	}	
	else{
	  TH1D *htemp = (TH1D*)TFile::Open(filename)->Get("Zh1"); NinEEMC+=htemp->Integral();
	}
      }
      
      if(filename.Contains("emu")){
	if(filename.Contains("run")){TH1D *htemp = (TH1D*)TFile::Open(filename)->Get("Zh1"); NinEMu+=htemp->Integral();}
      }
	
      if(filename.Contains("mumu")){
	if(filename.Contains("run")){
	  TH1D *htemp = (TH1D*)TFile::Open(filename)->Get("Zh1"); NinMuMu+=htemp->Integral();
	  TH1D *htemp1 = (TH1D*)TFile::Open(filename)->Get("Looseh1"); NinMuMuloose+=htemp1->Integral();
	}
	else if(filename.Contains("dy")){
	  if(filename.Contains("50inf")){
	    TH1D *htemp = (TH1D*)TFile::Open(filename)->Get("Zh1"); NinMuMuDYMC+=htemp->Integral();
	    TH1D *htemp1 = (TH1D*)TFile::Open(filename)->Get("TTh1"); NoutMuMuDYMC+=htemp1->Integral();}
	  else{TH1D *htemp = (TH1D*)TFile::Open(filename)->Get("TTh1"); NoutMuMuDYMC+=htemp->Integral();}
	}	
	else{
	  TH1D *htemp = (TH1D*)TFile::Open(filename)->Get("Zh1"); NinMuMuMC+=htemp->Integral();
	}
      }      
    }
  }
  double NoutMCEE = (NoutEEDYMC/NinEEDYMC)*(NinEE - 0.5*NinEMu*sqrt(NinEEloose/NinMuMuloose));
  double NoutMCMuMu = (NoutMuMuDYMC/NinMuMuDYMC)*(NinMuMu - 0.5*NinEMu*sqrt(NinMuMuloose/NinEEloose));
  
  double DYSFEE = NoutMCEE/NoutEEDYMC;
  double DYSFMuMu = NoutMCMuMu/NoutMuMuDYMC;

  cout<<"DYSFEE: "<<DYSFEE<<endl;
  cout<<"DYSFMuMu: "<<DYSFMuMu<<endl;

  DYScale[0]=DYSFEE;
  DYScale[1]=DYSFMuMu;
  DYScale[2]=1.;
  DYScale[3]=(DYSFEE+DYSFMuMu)/2;//not correct, fix later

}

void Plotter::InclFlatSystematics(int syst_number){
  
  //trigger uncertainties

  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .025;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .015;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .02;}//emu  

  syst_number++;

  //Lepton selection

  InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .04;//all 
  syst_number++;

  //Other Backgrounds (needs to be varied in Analysis.C)

  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .024;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .019;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .022;}//emu  
  syst_number++;

  //DY Backgrounds (needs to be varied in Analysis.C)
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .021;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .031;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .001;}//emu  
  syst_number++;

  //PU (for now)
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .003;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .003;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .001;}//emu  
  syst_number++;

  //B-tagging (for now)
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .06;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .06;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .06;}//emu  
  syst_number++;

  //KinFit 
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .02;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .02;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .017;}//emu  
  syst_number++;

  //Hadronization (for now)
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .049;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .043;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .054;}//emu  
  syst_number++;

  //Top Quark Mass (for now)
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .009;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .013;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .009;}//emu  
  syst_number++;

  //Q^2 scale (for now)
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .032;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .021;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .017;}//emu  
  syst_number++;

  //Matrix Element threshold (for now)
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .028;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .022;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .012;}//emu  
  syst_number++;

  //Branching Ratio
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .015;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .015;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .015;}//emu  
  syst_number++;

  //Luminosity
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .045;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .045;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .045;}//emu  
  syst_number++;

}
void Plotter::DiffFlatSystematics(int syst_number, int nbins){
  
  for(int bin = 0; bin<nbins; bin++){
    int syst = syst_number;
    //trigger uncertainties
    
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .025;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .015;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .02;}//emu  
    syst++;
    
    //Lepton selection
    
    DiffXSecSysErrorBySyst[channelType][bin][syst] = .02;//all (different from inclusive?) 
    syst++;
    
    //Other Backgrounds
    
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .003;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .003;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .003;}//emu  
    syst++;
    
    //DY Backgrounds
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .014;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .016;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .005;}//emu  
    syst++;
    
    //PU (for now)
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .004;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .004;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .003;}//emu  
    syst++;
    
    //B-tagging (for now)
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .017;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .017;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .017;}//emu  
    syst++;
    
    //KinFit 
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .005;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .005;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .005;}//emu  
    syst++;
    
    //Hadronization (for now)
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .006;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .01;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .003;}//emu  
    syst++;
    
    //Top Quark Mass (for now)
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .005;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .003;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .002;}//emu  
    syst++;
    
  //Q^2 scale (for now)
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .024;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .013;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .006;}//emu  
    syst++;
    
    //Matrix Element threshold (for now)
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .006;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .011;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .006;}//emu  
    syst++;
    
  }
}

void Plotter::CalcInclSystematics(TString Systematic, int syst_number){
  setSystDataSet(Systematic);
  fillSystHisto();

  TH1D* stacksum = (TH1D*)hists[2].Clone();
  TH1D* stacksumUp = (TH1D*)systhistsUp[2].Clone();
  TH1D* stacksumDown = (TH1D*)systhistsDown[2].Clone();

  for(unsigned int i=3; i<hists.size() ; i++){ // prepare histos and leg
    TH1 *htemp = (TH1D*)hists[i].Clone();
    stacksum->Add(htemp);
  }
  for(unsigned int i=3; i<systhistsUp.size() ; i++){ // prepare histos and leg
    TH1 *htemp = (TH1D*)systhistsUp[i].Clone();
    stacksumUp->Add(htemp);
  }
  for(unsigned int i=3; i<systhistsDown.size() ; i++){ // prepare histos and leg
    TH1 *htemp = (TH1D*)systhistsDown[i].Clone();
    stacksumDown->Add(htemp);
  }
  double Sys_Error_Up, Sys_Error_Down, Sys_Error, Sum_Errors;
  double scale = 1.;

  TH1D* h_sys  = (TH1D*) stacksumUp->Clone();   h_sys->Reset();
  TH1D* h_sys2 = (TH1D*) stacksumDown->Clone(); h_sys2->Reset();
  
  Sys_Error_Up   = abs(stacksum->Integral() - stacksumUp->Integral())/stacksum->Integral();
  Sys_Error_Down = abs(stacksum->Integral() - stacksumDown->Integral())/stacksum->Integral();
  Sys_Error  = (Sys_Error_Up+Sys_Error_Down)/(2.*scale);
  Sum_Errors += Sys_Error;

  InclusiveXsectionSysErrorBySyst[channelType][syst_number] = Sys_Error;
  //cout<<"Sys_Error: "<<Sys_Error<<endl;

}

void Plotter::CalcDiffSystematics(TString Systematic, int syst_number){

  double Xbins[XAxisbins.size()];
  for(unsigned int i = 0; i<XAxisbins.size();i++){Xbins[i]=XAxisbins[i];}
  setSystDataSet(Systematic);
  fillSystHisto();
  TH1D* stacksum = (TH1D*)hists[2].Rebin(bins,"stack",Xbins);
  TH1D* stacksumUp = (TH1D*)systhistsUp[2].Rebin(bins,"stackup",Xbins);
  TH1D* stacksumDown = (TH1D*)systhistsDown[2].Rebin(bins,"stackdown",Xbins);

  //DYScale Factor...
  for(unsigned int i=3; i<hists.size() ; i++){ // prepare histos and leg
    TH1 *htemp = (TH1D*)hists[i].Rebin(bins,"htemp",Xbins);
    stacksum->Add(htemp);
  }
  for(unsigned int i=3; i<systhistsUp.size() ; i++){ // prepare histos and leg
    TH1 *htempup = (TH1D*)systhistsUp[i].Rebin(bins,"htempup",Xbins);
    stacksumUp->Add(htempup);
  }
  for(unsigned int i=3; i<systhistsDown.size() ; i++){ // prepare histos and leg
    TH1 *htempdown = (TH1D*)systhistsDown[i].Rebin(bins,"htempdown",Xbins);
    stacksumDown->Add(htempdown);
  }
  double Sys_Error_Up, Sys_Error_Down, Sys_Error, Sum_Errors;
  double scale = 1.;

  for(Int_t bin = 0; bin <= stacksum->GetNbinsX(); ++bin) {
    if( stacksum->GetBinContent(bin+1) == 0 )  continue;
    Sys_Error_Up   = abs(stacksum->GetBinContent(bin+1) - stacksumUp->GetBinContent(bin+1))/stacksum->GetBinContent(bin+1);
    Sys_Error_Down = abs(stacksum->GetBinContent(bin+1) - stacksumDown->GetBinContent(bin+1))/stacksum->GetBinContent(bin+1);
    Sys_Error  = (Sys_Error_Up+Sys_Error_Down)/(2.*scale);
    Sum_Errors += Sys_Error;
    DiffXSecSysErrorBySyst[channelType][bin][syst_number] = Sys_Error;//the differential X-section Error per channel by bin [channel][bin][systematic]
  } 

}

Plotter::Plotter()
{
  name="defaultName";
  rangemin=0;
  rangemax=3;
  YAxis="N_{events}";
  initialized=false;
  
}

Plotter::Plotter(TString name_, TString XAxis_,TString YAxis_, double rangemin_, double rangemax_)
{
  name=name_;
  rangemin=rangemin_;
  rangemax=rangemax_;
  XAxis=XAxis_;
  YAxis=YAxis_;
  initialized=false;
}

Plotter::~Plotter()
{
}

void Plotter::setOptions(TString name_, TString YAxis_, TString XAxis_, bool logX_, bool logY_, double ymin_, double ymax_, double rangemin_, double rangemax_, int bins_, std::vector<double>XAxisbins_, std::vector<double>XAxisbinCenters_)
{
  XAxisbins.clear();
  XAxisbinCenters.clear();
  XAxisbinCenters = XAxisbinCenters_;
  XAxisbins = XAxisbins_;
  name=name_;
  bins=bins_;
  logX = logX_;
  logY = logY_;
  ymin = ymin_;
  ymax = ymax_;
  rangemin=rangemin_;
  rangemax=rangemax_;
  YAxis=YAxis_;
  XAxis=XAxis_;
  DYScale[0]=1.;
  DYScale[1]=1.;
  DYScale[2]=1.;
  DYScale[3]=1.;
}


void Plotter::setDataSet(std::vector<TString> dataset_, std::vector<double> scales_, std::vector<TString> legends_, std::vector<int> colors_, TString DYEntry_)
{
  dataset.clear();
  scales.clear();
  legends.clear();
  colors.clear();
  dataset=dataset_;
  scales=scales_;
  legends=legends_;
  colors=colors_;
  DYEntry=DYEntry_;
}

void Plotter::setDataSet(TString mode)
{
  initialized=false;

  channel=mode;
  if(channel =="ee"){channelType=0;channelLabel[0]="ee";}
  if(channel =="mumu"){channelType=1;channelLabel[1]="#mu#mu";}
  if(channel =="emu"){channelType=2;channelLabel[2]="e#mu";}
  if(channel =="combined"){channelType=3;channelLabel[3]="Dilepton Combined";}

  lumi=1141;
  
  DYEntry = "Z^{0} / #gamma* #rightarrow ee/#mu#mu";

  if(channel=="ee"){  
    ifstream FileList("HistoFileList_ee.txt");
    TString filename;

    dataset.clear();
    legends.clear();
    colors.clear();
  
    while(!FileList.eof()){
      FileList>>filename;

      if(filename!=""){
	dataset.push_back(filename);
	if(filename.Contains("run")){legends.push_back("data"); colors.push_back(kBlack);}
	else if(filename.Contains("ttbarsignal")){legends.push_back("t#bar{t} signal"); colors.push_back(kRed+1);}
	else if(filename.Contains("ttbarbg")){legends.push_back("t#bar{t} background"); colors.push_back(kRed+2);}
	else if(filename.Contains("single")){legends.push_back("tW"); colors.push_back(kMagenta);}
	else if(filename.Contains("ww") ||filename.Contains("wz")||filename.Contains("zz")){legends.push_back("VV"); colors.push_back(kYellow-10);}
	else if(filename.Contains("dytautau")){legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau"); colors.push_back(kAzure+8);}
	else if(filename.Contains("dymumu")||filename.Contains("dyee")){legends.push_back("Z^{0} / #gamma* #rightarrow ee/#mu#mu"); colors.push_back(kAzure-2);}
//	else if(filename.Contains("dyee")){legends.push_back("Z^{0} / #gamma* #rightarrow ee"); colors.push_back(kAzure-2);}
	else if(filename.Contains("wtolnu")){legends.push_back("W #rightarrow l#nu"); colors.push_back(kGreen-3);}
	else if(filename.Contains("qcd")){legends.push_back("QCD"); colors.push_back(kYellow);}
      }
    }
  }

  if(mode=="mumu"){

    dataset.clear();
    legends.clear();
    colors.clear();
    ifstream FileList("HistoFileList_mumu.txt");
    TString filename;

    while(!FileList.eof()){
      FileList>>filename;

      if(filename!=""){
	dataset.push_back(filename);

	if(filename.Contains("run")){legends.push_back("data"); colors.push_back(kBlack);}
	else if(filename.Contains("ttbarsignal")){legends.push_back("t#bar{t} signal"); colors.push_back(kRed+1);}
	else if(filename.Contains("ttbarbg")){legends.push_back("t#bar{t} background"); colors.push_back(kRed+2);}
	else if(filename.Contains("single")){legends.push_back("tW"); colors.push_back(kMagenta);}
	else if(filename.Contains("ww") ||filename.Contains("wz")||filename.Contains("zz")){legends.push_back("VV"); colors.push_back(kYellow-10);}
	else if(filename.Contains("dytautau")){legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau"); colors.push_back(kAzure+8);}
	else if(filename.Contains("dymumu")||filename.Contains("dyee")){legends.push_back("Z^{0} / #gamma* #rightarrow ee/#mu#mu"); colors.push_back(kAzure-2);}
	else if(filename.Contains("wtolnu")){legends.push_back("W #rightarrow l#nu"); colors.push_back(kGreen-3);}
	else if(filename.Contains("qcd")){legends.push_back("QCD"); colors.push_back(kYellow);}
      }
    }
  }
  if(mode=="emu"){

    dataset.clear();
    legends.clear();
    colors.clear();
    ifstream FileList("HistoFileList_emu.txt");
    TString filename;

    while(!FileList.eof()){
      FileList>>filename;

      if(filename!=""){
	dataset.push_back(filename);
	
	if(filename.Contains("run")){legends.push_back("data"); colors.push_back(kBlack);}
	else if(filename.Contains("ttbarsignal")){legends.push_back("t#bar{t} signal"); colors.push_back(kRed+1);}
	else if(filename.Contains("ttbarbg")){legends.push_back("t#bar{t} background"); colors.push_back(kRed+2);}
	else if(filename.Contains("single")){legends.push_back("tW"); colors.push_back(kMagenta);}
	else if(filename.Contains("ww") ||filename.Contains("wz")||filename.Contains("zz")){legends.push_back("VV"); colors.push_back(kYellow-10);}
	else if(filename.Contains("dytautau")){legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau"); colors.push_back(kAzure+8);}
	else if(filename.Contains("dymumu")||filename.Contains("dyee")){legends.push_back("Z^{0} / #gamma* #rightarrow ee/#mu#mu"); colors.push_back(kAzure-2);}
	else if(filename.Contains("wtolnu")){legends.push_back("W #rightarrow l#nu"); colors.push_back(kGreen-3);}
	else if(filename.Contains("qcd")){legends.push_back("QCD"); colors.push_back(kYellow);}
      }
    }
  }
  if(mode=="combined"){

    dataset.clear();
    legends.clear();
    colors.clear();
    ifstream FileList("HistoFileList_combined.txt");
    TString filename;

    while(!FileList.eof()){
      FileList>>filename;

      if(filename!=""){
	dataset.push_back(filename);
	
	if(filename.Contains("run")){legends.push_back("data"); colors.push_back(kBlack);}
	else if(filename.Contains("ttbarsignal")){legends.push_back("t#bar{t} signal"); colors.push_back(kRed+1);}
	else if(filename.Contains("ttbarbg")){legends.push_back("t#bar{t} background"); colors.push_back(kRed+2);}
	else if(filename.Contains("single")){legends.push_back("tW"); colors.push_back(kMagenta);}
	else if(filename.Contains("ww") ||filename.Contains("wz")||filename.Contains("zz")){legends.push_back("VV"); colors.push_back(kYellow-10);}
	else if(filename.Contains("dytautau")){legends.push_back("Z^{0} / #gamma* #rightarrow #tau#tau"); colors.push_back(kAzure+8);}
	else if(filename.Contains("dymumu")||filename.Contains("dyee")){legends.push_back("Z^{0} / #gamma* #rightarrow ee/#mu#mu"); colors.push_back(kAzure-2);}
	else if(filename.Contains("wtolnu")){legends.push_back("W #rightarrow l#nu"); colors.push_back(kGreen-3);}
	else if(filename.Contains("qcd")){legends.push_back("QCD"); colors.push_back(kYellow);}
      }
    }
  }
}

void Plotter::setSystDataSet(TString systematic)
{
  initialized=false;

  DYEntry = "Z^{0} / #gamma* #rightarrow ee/#mu#mu";
  lumi=1141;
  if(channel=="ee"){  
    TString HistoFileUp = "HistoFileList_"+systematic+"UP_"+channel+".txt";
    TString HistoFileDown = "HistoFileList_"+systematic+"DOWN_"+channel+".txt";
    ifstream FileListUp(HistoFileUp);
    ifstream FileListDown(HistoFileDown);
    TString filenameUp, filenameDown;

    datasetUp.clear();
    datasetDown.clear();
    legendsUp.clear();
    legendsDown.clear();
    colorsUp.clear();
    colorsDown.clear();
  
    while(!FileListUp.eof()){
      FileListUp>>filenameUp;

      if(filenameUp!=""){
	datasetUp.push_back(filenameUp);
	if(filenameUp.Contains("run")){legendsUp.push_back("data"); colorsUp.push_back(kBlack);}
	else if(filenameUp.Contains("ttbarsignal")){legendsUp.push_back("t#bar{t} signal"); colorsUp.push_back(kRed+1);}
	else if(filenameUp.Contains("ttbarbg")){legendsUp.push_back("t#bar{t} background"); colorsUp.push_back(kRed+2);}
	else if(filenameUp.Contains("single")){legendsUp.push_back("tW"); colorsUp.push_back(kMagenta);}
	else if(filenameUp.Contains("ww") ||filenameUp.Contains("wz")||filenameUp.Contains("zz")){legendsUp.push_back("VV"); colorsUp.push_back(kYellow-10);}
	else if(filenameUp.Contains("dytautau")){legendsUp.push_back("Z^{0} / #gamma* #rightarrow #tau#tau"); colorsUp.push_back(kAzure+8);}
	else if(filenameUp.Contains("dymumu")||filenameUp.Contains("dyee")){legendsUp.push_back("Z^{0} / #gamma* #rightarrow ee/#mu#mu"); colorsUp.push_back(kAzure-2);}
	else if(filenameUp.Contains("wtolnu")){legendsUp.push_back("W #rightarrow l#nu"); colorsUp.push_back(kGreen-3);}
	else if(filenameUp.Contains("qcd")){legendsUp.push_back("QCD"); colorsUp.push_back(kYellow);}
      }
    }
    while(!FileListDown.eof()){
      FileListDown>>filenameDown;
      if(filenameDown!=""){
	datasetDown.push_back(filenameDown);
	if(filenameDown.Contains("run")){legendsDown.push_back("data"); colorsDown.push_back(kBlack);}
	else if(filenameDown.Contains("ttbarsignal")){legendsDown.push_back("t#bar{t} signal"); colorsDown.push_back(kRed+1);}
	else if(filenameDown.Contains("ttbarbg")){legendsDown.push_back("t#bar{t} background"); colorsDown.push_back(kRed+2);}
	else if(filenameDown.Contains("single")){legendsDown.push_back("tW"); colorsDown.push_back(kMagenta);}
	else if(filenameDown.Contains("ww") ||filenameDown.Contains("wz")||filenameDown.Contains("zz")){legendsDown.push_back("VV"); colorsDown.push_back(kYellow-10);}
	else if(filenameDown.Contains("dytautau")){legendsDown.push_back("Z^{0} / #gamma* #rightarrow #tau#tau"); colorsDown.push_back(kAzure+8);}
	else if(filenameDown.Contains("dymumu")||filenameDown.Contains("dyee")){legendsDown.push_back("Z^{0} / #gamma* #rightarrow ee/#mu#mu"); colorsDown.push_back(kAzure-2);}
	else if(filenameDown.Contains("wtolnu")){legendsDown.push_back("W #rightarrow l#nu"); colorsDown.push_back(kGreen-3);}
	else if(filenameDown.Contains("qcd")){legendsDown.push_back("QCD"); colorsDown.push_back(kYellow);}
      }
    }
  }

  if(channel=="mumu"){  
    TString HistoFileUp = "HistoFileList_"+systematic+"UP_"+channel+".txt";
    TString HistoFileDown = "HistoFileList_"+systematic+"DOWN_"+channel+".txt";
    ifstream FileListUp(HistoFileUp);
    ifstream FileListDown(HistoFileDown);
    TString filenameUp, filenameDown;

    datasetUp.clear();
    datasetDown.clear();
    legendsUp.clear();
    legendsDown.clear();
    colorsUp.clear();
    colorsDown.clear();
  
    while(!FileListUp.eof()){
      FileListUp>>filenameUp;

      if(filenameUp!=""){
	datasetUp.push_back(filenameUp);
	if(filenameUp.Contains("run")){legendsUp.push_back("data"); colorsUp.push_back(kBlack);}
	else if(filenameUp.Contains("ttbarsignal")){legendsUp.push_back("t#bar{t} signal"); colorsUp.push_back(kRed+1);}
	else if(filenameUp.Contains("ttbarbg")){legendsUp.push_back("t#bar{t} background"); colorsUp.push_back(kRed+2);}
	else if(filenameUp.Contains("single")){legendsUp.push_back("tW"); colorsUp.push_back(kMagenta);}
	else if(filenameUp.Contains("ww") ||filenameUp.Contains("wz")||filenameUp.Contains("zz")){legendsUp.push_back("VV"); colorsUp.push_back(kYellow-10);}
	else if(filenameUp.Contains("dytautau")){legendsUp.push_back("Z^{0} / #gamma* #rightarrow #tau#tau"); colorsUp.push_back(kAzure+8);}
	else if(filenameUp.Contains("dymumu")||filenameUp.Contains("dyee")){legendsUp.push_back("Z^{0} / #gamma* #rightarrow ee/#mu#mu"); colorsUp.push_back(kAzure-2);}
	else if(filenameUp.Contains("wtolnu")){legendsUp.push_back("W #rightarrow l#nu"); colorsUp.push_back(kGreen-3);}
	else if(filenameUp.Contains("qcd")){legendsUp.push_back("QCD"); colorsUp.push_back(kYellow);}
      }
    }
    while(!FileListDown.eof()){
      FileListDown>>filenameDown;
      if(filenameDown!=""){
	datasetDown.push_back(filenameDown);
	if(filenameDown.Contains("run")){legendsDown.push_back("data"); colorsDown.push_back(kBlack);}
	else if(filenameDown.Contains("ttbarsignal")){legendsDown.push_back("t#bar{t} signal"); colorsDown.push_back(kRed+1);}
	else if(filenameDown.Contains("ttbarbg")){legendsDown.push_back("t#bar{t} background"); colorsDown.push_back(kRed+2);}
	else if(filenameDown.Contains("single")){legendsDown.push_back("tW"); colorsDown.push_back(kMagenta);}
	else if(filenameDown.Contains("ww") ||filenameDown.Contains("wz")||filenameDown.Contains("zz")){legendsDown.push_back("VV"); colorsDown.push_back(kYellow-10);}
	else if(filenameDown.Contains("dytautau")){legendsDown.push_back("Z^{0} / #gamma* #rightarrow #tau#tau"); colorsDown.push_back(kAzure+8);}
	else if(filenameDown.Contains("dymumu")||filenameDown.Contains("dyee")){legendsDown.push_back("Z^{0} / #gamma* #rightarrow ee/#mu#mu"); colorsDown.push_back(kAzure-2);}
	else if(filenameDown.Contains("wtolnu")){legendsDown.push_back("W #rightarrow l#nu"); colorsDown.push_back(kGreen-3);}
	else if(filenameDown.Contains("qcd")){legendsDown.push_back("QCD"); colorsDown.push_back(kYellow);}
      }
    }
  }

  if(channel=="emu"){  
    TString HistoFileUp = "HistoFileList_"+systematic+"UP_"+channel+".txt";
    TString HistoFileDown = "HistoFileList_"+systematic+"DOWN_"+channel+".txt";
    ifstream FileListUp(HistoFileUp);
    ifstream FileListDown(HistoFileDown);
    TString filenameUp, filenameDown;

    datasetUp.clear();
    datasetDown.clear();
    legendsUp.clear();
    legendsDown.clear();
    colorsUp.clear();
    colorsDown.clear();
  
    while(!FileListUp.eof()){
      FileListUp>>filenameUp;

      if(filenameUp!=""){
	datasetUp.push_back(filenameUp);
	if(filenameUp.Contains("run")){legendsUp.push_back("data"); colorsUp.push_back(kBlack);}
	else if(filenameUp.Contains("ttbarsignal")){legendsUp.push_back("t#bar{t} signal"); colorsUp.push_back(kRed+1);}
	else if(filenameUp.Contains("ttbarbg")){legendsUp.push_back("t#bar{t} background"); colorsUp.push_back(kRed+2);}
	else if(filenameUp.Contains("single")){legendsUp.push_back("tW"); colorsUp.push_back(kMagenta);}
	else if(filenameUp.Contains("ww") ||filenameUp.Contains("wz")||filenameUp.Contains("zz")){legendsUp.push_back("VV"); colorsUp.push_back(kYellow-10);}
	else if(filenameUp.Contains("dytautau")){legendsUp.push_back("Z^{0} / #gamma* #rightarrow #tau#tau"); colorsUp.push_back(kAzure+8);}
	else if(filenameUp.Contains("dymumu")||filenameUp.Contains("dyee")){legendsUp.push_back("Z^{0} / #gamma* #rightarrow ee/#mu#mu"); colorsUp.push_back(kAzure-2);}
	else if(filenameUp.Contains("wtolnu")){legendsUp.push_back("W #rightarrow l#nu"); colorsUp.push_back(kGreen-3);}
	else if(filenameUp.Contains("qcd")){legendsUp.push_back("QCD"); colorsUp.push_back(kYellow);}
      }
    }
    while(!FileListDown.eof()){
      FileListDown>>filenameDown;
      if(filenameDown!=""){
	datasetDown.push_back(filenameDown);
	if(filenameDown.Contains("run")){legendsDown.push_back("data"); colorsDown.push_back(kBlack);}
	else if(filenameDown.Contains("ttbarsignal")){legendsDown.push_back("t#bar{t} signal"); colorsDown.push_back(kRed+1);}
	else if(filenameDown.Contains("ttbarbg")){legendsDown.push_back("t#bar{t} background"); colorsDown.push_back(kRed+2);}
	else if(filenameDown.Contains("single")){legendsDown.push_back("tW"); colorsDown.push_back(kMagenta);}
	else if(filenameDown.Contains("ww") ||filenameDown.Contains("wz")||filenameDown.Contains("zz")){legendsDown.push_back("VV"); colorsDown.push_back(kYellow-10);}
	else if(filenameDown.Contains("dytautau")){legendsDown.push_back("Z^{0} / #gamma* #rightarrow #tau#tau"); colorsDown.push_back(kAzure+8);}
	else if(filenameDown.Contains("dymumu")||filenameDown.Contains("dyee")){legendsDown.push_back("Z^{0} / #gamma* #rightarrow ee/#mu#mu"); colorsDown.push_back(kAzure-2);}
	else if(filenameDown.Contains("wtolnu")){legendsDown.push_back("W #rightarrow l#nu"); colorsDown.push_back(kGreen-3);}
	else if(filenameDown.Contains("qcd")){legendsDown.push_back("QCD"); colorsDown.push_back(kYellow);}
      }
    }
  }

  if(channel=="combined"){  
    TString HistoFileUp = "HistoFileList_"+systematic+"UP_"+channel+".txt";
    TString HistoFileDown = "HistoFileList_"+systematic+"DOWN_"+channel+".txt";
    ifstream FileListUp(HistoFileUp);
    ifstream FileListDown(HistoFileDown);
    TString filenameUp, filenameDown;

    datasetUp.clear();
    datasetDown.clear();
    legendsUp.clear();
    legendsDown.clear();
    colorsUp.clear();
    colorsDown.clear();
  
    while(!FileListUp.eof()){
      FileListUp>>filenameUp;

      if(filenameUp!=""){
	datasetUp.push_back(filenameUp);
	if(filenameUp.Contains("run")){legendsUp.push_back("data"); colorsUp.push_back(kBlack);}
	else if(filenameUp.Contains("ttbarsignal")){legendsUp.push_back("t#bar{t} signal"); colorsUp.push_back(kRed+1);}
	else if(filenameUp.Contains("ttbarbg")){legendsUp.push_back("t#bar{t} background"); colorsUp.push_back(kRed+2);}
	else if(filenameUp.Contains("single")){legendsUp.push_back("tW"); colorsUp.push_back(kMagenta);}
	else if(filenameUp.Contains("ww") ||filenameUp.Contains("wz")||filenameUp.Contains("zz")){legendsUp.push_back("VV"); colorsUp.push_back(kYellow-10);}
	else if(filenameUp.Contains("dytautau")){legendsUp.push_back("Z^{0} / #gamma* #rightarrow #tau#tau"); colorsUp.push_back(kAzure+8);}
	else if(filenameUp.Contains("dymumu")||filenameUp.Contains("dyee")){legendsUp.push_back("Z^{0} / #gamma* #rightarrow ee/#mu#mu"); colorsUp.push_back(kAzure-2);}
	else if(filenameUp.Contains("wtolnu")){legendsUp.push_back("W #rightarrow l#nu"); colorsUp.push_back(kGreen-3);}
	else if(filenameUp.Contains("qcd")){legendsUp.push_back("QCD"); colorsUp.push_back(kYellow);}
      }
    }
    while(!FileListDown.eof()){
      FileListDown>>filenameDown;
      if(filenameDown!=""){
	datasetDown.push_back(filenameDown);
	if(filenameDown.Contains("run")){legendsDown.push_back("data"); colorsDown.push_back(kBlack);}
	else if(filenameDown.Contains("ttbarsignal")){legendsDown.push_back("t#bar{t} signal"); colorsDown.push_back(kRed+1);}
	else if(filenameDown.Contains("ttbarbg")){legendsDown.push_back("t#bar{t} background"); colorsDown.push_back(kRed+2);}
	else if(filenameDown.Contains("single")){legendsDown.push_back("tW"); colorsDown.push_back(kMagenta);}
	else if(filenameDown.Contains("ww") ||filenameDown.Contains("wz")||filenameDown.Contains("zz")){legendsDown.push_back("VV"); colorsDown.push_back(kYellow-10);}
	else if(filenameDown.Contains("dytautau")){legendsDown.push_back("Z^{0} / #gamma* #rightarrow #tau#tau"); colorsDown.push_back(kAzure+8);}
	else if(filenameDown.Contains("dymumu")||filenameDown.Contains("dyee")){legendsDown.push_back("Z^{0} / #gamma* #rightarrow ee/#mu#mu"); colorsDown.push_back(kAzure-2);}
	else if(filenameDown.Contains("wtolnu")){legendsDown.push_back("W #rightarrow l#nu"); colorsDown.push_back(kGreen-3);}
	else if(filenameDown.Contains("qcd")){legendsDown.push_back("QCD"); colorsDown.push_back(kYellow);}
      }
    }
  }
}


void Plotter::fillHisto()
{
  TH1::AddDirectory(kFALSE);
  if(!initialized){
    hists.clear();
    for(unsigned int i=0; i<dataset.size(); i++){
      TFile *ftemp = TFile::Open(dataset[i]);
      //TH1D *hist = (TH1D*)ftemp->Get(name)->Clone();
      TH1D *hist = (TH1D*)ftemp->Get("Hyp"+name)->Clone();
      if(name.Contains("Lepton")){
      	TString stemp = name;
	stemp.ReplaceAll("Lepton",6,"AntiLepton",10);
	TH1D *hist2 = (TH1D*)ftemp->Get("Hyp"+stemp)->Clone();     
      	hist->Add(hist2);
      }
      if(name.Contains("Top")){
      	TString stemp = name;
	stemp.ReplaceAll("Top",3,"AntiTop",7);
	TH1D *hist2 = (TH1D*)ftemp->Get("Hyp"+stemp)->Clone();     
      	hist->Add(hist2);
      }
      
      setHHStyle(*gStyle);
      //gStyle->SetErrorX(0);
      hists.push_back(*hist);
      //ftemp->Close("R");
      //delete hist;
      delete ftemp;
    }
    initialized=true;
  }
}

void Plotter::fillSystHisto()
{
  TH1::AddDirectory(kFALSE);
  if(!initialized){
    systhistsUp.clear();
    systhistsDown.clear();
    for(unsigned int i=0; i<datasetUp.size(); i++){
      TFile *ftemp = TFile::Open(datasetUp[i]);
      TH1D *hist = (TH1D*)ftemp->Get("Hyp"+name)->Clone();     
      if(name.Contains("Lepton")){
      	TString stemp = name;
	stemp.ReplaceAll("Lepton",6,"AntiLepton",10);
	TH1D *hist2 = (TH1D*)ftemp->Get("Hyp"+stemp)->Clone();     
      	hist->Add(hist2);
      }
      if(name.Contains("Top")){
      	TString stemp = name;
	stemp.ReplaceAll("Top",3,"AntiTop",7);
	TH1D *hist2 = (TH1D*)ftemp->Get("Hyp"+stemp)->Clone();     
      	hist->Add(hist2);
      }
      
      setHHStyle(*gStyle);
      //gStyle->SetErrorX(0);
      systhistsUp.push_back(*hist);
      delete ftemp;
    }
    for(unsigned int i=0; i<datasetDown.size(); i++){
      TFile *ftemp = TFile::Open(datasetDown[i]);
      TH1D *hist = (TH1D*)ftemp->Get("Hyp"+name)->Clone();     
      if(name.Contains("Lepton")){
      	TString stemp = name;
	stemp.ReplaceAll("Lepton",6,"AntiLepton",10);
	TH1D *hist2 = (TH1D*)ftemp->Get("Hyp"+stemp)->Clone();     
      	hist->Add(hist2);
      }
      if(name.Contains("Top")){
      	TString stemp = name;
	stemp.ReplaceAll("Top",3,"AntiTop",7);
	TH1D *hist2 = (TH1D*)ftemp->Get("Hyp"+stemp)->Clone();     
      	hist->Add(hist2);
      }
      
      setHHStyle(*gStyle);
      //gStyle->SetErrorX(0);
      systhistsDown.push_back(*hist);
      delete ftemp;
    }
    initialized=true;
  }
}


void Plotter::write() // do scaling, stacking, legending, and write in file MISSING: DY Rescale
{
  if(initialized){

  TCanvas * c = new TCanvas("","");

  THStack * stack=  new THStack("def", "def");
  TLegend * leg =  new TLegend(0.70,0.65,0.95,0.90);

  TH1D *drawhists[hists.size()];

  std::stringstream ss;
  ss << DYScale[channelType];
  TString scale;
  int signalHist = -1;
  scale=(TString)ss.str();
  
  leg->Clear();
  c->Clear();
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  c->SetName("");
  c->SetTitle("");
  for(unsigned int i=0; i<hists.size() ; i++){ // prepare histos and leg
    drawhists[i]=(TH1D*) hists[i].Clone();
    setStyle(*drawhists[i], i);
    if(legends[i]!=legends[i+1] && i!=(hists.size()-1)){
      drawhists[i]->SetLineColor(1);
    }

    if(legends[i] != "data"){
      if(legends[i] == "t#bar{t} signal"){signalHist = i;}
      if((legends[i] == DYEntry) && channelType!=2 ){
	drawhists[i]->Scale(DYScale[channelType]);
      }
      if(i > 1){
	if(legends[i] != legends[i-1]){
	  if((legends[i] == DYEntry)&& DYScale[channelType] != 1) leg->AddEntry(drawhists[i], legends[i],"f");
	  else leg->AddEntry(drawhists[i], legends[i] ,"f");
	}
      }
      stack->Add(drawhists[i]);  
    }
    else{
      if(i==0) leg->AddEntry(drawhists[i], legends[i] ,"pe");
      if(i>0){
	if(legends[i] != legends[i-1]){
	  leg->AddEntry(drawhists[i], legends[i] ,"pe");
	}
	if(legends[i] == legends[0]){
	  drawhists[0]->Add(drawhists[i]);
	}
      }
    }
  }
  TList* l = stack->GetHists();
  TH1D* stacksum = (TH1D*) l->At(0)->Clone();
  for (int i = 1; i < l->GetEntries(); ++i) {
    stacksum->Add((TH1D*)l->At(i));
  }
  //stat uncertainty::make a function
  TH1D* syshist =0;
  syshist = (TH1D*)stacksum->Clone();
  double lumierr = 0.045;
  for(Int_t i=0; i<=syshist->GetNbinsX(); ++i){
    
    Double_t binc = 0;
    binc += stacksum->GetBinContent(i);
    syshist->SetBinContent(i, binc);
    // calculate uncertainty: lumi uncertainty
    Double_t binerr2 = binc*binc*lumierr*lumierr;
    Double_t topunc = 0; // uncertainty on top xsec
    
    double topxsec = 169.9; //157.5
    double topxsecErr2 = 3.9*3.9 + 16.3*16.3;

    //    double topRelUnc = InclusiveXsectionStatError[channelType]/InclusiveXsection[channelType];
    double topRelUnc =  TMath::Sqrt(topxsecErr2)/topxsec;
    topunc += drawhists[signalHist]->GetBinContent(i)*topRelUnc;
    binerr2 += (topunc*topunc);
    syshist->SetLineColor(1);
    syshist->SetBinError(i, TMath::Sqrt(binerr2));
  }    



  if(logY)c->SetLogy();
  syshist->SetFillStyle(3004);
  syshist->SetFillColor(kBlack);
  leg->AddEntry( syshist, "uncertainty", "f" );

  drawhists[0]->SetMinimum(ymin);
  if(logY){  
    drawhists[0]->SetMaximum(20*drawhists[0]->GetBinContent(drawhists[0]->GetMaximumBin()));
  }
  else{drawhists[0]->SetMaximum(1.2*drawhists[0]->GetBinContent(drawhists[0]->GetMaximumBin()));}


  drawhists[0]->Draw("e1");
  stack->Draw("same HIST");
  gPad->RedrawAxis();
  TExec *setex1 = new TExec("setex1","gStyle->SetErrorX(0.5)");//this is frustrating and stupid but apparently necessary...
  setex1->Draw();
  syshist->Draw("same,E2");
  TExec *setex2 = new TExec("setex2","gStyle->SetErrorX(0.)");
  setex2->Draw();
  drawhists[0]->Draw("same,e1");
  
  DrawCMSLabels(true, 1143);
  DrawDecayChLabel(channelLabel[channelType]);    
  leg->Draw("SAME");
  drawRatio(drawhists[0], stacksum, 0.5, 1.9, *gStyle);
  gSystem->MakeDirectory("Plots");
  gSystem->MakeDirectory("Plots/"+channel);
  c->Print("Plots/"+channel+"/"+name+".eps");
  c->Clear();
  leg->Clear();
  delete c;
  delete leg;
  //delete stack;
  }
  else std::cout << "Histogram " << name << " not filled during the process." << std::endl;
}

void Plotter::setStyle(TH1 &hist, unsigned int i)
{
  hist.SetFillColor(colors[i]);
  hist.SetLineColor(colors[i]);
  

  if(legends[i] == "data"){
    hist.SetFillColor(0);
    hist.SetMarkerStyle(20); 
    hist.SetMarkerSize(1.);
    hist.SetLineWidth(1);
    hist.GetXaxis()->SetLabelFont(42);
    hist.GetYaxis()->SetTitleOffset(1.7);
    hist.GetXaxis()->SetTitle(XAxis);
    //hist.GetXaxis()->SetTitle("M^{t#bar{t}} #left[#frac{GeV}{c^{2}}#right]");
    hist.GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d#sigma}{dX}");
  }
}

void Plotter::setStyle(TH1D &hist, unsigned int i)
{
  hist.SetFillColor(colors[i]);
  hist.SetLineColor(colors[i]);
  

  if(legends[i] == "data"){
    hist.SetMarkerStyle(20); 
    hist.SetMarkerSize(1.);
    hist.SetLineWidth(1);
    hist.GetXaxis()->SetLabelFont(42);
    hist.GetXaxis()->SetTitle(XAxis);
    hist.GetYaxis()->SetTitle(YAxis);
    hist.GetYaxis()->SetTitleOffset(1.7);
  }
}

void Plotter::PlotXSec(){
  
     // measured results with statistical error
   Double_t mx[]   = {      0.50,       1.50,       2.50,       3.50};
   Double_t mexl[] = {      0.00,       0.00,       0.00,       0.00};
   Double_t mexh[] = {      0.00,       0.00,       0.00,       0.00};

   TGraphAsymmErrors *mplot = new TGraphAsymmErrors(4, mx, InclusiveXsection, mexl, mexh,InclusiveXsectionStatError, InclusiveXsectionStatError);
   mplot->SetMarkerStyle(20);
   mplot->SetMarkerColor(kBlack);
   mplot->SetMarkerSize(1.5);
   mplot->SetLineColor(kBlack);
   
   for(int i=0; i<4; i++){
     InclusiveXsectionTotalError[i] = sqrt(InclusiveXsectionStatError[i]*InclusiveXsectionStatError[i] +InclusiveXsection[i]*InclusiveXsectionSysError[i]*InclusiveXsection[i]*InclusiveXsectionSysError[i]);
   }

   TGraphAsymmErrors *mplotwithsys = new TGraphAsymmErrors(4, mx, InclusiveXsection, mexl, mexh,InclusiveXsectionTotalError, InclusiveXsectionTotalError);
   mplotwithsys->SetMarkerStyle(20);
   mplotwithsys->SetMarkerColor(kBlack);
   mplotwithsys->SetMarkerSize(1.5);
   mplotwithsys->SetLineColor(kBlack);

   // mstw
   Double_t mstwmean = 157.5;
   Double_t mstwx[]   = {    -0.5,     0.5,	1.5,	 2.5,	  3.5,     4.5};
   Double_t mstwy[]   = {mstwmean,mstwmean,mstwmean,mstwmean,mstwmean,mstwmean};
   Double_t mstwexl[] = {      .4,	.4,	 .5,	  .5,	   .5,      .5};
   Double_t mstwexh[] = {      .5,	.5,	 .5,	  .5,	   .4,      .4};
   Double_t mstweyl[] = {    24.4,    24.4,    24.4,	24.4,	 24.4,    24.4};
   Double_t mstweyh[] = {    23.2,    23.2,    23.2,	23.2,	 23.2,    23.2};

   TGraphAsymmErrors *mstwplot = new TGraphAsymmErrors(6, mstwx, mstwy, mstwexl, mstwexh, mstweyl, mstweyh);
   mstwplot->SetLineColor(kGreen+1);
   mstwplot->SetLineWidth(4);
   mstwplot->SetFillColor(kGreen+1);
   mstwplot->SetFillStyle(3004);

   // herapdf
   Double_t heramean = 144.156;
   Double_t herapdfx[]   = {	-0.5,	  0.5,     1.5,     2.5,     3.5,     4.5};
   Double_t herapdfy[]   = {heramean,heramean,heramean,heramean,heramean,heramean};
   Double_t herapdfexl[] = {	  .4,	   .4,      .5,      .5,      .5,      .5};
   Double_t herapdfexh[] = {	  .5,	   .5,      .5,      .5,      .4,      .4};
   Double_t herapdfeyl[] = {  13.849,  13.849,  13.849,  13.849,  13.849,  13.849};
   Double_t herapdfeyh[] = {   5.475,	5.475,   5.475,   5.475,   5.475,   5.475};

   TGraphAsymmErrors *herapdfplot = new TGraphAsymmErrors(6, herapdfx, herapdfy, herapdfexl, herapdfexh, herapdfeyl, herapdfeyh);
   herapdfplot->SetLineColor(kBlue+1);
   herapdfplot->SetLineWidth(4);
   herapdfplot->SetFillColor(kBlue+1);
   herapdfplot->SetFillStyle(3005);

   TH1F* framehist = new TH1F("framehist","",4,0.,4.);
   framehist->SetMinimum(0);
   framehist->SetMaximum(310);
   framehist->GetXaxis()->SetTickLength(0);
   framehist->GetXaxis()->SetBinLabel(1,"");
   framehist->GetXaxis()->SetBinLabel(2,"");
   framehist->GetXaxis()->SetBinLabel(3,"");
   framehist->GetYaxis()->SetTitle("#sigma [pb]");
   framehist->GetYaxis()->CenterTitle(kTRUE);

   TPaveText* box1 = new TPaveText(0.25,0.33,0.33,0.43,"NDC");
   box1->SetFillColor(10);
   box1->SetTextSize(0.04);
   box1->AddText("ee");

   TPaveText* box2 = new TPaveText(0.44,0.33,0.52,0.43,"NDC");
   box2->SetFillColor(10);
   box2->SetTextSize(0.04);
   box2->AddText("#mu#mu");

   TPaveText* box3 = new TPaveText(0.62,0.33,0.72,0.43,"NDC");
   box3->SetFillColor(10);
   box3->SetTextSize(0.04);
   box3->AddText("e#mu");

   TPaveText* box4 = new TPaveText(0.82,0.33,0.90,0.43,"NDC");
   box4->SetFillColor(10);
   box4->SetTextSize(0.04);
   box4->AddText("combined");

   TLegend* leg = getNewLegend(); // new TLegend( 0.56, 0.18, 0.89, 0.33 );
   leg->SetBorderSize( 0 );
   leg->SetFillColor( 0 );
   leg->SetTextFont(62);
   leg->SetTextSize(0.03);
   leg->AddEntry( mplot,       "Measurements",            "p"  );
   leg->AddEntry( mstwplot,    "MCFM #otimes MSTW08",     "lf" );
   leg->AddEntry( herapdfplot, "MCFM #otimes HERAPDF1.0", "lf" );

   TCanvas* c = new TCanvas("plot", "plot", 1200, 800);
   framehist->Draw();
   herapdfplot->Draw("C,2,SAME");
   mstwplot->Draw("C,2,SAME");
   gStyle->SetEndErrorSize(8);
   mplot->Draw("p,SAME");
   mplotwithsys->Draw("p,SAME,Z");
   leg ->Draw("SAME");
   box1->Draw("SAME");
   box2->Draw("SAME");
   box3->Draw("SAME");
   box4->Draw("SAME");
   c->Print("Plots/"+channel+"/InclusiveXSec.eps");
   c->Clear();
   delete c;
  
}

double Plotter::CalcXSec(){
  TH1::AddDirectory(kFALSE);
  //  CalcInclSystematics("JES",0);
  //CalcInclSystematics("RES",1);
  //InclFlatSystematics(2);
  
  double syst_square=0;

  for(int i =0; i<15; i++){
    syst_square += InclusiveXsectionSysErrorBySyst[channelType][i]*InclusiveXsectionSysErrorBySyst[channelType][i];
  }
  InclusiveXsectionSysError[channelType] = sqrt(syst_square);
  //cout<<"&^&^&^&^&^&^^&^&^ InclusiveXsectionSysError[channelType]: "<<InclusiveXsectionSysError[channelType]<<endl;
  double BranchingFraction[4]={0.0167, 0.0162, 0.0328, 0.06569};//[ee, mumu, emu, combined] including tau
  lumi = 1141;

  TH1D *numhists[hists.size()];
  double numbers[4]={0};

  for(unsigned int i=0; i<dataset.size(); i++){
    TFile *ftemp = TFile::Open(dataset[i]);
    TH1D *hist = (TH1D*)ftemp->Get("HypjetMultiXSec")->Clone();     
    numhists[i]=hist;
    delete ftemp;
  }


  for(unsigned int i=0; i<hists.size() ; i++){ // prepare histos and leg

    if(legends[i] == "data"){
      //cout<<legends[i]<<" = "<<numhists[i]->Integral()<<endl;
      numbers[0]+=numhists[i]->Integral();
    }
    else if(legends[i] == "t#bar{t} signal"){
      TFile *ftemp2 = TFile::Open(dataset[i]);
      TH1D *NoPUPlot = (TH1D*)ftemp2->Get("HypjetMultiNoPU")->Clone();
      //cout<<legends[i]<<" = "<<numhists[i]->Integral()<<endl;
      numbers[1]+=NoPUPlot->Integral();
      delete ftemp2;
      
      TFile *ftemp = TFile::Open(dataset[i]);
      TH1D *GenPlot = (TH1D*)ftemp->Get("GenAll")->Clone();
      numbers[2]+=GenPlot->Integral();
      delete ftemp;
    } 
    else{      
      if(legends[i] == "W #rightarrow l#nu"){
	//cout<<"numhists->Integral():"<<numhists[i]->Integral()<<endl;
      }
      if((legends[i] == DYEntry) && channelType!=2){
	numhists[i]->Scale(DYScale[channelType]);
      }
      //cout<<legends[i]<<" = "<<numhists[i]->Integral()<<endl;
      numbers[3]+=(int)numhists[i]->Integral();
    }        
  }  

  double xsec = (numbers[0]-numbers[3])/((numbers[1]/numbers[2])*BranchingFraction[channelType]*lumi);
  double xsecstaterror = TMath::Sqrt(numbers[0])/((numbers[1]/numbers[2])*BranchingFraction[channelType]*lumi);

  if(channelType!=3){
    InclusiveXsection[channelType] = xsec;
    InclusiveXsectionStatError[channelType] = xsecstaterror;
  }else{
    InclusiveXsection[channelType] =(InclusiveXsection[0]/(InclusiveXsectionStatError[0]*InclusiveXsectionStatError[0])
				    +InclusiveXsection[1]/(InclusiveXsectionStatError[1]*InclusiveXsectionStatError[1])			
		   		    +InclusiveXsection[2]/(InclusiveXsectionStatError[2]*InclusiveXsectionStatError[2]))/
				     (1/(InclusiveXsectionStatError[0]*InclusiveXsectionStatError[0])
				    +(1/(InclusiveXsectionStatError[1]*InclusiveXsectionStatError[1]))			
				    +(1/(InclusiveXsectionStatError[2]*InclusiveXsectionStatError[2])));			

    InclusiveXsectionStatError[channelType] =1/(TMath::Sqrt((1/(InclusiveXsectionStatError[0]*InclusiveXsectionStatError[0]))
							+(1/(InclusiveXsectionStatError[1]*InclusiveXsectionStatError[1]))			
    							+(1/(InclusiveXsectionStatError[2]*InclusiveXsectionStatError[2]))));			

    cout<<"!!!!!!!!!!!!!!!!!!!!ee Cross Section: "<<InclusiveXsection[0]<<" +/- "<<InclusiveXsectionStatError[0]<<"(stat) +/- "<<InclusiveXsection[0]*InclusiveXsectionSysError[0]<<"(sys)"<<endl;
    cout<<"!!!!!!!!!!!!!!!!!!!!mumu Cross Section: "<<InclusiveXsection[1]<<" +/- "<<InclusiveXsectionStatError[1]<<"(stat) +/- "<<InclusiveXsection[0]*InclusiveXsectionSysError[1]<<"(sys)"<<endl;
    cout<<"!!!!!!!!!!!!!!!!!!!!emu Cross Section: "<<InclusiveXsection[2]<<" +/- "<<InclusiveXsectionStatError[2]<<"(stat) +/- "<<InclusiveXsection[0]*InclusiveXsectionSysError[2]<<"(sys)"<<endl;
    cout<<"!!!!!!!!!!!!!!!!!!!!Combined Cross Section: "<<InclusiveXsection[3]<<" +/- "<<InclusiveXsectionStatError[3]<<"(stat) +/- "<<InclusiveXsection[0]*InclusiveXsectionSysError[3]<<"(sys)"<<endl;
  }
  return xsec;
}

void Plotter::PlotDiffXSec(){
    TH1::AddDirectory(kFALSE);
    //CalcDiffSystematics("JES", 0);
    //CalcDiffSystematics("RES", 1);
    //DiffFlatSystematics(2,nbins);
    double topxsec = 169.9;
    double BranchingFraction[4]={0.0167, 0.0162, 0.0328, 0.06569};//[ee, mumu, emu]
    //    double SignalEvents = 3701945.0;
    double SignalEvents = 3631452.0;

    double Xbins[XAxisbins.size()];
    for(unsigned int i = 0; i<XAxisbins.size();i++){Xbins[i]=XAxisbins[i];}
    double binCenters[XAxisbinCenters.size()];
    for(unsigned int i = 0; i<XAxisbinCenters.size();i++){binCenters[i]=XAxisbinCenters[i];}
    

    TH1 *RecoPlot = new TH1D;
    TH1 *GenPlot =new TH1D;
    TH1 *GenPlotTheory =new TH1D;
    //    double DataSum[nbins]={0};
    //double GenSignalSum[nbins]={0};
    //double BGSum[nbins]={0};
    double DataSum[XAxisbinCenters.size()];
    double GenSignalSum[XAxisbinCenters.size()];
    double BGSum[XAxisbinCenters.size()];

    TH1 *varhists[hists.size()];

    for (unsigned int i =0; i<hists.size(); i++){
      varhists[i]=hists[i].Rebin(bins,"varhists",Xbins);            
      setStyle(*varhists[i], i);
      if(legends[i] == "t#bar{t} signal"){
	TFile *ftemp2 = TFile::Open(dataset[i]);
	TH1D *temp2 =  (TH1D*)ftemp2->Get("Reco"+name)->Clone();
	if(name.Contains("Lepton")||name.Contains("Top")){
	  temp2->Add((TH1D*)ftemp2->Get("RecoAnti"+name)->Clone());
	}
	//	TH1D *temp2 =  (TH1D*)ftemp2->Get("RecoTTBarMass")->Clone();
	RecoPlot = (TH1D*)temp2->Rebin(bins,"recohists",Xbins);
	//      cout<<legends[i]<<" = "<<numhists[i]->Integral()<<endl;
	//numbers[1]+=NoPUPlot->Integral();
	
	TFile *ftemp = TFile::Open(dataset[i]);
	//	GenPlotTheory=(TH1D*)ftemp->Get("VisGenTTBarMass")->Clone();
	GenPlotTheory=(TH1D*)ftemp->Get("VisGen"+name)->Clone();
	if(name.Contains("Lepton")||name.Contains("Top")){
	  GenPlotTheory->Add((TH1D*)ftemp->Get("VisGenAnti"+name)->Clone());
	}
	GenPlot = GenPlotTheory->Rebin(bins,"genplot",Xbins);	
	delete ftemp;
	delete ftemp2;
      }           
    }

    double efficiencies[XAxisbinCenters.size()];
    for (unsigned int hist =0; hist<hists.size(); hist++){
      for (Int_t bin=0; bin<bins; ++bin) {
	if(legends[hist] == "data"){
	  DataSum[bin]+=varhists[hist]->GetBinContent(bin+1);
	}
	else if(legends[hist] == "t#bar{t} signal"){
	  efficiencies[bin] = (RecoPlot->GetBinContent(bin+1)) / (GenPlot->GetBinContent(bin+1));
	  GenSignalSum[bin] += GenPlot->GetBinContent(bin+1);
	}
	else{
	  BGSum[bin]+=varhists[hist]->Integral(bin,bin+1);
	}
      }
    }
    double binWidth[XAxisbinCenters.size()];
    TH1 *h_DiffXSec = (TH1D*)varhists[0]->Clone();
    TH1 *h_GenDiffXSec = (TH1D*)varhists[0]->Clone();
    h_DiffXSec->Reset();

    for (Int_t i=0; i<bins; ++i) {
      if(channelType!=3){
	binWidth[i] = Xbins[i+1]-Xbins[i];      
	DiffXSec[channelType][i] = (DataSum[i]-BGSum[i])/(efficiencies[i]*binWidth[i]*lumi);
	DiffXSecStatError[channelType][i] = TMath::Sqrt(DataSum[i])/(efficiencies[i]*lumi*binWidth[i]); // statistical error
	GenDiffXSec[channelType][i] = (GenSignalSum[i]*topxsec)/(SignalEvents*BranchingFraction[channelType]*binWidth[i]);//DIRTY (signal*topxsec)/(total events*bf*binwidth)
	GenDiffXSecError[channelType][i] = TMath::Sqrt(DataSum[i])/(efficiencies[i]*lumi*binWidth[i]); // statistical error
	
	// set measured cross section
	if (efficiencies[i] == 0) { //cannot divide by zero
	  cout << "WARNING in PlotDifferentialCrossSection: Efficieny is zero in bin " << i << " while creating " << name << endl;
	  h_DiffXSec->SetBinContent(i+1, 0);
	} else {
	  //cout<<"DiffXSec[i]: "<<DiffXSec[channelType][i]<<endl;;
	  //cout<<"GenDiffXSec[i]: "<<GenDiffXSec[i]<<endl;;
	  h_DiffXSec->SetBinContent(i+1,DiffXSec[channelType][i]);
	  h_GenDiffXSec->SetBinContent(i+1,GenDiffXSec[channelType][i]);
	  h_DiffXSec->SetBinError(i+1,(TMath::Sqrt(DataSum[i]))/(efficiencies[i]*lumi*binWidth[i])); // statistical error
	}
	cout<<endl;
      }else{//For the combination
	DiffXSec[channelType][i] =(DiffXSec[0][i]/(DiffXSecStatError[0][i]*DiffXSecStatError[0][i])
					 +DiffXSec[1][i]/(DiffXSecStatError[1][i]*DiffXSecStatError[1][i])			
					 +DiffXSec[2][i]/(DiffXSecStatError[2][i]*DiffXSecStatError[2][i]))/
	                                 (1/(DiffXSecStatError[0][i]*DiffXSecStatError[0][i])
				         +(1/(DiffXSecStatError[1][i]*DiffXSecStatError[1][i]))			
				         +(1/(DiffXSecStatError[2][i]*DiffXSecStatError[2][i])));			

	DiffXSecStatError[channelType][i]=1/(TMath::Sqrt((1/(DiffXSecStatError[0][i]*DiffXSecStatError[0][i]))
							+(1/(DiffXSecStatError[1][i]*DiffXSecStatError[1][i]))			
    							+(1/(DiffXSecStatError[2][i]*DiffXSecStatError[2][i]))));			

	//cout<<"&&&&&&&&&&&&&&&!!!!!!!!ee DiffCross Sec: "<<DiffXSec[0][i]<<" +/- "<<DiffXSecStatError[0][i]<<endl;
	//cout<<"&&&&&&&&&&&&&&&!!!!!!!!mumu DiffCross Sec: "<<DiffXSec[1][i]<<" +/- "<<DiffXSecStatError[1][i]<<endl;
	//cout<<"&&&&&&&&&&&&&&&!!!!!!!!emu DiffCross Sec: "<<DiffXSec[2][i]<<" +/- "<<DiffXSecStatError[2][i]<<endl;
	//cout<<"&&&&&&&&&&&&&&&!!!!!!!!Combined DiffCross Sec: "<<DiffXSec[3][i]<<" +/- "<<DiffXSecStatError[3][i]<<endl;
	h_DiffXSec->SetBinContent(i+1,DiffXSec[channelType][i]);
	h_DiffXSec->SetBinError(i+1,DiffXSecStatError[channelType][i]);
      }
    }

    //data normalization
    double datascale;
    datascale = 1./h_DiffXSec->Integral("width");//this is fine for one channel, but for the combination?  
    h_DiffXSec->Scale(datascale);
    

    for (Int_t i=0; i<bins; ++i) {//I don't think this is needed, but put it here for good measure
      if(channelType!=3){
	   VisXsection[channelType][i]=DiffXSec[channelType][i]*binWidth[i];//this is probably cheating
	   VisXsectionError[channelType][i]=TMath::Sqrt(DataSum[i])/(efficiencies[i]*lumi);//then this is as well
      }else{
	VisXsection[channelType][i] =(VisXsection[0][i]/(VisXsectionError[0][i]*VisXsectionError[0][i])
				   +VisXsection[1][i]/(VisXsectionError[1][i]*VisXsectionError[1][i])			
				   +VisXsection[2][i]/(VisXsectionError[2][i]*VisXsectionError[2][i]))/
	                          (1/(VisXsectionError[0][i]*VisXsectionError[0][i])
				   +(1/(VisXsectionError[1][i]*VisXsectionError[1][i]))			
				   +(1/(VisXsectionError[2][i]*VisXsectionError[2][i])));			
	
	VisXsectionError[channelType][i]=1/(TMath::Sqrt((1/(VisXsectionError[0][i]*VisXsectionError[0][i]))
						     +(1/(VisXsectionError[1][i]*VisXsectionError[1][i]))			
						     +(1/(VisXsectionError[2][i]*VisXsectionError[2][i]))));				
      }	 
    }
    //need to separate diffxsec calculation and plotting

    //theory curves

    double DiffXSecPlot[XAxisbinCenters.size()];
    double DiffXSecStatErrorPlot[XAxisbinCenters.size()];
    double DiffXSecTotalErrorPlot[XAxisbinCenters.size()];

    for (Int_t bin=0; bin<bins; bin++){//condense matrices to arrays for plotting
      double syst_square = 0;
      for(int syst =0; syst<15; syst++){
	syst_square += DiffXSecSysErrorBySyst[channelType][bin][syst]*DiffXSecSysErrorBySyst[channelType][bin][syst];
	//syst_square += DiffXSec[channelType][bin]*DiffXSecSysErrorBySyst[channelType][bin][syst]*DiffXSec[channelType][bin]*DiffXSecSysErrorBySyst[channelType][bin][syst];
      }
      DiffXSecSysError[channelType][bin] = sqrt(syst_square)*DiffXSec[channelType][bin];
      cout<<"DiffXSec[channelType][bin]: "<<DiffXSec[channelType][bin]<<endl;
      cout<<"DiffXSecSysError[channelType][bin]: "<<DiffXSecSysError[channelType][bin]<<endl;
      cout<<"DiffXSecStatError[channelType][bin]: "<<DiffXSecStatError[channelType][bin]<<endl;
      //DiffXSecTotalError[channelType][bin] = sqrt(DiffXSec[channelType][bin]*DiffXSecSysError[channelType][bin]*DiffXSec[channelType][bin]*DiffXSecSysError[channelType][bin] + DiffXSecStatError[channelType][bin]*DiffXSecStatError[channelType][bin]);
      DiffXSecTotalError[channelType][bin] = sqrt(DiffXSecSysError[channelType][bin]*DiffXSecSysError[channelType][bin] + DiffXSecStatError[channelType][bin]*DiffXSecStatError[channelType][bin]);
      cout<<"DiffXSecTotalError[channelType][bin]: "<<DiffXSecTotalError[channelType][bin]<<endl;

      DiffXSecPlot[bin]=DiffXSec[channelType][bin]*datascale;
      DiffXSecStatErrorPlot[bin]=DiffXSecStatError[channelType][bin]*datascale;
      DiffXSecTotalErrorPlot[bin]=DiffXSecTotalError[channelType][bin]*datascale;
      cout<<"DiffXSecPlot[bin]: "<<DiffXSecPlot[bin]<<endl;
      cout<<"DiffXSecStatErrorPlot[bin]: "<<DiffXSecStatErrorPlot[bin]<<endl;
      cout<<"DiffXSecTotalErrorPlot[bin]: "<<DiffXSecTotalErrorPlot[bin]<<endl<<endl;
    }

    Double_t mexl[XAxisbinCenters.size()];
    Double_t mexh[XAxisbinCenters.size()];
    TGraphAsymmErrors *tga_DiffXSecPlot = new TGraphAsymmErrors(bins, binCenters, DiffXSecPlot, mexl, mexh, DiffXSecStatErrorPlot, DiffXSecStatErrorPlot);
    tga_DiffXSecPlot->SetMarkerStyle(20);
    tga_DiffXSecPlot->SetMarkerColor(kBlack);
    tga_DiffXSecPlot->SetMarkerSize(1);
    tga_DiffXSecPlot->SetLineColor(kBlack);
   
    TGraphAsymmErrors *tga_DiffXSecPlotwithSys = new TGraphAsymmErrors(bins, binCenters, DiffXSecPlot, mexl, mexh, DiffXSecTotalErrorPlot, DiffXSecTotalErrorPlot);
    tga_DiffXSecPlotwithSys->SetMarkerStyle(20);
    tga_DiffXSecPlotwithSys->SetMarkerColor(kBlack);
    tga_DiffXSecPlotwithSys->SetMarkerSize(1);
    tga_DiffXSecPlotwithSys->SetLineColor(kBlack);
   

    GenPlotTheory->Scale(topxsec/(SignalEvents*GenPlotTheory->GetBinWidth(1)));
    
    double genscale = 1./GenPlotTheory->Integral("width");
    
    GenPlotTheory->Scale(genscale);
	
    genscale = 1./ h_GenDiffXSec->Integral("width");
    h_GenDiffXSec->Scale(genscale);



    //    TH1* mcnlohist = GetNloCurve("TtBar","Mass","MCatNLO");
    TH1* mcnlohist = GetNloCurve("Leptons","Pt","MCatNLO");
    double mcnloscale = 1./mcnlohist->Integral("width");
    mcnlohist->Rebin(10);mcnlohist->Scale(0.1);
    mcnlohist->Scale(mcnloscale);

    //    TH1* mcnlohistup = GetNloCurve("TtBar","Mass","MCNLOup");
    TH1* mcnlohistup = GetNloCurve("Leptons","Pt","MCNLOup");
    mcnlohistup->Rebin(10);mcnlohistup->Scale(0.1);
    mcnlohistup->Scale(mcnloscale);

    //    TH1* mcnlohistdown = GetNloCurve("TtBar","Mass","MCNLOdown");
    TH1* mcnlohistdown = GetNloCurve("Leptons","Pt","MCNLOdown");
    mcnlohistdown->Rebin(10);mcnlohistdown->Scale(0.1);
    mcnlohistdown->Scale(mcnloscale);

    //    TH1* powheghist = GetNloCurve("TtBar","Mass","Powheg");
    TH1* powheghist = GetNloCurve("Leptons","Pt","Powheg");
    double powhegscale = 1./powheghist->Integral("width");
    powheghist->Rebin(2);powheghist->Scale(0.5);
    powheghist->Scale(powhegscale);

    //Uncertainty band for MC@NLO
    const Int_t nMCNLOBins = mcnlohistup->GetNbinsX();
    Double_t x[nMCNLOBins];
    Double_t xband[2*nMCNLOBins];
    Double_t errup[nMCNLOBins];
    Double_t errdn[nMCNLOBins];
    Double_t errorband[2*nMCNLOBins];
    
    for( Int_t j = 0; j< nMCNLOBins; j++ ){
      x[j]=mcnlohist->GetBinCenter(j+1);
      errup[j]=mcnlohistup->GetBinContent(j+1);
      errdn[j]=mcnlohistdown->GetBinContent(j+1);
      
      xband[j] = x[j];
      errorband[j] = errdn[j]; //lower band
      xband[2*nMCNLOBins-j-1] = x[j];
      errorband[2*nMCNLOBins-j-1] = errup[j]; //upper band
      
    }
    
    TGraph *mcatnloBand = new TGraph(2*nMCNLOBins, xband, errorband);
    mcatnloBand->SetFillColor(kGray);
    mcatnloBand->SetLineColor(kAzure);
    mcatnloBand->SetLineWidth(2);

    TCanvas * c = new TCanvas("DiffXS","DiffXS");
    
    if(logY){
      c->SetLogy();
    }
    h_DiffXSec->SetMarkerStyle(20);
 
    h_GenDiffXSec->Draw();
    //h_DiffXSec->Draw("SAME, EP0");
    gStyle->SetEndErrorSize(8);
    mcatnloBand->Draw("same, F");

    GenPlotTheory->SetLineColor(2);
    GenPlotTheory->Rebin(4);GenPlotTheory->Scale(1./4.);
    GenPlotTheory->Draw("SAME,C");

    h_GenDiffXSec->SetLineColor(2);
    mcnlohist->SetLineColor(kAzure);
    mcnlohist->Draw("SAME,C");
    powheghist->SetLineColor(kGreen+1);
    powheghist->Draw("SAME,C");
    tga_DiffXSecPlot->Draw("p, SAME");
    tga_DiffXSecPlotwithSys->Draw("p, SAME, Z");
    //h_DiffXSec->Draw("SAME, EP0");
    DrawCMSLabels(true, lumi);
    DrawDecayChLabel(channelLabel[channelType]);    
    
    TLegend leg2 = *getNewLegend();
    leg2.AddEntry(h_DiffXSec, "Data",    "p");
    leg2.AddEntry(GenPlotTheory,            "Madgraph","l");
    if (mcnlohistup->GetEntries() && mcnlohistdown->GetEntries()) leg2.AddEntry(mcatnloBand,      "MC@NLO",  "fl");
    else if (mcnlohist->GetEntries()) leg2.AddEntry(mcnlohist,      "MC@NLO",  "l");
    if (powheghist->GetEntries())  leg2.AddEntry(powheghist,       "Powheg",  "l");        
    leg2.SetFillStyle(0);
    leg2.SetBorderSize(0);
    leg2.Draw("same");
    gPad->RedrawAxis();
    
    c->Print("Plots/"+channel+"/DiffXS.eps");
    c->Clear();
    delete c;
    
    THStack * stack=  new THStack("def", "def");
    TLegend * leg =  new TLegend(0.70,0.65,0.95,0.90);
    //TH1 *varhists[hists.size()];
    
    for(unsigned int i=0; i<hists.size() ; i++){ // prepare histos and leg
      //varhists[i]=(TH1D*) hists[i].Clone();
      setStyle(*varhists[i], i);
      if(legends[i] != "data"){
	if((legends[i] == DYEntry) && channelType!=2){
	  varhists[i]->Scale(DYScale[channelType]);
	}
	if(i > 1){
	  if(legends[i] != legends[i-1]){
	    if( (legends[i] == DYEntry) && DYScale[channelType]!= 1){
	      leg->AddEntry(varhists[i], legends[i]);
	    }else leg->AddEntry(varhists[i], legends[i] ,"f");
	  }
	}
	stack->Add(varhists[i]);  
      }
      else{
	if(i==0) leg->AddEntry(varhists[i], legends[i] ,"pe");
	if(i>0){
	  if(legends[i] != legends[i-1]){
	    leg->AddEntry(varhists[i], legends[i] ,"pe");
	  }
	  if(legends[i] == legends[0]){
	    varhists[0]->Add(varhists[i]);
	  }
	}
      }
    }
    
    TCanvas * c1 = new TCanvas("DiffXS","DiffXS");
    TList* l = stack->GetHists();
    TH1D* stacksum = (TH1D*) l->At(0)->Clone();
    for (int i = 1; i < l->GetEntries(); ++i) {
      stacksum->Add((TH1D*)l->At(i));
    }

    varhists[0]->Draw("el");
    stack->Draw("same HIST");
    varhists[0]->Draw("same, e1");
    DrawCMSLabels(true, 1143);
    DrawDecayChLabel(channelLabel[channelType]);    
    leg->Draw("SAME");
    gPad->RedrawAxis();
    
    c1->Print("Plots/"+channel+"/BinnedMass.eps");
    c1->Clear();
    delete c1;
}

// get generator cross section curve for NLO prediction
TH1* Plotter::GetNloCurve(const char *particle, const char *quantity, const char *generator){

  TH1::AddDirectory(kFALSE);
    TString histname("visible_");
    histname.Append(particle);
    histname.Append(quantity);
    histname.Append("_");
    histname.Append(generator);

    TH1* hist;

    TFile* file = new TFile;

    /*    if(strcmp(generator, "Powheg")==0){file = TFile::Open("/afs/naf.desy.de/user/d/dammann/public/Powheg.root","READ");}
    else if(strcmp(generator, "MCatNLO")==0){file = TFile::Open("/afs/naf.desy.de/user/a/aldaya/public/MCatNLO_status3_v20111028.root","READ");}
    else if(strcmp(generator, "MCNLOup")==0){file = TFile::Open("/afs/naf.desy.de/user/a/aldaya/public/MCatNLO_Uncert_Up_status3_v20111028.root","READ");}
    else if(strcmp(generator, "MCNLOdown")==0){file = TFile::Open("/afs/naf.desy.de/user/a/aldaya/public/MCatNLO_Uncert_Down_status3_v20111028.root","READ");}
    */
    if(strcmp(generator, "Powheg")==0){file = TFile::Open("Powheg.root","READ");}
    else if(strcmp(generator, "MCatNLO")==0){file = TFile::Open("MCatNLO_status3_v20111028.root","READ");}
    else if(strcmp(generator, "MCNLOup")==0){file = TFile::Open("MCatNLO_Uncert_Up_status3_v20111028.root","READ");}
    else if(strcmp(generator, "MCNLOdown")==0){file = TFile::Open("MCatNLO_Uncert_Down_status3_v20111028.root","READ");}

    /*    if(strcmp(generator, "MCatNLO")==0){
      file = mcatnloInput;
    }
    else if(strcmp(generator, "MCNLOup")==0){
      file = mcatnloInputUp;
      std::cerr << "MCNLOUp: " << file->GetName() << std::endl; 
    } 
     else if(strcmp(generator, "MCNLOdown")==0){
      file = mcatnloInputDn;
      std::cerr << "MCNLODn: " << file->GetName() << std::endl; 
    }  
    else if(strcmp(generator, "Powheg")==0){
      file = powhegInput;
    } else{
      std::cerr << "WARNING in GetNloCurve: unknown generator '" << generator << "' specified!" << endl;
    }
    */
    if (file && !file->IsZombie()) {
      file->GetObject<TH1>(histname, hist);

      if(!hist){
        std::cerr << "WARNING in GetNloCurve: input histogram '" << histname << "' could not been opened! Returning dummy!" << endl;
        hist = new TH1();
        return hist;
      }
      
      TH1D* rethist = (TH1D*)hist->Clone();
      TH1D* weight = (TH1D*)file->Get(TString("total_LeptonsPt_").Append(generator));
      
      Double_t wgt = 1.;
      if(!weight){
        std::cerr << "WARNING in GetNloCurve: histogram to extract original number of events could not be opened! No weighting applied!" << endl;
      } else{
	Double_t nevents = weight->GetEntries();
	//
        Double_t crosssection = 169.9;
        Double_t binw = hist->GetBinWidth(1);
        wgt = crosssection/nevents/binw;
      }
      rethist->Scale(wgt);
      return rethist;
    }

    std::cerr << "WARNING in GetNloCurve: input file could not been opened! Returning dummy!" << endl;
    hist = new TH1D();
    return hist;
}

// get new legend
TLegend* Plotter::getNewLegend() {
  TLegend *leg = new TLegend();
  leg->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.25);
  leg->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.15);
  leg->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength());
  leg->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextAlign(12);
  return leg;
}

#endif
