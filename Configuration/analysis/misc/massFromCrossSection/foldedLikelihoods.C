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

const double mZ=91.1876;

double alpha_s(const double Q, const double lambda_MSbar=0.213, const unsigned Nf = 5)
{
  //
  // c.f. arXiv:0908.1135 (Bethke: The 2009 World Average of alphaS)
  //
  const double lambda2 = lambda_MSbar*lambda_MSbar;
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

TGraphErrors* getRunningAlphaGraph(const double qRangeMin=80, const unsigned qRangeLength=111, const double lambda=0.213,
				   const double alphaErrAtMZ=0.0007)
{
  const double alphaAtMZ = alpha_s(mZ, lambda);
  double scale[qRangeLength];
  double alpha[qRangeLength];
  double scale_err[qRangeLength];
  double alpha_err[qRangeLength];
  double q = qRangeMin;
  for(unsigned i=0; i<qRangeLength; i++) {
    scale[i] = q;
    alpha[i] = alpha_s(q, lambda);
    scale_err[i] = 0.;
    alpha_err[i] = alphaErrAtMZ * alpha[i]/alphaAtMZ;
    q += 1;
  }
  TGraphErrors* graph = new TGraphErrors(qRangeLength, scale, alpha, scale_err, alpha_err);
  graph->GetXaxis()->SetTitle("Q (GeV)");
  graph->GetYaxis()->SetTitle("#alpha_{S} (Q)");
  graph->SetTitle("At three-loop level and with N(flavors)=5, using 2012 world average for #alpha_{S}(m_{Z})");
  return graph;
}

TGraphErrors getMeasXSecWithErr(const RooFormulaVar& measXSec, const RooFormulaVar& measXSecErr,
				RooRealVar& xvar, const double xMin, const double xMax, const unsigned nPoints)
{
  const double xOld = xvar.getVal();
  double x[nPoints];
  double y[nPoints];
  double xErr[nPoints];
  double yErr[nPoints];
  const double deltaX = (xMax - xMin)/nPoints;
  double xi = xMin;
  for(unsigned i=0; i<nPoints; i++) {
    xvar.setVal(xi);
    x[i] = xi;
    y[i] = measXSec.getVal();
    xErr[i] = 0.;
    yErr[i] = measXSecErr.getVal();
    xi += deltaX;
  }
  xvar.setVal(xOld);
  return TGraphErrors(nPoints, x, y, xErr, yErr);
}

TGraph* getAlphaLambdaGraph()
{
  unsigned nPoints=100;
  double lambda[nPoints];
  double alpha [nPoints];
  double x = 150;
  for(unsigned i=0; i<nPoints; i++) {
    lambda[i] = x;
    alpha [i] = alpha_s(mZ, x/1000.);
    x += 1;
  }
  TGraph* graph = new TGraph(nPoints, lambda, alpha);
  graph->GetXaxis()->SetTitle("#Lambda_{#bar{MS}} (MeV)");
  graph->GetYaxis()->SetTitle("#alpha_{S} (m_{Z})");
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
  case kMSTW : fileName += "_mstw.tab" ; break;
  case kHERA : fileName += "_hera.tab" ; break;
  case kABM  : fileName += "_abm.tab"  ; break;
  case kNNPDF: fileName += "_nnpdf.tab"; break;
  default    : std::cout << "PdfType (" << pdfType << ") not supported!" << std::endl; abort();
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
  TString name = "figures/"+label;
  name += (pole ? "_pole" : "_MSbar");
  switch (pdfType) {
  case kMSTW : name += "_mstw" ; break;
  case kHERA : name += "_hera" ; break;
  case kABM  : name += "_abm"  ; break;
  case kNNPDF: name += "_nnpdf"; break;
  default    : std::cout << "PdfType (" << pdfType << ") not supported!" << std::endl; abort();
  }
  return (name + ".eps");
}

void drawTheoryGraph(TGraphAsymmErrors* graph, TCanvas* canvas, const bool pole,
		     const TString epsLabel, const TString printNameBase)
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
  canvas->Print(epsLabel);
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
    if(relUncMean->GetFunction("pol1")) {
      relUncMean->GetFunction("pol1")->Draw("same");
      vec.push_back((TF1*) relUncMean->GetFunction("pol1")->Clone());
    }
    else
      std::cout << "WARNING: Failed to fit TGraph relUncMean for " << title << std::endl;
  }
  else {
    relUncUp->Fit("pol1", "Q");
    if(relUncUp->GetFunction("pol1")) {
      relUncUp->GetFunction("pol1")->Draw("same");
      vec.push_back((TF1*) relUncUp  ->GetFunction("pol1")->Clone());
    }
    else
      std::cout << "WARNING: Failed to fit TGraph relUncUp for " << title << std::endl;
    relUncDown->Fit("pol1", "Q");
    if(relUncDown->GetFunction("pol1")) {
      relUncDown->GetFunction("pol1")->Draw("same");
      vec.push_back((TF1*) relUncDown->GetFunction("pol1")->Clone());
    }
    else
      std::cout << "WARNING: Failed to fit TGraph relUncDown for " << title << std::endl;
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
  if(!mass.getTitle().Contains("bar"))
    mass.setVal(173.2);
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
  convLeg.AddEntry(convFrame->findObject(predXSec->name+"_rectangularProb_Norm[xsec]"), "Rect(#mu_{R/F})" , "F");
  convLeg.AddEntry(convFrame->findObject(predXSec->name+"_prob_Norm[xsec]"           ), "Gauss#otimesRect", "F");
  convLeg.Draw();
  TLatex textTop(0.,0.,title);
  textTop.SetNDC();
  textTop.SetTextAlign(11);
  textTop.SetX(gPad->GetLeftMargin());
  textTop.SetY(0.96);
  textTop.SetTextFont(43);
  textTop.SetTextSizePixels(25);
  textTop.Draw();
  char tmpTxt[99];
  sprintf(tmpTxt, "%s = %.1f GeV",
	  mass.getTitle().Data(), mass.getVal());
  TLatex textMass(0.,0.,tmpTxt);
  textMass.SetNDC();
  textMass.SetTextAlign(13);
  textMass.SetX(0.22);
  textMass.SetY(0.90);
  textMass.SetTextFont(43);
  textMass.SetTextSizePixels(24);
  textMass.Draw();
  sprintf(tmpTxt, "%s = %.4f",
	  alpha.getTitle().Data(), alpha.getVal());
  TLatex textAlpha(0.,0.,tmpTxt);
  textAlpha.SetNDC();
  textAlpha.SetTextAlign(13);
  textAlpha.SetX(0.22);
  textAlpha.SetY(0.85);
  textAlpha.SetTextFont(43);
  textAlpha.SetTextSizePixels(24);
  textAlpha.Draw();
  canvas->Print(printNameBase+".ps");
  canvas->Print(epsName);
  delete convFrame;
}

