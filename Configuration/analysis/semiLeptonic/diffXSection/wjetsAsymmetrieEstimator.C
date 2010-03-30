
// ---------description------------------------------------------
// --------------------------------------------------------------
// this Makro estimates the fraction of W+jets from (pseudo) data
// with errors derived from statistical errors via gaussian error calculus
// using the charge asymmetrie parameter and compares it to the 
// (gen-based) real W+jets fraction. additionally the pt(muon) is 
// plotted for positive and negative charged muons.
// --------------------------------------------------------------

#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <THStack.h>
#include <TLine.h>
#include <TStyle.h>

enum styles {kPseudo50, kWjetsPseudo50};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);
void drawcutline(double cutval, double maximum);
void wjetsAsymmetrieEstimator()
{
  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetErrorX(0); 

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  //  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecWjetsMadgraph7.root " ) );
  files_.push_back(new TFile("./diffXSecFromSignal/pseudoData7TeV50pb.root     " ) );
  files_.push_back(new TFile("./diffXSecFromSignal//pseudoData/pseudoWjets.root" ) );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> pt_, ptMuPlus_, ptMuMinus_;

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    pt_        .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/pt"        ) );
    ptMuMinus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/ptMuMinus" ) );
    ptMuPlus_  .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/ptMuPlus"  ) );
   }

  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;

  // for Pseudo datas
  lumiweight.push_back(1.0);
  lumiweight.push_back(1.0);

  // ---
  // do lumiweighting
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    pt_ [idx]->Scale(lumiweight[idx]);
    ptMuPlus_ [idx]->Scale(lumiweight[idx]);
    ptMuMinus_ [idx]->Scale(lumiweight[idx]);
  }

  // ---
  //    collect charge asymmetrie parameter
  // ---

  std::vector<double> parameter_;
  parameter_.push_back(2.46218);
  parameter_.push_back(3.02667);
  parameter_.push_back(7.84615);
  parameter_.push_back(9.95238);
  parameter_.push_back(20.5556);

  std::vector<double> parameterError_;
  parameterError_.push_back(0.323641);
  parameterError_.push_back(0.573873);
  parameterError_.push_back(4.27506 );
  parameterError_.push_back(6.81675 );
  parameterError_.push_back(31.0283 );

  // create histogram with Wjets-estimation from charge assymetrie method
  TH1F *ptWjetsEstimation= (TH1F*) pt_[0]->Clone();

  // calculate entries
  for(int i=2; i<= pt_[0]->GetNbinsX(); i++){
    ptWjetsEstimation->SetBinContent(  i, parameter_[i-2]* ((double)ptMuPlus_[kPseudo50]->GetBinContent(i) - (double)ptMuMinus_[kPseudo50]->GetBinContent(i))  );
    }

  // ---
  //    calculate error via gaussian error calculus
  // ---

  std::vector<double> estimationError_;
  double x=0;
  double y=0;
 
  std::cout << "----------------------------" << std::endl;
  std::cout << "W+jets background estimation" << std::endl;
  std::cout << "----------------------------" << std::endl;

  for(int i=2; i<= ptWjetsEstimation->GetNbinsX(); i++){
    x = (double)(ptMuPlus_ [kPseudo50]->GetBinContent(i));
    y = (double)(ptMuMinus_[kPseudo50]->GetBinContent(i));
    estimationError_.push_back(  sqrt( (x-y)*(x-y)*parameterError_[i-2]*parameterError_[i-2] + parameter_[i-2]*parameter_[i-2]*(x+y) )  );
    
    std::cout << "bin " << i << ": " <<  ptWjetsEstimation->GetBinContent(i) << " +/- " << estimationError_[i-2] << std::endl;
    ptWjetsEstimation->SetBinError( i, estimationError_[i-2] );
   }


  // ---
  //    configure histograms
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    histogramStyle(*pt_  [idx], idx);
    histogramStyle(*ptMuPlus_  [idx], idx);
    histogramStyle(*ptMuMinus_  [idx], idx);
  }

  histogramStyle(*ptWjetsEstimation, 0);

  // ---
  //    create legends 
  // ---

  // create a legend for estimation
  TLegend *leg0 = new TLegend(0.30, 0.61, 0.90, 0.86);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("50pb^{-1} @ #sqrt{s}=7TeV");
  leg0->AddEntry( pt_[kPseudo50]     , "pseudo data"             , "PL");
  leg0->AddEntry( pt_[kWjetsPseudo50], "real W+jets events"      , "PL");
  leg0->AddEntry( ptWjetsEstimation  , "estimated W+jets events" , "PL");

  // create a legend for pseudo data
  TLegend *leg1 = new TLegend(0.42, 0.62, 1.00, 0.83);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("50pb^{-1} @ #sqrt{s}=7TeV");
  leg1->AddEntry( pt_[kPseudo50]       , "pseudo data all"      , "PL");
  leg1->AddEntry( ptMuPlus_ [kPseudo50], "pseudo data #mu^{+}"  , "PL");
  leg1->AddEntry( ptMuMinus_[kPseudo50], "pseudo data #mu^{-}"  , "PL");

  // ---
  //    do the printing for pt_ (W-estimation via method and real fraction)
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // draw canvas
  canv0->cd(0);
  canv0->SetTitle("pt (tight #Mu) Estimation Quality");
  axesStyle(*pt_ [kWjetsPseudo50], "p_{t} ( tight #mu ) [GeV]", "events");
  pt_ [kWjetsPseudo50]->SetMinimum(0.);
  pt_ [kWjetsPseudo50]->SetMaximum( 400. );
  pt_ [kWjetsPseudo50]->SetLineColor (kBlue);
  pt_ [kWjetsPseudo50]->SetLineStyle(2);
  pt_ [kWjetsPseudo50]->Draw("");
  pt_ [kPseudo50]->SetMarkerStyle(22);
  pt_ [kPseudo50]->SetMarkerSize(1.2);
  pt_ [kPseudo50]->Draw("same");
  ptWjetsEstimation->SetLineColor (kRed);
  ptWjetsEstimation->SetMarkerColor(kRed);
  ptWjetsEstimation->SetMarkerStyle(22);
  ptWjetsEstimation->SetMarkerSize(1.2);
  ptWjetsEstimation->Draw("same");
  leg0             ->Draw("same");


  // ---
  //    do the printing for pt_ (pseudo data)
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetTitle("pt (tight #Mu) Pseudo Data");
  axesStyle(*pt_ [kPseudo50], "p_{t} ( tight #mu ) [GeV]", "events");
  pt_ [kPseudo50]->SetMinimum(0.);
  pt_ [kPseudo50]->SetMaximum( 200 );
  pt_ [kPseudo50]->SetMarkerStyle(22);
  pt_ [kPseudo50]->SetMarkerSize(1.2);
  pt_ [kPseudo50]->Draw("");
  pt_ [kPseudo50]->Draw("esame");
  ptMuPlus_  [kPseudo50]->Draw("esame");
  ptMuMinus_ [kPseudo50]->Draw("esame");
  ptMuPlus_  [kPseudo50]->SetLineColor (kBlue);
  ptMuPlus_  [kPseudo50]->SetLineStyle(2);
  ptMuPlus_  [kPseudo50]->Draw("same");
  ptMuMinus_ [kPseudo50]->SetLineColor (kRed);
  ptMuMinus_ [kPseudo50]->SetLineStyle(2);
  ptMuMinus_ [kPseudo50]->Draw("same");
  leg1                  ->Draw("same");


  // ---
  // saving
  // ---

  // ps

  canv0->Print("./diffXSecFromSignal/plots/chargeAsymmetrieEstimation50pbAt7TeV.ps(" );
  canv1->Print("./diffXSecFromSignal/plots/chargeAsymmetrieEstimation50pbAt7TeV.ps)" );
  
  // png
  canv0->Print("./diffXSecFromSignal/plots/ptMuonChargeEstimationWjets.png");
  canv1->Print("./diffXSecFromSignal/plots/ptMuonChargePseudoData50pb.png");
}

