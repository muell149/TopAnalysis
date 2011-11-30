#define MC_ERROR_MACRO

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <sys/stat.h>
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TList.h"
#include "TH1D.h"
#include "TH2D.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPostScript.h"
#include "TMath.h"
#include "TPad.h"
#include "TStyle.h"
#include "TGraphAsymmErrors.h"
#include "TPaveText.h"
#include "TopAnalysis/Configuration/analysis/semiLeptonic/diffXSection/basicFunctions.h"
#include "TopAnalysis/Configuration/analysis/semiLeptonic/diffXSection/HHStyle.h"

using namespace std;

/// CONFIGURABLES

// path to the ingoing root histogram files
const TString inpath("/afs/naf.desy.de/group/cms/scratch/markusm/Systematics/");

// path where the output is written
const TString outpath("Markus/DiffXS2011/Systematics/MCUncertainties/");

// output format
const TString outform(".png");
//const TString outform(".eps");

// output file name
const TString outfileName(outpath+"MCUncertainties.root");

///////////////////////////////////////////////////////////

//Bool_t set_LogY = kTRUE;
Bool_t set_LogY = kFALSE;

Bool_t isScaled = kTRUE;
//Bool_t isScaled = kFALSE;

///////////////////////////////////////////////////////////

TFile* files[100];

TLegend* leg = new TLegend(0.70,0.58,0.95,0.87);
//TLegend* leg = new TLegend(0.25,0.58,0.50,0.87);

const Int_t   nbinsLepPt = 5;
const Double_t binsLepPt[nbinsLepPt+1] = {20, 40, 70, 120, 180, 400};

const Int_t   nbinsLepEta = 6;
const Double_t binsLepEta[nbinsLepEta+1] = {-2.4, -1.5, -0.8, 0.0, 0.8, 1.5, 2.4};

const Int_t   nbinsLepPairPt = 7;
const Double_t binsLepPairPt[nbinsLepPairPt+1] = {0, 10, 20, 40, 60, 100, 150, 400};

const Int_t   nbinsLepPairMass = 5;
const Double_t binsLepPairMass[nbinsLepPairMass+1] = {12, 50, 76, 106, 200, 400};

const Int_t   nbinsTopRapidity = 4;
const Double_t binsTopRapidity[nbinsTopRapidity+1] = {-2.5, -1.2, 0.0, 1.2, 2.5};

const Int_t   nbinsTopPt = 4;
const Double_t binsTopPt[nbinsTopPt+1] = {0, 70, 140, 240, 400};

const Int_t   nbinsTtBarPt = 4;
const Double_t binsTtBarPt[nbinsTtBarPt+1] = {0, 20, 60, 120, 500};

const Int_t    nbinsTtBarRapidity = 4;
const Double_t binsTtBarRapidity[nbinsTtBarRapidity+1] = {-2.5, -1.2, 0.0, 1.2, 2.5};

const Int_t   nbinsTtBarMass = 5;
const Double_t binsTtBarMass[nbinsTtBarMass+1] = {345, 400, 475, 550, 700, 1000};

///////////////////////////////////////////////////////////

TH1* SummedStackHisto(const THStack* stack) {

  TList* l = stack->GetHists();

  if ( l->GetEntries() == 0 )  return 0;

  TH1* result = (TH1*)l->At(0)->Clone();

  for(int i = 1; i < l->GetEntries(); ++i) {

    result->Add((TH1*)l->At(i));

  }

  return result;

}


void SetHistogramStyle(TH1* h_ref, TH1* h_var_up, TH1* h_var_down) {

  h_ref->SetMarkerColor(kBlack);
  h_ref->SetMarkerStyle(20);
  h_ref->SetMarkerSize(1.6);
  h_ref->SetLineColor(kBlack);
  h_ref->SetLineWidth(2.);
  h_ref->Draw("E1,P");

  h_var_up->SetMarkerColor(kBlue);
  h_var_up->SetMarkerStyle(22);
  h_var_up->SetMarkerSize(1.6);
  h_var_up->SetLineColor(kBlue);
  h_var_up->SetLineWidth(2.);
  h_var_up->Draw("E1,P,SAME");

  h_var_down->SetMarkerColor(kRed);
  h_var_down->SetMarkerStyle(23);
  h_var_down->SetMarkerSize(1.6);
  h_var_down->SetLineColor(kRed);
  h_var_down->SetLineWidth(2.);
  h_var_down->Draw("E1,P,SAME");

  return;

}