void drawAlphaVsMass(const std::vector<const RooFormulaVar*>& predVec, const std::vector<TString>& labels,
		     TCanvas* canvas, const TString printNameBase, const bool oneTheoryOnly=false)
{
  TBox boxMass2012(171.8, 0.10,
		   174.6, 0.13);
  boxMass2012.SetFillColor(kYellow);
  TLine lineMass2012(173.2, 0.10,
		     173.2, 0.13);
  lineMass2012.SetLineStyle(2);
  TText textMass2012(172.5, 0.101, "Tevatron June 2012");
  textMass2012.SetTextAngle(90);
  textMass2012.SetTextAlign(12);
  textMass2012.SetTextFont(43);
  textMass2012.SetTextSizePixels(21);
 
  TBox boxAlpha2012(144., 0.1177,
		    187., 0.1191);
  boxAlpha2012.SetFillColor(kYellow);
  TLine lineAlpha2012(144, 0.1184,
		      187, 0.1184);
  lineAlpha2012.SetLineStyle(2);
  TText textAlpha2012(145.5, 0.1186, "PDG World Average June 2012");
  textAlpha2012.SetTextAlign(11);
  textAlpha2012.SetTextFont(43);
  textAlpha2012.SetTextSizePixels(21);

  const unsigned color[8] = {kRed, kRed, kGreen, kGreen, kCyan, kCyan, kBlue, kBlue};
  const unsigned style[8] = {1, 6, 2, 8, 3, 4, 1, 6};
  const unsigned nPreds = (oneTheoryOnly ? 1 : predVec.size());
  double yMin = 0.91 - nPreds*0.06;
  if(yMin < 0.55)
    yMin = 0.55;
  TLegend leg = TLegend(0.2, yMin, 0.7, 0.91);
  leg.SetFillStyle(0);
  leg.SetBorderSize(0);
  TH1* h2[nPreds];
  for(unsigned i=0; i<nPreds; i++) {
    h2[i] = predVec.at(i)->createHistogram("mass,alpha",50,30);
    h2[i]->Scale(1./(1*0.001));
    const double levels[1] = {162.};
    h2[i]->SetContour(1, levels);
    h2[i]->GetXaxis()->SetRangeUser(144., 186.);
    if(oneTheoryOnly)
      h2[i]->SetLineWidth(4);
    else
      h2[i]->SetLineWidth(2);
    h2[i]->SetLineStyle(style[i]);
    h2[i]->SetLineColor(color[i]);
    leg.AddEntry(h2[i], labels.at(i), "L");
    if(i==0) {
      h2[i]->Draw("cont3");
      boxMass2012.Draw();
      if(oneTheoryOnly)
	boxAlpha2012.Draw();
      lineMass2012.Draw();
      textMass2012.Draw();
      if(oneTheoryOnly) {
	lineAlpha2012.Draw();
	textAlpha2012.Draw();
      }
    }
    h2[i]->Draw("cont3 same");
  }
  leg.Draw();
  TLatex text(0.,0., "Approx. NNLO, #sigma_{t#bar{t}} (7 TeV) = 162 pb");
  text.SetNDC();
  text.SetTextAlign(13);
  text.SetX(gPad->GetLeftMargin());
  text.SetY(0.99);
  text.SetTextFont(43);
  text.SetTextSizePixels(16);
  text.Draw();
  gPad->RedrawAxis();
  canvas->Print(printNameBase+".ps");
  if(oneTheoryOnly)
    canvas->Print(printNameBase+"_predXSecAlphaVsMass_oneTheoryOnly.eps");
  else
    canvas->Print(printNameBase+"_predXSecAlphaVsMass.eps");
  for(unsigned i=0; i<nPreds; i++)
    delete h2[i];
}

