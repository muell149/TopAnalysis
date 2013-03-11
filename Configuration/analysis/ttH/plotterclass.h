#ifndef plotterclass_h
#define plotterclass_h

#include <vector>
#include <map>
#include <set>

#include "plotterHelpers.h"
#include "samples.h"
#include "dyScaleFactors.h"

class TGraphErrors;
class TLegend;
class RootFileReader;
class TString;




class Plotter {

public:
    
    Plotter(const Samples& samples, const double& luminosity, DyScaleFactors::DyScaleFactorMap m_dyScaleFactors, const DrawMode::DrawMode& drawMode);
    ~Plotter(){};
    
    void setOptions(TString, TString, TString, TString, int, bool, bool, bool, double, double, double, double, int, std::vector<double>, std::vector<double>);
    void producePlots();
    
    
    
private:
    
    typedef std::pair<TString, TH1D*> LegendHistPair;
    
    bool prepareDataset(const std::vector<Sample>&);

    void write(const Channel::Channel&, const Systematic::Systematic&);
    
    TLegend* ControlLegend(const LegendHistPair& dataHist, const std::vector<LegendHistPair>& stackHists, const std::vector<LegendHistPair>& higgsHists, TLegend* leg);
    void setStyle(SampleHistPair&, bool =false);
    void drawDecayChannelLabel(const Channel::Channel&, double textSize=0.04);
    void drawCmsLabels(int cmsprelim=1, double energy=8, double textSize=0.04);
    
    
    
    /// Samples to be analysed
    Samples samples_;
    
    /// Luminosity
    const double luminosity_;
    
    /// Map containing the Drell-Yan scale factors
    const DyScaleFactors::DyScaleFactorMap m_dyScaleFactors_;
    
    /// Draw mode for Higgs
    const DrawMode::DrawMode drawMode_;
    
    /// File reader for accessing specific histogram from given file
    RootFileReader* fileReader_;
    
    
    
    TString name_;
    
    int bins_, rebin_;
    double rangemin_, rangemax_, ymin_, ymax_;
    
    std::vector<double> XAxisbins_, XAxisbinCenters_;
    
    TString YAxis_;
    TString XAxis_;
    
    // The variable logX_ is not used at all...
    bool logX_, logY_, doDYScale_;
    
    
    
    /// Pair of histogram to print and corresponding sample
    std::vector<SampleHistPair> v_sampleHistPair_;
    
    
};







#endif







