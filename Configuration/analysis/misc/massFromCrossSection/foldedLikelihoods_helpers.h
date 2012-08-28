#ifndef foldedLikelihoods_helpers_h
#define foldedLikelihoods_helpers_h

double
getMaxAndUncertaintiesFromIntegral(TF1* f1, double &lowErr, double& higErr,
				   const double xMin, const double xMax, double stepSize, const double targetPrecision)
{
  std::cout << "============================================================" << std::endl;
  std::cout << "Calculating uncertainties for "
	    << f1->GetName() << " via integration around maximum..." << std::endl;
  const double precision = 1E-08;
  double* params = 0;
  const double max = f1->GetMaximumX();
  const double fullIntegral = f1->Integral(xMin, xMax, params, precision);
  std::cout << "Maximum: " << max << std::endl;
  std::cout << "Integral from " << xMin << " to " << xMax << ": " << fullIntegral
	    << " (deviation from unity will be used to rescale integrals calculated in the following)" << std::endl;
  if(fullIntegral < 0.97 || fullIntegral > 1.03) {
    std::cout << "Deviation from unity larger than expected!" << std::endl;
    abort();
  }
  double sigma = 0;
  std::cout << std::left << std::setw(8) << "Delta:" << " " << "Integral:" << std::endl;
  while( 1 ) {
    sigma += stepSize;
    const double integral = f1->Integral(max-sigma, max+sigma, params, precision) / fullIntegral;
    if(integral > 0.682) {
      std::cout << std::left << std::setw(8) << sigma << " " << integral << std::endl;
      if(integral < 0.683 && stepSize <= targetPrecision)
	break;
      sigma -= stepSize;
      stepSize *= 0.1;
    }
  }
  std::cout << "Symmetric uncertainty (1 sigma): " << sigma << std::endl;
  std::cout << "Function value at left / right edge: " << f1->Eval(max-sigma) << " / " << f1->Eval(max+sigma) << std::endl;
  lowErr = sigma;
  higErr = sigma;
  if( f1->Eval(max-lowErr) < f1->Eval(max+higErr) ) {
    while( f1->Eval(max-lowErr) < f1->Eval(max+higErr) ) {
      lowErr -= stepSize;
      higErr += stepSize;
    }
  }
  else {
    while( f1->Eval(max-lowErr) > f1->Eval(max+higErr) ) {
      lowErr += stepSize;
      higErr -= stepSize;
    }
  }
  std::cout << "Asymmetric uncertainties: " << "+" << higErr << ", -" << lowErr << std::endl;
  std::cout << "Function value at left / right edge: " << f1->Eval(max-lowErr) << " / " << f1->Eval(max+higErr) << std::endl;
  std::cout << "Integral: " << f1->Integral(max-lowErr, max+higErr, params, precision) << std::endl;
  std::cout << "============================================================" << std::endl;
  return max;
}

#endif

