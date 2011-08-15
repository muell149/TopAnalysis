#ifndef BCC_H_
#define BCC_H_

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <climits>

#include "TROOT.h"
#include "TSystem.h"
#include "TObject.h"
#include "TH1F.h"
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
    std::map<TString, TH1F>                 mapHistos;

    std::vector<TH1F> vecHistos;
    
    BCCMap mapCorrBinCentersInX;
    BCCMap mapCorrBinCenterErrorsInX; 

    void setBCCinX_MeanOverBin();
    void setBCCinX_IntersectionInBin();
    void setDefValues();

    void MakeHistos();
};

#endif
