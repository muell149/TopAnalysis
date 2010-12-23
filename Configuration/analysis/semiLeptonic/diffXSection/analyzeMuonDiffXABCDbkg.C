// ---------description---------------------------------
// -----------------------------------------------------
// this Makro estimates the number of QCD events in the
// semimuonic selection via ABCD method
// -----------------------------------------------------

#include <vector>
#include <iostream>
#include <fstream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TStyle.h>
#include <TPaveLabel.h>
#include <TF1.h>
#include <TMath.h>

enum samples {kQCD, kWjets, kTtbar, kZjets, kData, kAll};

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
template <class T>
void writeToFile(T output, TString file="crossSectionCalculation.txt", bool append=1);
void fitParabolaExtrapolate(TH1& hist, const double xmin=0., const double xmax=1., const int color=kBlack, const TString info="");
void fitLinearExtrapolate(TH1& hist, const double xmin=0., const double xmax=1., const int color=kBlack, const TString info="");
std::vector<double> fitExponentialExtrapolate(TH1& hist, const double xmin=0., const double xmax=1., const int color=kBlack, const TString info="");
std::pair<double,double> exponentialFit(double x, const double a, const double sa, const double b, const double sb);
std::vector<double> fitExponentialExtrapolate2(TH1& hist, const double xmin=0., const double xmax=1., const int color=kBlack, const TString info="");
//std::pair<double,double> exponentialFit2(double x, const double a, const double sa, const double b, const double sb);


