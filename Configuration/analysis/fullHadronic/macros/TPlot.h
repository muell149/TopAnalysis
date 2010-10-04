#include <map>
#include <vector>
#include <iostream>

#include <assert.h>

#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <THStack.h>
#include <TGaxis.h>

class Canvas
{
public:

  Canvas();
  Canvas(const Canvas& c);
  Canvas(TString t, TString x, bool logx, TString y, bool logy);
  /*
  Canvas(TString t, TString x, int r, bool logx, TString y, bool logy, TLegend* l);
  Canvas(TString t, TString x, int r, bool logx, TString y, bool logy, double minY, double maxY, TLegend* l);
  Canvas(TString t, TString x, int r, bool logx, double minX, double maxX, TString y, bool logy, TLegend* l);
  */
  Canvas(TString t, TString x, int r, bool logx, double minX, double maxX, TString y, bool logy, double minY, double maxY, TLegend* l);

  TCanvas* canv;
  TLegend* leg;
  TString title, xaxis, yaxis;
  bool xlog, ylog;
  int rebin;
  double xMin, xMax;
  double yMin, yMax;
  std::vector<TH1*> hists;
  THStack* stack;
  bool stats;
};

Canvas::Canvas(){
  canv = 0;
  hists.push_back(0);
  stack = new THStack();
  stats = true;
}

Canvas::Canvas(const Canvas& c){
  canv  = c.canv;
  hists = c.hists;
  title = c.title;
  xaxis = c.xaxis;
  yaxis = c.yaxis;
  xlog  = c.xlog;
  ylog  = c.ylog;
  rebin = c.rebin;
  xMin  = c.xMin;
  xMax  = c.xMax;
  yMin  = c.yMin;
  yMax  = c.yMax;
  stack = c.stack;
  stats = c.stats;
  leg   = c.leg;
}

Canvas::Canvas(TString t, TString x, int r, bool logx, double minX, double maxX, TString y, bool logy, double minY, double maxY, TLegend* l){
  canv = 0;

  hists.push_back(0);
  title = t;
  xaxis = x;
  yaxis = y;
  xlog  = logx;
  ylog  = logy;
  rebin = r;

  xMin = minX;
  xMax = maxX;
  yMin = minY;
  yMax = maxY;

  stack = new THStack(t.Data(),t.Data());
  stats = true;

  leg = l;
}
/*
Canvas::Canvas(TString t, TString x, int r, bool logx, double minX, double maxX, TString y, bool logy, TLegend* l){
  Canvas(t, x, r, logx, minX, maxX, y, logy, -1e300, 1e300, TLegend* l);
}

Canvas::Canvas(TString t, TString x, int r, bool logx, TString y, bool logy, double minY, double maxY, TLegend* l){
  Canvas(t, x, r, logx, -1e300, 1e300, y, logy, minY, maxY, TLegend* l);
}

Canvas::Canvas(TString t, TString x, int r, bool logx, TString y, bool logy, TLegend* l){
  Canvas(t, x, r, logx, -1e300, 1e300, y, logy, -1e300, 1e300, TLegend* l);
}
*/
Canvas::Canvas(TString t, TString x, bool logx, TString y, bool logy){
  Canvas(t, x, 1, logx, -1e300, 1e300, y, logy, -1e300, 1e300, 0);
  //Canvas(t, x, 1, logx, y, logy, 0);
}


// files and scaling factor to be used
std::vector< std::pair< TFile*, std::pair<TString, float> > >  files;

// files actually chosen to be plotted
TString whichFiles;

// lumi of data
double lumi;

// canvases to be drawn
std::map<TString,Canvas> canvases;

// legends
std::vector<TLegend*> legs;

// normalize all histogram to events in data
bool normalized;

void prepareEverything(bool norm = false){

  std::cout << "Preparing ..." << std::endl;

  normalized = norm;

  //  set root style
  gROOT->cd();
  gROOT->SetStyle("Plain");
  
  //  statistics visibility for all histogramms (for only one specific use hists[hist].SetStats(kTrue);)
  gStyle->SetOptStat(0);

  //  create legends to be filled later on
  legs.push_back(new TLegend(0.16, 0.73, 0.45, 0.92));
  legs.push_back(new TLegend(0.63, 0.73, 0.92, 0.92));
  legs.push_back(new TLegend(0.38, 0.73, 0.68, 0.92));
  legs.push_back(new TLegend(0.43, 0.49, 0.92, 0.92));
  legs.push_back(new TLegend(1.10, 1.10, 1.10, 1.10));
  legs.push_back(new TLegend(0.58, 0.63, 0.92, 0.92));
  legs.push_back(new TLegend(0.00, 0.00, 1.00, 1.00));
}

// choose samples to be shown and luminosity to normalize to
enum file{sig_nlo, sig_nlo_pf, bkg_nlo, bkg_nlo_pf, sig_mad, sig_mad_pf, bkg_mad, bkg_mad_pf, qcd_pyt, qcd_pyt_pf, qcd_mad, qcd_mad_pf, qcd_her, qcd_her_pf, data, data_pf};
void getFiles(float lumi_ = 50.){

  std::cout << "Start readind in files ..." << std::endl;

  lumi = lumi_;

  //  open input files and give names for legend entries and lumiweight, push_back empty string or 1 respectively if not needed!
  files.push_back(make_pair(new TFile("./cutFlow/sig_nlo.root"),    make_pair("t#bar{t} fullhad MC@NLO", (lumi_/100.*1.64365217496526e-2))));
  files.push_back(make_pair(new TFile("./cutFlow/sig_nlo_pf.root"), make_pair("t#bar{t} fullhad MC@NLO", (lumi_/100.*1.64365217496526e-2))));
  files.push_back(make_pair(new TFile("./cutFlow/bkg_nlo.root"),    make_pair("t#bar{t} other MC@NLO",   (lumi_/100.*1.64365217496526e-2))));
  files.push_back(make_pair(new TFile("./cutFlow/bkg_nlo_pf.root"), make_pair("t#bar{t} other MC@NLO",   (lumi_/100.*1.64365217496526e-2))));

  files.push_back(make_pair(new TFile("./cutFlow/sig_mad.root"),    make_pair("t#bar{t} fullhad MadGraph", (lumi_/100.*1.0988240560225e-2))));
  files.push_back(make_pair(new TFile("./cutFlow/sig_mad_pf.root"), make_pair("t#bar{t} fullhad MadGraph", (lumi_/100.*1.0988240560225e-2))));
  files.push_back(make_pair(new TFile("./cutFlow/bkg_mad.root"),    make_pair("t#bar{t} other MadGraph",   (lumi_/100.*1.0988240560225e-2))));
  files.push_back(make_pair(new TFile("./cutFlow/bkg_mad_pf.root"), make_pair("t#bar{t} other MadGraph",   (lumi_/100.*1.0988240560225e-2))));

  files.push_back(make_pair(new TFile("./cutFlow/QCD_pyt_offi.root"),    make_pair("QCD Pythia * 1.3", (lumi_/100.*1.3))));
  files.push_back(make_pair(new TFile("./cutFlow/QCD_pyt_offi_pf.root"), make_pair("QCD Pythia * 1.4", (lumi_/100.*1.4))));
  
  files.push_back(make_pair(new TFile("./cutFlow/QCD_mad.root"),    make_pair("QCD MadGraph * 2.6", (lumi_/100.*2.6))));
  files.push_back(make_pair(new TFile("./cutFlow/QCD_mad_pf.root"), make_pair("QCD MadGraph * 2.5", (lumi_/100.*2.5))));

  files.push_back(make_pair(new TFile("./cutFlow/QCD_her.root"),    make_pair("QCD Herwig * 0.7", (lumi_/100.*0.7))));
  files.push_back(make_pair(new TFile("./cutFlow/QCD_her_pf.root"), make_pair("QCD Herwig * 0.9", (lumi_/100.*0.9))));

  // for naming of data in the legend always LAST entry in the files vector is taken
  files.push_back(make_pair(new TFile("./cutFlow/data.root"),    make_pair("CMS Data 3.1 pb^{-1}", 1.)));
  files.push_back(make_pair(new TFile("./cutFlow/data_pf.root"), make_pair("CMS Data 3.1 pb^{-1}", 1.)));

  std::cout << "Finished reading in files" << std::endl;
}

void addCanvas(TString canvas, TString title, const char* xAxis, int xRebin, bool xAxisLog, double xMin, double xMax, const char* yAxis, bool yAxisLog, double yMin, double yMax, unsigned int legend){

  //  choose canvases which should be ((drawn and their titles) and the legend to be drawn to this canvas) 
  //  choose axes-titles and log-scale for axes (first x, second y)

  canvases[canvas] = Canvas(title, xAxis, xRebin, xAxisLog, xMin, xMax, yAxis, yAxisLog, yMin, yMax, legs.at(legend));
  
}

