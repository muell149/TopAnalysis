#include "basicFunctionsEff.h"

void tagAndProbePlotsRun2011A_MCdataCom_IsoEle25_27_32_TaP_and_subtrigger(bool save=false)
{
  /// set style
  // ============================
  //  Set ROOT Style
  // ============================
 
  gROOT->Reset();
//   gROOT->SetStyle("Plain");
  //   
//   TStyle myStyle("HHStyle","HHStyle");
//   setHHStyle(myStyle);
//   TGaxis::SetMaxDigits(2);
//   myStyle.cd();
//   gROOT->SetStyle("HHStyle");
//   gROOT->ForceStyle();  
  
  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetPadBottomMargin(0.11);
  gStyle->SetLabelSize(0.05,"XY");
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetFillColor(0);
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  gStyle->SetPadTickY(1);
  
//   const int fontstyle1=62;
  const int fontstyle1=42;
  gStyle->SetTitleFont(fontstyle1);
  gStyle->SetTitleFont(fontstyle1, "XYZ");
  gStyle->SetLabelFont(fontstyle1, "XYZ");
  gStyle->SetTextFont(fontstyle1);
  
  /// path where input files are stored
  TString inputPathScratch  ="/scratch/hh/current/cms/user/jlange/output_4_2_4/fullLeptonic";
  TString inputPath42       ="/afs/naf.desy.de/user/j/jlange/nafscratch/top/CMSSW_4_2_4/src/TopAnalysis/Configuration/analysis/fullLeptonic";
  TString inputPath428       ="/afs/naf.desy.de/user/j/jlange/nafscratch/top/CMSSW_4_2_8_patch7/src/TopAnalysis/Configuration/analysis/fullLeptonic";
  
  TString outputFolder   = "/afs/desy.de/user/j/jlange/analysis/tagAndProbe/plots/2011/singleEle/Fall11/DataMCcomp_IsoEle25subTrigger";
  TString outputFileName = "/IsoEle25subTrigger_WP70_CiCcomp_";
//   TString outputFileName = "/IsoEle27-32_5GeVaboveThresholdInclCombinedData";
  //TString outputFileName = "/IsoEle27-32_5GeVaboveThreshold";
  //TString outputFileName = "/IsoEle27-32_";

  TString fileFormatArr []= {"root", "png", "eps"};
  std::vector<TString> fileFormat(fileFormatArr, fileFormatArr + sizeof(fileFormatArr)/sizeof(TString));
  
  /// if set to 0: all plots (probe, test, eff) are drawn; to 1: only eff plots
  int onlyEffPlots =0;
  /// method ID of MC file to normalise scale factors to
  TString mIDnorm = "refTr1MCJet110";
  std::cout<< "Efficiency wrt. which SF is supposed to be normalized " <<  mIDnorm << std::endl;

  
   /// map with structure that keeps features of methods, like file, filename, legend etc.
  std::map<TString, method*> method_;
  
  //TString mIDarr []= {"m1","m2"};
  //TString mIDarr []= {"m1", "m1noPU", "m1PUEPS", "m1PUup", "m1PUdown","m2"};
//   TString mIDarr []= {"m1","m2", "m2-27", "m2-32EPS", "m2-32ApostEPS", "m2-32B", "m2-32WP70B"};
//    TString mIDarr []= {"m1", "refTr1MCJet110", "refTr1MCAll", "refTr1", "refTr2"};
  TString mIDarr []= {"refTr1MCJet110", "refTr1MCJet110WP70", "m1", "refTr2EPSnew", "refTr2EPSnewWP70"};
  //TString mIDarr []= {"m1", "refTr1MCJet110", "refTr1MCAll", "refTr1", "refTr1424"};
//  TString mIDarr []= {"refTr1", "refTr2"};
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
  
   /// Fall11 MC
  fileName=inputPath428+"/naf_analyzeZEleEleTagAndProbeMCFall11_HLT_IsoEle32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCFall11_HLT_IsoEle32_IsoEle25TriJet.root";
  method_["m1"] = new method(fileName, "Simulation IsoEle32", 3, 2, 1, 1, "E", "L", "treeV2","probePt>37. && TMath::Abs(probeEta)<2.1","eventWeightPUeventWeightPU");
  
  fileName=inputPath428+"/naf_analyzeZEleEleTagAndProbeMCFall11_HLT_IsoEle32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCFall11_HLT_IsoEle32_IsoEle25TriJet.root";
  method_["m1noPU"] = new method(fileName, "Fall11 IsoEle32 no PUrew", 2, 2, 1, 1, "E", "L", "treeV2","probePt>37. && TMath::Abs(probeEta)<2.1","");
  
  fileName=inputPath428+"/naf_analyzeZEleEleTagAndProbeMCFall11_HLT_IsoEle32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCFall11_HLT_IsoEle32_IsoEle25TriJet.root";
  method_["m1PUEPS"] = new method(fileName, "Fall11 IsoEle32 PUrew EPS", 3, 8, 1, 1, "E", "L", "treeV2","probePt>37.","eventWeightPUEPSeventWeightPUEPS");
  
  fileName=inputPath428+"/naf_analyzeZEleEleTagAndProbeMCFall11_HLT_IsoEle32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCFall11_HLT_IsoEle32_IsoEle25TriJet.root";
  method_["m1PUup"] = new method(fileName, "Fall11 IsoEle32 PUrew UP", 2, 4, 1, 1, "E", "L", "treeV2","probePt>37.","eventWeightPUsysUpeventWeightPUUp");
  
  fileName=inputPath428+"/naf_analyzeZEleEleTagAndProbeMCFall11_HLT_IsoEle32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCFall11_HLT_IsoEle32_IsoEle25TriJet.root";
  method_["m1PUdown"] = new method(fileName, "Fall11 IsoEle32 PUrew DOWN", 2, 7, 1, 1, "E", "L", "treeV2","probePt>37.","eventWeightPUsysDowneventWeightPUDown");
  
  /// data
//   fileName=inputPath428+"/naf_analyzeZEleEleTagAndProbeRun2011All_HLT_IsoEle27_32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeRun2011All_HLT_IsoEle27_32_IsoEle25TriJet.root";
//   method_["m2"] = new method(fileName, "2011 Data IsoEle27/32", 1, 1, 21, 1, "E", "L", "treeV2","probePt>30. && TMath::Abs(probeEta)<2.1 && run<=178380");
//   
//   fileName=inputPath428+"/naf_analyzeZEleEleTagAndProbeRun2011All_HLT_IsoEle27_32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeRun2011All_HLT_IsoEle27_32_IsoEle25TriJet.root";
//   method_["m2-27"] = new method(fileName, "2011 Data IsoEle27, run<=161176", 1, 1, 22, 1, "E", "L", "treeV2","probePt>30. && TMath::Abs(probeEta)<2.1 && run<=161176");
//   
  fileName=inputPath428+"/naf_analyzeZEleEleTagAndProbeRun2011All_HLT_IsoEle27_32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeRun2011All_HLT_IsoEle27_32_IsoEle25TriJet.root";
  method_["m2-32EPS"] = new method(fileName, "2011 Data IsoEle32 EPS", 1, 1, 23, 1, "E", "L", "treeV2","probePt>30. && TMath::Abs(probeEta)<2.1 && run>161176 && run<=167913");
//   
//   fileName=inputPath428+"/naf_analyzeZEleEleTagAndProbeRun2011All_HLT_IsoEle27_32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeRun2011All_HLT_IsoEle27_32_IsoEle25TriJet.root";
//   method_["m2-32ApostEPS"] = new method(fileName, "2011 Data IsoEle32 A post EPS", 1, 1, 24, 1, "E", "L", "treeV2","probePt>30. && TMath::Abs(probeEta)<2.1 && run>167913 && run<=175570");
//   
//   fileName=inputPath428+"/naf_analyzeZEleEleTagAndProbeRun2011All_HLT_IsoEle27_32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeRun2011All_HLT_IsoEle27_32_IsoEle25TriJet.root";
//   method_["m2-32B"] = new method(fileName, "2011 Data IsoEle32 B", 1, 1, 25, 1, "E", "L", "treeV2","probePt>30. && TMath::Abs(probeEta)<2.1 && run>175570 && run<=178380");
//   
//   fileName=inputPath428+"/naf_analyzeZEleEleTagAndProbeRun2011All_HLT_IsoEle27_32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeRun2011All_HLT_IsoEle27_32_IsoEle25TriJet.root";
//   method_["m2-32WP70B"] = new method(fileName, "2011 Data IsoEle32WP70 B", 1, 1, 26, 1, "E", "L", "treeV2","probePt>30. && TMath::Abs(probeEta)<2.1 && run>178380");
  
  
  /// subtrigger method on jet PD:
  
  fileName=inputPath428+"/naf_analyzeCrossTriggerRatiosMCFall11ttbar_Jet110_IsoEle25SubBit_cfg/analyzeCrossTriggerRatiosMCFall11_Jet110_IsoEle25.root";
  method_["refTr1MCJet110"] = new method(fileName, "MC ttbar Jet110 CiC IsoEle25", 1, 2, 1, 1, "E same", "LP","treeV2","","");
  
  fileName=inputPath428+"/naf_Fall11MC_Jet_IsoEle25SubBit_OldWP70eID/analyzeCrossTriggerRatiosMCFall11_Jet110_IsoEle25.root";
  method_["refTr1MCJet110WP70"] = new method(fileName, "MC ttbar Jet110 WP70 IsoEle25", 2, 2, 1, 1, "E same", "LP","treeV2","","");
  
  fileName=inputPath428+"/naf_Fall11MC_Jet_IsoEle25SubBit_OldWP70eID_TrigMatch/analyzeCrossTriggerRatiosMCFall11_Jet110_IsoEle25.root";
  method_["refTr1MCJet110WP70TrigMatch"] = new method(fileName, "MC ttbar Jet110 WP70 TrigMatch IsoEle25", 4, 2, 1, 1, "E same", "LP","treeV2","","");
  
  fileName=inputPath428+"/naf_Fall11MC_Jet_IsoEle25SubBit_CiCeID_TrigMatch/analyzeCrossTriggerRatiosMCFall11_Jet110_IsoEle25.root";
  method_["refTr1MCJet110CiCTrigMatch"] = new method(fileName, "MC ttbar Jet110 CiC TrigMatch IsoEle25", 5, 2, 1, 1, "E same", "LP","treeV2","","");
  
  fileName=inputPath428+"/naf_analyzeCrossTriggerRatiosMCFall11ttbar_All_IsoEle25SubBit_cfg/analyzeCrossTriggerRatiosMCFall11_All_IsoEle25TriJet.root";
  method_["refTr1MCAll"] = new method(fileName, "MC ttbar all IsoEle25", 3, 2, 1, 1, "E same", "LP","treeV2","","");
  
  fileName=inputPath428+"/naf_analyzeCrossTriggerRatiosRun2011APromptRecoV4_Jet_Ele25SubBit_cfg/analyzeCrossTriggerRatiosRun2011APromptRecoV4_165088_165633_Trig1_Jet_Ele25TriJet.root";
  method_["refTr1"] = new method(fileName, "Run PromptV4 Ele25", 2, 4, 20, 4, "E same", "LP","treeV2","","");
  
  fileName=inputPath42+"/naf_analyzeCrossTriggerRatiosRun2011APromptRecoV4_Jet_Ele25SubBit_cfg/analyzeCrossTriggerRatiosRun2011APromptRecoV4_165088_165633_Trig1_Jet_Ele25TriJet.root";
  method_["refTr1424"] = new method(fileName, "Run PromptV4 Ele25", 2, 4, 21, 4, "E same", "LP","treeV2","","");
  
  fileName=inputPath428+"/naf_analyzeCrossTriggerRatiosRun2011All_Jet_IsoEle25SubBit_cfg/analyzeCrossTriggerRatiosRun2011All_165970_180252_Trig2_Jet_IsoEle25TriJet.root";
  method_["refTr2"] = new method(fileName, "2011 all IsoEle25", 2, 8, 21, 8, "E same", "LP","treeV2","","");
  
  fileName=inputPath428+"/naf_analyzeCrossTriggerRatiosRun2011All_Jet_IsoEle25SubBit_cfg/analyzeCrossTriggerRatiosRun2011All_165970_180252_Trig2_Jet_IsoEle25TriJet.root";
  method_["refTr2EPS"] = new method(fileName, "2011 EPS IsoEle25", 2, 8, 22, 8, "E same", "LP","treeV2","runNumber<=167913 && runNumber>=165970","");
  
  fileName=inputPath428+"/naf_analyzeCrossTriggerRatiosRun2011APromptRecoV4_Jet_IsoEle25SubBit_cfg/analyzeCrossTriggerRatiosRun2011APromptRecoV4_165970_167913_Trig2_Jet_IsoEle25TriJet.root";
  method_["refTr2EPSnew"] = new method(fileName, "2011 EPS CiC IsoEle25", 1, 8, 21, 8, "E same", "LP","treeV2","runNumber<=167913 && runNumber>=165970","");
  
  fileName=inputPath428+"/naf_Jet_IsoEle25SubBit_OldWP70eID/analyzeCrossTriggerRatiosRun2011APromptRecoV4_165970_167913_Trig2_Jet_IsoEle25TriJet.root";
  method_["refTr2EPSnewWP70"] = new method(fileName, "2011 EPS WP70 IsoEle25", 1, 1, 22, 1, "E same", "LP","treeV2","runNumber<=167913 && runNumber>=165970","");
  
  fileName=inputPath428+"/naf_Jet_IsoEle25SubBit_OldWP70eID_TrigMatch/analyzeCrossTriggerRatiosRun2011APromptRecoV4_165970_167913_Trig2_Jet_IsoEle25TriJet.root";
  method_["refTr2EPSnewWP70TrigMatch"] = new method(fileName, "2011 EPS new WP70 TrigMatch IsoEle25", 2, 1, 21, 1, "E same", "LP","treeV2","runNumber<=167913 && runNumber>=165970","");
  
  fileName=inputPath428+"/naf_Jet_IsoEle25SubBit_CiCeID_TrigMatch/analyzeCrossTriggerRatiosRun2011APromptRecoV4_165970_167913_Trig2_Jet_IsoEle25TriJet.root";
  method_["refTr2EPSCiCTrigMatch"] = new method(fileName, "2011 EPS CiC TrigMatch IsoEle25", 2, 1, 22, 1, "E same", "LP","treeV2","runNumber<=167913 && runNumber>=165970","");
  
  fileName=inputPath428+"/naf_analyzeCrossTriggerRatiosRun2011All_Jet_IsoEle25SubBit_cfg/analyzeCrossTriggerRatiosRun2011All_165970_180252_Trig2_Jet_IsoEle25TriJet.root";
  method_["refTr2postEPS"] = new method(fileName, "2011 postEPS IsoEle25", 2, 8, 23, 8, "E same", "LP","treeV2","runNumber>167913","");
  
  fileName=inputPath42+"/naf_analyzeCrossTriggerRatiosRun2011APromptRecoV4_Jet_IsoEle25SubBit_cfg/analyzeCrossTriggerRatiosRun2011APromptRecoV4_165970_167913_Trig2_Jet_IsoEle25TriJet.root";
  method_["refTr2EPS424"] = new method(fileName, "Run PromptV4 IsoEle25", 2, 8, 25, 8, "E same", "LP","treeV2","TMath::Abs(eta)<2.1","");
  

  
  /// different tap studies (different efficiencies)

//    const int folderNum=6;
//    TString folderID[]={"tapTrkQEle", "tapIDEle", "tapIsoEle", "tapConvRejEle", "tapTotalSelectionEle", "tapTriggerEle"};
//    TString foldersTitle[]={"Track Quality", "ID", "Isolation", "Conversion Rejection", "Overall Selection", "Trigger"};
   
//    const int folderNum=2;
//    TString folderID[]={"tapTotalSelectionEle", "tapTriggerEle"};
//    TString foldersTitle[]={"Overall Selection", "Trigger"};
  
//   const int folderNum=1;
//   TString folderID[]={"tapTotalSelectionEle"};
//   TString foldersTitle[]={"Overall Selection"};
  
  const int folderNum=1;
  TString folderID[]={"tapTriggerEle"};
  TString foldersTitle[]={"Trigger"};
  
//   const int folderNum=1;
//     /// to combine selection and trigger efficiencies use tapAll:
//   TString folderID[]={"tapAllEle"};
//   TString foldersTitle[]={"Combined Selection and Trigger"};
  
//   const int folderNum=1;
//   TString folderID[]={"tapTrigger"};
//   TString foldersTitle[]={"Trigger"};
  
  /// for reference trigger method:
  TString folderIDrefTriggerPass="analyzeElectronKinematicsTrig2";
  TString folderIDrefTriggerAll="analyzeElectronKinematicsTrig1";


  /// effName = name of the effHisto; variables: corresponding variable to effName; cuts: corresponding cut to effName

  //TString effIDarr[]      = {"Control", "Pt", "Eta", "RelIso", "PVMult", "Mult", "MinDR","lepLepMass"};
  //TString effIDarr[]      = {"Control", "Pt", "Eta", "RelIso", "PVMult", "Mult", "PtEta0to1p5", "PtEta1p5to2p1"};
  //TString effIDarr[]      = {"Pt", "Eta", "RelIso", "PVMult", "Mult", "MinDR"};
  //TString effIDarr[]      = {"Pt"};
  TString effIDarr[]      = {"Pt", "Eta"};
  std::vector<TString> effID(effIDarr, effIDarr + sizeof(effIDarr)/sizeof(TString));
  int effIDNum = effID.size();
  std::cout<< "Number of considered plots: " <<  effIDNum << std::endl;
  
  
  TString effIDarr2[]      = {};
  //TString effIDarr2[]      = {"PtEta0to1p2", "PtEta1p2to2p1", "EtaPt30to45", "EtaPt45to60", "EtaPtGreater60", "PtMedian", "Pt3bins"};
  std::vector<TString> effID2(effIDarr2, effIDarr2 + sizeof(effIDarr2)/sizeof(TString));
  int effIDNum2 = effID2.size();
  std::cout<< "Number of considered plots 2: " <<  effIDNum2 << std::endl;
    
  /// map with structure that keeps features of histograms
  std::map<TString, std::map<TString, eff*> > eff_;
  
  /// title for histo, x and y axis (separated by "/")
  TString title0 ="";
  TString title ="";
  
  /// axis range
  //double yLo = 0.5, yHi = 1.1;
  double yLo = 0.8, yHi = 1.;
  double yLoSF = 0.9, yHiSF = 1.1;
  
  /// Constructor for struct eff(TString iniVar, T  iniCuts, TString iniBins, TString iniTitles, double iniYLo=-9999., double iniYHi=-9999., double iniXLo=-9999., double iniXHi=-9999.)
  TCut cutPt  = ""; /*"(probePt>30. || testPt>30. )";*/
  TCut cutEta = ""; /*"(TMath::Abs(probeEta)<2.1 || TMath::Abs(testEta)<2.1)";*/
  TCut cutPtEta = cutPt && cutEta;
  for(int iFolder=0; iFolder < folderNum; iFolder++){
    title = foldersTitle[iFolder]+" Efficiency/ / ";
    eff_["Control"][folderID[iFolder]]        =new eff("Control", cutPtEta, mBinsControl, binsControl_, title, yLo, yHi, -9999.,-9999.);
    title = foldersTitle[iFolder]+" Efficiency/p_{T} [GeV]/ ";
    eff_["Pt"][folderID[iFolder]]             =new eff("Pt", cutEta, mBinsPt, binsPtAN_, title, yLo, yHi, 30.,200.);
//     eff_["Pt"][folderID[iFolder]]             =new eff("Pt", cutEta, mBinsPt, binsPt_, title, yLo, yHi, 30.,200.);
    title = foldersTitle[iFolder]+" Efficiency/#eta/ ";
    eff_["Eta"][folderID[iFolder]]             =new eff("Eta", cutPt, mBinsEta, binsEta_, title, yLo, yHi);
//     eff_["Eta"][folderID[iFolder]]             =new eff("Eta", cutPt, mBinsEta, binsEtaEle_, title, yLo, yHi);
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
    
    title = foldersTitle[iFolder]+" Efficiency, 0<#eta<1.2/p_{T} [GeV]/ ";
    eff_["PtEta0to1p2"][folderID[iFolder]]             =new eff("Pt", "TMath::Abs(probeEta)<1.2", mBinsPt, binsPt_, title, yLo, yHi, 30.,200.);
    
    title = foldersTitle[iFolder]+" Efficiency 1.2<#eta<2.1/p_{T} [GeV]/ ";
    eff_["PtEta1p2to2p1"][folderID[iFolder]]             =new eff("Pt", "TMath::Abs(probeEta)>1.2 && TMath::Abs(probeEta)<2.1", mBinsPt, binsPt_, title, yLo, yHi, 30.,200.,true);
    
    title = foldersTitle[iFolder]+" Efficiency, 30<p_{T}<45/#eta/ ";
    eff_["EtaPt30to45"][folderID[iFolder]]             =new eff("Eta", "probePt>30. && probePt<45.", mBinsEta, binsEta_, title, yLo, yHi);
    
    title = foldersTitle[iFolder]+" Efficiency, 45<p_{T}<60/#eta/ ";
    eff_["EtaPt45to60"][folderID[iFolder]]             =new eff("Eta", "probePt>45. && probePt<60.", mBinsEta, binsEta_, title, yLo, yHi);
    
    title = foldersTitle[iFolder]+" Efficiency, 60<p_{T}/#eta/ ";
    eff_["EtaPtGreater60"][folderID[iFolder]]             =new eff("Eta", "probePt>60.", mBinsEta, binsEta_, title, yLo, yHi);
    
    title = foldersTitle[iFolder]+" Efficiency AN/p_{T} [GeV]/ ";
    eff_["PtAN"][folderID[iFolder]]             =new eff("Pt", cutEta, mBinsPt, binsPtAN_, title, yLo, yHi, 30.,200.);
    
    title = foldersTitle[iFolder]+" Efficiency Median/p_{T} [GeV]/ ";
    eff_["PtMedian"][folderID[iFolder]]             =new eff("Pt", cutEta, mBinsPt, binsPtMedian_, title, yLo, yHi, 30.,200.);
    
    title = foldersTitle[iFolder]+" Efficiency 3 bins/p_{T} [GeV]/ ";
    eff_["Pt3bins"][folderID[iFolder]]             =new eff("Pt", cutEta, mBinsPt, binsPt3bins_, title, yLo, yHi, 30.,200.);
  }

  /// ---
  /// get efficiencies from tree or histo
  ///  ---
  for(int iMethod=0; iMethod<mIDNum; iMethod++){
    for(int iEff=0; iEff<effIDNum; iEff++){
      for(int iFolder=0; iFolder<folderNum; iFolder++){
	if(!mID[iMethod].Contains("refTr")) getEfficiencies(eff_[effID[iEff]][folderID[iFolder]], method_[mID[iMethod]], mID[iMethod], folderID[iFolder], folderID[iFolder]);
	else                               getEfficiencies(eff_[effID[iEff]][folderID[iFolder]], method_[mID[iMethod]], mID[iMethod], folderIDrefTriggerPass, folderIDrefTriggerAll);
      }
    }
      
    for(int iEff=0; iEff<effIDNum2; iEff++){
      for(int iFolder=0; iFolder<folderNum; iFolder++){
	getEfficiencies(eff_[effID2[iEff]][folderID[iFolder]], method_[mID[iMethod]], mID[iMethod], folderID[iFolder], folderID[iFolder]);
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
  
  TCanvas* CanvComp2 [folderNum];
  TCanvas* CanvSFComp2 [folderNum];

  std::cout<< "Drawing eff. and SF"<<std::endl;
  for(int iFolder=0; iFolder<folderNum; iFolder++) {

    CanvComp[iFolder] = new TCanvas("Comparison"+folderID[iFolder], "Comparison"+folderID[iFolder], 1700,1000);
    CanvSFComp[iFolder] = new TCanvas("ComparisonSF"+folderID[iFolder], "ComparisonSF"+folderID[iFolder], 1700,1000);
    CanvEvtsComp[iFolder] = new TCanvas("ComparisonEvts"+folderID[iFolder], "ComparisonEvts"+folderID[iFolder], 1700,1000);
    CanvEvtsNormComp[iFolder] = new TCanvas("ComparisonEvtsNorm"+folderID[iFolder], "ComparisonEvtsNorm"+folderID[iFolder], 1700,1000);
    
    CanvComp2[iFolder] = new TCanvas("Comparison2"+folderID[iFolder], "Comparison2"+folderID[iFolder], 1700,1000);
    CanvSFComp2[iFolder] = new TCanvas("ComparisonSF2"+folderID[iFolder], "ComparisonSF2"+folderID[iFolder], 1700,1000);
    
    CanvComp[iFolder]->Divide(4,2);
    CanvSFComp[iFolder]->Divide(4,2);
    CanvEvtsComp[iFolder]->Divide(4,2);
    CanvEvtsNormComp[iFolder]->Divide(4,2);
    
    CanvComp2[iFolder]->Divide(4,2);
    CanvSFComp2[iFolder]->Divide(4,2);
  
    for(int iEff=0; iEff<effIDNum; iEff++){
      CanvComp[iFolder]->cd(iEff+1);
//       CanvComp[iFolder]->cd(iEff+1)->SetGrid(1,1);
      std::cout<< "Drawing eff."<<std::endl;
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
    
    for(int iEff=0; iEff<effIDNum2; iEff++){
      CanvComp2[iFolder]->cd(iEff+1);
//       CanvComp[iFolder]->cd(iEff+1)->SetGrid(1,1);
      std::cout<< "Drawing eff. 2"<<std::endl;
      drawEfficiencies(eff_[effID2[iEff]][folderID[iFolder]], method_, mID, 0.15,0.15,0.9,0.45,eff_[effID2[iEff]][folderID[iFolder]]->drawLegend);
      CanvSFComp2[iFolder]->cd(iEff+1);
      std::cout<< "Drawing SF"<<std::endl;
      drawSF          (eff_[effID2[iEff]][folderID[iFolder]], method_, mID, mIDnorm, 0.15,0.15,0.9,0.45,eff_[effID2[iEff]][folderID[iFolder]]->drawLegend, yLoSF, yHiSF, eff_[effID2[iEff]][folderID[iFolder]]->xLo, eff_[effID2[iEff]][folderID[iFolder]]->xHi);
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
	
	for(int iEff=0; iEff<effIDNum2; iEff++){
	  CanvComp  [iFolder]->cd(iEff+1)->Print(outputFolder+outputFileName+folderID[iFolder]+"_"+effID2[iEff]+"."+fileFormat[iFileFormat]);
	  CanvSFComp[iFolder]->cd(iEff+1)->Print(outputFolder+outputFileName+folderID[iFolder]+"_SF_"+effID2[iEff]+"."+fileFormat[iFileFormat]);
	}
	
	if(iFolder==0) CanvLeg->Print(outputFolder+outputFileName+"_Legend."+fileFormat[iFileFormat]);
	std::cout<<"Canvas with plots is saved in "<<outputFolder<<std::endl;
      }
      /// save graph in root file
//       TFile f("MuonEffSF2011.root", "new");
//       eff_["Eta"]["tapAll"]->graphSF["m2"]->SetName("tapAllSFeta");
//       //eff_["Eta"]["tapAll"]->graphSF["m2"]->SetTitle("tapAllSFeta");
//       eff_["Eta"]["tapAll"]->graphSF["m2"]->Write();
//       std::cout<<"MuonEffSF.root with TGraphErrors is saved in "<<outputFolder<<std::endl;
    }
  }
  std::cout<< "Done"<<std::endl;
}
