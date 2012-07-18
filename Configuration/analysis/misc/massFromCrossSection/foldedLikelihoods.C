#include "Riostream.h"

#include "TAxis.h"
#include "TBox.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TF2.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TMath.h"
#include "TROOT.h"
#include "TSystem.h"

#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooGenericPdf.h"
#include "RooPlot.h"
#include "RooPolyVar.h"
#include "RooProdPdf.h"
#include "RooRealVar.h"

#include <iostream>

#include "tdrstyle.C"
#include "foldedLikelihoods_helpers.h"
#include "foldedLikelihoods_classes.h"

enum PdfType { kMSTW, kHERA, kABM, kNNPDF };

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
  graph->SetTitle("At three-loop level and with N(flavors)=5, using 2009 world average for #alpha_{S}(M_{Z})");
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

std::vector<TGraphAsymmErrors*> readTheory(const TString name, const bool pole, const bool useAlphaUnc,
					   const PdfType pdfType)
{
  const unsigned nPoints = (name=="ahrens" ? 51 : 91);

  TString fileName = "theories_7TeV/" + name;
  fileName += (pole ? "_pole" : "_msbar");
  switch (pdfType) {
  case kMSTW: fileName += "_mstw.tab"; break;
  case kHERA: fileName += "_hera.tab"; break;
  case kABM : fileName += "_abm.tab" ; break;
  default   : std::cout << "PdfType (" << pdfType << ") not supported!" << std::endl; abort();
  }
  
  ifstream in;
  in.open(fileName);

  double mass     [nPoints];
  double sigma    [nPoints];
  double dummy_err[nPoints];
  double err_yu[4][nPoints];
  double err_yd[4][nPoints];

  unsigned i=0;
  while( !in.eof() ) {
    double mt, xsec, err_u[3], err_d[3];
    in >> mt >> xsec >> err_u[0] >> err_d[0] >> err_u[1] >> err_d[1] >> err_u[2] >> err_d[2];
    if( in.eof() ) break;
    mass [i] = mt;
    sigma[i] = xsec;
    for(unsigned j=0; j<3; j++) {
      err_yu[j][i] = err_u[j];
      err_yd[j][i] = err_d[j];
    }
    if(useAlphaUnc) {
      err_yu[3][i] = TMath::Sqrt(err_u[0]*err_u[0] + err_u[1]*err_u[1] + err_u[2]*err_u[2]);
      err_yd[3][i] = TMath::Sqrt(err_d[0]*err_d[0] + err_d[1]*err_d[1] + err_d[2]*err_d[2]);
    }
    else {
      err_yu[3][i] = TMath::Sqrt(err_u[0]*err_u[0] + err_u[1]*err_u[1]);
      err_yd[3][i] = TMath::Sqrt(err_d[0]*err_d[0] + err_d[1]*err_d[1]);
    }
    dummy_err[i] = 0;
    if(sigma[i]<1) {
      std::cout << "Spurious cross section of " << sigma[i] << " in line " << i+1 << " of " << fileName << std::endl;
      abort();
    }
    i++;      
  }

  in.close();
  if(i!=nPoints){
    std::cout << "Spurious number of lines in " << fileName << std::endl;
    std::cout << "Found / expected: " << i << " / " << nPoints << std::endl;
    abort();
  }

  std::vector<TGraphAsymmErrors*> vec;
  for(unsigned j=0; j<4; j++)
    vec.push_back(new TGraphAsymmErrors(nPoints, mass, sigma, dummy_err, dummy_err, err_yd[j], err_yu[j]));
  return vec;
}

TString epsString(const TString& label, const bool pole, const PdfType pdfType)
{
  TString name = "figs/"+label;
  name += (pole ? "_pole" : "_MSbar");
  switch (pdfType) {
  case kMSTW: name += "_mstw"; break;
  case kHERA: name += "_hera"; break;
  case kABM : name += "_abm" ; break;
  default   : std::cout << "PdfType (" << pdfType << ") not supported!" << std::endl; abort();
  }
  return (name + ".eps");
}

void drawTheoryGraph(TGraphAsymmErrors* graph, TCanvas* canvas, const bool pole,
		     const TString label, const TString printNameBase)
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
  canvas->Print("figs/"+label+".eps");
}

void removeEmptyPoints(TGraph* graph)
{
  unsigned n = graph->GetN();
  for(unsigned i=0; i<n; i++) {
    if((graph->GetY())[i]<0.0001) {
      graph->RemovePoint(i);
      i--;
      n--;
    }
  }
}

