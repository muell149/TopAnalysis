#include "basicFunctions.h"



void createNNLOplot(TString outputRootFile="kidonakisNNLO.root")
{
  gStyle->SetOptStat(0);
  // list of variables
  std::vector<TString> xSecVariables_, xSecLabel_;
  TString xSecVariables[] ={"topPt", "topY"};
  xSecVariables_ .insert( xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString) );
  
  // gotta get em all
  for(unsigned var=0; var<xSecVariables_.size(); ++var){
    // get raw nnlo points
    TString variable=xSecVariables_[var];
    TGraph * rawHist = new TGraph(variable+"normalNNLO7lhc173m.dat");
    // convert to TH1F*
    double *Xvalues = rawHist->GetX();
    int Nbins=rawHist->GetN();
    double *Yvalues = rawHist->GetY();
    TH1F* hist = new TH1F ( variable, variable, Nbins, Xvalues); 
    for(int bin=1; bin<=Nbins; ++bin){
      std::cout << "bin " << bin;
      std::cout << "(<x>=" << hist->GetBinCenter(bin);
      std::cout << "): " << Yvalues[bin-1] << std::endl;
      hist->SetBinContent(bin, Yvalues[bin-1]);
    }
    // ensure normalization
    hist->Scale(1./(hist->Integral(0.,hist->GetNbinsX()+1)));
    // divide by binwidth
    double width=1.;
    if(xSecVariables_[var]=="topPt") width=4.;
    if(xSecVariables_[var]=="topY" ) width=0.1;   
    //    for(int bin=1; bin<=Nbins; ++bin){
    //      hist->SetBinContent(bin, hist->GetBinContent(bin)/hist->GetBinWidth(bin));
    //}
    hist->Scale(1./width);
    // styling
    hist->GetXaxis()->SetRange(0, Nbins-1);
    hist->SetMarkerColor(kMagenta);
    hist->SetMarkerStyle(24);
    // print to canvas
    TCanvas *canv = new TCanvas("canv","canv",800,600);
    canv->cd();
    hist->Draw("p");
    // save in png and rootfile
    canv->SaveAs(variable+"Norm_kidonakis.png");
    TH1F* out=(TH1F*)hist->Clone();
    saveToRootFile(outputRootFile, hist, true, 0,"");
  }
}
