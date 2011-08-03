#include "basicFunctions.h"
#include "TTree.h"
#include "algorithm"

TH1F* distort(const TH1& hist, TString variation, TString variable, double distortParameter, int verbose);
double linSF(const double x, const double xmax, const double a, const double b, TString variation, double distortParameter);

void analyzeTopDiffXSecMCdependency(TString decayChannel="muon", bool save=false, int verbose=1, TString variation="down")
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
  if     (decayChannel=="muon"    ) analysisFileName="./diffXSecFromSignal/analysisRootFilesWithKinFit/muonDiffXSecSigMadD6TSummer11PF.root";
  else if(decayChannel=="electron") analysisFileName="./diffXSecFromSignal/analysisRootFilesWithKinFit/elecDiffXSecSigMadD6TSummer11PF.root";
  else{
    std::cout << "ERROR: decay channel " << decayChannel << " is no valid choice, use electron or muon!" << std::endl;
    exit(0);
  }
  // file name for output rootfile
  TString outputFileName=analysisFileName;
  outputFileName.ReplaceAll("PF", "MCShapeVar"+variation+"PF");
  // file name for folder where tree is read from
  TString folder="analyzeTopRecoKinematicsKinFit";
  TString genfolder="analyzeTopPartonLevelKinematics";
  if(phaseSpace==true) genfolder+="PhaseSpace";

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
    std::cout << "create rootfile with genbased reweighted distibutions" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "input rootfile: " << analysisFileName << std::endl;
    std::cout << "parton level plots for the calculation of the distortion ";
    std::cout << "SFs are taken from folder: " << genfolder << std::endl;
    std::cout << "used tree for filling distorted reco ";
    std::cout << "level plots: " << folder+"/tree" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "output rootfile: " << outputFileName << std::endl;
    std::cout << "reweighted parton level distributions are stored in folder: " << genfolder << std::endl;
    std::cout << "reweighted reconstruction level distributions are stored in folder: " << folder << std::endl;
  }

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
    inFile->Cp(analysisFileName, outputFileName);
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
    plots_      [variable_[i]+"PartonTruth"]=new TH1F( variable_[i]+"PartonTruth", variable_[i]+"PartonTruth", hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
    plotsScaled_[variable_[i]+"PartonTruth"]=new TH1F( variable_[i]+"PartonTruth", variable_[i]+"PartonTruth", hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
    plots_      [variable_[i]              ]=new TH1F( variable_[i]+"PartonTruth", variable_[i]+"PartonTruth", hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
    plotsScaled_[variable_[i]              ]=new TH1F( variable_[i]              , variable_[i]              , hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
    for(unsigned int j=0; j<variable_.size();++j){
      finalPlots_[variable_[j]+"PartonTruth"][variable_[i]]=new TH1F( variable_[j]+"PartonTruth"+variable_[i]+"SF", variable_[j]+"PartonTruth"+variable_[i]+"SF", hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
      finalPlots_[variable_[j]              ][variable_[i]]=new TH1F( variable_[j]              +variable_[i]+"SF", variable_[j]              +variable_[i]+"SF", hist->GetNbinsX(), hist->GetXaxis()->GetXmin(), hist->GetXaxis()->GetXmax());
    }
  }
  if(verbose>0) std::cout << std::endl;

  // ---
  //    part A: get values for all variables from tree
  // ---
  if(verbose>0) std::cout << std::endl << "part A: get tree entries" << std::endl;
  tree->SetBranchStatus("*",0);
  tree->SetBranchStatus("weight",1);
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
    inFile->GetObject(genfolder+"/"+variable_[i], targetPlot);
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
    // loop all bins
    for(int bin=0; bin<=plotsScaled_[variable_[i]+"PartonTruth"]->GetNbinsX()+1; ++bin){
      plotsScaled_[variable_[i]+"PartonTruth"]=distort(*plots_[variable_[i]+"PartonTruth"], variation, variable_[i], distortParameter, verbose-1);
    }
  }
  
  // B3 calculate SF
  std::map< TString, TH1F* > SF_;
  // loop all variables
  for(unsigned int i=0; i<variable_.size();++i){
    SF_[variable_[i]]=(TH1F*)plotsScaled_[variable_[i]+"PartonTruth"]->Clone();
    SF_[variable_[i]]->Divide(plots_[variable_[i]+"PartonTruth"]);
  }

  // B4 make sure to normalize the distorted plot 
  //    to the same area as the original one
  // -> dont change the absolut amount of events!
  // loop all variables
  for(unsigned int i=0; i<variable_.size();++i){
    double areaSF = plots_      [variable_[i]+"PartonTruth"]->Integral(0,plots_      [variable_[i]+"PartonTruth"]->GetNbinsX()+1);
    areaSF /=       plotsScaled_[variable_[i]+"PartonTruth"]->Integral(0,plotsScaled_[variable_[i]+"PartonTruth"]->GetNbinsX()+1);
    SF_[variable_[i]]->Scale(areaSF);
    plotsScaled_[variable_[i]+"PartonTruth"]->Scale(areaSF);
    if(verbose>1) std::cout << "area SF for " << variable_[i] << ": " << areaSF << std::endl;
  }
  if(verbose>0){
    std::cout << "distortion SF keeps normalization for original ";    
    std::cout << "(phase space) parton level truth distribution" << std::endl;
  }

  // B5 check for negative SF
  // loop all variables
  for(unsigned int i=0; i<variable_.size();++i){
    // loop all bins
    for(int bin=0; bin<=SF_[variable_[i]]->GetNbinsX()+1; ++bin){
      if(SF_[variable_[i]]->GetBinContent(bin)==1){
	std::cout << "ERROR: some distortion SF is 1!" << std::endl;
	exit(1);
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

  // C2 fill scaled and original plot into one canvas
  int canvasNumber=0;
  // loop all variables
  for(unsigned int i=0; i<variable_.size();++i){
    plotCanvas_[canvasNumber]->cd(0);
    plotCanvas_[canvasNumber]->SetTitle(variable_[i]);
    histogramStyle( *plots_      [variable_[i]+"PartonTruth"], 0, false);
    histogramStyle( *plotsScaled_[variable_[i]+"PartonTruth"], 2, false);
    if(plotsScaled_[variable_[i]+"PartonTruth"]->GetMaximum()>plots_[variable_[i]+"PartonTruth"]->GetMaximum()){
      plots_[variable_[i]+"PartonTruth"]->SetMaximum(plotsScaled_[variable_[i]+"PartonTruth"]->GetMaximum());
    }
    plots_      [variable_[i]+"PartonTruth"]->Draw("");
    plotsScaled_[variable_[i]+"PartonTruth"]->Draw("same");
    ++canvasNumber;
  }

  
  // C3 delete obsolete parton level plots needed for SF determination
//   for(unsigned int i=0; i<variable_.size();++i){
//     plots_      [variable_[i]+"PartonTruth"]->Reset();
//     plotsScaled_[variable_[i]+"PartonTruth"]->Reset();
//   }

  // ---
  //    part D: create weighted plots
  // ---
  if(verbose>0) std::cout << std::endl << "part D: use parton level based SF to reweight reco histos" << std::endl;
  // loop all events
  for(unsigned int event=0; event<tree->GetEntries(); ++event){
    tree->GetEntry(event);
    // i: loop all variables (for SF)
    for(unsigned int i=0; i<variable_.size();++i){
      // j: loop all variables (for plot to be scaled)
      for(unsigned int j=0; j<variable_.size();++j){
	double weight=value_["weight"];
	// get distortion SF (from variable i)
	double LepShapeWeight=0;
	double HadShapeWeight=0;
	// for leptonic and hadronic top: get 2xSF (from variable i)
	if(variable_[i].Contains("top")){
	  LepShapeWeight=SF_[variable_[i]]->GetBinContent(SF_[variable_[i]]->FindBin(value_[variable_[i]+"Lep"+"PartonTruth"]));
	  HadShapeWeight=SF_[variable_[i]]->GetBinContent(SF_[variable_[i]]->FindBin(value_[variable_[i]+"Had"+"PartonTruth"]));
	}
	// for other quantities: use one SF only (from variable i)
	else{
	  LepShapeWeight=SF_[variable_[i]]->GetBinContent(SF_[variable_[i]]->FindBin(value_[variable_[i]]));
	  HadShapeWeight=LepShapeWeight;
	}
	// filling for top quantities: fill leptonic and hadronic top quantities in same plot
	if(variable_[j].Contains("top")){
	  // parton truth plots
	  finalPlots_[variable_[j]+"PartonTruth"][variable_[i]]->Fill(value_[variable_[j]+"Lep"+"PartonTruth"], weight*LepShapeWeight);
	  finalPlots_[variable_[j]+"PartonTruth"][variable_[i]]->Fill(value_[variable_[j]+"Had"+"PartonTruth"], weight*HadShapeWeight);
	  // reconstruction level plots
	  finalPlots_[variable_[j]][variable_[i]]->Fill(value_[variable_[j]+"Lep"], weight*LepShapeWeight);
	  finalPlots_[variable_[j]][variable_[i]]->Fill(value_[variable_[j]+"Had"], weight*HadShapeWeight);
	}
	// other quantities: take average of leptonic and hadronic top SF
	else{
	  // parton truth plots
	  finalPlots_[variable_[j]+"PartonTruth"][variable_[i]]->Fill(value_[variable_[j]+"PartonTruth"], weight*0.5*(LepShapeWeight+HadShapeWeight));
	  // reconstruction level plots
	  finalPlots_[variable_[j]][variable_[i]]->Fill(value_[variable_[j]], weight*0.5*(LepShapeWeight+HadShapeWeight));
	}
      }
    }
  }

  // ---
  //    part E: collect all final plots
  // ---
  if(verbose>0) std::cout << std::endl << "part E: collect all final plots" << std::endl;
  // i: loop all variables (for SF)
  for(unsigned int i=0; i<variable_.size();++i){
    // j: loop all variables (for shown plot)
    for(unsigned int j=0; j<variable_.size();++j){
      // fill original/scaled reco plots only into canvas   
      if(i==j){
	char canvname[10];
	sprintf(canvname,"canv%i",canvasNumber);
	plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );
	plotCanvas_[canvasNumber]->cd(0);
	TString title = finalPlots_[variable_[j]][variable_[i]]->GetTitle();
	TString PS="RecoLevel";
	if(title.Contains("PartonTruth")) PS="PartonLevel";
	finalPlots_[variable_[j]][variable_[i]]->SetTitle(variable_[j]+PS+"SFfrom"+variable_[i]);
	plotCanvas_[canvasNumber]->SetTitle(variable_[j]+PS+"SFfrom"+variable_[i]);
	histogramStyle(*finalPlots_[variable_[j]][variable_[i]], 0, false);
	//histogramStyle( *, 2, false);
	finalPlots_[variable_[j]][variable_[i]]->Draw("");
	//->Draw("same");
	++canvasNumber;
      }
    }
  }

  // ---
  //    part F: save weighted plots and control plots
  // ---
  if(save){
    if(verbose>0) std::cout << std::endl << "part F: save rweighted reco histos to output file" << std::endl;
    // i: loop all variables (for SF)
    for(unsigned int i=0; i<variable_.size();++i){
      // j: loop all variables (for shown plot)
      for(unsigned int j=0; j<variable_.size();++j){
	// F1: save control plots: every quantity weighted by every quantity

	// F2: save scaled parton level distribution and reco plot in file
	if(i==j){
	  // parton level plot
	  // attention: the PS one is used
	  saveToRootFile(outputFileName, plotsScaled_[variable_[i]+"PartonTruth"], true, verbose-1, genfolder);
	  // reco plot (weighted with distorted parton level distribution of the same quantity)
	  saveToRootFile(outputFileName, finalPlots_[variable_[j]][variable_[i]] , true, verbose-1, folder   );
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
  if     (variation=="up"  ) a=1;
  else if(variation=="down") a=-1;
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
    double SF=linSF(x, xmax, a, b, variation, distortParameter2);
    // avoid SF=0 at maximum
    if(x==xmax){
      double xMaxNext    = hist.GetBinCenter(hist.GetMaximumBin()+1);
      double xMaxPrevious= hist.GetBinCenter(hist.GetMaximumBin()-1);
      // take SF slightly above/below average Sf 
      // of surrounding bins for variation=="up"/"down"
      SF= 0.5*(linSF(x, xMaxNext, a, b, variation, distortParameter2)+linSF(x, xMaxPrevious, a, b, variation, distortParameter2));
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

double linSF(const double x, const double xmax, const double a, const double b, TString variation, double distortParameter){
  double SF= a*std::abs(x-xmax)+b;
  if(SF<0){
    std::cout << "ERROR in function SF: negative result!" << std::endl;
    std::cout << a << "*" << "|" << x << "-" << xmax << "|" << "+" << b << "=" << SF << std::endl;
    exit(0);
  }
  return pow(SF, distortParameter);
}
