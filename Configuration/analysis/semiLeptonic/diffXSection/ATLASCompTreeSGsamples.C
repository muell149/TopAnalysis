#include "basicFunctions.h"

std::map<TString, std::vector<double> > makeVariableBinningA(int binning=1);
bool PythiaSample (unsigned int s);

unsigned int kMad    =0;
unsigned int kPow    =1;
unsigned int kPowHer =2;
unsigned int kMca    =3;
unsigned int kAlp    =4;
unsigned int kPowA   =5;
unsigned int kPowHerA=6;
unsigned int kMcaA   =7;

void ATLASCompTreeSGsamples(bool save = true, int verbose=0){
  int binning=2; //0:fine binning, 1:ATLAS, 2:CMS
  bool debug  = true ;
  bool debug2 = false;

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
  //file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/combinedDiffXSecSigFall11PFLarge.root"                                        , "Open"));
  file_.push_back(TFile::Open("/afs/cern.ch/work/i/iasincru/public/TopLHCWG_DiffXSex_CMS/MC_theory_samples/CMSttbarMadGraphZ2Pythia6CTEQ6L1Fall11MCProductionCycle.root", "Open"));
  file_.push_back(TFile::Open("/afs/cern.ch/work/i/iasincru/public/TopLHCWG_DiffXSex_CMS/MC_theory_samples/CMSttbarPowhegZ2Pythia6CTEQ6MFall11MCProductionCycle.root"   , "Open"));
  file_.push_back(TFile::Open("/afs/cern.ch/work/i/iasincru/public/TopLHCWG_DiffXSex_CMS/MC_theory_samples/CMSttbarPowhegAUET2Herwig6CTEQ6MFall11MCProductionCycle.root", "Open"));
  file_.push_back(TFile::Open("/afs/cern.ch/work/i/iasincru/public/TopLHCWG_DiffXSex_CMS/MC_theory_samples/CMSttbarMC@NLOHerwig6CTEQ6MFall11MCProductionCycle.root"     , "Open"));
  file_.push_back(TFile::Open("/afs/cern.ch/user/d/disipio/public/toplhcwg/ntuples_atlas/AlpgenJimmyttbarlnln.root", "Open"));
  file_.push_back(TFile::Open("/afs/cern.ch/user/d/disipio/public/toplhcwg/ntuples_atlas/TTbar_PowHeg_Pythia_P2011C.root", "Open"));
  file_.push_back(TFile::Open("/afs/cern.ch/user/d/disipio/public/toplhcwg/ntuples_atlas/TTbar_PowHeg_Jimmy.root", "Open"));
  file_.push_back(TFile::Open("/afs/cern.ch/user/d/disipio/public/toplhcwg/ntuples_atlas/T1_McAtNlo_Jimmy.root", "Open"));

  // list plots of relevance
  std::vector<TString> plotList_, axisLabel_;
  TString plots1D[ ] = {
    // KinFit plots before prob cut 
    "topPt",
    "topY",
    "ttbarPt",
    "ttbarY",
    "ttbarMass",
    //"decayChannel",
  };
  TString axisLabel1D[ ] = { 
    // KinFit plots before prob cut 
    "p_{T}^{t} #left[GeV#right];#Top quarks (norm.);0;20",
    "y^{t};#Top quarks (norm.);0;1",
    "p_{T}^{t#bar{t}} #left[GeV#right];t#bar{t} pairs (norm.);0;20",
    "y^{t#bar{t}};t#bar{t} pairs (norm.);0;1",
    "m^{t#bar{t}} #left[GeV#right];t#bar{t} pairs (norm.);0;50",
    //"t#bar{t} decay Channel;relative #Top-quark pairs;0;1",
  };

  plotList_ .insert(plotList_ .begin(), plots1D    , plots1D    + sizeof(plots1D    )/sizeof(TString));
  axisLabel_.insert(axisLabel_.begin(), axisLabel1D, axisLabel1D+ sizeof(axisLabel1D)/sizeof(TString));
  if(plotList_.size() != axisLabel_.size()){
    std::cout << "ERROR - 1D plots: Number of plots and axis label do not correspond .... Exiting macro!" << std::endl;
    exit(1);
  }
  // run automatically in batch mode if there are many canvas
  if(plotList_.size()>15) gROOT->SetBatch();

  // create canvas container
  std::vector<TCanvas*> plotCanvas_, plotCanvas2_;
  // create legend
  TLegend* leg= new TLegend(0.5, 0.5, 0.85, 0.88);
  legendStyle(*leg ,"#bf{t#bar{t} simulation, #sqrt{s}=7 TeV}"       );
  TLegend* leg2= new TLegend(0.5, 0.5, 0.85, 0.88);
  legendStyle(*leg2,"#bf{t#bar{t} PYTHIA simulation, #sqrt{s}=7 TeV}");
  TLegend* leg3= new TLegend(0.5, 0.5, 0.85, 0.88);
  legendStyle(*leg3,"#bf{t#bar{t} HERWIG simulation, #sqrt{s}=7 TeV}");

  // ============================
  //  get histos from tree
  // ============================
  unsigned int kfirst    =kMad;
  unsigned int klast     =kMcaA;
  unsigned int krelative1 =kPow; 
  TString krelative1lab="#scale[0.65]{CMS Powheg+Pythia}";
  unsigned int krelative2 =kPow;
  TString krelative2lab="#scale[0.65]{CMS Powheg+Pythia}";
  unsigned int krelative3 =kPowHer;
  TString krelative3lab="#scale[0.65]{CMS Powheg+Herwig}";  
  TString treePath ="genTree/tree";
  TString treePathA="tree";
  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  std::map<TString, std::vector<double> > binning_=makeVariableBinningA(binning);

  // get template histos
  std::vector<TH1F*> template_, template2_, template3_;
  if(debug) std::cout << "get template histos" << std::endl; 
  // loop all plots
  for(int plot=0; plot<(int)plotList_.size(); ++plot){
    TString thname="analyzeTopPartonLevelKinematics/"+plotList_[plot];
    if(debug) std::cout << thname << std::endl;
    //TH1F* temp=new TH1F(plotList_[plot], plotList_[plot], 100000, -5000., 5000.);
    TH1F* temp=new TH1F(plotList_[plot], plotList_[plot], binning_[plotList_[plot]].size()-1, &(binning_[plotList_[plot]][0]));
    //double rebinFactor =atof(((string)getStringEntry(axisLabel_[plot],4,";")).c_str());
    //temp->Rebin(rebinFactor);
    //reBinTH1F(*temp, binning_[plotList_[plot]], 2);
    temp->Reset("icms");
    temp->SetTitle("");
    temp->GetXaxis()->SetTitle(getStringEntry(axisLabel_[plot],1,";"));
    temp->GetYaxis()->SetTitle(getStringEntry(axisLabel_[plot],2,";"));
    temp->GetXaxis()->SetNoExponent(true);
    temp->SetStats(kFALSE);
    temp->SetLineWidth(3);
    temp->SetMarkerSize(1.25);
    //int binMax=temp->GetNbinsX()+1;
    template_ .push_back(temp);
    template2_.push_back(temp);
    template3_.push_back(temp);
  }
  if(debug) std::cout << "process trees" << std::endl; 
  // loop all samples
  for(unsigned int sample=kfirst; sample<=klast; ++sample){
    bool CMS = TString(file_.at(sample)->GetName()).Contains("CMS");
    if(debug){
      std::cout << "sample " << sample;
      if(CMS)  std::cout << " (CMS)";
      else  std::cout << " (ATLAS)";
      std::cout << std::endl; 
    }
    // get tree
    TString treePath2=treePath;
    if(!CMS)treePath2=treePathA;
    TTree* tree = (TTree*)(file_[sample]->Get(treePath2));
    if(!tree){
      std::cout << "WARNING: tree " << treePath << " not found in sample " << sample << ", will continue and neglect this one " << std::endl;
      // exit(0);
    }
    // container for values read from tree
    std::map< TString, float  > value_;
    std::map< TString, double > valueA_;
    // initialize map entries with 0 
    value_["weight"   ]=1;
    value_["topPt"    ]=0;
    value_["topbarPt" ]=0;
    value_["topY"     ]=0;
    value_["topbarY"  ]=0;
    value_["ttbarPt"  ]=0;
    value_["ttbarY"   ]=0;
    value_["ttbarMass"]=0;
    //value_["decayChannel"]=0;
    valueA_["weight"   ]=1;
    valueA_["topPt"    ]=0;
    valueA_["topbarPt" ]=0;
    valueA_["topY"     ]=0;
    valueA_["topbarY"  ]=0;
    valueA_["ttbarPt"  ]=0;
    valueA_["ttbarY"   ]=0;
    valueA_["ttbarMass"]=0;
    //valueA_["decayChannel"]=0;
    // initialize branches
    if(tree){
      tree->SetBranchStatus("*", 0);
      tree->SetBranchStatus("weight"      ,1);
      tree->SetBranchStatus("topPt"       ,1);
      tree->SetBranchStatus("topbarPt"    ,1);
      tree->SetBranchStatus("topY"        ,1);
      tree->SetBranchStatus("topbarY"     ,1);
      tree->SetBranchStatus("ttbarPt"     ,1);
      tree->SetBranchStatus("ttbarY"      ,1);
      tree->SetBranchStatus("ttbarMass"   ,1);
      //tree->SetBranchStatus("decayChannel",1);
      if(CMS){
	tree->SetBranchAddress("weight"      , (&value_["weight"   ]   ));
	tree->SetBranchAddress("topPt"       , (&value_["topPt"    ]   ));
	tree->SetBranchAddress("topbarPt"    , (&value_["topbarPt" ]   ));
	tree->SetBranchAddress("topY"        , (&value_["topY"     ]   ));
	tree->SetBranchAddress("topbarY"     , (&value_["topbarY"  ]   ));
	tree->SetBranchAddress("ttbarPt"     , (&value_["ttbarPt"  ]   ));
	tree->SetBranchAddress("ttbarY"      , (&value_["ttbarY"   ]   ));
	tree->SetBranchAddress("ttbarMass"   , (&value_["ttbarMass"]   ));
	//tree->SetBranchAddress("decayChannel", (&value_["decayChannel"]));
      }
      else{
	tree->SetBranchAddress("weight"      , (&valueA_["weight"   ]   ));
	tree->SetBranchAddress("topPt"       , (&valueA_["topPt"    ]   ));
	tree->SetBranchAddress("topbarPt"    , (&valueA_["topbarPt" ]   ));
	tree->SetBranchAddress("topY"        , (&valueA_["topY"     ]   ));
	tree->SetBranchAddress("topbarY"     , (&valueA_["topbarY"  ]   ));
	tree->SetBranchAddress("ttbarPt"     , (&valueA_["ttbarPt"  ]   ));
	tree->SetBranchAddress("ttbarY"      , (&valueA_["ttbarY"   ]   ));
	tree->SetBranchAddress("ttbarMass"   , (&valueA_["ttbarMass"]   ));
	//tree->SetBranchAddress("decayChannel", (&valueA_["decayChannel"]));
      }
    }

    // initialize histo
    if(debug) std::cout << "initialize histos from template" << std::endl; 
    int color =kRed+7; TString sampleName="MadGraph+Pythia old";
    //if(     sample==kMadOld){ color =kRed+7  ; sampleName="MadGraph+Pythia old" ;}
    if(sample==kMad||sample==kAlp){ color =kRed    ; sample==kMad ? sampleName="MadGraph+Pythia" : sampleName="Alpgen+Herwig"     ;}
    else if(sample==kPow   ||sample==kPowA   ){ color =kGreen  ; sampleName="Powheg+Pythia"      ;}
    else if(sample==kPowHer||sample==kPowHerA){ color =kMagenta; sampleName="Powheg+Herwig"      ;} 
    else if(sample==kMca   ||sample==kMcaA   ){ color =kBlue   ; sampleName="MC@NLO+Herwig"      ;}
    if(CMS) sampleName+="(CMS)"  ;
    else{
      sampleName+="(ATLAS)";
      color+=1;      
    }
    for(int plot=0; plot<(int)plotList_.size(); ++plot){
      // initialize result plots from template
      histo_[plotList_[plot]][sample]=(TH1F*)template_[plot]->Clone(plotList_[plot]+getTStringFromInt(sample));
      histo_[plotList_[plot]][sample]->SetLineColor(color);
      histo_[plotList_[plot]][sample]->SetMarkerColor(color);
      if(!CMS) histo_[plotList_[plot]][sample]->SetLineStyle(2);
    }
    // add legend entry
    leg->AddEntry(histo_[plotList_[0]][sample], sampleName, "L");
    if( PythiaSample(sample)) leg2->AddEntry(histo_[plotList_[0]][sample], sampleName, "L");
    if(!PythiaSample(sample)) leg3->AddEntry(histo_[plotList_[0]][sample], sampleName, "L");

    // loop tree
    if(tree){
      if(debug) std::cout << "fill plots from tree" << std::endl; 
      for(unsigned int event=0; event<tree->GetEntries(); ++event){
	// get event
	tree->GetEntry(event);
	// get relevant quantities
	float weight       = CMS ? value_["weight"      ] : valueA_["weight"      ];
	//float decayChannel = CMS ? value_["decayChannel"] : valueA_["decayChannel"];
	float topPtLep     = CMS ? value_["topPt"       ] : valueA_["topPt"       ];
	float topPtHad     = CMS ? value_["topbarPt"    ] : valueA_["topbarPt"    ];
	float topYLep      = CMS ? value_["topY"        ] : valueA_["topY"        ];
	float topYHad      = CMS ? value_["topbarY"     ] : valueA_["topbarY"     ];
	float ttbarPt      = CMS ? value_["ttbarPt"     ] : valueA_["ttbarPt"     ];
	float ttbarY       = CMS ? value_["ttbarY"      ] : valueA_["ttbarY"      ];
	float ttbarMass    = CMS ? value_["ttbarMass"   ] : valueA_["ttbarMass"   ];
	// debugging output
	if(debug2){
	  std::cout << "event " << event+1 << "/" << tree->GetEntries() << std::endl;
	  std::cout << "weight:       " << weight       << std::endl;
	  //std::cout << "decayChannel: " << decayChannel << std::endl;
	  std::cout << "topPtLep:     " << topPtLep     << std::endl;
	  std::cout << "topPtHad:     " << topPtHad     << std::endl;
	  std::cout << "topYLep:      " << topYLep      << std::endl;
	  std::cout << "topYHad:      " << topYHad      << std::endl;
	  std::cout << "ttbarPt:      " << ttbarPt      << std::endl;
	  std::cout << "ttbarMass:    " << ttbarMass    << std::endl;
	  std::cout << "ttbarY:       " << ttbarY       << std::endl;
	}
	// fill histo for all
	histo_["topPt"     ][sample]->Fill(topPtLep , weight);
	histo_["topPt"     ][sample]->Fill(topPtHad , weight);
	histo_["topY"      ][sample]->Fill(topYLep  , weight);
	histo_["topY"      ][sample]->Fill(topYHad  , weight);
	histo_["ttbarPt"   ][sample]->Fill(ttbarPt  , weight);
	histo_["ttbarY"    ][sample]->Fill(ttbarY   , weight);
	histo_["ttbarMass" ][sample]->Fill(ttbarMass, weight);
      } // end loop event
    } // end if tree
    for(int plot=0; plot<(int)plotList_.size(); ++plot){
      // normalize to unity
      histo_[plotList_[plot]][sample]->Scale(1./histo_[plotList_[plot]][sample]->Integral(0.,histo_[plotList_[plot]][sample]->GetNbinsX()+1)); 
    }
  } // end loop samples

  // ============================
  //  create canvas
  // ============================
  if(debug) std::cout << "create canvas" << std::endl; 
  for(int set=1; set<=3; ++set){
    // loop plots
    for(int plot=0; plot<(int)plotList_.size(); ++plot){
      TString name=plotList_[plot];
      TH1F* temptemplate=0;
      if(set==1) temptemplate=(TH1F*)template_ [plot]->Clone(TString(template_ [plot]->GetName())+"1");
      if(set==2) temptemplate=(TH1F*)template2_[plot]->Clone(TString(template2_[plot]->GetName())+"2");
      if(set==3) temptemplate=(TH1F*)template3_[plot]->Clone(TString(template3_[plot]->GetName())+"3");
      TString nameExt= set==2 ? "PYTHIA" : (set==3 ? "HERWIG" : "");
      if(debug) std::cout << "plot " << name << std::endl; 
      addCanvas(plotCanvas_);
      plotCanvas_[plotCanvas_.size()-1]->cd(0);
      plotCanvas_[plotCanvas_.size()-1]->SetName(name+nameExt);
      plotCanvas_[plotCanvas_.size()-1]->SetTitle(name+nameExt);
      temptemplate->SetMaximum(1.5*histo_[name][kPow]->GetMaximum());
      //temptemplate->GetXaxis()->SetLabelSize(0);
      //temptemplate->GetXaxis()->SetTitleSize(0);
      temptemplate->Draw("AXIS");
      // draw all samples
      for(unsigned int sample=kfirst; sample<=klast; ++sample){
	if(histo_[name].count(sample)>0&&(set==1||(set==2&&PythiaSample(sample))||(set==3&&!PythiaSample(sample)))){
	  if(debug) std::cout << " - draw sample " << sample << std::endl; 
	  histo_[name][sample]->Draw("hist same");
	}
      }
      // legend
      if(plotList_[plot].Contains("topPt")){
	if     (set==1) leg ->Draw("same");
	else if(set==2) leg2->Draw("same");
	else if(set==3) leg3->Draw("same");
	if(debug) std::cout << " - draw legend" << std::endl; 
      }
      // zero error
      std::vector<double> zeroerr_;
      for(int bin=0; bin<temptemplate->GetNbinsX(); ++bin) zeroerr_.push_back(0);
      // draw ratios
      if(debug) std::cout << " - draw ratios:" << std::endl; 
      //bool first=true;
      unsigned int krelative=krelative1;
      TString krelativelab=krelative1lab;
      if(set==2 ){ krelative=krelative2; krelativelab=krelative2lab;}
      if(set==3 ){ krelative=krelative3; krelativelab=krelative3lab;}
      drawRatio(temptemplate, temptemplate, 0.3, 1.7, myStyle, verbose, zeroerr_, "simulation", krelativelab, "AXIS", kWhite);
      for(unsigned int sample=kfirst; sample<=klast; ++sample){
	if((histo_[name].count(sample)>0&&histo_[name].count(krelative)>0)&&((set==1)||(set==2&&PythiaSample(sample))||(set==3&&!PythiaSample(sample)))){
	  if(debug) std::cout << "   sample " << sample << std::endl; 
	  //TString opt = first ? "hist" : "hist same";
	  TString opt = "hist same";
	  //if(first) first=false;
	  drawRatio(histo_[name][sample], histo_[name][krelative], 0.3, 1.7, myStyle, verbose, zeroerr_, "simulation", krelativelab, opt, histo_[name][sample]->GetLineColor());
	}
      }
      //if(set>1) DrawLabel(TString(template_[plot]->GetXaxis()->GetTitle()), 0.2, 0.07, 0.95, 0.3, 32, 0.15);
      temptemplate->Draw("AXIS same");
    } // end for loop plot
  } // end for loop sep
  if(save){
    TString name="./treeATLASCMScomparison";
    TString name2=binning==1 ? "ATLASbinning" : (binning==2 ? "CMSbinning" : "FineBinning");
    if(debug) std::cout << "save plots as pictures" << std::endl;  
    saveCanvas(plotCanvas_, name+name2, "", true, true);
    if(debug) std::cout << "save plots in rootfile" << std::endl;
    for(unsigned int i=0; i<plotCanvas_.size(); ++i){
      if(debug) {
	std::cout << i+1 << "/" << plotCanvas_.size();
	std::cout << ": "<< plotCanvas_[i]->GetTitle();
	std::cout << "->" << name+".root" << std::endl;
      }
      saveToRootFile(name+".root", plotCanvas_[i], true, 0, name2);
      //TFile* tempf=TFile::Open(name+".root", "READ");
      //if(!tempf) std::cout << "ERROR: can't open file!" << std::endl;
      //std::cout << "a" << std::endl;
      //TCanvas* temp = (TCanvas*)(tempf->Get(name2+"/"+plotCanvas_[i]->GetTitle())->Clone());
      //std::cout << "b" << std::endl;
      //plotCanvas2_.push_back(temp);
      //std::cout << "d" << std::endl;
      //tempf->Close();
    }
    //saveCanvas(plotCanvas2_, name+name2, "", true, true);
  }
}