std::vector<TF1*> getAndDrawRelativeUncertainty(const TGraphAsymmErrors* graph, TCanvas* canvas, const bool pole,
						const TString title, const TString epsName, const TString printNameBase,
						const bool symmetrize)
{
  const int n = graph->GetN();
  double uncUp  [n];
  double uncDown[n];
  double uncMean[n];
  double* y = graph->GetY();
  for(int i=0; i<n; i++) {
    uncUp  [i] = graph->GetErrorYhigh(i)/y[i];
    uncDown[i] = graph->GetErrorYlow (i)/y[i];
    uncMean[i] = (uncUp[i] + uncDown[i])/2;
  }
  TGraph* relUncUp   = new TGraph(n, graph->GetX(), uncUp  );
  TGraph* relUncDown = new TGraph(n, graph->GetX(), uncDown);
  TGraph* relUncMean = new TGraph(n, graph->GetX(), uncMean);
  removeEmptyPoints(relUncUp  );
  removeEmptyPoints(relUncDown);
  removeEmptyPoints(relUncMean);
  TString titleApp = ": " + title + " uncertainty";
  relUncUp->SetTitle(graph->GetTitle() + titleApp);
  if(pole)
    relUncUp->GetXaxis()->SetTitle("m_{t}^{pole} (GeV)");
  else
    relUncUp->GetXaxis()->SetTitle("m_{t}^{#bar{MS}} (GeV)");
  relUncUp->GetYaxis()->SetTitle("#delta#sigma_{t#bar{t}} / #sigma_{t#bar{t}}");
  relUncUp->GetYaxis()->CenterTitle();
  relUncUp->GetYaxis()->SetRangeUser(.0, .115);
  relUncUp  ->SetMarkerStyle(26);
  relUncDown->SetMarkerStyle(32);
  relUncUp->Draw("AP");
  relUncDown->Draw("P");
  std::vector<TF1*> vec;
  if(symmetrize) {
    relUncMean->Fit("pol1", "Q");
    relUncMean->GetFunction("pol1")->Draw("same");
    vec.push_back((TF1*) relUncMean->GetFunction("pol1")->Clone());
  }
  else {
    relUncUp->Fit("pol1", "Q");
    relUncUp->GetFunction("pol1")->Draw("same");
    relUncDown->Fit("pol1", "Q");
    relUncDown->GetFunction("pol1")->Draw("same");
    vec.push_back((TF1*) relUncUp  ->GetFunction("pol1")->Clone());
    vec.push_back((TF1*) relUncDown->GetFunction("pol1")->Clone());
  }
  TLegend leg = TLegend(0.8, 0.2, 0.9, 0.35);
  leg.SetFillColor(0);
  leg.SetBorderSize(0);
  leg.AddEntry(relUncUp  , "#delta_{+}", "P");
  leg.AddEntry(relUncDown, "#delta_{-}", "P");
  leg.Draw();
  gStyle->SetOptFit(0000);
  canvas->Print(printNameBase+".ps");
  canvas->Print(epsName);
  delete relUncUp;
  delete relUncDown;
  delete relUncMean;
  gStyle->SetOptFit(0011);
  return vec;
}

void drawConvolution(const PredXSec* predXSec, RooRealVar& xsec, RooRealVar& mass, RooRealVar& alpha,
		     const TString title, TCanvas* canvas, const TString printNameBase, const TString epsName)
{
  if(mass.getTitle().Contains("pole"))
    mass.setVal(172.5);
  else
    mass.setVal(165.);
  RooPlot* convFrame = xsec.frame(0.85*predXSec->xsec.getVal(), 1.15*predXSec->xsec.getVal());
  predXSec->gaussianProb.plotOn(convFrame, RooFit::LineColor(kGreen),
				RooFit::NormRange("xsec_fullRange"),
				RooFit::FillStyle(1001), RooFit::FillColor(kGreen), RooFit::DrawOption("F"));
  predXSec->gaussianProb.plotOn(convFrame, RooFit::Range(predXSec->xsec.getVal()-0.01,
							 predXSec->xsec.getVal()+0.01),
				RooFit::NormRange("xsec_fullRange"),
				RooFit::LineColor(kBlack), RooFit::LineWidth(1), RooFit::VLines());
  predXSec->rectangularProb.plotOn(convFrame, RooFit::Normalization(1.), RooFit::LineStyle(2), RooFit::FillColor(0));
  predXSec->prob.plotOn(convFrame, RooFit::LineColor(kRed), RooFit::FillColor(0));
  convFrame->GetYaxis()->SetTitle("Probability density");
  convFrame->Draw();
  gPad->RedrawAxis();
  TLegend convLeg = TLegend(0.66, 0.6, 0.92, 0.9);
  convLeg.SetFillStyle(0);
  convLeg.SetBorderSize(0);
  convLeg.AddEntry(convFrame->findObject(predXSec->name+"_gaussianProb_Norm[xsec]"   ), "Gauss(PDF)"      , "F");
  convLeg.AddEntry(convFrame->findObject(predXSec->name+"_rectangularProb_Norm[xsec]"), "Rect(#mu_{r/f})" , "F");
  convLeg.AddEntry(convFrame->findObject(predXSec->name+"_prob_Norm[xsec]"           ), "Gauss#otimesRect", "F");
  convLeg.Draw();
  char tmpTxt[99];
  sprintf(tmpTxt, "%s, %s = %.1f GeV, %s = %.4f",
	  title.Data(), mass.getTitle().Data(), mass.getVal(), alpha.getTitle().Data(), alpha.getVal());
  TLatex text(0.,0.,tmpTxt);
  text.SetNDC();
  text.SetTextAlign(13);
  text.SetX(0.16);
  text.SetY(0.99);
  text.SetTextFont(43);
  text.SetTextSizePixels(16);
  text.Draw();
  canvas->Print(printNameBase+".ps");
  canvas->Print(epsName);
  delete convFrame;
}

void plot2DimProb(const PredXSec* predXSec, TCanvas* canvas, const TString title,
		  const TString printNameBase, const TString epsName)
{
  TH1* h2 = predXSec->prob.createHistogram("mass,alpha,xsec",50,30,90);
  h2->Draw("box");
  TLatex text(0.,0.,title);
  text.SetNDC();
  text.SetTextAlign(13);
  text.SetX(0.16);
  text.SetY(0.99);
  text.SetTextFont(43);
  text.SetTextSizePixels(16);
  text.Draw();
  canvas->Print(printNameBase+".ps");
  canvas->Print(epsName);
  delete h2;
}

