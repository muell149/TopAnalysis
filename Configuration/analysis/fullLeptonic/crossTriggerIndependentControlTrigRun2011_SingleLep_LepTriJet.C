#include "basicFunctionsEff.h"

void crossTriggerIndependentControlTrigRun2011_SingleLep_LepTriJet(bool save=false)
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
  
  TString outputFolder   = "/afs/desy.de/user/j/jlange/analysis/tagAndProbe/plots/2011/EleHad/IsoEle27-32_Ele25TriJet";
  TString outputFileName = "/IsoEle27-32_Ele25TriJet_Combined_";

  TString fileFormatArr []= {"root", "png"};
  std::vector<TString> fileFormat(fileFormatArr, fileFormatArr + sizeof(fileFormatArr)/sizeof(TString));
  
  /// if set to 0: all plots (probe, test, eff) are drawn; to 1: only eff plots
  int onlyEffPlots =0;
  /// method ID of MC file to normalise scale factors to
  TString mIDnorm = "m1tt";
  std::cout<< "Efficiency wrt. which SF is supposed to be normalized " <<  mIDnorm << std::endl;

  
   /// map with structure that keeps features of methods, like file, filename, legend etc.
  std::map<TString, method*> method_;
  
//   TString mIDarr []= {"m1", "m2", "m3", "m4", "m5"};
//   TString mIDarr []= {"m1tt", "m1W", "m2", "m3", "m11", "m12"};
  TString mIDarr []= {"m1tt", "m4"};
  //TString mIDarr []= {"m1", "m5", "m10", "m11"};
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
  
  /// to produce plots up to EPS:
  /// Electrons:
  
  fileName=inputPath42+"/naf_analyzeCrossTriggerRatiosMCSummer11ttbar_IsoEle27_Ele25TriJet_cfg_TreeV2/analyzeCrossTriggerRatiosMCSummer11ttbar_IsoEle27_Ele25TriJet_TreeV2.root";
  method_["m1tt"] = new method(fileName, "MC t#bar{t}", 1, 1, 1, 1, "E same", "LP","treeV2","","");
  //weight
  //Summer11 tt IsoEle27_Ele25TriJet
  
  fileName=inputPath42+"/naf_analyzeCrossTriggerRatiosMCSummer11WJets_IsoEle27_Ele25TriJet_cfg_TreeV2/analyzeCrossTriggerRatiosMCSummer11WJets_IsoEle27_Ele25TriJet_TreeV2.root";
  method_["m1W"] = new method(fileName, "Summer11 W IsoEle27_Ele25TriJet", 1, 8, 1, 1, "E same", "LP","treeV2","","weight");
  
  fileName=inputPath42+"/naf_analyzeCrossTriggerRatiosMCSummer11ZJets_IsoEle27_Ele25TriJet_cfg_TreeV2/analyzeCrossTriggerRatiosMCSummer11ZJets_IsoEle27_Ele25TriJet_TreeV2.root";
  method_["m1Z"] = new method(fileName, "Summer11 Z IsoEle27_Ele25TriJet", 1, 4, 1, 1, "E same", "LP","treeV2","","weight");
  
  fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet.root";
  method_["m1TaP"] = new method(fileName, "Summer11 Z IsoEle27_Ele25TriJet", 1, 2, 1, 2, "E same", "LP","treeV2","","weight");
  
  fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle32_IsoEle25TriJet.root";
  method_["m1TaP2"] = new method(fileName, "Summer11 IsoEle32_IsoEle25TriJet", 2, 4, 1, 4, "E same", "LP","treeV2","","weight");
  
  /// data
  fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_160404_163869_HLT_IsoEle27_Ele25TriJet_cfg/analyzeZEleEleTagAndProbeRun2011A_160404_163869_HLT_IsoEle27_IsoEle25TriJet.root";
  method_["m2"] = new method(fileName, "Run May10 IsoEle27_Ele25TriJet", 2, 2, 21, 2, "E same", "LP","treeV2","","");
  
  fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_IsoEle25TriJet.root";
  method_["m3"] = new method(fileName, "Run PromptV4 IsoEle32_IsoEle25TriJet", 2, 4, 25, 4, "E same", "LP","treeV2","","");
  
  fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeRun2011A_165088_167913_HLT_IsoEle32_Ele25TriJet2_cfg/analyzeZEleEleTagAndProbeRun2011A_160404_167913_HLT_IsoEle27-32_IsoEle25TriJet.root";
  method_["m4"] = new method(fileName, "Daten", 2, 1, 21, 1, "E same", "LP","treeV2","","");
  //Run May10+PromptV4 IsoEle27(32)_IsoEle25TriJet
  
  /// Muons: 
  fileName=inputPathScratch+"/naf_analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu17_Mu17TriJet_muPt30_PUrewEPS_cfg/analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu17_Mu17TriJet_muPt30_PUrewEPS.root";
  method_["m10"] = new method(fileName, "Summer11 IsoMu17_Mu17TriJet", 1, 1, 1, 1, "E same", "LP","treeV2","","weight");
  
  fileName=inputPathScratch+"/naf_analyzeZMuMuTagAndProbeRun2011A_5e32_160404_163869_HLT_IsoMu17_IsoMu17TriJet_muPt30_cfg/analyzeZMuMuTagAndProbeRun2011A_5e32_160404_163869_HLT_IsoMu17_IsoMu17TriJet_muPt30.root";
  method_["m11"] = new method(fileName, "IsoMu17_Mu17TriJet 5e32", 1, 1, 20, 1, "E0", "LP","treeV2");
  
  fileName=inputPathScratch+"/naf_analyzeZMuMuTagAndProbeRun2011A_1e33_165088_167913_HLT_IsoMu17_IsoMu17TriJet_muPt30_cfg/analyzeZMuMuTagAndProbeRun2011A_1e33_165088_167913_HLT_IsoMu17_IsoMu17TriJet_muPt30.root";
  method_["m12"] = new method(fileName, "IsoMu17_Mu17TriJet 1e33", 1, 2, 22, 2, "E0 same", "LP","treeV2");
   