std::map<TString, std::vector<double> > makeVariableBinningA(int binning)
{
  // this function creates a map with the hard coded
  // bin values for variable binning
  // NOTE: it is important to quote the overflow bin
  // of the initial binning as last bin here!!!
  // otherwise dividing per binwidth function
  // might later give nan and histo wouldn't be drawn
  // modified quantities: none
  // used functions: none
  // used enumerators: none

  std::map<TString, std::vector<double> > result;
  std::vector<double> bins_;

  // pt(top)
  double topPtBins[]= {0.0, 50.0, 100.0, 150.0, 200.0 , 250.0, 350.0, 800.};
  double topPtBinsA[]= {0.0, 60.0, 100.0, 150.0, 200.0, 260.0, 320.0, 400.0, 500.0};
  if(binning==2) bins_.insert( bins_.begin(), topPtBins, topPtBins + sizeof(topPtBins)/sizeof(double) );
  else if(binning ==1) bins_.insert( bins_.begin(), topPtBinsA, topPtBinsA + sizeof(topPtBinsA)/sizeof(double) );
  else{
    double width=10.;
    double min=0.;
    double max=800.;
    for(double bin=min; bin<=max; bin+=width){
      bins_.push_back(bin);
    }
  }
  result["topPt"        ] = bins_;
  bins_.clear();

  // y(top)
  double topYBins[]={-2.5, -1.6, -1.2, -0.8, -0.4, 0.0, 0.4, 0.8, 1.2, 1.6, 2.5}; 
  if(binning>0) bins_.insert( bins_.begin(), topYBins, topYBins + sizeof(topYBins)/sizeof(double) );
  else{
    double width=0.1;
    double min=-2.5;
    double max= 2.5;
    for(double bin=min; bin<=max; bin+=width){
      bins_.push_back(bin);
    }
  }
  result["topY"   ]   = bins_;
  bins_.clear();

  // pt(ttbar)
  double ttbarPtBins[] = {0.0, 40.0, 170.0, 340.0, 1000.0};
  double ttbarPtBinsA[]= {0.0, 20.0, 45.0, 75.0, 120.0, 190.0, 300.0};
  if(binning==2) bins_.insert( bins_.begin(), ttbarPtBins, ttbarPtBins + sizeof(ttbarPtBins)/sizeof(double) );
  else if(binning ==1) bins_.insert( bins_.begin(), ttbarPtBinsA, ttbarPtBinsA + sizeof(ttbarPtBinsA)/sizeof(double) );
  else{
    double width=10.;
    double min=0.;
    double max=1000.;
    for(double bin=min; bin<=max; bin+=width){
      bins_.push_back(bin);
    }
  }
  result["ttbarPt"]=bins_;
  bins_.clear();

  // y(ttbar)
  double ttbarYBins[]= {-2.5, -1.0, -0.5, 0.0, 0.5, 1.0, 2.5};
  double ttbarYBinsA[]= {-2.5, -1.3, -0.9, -0.6, -0.3, 0.0, 0.3, 0.6, 0.9, 1.3, 2.5};
  if(binning==2) bins_.insert( bins_.begin(), ttbarYBins, ttbarYBins + sizeof(ttbarYBins)/sizeof(double) );
  else if(binning ==1) bins_.insert( bins_.begin(), ttbarYBinsA, ttbarYBinsA + sizeof(ttbarYBinsA)/sizeof(double) );
  else{
    double width=0.1;
    double min=-2.5;
    double max= 2.5;
    for(double bin=min; bin<=max; bin+=width){
      bins_.push_back(bin);
    }
  }
  result["ttbarY"]=bins_;
  bins_.clear();

  // m(ttbar)
  double ttbarMassBins[]= {345.0, 450.0, 550.0, 700.0, 950.0, 2700.0};
  double ttbarMassBinsA[]= {345.0, 400.0, 470.0, 550.0, 650.0, 800.0, 1100.0, 1600.0};
  if(binning==2) bins_.insert( bins_.begin(), ttbarMassBins, ttbarMassBins + sizeof(ttbarMassBins)/sizeof(double) );
  else if(binning ==1) bins_.insert( bins_.begin(), ttbarMassBinsA, ttbarMassBinsA + sizeof(ttbarMassBinsA)/sizeof(double) );
  else{
    double width=10.;
    double min=250.;
    double max=2500.;
    for(double bin=min; bin<=max; bin+=width){
      bins_.push_back(bin);
    }
  }
  result["ttbarMass"]=bins_;
  bins_.clear();

  return result;
}

bool PythiaSample (unsigned int s)
{
  if(s==kMad ) return true;
  if(s==kPow ) return true;
  if(s==kPowA) return true;
  return false;
}
