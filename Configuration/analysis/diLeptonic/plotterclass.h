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

// DAVID
#include "DilepSVDFunctions.h"
#include "DilepSVDFunctions.C"

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
  // DAVID
  void UnfoldingOptions(bool doSVD);
  void SetOutpath(TString path);
 private:
  TString name;
  int bins, datafiles;
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
  double InclusiveXsectionSysErrorBySyst[4][20];
  double DiffXSec[4][10];//the differential X-section per channel by bin [channel][bin]
  double DiffXSecStatError[4][10];//the differential X-section Error per channel by bin [channel][bin]
  double DiffXSecSysError[4][10];//the differential X-section Error per channel by bin [channel][bin]
  double DiffXSecSysErrorBySyst[4][10][20];//the differential X-section Error per channel by bin [channel][bin][systematic]
  double DiffXSecTotalError[4][10];//the differential X-section Error per channel by bin [channel][bin]
  double VisXsection[4][10];//needed for bin-by-bin corrections to combination [channel][bin]
  double VisXsectionError[4][10];//needed for bin-by-bin corrections to combination [channel][bin]
  double GenDiffXSec[4][10];//the differential X-section per channel by bin [channel][bin]
  double GenDiffXSecError[4][10];//the differential X-section Error per channel by bin [channel][bin]
  double TotalVisXSection[4];
  
  // DAVID
  bool doUnfolding; 
  TString outpath;
};


// DAVID
void Plotter::UnfoldingOptions(bool doSVD)
{
  doUnfolding = doSVD;
}


// DAVID
void Plotter::SetOutpath(TString path)
{
  outpath = path;
}



void Plotter::DYScaleFactor(){
  TH1::AddDirectory(kFALSE);
  ifstream FileList("FileLists/HistoFileList_Nominal_combined.txt");
  TString filename;
  
  double NoutEEDYMC=0, NinEEDYMC=0, NoutMuMuDYMC=0, NinMuMuDYMC=0;//Number of events in/out of z-veto region for the DY MC
  double NinEE=0, NinMuMu=0, NinEMu=0;//Number of events in z-veto region for data
  double NinEEloose=0, NinMuMuloose=0;//Number of data events in Z-Veto region with MET cut
  double NinEEMC=0, NinMuMuMC=0;//All other MC events

  while(!FileList.eof()){
    FileList>>filename;
    if(filename!=""){
      TFile *ftemp = TFile::Open(filename);
      if(filename.Contains("ee")){
	if(filename.Contains("run")){
	  TH1D *htemp = (TH1D*)ftemp->Get("Zh1"); NinEE+=htemp->Integral();
	  TH1D *htemp1 = (TH1D*)ftemp->Get("Looseh1"); NinEEloose+=htemp1->Integral();	  
	}
	else if(filename.Contains("dy")){
	  if(filename.Contains("50inf")){
	    TH1D *htemp = (TH1D*)ftemp->Get("Zh1"); NinEEDYMC+=htemp->Integral();
	    TH1D *htemp1 = (TH1D*)ftemp->Get("TTh1"); NoutEEDYMC+=htemp1->Integral();
	  }
	  else{TH1D *htemp = (TH1D*)ftemp->Get("TTh1"); NoutEEDYMC+=htemp->Integral();}
	}	
	else{
	  TH1D *htemp = (TH1D*)ftemp->Get("Zh1"); NinEEMC+=htemp->Integral();
	}
      }
      
      if(filename.Contains("emu")){
	if(filename.Contains("run")){TH1D *htemp = (TH1D*)ftemp->Get("Zh1"); NinEMu+=htemp->Integral();}
      }
	
      if(filename.Contains("mumu")){
	if(filename.Contains("run")){
	  TH1D *htemp = (TH1D*)ftemp->Get("Zh1"); NinMuMu+=htemp->Integral();
	  TH1D *htemp1 = (TH1D*)ftemp->Get("Looseh1"); NinMuMuloose+=htemp1->Integral();
	}
	else if(filename.Contains("dy")){
	  if(filename.Contains("50inf")){
	    TH1D *htemp = (TH1D*)ftemp->Get("Zh1"); NinMuMuDYMC+=htemp->Integral();
	    TH1D *htemp1 = (TH1D*)ftemp->Get("TTh1"); NoutMuMuDYMC+=htemp1->Integral();}
	  else{TH1D *htemp = (TH1D*)ftemp->Get("TTh1"); NoutMuMuDYMC+=htemp->Integral();}
	}	
	else{
	  TH1D *htemp = (TH1D*)ftemp->Get("Zh1"); NinMuMuMC+=htemp->Integral();
	}
      }      
      delete ftemp;
    }
  }
  double NoutMCEE = (NoutEEDYMC/NinEEDYMC)*(NinEE - 0.5*NinEMu*sqrt(NinEEloose/NinMuMuloose));
  double NoutMCMuMu = (NoutMuMuDYMC/NinMuMuDYMC)*(NinMuMu - 0.5*NinEMu*sqrt(NinMuMuloose/NinEEloose));
  
  double DYSFEE = NoutMCEE/NoutEEDYMC;
  double DYSFMuMu = NoutMCMuMu/NoutMuMuDYMC;

  //cout<<"DYSFEE: "<<DYSFEE<<endl;
  //cout<<"DYSFMuMu: "<<DYSFMuMu<<endl;

  DYScale[0]=DYSFEE;
  DYScale[1]=DYSFMuMu;
  DYScale[2]=1.;
  DYScale[3]=(DYSFEE+DYSFMuMu)/2;//not correct, but close, fix later
}

void Plotter::InclFlatSystematics(int syst_number){
  
  //trigger uncertainties

  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .025;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .015;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .02;}//emu  
  if (channelType==3){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = 
      1/(sqrt((1/(InclusiveXsectionSysErrorBySyst[0][syst_number]*InclusiveXsectionSysErrorBySyst[0][syst_number]) + 
  	       1/(InclusiveXsectionSysErrorBySyst[1][syst_number]*InclusiveXsectionSysErrorBySyst[1][syst_number]) +
  	       1/(InclusiveXsectionSysErrorBySyst[2][syst_number]*InclusiveXsectionSysErrorBySyst[2][syst_number]))));}//combined  

  syst_number++;

  //Lepton selection

  InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .04;//all 
  syst_number++;

  //B-tagging (for now)
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .06;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .06;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .06;}//emu  
  if (channelType==3){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .06;}//combined  
  syst_number++;

  //KinFit 
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .02;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .02;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .017;}//emu  
  if (channelType==3){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .017;}//combined 
  syst_number++;

  //Hadronization (for now)
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .049;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .043;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .054;}//emu  
  if (channelType==3){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = 
      1/(sqrt((1/(InclusiveXsectionSysErrorBySyst[0][syst_number]*InclusiveXsectionSysErrorBySyst[0][syst_number]) + 
  	       1/(InclusiveXsectionSysErrorBySyst[1][syst_number]*InclusiveXsectionSysErrorBySyst[1][syst_number]) +
  	       1/(InclusiveXsectionSysErrorBySyst[2][syst_number]*InclusiveXsectionSysErrorBySyst[2][syst_number]))));}//combined  
  syst_number++;

  //Branching Ratio
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .015;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .015;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .015;}//emu  
  if (channelType==3){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .015;}//combined  
  syst_number++;

  //Luminosity
  if (channelType==0){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .045;}//ee 
  if (channelType==1){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .045;}//mumu  
  if (channelType==2){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .045;}//emu  
  if (channelType==3){InclusiveXsectionSysErrorBySyst[channelType][syst_number] = .045;}//combined  
  syst_number++;

}
void Plotter::DiffFlatSystematics(int syst_number, int nbins){
  
  for(int bin = 0; bin<nbins; bin++){
    int syst = syst_number;
    //trigger uncertainties
    
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .025;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .015;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .02;}//emu  
    if (channelType==3){DiffXSecSysErrorBySyst[channelType][bin][syst] = 
	1/(sqrt((1/(DiffXSecSysErrorBySyst[0][bin][syst]*DiffXSecSysErrorBySyst[0][bin][syst]) + 
		 1/(DiffXSecSysErrorBySyst[1][bin][syst]*DiffXSecSysErrorBySyst[1][bin][syst]) +
		 1/(DiffXSecSysErrorBySyst[2][bin][syst]*DiffXSecSysErrorBySyst[2][bin][syst]))));}//combined  
    syst++;
    
    //Lepton selection
    
    DiffXSecSysErrorBySyst[channelType][bin][syst] = .02;//all (different from inclusive?) 
    syst++;
    
    //B-tagging (for now)
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .017;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .017;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .017;}//emu  
    if (channelType==3){DiffXSecSysErrorBySyst[channelType][bin][syst] = .017;}
	//	1/(sqrt((1/(DiffXSecSysErrorBySyst[0][bin][syst]*DiffXSecSysErrorBySyst[0][bin][syst]) + 
	//	 1/(DiffXSecSysErrorBySyst[1][bin][syst]*DiffXSecSysErrorBySyst[1][bin][syst]) +
	//	 1/(DiffXSecSysErrorBySyst[2][bin][syst]*DiffXSecSysErrorBySyst[2][bin][syst]))));}//combined  
    syst++;
    
    //KinFit 
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .005;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .005;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .005;}//emu  
    if (channelType==3){DiffXSecSysErrorBySyst[channelType][bin][syst] = .005;}
    //	1/(sqrt((1/(DiffXSecSysErrorBySyst[0][bin][syst]*DiffXSecSysErrorBySyst[0][bin][syst]) + 
    //		 1/(DiffXSecSysErrorBySyst[1][bin][syst]*DiffXSecSysErrorBySyst[1][bin][syst]) +
    //		 1/(DiffXSecSysErrorBySyst[2][bin][syst]*DiffXSecSysErrorBySyst[2][bin][syst]))));}//combined  
    syst++;
    
    //Hadronization (for now)
    if (channelType==0){DiffXSecSysErrorBySyst[channelType][bin][syst] = .006;}//ee 
    if (channelType==1){DiffXSecSysErrorBySyst[channelType][bin][syst] = .01;}//mumu  
    if (channelType==2){DiffXSecSysErrorBySyst[channelType][bin][syst] = .003;}//emu  
    if (channelType==3){DiffXSecSysErrorBySyst[channelType][bin][syst] = 
	1/(sqrt((1/(DiffXSecSysErrorBySyst[0][bin][syst]*DiffXSecSysErrorBySyst[0][bin][syst]) + 
		 1/(DiffXSecSysErrorBySyst[1][bin][syst]*DiffXSecSysErrorBySyst[1][bin][syst]) +
		 1/(DiffXSecSysErrorBySyst[2][bin][syst]*DiffXSecSysErrorBySyst[2][bin][syst]))));}//combined  
    syst++;
    
  }
}

