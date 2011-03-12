#include "basicFunctions.h"

void analyzeHypothesisKinFit(double luminosity = 35.9, bool save = true, int systematicVariation=sysNo, TString dataFile= "./diffXSecFromSignal/analysisRootFilesWithKinFit/muonDiffXSec2010Data36pbNov4ReRecoNov12Json.root")
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
     20:sysQCDup         21:sysQCDdown
  */
  // save: save plots?
  // data file: relative path of .root file
  // luminosity: [/nb]
  TString lumi = getTStringFromInt(roundToInt((luminosity), false));
  // b) options to be configured only once
  // get the .root files from the following folder:
  TString inputFolder = "./diffXSecFromSignal/analysisRootFilesWithKinFit";
  // save all plots into the following folder
  TString outputFolder = "./diffXSecFromSignal/plots/kinFit/";
  // choose name of the output .pdf file
  TString pdfName="kinFitpbHypothesis"+lumi+"pb";
  // set detail level of output 
  // 0: no output, 1: std output 2: output for debugging
  unsigned int verbose=2;
  // c) set root style
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetEndErrorSize (8);
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
                         "analyzeTopRecoKinematicsKinFit/topWAngle"  ,
                         "analyzeTopRecoKinematicsKinFit/topPtHad_"  ,
                         "analyzeTopRecoKinematicsKinFit/topPhiHad_" ,
                         "analyzeTopRecoKinematicsKinFit/topYHad_"   ,
                         "analyzeTopRecoKinematicsKinFit/topPtLep_"  ,
                         "analyzeTopRecoKinematicsKinFit/topPhiLep_" ,
                         "analyzeTopRecoKinematicsKinFit/topYLep_"   ,
                         "analyzeTopRecoKinematicsKinFit/bbbarAngle" ,
			 // generated top quantities
                         "analyzeTopGenLevelKinematics/topMass"      , 
                         "analyzeTopGenLevelKinematics/topPt"        ,                         
                         "analyzeTopGenLevelKinematics/topPhi"       ,
                         "analyzeTopGenLevelKinematics/topY"         ,
                         "analyzeTopGenLevelKinematics/topWAngle"    ,
                         "analyzeTopGenLevelKinematics/topPtHad_"    ,
                         "analyzeTopGenLevelKinematics/topPhiHad_"   ,
                         "analyzeTopGenLevelKinematics/topYHad_"     ,
                         "analyzeTopGenLevelKinematics/topPtLep_"    ,
                         "analyzeTopGenLevelKinematics/topPhiLep_"   ,
                         "analyzeTopGenLevelKinematics/topYLep_"     ,
			 "analyzeTopGenLevelKinematics/bbbarAngle"   ,
			 // reconstructed ttbar quantities
                         "analyzeTopRecoKinematicsKinFit/ttbarMass"  ,
                         "analyzeTopRecoKinematicsKinFit/ttbarPt"    ,
                         "analyzeTopRecoKinematicsKinFit/ttbarY"     ,
                         "analyzeTopRecoKinematicsKinFit/ttbarHT"    ,
                         "analyzeTopRecoKinematicsKinFit/ttbarSumY"  ,
			 "analyzeTopRecoKinematicsKinFit/ttbarDelPhi",
			 "analyzeTopRecoKinematicsKinFit/ttbarDelY"  
                       };
  TString plots2D[ ] = { // reco - gen Match correlation plots (ttbar signal only)
                         // a) combinatorics and Kinfit Hypothesis Quality(ttbar signal only)
                         "analyzeHypoKinFit/mapKinFit_"                      ,
			 // b) reconstructed Top quantities
			 "analyzeTopRecoKinematicsKinFitMatched/topPt_"      ,
			 "analyzeTopRecoKinematicsKinFitMatched/topPhi_"     ,
			 "analyzeTopRecoKinematicsKinFitMatched/topY_"       ,
			 "analyzeTopRecoKinematicsKinFitMatched/topWAngle_"  ,
                         "analyzeTopRecoKinematicsKinFitMatched/bbbarAngle_" ,
                         // c) reconstructed ttbar quantities
			 "analyzeTopRecoKinematicsKinFitMatched/ttbarMass_"  ,
                         "analyzeTopRecoKinematicsKinFitMatched/ttbarPt_"    ,
                         "analyzeTopRecoKinematicsKinFitMatched/ttbarY_"     ,
                         "analyzeTopRecoKinematicsKinFitMatched/ttbarHT_"    ,
                         "analyzeTopRecoKinematicsKinFitMatched/ttbarSumY_"  ,
			 "analyzeTopRecoKinematicsKinFitMatched/ttbarDelPhi_",
			 "analyzeTopRecoKinematicsKinFitMatched/ttbarDelY_"  
                       };

  // b) list plot axes style
  // 1D: "x-axis title"/"y-axis title"/log
  // log = 0 or 1 for linear or logarithmic axis 

  TString axisLabel1D[ ] = { // general fit performance
                             "probability (best fit hypothesis)/events/0"                   , 
			     "#chi^{2} (best fit hypothesis)/events/0"                      ,
			     "#Delta#chi^{2} (1^{st} - 2^{nd} best fit hypothesis)/events/0",
			     // combinatorics and Kinfit Hypothesis Quality(ttbar signal only)
			     "#Deltai_{lead jet}(genMatch - kinFit), hadronic b-quark/events/0", 
			     "#Deltai_{lead jet}(genMatch - kinFit), leptonic b-quark/events/0", 
			     "#Deltai_{lead jet}(genMatch - kinFit), light quarks/events/0"    , 
			     "N(wrong assigned jets)/events/0"                                 , 
			     // pull distributions
			     "(p_{t gen}-p_{t reco}) #sigmap_{t}^{-1} (hadronic b-quark)/events/0"  ,
			     "(#eta_{gen}-#eta_{reco}) #sigma#eta^{-1} (hadronic b-quark)/events/0" ,
			     "(#phi_{gen}-#phi_{reco}) #sigma#phi^{-1} (hadronic b-quark)/events/0" ,
			     "(p_{t gen}-p_{t reco}) #sigmap_{t}^{-1} (leptonic b-quark)/events/0"  ,
			     "(#eta_{gen}-#eta_{reco}) #sigma#eta^{-1} (leptonic b-quark)/events/0" ,
			     "(#phi_{gen}-#phi_{reco}) #sigma#phi^{-1} (leptonic b-quark)/events/0" ,
			     "(p_{t gen}-p_{t reco}) #sigmap_{t}^{-1} (light quark)/events/0"       ,
			     "(#eta_{gen}-#eta_{reco}) #sigma#eta^{-1} (light quark)/events/0"      ,
			     "(#phi_{gen}-#phi_{reco}) #sigma#phi^{-1} (light quark)/events/0"      ,
			     "(p_{t gen}-p_{t reco}) #sigmap_{t}^{-1} (lepton)/events/0"            ,
			     "(#eta_{gen}-#eta_{reco}) #sigma#eta^{-1} (lepton)/events/0"           ,
			     "(#phi_{gen}-#phi_{reco}) #sigma#phi^{-1} (lepton)/events/0"           ,
			     "(p_{t gen}-p_{t reco}) #sigmap_{t}^{-1} (neutrino)/events/0"          ,
			     "(#eta_{gen}-#eta_{reco}) #sigma#eta^{-1} (neutrino)/events/0"         ,
			     "(#phi_{gen}-#phi_{reco}) #sigma#phi^{-1} (neutrino)/events/0"         ,
			     "(p_{t reco}-p_{t gen}) p_{t gen}^{-1} (leptonic W)/events/0"          ,
			     "(#eta_{reco}-#eta_{gen}) #eta_{gen}^{-1} (leptonic W)/events/0"       ,
			     "(#phi_{reco}-#phi_{gen}) #phi_{gen}^{-1} (leptonic W)/events/0"       ,
			     "(p_{t reco}-p_{t gen}) p_{t gen}^{-1} (hadronic W)/events/0"          ,
			     "(#eta_{reco}-#eta_{gen}) #eta_{gen}^{-1} (hadronic W)/events/0"       ,
			     "(#phi_{reco}-#phi_{gen}) #phi_{gen}^{-1} (hadronic W)/events/0"       ,
			     // reconstructed Top quantities
                             "m_{t} Kinfit [GeV]/events/0"        ,
                             "p_{t}(t) Kinfit [GeV]/events/0"     ,
                             "#phi(t) Kinfit/events/0"            ,
                             "y(t) Kinfit/events/0"               ,
                             "angle(t,W) Kinfit (top rest frame)/events/0",     
                             "p_{t}(hadronic t) Kinfit [GeV]/events/0",                         
                             "#phi(hadronic t) Kinfit/events/0"   ,
                             "y(hadronic t) Kinfit/events/0"      ,
                             "p_{t}(leptonic t) Kinfit [GeV]/events/0",                         
                             "#phi(leptonic t) Kinfit/events/0"   ,
                             "y(leptonic t) Kinfit/events/0"      ,
			     "angle(b,#bar{b}) Kinfit (t#bar{t} rest frame)/events/0",
			     // generated top quantities
                             "m_{t} gen truth [GeV]/events/0"      ,
                             "p_{t}(t) gen truth/events/0"         ,
                             "#phi(t) gen truth/events/0"          ,
                             "y(t) gen truth/events/0"             ,
                             "angle(t,W) gen truth (top rest frame)/events/0",     
                             "p_{t}(hadronic t) gen truth/events/0",                         
                             "#phi(hadronic t) gen truth/events/0" ,
                             "y(hadronic t) gen truth/events/0"    ,
                             "p_{t}(leptonic t) gen truth/events/0",                         
                             "#phi(leptonic t) gen truth/events/0" ,
                             "y(leptonic t) gen truth/events/0"    ,
			     "angle(b,#bar{b}) gen truth (t#bar{t} rest frame)/events/0",
			     // reconstructed ttbar quantities	                            
                             "m(t#bar{t})Kinfit/events/0"                       ,
                             "p_{t}(t#bar{t})Kinfit/events/0"                   ,
                             "y(t#bar{t}) Kinfit/events/0"                      ,
                             "H_{T}(t#bar{t}) Kinfit/events/0"                  ,
                             "#Sigmay(t#bar{t}) Kinfit/events/0"                ,
                             "#phi(leptonic t)-#phi(hadronic t) Kinfit/events/0",                
                             "y(leptonic t)-y(hadronic t) Kinfit/events/0"           
                           };
  // 2D: "x-axis title"/"y-axis title"
  TString axisLabel2D[ ] = {// reco - gen Match correlation plots (ttbar signal only)
                            // a) combinatorics and Kinfit Hypothesis Quality(ttbar signal only)
                            "i_{lead jet} gen truth/i_{lead jet} hypothesis fit",
			    // b) reconstructed Top quantities
                            "p_{t}(t) matched/p_{t}(t) reco"                    ,
			    "#phi(t) matched/#phi(t) reco"                      ,
                            "y(t) matched/y(t) reco"                            ,
			    "angle(t,W) matched (top rest frame)/angle (top,W) reco (top rest frame)",
			    "angle(b,#bar{b}) matched (t#bar{t} rest frame)/angle(b,#bar{b}) reco (t#bar{t} rest frame)",
                            // c) reconstructed ttbar quantities
                            "m(t#bar{t}) matched/m(t#bar{t}) reco"              ,
                            "p_{t}(t#bar{t}) matched/p_{t}(t#bar{t})reco"       ,
                            "y(t#bar{t}) matched/y(t#bar{t}) reco"              ,
                            "H_{T}(t#bar{t}) matched/H_{T}(t#bar{t}) reco"      ,
                            "#Sigmay(t#bar{t}) matched/ reco"                   ,
                            "#phi(leptonic t)-#phi(hadronic t) matched/#phi(leptonic t)-#phi(hadronic t) Kinfit",
                            "y(leptonic t)-y(hadronic t) matched/y(leptonic t)-y(hadronic t) Kinfit"            
                           };
  // count # plots
  unsigned int N1Dplots = sizeof(plots1D)/sizeof(TString);
  unsigned int N2Dplots = sizeof(plots2D)/sizeof(TString);
  // check if all axis labels exist
  if(N1Dplots != sizeof(axisLabel1D)/sizeof(TString)) std::cout << "ERROR: some 1D plots or axis label are missing" << std::endl;
  if(N2Dplots != sizeof(axisLabel2D)/sizeof(TString)) std::cout << "ERROR: some 2D plots or axis label are missing" << std::endl;
  if((N1Dplots != sizeof(axisLabel1D)/sizeof(TString))||(N2Dplots != sizeof(axisLabel2D)/sizeof(TString))) exit (1);

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
  //    change 1D plots into stack plots
  // ---
  // loop plots -> all 1D plots will become stacked plots
  if(verbose>1) std::cout << std::endl;
  for(unsigned int plot=0; plot<plotList_.size(); ++plot){
    createStackPlot(plotList_, histo_, plot, N1Dplots, verbose);
  }
  if(verbose>1) std::cout << std::endl;

  // ---
  //    configure histograms
  // ---
  // needs: plotList_, histo_, histo2_, N1Dplots, axisLabel_, axisLabel1D, axisLabel2D
  std::vector<TString> axisLabel_;
  axisLabel_.insert( axisLabel_.begin(), axisLabel1D, axisLabel1D + sizeof(axisLabel1D)/sizeof(TString) );
  axisLabel_.insert( axisLabel_.end()  , axisLabel2D, axisLabel2D + sizeof(axisLabel2D)/sizeof(TString) );
  if(verbose>1){
    std::cout << "(plot, x Axis label , y Axis label , log scale?):" << std::endl;
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      std::cout << plotList_[plot] << ": " << getStringEntry(axisLabel_[plot],1);
      std::cout << " , " << getStringEntry(axisLabel_[plot], 2);
      if(plot<N1Dplots) std::cout<< " , " << getStringEntry(axisLabel_[plot], 3);
      std::cout << std::endl;
    }
  }
  // loop samples
  for(unsigned int sample=kSig; sample<=kData; ++sample){
    // loop plots
    for(unsigned int plot=0; plot<plotList_.size(); ++plot){
      // a) 1D
      if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)) histogramStyle( *histo_[plotList_[plot]][sample], sample, true );
      // b) 2D
      if((plot>=N1Dplots)&&(histo2_.count(plotList_[plot])>0)&&(histo2_[plotList_[plot]].count(sample)>0)) histStyle2D( *histo2_[plotList_[plot]][sample], sampleLabel(sample), getStringEntry(axisLabel_[plot],1), getStringEntry(axisLabel_[plot],2));
    }
  }

  // ---
  //    create one legend for all 1D histos
  // ---
  int Nlegends=0;  
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
	if(sample==kData) leg0->AddEntry(histo_[plotList_[plot]][sample], sampleLabel(sample)+", "+lumi+" pb^{-1}", "PL");
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
  int NCanvas = Nplots+Nlegends;
  // a) create canvas for all plots + legends
  for(int sample=0; sample<NCanvas; sample++){
    char canvname[10];
    sprintf(canvname,"canv%i",sample);    
    plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*plotCanvas_[sample]);
  }

  // ---
  //    rebinning histograms
  // ---
  // loop samples
  for(unsigned int sample=kSig; sample<=kData; ++sample){
    // 1) for 1D plots
    // check if plot exists- change binning
    if((histo_.count("analyzeTopRecoKinematicsKinFit/prob")>0)&&(histo_["analyzeTopRecoKinematicsKinFit/prob"].count(sample)>0)){
      histo_["analyzeTopRecoKinematicsKinFit/prob"][sample]->Rebin(5);
    }
    if((histo_.count("analyzeTopRecoKinematicsKinFit/chi2")>0)&&(histo_["analyzeTopRecoKinematicsKinFit/chi2"].count(sample)>0)){
      histo_["analyzeTopRecoKinematicsKinFit/chi2"][sample]->Rebin(5);
    }
    if((histo_.count("analyzeTopRecoKinematicsKinFit/delChi2")>0)&&(histo_["analyzeTopRecoKinematicsKinFit/delChi2"].count(sample)>0)){
      histo_["analyzeTopRecoKinematicsKinFit/delChi2"][sample]->Rebin(5);
    }
    if((histo_.count("analyzeTopRecoKinematicsKinFit/bbbarAngle")>0)&&(histo_["analyzeTopRecoKinematicsKinFit/bbbarAngle"].count(sample)>0)){
      histo_["analyzeTopRecoKinematicsKinFit/bbbarAngle"][sample]->Rebin(2);
    }
    if((histo_.count("analyzeTopRecoKinematicsKinFit/topMass")>0)&&(histo_["analyzeTopRecoKinematicsKinFit/topMass"].count(sample)>0)){
      histo_["analyzeTopRecoKinematicsKinFit/topMass"][sample]->Rebin(40);
      if(sample==kData) std::cout << "entries in data top mass 160 - 180 GeV: " << histo_["analyzeTopRecoKinematicsKinFit/topMass"][sample]->GetBinContent(4) << std::endl;
    }
  }

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
      // a1) for 1D plots (existing)
      if(plot<N1Dplots){
	// check if plot is existing
	if((histo_.count(plotList_[plot])>0)&&(histo_[plotList_[plot]].count(sample)>0)){
	  if(verbose>0){
	    std::cout << "plotting " << plotList_[plot];
	    std::cout << " from sample " << sampleLabel(sample);
	    std::cout << " to canvas " << canvasNumber << " ( ";
	    std::cout << plotCanvas_[canvasNumber]->GetTitle() << " )" << std::endl;
	  }
	  // first plot
	  if(first){
	    // min / max
	    double max = 1.3*histo_[plotList_[plot]][sample]->GetMaximum();
	    // if data file exists
	    if(histo_[plotList_[plot]].count(kData)>0){
	      std::cout << "data file found" << std::endl;
	      // and has larger maximum
	      if(max < 1.3*histo_[plotList_[plot]][kData]->GetMaximum()){
		std::cout << "max: ";
		// take this maximum
		max = 1.3*histo_[plotList_[plot]][kData]->GetMaximum();
		std::cout << 1.3*histo_[plotList_[plot]][sample]->GetMaximum() << " -> " << max << std::endl;
	      }
	    }
	    double min = 0;
	    // log plots
	    if(getStringEntry(axisLabel_[plot],3)=="1"){
	      plotCanvas_[canvasNumber]->SetLogy(1);
	      min=1;
	      max=exp(1.3*(std::log(max)-std::log(min))+std::log(min));
	    }
	    max = (double)roundToInt(max);
	    // axes and drawing
	    axesStyle(*histo_[plotList_[plot]][sample], getStringEntry(axisLabel_[plot],1), getStringEntry(axisLabel_[plot],2), min, max);
	    histo_[plotList_[plot]][sample]->Draw("");
	    histo_[plotList_[plot]][42] = (TH1F*)(histo_[plotList_[plot]][sample]->Clone());
	  }
	  // draw other plots into same canvas, draw data as points
	  else{ 
	    if(sample!=kData) histo_[plotList_[plot]][sample]->Draw("same");
	    if(sample==kData) histo_[plotList_[plot]][sample]->Draw("p e X0 same");
	  }
	  first=false;
	}
	// redraw axis at the end
	if((histo_.count(plotList_[plot])>0)&&(sample==kData)) histo_[plotList_[plot]][42]->Draw("axis same");
      }
      // a2) for 2D plots
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
      }
    }
    // for 1D hists: next canvas
    if((plot<N1Dplots)&&(histo_.count(plotList_[plot])>0)) ++canvasNumber;
  }
  // b) for legends
  plotCanvas_[canvasNumber]->cd(0);
  plotCanvas_[canvasNumber]->SetTitle("legendHypoKinFit");
  leg0->Draw("");
  ++canvasNumber;

  // ---
  // saving
  // ---
  if(save) saveCanvas(plotCanvas_, outputFolder, pdfName);
}
