#include <sstream>
#include <string>
#include <iostream>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLegend.h>

int findBinning(TString variable = "topPt", double purstabmin = 0.3, double startvalue = 9.)
{
  // make a nice style
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(10);

  // open file
  TFile* myFile1 = new TFile("analyzeTopQuarks.root", "READ");

  // get the 2D histogram
  TH2F* myHist2d = (TH2F*)myFile1->Get("analyzeTopRecKinematicsMatched/"+variable+"_");
  int xbins = myHist2d->GetNbinsX();
  double xmax = myHist2d->GetXaxis()->GetXmax();
  double xmin = myHist2d->GetXaxis()->GetXmin();

  // initialize vaiables
  int numberOfBins=0;
  vector<double> binvec;

  vector<double> purityvec;
  double purity=0.;
  double puritydenom=0.;

  vector<double> stabilityvec;
  double stability=0.;
  double stabilitydenom=0.;

  double myenum=0.;

  int iSave=0;
  int startbin=(int)((startvalue-xmin)*xbins/(xmax-xmin))+1;
  cout<<"starting with bin number "<<startbin<<"."<<endl;

  // find the desired binning
  for(int i=1; i<=xbins; i++)
    {
      if(!iSave)iSave=i;
      for(int j=0; j<=xbins+1; j++)
      {
	puritydenom+=myHist2d->GetBinContent(j,i);
	stabilitydenom+=myHist2d->GetBinContent(i,j);
      }
      for(int k=iSave; k<=i; k++)
	{
	  for(int l=iSave; l<=i; l++)
	    {
	      myenum+=myHist2d->GetBinContent(l,k);
	    }
	}
      if(puritydenom)purity=myenum/puritydenom;
      if(stabilitydenom)stability=myenum/stabilitydenom;
      myenum=0.;
      if((purity>=purstabmin && stability>=purstabmin) || i==startbin-1 || i==xbins)
	{
	  purityvec.push_back(purity);
	  stabilityvec.push_back(stability);
	  binvec.push_back(myHist2d->GetBinLowEdge(iSave));
	  numberOfBins++;
	  puritydenom=0.;
	  stabilitydenom=0.;
	  iSave=0;
	}
    }
  binvec.push_back(xmax);

  // print the binning
  cout<<numberOfBins<<" bins: {";
  for(int i=0; i<numberOfBins; i++)
    {
      cout<<binvec[i]<<", ";
    }
  cout<<xmax<<"}"<<endl;

  // draw stability & purity histogram with the determined binning
  TCanvas* purstab = new TCanvas("purstab","purstab");
  TH1F* purityhist    = new TH1F("purityhist"   ,"purityhist"   ,numberOfBins, &(binvec.front()));
  TH1F* stabilityhist = new TH1F("stabilityhist","stabilityhist",numberOfBins, &(binvec.front()));

  for(int i=0; i<numberOfBins; i++)
    {
      purityhist->SetBinContent(i+1,purityvec[i]);
      stabilityhist->SetBinContent(i+1,stabilityvec[i]);
    }
  purityhist->SetTitle("");
  TString xtitle = "";
  if(variable.Contains("Pt"))xtitle+="p_{t}";
  else if(variable.Contains("Y"))xtitle+="y";
  else if(variable.Contains("Mass"))xtitle+="m";
  if(variable.Contains("top"))xtitle+="(top)";
  else if(variable.Contains("ttbar"))xtitle+="(ttbar)";
  if(variable.Contains("Pt") || variable.Contains("Mass"))xtitle+=" [GeV]";
  purityhist->GetXaxis()->SetTitle(xtitle);
  purityhist->SetMinimum(0.);
  double max=purityhist->GetMaximum();
  if(stabilityhist->GetMaximum()>max)max=stabilityhist->GetMaximum();
  purityhist->SetMaximum(1.1*max);
  purityhist->SetLineColor(2);
  purityhist->SetLineWidth(2);
  stabilityhist->SetLineColor(4);
  stabilityhist->SetLineStyle(2);
  stabilityhist->SetLineWidth(2);

  purityhist->Draw();
  stabilityhist->Draw("same");

  TLegend* leg=new TLegend(0.4,0.4,0.6,0.6);
  leg->AddEntry(purityhist,   "Purity"    ,"l");
  leg->AddEntry(stabilityhist,"Stability" ,"l");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->Draw("same");

  return 0;
}
