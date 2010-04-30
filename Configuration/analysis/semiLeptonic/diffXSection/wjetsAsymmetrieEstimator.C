
// ---------description------------------------------------------
// --------------------------------------------------------------
// this Makro estimates the fraction of W+jets from (pseudo) data
// with errors derived from statistical errors via gaussian error 
// calculus using the charge asymmetrie parameter (determined 
// within chargeAsymmetrieCalculator.C) and compares it to the 
// (gen-based) real W+jets fraction. Additionally the pt(muon) 
// is plotted for positive and negative charged muons.
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

enum styles {kPseudo50, kWjets};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void drawcutline(double cutval, double maximum);
double getChargeAsymmetrieParameter(TString bin, TString Njets);
double getErrorOfChargeAsymmetrieParameter(TString bin, TString Njets);

void wjetsAsymmetrieEstimator()
{
  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetErrorX(0); 

  // choose jet multiplicity you want to see: "Njets1" / "Njets2" / "Njets3" / "Njets4" / "Btag"
  TString multiplicity ="Njets1";
  // choose whether you want to save every plot as png and all within one ps file
  bool save = true;
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/chargeAsymmetrie/";
 
  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  files_.push_back(new TFile("./diffXSecFromSignal/pseudoData7TeV50pb.root"        ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecWjetsMadgraph7TeV.root" ) );  

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> pt_, ptMuPlus_, ptMuMinus_;
  TString which ="Rec";
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    ptMuMinus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+multiplicity+"/ptMinus" ) );
    ptMuPlus_  .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+multiplicity+"/ptPlus"  ) );
   }

  pt_ .push_back(  (TH1F*)ptMuMinus_[kPseudo50]->Clone() );
  pt_  [0]->Add (         ptMuPlus_ [kPseudo50]          );
  pt_ .push_back( (TH1F*)files_[kWjets]->Get("analyzeTightMuonCrossSectionRec"+multiplicity+"/pt") );

  // ---
  //    scale Wjets to luminosity
  // ---
  double lumiweight=0.12305083;
  pt_       [kWjets]->Scale(lumiweight);
  ptMuMinus_[kWjets]->Scale(lumiweight);
  ptMuPlus_ [kWjets]->Scale(lumiweight);

  // ---
  //    collect charge asymmetrie parameter
  // ---
  std::vector<double> parameter_;
  parameter_.push_back(getChargeAsymmetrieParameter( "2", multiplicity));
  parameter_.push_back(getChargeAsymmetrieParameter( "3", multiplicity));
  parameter_.push_back(getChargeAsymmetrieParameter( "4", multiplicity));
  parameter_.push_back(getChargeAsymmetrieParameter( "5", multiplicity));

  std::vector<double> parameterError_;
  parameterError_.push_back( getErrorOfChargeAsymmetrieParameter( "2", multiplicity) );
  parameterError_.push_back( getErrorOfChargeAsymmetrieParameter( "3", multiplicity) );
  parameterError_.push_back( getErrorOfChargeAsymmetrieParameter( "4", multiplicity) );
  parameterError_.push_back( getErrorOfChargeAsymmetrieParameter( "5", multiplicity) );

  // create histogram with Wjets-estimation from charge assymetrie method
  TH1F *ptWjetsEstimation= (TH1F*) pt_[0]->Clone();

  // calculate entries
  for(int i=2; i<= pt_[kPseudo50]->GetNbinsX(); i++){
    ptWjetsEstimation->SetBinContent(  i, parameter_[i-2]* ((double)ptMuPlus_[kPseudo50]->GetBinContent(i) - (double)ptMuMinus_[kPseudo50]->GetBinContent(i))  );
    }

  // ---
  //    calculate error via gaussian error calculus
  // ---
  std::vector<double> estimationError_;
  double x=0;
  double y=0;
 
  std::cout << "------------------------------------" << std::endl;
  std::cout << "W+jets background estimation "+multiplicity+"+" << std::endl;
  std::cout << "------------------------------------" << std::endl;

  for(int i=2; i<= ptWjetsEstimation->GetNbinsX(); i++){
    x = (double)(ptMuPlus_ [kPseudo50]->GetBinContent(i));
    y = (double)(ptMuMinus_[kPseudo50]->GetBinContent(i));
    estimationError_.push_back(  sqrt( (x-y)*(x-y)*parameterError_[i-2]*parameterError_[i-2] + parameter_[i-2]*parameter_[i-2]*(x+y) )  );
    
    std::cout << "estimation bin "    << i << ":   " <<  ptWjetsEstimation->GetBinContent(i) << " +/- " << estimationError_[i-2] << std::endl;
    std::cout << "( real # W events " <<      ": "   <<  pt_[kWjets]      ->GetBinContent(i) << " )"                             << std::endl;
    ptWjetsEstimation->SetBinError( i, estimationError_[i-2] );
   }

  // ---
  //    create legends 
  // ---

  // create a legend for estimation
  TLegend *leg0 = new TLegend(0.34, 0.63, 0.96, 0.88);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("50pb^{-1} @ #sqrt{s}=7TeV, "+multiplicity+"+"    );
  leg0->AddEntry( pt_[kPseudo50]     , "all pseudo data"      , "PL");
  leg0->AddEntry( ptWjetsEstimation  , "estimated # (W+jets)" , "PL");
  leg0->AddEntry( ptWjetsEstimation  , "from pseudo data"     , ""  );
  leg0->AddEntry( pt_[kWjets]        , "real # (W+jets) (MC)" , "PL");

  // create a legend for pseudo data
  TLegend *leg1 = new TLegend(0.38, 0.65, 1.00, 0.89);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("50pb^{-1} @ #sqrt{s}=7TeV, "+multiplicity+"+"      );
  leg1->AddEntry( pt_[kPseudo50]       , "pseudo data all #mu"  , "PL");
  leg1->AddEntry( ptMuPlus_ [kPseudo50], "pseudo data #mu^{+}"  , "PL");
  leg1->AddEntry( ptMuMinus_[kPseudo50], "pseudo data #mu^{-}"  , "PL");

  // ---
  //    do the printing for pt_ (W-estimation via method and real fraction)
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  // draw canvas
  canv0->cd(0);
  canv0->SetTitle("chargeAsymmetrieEstimationQuality");
  axesStyle(*pt_ [kWjets], "p_{t} ( tight #mu ) [GeV]", "events", 0, 1.5*pt_ [kPseudo50]->GetMaximum(), 0.065, 1.5);
  histogramStyle(*pt_ [kWjets], kBlue , 2); 
  histogramStyle(*pt_ [kPseudo50  ], kBlack, 1, 22, 1.2);
  histogramStyle(*ptWjetsEstimation, kRed  , 1, 22, 1.2);
  pt_ [kWjets]     ->Draw("");
  ptWjetsEstimation->Draw("same");
  pt_ [kPseudo50  ]->Draw("same");
  pt_ [kPseudo50  ]->Draw("esame");
  leg0             ->Draw("same");

  // ---
  //    do the printing for pt_ (pseudo data)
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);
  // draw canvas
  canv1->cd(0);
  canv1->SetTitle("ptMuChargePseudoData");
  axesStyle(*pt_ [kPseudo50], "p_{t} ( tight #mu ) [GeV]", "events", 0., 1.4*pt_ [kPseudo50]->GetMaximum(), 0.065, 1.5);
  histogramStyle(*ptMuPlus_ [kPseudo50], kBlue , 1); 
  histogramStyle(*ptMuMinus_[kPseudo50], kRed  , 1); 
  pt_        [kPseudo50]->Draw("hist");
  pt_        [kPseudo50]->Draw("esame");
  ptMuPlus_  [kPseudo50]->Draw("esame");
  ptMuMinus_ [kPseudo50]->Draw("esame");
  ptMuPlus_  [kPseudo50]->Draw("histsame");
  ptMuMinus_ [kPseudo50]->Draw("histsame");
  leg1                  ->Draw("same");

  // ---
  // saving
  // ---

  if(save){
    // ps
    canv0->Print(saveTo+"chargeAsymmetrieEstimation50pbAt7TeV"+multiplicity+".ps(" );
    canv1->Print(saveTo+"chargeAsymmetrieEstimation50pbAt7TeV"+multiplicity+".ps)" );
  
    // png
    canv1->Print(saveTo+(TString)(canv0->GetTitle())+".png");
    canv1->Print(saveTo+(TString)(canv1->GetTitle())+".png");
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

double getChargeAsymmetrieParameter(TString bin, TString Njets)
{
  // create container for histo max values sortet by plot and Njet
  std::map< TString, std::map <TString,double> > maxValues_;  
  // store values for charge asymmetrie parameter 
  // calculated within chargeAsymmetrieCalculator.C
  maxValues_["2" ]["Njets4"]= 2.46218;   
  maxValues_["3" ]["Njets4"]= 3.02667; 
  maxValues_["4" ]["Njets4"]= 7.84615; 
  maxValues_["5" ]["Njets4"]= 9.95238; 

  maxValues_["2" ]["Njets3"]= 2.94059;
  maxValues_["3" ]["Njets3"]= 3.89305;
  maxValues_["4" ]["Njets3"]= 7.89172;
  maxValues_["5" ]["Njets3"]= 68.2308;

  maxValues_["2" ]["Njets2"]= 3.3677;
  maxValues_["3" ]["Njets2"]= 7.10938;
  maxValues_["4" ]["Njets2"]= 6.72402;
  maxValues_["5" ]["Njets2"]= 16.3228;

  maxValues_["2" ]["Njets1"]= 3.70916;
  maxValues_["3" ]["Njets1"]= 6.36648;
  maxValues_["4" ]["Njets1"]= 11.627;
  maxValues_["5" ]["Njets1"]= 13.5367;

  // get maximum value
  return maxValues_.find(bin)->second.find(Njets)->second;
}

double getErrorOfChargeAsymmetrieParameter(TString bin, TString Njets)
{
  // create container for histo max values sortet by plot and Njet
  std::map< TString, std::map <TString,double> > maxValues_;  
  // store values for the error of the charge asymmetrie parameter 
  // calculated within chargeAsymmetrieCalculator.C
  maxValues_["2" ]["Njets4"]= 0.323641;
  maxValues_["3" ]["Njets4"]= 0.573873;
  maxValues_["4" ]["Njets4"]= 4.27506;
  maxValues_["5" ]["Njets4"]= 6.81675;

  maxValues_["2" ]["Njets3"]= 0.192632;
  maxValues_["3" ]["Njets3"]= 0.383863;
  maxValues_["4" ]["Njets3"]= 1.75506;
  maxValues_["5" ]["Njets3"]= 156.298;

  maxValues_["2" ]["Njets2"]= 0.0979765;
  maxValues_["3" ]["Njets2"]= 0.500157;
  maxValues_["4" ]["Njets2"]= 0.509546;
  maxValues_["5" ]["Njets2"]= 4.13009;

  maxValues_["2" ]["Njets1"]= 0.045038;
  maxValues_["3" ]["Njets1"]= 0.152079;
  maxValues_["4" ]["Njets1"]= 0.612709;
  maxValues_["5" ]["Njets1"]= 1.38129;
  // get maximum value
  return maxValues_.find(bin)->second.find(Njets)->second;
}
