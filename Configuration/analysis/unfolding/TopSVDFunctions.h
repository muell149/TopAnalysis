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
    static TString SVD_CPQSS(TString channel, TString particle, TString quantity, TString special, TString syst);
    static TString SVD_PlotName(TString channel, TString particle, TString quantity, TString special, TString syst, TString plotName);
    static double SVD_Divide(double numerator, double denominator);
    static double SVD_BinomialError(double numerator, double denominator);
    static double SVD_Sqrt(double square);
    static TLegend* SVD_NewLegend(TString header1, TString header2, double regPar = 0., int mode = -1);
    static TLegend* SVD_NewLegendK();
    static TH1D* SVD_CloneHists1D(TH1D* hist, int numHist = 1);
    static TH2D* SVD_CloneHists2D(TH1D* hist, int numHist = 1);
    static void SVD_MoveOFBins1D(TH1D* hist, int numHist = 1);
    static void SVD_MoveOFBins2D(TH2D* hist, int numHist = 1);
    static void SVD_EmptySideBins1D(TH1D* histo, int numHist = 1);
    static void SVD_EmptySideBins2D(TH2D* histo, int numHist = 1);
    static void SVD_EmptyHistogram1D(TH1D* histo, int numHist = 1);
    static void SVD_EmptyHistogram2D(TH2D* histo, int numHist = 1);
    static void SVD_EmptyHistoErrors1D(TH1D* histo, int numHist = 1);
    static void SVD_EmptyHistoErrors2D(TH2D* histo, int numHist = 1);
    static TH1D* SVD_Rebin1D(TH1D* input, int nbinsx, double* binsx, int numHist = 1);
    static TH2D* SVD_Rebin2D(TH2D* input, int nbinsx, double* binsx, int nbinsy, double* binsy, int numHist = 1, bool transpose = false);
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
    static TH1D* SVD_MakeRatioNum(TH1D* numerator, TH1D* denominator, int numHist = 1);
    static TH1D* SVD_MakeRatioDenom(TH1D* numerator, TH1D* denominator, int numHist = 1);
    static TH1D* SVD_MakeRatioZero(TH1D* numerator, TH1D* denominator, int numHist = 1);
    static void SVD_DrawStack(THStack* stack, TString xTitle, TString yTitle, TString options = "", int col = -1);
    static void SVD_DrawStackRange(THStack* stack, TString xTitle, TString yTitle, double ymin, double ymax, TString options = "", int col = -1);
    static void SVD_SetTitles1D(TH1D* histo, TString name, TString xTitle, TString yTitle, int numHist = 1);
    static void SVD_SetTitles2D(TH2D* histo, TString name, TString xTitle, TString yTitle, TString zTitle, int numHist = 1);
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
    static TH1D* SVD_Refold(TH1D* unfHist, TH1D* xiniHist, TH2D* mcHist, bool useWeights, int numHist = 1);
    static double SVD_LumiScaleFactor(TH1D* dataHist, TH1D* recHist);
    static int SVD_FindBin(TAxis* axis, double bnd);
    static void SVD_BackgrHandling(TH1D*& dataHist, TH1D* bgrHist, TH1D* ttbgrHist, TH1D* biniHist, TH1D* rawHist, int numHist = 1);
    static void SVD_Array2Legend(TLegend* leg, TH1D* histo, TString string, TString option = "", int numHist = 1);
    static void SVD_Array2Stack(THStack* stack, TH1D* histo, TString options, int col, int numHist = 1);
    static void SVD_ArrayScale(TH1D* histo, double scale, int numHist = 1); 
    static TopSVDUnfold* SVD_SetupTool(TH1D* dataHist, TH1D* biniHist, TH1D* xiniHist, TH2D* mcHist, double theTau, int numHist = 1);
    static TH1D* SVD_CallSVDUnfolding(TopSVDUnfold* mySVDUnfold, int theKReg, int numHist = 1);
    static TH1D* SVD_RetrieveWeights(TopSVDUnfold* mySVDUnfold, int numHist = 1);
    static TH1D* SVD_RetrieveDD(TopSVDUnfold* mySVDUnfold, int numHist = 1);
    static TH1D* SVD_RetrieveSV(TopSVDUnfold* mySVDUnfold, int numHist = 1);
    static void SVD_Pur(TH1D*& purHist, TH2D* mcHist,int numHist = 1);
    static void SVD_Stab(TH1D*& stabHist, TH2D* mcHist,int numHist = 1);
    static void SVD_Eff(TH1D*& effHist, TH2D* mcHist, TH1D* xiniHist,  int numHist = 1);
    static void SVD_BBBEff(TH1D*& beffHist, TH2D* mcHist, TH1D* xiniHist, int numHist = 1);
    static void SVD_BBBUnf(TH1D*& bbbHist, TH1D* dataHist, TH1D* beffHist, int numHist = 1);
    static TH1D* SVD_ArrayToShifts(TH1D* array, int numHist = 1);
    
    // Unfolding function
    static double SVD_Unfold(
            TH1D* dataInputHist,                    
            TH1D* bgrInputHist,   
            TH1D* ttbgrInputHist,
            TH1D* genInputHist,                     
            TH1D* recInputHist,                
            TH2D* respInputHist,          
            const double thebins[],     
            const int numbins,        
            double regPar,          
            int regMode,                       
            TH1D*& unfolded,
            int numSys = 0,            
            TString channel = "",                   
            TString particle = "",       
            TString quantity = "",              
            TString special = "",       
            TString systname = "",
            TString channelTex = "",               
            TString particleTex = "",      
            TString quantityTex = "",          
            TString specialTex = "",   
            TString systnameTex = "",
            TString rootFile = "",              
            TString psFile = "",            
            TString scanResultFile = "",
            const int verbose = 1,
            bool scanPlots = false
    );
      
      
};

#endif