void CalculateEfficiencies(TFile* file_ref, TFile* file_var_up, TFile* file_var_down,
			   TString HistName, Int_t nbins, const Double_t bins[], const TString label, const Double_t scale) {

  TH1* h_ref_gen;
  TH1* h_ref_reco;
  TH1* h_ref_eff;
  TH1* h_style = 0;
  TH1* h_var_up_gen;
  TH1* h_var_up_reco;
  TH1* h_var_up_eff;
  TH1* h_var_down_gen;
  TH1* h_var_down_reco;
  TH1* h_var_down_eff;

  cout << "   >>> HistName:  " << HistName << endl;

  TString title = HistName.Copy().Prepend("analyzeVisibleGenTopEvent/gen_");

  file_ref->GetObject(      title, h_ref_gen);
  file_ref->GetObject(      title, h_style);
  file_var_up->GetObject(   title, h_var_up_gen);
  file_var_down->GetObject( title, h_var_down_gen);

  h_ref_gen      = h_ref_gen->Rebin(nbins,"",     &bins[0]);
  h_var_up_gen   = h_var_up_gen->Rebin(nbins,"",  &bins[0]);
  h_var_down_gen = h_var_down_gen->Rebin(nbins,"",&bins[0]);

  if(isScaled) {
    h_var_up_gen->Scale(h_ref_gen->Integral()/h_var_up_gen->Integral());
    h_var_down_gen->Scale(h_ref_gen->Integral()/h_var_down_gen->Integral());
  }

  title = HistName.Copy().Prepend("analyzeKinSolution8/kin_");

  file_ref->GetObject(      title, h_ref_reco);
  file_var_up->GetObject(   title, h_var_up_reco);
  file_var_down->GetObject( title, h_var_down_reco);

  h_ref_reco      = h_ref_reco->Rebin(      nbins,"", &bins[0]);
  h_var_up_reco   = h_var_up_reco->Rebin(   nbins,"", &bins[0]);
  h_var_down_reco = h_var_down_reco->Rebin( nbins,"", &bins[0]);

  if(isScaled) {
    h_var_up_reco->Scale(h_ref_reco->Integral()/h_var_up_reco->Integral());
    h_var_down_reco->Scale(h_ref_reco->Integral()/h_var_down_reco->Integral());
  }

  h_ref_eff      = new TH1F(HistName.Copy().Append("_EFF_REF").Append( label), HistName.Copy().Append("_EFF_REF").Append( label), nbins, &bins[0]);
  h_var_up_eff   = new TH1F(HistName.Copy().Append("_EFF_UP").Append(  label), HistName.Copy().Append("_EFF_UP").Append(  label), nbins, &bins[0]);
  h_var_down_eff = new TH1F(HistName.Copy().Append("_EFF_DOWN").Append(label), HistName.Copy().Append("_EFF_DOWN").Append(label), nbins, &bins[0]);

  h_ref_gen->Sumw2();
  h_var_up_gen->Sumw2();
  h_var_down_gen->Sumw2();
  h_ref_reco->Sumw2();
  h_var_up_reco->Sumw2();
  h_var_down_reco->Sumw2();

  h_ref_eff->Divide(h_ref_reco,h_ref_gen,1,1,"B");
  h_var_up_eff->Divide(h_var_up_reco,h_var_up_gen,1,1,"B");
  h_var_down_eff->Divide(h_var_down_reco,h_var_down_gen,1,1,"B");

  TCanvas* GEN = new TCanvas("GEN","", 900, 900);
  GEN->cd();
  h_ref_gen->SetMaximum(1.2*h_ref_gen->GetMaximum());
  h_ref_gen->SetMinimum(0.);
  if(!isScaled) {
    h_var_up_gen->Scale(h_ref_gen->Integral()/h_var_up_gen->Integral());
    h_var_down_gen->Scale(h_ref_gen->Integral()/h_var_down_gen->Integral());
  }
  SetHistogramStyle(h_ref_gen, h_var_up_gen, h_var_down_gen);
  GEN->Print(outpath.Copy().Append(HistName).Append("_GEN_").Append(label).Append(outform));

  TCanvas* RECO = new TCanvas("RECO","", 900, 900);
  RECO->cd();
  h_ref_reco->SetMaximum(1.2*h_ref_reco->GetMaximum());
  h_ref_reco->SetMinimum(0.);
  if(!isScaled) {
    h_var_up_reco->Scale(h_ref_reco->Integral()/h_var_up_reco->Integral());
    h_var_down_reco->Scale(h_ref_reco->Integral()/h_var_down_reco->Integral());
  }
  SetHistogramStyle(h_ref_reco, h_var_up_reco, h_var_down_reco);
  RECO->Print(outpath.Copy().Append(HistName).Append("_RECO_").Append(label).Append(outform));

  TCanvas* EFF = new TCanvas("EFF","", 900, 900);
  EFF->cd();
  h_ref_eff->SetMaximum(1.04);
  h_ref_eff->SetMinimum(0.);
  SetHistogramStyle(h_ref_eff, h_var_up_eff, h_var_down_eff);
  EFF->Print(outpath.Copy().Append(HistName).Append("_EFF_").Append(label).Append(outform));

  leg->AddEntry(h_style,label,"F");
  cout << "-------------" << endl << endl;

}


