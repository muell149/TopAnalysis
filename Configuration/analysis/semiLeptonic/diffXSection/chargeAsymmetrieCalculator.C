
// ---------description------------------------------------
// --------------------------------------------------------
// this Makro plots pt(muon) for W+jets and Ttbar Monte 
// Carlo sample and calculates the charge assymetrie R
// parameter for W+jets. The obtained Value
// can be used to estimate the W+jets background in Top
// events. The calculation of R is done for each bin. 
// --------------------------------------------------------

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

enum styles {kWjets, kTtbar};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);
void drawcutline(double cutval, double maximum);
void chargeAsymmetrieCalculator()
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
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecWjetsMadgraph7.root     " ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecAllTtbarMcAtNlo7TeV.root" ) );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> eta_, phi_, pt_, etaGen_, phiGen_, ptGen_, etaMuPlus_, phiMuPlus_, ptMuPlus_ , etaMuMinus_, phiMuMinus_, ptMuMinus_;
  std::vector<TH2F*> corrPt_, corrPhi_, corrEta_;

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    eta_   .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/eta"   ) );
    pt_    .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/pt"    ) );
    phi_   .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/phi"   ) );
    etaMuMinus_.push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/etaMuMinus") );
    ptMuMinus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/ptMuMinus" ) );
    phiMuMinus_.push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/phiMuMinus") );
    etaMuPlus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/etaMuPlus" ) );
    ptMuPlus_  .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/ptMuPlus"  ) );
    phiMuPlus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/phiMuPlus" ) );
  }

  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;

  // when using full statistics

  // for current 7TeV Madgraph W+jets sample
  //  lumiweight.push_back(0.1231);

  // for current 7TeV MCAtNlo Ttbar sample
  //  lumiweight.push_back(0.0083);

  // ---
  // do lumiweighting
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
//     eta_[idx]->Scale(lumiweight[idx]);
//     phi_[idx]->Scale(lumiweight[idx]);
//    pt_ [idx]->Scale(lumiweight[idx]);
//     etaMuPlus_[idx]->Scale(lumiweight[idx]);
//     phiMuPlus_[idx]->Scale(lumiweight[idx]);
//    ptMuPlus_ [idx]->Scale(lumiweight[idx]);
//     etaMuMinus_[idx]->Scale(lumiweight[idx]);
//     phiMuMinus_[idx]->Scale(lumiweight[idx]);
 //   ptMuMinus_ [idx]->Scale(lumiweight[idx]);
  }

  // ---
  //    configure histograms
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
//     histogramStyle(*eta_ [idx], idx);
//     histogramStyle(*phi_ [idx], idx);
    histogramStyle(*pt_  [idx], idx);
//     histogramStyle(*etaMuPlus_ [idx], idx);
//     histogramStyle(*phiMuPlus_ [idx], idx);
    histogramStyle(*ptMuPlus_  [idx], idx);
