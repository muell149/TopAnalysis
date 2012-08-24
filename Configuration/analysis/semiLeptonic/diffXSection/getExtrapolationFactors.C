#include "basicFunctions.h"

TCanvas* getExtrapolFak(TString plotName, TString label, int verbose, TString outputFileFull, TString outputFileParton, TString outputFileHadron){

  // ============================ 
  //  Set Root Style
  // ============================

  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  TGaxis::SetMaxDigits(2);
  myStyle.cd();
  gROOT->SetStyle("HHStyle");
  
  // open files
  TFile* fileFull   = TFile::Open(outputFileFull  , "READ");
  TFile* fileParton = TFile::Open(outputFileParton, "READ");
  TFile* fileHadron = TFile::Open(outputFileHadron, "READ");
  // dont associate new objects with file to be able to close it in the end
  gROOT->cd();
  // get canvas^3 for chosen cross section
  TCanvas* canvasFull   = (TCanvas*)(fileFull  ->Get("xSec/sysNo/"+plotName+"Norm")->Clone());
  TCanvas* canvasParton = (TCanvas*)(fileParton->Get("xSec/sysNo/"+plotName+"Norm")->Clone());
  TCanvas* canvasHadron = (TCanvas*)(fileHadron->Get("xSec/sysNo/"+plotName+"Norm")->Clone());
  
  // get data histos 
  TH1F* dataFull      = killEmptyBins((TH1F*)((canvasFull  ->GetPrimitive(plotName+"kData"))->Clone()));
  TH1F* dataRawParton = killEmptyBins((TH1F*)((canvasParton->GetPrimitive(plotName+"kData"))->Clone()));
  TH1F* dataRawHadron = killEmptyBins((TH1F*)((canvasHadron->GetPrimitive(plotName+"kData"))->Clone()));
  
  // use always the correct PS definition:
  //     hadron level for b-quarks and lepton
  //     parton level for all others
  TH1F* dataPS = ( (plotName.Contains("bq")||plotName.Contains("lep")) ? (TH1F*)dataRawHadron->Clone() : (TH1F*)dataRawParton->Clone() );

  // adjust style and labels
  TString PSlabel = ( (plotName.Contains("bq")||plotName.Contains("lep")) ? "hadron" : "parton" );
  int color = kBlue;
  if(PSlabel=="hadron") color-=4;
  dataPS->SetLineColor(color);
  dataPS->SetMarkerColor(color);
  histogramStyle(*dataFull, kData);
  dataFull->SetLineWidth(3);
  dataPS->SetLineWidth(3);
  if     (plotName=="lepPt") dataFull->GetXaxis()->SetRangeUser(0.,199.);
  else if(plotName=="bqPt" ) dataFull->GetXaxis()->SetRangeUser(0.,399.);
  else                       setXAxisRange(dataFull, plotName);
  double max=dataFull->GetMaximum();
  if(max<dataPS->GetMaximum()) max=dataPS->GetMaximum();
  dataFull->SetMaximum(1.3*max);
  dataFull->GetXaxis()->SetTitle(xSecLabelName(plotName));
  TString label2=label;
  TString label3="";
  if(label.Contains("/[GeV]")){
    label2.ReplaceAll("/[GeV]","");
    label3=" / [GeV]";
  }
  label2.ReplaceAll("/ ","");
  dataFull->GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d#sigma}{d"+label2+"}"+label3);
  dataFull->GetYaxis()->SetNoExponent(false);
  dataFull->GetXaxis()->SetNoExponent(true);
  dataFull->SetTitle("");

  // create legend
  TLegend *leg0 = new TLegend(0.65, 0.762, 0.95, 0.89);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("phase spaces");
  leg0->AddEntry(dataFull, "extrapol. parton lv","L");
  leg0->AddEntry(dataPS  , "restricted "+PSlabel+" lv","L");

  // create label
  TPaveText *headerlabel = new TPaveText();
  headerlabel -> SetX1NDC(gStyle->GetPadLeftMargin());
  headerlabel -> SetY1NDC(1.0-gStyle->GetPadTopMargin());
  headerlabel -> SetX2NDC(1.0-gStyle->GetPadRightMargin());
  headerlabel -> SetY2NDC(1.0);
  headerlabel -> SetTextFont(42);
  headerlabel -> AddText("comparing 2011 data results");
  headerlabel->SetFillStyle(0);
  headerlabel->SetBorderSize(0);
  headerlabel->SetTextSize(0.04);
  headerlabel->SetTextAlign(32);

  // create extrapolation factor / ratio canvas
  std::vector<TCanvas*> plotCanvas_;
  addCanvas(plotCanvas_);
  plotCanvas_[0]->cd();
  plotCanvas_[0]->Draw();
  dataFull->Draw("hist");
  dataPS->Draw("hist same");
  leg0->Draw("same");
  headerlabel->Draw("same");
  DrawDecayChLabel("e/#mu + Jets Combined");
  drawRatio(dataPS, dataFull, 0., 2.4, myStyle, verbose, std::vector<double>(0), PSlabel+" PS", "extrapolated", "hist", kBlack);

  // close files
  fileFull  ->Close();
  fileParton->Close();
  fileHadron->Close();
  
  // return
  return plotCanvas_[0];
}

void getExtrapolationFactors(int verbose=0){

  // Defintion of variables and labels (centrally defined in basicFunction.h)
  std::vector<TString> xSecVariables_, xSecLabel_;
  xSecVariables_.insert(xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString));
  xSecLabel_    .insert(xSecLabel_    .begin(), xSecLabel    , xSecLabel     + sizeof(xSecLabel    )/sizeof(TString) );     
  // get correct names
  TString outputFolder="./diffXSecFromSignal/plots/combined/2011/";
  
  TString outputFileFull="diffXSecTopSemiLepParton.root";
  TString outputFileParton="diffXSecTopSemiLepPartonPhaseSpace.root";
  TString outputFileHadron="diffXSecTopSemiLepHadronPhaseSpace.root";

  // loop variables
  for(unsigned int i=0; i<xSecVariables_.size(); ++i){
    TString variable=xSecVariables_[i];
    // create ratio canvas
    TCanvas*canv=getExtrapolFak(variable, xSecLabel_[i], verbose, outputFileFull, outputFileParton, outputFileHadron);
    canv->SetName (variable);
    canv->SetTitle(variable);
    // save ratio plots
    int initialIgnoreLevel=gErrorIgnoreLevel;
    if(verbose==0) gErrorIgnoreLevel=kWarning;
    canv->Print(outputFolder+"extrapolationFactor"+variable+"NormCombined.eps");
    canv->Print(outputFolder+"extrapolationFactor"+variable+"NormCombined.png");
    if(i==0) canv->Print(outputFolder+"extrapolationFactorNormCombined.pdf(");
    else if (i==xSecVariables_.size()-1) canv->Print(outputFolder+"extrapolationFactorNormCombined.pdf)");
    else canv->Print(outputFolder+"extrapolationFactorNormCombined.pdf");
    gErrorIgnoreLevel=initialIgnoreLevel;
    saveToRootFile(outputFileFull, canv, true, verbose,"extrapolationFactor");
    // delete ratio canvas
    delete canv;
  }
}
