#include "basicFunctions.h"
#include "../../unfolding/TopSVDFunctions.h" 
#include "../../unfolding/TopSVDFunctions.C" 

void analyzeHypothesisKinFit(double luminosity = 1143.22, bool save = true, int systematicVariation=sysNo, unsigned int verbose=0, TString inputFolderName="RecentAnalysisRun",
			     //TString dataFile= "/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/analyzeDiffXData2011A_Electron_160404_167913.root",
			     TString dataFile= "/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/analyzeDiffXData2011A_Muon_160404_167913.root",
			     std::string decayChannel = "muon", bool SVDunfold=true)
{
  // ============================
  //  Set ROOT Style
  // ============================
 
  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  TGaxis::SetMaxDigits(2);
  myStyle.cd();
  gROOT->SetStyle("HHStyle");
  gROOT->ForceStyle();	
  
  // ============================
  //  Name Conventions
  // ============================
  // a) enumerator sample convention (as defined in basicFunctions.h)
  //    kSig,    kBkg,    kZjets,  kWjets, 
  //    kQCD,    kSTop,   kDiBos,  kData, 
  //    kQCDEM1, kQCDEM2, kQCDEM3, kQCDBCE1, kQCDBCE2, kQCDBCE3,  
  //    kWW,     kWZ,     kZZ, 
  //    kSTops,  kSATops, kSTopt,  kSATopt,  kSToptW , kSAToptW};

  // b) file name convention (implemented in basicFunctions.h)
  //    "muonDiffXSec"+sampleName+GeneratorName+GeneratorTune+MCProductionCycle+systematicVariation+"PF.root"
  //    GeneratorName= "Mad", "Pythia6"
  //    GeneratorTune= "Z2", "D6T"
  //    MCProductionCycle= "Summer11"

  // ============================
  //  Options
  // ============================
  //
  // a) options directly entered when calling function
  //    systematicVariation: which systematic shift do you want to make? from basicFunctions.h:  
  //
  //  0: noSys                                                      
  //  1: sysLumiUp                   2: sysLumiDown                               
  //  3: sysPUUp                     4: sysPUDown                   
  //  5: sysJESUp                    6: sysJESDown                  
  //  7: sysJERUp                    8: sysJERDown                  
  //  9: sysTrigEffSFNormUp         10: sysTrigEffSFNormDown         
  // 11: sysTriggerEffSFShapeUpEta  12: sysTriggerEffSFShapeDownEta 
  // 13: sysTriggerEffSFShapeUpPt   14: sysTriggerEffSFShapeDownPt  
  // 15: sysMuEffSFUp               16: sysMuEffSFDown              
  // 17: sysBtagSFShapeUpPt65       18: sysBtagSFShapeDownPt65  
  // 19: sysBtagSFShapeUpEta0p7     20: sysBtagSFShapeDownEta0p7
  // 21: sysMisTagSFUp              22: sysMisTagSFDown             
  // 23: sysTopScaleUp              24: sysTopScaleDown             
  // 25: sysVBosonScaleUp           26: sysVBosonScaleDown           
  // 27: sysSingleTopScaleUp        28: sysSingleTopScaleDown       
  // 29: sysTopMatchUp              20: sysTopMatchDown             
  // 31: sysVBosonMatchUp           32: sysVBosonMatchDown          
  // 33: sysTopMassUp               34: sysTopMassDown              
  // 35: sysQCDUp                   36: sysQCDDown                  
  // 37: sysSTopUp                  38: sysSTopDown                 
  // 39: sysDiBosUp                 40: sysDiBosDown                
  // 41: sysPDFUp                   42: sysPDFDown                  
  // 43: sysHadUp                   44: sysHadDown                  
  // 45: sysShapeUp                 46: sysShapeDown                
  // 47: ENDOFSYSENUM
  
  if(luminosity<40.&&systematicVariation==sysLumiUp  )      luminosity*=1.04;
  else if(luminosity<40.&&systematicVariation==sysLumiDown) luminosity*=0.96;
  if(luminosity>40.&&systematicVariation==sysLumiUp  )      luminosity*=1.045;
  else if(luminosity>40.&&systematicVariation==sysLumiDown) luminosity*=0.955;
  // verbose: set detail level of output 
  // 0: no output, 1: std output 2: more output 3: output for debugging
  // data file: relative path of .root file
  // save: save plots?
  // SVDunfold: use SVD instead of bin to bin unfolding
  // compare SVD and BBB results
  bool compare=false;
  if(!SVDunfold) compare=false;
  // luminosity: [/pb]
  TString lumi = getTStringFromInt(roundToInt((luminosity), false));  
  // b) options to be configured only once
  // get the .root files from the following folder:
  TString inputFolder = "/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName;
  // see if its 2010 or 2011 data from luminosity
  TString dataSample="";
  if(luminosity<50) dataSample="2010";
  if(luminosity>50) dataSample="2011";
  // save all plots into the following folder
  TString outputFolder = "./diffXSecFromSignal/plots/"+decayChannel+"/";
  if(dataSample!="") outputFolder+=dataSample+"/";
  // save all plots within a root file named:
  TString outputFileName="diffXSecTopSemi";
  if(decayChannel=="muon"    ) outputFileName+="Mu";
  if(decayChannel=="electron") outputFileName+="Elec";
  outputFileName+=dataSample+".root";
  // choose name of the output .pdf file
  TString pdfName="kinFitHypothesis"+lumi+"pb";
  // choose if differential xSecs are extrapolated to whole phase space
  bool extrapolate=false;
  TString PS="";
  if(!extrapolate)PS="PhaseSpace";
  // choose plot input folder corresponding to systematic Variation  
  TString sysInputFolderExtension="";
  TString sysInputGenFolderExtension="";
  // create list of variables you would like to create the efficiency / cross section for
  std::vector<TString> xSecVariables_, xSecLabel_;
  TString xSecVariables[] ={"topPt", "topY", "ttbarPt", "ttbarMass", "ttbarY", "lepPt" ,"lepEta", "bqPt", "bqEta"};
  TString xSecLabel    [] ={"p_{T}^{t and #bar{t}}/[#frac{GeV}{c}]" , "y^{t and #bar{t}}/ ", "p_{T}^{t#bar{t}}/[#frac{GeV}{c}]", "m_{t#bar{t}}/[#frac{GeV}{c^{2}}]", "y^{t#bar{t}}/ ", "p_{T}^{#mu}/[#frac{GeV}{c}]" , "#eta^{#mu}/ ", "p_{T}^{b and #bar{b}}/[#frac{GeV}{c}]" , "#eta^{b and #bar{b}}/ "};
  xSecVariables_ .insert( xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString) );
  xSecLabel_     .insert( xSecLabel_    .begin(), xSecLabel    , xSecLabel     + sizeof(xSecLabel    )/sizeof(TString) );

  switch (systematicVariation)
  {
    case sysPUUp                     : sysInputFolderExtension="PUup";   sysInputGenFolderExtension=sysInputFolderExtension; break;
    case sysPUDown                   : sysInputFolderExtension="PUdown"; sysInputGenFolderExtension=sysInputFolderExtension; break;
    case sysTrigEffSFNormUp          : sysInputFolderExtension="TriggerEffSFNormUp";        break;
    case sysTrigEffSFNormDown        : sysInputFolderExtension="TriggerEffSFNormDown";      break;
    case sysTriggerEffSFShapeUpEta   : sysInputFolderExtension="TriggerEffSFShapeUpEta";    break;
    case sysTriggerEffSFShapeDownEta : sysInputFolderExtension="TriggerEffSFShapeDownEta";  break;
    case sysTriggerEffSFShapeUpPt    : sysInputFolderExtension="TriggerEffSFShapeUpPt";     break;
    case sysTriggerEffSFShapeDownPt  : sysInputFolderExtension="TriggerEffSFShapeDownPt";   break;
 // case sysTriggerEffSFShapeUpPt40  : sysInputFolderExtension="TriggerEffSFShapeUpPt40";   break;
 // case sysTriggerEffSFShapeDownPt40: sysInputFolderExtension="TriggerEffSFShapeUpPt40";   break;
    case sysMuEffSFUp                : sysInputFolderExtension="SelectionEffSFNormUp";      break;
    case sysMuEffSFDown              : sysInputFolderExtension="SelectionEffSFNormDown";    break;
 // case sysBtagSFUp                 : sysInputFolderExtension="BtagSFup";                  break;
 // case sysBtagSFDown               : sysInputFolderExtension="BtagSFdown";                break;
 // case sysBtagSFShapeUpPt100       : sysInputFolderExtension="BTagSFShapeUpPt100";        break;
 // case sysBtagSFShapeDownPt100     : sysInputFolderExtension="BTagSFShapeDownPt100";      break;
 // case sysBtagSFShapeUpEta1p2      : sysInputFolderExtension="BTagSFShapeUpEta1p2";       break;
 // case sysBtagSFShapeDownEta1p2    : sysInputFolderExtension="BTagSFShapeDownEta1p2";     break;
    case sysBtagSFShapeUpPt65        : sysInputFolderExtension="BTagSFShapeUpPt65";         break;
    case sysBtagSFShapeDownPt65      : sysInputFolderExtension="BTagSFShapeDownPt65";       break;
    case sysBtagSFShapeUpEta0p7      : sysInputFolderExtension="BTagSFShapeUpEta0p7";       break;
    case sysBtagSFShapeDownEta0p7    : sysInputFolderExtension="BTagSFShapeDownEta0p7";     break;
    case sysMisTagSFUp               : sysInputFolderExtension="MisTagSFup";                break;
    case sysMisTagSFDown             : sysInputFolderExtension="MisTagSFdown";              break;
    default: break;
  }

  // additional (control plot folders): NoWeight, OnlyPUWeight, NoBtagSFWeight;

  //  ---
  //     choose plots
  //  ---
  // a) list plots you would like to see ("folder/plotName") - same as in .root files (for 1D and 2D)
  TString plots1D[ ] = { // general fit performance
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/prob"       , 
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/chi2"       , 
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/delChi2"    ,
    // reconstructed top quantities
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topMass"    ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPt"      ,                         
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPhi"     ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topY"       ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPtHad"   ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPhiHad"  ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topYHad"    ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPtLep"   ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPhiLep"  ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topYLep"    ,
    // generated top quantities
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topMass"      , 
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topPt"        ,    
    "analyzeTopPartonLevelKinematicsPhaseSpace"+sysInputGenFolderExtension+"/topPt", 
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topPhi"       ,
    "analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/topY",
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topPtHad"     ,
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topPhiHad"    ,
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topYHad"      ,
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topPtLep"     ,
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topPhiLep"    ,
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topYLep"      ,
    // reconstructed ttbar quantities
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarMass"  ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarPt"    ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarY"     ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarHT"    ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarSumY"  ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarDelPhi",
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarDelY"  ,
    // generated ttbar quantities
    "analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/ttbarMass",
    "analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/ttbarPt"  ,
    "analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/ttbarY"   ,
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/ttbarHT"    ,
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/ttbarSumY"  ,
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/ttbarDelPhi",
    "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/ttbarDelY"  ,
    // reconstructed lepton quantities
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/lepPt" ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/lepEta",
    // generated lepton quantities
    "analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/lepPt" ,
    "analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/lepEta",
    // reconstructed b-quark quantities
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/bqPt",
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/bqEta",
    // generated b-quark quantities
    "analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/bqPt",
    "analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/bqEta"
  };
 TString plots1Dadd[ ] = {
   // generated angular distributions
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/bbbarAngle"   ,
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/bbbarAngleTtRF",
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/WWAngle"     ,
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topWAngleLep",
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topWAngleHad",
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topBAngleLep",
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topBAngleHad",
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/bWAngleLep"  ,
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/bWAngleHad"  ,
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/qqbarAngle"  ,
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/qBlepAngle"  ,
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/qBhadAngle"  ,
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/lepBlepAngle",
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/lepBlepAngleTtRF",
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/lepBhadAngle",
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/lepQAngle"   ,
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/MuonNeutrinoAngle",
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/lepBNeutrinoAngle",
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/hadBNeutrinoAngle",
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/qNeutrinoAngle"   ,
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/lepWDir"     ,
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/qWDir"       ,
   "analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/nuWDir"      ,
   // reconstructed angular distributions
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/bbbarAngle"  ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/bbbarAngleTtRF",
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/WWAngle"     ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topWAngleLep",
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topWAngleHad",
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topBAngleLep",
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topBAngleHad",
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/bWAngleLep"  ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/bWAngleHad"  ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/qqbarAngle"  ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/qBlepAngle"  ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/qBhadAngle"  ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/lepBlepAngle",
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/lepBlepAngleTtRF",
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/lepBhadAngle",
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/lepQAngle"   ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/MuonNeutrinoAngle",
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/lepBNeutrinoAngle",
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/hadBNeutrinoAngle",
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/qNeutrinoAngle"   ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/lepWDir"     ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/nuWDir"      ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/qWDir"       ,
   // reconstructed event shape variables
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/aplanarity" ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/sphericity" ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/C"          ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/D"          ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/circularity",
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/isotropy"   ,
   // combinatorics and Kinfit Hypothesis Quality(ttbar signal only)
   "analyzeHypoKinFit/hadBQuark"               , 
   "analyzeHypoKinFit/lepBQuark"               , 
   "analyzeHypoKinFit/lightQuark"              , 
   "analyzeHypoKinFit/wrongAssign"             ,
   "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/qAssignment",
   "analyzeHypoKinFit/PartonJetDRall"          ,
   // pull distributions top quantities
   "analyzeHypoKinFit/hadBQuarkPt"             ,
   "analyzeHypoKinFit/hadBQuarkEta"            ,
   "analyzeHypoKinFit/hadBQuarkPhi"            ,
   "analyzeHypoKinFit/lepBQuarkPt"             ,
   "analyzeHypoKinFit/lepBQuarkEta"            ,
   "analyzeHypoKinFit/lepBQuarkPhi"            ,
   "analyzeHypoKinFit/lightQuarkPt"            ,
   "analyzeHypoKinFit/lightQuarkEta"           ,
   "analyzeHypoKinFit/lightQuarkPhi"           ,
   "analyzeHypoKinFit/leptonPt"                ,
   "analyzeHypoKinFit/leptonEta"               ,
   "analyzeHypoKinFit/leptonPhi"               ,
   "analyzeHypoKinFit/neutrinoPt"              ,
   "analyzeHypoKinFit/neutrinoEta"             ,
   "analyzeHypoKinFit/neutrinoPhi"             ,
   "analyzeHypoKinFit/lepWPt"                  ,
   "analyzeHypoKinFit/lepWEta"                 ,
   "analyzeHypoKinFit/lepWPhi"                 ,
   "analyzeHypoKinFit/hadWPt"                  ,
   "analyzeHypoKinFit/hadWEta"                 ,
   "analyzeHypoKinFit/hadWPhi"                 ,
   // pull distributions input objects before/after kinematic fit
   // (i) lepton
   "analyzeHypoKinFitLepton/leptonPullPtKinFitRec",
   "analyzeHypoKinFitLepton/leptonPullPtKinFitPartonTruth",
   "analyzeHypoKinFitLepton/leptonPullPtRecPartonTruth",
   "analyzeHypoKinFitLepton/leptonPullEtaKinFitRec",
   "analyzeHypoKinFitLepton/leptonPullEtaKinFitPartonTruth",
   "analyzeHypoKinFitLepton/leptonPullEtaRecPartonTruth",
   "analyzeHypoKinFitLepton/leptonPullPhiKinFitRec",
   "analyzeHypoKinFitLepton/leptonPullPhiKinFitPartonTruth",
   "analyzeHypoKinFitLepton/leptonPullPhiRecPartonTruth",
   "analyzeHypoKinFitLeptonCorr/leptonPullPtKinFitRec",
   "analyzeHypoKinFitLeptonCorr/leptonPullPtKinFitPartonTruth",
   "analyzeHypoKinFitLeptonCorr/leptonPullPtRecPartonTruth",
   "analyzeHypoKinFitLeptonCorr/leptonPullEtaKinFitRec",
   "analyzeHypoKinFitLeptonCorr/leptonPullEtaKinFitPartonTruth",
   "analyzeHypoKinFitLeptonCorr/leptonPullEtaRecPartonTruth",
   "analyzeHypoKinFitLeptonCorr/leptonPullPhiKinFitRec",
   "analyzeHypoKinFitLeptonCorr/leptonPullPhiKinFitPartonTruth",
   "analyzeHypoKinFitLeptonCorr/leptonPullPhiRecPartonTruth",
   // (ii) neutrino
   "analyzeHypoKinFitMET/neutrinoPullPtKinFitRec",
   "analyzeHypoKinFitMET/neutrinoPullPtKinFitPartonTruth",
   "analyzeHypoKinFitMET/neutrinoPullPtRecPartonTruth",
   "analyzeHypoKinFitMET/neutrinoPullEtaKinFitRec",
   "analyzeHypoKinFitMET/neutrinoPullEtaKinFitPartonTruth",
   "analyzeHypoKinFitMET/neutrinoPullEtaRecPartonTruth",
   "analyzeHypoKinFitMET/neutrinoPullPhiKinFitRec",
   "analyzeHypoKinFitMET/neutrinoPullPhiKinFitPartonTruth",
   "analyzeHypoKinFitMET/neutrinoPullPhiRecPartonTruth",
   "analyzeHypoKinFitMETCorr/neutrinoPullPtKinFitRec",
   "analyzeHypoKinFitMETCorr/neutrinoPullPtKinFitPartonTruth",
   "analyzeHypoKinFitMETCorr/neutrinoPullPtRecPartonTruth",
   "analyzeHypoKinFitMETCorr/neutrinoPullEtaKinFitRec",
   "analyzeHypoKinFitMETCorr/neutrinoPullEtaKinFitPartonTruth",
   "analyzeHypoKinFitMETCorr/neutrinoPullEtaRecPartonTruth",
   "analyzeHypoKinFitMETCorr/neutrinoPullPhiKinFitRec",
   "analyzeHypoKinFitMETCorr/neutrinoPullPhiKinFitPartonTruth",
   "analyzeHypoKinFitMETCorr/neutrinoPullPhiRecPartonTruth",
   // (iii) hadronic b jet
   "analyzeHypoKinFitJets/hadBQuarkPullPtKinFitRec",
   "analyzeHypoKinFitJets/hadBQuarkPullPtKinFitPartonTruth",
   "analyzeHypoKinFitJets/hadBQuarkPullPtRecPartonTruth",
   "analyzeHypoKinFitJets/hadBQuarkPullEtaKinFitRec",
   "analyzeHypoKinFitJets/hadBQuarkPullEtaKinFitPartonTruth",
   "analyzeHypoKinFitJets/hadBQuarkPullEtaRecPartonTruth",
   "analyzeHypoKinFitJets/hadBQuarkPullPhiKinFitRec",
   "analyzeHypoKinFitJets/hadBQuarkPullPhiKinFitPartonTruth",
   "analyzeHypoKinFitJets/hadBQuarkPullPhiRecPartonTruth",
   "analyzeHypoKinFitJetsCorr/hadBQuarkPullPtKinFitRec",
   "analyzeHypoKinFitJetsCorr/hadBQuarkPullPtKinFitPartonTruth",
   "analyzeHypoKinFitJetsCorr/hadBQuarkPullPtRecPartonTruth",
   "analyzeHypoKinFitJetsCorr/hadBQuarkPullEtaKinFitRec",
   "analyzeHypoKinFitJetsCorr/hadBQuarkPullEtaKinFitPartonTruth",
   "analyzeHypoKinFitJetsCorr/hadBQuarkPullEtaRecPartonTruth",
   "analyzeHypoKinFitJetsCorr/hadBQuarkPullPhiKinFitRec",
   "analyzeHypoKinFitJetsCorr/hadBQuarkPullPhiKinFitPartonTruth",
   "analyzeHypoKinFitJetsCorr/hadBQuarkPullPhiRecPartonTruth",
   // (iv) leptonic b jet
   "analyzeHypoKinFitJets/lepBQuarkPullPtKinFitRec",
   "analyzeHypoKinFitJets/lepBQuarkPullPtKinFitPartonTruth",
   "analyzeHypoKinFitJets/lepBQuarkPullPtRecPartonTruth",
   "analyzeHypoKinFitJets/lepBQuarkPullEtaKinFitRec",
   "analyzeHypoKinFitJets/lepBQuarkPullEtaKinFitPartonTruth",
   "analyzeHypoKinFitJets/lepBQuarkPullEtaRecPartonTruth",
   "analyzeHypoKinFitJets/lepBQuarkPullPhiKinFitRec",
   "analyzeHypoKinFitJets/lepBQuarkPullPhiKinFitPartonTruth",
   "analyzeHypoKinFitJets/lepBQuarkPullPhiRecPartonTruth",  
   "analyzeHypoKinFitJetsCorr/lepBQuarkPullPtKinFitRec",
   "analyzeHypoKinFitJetsCorr/lepBQuarkPullPtKinFitPartonTruth",
   "analyzeHypoKinFitJetsCorr/lepBQuarkPullPtRecPartonTruth",
   "analyzeHypoKinFitJetsCorr/lepBQuarkPullEtaKinFitRec",
   "analyzeHypoKinFitJetsCorr/lepBQuarkPullEtaKinFitPartonTruth",
   "analyzeHypoKinFitJetsCorr/lepBQuarkPullEtaRecPartonTruth",
   "analyzeHypoKinFitJetsCorr/lepBQuarkPullPhiKinFitRec",
   "analyzeHypoKinFitJetsCorr/lepBQuarkPullPhiKinFitPartonTruth",
   "analyzeHypoKinFitJetsCorr/lepBQuarkPullPhiRecPartonTruth",
   // (v) light jets
   "analyzeHypoKinFitJets/lightQuarkPullPtKinFitRec",
   "analyzeHypoKinFitJets/lightQuarkPullPtKinFitPartonTruth",
   "analyzeHypoKinFitJets/lightQuarkPullPtRecPartonTruth",
   "analyzeHypoKinFitJets/lightQuarkPullEtaKinFitRec",
   "analyzeHypoKinFitJets/lightQuarkPullEtaKinFitPartonTruth",
   "analyzeHypoKinFitJets/lightQuarkPullEtaRecPartonTruth",
   "analyzeHypoKinFitJets/lightQuarkPullPhiKinFitRec",
   "analyzeHypoKinFitJets/lightQuarkPullPhiKinFitPartonTruth",
   "analyzeHypoKinFitJets/lightQuarkPullPhiRecPartonTruth",
   "analyzeHypoKinFitJetsCorr/lightQuarkPullPtKinFitRec",
   "analyzeHypoKinFitJetsCorr/lightQuarkPullPtKinFitPartonTruth",
   "analyzeHypoKinFitJetsCorr/lightQuarkPullPtRecPartonTruth",
   "analyzeHypoKinFitJetsCorr/lightQuarkPullEtaKinFitRec",
   "analyzeHypoKinFitJetsCorr/lightQuarkPullEtaKinFitPartonTruth",
   "analyzeHypoKinFitJetsCorr/lightQuarkPullEtaRecPartonTruth",
   "analyzeHypoKinFitJetsCorr/lightQuarkPullPhiKinFitRec",
   "analyzeHypoKinFitJetsCorr/lightQuarkPullPhiKinFitPartonTruth",
   "analyzeHypoKinFitJetsCorr/lightQuarkPullPhiRecPartonTruth",
 };


  TString plots2D[ ] = { // reco - gen Match correlation plots (ttbar signal only)
    // a) combinatorics and Kinfit Hypothesis Quality(ttbar signal only)
    "analyzeHypoKinFit/mapKinFit_"                                          ,
    // b) response matrix top quantities
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPt_"      ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPhi_"     ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topY_"       ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/bbbarAngle_" ,
    // c) response matrix ttbar quantities
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarMass_"  ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarPt_"    ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarY_"     ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarHT_"    ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarSumY_"  ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarDelPhi_",
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/ttbarDelY_"  , 
    // d) response matrix lepton quantities
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/lepPt_"      ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/lepEta_"     ,
    // e) response matrix b-quark quantities
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/bqPt_"       ,
    "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/bqEta_"      ,   
  };

  // b) list plot axes style
  // 1D: "x-axis title"/"y-axis title"/log/rebin-factor
  // log = 0 or 1 for linear or logarithmic axis 

  TString axisLabel1D[ ] = { // general fit performance
    "probability (best fit hypothesis)/events/1/25"                   , 
    "#chi^{2} (best fit hypothesis)/events/0/10"                      ,
    "#Delta#chi^{2} (1^{st} - 2^{nd} best fit hypothesis)/events/0/10",
    // reconstructed top quantities
    "m^{t and #bar{t}} #left[#frac{GeV}{c^{2}}#right]/#frac{dN}{dm^{t and #bar{t}}} #left[(#frac{GeV}{c^{2}})^{-1}#right]/0/10",
    "p_{T}^{t and #bar{t}} #left[#frac{GeV}{c}#right]/#frac{dN}{dp_{T}^{t and #bar{t}}} #left[#left(#frac{GeV}{c}#right)^{-1}#right]/0/1", //20"
    "#phi^{t and #bar{t}}/#frac{dN}{d#phi^{t and #bar{t}}}/0/4",
    "y^{t and #bar{t}}/#frac{dN}{dy^{t and #bar{t}}}/0/1",//5"
    "p_{T}(hadronic t) #left[#frac{GeV}{c}#right]/#frac{dN}{dp_{T}^{had. t}} #left[#left(#frac{GeV}{c}#right)^{-1}#right]/0/20",                         
    "#phi(hadronic t)/#frac{dN}{d#phi^{had. t}}/0/4",
    "y(hadronic t)/#frac{dN}{dy^{had. t}}/0/5"    ,
    "p_{T}(leptonic t) #left[#frac{GeV}{c}#right]/#frac{dN}{dp_{T}^{lep. t}} #left[#left(#frac{GeV}{c}#right)^{-1}#right]/0/20",                         
    "#phi(leptonic t)/#frac{dN}{d#phi^{lep. t}}/0/4",
    "y(leptonic t)/#frac{dN}{dy^{lep. t}}/0/5"   ,
    // generated top quantities
    "m^{t and #bar{t}} parton truth #left[#frac{GeV}{c^{2}}#right]/events/0/10",
    "p_{T}^{t and #bar{t}} #left[#frac{GeV}{c}#right] parton truth/events/0/1",//20"
    "p_{T}^{t and #bar{t}} #left[#frac{GeV}{c}#right] parton truth Phase Space/events/0/1",//20"
    "#phi(t) parton truth/events/0/4",
    "y^{t and #bar{t}} parton truth/events/0/1",//5"
    "p_{T}(hadronic t) #left[#frac{GeV}{c}#right] parton truth/events/0/20",                         
    "#phi(hadronic t) parton truth/events/0/4",
    "y(hadronic t) parton truth/events/0/5",
    "p_{T}(leptonic t) #left[#frac{GeV}{c}#right] parton truth/events/0/20",                         
    "#phi(leptonic t) parton truth/events/0/4",
    "y(leptonic t) parton truth/events/0/5",
    // reconstructed ttbar quantities	                            
    "m_{t#bar{t}} #left[#frac{GeV}{c^{2}}#right]/#frac{dN}{dm^{t#bar{t}}} #left[#left(#frac{GeV}{c^{2}}#right)^{-1}#right]/1/1",//60"
    "p_{T}^{t#bar{t}} #left[#frac{GeV}{c}#right]/#frac{dN}{dp_{T}^{t#bar{t}}} #left[#left(#frac{GeV}{c}#right)^{-1}#right]/0/1",//10"
    "y^{t#bar{t}}/#frac{dN}{dy^{t#bar{t}}}/0/1",//2
    "H_{T}^{t#bar{t}}=#Sigma(E_{T}(jets)) #left[#frac{GeV}{c}#right]/#frac{dN}{dH_{T}^{t#bar{t}}}/0/20",
    "y^{t}+y^{#bar{t}}/#frac{dN}{d(y^{t}+y^{#bar{t}})}/0/10",
    "#phi{lep. t}-#phi{had. t}/#frac{dN}{d(#phi^(lep. t)-#phi^{had. t})}/0/4",                
    "y^{lep. t}-y^{had. t}/#frac{dN}{d(y^(lep. t)-y^{had. t})}/0/4",  
    // generated ttbar quantities	                            
    "m_{t#bar{t}} #left[#frac{GeV}{c^{2}}#right] parton truth/events/1/1",//60"
    "p_{T}^{t#bar{t}} #left[#frac{GeV}{c}#right] parton truth/events/0/1",//10"
    "y^{t#bar{t}} parton truth/events/0/1",//2
    "H_{T}^{t#bar{t}}=#Sigma(E_{T}(jets)) #left[#frac{GeV}{c}#right] parton truth/events/0/20",
    "y^{t and #bar{t}} parton truth/events/0/10",
    "#phi(leptonic t)-#phi(hadronic t) parton truth/events/0/4",                
    "y(leptonic t)-y(hadronic t) parton truth/events/0/4",
    // reconstructed lepton quantities
    "p_{T}^{l} #left[#frac{GeV}{c}#right]/events #left[(#frac{GeV}{c})^{-1}#right]/0/1",
    "#eta^{l}/events/0/1" ,
    // generated lepton quantities
    "p_{T}^{l} #left[#frac{GeV}{c}#right] parton truth/events/0/1",
    "#eta^{l} parton truth/events/0/1",
    // reconstructed b-quark quantities
    "p_{T}^{b and #bar{b}} #left[#frac{GeV}{c}#right]/events #left[(#frac{GeV}{c})^{-1}#right]/0/1",
    "#eta^{b and #bar{b}}/events/0/1" ,
    // generated b-quark quantities
    "p_{T}^{b and #bar{b}} #left[#frac{GeV}{c}#right] parton truth/events/0/1",
    "#eta^{b and #bar{b}} parton truth/events/0/1",
  };
  // 2D: "x-axis title"/"y-axis title"
  TString axisLabel2D[ ] = {// reco - gen Match correlation plots (ttbar signal only)
    // a) combinatorics and KinFit Hypothesis Quality(ttbar signal only)
    "i_{lead jet} parton truth/i_{lead jet} hypothesis fit",
    // b) response matrix Top quantities
    "p_{T}^{t and #bar{t}} #left[#frac{GeV}{c}#right] gen/p_{T}^{t and #bar{t}} #left[#frac{GeV}{c}#right] reco",
    "#phi^{t and #bar{t}} gen/#phi^{t and #bar{t}} reco",
    "y^{t and #bar{t}} gen/y^{t and #bar{t}} reco",
    "angle(b,#bar{b}) gen (t#bar{t} rest frame)/angle(b,#bar{b}) reco (t#bar{t} rest frame)",
    // c) response matrix ttbar quantities
    "m(t#bar{t}) #left[#frac{GeV}{c^{2}}#right] gen/m(t#bar{t}) #left[#frac{GeV}{c^{2}}#right] reco",
    "p_{T}(t#bar{t}) #left[#frac{GeV}{c}#right] gen/p_{T}(t#bar{t}) #left[#frac{GeV}{c}#right] reco",
    "y(t#bar{t}) gen/y(t#bar{t}) reco"              ,
    "H_{T}(t#bar{t}) #left[#frac{GeV}{c}#right] gen/H_{T}(t#bar{t}) #left[#frac{GeV}{c}#right] reco",
    "#Sigmay(t#bar{t}) gen/#Sigmay(t#bar{t}) reco"  ,
    "#phi(leptonic t)-#phi(hadronic t) gen/#phi(leptonic t)-#phi(hadronic t) Kinfit",
    "y(leptonic t)-y(hadronic t) gen/y(leptonic t)-y(hadronic t) Kinfit" ,
    // d) response matrix lepton quantities
    "p_{T}^{l} #left[#frac{GeV}{c}#right] gen/p_{T}^{l} #left[#frac{GeV}{c}#right] reco",
    "#eta^{l} gen/#eta^{l} reco",           
    // e) response matrix b-quark quantities
    "p_{T}^{b or #bar{b}} #left[#frac{GeV}{c}#right] gen/p_{T}^{b or #bar{b}} #left[#frac{GeV}{c}#right] reco",
    "#eta^{b or #bar{b}} gen/#eta^{b or #bar{b}} reco",           
  };
  TString axisLabel1Dadd[ ] = {
    // generated angular distributions
    "#angle(b,#bar{b}) parton truth (detector rest frame)/events/0/21",
    "#angle(b,#bar{b}) parton truth (t#bar{t} rest frame)/events/0/21",
    "#angle(W,W) parton truth (t#bar{t} RF)/events/0/21"              ,
    "#angle(lep.t,W) parton truth (t:t#bar{t} RF, W:t RF)/events/0/21",
    "#angle(had.t,W) parton truth (t:t#bar{t} RF, W:t RF)/events/0/21",
    "#angle(lep.t,b) parton truth (t#bar{t} rest frame)/events/0/21"  ,
    "#angle(had.t,b) parton truth (t#bar{t} rest frame)/events/0/21"  ,
    "#angle(lep.b,W) parton truth (t#bar{t} rest frame)/events/0/21"  ,
    "#angle(had.b,W) parton truth (t#bar{t} rest frame)/events/0/21"  ,
    "#angle(q,#bar{q}) parton truth (top rest frame)/events/0/21"     ,
    "#angle(q,lep.b) parton truth (t#bar{t} rest frame)/events/0/21"  ,
    "#angle(q,had.b) parton truth (top rest frame)/events/0/21"       ,
    "#angle(#mu,lep.b) parton truth (top rest frame)/events/0/21"     , 
    "#angle(#mu,lep.b) parton truth (t#bar{t} rest frame)/events/0/21",
    "#angle(#mu,lep.b) parton truth (top rest frame)/events/0/21"     ,
    "#angle(#mu,q) parton truth (t#bar{t} rest frame)/events/0/21"    ,
    "#angle(#mu,#nu) parton truth (t#bar{t} rest frame)/events/0/21"  ,
    "#angle(#nu,lep.b) parton truth (top rest frame)/events/0/21"     ,
    "#angle(#nu,had.b) parton truth (t#bar{t} rest frame)/events/0/21",
    "#angle(#nu,q) parton truth (t#bar{t} rest frame)/events/0/21"    ,
    "#angle(#mu,W) parton truth (#mu:W RF, W:Det RF)/events/0/21"     ,
    "#angle(q,W) parton truth (q:W RF, W:Det RF)/events/0/21"         ,
    "#angle(#nu,W) parton truth (#nu:W RF, W:Det RF)/events/0/21"     ,
    //  reconstructed angular distributions
    "#angle(b,#bar{b}) (detector rest frame)/events/0/21",
    "#angle(b,#bar{b}) (t#bar{t} rest frame)/events/0/21",
    "#angle(W,W) (t#bar{t} RF)/events/0/21"              ,
    "#angle(lep.t,W) (t:t#bar{t} RF, W:t RF)/events/0/21",
    "#angle(had.t,W) (t:t#bar{t} RF, W:t RF)/events/0/21",
    "#angle(lep.t,b) (t#bar{t} rest frame)/events/0/21"  ,
    "#angle(had.t,b) (t#bar{t} rest frame)/events/0/21"  ,
    "#angle(lep.b,W) (t#bar{t} rest frame)/events/0/21"  ,
    "#angle(had.b,W) (t#bar{t} rest frame)/events/0/21"  ,
    "#angle(q,#bar{q}) (top rest frame)/events/0/21"     ,
    "#angle(q,lep.b) (t#bar{t} rest frame)/events/0/21"  ,
    "#angle(q,had.b) (top rest frame)/events/0/21"       ,
    "#angle(#mu,lep.b) (top rest frame)/events/0/21"     , 
    "#angle(#mu,lep.b) (t#bar{t} rest frame)/events/0/21",
    "#angle(#mu,lep.b) (top rest frame)/events/0/21"     ,
    "#angle(#mu,q) (t#bar{t} rest frame)/events/0/21"    ,
    "#angle(#mu,#nu) (t#bar{t} rest frame)/events/0/21"  ,
    "#angle(#nu,lep.b) (top rest frame)/events/0/21"     ,
    "#angle(#nu,had.b) (t#bar{t} rest frame)/events/0/21",
    "#angle(#nu,q) (t#bar{t} rest frame)/events/0/21"    ,
    "#angle(#mu,lep.W) (#mu:W RF, W:Det RF)/events/0/21" ,
    "#angle(#nu,lep.W) (#nu:W RF, W:Det RF)/events/0/21" ,
    "#angle(q,had.W) (q:W RF, W:Det RF)/events/0/21"     ,
    // reconstructed event shape variables
    "aplanarity/events/0/2"  ,
    "sphericity/events/0/10" ,
    "C/events/0/10"          ,
    "D/events/0/4"           ,
    "circularity/events/0/10",
    "isotropy/events/0/10"   ,
    // combinatorics and Kinfit Hypothesis Quality(ttbar signal only)
    "#Deltai_{lead jet}(genMatch - kinFit), hadronic b-quark/events/0/1", 
    "#Deltai_{lead jet}(genMatch - kinFit), leptonic b-quark/events/0/1", 
    "#Deltai_{lead jet}(genMatch - kinFit), light quarks/events/0/1"    ,
    "N(wrong assigned jets)/events/0/1"                                 , 
    "permutation/events/0/1"                                            ,
    "#DeltaR(parton, reco jet assigned from Kinfit)/partons/1/10"       ,
    // pull distributions
    "(p_{t gen}-p_{t fit}) (#sigmap_{t})^{-1} (hadronic b-quark)/events/0/1"  ,
    "(#eta_{gen}-#eta_{fit}) (#sigma#eta)^{-1} (hadronic b-quark)/events/0/1" ,
    "(#phi_{gen}-#phi_{fit}) (#sigma#phi)^{-1} (hadronic b-quark)/events/0/1" ,
    "(p_{t gen}-p_{t fit}) (#sigmap_{t})^{-1} (leptonic b-quark)/events/0/1"  ,
    "(#eta_{gen}-#eta_{fit}) (#sigma#eta)^{-1} (leptonic b-quark)/events/0/1" ,
    "(#phi_{gen}-#phi_{fit}) (#sigma#phi)^{-1} (leptonic b-quark)/events/0/1" ,
    "(p_{t gen}-p_{t fit}) (#sigmap_{t})^{-1} (light quark)/events/0/1"       ,
    "(#eta_{gen}-#eta_{fit}) (#sigma#eta)^{-1} (light quark)/events/0/1"      ,
    "(#phi_{gen}-#phi_{fit}) (#sigma#phi)^{-1} (light quark)/events/0/1"      ,
    "(p_{t gen}-p_{t fit}) (#sigmap_{t})^{-1} (lepton)/events/0/1"            ,
    "(#eta_{gen}-#eta_{fit}) (#sigma#eta)^{-1} (lepton)/events/0/1"           ,
    "(#phi_{gen}-#phi_{fit}) (#sigma#phi)^{-1} (lepton)/events/0/1"           ,
    "(p_{t gen}-p_{t fit}) (#sigmap_{t})^{-1} (neutrino)/events/0/1"          ,
    "(#eta_{gen}-#eta_{fit}) (#sigma#eta)^{-1} (neutrino)/events/0/1"         ,
    "(#phi_{gen}-#phi_{fit}) (#sigma#phi)^{-1} (neutrino)/events/0/1"         ,
    "(p_{t fit}-p_{t gen}) p_{t gen}^{-1} (leptonic W)/events/0/1"            ,
    "(#eta_{fit}-#eta_{gen}) #eta_{gen}^{-1} (leptonic W)/events/0/1"         ,
    "(#phi_{fit}-#phi_{gen}) #phi_{gen}^{-1} (leptonic W)/events/0/1"         ,
    "(p_{t fit}-p_{t gen}) p_{t gen}^{-1} (hadronic W)/events/0/1"            ,
    "(#eta_{fit}-#eta_{gen}) #eta_{gen}^{-1} (hadronic W)/events/0/1"         ,
    "(#phi_{fit}-#phi_{gen}) #phi_{gen}^{-1} (hadronic W)/events/0/1"         ,
    // (IV) residuals for input objects before/after kinematic fit
    // (i) lepton
    "(p_{t}^{lep kinFit}-p_{t}^{lep rec}) : p_{t}^{lep rec}/Frequency/0/10",
    "(p_{t}^{lep kinFit}-p_{t}^{lep parton}) : p_{t}^{lep parton}/Frequency/0/10",
    "(p_{t}^{lep Rec}-p_{t}^{lep parton}) : p_{t}^{lep parton}/Frequency/0/10",
    "#eta^{lep kinFit}-#eta^{lep rec}/Frequency/0/10",
    "#eta^{lep kinFit}-#eta^{lep parton}/Frequency/0/10",
    "#eta^{lep Rec}-#eta^{lep parton}/Frequency/0/10",
    "#phi^{lep kinFit}-#phi^{lep rec}/Frequency/0/10",
    "#phi^{lep kinFit}-#phi^{lep parton}/Frequency/0/10",
    "#phi^{lep Rec}-#phi^{lep parton}/Frequency/0/10",
    "(p_{t}^{lep kinFit}-p_{t}^{lep rec}) : p_{t}^{lep rec}/Frequency (correct permutation)/0/10",
    "(p_{t}^{lep kinFit}-p_{t}^{lep parton}) : p_{t}^{lep parton}/Frequency (correct permutation)/0/10",
    "(p_{t}^{lep Rec}-p_{t}^{lep parton}) : p_{t}^{lep parton}/Frequency (correct permutation)/0/10",
    "#eta^{lep kinFit}-#eta^{lep rec}/Frequency (correct permutation)/0/10",
    "#eta^{lep kinFit}-#eta^{lep parton}/Frequency (correct permutation)/0/10",
    "#eta^{lep Rec}-#eta^{lep parton}/Frequency (correct permutation)/0/10",
    "#phi^{lep kinFit}-#phi^{lep rec}/Frequency (correct permutation)/0/10",
    "#phi^{lep kinFit}-#phi^{lep parton}/Frequency (correct permutation)/0/10",
    "#phi^{lep Rec}-#phi^{lep parton}/Frequency (correct permutation)/0/10",
    // (ii) neutrino
    "(p_{t}^{#nu kinFit}-p_{t}^{#nu rec}) : p_{t}^{#nu rec}/Frequency/0/10",
    "(p_{t}^{#nu kinFit}-p_{t}^{#nu parton}) : p_{t}^{#nu parton}/Frequency/0/10",
    "(p_{t}^{#nu Rec}-p_{t}^{#nu parton}) : p_{t}^{#nu parton}/Frequency/0/10",
    "#eta^{#nu kinFit}-#eta^{#nu rec}/Frequency/0/10",
    "#eta^{#nu kinFit}-#eta^{#nu parton}/Frequency/0/10",
    "#eta^{#nu Rec}-#eta^{#nu parton}/Frequency/0/10",
    "#phi^{#nu kinFit}-#phi^{#nu rec}/Frequency/0/10",
    "#phi^{#nu kinFit}-#phi^{#nu parton}/Frequency/0/10",
    "#phi^{#nu Rec}-#phi^{#nu parton}/Frequency/0/10",
    "(p_{t}^{#nu kinFit}-p_{t}^{#nu rec}) : p_{t}^{#nu rec}/Frequency (correct permutation)/0/10",
    "(p_{t}^{#nu kinFit}-p_{t}^{#nu parton}) : p_{t}^{#nu parton}/Frequency (correct permutation)/0/10",
    "(p_{t}^{#nu Rec}-p_{t}^{#nu parton}) : p_{t}^{#nu parton}/Frequency (correct permutation)/0/10",
    "#eta^{#nu kinFit}-#eta^{#nu rec}/Frequency (correct permutation)/0/10",
    "#eta^{#nu kinFit}-#eta^{#nu parton}/Frequency (correct permutation)/0/10",
    "#eta^{#nu Rec}-#eta^{#nu parton}/Frequency (correct permutation)/0/10",
    "#phi^{#nu kinFit}-#phi^{#nu rec}/Frequency (correct permutation)/0/10",
    "#phi^{#nu kinFit}-#phi^{#nu parton}/Frequency (correct permutation)/0/10",
    "#phi^{#nu Rec}-#phi^{#nu parton}/Frequency (correct permutation)/0/10",
    // (iii) hadronic b jet
    "(p_{t}^{had b-jet kinFit}-p_{t}^{had b-jet rec}) : p_{t}^{had b-jet rec}/Frequency/0/10",
    "(p_{t}^{had b-jet kinFit}-p_{t}^{had b-jet parton}) : p_{t}^{had b-jet parton}/Frequency/0/10",
    "(p_{t}^{had b-jet Rec}-p_{t}^{had b-jet parton}) : p_{t}^{had b-jet parton}/Frequency/0/10",
    "#eta^{had b-jet kinFit}-#eta^{had b-jet rec}/Frequency/0/10",
    "#eta^{had b-jet kinFit}-#eta^{had b-jet parton}/Frequency/0/10",
    "#eta^{had b-jet Rec}-#eta^{had b-jet parton}/Frequency/0/10",
    "#phi^{had b-jet kinFit}-#phi^{had b-jet rec}/Frequency/0/10",
    "#phi^{had b-jet kinFit}-#phi^{had b-jet parton}/Frequency/0/10",
    "#phi^{had b-jet Rec}-#phi^{had b-jet parton}/Frequency/0/10",
    "(p_{t}^{had b-jet kinFit}-p_{t}^{had b-jet rec}) : p_{t}^{had b-jet rec}/Frequency (correct permutation)/0/10",
    "(p_{t}^{had b-jet kinFit}-p_{t}^{had b-jet parton}) : p_{t}^{had b-jet parton}/Frequency (correct permutation)/0/10",
    "(p_{t}^{had b-jet Rec}-p_{t}^{had b-jet parton}) : p_{t}^{had b-jet parton}/Frequency (correct permutation)/0/10",
    "#eta^{had b-jet kinFit}-#eta^{had b-jet rec}/Frequency (correct permutation)/0/10",
    "#eta^{had b-jet kinFit}-#eta^{had b-jet parton}/Frequency (correct permutation)/0/10",
    "#eta^{had b-jet Rec}-#eta^{had b-jet parton}/Frequency (correct permutation)/0/10",
    "#phi^{had b-jet kinFit}-#phi^{had b-jet rec}/Frequency (correct permutation)/0/10",
    "#phi^{had b-jet kinFit}-#phi^{had b-jet parton}/Frequency (correct permutation)/0/10",
    "#phi^{had b-jet Rec}-#phi^{had b-jet parton}/Frequency (correct permutation)/0/10",
    // (iv) leptonic b jet
    "(p_{t}^{lep b-jet kinFit}-p_{t}^{lep b-jet rec}) : p_{t}^{lep b-jet rec}/Frequency/0/10",
    "(p_{t}^{lep b-jet kinFit}-p_{t}^{lep b-jet parton}) : p_{t}^{lep b-jet parton}/Frequency/0/10",
    "(p_{t}^{lep b-jet Rec}-p_{t}^{lep b-jet parton}) : p_{t}^{lep b-jet parton}/Frequency/0/10",
    "#eta^{lep b-jet kinFit}-#eta^{lep b-jet rec}/Frequency/0/10",
    "#eta^{lep b-jet kinFit}-#eta^{lep b-jet parton}/Frequency/0/10",
    "#eta^{lep b-jet Rec}-#eta^{lep b-jet parton}/Frequency/0/10",
    "#phi^{lep b-jet kinFit}-#phi^{lep b-jet rec}/Frequency/0/10",
    "#phi^{lep b-jet kinFit}-#phi^{lep b-jet parton}/Frequency/0/10",
    "#phi^{lep b-jet Rec}-#phi^{lep b-jet parton}/Frequency/0/10",
    "(p_{t}^{lep b-jet kinFit}-p_{t}^{lep b-jet rec}) : p_{t}^{lep b-jet rec}/Frequency (correct permutation)/0/10",
    "(p_{t}^{lep b-jet kinFit}-p_{t}^{lep b-jet parton}) : p_{t}^{lep b-jet parton}/Frequency (correct permutation)/0/10",
    "(p_{t}^{lep b-jet Rec}-p_{t}^{lep b-jet parton}) : p_{t}^{lep b-jet parton}/Frequency (correct permutation)/0/10",
    "#eta^{lep b-jet kinFit}-#eta^{lep b-jet rec}/Frequency (correct permutation)/0/10",
    "#eta^{lep b-jet kinFit}-#eta^{lep b-jet parton}/Frequency (correct permutation)/0/10",
    "#eta^{lep b-jet Rec}-#eta^{lep b-jet parton}/Frequency (correct permutation)/0/10",
    "#phi^{lep b-jet kinFit}-#phi^{lep b-jet rec}/Frequency (correct permutation)/0/10",
    "#phi^{lep b-jet kinFit}-#phi^{lep b-jet parton}/Frequency (correct permutation)/0/10",
    "#phi^{lep b-jet Rec}-#phi^{lep b-jet parton}/Frequency (correct permutation)/0/10",
    // (v) light jets
    "(p_{t}^{light jet kinFit}-p_{t}^{light jet rec}) : p_{t}^{light jet rec}/Frequency/0/10",
    "(p_{t}^{light jet kinFit}-p_{t}^{light jet parton}) : p_{t}^{light jet parton}/Frequency/0/10",
    "(p_{t}^{light jet Rec}-p_{t}^{light jet parton}) : p_{t}^{light jet parton}/Frequency/0/10",
    "#eta^{light jet kinFit}-#eta^{light jet rec}/Frequency/0/10",
    "#eta^{light jet kinFit}-#eta^{light jet parton}/Frequency/0/10",
    "#eta^{light jet Rec}-#eta^{light jet parton}/Frequency/0/10",
    "#phi^{light jet kinFit}-#phi^{light jet rec}/Frequency/0/10",
    "#phi^{light jet kinFit}-#phi^{light jet parton}/Frequency/0/10",
    "#phi^{light jet Rec}-#phi^{light jet parton}/Frequency/0/10",
    "(p_{t}^{light jet kinFit}-p_{t}^{light jet rec}) : p_{t}^{light jet rec}/Frequency (correct permutation)/0/10",
    "(p_{t}^{light jet kinFit}-p_{t}^{light jet parton}) : p_{t}^{light jet parton}/Frequency (correct permutation)/0/10",
    "(p_{t}^{light jet Rec}-p_{t}^{light jet parton}) : p_{t}^{light jet parton}/Frequency (correct permutation)/0/10",
    "#eta^{light jet kinFit}-#eta^{light jet rec}/Frequency (correct permutation)/0/10",
    "#eta^{light jet kinFit}-#eta^{light jet parton}/Frequency (correct permutation)/0/10",
    "#eta^{light jet Rec}-#eta^{light jet parton}/Frequency (correct permutation)/0/10",
    "#phi^{light jet kinFit}-#phi^{light jet rec}/Frequency (correct permutation)/0/10",
    "#phi^{light jet kinFit}-#phi^{light jet parton}/Frequency (correct permutation)/0/10",
    "#phi^{light jet Rec}-#phi^{light jet parton}/Frequency (correct permutation)/0/10",
  };
  // count # plots
  unsigned int N1Dplots = sizeof(plots1D)/sizeof(TString);
  unsigned int N2Dplots = sizeof(plots2D)/sizeof(TString);
  unsigned int N1Dplotsadd = sizeof(plots1Dadd)/sizeof(TString);
  
  
  // check if all axis labels exist
  if(N1Dplots != sizeof(axisLabel1D)/sizeof(TString)) std::cout << "ERROR: some 1D plots or axis label are missing" << std::endl;
  if(N2Dplots != sizeof(axisLabel2D)/sizeof(TString)) std::cout << "ERROR: some 2D plots or axis label are missing" << std::endl;
  if((N1Dplots != sizeof(axisLabel1D)/sizeof(TString))||(N2Dplots != sizeof(axisLabel2D)/sizeof(TString))) exit (1);
  if(systematicVariation==sysNo){
    if(N1Dplotsadd != sizeof(axisLabel1Dadd)/sizeof(TString)){
      std::cout << "ERROR: some additional 1D plots or axis label are missing" << std::endl;
      exit(1);
    }
    N1Dplots+=N1Dplotsadd;
  }
  // run automatically in batch mode if there are many canvas
  if((N1Dplots+N2Dplots)>15) gROOT->SetBatch();

  // ---
  //    open our standard analysis files
  // ---
  std::map<unsigned int, TFile*> files_ = getStdTopAnalysisFiles(inputFolder, systematicVariation, dataFile, decayChannel);

  // ---
  //    loading histos
  // ---
  // collect all plot names in vector (first 1D, then 2D)
  std::vector<TString> plotList_;
  plotList_.insert( plotList_.begin(), plots1D, plots1D + sizeof(plots1D)/sizeof(TString) );
  if(systematicVariation==sysNo) plotList_.insert( plotList_.end(), plots1Dadd, plots1Dadd + sizeof(plots1Dadd)/sizeof(TString) );
  plotList_.insert( plotList_.end()  , plots2D, plots2D + sizeof(plots2D)/sizeof(TString) );
  // remove irrelevant plots for systemtic variation to speed up

  // container for all histos (1D&2D)
  // example for acess: histo_["plotName"][sampleNr]
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, TH1F* > histoErrorBand_;
  std::map< TString, std::map <unsigned int, TH2F*> > histo2_;
  // total # plots 
  int Nplots=0;
  // save all histos from plotList_ that exist in files_ into 
  // histo_ and histo2_ and count total # of plots as Nplots
  if(verbose>1) std::cout << std::endl;
  std::vector<TString> vecRedundantPartOfNameInData;
  vecRedundantPartOfNameInData.push_back(sysInputFolderExtension);
  getAllPlots(files_, plotList_, histo_, histo2_, N1Dplots, Nplots, verbose-1, decayChannel, &vecRedundantPartOfNameInData);
  // ---
  //    lumiweighting for choosen luminosity
  // ---
  // scale every histo in histo_ and histo2_ to the corresponding luminosity
  // Additionally the mu eff SF is applied
  // NOTE: luminosity [/pb]
  scaleByLuminosity(plotList_, histo_, histo2_, N1Dplots, luminosity, verbose-1, systematicVariation, decayChannel);

  // ---
  //    add single top channels and DiBoson contributions
  // ---
  // for SingleTop and DiBoson samples:
  // every plot plotList_ existing in sTop/ diBoson .root file
  // will be combined and saved in the histo_ and histo2_ map
  // reCreate: recreate combined plots if they are already existing
  bool reCreate=false;
  AddSingleTopAndDiBoson(plotList_, histo_, histo2_, N1Dplots, verbose-1, reCreate, decayChannel);

  // ---
  //    copy event yields for total xSec calculation
  // ---
  TH1F* dataYield =(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPt"][kData ]->Clone());
  TH1F* SigYield  =(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPt"][kSig  ]->Clone());
  TH1F* BkgYield  =(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPt"][kBkg  ]->Clone());
  TH1F* STopYield =(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPt"][kSTop ]->Clone());
  TH1F* WjetYield =(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPt"][kWjets]->Clone());
  TH1F* ZjetYield =(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPt"][kZjets]->Clone());
  TH1F* DiBosYield=(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPt"][kDiBos]->Clone());
  TH1F* QCDYield  =(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/topPt"][kQCD  ]->Clone());
  TH1F* GenInclusive =(TH1F*)(histo_["analyzeTopPartonLevelKinematics"+sysInputGenFolderExtension+"/topPt"          ][kSig]->Clone());
  TH1F* GenPhaseSpace=(TH1F*)(histo_["analyzeTopPartonLevelKinematicsPhaseSpace"+sysInputGenFolderExtension+"/topPt"][kSig]->Clone());

  // ---
  //    configure histograms
  // ---
  // needs: plotList_, histo_, histo2_, N1Dplots, axisLabel_, axisLabel1D, axisLabel2D
  std::vector<TString> axisLabel_;
  axisLabel_.insert( axisLabel_.begin(), axisLabel1D, axisLabel1D + sizeof(axisLabel1D)/sizeof(TString) );
  if(systematicVariation==sysNo) axisLabel_.insert( axisLabel_.end(), axisLabel1Dadd, axisLabel1Dadd + sizeof(axisLabel1Dadd)/sizeof(TString) );
  axisLabel_.insert( axisLabel_.end()  , axisLabel2D, axisLabel2D + sizeof(axisLabel2D)/sizeof(TString) );
  // loop plots
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    if(decayChannel=="electron"&&axisLabel_[plot].Contains("#mu")) axisLabel_[plot].ReplaceAll("#mu", "e");
    if(verbose>1){
      std::cout << "(plot, x Axis label , y Axis label , log scale?, rebinning factor):" << std::endl;
      std::cout << plotList_[plot] << ": " << getStringEntry(axisLabel_[plot],1);
      std::cout << " , " << getStringEntry(axisLabel_[plot], 2);
      if(plot<N1Dplots){
	std::cout<< " , " << getStringEntry(axisLabel_[plot], 3);
	std::cout<< " , " << getStringEntry(axisLabel_[plot], 4);
      }
      std::cout << std::endl;
    }
  }
  // loop samples
  for(unsigned int sample=kSig; sample<=kData; ++sample){
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      // a) 1D
      if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)){ 
	// default
	histogramStyle( *histo_[plotList_[plot]][sample], sample, true);
	// special configurations
	if(getStringEntry(plotList_[plot], 2)=="PartonJetDRall")histo_[plotList_[plot]][sample]->SetNdivisions(816);
      }
      // b) 2D
      if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)) histStyle2D( *histo2_[plotList_[plot]][sample], sampleLabel(sample,decayChannel), getStringEntry(axisLabel_[plot],1), getStringEntry(axisLabel_[plot],2));
    }
  }
  // -------------------------------------------
  // clone relevant plots for SVD unfolding xSec
  // -------------------------------------------
  int kAllMC=kSAToptW+1;
  for(unsigned int var=0; var<xSecVariables_.size(); ++var){
    TString variable=xSecVariables_[var];
    // ttbar BG yield for signal fraction
    histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable][kBkg]=(TH1F*)histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kBkg]->Clone();
    // create combined BG reco plot
    histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable][kAllMC]=(TH1F*)histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kBkg]->Clone();
    for(int bgsample=kZjets; bgsample<=kDiBos; ++bgsample){
      histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable][kAllMC]->Add((TH1F*)histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][bgsample]->Clone());
    }
    // data event yield
    histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable][kData]=(TH1F*)histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData]->Clone();
    // signal reco plot
    histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable][kSig]=(TH1F*)histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSig]->Clone();
    // signal gen plot
    histo_["analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/raw"+variable][kSig]=(TH1F*)histo_["analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/"+variable][kSig]->Clone();
    // response matrix plot
    histo2_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable+"_"][kSig]=(TH2F*)histo2_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable+"_"][kSig]->Clone();
  }
  
  // ---
  //    rebinning 1D histograms
  // ---
  // create variable bin edges
  std::map<TString, std::vector<double> > binning_ = makeVariableBinning();
  // loop samples
  for(unsigned int sample=kSig; sample<=kData; ++sample){
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      TString plotName=plotList_[plot];
      // check if plot exists and is 1D
      if((plot<N1Dplots)&&(plotExists(histo_, plotName, sample))){
	// equidistant binning
	  double reBinFactor = atof(((string)getStringEntry(axisLabel_[plot],4)).c_str());
	if(reBinFactor>1&&binning_.count(plotName)==0){
	  equalReBinTH1(reBinFactor, histo_, plotName, sample);
	}
	// variable binning
	else{
	  // check existence of e.g. binning_["topPt"]
	  if(binning_.count(getStringEntry(plotName, 2))>0){
	    reBinTH1F(*histo_[plotName][sample], binning_[getStringEntry(plotName, 2)], verbose-1);
	    if(verbose>1){
	      for(int i=1; i<= histo_[plotName][sample]->GetNbinsX()+1; i++){
	       
		std::cout << "bin " << i << ": " << histo_[plotName][sample]->GetBinContent(i) << " / ";
		std::cout << histo_[plotName][sample]->GetBinWidth(i) << std::endl;
	      }
	    }
	    // divide by binwidth
	    histo_[plotName][sample] = divideByBinwidth(histo_[plotName][sample], verbose-1);
	    if(verbose>1){
	      for(int i=1; i<= histo_[plotName][sample]->GetNbinsX()+1; i++){
		std::cout << "bin " << i << "= " << histo_[plotName][sample]->GetBinContent(i) << std::endl;
	      }
	    }
	    // change y axis label
	    if(!axisLabel_[plot].Contains("binwidth")){
	      //axisLabel_[plot].ReplaceAll(getStringEntry(axisLabel_[plot],2), getStringEntry(axisLabel_[plot],2)+" per binwidth");
	      // check if unit is GeV
	      if(getStringEntry(axisLabel_[plot],1).Contains("GeV")){
		//axisLabel_[plot].ReplaceAll(getStringEntry(axisLabel_[plot],2), getStringEntry(axisLabel_[plot],2)+" [#frac{c}{GeV}]");
	      }
	    }
	  }
	}
      }
    }
  }
  
  // ---
  //    MC efficiency determination
  // ---
  // count # of efficiency histos
  unsigned int NMCeff=0;
  // loop all variables
  for(unsigned int number=0; number<xSecVariables_.size(); ++number){
    TString variable=xSecVariables_[number];    
TString efficiency="efficiency/"+variable;
    // check if gen and reco plots are available
    if(plotExists(histo_, "analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/"+variable, kSig)&&plotExists(histo_, "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable, kSig)){
      // std::cout << "found gen and reco" << std::endl;
      // get reco plot
      histo_[efficiency][kSig]=(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSig]->Clone());
      // divide by gen plot
      histo_[efficiency][kSig]->Divide((TH1F*)(histo_["analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/"+variable][kSig]->Clone()));
//       if(sys==sysHadronisationUp){
// 	double SF=1;
// 	for(int bin=1; bin<=histo_[efficiency][kSig]->GetNbinsX(); ++bin){
// 	  histo_[efficiency][kSig]->SetBinContent(bin histo_[efficiency][kSig]->GetBinContent(bin)*SF);
// 	}
//       }
      // std::cout << "gen(bin1): "  <<  histo_["analyzeTopPartonLevelKinematics/"+variable  ][kSig]->GetBinContent(1) << std::endl;
      // std::cout << "reco(bin1): " <<  histo_["analyzeTopRecoKinematicsKinFit/"+variable][kSig]->GetBinContent(1) << std::endl;
      // std::cout << "eff(bin1): "  <<  histo_[efficiency][kSig]->GetBinContent(1) << std::endl;

      // add plot to list of plots
      plotList_.push_back(efficiency);
      // add axis configuration
      unsigned int positionOfRecoAxisLabel = positionInVector(plotList_, "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable);
      TString recoAxisLabel =axisLabel_[positionOfRecoAxisLabel];
      axisLabel_.push_back(""+getStringEntry(recoAxisLabel,1)+"/"+"#epsilon #times A (MC t#bar{t}#rightarrow#mu)/"+getStringEntry(recoAxisLabel,3)+"/"+getStringEntry(recoAxisLabel,4));
      if(decayChannel=="electron") axisLabel_[axisLabel_.size()-1].ReplaceAll("#mu", "e");
      // set binomial errors
      if(verbose>1) std::cout << "       eff, events, width, sqrt(eff*(1.-eff)/events" << std::endl;
      for(int bin=1; bin<=histo_[efficiency][kSig]->GetNbinsX(); ++bin){
	double eff=histo_[efficiency][kSig]->GetBinContent(bin); 
	double N=histo_["analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/"+variable][kSig]->GetBinContent(bin);
	double width=histo_["analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/"+variable][kSig]->GetBinWidth(bin);
	N*=width*effSFAB(systematicVariation,decayChannel);
	N/=(lumiweight(kSig, luminosity, systematicVariation, decayChannel));
	if(verbose>1){
	  std::cout << "bin " << bin << ": " << eff << ", " << N << ", " << width;
	  std::cout << ", " <<  sqrt(eff*(1.-eff)/N) << std::endl;
	}
	histo_[efficiency][kSig]->SetBinError(bin, sqrt(eff*(1.-eff)/N));
	// set error to 0 for bins with width 0 or 0 entries
	if(N==0) histo_[efficiency][kSig]->SetBinError(bin, 0);
      }
      // change histo style
      histogramStyle(*histo_[efficiency][kSig], kSig, false, 0.6);
      ++NMCeff;
    }
  }

  // ---
  //    differential cross section (extrapolated or PS) determination
  // ---
  // count # of cross section histos
  unsigned int NXSec=0;
  // loop all variables
  for(unsigned int number=0; number<xSecVariables_.size(); ++number){
    TString variable=xSecVariables_[number];
    TString label =getStringEntry(xSecLabel_[number],1);
    TString label2=getStringEntry(xSecLabel_[number],2);
    if(label2=="[#frac{GeV}{c}]")          label2="#left[pb #left(#frac{GeV}{c}#right)^{-1}#right]";
    else if(label2=="[#frac{GeV}{c^{2}}]") label2="#left[pb #left(#frac{GeV}{c^{2}}#right)^{-1}#right]";
    else if(label2==" ") label2="[pb]";
    TString xSec ="xSec/";
    if(compare) xSec+="BBB";
    xSec+=variable;
    bool calculateXSec=true;
    // loop samples 
    for(unsigned int sample=kSig; sample<=kData; ++sample){
      // check if reco MC plot and data event yield plots are available
      if(!plotExists(histo_, "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable, sample)){
	calculateXSec=false;
      }
    }
    // check if efficiency plot is available
    if(!plotExists(histo_, "efficiency/"+variable, kSig)){
      calculateXSec=false;
    }
    if(calculateXSec&&(!SVDunfold||compare)){
      // a) differential XSec from data
      // get data plot
      TString name=TString(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData]->GetName())+"kData";
      histo_[xSec][kData]=(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData]->Clone(name));
      // subtract BG(MC)
      //histo_[xSec][kData]->Add((TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kBkg  ]->Clone()), -1); // other ttbar BG is accessed by a signal fraction (see below) 
      histo_[xSec][kData]->Add((TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kZjets]->Clone()), -1);
      histo_[xSec][kData]->Add((TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kWjets]->Clone()), -1);
      histo_[xSec][kData]->Add((TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSTop ]->Clone()), -1);
      histo_[xSec][kData]->Add((TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kDiBos]->Clone()), -1);
      histo_[xSec][kData]->Add((TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kQCD  ]->Clone()), -1);
      // correct for fraction of ttbar events that are signal
      histo_[xSec+"AllTtBar"][kSig]=     (TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSig]->Clone());
      histo_[xSec+"AllTtBar"][kSig]->Add((TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kBkg]->Clone()));
      histo_[xSec+"SignalFraction"][kSig]=(TH1F*)histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSig]->Clone();
      histo_[xSec+"SignalFraction"][kSig]->Divide(histo_[xSec+"AllTtBar"][kSig]);
      histo_[xSec][kData]->Multiply(histo_[xSec+"SignalFraction"][kSig]);
      // apply efficiency correction
      DivideYieldByEfficiencyAndLumi(histo_[xSec][kData], ((TH1F*)(histo_["efficiency/"+variable][kSig])), luminosity, 0);
      // b) differential XSec from Signal(MC prediction)
      histo_[xSec][kSig]=(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSig]->Clone());
      DivideYieldByEfficiencyAndLumi(histo_[xSec][kSig], (TH1F*)(histo_["efficiency/"+variable][kSig]), luminosity, 0);
      // add plot to list of plots
      plotList_.push_back(xSec);
      // add axis configuration
      unsigned int positionOfRecoAxisLabel = positionInVector(plotList_, "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable);
      TString recoAxisLabel =axisLabel_[positionOfRecoAxisLabel];
      recoAxisLabel.ReplaceAll("KinFit ","");
      //      axisLabel_.push_back(""+getStringEntry(recoAxisLabel,1)+"/"+"#frac{d#sigma}{d"+label+"} "+label2+" (t#bar{t}#rightarrow #mu prompt)/"+getStringEntry(recoAxisLabel,3)+"/"+getStringEntry(recoAxisLabel,4));
      axisLabel_.push_back(""+getStringEntry(recoAxisLabel,1)+"/"+"#frac{d#sigma}{d"+label+"} "+label2+"/"+getStringEntry(recoAxisLabel,3)+"/"+getStringEntry(recoAxisLabel,4));
      if(decayChannel=="electron") axisLabel_[axisLabel_.size()-1].ReplaceAll("#mu", "e");
      // configure xSec plot histo style
      histogramStyle(*histo_[xSec][kData], kData, false);
      histogramStyle(*histo_[xSec][kSig ], kSig , false);
      if(compare){
	histo_[xSec][kData]->SetLineColor  (38);
	histo_[xSec][kData]->SetMarkerColor(38);
	histo_[xSec][kData]->SetMarkerStyle(33);
	histo_[xSec][kSig ]->SetLineColor  (kOrange);
	histo_[xSec][kSig ]->SetMarkerColor(kOrange);
      }
      // restrict axis
      setXAxisRange(histo_[xSec][kData], variable);
      setXAxisRange(histo_[xSec][kSig ], variable);
      if(!compare)++NXSec;
    }
  }

  // ---
  //    total inclusive cross section (ttbar->X) determination
  // ---
  double xSecResult=0;
  double effA=0;
  double BR=0;
  ++NXSec;
  // get event yields
  // careful: plot contains leptonic and hadronic top -> *0.5
  double Ndata  = 0.5 * dataYield ->Integral(0, dataYield ->GetNbinsX()+1);
  double NSig   = 0.5 * SigYield  ->Integral(0, SigYield  ->GetNbinsX()+1);
  double NBGtop = 0.5 * BkgYield  ->Integral(0, BkgYield  ->GetNbinsX()+1); 
  double NBGZ   = 0.5 * ZjetYield ->Integral(0, ZjetYield ->GetNbinsX()+1);
  double NBGW   = 0.5 * WjetYield ->Integral(0, WjetYield ->GetNbinsX()+1);
  double NBGsTop= 0.5 * STopYield ->Integral(0, STopYield ->GetNbinsX()+1);
  double NBGVV  = 0.5 * DiBosYield->Integral(0, DiBosYield->GetNbinsX()+1);
  double NBGQCD = 0.5 * QCDYield  ->Integral(0, QCDYield  ->GetNbinsX()+1);
  double NBG= NBGZ+NBGW+NBGsTop+NBGVV+NBGQCD; //other ttbar BG is handled by a signal fraction (see below sigFrac)
  double NAllMC=NSig+NBGtop+NBG;
  double sigFrac=NSig/(NSig+NBGtop);
  // print event composition
  if(verbose>0&&systematicVariation==sysNo){ 
    std::cout << std::endl;
    std::cout << "events expected from MC: " << NAllMC << std::endl;
    std::cout << "expected event composition:"   << std::endl;
    std::cout << "ttbar SG:  " << std::setprecision(4) << std::fixed << NSig   / NAllMC;
    std::cout << " (" << lumiweight(kSig, luminosity, systematicVariation, decayChannel) << "*";
    std::cout << NSig/lumiweight(kSig, luminosity, systematicVariation, decayChannel) << "=" << NSig    << ") " << std::endl;
    std::cout << " (" << "mean event SF: " << NSig/(lumiweight(kSig, luminosity, systematicVariation, decayChannel)*(0.5*SigYield->GetEntries())) << ")" << std::endl;
    std::cout << "ttbar BG:  " << std::setprecision(4) << std::fixed << NBGtop / NAllMC; 
    std::cout << " (" << lumiweight(kBkg, luminosity, systematicVariation, decayChannel) << "*";
    std::cout << NBGtop/lumiweight(kBkg, luminosity, systematicVariation, decayChannel) << "=" << NBGtop << ") " << std::endl;
    std::cout << "single top:" << std::setprecision(4) << std::fixed << NBGsTop/ NAllMC; 
    std::cout << " (" << NBGsTop << ") " << std::endl;
    std::cout << "W+jets    :" << std::setprecision(4) << std::fixed << NBGW   / NAllMC; 
    std::cout << " (" << lumiweight(kWjets, luminosity, systematicVariation, decayChannel) << "*";
    std::cout << NBGW/lumiweight(kWjets, luminosity, systematicVariation, decayChannel) << "=" << NBGW << ") " << std::endl;
    std::cout << "QCD       :" << std::setprecision(4) << std::fixed << NBGQCD / NAllMC; 
    std::cout << " (" << lumiweight(kQCD, luminosity, systematicVariation, decayChannel) << "*";
    std::cout << NBGQCD/lumiweight(kQCD, luminosity, systematicVariation, decayChannel) << "=" << NBGQCD << ") " << std::endl;
    std::cout << "Z+jets    :" << std::setprecision(4) << std::fixed << NBGZ   / NAllMC;
    std::cout << " (" << lumiweight(kZjets, luminosity, systematicVariation, decayChannel) << "*";
    std::cout << NBGZ/lumiweight(kZjets, luminosity, systematicVariation, decayChannel) << "=" << NBGZ << ") " << std::endl;
    std::cout << "Diboson   :" << std::setprecision(4) << std::fixed << NBGVV  / NAllMC; 
    std::cout << " (" << NBGVV << ") " << std::endl;
  }
  // efficiency calculation
  double NGenPhaseSpace=0.5 * GenPhaseSpace->Integral(0, GenPhaseSpace->GetNbinsX()+1);
  double eff=NSig/NGenPhaseSpace;
  // acceptance
  double NGen          =0.5 * GenInclusive ->Integral(0, GenInclusive ->GetNbinsX()+1);
  effA=NSig/NGen;
  double A= effA/eff;
  // branching ratio
  // careful: the xSec here needs to be 
  // consistent with the one in lumiweight()
  BR=NGen*1.0/(ttbarCrossSection*luminosity);
  //  double BR2=12.0/81.0;
  // calculate xSec
  xSecResult= ( Ndata-NBG ) * sigFrac / ( eff*A*luminosity*BR );
  double sigmaxSec = sqrt( Ndata ) * sigFrac / ( eff*A*luminosity*BR );
  // text output
  if(verbose>0){ 
    std::cout << std::endl;
    std::cout << "systematic variation:" << sysLabel(systematicVariation) << std::endl;
    std::cout << "lumi[pb]:      " << luminosity << std::endl;
    std::cout << "N(Data):       " << Ndata << std::endl;
    std::cout << "N(BG):         " << NBG   << std::endl;
    std::cout << "eff:           " << eff   << std::endl;
    std::cout << "A:             " << A     << std::endl;
    std::cout << "BR MC:         " << BR    << std::endl;
    std::cout << "ttbar sigfrac: " << sigFrac << std::endl;
    std::cout << "inclusive cross section";
    if(extrapolate) std::cout << " (extrapolated)";
    std::cout << " [pb]: ";
    std::cout << xSecResult << " +/- " << sigmaxSec << "(stat.)" << std::endl;
    std::cout << std::endl;
  }
  // create histo
  TString inclName = "xSec/inclusive";
  histo_[inclName][kData] = new TH1F( "inclusivekData", "inclusivekData", 1, 0., 1.0);
  histo_[inclName][kData]->SetBinContent(1, xSecResult     );
  histo_[inclName][kData]->SetBinError  (1, sigmaxSec);
  // add plot to list of all plots
  plotList_.push_back(inclName);
  // configure xSec plot histo style
  histogramStyle(*histo_[inclName][kData], kData, false);
  axisLabel_.push_back(" /#sigma(t#bar{t}#rightarrowX)[pb]/0/1");
  // theory xSec
  histo_[inclName][kSig]=(TH1F*)histo_[inclName][kData]->Clone("xSec/inclusiveTheory");
  histo_[inclName][kSig]->SetBinContent(1, 157.5);
  histo_[inclName][kSig]->SetBinError  (1, 0);
  histogramStyle(*histo_[inclName][kSig ], kSig , false);

  // ---
  //    differential normalized cross section (phase space) determination
  // ---
  if(!SVDunfold||compare){
    // loop all variables
    for(unsigned int number=0; number<xSecVariables_.size(); ++number){
      TString variable=xSecVariables_[number];
      TString label =getStringEntry(xSecLabel_[number],1);
      TString label2=getStringEntry(xSecLabel_[number],2);
      if(label2=="[#frac{GeV}{c}]") label2="#left[#left(#frac{GeV}{c}#right)^{-1}#right]";
      else if(label2=="[#frac{GeV}{c^{2}}]") label2="#left[#left(#frac{GeV}{c^{2}}#right)^{-1}#right]";
      else if(label2==" ") label2="";
      TString xSec ="xSecNorm/";
      if(compare) xSec+="BBB";
      xSec+=variable;
      bool calculateXSec=true;
      // loop samples 
      for(unsigned int sample=kSig; sample<=kData; ++sample){
	// check if reco MC plot and data event yield plots are available
	if(!plotExists(histo_, "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable, sample)){
	  calculateXSec=false;
	}
      }
      // check if efficiency plot is available
      if(!plotExists(histo_, "efficiency/"+variable, kSig)){
	calculateXSec=false;
      }
      if(calculateXSec){
	// a) differential norm XSec from data
	// get data plot
	TString name=TString(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData]->GetName())+"kData";
	histo_[xSec][kData]=(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData]->Clone(name));
	// total number of data events for this variable
	double NdataVariable=getInclusiveXSec(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData],verbose-1);
	// total number of BG events for this variable
	double NBGVariable=getInclusiveXSec(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kWjets],verbose-1);
	// NBGVariable+=getInclusiveXSec(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kBkg],verbose-1);
	// BG from other ttbar events is treated in the signal fraction
	NBGVariable+=getInclusiveXSec(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSTop ],verbose-1);
	NBGVariable+=getInclusiveXSec(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kDiBos],verbose-1);
	NBGVariable+=getInclusiveXSec(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kQCD  ],verbose-1);
	NBGVariable+=getInclusiveXSec(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kZjets],verbose-1);
	// ttbar signal fraction
	double NttbarAll=getInclusiveXSec(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSig],verbose-1);
	NttbarAll+=getInclusiveXSec(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kBkg],verbose-1);
	double sigFracVariable=getInclusiveXSec(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSig],verbose-1);
	sigFracVariable/=NttbarAll;
	// inclusive efficiency (* A) for this variable
	double effIncl= getInclusiveXSec(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable ][kSig],verbose-1);
	effIncl/= getInclusiveXSec(histo_["analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/"+variable][kSig],verbose-1);
	// loop bins
	for(int bin =0; bin<=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData]->GetNbinsX()+1; ++bin){
	  // for inclusive values of xSecResult, effA, BR, Ndata and NBG 
	  // which are used in the calculation are taken from section
	  // "total inclusive cross section (ttbar->X) determination" above
	  // remark: event numbers are taken from yield plots-> *binwidth
	  // get data entries in bin

	  // get binwidth
	  double binwidth=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData]->GetBinWidth(bin);
	  double NdataBin=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData]->GetBinContent(bin);
	  NdataBin*=binwidth;
	  // get BG in bin
	  double NBGBin=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kZjets]->GetBinContent(bin);
	  //NBGBin+=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kBkg]->GetBinContent(bin);
	  // BG from other ttbar events is treated in the signal fraction
	  NBGBin+=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kWjets]->GetBinContent(bin);
	  NBGBin+=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSTop ]->GetBinContent(bin);
	  NBGBin+=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kDiBos]->GetBinContent(bin);
	  NBGBin+=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kQCD  ]->GetBinContent(bin);
	  NBGBin*=binwidth;
	  // ttbar signal fraction
	  double NttbarAllBin=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSig]->GetBinContent(bin);
	  NttbarAllBin      +=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kBkg]->GetBinContent(bin);
	  double sigFracBin=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSig]->GetBinContent(bin);
	  sigFracBin/=NttbarAllBin;
	  if(!isfinite(sigFracBin)||isnan(sigFracBin)) sigFracBin=1;
	  // calculate Ni = number of ttbar only events in bin from data
	  double Ni= NdataBin-NBGBin;
	  // calculate Ntot = sum_i(Ni) number of signal only events from data for this variable
	  double Ntot =NdataVariable-NBGVariable;
	  // get eff*A in bin
	  double effABin=(histo_["efficiency/"+variable][kSig])->GetBinContent(bin);
	  // calculate cross section for this bin
	  double xSecBin = (Ni/Ntot) * (sigFracBin/sigFracVariable) * (effIncl/effABin) * (1/binwidth);
	  // calculate complete error
	  double Nierror=sqrt(NdataBin); // the error of NBG is treated as systematic variation
	  double sumErrorNjSquare = 0; // sum(j,i!=j) [ errorNj*errorNj ]
	  for(int bin2=1; bin2<=histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData]->GetNbinsX()+1; ++bin2){
	    if(bin2!=bin){    
	      double errorNj = sqrt( histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData]->GetBinContent(bin2) 
				     * (histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData]->GetBinWidth(bin2)) );   
	      // remark: Nj=NdataBinj-NBGBinj, as above, the error of NBGBinj is treated 
	      // as systematic variation and therefore not incorporated here
	      sumErrorNjSquare += errorNj*errorNj;
	    }
	  }
	  // calculate complete error
	  double xSecBinError = sqrt( ((Ntot - Ni)*(Ntot - Ni)*Nierror*Nierror) + (Ni*Ni*sumErrorNjSquare) );
	  xSecBinError/= (Ntot*Ntot);
	  xSecBinError*= (effIncl/effABin) * (sigFracBin/sigFracVariable) * (1/binwidth);
	  // check for ambiguities
	  if(!isfinite(xSecBin)||isnan(xSecBin)){
	    if(verbose>1){ 
	      std::cout << "bin " << bin << " in ";
	      std::cout << "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable;
	      std::cout << "gives no valid cross section!" << std::endl;
	      std::cout << "!will set this bin to 0!" << std::endl;
	    }
	    xSecBin=0;	 
	    xSecBinError=0;
	  }
	  // set underflow/overflow to 0
	  // because of infinite binwidth
	  if(bin==0||bin==histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kData]->GetNbinsX()+1){
	    xSecBinError=0;
	    xSecBin=0;
	  }
	  // check calculation for one example bin
	  TString testVar  = "ttbarPt";
	  TString testVar2 = "ttbarMass";
	  int testBin=0;
	  if(verbose>0&&xSecBin!=0&&(variable==testVar||variable==testVar2)&&bin==testBin){
	    std::cout << std::endl << "differential normalized xSec ";
	    std::cout << variable+" bin " << bin << ":" << std::endl;
	    std::cout << "binwidth:             " << std::setprecision(3) << std::fixed << binwidth << std::endl;
	    std::cout << "Ndata(bin):           " << std::setprecision(3) << std::fixed << NdataBin << std::endl;
	    std::cout << "NBG(bin):             " << std::setprecision(3) << std::fixed << NBGBin << std::endl;
	    std::cout << "eff*A(bin):           " << std::setprecision(3) << std::fixed << effABin << std::endl;
	    std::cout << "ttbar sig frac(bin):  " << std::setprecision(3) << std::fixed << sigFracBin << std::endl;
	    std::cout << "Ndata(incl):          " << std::setprecision(3) << std::fixed << NdataVariable << std::endl;
	    std::cout << "NBG(incl):            " << std::setprecision(3) << std::fixed << NBGVariable << std::endl;
	    std::cout << "eff*A(incl):          " << std::setprecision(3) << std::fixed << effIncl << std::endl;
	    std::cout << "ttbar sig frac(incl): " << std::setprecision(3) << std::fixed << sigFracVariable << std::endl;
	    std::cout << "result:               " << std::setprecision(3) << std::fixed << xSecBin << std::endl;
	    if(extrapolate){
	      double xSecBinFromDiffAndIncl= histo_["xSec/"+variable][kData]->GetBinContent(bin)/(xSecResult*BR);
	      std::cout << "from diff and incl. xSec: ";
	      std::cout << std::setprecision(3) << std::fixed << xSecBinFromDiffAndIncl << std::endl;
	      std::cout << "ratio: " << xSecBin/xSecBinFromDiffAndIncl << std::endl;
	    }
	  }
	  // apply cross section and error to plot
	  histo_[xSec][kData]->SetBinContent(bin, xSecBin     );
	  histo_[xSec][kData]->SetBinError  (bin, xSecBinError);
	  //saveToRootFile(outputFileName, histo_[xSec][kData], true, verbose-1,"xSec/NormXSec");
	}
      }
      if(verbose>1){
	std::cout << "integral diff.norm.data distribution (" << variable << "): ";
	std::cout << getInclusiveXSec(histo_[xSec][kData],verbose-1) << std::endl;
      }
      // b) differential normalized XSec from Signal(MC prediction)
      histo_[xSec][kSig]=(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable][kSig]->Clone());
      DivideYieldByEfficiencyAndLumi(histo_[xSec][kSig], (TH1F*)(histo_["efficiency/"+variable][kSig]), luminosity, 0);
      double XSecInclTheoPS= getInclusiveXSec(histo_[xSec][kSig], verbose-1);
      // exclude underflow and overflow bins because they are negligible and treated wrong
      XSecInclTheoPS-=histo_[xSec][kSig]->GetBinContent(0);
      XSecInclTheoPS-=histo_[xSec][kSig]->GetBinContent(histo_[xSec][kSig]->GetNbinsX()+1);
      histo_[xSec][kSig]->Scale(1/(XSecInclTheoPS));
      if(verbose>1){
	std::cout << "integral diff.norm.MC distribution (" << variable << "): ";
	std::cout << getInclusiveXSec(histo_[xSec][kSig],verbose-1) << std::endl;
      }
      // add plot to list of plots
      plotList_.push_back(xSec);
      // add axis configuration
      unsigned int positionOfRecoAxisLabel = positionInVector(plotList_, "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable);
      TString recoAxisLabel =axisLabel_[positionOfRecoAxisLabel];
      recoAxisLabel.ReplaceAll("KinFit ","");
      //    axisLabel_.push_back(""+getStringEntry(recoAxisLabel,1)+"/"+"#frac{1}{#sigma}"+" #frac{d#sigma}{d"+label+"} "+label2+" (t#bar{t}#rightarrow #mu prompt"+")/"+getStringEntry(recoAxisLabel,3)+"/"+getStringEntry(recoAxisLabel,4));
      axisLabel_.push_back(""+getStringEntry(recoAxisLabel,1)+"/"+"#frac{1}{#sigma}"+" #frac{d#sigma}{d"+label+"} "+label2+"/"+getStringEntry(recoAxisLabel,3)+"/"+getStringEntry(recoAxisLabel,4));
      if(decayChannel=="electron") axisLabel_[axisLabel_.size()-1].ReplaceAll("#mu", "e");
      // configure xSec plot histo style
      histogramStyle(*histo_[xSec][kData], kData, false);
      histogramStyle(*histo_[xSec][kSig ], kSig , false);
      if(compare){
	histo_[xSec][kData]->SetLineColor  (38);
	histo_[xSec][kData]->SetMarkerColor(38);
	histo_[xSec][kData]->SetMarkerStyle(33);
	histo_[xSec][kSig ]->SetLineColor  (kOrange);
	histo_[xSec][kSig ]->SetMarkerColor(kOrange);
      }
      // restrict axis
      setXAxisRange(histo_[xSec][kData], variable);
      setXAxisRange(histo_[xSec][kSig ], variable);
      if(!compare) ++NXSec;
    }
  }

  // =======================================
  //    use SVD unfolding for cross sections
  // =======================================
  if(SVDunfold){
    // loop all variables
    for(unsigned int number=0; number<xSecVariables_.size(); ++number){
      // prepare style for xSec plots
      TString variable=xSecVariables_[number];
      TString labelNorm =getStringEntry(xSecLabel_[number],1);
      TString label2Norm=getStringEntry(xSecLabel_[number],2);
      if(label2Norm=="[#frac{GeV}{c}]") label2Norm="#left[#left(#frac{GeV}{c}#right)^{-1}#right]";
      else if(label2Norm=="[#frac{GeV}{c^{2}}]") label2Norm="#left[#left(#frac{GeV}{c^{2}}#right)^{-1}#right]";
      else if(label2Norm==" ") label2Norm="";
      TString label =getStringEntry(xSecLabel_[number],1);
      TString label2=getStringEntry(xSecLabel_[number],2);
      if(label2=="[#frac{GeV}{c}]")          label2="#left[pb #left(#frac{GeV}{c}#right)^{-1}#right]";
      else if(label2=="[#frac{GeV}{c^{2}}]") label2="#left[pb #left(#frac{GeV}{c^{2}}#right)^{-1}#right]";
      else if(label2==" ") label2="[pb]";
      TString xSec ="xSec/"+variable;
      TString xSecNorm ="xSecNorm/"+variable;
      // -----------------------------------
      // check availablility of input histos
      // -----------------------------------
      bool calculateXSec=true;
      // check if BG reco plot is available
      if(!plotExists(histo_, "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable, kAllMC)){
	std::cout << "warning: plot " << "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable << " not found for BG" << std::endl;
	calculateXSec=false;
      }
      // check if ttbar BG reco plot is available
      if(!plotExists(histo_, "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable, kBkg)){
	std::cout << "warning: plot " << "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable << " not found for BG" << std::endl;
	calculateXSec=false;
      }
      // check if data event yield is available
      if(!plotExists(histo_, "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable, kData)){
	std::cout << "warning: plot " << "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable << " not found for data" << std::endl;
	calculateXSec=false;
      }
      // check if signal reco plot is available
      if(!plotExists(histo_, "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable, kSig)){
	std::cout << "warning: plot " << "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable << " not found for signal" << std::endl;
	calculateXSec=false;
      }
      // check if signal gen level plot is available
      if(!plotExists(histo_, "analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/raw"+variable, kSig)){
	std::cout << "warning: plot " << "analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/raw"+variable << " not found for signal" << std::endl;
	calculateXSec=false;
      }
      // check if response matrix plot is available
      if(!plotExists(histo2_, "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable+"_", kSig)){
	std::cout << "warning: plot " << "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable+"_" << " not found for signal" << std::endl;
	calculateXSec=false;
      }
      // ----------------
      // configure labels
      // ----------------
      // particle
      TString particle="";
      variable.Contains("ttbar") ? particle="t#bar{t}" : (variable.Contains("lep") ? particle="lepton" : (variable.Contains("top") ? particle="t and #bar{t}" : (variable.Contains("bq") ? particle="b and #bar{b}" : particle="unknown") ) );
    
      TString particleTex=particle;
      particle.ReplaceAll("#","");
      particle.ReplaceAll("{","");
      particle.ReplaceAll("}","");
      // quantity
      TString quantity="";
      variable.Contains("Mass") ? quantity="mass" : (variable.Contains("Pt") ? quantity="p_{t}" : (variable.Contains("Eta") ? quantity="#eta" : (variable.Contains("Y") ? quantity="y" : quantity="unknown") ) );
      TString quantityTex=quantity;
      quantity.ReplaceAll("#","");
      quantity.ReplaceAll("{","");
      quantity.ReplaceAll("}","");
      // decay channel
      TString channelTex="#mu";
      if(decayChannel=="electron") channelTex="e";
      TString rootFile="";
      TString psFile="";
      //if(save){ 
      rootFile="diffXSecUnfoldTopSemi";
      if(decayChannel=="muon"    ) rootFile+="Mu";
      if(decayChannel=="electron") rootFile+="Elec";
      rootFile+=dataSample+".root";
      psFile=outputFolder+"unfolding/unfolding"+variable+".ps";
      //}
      TString special="";
      // -----------
      // get binning
      // -----------
      // a) filter relevant bins
      std::vector<double> relevantBins_;
      // loop all entries in binning_
      for(unsigned int bin=0; bin<binning_[variable].size(); ++bin){
	bool relevant=true;
	// exclude first bin for some variables
	if(bin==0&&(variable=="topY"||variable=="ttbarY"||variable=="ttbarMass"||variable=="lepEta"||variable=="lepPt"||variable=="bqEta"||variable=="bqPt")) relevant=false;
	// exclude last bin for some variables
	if(bin==binning_[variable].size()-1&&(variable=="topY"||variable=="ttbarY"||variable=="lepEta"||variable=="bqEta"||variable=="topPt"||variable=="lepPt"||variable=="bqPt")) relevant=false;
	if(relevant) relevantBins_.push_back(binning_[variable][bin]); 
      }
      // b) calculate number of considered bins 
      int unfoldbins=relevantBins_.size()-1; // NB: N(bins)=NbinEdges-1 
      // c) refill bin edges to array
      double bins[relevantBins_.size()];
      for(unsigned int bin=0; bin<relevantBins_.size(); ++bin){
	bins[bin]=relevantBins_[bin]; 
	if(verbose>1) std::cout << "bin " << bin << ": " << bins[bin]<< std::endl;
      }
      if(verbose>1) std::cout << "bins used for unfolding: " << unfoldbins << std::endl;

      // ----------------------
      // use unfolding machine
      // ----------------------
      if(calculateXSec){
	TH1D* unfoldedData=new TH1D();
	TopSVDFunctions::SVD_Unfold(
	// Data Input (RAW Data including the background)
	*&histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable][kData],                  
	// Background (will be substracted from data)
	*&histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable][kAllMC],
	// ttbar background only (used to calculate a ttbar signal 
	// fraction instead of subtracting the yield which depends 
	// on the inclusive ttbar cross section.) 
	// Note: if 0 pointer is handed over 
	*&histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable][kBkg],
	// Generated MC
	*&histo_["analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/raw"+variable][kSig],
	// Reconstructed MC
	*&histo_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable][kSig],
	// Response Matrix 
	*&histo2_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/raw"+variable+"_"][kSig],
	// Binning for the unfolding
	bins, 
	// Number of bins for unfolding (not counting OF bins !!!)
	unfoldbins, 
	// Regularization parameter
	regParameter(variable, decayChannel, 2, true),  //unfoldbins+2,
	// Regularization Modus 
	// regMode=0 is standard BBB unfolding, no regularization
	// regMode=1 is SVD Unfolding, regularization by means of the "K" Parameter. Specify the k Parameter in 'regPar'
	//           -> NOTE: tau=false otion is needed when using function "regParameter"
	// regMode=2 is SVD Unfolding, regularization by means of the "TAU" Parameter. Specify the tau Parameter in 'regpar'
	//           -> NOTE: tau=true otion is needed when using function "regParameter"
	// regMode=3 is SVD Unfolding. A scan for the optimal tau parameter is performed. The scan is performed around
	// a "center value" for k, to be specified in 'regpar'. Note: The scan may take a while!
	// regMode=4 is SVD Unfolding. A scan for the optimal k parameter is performed. The scan is performed around
	// a "center value" for tau, to be specified in 'regpar'
	// Note: The scan may take a while! 
	2,                            
	// Returned: Unfolded Distribution              
	unfoldedData,
	// Specify Name for the Channel ("mumu", "emu", "ee" ...)
	(TString)decayChannel,  
	// Specify Name for the Physics Object ("Top", "Jets", "Leptons")      
	particle,
	// Specify Name for the Quantity ("Eta", "Pt", or "Mass");      
	quantity,
	// Specify Name for special run of unfolding
	special, 
	// Nicely formatted name for the channel
	channelTex,
	// Nicely formatted name for the physics object 
	particleTex,
	// Nicely formatted name for ithe quantity
	quantityTex,
	// Nicely formatted name indicating some special condition 
	special,
	// If specified, plots will be saved in ROOT File
	rootFile,
	// If specified, plots will be saved in PS File
	psFile,
	// output
	// verbose=0: no output at all
	// verbose=1: standard output
	// verbose=2: debug output
	0
	);
	// ---------------------------------------------
	// remaining steps for cross section calculation
	// ---------------------------------------------
	// use unfolded event yield as input
	histo_[xSec][kData]=(TH1F*)unfoldedData->Clone();
	// divide by binwidth
	histo_[xSec][kData] = divideByBinwidth(histo_[xSec][kData], verbose-1);
	// divide by luminosity 
	histo_[xSec][kData]->Scale(1./(luminosity));	
	// Normalization
	// NB: exclude underflow and overflow bins because they are negligible and treated wrong
	histo_[xSecNorm][kData]=(TH1F*)histo_[xSec][kData]->Clone();
	double inclXSecPS =getInclusiveXSec(histo_[xSec][kData],verbose-1);
	inclXSecPS-=histo_[xSec][kData]->GetBinContent(0);
	inclXSecPS-=histo_[xSec][kData]->GetBinContent(histo_[xSec][kData]->GetNbinsX()+1);
	histo_[xSecNorm][kData]->Scale(1./inclXSecPS);
	// --------------
	// styling issues
	// --------------
	// add plot to list of plots
	plotList_.push_back(xSec);
	plotList_.push_back(xSecNorm);
	// add axis configuration
	unsigned int positionOfRecoAxisLabel = positionInVector(plotList_, "analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+variable);
	TString recoAxisLabel =axisLabel_[positionOfRecoAxisLabel];
	recoAxisLabel.ReplaceAll("KinFit ","");
	axisLabel_.push_back(""+getStringEntry(recoAxisLabel,1)+"/"+"#frac{d#sigma}{d"+label+"} "+label2+"/"+getStringEntry(recoAxisLabel,3)+"/"+getStringEntry(recoAxisLabel,4));
	if(decayChannel=="electron") axisLabel_[axisLabel_.size()-1].ReplaceAll("#mu", "e");
	axisLabel_.push_back(""+getStringEntry(recoAxisLabel,1)+"/"+"#frac{1}{#sigma}"+" #frac{d#sigma}{d"+labelNorm+"} "+label2Norm+"/"+getStringEntry(recoAxisLabel,3)+"/"+getStringEntry(recoAxisLabel,4));
	if(decayChannel=="electron") axisLabel_[axisLabel_.size()-1].ReplaceAll("#mu", "e");
	// configure xSec plot histo style
	histogramStyle(*histo_[xSecNorm][kData], kData, false);
	// restrict axis
	setXAxisRange(histo_[xSecNorm][kData], variable);
	NXSec=NXSec+2;
	// thicker error bars for comparison
	if(compare){
	  histo_[xSecNorm][kData]->SetLineWidth(4);
	  histo_[xSec    ][kData]->SetLineWidth(4);
	}
	// ------------------------------------------------------
	// calculate differential XSec from Signal(MC prediction)
	// ------------------------------------------------------
	// get PS gen event yield/binwidth plots
	histo_[xSec][kSig]=(TH1F*)(histo_["analyzeTopPartonLevelKinematics"+PS+sysInputGenFolderExtension+"/"+variable][kSig]->Clone());
	// divide by lumi
	histo_[xSec][kSig]->Scale(1/luminosity);
	// Normalization
	histo_[xSecNorm][kSig]=(TH1F*)(histo_[xSec][kSig]->Clone());
	// NB: exclude underflow and overflow bins because they are negligible and treated wrong
	double XSecInclTheoPS= getInclusiveXSec(histo_[xSec][kSig],verbose-1);
	XSecInclTheoPS-=histo_[xSec][kSig]->GetBinContent(0);
	XSecInclTheoPS-=histo_[xSec][kSig]->GetBinContent(histo_[xSec][kSig]->GetNbinsX()+1);
	histo_[xSecNorm][kSig]->Scale(1/(XSecInclTheoPS));
	// style
	histogramStyle(*histo_[xSec    ][kSig ], kSig , false);
	histogramStyle(*histo_[xSecNorm][kSig ], kSig , false);
	if(compare){
	  histo_[xSec    ][kSig ]->SetLineWidth  (3);
	  histo_[xSecNorm][kSig ]->SetLineWidth  (3);
	}
	setXAxisRange(histo_[xSec][kSig ], variable);
	setXAxisRange(histo_[xSecNorm][kSig ], variable);
      }    
    }
  }

  // ===============================================================
  //  Errors for uncertainty bands from ttbar Xsec and luminosity
  // ===============================================================
  
  if(verbose>0) std::cout << std::endl << " Start calculating error bands for 1D plots .... ";
  makeUncertaintyBands(histo_, histoErrorBand_, plotList_, N1Dplots);
  if(verbose>0) std::cout << " .... Finished." << std::endl; 

  // =========================================
  //  Create one legend for all 1D histos
  // =========================================
  unsigned int Nlegends=0;  
  TLegend *leg  = new TLegend();  
  TLegend *leg0 = new TLegend(0.05, 0.15, 1.05, 0.9);
  Nlegends+=2;
  leg ->SetFillStyle(0);
  leg ->SetBorderSize(0);
  leg ->SetTextSize(0.03);
  leg ->SetTextAlign(12);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Kin. Fit (after selection)");
  // fill in contributing sample
  // data is to be first entry
  bool TwoThousandElevenData=false;
  TString lumilabel = Form("%3.2f fb^{-1}",luminosity/1000);
  if(luminosity>50.0) TwoThousandElevenData=true;
  else lumilabel=Form("%2.0f pb^{-1}",luminosity);    
  leg ->AddEntry(histo_[plotList_[plotList_.size()-1]][kData], sampleLabel(kData,decayChannel,TwoThousandElevenData),"P");
  leg0->AddEntry(histo_[plotList_[plotList_.size()-1]][kData], sampleLabel(kData,decayChannel,TwoThousandElevenData)+", "+lumilabel,"P");
  // now loop over MC samples
  for(unsigned int sample=kSig; sample<kData; ++sample){
    // check if sampe exists in at least one plot
    bool exit=false;
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size()-1; ++plot){  // <plotList_.size()-1, because last entry is for data (see above)
      // if found: add entry to legend
      if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)&&(!exit)){
	leg ->AddEntry(histo_[plotList_[plot]][sample], sampleLabel(sample,decayChannel), "F");
	leg0->AddEntry(histo_[plotList_[plot]][sample], sampleLabel(sample,decayChannel), "F");
	exit=true;
      }
    }
  }
  // add entry for uncertainty to legends
  if (histoErrorBand_.size() > 0 && plotList_.size() > 0){
      leg ->AddEntry(histoErrorBand_[plotList_[0]],"Uncertainty","F");
      leg0->AddEntry(histoErrorBand_[plotList_[0]],"Uncertainty","F");
  }
  
  // create in canvas legend for residuals
  TLegend *legPull = new TLegend(0.6, 0.5, 0.96, 0.9);
  legPull->SetFillStyle(0);
  legPull->SetBorderSize(0);
  legPull->SetTextSize(0.04);
  //legPull->SetEntrySeparation(0.45);
  legPull->AddEntry((TObject*)0, "#bf{rel. variation fit}", "");
  if(histo_.count("analyzeHypoKinFitLepton/leptonPullPtKinFitRec")>0&&histo_["analyzeHypoKinFitLepton/leptonPullPtKinFitRec"].count(kSig)>0){
    legPull->AddEntry(histo_["analyzeHypoKinFitLepton/leptonPullPtKinFitRec"     ][kSig], "(reco - fit) / reco", "L");
  }
  legPull->AddEntry((TObject*)0, "#bf{residuals}", "");
  if(histo_.count("analyzeHypoKinFitLepton/leptonPullPtRecPartonTruth")>0&&histo_["analyzeHypoKinFitLepton/leptonPullPtRecPartonTruth"].count(kSig)>0){
    legPull->AddEntry(histo_["analyzeHypoKinFitLepton/leptonPullPtRecPartonTruth"][kSig], "#splitline{before KinFit}{reco wrt. parton}"      , "L");
  }  
  if(histo_.count("analyzeHypoKinFitLepton/leptonPullPtKinFitPartonTruth")>0&&histo_["analyzeHypoKinFitLepton/leptonPullPtKinFitPartonTruth"].count(kSig)>0){
    legPull->AddEntry(histo_["analyzeHypoKinFitLepton/leptonPullPtKinFitPartonTruth"][kSig], "#splitline{after KinFit}{fitted wrt. parton}"       , "L");
  }

  // ---
  //     print information about plots, canvas and legends
  // ---
  if(verbose>1){
    std::cout << std::endl << "# different plots requested: 1D + 2D = ";
    std::cout << N1Dplots + N2Dplots << " ( " << N1Dplots << " + " << N2Dplots << " )" << std::endl;
    std::cout << "1D plots for different samples will be drawn ";
    std::cout << "into same canvas as stacked plot" << std::endl;
    std::cout << "every 2D plot will be drawn into a seperate canvas" << std::endl;
    std::cout << "#Canvas for plots: " << Nplots << std::endl;
    std::cout << "#legends: " << Nlegends << std::endl;
    std::cout << "every legend will be drawn into a seperate canvas" << std::endl;
    std::cout << "#Canvas = #plots + #legends: " << Nplots+Nlegends << std::endl<< std::endl;
  }

  // ---
  //    create canvas
  // ---
  std::vector<TCanvas*> plotCanvas_;
  // entries added when printing is done

  // ---
  //    change 1D plots into stack plots
  // ---
  // loop plots 
  if(verbose>2) std::cout << std::endl;
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    // show kinfit permutation plot as relative plot for signal
    // and delete this plot for all other samples 
    if(plotList_[plot].Contains("qAssignment")){
      TString permutationLabel=plotList_[plot];
      for(unsigned int sample=kBkg; sample<=kData; ++sample){
	if(histo_[permutationLabel].count(sample)>0)  histo_[permutationLabel].erase(sample);
      }
      if(histo_[permutationLabel].count(kSig)>0){ 
	histo_[permutationLabel][kSig]->Scale(1./histo_[permutationLabel][kSig]->Integral(0, histo_[permutationLabel][kSig]->GetNbinsX()));
	axisLabel_[plot].ReplaceAll("events","relative fraction of events");
	histogramStyle( *histo_[permutationLabel][kSig], kSig, true);
      }
    }
    // pull plots as line, signal only, no stack, relative 
    else if(plotList_[plot].Contains("analyzeHypoKinFitLepton")||plotList_[plot].Contains("analyzeHypoKinFitMET")||plotList_[plot].Contains("analyzeHypoKinFitJets")){
      TString pullLabel=plotList_[plot];
      for(unsigned int sample=kBkg; sample<=kData; ++sample){
	if(histo_[pullLabel].count(sample)>0)  histo_[pullLabel].erase(sample);
      }
      if(histo_[pullLabel].count(kSig)>0){ 
	histo_[pullLabel][kSig]->Scale(1./histo_[pullLabel][kSig]->Integral(0, histo_[pullLabel][kSig]->GetNbinsX()));
	axisLabel_[plot].ReplaceAll("Frequency","event fraction");
	histogramStyle( *histo_[pullLabel][kSig], kSig, false);
	histo_[pullLabel][kSig]->SetLineWidth(3);
	if(pullLabel.Contains("RecPartonTruth")) histo_[pullLabel][kSig]->SetLineColor(kBlue );
	if(pullLabel.Contains("KinFitRec"     )) histo_[pullLabel][kSig]->SetLineColor(kBlack);
      }
    }
    // otherwise: all 1D plots will become stacked plots
    else createStackPlot(plotList_, histo_, plot, N1Dplots, verbose-1, decayChannel);
  }
  if(verbose>2) std::cout << std::endl;

  // FIXME MARTIN BBB Cross check
  //for(unsigned int plot=0; plot<plotList_.size(); ++plot){
  //  std::cout << plotList_[plot] << std::endl;
  //}

  // ---
  //    do the printing
  // ---
  // a) for plots
  // loop plots
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    bool first=true;
    // loop samples
    for(unsigned int sample=kSig; sample<=kData; ++sample){
      // a1) for 1D event yields, efficiency and cross section plots (existing)
      if((plot<N1Dplots)||(plot>=N1Dplots+N2Dplots)){
	// check if plot is existing
	// draw BBB xSec control plots in same canvas with SVD result
	if(((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0))&&!plotList_[plot].Contains("BBB")){
	  // draw all pull distributions in same canvas if RecPartonTruth pull is called
	  if((!plotList_[plot].Contains("Pull")||plotList_[plot].Contains("RecPartonTruth"))){
	    // create canvas and set titel corresponding to plotname in .root file
	    if(first){
	      addCanvas(plotCanvas_);
	      plotCanvas_[plotCanvas_.size()-1]->cd(0);
	      plotCanvas_[plotCanvas_.size()-1]->SetTitle(getStringEntry(plotList_[plot], 2)+getStringEntry(plotList_[plot], 1));
	    }
	    if(verbose>1){
	      std::cout << "plotting " << plotList_[plot];
	      std::cout << " from sample " << sampleLabel(sample,decayChannel);
	      std::cout << " to canvas " << plotCanvas_.size()-1 << " ( ";
	      std::cout << plotCanvas_[plotCanvas_.size()-1]->GetTitle() << " )" << std::endl;
	    }
	    // for efficiency plots: draw grid
	    if(getStringEntry(plotList_[plot], 1)=="efficiency"||plotList_[plot].Contains("qAssignment")) plotCanvas_[plotCanvas_.size()-1]->SetGrid(1,1);
	    // for histos with variable binning:
	    if(binning_.count("analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+getStringEntry(plotList_[plot], 2))>0){
	      // get variable binning
	      TString plotName=getStringEntry(plotList_[plot], 2);
	      std::vector<double> binEdges_=binning_["analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/"+plotName];
	      // set maximum of histo to last bin considered 
	      // in variable binning (overflow excluded)
	      double firstBin=0;
	      double lastBin=binEdges_.size()-2;
	      // -2 for subtracting overflow bin
	      if(verbose>2){
		std::cout << "1st bin, last bin: " << firstBin << " , " << lastBin << std::endl;
	      }
	      histo_[plotList_[plot]][sample]->GetXaxis()->SetRange(firstBin, lastBin);
	    }
	    // first plot
	    if(first){
	      // min / max
	      double max = 1.3*histo_[plotList_[plot]][sample]->GetMaximum();
	      // if data file exists
	      if(histo_[plotList_[plot]].count(kData)>0){
		// and has larger maximum
		if(max < 1.3*histo_[plotList_[plot]][kData]->GetMaximum()){
		  // take this maximum
		  max = 1.3*histo_[plotList_[plot]][kData]->GetMaximum();
		  if(verbose>1) std:: cout << "take max from data! " << std::endl;
		}
	      }
	      double min = 0;
	      // log plots
	      if(getStringEntry(axisLabel_[plot],3)=="1"){
		plotCanvas_[plotCanvas_.size()-1]->SetLogy(1);
		min=1;
		max=exp(1.3*(std::log(max)-std::log(min))+std::log(min));
		if(plotList_[plot]=="analyzeTopRecoKinematicsKinFit"+sysInputFolderExtension+"/prob") min=0.1; 
		if(plotList_[plot].Contains("ttbarMass")&&plotList_[plot].Contains("xSec")){
		  min=0.0001;
		  max=1.2*exp(1.3*(std::log(max)-std::log(min))+std::log(min));
		  if(plotList_[plot].Contains("Norm")){
		    min=0.00001;
		    max=0.06;
		  }
		}
	      }
	      // get nicer int values if maximum is large enough
	      if(max>3) max = (double)roundToInt(max);
	      // style for pull plots
	      if(plotList_[plot].Contains("RecPartonTruth")){
		min=0;
		//max=1;
		TString title=(TString)plotCanvas_[plotCanvas_.size()-1]->GetTitle();
		title.ReplaceAll("RecPartonTruth","");
		plotCanvas_[plotCanvas_.size()-1]->SetTitle(title);
		histo_[plotList_[plot]][sample]->GetYaxis()->SetNoExponent(true);
		plotCanvas_[plotCanvas_.size()-1]->SetGrid(1,1);
	      }
	      // axis style
	      axesStyle(*histo_[plotList_[plot]][sample], getStringEntry(axisLabel_[plot],1), getStringEntry(axisLabel_[plot],2), min, max); 
	      histo_[plotList_[plot]][sample]->GetXaxis()->SetNoExponent(true);
	      if(max>1&&max<100) histo_[plotList_[plot]][sample]->GetYaxis()->SetNoExponent(true);
	      else histo_[plotList_[plot]][sample]->GetYaxis()->SetNoExponent(false);
	      if(plotList_[plot].Contains("qAssignment")) histo_[plotList_[plot]][sample]->GetYaxis()->SetNoExponent(true);
	      if(getStringEntry(plotList_[plot], 1).Contains("xSec")) histo_[plotList_[plot]][sample]->GetYaxis()->SetTitleOffset(1.6);
	      // restrict x axis for different plots
	      if(getStringEntry(plotList_[plot], 2)=="topMass") histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,500);
	      if(getStringEntry(plotList_[plot], 2)=="lepEta")  histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(-2.0,2.0);
	      if(!(plotList_[plot].Contains("xSec"))&&(getStringEntry(plotList_[plot], 2)=="topY"   ||
						       getStringEntry(plotList_[plot], 2)=="topYHad"|| 
						       getStringEntry(plotList_[plot], 2)=="topYLep")){
		histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(-3,3);}
	      if(getStringEntry(plotList_[plot], 2)=="lepPt" )  histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(30,190);
	      if(getStringEntry(plotList_[plot], 2)=="ttbarY")  histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(-1,1);
	      if(getStringEntry(plotList_[plot], 2)=="PartonJetDRall") histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,4);
	      // draw efficiency plots as line
	      if(getStringEntry(plotList_[plot], 1)=="efficiency") histo_[plotList_[plot]][sample]->Draw("p e");
	      // draw pull plots as line into same canvas with extra legend
	      if(plotList_[plot].Contains("RecPartonTruth")){
		histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(-1.5,1.5);
		histo_[plotList_[plot]][sample]->GetXaxis()->SetTitle(((TString)(histo_[plotList_[plot]][sample]->GetXaxis()->GetTitle())).ReplaceAll(":","/"));
		histo_[plotList_[plot]][sample]->GetYaxis()->SetNoExponent(true);
		histo_[plotList_[plot]][sample]->Draw("hist");
		TString afterKinFit=plotList_[plot];
		afterKinFit.ReplaceAll("RecPartonTruth","KinFitPartonTruth");
		TString kinFitShift=plotList_[plot];
		kinFitShift.ReplaceAll("RecPartonTruth","KinFitRec"        );
		if(histo_.count(afterKinFit)>0){ 
		  histo_[plotList_[plot]][sample]->SetMaximum(1.3*histo_[afterKinFit][sample]->GetMaximum());
		  histo_[afterKinFit][sample]->Draw("hist same");
		}
		if(histo_.count(kinFitShift)>0) histo_[kinFitShift][sample]->Draw("hist same");
		legPull->Draw("same");
	      }
	      // others as histo (stack)
	      else histo_[plotList_[plot]][sample]->Draw("hist");
	      histo_[plotList_[plot]][42] = (TH1F*)(histo_[plotList_[plot]][sample]->Clone());
	      // draw BBB comparison results in same canvas
	      if(compare&&plotList_[plot].Contains("xSec")){
		TString BBBlabel=plotList_[plot];
		BBBlabel.ReplaceAll("xSec/","xSec/BBB");
		BBBlabel.ReplaceAll("xSecNorm/","xSecNorm/BBB");
		if(plotExists(histo_, BBBlabel, sample)) histo_[BBBlabel][sample]->Draw("hist same");
	      }
	    }
	    // draw other plots into same canvas
	    else{ 
	      // draw data as points
	      if(sample==kData){ 
		histo_[plotList_[plot]][sample]->Draw("p e X0 same");
		// draw BBB comparison results in same canvas
		if(compare&&plotList_[plot].Contains("xSec")){
		  TString BBBlabel=plotList_[plot];
		  BBBlabel.ReplaceAll("xSec/","xSec/BBB");
		  BBBlabel.ReplaceAll("xSecNorm/","xSecNorm/BBB");
		  if(plotExists(histo_, BBBlabel, sample)) histo_[BBBlabel][sample]->Draw("p e X0 same");
		}
	      }
	      else{
		// draw efficiencies as points
		if(getStringEntry(plotList_[plot], 1)=="efficiency") histo_[plotList_[plot]][sample]->Draw("p e same");
		// draw others as histo (stack)
		else histo_[plotList_[plot]][sample]->Draw("hist same");
	      }
	    }
	    first=false;
	    // draw legend for recoYield plots
	    TString title=plotCanvas_[plotCanvas_.size()-1]->GetTitle();
	    if(title.Contains("analyzeTopRecoKinematicsKinFit")){
	      leg->SetX1NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength() - 0.20);
	      leg->SetY1NDC(1.0 - gStyle->GetPadTopMargin()   - gStyle->GetTickLength() - 0.03*leg->GetNRows());
	      leg->SetX2NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength());
	      leg->SetY2NDC(1.0 - gStyle->GetPadTopMargin()   - gStyle->GetTickLength());
	      if(!plotList_[plot].Contains("qAssignment")) leg->Draw("SAME");
	    }
	    // redraw axis at the end
	    if((histo_.count(plotList_[plot])>0)&&(sample==kData)) histo_[plotList_[plot]][42]->Draw("axis same");	 
	    TString plotType=getStringEntry(plotList_[plot], 1);
	    if(plotType.Contains("xSec")||plotType.Contains("Reco")){
	      if (decayChannel=="muon") DrawDecayChLabel("#mu + Jets");
	      else if(decayChannel=="electron") DrawDecayChLabel("e + Jets");
	      DrawCMSLabels(true,luminosity);
	    }
	  }
	  first=false;
	  // draw uncertainty bands, add legend and labels and re-draw axis
	  if((histo_.count(plotList_[plot])>0)&&(sample==kData)){
	    // configure style of and draw uncertainty bands
	    if (!plotList_[plot].Contains("xSec")){
	      histoErrorBand_[plotList_[plot]]->SetMarkerStyle(0);
	      histoErrorBand_[plotList_[plot]]->SetFillColor(1);
	      histoErrorBand_[plotList_[plot]]->SetFillStyle(3004);
	      gStyle->SetErrorX(0.5);  
	      histoErrorBand_[plotList_[plot]]->Draw("E2 SAME");	 	     
	      // draw legend for recoYield plots
	      TString tempTitle = plotCanvas_[plotCanvas_.size()-1]->GetTitle();
	      if(tempTitle.Contains("analyzeTopRecoKinematicsKinFit")){
		leg->SetX1NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength() - 0.20);
		leg->SetY1NDC(1.0 - gStyle->GetPadTopMargin()   - gStyle->GetTickLength() - 0.03 * leg->GetNRows() );
		leg->SetX2NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength());
		leg->SetY2NDC(1.0 - gStyle->GetPadTopMargin()   - gStyle->GetTickLength());
		if(!plotList_[plot].Contains("qAssignment")) leg->Draw("SAME");
	      }	 
	      // labels
	      TString plotType=getStringEntry(plotList_[plot], 1);
	      if(plotType.Contains("xSec")||plotType.Contains("Reco")){
		if (decayChannel=="muon")         DrawDecayChLabel("#mu + Jets");
		else if(decayChannel=="electron") DrawDecayChLabel("e + Jets");
		DrawCMSLabels(true,luminosity);
	      }
	      // redraw axis
	      histo_[plotList_[plot]][42]->Draw("axis same");
	    }
	  }
	}
      }
      
      // a3) for 2D plots
      if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)&&	  
	 // draw gen-reco correlation only for signal 
	 (!plotList_[plot].Contains("_"   )||sample==kSig)){
	// new Canvas for every plot
	addCanvas(plotCanvas_);
	plotCanvas_[plotCanvas_.size()-1]->cd(0);
	plotCanvas_[plotCanvas_.size()-1]->SetRightMargin(myStyle.GetPadRightMargin());
	plotCanvas_[plotCanvas_.size()-1]->SetTitle(getStringEntry(plotList_[plot],2)+getStringEntry(plotList_[plot],1)+getTStringFromInt(sample));
	if(verbose>1){
	  std::cout << "plotting " << plotList_[plot];
	  std::cout << " from sample " << sampleLabel(sample,decayChannel);
	  std::cout << " to canvas " << plotCanvas_.size()-1  << " ( ";
	  std::cout << plotCanvas_[plotCanvas_.size()-1]->GetTitle() << " )"  << std::endl;
	}
	// draw histo
	plotCanvas_[plotCanvas_.size()-1]->SetRightMargin(0.15);
	histo2_[plotList_[plot]][sample]->GetXaxis()->SetNoExponent(true);
	histo2_[plotList_[plot]][sample]->GetYaxis()->SetNoExponent(true);
	histo2_[plotList_[plot]][sample]->Draw("colz");
	// print correlation factor
	double d = histo2_[plotList_[plot]][sample]->GetCorrelationFactor();
	char correlation[20];
	sprintf(correlation, "%f", d);
	TString corr = (TString)correlation;
	DrawLabel("correlation: "+corr, 0.35, 0.92, 0.75, 0.99, 0.7);
      }
    }
  }
  // b) for legends
  addCanvas(plotCanvas_);
  plotCanvas_[plotCanvas_.size()-1]->cd(0);
  plotCanvas_[plotCanvas_.size()-1]->SetTitle("legend");
  leg0->Draw("");

  // ---
  // saving
  // ---
  if(save){
    // pdf and eps only for standard analysis without variation
    if(systematicVariation==sysNo){
      if(verbose<=1) gErrorIgnoreLevel=kWarning;
      // a) as pdf
      saveCanvas(plotCanvas_, outputFolder, pdfName, true, false);
      // b) as eps and png
      for(unsigned int idx=0; idx<plotCanvas_.size(); idx++){
	TString saveToFolder=outputFolder;
	TString title=(plotCanvas_[idx])->GetTitle();
	if(title.Contains("efficiency"                     )) saveToFolder+="effAndAcc/";
	if(title.Contains("analyzeTopPartonLevelKinematics")) saveToFolder+="partonLevel/";
	if(title.Contains("analyzeHypoKinFit"              )) saveToFolder+="kinFitPerformance/";
	if(title.Contains("xSec"                           )) saveToFolder+="xSec/";
       	if(title.Contains("analyzeTopRecoKinematicsKinFit" )) saveToFolder+="recoYield/";
	if(title.Contains("0")                              ) saveToFolder=outputFolder+"genRecoCorrPlots/";
	if(!title.Contains("canv")){
	  plotCanvas_[idx]->Print(saveToFolder+(TString)(plotCanvas_[idx]->GetTitle())+".eps"); 
	  plotCanvas_[idx]->Print(saveToFolder+(TString)(plotCanvas_[idx]->GetTitle())+".png");
	}
      }
    }
    // c) root file
    std::vector< std::pair< TCanvas*,TString > > saveCanvas_;
    if(verbose>0) std::cout << "will save all plots in outputfile named " << outputFileName << std::endl;
    for(unsigned int idx=0; idx<plotCanvas_.size(); ++idx){
      // get correct folder
      TString title=(plotCanvas_[idx])->GetTitle();
      TString outputfolder="";
      TString possibleFolderNames[5]={"efficiency", "analyzeTopRecoKinematicsKinFit", "xSec", "analyzeTopPartonLevelKinematics", "analyzeHypoKinFit"};
      for(unsigned int name=0; name<sizeof(possibleFolderNames)/sizeof(TString); ++name){
	// add another subfoder indicating the systematic variation
	if(title.Contains(possibleFolderNames[name])){ 
	  outputfolder=possibleFolderNames[name]+"/"+sysLabel(systematicVariation);
	  plotCanvas_[idx]->SetTitle(title.ReplaceAll(possibleFolderNames[name],""));
	}
      }
      // save only canvas from selected subfolders or legends
      if(outputfolder!=""||title.Contains("legend")){ 
	// collect information in saveCanvas_
	saveCanvas_.push_back(std::make_pair((TCanvas*)plotCanvas_[idx]->Clone(),outputfolder));
      }
    }
    // save all collected plots
    saveToRootFileAll(outputFileName, saveCanvas_, true, verbose-1);
  }
  
  // delete pointer
  delete leg0;
  closeStdTopAnalysisFiles(files_);
}
