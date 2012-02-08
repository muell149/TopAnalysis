#ifndef TOPSVDFUNCTIONS_H
#define TOPSVDFUNCTIONS_H

// Includes from Root and C++  
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <sys/stat.h>
#include <map>
#include "assert.h"
#include "TString.h"
#include "TExec.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TH1D.h"
#include "TH2D.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPostScript.h"
#include "TMath.h"
#include "TPad.h"
#include "TStyle.h"
#include "TGraphAsymmErrors.h"
#include "TPaveText.h"
#include "TPaletteAxis.h"

// Includes from Top Analysis
#include "TopAnalysis/Configuration/analysis/semiLeptonic/diffXSection/basicFunctions.h"
#include "TopAnalysis/Configuration/analysis/semiLeptonic/diffXSection/HHStyle.h"
#include "TopAnalysis/Configuration/analysis/unfolding/TopSVDUnfold.h"
#include "TopAnalysis/Configuration/analysis/unfolding/TopSVDUnfold.C"

// Namespaces
using namespace std;


class TopSVDFunctions
{

public: 
	
	// Helper Functions
	static TString SVD_CPQS(TString channel, TString particle, TString quantity, TString special);
	static TString SVD_PlotName(TString channel, TString particle, TString quantity, TString special, TString plotName);
	static double SVD_Divide(double numerator, double denominator);
	static double SVD_BinomialError(double numerator, double denominator);
	static double SVD_Sqrt(double square);
	static TLegend* SVD_NewLegend();
	static void SVD_MoveOFBins1D(TH1D* hist);
	static void SVD_MoveOFBins2D(TH2D* hist);
	static void SVD_EmptySideBins1D(TH1D* histo);
	static void SVD_EmptySideBins2D(TH2D* histo);
	static TH1D* SVD_Rebin1D(TH1* input, int nbinsx, double* binsx);
	static TH2D* SVD_Rebin2D(TH1* input, int nbinsx, double* binsx, int nbinsy, double* binsy, bool transpose = false);
	static TH2D* SVD_Cov2Corr(TH2D* input, TString name, TString axisName, TString type);
	static TH1D* SVD_Cov2Err(TH2D* input, TH1D* means, TString name, TString axisName, TString type);
	static void SVD_Draw2D(TH2D* hist, TString options = "");
	static void SVD_Draw1D(TH1D* hist, TString options = "",  int color = 1);
	static void SVD_DrawRange(TH1D* histo, double ymin, double ymax, TString options = "",  int color = 0);
	static TH1D* SVD_MakeRatioNum(TH1D* numerator, TH1D* denominator);
	static TH1D* SVD_MakeRatioDenom(TH1D* numerator, TH1D* denominator);
	static void SVD_DrawStack(THStack* stack, TString xTitle, TString yTitle, TString options = "", int cols = -1);
	static void SVD_SetTitles1D(TH1D* histo, TString name, TString xTitle, TString yTitle);
	static void SVD_SetTitles2D(TH2D* histo, TString name, TString xTitle, TString yTitle, TString zTitle);
	static double SVD_Chi2A(TH1D* dataHist, TH1D* refoldHist);
	static int SVD_GoodRecBins(TH1D* dataHist);
	static int SVD_GoodGenBins(TH1D* xiniHist);
	static int SVD_Ndof(TH1D* dataHist, TH1D* xiniHist) ;
	static int SVD_Unfold(
	        TH1* dataInputHist,                    
	        TH1* bgrInputHist,                     
	        TH1* genInputHist,                     
	        TH1* recInputHist,                
	        TH1* respInputHist,          
	        const double thebins[],     
	        const int numbins,       
	        int kreg,                          
	        TH1D*& unfolded,            
	        TString channel = "",                   
	        TString particle = "",       
	        TString quantity = "",              
	        TString special = "",                
	        TString channelTex = "",               
	        TString particleTex = "",      
	        TString quantityTex = "",          
	        TString specialTex = "",              
	        TString rootFile = "",              
	        TString psFile = ""          
	);
	 
};

#endif

