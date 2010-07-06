
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

enum styles {kWjets,kPseudo50};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void drawcutline(double cutval, double maximum);
std::pair<double,double> getChargeAsymmetrieParameter(int njets);
string getStringFromInt(int i);
double sumUpEntries(TH1F& histo);

void wjetsAsymmetrieEstimator()
{
  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetErrorX(0); 

  // choose whether you want to save every plot as png and all within one ps file
  bool save = true;
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/chargeAsymmetrie/";
 
  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/spring10Samples/spring10SelV2Sync";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecWjetsMadSpring10.root"   ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/spring10PseudoData7TeV50pb.root" ) );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> ptMuPlusPseudoNjets_, ptMuMinusPseudoNjets_, ptWjetsNjets_, ptPseudoNjets_;
  for(int idx=1; idx<=4; idx++){
  // all Njets-histos for 50 pb-1 pseudo data
    ptMuPlusPseudoNjets_ .push_back( (TH1F*)(files_[kPseudo50]->Get("analyzeTightMuonCrossSectionRecNjets"+(TString)getStringFromInt(idx)+"/ptPlus"  ) )->Clone() );
    ptMuMinusPseudoNjets_.push_back( (TH1F*)(files_[kPseudo50]->Get("analyzeTightMuonCrossSectionRecNjets"+(TString)getStringFromInt(idx)+"/ptMinus" ) )->Clone() );
  // all Njets-histos for W+jets
    ptWjetsNjets_ .push_back( (TH1F*)(files_[kWjets]->Get("analyzeTightMuonCrossSectionRecNjets"+(TString)getStringFromInt(idx)+"/pt") )->Clone() );
    ptPseudoNjets_.push_back(  (TH1F*)(ptMuPlusPseudoNjets_ [idx-1]->Clone()) );
    ptPseudoNjets_[idx-1]->Add((TH1F*)(ptMuMinusPseudoNjets_[idx-1]->Clone()) );
  }
  
  // ---
  //    scale Wjets to luminosity
  // ---
  // spring10 7TeV W+jets MADGRAPH sample 
  double lumiweight=0.13904207;
  // 50 pb^{-1}
  for(unsigned idx=1; idx<=4; idx++){
    ptWjetsNjets_[idx-1]->Scale(lumiweight);
  }

  // check weighting
  std::cout << "" << std::endl;
  std::cout << "check weighting W+jets MC" << std::endl;
  std::cout << "N(W) before weighting: " << ptWjetsNjets_[0]->GetEntries() << std::endl;
  double weightedEntries = sumUpEntries(*ptWjetsNjets_[0]);
  std::cout << "N(W) after weighting: " << weightedEntries << std::endl;
  std::cout << "ratio : " << weightedEntries/(double)(ptWjetsNjets_[0]->GetEntries()) << std::endl;
  std::cout << "weight: " << lumiweight << std::endl;

  // check pseudo data reading out
  std::cout << "" << std::endl;
  std::cout << "check pseudo data N(jets)>=1" << std::endl;
  std::cout << "N = "  << sumUpEntries(*ptPseudoNjets_[0]) << std::endl;
  std::cout << "N+ = " << sumUpEntries(*ptMuPlusPseudoNjets_ [0]) << std::endl;
  std::cout << "N- = " << sumUpEntries(*ptMuMinusPseudoNjets_[0]) << std::endl;

  // print out necessary informations
  std::cout << "w+jets estimation" << std::endl;
  std::cout << "- R(pt(mu)>=20 GeV) from W+jets gen niveau" << std::endl;
  std::cout << "- estimation from combined pseudo data reco files (wjets+zjets+qcd+ttbar)" << std::endl;

  // ---
  //    create histogram with W+jets-estimation from charge asymmetrie method and MC truth
  // ---
  TH1F *wjetsEstimation = new TH1F("wjetsEstimation" , "wjetsEstimation" , 4, 0.5, 4.5);
  TH1F *wjetsTruth      = new TH1F("wjetsTruth"      , "wjetsTruth"      , 4, 0.5, 4.5);
  TH1F *allPseudoEvents = new TH1F("allPseudoEvents" , "allPseudoEvents" , 4, 0.5, 4.5);
  // loop jet multiplicities
  for(int njets=1; njets<=wjetsEstimation->GetNbinsX(); njets++){
    std::cout << ""                      << std::endl;
    std::cout << "N(jets) >= " << njets << std::endl; 
    std::cout << "---------------------" << std::endl;
    double x = sumUpEntries(*ptMuPlusPseudoNjets_ [njets-1]);
    double y = sumUpEntries(*ptMuMinusPseudoNjets_[njets-1]);
    double R =getChargeAsymmetrieParameter(njets).first;
    double dR=getChargeAsymmetrieParameter(njets).second;
    // calculate entries for W+jets-estimation
    wjetsEstimation->SetBinContent( njets, (x-y)*R );
    // calculate error for W+jets-estimation via gaussian error calculus
    wjetsEstimation->SetBinError( njets, sqrt( (x-y)*(x-y)*dR*dR + R*R*(x+y) )  );
    std::cout << "N(mu+, pseudo data) = "  << x << std::endl;
    std::cout << "N(mu-, pseudo data) = "  << y << std::endl;
    std::cout << "R(Njets >=" << njets << ") = " << R << " +- " << dR << std::endl;
    std::cout << "N(estimated W)= " << wjetsEstimation->GetBinContent(njets) << " +- " << wjetsEstimation->GetBinError(njets) << std::endl;
    // calculate entries for W+jets MC truth
    wjetsTruth->SetBinContent( njets, sumUpEntries(*ptWjetsNjets_[njets-1]) );
    std::cout << "N(W, MC truth) = " << wjetsTruth->GetBinContent(njets) << std::endl;
    allPseudoEvents->SetBinContent( njets, sumUpEntries(*ptPseudoNjets_[njets-1]) );
    std::cout << "total # events: " << allPseudoEvents->GetBinContent(njets) << std::endl;
  }

  // ---
  //    create legends 
  // ---
  // create a legend for estimation
  TLegend *leg0 = new TLegend(0.30, 0.69, 0.92, 0.94);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("N_{W} @ 50pb^{-1} (7TeV)");
  leg0->AddEntry( wjetsEstimation, "estimation from pseudo data", "P");
  leg0->AddEntry( wjetsTruth     , "MC truth"                   , "L" );
  leg0->AddEntry( allPseudoEvents, "total # events"             , "L" );

  // ---
  //    do the printing for N_W [Njets]
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  canv0->SetTitle("wjetsCAEstimation50pb");
  axesStyle(*wjetsTruth, "N_{jets} #geq", "N_{W}", 1., 10000000);
  histogramStyle(*wjetsTruth     , kBlue , 1, 20, 0.5); 
  histogramStyle(*wjetsEstimation, kRed  , 1, 22, 1.2);
  histogramStyle(*allPseudoEvents, kBlack, 1, 20, 0.5); 
  wjetsTruth     ->Draw("");
  allPseudoEvents->Draw("same");
  wjetsEstimation->Draw("esame");
  leg0           ->Draw("same");

  // ---
  // saving
  // ---

  if(save){
    // ps
    canv0->Print(saveTo+"chargeAsymmetrieEstimation.ps" );
    // png
    canv0->Print(saveTo+(TString)(canv0->GetTitle())+".png");
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

std::pair<double,double> getChargeAsymmetrieParameter(int njets)
{  
  std::map< TString, std::map <unsigned int, std::pair<double,double> > > Rinclusive_;
  Rinclusive_["mu"][1] = make_pair( 5.60626 , 0.0634405 );
  Rinclusive_["mu"][2] = make_pair( 5.20138 , 0.129156  );
  Rinclusive_["mu"][3] = make_pair( 4.55043 , 0.233407  );
  Rinclusive_["mu"][4] = make_pair( 4.07162 , 0.410175  );
  return Rinclusive_["mu"][njets];
}

string getStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return result;
}

double sumUpEntries(TH1F& histo){
  // sum up all bin entries of histo  
  // +1 : include overflow bin
  double entries=0;
  for(int idx=1; idx<=histo.GetNbinsX()+1; idx++){
    entries+=histo.GetBinContent(idx);
  }
  return entries;
}
