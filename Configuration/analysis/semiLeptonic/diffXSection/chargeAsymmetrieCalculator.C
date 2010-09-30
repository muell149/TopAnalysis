
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
#include <string>
#include <fstream>

#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <THStack.h>
#include <TLine.h>
#include <TStyle.h>
#include <TPaveLabel.h>
#include <TF1.h>
#include <TMath.h>

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void drawcutline(double cutval, double maximum);
TH1F* calcutateR(TH1F& ptPlus, TH1F& ptMinus, TString label="", TString jetMultiplicity="");
std::pair<double,double> calcutateTotalR(double ptPlus, double ptMinus, TString label="", TString jetMultiplicity="");
TString getTStringFromInt(int i);
double sumBinEntries(TH1F& histo, int excludeBin1=0, int excludeBin2=0, int excludeBin3=0);
void fitQuadraticExtrapolate(TH1F& hist, double xmin, double xmax, int color, TString info);
std::vector<std::pair<double,double> > fitLinear(TH1F& hist, double xmin, double xmax, int color, TString info);
template <class T>
void writeToFile(T output, TString file="crossSectionCalculation.txt", bool append=1);

void chargeAsymmetrieCalculator(bool save = true, bool textoutput=false)
{ 
  // ---
  //    main function parameters
  // ---
  // save:       choose whether you want to save every plot as png and all within one ps file
  // textoutput: choose whether you want to save the estimated number of QCD events for data 
  //             in .txt file to share it with other parts of the Analysis
  // choose target directory for saving:
  TString saveTo = "./diffXSecFromSignal/plots/chargeAsymmetrie/";

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
  TString whichSample = "/spring10Samples/spring10SelV2Sync";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/chargeAsymmetryWjetsMadSpring10.root") );

  // ---
  //    get histograms
  // ---
  // get e, mu, tau and mu+tau->mu histos for all jet multiplicities 
  std::vector<TH1F*> ptNMuPlus_, ptNMuMinus_, ptNEPlus_, ptNEMinus_, ptNTPlus_, ptNTMinus_, ptNWMuPlus_, ptNWMuMinus_;  
  TString mult="";
  for(int idx=0; idx<=4; ++idx) {
    if(idx==0) mult="";
    else {
      mult = "Njets"+getTStringFromInt(idx);
    }
    ptNMuMinus_ .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryMuons"+mult+"/ptMinus"     ) );
    ptNMuPlus_  .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryMuons"+mult+"/ptPlus"      ) );
    ptNEMinus_  .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWElectrons"+mult+"/ptMinus" ) );
    ptNEPlus_   .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWElectrons"+mult+"/ptPlus"  ) );
    ptNTMinus_  .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWTaus"+mult+"/ptMinus"      ) );
    ptNTPlus_   .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWTaus"+mult+"/ptPlus"       ) ); 
    ptNWMuMinus_.push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWMuons"+mult+"/ptMinus"     ) );
    ptNWMuPlus_ .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWMuons"+mult+"/ptPlus"      ) );
  }
 
  // --- 
  //    calculate charge asymmetry parameters R and errors
  // ---
  // a) R(ptmu) for different jet multiplicities and leptons
  // ----------------------------------------------------------------------------------------------
  // Rpt_[lepton][jetMultiplicity] -> eg: Rpt_[Wmu][4] = R(pt) for muons from W after >= 4 jets cut
  std::map< TString, std::map <unsigned int,TH1F* > > Rpt_;
  // loop jet multiplicities
  for(int njets =0; njets<=4; njets++){
    Rpt_["mu"  ][njets] = (TH1F*) calcutateR(*ptNMuPlus_[njets],  *ptNMuMinus_[njets],  "Muons from W and W->tau", "N(jets) >= "+getTStringFromInt(njets));
    Rpt_["Wmu" ][njets] = (TH1F*) calcutateR(*ptNWMuPlus_[njets], *ptNWMuMinus_[njets], "Muons from W", "N(jets) >= "+getTStringFromInt(njets));
    Rpt_["We"  ][njets] = (TH1F*) calcutateR(*ptNEPlus_[njets],   *ptNEMinus_[njets],   "Electrons from W", "N(jets) >= "+getTStringFromInt(njets));
    Rpt_["Wtau"][njets] = (TH1F*) calcutateR(*ptNTPlus_[njets],   *ptNTMinus_[njets],   "Taus from W", "N(jets) >= "+getTStringFromInt(njets));
  }

  // b) inclusive R(ptlep>20GeV) for different jet multiplicities and leptons
  // ----------------------------------------------------------------------------------------------
  // Rpt_[lepton][jetMultiplicity] -> eg: Rpt_[Wmu][4].first/second = R/dR for muons with pt>20GeV from W after >= 4 jets cut
  std::map< TString, std::map <unsigned int, std::pair<double,double> > > Rinclusive_;
  for(int njets =0; njets<=4; njets++){
    Rinclusive_["mu"  ][njets] = calcutateTotalR(sumBinEntries(*ptNMuPlus_[njets],1),  sumBinEntries(*ptNMuMinus_[njets],1),  "Muons from W and W->tau, pt>20GeV", "N(jets) >= "+getTStringFromInt(njets));
    Rinclusive_["Wmu" ][njets] = calcutateTotalR(sumBinEntries(*ptNWMuPlus_[njets],1), sumBinEntries(*ptNWMuMinus_[njets],1), "Muons from W, pt>20GeV", "N(jets) >= "+getTStringFromInt(njets));
    Rinclusive_["We"  ][njets] = calcutateTotalR(sumBinEntries(*ptNEPlus_[njets],1),   sumBinEntries(*ptNEMinus_[njets],1),   "Electrons from W, pt>20GeV", "N(jets) >= "+getTStringFromInt(njets));
    Rinclusive_["Wtau"][njets] = calcutateTotalR(sumBinEntries(*ptNTPlus_[njets],1),   sumBinEntries(*ptNTMinus_[njets],1),   "Taus from W, pt>20GeV", "N(jets) >= "+getTStringFromInt(njets));
  }

  // c)  create R_inclusive[Njets] plot(s) from b)
  TH1F* RNjetsMu  = new TH1F("RNjetsMu" , "RNjetsMu" , 5, -0.5, 4.5);
  TH1F* RNjetsWMu = new TH1F("RNjetsWMu", "RNjetsWMu", 5, -0.5, 4.5);
  for(int bin=1; bin<= ptNMuPlus_[1]->GetNbinsX()+1; bin++){
    // -1 because 1st bin = 0 jets bin
    RNjetsMu->SetBinContent(bin,  Rinclusive_["mu"][bin-1].first);
    RNjetsMu->SetBinError  (bin,  Rinclusive_["mu"][bin-1].second);
    RNjetsWMu->SetBinContent(bin,  Rinclusive_["Wmu"][bin-1].first);
    RNjetsWMu->SetBinError  (bin,  Rinclusive_["Wmu"][bin-1].second);
  }

  // ---
  //    create legends 
  // ---
  // create a legend for R_inclusive[Njets] for some leptons
  TLegend *leg0 = new TLegend(0.25, 0.70, 1.0, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("inclusive R for p_{ t} (#mu) > 20 GeV, | #eta | < 2.1" );
  leg0->AddEntry(RNjetsMu ,"W -> #mu#nu_{#mu} & W -> #tau#nu->#mu#nu_{#mu}#nu_{#tau}", "PL");
  leg0->AddEntry(RNjetsWMu,"W -> #mu#nu_{#mu}"                                       , "PL");

  // create a legend for asymmetry parameter from different leptons without jet selection
  TLegend *leg1 = new TLegend(0.21, 0.65, 0.99, 0.89);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("R_{gen MC}: W+jets(MADGRAPH), 406 pb^ { -1}");
  leg1->AddEntry( Rpt_["mu"  ][0], "#mu from W & W -> #tau", "P");
  leg1->AddEntry( Rpt_["We"  ][0], "e from W"              , "P");
  leg1->AddEntry( Rpt_["Wtau"][0], "#tau from W"           , "P");
  leg1->AddEntry( Rpt_["Wmu" ][0], "#mu from W"            , "P");

  // create a legend for asymmetry parameter from different leptons for >= 1 jet selection
  TLegend *leg2 = new TLegend(0.21, 0.65, 0.99, 0.89);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetHeader("R_{gen MC}: W+jets(MADGRAPH), 406 pb^ { -1}");
  leg2->AddEntry( Rpt_["mu"  ][1], "#mu from W & W -> #tau", "P");
  leg2->AddEntry( Rpt_["We"  ][1], "e from W"              , "P");
  leg2->AddEntry( Rpt_["Wtau"][1], "#tau from W"           , "P");
  leg2->AddEntry( Rpt_["Wmu" ][1], "#mu from W"            , "P");

  // R(ptmu) for all jet multiplicities for W->mu && W->tau->mu
  TLegend *leg3a = new TLegend(0.21, 0.73, 1.0, 0.93);
  leg3a->SetFillStyle(0);
  leg3a->SetBorderSize(0);
  leg3a->SetHeader("R_{gen MC} W->mu & W->tau->mu");
  leg3a->AddEntry( Rpt_["mu"][0], "N(jets)#geq0", "P");
  leg3a->AddEntry( Rpt_["mu"][1], "N(jets)#geq1", "P");

  // R(ptmu) for all jet multiplicities for W->mu && W->tau->mu
  TLegend *leg3b = new TLegend(0.61, 0.68, 0.88, 0.87);
  leg3b->SetFillStyle(0);
  leg3b->SetBorderSize(0);
  leg3b->AddEntry( Rpt_["mu"][2], "N(jets)#geq2", "P");
  leg3b->AddEntry( Rpt_["mu"][3], "N(jets)#geq3", "P");
  leg3b->AddEntry( Rpt_["mu"][4], "N(jets)#geq4", "P");

   // label indicating used jetcut
  TPaveLabel *jet0 = new TPaveLabel(0.76, 0.86, 0.96, 1.0, "no jetcut", "br NDC");
  jet0->SetFillStyle(0);
  jet0->SetBorderSize(0);
  jet0->SetTextSize(0.26);
  TPaveLabel *jet1= (TPaveLabel*)(jet0->Clone());
  jet1->SetLabel("N(jets) #geq 1");

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<=3; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ---
  //    do the printing for R_inclusive[Njets] for some leptons
  // ---
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetTitle("inclusiveRNjets");
  axesStyle(*RNjetsMu, "N_{jets} #geq", "R = #frac{N_{W^{+}} + N_{W^{-}}}{N_{W^{+}} - N_{W^{-}}}", 1, 1.5*RNjetsMu->GetMaximum(), 0.06, 1.3 );
  histogramStyle(*RNjetsMu , kBlack,  1, 20, 1.0);
  histogramStyle(*RNjetsWMu, kRed  ,  1, 20, 1.0);
  RNjetsMu ->Draw("");
  RNjetsWMu->Draw("same");
  std::vector<std::pair<double,double> > inclusiveRfit_ =fitLinear(*RNjetsMu, 1.0, 4.5, RNjetsMu->GetLineColor(), "R( N(jets) ), W->mu & W->tau->mu");
  leg0     ->Draw("same");

  // ---
  //     do the printing for R(ptlep) with >= 0 jets for some leptons
  // ---
  MyCanvas[1]->cd(0);
  MyCanvas[1]->SetTitle("RptMuNjets0");
  axesStyle(*Rpt_["mu"][0], "p_{t} ( gen lep ) [GeV]", "R = #frac{N_{W^{+}} + N_{W^{-}}}{N_{W^{+}} - N_{W^{-}}}", 0, 70, 0.05, 1.5);  
  histogramStyle(*Rpt_["mu"  ][0], kBlack, 1, 20, 1.0);
  histogramStyle(*Rpt_["Wmu" ][0], kRed  , 1, 20, 1.0);
  histogramStyle(*Rpt_["We"  ][0], kBlue , 1, 20, 1.0);
  histogramStyle(*Rpt_["Wtau"][0], kGreen, 1, 20, 1.0);
  Rpt_["mu"  ][0]->DrawClone("");
  Rpt_["Wmu" ][0]->DrawClone("same");
  Rpt_["We"  ][0]->DrawClone("same");
  Rpt_["Wtau"][0]->DrawClone("same");
  leg1           ->DrawClone("same");
  jet0           ->DrawClone("same");

  // ---
  //     do the printing for R(ptlep) with >= 1 jets for some leptons
  // ---
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetTitle("RptMuNjets1");
  axesStyle(*Rpt_["mu"][1], "p_{t} ( gen lep ) [GeV]", "R = #frac{N_{W^{+}} + N_{W^{-}}}{N_{W^{+}} - N_{W^{-}}}", 0, 70, 0.05, 1.5);  
  histogramStyle(*Rpt_["mu"  ][1], kBlack, 1, 20, 1.0);
  histogramStyle(*Rpt_["Wmu" ][1], kRed  , 1, 20, 1.0);
  histogramStyle(*Rpt_["We"  ][1], kBlue , 1, 20, 1.0);
  histogramStyle(*Rpt_["Wtau"][1], kGreen, 1, 20, 1.0);
  Rpt_["mu"  ][1]->DrawClone("");
  Rpt_["Wmu" ][1]->DrawClone("same");
  Rpt_["We"  ][1]->DrawClone("same");
  Rpt_["Wtau"][1]->DrawClone("same");
  leg2           ->DrawClone("same");
  jet1           ->DrawClone("same");

  // ---
  //     do the printing for R(ptlep) with >= 1 jets for some leptons
  // ---
  MyCanvas[3]->cd(0);
  MyCanvas[3]->SetTitle("RptMuAllNjetsMuAndTauMu");
  axesStyle(*Rpt_["mu"][4], "p_{t} ( gen lep ) [GeV]", "R = #frac{N_{W^{+}} + N_{W^{-}}}{N_{W^{+}} - N_{W^{-}}}", 0, 70, 0.05, 1.5);  
  histogramStyle(*Rpt_["mu"][0], kBlack, 1, 20, 1.0);
  histogramStyle(*Rpt_["mu"][1], kRed  , 1, 20, 1.0);
  histogramStyle(*Rpt_["mu"][2], kBlue , 1, 20, 1.0);
  histogramStyle(*Rpt_["mu"][3], kGreen, 1, 20, 1.0);
  histogramStyle(*Rpt_["mu"][4], 50    , 1, 20, 1.0);
  Rpt_["mu"][4]->Draw("");
  Rpt_["mu"][3]->Draw("same");
  Rpt_["mu"][2]->Draw("same");
  Rpt_["mu"][1]->Draw("same");
  Rpt_["mu"][0]->Draw("same");
  fitQuadraticExtrapolate(*Rpt_["mu"][4], 20., 100., Rpt_["mu"][4]->GetLineColor(), "R_inclusive, N(jets)>=4");
  fitQuadraticExtrapolate(*Rpt_["mu"][3], 20., 100., Rpt_["mu"][3]->GetLineColor(), "R_inclusive, N(jets)>=3");
  fitQuadraticExtrapolate(*Rpt_["mu"][2], 20., 100., Rpt_["mu"][2]->GetLineColor(), "R_inclusive, N(jets)>=2");
  fitQuadraticExtrapolate(*Rpt_["mu"][1], 20., 100., Rpt_["mu"][1]->GetLineColor(), "R_inclusive, N(jets)>=1");
  fitQuadraticExtrapolate(*Rpt_["mu"][0], 20., 100., Rpt_["mu"][0]->GetLineColor(), "R_inclusive, N(jets)>=0");
  leg3a        ->Draw("same");
  leg3b        ->Draw("same");

  // ---
  //     calculate fittet inclusive R for W->mu && W->tau->mu
  // ---
  // loop jet multiplicities
  for(double njets =1; njets<=4; njets++){
    double a= inclusiveRfit_[0].first;
    double b= inclusiveRfit_[1].first;
    double sa= inclusiveRfit_[0].second;
    double sb= inclusiveRfit_[1].second;
    double inclusiveRfit = a*(njets)+b;
    //inclusiveRfit = (a-2*sa)*(njets)+b;
    double errorInclusiveRfit = sqrt( (njets*sa)*(njets*sa) + sb*sb );
    // print out to shell
    if(njets==1) std::cout << std::endl << "inclusive R (linear fit) for W->mu && W->tau->mu" << std::endl;
    std::cout << "N(jets)>="+getTStringFromInt(njets) << ": R = " << inclusiveRfit << " +/- " << errorInclusiveRfit << std::endl;
    // if textoutput==true: save fitted inclusive R values within .txt-file
    if(textoutput==true){
      if(njets==1) writeToFile("inclusive R (from linear fit) for gen W->mu and W->tau->mu for N(jets) >= 1 - 4:");
      writeToFile(inclusiveRfit);
    }
  }
  
  // ---
  // saving
  // ---  
  if(save){
    // ps
    MyCanvas[0]->Print(saveTo+"chargeAsymmetrieParameter.ps("  );
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+"chargeAsymmetrieParameter.ps"  );   
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+"chargeAsymmetrieParameter.ps)"  );
  
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

TH1F* calcutateR(TH1F& ptPlus, TH1F& ptMinus, TString label, TString jetMultiplicity){
  // calculates charge asymmetry parameter
  // R as function of pt(mu) for N(jets)=jetMultiplicity
  // from ptPlus and ptMinus histos
  // label should correspond to the lepton input (e.g. W->mu)

  std::vector<double> parameter_;
  std::vector<double> parameterError_;
  double ptP=0;
  double ptM=0;
  double x=0;
  // print out settings for R-calculation
  std::cout << "----------------------------------------" << std::endl;
  std::cout << " R[ pt(mu) ] "+label  << std::endl;
  std::cout << "---------"+jetMultiplicity+"------------------------" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
  // ---
  //    calculate R and error via gaussian error calculus
  // ---
  for(int i=1; i<= ptPlus.GetNbinsX()+1; i++){
    ptP = (double)(ptPlus .GetBinContent(i));
    ptM = (double)(ptMinus.GetBinContent(i));
    if(ptP!=0 && ptM!=0){
      x = ptM / ptP;
      double parameter = (1.0 + x) / (1.0 -x);
      parameter_     .push_back( parameter );
      parameterError_.push_back( ( 1.0/(ptP-ptM) ) * sqrt( ptP *(1-parameter)*(1-parameter) + 
							   ptM *(1+parameter)*(1+parameter) )  );
      std::cout << "bin " << i << ": " << parameter_[i-1] << " +/- " << parameterError_[i-1] << std::endl;
    }
    else{
      parameter_     .push_back( 0.0 );
      parameterError_.push_back( 0.0 );
      std::cout << "bin " << i << ": no entries for lep+ and/or lep-" << std::endl;    
    }
  }

  // create histogram with assymetrie parameter as clone
  TH1F *asymmetryParameter= (TH1F*) ptPlus.Clone();
  // fill in calculated entries and errors
  for(int i=1; i<= ptPlus.GetNbinsX()+1; i++){
    asymmetryParameter->SetBinContent( i, parameter_[i-1] );
    asymmetryParameter->SetBinError  ( i, parameterError_[i-1] );
  }
  return asymmetryParameter;
}


std::pair<double,double> calcutateTotalR(double ptPlus, double ptMinus, TString label, TString jetMultiplicity){
  // calculate charge asymmetrie parameter R
  // for N(jets)=jetMultiplicity integrated over 
  // lepton pt from ptMinus and ptPlus which 
  // correspond to the total number of negative and 
  // positive charged leptons
  // label should correspond to the lepton input (e.g. W->mu)
  // the result is stored in a vector with R as component 0 
  // and error of R as component 1

  double parameter;
  double parameterError;
  double x=0;

  std::cout << "----------------------------------------" << std::endl;
  std::cout << "inclusive R for "+label                   << std::endl;
  std::cout << "---------"+jetMultiplicity+"--------------------" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
  std::cout << "N(lep+)=" << ptPlus  << std::endl;
  std::cout << "N(lep-)=" << ptMinus << std::endl;

  if(ptPlus!=0 && ptMinus!=0){ 
    x = ptMinus/ptPlus;
    std::cout << "N(lep-)/N(lep+)=" << x << std::endl;
    parameter= (1.0 + x) / (1.0 - x) ; 
    parameterError= ( 1.0/(ptPlus-ptMinus) ) * sqrt( ptPlus *(1-parameter)*(1-parameter) + 
						     ptMinus*(1+parameter )*(1+parameter) );
    std::cout << "R = " << parameter << " +/- " << parameterError << std::endl;
  }
  else{
    parameter      = 0.0;
    parameterError = 0.0;
    std::cout << "no entries for lep+ and/or lep-" << std::endl;    
  }
  std::pair<double,double> output_;
  output_.first  = parameter;
  output_.second = parameterError;
  return output_;
}

TString getTStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return result;
}

