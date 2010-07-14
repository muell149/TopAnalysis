// ---------description---------------------------------
// -----------------------------------------------------
// this Makro estimates the number of QCD events in the
// semimuonic selection via ABCD method
// -----------------------------------------------------

#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
 
enum samples {kQCD, kWjets, kTtbar, kZjets, kData};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, bool filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void histStyle2D(TH2& hist, const char* titleHisto="", const char* titleX="", const char* titleY="", const double xMin=-1, const double xMax=-1, const double yMin=-1, const double yMax=-1);
double Entries(TH2& hist, const int binXmin=1, const int binXmax=1, const int binYmin=1, const int binYmax=1, const TString label="");
double GetXAxisValue(TH2& hist, double bin);
double GetYAxisValue(TH2& hist, double bin);

void analyzeMuonDiffXABCDbkg()
{
  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);

  // choose luminosity for scaling of event numbers and for legend as entry
  int luminosity = 50;
  TString lum = "50";
  // choose whether you want to save every plot as png and all within one ps file
  bool save = false;
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/ABCD/";

  // ---
  //    get input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/spring10Samples/spring10SelV2Sync";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/QCDABCD.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH2F*> relIsoVsDb_;
  for(unsigned int idx=kQCD; idx<=kQCD; ++idx) {
    relIsoVsDb_.push_back( (TH2F*)files_[idx]->Get("estimationMuonsQuality/relIsoVsDb_") );
  }

  // ---
  //    define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;
  // a) for current QCD 7TeV Mc@Nlo sample 
  lumiweight.push_back(0.98351978/50.0*(double)luminosity);
  
  // Get Entries for samples 
  std::vector<double> regionA_, regionB_, regionC_, regionD_;
  regionA_.push_back(Entries(*relIsoVsDb_[kQCD], 0 , 5  , 0, 2 , "QCD Region A") );
  regionB_.push_back(Entries(*relIsoVsDb_[kQCD], 40, 101, 0, 2 , "QCD Region B") );
  regionC_.push_back(Entries(*relIsoVsDb_[kQCD], 0 , 5  , 3, 10, "QCD Region C") );
  regionD_.push_back(Entries(*relIsoVsDb_[kQCD], 40, 101, 3, 10, "QCD Region D") );
  // Do the estimate for region A from region B, C and D
  double estimation = regionB_[kQCD]*regionC_[kQCD]/regionD_[kQCD];
  double estimationError = estimation*sqrt( 1/regionB_[kQCD] + 1/regionC_[kQCD] + 1/regionD_[kQCD] );
  std::cout << "ABCD estimation for signal region A:" << estimation << "+/-" << estimationError << std::endl;
  
  // ---
  //    create legend(s)
  // ---
  TLegend    *leg0 = new TLegend   (0.42, 0.78, 1.0, 0.94);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  //  leg0->SetHeader("");
  leg0->AddEntry( relIsoVsDb_[kQCD], "QCD PYTHIA, 49 / pb", "PL");

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<=0; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ---
  //    do the printing for corrPt_
  // ---
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetTitle("relIsoVsDb");
  histStyle2D(*relIsoVsDb_[kQCD], "", "relIso", "d_{B} [cm]", 0.0, 1.0, 0.0, 0.1);
  //  relIsoVsDb_[kQCD]->Draw("colz");
  relIsoVsDb_[kQCD]->Draw("");
  leg0->Draw("same");


  // ---
  // saving
  // ---
  if(save){   
    // ps
    MyCanvas[0]->Print(saveTo+"ABCDmethod.ps(");
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+"ABCDmethod.ps");   
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+"ABCDmethod.ps)");
  
    // png
    for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
      MyCanvas[idx]->Print(saveTo+(TString)(MyCanvas[idx]->GetTitle())+".png");      
    }
  }

}

double Entries(TH2& hist, const int binXmin, const int binXmax, const int binYmin, const int binYmax, TString label){
// this Function simply counts the number of
// entries of hist in the chosen range: 
// binXmin <= x <= binXmax && binYmin <= y <= binYmax  

  std::cout << "range for " << label << ":"<< std::endl;
  std::cout << GetXAxisValue(hist, (double)(binXmin)) << " <= relIso <= " << GetXAxisValue(hist, (double)(binXmax)) << std::endl;
  std::cout << GetYAxisValue(hist, (double)(binYmin)) << " <= dB <= " << GetYAxisValue(hist, (double)(binYmax)) << std::endl;
 
  int result=0;
  // k: adress relIso bin
  // l: adress dB bin
  for(int k=binXmin; k<=binXmax; ++k){
    for(int l=binYmin; l<=binYmax; ++l){
      result += hist.GetBinContent(k,l);
    }
  }
  std::cout << "entries: " << result << std::endl;
  return (double)result;
}

void canvasStyle(TCanvas& canv) 
{
  canv.SetFillStyle   ( 4000 );
  canv.SetLeftMargin  ( 0.20 );
  canv.SetRightMargin ( 0.05 );
  canv.SetBottomMargin( 0.15 );
  canv.SetTopMargin   ( 0.05 );
}

void histogramStyle(TH1& hist, int color, int lineStyle, int markerStyle, float markersize, bool filled) 
{
  hist.SetLineWidth(3);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color);
  hist.SetMarkerColor(color);  
  hist.SetMarkerStyle(markerStyle);
  hist.SetMarkerSize(markersize);
  hist.SetLineStyle(lineStyle);
  if(filled){
  hist.SetFillStyle(1001);
  hist.SetFillColor(color);
  }
  else{
    hist.SetFillStyle(0);
  }
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

void histStyle2D(TH2& hist, const char* titleHisto, const char* titleX, const char* titleY, const double xMin, const double xMax, const double yMin, const double yMax) 
{
  hist.SetTitle(titleHisto);
  hist.GetXaxis()->SetTitle(titleX);
  hist.GetXaxis()->SetTitleSize ( 0.05 );
  hist.GetXaxis()->SetLabelColor(  1   );
  hist.GetXaxis()->SetLabelFont ( 62   );
  hist.GetXaxis()->SetLabelSize ( 0.04 );
  hist.GetXaxis()->SetNdivisions(  505 );
  hist.GetXaxis()->CenterTitle  ( true );
  hist.GetYaxis()->SetTitle(titleY);
  hist.GetYaxis()->SetTitleSize  ( 0.05 );
  hist.GetYaxis()->SetTitleColor (    1 );
  hist.GetYaxis()->SetTitleOffset(  1.5 );
  hist.GetYaxis()->SetTitleFont  (   62 );
  hist.GetYaxis()->SetLabelSize  ( 0.04 );
  hist.GetYaxis()->SetLabelFont  (   62 );
  hist.GetYaxis()->SetNdivisions (  505 );
  hist.GetYaxis()->CenterTitle   ( true );
  if(xMin!=-1 && xMax!=-1)hist.SetAxisRange(xMin, xMax, "X");
  if(yMin!=-1 && yMax!=-1)hist.SetAxisRange(yMin, yMax, "Y");
  hist.SetStats(kFALSE);
}

double GetXAxisValue(TH2& hist, double bin){
  return (bin) * (double)( hist.GetXaxis()->GetBinLowEdge(hist.GetNbinsX()+1) ) / (double)( hist.GetNbinsX() );
}

double GetYAxisValue(TH2& hist, double bin){
  return (bin) * (double)( hist.GetYaxis()->GetBinLowEdge(hist.GetNbinsY()+1) ) / (double)( hist.GetNbinsY() );
}
