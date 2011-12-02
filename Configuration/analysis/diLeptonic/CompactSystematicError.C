#define SYS_ERROR_MACRO

#include <iostream>
#include <fstream>
#include <sstream>
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
// const TString inpath("/afs/naf.desy.de/user/w/wbehrenh/cms/systematicsOct14/");
const TString inpath("/afs/naf.desy.de/user/w/wbehrenh/cms/systematicsNov4/");

// path where the output is written
const TString outpath("Markus/DiffXS2011/Systematics/plots/");
// const TString outpath("~wbehrenh/cms/systematicsNov4-output/");

// output format
const TString outform(".png");
//const TString outform(".eps");

///////////////////////////////////////////////////////////

Bool_t isDiff   = kTRUE;
//Bool_t isDiff   = kFALSE;

Bool_t isTotal = !(isDiff);

// output file name
const TString outfileName(isDiff ? outpath+"Systematic_Errors_DIFF.root" : outpath+"Systematic_Errors_TOTAL.root");

///////////////////////////////////////////////////////////

//Bool_t set_LogY = kTRUE;
Bool_t set_LogY = kFALSE;

///////////////////////////////////////////////////////////

Bool_t isModel = kTRUE;
//Bool_t isModel = kFALSE;

Bool_t isExp = kTRUE;
//Bool_t isExp = kFALSE;

Bool_t isStat  = kTRUE;
//Bool_t isStat  = kFALSE;

Bool_t isPSE = kFALSE;

///////////////////////////////////////////////////////////

TObjArray Hlist;

TFile*   files[100];
THStack* sum_stat_errors[1000];
THStack* sum_exp_errors[1000];
THStack* sum_mod_errors[1000];
THStack* sum_errors[1000];

TLegend* leg = new TLegend(0.70,0.58,0.95,0.87);
//TLegend* leg = new TLegend(0.25,0.58,0.50,0.87);

///////////////////////////////////////////////////////////

void setupTotalErrors() {

  TList* ListOfKeys = files[0]->GetListOfKeys();

  for(Int_t i = 0; i < ListOfKeys->GetEntries(); ++i) {

    sum_stat_errors[i] = new THStack("","");
    sum_exp_errors[i]  = new THStack("","");
    sum_mod_errors[i]  = new THStack("","");
    sum_errors[i]      = new THStack("","");

  }

}


void setHistogramStyle(TH1* hist, Color_t LineColor, Style_t LineStyle, Width_t LineWidth, Color_t HistColor) {

  hist->SetLineColor(LineColor);
  hist->SetLineStyle(LineStyle);
  hist->SetLineWidth(LineWidth);
  hist->SetFillColor(HistColor);

  return;

}


TH1* SummedStackHisto(const THStack* stack) {

  TList* l = stack->GetHists();

  if ( l->GetEntries() == 0 )  return 0;

  TH1* result = (TH1*)l->At(0)->Clone();

  for(int i = 1; i < l->GetEntries(); ++i) {

    result->Add((TH1*)l->At(i));

  }

  return result;

}


void SymmetrizeAroundZero_OLD(TH1* h_sys, TH1* h_sys2) {

  Int_t N_bins = h_sys->GetNbinsX();

  Double_t Sys_Error  = 0.;
  Double_t Sys_Error2 = 0.;
  Double_t Sum_Errors = 0.;

  cout << ">>>   Symmetrizing Errors:" << endl;
  cout << "--------------------------" << endl << endl;

  for(Int_t bin = 1; bin <= h_sys->GetNbinsX()/2; ++bin) {

    if( h_sys->GetBinContent(bin) == 0 )  continue;

    Double_t PlusMinus_Average = (h_sys->GetBinContent(bin) + h_sys->GetBinContent(N_bins+1-bin))/2.;

    Sys_Error  = PlusMinus_Average;
    Sys_Error2 = Sys_Error * Sys_Error;

    h_sys->SetBinContent(           bin, Sys_Error  );
    h_sys->SetBinContent(  N_bins+1-bin, Sys_Error  );
    h_sys2->SetBinContent(          bin, Sys_Error2 );
    h_sys2->SetBinContent( N_bins+1-bin, Sys_Error2 );

    cout << "Sys. Error: " << Sys_Error << endl;
    Sum_Errors += (2.*Sys_Error);

  }

  cout << "------------------" << endl;
  cout << " Sym. Ave. Error: " << Sum_Errors/N_bins << endl;
  cout << "------------------" << endl << endl;

}