void analyzeMuonDiffXABCDbkg(double luminosity = 50, bool save = false, bool textoutput=false, TString dataFile="./diffXSecFromSignal/data/DiffXSecData_Nov15.root", TString jetType = "PF")
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
  TString saveTo = "./diffXSecFromSignal/plots/ABCD/";
  TString file = "crossSectionCalculation"+jetType+".txt";

  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  //  gStyle->SetErrorX(0);

  // ---
  //    get input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/analysisRootFiles";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecQCDPythiaZ2Fall10"+jetType+".root") );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecWjetsMadD6TFall10"+jetType+".root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecAllMadD6TFall10"+jetType+".root"   ) );
  //files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecAllNloFall10.root"   ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecZjetsMadD6TFall10"+jetType+".root" ) );
  files_.push_back(new TFile(dataFile                                                            ) );

  // ---
  //    get histograms
  // ---
  // create jet multiplicity indicator
  std::vector<TString> Njets_;
  TString jets[ 4 ] = { "Njets1", "Njets2", "Njets3", "Njets4" };
  Njets_.insert( Njets_.begin(), jets, jets + 4 );
  // create container for histos
  std::map< TString, std::map <unsigned int, TH2F*> > relIsoVsDb_;
  std::map< TString, std::map <unsigned int, TH1F*> >recoSelectionPt_;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop all samples
    for(unsigned int idx=kQCD; idx<=kData; ++idx) {
      // ABCD relIso-dB correlation plot
      relIsoVsDb_[Njets_[mult]][idx] = (TH2F*)(files_[idx]->Get("estimationMuonsQuality"+Njets_[mult]+"/relIsoVsDb_")->Clone());
      // pt from full reco selection -> correction factor
       recoSelectionPt_[Njets_[mult]][idx] =(TH1F*)(files_[idx]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/pt")->Clone());
     }
  }

  // ---
  //    define weights concerning luminosity
  // ---
  std::vector<double> lumiweight_;
  // a) for current QCD 7TeV PYTHIA sample 
  lumiweight_.push_back(0.143500567/50.0*luminosity);
  // b) for current wjets 7TeV MADGRAPH sample 
  lumiweight_.push_back(0.105750913/50.0*luminosity);  
  // c) for current ttbar 7TeV MADGRAPH sample 
  lumiweight_.push_back(0.006029022/50.0*luminosity);
  // d) for current zjets 7TeV MADGRAPH sample 
  lumiweight_.push_back(0.059912090/50.0*luminosity);

  // ---
  //    lumiweight and combine all MC samples
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    relIsoVsDb_[Njets_[mult]][kAll] = (TH2F*)relIsoVsDb_[Njets_[mult]][kQCD]->Clone();
    relIsoVsDb_[Njets_[mult]][kAll]->Scale(lumiweight_[kQCD]); 
    // loop all samples
    for(unsigned int idx=kWjets; idx<=kZjets; ++idx) {
      // lumiweighting
      relIsoVsDb_[Njets_[mult]][idx]->Scale(lumiweight_[idx]);
      relIsoVsDb_[Njets_[mult]][42] = (TH2F*)relIsoVsDb_[Njets_[mult]][idx]->Clone();
      relIsoVsDb_[Njets_[mult]][kAll]->Add(relIsoVsDb_[Njets_[mult]][42]);
    }
  }

  // ---
  //    create canvas
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<=25; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ---
  //    configuration for ABCD calculation
  // ---
  // create container for estimation results
  std::map< TString, std::map <unsigned int, std::pair<double,double> > > ABCDresult_;
  // create container for correction factor ABC->standard reco selection
  std::vector<std::pair<double,double> > correctionFactor_;
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

  // ---
  //    print out event composition after ABCD selection
  // ---
  std::cout << "" << std::endl;
  std::cout << "output of ABCD estimation" << std::endl;
  std::cout << "( scaled to luminosity: " << luminosity << " / pb )" << std::endl;
  std::cout << "" << std::endl;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    std::cout << "----------------" << std::endl;
    std::cout << "N(jets) >= " << mult+1 << std::endl;
    std::cout << "----------------" << std::endl;
    // loop all samples
    for(unsigned int idx=kQCD; idx<=kData; ++idx){
      std::cout << "" << std::endl;
      if(idx==kQCD)   std::cout << "QCD sample:"    << std::endl; 
      if(idx==kWjets) std::cout << "W+jets sample:" << std::endl; 
      if(idx==kTtbar) std::cout << "ttbar sample:"  << std::endl; 
      if(idx==kZjets) std::cout << "Z+jets sample:" << std::endl;
      if(idx==kData ) std::cout<< "-----" << std::endl << "Data: " << std::endl;
      std::cout << "Region A: " << Entries(*relIsoVsDb_[Njets_[mult]][idx], relIsoBinACLow, relIsoBinACUp, dBBinABLow, dBBinABUp, "Region A", false) << std::endl;
      std::cout << "Region B: " << Entries(*relIsoVsDb_[Njets_[mult]][idx], relIsoBinBDLow, relIsoBinBDUp, dBBinABLow, dBBinABUp, "Region B", false) << std::endl;
      std::cout << "Region C: " << Entries(*relIsoVsDb_[Njets_[mult]][idx], relIsoBinACLow, relIsoBinACUp, dBBinCDLow, dBBinCDUp, "Region C", false) << std::endl;
      std::cout << "Region D: " << Entries(*relIsoVsDb_[Njets_[mult]][idx], relIsoBinBDLow, relIsoBinBDUp, dBBinCDLow, dBBinCDUp, "Region D", false) << std::endl;
      // print out correlation factor
      std::cout << "correlation factor: " << relIsoVsDb_[Njets_[mult]][idx]->GetCorrelationFactor() << std::endl;
      if(idx==kData ) std::cout<< "" << std::endl;
      // calculate correction factor ABCD->Reco selection for all N(jets)
      if(idx==kQCD){
	double Nreco = (recoSelectionPt_[Njets_[mult]][idx]->GetEntries()) * (lumiweight_[idx]);
	double Nabcd = Entries(*relIsoVsDb_[Njets_[mult]][idx], relIsoBinACLow, relIsoBinACUp, dBBinABLow, dBBinABUp, "Region A", false);
	correctionFactor_.push_back(  make_pair (Nreco / Nabcd, sqrt((Nreco/(Nabcd*Nabcd))*(1.0+Nreco/Nabcd)) )  );
      }
    }
  }

  //---
  //   draw, fit and extrapolate ABCD->default selection correction factor
  //---
  // weighting factor(N_jets) plot
  TH1F *weight  = new TH1F("weight" , "weight" , 4, 0.5, 4.5);
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    weight->SetBinContent(mult+1, correctionFactor_ [mult].first );
    weight->SetBinError  (mult+1, correctionFactor_ [mult].second);
  }
  // draw weighting factor(N_jets) in last Canvas
  MyCanvas[MyCanvas.size()-1]->cd(0);
  MyCanvas[MyCanvas.size()-1]->SetTitle("ABCDweigthingFactor");
  axesStyle(*weight, "N(jets) #geq", "weight = #frac{N(QCD, reco selection)}{N(QCD, ABCD region A)}", 0.2, 1, 0.04, 1.9);
  histogramStyle(*weight, kBlack, 1, 20, 1.25); 
  weight->Draw("P");

  // do a exponential fit exp(ax)+b and save a, b and their errors in vector exponentialFitParameters
  std::vector<double> exponentialFitParameters = fitExponentialExtrapolate(*weight, 1., 3., weight->GetLineColor(), "ABCD->reco selection weighting factor");
  enum exponentialFitResults {a, sa, b, sb};
  // calculate weighting factors(Njets) from fit function and save them in weightValues_
  std::map< TString, std::pair <double, double> > weightValues_;
  for(int jetMultiplicity=1; jetMultiplicity<=4; ++jetMultiplicity){
    weightValues_[Njets_[jetMultiplicity-1]] = exponentialFit((double)jetMultiplicity, exponentialFitParameters[a], exponentialFitParameters[sa], exponentialFitParameters[b], exponentialFitParameters[sb]);
    if(jetMultiplicity==1) std::cout << "" << std::endl;
    if(jetMultiplicity==1) std::cout << "results for ABCD-> default selection correction factor" << std::endl;
    if(jetMultiplicity==1) std::cout << "( calculated, from fit function )" << std::endl;
    std::cout << "N(jets) >= " << jetMultiplicity << ": ( " << correctionFactor_[jetMultiplicity-1].first << " +/- " << correctionFactor_[jetMultiplicity-1].second << " , " << weightValues_[Njets_[jetMultiplicity-1]].first << " +/- " << weightValues_[Njets_[jetMultiplicity-1]].second << " )" << std::endl;    
  }

  //---
  //   do ABCD estimation
  //---
  double regionA, regionB, regionC, regionD;
  double estimation = -1;
  double estimationError = -1;
  std::cout << "" << std::endl;
  std::cout << "ABCD estimation" << std::endl;
  // for QCD only, all MC and data
  for(unsigned int forWhich=kQCD; forWhich<=kAll; ++forWhich){
    if(forWhich==kData) std::cout << "" << std::endl << "b) calculation for data:" << std::endl;
    if(forWhich==kQCD)  std::cout << "" << std::endl << "a) calculation from QCD MC only:" << std::endl;
    if(forWhich==kAll)  std::cout << "" << std::endl << "c) calculation from all MC events ("+lum+" / pb):" << std::endl;
    // for all jet multiplicities
    for(unsigned int mult=0; mult<Njets_.size(); ++mult){
      std::cout << "" << std::endl;
      std::cout << "N(jets) >= " << mult+1 << std::endl;
      // get entries of the 4 regions
      regionA=Entries(*relIsoVsDb_[Njets_[mult]][forWhich], relIsoBinACLow, relIsoBinACUp, dBBinABLow, dBBinABUp, "Region A");
      regionB=Entries(*relIsoVsDb_[Njets_[mult]][forWhich], relIsoBinBDLow, relIsoBinBDUp, dBBinABLow, dBBinABUp, "Region B");
      regionC=Entries(*relIsoVsDb_[Njets_[mult]][forWhich], relIsoBinACLow, relIsoBinACUp, dBBinCDLow, dBBinCDUp, "Region C");
      regionD=Entries(*relIsoVsDb_[Njets_[mult]][forWhich], relIsoBinBDLow, relIsoBinBDUp, dBBinCDLow, dBBinCDUp, "Region D");
      // do the estimate for region A from region B, C and D
      estimation = regionB*regionC/regionD;
      estimationError = estimation*sqrt( 1/sqrt(regionB) + 1/sqrt(regionC) + 1/sqrt(regionD) );
      std::cout << "ABCD estimation for signal region A:" << estimation << "+/-" << estimationError << std::endl;
      std::cout << "N(QCD) after default selection: " << recoSelectionPt_[Njets_[mult]][kQCD]->GetEntries()*lumiweight_[kQCD] << std::endl;
      // use fitted correction parameter from above to scale estimation
      std::cout << "(MC ABCD->reco correction factor used: " << weightValues_[Njets_[mult]].first << "+/-" << weightValues_[Njets_[mult]].second << " )" << std::endl;
      double weightedEstimation = estimation*weightValues_[Njets_[mult]].first;
      double weightedEstimationError = estimationError*weightValues_[Njets_[mult]].first;
      std::cout << "weighted estimation:" << estimation*weightValues_[Njets_[mult]].first << "+/-" << estimationError*weightValues_[Njets_[mult]].first << std::endl;
      // save value and error of estimation in ABCDresult_
      // a) for QCD: apply lumi-scaling
      if(forWhich==kQCD)ABCDresult_[Njets_[mult]][forWhich] = make_pair(lumiweight_[kQCD]*weightedEstimation, weightedEstimationError*sqrt(lumiweight_[kQCD]));
      // b) for all MC and data: no scaling
      if(forWhich==kAll||forWhich==kData) ABCDresult_[Njets_[mult]][forWhich] = make_pair(weightedEstimation, weightedEstimationError); 
      // c) if textoutput==true: save numbers for data estimation within .txt-file
      if(textoutput&&forWhich==kData){
	TString info = "ABCD QCD estimation results for Njets>=1,2,3 and 4: ";
	if(mult==0) writeToFile(info,file);
	writeToFile(weightedEstimation,file);
      }
    } 
    // jump from QCD to Data, skipping other MC samples
    if(forWhich==kQCD) forWhich=forWhich+3;      
  }

  // ---
  //    create estimation quality plots
  // ---
  TH1F *MCTruth = new TH1F("MCTruth" , "MCTruth" , 4, 0.5, 4.5);
  TH1F *FromQCD = new TH1F("FromQCD" , "FromQCD" , 4, 0.5, 4.5);
  TH1F *FromAll = new TH1F("FromAll" , "FromAll" , 4, 0.5, 4.5);

  // loop bins = multiplicity
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    MCTruth->SetBinContent(mult+1, lumiweight_[kQCD]*recoSelectionPt_[Njets_[mult]][kQCD]->GetEntries());
    FromQCD->SetBinContent(mult+1, ABCDresult_[Njets_[mult]][kQCD].first  );
    FromQCD->SetBinError  (mult+1, ABCDresult_[Njets_[mult]][kQCD].second );
    FromAll->SetBinContent(mult+1, ABCDresult_[Njets_[mult]][kAll].first  );
    FromAll->SetBinError  (mult+1, ABCDresult_[Njets_[mult]][kAll].second );
  }

  // ---
  //    create legend(s)
  // ---
  // for result plot
  TLegend*leg1 = new TLegend   (0.46, 0.64, 0.89, 0.94);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader( "ABCD method ("+lum+" pb^{-1})");
  leg1->AddEntry ( MCTruth, "MC default selection truth","L");
  leg1->AddEntry ( FromQCD, "estimation (QCD only)"  , "PL");
  leg1->AddEntry ( FromAll, "estimation (all events)", "PL");
  // create jet multiplicity label
  std::vector<TPaveLabel*> jetMultiplicity_;
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){ 
    TPaveLabel *jet = new TPaveLabel(0.11, 0.80, 0.62, 1.02, "N(Jets) #geq "+getTStringFromInt(mult+1), "br NDC");
    jet->SetFillStyle(0);
    jet->SetBorderSize(0);
    jet->SetTextSize(0.26);
    jetMultiplicity_.push_back((TPaveLabel*)jet->Clone());
  }
  // create MC sample label
  std::vector<TString> sample_;
  TString samples[ 6 ] = { "QCD", "Wjets", "Ttbar", "Zjets", "Data", "allMC" };
  sample_.insert( sample_.begin(), samples, samples + 6 );
  std::vector<TPaveLabel*> sampleLabel_;
  for(unsigned int idx=kQCD; idx<=kAll; ++idx){
    TString header = "";
    if(idx==kData) header = ""+sample_[idx];
    if(idx!=kData) header = ""+sample_[idx]+", ("+lum+" / pb)";
    TPaveLabel *slabel = new TPaveLabel(0.51, 0.83, 0.95, 1.0, header, "br NDC");
    slabel->SetFillStyle(0);
    slabel->SetBorderSize(0);
    slabel->SetTextSize(0.26);
    sampleLabel_.push_back( (TPaveLabel*)(slabel->Clone()) );
  }

  // ---
  //    do the printing for relIsoVsDb 
  // ---
  int index =0;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop samples 
    for(unsigned int idx=kQCD; idx<=kAll; ++idx) {
      // set styling
      histStyle2D(*relIsoVsDb_[Njets_[mult]][idx], kBlack, 0.0, 1.0, 0.0, 0.1, "", "relIso (lead #mu)", "d_{B} [cm] (lead #mu)");
      // open canvas
      MyCanvas[index]->cd(0);
      MyCanvas[index]->SetTitle("relIsoVsDb"+Njets_[mult]+sample_[idx]);
      ++index;
      // draw plots and redraw axis
      relIsoVsDb_[Njets_[mult]][idx]->Draw("box");
      relIsoVsDb_[Njets_[mult]][idx]->Draw("AXIS same");
      // draw legends 
      sampleLabel_[idx]     ->Draw("same");
      jetMultiplicity_[mult]->Draw("same");
      // Draw ABCD regions
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
      // A,B,C,D
      DrawLabel("A", 0.085, 0.125, 0.35 , 0.34 );
      DrawLabel("B", 0.580, 0.120, 0.845, 0.335);
      DrawLabel("C", 0.085, 0.362, 0.35 , 0.577);
      DrawLabel("D", 0.580, 0.362, 0.845, 0.577);
    }
  }

  // ---
  //    do the printing for the ABCD estimation results
  // ---
  MyCanvas[index]->cd(0);
  MyCanvas[index]->SetTitle("ABCDestimationResultsMC"+lum+"pb");
  MyCanvas[index]->SetLogy();
  axesStyle(*MCTruth, "N(jets) #geq", "events", 1, 300000/50*luminosity, 0.05, 1.4);
  histogramStyle(*MCTruth, kBlack, 1, 10, 1.0); 
  histogramStyle(*FromQCD, kBlue , 1, 22, 1.5); 
  histogramStyle(*FromAll, kRed  , 1, 23, 1.5);
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

