#include "Histo.h"

void Histo::MakePlots(){

  gROOT->SetBatch(kTRUE);

  std::vector<double> Xbins;
  std::vector<double> binCenters;
  /*  Plotter h_XSecPlot;
  h_XSecPlot.setOptions("jetMultiXSec","N_{Events}","N_{jets}", false, false, 0.0, 0, 0, 0,0,Xbins, binCenters);
  h_XSecPlot.DYScaleFactor();
  h_XSecPlot.setDataSet("mumu");
  h_XSecPlot.fillHisto();
  h_XSecPlot.CalcXSec();
  h_XSecPlot.setDataSet("emu");
  h_XSecPlot.fillHisto();
  h_XSecPlot.CalcXSec();
  h_XSecPlot.setDataSet("ee");
  h_XSecPlot.fillHisto();
  h_XSecPlot.CalcXSec();
  h_XSecPlot.setDataSet("combined");
  h_XSecPlot.fillHisto();
  h_XSecPlot.CalcXSec();
  h_XSecPlot.PlotXSec();
  */
  string histolist = "HistoList";
  ifstream HistStream;
  HistStream.open(histolist.c_str());

  while(!HistStream.eof()){
  	
  	// Read HistoList-File
    TString name, YAxis, XAxis;
    bool logX, logY;
    int bins;
    double ymin, ymax, xmin, xmax;
    HistStream>>name>>YAxis>>XAxis>>logX>>logY>>ymin>>ymax>>xmin>>xmax>>bins;
    
    // Avoid running over empty lines in 'HistoList'-File
    if ( name.CompareTo("") == 0 ) continue;
    
    // Create Plotter 
    Plotter h_generalPlot;
    Xbins.clear();binCenters.clear();
    
     
 
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
    
    // Unfolding Options
    bool doSVD = false;
    bool unfoldingPlotsToPs = false;
    bool unfoldingPlotsToRoot = false;
    TString outpath = "";
    h_generalPlot.UnfoldingOptions(doSVD, unfoldingPlotsToPs, unfoldingPlotsToRoot);
    h_generalPlot.SetOutpath("");
    
    
    h_generalPlot.setOptions(name,YAxis,XAxis, logX, logY, ymin, ymax, xmin, xmax, bins, Xbins, binCenters);
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
    bool logX, logY;
    int bins;
    double ymin, ymax, xmin, xmax;
    controlHistStream>>name>>YAxis>>XAxis>>logX>>logY>>ymin>>ymax>>xmin>>xmax>>bins;

    // Avoid running over empty lines in 'HistoList'-File
    if ( name.CompareTo("") == 0 ) continue;
    // Create Plotter 
    Plotter h_generalPlot;
    Xbins.clear();binCenters.clear();
    
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
    
    //  h_generalPlot.setOptions("","DIMFull","N_{Events}","M_{#mu#mu}", false, true, 0, 0.1, 0, 0, 0);//Figure 2
    //h_generalPlot.setOptions("","jetMulti","N_{Events}","N_{jets}", false, true, 0, 0.1, 0, 0, 0);//Figure 3
    //  h_generalPlot.setOptions("","LeptonpT","N_{Events}","p_{T,#mu}[GeV]", false, false, 0, 0., 0, 0, 0);//Figure 5
    //  h_generalPlot.setOptions("","LeptonEta","N_{Events}","#eta_{#mu}", false, false, 0, 0., 0, 0, 0);//Figure 6
    //h_generalPlot.setOptions("","jetMulti","N_{Events}","N_{jets}", false, false, 0, 0.0, 0, 0, 0);//Figure 7
    //  h_generalPlot.setOptions("","jetpT","N_{Events}","p_{T,jet}[GeV]", false, false, 0, 0., 0, 0, 0);//Figure 8
    //h_generalPlot.setOptions("","jetHT","N_{Events}","H_{T,all jets}[GeV]", false, true, 0, 0.1, 0, 0, 0);//Figure 9
    //  h_generalPlot.setOptions("","BjetMulti","N_{Events}","N_{tags, TCHEL}", false, false, 0, 0.0, 0, 0, 0);//Figure 10
    //  h_generalPlot.setOptions("","Allh1","N_{Events}","M_{#mumu}", false, false, 0, 0.0, 0, 0, 0);//Figure 11
    //h_generalPlot.setOptions("LeptonpT","N_{Events}","p_{T}^{l^{+}andl^{-}}", false, true, 0, 0.0001, 0, 0, 0);//Figure 12/Figure 12

    // Unfolding Options
    bool doSVD = false;
    bool unfoldingPlotsToPs = false;
    bool unfoldingPlotsToRoot = false;
    TString outpath = "";
    h_generalPlot.UnfoldingOptions(doSVD, unfoldingPlotsToPs, unfoldingPlotsToRoot);
    h_generalPlot.SetOutpath("");

    h_generalPlot.setOptions(name,YAxis,XAxis, logX, logY, ymin, ymax, xmin, xmax, bins, Xbins, binCenters);
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
