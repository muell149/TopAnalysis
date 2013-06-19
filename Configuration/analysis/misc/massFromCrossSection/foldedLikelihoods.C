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

enum PdfType { kMSTW, kHERA, kABM, kNNPDF, kCT };

const double mZ=91.1876;

const bool moch_highE=true;

const bool topppOnly=true;

const TString figDir = (moch_highE ? "figures" : "figures_mocOff");

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

TGraph getRelChangePredXSec(const PredXSec* predXSec, RooRealVar& xvar)
{
  const bool isAlpha = (xvar.getTitle().Contains("alpha") ? true : false);
  const double xOld = xvar.getVal();
  const unsigned nPoints = (isAlpha ? 21 : 21);
  const double xMin = (isAlpha ? 0.108 : 163.);
  const double xMax = (isAlpha ? 0.128 : 183.);
  const double refX = (isAlpha ? 0.118 : 173.);
  const double deltaX = (xMax - xMin)/nPoints;
  double x[nPoints];
  double y[nPoints];
  xvar.setVal(refX);
  const double refY = predXSec->xsec.getVal();
  double xi = xMin;
  for(unsigned i=0; i<nPoints; i++) {
    xvar.setVal(xi);
    x[i] = xi;
    y[i] = predXSec->xsec.getVal() / refY;
    xi += deltaX;
  }
  xvar.setVal(xOld);
  return TGraph(nPoints, x, y);
}

TGraphAsymmErrors getPredXSecWithErr(const PredXSec* predXSec, RooRealVar& xvar, const double xMin, const double xMax,
				     const unsigned nPoints, const double xerr=0.)
{
  const double xOld = xvar.getVal();
  double x[nPoints];
  double y[nPoints];
  double xErr[nPoints];
  double yErrLo[nPoints];
  double yErrHi[nPoints];
  const double deltaX = (xMax - xMin)/nPoints;
  double xi = xMin;
  for(unsigned i=0; i<nPoints; i++) {
    xvar.setVal(xi);
    x[i] = xi;
    y[i] = predXSec->xsec.getVal();
    xErr[i] = xerr;
    yErrLo[i] = TMath::Sqrt(TMath::Power(y[i]-predXSec->xsecScaleDown.getVal(),2) +
			    TMath::Power(predXSec->gaussianUnc.getVal(),2));
    yErrHi[i] = TMath::Sqrt(TMath::Power(predXSec->xsecScaleUp.getVal()-y[i],2) +
			    TMath::Power(predXSec->gaussianUnc.getVal(),2));
    xi += deltaX;
  }
  xvar.setVal(xOld);
  return TGraphAsymmErrors(nPoints, x, y, xErr, xErr, yErrLo, yErrHi);  
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
  TString fileName = "theories_7TeV/" + name;
  fileName += (pole ? "_pole" : "_msbar");
  switch (pdfType) {
  case kMSTW : fileName += "_mstw" ; break;
  case kHERA : fileName += "_hera" ; break;
  case kABM  : fileName += "_abm"  ; break;
  case kNNPDF: fileName += "_nnpdf"; break;
  case kCT   : fileName += "_ct"; break;
  default    : std::cout << "PdfType (" << pdfType << ") not supported!" << std::endl; abort();
  }
  if(name=="moch" && !moch_highE)
    fileName += "_off";
  fileName += ".tab";
  
  std::cout << "Reading " << fileName << " ..." << std::endl;
  ifstream in;
  in.open(fileName);

  const unsigned nPoints = 91;
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
    if(pdfType==kCT) {
      err_u[1] /= 1.64;
      err_d[1] /= 1.64;
    }
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
  TString name = figDir+"/"+label;
  name += (pole ? "_pole" : "_MSbar");
  switch (pdfType) {
  case kMSTW : name += "_mstw" ; break;
  case kHERA : name += "_hera" ; break;
  case kABM  : name += "_abm"  ; break;
  case kNNPDF: name += "_nnpdf"; break;
  case kCT: name += "_ct"   ; break;
  default    : std::cout << "PdfType (" << pdfType << ") not supported!" << std::endl; abort();
  }
  return (name + ".eps");
}

void drawTheoryGraph(TGraphAsymmErrors* graph, TCanvas* canvas, const bool pole,
		     TString epsLabel, const TString printNameBase)
{
  if(pole)
    graph->GetXaxis()->SetTitle("m_{t} (GeV)");
  else
    graph->GetXaxis()->SetTitle("m_{t}^{#bar{MS}} (GeV)");
  graph->GetYaxis()->SetTitle("#sigma_{t#bar{t}} (pb)");
  graph->GetYaxis()->CenterTitle();

  graph->Draw("AP");
  graph->Draw("2");
  graph->GetFunction("f1")->Draw("same");

  canvas->Print(printNameBase+".ps");
  canvas->Print(epsLabel);

  const unsigned n = graph->GetN();
  double relDiff[n];
  for(unsigned i=0; i<n; i++)
    relDiff[i] = (graph->GetFunction("f1")->Eval((graph->GetX())[i]) / (graph->GetY())[i] -1.) * 100.;
  TGraph graphRelDiff(n, graph->GetX(), relDiff);
  graphRelDiff.SetTitle(graph->GetTitle());
  graphRelDiff.GetXaxis()->SetTitle(graph->GetXaxis()->GetTitle());
  graphRelDiff.GetYaxis()->SetTitle("#sigma_{t#bar{t}}^{fit}/#sigma_{t#bar{t}}^{point} -1 (%)");
  graphRelDiff.GetYaxis()->CenterTitle();
  graphRelDiff.Draw("AP");
  //  graphRelDiff.Fit("pol3");
  canvas->Print(printNameBase+".ps");
  canvas->Print(epsLabel.Insert(epsLabel.Index(".eps"), "_relDiffToFitFunc"));
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
    relUncUp->GetXaxis()->SetTitle("m_{t} (GeV)");
  else
    relUncUp->GetXaxis()->SetTitle("m_{t}^{#bar{MS}} (GeV)");
  relUncUp->GetYaxis()->SetTitle("#delta#sigma_{t#bar{t}} / #sigma_{t#bar{t}}");
  relUncUp->GetYaxis()->CenterTitle();
  relUncUp->GetYaxis()->SetRangeUser(.0, .07);
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
  alpha.setVal(0.1184);
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
  TLatex sqrtSText(0.,0.,"#sqrt{s} = 7 TeV");
  sqrtSText.SetNDC();
  sqrtSText.SetTextAlign(23);
  sqrtSText.SetX(0.32);
  sqrtSText.SetY(0.90);
  sqrtSText.SetTextFont(43);
  sqrtSText.SetTextSizePixels(28);
  sqrtSText.Draw();
  char tmpTxt[99];
  sprintf(tmpTxt, "%s = %.1f GeV",
	  mass.getTitle().Data(), mass.getVal());
  TLatex textMass(0.,0.,tmpTxt);
  textMass.SetNDC();
  textMass.SetTextAlign(23);
  textMass.SetX(0.32);
  textMass.SetY(0.84);
  textMass.SetTextFont(43);
  textMass.SetTextSizePixels(28);
  textMass.Draw();
  sprintf(tmpTxt, "%s = %.4f",
	  alpha.getTitle().Data(), alpha.getVal());
  TLatex textAlpha(0.,0.,tmpTxt);
  textAlpha.SetNDC();
  textAlpha.SetTextAlign(23);
  textAlpha.SetX(0.32);
  textAlpha.SetY(0.78);
  textAlpha.SetTextFont(43);
  textAlpha.SetTextSizePixels(28);
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

  const unsigned color[7] = {kRed, kGreen, kRed, kRed, kRed, kRed, kRed};
  const unsigned style[7] = {1, 1, 2, 3, 5, 8, 6};
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
      if(oneTheoryOnly)
	boxAlpha2012.Draw();
      if(!((TString)h2[i]->GetXaxis()->GetTitle()).Contains("bar")) {
	boxMass2012.Draw();
	lineMass2012.Draw();
	textMass2012.Draw();
      }
      if(oneTheoryOnly) {
	lineAlpha2012.Draw();
	textAlpha2012.Draw();
      }
    }
    h2[i]->Draw("cont3 same");
  }
  leg.Draw();
  TLatex text(0.,0., "NNLO+NNLL, #sigma_{t#bar{t}} (7 TeV) = 162 pb");
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

void plotProjectedPDF(const FinalLikeliResults1D* result, RooPlot* frame, const int color, const int fillStyle,
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
  frame->GetYaxis()->SetTitle("Posterior density");
}

TLatex* cmsTxt(const bool targetAlpha)
{
  TString txt = "CMS, #sqrt{s} = 7 TeV, L = 2.3 fb^{-1}; NNLO+NNLL for #sigma_{#lower[-0.2]{t#bar{t}}}; ";
  if(targetAlpha)
    txt += "m_{#kern[0.3]{#lower[-0.1]{t}}} = 173.2 #pm 1.4 GeV";
  else
    txt += "#alpha_{S} (m_{Z}) = 0.1184 #pm 0.0007";
  TLatex* text = new TLatex(0,0,txt);
  text->SetNDC();
  text->SetTextAlign(23);
  text->SetX(0.5);
  text->SetY(1.003);
  text->SetTextFont(43);
  text->SetTextSizePixels(25);
  return text;
}