void Plotter::CalcInclSystematics(TString Systematic, int syst_number){
  setSystDataSet(Systematic);
  fillSystHisto();

  TH1D* stacksum = (TH1D*)hists[datafiles].Clone();
  TH1D* stacksumUp = (TH1D*)systhistsUp[datafiles].Clone();
  TH1D* stacksumDown = (TH1D*)systhistsDown[datafiles].Clone();

  for(unsigned int i=datafiles+1; i<hists.size() ; i++){ // prepare histos and leg
    TH1 *htemp = (TH1D*)hists[i].Clone();
    if((legends[i] == DYEntry) && channelType!=2 ){
      htemp->Scale(DYScale[channelType]);
    }
    stacksum->Add(htemp);
  }
  for(unsigned int i=datafiles+1; i<systhistsUp.size() ; i++){ // prepare histos and leg
    TH1 *htemp = (TH1D*)systhistsUp[i].Clone();
    if((legends[i] == DYEntry) && channelType!=2 ){
      htemp->Scale(DYScale[channelType]);
    }
    if((legends[i] == DYEntry) && Systematic == "DY_"){
      htemp->Scale(1.5);
    }
    if((legends[i] != DYEntry)&& (legends[i] != "t#bar{t} signal") && Systematic == "BG_"){
      htemp->Scale(1.3);
    }
    stacksumUp->Add(htemp);
  }
  for(unsigned int i=datafiles+1; i<systhistsDown.size() ; i++){ // prepare histos and leg
    TH1 *htemp = (TH1D*)systhistsDown[i].Clone();
    if((legends[i] == DYEntry) && channelType!=2 ){
      htemp->Scale(DYScale[channelType]);
    }
    if((legends[i] == DYEntry) && Systematic == "DY_"){
      htemp->Scale(0.5);
    }
    if((legends[i] != DYEntry)&& (legends[i] != "t#bar{t} signal") && Systematic == "BG_"){
      htemp->Scale(0.7);
    }
    stacksumDown->Add(htemp);
  }
  double Sys_Error_Up, Sys_Error_Down, Sys_Error;//, Sum_Errors;
  double scale = 1.;

  TH1D* h_sys  = (TH1D*) stacksumUp->Clone();   h_sys->Reset();
  TH1D* h_sys2 = (TH1D*) stacksumDown->Clone(); h_sys2->Reset();
  
  Sys_Error_Up   = abs(stacksum->Integral() - stacksumUp->Integral())/stacksum->Integral();
  Sys_Error_Down = abs(stacksum->Integral() - stacksumDown->Integral())/stacksum->Integral();
  Sys_Error  = (Sys_Error_Up+Sys_Error_Down)/(2.*scale);
  //  Sum_Errors += Sys_Error;

  InclusiveXsectionSysErrorBySyst[channelType][syst_number] = Sys_Error;

}

