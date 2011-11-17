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

int  purityStabilityEfficiency(TString variable = "lepPt", bool save=false, TString lepton="muon", 
			       TString inputFolderName="TOP2011/110819_AnalysisRun", bool plotEfficiency = true, 
			       bool plotEfficiencyPhaseSpace = true, bool plotEfficiency2 = false, double chi2Max=99999)
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
  //TString outputFolder = "/afs/desy.de/user/j/jlange/analysis/top/diffXSec/purStabEff/"+lepton;
  //TString outputFolder = "/afs/naf.desy.de/user/j/jlange/public/analysis/purStabEff/compSpringSummer11";
  TString outputFolder = "./diffXSecFromSignal/plots/"+lepton+"/2011/binning";
  if(useTree&&chi2Max<100){ 
    plotEfficiencyPhaseSpace = false;
    plotEfficiency = false;
    plotEfficiency2= false;
  }

  if(lepton=="electron") lepton="elec";
  
  // input file
  TFile* myFile1 = new TFile("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/"+lepton+"DiffXSecSigMadD6TSummer11PF.root", "READ");
  //TFile* myFile1 = new TFile("/afs/naf.desy.de/user/j/jlange/public/analysis/"+lepton+"DiffXSecSigMadD6TSpring11PF.root", "READ"); //TFile("/afs/desy.de/user/m/mgoerner/public/analysisRootFilesWithKinFit/"+lepton+"DiffXSecSigMadD6TSpring11PF.root", "READ");
  //TFile("/afs/naf.desy.de/user/j/jlange/public/analysis/elecDiffXSecSigMadD6TSpring11PF.root", "READ");
  TFile* myFile2 = new TFile("/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/"+lepton+"DiffXSecSigMadD6TSummer11PF.root", "READ");
  
  // determine here the binning:
  // Attention: binning ALWAYS should start from left boundary of first and bin of the input file;
  // it ends with the last bin of the input file even if this is not part of the array defined below
  
  
  std::map<TString, std::vector<double> > binningMap = makeVariableBinning();
  std::vector<double> xBins = binningMap[variable];
  int NxBins = xBins.size();
  
  
  // pt
   //double xBins[] = {0, 60, 120, 200, 280, 400};
  // y
   //double xBins[] = {-5., -2.5, -1.5, -1., -0.5, 0, 0.5, 1., 1.5, 2.5};
   // ttbar pt
   //double xBins[] = {0, 20, 60, 110, 200};
   // ttbar Y
   //double xBins[] = {-5., -1.3, -0.9, -0.6, -0.3, 0., 0.3, 0.6, 0.9, 1.3};
   // ttbarMass
   //double xBins[] = {0, 400, 500, 630, 900};
   //double xBins[] = {0, 345, 410, 480, 580, 750};
   //Korea:
   //double xBins[] = {0, 350, 400, 450, 500, 550,600,700,800};
  // lepPt
  //double xBins[] = {0., 20., 25., 30., 35., 40., 45., 50., 60., 70., 80., 100., 120., 150., 200., 275., 400., 1200.};
  // lepEta
  //double xBins[] = {-5., -2.5, -2.1, -1.8, -1.5, -1.2, -0.9, -0.6, -0.3, 0., 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.5, 5.};
  //int NxBins = sizeof(xBins)/sizeof(double);

  std::cout << "size of xBins array: " << NxBins << std::endl;
  
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
  if(useTree) myHist2d->Scale(0);
  // loading tree
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
  else variable_.push_back(variable);
  // container for values read from tree
  std::map< TString, float > value_;
  // container for chi2 cut efficiency
  TH1F* chi2eff = (TH1F*)(((TH1F*)myFile1->Get("analyzeTopPartonLevelKinematicsPhaseSpace/"+variable))->Clone());
  chi2eff->Scale(0);
  TH1F* all=(TH1F*)chi2eff->Clone();
  
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
	if(useTree) myHist2d->Fill(gen, rec, weight);
	// fill events passing chi2
	chi2eff->Fill(rec, weight);
      }
      // fill all events
      all->Fill(rec, weight);
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
  myHist2d->Draw("colz");
  
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

      if( (numberOfBins+1 < NxBins && myHist2d->GetBinCenter(i+1) > xBins[numberOfBins+1]) || i==xbins){
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
  cout<<numberOfBins<<" bins: {";
  for(int i=0; i<numberOfBins; i++)
    {
      cout<<binvec[i]<<", ";
    }
  cout<<xmax<<"}"<<endl;

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
  
  // if als effiency in limited phase space interesting:
  if(plotEfficiencyPhaseSpace){
    // get histogram of generated quantity
    TH1F* genHistPS = (TH1F*)(((TH1F*)myFile1->Get("analyzeTopPartonLevelKinematicsPhaseSpace/"+variable))->Clone());
    TCanvas* Canv4 = new TCanvas("analyzeTopPartonLevelKinematicsPhaseSpace","analyzeTopPartonLevelKinematicsPhaseSpace",600,600);
    Canv4->cd();
    //genHistPS->SetStats(kFALSE);
    genHistPS->Draw();
    // rebin histogram of generated quantity
    genHistPS = (TH1F*)genHistPS->Rebin(binvec.size()-1, genHistPS->GetName(), &(binvec.front()));
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
  if(chi2Max<100){    
    chi2eff = (TH1F*)chi2eff->Rebin(binvec.size()-1, chi2eff->GetName(), &(binvec.front()));
    all     = (TH1F*)all    ->Rebin(binvec.size()-1, all->GetName()    , &(binvec.front()));
    chi2eff->Divide(all);
    chi2eff->SetLineColor(1);
    //chi2eff->SetLineStyle(2);
    chi2eff->SetLineWidth(4);
    chi2eff->Draw("same");
  }
  if (lepton=="muon") DrawDecayChLabel("#mu + Jets");
  else if(lepton=="electron") DrawDecayChLabel("e + Jets");
  double legEdge = 0.4;
  if(plotEfficiency)legEdge = effHist->GetMinimum();
  TLegend* leg=new TLegend(0.47,0.68,0.67,0.87);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(purityhist,   "Purity"    ,"l");
  leg->AddEntry(stabilityhist,"Stability" ,"l");
  //purityhist->GetYaxis()->SetRangeUser  (0, 0.2);
  if(plotEfficiency)leg->AddEntry(effHist,"eff'*A","l");
  //if(plotEfficiency)leg->AddEntry(effHist,"Eff*A full PS Spring11","l");
  if(plotEfficiencyPhaseSpace)leg->AddEntry(effHistPS,"eff' in restr. PS","l");
  if(plotEfficiency2)leg->AddEntry(effHist2,"eff'*A full PS Summer11","l");
  if(chi2Max<100){
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
  
  if(save){
    TString chi="";
    if(chi2Max<100){ 
      chi+="chi";
      chi+=chi2Max;
    }
    purstab->Print(outputFolder+"/purStabEff_"+lepton+"_"+variable+chi+".png");
    std::cout<<"Canvas with purity and stability plots is saved in "<<outputFolder<<std::endl;
  }
    
  return 0;
}
