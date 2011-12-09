#define Histo_cxx

#include "Histo.h"


void Histo::MakePlots(){
  //  h_HypTTbarMass.setOptions("","HypTTBarMass","Events", 0, 0, 0, 1);
  //h_HypTTbarMass.fillHisto();
  //h_HypTTbarMass.setDataSet("mumu");
  //h_HypTTbarMass.write();

  h_jetMulti.setOptions("","jetMulti","Events", 0, 0, 0, 1);
  h_jetMulti.setDataSet("mumu");
  h_jetMulti.fillHisto();
  h_jetMulti.CalcXSec();
  h_jetMulti.write();

  h_jetMulti.setDataSet("ee");
  h_jetMulti.fillHisto();
  h_jetMulti.CalcXSec();
  h_jetMulti.write();

  h_jetMulti.setDataSet("emu");
  h_jetMulti.fillHisto();
  h_jetMulti.CalcXSec();
  h_jetMulti.write();

  h_jetMulti.setDataSet("combined");
  h_jetMulti.fillHisto();
  h_jetMulti.CalcXSec();
  h_jetMulti.write();

  h_HypTTbarMass.setOptions("","HypTTBarMass","Events", 0, 0, 0, 1);
  h_HypTTbarMass.setDataSet("mumu");
  h_HypTTbarMass.fillHisto();
  h_HypTTbarMass.PlotDiffXSec();
  h_HypTTbarMass.write();

  h_HypTTbarMass.setDataSet("ee");
  h_HypTTbarMass.fillHisto();
  h_HypTTbarMass.PlotDiffXSec();
  h_HypTTbarMass.write();

  h_HypTTbarMass.setDataSet("emu");
  h_HypTTbarMass.fillHisto();
  h_HypTTbarMass.PlotDiffXSec();

  h_HypTTbarMass.write();
  h_HypTTbarMass.setDataSet("combined");
  h_HypTTbarMass.fillHisto();
  h_HypTTbarMass.PlotDiffXSec();
  h_HypTTbarMass.write();
  
  /*AllDIM.setOptions("","Allh1","Events", 0, 0, 0, 1);
  AllDIM.setDataSet("mumu");
  AllDIM.fillHisto();
  AllDIM.write();

  GenDIM.setOptions("","GenAll","Events", 0, 0, 0, 1);
  GenDIM.setDataSet("mumu");
  GenDIM.fillHisto();
  GenDIM.write();

  InDIM.setOptions("","Zh1","Events", 0, 0, 0, 1);
  InDIM.setDataSet("mumu");
  InDIM.fillHisto();
  InDIM.write();

  OutDIM.setOptions("","TTh1","Events", 0, 0, 0, 1);
  OutDIM.setDataSet("mumu");
  OutDIM.fillHisto();
  OutDIM.write();

  h_HypTopMass.setOptions("","HypTopMass","Events", 0, 0, 0, 1);
  h_HypTopMass.fillHisto();
  h_HypTopMass.setDataSet("mumu");
  //  h_HypTopMass.PlotDiffXSec();
  h_HypTopMass.write();

  h_HypAntiTopMass.setOptions("","HypAntiTopMass","Events", 0, 0, 0, 1);
  h_HypAntiTopMass.fillHisto();
  h_HypAntiTopMass.setDataSet("mumu");
  h_HypAntiTopMass.write();

  h_HypToppT.setOptions("","HypToppT","Events", 0, 0, 0, 1);
  h_HypToppT.fillHisto();
  h_HypToppT.setDataSet("mumu");
  //  h_HypToppT.PlotDiffXSec();
  h_HypToppT.write();

  h_HypAntiToppT.setOptions("","HypAntiToppT","Events", 0, 0, 0, 1);
  h_HypAntiToppT.fillHisto();
  h_HypAntiToppT.setDataSet("mumu");
  h_HypAntiToppT.write();

  h_HypWPluspT.setOptions("","HypWPluspT","Events", 0, 0, 0, 1);
  h_HypWPluspT.fillHisto();
  h_HypWPluspT.setDataSet("mumu");
  h_HypWPluspT.write();

  h_HypWMinuspT.setOptions("","HypWMinuspT","Events", 0, 0, 0, 1);
  h_HypWMinuspT.fillHisto();
  h_HypWMinuspT.setDataSet("mumu");
  h_HypWMinuspT.write();

  h_HypLeptonpT.setOptions("","HypLeptonpT","Events", 0, 0, 0, 1);
  h_HypLeptonpT.fillHisto();
  h_HypLeptonpT.setDataSet("mumu");
  h_HypLeptonpT.write();

  h_HypAntiLeptonpT.setOptions("","HypAntiLeptonpT","Events", 0, 0, 0, 1);
  h_HypAntiLeptonpT.fillHisto();
  h_HypAntiLeptonpT.setDataSet("mumu");
  h_HypAntiLeptonpT.write();

  h_HypBpT.setOptions("","HypBpT","Events", 0, 0, 0, 1);
  h_HypBpT.fillHisto();
  h_HypBpT.setDataSet("mumu");
  h_HypBpT.write();

  h_HypAntiBpT.setOptions("","HypAntiBpT","Events", 0, 0, 0, 1);
  h_HypAntiBpT.fillHisto();
  h_HypAntiBpT.setDataSet("mumu");
  h_HypAntiBpT.write();

  h_HypNeutrinopT.setOptions("","HypNeutrinopT","Events", 0, 0, 0, 1);
  h_HypNeutrinopT.fillHisto();
  h_HypNeutrinopT.setDataSet("mumu");
  h_HypNeutrinopT.write();

  h_HypAntiNeutrinopT.setOptions("","HypAntiNeutrinopT","Events", 0, 0, 0, 1);
  h_HypAntiNeutrinopT.fillHisto();
  h_HypAntiNeutrinopT.setDataSet("mumu");
  h_HypAntiNeutrinopT.write();


  h_HypTopEta.setOptions("","HypTopEta","Events", 0, 0, 0, 1);
  h_HypTopEta.fillHisto();
  h_HypTopEta.setDataSet("mumu");
  h_HypTopEta.write();

  h_HypAntiTopEta.setOptions("","HypAntiTopEta","Events", 0, 0, 0, 1);
  h_HypAntiTopEta.fillHisto();
  h_HypAntiTopEta.setDataSet("mumu");
  h_HypAntiTopEta.write();

  h_HypWPlusEta.setOptions("","HypWPlusEta","Events", 0, 0, 0, 1);
  h_HypWPlusEta.fillHisto();
  h_HypWPlusEta.setDataSet("mumu");
  h_HypWPlusEta.write();

  h_HypWMinusEta.setOptions("","HypWMinusEta","Events", 0, 0, 0, 1);
  h_HypWMinusEta.fillHisto();
  h_HypWMinusEta.setDataSet("mumu");
  h_HypWMinusEta.write();

  h_HypLeptonEta.setOptions("","HypLeptonEta","Events", 0, 0, 0, 1);
  h_HypLeptonEta.fillHisto();
  h_HypLeptonEta.setDataSet("mumu");
  h_HypLeptonEta.write();

  h_HypAntiLeptonEta.setOptions("","HypAntiLeptonEta","Events", 0, 0, 0, 1);
  h_HypAntiLeptonEta.fillHisto();
  h_HypAntiLeptonEta.setDataSet("mumu");
  h_HypAntiLeptonEta.write();

  h_HypBEta.setOptions("","HypBEta","Events", 0, 0, 0, 1);
  h_HypBEta.fillHisto();
  h_HypBEta.setDataSet("mumu");
  h_HypBEta.write();

  h_HypAntiBEta.setOptions("","HypAntiBEta","Events", 0, 0, 0, 1);
  h_HypAntiBEta.fillHisto();
  h_HypAntiBEta.setDataSet("mumu");
  h_HypAntiBEta.write();

  h_HypNeutrinoEta.setOptions("","HypNeutrinoEta","Events", 0, 0, 0, 1);
  h_HypNeutrinoEta.fillHisto();
  h_HypNeutrinoEta.setDataSet("mumu");
  h_HypNeutrinoEta.write();

  h_HypAntiNeutrinoEta.setOptions("","HypAntiNeutrinoEta","Events", 0, 0, 0, 1);
  h_HypAntiNeutrinoEta.fillHisto();
  h_HypAntiNeutrinoEta.setDataSet("mumu");
  h_HypAntiNeutrinoEta.write();

  h_HypTopE.setOptions("","HypTopE","Events", 0, 0, 0, 1);
  h_HypTopE.fillHisto();
  h_HypTopE.setDataSet("mumu");
  h_HypTopE.write();

  h_HypAntiTopE.setOptions("","HypAntiTopE","Events", 0, 0, 0, 1);
  h_HypAntiTopE.fillHisto();
  h_HypAntiTopE.setDataSet("mumu");
  h_HypAntiTopE.write();

  h_HypWPlusE.setOptions("","HypWPlusE","Events", 0, 0, 0, 1);
  h_HypWPlusE.fillHisto();
  h_HypWPlusE.setDataSet("mumu");
  h_HypWPlusE.write();

  h_HypWMinusE.setOptions("","HypWMinusE","Events", 0, 0, 0, 1);
  h_HypWMinusE.fillHisto();
  h_HypWMinusE.setDataSet("mumu");
  h_HypWMinusE.write();

  h_HypLeptonE.setOptions("","HypLeptonE","Events", 0, 0, 0, 1);
  h_HypLeptonE.fillHisto();
  h_HypLeptonE.setDataSet("mumu");
  h_HypLeptonE.write();

  h_HypAntiLeptonE.setOptions("","HypAntiLeptonE","Events", 0, 0, 0, 1);
  h_HypAntiLeptonE.fillHisto();
  h_HypAntiLeptonE.setDataSet("mumu");
  h_HypAntiLeptonE.write();

  h_HypBE.setOptions("","HypBE","Events", 0, 0, 0, 1);
  h_HypBE.fillHisto();
  h_HypBE.setDataSet("mumu");
  h_HypBE.write();

  h_HypAntiBE.setOptions("","HypAntiBE","Events", 0, 0, 0, 1);
  h_HypAntiBE.fillHisto();
  h_HypAntiBE.setDataSet("mumu");
  h_HypAntiBE.write();

  h_HypNeutrinoE.setOptions("","HypNeutrinoE","Events", 0, 0, 0, 1);
  h_HypNeutrinoE.fillHisto();
  h_HypNeutrinoE.setDataSet("mumu");
  h_HypNeutrinoE.write();

  h_HypAntiNeutrinoE.setOptions("","HypAntiNeutrinoE","Events", 0, 0, 0, 1);
  h_HypAntiNeutrinoE.fillHisto();
  h_HypAntiNeutrinoE.setDataSet("mumu");
  h_HypAntiNeutrinoE.write();
  */
  return;


}

Histo::Histo(){MakePlots();}

Histo::~Histo(){}
