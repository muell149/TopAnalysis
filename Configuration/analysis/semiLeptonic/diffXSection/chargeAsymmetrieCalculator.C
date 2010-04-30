
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
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void drawcutline(double cutval, double maximum);

void chargeAsymmetrieCalculator()
{
  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetErrorX(0); 


  // choose jet multiplicity you want to see: "Njets1" / "Njets2" / "Njets3" / "Njets4"
  TString jetMultiplicity = "Njets4";
  // choose whether you want to scale to certain luminosity
  bool useLumiWeight = false;
  // choose whether you want to save every plot as png and all within one ps file
  bool save = true;
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/chargeAsymmetrie/";

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecWjetsMadgraph7TeV.root              " ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecRecoAllTtbarMcAtNlo7TeVsummer09.root" ) );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> eta_, phi_, pt_, etaMuPlus_, phiMuPlus_, ptMuPlus_ , etaMuMinus_, phiMuMinus_, ptMuMinus_;

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    eta_       .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/eta" ) );
    pt_        .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/pt"  ) );
    phi_       .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/phi" ) );
    etaMuMinus_.push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/etaMinus") );
    ptMuMinus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/ptMinus" ) );
    phiMuMinus_.push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/phiMinus") );
    etaMuPlus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/etaPlus" ) );
    ptMuPlus_  .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/ptPlus"  ) );
    phiMuPlus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/phiPlus" ) );
  }

  // ---
  // define weights concerning luminosity
  // ---

  std::vector<double> lumiweight;
  // when using full statistics

  // for current 7TeV Madgraph W+jets sample
  lumiweight.push_back(0.13904207);

  // for current 7TeV MCAtNlo Ttbar sample
  lumiweight.push_back(0.00831910);

  // ---
  // do lumiweighting
  // ---

  if(useLumiWeight){
    for(unsigned int idx=0; idx<files_.size(); ++idx) {
      eta_[idx]       ->Scale(lumiweight[idx]);
      phi_[idx]       ->Scale(lumiweight[idx]);
      pt_ [idx]       ->Scale(lumiweight[idx]);
      etaMuPlus_ [idx]->Scale(lumiweight[idx]);
      phiMuPlus_ [idx]->Scale(lumiweight[idx]);
      ptMuPlus_  [idx]->Scale(lumiweight[idx]);
      etaMuMinus_[idx]->Scale(lumiweight[idx]);
      phiMuMinus_[idx]->Scale(lumiweight[idx]);
      ptMuMinus_ [idx]->Scale(lumiweight[idx]);
    }
  }

  // ---
  //    calculate charge asymmetrie parameter
  // ---

  std::vector<double> parameter_;
  std::vector<double> parameterError_;
  double x=0;
  double y=0;

  std::cout << "----------------------------"             << std::endl;
  std::cout << "charge assymmetrie parameter"             << std::endl;
  std::cout << "--------- "+jetMultiplicity+" ----------" << std::endl;
  std::cout << "----------------------------"             << std::endl;
   for(int i=2; i<= pt_[kWjets]->GetNbinsX(); i++){
     x = ((double)(ptMuMinus_[kWjets]->GetBinContent(i))) /  ((double)(ptMuPlus_[kWjets]->GetBinContent(i)));
     parameter_.push_back( (1.0 + x) / (1.0 -x) );
   }
  std::cout << "----------------------------"             << std::endl;
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
  leg0->SetHeader("W+jets (MAD), 406 pb^{-1}");
  leg0->AddEntry( pt_[kWjets]        , "all"      , "PL");
  leg0->AddEntry(ptMuPlus_  [kWjets] , "#mu^{+}"  , "PL");
  leg0->AddEntry(ptMuMinus_ [kWjets] , "#mu^{-}"  , "PL");

  // create a legend for Ttbar
  TLegend *leg1 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Ttbar (MC@NLO), 6021 pb^{-1}");
  leg1->AddEntry( pt_[kTtbar]        , "all"      , "PL");
  leg1->AddEntry(ptMuPlus_  [kTtbar] , "#mu^{+}"  , "PL");
  leg1->AddEntry(ptMuMinus_ [kTtbar] , "#mu^{-}"  , "PL");

  // create a legend for assymetrie parameter
  TLegend *leg2 = new TLegend(0.25, 0.67, 0.81, 0.79);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetHeader("W+jets(MAD), 406 pb^{-1}");
  leg2->AddEntry(asymmetrieParameter, "R_{charge asymmetrie}" , "PL");

  // create a legend for used jetCut
  TLegend *leg3 = new TLegend(0.23, 0.85, 0.62, 0.97);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  leg3->SetHeader("selection: "+jetMultiplicity+"+");

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<=2; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ---
  //    do the printing for pt, ptMuPlus and ptMuMinus (Wjets)
  // ---
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetTitle("ptMuChargeWjets"+jetMultiplicity);
  axesStyle(*pt_ [kWjets], "p_{t} ( tight #mu ) [GeV]", "events", 0, 1.4*pt_ [kWjets]->GetMaximum(), 0.06, 1.5 );
  histogramStyle(*pt_       [kWjets], kBlack, 1, 20);
  histogramStyle(*ptMuPlus_ [kWjets], kBlue , 2, 20);
  histogramStyle(*ptMuMinus_[kWjets], kRed  , 2, 20);
  pt_ [kWjets]->Draw("");
  pt_ [kWjets]->Draw("esame");
  ptMuPlus_ [kWjets]->Draw("same");
  ptMuPlus_ [kWjets]->Draw("esame");
  ptMuMinus_[kWjets]->Draw("same");
  ptMuMinus_[kWjets]->Draw("esame");
  leg0              ->Draw("same");
  leg3              ->Draw("same");

  // ---
  //    do the printing for pt_ (ttbar)
  // ---
  MyCanvas[1]->cd(0);
  MyCanvas[1]->SetTitle("ptMuChargeAllTtbar"+jetMultiplicity);
  axesStyle(*pt_ [kTtbar], "p_{t} ( tight #mu ) [GeV]", "events", 0, 1.4*pt_ [kTtbar]->GetMaximum(), 0.06, 1.5);
  histogramStyle(*pt_       [kTtbar], kBlack, 1, 20);
  histogramStyle(*ptMuPlus_ [kTtbar], kBlue , 2, 20);
  histogramStyle(*ptMuMinus_[kTtbar], kRed  , 2, 20);
  pt_ [kTtbar]->Draw("");
  ptMuPlus_ [kTtbar]->Draw("same");
  ptMuMinus_[kTtbar]->Draw("same");
  leg1              ->Draw("same");
  leg3              ->Draw("same");

  // ---
  //    do the printing for asymmetrieParameter
  // ---
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetTitle("chargeAsymmetrieParameterWjets"+jetMultiplicity);
  axesStyle(*asymmetrieParameter, "p_{t} ( tight #mu ) [GeV]", "R=#frac{N_{W}^{+} + N_{W}^{-}}{N_{W}^{+} - N_{W}^{-}}", 0, 40, 0.05, 1.5);
  histogramStyle(*asymmetrieParameter, kBlack, 1, 20, 1.2);
  asymmetrieParameter->Draw("");
  leg2               ->Draw("same");
  leg3              ->Draw("same");

  // ---
  // saving
  // ---
  
  if(save){
    // ps
    MyCanvas[0]->Print(saveTo+"chargeAsymmetrieParameter"+jetMultiplicity+".ps("  );
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+"chargeAsymmetrieParameter"+jetMultiplicity+".ps"  );   
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+"chargeAsymmetrieParameter"+jetMultiplicity+".ps)"  );
  
    // png
    for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
      MyCanvas[idx]->Print(saveTo+(TString)(MyCanvas[idx]->GetTitle())+".png"  );      
    }
  }
}

