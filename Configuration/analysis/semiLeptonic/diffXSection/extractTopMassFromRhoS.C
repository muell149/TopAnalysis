#include "basicFunctions.h"


std::pair< double, double > extraction(int verbose=1, double luminosity=19712., bool save=true, double minx=160., double maxx=185., double nbinsx=250, bool dataMassDependence=false, int binOfInterest=1, TString outputFolder="./", TString outputFile="diffXSecTopSemiLepHadronPhaseSpace.root");

void extractTopMassFromRhoS(int verbose=0, double luminosity=19712., bool save=true){

  // define some parameters
  // range of plot
  double minx=160.;
  double maxx=185.;
  // fine bins
  double nbinsx=250.;
  // consider mass dependence of measurement
  bool dataMassDependence=true;  
  // where to store the output
  TString outputFolder="./diffXSecFromSignal/plots/combined/2012/rhos/";
  TString outputFile="diffXSecTopSemiLepHadronPhaseSpace.root";
  // comraison mass value
  double mass   =173.18;
  double masserr=0.94;

  // ============================
  //  Set Root Style
  // ============================
  TStyle myStyle("HHStyle2","HHStyle2");
  setHHStyle(myStyle);
  TGaxis::SetMaxDigits(2);
  myStyle.cd();
  gROOT->SetStyle("HHStyle2");
  gStyle->SetEndErrorSize(8);

  // create empty mass from bin plot
  std::map< TString, std::vector<double> > binning_ = makeVariableBinning();
  int Nbins = std::abs(binning_["rhos"][binning_["rhos"].size()-1]-binning_["rhos"][0])*100;
  // get histogram in correct binning
  TH1F* extractedMass= new TH1F("extractedMass", "extractedMass", Nbins, binning_["rhos"][0], binning_["rhos"][binning_["rhos"].size()-1]);
  reBinTH1F(*extractedMass, binning_["rhos"], 0);
  TH1F* TevatronMass= new TH1F("TevatronMass", "TevatronMass", 1, binning_["rhos"][0], binning_["rhos"][binning_["rhos"].size()-1]);
  TH1F* TevatronMassUp=(TH1F*)TevatronMass->Clone("TevatronMassUp");
  TH1F* TevatronMassDn=(TH1F*)TevatronMass->Clone("TevatronMassDn");
  histogramStyle(*TevatronMass, kSig, false, 0.1);
  histogramStyle(*TevatronMassUp, kBkg, true, 0.1); 
  TevatronMassUp->SetFillColor(color_[1]);
  TevatronMassUp->SetFillStyle(1001);
  TevatronMassUp->SetLineColor(10);
  histogramStyle(*TevatronMassDn, kBkg, true, 0.1, 10); 
  TevatronMass  ->SetBinContent(1, mass);
  TevatronMassUp->SetBinContent(1, mass+masserr);
  TevatronMassDn->SetBinContent(1, mass-masserr);

  //loop all bins
  for(int bin=1; bin<=4; ++bin){
    // !!! define bin of interest !!! 
    int binOfInterest=bin;
    // perform top mass extraction
    std::pair< double, double >resultbin=extraction(verbose, luminosity, save, minx, maxx, nbinsx, dataMassDependence, binOfInterest, outputFolder, outputFile);
    extractedMass->SetBinContent(bin, resultbin.first);
    extractedMass->SetBinError(bin, std::abs(resultbin.second));
  }
  
  // create legend
  TLegend *leg = new TLegend(0.68, 0.74, 0.92, 0.85);
  legendStyle(*leg,"");
  TH1F* legtev=(TH1F*)TevatronMass->Clone("legtevatron");
  legtev->SetFillColor  (TevatronMassUp->GetFillColor());
  legtev->SetFillStyle  (TevatronMassUp->GetFillStyle());
  leg->AddEntry(extractedMass, "#splitline{extracted from}{CMS data}", "LP" );
  leg->AddEntry(legtev       , "Tevatron"               , "FLP");
 
  // draw extracted mass for all bins
  std::vector<TCanvas*> plotCanvas_;
  addCanvas(plotCanvas_);
  plotCanvas_[plotCanvas_.size()-1]->cd(0);
  TString title="mtopExtractionFromRhosAllBins";
  if(dataMassDependence) title+="DataMassDependence";
  plotCanvas_[plotCanvas_.size()-1]->SetName (title);
  plotCanvas_[plotCanvas_.size()-1]->SetTitle(title);
  if(!dataMassDependence) plotCanvas_[plotCanvas_.size()-1]->SetLogy(1);
  //double min=dataMassDependence ? 120.: 1.;
  //double max=dataMassDependence ? 230.: 500.;
  axesStyle(*extractedMass, xSecLabelName("rhos"), "m^{top} [GeV]");
  histogramStyle(*extractedMass, kData);
  //extractedMass->SetMaximum(max);
  //extractedMass->SetMinimum(min);
  extractedMass->GetYaxis()->SetNoExponent(true);
  extractedMass->Draw("AXIS");
  TevatronMassUp->Draw("hist same");
  TevatronMassDn->Draw("hist same");
  TevatronMass  ->Draw("hist same");
  extractedMass ->Draw("p e same");
  leg->Draw("same");
 extractedMass->Draw("AXIS same");
  DrawCMSLabels(true, luminosity, 0.04, false, false, false);
}