void SymmetrizeAroundZero(TH1* h_ref, TH1* h_var_up, TH1* h_var_down, TH1* h_sys, TH1* h_sys2, Double_t &Sum_Errors, const Double_t scale) {

  Int_t N_bins = h_ref->GetNbinsX();

  Double_t Sys_Error      = 0.;
  Double_t Sys_Error2     = 0.;
  Double_t Sys_Error_Up   = 0.;
  Double_t Sys_Error_Down = 0.;

  for(Int_t bin = 1; bin <= h_ref->GetNbinsX()/2; ++bin) {

    if( h_ref->GetBinContent(bin) == 0 )  continue;

    Double_t PlusMinus_Average_Ref  = 0.;
    Double_t PlusMinus_Average_Up   = 0.;
    Double_t PlusMinus_Average_Down = 0.;

    PlusMinus_Average_Ref  = (h_ref->GetBinContent(bin)      + h_ref->GetBinContent(N_bins+1-bin)     ) / 2.;
    PlusMinus_Average_Up   = (h_var_up->GetBinContent(bin)   + h_var_up->GetBinContent(N_bins+1-bin)  ) / 2.;
    PlusMinus_Average_Down = (h_var_down->GetBinContent(bin) + h_var_down->GetBinContent(N_bins+1-bin)) / 2.;

    Sys_Error_Up   = abs(PlusMinus_Average_Ref - PlusMinus_Average_Up  ) / PlusMinus_Average_Ref;
    Sys_Error_Down = abs(PlusMinus_Average_Ref - PlusMinus_Average_Down) / PlusMinus_Average_Ref;

    Sys_Error  = (Sys_Error_Up+Sys_Error_Down)/(2.*scale);
    Sys_Error2 = Sys_Error * Sys_Error;

    h_sys->SetBinContent(           bin, Sys_Error  );
    h_sys->SetBinContent(  N_bins+1-bin, Sys_Error  );
    h_sys2->SetBinContent(          bin, Sys_Error2 );
    h_sys2->SetBinContent( N_bins+1-bin, Sys_Error2 );

    cout << "Sys. Error: " << Sys_Error << endl;
    Sum_Errors += (2.*Sys_Error);

  }

}


void CalculateSystematicErrors(Color_t LineColor, Style_t LineStyle, Width_t LineWidth, Color_t HistColor,
			       TFile* file_ref, TFile* file_var_up, TFile* file_var_down, THStack* errors[], const TString label, const Double_t scale) {

  TList* ListOfKeys = file_ref->GetListOfKeys();

  TH1* h_ref;
  TH1* h_style = 0;
  TH1* h_var_up;
  TH1* h_var_down;

  for(Int_t j = 0; j < ListOfKeys->GetEntries(); ++j) {

    TString title = ListOfKeys->At(j)->GetName();
    cout << "   >>>   " << title << endl;

    //     if( label.Contains("Q2_SCALE") || label.Contains("TOP_MASS") || label.Contains("MATCHING") || label.Contains("HADRON") ) {
    //       if( !(isPSE) &&   title.Contains("PSE_")  )  continue;
    //       if(   isPSE  && !(title.Contains("PSE_")) )  continue;
    //     }

    //     else if( title.Contains("PSE_") )  continue;

    if( title.Contains("PSE_") )  continue;

    Double_t Sys_Error      = 0.;
    Double_t Sys_Error2     = 0.;
    Double_t Sys_Error_Up   = 0.;
    Double_t Sys_Error_Down = 0.;
    Double_t Sum_Errors     = 0.;

    file_ref->GetObject(      title, h_ref);
    file_ref->GetObject(      title, h_style);
    file_var_up->GetObject(   title, h_var_up);
    file_var_down->GetObject( title, h_var_down);

    TH1* h_sys  = (TH1*) h_var_up->Clone();   h_sys->Reset();
    TH1* h_sys2 = (TH1*) h_var_down->Clone(); h_sys2->Reset();

    setHistogramStyle(h_ref,      kBlack, 1, 2, HistColor);
    setHistogramStyle(h_var_up,   kBlue,  1, 1, HistColor);
    setHistogramStyle(h_var_down, kRed,   1, 1, HistColor);

    TCanvas* Canvas = new TCanvas("plot", "plot", 800, 800);

    Canvas->Clear();
    h_ref->SetMarkerColor(kBlack);
    h_ref->Draw();
    h_var_up->SetMarkerColor(kBlue);
    h_var_up->Draw("SAME");
    h_var_down->SetMarkerColor(kRed);
    h_var_down->Draw("SAME");
    if(set_LogY) gPad->SetLogy();
    Canvas->Print(outpath.Copy().Append(title).Append("_").Append(label).Append(outform));

    Int_t N_bins = h_ref->GetNbinsX();

    if( (title.Contains("Leptons_Eta") || title.Contains("TopQuarks_Rapidity")) &&
	(label.Contains("MLL30") || label.Contains("Q2_SCALE") || label.Contains("TOP_MASS") || label.Contains("MATCHING") || label.Contains("HADRON")) ) {
      SymmetrizeAroundZero(h_ref, h_var_up, h_var_down, h_sys, h_sys2, Sum_Errors, scale);
    }

    else {
      for(Int_t bin = 1; bin <= h_ref->GetNbinsX(); ++bin) {
	if( h_ref->GetBinContent(bin) == 0 )  continue;
	Sys_Error_Up   = abs(h_ref->GetBinContent(bin) - h_var_up->GetBinContent(bin))/h_ref->GetBinContent(bin);
	Sys_Error_Down = abs(h_ref->GetBinContent(bin) - h_var_down->GetBinContent(bin))/h_ref->GetBinContent(bin);
	Sys_Error  = (Sys_Error_Up+Sys_Error_Down)/(2.*scale);
	Sys_Error2 = Sys_Error * Sys_Error;
	h_sys->SetBinContent(  bin, Sys_Error  );
	h_sys2->SetBinContent( bin, Sys_Error2 );
	cout << "Sys. Error: " << Sys_Error << endl;
	Sum_Errors += Sys_Error;
      }
    }

    cout << "-------------" << endl;
    cout << " Ave. Error: " << Sum_Errors/N_bins << endl;
    cout << "-------------" << endl << endl;

    setHistogramStyle(h_sys,  LineColor, LineStyle, LineWidth, HistColor);
    setHistogramStyle(h_sys2, LineColor, LineStyle, LineWidth, HistColor);
    h_style = h_sys;
    title.Append("_sys_error_");
    title.Append(label);
    h_sys->SetName(title);
    Hlist.Add(h_sys);

    sum_errors[j]->Add(h_sys2);
    errors[j]->Add(h_sys2);

  }

  leg->AddEntry(h_style,label,"F");
  cout << "-------------" << endl << endl;

}