void MCUncertainties() {

  setHHStyle(*gStyle);

  leg->Clear();
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);

  ////////////////////////////////////////////////////////////////////
  //  HADRONISATION --------------------------------------------------
  ////////////////////////////////////////////////////////////////////

  files[0] = new TFile(inpath.Copy().Append("emu_ttbarsignal_madgraph_Fall10.root"));
  files[1] = new TFile(inpath.Copy().Append("emu_ttbarsignal_powheg_pythia6_Fall10.root"));
  files[2] = new TFile(inpath.Copy().Append("emu_ttbarsignal_powheg_herwig6_Fall10.root"));

  if( files[0] && !files[0]->IsZombie() && files[1] && !files[1]->IsZombie() && files[2] && !files[2]->IsZombie() ) {
    cout << "-------------------------" << endl;
    cout << "   >>>   HADRONISATION   " << endl;
    cout << "-------------------------" << endl << endl;
    CalculateEfficiencies(files[0], files[1], files[2], "LepPt",         nbinsLepPt,         binsLepPt,         "HADRON", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "LepEta",        nbinsLepEta,        binsLepEta,        "HADRON", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "LepPairPt",     nbinsLepPairPt,     binsLepPairPt,     "HADRON", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "LepPairMass",   nbinsLepPairMass,   binsLepPairMass,   "HADRON", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TopPt",         nbinsTopPt,         binsTopPt,         "HADRON", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TopRapidity",   nbinsTopRapidity,   binsTopRapidity,   "HADRON", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TtBarMass",     nbinsTtBarMass,     binsTtBarMass,     "HADRON", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TtBarPt",       nbinsTtBarPt,       binsTtBarPt,       "HADRON", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TtBarRapidity", nbinsTtBarRapidity, binsTtBarRapidity, "HADRON", 1.);
  }

  ////////////////////////////////////////////////////////////////////
  //  TOP MASS -------------------------------------------------------
  ////////////////////////////////////////////////////////////////////

  files[0] = new TFile(inpath.Copy().Append("emu_ttbarsignal_madgraph_Fall10.root"));
  files[1] = new TFile(inpath.Copy().Append("emu_ttbarsignal_mass178_5_Fall10.root"));
  files[2] = new TFile(inpath.Copy().Append("emu_ttbarsignal_mass166_5_Fall10.root"));

  if( files[0] && !files[0]->IsZombie() && files[1] && !files[1]->IsZombie() && files[2] && !files[2]->IsZombie() ) {
    cout << "-------------------------" << endl;
    cout << "   >>>   TOP MASS        " << endl;
    cout << "-------------------------" << endl << endl;
    CalculateEfficiencies(files[0], files[1], files[2], "LepPt",         nbinsLepPt,         binsLepPt,         "TOP_MASS", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "LepEta",        nbinsLepEta,        binsLepEta,        "TOP_MASS", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "LepPairPt",     nbinsLepPairPt,     binsLepPairPt,     "TOP_MASS", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "LepPairMass",   nbinsLepPairMass,   binsLepPairMass,   "TOP_MASS", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TopPt",         nbinsTopPt,         binsTopPt,         "TOP_MASS", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TopRapidity",   nbinsTopRapidity,   binsTopRapidity,   "TOP_MASS", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TtBarMass",     nbinsTtBarMass,     binsTtBarMass,     "TOP_MASS", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TtBarPt",       nbinsTtBarPt,       binsTtBarPt,       "TOP_MASS", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TtBarRapidity", nbinsTtBarRapidity, binsTtBarRapidity, "TOP_MASS", 1.);
  }

  ////////////////////////////////////////////////////////////////////
  //  MATCHING -------------------------------------------------------
  ////////////////////////////////////////////////////////////////////

  files[0] = new TFile(inpath.Copy().Append("emu_ttbarsignal_madgraph_Fall10.root"));
  files[1] = new TFile(inpath.Copy().Append("emu_ttbarsignal_matchingup_Fall10.root"));
  files[2] = new TFile(inpath.Copy().Append("emu_ttbarsignal_matchingdown_Fall10.root"));

  if( files[0] && !files[0]->IsZombie() && files[1] && !files[1]->IsZombie() && files[2] && !files[2]->IsZombie() ) {
    cout << "-------------------------" << endl;
    cout << "   >>>   MATCHING        " << endl;
    cout << "-------------------------" << endl << endl;
    CalculateEfficiencies(files[0], files[1], files[2], "LepPt",         nbinsLepPt,         binsLepPt,         "MATCHING", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "LepEta",        nbinsLepEta,        binsLepEta,        "MATCHING", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "LepPairPt",     nbinsLepPairPt,     binsLepPairPt,     "MATCHING", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "LepPairMass",   nbinsLepPairMass,   binsLepPairMass,   "MATCHING", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TopPt",         nbinsTopPt,         binsTopPt,         "MATCHING", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TopRapidity",   nbinsTopRapidity,   binsTopRapidity,   "MATCHING", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TtBarMass",     nbinsTtBarMass,     binsTtBarMass,     "MATCHING", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TtBarPt",       nbinsTtBarPt,       binsTtBarPt,       "MATCHING", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TtBarRapidity", nbinsTtBarRapidity, binsTtBarRapidity, "MATCHING", 1.);
  }

  ////////////////////////////////////////////////////////////////////
  //   Q^2 SCALE -----------------------------------------------------
  ////////////////////////////////////////////////////////////////////

  files[0] = new TFile(inpath.Copy().Append("emu_ttbarsignal_madgraph_Fall10.root"));
  files[1] = new TFile(inpath.Copy().Append("emu_ttbarsignal_scaleup_Fall10.root"));
  files[2] = new TFile(inpath.Copy().Append("emu_ttbarsignal_scaledown_Fall10.root"));

  if( files[0] && !files[0]->IsZombie() && files[1] && !files[1]->IsZombie() && files[2] && !files[2]->IsZombie() ) {
    cout << "-------------------------" << endl;
    cout << "   >>>   Q2_SCALE        " << endl;
    cout << "-------------------------" << endl << endl;
    CalculateEfficiencies(files[0], files[1], files[2], "LepPt",         nbinsLepPt,         binsLepPt,         "Q2_SCALE", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "LepEta",        nbinsLepEta,        binsLepEta,        "Q2_SCALE", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "LepPairPt",     nbinsLepPairPt,     binsLepPairPt,     "Q2_SCALE", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "LepPairMass",   nbinsLepPairMass,   binsLepPairMass,   "Q2_SCALE", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TopPt",         nbinsTopPt,         binsTopPt,         "Q2_SCALE", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TopRapidity",   nbinsTopRapidity,   binsTopRapidity,   "Q2_SCALE", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TtBarMass",     nbinsTtBarMass,     binsTtBarMass,     "Q2_SCALE", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TtBarPt",       nbinsTtBarPt,       binsTtBarPt,       "Q2_SCALE", 1.);
    CalculateEfficiencies(files[0], files[1], files[2], "TtBarRapidity", nbinsTtBarRapidity, binsTtBarRapidity, "Q2_SCALE", 1.);
  }

  TFile outfile(outfileName,"recreate");
  outfile.Close();
  cout << "-------------------------" << endl << endl;

}


int main() {

  MCUncertainties();

}