void addCanvas(TString canvas, TString title, const char* xAxis, bool xAxisLog, double xMin, double xMax, const char* yAxis, bool yAxisLog, double yMin, double yMax, unsigned int legend){
  addCanvas(canvas, title, xAxis, 1, xAxisLog, xMin, xMax, yAxis, yAxisLog, yMin, yMax, legend);
}
void addCanvas(TString canvas, TString title, const char* xAxis, int xRebin, bool xAxisLog, double xMin, double xMax, const char* yAxis, bool yAxisLog, unsigned int legend){
  addCanvas(canvas, title, xAxis, xRebin, xAxisLog, xMin, xMax, yAxis, yAxisLog, -1e300, 1e300, legend);
}
void addCanvas(TString canvas, TString title, const char* xAxis, int xRebin, bool xAxisLog, const char* yAxis, bool yAxisLog, double yMin, double yMax, unsigned int legend){
  addCanvas(canvas, title, xAxis, xRebin, xAxisLog, -1e300, 1e300, yAxis, yAxisLog, yMin, yMax, legend);
}
void addCanvas(TString canvas, TString title, const char* xAxis, int xRebin, bool xAxisLog, const char* yAxis, bool yAxisLog, unsigned int legend){
  addCanvas(canvas, title, xAxis, xRebin, xAxisLog, -1e300, 1e300, yAxis, yAxisLog, -1e300, 1e300, legend);
}
void addCanvas(TString canvas, TString title, const char* xAxis, bool xAxisLog, double xMin, double xMax, const char* yAxis, bool yAxisLog, unsigned int legend){
  addCanvas(canvas, title, xAxis, 1, xAxisLog, xMin, xMax, yAxis, yAxisLog, -1e300, 1e300, legend);
}
void addCanvas(TString canvas, TString title, const char* xAxis, bool xAxisLog, const char* yAxis, bool yAxisLog, double yMin, double yMax, unsigned int legend){
  addCanvas(canvas, title, xAxis, 1, xAxisLog, -1e300, 1e300, yAxis, yAxisLog, yMin, yMax, legend);
}
void addCanvas(TString canvas, TString title, const char* xAxis, bool xAxisLog, const char* yAxis, bool yAxisLog, unsigned int legend){
  addCanvas(canvas, title, xAxis, 1, xAxisLog, yAxis, yAxisLog, legend);
}
void addCanvas(TString canvas, const char* xAxis, const char* yAxis){
  addCanvas(canvas, "", xAxis, false, yAxis, false, 1);
}
void addCanvas(TString canvas){
  addCanvas(canvas, "", "", false, "", false, 1);
}