std::pair< double, double > extraction(int verbose, double luminosity, bool save, double minx, double maxx, double nbinsx, bool dataMassDependence, int binOfInterest, TString outputFolder, TString outputFile){

  // A) get measurement from data
  // open data result file
  TFile* datafile = TFile::Open(outputFile, "READ");
  // dont associate new objects with file to be able to close it in the end
  gROOT->cd();
  // get canvas for norm rhos
  TCanvas* canvasNom = (TCanvas*)(datafile->Get("finalXSec/rhosNorm")->Clone());
  // get data result plot with final errors from canvas
  TGraphAsymmErrors* dataRaw  = (TGraphAsymmErrors*)canvasNom->GetPrimitive("dataTotalError");
  //TGraphAsymmErrors* dataStat = (TGraphAsymmErrors*)canvas->GetPrimitive("dataStatError");=
  // binning
  std::map< TString, std::vector<double> > binning_ = makeVariableBinning();
  int Nbins = std::abs(binning_["rhos"][binning_["rhos"].size()-1]-binning_["rhos"][0])*100;
  // get histogram in correct binning
  TH1F* data= new TH1F("dataRhoSNorm"+getTStringFromInt(binOfInterest), "dataRhoSNorm"+getTStringFromInt(binOfInterest), Nbins, binning_["rhos"][0], binning_["rhos"][binning_["rhos"].size()-1]);
  reBinTH1F(*data, binning_["rhos"], 0);
  // refill TGraphAsymmErrors to rebinned histo
  for(int bin=1; bin<=data->GetNbinsX(); ++bin){
    data->SetBinContent(bin, dataRaw->GetY()[bin]);
    double err=dataRaw->GetErrorYhigh(bin);
    if(err<dataRaw->GetErrorYlow(bin)) err=dataRaw->GetErrorYlow(bin);
    data->SetBinError(bin, err);
  }
  std::cout << "bin: [" << data->GetBinLowEdge(binOfInterest) << ".." << data->GetBinLowEdge(binOfInterest+1) << "]" <<  std::endl; 
  // get values for different top masses
  std::vector<double > MassPointsData_;
  std::vector<TH1F*  > data_;
  if(dataMassDependence) MassPointsData_.push_back(169.5);
  MassPointsData_.push_back(172.5);
  if(dataMassDependence) MassPointsData_.push_back(175.5);
  TCanvas* canvasUp = (TCanvas*)(datafile->Get("xSec/sysTopMassUp/rhosNorm"  )->Clone("dataCanvUp"));
  TCanvas* canvasDn = (TCanvas*)(datafile->Get("xSec/sysTopMassDown/rhosNorm")->Clone("dataCanvDn"));
  TH1F* dataUp= (TH1F*)(canvasUp->GetPrimitive("rhoskData")->Clone("dataUp"));
  TH1F* dataDn= (TH1F*)(canvasDn->GetPrimitive("rhoskData")->Clone("dataDn"));
  if(dataMassDependence) data_.push_back((TH1F*)dataDn->Clone("measurementDn"     ));
  data_.push_back((TH1F*)data  ->Clone("measurementCentral"));
  if(dataMassDependence) data_.push_back((TH1F*)dataUp->Clone("measurementUp"     ));
  // extract uncertainty for bin of interest from central mass point 
  double central =data->GetBinContent(binOfInterest);
  double errorAbs=data->GetBinError  (binOfInterest);
  double errRel=std::abs(1.-(central+errorAbs)/central);
  //double up    =central+errorAbs;
  //double dn    =central-errorAbs;
  if(verbose>0) std::cout << "central data result: " << central << "+/-" << errorAbs << " (=" << errRel*100 << "% unc.)" << std::endl;

  // collect rhos data results from bin of interest for different masses in one separate plot
  TH1F* measurement= new TH1F("CMSdata"+getTStringFromInt(binOfInterest), "CMSdata"+getTStringFromInt(binOfInterest), nbinsx, minx, maxx);
  // loop samples
  for( unsigned int masspoint=0; masspoint<data_.size(); ++masspoint ){
    double value=data_[masspoint]->GetBinContent(binOfInterest);
    if(verbose>0) std::cout << "data(" << MassPointsData_[masspoint] << "GeV): " << value << std::endl;
    measurement->SetBinContent(measurement->FindBin(MassPointsData_[masspoint]), value   );
    measurement->SetBinError  (measurement->FindBin(MassPointsData_[masspoint]), errorAbs);
  }
  histogramStyle(*measurement, kData, false, 1.3, color_[0]);
  measurement->SetMarkerColor(color_[0]);
  measurement->SetMarkerStyle(33);
  // keep modified versions for drawing
  TH1F* measNomOnly   =((TH1F*)(measurement->Clone("measurementNominalOnly")));
  TH1F* measNonNomOnly=((TH1F*)(measurement->Clone("measurementNonNominal" )));
  for( unsigned int masspoint=0; masspoint<data_.size(); ++masspoint ){
    double value=data_[masspoint]->GetBinContent(binOfInterest);
    if(value!=central) measNomOnly->SetBinContent(measNomOnly->FindBin(MassPointsData_[masspoint]), 0.);
    measNonNomOnly->SetBinError(measNonNomOnly->FindBin(MassPointsData_[masspoint]), 0.);
  }
  // do a linear fit of the mass dependence
  TF1* lindata=new TF1("linFitdata", "[0]*x+[1]", minx, maxx);
  lindata->SetLineColor(measurement->GetLineColor());
  lindata->SetLineWidth(2);
  TString option="Q";
  if(verbose>0)option="";
  if(verbose>1)option="V";
  option+="R";
  measurement->Fit(lindata, option,"",MassPointsData_[0]-0.5, MassPointsData_[MassPointsData_.size()-1]+0.5);
  if(!dataMassDependence){
    lindata->SetParameter(0, 0.     );
    lindata->SetParameter(1, central);
  }
  double adata=lindata->GetParameter(0);
  double bdata=lindata->GetParameter(1);
//   TF1* lindataUp=new TF1("linFitdataUp", "[0]*x+[1]", minx, maxx);
//   TF1* lindataDn=new TF1("linFitdataDn", "[0]*x+[1]", minx, maxx);
//   lindataUp->SetParameter(0, adata);
//   lindataDn->SetParameter(0, adata);
//   lindataUp->SetParameter(1, bdata+errorAbs);
//   lindataDn->SetParameter(1, bdata-errorAbs);

  // create data band plot
  TH1F* measurementCentral= new TH1F  ("CMSdataNom"+getTStringFromInt(binOfInterest), "CMSdataNom"+getTStringFromInt(binOfInterest)    , nbinsx, minx, maxx);
  measurementCentral->Add(lindata);
  histogramStyle(*measurementCentral, kSig, false, 0.1);
  TH1F* measurementUp= new TH1F("CMSdataUp"+getTStringFromInt(binOfInterest), "CMSdataUp"+getTStringFromInt(binOfInterest), nbinsx, minx, maxx);
  //measurement->Add(lindataUp);
  histogramStyle(*measurementUp, kBkg, true, 0.1); 
  measurementUp->SetFillColor(color_[1]);
  measurementUp->SetFillStyle(1001);
  measurementUp->SetLineColor(10);
  TH1F* measurementDn= new TH1F("CMSdataDn"+getTStringFromInt(binOfInterest), "CMSdataDn"+getTStringFromInt(binOfInterest), nbinsx, minx, maxx);
  //measurementDn->Add(lindataDn);
  histogramStyle(*measurementDn, kBkg, true, 0.1, 10); 
  for(int bin=1; bin<=measurementCentral->GetNbinsX(); ++bin){
    measurementUp->SetBinContent(bin, measurementCentral->GetBinContent(bin)+errorAbs);
    measurementDn->SetBinContent(bin, measurementCentral->GetBinContent(bin)-errorAbs);
  }

  // B) get prediction with top mass dependence
  //  load rootfiles
  std::vector<TFile* > file_;
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/TopMassDown/combinedDiffXSecSigTopMassDownSummer12PF.root", "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/combinedDiffXSecSigSummer12PF.root"                       , "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/TopMassUp/combinedDiffXSecSigTopMassUpSummer12PF.root"    , "Open"));
  std::vector<double > mtop_;
  // fill mass indication
  mtop_.push_back(169.5);
  mtop_.push_back(172.5);
  mtop_.push_back(175.5);

  // get rhos plots
  std::vector<TH1F* > rhosMC_;
  // loop samples
  for(int sample=0; sample<(int)file_.size(); ++sample ){
    // get plot
    TH1F* temp=(TH1F*)((file_[sample]->Get("compositedHadronGenPhaseSpace/rhosGen"))->Clone("temp"));
    // rebin it
    reBinTH1F(*temp, binning_["rhos"], 0);
    // divide by integral and binwidth
    double N=temp->Integral(1, temp->GetNbinsX());
    for(int i=1; i<= temp->GetNbinsX(); i++){
      temp->SetBinContent(i, ( (double)(temp->GetBinContent(i)) / (N*temp->GetBinWidth(i)) ) );
    }
    // keep it in vector
    rhosMC_.push_back((TH1F*)temp->Clone(TString("rhosMC")+getTStringFromInt(sample)));  
  }

  // collect rhos results from last bin for different masses is separate plot
  TH1F* MC= new TH1F("CMSMC", "CMSMC", nbinsx, minx, maxx);
  //reBinTH1F(*data, mtop_,0);
  // loop samples
  for( unsigned int sample=0; sample<file_.size(); ++sample ){
    double value=rhosMC_[sample]->GetBinContent(binOfInterest);
    if(verbose>0) std::cout << "MC(" << mtop_[sample] << "GeV): " << value << std::endl;
    MC->SetBinContent(MC->FindBin(mtop_[sample]), value);
  }
  histogramStyle(*MC, kData, false, 1.2, kGreen);
  // do a linear fit of the mass dependence
  TF1* lin=new TF1("linFit", "[0]*x+[1]", minx, maxx);
  lin->SetLineColor(MC->GetLineColor());
  lin->SetLineWidth(2);
  MC->Fit(lin,option,"",mtop_[0]-0.5, mtop_[mtop_.size()-1]+0.5);
  double a=lin->GetParameter(0);
  double b=lin->GetParameter(1);
  // C) calculate intersection
  //double mresult=(central-b)/a;
  double mresultfit=(b-bdata)/(adata-a);
  double centralfit=adata*mresultfit+bdata;
  double mup=(b-(bdata+errorAbs))/(adata-a);
  double mdn=(b-(bdata-errorAbs))/(adata-a);
  double up=adata*mup+(bdata+errorAbs);
  double dn=adata*mdn+(bdata-errorAbs);
  if(verbose>0){
    std::cout << "mtop= (" << mdn << ".." << mresultfit << ".." << mup << ")" << std::endl; 
    if(verbose>0) std::cout << "mtop= " << mresultfit << " +" << mresultfit-mup << " -" << mdn-mresultfit << std::endl; 
  }

  // ---
  //    legend
  // ---
  TLegend *leg = new TLegend(0.61, 0.7, 0.96, 0.86);
  legendStyle(*leg,"");
  TH1F* legmeasurement=(TH1F*)measurementCentral->Clone("legdata");
  legmeasurement->SetFillColor  (measurementUp->GetFillColor());
  legmeasurement->SetFillStyle  (measurementUp->GetFillStyle());
  legmeasurement->SetMarkerStyle(measurement->GetMarkerStyle());
  legmeasurement->SetMarkerColor(measurement->GetMarkerColor());
  leg->AddEntry(legmeasurement, "CMS data"      , "FPL");
  leg->AddEntry(MC            , "CMS simulation", "P" );
  //leg->AddEntry(lin           , "linear fit"    , "L" );
  
  // D) create final plot
  std::vector<TCanvas*> plotCanvas_;
  addCanvas(plotCanvas_);
  plotCanvas_[plotCanvas_.size()-1]->cd(0);
  TString title="mtopExtractionFromRhosBin"+getTStringFromInt(binOfInterest);
  if(dataMassDependence) title+="DataMassDependence";
  plotCanvas_[plotCanvas_.size()-1]->SetName (title);
  plotCanvas_[plotCanvas_.size()-1]->SetTitle(title);
  double min=0.2;
  double max=0.8;
  if(binOfInterest==1){
    min=0.0005;
    max=0.06;
  }
  else if(binOfInterest==2){
    min=1.0;
    max=2.2;
  }
  else if(binOfInterest==3){
    min=1.8;
    max=3.4;
  }
  else if(binOfInterest==4){
    min=0.2;
    max=0.8;
  }
  MC->SetMaximum(max);
  MC->SetMinimum(min);
  MC->GetXaxis()->SetNoExponent(true);
  axesStyle(*MC, "m^{top}", "#frac{1}{#sigma} #frac{d#sigma}{d#rho_{S}} ("+getTStringFromDouble(data->GetBinLowEdge(binOfInterest))+" #leq#rho_{S}#leq "+getTStringFromDouble(data->GetBinLowEdge(binOfInterest+1))+")");
  MC->Draw("AXIS");
  measurementUp     ->Draw("hist same");
  measurementDn     ->Draw("hist same");
  measurementCentral->Draw("hist same");
  MC->Draw("p same");
  lin->Draw("same");
  MC->Draw("AXIS same");
  measNonNomOnly->Draw("p same");
  measNomOnly->Draw("p same");
  drawLine(mresultfit, min, mresultfit, centralfit, kBlack, 2, 2);
  drawLine(mup    , min, mup       , up     , kBlack, 1, 2);
  drawLine(mdn    , min, mdn       , dn     , kBlack, 1, 2);
  leg->Draw("same");
  DrawCMSLabels(true, luminosity, 0.04, false, false, false);
  // E) do saving 
  if(save){
    int initWarningLV=gErrorIgnoreLevel;
    if(verbose<=1) gErrorIgnoreLevel=kWarning;
    plotCanvas_[0]->Print(outputFolder+plotCanvas_[0]->GetName()+".eps");
    plotCanvas_[0]->Print(outputFolder+plotCanvas_[0]->GetName()+".png");
    saveToRootFile(outputFile, plotCanvas_[0], true, verbose-1, "massFromRhos");
    gErrorIgnoreLevel=initWarningLV;
  }
  std::cout << mresultfit << "+/-" << std::abs(mresultfit-mup) << std::endl;
  return make_pair(mresultfit, std::abs(mresultfit-mup));
}
