// ---------description-----------------------------------
// -------------------------------------------------------
// this Makro shows the effects of the JES ( +/- 10 % ) 
// and the contribution of signal / background in each bin
// ! careful about the order when reading in files, some
// calculations are sensitive to it !
// -------------------------------------------------------
  
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
#include <TPaveLabel.h>

enum styles {kSig, kWjets, kBkg, kZjets, kQCD, kSigJES11, kWjetsJES11, kBkgJES11, kZjetsJES11, kQCDJES11, kSigJES09, kWjetsJES09, kBkgJES09, kZjetsJES09, kQCDJES09, kPseudo50, kSGBG, kSGBGJES11, kSGBGJES09};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, int filled=0, double lineWidth=3.); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void drawcutline(double cutval, double maximum);
void divideByBinwidth(std::vector<TH1F*> histoVector);
void divideByBinwidth2(TH1F& plot);
double getMaximumDependingOnNjetsCut(TString plot, TString Njets);

void analyzeMuonDiffXJES()
{
  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetErrorX(0); 

  // choose jet multiplicity you want to see: "Njets1" / "Njets2" / "Njets3" / "Njets4" / "Njets4Btag" / "Njets3Btag"
  TString jetMultiplicity ="Njets1";
  // choose whether you want to save every plot as png and all within one ps file
  bool save = false;
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/JESstudies/";
  // choose luminosity for scaling of event numbers and for legend as entry
  int luminosity = 50;
  TString lum = "50";

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;

  TString whichSample = "/spring10Samples/spring10SelV2Sync";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigNloSpring10.root"    ) );
//   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigMadSpring10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecWjetsMadSpring10.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgNloSpring10.root"    ) );
//   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgMadSpring10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecZjetsMadSpring10.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecQCDPythiaSpring10.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigNloSpring10JES11.root"    ) );
//   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigMadSpring10JES11.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecWjetsMadSpring10JES11.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgNloSpring10JES11.root"    ) );
//   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgMadSpring10JES11.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecZjetsMadSpring10JES11.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecQCDPythiaSpring10JES11.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigNloSpring10JES09.root"    ) );
//   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigMadSpring10JES09.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecWjetsMadSpring10JES09.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgNloSpring10JES09.root"    ) );
//   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgMadSpring10JES09.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecZjetsMadSpring10JES09.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecQCDPythiaSpring10JES09.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/spring10PseudoData7TeV"+lum+"pb.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> pt_;

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    pt_    .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/pt") );
   }

  // ---
  //    define weights concerning luminosity for 50 pb-1 @ 7TeV
  // ---
  std::vector<double> lumiweight;
  // 7 TeV Monte Carlo spring 10 samples
  // -----------------------------------
  // MC@NLO signal / Madgraph signal / W+jets Madgraph / MC@NLO background / Madgraph background/ Z+jets Madgraph / QCD Pythia

  // a) unshifted:
  lumiweight.push_back(0.007940958/50.0*(double)luminosity);
//   lumiweight.push_back(0.005308736/50.0*(double)luminosity);
  lumiweight.push_back(0.155498692/50.0*(double)luminosity);
  lumiweight.push_back(0.007940958/50.0*(double)luminosity);
//   lumiweight.push_back(0.005308736/50.0*(double)luminosity);
  lumiweight.push_back(0.140471057/50.0*(double)luminosity);
  lumiweight.push_back(0.910264515/50.0*(double)luminosity);

  // b) for JES-shifted samples (first +10%, then -10%)-> taken from above:
  lumiweight.push_back(lumiweight[0]);
//   lumiweight.push_back(lumiweight[0]);
  lumiweight.push_back(lumiweight[1]);
  lumiweight.push_back(lumiweight[2]);
//   lumiweight.push_back(lumiweight[2]);
  lumiweight.push_back(lumiweight[3]);
  lumiweight.push_back(lumiweight[4]);
  lumiweight.push_back(lumiweight[0]);
//   lumiweight.push_back(lumiweight[0]);
  lumiweight.push_back(lumiweight[1]);
  lumiweight.push_back(lumiweight[2]);
