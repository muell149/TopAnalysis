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

int findBinning(TString variable = "topPt", double purstabmin = 0.3, double startvalue = 9., bool plotEfficiency = true)
{
  // make a nice style
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  // open file
  TFile* myFile1 = new TFile("/afs/desy.de/user/m/mgoerner/public/analysisRootFilesWithKinFit/muonDiffXSecSigMadD6TFall10PF.root", "READ");

  // get the 2D histogram
  // x-Axis should be generated value, y-Axis should be reconstructed value
  TH2F* myHist2d = (TH2F*)myFile1->Get("analyzeTopRecoKinematicsKinFitMatched/"+variable+"_");
  int xbins = myHist2d->GetNbinsX();
  double xmax = myHist2d->GetXaxis()->GetXmax();
  double xmin = myHist2d->GetXaxis()->GetXmin();

  // initialize variables
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
  // loop over bins of one axis of 2D histogram
  // (need to be the same binning for x and y anyway!)
  for(int i=1; i<=xbins; i++)
    {
      // save bin number which will be the lower edge of the final bin
      if(!iSave)iSave=i;
      // loop over bins of the other axis of 2D histogram
      for(int j=0; j<=xbins+1; j++)
      {
	// denominator for purity (number of reconstructed events)
	puritydenom+=myHist2d->GetBinContent(j,i);
	// denominator for stability (number of generated events)
	stabilitydenom+=myHist2d->GetBinContent(i,j);
      }
      // loop over bins starting from lower edge of the final bin
      for(int k=iSave; k<=i; k++)
	{
	  // loop over bins starting from lower edge of the final bin
	  for(int l=iSave; l<=i; l++)
	    {
	      // enumerator
	      myenum+=myHist2d->GetBinContent(l,k);
	    }
	}
      // calculate purity (avoid dividing by zero)
      if(puritydenom)purity=myenum/puritydenom;
      // calculate stability (avoid dividing by zero)
      if(stabilitydenom)stability=myenum/stabilitydenom;
      myenum=0.;
      // find upper edge of final bin
      if((purity>=purstabmin && stability>=purstabmin) || i==startbin-1 || i==xbins)
	{
	  // write results to vector
	  purityvec.push_back(purity);
	  stabilityvec.push_back(stability);
	  binvec.push_back(myHist2d->GetBinLowEdge(iSave));
	  // count bins
	  numberOfBins++;
	  // reset variables
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
  TCanvas* purstab = new TCanvas("purstab","purstab",600,600);
  gPad->SetBottomMargin(0.19);
  purstab->cd();
  TH1F* purityhist    = new TH1F("purityhist"   ,"purityhist"   ,numberOfBins, &(binvec.front()));
  TH1F* stabilityhist = new TH1F("stabilityhist","stabilityhist",numberOfBins, &(binvec.front()));

  // get histogram of generated quantity
  TH1F* genHist = (TH1F*)myFile1->Get("analyzeTopGenLevelKinematics/"+variable);
  // rebin histogram of generated quantity
  genHist = (TH1F*)genHist->Rebin(binvec.size()-1, genHist->GetName(), &(binvec.front()));
  // get histogram of reconstructed quantity
  TH1F* effHist = (TH1F*)((TH1F*)myFile1->Get("analyzeTopRecoKinematicsKinFit/"+variable))->Clone();
  // rebin histogram of reconstructed quantity
  effHist = (TH1F*)effHist->Rebin(binvec.size()-1, effHist->GetName(), &(binvec.front()));
  // calculate efficiency histogram
  effHist->Divide(genHist);

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
  if(variable=="topWAngle")xtitle="Angle(top,W)";
  purityhist->GetXaxis()->SetTitle(xtitle);

  purityhist->GetXaxis()->SetTitleSize  ( 0.07);
  purityhist->GetXaxis()->SetTitleColor (    1);
  purityhist->GetXaxis()->SetTitleOffset(  0.95);
  purityhist->GetXaxis()->SetTitleFont  (   62);
  purityhist->GetXaxis()->SetLabelSize  ( 0.07);
  purityhist->GetXaxis()->SetLabelFont  (   62);
  purityhist->GetXaxis()->SetNdivisions (  505);
  
  purityhist->GetYaxis()->SetTitleSize  ( 0.07);
  purityhist->GetYaxis()->SetTitleColor (    1);
  purityhist->GetYaxis()->SetTitleOffset(  1.0);
  purityhist->GetYaxis()->SetTitleFont  (   62);
  purityhist->GetYaxis()->SetLabelSize  ( 0.07);
  purityhist->GetYaxis()->SetLabelFont  (   62);
  purityhist->GetYaxis()->SetNdivisions (  505);

  purityhist->SetMinimum(0.);
  double max=purityhist->GetMaximum();
  if(stabilityhist->GetMaximum()>max)max=stabilityhist->GetMaximum();
  purityhist->SetMaximum(1.1*max);
  purityhist->SetLineColor(2);
  purityhist->SetLineWidth(4);
  stabilityhist->SetLineColor(4);
  stabilityhist->SetLineStyle(2);
  stabilityhist->SetLineWidth(4);
  effHist->SetLineColor(1);
  effHist->SetLineStyle(1);
  effHist->SetLineWidth(4);

  purityhist->Draw();
  stabilityhist->Draw("same");
  if(plotEfficiency)effHist->Draw("same");


  double legEdge = 0.4;
  if(plotEfficiency)legEdge = effHist->GetMinimum();
  TLegend* leg=new TLegend(0.4,legEdge,0.6,legEdge+0.2);
  leg->SetTextSize(0.07);
  leg->AddEntry(purityhist,   "Purity"    ,"l");
  leg->AddEntry(stabilityhist,"Stability" ,"l");
  if(plotEfficiency)leg->AddEntry(effHist,"Efficiency","l");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->Draw("same");

  return 0;
}
