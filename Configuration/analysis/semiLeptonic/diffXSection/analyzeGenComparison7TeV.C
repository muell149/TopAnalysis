#include "basicFunctions.h"

void analyzeGenComparison7TeV(bool save = true, int verbose=0, bool theoryVariations=false){
  
  // !!! run different ttbar MCs OR Theory Variations !!!
  // theoryVariations=false OR true
  // use same binning as in analysis?
  bool analysisBinning=false;
  TString saveNameExt="";

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
  if(verbose>0) std::cout << "opening files" << std::endl;
  if(!theoryVariations){
    file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/combinedDiffXSecSigFall11PF.root"            , "Open"));
    file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/combinedDiffXSecSigPowhegFall11PF.root"      , "Open"));
    file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/combinedDiffXSecSigPowhegHerwigFall11PF.root", "Open"));
    file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun/combinedDiffXSecSigMcatnloFall11PF.root"     , "Open"));
  }

  // save output path
  TString outpath="diffXSecFromSignal/plots/combined/2012/ttgencomparison/";
  // -> create it via: mkdir -p diffXSecFromSignal/plots/combined/2012/ttgencomparison
  
  // list plots of relevance
  if(verbose>0) std::cout << "listing plots" << std::endl;
  std::vector<TString> plotList_, axisLabel_;
  TString plots1D[ ] = {
    // generated full PS quantities    
    "analyzeTopPartonLevelKinematics/ttbarMass",
    "analyzeTopPartonLevelKinematics/ttbarPt"  ,
    "analyzeTopPartonLevelKinematics/ttbarY"   ,
    "analyzeTopPartonLevelKinematics/topMass"  ,  
    "analyzeTopPartonLevelKinematics/topPt"    ,
    "analyzeTopPartonLevelKinematics/topY"     ,
    "analyzeTopPartonLevelKinematics/lepPt"    ,
    "analyzeTopPartonLevelKinematics/lepEta"   ,
    "analyzeTopPartonLevelKinematics/bqPt"     ,
    "analyzeTopPartonLevelKinematics/bqEta"    ,
  };
  TString axisLabel1D[ ] = { 
    // generated full PS quantities
    "parton truth m^{t#bar{t}} #left[GeV#right];rel. #Events;0;50"   ,
    "parton truth p_{T}^{t#bar{t}} #left[GeV#right];rel. #Events;0;1",
    "parton truth y^{t#bar{t}};rel. #Events;0;1"                     ,
    "parton truth m^{t} #left[GeV#right];rel. #Top quarks;0;1"       ,
    "parton truth p_{T}^{t} #left[GeV#right];rel. #Top quarks;0;10"  ,
    "parton truth y^{t};rel. #Top quarks;0;1"                        ,
    "parton truth p_{T}^{lepton} #left[GeV#right];rel. #Events;0;5"  ,
    "parton truth #eta^{lepton};rel. #Events;0;1"                    ,
    "parton truth p_{T}^{b} #left[GeV#right];rel. #b-quarks;0;5"     ,
    "parton truth #eta^{b};rel. #b-quarks;0;1"                       ,
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
  // create variable bin edges
  std::map<TString, std::vector<double> > binning_ = makeVariableBinning(false);

  // ============================
  //  get histos
  // ============================
  // sample enumerator
  unsigned int kMadPy =0;
  unsigned int kPowPy =1;
  unsigned int kPowHer=2;
  unsigned int kMcHer =3;

  unsigned int kStart=kMadPy;
  unsigned int kEnd  =kMcHer+1;

  std::map< TString, std::map <unsigned int, TH1F*> > histo_;
  // loop all plots
  if(verbose>0) std::cout << "looping plots" << std::endl;
  for(int plot=0; plot<(int)plotList_.size(); ++plot){
    // name
    TString name=plotList_[plot];
    if(verbose>1) std::cout << "plot: " << name << std::endl;
    // legend
    TLegend* leg= new TLegend(0.65, 0.65, 0.85, 0.88);
    legendStyle(*leg,"");
    // loop samples
    for( unsigned int sample=kStart; sample<kEnd; ++sample ){
      // sample found indicator
      bool foundPlot=false;
      if(verbose>1) std::cout << " - sample" << sample << std::endl;
      // load histogram
      TH1* targetPlot;
      file_[sample]->GetObject(name, targetPlot);
      if(!targetPlot){
	if(verbose>1) std::cout << "   -> plot NOT found" << std::endl;
      }
      // if it exists
      else{
	if(verbose>1) std::cout << "   -> plot found" << sample << std::endl;
	histo_[name][sample]=(TH1F*)(targetPlot->Clone());
	// rebinning
	double reBinFactor = atof(((string)getStringEntry(axisLabel_[plot],4,";")).c_str());
	TString xSecName=extractxSecName(name);	
	if(analysisBinning&&binning_.count(xSecName)>0){ 
	  // check existence of e.g. binning_["topPt"]
	  if(binning_.count(xSecName)>0){
	    reBinTH1F(*histo_[name][sample], binning_[xSecName], verbose-1);
	    // remove additional bins with 0 width
	    double *newBinLowEdges = new double[binning_[xSecName].size()];
	    newBinLowEdges = &binning_[xSecName].front();
	    histo_[name][sample]= (TH1F*)histo_[name][sample]->Rebin(binning_[xSecName].size()-1, histo_[name][sample]->GetName(), newBinLowEdges); 
	  }
	}
	else if(reBinFactor>1) equalReBinTH1(reBinFactor, histo_, name, sample);
	// normalize to unity
	histo_[name][sample]->Scale(1./histo_[name][sample]->Integral(0,histo_[name][sample]->GetNbinsX()));
	// add legend entry
	if(!foundPlot){
	  foundPlot=true;
	  if(sample==kMadPy ) leg->AddEntry(histo_[name][sample], constMadGraphPythiaLabel, "L");
	  if(sample==kPowPy ) leg->AddEntry(histo_[name][sample], constPowhegPythiaLabel  , "L");
	  if(sample==kPowHer) leg->AddEntry(histo_[name][sample], constPowhegHerwigLabel  , "L");
	  if(sample==kMcHer ) leg->AddEntry(histo_[name][sample], constMcatnloHerwigLabel , "L");
	}
	// histostyle
	histo_[name][sample]->SetStats(false);
	histo_[name][sample]->SetLineWidth(3);
	if(sample==kMadPy ){ histo_[name][sample]->SetLineColor(kBlack)            ; histo_[name][sample]->SetLineStyle(1                ); }
	if(sample==kPowPy ){ histo_[name][sample]->SetLineColor(constPowhegColor  ); histo_[name][sample]->SetLineStyle(constPowhegStyle ); }
	if(sample==kPowHer){ histo_[name][sample]->SetLineColor(constMadgraphColor); histo_[name][sample]->SetLineStyle(constPowhegStyle2); }
	if(sample==kMcHer ){ histo_[name][sample]->SetLineColor(constMcatnloColor ); histo_[name][sample]->SetLineStyle(constMcatnloStyle); }
      }
      // Drawing etc done after progressing last sample
      if(sample==kEnd-1&&histo_[name].count(kStart)>0){
	if(verbose>1) std::cout << "drawing" << std::endl;
	// ============================
	//  create canvas
	// ============================
	char canvname[10];
	sprintf(canvname,"canv%i",plot);    
	plotCanvas_.push_back( new TCanvas( canvname, canvname, 600, 600) );
	TString canvTitle=getStringEntry(name,2)+getStringEntry(name,1);
	if(theoryVariations) canvTitle+="_theoryMods";
	if(analysisBinning) canvTitle+="PAPERBinning";
	canvTitle+="7TeV";
	plotCanvas_[plotCanvas_.size()-1]->SetTitle(canvTitle);
	// min/max (y-axis)
	unsigned int sampleMax=kStart;
	for( unsigned int sample2=kStart+1; sample2<kEnd; ++sample2 ){
	  if(histo_[name].count(sample2)>0&&histo_[name][sample2]->GetMaximum()>histo_[name][sampleMax]->GetMaximum()) sampleMax=sample2;
	}
	if(verbose>1) std::cout << "use max from sample " << sampleMax << std::endl;
	double max = 1.2*histo_[name][sampleMax]->GetMaximum();
	double min = 0.;
	// log plots
	if(getStringEntry(axisLabel_[plot],3,";")=="1"){
	  plotCanvas_[plot]->SetLogy(1);
	  min=0.001;
	  max=exp(1.2*(std::log(max)-std::log(min))+std::log(min));
	}
	if(min==0.&&max>0.001) min+=0.001;
	if(min==1.&&max>1.001) min+=0.001;
	axesStyle(*histo_[name][kStart], getStringEntry(axisLabel_[plot],1,";"), getStringEntry(axisLabel_[plot],2,";"), min, max);
	histo_[plotList_[plot]][kStart]->GetXaxis()->SetNoExponent(true);  
	// adjust range (x-axis)
	double xUp=histo_[name][kStart]->GetXaxis()->GetXmax();
	double xDn=histo_[name][kStart]->GetXaxis()->GetXmin();
	if(name.Contains("topMass")){xDn=165.;xUp=180.;}
	if(name.Contains("lepPt")){xDn=0.;xUp=500.;}
	if(name.Contains("bqPt" )){xDn=0.;xUp=500.;}
	if(name.Contains("analyzeTopPartonLevelKinematics/leadqPt" )){xDn=0.;xUp=500.;}
	if(name.Contains("bbbarMass" )){xDn=0.;xUp=1000.;}
	if(name.Contains("bbbarPt"   )){xDn=0.;xUp=500. ;}
	if(name.Contains("MET"       )){xDn=0.;xUp=1000.;}
	if(xUp!=histo_[name][kStart]->GetXaxis()->GetXmax()||xDn!=histo_[name][kStart]->GetXaxis()->GetXmin()){
	  if(verbose>1) std::cout << "resetting x range: " << xDn << ".." << xUp << std::endl;
	  for( unsigned int sample2=kStart; sample2<kEnd; ++sample2 ){
	    if(histo_[name].count(sample2)>0) histo_[name][sample2]->GetXaxis()->SetRangeUser(xDn,xUp-0.000001);
	  }
	}
	// ============================
	//  plotting
	// ============================
	if(verbose>1) std::cout << "draw MadGraph" << std::endl;
	TH1F* temp=(TH1F*)(histo_[name][kStart]->Clone());
	temp->GetXaxis()->SetTitle("");
	temp->GetXaxis()->SetLabelSize(0.0);
	temp->Draw("AXIS");
	histo_[name][kStart]->Draw("hist same");
	for( unsigned int sample2=kStart+1; sample2<kEnd; ++sample2 ){
	  if(histo_[name].count(sample2)>0){
	    if(verbose>1) std::cout << "draw sample " << sample2 << "/" << kEnd << std::endl;
	    histo_[name][sample2]->Draw("hist same");
	  }
	}
	if(verbose>1) std::cout << "draw legend" << std::endl;
	//leg->SetHeader(getStringEntry(axisLabel_[plot],1,";"));
	leg->DrawClone("same");
	DrawLabel(getStringEntry(axisLabel_[plot],1,";"), 0.65, 0.03, 0.85, 0.08);
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
	if(verbose>1) std::cout << "draw labels"  << std::endl;
	//sellabel->Draw("same");
	DrawDecayChLabel("e/#mu + Jets Combined");
	DrawCMSLabels(false, 0., 0.04, true, true, true);
	// ratio
	bool ratio=true;
	if(name.Contains("topMass")) ratio=false; 
	if(ratio){
	  if(verbose>1) std::cout << "draw ratios " << std::endl;
	  bool one=true;
	  for( unsigned int sample2=kStart; sample2<kEnd; ++sample2 ){
	    if(histo_[name].count(sample2)>0){
	      if(verbose>1) std::cout << "  for sample " << sample2 << "/" << kMcHer << std::endl;
	      std::vector<double> err_=std::vector<double>(0);
	      //for(int bin=1; bin<=histo_[name][kStart]->GetNbinsX(); ++bin){
	      //  double b =histo_[name][kStart]->GetBinContent(bin);
	      //  double Db=sqrt(b);
	      //  double a =histo_[name][sample2]->GetBinContent(bin);
	      //  double Da=sqrt(a);
	      //  err_.push_back(sqrt((a*a*Db*Db)/(b*b*b*b)+(Da*Da)/(b*b)));
	      //}
	      //gStyle->SetErrorX(0.5);
	      TString drawoption=  one ? "hist" : "hist same";
	      if(verbose>1) std::cout << "  with drawoption: " << drawoption << std::endl;
	      one=false;
	      TString denumLabel="PowhegHerwig";
	      double minRat=0.25;
	      double maxRat=2.2;
	      drawRatio(histo_[name][sample2], histo_[name][kPowHer], minRat, maxRat, myStyle, verbose, err_, "generator", denumLabel, drawoption, histo_[name][sample2]->GetLineColor(), false, 0.2);
	    }
	  }
	}
	// save topPt in extra rootfile
	if(name.Contains("topPt")){
	  plotCanvas_[plotCanvas_.size()-1]->SetTitle(getStringEntry(name,2));
	  saveToRootFile("topPt7TeVSimulationComparison.root", plotCanvas_[plotCanvas_.size()-1], true, 0,"");
	  plotCanvas_[plotCanvas_.size()-1]->SetTitle(canvTitle);
	}

      }
    }
    delete leg;
  }
  if(save){
    if(verbose==0) gErrorIgnoreLevel=kWarning;
    if(verbose>1) std::cout << "saving"  << std::endl;
    TString filename="topComparison7TeV";
    if(theoryVariations) filename+="_theoryMods";
    saveCanvas(plotCanvas_, outpath, filename, true, true);
  }
}