//   lumiweight.push_back(lumiweight[2]);
  lumiweight.push_back(lumiweight[3]);
  lumiweight.push_back(lumiweight[4]);
  // c) for pseudodata
  lumiweight.push_back(1.0);

  // ---
  //    do lumiweighting
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    pt_ [idx]->Scale(lumiweight[idx]);
  }

  // ---  
  //    clone plots to have also #events(pT#muon) and not only d#sigma/dpT(#muon)*1/#sigma )(pT#muon)
  // ---
  
  std::vector<TH1F*> ptEventNumbers_;
  
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    ptEventNumbers_ .push_back( (TH1F*)(pt_ [idx]->Clone()) );
  }
  ptEventNumbers_.push_back ( (TH1F*)(ptEventNumbers_[kSig]->Clone()) );
  for(unsigned int idx=kWjets; idx<=kQCD; ++idx) {
    ptEventNumbers_[kSGBG]->Add(ptEventNumbers_[idx]);
  }
  ptEventNumbers_.push_back ( (TH1F*)(ptEventNumbers_[kSigJES11]->Clone()) );
  for(unsigned int idx=kWjetsJES11; idx<=kQCDJES11; ++idx) {
    ptEventNumbers_[kSGBGJES11]->Add(ptEventNumbers_[idx]);
  }
   ptEventNumbers_.push_back ( (TH1F*)(ptEventNumbers_[kSigJES09]->Clone()) );
  for(unsigned int idx=kWjetsJES09; idx<=kQCDJES09; ++idx) {
    ptEventNumbers_[kSGBGJES09]->Add(ptEventNumbers_[idx]);
  }
 
  // ---  
  //    print out weighted event numbers for all files
  // ---

  std::vector<double> entriesPt_;

  for(unsigned int idx=0; idx<files_.size()-1; ++idx) {
    entriesPt_.push_back ( pt_ [idx]->Integral() );
    std::cout << "total weighted # of events in pt (file " << idx << "): " << entriesPt_[idx] << std::endl;
  }
  std::cout << "total # of events in pseudo data: " << pt_ [15]->Integral() << std::endl;
  
  // ---
  //    do scaling with respect to inclusive cross section (taken from same histogram) and division by binwidth
  // ---
  
  for(unsigned int idx=0; idx<files_.size(); ++idx) {

    pt_  [idx]->Scale(1/entriesPt_ [idx]);
    for(int i=1; i<= pt_[idx]->GetNbinsX(); i++){
      pt_[idx]->SetBinContent(i,((double)(pt_[idx]->GetBinContent(i))/(double)(pt_[idx]->GetBinWidth(i)))  );
    }
  }
 
  // ---
  //    diffXSec plot for signal + background for datalike signature (also JES +/- 10%)
  // ---
  
  // a) creating
  pt_.push_back( (TH1F*)(ptEventNumbers_[kSig]->Clone()) );
  pt_.push_back( (TH1F*)(ptEventNumbers_[kSigJES11]->Clone()) );
  pt_.push_back( (TH1F*)(ptEventNumbers_[kSigJES09]->Clone()) );

 for(int idx=kWjets; idx<=kQCD; ++idx) {
    pt_[kSGBG]->Add(ptEventNumbers_[idx]);
  }
 for(int idx=kWjetsJES11; idx<=kQCDJES11; ++idx) {
    pt_[kSGBGJES11]->Add(ptEventNumbers_[idx]);
  }
 for(int idx=kWjetsJES09; idx<=kQCDJES09; ++idx) {
    pt_[kSGBGJES09]->Add(ptEventNumbers_[idx]);
  }

  // b) scaling with respect to inclusive XSec
  pt_[kSGBG     ]->Scale(  1/ ((double)(entriesPt_[kSig]+entriesPt_[kBkg]+entriesPt_[kQCD]+entriesPt_[kWjets]+entriesPt_[kZjets]))  );
  pt_[kSGBGJES11]->Scale(  1/ ((double)(entriesPt_[kSigJES11]+entriesPt_[kBkgJES11]+entriesPt_[kQCDJES11]+entriesPt_[kWjetsJES11]+entriesPt_[kZjetsJES11]))  );
  pt_[kSGBGJES09]->Scale(  1/ ((double)(entriesPt_[kSigJES09]+entriesPt_[kBkgJES09]+entriesPt_[kQCDJES09]+entriesPt_[kWjetsJES09]+entriesPt_[kZjetsJES09]))  );


  // c) division by binwidth
  for(int i=1; i<= pt_[kSGBG]->GetNbinsX(); i++){
    pt_[kSGBG     ]->SetBinContent(i,((double)(pt_[kSGBG]->GetBinContent(i))/(double)(pt_[kSGBG]->GetBinWidth(i)))  );
    pt_[kSGBGJES11]->SetBinContent(i,((double)(pt_[kSGBGJES11]->GetBinContent(i))/(double)(pt_[kSGBGJES11]->GetBinWidth(i)))  );
    pt_[kSGBGJES09]->SetBinContent(i,((double)(pt_[kSGBGJES09]->GetBinContent(i))/(double)(pt_[kSGBGJES09]->GetBinWidth(i)))  );
  }

 // clone histograms for drawing without error bars
  TH1F *ptEventNumbersSigNoErrors= (TH1F*)ptEventNumbers_[kSig]->Clone();

  // ---
  //    get and print some numbers
  // ---

  // a) get total number of filled bins above cut value of 20 GeV from pt histo
  int totalBinNumber = (pt_[kSig]->GetNbinsX())-1;
  std::cout << "total bin number between 20 and 200 GeV: " << totalBinNumber << std::endl;
 
  // b) get binning values from pt histo
  std::vector<int> binValue_;
  for(int i=1; i<= totalBinNumber+2; i++){
    // +2 for underflow bin and upper Edge of last bin
    binValue_.push_back(pt_[kSig]->GetBinLowEdge(i));
    std::cout << "lower edge bin " << i << " :" << binValue_[i-1] << std::endl;
  }

  // c) print out event composition (lumi weighted) in each pt - bin
  std::cout << "---(weighted) event composition per pt-bin---"<< std::endl;
  std::cout << "( ttbarsig / ttbar bkg / W+jets / Z+jets / QCD / Pseudodata no shift)::"<< std::endl;
  std::cout << "a) ohne JES:"<< std::endl;

  for(int i=2; i<= pt_[kSig]->GetNbinsX()+1; i++){
    std::cout << "pt-bin "<< i << ": ( " <<  ptEventNumbers_[kSig]->GetBinContent(i) << " / " <<  ptEventNumbers_[kBkg]->GetBinContent(i) <<" / " << ptEventNumbers_[kWjets]->GetBinContent(i) <<" / " <<   ptEventNumbers_[kZjets]->GetBinContent(i)  <<" / " <<   ptEventNumbers_[kQCD]->GetBinContent(i) << " / " <<   ptEventNumbers_[kPseudo50]->GetBinContent(i) <<" ) " << std::endl;
  }
  std::cout << "b) JES +10% :"<< std::endl;
  for(int i=2; i<= pt_[kSigJES11]->GetNbinsX()+1; i++){
    std::cout << "pt-bin "<< i << ": ( " <<  ptEventNumbers_[kSigJES11]->GetBinContent(i) << " / " <<  ptEventNumbers_[kBkgJES11]->GetBinContent(i) <<" / " << ptEventNumbers_[kWjetsJES11]->GetBinContent(i) <<" / " <<   ptEventNumbers_[kZjetsJES11]->GetBinContent(i) << " / " <<   ptEventNumbers_[kQCDJES11]->GetBinContent(i) <<" ) " << std::endl;
  }
  std::cout << "c) JES -10% :"<< std::endl;
  for(int i=2; i<= pt_[kSigJES09]->GetNbinsX()+1; i++){
    std::cout << "pt-bin "<< i << ": ( " <<  ptEventNumbers_[kSigJES09]->GetBinContent(i) << " / " <<  ptEventNumbers_[kBkgJES09]->GetBinContent(i) <<" / " << ptEventNumbers_[kWjetsJES09]->GetBinContent(i) <<" / " <<   ptEventNumbers_[kZjetsJES09]->GetBinContent(i) << " / " <<   ptEventNumbers_[kQCDJES09]->GetBinContent(i) <<" ) " << std::endl;
  } 

  // ---
  //    calculate statistical error for diff. XSec via gaussian error calculus
  // ---

  std::vector<double> ptDiffXError_, ptDiffXPseudoError_, ptDiffXAllSamplesError_;

  //  a) for signal

  // i: calculation for each bin (starting with filled bin-> i=2, take care totalBinNumber starts counting at 2nd bin -> +1)
  for(int i =2; i<=totalBinNumber+1; i++){

    // calculate shortcut expression needed in final formula
    double errorHelperA=0;  
    errorHelperA= ( (double)(pt_[kSig]->GetBinWidth(i)) * entriesPt_[kSig] ); 

    // final formula for total cross section taken from same histogram
    ptDiffXError_.push_back(   sqrt(  ((double)(ptEventNumbers_ [kSig]->GetBinContent(i)) / errorHelperA / errorHelperA) * ( 1.0 - 2.0 * (double)(pt_[kSig]->GetBinWidth(i)) / errorHelperA + ( (double)(ptEventNumbers_ [kSig]->GetBinContent(i)) * (double)(pt_[kSig]->GetBinWidth(i)) * (double)(pt_[kSig]->GetBinWidth(i)) * (entriesPt_[kSig])  / errorHelperA / errorHelperA) )  )   );
  }
  //  b) for pseudo data

  // i: calculation for each bin (starting with filled bin-> i=2, take care totalBinNumber starts counting at 2nd bin -> +1)
  for(int i =2; i<=totalBinNumber+1; i++){

    // calculate shortcut expression needed in final formula
    double errorHelperA=0;  
    errorHelperA= ( (double)(pt_[kPseudo50]->GetBinWidth(i)) * entriesPt_[kPseudo50] ); 

    // final formula for total cross section taken from same histogram
    ptDiffXPseudoError_.push_back(   sqrt(  ((double)(ptEventNumbers_ [kPseudo50]->GetBinContent(i)) / errorHelperA / errorHelperA) * ( 1.0 - 2.0 * (double)(pt_[kPseudo50]->GetBinWidth(i)) / errorHelperA + ( (double)(ptEventNumbers_ [kPseudo50]->GetBinContent(i)) * (double)(pt_[kPseudo50]->GetBinWidth(i)) * (double)(pt_[kPseudo50]->GetBinWidth(i)) * (entriesPt_[kPseudo50])  / errorHelperA / errorHelperA) )  )   );
  }

  //  c) for all events surviving the selection

  // i: calculation for each bin (starting with filled bin-> i=2, take care totalBinNumber starts counting at 2nd bin -> +1)
  for(int i =2; i<=totalBinNumber+1; i++){

    // calculate shortcut expression needed in final formula
    double errorHelperA=0;
    double totalEventNumbers = entriesPt_[kSig]+entriesPt_[kBkg]+entriesPt_[kZjets]+entriesPt_[kWjets]+entriesPt_[kQCD];
    double totalBinContent = (double)(ptEventNumbers_ [kSig]->GetBinContent(i))+ (double)(ptEventNumbers_ [kBkg]->GetBinContent(i)) +  (double)(ptEventNumbers_ [kWjets]->GetBinContent(i)) + (double)(ptEventNumbers_ [kZjets]->GetBinContent(i)) + (double)(ptEventNumbers_ [kQCD]->GetBinContent(i));

    errorHelperA= ( (double)(pt_[kSig]->GetBinWidth(i)) * totalEventNumbers ); 

    // final formula for total cross section taken from same histogram
    ptDiffXAllSamplesError_.push_back(   sqrt(  (totalBinContent / errorHelperA / errorHelperA) * ( 1.0 - 2.0 * (double)(pt_[kSig]->GetBinWidth(i)) / errorHelperA + (  totalBinContent * (double)(pt_[kSig]->GetBinWidth(i)) * (double)(pt_[kSig]->GetBinWidth(i)) * (totalEventNumbers)  / errorHelperA / errorHelperA) )  )   );
  }

  // ---
  //     print out diffXValue(pt) for each bin with statistical errors
  // ---
  
  for(int i=2; i<= pt_[kSig]->GetNbinsX(); i++){
    std::cout << "(d#sigma)/(dpt(muon) * #sigma) Signal  pt-bin "<< i << ": " <<  pt_[kSig]->GetBinContent(i) << " +/- " <<  ptDiffXError_[i-2] << std::endl;
  }

  // ---
  //     event composition after cuts in rel. numbers (with respect to total bin entries)
  // ---

  THStack *compositionRel=new THStack ("compositionRel","");
  THStack *compositionRelJES11=new THStack ("compositionRelJES11","");
  THStack *compositionRelJES09=new THStack ("compositionRelJES09","");
  std::vector<TH1F*> ptEventNumbersRel_;

  // create relative plots

  for(int idx=kSig; idx<=kQCD; idx++){
    ptEventNumbersRel_ .push_back( (TH1F*)ptEventNumbers_[idx]->Clone() );

    // calculate value for each bin i
    for(int i=2; i<=pt_[kSig]->GetNbinsX(); i++){
      ptEventNumbersRel_[idx]->SetBinContent(  i, (ptEventNumbersRel_[idx]->GetBinContent(i) ) / ( ptEventNumbersSigNoErrors->GetBinContent(i)+ptEventNumbers_[kWjets]->GetBinContent(i)+ptEventNumbers_[kBkg]->GetBinContent(i)+ptEventNumbers_[kZjets]->GetBinContent(i)+ptEventNumbers_[kQCD]->GetBinContent(i) )  );
    }
    compositionRel->Add(ptEventNumbersRel_[idx],"HIST"); 
  }

  for(int idx=kSigJES11; idx<=kQCDJES11; idx++){
    ptEventNumbersRel_ .push_back( (TH1F*)ptEventNumbers_[idx]->Clone() );

    // calculate value for each bin i
    for(int i=2; i<=pt_[kSigJES11]->GetNbinsX(); i++){
      ptEventNumbersRel_[idx]->SetBinContent(  i, (ptEventNumbersRel_[idx]->GetBinContent(i) ) / ( ptEventNumbers_[kSigJES11]->GetBinContent(i)+ptEventNumbers_[kWjetsJES11]->GetBinContent(i)+ptEventNumbers_[kBkgJES11]->GetBinContent(i)+ptEventNumbers_[kZjetsJES11]->GetBinContent(i)+ptEventNumbers_[kQCDJES11]->GetBinContent(i) )  );
    }
    
    compositionRelJES11->Add(ptEventNumbersRel_[idx],"HIST"); 
  }

    for(int idx=kSigJES09; idx<=kQCDJES09; idx++){
    ptEventNumbersRel_ .push_back( (TH1F*)ptEventNumbers_[idx]->Clone() );

    // calculate value for each bin i
    for(int i=2; i<=pt_[kSigJES09]->GetNbinsX(); i++){
      ptEventNumbersRel_[idx]->SetBinContent(  i, (ptEventNumbersRel_[idx]->GetBinContent(i) ) / ( ptEventNumbers_[kSigJES09]->GetBinContent(i)+ptEventNumbers_[kWjetsJES09]->GetBinContent(i)+ptEventNumbers_[kBkgJES09]->GetBinContent(i)+ptEventNumbers_[kZjetsJES09]->GetBinContent(i)+ptEventNumbers_[kQCDJES09]->GetBinContent(i) )  );
    }
    compositionRelJES09->Add(ptEventNumbersRel_[idx],"HIST"); 
    }
    
    THStack *compositionJES11=new THStack ("compositionJES11","");
    THStack *composition     =new THStack ("composition","");
    THStack *compositionJES09=new THStack ("compositionJES09","");
    histogramStyle(*ptEventNumbersSigNoErrors, kRed, 1, 22, 3006);
    histogramStyle(*ptEventNumbers_[kWjets], kGreen, 1, 20, 3004);
    histogramStyle(*ptEventNumbers_[kBkg  ], kBlue,  1, 23, 3007);
    histogramStyle(*ptEventNumbers_[kZjets], 6,      1, 21, 3005);
    histogramStyle(*ptEventNumbers_[kQCD  ], 17,     1, 29, 1001); 
    histogramStyle(* ptEventNumbers_[kSigJES11  ], kRed,   1, 22, 3006);
    histogramStyle(* ptEventNumbers_[kWjetsJES11], kGreen, 1, 20, 3004);
    histogramStyle(* ptEventNumbers_[kBkgJES11  ], kBlue,  1, 23, 3007);
    histogramStyle(* ptEventNumbers_[kZjetsJES11], 6,      1, 21, 3005);
    histogramStyle(* ptEventNumbers_[kQCDJES11  ], 17,     1, 29, 1001); 
    histogramStyle(* ptEventNumbers_[kSigJES09  ], kRed,   1, 22, 3006);
    histogramStyle(* ptEventNumbers_[kWjetsJES09], kGreen, 1, 20, 3004);
    histogramStyle(* ptEventNumbers_[kBkgJES09  ], kBlue,  1, 23, 3007);
    histogramStyle(* ptEventNumbers_[kZjetsJES09], 6,      1, 21, 3005);
    histogramStyle(* ptEventNumbers_[kQCDJES09  ], 17,     1, 29, 1001);
    composition->Add(ptEventNumbersSigNoErrors);
    for(int idx=kWjets; idx<=kQCD; idx++){
      composition->Add(ptEventNumbers_[idx] );
    }
    for(int idx=kSigJES11; idx<=kQCDJES11; idx++){
      compositionJES11->Add(ptEventNumbers_[idx] );
    }
    for(int idx=kSigJES09; idx<=kQCDJES09; idx++){
      compositionJES09->Add(ptEventNumbers_[idx] );
    }
    histogramStyle(* ptEventNumbersRel_[kSig], kRed, 1, 22, 0, 4.);
    for(int idx=kWjets; idx<=kQCD; idx++){
      histogramStyle(* ptEventNumbersRel_[idx], ptEventNumbers_[idx]->GetLineColor(), 1, ptEventNumbers_[idx]->GetMarkerStyle(), 0, 4);
    }
    for(int idx=kSigJES11; idx<=kQCDJES11; idx++){
      histogramStyle(* ptEventNumbersRel_[idx], ptEventNumbers_[idx]->GetLineColor(), 6, 9, 0, 4.);
    }
    for(int idx=kSigJES09; idx<=kQCDJES09; idx++){
      histogramStyle(* ptEventNumbersRel_[idx], ptEventNumbers_[idx]->GetLineColor(), 7, 9, 0, 4.);
    }
        
    // ---
    //    divide plots with event numbers by binwidth to have natural form of spectrum
    // ---      
    divideByBinwidth(ptEventNumbers_ );
    divideByBinwidth2(*ptEventNumbersSigNoErrors);

    // ---
    //    create legends 
    // ---
    
    // create a legend for relative plot with underground
    TLegend *leg0 = new TLegend(0.01, 0.31, 0.55, 0.72);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetHeader("MC samples @ 7TeV");
    leg0->AddEntry( ptEventNumbersRel_[kSig]       , "semi #mu t#bar{t} Mc@Nlo", "PL");
    leg0->AddEntry( ptEventNumbersRel_[kBkg]       , "other t#bar{t} Mc@Nlo"   , "PL");
    leg0->AddEntry( ptEventNumbersRel_[kQCD]       , "QCD Pythia"              , "PL");
    leg0->AddEntry( ptEventNumbersRel_[kWjets]     , "Wjets Madgraph"          , "PL");
    leg0->AddEntry( ptEventNumbersRel_[kZjets]     , "Zjets Madgraph"          , "PL");
 
    // create a legend for relative plot with underground
    TLegend *leg1 = new TLegend(0.48, 0.31, 0.83, 0.72);
    leg1->SetFillStyle(0);
    leg1->SetBorderSize(0);
    leg1->SetHeader("-10%");
    leg1->SetMargin(0.5);
    leg1->AddEntry( ptEventNumbersRel_[kSigJES09]       , " "   , "PL");
    leg1->AddEntry( ptEventNumbersRel_[kBkgJES09]       , " "   , "PL");
    leg1->AddEntry( ptEventNumbersRel_[kQCDJES09]       , " "   , "PL");
    leg1->AddEntry( ptEventNumbersRel_[kWjetsJES09]     , " "   , "PL");
    leg1->AddEntry( ptEventNumbersRel_[kZjetsJES09]     , " "   , "PL");

    // create a legend for relative plot with underground
    TLegend *leg2 = new TLegend(0.65, 0.31, 1.00, 0.72);
    leg2->SetFillStyle(0);
    leg2->SetBorderSize(0);
    leg2->SetHeader("+10%");
    leg2->SetMargin(0.5);
    leg2->AddEntry( ptEventNumbersRel_[kSigJES11]       , " "   , "PL");
    leg2->AddEntry( ptEventNumbersRel_[kBkgJES11]       , " "   , "PL");
    leg2->AddEntry( ptEventNumbersRel_[kQCDJES11]       , " "   , "PL");
    leg2->AddEntry( ptEventNumbersRel_[kWjetsJES11]     , " "   , "PL");
    leg2->AddEntry( ptEventNumbersRel_[kZjetsJES11]     , " "   , "PL");  

    // create a legend for Signal, JES +/- 10%
    TLegend *leg3 = new TLegend(0.27, 0.70, 1.05, 0.93);
    leg3->SetFillStyle(0);
    leg3->SetBorderSize(0);
    leg3->SetHeader(lum+" pb^{-1} @ 7TeV (t#bar{t}(#mu) MC@NLO only)");
    leg3->AddEntry( pt_[kSig]     , "JES #pm 0 %", "PL");
    leg3->AddEntry( pt_[kSigJES11], "JES +10 %"  , "L");
    leg3->AddEntry( pt_[kSigJES09], "JES -10 %"  , "L");
    
    // create a legend for stack plot with underground
    TLegend *leg4 = new TLegend(0.03, 0.25, 1.00, 0.87);
    leg4->SetFillStyle(0);
    leg4->SetBorderSize(0);
    leg4->SetHeader(lum+" pb^{-1} @ 7TeV MC samples");
    leg4->AddEntry( ptEventNumbersSigNoErrors , "semi #mu t#bar{t} (Mc@Nlo)", "F" );
    leg4->AddEntry( ptEventNumbers_[kBkg]     , "other t#bar{t} (Mc@Nlo)"   , "F" );
    leg4->AddEntry( ptEventNumbers_[kQCD]     , "QCD (Pythia)"              , "F" );
    leg4->AddEntry( ptEventNumbers_[kWjets]   , "Wjets (Madgraph)"          , "F" );
    leg4->AddEntry( ptEventNumbers_[kZjets]   , "Zjets (Madgraph)"          , "F" );
    // leg4->AddEntry( ptEventNumbers_[kPseudo50], "pseudo data"          , "P");
    
    // create a legend for diffX pt(mu) (all left events after selektion, JES +/- 10%)
    TLegend *leg5 = new TLegend(0.25, 0.68, 0.90, 0.90);
    leg5->SetFillStyle(0);
    leg5->SetBorderSize(0);
    leg5->SetHeader("all MC samples (7 TeV @ "+lum+" pb^{-1})");
    leg5->AddEntry( pt_[kSGBG]     , "JES #pm 0 %", "PL");
    leg5->AddEntry( pt_[kSGBGJES11], "JES +10 %"  , "L");
    leg5->AddEntry( pt_[kSGBGJES09], "JES -10 %"  , "L");
   
    // create jet multiplicity label  
    TString jetMultiplicityLabel="";
    TString jetMultiplicityLabelbtag="";
    if(jetMultiplicity=="Njets1")jetMultiplicityLabel="N(Jets) #geq 1";
    if(jetMultiplicity=="Njets2")jetMultiplicityLabel="N(Jets) #geq 2";
    if(jetMultiplicity=="Njets3")jetMultiplicityLabel="N(Jets) #geq 3";
    if(jetMultiplicity=="Njets4")jetMultiplicityLabel="N(Jets) #geq 4";
    TPaveLabel *leg6 = new TPaveLabel(0.50, 0.74, 1.0, 1.0, jetMultiplicityLabel, "br NDC");
    leg6->SetFillStyle(0);
    leg6->SetBorderSize(0);
    leg6->SetTextSize(0.26);
    // create JES labels
    TPaveLabel *leg7 = new TPaveLabel(0.50, 0.65, 1.0, 0.90, "JES #pm 0 %", "br NDC");
    leg7->SetFillStyle(0);
    leg7->SetBorderSize(0);
    leg7->SetTextSize(0.26);
    TPaveLabel *leg8 = new TPaveLabel(0.50, 0.65, 1.0, 0.90, "JES -10 %", "br NDC");
    leg8->SetFillStyle(0);
    leg8->SetBorderSize(0);
    leg8->SetTextSize(0.26);
    TPaveLabel *leg9 = new TPaveLabel(0.50, 0.65, 1.0, 0.90, "JES +10 %", "br NDC");
    leg9->SetFillStyle(0);
    leg9->SetBorderSize(0);
    leg9->SetTextSize(0.26);
    TPaveLabel *leg10 = new TPaveLabel(0.39, 0.64, 0.89, 0.89, "JES:", "br NDC");
    leg10->SetFillStyle(0);
    leg10->SetBorderSize(0);
    leg10->SetTextSize(0.26);

    std::vector<TCanvas*> MyCanvas;   
    for(int idx=0; idx<=9; idx++){ 
      char canvname[10];
      sprintf(canvname,"canv%i",idx);    
      MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
      canvasStyle(*MyCanvas[idx]);
    }
    
    // ---
    //    do the printing for pt_ ( normalized,DIFFerential xSec ttbar(muon) only with JES +/-10% )
    // ---
    MyCanvas[0]->cd(0);
    MyCanvas[0]->SetTitle("ptDiffXSecSignalJESEffectMcatnlo7TeV"+lum+"pb"+jetMultiplicity);
    axesStyle(*pt_ [kSig], "p_{t} ( #mu ) [GeV]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{t}(#mu)} [ GeV^{-1} ]", 0., 0.035, 0.04, 2.2);
    histogramStyle(*pt_  [kSig]     , kBlack, 1);
    pt_[kSig]->SetMarkerSize(1.0);
    histogramStyle(*pt_  [kSigJES11], kBlue,  2);
    histogramStyle(*pt_  [kSigJES09], kRed,   2);
    pt_ [kSig]->SetBinError( 1, 0. );
    for(int i =2; i<= totalBinNumber+1; i++){
      pt_ [kSig]->SetBinError(  i, ptDiffXError_[i-2]  );
    }
    pt_ [kSig]     ->Draw("HIST");
    pt_ [kSig]     ->Draw("esame");
    pt_ [kSigJES11]->Draw("same");
    pt_ [kSigJES09]->Draw("same");
    leg3           ->Draw("same");
    
    // ---
    //    do the printing for pt_ ( normalized,DIFFerential xSec signal + background with JES +/-10% )
    // ---
    MyCanvas[1]->cd(0);
    MyCanvas[1]->SetTitle("ptDiffXSecAllJESEffect7TeV"+lum+"pb"+jetMultiplicity);
    axesStyle(*pt_ [kSGBG], "p_{t} ( #mu ) [GeV]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{t}(#mu)} [ GeV^{-1} ]", 0., getMaximumDependingOnNjetsCut("ptDiff",jetMultiplicity), 0.04, 2.2);
    histogramStyle(*pt_ [kSGBG]     , kBlack, 1);
    pt_[kSGBG]->SetMarkerSize(1.0);
    histogramStyle(*pt_ [kSGBGJES11], kBlue,  2);
    histogramStyle(*pt_ [kSGBGJES09], kRed ,  2);
    for(int i =2; i<= totalBinNumber+1; i++){
      pt_[kSGBG]->SetBinError( i, ptDiffXAllSamplesError_[i-2] );
    }
    pt_ [kSGBG]     ->Draw("HIST");
    pt_ [kSGBG]     ->Draw("esame");
    pt_ [kSGBGJES11]->Draw("same");
    pt_ [kSGBGJES09]->Draw("same");
    leg5            ->Draw("same");

  // ---
  //    do the printing for ptEventNumbers_ ( eventNUMBERs/binwidth in pt(muon) for ttbar(muon) only with JES +/-10% )
  // ---
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetTitle("ptInclusiveSignalJESEffectMcatnlo7TeV"+lum+"pb"+jetMultiplicity);
  axesStyle(*ptEventNumbers_ [kSig], "p_{t} ( #mu ) [GeV]", "events / GeV", 0., getMaximumDependingOnNjetsCut("ptSignal",jetMultiplicity));
  TH1F *ptEvtsJES11= (TH1F*)(ptEventNumbers_ [kSigJES11]->Clone());
  TH1F *ptEvtsJES09= (TH1F*)(ptEventNumbers_ [kSigJES09]->Clone());
  histogramStyle(*ptEventNumbers_ [kSig], kBlack, 1);
  ptEventNumbers_[kSig]->SetMarkerSize(1.0);
  histogramStyle(*ptEvtsJES11,            kBlue , 2, 20, 0);
  histogramStyle(*ptEvtsJES09,            kRed  , 2, 20, 0);
  ptEventNumbers_ [kSig]->SetBinError( 1, 0. );
  for(int i =2; i<= totalBinNumber+1; i++){
    ptEventNumbers_ [kSig]->SetBinError(  i, sqrt( (double)(ptEventNumbers_[kSig]->GetBinContent(i)) ) / sqrt( (double)(ptEventNumbers_[kSig]->GetBinWidth(i)) )  );
  }
  ptEventNumbers_ [kSig]->Draw("HIST");
  ptEvtsJES11->Draw("same");
  ptEvtsJES09->Draw("same");
  ptEventNumbers_ [kSig]->Draw("esame");
  leg3       ->Draw("same");

  // ---
  //    do the printing for ptEventNumbers_ ( eventNUMBERs/binwidth in pt(muon) for signal + background with JES +/-10% )
  // ---
  MyCanvas[3]->cd(0);
  MyCanvas[3]->SetTitle("ptInclusiveAllJESEffect7TeV"+lum+"pb"+jetMultiplicity);
  axesStyle(*ptEventNumbers_ [kSGBG], "p_{t} ( #mu ) [GeV]", "events / GeV", 0., 1.7*getMaximumDependingOnNjetsCut("ptStack",jetMultiplicity), 0.05, 1.4);
  histogramStyle(*ptEventNumbers_ [kSGBG]     , kBlack, 1);
  ptEventNumbers_[kSGBG]->SetMarkerSize(1.0);
  histogramStyle(*ptEventNumbers_ [kSGBGJES11], kBlue,  2);
  histogramStyle(*ptEventNumbers_ [kSGBGJES09], kRed,   2);
  for(int i =2; i<= totalBinNumber+1; i++){
    ptEventNumbers_ [kSGBG]->SetBinError(  i, sqrt( (double)(ptEventNumbers_[kSGBG]->GetBinContent(i)) ) / sqrt( (double)(ptEventNumbers_[kSGBG]->GetBinWidth(i)) )  );
  }
  ptEventNumbers_ [kSGBG     ]->Draw("HIST");
  ptEventNumbers_ [kSGBGJES11]->Draw("same");
  ptEventNumbers_ [kSGBGJES09]->Draw("same");
  ptEventNumbers_ [kSGBG     ]->Draw("esame");
  leg5                        ->Draw("same");

  // ---
  //    do the printing for EventNumbers ( eventNUMBERs/binwidth in pt(muon) for signal + background and pseudo data as STACK plot )
  // ---

  MyCanvas[4]->cd(0);
  MyCanvas[4]->SetTitle("eventCompositionNoJES"+lum+"pb"+jetMultiplicity);
  axesStyle(*ptEventNumbersSigNoErrors, "p_{t} ( #mu ) [GeV]", "events / GeV", -123., getMaximumDependingOnNjetsCut("ptStack",jetMultiplicity), 0.05, 1.4 );
  histogramStyle(*ptEventNumbers_[kPseudo50], kBlack, 1, 22);
  ptEventNumbersSigNoErrors->Draw("AXIS");
  composition              ->Draw("same");
  for(int i =2; i<= totalBinNumber+1; i++){
    ptEventNumbers_[kPseudo50]->SetBinError(  i, (int)sqrt((double)ptEventNumbers_[kPseudo50]->GetBinContent(i)) / sqrt( (double)(ptEventNumbers_[kPseudo50]->GetBinWidth(i)) )  );
  }
  //  ptEventNumbers_[kPseudo50]->Draw("psame");
  leg6                      ->Draw("same");
  leg7                      ->Draw("same");

  // ---
  //    do the printing for EventNumbers ( with JES+10%: eventNUMBERs/binwidth in pt(muon) for signal + background as STACK plot )
  // ---
  MyCanvas[5]->cd(0);
  MyCanvas[5]->SetTitle("eventCompositionJES11"+lum+"pb"+jetMultiplicity);
  ptEventNumbersSigNoErrors->Draw("AXIS");
  compositionJES11         ->Draw("same");
  leg6                     ->Draw("same");
  leg9                     ->Draw("same");

  // ---
  //    do the printing for EventNumbers ( with JES-10%: eventNUMBERs/binwidth in pt(muon) for signal + background as STACK plot )
  // ---
  MyCanvas[6]->cd(0);
  MyCanvas[6]->SetTitle("eventCompositionJES09"+lum+"pb"+jetMultiplicity);
  ptEventNumbersSigNoErrors->Draw("AXIS");
  compositionJES09         ->Draw("same");
  leg6                     ->Draw("same");
  leg8                     ->Draw("same");

  // ---
  //    do the printing for EventNumbers (  with and without JES: eventNUMBERs in pt(muon) for signal + background as REALTIVE plot )
  // ---
  float maxRel =1.2;
  MyCanvas[7]->cd(0);
  MyCanvas[7]->SetTitle("eventCompositionRelativeWithAndWithoutJES"+lum+"pb"+jetMultiplicity);
  MyCanvas[7]->SetGrid(1,1);
  axesStyle(*ptEventNumbersRel_[kSigJES09], "p_{t} ( #mu ) [GeV]", "fraction (events)", -123., maxRel);
  ptEventNumbersRel_[kSigJES09]->Draw("");
  for(int idx=kSig; idx<=kQCDJES09; idx++){
    ptEventNumbersRel_[idx]->Draw("same");
    ptEventNumbersRel_[idx]->Draw("Psame");
  }
  leg6->Draw("same");

  // ---
  //    do the printing for stack plot legend
  // ---
  MyCanvas[8]->cd(0);
  MyCanvas[8]->SetTitle("legendStackPlotJES"+lum+"pb"+jetMultiplicity);
  leg4       ->Draw("same");

  // ---
  //    do the printing for relative event composition plot legend
  // ---
  MyCanvas[9]->cd(0);
  MyCanvas[9]->SetTitle("legendFractionPlotJES"+lum+"pb"+jetMultiplicity);
  leg0->Draw("same");
  leg1->Draw("same");
  leg2->Draw("same");
  leg10->Draw("same");

  // ---
  // saving
  // ---

  if(save){    
    // ps
    MyCanvas[0]->Print(saveTo+"diffXJESandBGMcatnlo7TeV"+lum+"pb"+jetMultiplicity+".ps("  );
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+"diffXJESandBGMcatnlo7TeV"+lum+"pb"+jetMultiplicity+".ps"  );   
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+"diffXJESandBGMcatnlo7TeV"+lum+"pb"+jetMultiplicity+".ps)"  );
  
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

