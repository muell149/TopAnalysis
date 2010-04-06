
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

enum styles {kSig, kWjets, kBkg, kZjets, kQCD, kSigJES11, kWjetsJES11, kBkgJES11, kZjetsJES11, kQCDJES11, kSigJES09, kWjetsJES09, kBkgJES09, kZjetsJES09, kQCDJES09, kPseudo50, kSGBG, kSGBGJES11, kSGBGJES09};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, int filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void drawcutline(double cutval, double maximum);

void analyzeMuonDiffXJES()
{
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
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecSigMcAtNlo7TeVReduced.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecWjetsMadgraph7TeVReduced.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecBkgMcAtNlo7TeVReduced.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecZjetsMadgraph7TeVReduced.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecQCDPythia7TeVReduced.root"     ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecSigMcAtNlo7TeVJES11.root"      ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecWjetsMadgraph7TeVJES11.root"   ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecBkgMcAtNlo7TeVJES11.root"      ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecZjetsMadgraph7TeVJES11.root"   ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecQCDPythia7TeVJES11.root"       ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecSigMcAtNlo7TeVJES09.root"      ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecWjetsMadgraph7TeVJES09.root"   ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecBkgMcAtNlo7TeVJES09.root"      ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecZjetsMadgraph7TeVJES09.root"   ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecQCDPythia7TeVJES09.root"       ) );
  files_.push_back(new TFile("./diffXSecFromSignal/pseudoData7TeV50pb.root"               ) );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> pt_;
  std::vector<TH2F*> corrPt_;

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    pt_    .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/pt"    ) );
    corrPt_    .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonPt_"    ) );
  }

  // ---
  //    define weights concerning luminosity for 50 pb-1 @ 7TeV
  // ---
  std::vector<double> lumiweight;
  // MC@NLO signal / W+jets Madgraph / MC@NLO background / Z+jets Madgraph / QCD Pythia

  // a) for reduced statistics:
  lumiweight.push_back(0.0084);
  lumiweight.push_back(0.1403);
  lumiweight.push_back(0.0084);
  lumiweight.push_back(0.1507);
  lumiweight.push_back(1.0286);
  // b) for shifted BG samples (first +10%, then -10%) full statistics:
  lumiweight.push_back(0.0083);
  lumiweight.push_back(0.1231);
  lumiweight.push_back(0.0083);
  lumiweight.push_back(0.1310);
  lumiweight.push_back(1.0286);
  lumiweight.push_back(0.0083);
  lumiweight.push_back(0.1231);
  lumiweight.push_back(0.0083);
  lumiweight.push_back(0.1310);
  lumiweight.push_back(1.0286);
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

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    entriesPt_.push_back ( lumiweight[idx]*(corrPt_ [idx]->GetEntries()) );
    std::cout << "total weighted # of events in pt (file " << idx << "): " << entriesPt_[idx] << std::endl;
  }
  
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
  pt_[kSGBG]->Scale(  1/ ((double)(entriesPt_[kSig]+entriesPt_[kBkg]+entriesPt_[kQCD]+entriesPt_[kWjets]+entriesPt_[kZjets]))  );
  pt_[kSGBGJES11]->Scale(  1/ ((double)(entriesPt_[kSigJES11]+entriesPt_[kBkgJES11]+entriesPt_[kQCDJES11]+entriesPt_[kWjetsJES11]+entriesPt_[kZjetsJES11]))  );
  pt_[kSGBGJES09]->Scale(  1/ ((double)(entriesPt_[kSigJES09]+entriesPt_[kBkgJES09]+entriesPt_[kQCDJES09]+entriesPt_[kWjetsJES09]+entriesPt_[kZjetsJES09]))  );


  // c) division by binwidth
  for(int i=1; i<= pt_[kSGBG]->GetNbinsX(); i++){
    pt_[kSGBG]->SetBinContent(i,((double)(pt_[kSGBG]->GetBinContent(i))/(double)(pt_[kSGBG]->GetBinWidth(i)))  );
    pt_[kSGBGJES11]->SetBinContent(i,((double)(pt_[kSGBGJES11]->GetBinContent(i))/(double)(pt_[kSGBGJES11]->GetBinWidth(i)))  );
    pt_[kSGBGJES09]->SetBinContent(i,((double)(pt_[kSGBGJES09]->GetBinContent(i))/(double)(pt_[kSGBGJES09]->GetBinWidth(i)))  );
  }

 // clone histograms for drawing without error bars
  TH1F *ptEventNumbersSigNoErrors= (TH1F*)ptEventNumbers_[kSig]->Clone();
  TH1F *ptkSGBGNoErrors= (TH1F*)(pt_[kSGBG]->Clone());
  TH1F *ptSGBG =(TH1F*)(pt_[kSGBG]->Clone());

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
  //     copy diffXpt for drawing without statistical errors
  // ---

  TH1F* ptDiffXNoErrors = (TH1F*)pt_[kSig]->Clone();

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
    THStack *composition=new THStack ("composition","");
    THStack *compositionJES09=new THStack ("compositionJES09","");
    histogramStyle(*ptEventNumbersSigNoErrors, kRed, 1, 22, 1);
    histogramStyle(*ptEventNumbers_[kWjets], kGreen, 1, 20, 1);
    histogramStyle(*ptEventNumbers_[kBkg  ], kBlue,  1, 23, 1);
    histogramStyle(*ptEventNumbers_[kZjets], 6,      1, 21, 1);
    histogramStyle(*ptEventNumbers_[kQCD  ], 14,     1, 29, 1); 
    histogramStyle(* ptEventNumbers_[kSigJES11  ], kRed,   1, 22, 1);
    histogramStyle(* ptEventNumbers_[kWjetsJES11], kGreen, 1, 20, 1);
    histogramStyle(* ptEventNumbers_[kBkgJES11  ], kBlue,  1, 23, 1);
    histogramStyle(* ptEventNumbers_[kZjetsJES11], 6,      1, 21, 1);
    histogramStyle(* ptEventNumbers_[kQCDJES11  ], 14,     1, 29, 1); 
    histogramStyle(* ptEventNumbers_[kSigJES09  ], kRed,   1, 22, 1);
    histogramStyle(* ptEventNumbers_[kWjetsJES09], kGreen, 1, 20, 1);
    histogramStyle(* ptEventNumbers_[kBkgJES09  ], kBlue,  1, 23, 1);
    histogramStyle(* ptEventNumbers_[kZjetsJES09], 6,      1, 21, 1);
    histogramStyle(* ptEventNumbers_[kQCDJES09  ], 14,     1, 29, 1);
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
    histogramStyle(* ptEventNumbersRel_[kSig  ], kRed,   1, 22, 0);
    for(int idx=kWjets; idx<kQCDJES09; idx++){
      histogramStyle(* ptEventNumbersRel_[idx], ptEventNumbers_[idx]->GetLineColor(), 1, ptEventNumbers_[idx]->GetMarkerStyle(), 0);  
    }

  // ---
  //    create legends 
  // ---

  // create a legend for Signal, JES +/- 10%
    TLegend *leg3 = new TLegend(0.27, 0.70, 1.05, 0.93);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  leg3->SetHeader("semi-#mu Top-Antitop (MC@NLO 7 TeV) & 50 pb^{-1}");
  leg3->AddEntry( pt_[kSig]     , "unshifted"  , "PL");
  leg3->AddEntry( pt_[kSigJES11], "JES +10 %"  , "PL");
  leg3->AddEntry( pt_[kSigJES09], "JES -10 %"  , "PL");

  // create a legend for stack plot with underground
  TLegend *leg4 = new TLegend(0.5, 0.64, 0.97, 0.89);
  leg4->SetFillStyle(0);
  leg4->SetBorderSize(0);
  leg4->SetHeader("50 pb^{-1} @ 7TeV MC samples");
  leg4->AddEntry( ptEventNumbersSigNoErrors , "semi #mu ttbar Mc@Nlo", "F" );
  leg4->AddEntry( ptEventNumbers_[kBkg]     , "other ttbar Mc@Nlo"   , "F" );
  leg4->AddEntry( ptEventNumbers_[kQCD]     , "QCD Pythia"           , "F" );
  leg4->AddEntry( ptEventNumbers_[kWjets]   , "Wjets Madgraph"       , "F" );
  leg4->AddEntry( ptEventNumbers_[kZjets]   , "Zjets Madgraph"       , "F" );
  leg4->AddEntry( ptEventNumbers_[kPseudo50], "pseudo data"          , "P");

  // create a legend for relative plot with underground
  TLegend *leg0 = new TLegend(0.48, 0.69, 0.95, 0.94);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("MC samples @ 7TeV");
  leg0->AddEntry( ptEventNumbersRel_[kSig]       , "semi #mu ttbar Mc@Nlo", "PL");
  leg0->AddEntry( ptEventNumbersRel_[kBkg]       , "other ttbar Mc@Nlo"   , "PL");
  leg0->AddEntry( ptEventNumbersRel_[kQCD]       , "QCD Pythia"           , "PL");
  leg0->AddEntry( ptEventNumbersRel_[kWjets]     , "Wjets Madgraph"       , "PL");
  leg0->AddEntry( ptEventNumbersRel_[kZjets]     , "Zjets Madgraph"       , "PL");

  // create a legend for Signal, Signal + Background, pseudo data
  TLegend *leg5 = new TLegend(0.21, 0.67, 0.92, 0.92);
  leg5->SetFillStyle(0);
  leg5->SetBorderSize(0);
  leg5->SetHeader("50 pb^{-1} @ 7 TeV");
  leg5->AddEntry( ptDiffXNoErrors, "signal only"        , "PL");
  leg5->AddEntry( ptSGBG         , "signal + background", "PL");
  leg5->AddEntry( pt_[kPseudo50] , "pseudo data"        , "P");

  // create a legend for diffX pt(mu) (all left events after selektion, JES +/- 10%)
  TLegend *leg6 = new TLegend(0.25, 0.64, 1.05, 0.92);
  leg6->SetFillStyle(0);
  leg6->SetBorderSize(0);
  leg6->SetHeader("events after selection @ 7 TeV & 50 pb^{-1}");
  leg6->AddEntry( pt_[kSGBG]     , "unshifted"  , "PL");
  leg6->AddEntry( pt_[kSGBGJES11], "JES +10 %"  , "PL");
  leg6->AddEntry( pt_[kSGBGJES09], "JES -10 %"  , "PL");

  // create a legend for all left events after selektion, JES +/- 10%
  TLegend *leg7 = new TLegend(0.20, 0.69, 0.93, 0.94);
  leg7->SetFillStyle(0);
  leg7->SetBorderSize(0);
  leg7->SetHeader("events after selection @ 7 TeV & 50 pb^{-1}");
  leg7->AddEntry( ptEventNumbers_[kSGBG]     , "unshifted"  , "PL");
  leg7->AddEntry( ptEventNumbers_[kSGBGJES11], "JES +10 %"  , "PL");
  leg7->AddEntry( ptEventNumbers_[kSGBGJES09], "JES -10 %"  , "PL");

  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<=10; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }
  
  // ---
  //    do the printing for pt_ ( normalized,DIFFerential xSec ttbar(muon) only with JES +/-10% )
  // ---
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetTitle("ptDiffXSecSignalJESEffectMcatnlo7TeV");
  axesStyle(*pt_ [kSig], "p_{t} ( #mu ) [GeV]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{t}(#mu)}", 0., 0.035, 0.04, 2.0);
  histogramStyle(*pt_  [kSig]     , kBlack, 1);
  histogramStyle(*pt_  [kSigJES11], kBlue,  2);
  histogramStyle(*pt_  [kSigJES09], kRed,   2);
  pt_ [kSig]->SetBinError( 1, 0. );
  for(int i =2; i<= totalBinNumber+1; i++){
    pt_ [kSig]->SetBinError(  i, ptDiffXError_[i-2]  );
  }
  pt_ [kSig]     ->Draw("");
  pt_ [kSigJES11]->Draw("same");
  pt_ [kSigJES09]->Draw("same");
  leg3           ->Draw("same");

  // ---
  //    do the printing for pt_ ( normalized,DIFFerential xSec signal + background with JES +/-10% )
  // ---
  MyCanvas[1]->cd(0);
  MyCanvas[1]->SetTitle("ptDiffXSecAllJESEffect7TeV");
  axesStyle(*pt_ [kSGBG], "p_{t} ( #mu ) [GeV]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{t}(#mu)}", 0., 0.035, 0.04, 2.0);
  histogramStyle(*pt_ [kSGBG]     , kBlack, 1);
  histogramStyle(*pt_ [kSGBGJES11], kBlue,  2);
  histogramStyle(*pt_ [kSGBGJES09], kRed ,  2);
  for(int i =2; i<= totalBinNumber+1; i++){
    pt_[kSGBG]->SetBinError( i, ptDiffXAllSamplesError_[i-2] );
  }
  pt_ [kSGBG]     ->Draw();
  ptkSGBGNoErrors ->Draw("same");
  pt_ [kSGBGJES11]->Draw("same");
  pt_ [kSGBGJES09]->Draw("same");
  leg6            ->Draw("same");


  // ---
  //    do the printing for pt_ ( normalized,DIFFerential xSec signal, signal + background and Pseudo Data )
  // ---
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetTitle("ptDiffXSecForSGBGAndPseudoData7TeV");
  histogramStyle(*pt_ [kPseudo50], kBlack, 1, 22);
  histogramStyle(*ptSGBG, kBlue, 1, 20);
  histogramStyle(*ptDiffXNoErrors, kRed, 1, 20);
  axesStyle(*ptDiffXNoErrors, "p_{t} ( #mu ) [GeV]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{t}(#mu)}", 0., 0.035, 0.04, 2.0);
  for(int i =2; i<= totalBinNumber+1; i++){
    pt_[kPseudo50]->SetBinError(  i, ptDiffXPseudoError_[i-2] );
  }
  ptDiffXNoErrors->Draw();
  ptSGBG         ->Draw("same"); 
  pt_ [kPseudo50]->Draw("psame");
  leg5           ->Draw("same");

  // ---
  //    do the printing for ptEventNumbers_ ( eventNUMBERs/binwidth in pt(muon) for ttbar(muon) only with JES +/-10% )
  // ---
  MyCanvas[3]->cd(0);
  MyCanvas[3]->SetTitle("ptInclusiveSignalJESEffectMcatnlo7TeV");
  axesStyle(*ptEventNumbers_ [kSig], "p_{t} ( #mu ) [GeV]", "events", 0., 130.);
  TH1F *ptEvtsJES11= (TH1F*)(ptEventNumbers_ [kSigJES11]->Clone());
  TH1F *ptEvtsJES09= (TH1F*)(ptEventNumbers_ [kSigJES09]->Clone());
  histogramStyle(*ptEventNumbers_ [kSig], kBlack, 1);
  histogramStyle(*ptEvtsJES11,            kBlue , 2, 20, 0);
  histogramStyle(*ptEvtsJES09,            kRed  , 2, 20, 0);
  ptEventNumbers_ [kSig]->SetBinError( 1, 0. );
  for(int i =2; i<= totalBinNumber+1; i++){
    ptEventNumbers_ [kSig]->SetBinError(  i, sqrt( (double)(ptEventNumbers_[kSig]->GetBinContent(i)) )  );
  }
  ptEventNumbers_ [kSig]->Draw("");
  ptEvtsJES11->Draw("same");
  ptEvtsJES09->Draw("same");
  leg3       ->Draw("same");

  // ---
  //    do the printing for ptEventNumbers_ ( eventNUMBERs/binwidth in pt(muon) for signal + background with JES +/-10% )
  // ---
  MyCanvas[4]->cd(0);
  MyCanvas[4]->SetTitle("ptInclusiveAllJESEffect7TeV");
  axesStyle(*ptEventNumbers_ [kSGBG], "p_{t} ( #mu ) [GeV]", "events", 0., 270.);
  histogramStyle(*ptEventNumbers_ [kSGBG]     , kBlack, 1);
  histogramStyle(*ptEventNumbers_ [kSGBGJES11], kBlue,  2);
  histogramStyle(*ptEventNumbers_ [kSGBGJES09], kRed,   2);
  ptEventNumbers_ [kSGBG]->Draw("e0");
  ptEventNumbers_ [kSGBG]->Draw("same");
  ptEventNumbers_ [kSGBGJES11]->Draw("same");
  ptEventNumbers_ [kSGBGJES09]->Draw("same");
  leg6                        ->Draw("same");

  // ---
  //    do the printing for EventNumbers ( eventNUMBERs/binwidth in pt(muon) for signal + background and pseudo data as STACK plot )
  // ---

  MyCanvas[5]->cd(0);
  MyCanvas[5]->SetTitle("eventCompositionNoJES");
  axesStyle(*ptEventNumbersSigNoErrors, "p_{t} ( #mu ) [GeV]", "events", -123., 170. );
  histogramStyle(*ptEventNumbers_[kPseudo50], kBlack, 1, 22);
  ptEventNumbersSigNoErrors->Draw("AXIS");
  composition              ->Draw("same");
  for(int i =2; i<= totalBinNumber+1; i++){
    ptEventNumbers_[kPseudo50]->SetBinError(  i, (int)sqrt((double)ptEventNumbers_[kPseudo50]->GetBinContent(i))  );
  }
  ptEventNumbers_[kPseudo50]->Draw("psame");
  leg4                      ->Draw("same");

  // ---
  //    do the printing for EventNumbers ( with JES+10%: eventNUMBERs/binwidth in pt(muon) for signal + background as STACK plot )
  // ---
  MyCanvas[6]->cd(0);
  MyCanvas[6]->SetTitle("eventCompositionJES11");
  ptEventNumbersSigNoErrors->Draw("AXIS");
  compositionJES11         ->Draw("same");
  leg4                     ->Draw("same");

  // ---
  //    do the printing for EventNumbers ( with JES-10%: eventNUMBERs/binwidth in pt(muon) for signal + background as STACK plot )
  // ---
  MyCanvas[7]->cd(0);
  MyCanvas[7]->SetTitle("eventCompositionJES09");
  ptEventNumbersSigNoErrors->Draw("AXIS");
  compositionJES09         ->Draw("same");
  leg4                     ->Draw("same");


  // ---
  //    do the printing for EventNumbers ( eventNUMBERs/binwidth in pt(muon) for signal + background as REALTIVE plot )
  // ---
  MyCanvas[8]->cd(0);
  MyCanvas[8]->SetTitle("eventCompositionRelative");
  MyCanvas[8]->SetGrid(1,1);
  axesStyle(*ptEventNumbersRel_[kSig], "p_{t} ( #mu ) [GeV]", "fraction (events)", -123., 1.0);
  ptEventNumbersRel_[kSig]->Draw("");
  for(int idx=kSig; idx<=kQCD; idx++){
    ptEventNumbersRel_[idx]->Draw("same");
    ptEventNumbersRel_[idx]->Draw("Psame");
    }
  leg0          ->Draw("same");

  // ---
  //    do the printing for EventNumbers (  with JES+10%: eventNUMBERs/binwidth in pt(muon) for signal + background as REALTIVE plot )
  // ---
  MyCanvas[9]->cd(0);
  MyCanvas[9]->SetTitle("eventCompositionRelativeJES11");
  MyCanvas[9]->SetGrid(1,1);
  axesStyle(*ptEventNumbersRel_[kSigJES11], "p_{t} ( #mu ) [GeV]", "fraction (events)", -123., 1.0);
  ptEventNumbersRel_[kSigJES11]->Draw("");
  for(int idx=kSigJES11; idx<=kQCDJES11; idx++){
    ptEventNumbersRel_[idx]->Draw("same");
    ptEventNumbersRel_[idx]->Draw("Psame");
    }
  leg0          ->Draw("same");

  // ---
  //    do the printing for EventNumbers (  with JES-10%: eventNUMBERs/binwidth in pt(muon) for signal + background as REALTIVE plot )
  // ---
  MyCanvas[10]->cd(0);
  MyCanvas[10]->SetTitle("eventCompositionRelativeJES09");
  MyCanvas[10]->SetGrid(1,1);
  axesStyle(*ptEventNumbersRel_[kSigJES09], "p_{t} ( #mu ) [GeV]", "fraction (events)", -123., 1.0);
  ptEventNumbersRel_[kSigJES09]->Draw("");
  for(int idx=kSigJES09; idx<=kQCDJES09; idx++){
    ptEventNumbersRel_[idx]->Draw("same");
    ptEventNumbersRel_[idx]->Draw("Psame");
    }
  leg0          ->Draw("same");

  // ---
  // saving
  // ---
  
//   // ps
//   MyCanvas[0]->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps("  );
//   for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
//     MyCanvas[idx]->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps"  );   
//   }
//   MyCanvas[MyCanvas.size()-1]->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps)"  );
  
//   // png
//   for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
//     MyCanvas[idx]->Print("./diffXSecFromSignal/plots/"+(TString)(MyCanvas[idx]->GetTitle())+".png"  );      
//   }
}

void canvasStyle(TCanvas& canv) 
{
  canv.SetFillStyle   ( 4000 );
  canv.SetLeftMargin  ( 0.20 );
  canv.SetRightMargin ( 0.05 );
  canv.SetBottomMargin( 0.15 );
  canv.SetTopMargin   ( 0.05 );
}

void histogramStyle(TH1& hist, int color, int lineStyle, int markerStyle, int filled) 
{
  hist.SetLineWidth(3);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color);
  hist.SetMarkerColor(color);  
  hist.SetMarkerStyle(markerStyle);
  hist.SetMarkerSize(1.5);
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
