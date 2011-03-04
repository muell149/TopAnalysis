
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

void chargeAsymmetrieCalculator(bool save = false, bool textoutput=false, TString jetType = "PF")
{ 
  // ---
  //    main function parameters
  // ---
  // save:       choose whether you want to save every plot as eps and all within one ps file
  // textoutput: choose whether you want to save the estimated number of QCD events for data 
  //             in .txt file to share it with other parts of the Analysis
  // choose target directory for saving:
  TString saveTo = "./diffXSecFromSignal/plots/chargeAsymmetrie/";
  TString file = "crossSectionCalculation"+jetType+".txt";
  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetErrorX(0); 
  gStyle->SetEndErrorSize (8);

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/analysisRootFiles";
  files_.push_back( new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecWjetsMadD6TFall10"+jetType+".root") );
  //files_.push_back( new TFile("/afs/naf.desy.de/user/h/henderle/public/muonDiffXSecWjetsMadSpring10PF.root") );

  // ---
  //    get histograms
  // ---
  // create jet multiplicity indicator
  std::vector<TString> Njets_;
  TString jets[ 4 ] = { "Njets1", "Njets2", "Njets3", "Njets4" };
  Njets_.insert( Njets_.begin(), jets, jets + 4 );
  // mu+/- reco histos for all jet multiplicities 
  std::vector<TH1F*> ptNMuPlus_, ptNMuMinus_;
  for(int mult=0; mult<=3; ++mult) {
    ptNMuMinus_ .push_back( (TH1F*)files_[0]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/ptMinus") );
    ptNMuPlus_  .push_back( (TH1F*)files_[0]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/ptPlus" ) );
  }
 
  // --- 
  //    calculate charge asymmetry parameter R and errors
  // ---
  // a) R(ptmu) for different jet multiplicities and leptons
  // ----------------------------------------------------------------------------------------------
  // Rpt_[lepton][jetMultiplicity] -> eg: Rpt_[Wmu][4] = R(pt) for muons from W after >= 4 jets cut
  std::map< TString, std::map <unsigned int,TH1F* > > Rpt_;
  // loop jet multiplicities
  for(int njets =1; njets<=4; njets++){
    Rpt_["mu"][njets] = (TH1F*) calcutateR(*ptNMuPlus_[njets-1], *ptNMuMinus_[njets-1],  "Muons", "N(jets) >= "+getTStringFromInt(njets));
  }

  // b) inclusive R(ptmu>20GeV) for different jet multiplicities and leptons
  // ----------------------------------------------------------------------------------------------
  // Rpt_[lepton][jetMultiplicity] -> eg: Rpt_[Wmu][4].first/second = R/dR for muons from events with >= 4 jets cut
  std::map< TString, std::map <unsigned int, std::pair<double,double> > > Rinclusive_;
  for(int njets =1; njets<=4; njets++){
    Rinclusive_["mu"][njets] = calcutateTotalR(sumBinEntries(*ptNMuPlus_[njets-1],1),  sumBinEntries(*ptNMuMinus_[njets-1],1),  "Muons", "N(jets) >= "+getTStringFromInt(njets));
  }

  // c)  create R_inclusive[Njets] plot from b)
  TH1F* RNjetsMu  = new TH1F("RNjetsMu" , "RNjetsMu" , 4, 0.5, 4.5);
  for(int bin=1; bin<= 4; bin++){
    // -1 because 1st bin = 0 jets bin
    RNjetsMu->SetBinContent(bin,  Rinclusive_["mu"][bin].first);
    RNjetsMu->SetBinError  (bin,  Rinclusive_["mu"][bin].second);
  }

  // ---
  //    create legends 
  // ---
  // create a legend for R_inclusive[Njets] for some leptons
  TLegend *leg0 = new TLegend(0.25, 0.77, 1.0, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("inclusive R" );
  leg0->AddEntry(RNjetsMu ,"W#rightarrow#mu#nu+Jets", "PL");

  // R(ptmu) for all jet multiplicities part1
  TLegend *leg1a = new TLegend(0.21, 0.71, 0.85, 0.94);
  leg1a->SetFillStyle(0);
  leg1a->SetBorderSize(0);
  leg1a->SetHeader("  R(W#rightarrow#mu#nu+Jets)");
  leg1a->AddEntry( Rpt_["mu"][1], "N(jets)#geq1", "P");
  leg1a->AddEntry( Rpt_["mu"][2], "N(jets)#geq2", "P");

  // R(ptmu) for all jet multiplicities part2
  TLegend *leg1b = new TLegend(0.62, 0.70, 0.96, 0.86);
  leg1b->SetFillStyle(0);
  leg1b->SetBorderSize(0);
  leg1b->AddEntry( Rpt_["mu"][3], "N(jets)#geq3", "P");
  leg1b->AddEntry( Rpt_["mu"][4], "N(jets)#geq4", "P");

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<=1; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ---
  //    do the printing for R_inclusive[Njets]
  // ---
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetTitle("inclusiveRNjets");
  axesStyle(*RNjetsMu, "N_{jets} #geq", "R = #frac{N_{W^{+}} + N_{W^{-}}}{N_{W^{+}} - N_{W^{-}}}", 2.5, 8, 0.06, 1.3 );
  histogramStyle(*RNjetsMu , kBlack,  1, 22, 1.5);
  RNjetsMu ->Draw("e1");
  std::vector<std::pair<double,double> > inclusiveRfit_ =fitLinear(*RNjetsMu, 1.0, 4.5, RNjetsMu->GetLineColor(), "R( N(jets) ), W->mu & W->tau->mu");
  leg0     ->Draw("same");

  // ---
  //     do the printing for R(ptmu) for different N(jets)
  // ---
  MyCanvas[1]->cd(0);
  MyCanvas[1]->SetTitle("RptMuAllNjetsMu");
  axesStyle(*Rpt_["mu"][4], "p_{t} ( reco #mu ) [GeV]", "R = #frac{N_{W^{+}} + N_{W^{-}}}{N_{W^{+}} - N_{W^{-}}}", 0, 30, 0.05, 1.5);  
  histogramStyle(*Rpt_["mu"][1], kRed    , 1, 29, 2.0);
  histogramStyle(*Rpt_["mu"][2], kGreen-3, 1, 20, 1.5);
  histogramStyle(*Rpt_["mu"][3], kBlue   , 1, 23, 1.5);
  histogramStyle(*Rpt_["mu"][4], kMagenta, 1, 22, 1.5);
  Rpt_["mu"][4]->GetXaxis()->SetRangeUser(0,94);
  Rpt_["mu"][4]->Draw("e1");
  Rpt_["mu"][3]->Draw("e1same");
  Rpt_["mu"][2]->Draw("e1same");
  Rpt_["mu"][1]->Draw("e1same");
  fitQuadraticExtrapolate(*Rpt_["mu"][4], 20., 100., Rpt_["mu"][4]->GetLineColor(), "R_inclusive, N(jets)>=4");
  fitQuadraticExtrapolate(*Rpt_["mu"][3], 20., 100., Rpt_["mu"][3]->GetLineColor(), "R_inclusive, N(jets)>=3");
  fitQuadraticExtrapolate(*Rpt_["mu"][2], 20., 100., Rpt_["mu"][2]->GetLineColor(), "R_inclusive, N(jets)>=2");
  fitQuadraticExtrapolate(*Rpt_["mu"][1], 20., 100., Rpt_["mu"][1]->GetLineColor(), "R_inclusive, N(jets)>=1");
  leg1a        ->Draw("same");
  leg1b        ->Draw("same");

  // ---
  //     calculate fittet inclusive R for W->mu
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
    if(njets==1) std::cout << std::endl << "inclusive R (linear fit) for W->mu" << std::endl;
    std::cout << "N(jets)>="+getTStringFromInt(njets) << ": R = " << inclusiveRfit << " +/- " << errorInclusiveRfit << std::endl;
    // if textoutput==true: save fitted inclusive R values within .txt-file
    if(textoutput==true){
      if(njets==1) writeToFile("inclusive R (from linear fit) for gen W->mu and W->tau->mu for N(jets) >= 1 - 4:",file);
      writeToFile(inclusiveRfit,file);
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
  
    // eps
    for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
      MyCanvas[idx]->Print(saveTo+(TString)(MyCanvas[idx]->GetTitle())+".eps"  );      
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
    std::cout << "bin " << i << "mu+ / mu- = " << ptP << " / " << ptM << std::endl;
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
