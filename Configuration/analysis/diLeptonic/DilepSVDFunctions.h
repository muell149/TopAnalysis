#ifndef DILEPSVDFUNCTIONS_H
#define DILEPSVDFUNCTIONS_H

// Include parent class
#include "../unfolding/TopSVDFunctions.h"
#include "../unfolding/TopSVDFunctions.C"


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



	// REGMODES:
	// (1) regMode=0 is standard BBB unfolding, no regularization
	// (2) regMode=1 is SVD Unfolding, regularization by means of 
	//        the k Parameter. Specify the k Parameter in 'regPar'
	// (3) regMode=2 is SVD Unfolding, regularization by means of
	//        the tau Parameter. Specify the tau Parameter 
	//        in 'regpar'
	// (4) regMode=3 is SVD Unfolding. A scan for the optimal tau
	//        parameter is performed. The scan is performed around
	//        a "center value" for tau, to be specified in 'regpar' .
	//        Note: The scan may take a while!     
	// (5) regMode=4 is SVD Unfolding. A scan for the optimal tau
	//        parameter is performed. The scan is performed around
	//        a "center value" for k, to be specified in 'regpar'    
	//        Note: The scan may take a while!
	// Standard Value is (1).      
	int  GetRegMode() { return regMode; }
	void SetRegMode(int b) { regMode = b;}
	


public: 	
	double SVD_GetRegPar(TString channel, TString particle, TString quantity, TString special = "");
    void SVD_Tex(TString channel, TString particle, TString quantity, TString special, TString& channelTex, TString& particleTex, TString& quantityTex, TString& specialTex);
    TString SVD_GetOutputPath();
    TString SVD_GetOutputFileNamePs(TString channel, TString particle, TString quantity, TString special = "");
    TString SVD_GetOutputFileNameRoot(TString channel, TString particle, TString quantity, TString special = "");
    double SVD_DoUnfold(TH1* dataInputHist,TH1* bgrInputHist,TH1* genInputHist,TH1* recInputHist,TH1* respInputHist,const double thebins[],const int numbins,                  
        TH1D*& unfolded,TString channel,TString particle,TString quantity,TString special);
 
 
 
 
private: 
    bool unfoldingPlotsToPs;
    bool unfoldingPlotsToRoot; 
    int regMode;
    TString outpath;
     
	 
};

#endif

