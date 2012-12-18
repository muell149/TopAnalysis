#include "basicFunctionsEff.h"

void tagAndProbePlotsMC_IsoMu17_IsoMu24Comp_PUrewComp(bool save=false)
{
  gStyle->SetOptStat(0);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetPadBottomMargin(0.11);
  gStyle->SetLabelSize(0.05,"XY");
  gStyle->SetTitleSize(0.05,"XY");
  gStyle->SetFillColor(0);
  gROOT->Reset();
  
  
  /// path where input files are stored
  TString inputPathScratch  ="/scratch/hh/current/cms/user/jlange/output_4_2_4/fullLeptonic";
  TString inputPath42       ="/afs/naf.desy.de/user/j/jlange/nafscratch/top/CMSSW_4_2_4/src/TopAnalysis/Configuration/analysis/fullLeptonic";
  TString inputPath428       ="/afs/naf.desy.de/user/j/jlange/nafscratch/top/CMSSW_4_2_8_patch7/src/TopAnalysis/Configuration/analysis/fullLeptonic";
  
  TString outputFolder   = "/afs/desy.de/user/j/jlange/analysis/tagAndProbe/plots/2011/singleMu/PF2PAT/MC_IsoMu17_IsoMu24Comp_PUrewComp";
  TString outputFileName = "/MC_IsoMu17_IsoMu24Comp_PUrewComp_";

  TString fileFormatArr []= {"root", "png"};
  std::vector<TString> fileFormat(fileFormatArr, fileFormatArr + sizeof(fileFormatArr)/sizeof(TString));
  
  /// if set to 0: all plots (probe, test, eff) are drawn; to 1: only eff plots
  int onlyEffPlots =0;
  /// method ID of MC file to normalise scale factors to
  TString mIDnorm = "mF2";
  std::cout<< "Efficiency wrt. which SF is supposed to be normalized " <<  mIDnorm << std::endl;

  
   /// map with structure that keeps features of methods, like file, filename, legend etc.
  std::map<TString, method*> method_;
  
  //TString mIDarr []= {"m3", "m4", "m5","m6","m7","m8"};
  //TString mIDarr []= {"m1", "m2", "m3", "m4", "m5","m6","m7","m8","m9"};
  TString mIDarr []= {"mF1", "mF2", "mF2up", "mF2down"};
  //TString mIDarr []= {"m2", "m4","m5", "m6","m7"};
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
  

  
  fileName=inputPathScratch+"/naf_analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu17_Mu17TriJet_muPt30_PUrewEPS_cfg/analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu17_Mu17TriJet_muPt30_PUrewEPS.root";
  method_["m1"] = new method(fileName, "Summer11 IsoMu17 no PUrew", 1, 2, 1, 2, "E", "L","tree","");
  
  fileName=inputPathScratch+"/naf_analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu17_Mu17TriJet_muPt30_PUrewEPS_cfg/analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu17_Mu17TriJet_muPt30_PUrewEPS.root";
  method_["m2"] = new method(fileName, "Summer11 IsoMu17 PU rew", 2, 2, 1, 2, "E", "L","histo","");
  
//   fileName=inputPath42+"/naf_analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu17_Mu17TriJet_muPt30_PUrewEPS_cfg/analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu17_Mu17TriJet_muPt30_PUrewEPS.root";
//   method_["m4"] = new method(fileName, "Summer11 IsoMu17 new tree PUrew", 2, 3, 1, 2, "E same", "L","treeWeight");
  
  fileName=inputPathScratch+"/naf_analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu24_Mu17TriJet_muPt30_PUrewEPS_cfg/analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu24_Mu17TriJet_muPt30_PUrewEPS.root";
  method_["m3"] = new method(fileName, "Summer11 IsoMu24 no PUrew", 1, 1, 1, 1, "E", "L", "tree","(probePt>30. || testPt>30. )");
  
  fileName=inputPathScratch+"/naf_analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu24_Mu17TriJet_muPt30_PUrewEPS_cfg/analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu24_Mu17TriJet_muPt30_PUrewEPS.root";
  method_["m4"] = new method(fileName, "Summer11 IsoMu24 PUrew", 2, 1, 1, 1, "E", "L", "treeWeight","(probePt>30. || testPt>30. )");
  
  
  
  /// Fall11
  fileName=inputPath428+"/naf_analyzeZMuMuTagAndProbeMCFall11_HLT_IsoMu24_eta2p1_IsoMu17TriJet_cfg/analyzeZMuMuTagAndProbeMCFall11_HLT_IsoMu24_eta2p1_IsoMu17eta2p1TriJet.root";
  method_["mF1"] = new method(fileName, "Fall11 IsoMu24eta2p1 no PUrew", 1, 1, 1, 1, "E", "L", "treeV2","probePt>30.");
  
  fileName=inputPath428+"/naf_analyzeZMuMuTagAndProbeMCFall11_HLT_IsoMu24_eta2p1_IsoMu17TriJet_cfg/analyzeZMuMuTagAndProbeMCFall11_HLT_IsoMu24_eta2p1_IsoMu17eta2p1TriJet.root";
  method_["mF2"] = new method(fileName, "Fall11 IsoMu24eta2p1 PUrew", 2, 2, 1, 1, "E", "L", "treeV2","probePt>30.","eventWeightPUeventWeightPU");
  
  fileName=inputPath428+"/naf_analyzeZMuMuTagAndProbeMCFall11_HLT_IsoMu24_eta2p1_IsoMu17TriJet_cfg/analyzeZMuMuTagAndProbeMCFall11_HLT_IsoMu24_eta2p1_IsoMu17eta2p1TriJet.root";
  method_["mF3"] = new method(fileName, "Fall11 IsoMu24eta2p1 PUrew EPS", 3, 8, 1, 1, "E", "L", "treeV2","probePt>30.","eventWeightPUEPSeventWeightPUEPS");
  
  fileName=inputPath428+"/naf_analyzeZMuMuTagAndProbeMCFall11_HLT_IsoMu24_eta2p1_IsoMu17TriJet_cfg/analyzeZMuMuTagAndProbeMCFall11_HLT_IsoMu24_eta2p1_IsoMu17eta2p1TriJet.root";
  method_["mF2up"] = new method(fileName, "Fall11 IsoMu24eta2p1 PUrew UP", 2, 4, 1, 1, "E", "L", "treeV2","probePt>30.","eventWeightPUsysUpeventWeightPUUp");
  
  fileName=inputPath428+"/naf_analyzeZMuMuTagAndProbeMCFall11_HLT_IsoMu24_eta2p1_IsoMu17TriJet_cfg/analyzeZMuMuTagAndProbeMCFall11_HLT_IsoMu24_eta2p1_IsoMu17eta2p1TriJet.root";
  method_["mF2down"] = new method(fileName, "Fall11 IsoMu24eta2p1 PUrew DOWN", 2, 7, 1, 1, "E", "L", "treeV2","probePt>30.","eventWeightPUsysDowneventWeightPUDown");
  
//   fileName=inputPathScratch+"/naf_analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu24_Mu17TriJet_muPt30_PUrewEPS_cfg/analyzeZMuMuTagAndProbeMCSummer11_HLT_IsoMu24_Mu17TriJet_muPt30_PUrewEPS.root";
//   method_["m4"] = new method(fileName, "Summer11 IsoMu24 PUrew histo", 2, 3, 1, 1, "E same", "L", "histo");
  //   
//   fileName=inputPath42+"/naf_analyzeZMuMuTagAndProbeRun2011AV4PromptReco_HLT_IsoMu17_cfg/analyzeZMuMuTagAndProbeRun2011AV1+4_HLT_IsoMu17.root";
//   method_["m5"] = new method(fileName, "1.1 fb^{-1} IsoMu17", 1, 2, 20, 2, "E X0 P same", "P", "histo");
  
  
  /// different tap studies (different efficiencies)
//    const int folderNum=5;
//    TString folderID[]={"tapTrkQ", "tapIso", "tapMinDR", "tapTotalSelection", "tapTrigger"};
//    TString foldersTitle[]={"ID", "Isolation", "#DeltaR (after Iso Cut)","Overall Selection", "Trigger"};
  
  const int folderNum=1;
  TString folderID[]={"tapTrigger"};
  TString foldersTitle[]={"Trigger"};


  /// effName = name of the effHisto; variables: corresponding variable to effName; cuts: corresponding cut to effName

//   TString effIDarr[]      = {"Control", "Pt", "Eta", "RelIso", "PVMult", "Mult", "MinDR","lepLepMass"};
  //TString effIDarr[]      = {"Control", "Pt", "Eta", "RelIso", "PVMult", "Mult", "PtEta0to1p5", "PtEta1p5to2p1"};
  TString effIDarr[]      = {"Pt", "Eta", "RelIso", "PVMult", "Mult", "MinDR"};
  //TString effIDarr[]      = {"Pt"};
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
  double yLo = 0.4, yHi = 1.;
  double yLoSF = 0.8, yHiSF = 1.2;
  
  /// Constructor for struct eff(TString iniVar, T  iniCuts, TString iniBins, TString iniTitles, double iniYLo=-9999., double iniYHi=-9999., double iniXLo=-9999., double iniXHi=-9999.)
  TCut cutPt  = "" ;//"probePt>30."; /*"(probePt>30. || testPt>30. )";*/
  TCut cutEta = "" ;//"TMath::Abs(probeEta)<2.1"; /*"(TMath::Abs(probeEta)<2.1 || TMath::Abs(testEta)<2.1)";*/
  TCut cutPtEta = cutPt && cutEta;
  for(int iFolder=0; iFolder < folderNum; iFolder++){
    title = foldersTitle[iFolder]+" Efficiency/ / ";
    eff_["Control"][folderID[iFolder]]        =new eff("Control", cutPtEta, mBinsControl, binsControl_, title, yLo, yHi, -9999.,-9999.,true);
    title = foldersTitle[iFolder]+" Efficiency/p_{T} [GeV]/ ";
    eff_["Pt"][folderID[iFolder]]             =new eff("Pt", cutEta, mBinsPt, binsPt_, title, yLo, yHi, 30.,200.);
    title = foldersTitle[iFolder]+" Efficiency/#eta/ ";
    eff_["Eta"][folderID[iFolder]]             =new eff("Eta", cutPt, mBinsEta, binsEta_, title, yLo, yHi);
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
    
//     title = foldersTitle[iFolder]+" Efficiency/p_{T} [GeV]/ ";
//     eff_["PtEta0to1p5"][folderID[iFolder]]             =new eff("Pt", "TMath::Abs(probeEta)<1.5", mBinsPt, binsPt_, title, yLo, yHi, 30.,150.,true);
//     
//     title = foldersTitle[iFolder]+" Efficiency/p_{T} [GeV]/ ";
//     eff_["PtEta1p5to2p1"][folderID[iFolder]]             =new eff("Pt", "TMath::Abs(probeEta)>1.5 && TMath::Abs(probeEta)<2.1", mBinsPt, binsPt_, title, yLo, yHi, 30.,150.,true);
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
      std::cout<< "Drawing eff."<<std::endl;
      drawEfficiencies(eff_[effID[iEff]][folderID[iFolder]], method_, mID, 0.15,0.15,0.9,0.45,eff_[effID[iEff]][folderID[iFolder]]->drawLegend);
      CanvSFComp[iFolder]->cd(iEff+1);
      std::cout<< "Drawing SF"<<std::endl;
      //drawSF          (eff_[effID[iEff]][folderID[iFolder]], method_, mID, mIDnorm, 0.15,0.15,0.9,0.45,eff_[effID[iEff]][folderID[iFolder]]->drawLegend, yLoSF, yHiSF, eff_[effID[iEff]][folderID[iFolder]]->xLo, eff_[effID[iEff]][folderID[iFolder]]->xHi);
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
  std::cout<< "Done"<<std::endl;
}
