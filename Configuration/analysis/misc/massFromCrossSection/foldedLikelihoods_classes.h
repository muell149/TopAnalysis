#ifndef foldedLikelihoods_classes_h
#define foldedLikelihoods_classes_h

#include "RooNumIntConfig.h"

//////////////////////////////////////////////////
/// Class for linearized relative uncertainties
//////////////////////////////////////////////////

class LinRelUncertainty {

public:

  LinRelUncertainty(const TString& label, const TF1* fittedFunction, RooRealVar& x);

private:

  const RooRealVar p0;
  const RooRealVar p1;

public:

  const RooPolyVar polyVar;

};

LinRelUncertainty::LinRelUncertainty(const TString& label, const TF1* fittedFunction, RooRealVar& x):
  p0(label+"_p0", label+"_p0", fittedFunction->GetParameter(0)),
  p1(label+"_p1", label+"_p1", fittedFunction->GetParameter(1)),
  polyVar(label, label, x, RooArgSet(p0, p1))
{}

//////////////////////////////////////////////////
/// Class for predicted cross sections
/// with mass dependence and uncertainties
//////////////////////////////////////////////////

class PredXSec {

public:

  PredXSec(const TString& label, RooRealVar& xsec_var, RooRealVar& mass_var,
	   const TF1* xsec_func, const std::vector<TF1*>* unc_funcs);

public:

  const TString name;

private:

  const RooRealVar p0;
  const RooRealVar p1;
  const RooRealVar p2;
  const RooRealVar p3;

  const LinRelUncertainty relUncPdf;
  const LinRelUncertainty relUncAlpha;
  const LinRelUncertainty relUncScaleUp;
  const LinRelUncertainty relUncScaleDown;

public:

  RooFormulaVar xsec;

private:

  RooFormulaVar xsecScaleUp;
  RooFormulaVar xsecScaleDown;
  RooFormulaVar gaussianUnc;

  RooNumIntConfig mcIntegratorCfg;

public:

  RooGaussian gaussianProb;
  RooGenericPdf rectangularProb;
  RooGenericPdf prob;

};

PredXSec::PredXSec(const TString& label, RooRealVar& xsec_var, RooRealVar& mass_var,
		   const TF1* xsec_func, const std::vector<TF1*>* unc_funcs):
  name(label),
  p0(label+"_p0", label+"_p0", xsec_func->GetParameter(0)),
  p1(label+"_p1", label+"_p1", xsec_func->GetParameter(1)),
  p2(label+"_p2", label+"_p2", xsec_func->GetParameter(2)),
  p3(label+"_p3", label+"_p3", xsec_func->GetParameter(3)),
  relUncPdf      (label+"_relUncPdf"      , unc_funcs[1].at(0), mass_var),
  relUncAlpha    (label+"_relUncAlpha"    , unc_funcs[2].at(0), mass_var),
  relUncScaleUp  (label+"_relUncScaleUp"  , unc_funcs[0].at(0), mass_var),
  relUncScaleDown(label+"_relUncScaleDown", unc_funcs[0].at(1), mass_var),
  xsec(label+"_xsec", label+"_xsec", "(@1+@2*@0+@3*@0*@0+@4*@0*@0*@0)/(@0*@0*@0*@0)",
       RooArgSet(mass_var, p0, p1, p2, p3)),
  xsecScaleUp(label+"_xsecScaleUp", label+"_xsecScaleUp", "@0+@0*TMath::Abs(@1)",
	      RooArgSet(xsec, relUncScaleUp.polyVar)),
  xsecScaleDown(label+"_xsecScaleDown", label+"_xsecScaleDown", "@0-@0*TMath::Abs(@1)",
		RooArgSet(xsec, relUncScaleDown.polyVar)),
  gaussianUnc(label+"_gaussianUnc", label+"_gaussianUnc", "@0*TMath::Sqrt(@1*@1+@2*@2)",
	      RooArgSet(xsec, relUncPdf.polyVar, relUncAlpha.polyVar)),
  mcIntegratorCfg(*RooAbsReal::defaultIntegratorConfig()),
  gaussianProb(label+"_gaussianProb", label+"_gaussianProb", xsec_var, xsec, gaussianUnc),
  rectangularProb(label+"_rectangularProb", label+"_rectangularProb",
		  "(@0 >= @1) && (@0 < @2)", RooArgList(xsec_var, xsecScaleDown, xsecScaleUp)),
  prob(label+"_prob", label+"_prob",
       "1/(2*(@3-@2))*(TMath::Erf((@3-@0)/(@1*TMath::Sqrt(2)))-TMath::Erf((@2-@0)/(@1*TMath::Sqrt(2))))",
       RooArgList(xsec_var, gaussianUnc, xsecScaleDown, xsecScaleUp))
{
  mcIntegratorCfg.method1D().setLabel("RooMCIntegrator");
  rectangularProb.setIntegratorConfig(mcIntegratorCfg);
}

#endif
