// --------------------------------------------------------------
// This macro calculates the purity, stability and efficiency
// for a user-defined fixed binning.
// (Modified version of the macro findBinning.C)
// --------------------------------------------------------------


#include <sstream>
#include <string>
#include <iostream>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TPaletteAxis.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TLegend.h>
#include "TTree.h"
#include "algorithm"
#include <TMath.h>
#include "HHStyle.h"
#include "basicFunctions.h"

void purityStabilityEfficiency(TString variable = "ttbarPt", bool save=false, TString lepton="muon", 
			       TString inputFolderName="RecentAnalysisRun", bool plotEfficiency = true, 
			       bool plotEfficiencyPhaseSpace = true, bool plotEfficiency2 = false, double chi2Max=99999, int verbose=0)
{
  // ARGUMENTS of function:
  // variable:       choose variable to plot, e.g.:
  //                 topPt, topY, ttbarPt, ttbarY, ttbarMass, lepPt, lepY
  // save:           save the purity and stability canvas 
  // lepton:         "muon" or "elec"
  // plotEfficiency: in addition to purity and stability also efficiency*acceptance is plotted (if true)
  // plotEfficiencyPhaseSpace: in addition to purity, stability, efficiency*acceptance also 
  //                           efficiency in restricted phase space (i.e. Acceptance=1) is plotted (if true)
  bool useTree=true; // use default 2D histo or create 2D histo from tree, allows chi2 cuts
  if(!useTree) chi2Max=99999; // can be done only with tree
  // output folder in case of saving the canvases:
  TString outputFolder = "./diffXSecFromSignal/plots/"+lepton+"/2011/binning";
  if(useTree&&chi2Max<100){ 
    plotEfficiencyPhaseSpace = false;
    plotEfficiency = false;
    plotEfficiency2= false;
  }
 
  // input file
  TFile* myFile1 = new TFile("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/"+TopFilename(kSig, sysNo, (std::string)lepton), "READ");
  TFile* myFile2 = new TFile("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/"+TopFilename(kSig, sysNo, (std::string)lepton), "READ");
 
  if(lepton=="electron") lepton="elec";
    
  // determine here the binning:
  // Attention: binning ALWAYS should start from left boundary of first and bin of the input file;
  // it ends with the last bin of the input file even if this is not part of the array defined below
  
  std::map<TString, std::vector<double> > binningMap = makeVariableBinning();
  std::vector<double> xBins = binningMap[variable];
  int NxBins = xBins.size()-1;  
  
  // pt
  // double xBins[] = {0, 60, 120, 200, 280, 400};
  // y
  // double xBins[] = {-5., -2.5, -1.5, -1., -0.5, 0, 0.5, 1., 1.5, 2.5};
  // ttbar pt
  // double xBins[] = {0, 20, 60, 110, 200};
  // ttbar Y
  // double xBins[] = {-5., -1.3, -0.9, -0.6, -0.3, 0., 0.3, 0.6, 0.9, 1.3};
  // ttbarMass
  // double xBins[] = {0, 400, 500, 630, 900};
  // double xBins[] = {0, 345, 410, 480, 580, 750};
  // Korea:
  // double xBins[] = {0, 350, 400, 450, 500, 550,600,700,800};
  // lepPt
  // double xBins[] = {0., 20., 25., 30., 35., 40., 45., 50., 60., 70., 80., 100., 120., 150., 200., 275., 400., 1200.};
  // lepEta
  // double xBins[] = {-5., -2.5, -2.1, -1.8, -1.5, -1.2, -0.9, -0.6, -0.3, 0., 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.5, 5.};
  // b-quark Pt
  // double bqPtBins[]  = {0, 30, 60, 95, 140, 200, 400 };
  // b-quark Eta 
  // double bqEtaBins[] = {-5.0, -2.5, -1.5, -1.0, -0.5, 0., 0.5, 1.0, 1.5, 2.5, 5.0};
  //int NxBins = sizeof(xBins)/sizeof(double);

  if(verbose>0) std::cout << "size of xBins: " << NxBins << std::endl;
  
  // change x axis range
  double rangeUserLeft = -1e6;
  double rangeUserRight = 1e6;
  if ( variable == "topPt")          { rangeUserLeft = 0         ; rangeUserRight = 400-0.001; }
  else if ( variable == "topY")      { rangeUserLeft = -2.5+0.001; rangeUserRight = 2.5-0.001; }
  else if ( variable == "ttbarPt")   { rangeUserLeft = 0         ; rangeUserRight = 300-0.001; }
  else if ( variable == "ttbarY")    { rangeUserLeft = -1.3+0.001; rangeUserRight = 1.3-0.001; }
  else if ( variable == "ttbarMass") { rangeUserLeft = 345+0.001 ; rangeUserRight = 1200-0.001;}
  else if ( variable == "lepPt" )    { rangeUserLeft = 30        ; rangeUserRight = 400-0.001; }
  else if ( variable == "lepEta")    { rangeUserLeft = -2.1+0.001; rangeUserRight = 2.1-0.001; }
  else if ( variable == "bqPt")      { rangeUserLeft = 0         ; rangeUserRight = 350-0.001; useTree=false;}
  else if ( variable == "bqEta")     { rangeUserLeft = -2.4+0.001; rangeUserRight = 2.4-0.001; useTree=false;}

  //else if ( variable == "lepPt"  && lepton == "muon")    { rangeUserLeft = 20  ; rangeUserRight = 400-0.001; }
  //else if ( variable == "lepPt"  && lepton == "elec")    { rangeUserLeft = 30  ; rangeUserRight = 400-0.001; }
  //else if ( variable == "lepEta" && lepton == "muon")    { rangeUserLeft = -2.1; rangeUserRight = 2.1-0.001; }
  //else if ( variable == "lepEta" && lepton == "elec")    { rangeUserLeft = -2.5; rangeUserRight = 2.5-0.001; }
    
  // make a nice style
  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  myStyle.cd();
  TGaxis::SetMaxDigits(2);
  gROOT->SetStyle("HHStyle");
  gROOT->ForceStyle();	

  // ---
  //    get the 2D histogram
  // ---
  // x-Axis should be generated value, y-Axis should be reconstructed value
  TH2F* myHist2d = (TH2F*)(((TH2F*)myFile1->Get("analyzeTopRecoKinematicsKinFit/"+variable+"_"))->Clone());
  // empty histogram
  if(useTree) myHist2d->Reset("ICES"); // Scale(0);
  // create response matrix with and without efficiency correction in final binning; will be only filled if useTree==true
  TH2F* responseMatrix = new TH2F("responseMatrix", "responseMatrix", NxBins, &xBins[0], NxBins, &xBins[0]);
  TH2F* migrationMatrix = new TH2F("migrationMatrix", "migrationMatrix", NxBins, &xBins[0], NxBins, &xBins[0]);
  // create pointer to avoid problems with object persistence  
  TH1F* chi2eff = NULL;
  TH1F* all     = NULL;
  // loading tree
  if (useTree){
    TTree *tree=(TTree*)(myFile1->Get("analyzeTopRecoKinematicsKinFit/tree"));
    if(!tree||tree->IsZombie()){
      std::cout << "there seems to be a problem with the chosen tree " << "analyzeTopRecoKinematicsKinFit/tree" << std::endl;
      exit(0);  
    }
    // list relevant tree entries
    std::vector<TString> variable_;
    if(variable.Contains("top")){
      variable_.push_back(variable+"Lep");
      variable_.push_back(variable+"Had");
    }
    else if(variable.Contains("bqPt")){
      variable_.push_back("lepBPt");
      variable_.push_back("hadBPt");
    }  
    else if(variable.Contains("bqEta")){
      variable_.push_back("lepBEta");
      variable_.push_back("hadBEta");
    }
    else variable_.push_back(variable);
    // container for values read from tree
    std::map< TString, float > value_;
    // container for chi2 cut efficiency
    chi2eff = (TH1F*)(((TH1F*)myFile1->Get("analyzeTopPartonLevelKinematicsPhaseSpace/"+variable))->Clone());
    chi2eff->Scale(0);
    all=(TH1F*)chi2eff->Clone();
  
  // initialize map entries with 0 
  // to avoid problems with the map re-ordering
  // when new entries are added
    value_["weight"]=0;
    for(unsigned int i=0; i<variable_.size(); ++i){
      value_[variable_[i]]=0;
      value_[variable_[i]+"PartonTruth"]=0;
    }
    // initialize branches
    tree->SetBranchStatus("*",0);
    tree->SetBranchStatus("weight",1);
    tree->SetBranchAddress("weight",(&value_["weight"]));
    tree->SetBranchStatus("chi2",1);
    tree->SetBranchAddress("chi2",(&value_["chi2"]));
    for(unsigned int i=0; i<variable_.size(); ++i){
      // activate branches
      tree->SetBranchStatus(variable_[i],1);
      tree->SetBranchStatus(variable_[i]+"PartonTruth",1);
      // save branch values in map
      tree->SetBranchAddress(variable_[i],(&value_[variable_[i]]));
      tree->SetBranchAddress(variable_[i]+"PartonTruth",(&value_[variable_[i]+"PartonTruth"]));
    }
    // loop all events to fill plots
    for(unsigned int event=0; event<tree->GetEntries(); ++event){
      tree->GetEntry(event);
      double weight=value_["weight"];
      double chi2=value_["chi2"];
      for(unsigned int i=0; i<variable_.size(); ++i){
	double rec =value_[variable_[i]];
	double gen =value_[variable_[i]+"PartonTruth"];
	if(rec==-9999||gen==-9999){ 
	  std::cout << "variable " << variable << " is not filled properly:" << std::endl;
	  std::cout << "rec " <<  variable_[i] << ": " << rec << std::endl;
	  std::cout << "gen " <<  variable_[i]+"PartonTruth" << ": " << gen << std::endl;
	  exit(0);
	}
	// apply chi2 cut
	if(chi2<chi2Max){
	  myHist2d       ->Fill(gen, rec, weight);
	  responseMatrix ->Fill(gen, rec, weight);
	  // fill events passing chi2
	  chi2eff->Fill(rec, weight);
	}
	// fill all events
	all->Fill(rec, weight);
      }
    }
  }

  int xbins = myHist2d->GetNbinsX();
  double xmax = myHist2d->GetXaxis()->GetXmax();
  //double xmin = myHist2d->GetXaxis()->GetXmin();
  
  // draw the obtained histo
  TCanvas* Canv1 = new TCanvas("analyzeTopRecoKinematicsKinFitCorr","analyzeTopRecoKinematicsKinFitCorr",600,600);
  Canv1->cd();
  Canv1->SetRightMargin(0.1);
  myHist2d->SetStats(kFALSE);
  myHist2d->GetXaxis()->SetTitle("gen");
  myHist2d->GetYaxis()->SetTitle("rec");
  //myHist2d->Draw("colz");
  myHist2d->Draw("");
  
  // initialize variables
  int numberOfBins=0;
  vector<double> binvec;

  vector<double> purityvec;
  double purity=0.;
  double puritydenom=0.;

  vector<double> stabilityvec;
  double stability=0.;
  double stabilitydenom=0.;

  double myenum=0.;

  int iSave=0;
  
  // calculate purity and stability
  // loop over bins of one axis of 2D histogram
  // (need to be the same binning for x and y anyway!)
  for(int i=1; i<=xbins; i++)
    {
      // save bin number which will be the lower edge of the final bin
      if(!iSave)iSave=i;
      // loop over bins of the other axis of 2D histogram
      for(int j=0; j<=xbins+1; j++)
      {
	// denominator for purity (number of reconstructed events)
	puritydenom+=myHist2d->GetBinContent(j,i);
	// denominator for stability (number of generated events)
	stabilitydenom+=myHist2d->GetBinContent(i,j);
      }
      // loop over bins starting from lower edge of the final bin
      for(int k=iSave; k<=i; k++)
	{
	  // loop over bins starting from lower edge of the final bin
	  for(int l=iSave; l<=i; l++)
	    {
	      // enumerator
	      myenum+=myHist2d->GetBinContent(l,k);
	    }
	}
      // calculate purity (avoid dividing by zero)
      if(puritydenom)purity=myenum/puritydenom;
      else purity=0;
      // calculate stability (avoid dividing by zero)
      if(stabilitydenom)stability=myenum/stabilitydenom;
      else stability=0;

      if( (numberOfBins+1 < NxBins+1 && myHist2d->GetBinCenter(i+1) > xBins[numberOfBins+1]) || i==xbins){
	    // write results to vector
	    purityvec.push_back(purity);
	    stabilityvec.push_back(stability);
	    binvec.push_back(myHist2d->GetBinLowEdge(iSave));
	    // count bins
	    numberOfBins++;
	    // reset variables
	    puritydenom=0.;
	    stabilitydenom=0.;
	    iSave=0;
	  }
      myenum=0.;
    }
  binvec.push_back(xmax);

  // print the binning
  if(verbose>0){
    cout<<numberOfBins<<" bins: {";
    for(int i=0; i<numberOfBins; i++)
      {
	cout<<binvec[i]<<", ";
      }
    cout<<xmax<<"}"<<endl;
  }
  
  // draw stability & purity histogram with the determined binning
  TH1F* purityhist    = new TH1F("purityhist"   ,"purityhist"   ,numberOfBins, &(binvec.front()));
  TH1F* stabilityhist = new TH1F("stabilityhist","stabilityhist",numberOfBins, &(binvec.front()));
  
  // ----------- Efficiency calculation--------------------------------

  // get histogram of generated quantity
  TH1F* genHist = (TH1F*)(((TH1F*)myFile1->Get("analyzeTopPartonLevelKinematics/"+variable))->Clone());
  //genHist->SetStats(kFALSE);
  TCanvas* Canv2 = new TCanvas("analyzeTopPartonLevelKinematics","analyzeTopPartonLevelKinematics",600,600);
  Canv2->cd();
  genHist->Draw();
  // rebin histogram of generated quantity
  genHist = (TH1F*)genHist->Rebin(binvec.size()-1, genHist->GetName(), &(binvec.front()));
  // get histogram of reconstructed quantity
  TH1F* effHist = (TH1F*)(((TH1F*)myFile1->Get("analyzeTopRecoKinematicsKinFit/"+variable))->Clone());
  //effHist->SetStats(kFALSE);
  TCanvas* Canv3 = new TCanvas("analyzeTopRecoKinematicsKinFit","analyzeTopRecoKinematicsKinFit",600,600);
  Canv3->cd();
  effHist->Draw();
  // rebin histogram of reconstructed quantity
  effHist = (TH1F*)effHist->Rebin(binvec.size()-1, effHist->GetName(), &(binvec.front()));
  TH1F* effHistPS=(TH1F*)(effHist->Clone());
  // calculate efficiency histogram
  effHist->Divide(genHist);
  
  // if also effiency in limited phase space interesting:
  TH1F* genHistPS = 0;
  if(plotEfficiencyPhaseSpace){
    // get histogram of generated quantity
    genHistPS = (TH1F*)(((TH1F*)myFile1->Get("analyzeTopPartonLevelKinematicsPhaseSpace/"+variable))->Clone());
    TCanvas* Canv4 = new TCanvas("analyzeTopPartonLevelKinematicsPhaseSpace","analyzeTopPartonLevelKinematicsPhaseSpace",600,600);
    Canv4->cd();
    //genHistPS->SetStats(kFALSE);
    genHistPS->Draw();
    // rebin histogram of generated quantity
    genHistPS = (TH1F*)genHistPS->Rebin(binvec.size()-1, genHistPS->GetName(), &(binvec.front()));
    //genHistPS->Draw("");
    // calculate efficiency histogram
    effHistPS->Divide(genHistPS);
  }
  
    // if 2 effiency plots are supposed to be compared:
  TH1F* effHist2 = 0;
  if(plotEfficiency2){
    // get histogram of generated quantity
    TH1F* genHist2 = (TH1F*)(((TH1F*)myFile2->Get("analyzeTopPartonLevelKinematics/"+variable))->Clone());
    TCanvas* Canv4 = new TCanvas("analyzeTopPartonLevelKinematics2","analyzeTopPartonLevelKinematics2",600,600);
    Canv4->cd();
    genHist2->Draw();
    // rebin histogram of generated quantity
    genHist2 = (TH1F*)genHist2->Rebin(binvec.size()-1, genHist2->GetName(), &(binvec.front()));
    effHist2 = (TH1F*)(((TH1F*)myFile2->Get("analyzeTopRecoKinematicsKinFit/"+variable))->Clone());
    // rebin histogram of reconstructed quantity
    effHist2 = (TH1F*)effHist2->Rebin(binvec.size()-1, effHist2->GetName(), &(binvec.front()));
    // calculate efficiency histogram
    effHist2->Divide(genHist2);
  }

  for(int i=0; i<numberOfBins; i++)
    {
      purityhist->SetBinContent(i+1,purityvec[i]);
      stabilityhist->SetBinContent(i+1,stabilityvec[i]);
    }
  purityhist->SetTitle("");
  TString xtitle = "";
  if(variable.Contains("Pt"))xtitle+="p_{T}";
  else if(variable.Contains("Y"))xtitle+="y";
  else if(variable.Contains("Eta"))xtitle+="#eta";
  else if(variable.Contains("Mass"))xtitle+="m";
  if(variable.Contains("top"))xtitle+="^{t and #bar{t}}";
  else if(variable.Contains("ttbar"))xtitle+="^{t#bar{t}}";
  else if(variable.Contains("lep"))xtitle+="^{l}";
  if(variable.Contains("Pt"))xtitle+=" #left[#frac{GeV}{c}#right]";
  else if(variable.Contains("Mass"))xtitle+=" #left[#frac{GeV}{c^{2}}#right]";
  if(variable=="topWAngle")xtitle="Angle(top,W)";
  purityhist->GetXaxis()->SetTitle(xtitle);
  purityhist->GetXaxis()->SetNoExponent(true);
  purityhist->GetYaxis()->SetNoExponent(true);

  //purityhist->GetXaxis()->SetTitleSize  ( 0.07);
  //purityhist->GetXaxis()->SetTitleColor (    1);
  //purityhist->GetXaxis()->SetTitleOffset(  0.95);
  //purityhist->GetXaxis()->SetTitleFont  (   62);
  //purityhist->GetXaxis()->SetLabelSize  ( 0.07);
  //purityhist->GetXaxis()->SetLabelFont  (   62);
  //purityhist->GetXaxis()->SetNdivisions (  505);
  purityhist->GetXaxis()->SetRangeUser  (rangeUserLeft, rangeUserRight);
  
  //purityhist->GetYaxis()->SetTitleSize  ( 0.07);
  //purityhist->GetYaxis()->SetTitleColor (    1);
  //purityhist->GetYaxis()->SetTitleOffset(  1.0);
  //purityhist->GetYaxis()->SetTitleFont  (   62);
  //purityhist->GetYaxis()->SetLabelSize  ( 0.07);
  //purityhist->GetYaxis()->SetLabelFont  (   62);
  //purityhist->GetYaxis()->SetNdivisions (  505);
  purityhist->GetYaxis()->SetRangeUser  (0, 0.2);

  purityhist->SetMinimum(0.);
  //double max=purityhist->GetMaximum();
  //if(stabilityhist->GetMaximum()>max)max=stabilityhist->GetMaximum();
  //purityhist->SetMaximum(1.1*max);
  purityhist->SetMaximum(1.0);
  purityhist->SetLineColor(2);
  purityhist->SetLineWidth(4);
  stabilityhist->SetLineColor(4);
  stabilityhist->SetLineStyle(2);
  stabilityhist->SetLineWidth(4);
  effHist->SetLineColor(1);
  effHist->SetLineStyle(1);
  effHist->SetLineWidth(4);
  effHist->GetXaxis()->SetNoExponent(true);
  effHist->GetYaxis()->SetNoExponent(true);
  purityhist->SetStats(kFALSE);

  TCanvas* purstab = new TCanvas("purstab","purstab",600,600);
  //gPad->SetBottomMargin(0.19);
  purstab->cd();
  purstab->SetGrid(1,1);
  purityhist->Draw();
  stabilityhist->Draw("same");
  if(plotEfficiency)effHist->Draw("same");
  if(plotEfficiencyPhaseSpace){
    effHistPS->SetLineColor(1);
    effHistPS->SetLineStyle(2);
    effHistPS->SetLineWidth(4);
    effHistPS->Draw("same");
  }
  if(plotEfficiency2){
    effHist2->SetLineColor(1);
    effHist2->SetLineStyle(2);
    effHist2->SetLineWidth(4);
    effHist2->Draw("same");
  }
  // chi2 cut efficiency
  if(useTree && chi2Max<100){    
    chi2eff = (TH1F*)chi2eff->Rebin(binvec.size()-1, chi2eff->GetName(), &(binvec.front()));
    all     = (TH1F*)all    ->Rebin(binvec.size()-1, all->GetName()    , &(binvec.front()));
    chi2eff->Divide(all);
    chi2eff->SetLineColor(1);
    //chi2eff->SetLineStyle(2);
    chi2eff->SetLineWidth(4);
    chi2eff->Draw("same");
  }
  if (lepton=="muon") DrawDecayChLabel("#mu + Jets");
  else if(lepton=="elec") DrawDecayChLabel("e + Jets");
  double legEdge = 0.4;
  if(plotEfficiency)legEdge = effHist->GetMinimum();
  TLegend* leg=new TLegend(0.47,0.68,0.67,0.87);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(purityhist,   "Purity"    ,"l");
  leg->AddEntry(stabilityhist,"Stability" ,"l");
  //purityhist->GetYaxis()->SetRangeUser  (0, 0.2);
  if(plotEfficiency)leg->AddEntry(effHist,"eff.*A","l");
  //if(plotEfficiency)leg->AddEntry(effHist,"Eff*A full PS Spring11","l");
  if(plotEfficiencyPhaseSpace)leg->AddEntry(effHistPS,"eff. in restr. PS","l");
  if(plotEfficiency2)leg->AddEntry(effHist2,"eff.*A full PS Summer11","l");
  if(useTree && chi2Max<100){
    TString entry="#chi^{2} < ";
    entry+=chi2Max;
    entry+=" cut eff.";
    leg->AddEntry(chi2eff,entry,"l");
  }
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  if(variable == "topPt"||chi2Max<100) leg->Draw("same");
  
  // canvas for legend
  //TCanvas* purstabLeg = new TCanvas("purstabLeg","purstabLeg",600,300);
  //leg->Draw("same");
  
  // create histo with efficiency counting all events stemming from a gen bin that are reconstructed anywhere 
  // wrt. all events initially created in that bin, which are reconstructed or not 
  TH1F* effHistGen = new TH1F("effHistGen","effHistGen", NxBins, &xBins[0]);
  TCanvas* CanvEffGen = new TCanvas("CanvEffGen","CanvEffGen",600,600);
  
  // calculate response matrix as probability matrix: divide number in bin(gen,rec) by number of all
  // initially generated events in the gen bin (i.e. also if they have been lost due to inefficiencies);
  // if restricted phase space shall be plotted, it is calculated for that one
  TCanvas* CanvResponseMatrix = new TCanvas("CanvResponseMatrix","CanvResponseMatrix",600,600);
  // additionally: calculate response matrix that only includes migration effects, not limited acc. or eff.
  TCanvas* CanvMigrationMatrix = new TCanvas("CanvMigrationMatrix","CanvMigrationMatrix",600,600);
  if(useTree){
    for(int iGenBin=1; iGenBin <=NxBins; iGenBin++){
      double allRecEvtsFromGenBin=0.;
      double effDenom=-1.;
      double effGen=0.;
      double effDenomMigrationOnly = responseMatrix->Integral(iGenBin,iGenBin,0,NxBins+1);
      if(plotEfficiencyPhaseSpace && genHistPS->GetBinContent(iGenBin)) effDenom=genHistPS->GetBinContent(iGenBin);
      else if(genHist->GetBinContent(iGenBin))                          effDenom=genHist  ->GetBinContent(iGenBin);
      
      for(int iRecBin=1; iRecBin <=NxBins; iRecBin++){
	double binContentResponse=0.;
	double binContentMigration=0.;
	if(effDenom>0)              binContentResponse  = responseMatrix->GetBinContent(iGenBin, iRecBin)/ effDenom;
	if(effDenomMigrationOnly>0) binContentMigration = responseMatrix->GetBinContent(iGenBin, iRecBin)/ effDenomMigrationOnly;
	//binContent=99;
//  	if(verbose>1) std::cout<<"num= "<<responseMatrix->GetBinContent(iGenBin, iRecBin) <<"; denom= "<<effDenom<<"; binContentResponse= "<< binContent<<std::endl;
	allRecEvtsFromGenBin+=responseMatrix->GetBinContent(iGenBin, iRecBin);
	responseMatrix  ->SetBinContent(iGenBin, iRecBin, binContentResponse);
	migrationMatrix ->SetBinContent(iGenBin, iRecBin, binContentMigration);
      }
      effGen=(double)allRecEvtsFromGenBin/effDenom;
//    if(verbose>1){
// 	std::cout<<"-------------------------"<<std::endl;
// 	std::cout<<"EffNum= "<<allRecEvtsFromGenBin<<"; Eff.= "<<effGen <<std::endl;
// 	std::cout<<"effDenomMigrationOnly= "<<effDenomMigrationOnly <<std::endl;
// 	std::cout<<"-------------------------"<<std::endl;
//    }
      effHistGen->SetBinContent(iGenBin, effGen);
    }
  
  // draw responseMatrix incl. eff.
  CanvResponseMatrix->cd();
  CanvResponseMatrix->SetRightMargin(0.2);
  responseMatrix->SetStats(kFALSE);
  responseMatrix->GetXaxis()->SetTitle("gen "+xtitle);
  responseMatrix->GetYaxis()->SetTitle("rec "+xtitle);
  responseMatrix->GetXaxis()->SetRangeUser(rangeUserLeft,rangeUserRight);
  responseMatrix->GetYaxis()->SetRangeUser(rangeUserLeft,rangeUserRight);
  responseMatrix->GetXaxis()->SetNoExponent(true);
  responseMatrix->GetYaxis()->SetNoExponent(true);
  responseMatrix->GetZaxis()->SetNoExponent(true);
  responseMatrix->GetZaxis()->SetRangeUser(0,0.3);
  responseMatrix->SetTitle("Response Matrix - Including Efficiency");
  responseMatrix->Draw("COLZ");
  //TPaletteAxis *palette = (TPaletteAxis*)responseMatrix->GetListOfFunctions()->FindObject("palette");
  //gPad->Update();
  if(plotEfficiencyPhaseSpace) DrawLabel("Full Response Matrix - Migration and Efficiency",gStyle->GetPadLeftMargin(),1.0-gStyle->GetPadTopMargin(),1.-gStyle->GetPadRightMargin(),1.,12,0.03);
  else DrawLabel("Full Response Matrix - Migration and Eff.*Acc.",gStyle->GetPadLeftMargin(),1.0-gStyle->GetPadTopMargin(),1.-gStyle->GetPadRightMargin(),1.,12,0.03);
  
  // draw migrationMatrix w/o eff.
  CanvMigrationMatrix->cd();
  CanvMigrationMatrix->SetRightMargin(0.2);
  migrationMatrix->SetStats(kFALSE);
  migrationMatrix->GetXaxis()->SetTitle("gen "+xtitle);
  migrationMatrix->GetYaxis()->SetTitle("rec "+xtitle);
  migrationMatrix->GetXaxis()->SetRangeUser(rangeUserLeft,rangeUserRight);
  migrationMatrix->GetYaxis()->SetRangeUser(rangeUserLeft,rangeUserRight);
  migrationMatrix->GetXaxis()->SetNoExponent(true);
  migrationMatrix->GetYaxis()->SetNoExponent(true);
  migrationMatrix->GetZaxis()->SetNoExponent(true);
  migrationMatrix->GetZaxis()->SetRangeUser(0,1);
  migrationMatrix->SetTitle("Response Matrix - Migration Only");
  //gStyle->SetPaintTextFormat("3.2f");
  migrationMatrix->Draw("COLZ");
  DrawLabel("Response Matrix - Migration Only",gStyle->GetPadLeftMargin(),1.0-gStyle->GetPadTopMargin(),1.-gStyle->GetPadRightMargin(),1.,12,0.03);
  
  // draw effGen together with effective efficiencies from bin-by-bin
  CanvEffGen->cd();
  effHistGen->GetXaxis()->SetTitle("gen "+xtitle);
  effHistGen->GetXaxis()->SetNoExponent(true);
  effHistGen->GetYaxis()->SetNoExponent(true);
  effHistGen->SetLineColor(kGreen+2);
  effHistGen->SetLineStyle(1);
  effHistGen->SetLineWidth(4);
  effHistGen->GetXaxis()->SetRangeUser  (rangeUserLeft, rangeUserRight);
  effHistGen->GetYaxis()->SetRangeUser  (0., 0.5);
  effHistGen->Draw("");
  if(plotEfficiency)           effHist->Draw("same");
  if(plotEfficiencyPhaseSpace) effHistPS->Draw("same");
  
  TLegend* leg2=new TLegend(0.2,0.68,0.67,0.87);
  leg2->SetTextSize(0.03);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  if(plotEfficiencyPhaseSpace) leg2->AddEntry(effHistGen,   "Pure eff. in restr. PS (no migration)"    ,"l");
  else                         leg2->AddEntry(effHistGen,   "Pure eff.*A (no migration)"    ,"l");
  if(plotEfficiency)           leg2->AddEntry(effHist,"eff.*A (bin-by-bin)","l");
  if(plotEfficiencyPhaseSpace) leg2->AddEntry(effHistPS,"eff. in restr. PS (bin-by-bin)","l");
  leg2->Draw();
}
  
  if(save){
    if(verbose==0) gErrorIgnoreLevel=kWarning; 
    TString chi="";
    if(chi2Max<100){ 
      chi+="chi";
      chi+=chi2Max;
    }
    purstab->Print(outputFolder+"/purStabEff_"+lepton+"_"+variable+chi+".png");
    purstab->Print(outputFolder+"/purStabEff_"+lepton+"_"+variable+chi+".eps");
    if(useTree){
      CanvResponseMatrix->Print(outputFolder+"/responseMatrix_"+lepton+"_"+variable+chi+".png");
      CanvMigrationMatrix->Print(outputFolder+"/migrationMatrix_"+lepton+"_"+variable+chi+".png");
      CanvEffGen->Print(outputFolder+"/pureGenEff_"+lepton+"_"+variable+chi+".png");
    }
    if(verbose>0) std::cout<<"Canvas with purity and stability plots is saved in "<<outputFolder<<std::endl;
  }

  // control value for pur/stab
  double minMigr=0.4;
  // print range of migration variables
  double maxStab=0.;
  double maxPur =0.;
  double minStab=1.;
  double minPur =1.;
  int purityMinimumBin=0;
  int purityMaximumBin=0;
  int stabilityMinimumBin=0;
  int stabilityMaximumBin=0;
  int Nbins=0;
  int NPurok=0;
  int NStabok=0;
  // loop bins
  for(int bin=1; bin<=purityhist->GetNbinsX(); ++bin){
    // check range
    if(purityhist->GetBinCenter(bin)>=rangeUserLeft&&purityhist->GetBinCenter(bin)<=rangeUserRight){
      // migration in this bin
      double TMPStab=stabilityhist->GetBinContent(bin);
      double TMPPur =purityhist   ->GetBinContent(bin);
      if(TMPStab<1.&&TMPPur>0.){
	// count all bins used for measurement
	++Nbins;
	// search for min/max values
	if(TMPStab<1.&&TMPStab>maxStab){ maxStab= TMPStab; stabilityMaximumBin=bin;}
	if(TMPPur<1. &&TMPPur>maxPur  ){ maxPur = TMPPur; purityMaximumBin=bin;    }
	if(TMPStab>0.&&TMPStab<minStab){ minStab= TMPStab; stabilityMinimumBin=bin;}
	if(TMPPur>0. &&TMPPur<minPur  ){ minPur = TMPPur; purityMinimumBin=bin;    }
	// check minimal migration condition
	if(TMPStab>minMigr)NStabok++;
	if(TMPPur >minMigr)NPurok++;
      }
    }
  }
  std::cout << std::endl << variable << "(" << lepton << "):" << std::endl;
  std::cout << "--------------------" << std::endl;
  std::cout << std::setprecision(2) << std::fixed << minPur  << " (<" << variable; 
  std::cout << ">=" << std::setprecision(0) << std::fixed;
  std::cout << purityhist->GetBinCenter(purityMinimumBin) << ") < purity < ";
  std::cout << std::setprecision(2) << std::fixed << maxPur  << " (<" << variable;
  std::cout << ">=" << std::setprecision(0) << std::fixed;
  std::cout << purityhist->GetBinCenter(purityMaximumBin) << ")" << std::endl;
  std::cout << "( purity > " << std::setprecision(2) << std::fixed;
  std::cout << minMigr << " in " << NPurok << "/" << Nbins << " bins)" << std::endl;
  std::cout << std::setprecision(2) << std::fixed << minStab << " (<" << variable;
  std::cout << ">=" << std::setprecision(0) << std::fixed;
  std::cout << stabilityhist->GetBinCenter(stabilityMinimumBin) << ") < stability < ";
  std::cout << std::setprecision(2) << std::fixed << maxStab << " (<" << variable;
  std::cout << ">=" << std::setprecision(0) << std::fixed;
  std::cout << stabilityhist->GetBinCenter(stabilityMaximumBin) << ")"<< std::endl;
  std::cout << "( stability > " << std::setprecision(2) << std::fixed << minMigr;
  std::cout << " in " << NStabok << "/" << Nbins << " bins)" << std::endl<< std::endl;
}
