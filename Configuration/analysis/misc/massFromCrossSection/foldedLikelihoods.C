//
// 1. initialize an up-to-date ROOT version, e.g. with: ini ROOT528
//    (there are issues when drawing graphs with errors in old ROOT versions)
// 2. compile like: g++ -Wall `root-config --cflags --libs` -lRooFit -o foldedLikelihoods foldedLikelihoods.C
// 3. execute with: foldedLikelihoods
//

#include "Riostream.h"

#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "TLegend.h"
#include "TMath.h"
#include "TROOT.h"

#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooRealVar.h"

#include <iostream>

#include "tdrstyle.C"

double alpha_s(const double Q)
{
  //
  // c.f. arXiv:0908.1135 (Bethke: The 2009 World Average of alphaS)
  //
  const unsigned Nf = 5; // number of active flavors (assumed range here: from b mass threshold up to top mass scale!)
  const double lambda2 = 0.213*0.213; // from lambda_MSbar with alpha_s(mZ) = 0.1184 and Nf = 5
  const double beta0 = (33-2*Nf)/(12*TMath::Pi());
  const double beta1 = (153-19*Nf)/(24*TMath::Power(TMath::Pi(),2));
  const double beta2 = (77139-15099*Nf+325*Nf*Nf)/(3456*TMath::Power(TMath::Pi(),3));
  const double L = TMath::Log(Q*Q/lambda2);
  const double lnL = TMath::Log(L);
  return 1./(beta0*L) - beta1*lnL/(beta0*beta0*beta0*L*L)
    + 1./(beta0*beta0*beta0*L*L*L)*(TMath::Power(beta1/beta0,2)*(lnL*lnL-lnL-1)+beta2/beta0);
  //  return alpha_s_mZ / (1+alpha_s_mZ*beta0*TMath::Log(Q*Q/mZ/mZ)); // just as a cross check: the 1-loop approximation
}

double mMSbar(const double mPole, const double alpha_s)
{
  //
  // c.f. arXiv:0805.1333 (Bernreuther: Top Quark Physics at the LHC)
  // note that the value of alpha_s has to be given in the MSbar scheme!
  //
  const double aOverPi = alpha_s / TMath::Pi();
  return mPole / (1. + 4./3*aOverPi + 8.2364*TMath::Power(aOverPi,2) + 73.638*TMath::Power(aOverPi,3));
}

double mMSbar(const double mPole)
{
  //
  // including iterative calculation of alpha_s(mMSbar)
  //
  double mMSbarPre = mPole;
  double mMSbarNew = mPole;
  do {
    const double alpha = alpha_s(mMSbarNew);
    mMSbarPre = mMSbarNew;
    mMSbarNew = mMSbar(mPole, alpha);
  } while(TMath::Abs(mMSbarNew-mMSbarPre) > 0.01); // convergence criterion
  return mMSbarNew;
}

TGraph* getRunningAlphaGraph()
{
  int n = 111;
  double mass [n];
  double alpha[n];
  double m = 80;
  for(int i=0; i<n; i++) {
    mass [i] = m;
    alpha[i] = alpha_s(m);
    m += 1;
  }
  TGraph* graph = new TGraph(n, mass, alpha);
  graph->GetXaxis()->SetTitle("Q (GeV)");
  graph->GetYaxis()->SetTitle("#alpha_{S}");
  graph->SetTitle("At three-loop level and with N(flavors)=5, using 2009 world average for #alpha_{s}(M_{Z})");
  graph->GetYaxis()->CenterTitle();
  return graph;
}

TGraph* getMassShiftGraph()
{
  int n = 81;
  double mass [n];
  double shift[n];
  double m = 140;
  for(int i=0; i<n; i++) {
    mass [i] = mMSbar(m);
    shift[i] = m-mMSbar(m);
    m += 1;
  }
  TGraph* graph = new TGraph(n, mass, shift);
  graph->GetXaxis()->SetTitle("m_{t}^{#bar{MS}} (GeV)");
  graph->GetYaxis()->SetTitle("m_{t}^{pole}-m_{t}^{#bar{MS}} (GeV)");
  return graph;
}

