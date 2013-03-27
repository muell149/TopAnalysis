#include "TROOT.h"
#include "TStyle.h"
#include <vector>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TGraph.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLine.h"
#include "TString.h"

double getSoB(TH1F* sig, TH1F* bkg, double probCut, TString opt);
void drawLine(const double xmin, const double ymin, const double xmax, const double ymax, const unsigned int color, const double lineWidth, const unsigned int lineStyle);
TString getTStringFromInt(int i);
TString getTStringFromDouble(double d, int precision, bool output);
void drawArrow(const double xmin, const double y, const double xmax, const unsigned int color, const double lineWidth, const unsigned int lineStyle, double stretchFactor);

void optimizeProbCut(TString optimize = "#frac{sig}{#sqrt{sig+bkg}}", TString lep = "both")
{
  // configure style
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);

  // set optimization parameter
  // optimize the product signal efficiency times signal purity:
  // TString optimize = "#frac{sig}{#sqrt{sig+bkg}}";
  // optimize the product signal efficiency times signal to background ratio:
  // TString optimize = "#frac{sig}{#sqrt{bkg}}"; 
  // optimize signal purity (don't use this one!):
  // TString optimize = "#frac{sig}{sig+bkg}";

  // read files
  TString path = "/afs/naf.desy.de/group/cms/scratch/tophh/newRecentAnalysisRun8TeV/";
  std::vector<TFile*> files_;
  if(lep=="both" || lep=="muon")files_.push_back(new TFile(path+"muonDiffXSecSigSummer12PF.root"));
  if(lep=="both" || lep=="muon")  files_.push_back(new TFile(path+"muonDiffXSecBkgSummer12PF.root"));
  if(lep=="both" || lep=="electron")  files_.push_back(new TFile(path+"elecDiffXSecSigSummer12PF.root"));
  if(lep=="both" || lep=="electron")  files_.push_back(new TFile(path+"elecDiffXSecBkgSummer12PF.root"));

  // get trees
  vector<TTree*> trees_;
  float decayChannel;
  float prob;
  float qAssignment;
  float weight;
  for(UInt_t i = 0; i < files_.size(); i++){
    trees_.push_back((TTree*)files_[i]->Get("analyzeTopRecoKinematicsKinFit/tree"));
    trees_[i]->SetBranchAddress("decayChannel",&decayChannel);
    trees_[i]->SetBranchAddress("prob",&prob);
    trees_[i]->SetBranchAddress("qAssignment",&qAssignment);
    trees_[i]->SetBranchAddress("weight",&weight);
  }

  // initialize histograms
  // only right permutaions
  TH1F* sigHisto = new TH1F("probHistSig","signal probability",1000000,0.,1.);
  // wrong permutaions and ttbar bkg
  TH1F* bkgHisto = new TH1F("probHistBkg","background probability",1000000,0.,1.);
  // all ttbar signal (right+wrong permutations)
  TH1F* ttSigHisto = new TH1F("histTtSig","ttSig probability",1000000,0.,1.);
  // all ttbar background
  TH1F* ttBkgHisto = new TH1F("histTtBkg","ttBkg probability",1000000,0.,1.);
  // kinFit permutations
  TH1F* permutation     = new TH1F("permutation","permutation", 10, -0.5, 9.5 );
  permutation->GetXaxis()->SetBinLabel(1, "ok"      );
  permutation->GetXaxis()->SetBinLabel(2, "bb"      );
  permutation->GetXaxis()->SetBinLabel(3, "blepq"   );
  permutation->GetXaxis()->SetBinLabel(4, "bhadq"   );
  permutation->GetXaxis()->SetBinLabel(5, "bbqlep"  );    
  permutation->GetXaxis()->SetBinLabel(6, "bbqhad"  );
  permutation->GetXaxis()->SetBinLabel(7, "bbqq"       );
  permutation->GetXaxis()->SetBinLabel(8, "low pt jet" );
  permutation->GetXaxis()->SetBinLabel(9, "wrong jet"  );
  permutation->GetXaxis()->SetBinLabel(10,"no match"   );
  // kinFit permutations for a optimal probability selection
  TH1F* permutationProb = (TH1F*)(permutation->Clone("permutationProb"));
  
  // fill histograms
  Long64_t nevent = 0;
  for(UInt_t i = 0; i < files_.size(); i++)
    {
      nevent = (Long64_t)trees_[i]->GetEntries();
      for(Long64_t ientry = 0; ientry < nevent; ++ientry){
	trees_[i]->GetEntry(ientry);
	if((i>1 && decayChannel==1) || (i<=1 && decayChannel==2 && !(lep=="electron")) || (lep=="electron" && decayChannel==1))ttSigHisto->Fill(prob,weight);
	else ttBkgHisto->Fill(prob,weight);
	if(qAssignment==0)sigHisto->Fill(prob,weight);
	else bkgHisto->Fill(prob,weight);
      }
    }

  // find optimal probability cut
  double goldSec     = (3.-sqrt(5.))/2.;
  double optimalProb = -1.;
  double optimalSoB  = -1.;
  double optimalEff  = -1.;
  double SoBLowProb  = 0.;
  double SoBHighProb = 0.;
  double lowProb     = 0.;
  double highProb    = 1.;
  double newLowProb  = goldSec;
  double newHighProb = 1 - goldSec;
  double sigEvents   = sigHisto->Integral();
  double ttSigEvents = ttSigHisto->Integral();
  double ttBkgEvents = ttBkgHisto->Integral();
  vector<double> probVec;
  vector<double> SoBVec;
  vector<double> SeffVec;

  // calculate some points for the plots
  for ( int i = 0 ; i < 100 ; i++ ) {
    probVec.push_back(i/100.);
    SoBVec.push_back(getSoB(sigHisto,bkgHisto,i/100.,optimize));
    SeffVec.push_back(sigHisto->Integral(sigHisto->FindBin(i/100.),sigHisto->GetNbinsX()+1)/sigEvents);
  }

  // golden section search for optimal cut value
  for ( int i = 0 ; i < 100 ; i++ ) {
    if( optimalProb!=newLowProb ){
      // calculate s/sqrt(s+b) or s/sqrt(b) for lowProb
      SoBLowProb = getSoB(sigHisto,bkgHisto,newLowProb,optimize);
      probVec.push_back(newLowProb);
      SoBVec.push_back(SoBLowProb);
      SeffVec.push_back(sigHisto->Integral(sigHisto->FindBin(newLowProb),sigHisto->GetNbinsX()+1)/sigEvents);
      cout << "newLowProb: " << newLowProb << " -> "+optimize+": " << SoBLowProb << endl;
    }
    if(optimalProb!=newHighProb){
      // calculate s/sqrt(s+b) or s/sqrt(b) for highProb
      SoBHighProb = getSoB(sigHisto,bkgHisto,newHighProb,optimize);
      probVec.push_back(newHighProb);
      SoBVec.push_back(SoBHighProb);
      SeffVec.push_back(sigHisto->Integral(sigHisto->FindBin(newHighProb),sigHisto->GetNbinsX()+1)/sigEvents);
      cout << "newHighProb: " << newHighProb << " -> "+optimize+": " << SoBHighProb << endl;
    }
    if(SoBLowProb>SoBHighProb){
      highProb=newHighProb;
      optimalProb=newLowProb;
      optimalSoB=SoBLowProb;
      newHighProb=newLowProb;
      optimalEff=sigHisto->Integral(sigHisto->FindBin(newLowProb),sigHisto->GetNbinsX()+1)/sigEvents;
      if(TMath::Abs(SoBLowProb-SoBHighProb)/(SoBLowProb+SoBHighProb)<0.0000001)break;
      SoBHighProb=SoBLowProb;
      newLowProb=lowProb+goldSec*(highProb-lowProb);
    } else {
      lowProb=newLowProb;
      optimalProb=newHighProb;
      optimalSoB=SoBHighProb;
      newLowProb=newHighProb;
      optimalEff=sigHisto->Integral(sigHisto->FindBin(newHighProb),sigHisto->GetNbinsX()+1)/sigEvents;
      if(TMath::Abs(SoBLowProb-SoBHighProb)/(SoBLowProb+SoBHighProb)<0.0000001)break;
      SoBLowProb=SoBHighProb;
      newHighProb=highProb-goldSec*(highProb-lowProb);
    }
  }
  double ttSigEff = ttSigHisto->Integral(ttSigHisto->FindBin(optimalProb),ttSigHisto->GetNbinsX()+1)/ttSigEvents;
  double ttBkgEff = ttBkgHisto->Integral(ttBkgHisto->FindBin(optimalProb),ttBkgHisto->GetNbinsX()+1)/ttBkgEvents;
  double ttEff    = (ttSigHisto->Integral(ttSigHisto->FindBin(optimalProb),ttSigHisto->GetNbinsX()+1)+ttBkgHisto->Integral(ttBkgHisto->FindBin(optimalProb),ttBkgHisto->GetNbinsX()+1))/(ttSigEvents+ttBkgEvents);
  cout << endl << "Optimal probability cut: prob > " << optimalProb << endl;
  cout << " -> "<< endl;
  cout << " eff(all ttbar          ): " << ttEff << endl;
  cout << " eff(correct permutation): " << optimalEff << endl;
  cout << " eff(ttbar-signal       ): " << ttSigEff << endl;
  cout << " eff(ttbar-bkg          ): " << ttBkgEff << endl;
  cout << " "<< optimize << "        : " << getSoB(sigHisto,bkgHisto,-1,optimize);
  cout << "  (" << getSoB(sigHisto,bkgHisto,optimalProb,optimize) << "   for prob>" << optimalProb << ")" << endl;
  cout << " ttbar SG / ttbar BG               : " <<  ttSigEvents/ttBkgEvents;
  cout << "  (" <<  ttSigHisto->Integral(ttSigHisto->FindBin(optimalProb),ttSigHisto->GetNbinsX()+1)/ttBkgHisto->Integral(ttBkgHisto->FindBin(optimalProb),ttBkgHisto->GetNbinsX()+1)  << "  for prob>" << optimalProb << ")" << endl;
  cout << " correct permutation / all ttbar SG: " <<  sigHisto->Integral(0,sigHisto->GetNbinsX()+1)/ttSigEvents;
  cout << " (" <<  sigHisto->Integral(sigHisto->FindBin(optimalProb),sigHisto->GetNbinsX()+1)/ttSigHisto->Integral(ttSigHisto->FindBin(optimalProb),ttSigHisto->GetNbinsX()+1) << " for prob>" << optimalProb << ")" << endl;


  // fill permutation histos
  for(UInt_t i = 0; i < files_.size(); i++)
    {
      nevent = (Long64_t)trees_[i]->GetEntries();
      for(Long64_t ientry = 0; ientry < nevent; ++ientry){
	trees_[i]->GetEntry(ientry);
	if((i>1 && decayChannel==1) || (i<=1 && decayChannel==2 && !(lep=="electron")) || (lep=="electron" && decayChannel==1)){
	  permutation->Fill(qAssignment,weight);
	  if(prob>optimalProb) permutationProb->Fill(qAssignment,weight);
	}
      }
    }
  // get efficiency per permutation
  TH1F* effPermu = (TH1F*)(permutationProb->Clone("effPermu"));
  effPermu->Divide((TH1F*)(permutation->Clone()));
  // normalize permutation histos
  permutation    ->Scale(1./permutation    ->Integral(0,permutation    ->GetNbinsX()+1));
  permutationProb->Scale(1./permutationProb->Integral(0,permutationProb->GetNbinsX()+1));

  // set up canvas
  TCanvas *canv = new TCanvas("canv","probability cut optimisation",10,10,1200,600);
  canv->Divide(2,1);
  canv->cd(1)->SetLeftMargin  (0.15);
  canv->cd(1)->SetRightMargin (0.03);
  canv->cd(1)->SetBottomMargin(0.10);
  canv->cd(1)->SetTopMargin   (0.05);
  canv->cd(2)->SetLeftMargin  (0.15);
  canv->cd(2)->SetRightMargin (0.03);
  canv->cd(2)->SetBottomMargin(0.10);
  canv->cd(2)->SetTopMargin   (0.05);
  TCanvas *canv2 = new TCanvas("canv2","probability",10,10,900,600);
  canv2->cd()->SetLeftMargin  (0.08);
  canv2->cd()->SetRightMargin (0.03);
  canv2->cd()->SetBottomMargin(0.10);
  canv2->cd()->SetTopMargin   (0.05);
  canv2->cd()->SetLogy();
  TCanvas *canv3 = new TCanvas("canv3","probabilityFraction",10,10,900,600);
  canv3->cd()->SetLeftMargin  (0.08);
  canv3->cd()->SetRightMargin (0.03);
  canv3->cd()->SetBottomMargin(0.10);
  canv3->cd()->SetTopMargin   (0.05);
  canv3->cd()->SetLogy();
  TCanvas *canv4 = new TCanvas("canv4","permutation",10,10,900,600);
  canv4->cd()->SetLeftMargin  (0.08);
  canv4->cd()->SetRightMargin (0.03);
  canv4->cd()->SetBottomMargin(0.10);
  canv4->cd()->SetTopMargin   (0.05);
  TCanvas *canv5 = new TCanvas("canv5","effPerPermutation",10,10,900,600);
  canv5->cd()->SetLeftMargin  (0.08);
  canv5->cd()->SetRightMargin (0.03);
  canv5->cd()->SetBottomMargin(0.10);
  canv5->cd()->SetTopMargin   (0.05);

  // draw graph s/sqrt(s+b) or s/sqrt(b) vs probability
  canv->cd(1);
  TGraph* optSoB = new TGraph((int)probVec.size(),&probVec.front(),&SoBVec.front());
  optSoB->SetMarkerStyle(20);
  sigHisto->SetMaximum(1.1*optimalSoB);
  sigHisto->GetXaxis()->SetTitle("probability");
  sigHisto->GetYaxis()->SetTitle(optimize);
  sigHisto->GetYaxis()->SetTitleOffset(1.65);
  sigHisto->DrawClone("axis");
  optSoB->DrawClone("p same");

  // draw graph signal efficiency vs probability
  canv->cd(2);
  TGraph* eff = new TGraph((int)probVec.size(),&probVec.front(),&SeffVec.front());
  eff->SetMarkerStyle(20);
  sigHisto->SetMaximum(1.);
  sigHisto->GetYaxis()->SetTitle("signal efficiency");
  sigHisto->DrawClone("axis");
  eff->DrawClone("p same");

  // draw prob distribution
  canv2->cd();
  sigHisto->SetTitle("");
  sigHisto->GetXaxis()->SetTitle("Probability (best hypothesis)");
  sigHisto->GetYaxis()->SetTitle("Events");
  sigHisto->GetYaxis()->SetTitleOffset(0.85);
  TH1F* sigFracHisto=(TH1F*)sigHisto->Clone("sigFracHisto");
  sigFracHisto->SetLineColor(kRed+1);
  sigFracHisto->SetLineWidth(3);
  sigFracHisto->SetMinimum(0.001);
  sigFracHisto->SetMaximum(1.00);
  sigFracHisto->GetYaxis()->SetTitle("rel. Events");
  sigHisto->SetFillColor(kRed+1);
  sigHisto->Add(bkgHisto);
  sigHisto->Rebin(10000);
  sigHisto->SetMinimum(10);
  sigFracHisto->Rebin(10000);
  sigHisto->DrawClone("h");
  TH1F* bkgFracHisto=(TH1F*)bkgHisto->Clone("bkgFracHisto");
  bkgFracHisto->SetLineWidth(3);
  bkgFracHisto->SetLineStyle(9);
  bkgFracHisto->SetLineColor(kRed);
  bkgHisto->SetFillStyle(1001);
  bkgHisto->SetFillColor(10);
  bkgFracHisto->Rebin(10000);
  bkgHisto->Rebin(10000);
  bkgHisto->DrawClone("h same");
  bkgHisto->SetFillStyle(3001);
  bkgHisto->SetFillColor(kRed);
  bkgHisto->DrawClone("h same");
  TH1F* ttBkgFracHisto=(TH1F*)ttBkgHisto->Clone("ttBkgFracHisto");
  int ttBkgColor=kBlue;//kRed-7
  ttBkgFracHisto->SetLineColor(ttBkgColor);
  ttBkgFracHisto->SetLineWidth(3);
  ttBkgFracHisto->SetLineStyle(2);
  ttBkgHisto->SetFillColor(10);
  ttBkgHisto->SetFillStyle(1001);
  ttBkgHisto->Rebin(10000);
  ttBkgFracHisto->Rebin(10000);
  ttBkgHisto->DrawClone("h same");
  ttBkgHisto->SetFillColor(ttBkgColor);
  ttBkgHisto->SetFillStyle(3144);
  ttBkgHisto->DrawClone("h same");
  // draw legend
  TLegend *leg  = new TLegend(); 
  leg->SetX1NDC(0.3);
  leg->SetY1NDC(0.6);
  leg->SetX2NDC(0.9);
  leg->SetY2NDC(0.9);
  leg ->SetFillStyle(1001);
  leg ->SetFillColor(10);
  leg ->SetBorderSize(0);
  //leg ->SetTextSize(0.1);
  leg ->SetTextAlign(12);
  leg ->SetHeader(" t#bar{t} Simulation");
  TLegend *leg2=(TLegend *)leg->Clone();
  leg ->AddEntry(sigHisto, "SG correct permutation"  , "F");
  leg ->AddEntry(bkgHisto, "SG other permutation"    , "F");
  leg ->AddEntry(ttBkgHisto, "BG (non prompt l+jets signal)", "F");
  leg ->AddEntry(effPermu, "optimal cut: prob>"+getTStringFromDouble(optimalProb, 4, false), "L");
  leg2 ->AddEntry(sigFracHisto, "SG correct permutation"  , "L");
  leg2 ->AddEntry(bkgFracHisto, "SG other permutation"    , "L");
  leg2 ->AddEntry(ttBkgFracHisto, "BG (non prompt l+jets signal)", "L");
  leg2 ->AddEntry(effPermu, "optimal cut: prob>"+getTStringFromDouble(optimalProb, 4, false), "L");
  leg ->Draw("same");
  drawLine(optimalProb, sigHisto->GetMinimum(), optimalProb, 0.6*sigHisto->GetMaximum(), kBlack, 2, 1);
  drawArrow(optimalProb, sigHisto->GetMaximum()/10, optimalProb+0.05, kBlack, 2, 1, 1.2);
  sigHisto->DrawClone("axis same");

  // draw normalized prob distribution
  canv3->cd();
  sigFracHisto->DrawClone("axis");
  sigFracHisto->DrawNormalized("same");
  bkgFracHisto->DrawNormalized("same");
  ttBkgFracHisto->DrawNormalized("same");
  drawLine(optimalProb, sigFracHisto->GetMinimum(), optimalProb, 0.6*sigFracHisto->GetMaximum(), kBlack, 2, 1);
  drawArrow(optimalProb, sigFracHisto->GetMaximum()/10, optimalProb+0.05, kBlack, 2, 1, 1.2);
  sigFracHisto->DrawClone("axis same");
  leg2->Draw("same");
  // draw permutation distribution
  canv4->cd();
  permutation->SetTitle("");
  permutation->GetXaxis()->SetTitle("jet permutation of kinematic fit wrt. parton truth");
  permutation->GetYaxis()->SetTitle("rel. Events");
  permutation    ->SetLineWidth(3);
  permutation    ->SetLineColor(kBlue);
  permutation    ->SetLineStyle(1);
  permutation    ->Draw();
  permutationProb->SetLineWidth(3);
  permutationProb->SetLineStyle(2);
  permutationProb->SetLineColor(kRed);
  permutationProb->Draw("same");
  TLegend *leg3  = new TLegend(); 
  leg3->SetX1NDC(0.3);
  leg3->SetY1NDC(0.6);
  leg3->SetX2NDC(0.7);
  leg3->SetY2NDC(0.9);
  leg3 ->SetFillStyle(1001);
  leg3 ->SetFillColor(10);
  leg3 ->SetBorderSize(0);
  leg3 ->SetTextAlign(12);
  leg3->AddEntry(permutation, "t#bar{t}#rightarrowl+jets prompt", "L");
  leg3->AddEntry(permutationProb, "  + prob>"+getTStringFromDouble(optimalProb, 4, false), "L");
  leg3->Draw("same");
  // draw efficiency per permutation
  canv5->cd();
  effPermu->SetTitle("");
  effPermu->GetXaxis()->SetTitle("jet permutation of kinematic fit wrt. parton truth");
  effPermu->GetYaxis()->SetTitle("eff(prob>"+getTStringFromDouble(optimalProb, 4, false)+")");
  effPermu    ->SetLineWidth(3);
  effPermu    ->SetLineColor(kBlack);
  effPermu    ->SetLineStyle(1);
  effPermu    ->Draw();
}

