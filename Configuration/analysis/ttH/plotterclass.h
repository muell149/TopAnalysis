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
  
    Plotter();
    void   setOptions(TString, TString, TString, TString, int, bool, bool, bool, double, double, double, double, int, std::vector<double>, std::vector<double>);
    void   setDataSet(std::vector<TString>, std::vector<double>, std::vector<TString>, std::vector<int>, TString);
    void   setDataSet(Sample::Channel, TString);
    bool   fillHisto();
    void   setStyle(TH1*, unsigned int, bool = false);
    void   write(Sample::Channel, TString, DrawMode, std::vector<Sample>);
    void   setLumi(double);
    
    void MakeTable();



    void DYScaleFactor(TString);



    //IVAN's Scaling Code
    void ApplyFlatWeights(TH1* varhists,   const double weight);
    double SampleXSection(const TString& filename);
    double CalcLumiWeight(const TString& WhichSample);
    std::vector<TString> InputFileList(TString mode, TString Systematic);

    TLegend* ControlLegend(int HistsSize, TH1* drawhists[], std::vector<TString> legends, TLegend *leg, bool drawHiggsOverlaid, std::vector<TString> v_higgsLabel);


private:
    
    void DrawDecayChLabel(TString decaychannel="", double textSize=0.04);
    void DrawCMSLabels(int cmsprelim=true, double energy=8, double textSize=0.04);
    
    TString name_;

    TString specialComment_;
    int bins_, datafiles_, rebin_;
    double rangemin_, rangemax_, ymin_, ymax_;

    std::vector<TString> dataset_;
    // The variable scales_ is not used at all...
    std::vector<double> scales_;
    std::vector<TString> legends_;
    std::vector<int> colors_;
    std::vector<double> XAxisbins_, XAxisbinCenters_;

    std::vector<double> DYScale_;
    TString DYEntry_;
    TString YAxis_;
    TString XAxis_;
    int channelType_; //0=ee 1==mumu 2==emu 3==combined  

    std::vector<TH1D> hists_;

    // The variable logX_ is not used at all...
    bool initialized_, logX_, logY_, doDYScale_;
    double lumi_;

    std::vector<TString> channelLabel_;

    TString outpathPlots_;
    TString subfolderChannel_;
    TString subfolderSpecial_;
    
    // Could probably replace topxsec_ by fixed value
    static const double topxsec_;
    RootFileReader *fileReader_;
    
    
    std::vector<Sample> v_sample_;
};

#endif