//  choose which histograms should be drawn
void addCanvs(TString canvases = "Stats"){

  std::cout << "Start plotting ..." << std::endl;

  if(canvases.Contains("dipl_norm")){
    addCanvas("tightLeadingJetQuality_0/cef"     , "", "f_{CE}"       , false, "jets"  , true , 4);
    addCanvas("tightLeadingJetQuality_0/chf"     , "", "f_{CH}"       , false, "jets"  , false, 4);
    addCanvas("tightLeadingJetQuality_0/nef"     , "", "f_{NE}"       , false, "jets"  , false, 4);
    addCanvas("tightLeadingJetQuality_0/nhf"     , "", "f_{NH}"       , false, "jets"  , true , 4);
    addCanvas("tightLeadingJetQuality_0/ncp"     , "", "n_{charged}"  , false, "jets"  , false, 3);
    addCanvas("tightLeadingJetQuality_0/emf"     , "", "f_{EM}"       , false, "jets"  , false, 4);
    addCanvas("tightLeadingJetQuality_0/fHPD_"   , "", "f_{HPD}"      , false, "jets"  , false, 3);
    addCanvas("tightLeadingJetQuality_0/n90Hits_", "", "n_{90}^{hits}", false, "jets"  , false, 4);
    addCanvas("tightLeadingJetQuality_0/n_"      , "", "n_{const}"    , false, "jets"  , false, 4);

    addCanvas("tightLeadingJetKinematics_0/eta"  , "", "#eta"         , false, "jets"  , true , 1);
  }

  if(canvases.Contains("dipl") && !canvases.Contains("dipl_norm")){
    
    addCanvas("tightLeadingJetQuality_1/cef"     , "", "f_{CE}"       , false, "jets", true , 4);
    addCanvas("tightLeadingJetQuality_1/chf"     , "", "f_{CH}"       , false, "jets", false, 4);
    addCanvas("tightLeadingJetQuality_1/nef"     , "", "f_{NE}"       , false, "jets", false, 4);
    addCanvas("tightLeadingJetQuality_1/nhf"     , "", "f_{NH}"       , false, "jets", true , 4);
    addCanvas("tightLeadingJetQuality_1/ncp"     , "", "n_{charged}"  , false, "jets", false, 3);
    addCanvas("tightLeadingJetQuality_1/n_"      , "", "n_{const}"    , false, "jets", false, 4);
    addCanvas("tightLeadingJetQuality_1/emf"     , "", "f_{EM}"       , false, "jets", false, 4);
    addCanvas("tightLeadingJetQuality_1/fHPD_"   , "", "f_{HPD}"      , false, "jets", false, 3);
    addCanvas("tightLeadingJetQuality_1/n90Hits_", "", "n_{90}^{hits}", false, "jets", false, 4);

    //addCanvas("tightLeadingJetKinematics_0/eta"  , "", "#eta"       , false, "jets"  , true , 1);
    //addCanvas("tightLead_0_JetKinematics_0/pt"   , "", "p_{t} [GeV]", false, "events", true , 4);
    //addCanvas("tightLead_1_JetKinematics_0/pt"   , "", "p_{t} [GeV]", false, "events", true , 4);
    //addCanvas("tightLead_2_JetKinematics_0/pt"   , "", "p_{t} [GeV]", false, "events", true , 4);
    //addCanvas("tightLead_3_JetKinematics_0/pt"   , "", "p_{t} [GeV]", false, "events", true , 4);
    //addCanvas("tightLead_4_JetKinematics_0/pt"   , "", "p_{t} [GeV]", false, "events", true , 4);
    //addCanvas("tightLead_5_JetKinematics_0/pt"   , "", "p_{t} [GeV]", false, "events", true , 3);

    addCanvas("tightLeadingJetKinematics_1/eta", "", "#eta"           , false,            "jets"  , false, 4);
    addCanvas("tightLead_0_JetKinematics_1/pt" , "", "p_{t} [GeV]", 2 , false, 20., 600., "events", true , 4);
    addCanvas("tightLead_1_JetKinematics_1/pt" , "", "p_{t} [GeV]", 2 , false, 20., 600., "events", true , 4);
    addCanvas("tightLead_2_JetKinematics_1/pt" , "", "p_{t} [GeV]", 2 , false, 20., 300., "events", true , 4);
    addCanvas("tightLead_3_JetKinematics_1/pt" , "", "p_{t} [GeV]", 2 , false, 20., 250., "events", true , 4);
    addCanvas("tightLead_4_JetKinematics_1/pt" , "", "p_{t} [GeV]", 2 , false, 20., 200., "events", true , 4);
    addCanvas("tightLead_5_JetKinematics_1/pt" , "", "p_{t} [GeV]", 2 , false, 20., 180., "events", true , 3);

    //addCanvas("tightBJet_0_JetKinematics_1/pt"          , "", "p_{t} [GeV]", 2 , false, "events", true , 4);//1);
    //addCanvas("tightBJet_1_JetKinematics_1/pt"          , "", "p_{t} [GeV]", 2 , false, "events", true , 4);//1);
    addCanvas("monitoredTightBJet_0_JetKinematics_1/pt" , "", "p_{t} [GeV]", 2 , false, 20., 600., "events", true , 4);//1);
    addCanvas("monitoredTightBJet_1_JetKinematics_1/pt" , "", "p_{t} [GeV]", 2 , false, 20., 300., "events", true , 3);

    addCanvas("tightLeadingJetQuality_1/btagTrkCntHighEff_"  , "", "d_{B}(TCHE)" , false, "jets", true , 4);
    addCanvas("tightLeadingJetQuality_1/btagTrkCntHighPurity", "", "d_{B}(TCHP)" , false, "jets", true , 3);//1);
    //addCanvas("tightLeadingJetQuality_1/btagSimpleSecVtx_"   , "", "disc_{SSVHE}", false, "jets", true , 1);

    addCanvas("tightBottomJetKinematics_1/n"         , "", "n_{b-jet}", false, "events", true , 3);
    //addCanvas("monitoredTightBottomJetKinematics_1/n", "", "n_{b-jet}", false, "events", true , 4);//3);

    addCanvas("eventShapes_1/C"            , "", "C"          ,  5 , false,         "events", true , 4);
    addCanvas("eventShapes_1/D"            , "", "D"          ,  5 , false,         "events", true , 4);
    addCanvas("eventShapes_1/aplanarity"   , "", "aplanarity" ,  5 , false,         "events", true , 5);
    addCanvas("eventShapes_1/circularity"  , "", "circularity",  5 , false,         "events", true , 4);
    addCanvas("eventShapes_1/isotropy"     , "", "isotropy"   ,  5 , false,         "events", true , 4);
    addCanvas("eventShapes_1/sphericity"   , "", "sphericity" ,  5 , false,         "events", true , 4);
    addCanvas("fullHadSpecial_1/ht"        , "", "H_{t} [GeV]", 20 , false,         "events", true , 5);
    addCanvas("fullHadSpecial_1/centrality", "", "centrality" ,  5 , false, 0., 1., "events", true , 4);

    //addCanvas("eventShapes_2/C"            , "", "C"          , 20 , false, "events", true , 4);
    //addCanvas("eventShapes_2/D"            , "", "D"          , 20 , false, "events", true , 3);
    //addCanvas("eventShapes_2/aplanarity"   , "", "aplanarity" , 10 , false, "events", true , 3);
    //addCanvas("eventShapes_2/circularity"  , "", "circularity", 20 , false, "events", true , 4);
    //addCanvas("eventShapes_2/isotropy"     , "", "isotropy"   , 20 , false, "events", true , 4);
    //addCanvas("eventShapes_2/sphericity"   , "", "sphericity" , 20 , false, "events", true , 4);
    //addCanvas("fullHadSpecial_2/ht"        , "", "H_{t} [GeV]", 50 , false, "events", true , 4);
    //addCanvas("fullHadSpecial_2/centrality", "", "centrality" , 22 , false, "events", true , 4);

    addCanvas("kinFitQuality_2/prob"    , "", "P(#chi^{2})"          , 10 , false, "events", true , 1.5e-1, 100., 5);  // leg: 3 - 5
    addCanvas("kinFitQuality_2/prob_log", "", "log_{10}(P(#chi^{2}))", 10 , false, "events", true , 5e-3, 100., 4);
    addCanvas("kinFitQuality_3/prob"    , "", "P(#chi^{2})"          , 10 , false, "events", true , 40.e-2, 30., 5); // down: 10.e-2 -  :: up: 10 - 30
    //addCanvas("kinFitQuality_3/prob_log", "", "log_{10}(P(#chi^{2}))", 10 , false, "events", true , 5e-3, 100., 4);

    //addCanvas("kinFitQuality_2/bQuarkEta"        , "", "d#eta"         , false, "events", true , 1);
    //addCanvas("kinFitQuality_2/bQuarkPhi"        , "", "d#varphi"      , false, "events", true , 1);
    //addCanvas("kinFitQuality_2/bQuarkPt"         , "", "dp_{t}"    , 5 , false, "events", true , 4);//0);
    //addCanvas("kinFitQuality_2/lightQuarkEta"    , "", "d#eta"         , false, "events", true , 1);
    //addCanvas("kinFitQuality_2/lightQuarkPhi"    , "", "d#varphi"      , false, "events", true , 1);
    //addCanvas("kinFitQuality_2/lightQuarkPt"     , "", "dp_{t}"    , 5 , false, "events", true , 4);//0);

    addCanvas("kinFitQuality_2/bPullEta"        , "", "(#eta_{rec}-#eta_{fit})/#sigma_{#eta}"             , false, -2., 2., "events", true , 4);
    addCanvas("kinFitQuality_2/bPullPhi"        , "", "(#varphi_{rec}-#varphi_{fit})/#sigma_{#varphi}"    , false, -2., 2., "events", true , 5);
    addCanvas("kinFitQuality_2/bPullEt"         , "", "(E_{t,rec}-E_{t,fit})/#sigma_{E_{t}}"          , 5 , false,          "events", true , 4);//0);
    addCanvas("kinFitQuality_2/lightPullEta"    , "", "(#eta_{rec}-#eta_{fit})/#sigma_{#eta}"             , false, -2., 2., "events", true , 4);
    addCanvas("kinFitQuality_2/lightPullPhi"    , "", "(#varphi_{rec}-#varphi_{fit})/#sigma_{#varphi}"    , false, -2., 2., "events", true , 4);
    addCanvas("kinFitQuality_2/lightPullEt"     , "", "(E_{t,rec}-E_{t,fit})/#sigma_{E_{t}}"          , 5 , false,          "events", true , 4);//0);

    addCanvas("kinFitQuality_3/bPullEta"        , "", "(#eta_{rec}-#eta_{fit})/#sigma_{#eta}"             , false, -2., 2., "events", true , 4);
    addCanvas("kinFitQuality_3/bPullPhi"        , "", "(#varphi_{rec}-#varphi_{fit})/#sigma_{#varphi}"    , false, -2., 2., "events", true , 5);
    addCanvas("kinFitQuality_3/bPullEt"         , "", "(E_{t,rec}-E_{t,fit})/#sigma_{E_{t}}"          , 5 , false,          "events", true , 4);//0);
    addCanvas("kinFitQuality_3/lightPullEta"    , "", "(#eta_{rec}-#eta_{fit})/#sigma_{#eta}"             , false, -2., 2., "events", true , 4);
    addCanvas("kinFitQuality_3/lightPullPhi"    , "", "(#varphi_{rec}-#varphi_{fit})/#sigma_{#varphi}"    , false, -2., 2., "events", true , 4);
    addCanvas("kinFitQuality_3/lightPullEt"     , "", "(E_{t,rec}-E_{t,fit})/#sigma_{E_{t}}"          , 5 , false,          "events", true , 4);//0);

    addCanvas("fullHadTopReco_2/topQuarkMass"    , "", "m_{top} [GeV]", 20 , false, "top quarks", false, 0., 21., 4);//1);  // up: 30 - 21
    addCanvas("fullHadTopReco_2/topQuarkMassHypo", "", "m_{top} [GeV]", 20 , false, "top quarks", false, 0., 36., 3);//1);  // up: 40 - 36
								      
    addCanvas("fullHadTopReco_3/topQuarkMass"    , "", "m_{top} [GeV]", 20 , false, "top quarks", false, 0., 12.0, 4);//1);  // up: 5.5 - 12
    addCanvas("fullHadTopReco_3/topQuarkMassHypo", "", "m_{top} [GeV]", 20 , false, "top quarks", false, 0., 14.0, 4);       // up: 7.5 - 14

  }
  for(unsigned long i = 0; i <= 3; ++i){
    if(canvases.Contains("Stats") && !canvases.Contains("Kin")){
      // name of canvas, title of canvas, xAxis title, xAxis in log, yAxis title, yAxis in log, legend to be drawn
      addCanvas((TString)"tightLeadingJetKinematics_" + i + (TString)"/n",   "Tight Leading Jet Multiplicity", "n",      false, "events", false, 0);
    }
    if(canvases.Contains("Kin") && (!canvases.Contains("Kin_") || canvases.Contains((TString)"Kin_" + i))){
      // name of canvas, title of canvas, xAxis title, xAxis in log, yAxis title, yAxis in log, legend to be drawn
      addCanvas((TString)"tightLeadingJetKinematics_" + i + (TString)"/n",   "Tight Leading Jet Multiplicity", "n",      false, "events", true, 0);
      addCanvas((TString)"tightLeadingJetKinematics_" + i + (TString)"/en",  "Tight Leading Jet energy",       "energy", false, "jets", true, 1);
      addCanvas((TString)"tightLeadingJetKinematics_" + i + (TString)"/eta", "Tight Leading Jet #eta",         "#eta",   false, "jets", true, 1);
      addCanvas((TString)"tightLeadingJetKinematics_" + i + (TString)"/phi", "Tight Leading Jet #varphi",      "#varphi",false, "jets", true, 1);
      addCanvas((TString)"tightLeadingJetKinematics_" + i + (TString)"/pt",  "Tight Leading Jet p_{t}",        "p_{t}",  false, "jets", true, 1);

      addCanvas((TString)"tightBottomJetKinematics_"  + i + (TString)"/n",    "Tight Bottom Jet Multiplicity",  "n",      false, "events", true, 1);
      addCanvas((TString)"tightBottomJetKinematics_"  + i + (TString)"/en",   "Tight Bottom Jet energy",        "energy", false, "jets", true, 1);
      addCanvas((TString)"tightBottomJetKinematics_"  + i + (TString)"/eta",  "Tight Bottom Jet #eta",          "#eta",   false, "jets", true, 1);
      addCanvas((TString)"tightBottomJetKinematics_"  + i + (TString)"/phi",  "Tight Bottom Jet #varphi",       "#varphi",false, "jets", true, 1);
      addCanvas((TString)"tightBottomJetKinematics_"  + i + (TString)"/pt",   "Tight Bottom Jet p_{t}",         "p_{t}",  false, "jets", true, 1);

      addCanvas((TString)"tightBJet_0_JetKinematics_" + i + (TString)"/en",  "1. Tight B Jet energy",          "energy", false, "events", true, 1);
      addCanvas((TString)"tightBJet_0_JetKinematics_" + i + (TString)"/eta", "1. Tight B Jet #eta",            "#eta",   false, "events", true, 1);
      addCanvas((TString)"tightBJet_0_JetKinematics_" + i + (TString)"/phi", "1. Tight B Jet #varphi",         "#varphi",false, "events", true, 1);
      addCanvas((TString)"tightBJet_0_JetKinematics_" + i + (TString)"/pt",  "1. Tight B Jet p_{t}",           "p_{t}",  false, "events", true, 1);

      addCanvas((TString)"tightBJet_1_JetKinematics_" + i + (TString)"/en",  "2. Tight B Jet energy",          "energy", false, "events", true, 1);
      addCanvas((TString)"tightBJet_1_JetKinematics_" + i + (TString)"/eta", "2. Tight B Jet #eta",            "#eta",   false, "events", true, 1);
      addCanvas((TString)"tightBJet_1_JetKinematics_" + i + (TString)"/phi", "2. Tight B Jet #varphi",         "#varphi",false, "events", true, 1);
      addCanvas((TString)"tightBJet_1_JetKinematics_" + i + (TString)"/pt",  "2. Tight B Jet p_{t}",           "p_{t}",  false, "events", true, 1);

      addCanvas((TString)"tightLead_0_JetKinematics_" + i + (TString)"/en",  "1. Tight Leading Jet energy",    "energy", false, "events", true, 1);
      addCanvas((TString)"tightLead_0_JetKinematics_" + i + (TString)"/eta", "1. Tight Leading Jet #eta",      "#eta",   false, "events", true, 1);
      addCanvas((TString)"tightLead_0_JetKinematics_" + i + (TString)"/phi", "1. Tight Leading Jet #varphi",   "#varphi",false, "events", true, 1);
      addCanvas((TString)"tightLead_0_JetKinematics_" + i + (TString)"/pt",  "1. Tight Leading Jet p_{t}",     "p_{t}",  false, "events", true, 1);

      addCanvas((TString)"tightLead_1_JetKinematics_" + i + (TString)"/en",  "2. Tight Leading Jet energy",    "energy", false, "events", true, 1);
      addCanvas((TString)"tightLead_1_JetKinematics_" + i + (TString)"/eta", "2. Tight Leading Jet #eta",      "#eta",   false, "events", true, 1);
      addCanvas((TString)"tightLead_1_JetKinematics_" + i + (TString)"/phi", "2. Tight Leading Jet #varphi",   "#varphi",false, "events", true, 1);
      addCanvas((TString)"tightLead_1_JetKinematics_" + i + (TString)"/pt",  "2. Tight Leading Jet p_{t}",     "p_{t}",  false, "events", true, 1);

      addCanvas((TString)"tightLead_2_JetKinematics_" + i + (TString)"/en",  "3. Tight Leading Jet energy",    "energy", false, "events", true, 1);
      addCanvas((TString)"tightLead_2_JetKinematics_" + i + (TString)"/eta", "3. Tight Leading Jet #eta",      "#eta",   false, "events", true, 1);
      addCanvas((TString)"tightLead_2_JetKinematics_" + i + (TString)"/phi", "3. Tight Leading Jet #varphi",   "#varphi",false, "events", true, 1);
      addCanvas((TString)"tightLead_2_JetKinematics_" + i + (TString)"/pt",  "3. Tight Leading Jet p_{t}",     "p_{t}",  false, "events", true, 1);

      addCanvas((TString)"tightLead_3_JetKinematics_" + i + (TString)"/en",  "4. Tight Leading Jet energy",    "energy", false, "events", true, 1);
      addCanvas((TString)"tightLead_3_JetKinematics_" + i + (TString)"/eta", "4. Tight Leading Jet #eta",      "#eta",   false, "events", true, 1);
      addCanvas((TString)"tightLead_3_JetKinematics_" + i + (TString)"/phi", "4. Tight Leading Jet #varphi",   "#varphi",false, "events", true, 1);
      addCanvas((TString)"tightLead_3_JetKinematics_" + i + (TString)"/pt",  "4. Tight Leading Jet p_{t}",     "p_{t}",  false, "events", true, 1);

      addCanvas((TString)"tightLead_4_JetKinematics_" + i + (TString)"/en",  "5. Tight Leading Jet energy",    "energy", false, "events", true, 1);
      addCanvas((TString)"tightLead_4_JetKinematics_" + i + (TString)"/eta", "5. Tight Leading Jet #eta",      "#eta",   false, "events", true, 1);
      addCanvas((TString)"tightLead_4_JetKinematics_" + i + (TString)"/phi", "5. Tight Leading Jet #varphi",   "#varphi",false, "events", true, 1);
      addCanvas((TString)"tightLead_4_JetKinematics_" + i + (TString)"/pt",  "5. Tight Leading Jet p_{t}",     "p_{t}",  false, "events", true, 1);

      addCanvas((TString)"tightLead_5_JetKinematics_" + i + (TString)"/en",  "6. Tight Leading Jet energy",    "energy", false, "events", true, 1);
      addCanvas((TString)"tightLead_5_JetKinematics_" + i + (TString)"/eta", "6. Tight Leading Jet #eta",      "#eta",   false, "events", true, 1);
      addCanvas((TString)"tightLead_5_JetKinematics_" + i + (TString)"/phi", "6. Tight Leading Jet #varphi",   "#varphi",false, "events", true, 1);
      addCanvas((TString)"tightLead_5_JetKinematics_" + i + (TString)"/pt",  "6. Tight Leading Jet p_{t}",     "p_{t}",  false, "events", true, 1);
    }
    if(canvases.Contains("Fit") && (!canvases.Contains("Fit_") || canvases.Contains((TString)"Fit_" + i))){
      if((!canvases.Contains("Fit_") || canvases.Contains((TString)"Fit_" + i)) && i > 1){
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/bQuarkEta", "", "fitted #eta diviation", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/bQuarkPhi", "", "fitted #varphi diviation", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/bQuarkPt", "", "fitted pt diviation", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/lightQuarkEta", "", "fitted #eta diviation", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/lightQuarkPhi", "", "fitted #varphi diviation", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/lightQuarkPt", "", "fitted pt diviation", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/wEta", "", "fitted #eta diviation", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/wPhi", "", "fitted #varphi diviation", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/wPt", "", "fitted pt diviation", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/topQuarkEta", "", "fitted #eta diviation", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/topQuarkPhi", "", "fitted #varphi diviation", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/topQuarkPt", "", "fitted pt diviation", false, "events", true, 1);

	addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2"    , "", "Chi2"                       , false, "events", true, 1);
	addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob"    , "", "Probability(Chi2)"          , false, "events", true, 1);
	addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_log", "", "log_{10}(Probability(Chi2))", false, "events", true, 0);

	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_2", "", "Chi2 2", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_2", "", "Probability(Chi2 2)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_3", "", "Chi2 3", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_3", "", "Probability(Chi2 3)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_4", "", "Chi2 4", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_4", "", "Probability(Chi2 4)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_5", "", "Chi2 5", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_5", "", "Probability(Chi2 5)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_6", "", "Chi2 6", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_6", "", "Probability(Chi2 6)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_7", "", "Chi2 7", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_7", "", "Probability(Chi2 7)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_8", "", "Chi2 8", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_8", "", "Probability(Chi2 8)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_9", "", "Chi2 9", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_9", "", "Probability(Chi2 9)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_10", "", "Chi2 10", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_10", "", "Probability(Chi2 10)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_11", "", "Chi2 11", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_11", "", "Probability(Chi2 11)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_12", "", "Chi2 12", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_12", "", "Probability(Chi2 12)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_13", "", "Chi2 13", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_13", "", "Probability(Chi2 13)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_14", "", "Chi2 14", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_14", "", "Probability(Chi2 14)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_15", "", "Chi2 15", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_15", "", "Probability(Chi2 15)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_16", "", "Chi2 16", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_16", "", "Probability(Chi2 16)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_17", "", "Chi2 17", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_17", "", "Probability(Chi2 17)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_18", "", "Chi2 18", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_18", "", "Probability(Chi2 18)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_19", "", "Chi2 19", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_19", "", "Probability(Chi2 19)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_20", "", "Chi2 20", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_20", "", "Probability(Chi2 20)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2 21", "", "Chi2 21", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob 21", "", "Probability(Chi2 21)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_22", "", "Chi2 22", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_22", "", "Probability(Chi2 22)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_23", "", "Chi2 23", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_23", "", "Probability(Chi2 23)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_24", "", "Chi2 24", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_24", "", "Probability(Chi2 24)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_25", "", "Chi2 25", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_25", "", "Probability(Chi2 25)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_26", "", "Chi2 26", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_26", "", "Probability(Chi2 26)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_27", "", "Chi2 27", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_27", "", "Probability(Chi2 27)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_28", "", "Chi2 28", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_28", "", "Probability(Chi2 28)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_29", "", "Chi2 29", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_29", "", "Probability(Chi2 29)", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/chi2_30", "", "Chi2 30", false, "events", true, 1);
	//addCanvas((TString)"kinFitQuality_" + i + (TString)"/prob_30", "", "Probability(Chi2 30)", false, "events", true, 1);
      }
      //else{
      //	std::cout << "Found invalid expression!" << std::endl;
      //	std::cout << "In expression 'Fit_x' x has to be larger than 0!" << std::endl;
      //	assert(0);
      //}
    }
    if(canvases.Contains("Reco") && (!canvases.Contains("Reco_") || canvases.Contains((TString)"Reco_" + i))){
      if((!canvases.Contains("Reco_") || canvases.Contains((TString)"Reco_" + i)) && i > 1){
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/bQuarkEta"       , "", "b #eta"  , false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/bQuarkPhi"       , "", "b #varphi"  , false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/bQuarkPt"        , "", "b pt"    , false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/bQuarkMass"      , "", "b mass"  , false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/lightQuarkEta"   , "", "q #eta"  , false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/lightQuarkPhi"   , "", "q #varphi"  , false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/lightQuarkPt"    , "", "q pt"    , false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/lightQuarkMass"  , "", "q mass"  , false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/wEta"            , "", "w #eta"  , false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/wPhi"            , "", "w #varphi"  , false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/wPt"             , "", "w pt"    , false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/wMass"           , "", "w mass"  , false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/topQuarkEta"     , "", "top #eta", false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/topQuarkPhi"     , "", "top #varphi", false, "events", true, 1);
	//addCanvas((TString)"fullHadTopReco_" + i + (TString)"/topQuarkPt"      , "", "top pt"  , false, "events", true, 1);

	addCanvas((TString)"fullHadTopReco_" + i + (TString)"/topQuarkMass"    , "", "top mass", false, "top quarks", true, 1);
	addCanvas((TString)"fullHadTopReco_" + i + (TString)"/topQuarkMassHypo", "", "top mass", false, "top quarks", false, 1);
      }
      //else{
      //	std::cout << "Found invalid expression!" << std::endl;
      //	std::cout << "In expression 'Reco_x' x has to be larger than 0!" << std::endl;
      //	assert(0);
      //}
    }
    if(canvases.Contains("Shap") && (!canvases.Contains("Shap_") || canvases.Contains((TString)"Shap_" + i))){
      addCanvas((TString)"eventShapes_" + i + (TString)"/C"          , "", "C"          , false, "events", true , 1);
      addCanvas((TString)"eventShapes_" + i + (TString)"/D"          , "", "D"          , false, "events", true , 1);
      addCanvas((TString)"eventShapes_" + i + (TString)"/aplanarity" , "", "aplanarity" , false, "events", true , 1);
      addCanvas((TString)"eventShapes_" + i + (TString)"/circularity", "", "circularity", false, "events", true , 0);
      addCanvas((TString)"eventShapes_" + i + (TString)"/isotropy"   , "", "isotropy"   , false, "events", true , 0);
      addCanvas((TString)"eventShapes_" + i + (TString)"/sphericity" , "", "sphericity" , false, "events", true , 1);

      //addCanvas((TString)"eventShapes_" + i + (TString)"/apl_c"      , "", "aplanarity" , false, "C"          , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/apl_d"      , "", "aplanarity" , false, "D"          , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/c_d"        , "", "C"          , false, "D"          , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/cir_apl"    , "", "circularity", false, "aplanarity" , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/cir_c"      , "", "circularity", false, "C"          , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/cir_d"      , "", "circularity", false, "D"          , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/cir_sph"    , "", "circularity", false, "sphericity" , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/iso_apl"    , "", "isotropy"   , false, "aplanarity" , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/iso_c"      , "", "isotropy"   , false, "C"          , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/iso_cir"    , "", "isotropy"   , false, "circularity", false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/iso_d"      , "", "isotropy"   , false, "D"          , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/iso_sph"    , "", "isotropy"   , false, "sphericity" , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/sph_apl"    , "", "sphericity" , false, "aplanarity" , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/sph_c"      , "", "sphericity" , false, "C"          , false, 2);
      //addCanvas((TString)"eventShapes_" + i + (TString)"/sph_d"      , "", "sphericity" , false, "D"          , false, 2);
    }
    if(canvases.Contains("Spec") && (!canvases.Contains("Spec_") || canvases.Contains((TString)"Spec_" + i))){
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/ht"      , "", "Ht"               , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/ht3jet"  , "", "Ht from 3. jet on", false, "events", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/realB"   , "", "realB (HighPur)"  , false, "events", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/realBCSV", "", "realB (SecVertex)", false, "events", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/realBSM" , "", "realB (SoftMuon)" , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/mjj"     , "", "mjj"              , false, "dijet masses", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/mjjj"    , "", "mjjj"             , false, "trijet masses", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/hltQuadPass" , "", "hltQuadPass"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/jetPtUn" , "", "jetPtUn"          , false, "jets", true, 1);

      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/centrality", "", "centrality", false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/et56"      , "", "Et_{5,6}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/sqrt_s"    , "", "#sqrt{s}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/M3"        , "", "M3"        , false, "events", true, 1);

      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaeta"  , "", "#etax#eta moment", false, "jets", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaeta_b", "", "#etax#eta moment", false, "jets", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaeta_g", "", "#etax#eta moment", false, "jets", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaeta_q", "", "#etax#eta moment", false, "jets", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaphi"  , "", "#etax#varphi moment", false, "jets", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaphi_b", "", "#etax#phi moment", false, "jets", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaphi_g", "", "#etax#phi moment", false, "jets", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaphi_q", "", "#etax#phi moment", false, "jets", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/phiphi"  , "", "#varphix#varphi moment", false, "jets", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/phiphi_b", "", "#phix#phi moment", false, "jets", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/phiphi_g", "", "#phix#phi moment", false, "jets", true, 1);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/phiphi_q", "", "#phix#phi moment", false, "jets", true, 1);

      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1-pt2"  , "", "pt_{1}-pt_{2}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1-pt3"  , "", "pt_{1}-pt_{3}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1-pt4"  , "", "pt_{1}-pt_{4}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1-pt5"  , "", "pt_{1}-pt_{5}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1-pt6"  , "", "pt_{1}-pt_{6}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt2-pt3"  , "", "pt_{2}-pt_{3}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt2-pt4"  , "", "pt_{2}-pt_{4}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt2-pt5"  , "", "pt_{2}-pt_{5}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt2-pt6"  , "", "pt_{2}-pt_{6}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt3-pt4"  , "", "pt_{3}-pt_{4}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt3-pt5"  , "", "pt_{3}-pt_{5}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt3-pt6"  , "", "pt_{3}-pt_{6}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt4-pt5"  , "", "pt_{4}-pt_{5}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt4-pt6"  , "", "pt_{4}-pt_{6}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt5-pt6"  , "", "pt_{5}-pt_{6}"  , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/ptb1-ptb2", "", "pt_{b1}-pt_{b2}", false, "events", true, 1);

      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1-pt2_norm"  , "", "(pt_{1}-pt_{2})/(pt_{1}+pt_{2})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1-pt3_norm"  , "", "(pt_{1}-pt_{3})/(pt_{1}+pt_{3})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1-pt4_norm"  , "", "(pt_{1}-pt_{4})/(pt_{1}+pt_{4})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1-pt5_norm"  , "", "(pt_{1}-pt_{5})/(pt_{1}+pt_{5})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1-pt6_norm"  , "", "(pt_{1}-pt_{6})/(pt_{1}+pt_{6})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt2-pt3_norm"  , "", "(pt_{2}-pt_{3})/(pt_{2}+pt_{3})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt2-pt4_norm"  , "", "(pt_{2}-pt_{4})/(pt_{2}+pt_{4})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt2-pt5_norm"  , "", "(pt_{2}-pt_{5})/(pt_{2}+pt_{5})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt2-pt6_norm"  , "", "(pt_{2}-pt_{6})/(pt_{2}+pt_{6})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt3-pt4_norm"  , "", "(pt_{3}-pt_{4})/(pt_{3}+pt_{4})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt3-pt5_norm"  , "", "(pt_{3}-pt_{5})/(pt_{3}+pt_{5})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt3-pt6_norm"  , "", "(pt_{3}-pt_{6})/(pt_{3}+pt_{6})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt4-pt5_norm"  , "", "(pt_{4}-pt_{5})/(pt_{4}+pt_{5})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt4-pt6_norm"  , "", "(pt_{4}-pt_{6})/(pt_{4}+pt_{6})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt5-pt6_norm"  , "", "(pt_{5}-pt_{6})/(pt_{5}+pt_{6})"    , false, "events", true, 1);
      addCanvas((TString)"fullHadSpecial_" + i + (TString)"/ptb1-ptb2_norm", "", "(pt_{b1}-pt_{b2})/(pt_{b1}+pt_{b2})", false, "events", true, 1);

      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaetaetaphi"  , "", "etaeta", false, "etaphi", false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaetaetaphi_b", "", "etaeta", false, "etaphi", false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaetaetaphi_g", "", "etaeta", false, "etaphi", false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaetaetaphi_q", "", "etaeta", false, "etaphi", false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaetaphiphi"  , "", "etaeta", false, "phiphi", false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaetaphiphi_b", "", "etaeta", false, "phiphi", false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaetaphiphi_g", "", "etaeta", false, "phiphi", false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaetaphiphi_q", "", "etaeta", false, "phiphi", false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaphiphiphi"  , "", "etaphi", false, "phiphi", false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaphiphiphi_b", "", "etaphi", false, "phiphi", false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaphiphiphi_g", "", "etaphi", false, "phiphi", false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/etaphiphiphi_q", "", "etaphi", false, "phiphi", false, 2);
      //
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1pt2"        , "", "pt1"   , false, "pt2"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1pt3"        , "", "pt1"   , false, "pt3"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1pt4"        , "", "pt1"   , false, "pt4"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1pt5"        , "", "pt1"   , false, "pt5"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt1pt6"        , "", "pt1"   , false, "pt6"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt2pt3"        , "", "pt2"   , false, "pt3"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt2pt4"        , "", "pt2"   , false, "pt4"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt2pt5"        , "", "pt2"   , false, "pt5"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt2pt6"        , "", "pt2"   , false, "pt6"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt3pt4"        , "", "pt3"   , false, "pt4"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt3pt5"        , "", "pt3"   , false, "pt5"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt3pt6"        , "", "pt3"   , false, "pt6"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt4pt5"        , "", "pt4"   , false, "pt5"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt4pt6"        , "", "pt4"   , false, "pt6"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/pt5pt6"        , "", "pt5"   , false, "pt6"   , false, 2);
      //addCanvas((TString)"fullHadSpecial_" + i + (TString)"/ptb1ptb2"      , "", "ptb1"  , false, "ptb2"  , false, 2);
    }
    if(canvases.Contains("Qual") && (!canvases.Contains("Qual_") || canvases.Contains((TString)"Qual_" + i))){
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/btagCombSecVtxMVA_"  , "", "combSecVtxMVA"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/btagCombSecVtx_"     , "", "combSecVtx"     , false, "jets", true, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/btagJetBProbability_", "", "jetBProbability", false, "jets", true, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/btagJetProbability_" , "", "jetProbability" , false, "jets", true, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/btagSimpleSecVtx_"   , "", "simpleSecVtx"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/btagSoftElecByIP3d_" , "", "softElecByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/btagSoftElecByPt_"   , "", "softElecByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/btagSoftMuonByIP3d_" , "", "softMuonByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/btagSoftMuonByPt_"   , "", "softMuonByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/btagSoftMuon_"       , "", "softMuon"       , false, "jets", true, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/btagTrkCntHighEff_"  , "", "trkCntHighEff"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/btagTrkCntHighPurity", "", "trkCntHighPur"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/cef"  , "", "cef" , false, "jets", true , 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/chf"  , "", "chf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/nef"  , "", "nef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/nhf"  , "", "nhf" , false, "jets", true , 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/ncp"  , "", "ncp" , false, "jets", false, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/nch"  , "", "nch" , false, "jets", false, 1);
      addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/emf"  , "", "emf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/fHPD_", "", "fHPD", false, "jets", false, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/n60_" , "", "n60" , false, "jets", false, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/n90_" , "", "n90" , false, "jets", false, 1);
      //addCanvas((TString)"tightLeadingJetQuality_" + i + (TString)"/n_"   , "", "n"   , false, "jets", false, 1);
      //
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/btagCombSecVtxMVA_"  , "", "combSecVtxMVA"  , false, "jets", true, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/btagCombSecVtx_"     , "", "combSecVtx"     , false, "jets", true, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/btagJetBProbability_", "", "jetBProbability", false, "jets", true, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/btagJetProbability_" , "", "jetProbability" , false, "jets", true, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/btagSimpleSecVtx_"   , "", "simpleSecVtx"   , false, "jets", true, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/btagSoftElecByIP3d_" , "", "softElecByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/btagSoftElecByPt_"   , "", "softElecByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/btagSoftMuonByIP3d_" , "", "softMuonByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/btagSoftMuonByPt_"   , "", "softMuonByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/btagSoftMuon_"       , "", "softMuon"       , false, "jets", true, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/btagTrkCntHighEff_"  , "", "trkCntHighEff"  , false, "jets", true, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/btagTrkCntHighPurity", "", "trkCntHighPur"  , false, "jets", true, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/cef"  , "", "cef" , false, "jets", false, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/chf"  , "", "chf" , false, "jets", false, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/nef"  , "", "nef" , false, "jets", false, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/nhf"  , "", "nhf" , false, "jets", false, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/ncp"  , "", "ncp" , false, "jets", false, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/nch"  , "", "nch" , false, "jets", false, 1);
      addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/emf"  , "", "emf" , false, "jets", false, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/fHPD_", "", "fHPD", false, "jets", false, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/n60_" , "", "n60" , false, "jets", false, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/n90_" , "", "n90" , false, "jets", false, 1);
      //addCanvas((TString)"tightBottomJetQuality_" + i + (TString)"/n_"   , "", "n"   , false, "jets", false, 1);

      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/btagCombSecVtxMVA_"  , "", "combSecVtxMVA"  , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/btagCombSecVtx_"     , "", "combSecVtx"     , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/btagJetBProbability_", "", "jetBProbability", false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/btagJetProbability_" , "", "jetProbability" , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/btagSimpleSecVtx_"   , "", "simpleSecVtx"   , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/btagSoftElecByIP3d_" , "", "softElecByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/btagSoftElecByPt_"   , "", "softElecByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/btagSoftMuonByIP3d_" , "", "softMuonByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/btagSoftMuonByPt_"   , "", "softMuonByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/btagSoftMuon_"       , "", "softMuon"       , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/btagTrkCntHighEff_"  , "", "trkCntHighEff"  , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/btagTrkCntHighPurity", "", "trkCntHighPur"  , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/cef"  , "", "cef" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/chf"  , "", "chf" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/nef"  , "", "nef" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/nhf"  , "", "nhf" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/ncp"  , "", "ncp" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/nch"  , "", "nch" , false, "jets", false, 1);
      addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/emf"  , "", "emf" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/fHPD_", "", "fHPD", false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/n60_" , "", "n60" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/n90_" , "", "n90" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_0_JetQuality_" + i + (TString)"/n_"   , "", "n"   , false, "jets", false, 1);
      //
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/btagCombSecVtxMVA_"  , "", "combSecVtxMVA"  , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/btagCombSecVtx_"     , "", "combSecVtx"     , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/btagJetBProbability_", "", "jetBProbability", false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/btagJetProbability_" , "", "jetProbability" , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/btagSimpleSecVtx_"   , "", "simpleSecVtx"   , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/btagSoftElecByIP3d_" , "", "softElecByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/btagSoftElecByPt_"   , "", "softElecByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/btagSoftMuonByIP3d_" , "", "softMuonByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/btagSoftMuonByPt_"   , "", "softMuonByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/btagSoftMuon_"       , "", "softMuon"       , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/btagTrkCntHighEff_"  , "", "trkCntHighEff"  , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/btagTrkCntHighPurity", "", "trkCntHighPur"  , false, "jets", true, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/cef"  , "", "cef" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/chf"  , "", "chf" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/nef"  , "", "nef" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/nhf"  , "", "nhf" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/ncp"  , "", "ncp" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/nch"  , "", "nch" , false, "jets", false, 1);
      addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/emf"  , "", "emf" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/fHPD_", "", "fHPD", false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/n60_" , "", "n60" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/n90_" , "", "n90" , false, "jets", false, 1);
      //addCanvas((TString)"tightBJet_1_JetQuality_" + i + (TString)"/n_"   , "", "n"   , false, "jets", false, 1);
      //
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/btagCombSecVtxMVA_"  , "", "combSecVtxMVA"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/btagCombSecVtx_"     , "", "combSecVtx"     , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/btagJetBProbability_", "", "jetBProbability", false, "jets", true, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/btagJetProbability_" , "", "jetProbability" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/btagSimpleSecVtx_"   , "", "simpleSecVtx"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/btagSoftElecByIP3d_" , "", "softElecByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/btagSoftElecByPt_"   , "", "softElecByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/btagSoftMuonByIP3d_" , "", "softMuonByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/btagSoftMuonByPt_"   , "", "softMuonByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/btagSoftMuon_"       , "", "softMuon"       , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/btagTrkCntHighEff_"  , "", "trkCntHighEff"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/btagTrkCntHighPurity", "", "trkCntHighPur"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/cef"  , "", "cef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/chf"  , "", "chf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/nef"  , "", "nef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/nhf"  , "", "nhf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/ncp"  , "", "ncp" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/nch"  , "", "nch" , false, "jets", false, 1);
      addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/emf"  , "", "emf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/fHPD_", "", "fHPD", false, "jets", false, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/n60_" , "", "n60" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/n90_" , "", "n90" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_0_JetQuality_" + i + (TString)"/n_"   , "", "n"   , false, "jets", false, 1);
      //
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/btagCombSecVtxMVA_"  , "", "combSecVtxMVA"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/btagCombSecVtx_"     , "", "combSecVtx"     , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/btagJetBProbability_", "", "jetBProbability", false, "jets", true, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/btagJetProbability_" , "", "jetProbability" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/btagSimpleSecVtx_"   , "", "simpleSecVtx"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/btagSoftElecByIP3d_" , "", "softElecByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/btagSoftElecByPt_"   , "", "softElecByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/btagSoftMuonByIP3d_" , "", "softMuonByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/btagSoftMuonByPt_"   , "", "softMuonByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/btagSoftMuon_"       , "", "softMuon"       , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/btagTrkCntHighEff_"  , "", "trkCntHighEff"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/btagTrkCntHighPurity", "", "trkCntHighPur"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/cef"  , "", "cef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/chf"  , "", "chf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/nef"  , "", "nef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/nhf"  , "", "nhf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/ncp"  , "", "ncp" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/nch"  , "", "nch" , false, "jets", false, 1);
      addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/emf"  , "", "emf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/fHPD_", "", "fHPD", false, "jets", false, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/n60_" , "", "n60" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/n90_" , "", "n90" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_1_JetQuality_" + i + (TString)"/n_"   , "", "n"   , false, "jets", false, 1);
      //
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/btagCombSecVtxMVA_"  , "", "combSecVtxMVA"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/btagCombSecVtx_"     , "", "combSecVtx"     , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/btagJetBProbability_", "", "jetBProbability", false, "jets", true, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/btagJetProbability_" , "", "jetProbability" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/btagSimpleSecVtx_"   , "", "simpleSecVtx"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/btagSoftElecByIP3d_" , "", "softElecByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/btagSoftElecByPt_"   , "", "softElecByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/btagSoftMuonByIP3d_" , "", "softMuonByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/btagSoftMuonByPt_"   , "", "softMuonByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/btagSoftMuon_"       , "", "softMuon"       , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/btagTrkCntHighEff_"  , "", "trkCntHighEff"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/btagTrkCntHighPurity", "", "trkCntHighPur"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/cef"  , "", "cef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/chf"  , "", "chf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/nef"  , "", "nef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/nhf"  , "", "nhf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/ncp"  , "", "ncp" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/nch"  , "", "nch" , false, "jets", false, 1);
      addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/emf"  , "", "emf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/fHPD_", "", "fHPD", false, "jets", false, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/n60_" , "", "n60" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/n90_" , "", "n90" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_2_JetQuality_" + i + (TString)"/n_"   , "", "n"   , false, "jets", false, 1);
      //
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/btagCombSecVtxMVA_"  , "", "combSecVtxMVA"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/btagCombSecVtx_"     , "", "combSecVtx"     , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/btagJetBProbability_", "", "jetBProbability", false, "jets", true, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/btagJetProbability_" , "", "jetProbability" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/btagSimpleSecVtx_"   , "", "simpleSecVtx"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/btagSoftElecByIP3d_" , "", "softElecByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/btagSoftElecByPt_"   , "", "softElecByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/btagSoftMuonByIP3d_" , "", "softMuonByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/btagSoftMuonByPt_"   , "", "softMuonByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/btagSoftMuon_"       , "", "softMuon"       , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/btagTrkCntHighEff_"  , "", "trkCntHighEff"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/btagTrkCntHighPurity", "", "trkCntHighPur"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/cef"  , "", "cef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/chf"  , "", "chf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/nef"  , "", "nef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/nhf"  , "", "nhf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/ncp"  , "", "ncp" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/nch"  , "", "nch" , false, "jets", false, 1);
      addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/emf"  , "", "emf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/fHPD_", "", "fHPD", false, "jets", false, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/n60_" , "", "n60" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/n90_" , "", "n90" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_3_JetQuality_" + i + (TString)"/n_"   , "", "n"   , false, "jets", false, 1);
      //
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/btagCombSecVtxMVA_"  , "", "combSecVtxMVA"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/btagCombSecVtx_"     , "", "combSecVtx"     , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/btagJetBProbability_", "", "jetBProbability", false, "jets", true, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/btagJetProbability_" , "", "jetProbability" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/btagSimpleSecVtx_"   , "", "simpleSecVtx"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/btagSoftElecByIP3d_" , "", "softElecByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/btagSoftElecByPt_"   , "", "softElecByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/btagSoftMuonByIP3d_" , "", "softMuonByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/btagSoftMuonByPt_"   , "", "softMuonByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/btagSoftMuon_"       , "", "softMuon"       , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/btagTrkCntHighEff_"  , "", "trkCntHighEff"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/btagTrkCntHighPurity", "", "trkCntHighPur"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/cef"  , "", "cef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/chf"  , "", "chf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/nef"  , "", "nef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/nhf"  , "", "nhf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/ncp"  , "", "ncp" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/nch"  , "", "nch" , false, "jets", false, 1);
      addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/emf"  , "", "emf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/fHPD_", "", "fHPD", false, "jets", false, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/n60_" , "", "n60" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/n90_" , "", "n90" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_4_JetQuality_" + i + (TString)"/n_"   , "", "n"   , false, "jets", false, 1);
      //
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/btagCombSecVtxMVA_"  , "", "combSecVtxMVA"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/btagCombSecVtx_"     , "", "combSecVtx"     , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/btagJetBProbability_", "", "jetBProbability", false, "jets", true, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/btagJetProbability_" , "", "jetProbability" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/btagSimpleSecVtx_"   , "", "simpleSecVtx"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/btagSoftElecByIP3d_" , "", "softElecByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/btagSoftElecByPt_"   , "", "softElecByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/btagSoftMuonByIP3d_" , "", "softMuonByIP3d" , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/btagSoftMuonByPt_"   , "", "softMuonByPt"   , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/btagSoftMuon_"       , "", "softMuon"       , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/btagTrkCntHighEff_"  , "", "trkCntHighEff"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/btagTrkCntHighPurity", "", "trkCntHighPur"  , false, "jets", true, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/cef"  , "", "cef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/chf"  , "", "chf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/nef"  , "", "nef" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/nhf"  , "", "nhf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/ncp"  , "", "ncp" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/nch"  , "", "nch" , false, "jets", false, 1);
      addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/emf"  , "", "emf" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/fHPD_", "", "fHPD", false, "jets", false, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/n60_" , "", "n60" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/n90_" , "", "n90" , false, "jets", false, 1);
      //addCanvas((TString)"tightLead_5_JetQuality_" + i + (TString)"/n_"   , "", "n"   , false, "jets", false, 1);
    }
    if(canvases.Contains("MET") && (!canvases.Contains("MET_") || canvases.Contains((TString)"MET_" + i))){
      addCanvas((TString)"METKinematics_" + i + (TString)"/met.et"   , "", "#slash{E_{t}}"     , 10 , false, "events"       , true, 1);
      addCanvas((TString)"METKinematics_" + i + (TString)"/met.phi"  , "", "#varphi"           , 10 , false, "events"       , true, 1);
      addCanvas((TString)"METKinematics_" + i + (TString)"/met.px"   , "", "p_{x}"             , 10 , false, "events"       , true, 1);
      addCanvas((TString)"METKinematics_" + i + (TString)"/met.py"   , "", "p_{y}"             , 10 , false, "events"       , true, 1);
      addCanvas((TString)"METKinematics_" + i + (TString)"/met.sig"  , "", "sign #slash{E_{t}}",  2 , false, "events"       , true, 1);
      addCanvas((TString)"METKinematics_" + i + (TString)"/met.sumEt", "", "#Sigma E_{t}"      , 50 , false, "events"       , true, 1);
      
      //addCanvas((TString)"METKinematics_" + i + (TString)"/metSumEt" , "", "#Sigma E_{t}"           , false, "#slash{E_{t}}", true, 1);

      if((!canvases.Contains("MET_") || canvases.Contains((TString)"MET_" + i)) && i > 1){
 	addCanvas((TString)"METKinFit_" + i + (TString)"/preFitMET"    , "", "#slash{E_{t}}_{preFit}" , 10 , false, "events"       , true, 1);
 	addCanvas((TString)"METKinFit_" + i + (TString)"/postFitMET"   , "", "#slash{E_{t}}_{postFit}", 10 , false, "events"       , true, 1);
      }
    }
    if( !canvases.Contains("Kin")  && !canvases.Contains("Shap") && !canvases.Contains("Spec") &&
        !canvases.Contains("Fit")  && !canvases.Contains("Reco") && !canvases.Contains("Qual") &&
	!canvases.Contains("MET")  && !canvases.Contains("Stats") &&
	!canvases.Contains("dipl") && !canvases.Contains("dipl_norm") ){
      std::cout << "Found no expression matching all criteria!" << std::endl;
      std::cout << "Valid are: Kin, Shap, Spec, Fit, Reco, Qual, MET, Stats, dipl, dipl_norm" << std::endl;
      assert(0);
    }
  }
  std::cout << "Canvases created" << std::endl;
}