//     histogramStyle(*etaMuMinus_ [idx], idx);
//     histogramStyle(*phiMuMinus_ [idx], idx);
    histogramStyle(*ptMuMinus_  [idx], idx);
  }

  // ---
  //    calculate charge asymmetrie parameter
  // ---

  std::vector<double> parameter_;
  std::vector<double> parameterError_;
  double x=0;
  double y=0;

  std::cout << "----------------------------" << std::endl;
  std::cout << "charge assymmetrie parameter" << std::endl;
  std::cout << "----------------------------" << std::endl;

   for(int i=2; i<= pt_[kWjets]->GetNbinsX(); i++){
     x = ((double)(ptMuMinus_[kWjets]->GetBinContent(i))) /  ((double)(ptMuPlus_[kWjets]->GetBinContent(i)));
     parameter_.push_back( (1.0 + x) / (1.0 -x) );
   }

  // ---
  //    calculate error via gaussian error calculus
  // ---
   for(int i=2; i<= pt_[kWjets]->GetNbinsX(); i++){
     x = 1.0 / ( (double)(ptMuPlus_[kWjets]->GetBinContent(i)) - (double)(ptMuMinus_[kWjets]->GetBinContent(i)) );
     y = ( (double)(ptMuPlus_[kWjets]->GetBinContent(i)) + (double)(ptMuMinus_[kWjets]->GetBinContent(i)) ) / (  ( (double)(ptMuPlus_[kWjets]->GetBinContent(i)) - (double)(ptMuMinus_[kWjets]->GetBinContent(i)) ) * ( (double)(ptMuPlus_[kWjets]->GetBinContent(i)) - (double)(ptMuMinus_[kWjets]->GetBinContent(i)) )  );

     parameterError_.push_back(  sqrt( ((x-y)*(x-y))*(double)(ptMuPlus_[kWjets]->GetBinContent(i)) + ((x+y)*(x+y))*(double)(ptMuMinus_[kWjets]->GetBinContent(i)) )  );
     std::cout << "bin " << i << ": " << parameter_[i-2] << " +/- " << parameterError_[i-2] << std::endl;
   }

  // create histogram with assymetrie parameter as clone
  TH1F *asymmetrieParameter= (TH1F*) pt_[0]->Clone();

  // use calculated entries
  for(int i=2; i<= pt_[0]->GetNbinsX(); i++){
    asymmetrieParameter->SetBinContent( i, parameter_[i-2] );
    asymmetrieParameter->SetBinError  ( i, parameterError_[i-2] );
    }




  // ---
  //    create legends 
  // ---

  // create a legend for Wjets
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("W+jets (MADGRAPH), #sqrt{s}=7 TeV & 406 pb^{-1}");
  leg0->AddEntry( pt_[kWjets]        , "all"      , "PL");
  leg0->AddEntry(ptMuPlus_  [kWjets] , "#mu^{+}"  , "PL");
  leg0->AddEntry(ptMuMinus_ [kWjets] , "#mu^{-}"  , "PL");

  // create a legend for Ttbar
  TLegend *leg1 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Ttbar (MC@NLO), #sqrt{s}=7 TeV & 6021 pb^{-1}");
  leg1->AddEntry( pt_[kTtbar]        , "all"      , "PL");
  leg1->AddEntry(ptMuPlus_  [kTtbar] , "#mu^{+}"  , "PL");
  leg1->AddEntry(ptMuMinus_ [kTtbar] , "#mu^{-}"  , "PL");

  // create a legend for assymetrie parameter
  TLegend *leg2 = new TLegend(0.24, 0.75, 0.80, 0.87);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetHeader("W+jets @ #sqrt{s}=7 TeV for  406 pb^{-1}");
  leg2->AddEntry(asymmetrieParameter, "asymmetrie parameter R"  , "PL");

  // ---
  //    do the printing for pt_ (Wjets)
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // draw canvas
  canv0->cd(0);
  canv0->SetTitle("pt (tight #Mu) for Wjets");
  axesStyle(*pt_ [kWjets], "p_{t} ( tight #mu ) [GeV]", "events");
  pt_ [kWjets]->SetMinimum(0.);
  pt_ [kWjets]->SetMaximum( 1.4*pt_ [kWjets]->GetMaximum() );
  pt_ [kWjets]->Draw("");
  pt_ [kWjets]->Draw("esame");
  ptMuPlus_ [kWjets]->SetLineColor (kBlue);
  ptMuPlus_ [kWjets]->SetLineStyle(2);
  ptMuPlus_ [kWjets]->Draw("same");
  ptMuPlus_ [kWjets]->Draw("esame");
  ptMuMinus_[kWjets]->SetLineColor (kRed);
  ptMuMinus_[kWjets]->SetLineStyle(2);
  ptMuMinus_[kWjets]->Draw("same");
  ptMuMinus_[kWjets]->Draw("esame");
  leg0              ->Draw("same");

  // ---
  //    do the printing for pt_ (ttbar)
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetTitle("pt (tight #Mu) for Ttbar");
  axesStyle(*pt_ [kTtbar], "p_{t} ( tight #mu ) [GeV]", "events");
  pt_ [kTtbar]->SetMinimum(0.);
  pt_ [kTtbar]->SetMaximum( 1.4*pt_ [kTtbar]->GetMaximum() );
  pt_ [kTtbar]->Draw("");
  ptMuPlus_ [kTtbar]->SetLineColor (kBlue);
  ptMuPlus_ [kTtbar]->SetLineStyle(2);
  ptMuPlus_ [kTtbar]->Draw("same");
  ptMuMinus_[kTtbar]->SetLineColor (kRed);
  ptMuMinus_[kTtbar]->SetLineStyle(2);
  ptMuMinus_[kTtbar]->Draw("same");
  leg1              ->Draw("same");

  // ---
  //    do the printing for asymmetrieParameter
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetTitle("asymmetrie parameter");
  axesStyle(*asymmetrieParameter, "p_{t} ( tight #mu ) [GeV]", "R=#frac{N_{W}^{+} + N_{W}^{-}}{N_{W}^{+} - N_{W}^{-}}");
  asymmetrieParameter->SetMinimum( 0.);
  asymmetrieParameter->SetMaximum( 40. );
  asymmetrieParameter->SetMarkerStyle(20);
  asymmetrieParameter->SetMarkerSize(1.2);
  asymmetrieParameter->GetYaxis()->SetTitleSize(0.05);
  asymmetrieParameter->GetYaxis()->SetTitleOffset(  1.5);
  asymmetrieParameter->Draw("");
  leg2               ->Draw("same");

  // ---
  // saving
  // ---

  std::cout << "use root -l chargeAssymmetrieCalculator.C+ > parameter.txt to save output in file" << std::endl;  

  // ps

  canv0->Print("./diffXSecFromSignal/plots/chargeAsymmetrieWjetsMadgraph7TeV.ps(" );
  canv1->Print("./diffXSecFromSignal/plots/chargeAsymmetrieWjetsMadgraph7TeV.ps"  );
  canv2->Print("./diffXSecFromSignal/plots/chargeAsymmetrieWjetsMadgraph7TeV.ps)" );

  // png
  canv0->Print("./diffXSecFromSignal/plots/ptMuonChargeWjetsMadgraph7TeV.png");
  canv1->Print("./diffXSecFromSignal/plots/ptMuonChargeTtbarMcAtNlo7TeV.png" );
  canv2->Print("./diffXSecFromSignal/plots/chargeAsymmetrieParameter.png"    );
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