void SetConstantErrors(Color_t LineColor, Style_t LineStyle, Width_t LineWidth, Color_t HistColor, TFile* file_ref, THStack* errors[], const TString label,
		       Double_t Total_mumu, Double_t Total_ee, Double_t Total_emu, Double_t Total_combined,
		       Double_t  Diff_mumu, Double_t  Diff_ee, Double_t  Diff_emu, Double_t  Diff_combined ) {

  TList* ListOfKeys = file_ref->GetListOfKeys();

  TH1* h_ref;
  TH1* h_style = 0;

  for(Int_t j = 0; j < ListOfKeys->GetEntries(); ++j) {

    TString title = ListOfKeys->At(j)->GetName();
    cout << "   >>>   " << title << endl;
    if( title.Contains("PSE_") )  continue;

    Double_t Sys_Error  = 0.;
    Double_t Sys_Error2 = 0.;
    Double_t Sum_Errors = 0.;

    file_ref->GetObject( title, h_ref);
    file_ref->GetObject( title, h_style);

    TH1* h_sys   = (TH1*) h_ref->Clone(); h_sys->Reset();
    TH1* h_sys2  = (TH1*) h_ref->Clone(); h_sys2->Reset();

    Int_t N_bins = h_ref->GetNbinsX();

    for(Int_t bin = 1; bin <= h_ref->GetNbinsX(); ++bin) {

      //  TOTAL XS
      if(isTotal) {
	if( title.Contains("mumu_") )      Sys_Error = Total_mumu;
	if( title.Contains("ee_") )        Sys_Error = Total_ee;
	if( title.Contains("emu_") )       Sys_Error = Total_emu;
	if( title.Contains("combined_") )  Sys_Error = Total_combined;
      }

      //  DIFFERENTIAL XS
      if(isDiff) {
	if( title.Contains("mumu_") )      Sys_Error = Diff_mumu;
	if( title.Contains("ee_") )        Sys_Error = Diff_ee;
	if( title.Contains("emu_") )       Sys_Error = Diff_emu;
	if( title.Contains("combined_") )  Sys_Error = Diff_combined;
      }

      Sys_Error2 = Sys_Error * Sys_Error;

      h_sys->SetBinContent(  bin, Sys_Error  );
      h_sys2->SetBinContent( bin, Sys_Error2 );
      cout << "Sys. Error: " << Sys_Error << endl;
      Sum_Errors += Sys_Error;

    }

    cout << "-------------" << endl;
    cout << " Ave. Error: " << Sum_Errors/N_bins << endl;
    cout << "-------------" << endl << endl;

    setHistogramStyle(h_sys,  LineColor, LineStyle, LineWidth, HistColor);
    setHistogramStyle(h_sys2, LineColor, LineStyle, LineWidth, HistColor);
    h_style = h_sys;
    title.Append("_sys_error_");
    title.Append(label);
    h_sys->SetName(title);
    Hlist.Add(h_sys);
    sum_errors[j]->Add(h_sys2);
    errors[j]->Add(h_sys2);

  }

  leg->AddEntry(h_style,label,"F");
  cout << "-------------" << endl << endl;

}