TGraphAsymmErrors* readAhr(const bool pole, const bool useAlphaUnc, const bool heraPDF)
{
  ifstream in;
  if(pole) {
    if(heraPDF)
      in.open("ahrens_mpole_exp_hera.tab");
    else
      in.open("ahrens_all.tab");
  }
  else {
    if(heraPDF)
      in.open("ahrens_ms_hera_exp.dat");
    else
      in.open("mstw_ahrens_msbar_all.tab");
  }

  int n = 51;
  if(!pole)
    n=50;
  double mass [n];
  double sigma[n];
  double dummy_err[n];
  double err_yu[n];
  double err_yd[n];

  int i=0;
  while( 1 ) {
    if( in.eof() ) break;
    double err_u1, err_d1, err_u2, err_d2, err_u3, err_d3;
    if(heraPDF) {
      in >> mass[i] >> sigma[i] >> err_u1 >> err_d1 >> err_u2 >> err_d2;
      if(useAlphaUnc) {
	const double relAlphaUnc = (heraPDF ? 0.04 : 0.05);
	err_yu[i] = TMath::Sqrt(err_u1*err_u1 + err_u2*err_u2 + TMath::Power(sigma[i]*relAlphaUnc,2));
	err_yd[i] = TMath::Sqrt(err_d1*err_d1 + err_d2*err_d2 + TMath::Power(sigma[i]*relAlphaUnc,2));
      }
      else {
	err_yu[i] = TMath::Sqrt(err_u1*err_u1 + err_u2*err_u2);
	err_yd[i] = TMath::Sqrt(err_d1*err_d1 + err_d2*err_d2);
      }
    }
    else {
      in >> mass[i] >> sigma[i] >> err_u1 >> err_d1 >> err_u2 >> err_d2 >> err_u3 >> err_d3;
      if(useAlphaUnc) {
	err_yu[i] = TMath::Sqrt(err_u1*err_u1 + err_u2*err_u2);
	err_yd[i] = TMath::Sqrt(err_d1*err_d1 + err_d2*err_d2);
      }
      else {
	err_yu[i] = TMath::Sqrt(err_u1*err_u1 + err_u3*err_u3);
	err_yd[i] = TMath::Sqrt(err_d1*err_d1 + err_d3*err_d3);
      }
    }

    dummy_err[i] = 0;
    if(sigma[i]>0)
      i++;
  }  
  in.close();

  return new TGraphAsymmErrors(n, mass, sigma, dummy_err, dummy_err, err_yd, err_yu);
}

TGraphAsymmErrors* readKid(const bool useAlphaUnc)
{
  ifstream in;
  in.open("Kidonakis-ttbarLHC7.dat");

  int n = 91;
  double mass [n];
  double sigma[n];
  double dummy_err[n];
  double err_yu[n];
  double err_yd[n];

  int i=0;
  while( 1 ) {
    if( in.eof() ) break;
    in >> mass[i] >> sigma[i];
    dummy_err[i] = 0;
    if(useAlphaUnc) {
      //                                            alpha_s                        scale
      err_yu[i] = TMath::Sqrt(TMath::Power(sigma[i]*0.078,2)+TMath::Power(sigma[i]*0.044,2)+TMath::Power(sigma[i]*0.055,2));
      err_yd[i] = TMath::Sqrt(TMath::Power(sigma[i]*0.070,2)+TMath::Power(sigma[i]*0.031,2)+TMath::Power(sigma[i]*0.055,2));
    }
    else {
      err_yu[i] = TMath::Sqrt(TMath::Power(sigma[i]*0.000,2)+TMath::Power(sigma[i]*0.044,2)+TMath::Power(sigma[i]*0.055,2));
      err_yd[i] = TMath::Sqrt(TMath::Power(sigma[i]*0.000,2)+TMath::Power(sigma[i]*0.031,2)+TMath::Power(sigma[i]*0.055,2));
    }
    i++;
  }  
  in.close();

  return new TGraphAsymmErrors(n, mass, sigma, dummy_err, dummy_err, err_yd, err_yu);
}