void fitParabolaExtrapolate(TH1& hist, const double xmin, const double xmax, const int color, const TString info){
  // print out info
  std::cout << "" << std::endl;
  std::cout << "parabola fit: a*x*x +b*x +c for " << info << std::endl;
  std::cout << "-----------------------=----------------------------" << std::endl;
  TF1* myPol = new TF1("myPol","[0]*x*x+[1]*x+[2]");
  // do a*x^2+b fit for hist in range [xmin,xmax]
  hist.Fit(myPol,"Q","same",xmin, xmax);
  myPol->SetRange(hist.GetBinLowEdge(1),hist.GetBinLowEdge(hist.GetNbinsX()+1));
  // edit color of fit and extrapolate to whole region of x
  myPol->SetLineColor(color);
  myPol->DrawClone("same");
  std::cout << "a = " << myPol->GetParameter(0) << " +/- " << myPol->GetParError(0) << std::endl;
  std::cout << "b = " << myPol->GetParameter(1) << " +/- " << myPol->GetParError(1) << std::endl;
  std::cout << "c = " << myPol->GetParameter(2) << " +/- " << myPol->GetParError(2) << std::endl;
  std::cout << "chi2/ndof = " << myPol->GetChisquare() / myPol->GetNDF() << std::endl;
  std::cout << "probability = " << TMath::Prob(myPol->GetChisquare(),myPol->GetNDF()) << std::endl;
}