void fillHistograms(TString whichFiles_){

  std::cout << "Start filling histograms ..." << std::endl;

  whichFiles = whichFiles_;

  std::vector< std::pair< TFile*, std::pair<TString, float> > >  files_;

  if(whichFiles_ == "calo"){
    files_.push_back(files[sig_nlo]);
    files_.push_back(files[bkg_nlo]);
    files_.push_back(files[qcd_pyt]);
    files_.push_back(files[data]);
  }
  else if(whichFiles_ == "pf"){
    files_.push_back(files[sig_nlo_pf]);
    files_.push_back(files[bkg_nlo_pf]);
    files_.push_back(files[qcd_pyt_pf]);
    files_.push_back(files[data_pf]);
  }
  else if(whichFiles_ == "mad_pyt_calo"){
    files_.push_back(files[sig_mad]);
    files_.push_back(files[bkg_mad]);
    files_.push_back(files[qcd_pyt]);
    files_.push_back(files[data]);
  }
  else if(whichFiles_ == "mad_pyt_pf"){
    files_.push_back(files[sig_mad_pf]);
    files_.push_back(files[bkg_mad_pf]);
    files_.push_back(files[qcd_pyt_pf]);
    files_.push_back(files[data_pf]);
  }
  else if(whichFiles_ == "mad_calo"){
    files_.push_back(files[sig_mad]);
    files_.push_back(files[bkg_mad]);
    files_.push_back(files[qcd_mad]);
    files_.push_back(files[data]);
  }
  else if(whichFiles_ == "mad_pf"){
    files_.push_back(files[sig_mad_pf]);
    files_.push_back(files[bkg_mad_pf]);
    files_.push_back(files[qcd_mad_pf]);
    files_.push_back(files[data_pf]);
  }
  else if(whichFiles_ == "her_calo"){
    files_.push_back(files[sig_nlo]);
    files_.push_back(files[bkg_nlo]);
    files_.push_back(files[qcd_her]);
    files_.push_back(files[data]);
  }
  else if(whichFiles_ == "her_pf"){
    files_.push_back(files[sig_nlo_pf]);
    files_.push_back(files[bkg_nlo_pf]);
    files_.push_back(files[qcd_her_pf]);
    files_.push_back(files[data_pf]);
  }
   else{
    std::cout << "File definition '" << whichFiles_ << "' unknown, please choose an existing one!" << std::endl;
    exit(0);
  }
  for(std::vector< std::pair< TFile*, std::pair<TString, float> > >::const_iterator file = files_.begin() ; file != files_.end() ; ++file){
    if(file->first->IsZombie()){
      std::cout << "One or more files could not be opened, please check spelling, existence and access permissions!" << std::endl;
      exit(1);
    }
  }

  //  go over all histograms to be drawn per file
  for(std::map<TString,Canvas>::iterator canv = canvases.begin(); canv != canvases.end(); ++canv) {

    double normalizationScale = 0;

    for(std::vector< std::pair< TFile*, std::pair<TString, float> > >::const_iterator file = files_.begin(); file != files_.end(); ++file){
      
      TH1F* histo = ((TH1F*)file->first->Get(canv->first)->Clone());
      histo->Scale(file->second.second);
      if(normalized && file != --files_.end()) normalizationScale += histo->Integral(0,histo->GetNbinsX()+1);
      histo->SetStats(canv->second.stats);

      if(canv->second.rebin > 1) histo->Rebin(canv->second.rebin);

      // styling options for histograms
      if(file - files_.begin() == 0){
	histo->SetFillColor( kRed - 4 );
      }
      else if(file - files_.begin() == 1){
	histo->SetFillColor( kBlue + 1 );
      }
      else if(file - files_.begin() == 2){
	//histo->SetFillColor( kGreen - 4 );
	histo->SetFillColor( kYellow );
      }
      else if(file - files_.begin() == 3){
	histo->SetMarkerStyle( 29 );
	histo->SetMarkerSize( 2.0 );
	histo->SetLineWidth( 2 );
      }

      // create one type of diagram and choose if the histograms should be normalized (histo->Scale(1./histo->Integral() ) )
      if(file == files_.begin()){
	canv->second.canv = new TCanvas( canv->first, canv->first, 1, 1, 601, 601 );
	canv->second.canv->SetLeftMargin(0.13);
	canv->second.canv->SetRightMargin(0.07);
	canv->second.canv->SetBottomMargin(0.13);
	canv->second.canv->SetTopMargin(0.07);

	// 1. histogram to be drawn in one canvas
	canv->second.hists.at(0) = histo;
      }
      else{
	// other histograms to be drawn in one canvas
	canv->second.hists.push_back(histo);
      }
      if(file != files_.end() - 1) canv->second.stack->Add(canv->second.hists.back(), "hist");

      if(canv == canvases.begin()){
	for(std::vector<TLegend*>::iterator leg = legs.begin(); leg != legs.end(); ++leg){
	  (*leg)->SetFillColor(kWhite);
	  (*leg)->SetBorderSize(0);
	  if(file != files_.end() - 1) (*leg)->AddEntry(histo, file->second.first,"f");
	}
      }
    }
    if(normalized){
      for(std::vector<TH1*>::iterator hist = canv->second.hists.begin(); hist != --canv->second.hists.end(); ++hist){
	(*hist)->Scale(canv->second.hists.back()->Integral(0,canv->second.hists.back()->GetNbinsX()+1)/normalizationScale);
      }
    }
  }
  std::cout << "Finished filling histograms" << std::endl;
}