void Plotter::CalcDiffSystematics(TString Systematic, int syst_number){
 
  double Xbins[XAxisbins.size()];
  for(unsigned int i = 0; i<XAxisbins.size();i++){Xbins[i]=XAxisbins[i];}
  setSystDataSet(Systematic);  
  fillSystHisto(); 
  TH1D* stacksum = (TH1D*)hists[datafiles].Rebin(bins,"stack",Xbins);  
  TH1D* stacksumUp = (TH1D*)systhistsUp[datafiles].Rebin(bins,"stackup",Xbins); 
  TH1D* stacksumDown = (TH1D*)systhistsDown[datafiles].Rebin(bins,"stackdown",Xbins); 

  TH2 *genReco2d=NULL;
  TH2 *genReco2dUp=NULL;
  TH2 *genReco2dDown=NULL;

  TH1 *GenPlot = NULL;

  TString newname = name;
  if(name.Contains("Hyp")){//Histogram naming convention has to be smarter
    newname.ReplaceAll("Hyp",3,"",0);
  } 
  //DYScale Factor...
  for(unsigned int i=datafiles+1; i<hists.size() ; i++){ // prepare histos and leg
    TFile *ftemp = TFile::Open(dataset[i]);
    if(genReco2d==NULL){
      genReco2d = (TH2*)ftemp->Get("GenReco"+newname)->Clone();
      GenPlot = (TH1*)ftemp->Get("VisGen"+newname)->Clone();
    } else{
      genReco2d->Add((TH2*)ftemp->Get("GenReco"+newname)->Clone());
      GenPlot->Add((TH1*)ftemp->Get("VisGen"+newname)->Clone());
    }
    TH1 *htemp = (TH1D*)hists[i].Rebin(bins,"htemp",Xbins);
    if((legends[i] == DYEntry) && channelType!=2 ){
      htemp->Scale(DYScale[channelType]);
    }
    stacksum->Add(htemp);
    delete ftemp;
  } 
  for(unsigned int i=datafiles+1; i<systhistsUp.size() ; i++){ // prepare histos and leg
    TFile *ftempUp = TFile::Open(datasetUp[i]);
    if(genReco2dUp==NULL){
      genReco2dUp = (TH2*)ftempUp->Get("GenReco"+newname)->Clone();
    } else{
      genReco2dUp->Add((TH2*)ftempUp->Get("GenReco"+newname)->Clone());
    }
    TH1 *htemp = (TH1D*)systhistsUp[i].Rebin(bins,"htempup",Xbins);
    if((legends[i] == DYEntry) && channelType!=2 ){
      htemp->Scale(DYScale[channelType]);
    }
    stacksumUp->Add(htemp);
    if((legends[i] == DYEntry) && Systematic == "DY_"){
      htemp->Scale(1.5);
    }
    if((legends[i] != DYEntry)&& (legends[i] != "t#bar{t} signal") && Systematic == "BG_"){
      htemp->Scale(1.3);
    }

    delete ftempUp;
  } 
  for(unsigned int i=datafiles+1; i<systhistsDown.size() ; i++){ // prepare histos and leg
    TFile *ftempDown = TFile::Open(datasetDown[i]);
    if(genReco2dDown==NULL){
      genReco2dDown = (TH2*)ftempDown->Get("GenReco"+newname)->Clone();
    } else{
      genReco2dDown->Add((TH2*)ftempDown->Get("GenReco"+newname)->Clone());
    }
    TH1 *htemp = (TH1D*)systhistsDown[i].Rebin(bins,"htempdown",Xbins);
    if((legends[i] == DYEntry) && channelType!=2 ){
      htemp->Scale(DYScale[channelType]);
    }
    if((legends[i] == DYEntry) && Systematic == "DY_"){
      htemp->Scale(0.5);
    }
    if((legends[i] != DYEntry)&& (legends[i] != "t#bar{t} signal") && Systematic == "BG_"){
      htemp->Scale(0.7);
    }
    stacksumDown->Add(htemp);
    delete ftempDown;
  }
   
  double Sys_Error_Up, Sys_Error_Down, Sys_Error;//, Sum_Errors;
  double scale = 1.;

  for(Int_t bin = 0; bin <= stacksum->GetNbinsX(); ++bin) {
    if( stacksum->GetBinContent(bin+1) == 0 )  continue;
    Sys_Error_Up   = abs(stacksum->GetBinContent(bin+1) - stacksumUp->GetBinContent(bin+1))/stacksum->GetBinContent(bin+1);
    Sys_Error_Down = abs(stacksum->GetBinContent(bin+1) - stacksumDown->GetBinContent(bin+1))/stacksum->GetBinContent(bin+1);
    Sys_Error  = (Sys_Error_Up+Sys_Error_Down)/(2.*scale);
    //    Sum_Errors += Sys_Error;
    DiffXSecSysErrorBySyst[channelType][bin][syst_number] = Sys_Error;//the differential X-section Error per channel by bin [channel][bin][systematic]
  } 
   
  // DAVID. Guckst du hier!
  bool saveUnfStat = doUnfolding;
  doUnfolding = false;
  if ( doUnfolding == true ) {
  
  		// SVD Helper Class
		DilepSVDFunctions mySVDFunctions; 
		mySVDFunctions.SetOutputPath(outpath);  
		
		// Variables for the needed histograms
		TH1D* theDataHist = NULL;
		TH1D* theBgrHist = NULL;
		TH1D* theBgrHistUp = NULL;
		TH1D* theBgrHistDown = NULL;
		TH1D* theRecHist = NULL;
		TH1D* theRecHistUp = NULL;
		TH1D* theRecHistDown = NULL;
		TH1D* theGenHist = NULL;
		TH1D* theGenHistUp = NULL;
		TH1D* theGenHistDown = NULL; 
		TH2D* theRespHist = NULL;
		TH2D* theRespHistUp = NULL;
		TH2D* theRespHistDown = NULL;   
		
		// DAVID:
		// Data, Signal and Background
		// can be obtained from vectors that Tyler fills.
		// These are the vectors
		// "hists", "systhistsUp" amd "systhistsDown"
		// Notice, that the DY Background will be scaled with
		// the DYScale.
		for ( size_t i = 0; i < hists.size() ; i++ ) {
			if ( legends[i] == "data" ) {
				
				// Get Data Hist
				if ( theDataHist == NULL ) {
					theDataHist = (TH1D*) (hists[i]).Clone("theDataHist");
				} else {
					theDataHist->Add(&(hists[i]));
				}
			} else if ( legends[i] == "t#bar{t} signal") {
				
				// Get Signal Hist
				if ( theRecHist == NULL ) {
					theRecHist = (TH1D*) (hists[i]).Clone("theRecHist");
				} else {
					theRecHist->Add(&(hists[i]));
				}
				if ( theRecHistUp == NULL ) {
					theRecHistUp = (TH1D*) (systhistsUp[i]).Clone("theRecHistUp");
				} else {
					theRecHistUp->Add(&(hists[i]));
				}
				if ( theRecHistDown == NULL ) {
					theRecHistDown = (TH1D*) (systhistsDown[i]).Clone("theRecHistDown");
				} else {
					theRecHistDown->Add(&(hists[i]));
				}
			} else {
				
				// Calculate DYScale fist
				double theDYScale = 1.;
				if ( (legends[i] == DYEntry) && (channelType != 2 ) ) {
				    theDYScale = DYScale[channelType];
				}
				
				// Get Background HIst, thereby applying DY Scale
				if ( theBgrHist == NULL ) {
					theBgrHist = (TH1D*) (hists[i]).Clone("theBgrHist");
					theBgrHist->Scale(theDYScale);
				} else {
					theBgrHist->Add(&(hists[i]), theDYScale);
				}
				if ( theBgrHistUp == NULL ) {
					theBgrHistUp = (TH1D*) (systhistsUp[i]).Clone("theBgrHistUp");
				} else {
					theBgrHistUp->Add(&(hists[i]));
				}
				if ( theBgrHistDown == NULL ) {
					theBgrHistDown = (TH1D*) (systhistsDown[i]).Clone("theBgrHistDown");
				} else {
					theBgrHistDown->Add(&(hists[i]));
				} 
			}
		}
  
		
		 
	 
		// DAVID
		// Response Matrix and visible Gen Dist
		// have to be obtained from the files directly
		for ( size_t i = 0; i < hists.size() ; i++ ) {
		    if(legends[i] == "t#bar{t} signal"){
		    	
		    	// Nominal Sample
		    	TFile* ftemp = TFile::Open(dataset[i]);
		    	TH2D* resptemp = (TH2D*) ftemp->Get("GenReco"+newname);
		    	TH1D* gentemp = (TH1D*) ftemp->Get("VisGen"+newname); 
				if ( theRespHist == NULL ) {
					theRespHist = (TH2D*) (resptemp)->Clone("theRespHist");
				} else {
					theRespHist->Add(resptemp);
				}
				if ( theGenHist == NULL ) {
					theGenHist = (TH1D*) (gentemp)->Clone("theGenHist");
				} else {
					theGenHist->Add(gentemp);
				}
				delete ftemp;
				
		    	// Shift Up
		    	TFile* ftempUp = TFile::Open(datasetUp[i]);
		    	TH2D* resptempUp = (TH2D*) ftempUp->Get("GenReco"+newname);
				if ( theRespHistUp == NULL ) {
					theRespHistUp = (TH2D*) (resptempUp)->Clone("theRespHistUp");
				} else {
					theRespHistUp->Add(resptempUp);
				}
				if ( theGenHistUp == NULL ) {
					theGenHistUp = (TH1D*) (gentemp)->Clone("theGenHistUp");
				} else {
					theGenHistUp->Add(gentemp);
				} 
				delete ftempUp;
				
		    	// Shift Down
		    	TFile* ftempDown = TFile::Open(datasetDown[i]);
		    	TH2D* resptempDown = (TH2D*) ftempDown->Get("GenReco"+newname);
				if ( theRespHistDown == NULL ) {
					theRespHistDown = (TH2D*) (resptempDown)->Clone("theRespHistDown");
				} else {
					theRespHistDown->Add(resptempDown);
				}
				if ( theGenHistDown == NULL ) {
					theGenHistDown = (TH1D*) (gentemp)->Clone("theGenHistDown");
				} else {
					theGenHistDown->Add(gentemp);
				} 
				delete ftempDown;
		    	
		    }
		}
//// DAVID
//// Make a real crude reweighting of the Resp and Gen Hists
//double lumiResp = 	theRespHist->Integral();
//double lumiRespUp = 	theRespHistUp->Integral();
//double lumiRespDown = 	theRespHistDown->Integral();
//double lumiRec =     theRecHist->Integral();
//double lumiRecUp =     theRecHistUp->Integral();
//double lumiRecDown =     theRecHistDown->Integral();
//double lumiGen =     theGenHist->Integral();
//double lumiGenUp =     theGenHistUp->Integral();
//double lumiGenDown =     theGenHistDown->Integral(); 
//double extra_factor = 1.;
//if ( lumiRespDown < 0.7*lumiResp ) {
//	extra_factor = (2.*lumiResp) / (lumiRespDown+lumiRespUp);
//} 
//double scaleResp = lumiRec / lumiResp;
//double scaleGen = scaleResp;
//theRespHist->Scale(scaleResp);
//theRespHistUp->Scale(scaleResp*extra_factor);
//theRespHistDown->Scale(scaleResp*extra_factor);
//theGenHist->Scale(scaleGen);
//theGenHistUp->Scale(scaleGen*extra_factor);
//theGenHistDown->Scale(scaleGen*extra_factor);
//cout << "*******************************************************************************" << endl;
//cout << "Hey! " << endl;
//cout << "A real crude reweighting is being done here ... " << endl;
//cout << "Scale Factor applied on resp Matrix: " << scaleResp << endl;
//cout << "Scale Factor applied on gen Dist: " << scaleGen << endl;
//cout << "     Integral Resp = " << lumiResp << endl;
//cout << "     Integral RespUp = " << lumiRespUp << endl;
//cout << "     Integral RespDown = " << lumiRespDown << endl;
//cout << "     Integral Rec = " << lumiRec << endl;
//cout << "     Integral RecUp = " << lumiRecUp << endl;
//cout << "     Integral RecDown = " << lumiRecDown << endl;
//cout << "     Integral Gen = " << lumiGen << endl;
//cout << "     Integral GenUp = " << lumiGenUp << endl;
//cout << "     Integral GenDown = " << lumiGenDown << endl;  
//lumiResp = 	theRespHist->Integral();
//lumiRespUp = 	theRespHistUp->Integral();
//lumiRespDown = 	theRespHistDown->Integral();
//lumiRec =     theRecHist->Integral();
//lumiRecUp =     theRecHistUp->Integral();
//lumiRecDown =     theRecHistDown->Integral();
//lumiGen =     theGenHist->Integral();
//lumiGenUp =     theGenHistUp->Integral();
//lumiGenDown =     theGenHistDown->Integral();
//cout << "After reweighting" << endl;
//cout << "     Integral Resp = " << lumiResp << endl;
//cout << "     Integral RespUp = " << lumiRespUp << endl;
//cout << "     Integral RespDown = " << lumiRespDown << endl;
//cout << "     Integral Rec = " << lumiRec << endl;
//cout << "     Integral RecUp = " << lumiRecUp << endl;
//cout << "     Integral RecDown = " << lumiRecDown << endl;
//cout << "     Integral Gen = " << lumiGen << endl;
//cout << "     Integral GenUp = " << lumiGenUp << endl;
//cout << "     Integral GenDown = " << lumiGenDown << endl; 
//cout << "*******************************************************************************" << endl; 
		    	 
		// Get the binning 
		double* theBins = Xbins;
		int numberBins = bins;
		
		
		// Names and Labels
		TString channelLabelStr(channelLabel[channelType]);
        TString theChannelName = channelLabelStr; 		
        if ( channelLabelStr.Contains("#mu#mu")  ) theChannelName = "mumu";
        if ( channelLabelStr.Contains("e#mu")    ) theChannelName = "emu";
        if ( channelLabelStr.Contains("ee")      ) theChannelName = "ee";
        if ( channelLabelStr.Contains("Dilepton Combined")    ) theChannelName = "combined";
        TString theParticleName = "";
		if ( name.Contains("Lepton") ) theParticleName = "Leptons";
		if ( name.Contains("LLBar")   ) theParticleName = "LepPair";
		if ( name.Contains("Top")     ) theParticleName = "TopQuark";
		if ( name.Contains("TTBar")   ) theParticleName = "TtBar";
		TString theQuantityName = "";
		if ( name.Contains("pT")      ) theQuantityName = "Pt";
		if ( name.Contains("Eta")     ) theQuantityName = "Eta";
		if ( name.Contains("Rapidity")) theQuantityName = "Rapidity";
		if ( name.Contains("Mass")    ) theQuantityName = "Mass";
		TString theSpecialPostfix = "";
		TString theSystematicName = Systematic;
		
		
 
        // UNFOLDING OF SYSTEMATICS
        // Retrieve histograms with the unfolded quantities.
        // Note: The unfolded histograms have additional side bins!
        // Keep this in mind when accessing bin content via indices 
		TH1D* symmSysErrors = NULL; 
		mySVDFunctions.SVD_DoUnfoldSys(
			theDataHist,
        	theBgrHist, theBgrHistUp, theBgrHistDown, 
        	theGenHist, theGenHistUp, theGenHistDown, 
        	theRecHist, theRecHistUp, theRecHistDown, 
        	theRespHist, theRespHistUp, theRespHistDown, 
        	theBins, numberBins,
            symmSysErrors,  
            theChannelName, theParticleName, theQuantityName, theSpecialPostfix, theSystematicName
        ); 
  	

		
  	    // Save the shifts in Tyler's triple-matrix ...
        for(Int_t bin = 0; bin <= stacksum->GetNbinsX(); ++bin) {
        	Sys_Error = symmSysErrors->GetBinContent(bin+2); // Keep in mind the extra layer of OF bins
        	
        	// Save it
	        DiffXSecSysErrorBySyst[channelType][bin][syst_number] = Sys_Error;//the differential X-section Error per channel by bin [channel][bin][systematic]
	    } 
  }
  
  // Old pre SVD code
  if ( doUnfolding == false) {
  		for(Int_t bin = 0; bin <= stacksum->GetNbinsX(); ++bin) {
	    if( stacksum->GetBinContent(bin+1) == 0 )  continue;
	    Sys_Error_Up   = abs(stacksum->GetBinContent(bin+1) - stacksumUp->GetBinContent(bin+1))/stacksum->GetBinContent(bin+1);
	    Sys_Error_Down = abs(stacksum->GetBinContent(bin+1) - stacksumDown->GetBinContent(bin+1))/stacksum->GetBinContent(bin+1);
	    Sys_Error  = (Sys_Error_Up+Sys_Error_Down)/(2.*scale);
	    //    Sum_Errors += Sys_Error;
	    DiffXSecSysErrorBySyst[channelType][bin][syst_number] = Sys_Error;//the differential X-section Error per channel by bin [channel][bin][systematic]
	} 
  }
  doUnfolding = saveUnfStat;
}

