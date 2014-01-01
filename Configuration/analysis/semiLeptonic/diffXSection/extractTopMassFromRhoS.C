#include "basicFunctions.h"

std::pair< double, double > extraction(int verbose=0, double luminosity=19712., bool save=true, double minx=160., double maxx=185., double nbinsx=250, bool dataMassDependence=false, int binOfInterest=1, TString outputFolder="./", TString outputFile="diffXSecTopSemiLepHadronPhaseSpace.root");

void extractTopMassFromRhoS(int verbose=0, double luminosity=19712., bool save=true){

  // define some parameters
  // range of plot
  double minx2=130.;
  double maxx2=250.;
  double minx=160.;
  double maxx=190.;

  // fine bins
  double nbinsx=250.;
  // consider mass dependence of measurement
  bool dataMassDependence=true;  
  // where to store the output
  TString outputFolder="./diffXSecFromSignal/plots/combined/2012/rhos/";
  TString outputFile="diffXSecTopSemiLepHadronPhaseSpace.root";
  // comparison mass value (Tevatron)
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
  histogramStyle(*TevatronMass, kSig, false, 0.1);
  TevatronMass->SetBinContent(1,mass);
  TGraphAsymmErrors* TevatronMassErr= new TGraphAsymmErrors(nbinsx);  
  for(int bin=1; bin<=extractedMass->GetNbinsX(); ++bin){
    double binWidth             = extractedMass->GetBinWidth(bin);
    double binCenter            = extractedMass->GetBinCenter(bin);
    TevatronMassErr->SetPoint     (bin-1, binCenter, mass);
    TevatronMassErr->SetPointError(bin-1, 0.5*binWidth, 0.5*binWidth, masserr, masserr);
  }
  TevatronMassErr->SetLineColor(color_[kSig]);
  TevatronMassErr->SetMarkerColor(color_[kSig]);
  TevatronMassErr->SetFillColor(color_[kBkg]);
  TevatronMassErr->SetFillStyle(1001);
  TevatronMassErr->SetLineWidth(2);
  TevatronMassErr->SetLineStyle(1);
  TevatronMassErr->SetMarkerSize(0.1);

  //loop all bins
  for(int bin=1; bin<=4; ++bin){
    // !!! define bin of interest !!! 
    int binOfInterest=bin;
    // perform top mass extraction
    std::pair< double, double >resultbin=extraction(verbose, luminosity, save, (binOfInterest==2||binOfInterest==4) ? minx : minx2, (binOfInterest==2||binOfInterest==4) ? maxx : maxx2, nbinsx, dataMassDependence, binOfInterest, outputFolder, outputFile);
    extractedMass->SetBinContent(bin, resultbin.first);
    extractedMass->SetBinError(bin, std::abs(resultbin.second));
  }
  
  // linear fit to extracted mass values
  std::vector<TCanvas*> plotCanvas_;
  addCanvas(plotCanvas_);
  plotCanvas_[plotCanvas_.size()-1]->cd(0);
  TF1* combfit=new TF1("combfitdata", "[0]", extractedMass->GetBinLowEdge(1), extractedMass->GetBinLowEdge(extractedMass->GetNbinsX()+1));
  combfit->SetLineColor(kBlue);
  combfit->SetLineWidth(3);
  TString option="Q";
  if(verbose>0)option="";
  if(verbose>1)option="V";
  option+="0";
  extractedMass->Fit(combfit, option,"",extractedMass->GetBinLowEdge(1), extractedMass->GetBinLowEdge(extractedMass->GetNbinsX()+1));
  double mcomb=combfit->GetParameter(0);
  double merr =combfit->GetParError(0);
  // histogram with fit result
  TH1F* CombMass= new TH1F("CombMass", "CombMass", 1, binning_["rhos"][0], binning_["rhos"][binning_["rhos"].size()-1]);
  histogramStyle(*CombMass, kSig, false, 0.1, kBlue);
  CombMass->SetBinContent(1, mcomb);
  TGraphAsymmErrors* massfinal= new TGraphAsymmErrors(nbinsx);  
  for(int bin=1; bin<=extractedMass->GetNbinsX(); ++bin){
    double binWidth             = extractedMass->GetBinWidth(bin);
    double binCenter            = extractedMass->GetBinCenter(bin);
    massfinal->SetPoint     (bin-1, binCenter, mcomb);
    massfinal->SetPointError(bin-1, 0.5*binWidth, 0.5*binWidth, merr, merr);
  }
  massfinal->SetLineColor(kBlue);
  massfinal->SetMarkerColor(kBlue);
  massfinal->SetFillColor(kBlue-9);
  massfinal->SetFillStyle(1001);
  massfinal->SetLineWidth(2);
  massfinal->SetLineStyle(1);
  massfinal->SetMarkerSize(0.1);

  std::cout << "mtop(combined)=" << mcomb << "+/-" << merr << "GeV" << std::endl;

  // create legend
  TLegend *leg = new TLegend(0.68, 0.64, 0.92, 0.85 );
  legendStyle(*leg,"");
  TH1F* legtev=(TH1F*)TevatronMass->Clone("legtevatron");
  legtev->SetFillColor  (TevatronMassErr->GetFillColor());
  legtev->SetFillStyle  (TevatronMassErr->GetFillStyle());
  TH1F* legcomb=(TH1F*)TevatronMass->Clone("legcomb");
  legcomb->SetLineColor(massfinal->GetLineColor());
  legcomb->SetLineWidth(massfinal->GetLineWidth());
  legcomb->SetFillColor(massfinal->GetFillColor());
  legcomb->SetFillStyle(massfinal->GetFillStyle());
  leg->AddEntry(extractedMass, "#splitline{extracted from}{CMS data}", "LP" );
  leg->AddEntry(legcomb      , "#splitline{fit to data points:}{"+getTStringFromDouble(mcomb, 1)+"#pm"+getTStringFromDouble(merr, 1)+" GeV}", "FLP");
  leg->AddEntry(legtev       , "Tevatron"               , "FLP");

  // draw extracted mass for all bins
  TString title="mtopExtractionFromRhosAllBins";
  if(dataMassDependence) title+="DataMassDependence";
  plotCanvas_[plotCanvas_.size()-1]->SetName (title);
  plotCanvas_[plotCanvas_.size()-1]->SetTitle(title);
  if(!dataMassDependence) plotCanvas_[plotCanvas_.size()-1]->SetLogy(1);
  axesStyle(*extractedMass, xSecLabelName("rhos"), "m^{top} [GeV]");
  histogramStyle(*extractedMass, kData);
  extractedMass->GetYaxis()->SetNoExponent(true);
  extractedMass->Draw("AXIS");
  massfinal->Draw("e2 same");
  CombMass->Draw("hist same");
  TevatronMassErr->Draw("e2 same");
  TevatronMass->Draw("hist same");
  extractedMass->Draw("p e same");
  leg->Draw("same");
  extractedMass->Draw("AXIS same");
  DrawCMSLabels(true, luminosity, 0.04, false, false, false);

  // saving 
  if(save){
    if(verbose>0) std::cout << "saving" << std::endl;
    int initWarningLV=gErrorIgnoreLevel;
    if(verbose<1) gErrorIgnoreLevel=kWarning;
    for(unsigned int plot=0; plot<=plotCanvas_.size()-1; ++plot){
      //if(verbose>1) std::cout << " - for " << outputFolder+plotCanvas_[plot]->GetName() << std::endl;
      plotCanvas_[plot]->Print(outputFolder+plotCanvas_[plot]->GetName()+".eps");
      plotCanvas_[plot]->Print(outputFolder+plotCanvas_[plot]->GetName()+".png");
      saveToRootFile(outputFile, plotCanvas_[plot], true, verbose-1, "massFromRhos");
    }
    gErrorIgnoreLevel=initWarningLV;
 } 

}