void drawMC(){

  std::cout << "Start drawing MC prediction ..." << std::endl;

  for(std::map<TString,Canvas>::iterator canv = canvases.begin(); canv != canvases.end(); ++canv) {
    canv->second.canv->cd();
    canv->second.stack->Draw();

    // set things for THStack after it has been drawn, because it is to stupid to let it be done before!
    canv->second.stack->SetTitle("");
    canv->second.stack->GetXaxis()->SetTitle(canv->second.xaxis);
    canv->second.stack->GetXaxis()->SetTitleOffset(0.75);
    canv->second.stack->GetXaxis()->SetTitleSize(0.07);
    canv->second.stack->GetYaxis()->SetTitle(canv->second.yaxis);
    canv->second.stack->GetYaxis()->SetTitleOffset(1.0);
    canv->second.stack->GetYaxis()->SetTitleSize(0.06);
    //TGaxis::SetMaxDigits(3);

    if(canv->second.xlog) canv->second.canv->SetLogx();
    if(canv->second.ylog) canv->second.canv->SetLogy();
    
    double max = (canv->second.hists.back()->GetMaximum() > canv->second.stack->GetMaximum()) ? canv->second.hists.back()->GetMaximum() : canv->second.stack->GetMaximum();
    (canv->second.ylog) ? canv->second.stack->SetMaximum(2. * max) : canv->second.stack->SetMaximum(1.1 * max);

    (canv->second.ylog) ? canv->second.stack->SetMinimum(0.6) : canv->second.stack->SetMinimum(0.);

    if(canv->second.xMin != -1e300 || canv->second.xMax != 1e300) canv->second.stack->GetXaxis()->SetRangeUser(canv->second.xMin, canv->second.xMax);
    //if(canv->second.yMin != -1e300 || canv->second.yMax != 1e300) canv->second.stack->GetYaxis()->SetRangeUser(canv->second.yMin, canv->second.yMax);
    if(canv->second.yMin != -1e300 || canv->second.yMax != 1e300) {
      canv->second.stack->SetMinimum(canv->second.yMin);
      canv->second.stack->SetMaximum(canv->second.yMax);
    }

    canv->second.leg->Draw("same");

    canv->second.canv->Paint();
  }

  new TCanvas("Legend","Legend",1,1,601,601);
  legs.back()->Draw();

  std::cout << "MC prediction drawn" << std::endl;
}