void histogramStyle(TH1& hist, int color, int lineStyle, int markerStyle, int filled, double lineWidth) 
{
  hist.SetLineWidth(lineWidth);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color);
  hist.SetMarkerColor(color);  
  hist.SetMarkerStyle(markerStyle);
  hist.SetMarkerSize(1.5);
  hist.SetLineStyle(lineStyle);
  if(filled!=0){
  hist.SetFillStyle(filled);
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

void divideByBinwidth(std::vector<TH1F*> histoVector)
{
  // loop over every sample of one histo
  for(unsigned int idx=0; idx<histoVector.size(); idx++){
    // loop over every bin    
    for(int bini=1; bini<= histoVector[idx]->GetNbinsX(); bini++){
      histoVector[idx]->SetBinContent(bini,((double)(histoVector[idx]->GetBinContent(bini))/(double)(histoVector[idx]->GetBinWidth(bini)))  );
    }
  } 
}

void divideByBinwidth2(TH1F& plot)
{
  // loop over every bin    
  for(int bini=1; bini<= plot.GetNbinsX(); bini++){
    plot.SetBinContent(bini,((double)(plot.GetBinContent(bini))/(double)(plot.GetBinWidth(bini)))  );   
  } 
}

double getMaximumDependingOnNjetsCut(TString plot, TString Njets)
{
  // create container for histo max values sortet by plot and Njet
  std::map< TString, std::map <TString,double> > maxValues_;  
  // create maximum values for inclusive stacked pt plot, 
  // differential pt plot and iclusive pt for signal ( all 50pb^-1)
  maxValues_["ptStack" ]["Njets4Btag"]= 12.;
  maxValues_["ptStack" ]["Njets3Btag"]= 12.;
  maxValues_["ptStack" ]["Njets4"]= 16.;   
  maxValues_["ptStack" ]["Njets3"]= 55.;
  maxValues_["ptStack" ]["Njets2"]= 280.;
  maxValues_["ptStack" ]["Njets1"]= 1700.;

  maxValues_["ptSignal" ]["Njets4Btag"]= 6.5;
  maxValues_["ptSignal" ]["Njets3Btag"]= 6.5;
  maxValues_["ptSignal" ]["Njets4"]= 10;   
  maxValues_["ptSignal" ]["Njets3"]= 15.;
  maxValues_["ptSignal" ]["Njets2"]= 20.;
  maxValues_["ptSignal" ]["Njets1"]= 20.;

  maxValues_["ptDiff"   ]["Njets4Btag"]=0.035;
  maxValues_["ptDiff"   ]["Njets3Btag"]=0.035;
  maxValues_["ptDiff"   ]["Njets4"]=0.035;
  maxValues_["ptDiff"   ]["Njets3"]=0.055;
  maxValues_["ptDiff"   ]["Njets2"]=0.055;
  maxValues_["ptDiff"   ]["Njets1"]=0.055;

  // get maximum value
  return maxValues_.find(plot)->second.find(Njets)->second;
}