int foldedLikelihoods(const bool targetAlpha, const bool pole)
{
  if(targetAlpha && !pole) {
    std::cout << "Can't use alpha as target variable in the MSbar scheme here!" << std::endl;
    abort();
  }

  const bool useAlphaUnc = false;

  setTDRStyle();
  gStyle->SetTitleBorderSize(1);
  gStyle->SetOptFit(0011);

  RooAbsReal::defaultIntegratorConfig()->method2D().setLabel("RooSegmentedIntegrator2D");
  RooAbsReal::defaultIntegratorConfig()->getConfigSection("RooIntegrator1D").setCatLabel("sumRule", "Midpoint");
  RooAbsReal::defaultIntegratorConfig()->methodND().setLabel("RooMCIntegrator");

  gSystem->mkdir(figDir);

  TString printNameBase = figDir+"/foldedLikelihoods";
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
    canvas->Print(figDir+"/alpha_s.eps");
    gStyle->SetOptTitle(0);
  }

  TGraph* mShift = 0;
  if(!pole) {
    mShift = getMassShiftGraph();
    mShift->Draw("AP");
    mShift->Fit("pol1", "Q");
    canvas->Print(printNameBase+".ps");
    canvas->Print(figDir+"/MSbar_vs_pole_mass.eps");
  }