void plotProjectedPDF(FinalLikeliResults1D* result, RooPlot* frame, const int color, const int fillStyle,
		      const RooRealVar& x_var)
{
  TString normRange = (TString)x_var.GetName() + "_fullRange";
  result->projPdf->plotOn(frame, RooFit::Range(result->bestX - result->lowErrFromIntegral,
					       result->bestX + result->highErrFromIntegral), RooFit::NormRange(normRange),
			  RooFit::FillStyle(fillStyle), RooFit::FillColor(color-9), RooFit::LineColor(color-9),
			  RooFit::DrawOption("F"), RooFit::VLines(), RooFit::Name("Confide"));
  result->projPdf->plotOn(frame, RooFit::LineColor(color+1), RooFit::NormRange(normRange));
  double epsilon = 0.00001;
  if(!strcmp(x_var.GetName(),"mass"))
    epsilon = 0.01;
  if(x_var.GetName())
    result->projPdf->plotOn(frame, RooFit::Range(result->bestX - epsilon,
						 result->bestX + epsilon), RooFit::NormRange(normRange),
			    RooFit::LineColor(kBlack), RooFit::LineWidth(2), RooFit::LineStyle(2), RooFit::VLines(),
			    RooFit::Name("Maximum"));
  frame->GetYaxis()->SetTitle("Likelihood density");
}

TLatex* cmsTxt()
{
  const TString txt = "2.3 fb^{-1} of 2011 CMS t#bar{t} data #times approx. NNLO,  #sqrt{s} = 7 TeV, m = 173.2 #pm 1.4 GeV" ;
  TLatex* text = new TLatex(0,0,txt);
  text->SetNDC();
  text->SetTextAlign(13);
  text->SetX(gPad->GetLeftMargin());
  text->SetY(1.003);
  text->SetTextFont(43);
  text->SetTextSizePixels(25);
  return text;
}

