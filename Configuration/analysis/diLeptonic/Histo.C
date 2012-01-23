#define Histo_cxx

#include "Histo.h"
#include <fstream>
#include <string>


void Histo::MakePlots(){

  std::vector<double> Xbins;
  std::vector<double> binCenters;
  h_generalPlot.setOptions("jetMultiXSec","N_{Events}","N_{jets}", false, false, 0.1, 0, 0, 0,0,Xbins, binCenters);
  h_generalPlot.DYScaleFactor();
  h_generalPlot.setDataSet("mumu");
  h_generalPlot.fillHisto();
  h_generalPlot.CalcXSec();
  h_generalPlot.setDataSet("emu");
  h_generalPlot.fillHisto();
  h_generalPlot.CalcXSec();
  h_generalPlot.setDataSet("ee");
  h_generalPlot.fillHisto();
  h_generalPlot.CalcXSec();
  h_generalPlot.setDataSet("combined");
  h_generalPlot.fillHisto();
  h_generalPlot.CalcXSec();
  h_generalPlot.PlotXSec();
  
  string lumifile = "HistoList";
  ifstream HistStream;
  HistStream.open(lumifile.c_str());

  while(!HistStream.eof()){
    TString name, YAxis, XAxis;
    bool logX, logY;
    int bins;
    double ymin, ymax, xmin, xmax;
    Xbins.clear();binCenters.clear();
  
    HistStream>>name>>YAxis>>XAxis>>logX>>logY>>ymin>>ymax>>xmin>>xmax>>bins;
    cout<<"bins: "<<bins<<endl;
    for(int i = 0; i < bins+1; i++){
      double temp;
      HistStream>>temp; 
      Xbins.push_back(temp);
      cout<<Xbins[i]<<endl;
    }
    for(int i = 0; i < bins; i++){//only until bincenter code is finalized
      double temp;
      HistStream>>temp;
      binCenters.push_back(temp);
      cout<<binCenters[i]<<endl;
    }
    
    //  h_generalPlot.setOptions("","DIMFull","N_{Events}","M_{#mu#mu}", false, true, 0, 0.1, 0, 0, 0);//Figure 2
    //h_generalPlot.setOptions("","jetMulti","N_{Events}","N_{jets}", false, true, 0, 0.1, 0, 0, 0);//Figure 3
    //  h_generalPlot.setOptions("","LeptonpT","N_{Events}","p_{T,#mu}[GeV]", false, false, 0, 0., 0, 0, 0);//Figure 5
    //  h_generalPlot.setOptions("","LeptonEta","N_{Events}","#eta_{#mu}", false, false, 0, 0., 0, 0, 0);//Figure 6
    //h_generalPlot.setOptions("","jetMulti","N_{Events}","N_{jets}", false, false, 0, 0.0, 0, 0, 0);//Figure 7
    //  h_generalPlot.setOptions("","jetpT","N_{Events}","p_{T,jet}[GeV]", false, false, 0, 0., 0, 0, 0);//Figure 8
    //h_generalPlot.setOptions("","jetHT","N_{Events}","H_{T,all jets}[GeV]", false, true, 0, 0.1, 0, 0, 0);//Figure 9
    //  h_generalPlot.setOptions("","BjetMulti","N_{Events}","N_{tags, TCHEL}", false, false, 0, 0.0, 0, 0, 0);//Figure 10
    //  h_generalPlot.setOptions("","Allh1","N_{Events}","M_{#mumu}", false, false, 0, 0.0, 0, 0, 0);//Figure 11
    //h_generalPlot.setOptions("LeptonpT","N_{Events}","p_{T}^{l^{+}andl^{-}}", false, true, 0, 0.0001, 0, 0, 0);//Figure 12
    h_generalPlot.setOptions(name,YAxis,XAxis, logX, logY, ymin, ymax, xmin, xmax, bins, Xbins, binCenters);//Figure 12
    h_generalPlot.DYScaleFactor();
    h_generalPlot.setDataSet("mumu");
    h_generalPlot.fillHisto();
    h_generalPlot.PlotDiffXSec();
    h_generalPlot.write();
    /*  h_generalPlot.DYScaleFactor();
	h_generalPlot.setDataSet("emu");
	h_generalPlot.fillHisto();
	h_generalPlot.PlotDiffXSec();
	h_generalPlot.write();
	h_generalPlot.DYScaleFactor();
	h_generalPlot.setDataSet("ee");
	h_generalPlot.fillHisto();
	h_generalPlot.PlotDiffXSec();
	h_generalPlot.write();
	h_generalPlot.DYScaleFactor();
	h_generalPlot.setDataSet("combined");
	h_generalPlot.fillHisto();
	h_generalPlot.PlotDiffXSec();
	h_generalPlot.write();
    */
    
  }
  return;
}

Histo::Histo(){
  MakePlots();
}

Histo::~Histo(){
}