void canvasStyle(TCanvas& canv) 
{
  canv.SetFillStyle   ( 4000 );
  canv.SetLeftMargin  ( 0.20 );
  canv.SetRightMargin ( 0.05 );
  canv.SetBottomMargin( 0.15 );
  canv.SetTopMargin   ( 0.05 );
}

void histogramStyle(TH1& hist, unsigned int style) 
{
  // pre-defined line style
  std::vector<int> color;
  color.push_back( kBlack ); 
  color.push_back( kBlack ); 

  // pre-defined marker style
  std::vector<int> marker;
  marker.push_back( 20);

  // set line width
  
  hist.SetLineWidth(3);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color[style]);
  hist.SetMarkerColor(color[style]);
  
}

void drawcutline(double cutval, double maximum)
{
  TLine *cut = new TLine();
  cut->SetLineWidth(3);
  cut->SetLineColor(28);
  cut->DrawLine(cutval,0.,cutval,maximum);
}

void axesStyle(TH1& hist, const char* titleX, const char* titleY) 
{
  hist.SetTitle("");

  hist.GetXaxis()->SetTitle(titleX);
  hist.GetXaxis()->CenterTitle();
  hist.GetXaxis()->SetTitleSize  ( 0.06);
  hist.GetXaxis()->SetTitleColor (    1);
  hist.GetXaxis()->SetTitleOffset(  1.0);
  hist.GetXaxis()->SetTitleFont  (   62);
  hist.GetXaxis()->SetLabelSize  ( 0.05);
  hist.GetXaxis()->SetLabelFont  (   62);
  hist.GetXaxis()->SetNdivisions (  505);
  
  hist.GetYaxis()->SetTitle(titleY);
  hist.GetYaxis()->SetTitleSize  ( 0.07);
  hist.GetYaxis()->SetTitleColor (    1);
  hist.GetYaxis()->SetTitleOffset(  1.2);
  hist.GetYaxis()->SetTitleFont  (   62);
  hist.GetYaxis()->SetLabelSize  ( 0.04);
  hist.GetYaxis()->SetLabelFont  (   62);
  hist.GetYaxis()->CenterTitle   ( true);
}
