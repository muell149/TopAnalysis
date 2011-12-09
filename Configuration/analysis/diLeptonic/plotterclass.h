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
#include "TStyle.h"
#include "TMath.h"
#include "TROOT.h"
#include <sstream>
#include "basicFunctions.h"
#include "HHStyle.h"

//#include <Int_t.h>




class Plotter {

 public:
  Plotter();
  Plotter(TString, TString, TString, int, double, double, double);
  ~Plotter();
  void   setOptions(TString, TString, TString, int, double, double, double);
  void   setDataSet(std::vector<TString>, std::vector<double>, std::vector<TString>, std::vector<int>, TString);
  void   setDataSet(TString);
  void   fillHisto();
  void   fill(TString, float, Double_t);
  void   fill(TString, double, Double_t);
  void   fill(TString, int, Double_t);
  void   fill(TString, std::vector<float>, Double_t);
  void   fill(TString, std::vector<double>, Double_t);
  void   fill(TString, std::vector<int>, Double_t);
  void setStyle(TH1F&, unsigned int);
  void setStyle(TH1&, unsigned int);
  void   write();
  void writeRescaleHisto(TString, std::vector<TString> ); //for specific samples
  void writeRescaleHisto(TString);                        //for all MC
  double CalcXSec();
  double CalcDYScale();
  void PlotDiffXSec();
  TLegend* getNewLegend();
  TH1* GetNloCurve(const char *particle, const char *quantity, const char *generator);
 private:
  TString name;
  TString title;
  int bins;
  double rangemin;
  double rangemax;
  std::vector<TFile> files;
  std::vector<TString> dataset;
  std::vector<double> scales;
  std::vector<TString> legends;
  std::vector<int> colors;
  double DYScale;
  TString DYEntry;
  TString YAxis;
  TString channel;
  int channelType; //0=ee 1==mumu 2==emu 3==combined  
  TH1F onehist;
  std::vector<TH1F> hists;
  std::vector<TH1D> hists2;
  bool initialized;
  int lumi;
  double InclusiveXsection[4];
  double InclusiveXsectionError[4];
  double VisXsection[4][10];//needed for bin-by-bin corrections to combination [channel][bin]
  double VisXsectionError[4][10];//needed for bin-by-bin corrections to combination [channel][bin]
  double DiffXSec[4][10];//the differential X-section per channel by bin [channel][bin]
  double DiffXSecError[4][10];//the differential X-section Error per channel by bin [channel][bin]
  double GenDiffXSec[4][10];//the differential X-section per channel by bin [channel][bin]
  double GenDiffXSecError[4][10];//the differential X-section Error per channel by bin [channel][bin]

};



Plotter::Plotter()
{
  title="defaultTitle";
  name="defaultName";
  bins=10;
  rangemin=0;
  rangemax=3;
  DYScale=1;
  YAxis="N_{events}";
  initialized=false;
  
}

Plotter::Plotter(TString title_, TString name_, TString YAxis_, int bins_, double rangemin_, double rangemax_, double DYScale_)
{
  title=title_;
  name=name_;
  bins=bins_;
  rangemin=rangemin_;
  rangemax=rangemax_;
  DYScale=DYScale_;
  YAxis=YAxis_;
  initialized=false;
}

Plotter::~Plotter()
{
}

