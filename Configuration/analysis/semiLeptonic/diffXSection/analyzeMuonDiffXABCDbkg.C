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
#include <TLine.h>
#include <TStyle.h>
#include <TPaveLabel.h>

enum samples {kQCD, kWjets, kTtbar, kZjets, kAll, kData};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, bool filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void histStyle2D(TH2& hist, const int color=kBlack, const double xMin=-1, const double xMax=-1, const double yMin=-1, const double yMax=-1, const char* titleHisto="", const char* titleX="", const char* titleY="");
double Entries(TH2& hist, const int binXmin=1, const int binXmax=1, const int binYmin=1, const int binYmax=1, const TString label="", bool printOut=true);
double GetXAxisValue(TH2& hist, double bin);
double GetYAxisValue(TH2& hist, double bin);
TString getTStringFromInt(int i);
void drawLine(const double x1, const double x2, const double y1, const double y2);
void DrawLabel(TString text, const double x1, const double y1, const double x2, const double y2);

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
  TString lum = getTStringFromInt(luminosity);
  // choose whether you want to save every plot as png and all within one ps file
  bool save = true;
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/ABCD/";

  // ---
  //    get input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/spring10Samples/spring10SelV2Sync";
  //  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/QCDABCD.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/QCDABCDnoSelection.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/wjetsABCD.root") );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/ttbarABCD.root") );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/zjetsABCD.root") );

  // ---
  //    get histograms
  // ---
  // create jet multiplicity indicator
  std::vector<TString> Njets_;
  Njets_.push_back("Njets1");
  Njets_.push_back("Njets2");
  Njets_.push_back("Njets3");
  Njets_.push_back("Njets4");
  // create container for all histos
  std::map< TString, std::map <unsigned int, TH2F*> > relIsoVsDb_;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop all samples
    for(unsigned int idx=kQCD; idx<=kZjets; ++idx) {
      relIsoVsDb_[Njets_[mult]][idx] = (TH2F*)(files_[idx]->Get("estimationMuonsQuality"+Njets_[mult]+"/relIsoVsDb_")->Clone());
    }
  }

  // ---
  //    define weights concerning luminosity
  // ---
  std::vector<double> lumiweight_;
  // a) for current QCD 7TeV PYTHIA sample 
  lumiweight_.push_back(0.98351978/50.0*(double)luminosity);
  // b) for current wjets 7TeV MADGRAPH sample 
  lumiweight_.push_back(0.13904207/50.0*(double)luminosity);  
  // c) for current ttbar 7TeV MC@NLO sample 
  lumiweight_.push_back(0.00831910/50.0*(double)luminosity);
  // d) for current zjets 7TeV MADGRAPH sample 
  lumiweight_.push_back(0.14332841/50.0*(double)luminosity);

  // ---
  //    combine all MC samples
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    relIsoVsDb_[Njets_[mult]][kAll] = (TH2F*)relIsoVsDb_[Njets_[mult]][kQCD]->Clone();
    relIsoVsDb_[Njets_[mult]][kAll]->Scale(lumiweight_[kQCD]); 
    // loop all samples
    for(unsigned int idx=kWjets; idx<=kZjets; ++idx) {
      relIsoVsDb_[Njets_[mult]][42] = (TH2F*)relIsoVsDb_[Njets_[mult]][idx]->Clone();
      relIsoVsDb_[Njets_[mult]][42]->Scale(lumiweight_[idx]);
      relIsoVsDb_[Njets_[mult]][kAll]->Add(relIsoVsDb_[Njets_[mult]][42]);
    }
  }

  // ---
  //    ABCD estimation for QCD only and from all events (weighted to 51 / pb) for all jet multiplicities
  // ---
  // create container for estimation results
  std::map< TString, std::map <unsigned int, std::pair<double,double> > > ABCDresult_;
  // dB    : 1000 bins from 0 to 1 -> 1 bin = 0.001 as upper edge
  // relIso: 100  bins from 0 to 1 -> 1 bin = 0.01  as upper edge

  // choose your values
  int relIsoBinACLow = 0;   // = 0 and underflow
  int relIsoBinACUp  = 5;   // = 0.05
  int relIsoBinBDLow = 40;  // = 0.4
  int relIsoBinBDUp  = 100; // = 1.0
  int dBBinABLow = 0;    // = 0 and underflow
  int dBBinABUp  = 20;   // = 0.02
  int dBBinCDLow = 30;   // = 0.03
  int dBBinCDUp  = 100;  // = 0.1

  // calculation
  double regionA, regionB, regionC, regionD;
  double estimation = -1;
  double estimationError = -1;
  for(unsigned int forWhich=kQCD; forWhich<=kAll; forWhich=forWhich+4){
    if(forWhich==kQCD) std::cout << "" << std::endl << "calculation from QCD only:" << std::endl;
    if(forWhich==kAll) std::cout << "" << std::endl << "calculation from all events ("+lum+" / pb):" << std::endl;
    // loop jet multiplicities
    for(unsigned int mult=0; mult<Njets_.size(); ++mult){
      std::cout << "" << std::endl;
      std::cout << "N(jets) >= " << mult+1 << std::endl;
      regionA=Entries(*relIsoVsDb_[Njets_[mult]][forWhich], relIsoBinACLow, relIsoBinACUp, dBBinABLow, dBBinABUp, "Region A");
      regionB=Entries(*relIsoVsDb_[Njets_[mult]][forWhich], relIsoBinBDLow, relIsoBinBDUp, dBBinABLow, dBBinABUp, "Region B");
      regionC=Entries(*relIsoVsDb_[Njets_[mult]][forWhich], relIsoBinACLow, relIsoBinACUp, dBBinCDLow, dBBinCDUp, "Region C");
      regionD=Entries(*relIsoVsDb_[Njets_[mult]][forWhich], relIsoBinBDLow, relIsoBinBDUp, dBBinCDLow, dBBinCDUp, "Region D");
      // Do the estimate for region A from region B, C and D
      estimation = regionB*regionC/regionD;
      estimationError = estimation*sqrt( 1/regionB + 1/regionC + 1/regionD );
      std::cout << "ABCD estimation for signal region A:" << estimation << "+/-" << estimationError << std::endl;
      // save value and error of estimation
      if(forWhich==kQCD)ABCDresult_[Njets_[mult]][forWhich] = make_pair(lumiweight_[kQCD]*estimation, estimationError/sqrt(lumiweight_[kQCD]));
      else ABCDresult_[Njets_[mult]][forWhich] = make_pair(estimation, estimationError);
    }
  }

  // ---
  //    create estimation quality plots
  // ---
  TH1F *MCTruth = new TH1F("MCTruth" , "MCTruth" , 4, 0.5, 4.5);
  TH1F *FromQCD = new TH1F("FromQCD" , "FromQCD" , 4, 0.5, 4.5);
  TH1F *FromAll = new TH1F("FromAll" , "FromAll" , 4, 0.5, 4.5);

  // loop bins = multiplicity
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    MCTruth->SetBinContent(mult+1, lumiweight_[kQCD]*Entries(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinACLow, relIsoBinACUp, dBBinABLow, dBBinABUp, "Region A", false));
    FromQCD->SetBinContent(mult+1, ABCDresult_[Njets_[mult]][kQCD].first  );
    FromQCD->SetBinError  (mult+1, ABCDresult_[Njets_[mult]][kQCD].second );
    FromAll->SetBinContent(mult+1, ABCDresult_[Njets_[mult]][kAll].first  );
    FromAll->SetBinError  (mult+1, ABCDresult_[Njets_[mult]][kAll].second );
  }

  // ---
  //    create legend(s)
  // ---
  TLegend*leg0 = new TLegend   (0.51, 0.59, 0.96, 0.87);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->AddEntry( relIsoVsDb_["Njets1"][kQCD  ], "QCD (51 / pb)"      , "L");
  leg0->AddEntry( relIsoVsDb_["Njets1"][kTtbar], "Ttbar (6010 / pb)"  , "L");
  leg0->AddEntry( relIsoVsDb_["Njets1"][kWjets], "W+jets (360 / pb)", "L");
  leg0->AddEntry( relIsoVsDb_["Njets1"][kZjets], "Z+jets (349 / pb)", "L");
  TLegend*leg1 = new TLegend   (0.43, 0.62, 0.86, 0.92);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader( "ABCD method ("+lum+" pb^{-1})");
  leg1->AddEntry ( MCTruth, "MC truth","PL");
  leg1->AddEntry ( FromQCD, "estimation (QCD only  )", "PL");
  leg1->AddEntry ( FromAll, "estimation (all events)", "PL");
  // create jet multiplicity label
  std::vector<TPaveLabel*> jetMultiplicity_;
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){ 
    TPaveLabel *jet = new TPaveLabel(0.11, 0.83, 0.62, 1.05, "N(Jets) #geq "+getTStringFromInt(mult+1), "br NDC");
    jet->SetFillStyle(0);
    jet->SetBorderSize(0);
    jet->SetTextSize(0.26);
    jetMultiplicity_.push_back((TPaveLabel*)jet->Clone());
  }

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<=4; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ---
  //    do the printing for relIsoVsDb 
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    MyCanvas[mult]->cd(0);
    MyCanvas[mult]->SetTitle("relIsoVsDb"+Njets_[mult]);
    histStyle2D(*relIsoVsDb_[Njets_[mult]][kQCD  ], kBlack, 0.0, 1.0, 0.0, 0.1, "", "relIso (lead #mu)", "d_{B} [cm] (lead #mu)");
    histStyle2D(*relIsoVsDb_[Njets_[mult]][kWjets], kGreen, 0.0, 1.0, 0.0, 0.1);
    histStyle2D(*relIsoVsDb_[Njets_[mult]][kTtbar], kRed  , 0.0, 1.0, 0.0, 0.1);
    histStyle2D(*relIsoVsDb_[Njets_[mult]][kZjets], 7     , 0.0, 1.0, 0.0, 0.1);
    //  relIsoVsDb_[Njets_[mult]][kQCD]->Draw("colz");
    relIsoVsDb_[Njets_[mult]][kQCD  ]->Draw("");
    relIsoVsDb_[Njets_[mult]][kZjets]->Draw("same");
    relIsoVsDb_[Njets_[mult]][kWjets]->Draw("same");
    relIsoVsDb_[Njets_[mult]][kTtbar]->Draw("same");
    relIsoVsDb_[Njets_[mult]][kQCD  ]->Draw("AXIS same");
    // lines region A
    drawLine(GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinACLow), GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinACUp), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinABUp ), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinABUp));
    drawLine(GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinACUp ), GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinACUp), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinABLow), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinABUp));
    // lines region B
    drawLine(GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinBDLow), GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinBDUp ), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinABUp ), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinABUp));
    drawLine(GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinBDLow), GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinBDLow), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinABLow), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinABUp));
    // lines region C
    drawLine(GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinACLow), GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinACUp), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinCDLow), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinCDLow));
    drawLine(GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinACUp ), GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinACUp), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinCDLow), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinCDUp));
    // lines region D
    drawLine(GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinBDLow), GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinBDUp ), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinCDLow), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinCDLow));
    drawLine(GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinBDLow), GetXAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], relIsoBinBDLow), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinCDLow), GetYAxisValue(*relIsoVsDb_[Njets_[mult]][kQCD], dBBinCDUp)); 
    // Draw A,B,C,D
    DrawLabel("A", 0.085, 0.125, 0.35 , 0.34 );
    DrawLabel("B", 0.580, 0.120, 0.845, 0.335);
    DrawLabel("C", 0.085, 0.362, 0.35 , 0.577);
    DrawLabel("D", 0.580, 0.362, 0.845, 0.577);
    leg0                             ->Draw("same");
    jetMultiplicity_[mult]           ->Draw("same");
  }

  // ---
  //    do the printing for the ABCD estimation results
  // ---
  MyCanvas[4]->cd(0);
  MyCanvas[4]->SetTitle("ABCDestimationResults");
  axesStyle(*MCTruth, "N(jets) #geq", "events", 0, 10000, 0.05, 1.4);
  histogramStyle(*MCTruth, kBlack, 1, 20, 1.2); 
  histogramStyle(*FromQCD, kBlue , 1, 20, 1.2); 
  histogramStyle(*FromAll, kRed  , 1, 20, 1.2);
  MCTruth->Draw("");
  FromQCD->Draw("same");
  FromAll->Draw("same");
  leg1   ->Draw("same");

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