int foldedLikelihoods(const bool pole)
{
  const bool useAlphaUnc = false;

  setTDRStyle();
  gStyle->SetTitleBorderSize(1);
  gStyle->SetOptFit(0011);

  RooAbsReal::defaultIntegratorConfig()->method2D().setLabel("RooSegmentedIntegrator2D");
  RooAbsReal::defaultIntegratorConfig()->getConfigSection("RooIntegrator1D").setCatLabel("sumRule", "Midpoint");
  RooAbsReal::defaultIntegratorConfig()->methodND().setLabel("RooMCIntegrator");

  gSystem->mkdir("figures");

  TString printNameBase = "figures/foldedLikelihoods";
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
    canvas->Print("figures/alpha_s.eps");
    gStyle->SetOptTitle(0);
  }

  TGraph* mShift = 0;
  if(!pole) {
    mShift = getMassShiftGraph();
    mShift->Draw("AP");
    mShift->Fit("pol1", "Q");
    canvas->Print(printNameBase+".ps");
    canvas->Print("figures/MSbar_vs_pole_mass.eps");
  }

  //////////////////////////////////////
  /// Start of quick'n dirty
  //////////////////////////////////////

  TGraph* alphaLambdaGraph = getAlphaLambdaGraph();
  alphaLambdaGraph->Draw("AC");
  canvas->Print(printNameBase+".ps");
  delete alphaLambdaGraph;

  runningAlpha = getRunningAlphaGraph(50, 450);
  TGraph* runningAlpha_new = getRunningAlphaGraph(50, 450, 0.200, 0.0032);

  runningAlpha->SetFillColor(kMagenta-9);
  runningAlpha_new->SetFillColor(kCyan);
  runningAlpha->SetLineStyle(2);
  runningAlpha_new->SetLineStyle(3);

  TLegend lastMinuteLeg = TLegend(0.4, 0.7, 0.95, 0.85);
  lastMinuteLeg.SetFillColor(0);
  lastMinuteLeg.SetBorderSize(0);
  lastMinuteLeg.AddEntry(runningAlpha    , "PDG 2012 world average"  , "LF");
  lastMinuteLeg.AddEntry(runningAlpha_new, "Our result", "LF");

  TLine lineMZ(mZ, 0.09, mZ, 0.135);
  TLatex textMZ(0.95*mZ, 0.11, "m_{Z}");
  textMZ.SetTextAngle(90);
  textMZ.SetTextAlign(32);
  textMZ.SetTextFont(43);
  textMZ.SetTextSizePixels(25);

  TLine line2Mt(2*173.2, 0.09, 2*173.2, 0.135);
  TLatex text2Mt(0.95*2*173.2, 0.11, "2m_{t}");
  text2Mt.SetTextAngle(90);
  text2Mt.SetTextAlign(32);
  text2Mt.SetTextFont(43);
  text2Mt.SetTextSizePixels(25);

  runningAlpha_new->Draw("A3");
  lineMZ.Draw();
  textMZ.Draw();
  line2Mt.Draw();
  text2Mt.Draw();
  runningAlpha_new->Draw("3");
  runningAlpha->Draw("3");
  runningAlpha->Draw("XC");
  runningAlpha_new->Draw("XC");
  gPad->SetLogx();
  lastMinuteLeg.Draw();
  gPad->RedrawAxis();
  runningAlpha_new->GetXaxis()->SetLimits(50, 500);
  runningAlpha_new->GetXaxis()->SetMoreLogLabels();
  runningAlpha_new->GetXaxis()->SetNoExponent();
  runningAlpha_new->GetYaxis()->SetRangeUser(0.09, 0.135);
  canvas->Print(printNameBase+".ps");
  canvas->Print(printNameBase+"results_qDep.eps");
  gPad->SetLogx(false);

  delete runningAlpha_new;

  //////////////////////////////////////
  /// End of quick'n dirty
  //////////////////////////////////////

  const unsigned nPdfSets  = 3;
  const unsigned nTheories = 2;

  //  std::vector<TGraphAsymmErrors*> ahr_vec[nPdfSets];
  std::vector<TGraphAsymmErrors*> moc_vec[nPdfSets];
  std::vector<TGraphAsymmErrors*> mit_vec[nPdfSets];
  
  //  TGraphAsymmErrors* ahr[nPdfSets];
  TGraphAsymmErrors* moc[nPdfSets];
  TGraphAsymmErrors* mit[nPdfSets];
  
  std::vector<TF1*> moc_funcs[nPdfSets][4];
  //  std::vector<TF1*> ahr_funcs[nPdfSets][4];
  std::vector<TF1*> mit_funcs[nPdfSets][4];

  const TString pdfName [4] = {"MSTW2008", "HERAPDF1.5", "ABM11", "NNPDF2.1"};
  const TString theoName[nTheories] = {"HATHOR 1.2", "Top++ 1.2"};

  TString theoTitle[nPdfSets][nTheories];
  for(unsigned h=0; h<nPdfSets; h++)
    for(unsigned i=0; i<nTheories; i++)
      theoTitle[h][i] = theoName[i] + " with " + pdfName[h];

  const TString errName [4] = {"Scale", "Experimental PDF", "#alpha_{S}", "Total"};
  const TString errLabel[4] = {"scale", "expPDF", "alphaS", "total"};

  TF1* f1 = new TF1("f1", "([0]+[1]*x+[2]*TMath::Power(x,2)+[3]*TMath::Power(x,3))/TMath::Power(x,4)", 0, 1000);
  f1->SetParNames("a", "b", "c", "d");

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
    drawTheoryGraph(mit[h], canvas, pole, epsString("mitov", pole, (PdfType)h), printNameBase);
    for(unsigned j=0; j<2; j++)
      moc_funcs[h][j] = getAndDrawRelativeUncertainty(moc_vec[h].at(j), canvas, pole, errName[j],
						      epsString("relUnc_moch_"+errLabel[j], pole, (PdfType)h),
						      printNameBase, (j==1 || j==2));
    drawTheoryGraph(moc[h], canvas, pole, epsString("moch", pole, (PdfType)h), printNameBase);
//    for(unsigned j=0; j<4; j++)
//      ahr_funcs[h][j] = getAndDrawRelativeUncertainty(ahr_vec[h].at(j), canvas, pole, errName[j],
//						      epsString("relUnc_ahrens_"+errLabel[j], pole, (PdfType)h),
//						      printNameBase, (j==1 || j==2));
//    drawTheoryGraph(ahr[h], canvas, pole, "ahrens", printNameBase);
    
    gStyle->SetOptTitle(0);
  }