TGraphAsymmErrors* readMoc(const bool pole, const bool useAlphaUnc, const bool heraPDF)
{
  ifstream in;
  if(pole) {    
    if(heraPDF)
      in.open("herapdf.tab");
    else
      in.open("Moch_mpole_mstw_cropped.out");
  }
  else {
    if(heraPDF)
      in.open("moch_ms_hera15nnlo_rel.out");
    else
    in.open("top_mstw.tab");
  }

  int n = 51;
  double mass [n];
  double sigma[n];
  double dummy_err[n];
  double err_yu[n];
  double err_yd[n];

  int i=0;
  while( 1 ) {
    if( in.eof() ) break;

    double mt, sig;

    if(heraPDF) {
      if(pole) {
	double err;
	in >> mt >> sig >> err;
	
	err_yu[i] = err;
	err_yd[i] = err;
      }
      else {
	double uScale, dScale, pdf, uAlpha, dAlpha;
	in >> mt >> sig >> uScale >> dScale >> pdf >> uAlpha >> dAlpha;
	
	if(!useAlphaUnc) {
	  uAlpha = 0;
	  dAlpha = 0;
	}
	err_yu[i] = TMath::Sqrt(TMath::Power(uScale/100*sig,2)+TMath::Power(pdf/100*sig,2)+TMath::Power(uAlpha/100*sig,2));
	err_yd[i] = TMath::Sqrt(TMath::Power(dScale/100*sig,2)+TMath::Power(pdf/100*sig,2)+TMath::Power(dAlpha/100*sig,2));
      }
    }
    else{
      double uPdf, dPdf, uRen, dRen, uFac, dFac;
      in >> mt >> sig >> uPdf >> dPdf >> uRen >> dRen >> uFac >> dFac;
      
      const double uScale = TMath::Max(sig, TMath::Max( TMath::Max(uRen,dRen), TMath::Max(uFac,dFac)));
      const double dScale = TMath::Min(sig, TMath::Min( TMath::Min(uRen,dRen), TMath::Min(uFac,dFac)));
      
      if(useAlphaUnc) {
	err_yu[i] = TMath::Sqrt(TMath::Power(uPdf-sig,2) + TMath::Power(uScale-sig,2) + TMath::Power(sig*0.08,2));
	err_yd[i] = TMath::Sqrt(TMath::Power(sig-dPdf,2) + TMath::Power(sig-dScale,2) + TMath::Power(sig*0.08,2));
      }
      else {
	err_yu[i] = TMath::Sqrt(TMath::Power(uPdf-sig,2) + TMath::Power(uScale-sig,2));
	err_yd[i] = TMath::Sqrt(TMath::Power(sig-dPdf,2) + TMath::Power(sig-dScale,2));
      }
    }

    dummy_err[i] = 0;
    mass [i] = mt;
    sigma[i] = sig;
    i++;
  }  
  in.close();

  return new TGraphAsymmErrors(n, mass, sigma, dummy_err, dummy_err, err_yd, err_yu);
}

void drawTheoryGraph(TGraphAsymmErrors* graph, TCanvas* canvas, const bool pole, TString label, TString printNameBase)
{
  if(pole)
    graph->GetXaxis()->SetTitle("m_{t}^{pole} (GeV)");
  else
    graph->GetXaxis()->SetTitle("m_{t}^{#bar{MS}} (GeV)");
  graph->GetYaxis()->SetTitle("#sigma_{t#bar{t}} (pb)");
  graph->GetYaxis()->CenterTitle();

  graph->Draw("AP");
  graph->Draw("2");
  graph->GetFunction("f1")->Draw("same");

  canvas->Print(printNameBase+".ps");
  canvas->Print(label+".eps");
}