std::pair< double, double > extraction(int verbose, double luminosity, bool save, double minx, double maxx, double nbinsx, bool dataMassDependence, int binOfInterest, TString outputFolder, TString outputFile){

  // ============================  
  //  Set ROOT Style
  // ============================
  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  //TGaxis::SetMaxDigits(2);
  //myStyle.cd();
  //gROOT->SetStyle("HHStyle");
  //gROOT->ForceStyle();
  // A) get measurement from data
  // open data result file
  TFile* datafile = TFile::Open(outputFile, "READ");
  // dont associate new objects with file to be able to close it in the end
  gROOT->cd();
  // get canvas for norm rhos
  TCanvas* canvasNom = (TCanvas*)(datafile->Get("finalXSec/rhosNorm")->Clone());
  // get data result plot with final errors from canvas
  TGraphAsymmErrors* dataRaw  = (TGraphAsymmErrors*)((canvasNom->GetPrimitive("dataTotalError"))->Clone("dataTot" ));
  TGraphAsymmErrors* dataStat = (TGraphAsymmErrors*)((canvasNom->GetPrimitive("dataStatError" ))->Clone("dataStat"));
  // binning
  std::map< TString, std::vector<double> > binning_ = makeVariableBinning();
  int Nbins = std::abs(binning_["rhos"][binning_["rhos"].size()-1]-binning_["rhos"][0])*100;
  // get histogram in correct binning
  TH1F* data= new TH1F("dataRhoSNorm"+getTStringFromInt(binOfInterest), "dataRhoSNorm"+getTStringFromInt(binOfInterest), Nbins, binning_["rhos"][0], binning_["rhos"][binning_["rhos"].size()-1]);
  reBinTH1F(*data, binning_["rhos"], 0);
  // refill TGraphAsymmErrors to rebinned histo
  for(int bin=1; bin<=data->GetNbinsX(); ++bin){
    //std::cout << dataRaw ->GetY()[bin] << std::endl;
    //std::cout << dataStat->GetY()[bin] << std::endl;
    data->SetBinContent(bin, dataRaw->GetY()[bin]);
    double err=dataRaw->GetErrorYhigh(bin);
    if(err<dataRaw->GetErrorYlow(bin)) err=dataRaw->GetErrorYlow(bin);
    data->SetBinError(bin, err);
  }
  axesStyle(*data, xSecLabelName("rhos"), "#frac{1}{#sigma} #frac{d#sigma}{d#rho_{S}}" , 0., 4.);
  data->SetTitleOffset(0.8*data->GetTitleOffset("Y"), "Y");
  std::cout << "bin: [" << data->GetBinLowEdge(binOfInterest) << ".." << data->GetBinLowEdge(binOfInterest+1) << "]" <<  std::endl; 
  // get values for different top masses
  std::vector<double > MassPointsData_;
  std::vector<TH1F*  > data_;
  if(dataMassDependence){
    MassPointsData_.push_back(161.5);
    MassPointsData_.push_back(163.5);
    MassPointsData_.push_back(166.5);
    MassPointsData_.push_back(169.5);
  }
  MassPointsData_.push_back(172.5);
  if(dataMassDependence){
    MassPointsData_.push_back(175.5);
    MassPointsData_.push_back(178.5);
    MassPointsData_.push_back(181.5);
    MassPointsData_.push_back(184.5);
  }
  TCanvas* canvasUp  = (TCanvas*)(datafile->Get("xSec/sysTopMassUp/rhosNorm"   )->Clone("dataCanvUp" ));
  TCanvas* canvasDn  = (TCanvas*)(datafile->Get("xSec/sysTopMassDown/rhosNorm" )->Clone("dataCanvDn" ));
  TCanvas* canvasUp2 = (TCanvas*)(datafile->Get("xSec/sysTopMassUp2/rhosNorm"  )->Clone("dataCanvUp2"));
  TCanvas* canvasDn2 = (TCanvas*)(datafile->Get("xSec/sysTopMassDown2/rhosNorm")->Clone("dataCanvDn2"));
  TCanvas* canvasUp3 = (TCanvas*)(datafile->Get("xSec/sysTopMassUp3/rhosNorm"  )->Clone("dataCanvUp3"));
  TCanvas* canvasDn3 = (TCanvas*)(datafile->Get("xSec/sysTopMassDown3/rhosNorm")->Clone("dataCanvDn3"));
  TCanvas* canvasUp4 = (TCanvas*)(datafile->Get("xSec/sysTopMassUp4/rhosNorm"  )->Clone("dataCanvUp4"));
  TCanvas* canvasDn4 = (TCanvas*)(datafile->Get("xSec/sysTopMassDown4/rhosNorm")->Clone("dataCanvDn4"));
  TH1F* dataUp = (TH1F*)(canvasUp ->GetPrimitive("rhoskData")->Clone("dataUp" ));
  TH1F* dataDn = (TH1F*)(canvasDn ->GetPrimitive("rhoskData")->Clone("dataDn" ));
  TH1F* dataUp2= (TH1F*)(canvasUp2->GetPrimitive("rhoskData")->Clone("dataUp2"));
  TH1F* dataDn2= (TH1F*)(canvasDn2->GetPrimitive("rhoskData")->Clone("dataDn2"));
  TH1F* dataUp3= (TH1F*)(canvasUp3->GetPrimitive("rhoskData")->Clone("dataUp3"));
  TH1F* dataDn3= (TH1F*)(canvasDn3->GetPrimitive("rhoskData")->Clone("dataDn3"));
  TH1F* dataUp4= (TH1F*)(canvasUp4->GetPrimitive("rhoskData")->Clone("dataUp4"));
  TH1F* dataDn4= (TH1F*)(canvasDn4->GetPrimitive("rhoskData")->Clone("dataDn4"));
 if(dataMassDependence){
    data_.push_back((TH1F*)dataDn4->Clone("measurementDn4"    ));
    data_.push_back((TH1F*)dataDn3->Clone("measurementDn3"    ));
    data_.push_back((TH1F*)dataDn2->Clone("measurementDn2"    ));
    data_.push_back((TH1F*)dataDn ->Clone("measurementDn"     ));
  }
  data_.push_back((TH1F*)data  ->Clone("measurementCentral"));
  if(dataMassDependence){
    data_.push_back((TH1F*)dataUp ->Clone("measurementUp"     ));
    data_.push_back((TH1F*)dataUp2->Clone("measurementUp2"    ));
    data_.push_back((TH1F*)dataUp3->Clone("measurementUp3"    ));
    data_.push_back((TH1F*)dataUp4->Clone("measurementUp4"    ));
  }
  // extract uncertainty for bin of interest from central mass point 
  double central =data->GetBinContent(binOfInterest);
  double errorAbs=data->GetBinError  (binOfInterest);
  double errRel=std::abs(1.-(central+errorAbs)/central);
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
  histogramStyle(*measurement, kData, false, 1.5, color_[0]);
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
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/TopMassDown/combinedDiffXSecSigTopMassDown4Summer12PF.root", "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/TopMassDown/combinedDiffXSecSigTopMassDown3Summer12PF.root", "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/TopMassDown/combinedDiffXSecSigTopMassDown2Summer12PF.root", "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/TopMassDown/combinedDiffXSecSigTopMassDownSummer12PF.root" , "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/combinedDiffXSecSigSummer12PF.root"                        , "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/TopMassUp/combinedDiffXSecSigTopMassUpSummer12PF.root"     , "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/TopMassUp/combinedDiffXSecSigTopMassUp2Summer12PF.root"    , "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/TopMassUp/combinedDiffXSecSigTopMassUp3Summer12PF.root"    , "Open"));
  file_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/TopMassUp/combinedDiffXSecSigTopMassUp4Summer12PF.root"    , "Open"));
  std::vector<double > mtop_;
  // fill mass indication
  mtop_.push_back(161.5);
  mtop_.push_back(163.5);
  mtop_.push_back(166.5);
  mtop_.push_back(169.5);
  mtop_.push_back(172.5);
  mtop_.push_back(175.5);
  mtop_.push_back(178.5);
  mtop_.push_back(181.5);
  mtop_.push_back(184.5);

  // C) get prediction with theory parameter dependence
  std::vector<TFile* > fileSys_;
  //  load rootfiles
  fileSys_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/ScaleUp/combinedDiffXSecSigScaleUpSummer12PF.root"     , "Open"));
  fileSys_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/ScaleDown/combinedDiffXSecSigScaleDownSummer12PF.root" , "Open"));
  fileSys_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/MatchUp/combinedDiffXSecSigMatchUpSummer12PF.root"     , "Open"));
  fileSys_.push_back(TFile::Open("/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV_doubleKinFit/MatchDown/combinedDiffXSecSigMatchDownSummer12PF.root" , "Open"));

  // get rhos(mtop) plots
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

  // get rhos(parameter) plots
  std::vector<TH1F* > rhosMCsys_;
  // loop samples
  for(int sample=0; sample<(int)fileSys_.size(); ++sample ){
    // get plot
    TH1F* temp=(TH1F*)((fileSys_[sample]->Get("compositedHadronGenPhaseSpace/rhosGen"))->Clone("tempSys"));
    // rebin it
    reBinTH1F(*temp, binning_["rhos"], 0);
    // divide by integral and binwidth
    double N=temp->Integral(1, temp->GetNbinsX());
    for(int i=1; i<= temp->GetNbinsX(); i++){
      temp->SetBinContent(i, ( (double)(temp->GetBinContent(i)) / (N*temp->GetBinWidth(i)) ) );
    }
    // keep it in vector
    rhosMCsys_.push_back((TH1F*)temp->Clone(TString("rhosMCsys")+getTStringFromInt(sample)));  
  }

  // collect rhos results from bin of interest for different masses is separate plot
  double MCnom=0.;
  TH1F* MC= new TH1F("CMSMC", "CMSMC", nbinsx, minx, maxx);
  //reBinTH1F(*data, mtop_,0);
  // loop samples
  for( unsigned int sample=0; sample<file_.size(); ++sample ){
    double value=rhosMC_[sample]->GetBinContent(binOfInterest);
    if(verbose>0) std::cout << "MC(" << mtop_[sample] << "GeV): " << value << std::endl;
    MC->SetBinContent(MC->FindBin(mtop_[sample]), value);
    if(mtop_[sample]==172.5) MCnom=value;
  }
  histogramStyle(*MC, kData, false, 1.2, kGreen-2);
  

  // extract values for parameter dependence
  double MCnomUnc=0.;
  for( unsigned int sample=0; sample<fileSys_.size(); sample=sample+2){
    double valueUp=rhosMCsys_[sample  ]->GetBinContent(binOfInterest);
    double valueDn=rhosMCsys_[sample+1]->GetBinContent(binOfInterest);
    double unc=0.5*(std::abs(valueUp-MCnom)+std::abs(valueDn-MCnom));
    MCnomUnc+=unc;
    //std::cout << "c : " << MCnom << std::endl;
    //std::cout << "up=" << fileSys_[sample  ]->GetName() << ": " << valueUp << std::endl;
    //std::cout << "dn=" << fileSys_[sample+1]->GetName() << ": " << valueDn << std::endl;
  }
  
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
  double mup=(b-MCnomUnc-(bdata+errorAbs))/(adata-a);
  double mdn=(b+MCnomUnc-(bdata-errorAbs))/(adata-a);
  double up=adata*mup+(bdata+errorAbs);
  double dn=adata*mdn+(bdata-errorAbs);
  if(verbose>0){
    std::cout << "mtop= (" << mdn << ".." << mresultfit << ".." << mup << ")" << std::endl; 
    if(verbose>0) std::cout << "mtop= " << mresultfit << " +" << mresultfit-mup << " -" << mdn-mresultfit << std::endl; 
  }
  TGraphAsymmErrors* MCunc= new TGraphAsymmErrors(nbinsx);  
  for(int bin=1; bin<=measurementCentral->GetNbinsX(); ++bin){
    //double binEdgeDown          = measurementCentral->GetBinLowEdge(bin);
    //double binEdgeUp            = measurementCentral->GetBinLowEdge(bin+1);
    double binWidth             = measurementCentral->GetBinWidth(bin);
    double binCenter            = measurementCentral->GetBinCenter(bin);
    double value=a*binCenter+b;
    MCunc->SetPoint     (bin-1, binCenter, value);
    MCunc->SetPointError(bin-1, 0.5*binWidth, 0.5*binWidth, MCnomUnc, MCnomUnc);
  }
  MCunc->SetLineColor(kGreen);
  MCunc->SetMarkerColor(kGreen);
  MCunc->SetFillColor(kGreen);
  MCunc->SetFillStyle(3344);
  MCunc->SetLineWidth(1);
  MCunc->SetLineStyle(1);
  MCunc->SetMarkerSize(0.1);
  
  // chi2 approach for binOfInterest
  TH1F* chi2CMS= new TH1F  ("chi2Bin"+getTStringFromInt(binOfInterest), "chi2Bin"+getTStringFromInt(binOfInterest), nbinsx, minx, maxx);
  histogramStyle(*chi2CMS, kData, false, 1.3);
  axesStyle(*chi2CMS, "m^{top}", "#chi^{2} ("+getTStringFromDouble(data->GetBinLowEdge(binOfInterest))+" #leq#rho_{S}#leq "+getTStringFromDouble(data->GetBinLowEdge(binOfInterest+1))+")");
  chi2CMS->GetXaxis()->SetNoExponent(true);
  // uncertainty MC pred.+ data measurement from central masspoint
  double totUnc=MCnomUnc*MCnomUnc+errorAbs*errorAbs;
  // loop all masspoints
  for( unsigned int masspoint=0; masspoint<data_.size(); ++masspoint ){
    double valuedata=data_  [masspoint]->GetBinContent(binOfInterest);
    double valueMC  =rhosMC_[masspoint]->GetBinContent(binOfInterest);
    double currentmasspoint=mtop_[masspoint];
    double chi2=std::abs(valuedata-valueMC)*std::abs(valuedata-valueMC)/totUnc;
    chi2CMS->SetBinContent(chi2CMS->FindBin(currentmasspoint), chi2);
  }

  // ---
  //    legend
  // ---
  TLegend *leg = new TLegend(0.61, (binOfInterest!=3) ? 0.7 : 0.25, 0.96, (binOfInterest!=3) ? 0.86 : 0.41);
  legendStyle(*leg,"");
  TH1F* legmeasurement=(TH1F*)measurementCentral->Clone("legdata");
  legmeasurement->SetFillColor  (measurementUp->GetFillColor());
  legmeasurement->SetFillStyle  (measurementUp->GetFillStyle());
  legmeasurement->SetMarkerStyle(measurement->GetMarkerStyle());
  legmeasurement->SetMarkerColor(measurement->GetMarkerColor());
  legmeasurement->SetMarkerSize (measurement->GetMarkerSize() );
  TH1F* legMC=(TH1F*)MC->Clone("legMC");
  legMC->SetFillColor(MCunc->GetFillColor());
  legMC->SetFillStyle(MCunc->GetFillStyle());
  leg->AddEntry(legmeasurement, "CMS data"      , "FLP");
  leg->AddEntry(legMC         , "CMS simulation", "PLF" );
  //leg->AddEntry(lin           , "linear fit"    , "L" );
  
  // D) create final plots
  std::vector<TCanvas*> plotCanvas_;
  // intersection method
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
  MCunc->Draw("p e2 same");
  MC   ->Draw("p same");
  lin->Draw("same");
  measNonNomOnly->Draw("p same");
  measNomOnly->Draw("p same");
  MC->Draw("AXIS same");
  if(mresultfit<=maxx&&mresultfit>=minx) drawLine(mresultfit, min, mresultfit, centralfit, kBlack, 2, 2);
  if(mup<=maxx       &&mup>=minx       ) drawLine(mup       , min, mup       , up        , kBlack, 1, 2);
  if(mdn<=maxx       &&mdn>=minx       ) drawLine(mdn       , min, mdn       , dn        , kBlack, 1, 2);
  leg->Draw("same");
  DrawCMSLabels(true, luminosity, 0.04, false, false, false);
  // chi2 method
  addCanvas(plotCanvas_);
  plotCanvas_[plotCanvas_.size()-1]->cd(0);
  TString title2="mtopChi2ScanRhosBin"+getTStringFromInt(binOfInterest);
  if(dataMassDependence) title2+="DataMassDependence";
  plotCanvas_[plotCanvas_.size()-1]->SetName (title2);
  plotCanvas_[plotCanvas_.size()-1]->SetTitle(title2);
  chi2CMS->Draw("p");
  
  // E) Canvas with different mass predictions
  //    duplicate canvas from nominal data measurement
  if(binOfInterest==1){
    gROOT->cd();
    std::cout << "create cross section for different masses plot" << std::endl;
    //plotCanvas_.push_back((TCanvas*)(canvasNom->Clone()));
    addCanvas(plotCanvas_);  
    plotCanvas_[plotCanvas_.size()-1]->cd(0);
    plotCanvas_[plotCanvas_.size()-1]->SetName ("finalXSecrhosNormCombinedHadronLvPSMassCurves");
    plotCanvas_[plotCanvas_.size()-1]->SetTitle("finalXSecrhosNormCombinedHadronLvPSMassCurves");
    // remove other MC curves
    data->Draw("AXIS");
    // style for mass samples
    std::vector <int > colorMC_;
    colorMC_.push_back(6         );
    colorMC_.push_back(kBlue     );
    colorMC_.push_back(kGreen+1  );
    colorMC_.push_back(kGreen+3  );
    colorMC_.push_back(kRed      );
    colorMC_.push_back(kAzure+8  );
    colorMC_.push_back(kOrange+3 ); 
    colorMC_.push_back(kMagenta+2); 
    colorMC_.push_back(kOrange+8 );
    std::vector <int > style_;
    style_.push_back(2);
    style_.push_back(10);
    style_.push_back(4);
    style_.push_back(6);
    style_.push_back(1);
    style_.push_back(7);
    style_.push_back(8);
    style_.push_back(9);
    style_.push_back(3);
    // create legend
    TLegend *legMasses = new TLegend(0.7, 0.4 , 1.2, 0.8 );
    TLegend *legDat    = new TLegend(0.7, 0.75, 1.2, 0.95);
    legDat->AddEntry(data, "Data", "LP");
    legendStyle(*legMasses,"#splitline{MadGraph+Pythia}{m_{top}[GeV]=}");
    legendStyle(*legDat   , "");
    // loop mass points
    for(int sample=0; sample<(int)file_.size(); ++sample ){
      // get and draw curves
      rhosMC_[sample]->SetLineColor(  colorMC_[sample]);
      rhosMC_[sample]->SetMarkerColor(colorMC_[sample]);
      rhosMC_[sample]->SetLineWidth(3);
      rhosMC_[sample]->SetLineStyle(style_[sample]);
      rhosMC_[sample]->Draw("hist same");
      // add legend entry
      double val=mtop_[sample];
      legMasses->AddEntry(rhosMC_[sample], Form("%2.1f", val), "L" );
    }
    // redraw data
    dataStat->Draw("e p same");
    data    ->Draw("e p same");
    // draw legend
    legMasses->Draw("same");
    legDat   ->Draw("same");
    // draw labels
    DrawDecayChLabel("e/#mu + Jets Combined");
    DrawCMSLabels(prelim, 0.5*(constLumiMuon+constLumiElec), 0.04, false, false, false);
    // saving
    TCanvas* tempCanv=(TCanvas*)(plotCanvas_[plotCanvas_.size()-1]->Clone());
    int initWarningLV=gErrorIgnoreLevel;
    if(verbose<1) gErrorIgnoreLevel=kWarning;   tempCanv->Print(outputFolder+tempCanv->GetName()+".eps");
    tempCanv->Print(outputFolder+tempCanv->GetName()+".png");
    saveToRootFile(outputFile, tempCanv, true, verbose-1, "massFromRhos");
    gErrorIgnoreLevel=initWarningLV;
    // canvas with ratio
    gROOT->cd();
    bool drawRat =true;
    bool drawRat2=false;
    std::cout << "create ratios for cross section for different masses" << std::endl;
    if(drawRat){
      // adapt some stylings
      legMasses->SetY1(1.12*legMasses->GetY1());
      data->SetLabelSize(0.);
      data->SetTitleSize(0.);
      data->SetMaximum(5.);
      rhosMC_[0]->SetLabelSize(0.85*rhosMC_[0]->GetLabelSize());
      rhosMC_[0]->SetTitleSize(1.3*rhosMC_[0]->GetTitleSize());
      rhosMC_[0]->SetLabelSize(1.3*rhosMC_[0]->GetLabelSize("y"), "Y");
      rhosMC_[0]->SetTitleSize(1.4*rhosMC_[0]->GetTitleSize("y"), "Y");

      plotCanvas_[plotCanvas_.size()-1]->Update();
      // ratio function
      plotCanvas_.push_back(drawFinalResultRatio((TH1F*)data->Clone("dataTotRat"), 0.35, 1.75, myStyle, verbose, rhosMC_, (TCanvas*)(plotCanvas_[plotCanvas_.size()-1]->Clone()), -1., -1., dataStat, true));
      plotCanvas_[plotCanvas_.size()-1]->cd();
      plotCanvas_[plotCanvas_.size()-1]->SetName ("ratioFinalXSecrhosNormCombinedHadronPhaseSpaceMassCurves");
      plotCanvas_[plotCanvas_.size()-1]->SetTitle("ratioFinalXSecrhosNormCombinedHadronPhaseSpaceMassCurves");
      plotCanvas_[plotCanvas_.size()-1]->Draw();
      plotCanvas_[plotCanvas_.size()-1]->Update();
    }
    if(drawRat2){
     gPad->cd();
      //plotCanvas_[plotCanvas_.size()-1]->Draw();
      //plotCanvas_[plotCanvas_.size()-1]->Update();
      //data->Draw("hist same");
      for(int bin=1; bin<=data->GetNbinsX(); ++bin) std::cout << data->GetBinContent(bin) << std::endl;
      // error vector dummy
      std::vector<double> zeroerr_;
      for(int bin=1; bin<=rhosMC_[0]->GetNbinsX(); ++bin) zeroerr_.push_back(0.);
      std::cout << "- 1" << std::endl;
      // axis
      drawRatio(data, data, 0.6, 1.6, myStyle, 0, zeroerr_, "prediction", "data", "axis", kBlack, false);
      std::cout << "- 2" << std::endl;
      // MCs
      for(int sample=0; sample<(int)file_.size(); ++sample ){
	drawRatio(rhosMC_[sample], data, 0.6, 1.6, myStyle, 0, zeroerr_, "prediction", "data", "hist same", rhosMC_[sample]->GetLineColor(), false);
      }
      std::cout << "- 3" << std::endl;
      // data error vector
      std::vector<double> err_;
      for(int bin=1; bin<=data->GetNbinsX(); ++bin) err_.push_back(data->GetBinError(bin)/data->GetBinContent(bin));
      // axis
      drawRatio(data, data, 0.6, 1.6, myStyle, 0, err_, "prediction", "data", "e p same", kBlack, false);
    }
  }

  // F) do saving 
  if(save){
    gROOT->cd();
    int initWarningLV=gErrorIgnoreLevel;
    if(verbose<1) gErrorIgnoreLevel=kWarning;
    for(unsigned int plot=0; plot<=plotCanvas_.size()-1; ++plot){
      //std::cout << plotCanvas_[plot]->GetName() << std::endl;
      if(!TString(plotCanvas_[plot]->GetName()).Contains("final")){
	plotCanvas_[plot]->Print(outputFolder+plotCanvas_[plot]->GetName()+".eps");
	plotCanvas_[plot]->Print(outputFolder+plotCanvas_[plot]->GetName()+".png");
	saveToRootFile(outputFile, plotCanvas_[plot], true, verbose-1, "massFromRhos");
	gROOT->cd();
      }
    }
    gErrorIgnoreLevel=initWarningLV;
  }
  std::cout << "intersection method: " << mresultfit << "+/-" << std::abs(mresultfit-mup) << std::endl;
  return make_pair(mresultfit, std::abs(mresultfit-mup));
}