double sumBinEntries(TH1F& histo, int excludeBin1, int excludeBin2, int excludeBin3){
  // get N(entries) in all bins of histo
  // excluding excludeBin1/2/3
  double sum = 0;
  for(int bin=1; bin<= histo.GetNbinsX()+1; bin++){
    if(bin!=excludeBin1 && bin!=excludeBin2 && bin!=excludeBin3) sum+=histo.GetBinContent(bin);
  }

  return sum;
}

void fitQuadraticExtrapolate(TH1F& hist, double xmin, double xmax, int color, TString info){
  // print out info
  std::cout << "" << std::endl;
  std::cout << "quadratic fit: a*x^2 +b for " << info << std::endl;
  std::cout << "-----------------------=----------------" << std::endl;
  TF1* myPol = new TF1("myPol","[0]+[1]*x*x");
  // do a*x^2+b fit for hist in range [xmin,xmax]
  hist.Fit(myPol,"Q","same",xmin, xmax);
  // edit color of fit and extrapolate to whole region of x
  myPol->SetRange(hist.GetBinLowEdge(1),hist.GetBinLowEdge(hist.GetNbinsX()+1));
  myPol->SetLineColor(color);
  myPol->DrawClone("same");
  std::cout << "a = " << myPol->GetParameter(1) << " +/- " << myPol->GetParError(1) << std::endl;
  std::cout << "b = " << myPol->GetParameter(0) << " +/- " << myPol->GetParError(0) << std::endl;
  std::cout << "chi2/ndof = " << myPol->GetChisquare() / myPol->GetNDF() << std::endl;
  std::cout << "probability = " << TMath::Prob(myPol->GetChisquare(),myPol->GetNDF()) << std::endl;
}

