#include "basicFunctions.h"
#include "TTree.h"
#include "algorithm"

TH1F* distort(const TH1& hist, TString variation, TString variable, double distortParameter, int verbose);
double linSF(const double x, const double xmax, const double a, const double b, double distortParameter);

void analyzeTopDiffXSecMCdependency(TString decayChannel="muon", bool save=true, int verbose=1, TString inputFolderName="TOP2011/110819_AnalysisRun")
{
  // ---
  //     Configuration
  // ---
  // det up common analysis style
  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  TGaxis::SetMaxDigits(2);
  myStyle.cd();
  gROOT->SetStyle("HHStyle");

  // restricted kinematic phase space?
  bool phaseSpace=true;

  // define names
  // file name for input rootfile
  TString analysisFileName="";
  if     (decayChannel=="muon"    ) analysisFileName="/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/muonDiffXSecSigMadD6TSummer11PF.root";
  else if(decayChannel=="electron") analysisFileName="/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/elecDiffXSecSigMadD6TSummer11PF.root";
  else{
    std::cout << "ERROR: decay channel " << decayChannel << " is no valid choice, use electron or muon!" << std::endl;
    exit(0);
  }
  // file name for output rootfiles
  TString outputFileNameUp=analysisFileName;
  TString outputFileNameDown=analysisFileName;
  outputFileNameUp.ReplaceAll  ("PF", "MCShapeVarUpPF"  );
  outputFileNameDown.ReplaceAll("PF", "MCShapeVarDownPF");
  // name for folder where tree is read from
  TString folder="analyzeTopRecoKinematicsKinFit";
  TString genfolder="analyzeTopPartonLevelKinematics";
  if(phaseSpace==true) genfolder+="PhaseSpace";
  // name for folder where plots are saved to
  TString savePlotsTo="./diffXSecFromSignal/plots/"+decayChannel+"/2011/shapeReweighting";
  // define variables
  std::vector<TString> variable_;
  TString variable[] ={"topPt", "topY", "ttbarPt", "ttbarMass", "ttbarY"};
  variable_.insert( variable_.begin(), variable, variable + sizeof(variable)/sizeof(TString) );
  // container for values read from tree
  std::map< TString, float > value_;
  // container for original and shape distorted
  // parton Level (phase space) plots
  std::map< TString, TH1F*> plots_;
  std::map< TString, TH1F*> plotsScaled_;
  // container for final distorted plots
  // lep/had top quantities are filled in the same plot
  std::map< TString, std::map< TString, TH1F*> > finalPlots_;
  
  // printout of configuration
  if(verbose>0){
    std::cout << std::endl << "create rootfile with genbased reweighted distibutions" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "input rootfile: " << analysisFileName << std::endl;
    std::cout << "parton level plots for the calculation of the distortion ";
    std::cout << "SFs are taken from folder: " << genfolder << std::endl;
    std::cout << "used tree for filling distorted reco ";
    std::cout << "level plots: " << folder+"/tree" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "output rootfiles: " << outputFileNameUp << ", " << outputFileNameDown << std::endl;
    std::cout << "reweighted parton level distributions are stored in folder: " << genfolder << std::endl;
    std::cout << "reweighted reconstruction level distributions are stored in folder: " << folder << std::endl;
  }

  // define list of variations
  std::vector<TString> variation_;
  variation_.push_back("Up");
  variation_.push_back("Down");

  // ---
  //     Loading
  // ---
  // load input file
  TFile*inFile= new TFile(analysisFileName, "read");
  if(!inFile||inFile->IsZombie()){
    std::cout << "there seems to be a problem with the chosen input file " << analysisFileName << std::endl;
    exit(0);
  }
  // draw a copy of the input file
  // the cross section input plots will 
  // be replaced in part F
  if(save){
    std::cout << "copy old root file, will only replace shifted plots" << std::endl;
    std::cout << "a) varition up" << std::endl;
    inFile->Cp(analysisFileName, outputFileNameUp);
    std::cout << "b) varition down" << std::endl;
    inFile->Cp(analysisFileName, outputFileNameDown);
  }
  // loading trees
  TTree *tree=(TTree*)(inFile->Get(folder+"/tree"));
  if(!tree||tree->IsZombie()){
     std::cout << "there seems to be a problem with the chosen tree " << folder+"/tree" << std::endl;
     exit(0);  
  }

  // initialize map entries with 0 
  // to avoid problems with the map re-ordering
  // when new entries are added
  value_["weight"]=0;
  if(verbose>0) std::cout << "considered variables: ";
  for(unsigned int i=0; i<variable_.size();++i){
    TH1F* hist=(TH1F*)(inFile->Get(folder+"/"+variable_[i]));
    if(verbose>0) std::cout << variable_[i]+" ";
    value_[variable_[i]              ]=0;
    value_[variable_[i]+"PartonTruth"]=0;
    if(variable_[i].Contains("top")){
      value_[variable_[i]+"Lep"]=0;
      value_[variable_[i]+"Had"]=0;
      value_[variable_[i]+"LepPartonTruth"]=0;
      value_[variable_[i]+"HadPartonTruth"]=0;
    }
    // initialize plots with correct binning
    // original plots for parton level phase space / reconstruction level
    plots_      [variable_[i]+"PartonTruth"]=new TH1F( variable_[i]+"PartonTruth", variable_[i]+"PartonTruth", hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
    plots_      [variable_[i]              ]=new TH1F( variable_[i]              , variable_[i]              , hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
    // loop all variations 
    for(unsigned int var=0; var<variation_.size();++var){
      TString Var=variation_[var];
      // systematic distorted plots for parton level phase space / reconstruction level
      // used for SF determination
      plotsScaled_[variable_[i]+"PartonTruth"+Var]=new TH1F( variable_[i]+"PartonTruth"+Var, variable_[i]+"PartonTruth"+Var, hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
      plotsScaled_[variable_[i]              +Var]=new TH1F( variable_[i]+Var              , variable_[i]+Var              , hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
      for(unsigned int j=0; j<variable_.size();++j){
	// final plots: reweighted plots from tree entries
	// (reweighting based on all events on parton level within phase space)
	// reconstruction level plots and parton level plots for reconstructed events
	finalPlots_[variable_[j]+"PartonTruth"][variable_[i]+Var]=new TH1F( variable_[j]+"PartonTruth"+variable_[i]+"SF"+Var, variable_[j]+"PartonTruth"+variable_[i]+"SF"+Var, hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
	finalPlots_[variable_[j]              ][variable_[i]+Var]=new TH1F( variable_[j]              +variable_[i]+"SF"+Var, variable_[j]              +variable_[i]+"SF"+Var, hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
      }
    }
  }
  if(verbose>0) std::cout << std::endl;

  // ---
  //    part A: get values for all variables from tree
  // ---
  if(verbose>0) std::cout << std::endl << "part A: get tree entries" << std::endl;
  tree->SetBranchStatus("*",0);
  tree->SetBranchStatus("weight",1);
  tree->SetBranchAddress("weight",(&value_["weight"]));
  // loop all variables
  for(unsigned int i=0; i<variable_.size();++i){
    // take care about splitted leptonic and hadronic top distributions
    if(variable_[i].Contains("top")){
      // activate branches
      tree->SetBranchStatus(variable_[i]+"Lep",1);
      tree->SetBranchStatus(variable_[i]+"Had",1);
      tree->SetBranchStatus(variable_[i]+"LepPartonTruth",1);
      tree->SetBranchStatus(variable_[i]+"HadPartonTruth",1);
      // save branch values in map
      tree->SetBranchAddress(variable_[i]+"Lep",(&value_[variable_[i]+"Lep"]));
      tree->SetBranchAddress(variable_[i]+"Had",(&value_[variable_[i]+"Had"]));
      tree->SetBranchAddress(variable_[i]+"LepPartonTruth",(&value_[variable_[i]+"LepPartonTruth"]));
      tree->SetBranchAddress(variable_[i]+"HadPartonTruth",(&value_[variable_[i]+"HadPartonTruth"]));
    }
    // same for ttbar quantities
    else{
      tree->SetBranchStatus(variable_[i],1);
      tree->SetBranchStatus(variable_[i]+"PartonTruth",1);
      tree->SetBranchAddress(variable_[i],(&value_[variable_[i]]));
      tree->SetBranchAddress(variable_[i]+"PartonTruth",(&value_[variable_[i]+"PartonTruth"]));
    }
  }
  // check if tree entries are ok
  std::vector<TString> uninitialized_;
  int Nevents=0;
  // loop all events
  for(unsigned int event=0; event<tree->GetEntries(); ++event){
    tree->GetEntry(event);
    Nevents++;
    // loop all variables
    for(unsigned int i=0; i<variable_.size();++i){
      // check leptonic/ hadronic top quantities
      if(variable_[i].Contains("top")){
	// leptonic top
	if(value_[variable_[i]+"Lep"]==-9999){
	  // check if already an invalid branch entry was found
	  vector<TString>::iterator it=find(uninitialized_.begin(), uninitialized_.end(), variable_[i]+"Lep");
	  if(uninitialized_.size()==0||it!=uninitialized_.end()) uninitialized_.push_back(variable_[i]+"Lep");
	}
	// hadronic top
	if(value_[variable_[i]+"Had"]==-9999){
	  // check if already an invalid branch entry was found
	  vector<TString>::iterator it=find(uninitialized_.begin(), uninitialized_.end(), variable_[i]+"Had");
	  if(uninitialized_.size()==0||it!=uninitialized_.end()) uninitialized_.push_back(variable_[i]+"Had");
	}
      }
      // check ttbar quantities
      else{ 
	if(value_[variable_[i]]==-9999){
	  // check if already an invalid branch entry was found
	  vector<TString>::iterator it=find(uninitialized_.begin(), uninitialized_.end(), variable_[i]);
	  if(uninitialized_.size()==0||it!=uninitialized_.end()) uninitialized_.push_back(variable_[i]);
	}
      }
    }
  }
  // print list of uninitialized tree entries
  if(uninitialized_.size()>0){
    std::cout << "there are " << uninitialized_.size();
    std::cout << " (partly) uninitialized branches in the tree:" << std::endl;
    for(unsigned int var=0; var<uninitialized_.size();++var){
      std::cout << uninitialized_[var] << std::endl;
    }
    exit(0);
  }
  else{
    std::cout << "all trees seem to be filled properly" << std::endl;
    std::cout << Nevents << " events in total" << std::endl;
  }

  // ---
  //    part B: get weights for shape distortion
  // ---
  if(verbose>0) std::cout << std::endl << "part B: get weights for shape distortion" << std::endl;
  // B1 get original parton level distribution (phasespace) plots
  // loop all variables
  for(unsigned int i=0; i<variable_.size();++i){
    TH1* targetPlot;
    TH1* targetPlot2;
    inFile->GetObject(genfolder+"/"+variable_[i], targetPlot);
    inFile->GetObject(folder+"/"+variable_[i]   , targetPlot2);
    // check if plot exits
    if(!targetPlot){ 
      std::cout << "plot " << genfolder+"/"+variable_[i] << "can not ";
      std::cout << "be found in file " << analysisFileName << std::endl;
      exit(0);
    }
    else{
      plots_[variable_[i]+"PartonTruth"]=(TH1F*)(targetPlot->Clone());
      // check for empty plots
      if(plots_[variable_[i]+"PartonTruth"]->GetEntries()==0){
	std::cout << "ERROR: empty plot " << analysisFileName;
	std::cout << "/"+genfolder+"/"+variable_[i] << std::endl;
	exit(0);
      }
    }
    if(!targetPlot2){ 
      std::cout << "plot " << folder+"/"+variable_[i] << "can not ";
      std::cout << "be found in file " << analysisFileName << std::endl;
      exit(0);
    }
    else{
      plots_[variable_[i]]=(TH1F*)(targetPlot2->Clone());
      // check for empty plots
      if(plots_[variable_[i]]->GetEntries()==0){
	std::cout << "ERROR: empty plot " << analysisFileName;
	std::cout << "/"+folder+"/"+variable_[i] << std::endl;
	exit(0);
      }
    }
  }
  // check if all plots are filled properly
  int NeventsPS=plots_["ttbarMassPartonTruth"]->GetEntries();
  if(verbose>0) std::cout << NeventsPS << " events in chosen Phase space" << std::endl;
  // loop all variables
  for(unsigned int i=0; i<variable_.size();++i){
    // count number of entries
    int entries=plots_[variable_[i]+"PartonTruth"]->GetEntries();
    // take into account that there are two top quarks
    if(variable_[i].Contains("top")) entries*=0.5;
    // compare number of events
    if(entries!=NeventsPS){
	std::cout << "ERROR: wrong number of events in plot " << analysisFileName;
	std::cout << "/"+genfolder+"/"+variable_[i] << " or /ttbarMass" << std::endl;
	exit(0);
    }
  }
  if(verbose>0) std::cout << "original parton level phase space plots loaded successfully" << std::endl;

  // B2 distort distributions
  double distortParameter=2;
  if(verbose>0) std::cout << "performing a linear distortion" /*<<" with parameter " << distortParameter*/ << std::endl;
  // loop all variables
  for(unsigned int i=0; i<variable_.size();++i){
    // loop all variations 
    for(unsigned int var=0; var<variation_.size();++var){
      TString Var=variation_[var];
      // loop all bins
      for(int bin=0; bin<=plotsScaled_[variable_[i]+"PartonTruth"+Var]->GetNbinsX()+1; ++bin){
	plotsScaled_[variable_[i]+"PartonTruth"+Var]=distort(*plots_[variable_[i]+"PartonTruth"], Var, variable_[i], distortParameter, verbose-1);
      }
    }
  }
  
  // B3 calculate SF
  std::map< TString, TH1F* > SF_;
  // loop all variables
  for(unsigned int i=0; i<variable_.size();++i){
    // loop all variations 
    for(unsigned int var=0; var<variation_.size();++var){
      TString Var=variation_[var];
      SF_[variable_[i]+Var]=(TH1F*)plotsScaled_[variable_[i]+"PartonTruth"+Var]->Clone();
      SF_[variable_[i]+Var]->Divide(plots_[variable_[i]+"PartonTruth"]);
    }
  }

  // B4 make sure to normalize the distorted plot 
  //    to the same area as the original one
  // -> dont change the absolut amount of events!
  // loop all variables
  for(unsigned int i=0; i<variable_.size();++i){
    // loop all variations 
    for(unsigned int var=0; var<variation_.size();++var){
      TString Var=variation_[var];
      double initArea = plots_[variable_[i]+"PartonTruth"]->Integral(0,plots_[variable_[i]+"PartonTruth"]->GetNbinsX()+1);
      double areaSFUp   = initArea/plotsScaled_[variable_[i]+"PartonTruth"+"Up"  ]->Integral(0,plotsScaled_[variable_[i]+"PartonTruth"+"Up"  ]->GetNbinsX()+1);
      double areaSFDown = initArea/plotsScaled_[variable_[i]+"PartonTruth"+"Down"]->Integral(0,plotsScaled_[variable_[i]+"PartonTruth"+"Down"]->GetNbinsX()+1);
      SF_[variable_[i]+"Up"  ]->Scale(areaSFUp  );
      plotsScaled_[variable_[i]+"PartonTruth"+"Up"  ]->Scale(areaSFUp);
      SF_[variable_[i]+"Down"]->Scale(areaSFDown);
      plotsScaled_[variable_[i]+"PartonTruth"+"Down"]->Scale(areaSFDown);
      if(verbose>1) std::cout << "area SF(up variation) for "   << variable_[i] << ": " << areaSFUp   << std::endl;
      if(verbose>1) std::cout << "area SF(down variation) for " << variable_[i] << ": " << areaSFDown << std::endl;
    }
  }
  if(verbose>0){
    std::cout << "distortion SF keeps normalization for original ";    
    std::cout << "(phase space) parton level truth distribution" << std::endl;
  }

  // B5 check for negative SF
  // loop all variables
  for(unsigned int i=0; i<variable_.size();++i){
    // loop all variations 
    for(unsigned int var=0; var<variation_.size();++var){
      TString Var=variation_[var];
      // loop all bins
      for(int bin=0; bin<=SF_[variable_[i]+Var]->GetNbinsX()+1; ++bin){
	if(SF_[variable_[i]+Var]->GetBinContent(bin)==1){
	  std::cout << "ERROR: some distortion SF for "+Var+" variation is 1!" << std::endl;
	  exit(1);
	}
      }
    }
  }
    
  // ---
  //    part C: create control plots for weighted (phase space) parton level distributions
  // ---
  if(verbose>0) std::cout << std::endl << "part C: create control plots" << std::endl;
  std::vector<TCanvas*> plotCanvas_;
  // C1 create canvas
  for(unsigned int plot=0; plot<variable_.size(); ++plot){
    char canvname[10];
    sprintf(canvname,"canv%i",plot);    
    plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );
    //canvasStyle(*plotCanvas_[sample]);
  }
  // C2 create legend
  TLegend *legPS = new TLegend(0.69, 0.66, 1.00, 0.85);
  legPS->SetFillStyle(0);
  legPS->SetBorderSize(0);
  legPS->SetEntrySeparation(0.45);
  legPS->SetHeader("#splitline{parton level}{(phase space)}");
  legPS->AddEntry(plotsScaled_[variable_[0]+"PartonTruth"+"Up"  ], "up"     , "L");
  legPS->AddEntry(plots_      [variable_[0]+"PartonTruth"       ], "central", "L");
  legPS->AddEntry(plotsScaled_[variable_[0]+"PartonTruth"+"Down"], "down"   , "L");

  // C3 fill scaled and original plot into one canvas
  int canvasNumber=0;
  // loop all variables
  for(unsigned int i=0; i<variable_.size();++i){
    plotCanvas_[canvasNumber]->cd(0);
    plotCanvas_[canvasNumber]->SetTitle(variable_[i]+"PartonLevelPhaseSpace");
    histogramStyle(*plotsScaled_[variable_[i]+"PartonTruth"+"Up"  ], 0, false);
    histogramStyle(*plotsScaled_[variable_[i]+"PartonTruth"+"Down"], 2, false);
    histogramStyle(*plots_      [variable_[i]+"PartonTruth"       ], 0, false);
    plots_      [variable_[i]+"PartonTruth"       ]->SetLineColor(kBlack);
    plotsScaled_[variable_[i]+"PartonTruth"+"Down"]->GetXaxis()->SetNoExponent(true);
    plotsScaled_[variable_[i]+"PartonTruth"+"Down"]->GetXaxis()->SetTitle(variable_[i]);
    plotsScaled_[variable_[i]+"PartonTruth"+"Down"]->GetYaxis()->SetTitle("events");
    plotsScaled_[variable_[i]+"PartonTruth"+"Down"]->Draw("");
    plotsScaled_[variable_[i]+"PartonTruth"+"Up"  ]->Draw("same");
    plots_      [variable_[i]+"PartonTruth"       ]->Draw("same");
    legPS->Draw("same");
    ++canvasNumber;
  }
  //int partonLevelPlots=canvasNumber;

  // ---
  //    part D: create weighted plots
  // ---
  if(verbose>0) std::cout << std::endl << "part D: use parton level based SF to reweight reco histos" << std::endl;
  // loop all events
  for(unsigned int event=0; event<tree->GetEntries(); ++event){
    tree->GetEntry(event);
    double weight=value_["weight"];
    if(weight==0) std::cout << "WARNING: standard event weight (from tree) is 0!" << std::endl;
    // i: loop all variables (for SF)
    for(unsigned int i=0; i<variable_.size();++i){
      if(verbose>3) std::cout << "SF: " << variable_[i] << ", "; 
      // j: loop all variables (for plot to be scaled)
      for(unsigned int j=0; j<variable_.size();++j){
	if(verbose>3) std::cout << "variable: " << variable_[j] << std::endl;
	// loop all variations 
	for(unsigned int var=0; var<variation_.size();++var){
	  TString Var=variation_[var];
	  if(verbose>3) std::cout << "variation: " << Var << std::endl;
	  // get distortion SF (from variable i)
	  double LepShapeWeight=0;
	  double HadShapeWeight=0;
	  // for leptonic and hadronic top: get 2xSF (from variable i)
	  if(variable_[i].Contains("top")){
	    LepShapeWeight=SF_[variable_[i]+Var]->GetBinContent(SF_[variable_[i]+Var]->FindBin(value_[variable_[i]+"Lep"+"PartonTruth"]));
	    HadShapeWeight=SF_[variable_[i]+Var]->GetBinContent(SF_[variable_[i]+Var]->FindBin(value_[variable_[i]+"Had"+"PartonTruth"]));
	  }
	  // for other quantities: use one SF only (from variable i)
	  else{
	    LepShapeWeight=SF_[variable_[i]+Var]->GetBinContent(SF_[variable_[i]+Var]->FindBin(value_[variable_[i]]));
	    HadShapeWeight=LepShapeWeight;
	  }
	  if(verbose>3) std::cout << "had weight: " << HadShapeWeight << std::endl;
	  if(verbose>3) std::cout << "lep weight: " << LepShapeWeight << std::endl;
	  // filling for top quantities: fill leptonic and hadronic top quantities in same plot
	  if(variable_[j].Contains("top")){
	    // parton truth plots
	    finalPlots_[variable_[j]+"PartonTruth"][variable_[i]+Var]->Fill(value_[variable_[j]+"Lep"+"PartonTruth"], weight*LepShapeWeight);
	    finalPlots_[variable_[j]+"PartonTruth"][variable_[i]+Var]->Fill(value_[variable_[j]+"Had"+"PartonTruth"], weight*HadShapeWeight);
	    if(verbose>3) std::cout << "lep parton truth: " << value_[variable_[j]+"Lep"+"PartonTruth"] << "*" <<  weight << "*" << LepShapeWeight << std::endl;
	    if(verbose>3) std::cout << "had parton truth: " << value_[variable_[j]+"Had"+"PartonTruth"] << "*" <<  weight << "*" << HadShapeWeight << std::endl;
	    // reconstruction level plots
	    finalPlots_[variable_[j]][variable_[i]+Var]->Fill(value_[variable_[j]+"Lep"], weight*LepShapeWeight);
	    finalPlots_[variable_[j]][variable_[i]+Var]->Fill(value_[variable_[j]+"Had"], weight*HadShapeWeight);
	    if(verbose>3) std::cout << "lep reco: " << value_[variable_[j]+"Lep"] << "*" <<  weight << "*" << LepShapeWeight << std::endl;
	    if(verbose>3) std::cout << "had reco: " << value_[variable_[j]+"Had"] << "*" <<  weight << "*" << HadShapeWeight << std::endl;
	  }
	  // other quantities: take average of leptonic and hadronic top SF
	  else{
	    // parton truth plots
	    finalPlots_[variable_[j]+"PartonTruth"][variable_[i]+Var]->Fill(value_[variable_[j]+"PartonTruth"], weight*0.5*(LepShapeWeight+HadShapeWeight));
	    if(verbose>3) std::cout << "parton level: " << value_[variable_[j]+"PartonTruth"] << "*" <<  weight << "*" << 0.5*(LepShapeWeight+HadShapeWeight) << std::endl;
	    // reconstruction level plots
	    finalPlots_[variable_[j]][variable_[i]+Var]->Fill(value_[variable_[j]], weight*0.5*(LepShapeWeight+HadShapeWeight));
	    if(verbose>3) std::cout << "reco: " << value_[variable_[j]] << "*" <<  weight << "*" << 0.5*(LepShapeWeight+HadShapeWeight) << std::endl;
	  }
	}
      }
    }
  }

  // ---
  //    part E: draw all reweighted reco level plots
  // ---
  TLegend* legReco= new TLegend(0.65, 0.696, 1.15, 0.86);
  legReco->SetFillStyle(0);
  legReco->SetBorderSize(0);
  legReco->SetHeader("reconstruction level");
  legReco->AddEntry(finalPlots_[variable_[0]][variable_[0]+"Up"  ], "up"     , "L");
  legReco->AddEntry(plots_      [variable_[0]]                    , "central", "L");
  legReco->AddEntry(finalPlots_[variable_[0]][variable_[0]+"Down"], "down"   , "L");
  if(verbose>0) std::cout << std::endl << "part E: collect all final plots" << std::endl;
  // i: loop all variables (for SF)
  for(unsigned int i=0; i<variable_.size();++i){
    // j: loop all variables (for shown plot)
    for(unsigned int j=0; j<variable_.size();++j){
      // fill original/scaled reco plots only into canvas   
      if(i==j){
	// create canvas for every plot
	char canvname[10];
	sprintf(canvname,"canv%i",canvasNumber);
	plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );
	plotCanvas_[canvasNumber]->cd(0);
	// set canvas title and headline
	TString title = finalPlots_[variable_[j]][variable_[i]+"Up"]->GetTitle();
	TString PS="RecoLevel";
	if(title.Contains("PartonTruth")) PS="PartonLevel";
	finalPlots_[variable_[j]][variable_[i]+"Up"  ]->SetTitle(variable_[j]+PS+"SFfrom"+variable_[i]+"Up"  );
	finalPlots_[variable_[j]][variable_[i]+"Down"]->SetTitle(variable_[j]+PS+"SFfrom"+variable_[i]+"Down");
	plotCanvas_[canvasNumber]->SetTitle(variable_[j]+PS+"SFfrom"+variable_[i]);
	// set style
	histogramStyle(*finalPlots_[variable_[j]][variable_[i]+"Up"  ], 0, false);
	histogramStyle(*finalPlots_[variable_[j]][variable_[i]+"Down"], 2, false);
	histogramStyle(*plots_[variable_[j]], 0, false);
	plots_[variable_[j]]->SetLineColor(kBlack);
	// draw
	finalPlots_[variable_[j]][variable_[i]+"Down"]->GetXaxis()->SetNoExponent(true);
	finalPlots_[variable_[j]][variable_[i]+"Down"]->GetXaxis()->SetTitle(variable_[j]);
	finalPlots_[variable_[j]][variable_[i]+"Down"]->GetYaxis()->SetTitle("events");
	finalPlots_[variable_[j]][variable_[i]+"Down"]->DrawClone("");
	finalPlots_[variable_[j]][variable_[i]+"Up"  ]->DrawClone("same");
	plots_[variable_[j]]->DrawClone("same");
	// change name
	finalPlots_[variable_[j]][variable_[i]+"Down"]->SetName (variable_[j]);
	finalPlots_[variable_[j]][variable_[i]+"Down"]->SetTitle(variable_[j]);
	finalPlots_[variable_[j]][variable_[i]+"Up"  ]->SetName (variable_[j]);
	finalPlots_[variable_[j]][variable_[i]+"Up"  ]->SetTitle(variable_[j]);
	// draw legend
	if(PS=="RecoLevel") legReco->Draw("same");
	// adapt counter
	++canvasNumber;
      }
    }
  }

  // ---
  //    part F: save weighted plots and control plots
  // ---
  bool saveIntoRootfile=true;
  if(save){
    if(verbose>0){
      std::cout << std::endl << "part F1: save rweighted parton level and";
      std::cout << "reconstruction level plots to output folder" << std::endl;
    }
    // F1: save control plots
    for(unsigned int plot=0; plot<plotCanvas_.size(); ++plot){
      plotCanvas_[plot]->Print(savePlotsTo+"/"+plotCanvas_[plot]->GetTitle()+".png");
      plotCanvas_[plot]->Print(savePlotsTo+"/"+plotCanvas_[plot]->GetTitle()+".eps");
    }
    // F2: save scaled parton level distribution 
    // and reco plots in root file for systematic variation
    if(verbose>0) std::cout << std::endl << "part F2: save reweighted reco histos to output files" << std::endl;
    // i: loop all variables (for SF)
    for(unsigned int i=0; i<variable_.size();++i){
      // j: loop all variables (for shown plot)
      for(unsigned int j=0; j<variable_.size();++j){
	// up to now: save only plots where reco plot is weighted with its own gen distribution
	if(saveIntoRootfile&&i==j){
	  // parton level plot
	  // attention: the distorted PS parton level plots used for SF determination are used
	  saveToRootFile(outputFileNameUp  , plotsScaled_[variable_[i]+"PartonTruth"+"Up"  ], true, verbose-1, genfolder);
	  saveToRootFile(outputFileNameDown, plotsScaled_[variable_[i]+"PartonTruth"+"Down"], true, verbose-1, genfolder);
	  // reco plot (weighted with distorted parton level distribution of the same quantity)
	  saveToRootFile(outputFileNameUp  , finalPlots_[variable_[j]][variable_[i]+"Up"  ] , true, verbose-1, folder);
	  saveToRootFile(outputFileNameDown, finalPlots_[variable_[j]][variable_[i]+"Down"] , true, verbose-1, folder);
	}
      }
    }
  }
}

TH1F* distort(const TH1& hist, TString variation, TString variable, double distortParameter, int verbose)
{
  // this function does a linear shape distortion.
  // for variation=="up"/"down" bins that are close in 
  // x to the x value with maximum bin content(xmax)
  // are scaled more/less
  if(verbose>1) std::cout << variable << " (" << variation << ")" << std::endl;
  TH1F* result=(TH1F*)(hist.Clone());
  // parameter of linear smearing
  double a=0;
  if     (variation=="Up"  ) a=1;
  else if(variation=="Down") a=-1;
  else{
    std::cout << "ERROR in function distort: chose variation " << variation << " not known" << std::endl;
    exit(0);
  }   
  double b=hist.GetBinLowEdge(hist.GetNbinsX()+1);
  // take different distribution shapes into account
  double distortParameter2=0;
  if     (variable=="topPt"    )distortParameter2=distortParameter*1.2;
  else if(variable=="ttbarPt"  )distortParameter2=distortParameter;
  else if(variable=="ttbarMass")distortParameter2=distortParameter*1.5;
  else if(variable=="topY"  )distortParameter2=1.0;
  else if(variable=="ttbarY")distortParameter2=1.0;
  else{
    std::cout << "ERROR in function distort: chose variable " << variable << " not known" << std::endl;
    exit(0);
  }
  // SF control variables
  double SFmin=10000;
  double SFmax=0;
  // find maximum
  double xmax= 0.;//hist.GetBinCenter(hist.GetMaximumBin());
  // loop bins
  for(int bin=1; bin<result->GetNbinsX(); ++bin){ 
    // get SF 
    double x= hist.GetBinCenter(bin);
    double SF=linSF(x, xmax, a, b, distortParameter2);
    // avoid SF=0 at maximum
    if(x==xmax){
      double xMaxNext    = hist.GetBinCenter(hist.GetMaximumBin()+1);
      double xMaxPrevious= hist.GetBinCenter(hist.GetMaximumBin()-1);
      // take SF slightly above/below average Sf 
      // of surrounding bins for variation=="up"/"down"
      SF= 0.5*(linSF(x, xMaxNext, a, b, distortParameter2)+linSF(x, xMaxPrevious, a, b, distortParameter2));
    }
    // search max/min SF
    if(verbose>1){
      if(SF>SFmax) SFmax=SF;
      if(SF<SFmin) SFmin=SF;
    }
    // scale bin content
    result->SetBinContent(bin,SF*hist.GetBinContent(bin));
  }
  // print max/min SF
  if(verbose>1){
    std::cout << "minimum SF: "<< SFmin << std::endl;
    std::cout << "maximum SF: "<< SFmax << std::endl;
  }
  // return distorted plot
  return result;
}

double linSF(const double x, const double xmax, const double a, const double b, double distortParameter){
  double SF= a*std::abs(x-xmax)+b;
  if(SF<0){
    std::cout << "ERROR in function SF: negative result!" << std::endl;
    std::cout << a << "*" << "|" << x << "-" << xmax << "|" << "+" << b << "=" << SF << std::endl;
    exit(0);
  }
  return pow(SF, distortParameter);
}