void plotProjectedPDF(RooAbsPdf* pdf, RooPlot* frame, const int color, const int fillStyle,
		      const double max, const double errLow, const double errHig)
{
  pdf->plotOn(frame, RooFit::LineColor(color), RooFit::NormRange("mass_fullRange"));
  pdf->plotOn(frame, RooFit::Range(max-errLow, max+errHig), RooFit::NormRange("mass_fullRange"),
	      //	      RooFit::LineColor(color), RooFit::LineWidth(1),
	      RooFit::FillStyle(fillStyle), RooFit::FillColor(color), RooFit::DrawOption("F"), RooFit::VLines());
  pdf->plotOn(frame, RooFit::Range(max-.01, max+.01), RooFit::NormRange("mass_fullRange"),
	      RooFit::LineColor(color), RooFit::LineWidth(3), RooFit::VLines());
}

TLatex* cmsTxt(const bool full2011dilep)
{
  const TString txt = (full2011dilep ?
		       //		       "CMS, 2.3 fb^{-1} at  #sqrt{s} = 7 TeV" :
		       "CMS 2011 t#bar{t} Data #times Approx. NNLO by Langenfeld et al." :
		       "CMS Preliminary, 1.14 fb^{-1} at  #sqrt{s} = 7 TeV");
  TLatex* text = new TLatex(3.570061,23.08044,txt);
  text->SetNDC();
  text->SetTextAlign(13);
  text->SetX(0.16);
  text->SetY(1.003);
  text->SetTextFont(42);
  text->SetTextSizePixels(24);
  return text;
}