void drawData(){

  std::cout << "Start drawing data ..." << std::endl;

  for(std::map<TString,Canvas>::iterator canv = canvases.begin(); canv != canvases.end(); ++canv) {
    canv->second.canv->cd();
    canv->second.hists.back()->Draw("samePE");
    if(canv == canvases.begin()){
      for(std::vector<TLegend*>::iterator leg = legs.begin(); leg != legs.end(); ++leg){
	(*leg)->AddEntry(canv->second.hists.back(), files.back().second.first,"pl");
      }
    }
    canv->second.canv->Paint();
  }
  std::cout << "Data drawn" << std::endl;
}



void saveToPs() {

  std::cout << "Start saving everything to disk as plots.ps ..." << std::endl;
  
  TSeqCollection * list = gROOT->GetListOfCanvases();

  if( list->GetEntries() == 1) { list->First()->Print( "plots_" + whichFiles + ".ps" ); return; }
  
  int canv = -1;
  do{
    ++canv;
    if( list->At( canv ) == list->First()) list->At( canv )->Print( "plots_" + whichFiles + ".ps(" );
                                           list->At( canv )->Print( "plots_" + whichFiles + ".ps"  );
    if( list->At( canv ) == list->Last())  list->At( canv )->Print( "plots_" + whichFiles + ".ps)" );
  } while( list->At( canv ) != list->Last() );
 
  std::cout << "Everything saved to disk as plots_" << whichFiles << ".ps" << std::endl;
}