void DrawStatisticalErrors(Color_t LineColor, Style_t LineStyle, Width_t LineWidth, Color_t HistColor, TFile* file_ref) {

  TList* ListOfKeys = file_ref->GetListOfKeys();

  TH1* h_ref;
  TH1* h_style = 0;

  for(Int_t j = 0; j < ListOfKeys->GetEntries(); ++j) {

    TString title = ListOfKeys->At(j)->GetName();
    cout << "   >>>   " << title << endl;
    if( title.Contains("PSE_") )  continue;

    Double_t Stat_Error  = 0.;
    Double_t Stat_Error2 = 0.;
    Double_t Sum_Errors  = 0.;

    file_ref->GetObject( title, h_ref);
    file_ref->GetObject( title, h_style);

    TH1* h_stat  = (TH1*) h_ref->Clone();   h_stat->Reset();
    TH1* h_stat2 = (TH1*) h_ref->Clone();   h_stat2->Reset();

    Int_t N_bins = h_ref->GetNbinsX();

    for(Int_t bin = 1; bin <= h_ref->GetNbinsX(); ++bin) {

      if( h_ref->GetBinContent(bin) == 0 )  continue;

      Stat_Error  = h_ref->GetBinError(bin)/h_ref->GetBinContent(bin);
      Stat_Error2 = Stat_Error * Stat_Error;
      h_stat->SetBinContent(  bin, Stat_Error  );
      h_stat2->SetBinContent( bin, Stat_Error2 );
      cout << "Stat. Error: " << Stat_Error << endl;
      Sum_Errors += Stat_Error;

    }

    cout << "-------------" << endl;
    cout << " Ave. Error: " << Sum_Errors/N_bins << endl;
    cout << "-------------" << endl << endl;

    setHistogramStyle(h_stat,  LineColor, LineStyle, LineWidth, HistColor);
    setHistogramStyle(h_stat2, LineColor, LineStyle, LineWidth, HistColor);
    h_style = h_stat;
    title.Append("_STAT_error");
    h_stat->SetName(title);
    Hlist.Add(h_stat);
    sum_errors[j]->Add(h_stat2);
    sum_stat_errors[j]->Add(h_stat2);

  }

  leg->AddEntry(h_style,"Statistical","F");
  cout << "-------------" << endl << endl;

}


void CalculateTotalErrors(TFile* file_ref, Double_t Hist_max, Double_t Hist_min) {

  TList* ListOfKeys = file_ref->GetListOfKeys();

  TH1* h;

  for(Int_t i = 0; i < ListOfKeys->GetEntries(); ++i) {

    TString title = ListOfKeys->At(i)->GetName();
    if( title.Contains("PSE_") )  continue;

    file_ref->GetObject(title, h);
    TAxis* xaxis = h->GetXaxis();

    title.Append("_total_error2");
    sum_errors[i]->SetName(title);

    TCanvas* Canvas = new TCanvas("plot", "plot", 800, 800);
    Canvas->Clear();
    sum_errors[i]->Draw("HIST");
    leg->Draw("SAME");

    if( sum_errors[i]->GetMaximum() > 0. )  Hist_max = sum_errors[i]->GetMaximum();
    sum_errors[i]->SetMaximum(1.8 * Hist_max);
    sum_errors[i]->SetMinimum(Hist_min);
    sum_errors[i]->GetXaxis()->SetTitle(xaxis->GetTitle());
    sum_errors[i]->GetYaxis()->SetTitle("#sum #left( #frac{#Delta #sigma}{#sigma} #right)^{2}");
    sum_errors[i]->GetYaxis()->SetTitleOffset(2.4);
    sum_errors[i]->GetYaxis()->SetTitleSize(0.035);

    Canvas->Print(outpath.Copy().Append(title).Append(outform));

    Hlist.Add(sum_errors[i]);

    TH1* total_error = SummedStackHisto(sum_errors[i]);

    for(Int_t bin = 1; bin <= total_error->GetNbinsX(); ++bin) {
      Double_t Total_Error = sqrt(total_error->GetBinContent(bin));
      total_error->SetBinContent( bin, Total_Error );
    }

    // reset title
    title = ListOfKeys->At(i)->GetName();
    title.Append("_total_error");
    total_error->SetName(title);
    Hlist.Add(total_error);

  }

}


