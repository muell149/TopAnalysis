
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
TH1F* calcutateR(TH1F& ptPlus, TH1F& ptMinus, TString label="", TString jetMultiplicity="");
std::vector<double> calcutateTotalR(double ptPlus, double ptMinus, TString label="", TString jetMultiplicity="");
string getStringFromInt(int i);

void chargeAsymmetrieCalculator()
{
  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetErrorX(0); 


  // choose jet multiplicity you want to see: "Njets1" / "Njets2" / "Njets3" / "Njets4" 
  TString jetMultiplicity = "Njets1";
  // choose whether you want to save every plot as png and all within one ps file
  bool save = true;
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/chargeAsymmetrie/";

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/spring10Samples/recoAndGenFromPATtuplesWithSummer09JEC";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/chargeAsymmetryWjetsMadSpring10.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> ptMu_, ptMuPlus_, ptMuMinus_, ptWMu_, ptWMuPlus_, ptWMuMinus_, ptWE_, ptWEPlus_, ptWEMinus_, ptWT_, ptWTPlus_, ptWTMinus_;
  ptWMu_      .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWMuons"+jetMultiplicity+"/pt"          ) );
  ptWMuMinus_ .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWMuons"+jetMultiplicity+"/ptMinus"     ) );
  ptWMuPlus_  .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWMuons"+jetMultiplicity+"/ptPlus"      ) );
  ptMu_       .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryMuons"+jetMultiplicity+"/pt"           ) );
  ptMuMinus_  .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryMuons"+jetMultiplicity+"/ptMinus"      ) );
  ptMuPlus_   .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryMuons"+jetMultiplicity+"/ptPlus"       ) );
  ptWE_       .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWElectrons"+jetMultiplicity+"/pt"      ) );
  ptWEMinus_  .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWElectrons"+jetMultiplicity+"/ptMinus" ) );
  ptWEPlus_   .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWElectrons"+jetMultiplicity+"/ptPlus"  ) );
  ptWT_       .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWTaus"+jetMultiplicity+"/pt"           ) );
  ptWTMinus_  .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWTaus"+jetMultiplicity+"/ptMinus"      ) );
  ptWTPlus_   .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWTaus"+jetMultiplicity+"/ptPlus"       ) );  
 
  std::vector<TH1F*> ptNMuPlus_, ptNMuMinus_, ptNEPlus_, ptNEMinus_, ptNTPlus_, ptNTMinus_; 
  TString mult="";
  for(int idx=0; idx<=4; ++idx) {
    if(idx==0) mult="";
    else {
      mult = "Njets"+(TString)getStringFromInt(idx);
    }
    ptNMuMinus_ .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWMuons"+mult+"/ptMinus"     ) );
    ptNMuPlus_  .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWMuons"+mult+"/ptPlus"      ) );
    ptNEMinus_  .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWElectrons"+mult+"/ptMinus" ) );
    ptNEPlus_   .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWElectrons"+mult+"/ptPlus"  ) );
    ptNTMinus_  .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWTaus"+mult+"/ptMinus"      ) );
    ptNTPlus_   .push_back( (TH1F*)files_[0]->Get("analyzeChargeAsymmetryWTaus"+mult+"/ptPlus"       ) );  
  }

  // --- 
  //    calculate charge asymmetry parameter R for different leptons in every pt(lepton)-bin
  // ---
  std::vector<TH1F*> Rparameters_;
  enum leptons{kWMuon, kWElectron, kWTau, kMuon, kallLeptons};
  Rparameters_ .push_back ( calcutateR(*ptWMuPlus_ [kWjets], *ptWMuMinus_ [kWjets], "Muons from W"         , jetMultiplicity) );
  Rparameters_ .push_back ( calcutateR(*ptWEPlus_  [kWjets], *ptWEMinus_  [kWjets], "Electrons from W"     , jetMultiplicity) );
  Rparameters_ .push_back ( calcutateR(*ptWTPlus_  [kWjets], *ptWTMinus_  [kWjets], "Taus from W"          , jetMultiplicity) );
  Rparameters_ .push_back ( calcutateR(*ptMuPlus_  [kWjets], *ptMuMinus_  [kWjets], "W->#mu & W->#tau->#mu", jetMultiplicity) );
  TH1F* allLeptonsPlus = (TH1F*)ptWMuPlus_[kWjets]->Clone();
  allLeptonsPlus->Add(ptWEPlus_[kWjets]);
  allLeptonsPlus->Add(ptWTPlus_[kWjets]);
  TH1F* allLeptonsMinus = (TH1F*)ptWMuMinus_[kWjets]->Clone();
  allLeptonsMinus->Add(ptWEMinus_[kWjets]);
  allLeptonsMinus->Add(ptWTMinus_[kWjets]);
  Rparameters_ .push_back ( calcutateR(*allLeptonsPlus, *allLeptonsMinus, "all Leptons from W", jetMultiplicity) );

  // --- 
  //    calculate inclusive R for all jet multiplicities and plot R_inclusive[N_jets]
  // ---
  // a)  read out entries for all jet multiplizities
  std::vector<double> positiveCharged_;
  std::vector<double> negativeCharged_;
  std::vector<double> positiveChargedBin2_;
  std::vector<double> negativeChargedBin2_;
  std::vector<double> positiveChargedBin3_;
  std::vector<double> negativeChargedBin3_;
  std::vector<double> positiveChargedBin4_;
  std::vector<double> negativeChargedBin4_;
  for(unsigned int idx=0; idx<ptNMuPlus_.size(); idx++){
    //    positiveCharged_ .push_back((double)(ptNMuPlus_[idx]->GetEntries()+ptNEPlus_[idx]->GetEntries()+ptNTPlus_[idx]->GetEntries()));
    //    negativeCharged_ .push_back((double)(ptNMuMinus_[idx]->GetEntries()+ptNEMinus_[idx]->GetEntries()+ptNTMinus_[idx]->GetEntries()));
    positiveCharged_ .push_back((double)( ptNMuPlus_ [idx]->GetEntries()-ptNMuPlus_ [idx]->GetBinContent(1) ));
    negativeCharged_ .push_back((double)( ptNMuMinus_[idx]->GetEntries()-ptNMuMinus_[idx]->GetBinContent(1) ));
    positiveChargedBin2_ .push_back((double)( ptNMuPlus_ [idx]->GetBinContent(2) ));
    negativeChargedBin2_ .push_back((double)( ptNMuMinus_[idx]->GetBinContent(2) ));
    positiveChargedBin3_ .push_back((double)( ptNMuPlus_ [idx]->GetBinContent(3) ));
    negativeChargedBin3_ .push_back((double)( ptNMuMinus_[idx]->GetBinContent(3) ));
    positiveChargedBin4_ .push_back((double)( ptNMuPlus_ [idx]->GetBinContent(4) ));
    negativeChargedBin4_ .push_back((double)( ptNMuMinus_[idx]->GetBinContent(4) ));
  }
  // b)  calculate inclusive R and its error
  std::vector< std::vector<double> > RNjets_, RNjetsBin2_, RNjetsBin3_, RNjetsBin4_;
  for(unsigned int idx=0; idx<ptNMuPlus_.size(); idx++){
    RNjets_ .push_back(calcutateTotalR(positiveCharged_[idx], negativeCharged_[idx], "muon from W, pt>20GeV" , "Njets"+(TString)getStringFromInt(idx)));
    RNjetsBin2_ .push_back(calcutateTotalR(positiveChargedBin2_[idx], negativeChargedBin2_[idx], "muon from W, 20<pt<35GeV" , "Njets"+(TString)getStringFromInt(idx)));
    RNjetsBin3_ .push_back(calcutateTotalR(positiveChargedBin3_[idx], negativeChargedBin3_[idx], "muon from W, 35<pt<50GeV" , "Njets"+(TString)getStringFromInt(idx)));
    RNjetsBin4_ .push_back(calcutateTotalR(positiveChargedBin4_[idx], negativeChargedBin4_[idx], "muon from W, 50<pt<70GeV" , "Njets"+(TString)getStringFromInt(idx)));
  }
  // c)  create R[Njets]-plot
  TH1F* RNjets     = new TH1F("RNjets"    , "RNjets"    , 5, -0.5, 4.5);
  TH1F* RNjetsBin2 = new TH1F("RNjetsBin2", "RNjetsBin2", 5, -0.5, 4.5);
  TH1F* RNjetsBin3 = new TH1F("RNjetsBin3", "RNjetsBin3", 5, -0.5, 4.5);
  TH1F* RNjetsBin4 = new TH1F("RNjetsBin4", "RNjetsBin4", 5, -0.5, 4.5);
  for(unsigned idx=0; idx<ptNMuPlus_.size(); idx++){
    RNjets    ->SetBinContent(idx+1, (RNjets_    [idx])[0]);
    RNjets    ->SetBinError  (idx+1, (RNjets_    [idx])[1]);
    RNjetsBin2->SetBinContent(idx+1, (RNjetsBin2_[idx])[0]);
    RNjetsBin2->SetBinError  (idx+1, (RNjetsBin2_[idx])[1]);
    RNjetsBin3->SetBinContent(idx+1, (RNjetsBin3_[idx])[0]);
    RNjetsBin3->SetBinError  (idx+1, (RNjetsBin3_[idx])[1]);
    RNjetsBin4->SetBinContent(idx+1, (RNjetsBin4_[idx])[0]);
    RNjetsBin4->SetBinError  (idx+1, (RNjetsBin4_[idx])[1]);
  }
  
  // ---
  //    create legends 
  // ---
  // create a legend for event plots
  TLegend *leg0 = new TLegend(0.42, 0.51, 1.00, 0.87);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("W+jets (MADGRAPH), 406 pb^{-1}");
  leg0->AddEntry(ptWMu_[kWjets]       , "all #mu  (status3)" , "PL");
  leg0->AddEntry(ptWE_ [kWjets]       , "all e (status3)"    , "PL");
  leg0->AddEntry(ptWT_ [kWjets]       , "all #tau (status3)" , "PL");
  leg0->AddEntry(ptWMuPlus_  [kWjets] , "#mu^{+} (status3)"  , "PL");
  leg0->AddEntry(ptWMuMinus_ [kWjets] , "#mu^{-} (status3)"  , "PL");
  //  leg0->AddEntry(ptWEPlus_   [kWjets] , "e^{+}"    , "PL");
  //  leg0->AddEntry(ptWEMinus_  [kWjets] , "e^{-}"    , "PL");
  //  leg0->AddEntry(ptWTPlus_   [kWjets] , "#tau^{+}" , "PL");
  //  leg0->AddEntry(ptWTMinus_  [kWjets] , "#tau^{-}" , "PL");
  //leg0->AddEntry(ptMu_      [kWjets] , "#mu  & #tau ->#mu   (status1)"        , "PL");
  //leg0->AddEntry(ptMuPlus_  [kWjets] , "#mu^{+} & #tau^{+}->#mu^{+} (status1)"  , "PL");
  //leg0->AddEntry(ptMuMinus_ [kWjets] , "#mu^{-} & #tau^{-}->#mu^{-} (status1)"  , "PL");

   // create a legend for R[Njets]
  TLegend *leg1 = new TLegend(0.25, 0.70, 1.0, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("R(MC gen (W->#mu#nu)+jets MADGRAPH)");
  leg1->AddEntry(RNjets,"                p_{t} (#mu) > 20 GeV, |#eta| < #infty", "PL");
  leg1->AddEntry(RNjetsBin2, "20 GeV > p_{t} (#mu) > 35 GeV, |#eta| < #infty"  , "PL");
  leg1->AddEntry(RNjetsBin3, "35 GeV > p_{t} (#mu) > 50 GeV, |#eta| < #infty"  , "PL");
  leg1->AddEntry(RNjetsBin4, "50 GeV > p_{t} (#mu) > 70 GeV, |#eta| < #infty"  , "PL");

  // create a legend for assymetrie parameter
  TLegend *leg2 = new TLegend(0.21, 0.63, 0.99, 0.87);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetHeader("R_{c.a. MC}: W+jets(MADGRAPH), 406 pb^{-1}");
  leg2->AddEntry(Rparameters_[kWMuon     ], "#mu from W (gen)"         , "P");
  //  leg2->AddEntry(Rparameters_[kWElectron ], "e from W (gen)"           , "P");
  //  leg2->AddEntry(Rparameters_[kWTau      ], "#tau from W (gen)"        , "P");
  //  leg2->AddEntry(Rparameters_[kallLeptons], "all leptons from W (gen)" , "P");
  leg2->AddEntry(Rparameters_[kMuon      ], "W->#mu & W->#tau->#mu"    , "P");

  // create a legend for used jetCut
  TLegend *leg3 = new TLegend(0.23, 0.85, 0.62, 0.97);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  if(jetMultiplicity!="")  leg3->SetHeader("selection: "+jetMultiplicity+"+");
  else leg3->SetHeader("no jet selection");

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
  //    do the printing for pt, ptMuPlus and ptMuMinus (Wjets, different kind of leptons)
  // ---
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetTitle("ptLepChargeWjets"+jetMultiplicity);
  axesStyle(*ptWMu_ [kWjets], "p_{t} ( gen lep ) [GeV]", "events", 1, 1.4*ptWE_ [kWjets]->GetMaximum(), 0.06, 1.5 );
  histogramStyle(*ptWMu_      [kWjets], kRed ,  1, 21, 1.5);
  histogramStyle(*ptWMuPlus_  [kWjets], kRed ,  2, 21, 1.5);
  histogramStyle(*ptWMuMinus_ [kWjets], kRed ,  9, 21, 1.5);
  histogramStyle(*ptMu_       [kWjets], kBlue,  1, 20, 1.5);
  histogramStyle(*ptMuPlus_   [kWjets], kBlue,  2, 20, 1.5);
  histogramStyle(*ptMuMinus_  [kWjets], kBlue,  9, 20, 1.5);
  histogramStyle(*ptWE_       [kWjets], kBlue,  1, 22, 1.5);
  histogramStyle(*ptWEPlus_   [kWjets], kBlue,  2, 22, 1.5);
  histogramStyle(*ptWEMinus_  [kWjets], kBlue,  9, 22, 1.5);
  histogramStyle(*ptWT_       [kWjets], kGreen, 1, 23, 1.65);
  histogramStyle(*ptWTPlus_   [kWjets], kGreen, 2, 23, 1.65);
  histogramStyle(*ptWTMinus_  [kWjets], kGreen, 9, 23, 1.65);
  ptWMu_     [kWjets]->Draw("");
  ptWMu_     [kWjets]->Draw("esame");
  //  ptMu_      [kWjets]->Draw("same");
  //  ptMu_      [kWjets]->Draw("esame");
  ptWMuPlus_ [kWjets]->Draw("same" );
  ptWMuPlus_ [kWjets]->Draw("esame");
  ptWMuMinus_[kWjets]->Draw("same" );
  ptWMuMinus_[kWjets]->Draw("esame");
//   ptMuPlus_  [kWjets]->Draw("same" );
//   ptMuPlus_  [kWjets]->Draw("esame");
//   ptMuMinus_ [kWjets]->Draw("same" );
//   ptMuMinus_ [kWjets]->Draw("esame");
  ptWT_      [kWjets]->Draw("same" );
  ptWT_      [kWjets]->Draw("esame");
  ptWE_      [kWjets]->Draw("same" );
  ptWE_      [kWjets]->Draw("esame");
//   ptWTPlus_  [kWjets]->Draw("same" );
//   ptWTPlus_  [kWjets]->Draw("esame");
//   ptWTMinus_ [kWjets]->Draw("same" );
//   ptWTMinus_ [kWjets]->Draw("esame");
//   ptWEPlus_  [kWjets]->Draw("same" );
//   ptWEPlus_  [kWjets]->Draw("esame");
//   ptWEMinus_ [kWjets]->Draw("same" );
//   ptWEMinus_ [kWjets]->Draw("esame");
  leg0               ->Draw("same" );
  leg3               ->Draw("same" );

  // ---
  //    do the printing for the asymmetry parameter
  // ---
  MyCanvas[1]->cd(0);
  MyCanvas[1]->SetTitle("chargeAsymmetrieParameterWjets"+jetMultiplicity);
  axesStyle(*Rparameters_[kWMuon], "p_{t} ( tight #mu ) [GeV]", "R = #frac{N_{W^{+}} + N_{W^{-}}}{N_{W^{+}} - N_{W^{-}}}", 0, 45, 0.05, 1.5);  
  histogramStyle(*Rparameters_[kWMuon     ], kRed  , 1, 2, 2.2);
  histogramStyle(*Rparameters_[kWElectron ], 46    , 1, 2, 2.2);
  histogramStyle(*Rparameters_[kWTau      ], kGreen, 1, 2, 2.2);
  histogramStyle(*Rparameters_[kMuon      ], kBlue , 1, 2, 2.2);
  histogramStyle(*Rparameters_[kallLeptons], kBlack, 1, 2, 2.2);
  Rparameters_[kWMuon     ]->Draw("");
  //  Rparameters_[kWElectron ]->Draw("same");
  //  Rparameters_[kWTau      ]->Draw("same");
  Rparameters_[kMuon      ]->Draw("same");
  //  Rparameters_[kallLeptons]->Draw("same");
  leg2                     ->Draw("same");
  leg3                     ->Draw("same");


  // ---
  //    do the printing for R[Njets]
  // ---
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetTitle("chargeAsymmetrieParameterInclusiveNjetsWjets");
  axesStyle(*RNjets, "N_{jets} #geq", "R = #frac{N_{W^{+}} + N_{W^{-}}}{N_{W^{+}} - N_{W^{-}}}", 0, 20, 0.05, 1.5);
  histogramStyle(*RNjets    , kBlack, 1, 8, 1.0);
  histogramStyle(*RNjetsBin2, kBlue , 1, 8, 1.0);
  histogramStyle(*RNjetsBin3,     8 , 1, 8, 1.0);
  histogramStyle(*RNjetsBin4, kRed  , 1, 8, 1.0);
  RNjets->Draw("");
  RNjetsBin2->Draw("same");
  RNjetsBin3->Draw("same");
  RNjetsBin4->Draw("same");
  leg1->Draw("same");

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

TH1F* calcutateR(TH1F& ptPlus, TH1F& ptMinus, TString label, TString jetMultiplicity){
  // calculate charge asymmetrie parameter
  // for ptMinus and ptPlus

  std::vector<double> parameter_;
  std::vector<double> parameterError_;
  double x=0;
  double y=0;

  std::cout << "----------------------------------------" << std::endl;
  std::cout << "charge assymmetrie parameter for "+label  << std::endl;
  std::cout << "---------"+jetMultiplicity+"------------------------" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
  for(int i=2; i<= ptPlus.GetNbinsX(); i++){
    x = ((double)(ptMinus.GetBinContent(i))) /  ((double)(ptPlus.GetBinContent(i)));
    parameter_.push_back( (1.0 + x) / (1.0 -x) );
  }
  // ---
  //    calculate error via gaussian error calculus
  // ---
  for(int i=2; i<= ptPlus.GetNbinsX(); i++){
    x = 1.0 / ( (double)(ptPlus.GetBinContent(i)) - (double)(ptMinus.GetBinContent(i)) );
    y = ( (double)(ptPlus.GetBinContent(i)) + (double)(ptMinus.GetBinContent(i)) ) / (  ( (double)(ptPlus.GetBinContent(i)) - (double)(ptMinus.GetBinContent(i)) ) * ( (double)(ptPlus.GetBinContent(i)) - (double)(ptMinus.GetBinContent(i)) )  );
    parameterError_.push_back(  sqrt( ((x-y)*(x-y))*(double)(ptPlus.GetBinContent(i)) + ((x+y)*(x+y))*(double)(ptMinus.GetBinContent(i)) )  );
    std::cout << "bin " << i << ": " << parameter_[i-2] << " +/- " << parameterError_[i-2] << std::endl;
  }

  // create histogram with assymetrie parameter as clone
  TH1F *asymmetrieParameter= (TH1F*) ptPlus.Clone();

  // use calculated entries
  for(int i=2; i<= ptPlus.GetNbinsX(); i++){
    asymmetrieParameter->SetBinContent( i, parameter_[i-2] );
    asymmetrieParameter->SetBinError  ( i, parameterError_[i-2] );
  }
  return asymmetrieParameter;
}


std::vector<double> calcutateTotalR(double ptPlus, double ptMinus, TString label, TString jetMultiplicity){
  // calculate charge asymmetrie parameter
  // for ptMinus and ptPlus which correspond 
  // to the total number of negative and 
  // positive charged lepton
  
  double parameter;
  double parameterError;
  double x=0;
  double y=0;

  std::cout << "----------------------------------------" << std::endl;
  std::cout << "inclusive R for "+label                   << std::endl;
  std::cout << "---------"+jetMultiplicity+"--------------------" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
  x = ptMinus/ptPlus;
  parameter= (1.0 + x) / (1.0 -x) ; 
  x = 1.0 / (ptPlus - ptMinus);
  y = ( ptPlus + ptMinus ) / (  ( ptPlus - ptMinus ) * ( ptPlus - ptMinus )  );
  parameterError= sqrt( ((x-y)*(x-y))*ptPlus + ((x+y)*(x+y))*ptMinus );
  std::cout << "R = " << parameter << " +/- " << parameterError << std::endl;
  std::vector<double> output_;
  output_.push_back(parameter);
  output_.push_back(parameterError);
  return output_;
}

string getStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return result;
}
