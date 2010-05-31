
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

enum styles {kPseudo50, kPseudo100, kWjets, kWjets100};

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

  // choose jet multiplicity you want to see: "Njets1" / "Njets2" / "Njets3" / "Njets4"
  TString multiplicity ="Njets1";
  // choose whether you want to save every plot as png and all within one ps file
  bool save = false;
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/chargeAsymmetrie/";
 
  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/spring10Samples/recoAndGenFromPATtuplesWithSummer09JEC";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/spring10PseudoData7TeV50pb.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/spring10PseudoData7TeV100pb.root") );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecWjetsMadSpring10.root"   ) );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> pt_, ptMuPlus_, ptMuMinus_;
  for(unsigned int idx=kPseudo50; idx<=kPseudo100; ++idx) {
    ptMuMinus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+multiplicity+"/ptMinus" ) );
    ptMuPlus_  .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+multiplicity+"/ptPlus"  ) );
  }
  for(unsigned int idx=kWjets; idx<files_.size(); ++idx) {
    ptMuMinus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+multiplicity+"/ptMinus" ) );
    ptMuPlus_  .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+multiplicity+"/ptPlus"  ) );
  }

  // combine mu+ and mu- histos to inclusive mu 
  // a) for pseudo data
  pt_ .push_back(  (TH1F*)ptMuMinus_[kPseudo50 ]->Clone() );
  pt_  [kPseudo50] ->Add (ptMuPlus_ [kPseudo50 ]          );
  pt_ .push_back(  (TH1F*)ptMuMinus_[kPseudo100]->Clone() );
  pt_  [kPseudo100]->Add (ptMuPlus_ [kPseudo100]          );
  // b1) for W+jets (50pb-1)
  pt_        .push_back( (TH1F*)files_[kWjets]->Get("analyzeTightMuonCrossSectionRec"+multiplicity+"/pt") );
  // b2) W+jets for 100 pb-1 estimate
  pt_        .push_back( (TH1F*)files_[kWjets]->Get("analyzeTightMuonCrossSectionRec"+multiplicity+"/pt") );
  ptMuMinus_ .push_back( (TH1F*)files_[kWjets]->Get("analyzeTightMuonCrossSectionRec"+multiplicity+"/ptMinus") );
  ptMuPlus_  .push_back( (TH1F*)files_[kWjets]->Get("analyzeTightMuonCrossSectionRec"+multiplicity+"/ptPlus" ) );

  // ---
  //    scale Wjets to luminosity
  // ---
  // spring10 7TeV W+jets MADGRAPH sample 
  double lumiweight=0.13904207;
  // 50 pb^{-1}
  pt_       [kWjets]->Scale(lumiweight);
  ptMuMinus_[kWjets]->Scale(lumiweight);
  ptMuPlus_ [kWjets]->Scale(lumiweight);
  // 100 pb^{-1}
  pt_       [kWjets100]->Scale(lumiweight*2);
  ptMuMinus_[kWjets100]->Scale(lumiweight*2);
  ptMuPlus_ [kWjets100]->Scale(lumiweight*2);

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
  TH1F *ptWjetsEstimation   = (TH1F*) pt_[kPseudo50 ]->Clone();
  TH1F *ptWjetsEstimation100= (TH1F*) pt_[kPseudo100]->Clone();

  // calculate entries for Wjets-estimation
  for(int i=2; i<= pt_[kPseudo50]->GetNbinsX(); i++){
    ptWjetsEstimation->SetBinContent(  i, parameter_[i-2]* ((double)ptMuPlus_[kPseudo50]->GetBinContent(i) - (double)ptMuMinus_[kPseudo50]->GetBinContent(i))  );
    ptWjetsEstimation100->SetBinContent(  i, parameter_[i-2]* ((double)ptMuPlus_[kPseudo100]->GetBinContent(i) - (double)ptMuMinus_[kPseudo100]->GetBinContent(i))  );
  }
  
  // ---
  //    calculate error via gaussian error calculus
  // ---
  std::vector<double> estimationError_;
  std::vector<double> estimationError100_;
  double x=0;
  double y=0;
 
  // a) 50 pb-1
  std::cout << "------------------------------------" << std::endl;
  std::cout << "W+jets background estimation "+multiplicity+"^{+}, 50pb^{-1}" << std::endl;
  std::cout << "------------------------------------" << std::endl;

  for(int i=2; i<= ptWjetsEstimation->GetNbinsX(); i++){
    x = (double)(ptMuPlus_ [kPseudo50]->GetBinContent(i));
    y = (double)(ptMuMinus_[kPseudo50]->GetBinContent(i));
    estimationError_.push_back(  sqrt( (x-y)*(x-y)*parameterError_[i-2]*parameterError_[i-2] + parameter_[i-2]*parameter_[i-2]*(x+y) )  );
    
    std::cout << "estimation bin "    << i << ":   " <<  ptWjetsEstimation->GetBinContent(i) << " +/- " << estimationError_[i-2] << std::endl;
    std::cout << "( real # W events " <<      ": "   <<  pt_[kWjets]      ->GetBinContent(i) << " )"                             << std::endl;
    ptWjetsEstimation->SetBinError( i, estimationError_[i-2] );
   }

  // b) 100 pb-1
  std::cout << "------------------------------------" << std::endl;
  std::cout << "W+jets background estimation "+multiplicity+"^{+}, 100pb^{-1}" << std::endl;
  std::cout << "------------------------------------" << std::endl;

  for(int i=2; i<= ptWjetsEstimation100->GetNbinsX(); i++){
    x = (double)(ptMuPlus_ [kPseudo100]->GetBinContent(i));
    y = (double)(ptMuMinus_[kPseudo100]->GetBinContent(i));
    estimationError100_.push_back(  sqrt( (x-y)*(x-y)*parameterError_[i-2]*parameterError_[i-2] + parameter_[i-2]*parameter_[i-2]*(x+y) )  );
    
    std::cout << "estimation bin "    << i << ":   " <<  ptWjetsEstimation100->GetBinContent(i) << " +/- " << estimationError100_[i-2] << std::endl;
    std::cout << "( real # W events " <<      ": "   <<  pt_[kWjets100]      ->GetBinContent(i) << " )"                             << std::endl;
    ptWjetsEstimation100->SetBinError( i, estimationError100_[i-2] );
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

  // create a legend for estimation
  TLegend *leg2 = new TLegend(0.34, 0.63, 0.96, 0.88);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetHeader("100pb^{-1} @ #sqrt{s}=7TeV, "+multiplicity+"+"    );
  leg2->AddEntry( pt_[kPseudo100]      , "all pseudo data"      , "PL");
  leg2->AddEntry( ptWjetsEstimation100 , "estimated # (W+jets)" , "PL");
  leg2->AddEntry( ptWjetsEstimation100 , "from pseudo data"     , ""  );
  leg2->AddEntry( pt_[kWjets100]       , "real # (W+jets) (MC)" , "PL");

  // create a legend for pseudo data
  TLegend *leg3 = new TLegend(0.38, 0.65, 1.00, 0.89);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  leg3->SetHeader("100pb^{-1} @ #sqrt{s}=7TeV, "+multiplicity+"+"      );
  leg3->AddEntry( pt_[kPseudo100]       , "pseudo data all #mu"  , "PL");
  leg3->AddEntry( ptMuPlus_ [kPseudo100], "pseudo data #mu^{+}"  , "PL");
  leg3->AddEntry( ptMuMinus_[kPseudo100], "pseudo data #mu^{-}"  , "PL");

  // ---
  //    do the printing for pt_ (W-estimation via method and real fraction): 50 pb-1
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  // draw canvas
  canv0->cd(0);
  canv0->SetTitle("chargeAsymmetrieEstimationQuality50");
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
  //    do the printing for pt_ (W-estimation via method and real fraction): 100 pb-1
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);
  // draw canvas
  canv1->cd(0);
  canv1->SetTitle("chargeAsymmetrieEstimationQuality100");
  axesStyle(*pt_ [kWjets100], "p_{t} ( tight #mu ) [GeV]", "events", 0, 1.5*pt_ [kPseudo100]->GetMaximum(), 0.065, 1.5);
  histogramStyle(*pt_ [kWjets100], kBlue , 2); 
  histogramStyle(*pt_ [kPseudo100  ], kBlack, 1, 22, 1.2);
  histogramStyle(*ptWjetsEstimation100, kRed  , 1, 22, 1.2);
  pt_ [kWjets100]     ->Draw("");
  ptWjetsEstimation100->Draw("same");
  pt_ [kPseudo100  ]  ->Draw("same");
  pt_ [kPseudo100  ]  ->Draw("esame");
  leg2                ->Draw("same");

  // ---
  //    do the printing for pt_ (pseudo data): 50 pb-1
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);
  // draw canvas
  canv2->cd(0);
  canv2->SetTitle("ptMuChargePseudoData");
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
  //    do the printing for pt_ (pseudo data): 100 pb-1
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);
  // draw canvas
  canv3->cd(0);
  canv3->SetTitle("ptMuChargePseudoData100");
  axesStyle(*pt_ [kPseudo100], "p_{t} ( tight #mu ) [GeV]", "events", 0., 1.4*pt_ [kPseudo100]->GetMaximum(), 0.065, 1.5);
  histogramStyle(*ptMuPlus_ [kPseudo100], kBlue , 1); 
  histogramStyle(*ptMuMinus_[kPseudo100], kRed  , 1); 
  pt_        [kPseudo100]->Draw("hist");
  pt_        [kPseudo100]->Draw("esame");
  ptMuPlus_  [kPseudo100]->Draw("esame");
  ptMuMinus_ [kPseudo100]->Draw("esame");
  ptMuPlus_  [kPseudo100]->Draw("histsame");
  ptMuMinus_ [kPseudo100]->Draw("histsame");
  leg3                   ->Draw("same");


  // ---
  // saving
  // ---

  if(save){
    // ps
    canv0->Print(saveTo+"chargeAsymmetrieEstimation50And100pbAt7TeV"+multiplicity+".ps(" );
    canv1->Print(saveTo+"chargeAsymmetrieEstimation50pAnd100bAt7TeV"+multiplicity+".ps"  );
    canv2->Print(saveTo+"chargeAsymmetrieEstimation50And100pbAt7TeV"+multiplicity+".ps"  );
    canv3->Print(saveTo+"chargeAsymmetrieEstimation50And100pbAt7TeV"+multiplicity+".ps)" );
    // png
    canv0->Print(saveTo+(TString)(canv0->GetTitle())+".png");
    canv1->Print(saveTo+(TString)(canv1->GetTitle())+".png");
    canv2->Print(saveTo+(TString)(canv1->GetTitle())+".png");
    canv3->Print(saveTo+(TString)(canv1->GetTitle())+".png");
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
  std::map< TString, std::map <TString,double> > R_;  
  // store values for charge asymmetrie parameter 
  // calculated within chargeAsymmetrieCalculator.C
  R_["2" ]["Njets4"]= 2.36134;   
  R_["3" ]["Njets4"]= 3.23129; 
  R_["4" ]["Njets4"]= 5.67647; 
  R_["5" ]["Njets4"]= 15.5;
  R_["all"]["Njets4"]= 4.18182;
			      
  R_["2" ]["Njets3"]= 2.52539;
  R_["3" ]["Njets3"]= 3.88462;
  R_["4" ]["Njets3"]= 7.576;
  R_["5" ]["Njets3"]= 22.56;
  R_["all"]["Njets3"]= 4.60473;
			      
  R_["2" ]["Njets2"]= 3.03971;
  R_["3" ]["Njets2"]= 5.08223;
  R_["4" ]["Njets2"]= 11.7044; 
  R_["5" ]["Njets2"]= 56.3673;
  R_["all"]["Njets2"]= 5.38754;
			      
  R_["2" ]["Njets1"]= 3.53238;
  R_["3" ]["Njets1"]= 5.88594;
  R_["4" ]["Njets1"]= 19.5745;
  R_["5" ]["Njets1"]= 146.354;
  R_["all"]["Njets1"]= 6.00053;

  // get maximum value
  return R_.find(bin)->second.find(Njets)->second;
}