void drawRelativeUncertainty(TGraphAsymmErrors* graph, TCanvas* canvas, const bool pole,
			     TString label, TString printNameBase, double& deltaMax)
{
  const int n = graph->GetN();
  double uncUp  [n];
  double uncDown[n];
  double uncMax [n];
  double* y = graph->GetY();
  deltaMax = 0;
  for(int i=0; i<n; i++) {
    uncUp  [i] = graph->GetErrorYhigh(i)/y[i];
    uncDown[i] = graph->GetErrorYlow (i)/y[i];
    uncMax [i] = TMath::Max(uncUp[i], uncDown[i]);
    deltaMax = TMath::Max(deltaMax, TMath::Max(uncUp[i], uncDown[i]));
  }
  TGraph* relUncUp   = new TGraph(n, graph->GetX(), uncUp  );
  TGraph* relUncDown = new TGraph(n, graph->GetX(), uncDown);
  TGraph* maxUnc     = new TGraph(n, graph->GetX(), uncMax );
  char tmpTxt[99];
  sprintf(tmpTxt, "%s (#delta_{max} =  %.4f)", graph->GetTitle(), deltaMax);
  relUncUp->SetTitle(tmpTxt);
  if(pole)
    relUncUp->GetXaxis()->SetTitle("m_{t}^{pole} (GeV)");
  else
    relUncUp->GetXaxis()->SetTitle("m_{t}^{#bar{MS}} (GeV)");
  relUncUp->GetYaxis()->SetTitle("#delta#sigma_{t#bar{t}} / #sigma_{t#bar{t}}");
  relUncUp->GetYaxis()->CenterTitle();
  relUncUp->GetYaxis()->SetRangeUser(.055, .115);
  //  relUncUp->GetYaxis()->SetRangeUser(.0, .115);
  relUncUp  ->SetLineStyle(2);
  relUncDown->SetLineStyle(3);
  relUncUp->Draw("AL");
  relUncDown->Draw("L");
  maxUnc->Fit("pol2");
  maxUnc->GetFunction("pol2")->Draw("same");
  TLegend leg = TLegend(0.8, 0.2, 0.9, 0.35);
  leg.SetFillColor(0);
  leg.SetBorderSize(0);
  leg.AddEntry(relUncUp  , "#delta_{+}", "L");
  leg.AddEntry(relUncDown, "#delta_{-}", "L");
  leg.Draw();
  gStyle->SetOptFit(0000);
  canvas->Print(printNameBase+".ps");
  delete relUncUp;
  delete relUncDown;
  delete maxUnc;
  gStyle->SetOptFit(0011);
}

void getUncertaintiesFromIntegral(TF1* f1, double &lowErr, double& higErr)
{
  std::cout << "============================================================" << std::endl;
  std::cout << "Calculating uncertainties for "
	    << f1->GetName() << " via integration around maximum..." << std::endl;
  const double precision = 1E-08;
  const double max = f1->GetMaximumX();
  double* params = 0;
  //  std::cout << f1->Integral(140, 200, params, precision) << std::endl; // this will give an integral of 1.00
  double sigma = 0;
  double stepSize = 1;
  std::cout << std::left << std::setw(8) << "Delta:" << " " << "Integral:" << std::endl;
  while( 1 ) {
    sigma += stepSize;
    double integral = f1->Integral(max-sigma, max+sigma, params, precision);
    if(integral > 0.6827) {
      sigma -= stepSize;
      std::cout << std::left << std::setw(8) << sigma << " " << integral << std::endl;
      stepSize *= 0.1;
      if(stepSize < 0.01)
	break;
    }
  }
  std::cout << "Symmetric uncertainty (1 sigma): " << sigma << std::endl;
  std::cout << "Function value at left / right edge: " << f1->Eval(max-sigma) << " / " << f1->Eval(max+sigma) << std::endl;
  lowErr = sigma;
  higErr = sigma;
  while( f1->Eval(max-lowErr) < f1->Eval(max+higErr) ) {
    lowErr -= stepSize;
    higErr += stepSize;
  }
  std::cout << "Asymmetric uncertainties: " << "+" << higErr << ", -" << lowErr << std::endl;
  std::cout << "Function value at left / right edge: " << f1->Eval(max-lowErr) << " / " << f1->Eval(max+higErr) << std::endl;
  std::cout << "Integral: " << f1->Integral(max-lowErr, max+higErr, params, precision) << std::endl;
  std::cout << "============================================================" << std::endl;
  return;
}

void plotProjectedPDF(RooAbsPdf* pdf, RooPlot* frame, const int color,
		      const double max, const double errLow, const double errHig)
{
  pdf->plotOn(frame, RooFit::LineColor(color));
  pdf->plotOn(frame, RooFit::Range(max-errLow, max+errHig), RooFit::NormRange("fullRange"),
	      RooFit::FillStyle(1001), RooFit::FillColor(color), RooFit::DrawOption("F"), RooFit::VLines());
  pdf->plotOn(frame, RooFit::Range(max-.01, max+.01), RooFit::NormRange("fullRange"),
	      RooFit::LineColor(kBlack), RooFit::LineWidth(1), RooFit::VLines());
}

