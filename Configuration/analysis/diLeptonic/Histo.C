#include "Histo.h"

void Histo::MakePlots(){

  gROOT->SetBatch(kTRUE);

  std::vector<double> Xbins;
  std::vector<double> binCenters;
  Plotter h_XSecPlot;
  h_XSecPlot.setOptions("HypjetMultiXSec","N_{Events}","N_{jets}", true, false, false, 0.0, 0, 0, 0,0,Xbins, binCenters);
  h_XSecPlot.DYScaleFactor();
  h_XSecPlot.setDataSet("mumu");
  h_XSecPlot.fillHisto();
  h_XSecPlot.PlotXSec();
  h_XSecPlot.MakeTable();
  h_XSecPlot.setDataSet("emu");
  h_XSecPlot.fillHisto();
  h_XSecPlot.PlotXSec();
  h_XSecPlot.MakeTable();
  h_XSecPlot.setDataSet("ee");
  h_XSecPlot.fillHisto();
  h_XSecPlot.PlotXSec();
  h_XSecPlot.MakeTable();
  h_XSecPlot.setDataSet("combined");
  h_XSecPlot.fillHisto();
  h_XSecPlot.PlotXSec();
  h_XSecPlot.MakeTable();
  //  h_XSecPlot.PlotXSec();

  string histolist = "HistoList";
  ifstream HistStream;
  HistStream.open(histolist.c_str());

  while(!HistStream.eof()){
  	
  	// Read HistoList-File
    TString name, YAxis, XAxis;
    bool logX, logY, DYScale;
    int bins;
    double ymin, ymax, xmin, xmax;
    HistStream>>name>>YAxis>>XAxis>>DYScale>>logX>>logY>>ymin>>ymax>>xmin>>xmax>>bins;
    
    // Avoid running over empty lines in 'HistoList'-File
    if ( name.CompareTo("") == 0 ) continue;
    
    // Create Plotter 
    Plotter h_generalPlot;
    Xbins.clear();
    binCenters.clear();
    
     
 
    for(int i = 0; i < bins+1; i++){
      double temp;
      HistStream>>temp; 
      Xbins.push_back(temp);
    }
    for(int i = 0; i < bins; i++){//only until bincenter code is finalized
      double temp;
      HistStream>>temp;
      binCenters.push_back(temp);
    }
    
    /////////////////////////////////////////////////////
    /////////   UNFOLDING OPTIONS     ///////////////////
    /////////////////////////////////////////////////////
    
    // Unfolding Options
    bool doSVD = true;
    TString outpath = "";
    h_generalPlot.UnfoldingOptions(doSVD);
    h_generalPlot.SetOutpath("");
    
    /////////////////////////////////////////////////////
    /////////////////////////////////////////////////////
    /////////////////////////////////////////////////////
    
    h_generalPlot.setOptions(name,YAxis,XAxis, DYScale, logX, logY, ymin, ymax, xmin, xmax, bins, Xbins, binCenters);
    h_generalPlot.DYScaleFactor();
    h_generalPlot.setDataSet("mumu");
    h_generalPlot.fillHisto();
    h_generalPlot.write();  
    h_generalPlot.PlotDiffXSec(); 
    h_generalPlot.DYScaleFactor();
    h_generalPlot.setDataSet("emu");
    h_generalPlot.fillHisto();
    h_generalPlot.write();
    h_generalPlot.PlotDiffXSec();
    h_generalPlot.DYScaleFactor();
    h_generalPlot.setDataSet("ee");
    h_generalPlot.fillHisto();
    h_generalPlot.write();
    h_generalPlot.PlotDiffXSec();
    h_generalPlot.DYScaleFactor();
    h_generalPlot.setDataSet("combined");
    h_generalPlot.fillHisto();
    h_generalPlot.write();
    h_generalPlot.PlotDiffXSec();
    
  }

  
  string controlhistolist = "HistoList_control";
  ifstream controlHistStream;
  controlHistStream.open(controlhistolist.c_str());

  while(!controlHistStream.eof()){
  	// Read HistoList-File
    TString name, YAxis, XAxis;
    bool logX, logY, DYScale;
    int bins;
    double ymin, ymax, xmin, xmax;
    controlHistStream>>name>>YAxis>>XAxis>>DYScale>>logX>>logY>>ymin>>ymax>>xmin>>xmax>>bins;

    // Avoid running over empty lines in 'HistoList'-File
    if ( name.CompareTo("") == 0 ) continue;
    // Create Plotter 
    Plotter h_generalPlot;
    Xbins.clear();
    binCenters.clear();
    
    for(int i = 0; i < bins+1; i++){
      double temp;
      controlHistStream>>temp; 
      Xbins.push_back(temp);
    }
    for(int i = 0; i < bins; i++){//only until bincenter code is finalized
      double temp;
      controlHistStream>>temp;
      binCenters.push_back(temp);
    }
    
    /////////////////////////////////////////////////////
    /////////   UNFOLDING OPTIONS     ///////////////////
    /////////////////////////////////////////////////////
    
    // Unfolding Options
    bool doSVD = false; 
    TString outpath = "";
    h_generalPlot.UnfoldingOptions(doSVD);
    h_generalPlot.SetOutpath("");
    
    /////////////////////////////////////////////////////
    /////////////////////////////////////////////////////
    ///////////////////////////////////////////////////// 
    

    h_generalPlot.setOptions(name,YAxis,XAxis, DYScale, logX, logY, ymin, ymax, xmin, xmax, bins, Xbins, binCenters);
    h_generalPlot.DYScaleFactor();
    h_generalPlot.setDataSet("mumu");
    h_generalPlot.fillHisto();
    h_generalPlot.write();
    h_generalPlot.DYScaleFactor();
    h_generalPlot.setDataSet("emu");
    h_generalPlot.fillHisto();
    h_generalPlot.write();
    h_generalPlot.DYScaleFactor();
    h_generalPlot.setDataSet("ee");
    h_generalPlot.fillHisto();
    h_generalPlot.write();
    h_generalPlot.DYScaleFactor();
    h_generalPlot.setDataSet("combined");
    h_generalPlot.fillHisto();
    h_generalPlot.write();
  }
  return;
}

Histo::Histo(){
  MakePlots();
}

Histo::~Histo(){
}

