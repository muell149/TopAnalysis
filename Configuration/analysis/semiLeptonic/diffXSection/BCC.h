#ifndef BCC_H_
#define BCC_H_

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include "TROOT.h"
#include "TSystem.h"
#include "TObject.h"
#include "TTree.h"
#include "TFile.h"
#include "TString.h"

// =================
//  Class Definiton
// =================

typedef std::map<TString, std::vector<double> > BCCMap; 

class BCC
{

public:
	
    BCC();
    BCC(TString filename, TString pathname, std::vector<TString> branches, bool mergeLepHad);
    ~BCC();

    BCCMap getMapWithCorrectedCentersInX();
    BCCMap getMapWithCenterErrorsInX();

    int  getErrorCode();

    void runBCCCalculation();

private:
	
    int error_code;  

    TFile *datafile;	
    
    std::map<TString, std::vector<double> > mapBinning;

    std::map<TString, std::vector<double> > mapData;
    
    BCCMap mapCorrBinCentersInX;
    BCCMap mapCorrBinCenterErrorsInX; 

    void setBCCinX();
    void setDefValues();
};


#endif

// for comparison and verification after implementing in official code, can be deleted afterwards

// Bin Centers:
// ttbarMass: 172.5     382.511   442.877    524.041    647.814    879.805 
// topPt:      39.3367   89.9619  155.206    233.902    325.026    480.075 
// ttbarPt:    11.1864   36.7654   81.1256   145.42     239.722 
// topY:       -2.57325  -1.71218  -1.22022   -0.736835  -0.244313   0.245608 0.736329 1.22035 1.71145 2.51202 
// ttbarY:     -1.48288  -1.07159  -0.740248  -0.445975  -0.149249   0.148405 0.444356 0.74196 1.07206 1.47898 

// Statistical Errors:
// ttbarMass: 0          0.105901   0.121414    0.186833    0.374841    1.29595 
// ttbarPt:   0.0311329  0.0582672  0.107555    0.238643    0.472781 
// topPt:     0.0793688  0.0670139  0.0932188   0.140693    0.304792    1.31383 
// topY:      0.00815277 0.00201412 0.000995015 0.000793801 0.000718997 0.000725178 0.000803075 0.00101016  0.00206925 0 
// ttbarY:    0.00286502 0.00125384 0.000852837 0.000748935 0.000707921 0.000703506 0.000740888 0.000858148 0.00125746 0.00275718 


