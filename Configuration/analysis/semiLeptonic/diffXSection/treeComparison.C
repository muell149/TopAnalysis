#include "basicFunctions.h"

bool isValidsample(unsigned int sample, unsigned int systematicVariation);

void treeComparison(double luminosity = 19712, bool save = true, int verbose=2, TString inputFolderName= "RecentAnalysisRun8TeV_doubleKinFit", TString dataFile= "/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/elecDiffXSecData2012ABCDAll.root:/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/muonDiffXSecData2012ABCDAll.root", const std::string decayChannel = "combined", bool withRatioPlot=true)
{

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

  // default configurations
  unsigned int systematicVariation=sysNo;
  TString ttbarMC="Madgraph";
  bool scaleTtbarToMeasured=true;
  // adjust luminosity and data files for combined control plots
  double luminosityEl=constLumiElec;
  double luminosityMu=constLumiMuon;
  if(!dataFile.Contains(":")){
    std::cout << "wrong input filenames, should be dataFileEl:dataFileMu, but is ";
    std::cout << dataFile << std::endl;
    exit(0);
  }
  TString dataFileEl=getStringEntry(dataFile,1 , ":");
  TString dataFileMu=getStringEntry(dataFile,42, ":");
  // file container
  std::map<unsigned int, TFile*> files_, filesMu_, filesEl_;
  // file vector storage
  std::vector< std::map<unsigned int, TFile*> > fileList_;
  // get analysis files
  TString inputFolder="/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName;
  if(verbose>0) std::cout << "loading files from " << inputFolder << std::endl;
  if(decayChannel!="combined"){
    TString dataFiletemp= decayChannel=="muon" ? dataFileMu : dataFileEl;
    files_ = getStdTopAnalysisFiles(inputFolder, systematicVariation, dataFiletemp, decayChannel, ttbarMC);
    fileList_.push_back(files_);
  }
  else{
    filesMu_ = getStdTopAnalysisFiles(inputFolder, systematicVariation, dataFileMu, "muon"    , ttbarMC);
    filesEl_ = getStdTopAnalysisFiles(inputFolder, systematicVariation, dataFileEl, "electron", ttbarMC);
    fileList_.push_back(filesMu_);
    fileList_.push_back(filesEl_);
  }
  // topPt histogram template
  if(verbose>0) std::cout << "creating temp histo" << std::endl;
  TH1F* temp= (TH1F*)(((TH1F*)(fileList_.at(0)[kSig]->Get("analyzeTopRecoKinematicsKinFit/topPt"))->Clone()));
  temp->Rebin(20);
  temp->Reset("icms");
  temp->SetTitle("");
  temp->GetXaxis()->SetTitle("p_{T}^{t} #left[GeV#right]");
  temp->GetYaxis()->SetTitle("Top quarks");
  //axesStyle(*temp, "p_{T}^{t} #left[GeV#right]", "norm. Top quarks", 0., 0.15);
  temp->GetXaxis()->SetRangeUser(0.,400.);
  //temp->GetYaxis()->SetRangeUser(0.,0.2 );
  temp->SetStats(kFALSE);
  temp->SetLineWidth(3);
  temp->SetMarkerSize(1.25);
  int binMax=temp->GetNbinsX()+1;
  // container for all histos
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  
  // determine number of channels
  unsigned int nchannels = decayChannel=="combined" ? 2 : 1;
  
  // loop decay channels
  if(verbose>0) std::cout << "looping channels" << std::endl;
  for(unsigned int channel=0; channel<nchannels; ++channel){
    std::map<unsigned int, TFile*> tempfiles_=fileList_.at(channel);
    std::string tempChannel= decayChannel!="combined" ? decayChannel : (channel==0 ? "muon" : "electron");
    if(verbose>1) std::cout << " - " << tempChannel << std::endl;
    TString channelExt=getTStringFromInt(channel);
    // loop samples
    for(unsigned int sample=kSig; sample<=kSAToptW; ++sample){
      // check if sample is relevant
      if(isValidsample(sample, systematicVariation)){
	if(verbose>1){
	  std::cout << "  -> processing " << sampleLabel(sample, tempChannel);
	  std::cout << " (file " << tempfiles_[sample]->GetName() << ")" << std::endl;
	}
	// calculate luminosity event weight
	double lumi=decayChannel!="combined" ? luminosity : (channel==0 ? luminosityMu : luminosityEl);
	double lumiwgt=lumiweight(sample, lumi, systematicVariation, tempChannel);
	if(verbose>1) std::cout << "     (lumiweight=" << lumiwgt << ")" << std::endl;
	// get trees
	TTree* tree = (TTree*)(tempfiles_[sample]->Get("analyzeTopRecoKinematicsKinFit/tree"));
	if(!tree) std::cout << "     !WARNING: tree not found, will ignore file and continue!" << std::endl;
	else if(verbose>1)  std::cout << "     (tree found, contains " << tree->GetEntries() << " entries)" << std::endl;
	// container for values read from tree
	std::map< TString, float > value_;
	// initialize map entries with 0 
	value_["weight"  ]=1;
	value_["chi2"    ]=0;
	value_["topPtLep"]=0;
	value_["topPtHad"]=0;
	// initialize branches
	tree->SetBranchStatus ("*", 0);
	tree->SetBranchStatus ("weight"  , 1);
	tree->SetBranchStatus ("topPtLep", 1);
	tree->SetBranchStatus ("topPtHad", 1);
	tree->SetBranchStatus ("chi2"    , 1);
	tree->SetBranchAddress("chi2"    ,(&value_["chi2"    ]));
	tree->SetBranchAddress("weight"  ,(&value_["weight"  ]));
	tree->SetBranchAddress("topPtLep",(&value_["topPtLep"]));
	tree->SetBranchAddress("topPtHad",(&value_["topPtHad"]));
	// initialize result plots
	histo_["topPt"+channelExt     ][sample]=(TH1F*)(temp->Clone());
	histo_["topPtProb1"+channelExt][sample]=(TH1F*)(temp->Clone());
	histo_["topPtProb2"+channelExt][sample]=(TH1F*)(temp->Clone());
	if(verbose>1) std::cout << "     -> looping tree" << std::endl;
	// loop all events to fill plots
	for(unsigned int event=0; event<tree->GetEntries(); ++event){
	  // get event
	  tree->GetEntry(event);
	  // get relevant quantities
	  double weight=value_["weight"]*lumiwgt;
	  double chi2  =value_["chi2"  ];
	  double topPtLep=value_["topPtLep"];
	  double topPtHad=value_["topPtHad"];
	  if(verbose>2){
	    std::cout << "      event #" << event+1 << "/" << tree->GetEntries() << ":" << std::endl;
	    std::cout << "      weight=" << weight << ", chi2=" << chi2 << ", topPtLep=" << topPtLep << ", topPtHad=" << topPtHad << std::endl;
	  }
	  // fill histo for all
	  histo_["topPt"+channelExt][sample]->Fill(topPtLep, weight);
	  histo_["topPt"+channelExt][sample]->Fill(topPtHad, weight);
	  // fill histo for prob>0.02
	  if(chi2<7.824){
	    histo_["topPtProb1"+channelExt][sample]->Fill(topPtLep, weight);
	    histo_["topPtProb1"+channelExt][sample]->Fill(topPtHad, weight);
	  }
	  // fill histo for prob>0.20
	  if(chi2<3.219){
	    histo_["topPtProb2"+channelExt][sample]->Fill(topPtLep, weight);
	    histo_["topPtProb2"+channelExt][sample]->Fill(topPtHad, weight);
	  }
	} // end for loop tree events
      } // end if is valid sample
    } // end for loop samples
  } // end for loop decay channels



  // create final plots
  // -> combine decay channels and MC samples
  unsigned int kAllMC=42;
  // loop samples
  if(verbose>0) std::cout << "combining decay channels and MC samples" << std::endl;
  for(unsigned int sample=kSig; sample<=kSAToptW; ++sample){
    // check if sample is relevant
    if(isValidsample(sample, systematicVariation)){
      // loop decay channels
      for(unsigned int channel=0; channel<nchannels; ++channel){
	std::string tempChannel= decayChannel!="combined" ? decayChannel : (channel==0 ? "muon" : "electron");
	if(verbose>1) std::cout << " -> processing " << sampleLabel(sample, tempChannel) << "(" << tempChannel << ")" << std::endl;
	TString channelExt=getTStringFromInt(channel);
	// get plots for current channels
	TH1F* tempHist1=(TH1F*)histo_["topPt"+channelExt     ][sample]->Clone();
	TH1F* tempHist2=(TH1F*)histo_["topPtProb1"+channelExt][sample]->Clone();
	TH1F* tempHist3=(TH1F*)histo_["topPtProb2"+channelExt][sample]->Clone();
	double nevents1=tempHist1->Integral(0,binMax);
	double nevents2=tempHist2->Integral(0,binMax);
	double nevents3=tempHist3->Integral(0,binMax);

	// add all channels for final histogram
	if(channel==0){
	  histo_["topPt"     ][sample]=(TH1F*)tempHist1->Clone();
	  histo_["topPtProb1"][sample]=(TH1F*)tempHist2->Clone();
	  histo_["topPtProb2"][sample]=(TH1F*)tempHist3->Clone();
	}
	else{
	  histo_["topPt"     ][sample]->Add((TH1F*)tempHist1->Clone());
	  histo_["topPtProb1"][sample]->Add((TH1F*)tempHist2->Clone());
	  histo_["topPtProb2"][sample]->Add((TH1F*)tempHist3->Clone());
	}
	if(verbose>2) std::cout << "    (#events(" << tempChannel << ")=" <<  nevents1 << " / " << nevents2 << " / " << nevents3 << ")" << std::endl;
      } // end channel for loop 
      double neventsComb1=histo_["topPt"     ][sample]->Integral(0,binMax);
      double neventsComb2=histo_["topPtProb1"][sample]->Integral(0,binMax);
      double neventsComb3=histo_["topPtProb2"][sample]->Integral(0,binMax);
      if(verbose>1) std::cout << "    (#events=" <<  neventsComb1 << " / " << neventsComb2 << " / " << neventsComb3 << ")" << std::endl;
      // combine all MC samples
      if(sample!=kData){
	if(sample==kSig){
	  histo_["topPt"     ][kAllMC]=(TH1F*)histo_["topPt"     ][sample]->Clone();
	  histo_["topPtProb1"][kAllMC]=(TH1F*)histo_["topPtProb1"][sample]->Clone();
	  histo_["topPtProb2"][kAllMC]=(TH1F*)histo_["topPtProb2"][sample]->Clone();
	}
	else{
	  histo_["topPt"     ][kAllMC]->Add((TH1F*)histo_["topPt"     ][sample]->Clone());
	  histo_["topPtProb1"][kAllMC]->Add((TH1F*)histo_["topPtProb1"][sample]->Clone());
	  histo_["topPtProb2"][kAllMC]->Add((TH1F*)histo_["topPtProb2"][sample]->Clone());
	  // MC stack creation
	}
	// MC histogram style
	histogramStyle(*histo_["topPt"     ][sample], sample, true);
	histogramStyle(*histo_["topPtProb1"][sample], sample, true);
	histogramStyle(*histo_["topPtProb2"][sample], sample, true);	
      }
      else{
	// data histogram style
	histogramStyle(*histo_["topPt"     ][sample], kData, false);
	histogramStyle(*histo_["topPtProb1"][sample], kData, false);
	histogramStyle(*histo_["topPtProb2"][sample], kData, false);
      }
    } // end if sample is valid
  } // end sample for loop

  // print some interesting numbers
  double neventsMC1=histo_["topPt"     ][kAllMC]->Integral(0,binMax);
  double neventsMC2=histo_["topPtProb1"][kAllMC]->Integral(0,binMax);
  double neventsMC3=histo_["topPtProb2"][kAllMC]->Integral(0,binMax);
  if(verbose>0) std::cout << "#events( MC )=" <<  neventsMC1 << " / " << neventsMC2 << " / " << neventsMC3 << ")" << std::endl;
  double neventsData1=histo_["topPt"     ][kData]->Integral(0,binMax);
  double neventsData2=histo_["topPtProb1"][kData]->Integral(0,binMax);
  double neventsData3=histo_["topPtProb2"][kData]->Integral(0,binMax);
  if(verbose>0) std::cout << "#events(Data)=" <<  neventsData1 << " / " << neventsData2 << " / " << neventsData3 << ")" << std::endl;
  if(verbose>0) std::cout << "data/MC ratio=" <<  neventsData1/neventsMC1 << " / " << neventsData2/neventsMC2 << " / " << neventsData3/neventsMC3 << ")" << std::endl;

  // sacale ttbar to match total number of events
  if(scaleTtbarToMeasured){
    if(verbose>0) std::cout << "scale ttbar component to match #data events " << std::endl;
    double neventsTop1=histo_["topPt"     ][kSig]->Integral(0,binMax)+histo_["topPt"     ][kBkg]->Integral(0,binMax);
    double neventsTop2=histo_["topPtProb1"][kSig]->Integral(0,binMax)+histo_["topPtProb1"][kBkg]->Integral(0,binMax);
    double neventsTop3=histo_["topPtProb2"][kSig]->Integral(0,binMax)+histo_["topPtProb2"][kBkg]->Integral(0,binMax);
    double SFTop1=(neventsTop1+(neventsData1-neventsMC1))/neventsTop1;
    double SFTop2=(neventsTop2+(neventsData2-neventsMC2))/neventsTop2;
    double SFTop3=(neventsTop3+(neventsData3-neventsMC3))/neventsTop3;
    // scale top plots
    histo_["topPt"     ][kSig]->Scale(SFTop1);
    histo_["topPtProb1"][kSig]->Scale(SFTop2);
    histo_["topPtProb2"][kSig]->Scale(SFTop3);
    histo_["topPt"     ][kBkg]->Scale(SFTop1);
    histo_["topPtProb1"][kBkg]->Scale(SFTop2);
    histo_["topPtProb2"][kBkg]->Scale(SFTop3);
    // scale combined MC plots
    histo_["topPt"     ][kAllMC]->Add(histo_["topPt"     ][kSig] , SFTop1-1.);
    histo_["topPtProb1"][kAllMC]->Add(histo_["topPtProb1"][kSig] , SFTop2-1.);
    histo_["topPtProb2"][kAllMC]->Add(histo_["topPtProb2"][kSig] , SFTop3-1.);
    histo_["topPt"     ][kAllMC]->Add(histo_["topPt"     ][kBkg] , SFTop1-1.);
    histo_["topPtProb1"][kAllMC]->Add(histo_["topPtProb1"][kBkg] , SFTop2-1.);
    histo_["topPtProb2"][kAllMC]->Add(histo_["topPtProb2"][kBkg] , SFTop3-1.);
    double neventsMCscaled1=histo_["topPt"     ][kAllMC]->Integral(0,binMax);
    double neventsMCscaled2=histo_["topPtProb1"][kAllMC]->Integral(0,binMax);
    double neventsMCscaled3=histo_["topPtProb2"][kAllMC]->Integral(0,binMax);
    if(verbose>1) std::cout << "data/MC ratio=" <<  neventsData1/neventsMCscaled1 << " / " << neventsData2/neventsMCscaled2 << " / " << neventsData3/neventsMCscaled3 << ")" << std::endl;
  };

  // all MC histogram style
  histo_["topPt"     ][kAllMC]->SetLineColor(kBlue);
  histo_["topPt"     ][kAllMC]->SetMarkerColor(kBlue);
  histo_["topPt"     ][kAllMC]->SetLineStyle(1);
  histo_["topPtProb1"][kAllMC]->SetLineColor(kBlue);
  histo_["topPtProb1"][kAllMC]->SetMarkerColor(kBlue);
  histo_["topPtProb1"][kAllMC]->SetLineStyle(1);
  histo_["topPtProb2"][kAllMC]->SetLineColor(kBlue);
  histo_["topPtProb2"][kAllMC]->SetMarkerColor(kBlue);
  histo_["topPtProb2"][kAllMC]->SetLineStyle(1);
  
  std::vector<double> zeroerr_;
  for(int bin=0; bin<histo_["topPt"][kAllMC]->GetNbinsX(); ++bin) zeroerr_.push_back(0);

  // normalization
  // -> not done at the moment

  //  Create canvas
  if(verbose>0)  std::cout << "creating canvas" << std::endl;
  std::vector<TCanvas*> plotCanvas_;
  for(unsigned int sample=0; sample<3; sample++){
    addCanvas(plotCanvas_);
  }

  // create legend
  if(verbose>0)  std::cout << "creating legend" << std::endl;
  TLegend *leg= new TLegend(0.73, 0.69, 0.91, 0.88);
  legendStyle(*leg,"");
  TLegend *leg2=(TLegend*)leg->Clone(); 
  TLegend *leg3=(TLegend*)leg->Clone(); 
  leg ->SetHeader("KinFit, all");
  leg2->SetHeader("prob>0.02");
  leg3->SetHeader("prob>0.20");
  leg ->AddEntry(histo_["topPt"     ][kData ], "data"   , "LP");
  leg ->AddEntry(histo_["topPt"     ][kAllMC], "all MC" , "L");
  leg2->AddEntry(histo_["topPtProb1"][kData ], "data"   , "LP");
  leg2->AddEntry(histo_["topPtProb1"][kAllMC], "all MC" , "L");
  leg3->AddEntry(histo_["topPtProb2"][kData ], "data"   , "LP");
  leg3->AddEntry(histo_["topPtProb2"][kAllMC], "all MC" , "L");

  int canvasNumber=0;
  // KinFit
  if(verbose>0)  std::cout << "plotting " << std::endl;
  plotCanvas_[canvasNumber]->cd(0);
  plotCanvas_[canvasNumber]->SetTitle("topPtKinFit");
  // drawing
  // axis
  //temp->Draw("axis");
  // plots
  histo_["topPt"][kData ]->SetMaximum(1.2*histo_["topPt"][kData ]->GetMaximum());
  histo_["topPt"][kData ]->GetXaxis()->SetNoExponent(true);
  histo_["topPt"][kData ]->GetYaxis()->SetNoExponent(true);
  histo_["topPt"][kData ]->Draw("axis");
  histo_["topPt"][kAllMC]->Draw("hist same");
  histo_["topPt"][kData ]->Draw("ep same");
  // legend
  leg->Draw("same");
  // add labels for decay channel, luminosity, energy and CMS preliminary (if applicable)
  if      (decayChannel=="muon"    ) DrawDecayChLabel("#mu + Jets");
  else if (decayChannel=="electron") DrawDecayChLabel("e + Jets");
  else                               DrawDecayChLabel("e/#mu + Jets Combined");  
  DrawCMSLabels(true,luminosity);
  // draw ratio
  if(withRatioPlot){
    std::vector<double> err_;
    for(int bin=1; bin<histo_["topPt"][kAllMC]->GetNbinsX(); ++bin){
      double val=histo_["topPt"][kData]->GetBinContent(bin)/histo_["topPt"][kAllMC]->GetBinContent(bin)*histo_["topPt"][kData]->GetBinError(bin)/histo_["topPt"][kData]->GetBinContent(bin);    
      if(val<0||val>histo_["topPt"][kData]->GetBinContent(bin)) val=1.;
      err_.push_back(val);
    }
    int rval1 = drawRatio(histo_["topPt"][kData], histo_["topPt"][kAllMC], 0.7, 1.3, myStyle, verbose, err_, "N(data)", "N(MC)", "p e", kBlack, true, 1.2);
    if (rval1!=0) std::cout << " Problem occured when creating ratio plot for " << "KinFit" << std::endl;
  }
  canvasNumber++;

  // prob>0.02
  plotCanvas_[canvasNumber]->cd(0);
  plotCanvas_[canvasNumber]->SetTitle("topPtProb01");
  // drawing
  // axis
  temp->Draw("axis");
  // plots
  histo_["topPtProb1"][kData ]->SetMaximum(1.2*histo_["topPtProb1"][kData ]->GetMaximum());
  histo_["topPtProb1"][kData ]->GetXaxis()->SetNoExponent(true);
  histo_["topPtProb1"][kData ]->GetYaxis()->SetNoExponent(true);
  histo_["topPtProb1"][kData ]->Draw("axis");
  histo_["topPtProb1"][kAllMC]->Draw("hist same");
  histo_["topPtProb1"][kData ]->Draw("ep same");
  // legend
  leg2->Draw("same");
  // add labels for decay channel, luminosity, energy and CMS preliminary (if applicable)
  if      (decayChannel=="muon"    ) DrawDecayChLabel("#mu + Jets");
  else if (decayChannel=="electron") DrawDecayChLabel("e + Jets");
  else                               DrawDecayChLabel("e/#mu + Jets Combined");  
  DrawCMSLabels(true,luminosity);
  // draw ratio
  if(withRatioPlot){
    std::vector<double> err_;
    for(int bin=1; bin<histo_["topPtProb1"][kAllMC]->GetNbinsX(); ++bin){
      double val=histo_["topPtProb1"][kData]->GetBinContent(bin)/histo_["topPtProb1"][kAllMC]->GetBinContent(bin)*histo_["topPtProb1"][kData]->GetBinError(bin)/histo_["topPtProb1"][kData]->GetBinContent(bin);    
      if(val<0||val>histo_["topPtProb1"][kData]->GetBinContent(bin)) val=1.;
      err_.push_back(val);
    }
    int rval1 = drawRatio(histo_["topPtProb1"][kData], histo_["topPtProb1"][kAllMC], 0.7, 1.3, myStyle, verbose, err_, "N(data)", "N(MC)", "p e", kBlack, true, 1.2);
    if (rval1!=0) std::cout << " Problem occured when creating ratio plot for " << "KinFit" << std::endl;
  }
  canvasNumber++;

  // prob>0.20
  plotCanvas_[canvasNumber]->cd(0);
  plotCanvas_[canvasNumber]->SetTitle("topPtProb02");
  // drawing
  // axis
  temp->Draw("axis");
  // plots
  histo_["topPtProb2"][kData ]->SetMaximum(1.2*histo_["topPtProb2"][kData ]->GetMaximum());
  histo_["topPtProb2"][kData ]->GetXaxis()->SetNoExponent(true);
  histo_["topPtProb2"][kData ]->GetYaxis()->SetNoExponent(true);
  histo_["topPtProb2"][kData ]->Draw("axis");
  histo_["topPtProb2"][kAllMC]->Draw("hist same");
  histo_["topPtProb2"][kData ]->Draw("ep same");
  // legend
  leg3->Draw("same");
  // add labels for decay channel, luminosity, energy and CMS preliminary (if applicable)
  if      (decayChannel=="muon"    ) DrawDecayChLabel("#mu + Jets");
  else if (decayChannel=="electron") DrawDecayChLabel("e + Jets");
  else                               DrawDecayChLabel("e/#mu + Jets Combined");  
  DrawCMSLabels(true,luminosity);
  // draw ratio
  if(withRatioPlot){
    std::vector<double> err_;
    for(int bin=1; bin<histo_["topPtProb2"][kAllMC]->GetNbinsX(); ++bin){
      double val=histo_["topPtProb2"][kData]->GetBinContent(bin)/histo_["topPtProb2"][kAllMC]->GetBinContent(bin)*histo_["topPtProb2"][kData]->GetBinError(bin)/histo_["topPtProb2"][kData]->GetBinContent(bin);    
      if(val<0||val>histo_["topPtProb2"][kData]->GetBinContent(bin)) val=1.;
      err_.push_back(val);
    }
    int rval1 = drawRatio(histo_["topPtProb2"][kData], histo_["topPtProb2"][kAllMC], 0.7, 1.3, myStyle, verbose, err_, "N(data)", "N(MC)", "p e", kBlack, true, 1.2);
    if (rval1!=0) std::cout << " Problem occured when creating ratio plot for " << "KinFit" << std::endl;
  }
  canvasNumber++;

  if(verbose>0) std::cout << "do saving" << std::endl;
  if(save){
    // eps and png
    if(verbose==0) gErrorIgnoreLevel=kWarning;
    saveCanvas(plotCanvas_, "./", "topPtProbabilityTest", true, true, true);
  }
}

bool isValidsample(unsigned int sample, unsigned int systematicVariation){
  // exclude combined samples as they contain no tree
  // and ENDOFENUMs as they represent no sample
  if(sample==kQCD||sample==kSTop||sample==kDiBos||sample==ENDOFSAMPLEENUM||sample==ENDOFSAMPLEENUM2) return false;
  // exclude all QCD samples (statistical fluctuations)
  if(sample>=kQCDEM1&&sample<=kQCDBCE3  ) return false;
  // exclude systematic signal samples
  if(sample>=kSigPow&&sample<=kBkgPowHer) return false;
  // excude splitted single top samples for non scale variation
  if(!(systematicVariation==sysSingleTopScaleUp||systematicVariation==sysSingleTopScaleDown)&&sample>=kSToptW1&&sample<=kSAToptW3) return false;
  return true;
}