void fitSimpleGaussForComparison(TF1* f1, TCanvas* canvas, const bool pole, TString printNameBase)
{
  TH1* hist = f1->GetHistogram();
  if(pole)
    hist->GetXaxis()->SetTitle("m_{t}^{pole} (GeV)");
  else
    hist->GetXaxis()->SetTitle("m_{t}^{#bar{MS}} (GeV)");
  hist->GetYaxis()->SetTitle("a.u.");
  hist->GetYaxis()->CenterTitle();
  hist->SetFillStyle(0);
  hist->Draw("hist");
  hist->Fit("gaus");
  hist->GetFunction("gaus")->SetLineWidth(2);
  char tmpTxt[99];
  sprintf(tmpTxt, "%s: %.1f GeV vs. %.1f GeV",
	  f1->GetTitle(), f1->GetMaximumX(), hist->GetFunction("gaus")->GetParameter(1));
  hist->SetTitle(tmpTxt);
  canvas->Print(printNameBase+".ps");
}

int foldedLikelihoods()
{
  const bool pole    = true;
  const bool useAlphaUnc = true;
  const bool heraPDF = false;

  setTDRStyle();
  gStyle->SetTitleBorderSize(1);
  gStyle->SetOptFit(0011);

  TString printNameBase = "foldedLikelihoods";
  if(!pole)
    printNameBase += "_MSbar";
  if(heraPDF)
    printNameBase += "_hera";

  TCanvas* canvas = new TCanvas("canvas", "canvas", 10, 10, 900, 600);
  canvas->cd()->SetRightMargin(0.04);
  canvas->Print(printNameBase+".ps[");

  TGraph* runningAlpha = 0;
  if(!pole) {
    runningAlpha = getRunningAlphaGraph();
    gStyle->SetOptTitle(1);
    runningAlpha->Draw("AP");
    canvas->Print(printNameBase+".ps");
    canvas->Print("alpha_s.eps");
    gStyle->SetOptTitle(0);
  }

  TGraph* mShift = 0;
  if(!pole) {
    mShift = getMassShiftGraph();
    mShift->Draw("AP");
    mShift->Fit("pol1");
    canvas->Print(printNameBase+".ps");
    canvas->Print("MSbar_vs_pole_mass.eps");
  }

  TGraphAsymmErrors* ahr = readAhr(pole, useAlphaUnc, heraPDF);
  TGraphAsymmErrors* kid = readKid(useAlphaUnc);
  TGraphAsymmErrors* moc = readMoc(pole, useAlphaUnc, heraPDF);

  TF1* f1 = new TF1("f1", "([0]+[1]*x+[2]*TMath::Power(x,2)+[3]*TMath::Power(x,3))/TMath::Power(x,4)", 0, 1000);
//  TF1* f1 = new TF1("f1", "([0]+[1]*(x-172.5)+[2]*TMath::Power(x-172.5,2)+[3]*TMath::Power(x-172.5,3))/TMath::Power(x-172.5,4)", 0, 1000);
//  f1->SetParameter(0, 150.);
//  f1->SetParameter(1, -1.5);
//  f1->SetParameter(2, 0.01);
//  f1->SetParameter(3, 0);
  kid->Fit(f1, "0");
  ahr->Fit(f1, "0");
  moc->Fit(f1, "0");

  kid->SetTitle("Kidonakis");
  moc->SetTitle("Langenfeld et al.");
  ahr->SetTitle("Ahrens et al.");

  gStyle->SetOptTitle(1);

  double deltaMaxKid, deltaMaxMoc, deltaMaxAhr;

  if(pole && !heraPDF) {
    drawTheoryGraph        (kid, canvas, pole, "kidonakis", printNameBase);
    drawRelativeUncertainty(kid, canvas, pole, "kidonakis", printNameBase, deltaMaxKid);
  }
  else
    deltaMaxKid = 999.;
  drawTheoryGraph        (moc, canvas, pole, "moch"     , printNameBase);
  drawRelativeUncertainty(moc, canvas, pole, "moch"     , printNameBase, deltaMaxMoc);
  drawTheoryGraph        (ahr, canvas, pole, "ahrens"   , printNameBase);
  drawRelativeUncertainty(ahr, canvas, pole, "ahrens"   , printNameBase, deltaMaxAhr);

  gStyle->SetOptTitle(0);

  RooRealVar mass("mass", "m_{t}^{pole}", 140., 200., "GeV");
  if(!pole)
    mass.SetTitle("m_{t}^{#bar{MS}}");

  RooRealVar xsec("xsec" , "#sigma_{t #bar{t}}", 50., 500., "pb");

  mass.setRange("fullRange", 140., 200.);

  RooRealVar shift_p0("shift_p0", "shift_p0", 0.);
  RooRealVar shift_p1("shift_p1", "shift_p1", 0.);
  if(!pole) {
    shift_p0.setVal(mShift->GetFunction("pol1")->GetParameter(0));
    shift_p1.setVal(mShift->GetFunction("pol1")->GetParameter(1));
  }
  RooPolyVar shift("shift", "shift", mass, RooArgSet(shift_p0, shift_p1));

  RooFormulaVar deltaM("deltaM", "deltaM", "@0-172.5+@1", RooArgSet(mass, shift));
  // e-mu
  //  RooRealVar p0("p0", "p0",  1.01    ); // e-mu
  //  RooRealVar p1("p1", "p1", -0.93E-02); // e-mu
  //  RooRealVar p2("p2", "p2",  1.2E-04 ); // e-mu
  // mu-mu
  //  RooRealVar p0("p0", "p0",  1.00    ); // mu-mu
  //  RooRealVar p1("p1", "p1", -1.01E-02); // mu-mu
  //  RooRealVar p2("p2", "p2",  1.1E-04 ); // mu-mu
  // e-e
  //  RooRealVar p0("p0", "p0",  1.02    ); // e-e
  //  RooRealVar p1("p1", "p1", -1.02E-02); // e-e
  //  RooRealVar p2("p2", "p2",  1.0E-04 ); // e-e
  // weighted average
  RooRealVar p0("p0", "p0",  1.01    ); // e-mu
  RooRealVar p1("p1", "p1", -0.97E-02); // e-mu
  RooRealVar p2("p2", "p2",  1.125E-04 ); // e-mu

  RooPolyVar measXSecMassDepRel("measXSecMassDepRel", "measXSecMassDepRel", deltaM, RooArgSet(p0, p1, p2));
  RooRealVar measXSec("measXSec", "measXSec", 169.9, "pb");
  // total exp uncert of 18.3 from adding quadr. 3.9 (stat), 16.3 (syst) and 7.6 (lumi)
  // and subtracting 1.5 % = 2.5485 pb for the top mass (in e-mu, it is 2.6 % for ee and mumu)
  // FIXME: This should rather be 18.23 pb!? Resulting m_t from Moch changes from 170.3 to 170.4 GeV, no other effects
  // Kept at 18.3 pb for the time being, in order to have stable numbers for the PAS
  RooRealVar measXSecErr("measXSecErr", "measXSecErr", 18.3, "pb");
  RooFormulaVar measXSecMassDep("measXSecMassDep", "measXSecMassDep", "@0*@1", RooArgSet(measXSecMassDepRel,measXSec));
  RooGaussian measXSecPDF("measXSecPDF", "measXSecPDF", xsec, measXSecMassDep, measXSecErr);

  RooRealVar kid_p0("kid_p0", "kid_p0", kid->GetFunction("f1")->GetParameter(0));
  RooRealVar kid_p1("kid_p1", "kid_p1", kid->GetFunction("f1")->GetParameter(1));
  RooRealVar kid_p2("kid_p2", "kid_p2", kid->GetFunction("f1")->GetParameter(2));  
  RooRealVar kid_p3("kid_p3", "kid_p3", kid->GetFunction("f1")->GetParameter(3));  
  RooFormulaVar kidXSec("kidXSec", "kidXSec", "(@1+@2*@0+@3*@0*@0+@4*@0*@0*@0)/(@0*@0*@0*@0)",
			RooArgSet(mass, kid_p0, kid_p1, kid_p2, kid_p3));
  RooRealVar kidXSecRelErr("kidXSecRelErr", "kidXSecRelErr", deltaMaxKid);
  RooFormulaVar kidXSecErr("kidXSecErr", "kidXSecErr", "@0*@1", RooArgSet(kidXSec, kidXSecRelErr));
  RooGaussian kidXSecPDF("kidXSecPDF", "kidXSecPDF", xsec, kidXSec, kidXSecErr);

  RooRealVar moc_p0("moc_p0", "moc_p0", moc->GetFunction("f1")->GetParameter(0));
  RooRealVar moc_p1("moc_p1", "moc_p1", moc->GetFunction("f1")->GetParameter(1));
  RooRealVar moc_p2("moc_p2", "moc_p2", moc->GetFunction("f1")->GetParameter(2));  
  RooRealVar moc_p3("moc_p3", "moc_p3", moc->GetFunction("f1")->GetParameter(3));  
  RooFormulaVar mocXSec("mocXSec", "mocXSec", "(@1+@2*@0+@3*@0*@0+@4*@0*@0*@0)/(@0*@0*@0*@0)",
			RooArgSet(mass, moc_p0, moc_p1, moc_p2, moc_p3));
  RooRealVar mocXSecRelErr("mocXSecRelErr", "mocXSecRelErr", deltaMaxMoc);
  RooFormulaVar mocXSecErr("mocXSecErr", "mocXSecErr", "@0*@1", RooArgSet(mocXSec, mocXSecRelErr));
  RooGaussian mocXSecPDF("mocXSecPDF", "mocXSecPDF", xsec, mocXSec, mocXSecErr);

  RooRealVar ahr_p0("ahr_p0", "ahr_p0", ahr->GetFunction("f1")->GetParameter(0));
  RooRealVar ahr_p1("ahr_p1", "ahr_p1", ahr->GetFunction("f1")->GetParameter(1));
  RooRealVar ahr_p2("ahr_p2", "ahr_p2", ahr->GetFunction("f1")->GetParameter(2));  
  RooRealVar ahr_p3("ahr_p3", "ahr_p3", ahr->GetFunction("f1")->GetParameter(3));  
  RooFormulaVar ahrXSec("ahrXSec", "ahrXSec", "(@1+@2*@0+@3*@0*@0+@4*@0*@0*@0)/(@0*@0*@0*@0)",
			RooArgSet(mass, ahr_p0, ahr_p1, ahr_p2, ahr_p3));
  RooRealVar ahrXSecRelErr("ahrXSecRelErr", "ahrXSecRelErr", deltaMaxAhr);
  RooFormulaVar ahrXSecErr("ahrXSecErr", "ahrXSecErr", "@0*@1", RooArgSet(ahrXSec, ahrXSecRelErr));
  RooGaussian ahrXSecPDF("ahrXSecPDF", "ahrXSecPDF", xsec, ahrXSec, ahrXSecErr);

  const int colorKid = kRed+1;
  const int colorAhr = kMagenta;
  const int colorMoc = kGreen-3;
  const int colorDil = kBlue;

  RooPlot* frame = mass.frame();
  if(pole && !heraPDF)
    kidXSec.plotOn(frame, RooFit::LineColor(colorKid));
  ahrXSec.plotOn(frame, RooFit::LineColor(colorAhr));
  mocXSec.plotOn(frame, RooFit::LineColor(colorMoc));
  measXSecMassDep.plotOn(frame, RooFit::LineColor(colorDil));
  frame->GetYaxis()->SetTitle("#sigma_{t#bar{t}} (pb)");
  frame->Draw();
  canvas->Print(printNameBase+".ps");
  
  RooProdPdf kidProdPDF("kidProdPDF", "kidProdPDF", RooArgList(measXSecPDF, kidXSecPDF));
  RooProdPdf mocProdPDF("mocProdPDF", "mocProdPDF", RooArgList(measXSecPDF, mocXSecPDF));
  RooProdPdf ahrProdPDF("ahrProdPDF", "ahrProdPDF", RooArgList(measXSecPDF, ahrXSecPDF));

  frame = mass.frame(RooFit::Range(150., 190.));

  RooAbsPdf* kidProjectedPDF = kidProdPDF.createProjection(xsec);
  RooAbsPdf* mocProjectedPDF = mocProdPDF.createProjection(xsec);
  RooAbsPdf* ahrProjectedPDF = ahrProdPDF.createProjection(xsec);

  TF1* kidTF = kidProjectedPDF->asTF(mass, RooArgSet(), RooArgSet(mass));
  TF1* mocTF = mocProjectedPDF->asTF(mass, RooArgSet(), RooArgSet(mass));
  TF1* ahrTF = ahrProjectedPDF->asTF(mass, RooArgSet(), RooArgSet(mass));

  const double kidMax = kidTF->GetMaximumX();
  const double mocMax = mocTF->GetMaximumX();
  const double ahrMax = ahrTF->GetMaximumX();

  double kidLowErr, kidHigErr;
  double mocLowErr, mocHigErr;
  double ahrLowErr, ahrHigErr;

  getUncertaintiesFromIntegral(kidTF, kidLowErr, kidHigErr);
  getUncertaintiesFromIntegral(mocTF, mocLowErr, mocHigErr);
  getUncertaintiesFromIntegral(ahrTF, ahrLowErr, ahrHigErr);

  plotProjectedPDF(mocProjectedPDF, frame, colorMoc, mocMax, mocLowErr, mocHigErr);
  if(pole && !heraPDF)
    plotProjectedPDF(kidProjectedPDF, frame, colorKid, kidMax, kidLowErr, kidHigErr);
  plotProjectedPDF(ahrProjectedPDF, frame, colorAhr, ahrMax, ahrLowErr, ahrHigErr);

  frame->GetYaxis()->SetTitle("Probability density");
  frame->GetYaxis()->SetRangeUser(0., 0.034);
  frame->Draw();

  kidTF->SetLineColor(kBlack);
  kidTF->SetFillColor(colorKid);
  kidTF->SetFillStyle(1001);

  mocTF->SetLineColor(kBlack);
  mocTF->SetFillColor(colorMoc);
  mocTF->SetFillStyle(1001);

  ahrTF->SetLineColor(kBlack);
  ahrTF->SetFillColor(colorAhr);
  ahrTF->SetFillStyle(1001);

  double yMin = 0.70;
  if(!pole || heraPDF)
    yMin = 0.77;
  TLegend leg = TLegend(0.2, yMin, 0.9, 0.9);
  leg.SetFillStyle(0);
  leg.SetBorderSize(0);

  char legTmpTxt[99];
  sprintf(legTmpTxt, "Langenfeld et al. (%.1f +%.1f -%.1f GeV)", mocMax, mocHigErr, mocLowErr);
  leg.AddEntry(mocTF, legTmpTxt, "F");
  if(pole && !heraPDF) {
    sprintf(legTmpTxt, "Kidonakis (%.1f +%.1f -%.1f GeV)", kidMax, kidHigErr, kidLowErr);
    leg.AddEntry(kidTF, legTmpTxt, "F");
  }
  sprintf(legTmpTxt, "Ahrens et al. (%.1f +%.1f -%.1f GeV)", ahrMax, ahrHigErr, ahrLowErr);
  leg.AddEntry(ahrTF, legTmpTxt, "F");
  leg.Draw();

  canvas->Print(printNameBase+".ps");
  TString epsName = "densities";
  if(!pole)
    epsName += "_MSbar";
  if(heraPDF)
    epsName += "_hera";
  canvas->Print(epsName+".eps");

  gStyle->SetOptTitle(1);

  kidTF->SetTitle("Kidonakis");
  mocTF->SetTitle("Langenfeld et al.");
  ahrTF->SetTitle("Ahrens et al.");

  if(pole && !heraPDF)
    fitSimpleGaussForComparison(kidTF, canvas, pole, printNameBase);
  fitSimpleGaussForComparison(ahrTF, canvas, pole, printNameBase);
  fitSimpleGaussForComparison(mocTF, canvas, pole, printNameBase);

  canvas->Print(printNameBase+".ps]");

  if(!pole) {
    delete runningAlpha;
    delete mShift;
  }
  delete ahr;
  delete kid;
  delete moc;
  delete canvas;
  delete f1;

  return 0;
}

int main() {
  return foldedLikelihoods();
}
