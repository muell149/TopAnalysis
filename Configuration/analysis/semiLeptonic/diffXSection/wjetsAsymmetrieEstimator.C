
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
#include <fstream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <THStack.h>
#include <TLine.h>
#include <TStyle.h>
#include <TF1.h>

enum styles {kWjets, kPseudo50, kData, kTtbar};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void drawcutline(double cutval, double maximum);
std::pair<double,double> getChargeAsymmetrieParameter(int njets, bool loadR);
TString getTStringFromInt(int i);
double sumUpEntries(TH1F& histo);
template <class T>
void writeToFile(T output, TString file="crossSectionCalculationPF.txt", bool append=1);
double readLineFromFile(int line, TString file="crossSectionCalculationPF.txt");

void wjetsAsymmetrieEstimator(double luminosity = 36.1, bool save = false, bool textoutput=true, TString dataFile="./diffXSecFromSignal/data/DiffXSecData_Nov15PF.root", TString jetType = "PF")
{
  // ---
  //    main function parameters
  // ---
  // save:       choose whether you want to save every plot as png and all within one ps file
  // textoutput: choose whether you want to save the estimated number of QCD events for data 
  //             in .txt file to share it with other parts of the Analysis
  // luminosity: choose luminosity for scaling of event numbers 
  //             lum is derived from this and used for legend as entry
  TString lum = getTStringFromInt((int)luminosity);
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/chargeAsymmetrie/";
  // choose whether you want to load c.a. parameter from crossSection.txt file
  // when writing into file, R is also taken from file
  bool loadR = false;
  if(textoutput) loadR=true;
  TString file = "crossSectionCalculation"+jetType+".txt";
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
  TString whichSample = "/analysisRootFiles";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecWjetsMadD6TFall10"+jetType+".root"      ) );
  files_.push_back(new TFile("./diffXSecFromSignal/spring10Samples/spring10SelV2Sync/spring10PseudoData7TeV50pb.root" ) );
  files_.push_back(new TFile(dataFile                                                                                 ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecAllMadD6TFall10"+jetType+".root"        ) );
  //files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecAllNloSpring10.root"     ) );

  // create container for the different histos
  std::map< TString, std::map <unsigned int, TH1F*> > ptMuPlus_, ptMuMinus_, pt_;
  // example: ptMuPlus_[kWjets]["Njets1"]
  // ------------------------------------
  // create jet multiplicity indicator
  std::vector<TString> Njets_;
  TString jets[ 4 ] = { "Njets1", "Njets2", "Njets3", "Njets4" };
  Njets_.insert( Njets_.begin(), jets, jets + 4 );

  // ---
  //    get histograms
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<4; ++mult){
    // loop input files (W, all MC, data)
    for(int idx=kWjets; idx<=kTtbar; ++idx){
      // pt(mu+/-)
      ptMuPlus_ [Njets_[mult]][idx] = (TH1F*)(files_[idx]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/ptPlus" ))->Clone();
      ptMuMinus_[Njets_[mult]][idx] = (TH1F*)(files_[idx]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/ptMinus"))->Clone();
      // pt(all mu) as mu+ + mu-
      pt_[Njets_[mult]][idx] = (TH1F*)ptMuPlus_ [Njets_[mult]][idx]->Clone();
      pt_[Njets_[mult]][idx]->Add( (TH1F*)ptMuMinus_[Njets_[mult]][idx]->Clone() ); 
    }
  }
    
  // ---
  //    scale W+jets to luminosity
  // ---
  // a) fall10 7TeV W+jets MADGRAPH D6T sample 
  double lumiweight=0.105750913/50*luminosity;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<4; ++mult){
    ptMuPlus_ [Njets_[mult]][kWjets]->Scale(lumiweight);
    ptMuMinus_[Njets_[mult]][kWjets]->Scale(lumiweight);
    pt_       [Njets_[mult]][kWjets]->Scale(lumiweight);
  }
  // b) fall10 7TeV TTbar MADGRAPH D6T sample
  double lumiweight2=0.006029022/50*luminosity;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<4; ++mult){
    ptMuPlus_ [Njets_[mult]][kTtbar]->Scale(lumiweight2);
    ptMuMinus_[Njets_[mult]][kTtbar]->Scale(lumiweight2);
    pt_       [Njets_[mult]][kTtbar]->Scale(lumiweight2);
  }

  // check weighting
  std::cout << "" << std::endl;
  std::cout << "check weighting W+jets MC (Njets>=4)" << std::endl;
  std::cout << "N(W) before weighting: " <<  pt_[Njets_[3]][kWjets]->GetEntries() << std::endl;
  double weightedEntries = sumUpEntries(*pt_[Njets_[3]][kWjets]);
  std::cout << "N(W) after weighting: " << weightedEntries << std::endl;
  std::cout << "ratio : " << weightedEntries/(double)(pt_[Njets_[3]][kWjets]->GetEntries()) << std::endl;
  std::cout << "weight: " << lumiweight << std::endl;

  // check pseudo data read out
  std::cout << "" << std::endl;
  std::cout << "check pseudo data N(jets)>=4" << std::endl;
  std::cout << "N = "  << sumUpEntries(*pt_       [Njets_[3]][kPseudo50]) << std::endl;
  std::cout << "N+ = " << sumUpEntries(*ptMuPlus_ [Njets_[3]][kPseudo50]) << std::endl;
  std::cout << "N- = " << sumUpEntries(*ptMuMinus_[Njets_[3]][kPseudo50]) << std::endl;

  // print out important informations
  std::cout << std::endl << "w+jets estimation details:" << std::endl;
  std::cout << "- used R(pt(mu)>=20 GeV) from W->(mu && tau->mu)+jets gen niveau" << std::endl;
  std::cout << "- R is expected to have no error" << std::endl;
  std::cout << "- to test the method, the estimation is done from combined pseudo"  << std::endl;
  std::cout << "  data reco files (wjets+zjets+qcd+ttbar)" << std::endl;
  std::cout << "  and from W+jets sample only" << std::endl;
  std::cout << "- additionally the estimation is done for real data" << std::endl<< std::endl;

  // ---
  //    Apply the charge asymmetry method
  // ---
  // create c.a. estimation, MC truth and all events [N(jets)] histos
  TH1F *wjetsEstimationW   = new TH1F("wjetsEstimationW"   , "wjetsEstimationW"  , 4, 0.5, 4.5);
  TH1F *wjetsEstimationAll = new TH1F("wjetsEstimationAll" , "wjetsEstimationAll", 4, 0.5, 4.5);
  TH1F *wjetsTruth         = new TH1F("wjetsTruth"         , "wjetsTruth"        , 4, 0.5, 4.5);
  TH1F *allPseudoEvents    = new TH1F("allPseudoEvents"    , "allPseudoEvents"   , 4, 0.5, 4.5);
  TH1F *wjetsData          = new TH1F("wjetsData"          , "wjetsData"         , 4, 0.5, 4.5);
  // loop samples (W+jets, pseudo data, real data)
  for(unsigned int idx=kWjets; idx<=kData; ++idx){
    // print out info for c.a. estimation
    if(idx==kWjets   )std::cout << std::endl << "a) estimation from W+jets MC only:"       << std::endl << std::endl;
    if(idx==kPseudo50)std::cout << std::endl << "b) estimation from pseudo data (all MC):" << std::endl << std::endl;
    if(idx==kData    )std::cout << std::endl << "c) estimation within data:"               << std::endl << std::endl;
    // loop jet multiplicities
    for(int njets=1; njets<=4; ++njets){
      // a) charge asymmetry estimation
      std::cout << "---------------------" << std::endl << std::endl;
      std::cout << "N(jets) >= " << njets  << std::endl; 
      std::cout << "" << std::endl;
      double x = sumUpEntries(*ptMuPlus_ [Njets_[njets-1]][idx]);
      double y = sumUpEntries(*ptMuMinus_[Njets_[njets-1]][idx]);
      double R =getChargeAsymmetrieParameter(njets,loadR).first;
      double dR=getChargeAsymmetrieParameter(njets,loadR).second;
      // calculate entries for W+jets-estimation
      double NW = (x-y)*R;
      // calculate error for W+jets-estimation via gaussian error calculus
      double NWError = R*sqrt(NW);
      // print out results
      std::cout << "N(mu+)= "  << x << std::endl;
      std::cout << "N(mu-)= "  << y << std::endl;
      std::cout << "R(Njets >=" << njets << ") = " << R << " +- " << dR << std::endl;
      std::cout << "N(estimated W) = " << NW << " +- " << NWError << std::endl;
      std::cout << "N(W, MC truth) = "   << sumUpEntries(*pt_[Njets_[njets-1]][kWjets]) << std::endl;
      double ratio = NW/sumUpEntries(*pt_[Njets_[njets-1]][kWjets]);
      if(idx==kData) std::cout << "ratio NWest/NWMC = " << ratio << std::endl;
      std::cout << "total # of events: " << sumUpEntries(*pt_[Njets_[njets-1]][idx])    << std::endl;
      // b) fill wjetsEstimationW histo
      if(idx==kWjets){
	wjetsEstimationW->SetBinContent( njets, NW);
	wjetsEstimationW->SetBinError  ( njets, NWError);
      }
      // c) fill wjetsEstimationAll histo
      if(idx==kPseudo50){
	wjetsEstimationAll->SetBinContent( njets, NW);
	wjetsEstimationAll->SetBinError  ( njets, NWError);
      }
      // d) fill wjetsTruth histo
      if(idx==kWjets) wjetsTruth->SetBinContent( njets, sumUpEntries(*pt_[Njets_[njets-1]][kWjets]) );
      // e) fill allPseudoEvents histo
      if(idx==kPseudo50) allPseudoEvents->SetBinContent( njets, ratio );
      // f) fill data estimation histo
      if(idx==kData) wjetsData->SetBinContent( njets, sumUpEntries(*pt_[Njets_[njets-1]][kPseudo50]) );
      // g) if textoutput==true: save W+jets data estimation within .txt-file
      if(textoutput==true&&idx==kData){
	if(njets==1) writeToFile("estimated N(W) in Data using charge asymmetry method with R from above for N(jets) >= 1 - 4",file);
	writeToFile((x-y)*R,file); 
      }
    }
  }

  // ---
  //    create legends 
  // ---
  // create a legend for estimation
  TLegend *leg0 = new TLegend(0.30, 0.69, 0.92, 0.94);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("N_{W} @ "+lum+" pb^{-1} ( 7 TeV )");
  leg0->AddEntry( wjetsTruth        , "MC truth"                            , "L" );
  leg0->AddEntry( wjetsEstimationW  , "estimation from W#rightarrowl#nu MC" , "PL");
  leg0->AddEntry( wjetsEstimationAll, "estimation from pseudo data (all MC)", "PL");
  //  leg0->AddEntry( allPseudoEvents   , "total # pseudo events"               , "L" );

  // create a legend for mu, mu+ and mu- of Ttar
  TLegend *leg1 = new TLegend(0.47, 0.68, 1.0, 0.93);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("t#bar{t}: "+lum+" pb^{-1}, N(jets) #geq 1"   );
  leg1->AddEntry( pt_       [Njets_[0]][kTtbar], "all #mu" , "L");
  leg1->AddEntry( ptMuPlus_ [Njets_[0]][kTtbar], "#mu^{+}" , "L");
  leg1->AddEntry( ptMuMinus_[Njets_[0]][kTtbar], "#mu^{-}" , "L");

  // create a legend for mu, mu+ and mu- of Ttar
  TLegend *leg2 = new TLegend(0.47, 0.68, 1.0, 0.93);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetHeader("W+jets: "+lum+" pb^{-1}, N(jets) #geq 1"     );
  leg2->AddEntry( pt_       [Njets_[0]][kWjets], "all #mu" , "L");
  leg2->AddEntry( ptMuPlus_ [Njets_[0]][kWjets], "#mu^{+}" , "L");
  leg2->AddEntry( ptMuMinus_[Njets_[0]][kWjets], "#mu^{-}" , "L");

  // ---
  //    do the printing for N_W [Njets]
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  canv0->SetTitle("wjetsCAEstimation"+lum+"pb");
  axesStyle(*wjetsTruth, "N_{jets} #geq", "N_{W}", 1., 10000000/50*luminosity);
  histogramStyle(*wjetsTruth        , kGreen, 1, 20, 0.5); 
  histogramStyle(*wjetsEstimationW  , kBlue , 1, 23, 1.8);
  histogramStyle(*wjetsEstimationAll, kRed  , 1, 22, 1.8);
  histogramStyle(*allPseudoEvents   , kBlack, 2, 20, 0.5); 
  wjetsTruth        ->Draw("");
  //  allPseudoEvents   ->Draw("same");
  wjetsEstimationAll->Draw("esame");
  wjetsEstimationW  ->Draw("esame");
  leg0              ->Draw("same");

  // ---
  //    do the printing for mu, mu+ and mu- for Top and W+jets
  // ---
  // a ) Top
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);
  // draw canvas
  canv1->cd(0);
  canv1->SetTitle("TopNjets1MuonCharge"+lum+"pb");
  axesStyle(*pt_[Njets_[0]][kTtbar], "p_{t} (#mu)", "N_{t#bar{t}}", 0., 1.2*pt_[Njets_[0]][kTtbar]->GetMaximum(), 0.05, 1.3);
  histogramStyle(*ptMuPlus_ [Njets_[0]][kTtbar], kBlue , 2, 20, 0.5); 
  histogramStyle(*ptMuMinus_[Njets_[0]][kTtbar], kRed  , 3, 20, 0.5); 
  histogramStyle(*pt_       [Njets_[0]][kTtbar], kBlack, 1, 20, 0.5);
  pt_       [Njets_[0]][kTtbar]->Draw("");
  ptMuMinus_[Njets_[0]][kTtbar]->Draw("same");
  ptMuPlus_ [Njets_[0]][kTtbar]->Draw("same");
  leg1                         ->Draw("same");

  // b ) W+jets
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);
  // draw canvas
  canv2->cd(0);
  canv2->SetTitle("WjetsNjets1MuonCharge"+lum+"pb");
  axesStyle(*pt_[Njets_[0]][kWjets], "p_{t} (#mu)", "N_{W}", 0., 1.2*pt_[Njets_[0]][kWjets]->GetMaximum(), 0.05, 1.3);
  histogramStyle(*ptMuPlus_ [Njets_[0]][kWjets], kBlue , 2, 20, 0.5); 
  histogramStyle(*ptMuMinus_[Njets_[0]][kWjets], kRed  , 3, 20, 0.5); 
  histogramStyle(*pt_       [Njets_[0]][kWjets], kBlack, 1, 20, 0.5);
  pt_       [Njets_[0]][kWjets]->Draw("");
  ptMuMinus_[Njets_[0]][kWjets]->Draw("same");
  ptMuPlus_ [Njets_[0]][kWjets]->Draw("same");
  leg2                         ->Draw("same");

  // ---
  // saving
  // ---

  if(save){
    // ps
    canv0->Print(saveTo+"chargeAsymmetrieEstimation.ps(" );
    canv1->Print(saveTo+"chargeAsymmetrieEstimation.ps"  );
    canv2->Print(saveTo+"chargeAsymmetrieEstimation.ps)" );
    // png
    canv0->Print(saveTo+(TString)(canv0->GetTitle())+".png");
    canv1->Print(saveTo+(TString)(canv1->GetTitle())+".png");
    canv2->Print(saveTo+(TString)(canv2->GetTitle())+".png");
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

TString getTStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return (TString)result;
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

std::pair<double,double> getChargeAsymmetrieParameter(int njets, bool loadR)
{
  // use R like it is written down here or load it from file
  if( loadR) return make_pair( readLineFromFile(2+njets) , 0 );
  std::map< TString, std::map <unsigned int, std::pair<double,double> > > Rinclusive_;
  Rinclusive_["mu"][1] = make_pair( 5.83643 , 0);
  Rinclusive_["mu"][2] = make_pair( 5.43496 , 0);
  Rinclusive_["mu"][3] = make_pair( 5.03349 , 0);
  Rinclusive_["mu"][4] = make_pair( 4.63202 , 0); 
  return Rinclusive_["mu"][njets];
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

double readLineFromFile(int line, TString file){
  // introduce function to read a double value drom a specific line of a file
  std::ifstream finDouble (file);
  std::string readIn;
  // check if file exists
  if (!finDouble){
    std::cout << "can not open file" << std::endl;
    return -1;
  }
  // loop lines of the file
  for(int l=1; !finDouble.eof(); ++l){
    // save line content in readIn
    getline(finDouble, readIn);
    // convert your chosen line into double and return it
    if(l==line) return atof(readIn.c_str()); 
  }
  // if line is not found
  std::cout << "can not find line" << std::endl;
  return -1.;  
}