void Plotter::setOptions(TString title_, TString name_, TString YAxis_, int bins_, double rangemin_, double rangemax_, double DYScale_)
{
  title=title_;
  name=name_;
  bins=bins_;
  rangemin=rangemin_;
  rangemax=rangemax_;
  DYScale=DYScale_;
  YAxis=YAxis_;
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
  if(channel =="ee")channelType=0;
  if(channel =="mumu")channelType=1;
  if(channel =="emu")channelType=2;
  if(channel =="combined")channelType=3;

  lumi=1141;
  

  if(channel=="ee"){  
    DYEntry = "Z^{0} / #gamma* #rightarrow ee";
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
	else if(filename.Contains("dymumu")){legends.push_back("Z^{0} / #gamma* #rightarrow #mu#mu"); colors.push_back(kAzure-2);}
	else if(filename.Contains("dyee")){legends.push_back("Z^{0} / #gamma* #rightarrow ee"); colors.push_back(kAzure-2);}
	else if(filename.Contains("wtolnu")){legends.push_back("W #rightarrow l#nu"); colors.push_back(kGreen-3);}
	else if(filename.Contains("qcd")){legends.push_back("QCD"); colors.push_back(kYellow);}
      }
    }
  }

  if(mode=="mumu"){

    dataset.clear();
    legends.clear();
    colors.clear();
    DYEntry = "Z^{0} / #gamma* #rightarrow #mu#mu";
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
	else if(filename.Contains("dymumu")){legends.push_back("Z^{0} / #gamma* #rightarrow #mu#mu"); colors.push_back(kAzure-2);}
	else if(filename.Contains("dyee")){legends.push_back("Z^{0} / #gamma* #rightarrow ee"); colors.push_back(kAzure-2);}
	else if(filename.Contains("wtolnu")){legends.push_back("W #rightarrow l#nu"); colors.push_back(kGreen-3);}
	else if(filename.Contains("qcd")){legends.push_back("QCD"); colors.push_back(kYellow);}
      }
    }
  }
  if(mode=="emu"){

    dataset.clear();
    legends.clear();
    colors.clear();
    DYEntry = "";
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
	else if(filename.Contains("dymumu")){legends.push_back("Z^{0} / #gamma* #rightarrow #mu#mu"); colors.push_back(kAzure-2);}
	else if(filename.Contains("dyee")){legends.push_back("Z^{0} / #gamma* #rightarrow ee"); colors.push_back(kAzure-2);}
	else if(filename.Contains("wtolnu")){legends.push_back("W #rightarrow l#nu"); colors.push_back(kGreen-3);}
	else if(filename.Contains("qcd")){legends.push_back("QCD"); colors.push_back(kYellow);}
      }
    }
  }
  if(mode=="combined"){

    dataset.clear();
    legends.clear();
    colors.clear();
    DYEntry = "";
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
	else if(filename.Contains("dymumu")){legends.push_back("Z^{0} / #gamma* #rightarrow #mu#mu"); colors.push_back(kAzure-2);}
	else if(filename.Contains("dyee")){legends.push_back("Z^{0} / #gamma* #rightarrow ee"); colors.push_back(kAzure-2);}
	else if(filename.Contains("wtolnu")){legends.push_back("W #rightarrow l#nu"); colors.push_back(kGreen-3);}
	else if(filename.Contains("qcd")){legends.push_back("QCD"); colors.push_back(kYellow);}
      }
    }
  }
}


void Plotter::fillHisto()
{
  if(!initialized){
    hists.clear();
    for(unsigned int i=0; i<dataset.size(); i++){
      TFile *ftemp = TFile::Open(dataset[i]);
      TH1F *hist = (TH1F*)ftemp->Get(name);     
      setHHStyle(*gStyle);
      gStyle->SetErrorX(0);
      hists.push_back(*hist);
    }
    initialized=true;
  }
}

void Plotter::fill(TString dataType, float no, Double_t weight)
{
  if(!initialized){

    TH1F hist = TH1F(title, name, bins, rangemin, rangemax);

    for(unsigned int i=0; i<dataset.size(); i++){
      hists.push_back(hist);
    }
    initialized=true;
  }

  for(unsigned int j = 0; j < dataset.size(); j++){
    if(dataType == dataset[j]){
      hists[j].Fill(no, weight);
    }
  }

}

void Plotter::fill(TString dataType, int  no, Double_t weight)
{
  fill(dataType, (float) no, weight);
}

void Plotter::fill(TString dataType, double  no, Double_t weight)
{
  fill(dataType, (float) no, weight);
}

void Plotter::fill(TString dataType, std::vector<int> no, Double_t weight)
{
  for(unsigned int i=0; i< no.size(); i++){
  fill(dataType, (float) no[i], weight);
  }
}

void Plotter::fill(TString dataType, std::vector<double> no, Double_t weight)
{
  for(unsigned int i=0; i< no.size(); i++){
  fill(dataType, (float) no[i], weight);
  }
}

void Plotter::fill(TString dataType, std::vector<float> no, Double_t weight)      //// DONT HAND OVER POINTERS!!!
{
  for(unsigned int i=0; i< no.size(); i++){
  fill(dataType, no[i], weight);
  }
}