void SummarizeAllErrors(TFile* file_ref, Double_t Hist_max, Double_t Hist_min) {

  TList* ListOfKeys = file_ref->GetListOfKeys();

  TH1* h;

  TH1* stat_error = 0;
  TH1*  exp_error = 0;
  TH1*  mod_error = 0;

  for(Int_t i = 0; i < ListOfKeys->GetEntries(); ++i) {

    TString title = ListOfKeys->At(i)->GetName();
    if( title.Contains("PSE_") )  continue;

    file_ref->GetObject(title, h);
    TAxis* xaxis = h->GetXaxis();

    TH1* total_error = SummedStackHisto(sum_errors[i]);
    setHistogramStyle(total_error, kBlack, 1., 4., 0.);
    total_error->SetFillStyle(0);

    if ( isStat ) {
      stat_error = SummedStackHisto(sum_stat_errors[i]);
      setHistogramStyle(stat_error, kBlue, 1., 3., 0.);
      stat_error->SetFillStyle(0);
      // reset title
      title = ListOfKeys->At(i)->GetName();
      title.Append("_stat_error");
      stat_error->SetName(title);
    }

    if ( isExp ) {
      exp_error = SummedStackHisto( sum_exp_errors[i]);
      setHistogramStyle(exp_error, kRed, 1., 3., 0.);
      exp_error->SetFillStyle(0);
      // reset title
      title = ListOfKeys->At(i)->GetName();
      title.Append("_exp_error");
      exp_error->SetName(title);
    }

    if ( isModel ) {
      mod_error = SummedStackHisto( sum_mod_errors[i]);
      setHistogramStyle(mod_error, kGreen, 1., 3., 0.);
      mod_error->SetFillStyle(0);
      // reset title
      title = ListOfKeys->At(i)->GetName();
      title.Append("_mod_error");
      mod_error->SetName(title);
    }

    for(Int_t bin = 1; bin <= total_error->GetNbinsX(); ++bin) {

      Double_t Total_Error = sqrt(total_error->GetBinContent(bin));
      total_error->SetBinContent( bin, Total_Error );

      if ( isStat ) {
	Double_t Stat_Error = sqrt(stat_error->GetBinContent(bin));
	stat_error->SetBinContent( bin, Stat_Error );
      }

      if ( isExp ) {
	Double_t  Exp_Error = sqrt(exp_error->GetBinContent(bin));
	exp_error->SetBinContent( bin, Exp_Error );
      }

      if ( isModel ) {
	Double_t Model_Error = sqrt(mod_error->GetBinContent(bin));
	mod_error->SetBinContent( bin, Model_Error );
      }

    }

    TLegend* leg2 = new TLegend(0.70,0.58,0.95,0.87);
    leg2->Clear();
    leg2->SetFillStyle(0);
    leg2->SetBorderSize(0);
    if ( isStat  )  leg2->AddEntry(stat_error,"Statistical","L");
    if ( isExp   )  leg2->AddEntry(exp_error,"Experimental","L");
    if ( isModel )  leg2->AddEntry(mod_error,"Model","L");
    leg2->AddEntry(total_error,"Total error","L");

    if( total_error->GetMaximum() > 0. )  Hist_max = total_error->GetMaximum();
    total_error->SetMaximum(2. * Hist_max);
    total_error->SetMinimum(Hist_min);
    total_error->GetXaxis()->SetTitle(xaxis->GetTitle());
    total_error->GetYaxis()->SetTitle("#frac{#Delta #sigma}{#sigma}");
    total_error->GetYaxis()->SetTitleOffset(2.4);
    total_error->GetYaxis()->SetTitleSize(0.035);

    if ( isStat  )  Hlist.Add(stat_error);
    if ( isExp   )  Hlist.Add(exp_error);
    if ( isModel )  Hlist.Add(mod_error);

    TCanvas* Canvas2 = new TCanvas("plot2", "plot2", 800, 800);

    Canvas2->Clear();
    total_error->Draw("F");
    if ( isStat  )  stat_error->Draw("F,SAME");
    if ( isExp   )  exp_error->Draw("F,SAME");
    if ( isModel )  mod_error->Draw("F,SAME");
    leg2->Draw("SAME");

    // reset title
    title = ListOfKeys->At(i)->GetName();
    title.Append("_all_errors");

    Canvas2->Print(outpath.Copy().Append(title).Append(outform));

  }

}