//   fileName=inputPathScratch+"/naf_analyzeZMuMuTagAndProbeRun2011A_2e33_170826_173198_HLT_IsoMu24_IsoMu17TriJet_muPt30_cfg/analyzeZMuMuTagAndProbeRun2011A_2e33_170826_173198_HLT_IsoMu24_IsoMu17TriJet_muPt30.root";
//   method_["m3"] = new method(fileName, "IsoMu24 2e33", 1, 4, 22, 4, "E0 same", "P","treeV2");
//    
//   fileName=inputPathScratch+"/naf_analyzeZMuMuTagAndProbeRun2011A_3e33_173212_175770_HLT_IsoMu24Eta_IsoMu17EtaTriJet_muPt30_cfg/analyzeZMuMuTagAndProbeRun2011A_3e33_173212_175770_HLT_IsoMu24Eta_IsoMu17EtaTriJet_muPt30.root";
//   method_["m4"] = new method(fileName, "IsoMu24 3e33", 1, 8, 23, 8, "E0 same", "P","treeV2");
  
  /// To compare different run ranges also beyond EPS:
//   fileName=inputPath42+"/naf_analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet_cfg/analyzeZEleEleTagAndProbeMCSummer11_HLT_IsoEle27_IsoEle25TriJet.root";
//   method_["m1"] = new method(fileName, "Summer11 IsoEle27", 1, 2, 1, 2, "E same", "LP","treeV2","","PUweightEPSeventWeightPU");
//    //PUweightEPSeventWeightPU

  
  /// different tap studies (different efficiencies)

  
  const int folderNum=1;
  TString folderID[]={""};
  TString foldersTitle[]={"Jet Leg Trigger"};
  /// for reference trigger method:
  TString folderIDrefTriggerPass="analyzeJetAllTrig2AfterCut";
  TString folderIDrefTriggerAll="analyzeJetAllTrig1AfterCut";
  
//   TString folderIDrefTriggerPass="analyzeJetDiffMultTrig2AfterCut";
//   TString folderIDrefTriggerAll="analyzeJetDiffMultTrig1AfterCut";


  /// effName = name of the effHisto; variables: corresponding variable to effName; cuts: corresponding cut to effName

//   TString effIDarr[]      = {"Control", "Pt", "Eta", "RelIso", "PVMult", "Mult", "MinDR","lepLepMass"};
   //TString effIDarr[]      = {"Control", "Pt", "Eta", "RelIso", "PVMult", "Mult", "PtEta0to1p5", "PtEta1p5to2p1"};
  //TString effIDarr[]      = {"Pt", "Eta", "RelIso", "PVMult", "Mult", "MinDR"};
   TString effIDarr[]      = {"pt3-3jets", "pt4-4jets", "pt4-geq4jets", "pt5-5jets", "eta3-3jets", "eta4-4jets", "eta4-geq4jets", "eta5-5jets"};