void fitLinearExtrapolate(TH1& hist, const double xmin, const double xmax, const int color, const TString info){
  // print out info
  std::cout << "" << std::endl;
  std::cout << "linear fit: a*x +b for " << info << std::endl;
  std::cout << "-----------------------=----------------------------" << std::endl;
  TF1* myPol = new TF1("myPol","[0]*x+[1]");
  // do a*x^2+b fit for hist in range [xmin,xmax]
  hist.Fit(myPol,"Q","same",xmin, xmax);
  myPol->SetRange(hist.GetBinLowEdge(1),hist.GetBinLowEdge(hist.GetNbinsX()+1));
  // edit color of fit and extrapolate to whole region of x
  myPol->SetLineColor(color);
  myPol->DrawClone("same");
  std::cout << "a = " << myPol->GetParameter(0) << " +/- " << myPol->GetParError(0) << std::endl;
  std::cout << "b = " << myPol->GetParameter(1) << " +/- " << myPol->GetParError(1) << std::endl;
  std::cout << "chi2/ndof = " << myPol->GetChisquare() / myPol->GetNDF() << std::endl;
  std::cout << "probability = " << TMath::Prob(myPol->GetChisquare(),myPol->GetNDF()) << std::endl;
}

std::vector<double> fitExponentialExtrapolate(TH1& hist, const double xmin, const double xmax, const int color, const TString info){
  // print out info
  std::cout << "" << std::endl;
  std::cout << "exponential fit: exp(a*x) +b for " << info << std::endl;
  std::cout << "-----------------------=----------------------------" << std::endl;
  TF1* myPol = new TF1("myPol","exp([0]*x)+[1]");
  // do a*x^2+b fit for hist in range [xmin,xmax]
  hist.Fit(myPol,"Q","same",xmin, xmax);
  myPol->SetRange(hist.GetBinLowEdge(1),hist.GetBinLowEdge(hist.GetNbinsX()+1));
  // edit color of fit and extrapolate to whole region of x
  myPol->SetLineColor(color);
  myPol->DrawClone("same");
  std::cout << "a = " << myPol->GetParameter(0) << " +/- " << myPol->GetParError(0) << std::endl;
  std::cout << "b = " << myPol->GetParameter(1) << " +/- " << myPol->GetParError(1) << std::endl;
  std::cout << "chi2/ndof = " << myPol->GetChisquare() / myPol->GetNDF() << std::endl;
  std::cout << "probability = " << TMath::Prob(myPol->GetChisquare(),myPol->GetNDF()) << std::endl;
  std::vector<double> result_;
  result_ .push_back(myPol->GetParameter(0));
  result_ .push_back(myPol->GetParError(0));
  result_ .push_back(myPol->GetParameter(1));
  result_ .push_back(myPol->GetParError(1));
  return result_;
}

