#ifndef foldedLikelihoods_classes_h
#define foldedLikelihoods_classes_h

//////////////////////////////////////////////////
/// Class for linearized relative uncertainties
//////////////////////////////////////////////////

class LinRelUncertainty {

public:

  LinRelUncertainty(const TString& label, const TF1* fittedFunction, RooRealVar& x);

private:

  RooRealVar p0;
  RooRealVar p1;

public:

  RooPolyVar polyVar;

};

LinRelUncertainty::LinRelUncertainty(const TString& label, const TF1* fittedFunction, RooRealVar& x):
  p0(label+"_p0", label+"_p0", fittedFunction->GetParameter(0)),
  p1(label+"_p1", label+"_p1", fittedFunction->GetParameter(1)),
  polyVar(label, label, x, RooArgSet(p0, p1))
{}

#endif