void Plotter::write() // do scaling, stacking, legending, and write in file MISSING: DY Rescale
{
  //hists[0].Write();
  //c->Write();
  
  if(initialized){

  TCanvas * c = new TCanvas(title,title);

// fill(dataset[0], -999, 1);

  THStack * stack=  new THStack("def", "def");
  TLegend * leg =  new TLegend(0.70,0.65,0.95,0.90);


  TH1F *drawhists[hists.size()];

  std::stringstream ss;
  if(channelType==0){DYScale = 1.23;}
  if(channelType==1){DYScale = 1.27;}
  if(channelType==2){DYScale = 1.00;}
  ss << DYScale;
  TString scale;

  scale=(TString)ss.str();
  
  leg->Clear();
  c->Clear();
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  c->SetName(title);
  c->SetTitle(title);
  for(unsigned int i=0; i<hists.size() ; i++){ // prepare histos and leg
    drawhists[i]=(TH1F*) hists[i].Clone();
    setStyle(*drawhists[i], i);
    if(legends[i] != "data"){
      if(legends[i] == DYEntry) drawhists[i]->Scale(DYScale);
      if(i > 1){
	if(legends[i] != legends[i-1]){
	  if(legends[i] == DYEntry && DYScale != 1) leg->AddEntry(drawhists[i], legends[i]);
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
  TH1* stacksum = (TH1*) l->At(0)->Clone();
  for (int i = 1; i < l->GetEntries(); ++i) {
    stacksum->Add((TH1*)l->At(i));
  }
    
  drawhists[0]->Draw("el");
  stack->Draw("same");
  drawhists[0]->Draw("same, e1");
  DrawCMSLabels(true, 1143);
  DrawDecayChLabel(channel);    
  leg->Draw("SAME");
  //drawRatio(drawhists[0], stacksum, 0.5, 1.9, *gStyle);
  gSystem->MakeDirectory("Plots");
  gSystem->MakeDirectory("Plots/"+channel);
  c->Print("Plots/"+channel+"/"+name+".eps");
  c->Clear();
  leg->Clear();
  delete c;
  delete leg;
  //delete stack;
  }
  else std::cout << "Histogram " << title << " not filled during the process." << std::endl;
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
    //   hist.GetXaxis()->SetTitle(name);
    hist.GetXaxis()->SetTitle("M^{t#bar{t}} #left[#frac{GeV}{c^{2}}#right]");
    hist.GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d#sigma}{dX}");
  }
}

void Plotter::setStyle(TH1F &hist, unsigned int i)
{
  hist.SetFillColor(colors[i]);
  hist.SetLineColor(colors[i]);
  

  if(legends[i] == "data"){
    hist.SetMarkerStyle(20); 
    hist.SetMarkerSize(1.);
    hist.SetLineWidth(1);
    hist.GetXaxis()->SetLabelFont(42);
    hist.GetXaxis()->SetTitle(name);
    hist.GetYaxis()->SetTitle(YAxis);
  }
}

double Plotter::CalcXSec(){
  double BranchingFraction[4]={0.0167, 0.0162, 0.0328, 0.06569};//[ee, mumu, emu]
  lumi = 1141;

  TH1F *numhists[hists.size()];
  double numbers[4]={0};

  for(unsigned int i=0; i<dataset.size(); i++){
    TFile *ftemp = TFile::Open(dataset[i]);
    TH1F *hist = (TH1F*)ftemp->Get("jetMulti");     
    numhists[i]=hist;
  }


  for(unsigned int i=0; i<hists.size() ; i++){ // prepare histos and leg

    if(legends[i] == "data"){
      //cout<<legends[i]<<" = "<<numhists[i]->Integral()<<endl;
      numbers[0]+=numhists[i]->Integral();
    }
    else if(legends[i] == "t#bar{t} signal"){
      TFile *ftemp2 = TFile::Open(dataset[i]);
      TH1D *NoPUPlot = (TH1D*)ftemp2->Get("jetMultiNoPU");
      //cout<<legends[i]<<" = "<<numhists[i]->Integral()<<endl;
      numbers[1]+=NoPUPlot->Integral();
      
      TFile *ftemp = TFile::Open(dataset[i]);
      TH1D *GenPlot = (TH1D*)ftemp->Get("GenAll");
      numbers[2]+=GenPlot->Integral();
    } 
    else{
      if(legends[i] == DYEntry) hists[i].Scale(DYScale);
      //cout<<legends[i]<<" = "<<numhists[i]->Integral()<<endl;
      numbers[3]+=(int)numhists[i]->Integral();
    }        
  }  
  //  cout<<"Total Data: "<<numbers[0]<<endl;
  //cout<<"Total ttbar signal: "<<numbers[1]<<endl;
  //cout<<"Total GenTTBar: "<<numbers[2]<<endl;
  //cout<<"Total Other Bg: "<<numbers[3]<<endl;

  double xsec = (numbers[0]-numbers[3])/((numbers[1]/numbers[2])*BranchingFraction[channelType]*lumi);
  double xsecstaterror = TMath::Sqrt(numbers[0])/((numbers[1]/numbers[2])*BranchingFraction[channelType]*lumi);

  if(channelType!=3){
    InclusiveXsection[channelType] = xsec;
    InclusiveXsectionError[channelType] = xsecstaterror;
  }else{
    InclusiveXsection[channelType] =(InclusiveXsection[0]/(InclusiveXsectionError[0]*InclusiveXsectionError[0])
				    +InclusiveXsection[1]/(InclusiveXsectionError[1]*InclusiveXsectionError[1])			
		   		    +InclusiveXsection[2]/(InclusiveXsectionError[2]*InclusiveXsectionError[2]))/
				     (1/(InclusiveXsectionError[0]*InclusiveXsectionError[0])
				    +(1/(InclusiveXsectionError[1]*InclusiveXsectionError[1]))			
				    +(1/(InclusiveXsectionError[2]*InclusiveXsectionError[2])));			

    InclusiveXsectionError[channelType] =1/(TMath::Sqrt((1/(InclusiveXsectionError[0]*InclusiveXsectionError[0]))
							+(1/(InclusiveXsectionError[1]*InclusiveXsectionError[1]))			
    							+(1/(InclusiveXsectionError[2]*InclusiveXsectionError[2]))));			

    cout<<"!!!!!!!!!!!!!!!!!!!!ee Cross Section: "<<InclusiveXsection[0]<<" +/- "<<InclusiveXsectionError[0]<<endl;
    cout<<"!!!!!!!!!!!!!!!!!!!!mumu Cross Section: "<<InclusiveXsection[1]<<" +/- "<<InclusiveXsectionError[1]<<endl;
    cout<<"!!!!!!!!!!!!!!!!!!!!emu Cross Section: "<<InclusiveXsection[2]<<" +/- "<<InclusiveXsectionError[2]<<endl;
    cout<<"!!!!!!!!!!!!!!!!!!!!Combined Cross Section: "<<InclusiveXsection[3]<<" +/- "<<InclusiveXsectionError[3]<<endl;
  }
  return xsec;
}

void Plotter::PlotDiffXSec(){
    double topxsec = 169.9;
    double BranchingFraction[4]={0.0167, 0.0162, 0.0328, 0.06569};//[ee, mumu, emu]
    double SignalEvents = 3701947.0;

    const Int_t nbins = 5;
    const Double_t Xbins[nbins+1] = {345, 400, 475, 550, 700, 1000};//for ttbarmass
    //    const Double_t binCenterTopPt[nbinsTopPt] = {32, 109, 185, 308};

    TH1 *RecoPlot = new TH1D;
    TH1 *GenPlot =new TH1D;
    TH1 *GenPlotTheory =new TH1D;
    double DataSum[nbins]={0};
    double GenSignalSum[nbins]={0};
    double BGSum[nbins]={0};

    TH1 *varhists[hists.size()];

    for (unsigned int i =0; i<hists.size(); i++){
      varhists[i]=hists[i].Rebin(nbins,"",Xbins);            
      setStyle(*varhists[i], i);
      if(legends[i] == "t#bar{t} signal"){
	TFile *ftemp2 = TFile::Open(dataset[i]);
	TH1D *temp2 =  (TH1D*)ftemp2->Get("RecoTTBarMass");
	RecoPlot = (TH1*)temp2->Rebin(nbins,"",Xbins);
	//      cout<<legends[i]<<" = "<<numhists[i]->Integral()<<endl;
	//numbers[1]+=NoPUPlot->Integral();
	
	TFile *ftemp = TFile::Open(dataset[i]);
	GenPlotTheory =  (TH1D*)ftemp->Get("VisGenTTBarMass");
	GenPlot =GenPlotTheory->Rebin(nbins,"",Xbins);	
      }           
    }

    double efficiencies[nbins];
    for (unsigned int hist =0; hist<hists.size(); hist++){
      
      for (Int_t bin=0; bin<nbins; ++bin) {
	if(legends[hist] == "data"){
	  DataSum[bin]+=varhists[hist]->GetBinContent(bin+1);
	}
	else if(legends[hist] == "t#bar{t} signal"){
	  efficiencies[bin] = (RecoPlot->GetBinContent(bin+1)) / (GenPlot->GetBinContent(bin+1));
	  GenSignalSum[bin] += varhists[hist]->GetBinContent(bin+1);
	}
	else{
	  //	  BGSum[bin]+=varhists[bin]->GetBinContent(bin+1);
	  BGSum[bin]+=varhists[hist]->Integral(bin,bin+1);
	}
      }
    }
    double binWidth[nbins] ={0};
    //    double DiffXSec[nbins]={0};
    //    double DiffXSec[nbins]={0};
    //    double GenDiffXSec[nbins]={0};
    TH1 *h_DiffXSec = (TH1*)varhists[0]->Clone();
    TH1 *h_GenDiffXSec = (TH1*)varhists[0]->Clone();
    h_DiffXSec->Reset();

    for (Int_t i=0; i<nbins; ++i) {
      if(channelType!=3){
	binWidth[i] = Xbins[i+1]-Xbins[i];      
	DiffXSec[channelType][i] = (DataSum[i]-BGSum[i])/(efficiencies[i]*binWidth[i]*lumi);
	DiffXSecError[channelType][i] = TMath::Sqrt(DataSum[i])/(efficiencies[i]*lumi*binWidth[i]); // statistical error
	GenDiffXSec[channelType][i] = (GenSignalSum[i]*topxsec)/(SignalEvents*BranchingFraction[channelType]*binWidth[i]);//DIRTY (signal*topxsec)/(total events*bf*binwidth)
	GenDiffXSecError[channelType][i] = TMath::Sqrt(DataSum[i])/(efficiencies[i]*lumi*binWidth[i]); // statistical error
	cout<<"DataSum[i]: "<<DataSum[i]<<endl;
	cout<<"GenSignalSum[i]: "<<GenSignalSum[i]<<endl;
	cout<<"BGSum[i]: "<<BGSum[i]<<endl;
	cout<<"efficiencies[i]: "<<efficiencies[i]<<endl;
	cout<<"binWidth[i]: "<<binWidth[i]<<endl;
	
	
	// set measured cross section
	if (efficiencies[i] == 0) { //cannot divide by zero
	  cout << "WARNING in PlotDifferentialCrossSection: Efficieny is zero in bin " << i << " while creating " << title << endl;
	  h_DiffXSec->SetBinContent(i+1, 0);
	  //	h_DiffXSec->SetBinError(i+1, 0);
	} else {
	  cout<<"DiffXSec[i]: "<<DiffXSec[channelType][i]<<endl;;
	  cout<<"GenDiffXSec[i]: "<<GenDiffXSec[i]<<endl;;
	  h_DiffXSec->SetBinContent(i+1,DiffXSec[channelType][i]);
	  h_GenDiffXSec->SetBinContent(i+1,GenDiffXSec[channelType][i]);
	  h_DiffXSec->SetBinError(i+1,(TMath::Sqrt(DataSum[i]))/(efficiencies[i]*lumi*binWidth[i])); // statistical error
	  //	h_GenDiffXSec->SetBinError(i+1,0);
	}
	cout<<endl;
      }else{//For the combination
	DiffXSec[channelType][i] =(DiffXSec[0][i]/(DiffXSecError[0][i]*DiffXSecError[0][i])
					 +DiffXSec[1][i]/(DiffXSecError[1][i]*DiffXSecError[1][i])			
					 +DiffXSec[2][i]/(DiffXSecError[2][i]*DiffXSecError[2][i]))/
	                                 (1/(DiffXSecError[0][i]*DiffXSecError[0][i])
				         +(1/(DiffXSecError[1][i]*DiffXSecError[1][i]))			
				         +(1/(DiffXSecError[2][i]*DiffXSecError[2][i])));			

	DiffXSecError[channelType][i]=1/(TMath::Sqrt((1/(DiffXSecError[0][i]*DiffXSecError[0][i]))
							+(1/(DiffXSecError[1][i]*DiffXSecError[1][i]))			
    							+(1/(DiffXSecError[2][i]*DiffXSecError[2][i]))));			

	//cout<<"&&&&&&&&&&&&&&&!!!!!!!!ee DiffCross Sec: "<<DiffXSec[0][i]<<" +/- "<<DiffXSecError[0][i]<<endl;
	//cout<<"&&&&&&&&&&&&&&&!!!!!!!!mumu DiffCross Sec: "<<DiffXSec[1][i]<<" +/- "<<DiffXSecError[1][i]<<endl;
	//cout<<"&&&&&&&&&&&&&&&!!!!!!!!emu DiffCross Sec: "<<DiffXSec[2][i]<<" +/- "<<DiffXSecError[2][i]<<endl;
	//cout<<"&&&&&&&&&&&&&&&!!!!!!!!Combined DiffCross Sec: "<<DiffXSec[3][i]<<" +/- "<<DiffXSecError[3][i]<<endl;
	h_DiffXSec->SetBinContent(i+1,DiffXSec[channelType][i]);
	h_DiffXSec->SetBinError(i+1,DiffXSecError[channelType][i]);


	/*	GenDiffXSec[channelType][i] =(GenDiffXSec[0][i]/(GenDiffXSecError[0][i]*GenDiffXSecError[0][i])
				      +GenDiffXSec[1][i]/(GenDiffXSecError[1][i]*GenDiffXSecError[1][i])			
				      +GenDiffXSec[2][i]/(GenDiffXSecError[2][i]*GenDiffXSecError[2][i]))/
	                                 (1/(GenDiffXSecError[0][i]*GenDiffXSecError[0][i])
				         +(1/(GenDiffXSecError[1][i]*GenDiffXSecError[1][i]))			
				         +(1/(GenDiffXSecError[2][i]*GenDiffXSecError[2][i])));			

	GenDiffXSecError[channelType][i]=1/(TMath::Sqrt((1/(GenDiffXSecError[0][i]*GenDiffXSecError[0][i]))
							+(1/(GenDiffXSecError[1][i]*GenDiffXSecError[1][i]))			
    							+(1/(GenDiffXSecError[2][i]*GenDiffXSecError[2][i]))));			

	cout<<"&&&&&&&&&&&&&&&!!!!!!!!ee GenDiffCross Sec: "<<GenDiffXSec[0][i]<<" +/- "<<GenDiffXSecError[0][i]<<endl;
	cout<<"&&&&&&&&&&&&&&&!!!!!!!!mumu GenDiffCross Sec: "<<GenDiffXSec[1][i]<<" +/- "<<GenDiffXSecError[1][i]<<endl;
	cout<<"&&&&&&&&&&&&&&&!!!!!!!!emu GenDiffCross Sec: "<<GenDiffXSec[2][i]<<" +/- "<<GenDiffXSecError[2][i]<<endl;
	cout<<"&&&&&&&&&&&&&&&!!!!!!!!Combined GenDiffCross Sec: "<<GenDiffXSec[3][i]<<" +/- "<<GenDiffXSecError[3][i]<<endl;
	h_GenDiffXSec->SetBinContent(i+1,GenDiffXSec[channelType][i]);
	h_GenDiffXSec->SetBinError(i+1,GenDiffXSecError[channelType][i]);*/
      }
    }

    //data normalization
    double datascale;
    datascale = 1./h_DiffXSec->Integral("width");//this is fine for one channel, but for the combination?
    h_DiffXSec->Scale(datascale);
    

    for (Int_t i=0; i<nbins; ++i) {//I don't think this is needed, but put it here for good measure
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
	
	//	cout<<"&&&&&&&&&&&&&&&!!!!!!!!ee VisCross section: "<<VisXsection[0][i]<<" +/- "<<VisXsectionError[0][i]<<endl;
	//cout<<"&&&&&&&&&&&&&&&!!!!!!!!mumu VisCross section: "<<VisXsection[1][i]<<" +/- "<<VisXsectionError[1][i]<<endl;
	//cout<<"&&&&&&&&&&&&&&&!!!!!!!!emu VisCross section: "<<VisXsection[2][i]<<" +/- "<<VisXsectionError[2][i]<<endl;
	//cout<<"&&&&&&&&&&&&&&&!!!!!!!!Combined VisCross section: "<<VisXsection[3][i]<<" +/- "<<VisXsectionError[3][i]<<endl;
      }	 
    }
    //theory curves

    GenPlotTheory->Scale(topxsec/(SignalEvents*GenPlotTheory->GetBinWidth(1)));
    
    double genscale = 1./GenPlotTheory->Integral("width");
    
    GenPlotTheory->Scale(genscale);
	
    //genscale = 1./ h_GenDiffXSec->Integral("width");
    //h_GenDiffXSec->Scale(genscale);



    TH1* mcnlohist = GetNloCurve("TtBar","Mass","MCatNLO");
    double mcnloscale = 1./mcnlohist->Integral("width");
    mcnlohist->Rebin(10);mcnlohist->Scale(0.1);
    mcnlohist->Scale(mcnloscale);

    TH1* mcnlohistup = GetNloCurve("TtBar","Mass","MCNLOup");
    mcnlohistup->Rebin(10);mcnlohistup->Scale(0.1);
    mcnlohistup->Scale(mcnloscale);

    TH1* mcnlohistdown = GetNloCurve("TtBar","Mass","MCNLOdown");
    mcnlohistdown->Rebin(10);mcnlohistdown->Scale(0.1);
    mcnlohistdown->Scale(mcnloscale);

    TH1* powheghist = GetNloCurve("TtBar","Mass","Powheg");
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
    
    c->SetLogy();

    h_DiffXSec->SetMarkerStyle(20);
 
    h_DiffXSec->Draw("EP0");
    mcatnloBand->Draw("same, F");

    GenPlotTheory->SetLineColor(2);
    GenPlotTheory->Rebin(4);GenPlotTheory->Scale(1./4.);
    GenPlotTheory->Draw("SAME,C");

    h_GenDiffXSec->SetLineColor(2);
    h_GenDiffXSec->Draw("SAME");
    mcnlohist->SetLineColor(kAzure);
    mcnlohist->Draw("SAME,C");
    powheghist->SetLineColor(kGreen+1);
    powheghist->Draw("SAME,C");
    h_DiffXSec->Draw("SAME, EP0");
    DrawCMSLabels(true, lumi);
    DrawDecayChLabel(channel);    
    
    TLegend leg2 = *getNewLegend();
    leg2.AddEntry(h_DiffXSec, "Data",    "p");
    leg2.AddEntry(GenPlotTheory,            "Madgraph","l");
    if (mcnlohistup->GetEntries() && mcnlohistdown->GetEntries()) leg2.AddEntry(mcatnloBand,      "MC@NLO",  "fl");
    else if (mcnlohist->GetEntries()) leg2.AddEntry(mcnlohist,      "MC@NLO",  "l");
    if (powheghist->GetEntries())  leg2.AddEntry(powheghist,       "Powheg",  "l");        
    leg2.SetFillStyle(0);
    leg2.SetBorderSize(0);
    leg2.Draw("same");

    
    
    c->Print("Plots/"+channel+"/DiffXS.eps");
    c->Clear();
    delete c;
    
    THStack * stack=  new THStack("def", "def");
    TLegend * leg =  new TLegend(0.70,0.65,0.95,0.90);
    //TH1 *varhists[hists.size()];
    
    for(unsigned int i=0; i<hists.size() ; i++){ // prepare histos and leg
      //varhists[i]=(TH1F*) hists[i].Clone();
      setStyle(*varhists[i], i);
      if(legends[i] != "data"){
	if(legends[i] == DYEntry) varhists[i]->Scale(DYScale);
	if(i > 1){
	  if(legends[i] != legends[i-1]){
	    if(legends[i] == DYEntry && DYScale != 1) leg->AddEntry(varhists[i], legends[i]);
	    else leg->AddEntry(varhists[i], legends[i] ,"f");
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
    TH1* stacksum = (TH1*) l->At(0)->Clone();
    for (int i = 1; i < l->GetEntries(); ++i) {
      stacksum->Add((TH1*)l->At(i));
    }
    
    varhists[0]->Draw("el");
    stack->Draw("same");
    varhists[0]->Draw("same, e1");
    DrawCMSLabels(true, 1143);
    DrawDecayChLabel("#mu#mu");    
    leg->Draw("SAME");
    
    c1->Print("Plots/"+channel+"/BinnedMass.eps");
    c1->Clear();
    delete c1;
}

void Plotter::writeRescaleHisto(TString histname, std::vector<TString> samples)
{

  if(initialized && hists.size()>0){
    TH1F h = hists[0];
    h.SetName(histname);
    h.SetTitle(histname);

    for(int binIter=1; binIter<hists[0].GetNbinsX()+1; binIter++){
      float nMC=0;
      float nData=0;
      float nSample=0;

      for(unsigned int i=0; i<hists.size() ; i++){
	if(legends[i] == "data") nData=nData + hists[i].GetBinContent(binIter);
	else                     nMC=nMC +  hists[i].GetBinContent(binIter);
	for(unsigned int j=0; j<samples.size(); j++){
	  if(dataset[i] == samples[j]) nSample=nSample +  hists[i].GetBinContent(binIter);
	}
      }
      if(nSample!=0 && 1+(nData-nMC)/nSample > 0) h.SetBinContent(binIter, 1+(nData-nMC)/nSample);
      else           h.SetBinContent(binIter, 1);
      std::cout << nData << " d  " << nMC << " MC   " << nSample << " S  in bin " << binIter << std::endl;
    }
    h.Write();
  }
  else std::cout << "Histogram " << title << " not filled during the process." << std::endl;

}


void Plotter::writeRescaleHisto(TString histname)
{

  if(initialized && hists.size()>0){
    TH1F h = hists[0];
    h.SetName(histname);
    h.SetTitle(histname);

    std::vector<TString> samples=dataset;

    for(int binIter=1; binIter<hists[0].GetNbinsX()+1; binIter++){
      float nMC=0;
      float nData=0;

      for(unsigned int i=0; i<hists.size() ; i++){
	if(legends[i] == "data") nData=nData +  hists[i].GetBinContent(binIter);
	else                     nMC=nMC +  hists[i].GetBinContent(binIter);
	
      }
      if(nMC!=0 && nData!=0) h.SetBinContent(binIter, (nData/nMC));
      else                   h.SetBinContent(binIter, 1);
      std::cout << nData << " d  " << nMC << " MC  in bin " << binIter << std::endl;
    }
    h.Write();
  }
  else std::cout << "Histogram " << title << " not filled during the process." << std::endl;

}

// get generator cross section curve for NLO prediction
TH1* Plotter::GetNloCurve(const char *particle, const char *quantity, const char *generator){

    TString histname("visible_");
    histname.Append(particle);
    histname.Append(quantity);
    histname.Append("_");
    histname.Append(generator);

    TH1* hist;

    TFile* file = new TFile;

    if(strcmp(generator, "Powheg")==0){file = TFile::Open("/afs/naf.desy.de/user/d/dammann/public/Powheg.root","READ");}
    else if(strcmp(generator, "MCatNLO")==0){file = TFile::Open("/afs/naf.desy.de/user/a/aldaya/public/MCatNLO_status3_v20111028.root","READ");}
    else if(strcmp(generator, "MCNLOup")==0){file = TFile::Open("/afs/naf.desy.de/user/a/aldaya/public/MCatNLO_Uncert_Up_status3_v20111028.root","READ");}
    else if(strcmp(generator, "MCNLOdown")==0){file = TFile::Open("/afs/naf.desy.de/user/a/aldaya/public/MCatNLO_Uncert_Down_status3_v20111028.root","READ");}
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
        hist = new TH1D();
        return hist;
      }
      
      TH1* rethist = (TH1*)hist->Clone();
      TH1* weight = (TH1*)file->Get(TString("total_LeptonsPt_").Append(generator));
      
      Double_t wgt = 1.;
      if(!weight){
        std::cerr << "WARNING in GetNloCurve: histogram to extract original number of events could not be opened! No weighting applied!" << endl;
      } else{
	Double_t nevents = weight->GetEntries();
	//
        Double_t crosssection = CalcXSec();
        Double_t binw = hist->GetBinWidth(1);
        wgt = crosssection/nevents/binw;
      }
      rethist->Scale(wgt);
      return rethist;
    }

    std::cerr << "WARNING in GetNloCurve: input file could not been opened! Returning dummy!" << endl;
    hist = new TH1F();
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


// void plotterclass(){ /////just for testing!!!!

//   TFile *f = new TFile("test.root", "RECREATE");

//   Plotter test; 
//   test.setOptions("test", "testname", 10, 0, 10, 1);
//   Plotter test2 = Plotter("test2", "testname2", 10, 0, 10, 1);
//   test.setDataSet("ee");
//   test2.setDataSet("ee");

//   test.fill("ee_200rereco.root", 3,1);
//   test.fill("ee_800prompt.root", 2,1);
//   test.fill("ee_ttbarsignal.root", 2,1);

//   test2.fill("ee_200rereco.root", 5,1);
//   test2.fill("ee_800prompt.root", 6,1);
//   test2.fill("ee_ttbarsignal.root", 2,1);


//   std::cout << "check!" << std::endl;
//   test.write();
//   test2.write();
//   //return 0;

//   f->Close();
//   //delete f;
// }


#endif
