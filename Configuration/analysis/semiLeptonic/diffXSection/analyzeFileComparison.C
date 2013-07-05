#include "basicFunctions.h"

void analyzeFileComparison(bool save = true, int verbose=0){
  
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
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_PromptReco_12fb_PAS/fixedTopMass171_5/elecDiffXSecSigSummer12PF.root", "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_PromptReco_12fb_PAS/fixedTopMass171_5/muonDiffXSecSigSummer12PF.root", "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/newRecentAnalysisRunTopMassFix_PromptReco_12fb/elecDiffXSecSigSummer12PF.root", "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/newRecentAnalysisRunTopMassFix_PromptReco_12fb/muonDiffXSecSigSummer12PF.root", "Open"));
  // list plots of relevance
  std::vector<TString> plotList_, axisLabel_;
  TString plots1D[ ] = {
    // KinFit plots before prob cut 
    "analyzeTopRecoKinematicsKinFit/prob",
    "analyzeTopRecoKinematicsKinFit/ttbarAngle",
    "analyzeTopRecoKinematicsKinFit/topPt",
    "analyzeTopRecoKinematicsKinFit/topPtTtbarSys",
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
    "analyzeTopRecoKinematicsKinFit/lepEtaPlus",
    "analyzeTopRecoKinematicsKinFit/lepEtaMinus",
    "analyzeTopRecoKinematicsKinFit/topEtaPlus",
    "analyzeTopRecoKinematicsKinFit/topEtaMinus",
    "analyzeTopRecoKinematicsKinFit/lepYPlus",
    "analyzeTopRecoKinematicsKinFit/lepYMinus",
    "analyzeTopRecoKinematicsKinFit/topYPlus",
    "analyzeTopRecoKinematicsKinFit/topYMinus",
    "analyzeTopRecoKinematicsKinFit/topYHad",
    "analyzeTopRecoKinematicsKinFit/topYLep",
    "analyzeTopRecoKinematicsKinFit/topYLead",
    "analyzeTopRecoKinematicsKinFit/topYSubLead",
    "analyzeTopRecoKinematicsKinFit/leadqPt",
    "analyzeTopRecoKinematicsKinFit/bbbarPt",
    "analyzeTopRecoKinematicsKinFit/bbbarY",
    "analyzeTopRecoKinematicsKinFit/bbbarMass", 
    "compositedKinematicsKinFit/shiftLqPt",
    "compositedKinematicsKinFit/shiftLqEta",
    "compositedKinematicsKinFit/shiftLqPhi",
    "compositedKinematicsKinFit/shiftBqPt",
    "compositedKinematicsKinFit/shiftBqEta",
    "compositedKinematicsKinFit/shiftBqPhi",
    "compositedKinematicsKinFit/shiftLepPt",
    "compositedKinematicsKinFit/shiftLepEta",
    "compositedKinematicsKinFit/shiftLepPhi",
    "compositedKinematicsKinFit/shiftNuPt",
    "compositedKinematicsKinFit/shiftNuEta",
    "compositedKinematicsKinFit/shiftNuPhi",
    // KinFit plots after prob cut 
    "analyzeTopRecoKinematicsKinFitProbSel/ttbarAngle",
    "analyzeTopRecoKinematicsKinFitProbSel/topPt",
    "analyzeTopRecoKinematicsKinFitProbSel/topPtTtbarSys",
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
    "analyzeTopRecoKinematicsKinFitProbSel/lepEtaPlus",
    "analyzeTopRecoKinematicsKinFitProbSel/lepEtaMinus",
    "analyzeTopRecoKinematicsKinFitProbSel/topEtaPlus",
    "analyzeTopRecoKinematicsKinFitProbSel/topEtaMinus",
    "analyzeTopRecoKinematicsKinFitProbSel/lepYPlus",
    "analyzeTopRecoKinematicsKinFitProbSel/lepYMinus",
    "analyzeTopRecoKinematicsKinFitProbSel/topYPlus",
    "analyzeTopRecoKinematicsKinFitProbSel/topYMinus",
    "analyzeTopRecoKinematicsKinFitProbSel/topYHad",
    "analyzeTopRecoKinematicsKinFitProbSel/topYLep",
    "analyzeTopRecoKinematicsKinFitProbSel/topYLead",
    "analyzeTopRecoKinematicsKinFitProbSel/topYSubLead",
    "analyzeTopRecoKinematicsKinFitProbSel/leadqPt",
    "analyzeTopRecoKinematicsKinFitProbSel/bbbarPt",
    "analyzeTopRecoKinematicsKinFitProbSel/bbbarY",
    "analyzeTopRecoKinematicsKinFitProbSel/bbbarMass", 
  };
  TString axisLabel1D[ ] = { 
    // KinFit plots before prob cut 
    "probability (best fit hypothesis);Events;1;25", 
    "#angle(t,#bar{t});Events;0;15",
    "p_{T}^{t} #left[GeV#right];Top quarks;0;20",
    "p_{T}^{t} #left[GeV#right] (t#bar{t} system);Events;0;20",
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
    "#eta^{l+};Events;0;1",
    "#eta^{l-};Events;0;1",
    "#eta^{t+};Events;0;1",
    "#eta^{t-};Events;0;1",
    "y^{l+};Events;0;1",
    "y^{l-};Events;0;1",
    "y^{t+};Events;0;1",
    "y^{t-};Events;0;1",
    "y^{t+};Events;0;1",
    "y^{t-};Events;0;1",
    "y^{Lead.t};Events;0;1",
    "y^{NLead.t};Events;0;1",
    "p_{T}^{leading jet} #left[GeV#right];Events;0;4",
    "p_{T}^{b#bar{b}}(assigned to t#bar{t} system) #left[GeV#right];Events;0;20",  
    "y^{b#bar{b}}(assigned to t#bar{t} system);Events;0;1",
    "m^{b#bar{b}}(assigned to t#bar{t} system) #left[GeV#right];Events;0;20",
    "#Delta p_{T}^{light jets} #left[GeV#right];Events;0;40",
    "#Delta #eta^{light jets};Events;0;1",
    "#Delta #phi^{light jets};Events;0;20",
    "#Delta p_{T}^{b jets} #left[GeV#right];Events;0;25",
    "#Delta #eta^{b jets};Events;0;2",
    "#Delta #phi^{b jets};Events;0;2",
    "#Delta p_{T}^{lepton} #left[GeV#right];Events;0;2",
    "#Delta #eta^{lepton};Events;0;1",
    "#Delta #phi^{lepton};Events;0;1",
    "#Delta p_{T}^{neutrino} #left[GeV#right];Events;0;10",
    "#Delta #eta^{neutrino};Events;0;20",
    "#Delta #phi^{neutrino};Events;0;4",
    // KinFit plots after prob cut 
    "#angle(t,#bar{t});Events;0;15",
    "p_{T}^{t} #left[GeV#right];Top quarks;0;20",
    "p_{T}^{t} #left[GeV#right] (t#bar{t} system);Events;0;20",
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
    "#eta^{l+};Events;0;1",
    "#eta^{l-};Events;0;1",
    "#eta^{t+};Events;0;1",
    "#eta^{t-};Events;0;1",
    "y^{l+};Events;0;1",
    "y^{l-};Events;0;1",
    "y^{t+};Events;0;1",
    "y^{t-};Events;0;1",
    "y^{t+};Events;0;1",
    "y^{t-};Events;0;1",
    "y^{Lead.t};Events;0;1",
    "y^{NLead.t};Events;0;1",
    "p_{T}^{leading jet} #left[GeV#right];Events;0;4",
    "p_{T}^{b#bar{b}}(assigned to t#bar{t} system) #left[GeV#right];Events;0;20",  
    "y^{b#bar{b}}(assigned to t#bar{t} system);Events;0;1",
    "m^{b#bar{b}}(assigned to t#bar{t} system) #left[GeV#right];Events;0;20",
  };
  plotList_ .insert(plotList_ .begin(), plots1D    , plots1D    + sizeof(plots1D    )/sizeof(TString));
  axisLabel_.insert(axisLabel_.begin(), axisLabel1D, axisLabel1D+ sizeof(axisLabel1D)/sizeof(TString));
  if(plotList_.size() != axisLabel_.size()){
    std::cout << "ERROR - 1D plots: Number of plots and axis label do not correspond .... Exiting macro!" << std::endl;
    exit(1);
  }
  // run automatically in batch mode if there are many canvas
  if(plotList_.size()>15) gROOT->SetBatch();

  // canvas container
  std::vector<TCanvas*> plotCanvas_;
  // legend
  TLegend* leg= new TLegend(0.6, 0.75, 0.9, 0.88);
  legendStyle(*leg,"t#bar{t} SG MC (m_{top}^{gen}=172.5 GeV)");
  
  // ============================
  //  get histos
  // ============================
  unsigned int k1725=0;
  unsigned int k1715=1;
  
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  // loop all plots
  for(int plot=0; plot<(int)plotList_.size(); ++plot){
    TString name=plotList_[plot];
    // nominal mtop
    histo_[name][k1725]=(TH1F*)file_[2]->Get(name);
    histo_[name][k1725]->Add((TH1F*)file_[3]->Get(name));
    // mtop -1 GeV shifted
    histo_[name][k1715]=(TH1F*)file_[0]->Get(name);
    histo_[name][k1715]->Add((TH1F*)file_[1]->Get(name));
    // rebinning
    double reBinFactor = atof(((string)getStringEntry(axisLabel_[plot],4,";")).c_str());
    if(reBinFactor>1){
      equalReBinTH1(reBinFactor, histo_, name, k1715);
      equalReBinTH1(reBinFactor, histo_, name, k1725);
    }
    // legend
    if(plot==0){
      leg->AddEntry(histo_[name][k1725], "m_{top}^{rec}=172.5 GeV fix", "L");
      leg->AddEntry(histo_[name][k1715], "m_{top}^{rec}=171.5 GeV fix", "L");
    }   
    // histostyle
    histo_[name][k1725]->SetLineColor(kRed );
    histo_[name][k1715]->SetLineColor(kBlue);
    histo_[name][k1725]->SetStats(false);
    histo_[name][k1715]->SetStats(false);

    // ============================
    //  create canvas
    // ============================
    char canvname[10];
    sprintf(canvname,"canv%i",plot);    
    plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );
    // min/max (y-axis)
    unsigned int sampleMax= (histo_[name][k1725]->GetMaximum()>histo_[name][k1715]->GetMaximum()) ? k1725 : k1715;
    double max = 1.4*histo_[name][sampleMax]->GetMaximum();
    double min = 0.;
    // log plots
    if(getStringEntry(axisLabel_[plot],3,";")=="1"){
      plotCanvas_[plot]->SetLogy(1);
      min=1;
      max=exp(1.4*(std::log(max)-std::log(min))+std::log(min));
    }
    if(min==0.&&max>0.001) min+=0.001;
    if(min==1.&&max>1.001) min+=0.001;
    axesStyle(*histo_[name][k1725], getStringEntry(axisLabel_[plot],1,";"), getStringEntry(axisLabel_[plot],2,";"), min, max);	    
    // adjust range (x-axis)
    double xUp=histo_[name][k1725]->GetXaxis()->GetXmax();
    double xDn=histo_[name][k1725]->GetXaxis()->GetXmin();
    if(name.Contains("topPt" )){xDn=0.  ; xUp=400.;}
    if(name.Contains("topY"  )){xDn=-2.5; xUp=2.5 ;}
    if(name.Contains("ttbarY")){xDn=-2.5; xUp=2.5 ;}
    if(name.Contains("ttbarMass")){xDn=300.;xUp=1000.;}
    if(name.Contains("ttbarHT"  )){xDn=50. ;xUp=500.;}
    if(name.Contains("lepPt" )){xDn=0.;xUp=200.;}
    if(name.Contains("lepEta")){xDn=-2.0;xUp=2.0;}
    if(name.Contains("leadqPt" )){xDn=0.;xUp=300.;}
    if(name.Contains("leadqEta")){xDn=-3.;xUp=3.;}
    if(name.Contains("bqPt" )){xDn=0. ;xUp=300.;}
    if(name.Contains("bqEta")){xDn=-3.;xUp=3.;}
    if(name.Contains("bbbarPt")){xDn=0.;xUp=300.;}
    if(name.Contains("bbbarY"   )){xDn=-2.5;xUp=2.5;}
    if(name.Contains("bbbarMass")){xDn=0.;xUp=500.;}
    if(name.Contains("shiftLqEta")){xDn=-0.4;xUp=0.4;}
    if(name.Contains("shiftLqPhi")){xDn=-0.2;xUp=0.2;}
    if(name.Contains("shiftBqPt")){xDn=-30.;xUp=30.;}
    if(name.Contains("shiftBqEta")){xDn=-0.02;xUp=0.02;}
    if(name.Contains("shiftBqPhi")){xDn=-0.1;xUp=0.1;}
    if(name.Contains("shiftLepPt")){xDn=-5.;xUp=5.;}
    if(name.Contains("shiftNuPt" )){xDn=-50.;xUp=50.;}
    if(name.Contains("shiftNuPhi" )){xDn=-1.;xUp=1.;}
    //if(name.Contains("")){xDn=;xUp=;}
    //if(name.Contains("")){xDn=;xUp=;}
    if(xUp!=histo_[name][k1725]->GetXaxis()->GetXmax()||xDn!=histo_[name][k1725]->GetXaxis()->GetXmin()) histo_[name][k1725]->GetXaxis()->SetRangeUser(xDn,xUp-0.000001);
    
    // ============================
    //  plotting
    // ============================
    histo_[name][k1725]->Draw("hist");
    histo_[name][k1715]->Draw("hist same");
    leg->Draw("same");
    // draw cut label
    TString cutLabel="1 lepton, #geq4 Jets";
    if(name.Contains("Tagged")||plotList_[plot].Contains("AfterBtagging")) cutLabel+=", #geq2 b-tags";
    else if(name.Contains("KinFit")) cutLabel+=", #geq2 b-tags, KinFit";
    if(plotList_[plot].Contains("ProbSel")) cutLabel.ReplaceAll("KinFit","prob>0.02");
    double positionX=xUp+0.045*(xUp-xDn)*(gStyle->GetCanvasDefW()/600.);
    double positionY=min;
    //std::cout << plotList_[plot] << ": " << xUp << "+0.03*(" << xUp << "-" << xDn << ")=" << positionX << std::endl;
    TLatex *sellabel = new TLatex(positionX,positionY,cutLabel);
    sellabel->SetTextAlign(11);
    sellabel->SetTextAngle(90);
    sellabel->SetTextSize(0.04);
    sellabel->Draw("same");
    DrawDecayChLabel("e/#mu + Jets Combined");
    // ratio
    std::vector<double> err_;
    for(int bin=1; bin<=histo_[name][k1725]->GetNbinsX(); ++bin){
      double b =histo_[name][k1725]->GetBinContent(bin);
      double Db=sqrt(b);
      double a =histo_[name][k1715]->GetBinContent(bin);
      double Da=sqrt(a);
      err_.push_back(sqrt((a*a*Db*Db)/(b*b*b*b)+(Da*Da)/(b*b)));
    }
    //gStyle->SetErrorX(0.5);
    drawRatio(histo_[name][k1715], histo_[name][k1725], 0.9, 1.12, myStyle, verbose, err_, "m_{top}^{rec}=171.5 GeV", "m_{top}^{rec}=172.5 GeV", "e X0", kBlack, false, 0.2);
  }

  if(save){
    saveCanvas(plotCanvas_, "./topMassBias", "topMassBiasStudy", true, true);
  }
}
