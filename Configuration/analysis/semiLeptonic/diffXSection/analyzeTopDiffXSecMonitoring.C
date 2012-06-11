#include "basicFunctions.h"

void analyzeTopDiffXSecMonitoring(double luminosity = 4967.5, bool save = true, int verbose=0, 
				  TString inputFolderName="RecentAnalysisRun",
				  //TString dataFile= "/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/analyzeDiffXData2011AllCombinedMuon.root",
				  //TString dataFile= "/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/analyzeDiffXData2011AllCombinedElectron.root",
				  TString dataFile= "/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/analyzeDiffXData2011AllCombinedElectron.root:/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/analyzeDiffXData2011AllCombinedMuon.root",
				  const std::string decayChannel = "combined", 
				  bool withRatioPlot = true, bool extrapolate=false, bool hadron=false)
{
  // ============================
  //  Set Root Style
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

  //  0: kSig      1: kBkg      2: kZjets    3: kWjets
  //  4: kQCD      5: kSTop     6: kDiBos    7: kData
  //  8: kQCDEM1   9: kQCDEM2  10: kQCDEM3  11: kQCDBCE1  12: kQCDBCE2  13: kQCDBCE3  
  // 14: kWW      15: kWZ      16: kZZ      
  // 17: kSTops   18: kSATops  19: kSTopt   20: kSATopt   21: kSToptW   22: kSAToptW
  // 18: ENDOFSAMPLEENUM

  // b) file name convention (implemented in basicFunctions.h)

  // decayChannel+"DiffXSec"+sampleName+systematicVariation+MCProduction+"PF.root"

  // decayChannel      = "elec", "muon"
  // sampleName        = "Sig", "Bkg", Wjets", "Zjets", "WW", "WZ", "ZZ", "VV", "SingleTopSchannel", 
  //                     "SingleTopTchannel", "SingleTopTWchannel", "QCD"
  // MCProductionCycle = "Summer11","Fall11"
	
  // ============================
  //  Options
  // ============================

  // a) options directly entered when calling function
  // luminosity: [/pb]

  TString lumi = getTStringFromInt(roundToInt((luminosity), false));  

  // save:    save plots?
  // verbose: set detail level of output 
  //          0: no output 
  //          1: std output
  //          2: output for debugging

  // b) options to be configured only once
  // choose if you want to set QCD artificially to 0 to avoid problems with large SF for single events
  bool setQCDtoZero=true;
  //if(withRatioPlot==true) setQCDtoZero=false;
  // get the .root files from the following folder:
  TString inputFolder = "/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName;
  // see if its 2010 or 2011 data from luminosity
  TString dataSample = "";
  if(luminosity<36) dataSample="2010";
  if(luminosity>36) dataSample="2011";
  // save all plots into the following folder
  TString outputFolder = "./diffXSecFromSignal/plots/"+decayChannel+"/";
  if(dataSample!="") outputFolder+=dataSample+"/";
  outputFolder += (withRatioPlot ? "monitoring/" : "monitoring/withoutRatioPlots/") ;
  // save all plots within a root file named:
  TString outputFileName="diffXSecTopSemi";
  if(decayChannel=="muon"    ) outputFileName+="Mu";
  if(decayChannel=="electron") outputFileName+="Elec";
  if(decayChannel=="combined") outputFileName+="Comb";
  // NOTE: reco plots are the same - whatever PS is chosen but its nice
  //       to have them in the same output file like the cross sections
  // choose phase space
  TString PS="";
  // a) for full PS use extrapolate=true;
  if(!extrapolate) PS="PhaseSpace";
  // b) for restricted phase space:
  // b1) parton PS: hadron=false
  // b2) hadron PS: hadron=true
  TString LV="Parton";
  if(!extrapolate&&hadron) LV="Hadron";
  outputFileName+=dataSample+LV+PS+".root";
  // choose name of the output .pdf file
  TString pdfName="differentialXSecMonitoring"+lumi+"pb";
  // chose wheter SSV instead of CSV btagging control plots should be shown 
  // (WITHOUT ERRORBANDS..)
  bool SSV=false;
  if(SSV) std::cout << std::endl << " for all \"...Tagged/...\" plots the SSV algorithm is chosen!" << std::endl;
  // adjust luminosity and data files for combined control plots
  double luminosityEl=0;
  double luminosityMu=0;
  TString dataFileEl="";
  TString dataFileMu="";
  if(decayChannel=="combined"&&luminosity>4500&&luminosity<5000){
    luminosityEl=4980;
    luminosityMu=4955;
    dataFileEl=getStringEntry(dataFile,1 , ":");
    dataFileMu=getStringEntry(dataFile,42, ":");
  }
 
  //  0: sysNo
  //  1: sysLumiUp                   2: sysLumiDown
  //  3: sysPUUp                     4: sysPUDown                  
  //  5: sysJESUp                    6: sysJESDown                 
  //  7: sysJERUp                    8: sysJERDown         
  //  9: sysLepEffSFNormUp          10: sysLepEffSFNormDown     
  // 11: sysLepEffSFShapeEtaUp      12: sysLepEffSFShapeEtaDown
  // 13: sysLepEffSFShapePtUp       14: sysLepEffSFShapePtDown 
  // 15: sysTriggerEffSFJetNormUp   16: sysTriggerEffSFJetNormDown
  // 17: sysTriggerEffSFJetShapeUp  18: sysTriggerEffSFJetShapeDown
  // 19: sysBtagSFUp                20: sysBtagSFDown
  // 21: sysBtagSFShapePt65Up       22: sysBtagSFShapePt65Down
  // 23: sysBtagSFShapeEta0p7Up     24: sysBtagSFShapeEta0p7Down
  // 25: sysMisTagSFUp              26: sysMisTagSFDown
  // 27: sysTopScaleUp              28: sysTopScaleDown          
  // 29: sysVBosonScaleUp           30: sysVBosonScaleDown        
  // 31: sysSingleTopScaleUp        32: sysSingleTopScaleDown
  // 33: sysTopMatchUp              34: sysTopMatchDown          
  // 35: sysVBosonMatchUp           36: sysVBosonMatchDown
  // 37: sysTopMassUp               38: sysTopMassDown
  // 39: sysQCDUp                   40: sysQCDDown                 
  // 41: sysSTopUp                  42: sysSTopDown               
  // 43: sysDiBosUp                 44: sysDiBosDown              
  // 45: sysPDFUp                   46: sysPDFDown
  // 47: sysHadUp                   48: sysHadDown
  // 49: sysGenPowheg               50: sysGenMCatNLO
  // 51: sysShapeUp                 52: sysShapeDown
  // 53: ENDOFSYSENUM

  int systematicVariation=sysNo;

  // ============================
  //     choose plots
  // ============================

  // a) list plots you would like to see ("folder/plotName") - same as in .root files (for 1D and 2D)

  TString plots1D[ ] = { 
    // (I) preselection
    // (ii) jet monitoring
    //"tightJetKinematicsPreSel/n"  ,
    //"tightJetKinematicsPreSel/en" ,
    //"tightJetKinematicsPreSel/pt" ,
    //"tightJetKinematicsPreSel/eta",
    //"tightJetKinematicsPreSel/phi",
    // (II) before btagging
    // (ii) jet monitoring
    "tightJetKinematics/n"  ,
    "tightJetKinematicsNjets1/n",
    "tightJetKinematics/en" ,
    "tightJetKinematics/pt" ,
    "tightJetKinematics/eta",
    "tightJetKinematics/phi",
    "tightJetKinematics/ht",
    "tightJetQuality/n_"    ,
    "tightJetQuality/charge",
    "tightJetQuality/nhf"   ,
    "tightJetQuality/nef"   ,
    "tightJetQuality/chf"   ,
    "tightJetQuality/cef"   ,
    "tightJetQuality/ncp"   ,
    "tightLead_0_JetKinematics/en" ,
    "tightLead_0_JetKinematics/pt" ,
    "tightLead_0_JetKinematics/eta",
    "tightLead_0_JetKinematics/phi",
    "tightLead_1_JetKinematics/en" ,
    "tightLead_1_JetKinematics/pt" ,
    "tightLead_1_JetKinematics/eta",
    "tightLead_1_JetKinematics/phi",
    "tightLead_2_JetKinematics/en" ,
    "tightLead_2_JetKinematics/pt" ,
    "tightLead_2_JetKinematics/eta",
    "tightLead_2_JetKinematics/phi",
    "tightLead_3_JetKinematics/en" ,
    "tightLead_3_JetKinematics/pt" ,
    "tightLead_3_JetKinematics/eta",
    "tightLead_3_JetKinematics/phi",
    // (iii) btag monitoring
    "tightJetQuality/btagTrkCntHighPurity",
    "tightJetQuality/btagTrkCntHighEff_"  ,
    "tightJetQuality/btagSimpleSecVtxHighEff_",
    "tightJetQuality/btagSimpleSecVtxHighPur_",
    "tightJetQuality/btagCombSecVtx_",
    "tightJetQuality/btagCombSecVtxMVA_",
    "tightJetQuality/btagJetBProbability_",
    "tightJetQuality/btagJetProbability_",
    "tightJetQuality/btagSoftMuon_",
    "tightJetQuality/btagSoftMuonByPt_",
    "tightJetQuality/btagSoftMuonByIP3d_",
    "bottomJetKinematics/n",
    // (iv) MET monitoring
    "analyzeMETMuon/metEt"   ,
    "analyzeMETMuon/metSumEt",
    // (v) Vertices and pileup
    "PUControlDistributionsBeforeBtagging/pileup",
    "PUControlDistributionsBeforeBtagging/pileup_reweighted",
    "PUControlDistributionsBeforeBtagging/pileup_reweighted_up",
    "PUControlDistributionsBeforeBtagging/pileup_reweighted_down",
    "PUControlDistributionsBeforeBtagging/npvertex",
    "PUControlDistributionsBeforeBtagging/npvertex_reweighted",
    "PUControlDistributionsBeforeBtagging/npvertex_reweighted_up",
    "PUControlDistributionsBeforeBtagging/npvertex_reweighted_down",
    // (III) after btagging 
    // (ii) jet monitoring
    "tightJetKinematicsTagged/n"  ,
    "tightJetKinematicsTagged/pt" ,
    "tightJetKinematicsTagged/eta",
    "tightJetKinematicsTagged/phi",
    "tightJetKinematicsTagged/ht",
    "tightLead_0_JetKinematicsTagged/pt" ,
    "tightLead_0_JetKinematicsTagged/eta",
    "tightLead_1_JetKinematicsTagged/pt" ,
    "tightLead_1_JetKinematicsTagged/eta",
    "tightLead_2_JetKinematicsTagged/pt" ,
    "tightLead_2_JetKinematicsTagged/eta",
    "tightLead_3_JetKinematicsTagged/pt" ,
    "tightLead_3_JetKinematicsTagged/eta",
    "bottomLead_0_JetKinematicsTagged/pt",
    "bottomLead_1_JetKinematicsTagged/pt",
    "bottomLead_0_JetKinematicsTagged/eta",
    "bottomLead_1_JetKinematicsTagged/eta",
    // (iii) btag monitoring    
    "tightJetQualityTagged/btagCombSecVtx_",
    "bottomJetKinematicsTagged/n"          ,
    // (iv) MET monitoring
    "analyzeMETMuonTagged/metEt"   ,
    "analyzeMETMuonTagged/metSumEt",
    // (v) Vertices and pileup
    "PUControlDistributionsAfterBtagging/pileup",
    "PUControlDistributionsAfterBtagging/pileup_reweighted",
    "PUControlDistributionsAfterBtagging/pileup_reweighted_up",
    "PUControlDistributionsAfterBtagging/pileup_reweighted_down",
    "PUControlDistributionsAfterBtagging/npvertex",
    "PUControlDistributionsAfterBtagging/npvertex_reweighted",
    "PUControlDistributionsAfterBtagging/npvertex_reweighted_up", 
    "PUControlDistributionsAfterBtagging/npvertex_reweighted_down", 
    // (III) after kinematic fit 
    "analyzeTopRecoKinematicsKinFit/topPt",
    "analyzeTopRecoKinematicsKinFit/topY",
    "analyzeTopRecoKinematicsKinFit/ttbarPt",
    "analyzeTopRecoKinematicsKinFit/ttbarY",
    "analyzeTopRecoKinematicsKinFit/ttbarMass",
    "analyzeTopRecoKinematicsKinFit/lepPt",
    "analyzeTopRecoKinematicsKinFit/lepEta",
    "analyzeTopRecoKinematicsKinFit/lightqPt",
    "analyzeTopRecoKinematicsKinFit/lightqEta",   
    "analyzeTopRecoKinematicsKinFit/bqPt",
    "analyzeTopRecoKinematicsKinFit/bqEta",
    "analyzeTopRecoKinematicsKinFitBeforeProbSel/prob", 
    "analyzeTopRecoKinematicsKinFitBeforeProbSel/chi2",
    // gen distributions
    "analyzeTopPartonLevelKinematics/ttbarMass",
    "analyzeTopPartonLevelKinematicsPhaseSpace/ttbarMass",
  };

  TString plots1Dmu[ ] = { 
    // (I) preselection
    // (i) muon monitoring
    "testIsoMuonQuality/relIso",
    //"kinematicMuonQualityPreSel/nHit"   ,
    //"kinematicMuonQualityPreSel/chi2"   ,
    //"kinematicMuonQualityPreSel/dB"     ,
    //"kinematicMuonQualityPreSel/dz"     ,
    //"kinematicMuonQualityPreSel/matches",  
    //"trackMuontightJetsKinematicsPreSel/dist30_",
    //"goldenMuonQualityPreSel/relIso"    , 
    //"tightMuonKinematicsPreSel/n"       ,
    // (II) before btagging
    // (i) muon monitoring
    "tightMuonKinematics/n" ,
    "tightMuonKinematics/en" ,
    "tightMuonKinematics/pt" ,
    "tightMuonKinematics/eta",
    "tightMuonKinematics/y"  ,
    "tightMuonKinematics/phi",
    "tightMuonQuality/nHit"   ,
    "tightMuonQuality/chi2"   ,
    "tightMuonQuality/dB"     ,
    "tightMuonQuality/dz"     ,
    "tightMuonQuality/ecalEn" ,
    "tightMuonQuality/hcalEn" ,
    "tightMuonQuality/relIso" ,
    "tightMuonQuality/matches",  			 
    // (III) after btagging 
    // (i) muon monitoring
    "tightMuonQualityTagged/relIso" ,
    "tightMuonKinematicsTagged/pt" ,
    "tightMuonKinematicsTagged/eta",
    "tightMuonKinematicsTagged/phi"
  };
	
  TString plots1De[ ] = { 
    // (ib) electron monitoring
    "testIsoElectronQuality/relIso",
    "tightElectronKinematics/n" ,
    "tightElectronKinematics/en" ,
    "tightElectronKinematics/et" ,
    "tightElectronKinematics/eta",
    "tightElectronKinematics/phi",
    "tightElectronQuality/etaSC"  ,
    "tightElectronQuality/dB"     ,
    "tightElectronQuality/simpleEleId70cIso", 
    "tightElectronQuality/nHitsInner",
    "tightElectronQuality/convDcot" ,
    "tightElectronQuality/convDist" ,
    "tightElectronQuality/relIso"   ,
    // (ib) electron monitoring
    "tightElectronQualityTagged/relIso",
    "tightElectronKinematicsTagged/et" ,
    "tightElectronKinematicsTagged/eta",
    "tightElectronKinematicsTagged/phi"
  };
	
  TString plots2D[ ] = { 
  };	
	
  // b) list plot axes style
  // 1D: "x-axis title"/"y-axis title"/log/rebin-factor
  // log = 0 or 1 for linear or logarithmic axis 
      
  TString axisLabel1D[ ] = { 
    // (I) preselection
    // (ii) jet monitoring
    //"N_{jets}/events/0/1",
    //"E(jets)/jets/1/1",
    //"p_{t}(jets)/jets/1/1",
    //"#eta(jets)/jets/0/5",
    //"#phi(jets)/jets/0/10",
    // (II) before btagging
    // (ii) jet monitoring
    "N_{jets};events;1;1",
    "N_{jets};events;1;1",
    "E(jets) [GeV];jets;1;1",
    "p_{t}(jets) #left[GeV#right];jets;1;1",
    "#eta(jets);jets;0;5",
    "#phi(jets);jets;0;10",
    "H_{T} #left[GeV#right];events;0;50",
    "N(jet constituents);jets;0;10",
    "jet charge;jets;0;10"         ,
    "neutral hadron fraction (jets);jets;1;1"         ,
    "neutral electromagnetic fraction (jets);jets;0;2",
    "charged hadron fraction (jets);jets;0;1"         ,
    "charged electromagnetic fraction (jets);jets;1;1",
    "N_{charged particles} (jets);jets;0;2"           ,
    "E(lead 1^{st} jet) [GeV];events;1;2",
    "p_{t}(lead 1^{st} jet) #left[GeV#right];events;0;5",
    "#eta(lead 1^{st} jet);events;0;5",
    "#phi(lead 1^{st} jet);events;0;10",
    "E(lead 2^{nd} jet) [GeV];events;1;2",
    "p_{t}(lead 2^{nd} jet) #left[GeV#right];events;0;5",
    "#eta(lead 2^{nd} jet);events;0;5",
    "#phi(lead 2^{nd} jet);events;0;10",
    "E(lead 3^{rd} jet) [GeV];events;1;2",
    "p_{t}(lead 3^{rd} jet) #left[GeV#right];events;0;5",
    "#eta(lead 3^{rd} jet);events;0;5",
    "#phi(lead 3^{rd} jet);events;0;10",
    "E(lead 4^{th} jet) [GeV];events;1;2",
    "p_{t}(lead 4^{th} jet) #left[GeV#right];events;0;5",
    "#eta(lead 4^{th} jet);events;0;5",
    "#phi(lead 4^{th} jet);events;0;10",
    // (iii) btag monitoring
    "b-discr.(TCHP);jets;0;2"        ,
    "b-discr.(TCHE);jets;0;2"	,
    "b-discr.(SSV HEff);jets;1;2"	,
    "b-discr.(SSV HPur);jets;0;2"	,
    "b-discr.(CSV);jets;0;2"	,
    "b-discr.(CSVMVA);jets;0;2"	,
    "b-discr.(JetBProb);jets;0;5"	,
    "b-discr.(JetProb);jets;0;5"	,
    "b-discr.(soft#mu);jets;0;10"	,
    "b-discr.(soft#muPt);jets;0;10"  ,                  
    "b-discr.(soft#muIP3d);jets;0;10",
    "N_{b-jets};events;1;1"      ,
    // (iv) MET monitoring 
    "#slash{E}_{T} #left[GeV#right];events;0;10",
    "#SigmaE_{T} [GeV];events;0;50"  ,
    // (v) Vertices and pileup
    "Number of PU Events;Frequency;1;1",
    "Number of PU Events (Reweighted);Frequency;1;1",
    "Number of PU Events (Reweighted sysUp);Frequency;1;1",
    "Number of PU Events (Reweighted sysDown);Frequency;1;1",
    "Number of Vertices;Frequency;1;1",
    "Number of Vertices (Reweighted);Frequency;1;1",
    "Number of Vertices (Reweighted sysUp);Frequency;1;1",
    "Number of Vertices (Reweighted sysDown);Frequency;1;1",
    // (III) after btagging 
    // (ii) jet monitoring
    "N_{jets};events;1;1",
    "p_{t}(jets) #left[GeV#right];jets;1;2",
    "#eta(jets);jets;0;5" ,
    "#phi(jets);jets;0;10",
    "H_{T} [GeV];events;0;100",
    "p_{t}(lead 1^{st} jet) #left[GeV#right];events;1;5",
    "#eta(lead 1^{st} jet);events;0;5" ,
    "p_{t}(lead 2^{nd} jet) #left[GeV#right];events;1;5",
    "#eta(lead 2^{nd} jet);events;0;5" ,
    "p_{t}(lead 3^{rd} jet) #left[GeV#right];events;1;5",
    "#eta(lead 3^{rd} jet);events;0;5" ,
    "p_{t}(lead 4^{th} jet) #left[GeV#right];events;1;5",
    "#eta(lead 4^{th} jet);events;0;5" ,
    "p_{t}(lead 1^{st} b-tagged jet) #left[GeV#right];events;1;5",
    "p_{t}(lead 2^{nd} b-tagged jet) #left[GeV#right];events;1;5",
    "#eta(lead 1^{st} b-tagged jet);events;0;5" ,
    "#eta(lead 2^{nd} b-tagged jet);events;0;5" ,
    // (iii) btag monitoring    
    "b-discr.(CSV);jets;0;2",
    "N_{b-jets};events;1;1" ,
    // (iv) MET monitoring 
    "#slash{E}_{T} #left[GeV#right];events;0;20",
    "#SigmaE_{T} [GeV];events;0;30",
    // (v) Vertices and pileup
    "Number of PU Events;Frequency;0;1",
    "Number of PU Events (Reweighted);Frequency;0;1",
    "Number of PU Events (Reweighted sysUp);Frequency;0;1",
    "Number of PU Events (Reweighted sysDown);Frequency;0;1",
    "Number of Vertices;Frequency;0;1",
    "Number of Vertices (Reweighted);Frequency;0;1",
    "Number of Vertices (Reweighted sysUp);Frequency;0;1", 
    "Number of Vertices (Reweighted sysDown);Frequency;0;1", 
    // (III) after kinematic fit 
    "p^{t}^{t and #bar{t}} #left[GeV#right];N^{t and #bar{t}};0;20",
    "y^{t and #bar{t}};N^{t and #bar{t}};0;1",
    "p^{t}^{t#bar{t}} #left[GeV#right];N^{t#bar{t}};0;20",
    "y^{t#bar{t}};N^{t#bar{t}};0;1",
    "m^{t#bar{t}} #left[GeV#right];N^{t#bar{t}};0;20",
    "p^{t}^{l} #left[GeV#right];N^{l};0;20",    
    "#eta^{l};N^{l};0;1",
    "p^{t}^{q} #left[GeV#right];N^{q};0;20",    
    "#eta^{q};N^{q};0;1",
    "p^{t}^{b and #bar{b}} #left[GeV#right];N^{b and #bar{b}};0;20",    
    "#eta^{b and #bar{b}};N^{b and #bar{b}};0;1",
    "probability (best fit hypothesis);events;1;25", 
    "#chi^{2} (best fit hypothesis);events;0;10",
    // gen distributions
    "m^{t#bar{t}} #left[GeV#right] parton all truth;events;1;1",
    "m^{t#bar{t}} #left[GeV#right] parton lv truth;events;1;1"

  };

  TString axisLabel1De[ ] = {
    // (iv) electron monitoring
    "PF relIso(e) N-1;events;0;1",
    "N_{e};events;0;1" ,
    "E(e) [GeV];events;0;2",
    "E_{t}(e) [GeV];events;0;1" ,
    "#eta(e);events;0;5",
    "#phi(e);events;0;5",
    "#eta(S.C.);events;0;1"  ,
    "d_{xy} (e wrt. beamspot) [cm];events;0;1",
    "simpleEleId70cIso;events;0;1", 
    "nHitsInner(conv);events;0;1",
    "convCot;events;0;5",
    "convDist;events;0;5" ,
    "PF relIso(e);events;0;1" ,
    // (iv) electron monitoring
    "PF relIso(e);events;0;1" ,
    "E_{t}(e) [GeV];events;0;2",
    "#eta(e);events;0;1",
    "#phi(e);events;0;1"
  };
	
  TString axisLabel1Dmu[ ] = {
    // (I) preselection
    // (i) muon monitoring
    "PF relIso(#mu) N-1;events;0;1",
    //"N_{hits}(inner tracker #mu)/events/0/1"          ,
    //"#chi^{2} (global trackfit #mu(pt,#eta))/events/1/1",
    //"d_{xy} (#mu(pt,#eta) wrt. beamspot)/events/0/1" ,
    //"d_{z} (#mu(pt,#eta))/events/0/10",
    //"N_{matched #mu segments}(#mu(pt,#eta))/events/0/1",
    //"#DeltaR(jet(pt,#eta,ID), #mu(pt, #eta, track criteria))/events/0/1",
    //"relIso(#mu(no isolation))/events/0/1",
    //"N_{#mu}/events/0/1",
    // (II) before btagging
    // (i) muon monitoring
    "N_{#mu};events;0;1"   ,
    "E(#mu);events;0;2"    ,
    "p_{t}(#mu);events;0;1",
    "#eta(#mu);events;0;5" ,
    "y(#mu);events;0;5"    ,	
    "#phi(#mu);events;0;5" ,
    "N_{hits}(inner tracker #mu);events;0;1"          ,
    "#chi^{2} (global trackfit #mu);events;1;1",
    "d_{xy} (#mu wrt. beamspot) [cm];events;0;1" ,
    "d_{z} (#mu) [cm];events;0;10"               ,
    "E_{Ecal} (#mu);events;1;1",
    "E_{Hcal} (#mu);events;1;1",
    "PF relIso(#mu);events;0;1",
    "N_{matched #mu segments}(#mu);events;0;1",
    // (III) after btagging 
    // (i) muon monitoring
    "PF relIso(#mu);events;0;1",
    "p_{t}(#mu);events;0;2",
    "#eta(#mu);events;0;1",
    "#phi(#mu);events;0;10",
  };

  // 2D: "x-axis title"/"y-axis title"
  TString axisLabel2D[ ] = {
  };
  // ======================================================================
  //  Count number of plots + cross-check to number of axis-label defined 
  // ======================================================================
  unsigned int N1Dplots = sizeof(plots1D)/sizeof(TString);
  if(decayChannel=="electron") N1Dplots+=(sizeof(plots1De )/sizeof(TString));
  if(decayChannel=="muon"    ) N1Dplots+=(sizeof(plots1Dmu)/sizeof(TString));
  unsigned int N2Dplots = sizeof(plots2D)/sizeof(TString);
  // get number fo axis labels and check if it corresponds to number of plots
  unsigned int Naxislabels = sizeof(axisLabel1D)/sizeof(TString);
  if(decayChannel=="electron") Naxislabels+=(sizeof(axisLabel1De )/sizeof(TString));
  if(decayChannel=="muon"    ) Naxislabels+=(sizeof(axisLabel1Dmu)/sizeof(TString));
  if(N1Dplots != Naxislabels){
    std::cout << "ERROR - 1D plots: Number of plots and axis label do not correspond .... Exiting macro!" << std::endl;
    exit(1);
  }
  if(N2Dplots != sizeof(axisLabel2D)/sizeof(TString)){
    std::cout << "ERROR - 2D plots: Number of plots and axis label do not correspond .... Exiting macro!" << std::endl;
    exit (1);
  }
  // run automatically in batch mode if there are many canvas
  if((N1Dplots+N2Dplots)>15) gROOT->SetBatch();
	
  // ===================================
  //  Open the standard analysis files
  // ===================================
  std::map<unsigned int, TFile*> files_, filesMu_, filesEl_;
  if(decayChannel!="combined") files_ = getStdTopAnalysisFiles(inputFolder, systematicVariation, dataFile, decayChannel);
  else{
    filesMu_ = getStdTopAnalysisFiles(inputFolder, systematicVariation, dataFileMu, "muon"    );
    filesEl_ = getStdTopAnalysisFiles(inputFolder, systematicVariation, dataFileEl, "electron");
  }

  // =====================
  //  Loading histos
  // =====================
  // collect all plot names in vector (first 1D, then 2D)
  std::vector<TString> plotList_;
  plotList_.insert( plotList_.begin(), plots1D, plots1D + sizeof(plots1D)/sizeof(TString) );
  if(decayChannel=="electron") plotList_.insert( plotList_.end(), plots1De , plots1De  + sizeof(plots1De )/sizeof(TString) );
  if(decayChannel=="muon"    ) plotList_.insert( plotList_.end(), plots1Dmu, plots1Dmu + sizeof(plots1Dmu)/sizeof(TString) );
  plotList_.insert( plotList_.end(), plots2D, plots2D + sizeof(plots2D)/sizeof(TString) );	
	
  // container for all histos (1D&2D)
  // example for acess: histo_["plotName"][sampleNr]
  std::map< TString, std::map <unsigned int, TH1F*> > histo_, histoEl_, histoMu_;
  std::map< TString, TH1F* > histoErrorBand_;
  std::map< TString, std::map <unsigned int, TH2F*> > histo2_, histo2El_, histo2Mu_;
  // a) Save all histos from plotList_ that exist in files_ into histo_ and histo2_
  // b) Count total number of plots as Nplots
  // c) Special action required for control plots regarding PU and nVertex:
  //    - Compare the reweighted histos in MC to the same but unweighted histo in data
  //    - Strip off appendices from histo-names as redundant part of name to get the according plots from data
  if(verbose>0) std::cout << std::endl;
  int Nplots=0;
  std::vector<TString> vecRedundantPartOfNameInData;
  vecRedundantPartOfNameInData.push_back("_reweighted_up");
  vecRedundantPartOfNameInData.push_back("_reweighted_down");
  vecRedundantPartOfNameInData.push_back("_reweighted");
  if(decayChannel!="combined") getAllPlots(files_, plotList_, histo_, histo2_, N1Dplots, Nplots, verbose, decayChannel, &vecRedundantPartOfNameInData, SSV);
  else{
    getAllPlots(filesMu_, plotList_, histoMu_, histo2Mu_, N1Dplots, Nplots, verbose, "muon"    , &vecRedundantPartOfNameInData, SSV);
    getAllPlots(filesEl_, plotList_, histoEl_, histo2El_, N1Dplots, Nplots, verbose, "electron", &vecRedundantPartOfNameInData, SSV);
  }

  
  // ==========================================
  //  Lumiweighting for choosen luminosity
  // ==========================================
  // scale every histo in histo_ and histo2_ to the corresponding luminosity
  // NOTE: luminosity [/pb]
  if(decayChannel!="combined") scaleByLuminosity(plotList_, histo_, histo2_, N1Dplots, luminosity, verbose, systematicVariation, decayChannel);
  else{
    scaleByLuminosity(plotList_, histoMu_, histo2Mu_, N1Dplots, luminosityMu, verbose, systematicVariation, "muon"    );
    scaleByLuminosity(plotList_, histoEl_, histo2El_, N1Dplots, luminosityEl, verbose, systematicVariation, "electron");
  }

  // =======================================================
  //  Add single top channels and DiBoson contributions
  // =======================================================
  // for SingleTop and DiBoson samples:
  // every plot plotList_ existing in sTop/ diBoson .root file
  // will be combined and saved in the histo_ and histo2_ map
  // reCreate: reCreate combined plots if they are already existing
  bool reCreate=false;
  if(decayChannel!="combined")  AddSingleTopAndDiBoson(plotList_, histo_, histo2_, N1Dplots, verbose, reCreate, decayChannel);
  else{
    AddSingleTopAndDiBoson(plotList_, histoMu_, histo2Mu_, N1Dplots, verbose, reCreate, "muon"    ); 
    AddSingleTopAndDiBoson(plotList_, histoEl_, histo2El_, N1Dplots, verbose, reCreate, "electron");
  }


  // =======================================================
  //  Add decay channels for combined control plot
  // =======================================================
  if(decayChannel=="combined"){
    // loop samples
    for(unsigned int sample=kSig; sample<=kData; ++sample){
      if(verbose>1) std::cout << sampleLabel(sample) << std::endl;
      // loop plots
      for(unsigned int plot=0; plot<plotList_.size(); ++plot){
	if(verbose>1) std::cout << plotList_[plot] << " : " ;
	// a) 1D
	if((plot<N1Dplots)&&(histoMu_.count(plotList_[plot])>0)&&(histoMu_[plotList_[plot]].count(sample)>0)&&(histoEl_.count(plotList_[plot])>0)&&(histoEl_[plotList_[plot]].count(sample)>0)){ 
	  if(verbose>1) std::cout << "1D" << std::endl;
	  histo_[plotList_[plot]][sample]=(TH1F*)(histoMu_[plotList_[plot]][sample]->Clone());
	  histo_[plotList_[plot]][sample]->Add((TH1F*)(histoEl_[plotList_[plot]][sample]->Clone()));
	}
	// b) 2D
	else if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)){
	  if(verbose>1) std::cout << "2D" << std::endl;
	  histo2_[plotList_[plot]][sample]=(TH2F*)(histo2Mu_[plotList_[plot]][sample]->Clone());
	  histo2_[plotList_[plot]][sample]->Add((TH2F*)(histo2El_[plotList_[plot]][sample]->Clone()));
	}
	else{
	  if(verbose>1) std::cout << "NOT FOUND" << std::endl;
	}
      }   
    }
  }

  // ============================
  //  Configure histograms
  // ============================
  // needs: plotList_, histo_, histo2_, N1Dplots, axisLabel_, axisLabel1D, axisLabel2D
  std::vector<TString> axisLabel_;
  axisLabel_.insert( axisLabel_.begin(), axisLabel1D, axisLabel1D + sizeof(axisLabel1D)/sizeof(TString) );
  if(decayChannel=="electron") axisLabel_.insert( axisLabel_.end(), axisLabel1De , axisLabel1De +sizeof(axisLabel1De )/sizeof(TString) );
  if(decayChannel=="muon"    ) axisLabel_.insert( axisLabel_.end(), axisLabel1Dmu, axisLabel1Dmu+sizeof(axisLabel1Dmu)/sizeof(TString) );
  axisLabel_.insert( axisLabel_.end()  , axisLabel2D, axisLabel2D + sizeof(axisLabel2D)/sizeof(TString) );
  if(verbose>1){
    std::cout << "(plot, x Axis label, y Axis label, log scale?, rebinning factor):" << std::endl;
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      std::cout << plotList_[plot];
      std::cout << ": " << getStringEntry(axisLabel_[plot],1,";");
      std::cout << ", " << getStringEntry(axisLabel_[plot],2,";");
      if(plot<N1Dplots){
	std::cout << ", " << getStringEntry(axisLabel_[plot],3,";");
	std::cout << ", " << getStringEntry(axisLabel_[plot],4,";");
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
	// Default configuration
	histogramStyle(*histo_[plotList_[plot]][sample], sample, true);
	// Special configurations
	if(getStringEntry(plotList_[plot], 2)=="PartonJetDRall") histo_[plotList_[plot]][sample] -> SetNdivisions(816);
	// set QCD to 0
	if(setQCDtoZero&&sample==kQCD&&(plotList_[plot].Contains("Tagged")||plotList_[plot].Contains("analyzeTopReco"))) histo_[plotList_[plot]][sample]->Scale(0.);
      }
      // b) 2D
      if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)){
	histStyle2D( *histo2_[plotList_[plot]][sample], sampleLabel(sample,decayChannel), getStringEntry(axisLabel_[plot],1,";"), getStringEntry(axisLabel_[plot],2,";"));
      }
    }
  }
  
  // ============================
  //  Event composition
  // ============================
  std::map< TString, std::map <unsigned int, double> > events_;
  // a) get event numbers
  std::vector<TString> selection_;
  selection_.push_back("tightJetKinematics/n"      );
  selection_.push_back("tightJetKinematicsTagged/n");
  selection_.push_back("analyzeTopRecoKinematicsKinFit/ttbarMass");  
  unsigned int MCBG=ENDOFSAMPLEENUM;
  events_[selection_[0]][MCBG]=0;
  events_[selection_[1]][MCBG]=0; 
  events_[selection_[2]][MCBG]=0;
  // loop pretagged/tagged
  for(unsigned int step=0; step<selection_.size(); ++step){
    // loop samples
    for(unsigned int sample=kSig; sample<=kData; ++sample){
      // save number
      events_[selection_[step]][sample]=histo_[selection_[step]][sample]->Integral(0,histo_[selection_[step]][sample]->GetNbinsX()+1);
      // add non ttbar MC
      if(sample>kSig&&sample<kData) events_[selection_[step]][MCBG]+=events_[selection_[step]][sample];
    }
  }
  // b) print composition (only if ratio is also drawn)
  if(verbose>=0&&withRatioPlot){
    double NttbarFull= histo_["analyzeTopPartonLevelKinematics/ttbarMass"          ][kSig]->Integral(0, histo_["analyzeTopPartonLevelKinematics/ttbarMass"          ][kSig]->GetNbinsX()+1);
    double NttbarPS  = histo_["analyzeTopPartonLevelKinematicsPhaseSpace/ttbarMass"][kSig]->Integral(0, histo_["analyzeTopPartonLevelKinematicsPhaseSpace/ttbarMass"][kSig]->GetNbinsX()+1);
    double BR=0.145888;
    double A=NttbarPS/NttbarFull;
    // loop pretagged/tagged
    for(unsigned int step=0; step<selection_.size(); ++step){    
      // print label
      switch (step){
          case 0 : std::cout << std::endl << " Event composition ---- pre-tagged, derived from: "+selection_[step]          << std::endl; break;
          case 1 : std::cout << std::endl << " Event composition ---- after b-tagging, derived from: "+selection_[step]     << std::endl; break;
          case 2 : std::cout << std::endl << " Event composition ---- after kinematic fit, derived from: "+selection_[step] << std::endl; break;
          default: break;
      }
      // all MC events
      double NAllMC=events_[selection_[step]][kSig]+events_[selection_[step]][MCBG];
      double NData=events_[selection_[step]][kData];
      // print yield and composition
      std::cout << " Events observed in data: " << NData << std::endl;
      std::cout << " Events expected from MC: " << NAllMC << std::endl << std::endl;
      std::cout << " Expected event composition:"   << std::endl; 
      std::cout << " ttbar SG:   " << std::setprecision(4) << std::fixed << events_[selection_[step]][kSig  ] / NAllMC << std::endl;
      std::cout << " ttbar BG:   " << std::setprecision(4) << std::fixed << events_[selection_[step]][kBkg  ] / NAllMC << std::endl;
      std::cout << " W + Jets:   " << std::setprecision(4) << std::fixed << events_[selection_[step]][kWjets] / NAllMC << std::endl; 
      std::cout << " Z + Jets:   " << std::setprecision(4) << std::fixed << events_[selection_[step]][kZjets] / NAllMC << std::endl;
      std::cout << " QCD:        " << std::setprecision(4) << std::fixed << events_[selection_[step]][kQCD  ] / NAllMC;
      if(setQCDtoZero&&events_[selection_[step]][kQCD]==0.0)  std::cout  << " (artificially set to 0)";
      std::cout << std::endl;
      std::cout << " Single Top: " << std::setprecision(4) << std::fixed << events_[selection_[step]][kSTop ] / NAllMC << std::endl;
      std::cout << " DiBoson:    " << std::setprecision(4) << std::fixed << events_[selection_[step]][kDiBos] / NAllMC << std::endl;
      double NnonTtbarBG=NAllMC-events_[selection_[step]][kSig]-events_[selection_[step]][kBkg];
      double ttbarSigFrac=events_[selection_[step]][kSig]/(events_[selection_[step]][kSig]+events_[selection_[step]][kBkg]);
      double eff=events_[selection_[step]][kSig]/NttbarPS;  
      double luminosity2=luminosity;
      if(decayChannel=="combined") luminosity2=luminosityMu+luminosityEl;
      double xSec=(NData-NnonTtbarBG)*ttbarSigFrac/(A*eff*BR*luminosity2);
      std::cout << std::endl;
      std::cout << "    inclusive cross section: " << std::setprecision(2) << std::fixed << xSec << std::endl;
      std::cout << "      N(nonttBG): " << std::setprecision(2) << std::fixed << NnonTtbarBG << std::endl;
      std::cout << "      tt SG frac: " << std::setprecision(2) << std::fixed << ttbarSigFrac << std::endl;
      std::cout << "      BR:         " << std::setprecision(2) << std::fixed << BR  << std::endl;
      std::cout << "      efficiency: " << std::setprecision(2) << std::fixed << eff << std::endl;
      std::cout << "      acceptance: " << std::setprecision(2) << std::fixed << A   << std::endl;
    }
    std::cout << std::endl << " The event composition is only printed when running the monitoring macro using the option 'withRatioPlot=true' " << std::endl;
  }
	
  // ============================
  //  Rebinning 1D histograms
  // ============================
  // loop samples
  for(unsigned int sample=kSig; sample<=kData; ++sample){
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      TString plotName=plotList_[plot];
      // check if plot exists and is 1D
      if((plot<N1Dplots)&&(plotExists(histo_, plotName, sample))){
	// equidistant binning
	double reBinFactor = atof(((string)getStringEntry(axisLabel_[plot],4,";")).c_str());
	if(reBinFactor>1){
	  equalReBinTH1(reBinFactor, histo_, plotName, sample);
	}
      }
    }
  }

  // ===============================================================
  //  Errors for uncertainty bands from ttbar Xsec and luminosity
  // ===============================================================
  if(verbose>0) std::cout << std::endl << " Start calculating error bands for 1D plots .... ";
  if(!SSV) makeUncertaintyBands(histo_, histoErrorBand_, plotList_, N1Dplots);
  if(verbose>0) std::cout << " .... Finished." << std::endl; 

  // ========================================================
  //  Create Legends
  // ========================================================
  unsigned int Nlegends=0; 
  TLegend *leg  = new TLegend(); 
  TLegend *leg0 = new TLegend(0.05, 0.15, 1.05, 0.9);
  TLegend *leg1 = new TLegend(0.05, 0.15, 1.05, 0.9);
  Nlegends+=3;
  legendStyle(*leg,"");
  legendStyle(*leg0,"After Selection, Before b-Tagging");
  legendStyle(*leg1,"After Selection and b-Tagging");

  // Set legend entries
  // - First entry: data
  // - Following entries: MC samples (if existing)
  // - Last entry: uncertainty band

  // Data:
  TString lumilabel = Form("%2.1f fb^{-1}",luminosity/1000);
  leg ->AddEntry(histo_[plotList_[plotList_.size()-3]][kData], decayChannel=="combined" ? sampleLabel(kData) : sampleLabel(kData,decayChannel),"P");
  leg0->AddEntry(histo_[plotList_[plotList_.size()-3]][kData], decayChannel=="combined" ? sampleLabel(kData) : sampleLabel(kData,decayChannel)+", "+lumilabel,"PL");
  leg1->AddEntry(histo_[plotList_[plotList_.size()-3]][kData], decayChannel=="combined" ? sampleLabel(kData) : sampleLabel(kData,decayChannel)+", "+lumilabel,"PL");
 
  // MC samples (add only if sample exists in at least one plot, then quit plot-loop to avoid duplication of entries)
  for(unsigned int sample=kSig; sample<kData; ++sample){
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size()-1; ++plot){  // <plotList_.size()-1, because last entry is for data (see above)
      if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)){
	leg ->AddEntry(histo_[plotList_[plot]][sample], decayChannel=="combined" ? sampleLabel(sample) : sampleLabel(sample,decayChannel), "F");
	leg0->AddEntry(histo_[plotList_[plot]][sample], decayChannel=="combined" ? sampleLabel(sample) : sampleLabel(sample,decayChannel), "F");
	leg1->AddEntry(histo_[plotList_[plot]][sample], decayChannel=="combined" ? sampleLabel(sample) : sampleLabel(sample,decayChannel), "F");
	break;
      }
    }
  }
  
  // Uncertainty band
  if(histoErrorBand_.size() > 0 && plotList_.size() > 0){
    leg ->AddEntry(histoErrorBand_[plotList_[0]],"Uncertainty","F");
    leg0->AddEntry(histoErrorBand_[plotList_[0]],"Uncertainty","F");
    leg1->AddEntry(histoErrorBand_[plotList_[0]],"Uncertainty","F");
  }

  // =====================
  //  Create canvas
  // =====================
  std::vector<TCanvas*> plotCanvas_;
  // a) create canvas for all plots + legends
  for(unsigned int sample=0; sample<N1Dplots+N2Dplots+Nlegends; sample++){
    char canvname[10];
    sprintf(canvname,"canv%i",sample);    
    plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );
    //canvasStyle(*plotCanvas_[sample]);
  }
	
  // ===================================
  //  Change 1D plots into stack plots
  // ===================================
  // loop plots -> all 1D plots will become stacked plots
  if(verbose>1) std::cout << std::endl;
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    createStackPlot(plotList_, histo_, plot, N1Dplots, verbose, decayChannel);
  }
  if(verbose>1) std::cout << std::endl;
	
  // =====================
  //  Do the printing
  // =====================
  //
  // a) for plots
  //
  int canvasNumber=0;
  // loop plots
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    bool first=true;
    // open canvas and set title corresponding to plotname in .root file
    plotCanvas_[canvasNumber]->cd(0);
    plotCanvas_[canvasNumber]->SetTitle(getStringEntry(plotList_[plot], 2)+getStringEntry(plotList_[plot], 1));	    
    // loop samples
    for(unsigned int sample=kSig; sample<=kData; ++sample){
      // a1) for 1D event yields, efficiency and cross section plots (existing)
      if((plot<N1Dplots)||(plot>=N1Dplots+N2Dplots)){
	// check if plot is existing
       	if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)&&histo_[plotList_[plot]][sample]){
	  histo_[plotList_[plot]][sample]->GetXaxis()->SetNoExponent(true);
	  if(verbose>0){
	    std::cout << " Plotting "    << plotList_[plot];
	    if(decayChannel!="combined") std::cout << " from sample " << sampleLabel(sample,decayChannel);
	    else std::cout << " from sample " << sampleLabel(sample, "muon") << " and " << sampleLabel(sample, "electron");
	    std::cout << " to canvas "   << canvasNumber << " ( " << plotCanvas_[canvasNumber]->GetTitle() << " )";
	    std::cout << std::endl;
	  }
	  // first plot
	  if(first){
	    // plot to take maximum from
	    TString maxFrom=plotList_[plot];
	    if(plotList_[plot].Contains("_JetKinematicsTagged/pt")) maxFrom="tightLead_3_JetKinematicsTagged/pt";
	    if(plotList_[plot].Contains("_JetKinematics/pt"))       maxFrom="tightLead_3_JetKinematics/pt";
	    if(!histo_[maxFrom].count(sample)>0||!histo_[maxFrom].count(kData)>0) maxFrom=plotList_[plot];
	    if(verbose>1) std:: cout << " Take max for histo " << plotList_[plot] << " from histo " << maxFrom << std::endl;
	    // min / max
	    double max = 1.3*histo_[maxFrom][sample]->GetMaximum();
	    // if data file exists
	    if(histo_.count(maxFrom)>0&&histo_[maxFrom].count(kData)>0&&histo_[plotList_[plot]][kData]){
	      // and has larger maximum
	      if(max < 1.3*histo_[maxFrom][kData]->GetMaximum()){
		// take this maximum
		max = 1.3*histo_[maxFrom][kData]->GetMaximum();
		if(verbose>1) std:: cout << " Take max from data! " << std::endl;
	      }
	    }
	    double min = 0;
	    // log plots
	    if(getStringEntry(axisLabel_[plot],3,";")=="1"){
	      plotCanvas_[canvasNumber]->SetLogy(1);
	      min=1;
	      max=exp(1.3*(std::log(max)-std::log(min))+std::log(min));
	      if(plotList_[plot].Contains("analyzeTopRecoKinematicsKinFit")&&plotList_[plot].Contains("/prob")) min=0.1; 
	      if(plotList_[plot].Contains("_JetKinematicsTagged/pt")) min=0.1;
	    }
	    // get nicer int values if maximum is large enough
	    if(max>3) max = (double)roundToInt(max);
	    if(plotList_[plot].Contains("btagSimpleSecVtx"))max*=0.8;
	    // Set x-axis range for special plots
	    if(getStringEntry(plotList_[plot], 2)=="nHit"  ) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(10,30 );
	    if(getStringEntry(plotList_[plot], 2)=="chi2"  ){ 
	      if(getStringEntry(plotList_[plot], 1).Contains("analyzeTopRecoKinematicsKinFit")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,60);
	      else histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,10);
	    }
	    if(getStringEntry(plotList_[plot], 2)=="dB"    ) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,0.02);
	    if(plotList_[plot].Contains("relIso")&&!plotList_[plot].Contains("test")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,0.15);
	    if(plotList_[plot].Contains("tightJetKinematics/n")||plotList_[plot].Contains("tightJetKinematicsTagged/n")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(4,10);
	    if(plotList_[plot].Contains("tightJetKinematicsNjets1/n")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(1,10);
	    if(plotList_[plot].Contains("_JetKinematics/en")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,500);
	    if(plotList_[plot].Contains("_JetKinematics/pt")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,300);
	    if(plotList_[plot].Contains("analyzeMETMuon/metSumEt")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(200,1400);
	    if(plotList_[plot].Contains("analyzeMETMuon/metEt")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,300);
	    if(plotList_[plot].Contains("bottomJetKinematics")&&plotList_[plot].Contains("/n")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,5);
	    if(plotList_[plot].Contains("JetKinematicsTagged")&&plotList_[plot].Contains("pt")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0,350);
	    if(plotList_[plot].Contains("btagSimpleSecVtx")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(-1,7);	
	    if(plotList_[plot].Contains("lepPt" )) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0.,250.);
	    if(plotList_[plot].Contains("lepEta")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(-2.5,2.5);
	    if(plotList_[plot].Contains("bqPt"  )) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0.,250.);
	    if(plotList_[plot].Contains("bqEta" )) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(-2.5,2.5);
	    if(plotList_[plot].Contains("topPt" )) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(0.,400.);
	    if(plotList_[plot].Contains("topY"  )) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(-2.5,2.5);
	    if(plotList_[plot].Contains("ttbarY")) histo_[plotList_[plot]][sample]->GetXaxis()->SetRangeUser(-2.0,2.0);	
	    // axis style
	    axesStyle(*histo_[plotList_[plot]][sample], getStringEntry(axisLabel_[plot],1,";"), getStringEntry(axisLabel_[plot],2,";"), min, max);
	    histo_[plotList_[plot]][sample]->GetXaxis()->SetNoExponent(true);
	    if(max<100) histo_[plotList_[plot]][sample]->GetYaxis()->SetNoExponent(true);
	    else histo_[plotList_[plot]][sample]->GetYaxis()->SetNoExponent(false);
	    // draw histos (as stack)
	    histo_[plotList_[plot]][sample]->Draw("hist X0");
	    histo_[plotList_[plot]][ENDOFSAMPLEENUM] = (TH1F*)(histo_[plotList_[plot]][sample]->Clone());
	    histo_[plotList_[plot]][ENDOFSAMPLEENUM]->GetXaxis()->SetNoExponent(true);
	  }
	  // draw other plots into same canvas 
	  else{ 
	    // draw data as points
	    if(sample==kData) histo_[plotList_[plot]][sample]->Draw("p e X0 same");
	    // draw others as histo (stack)
	    else histo_[plotList_[plot]][sample]->Draw("hist X0 same");
	  }
	  first=false;
	  // at the end:
	  if((sample==kData)&&(histo_.count(plotList_[plot])>0)&&histo_[plotList_[plot]][sample]){
	    if(!SSV){
	      // configure style of and draw uncertainty bands
	      histoErrorBand_[plotList_[plot]]->SetMarkerStyle(0);
	      histoErrorBand_[plotList_[plot]]->SetFillColor(1);
	      histoErrorBand_[plotList_[plot]]->SetFillStyle(3004);
	      gStyle->SetErrorX(0.5);  
	      histoErrorBand_[plotList_[plot]]->Draw("E2 SAME");
	    }
	    // redraw axis 
	    histo_[plotList_[plot]][ENDOFSAMPLEENUM]->Draw("axis X0 same");
	    if((unsigned int)canvasNumber<plotCanvas_.size()-Nlegends){
	      // draw label indicating event selection, common labels and legend
	      TString label = "pre-Tagged";
	      if(plotList_[plot].Contains("Tagged") || plotList_[plot].Contains("AfterBtagging")){ 
		label = "Tagged";
		if(SSV) label+=" SSV";
	      }
	      if(plotList_[plot].Contains("test"  )) label = "N-1 Selection";
	      if(plotList_[plot].Contains("PreSel")) label = "Pre-Selected";
	      if(plotList_[plot].Contains("Njets1")) label = "#geq 1 Jet";
	      if(plotList_[plot].Contains("KinFit")) label = "";
	      DrawLabel(label, 1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength() - 0.2, 1.0 - gStyle->GetPadTopMargin() - gStyle->GetTickLength() - 0.05,
		 	       1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength(),       1.0 - gStyle->GetPadTopMargin() - gStyle->GetTickLength(), 12    );
	      leg->SetX1NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength() - 0.20);
	      leg->SetY1NDC(1.0 - gStyle->GetPadTopMargin()   - gStyle->GetTickLength() - 0.05 - 0.03 * leg->GetNRows());
	      leg->SetX2NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength());
	      leg->SetY2NDC(1.0 - gStyle->GetPadTopMargin()   - gStyle->GetTickLength() - 0.05);
	      leg->Draw("SAME");
	      // add labels for decay channel, luminosity, energy and CMS preliminary (if applicable)
	      if (decayChannel=="muon") DrawDecayChLabel("#mu + Jets");
	      else if (decayChannel=="electron") DrawDecayChLabel("e + Jets");
	      else DrawDecayChLabel("e/#mu + Jets Combined");
	      // set first parameter to false once "CMS Preliminary" is not required anymore
	      DrawCMSLabels(false,luminosity); 
	      //draw data/MC ratio
	      if((histo_[plotList_[plot]].count(kSig)>0) && withRatioPlot){
		drawRatio(histo_[plotList_[plot]][kData], histo_[plotList_[plot]][kSig], 0.1, 1.9, myStyle, verbose);	       
	      }
	    }
	  }
      	} // end: plot existing?
      } // end: 1D plots
      
      //  a2) for 2D plots
      if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)){
	// new Canvas for every plot
	plotCanvas_[canvasNumber]->cd(0);
	plotCanvas_[canvasNumber]->SetRightMargin(0.15);
	plotCanvas_[canvasNumber]->SetTitle(getStringEntry(plotList_[plot],2)+getStringEntry(plotList_[plot],1)+getTStringFromInt(sample)); 
	if(verbose>1){
	  std::cout << " Plotting "    << plotList_[plot];
	  std::cout << " from sample " << sampleLabel(sample,decayChannel);
	  std::cout << " to canvas "   << canvasNumber  << " ( " << plotCanvas_[canvasNumber]->GetTitle() << " )";
	  std::cout << std::endl;
	}
	++canvasNumber;
	// draw histo
	histo2_[plotList_[plot]][sample]->Draw("colz");
	// print correlation factor
	DrawLabel(Form("Correlation: %f",histo2_[plotList_[plot]][sample]->GetCorrelationFactor()), 0.35, 0.92, 0.75, 0.99, 0.7);
      }
    }
    // for 1D hists: next canvas
    if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)) ++canvasNumber;
  }

  // b) for legends
  //
  // b1) before btagging
  //  
  plotCanvas_[canvasNumber]->cd(0);
  plotCanvas_[canvasNumber]->SetTitle("legendMonitoringBeforeBtagging");
  leg0->Draw("");
  ++canvasNumber;
  //
  // b2) after btagging
  //
  plotCanvas_[canvasNumber]->cd(0);
  plotCanvas_[canvasNumber]->SetTitle("legendMonitoringAfterBtagging");
  leg1->Draw("");
  ++canvasNumber;
	
  // ==============
  //  Saving plots
  // ==============
  if(save){
    // eps and png
    if(verbose==0) gErrorIgnoreLevel=kWarning;
    saveCanvas(plotCanvas_, outputFolder, pdfName, true, false);
    for(unsigned int idx=0; idx<plotCanvas_.size(); idx++){
      TString title=(TString)(plotCanvas_[idx])->GetTitle();
      if(!title.Contains("canv")){
	plotCanvas_[idx]->Print(outputFolder+title+".eps"); 
	plotCanvas_[idx]->Print(outputFolder+title+".png");
      }
    }
    // root file
    if(verbose>0) std::cout << "will save into outputfile named " << outputFileName << std::endl;
    for(unsigned int idx=0; idx<plotCanvas_.size(); ++idx){
      saveToRootFile(outputFileName, plotCanvas_[idx], true, verbose, "monitoring");
    }
  }
  // delete pointer
  closeStdTopAnalysisFiles(files_);
}
