#include "basicFunctionsEff.h"

void tagAndProbePlotsRun2012_MCdataCom_IsoMu24eta2p1(bool save=false, bool saveRoot=false)
{
  /// decide whether to do 1D or 2D plots or both
  bool do1D = true;
  bool do2D = true;
  
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
  
//   gStyle->SetLineScalePS(1);
  
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
  
  // for 2D histo text
  gStyle->SetPaintTextFormat("3.3f");
  gStyle->SetPalette(1);
  
  /// path where input files are stored
  TString inputPathScratch  ="/afs/naf.desy.de/group/cms/scratch/tophh/efficiencies";
  TString inputPath535      ="/afs/naf.desy.de/user/j/jlange/nafscratch/top/CMSSW_5_3_5/src/TopAnalysis/Configuration/analysis/fullLeptonic";
  TString inputPathDust     ="/scratch/hh/dust/naf/cms/user/jlange/output_5_3";
  
  TString outputFolder   = "/afs/desy.de/user/j/jlange/analysis/tagAndProbe/plots/2012/singleMu";
//  TString outputFolder   = "/afs/desy.de/user/j/jlange/analysis/tagAndProbe/plots/2011/singleMu/Fall11/DataMCcomp_IsoMu17-24_relIsoL0p2";
  
   TString outputFileName = "/DataMCcomp_IsoMu24eta2p1_";
//  TString outputFileName = "/DataMCcomp_IsoMu17-24_relIsoL0p2_";

  TString fileFormatArr []= {"root", "png", "eps"};
  std::vector<TString> fileFormat(fileFormatArr, fileFormatArr + sizeof(fileFormatArr)/sizeof(TString));
  
  /// if set to 0: all plots (probe, test, eff) are drawn; to 1: only eff plots
  int onlyEffPlots =1;
  /// method ID of MC file to normalise scale factors to
  TString mIDnorm = "m1";
  std::cout<< "Efficiency wrt. which SF is supposed to be normalized " <<  mIDnorm << std::endl;

  
   /// map with structure that keeps features of methods, like file, filename, legend etc.
  std::map<TString, method*> method_;

  /// standard for nice plots:
  TString mIDarr []= {"m1","m2"};
  /// for different PU scenarios: (also savable in root file)
//   TString mIDarr []= {"m1", "m1PUup", "m1PUdown", "m2", "m2PUup", "m2PUdown"};

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
  
  /// Define pt and eta cuts for TH2 
  /// TCut does not work for TH2
  double cutPt2D  = 30.;
  double cutEta2D = 2.1;
  
  /// Constructor for struct method(TString iniFileName, TString iniLegName, int iniLineStyle, int iniLineColor, int iniMarkerStyle, int iniMarkerColor, TString iniDrawOpt, TString iniLepOpt, TString source)
  
   /// Summer12 MC
  fileName=inputPathScratch+"/analyzeZMuMuTagAndProbeMCSummer12_HLT_IsoMu24_eta2p1.root";
  method_["m1"] = new method(fileName, "Simulation IsoMu24eta2p1", 1, 2, 1, 1, "E", "L", "treeV2","probePt>30. && TMath::Abs(probeEta)<2.1","eventWeightPUeventWeightPU");
  
  method_["m1PUup"] = new method(fileName, "Simulation IsoMu24eta2p1 PUrew UP", 1, 2, 1, 1, "E", "L", "treeV2","probePt>30. && TMath::Abs(probeEta)<2.1","eventWeightPUsysUpeventWeightPUUp","m1PUup");
  
  method_["m1PUdown"] = new method(fileName, "Simulation IsoMu24eta2p1 PUrew DOWN", 1, 2, 1, 1, "E", "L", "treeV2","probePt>30. && TMath::Abs(probeEta)<2.1","eventWeightPUsysDowneventWeightPUDown","m1PUdown");
  
  /// data
  fileName=inputPathScratch+"/analyzeZMuMuTagAndProbeRun2012ABC_HLT_IsoMu24eta2p1.root";
  method_["m2"] = new method(fileName, "Data IsoMu24eta2p1", 1, 1, 21, 1, "E", "L", "treeV2","probePt>30. && TMath::Abs(probeEta)<2.1");
  
  method_["m2PUup"] = new method(fileName, "Data IsoMu24eta2p1 PU up", 1, 1, 24, 1, "E", "LP", "treeV2","probePt>30. && TMath::Abs(probeEta)<2.1","","m1PUup");
  
  method_["m2PUdown"] = new method(fileName, "Data IsoMu24eta2p1 PU down", 1, 1, 26, 1, "E", "LP", "treeV2","probePt>30. && TMath::Abs(probeEta)<2.1","","m1PUdown");
  

  
  /// different tap studies (different efficiencies)
//    const int folderNum=4;
//    TString folderID[]={"tapTrkQ", "tapIso", "tapTotalSelection", "tapTrigger"};
//    TString foldersTitle[]={"Muon ID", "Muon Isolation", "Muon Selection", "Muon Trigger"};
  
//   const int folderNum=3;
//   TString folderID[]={"tapTotalSelection", "tapTrigger", "tapAll"};
//   TString foldersTitle[]={"Muon Selection", "Muon Trigger", "Combined Muon Selection and Trigger"};
  
 /// to combine selection and trigger efficiencies use tapAll:
  const int folderNum=1;
  TString folderID[]={"tapAll"};
  TString foldersTitle[]={"Combined Selection and Trigger"};
  
//   const int folderNum=1;
//   TString folderID[]={"tapTrigger"};
//   TString foldersTitle[]={"Muon Trigger"};
  
//   const int folderNum=2;
//   TString folderID[]={"tapTotalSelection", "tapTrigger"};
//   TString foldersTitle[]={"Muon Selection", "Muon Trigger"};
  
//     const int folderNum=1;
//     TString folderID[]={"tapIso"};
//     TString foldersTitle[]={"Isolation"};


  /// effName = name of the effHisto; variables: corresponding variable to effName; cuts: corresponding cut to effName

//     TString effIDarr[]      = {"Control", "Pt", "Eta", "RelIso", "PVMult", "Mult", "MinDR","Pt_inclLegend"};
  TString effIDarr[]      = {"Control", "Pt", "Eta", "PVMult", "Mult", "MinDR", "EtaPt30to45", "EtaPtGreater45"};
//  TString effIDarr[]      = {"Control", "Pt", "Eta", "EtaPt30to45", "EtaPtGreater45"};
   //TString effIDarr[]      = {"Pt_inclLegend"};
   //TString effIDarr[]      = {"Control", "Pt", "Eta", "RelIso", "PVMult", "Mult", "MinDR","lepLepMass"};
  //TString effIDarr[]      = {"Control", "Pt", "Eta", "RelIso", "PVMult", "Mult", "PtEta0to1p5", "PtEta1p5to2p1"};
  //TString effIDarr[]      = {"Pt", "Eta", "RelIso", "PVMult", "Mult", "MinDR"};
//   TString effIDarr[]      = {"Pt"};
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
  std::map<TString, eff2D*> eff2DPtEta_;
  
  /// title for histo, x and y axis (separated by "/")
  TString title0 ="";
  TString title ="";
  
  /// axis range
  //double yLo = 0.5, yHi = 1.1;
  double yLo = 0.45, yHi = 1.;
  double yLoSF = 0.9, yHiSF = 1.1-0.0001;
  
  /// Constructor for struct eff(TString iniVar, T  iniCuts, TString iniBins, TString iniTitles, double iniYLo=-9999., double iniYHi=-9999., double iniXLo=-9999., double iniXHi=-9999.)
  TCut cutPt  = "probePt>30."; // && probeRelIso<0.2 "; /*"(probePt>30. || testPt>30. )";*/
  TCut cutEta = "TMath::Abs(probeEta)<2.1"; // && probeRelIso<0.2 "; /*"(TMath::Abs(probeEta)<2.1 || TMath::Abs(testEta)<2.1)";*/
  TCut cutPtEta = cutPt && cutEta;
  for(int iFolder=0; iFolder < folderNum; iFolder++){
    title = foldersTitle[iFolder]+" Efficiency/ / ";
    eff_["Control"][folderID[iFolder]]        =new eff("Control", cutPtEta, mBinsControl, binsControl_, title, yLo, yHi, -9999.,-9999.);
    title = foldersTitle[iFolder]+" Efficiency/p_{T} [GeV]/ ";
    eff_["Pt"][folderID[iFolder]]             =new eff("Pt", cutEta, mBinsPt, binsPtAN_, title, yLo, yHi, 30.,200.);
    title = foldersTitle[iFolder]+" Efficiency/p_{T} [GeV]/ ";
    eff_["Pt_inclLegend"][folderID[iFolder]]             =new eff("Pt", cutEta, mBinsPt, binsPtAN_, title, yLo, yHi, 30.,200.,true);
    title = foldersTitle[iFolder]+" Efficiency/#eta/ ";
    eff_["Eta"][folderID[iFolder]]             =new eff("Eta", cutPt, mBinsEta, binsEta_, title, yLo, yHi,-2.1,2.1);
    title = foldersTitle[iFolder]+" Efficiency/relIso/ ";
    eff_["RelIso"][folderID[iFolder]]          =new eff("RelIso", cutPtEta, mBinsRelIso, binsRelIso_, title, yLo, yHi);
    title = foldersTitle[iFolder]+" Efficiency/absIso/ ";
    eff_["AbsIso"][folderID[iFolder]]          =new eff("AbsIso", cutPtEta, mBinsAbsIso, binsAbsIso_, title, yLo, yHi);
    title = foldersTitle[iFolder]+" Efficiency/N_{PV}/ ";
    eff_["PVMult"][folderID[iFolder]]          =new eff("PVMult", cutPtEta, mBinsPVMult, binsPVMult_, title, yLo, yHi,0.,40.);
    title = foldersTitle[iFolder]+" Efficiency/N_{jet}/ ";
    eff_["Mult"][folderID[iFolder]]            =new eff("Mult", cutPtEta, mBinsMult, binsMult_, title, yLo, yHi);
    title = foldersTitle[iFolder]+" Efficiency/Minimum #DeltaR(#mu,jet)/ ";
    eff_["MinDR"][folderID[iFolder]]            =new eff("MinDR", cutPtEta&& "probeRelIso<0.2", mBinsMinDR, binsMinDR_, title, yLo, yHi, 0., 5.);
    title = foldersTitle[iFolder]+" Efficiency/Minimum M_{lep,lep}/ ";
    eff_["lepLepMass"][folderID[iFolder]]            =new eff("lepLepMass", cutPtEta, mBinsLepLepMass, binsLepLepMass_, title, yLo, yHi);
    
    title = foldersTitle[iFolder]+" Efficiency, 0<#eta<1.2/p_{T} [GeV]/ ";
    eff_["PtEta0to1p2"][folderID[iFolder]]             =new eff("Pt", "TMath::Abs(probeEta)<1.2", mBinsPt, binsPt_, title, yLo, yHi, 30.,200.);
    
    title = foldersTitle[iFolder]+" Efficiency 1.2<#eta<2.1/p_{T} [GeV]/ ";
    eff_["PtEta1p2to2p1"][folderID[iFolder]]             =new eff("Pt", "TMath::Abs(probeEta)>1.2 && TMath::Abs(probeEta)<2.1", mBinsPt, binsPt_, title, yLo, yHi, 30.,200.,true);
    
    title = foldersTitle[iFolder]+" Efficiency, 30<p_{T}<45/#eta/ ";
    eff_["EtaPt30to45"][folderID[iFolder]]             =new eff("Eta", "probePt>30. && probePt<45.", mBinsEta, binsEta_, title, yLo, yHi);
    
    title = foldersTitle[iFolder]+" Efficiency, 40<p_{T}<50/#eta/ ";
    eff_["EtaPt40to50"][folderID[iFolder]]             =new eff("Eta", "probePt>40. && probePt<50.", mBinsEta, binsEta_, title, yLo, yHi);
    
    title = foldersTitle[iFolder]+" Efficiency, 45<p_{T}/#eta/ ";
    eff_["EtaPtGreater45"][folderID[iFolder]]             =new eff("Eta", "probePt>45.", mBinsEta, binsEta_, title, yLo, yHi);
    
    title = foldersTitle[iFolder]+" Efficiency AN/p_{T} [GeV]/ ";
    eff_["PtAN"][folderID[iFolder]]             =new eff("Pt", cutEta, mBinsPt, binsPtAN_, title, yLo, yHi, 30.,200.);
    
    title = foldersTitle[iFolder]+" Efficiency Median/p_{T} [GeV]/ ";
    eff_["PtMedian"][folderID[iFolder]]             =new eff("Pt", cutEta, mBinsPt, binsPtMedian_, title, yLo, yHi, 30.,200.);
    
    title = foldersTitle[iFolder]+" Efficiency 3 bins/p_{T} [GeV]/ ";
    eff_["Pt3bins"][folderID[iFolder]]             =new eff("Pt", cutEta, mBinsPt, binsPt3bins_, title, yLo, yHi, 30.,200.);
    
    /// 2D pt:eta
    title = foldersTitle[iFolder]+" Efficiency/p_{T} [GeV]/#eta/ ";
    eff2DPtEta_[folderID[iFolder]]             =new eff2D("Pt", "Eta", cutPtEta, mBinsPtMu2D, binsPtMu2D_, mBinsEtaMu2D, binsEtaMu2D_, title, yLo, yHi, 30.+0.001,200.-0.001, -2.1+0.001, 2.1-0.001);
  }

  /// ---
  /// get efficiencies from tree or histo
  ///  ---
  for(int iMethod=0; iMethod<mIDNum; iMethod++){
    /// 1D
    if(do1D){
      for(int iEff=0; iEff<effIDNum; iEff++){
	for(int iFolder=0; iFolder<folderNum; iFolder++){
	  getEfficiencies(eff_[effID[iEff]][folderID[iFolder]], method_[mID[iMethod]], mID[iMethod], folderID[iFolder], folderID[iFolder]);
	}
      }
      for(int iEff=0; iEff<effIDNum2; iEff++){
	for(int iFolder=0; iFolder<folderNum; iFolder++){
	  getEfficiencies(eff_[effID2[iEff]][folderID[iFolder]], method_[mID[iMethod]], mID[iMethod], folderID[iFolder], folderID[iFolder]);
	}
      }
    }
    /// 2D
    if(do2D){
      for(int iFolder=0; iFolder<folderNum; iFolder++){
	getEfficiencies2D(eff2DPtEta_[folderID[iFolder]], method_[mID[iMethod]], mID[iMethod], folderID[iFolder], folderID[iFolder], cutPt2D, cutEta2D);
      }
    }
  }

 /// Draw one Canvas for each folder comparing different methods.
 /// Each canvas shows test (1st row) and probe collection (2nd) and efficiency (3rd) for different variables (columns)
  TCanvas* CanvComp [folderNum];
  TCanvas* CanvSFComp [folderNum];
  TCanvas* CanvEffAndSFComp [folderNum];
  TCanvas* CanvEvtsComp [folderNum];
  TCanvas* CanvEvtsNormComp [folderNum];
  TCanvas* CanvLeg = new TCanvas("CanvLeg", "CanvLeg", 350,200);
  
  TCanvas* CanvComp2 [folderNum];
  TCanvas* CanvSFComp2 [folderNum];
  
  TCanvas* CanvComp2DPtEta [folderNum];
  TCanvas* CanvComp2DPtEtaSF [folderNum];
  TCanvas* CanvComp2DPtEtaSFerr [folderNum];
  TCanvas* CanvComp2DPtEtaPass [folderNum];
  TCanvas* CanvComp2DPtEtaAll [folderNum];

  std::cout<< "Drawing eff. and SF"<<std::endl;
  for(int iFolder=0; iFolder<folderNum; iFolder++) {

    CanvComp[iFolder] = new TCanvas("Comparison"+folderID[iFolder], "Comparison"+folderID[iFolder], 1700,1000);
    CanvSFComp[iFolder] = new TCanvas("ComparisonSF"+folderID[iFolder], "ComparisonSF"+folderID[iFolder], 1700,1000);
    CanvEffAndSFComp[iFolder] = new TCanvas("ComparisonEffAndSF"+folderID[iFolder], "ComparisonEffAndSF"+folderID[iFolder], 1700,1000);
    CanvEvtsComp[iFolder] = new TCanvas("ComparisonEvts"+folderID[iFolder], "ComparisonEvts"+folderID[iFolder], 1700,1000);
    CanvEvtsNormComp[iFolder] = new TCanvas("ComparisonEvtsNorm"+folderID[iFolder], "ComparisonEvtsNorm"+folderID[iFolder], 1700,1000);
    
    CanvComp2[iFolder] = new TCanvas("Comparison2"+folderID[iFolder], "Comparison2"+folderID[iFolder], 1700,1000);
    CanvSFComp2[iFolder] = new TCanvas("ComparisonSF2"+folderID[iFolder], "ComparisonSF2"+folderID[iFolder], 1700,1000);
    
    CanvComp[iFolder]->Divide(4,2);
    CanvSFComp[iFolder]->Divide(4,2);
    CanvEffAndSFComp[iFolder]->Divide(4,2);
    CanvEvtsComp[iFolder]->Divide(4,2);
    CanvEvtsNormComp[iFolder]->Divide(4,2);
    
    CanvComp2[iFolder]->Divide(4,2);
    CanvSFComp2[iFolder]->Divide(4,2);
    
    /// 1D
    if(do1D){
      for(int iEff=0; iEff<effIDNum; iEff++){
	CanvComp[iFolder]->cd(iEff+1);
// 	std::cout<< "Drawing eff."<<std::endl;
// 	drawEfficiencies(eff_[effID[iEff]][folderID[iFolder]], method_, mID, 0.12,0.15,1.0,0.45,eff_[effID[iEff]][folderID[iFolder]]->drawLegend);
// 	CanvSFComp[iFolder]->cd(iEff+1);
// 	std::cout<< "Drawing SF"<<std::endl;
// 	drawSF          (eff_[effID[iEff]][folderID[iFolder]], method_, mID, mIDnorm, 0.12,0.15,1.0,0.45,eff_[effID[iEff]][folderID[iFolder]]->drawLegend, yLoSF, yHiSF, eff_[effID[iEff]][folderID[iFolder]]->xLo, eff_[effID[iEff]][folderID[iFolder]]->xHi);
	
	std::cout<< "Drawing Eff. and SF"<<std::endl;
	CanvEffAndSFComp[iFolder]->cd(iEff+1);
	drawEffAndSFinOne (eff_[effID[iEff]][folderID[iFolder]], method_, mID, mIDnorm, 0.12,0.15,1.0,0.45,eff_[effID[iEff]][folderID[iFolder]]->drawLegend, yLoSF, yHiSF, eff_[effID[iEff]][folderID[iFolder]]->xLo, eff_[effID[iEff]][folderID[iFolder]]->xHi);
        /// if desired plot also raw event number histos
	if(onlyEffPlots!=1) {
	  std::cout<< "Drawing event numbers"<<std::endl;
	  CanvEvtsComp[iFolder]->cd(iEff+1);
	  drawEventHistos(eff_[effID[iEff]][folderID[iFolder]], method_, mID, 0.12,0.15,1.0,0.45,eff_[effID[iEff]][folderID[iFolder]]->drawLegend);
	  CanvEvtsNormComp[iFolder]->cd(iEff+1);
	  drawEventHistos(eff_[effID[iEff]][folderID[iFolder]], method_, mID, 0.12,0.15,1.0,0.45,eff_[effID[iEff]][folderID[iFolder]]->drawLegend,"normInt");
	}
      }
      for(int iEff=0; iEff<effIDNum2; iEff++){
	CanvComp2[iFolder]->cd(iEff+1);
        // CanvComp[iFolder]->cd(iEff+1)->SetGrid(1,1);
	std::cout<< "Drawing eff. 2"<<std::endl;
	drawEfficiencies(eff_[effID2[iEff]][folderID[iFolder]], method_, mID, 0.12,0.15,1.0,0.45,eff_[effID2[iEff]][folderID[iFolder]]->drawLegend);
	CanvSFComp2[iFolder]->cd(iEff+1);
	std::cout<< "Drawing SF"<<std::endl;
	drawSF          (eff_[effID2[iEff]][folderID[iFolder]], method_, mID, mIDnorm, 0.12,0.15,1.0,0.45,eff_[effID2[iEff]][folderID[iFolder]]->drawLegend, yLoSF, yHiSF, eff_[effID2[iEff]][folderID[iFolder]]->xLo, eff_[effID2[iEff]][folderID[iFolder]]->xHi);
      }
    }
    /// draw 2D efficiencies
    if(do2D){

      CanvComp2DPtEta[iFolder] = new TCanvas("Comparison2DPtEta"+folderID[iFolder], "Comparison2DPtEta"+folderID[iFolder], 1700,1000);
      CanvComp2DPtEta[iFolder]->Divide((mIDNum+1)/2,2);
      
      CanvComp2DPtEtaSF[iFolder] = new TCanvas("Comparison2DPtEtaSF"+folderID[iFolder], "Comparison2DPtEtaSF"+folderID[iFolder], 1700,1000);
      CanvComp2DPtEtaSF[iFolder]->Divide((mIDNum+1)/2,2);
      
      CanvComp2DPtEtaSFerr[iFolder] = new TCanvas("Comparison2DPtEtaSFerr"+folderID[iFolder], "Comparison2DPtEtaSFerr"+folderID[iFolder], 1700,1000);
      CanvComp2DPtEtaSFerr[iFolder]->Divide((mIDNum+1)/2,2);
      
      CanvComp2DPtEtaPass[iFolder] = new TCanvas("Comparison2DPtEtaPass"+folderID[iFolder], "Comparison2DPtEtaPass"+folderID[iFolder], 1700,1000);
      CanvComp2DPtEtaPass[iFolder]->Divide((mIDNum+1)/2,2);
      
      CanvComp2DPtEtaAll[iFolder] = new TCanvas("Comparison2DPtEtaAll"+folderID[iFolder], "Comparison2DPtEtaAll"+folderID[iFolder], 1700,1000);
      CanvComp2DPtEtaAll[iFolder]->Divide((mIDNum+1)/2,2);
      
      std::cout<< "Drawing 2D Pt Eta Eff."<<std::endl;
      for(unsigned int iMethod=0; iMethod<mID.size(); iMethod++){
	CanvComp2DPtEta[iFolder]->cd(iMethod+1);
	eff2DPtEta_[folderID[iFolder]]->his[mID[iMethod]]->Draw("colz text");
	
	CanvComp2DPtEtaPass[iFolder]->cd(iMethod+1);
	eff2DPtEta_[folderID[iFolder]]->hisPass[mID[iMethod]]->Draw("colz text");
	
	CanvComp2DPtEtaAll[iFolder]->cd(iMethod+1);
	eff2DPtEta_[folderID[iFolder]]->hisAll[mID[iMethod]]->Draw("colz text");

	/// 2D SF!!!
	std::cout<< "Drawing 2D SF"<<std::endl;
	
	CanvComp2DPtEtaSF[iFolder]->cd(iMethod+1);
	getSF2D (eff2DPtEta_[folderID[iFolder]], method_, mID, mIDnorm, 0.8, 1.2);
	eff2DPtEta_[folderID[iFolder]]->hisSF[mID[iMethod]]->Draw("colz text");
	
	CanvComp2DPtEtaSFerr[iFolder]->cd(iMethod+1);
	eff2DPtEta_[folderID[iFolder]]->hisSFerr[mID[iMethod]]->Draw("colz text");
      }
    }
    
  // draw legend
    CanvLeg->cd();
    if(iFolder==0) drawLegend(eff_[effID[0]][folderID[0]], method_, mID, 0.,0.,1.,1.);
  
//   effControl[iMethod][iFolder]->GetXaxis()->SetNdivisions(0);
//   effRelIso[iMethod][iFolder]->GetXaxis()->SetNdivisions(505);
 
    if(save){
      for(unsigned int iFileFormat=0; iFileFormat < fileFormat.size(); iFileFormat++){
	if(do1D){
	  CanvComp[iFolder]->Print(outputFolder+outputFileName+folderID[iFolder]+"_overview."+fileFormat[iFileFormat]);
	  for(int iEff=0; iEff<effIDNum; iEff++){
	    //CanvComp  [iFolder]->cd(iEff+1)->Print(outputFolder+outputFileName+folderID[iFolder]+"_"+effID[iEff]+"."+fileFormat[iFileFormat]);
	    //CanvSFComp[iFolder]->cd(iEff+1)->Print(outputFolder+outputFileName+folderID[iFolder]+"_SF_"+effID[iEff]+"."+fileFormat[iFileFormat]);
	    CanvEffAndSFComp[iFolder]->cd(iEff+1)->Print(outputFolder+outputFileName+folderID[iFolder]+"_EffAndSF_"+effID[iEff]+"."+fileFormat[iFileFormat]);
	  }
	  for(int iEff=0; iEff<effIDNum2; iEff++){
	    CanvComp  [iFolder]->cd(iEff+1)->Print(outputFolder+outputFileName+folderID[iFolder]+"_"+effID2[iEff]+"."+fileFormat[iFileFormat]);
	    CanvSFComp[iFolder]->cd(iEff+1)->Print(outputFolder+outputFileName+folderID[iFolder]+"_SF_"+effID2[iEff]+"."+fileFormat[iFileFormat]);
	  }
	}
	/// 2D
	if(do2D){
	  CanvComp2DPtEta[iFolder]->Print(outputFolder+outputFileName+folderID[iFolder]+"_"+"Eff2DPtEta."+fileFormat[iFileFormat]);
	  CanvComp2DPtEtaSF[iFolder]->Print(outputFolder+outputFileName+folderID[iFolder]+"_"+"SF2DPtEta."+fileFormat[iFileFormat]);
	}
	if(iFolder==0) CanvLeg->Print(outputFolder+outputFileName+"_Legend."+fileFormat[iFileFormat]);
	std::cout<<"Canvas with plots is saved in "<<outputFolder<<std::endl;
      }
    }
    /// save graph in root file
    /// 1D
    if(saveRoot && do1D){
      TFile f("MuonEffSF2012.root", "recreate");
      eff_["Eta"]["tapAll"]->graphSF["m2"]->SetName("tapAllSFeta");
      eff_["Eta"]["tapAll"]->graphSF["m2"]->Write();
      eff_["Eta"]["tapAll"]->graphSF["m2PUup"]->SetName("tapAllSFetaPUup");
      eff_["Eta"]["tapAll"]->graphSF["m2PUup"]->Write();
      eff_["Eta"]["tapAll"]->graphSF["m2PUdown"]->SetName("tapAllSFetaPUdown");
      eff_["Eta"]["tapAll"]->graphSF["m2PUdown"]->Write();
      std::cout<<"MuonEffSF2012.root with TGraphErrors is saved "<<std::endl;
    }
    /// 2D
    if(saveRoot && do2D){
      TFile f("MuonEffSF2D2012.root", "recreate");
      eff2DPtEta_[ "tapAll"]->hisSF["m2"]->SetName("tapAllSFeta");
      eff2DPtEta_[ "tapAll"]->hisSF["m2"]->Write();
      eff2DPtEta_[ "tapAll"]->hisSF["m2PUup"]->SetName("tapAllSFetaPUup");
      eff2DPtEta_[ "tapAll"]->hisSF["m2PUup"]->Write();
      eff2DPtEta_[ "tapAll"]->hisSF["m2PUdown"]->SetName("tapAllSFetaPUdown");
      eff2DPtEta_[ "tapAll"]->hisSF["m2PUdown"]->Write();
      std::cout<<"MuonEffSF2D2012.root with 2D SF Histos is saved in "<<std::endl;
    }
  }
  std::cout<< "Done"<<std::endl;
}
