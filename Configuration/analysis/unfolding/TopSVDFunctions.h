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
#include "../semiLeptonic/diffXSection/basicFunctions.h"
#include "../semiLeptonic/diffXSection/HHStyle.h"
#include "TopSVDUnfold.h"
#include "TopSVDUnfold.C"

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
	static void SVD_RangeGraph(TGraph* graph, double& xmin, double& xmax, double& ymin, double& ymax);
	static void SVD_DrawGraph(TGraph* graph, TH1D*& bgrHisto, TString options = "",  int color = 1);
	static double SVD_TextPosX(TH1D* hist, double xpos, bool log, int orientation);
	static double SVD_TextPosY(TH1D* hist, double ypos, bool log, int orientation);
	static TLatex* SVD_DrawText(TString theText, double xpos, double ypos, int orientation, TLatex*& mylatex); 
	static TLine* SVD_DrawVertLine(TH1D*& bgrHisto, double xpos, int color = 1); 
	static TLine* SVD_DrawHorizLine(TH1D*& bgrHisto, double ypos, int color = 1); 
	static void SVD_DrawVertLines(TH1D*& bgrHisto, TVectorD* xpositions, int color = 1); 
    static TGraph* SVD_Vect2Graph(TVectorD* vectorX, TVectorD* vectorY);
    static TGraph* SVD_Point2Graph(double x, double y);
	static void SVD_DrawRange(TH1D* histo, double ymin, double ymax, TString options = "",  int color = 0);
	static TH1D* SVD_MakeRatioNum(TH1D* numerator, TH1D* denominator);
	static TH1D* SVD_MakeRatioDenom(TH1D* numerator, TH1D* denominator);
	static TH1D* SVD_MakeRatioZero(TH1D* numerator, TH1D* denominator);
	static void SVD_DrawStack(THStack* stack, TString xTitle, TString yTitle, TString options = "", int cols = -1);
	static void SVD_SetTitles1D(TH1D* histo, TString name, TString xTitle, TString yTitle);
	static void SVD_SetTitles2D(TH2D* histo, TString name, TString xTitle, TString yTitle, TString zTitle);
	static double SVD_Chi2A(TH1D* dataHist, TH1D* refoldHist);
	static int SVD_GoodRecBins(TH1D* dataHist);
	static int SVD_GoodGenBins(TH1D* xiniHist);
	static int SVD_Ndof(TH1D* dataHist, TH1D* xiniHist) ;
	static TVectorD* SVD_CalcScanPoints(double firstTau, double lastTau, int nScanPoints);
	static double SVD_ScanGlobalCorrelation(TH2D* statCovHist);
	static double SVD_ScanChiSquared(TH1D* weightHist, TH1D* dataHist, TH2D* mcHist);
	static double SVD_ScanCurvature(double curv); 
	static double SVD_ScanAvgSqErr(TH2D* covMatrix); 
	static double SVD_ScanAvgMean(TH1D* unfHist); 
	static void SVD_NewRange(double min, double max, double& newmin, double& newmax, bool log);
	static void SVD_NewUpperRange(double max, double& newmax);
	static TH1D* SVD_CalcGlobCorr(TH2D* statCovHist);
	static double SVD_AvgGlobCorr(TH1D* globCorrHist);
	static int SVD_FindMinimum(TVectorD* xVec, TVectorD* yVec, double& xBest, double& yBest);
	static TH1D* SVD_Refold(TH1D* unfHist, TH1D* xiniHist, TH2D* mcHist, bool useWeights = false);
	static double SVD_LumiScaleFactor(TH1D* dataHist, TH1D* recHist);
	static void SVD_EmptyHistogram1D(TH1D* histo);
	static void SVD_EmptyHistogram2D(TH2D* histo);
	static void SVD_EmptyHistoErrors1D(TH1D* histo);
	static void SVD_EmptyHistoErrors2D(TH2D* histo);
	static int SVD_FindBin(TAxis* axis, double bnd);
	
	// Unfolding function
	static double SVD_Unfold(
	        TH1* dataInputHist,                    
	        TH1* bgrInputHist,   
		TH1* ttbgrInputHist,
	        TH1* genInputHist,                     
	        TH1* recInputHist,                
	        TH1* respInputHist,          
	        const double thebins[],     
	        const int numbins,        
	        double regPar,          
		int regMode,	                   
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
	        TString psFile = "",
		const int verbose = 1,
		bool scanPlots = false
	);
	 
};

#endif