void saveToPng() {

  std::cout << "Start saving everything to disk as pngs_" << whichFiles << "/*.png ..." << std::endl;

  TSeqCollection * list = gROOT->GetListOfCanvases();
  TString nameOfCanvas;
  
  TString folder = "pngs_" + whichFiles;
  mkdir(folder, S_IRWXU|S_IRWXG|S_IRWXO);

  int canv = -1;
  do{
    ++canv;
    nameOfCanvas = (TString)list->At( canv )->GetName();
    nameOfCanvas.ReplaceAll("/","_");
    list->At( canv )->Print( folder + "/" + nameOfCanvas + ".png");
  } while( list->At( canv ) != list->Last() );

  std::cout << "Everything saved to disk as pngs_" << whichFiles << "/*.png" << std::endl;
}

void printCutFlow() {

  std::cout << "Start printing out cuf flow ..." << std::endl;

  std::cout << "------------------------" << std::endl;
  std::cout << "triggering already done " << std::endl;
  std::cout << "------------------------" << std::endl;

  for(unsigned long i = 0; i <= 3; ++i){

    TString c0 = (TString)"tightLeadingJetKinematics_" + i + (TString)"/n";

    std::map<TString,Canvas>::const_iterator canv = canvases.find(c0);
    if(canv != canvases.end()) {
    
      // integral to use:
      // Integral(0,GetNbinsX()+1)
      
      double fullHad = (canv->second.hists).at(0)->Integral(0,(canv->second.hists).at(0)->GetNbinsX()+1);
      double ttOther = (canv->second.hists).at(1)->Integral(0,(canv->second.hists).at(1)->GetNbinsX()+1);
      double qcdpt15 = (canv->second.hists).at(2)->Integral(0,(canv->second.hists).at(2)->GetNbinsX()+1);
      double data    = (canv->second.hists).at(3)->Integral(0,(canv->second.hists).at(3)->GetNbinsX()+1);


      std::cout << "---------------------------" << std::endl;
      std::cout << "cut step " << i << ":" << std::endl;
      std::cout << "---------------------------" << std::endl;
      std::cout << "fullhad : " << fullHad << " (" << 100* fullHad         /(fullHad+ttOther+qcdpt15) << "%, eff: " << 100* fullHad/(163.*lumi*0.44444)  << "%)" << std::endl;
      std::cout << "ttother : " << ttOther << " (" << 100*(fullHad+ttOther)/(fullHad+ttOther+qcdpt15) << "%, eff: " << 100*(fullHad+ttOther)/(163.*lumi) << "%)" << std::endl;
      std::cout << "qcdpt15 : " << qcdpt15 << std::endl;
      std::cout << "sum     : " << fullHad + ttOther + qcdpt15 << std::endl;
      std::cout << "data    : " << data << " +/- " << sqrt(data) << std::endl;
      std::cout << "---------------------------" << std::endl;
      std::cout << "S/B     : " << fullHad / ( ttOther + qcdpt15 ) << std::endl;
      std::cout << "S/r(S+B): " << fullHad / sqrt( fullHad + ttOther + qcdpt15 ) << std::endl;
      std::cout << "---------------------------" << std::endl;
    }
  }
  for(unsigned long i = 1; i <= 3; ++i){

    TString c0 = (TString)"tightLeadingJetKinematics_" + i + (TString)"/n";

    std::map<TString,Canvas>::const_iterator canv = canvases.find(c0);
    if(canv != canvases.end()) {

      double fullHad = (canv->second.hists).at(0)->Integral(0,(canv->second.hists).at(0)->GetNbinsX()+1);
      double ttOther = (canv->second.hists).at(1)->Integral(0,(canv->second.hists).at(1)->GetNbinsX()+1);
      double qcdpt15 = (canv->second.hists).at(2)->Integral(0,(canv->second.hists).at(2)->GetNbinsX()+1);
      double data    = (canv->second.hists).at(3)->Integral(0,(canv->second.hists).at(3)->GetNbinsX()+1);

      if(i==1)   std::cout << std::endl;
      if(i==1)   std::cout << "multi-jet & "          << fullHad << " & " << ttOther << " & " << qcdpt15 << " & " << fullHad/(ttOther+qcdpt15) << " & " << fullHad+ttOther+qcdpt15 << " & " << data << " \\\\" << std::endl;
      else if(i==2)   std::cout << "b-tag & "         << fullHad << " & " << ttOther << " & " << qcdpt15 << " & " << fullHad/(ttOther+qcdpt15) << " & " << fullHad+ttOther+qcdpt15 << " & " << data << " \\\\" << std::endl;
      else if(i==3) { std::cout << "kinematic fit & " << fullHad << " & " << ttOther << " & " << qcdpt15 << " & " << fullHad/(ttOther+qcdpt15) << " & " << fullHad+ttOther+qcdpt15 << " & " << data <<            std::endl;
	              std::cout << std::endl; }
    }
  }
  std::cout << "Finished printing out cut flow" << std::endl;
}

