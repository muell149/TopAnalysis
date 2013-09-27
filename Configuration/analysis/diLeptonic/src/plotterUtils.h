#ifndef ttbar_histoUtils_h
#define ttbar_histoUtils_h

#include <vector>

#include <Rtypes.h>

class TH1;
class THStack;
class TStyle;




namespace ttbar{
    
    /// Draw ratio of two histograms
    void drawRatio(const TH1* histNumerator, 
                   const TH1* histDenominator,
                   const Double_t& ratioMin, 
                   const Double_t& ratioMax, 
                   const bool addFit = 0,
                   const TStyle& myStyle = *gStyle, 
                   const int verbose=0, 
                   const std::vector<double>& err=std::vector<double>(0));



    /// Set histogram style to HH definition
    void setHHStyle(TStyle& HHStyle);



    /** Sum the histograms in a stack and
     * return the sum in a new TH1
     */
    TH1* summedStackHisto(const THStack* stack);
}





#endif