// calculate s/sqrt(s+b) or s/sqrt(+b)
double getSoB(TH1F* sig, TH1F* bkg, double probCut, TString opt)
{
  double signal = sig->Integral(sig->FindBin(probCut),sig->GetNbinsX()+1);
  double backgr = bkg->Integral(sig->FindBin(probCut),sig->GetNbinsX()+1);
  double result = 0.;
  if(opt=="#frac{sig}{#sqrt{bkg}}")result = signal/TMath::Sqrt(backgr);
  if(opt=="#frac{sig}{#sqrt{sig+bkg}}")result = signal/TMath::Sqrt(signal+backgr);
  return result;
}

void drawLine(const double xmin, const double ymin, const double xmax, const double ymax, const unsigned int color, const double lineWidth, const unsigned int lineStyle)
{
  // this function draws a line withe the chosen coordinates,
  // color and width into the active canvas
  TLine *line = new TLine();
  line->SetLineWidth(lineWidth);
  line->SetLineStyle(lineStyle);
  line->SetLineColor(color);
  line->DrawLine(xmin, ymin, xmax, ymax);
}

TString getTStringFromInt(int i)
{
  // function to convert an int "i" to
  // a TString and return this one
  char result[20];
  sprintf(result, "%i", i);
  return (TString)result;
}

TString getTStringFromDouble(double d, int precision, bool output)
{
  // function to convert an double "d" to
  // a TString and return this one
  TString conv="%.";
  conv+=getTStringFromInt(precision);
  conv+="f";
  char result[30];
  if(output) std::cout << "sprintf(result, conv, d)=sprintf(" << result << ", " << conv << ", " << d << ")" << std::endl;
  sprintf(result, conv, d);
  return (TString)result;
}

void drawArrow(const double xmin, const double y, const double xmax, const unsigned int color, const double lineWidth, const unsigned int lineStyle, double stretchFactor)
{
  // this function draws an arrow line with the chosen coordinates,
  drawLine(xmin, y, xmax, y, color, lineWidth, lineStyle);
  drawLine(0.8*xmax, y*stretchFactor, xmax, y, color, lineWidth, lineStyle);
  drawLine(0.8*xmax, y/stretchFactor, xmax, y, color, lineWidth, lineStyle);
}