void canvasStyle(TCanvas& canv) 
{
  canv.SetFillStyle   ( 4000 );
  canv.SetLeftMargin  ( 0.20 );
  canv.SetRightMargin ( 0.05 );
  canv.SetBottomMargin( 0.15 );
  canv.SetTopMargin   ( 0.05 );
}

void histogramStyle(TH1& hist, int color, int lineStyle, int markerStyle, float markersize, int filled) 
{
  hist.SetLineWidth(3);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color);
  hist.SetMarkerColor(color);  
  hist.SetMarkerStyle(markerStyle);
  hist.SetMarkerSize(markersize);
  hist.SetLineStyle(lineStyle);
  if(filled==1){
  hist.SetFillStyle(1001);
  hist.SetFillColor(color);
  }
  else{
    hist.SetFillStyle(0);
  }
}

void drawcutline(double cutval, double maximum)
{
  TLine *cut = new TLine();
  cut->SetLineWidth(3);
  cut->SetLineColor(28);
  cut->DrawLine(cutval,0.,cutval,maximum);
}

void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin, float yMax, float yTitleSize, float yTitleOffset) 
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
  hist.GetYaxis()->SetTitleSize  ( yTitleSize );
  hist.GetYaxis()->SetTitleColor (    1);
  hist.GetYaxis()->SetTitleOffset(yTitleOffset);
  hist.GetYaxis()->SetTitleFont  (   62);
  hist.GetYaxis()->SetLabelSize  ( 0.04);
  hist.GetYaxis()->SetLabelFont  (   62);
  hist.GetYaxis()->CenterTitle   ( true);
  if(yMin!=-123) hist.SetMinimum(yMin);
  if(yMax!=-123) hist.SetMaximum(yMax);
}