//  canvas->Print(printNameBase+".ps]");
//  return 0;

  RooRealVar mass("mass", "m_{t}", 140., 190., "GeV");
  if(!pole)
    mass.SetTitle("m_{t}^{#bar{MS}}");

  RooRealVar alpha("alpha", "#alpha_{S}(m_{Z})", 0.10, 0.13);

  RooRealVar xsec("xsec" , "#sigma_{t #bar{t}}", 0., 900., "pb");

  RooRealVar alpha2012_mean("alpha2012_mean", "alpha2012_mean", 0.1184);
  RooRealVar alpha2012_unc ("alpha2012_unc" , "alpha2012_unc" , 0.0007);

  RooRealVar alphaMSTW_mean("alphaMSTW_mean", "alphaMSTW_mean", 0.1171); //Eur.Phys.J.C64:653-680,2009
  RooRealVar alphaMSTW_unc ("alphaMSTW_unc" , "alphaMSTW_unc" , 0.0014); //Eur.Phys.J.C64:653-680,2009

  RooRealVar alphaHERA_mean("alphaHERA_mean", "alphaHERA_mean", 0.1176);
  RooRealVar alphaHERA_unc ("alphaHERA_unc" , "alphaHERA_unc" , 0.0020);

  RooRealVar alphaABM_mean("alphaABM_mean", "alphaABM_mean", 0.1134);
  RooRealVar alphaABM_unc ("alphaABM_unc" , "alphaABM_unc" , 0.0011);

  RooRealVar alphaNNPDF_mean("alphaNNPDF_mean", "alphaNNPDF_mean", 0.1180); //dummy!!!
  RooRealVar alphaNNPDF_unc ("alphaNNPDF_unc" , "alphaNNPDF_unc" , 0.0080); //dummy!!!

  std::vector<RooRealVar> defaultAlphas;
  defaultAlphas.push_back(alphaMSTW_mean );
  defaultAlphas.push_back(alphaHERA_mean );
  defaultAlphas.push_back(alphaABM_mean  );
  defaultAlphas.push_back(alphaNNPDF_mean);

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

  RooFormulaVar deltaM("deltaM", "deltaM", "@0-172.5+@1", RooArgSet(mass, shift));

  RooRealVar p0("p0", "p0", 1.);
  RooRealVar p1("p1", "p1", -0.008);
  RooRealVar p2("p2", "p2", -0.000137);
  RooPolyVar measXSecMassDepRel("measXSecMassDepRel", "measXSecMassDepRel", deltaM, RooArgSet(p0, p1, p2));
  RooRealVar measXSec("measXSec", "measXSec", 161.9, "pb");
  RooRealVar measXSecErr("measXSecErr", "measXSecErr", 6.725, "pb");

  RooFormulaVar measXSecMassDep("measXSecMassDep", "measXSecMassDep", "(@0*@1)*(1+0.01*(@2-0.1180)/0.0100)",
				RooArgSet(measXSecMassDepRel,measXSec,alpha));
  RooFormulaVar measXSecMassDepErr("measXSecMassDepErr", "measXSecMassDepErr",
				   "TMath::Sqrt(TMath::Power((@0/@1)*@2,2)+TMath::Power((@0/@1)*@2*(1+0.01*TMath::Abs((@3-0.1180)/0.0100)),2))",
				   RooArgSet(measXSecMassDep,measXSec,measXSecErr,alpha));
  RooGaussian measXSecPDF("measXSecPDF", "measXSecPDF", xsec, measXSecMassDep, measXSecMassDepErr);

