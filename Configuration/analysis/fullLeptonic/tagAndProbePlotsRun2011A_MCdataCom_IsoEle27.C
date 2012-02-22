#include "basicFunctionsEff.h"

void tagAndProbePlotsRun2011A_MCdataCom_IsoEle27(bool save=false)
{
  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetPadBottomMargin(0.11);
  gStyle->SetLabelSize(0.05,"XY");
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetFillColor(0);
  
  
  /// path where input files are stored
  TString inputPathScratch  ="/scratch/hh/current/cms/user/jlange/output_4_2_4/fullLeptonic";
  TString inputPath42       ="/afs/naf.desy.de/user/j/jlange/nafscratch/top/CMSSW_4_2_4/src/TopAnalysis/Configuration/analysis/fullLeptonic";
  
//   TString outputFolder   = "/afs/desy.de/user/j/jlange/analysis/tagAndProbe/plots/2011/singleEle/IsoEle27-32MCdataComp";
   TString outputFolder   = "/afs/desy.de/user/j/jlange/analysis/tagAndProbe/plots/2011/singleEle/ID-Iso";
   TString outputFileName = "/ID-Iso_AllWrtIsoEle27NoPUwCombined_";
//   TString outputFileName = "/IsoEle27-32_5GeVaboveThresholdInclCombinedData";
//   TString outputFileName = "/IsoEle27-32_5GeVaboveThreshold";
//  TString outputFileName = "/IsoEle27-32_5GeVaboveThresholdCombinedData";
  //TString outputFileName = "/IsoEle27-32_";

  TString fileFormatArr []= {"root", "png"};
  std::vector<TString> fileFormat(fileFormatArr, fileFormatArr + sizeof(fileFormatArr)/sizeof(TString));
  
  /// if set to 0: all plots (probe, test, eff) are drawn; to 1: only eff plots
  int onlyEffPlots =1;
  /// method ID of MC file to normalise scale factors to
  TString mIDnorm = "m1";
  std::cout<< "Efficiency wrt. which SF is supposed to be normalized " <<  mIDnorm << std::endl;

  
   /// map with structure that keeps features of methods, like file, filename, legend etc.
  std::map<TString, method*> method_;
  
  //TString mIDarr []= {"m3", "m4", "m5","m6","m7","m8"};
//   TString mIDarr []= {"m1", "m2", "m3", "m4", "m5"};
  //TString mIDarr []= {"m1", "m1b", "m2", "m2b", "m3", "m4"};
  TString mIDarr []= {"m1", "m5"};
  //TString mIDarr []= {"m1"};
  std::vector<TString> mID(mIDarr, mIDarr + sizeof(mIDarr)/sizeof(TString));
  int mIDNum = mID.size();
  std::cout<< "Number of considered methods (i.e. files): " <<  mIDNum << std::endl;
  
  // check if mIDnorm is in vector and give error if not
  bool inVector=false;
  for(int i=0; i< mIDNum; i++) if(mID[i]==mIDnorm) inVector=true;
  if(!inVector) {
    std::cout<<"ERROR!!!! Efficiency wrt. which SF is supposed to be normalized is not in mID vector!!! "<<std::endl; 
    return;
  }
  
  TString fileName ;
  
    /// Define histo and legend styles and options
//   int lineStyle   []= {1,1,1,1,1,1};
//   int lineColor   []= {2,1,4,kGreen+2,kGray+2,3};
//   int markerStyle []={1,21,22,20,22,23};
//   int markerColor []= {2,1,4,kGreen+2,kGray+2,3};
//   TString drawOpt []= {"","E X0 P same","E X0 P same","E X0 same","E X0 same","E same"};
//   TString legOpt  []= {"L","P","P","P","P","P"};
//   bool legOnPlot = false;
  
  /// Constructor for struct method(TString iniFileName, TString iniLegName, int iniLineStyle, int iniLineColor, int iniMarkerStyle, int iniMarkerColor, TString iniDrawOpt, TString iniLepOpt, TString source)
  
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet.root";
//   method_["m1"] = new method(fileName, "MC, IsoEle27, p_{T}>32GeV", 1, 2, 1, 2, "E same", "LP","treeV2","probePt>32.","");
//    //PUweightEPSeventWeightPU
//   
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_160404_163869_HLT_IsoEle27_Ele25TriJet_cfg/analyzeZEleEleTagAndProbeRun2011A_160404_163869_HLT_IsoEle27_IsoEle25TriJet.root";
//   method_["m2"] = new method(fileName, "Run May10 IsoEle27, p_{T}>32GeV", 1, 2, 21, 2, "E same", "LP","treeV2","probePt>32.","");
//   
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet.root";
//   method_["m3"] = new method(fileName, "Summer11 IsoEle32, p_{T}>37GeV", 2, 4, 1, 4, "E same", "LP","treeV2","probePt>37.","PUweightEPSeventWeightPU");
//   
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_IsoEle25TriJet.root";
//   method_["m4"] = new method(fileName, "Run PromptV4 IsoEle32, p_{T}>37GeV", 2, 4, 25, 4, "E same", "LP","treeV2","probePt>37.","");
//   
// //   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_160404_167913_HLT_IsoEle27-32_IsoEle25TriJet.root";
// //   method_["m5"] = new method(fileName, "Run May10+PromptV4 IsoEle27(32), p_{T}>32(37)GeV", 2, 1, 26, 1, "E same", "LP","treeV2","(probePt>32. && run<165000) || (probePt>37. && run>165000)","");
//   
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_160404_167913_HLT_IsoEle27-32_IsoEle25TriJet.root";
//   method_["m5"] = new method(fileName, "Daten, IsoEle27(32), p_{T}>32(37)GeV", 2, 1, 21, 1, "E same", "LP","treeV2","(probePt>32. && run<165000) || (probePt>37. && run>165000)","");
  
  
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet.root";
//   method_["m1"] = new method(fileName, "Summer11 IsoEle27 PUw", 1, 2, 1, 2, "E same", "LP","treeV2","","");
   //PUweightEPSeventWeightPU
  //treeV2
  
  fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet.root";
  method_["m1"] = new method(fileName, "MC", 1, 2, 1, 2, "E same", "LP","treeV2","","");
  
  fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet.root";
  method_["m1b"] = new method(fileName, "Summer11 IsoEle27 no PUw", 1, 1, 1, 1, "E same", "LP","treeV2","","");
  
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet.root";
//   method_["m1c"] = new method(fileName, "Summer11 IsoEle27 PUw histo", 1, 8, 1, 8, "E same", "LP","histo","","");
  
  fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet.root";
  method_["m2"] = new method(fileName, "Summer11 IsoEle32 PUw", 2, 4, 1, 4, "E same", "LP","treeV2","","PUweightEPSeventWeightPU");
  
  fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet.root";
  method_["m2b"] = new method(fileName, "Summer11 IsoEle32 no PUw", 2, 1, 1, 1, "E same", "LP","treeV2","","");
  
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet.root";
//   method_["m4"] = new method(fileName, "Summer11 IsoEle32 tagPt>35", 3, 4, 1, 4, "E same", "LP","treeV2","tagPt>35","PUweightEPSeventWeightPU");
  
  fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_160404_163869_HLT_IsoEle27_Ele25TriJet_cfg/analyzeZEleEleTagAndProbeRun2011A_160404_163869_HLT_IsoEle27_IsoEle25TriJet.root";
  method_["m3"] = new method(fileName, "Run May10 IsoEle27", 1, 2, 21, 2, "E same", "LP","treeV2","","");
  
 fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_IsoEle25TriJet.root";
  method_["m4"] = new method(fileName, "Run PromptV4 IsoEle32", 2, 4, 25, 4, "E same", "LP","treeV2","","");
  
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_160404_167913_HLT_IsoEle27-32_IsoEle25TriJet.root";
//   method_["m5"] = new method(fileName, "Run May10+PromptV4 IsoEle27(32)", 2, 1, 26, 1, "E same", "LP","treeV2","","");
  fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_160404_167913_HLT_IsoEle27-32_IsoEle25TriJet.root";
  method_["m5"] = new method(fileName, "Daten", 2, 1, 21, 1, "E same", "LP","treeV2","","");
  
//   
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_160404_167913_HLT_IsoEle27-32_IsoEle25TriJet.root";
//   method_["m6"] = new method(fileName, "Run May10+PromptV4 IsoEle27(32) tagPt>35", 2, 1, 27, 1, "E same", "LP","treeV2","tagPt>35","");
  
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet.root";
//   method_["m6"] = new method(fileName, "Summer11 IsoEle32 pt>35 GeV", 2, 6, 1, 6, "E same", "LP","treeV2","tagPt>35","PUweightEPSeventWeightPU");
//   
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_IsoEle25TriJet.root";
//   method_["m7"] = new method(fileName, "Run PromptV4 IsoEle32 pt>35 GeV", 2, 6, 27, 6, "E same", "LP","treeV2","tagPt>35","");
//   
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet.root";
//   method_["m8"] = new method(fileName, "Summer11 IsoEle32 pt>50 GeV", 2, 8, 1, 8, "E same", "LP","treeV2","tagPt>50","PUweightEPSeventWeightPU");
//   
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_IsoEle25TriJet.root";
//   method_["m9"] = new method(fileName, "Run PromptV4 IsoEle32 pt>50 GeV", 2, 8, 28, 8, "E same", "LP","treeV2","tagPt>50","");

  fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_170053_178380_HLT_IsoEle32_Ele25TriJet_cfg/analyzeZEleEleTagAndProbeRun2011AB_170053_178380_HLT_IsoEle32_IsoEle25TriJet.root";
  method_["m10"] = new method(fileName, "Run Aug05+PromptV6 +B IsoEle32", 2, 8, 27, 8, "E same", "LP","treeV2","","");
  
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_170053_178380_HLT_IsoEle32_Ele25TriJet_cfg/analyzeZEleEleTagAndProbeRun2011AB_170053_178380_HLT_IsoEle32_IsoEle25TriJet.root";
//   method_["m11"] = new method(fileName, "Run Aug05+PromptV6 IsoEle32", 2, 6, 28, 6, "E same", "LP","treeV2","run<175800","");
//   
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_170053_178380_HLT_IsoEle32_Ele25TriJet_cfg/analyzeZEleEleTagAndProbeRun2011AB_170053_178380_HLT_IsoEle32_IsoEle25TriJet.root";
//   method_["m12"] = new method(fileName, "Run B IsoEle32", 2, 2, 29, 2, "E same", "LP","treeV2","run>175800","");
  
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011B5e33_178420_180252_HLT_Ele32_WP70_Ele25TriPFJet_cfg/analyzeZEleEleTagAndProbeRun2011AB_178420_180252_HLT_Ele32_WP70_IsoEle25TriJet.root";
//   method_["m13"] = new method(fileName, "Run B 5e33 Ele32_WP70", 2, 4, 25, 4, "E same", "LP","treeV2","","");
  
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_160404_167913_HLT_IsoEle27-32_IsoEle25TriJet.root";
//   method_["m6"] = new method(fileName, "Run May10+PromptV4 IsoEle27(32) Q=-1", 2, 4, 26, 4, "E same", "LP","treeV2","probeCharge==-1 &&tagPt>50","");
//   
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_160404_167913_HLT_IsoEle27-32_IsoEle25TriJet.root";
//   method_["m7"] = new method(fileName, "Run May10+PromptV4 IsoEle27(32) Q=1", 2, 8, 26, 8, "E same", "LP","treeV2","probeCharge==1 &&tagPt>50","");
  
  
  /// different tap studies (different efficiencies)
//    const int folderNum=5;
//    TString folderID[]={"tapTrkQ", "tapIso", "tapMinDR", "tapTotalSelection", "tapTrigger"};
//    TString foldersTitle[]={"ID", "Isolation", "#DeltaR (after Iso Cut)","Overall Selection", "Trigger"};
   
//    const int folderNum=6;
//    TString folderID[]={"tapTrkQEle", "tapIDEle", "tapIsoEle", "tapConvRejEle", "tapTotalSelectionEle", "tapTriggerEle"};
//    TString foldersTitle[]={"Track Quality", "ID", "Isolation", "Conversion Rejection", "Overall Selection", "Trigger"};
  
//   const int folderNum=4;
//   TString folderID[]={"tapTrkQEle", "tapIDEle", "tapIsoEle", "tapConvRejEle"};
//   TString foldersTitle[]={"Track Quality", "ID", "Isolation", "Conversion Rejection"};
   
//    const int folderNum=2;
//    TString folderID[]={"tapTotalSelectionEle", "tapTriggerEle"};
//    TString foldersTitle[]={"Overall Selection", "Trigger"};
  
  const int folderNum=1;
  TString folderID[]={"tapTotalSelectionEle"};
  TString foldersTitle[]={"Overall Selection"};
  
//   const int folderNum=1;
//   TString folderID[]={"tapTriggerEle"};
//   TString foldersTitle[]={"Trigger"};


  /// effName = name of the effHisto; variables: corresponding variable to effName; cuts: corresponding cut to effName

//    TString effIDarr[]      = {"Control", "Pt", "Eta", "RelIso", "PVMult", "Mult", "MinDR","lepLepMass"};
  TString effIDarr[]      = {"Control", "Pt", "Eta", "RelIso", "PVMult", "Mult"};
   //TString effIDarr[]      = {"Control", "Pt", "Eta", "RelIso", "PVMult", "Mult", "PtEta0to1p5", "PtEta1p5to2p1"};
//   TString effIDarr[]      = {"Pt", "Eta", "RelIso", "PVMult", "Mult", "MinDR"};
//   TString effIDarr[]      = {"Control"};
  std::vector<TString> effID(effIDarr, effIDarr + sizeof(effIDarr)/sizeof(TString));
  int effIDNum = effID.size();
  std::cout<< "Number of considered plots: " <<  effIDNum << std::endl;
    
  /// map with structure that keeps features of histograms
  std::map<TString, std::map<TString, eff*> > eff_;
  
  /// title for histo, x and y axis (separated by "/")
  TString title0 ="";
  TString title ="";
  
  /// axis range
  //double yLo = 0.5, yHi = 1.1;
  double yLo = 0.5, yHi = 1.;
  double yLoSF = 0.9, yHiSF = 1.1;
  
  /// Constructor for struct eff(TString iniVar, T  iniCuts, TString iniBins, TString iniTitles, double iniYLo=-9999., double iniYHi=-9999., double iniXLo=-9999., double iniXHi=-9999.)
//   TCut cutPt  =""; /*"(probePt>30. || testPt>30. )";*/
//   TCut cutEta =""; /*"(TMath::Abs(probeEta)<2.1 || TMath::Abs(testEta)<2.1)";*/
//   TCut cutPtEta = cutPt && cutEta;
  TCut cutPt  ="probePt>30."; /*"(probePt>30. || testPt>30. )";*/
  TCut cutEta ="TMath::Abs(probeEta)<2.5"; /*"(TMath::Abs(probeEta)<2.1 || TMath::Abs(testEta)<2.1)";*/
  TCut cutPtEta = cutPt && cutEta;
  for(int iFolder=0; iFolder < folderNum; iFolder++){
    title = foldersTitle[iFolder]+" Efficiency/ / ";
    eff_["Control"][folderID[iFolder]]        =new eff("Control", cutPtEta, mBinsControl, binsControl_, title, yLo, yHi, -9999.,-9999.,true);
    title = foldersTitle[iFolder]+" Efficiency/p_{T} [GeV]/ ";
    eff_["Pt"][folderID[iFolder]]             =new eff("Pt", cutEta, mBinsPt, binsPt_, title, yLo, yHi, 30.,150.);
    title = foldersTitle[iFolder]+" Efficiency/#eta/ ";
    eff_["Eta"][folderID[iFolder]]             =new eff("Eta", cutPt, mBinsEtaEle, binsEtaEle_, title, yLo, yHi);
    title = foldersTitle[iFolder]+" Efficiency/relIso/ ";
    eff_["RelIso"][folderID[iFolder]]          =new eff("RelIso", cutPtEta, mBinsRelIso, binsRelIso_, title, yLo, yHi);
    title = foldersTitle[iFolder]+" Efficiency/absIso/ ";
    eff_["AbsIso"][folderID[iFolder]]          =new eff("AbsIso", cutPtEta, mBinsAbsIso, binsAbsIso_, title, yLo, yHi);
    title = foldersTitle[iFolder]+" Efficiency/Primary Vertices/ ";
    eff_["PVMult"][folderID[iFolder]]          =new eff("PVMult", cutPtEta, mBinsPVMult, binsPVMult_, title, yLo, yHi,0.,20.);
    title = foldersTitle[iFolder]+" Efficiency/N_{jet}/ ";
    eff_["Mult"][folderID[iFolder]]            =new eff("Mult", cutPtEta, mBinsMult, binsMult_, title, yLo, yHi);
    title = foldersTitle[iFolder]+" Efficiency/Minimum #DeltaR(#mu,jet)/ ";
    eff_["MinDR"][folderID[iFolder]]            =new eff("MinDR", cutPtEta, mBinsMinDR, binsMinDR_, title, yLo, yHi);
    title = foldersTitle[iFolder]+" Efficiency/Minimum M_{lep,lep}/ ";
    eff_["lepLepMass"][folderID[iFolder]]            =new eff("lepLepMass", cutPtEta, mBinsLepLepMass, binsLepLepMass_, title, yLo, yHi);
    
    title = foldersTitle[iFolder]+" Efficiency/p_{T} [GeV]/ ";
    eff_["PtEta0to1p5"][folderID[iFolder]]             =new eff("Pt", "TMath::Abs(probeEta)<1.5", mBinsPt, binsPt_, title, yLo, yHi, 30.,150.,true);
    
    title = foldersTitle[iFolder]+" Efficiency/p_{T} [GeV]/ ";
    eff_["PtEta1p5to2p1"][folderID[iFolder]]             =new eff("Pt", "TMath::Abs(probeEta)>1.5 && TMath::Abs(probeEta)<2.1", mBinsPt, binsPt_, title, yLo, yHi, 30.,150.,true);
  }

  /// ---
  /// get efficiencies from tree or histo
  ///  ---
  for(int iMethod=0; iMethod<mIDNum; iMethod++){
    for(int iEff=0; iEff<effIDNum; iEff++){
      for(int iFolder=0; iFolder<folderNum; iFolder++){
	getEfficiencies(eff_[effID[iEff]][folderID[iFolder]], method_[mID[iMethod]], mID[iMethod], folderID[iFolder], folderID[iFolder]);
      }
    }
  }

 /// Draw one Canvas for each folder comparing different methods.
 /// Each canvas shows test (1st row) and probe collection (2nd) and efficiency (3rd) for different variables (columns)
 TCanvas* CanvComp [folderNum];
 TCanvas* CanvSFComp [folderNum];
 TCanvas* CanvEvtsComp [folderNum];
 TCanvas* CanvEvtsNormComp [folderNum];
 TCanvas* CanvLeg = new TCanvas("CanvLeg", "CanvLeg", 350,200);

 std::cout<< "Drawing eff. and SF"<<std::endl;
for(int iFolder=0; iFolder<folderNum; iFolder++) {

  CanvComp[iFolder] = new TCanvas("Comparison"+folderID[iFolder], "Comparison"+folderID[iFolder], 1700,1000);
  CanvSFComp[iFolder] = new TCanvas("ComparisonSF"+folderID[iFolder], "ComparisonSF"+folderID[iFolder], 1700,1000);
  CanvEvtsComp[iFolder] = new TCanvas("ComparisonEvts"+folderID[iFolder], "ComparisonEvts"+folderID[iFolder], 1700,1000);
  CanvEvtsNormComp[iFolder] = new TCanvas("ComparisonEvtsNorm"+folderID[iFolder], "ComparisonEvtsNorm"+folderID[iFolder], 1700,1000);
  
  CanvComp[iFolder]->Divide(4,2);
  CanvSFComp[iFolder]->Divide(4,2);
  CanvEvtsComp[iFolder]->Divide(4,2);
  CanvEvtsNormComp[iFolder]->Divide(4,2);
  
  for(int iEff=0; iEff<effIDNum; iEff++){
    CanvComp[iFolder]->cd(iEff+1);
    std::cout<< "============================================================" <<std::endl;
    std::cout<< "Drawing eff. for "<< folderID[iFolder] <<std::endl;
    drawEfficiencies(eff_[effID[iEff]][folderID[iFolder]], method_, mID, 0.15,0.15,0.9,0.45,eff_[effID[iEff]][folderID[iFolder]]->drawLegend);
    CanvSFComp[iFolder]->cd(iEff+1);
    std::cout<< "Drawing SF"<<std::endl;
    drawSF          (eff_[effID[iEff]][folderID[iFolder]], method_, mID, mIDnorm, 0.15,0.15,0.9,0.45,eff_[effID[iEff]][folderID[iFolder]]->drawLegend, yLoSF, yHiSF, eff_[effID[iEff]][folderID[iFolder]]->xLo, eff_[effID[iEff]][folderID[iFolder]]->xHi);
    // if desired plot also raw event number histos
    if(onlyEffPlots!=1) {
      std::cout<< "Drawing event numbers"<<std::endl;
      CanvEvtsComp[iFolder]->cd(iEff+1);
      drawEventHistos(eff_[effID[iEff]][folderID[iFolder]], method_, mID, 0.15,0.15,0.9,0.45,eff_[effID[iEff]][folderID[iFolder]]->drawLegend);
      CanvEvtsNormComp[iFolder]->cd(iEff+1);
      drawEventHistos(eff_[effID[iEff]][folderID[iFolder]], method_, mID, 0.15,0.15,0.9,0.45,eff_[effID[iEff]][folderID[iFolder]]->drawLegend,"normInt");
    }
  }
  // draw legend
  CanvLeg->cd();
  if(iFolder==0) drawLegend(eff_[effID[0]][folderID[0]], method_, mID, 0.,0.,1.,1.);
  
//   effControl[iMethod][iFolder]->GetXaxis()->SetNdivisions(0);
//   effRelIso[iMethod][iFolder]->GetXaxis()->SetNdivisions(505);
 
 if(save){
   for(unsigned int iFileFormat=0; iFileFormat < fileFormat.size(); iFileFormat++){
    CanvComp[iFolder]->Print(outputFolder+outputFileName+folderID[iFolder]+"_overview."+fileFormat[iFileFormat]);
    for(int iEff=0; iEff<effIDNum; iEff++){
      CanvComp  [iFolder]->cd(iEff+1)->Print(outputFolder+outputFileName+folderID[iFolder]+"_"+effID[iEff]+"."+fileFormat[iFileFormat]);
      CanvSFComp[iFolder]->cd(iEff+1)->Print(outputFolder+outputFileName+folderID[iFolder]+"_SF_"+effID[iEff]+"."+fileFormat[iFileFormat]);
    }
    if(iFolder==0) CanvLeg->Print(outputFolder+outputFileName+"_Legend."+fileFormat[iFileFormat]);
    std::cout<<"Canvas with plots is saved in "<<outputFolder<<std::endl;
   }
  }
 }
}
