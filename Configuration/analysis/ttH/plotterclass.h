#ifndef plotterclass_h
#define plotterclass_h

#include <vector>
#include <map>
#include <set>

#include "samples.h"
#include "dyScaleFactors.h"

class TGraphErrors;
class TLegend;
class RootFileReader;
class TString;




class Plotter {

public:
    
    enum DrawMode{stacked, overlaid, scaledoverlaid, undefined};
    
    Plotter(const Samples& samples, const double& luminosity, DyScaleFactors::DyScaleFactorMap m_dyScaleFactors, const DrawMode& drawMode);
    ~Plotter(){};
    
    void setOptions(TString, TString, TString, TString, int, bool, bool, bool, double, double, double, double, int, std::vector<double>, std::vector<double>);
    void producePlots();
    
private:
    
    bool prepareDataset(const Sample::Channel&, const Sample::Systematic&, const std::vector<Sample>&);

    void write(const Sample::Channel&, const Sample::Systematic&);
    
    TLegend* ControlLegend(std::vector<SampleHistPair>& v_sampleHistPair, TLegend* leg, bool drawHiggsOverlaid, std::vector<TString> v_higgsLabel);
    
    void setStyle(SampleHistPair&, bool =false);
    void drawDecayChannelLabel(const Sample::Channel&, double textSize=0.04);
    void drawCmsLabels(int cmsprelim=1, double energy=8, double textSize=0.04);
    
    
    
    /// Samples to be analysed
    Samples samples_;
    
    /// Luminosity
    const double luminosity_;
    
    /// Map containing the Drell-Yan scale factors
    const DyScaleFactors::DyScaleFactorMap m_dyScaleFactors_;
    
    /// Draw mode for Higgs
    const DrawMode drawMode_;
    
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
    
    TString outpathPlots_;
    TString subfolderChannel_;
    TString subfolderSpecial_;
    
    
};



namespace Tools{
    
    /// Convert a DrawMode from string to typedef
    Plotter::DrawMode convertDrawMode(const std::string& drawMode);
    
    /// Convert a DrawMode from typedef to string
    std::string convertDrawMode(const Plotter::DrawMode& drawMode);
}





#endif