double Entries(TH2& hist, const int binXmin, const int binXmax, const int binYmin, const int binYmax, TString label, bool printOut){
// this Function simply counts the number of
// entries of hist in the chosen range: 
// binXmin <= x <= binXmax && binYmin <= y <= binYmax  

  if(printOut)std::cout << "range for " << label << ":"<< std::endl;
  if(printOut)std::cout << GetXAxisValue(hist, (double)(binXmin)) << " <= relIso <= " << GetXAxisValue(hist, (double)(binXmax)) << std::endl;
  if(printOut)std::cout << GetYAxisValue(hist, (double)(binYmin)) << " <= dB <= " << GetYAxisValue(hist, (double)(binYmax)) << std::endl;
 
  double result=0;
  // k: adress relIso bin
  // l: adress dB bin
  for(int k=binXmin; k<=binXmax; ++k){
    for(int l=binYmin; l<=binYmax; ++l){
      result += hist.GetBinContent(k,l);
    }
  }
  if(printOut)std::cout << "entries: " << result << std::endl;
  return result;
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

void histStyle2D(TH2& hist, const int color, const double xMin, const double xMax, const double yMin, const double yMax, const char* titleHisto, const char* titleX, const char* titleY) 
{
  hist.SetTitle(titleHisto);
  hist.SetLineColor(color);
  hist.SetMarkerColor(color);
  hist.SetMarkerSize(1.5);
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

TString getTStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return (TString)result;
}

void drawLine(const double x1, const double x2, const double y1, const double y2)
{
  TLine *cut = new TLine();
  cut->SetLineWidth(3);
  cut->SetLineStyle(1);
  cut->SetLineColor(1);
  cut->DrawLine(x1, y1, x2, y2);
}

void DrawLabel(TString text, const double x1, const double y1, const double x2, const double y2)
{
  TPaveLabel *label = new TPaveLabel(x1, y1, x2, y2, text, "br NDC");
  label->SetFillStyle(0);
  label->SetBorderSize(0);
  label->SetTextSize(0.26);
  label->Draw("same");
}