//   TString effIDarr[]      = {"pt3-3jets", "pt4-4jets", "pt4-geq4jets", "pt5-5jets", "pv-3jets", "pv-4jets", "pv-geq4jets", "pv-5jets"};
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
  double yLo = 0.9, yHi = 1.;
  double yLoSF = 0.9, yHiSF = 1.1;
  
  /// Constructor for struct eff(TString iniVar, T  iniCuts, TString iniBins, TString iniTitles, double iniYLo=-9999., double iniYHi=-9999., double iniXLo=-9999., double iniXHi=-9999.)
  TCut cutPt  =""; /*"(probePt>30. || testPt>30. )";*/
  TCut cutEta =""; /*"(TMath::Abs(probeEta)<2.1 || TMath::Abs(testEta)<2.1)";*/
  TCut cutPtEta = cutPt && cutEta;
  for(int iFolder=0; iFolder < folderNum; iFolder++){
    title = foldersTitle[iFolder]+" Efficiency/ / ";
    eff_["Control"][folderID[iFolder]]        =new eff("Control", cutPtEta, mBinsControl, binsControl_, title, yLo, yHi, -9999.,-9999.,true);
//     title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=3/3rd Jet p_{T} [GeV]/ ";
//     eff_["pt3-3jets"][folderID[iFolder]]             =new eff("pt3", "n==3", mBinsJetPt, binsJetPt_, title, yLo, yHi, 30.,150.,true);
//     title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=4/3rd Jet p_{T} [GeV]/ ";
//     eff_["pt3-4jets"][folderID[iFolder]]             =new eff("pt3", "n==4", mBinsJetPt, binsJetPt_, title, yLo, yHi, 30.,150.,true);
//     title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=4/4th Jet p_{T} [GeV]/ ";
//     eff_["pt4-4jets"][folderID[iFolder]]             =new eff("pt4", "n==4", mBinsJetPt, binsJetPt_, title, yLo, yHi, 30.,150.,true);
//     title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=5/3rd Jet p_{T} [GeV]/ ";
//     eff_["pt3-5jets"][folderID[iFolder]]             =new eff("pt3", "n==5", mBinsJetPt, binsJetPt_, title, yLo, yHi, 30.,150.,true);
//     title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=5/4th Jet p_{T} [GeV]/ ";
//     eff_["pt4-5jets"][folderID[iFolder]]             =new eff("pt4", "n==5", mBinsJetPt, binsJetPt_, title, yLo, yHi, 30.,150.,true);
//     title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=5/5th Jet p_{T} [GeV]/ ";
//     eff_["pt5-5jets"][folderID[iFolder]]             =new eff("pt5", "n==5", mBinsJetPt, binsJetPt_, title, yLo, yHi, 30.,150.,true);
    
    
    title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=3/3rd Jet p_{T} [GeV]/ ";
    eff_["pt3-3jets"][folderID[iFolder]]             =new eff("pt3", "n==3", mBinsJetPt, binsJetPt_, title, yLo, yHi, 30.,150.,true);
    title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=4/4th Jet p_{T} [GeV]/ ";
    eff_["pt4-4jets"][folderID[iFolder]]             =new eff("pt4", "n==4", mBinsJetPt, binsJetPt_, title, yLo, yHi, 30.,150.);
    title = foldersTitle[iFolder]+" Efficiency, N_{Jet}>=4/4th Jet p_{T} [GeV]/ ";
    eff_["pt4-geq4jets"][folderID[iFolder]]             =new eff("pt4", "n>=4", mBinsJetPt, binsJetPt_, title, yLo, yHi, 30.,150.);
    title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=5/5th Jet p_{T} [GeV]/ ";
    eff_["pt5-5jets"][folderID[iFolder]]             =new eff("pt5", "n==5", mBinsJetPt, binsJetPt_, title, yLo, yHi, 30.,150.);
    
    title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=3/3rd Jet eta [GeV]/ ";
    eff_["eta3-3jets"][folderID[iFolder]]             =new eff("eta3", "n==3", mBinsJetEta, binsJetEta_, title, yLo, yHi, 30.,150.);
    title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=4/4th Jet eta [GeV]/ ";
    eff_["eta4-4jets"][folderID[iFolder]]             =new eff("eta4", "n==4", mBinsJetEta, binsJetEta_, title, yLo, yHi, 30.,150.);
    title = foldersTitle[iFolder]+" Efficiency, N_{Jet}>=4/4th Jet eta [GeV]/ ";
    eff_["eta4-geq4jets"][folderID[iFolder]]             =new eff("eta4", "n>=4", mBinsJetEta, binsJetEta_, title, yLo, yHi, 30.,150.);
    title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=5/5th Jet eta [GeV]/ ";
    eff_["eta5-5jets"][folderID[iFolder]]             =new eff("eta5", "n==5", mBinsJetEta, binsJetEta_, title, yLo, yHi, 30.,150.);
    
    title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=3 /pv / ";
    eff_["pv-3jets"][folderID[iFolder]]             =new eff("pv", "n==3", mBinsPVMult, binsPVMult_, title, yLo, yHi, 30.,150.);
    title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=4/ pv / ";
    eff_["pv-4jets"][folderID[iFolder]]             =new eff("pv", "n==4", mBinsPVMult, binsPVMult_, title, yLo, yHi, 30.,150.);
    title = foldersTitle[iFolder]+" Efficiency, N_{Jet}>=4/ pv / ";
    eff_["pv-geq4jets"][folderID[iFolder]]             =new eff("pv", "n>=4", mBinsPVMult, binsPVMult_, title, yLo, yHi, 30.,150.);
    title = foldersTitle[iFolder]+" Efficiency, N_{Jet}=5/ pv / ";
    eff_["pv-5jets"][folderID[iFolder]]             =new eff("pv", "n==5", mBinsPVMult, binsPVMult_, title, yLo, yHi, 30.,150.);
  }

  /// ---
  /// get efficiencies from tree or histo
  ///  ---
  for(int iMethod=0; iMethod<mIDNum; iMethod++){
    for(int iEff=0; iEff<effIDNum; iEff++){
      for(int iFolder=0; iFolder<folderNum; iFolder++){
	getEfficiencies(eff_[effID[iEff]][folderID[iFolder]], method_[mID[iMethod]], mID[iMethod], folderIDrefTriggerPass, folderIDrefTriggerAll);
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
