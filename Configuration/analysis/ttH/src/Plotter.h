#ifndef plotterclass_h
#define plotterclass_h

#include <vector>
#include <map>
#include <set>

class TGraphErrors;
class TLegend;
class RootFileReader;
class TString;
class TH1;

#include "plotterHelpers.h"
#include "DyScaleFactors.h"
#include "sampleHelpers.h"
#include "SamplesFwd.h"





class Plotter {

public:
    
    Plotter(const Samples& samples,
            const double& luminosity,
            const DyScaleFactors::DyScaleFactorMap& m_dyScaleFactors,
            const DrawMode::DrawMode& drawMode);
    ~Plotter(){};
    
    void setOptions(const TString&, const TString&, const TString&, const TString&,
                    const int, const bool, const bool, const bool,
                    const double&, const double&, const double&, const double&,
                    const int, const std::vector<double>&, const std::vector<double>&);
    void producePlots();
    
    
    
private:
    
    typedef std::pair<TString, TH1*> LegendHistPair;
    
    bool prepareDataset(const std::vector<Sample>&, const Systematic::Systematic& systematic);

    void write(const Channel::Channel&, const Systematic::Systematic&);
    
    TLegend* controlLegend(const LegendHistPair& dataHist, const std::vector<LegendHistPair>& stackHists,
                           const std::vector<LegendHistPair>& higgsHists, TLegend* leg);
    void setStyle(SampleHistPair&, const bool isControlPlot=false);
    void drawDecayChannelLabel(const Channel::Channel&, const double& textSize=0.04);
    void drawCmsLabels(const int cmsprelim=1, const double& energy=8, const double& textSize=0.04);
    
    
    
    /// Samples to be analysed
    const Samples& samples_;
    
    /// Luminosity
    const double luminosity_;
    
    /// Map containing the Drell-Yan scale factors
    const DyScaleFactors::DyScaleFactorMap& m_dyScaleFactors_;
    
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