//  //////////////////////////////////////
//  /// Start of quick'n dirty
//  //////////////////////////////////////
//
//  TGraph* alphaLambdaGraph = getAlphaLambdaGraph();
//  alphaLambdaGraph->Draw("AC");
//  canvas->Print(printNameBase+".ps");
//  delete alphaLambdaGraph;
//
//  runningAlpha = getRunningAlphaGraph(50, 450);
//  TGraph* runningAlpha_new = getRunningAlphaGraph(50, 450, 0.207, 0.0043);
//
//  runningAlpha->SetFillColor(kMagenta-9);
//  runningAlpha_new->SetFillColor(kCyan);
//  runningAlpha->SetLineStyle(2);
//  runningAlpha_new->SetLineStyle(3);
//
//  TLegend lastMinuteLeg = TLegend(0.4, 0.7, 0.8, 0.9);
//  lastMinuteLeg.SetFillColor(0);
//  lastMinuteLeg.SetBorderSize(0);
//  lastMinuteLeg.AddEntry(runningAlpha    , "PDG 2012"  , "LF");
//  lastMinuteLeg.AddEntry(runningAlpha_new, "CMS-PAS-TOP-12-022", "LF");
//
//  TLine lineMZ(mZ, 0.09, mZ, 0.135);
//  lineMZ.SetLineWidth(3);
//  TLatex textMZ(0.95*mZ, 0.11, "m_{#lower[-0.1]{Z}}");
//  textMZ.SetTextAngle(90);
//  textMZ.SetTextAlign(32);
//  textMZ.SetTextFont(43);
//  textMZ.SetTextSizePixels(33);
//
//  TLine line2Mt(2*173.2, 0.09, 2*173.2, 0.135);
//  line2Mt.SetLineWidth(3);
//  TLatex text2Mt(0.95*2*173.2, 0.11, "2m_{#lower[-0.2]{t}}");
//  text2Mt.SetTextAngle(90);
//  text2Mt.SetTextAlign(32);
//  text2Mt.SetTextFont(43);
//  text2Mt.SetTextSizePixels(33);
//
//  runningAlpha_new->Draw("A3");
//  lineMZ.Draw();
//  textMZ.Draw();
//  line2Mt.Draw();
//  text2Mt.Draw();
//  runningAlpha_new->Draw("3");
//  runningAlpha->Draw("3");
//  runningAlpha->Draw("XC");
//  runningAlpha_new->Draw("XC");
//  gPad->SetLogx();
//  lastMinuteLeg.Draw();
//  gPad->RedrawAxis();
//  runningAlpha_new->GetXaxis()->SetLimits(50, 500);
//  runningAlpha_new->GetXaxis()->SetMoreLogLabels();
//  runningAlpha_new->GetXaxis()->SetNoExponent();
//  runningAlpha_new->GetYaxis()->SetRangeUser(0.09, 0.135);
//  canvas->Print(printNameBase+".ps");
//  canvas->Print(printNameBase+"results_qDep.eps");
//  gPad->SetLogx(false);
//
//  delete runningAlpha_new;
//
////  canvas->Print(printNameBase+".ps]");
////  return 0;
//
//  //////////////////////////////////////
//  /// End of quick'n dirty
//  //////////////////////////////////////

  const unsigned nPdfSets  = 5;
  const unsigned nTheories = 2;

  std::vector<TGraphAsymmErrors*> moc_vec[nPdfSets];
  std::vector<TGraphAsymmErrors*> mit_vec[nPdfSets];
  
  TGraphAsymmErrors* moc[nPdfSets];
  TGraphAsymmErrors* mit[nPdfSets];
  
  std::vector<TF1*> moc_funcs[nPdfSets][4];
  std::vector<TF1*> mit_funcs[nPdfSets][4];

  const TString pdfName [nPdfSets ] = {"MSTW2008", "HERAPDF1.5", "ABM11", "NNPDF2.3", "CT10"};
  const TString theoName[nTheories] = {"HATHOR 1.3", "Top++ 2.0"};

  TString theoTitle[nPdfSets][nTheories];
  for(unsigned h=0; h<nPdfSets; h++)
    for(unsigned i=0; i<nTheories; i++)
      theoTitle[h][i] = theoName[i] + ", " + pdfName[h];

  const TString errName [4] = {"Scale", "Experimental PDF", "#alpha_{S}", "Total"};
  const TString errLabel[4] = {"scale", "expPDF", "alphaS", "total"};

  //  TF1* f1 = new TF1("f1", "[0]+[1]/x+[2]*TMath::Power(x,-2)+[3]*TMath::Power(x,-3)+[4]*TMath::Power(x,-4)", 0, 1000);
  //  TF1* f1 = new TF1("f1", "([0]+[1]*x+[2]*TMath::Power(x,2)+[3]*TMath::Power(x,3))", 0, 1000);
  //  TF1* f1 = new TF1("f1", "([0]+[1]*x+[2]*TMath::Power(x,2)+[3]*TMath::Power(x,3))/TMath::Power(x,5)", 0, 1000);
  //  TF1* f1 = new TF1("f1", "TMath::Power(x, [0])*[1]", 0, 1000);
  //  TF1* f1 = new TF1("f1", "TMath::Power(x, [0]+[2]*x)*[1]", 0, 1000);
  //  TF1* f1 = new TF1("f1", "TMath::Power(x, [0])*TMath::Exp([2]*x)*[1]", 0, 1000);
  //  TF1* f1 = new TF1("f1", "TMath::Power(x, [0])*([1]*x+[2]*x*x+[3]*x*x*x)", 0, 1000);
  //  TF1* f1 = new TF1("f1", "[4]*TMath::Power(x, [0])+([1]*x+[2]*x*x+[3]*x*x*x)", 0, 1000);
  //  TF1* f1 = new TF1("f1", "TMath::Exp([1]*x+[2]*x*x+[3]*x*x*x)*[0]", 0, 1000);
  //  TF1* f1 = new TF1("f1", "[0]+(x-175.)*[1]+[2]*(x-175.)*(x-175.)+[3]*(x-175.)*(x-175.)*(x-175.)", 0, 1000);
  TF1* f1 = new TF1("f1", "([0]+[1]*x+[2]*TMath::Power(x,2)+[3]*TMath::Power(x,3))/TMath::Power(x,4)", 0, 1000);
  f1->SetParNames("a", "b", "c", "d");

  for(unsigned h=0; h<nPdfSets; h++) {
    moc_vec[h] = readTheory("moch"  , pole, useAlphaUnc, (PdfType)h);
    moc[h] = moc_vec[h].at(3);
    moc[h]->Fit(f1, "WQ0");
    for(unsigned j=0; j<4; j++)
      moc_vec[h].at(j)->SetTitle(theoTitle[h][0]);

    if(pole) {
      mit_vec[h] = readTheory("mitov" , pole, useAlphaUnc, (PdfType)h);
      mit[h] = mit_vec[h].at(3);
      mit[h]->Fit(f1, "WQ0");
      for(unsigned j=0; j<4; j++)
	mit_vec[h].at(j)->SetTitle(theoTitle[h][1]);
    }

    gStyle->SetOptTitle(1);

    if(pole) {
      for(unsigned j=0; j<2; j++)
	mit_funcs[h][j] = getAndDrawRelativeUncertainty(mit_vec[h].at(j), canvas, pole, errName[j],
							epsString("relUnc_mitov_"+errLabel[j], pole, (PdfType)h),
							printNameBase, (j==1 || j==2));
      drawTheoryGraph(mit[h], canvas, pole, epsString("mitov", pole, (PdfType)h), printNameBase);
    }
    for(unsigned j=0; j<2; j++)
      moc_funcs[h][j] = getAndDrawRelativeUncertainty(moc_vec[h].at(j), canvas, pole, errName[j],
						      epsString("relUnc_moch_"+errLabel[j], pole, (PdfType)h),
						      printNameBase, (j==1 || j==2));
    drawTheoryGraph(moc[h], canvas, pole, epsString("moch", pole, (PdfType)h), printNameBase);
    
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

  RooRealVar alphaNNPDF_mean("alphaNNPDF_mean", "alphaNNPDF_mean", 0.1173); //arXiv:1110.2483 (based on NNPDF2.1)
  RooRealVar alphaNNPDF_unc ("alphaNNPDF_unc" , "alphaNNPDF_unc" , 0.0007); //arXiv:1110.2483 (based on NNPDF2.1)
  RooRealVar alphaNNPDF_main("alphaNNPDF_main", "alphaNNPDF_main", 0.1190); //here we used the central value of the
                                                                            //scan range as reference for most studies

  RooRealVar alphaCT_mean("alphaCT_mean", "alphaCT_mean", 0.1180);
  RooRealVar alphaCT_unc ("alphaCT_unc" , "alphaCT_unc" , 0.0020);

  std::vector<RooRealVar> defaultAlphas;
  defaultAlphas.push_back(alphaMSTW_mean );
  defaultAlphas.push_back(alphaHERA_mean );
  defaultAlphas.push_back(alphaABM_mean  );
  defaultAlphas.push_back(alphaNNPDF_mean); 
  defaultAlphas.push_back(alphaCT_mean   );

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
  //  RooFormulaVar deltaM("deltaM", "deltaM", "@0-171.5+@1", RooArgSet(mass, shift));
  //  RooFormulaVar deltaM("deltaM", "deltaM", "@0-173.5+@1", RooArgSet(mass, shift));

  RooRealVar p0("p0", "p0", 1.);
  RooRealVar p1("p1", "p1", -0.008);
  RooRealVar p2("p2", "p2", -0.000137);
  RooPolyVar measXSecMassDepRel("measXSecMassDepRel", "measXSecMassDepRel", deltaM, RooArgSet(p0, p1, p2));
  RooRealVar measXSec("measXSec", "measXSec", 161.9, "pb");
  RooRealVar measXSecErr("measXSecErr", "measXSecErr", 6.725, "pb");

  RooFormulaVar measXSecMassDep("measXSecMassDep", "measXSecMassDep", "@0*@1",
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

  PredXSec* predXSec[nPdfSets][nTheories];

  std::vector<const RooFormulaVar*> predXSecFormularVec;
  std::vector<TString> predXSecFormularVecLabels;

  for(unsigned h=0; h<nPdfSets; h++) {
    alpha.setVal(defaultAlphas.at(h).getVal());

    TString alphaFileName = (pole ? "pole_" : "msbar_");
    TString suf = "PredXSec";

    switch(h) {
    case kMSTW : alphaFileName += "mstw" ; suf += "MSTW" ; break;
    case kHERA : alphaFileName += "hera" ; suf += "HERA" ; break;
    case kABM  : alphaFileName += "abm"  ; suf += "ABM"  ; break;
    case kNNPDF: alphaFileName += "nnpdf"; suf += "NNPDF"; break;
    case kCT   : alphaFileName += "ct"   ; suf += "CT"   ; break;
    }

    TString alphaFileNameMit = "theories_7TeV/mitov_"+alphaFileName+"_alphaDep.root";
    TString alphaFileNameMoc = "theories_7TeV/moch_" +alphaFileName;
    if(!moch_highE)
      alphaFileNameMoc += "_off";
    alphaFileNameMoc += "_alphaDep.root";

    TFile* mitAlphaFile;
    TFile* mocAlphaFile;
    
    if(pole) {
      mitAlphaFile = new TFile(alphaFileNameMit, "READ");    
      predXSec[h][1] = new PredXSec("mit"+suf, xsec, mass, alpha, mit[h]->GetFunction("f1"), mit_funcs[h],
				    mitAlphaFile, (h==kNNPDF ? alphaNNPDF_main : defaultAlphas.at(h)));
      mitAlphaFile->Close();
      delete mitAlphaFile;

      drawConvolution(predXSec[h][1], xsec, mass, alpha, theoTitle[h][1], canvas, printNameBase,
		      epsString("convolution_mitov", pole, (PdfType)h));

      predXSecFormularVec.push_back(&predXSec[h][1]->xsec);
      predXSecFormularVecLabels.push_back(theoTitle[h][1]);
    }
    mocAlphaFile = new TFile(alphaFileNameMoc, "READ");
    predXSec[h][0] = new PredXSec("moc"+suf, xsec, mass, alpha, moc[h]->GetFunction("f1"), moc_funcs[h],
				  mocAlphaFile, (h==kNNPDF ? alphaNNPDF_main : defaultAlphas.at(h)));
    mocAlphaFile->Close();
    delete mocAlphaFile;

    drawConvolution(predXSec[h][0], xsec, mass, alpha, theoTitle[h][0], canvas, printNameBase,
		    epsString("convolution_moch", pole, (PdfType)h));

    if(h==0 || !pole) {
      predXSecFormularVec.push_back(&predXSec[h][0]->xsec);
      predXSecFormularVecLabels.push_back(theoTitle[h][0]);
    }
  }
  drawAlphaVsMass(predXSecFormularVec, predXSecFormularVecLabels, canvas, printNameBase, true);
  drawAlphaVsMass(predXSecFormularVec, predXSecFormularVecLabels, canvas, printNameBase);

  //  canvas->Print(printNameBase+".ps]");
  //  return 0;

  mass.setVal(mass_mean.getVal());

  gStyle->SetEndErrorSize(5*gStyle->GetEndErrorSize());

  TLatex sqrtSText(0.,0.,"#sqrt{s} = 7 TeV");
  sqrtSText.SetNDC();
  sqrtSText.SetTextAlign(23);
  sqrtSText.SetX(0.80);
  sqrtSText.SetY(0.88);
  sqrtSText.SetTextFont(43);
  sqrtSText.SetTextSizePixels(28);

  TGraph relChangeAlphaPredXSecNNPDF = getRelChangePredXSec(predXSec[kNNPDF][1], alpha);
  TGraph relChangeAlphaPredXSecCT    = getRelChangePredXSec(predXSec[kCT   ][1], alpha);
  TGraph relChangeAlphaPredXSecMSTW  = getRelChangePredXSec(predXSec[kMSTW ][1], alpha);
  TGraph relChangeAlphaPredXSecHERA  = getRelChangePredXSec(predXSec[kHERA ][1], alpha);
  TGraph relChangeAlphaPredXSecABM   = getRelChangePredXSec(predXSec[kABM  ][1], alpha);
  relChangeAlphaPredXSecCT   .SetLineColor(kGreen);
  relChangeAlphaPredXSecMSTW .SetLineColor(kRed);
  relChangeAlphaPredXSecHERA .SetLineColor(kMagenta);
  relChangeAlphaPredXSecABM  .SetLineColor(kBlue);
  relChangeAlphaPredXSecNNPDF.GetYaxis()->SetRangeUser(0.65, 1.35);
  relChangeAlphaPredXSecNNPDF.GetYaxis()->SetTitle("#sigma_{t #bar{t}} (#alpha_{S} (m_{Z})) / #sigma_{t #bar{t}} (#alpha_{S} (m_{Z}) = 0.118)");
  relChangeAlphaPredXSecNNPDF.GetXaxis()->SetTitle("#alpha_{S} (m_{Z})");
  relChangeAlphaPredXSecNNPDF.GetXaxis()->SetNdivisions(505);
  relChangeAlphaPredXSecNNPDF.Draw("AC");
  relChangeAlphaPredXSecCT   .Draw("C");
  relChangeAlphaPredXSecMSTW .Draw("C");
  relChangeAlphaPredXSecHERA .Draw("C");
  relChangeAlphaPredXSecABM  .Draw("C");

  TLegend legRelChangeAlphaPredXSec = TLegend(0.2, 0.6, 0.5, 0.9);
  legRelChangeAlphaPredXSec.SetFillStyle(0);
  legRelChangeAlphaPredXSec.SetBorderSize(0);
  legRelChangeAlphaPredXSec.AddEntry(&relChangeAlphaPredXSecABM  , "ABM"  , "L");
  legRelChangeAlphaPredXSec.AddEntry(&relChangeAlphaPredXSecCT   , "CT"   , "L");
  legRelChangeAlphaPredXSec.AddEntry(&relChangeAlphaPredXSecHERA , "HERA" , "L");
  legRelChangeAlphaPredXSec.AddEntry(&relChangeAlphaPredXSecMSTW , "MSTW" , "L");
  legRelChangeAlphaPredXSec.AddEntry(&relChangeAlphaPredXSecNNPDF, "NNPDF", "L");

  legRelChangeAlphaPredXSec.Draw();

  canvas->Print(printNameBase+".ps");
  canvas->Print(printNameBase+"_relChangePredXSec_alpha.eps");

  TGraph relChangeMassPredXSecNNPDF = getRelChangePredXSec(predXSec[kNNPDF][1], mass);
  TGraph relChangeMassPredXSecCT    = getRelChangePredXSec(predXSec[kCT   ][1], mass);
  TGraph relChangeMassPredXSecMSTW  = getRelChangePredXSec(predXSec[kMSTW ][1], mass);
  TGraph relChangeMassPredXSecHERA  = getRelChangePredXSec(predXSec[kHERA ][1], mass);
  TGraph relChangeMassPredXSecABM   = getRelChangePredXSec(predXSec[kABM  ][1], mass);
  relChangeMassPredXSecCT   .SetLineColor(kGreen);
  relChangeMassPredXSecMSTW .SetLineColor(kRed);
  relChangeMassPredXSecHERA .SetLineColor(kMagenta);
  relChangeMassPredXSecABM  .SetLineColor(kBlue);
  relChangeMassPredXSecNNPDF.GetYaxis()->SetRangeUser(0.7, 1.4);
  relChangeMassPredXSecNNPDF.GetYaxis()->SetTitle("#sigma_{t #bar{t}} (m_{t}) / #sigma_{t #bar{t}} (m_{t} = 173)");
  relChangeMassPredXSecNNPDF.GetXaxis()->SetTitle("m_{t} (GeV)");
  relChangeMassPredXSecNNPDF.Draw("AC");
  relChangeMassPredXSecCT   .Draw("C");
  relChangeMassPredXSecMSTW .Draw("C");
  relChangeMassPredXSecHERA .Draw("C");
  relChangeMassPredXSecABM  .Draw("C");

  legRelChangeAlphaPredXSec.SetX1NDC(0.6);
  legRelChangeAlphaPredXSec.SetX2NDC(0.9);
  legRelChangeAlphaPredXSec.Draw();

  canvas->Print(printNameBase+".ps");
  canvas->Print(printNameBase+"_relChangePredXSec_mass.eps");

  //  canvas->Print(printNameBase+".ps]");
  //  return 0;

  TBox boxAlpha2012(alpha2012_mean.getVal()-alpha2012_unc.getVal(), 115.,
		    alpha2012_mean.getVal()+alpha2012_unc.getVal(), 235.);
  boxAlpha2012.SetFillColor(kMagenta-9);
  boxAlpha2012.SetFillStyle(3007);
  TLine lineAlpha2012(alpha2012_mean.getVal(), 115.,
		      alpha2012_mean.getVal(), 235.);
  lineAlpha2012.SetLineStyle(2);
  TLine lineAlpha2012_left(alpha2012_mean.getVal()-alpha2012_unc.getVal(), 115.,
			   alpha2012_mean.getVal()-alpha2012_unc.getVal(), 235.);
  TLine lineAlpha2012_right(alpha2012_mean.getVal()+alpha2012_unc.getVal(), 115.,
			    alpha2012_mean.getVal()+alpha2012_unc.getVal(), 235.);
  lineAlpha2012_left .SetLineColor(kMagenta-9);
  lineAlpha2012_right.SetLineColor(kMagenta-9);
  TText textAlpha2012_left(alpha2012_mean.getVal()-0.5*alpha2012_unc.getVal(), 135., "PDG");
  textAlpha2012_left.SetTextAngle(90);
  textAlpha2012_left.SetTextAlign(32);
  textAlpha2012_left.SetTextFont(43);
  textAlpha2012_left.SetTextSizePixels(23);
  TText textAlpha2012_right(alpha2012_mean.getVal()+0.5*alpha2012_unc.getVal(), 135., "2012");
  textAlpha2012_right.SetTextAngle(90);
  textAlpha2012_right.SetTextAlign(32);
  textAlpha2012_right.SetTextFont(43);
  textAlpha2012_right.SetTextSizePixels(23);

  if(pole) {

  TGraphErrors measXSecWithErrAlpha = getMeasXSecWithErr(measXSecMassDep, measXSecMassDepErr, alpha, 0.10, 0.13, 30);

  TGraphAsymmErrors predXSecAlphaMitNNPDF = getPredXSecWithErr(predXSec[kNNPDF][1], alpha, 0.10, 0.13, 30);

  TGraphAsymmErrors predXSecDefAlphaMitNNPDF = getPredXSecWithErr(predXSec[kNNPDF][1], alpha,
								  alphaNNPDF_mean.getVal(), alphaNNPDF_mean.getVal(),
								  1, alphaNNPDF_unc.getVal());
  predXSecDefAlphaMitNNPDF.SetLineColor(kRed);
  predXSecDefAlphaMitNNPDF.SetMarkerSize(2);
  predXSecDefAlphaMitNNPDF.SetMarkerStyle(22);

  TGraphAsymmErrors predXSecDefAlphaMocNNPDF = getPredXSecWithErr(predXSec[kNNPDF][0], alpha,
								  alphaNNPDF_mean.getVal(), alphaNNPDF_mean.getVal(),
								  1, alphaNNPDF_unc.getVal());
  predXSecDefAlphaMocNNPDF.SetLineColor(kGreen);
  predXSecDefAlphaMocNNPDF.SetMarkerSize(2);
  predXSecDefAlphaMocNNPDF.SetMarkerStyle(23);

  TGraphAsymmErrors predXSecDefAlphaMitMSTW = getPredXSecWithErr(predXSec[kMSTW][1], alpha,
								 alphaMSTW_mean.getVal(), alphaMSTW_mean.getVal(),
								 1, alphaMSTW_unc.getVal());
  predXSecDefAlphaMitMSTW.SetLineColor(kRed);
  predXSecDefAlphaMitMSTW.SetMarkerSize(2);
  predXSecDefAlphaMitMSTW.SetMarkerStyle(21);

  TGraphAsymmErrors predXSecDefAlphaMitHERA = getPredXSecWithErr(predXSec[kHERA][1], alpha,
								 alphaHERA_mean.getVal(), alphaHERA_mean.getVal(),
								 1, alphaHERA_unc.getVal());
  predXSecDefAlphaMitHERA.SetLineColor(kRed);
  predXSecDefAlphaMitHERA.SetMarkerSize(3);
  predXSecDefAlphaMitHERA.SetMarkerStyle(29);

  TGraphAsymmErrors predXSecDefAlphaMitABM = getPredXSecWithErr(predXSec[kABM][1], alpha,
								alphaABM_mean.getVal(), alphaABM_mean.getVal(),
								1, alphaABM_unc.getVal());
  predXSecDefAlphaMitABM.SetLineColor(kRed);
  predXSecDefAlphaMitABM.SetMarkerSize(2.5);
  predXSecDefAlphaMitABM.SetMarkerStyle(34);

  TGraphAsymmErrors predXSecDefAlphaMitCT = getPredXSecWithErr(predXSec[kCT][1], alpha,
							       alphaCT_mean.getVal(), alphaCT_mean.getVal(),
							       1, alphaCT_unc.getVal());
  predXSecDefAlphaMitCT.SetLineColor(kRed);
  predXSecDefAlphaMitCT.SetMarkerSize(2.0);
  predXSecDefAlphaMitCT.SetMarkerStyle(20);

  RooPlot* frame_alpha = alpha.frame(RooFit::Range(0.108, 0.122));
  frame_alpha->addObject(&boxAlpha2012);
  frame_alpha->addObject(&lineAlpha2012);
  frame_alpha->addObject(&lineAlpha2012_left);
  frame_alpha->addObject(&lineAlpha2012_right);
  frame_alpha->addObject(&textAlpha2012_left);
  frame_alpha->addObject(&textAlpha2012_right);
  frame_alpha->addObject(&measXSecWithErrAlpha, "3");
  frame_alpha->addObject(&measXSecWithErrAlpha, "CX");
  frame_alpha->addObject(&predXSecAlphaMitNNPDF, "3");
  predXSecAlphaMitNNPDF.SetFillColor(kRed-9);
  //  predXSecAlphaMitNNPDF.SetFillStyle(3244);
  predXSec[3][1]->xsec.plotOn(frame_alpha, RooFit::LineColor(kRed));
  frame_alpha->addObject(&predXSecDefAlphaMitNNPDF, "PE");
  frame_alpha->GetYaxis()->SetTitle("#sigma_{t#bar{t}} (pb)");
  frame_alpha->SetMaximum(235.);
  frame_alpha->SetMinimum(115.);
  frame_alpha->Draw();
  measXSecWithErrAlpha.SetFillColor(kBlue-10);
  measXSecWithErrAlpha.SetLineColor(kBlue+1);
  TLegend legAlphaDep = TLegend(0.18, 0.81, 0.6, 0.92);
  legAlphaDep.SetFillStyle(0);
  legAlphaDep.SetBorderSize(0);
  legAlphaDep.AddEntry(&measXSecWithErrAlpha, "CMS, L = 2.3 fb^{-1}", "FL");
  frame_alpha->getAttMarker(predXSec[3][1]->xsec.GetName()+(TString)"_Norm[alpha]")->SetMarkerStyle(22);
  frame_alpha->getAttMarker(predXSec[3][1]->xsec.GetName()+(TString)"_Norm[alpha]")->SetMarkerSize(2);
  frame_alpha->getAttFill(predXSec[3][1]->xsec.GetName()+(TString)"_Norm[alpha]")->SetFillColor(kRed-9);
  legAlphaDep.AddEntry(frame_alpha->findObject(predXSec[3][1]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[3][1], "FLP");
  legAlphaDep.Draw();
  char massTxt[99];
  sprintf(massTxt, "%s = %.1f GeV", mass.getTitle().Data(), mass.getVal());
  TLatex massText(0.,0.,massTxt);
  massText.SetNDC();
  massText.SetTextAlign(23);
  massText.SetX(0.80);
  massText.SetY(0.82);
  massText.SetTextFont(43);
  massText.SetTextSizePixels(28);
  massText.Draw();
  sqrtSText.Draw();
  canvas->Print(printNameBase+".ps");
  canvas->Print(printNameBase+"_xsec_vs_alpha_nnpdfOnly.eps");
//  if(!topppOnly) {
//    predXSec[3][0]->xsec.plotOn(frame_alpha, RooFit::LineColor(kGreen));
//    frame_alpha->addObject(&predXSecDefAlphaMocNNPDF, "PE");
//    frame_alpha->SetMaximum(235.);
//    frame_alpha->SetMinimum(115.);
//    frame_alpha->Draw();
//    frame_alpha->getAttMarker(predXSec[3][0]->xsec.GetName()+(TString)"_Norm[alpha]")->SetMarkerStyle(23);
//    frame_alpha->getAttMarker(predXSec[3][0]->xsec.GetName()+(TString)"_Norm[alpha]")->SetMarkerSize(2);
//    legAlphaDep.AddEntry(frame_alpha->findObject(predXSec[3][0]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[3][0], "LP");
//    legAlphaDep.SetY1NDC(0.75);
//    legAlphaDep.Draw();
//    massText.Draw();
//    canvas->Print(printNameBase+".ps");
//    canvas->Print(printNameBase+"_xsec_vs_alpha_pre2.eps");
//  }
  predXSec[0][1]->xsec.plotOn(frame_alpha, RooFit::LineColor(kRed), RooFit::LineStyle(2));
  predXSec[1][1]->xsec.plotOn(frame_alpha, RooFit::LineColor(kRed), RooFit::LineStyle(3));
  predXSec[2][1]->xsec.plotOn(frame_alpha, RooFit::LineColor(kRed), RooFit::LineStyle(5));
  predXSec[4][1]->xsec.plotOn(frame_alpha, RooFit::LineColor(kRed), RooFit::LineStyle(8));
  frame_alpha->addObject(&predXSecDefAlphaMitMSTW , "PE");
  frame_alpha->addObject(&predXSecDefAlphaMitHERA , "PE");
  frame_alpha->addObject(&predXSecDefAlphaMitABM  , "PE");
  frame_alpha->addObject(&predXSecDefAlphaMitCT   , "PE");
  frame_alpha->SetMaximum(235.);
  frame_alpha->SetMinimum(115.);
  frame_alpha->Draw();
  frame_alpha->getAttMarker(predXSec[0][1]->xsec.GetName()+(TString)"_Norm[alpha]")->SetMarkerStyle(21);
  frame_alpha->getAttMarker(predXSec[0][1]->xsec.GetName()+(TString)"_Norm[alpha]")->SetMarkerSize(2);
  frame_alpha->getAttMarker(predXSec[1][1]->xsec.GetName()+(TString)"_Norm[alpha]")->SetMarkerStyle(29);
  frame_alpha->getAttMarker(predXSec[1][1]->xsec.GetName()+(TString)"_Norm[alpha]")->SetMarkerSize(3);
  frame_alpha->getAttMarker(predXSec[2][1]->xsec.GetName()+(TString)"_Norm[alpha]")->SetMarkerStyle(34);
  frame_alpha->getAttMarker(predXSec[2][1]->xsec.GetName()+(TString)"_Norm[alpha]")->SetMarkerSize(2.5);
  frame_alpha->getAttMarker(predXSec[4][1]->xsec.GetName()+(TString)"_Norm[alpha]")->SetMarkerStyle(20);
  frame_alpha->getAttMarker(predXSec[4][1]->xsec.GetName()+(TString)"_Norm[alpha]")->SetMarkerSize(2.0);
  legAlphaDep.Clear();
  legAlphaDep.AddEntry(&measXSecWithErrAlpha, "CMS, L = 2.3 fb^{-1}", "FL");
  legAlphaDep.AddEntry(frame_alpha->findObject(predXSec[2][1]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[2][1], "LP");
  legAlphaDep.AddEntry(frame_alpha->findObject(predXSec[4][1]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[4][1], "LP");
  legAlphaDep.AddEntry(frame_alpha->findObject(predXSec[1][1]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[1][1], "LP");
  legAlphaDep.AddEntry(frame_alpha->findObject(predXSec[0][1]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[0][1], "LP");
  legAlphaDep.AddEntry(frame_alpha->findObject(predXSec[3][1]->xsec.GetName()+(TString)"_Norm[alpha]"), theoTitle[3][1], "FLP");
  legAlphaDep.SetY1NDC(0.54);
  legAlphaDep.Draw();
  TLatex headerXSecVsAlpha(0.,0.,"#sqrt{s} = 7 TeV; m_{#kern[0.5]{#lower[-0.3]{t}}} = 173.2 GeV");
  headerXSecVsAlpha.SetNDC();
  headerXSecVsAlpha.SetTextAlign(11);
  headerXSecVsAlpha.SetX(gPad->GetLeftMargin());
  headerXSecVsAlpha.SetY(0.96);
  headerXSecVsAlpha.SetTextFont(43);
  headerXSecVsAlpha.SetTextSizePixels(25);
  headerXSecVsAlpha.Draw();
  //  massText.Draw();
  //  sqrtSText.Draw();

  canvas->Print(printNameBase+".ps");
  canvas->Print(printNameBase+"_xsec_vs_alpha.eps");

  }

  TGraphErrors measXSecWithErrMass = getMeasXSecWithErr(measXSecMassDep, measXSecMassDepErr, mass, 130., 220., 90);

  alpha.setVal(alpha2012_mean.getVal());
  char alphaTxt[99];
  sprintf(alphaTxt, "%s = %.4f", alpha.getTitle().Data(), alpha.getVal());
  TLatex alphaText(0.,0.,alphaTxt);
  alphaText.SetNDC();
  alphaText.SetTextAlign(23);
  alphaText.SetX(0.32);
  alphaText.SetY(0.24);
  alphaText.SetTextFont(43);
  alphaText.SetTextSizePixels(28);

  sqrtSText.SetX(0.32);
  sqrtSText.SetY(0.30);

  TGraphAsymmErrors predXSecMassMitNNPDF = getPredXSecWithErr(predXSec[kNNPDF][1], mass, 130., 220., 90);

  RooPlot* frame_mass;
  if(pole)
    frame_mass = mass.frame(165., 190.);
  else
    frame_mass = mass.frame(155., 185.);
  TBox boxMass2012(mass_mean.getVal()-mass_unc.getVal(), 115.,
		   mass_mean.getVal()+mass_unc.getVal(), 235.);
  boxMass2012.SetFillColor(kMagenta-9);
  boxMass2012.SetFillStyle(3007);
  TLine lineMass2012(mass_mean.getVal(), 115.,
		     mass_mean.getVal(), 235.);
  lineMass2012.SetLineStyle(2);
  TLine lineMass2012_left(mass_mean.getVal()-mass_unc.getVal(), 115.,
			  mass_mean.getVal()-mass_unc.getVal(), 235.);
  TLine lineMass2012_right(mass_mean.getVal()+mass_unc.getVal(), 115.,
			   mass_mean.getVal()+mass_unc.getVal(), 235.);
  lineMass2012_left .SetLineColor(kMagenta-9);
  lineMass2012_right.SetLineColor(kMagenta-9);
  TText textMass2012_left(mass_mean.getVal()-0.5*mass_unc.getVal(), 140., "Tevatron");
  textMass2012_left.SetTextAngle(90);
  textMass2012_left.SetTextAlign(32);
  textMass2012_left.SetTextFont(43);
  textMass2012_left.SetTextSizePixels(23);
  TText textMass2012_right(mass_mean.getVal()+0.5*mass_unc.getVal(), 140., "2012");
  textMass2012_right.SetTextAngle(90);
  textMass2012_right.SetTextAlign(32);
  textMass2012_right.SetTextFont(43);
  textMass2012_right.SetTextSizePixels(23);

  frame_mass->addObject(&boxMass2012);
  frame_mass->addObject(&lineMass2012);
  frame_mass->addObject(&lineMass2012_left);
  frame_mass->addObject(&lineMass2012_right);
  frame_mass->addObject(&textMass2012_left);
  frame_mass->addObject(&textMass2012_right);
  frame_mass->addObject(&measXSecWithErrMass, "3");
  frame_mass->addObject(&measXSecWithErrMass, "CX");
  measXSecWithErrMass.SetFillColor(kBlue-10);
  measXSecWithErrMass.SetLineColor(kBlue+1);
  frame_mass->addObject(&predXSecMassMitNNPDF, "3");
  frame_mass->addObject(&predXSecMassMitNNPDF, "CX");
  predXSecMassMitNNPDF.SetFillColor(kRed-9);
  //  predXSecMassMitNNPDF.SetFillStyle(3244);
  predXSecMassMitNNPDF.SetLineColor(kRed+1);
  if(pole) {
    predXSec[3][1]->xsec.plotOn(frame_mass, RooFit::LineColor(kRed));
    if(!topppOnly)
      predXSec[3][0]->xsec.plotOn(frame_mass, RooFit::LineColor(kGreen));
  }
  else
    predXSec[3][0]->xsec.plotOn(frame_mass, RooFit::LineColor(kRed));
  predXSec[0][pole]->xsec.plotOn(frame_mass, RooFit::LineColor(kRed), RooFit::LineStyle(2));
  predXSec[1][pole]->xsec.plotOn(frame_mass, RooFit::LineColor(kRed), RooFit::LineStyle(3));
  predXSec[2][pole]->xsec.plotOn(frame_mass, RooFit::LineColor(kRed), RooFit::LineStyle(5));
  predXSec[4][pole]->xsec.plotOn(frame_mass, RooFit::LineColor(kRed), RooFit::LineStyle(8));
  frame_mass->GetYaxis()->SetTitle("#sigma_{t#bar{t}} (pb)");
  frame_mass->SetMaximum(235.);
  frame_mass->SetMinimum(115.);
  frame_mass->Draw();
  TLatex headerXSecVsMass(0.,0.,"#sqrt{s} = 7 TeV; #alpha_{#lower[-0.1]{S}}#lower[-0.1]{(}m_{#lower[-0.1]{Z}}#lower[-0.1]{)} = 0.1184");
  headerXSecVsMass.SetNDC();
  headerXSecVsMass.SetTextAlign(11);
  headerXSecVsMass.SetX(gPad->GetLeftMargin());
  headerXSecVsMass.SetY(0.96);
  headerXSecVsMass.SetTextFont(43);
  headerXSecVsMass.SetTextSizePixels(25);
  headerXSecVsMass.Draw();
  //  alphaText.Draw();
  //  sqrtSText.Draw();
  TLegend legMassDep = TLegend(0.50, 0.54, 0.92, 0.92);
  legMassDep.SetFillStyle(0);
  legMassDep.SetBorderSize(0);
  legMassDep.AddEntry(&measXSecWithErrMass, "CMS, L = 2.3 fb^{-1}", "FL");
  legMassDep.AddEntry(frame_mass->findObject(predXSec[2][pole]->xsec.GetName()+(TString)"_Norm[mass]"), theoTitle[2][pole], "L");
  legMassDep.AddEntry(frame_mass->findObject(predXSec[4][pole]->xsec.GetName()+(TString)"_Norm[mass]"), theoTitle[4][pole], "L");
  legMassDep.AddEntry(frame_mass->findObject(predXSec[1][pole]->xsec.GetName()+(TString)"_Norm[mass]"), theoTitle[1][pole], "L");
  legMassDep.AddEntry(frame_mass->findObject(predXSec[0][pole]->xsec.GetName()+(TString)"_Norm[mass]"), theoTitle[0][pole], "L");
  if(pole)
    legMassDep.AddEntry(&predXSecMassMitNNPDF, theoTitle[3][1], "FL");
  if(!topppOnly)
    legMassDep.AddEntry(frame_mass->findObject(predXSec[3][0]->xsec.GetName()+(TString)"_Norm[mass]"), theoTitle[3][0], "L");
  legMassDep.Draw();
  canvas->Print(printNameBase+".ps");
  canvas->Print(printNameBase+"_xsec_vs_mass.eps");

  canvas->Print(printNameBase+".ps]");
  return 0;

  FinalLikeliResults1D* mocResult[nPdfSets];
  FinalLikeliResults1D* mitResult[nPdfSets];

  for(unsigned h=0; h<nPdfSets; h++) {
    //  for(unsigned h=3; h<4; h++) {
    const TString suf[nPdfSets] = {"MSTW", "HERA", "ABM", "NNPDF", "CT"};

    if(targetAlpha) {
      if(!topppOnly)
	mocResult[h] = new FinalLikeliResults1D("mocResult"+suf[h], measXSec, xsec, alpha,
						RooArgList(measXSecPDF,predXSec[h][0]->prob), mass, mass_mean, mass_unc);
      mitResult[h] = new FinalLikeliResults1D("mitResult"+suf[h], measXSec, xsec, alpha,
					      RooArgList(measXSecPDF,predXSec[h][1]->prob), mass, mass_mean, mass_unc);
    }
    else {
      if(!topppOnly)
	mocResult[h] = new FinalLikeliResults1D("mocResult"+suf[h], measXSec, xsec, mass,
						RooArgList(measXSecPDF,predXSec[h][0]->prob),
						alpha, alpha2012_mean, alpha2012_unc);
      if(pole)
	mitResult[h] = new FinalLikeliResults1D("mitResult"+suf[h], measXSec, xsec, mass,
						RooArgList(measXSecPDF,predXSec[h][1]->prob),
						alpha, alpha2012_mean, alpha2012_unc);
      //alpha, alphaABM_mean, alphaABM_unc);
    }
  }

//  if(pole) {
//    char tmpTxt[99];
//    if(topppOnly) {
//      TString format = (targetAlpha ?
//			"%s &  %.4f & ${}^{+%.4f}_{-%.4f}$ & ${}^{+%.4f}_{-%.4f}$ & ${}^{+%.4f}_{-%.4f}$\\\\" :
//			"%s &  %.1f & ${}^{+%.1f}_{-%.1f}$ & ${}^{+%.1f}_{-%.1f}$ & ${}^{+%.1f}_{-%.1f}$\\\\");
//      sprintf(tmpTxt, format, pdfName[kNNPDF].Data(),
//	      mitResult[kNNPDF]->bestX,
//	      mitResult[kNNPDF]->highErrTotal,
//	      mitResult[kNNPDF]->lowErrTotal,
//	      mitResult[kNNPDF]->highErrFromConstraintUncertainty,
//	      mitResult[kNNPDF]->lowErrFromConstraintUncertainty,
//	      mitResult[kNNPDF]->highErrFromBeamUncertainty,
//	      mitResult[kNNPDF]->lowErrFromBeamUncertainty);
//      std::cout << tmpTxt << std::endl;
//    }
//  }
//  canvas->Print(printNameBase+".ps]");
//  return 0;

  const unsigned nSummaryPoints = nPdfSets*nTheories;
  TGraphAsymmErrors mocSummaryGraphInnErr(nPdfSets);
  TGraphAsymmErrors mocSummaryGraphTotErr(nPdfSets);
  TGraphAsymmErrors mitSummaryGraphInnErr(nPdfSets);
  TGraphAsymmErrors mitSummaryGraphTotErr(nPdfSets);

  if(!topppOnly) {
    mocResult[kABM  ]->addPointToGraphs(mocSummaryGraphInnErr, mocSummaryGraphTotErr, 4, 2*4+0.2);
    mocResult[kCT   ]->addPointToGraphs(mocSummaryGraphInnErr, mocSummaryGraphTotErr, 3, 2*3+0.2);
    mocResult[kHERA ]->addPointToGraphs(mocSummaryGraphInnErr, mocSummaryGraphTotErr, 2, 2*2+0.2);
    mocResult[kMSTW ]->addPointToGraphs(mocSummaryGraphInnErr, mocSummaryGraphTotErr, 1, 2*1+0.2);
    mocResult[kNNPDF]->addPointToGraphs(mocSummaryGraphInnErr, mocSummaryGraphTotErr, 0, 2*0+0.2);
  }

  if(pole) {
    const double yOffSet = (topppOnly ? 0.5 : 0.8);
    mitResult[kABM  ]->addPointToGraphs(mitSummaryGraphInnErr, mitSummaryGraphTotErr, 4, 2*4+yOffSet);
    mitResult[kCT   ]->addPointToGraphs(mitSummaryGraphInnErr, mitSummaryGraphTotErr, 3, 2*3+yOffSet);
    mitResult[kHERA ]->addPointToGraphs(mitSummaryGraphInnErr, mitSummaryGraphTotErr, 2, 2*2+yOffSet);
    mitResult[kMSTW ]->addPointToGraphs(mitSummaryGraphInnErr, mitSummaryGraphTotErr, 1, 2*1+yOffSet);
    mitResult[kNNPDF]->addPointToGraphs(mitSummaryGraphInnErr, mitSummaryGraphTotErr, 0, 2*0+yOffSet);
  }

  if(targetAlpha) {
    mitSummaryGraphTotErr.GetXaxis()->SetLimits(0.108, 0.122);
    mocSummaryGraphTotErr.GetXaxis()->SetLimits(0.1095, 0.1255);
    mitSummaryGraphTotErr.GetXaxis()->SetTitle(alpha.getTitle());
    mocSummaryGraphTotErr.GetXaxis()->SetTitle(alpha.getTitle());
  }
  else {
    if(pole) {
      mitSummaryGraphTotErr.GetXaxis()->SetLimits(166., 185.);
      mocSummaryGraphTotErr.GetXaxis()->SetLimits(163., 185.);
    }
    else
      mocSummaryGraphTotErr.GetXaxis()->SetLimits(155., 180.);
    mitSummaryGraphTotErr.GetXaxis()->SetTitle(mass.getTitle(true));
    mocSummaryGraphTotErr.GetXaxis()->SetTitle(mass.getTitle(true));
  }

  mitSummaryGraphTotErr.GetYaxis()->SetRangeUser(-1, nSummaryPoints+3);
  mocSummaryGraphTotErr.GetYaxis()->SetRangeUser(-1, nSummaryPoints+3);
  mitSummaryGraphTotErr.GetYaxis()->SetNdivisions(0);
  mocSummaryGraphTotErr.GetYaxis()->SetNdivisions(0);

  mocSummaryGraphTotErr.SetMarkerSize(2);
  mitSummaryGraphTotErr.SetMarkerSize(2);
  mocSummaryGraphTotErr.SetMarkerStyle(22);
  mitSummaryGraphTotErr.SetMarkerStyle(23);

  boxMass2012.SetY1(-1);
  lineMass2012.SetY1(-1);
  lineMass2012_left.SetY1(-1);
  lineMass2012_right.SetY1(-1);
  boxMass2012.SetY2(nSummaryPoints+3);
  lineMass2012.SetY2(nSummaryPoints+3);
  lineMass2012_left.SetY2(nSummaryPoints+3);
  lineMass2012_right.SetY2(nSummaryPoints+3);
  textMass2012_left.SetY((nSummaryPoints+3)*0.95);
  textMass2012_right.SetY((nSummaryPoints+3)*0.95);

  boxAlpha2012.SetY1(-1);
  lineAlpha2012.SetY1(-1);
  lineAlpha2012_left.SetY1(-1);
  lineAlpha2012_right.SetY1(-1);
  boxAlpha2012.SetY2(nSummaryPoints+3);
  lineAlpha2012.SetY2(nSummaryPoints+3);
  lineAlpha2012_left.SetY2(nSummaryPoints+3);
  lineAlpha2012_right.SetY2(nSummaryPoints+3);
  textAlpha2012_left.SetY((nSummaryPoints+3)*0.95);
  textAlpha2012_right.SetY((nSummaryPoints+3)*0.95);

  const double xLeftTextPdfSet[2] = {166.5, 0.1085};

  TBox boxAlphaABM(alphaABM_mean.getVal()-alphaABM_unc.getVal(), 7.9,
		   alphaABM_mean.getVal()+alphaABM_unc.getVal(), 9.1);
  boxAlphaABM.SetFillColor(kGreen-9);
  TLine lineAlphaABM(alphaABM_mean.getVal(), 7.9,
		     alphaABM_mean.getVal(), 9.1);
  lineAlphaABM.SetLineStyle(3);
  TText textABM(xLeftTextPdfSet[targetAlpha], 8.5, "ABM11");
  textABM.SetTextFont(43);
  textABM.SetTextSizePixels(26);
  textABM.SetTextAlign(12);

  TBox boxAlphaCT(alphaCT_mean.getVal()-alphaCT_unc.getVal(), 5.9,
		  alphaCT_mean.getVal()+alphaCT_unc.getVal(), 7.1);
  boxAlphaCT.SetFillColor(kGreen-9);
  TLine lineAlphaCT(alphaCT_mean.getVal(), 5.9,
		    alphaCT_mean.getVal(), 7.1);
  lineAlphaCT.SetLineStyle(3);
  TText textCT(xLeftTextPdfSet[targetAlpha], 6.5, "CT10");
  textCT.SetTextFont(43);
  textCT.SetTextSizePixels(26);
  textCT.SetTextAlign(12);

  TBox boxAlphaHERA(alphaHERA_mean.getVal()-alphaHERA_unc.getVal(), 3.9,
		    alphaHERA_mean.getVal()+alphaHERA_unc.getVal(), 5.1);
  boxAlphaHERA.SetFillColor(kGreen-9);
  TLine lineAlphaHERA(alphaHERA_mean.getVal(), 3.9,
		      alphaHERA_mean.getVal(), 5.1);
  lineAlphaHERA.SetLineStyle(3);
  TText textHERA(xLeftTextPdfSet[targetAlpha], 4.5, "HERAPDF1.5");
  textHERA.SetTextFont(43);
  textHERA.SetTextSizePixels(26);
  textHERA.SetTextAlign(12);

  TBox boxAlphaMSTW(alphaMSTW_mean.getVal()-alphaMSTW_unc.getVal(), 1.9,
		    alphaMSTW_mean.getVal()+alphaMSTW_unc.getVal(), 3.1);
  boxAlphaMSTW.SetFillColor(kGreen-9);
  TLine lineAlphaMSTW(alphaMSTW_mean.getVal(), 1.9,
		      alphaMSTW_mean.getVal(), 3.1);
  lineAlphaMSTW.SetLineStyle(3);
  TText textMSTW(xLeftTextPdfSet[targetAlpha], 2.5, "MSTW2008");
  textMSTW.SetTextFont(43);
  textMSTW.SetTextSizePixels(26);
  textMSTW.SetTextAlign(12);

  TBox boxAlphaNNPDF(alphaNNPDF_mean.getVal()-alphaNNPDF_unc.getVal(), -0.1,
		     alphaNNPDF_mean.getVal()+alphaNNPDF_unc.getVal(),  1.1);
  boxAlphaNNPDF.SetFillColor(kGreen-9);
  TLine lineAlphaNNPDF(alphaNNPDF_mean.getVal(), -0.1,
		       alphaNNPDF_mean.getVal(),  1.1);
  lineAlphaNNPDF.SetLineStyle(3);
  TText textNNPDF(xLeftTextPdfSet[targetAlpha], 0.5, "NNPDF2.3");
  textNNPDF.SetTextFont(43);
  textNNPDF.SetTextSizePixels(26);
  textNNPDF.SetTextAlign(12);

  double yLeft = 0.10;
  double yRight = 0.25;
  if(!moch_highE) {
    yLeft = 0.05;
    yRight = 0.48;
  }
  TLegend summaryLeg = TLegend(yLeft, 0.75, yRight, 0.9);
  summaryLeg.SetFillStyle(0);
  summaryLeg.SetBorderSize(0);
  if(pole)
    summaryLeg.AddEntry(&mitSummaryGraphTotErr, theoName[1], "PL");
  if(!moch_highE)
    summaryLeg.AddEntry(&mocSummaryGraphTotErr, theoName[0]+" w/o high-energy approx.", "PL");
  else
    summaryLeg.AddEntry(&mocSummaryGraphTotErr, theoName[0], "PL");

  const double oldPadLeftMargin = gPad->GetLeftMargin();
  const double oldPadTopMargin  = gPad->GetTopMargin();
  gPad->SetLeftMargin(gPad->GetRightMargin());
  gPad->SetTopMargin(1.25*oldPadTopMargin);

  if(!pole)
    mocSummaryGraphTotErr.Draw("AP");
  else
    mitSummaryGraphTotErr.Draw("AP");
  if(targetAlpha) {
    boxAlphaMSTW.Draw();
    lineAlphaMSTW.Draw();
    boxAlphaHERA.Draw();
    lineAlphaHERA.Draw();
    boxAlphaABM.Draw();
    lineAlphaABM.Draw();
    boxAlphaNNPDF.Draw();
    lineAlphaNNPDF.Draw();
    boxAlphaCT.Draw();
    lineAlphaCT.Draw();
    boxAlpha2012.Draw();
    lineAlpha2012.Draw();
    lineAlpha2012_left.Draw();
    lineAlpha2012_right.Draw();
  }
  else if (pole) {
    boxMass2012.Draw();
    lineMass2012.Draw();
    lineMass2012_left.Draw();
    lineMass2012_right.Draw();    
  }
  if(!topppOnly) {
    mocSummaryGraphTotErr.Draw("P");
    mocSummaryGraphInnErr.Draw("||");
  }
  if(pole) {
    mitSummaryGraphTotErr.Draw("P");
    mitSummaryGraphInnErr.Draw("||");
  }
  if(!topppOnly)
    summaryLeg.Draw();
  gPad->RedrawAxis();
  textMSTW.Draw();
  textHERA.Draw();
  textABM.Draw();
  textNNPDF.Draw();
  textCT.Draw();
  if(targetAlpha) {
    textAlpha2012_left.Draw();
    textAlpha2012_right.Draw();
  }
  else {
    if (pole) {
      textMass2012_left.Draw();
      textMass2012_right.Draw();
    }
  }
  TLatex* cmsLabel = cmsTxt(targetAlpha);
//  sqrtSText.SetY(0.90);
//  sqrtSText.SetX(0.75);
//  sqrtSText.Draw();
  cmsLabel->Draw();
//  TLatex constrText(0.,0.,(targetAlpha ? "#alpha_{S} (m_{Z}) = 0.1184 #pm 0.0007" : "m_{t} = 173.2 #pm 1.4 GeV"));
//  constrText.SetNDC();
//  constrText.SetTextAlign(23);
//  constrText.SetX(0.75);
//  constrText.SetY(0.82);
//  constrText.SetTextFont(43);
//  constrText.SetTextSizePixels(28);
//  constrText.Draw();
  if(targetAlpha)
    canvas->Print(printNameBase+"_alphaSummaryPlot.eps");
  else
    canvas->Print(printNameBase+"_massSummaryPlot.eps");
  canvas->Print(printNameBase+".ps");

  gPad->SetLeftMargin(oldPadLeftMargin);
  gPad->SetTopMargin(oldPadTopMargin);
  
//  canvas->Print(printNameBase+".ps]");
//  return 0;
  
  const TString outfile_name = (targetAlpha ? printNameBase+ "_alphaSummary.tab" : printNameBase+ "_massSummary.tab");
  ofstream outfile;
  outfile.open(outfile_name);
  if(topppOnly)
    outfile << "\\begin{tabular}{|l|c|c|c|c|}" << std::endl;
  else
    outfile << "\\begin{tabular}{|ll|c|c|c|c|}" << std::endl;
  outfile << "\\hline" << std::endl;
  const TString oneOrTwoEmptyCols = (topppOnly ? " & " : " & & ");
  if(targetAlpha)
    outfile << oneOrTwoEmptyCols << "Most likely        & \\multicolumn{3}{c|}{Uncertainty} \\\\" << std::endl;
  else
    outfile << oneOrTwoEmptyCols << "Most likely \\mtop & \\multicolumn{3}{c|}{Uncertainty (GeV)} \\\\" << std::endl;
  if(targetAlpha)
    outfile << oneOrTwoEmptyCols << "$\\alpha_S (\\mZ)$ value  & Total & From $\\delta \\mtop$" << std::endl;
  else
    outfile << oneOrTwoEmptyCols << "value (GeV)        & Total & From $\\delta \\alpha_{S}$" << std::endl;
  outfile << " & From $\\delta E_{\\text{LHC}}$ \\\\" << std::endl << "\\hline" << std::endl;
  const unsigned hOrdered[nPdfSets] = {2, 4, 1, 0, 3};
  for(unsigned h=0; h<nPdfSets; h++) {
    char tmpTxt[99];
    if(pole) {
      if(topppOnly) {
	TString format = (targetAlpha ?
			  "%s &  %.4f & ${}^{+%.4f}_{-%.4f}$ & ${}^{+%.4f}_{-%.4f}$ & ${}^{+%.4f}_{-%.4f}$\\\\" :
			  "%s &  %.1f & ${}^{+%.1f}_{-%.1f}$ & ${}^{+%.1f}_{-%.1f}$ & ${}^{+%.1f}_{-%.1f}$\\\\");
	sprintf(tmpTxt, format, pdfName[hOrdered[h]].Data(),
		mitResult[hOrdered[h]]->bestX,
		mitResult[hOrdered[h]]->highErrTotal,
		mitResult[hOrdered[h]]->lowErrTotal,
		mitResult[hOrdered[h]]->highErrFromConstraintUncertainty,
		mitResult[hOrdered[h]]->lowErrFromConstraintUncertainty,
		mitResult[hOrdered[h]]->highErrFromBeamUncertainty,
		mitResult[hOrdered[h]]->lowErrFromBeamUncertainty);
	outfile << tmpTxt << std::endl;
      }
      else {
	TString format = (targetAlpha ?
			  "%s & \\multirow{2}{*}{with %s} &  %.4f & ${}^{+%.4f}_{-%.4f}$ & ${}^{+%.4f}_{-%.4f}$ \\\\" :
			  "%s & \\multirow{2}{*}{with %s} &  %.1f & ${}^{+%.1f}_{-%.1f}$ & ${}^{+%.1f}_{-%.1f}$ \\\\");
	sprintf(tmpTxt, format,
		theoName[1].Data(), pdfName[hOrdered[h]].Data(),
		mitResult[hOrdered[h]]->bestX,
		mitResult[hOrdered[h]]->highErrTotal,
		mitResult[hOrdered[h]]->lowErrTotal,
		mitResult[hOrdered[h]]->highErrFromConstraintUncertainty,
		mitResult[hOrdered[h]]->lowErrFromConstraintUncertainty);
	outfile << tmpTxt << std::endl;
	outfile << "\\cline{3-5}" << std::endl;
	format = (targetAlpha ?
		  "%s & & %.4f & ${}^{+%.4f}_{-%.4f}$ & ${}^{+%.4f}_{-%.4f}$ \\\\" :
		  "%s & & %.1f & ${}^{+%.1f}_{-%.1f}$ & ${}^{+%.1f}_{-%.1f}$ \\\\");
	sprintf(tmpTxt, format,
		theoName[0].Data(),
		mocResult[hOrdered[h]]->bestX,
		mocResult[hOrdered[h]]->highErrTotal,
		mocResult[hOrdered[h]]->lowErrTotal,
		mocResult[hOrdered[h]]->highErrFromConstraintUncertainty,
		mocResult[hOrdered[h]]->lowErrFromConstraintUncertainty);
	outfile << tmpTxt << std::endl;
      }
      outfile << "\\hline" << std::endl;
    }
    else {
      TString format = "%s & with %s &  %.1f & ${}^{+%.1f}_{-%.1f}$ & ${}^{+%.1f}_{-%.1f}$ \\\\";
      sprintf(tmpTxt, format,
	      theoName[0].Data(), pdfName[hOrdered[h]].Data(),
	      mocResult[hOrdered[h]]->bestX,
	      mocResult[hOrdered[h]]->highErrTotal,
	      mocResult[hOrdered[h]]->lowErrTotal,
	      mocResult[hOrdered[h]]->highErrFromConstraintUncertainty,
	      mocResult[hOrdered[h]]->lowErrFromConstraintUncertainty);
      outfile << tmpTxt << std::endl;
      outfile << "\\hline" << std::endl;      
    }
  }
  outfile << "\\end{tabular}" << std::endl;
  outfile.close();
  std::cout << "Wrote " << outfile_name << std::endl;

//  canvas->Print(printNameBase+".ps]");
//  return 0;

  for(unsigned h=0; h<nPdfSets; h++) {
    for(unsigned t=0; t<2; t++) {

      if((t==0 && topppOnly) ||
	 (t==1 && !pole))
	continue;

      const FinalLikeliResults1D* result = (t ? mitResult[h] : mocResult[h]);

      char tmpTxt[99];
      sprintf(tmpTxt, "CMS, L = 2.3 fb^{-1}; %s", theoTitle[h][t].Data());
      TLatex text(0.,0.,tmpTxt);
      text.SetNDC();
      text.SetTextAlign(13);
      text.SetX(gPad->GetLeftMargin());
      text.SetY(1.003);
      text.SetTextFont(43);
      text.SetTextSizePixels(25);

      if(targetAlpha)
	sprintf(tmpTxt, "%s = %.1f GeV",
		mass.getTitle().Data(), mass.getVal());
      else
	sprintf(tmpTxt, "%s = %.4f",
		alpha.getTitle().Data(), alpha.getVal());
      TLatex textConstrVar(0.,0.,tmpTxt);
      textConstrVar.SetNDC();
      textConstrVar.SetTextAlign(23);
      textConstrVar.SetX(0.32);
      textConstrVar.SetY(0.84);
      textConstrVar.SetTextFont(43);
      textConstrVar.SetTextSizePixels(28);
      
      sqrtSText.SetY(0.90);

      RooPlot* frame;
      if(targetAlpha) {
	frame = alpha.frame(RooFit::Range(0.107, 0.125));
	plotProjectedPDF(result, frame, kRed, 1001, alpha);
      }
      else {
	frame = mass.frame(RooFit::Range(167., 190.));
	plotProjectedPDF(result, frame, kRed, 1001, mass);
      }
      frame->Draw();
      frame->SetMaximum(1.4*frame->GetMaximum());
      
      TLegend likeLeg = TLegend(0.5, 0.75, 0.9, 0.92);
      likeLeg.SetFillStyle(0);
      likeLeg.SetBorderSize(0);
      likeLeg.AddEntry("Maximum", "Maximum posterior"      , "L");
      likeLeg.AddEntry("Confide", "68% confidence interval" , "F");
      likeLeg.SetTextFont(43);
      likeLeg.SetTextSizePixels(28);

      likeLeg.Draw();
      text.Draw();
      textConstrVar.Draw();
      sqrtSText.Draw();
      canvas->Print(printNameBase+".ps");
      const TString epsAppendix = (t ? "mitov" : "moch");
      if(targetAlpha)
	canvas->Print(epsString("final_likeDensity_alpha_"+epsAppendix, pole, (PdfType)h));
      else
	canvas->Print(epsString("final_likeDensity_mass_"+epsAppendix, pole, (PdfType)h));
    }
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
      if(pole)
	delete mit_vec[h].at(j);
      for(unsigned i=0; i<moc_funcs[h][j].size(); i++) {
	  delete moc_funcs[h][j].at(i);
	if(pole)
	  delete mit_funcs[h][j].at(i);
      }
    }
    if(!topppOnly)
      delete mocResult[h];
    if(pole)
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
  if(argc==2) {
    if(!strcmp(argv[1],"alpha"))
      return foldedLikelihoods(true, true);
  }
  else if(argc==3) {
    if(!strcmp(argv[1],"mass") && !(strcmp(argv[2],"msbar") && strcmp(argv[2],"pole")))
      return foldedLikelihoods(false, !strcmp(argv[2],"pole"));
  }
  std::cout << "Please call the program in one of the following ways:" << std::endl
	    << "foldedLikelihoods alpha" << std::endl
	    << "foldedLikelihoods mass pole" << std::endl
	    << "foldedLikelihoods mass msbar" << std::endl;
  return 64;
}
