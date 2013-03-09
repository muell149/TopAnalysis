#ifndef plotterclass_h
#define plotterclass_h

#include <TString.h>
#include <TH1.h>
#include <TGraphAsymmErrors.h>
#include <vector>
#include <map>
#include <set>
#include <TH2.h>
#include <TH1D.h>

#include "../diLeptonic/utils.h"
#include "samples.h"
#include "dyScaleFactors.h"


class TGraphErrors;
class TLegend;


class Plotter {

public:
    
    enum DrawMode{stacked, overlaid, scaledoverlaid, undefined};
    
    Plotter(){};
    Plotter(const double& luminosity, DyScaleFactors::DyScaleFactorMap m_dyScaleFactors);
    ~Plotter(){};
    
    void setOptions(TString, TString, TString, TString, int, bool, bool, bool, double, double, double, double, int, std::vector<double>, std::vector<double>);
    void producePlots(Samples& samples, const DrawMode& drawMode);
    
private:
    
    bool prepareDataset(const Sample::Channel&, const Sample::Systematic&, const std::vector<Sample>&);

    void write(const Sample::Channel&, const Sample::Systematic&, const DrawMode&);
    
    TLegend* ControlLegend(std::vector<SampleHistPair>& v_sampleHistPair, TLegend* leg, bool drawHiggsOverlaid, std::vector<TString> v_higgsLabel);
    
    void setStyle(SampleHistPair&, bool =false);
    void drawDecayChannelLabel(const Sample::Channel&, double textSize=0.04);
    void drawCmsLabels(int cmsprelim=1, double energy=8, double textSize=0.04);
    
    
    
    /// Luminosity
    double luminosity_;
    
    /// Map containing the Drell-Yan scale factors
    DyScaleFactors::DyScaleFactorMap m_dyScaleFactors_;
    
    /// File reader for accessing specific histogram from given file
    RootFileReader *fileReader_;
    
    
    
    TString name_;
    
    int bins_, rebin_;
    double rangemin_, rangemax_, ymin_, ymax_;
    
    std::vector<double> XAxisbins_, XAxisbinCenters_;
    
    TString YAxis_;
    TString XAxis_;
    
    // The variable logX_ is not used at all...
    bool logX_, logY_, doDYScale_;
    
    
    
    
    std::vector<SampleHistPair> v_sampleHistPair_;
    
    TString outpathPlots_;
    TString subfolderChannel_;
    TString subfolderSpecial_;
    
    
};

#endif
