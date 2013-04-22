#ifndef util_h
#define util_h

#include <string>

#include <TStyle.h>
#include <Rtypes.h>

class TLorentzVector;
class TH1;
class TString;
class THStack;

#include "classes.h"






/// Convert LorentzVector to an array[E, px, py, pz]
void LVtod4(const LV& lv, double* d);



/// Convert double to string (smart number of digits)
std::string d2s(const double& d);



/// Draw ratio of two histograms
void drawRatio(const TH1* histNumerator, 
               const TH1* histDenominator,
               const Double_t& ratioMin, 
               const Double_t& ratioMax, 
               const TStyle& myStyle = *gStyle, 
               const int verbose=0, 
               const std::vector<double>& err=std::vector<double>(0));



/// Set histogram style to HH definition
void setHHStyle(TStyle& HHStyle);



/// conversion between ROOT's TLorentzVector and 
/// our LV type (ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> >)
const TLorentzVector LVtoTLV(const LV& lv);
const LV TLVtoLV(const TLorentzVector& lv);



/** Sum the histograms in a stack and
 * return the sum in a new TH1
 */
TH1* SummedStackHisto(const THStack* stack);



/** Calculate the median of a histogram
 * 
 */
double Median(TH1* h1);



/// return CMSSW_BASE environment variable as string, with error checking
const std::string CMSSW_BASE();



/// Return the path where relevant input data (e.g. histograms for scale factors) is stored
const TString DATA_PATH();





#endif