int foldedLikelihoods(const bool pole)
{
  const bool useAlphaUnc = false;
  const bool full2011dilep = true;

  setTDRStyle();
  gStyle->SetTitleBorderSize(1);
  gStyle->SetOptFit(0011);

  RooAbsReal::defaultIntegratorConfig()->method2D().setLabel("RooSegmentedIntegrator2D");
  RooAbsReal::defaultIntegratorConfig()->getConfigSection("RooIntegrator1D").setCatLabel("sumRule", "Midpoint");
  RooAbsReal::defaultIntegratorConfig()->methodND().setLabel("RooMCIntegrator");

  gSystem->mkdir("figs");

  TString printNameBase = "figs/foldedLikelihoods";
  printNameBase += (pole ? "_pole" : "_MSbar");

  TCanvas* canvas = new TCanvas("canvas", "canvas", 10, 10, 900, 600);
  canvas->cd()->SetRightMargin(0.04);
  canvas->Print(printNameBase+".ps[");

  TGraph* runningAlpha = 0;
  if(!pole) {
    runningAlpha = getRunningAlphaGraph();
    gStyle->SetOptTitle(1);
    runningAlpha->Draw("AP");
    canvas->Print(printNameBase+".ps");
    canvas->Print("figs/alpha_s.eps");
    gStyle->SetOptTitle(0);
  }

  TGraph* mShift = 0;
  if(!pole) {
    mShift = getMassShiftGraph();
    mShift->Draw("AP");
    mShift->Fit("pol1", "Q");
    canvas->Print(printNameBase+".ps");
    canvas->Print("figs/MSbar_vs_pole_mass.eps");
  }

  const unsigned nPdfSets=3;
  const unsigned nTheories=2;

  //  std::vector<TGraphAsymmErrors*> ahr_vec[nPdfSets];
  std::vector<TGraphAsymmErrors*> moc_vec[nPdfSets];
  std::vector<TGraphAsymmErrors*> mit_vec[nPdfSets];
  
  //  TGraphAsymmErrors* ahr[nPdfSets];
  TGraphAsymmErrors* moc[nPdfSets];
  TGraphAsymmErrors* mit[nPdfSets];
  
  std::vector<TF1*> moc_funcs[nPdfSets][4];
  //  std::vector<TF1*> ahr_funcs[nPdfSets][4];
  std::vector<TF1*> mit_funcs[nPdfSets][4];

  const TString pdfName[nPdfSets] = {"MSTW2008", "HERAPDF1.5", "ABM11"};
  const TString theoName[nTheories] = {"Langenfeld", "Cacciari"};

  TString theoTitle[nPdfSets][nTheories];
  for(unsigned h=0; h<nPdfSets; h++)
    for(unsigned i=0; i<nTheories; i++)
      theoTitle[h][i] = theoName[i] + " et al. with " + pdfName[h];

  const TString errName [4] = {"Scale", "Experimental PDF", "#alpha_{S}", "Total"};
  const TString errLabel[4] = {"scale", "expPDF", "alphaS", "total"};

  TF1* f1 = new TF1("f1", "([0]+[1]*x+[2]*TMath::Power(x,2)+[3]*TMath::Power(x,3))/TMath::Power(x,4)", 0, 1000);

  for(unsigned h=0; h<nPdfSets; h++) {
    //    ahr_vec[h] = readTheory("ahrens", pole, useAlphaUnc, (PdfType)h);
    moc_vec[h] = readTheory("moch"  , pole, useAlphaUnc, (PdfType)h);
    mit_vec[h] = readTheory("mitov" , pole, useAlphaUnc, (PdfType)h);

    //    ahr[h] = ahr_vec[h].at(3);
    moc[h] = moc_vec[h].at(3);
    mit[h] = mit_vec[h].at(3);

    //    ahr[h]->Fit(f1, "Q0");
    moc[h]->Fit(f1, "Q0");
    mit[h]->Fit(f1, "Q0");

    for(unsigned j=0; j<4; j++) {
      //      ahr_vec[h].at(j)->SetTitle(theoTitle[h][0]);
      moc_vec[h].at(j)->SetTitle(theoTitle[h][0]);
      mit_vec[h].at(j)->SetTitle(theoTitle[h][1]);
    }

    gStyle->SetOptTitle(1);
    
    for(unsigned j=0; j<2; j++)
      mit_funcs[h][j] = getAndDrawRelativeUncertainty(mit_vec[h].at(j), canvas, pole, errName[j],
						      epsString("relUnc_mitov_"+errLabel[j], pole, (PdfType)h),
						      printNameBase, (j==1 || j==2));
    drawTheoryGraph(mit[h], canvas, pole, "mitov", printNameBase);
    for(unsigned j=0; j<2; j++)
      moc_funcs[h][j] = getAndDrawRelativeUncertainty(moc_vec[h].at(j), canvas, pole, errName[j],
						      epsString("relUnc_moch_"+errLabel[j], pole, (PdfType)h),
						      printNameBase, (j==1 || j==2));
    drawTheoryGraph(moc[h], canvas, pole, "moch", printNameBase);
//    for(unsigned j=0; j<4; j++)
//      ahr_funcs[h][j] = getAndDrawRelativeUncertainty(ahr_vec[h].at(j), canvas, pole, errName[j],
//						      epsString("relUnc_ahrens_"+errLabel[j], pole, (PdfType)h),
//						      printNameBase, (j==1 || j==2));
//    drawTheoryGraph(ahr[h], canvas, pole, "ahrens", printNameBase);
    
    gStyle->SetOptTitle(0);
  }

  RooRealVar mass("mass", "m_{t}^{pole}", 140., 190., "GeV");
  if(!pole)
    mass.SetTitle("m_{t}^{#bar{MS}}");

  RooRealVar alpha("alpha", "#alpha_{S}(M_{Z})", 0.10, 0.13);

  RooRealVar xsec("xsec" , "#sigma_{t #bar{t}}", 0., 900., "pb");

  RooRealVar alpha2012_mean("alpha2012_mean", "alpha2012_mean", 0.1184);
  RooRealVar alpha2012_unc ("alpha2012_unc" , "alpha2012_unc" , 0.0007);

  RooRealVar alphaMSTW_mean("alphaMSTW_mean", "alphaMSTW_mean", 0.1171); //Eur.Phys.J.C64:653-680,2009
  RooRealVar alphaMSTW_unc ("alphaMSTW_unc" , "alphaMSTW_unc" , 0.0014); //Eur.Phys.J.C64:653-680,2009

  RooRealVar alphaHERA_mean("alphaHERA_mean", "alphaHERA_mean", 0.1176);
  RooRealVar alphaHERA_unc ("alphaHERA_unc" , "alphaHERA_unc" , 0.0020);

  RooRealVar alphaABM_mean("alphaABM_mean", "alphaABM_mean", 0.1134);
  RooRealVar alphaABM_unc ("alphaABM_unc" , "alphaABM_unc" , 0.0011);

  std::vector<RooRealVar> defaultAlphas;
  defaultAlphas.push_back(alphaMSTW_mean);
  defaultAlphas.push_back(alphaHERA_mean);
  defaultAlphas.push_back(alphaABM_mean );

  RooRealVar mass_mean("mass_mean", "mass_mean", 173.2); // Tevatron July 2012
  RooRealVar mass_unc ("mass_unc" , "mass_unc" , 1.4); // Tevatron July 2012 plus 1 GeV for m(pole)/m(MC)?
  RooGaussian massProb("massProb", "massProb", mass, mass_mean, mass_unc);

  mass.setRange("mass_fullRange", 140., 190.);
  xsec.setRange("xsec_fullRange", 10., 900.);

  RooRealVar shift_p0("shift_p0", "shift_p0", 0.);
  RooRealVar shift_p1("shift_p1", "shift_p1", 0.);
  if(!pole) {
    shift_p0.setVal(mShift->GetFunction("pol1")->GetParameter(0));
    shift_p1.setVal(mShift->GetFunction("pol1")->GetParameter(1));
  }
  RooPolyVar shift("shift", "shift", mass, RooArgSet(shift_p0, shift_p1));

  TString deltaM_formula = "@0-172.5+@1";
  if(full2011dilep)
    deltaM_formula = "@0+@1";
  RooFormulaVar deltaM("deltaM", "deltaM", deltaM_formula, RooArgSet(mass, shift));
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

  if(full2011dilep) {
    p0.setVal(-1.467);
    p1.setVal(0.03715);
    p2.setVal(-0.0001324);
//    p0.setVal(1.0);
//    p1.setVal(0.0);
//    p2.setVal(0.0);
  }

  RooPolyVar measXSecMassDepRel("measXSecMassDepRel", "measXSecMassDepRel", deltaM, RooArgSet(p0, p1, p2));
  RooRealVar measXSec("measXSec", "measXSec", 169.9, "pb");
  // total exp uncert of 18.23 from adding quadr. 3.9 (stat), 16.3 (syst) and 7.6 (lumi)
  // and subtracting 1.5 % = 2.5485 pb for the top mass (in e-mu, it is 2.6 % for ee and mumu)
  RooRealVar measXSecErr("measXSecErr", "measXSecErr", 18.23, "pb");

  if(full2011dilep) {
    measXSec.setVal(161.9);
    measXSecErr.setVal(6.725);
  }

  RooFormulaVar measXSecMassDep("measXSecMassDep", "measXSecMassDep", "@0*@1", RooArgSet(measXSecMassDepRel,measXSec));
  RooGaussian measXSecPDF("measXSecPDF", "measXSecPDF", xsec, measXSecMassDep, measXSecErr);

  PredXSec* mitPredXSec[nPdfSets];
  PredXSec* mocPredXSec[nPdfSets];
  //  PredXSec* ahrPredXSec[nPdfSets];

  for(unsigned h=0; h<nPdfSets; h++) {
    TString alphaFileName = (pole ? "pole_" : "msbar_");
    TString suf = "PredXSec";

    switch(h) {
    case kMSTW: alphaFileName += "mstw"; suf += "MSTW"; break;
    case kHERA: alphaFileName += "hera"; suf += "HERA"; break;
    case kABM : alphaFileName += "abm" ; suf += "ABM" ; break;
    }

    TFile mitAlphaFile("theories_7TeV/mitov_"+alphaFileName+"_alphaDep.root", "READ");
    TFile mocAlphaFile("theories_7TeV/moch_" +alphaFileName+"_alphaDep.root", "READ");
    
    mitPredXSec[h] = new PredXSec("mit"+suf, xsec, mass, alpha, mit[h]->GetFunction("f1"), mit_funcs[h],
				  mitAlphaFile, defaultAlphas.at(h));
    mocPredXSec[h] = new PredXSec("moc"+suf, xsec, mass, alpha, moc[h]->GetFunction("f1"), moc_funcs[h],
				  mocAlphaFile, defaultAlphas.at(h));
    //    ahrPredXSec[h] = new PredXSec("ahrPredXSec"+suf, xsec, mass, alpha, ahr[h]->GetFunction("f1"), ahr_funcs[h], alphaFile);

    mitAlphaFile.Close();
    mocAlphaFile.Close();

    alpha.setVal(defaultAlphas.at(h).getVal());

    drawConvolution(mitPredXSec[h], xsec, mass, alpha, theoTitle[h][1], canvas, printNameBase,
		    epsString("convolution_mitov", pole, (PdfType)h));
    drawConvolution(mocPredXSec[h], xsec, mass, alpha, theoTitle[h][0], canvas, printNameBase,
		    epsString("convolution_moch", pole, (PdfType)h));
//    drawConvolution(ahrPredXSec[h], xsec, mass, alpha, theoTitle[h][0], canvas, printNameBase,
//		    epsString("convolution_ahrens", pole, (PdfType)h));
  }

  //  const int colorAhr = kMagenta;
  const int colorMoc = kGreen-3;
  const int colorMit = kCyan;
  const int colorDil = kBlue;

  RooPlot* frame = mass.frame();
  //  ahrPredXSec[0]->xsec.plotOn(frame, RooFit::LineColor(colorAhr));
  mocPredXSec[0]->xsec.plotOn(frame, RooFit::LineColor(colorMoc));
  mitPredXSec[0]->xsec.plotOn(frame, RooFit::LineColor(colorMit));
  measXSecMassDep.plotOn(frame, RooFit::LineColor(colorDil));
  frame->GetYaxis()->SetTitle("#sigma_{t#bar{t}} (pb)");
  frame->Draw();
  canvas->Print(printNameBase+".ps");
  canvas->Print(epsString("xsec_vs_mass", pole, (PdfType)0));

  RooPlot* frame_alpha = alpha.frame(RooFit::Range(0.110, 0.125));
  mass.setVal(mass_mean.getVal());
  mocPredXSec[0]->xsec.plotOn(frame_alpha, RooFit::LineColor(kRed)  , RooFit::LineStyle(2));
  mocPredXSec[1]->xsec.plotOn(frame_alpha, RooFit::LineColor(kGreen), RooFit::LineStyle(2));
  mocPredXSec[2]->xsec.plotOn(frame_alpha, RooFit::LineColor(kCyan ), RooFit::LineStyle(2));
  mitPredXSec[0]->xsec.plotOn(frame_alpha, RooFit::LineColor(kRed));
  mitPredXSec[1]->xsec.plotOn(frame_alpha, RooFit::LineColor(kGreen));
  mitPredXSec[2]->xsec.plotOn(frame_alpha, RooFit::LineColor(kCyan));
  measXSecMassDep.plotOn(frame_alpha, RooFit::LineColor(colorDil), RooFit::LineStyle(3));
  frame_alpha->GetYaxis()->SetTitle("#sigma_{t#bar{t}} (pb)");
  frame_alpha->SetMaximum(230.);
  frame_alpha->SetMinimum(110.);
  frame_alpha->Draw();
  TLegend theoLeg = TLegend(0.2, 0.52, 0.65, 0.9);
  theoLeg.SetFillStyle(0);
  theoLeg.SetBorderSize(0);
  for(unsigned h=0; h<nPdfSets; h++) {
    theoLeg.AddEntry(frame_alpha->findObject(mocPredXSec[h]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[h][0], "L");
    theoLeg.AddEntry(frame_alpha->findObject(mitPredXSec[h]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[h][1], "L");
  }
  theoLeg.AddEntry(frame_alpha->findObject(measXSecMassDep.GetName()+(TString)"_Norm[alpha]"), "CMS 2011", "L");
  theoLeg.Draw();
  char massTxt[99];
  sprintf(massTxt, "%s = %.1f GeV", mass.getTitle().Data(), mass.getVal());
  TLatex massText(0.,0.,massTxt);
  massText.SetNDC();
  massText.SetTextAlign(13);
  massText.SetX(0.70);
  massText.SetY(0.85);
  massText.SetTextFont(43);
  massText.SetTextSizePixels(22);
  massText.Draw();
  canvas->Print(printNameBase+".ps");
  canvas->Print(epsString("xsec_vs_alpha", pole, (PdfType)0));

  RooGaussian alphaProb[2] = {RooGaussian("alphaProbMSTW", "alphaProbMSTW", alpha, alphaMSTW_mean, alphaMSTW_unc),
			      RooGaussian("alphaProbHERA", "alphaProbHERA", alpha, alphaHERA_mean, alphaHERA_unc)};

//  RooProdPdf testProd("testProd", "testProd", RooArgList(measXSecPDF,mocPredXSec[0]->prob, alphaProb[0]));
//  RooAbsPdf*  projPdfTest = testProd.createProjection(xsec);
//  TF2* f2Test = (TF2*) projPdfTest->asTF(RooArgList(alpha, mass), RooArgList(), RooArgSet(alpha, mass));
//  gStyle->SetPalette(1);
//  f2Test->GetXaxis()->SetTitle(alpha.getTitle());
//  f2Test->GetYaxis()->SetTitle(mass.getTitle(true));
//  //  f2Test->Draw("cont3");
//  f2Test->SetLineColor(kGray);
//  f2Test->Draw("surf7");
//  f2Test->Draw("cont1 same");
//  canvas->Print("test.eps");
//
//  canvas->Print(printNameBase+".ps]");
//  return 0;

  FinalLikeliResults* mocResultAlpha[nPdfSets];
  FinalLikeliResults* mocResultMass [nPdfSets];

  FinalLikeliResults* mitResultAlpha[nPdfSets];
  FinalLikeliResults* mitResultMass [nPdfSets];

  gStyle->SetEndErrorSize(5*gStyle->GetEndErrorSize());

  const double alphaAxisMin = 0.1135;
  const double alphaAxisMax = 0.1205;

  const double massAxisMin = 170.;
  const double massAxisMax = 180.;

  for(unsigned h=0; h<nPdfSets; h++) {
    const TString suf[3] = {"MSTW", "HERA", "ABM"};

//    mocResultAlpha[h] = new FinalLikeliResults("mocResultAlpha"+suf[h],
//					       xsec,mass,alpha, RooArgList(measXSecPDF,mocPredXSec[h]->prob,massProb));
//    mocResultMass[h]  = new FinalLikeliResults("mocResultMass"+suf[h],
//					       xsec,mass,alpha, RooArgList(measXSecPDF,mocPredXSec[h]->prob,alphaProb[h]));

    mocResultAlpha[h] = new FinalLikeliResults("mitResultAlpha"+suf[h],
					       xsec,mass,alpha, RooArgList(measXSecPDF,mitPredXSec[h]->prob,massProb));
    mocResultMass[h]  = new FinalLikeliResults("mitResultMass"+suf[h],
					       xsec,mass,alpha, RooArgList(measXSecPDF,mitPredXSec[h]->prob,alphaProb[h]));

    mocResultAlpha[h]->point.GetXaxis()->SetLimits(alphaAxisMin, alphaAxisMax);
    mocResultAlpha[h]->point.GetYaxis()->SetRangeUser(massAxisMin , massAxisMax);
    mocResultAlpha[h]->point.SetPointError(0, mocResultAlpha[h]->point.GetErrorX(0), 0);

    mocResultMass[h]->point.GetXaxis()->SetLimits(alphaAxisMin, alphaAxisMax);
    mocResultMass[h]->point.GetYaxis()->SetRangeUser(massAxisMin, massAxisMax);
    mocResultMass[h]->point.SetPointError(0, 0, mocResultMass[h]->point.GetErrorY(0));

    mocResultMass[h]->point  .SetLineStyle(2+h);
    mocResultMass[h]->ellipse.SetLineStyle(2+h);

    mocResultAlpha[h]->point  .SetLineStyle(2+h);
    mocResultAlpha[h]->ellipse.SetLineStyle(2+h);
  }
  mocResultMass[0]->point.SetMarkerStyle(22);
  mocResultMass[1]->point.SetMarkerStyle(26);

  mocResultAlpha[0]->point.SetMarkerStyle(23);
  mocResultAlpha[1]->point.SetMarkerStyle(32);

  TBox boxAlpha2012(alpha2012_mean.getVal()-alpha2012_unc.getVal(), massAxisMin,
		    alpha2012_mean.getVal()+alpha2012_unc.getVal(), massAxisMax);
  boxAlpha2012.SetFillColor(kYellow-9);
  boxAlpha2012.SetFillStyle(3007);
  TLine lineAlpha2012(alpha2012_mean.getVal(), massAxisMin,
		      alpha2012_mean.getVal(), massAxisMax);
  TLine lineAlpha2012_left(alpha2012_mean.getVal()-alpha2012_unc.getVal(), massAxisMin,
			   alpha2012_mean.getVal()-alpha2012_unc.getVal(), massAxisMax);
  TLine lineAlpha2012_right(alpha2012_mean.getVal()+alpha2012_unc.getVal(), massAxisMin,
			    alpha2012_mean.getVal()+alpha2012_unc.getVal(), massAxisMax);
  lineAlpha2012_left .SetLineColor(kYellow-9);
  lineAlpha2012_right.SetLineColor(kYellow-9);

  TText textAlpha2012(alpha2012_mean.getVal(), massAxisMax-0.5, "PDG 2012");
  textAlpha2012.SetTextAngle(90);
  textAlpha2012.SetTextAlign(31);
  textAlpha2012.SetTextSizePixels(18);
  textAlpha2012.SetTextFont(42);

  TText textAlphaMSTW(alphaMSTW_mean.getVal(), massAxisMax-0.5, "Default MSTW 2008");
  textAlphaMSTW.SetTextAngle(90);
  textAlphaMSTW.SetTextAlign(31);
  textAlphaMSTW.SetTextSizePixels(14);
  textAlphaMSTW.SetTextFont(42);

  TText textAlphaHERA(alphaHERA_mean.getVal(), massAxisMax-0.5, "Default HERAPDF 1.5");
  textAlphaHERA.SetTextAngle(90);
  textAlphaHERA.SetTextAlign(31);
  textAlphaHERA.SetTextSizePixels(14);
  textAlphaHERA.SetTextFont(42);

  TBox boxAlphaMSTW(alphaMSTW_mean.getVal()-alphaMSTW_unc.getVal(), massAxisMin,
		    alphaMSTW_mean.getVal()+alphaMSTW_unc.getVal(), massAxisMax);
  boxAlphaMSTW.SetFillColor(kGreen-9);
  boxAlphaMSTW.SetFillStyle(3013);
  TLine lineAlphaMSTW(alphaMSTW_mean.getVal(), massAxisMin,
		      alphaMSTW_mean.getVal(), massAxisMax);

  TLine lineAlphaMSTW_left(alphaMSTW_mean.getVal()-alphaMSTW_unc.getVal(), massAxisMin,
			   alphaMSTW_mean.getVal()-alphaMSTW_unc.getVal(), massAxisMax);
  TLine lineAlphaMSTW_right(alphaMSTW_mean.getVal()+alphaMSTW_unc.getVal(), massAxisMin,
			    alphaMSTW_mean.getVal()+alphaMSTW_unc.getVal(), massAxisMax);
  lineAlphaMSTW_left .SetLineColor(kGreen-9);
  lineAlphaMSTW_right.SetLineColor(kGreen-9);

  TBox boxAlphaHERA(alphaHERA_mean.getVal()-alphaHERA_unc.getVal(), massAxisMin,
		    alphaHERA_mean.getVal()+alphaHERA_unc.getVal(), massAxisMax);
  boxAlphaHERA.SetFillColor(kCyan-9);
  TLine lineAlphaHERA(alphaHERA_mean.getVal(), massAxisMin,
		      alphaHERA_mean.getVal(), massAxisMax);

  TBox boxMass(alphaAxisMin, mass_mean.getVal()-mass_unc.getVal(),
	       alphaAxisMax, mass_mean.getVal()+mass_unc.getVal());
  boxMass.SetFillColor(kMagenta-9);
  TLine lineMass(alphaAxisMin, mass_mean.getVal(),
		 alphaAxisMax, mass_mean.getVal());

  TText textMass(alphaAxisMin+0.0002, mass_mean.getVal(), "Tevatron July 2012");
  textMass.SetTextAlign(11);
  textMass.SetTextSizePixels(18);
  textMass.SetTextFont(42);

  TLegend legResultsMass = TLegend(0.2, 0.76, 0.5, 0.9);
  legResultsMass.SetFillStyle(0);
  legResultsMass.SetBorderSize(0);
  legResultsMass.AddEntry(&mocResultMass[0]->point, "MSTW 2008"  , "PL");
  legResultsMass.AddEntry(&mocResultMass[1]->point, "HERAPDF 1.5", "PL");

  TLegend legResultsAlpha = TLegend(0.2, 0.76, 0.5, 0.9);
  legResultsAlpha.SetFillStyle(0);
  legResultsAlpha.SetBorderSize(0);
  legResultsAlpha.AddEntry(&mocResultAlpha[0]->point, "MSTW 2008"  , "PL");
  legResultsAlpha.AddEntry(&mocResultAlpha[1]->point, "HERAPDF 1.5", "PL");

  mocResultMass[0]->point.Draw("AP");
  boxMass.Draw();
  boxAlpha2012.Draw();
  lineAlpha2012_left .Draw();
  lineAlpha2012_right.Draw();
  lineMass.Draw();
  lineAlpha2012.Draw();
  gPad->RedrawAxis();
  for(unsigned h=0; h<2; h++) {
    mocResultMass[h]->point.Draw("P");
    mocResultMass[h]->ellipse.Draw("L");
  }
  legResultsMass.Draw();
  textAlpha2012.Draw();
  textMass.Draw();
  TLatex* cmsLabel = cmsTxt(full2011dilep);
  cmsLabel->Draw();
  canvas->Print(printNameBase+".ps");
  canvas->Print(epsString("results_mass", pole, (PdfType)0));
  canvas->Print("results_mass.root");

  mocResultAlpha[0]->point.Draw("AP");
  boxAlphaHERA.Draw();
  boxAlphaMSTW.Draw();
  lineAlphaMSTW_left .Draw();
  lineAlphaMSTW_right.Draw();
  boxAlpha2012.Draw();
  lineAlphaHERA.Draw();
  lineAlpha2012_left .Draw();
  lineAlpha2012_right.Draw();
  lineAlphaMSTW.Draw();
  lineAlpha2012.Draw();
  gPad->RedrawAxis();
  for(unsigned h=0; h<2; h++) {
    mocResultAlpha[h]->point.Draw("P");
    mocResultAlpha[h]->ellipse.Draw("L");
  }
  legResultsAlpha.Draw();
  textAlpha2012.Draw();
  textAlphaMSTW.Draw();
  textAlphaHERA.Draw();
  cmsLabel->Draw();
  canvas->Print(printNameBase+".ps");
  canvas->Print(epsString("results_alpha", pole, (PdfType)0));
  canvas->Print("results_alpha.root");

  const TString header[2] = {"MSTW 2008", "HERAPDF 1.5"};

  for(unsigned h=0; h<2; h++) {
    TLegend legResultsAlphaMass = TLegend(0.2, 0.69, 0.5, 0.9);
    legResultsAlphaMass.SetFillStyle(0);
    legResultsAlphaMass.SetBorderSize(0);
    legResultsAlphaMass.SetHeader(header[h]);
    legResultsAlphaMass.AddEntry(&mocResultMass [h]->point, "Constrained #alpha_{S}", "PL");
    legResultsAlphaMass.AddEntry(&mocResultAlpha[h]->point, "Constrained m_{t}"     , "PL");

    mocResultAlpha[h]->point.Draw("AP");
    mocResultAlpha[h]->ellipse.Draw("L");
    mocResultMass [h]->point.Draw("P");
    mocResultMass [h]->ellipse.Draw("L");
    legResultsAlphaMass.Draw();
    cmsLabel->Draw();
    canvas->Print(printNameBase+".ps");
    TString canvasName = "results_alpha_vs_mass_"; canvasName += h;
    canvas->Print(canvasName+".root");
    canvas->Print(epsString("results_alpha_vs_mass", pole, (PdfType)h));
  }

//  if(pole) {
//    std::cout << "============================================================" << std::endl;
//    std::cout << "Langenfeld et al.: Extracted pole mass = " << mocMax
//	      << " GeV (converted to MSbar mass: " << mMSbar(mocMax) << " GeV)" << std::endl;
//    std::cout << "Ahrens et al.    : Extracted pole mass = " << ahrMax
//	      << " GeV (converted to MSbar mass: " << mMSbar(ahrMax) << " GeV)" << std::endl;
//    std::cout << "============================================================" << std::endl;
//  }
//
//  if(full2011dilep)
//    frame = mass.frame(RooFit::Range(160., 190.));
//  else
//    frame = mass.frame(RooFit::Range(150., 190.));
//
//  plotProjectedPDF(mocProjectedPDF, frame, colorMoc, 3505, mocMax, mocLowErr, mocHigErr);
//  plotProjectedPDF(ahrProjectedPDF, frame, colorAhr, 3554, ahrMax, ahrLowErr, ahrHigErr);
//
//  frame->GetYaxis()->SetTitle("Probability density");
//  if(full2011dilep)
//    frame->GetYaxis()->SetRangeUser(0., 0.056);
//  else
//    frame->GetYaxis()->SetRangeUser(0., 0.034);
//  frame->Draw();
//
//  TLatex* cmsLabel = cmsTxt(full2011dilep);
//  cmsLabel->Draw();
//
//  mocTF->SetLineColor(kBlack);
//  mocTF->SetFillColor(colorMoc);
//  mocTF->SetFillStyle(3305);
//
//  ahrTF->SetLineColor(kBlack);
//  ahrTF->SetFillColor(colorAhr);
//  ahrTF->SetFillStyle(3554);
//
//  double yMin = 0.77;
//  TLegend leg = TLegend(0.2, yMin, 0.9, 0.9);
//  leg.SetFillStyle(0);
//  leg.SetBorderSize(0);
//
//  char legTmpTxt[99];
//  sprintf(legTmpTxt, "Langenfeld et al. (%.1f +%.1f -%.1f GeV)", mocMax, mocHigErr, mocLowErr);
//  leg.AddEntry(mocTF, legTmpTxt, "F");
//  sprintf(legTmpTxt, "Ahrens et al. (%.1f +%.1f -%.1f GeV)", ahrMax, ahrHigErr, ahrLowErr);
//  leg.AddEntry(ahrTF, legTmpTxt, "F");
//  leg.Draw();
//
//  canvas->Print(printNameBase+".ps");
//  canvas->Print(epsString("densities", pole, heraPDF));
//
//  // producing final overview plots
//
//  //  gStyle->SetOptFit(0000); ???
//  ahr->GetXaxis()->SetRangeUser(140., 190.);
//  ahr->SetFillColor(colorAhr);
//  moc->SetFillColor(colorMoc);
//  //  moc->SetFillStyle(3002);
//  ahr->Draw("A3");
//  moc->Draw("3 same");
//  moc->Draw("L same");
//  ahr->GetYaxis()->CenterTitle(false);
//  gPad->RedrawAxis();
//  canvas->Print(printNameBase+".ps");
  
  // cleaning up

  canvas->Print(printNameBase+".ps]");

  if(!pole) {
    delete runningAlpha;
    delete mShift;
  }
  for(unsigned h=0; h<nPdfSets; h++) {
    for(unsigned j=0; j<4; j++) {
      //      delete ahr_vec[h].at(j);
      delete moc_vec[h].at(j);
      delete mit_vec[h].at(j);
      for(unsigned i=0; i<moc_funcs[h][j].size(); i++) {
	delete moc_funcs[h][j].at(i);
	//	delete ahr_funcs[h][j].at(i);
	delete mit_funcs[h][j].at(i);
      }
    }
    delete mitPredXSec[h];
    delete mocPredXSec[h];
    //    delete ahrPredXSec[h];

//    delete mitResultAlpha[h];
//    delete mitResultMass[h];

    delete mocResultAlpha[h];
    delete mocResultMass[h];
  }
  delete canvas;
  delete f1;
  delete cmsLabel;

  return 0;
}

//////////////////////////////////////////////////
// main function
//////////////////////////////////////////////////

int main(const int argc, const char** argv) {
  if(argc!=2) {
    std::cout << "Wrong number of arguments!" << std::endl;
    std::cout << "Choose either 'pole' or 'msbar'...!" << std::endl;
    return 64;
  }
  else if(strcmp(argv[1],"msbar") && strcmp(argv[1],"pole")) {
    std::cout << "Unkown argument: " << argv[1] << std::endl;
    std::cout << "Choose either 'pole' or 'msbar'...!" << std::endl;
    return 64;
  }
  return foldedLikelihoods(!strcmp(argv[1],"pole"));
}
