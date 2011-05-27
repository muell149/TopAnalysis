#include "basicFunctions.h"

void analyzeHypothesisKinFit(double luminosity = 188.0, bool save = true, int systematicVariation=sysNo, unsigned int verbose=0, //TString dataFile= "./diffXSecFromSignal/analysisRootFilesWithKinFit/muonDiffXSec2010Data36pbNov4ReRecoNov12Json.root")
			     TString dataFile= "./diffXSecFromSignal/analysisRootFilesWithKinFit/muonDiffXSec2011Data188pPromptReco1305Json.root")
{
  //  ---
  //     name conventions
  //  ---
  // a) enumerator sample convention (as defined in basicFunctions.h)
     /*0:*/  /*1:*/  /*2:*/    /*3:*/    /*4:*/   /*5:*/    /*6:*/  /*7:*/  /*8,  9,  10*/ /* 11   ,  12     ,   13:  */
  // kSig  , kBkg  , kZjets  , kWjets  , kQCD   , kSTop   , kDiBos, kData , kWW, kWZ, kZZ, kSTops  , kSTopt  , kSToptW 
  // b) file name convention (implemented in basicFunctions.h)
  // "muonDiffXSec"+sampleName+GeneratorName+GeneratorTune+MCProductionCycle+systematicVariation+"PF.root"
  // sampleName = "Sig", "Bkg", Wjets", "Zjets", "WW", "WZ", "ZZ", "VV", "SingleTopSchannel", 
  //              "SingleTopTchannel", "SingleTopTWchannel", "QCD"
  // GeneratorName= "Mad", "Pythia6"
  // GeneratorTune= "Z2", "D6T"
  // MCProductionCycle= "Fall10"
  // systematicVariation= "JESup", "JESdown", "JERup", "JERdown", "PileUp", "ScaleUp", 
  //                      "ScaleDown", "MatchUp", "MatchDown"

  //  ---
  //     options
  //  ---
  // a) options directly entered when calling function
  /* systematicVariation: which systematic shift do you want to make? from basicFunctions.h:
     0:sysNo              1:sysLumiUp          2:sysLumiDown          3:sysJESUp      
     4:sysJESDown         5:sysJERUp           6:sysJERDown           7:sysTopScaleUp 
     8:sysTopScaleDown    9:sysVBosonScaleUp  10:sysVBosonScaleDown  11:sysTopMatchUp 
     12:sysTopMatchDown  13:sysVBosonMatchUp  14:sysVBosonMatchDown  15:sysMuEffSFup  
     16:sysMuEffSFdown   17:sysISRFSRup       18:sysISRFSRdown       19:sysPileUp    
     20:sysQCDup         21:sysQCDdown        22:sysSTopUp           23:sysSTopDown  
     24:sysBtagUp        25:sysBtagDown       26:sysDiBosUp          27:sysDiBosDown
  */
  if(systematicVariation==sysLumiUp  ) luminosity*=1.04;
  if(systematicVariation==sysLumiDown) luminosity*=0.96;
  // verbose: set detail level of output 
  // 0: no output, 1: std output 2: output for debugging
  // data file: relative path of .root file
  // save: save plots?
  // luminosity: [/pb]
  TString lumi = getTStringFromInt(roundToInt((luminosity), false));
  // b) options to be configured only once
  // get the .root files from the following folder:
  TString inputFolder = "./diffXSecFromSignal/analysisRootFilesWithKinFit";
  // see if its 2010 or 2011 data from luminosity
  TString dataSample="";
  if(luminosity<36) dataSample="2010";
  if(luminosity>36) dataSample="2011";
  // save all plots into the following folder
  TString outputFolder = "./diffXSecFromSignal/plots/kinFit/";
  if(dataSample!="") outputFolder+=dataSample+"/";
  // save all plots within a root file named:
  TString outputFileName="diffXSecTopSemiMu"+dataSample+".root";
  // choose name of the output .pdf file
  TString pdfName="kinFitpbHypothesis"+lumi+"pb";
  // c) set root style
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetEndErrorSize(8);
  gStyle->SetPalette(1);
  //  gStyle->SetErrorX(0); 

  //  ---
  //     choose plots
  //  ---
  // a) list plots you would like to see ("folder/plotName") - same as in .root files (for 1D and 2D)
  TString plots1D[ ] = { // general fit performance
                         "analyzeTopRecoKinematicsKinFit/prob"       , 
			 "analyzeTopRecoKinematicsKinFit/chi2"       , 
			 "analyzeTopRecoKinematicsKinFit/delChi2"    ,
			 // combinatorics and Kinfit Hypothesis Quality(ttbar signal only)
			 "analyzeHypoKinFit/hadBQuark"               , 
			 "analyzeHypoKinFit/lepBQuark"               , 
			 "analyzeHypoKinFit/lightQuark"              , 
			 "analyzeHypoKinFit/wrongAssign"             ,
			 "analyzeHypoKinFit/qAssignment"             ,
			 "analyzeHypoKinFit/PartonJetDRall"          ,
			 // pull distributions
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
			 // reconstructed top quantities
                         "analyzeTopRecoKinematicsKinFit/topMass"    ,
                         "analyzeTopRecoKinematicsKinFit/topPt"      ,                         
                         "analyzeTopRecoKinematicsKinFit/topPhi"     ,
                         "analyzeTopRecoKinematicsKinFit/topY"       ,
                         "analyzeTopRecoKinematicsKinFit/topPtHad"   ,
                         "analyzeTopRecoKinematicsKinFit/topPhiHad"  ,
                         "analyzeTopRecoKinematicsKinFit/topYHad"    ,
                         "analyzeTopRecoKinematicsKinFit/topPtLep"   ,
                         "analyzeTopRecoKinematicsKinFit/topPhiLep"  ,
                         "analyzeTopRecoKinematicsKinFit/topYLep"    ,
			 // reconstructed angular distributions
                         "analyzeTopRecoKinematicsKinFit/bbbarAngle"  ,
                         "analyzeTopRecoKinematicsKinFit/bbbarAngleTtRF",
                         "analyzeTopRecoKinematicsKinFit/WWAngle"     ,
                         "analyzeTopRecoKinematicsKinFit/topWAngleLep",
                         "analyzeTopRecoKinematicsKinFit/topWAngleHad",
                         "analyzeTopRecoKinematicsKinFit/topBAngleLep",
                         "analyzeTopRecoKinematicsKinFit/topBAngleHad",
                         "analyzeTopRecoKinematicsKinFit/bWAngleLep"  ,
                         "analyzeTopRecoKinematicsKinFit/bWAngleHad"  ,
                         "analyzeTopRecoKinematicsKinFit/qqbarAngle"  ,
                         "analyzeTopRecoKinematicsKinFit/qBlepAngle"  ,
                         "analyzeTopRecoKinematicsKinFit/qBhadAngle"  ,
			 "analyzeTopRecoKinematicsKinFit/lepBlepAngle",
			 "analyzeTopRecoKinematicsKinFit/lepBlepAngleTtRF",
			 "analyzeTopRecoKinematicsKinFit/lepBhadAngle",
			 "analyzeTopRecoKinematicsKinFit/lepQAngle"   ,
			 "analyzeTopRecoKinematicsKinFit/MuonNeutrinoAngle",
			 "analyzeTopRecoKinematicsKinFit/lepBNeutrinoAngle",
			 "analyzeTopRecoKinematicsKinFit/hadBNeutrinoAngle",
			 "analyzeTopRecoKinematicsKinFit/qNeutrinoAngle"   ,
			 "analyzeTopRecoKinematicsKinFit/lepWDir"     ,
			 "analyzeTopRecoKinematicsKinFit/nuWDir"      ,
			 "analyzeTopRecoKinematicsKinFit/qWDir"       ,
			 // reconstructed event shape variables
			 "analyzeTopRecoKinematicsKinFit/aplanarity" ,
			 "analyzeTopRecoKinematicsKinFit/sphericity" ,
			 "analyzeTopRecoKinematicsKinFit/C"          ,
			 "analyzeTopRecoKinematicsKinFit/D"          ,
			 "analyzeTopRecoKinematicsKinFit/circularity",
			 "analyzeTopRecoKinematicsKinFit/isotropy"   ,
			 // generated top quantities
                         "analyzeTopPartonLevelKinematics/topMass"      , 
                         "analyzeTopPartonLevelKinematics/topPt"        ,                         
                         "analyzeTopPartonLevelKinematics/topPhi"       ,
                         "analyzeTopPartonLevelKinematics/topY"         ,
                         "analyzeTopPartonLevelKinematics/topPtHad"     ,
                         "analyzeTopPartonLevelKinematics/topPhiHad"    ,
                         "analyzeTopPartonLevelKinematics/topYHad"      ,
                         "analyzeTopPartonLevelKinematics/topPtLep"     ,
                         "analyzeTopPartonLevelKinematics/topPhiLep"    ,
                         "analyzeTopPartonLevelKinematics/topYLep"      ,
			 // generated angular distributions
			 "analyzeTopPartonLevelKinematics/bbbarAngle"   ,
			 "analyzeTopPartonLevelKinematics/bbbarAngleTtRF",
                         "analyzeTopPartonLevelKinematics/WWAngle"     ,
                         "analyzeTopPartonLevelKinematics/topWAngleLep",
                         "analyzeTopPartonLevelKinematics/topWAngleHad",
                         "analyzeTopPartonLevelKinematics/topBAngleLep",
                         "analyzeTopPartonLevelKinematics/topBAngleHad",
                         "analyzeTopPartonLevelKinematics/bWAngleLep"  ,
                         "analyzeTopPartonLevelKinematics/bWAngleHad"  ,
                         "analyzeTopPartonLevelKinematics/qqbarAngle"  ,
                         "analyzeTopPartonLevelKinematics/qBlepAngle"  ,
                         "analyzeTopPartonLevelKinematics/qBhadAngle"  ,
			 "analyzeTopPartonLevelKinematics/lepBlepAngle",
			 "analyzeTopPartonLevelKinematics/lepBlepAngleTtRF",
			 "analyzeTopPartonLevelKinematics/lepBhadAngle",
			 "analyzeTopPartonLevelKinematics/lepQAngle"   ,
			 "analyzeTopPartonLevelKinematics/MuonNeutrinoAngle",
			 "analyzeTopPartonLevelKinematics/lepBNeutrinoAngle",
			 "analyzeTopPartonLevelKinematics/hadBNeutrinoAngle",
			 "analyzeTopPartonLevelKinematics/qNeutrinoAngle"   ,
			 "analyzeTopPartonLevelKinematics/lepWDir"     ,
			 "analyzeTopPartonLevelKinematics/qWDir"       ,
			 "analyzeTopPartonLevelKinematics/nuWDir"      ,
			 // reconstructed ttbar quantities
                         "analyzeTopRecoKinematicsKinFit/ttbarMass"  ,
                         "analyzeTopRecoKinematicsKinFit/ttbarPt"    ,
                         "analyzeTopRecoKinematicsKinFit/ttbarY"     ,
                         "analyzeTopRecoKinematicsKinFit/ttbarHT"    ,
                         "analyzeTopRecoKinematicsKinFit/ttbarSumY"  ,
			 "analyzeTopRecoKinematicsKinFit/ttbarDelPhi",
			 "analyzeTopRecoKinematicsKinFit/ttbarDelY"  ,
			 // generated ttbar quantities
                         "analyzeTopPartonLevelKinematics/ttbarMass"  ,
                         "analyzeTopPartonLevelKinematics/ttbarPt"    ,
                         "analyzeTopPartonLevelKinematics/ttbarY"     ,
                         "analyzeTopPartonLevelKinematics/ttbarHT"    ,
                         "analyzeTopPartonLevelKinematics/ttbarSumY"  ,
			 "analyzeTopPartonLevelKinematics/ttbarDelPhi",
			 "analyzeTopPartonLevelKinematics/ttbarDelY"  
                       };
  TString plots2D[ ] = { // reco - gen Match correlation plots (ttbar signal only)
                         // a) combinatorics and Kinfit Hypothesis Quality(ttbar signal only)
                         "analyzeHypoKinFit/mapKinFit_"                      ,
			 // b) reconstructed Top quantities
			 "analyzeTopRecoKinematicsKinFit/topPt_"      ,
			 "analyzeTopRecoKinematicsKinFit/topPhi_"     ,
			 "analyzeTopRecoKinematicsKinFit/topY_"       ,
                         "analyzeTopRecoKinematicsKinFit/bbbarAngle_" ,
                         // c) reconstructed ttbar quantities
			 "analyzeTopRecoKinematicsKinFit/ttbarMass_"  ,
                         "analyzeTopRecoKinematicsKinFit/ttbarPt_"    ,
                         "analyzeTopRecoKinematicsKinFit/ttbarY_"     ,
                         "analyzeTopRecoKinematicsKinFit/ttbarHT_"    ,
                         "analyzeTopRecoKinematicsKinFit/ttbarSumY_"  ,
			 "analyzeTopRecoKinematicsKinFit/ttbarDelPhi_",
			 "analyzeTopRecoKinematicsKinFit/ttbarDelY_"  
                       };

  // b) list plot axes style
  // 1D: "x-axis title"/"y-axis title"/log/rebin-factor
  // log = 0 or 1 for linear or logarithmic axis 

  TString axisLabel1D[ ] = { // general fit performance
                             "probability (best fit hypothesis)/events/1/25"                   , 
			     "#chi^{2} (best fit hypothesis)/events/0/10"                      ,
			     "#Delta#chi^{2} (1^{st} - 2^{nd} best fit hypothesis)/events/0/10",
			     // combinatorics and Kinfit Hypothesis Quality(ttbar signal only)
			     "#Deltai_{lead jet}(genMatch - kinFit), hadronic b-quark/events/0/1", 
			     "#Deltai_{lead jet}(genMatch - kinFit), leptonic b-quark/events/0/1", 
			     "#Deltai_{lead jet}(genMatch - kinFit), light quarks/events/0/1"    ,
			     "N(wrong assigned jets)/events/0/1"                                 , 
			     "permutation/events/0/1"                                            ,
			     "#DeltaR(parton, reco jet assigned from Kinfit)/partons/1/10"                        ,
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
 			     "(p_{t fit}-p_{t gen}) p_{t gen}^{-1} (leptonic W)/events/0/1"          ,
 			     "(#eta_{fit}-#eta_{gen}) #eta_{gen}^{-1} (leptonic W)/events/0/1"       ,
 			     "(#phi_{fit}-#phi_{gen}) #phi_{gen}^{-1} (leptonic W)/events/0/1"       ,
 			     "(p_{t fit}-p_{t gen}) p_{t gen}^{-1} (hadronic W)/events/0/1"          ,
 			     "(#eta_{fit}-#eta_{gen}) #eta_{gen}^{-1} (hadronic W)/events/0/1"       ,
 			     "(#phi_{fit}-#phi_{gen}) #phi_{gen}^{-1} (hadronic W)/events/0/1"       ,
			     // reconstructed top quantities
                             "m_{t} Kinfit [GeV]/top quarks/0/10"     ,
                             "p_{t}(t) Kinfit [GeV]/top quarks/0/1"   ,//20"
                             "#phi(t) Kinfit/top quarks/0/4"         ,
                             "y(t) Kinfit/top quarks/0/1"             ,//5"
                             "p_{t}(hadronic t) Kinfit [GeV]/events/0/20",                         
                             "#phi(hadronic t) Kinfit/events/0/4",
                             "y(hadronic t) Kinfit/events/0/5"    ,
                             "p_{t}(leptonic t) Kinfit [GeV]/events/0/20",                         
                             "#phi(leptonic t) Kinfit/events/0/4",
                             "y(leptonic t) Kinfit/events/0/5"   ,
			     //  reconstructed angular distributions
			     "#angle(b,#bar{b}) Kinfit (detector rest frame)/events/0/21",
			     "#angle(b,#bar{b}) Kinfit (t#bar{t} rest frame)/events/0/21",
                             "#angle(W,W) Kinfit (t#bar{t} RF)/events/0/21"              ,
                             "#angle(lep.t,W) Kinfit (t:t#bar{t} RF, W:t RF)/events/0/21",
                             "#angle(had.t,W) Kinfit (t:t#bar{t} RF, W:t RF)/events/0/21",
                             "#angle(lep.t,b) Kinfit (t#bar{t} rest frame)/events/0/21"  ,
			     "#angle(had.t,b) Kinfit (t#bar{t} rest frame)/events/0/21"  ,
                             "#angle(lep.b,W) Kinfit (t#bar{t} rest frame)/events/0/21"  ,
                             "#angle(had.b,W) Kinfit (t#bar{t} rest frame)/events/0/21"  ,
                             "#angle(q,#bar{q}) Kinfit (top rest frame)/events/0/21"     ,
                             "#angle(q,lep.b) Kinfit (t#bar{t} rest frame)/events/0/21"  ,
                             "#angle(q,had.b) Kinfit (top rest frame)/events/0/21"       ,
			     "#angle(#mu,lep.b) Kinfit (top rest frame)/events/0/21"     , 
			     "#angle(#mu,lep.b) Kinfit (t#bar{t} rest frame)/events/0/21",
			     "#angle(#mu,lep.b) Kinfit (top rest frame)/events/0/21"     ,
			     "#angle(#mu,q) Kinfit (t#bar{t} rest frame)/events/0/21"    ,
			     "#angle(#mu,#nu) Kinfit (t#bar{t} rest frame)/events/0/21"  ,
			     "#angle(#nu,lep.b) Kinfit (top rest frame)/events/0/21"     ,
			     "#angle(#nu,had.b) Kinfit (t#bar{t} rest frame)/events/0/21",
			     "#angle(#nu,q) Kinfit (t#bar{t} rest frame)/events/0/21"    ,
			     "#angle(#mu,lep.W) Kinfit (#mu:W RF, W:Det RF)/events/0/21" ,
			     "#angle(#nu,lep.W) Kinfit (#nu:W RF, W:Det RF)/events/0/21" ,
			     "#angle(q,had.W) Kinfit (q:W RF, W:Det RF)/events/0/21"     ,
			     // reconstructed event shape variables
			     "aplanarity Kinfit/events/0/2"  ,
			     "sphericity Kinfit/events/0/10" ,
			     "C Kinfit/events/0/10"          ,
			     "D Kinfit/events/0/4"           ,
			     "circularity Kinfit/events/0/10",
			     "isotropy Kinfit/events/0/10"   ,
			     // generated top quantities
                             "m_{t} parton truth [GeV]/events/0/10"      ,
                             "p_{t}(t) parton truth/events/0/1"          ,//20"
                             "#phi(t) parton truth/events/0/4"          ,
                             "y(t) parton truth/events/0/1"              ,//5"
                             "p_{t}(hadronic t) parton truth/events/0/20",                         
                             "#phi(hadronic t) parton truth/events/0/4" ,
                             "y(hadronic t) parton truth/events/0/5"     ,
                             "p_{t}(leptonic t) parton truth/events/0/20",                         
                             "#phi(leptonic t) parton truth/events/0/4" ,
                             "y(leptonic t) parton truth/events/0/5"     ,
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
// 			     // generated event shape variables
// 			     "aplanarity parton truth/events/0/4"  ,
// 			     "sphericity parton truth/events/0/10" ,
// 			     "C parton truth/events/0/10"          ,
// 			     "D parton truth/events/0/4"           ,
// 			     "circularity parton truth/events/0/10",
// 			     "isotropy parton truth/events/0/10"   ,
			     // reconstructed ttbar quantities	                            
                             "m(t#bar{t}) Kinfit/events/0/1"                         ,//60"
                             "p_{t}(t#bar{t}) Kinfit/events/0/1"                     ,//10"
                             "y(t#bar{t}) Kinfit/events/0/1"                         ,//2
                             "H_{T}(t#bar{t})=#Sigma(p_{T}(jets)) Kinfit/events/0/20",
                             "y(t)+y(#bar{t}) Kinfit/events/0/10"                    ,
                             "#phi(leptonic t)-#phi(hadronic t) Kinfit/events/0/4"  ,                
                             "y(leptonic t)-y(hadronic t) Kinfit/events/0/4"         ,  
			     // generated ttbar quantities	                            
                             "m(t#bar{t}) parton truth/events/0/1"                         ,//60"
                             "p_{t}(t#bar{t}) parton truth/events/0/1"                     ,//10"
                             "y(t#bar{t}) parton truth/events/0/1"                         ,//2
                             "H_{T}(t#bar{t})=#Sigma(p_{T}(jets)) parton truth/events/0/20",
                             "y(t)+y(#bar{t}) parton truth/events/0/10"                    ,
                             "#phi(leptonic t)-#phi(hadronic t) parton truth/events/0/4"  ,                
                             "y(leptonic t)-y(hadronic t) parton truth/events/0/4" 
                           };
  // 2D: "x-axis title"/"y-axis title"
  TString axisLabel2D[ ] = {// reco - gen Match correlation plots (ttbar signal only)
                            // a) combinatorics and Kinfit Hypothesis Quality(ttbar signal only)
                            "i_{lead jet} parton truth/i_{lead jet} hypothesis fit",
			    // b) reconstructed Top quantities
                            "p_{t}(t) gen/p_{t}(t) reco"                    ,
			    "#phi(t) gen/#phi(t) reco"                      ,
                            "y(t) gen/y(t) reco"                            ,
			    "angle(b,#bar{b}) gen (t#bar{t} rest frame)/angle(b,#bar{b}) reco (t#bar{t} rest frame)",
                            // c) reconstructed ttbar quantities
                            "m(t#bar{t}) gen/m(t#bar{t}) reco"              ,
                            "p_{t}(t#bar{t}) gen/p_{t}(t#bar{t}) reco"      ,
                            "y(t#bar{t}) gen/y(t#bar{t}) reco"              ,
                            "H_{T}(t#bar{t}) gen/H_{T}(t#bar{t}) reco"      ,
                            "#Sigmay(t#bar{t}) gen/#Sigmay(t#bar{t}) reco"  ,
                            "#phi(leptonic t)-#phi(hadronic t) gen/#phi(leptonic t)-#phi(hadronic t) Kinfit",
                            "y(leptonic t)-y(hadronic t) gen/y(leptonic t)-y(hadronic t) Kinfit"            
                           };
  // count # plots
  unsigned int N1Dplots = sizeof(plots1D)/sizeof(TString);
  unsigned int N2Dplots = sizeof(plots2D)/sizeof(TString);
  // check if all axis labels exist
  if(N1Dplots != sizeof(axisLabel1D)/sizeof(TString)) std::cout << "ERROR: some 1D plots or axis label are missing" << std::endl;
  if(N2Dplots != sizeof(axisLabel2D)/sizeof(TString)) std::cout << "ERROR: some 2D plots or axis label are missing" << std::endl;
  if((N1Dplots != sizeof(axisLabel1D)/sizeof(TString))||(N2Dplots != sizeof(axisLabel2D)/sizeof(TString))) exit (1);
  // run automatically in batch mode if there are many canvas
  if((N1Dplots+N2Dplots)>15) gROOT->SetBatch();

  // ---
  //    open our standard analysis files
  // ---
  std::map<unsigned int, TFile*> files_ = getStdTopAnalysisFiles(inputFolder, systematicVariation, dataFile);
  
  // ---
  //    loading histos
  // ---
  // collect all plot names in vector (first 1D, then 2D)
  std::vector<TString> plotList_;
  plotList_.insert( plotList_.begin(), plots1D, plots1D + sizeof(plots1D)/sizeof(TString) );
  plotList_.insert( plotList_.end()  , plots2D, plots2D + sizeof(plots2D)/sizeof(TString) );
  // container for all histos (1D&2D)
  // example for acess: histo_["plotName"][sampleNr]
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, std::map <unsigned int, TH2F*> > histo2_;
  // total # plots 
  int Nplots=0;
  // save all histos from plotList_ that exist in files_ into 
  // histo_ and histo2_ and count total # of plots as Nplots
  if(verbose>0) std::cout << std::endl;
  getAllPlots( files_, plotList_, histo_, histo2_, N1Dplots, Nplots, verbose);

  // ---
  //    lumiweighting for choosen luminosity
  // ---
  // scale every histo in histo_ and histo2_ to the corresponding luminosity
  // Additionally the mu eff SF is applied
  // NOTE: luminosity [/pb]
  scaleByLuminosity(plotList_, histo_, histo2_, N1Dplots, luminosity, verbose, systematicVariation);

  // ---
  //    add single top channels and DiBoson contributions
  // ---
  // for SingleTop and DiBoson samples:
  // every plot plotList_ existing in sTop/ diBoson .root file
  // will be combined and saved in the histo_ and histo2_ map
  // reCreate: reCreate combined plots if they are already existing
  bool reCreate=true;
  AddSingleTopAndDiBoson(plotList_, histo_, histo2_, N1Dplots, verbose, reCreate);

  // ---
  //    configure histograms
  // ---
  // needs: plotList_, histo_, histo2_, N1Dplots, axisLabel_, axisLabel1D, axisLabel2D
  std::vector<TString> axisLabel_;
  axisLabel_.insert( axisLabel_.begin(), axisLabel1D, axisLabel1D + sizeof(axisLabel1D)/sizeof(TString) );
  axisLabel_.insert( axisLabel_.end()  , axisLabel2D, axisLabel2D + sizeof(axisLabel2D)/sizeof(TString) );
  if(verbose>1){
    std::cout << "(plot, x Axis label , y Axis label , log scale?, rebinning factor):" << std::endl;
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
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
	histogramStyle( *histo_[plotList_[plot]][sample], sample, true );
	// special configurations
	if(getStringEntry(plotList_[plot], 2)=="PartonJetDRall")histo_[plotList_[plot]][sample]->SetNdivisions(816);
      }
      // b) 2D
      if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)) histStyle2D( *histo2_[plotList_[plot]][sample], sampleLabel(sample), getStringEntry(axisLabel_[plot],1), getStringEntry(axisLabel_[plot],2));
    }
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
	    reBinTH1F(*histo_[plotName][sample], binning_[getStringEntry(plotName, 2)], verbose);
	    if(verbose>1){
	      for(int i=1; i<= histo_[plotName][sample]->GetNbinsX()+1; i++){
		std::cout << "bin " << i << ": " << histo_[plotName][sample]->GetBinContent(i) << " / ";
		std::cout << histo_[plotName][sample]->GetBinWidth(i) << std::endl;
	      }
	    }
	    // divide by binwidth
	    histo_[plotName][sample] = divideByBinwidth(histo_[plotName][sample], 2);
	    if(verbose>1){
	      for(int i=1; i<= histo_[plotName][sample]->GetNbinsX()+1; i++){
		std::cout << "bin " << i << "= " << histo_[plotName][sample]->GetBinContent(i) << std::endl;
	      }
	    }
	    // change y axis label
	    if(!axisLabel_[plot].Contains("binwidth")){
	      axisLabel_[plot].ReplaceAll(getStringEntry(axisLabel_[plot],2), getStringEntry(axisLabel_[plot],2)+" per binwidth");
	      // check if unit is GeV
	      if(getStringEntry(axisLabel_[plot],1).Contains("GeV")){
		axisLabel_[plot].ReplaceAll(getStringEntry(axisLabel_[plot],2), getStringEntry(axisLabel_[plot],2)+" [GeV^{-1}]");
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
  // create list of variables you would like to create the efficiency / cross section for
  std::vector<TString> xSecVariables_, xSecLabel_;
  TString xSecVariables[] ={"topPt"          , "topY"           , "ttbarPt"            , "ttbarMass"      , "ttbarY"              };
  TString xSecLabel    [] ={"p_{t}(top)/GeV" , "y(top)/binwidth", "p_{t}(t#bar{t})/GeV", "m(t#bar{t})/GeV", "y(t#bar{t})/binwidth"};
  xSecVariables_ .insert( xSecVariables_.begin(), xSecVariables, xSecVariables + sizeof(xSecVariables)/sizeof(TString) );
  xSecLabel_     .insert( xSecLabel_    .begin(), xSecLabel    , xSecLabel     + sizeof(xSecLabel    )/sizeof(TString) );
  // loop all variables
  for(unsigned int number=0; number<xSecVariables_.size(); ++number){
    TString variable=xSecVariables_[number];
    TString efficiency="efficiency/"+variable;
    // check if gen and reco plots are available
    if(plotExists(histo_, "analyzeTopPartonLevelKinematics/"+variable, kSig)&&plotExists(histo_, "analyzeTopRecoKinematicsKinFit/"+variable, kSig)){
      //    std::cout << "found gen and reco" << std::endl;
      // get reco plot
      histo_[efficiency][kSig]=(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit/"+variable][kSig]->Clone());
      // divide by gen plot
      histo_[efficiency][kSig]->Divide((TH1F*)(histo_["analyzeTopPartonLevelKinematics/"+variable][kSig]->Clone()));

      // std::cout << "gen(bin1): "  <<  histo_["analyzeTopPartonLevelKinematics/"+variable  ][kSig]->GetBinContent(1) << std::endl;
      // std::cout << "reco(bin1): " <<  histo_["analyzeTopRecoKinematicsKinFit/"+variable][kSig]->GetBinContent(1) << std::endl;
      // std::cout << "eff(bin1): "  <<  histo_[efficiency][kSig]->GetBinContent(1) << std::endl;

      // add plot to list of plots
      plotList_.push_back(efficiency);
      // add axis configuration
      unsigned int positionOfRecoAxisLabel = positionInVector(plotList_, "analyzeTopRecoKinematicsKinFit/"+variable);
      TString recoAxisLabel =axisLabel_[positionOfRecoAxisLabel];
      axisLabel_.push_back(""+getStringEntry(recoAxisLabel,1)+"/"+"#epsilon #times A (MC t#bar{t}#rightarrow#mu)/"+getStringEntry(recoAxisLabel,3)+"/"+getStringEntry(recoAxisLabel,4));
      // set binomial errors
      if(verbose>1) std::cout << "       eff, events, width, sqrt(eff*(1.-eff)/events" << std::endl;
      for(int bin=1; bin<=histo_[efficiency][kSig]->GetNbinsX(); ++bin){
	double eff=histo_[efficiency][kSig]->GetBinContent(bin); 
	double N=histo_["analyzeTopPartonLevelKinematics/"+variable][kSig]->GetBinContent(bin);
	double width=histo_["analyzeTopPartonLevelKinematics/"+variable][kSig]->GetBinWidth(bin);
	N*=width;
	N/=(effSFAB(sysNo)*lumiweight(kSig, luminosity, systematicVariation));
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
  //    cross section (whole phase space) determination
  // ---
  // count # of cross section histos
  unsigned int NXSec=0;
  // loop all variables
  for(unsigned int number=0; number<xSecVariables_.size(); ++number){
    TString variable=xSecVariables_[number];
    TString label =getStringEntry(xSecLabel_[number],1);
    TString label2=getStringEntry(xSecLabel_[number],2);
    TString xSec ="xSec/"+variable;
    bool calculateXSec=true;
    // loop samples 
    for(unsigned int sample=kSig; sample<=kData; ++sample){
      // check if reco MC plot and data event yield plots are available
      if(!plotExists(histo_, "analyzeTopRecoKinematicsKinFit/"+variable, sample)){
	calculateXSec=false;
      }
    }
    // check if efficiency plot is available
    if(!plotExists(histo_, "efficiency/"+variable, kSig)){
      calculateXSec=false;
    }
    if(calculateXSec){
      // a) differential XSec from data
      // get data plot
      TString name=TString(histo_["analyzeTopRecoKinematicsKinFit/"+variable][kData]->GetName())+"kData";
      histo_[xSec][kData]=(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit/"+variable][kData]->Clone(name));
      // subtract BG(MC)
      histo_[xSec][kData]->Add((TH1F*)(histo_["analyzeTopRecoKinematicsKinFit/"+variable][kBkg  ]->Clone()), -1);
      histo_[xSec][kData]->Add((TH1F*)(histo_["analyzeTopRecoKinematicsKinFit/"+variable][kZjets]->Clone()), -1);
      histo_[xSec][kData]->Add((TH1F*)(histo_["analyzeTopRecoKinematicsKinFit/"+variable][kWjets]->Clone()), -1);
      histo_[xSec][kData]->Add((TH1F*)(histo_["analyzeTopRecoKinematicsKinFit/"+variable][kSTop ]->Clone()), -1);
      histo_[xSec][kData]->Add((TH1F*)(histo_["analyzeTopRecoKinematicsKinFit/"+variable][kDiBos]->Clone()), -1);
      // apply efficiency correction
      DivideYieldByEfficiencyAndLumi(histo_[xSec][kData], ((TH1F*)(histo_["efficiency/"+variable][kSig])), luminosity, 0);

      // b) differential XSec from Signal(MC prediction)
      histo_[xSec][kSig]=(TH1F*)(histo_["analyzeTopRecoKinematicsKinFit/"+variable][kSig]->Clone());
      DivideYieldByEfficiencyAndLumi(histo_[xSec][kSig], (TH1F*)(histo_["efficiency/"+variable][kSig]), luminosity, 0);
      // add plot to list of plots
      plotList_.push_back(xSec);
      // add axis configuration
      unsigned int positionOfRecoAxisLabel = positionInVector(plotList_, "analyzeTopRecoKinematicsKinFit/"+variable);
      TString recoAxisLabel =axisLabel_[positionOfRecoAxisLabel];
      axisLabel_.push_back(""+getStringEntry(recoAxisLabel,1)+"/"+"#frac{d#sigma}{d"+label+"} [ #frac{pb}{"+label2+"} ] (inclusive t#bar{t}#rightarrow#mu)/"+getStringEntry(recoAxisLabel,3)+"/"+getStringEntry(recoAxisLabel,4));
      // configure xSec plot histo style
      histogramStyle(*histo_[xSec][kData], kData, false);
      histogramStyle(*histo_[xSec][kSig ], kSig , true );
      // restrict axis
      if(variable=="topPt"){ 
	histo_[xSec][kData]->GetXaxis()->SetRange(1,5);
	histo_[xSec][kSig ]->GetXaxis()->SetRange(1,5);
      }
      if(variable=="topY"){ 
	histo_[xSec][kData]->GetXaxis()->SetRange(2,9);
	histo_[xSec][kSig ]->GetXaxis()->SetRange(2,9);
      }
      ++NXSec;
      // save TH1F for data in extra folder
      //saveToRootFile(outputFileName, histo_[xSec][kData], true, verbose, "xSecDataTH1FAllSystematics/"+sysLabel(systematicVariation));
    }
  }
  // ---
  //    create one legend for all 1D histos
  // ---
  unsigned int Nlegends=0;  
  TLegend *leg0 = new TLegend(0.05, 0.15, 1.05, 0.9);
  ++Nlegends;
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Kin. Fit (after selection)");
  // fill in contributing sample
  // loop samples
  for(unsigned int sample=kSig; sample<=kData; ++sample){
    // check if sampe exists in at least one plot
    bool exit=false;
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      // if found: add entry to legend
      if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)&&(!exit)){
	bool TwoThousandElevenData=false;
	if(luminosity>36.0) TwoThousandElevenData=true;
	if(sample==kData) leg0->AddEntry(histo_[plotList_[plot]][sample], sampleLabel(sample,TwoThousandElevenData)+", "+lumi+" pb^{-1}", "PL");
	else leg0->AddEntry(histo_[plotList_[plot]][sample], sampleLabel(sample), "F");
	exit=true;
      }
    }
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
  //  int NCanvas = Nplots+Nlegends;
  // a) create canvas for all plots + legends
  //  for(int sample=0; sample<NCanvas; sample++){
  for(unsigned int sample=0; sample<N1Dplots+N2Dplots+NMCeff+NXSec+Nlegends; sample++){
    char canvname[10];
    sprintf(canvname,"canv%i",sample);    
    plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*plotCanvas_[sample]);
  }

  // ---
  //    change 1D plots into stack plots
  // ---
  // loop plots -> all 1D plots will become stacked plots
  if(verbose>1) std::cout << std::endl;
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    createStackPlot(plotList_, histo_, plot, N1Dplots, verbose);
  }
  if(verbose>1) std::cout << std::endl;

  // ---
  //    do the printing
  // ---
  // a) for plots
  int canvasNumber=0;
  // loop plots
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    bool first=true;
    // open canvas and set titel corresponding to plotname in .root file
    plotCanvas_[canvasNumber]->cd(0);
    plotCanvas_[canvasNumber]->SetTitle(getStringEntry(plotList_[plot], 2)+getStringEntry(plotList_[plot], 1));
    // loop samples
    for(unsigned int sample=kSig; sample<=kData; ++sample){
      // a1) for 1D event yields, efficiency and cross section plots (existing)
      if((plot<N1Dplots)||(plot>=N1Dplots+N2Dplots)){
	// check if plot is existing
	if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)){
	  if(verbose>0){
	    std::cout << "plotting " << plotList_[plot];
	    std::cout << " from sample " << sampleLabel(sample);
	    std::cout << " to canvas " << canvasNumber << " ( ";
	    std::cout << plotCanvas_[canvasNumber]->GetTitle() << " )" << std::endl;
	  }
	  // for efficiency plots: draw grid
	  if(getStringEntry(plotList_[plot], 1)=="efficiency") plotCanvas_[canvasNumber]->SetGrid(1,1);
	  // for histos with variable binning:
	  if(binning_.count("analyzeTopRecoKinematicsKinFit/"+getStringEntry(plotList_[plot], 2))>0){
	    // get variable binning
	    TString plotName=getStringEntry(plotList_[plot], 2);
	    std::vector<double> binEdges_=binning_["analyzeTopRecoKinematicsKinFit/"+plotName];
	    // set maximum of histo to last bin considered 
	    // in variable binning (overflow excluded)
	    double firstBin=0;
	    double lastBin=binEdges_.size()-2;
	    // -2 for subtracting overflow bin
	    if(verbose>1){
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
	      plotCanvas_[canvasNumber]->SetLogy(1);
	      min=1;
	      max=exp(1.3*(std::log(max)-std::log(min))+std::log(min));
	      if(plotList_[plot]=="analyzeTopRecoKinematicsKinFit/prob") min=0.1; 
	    }
	    // get nicer int values if maximum is large enough
	    if(max>3) max = (double)roundToInt(max);
	    // axis style
	    axesStyle(*histo_[plotList_[plot]][sample], getStringEntry(axisLabel_[plot],1), getStringEntry(axisLabel_[plot],2), min, max); 
	    if(getStringEntry(plotList_[plot], 1)=="xSec") histo_[plotList_[plot]][sample]->GetYaxis()->SetTitleOffset( 1.5 );
	    // restrict x axis for different plots
	    if(getStringEntry(plotList_[plot], 2)=="topMass") histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,500);
	    if(getStringEntry(plotList_[plot], 1)!="xSec"   &&(getStringEntry(plotList_[plot], 2)=="topY"   ||
	       getStringEntry(plotList_[plot], 2)=="topYHad"|| getStringEntry(plotList_[plot], 2)=="topYLep")){
	      histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(-3,3);
	    }
	    if(getStringEntry(plotList_[plot], 2)=="ttbarY") histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(-5,5);
	    if(getStringEntry(plotList_[plot], 2)=="PartonJetDRall") histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,4);
	    // draw efficiency plots as line
	    if(getStringEntry(plotList_[plot], 1)=="efficiency") histo_[plotList_[plot]][sample]->Draw("p e1");
	    // others as histo (stack)
	    else histo_[plotList_[plot]][sample]->Draw("hist");
	    histo_[plotList_[plot]][42] = (TH1F*)(histo_[plotList_[plot]][sample]->Clone());
	  }
	  // draw other plots into same canvas
	  else{ 
	    // draw data as points
	    if(sample==kData) histo_[plotList_[plot]][sample]->Draw("p e1 X0 same");
	    else{
	      // draw efficiencies as points
	      if(getStringEntry(plotList_[plot], 1)=="efficiency") histo_[plotList_[plot]][sample]->Draw("p e1 same");
	      // draw others as histo (stack)
	      else histo_[plotList_[plot]][sample]->Draw("hist same");
	    }
	  }
	  first=false;
	  // redraw axis at the end
	  if((histo_.count(plotList_[plot])>0)&&(sample==kData)) histo_[plotList_[plot]][42]->Draw("axis same");
	}
      }
      // a3) for 2D plots
      if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)){
	// new Canvas for every plot
	plotCanvas_[canvasNumber]->cd(0);
	plotCanvas_[canvasNumber]->SetRightMargin ( 0.15 );
	plotCanvas_[canvasNumber]->SetTitle(getStringEntry(plotList_[plot],2)+getStringEntry(plotList_[plot],1)+getTStringFromInt(sample)); 
	if(verbose>1){
	  std::cout << "plotting " << plotList_[plot];
	  std::cout << " from sample " << sampleLabel(sample);
	  std::cout << " to canvas " << canvasNumber  << " ( ";
	  std::cout << plotCanvas_[canvasNumber]->GetTitle() << " )"  << std::endl;
	}
	++canvasNumber;
	// draw histo
	histo2_[plotList_[plot]][sample]->Draw("colz");
	// print correlation factor
	double d = histo2_[plotList_[plot]][sample]->GetCorrelationFactor();
	char correlation[20];
	sprintf(correlation, "%f", d);
        TString corr = (TString)correlation;
	DrawLabel("correlation: "+corr, 0.35, 0.92, 0.75, 0.99, 0.7);
      }
    }
    // for 1D hists and efficiency hists: next canvas
    if(((plot<N1Dplots)||(plot>=N1Dplots+N2Dplots))&&(histo_.count(plotList_[plot])>0)) ++canvasNumber;
  }
  // b) for legends
  plotCanvas_[canvasNumber]->cd(0);
  plotCanvas_[canvasNumber]->SetTitle("legend");
  leg0->Draw("");
  ++canvasNumber;

  // ---
  // saving
  // ---
  if(save){
    // pdf and eps only for standard analysis without variation
    if(systematicVariation==sysNo){
      if(verbose==0) gErrorIgnoreLevel=kWarning;
      // a) as pdf
      saveCanvas(plotCanvas_, outputFolder, pdfName, true, false);
      // b) as eps
      for(unsigned int idx=0; idx<plotCanvas_.size(); idx++){
	TString saveToFolder=outputFolder;
	TString title=(plotCanvas_[idx])->GetTitle();
	if(title.Contains("efficiency"                     )) saveToFolder+="effAndAcc/";
	if(title.Contains("analyzeTopPartonLevelKinematics")) saveToFolder+="partonLevel/";
	if(title.Contains("analyzeHypoKinFit"              )) saveToFolder+="kinFitPerformance/";
	if(title.Contains("xSec"                           )) saveToFolder+="xSec/";
							   
	if(title.Contains("analyzeTopRecoKinematicsKinFit" )) saveToFolder+="recoYield/";
	if(title.Contains("0")                                    ) saveToFolder=outputFolder+"genRecoCorrPlots/";
	plotCanvas_[idx]->Print(saveToFolder+(TString)(plotCanvas_[idx]->GetTitle())+".eps");      
      }
    }
    // c) root file
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
      saveToRootFile(outputFileName, plotCanvas_[idx], true, verbose,outputfolder);
    }
  }
}