//  mass.setVal(173.2);
//  alpha.setVal(0.118);
//  std::cout << measXSecMassDep.getVal() << std::endl;
//  std::cout << measXSecMassDepErr.getVal() << std::endl;
//  return 0;

  PredXSec* mitPredXSec[nPdfSets];
  PredXSec* mocPredXSec[nPdfSets];
  //  PredXSec* ahrPredXSec[nPdfSets];

  std::vector<const RooFormulaVar*> predXSecFormularVec;
  std::vector<TString> predXSecFormularVecLabels;

  for(unsigned h=0; h<nPdfSets; h++) {
    TString alphaFileName = (pole ? "pole_" : "msbar_");
    TString suf = "PredXSec";

    switch(h) {
    case kMSTW : alphaFileName += "mstw" ; suf += "MSTW" ; break;
    case kHERA : alphaFileName += "hera" ; suf += "HERA" ; break;
    case kABM  : alphaFileName += "abm"  ; suf += "ABM"  ; break;
    case kNNPDF: alphaFileName += "nnpdf"; suf += "NNPDF"; break;
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

    predXSecFormularVec.push_back(&mitPredXSec[h]->xsec);
    predXSecFormularVec.push_back(&mocPredXSec[h]->xsec);

    predXSecFormularVecLabels.push_back(theoTitle[h][1]);
    predXSecFormularVecLabels.push_back(theoTitle[h][0]);
  }
  drawAlphaVsMass(predXSecFormularVec, predXSecFormularVecLabels, canvas, printNameBase, true);
  drawAlphaVsMass(predXSecFormularVec, predXSecFormularVecLabels, canvas, printNameBase);

//  canvas->Print(printNameBase+".ps]");
//  return 0;

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

  mass.setVal(mass_mean.getVal());

  TGraphErrors measXSecWithErr = getMeasXSecWithErr(measXSecMassDep, measXSecMassDepErr, alpha, 0.10, 0.13, 30);

  RooPlot* frame_alpha = alpha.frame(RooFit::Range(0.110, 0.125));
  frame_alpha->addObject(&measXSecWithErr, "3");
  frame_alpha->addObject(&measXSecWithErr, "CX");
  mitPredXSec[0]->xsec.plotOn(frame_alpha, RooFit::LineColor(kRed));
  frame_alpha->GetYaxis()->SetTitle("#sigma_{t#bar{t}} (pb)");
  frame_alpha->SetMaximum(230.);
  frame_alpha->SetMinimum(110.);
  frame_alpha->Draw();
  measXSecWithErr.SetFillColor(kBlue-9);
  measXSecWithErr.SetLineColor(kBlue+1);
  TLegend theoLeg = TLegend(0.18, 0.81, 0.63, 0.92);
  theoLeg.SetFillStyle(0);
  theoLeg.SetBorderSize(0);
  theoLeg.AddEntry(&measXSecWithErr, "CMS 2011, 2.3 fb^{-1}", "FL");
  theoLeg.AddEntry(frame_alpha->findObject(mitPredXSec[0]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[0][1], "L");
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
  canvas->Print(printNameBase+"_xsec_vs_alpha_pre1.eps");
  mocPredXSec[0]->xsec.plotOn(frame_alpha, RooFit::LineColor(kRed)  , RooFit::LineStyle(2));
  frame_alpha->SetMaximum(230.);
  frame_alpha->SetMinimum(110.);
  frame_alpha->Draw();
  theoLeg.AddEntry(frame_alpha->findObject(mocPredXSec[0]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[0][0], "L");
  theoLeg.SetY1NDC(0.75);
  theoLeg.Draw();
  massText.Draw();
  canvas->Print(printNameBase+".ps");
  canvas->Print(printNameBase+"_xsec_vs_alpha_pre2.eps");
  mocPredXSec[1]->xsec.plotOn(frame_alpha, RooFit::LineColor(kGreen), RooFit::LineStyle(2));
  mocPredXSec[2]->xsec.plotOn(frame_alpha, RooFit::LineColor(kCyan ), RooFit::LineStyle(2));
  mitPredXSec[1]->xsec.plotOn(frame_alpha, RooFit::LineColor(kGreen));
  mitPredXSec[2]->xsec.plotOn(frame_alpha, RooFit::LineColor(kCyan));
  frame_alpha->SetMaximum(230.);
  frame_alpha->SetMinimum(110.);
  frame_alpha->Draw();
  for(unsigned h=1; h<nPdfSets; h++) {
    theoLeg.AddEntry(frame_alpha->findObject(mitPredXSec[h]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[h][1], "L");
    theoLeg.AddEntry(frame_alpha->findObject(mocPredXSec[h]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[h][0], "L");
  }
  theoLeg.SetY1NDC(0.54);
  theoLeg.Draw();
  massText.Draw();
  canvas->Print(printNameBase+".ps");
  canvas->Print(printNameBase+"_xsec_vs_alpha.eps");

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

  FinalLikeliResults1D* mocResult[nPdfSets];
  FinalLikeliResults1D* mitResult[nPdfSets];

  const unsigned nSummaryPoints = nPdfSets*nTheories;
  TGraphAsymmErrors mocSummaryGraphInnErr(nSummaryPoints);
  TGraphAsymmErrors mocSummaryGraphTotErr(nSummaryPoints);
  TGraphAsymmErrors mitSummaryGraphInnErr(nSummaryPoints);
  TGraphAsymmErrors mitSummaryGraphTotErr(nSummaryPoints);
  unsigned iGraphPoint = 0;

  for(unsigned h=0; h<nPdfSets; h++) {
    const TString suf[4] = {"MSTW", "HERA", "ABM", "NNPDF"};

    mocResult[h] = new FinalLikeliResults1D("mocResult"+suf[h], xsec, alpha, RooArgList(measXSecPDF,mocPredXSec[h]->prob),
					    mass, mass_mean, mass_unc);
    mitResult[h] = new FinalLikeliResults1D("mitResult"+suf[h], xsec, alpha, RooArgList(measXSecPDF,mitPredXSec[h]->prob),
					    mass, mass_mean, mass_unc);

    mocResult[h]->addPointToGraphs(mocSummaryGraphInnErr, mocSummaryGraphTotErr, iGraphPoint, 2*iGraphPoint+0.2);
    mitResult[h]->addPointToGraphs(mitSummaryGraphInnErr, mitSummaryGraphTotErr, iGraphPoint, 2*iGraphPoint+0.8);
    iGraphPoint++;
  }

  gStyle->SetEndErrorSize(5*gStyle->GetEndErrorSize());

  mocSummaryGraphTotErr.GetXaxis()->SetLimits(0.1115, 0.1245);
  mocSummaryGraphTotErr.GetXaxis()->SetTitle(alpha.getTitle());
  mocSummaryGraphTotErr.GetYaxis()->SetRangeUser(-1, nSummaryPoints+2);
  mocSummaryGraphTotErr.GetYaxis()->SetNdivisions(0);

  mocSummaryGraphTotErr.SetMarkerSize(2);
  mitSummaryGraphTotErr.SetMarkerSize(2);
  mocSummaryGraphTotErr.SetMarkerStyle(22);
  mitSummaryGraphTotErr.SetMarkerStyle(23);

  TBox boxAlpha2012(alpha2012_mean.getVal()-alpha2012_unc.getVal(), -1,
		    alpha2012_mean.getVal()+alpha2012_unc.getVal(), nSummaryPoints+2);
  boxAlpha2012.SetFillColor(kMagenta-9);
  boxAlpha2012.SetFillStyle(3007);
  TLine lineAlpha2012(alpha2012_mean.getVal(), -1,
		      alpha2012_mean.getVal(), nSummaryPoints+2);
  lineAlpha2012.SetLineStyle(2);
  TLine lineAlpha2012_left(alpha2012_mean.getVal()-alpha2012_unc.getVal(), -1,
			   alpha2012_mean.getVal()-alpha2012_unc.getVal(), nSummaryPoints+2);
  TLine lineAlpha2012_right(alpha2012_mean.getVal()+alpha2012_unc.getVal(), -1,
			    alpha2012_mean.getVal()+alpha2012_unc.getVal(), nSummaryPoints+2);
  lineAlpha2012_left .SetLineColor(kMagenta-9);
  lineAlpha2012_right.SetLineColor(kMagenta-9);
  TText textAlpha2012(alpha2012_mean.getVal()-0.5*alpha2012_unc.getVal(), (nSummaryPoints+2)*0.95, "PDG 2012");
  textAlpha2012.SetTextAngle(90);
  textAlpha2012.SetTextAlign(32);
  textAlpha2012.SetTextFont(43);
  textAlpha2012.SetTextSizePixels(23);

  TBox boxAlphaMSTW(alphaMSTW_mean.getVal()-alphaMSTW_unc.getVal(), -0.1,
		    alphaMSTW_mean.getVal()+alphaMSTW_unc.getVal(),  1.1);
  boxAlphaMSTW.SetFillColor(kGreen-9);
  TLine lineAlphaMSTW(alphaMSTW_mean.getVal(), -0.1,
		      alphaMSTW_mean.getVal(),  1.1);
  lineAlphaMSTW.SetLineStyle(3);
  TText textAlphaMSTW(0.1215, 0.5, "MSTW2008");
  textAlphaMSTW.SetTextFont(43);
  textAlphaMSTW.SetTextSizePixels(26);
  textAlphaMSTW.SetTextAlign(12);

  TBox boxAlphaHERA(alphaHERA_mean.getVal()-alphaHERA_unc.getVal(), 1.9,
		    alphaHERA_mean.getVal()+alphaHERA_unc.getVal(), 3.1);
  boxAlphaHERA.SetFillColor(kGreen-9);
  TLine lineAlphaHERA(alphaHERA_mean.getVal(), 1.9,
		      alphaHERA_mean.getVal(), 3.1);
  lineAlphaHERA.SetLineStyle(3);
  TText textAlphaHERA(alphaHERA_mean.getVal()+alphaHERA_unc.getVal()+0.0004, 2.5, "HERAPDF1.5");
  textAlphaHERA.SetTextFont(43);
  textAlphaHERA.SetTextSizePixels(26);
  textAlphaHERA.SetTextAlign(12);

  TBox boxAlphaABM(alphaABM_mean.getVal()-alphaABM_unc.getVal(), 3.9,
		    alphaABM_mean.getVal()+alphaABM_unc.getVal(), 5.1);
  boxAlphaABM.SetFillColor(kGreen-9);
  TLine lineAlphaABM(alphaABM_mean.getVal(), 3.9,
		      alphaABM_mean.getVal(), 5.1);
  lineAlphaABM.SetLineStyle(3);
  TText textAlphaABM(alphaABM_mean.getVal()+alphaABM_unc.getVal()+0.0004, 4.5, "ABM11");
  textAlphaABM.SetTextFont(43);
  textAlphaABM.SetTextSizePixels(26);
  textAlphaABM.SetTextAlign(12);

  TText textAlphaNNPDF(alphaHERA_mean.getVal()+alphaHERA_unc.getVal()+0.0004, 6.5, "NNPDF2.1");
  textAlphaNNPDF.SetTextFont(43);
  textAlphaNNPDF.SetTextSizePixels(26);
  textAlphaNNPDF.SetTextAlign(12);

  TLegend summaryLeg = TLegend(0.1, 0.75, 0.25, 0.9);
  summaryLeg.SetFillStyle(0);
  summaryLeg.SetBorderSize(0);
  summaryLeg.AddEntry(&mitSummaryGraphTotErr, theoName[1], "PL");
  summaryLeg.AddEntry(&mocSummaryGraphTotErr, theoName[0], "PL");

  const double oldPadLeftMargin = gPad->GetLeftMargin();
  gPad->SetLeftMargin(gPad->GetRightMargin());

  mocSummaryGraphTotErr.Draw("AP");
  boxAlphaMSTW.Draw();
  lineAlphaMSTW.Draw();
  boxAlphaHERA.Draw();
  lineAlphaHERA.Draw();
  boxAlphaABM.Draw();
  lineAlphaABM.Draw();
  boxAlpha2012.Draw();
  lineAlpha2012.Draw();
  lineAlpha2012_left.Draw();
  lineAlpha2012_right.Draw();
  mocSummaryGraphTotErr.Draw("P");
  mocSummaryGraphInnErr.Draw("||");
  mitSummaryGraphTotErr.Draw("P");
  mitSummaryGraphInnErr.Draw("||");
  summaryLeg.Draw();
  gPad->RedrawAxis();
  textAlpha2012.Draw();
  textAlphaMSTW.Draw();
  textAlphaHERA.Draw();
  textAlphaABM.Draw();
  if(nPdfSets>kNNPDF)
    textAlphaNNPDF.Draw();
  TLatex* cmsLabel = cmsTxt();
  cmsLabel->Draw();
  canvas->Print(printNameBase+"_summaryPlot.eps");
  canvas->Print(printNameBase+".ps");

  gPad->SetLeftMargin(oldPadLeftMargin);

  ofstream outfile;
  outfile.open(printNameBase+ "_summary.tab");
  outfile << "\\begin{tabular}{|ll|c|c|c|}" << std::endl;
  outfile << "\\hline" << std::endl;
  outfile << " & & Most likely & \\multicolumn{2}{c|}{Uncertainty} \\\\" << std::endl;
  outfile << " & & value       & Total & From $\\delta m_{t}$ \\\\" << std::endl;
  outfile << "\\hline" << std::endl;
  for(unsigned h=0; h<nPdfSets; h++) {
    char tmpTxt[99];
    sprintf(tmpTxt, "%s & \\multirow{2}{*}{with %s} & %.4f & $\\pm %.4f$ & $\\pm %.4f$ \\\\",
	    theoName[1].Data(), pdfName[h].Data(),
	    mitResult[h]->bestX,
	    TMath::Max(mitResult[h]->highErrTotal, mitResult[h]->lowErrTotal),
	    TMath::Max(mitResult[h]->highErrFromConstraintUncertainty, mitResult[h]->lowErrFromConstraintUncertainty));
    outfile << tmpTxt << std::endl;
    outfile << "\\cline{3-5}" << std::endl;
    sprintf(tmpTxt, "%s & & %.4f & $\\pm %.4f$ & $\\pm %.4f$ \\\\",
	    theoName[0].Data(),
	    mocResult[h]->bestX,
	    TMath::Max(mocResult[h]->highErrTotal, mocResult[h]->lowErrTotal),
	    TMath::Max(mocResult[h]->highErrFromConstraintUncertainty, mocResult[h]->lowErrFromConstraintUncertainty));
    outfile << tmpTxt << std::endl;
    outfile << "\\hline" << std::endl;
  }
  outfile << "\\end{tabular}" << std::endl;
  outfile.close();
  std::cout << "Wrote " << printNameBase+ "_summary.tab" << std::endl;

//  const unsigned color[3] = {kRed+1, kMagenta, kGreen-3};
//  const unsigned fillStyle[3] = {3545, 3305, 3554};

  for(unsigned h=0; h<nPdfSets; h++) {
    char tmpTxt[99];
    sprintf(tmpTxt, "2.3 fb^{-1} of 2011 CMS t#bar{t} data #times %s", theoTitle[h][0].Data());
    TLatex text(0.,0.,tmpTxt);
    text.SetNDC();
    text.SetTextAlign(13);
    text.SetX(gPad->GetLeftMargin());
    text.SetY(1.003);
    text.SetTextFont(43);
    text.SetTextSizePixels(25);

    sprintf(tmpTxt, "%s = %.1f GeV",
	    mass.getTitle().Data(), mass.getVal());
    TLatex textMass(0.,0.,tmpTxt);
    textMass.SetNDC();
    textMass.SetTextAlign(13);
    textMass.SetX(0.22);
    textMass.SetY(0.90);
    textMass.SetTextFont(43);
    textMass.SetTextSizePixels(24);

    frame_alpha = alpha.frame(RooFit::Range(0.105, 0.130));
    plotProjectedPDF(mocResult[h], frame_alpha, kRed, 1001, alpha);
    frame_alpha->Draw();
    frame_alpha->SetMaximum(1.4*frame_alpha->GetMaximum());

    TLegend likeLeg = TLegend(0.5, 0.75, 0.9, 0.92);
    likeLeg.SetFillStyle(0);
    likeLeg.SetBorderSize(0);
    likeLeg.AddEntry("Maximum", "Maximum likelihood"      , "L");
    likeLeg.AddEntry("Confide", "68% confidence interval" , "F");
    likeLeg.SetTextFont(43);
    likeLeg.SetTextSizePixels(25);

    likeLeg.Draw();
    text.Draw();
    textMass.Draw();
    canvas->Print(printNameBase+".ps");
    canvas->Print(epsString("final_probDensity_moch", pole, (PdfType)h));

    sprintf(tmpTxt, "2.3 fb^{-1} of 2011 CMS t#bar{t} data #times %s", theoTitle[h][1].Data());    
    text.SetTitle(tmpTxt);
    frame_alpha = alpha.frame(RooFit::Range(0.105, 0.130));
    plotProjectedPDF(mitResult[h], frame_alpha, kRed, 1001, alpha);
    frame_alpha->Draw();
    frame_alpha->SetMaximum(1.4*frame_alpha->GetMaximum());
    likeLeg.Draw();
    text.Draw();
    textMass.Draw();
    canvas->Print(printNameBase+".ps");
    canvas->Print(epsString("final_probDensity_mitov", pole, (PdfType)h));
  }
  
  // cleaning up

  canvas->Print(printNameBase+".ps]");

  if(runningAlpha)
    delete runningAlpha;
  if(mShift)
    delete mShift;
  for(unsigned h=0; h<nPdfSets; h++) {
    for(unsigned j=0; j<4; j++) {
      delete moc_vec[h].at(j);
      delete mit_vec[h].at(j);
      for(unsigned i=0; i<moc_funcs[h][j].size(); i++) {
	delete moc_funcs[h][j].at(i);
	delete mit_funcs[h][j].at(i);
      }
    }
    delete mocResult[h];
    delete mitResult[h];
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
