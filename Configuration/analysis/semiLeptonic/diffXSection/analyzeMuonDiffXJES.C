
// ---------description-----------------------------------
// -------------------------------------------------------
// this Makro shows the effects of the JES ( +/- 10 % ) 
// and the contribution of signal / background in each bin
// ! careful about the order when reading in files, some
//   calculations are sensitive to it !
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
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);
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
  std::vector<TH1F*> eta_, phi_, pt_, etaGen_, phiGen_, ptGen_, etaMuPlus_, phiMuPlus_, ptMuPlus_ , etaMuMinus_, phiMuMinus_, ptMuMinus_;
  std::vector<TH2F*> corrPt_, corrPhi_, corrEta_;

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    eta_   .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/eta"   ) );
    pt_    .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/pt"    ) );
    phi_   .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/phi"   ) );
    etaGen_.push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/etaGen") );
    ptGen_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/ptGen" ) );
    phiGen_.push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/phiGen") );
    etaMuMinus_.push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/etaMuMinus") );
    ptMuMinus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/ptMuMinus" ) );
    phiMuMinus_.push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/phiMuMinus") );
    etaMuPlus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/etaMuPlus" ) );
    ptMuPlus_  .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/ptMuPlus"  ) );
    phiMuPlus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/phiMuPlus" ) );

    corrEta_   .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonEta_"   ) );
    corrPt_    .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonPt_"    ) );
    corrPhi_   .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonPhi_"   ) );
  }


  // ---
  // create Vector to store output statements
  // ---
  std::vector<TString> output_;
  TString textHelper = "";
  output_.push_back("MC@NLO 7 TeV");

  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;

  // when using reduced statistics

  // for current 7TeV Mc@Nlo sample (signal)
  lumiweight.push_back(0.0084);

  // for current 7TeV Madgraph W+jets sample
  lumiweight.push_back(0.1403);

  // for current 7TeV Mc@Nlo sample (background)
  lumiweight.push_back(0.0084);

  // for current 7TeV Madgraph Z+jets sample
  lumiweight.push_back(0.1507);

  // for current 7TeV Pythia QCD sample
  lumiweight.push_back(1.0286);

  // for shifted BG samples (first +10%, then -10%) full statistics

  // for current 7TeV Mc@Nlo sample (signal)
  lumiweight.push_back(0.0083);

  // for current 7TeV Madgraph W+jets sample
  lumiweight.push_back(0.1231);

  // for current 7TeV Mc@Nlo sample (background)
  lumiweight.push_back(0.0083);

  // for current 7TeV Madgraph Z+jets sample
  lumiweight.push_back(0.1310);

  // for current 7TeV Pythia QCD sample
  lumiweight.push_back(1.0286);

  // for current 7TeV Mc@Nlo sample (signal)
  lumiweight.push_back(0.0083);

  // for current 7TeV Madgraph W+jets sample
  lumiweight.push_back(0.1231);

  // for current 7TeV Mc@Nlo sample (background)
  lumiweight.push_back(0.0083);

  // for current 7TeV Madgraph Z+jets sample
  lumiweight.push_back(0.1310);

  // for current 7TeV Pythia QCD sample
  lumiweight.push_back(1.0286);

  // for pseudodata
  lumiweight.push_back(1.0);

  // ---
  // do lumiweighting
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    eta_[idx]->Scale(lumiweight[idx]);
    phi_[idx]->Scale(lumiweight[idx]);
    pt_ [idx]->Scale(lumiweight[idx]);
    etaGen_[idx]->Scale(lumiweight[idx]);
    phiGen_[idx]->Scale(lumiweight[idx]);
    ptGen_ [idx]->Scale(lumiweight[idx]);
    etaMuPlus_[idx]->Scale(lumiweight[idx]);
    phiMuPlus_[idx]->Scale(lumiweight[idx]);
    ptMuPlus_ [idx]->Scale(lumiweight[idx]);
    etaMuMinus_[idx]->Scale(lumiweight[idx]);
    phiMuMinus_[idx]->Scale(lumiweight[idx]);
    ptMuMinus_ [idx]->Scale(lumiweight[idx]);
  }

  // ---  
  //    clone plots with weighted event numbers
  // ---
  
  std::vector<TH1F*> etaEventNumbers_, phiEventNumbers_, ptEventNumbers_, etaGenEventNumbers_, phiGenEventNumbers_, ptGenEventNumbers_, etaMuPlusEventNumbers_, phiMuPlusEventNumbers_, ptMuPlusEventNumbers_ , etaMuMinusEventNumbers_, phiMuMinusEventNumbers_, ptMuMinusEventNumbers_;
  
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    etaEventNumbers_.push_back( (TH1F*)(eta_[idx]->Clone()) );
    phiEventNumbers_.push_back( (TH1F*)(phi_[idx]->Clone()) );
    ptEventNumbers_.push_back ( (TH1F*)(pt_ [idx]->Clone()) );
    etaGenEventNumbers_.push_back( (TH1F*)(etaGen_[idx]->Clone()) );
    phiGenEventNumbers_.push_back( (TH1F*)(phiGen_[idx]->Clone()) );
    ptGenEventNumbers_.push_back ( (TH1F*)(ptGen_ [idx]->Clone()) );
    etaMuPlusEventNumbers_.push_back( (TH1F*)(etaMuPlus_[idx]->Clone()) );
    phiMuPlusEventNumbers_.push_back(  (TH1F*)(phiMuPlus_[idx]->Clone()) );
    ptMuPlusEventNumbers_.push_back (  (TH1F*)(ptMuPlus_ [idx]->Clone()) );
    etaMuMinusEventNumbers_.push_back(  (TH1F*)(etaMuMinus_[idx]->Clone()) );
    phiMuMinusEventNumbers_.push_back(  (TH1F*)(phiMuMinus_[idx]->Clone()) );
    ptMuMinusEventNumbers_.push_back (  (TH1F*)(ptMuMinus_ [idx]->Clone()) );
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

  std::vector<double> eventNumbersPt_, eventNumbersEta_, eventNumbersPhi_;

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    eventNumbersPt_.push_back ( lumiweight[idx]*(corrPt_ [idx]->GetEntries()) );
    eventNumbersEta_.push_back( lumiweight[idx]*(corrEta_[idx]->GetEntries()) );
    eventNumbersPhi_.push_back( lumiweight[idx]*(corrPhi_[idx]->GetEntries()) );

    std::cout << "total weighted # of sig events in pt (file " << idx << "): " << eventNumbersPt_[idx] << std::endl;
    textHelper = "total weighted # of sig events in pt (file ";
    textHelper += idx;
    textHelper += "): ";
    textHelper += eventNumbersPt_[idx] ;
    output_ .push_back(textHelper);
  }
  
  // ---
  //    do scaling with respect to inclusive cross section (taken from same histogram)
  // ---
  
  for(unsigned int idx=0; idx<files_.size(); ++idx) {

    pt_ [idx]->Scale(1/eventNumbersPt_[idx]);
    ptGen_ [idx]->Scale(1/eventNumbersPt_[idx]);
    ptMuPlus_ [idx]->Scale(1/eventNumbersPt_[idx]);
    ptMuMinus_ [idx]->Scale(1/eventNumbersPt_[idx]);
    
    eta_ [idx]->Scale(1/eventNumbersEta_[idx]);
    etaGen_ [idx]->Scale(1/eventNumbersEta_[idx]);
    etaMuPlus_ [idx]->Scale(1/eventNumbersEta_[idx]);
    etaMuMinus_ [idx]->Scale(1/eventNumbersEta_[idx]);
      
    phi_ [idx]->Scale(1/eventNumbersPhi_[idx]);
    phiGen_ [idx]->Scale(1/eventNumbersPhi_[idx]);
    phiMuPlus_ [idx]->Scale(1/eventNumbersPhi_[idx]);
    phiMuMinus_ [idx]->Scale(1/eventNumbersPhi_[idx]);
  }

  // ---
  //    division by binwidth
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {

    for(int i=1; i<= pt_[idx]->GetNbinsX(); i++){
      pt_[idx]->SetBinContent(i,((double)(pt_[idx]->GetBinContent(i))/(double)(pt_[idx]->GetBinWidth(i)))  );
      ptGen_[idx]->SetBinContent(i,((double)(ptGen_[idx]->GetBinContent(i))/(double)(ptGen_[idx]->GetBinWidth(i)))  );
      ptMuPlus_[idx]->SetBinContent(i,((double)(ptMuPlus_[idx]->GetBinContent(i))/(double)(ptMuPlus_[idx]->GetBinWidth(i)))  );
      ptMuMinus_[idx]->SetBinContent(i,((double)(ptMuMinus_[idx]->GetBinContent(i))/(double)(ptMuMinus_[idx]->GetBinWidth(i)))  );
    }
    
    for(int i=1; i<= phi_[idx]->GetNbinsX(); i++){
      phi_[idx]->SetBinContent(i,((double)(phi_[idx]->GetBinContent(i))/(double)(phi_[idx]->GetBinWidth(i)))  );
      phiGen_[idx]->SetBinContent(i,((double)(phiGen_[idx]->GetBinContent(i))/(double)(phiGen_[idx]->GetBinWidth(i)))  );
      phiMuPlus_[idx]->SetBinContent(i,((double)(phiMuPlus_[idx]->GetBinContent(i))/(double)(phiMuPlus_[idx]->GetBinWidth(i)))  );
      phiMuMinus_[idx]->SetBinContent(i,((double)(phiMuMinus_[idx]->GetBinContent(i))/(double)(phiMuMinus_[idx]->GetBinWidth(i)))  );
    }
    
    for(int i=1; i<= eta_[idx]->GetNbinsX(); i++){
      eta_[idx]->SetBinContent(i,((double)(eta_[idx]->GetBinContent(i))/(double)(eta_[idx]->GetBinWidth(i)))  );
      etaGen_[idx]->SetBinContent(i,((double)(etaGen_[idx]->GetBinContent(i))/(double)(etaGen_[idx]->GetBinWidth(i)))  );
      etaMuPlus_[idx]->SetBinContent(i,((double)(etaMuPlus_[idx]->GetBinContent(i))/(double)(etaMuPlus_[idx]->GetBinWidth(i)))  );
      etaMuMinus_[idx]->SetBinContent(i,((double)(etaMuMinus_[idx]->GetBinContent(i))/(double)(etaMuMinus_[idx]->GetBinWidth(i)))  );
    }
  }

  
  // create 1D pt histo for all channels without binning as projection of correlation plot
  TH1F *ptAllUnbinned= (TH1F*)(corrPt_[kSig]->ProjectionY()->Clone());
  ptAllUnbinned->Scale(lumiweight[kSig]) ;

   for(int idx = kWjets; idx <= kQCD; idx++){
     TH1F *help= (TH1F*)(corrPt_[idx]->ProjectionY());
     help->Scale(lumiweight[idx]);
     ptAllUnbinned->Add(help);
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
  pt_[kSGBG]->Scale(  1/ ((double)(eventNumbersPt_[kSig]+eventNumbersPt_[kBkg]+eventNumbersPt_[kQCD]+eventNumbersPt_[kWjets]+eventNumbersPt_[kZjets]))  );
  pt_[kSGBGJES11]->Scale(  1/ ((double)(eventNumbersPt_[kSigJES11]+eventNumbersPt_[kBkgJES11]+eventNumbersPt_[kQCDJES11]+eventNumbersPt_[kWjetsJES11]+eventNumbersPt_[kZjetsJES11]))  );
  pt_[kSGBGJES09]->Scale(  1/ ((double)(eventNumbersPt_[kSigJES09]+eventNumbersPt_[kBkgJES09]+eventNumbersPt_[kQCDJES09]+eventNumbersPt_[kWjetsJES09]+eventNumbersPt_[kZjetsJES09]))  );


  // c) division by binwidth
  for(int i=1; i<= pt_[kSGBG]->GetNbinsX(); i++){
    pt_[kSGBG]->SetBinContent(i,((double)(pt_[kSGBG]->GetBinContent(i))/(double)(pt_[kSGBG]->GetBinWidth(i)))  );
    pt_[kSGBGJES11]->SetBinContent(i,((double)(pt_[kSGBGJES11]->GetBinContent(i))/(double)(pt_[kSGBGJES11]->GetBinWidth(i)))  );
    pt_[kSGBGJES09]->SetBinContent(i,((double)(pt_[kSGBGJES09]->GetBinContent(i))/(double)(pt_[kSGBGJES09]->GetBinWidth(i)))  );
  }

 // clone histogram with signal event numbers to have it without error bars
  TH1F *ptEventNumbersSigNoErrors= (TH1F*)ptEventNumbers_[kSig]->Clone();

  // ---
  //    configure histograms
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    histogramStyle(*eta_ [idx], idx);
    histogramStyle(*phi_ [idx], idx);
    histogramStyle(*pt_  [idx], idx);
    histogramStyle(*etaGen_ [idx], idx);
    histogramStyle(*phiGen_ [idx], idx);
    histogramStyle(*ptGen_  [idx], idx);
    histogramStyle(*etaMuPlus_ [idx], idx);
    histogramStyle(*phiMuPlus_ [idx], idx);
    histogramStyle(*ptMuPlus_  [idx], idx);
    histogramStyle(*etaMuMinus_ [idx], idx);
    histogramStyle(*phiMuMinus_ [idx], idx);
    histogramStyle(*ptMuMinus_  [idx], idx);
    histogramStyle(*etaEventNumbers_ [idx], idx);
    histogramStyle(*phiEventNumbers_ [idx], idx);
    histogramStyle(*ptEventNumbers_  [idx], idx);
    histogramStyle(*etaGenEventNumbers_ [idx], idx);
    histogramStyle(*phiGenEventNumbers_ [idx], idx);
    histogramStyle(*ptGenEventNumbers_  [idx], idx);
    histogramStyle(*etaMuPlusEventNumbers_ [idx], idx);
    histogramStyle(*phiMuPlusEventNumbers_ [idx], idx);
    histogramStyle(*ptMuPlusEventNumbers_  [idx], idx);
    histogramStyle(*etaMuMinusEventNumbers_ [idx], idx);
    histogramStyle(*phiMuMinusEventNumbers_ [idx], idx);
    histogramStyle(*ptMuMinusEventNumbers_ [idx], idx);

  }
  histogramStyle(*ptEventNumbersSigNoErrors, kSig);
  histogramStyle(*pt_ [kSGBG], kSGBG);
  histogramStyle(*pt_ [kSGBGJES11], kSGBGJES11);
  histogramStyle(*pt_ [kSGBGJES11], kSGBGJES11);
  histogramStyle(*ptAllUnbinned, kSGBG);

  // ---
  //    get and print some numbers
  // ---

  // a) get total number of filled bins above cut value of 20 GeV from pt histo
  int totalBinNumber = (pt_[kSig]->GetNbinsX())-1;
  std::cout << "total bin number between 20 and 200 GeV: " << totalBinNumber << std::endl;
    textHelper = "total bin number between 20 and 200 GeV: ";
    textHelper += totalBinNumber ;
    output_ .push_back(textHelper);

  // b) get binning values from pt histo
  std::vector<int> binValue_;
  for(int i=1; i<= totalBinNumber+2; i++){
    // +2 for underflow bin and upper Edge of last bin
    binValue_.push_back(pt_[kSig]->GetBinLowEdge(i));
    std::cout << "lower edge bin " << i << " :" << binValue_[i-1] << std::endl;
    textHelper = "lower edge bin ";
    textHelper += i;
    textHelper += " :";
    textHelper += binValue_[i-1];
    output_ .push_back(textHelper);
  }
  // add overflow bin for completeness
  binValue_.push_back(401);


  // c) print out event composition (lumi weighted) in each pt - bin
  std::cout << "---(weighted) event composition per pt-bin---"<< std::endl;
  std::cout << "( ttbarsig / ttbar bkg / W+jets / Z+jets / QCD / Pseudodata no shift)::"<< std::endl;
  std::cout << "a) ohne JES:"<< std::endl;
  textHelper = "(weighted) event composition per pt-bin";
  textHelper += "( ttbarsig / ttbar bkg / W+jets / Z+jets / QCD / Pseudodata)::";
  textHelper += "a) ohne JES:";
  output_ .push_back(textHelper);

  for(int i=2; i<= pt_[kSig]->GetNbinsX()+1; i++){
    std::cout << "pt-bin "<< i << ": ( " <<  ptEventNumbers_[kSig]->GetBinContent(i) << " / " <<  ptEventNumbers_[kBkg]->GetBinContent(i) <<" / " << ptEventNumbers_[kWjets]->GetBinContent(i) <<" / " <<   ptEventNumbers_[kZjets]->GetBinContent(i)  <<" / " <<   ptEventNumbers_[kQCD]->GetBinContent(i) << " / " <<   ptEventNumbers_[kPseudo50]->GetBinContent(i) <<" ) " << std::endl;

    textHelper = "pt-bin ";
    textHelper += i;
    textHelper += ": ( ";
    textHelper += ptEventNumbers_[kSig]->GetBinContent(i);
    textHelper += " / " ;
    textHelper += ptEventNumbers_[kBkg]->GetBinContent(i);
    textHelper += " / " ;
    textHelper += ptEventNumbers_[kWjets]->GetBinContent(i);
    textHelper += " / " ;
    textHelper +=  ptEventNumbers_[kZjets]->GetBinContent(i);
    textHelper += " / " ;
    textHelper +=  ptEventNumbers_[kQCD]->GetBinContent(i);
    output_ .push_back(textHelper);
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
    errorHelperA= ( (double)(pt_[kSig]->GetBinWidth(i)) * eventNumbersPt_[kSig] ); 

    // final formula for total cross section taken from same histogram
    ptDiffXError_.push_back(   sqrt(  ((double)(ptEventNumbers_ [kSig]->GetBinContent(i)) / errorHelperA / errorHelperA) * ( 1.0 - 2.0 * (double)(pt_[kSig]->GetBinWidth(i)) / errorHelperA + ( (double)(ptEventNumbers_ [kSig]->GetBinContent(i)) * (double)(pt_[kSig]->GetBinWidth(i)) * (double)(pt_[kSig]->GetBinWidth(i)) * (eventNumbersPt_[kSig])  / errorHelperA / errorHelperA) )  )   );
  }
  //  b) for pseudo data

  // i: calculation for each bin (starting with filled bin-> i=2, take care totalBinNumber starts counting at 2nd bin -> +1)
  for(int i =2; i<=totalBinNumber+1; i++){

    // calculate shortcut expression needed in final formula
    double errorHelperA=0;  
    errorHelperA= ( (double)(pt_[kPseudo50]->GetBinWidth(i)) * eventNumbersPt_[kPseudo50] ); 

    // final formula for total cross section taken from same histogram
    ptDiffXPseudoError_.push_back(   sqrt(  ((double)(ptEventNumbers_ [kPseudo50]->GetBinContent(i)) / errorHelperA / errorHelperA) * ( 1.0 - 2.0 * (double)(pt_[kPseudo50]->GetBinWidth(i)) / errorHelperA + ( (double)(ptEventNumbers_ [kPseudo50]->GetBinContent(i)) * (double)(pt_[kPseudo50]->GetBinWidth(i)) * (double)(pt_[kPseudo50]->GetBinWidth(i)) * (eventNumbersPt_[kPseudo50])  / errorHelperA / errorHelperA) )  )   );
  }

  //  c) for all events surviving the selection

  // i: calculation for each bin (starting with filled bin-> i=2, take care totalBinNumber starts counting at 2nd bin -> +1)
  for(int i =2; i<=totalBinNumber+1; i++){

    // calculate shortcut expression needed in final formula
    double errorHelperA=0;
    double totalEventNumbers = eventNumbersPt_[kSig]+eventNumbersPt_[kBkg]+eventNumbersPt_[kZjets]+eventNumbersPt_[kWjets]+eventNumbersPt_[kQCD];
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
    textHelper = "(weighted) # events pt-bin ";
    textHelper += i ;
    textHelper += ": ";
    textHelper += pt_[kSig]->GetBinContent(i);
    textHelper += " +/- " ;
    textHelper += ptDiffXError_[i-2];
    output_ .push_back(textHelper);
  }

  // ---
  //     copy diffXpt for drawing without statistical errors
  // ---

  TH1F* ptDiffXNoErrors = (TH1F*)pt_[kSig]->Clone();

  // ---
  //     print out event composition after cuts in rel. numbers (with respect to total bin entries)
  // ---

  THStack *compositionRel=new THStack ("compositionRel","");
  THStack *compositionRelJES11=new THStack ("compositionRelJES11","");
  THStack *compositionRelJES09=new THStack ("compositionRelJES09","");
  std::vector<TH1F*> ptEventNumbersRel_;

  // create Marker Style vector
  std::vector<int> markerStyle_;
  markerStyle_.push_back(22);
  markerStyle_.push_back(20);
  markerStyle_.push_back(23);  
  markerStyle_.push_back(21);
  markerStyle_.push_back(29);

  // create relative plots

  for(int idx=kSig; idx<=kQCD; idx++){
    ptEventNumbersRel_ .push_back( (TH1F*)ptEventNumbers_[idx]->Clone() );

    // calculate value for each bin i
    for(int i=2; i<=pt_[kSig]->GetNbinsX(); i++){
      ptEventNumbersRel_[idx]->SetBinContent(  i, (ptEventNumbersRel_[idx]->GetBinContent(i) ) / ( ptEventNumbersSigNoErrors->GetBinContent(i)+ptEventNumbers_[kWjets]->GetBinContent(i)+ptEventNumbers_[kBkg]->GetBinContent(i)+ptEventNumbers_[kZjets]->GetBinContent(i)+ptEventNumbers_[kQCD]->GetBinContent(i) )  );
    }
    
    histogramStyle(* ptEventNumbersRel_[idx], idx);
    ptEventNumbersRel_[idx]->SetMarkerStyle(markerStyle_[idx]);
    ptEventNumbersRel_[idx]->SetMarkerSize(1.5);

      compositionRel->Add(ptEventNumbersRel_[idx],"HIST"); 
  }

  for(int idx=kSigJES11; idx<=kQCDJES11; idx++){
    ptEventNumbersRel_ .push_back( (TH1F*)ptEventNumbers_[idx]->Clone() );

    // calculate value for each bin i
    for(int i=2; i<=pt_[kSigJES11]->GetNbinsX(); i++){
      ptEventNumbersRel_[idx]->SetBinContent(  i, (ptEventNumbersRel_[idx]->GetBinContent(i) ) / ( ptEventNumbers_[kSigJES11]->GetBinContent(i)+ptEventNumbers_[kWjetsJES11]->GetBinContent(i)+ptEventNumbers_[kBkgJES11]->GetBinContent(i)+ptEventNumbers_[kZjetsJES11]->GetBinContent(i)+ptEventNumbers_[kQCDJES11]->GetBinContent(i) )  );
    }
    
    histogramStyle(* ptEventNumbersRel_[idx], idx);
    ptEventNumbersRel_[idx]->SetMarkerStyle(markerStyle_[idx]);
    ptEventNumbersRel_[idx]->SetMarkerSize(1.5);

      compositionRelJES11->Add(ptEventNumbersRel_[idx],"HIST"); 
  }

    for(int idx=kSigJES09; idx<=kQCDJES09; idx++){
    ptEventNumbersRel_ .push_back( (TH1F*)ptEventNumbers_[idx]->Clone() );

    // calculate value for each bin i
    for(int i=2; i<=pt_[kSigJES09]->GetNbinsX(); i++){
      ptEventNumbersRel_[idx]->SetBinContent(  i, (ptEventNumbersRel_[idx]->GetBinContent(i) ) / ( ptEventNumbers_[kSigJES09]->GetBinContent(i)+ptEventNumbers_[kWjetsJES09]->GetBinContent(i)+ptEventNumbers_[kBkgJES09]->GetBinContent(i)+ptEventNumbers_[kZjetsJES09]->GetBinContent(i)+ptEventNumbers_[kQCDJES09]->GetBinContent(i) )  );
    }
    
    histogramStyle(* ptEventNumbersRel_[idx], idx);
    ptEventNumbersRel_[idx]->SetMarkerStyle(markerStyle_[idx]);
    ptEventNumbersRel_[idx]->SetMarkerSize(1.5);

      compositionRelJES09->Add(ptEventNumbersRel_[idx],"HIST"); 
  }

  // ---
  //    create legends 
  // ---

  // create output slide as two legends, each on one half of side
  TLegend *leg1 = new TLegend(0.35, 0.0, 1.0, 1.0);
  leg1->SetFillStyle(3001);
  leg1->SetBorderSize(0);
  for(unsigned int i= ((unsigned int)(((double)(output_.size()))/2.0)); i< output_.size(); i++){
    leg1->AddEntry( pt_[kSig], output_[i]  , "" );;
  }

  TLegend *leg2 = new TLegend(-0.1, 0.0, 0.5, 1.0);
  leg2->SetFillStyle(3001);
  leg2->SetBorderSize(0);
  for(unsigned int i=0; i< (unsigned int)(((double)(output_.size()))/2.0); i++){
    leg2->AddEntry( pt_[kSig], output_[i]  , "" );;
  }

  // create a legend for Signal, JES +/- 10%
  TLegend *leg3 = new TLegend(0.45, 0.65, 1.05, 0.9);
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
  leg5->AddEntry( pt_[kSig]     , "signal only"        , "PL");
  leg5->AddEntry( pt_[kSGBG]    , "signal + background", "PL");
  leg5->AddEntry( pt_[kPseudo50], "pseudo data"        , "P");

  // create a legend for diffX pt(mu) (all left events after selektion, JES +/- 10%)
  TLegend *leg6 = new TLegend(0.45, 0.65, 1.05, 0.9);
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

  // ---
  //    do the printing for pt_ ( Signal and JES +/-10% )
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // draw canvas
  canv0->cd(0);
  canv0->SetTitle("signal: diffX pt distribution tight  #mu after Selection");
  axesStyle(*pt_ [kSig], "p_{t} ( tight #mu ) [GeV]", "rel. # events / binwidth / total # events");
  pt_ [kSig]->GetYaxis()->SetTitleSize  ( 0.04 );
  pt_ [kSig]->GetYaxis()->SetTitleOffset( 2.0  );
  pt_ [kSig]->SetMinimum(0.);
  pt_ [kSig]->SetMaximum(0.035 );
  pt_ [kSig]->SetBinError( 1, 0. );
  for(int i =2; i<= totalBinNumber+1; i++){
    pt_ [kSig]->SetBinError(  i, ptDiffXError_[i-2]  );
  }
  pt_ [kSig]->Draw("");
  pt_ [kSigJES11]->SetLineColor (kBlue);
  pt_ [kSigJES11]->SetLineStyle(3);
  pt_ [kSigJES11]->Draw("same");
  pt_ [kSigJES09]->SetLineColor (kBlack);
  pt_ [kSigJES09]->SetLineStyle(2);
  pt_ [kSigJES09]->Draw("same");
  leg3           ->Draw("same");

  // ---
  //    do the printing for eta_ ( Signal and JES +/-10% )
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetTitle("diffX eta distribution tight  #mu after Selection");
  axesStyle(*eta_ [kSig], "#eta ( tight #mu )", "rel. # events / binwidth / total # events");
  eta_ [kSig]->GetYaxis()->SetTitleSize  ( 0.04 );
  eta_ [kSig]->GetYaxis()->SetTitleOffset( 2.0  );
  eta_ [kSig]->SetMinimum(0.);
  eta_ [kSig]->SetMaximum(1.8* eta_ [kSigJES11]->GetMaximum() );
  eta_ [kSig]->Draw();
  eta_ [kSigJES11]->SetLineColor (kBlue);
  eta_ [kSigJES11]->SetLineStyle(3);
  eta_ [kSigJES11]->Draw("same");
  eta_ [kSigJES09]->SetLineColor (kBlack);
  eta_ [kSigJES09]->SetLineStyle(2);
  eta_ [kSigJES09]->Draw("same");
  leg3            ->Draw("same");

  // ---
  //    do the printing for phi_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetTitle("diffX phi distribution tight  #mu after Selection");
  axesStyle(*phi_ [kSig], "#phi ( tight #mu )", "rel. # events / binwidth / total # events");
  phi_ [kSig]->GetYaxis()->SetTitleSize  ( 0.04 );
  phi_ [kSig]->GetYaxis()->SetTitleOffset( 2.0  );
  phi_ [kSig]->SetMinimum(0.);
  phi_ [kSig]->SetMaximum(1.8* phi_ [kSigJES11]->GetMaximum() );
  phi_ [kSig]->Draw();
  phi_ [kSigJES11]->SetLineColor (kBlue);
  phi_ [kSigJES11]->SetLineStyle(3);
  phi_ [kSigJES11]->Draw("same");
  phi_ [kSigJES09]->SetLineColor (kBlack);
  phi_ [kSigJES09]->SetLineStyle(2);
  phi_ [kSigJES09]->Draw("same");
  leg3            ->Draw("same");

  // ---
  //    do the printing for ptEventNumbers_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  canv3->SetTitle("pt distribution tight  #mu after Selection");
  axesStyle(*ptEventNumbers_ [kSig], "p_{t} ( tight #mu ) [GeV]", "events");
  ptEventNumbers_ [kSig]->SetMinimum(0.);
  ptEventNumbers_ [kSig]->SetMaximum(1.2* ptEventNumbers_ [kSig]->GetMaximum() );
  ptEventNumbers_ [kSig]->SetBinError( 1, 0. );
  for(int i =2; i<= totalBinNumber+1; i++){
    ptEventNumbers_ [kSig]->SetBinError(  i, sqrt( (double)(ptEventNumbers_[kSig]->GetBinContent(i)) )  );
  }
  ptEventNumbers_ [kSig]->Draw("");
  TH1F *ptEvtsJES11= (TH1F*)(ptEventNumbers_ [kSigJES11]->Clone());
  ptEvtsJES11->SetLineColor(kBlue);
  ptEvtsJES11->SetLineStyle(2);
  ptEvtsJES11->Draw("same");
  TH1F *ptEvtsJES09= (TH1F*)( ptEventNumbers_ [kSigJES09]->Clone());
  ptEvtsJES09->SetLineColor(kBlack);
  ptEvtsJES09->SetLineStyle(2);
  ptEvtsJES09->Draw("same");
  leg3       ->Draw("same");

  // ---
  //    do the printing for etaEventNumbers_
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(*canv4);

  // draw canvas
  canv4->cd(0);
  canv4->SetTitle("eta distribution tight  #mu after Selection");
  axesStyle(*etaEventNumbers_ [kSig], "#eta ( tight #mu )", "events");
  etaEventNumbers_ [kSig]->SetMinimum(0.);
  etaEventNumbers_ [kSig]->SetMaximum(1.8* etaEventNumbers_ [kSigJES11]->GetMaximum() );
  etaEventNumbers_ [kSig]->Draw();
  etaEventNumbers_ [kSigJES11]->SetLineColor (kBlue);
  etaEventNumbers_ [kSigJES11]->SetLineStyle(3);
  etaEventNumbers_ [kSigJES11]->Draw("same");
  etaEventNumbers_ [kSigJES09]->SetLineColor (kBlack);
  etaEventNumbers_ [kSigJES09]->SetLineStyle(2);
  etaEventNumbers_ [kSigJES09]->Draw("same");
  leg3                        ->Draw("same");

  // ---
  //    do the printing for phiEventNumbers_
  // ---
  TCanvas* canv5 = new TCanvas("canv5", "canv5", 600, 600); canvasStyle(*canv5);

  // draw canvas
  canv5->cd(0);
  canv5->SetTitle("phi distribution tight  #mu after Selection");
  axesStyle(*phiEventNumbers_ [kSig], "#phi ( tight #mu )", "events");
  phiEventNumbers_ [kSig]->SetMinimum(0.);
  phiEventNumbers_ [kSig]->SetMaximum(1.8* phiEventNumbers_ [kSigJES11]->GetMaximum() );
  phiEventNumbers_ [kSig]->Draw();
  phiEventNumbers_  [kSigJES11]->SetLineColor (kBlue);
  phiEventNumbers_  [kSigJES11]->SetLineStyle(3);
  phiEventNumbers_  [kSigJES11]->Draw("same");
  phiEventNumbers_ [kSigJES09]->SetLineColor (kBlack);
  phiEventNumbers_ [kSigJES09]->SetLineStyle(2);
  phiEventNumbers_ [kSigJES09]->Draw("same");
  leg3                        ->Draw("same");

  // ---
  //    do the printing for EventNumbers (sig and underground) as stack plot
  // ---

  THStack *composition=new THStack ("composition","");

  ptEventNumbersSigNoErrors->SetFillColor(ptEventNumbersSigNoErrors->GetLineColor());
  //  ptEventNumbersSigNoErrors->SetLineColor(kGreen);
  ptEventNumbersSigNoErrors->SetFillStyle(1001);
  composition->Add(ptEventNumbersSigNoErrors);

  for(int idx=kWjets; idx<=kQCD; idx++){
  ptEventNumbers_[idx]->SetFillStyle(1001);
  ptEventNumbers_[idx]->SetFillColor( ptEventNumbers_[idx]->GetLineColor() );
  composition->Add(ptEventNumbers_[idx] );
  }

  TCanvas* canv6 = new TCanvas("canv6", "canv6", 600, 600); canvasStyle(*canv6);
  // draw canvas
  canv6->cd(0);
  canv6->SetTitle("event composition (per bin) after full selection");
  axesStyle(*ptEventNumbersSigNoErrors, "p_{t} ( tight #mu ) [GeV]", "events");
  ptEventNumbersSigNoErrors->SetMaximum( 150 );
  ptEventNumbersSigNoErrors->Draw("AXIS");
  composition               ->Draw("same");
  ptEventNumbers_[kPseudo50]->SetMarkerColor(kBlack);
  ptEventNumbers_[kPseudo50]->SetLineColor(kBlack);
  ptEventNumbers_[kPseudo50]->SetMarkerStyle(22);
  ptEventNumbers_[kPseudo50]->SetMarkerSize(1);
  for(int i =2; i<= totalBinNumber+1; i++){
    ptEventNumbers_[kPseudo50]->SetBinError(  i, (int)sqrt((double)ptEventNumbers_[kPseudo50]->GetBinContent(i))  );
  }
  ptEventNumbers_[kPseudo50]->Draw("psame");
  leg4                      ->Draw("same");


  // ---
  //    do the printing for EventNumbers (sig and underground) as relative plot
  // ---

  TCanvas* canv7 = new TCanvas("canv7", "canv7", 600, 600); canvasStyle(*canv7);
  // draw canvas
  canv7->cd(0);
  canv7->SetTitle("fraction of all surviving events per pt bin");
  canv7->SetGrid(1,1);
  //  canv7->Update();
  axesStyle(*ptEventNumbersRel_[kSig], "p_{t} ( tight #mu ) [GeV]", "fraction (events)");
  ptEventNumbersRel_[kSig]->SetMaximum( 1.0 );
  ptEventNumbersRel_[kSig]->GetYaxis()->SetTitle("fraction (events)");
  ptEventNumbersRel_[kSig]->Draw("");
  for(int idx=kSig; idx<=kQCD; idx++){
    ptEventNumbersRel_[idx]->SetMarkerStyle(markerStyle_[idx]);
    ptEventNumbersRel_[idx]->SetMarkerSize(1.5);
    ptEventNumbersRel_[idx]->Draw("same");
    ptEventNumbersRel_[idx]->Draw("Psame");
    }
  //  compositionRel->Draw("nostack,same");
  leg0          ->Draw("same");

  // ---
  //    do the printing for pt_ ( Signal, Signal + Background and Pseudo Data)
  // ---
  TCanvas* canv8 = new TCanvas("canv8", "canv8", 600, 600); canvasStyle(*canv8);

  // draw canvas
  canv8->cd(0);
  canv8->SetTitle("diffX pt for SG +BG after selection");
  axesStyle(*pt_ [kSGBG], "p_{t} ( tight #mu ) [GeV]", "rel. # events / binwidth / total # events");
  pt_ [kSGBG]->GetYaxis()->SetTitleSize  ( 0.04 );
  pt_ [kSGBG]->GetYaxis()->SetTitleOffset( 2.0  );
  pt_ [kSGBG]->SetMinimum(0.);
  pt_ [kSGBG]->SetMaximum(1.5* pt_ [kSig]->GetMaximum() );
  pt_ [kSGBG]->Draw(); 
  ptDiffXNoErrors->Draw("same");
  pt_ [kPseudo50]->SetMarkerStyle(22);
  for(int i =2; i<= totalBinNumber+1; i++){
    pt_[kPseudo50]->SetBinError(  i, ptDiffXPseudoError_[i-2] );
  }
  pt_ [kPseudo50]->Draw("psame");
  leg5      ->Draw("same");

  // ---
  //    do the printing for ptAllUnbinned_ 
  // ---
  TCanvas* canv9 = new TCanvas("canv9", "canv9", 600, 600); canvasStyle(*canv9);

  // draw canvas
  canv9->cd(0);
  canv9->SetTitle("binning seen @ all datasets weighted");
  axesStyle(*ptAllUnbinned, "p_{t} ( tight #mu ) [GeV]", "events");
  ptAllUnbinned->Rebin(2);
  ptAllUnbinned->GetYaxis()->SetTitleSize  ( 0.04 );
  ptAllUnbinned->GetYaxis()->SetTitleOffset( 2.0  );
  ptAllUnbinned->SetMinimum(0.);
  ptAllUnbinned->SetMaximum(1.2*ptAllUnbinned->GetMaximum() );
  ptAllUnbinned->Draw(); 
  drawcutline(20.0,  0.8*ptAllUnbinned->GetMaximum() );
  drawcutline(35.0,  0.8*ptAllUnbinned->GetMaximum() );
  drawcutline(50.0,  0.8*ptAllUnbinned->GetMaximum() );
  drawcutline(70.0,  0.8*ptAllUnbinned->GetMaximum() );
  drawcutline(95.0,  0.8*ptAllUnbinned->GetMaximum() );
  drawcutline(200.0, 0.8*ptAllUnbinned->GetMaximum() );

  // ---
  //    do the printing for pt_ ( Signal and background JES +/-10% )
  // ---
  TCanvas* canv10 = new TCanvas("canv10", "canv10", 600, 600); canvasStyle(*canv10);

  // draw canvas
  canv10->cd(0);
  canv10->SetTitle("all left events: diffX pt distribution tight  #mu after Selection");
  axesStyle(*pt_ [kSGBG], "p_{t} (#mu) [GeV]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{t}(#mu)}");
  pt_ [kSGBG]->GetYaxis()->SetTitleSize  ( 0.04 );
  pt_ [kSGBG]->GetYaxis()->SetTitleOffset( 2.0  );
  pt_ [kSGBG]->SetMinimum(0.);
  pt_ [kSGBG]->SetMaximum( 0.035 );
  pt_ [kSGBG]->SetLineColor(kBlack);
  pt_ [kSGBG]->Draw();
  pt_ [kSGBGJES11]->SetLineColor (kBlue);
  pt_ [kSGBGJES11]->SetLineStyle(2);
  pt_ [kSGBGJES11]->SetLineWidth(3);
  pt_ [kSGBGJES11]->Draw("same");
  pt_ [kSGBGJES09]->SetLineColor (kRed);
  pt_ [kSGBGJES09]->SetLineStyle(2);
  pt_ [kSGBGJES09]->SetLineWidth(3);
  pt_ [kSGBGJES09]->Draw("same");
  leg6            ->Draw("same");
  TH1F *ptkSGBGNoErrors= (TH1F*)(pt_[kSGBG]->Clone());
  ptkSGBGNoErrors->Draw("same");
  for(int i =2; i<= totalBinNumber+1; i++){
    pt_[kSGBG]->SetBinError(  i, ptDiffXAllSamplesError_[i-2] );
  }


  // ---
  //    do the printing for EventNumbers (sig and underground JES +10%) as stack plot
  // ---

  THStack *compositionJES11=new THStack ("compositionJES11","");
  ptEventNumbers_[kSigJES11]->SetLineColor(kRed);
  for(int idx=kSigJES11; idx<=kQCDJES11; idx++){
  ptEventNumbers_[idx]->SetFillStyle(1001);
  ptEventNumbers_[idx]->SetFillColor( ptEventNumbers_[idx]->GetLineColor() );
  compositionJES11->Add(ptEventNumbers_[idx] );
  }

  TCanvas* canv11 = new TCanvas("canv11", "canv11", 600, 600); canvasStyle(*canv11);
  // draw canvas
  canv11->cd(0);
  canv11->SetTitle("JES +10%: event composition (per bin) after full selection");
  axesStyle(*ptEventNumbersSigNoErrors, "p_{t} ( tight #mu ) [GeV]", "events");
  ptEventNumbersSigNoErrors->SetMaximum( 180 );
  ptEventNumbersSigNoErrors->Draw("AXIS");
  compositionJES11         ->Draw("same");
  leg4                     ->Draw("same");

  // ---
  //    do the printing for EventNumbers (sig and underground, JES +10%) as relative plot
  // ---

  TCanvas* canv12 = new TCanvas("canv12", "canv12", 600, 600); canvasStyle(*canv12);
  // draw canvas
  canv12->cd(0);
  canv12->SetTitle("JES +10%: fraction of all surviving events per pt bin");
  canv12->SetGrid(1,1);
  axesStyle(*ptEventNumbersRel_[kSigJES11], "p_{t} ( tight #mu ) [GeV]", "fraction (events)");
  ptEventNumbersRel_[kSigJES11]->SetMaximum( 1.0 );
  ptEventNumbersRel_[kSigJES11]->GetYaxis()->SetTitle("fraction (events)");
  ptEventNumbersRel_[kSigJES11]->Draw("");
  for(int idx=kSigJES11; idx<=kQCDJES11; idx++){
    ptEventNumbersRel_[idx]->SetMarkerStyle(markerStyle_[idx]);
    ptEventNumbersRel_[idx]->SetMarkerSize(1.5);
    ptEventNumbersRel_[idx]->Draw("same");
    ptEventNumbersRel_[idx]->Draw("Psame");
    }
  //  compositionRel->Draw("nostack,same");
  leg0          ->Draw("same");

  // ---
  //    do the printing for EventNumbers (sig and underground JES -10%) as stack plot
  // ---

  THStack *compositionJES09=new THStack ("compositionJES09","");
  ptEventNumbers_[kSigJES09]->SetLineColor(kRed);
  for(int idx=kSigJES09; idx<=kQCDJES09; idx++){
  ptEventNumbers_[idx]->SetFillStyle(1001);
  ptEventNumbers_[idx]->SetFillColor( ptEventNumbers_[idx]->GetLineColor() );
  compositionJES09->Add(ptEventNumbers_[idx] );
  }

  TCanvas* canv13 = new TCanvas("canv13", "canv13", 600, 600); canvasStyle(*canv13);
  // draw canvas
  canv13->cd(0);
  canv13->SetTitle("JES -10%: event composition (per bin) after full selection");
  axesStyle(*ptEventNumbersSigNoErrors, "p_{t} ( tight #mu ) [GeV]", "events");
  ptEventNumbersSigNoErrors->SetMaximum( 150 );
  ptEventNumbersSigNoErrors->Draw("AXIS");
  compositionJES09         ->Draw("same");
  leg4                     ->Draw("same");

  // ---
  //    do the printing for EventNumbers (sig and underground, JES -10%) as relative plot
  // ---

  TCanvas* canv14 = new TCanvas("canv14", "canv14", 600, 600); canvasStyle(*canv14);
  // draw canvas
  canv14->cd(0);
  canv14->SetTitle("JES -10%: fraction of all surviving events per pt bin");
  canv14->SetGrid(1,1);
  axesStyle(*ptEventNumbersRel_[kSigJES09], "p_{t} ( tight #mu ) [GeV]", "fraction (events)");
  ptEventNumbersRel_[kSigJES09]->SetMaximum( 1.0 );
  ptEventNumbersRel_[kSigJES09]->GetYaxis()->SetTitle("fraction (events)");
  ptEventNumbersRel_[kSigJES09]->Draw("");
  for(int idx=kSigJES09; idx<=kQCDJES09; idx++){
    ptEventNumbersRel_[idx]->SetMarkerStyle(markerStyle_[idx]);
    ptEventNumbersRel_[idx]->SetMarkerSize(1.5);
    ptEventNumbersRel_[idx]->Draw("same");
    ptEventNumbersRel_[idx]->Draw("Psame");
    }
  leg0          ->Draw("same");

  // ---
  //    do the printing for ptEventNumbers_ ( signal + background JES +/-10% )
  // ---
  TCanvas* canv15 = new TCanvas("canv15", "canv15", 600, 600); canvasStyle(*canv15);

  // draw canvas
  canv15->cd(0);
  canv15->SetTitle("pt (#mu) all samples after Selection");
  axesStyle(*ptEventNumbers_ [kSGBG], "p_{t} ( #mu ) [GeV]", "events");
  ptEventNumbers_ [kSGBG]->SetMinimum( 0.);
  ptEventNumbers_ [kSGBG]->SetMaximum( 240 );
  ptEventNumbers_ [kSGBG]->SetLineWidth(3);
  ptEventNumbers_ [kSGBG]->SetStats(kFALSE);
  ptEventNumbers_ [kSGBG]->Draw("e0");
  ptEventNumbers_ [kSGBG]->Draw("same");
  ptEventNumbers_ [kSGBGJES11]->SetLineColor(kBlue);
  ptEventNumbers_ [kSGBGJES11]->SetLineStyle(2);
  ptEventNumbers_ [kSGBGJES11]->SetLineWidth(3);
  ptEventNumbers_ [kSGBGJES11]->Draw("same");
  ptEventNumbers_ [kSGBGJES09]->SetLineColor(kRed);
  ptEventNumbers_ [kSGBGJES09]->SetLineStyle(2);
  ptEventNumbers_ [kSGBGJES09]->SetLineWidth(3);
  ptEventNumbers_ [kSGBGJES09]->Draw("same");
  //  TH1F *ptNumberskSGBGNoErrors= (TH1F*)(ptEventNumbers_[kSGBG]->Clone());
  //  ptNumberskSGBGNoErrors->Draw("same");
  leg7                        ->Draw("same");

  // ---
  //    do the printing for the output text
  // ---
  TCanvas* canv16 = new TCanvas("canv16", "canv16", 600, 600); canvasStyle(*canv16);

  // draw canvas
  canv16->cd(0);
  canv16->SetTitle("detail numbers");
  leg1->Draw("");
  leg2->Draw("same");

  // ---
  // saving
  // ---
  
  // ps

  canv0->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps(" );
  canv1->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps"  );
  canv2->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps"  );
  canv3->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps"  );
  canv4->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps"  );
  canv5->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps"  );
  canv6->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps"  );
  canv7->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps"  );
  canv8->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps"  );
  canv9->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps"  );
  canv10->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps" );
  canv11->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps" );
  canv12->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps" );
  canv13->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps" );
  canv14->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps" );
  canv14->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps" );
  canv16->Print("./diffXSecFromSignal/plots/diffXJESandBGMcatnlo7TeV.ps)");

  // png
  canv0->Print("./diffXSecFromSignal/plots/ptDiffXSecJESMcatnlo7TeV.png"         );
  canv1->Print("./diffXSecFromSignal/plots/etaDiffXSecJESMcatnlo7TeV.png"        );
  canv2->Print("./diffXSecFromSignal/plots/phiDiffXSecJESMcatnlo7TeV.png"        );
  canv3->Print("./diffXSecFromSignal/plots/ptInclusiveJESMcatnlo7TeV.png"        );
  canv4->Print("./diffXSecFromSignal/plots/etaInclusiveJESMcatnlo7TeV.png"       );
  canv5->Print("./diffXSecFromSignal/plots/phiInclusiveJESMcatnlo7TeV.png"       );
  canv6->Print("./diffXSecFromSignal/plots/eventComposition.png"                 );
  canv7->Print("./diffXSecFromSignal/plots/eventCompositionRelative.png"         );
  canv8->Print("./diffXSecFromSignal/plots/ptDiffXSecForSGBGAndPseudoData.png"   );
  canv9->Print("./diffXSecFromSignal/plots/ptBinnigFromAllWeighted.png"          );
  canv10->Print("./diffXSecFromSignal/plots/ptDiffXSecJESAllLeftEvents7TeV.png"  );
  canv11->Print("./diffXSecFromSignal/plots/eventCompositionJES11.png"           );
  canv12->Print("./diffXSecFromSignal/plots/eventCompositionRelativeJES11.png"   );
  canv13->Print("./diffXSecFromSignal/plots/eventCompositionJES09.png"           );
  canv14->Print("./diffXSecFromSignal/plots/eventCompositionRelativeJES09.png"   );
  canv15->Print("./diffXSecFromSignal/plots/ptInclusiveJESAfterSelektion7TeV.png");
  canv16->Print("./diffXSecFromSignal/plots/ptOutputJESandBGMcatnlo7TeV.png"     );

}

