#ifndef DILEPSVDFUNCTIONS_H
#define DILEPSVDFUNCTIONS_H

// Include parent class
#include "TopAnalysis/Configuration/analysis/unfolding/TopSVDFunctions.h"
#include "TopAnalysis/Configuration/analysis/unfolding/TopSVDFunctions.C"


// Namespaces
using namespace std;


class DilepSVDFunctions : public TopSVDFunctions
{

public:
	DilepSVDFunctions();
	
	// Setup
	bool GetUnfoldingPlotsToPs() { return unfoldingPlotsToPs; }
	void SetUnfoldingPlotsToPs(bool b) { unfoldingPlotsToPs = b;}
	bool GetUnfoldingPlotsToRoot() { return unfoldingPlotsToRoot; }
	void SetUnfoldingPlotsToRoot(bool b) { unfoldingPlotsToRoot = b;}
	void SetOutputPath(TString path) { outpath = path;}

	


public: 	
	int SVD_GetKValue(TString channel, TString particle, TString quantity, TString special = "");
    void SVD_Tex(TString channel, TString particle, TString quantity, TString special, TString& channelTex, TString& particleTex, TString& quantityTex, TString& specialTex);
    TString SVD_GetOutputPath();
    TString SVD_GetOutputFileNamePs(TString channel, TString particle, TString quantity, TString special = "");
    TString SVD_GetOutputFileNameRoot(TString channel, TString particle, TString quantity, TString special = "");
    int SVD_DoUnfold(TH1* dataInputHist,TH1* bgrInputHist,TH1* genInputHist,TH1* recInputHist,TH1* respInputHist,const double thebins[],const int numbins,                  
        TH1D*& unfolded,TString channel,TString particle,TString quantity,TString special);
 
 
 
 
private: 
    bool unfoldingPlotsToPs;
    bool unfoldingPlotsToRoot;
    TString outpath;
	 
};

#endif

