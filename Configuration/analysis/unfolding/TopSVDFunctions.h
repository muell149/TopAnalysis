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
         
        // Unfolding function
        // For dokumentation, see the function definition
        // in TopSVDFunctions.C
        static double SVD_Unfold(
                        TH1D* dataInputHist,                                        
                        TH1D* bgrInputHist,   
                        TH1D* ttbgrInputHist,
                        TH1D* genInputHist,                                         
                        TH1D* recInputHist,                                
                        TH2D* respInputHist,                                         
                        TH1D*& unfolded,                                       
                        TH1D*& unfoldedNorm,
                        double* totalDataEvents,
                        double* totalBgrEvents,
                        double* totalTtBgrEvents,
                        double* totalRecEvents,
                        double* totalGenEvents,
                        const double thebins[],         
                        const int numbins,                
                        double regPar,          
                        TString steering = "",
                        const int numSys = 0,                        
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
                        TString txtFile = "",
        				TString regParFile = ""
        );
    
    
    protected:
           
   
        // Math
        static double SVD_Divide(double numerator, double denominator);
        static double SVD_BinomialError(double numerator, double denominator);
        static double SVD_Sqrt(double square);
        
        
        // Legends, Stacks, Formatting and all that
        static TLegend* SVD_NewLegend(TString header1, TString header2, double regPar = 0., int mode = -1);
        static TLegend* SVD_NewLegendK();
        static TString SVD_CPQSS(TString channel, TString particle, TString quantity, TString special, TString syst); 
        static TString SVD_PlotName(TString channel, TString particle, TString quantity, TString special, TString syst, TString plotName);
        static void SVD_SetTitles1D(TH1D* histo, TString name, TString xTitle, TString yTitle, int numHist = 1);
        static void SVD_SetTitles2D(TH2D* histo, TString name, TString xTitle, TString yTitle, TString zTitle, int numHist = 1);
        static void SVD_ClearStackLeg(THStack*& stack, TLegend*& leg, TString header1, TString header2, TString header3);
        static void SVD_FormatLegendStandard(TLegend* leg);
        static void SVD_FormatLegendKScan(TLegend* leg);
        static void SVD_Array2Stack(THStack* stack, TLegend* leg, TH1D* histo, TString label, TString drawOptions, TString legOptions, int col, int numHist = 1);
         
       
        // Object Handling
        static TH1D* SVD_CloneHists1D(TH1D* hist, int numHist = 1);
        static TH2D* SVD_CloneHists2D(TH2D* hist, int numHist = 1);
        static void SVD_DeleteHists1D(TH1D*& hist, int numHist = 1);
        static void SVD_DeleteHists2D(TH2D*& hist, int numHist = 1);
        static void SVD_WriteHists1D(TH1D* hists, int numHist = 1);
        static void SVD_WriteHists2D(TH2D* hists, int numHist = 1); 
        static void SVD_RmDir1D(TH1D* hist, int numHist = 1);
        static void SVD_RmDir2D(TH2D* hist, int numHist = 1);
        static double SVD_DoubleFromArray(double* arr, int pos);
        
        // Histogram Manipulation
        static void SVD_MoveOFBins1D(TH1D* hist, int numHist = 1);
        static void SVD_MoveOFBins2D(TH2D* hist, int numHist = 1);
        static void SVD_EmptyRecSideBins1D(TH1D* histo, bool cutLowerRecSideBin, bool cutUpperRecSideBin, int numHist = 1);
        static void SVD_EmptyRecSideBins2D(TH2D* histo, bool cutLowerRecSideBin, bool cutUpperRecSideBin, int numHist = 1);
        static void SVD_EmptyGenSideBins1D(TH1D* histo, bool cutLowerGenSideBin, bool cutUpperGenSideBin, int numHist = 1);
        static void SVD_EmptyGenSideBins2D(TH2D* histo, bool cutLowerGenSideBin, bool cutUpperGenSideBin, int numHist = 1);
        static void SVD_EmptyHistogram1D(TH1D* histo, int numHist = 1);
        static void SVD_EmptyHistogram2D(TH2D* histo, int numHist = 1);
        static void SVD_EmptyHistoErrors1D(TH1D* histo, int numHist = 1);
        static void SVD_EmptyHistoErrors2D(TH2D* histo, int numHist = 1);  
        
        
        // Rebinning
        static int SVD_NumNewBins(int oldNumBins, bool addLowerSideBin, bool addUpperSideBin);
        static void SVD_NewBins(double*& theNewBins, int newNumBins, const double* theOldBins, int oldNumBins, bool addLowerSideBin, bool addUpperSideBin); 
        static TH1D* SVD_Rebin1D(TH1D* input, int nbinsx, const double* binsx, bool addLowerSideBin, bool addUpperSideBin, int numHist = 1);
        static TH2D* SVD_Rebin2D(TH2D* input, int nbinsx, const double* binsx, int nbinsy, const double* binsy, bool addLowerSideBin, bool addUpperSideBin, int numHist = 1, bool transpose = false);
        
        // Derived Histograms
        static int SVD_FindBin(TAxis* axis, double bnd);
        static TH1D* SVD_DiagElements(TH2D* histo, int numHist = 1);
        static TH1D* SVD_HistoErrors1D(TH1D* histo, int numHist = 1);
        static TH2D* SVD_HistoErrors2D(TH2D* histo, int numHist = 1);
        static TH2D* SVD_Cov2Corr(TH2D* input, TString name, TString axisName, TString type);
        static TH1D* SVD_Cov2Err(TH2D* input, TH1D* means, TString name, TString axisName, TString type);
        static TH2D* SVD_ProbMatrix(TH2D* mcHist, TH1D* genHist, int numHist = 1); 
        static TH1D* SVD_ProbHist(TH2D* mcHist, TH1D* genHist, int numHist = 1); 
        static TH1D* SVD_MakeRatioNum(TH1D* numerator, TH1D* denominator, int numHist = 1);
        static TH1D* SVD_MakeRatioDenom(TH1D* numerator, TH1D* denominator, int numHist = 1);
        static TH1D* SVD_MakeRatioZero(TH1D* numerator, TH1D* denominator, int numHist = 1); 
        
        
        // Calculate Ranges
        static void SVD_RangeGraph(TGraph* graph, double& xmin, double& xmax, double& ymin, double& ymax);
        static void SVD_RangeHisto(TH1D* histo, double& ymin, double& ymax, bool showOF = false, int numHist = 1);
        static void SVD_RangeStack(THStack* stack, double& ymin, double& ymax, bool showOF = false);
        static double SVD_TextPosX(TH1D* hist, double xpos, bool log, int orientation);
        static double SVD_TextPosY(TH1D* hist, double ypos, bool log, int orientation);
        static void SVD_NewRange(double min, double max, double& newmin, double& newmax, bool log);
        static void SVD_NewUpperRange(double max, double& newmax);
        static int SVD_FindMinimum(TVectorD* xVec, TVectorD* yVec, double& xBest, double& yBest); 
        
        
        // Drawing
        static void SVD_Draw2D(TH2D* hist, TString options = "");
        static void SVD_Draw1D(TH1D* hist, TString options = "",  int color = 1); 
        static void SVD_DrawGraph(TGraph* graph, TH1D*& bgrHisto, TString options = "",  int color = 1); 
        static void SVD_DrawGraphRange(TGraph* graph, TH1D*& bgrHisto, double ymin, double ymax, TString options = "",  int color = 1); 
        static void SVD_DrawGraphAutoRange(TGraph* graph, TH1D*& bgrHisto, TString options = "",  int color = 1); 
        static void SVD_DrawGraphZero(TGraph* graph, TH1D*& bgrHisto, TString options = "",  int color = 1); 
        static TLatex* SVD_DrawText(TString theText, double xpos, double ypos, int orientation, TLatex*& mylatex); 
        static TLine* SVD_DrawVertLine(TH1D*& bgrHisto, double xpos, int color = 1); 
        static TLine* SVD_DrawHorizLine(TH1D*& bgrHisto, double ypos, int color = 1); 
        static void SVD_DrawVertLines(TH1D*& bgrHisto, TVectorD* xpositions, int color = 1); 
        static void SVD_DrawRange(TH1D* histo, double ymin, double ymax, TString options = "",  int color = 0);
        static void SVD_DrawStackRange(THStack* stack, TLegend* leg, TString xTitle, TString yTitle, double ymin, double ymax, TString options = "", int col = -1, bool showOF = false);
        static void SVD_DrawStackAutoRange(THStack* stack, TLegend* leg, TString xTitle, TString yTitle, TString options, int col, bool showOF = false, bool log = false);
        static void SVD_DrawStackZero(THStack* stack, TLegend* leg, TString xTitle, TString yTitle, TString options, int col, bool showOF = false);
        static TGraph* SVD_Vect2Graph(TVectorD* vectorX, TVectorD* vectorY);
        static TGraph* SVD_Point2Graph(double x, double y); 
         
        
        // Refolding, ChiSquare and global Correlation 
        static double SVD_Chi2A(TH1D* dataHist, TH1D* refoldHist);
        static int SVD_GoodRecBins(TH1D* dataHist);
        static int SVD_GoodGenBins(TH1D* xiniHist);
        static int SVD_Ndof(TH1D* dataHist, TH1D* xiniHist); 
        static TH1D* SVD_CalcGlobCorr(TH2D* statCovHist, TH1D* dataHist);
        static double SVD_AvgGlobCorr(TH1D* globCorrHist);
        static TH1D* SVD_Refold(TH1D* unfHist, TH1D* xiniHist, TH2D* mcHist, bool useWeights, int numHist = 1);
        
        
        // Tau Scan  
        static TVectorD* SVD_CalcScanPoints(double firstTau, double lastTau, int nScanPoints);
        static double SVD_ScanGlobalCorrelation(TH2D* statCovHist, TH1D* dataHist);
        static double SVD_ScanChiSquared(TH1D* weightHist, TH1D* dataHist, TH2D* mcHist);
        static double SVD_ScanCurvature(double curv); 
        static double SVD_ScanAvgSqErr(TH2D* covMatrix); 
        static double SVD_ScanAvgMean(TH1D* unfHist);
        
        
        // Scaling
        static double SVD_LumiScaleFactor(TH1D* dataHist, TH1D* recHist);
        static void SVD_ArrayScale(TH1D* histo, double scale, int numHist = 1); 
        static double SVD_Integral1D(TH1D* hist, int syst, bool doOF); 
        static double SVD_Integral2D(TH2D* hist, int syst, bool doOF); 
        static double* SVD_ArrayIntegral1D(TH1D* hist, bool doOF, int numHist);
        
        // Background
        static void SVD_BackgrHandling(TH1D*& dataHist, TH1D* bgrHist, TH1D* ttbgrHist, TH1D* biniHist, TH1D* rawHist, int numHist = 1);
        
        
        // SVD Setup
        static TopSVDUnfold* SVD_SetupTool(TH1D* dataHist, TH1D* biniHist, TH1D* xiniHist, TH2D* mcHist, double theTau, int numHist = 1);
        static void SVD_DeleteSVD(TopSVDUnfold* SVDs, int numSVDs = 1);
        static TH1D* SVD_CallSVDUnfolding(TopSVDUnfold* mySVDUnfold, int theKReg, int numHist = 1);
        static TH1D* SVD_RetrieveWeights(TopSVDUnfold* mySVDUnfold, int numHist = 1);
        static TH1D* SVD_RetrieveDD(TopSVDUnfold* mySVDUnfold, int numHist = 1);
        static TH1D* SVD_RetrieveSV(TopSVDUnfold* mySVDUnfold, int numHist = 1);
        
        
        // Purity, Stability and all that
        static void SVD_Pur(TH1D*& purHist, TH2D* mcHist,int numHist = 1);
        static void SVD_Stab(TH1D*& stabHist, TH2D* mcHist,int numHist = 1);
        static void SVD_Eff(TH1D*& effHist, TH2D* mcHist, TH1D* xiniHist,  int numHist = 1);
        static void SVD_BBBEff(TH1D*& beffHist, TH1D* biniHist, TH1D* xiniHist, int numHist = 1);
        static void SVD_BBBUnf(TH1D*& bbbHist, TH1D* dataHist, TH1D* beffHist, int numHist = 1);
        
        
        // Systematics
        static TH1D* SVD_ArrayToShifts(TH1D* array, int numHist = 1); 
        
        
        // Normalization
        static void SVD_GlobalEventYield(double*& globEvYield, double*& globEvYieldErr, double* totalDataEvents, double* totalBgrEvents, double* totalTtBgrEvents, int numHist);
        static void SVD_GlobalEfficiency(double*& globalEff, double* totalRecEvents, double* totalGenEvents, int numHist);
        static TH1D* SVD_ExtNormalizeSVDDistribution(TH1D* inputHist, TH2D* probMatrixHist, TH2D* statCovMatrix, double* globalEfficiency, double* globalEventYield, double* globalEventYieldErr, int numHist);
        static TH1D* SVD_ExtNormalizeBBBDistribution(TH1D* inputHist, double* globalEfficiency, double* globalEventYield, double* globalEventYieldErr, int numHist);
        static TH1D* SVD_ExtNormalizeGenDistribution(TH1D* inputHist, double* totalGenEvents, int numHist);
        static TH1D* SVD_IntNormalizeSVDDistribution(TH1D* inputHist, TH2D* statCovMatrix, int numHist);
        static TH1D* SVD_IntNormalizeBBBDistribution(TH1D* inputHist, int numHist);
        static TH1D* SVD_IntNormalizeGenDistribution(TH1D* inputHist, int numHist);
        
        
        // Files and Folders
        static TString SVD_FindFolder(TString filepath);
        static TString SVD_FindFile(TString filepath);
        static void SVD_MakeFolder(TString outputpath);
        static void SVD_TouchFile(TString filepath);
        static void SVD_RemoveFile(TString filepath);
        static void SVD_LineToFile(TString string, TString filepath, TString option);
        static TString SVD_LineFromFile(TString key, TString filepath);
        static void SVD_PrintPage(TCanvas& canvas, TString outputfilename, bool doEps, int firstLast);
        
        // Misc
        static int SVD_GetDigit(TString steering, int digit, int standard); 
     
};

#endif