double getErrorOfChargeAsymmetrieParameter(TString bin, TString Njets)
{
  // create container for histo max values sortet by plot and Njet
  std::map< TString, std::map <TString,double> > RErr_;  
  // store values for the error of the charge asymmetrie parameter 
  // calculated within chargeAsymmetrieCalculator.C
  RErr_["2" ]["Njets4"]= 0.213075;
  RErr_["3" ]["Njets4"]= 0.455559;
  RErr_["4" ]["Njets4"]= 1.61442;
  RErr_["5" ]["Njets4"]= 15.2241;
  RErr_["all"]["Njets4"]= 0.386314;

  RErr_["2" ]["Njets3"]= 0.10905;
  RErr_["3" ]["Njets3"]= 0.29617;
  RErr_["4" ]["Njets3"]= 1.30729;
  RErr_["5" ]["Njets3"]= 15.139;
  RErr_["all"]["Njets3"]= 0.214129;

  RErr_["2" ]["Njets2"]= 0.0643744;
  RErr_["3" ]["Njets2"]= 0.204546;
  RErr_["4" ]["Njets2"]= 1.34262; 
  RErr_["5" ]["Njets2"]= 42.7425;
  RErr_["all"]["Njets2"]= 0.123572;

  RErr_["2" ]["Njets1"]= 0.0351946 ;
  RErr_["3" ]["Njets1"]= 0.114295 ;
  RErr_["4" ]["Njets1"]= 1.46363 ;
  RErr_["5" ]["Njets1"]= 138.253;
  RErr_["all"]["Njets1"]= 0.0640639;
  // get maximum value
  return RErr_.find(bin)->second.find(Njets)->second;
}
