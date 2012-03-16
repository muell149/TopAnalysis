#ifndef TOPSVDUNFOLD_H
#define TOPSVDUNFOLD_H

#include "BaseSVDUnfold.h"
#include "BaseSVDUnfold.C"

class TopSVDUnfold : public BaseSVDUnfold {

public:

    // Special Constructure that creates "empty" objects
    // This is needed create arrays of TopSVDUnfold on the heap
    TopSVDUnfold(); // Needed for the construction of arrays 


    // Constructors and Destructor
    TopSVDUnfold( const TH1D* bdat, const TH1D* bini, const TH1D* xini, const TH2D* Adet );
    TopSVDUnfold( const TH1D* bdat, TH2D* Bcov, const TH1D* bini, const TH1D* xini, const TH2D* Adet );
    TopSVDUnfold( const TopSVDUnfold& other ); 
    virtual ~TopSVDUnfold(); 
   
   
   
    // Steer Regularization
    void SetTau(double tau) { fTau = tau; }
    double GetTau() { return fTau;}
    void SetKReg(int kreg) { fKReg = kreg;}
   
    // Get Curvature of last unfolding run
    double GetCurv() { return fCurv; }
   
    
    // Get Histo of Weights of LAST Unfolding run
    TH1D* GetWeights(); 
   
   
    // UNFOLDING
    // Here, we overwrite the Unfold-Function from BaseSVDUnfold!
    // A litte HowTo:
    // If you want to steer the unfolding via k
    // --- just use the function as you are used to.
    // If you want to steer the unfolding via tau
    // --- Set tau via the "SetTau" setter function
    // --- Use UnfoldTau with k = -1.
    virtual TH1D* Unfold(Int_t kreg); 

protected:
    double fTau;
    double fCurv;
    bool fReturnWeights;
    TH1D* fWeights;
   
};

#endif