std::vector<std::pair<double,double> > fitLinear(TH1F& hist, double xmin, double xmax, int color, TString info){
  // print out info
  std::cout << "" << std::endl;
  std::cout << "linear fit: a*x +b for " << info << std::endl;
  std::cout << "-----------------------=----------------" << std::endl;
  TF1* myPol = new TF1("myPol","[0]+[1]*x");
  // do a*x^2+b fit for hist in range [xmin,xmax]
  hist.Fit(myPol,"Q","same",xmin, xmax);
  // edit color of fit and extrapolate to whole region of x
  //  myPol->SetRange(1.0, 4.5);
  myPol->SetLineColor(color);
  myPol->DrawClone("same");
  std::cout << "a = " << myPol->GetParameter(1) << " +/- " << myPol->GetParError(1) << std::endl;
  std::cout << "b = " << myPol->GetParameter(0) << " +/- " << myPol->GetParError(0) << std::endl;
  std::cout << "chi2/ndof = " << myPol->GetChisquare() / myPol->GetNDF() << std::endl;
  std::cout << "probability = " << TMath::Prob(myPol->GetChisquare(),myPol->GetNDF()) << std::endl;
  // return a and b parameter of fit and their errors
  std::vector<std::pair<double,double> > result_;
  result_.push_back ( make_pair(myPol->GetParameter(1), myPol->GetParError(1)) );
  result_.push_back ( make_pair(myPol->GetParameter(0), myPol->GetParError(0)) );
  return result_;
}

template <class T>
void writeToFile(T output, TString file, bool append){
  // introduce function to write in file
  // a) write into file
  if(!append){
    std::ofstream fout(file);
    fout << output << std::endl;
    fout.close();
  }
  // b) write to the end of the file  
  if(append){
    std::ofstream fapp(file, ios::app);
    fapp << output << std::endl;;
    fapp.close();
  }
}
