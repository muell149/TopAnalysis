  #include "basicFunctions.h"
#include "TTree.h"

void kinfitObjectShift(double luminosity = 4967.5, bool save = true, int verbose=0, 
		       TString inputFolderName="RecentAnalysisRun",
		       //TString dataFile= "/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/analyzeDiffXData2011AllCombinedMuon.root",
		       //TString dataFile= "/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/analyzeDiffXData2011AllCombinedElectron.root",
		       TString dataFile= "/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/analyzeDiffXData2011AllCombinedElectron.root:/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/analyzeDiffXData2011AllCombinedMuon.root",
		       const std::string decayChannel = "combined",
		       bool withRatioPlot = true)
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
  //bool setQCDtoZero=true;
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
  TString outputFileName="diffXSecObjectShifts";
  if(decayChannel=="muon"    ) outputFileName+="Mu";
  if(decayChannel=="electron") outputFileName+="Elec";
  if(decayChannel=="combined") outputFileName+="Comb";
  outputFileName+=".root";
  // choose name of the output .pdf file
  TString pdfName="differentialXSecMonitoring"+lumi+"pb";
  // adjust luminosity and data files for combined control plots
  double luminosityEl=0;
  double luminosityMu=0;
  TString dataFileEl="";
  TString dataFileMu="";
  if(decayChannel=="combined"&&luminosity>4500&&luminosity<5000){
    luminosityEl=constLumiElec;
    luminosityMu=constLumiMuon;
    dataFileEl=getStringEntry(dataFile,1 , ":");
    dataFileMu=getStringEntry(dataFile,42, ":");
  }

    //// kinfit object shifts
    //"compositedKinematicsKinFit/shiftLqPt",
    //"compositedKinematicsKinFit/shiftLqEta",
    //"compositedKinematicsKinFit/shiftLqPhi",
    //"compositedKinematicsKinFit/shiftBqPt",
    //"compositedKinematicsKinFit/shiftBqEta",
    //"compositedKinematicsKinFit/shiftBqPhi",
    //"compositedKinematicsKinFit/shiftLepPt",
    //"compositedKinematicsKinFit/shiftLepEta",
    //"compositedKinematicsKinFit/shiftLepPhi",
    //"compositedKinematicsKinFit/shiftNuPt",
    //"compositedKinematicsKinFit/shiftNuEta",
    //"compositedKinematicsKinFit/shiftNuPhi",
    //// kinfit object shifts
    //"#Delta p_{T}^{light jets} #left[GeV#right];events;0;5",
    //"#Delta #eta^{light jets};events;0;1",
    //"#Delta #phi^{light jets};events;0;10",
    //"#Delta p_{T}^{b jets} #left[GeV#right];events;0;5",
    //"#Delta #eta^{b jets};events;0;1",
    //"#Delta #phi^{b jets};events;0;2",
    //"#Delta p_{T}^{lepton} #left[GeV#right];events;0;1",
    //"#Delta #eta^{lepton};events;0;1",
    //"#Delta #phi^{lepton};events;0;1",
    //"#Delta p_{T}^{neutrino} #left[GeV#right];events;0;5",
    //"#Delta #eta^{neutrino};events;0;20",
    //"#Delta #phi^{neutrino};events;0;2",

  // get files
  std::map<unsigned int, TFile*> files_, filesMu_, filesEl_;
  if(decayChannel!="combined") files_ = getStdTopAnalysisFiles(inputFolder, sysNo, dataFile, decayChannel);
  else{
    filesMu_ = getStdTopAnalysisFiles(inputFolder, sysNo, dataFileMu, "muon"    );
    filesEl_ = getStdTopAnalysisFiles(inputFolder, sysNo, dataFileEl, "electron");
  }

  // create list of plots
  std::vector<TString> plotList_;
  plotList_.push_back("shiftBqPt"      );
  plotList_.push_back("shiftBqPtEtaR05");
  plotList_.push_back("shiftBqPtEtaR12");
  plotList_.push_back("shiftBqPtEtaR18");
  plotList_.push_back("shiftBqPtEtaR24");
  plotList_.push_back("shiftBqPtPtR50" );
  plotList_.push_back("shiftBqPtPtR80" );
  plotList_.push_back("shiftBqPtPtR120");
  plotList_.push_back("shiftBqPtPtRinf");
  // create list of selection criterias
  std::vector<TString> selList_;
  selList_.push_back("");
  selList_.push_back("( TMath::Abs(bqlepEtaPre)<0.5 && TMath::Abs(bqlepEtaPre)<0.5 )");
  selList_.push_back("( TMath::Abs(bqlepEtaPre)<1.2 && TMath::Abs(bqlepEtaPre)>0.5 )");
  selList_.push_back("( TMath::Abs(bqlepEtaPre)<1.8 && TMath::Abs(bqlepEtaPre)>1.2 )");
  selList_.push_back("( TMath::Abs(bqlepEtaPre)<2.4 && TMath::Abs(bqlepEtaPre)>1.8 )");
  selList_.push_back("( TMath::Abs(bqlepPtPre)<50. && TMath::Abs(bqlepPtPre)>30. )");
  selList_.push_back("( TMath::Abs(bqlepPtPre)<80. && TMath::Abs(bqlepPtPre)>50. )");
  selList_.push_back("( TMath::Abs(bqlepPtPre)<120.&& TMath::Abs(bqlepPtPre)>80. )");
  selList_.push_back("( TMath::Abs(bqlepPtPre)>120.&& TMath::Abs(bqlepPtPre)>120.)");

  // container for all histos (1D&2D)
  // example for acess: histo_["plotName"][sampleNr]
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  TString folder="compositedKinematicsKinFit";
  std::vector<TCanvas*> plotCanvas_;
  // loop files
  for(unsigned int sample=kSig; sample<=kSAToptW; ++sample){
    if(verbose>1) std::cout << sampleLabel(sample, "muon") << std::endl;
    if(sample!=kQCD&&sample!=kSTop&&sample!=kDiBos&&(sample<kQCDEM1||sample>kQCDBCE3)){
      // A) get trees   
      TTree* treeMu=(TTree*)(filesMu_[sample]->Get(folder+"/tree"));
      TTree* treeEl=(TTree*)(filesEl_[sample]->Get(folder+"/tree"));
      treeMu->SetBranchStatus("*", 1);
      treeEl->SetBranchStatus("*", 1);
      // B) loop plotlist
      for(unsigned int plot=0; plot<plotList_.size(); plot++){
	// C) get event weight and selection criteria
	TString SF=selList_[plot]+( (sample!=kData) ? (selList_[plot]=="" ? "weight" :"*weight" ) : "" );
	if(verbose>1) std::cout << "event SF used: " << SF << std::endl;
	// D) get plots from tree (lep/had b & mu/el channel)
	TString plotname=plotList_[plot];
	plotname.ReplaceAll("shift","");
	treeMu->Draw("bqlepPtPre-bqlepPtFit>>"+plotname+"Lep"+"Mu"+"(20,-50.,50.)",SF,"goff");
	treeMu->Draw("bqhadPtPre-bqhadPtFit>>"+plotname+"Had"+"Mu"+"(20,-50.,50.)",SF,"goff");
	treeEl->Draw("bqlepPtPre-bqlepPtFit>>"+plotname+"Lep"+"El"+"(20,-50.,50.)",SF,"goff");
	treeEl->Draw("bqhadPtPre-bqhadPtFit>>"+plotname+"Had"+"El"+"(20,-50.,50.)",SF,"goff");
	// E) do lumiweithing and save plots in map
	histo_[plotList_[plot]][sample] = (TH1F*)(gDirectory->Get(plotname+"Lep"+"Mu")->Clone());
	histo_[plotList_[plot]][sample]->Scale(lumiweight(sample, luminosityMu, sysNo, "muon"));
	histo_[plotList_[plot]][sample]->Add(((TH1F*)gDirectory->Get(plotname+"Had"+"Mu")->Clone()), lumiweight(sample, luminosityMu, sysNo, "muon"    ));
	histo_[plotList_[plot]][sample]->Add(((TH1F*)gDirectory->Get(plotname+"Lep"+"El")->Clone()), lumiweight(sample, luminosityEl, sysNo, "electron"));
	histo_[plotList_[plot]][sample]->Add(((TH1F*)gDirectory->Get(plotname+"Had"+"El")->Clone()), lumiweight(sample, luminosityEl, sysNo, "electron"));
	// configutre histostyle
	histogramStyle(*histo_[plotList_[plot]][sample], sample, true);
      }
    }
    else if(sample==kQCD){
      // loop histolist
      for(unsigned int plot=0; plot<plotList_.size(); plot++){
	// clone signal plot
	histo_[plotList_[plot]][sample] = (TH1F*)(histo_[plotList_[plot]][kSig]->Clone());
	// set bin content to 0
	histo_[plotList_[plot]][sample]->Scale(0.);
	// set style
	histogramStyle(*histo_[plotList_[plot]][sample], sample, true);
      }
    }
  }
  // create canvas
  for(unsigned int sample=0; sample<plotList_.size(); sample++){
    char canvname[10];
    sprintf(canvname,"canv%i",sample);
    plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );
  }

  //  Add single top channels and DiBoson contributions
  // reCreate: reCreate combined plots if they are already existing
  std::map< TString, std::map <unsigned int, TH2F*> > histo2_;
  bool reCreate=false;
  AddSingleTopAndDiBoson(plotList_, histo_, histo2_, plotList_.size(), verbose, reCreate, "");
  
  // create stack plots
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    createStackPlot(plotList_, histo_, plot, plotList_.size(), verbose, "muon");
  }

  //  Do the printing
  int canvasNumber=0;
  // loop plots
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    bool first=true;
    if(verbose>1) std::cout << plotList_[plot] << std::endl;
    // open canvas and set title corresponding to plotname in .root file
    plotCanvas_[canvasNumber]->cd(0);
    plotCanvas_[canvasNumber]->SetTitle(getStringEntry(plotList_[plot], 1));	  
    // loop samples
    for(unsigned int sample=kSig; sample<=kData; ++sample){
      if(verbose>1) std::cout << sampleLabel(sample, "muon") << std::endl;
      // check existance
      if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)&&(histo_[plotList_[plot]][sample])){
	if(verbose>1) std::cout << sampleLabel(sample, "muon") << "found, " << histo_[plotList_[plot]][sample]->GetEntries() << " entries" << std::endl;
	histo_[plotList_[plot]][sample]->GetXaxis()->SetNoExponent(true); 
	// first plot
	if(first){
	  double max=20000.;
	  double min=0;
	  axesStyle(*histo_[plotList_[plot]][sample], "#Delta p_{t}^{b jets}", "events", min, max);
	  histo_[plotList_[plot]][sample]->Draw("hist X0");
	}
	else{ 
	  // draw data as points
	  if(sample==kData) histo_[plotList_[plot]][sample]->Draw("p e X0 same");
	  // draw others as histo (stack)
	  else histo_[plotList_[plot]][sample]->Draw("hist X0 same");
	}
	first=false;
      }
    }
    // add labels for decay channel, luminosity, energy and CMS preliminary (if applicable)
    if (decayChannel=="muon") DrawDecayChLabel("#mu + Jets");
    else if (decayChannel=="electron") DrawDecayChLabel("e + Jets");
    else DrawDecayChLabel("e/#mu + Jets Combined");	      
    DrawCMSLabels(false,luminosity); 
    if(plotList_[plot].Contains("R")){
      TString label="";
      if(plotList_[plot].Contains("EtaR05")) label+="|#eta| < 0.5";
      if(plotList_[plot].Contains("EtaR12")) label+="0.5 < |#eta| < 1.2";
      if(plotList_[plot].Contains("EtaR18")) label+="1.2 < |#eta| < 1.8";
      if(plotList_[plot].Contains("EtaR24")) label+="1.8 < |#eta| < 2.4";
      if(plotList_[plot].Contains("PtR50" )) label+="30 < p_{t}[GeV] < 50";
      if(plotList_[plot].Contains("PtR80" )) label+="50 < p_{t}[GeV] < 80";
      if(plotList_[plot].Contains("PtR120")) label+="80 < p_{t}[GeV] < 120";
      if(plotList_[plot].Contains("PtRinf")) label+="p_{t} > 120 GeV";
      DrawLabel(label, 0.6, 0.75, 1.0, 0.85, 12, 0.04);  
    }
    //draw data/MC ratio
    if(histo_[plotList_[plot]].count(kSig)>0){
      int rval = drawRatio(histo_[plotList_[plot]][kData], histo_[plotList_[plot]][kSig], 0.1, 1.9, myStyle, 0);	       
      if (rval!=0) std::cout << " Problem occured for " << plotList_[plot] << std::endl;
    }
    ++canvasNumber;
  }
  // save canvas
  if(save){
    if(verbose>1) std::cout << "saving will be done" << std::endl;
    saveCanvas(plotCanvas_,"./diffXSecFromSignal/plots/combined/2011/monitoring/", "kinFitShiftBqPt", true, false);

  }
}