void SystematicErrors() {

  leg->Clear();
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);

  files[0] = new TFile(inpath.Copy().Append("standard.root"));

  setupTotalErrors();

  Color_t LineColor = kBlack;
  Style_t LineStyle = 1;
  Width_t LineWidth = 1;
  Color_t HistColor = kRed+1;

  ////////////////////////////////////////////////////////////////////////
  //  Statistical Error --------------------------------------------------
  ////////////////////////////////////////////////////////////////////////

  if(isStat) {

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kGray+3;

    files[0] = new TFile(inpath.Copy().Append("standard.root"));
    //    files[0] = new TFile("/afs/naf.desy.de/user/w/wbehrenh/scratch/final/standard/plots_5fb/DiffXS_Histograms.root");
    //    files[0] = new TFile("/afs/naf.desy.de/user/w/wbehrenh/scratch/final/standard/plots_2fb/DiffXS_Histograms.root");
    //    files[0] = new TFile("/afs/naf.desy.de/user/w/wbehrenh/scratch/final/standard/plots_2011b/DiffXS_Histograms.root");
    //    files[0] = new TFile("/afs/naf.desy.de/user/w/wbehrenh/scratch/final/standard/plots_2011av5v6/DiffXS_Histograms.root");

    if( files[0] && !files[0]->IsZombie() ) {
      cout << "--------------------------------" << endl;
      cout << "   >>>   " << "Statistical Error" << endl;
      cout << "--------------------------------" << endl << endl;
      DrawStatisticalErrors(LineColor, LineStyle, LineWidth, HistColor, files[0]);
    }

  }

  ////////////////////////////////////////////////////////////////////////
  //  Experimental Errors ------------------------------------------------
  ////////////////////////////////////////////////////////////////////////

  if(isExp) {

    //  JER --------------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kRed+1;

    files[0] = new TFile(inpath.Copy().Append("standard.root"));
    files[1] = new TFile(inpath.Copy().Append("jer_up.root"));
    files[2] = new TFile(inpath.Copy().Append("jer_down.root"));

    if( files[0] && !files[0]->IsZombie() && files[1] && !files[1]->IsZombie() && files[2] && !files[2]->IsZombie() ) {
      cout << "------------------------------------" << endl;
      cout << "   >>>   " << "Jet Energy RESOLUTION" << endl;
      cout << "------------------------------------" << endl << endl;
      CalculateSystematicErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], files[1], files[2], sum_exp_errors, "JER", 1.);
    }

    //  JES --------------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kRed-7;

    files[0] = new TFile(inpath.Copy().Append("standard.root"));
    files[3] = new TFile(inpath.Copy().Append("jes_up.root"));
    files[4] = new TFile(inpath.Copy().Append("jes_down.root"));

    if( files[0] && !files[0]->IsZombie() && files[3] && !files[3]->IsZombie() && files[4] && !files[4]->IsZombie() ) {
      cout << "-------------------------------" << endl;
      cout << "   >>>   " << "Jet Energy SCALE" << endl;
      cout << "-------------------------------" << endl << endl;
      CalculateSystematicErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], files[3], files[4], sum_exp_errors, "JES", 1.);
    }

    //  BG -------------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kPink;

    files[0] = new TFile(inpath.Copy().Append("standard.root"));
    files[5] = new TFile(inpath.Copy().Append("bg_up.root"));
    files[6] = new TFile(inpath.Copy().Append("bg_down.root"));

    if( files[0] && !files[0]->IsZombie() && files[5] && !files[5]->IsZombie() && files[6] && !files[6]->IsZombie() ) {
      cout << "--------------------------" << endl;
      cout << "   >>>   " << "BACKGROUNDS" << endl;
      cout << "--------------------------" << endl << endl;
      CalculateSystematicErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], files[5], files[6], sum_exp_errors, "BG", 1.);
    }

    //  DY ----------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kAzure+8;

    files[0] = new TFile(inpath.Copy().Append("standard.root"));
    files[7] = new TFile(inpath.Copy().Append("dy_up.root"));
    files[8] = new TFile(inpath.Copy().Append("dy_down.root"));

    if( files[0] && !files[0]->IsZombie() && files[7] && !files[7]->IsZombie() && files[8] && !files[8]->IsZombie() ) {
      cout << "------------------------" << endl;
      cout << "   >>>   " << "DRELL-YAN" << endl;
      cout << "------------------------" << endl << endl;
      CalculateSystematicErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], files[7], files[8], sum_exp_errors, "DY", 1.);
    }

    //  DY FROM MLL30 ----------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kAzure+8;

    files[0]  = new TFile(inpath.Copy().Append("standard.root"));
    files[9]  = new TFile(inpath.Copy().Append("standard_new.root"));
    //    files[10] = new TFile(inpath.Copy().Append("mll20_new.root"));
    files[10] = new TFile(inpath.Copy().Append("mll30_new.root"));
    //    files[10] = new TFile(inpath.Copy().Append("mll40_new.root"));
    //    files[10] = new TFile(inpath.Copy().Append("mll50_new.root"));

    if( files[0] && !files[0]->IsZombie() && files[9] && !files[9]->IsZombie() &&  files[10] && !files[10]->IsZombie() ) {
      cout << "--------------------" << endl;
      cout << "   >>>   " << "MLL30" << endl;
      cout << "--------------------" << endl << endl;
      CalculateSystematicErrors(LineColor, LineStyle, LineWidth, HistColor, files[9], files[10], files[10], sum_exp_errors, "MLL30", 1.);
    }

    // PILE-UP ----------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kYellow;

    files[0]  = new TFile(inpath.Copy().Append("standard.root"));
    files[11] = new TFile(inpath.Copy().Append("pu_up.root"));
    files[12] = new TFile(inpath.Copy().Append("pu_down.root"));

    if( files[0] && !files[0]->IsZombie() && files[11] && !files[11]->IsZombie() && files[12] && !files[12]->IsZombie() ) {
      cout << "----------------------" << endl;
      cout << "   >>>   " << "PILE-UP" << endl;
      cout << "----------------------" << endl << endl;
      CalculateSystematicErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], files[11], files[12], sum_exp_errors, "PILE_UP", 1.);
    }

    //  KIN FIT  --------------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kYellow-6;

    files[0]  = new TFile(inpath.Copy().Append("standard.root"));
    files[13] = new TFile(inpath.Copy().Append("no_kin_scale.root"));
    files[14] = new TFile(inpath.Copy().Append("standard.root"));
    //    files[14] = new TFile(inpath.Copy().Append("kin_scale2.root"));

    if( files[0] && !files[0]->IsZombie() && files[13] && !files[13]->IsZombie() &&  files[14] && !files[14]->IsZombie() ) {
      cout << "----------------------" << endl;
      cout << "   >>>   " << "KIN FIT" << endl;
      cout << "----------------------" << endl << endl;
      CalculateSystematicErrors(LineColor, LineStyle, LineWidth, HistColor, files[13], files[14], files[14], sum_exp_errors, "KIN_FIT", 1.);
    }

    // BTAG ----------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kAzure-2;

    if( files[0] && !files[0]->IsZombie() ) {
      cout << "------------------------" << endl;
      cout << "   >>>   " << "B-TAGGING" << endl;
      cout << "------------------------" << endl << endl;
      Double_t BTAG_Total_mumu     = 0.06;
      Double_t BTAG_Total_ee       = 0.06;
      Double_t BTAG_Total_emu      = 0.06;
      Double_t BTAG_Total_combined = 0.035;
      Double_t BTAG_Diff_mumu      = 0.03;
      Double_t BTAG_Diff_ee        = 0.03;
      Double_t BTAG_Diff_emu       = 0.03;
      Double_t BTAG_Diff_combined  = 0.017;

      SetConstantErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], sum_exp_errors, "BTAG",
			BTAG_Total_mumu, BTAG_Total_ee, BTAG_Total_emu, BTAG_Total_combined, BTAG_Diff_mumu, BTAG_Diff_ee, BTAG_Diff_emu, BTAG_Diff_combined);
    }

    // TRIGGER EFFICIENCIES -----------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kGreen-3;

    if( files[0] && !files[0]->IsZombie() ) {
      cout << "-----------------------------------" << endl;
      cout << "   >>>   " << "TRIGGER Efficiencies" << endl;
      cout << "-----------------------------------" << endl << endl;
      Double_t TRIG_Total_mumu     = 0.015;
      Double_t TRIG_Total_ee       = 0.025;
      Double_t TRIG_Total_emu      = 0.020;
      Double_t TRIG_Total_combined = 0.011;
      Double_t TRIG_Diff_mumu      = 0.015;
      Double_t TRIG_Diff_ee        = 0.025;
      Double_t TRIG_Diff_emu       = 0.020;
      Double_t TRIG_Diff_combined  = 0.011;

      SetConstantErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], sum_exp_errors, "TRIGGER",
			TRIG_Total_mumu, TRIG_Total_ee, TRIG_Total_emu, TRIG_Total_combined, TRIG_Diff_mumu, TRIG_Diff_ee, TRIG_Diff_emu, TRIG_Diff_combined);
    }

    // LEPTON SELECTION MODEL ------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kGreen+3;

    if( files[0] && !files[0]->IsZombie() ) {
      cout << "---------------------------" << endl;
      cout << "   >>>   " << "Lepton MODEL" << endl;
      cout << "---------------------------" << endl << endl;
      Double_t LEP_Total_mumu     = 0.04;
      Double_t LEP_Total_ee       = 0.04;
      Double_t LEP_Total_emu      = 0.04;
      Double_t LEP_Total_combined = 0.023;
      Double_t LEP_Diff_mumu      = 0.02;
      Double_t LEP_Diff_ee        = 0.02;
      Double_t LEP_Diff_emu       = 0.02;
      Double_t LEP_Diff_combined  = 0.012;

      SetConstantErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], sum_exp_errors, "LEPTON_ID",
			LEP_Total_mumu, LEP_Total_ee, LEP_Total_emu, LEP_Total_combined, LEP_Diff_mumu, LEP_Diff_ee, LEP_Diff_emu, LEP_Diff_combined);
    }

  }

  ///////////////////////////////////////////////////////////////////////
  //  Theoretical Errors ------------------------------------------------
  ///////////////////////////////////////////////////////////////////////

  if (isModel) {

    // Q^2 Scale ----------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kMagenta-4;

    files[0]  = new TFile(inpath.Copy().Append("madgraph_Fall10.root"));
    files[15] = new TFile(inpath.Copy().Append("scaleup_Fall10.root"));
    files[16] = new TFile(inpath.Copy().Append("scaledown_Fall10.root"));

    if( files[0] && !files[0]->IsZombie() && files[15] && !files[15]->IsZombie() && files[16] && !files[16]->IsZombie() ) {
      cout << "----------------------" << endl;
      cout << "   >>>   " << "Q Scale" << endl;
      cout << "----------------------" << endl << endl;
      CalculateSystematicErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], files[15], files[16], sum_mod_errors, "Q2_SCALE", 1.);
    }

    // Top mass ----------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kMagenta-2;

    files[0]  = new TFile(inpath.Copy().Append("madgraph_Fall10.root"));
    files[17] = new TFile(inpath.Copy().Append("mass178_5_Fall10.root"));
    files[18] = new TFile(inpath.Copy().Append("mass166_5_Fall10.root"));

    if( files[0] && !files[0]->IsZombie() && files[17] && !files[17]->IsZombie() && files[18] && !files[18]->IsZombie() ) {
      cout << "-----------------------" << endl;
      cout << "   >>>   " << "Top Mass" << endl;
      cout << "-----------------------" << endl << endl;
      CalculateSystematicErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], files[17], files[18], sum_mod_errors, "TOP_MASS", 5.);
    }

    // ME/PS matching ----------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kMagenta+4;

    files[0]  = new TFile(inpath.Copy().Append("madgraph_Fall10.root"));
    files[19] = new TFile(inpath.Copy().Append("matchingup_Fall10.root"));
    files[20] = new TFile(inpath.Copy().Append("matchingdown_Fall10.root"));

    if( files[0] && !files[0]->IsZombie() && files[19] && !files[19]->IsZombie() && files[20] && !files[20]->IsZombie() ) {
      cout << "-----------------------------" << endl;
      cout << "   >>>   " << "ME/PS Matching" << endl;
      cout << "-----------------------------" << endl << endl;
      CalculateSystematicErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], files[19], files[20], sum_mod_errors, "MATCHING", 1.);
    }

    //  HADRONISATION --------------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kMagenta-6;

    files[21] = new TFile(inpath.Copy().Append("powheg_pythia6_Fall10.root"));
    files[22] = new TFile(inpath.Copy().Append("powheg_herwig6_Fall10.root"));

    if( files[21] && !files[21]->IsZombie() && files[22] && !files[22]->IsZombie() ) {
      cout << "----------------------------" << endl;
      cout << "   >>>   " << "Hadronisation" << endl;
      cout << "----------------------------" << endl << endl;
      CalculateSystematicErrors(LineColor, LineStyle, LineWidth, HistColor, files[21], files[22], files[22], sum_mod_errors, "HADRON", 1.);
    }

  }

  ///////////////////////////////////////////////////////////////////////
  //  TOTAL Cross Section Errors ----------------------------------------
  ///////////////////////////////////////////////////////////////////////

  if(isTotal) {

    // BR  ----------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kBlue+1;

    if( files[0] && !files[0]->IsZombie() ) {
      cout << "------------------------------" << endl;
      cout << "   >>>   " << "Branching Ratio" << endl;
      cout << "------------------------------" << endl << endl;
      Double_t BR_Total_mumu     = 0.015;
      Double_t BR_Total_ee       = 0.015;
      Double_t BR_Total_emu      = 0.015;
      Double_t BR_Total_combined = 0.015;
      Double_t BR_Diff_mumu      = 0.;
      Double_t BR_Diff_ee        = 0.;
      Double_t BR_Diff_emu       = 0.;
      Double_t BR_Diff_combined  = 0.;

      SetConstantErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], sum_mod_errors, "BR",
			BR_Total_mumu, BR_Total_ee, BR_Total_emu, BR_Total_combined, BR_Diff_mumu, BR_Diff_ee, BR_Diff_emu, BR_Diff_combined);
    }

    // LUMINOSITY  ----------------------------------------------

    LineColor = kBlack;
    LineStyle = 1;
    LineWidth = 1;
    HistColor = kAzure+5;

    if( files[0] && !files[0]->IsZombie() ) {
      cout << "-------------------------" << endl;
      cout << "   >>>   " << "LUMINOSITY" << endl;
      cout << "-------------------------" << endl << endl;
      Double_t LUMI_Total_mumu     = 0.045;
      Double_t LUMI_Total_ee       = 0.045;
      Double_t LUMI_Total_emu      = 0.045;
      Double_t LUMI_Total_combined = 0.045;
      Double_t LUMI_Diff_mumu      = 0.;
      Double_t LUMI_Diff_ee        = 0.;
      Double_t LUMI_Diff_emu       = 0.;
      Double_t LUMI_Diff_combined  = 0.;

      SetConstantErrors(LineColor, LineStyle, LineWidth, HistColor, files[0], sum_exp_errors, "LUMI",
			LUMI_Total_mumu, LUMI_Total_ee, LUMI_Total_emu, LUMI_Total_combined, LUMI_Diff_mumu, LUMI_Diff_ee, LUMI_Diff_emu, LUMI_Diff_combined);
    }

  }

}


void CompactSystematicError() {

  if( !(isModel) && !(isExp) && !(isStat) ) {

    cout << "++++++++++++++++++++++++" << endl << endl;
    cout << "No uncertainty selected!" << endl << endl;
    cout << "++++++++++++++++++++++++" << endl << endl;

    return;

  }

  setHHStyle(*gStyle);
  SystematicErrors();

  Double_t Hist_max = 1.;
  Double_t Hist_min = 0.;

  CalculateTotalErrors(files[0], Hist_max, Hist_min);
  SummarizeAllErrors(  files[0], Hist_max, Hist_min);

  TFile outfile(outfileName,"recreate");
  Hlist.Write();
  outfile.Close();
  cout << "-------------------------" << endl << endl;

}


int main() {

  CompactSystematicError();

}