std::pair<double,double> exponentialFit(double x, const double a, const double sa, const double b, const double sb){
  // use parameters from function fitExponentialExtrapolate
  // to calculate weight and error for all je multiplicities
  double weight=0;
  double weightError=0;
  weight=exp(a*x)+b;
  weightError=sqrt( (sa*x)*(sa*x)*exp(2*a*x) + sb*sb );
  return make_pair(weight, weightError);
}


std::vector<double> fitExponentialExtrapolate2(TH1& hist, const double xmin, const double xmax, const int color, const TString info){
  // print out info
  std::cout << "" << std::endl;
  std::cout << "fit: p(1-p)^(n-1) for " << info << std::endl;
  std::cout << "-----------------------=----------------------------" << std::endl;
  TF1* myPol = new TF1("myPol","[0]*(1-[0])^(x-1)");
  // do a*x^2+b fit for hist in range [xmin,xmax]
  hist.Fit(myPol,"Q","same",xmin, xmax);
  myPol->SetRange(hist.GetBinLowEdge(1),hist.GetBinLowEdge(hist.GetNbinsX()+1));
  // edit color of fit and extrapolate to whole region of x
  myPol->SetLineColor(color);
  myPol->DrawClone("same");
  std::cout << "p = " << myPol->GetParameter(0) << " +/- " << myPol->GetParError(0) << std::endl;
  std::cout << "chi2/ndof = " << myPol->GetChisquare() / myPol->GetNDF() << std::endl;
  std::cout << "probability = " << TMath::Prob(myPol->GetChisquare(),myPol->GetNDF()) << std::endl;
  std::vector<double> result_;
  result_ .push_back(myPol->GetParameter(0));
  result_ .push_back(myPol->GetParError(0));
  result_ .push_back(1);
  result_ .push_back(0);
  return result_;
}

// std::pair<double,double> exponentialFit2(double x, const double a, const double sa, const double b, const double sb){
//   // use parameters from function fitExponentialExtrapolate
//   // to calculate weight and error for all je multiplicities
//   double weight=0;
//   double weightError=0;
//   weight=1-exp(a*x);
//   weightError=0;
//   return make_pair(weight, weightError);
// }
