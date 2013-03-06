#ifndef plotterclass_h
#define plotterclass_h

#include <TString.h>
#include <TH1.h>
#include <TGraphAsymmErrors.h>
#include <vector>
#include <map>
#include <set>
#include <TH2.h>

#include "../diLeptonic/utils.h"
#include "samples.h"


class TGraphErrors;
class TLegend;

class Plotter {

public:
    enum DrawMode{stacked, overlaid, scaledoverlaid, undefined};
    
    typedef std::pair<Sample, TH1D*> SampleHistPair;
    
    Plotter();
    void setOptions(TString, TString, TString, TString, int, bool, bool, bool, double, double, double, double, int, std::vector<double>, std::vector<double>);
    void write(Sample::Channel, Sample::Systematic, DrawMode, std::vector<Sample>);
    void setLumi(double);
    
    
    void MakeTable();



    void DYScaleFactor(TString);



    //IVAN's Scaling Code
    double SampleXSection(const TString& filename);
    double CalcLumiWeight(const TString& WhichSample);
    std::vector<TString> InputFileList(const Sample::Channel& channel, const Sample::Systematic& systematic);

    

private:
    TLegend* ControlLegend(std::vector<SampleHistPair>& v_sampleHistPair, TLegend* leg, bool drawHiggsOverlaid, std::vector<TString> v_higgsLabel);
    
    
    void setStyle(SampleHistPair&, bool =false);
    
    bool prepareDataset(Sample::Channel&, Sample::Systematic&, std::vector<Sample>&);
    
    void drawDecayChannelLabel(const Sample::Channel&, double textSize=0.04);
    void drawCmsLabels(int cmsprelim=1, double energy=8, double textSize=0.04);
    
    TString name_;

    TString specialComment_;
    int bins_, rebin_;
    double rangemin_, rangemax_, ymin_, ymax_;

    // The variable scales_ is not used at all...
    std::vector<double> scales_;
    std::vector<double> XAxisbins_, XAxisbinCenters_;

    std::vector<double> DYScale_;
    TString DYEntry_;
    TString YAxis_;
    TString XAxis_;
    int channelType_; //0=ee 1==mumu 2==emu 3==combined  


    // The variable logX_ is not used at all...
    bool logX_, logY_, doDYScale_;
    double lumi_;

    std::vector<TString> channelLabel_;

    TString outpathPlots_;
    TString subfolderChannel_;
    TString subfolderSpecial_;
    
    // Could probably replace topxsec_ by fixed value
    static const double topxsec_;
    RootFileReader *fileReader_;
    
    std::vector<SampleHistPair> v_sampleHistPair_;
};

#endif
