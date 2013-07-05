#include "basicFunctions.h"

void MCstatisticsUncertainty(bool save = true, int verbose=0){
  
  // ============================
  //  Set Root Style
  // ============================
		
  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  myStyle.SetStripDecimals(true);
  myStyle.cd();
  gROOT->SetStyle("HHStyle");
  gROOT->ForceStyle();
  TGaxis::SetMaxDigits(2);


  // ============================
  //  load rootfiles
  // ============================
  std::vector<TFile* > file_;
  TString folder="RecentAnalysisRun8TeV_PromptReco_12fb_PAS";
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/"+folder+"/elecDiffXSecSigSummer12PF.root", "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/"+folder+"/muonDiffXSecSigSummer12PF.root", "Open"));

  std::vector<TString> plotList_, axisLabel_;
  TString plots1D[ ] = {
    // KinFit plots before prob cut 
    "analyzeTopRecoKinematicsKinFit/topPt",
    //"analyzeTopRecoKinematicsKinFit/topPtTtbarSys",
    "analyzeTopRecoKinematicsKinFit/topY",
    "analyzeTopRecoKinematicsKinFit/topMass",
    "analyzeTopRecoKinematicsKinFit/ttbarPt",
    "analyzeTopRecoKinematicsKinFit/ttbarY",
    "analyzeTopRecoKinematicsKinFit/ttbarMass",
    "analyzeTopRecoKinematicsKinFit/ttbarHT",
    "analyzeTopRecoKinematicsKinFit/lepPt",
    "analyzeTopRecoKinematicsKinFit/lepEta",
    "analyzeTopRecoKinematicsKinFit/lightqPt",
    "analyzeTopRecoKinematicsKinFit/lightqEta",   
    "analyzeTopRecoKinematicsKinFit/bqPt",
    "analyzeTopRecoKinematicsKinFit/bqEta",
    "analyzeTopRecoKinematicsKinFit/bbbarPt",
    "analyzeTopRecoKinematicsKinFit/bbbarY",
    "analyzeTopRecoKinematicsKinFit/bbbarMass", 
    // KinFit plots after prob cut 
    "analyzeTopRecoKinematicsKinFitProbSel/topPt",
    //"analyzeTopRecoKinematicsKinFitProbSel/topPtTtbarSys",
    "analyzeTopRecoKinematicsKinFitProbSel/topY",
    "analyzeTopRecoKinematicsKinFitProbSel/topMass",
    "analyzeTopRecoKinematicsKinFitProbSel/ttbarPt",
    "analyzeTopRecoKinematicsKinFitProbSel/ttbarY",
    "analyzeTopRecoKinematicsKinFitProbSel/ttbarMass",
    "analyzeTopRecoKinematicsKinFitProbSel/ttbarHT",
    "analyzeTopRecoKinematicsKinFitProbSel/lepPt",
    "analyzeTopRecoKinematicsKinFitProbSel/lepEta",
    "analyzeTopRecoKinematicsKinFitProbSel/lightqPt",
    "analyzeTopRecoKinematicsKinFitProbSel/lightqEta",   
    "analyzeTopRecoKinematicsKinFitProbSel/bqPt",
    "analyzeTopRecoKinematicsKinFitProbSel/bqEta",
    "analyzeTopRecoKinematicsKinFitProbSel/bbbarPt",
    "analyzeTopRecoKinematicsKinFitProbSel/bbbarY",
    "analyzeTopRecoKinematicsKinFitProbSel/bbbarMass", 
  };
  TString plots2D[ ] = { 
    // b) response matrix top quantities
    "analyzeTopRecoKinematicsKinFit/topPt_"    ,  
    "analyzeTopRecoKinematicsKinFit/topY_"     ,
    // c) response matrix ttbar quantities
    "analyzeTopRecoKinematicsKinFit/ttbarMass_",
    "analyzeTopRecoKinematicsKinFit/ttbarPt_"  ,
    "analyzeTopRecoKinematicsKinFit/ttbarY_"   ,
    // KinFit plots after prob cut 
    // b) response matrix top quantities
    "analyzeTopRecoKinematicsKinFitProbSel/topPt_"    ,  
    "analyzeTopRecoKinematicsKinFitProbSel/topY_"     ,
    // c) response matrix ttbar quantities
    "analyzeTopRecoKinematicsKinFitProbSel/ttbarMass_",
    "analyzeTopRecoKinematicsKinFitProbSel/ttbarPt_"  ,
    "analyzeTopRecoKinematicsKinFitProbSel/ttbarY_"   ,
  };
  TString axisLabel1D[ ] = { 
    // KinFit plots before prob cut 
    "p_{T}^{t} #left[GeV#right];Top quarks;0;20",
    //"p_{T}^{t} #left[GeV#right] (t#bar{t} system);Events;0;20",
    "y^{t};Top quarks;0;1",
    "m^{t};Top quarks;0;10",
    "p_{T}^{t#bar{t}} #left[GeV#right];Top-quark pairs;0;20",
    "y^{t#bar{t}};Top-quark pairs;0;1",
    "m^{t#bar{t}} #left[GeV#right];Top-quark pairs;0;50",
    "H_{T}^{t#bar{t}}=#Sigma(E_{T}(jets)) #left[GeV#right];#frac{dN}{dH_{T}^{t#bar{t}}};0;20",
    "p_{T}^{l} #left[GeV#right];N^{l};0;10",
    "#eta^{l};Leptons;0;1",
    "p_{T}^{q} #left[GeV#right];tt jets;0;20",    
    "#eta^{q};tt jets;0;1",
    "p_{T}^{b} #left[GeV#right];b-jets;0;20",    
    "#eta^{b};b-jets;0;1",
    "p_{T}^{b#bar{b}}(assigned to t#bar{t} system) #left[GeV#right];Events;0;20",  
    "y^{b#bar{b}}(assigned to t#bar{t} system);Events;0;1",
    "m^{b#bar{b}}(assigned to t#bar{t} system) #left[GeV#right];Events;0;20",
    // KinFit plots after prob cut 
    "p_{T}^{t} #left[GeV#right];Top quarks;0;20",
    //"p_{T}^{t} #left[GeV#right] (t#bar{t} system);Events;0;20",
    "y^{t};Top quarks;0;1",
    "m^{t};Top quarks;0;10",
    "p_{T}^{t#bar{t}} #left[GeV#right];Top-quark pairs;0;20",
    "y^{t#bar{t}};Top-quark pairs;0;1",
    "m^{t#bar{t}} #left[GeV#right];Top-quark pairs;0;50",
    "H_{T}^{t#bar{t}}=#Sigma(E_{T}(jets)) #left[GeV#right];#frac{dN}{dH_{T}^{t#bar{t}}};0;20",
    "p_{T}^{l} #left[GeV#right];N^{l};0;10",
    "#eta^{l};Leptons;0;1",
    "p_{T}^{q} #left[GeV#right];tt jets;0;20",    
    "#eta^{q};tt jets;0;1",
    "p_{T}^{b} #left[GeV#right];b-jets;0;20",    
    "#eta^{b};b-jets;0;1",
    "p_{T}^{b#bar{b}}(assigned to t#bar{t} system) #left[GeV#right];Events;0;20",  
    "y^{b#bar{b}}(assigned to t#bar{t} system);Events;0;1",
    "m^{b#bar{b}}(assigned to t#bar{t} system) #left[GeV#right];Events;0;20",
  };

  // 2D: "x-axis title"/"y-axis title"
  TString axisLabel2D[ ] = {// reco - gen Match correlation plots (ttbar signal only)
    // b) response matrix Top quantities
    xSecLabelName("topPt"    )+" gen;"+xSecLabelName("topPt"     )+" reco",
    xSecLabelName("topY"     )+" gen;"+xSecLabelName("topY"     )+" reco",
    // c) response matrix ttbar quantities
    xSecLabelName("ttbarMass")+" gen;"+xSecLabelName("ttbarMass")+" reco",
    xSecLabelName("ttbarPt")+" gen;"+xSecLabelName("ttbarPt")+" reco",
    xSecLabelName("ttbarY")+" gen;"+xSecLabelName("ttbarY")+" reco" ,
    // KinFit plots after prob cut 
    // b) response matrix Top quantities
    xSecLabelName("topPt"    )+" gen;"+xSecLabelName("topPt"     )+" reco",
    xSecLabelName("topY"     )+" gen;"+xSecLabelName("topY"     )+" reco",
    // c) response matrix ttbar quantities
    xSecLabelName("ttbarMass")+" gen;"+xSecLabelName("ttbarMass")+" reco",
    xSecLabelName("ttbarPt")+" gen;"+xSecLabelName("ttbarPt")+" reco",
    xSecLabelName("ttbarY")+" gen;"+xSecLabelName("ttbarY")+" reco" ,
  };
  plotList_.insert(plotList_.begin(), plots1D, plots1D + sizeof(plots1D)/sizeof(TString));
  plotList_.insert(plotList_.end()  , plots2D, plots2D + sizeof(plots2D)/sizeof(TString));
  axisLabel_.insert(axisLabel_.begin(), axisLabel1D, axisLabel1D + sizeof(axisLabel1D)/sizeof(TString));
  axisLabel_.insert(axisLabel_.end()  , axisLabel2D, axisLabel2D + sizeof(axisLabel2D)/sizeof(TString));
  if(plotList_.size() != axisLabel_.size()){
    std::cout << "ERROR - 1D plots: Number of plots and axis label do not correspond .... Exiting macro!" << std::endl;
    exit(1);
  }
  double N1D=sizeof(plots1D)/sizeof(TString);
  // run automatically in batch mode if there are many canvas
  if(plotList_.size()>15) gROOT->SetBatch();

  // canvas container
  std::vector<TCanvas*> plotCanvas_;
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map< TString, std::map <unsigned int, TH2F*> > histo2D_;
  // create variable bin edges
  std::map<TString, std::vector<double> > binning_ = makeVariableBinning(false);
  // loop all plots
  for(int plot=0; plot<(int)plotList_.size(); ++plot){
    TString name=plotList_[plot];
    TString shortname=getStringEntry(name, 2, "/");
    shortname.ReplaceAll("_","");
    std::cout << std::endl << name << std::endl;
    int kdummy=42;
    // load 1D
    if(plot<N1D){
      std::cout << "1D" << std::endl;
      std::cout << "file 0" << std::endl;
      histo_[name][kdummy]=(TH1F*)file_[0]->Get(name);
      std::cout << "file 1" << std::endl;
      histo_[name][kdummy]->Add((TH1F*)file_[1]->Get(name));
    }
    // load 2D
    else{
      std::cout << "2D" << std::endl;
      std::cout << "file 0" << std::endl;
      histo2D_[name][kdummy]=(TH2F*)file_[0]->Get(name);
      std::cout << "file 1" << std::endl;
      histo2D_[name][kdummy]->Add((TH2F*)file_[1]->Get(name));
    }
    // rebinning
    // equidistant rebinning (1D only)
    std::cout << "rebinning" << std::endl;
    double reBinFactor = plot<N1D ? atof(((string)getStringEntry(axisLabel_[plot],4,";")).c_str()) : 1;
    if(reBinFactor>1&&binning_.count(shortname)==0){
      std::cout << "equidistant" << std::endl;
      if(plot<N1D) equalReBinTH1(reBinFactor, histo_, name, kdummy);
    }
    // variable binning
    else if(binning_.count(shortname)!=0){
      std::cout << "variable" << std::endl;
      // 1D
      if(plot<N1D){
	reBinTH1F(*histo_[name][kdummy], binning_[shortname], verbose-1);
      }
      // 2D
      else histo2D_[name][kdummy]=reBinTH2F(*histo2D_[name][kdummy], binning_[shortname], verbose);
    }
    // histostyle
    // 1D
    if(plot<N1D){
      histogramStyle(*histo_[name][kdummy], kSig, true);
      axesStyle(*histo_[name][kdummy], getStringEntry(axisLabel_[plot],1, ";"), getStringEntry(axisLabel_[plot],2, ";"));
      histo_[name][kdummy]->GetXaxis()->SetNoExponent(true);
    }
    // 2D
    else{
      histStyle2D(*histo2D_[name][kdummy],"",getStringEntry(axisLabel_[plot],1,";"),getStringEntry(axisLabel_[plot],2,";"));
      histo2D_[name][kdummy]->GetXaxis()->SetNoExponent(true);
      histo2D_[name][kdummy]->GetYaxis()->SetNoExponent(true);
    }
    // ============================
    //  create relative error plots
    // ============================
    int kdummy2=42*42;
    int digits=2;
    if(plot<N1D){
      // clone plot
      histo_[name][kdummy2]=(TH1F*)histo_[name][kdummy]->Clone(TString(histo_[name][kdummy]->GetName())+"relErr");
      // loop bins
      for(int bin=0; bin<= histo_[name][kdummy2]->GetNbinsX(); ++bin){
	// fill relative error in %
	histo_[name][kdummy2]->SetBinContent(bin, round(100./sqrt(histo_[name][kdummy2]->GetBinContent(bin)), digits));
      }
    }
    // 2D
    else{
      // clone plot
      histo2D_[name][kdummy2]=(TH2F*)histo2D_[name][kdummy]->Clone(TString(histo2D_[name][kdummy]->GetName())+"relErr");
      // loop bins
      for (Int_t ibinx = 0; ibinx <= histo2D_[name][kdummy]->GetNbinsX()+1; ibinx++) {
	for (Int_t ibiny = 0; ibiny <= histo2D_[name][kdummy]->GetNbinsY()+1; ibiny++) {
	  // fill relative error in %
	  double val=histo2D_[name][kdummy]->GetBinContent(ibinx, ibiny);
	  if (val <= 0.0) histo2D_[name][kdummy2]->SetBinContent(ibinx, ibiny, 0);
	  else histo2D_[name][kdummy2]->SetBinContent(ibinx, ibiny, round(100./sqrt(val), digits));
	}
      }
    }

    
    // ============================
    //  create canvas
    // ============================
    //char canvname[10];
    //sprintf(canvname,"canv%i",plot);  
    TString canvname=getStringEntry(name, 2, "/")+getStringEntry(name, 1, "/");
    plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );  
    plotCanvas_[plotCanvas_.size()-1]->cd(0);
    if(plot>=N1D) plotCanvas_[plotCanvas_.size()-1]->SetRightMargin(4*myStyle.GetPadRightMargin());
    // ============================
    //  plotting
    // ============================
    if(plot<N1D){
      histo_[name][kdummy]->Draw("hist");
      histo_[name][kdummy2]->Draw("text same");
    }
    else{
      histo2D_[name][kdummy]->Draw("colz");
      histo2D_[name][kdummy2]->Draw("text same");
    }
    // draw cut label
    DrawDecayChLabel("e/#mu + Jets Combined");
  }
  if(save){
    saveCanvas(plotCanvas_, "./MCstats/", "MCstatisticsStudy", true, true);
  }
}