Plotter::Plotter()
{
  name="defaultName";
  rangemin=0;
  rangemax=3;
  YAxis="N_{events}";
  initialized=false;
  datafiles = 0;
  
  // DAVID  
  outpath = "";

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

  lumi=4966;
  
  DYEntry = "Z^{0} / #gamma* #rightarrow ee/#mu#mu";

  if(channel=="ee" || channel=="emu" ||channel=="mumu"){  
    ifstream FileList("FileLists/HistoFileList_Nominal_"+channel+".txt");
    TString filename;
    datafiles=0;

    dataset.clear();
    legends.clear();
    colors.clear();
  
    while(!FileList.eof()){
      FileList>>filename;

      if(filename!=""){
	dataset.push_back(filename);
	if(filename.Contains("run")){legends.push_back("data"); colors.push_back(kBlack);datafiles++;}
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

  if(channel=="combined"){
    datafiles=0;
    dataset.clear();
    legends.clear();
    colors.clear();
    ifstream FileList("FileLists/HistoFileList_Nominal_combined.txt");
    TString filename;

    while(!FileList.eof()){
      FileList>>filename;

      if(filename!=""){
	dataset.push_back(filename);
	
	if(filename.Contains("run")){legends.push_back("data"); colors.push_back(kBlack);datafiles++;}
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
  lumi=4966;
  if(channel=="ee" || channel=="emu" || channel=="mumu"){  
    TString HistoFileUp,HistoFileDown; 
    if(systematic=="DY_" || systematic=="BG_"){
      HistoFileUp = "FileLists/HistoFileList_Nominal_"+channel+".txt";
      HistoFileDown = "FileLists/HistoFileList_Nominal_"+channel+".txt";
    }else{
      HistoFileUp = "FileLists/HistoFileList_"+systematic+"UP_"+channel+".txt";
      HistoFileDown = "FileLists/HistoFileList_"+systematic+"DOWN_"+channel+".txt";
    }
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
    TString HistoFileUp,HistoFileDown; 
    if(systematic=="DY_" || systematic=="BG_"){
      HistoFileUp = "FileLists/HistoFileList_Nominal_"+channel+".txt";
      HistoFileDown = "FileLists/HistoFileList_Nominal_"+channel+".txt";
    }else{
      HistoFileUp= "FileLists/HistoFileList_"+systematic+"UP_"+channel+".txt";
      HistoFileDown = "FileLists/HistoFileList_"+systematic+"DOWN_"+channel+".txt";
    }
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
      TH1D *hist = (TH1D*)ftemp->Get(name)->Clone();
      if(name.Contains("Lepton")){
      	TString stemp = name;
	    stemp.ReplaceAll("Lepton",6,"AntiLepton",10);
	    TH1D *hist2 = (TH1D*)ftemp->Get(stemp)->Clone();     
      	hist->Add(hist2);
      }
      if(name.Contains("BJet")){
      	TString stemp = name;
	    stemp.ReplaceAll("BJet",4,"AntiBJet",8);
	    TH1D *hist2 = (TH1D*)ftemp->Get(stemp)->Clone();     
      	hist->Add(hist2);
      }
      if(name.Contains("Top")){
      	TString stemp = name;
	    stemp.ReplaceAll("Top",3,"AntiTop",7);
	    TH1D *hist2 = (TH1D*)ftemp->Get(stemp)->Clone();     
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
    hists.clear();
    systhistsUp.clear();
    systhistsDown.clear();
    
    // Fill nominal sample
    for(unsigned int i=0; i<dataset.size(); i++){
      TFile *ftemp = TFile::Open(dataset[i]);
      TH1D *hist = (TH1D*)ftemp->Get(name)->Clone();
      if(name.Contains("Lepton")){
      	TString stemp = name;
	    stemp.ReplaceAll("Lepton",6,"AntiLepton",10);
	    TH1D *hist2 = (TH1D*)ftemp->Get(stemp)->Clone();     
      	hist->Add(hist2);
      }
      if(name.Contains("BJet")){
      	TString stemp = name;
	    stemp.ReplaceAll("BJet",4,"AntiBJet",8);
	    TH1D *hist2 = (TH1D*)ftemp->Get(stemp)->Clone();     
      	hist->Add(hist2);
      }
      if(name.Contains("Top")){
      	TString stemp = name;
	    stemp.ReplaceAll("Top",3,"AntiTop",7);
	    TH1D *hist2 = (TH1D*)ftemp->Get(stemp)->Clone();     
      	hist->Add(hist2);
      }
      
      setHHStyle(*gStyle);
      //gStyle->SetErrorX(0);
      hists.push_back(*hist);
      //ftemp->Close("R");
      //delete hist;
      delete ftemp;
    }
    
    
    // Fill up-shifted sample
    for(unsigned int i=0; i<datasetUp.size(); i++){
      TFile *ftemp = TFile::Open(datasetUp[i]);
      TH1D *hist = (TH1D*)ftemp->Get(name)->Clone();     
      if(name.Contains("BJet")){
      	TString stemp = name;
	    stemp.ReplaceAll("BJet",4,"AntiBJet",8);
	    TH1D *hist2 = (TH1D*)ftemp->Get(stemp)->Clone();     
      	hist->Add(hist2);
      }
      if(name.Contains("Lepton")){
      	TString stemp = name;
	    stemp.ReplaceAll("Lepton",6,"AntiLepton",10);
	    TH1D *hist2 = (TH1D*)ftemp->Get(stemp)->Clone();     
      	hist->Add(hist2);
      }
      if(name.Contains("Top")){
      	TString stemp = name;
	    stemp.ReplaceAll("Top",3,"AntiTop",7);
	    TH1D *hist2 = (TH1D*)ftemp->Get(stemp)->Clone();     
      	hist->Add(hist2);
      }
      
      setHHStyle(*gStyle);
      //gStyle->SetErrorX(0);
      systhistsUp.push_back(*hist);
      delete ftemp;
    }
    
    // Fill down-shifted sample
    for(unsigned int i=0; i<datasetDown.size(); i++){
      TFile *ftemp = TFile::Open(datasetDown[i]);
      TH1D *hist = (TH1D*)ftemp->Get(name)->Clone();     
      if(name.Contains("BJet")){
      	TString stemp = name;
	    stemp.ReplaceAll("BJet",4,"AntiBJet",8);
	    TH1D *hist2 = (TH1D*)ftemp->Get(stemp)->Clone();     
      	hist->Add(hist2);
      }
      if(name.Contains("Lepton")){
      	TString stemp = name;
	    stemp.ReplaceAll("Lepton",6,"AntiLepton",10);
	    TH1D *hist2 = (TH1D*)ftemp->Get(stemp)->Clone();     
       	hist->Add(hist2);
      }
      if(name.Contains("Top")){
      	TString stemp = name;
	    stemp.ReplaceAll("Top",3,"AntiTop",7);
	    TH1D *hist2 = (TH1D*)ftemp->Get(stemp)->Clone();     
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
  //  if(legends[i]!=legends[i+1] && i!=(hists.size()-1)){
   //   drawhists[i]->SetLineColor(1);
   // }
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
    
  
  TFile *f0 = new TFile("SigBackground.root","UPDATE");

  TList* l = stack->GetHists(); 
  TH1D* stacksum = (TH1D*) l->At(0)->Clone();
 
  TString aaa = "a";
  for (int i = 1; i < l->GetEntries(); ++i) {
    aaa=aaa+"a"; 
    stacksum->Add((TH1D*)l->At(i));
    if(legends[datafiles+i] == "t#bar{t} background") {
      stacksum->Write(name+"_"+channel+aaa+"_Background");
    }
    if(legends[datafiles+i] == "t#bar{t} signal") {
	stacksum->Write(name+"_"+channel+aaa+"_Signal");
    }

  } 
  f0->Close();
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
  
  DrawCMSLabels(true, lumi);
  
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
    hist.GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d#sigma}{d"+XAxis+"}");
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
   //mplotwithsys->Draw("p,SAME,Z");
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
  //CalcInclSystematics("PU_",2);
  //CalcInclSystematics("SCALE",3);
  //CalcInclSystematics("MATCH",4);
  //CalcInclSystematics("MASS",5);
  //CalcInclSystematics("DY_",6);
  //CalcInclSystematics("BG_",7);
  //InclFlatSystematics(8);
  
  double syst_square=0;

  for(int i =0; i<15; i++){
    syst_square += InclusiveXsectionSysErrorBySyst[channelType][i]*InclusiveXsectionSysErrorBySyst[channelType][i];
  }
  InclusiveXsectionSysError[channelType] = sqrt(syst_square);
  //cout<<"&^&^&^&^&^&^^&^&^ InclusiveXsectionSysError[channelType]: "<<InclusiveXsectionSysError[channelType]<<endl;
  //  double BranchingFraction[4]={0.0167, 0.0162, 0.0328, 0.06569};//[ee, mumu, emu, combined] including tau
  double BranchingFraction[4]={0.011556, 0.011067, 0.022618, 0.04524};//[ee, mumu, emu, combined] not including tau
  lumi = 4966;

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
      //      cout<<legends[i]<<" = "<<numhists[i]->Integral()<<endl;
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
      if((legends[i] == DYEntry) && channelType!=2){
	numhists[i]->Scale(DYScale[channelType]);
      }
      //cout<<legends[i]<<" = "<<numhists[i]->Integral()<<endl;
      numbers[3]+=numhists[i]->Integral();
    }        
  }  

  ////////////////////////////Make output for tables
  double tmp_num = 0;
  
  ofstream EventFile;
  string EventFilestring = "Plots/";
  if(channelType==0){EventFilestring.append("ee");}
  else if(channelType==1){EventFilestring.append("mumu");}
  else if(channelType==2){EventFilestring.append("emu");}
  else{EventFilestring.append("combined");}
  EventFilestring.append("/Events.txt");
  EventFile.open(EventFilestring.c_str());
  double bg_num = 0;
  for(unsigned int i=0; i<hists.size() ; i++){ 
    tmp_num+=numhists[i]->Integral();

    if(i==(hists.size()-1)){
      EventFile<<legends[i]<<": "<<tmp_num<<endl;
      bg_num+=tmp_num;
      tmp_num=0;
    }else if(legends[i]!=legends[i+1]){
      EventFile<<legends[i]<<": "<<tmp_num<<endl;
      if(legends[i]!="data")bg_num+=tmp_num;
      tmp_num=0;
    }

  }
  EventFile<<"Total background: "<<bg_num<<endl;
  EventFile.close();

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
    //CalcDiffSystematics("PU_", 2);
    //CalcDiffSystematics("SCALE", 3);
    //CalcDiffSystematics("MATCH", 4);
    //CalcDiffSystematics("MASS", 5);
    //CalcDiffSystematics("DY_", 6);
    //CalcDiffSystematics("BG_", 7);
    //DiffFlatSystematics(8,bins);
    double topxsec = 169.9;
    //double BranchingFraction[4]={0.0167, 0.0162, 0.0328, 0.06569};//[ee, mumu, emu]
    double SignalEvents = 3697693.0;
    double Xbins[XAxisbins.size()];
    for(unsigned int i = 0; i<XAxisbins.size();i++){Xbins[i]=XAxisbins[i];}
    double binCenters[XAxisbinCenters.size()];
    for(unsigned int i = 0; i<XAxisbinCenters.size();i++){binCenters[i]=XAxisbinCenters[i];}
    

    TH1 *RecoPlot = new TH1D;
    TH1 *RecoPlotFineBins = new TH1D;
    TH1 *GenPlot =new TH1D;
    TH1 *GenPlotTheory =new TH1D;
    //double DataSum[nbins]={0};
    //double GenSignalSum[nbins]={0};
    //double BGSum[nbins]={0};
    double DataSum[XAxisbinCenters.size()];
    double GenSignalSum[XAxisbinCenters.size()];
    double BGSum[XAxisbinCenters.size()];
    bool init = false;
    TH1 *varhists[hists.size()];
    TH2 *genReco2d=0; 
    TString newname = name;
    if(name.Contains("Hyp")){//Histogram naming convention has to be smarter
      newname.ReplaceAll("Hyp",3,"",0);
    }
    for (unsigned int i =0; i<hists.size(); i++){
      varhists[i]=hists[i].Rebin(bins,"varhists",Xbins);            
      setStyle(*varhists[i], i);
      if(legends[i] == "t#bar{t} signal"){
	TFile *ftemp = TFile::Open(dataset[i]);
	if(init==false){
	  RecoPlotFineBins =  (TH1D*)ftemp->Get("Reco"+newname)->Clone();
	  genReco2d = (TH2*)ftemp->Get("GenReco"+newname)->Clone();
	  GenPlotTheory=(TH1D*)ftemp->Get("VisGen"+newname)->Clone();
	  if(newname.Contains("Lepton")||newname.Contains("Top")||newname.Contains("BJet")){
	    RecoPlotFineBins->Add((TH1D*)ftemp->Get("RecoAnti"+newname)->Clone());
	    genReco2d->Add((TH2*)ftemp->Get("GenRecoAnti"+newname)->Clone());
	    GenPlotTheory->Add((TH1D*)ftemp->Get("VisGenAnti"+newname)->Clone());
	  }
	  init =true;
	} else {//account for more than one signal histogram
	  RecoPlotFineBins->Add((TH1D*)ftemp->Get("Reco"+newname)->Clone());
	  genReco2d->Add((TH2*)ftemp->Get("GenReco"+newname)->Clone());
	  GenPlotTheory->Add((TH1D*)ftemp->Get("VisGen"+newname)->Clone());
	  if(newname.Contains("Lepton")||newname.Contains("Top")||newname.Contains("BJet")){
	    GenPlotTheory->Add((TH1D*)ftemp->Get("VisGenAnti"+newname)->Clone());
	    genReco2d->Add((TH2*)ftemp->Get("GenRecoAnti"+newname)->Clone());
	    RecoPlotFineBins->Add((TH1D*)ftemp->Get("RecoAnti"+newname)->Clone());
	  }	  
	}
	delete ftemp;
      }           
    }
    GenPlot = GenPlotTheory->Rebin(bins,"genplot",Xbins);	
    RecoPlot = (TH1D*)RecoPlotFineBins->Rebin(bins,"recohists",Xbins);
    THStack * stack=  new THStack("def", "def");
    TLegend * leg =  new TLegend(0.70,0.65,0.95,0.90);
    for(unsigned int i=0; i<hists.size() ; i++){ // prepare histos and leg
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
	  if(legends[i] != legends[i-1]){//check
	    leg->AddEntry(varhists[i], legends[i] ,"pe");
	  }
	}
      }
    }

    ///////////////////////////////////
    //purity and stability plots as taken from CombinedCrossSection... ...
    
    TH1* genHist = (TH1*)GenPlot->Clone();
    TH1* genRecHist = new TH1D("","",bins,Xbins);
    int intbinsX[XAxisbins.size()];
    int intbinsY[XAxisbins.size()];
    // fill the elements of the main diagonal of the 2d hist into binned 1D histogram
    for (unsigned int i=0; i<XAxisbins.size(); ++i) {
        intbinsX[i] = genReco2d->GetXaxis()->FindBin(Xbins[i]+0.001);
        intbinsY[i] = genReco2d->GetYaxis()->FindBin(Xbins[i]+0.001);
//         std::cout << "PSE_bins " << intbinsX[i] << " " << intbinsY[i] << "\n";
        
//         if (intbinsX[i] != intbinsY[i]) std::cout << "ARGH!!!!!\n";
        if (i>0) {
            genRecHist->SetBinContent(i,
                        ((TH2D*)genReco2d)->Integral( intbinsX[i-1],intbinsX[i]-1,intbinsY[i-1],intbinsY[i]-1));
        }
    }

    TH1* genPseHist = ((TH2D*)genReco2d)->ProjectionX();
    TH1* recPseHist = ((TH2D*)genReco2d)->ProjectionY();
    
    TH1* genBinHist    = genPseHist->Rebin(bins,"genBinHist", Xbins);
    TH1* recBinHist    = recPseHist->Rebin(bins,"recBinHist", Xbins);

    genRecHist->SetBinContent(0,      0);
    genRecHist->SetBinContent(bins+1,0);
    genBinHist->SetBinContent(0,      0);
    genBinHist->SetBinContent(bins+1,0);
    recBinHist->SetBinContent(0,      0);
    recBinHist->SetBinContent(bins+1,0);
    genHist   ->SetBinContent(0,      0);
    genHist   ->SetBinContent(bins+1,0);

    // this is realy ugly but necessary:
    // As it seems, somewhere a double is tranformed into a float so that
    // efficiencies can be larger than 1.
    for(Int_t i=1; i<=genRecHist->GetNbinsX(); ++i){
      if(genRecHist->GetBinContent(i) > recBinHist->GetBinContent(i)){
        genRecHist->SetBinContent(i,recBinHist->GetBinContent(i));
        cout << "WARNING in PlotDifferentialCrossSections: number of events generated and reconstructed in bin" << i
	    << " = " << genRecHist->GetBinContent(i) << " is larger than number of reconstructed events in that bin"
	    << " = " << recBinHist->GetBinContent(i) << endl;
      }
      if(genRecHist->GetBinContent(i) > genBinHist->GetBinContent(i)){
        genRecHist->SetBinContent(i,genBinHist->GetBinContent(i));
	    cout << "WARNING in PlotDifferentialCrossSections: number of events generated and reconstructed in bin " << i
	    << " is larger than number of genrated events in that bin" << endl;
      }
    }

    // efficiency, purity, stability
    TGraphAsymmErrors* grE; // for efficiency
    TGraphAsymmErrors* grP; // for purity
    TGraphAsymmErrors* grS; // for stability

    // efficiency
    grE = new TGraphAsymmErrors(recBinHist, genHist);
    grE->SetMinimum(0);
    grE->SetMaximum(1);
    grE->SetLineColor(8);
    grE->SetLineWidth(2);
    grE->SetMarkerSize(2);
    grE->SetMarkerStyle(21);
    grE->SetMarkerColor(8);

    // purity
    grP = new TGraphAsymmErrors(genRecHist, recBinHist);
    grP->SetLineColor(4);
    grP->SetLineWidth(2);
    grP->SetMarkerSize(2);
    grP->SetMarkerStyle(23);
    grP->SetMarkerColor(4);

    // stability
    grS = new TGraphAsymmErrors(genRecHist, genBinHist);
    grS->SetLineColor(2);
    grS->SetLineWidth(2);
    grS->SetMarkerSize(2);
    grS->SetMarkerStyle(22);
    grS->SetMarkerColor(2);


    grE->GetXaxis()->SetTitle(XAxis);
    TCanvas * cESP = new TCanvas("ESP","ESP");

    // this is a dummy to get the x axis range corrct
    recBinHist->Reset();
    recBinHist->Draw();
    recBinHist->SetMaximum(1.);
    //    FormatHisto(recBinHist);
    
    grE->Draw("P,SAME");
    grP->Draw("P,SAME");
    grS->Draw("P,SAME");

    TLegend* leg3 = getNewLegend(); // new TLegend(0.60,0.73,0.95,0.83);
    leg3->SetFillStyle(0);
    leg3->SetBorderSize(0);
    leg3->AddEntry(grE, "Efficiency", "p" );
    leg3->AddEntry(grP, "Purity",    "p" );
    leg3->AddEntry(grS, "Stability", "p" );
    leg3->Draw("SAME");

    cESP->Print("Plots/"+channel+"/ESP_"+name+".eps");
    cESP->Clear();
    delete cESP;
    double efficiencies[XAxisbinCenters.size()];
    init = false;
    for (unsigned int hist =0; hist<hists.size(); hist++){
      if(legends[hist] == "data"){
	    for (Int_t bin=0; bin<bins; ++bin) {//poor for loop placement, but needed because genplot is the sum of all signal histograms
	      DataSum[bin]+=varhists[hist]->GetBinContent(bin+1);
	    }
      }
      else if((legends[hist] == "t#bar{t} signal")&&init==false){
	    init=true;
	    for (Int_t bin=0; bin<bins; ++bin) {//poor for loop placement, but needed because genplot is the sum of all signal histograms
	      efficiencies[bin] = (RecoPlot->GetBinContent(bin+1)) / (GenPlot->GetBinContent(bin+1));
	      GenSignalSum[bin] += GenPlot->GetBinContent(bin+1);
	      //	  cout<<"efficiencies[bin]: "<<efficiencies[bin]<<endl;
	    }      
      }
      else{
		for (Int_t bin=0; bin<bins; ++bin) {//poor for loop placement, but needed because genplot is the sum of all signal histograms
		  BGSum[bin]+=varhists[hist]->GetBinContent(bin+1);
		}
      }      
    }
    double totalDataSum = 0;
    for (Int_t bin=0; bin<bins; ++bin) {
      totalDataSum+=DataSum[bin];
    }
    double binWidth[XAxisbinCenters.size()];
    TH1 *h_DiffXSec = (TH1D*)varhists[0]->Clone();
    TH1 *h_GenDiffXSec = (TH1D*)varhists[0]->Clone();
    h_DiffXSec->Reset();

    // DAVID 
    if ( doUnfolding == true ) {
    	
		// SVD Helper Class
		DilepSVDFunctions mySVDFunctions; 
		mySVDFunctions.SetOutputPath(outpath); 

		
		// Getting the histogram 
		TH1* theDataHist = NULL;
		TH1* theBgrHist = NULL;
		TH1* theRecHist = NULL;
		TH1* theGenHist = GenPlot; 
		TH1* theRespHist = genReco2d;
		for ( size_t i = 0; i < hists.size() ; i++ ) {
			if ( legends[i] == "data" ) {
				if ( theDataHist == NULL ) {
					theDataHist = (TH1*) (varhists[i])->Clone("theDataHist");
				} else {
					theDataHist->Add(varhists[i]);
				}
			} else if ( legends[i] == "t#bar{t} signal") {
				if ( theRecHist == NULL ) {
					theRecHist = (TH1*) (varhists[i])->Clone("theRecHist");
				} else {
					theRecHist->Add(varhists[i]);
				}
			} else {
				if ( theBgrHist == NULL ) {
					theBgrHist = (TH1*) (varhists[i])->Clone("theBgrHist");
				} else {
					theBgrHist->Add(varhists[i]);
				}
			}
		}
	
		// Binning
		double* theBins = Xbins;
		int numberBins = bins;
		
		
		// Names and Labels
		TString channelLabelStr(channelLabel[channelType]);
        TString theChannelName = channelLabelStr; 		
        if ( channelLabelStr.Contains("#mu#mu")  ) theChannelName = "mumu";
        if ( channelLabelStr.Contains("e#mu")    ) theChannelName = "emu";
        if ( channelLabelStr.Contains("ee")      ) theChannelName = "ee";
        if ( channelLabelStr.Contains("comb")    ) theChannelName = "combined";
        TString theParticleName = "";
		if ( name.Contains("Lepton") ) theParticleName = "Leptons";
		if ( name.Contains("LLBar")   ) theParticleName = "LepPair";
		if ( name.Contains("Top")     ) theParticleName = "TopQuark";
		if ( name.Contains("TTBar")   ) theParticleName = "TtBar";
		TString theQuantityName = "";
		if ( name.Contains("pT")      ) theQuantityName = "Pt";
		if ( name.Contains("Eta")     ) theQuantityName = "Eta";
		if ( name.Contains("Rapidity")) theQuantityName = "Rapidity";
		if ( name.Contains("Mass")    ) theQuantityName = "Mass";
		TString theSpecialPostfix = "";
		
//// DAVID
//// Make a real crude reweighting of the Resp and Gen Hists
//double lumiResp = 	theRespHist->Integral();
//double lumiRec =     theRecHist->Integral();
//double lumiGen =     theGenHist->Integral();
//double scaleResp = lumiRec / lumiResp;
//double scaleGen = scaleResp;
//theRespHist->Scale(scaleResp); 
//theGenHist->Scale(scaleGen); // ATTENTION: Scale only the nominal
//                             // histo here, because the shifted ones are
//                             // just pointers to the nominal one
//cout << "*******************************************************************************" << endl;
//cout << "Hey! " << endl;
//cout << "A real crude reweighting is being done here ... " << endl;
//cout << "Scale Factor applied on resp Matrix: " << scaleResp << endl;
//cout << "Scale Factor applied on gen Dist: " << scaleGen << endl;
//cout << "     Integral Resp = " << lumiResp << endl;
//cout << "     Integral Rec  = " << lumiRec << endl;
//cout << "     Integral Gen  = " << lumiGen << endl;
//lumiResp = 	theRespHist->Integral();
//lumiRec =     theRecHist->Integral();
//lumiGen =     theGenHist->Integral();
//cout << "After reweighting" << endl;
//cout << "     Integral Resp = " << lumiResp << endl;
//cout << "     Integral Rec  = " << lumiRec << endl;
//cout << "     Integral Gen  = " << lumiGen << endl;
//cout << "*******************************************************************************" << endl; 
		    	 
		

        // UNFOLDING 
        // Retrieve a histogram with the unfolded quantities.
        // Note: The unfolded histogram has additional side bins!
        // Keep this in mind when accessing bin content via indices
        TH1D* unfoldedDistribution = NULL;
        int numSystematics = 0;
        mySVDFunctions.SVD_DoUnfold(
        	(TH1D*) theDataHist, 
        	(TH1D*) theBgrHist, 
        	(TH1D*) theGenHist, 
        	(TH1D*) theRecHist, 
        	(TH2D*) theRespHist, 
            theBins, numberBins,  
            unfoldedDistribution, numSystematics,
            theChannelName, theParticleName, theQuantityName, theSpecialPostfix, "");
 		
		
		// Make a vector from the result
		double UnfoldingResult[XAxisbinCenters.size()];
		double UnfoldingError[XAxisbinCenters.size()];
		for ( size_t i = 0; i < XAxisbinCenters.size() ; i++ ) {
			UnfoldingResult[i] = unfoldedDistribution->GetBinContent(i+1);
			UnfoldingError[i] = unfoldedDistribution->GetBinError(i+1);
		}
		
		 	
		
		// CROSS SECTION CALCULATION
	    for (Int_t i=0; i<bins; ++i) {
	        if(channelType!=3){
				binWidth[i] = Xbins[i+1]-Xbins[i];       
				DiffXSec[channelType][i] = UnfoldingResult[i]/(binWidth[i]*lumi);
				DiffXSecStatError[channelType][i] = UnfoldingError[i]/(lumi*binWidth[i]); // statistical error 
				GenDiffXSec[channelType][i] = (GenSignalSum[i]*topxsec)/(SignalEvents*binWidth[i]);//DIRTY (signal*topxsec)/(total events*binwidth)
				GenDiffXSecError[channelType][i] = TMath::Sqrt(DataSum[i])/(efficiencies[i]*lumi*binWidth[i]); // statistical error
				
				if(name.Contains("Lepton")||name.Contains("Top")||name.Contains("BJet")){
				  DiffXSec[channelType][i]=DiffXSec[channelType][i]/2.;
				  GenDiffXSec[channelType][i]=GenDiffXSec[channelType][i]/2.;
				  DiffXSecStatError[channelType][i]=DiffXSecStatError[channelType][i]/2.;
				}
			 
	        }else{//For the combination
				binWidth[i] = Xbins[i+1]-Xbins[i];      
				DiffXSec[channelType][i] =(DiffXSec[0][i]/(DiffXSecStatError[0][i]*DiffXSecStatError[0][i])
								 +DiffXSec[1][i]/(DiffXSecStatError[1][i]*DiffXSecStatError[1][i])			
								 +DiffXSec[2][i]/(DiffXSecStatError[2][i]*DiffXSecStatError[2][i]))/
				                                 (1/(DiffXSecStatError[0][i]*DiffXSecStatError[0][i])
							         +(1/(DiffXSecStatError[1][i]*DiffXSecStatError[1][i]))			
							         +(1/(DiffXSecStatError[2][i]*DiffXSecStatError[2][i])));			
			
				DiffXSecStatError[channelType][i]=1/(TMath::Sqrt((1/(DiffXSecStatError[0][i]*DiffXSecStatError[0][i]))
										+(1/(DiffXSecStatError[1][i]*DiffXSecStatError[1][i]))			
			    							+(1/(DiffXSecStatError[2][i]*DiffXSecStatError[2][i]))));			 
				GenDiffXSec[channelType][i] = (GenSignalSum[i]*topxsec)/(SignalEvents*binWidth[i]);//DIRTY (signal*topxsec)/(total events*binwidth)
				GenDiffXSecError[channelType][i] = TMath::Sqrt(DataSum[i])/(efficiencies[i]*lumi*binWidth[i]); // statistical error
		    }
		    h_DiffXSec->SetBinContent(i+1,DiffXSec[channelType][i]);
		    h_DiffXSec->SetBinError(i+1,DiffXSecStatError[channelType][i]);
		    h_GenDiffXSec->SetBinContent(i+1,GenDiffXSec[channelType][i]);	
	    }
	     
    	
    } else { // BBB Unfolding

	    for (Int_t i=0; i<bins; ++i) {
	      if(channelType!=3){
			binWidth[i] = Xbins[i+1]-Xbins[i];      
			//	cout<<"Datasum[i]: "<<DataSum[i]<<" BGSum[i]: "<<BGSum[i]<<" efficiencies[i]: "<<efficiencies[i]<<" binWidth[i]: "<<binWidth[i]<<" lumi: "<<lumi<<endl; 
			DiffXSec[channelType][i] = (DataSum[i]-BGSum[i])/(efficiencies[i]*binWidth[i]*lumi);
			DiffXSecStatError[channelType][i] = TMath::Sqrt(DataSum[i])/(efficiencies[i]*lumi*binWidth[i]); // statistical error
			//	GenDiffXSec[channelType][i] = (GenSignalSum[i]*topxsec)/(SignalEvents*BranchingFraction[channelType]*binWidth[i]);//DIRTY (signal*topxsec)/(total events*bf*binwidth)
			GenDiffXSec[channelType][i] = (GenSignalSum[i]*topxsec)/(SignalEvents*binWidth[i]);//DIRTY (signal*topxsec)/(total events*binwidth)
			GenDiffXSecError[channelType][i] = TMath::Sqrt(DataSum[i])/(efficiencies[i]*lumi*binWidth[i]); // statistical error
			
			if(name.Contains("Lepton")||name.Contains("Top")||name.Contains("BJet")){
			  DiffXSec[channelType][i]=DiffXSec[channelType][i]/2.;
			  GenDiffXSec[channelType][i]=GenDiffXSec[channelType][i]/2.;
			  DiffXSecStatError[channelType][i]=DiffXSecStatError[channelType][i]/2.;
			}
			if (efficiencies[i] == 0) { //cannot divide by zero
			  cout << "WARNING in PlotDifferentialCrossSection: Efficieny is zero in bin " << i << " while creating " << name << endl;
			  h_DiffXSec->SetBinContent(i+1, 0);
			  h_GenDiffXSec->SetBinContent(i+1,GenDiffXSec[channelType][i]);
			}/* else {
		  h_DiffXSec->SetBinContent(i+1,DiffXSec[channelType][i]);
		  h_DiffXSec->SetBinError(i+1,DiffXSecStatError[channelType][i]);
		  h_GenDiffXSec->SetBinContent(i+1,GenDiffXSec[channelType][i]);
		  }*/
		//cout<<endl;
	      }else{//For the combination
			binWidth[i] = Xbins[i+1]-Xbins[i];      
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
			GenDiffXSec[channelType][i] = (GenSignalSum[i]*topxsec)/(SignalEvents*binWidth[i]);//DIRTY (signal*topxsec)/(total events*binwidth)
			GenDiffXSecError[channelType][i] = TMath::Sqrt(DataSum[i])/(efficiencies[i]*lumi*binWidth[i]); // statistical error
	      }
	      h_DiffXSec->SetBinContent(i+1,DiffXSec[channelType][i]);
	      h_DiffXSec->SetBinError(i+1,DiffXSecStatError[channelType][i]);
	      h_GenDiffXSec->SetBinContent(i+1,GenDiffXSec[channelType][i]);	
	    }
    }
 	
    //data normalization
    double datascale;
    datascale = h_DiffXSec->Integral("width");
    if(name.Contains("LeptonEta")){
      TotalVisXSection[channelType] = datascale;
    }
    //cout<<"VISIBLE CROSS-SECTION: "<<TotalVisXSection[channelType]<<endl;
    h_DiffXSec->Scale(1/TotalVisXSection[channelType]);
    

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
      //cout<<"DiffXSec[channelType][bin]: "<<DiffXSec[channelType][bin]<<endl;
      //      cout<<"DiffXSecSysError[channelType][bin]: "<<DiffXSecSysError[channelType][bin]<<endl;
      //cout<<"DiffXSecStatError[channelType][bin]: "<<DiffXSecStatError[channelType][bin]<<endl;
      //DiffXSecTotalError[channelType][bin] = sqrt(DiffXSec[channelType][bin]*DiffXSecSysError[channelType][bin]*DiffXSec[channelType][bin]*DiffXSecSysError[channelType][bin] + DiffXSecStatError[channelType][bin]*DiffXSecStatError[channelType][bin]);
      DiffXSecTotalError[channelType][bin] = sqrt(DiffXSecSysError[channelType][bin]*DiffXSecSysError[channelType][bin] + DiffXSecStatError[channelType][bin]*DiffXSecStatError[channelType][bin]);
      //cout<<"DiffXSecTotalError[channelType][bin]: "<<DiffXSecTotalError[channelType][bin]<<endl;

      DiffXSecPlot[bin]=DiffXSec[channelType][bin]/TotalVisXSection[channelType];
      DiffXSecStatErrorPlot[bin]=DiffXSecStatError[channelType][bin]/TotalVisXSection[channelType];
      DiffXSecTotalErrorPlot[bin]=DiffXSecTotalError[channelType][bin]/TotalVisXSection[channelType];
      //      cout<<"DiffXSecPlot[bin]: "<<DiffXSecPlot[bin]<<endl;
      //      cout<<"DiffXSecStatErrorPlot[bin]: "<<DiffXSecStatErrorPlot[bin]<<endl;
      //cout<<"DiffXSecTotalErrorPlot[bin]: "<<DiffXSecTotalErrorPlot[bin]<<endl<<endl;
    }
 	
    Double_t mexl[XAxisbinCenters.size()];
    Double_t mexh[XAxisbinCenters.size()];
    for (unsigned int j=0; j<XAxisbinCenters.size();j++){mexl[j]=0;mexh[j]=0;}
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
    GenPlot->Scale(topxsec/(SignalEvents*GenPlot->GetBinWidth(1)));
    
    double genscale = 1./GenPlotTheory->Integral("width");
    
    GenPlotTheory->Scale(genscale);
    genscale = 1./ h_GenDiffXSec->Integral("width");
    
    h_GenDiffXSec->Scale(genscale);
    TH1* mcnlohist=0;TH1* mcnlohistup=0;TH1* mcnlohistdown=0;TH1* powheghist=0;
    if(name.Contains("LeptonpT")){mcnlohist = GetNloCurve("Leptons","Pt","MCatNLO");}//temprorary until I change the naming convention in the root file
    else if(name.Contains("LeptonEta")){mcnlohist = GetNloCurve("Leptons","Eta","MCatNLO");}
    else if(name.Contains("LLBarpT")){mcnlohist = GetNloCurve("LepPair","Pt","MCatNLO");}
    else if(name.Contains("LLBarMass")){mcnlohist = GetNloCurve("LepPair","Mass","MCatNLO");}
    else if(name.Contains("ToppT")){mcnlohist = GetNloCurve("TopQuarks","Pt","MCatNLO");}
    else if(name.Contains("TopRapidity")){mcnlohist = GetNloCurve("TopQuarks","Rapidity","MCatNLO");}
    else if(name.Contains("TTBarpT")){mcnlohist = GetNloCurve("TtBar","Pt","MCatNLO");}
    else if(name.Contains("TTBarRapidity")){mcnlohist = GetNloCurve("TtBar","Rapidity","MCatNLO");}
    else if(name.Contains("TTBarMass")){mcnlohist = GetNloCurve("TtBar","Mass","MCatNLO");}
    else{mcnlohist = GetNloCurve("Leptons","Eta","MCatNLO");mcnlohist->SetLineColor(kWhite);}//default curve
    //    mcnlohist = GetNloCurve("TtBar","Mass","MCatNLO");
    double mcnloscale = 1./mcnlohist->Integral("width");
    mcnlohist->Rebin(5);mcnlohist->Scale(0.2);
    mcnlohist->Scale(mcnloscale);

    if(name.Contains("LeptonpT")){mcnlohistup = GetNloCurve("Leptons","Pt","MCNLOup");}//temprorary until I change the naming convention in the root file
    else if(name.Contains("LeptonEta")){mcnlohistup = GetNloCurve("Leptons","Eta","MCNLOup");}
    else if(name.Contains("LLBarpT")){mcnlohistup = GetNloCurve("LepPair","Pt","MCNLOup");}
    else if(name.Contains("LLBarMass")){mcnlohistup = GetNloCurve("LepPair","Mass","MCNLOup");}
    else if(name.Contains("ToppT")){mcnlohistup = GetNloCurve("TopQuarks","Pt","MCNLOup");}
    else if(name.Contains("TopRapidity")){mcnlohistup = GetNloCurve("TopQuarks","Rapidity","MCNLOup");}
    else if(name.Contains("TTBarpT")){mcnlohistup = GetNloCurve("TtBar","Pt","MCNLOup");}
    else if(name.Contains("TTBarRapidity")){mcnlohistup = GetNloCurve("TtBar","Rapidity","MCNLOup");}
    else if(name.Contains("TTBarMass")){mcnlohistup = GetNloCurve("TtBar","Mass","MCNLOup");}
    else {mcnlohistup = new TH1();}
    mcnlohistup->Rebin(5);mcnlohistup->Scale(0.2);
    mcnlohistup->Scale(mcnloscale);

    if(name.Contains("LeptonpT")){mcnlohistdown = GetNloCurve("Leptons","Pt","MCNLOdown");}//temprorary until I change the naming convention in the root file
    else if(name.Contains("LeptonEta")){mcnlohistdown = GetNloCurve("Leptons","Eta","MCNLOdown");}
    else if(name.Contains("LLBarpT")){mcnlohistdown = GetNloCurve("LepPair","Pt","MCNLOdown");}
    else if(name.Contains("LLBarMass")){mcnlohistdown = GetNloCurve("LepPair","Mass","MCNLOdown");}
    else if(name.Contains("ToppT")){mcnlohistdown = GetNloCurve("TopQuarks","Pt","MCNLOdown");}
    else if(name.Contains("TopRapidity")){mcnlohistdown = GetNloCurve("TopQuarks","Rapidity","MCNLOdown");}
    else if(name.Contains("TTBarpT")){mcnlohistdown = GetNloCurve("TtBar","Pt","MCNLOdown");}
    else if(name.Contains("TTBarRapidity")){mcnlohistdown = GetNloCurve("TtBar","Rapidity","MCNLOdown");}
    else if(name.Contains("TTBarMass")){mcnlohistdown = GetNloCurve("TtBar","Mass","MCNLOdown");}
    else {mcnlohistdown = new TH1();}
    mcnlohistdown->Rebin(5);mcnlohistdown->Scale(0.2);
    mcnlohistdown->Scale(mcnloscale);

    if(name.Contains("LeptonpT")){powheghist = GetNloCurve("Leptons","Pt","Powheg");}//temprorary until I change the naming convention in the root file
    else if(name.Contains("LeptonEta")){powheghist = GetNloCurve("Leptons","Eta","Powheg");}
    else if(name.Contains("LLBarpT")){powheghist = GetNloCurve("LepPair","Pt","Powheg");}
    else if(name.Contains("LLBarMass")){powheghist = GetNloCurve("LepPair","Mass","Powheg");}
    else if(name.Contains("ToppT")){powheghist = GetNloCurve("TopQuarks","Pt","Powheg");}
    else if(name.Contains("TopRapidity")){powheghist = GetNloCurve("TopQuarks","Rapidity","Powheg");}
    else if(name.Contains("TTBarpT")){powheghist = GetNloCurve("TtBar","Pt","Powheg");}
    else if(name.Contains("TTBarRapidity")){powheghist = GetNloCurve("TtBar","Rapidity","Powheg");}
    else if(name.Contains("TTBarMass")){powheghist = GetNloCurve("TtBar","Mass","Powheg");}
    else {powheghist = new TH1();}
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
 
    h_GenDiffXSec->SetMinimum(ymin);
    if(logY){  
      h_GenDiffXSec->SetMaximum(20*h_GenDiffXSec->GetBinContent(h_GenDiffXSec->GetMaximumBin()));
    }
    else{ h_GenDiffXSec->SetMaximum(1.2*h_GenDiffXSec->GetBinContent(h_GenDiffXSec->GetMaximumBin()));}
    h_GenDiffXSec->Draw();
    //h_DiffXSec->Draw("SAME, EP0");
    gStyle->SetEndErrorSize(8);
    mcatnloBand->Draw("same, F");

    GenPlotTheory->SetLineColor(2);
    GenPlotTheory->Rebin(4);GenPlotTheory->Scale(1./4.);
    GenPlotTheory->Draw("SAME,C");
    h_GenDiffXSec->SetLineColor(2);
    mcnlohist->SetLineColor(kAzure);
    //mcnlohist->Draw("SAME,C");
    powheghist->SetLineColor(kGreen+1);
    //powheghist->Draw("SAME,C");
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
    h_GenDiffXSec->Draw("SAME");
    tga_DiffXSecPlot->Draw("p, SAME");
    //tga_DiffXSecPlotwithSys->Draw("p, SAME, Z");
    gPad->RedrawAxis();
    
    c->Print("Plots/"+channel+"/DiffXS_"+name+".eps");
    c->Clear();
    delete c;
     	
    
    TCanvas * c1 = new TCanvas("DiffXS","DiffXS");
    TList* l = stack->GetHists();
    TH1D* stacksum = (TH1D*) l->At(0)->Clone();
    for (int i = 1; i < l->GetEntries(); ++i) {
      stacksum->Add((TH1D*)l->At(i));
    } 

    for(unsigned int i=1; i<hists.size() ; i++){ // sum all data plots to first histogram
      if(legends[i] == legends[0]){
	varhists[0]->Add(varhists[i]);
      }
    }
    varhists[0]->SetMinimum(0);
    varhists[0]->GetYaxis()->SetTitle("N_{Events}");
    varhists[0]->Draw("el");
    stack->Draw("same HIST");
    varhists[0]->Draw("same, e1");
    DrawCMSLabels(true, lumi);
    DrawDecayChLabel(channelLabel[channelType]);    
    leg->Draw("SAME");
    gPad->RedrawAxis();
    TFile *f1 = new TFile("KinFitPlots.root","UPDATE");
    stacksum->Write(name+"_"+channel+"_MC");
    varhists[0]->Write(name+"_"+channel+"_Data");
    f1->Close();
    c1->Print("Plots/"+channel+"/preunfolded_"+name+".eps");
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

    if(strcmp(generator, "Powheg")==0){file = TFile::Open("Powheg.root","READ");}
    else if(strcmp(generator, "MCatNLO")==0){file = TFile::Open("MCatNLO_status3_v20111028.root","READ");}
    else if(strcmp(generator, "MCNLOup")==0){file = TFile::Open("MCatNLO_Uncert_Up_status3_v20111028.root","READ");}
    else if(strcmp(generator, "MCNLOdown")==0){file = TFile::Open("MCatNLO_Uncert_Down_status3_v20111028.root","READ");}

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
    delete file;
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