void canvasStyle(TCanvas& canv) 
{
  canv.SetFillStyle   ( 4000 );
  canv.SetLeftMargin  ( 0.20 );
  canv.SetRightMargin ( 0.05 );
  canv.SetBottomMargin( 0.15 );
  canv.SetTopMargin   ( 0.05 );
}

void histogramStyle(TH1& hist, unsigned int style) 
{
  // pre-defined line style
  std::vector<int> color;
  color.push_back( kRed   ); 
  color.push_back( kGreen ); 
  color.push_back( kBlue  );
  color.push_back( 6      );
  color.push_back( 14     );
  color.push_back( kRed   );
  color.push_back( kGreen ); 
  color.push_back( kBlue  );
  color.push_back( 6      );
  color.push_back( 14     );
  color.push_back( kRed   );
  color.push_back( kGreen ); 
  color.push_back( kBlue  );
  color.push_back( 6      );
  color.push_back( 14     );
  color.push_back( kBlack );
  color.push_back( kBlue  );
  color.push_back( kBlack );
  color.push_back( kRed   );

  // pre-defined marker style
  std::vector<int> marker;
  marker.push_back( 20);

  // set line width
  
  hist.SetLineWidth(3);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color[style]);
  hist.SetMarkerColor(color[style]);
  
}

void drawcutline(double cutval, double maximum)
{
  TLine *cut = new TLine();
  cut->SetLineWidth(3);
  cut->SetLineColor(28);
  cut->DrawLine(cutval,0.,cutval,maximum);
}

void axesStyle(TH1& hist, const char* titleX, const char* titleY) 
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
  hist.GetYaxis()->SetTitleSize  ( 0.07);
  hist.GetYaxis()->SetTitleColor (    1);
  hist.GetYaxis()->SetTitleOffset(  1.2);
  hist.GetYaxis()->SetTitleFont  (   62);
  hist.GetYaxis()->SetLabelSize  ( 0.04);
  hist.GetYaxis()->SetLabelFont  (   62);
  hist.GetYaxis()->CenterTitle   ( true);
}
