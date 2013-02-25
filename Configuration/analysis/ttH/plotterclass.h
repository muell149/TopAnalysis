#ifndef plotterclass_h
#define plotterclass_h

#include <TString.h>
#include <TH1.h>
#include <TGraphAsymmErrors.h>
#include <vector>
#include <map>
#include <set>
// HIGGSING
//#include "utils.h"
#include "../diLeptonic/utils.h"
#include <TH2.h>
// ENDHIGGSING

class TGraphErrors;
class TLegend;

class Plotter {

public:
    Plotter();
    void   setOptions(TString name_, TString specialComment_, TString YAxis_, TString XAxis_, int rebin_, bool doDYScale_, bool logX_, bool logY_, double ymin_, double ymax_, double rangemin_, double rangemax_, int bins_, std::vector<double> XAxisbins_, std::vector<double> XAxisbinCenters_);
    void   setDataSet(std::vector<TString>, std::vector<double>, std::vector<TString>, std::vector<int>, TString);
    void   setDataSet(TString, TString);
    bool   fillHisto();
    void   setStyle(TH1*, unsigned int, bool = false);
    void   preunfolding(TString Channel="", TString Systematic="");
    void   write(TString, TString);
    void   setLumi(double);
    
    void MakeTable();



    void DYScaleFactor(TString);


    TLegend* getNewLegend();
    TLegend* getNewLegendpre();

    TH1F* ConvertGraphToHisto(TGraphErrors *pGraph);
    TH1F* reBinTH1FIrregularNewBinning(TH1F *histoOldBinning, TString plotname, bool rescale);

    //IVAN's Scaling Code
    void ApplyFlatWeights(TH1* varhists,   const double weight);
    double SampleXSection(const TString& filename);
    double CalcLumiWeight(const TString& WhichSample);
    std::vector<TString> InputFileList(TString mode, TString Systematic);

    // DAVID
    TLegend* ControlLegend(int HistsSize, TH1* drawhists[], std::vector<TString> legends, TLegend *leg);


private:

    TString name;

    TString specialComment;
    int bins, datafiles, rebin;
    double rangemin, rangemax, ymin, ymax;

    std::vector<TString> dataset, datasetUp, datasetDown;
    std::vector<double> scales;
    std::vector<TString> legends, legendsSyst;
    std::vector<int> colors;
    std::vector<double> XAxisbins, XAxisbinCenters;

    std::vector<double> DYScale;
    TString DYEntry;
    TString YAxis;
    TString XAxis;
    TString channel;
    int channelType; //0=ee 1==mumu 2==emu 3==combined  

    std::vector<TH1D> hists;
    std::vector<TH1D> systhistsUp;
    std::vector<TH1D> systhistsDown;

    bool initialized, logX, logY, doDYScale;
    double lumi;
    int signalHist;

    std::vector<TString> channelLabel;

    double SignalEventswithWeight;
    
    TString outpathPlots;
    TString subfolderChannel;
    TString subfolderSpecial;

    static const double topxsec;
    RootFileReader *fileReader;
    void DrawDecayChLabel(TString decaychannel="", double textSize=0.04);
    void DrawCMSLabels(int cmsprelim=true, double energy=8, double textSize=0.04);

};

#endif
