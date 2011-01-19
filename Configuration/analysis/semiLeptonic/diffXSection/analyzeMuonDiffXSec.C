// ---------description---------------------------------
// -----------------------------------------------------
// this Makro determines the inclusive cross section for 
// ttbar semileptonic decay to muon and the differential, 
// normalized cross section ( d#sigma/dx(#mu)/#sigma )
// for x = pt, eta and phi (of the muon) for all events
// (dominated by W+jets) decaying into l+jets. In the 2nd
// case after event selection the QCD bkg estimated via
// ABCD method is substracted and l+jets MC based efficiency
// corrections were applied (inclusive 1, 2, 3 and 4 jet bin). 
// For the inclusive top cross section, two methods are 
// applied: a) take the numbers from above and correct for
// W+jets background estimated via charge asymmetry method
// b) requiring >= 4 jets, and at least 1 additional btag 
// and apply MC based top efficiency corrections
// this file can be used for probing the following systematic 
// variations: JES, Luminosity, topMC (MC@NLO /MADGRAPH),
// MC-efficiencies. For each varation aboves results are 
// saved within single .txt file. These are used then for
// the determination of systematic errors.
// -----------------------------------------------------

#include "styleHelper.h"
//#include "analyzeMuonDiffXTemplateFit.h"

void canvasStyle(TCanvas& canv);
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2, float xLabelSize = 0.06);
template <class T>
void writeToFile(T output, TString file="crossSectionCalculation.txt", bool append=1);
int roundToInt(double value, bool roundDown=false);
TString getTStringFromInt(int i);
TString getTStringFromDouble(double d);
TString jetLabel(TString input);
TString samples(int sampleEnum);
TH1F* divideByBinwidth(TH1F* histo, bool calculateError=true);
double getABCDNumbers( TString njets, bool loadValues, TString file);
double getMCEffiencies(TString variable, int bin, int njets, bool loadValues, bool useNLO=false, TString JES="", TString jetTyp = "", double scaleFactor = 0.01, TString putSysOn="");
TString sampleLabel(unsigned int sample);
double getInclusiveMCEff(TString topORlep, int njets, bool loadValues, bool useNLO=false, TString JES="", TString jetTyp = "", double scaleFactor = 0.01, TString putSysOn="");
void DrawLabel(TString text, const double x1, const double y1, const double x2, const double y2, double textSize = 0.26);
void scaleByLumi(TH1F* histo, double lumi);
void drawLine(const double xmin, const double ymin, const double xmax, const double ymax, unsigned int color=kBlack);
void systematicError(const TString plot, const int jetMultiplicity, TH1& histo, const TString variable, TString up = "JES11", TString down = "JES09");
TH1F* systematicHisto(const TString plot, const int jetMultiplicity, TH1& histo, const TString variable, TString up = "JES11", TString down = "JES09");
double systematicError2(const TString plot, TH1& histo, int usedBin, TString up = "JES11", TString down = "JES09");

void analyzeMuonDiffXSec(double luminosity = 36100, bool save = true, bool loadValues = true, TString dataFile="./diffXSecFromSignal/data/DiffXSecData_Nov15PF.root", bool useNLO=false, TString JES="", double lumiShift=1.0, double EffScaleFactor=1.0, double QCDVariation=1.0, double WjetsVariation=1.0, double sTopVariation=1.0, double DiBosVariation=1.0, double ZjetsVariation=1.0, bool finalPlots=true, bool logartihmicPlots=true, TString jetTyp = "PF", TString up = "JES11", TString down = "JES09", TString putSysOn = "", double scaleFactor = 0.964155)
{ 

  // ---
  //    define settings for systematic variations
  // ---
  TString TopSample = "Mad";
  TString LuminosityVariation="Nominal";
  TString EffScale = "EffStd";
  TString SampleScale="SampleWeightStd";
//   TString QCDScale="QCDestimationStd";
//   TString WjetsScale="WjetsEstimationStd";
//   TString sTopScale="sTopEstimationStd";
//   TString DiBosScale="DiBosEstimationStd";
  if(useNLO      ) TopSample ="Nlo";
  luminosity*=lumiShift;
  if(lumiShift>1.0) LuminosityVariation = "Up";
  if(lumiShift<1.0) LuminosityVariation = "Down";
  if(EffScaleFactor>1.0) EffScale = "EffUp";
  if(EffScaleFactor<1.0) EffScale = "EffDown";
  if(QCDVariation>1.0) SampleScale = "QCDestimationUp";
  if(QCDVariation<1.0) SampleScale = "QCDestimationDown";
  if(WjetsVariation>1.0) SampleScale = "WjetsEstimationUp";
  if(WjetsVariation<1.0) SampleScale = "WjetsEstimationDown";
  if(sTopVariation>1.0) SampleScale = "sTopEstimationUp";
  if(sTopVariation<1.0) SampleScale = "sTopEstimationDown";
  if(DiBosVariation>1.0) SampleScale = "DiBosEstimationUp";
  if(DiBosVariation<1.0) SampleScale = "DiBosEstimationDown";
  if(ZjetsVariation>1.0) SampleScale = "ZjetsEstimationUp";
  if(ZjetsVariation<1.0) SampleScale = "ZjetsEstimationDown";
  // consider systematic variations -> read from .txt with different name and other line
  TString file ="crossSectionCalculation";
  TString file2 ="crossSectionCalculation";
  if(useNLO      ) file+="NLO";
  file+=JES;
  file+=putSysOn;
  file+=jetTyp;
  file2+=jetTyp;
  file+=".txt";  
  file2+=".txt";  

  // ---
  //    main function parameters
  // ---
  // save       : choose whether you want to save every plot as png and all within one ps file
  // loadValues : choose whether you want to load effiency corrections 
  //              and bkg estimation from crossSection.txt file
  // luminosity : choose luminosity [pb] for scaling of event numbers 
  //              lum is derived from this and used for legend as entry
  //TString lum  = getTStringFromDouble(luminosity/1000);
  TString lum = getTStringFromInt(roundToInt(luminosity/1000));
  TString lum2 = getTStringFromInt(roundToInt(luminosity));
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/earlyData/crossSection/";
  // useNLO      : if true, MC@NLO instead of MAGRAPH sample is used as reco input
  // JES        : choose "", "up", or "down" to use the corresponding MC samples with shifted JES
  // lumiShift  : quantify the scaling factor for the uncertainty of the luminosity
  // EffScaleFactor: quantify the scaling factor for the uncertainty of all determined efficiencies
  // QCDVariation  : quantify the scaling factor for the uncertainty of the QCD estimation
  // finalPlots : if true, systematic errors are derived, needs all systematic variations done
  //              before, cause values are read in from created .txt files
  // createPlots: choose if you want plots as output beside the numbers
  // logartihmicPlots: choose whether you want to see the plots with logarithmic axis
  TString log = "";
  if(logartihmicPlots) log = "Log";
  // finalPlots: choose if all systematic variations have been done and the corresponding results
  // are available as .txt file. Then systematic errors are automatically calculated and drawn.
  double createPlots=false;
  if(finalPlots) createPlots=true;

  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetEndErrorSize (8);
  //  gStyle->SetPalette(1);
  //  gStyle->SetErrorX(0); 

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/analysisRootFiles";
  TString fileName;
  for(int ienum = 0; ienum<10; ienum++){
    fileName = "./diffXSecFromSignal"+whichSample+"/muonDiffXSec";
    if(ienum==kSig)   fileName += "SigMadD6TFall10";
    if(ienum==kBkg)   fileName += "BkgMadD6TFall10";
    if(ienum==kSToptW)fileName += "SingleTopTWchannelMadZ2Fall10";
    if(ienum==kSTops) fileName += "SingleTopSchannelMadZ2Fall10";
    if(ienum==kSTopt) fileName += "SingleTopTchannelMadZ2Fall10";
    if(ienum==kWjets) fileName += "WjetsMadD6TFall10";
    if(ienum==kZjets) fileName += "ZjetsMadD6TFall10";
    if(ienum==kDiBos) fileName += "VVPytia6Z2Fall10";
    if(ienum==kQCD)   fileName += "QCDPythiaZ2Fall10";
    if(ienum!=kQCD &&
       (putSysOn=="" || 
	(putSysOn=="Vonly" && (ienum==kWjets || ienum==kZjets)) || 
	(putSysOn=="TTonly" && (ienum==kSig || ienum==kBkg)) || 
	(putSysOn=="VandTT" && (ienum==kWjets || ienum==kZjets || ienum==kSig || ienum==kBkg))))
      fileName += JES;
    fileName += jetTyp+".root";
    if(ienum==kData)  fileName = dataFile;

    files_.push_back(new TFile(fileName));
  }

  // ---
  //    get histograms
  // ---
  // create jet multiplicity indicator
  std::vector<TString> Njets_;
  TString jets[ 6 ] = { "Njets1", "Njets2", "Njets3", "Njets4", "Njets4Btag", "Njets3Btag" };
  Njets_.insert( Njets_.begin(), jets, jets + 6 );
  // create variable indicator for easy handling of pt, eta and phi
  std::vector<TString> variables_;
  TString variables[ 3 ] = { "pt", "eta", "phi" };
  variables_.insert( variables_.begin(), variables, variables + 3 );
  // create container for all histos
  std::map< TString, std::map <unsigned int, std::map <TString, TH1F*> > > histo_;
  // example: histo_["pt"][kWjets]["Njets1"]
  // ---------------------------------------
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      // loop samples
      for(unsigned int idx=0; idx<files_.size(); ++idx) {
	// a) reco
	histo_[variables_[var]][idx][Njets_[mult]] = (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/"+variables_[var]);
      }
      // b) gen from MC (top-sig+bkg&Wjets)
      if(mult<4){
	histo_[variables_[var]][kGenSig   ][Njets_[mult]] = (TH1F*)(files_[kSig   ]->Get("analyzeTightMuonCrossSectionGen"+Njets_[mult]+"/"+variables_[var])->Clone());
	histo_[variables_[var]][kGenBkg   ][Njets_[mult]] = (TH1F*)(files_[kBkg   ]->Get("analyzeTightMuonCrossSectionGen"+Njets_[mult]+"/"+variables_[var])->Clone());
	histo_[variables_[var]][kGenW     ][Njets_[mult]] = (TH1F*)(files_[kWjets ]->Get("analyzeTightMuonCrossSectionGen"+Njets_[mult]+"/"+variables_[var])->Clone());
	histo_[variables_[var]][kGenSTops ][Njets_[mult]] = (TH1F*)(files_[kSTops ]->Get("analyzeTightMuonCrossSectionGen"+Njets_[mult]+"/"+variables_[var])->Clone());
	histo_[variables_[var]][kGenSTopt ][Njets_[mult]] = (TH1F*)(files_[kSTopt ]->Get("analyzeTightMuonCrossSectionGen"+Njets_[mult]+"/"+variables_[var])->Clone());
	histo_[variables_[var]][kGenSToptW][Njets_[mult]] = (TH1F*)(files_[kSToptW]->Get("analyzeTightMuonCrossSectionGen"+Njets_[mult]+"/"+variables_[var])->Clone());
      }
    }
  }

  // --- 
  //    print out some informations
  // ---
  int totalBinNumber = (histo_["pt"][kSig]["Njets4"]->GetNbinsX())-1;
  std::cout << std::endl << "general informations:" << std::endl;
  std::cout << "chosen luminosity: " << lum << " / pb"<< std::endl;
  if(loadValues) std::cout << "all values (corrections, bkg estimations etc.) will be taken from: " << "crossSectionCalculation.txt" << std::endl;
  if(!loadValues) std::cout << "numbers NOT read in from .txt file, taken from hard coded numbers in makro" << std::endl;
  std::cout << "total bin number (pt) between 20 and 200 GeV: " << totalBinNumber << std::endl;

  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight_;
  // 7 TeV Monte Carlo fall 10 samples
  // (2*ttbar MC@NLO, 2*ttbar MG, W+jets MG, Z+jets MG, QCD PYTHIA) 
  // -----------------------------------
  for(unsigned int idx=0; idx<files_.size()-1; ++idx) {
    if(!useNLO && (idx==kSig || idx==kBkg))lumiweight_.push_back(0.000006029022/50.0*luminosity);
    if( useNLO && (idx==kSig || idx==kBkg))lumiweight_.push_back(0.000006755505/50.0*luminosity);
    if(idx==kWjets)lumiweight_.push_back(0.000105750913/50.0*luminosity);
    if(idx==kZjets)lumiweight_.push_back(ZjetsVariation*0.000059912090/50.0*luminosity);
    if(idx==kDiBos)lumiweight_.push_back(DiBosVariation*0.001/50.0*luminosity);
    if(idx==kSTops)lumiweight_.push_back(sTopVariation*0.324*0.000000464677/50.0*luminosity);
    if(idx==kSTopt)lumiweight_.push_back(sTopVariation*0.324*0.000006672727/50.0*luminosity);
    if(idx==kSToptW)lumiweight_.push_back(sTopVariation*0.000001070791/50.0*luminosity);
    // fall10:
    if(idx==kQCD  )lumiweight_.push_back(0.000143500567/50.0*(luminosity/lumiShift));
    // spring10:
    //if(idx==kQCD)lumiweight_.push_back(0.000018205*(double)luminosity);
  }
 
  // ---
  //    lumiweighting for luminosity, add all MC for combined MC (l+jets and with QCD)
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      // loop samples
      for(unsigned int idx=0; idx<files_.size()-1; ++idx) {
	// scale MC samples to same luminosity
	histo_[variables_[var]][idx][Njets_[mult]]->Scale(EffScaleFactor*scaleFactor*lumiweight_[idx]);
	if((idx==kSig || idx==kBkg) && (mult==3 || mult==4))
	  histo_[variables_[var]][idx][Njets_[mult]]->Scale(0.98323995);
      }
      // scaling for gen-plots
      if(mult<4){
	histo_[variables_[var]][kGenSig   ][Njets_[mult]]->Scale(lumiweight_[kSig]);
	histo_[variables_[var]][kGenBkg   ][Njets_[mult]]->Scale(lumiweight_[kBkg]);
	histo_[variables_[var]][kGenW     ][Njets_[mult]]->Scale(lumiweight_[kWjets]);
	histo_[variables_[var]][kGenSTops ][Njets_[mult]]->Scale(lumiweight_[kSTops]);
	histo_[variables_[var]][kGenSTopt ][Njets_[mult]]->Scale(lumiweight_[kSTopt]);
	histo_[variables_[var]][kGenSToptW][Njets_[mult]]->Scale(lumiweight_[kSToptW]);
	histo_[variables_[var]][kGenSTop  ][Njets_[mult]] = (TH1F*)(histo_[variables_[var]][kGenSTops][Njets_[mult]]->Clone());
	histo_[variables_[var]][kGenSTop  ][Njets_[mult]]->Add((TH1F*)(histo_[variables_[var]][kGenSTopt][Njets_[mult]]->Clone()));
	histo_[variables_[var]][kGenSTop  ][Njets_[mult]]->Add((TH1F*)(histo_[variables_[var]][kGenSToptW][Njets_[mult]]->Clone()));
	if(mult==3){
	  histo_[variables_[var]][kGenSig   ][Njets_[mult]]->Scale(0.985608);
	  histo_[variables_[var]][kGenBkg   ][Njets_[mult]]->Scale(0.985608);
	}
      }
      // create combined single top
      histo_[variables_[var]][kSTop][Njets_[mult]]   =   (TH1F*)histo_[variables_[var]][kSTops][Njets_[mult]]->Clone();
      histo_[variables_[var]][kSTop][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][kSTopt][Njets_[mult]]->Clone() );
      histo_[variables_[var]][kSTop][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][kSToptW][Njets_[mult]]->Clone() );
      // create isolated l+jets combined MC plots
      histo_[variables_[var]][kLepJets][Njets_[mult]] = (TH1F*)histo_[variables_[var]][kSig][Njets_[mult]]->Clone();
      histo_[variables_[var]][kLepJets][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][kBkg][Njets_[mult]]->Clone() );
      histo_[variables_[var]][kLepJets][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][kSTop][Njets_[mult]]->Clone() );
      histo_[variables_[var]][kLepJets][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][kWjets][Njets_[mult]]->Clone() );
      // create all-MC plots (including QCD and Zjets)
      histo_[variables_[var]][kAllMC][Njets_[mult]] = (TH1F*)histo_[variables_[var]][kLepJets][Njets_[mult]]->Clone();
      histo_[variables_[var]][kAllMC][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][kQCD][Njets_[mult]]->Clone() );
      histo_[variables_[var]][kAllMC][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][kZjets][Njets_[mult]]->Clone() );
      histo_[variables_[var]][kAllMC][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][kDiBos][Njets_[mult]]->Clone() );
    }
  }

  // ---  
  //    print out numbers for event yield[Njets] for all MC and data
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    std::cout << std::endl << "----------------------------------------------" << std::endl;
    std::cout << "event yield for jet multiplicity "+jetLabel(Njets_[mult]) << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      std::cout << std::endl << "-- " << variables_[var] << " --" << std::endl << std::endl;
      // loop samples
      for(unsigned int idx=0; idx<files_.size(); ++idx) {
	std::cout << samples(idx) << std::endl;
	// loop bins
	for(int bin =1; bin<=histo_[variables_[var]][idx][Njets_[mult]]->GetNbinsX(); ++bin){
	  // start with 2nd bin for pt!
	  if(variables_[var]=="pt"&&bin==1) ++bin;
	  // for phi: include underflow bin
	  if(variables_[var]=="phi"&& bin==1) std::cout << "underflow bin: " << setprecision(2) << fixed << histo_[variables_[var]][idx][Njets_[mult]]->GetBinContent(0);
	  // get bin content
	  std::cout << "  bin " << bin << " : " << setprecision(2) << fixed << histo_[variables_[var]][idx][Njets_[mult]]->GetBinContent(bin);
	  // for pt and phi: include overflow bins
	  if((variables_[var]=="pt"||variables_[var]=="phi")&&bin==histo_[variables_[var]][idx][Njets_[mult]]->GetNbinsX()){
	    std::cout << "  overflow bin: " << setprecision(2) << fixed << histo_[variables_[var]][idx][Njets_[mult]]->GetBinContent(bin+1);
	  }
	}
	// print out total event number (including underflow and overflow)
	std::cout << std::endl << "total: " << setprecision(2) << fixed << histo_[variables_[var]][idx][Njets_[mult]]->Integral(0, histo_[variables_[var]][idx][Njets_[mult]]->GetNbinsX()+1 ) << std::endl;
      }
      // print out total number of MC entries for data MC comparison 
      std::cout << "( all MC: " << setprecision(2) << fixed << histo_[variables_[var]][kAllMC][Njets_[mult]]->Integral(0, histo_[variables_[var]][kAllMC][Njets_[mult]]->GetNbinsX()+1 ) << " )" << std::endl;
    }
    // print out S / B ratios
    double Ntop = histo_["pt"][kSig][Njets_[mult]]->Integral(0, histo_["pt"][kSig][Njets_[mult]]->GetNbinsX()+1);
    Ntop+= histo_["pt"][kBkg][Njets_[mult]]->Integral(0, histo_["pt"][kBkg][Njets_[mult]]->GetNbinsX()+1);
    double NLjets = histo_["pt"][kLepJets][Njets_[mult]]->Integral(0, histo_["pt"][kLepJets][Njets_[mult]]->GetNbinsX()+1);
    double NAll = histo_["pt"][kAllMC][Njets_[mult]]->Integral(0, histo_["pt"][kAllMC][Njets_[mult]]->GetNbinsX()+1);
    std::cout << "S/B for top             : " << Ntop   / (NAll-Ntop  ) << std::endl;
    std::cout << "S/B for l+jets (top+W+Z): " << NLjets / (NAll-NLjets) << std::endl;
  }

  // ---  
  //    get QCD bkg from data driven (ABCD) method
  // ---
  // print out
  std::vector<double> NQCD_;
  std::cout << std::endl << "QCD estimation from ABCD method" << std::endl;
  if(loadValues) std::cout << "(read in from .txt file)" << std::endl;
  else std::cout << "(taken from hard coded numbers)" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  // loop jet multiplicities (no btag)
  for(unsigned int mult=0; mult<4; ++mult){
    //if(finalPlots)std::cout<<std::endl<<"QCDscaletest: "<<templateFit((TH1F*)files_[kData]->Get("analyzePfMET"+Njets_[mult]+"/metEt"), (TH1F*)files_[kData]->Get("analyzePfMET"+Njets_[mult]+"AntiRel/metEt"), (TH1F*)files_[kQCD]->Get("analyzePfMET"+Njets_[mult]+"/metEt"), (TH1F*)files_[kWjets]->Get("analyzePfMET"+Njets_[mult]+"/metEt"), (TH1F*)files_[kZjets]->Get("analyzePfMET"+Njets_[mult]+"/metEt"), (TH1F*)files_[kSig]->Get("analyzePfMET"+Njets_[mult]+"/metEt"), (TH1F*)files_[kBkg]->Get("analyzePfMET"+Njets_[mult]+"/metEt"), (TH1F*)files_[kSTops]->Get("analyzePfMET"+Njets_[mult]+"/metEt"), (TH1F*)files_[kSTopt]->Get("analyzePfMET"+Njets_[mult]+"/metEt"), (TH1F*)files_[kSToptW]->Get("analyzePfMET"+Njets_[mult]+"/metEt"), Njets_[mult])<<std::endl;
    // a) get number
    // divide by scaleFactor here as QCD scale factors are with respect to the unscaled QCD MC
    if(Njets_[mult]=="Njets1") 
      NQCD_.push_back(QCDVariation*1.6*histo_[variables_[0]][kQCD][Njets_[mult]]->Integral(0, histo_[variables_[0]][kQCD][Njets_[mult]]->GetNbinsX()+1)/(EffScaleFactor*scaleFactor));
    if(Njets_[mult]=="Njets2") 
      NQCD_.push_back(QCDVariation*2.0*histo_[variables_[0]][kQCD][Njets_[mult]]->Integral(0, histo_[variables_[0]][kQCD][Njets_[mult]]->GetNbinsX()+1)/(EffScaleFactor*scaleFactor));
    if(Njets_[mult]=="Njets3") 
      NQCD_.push_back(QCDVariation*2.2*histo_[variables_[0]][kQCD][Njets_[mult]]->Integral(0, histo_[variables_[0]][kQCD][Njets_[mult]]->GetNbinsX()+1)/(EffScaleFactor*scaleFactor));
    if(Njets_[mult]=="Njets4") 
      NQCD_.push_back(QCDVariation*1.8*histo_[variables_[0]][kQCD][Njets_[mult]]->Integral(0, histo_[variables_[0]][kQCD][Njets_[mult]]->GetNbinsX()+1)/(EffScaleFactor*scaleFactor));
    // b) get shape from QCD MC
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      // get QCD MC
      histo_[variables_[var]][kABCD][Njets_[mult]]= (TH1F*)histo_[variables_[var]][kQCD][Njets_[mult]]->Clone();
      // get MC entries
      double NMCQCD = histo_[variables_[var]][kQCD][Njets_[mult]]->Integral(0, histo_[variables_[var]][kQCD][Njets_[mult]]->GetNbinsX()+1);
      // take care for division by 0
      if(NMCQCD==0) NMCQCD=1;
      // normalize to N(QCD) from ABCD method
      histo_[variables_[var]][kABCD][Njets_[mult]]->Scale(NQCD_[mult]/NMCQCD);
      // print out numbers
      std::cout << std::endl << "shape from QCD MC (" << variables_[var] << "):";
      // loop bins
      for(int bin =1; bin<=histo_[variables_[var]][kSig][Njets_[mult]]->GetNbinsX(); ++bin){
	// start with 2nd bin for pt!
	if(variables_[var]=="pt"&&bin==1) ++bin;
	// for phi: include underflow bin
	if(variables_[var]=="phi"&& bin==1) std::cout << "underflow bin: " << histo_["phi"][kABCD][Njets_[mult]]->GetBinContent(0);
	std::cout << "  bin " << bin << ": " << histo_[variables_[var]][kABCD][Njets_[mult]]->GetBinContent(bin);
	// for pt and phi: include overflow bins
	if((variables_[var]=="pt"||variables_[var]=="phi")&&bin==histo_[variables_[var]][kABCD][Njets_[mult]]->GetNbinsX()){
	  std::cout << "  overflow bin: " << histo_[variables_[var]][kABCD][Njets_[mult]]->GetBinContent(bin+1);
	}
      }
    }
  }

  // ---  
  //    get yield histos by dividing per binwidth and create stack plot
  // ---
  // create yield variable indicator to destinguish between hists divided by binwidth
  std::vector<TString> yield_;
  TString yield[ 3 ] = { "pt yield", "eta yield", "phi yield" };
  yield_.insert( yield_.begin(), yield, yield + 3 );
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      // loop all samples
      for(unsigned int idx=0; idx<=kSTop; ++idx) {
	// divide this histo by binwidth
	histo_[yield_[var]][idx][Njets_[mult]] = divideByBinwidth((TH1F*)histo_[variables_[var]][idx][Njets_[mult]]->Clone(), true);
	// rescale QCD by data driven estimation
	if(idx==kQCD){
	  double NQCDEstimate = NQCD_[mult];
	  double NQCDMC = histo_[variables_[var]][kQCD][Njets_[mult]]->Integral(0, histo_[variables_[var]][kQCD][Njets_[mult]]->GetNbinsX()+1);
	  histo_[yield_[var]][kQCD][Njets_[mult]]->Scale(NQCDEstimate/NQCDMC);
	  std::cout << std::endl << "ratio QCD ( estimation / MC prediction )" << std::endl;
	  std::cout << jetLabel(Njets_[mult]) << " : " << NQCDEstimate/NQCDMC << std::endl;	
	}
	// for MC: add all former histos to get stack plot
	if(idx!=0&&idx<kData)histo_[yield_[var]][idx][Njets_[mult]]->Add( (TH1F*)histo_[yield_[var]][idx-1][Njets_[mult]]->Clone() );
      }
    }
  }
  
  // ---  
  //    get MC event composition histos
  // ---
  // create composition variable indicator
  std::vector<TString> composition_;
  TString composition[ 3 ] = { "pt composition", "eta composition", "phi composition" };
  composition_.insert( composition_.begin(), composition, composition + 3 );
  // print out
  std::cout << std::endl << "relative event composition(%):" << std::endl;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    std::cout << std::endl << jetLabel(Njets_[mult]) << " " << std::endl;
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      std::cout << "-----" << variables_[var] << "-----" << std::endl;
      int sTopCount = 0;
      // loop all samples
      for(unsigned int idx=0; idx<files_.size()-1; ++idx){
	// a) clone lumiweigthed MC plots
	if(idx==kSTops || idx==kSTopt || idx==kSToptW){
	  if(sTopCount==0)histo_[composition_[var]][idx+2][Njets_[mult]] = (TH1F*)histo_[variables_[var]][idx][Njets_[mult]]->Clone();
	  else{
	    histo_[composition_[var]][idx+2-sTopCount][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][idx][Njets_[mult]]->Clone() );
	    histo_[composition_[var]][idx-1][Njets_[mult]] = 0;
	  }
	  sTopCount++;
	}
	else histo_[composition_[var]][idx][Njets_[mult]] = (TH1F*)histo_[variables_[var]][idx][Njets_[mult]]->Clone();
      }
      for(unsigned int idx=0; idx<files_.size()-1; ++idx){
	if(histo_[composition_[var]][idx][Njets_[mult]]){
	std::cout << sampleLabel(idx) << std::endl;
	  // b) calculate event composition for each bin
	  // loop bins (no overflow or underflow)
	  for(int bin =1; bin<=histo_[variables_[var]][kSig][Njets_[mult]]->GetNbinsX(); ++bin){
	    // start with 2nd bin for pt!
	    if(variables_[var]=="pt"&&bin==1) ++bin;
	    // get entries for actual sample
	    double Nsample = histo_[composition_[var]][idx][Njets_[mult]]->GetBinContent(bin);
	    // get entries from all sample-> loop sample again
	    double NAll    = 0;
	    for(unsigned int sample=0; sample<kData; ++sample){
	      NAll+=((TH1F*)histo_[variables_[var]][sample][Njets_[mult]]->Clone())->GetBinContent(bin);
	    }
	    // calculate relative event composition for this bin and this sample, fill to histo and print out
	    histo_[composition_[var]][idx][Njets_[mult]]->SetBinContent(bin, Nsample/NAll);
	    std::cout << "  bin " << bin << ": " << setprecision(1) << fixed << 100*histo_[composition_[var]][idx][Njets_[mult]]->GetBinContent(bin) << "";
	    if(bin==histo_[variables_[var]][kSig][Njets_[mult]]->GetNbinsX()) std::cout << std::endl;
	  }
	}
      }
    }
  }

  // ---
  //    get efficiencies from MC gen studies
  // ---
  // a) eff. for l+jets bin per bin correction -> differential cross section
  // create container for effiencies
  std::map< TString, std::map <unsigned int, std::map <TString, double> > > efficiency_;
  // example: efficiency_["pt"][(bin)1]["Njets1"]
  // , useNLO, JES
  // --------------------------------------- 
  // print out
  std::cout << std::endl << std::endl << "gen based MC efficiencies: " << std::endl;
  std::cout << std::endl << "a) differential l+jets" << std::endl;
  if(loadValues ) std::cout << "(read in from .txt file)" << std::endl;
  if(!loadValues) std::cout << "(no efficiency corrections applied)" << std::endl; 
  // loop jet multiplicities (also btag)
  for(int mult=0; mult<6; ++mult){
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      // loop bins
      for(int bin =1; bin<=histo_[variables_[var]][kSig][Njets_[mult]]->GetNbinsX(); ++bin){
	if(bin==1) std::cout << std::endl << "------------------------------------" << std::endl;
	// start with 2nd bin for pt!
	if(variables_[var]=="pt"&&bin==1) ++bin;
	// get underflow bin for phi
	if(variables_[var]=="phi"&&bin==1) efficiency_[variables_[var]][0][Njets_[mult]] = getMCEffiencies(variables_[var], 0, mult, loadValues, useNLO, JES, jetTyp, scaleFactor, putSysOn)*EffScaleFactor;
	efficiency_[variables_[var]][bin][Njets_[mult]] = getMCEffiencies(variables_[var], bin, mult, loadValues, useNLO, JES, jetTyp, scaleFactor, putSysOn)*EffScaleFactor;
	// get overflow bin for pt and phi
	if((variables_[var]=="pt"||variables_[var]=="phi")&&bin==histo_[variables_[var]][kSig][Njets_[mult]]->GetNbinsX()){
	  efficiency_[variables_[var]][bin+1][Njets_[mult]] = getMCEffiencies(variables_[var], bin+1, mult, loadValues, useNLO, JES, jetTyp, scaleFactor, putSysOn)*EffScaleFactor;
	}
      }
    }
  }
  // b) eff. for l+jets inclusive cross section (all jet multiplicities, no btag)
  std::cout << std::endl<< std::endl << "b) inclusive l+jets";
  // create container
  std::vector<double> ljetsInclusiveEff_;
  // loop jet multiplicities (no btag)
  for(int mult=0; mult<4; ++mult){
    ljetsInclusiveEff_. push_back( getInclusiveMCEff("lep", mult+1, loadValues, useNLO, JES, jetTyp, scaleFactor, putSysOn)*EffScaleFactor );
  }
  // c) eff. for top inclusive cross section 
  // N(jets)>=4 corresponds to 4
  // N(jets)>=4 && N(BTags)>=1 corresponds to 5
  std::cout<< std::endl << std::endl << "c1) inclusive top with b-tag";
  double effNjets4Btag = getInclusiveMCEff("top", 5, loadValues, useNLO, JES, jetTyp, scaleFactor, putSysOn)*EffScaleFactor;
  std::cout<< std::endl << std::endl << "c2) inclusive top without b-tag";
  double effNjets4     = getInclusiveMCEff("top", 4, loadValues, useNLO, JES, jetTyp, scaleFactor, putSysOn)*EffScaleFactor;

  // d) eff. for differenial top cross sections >=4 jets and btag
  int systematic=0;
  if((useNLO)||(JES!="")) systematic=11;

  // (i) pt
  std::vector<double> topPtEff_, topPtEff2_;
  std::cout << std::endl<< std::endl << "d) differential top (>=4 jets- with / without btag)";
  std::cout << std::endl << "(i) pt";
  for(int bin=2; bin<=7; ++bin){
    double eff =readLineFromFile(154-systematic+bin, file)*EffScaleFactor;
    double eff2=readLineFromFile(166-systematic+bin, file)*EffScaleFactor;
    topPtEff_ .push_back(eff );
    topPtEff2_.push_back(eff2);
    std::cout << std::endl << "bin " << bin << ": " << eff << " / " << eff2;
  }
  // (ii) eta
  std::vector<double> topEtaEff_, topEtaEff2_;
  std::cout << std::endl << "(ii) eta";
  for(int bin=1; bin<=4; ++bin){
    double eff = readLineFromFile(162-systematic+bin, file)*EffScaleFactor;
    double eff2= readLineFromFile(174-systematic+bin, file)*EffScaleFactor;
    topEtaEff_ .push_back(eff );
    topEtaEff2_.push_back(eff2);
    std::cout << std::endl << "bin " << bin << ": " << eff << " / " << eff2;
  }
  
  // ---
  //    get W-estimation from charge asymmetry method
  // ---
  double NWestimate = readLineFromFile(185,file2)*WjetsVariation;
  std::cout<< std::endl << std::endl << "W-estimation for N(jets)>=4 from charge asymmetry method: ";
  std::cout<< std::endl << NWestimate;

  // ---  
  //    create l+jets diff. (norm.) xSec (from data and l+jets MC)
  //    substract estimated QCD from data, apply efficiency corrections,
  // ---
  // output
  std::cout << std::endl << std::endl << "-------------------" << std::endl;
  std::cout << "--- L+jets xSec ---" << std::endl;
  std::cout << "-------------------";
  // create l+jets variable indicators to destinguish between other plots
  std::vector<TString> ljetsXSec_, ljetsXSecDiff_;
  TString ljetsXSec[ 3 ] = { "pt l+jets diff norm XSec", "eta l+jets diff norm XSec", "phi l+jets diff norm XSec" };
  ljetsXSec_.insert( ljetsXSec_.begin(), ljetsXSec, ljetsXSec + 3 );
  TString ljetsXSecDiff[ 3 ] = { "pt l+jets diff XSec", "eta l+jets diff XSec", "phi l+jets diff XSec" };
  ljetsXSecDiff_.insert( ljetsXSecDiff_.begin(), ljetsXSecDiff, ljetsXSecDiff + 3 );
  // loop samples - do l+jets diff. norm. xSec only for data and combined l+jets MC(W,Z,top)
  for(unsigned int idx=kData; idx<=kLepJets; ++idx){    
    if(idx==kData   ) std::cout << std::endl << std::endl << "a) from data" << std::endl;
    if(idx==kLepJets) std::cout << std::endl << std::endl << "b) from l+jets MC (W+jets, top, Z+jets)" << std::endl;
    // loop jet multiplicities
    for(unsigned int mult=0; mult<Njets_.size(); ++mult){
      std::cout << "-------------------"<< std::endl << "--"+jetLabel(Njets_[mult])+ "--" << std::endl << "-------------------" << std::endl;
      // loop pt, eta and phi
      for(unsigned int var=0; var<variables_.size(); ++var){
	std::cout<< std::endl << variables_[var] << std::endl;
 	// a) clone plot from the (lumiscaled) ones
	histo_[ljetsXSec_[var]][idx][Njets_[mult]] = (TH1F*)histo_[variables_[var]][idx][Njets_[mult]]->Clone();
	// b1) substract QCD for data (not done for btag-selections)
	if((idx==kData)&&(mult<4)) histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Add( histo_[variables_[var]][kABCD][Njets_[mult]], -1.0);
	// b2) subtract Z+jets from Data
	if(idx==kData)histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Add( histo_[variables_[var]][kZjets][Njets_[mult]], -1.0);
	// b3) subtract DiBoson from Data
	if(idx==kData)histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Add( histo_[variables_[var]][kDiBos][Njets_[mult]], -1.0);
	double NAll = histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Integral(0, histo_[ljetsXSec_[var]][idx][Njets_[mult]]->GetNbinsX()+1);
	// c) apply efficiency corrections for each bin
	// loop bins (including underflow and overflow)
	for(int bin =0; bin<=histo_[variables_[var]][kData][Njets_[mult]]->GetNbinsX()+1; ++bin){
	  // if efficiency is not 0 correct by division (reco=gen*eff)
	  if(efficiency_[variables_[var]][bin][Njets_[mult]]!=0){
	    histo_[ljetsXSec_[var]][idx][Njets_[mult]]->SetBinContent(bin, histo_[ljetsXSec_[var]][idx][Njets_[mult]]->GetBinContent(bin) / efficiency_[variables_[var]][bin][Njets_[mult]]);
	    // take care of error: N'=(N-NBG)/e -> sN'= sN/e
	    histo_[ljetsXSec_[var]][idx][Njets_[mult]]->SetBinError(bin, sqrt( histo_[variables_[var]][idx][Njets_[mult]]->GetBinContent(bin) ) / efficiency_[variables_[var]][bin][Njets_[mult]]);
	  }
	}
	// d) l+jets differential cross section (without normalization)
	// i) clone (also for inclusive l+jets xSec)
	histo_[ljetsXSecDiff_     [var]][idx][Njets_[mult]]= (TH1F*)histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Clone();
	// ii) divide by binwidth (and recalculate errors)
	histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]=divideByBinwidth(histo_[ljetsXSecDiff[var]][idx][Njets_[mult]], true);
	// iii) divide by luminosity
	scaleByLumi(histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], luminosity*0.001);
	// f) normalize to total cross section
	double totalEff = 0.;
	if(mult<4)totalEff = ljetsInclusiveEff_[mult];
	else
	  {
	    double totalGen = 0.;
	    for(int iBin=0; iBin<=histo_[variables_[var]][idx][Njets_[mult]]->GetNbinsX()+1; ++iBin){
	      if(efficiency_[variables_[var]][iBin][Njets_[mult]]!=0)totalGen+=histo_[variables_[var]][idx][Njets_[mult]]->GetBinContent(iBin)/efficiency_[variables_[var]][iBin][Njets_[mult]];
	    }
	    totalEff = NAll/totalGen;
	  }
	histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Scale(totalEff/NAll);
	// g) divide by binwidth
	histo_[ljetsXSec_[var]][idx][Njets_[mult]] = divideByBinwidth(histo_[ljetsXSec_[var]][idx][Njets_[mult]], false);
	// h) calculate error for each bin ( correlated error calculation as described in AN-10-090
	// choose bin max/min: start with underflow for phi, 2nd bin for pt, include overflow for phi/pt
	if(idx==kData){
	  int binMax=histo_[variables_[var]][idx][Njets_[mult]]->GetNbinsX();
	  int binMin=1;
	  if(variables_[var]=="pt" ) binMin=2;
	  if(variables_[var]=="phi") binMin=0;
	  if(variables_[var]!="eta") binMax+=1;
	  // loop bins
	  for(int bin =binMin; bin<=binMax; ++bin){
	    // get efficiencies
	    double eBin = efficiency_[variables_[var]][bin][Njets_[mult]];
	    // get binwidth
	    double binwidth=histo_[variables_[var]][idx][Njets_[mult]]->GetBinWidth(bin);
	    // get data entries
	    double NdataBin=histo_[variables_[var]][idx][Njets_[mult]]->GetBinContent(bin);
	    // get QCD estimation from ABCD method only for selection without btag
	    double NQCDBin=0.;
	    if(mult<4)NQCDBin = histo_[variables_[var]][kABCD][Njets_[mult]]->GetBinContent(bin);
	    // calculate Ni   = (NdataBin-NQCDbin)/ebin corrected entries in bin
	    double Ni= NdataBin-NQCDBin;
	    // calculate Nges = sum_i(Ni) corrected total number of entries
	    double Nges =NAll;
	    // compare #events(total) in histo when applying efficiency corrections for each bin or global efficiency correction 
	    //	  std::cout << "( " << NAll << " , " <<  histo_[variables_[var]][idx][Njets_[mult]]->Integral(0, histo_[variables_[var]][idx][Njets_[mult]]->GetNbinsX()+1)/ljetsInclusiveEff_[mult] << " )" << std::endl;
	    // calculate two expressions needed in complete error
	    double term1 = (Nges - Ni)*sqrt(NdataBin);
	    double term2 = 0;
	    for(int bin2=binMin; bin2<=binMax; ++bin2){
	      if(bin2!=bin){
		if(mult<4)term2 += histo_[variables_[var]][idx][Njets_[mult]]->GetBinContent(bin2)-histo_[variables_[var]][kABCD][Njets_[mult]]->GetBinContent(bin2);
		else term2 += histo_[variables_[var]][idx][Njets_[mult]]->GetBinContent(bin2);
	      }
	    }
	    // calculate complete error
	    double diffNormError = totalEff / ( Nges*Nges*eBin*binwidth );
	    diffNormError *= sqrt( term1*term1 + Ni*Ni*term2 );
	    // apply calculated error to plot
	    histo_[ljetsXSec_[var]][idx][Njets_[mult]]->SetBinError(bin, diffNormError);
	  }
	}
	// i) print out values for l+jet diff. norm xSec (all bins)
	// loop bins (excluding underflow and overflow-> can not divide by binwidth)
	std::cout << "1) diff norm. cross section l+jets ( "<< jetLabel(Njets_[mult]) << " ):" << std::endl;
	for(int bin =1; bin<=histo_[variables_[var]][kData][Njets_[mult]]->GetNbinsX(); ++bin){
	  std::cout << "  bin " << bin << ": ";
	  std::cout << setprecision(3) << fixed << histo_[ljetsXSec_[var]][idx][Njets_[mult]]->GetBinContent(bin) << " +/-";
	  std::cout << setprecision(3) << fixed << histo_[ljetsXSec_[var]][idx][Njets_[mult]]->GetBinError(bin)   << std::endl;
	  // save l+jet diff. norm xSec results for systematic variations and determination of systematic errors 
	  if(idx==kData){
	    bool append =true;
	    if(bin==1){
	      if(variables_[var]=="pt") ++bin;
	      if(mult==0) append=false;
	      writeToFile(ljetsXSec_[var]+Njets_[mult], "systematicVariations/diffNormXSec"+variables_[var]+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", append);
	    }
	    writeToFile(histo_[ljetsXSec_[var]][idx][Njets_[mult]]->GetBinContent(bin), "systematicVariations/diffNormXSec"+variables_[var]+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 1);
	  }
	}
	// j) print out values for l+jet diff. xSec (all bins)
	std::cout << "2) differential cross section l+jets ( "<< jetLabel(Njets_[mult]) << " ):" << std::endl;
	// loop bins (excluding underflow and overflow-> can not divide by binwidth)
	for(int bin =1; bin<=histo_[variables_[var]][kData][Njets_[mult]]->GetNbinsX(); ++bin){
	  // skip bin 1 for pt
	  if((variables_[var]=="pt")&&(bin==1)) ++bin;
	  std::cout << "  bin " << bin << ": ";
	  std::cout << setprecision(3) << fixed << histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->GetBinContent(bin) << " +/-";
	  std::cout << setprecision(3) << fixed << histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->GetBinError(bin)   << std::endl;
	  // save l+jet diff. xSec results for systematic variations and determination of systematic errors
	  if(idx==kData){
	    bool append =true;
	    if(bin==1||((variables_[var]=="pt")&&(bin==2))){
	      if(mult==0) append=false;
	      writeToFile(ljetsXSecDiff_[var]+Njets_[mult], "systematicVariations/differentialXSec"+variables_[var]+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", append);
	    }
	    writeToFile(histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->GetBinContent(bin), "systematicVariations/differentialXSec"+variables_[var]+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 1);
	  }
	}
      }
    }
  }

  // ---
  //    get gen W and ttbar diff norm XSec
  // ---
  std::vector<TString> ljetsXSecGen_;
  TString ljetsXSecGen[ 3 ] = { "pt l+jets diff norm XSecgen", "eta l+jets diff norm XSecgen", "phi l+jets diff norm XSecgen" };
  ljetsXSecGen_.insert( ljetsXSecGen_.begin(), ljetsXSecGen, ljetsXSecGen + 3 );
  // a) clone plots from the (lumiscaled) ones
  // loop kSig, kBkg. KW
  for(unsigned int idx=kGenSig; idx<=kGenSTop; ++idx){
    // loop jet multiplicities (no btag)
    for(unsigned int mult=0; mult<4; ++mult){
      // loop pt, eta, phi
      for(unsigned int var=0; var<variables_.size(); ++var){
	// a) clone plots from the (lumiscaled) ones
	histo_[ljetsXSecGen_[var]][idx][Njets_[mult]] = (TH1F*)histo_[variables_[var]][idx][Njets_[mult]]->Clone();
      }
    }
  }

  // b) calculate contributions for diff.norm.XSec.
  std::cout << "test diff norm XSec" << std::endl;
  // loop kSig, kBkg. KW
  for(unsigned int idx=kGenSig; idx<=kGenSTop; ++idx){
    // loop jet multiplicities (no btag)
    for(unsigned int mult=0; mult<4; ++mult){
      // loop pt, eta, phi
      for(unsigned int var=0; var<variables_.size(); ++var){
	// i) get entries
	double NttbarSig = histo_[variables_[var]][kGenSig ][Njets_[mult]]->Integral(0, histo_[variables_[var]][kGenSig ][Njets_[mult]]->GetNbinsX());
	double NttbarBkg = histo_[variables_[var]][kGenBkg ][Njets_[mult]]->Integral(0, histo_[variables_[var]][kGenBkg ][Njets_[mult]]->GetNbinsX());
	double NW        = histo_[variables_[var]][kGenW   ][Njets_[mult]]->Integral(0, histo_[variables_[var]][kGenW   ][Njets_[mult]]->GetNbinsX());
	double NsingleTop= histo_[variables_[var]][kGenSTop][Njets_[mult]]->Integral(0, histo_[variables_[var]][kGenSTop][Njets_[mult]]->GetNbinsX());
	// ii) loop bins and calculate entries
	int binMax=histo_[variables_[var]][idx][Njets_[mult]]->GetNbinsX();
	int binMin=1;
	if(variables_[var]=="pt" ) binMin=2;
	if(variables_[var]=="phi") binMin=0;
	if(variables_[var]!="eta") binMax+=1;
	// loop bins
	for(int bin =binMin; bin<=binMax; ++bin){
	  // get entries in the bin
	  double Ni      = histo_[ljetsXSecGen_[var]][idx][Njets_[mult]]->GetBinContent(bin);
	  // get binwidth
	  double binwidth=histo_[variables_[var]][idx][Njets_[mult]]->GetBinWidth(bin);
	  // calculate dsigma_idx/(dx*sigma_tot) 
	  double value = Ni / (binwidth*(NttbarSig+NttbarBkg+NW+NsingleTop));
	  histo_[ljetsXSecGen_[var]][idx][Njets_[mult]]->SetBinContent(bin, value);
	}
      }
    }
  }


  // k) create gen MC differential W and top XSec
  // create indicator
  std::vector<TString> ljetsGen_;
  TString ljetsGen[ 3 ] = { "pt l+jets gen", "eta l+jets gen", "phi l+jets gen" };
  ljetsGen_.insert( ljetsGen_.begin(), ljetsGen, ljetsGen + 3 );
  // loop jet multiplicities
  for(unsigned int mult=0; mult<4; ++mult){
    // loop pt, eta and phi
    for(unsigned int var=0; var<ljetsGen_.size(); ++var){
      // divide by binwidth
      histo_[ljetsGen_[var]][kGenSig ][Njets_[mult]] = divideByBinwidth((TH1F*)histo_[variables_[var]][kGenSig ][Njets_[mult]]->Clone(), true);
      histo_[ljetsGen_[var]][kGenBkg ][Njets_[mult]] = divideByBinwidth((TH1F*)histo_[variables_[var]][kGenBkg ][Njets_[mult]]->Clone(), true);
      histo_[ljetsGen_[var]][kGenSTop][Njets_[mult]] = divideByBinwidth((TH1F*)histo_[variables_[var]][kGenSTop][Njets_[mult]]->Clone(), true);
      histo_[ljetsGen_[var]][kGenW   ][Njets_[mult]] = divideByBinwidth((TH1F*)histo_[variables_[var]][kGenW   ][Njets_[mult]]->Clone(), true);
      // divide by luminosity
      scaleByLumi(histo_[ljetsGen_[var]][kGenSig ][Njets_[mult]], luminosity*0.001);
      scaleByLumi(histo_[ljetsGen_[var]][kGenBkg ][Njets_[mult]], luminosity*0.001);
      scaleByLumi(histo_[ljetsGen_[var]][kGenW   ][Njets_[mult]], luminosity*0.001);
      scaleByLumi(histo_[ljetsGen_[var]][kGenSTop][Njets_[mult]], luminosity*0.001);
      // create stack-plot: ttbar signal, ttbar other, W+jets
      histo_[ljetsGen_[var]][kGenBkg ][Njets_[mult]]->Add( histo_[ljetsGen_[var]][kGenSig ][Njets_[mult]] );
      histo_[ljetsGen_[var]][kGenSTop][Njets_[mult]]->Add( histo_[ljetsGen_[var]][kGenBkg ][Njets_[mult]] );
      histo_[ljetsGen_[var]][kGenW   ][Njets_[mult]]->Add( histo_[ljetsGen_[var]][kGenSTop][Njets_[mult]] );
    }
  }

  // ---
  //    W+jets scale factor estimation from 2jet bin
  // ---
  double WData2Jetsincl = histo_["pt"][kData ][Njets_[1]]->Integral( 0 , histo_["pt"][kData][Njets_[1]]->GetNbinsX()+1 ) - 
    NQCD_[1] - 
    histo_["pt"][kDiBos][Njets_[1]]->Integral( 0 , histo_["pt"][kDiBos][Njets_[1]]->GetNbinsX()+1 ) - 
    histo_["pt"][kSTop ][Njets_[1]]->Integral( 0 , histo_["pt"][kSTop ][Njets_[1]]->GetNbinsX()+1 ) -
    WjetsVariation*histo_["pt"][kSig  ][Njets_[1]]->Integral( 0 , histo_["pt"][kSig  ][Njets_[1]]->GetNbinsX()+1 ) -
    WjetsVariation*histo_["pt"][kBkg  ][Njets_[1]]->Integral( 0 , histo_["pt"][kBkg  ][Njets_[1]]->GetNbinsX()+1 );
  double VjetsSFincl=WData2Jetsincl/(histo_["pt"][kWjets][Njets_[1]]->Integral( 0 , histo_["pt"][kWjets][Njets_[1]]->GetNbinsX()+1 ) + 
				     histo_["pt"][kZjets][Njets_[1]]->Integral( 0 , histo_["pt"][kZjets][Njets_[1]]->GetNbinsX()+1 ));

  double WData2Jets = (histo_["pt"][kData ][Njets_[1]]->Integral( 0 , histo_["pt"][kData][Njets_[1]]->GetNbinsX()+1 )- 
		       histo_["pt"][kData ][Njets_[2]]->Integral( 0 , histo_["pt"][kData][Njets_[2]]->GetNbinsX()+1 )) - 
                      (NQCD_[1] - NQCD_[2]) -
                      (histo_["pt"][kDiBos][Njets_[1]]->Integral( 0 , histo_["pt"][kDiBos][Njets_[1]]->GetNbinsX()+1 )- 
		       histo_["pt"][kDiBos][Njets_[2]]->Integral( 0 , histo_["pt"][kDiBos][Njets_[2]]->GetNbinsX()+1 )) - 
                      (histo_["pt"][kSTop ][Njets_[1]]->Integral( 0 , histo_["pt"][kSTop ][Njets_[1]]->GetNbinsX()+1 )-
		       histo_["pt"][kSTop ][Njets_[2]]->Integral( 0 , histo_["pt"][kSTop ][Njets_[2]]->GetNbinsX()+1 )) -
                      (WjetsVariation*histo_["pt"][kSig  ][Njets_[1]]->Integral( 0 , histo_["pt"][kSig  ][Njets_[1]]->GetNbinsX()+1 )-
		       WjetsVariation*histo_["pt"][kSig  ][Njets_[2]]->Integral( 0 , histo_["pt"][kSig  ][Njets_[2]]->GetNbinsX()+1 )) -
                      (WjetsVariation*histo_["pt"][kBkg  ][Njets_[1]]->Integral( 0 , histo_["pt"][kBkg  ][Njets_[1]]->GetNbinsX()+1 )-
		       WjetsVariation*histo_["pt"][kBkg  ][Njets_[2]]->Integral( 0 , histo_["pt"][kBkg  ][Njets_[2]]->GetNbinsX()+1 ));
  double VjetsSF=WData2Jets/((histo_["pt"][kWjets][Njets_[1]]->Integral( 0 , histo_["pt"][kWjets][Njets_[1]]->GetNbinsX()+1 )-
			      histo_["pt"][kWjets][Njets_[2]]->Integral( 0 , histo_["pt"][kWjets][Njets_[2]]->GetNbinsX()+1 )) + 
			     (histo_["pt"][kZjets][Njets_[1]]->Integral( 0 , histo_["pt"][kZjets][Njets_[1]]->GetNbinsX()+1 )-
			      histo_["pt"][kZjets][Njets_[2]]->Integral( 0 , histo_["pt"][kZjets][Njets_[2]]->GetNbinsX()+1 )));

  std::cout << std::endl <<  "Vjets scale factor inclusive: " << VjetsSFincl << std::endl;
  std::cout << std::endl <<  "Vjets scale factor exclusive: " << VjetsSF << std::endl;
  // ---
  //    differential top cross sections (pt & eta) for >=4 jets / + >=1 btag
  // ---
  std::cout << std::endl << "differential top cross section" << std::endl;
  // in two ways: with(4) and without btag(3)
  for(unsigned int mult=4; mult>=3; --mult){
    
    // a) data
    // (i) clone plots from data yields
    histo_["pt top"  ][kData][Njets_[mult]]=(TH1F*)histo_["pt" ][kData][Njets_[mult]]->Clone();
    histo_["eta top" ][kData][Njets_[mult]]=(TH1F*)histo_["eta"][kData][Njets_[mult]]->Clone();
    // (ii) subtract BG from MC prediction
    histo_["pt BG"   ][kData][Njets_[mult]] =    (TH1F*)histo_["pt"][kWjets][Njets_[mult]]->Clone();
    histo_["pt BG"   ][kData][Njets_[mult]]->Add((TH1F*)histo_["pt"][kZjets][Njets_[mult]]->Clone());
    histo_["pt BG"   ][kData][Njets_[mult]]->Scale(VjetsSF);
    histo_["pt BG"   ][kData][Njets_[mult]]->Add((TH1F*)histo_["pt"][kDiBos][Njets_[mult]]->Clone());
    histo_["pt BG"   ][kData][Njets_[mult]]->Add((TH1F*)histo_["pt"][kSTop ][Njets_[mult]]->Clone());
    if(mult==3) histo_["ptBGQCD" ][kData][Njets_[mult]] = (TH1F*)histo_["pt"][kABCD][Njets_[mult]]->Clone();
    if(mult==4){
      histo_["ptBGQCD" ][kData][Njets_[mult]] = (TH1F*)histo_["pt"][kQCD ][Njets_[mult]]->Clone();
      histo_["ptBGQCD" ][kData][Njets_[mult]]->Scale(QCDVariation);
    }
    histo_["pt BG"   ][kData][Njets_[mult]]->Add(histo_["ptBGQCD"][kData][Njets_[mult]]);
    histo_["eta BG"  ][kData][Njets_[mult]] =    (TH1F*)histo_["eta"][kWjets][Njets_[mult]]->Clone();
    histo_["eta BG"  ][kData][Njets_[mult]]->Add((TH1F*)histo_["eta"][kZjets][Njets_[mult]]->Clone());
    histo_["eta BG"  ][kData][Njets_[mult]]->Scale(VjetsSF);
    histo_["eta BG"  ][kData][Njets_[mult]]->Add((TH1F*)histo_["eta"][kDiBos][Njets_[mult]]->Clone());
    histo_["eta BG"  ][kData][Njets_[mult]]->Add((TH1F*)histo_["eta"][kSTop ][Njets_[mult]]->Clone());
    if(mult==3) histo_["etaBGQCD"][kData][Njets_[mult]] = (TH1F*)histo_["eta"][kABCD][Njets_[mult]]->Clone();
    if(mult==4){
      histo_["etaBGQCD"][kData][Njets_[mult]] = (TH1F*)histo_["eta"][kQCD ][Njets_[mult]]->Clone();
      histo_["etaBGQCD"][kData][Njets_[mult]]->Scale(QCDVariation);
    }
    histo_["eta BG"  ][kData][Njets_[mult]]->Add(histo_["etaBGQCD"][kData][Njets_[mult]]);
    histo_["pt top"  ][kData][Njets_[mult]]->Add(histo_["pt BG"   ][kData][Njets_[mult]], -1);
    histo_["eta top" ][kData][Njets_[mult]]->Add(histo_["eta BG"  ][kData][Njets_[mult]], -1);
    // (iii) bin per bin efficiency corrections and division by luminosity
    // pt: start with second bin, include overflow, -2: vector strats with 0
    for(int bin=2; bin<=histo_["pt" ][kData][Njets_[mult]]->GetNbinsX()+1; ++bin){
      double      eff = topPtEff_ [bin-2];
      if(mult==3) eff = topPtEff2_[bin-2];
      histo_["pt top" ][kData][Njets_[mult]]->SetBinContent(bin, histo_["pt top" ][kData][Njets_[mult]]->GetBinContent(bin)     / (eff*luminosity*0.001));
      histo_["pt top" ][kData][Njets_[mult]]->SetBinError  (bin, sqrt( histo_["pt" ][kData][Njets_[mult]]->GetBinContent(bin) ) / (eff*luminosity*0.001));
    }
    // eta: start with 1st bin - no overflow -1: vector starts with 0
    for(int bin=1; bin<=histo_["eta" ][kData][Njets_[mult]]->GetNbinsX(); ++bin){
      double      eff = topEtaEff_ [bin-1];
      if(mult==3) eff = topEtaEff2_[bin-1];
      histo_["eta top"][kData][Njets_[mult]]->SetBinContent(bin, histo_["eta top"][kData][Njets_[mult]]->GetBinContent(bin)     / (eff*luminosity*0.001));
      histo_["eta top"][kData][Njets_[mult]]->SetBinError  (bin, sqrt( histo_["eta"][kData][Njets_[mult]]->GetBinContent(bin) ) / (eff*luminosity*0.001));
    }
    // (iv) divide per binwidth
    histo_["pt top" ][kData  ][Njets_[mult]]= divideByBinwidth(histo_["pt top" ][kData][Njets_[mult]], true);
    histo_["eta top"][kData  ][Njets_[mult]]= divideByBinwidth(histo_["eta top"][kData][Njets_[mult]], true);

    // b) gen ttbar sig + bkg - done only once
    if(mult==4){
      // (i) division by binwidth
      histo_["pt top" ][kGenSig][Njets_[3]]= divideByBinwidth((TH1F*)histo_["pt" ][kGenSig][Njets_[3]]->Clone(), true);
      histo_["pt top" ][kGenBkg][Njets_[3]]= divideByBinwidth((TH1F*)histo_["pt" ][kGenBkg][Njets_[3]]->Clone(), true);
      histo_["eta top"][kGenSig][Njets_[3]]= divideByBinwidth((TH1F*)histo_["eta"][kGenSig][Njets_[3]]->Clone(), true);
      histo_["eta top"][kGenBkg][Njets_[3]]= divideByBinwidth((TH1F*)histo_["eta"][kGenBkg][Njets_[3]]->Clone(), true);
      // (ii) division by luminosity
      scaleByLumi( histo_["pt top" ][kGenSig][Njets_[3]], luminosity*0.001);
      scaleByLumi( histo_["pt top" ][kGenBkg][Njets_[3]], luminosity*0.001);
      scaleByLumi( histo_["eta top"][kGenSig][Njets_[3]], luminosity*0.001);
      scaleByLumi( histo_["eta top"][kGenBkg][Njets_[3]], luminosity*0.001);
    }
    // do the printout for the values (pt/eta x ttbarsig/ttbarbkg/data)
    // pt
    std::cout << std::endl << "(i) pt" << std::endl;
    for(int idx=kData; idx<=kGenBkg; ++idx){
      if( (idx== kData) || ((mult==4)&&(idx==kGenSig)) || ((mult==4)&&(idx==kGenBkg)) ){
	int mult2=3;
	if(idx==kData  ) mult2=mult;
	if(idx==kData  ) std::cout << "data "+Njets_[mult2] << std::endl;
	if(idx==kGenSig) std::cout << "ttbar signal"        << std::endl;
	if(idx==kGenBkg) std::cout << "ttbar other"         << std::endl;
	for(int bin=2; bin<=histo_["pt" ][kData][Njets_[mult2]]->GetNbinsX(); ++bin){
	  std::cout << "bin " << bin << ": " << histo_["pt top" ][idx][Njets_[mult2]]->GetBinContent(bin);
	  std::cout << " +/- " << histo_["pt top" ][idx][Njets_[mult2]]->GetBinError(bin) << std::endl;
	  // save top differential(pt) xSec results for systematic variations and determination of systematic errors
	  if(idx==kData){
	    if(bin==2) writeToFile("top diffXSec "+Njets_[mult2], "systematicVariations/differentialTopPt"+Njets_[mult2]+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 0);
	    double value = histo_["pt top" ][kData][Njets_[mult2]]->GetBinContent(bin);
	    writeToFile(value, "systematicVariations/differentialTopPt"+Njets_[mult2]+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 1);
	  }
	}
      }
    }
    // eta
    std::cout << std::endl << "(ii) eta" << std::endl;
    for(int idx=kData; idx<=kGenBkg; ++idx){
      if( (idx== kData) || ((mult==4)&&(idx==kGenSig)) || ((mult==4)&&(idx==kGenBkg)) ){
	int mult2=3;
	if(idx==kData  ) mult2=mult;
	if(idx==kData  ) std::cout << "data"+Njets_[mult2] << std::endl;
	if(idx==kGenSig) std::cout << "ttbar signal"       << std::endl;
	if(idx==kGenBkg) std::cout << "ttbar other"        << std::endl;
	for(int bin=1; bin<=histo_["eta" ][kData][Njets_[mult2]]->GetNbinsX(); ++bin){
	  std::cout << "bin " << bin << ": " << histo_["eta top" ][idx][Njets_[mult2]]->GetBinContent(bin);
	  std::cout << " +/- " << histo_["eta top" ][idx][Njets_[mult2]]->GetBinError(bin) << std::endl;
	  // save top differential(eta) xSec results for systematic variations and determination of systematic errors
	  if(idx==kData){
	    if(bin==1) writeToFile("top diffXSec "+Njets_[mult2], "systematicVariations/differentialTopEta"+Njets_[mult2]+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 0);
	    double value = histo_["eta top"][kData][Njets_[mult2]]->GetBinContent(bin);
	    writeToFile(value, "systematicVariations/differentialTopEta"+Njets_[mult2]+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 1);
	  }
	}
      }
    }
  }

  // ---
  //    INCLUSIVE xSec (from data and MC) for chosen phase space
  // ---
  TH1F *sigmaLjetsInclusiveMCReco   = new TH1F("MCRecoLjets"  , "MCRecoLjets"  , 4, 0.5, 4.5);
  TH1F *sigmaLjetsInclusiveData     = new TH1F("data"         , "data"         , 4, 0.5, 4.5);
  TH1F *sigmaLjetsInclusiveMCGen    = new TH1F("MCGenLjets"   , "MCGenLjets"   , 4, 0.5, 4.5);
  TH1F *sigmaLjetsInclusiveMCGenTop = new TH1F("MCGenLjetsTop", "MCGenLjetsTop", 4, 0.5, 4.5);
  TH1F *sigmaLjetsInclusiveMCGenBkg = new TH1F("MCGenLjetsBkg", "MCGenLjetsBkg", 4, 0.5, 4.5);
  TH1F *sigmaLjetsInclusiveMCGenSig = new TH1F("MCGenLjetsSig", "MCGenLjetsSig", 4, 0.5, 4.5);
  TH1F *sigmaTopInclusiveDataNoBtag = new TH1F("dataTop1"     , "dataTop1"     , 6, 0.5, 6.5);
  TH1F *sigmaTopInclusiveMCReco     = new TH1F("MCRecoTop"    , "MCRecoTop"    , 6, 0.,  315./readLineFromFile(180-systematic, file));
  TH1F *sigmaTopInclusiveMCGen      = new TH1F("MCGenTop"     , "MCGenTop"     , 6, 0.5, 6.5);
  TH1F *sigmaTopInclusiveDataBtag   = new TH1F("dataTop2"     , "dataTop2"     , 6, 0.5, 6.5);
  TGraphErrors sigmaTopInclusiveDataGraph(2);
  std::vector<double> statErrExcl;
  std::cout << std::endl << std::endl << "inclusive cross sections:" << std::endl;
  // loop samples - l+jets MC(W,Z,top) and Data
  for(unsigned int idx=kData; idx<=kLepJets; ++idx){    
    if(idx==kData   ) std::cout << std::endl << std::endl << "a) from data" << std::endl;
    if(idx==kLepJets) std::cout << std::endl << std::endl << "b) from reco-MC (l+jets or top MC)" << std::endl;
    // loop jet multiplicities (no >=3 jets && >= 1 btag)
    for(unsigned int mult=0; mult<Njets_.size()-1; ++mult){
      std::cout << jetLabel(Njets_[mult])+ ": "<< std::endl;
      // ---
      // a1) l+jets (no btag)
      // ---
      if(mult<4){
	// (i) events after selection ( data / l+jets-MC )
	double Nselected = histo_["pt"][idx   ][Njets_[mult]]->Integral( 0 , histo_["pt"][idx   ][Njets_[mult]]->GetNbinsX()+1 );
	double NZjets    = histo_["pt"][kZjets][Njets_[mult]]->Integral( 0 , histo_["pt"][kZjets][Njets_[mult]]->GetNbinsX()+1 );
	double NDiBoson  = histo_["pt"][kDiBos][Njets_[mult]]->Integral( 0 , histo_["pt"][kDiBos][Njets_[mult]]->GetNbinsX()+1 );
        // (ii) QCD estimation (from ABCD) for data
	double NQCD=0;
        if(idx==kData) NQCD=NQCD_[mult];
        // (iii) calculate cross section (include MC-efficiency and luminosity)
	double Nmeasure = Nselected-NQCD-NZjets-NDiBoson;
        double sigma = Nmeasure/(ljetsInclusiveEff_[mult]*luminosity*0.001);
	double dsigma = sqrt(Nselected)/(ljetsInclusiveEff_[mult]*luminosity*0.001);
	std::cout << "l+jets:" << setprecision(3) << fixed << sigma << " +/- " << dsigma << " pb" << std::endl;
	// (iv) fill inclusive xSec(Njets) calculated from pt histo (QCD substracted and efficiency correction applied)
	if(idx==kData){
	  sigmaLjetsInclusiveData->SetBinContent(mult+1, sigma );
	  sigmaLjetsInclusiveData->SetBinError  (mult+1, dsigma);
	  // save l+jet xSec results for systematic variations and determination of systematic errors
	  bool append =true;
	  if(mult==0) append=false;
	  writeToFile("l+jets cross section (phase space) "+Njets_[mult], "systematicVariations/ljetsXSec"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", append);
	  writeToFile(sigma, "systematicVariations/ljetsXSec"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 1);
	}
	if(idx==kLepJets){
	  sigmaLjetsInclusiveMCReco->SetBinContent(mult+1, sigma );
	  sigmaLjetsInclusiveMCReco->SetBinError  (mult+1, dsigma);
	}
      }
      // ---
      // a2) l+jets excl jet bins (no btag)
      // ---
      if(mult<3 && idx==kData){
	// (i) events after selection ( data / l+jets-MC )
	double Nselected = histo_["pt"][idx   ][Njets_[mult+1]]->Integral( 0 , histo_["pt"][idx   ][Njets_[mult+1]]->GetNbinsX()+1 );
	double NZjets    = histo_["pt"][kZjets][Njets_[mult+1]]->Integral( 0 , histo_["pt"][kZjets][Njets_[mult+1]]->GetNbinsX()+1 );
	double NDiBoson  = histo_["pt"][kDiBos][Njets_[mult+1]]->Integral( 0 , histo_["pt"][kDiBos][Njets_[mult+1]]->GetNbinsX()+1 );
	// (ii) QCD estimation (from ABCD) for data
	double NQCD=0;
	if(idx==kData) NQCD=NQCD_[mult+1];
	// (iii) calculate cross section (include MC-efficiency and luminosity)
	double Nmeasure = Nselected-NQCD-NZjets-NDiBoson;
	double sigmaNPlus1 = Nmeasure/(ljetsInclusiveEff_[mult+1]*luminosity*0.001);
	double sigma = sigmaLjetsInclusiveData->GetBinContent(mult+1) - sigmaNPlus1;
	double dsigma = sigmaLjetsInclusiveData->GetBinError  (mult+1) * sqrt((histo_["pt"][kData][Njets_[mult]]->Integral( 0 , histo_["pt"][kData][Njets_[mult]]->GetNbinsX()+1 )-Nselected)/histo_["pt"][kData][Njets_[mult]]->Integral( 0 , histo_["pt"][kData][Njets_[mult]]->GetNbinsX()+1 ));
	statErrExcl.push_back(dsigma);
	std::cout << "l+jets (excl):" << setprecision(3) << fixed << sigma << " +/- " << dsigma << " pb" << std::endl;
	// save l+jet xSec results for systematic variations and determination of systematic errors
	bool append =true;
	if(mult==0) append=false;
	writeToFile("l+jets (excl) cross section (phase space) "+Njets_[mult], "systematicVariations/ljetsXSecExcl"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", append);
	writeToFile(sigma, "systematicVariations/ljetsXSecExcl"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 1);
      }
      if(mult==3 && idx==kData){
	statErrExcl.push_back(sigmaLjetsInclusiveData->GetBinError(mult+1));
	writeToFile("l+jets (excl) cross section (phase space) "+Njets_[mult], "systematicVariations/ljetsXSecExcl"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 1);
	writeToFile(sigmaLjetsInclusiveData->GetBinContent(mult+1), "systematicVariations/ljetsXSecExcl"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 1);
      }
      // ---
      // b) top 
      // ---
      // b1) >=4jets & >=1 Btag
      // (just apply effiency corrections)
      // loop jet multiplicities
      if(mult==4){
	double Nmeasure =0;
	double Nselected=0;
	// (i) events after selection ( data / top-MC )
	if(idx==kData){
	  Nselected   = histo_["pt"][kData ]["Njets4Btag"]->Integral( 0 , histo_["pt"][kData ]["Njets4Btag"]->GetNbinsX()+1 );
	  double NBG  = histo_["pt"][kWjets]["Njets4Btag"]->Integral( 0 , histo_["pt"][kWjets]["Njets4Btag"]->GetNbinsX()+1 )*VjetsSF;
	  NBG        += histo_["pt"][kSTop ]["Njets4Btag"]->Integral( 0 , histo_["pt"][kSTop ]["Njets4Btag"]->GetNbinsX()+1 );
	  NBG        += histo_["pt"][kZjets]["Njets4Btag"]->Integral( 0 , histo_["pt"][kZjets]["Njets4Btag"]->GetNbinsX()+1 )*VjetsSF;
	  NBG        += histo_["pt"][kDiBos]["Njets4Btag"]->Integral( 0 , histo_["pt"][kDiBos]["Njets4Btag"]->GetNbinsX()+1 );
	  NBG        += histo_["pt"][kQCD  ]["Njets4Btag"]->Integral( 0 , histo_["pt"][kQCD  ]["Njets4Btag"]->GetNbinsX()+1 )*QCDVariation;
	  Nmeasure = Nselected-NBG;
	}
	if(idx==kLepJets){
	  Nmeasure =  histo_["pt"][kSig][Njets_[mult]]->Integral( 0 , histo_["pt"][kSig][Njets_[mult]]->GetNbinsX()+1 );
	  Nmeasure += histo_["pt"][kBkg][Njets_[mult]]->Integral( 0 , histo_["pt"][kBkg][Njets_[mult]]->GetNbinsX()+1 );
	}
        // (ii) calculate cross section (include MC-efficiency and luminosity, take BG from MC)
	double sigma  = Nmeasure / effNjets4Btag / (0.001*luminosity);
	double dsigma = sqrt( Nselected ) / (effNjets4Btag*0.001*luminosity);
	std::cout << std::endl << "top: " << setprecision(4) << fixed << sigma << " +/- " << dsigma << " /pb" << std::endl;
	// (iii) fill inclusive xSec(phase space) calculated from >=4 jets & >= 1Btag histo (QCD subtracted, efficiency correction applied)
	if(idx==kData){
	  sigmaTopInclusiveDataBtag->SetBinContent(1, sigma );
	  sigmaTopInclusiveDataBtag->SetBinError  (1, dsigma);
	  sigmaTopInclusiveDataGraph.SetPoint(0, sigma, 1.);
	  sigmaTopInclusiveDataGraph.SetPointError(0, dsigma, 0.);
	  // save top xSec (phase space) results for systematic variations and determination of systematic errors
	  writeToFile("top cross section (phase space) N(jets)>=4 & N(Btags)>=1", "systematicVariations/topXSec"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 0);
	  writeToFile(sigma, "systematicVariations/topXSec"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 1);
	}
	if(idx==kLepJets){
	  sigmaTopInclusiveMCReco->SetBinContent(1, sigma );
	  sigmaTopInclusiveMCReco->SetBinError  (1, dsigma);
	}
      }
      // ---
      // b2) >=4jets & W-estimation
      // subtract W-boson bkg estimation from l+jets corrected value
      // loop jet multiplicities
      if(mult==3&&idx==kData){
	// (i) events after selection 
	double Nselected = histo_["pt"][idx   ][Njets_[mult]]->Integral( 0 , histo_["pt"][idx   ][Njets_[mult]]->GetNbinsX()+1 );
	// (ii) substract QCD and Z+jets and single Top and DiBoson (from RECO MC)
	double NQCD      = NQCD_[mult];
	                 //histo_["pt"][kQCD  ][Njets_[mult]]->Integral( 0 , histo_["pt"][kQCD  ][Njets_[mult]]->GetNbinsX()+1 );
	double NZjets    = histo_["pt"][kZjets][Njets_[mult]]->Integral( 0 , histo_["pt"][kZjets][Njets_[mult]]->GetNbinsX()+1 )*VjetsSF;
	double NDiBoson  = histo_["pt"][kDiBos][Njets_[mult]]->Integral( 0 , histo_["pt"][kDiBos][Njets_[mult]]->GetNbinsX()+1 );
	double NSTop     = histo_["pt"][kSTop ][Njets_[mult]]->Integral( 0 , histo_["pt"][kSTop ][Njets_[mult]]->GetNbinsX()+1 );
	// (iii) W+jets estimation (from charge asymmetrie method) - need to scale with same efficiency!
	double NW =NWestimate;
	double Nmeasure = Nselected-NQCD-NZjets-NW-NDiBoson;
	// if c.a. method is not working: substract W+jets from MC reco
	if(Nmeasure<=0||NW<0||1==1){
	  if(Nmeasure<=0) std::cout << "N(W) from c.a. is larger than N(all events), take N(W) from MC gen";
	  if(NW<0)        std::cout << "N(W) from c.a. is negative, take N(W) from MC gen";
	  else            std::cout << "N(W) from c.a. is not trusted at the moment, take N(W) from MC gen";
	  double NWMC=histo_["pt"][kWjets][Njets_[mult]]->Integral( 0 , histo_["pt"][kWjets][Njets_[mult]]->GetNbinsX()+1 );
	  NWMC*=VjetsSF;
	  Nmeasure=Nselected-NQCD-NZjets-NWMC-NSTop-NDiBoson;
	}
	// (iv) calculate cross section 
	double sigma  = Nmeasure/(0.001*luminosity*effNjets4);
	double dsigma = sqrt(Nselected)/(luminosity*0.001*effNjets4);
	std::cout << std::endl << "top: " << setprecision(4) << fixed << sigma << " +/- " << dsigma << " pb" << std::endl;
	// (v) fill inclusive xSec(phase space) calculated from >=4 jets histo (QCD and Wjets subtracted, efficiency correction applied)
	sigmaTopInclusiveDataNoBtag->SetBinContent(2, sigma );
	sigmaTopInclusiveDataNoBtag->SetBinError  (2, dsigma);
	sigmaTopInclusiveDataGraph.SetPoint(1, sigma, 2.);
	sigmaTopInclusiveDataGraph.SetPointError(1, dsigma, 0.);
	// save top xSec (phase space) results for systematic variations and determination of systematic errors
	writeToFile("top cross section (phase space) N(jets)>=4 & W-estimation", "systematicVariations/topXSec2"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 0);
	writeToFile(sigma, "systematicVariations/topXSec2"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 1);
      }
    }
  }

  // ---
  // c) l+jets and top gen MC
  // ---
  std::cout << std::endl << std::endl << "c) from gen-MC (W+jets && top MC)" << std::endl;
  // loop jet multiplicities (>= 1-4)
  for(unsigned int mult=0; mult<4; ++mult){
    double NTopSig = histo_["pt"][kGenSig ][Njets_[mult]]->Integral( 0 , histo_["pt"][kGenSig ][Njets_[mult]]->GetNbinsX()+1 ); 
    double NTopBkg = histo_["pt"][kGenBkg ][Njets_[mult]]->Integral( 0 , histo_["pt"][kGenBkg ][Njets_[mult]]->GetNbinsX()+1 ); 
    double NWjets  = histo_["pt"][kGenW   ][Njets_[mult]]->Integral( 0 , histo_["pt"][kGenW   ][Njets_[mult]]->GetNbinsX()+1 );
    double NSTop   = histo_["pt"][kGenSTop][Njets_[mult]]->Integral( 0 , histo_["pt"][kGenSTop][Njets_[mult]]->GetNbinsX()+1 );
    double NLjets = NSTop + NWjets + NTopSig + NTopBkg;
    double NTopAll = NSTop + NTopSig + NTopBkg;
    double sigmaLjetsGen = NLjets/(luminosity*0.001);
    double sigmaTopGen   = NTopAll/(luminosity*0.001);
    double sigmaTTGen    = (NTopSig+NTopBkg) / (luminosity*0.001);
    double sigmaTTGenSig = NTopSig/(luminosity*0.001);
    if(mult<4 ){
      sigmaLjetsInclusiveMCGen   ->SetBinContent(mult+1, sigmaLjetsGen);
      sigmaLjetsInclusiveMCGenTop->SetBinContent(mult+1, sigmaTopGen  );
      sigmaLjetsInclusiveMCGenBkg->SetBinContent(mult+1, sigmaTTGen   );
      sigmaLjetsInclusiveMCGenSig->SetBinContent(mult+1, sigmaTTGenSig);
      std::cout << "gen MC l+jets XSec "+jetLabel(Njets_[mult])+": ";
      std::cout << setprecision(4) << fixed << sigmaLjetsGen << " pb"  << std::endl;
    }
    if(mult==3){
      sigmaTopInclusiveMCGen  ->SetBinContent(1, sigmaTTGen);
      std::cout << "gen MC Top XSec "+jetLabel(Njets_[mult])+": ";
      std::cout << setprecision(4) << fixed  << sigmaTTGen << " pb"  << std::endl;
    }
  }
  std::cout << std::endl;

  // ---
  //    e) extrapolation to whole phase space
  // ---
  // 1. when using btag and 2. when subtracting w+jets from c.a./ or for low statistics from MC gen
  // sigma_topInclusive = sigma_topPhaseSpace  / extrapolation
  // extrapolation = N(ttbar MC gen >=4 jets) / N(ttbar theory)
  // N(ttbar theory) depends on the cross section which MUST be the same like it is 
  // used in the calculation of the lumiweight to cancel out in extrapolation factor
  // (i) set theory cross section draw as reference
  double sigmaTheory = 157.5;
  // (ii) get extrapolation factor from chosen to inclusive phase space
  double extrapolation = readLineFromFile(180-systematic, file);
  std::cout << "extrapolation factor from chosen to inclusive phase space: " << extrapolation  << std::endl;
  // (iii) apply extrapolation factor on cross section results from phase space
  double sigmaData       = sigmaTopInclusiveDataBtag->GetBinContent(1)   * extrapolation;
  double errorSigmaData  = sigmaTopInclusiveDataBtag->GetBinError(1)     * extrapolation;
  double sigmaData2      = sigmaTopInclusiveDataNoBtag->GetBinContent(2) * extrapolation;
  double errorSigmaData2 = sigmaTopInclusiveDataNoBtag->GetBinError(2)   * extrapolation;
  // (iv) fill histos with the calculated values
  TH1F *sigmaTopExtrapolatedData   = new TH1F("sigmaTopExtrapolatedData"  , "sigmaTopExtrapolatedData"  , 2, 0, 2.0);
  TH1F *sigmaTopExtrapolatedData2  = new TH1F("sigmaTopExtrapolatedData2" , "sigmaTopExtrapolatedData2" , 2, 0, 2.0);
  TH1F *sigmaTopExtrapolatedTheory = new TH1F("sigmaTopExtrapolatedTheory", "sigmaTopExtrapolatedTheory", 2, 0, 315);
  TGraphErrors sigmaTopExtrapolatedDataGraph(2);
  sigmaTopExtrapolatedData  ->SetBinContent(1, sigmaData      );
  sigmaTopExtrapolatedData  ->SetBinError  (1, errorSigmaData );
  sigmaTopExtrapolatedData2 ->SetBinContent(2, sigmaData2     );
  sigmaTopExtrapolatedData2 ->SetBinError  (2, errorSigmaData2);
  sigmaTopExtrapolatedTheory->SetBinContent(1, sigmaTheory    );
  sigmaTopExtrapolatedDataGraph.SetPoint(0, sigmaData, 1.);
  sigmaTopExtrapolatedDataGraph.SetPointError(0, errorSigmaData, 0.);
  sigmaTopExtrapolatedDataGraph.SetPoint(1, sigmaData2, 2.);
  sigmaTopExtrapolatedDataGraph.SetPointError(1, errorSigmaData2, 0.);
  // (vii) printing to have numbers
  std::cout << std::endl << "total cross section for complete phasespace" << std::endl;
  std::cout << "theory: " << setprecision(1) << fixed << sigmaTheory << " pb" << std::endl;
  std::cout << "data (use btag): "  << setprecision(1) << fixed << sigmaData;
  std::cout << " +/- " << setprecision(1) << fixed << errorSigmaData << " pb" << std::endl;
  std::cout << "data (no btag ): "  << setprecision(1) << fixed << sigmaData2;
  std::cout << " +/- " << setprecision(1) << fixed << errorSigmaData2 << " pb" << std::endl;
  // (viii) save top xSec (inclusive) results for systematic variations and determination of systematic errors
  writeToFile("top cross section (inclusive) N(jets)>=4 & N(Btags)>=1", "systematicVariations/topXSecInclusive1"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 0);
  writeToFile(sigmaData,  "systematicVariations/topXSecInclusive1"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 1);
  writeToFile("top cross section (inclusive) N(jets)>=4 & W-estimation", "systematicVariations/topXSecInclusive2"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 0);
  writeToFile(sigmaData2, "systematicVariations/topXSecInclusive2"+TopSample+"TopMC"+JES+putSysOn+"Lumi"+LuminosityVariation+EffScale+SampleScale+".txt", 1);

  if(createPlots){
    // ---
    //    create legends 
    // ---
    // a) create jet multiplicity label
    std::vector<TPaveLabel*> jetMultiplicity_;
    for(unsigned int mult=0; mult<Njets_.size(); ++mult){ 
      TPaveLabel *jet = new TPaveLabel(0.11, 0.78, 0.62, 1.0, jetLabel(Njets_[mult]), "br NDC");
      // take into account that b-tag labels are longer
      if((mult==Njets_.size()-2)||(mult==Njets_.size()-1)){
	jet->SetX1(0.12);
	jet->SetX2(0.90);
	jet->SetY1(0.78);
	jet->SetY2(1.0);
      }
      jet->SetFillStyle(0);
      jet->SetBorderSize(0);
      jet->SetTextSize(0.26);
      jetMultiplicity_.push_back((TPaveLabel*)jet->Clone());
    }
    // b) create legend with color code for all samples (for yield plots) - extra canvas
    TLegend *yieldLeg = new TLegend(0.08, 0.19, 0.94, 0.88);
    yieldLeg->SetFillStyle(0);
    yieldLeg->SetBorderSize(0);
    //  yieldLeg->SetHeader("MC "+lum+" / pb @ 7TeV");
    yieldLeg->AddEntry( histo_["pt yield"][kData  ]["Njets1"], "Data ("+lum+" pb^{-1})"     , "PL");
    yieldLeg->AddEntry( histo_["pt yield"][kQCD   ]["Njets1"], "QCD"                             , "F" );
    yieldLeg->AddEntry( histo_["pt yield"][kWjets ]["Njets1"], "W#rightarrowl#nu"              , "F" );
    yieldLeg->AddEntry( histo_["pt yield"][kSToptW]["Njets1"], "Single-Top"                    , "F" );
    yieldLeg->AddEntry( histo_["pt yield"][kZjets ]["Njets1"], "Z/#gamma*#rightarrowl^{+}l^{-}", "F" );
    yieldLeg->AddEntry( histo_["pt yield"][kBkg   ]["Njets1"], "t#bar{t} other"                , "F" );
    yieldLeg->AddEntry( histo_["pt yield"][kSig   ]["Njets1"], "t#bar{t} signal ( #mu prompt )"  , "F" );
    yieldLeg->AddEntry( histo_["pt yield"][kDiBos ]["Njets1"], "VV"               , "F" );
    // c) create legend for l+jets differential cross sections - extra canvas
    TLegend *lJetsXSecLeg = new TLegend(0.01, 0.30, 0.90, 0.92);
    lJetsXSecLeg->SetFillStyle(0);
    lJetsXSecLeg->SetBorderSize(0);
    lJetsXSecLeg->AddEntry(histo_[ljetsXSecDiff_[0]][kData][Njets_[0]], "Data ("+lum+" pb^{-1})", "PL");
    lJetsXSecLeg->AddEntry(histo_[ljetsGen_[0]][kGenW   ][Njets_[0]],    "W#rightarrowl#nu"                   , "F" );
    lJetsXSecLeg->AddEntry(histo_[ljetsGen_[0]][kGenSTop][Njets_[0]],    "Single-Top"                         , "F" );
    lJetsXSecLeg->AddEntry(histo_[ljetsGen_[0]][kGenBkg ][Njets_[0]],    "t#bar{t} ( #tau#rightarrow#mu )", "F" );
    lJetsXSecLeg->AddEntry(histo_[ljetsGen_[0]][kGenSig ][Njets_[0]],    "t#bar{t} ( #mu prompt )"                    , "F" );
    // c)2) create legend for l+jets differential cross sections - small
    TLegend *lJetsXSecLegSmall = new TLegend(0.43, 0.7, 0.93, 0.94);
    lJetsXSecLegSmall->SetFillStyle(0);
    lJetsXSecLegSmall->SetBorderSize(0);
    lJetsXSecLegSmall->AddEntry(histo_[ljetsXSecDiff_[0]][kData][Njets_[0]], "Data ("+lum+" pb^{-1})", "PL");
    lJetsXSecLegSmall->AddEntry(histo_[ljetsGen_[0]][kGenW   ][Njets_[0]],    "W#rightarrowl#nu"                   , "F" );
    lJetsXSecLegSmall->AddEntry(histo_[ljetsGen_[0]][kGenSTop][Njets_[0]],    "Single-Top"                         , "F" );
    lJetsXSecLegSmall->AddEntry(histo_[ljetsGen_[0]][kGenBkg ][Njets_[0]],    "t#bar{t} ( #tau#rightarrow#mu )", "F" );
    lJetsXSecLegSmall->AddEntry(histo_[ljetsGen_[0]][kGenSig ][Njets_[0]],    "t#bar{t} ( #mu prompt )"                    , "F" );
    // c)3) create legend for l+jets differential cross sections - split part1
    TLegend *lJetsXSecLegPart1 = new TLegend(0.15, 0.04, 0.83, 0.96);
    lJetsXSecLegPart1->SetFillStyle(0);
    lJetsXSecLegPart1->SetBorderSize(0);
    lJetsXSecLegPart1->AddEntry(histo_[ljetsXSecDiff_[0]][kData][Njets_[0]], "Data ("+lum+" pb^{-1})", "PL");
    lJetsXSecLegPart1->AddEntry(histo_[ljetsGen_[0]][kGenSig][Njets_[0]],    "t#bar{t} ( #mu prompt )"       , "F" );
    // c)4) create legend for l+jets differential cross sections - split part2
    TLegend *lJetsXSecLegPart2 = new TLegend(0.15, 0.04, 0.83, 0.96);
    lJetsXSecLegPart2->SetFillStyle(0);
    lJetsXSecLegPart2->SetBorderSize(0);
    lJetsXSecLegPart2->AddEntry(histo_[ljetsGen_[0]][kGenBkg ][Njets_[0]],    "t#bar{t} ( #tau#rightarrow#mu )", "F" );
    lJetsXSecLegPart2->AddEntry(histo_[ljetsGen_[0]][kGenW   ][Njets_[0]],    "W#rightarrowl#nu"                   , "F" );
    lJetsXSecLegPart2->AddEntry(histo_[ljetsGen_[0]][kGenSTop][Njets_[0]],    "Single-Top"                         , "F" );
    // d) create legend for l+jets differential Normalized cross sections - extra canvas
    TLegend *lJetsXSecLegNorm = new TLegend(0.01, 0.30, 1.20, 0.92);
    lJetsXSecLegNorm->SetFillStyle(0);
    lJetsXSecLegNorm->SetBorderSize(0);
    if(loadValues)   lJetsXSecLegNorm->SetHeader("after QCD and efficiency correction");
    if(!loadValues)  lJetsXSecLegNorm->SetHeader("without any QCD or efficiency corrections");
    lJetsXSecLegNorm->AddEntry(histo_["pt l+jets diff norm XSec"][kData   ]["Njets1"], "Data ("+lum+" pb^{-1})", "PL");
    lJetsXSecLegNorm->AddEntry(histo_["pt l+jets diff norm XSec"][kLepJets]["Njets1"], "MC (W#rightarrowl#nu, t#bar{t})", "PL");
    // e) create legends for event composition
    // part 1)
    TLegend *eventCompositionPart1 = new TLegend(0.15, 0.04, 0.83, 0.96);
    eventCompositionPart1->SetFillStyle(0);
    eventCompositionPart1->SetBorderSize(0);
    eventCompositionPart1->SetHeader("signal composition:");
    eventCompositionPart1->AddEntry( histo_["pt composition"][kSig   ]["Njets1"], "t#bar{t} signal ( #mu prompt )", "PL");
    eventCompositionPart1->AddEntry( histo_["pt composition"][kBkg   ]["Njets1"], "t#bar{t} other" , "PL");
    eventCompositionPart1->AddEntry( histo_["pt composition"][kSToptW]["Njets1"], "Single-Top"     , "PL");
    // part 2) 
    TLegend *eventCompositionPart2 = new TLegend(0.15, 0.04, 0.83, 0.96);
    eventCompositionPart2->SetFillStyle(0);
    eventCompositionPart2->SetBorderSize(0);
    eventCompositionPart2->AddEntry( histo_["pt composition"][kQCD  ]["Njets1"], "QCD"                             , "PL");
    eventCompositionPart2->AddEntry( histo_["pt composition"][kWjets]["Njets1"], "W#rightarrowl#nu"              , "PL");
    eventCompositionPart2->AddEntry( histo_["pt composition"][kZjets]["Njets1"], "Z/#gamma*#rightarrowl^{+}l^{-}", "PL");
    eventCompositionPart2->AddEntry( histo_["pt composition"][kDiBos]["Njets1"], "VV", "PL");
    // f) create legends for inclusive cross sections
    // (ia) l+jets
    TLegend *inclusiveCrossSectionLjetsLeg = new TLegend(0.5, 0.55, 0.96, 0.79);
    inclusiveCrossSectionLjetsLeg->SetFillStyle(0);
    inclusiveCrossSectionLjetsLeg->SetFillColor(10);
    inclusiveCrossSectionLjetsLeg->SetBorderSize(0);
    inclusiveCrossSectionLjetsLeg->SetTextSize(0.05);
    inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveData    , "Data ("+lum+" pb^{-1})" , "PL");
    inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveMCGen   , "W#rightarrowl#nu"                    ,  "F");
    inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveMCGenTop, "Single-Top"                          ,  "F");
    inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveMCGenBkg, "t#bar{t} ( #tau#rightarrow#mu )" ,  "F");
    inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveMCGenSig, "t#bar{t} ( #mu prompt )"                     ,  "F");
    //  inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveMCReco, "l+jets reco MC + corrections", "L" );
    // (ib) l+jets
    TLegend *inclusiveCrossSectionLjetsLeg2 = new TLegend(0.5, 0.63, 0.96, 0.8);
    inclusiveCrossSectionLjetsLeg2->SetFillStyle(0);
    inclusiveCrossSectionLjetsLeg2->SetFillColor(10);
    inclusiveCrossSectionLjetsLeg2->SetBorderSize(0);
    inclusiveCrossSectionLjetsLeg2->SetTextSize(0.05);
    inclusiveCrossSectionLjetsLeg2->AddEntry( sigmaLjetsInclusiveData    , "Data ("+lum+" pb^{-1})" , "PL");
    inclusiveCrossSectionLjetsLeg2->AddEntry( sigmaLjetsInclusiveMCGen   , "W#rightarrowl#nu"                    ,  "F");
    inclusiveCrossSectionLjetsLeg2->AddEntry( sigmaLjetsInclusiveMCGenTop, "Single-Top"                          ,  "F");
    inclusiveCrossSectionLjetsLeg2->AddEntry( sigmaLjetsInclusiveMCGenBkg, "t#bar{t} ( #tau#rightarrow#mu )" ,  "F");
    inclusiveCrossSectionLjetsLeg2->AddEntry( sigmaLjetsInclusiveMCGenSig, "t#bar{t} ( #mu prompt )"                     ,  "F");
    //  inclusiveCrossSectionLjetsLeg2->AddEntry( sigmaLjetsInclusiveMCReco, "l+jets reco MC + corrections", "L" );
    // (ii) top
    TLegend *inclusiveCrossSectionTopLeg =  new TLegend(0.2, 0.54, 0.94, 0.66);
    inclusiveCrossSectionTopLeg->SetFillStyle (1001);
    inclusiveCrossSectionTopLeg->SetFillColor(kWhite);
    inclusiveCrossSectionTopLeg->SetBorderSize(0);
    inclusiveCrossSectionTopLeg->SetTextSize(0.05);
    //inclusiveCrossSectionTopLeg->SetHeader("top cross section");
    inclusiveCrossSectionTopLeg->AddEntry( sigmaTopInclusiveDataBtag  , "Data ("+lum+" pb^{-1})"   , "PL");
    //inclusiveCrossSectionTopLeg->AddEntry( sigmaTopInclusiveDataNoBtag, "Data ("+lum+" pb^{-1}), W-estim.", "PL");
    inclusiveCrossSectionTopLeg->AddEntry( sigmaTopInclusiveMCGen     , "t#bar{t} MADGRAPH"                 , "L" );
    //  inclusiveCrossSectionTopLeg->AddEntry( sigmaTopInclusiveMCReco    , "l+jets reco MC +corr., use btag"  , "P ");
    // g)  create legends for DIFFERNTIAL TOP cross sections
    // (1) method using b-tag
    TLegend *differentialTopLeg = new TLegend(0.43, 0.7, 0.93, 0.94);
    differentialTopLeg->SetFillStyle(0);
    differentialTopLeg->SetBorderSize(0);
    differentialTopLeg->AddEntry( histo_["pt top"][kData  ][Njets_[4]]  , "Data ("+lum+" pb^{-1}), ", "PL");
    differentialTopLeg->AddEntry( histo_["pt top"][kData  ][Njets_[4]]  , "with b tagging"                     , ""  );
    differentialTopLeg->AddEntry( histo_["pt top"][kGenSig][Njets_[3]]  , "t#bar{t} ( #mu prompt )"                    , "F" );
    differentialTopLeg->AddEntry( histo_["pt top"][kGenBkg][Njets_[3]]  , "t#bar{t} ( #tau#rightarrow#mu )", "F" );
    // (2) method using W-estimation
    TLegend *differentialTopLeg2 = new TLegend(0.43, 0.7, 0.93, 0.94);
    differentialTopLeg2->SetFillStyle(0);
    differentialTopLeg2->SetBorderSize(0);
    differentialTopLeg2->AddEntry( histo_["pt top"][kData  ][Njets_[4]]  , "Data ("+lum+" pb^{-1}), ", "PL");
    differentialTopLeg2->AddEntry( histo_["pt top"][kData  ][Njets_[4]]  , "without b tagging"                  , ""  );
    differentialTopLeg2->AddEntry( histo_["pt top"][kGenSig][Njets_[3]]  , "t#bar{t} ( #mu prompt )"                    , "F" );
    differentialTopLeg2->AddEntry( histo_["pt top"][kGenBkg][Njets_[3]]  , "t#bar{t} ( #tau#rightarrow#mu )", "F" );
    // i)  create legends for inclusive TOP cross section extrapolated to whole phase space
    TLegend *inclusiveCrossSectionTopLeg2 =  new TLegend(0.07, 0.5, 0.94, 0.85);
    inclusiveCrossSectionTopLeg2->SetFillStyle (1001);
    inclusiveCrossSectionTopLeg2->SetFillColor(kWhite);
    inclusiveCrossSectionTopLeg2->SetBorderSize(0);
    inclusiveCrossSectionTopLeg2->SetTextSize(0.05);
    inclusiveCrossSectionTopLeg2->SetHeader("total t#bar{t} cross section");
    inclusiveCrossSectionTopLeg2->AddEntry( sigmaTopExtrapolatedData  , "Data ("+lum+" pb^{-1})"   , "PL");
    //inclusiveCrossSectionTopLeg2->AddEntry( sigmaTopExtrapolatedData2 , "Data ("+lum+" pb^{-1}), W-estim.", "PL");
    inclusiveCrossSectionTopLeg2->AddEntry( sigmaTopExtrapolatedTheory, "#sigma_{NLO} (MCFM, m_{t}=172.5 GeV)", "L" );

    // ---
    //    create canvas 
    // ---
    std::vector<TCanvas*> MyCanvas;
    // a) canvas for yield and diff norm xsec (also legends) and event composition
    for(int idx=0; idx<=83; idx++){ 
      char canvname[10];
      sprintf(canvname,"canv%i",idx);    
      MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
      canvasStyle(*MyCanvas[idx]);
    }
    // b) canvas for event composition legends (half size)
    MyCanvas.push_back( new TCanvas( "canv"+getTStringFromInt(MyCanvas.size()), "canv"+getTStringFromInt(MyCanvas.size()), 600, 200) );
    canvasStyle(*MyCanvas[MyCanvas.size()-1]);
    MyCanvas.push_back( new TCanvas( "canv"+getTStringFromInt(MyCanvas.size()), "canv"+getTStringFromInt(MyCanvas.size()), 600, 200) );
    canvasStyle(*MyCanvas[MyCanvas.size()-1]);
    MyCanvas.push_back( new TCanvas( "canv"+getTStringFromInt(MyCanvas.size()), "canv"+getTStringFromInt(MyCanvas.size()), 600, 200) );
    canvasStyle(*MyCanvas[MyCanvas.size()-1]);
    MyCanvas.push_back( new TCanvas( "canv"+getTStringFromInt(MyCanvas.size()), "canv"+getTStringFromInt(MyCanvas.size()), 600, 200) );
    canvasStyle(*MyCanvas[MyCanvas.size()-1]);

    // create canvas indicator
    int canvasNumber=0;

    // ---
    //    do the printing for event yield plots (all MC samples, all jet multiplicities and all variables)
    // ---
    // loop jet multiplicities (also btag)
    for(int mult=0; mult<6; ++mult){
      // loop pt, eta and phi
      for(unsigned int var=0; var<variables_.size(); ++var){
	// adress canvas with correct name
	MyCanvas[canvasNumber]->cd(0);
	MyCanvas[canvasNumber]->SetTitle(variables_[var]+"EventYield"+Njets_[mult]+log);
	if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
	bool sTopCount=true;
	// a) MC samples (loop)
	for(int idx=kQCD; idx>=0; --idx){
	  double min = 0.;
	  double maxValue = getMaxValue(*histo_[yield_[var]][kData][Njets_[mult]], variables_[var]);
	  double maxQCD = histo_[yield_[var]][kQCD][Njets_[mult]]->GetMaximum();
	  if(maxQCD>maxValue)maxValue=maxQCD;
	  double max = 1.15*maxValue;
	  // set axis for plots
	  if(idx==kQCD){
	    if(logartihmicPlots){
	      if(variables_[var]=="pt"){
		min=0.003*luminosity/1000.;
		max=exp(1.15*(std::log(maxValue)-std::log(min))+std::log(min));
	      }
	      else{
		min=0.5;
		max=exp(1.3*(std::log(maxValue)-std::log(min))+std::log(min));
	      }
	    }
	    if(variables_[var]=="phi") axesStyle(*histo_[yield_[var]][kQCD][Njets_[mult]], "#"+variables_[var]+"(#mu)", "events", min, max, 0.06, 1.4);
	    if(variables_[var]=="eta") axesStyle(*histo_[yield_[var]][kQCD][Njets_[mult]], "#"+variables_[var]+"(#mu)", "events", min, max, 0.06, 1.4);
	    if(variables_[var]=="pt" ) axesStyle(*histo_[yield_[var]][kQCD][Njets_[mult]], "p_{t}(#mu) [GeV]", "events / GeV", min, max, 0.06, 1.4);
	  }
	  // draw MC histos
	  if(idx==kQCD ){
	    // color style
	    histogramStyle(*histo_[yield_[var]][idx][Njets_[mult]], idx);	
	    histo_[yield_[var]][idx][Njets_[mult]]->Draw("HIST");	
	  }
	  else if(sTopCount || (idx!=kSTopt && idx!=kSTops && idx!=kSToptW)){
	    histogramStyle(*histo_[yield_[var]][idx][Njets_[mult]], idx);		
	    histo_[yield_[var]][idx][Njets_[mult]]->Draw("HIST same");
	  }
	  if(idx==kSTopt || idx==kSTops || idx==kSToptW)sTopCount=false;
	}
	// b) data
	histogramStyle(*histo_[yield_[var]][kData][Njets_[mult]], kData);
	histo_[yield_[var]][kData][Njets_[mult]]->DrawClone("p e X0 same");
	histo_[yield_[var]][kData][Njets_[mult]]->SetMarkerSize(1.8);
	histo_[yield_[var]][kData][Njets_[mult]]->Draw     ("p e X0 same");
	// c) redraw axis
	histo_[yield_[var]][kQCD][Njets_[mult]]->Draw("AXIS same");
	// d) draw jet multiplicity label
	jetMultiplicity_[mult]->Draw("same");
	// move to next canvas
	++canvasNumber;	
      }
    }

    // ---
    //    do the printing for DIFFERENTIAL NORMALIZED l+jets cross sections (all l+jets MC and data )
    // ---
    // loop jet multiplicities (also btag)
    for(int mult=0; mult<6; ++mult){
      // loop pt, eta and phi
      for(unsigned int var=0; var<variables_.size(); ++var){
	// adress canvas with correct name
	MyCanvas[canvasNumber]->cd(0);
	MyCanvas[canvasNumber]->SetTitle(variables_[var]+"DiffNormXSec"+Njets_[mult]+log);
	if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
	// loop samples
	for(int idx=kLepJets; idx>=kData; --idx){
	  // set style for histos
	  // a) for MC
	  if(idx==kLepJets){
	    histogramStyle(*histo_[ljetsXSec_[var]][idx][Njets_[mult]], kLepJets, false);
	    // set axis for plots
	    double min = 0.;
	    double maxValue = getMaxValue(*histo_[ljetsXSec_[var]][kData][Njets_[mult]], variables_[var], true, "diffNormXSec"+variables_[var], mult, up, down);
	    double max = 1.15*maxValue;
	    if(variables_[var]!="pt" && mult < 3)max=1.3*maxValue;
	    if(logartihmicPlots){
	      if(variables_[var]=="pt"){
		min=0.0003;
		max=exp(1.15*(std::log(maxValue)-std::log(min))+std::log(min));
	      }
	      else{
		min=0.03;
		max=exp(1.3*(std::log(maxValue)-std::log(min))+std::log(min));
	      }
	    }
	    if((variables_[var]=="phi")||(variables_[var]=="eta")){
	      axesStyle(*histo_[ljetsXSec_[var]][idx][Njets_[mult]], "#"+variables_[var]+"(#mu)", "#frac{1}{#sigma} #frac{d#sigma}{d#"+variables_[var]+" (#mu)}", min, max, 0.055, 1.6);
	    }
	    if(variables_[var]=="pt") {
	      axesStyle(*histo_[ljetsXSec_[var]][idx][Njets_[mult]], "p_{t}(#mu) [GeV]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{t} (#mu)} [ GeV^{-1} ]", min, max, 0.055, 1.6);
	    }
	  }
	  // b) for data
	  if(idx==kData){
	    histogramStyle(*histo_[ljetsXSec_[var]][idx][Njets_[mult]], kData, false);
	  }
	  // draw histos
	  if(idx==kLepJets){
	    if(mult<4)histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Draw("AXIS");
	    else histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Draw("HIST");
	  }
	  if(idx==kData   ){
	    histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Draw("p X0 e1 same");
	    if(finalPlots) systematicError("diffNormXSec"+variables_[var], mult, *histo_[ljetsXSec_[var]][kData][Njets_[mult]], variables_[var], up, down);
	  }
	}
		// draw ttbar sig, bkg and W contribution as stack plot if no btag is applied
	if(mult<4){
	// a) create stack plots
	histo_[ljetsXSecGen_[var]][kGenBkg ][Njets_[mult]]->Add(histo_[ljetsXSecGen_[var]][kGenSig ][Njets_[mult]]);
	histo_[ljetsXSecGen_[var]][kGenSTop][Njets_[mult]]->Add(histo_[ljetsXSecGen_[var]][kGenBkg ][Njets_[mult]]);
	histo_[ljetsXSecGen_[var]][kGenW   ][Njets_[mult]]->Add(histo_[ljetsXSecGen_[var]][kGenSTop][Njets_[mult]]);
	// b) choose color style
	histogramStyle(*histo_[ljetsXSecGen_[var]][kGenSig ][Njets_[mult]], kSig);
	histogramStyle(*histo_[ljetsXSecGen_[var]][kGenBkg ][Njets_[mult]], kBkg);
	histogramStyle(*histo_[ljetsXSecGen_[var]][kGenW   ][Njets_[mult]], kWjets);
	histogramStyle(*histo_[ljetsXSecGen_[var]][kGenSTop][Njets_[mult]], kSTops);
	// c) Draw
	histo_[ljetsXSecGen_[var]][kGenW   ][Njets_[mult]]->Draw("same");
	histo_[ljetsXSecGen_[var]][kGenSTop][Njets_[mult]]->Draw("same");
	histo_[ljetsXSecGen_[var]][kGenBkg ][Njets_[mult]]->Draw("same");
	histo_[ljetsXSecGen_[var]][kGenSig ][Njets_[mult]]->Draw("same");
	// d) redraw data
	//histo_[ljetsXSec_[var]][kLepJets][Njets_[mult]]->Draw("HIST");
	histo_[ljetsXSec_[var]][kData][Njets_[mult]]->Draw("p X0 e1 same");
	if(finalPlots) systematicError("diffNormXSec"+variables_[var], mult, *histo_[ljetsXSec_[var]][kData][Njets_[mult]], variables_[var]);
	}
	// draw jet multiplicity label
	jetMultiplicity_[mult]->Draw("same");
	// redraw axis
	histo_[ljetsXSec_[var]][kLepJets][Njets_[mult]]->Draw("AXIS same");
	// move to next canvas
	++canvasNumber;
      }
    }

    // ---
    //    do the printing for DIFFERENTIAL l+jets cross section (all l+jets MC and data )
    // ---
    // loop jet multiplicities (also btag)
    for(int mult=0; mult<6; ++mult){
      // loop pt, eta and phi
      for(unsigned int var=0; var<variables_.size(); ++var){
	// adress canvas with correct name
	MyCanvas[canvasNumber]->cd(0);
	MyCanvas[canvasNumber]->SetTitle(variables_[var]+"DiffXSec"+Njets_[mult]+log);
	if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
	// loop samples
	for(int idx=kLepJets; idx>=kData; --idx){
	  // set style for histos
	  // a) for MC
	  if(idx==kLepJets){
	    histogramStyle(*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], kLepJets);
	    // set axis for plots
	    double min = 0.;
	    double maxValue = getMaxValue(*histo_[ljetsXSecDiff_[var]][kData][Njets_[mult]], variables_[var], true, "differentialXSec"+variables_[var], mult, up, down);
	    double max = 1.15*maxValue;
	    if(logartihmicPlots){
	      if(variables_[var]=="pt"){
		min=0.005;
		max=exp(1.15*(std::log(maxValue)-std::log(min))+std::log(min));
	      }
	      else{
		min=0.5;
		max=exp(1.3*(std::log(maxValue)-std::log(min))+std::log(min));
	      }
	      //if(variables_[var]=="pt") max=0.1*max;
	      //if(variables_[var]!="pt") max=max/(5*mult+1);
	    }
	    if((variables_[var]=="phi")||(variables_[var]=="eta")){
	      axesStyle(*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], "#"+variables_[var]+"(#mu)", "#frac{d#sigma}{d#"+variables_[var]+" (#mu)} [ pb ]", min, max, 0.055, 1.5);
	    }
	    if(variables_[var]=="pt") {
	      axesStyle(*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], "p_{t}(#mu) [GeV]", "#frac{d#sigma}{dp_{t} (#mu)} [ pb / GeV ]", min, max, 0.055, 1.5);
	    }
	  }
	  // b) for data
	  if(idx==kData){
	    histogramStyle(*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], kData);
	  }
	  // draw histos
	  // a) MC
	  if(idx==kLepJets){
	    histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->Draw("HIST");
	    if(mult<4){
	      int mult2=mult;
	      histogramStyle(*histo_[ljetsGen_[var]][kGenW][Njets_[mult2]], kWjets);
	      histo_[ljetsGen_[var]][kGenW][Njets_[mult2]]->Draw("Hist same");
	      histogramStyle(*histo_[ljetsGen_[var]][kGenSTop][Njets_[mult2]], kSTops);
	      histo_[ljetsGen_[var]][kGenSTop][Njets_[mult2]]->Draw("Hist same");
	      histogramStyle(*histo_[ljetsGen_[var]][kGenBkg][Njets_[mult2]], kBkg);
	      histo_[ljetsGen_[var]][kGenBkg][Njets_[mult2]]->Draw("Hist same");
	      histogramStyle(*histo_[ljetsGen_[var]][kGenSig][Njets_[mult2]], kSig);
	      histo_[ljetsGen_[var]][kGenSig][Njets_[mult2]]->Draw("Hist same");
	    }
	    //	  if(mult==4) draw scaled MC-reco with Btag;
	  }
	  // b) data
	  if(idx==kData   ){
	    //lJetsXSecLegSmall->Draw("same");
	    histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->Draw("p e1 X0 same");
	    if(finalPlots) systematicError("differentialXSec"+variables_[var], mult, *histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], variables_[var], up, down);
	  }
	}
	// draw jet multiplicity label
	jetMultiplicity_[mult]->Draw("same");
	// redraw axis
	histo_[ljetsXSecDiff_[var]][kLepJets][Njets_[mult]]->Draw("AXIS same");
	// move to next canvas
	++canvasNumber;      
      }
    }

    // ---
    //    do the printing for MC based event composition
    // ---  
    // loop jet multiplicities (also btag)
    for(int mult=0; mult<6; ++mult){
      // loop pt, eta and phi
      for(unsigned int var=0; var<variables_.size(); ++var){
	// adress canvas with correct name
	MyCanvas[canvasNumber]->cd(0);
	MyCanvas[canvasNumber]->SetTitle(variables_[var]+"RelativeEventComposition"+Njets_[mult]);
	MyCanvas[canvasNumber]->SetGrid(1,1);
	// loop samples
	for(int idx=0; idx<=kQCD; ++idx){
	  if(histo_[composition_[var]][idx][Njets_[mult]]){
	    histogramStyle(*histo_[composition_[var]][idx][Njets_[mult]], idx, false); 
	    // axis style
	    if(idx==0){
	      if(variables_[var]=="phi"||variables_[var]=="eta"){
		axesStyle(*histo_[composition_[var]][idx][Njets_[mult]], "#"+variables_[var]+"(#mu)", "rel. event composition", 0., 1.);
	      }
	      if(variables_[var]=="pt"){
		axesStyle(*histo_[composition_[var]][idx][Njets_[mult]], "p_{t}(#mu)", "rel. event composition", 0., 1.);
	      }	  
	    }
	    // draw histos
	    if(idx==0){
	      histo_[composition_[var]][idx][Njets_[mult]]->Draw("hist" );
	      histo_[composition_[var]][idx][Njets_[mult]]->Draw("p same");
	    }
	    else{
	      histo_[composition_[var]][idx][Njets_[mult]]->Draw("hist same");
	      histo_[composition_[var]][idx][Njets_[mult]]->Draw("p same"   );
	    }
	  }
	}
	// draw jet multiplicity label
	jetMultiplicity_[mult]->Draw("same");
	// move to next canvas
	++canvasNumber; 
      }
    }

    // ---
    //    do the printing for the inclusive cross sections
    // ---
    // a1) l+jets
    MyCanvas[canvasNumber] ->cd(0);
    MyCanvas[canvasNumber] ->SetTitle("inclusiveCrossSectionLjets"+log);
    if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
    double min = 0.;
    double maxValue = getMaxValue(*sigmaLjetsInclusiveData, "Njets", true, "ljetsXSec", 6, up, down);
    double max = 1.1*maxValue;
    if(logartihmicPlots){
      min=1.95;
      max=exp(1.55*(std::log(maxValue)-std::log(min))+std::log(min));
    }
    axesStyle(*sigmaLjetsInclusiveData, "N_{jets}(p_{t}>30GeV)", "#sigma ( l+jets ) [ pb ]", min, max, 0.05, 1.2, 0.075);
    sigmaLjetsInclusiveData->GetXaxis()->SetNdivisions(510);
    histogramStyle(*sigmaLjetsInclusiveMCReco, kData);
    histogramStyle(*sigmaLjetsInclusiveMCGen, kWjets);
    histogramStyle(*sigmaLjetsInclusiveData, kData);
    for(int iBin = 1; iBin<=sigmaLjetsInclusiveData->GetNbinsX(); ++iBin)
      {
	char binLabel[6];
	sprintf(binLabel,"#geq%i",iBin);
	sigmaLjetsInclusiveData->GetXaxis()->SetBinLabel(iBin, binLabel);
      }
    sigmaLjetsInclusiveData    ->Draw("AXIS" );
    sigmaLjetsInclusiveMCGen     ->DrawClone("histsame" );
    histogramStyle(*sigmaLjetsInclusiveMCGenTop, kSTop);
    sigmaLjetsInclusiveMCGenTop  ->Draw("histsame" );
    histogramStyle(*sigmaLjetsInclusiveMCGenBkg, kBkg);
    sigmaLjetsInclusiveMCGenBkg  ->Draw("histsame" );
    histogramStyle(*sigmaLjetsInclusiveMCGenSig, kSig);
    sigmaLjetsInclusiveMCGenSig  ->Draw("histsame" );
    sigmaLjetsInclusiveData      ->Draw("p e1 X0 same"); 
    sigmaLjetsInclusiveData    ->Draw("AXIS same" );
    if(finalPlots) systematicError("ljetsXSec", 6, *sigmaLjetsInclusiveData, "Njets", up, down);
    inclusiveCrossSectionLjetsLeg->Draw("same" );
    //DrawLabel("phase space:"                                , 0.33 , 0.55, 0.82 , 0.75);
    DrawLabel("p_{t}(#mu)>20 GeV, |#eta(#mu)|<2.1"  , 0.25, 0.8, 0.99 , 1.);
    DrawLabel("p_{t}(jets)>30 GeV, |#eta(jets)|<2.4", 0.25, 0.73, 0.99, 0.93);
    ++canvasNumber;

    // a2) l+jets with ratio
    MyCanvas[canvasNumber] ->cd(0);
    MyCanvas[canvasNumber] ->SetTitle("inclusiveCrossSectionLjetsRatio"+log);
    if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
    MyCanvas[canvasNumber]->Size(600,800);
    TH1F *sigmaLjetsInclusiveDataMod = (TH1F*)sigmaLjetsInclusiveData->Clone();
    axesStyle(*sigmaLjetsInclusiveDataMod, "N_{jets}(p_{t}>30GeV)", "#sigma ( l+jets ) [ pb ]", min, 1.33*max, 0.05, 1.2, 0.075);
    sigmaLjetsInclusiveDataMod->GetXaxis()->SetTitleSize(0);
    sigmaLjetsInclusiveDataMod    ->DrawClone("AXIS" );
    sigmaLjetsInclusiveMCGen     ->DrawClone("histsame" );
    histogramStyle(*sigmaLjetsInclusiveMCGenTop, kSTop);
    sigmaLjetsInclusiveMCGenTop  ->DrawClone("histsame" );
    histogramStyle(*sigmaLjetsInclusiveMCGenBkg, kBkg);
    sigmaLjetsInclusiveMCGenBkg  ->DrawClone("histsame" );
    histogramStyle(*sigmaLjetsInclusiveMCGenSig, kSig);
    sigmaLjetsInclusiveMCGenSig  ->DrawClone("histsame" );
    sigmaLjetsInclusiveDataMod      ->DrawClone("p e1 X0 same"); 
    sigmaLjetsInclusiveDataMod    ->DrawClone("AXIS same" );
    std::vector<double> statErrMod;
    for(int iBin=1; iBin<=sigmaLjetsInclusiveDataMod->GetNbinsX(); iBin++)
      {
	statErrMod.push_back(sigmaLjetsInclusiveDataMod->GetBinError(iBin));
      }
    if(finalPlots) systematicError("ljetsXSec", 6, *sigmaLjetsInclusiveDataMod, "Njets", up, down);
    inclusiveCrossSectionLjetsLeg2->Draw("same" );
    //DrawLabel("phase space:"                                , 0.33 , 0.55, 0.82 , 0.75);
    DrawLabel("p_{t}(#mu)>20 GeV, |#eta(#mu)|<2.1"  , 0.25, 0.8, 0.99 , 1., 0.195);
    DrawLabel("p_{t}(jets)>30 GeV, |#eta(jets)|<2.4", 0.25, 0.73, 0.99, 0.93, 0.195);
    TH1F* sigmaLjetsInclusiveDataModSys = systematicHisto("ljetsXSec", 6, *sigmaLjetsInclusiveDataMod, "Njets", up, down);
    axesStyle(*sigmaLjetsInclusiveDataModSys, "N_{jets}(p_{t}>30GeV)", "#sigma ( l+jets ) [ pb ]", min, 1.33*max, 0.05, 1.2, 0.075);
    ratio_smal(sigmaLjetsInclusiveDataModSys,sigmaLjetsInclusiveMCGen,1.59,0.41,statErrMod);
    ++canvasNumber;

    // a3) l+jets exclusive bins with ratio
    MyCanvas[canvasNumber] ->cd(0);
    MyCanvas[canvasNumber] ->SetTitle("inclusiveCrossSectionLjetsRatioExcl"+log);
    if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
    MyCanvas[canvasNumber]->Size(600,800);
    TH1F *sigmaLjetsInclusiveDataExcl = (TH1F*)sigmaLjetsInclusiveData->Clone();
    TH1F *sigmaLjetsInclusiveMCGenExcl = (TH1F*)sigmaLjetsInclusiveMCGen->Clone();
    TH1F *sigmaLjetsInclusiveMCGenTopExcl = (TH1F*)sigmaLjetsInclusiveMCGenTop->Clone();
    TH1F *sigmaLjetsInclusiveMCGenBkgExcl = (TH1F*)sigmaLjetsInclusiveMCGenBkg->Clone();
    TH1F *sigmaLjetsInclusiveMCGenSigExcl = (TH1F*)sigmaLjetsInclusiveMCGenSig->Clone();
    for(int iBin=1; iBin<4; iBin++){
      sigmaLjetsInclusiveDataExcl->SetBinContent(iBin,sigmaLjetsInclusiveData->GetBinContent(iBin)-sigmaLjetsInclusiveData->GetBinContent(iBin+1));
      sigmaLjetsInclusiveDataExcl->SetBinError(iBin,sigmaLjetsInclusiveData->GetBinError(iBin)*sigmaLjetsInclusiveData->GetBinError(iBin)+
					       sigmaLjetsInclusiveData->GetBinError(iBin+1)*sigmaLjetsInclusiveData->GetBinError(iBin+1));
      sigmaLjetsInclusiveMCGenExcl->SetBinContent(iBin,sigmaLjetsInclusiveMCGen->GetBinContent(iBin)-sigmaLjetsInclusiveMCGen->GetBinContent(iBin+1));
      sigmaLjetsInclusiveMCGenExcl->SetBinError(iBin,sigmaLjetsInclusiveMCGen->GetBinError(iBin)*sigmaLjetsInclusiveMCGen->GetBinError(iBin)+
						sigmaLjetsInclusiveMCGen->GetBinError(iBin+1)*sigmaLjetsInclusiveMCGen->GetBinError(iBin+1));
      sigmaLjetsInclusiveMCGenTopExcl->SetBinContent(iBin,sigmaLjetsInclusiveMCGenTop->GetBinContent(iBin)-sigmaLjetsInclusiveMCGenTop->GetBinContent(iBin+1));
      sigmaLjetsInclusiveMCGenTopExcl->SetBinError(iBin,sigmaLjetsInclusiveMCGenTop->GetBinError(iBin)*sigmaLjetsInclusiveMCGenTop->GetBinError(iBin)+
						   sigmaLjetsInclusiveMCGenTop->GetBinError(iBin+1)*sigmaLjetsInclusiveMCGenTop->GetBinError(iBin+1));
      sigmaLjetsInclusiveMCGenBkgExcl->SetBinContent(iBin,sigmaLjetsInclusiveMCGenBkg->GetBinContent(iBin)-sigmaLjetsInclusiveMCGenBkg->GetBinContent(iBin+1));
      sigmaLjetsInclusiveMCGenBkgExcl->SetBinError(iBin,sigmaLjetsInclusiveMCGenBkg->GetBinError(iBin)*sigmaLjetsInclusiveMCGenBkg->GetBinError(iBin)+
						   sigmaLjetsInclusiveMCGenBkg->GetBinError(iBin+1)*sigmaLjetsInclusiveMCGenBkg->GetBinError(iBin+1));
      sigmaLjetsInclusiveMCGenSigExcl->SetBinContent(iBin,sigmaLjetsInclusiveMCGenSig->GetBinContent(iBin)-sigmaLjetsInclusiveMCGenSig->GetBinContent(iBin+1));
      sigmaLjetsInclusiveMCGenSigExcl->SetBinError(iBin,sigmaLjetsInclusiveMCGenSig->GetBinError(iBin)*sigmaLjetsInclusiveMCGenSig->GetBinError(iBin)+
						   sigmaLjetsInclusiveMCGenSig->GetBinError(iBin+1)*sigmaLjetsInclusiveMCGenSig->GetBinError(iBin+1));
    }
    axesStyle(*sigmaLjetsInclusiveDataExcl, "N_{jets}(p_{t}>30GeV)", "#sigma ( l+jets ) [ pb ]", min, 1.33*max, 0.05, 1.2, 0.075);
    sigmaLjetsInclusiveDataExcl->GetXaxis()->SetTitleSize(0);
    for(int iBin = 1; iBin<=sigmaLjetsInclusiveData->GetNbinsX(); ++iBin)
      {
	char binLabel[6];
	if(iBin<4)sprintf(binLabel,"%i",iBin);
	else sprintf(binLabel,"#geq%i",iBin);
	sigmaLjetsInclusiveDataExcl->GetXaxis()->SetBinLabel(iBin, binLabel);
      }
    sigmaLjetsInclusiveDataExcl      ->DrawClone("AXIS" );
    sigmaLjetsInclusiveMCGenExcl     ->DrawClone("histsame" );
    histogramStyle(*sigmaLjetsInclusiveMCGenTopExcl, kSTop);
    sigmaLjetsInclusiveMCGenTopExcl  ->DrawClone("histsame" );
    histogramStyle(*sigmaLjetsInclusiveMCGenBkgExcl, kBkg);
    sigmaLjetsInclusiveMCGenBkgExcl  ->DrawClone("histsame" );
    histogramStyle(*sigmaLjetsInclusiveMCGenSigExcl, kSig);
    sigmaLjetsInclusiveMCGenSigExcl  ->DrawClone("histsame" );
    sigmaLjetsInclusiveDataExcl      ->DrawClone("p e1 X0 same"); 
    sigmaLjetsInclusiveDataExcl      ->DrawClone("AXIS same" );
    if(finalPlots) systematicError("ljetsXSecExcl", 6, *sigmaLjetsInclusiveDataExcl, "Njets", up, down);
    inclusiveCrossSectionLjetsLeg2->Draw("same");
    //DrawLabel("phase space:"                                , 0.33 , 0.55, 0.82 , 0.75);
    DrawLabel("p_{t}(#mu)>20 GeV, |#eta(#mu)|<2.1"  , 0.25, 0.8, 0.99 , 1., 0.195);
    DrawLabel("p_{t}(jets)>30 GeV, |#eta(jets)|<2.4", 0.25, 0.73, 0.99, 0.93, 0.195);
    TH1F* sigmaLjetsInclusiveDataExclSys = systematicHisto("ljetsXSecExcl", 6, *sigmaLjetsInclusiveDataExcl, "Njets", up, down);
    axesStyle(*sigmaLjetsInclusiveDataExclSys, "N_{jets}(p_{t}>30GeV)", "#sigma ( l+jets ) [ pb ]", min, 1.33*max, 0.05, 1.2, 0.075);
    ratio_smal(sigmaLjetsInclusiveDataExclSys,sigmaLjetsInclusiveMCGenExcl,1.59,0.41,statErrExcl);
    ++canvasNumber;

    //// a4) W+jets exclusive bins with ratio
    //MyCanvas[canvasNumber] ->cd(0);
    //MyCanvas[canvasNumber] ->SetTitle("inclusiveCrossSectionLjetsRatioWjetsExcl"+log);
    //if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
    //MyCanvas[canvasNumber]->Size(600,800);
    //if(logartihmicPlots){
    //  min=0.95;
    //  max=exp(1.5*(std::log(maxValue)-std::log(min))+std::log(min));
    //}
    //TH1F *sigmaLjetsInclusiveDataWjetsExcl = (TH1F*)sigmaLjetsInclusiveDataExcl->Clone();
    //TH1F *sigmaLjetsInclusiveMCGenWjetsExcl = (TH1F*)sigmaLjetsInclusiveMCGenExcl->Clone();
    //sigmaLjetsInclusiveDataWjetsExcl->Add(sigmaLjetsInclusiveMCGenTopExcl,-1.);
    //sigmaLjetsInclusiveMCGenWjetsExcl->Add(sigmaLjetsInclusiveMCGenTopExcl,-1.);
    //
    //axesStyle(*sigmaLjetsInclusiveDataWjetsExcl, "N_{jets}(p_{t}>30GeV)", "#sigma ( W+jets ) [ pb ]", min, 1.33*max, 0.05, 1.2, 0.075);
    //sigmaLjetsInclusiveDataWjetsExcl      ->Draw("AXIS" );
    //sigmaLjetsInclusiveMCGenWjetsExcl     ->DrawClone("histsame" );
    //sigmaLjetsInclusiveDataWjetsExcl      ->Draw("p e1 X0 same"); 
    //sigmaLjetsInclusiveDataWjetsExcl      ->Draw("AXIS same" );
    //if(finalPlots) systematicError("ljetsXSecExcl", 6, *sigmaLjetsInclusiveDataWjetsExcl, "Njets", up, down);
    //inclusiveCrossSectionLjetsLeg2->Draw("same" );
    ////DrawLabel("phase space:"                                , 0.33 , 0.55, 0.82 , 0.75);
    //DrawLabel("p_{t}(#mu)>20 GeV, |#eta(#mu)|<2.1"  , 0.25, 0.8, 0.99 , 1., 0.195);
    //DrawLabel("p_{t}(jets)>30 GeV, |#eta(jets)|<2.4", 0.25, 0.73, 0.99, 0.93, 0.195);
    //ratio_smal(sigmaLjetsInclusiveDataWjetsExcl,sigmaLjetsInclusiveMCGenWjetsExcl,3.69,0.31);
    //++canvasNumber;

    // b) top with & without Btag in phase space
    MyCanvas[canvasNumber]     ->cd(0);
    MyCanvas[canvasNumber]     ->SetTitle("inclusiveCrossSectionTop");
    MyCanvas[canvasNumber]->SetLeftMargin( 0.05 );
    axesStyle(*sigmaTopInclusiveMCReco, "#sigma (t#bar{t}#rightarrow#mu + #geq 4 jets) [ pb ]", "", 0., 7.5, 0.05, 1.55);
    histogramStyle(*sigmaTopInclusiveMCReco    , 7   ,  false);
    histogramStyle(*sigmaTopInclusiveMCGen     , kSig,  false);
    histogramStyle(*sigmaTopInclusiveDataNoBtag, kData   ,  false);
    histogramStyle(*sigmaTopInclusiveDataBtag  , kData   , false);
    sigmaTopInclusiveMCReco->GetYaxis()->SetNdivisions (0);
    sigmaTopInclusiveMCReco    ->Draw("AXIS"); 
    double theoryErrorUp  =23.2;
    double theoryErrorDown=24.4;
    // extrapolation: defined in e) extrapolation to whole phase space
    TBox* box2 = new TBox((double)sigmaTopInclusiveMCGen->GetBinContent(1)+theoryErrorUp/extrapolation, 0.5, (double)sigmaTopInclusiveMCGen->GetBinContent(1)-theoryErrorDown/extrapolation, 2.5);
    box2->SetFillColor(kRed-7);
    box2->SetFillStyle(1001);
    box2->Draw("same");
    //  sigmaTopInclusiveMCGen     ->Draw("phistsame");
    drawLine(sigmaTopInclusiveMCGen->GetBinContent(1), 0.5, sigmaTopInclusiveMCGen->GetBinContent(1), 2.5, sigmaTopInclusiveMCGen->GetLineColor());
    //sigmaTopInclusiveDataNoBtag->Draw("p e1 X0 same");
    //sigmaTopInclusiveDataBtag  ->Draw("p e1 X0 same");
    sigmaTopInclusiveDataGraph.SetMarkerSize(2.);
    sigmaTopInclusiveDataGraph.SetLineWidth(2);
    sigmaTopInclusiveDataGraph.SetMarkerStyle(20);
    sigmaTopInclusiveDataGraph.DrawClone("p e1 same");
    //if(finalPlots) systematicError("topXSec" , 8, *sigmaTopInclusiveDataBtag  , "1");
    //if(finalPlots) systematicError("topXSec2", 8, *sigmaTopInclusiveDataNoBtag, "2");
    if(finalPlots){
      sigmaTopInclusiveDataGraph.SetPointError(0, systematicError2("topXSec" , *sigmaTopInclusiveDataBtag  , 1, up, down), 0.);
      sigmaTopInclusiveDataGraph.SetPointError(1, systematicError2("topXSec2", *sigmaTopInclusiveDataNoBtag, 2, up, down), 0.);
    }
    sigmaTopInclusiveDataGraph.Draw("p e same");
    inclusiveCrossSectionTopLeg->Draw("same" );
    DrawLabel("t#bar{t} cross section"                 , 0.06, 0.80, 0.99, 1.00);
    DrawLabel("p_{t}(#mu)>20 GeV, |#eta(#mu)|<2.1"     , 0.06, 0.73, 0.99, 0.93);
    DrawLabel("N(jets, p_{t}>30 GeV, |#eta|<2.4)#geq 4", 0.06, 0.66, 0.99, 0.86);

    DrawLabel("pre-tagged", 0.06, 0.27, 0.5, 0.47);
    DrawLabel("tagged", 0.06, 0.16, 0.5, 0.36);
    //DrawLabel("| #eta |<2.4"                   , 0.57, 0.14, 0.92, 0.32);
    sigmaTopInclusiveMCReco    ->Draw("AXIS same");
    ++canvasNumber;

    // c) top with & without b-tag extrapolated to whole phase space
    MyCanvas[canvasNumber]->cd(0);
    MyCanvas[canvasNumber]->SetTitle("inclusiveCrossSectionTopExtrapolatedWholePhaseSpace");
    MyCanvas[canvasNumber]->SetLeftMargin( 0.05 );
    axesStyle(*sigmaTopExtrapolatedTheory, "#sigma (t#bar{t}) [ pb ]", "", 0., 7.5, 0.05, 1.55);
    histogramStyle(*sigmaTopExtrapolatedTheory, kSig, false);
    histogramStyle(*sigmaTopExtrapolatedData  , kData   , false);
    histogramStyle(*sigmaTopExtrapolatedData2 , kData   , false);
    sigmaTopExtrapolatedTheory->GetYaxis()->SetNdivisions (0);
    sigmaTopExtrapolatedTheory  ->Draw("AXIS");
    TBox* box = new TBox((double)sigmaTopExtrapolatedTheory->GetBinContent(1)+theoryErrorUp, 0.5, (double)sigmaTopExtrapolatedTheory->GetBinContent(1)-theoryErrorDown, 2.5);
    box->SetFillColor(kRed-7);
    box->SetFillStyle(1001);
    box->Draw("same");
    drawLine(sigmaTopExtrapolatedTheory->GetBinContent(1), 0.5, sigmaTopExtrapolatedTheory->GetBinContent(1), 2.5, sigmaTopExtrapolatedTheory->GetLineColor());
    //sigmaTopExtrapolatedData2   ->Draw("p e1 X0 same");
    //sigmaTopExtrapolatedData    ->Draw("p e1 X0 same");
    sigmaTopExtrapolatedDataGraph.SetMarkerSize(2.);
    sigmaTopExtrapolatedDataGraph.SetLineWidth(2);
    sigmaTopExtrapolatedDataGraph.SetMarkerStyle(20);
    sigmaTopExtrapolatedDataGraph.DrawClone("p e1 same");
    //if(finalPlots) systematicError("topXSecInclusive1", 8   , *sigmaTopExtrapolatedData , "1");
    //if(finalPlots) systematicError("topXSecInclusive2", 8   , *sigmaTopExtrapolatedData2, "2");
    if(finalPlots){
      sigmaTopExtrapolatedDataGraph.SetPointError(0, systematicError2("topXSecInclusive1", *sigmaTopExtrapolatedData , 1, up, down), 0.);
      sigmaTopExtrapolatedDataGraph.SetPointError(1, systematicError2("topXSecInclusive2", *sigmaTopExtrapolatedData2, 2, up, down), 0.);
    }
    sigmaTopExtrapolatedDataGraph.Draw("p e same");
    inclusiveCrossSectionTopLeg2->Draw("same");

    DrawLabel("pre-tagged", 0.06, 0.27, 0.5, 0.47);
    DrawLabel("tagged", 0.06, 0.16, 0.5, 0.36);
    sigmaTopExtrapolatedTheory  ->Draw("AXIS same");
    ++canvasNumber;

    // ---
    //    do the printing for the DIFFERENTIAL TOP cross sections >= 4 jets
    // --- 
    // with(4) and without(3) btag
    for(unsigned int mult=4; mult>=3; --mult){
      // a) pt 
      MyCanvas[canvasNumber]->cd(0);
      MyCanvas[canvasNumber]->SetTitle("ptDifferentialTopCrossSection"+Njets_[mult]+log);
      if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
      // set axis 
      double min = 0.;
      double maxValue = getMaxValue(*histo_["pt top"][kData][Njets_[mult]], "pt", true, "differentialTopPt"+Njets_[mult], 7, up, down);
      double max = 1.5*maxValue;
      if(logartihmicPlots){
	min=0.0001;
	max=exp(1.5*(std::log(maxValue)-std::log(min))+std::log(min));
      }
//       double max = 0.43;
//       if(logartihmicPlots){
// 	min=0.0001;
// 	max=120.0;
//       }
      // Draw gen ttbar sig + bkg as stack and data as points on top
      histo_["pt top" ][kGenSig][Njets_[3]]->Add(histo_["pt top" ][kGenBkg][Njets_[3]]);
      histogramStyle(*histo_["pt top" ][kGenSig][Njets_[3]], kSig);
      axesStyle(*histo_["pt top" ][kGenSig][Njets_[3]], "p_{t}(#mu) [GeV]", "#frac{d#sigma}{dp_{t} (#mu)} (t#bar{t}#rightarrow#mu + #geq 4 jets) [ pb / GeV ]", min, max, 0.05, 1.55);
      histo_["pt top" ][kGenSig][Njets_[3]]->DrawCopy("hist");
      histogramStyle(*histo_["pt top" ][kGenBkg][Njets_[3]],kBkg);
      histo_["pt top" ][kGenBkg][Njets_[3]]->DrawCopy("hist same");
      histogramStyle(*histo_["pt top" ][kData  ][Njets_[mult]], kData);
      histo_["pt top" ][kData  ][Njets_[mult]]->DrawCopy("p e1  X0 same");
      if(finalPlots) systematicError("differentialTopPt"+Njets_[mult], 7, *histo_["pt top" ][kData  ][Njets_[mult]], "pt", up, down);
      histo_["pt top" ][kGenSig][Njets_[3]]->DrawCopy("axis same");
      //jetMultiplicity_[3]->Draw("same");
      if(mult==4) differentialTopLeg ->Draw("same");
      if(mult==3) differentialTopLeg2->Draw("same");
      ++canvasNumber;

      // b) eta
      MyCanvas[canvasNumber]->cd(0);
      MyCanvas[canvasNumber]->SetTitle("etaDifferentialTopCrossSection"+Njets_[mult]+log);
      if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
      // set axis 
      double min2 = 0.;
      double max2Value = getMaxValue(*histo_["eta top"][kData][Njets_[mult]], "eta", true, "differentialTopEta"+Njets_[mult], 7, up, down);
      double max2 = 1.5*max2Value;
      if(logartihmicPlots){
	min2=0.05;
	max2=exp(1.5*(std::log(max2Value)-std::log(min2))+std::log(min2));
      }

      // Draw gen ttbar sig + bkg as stack and data as points on top
      histo_["eta top" ][kGenSig][Njets_[3]]->Add(histo_["eta top" ][kGenBkg][Njets_[3]]);
      histogramStyle(*histo_["eta top" ][kGenSig][Njets_[3]], kSig);  
      axesStyle(*histo_["eta top"][kGenSig][Njets_[3]], "#eta(#mu)", "#frac{d#sigma}{d#eta (#mu)} (t#bar{t}#rightarrow#mu + #geq 4 jets) [ pb ]", min2, max2, 0.05, 1.55);
      histo_["eta top" ][kGenSig][Njets_[3]]->DrawCopy("hist");
      histogramStyle(*histo_["eta top" ][kGenBkg][Njets_[3]], kBkg);
      histo_["eta top" ][kGenBkg][Njets_[3]]->Draw("hist same");
      histogramStyle(*histo_["eta top" ][kData  ][Njets_[mult]], kData);
      histo_["eta top" ][kData  ][Njets_[mult]]->Draw("p e1 X0 same");
      if(finalPlots) systematicError("differentialTopEta"+Njets_[mult], 7, *histo_["eta top"][kData][Njets_[mult]], "eta", up, down);
      histo_["eta top" ][kGenSig][Njets_[3]   ]->Draw("axis same");
      //jetMultiplicity_[3]->Draw("same");
      if(mult==4) differentialTopLeg ->Draw("same");
      if(mult==3) differentialTopLeg2->Draw("same");
      ++canvasNumber;
    }

    // ---
    //    do the printing for the legends
    // ---
    // a) legend event yield legend
    MyCanvas[canvasNumber]->cd(0);
    MyCanvas[canvasNumber]->SetTitle("legendEventYield");
    yieldLeg->Draw("");
    ++canvasNumber;
    // b) legend diff xSec l+jets
    MyCanvas[canvasNumber]->cd(0);
    MyCanvas[canvasNumber]->SetTitle("legendDiffXSec");
    lJetsXSecLeg->Draw("");
    ++canvasNumber;
    // c) legend diff norm xSec l+jets
    MyCanvas[canvasNumber]->cd(0);
    MyCanvas[canvasNumber]->SetTitle("legendDiffNormXSec");
    lJetsXSecLegNorm->Draw("");
    ++canvasNumber;
    // d) legend event composition part 1
    MyCanvas[canvasNumber]->cd(0);
    MyCanvas[canvasNumber]->SetTitle("legendEventCompositionPart1");
    eventCompositionPart1->Draw("");
    ++canvasNumber;
    // e) legend event composition part 2
    MyCanvas[canvasNumber]->cd(0);
    MyCanvas[canvasNumber]->SetTitle("legendEventCompositionPart2");
    eventCompositionPart2->Draw("");
    ++canvasNumber;
    // f) legend diff xSec l+jets part 1
    MyCanvas[canvasNumber]->cd(0);
    MyCanvas[canvasNumber]->SetTitle("legendDiffXSecPart1");
    lJetsXSecLegPart1->Draw("");
    ++canvasNumber;
    // g) legend diff xSec l+jets part 2
    MyCanvas[canvasNumber]->cd(0);
    MyCanvas[canvasNumber]->SetTitle("legendDiffXSecPart2");
    lJetsXSecLegPart2->Draw("");
    ++canvasNumber;

    // ---
    // saving
    // ---
    if(save){   
      // ps
      MyCanvas[0]->Print(saveTo+"diffX7TeV"+lum2+"nbAllJetMultiplicities"+log+".pdf(", "pdf");
      for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
	MyCanvas[idx]->Print(saveTo+"diffX7TeV"+lum2+"nbAllJetMultiplicities"+log+".pdf", "pdf");   
      }
      MyCanvas[MyCanvas.size()-1]->Print(saveTo+"diffX7TeV"+lum2+"nbAllJetMultiplicities"+log+".pdf)", "pdf");
    
      // png
      for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
	MyCanvas[idx]->Print(saveTo+(TString)(MyCanvas[idx]->GetTitle())+".png");      
      }
    }
  }
}


void canvasStyle(TCanvas& canv){
  canv.SetFillStyle   ( 4000 );
  canv.SetLeftMargin  ( 0.20 );
  canv.SetRightMargin ( 0.05 );
  canv.SetBottomMargin( 0.15 );
  canv.SetTopMargin   ( 0.05 );
}

void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin, float yMax, float yTitleSize, float yTitleOffset, float xLabelSize){
  hist.SetTitle("");
  hist.GetXaxis()->SetTitle(titleX);
  //hist.GetXaxis()->CenterTitle();
  hist.GetXaxis()->SetTitleSize  ( 0.05);
  hist.GetXaxis()->SetTitleColor (    1);
  hist.GetXaxis()->SetTitleOffset(  1.1);
  hist.GetXaxis()->SetTitleFont  (   62);
  hist.GetXaxis()->SetLabelSize  ( xLabelSize);
  hist.GetXaxis()->SetLabelFont  (   62);
  hist.GetXaxis()->SetNdivisions (  505);
  hist.GetYaxis()->SetTitle(titleY);
  hist.GetYaxis()->SetTitleSize  ( yTitleSize );
  hist.GetYaxis()->SetTitleColor (    1);
  hist.GetYaxis()->SetTitleOffset(yTitleOffset);
  hist.GetYaxis()->SetTitleFont  (   62);
  hist.GetYaxis()->SetLabelSize  ( 0.05);
  hist.GetYaxis()->SetLabelFont  (   62);
  //hist.GetYaxis()->CenterTitle   ( true);
  if(yMin!=-123) hist.SetMinimum(yMin);
  if(yMax!=-123) hist.SetMaximum(yMax);
}

template <class T>
void writeToFile(T output, TString file, bool append){
  // introduce function to write in file
  // a) write into file
  if(!append){
    std::ofstream fout(file);
    fout << output << std::endl;
    fout.close();
  }
  // b) write to the end of the file  
  if(append){
    std::ofstream fapp(file, ios::app);
    fapp << output << std::endl;;
    fapp.close();
  }
 }

int roundToInt(double value, bool roundDown){
  int result=0;
  // take care of negative numbers
  if(value<0){
    std::cout << "no negative numbers allowed in roundToInt" << std::endl;
    return 0;
  }
  // get [value]
  for(int x=0; value>x; ++x){
    result=x;
  }
  // see if rest is > 0.5
  if(roundDown==false&&(value-result) >=0.5) return (result+1);
  return result;
}

TString getTStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return (TString)result;
}

TString jetLabel(TString input){
  TString label="";
  if(input=="Njets1") label="N(jets) #geq 1";
  if(input=="Njets2") label="N(jets) #geq 2";
  if(input=="Njets3") label="N(jets) #geq 3";
  if(input=="Njets4") label="N(jets) #geq 4";
  if(input=="Njets4Btag") label="N(jets) #geq 4, N(bTags) #geq 1";
  if(input=="Njets3Btag") label="N(jets) #geq 3, N(bTags) #geq 1";
  return label;
}

TString samples(int sampleEnum){
  TString output="";
  if(sampleEnum==kSig  ) output ="a) ttbar signal";
  if(sampleEnum==kBkg  ) output ="b) ttbar background";
  if(sampleEnum==kWjets) output ="c) W+jets";
  if(sampleEnum==kZjets) output ="d) Z+jets";
  if(sampleEnum==kDiBos) output ="d) DiBoson";
  if(sampleEnum==kQCD  ) output ="e) QCD";
  if(sampleEnum==kData ) output ="f) Data";
  if(sampleEnum==kSToptW)output ="g) single top tW";
  if(sampleEnum==kSTops) output ="h) single top s";
  if(sampleEnum==kSTopt) output ="i) single top t";
  return output;
}

TH1F* divideByBinwidth(TH1F* histo, bool calculateError){
  // divide entries in every bin by its binwidth
  // careful: not done for underflow/overflow
  TH1F* result = (TH1F*)histo->Clone();
  for(int i=1; i<= histo->GetNbinsX(); i++){
    double error = (double)(histo->GetBinError(i)) / (double)(histo->GetBinWidth(i));
    result->SetBinContent(i, ( (double)(histo->GetBinContent(i))/(double)(histo->GetBinWidth(i)) )  );
    if(calculateError) result->SetBinError(i, error);
  }
  return result;
 }

double getABCDNumbers( TString njets, bool loadValues, TString file){
  // get N(QCD) from ABCD estimation 
  // if loaded from file: be sure the lines are the wright ones!
  double result = 0;
  if(loadValues){
    if(njets=="Njets1") result= readLineFromFile(8 , file);
    if(njets=="Njets2") result= readLineFromFile(9 , file);
    if(njets=="Njets3") result= readLineFromFile(10, file);
    if(njets=="Njets4") result= readLineFromFile(11, file);
  }
  else{
    if(njets=="Njets1") result= 0;
    if(njets=="Njets2") result= 0;
    if(njets=="Njets3") result= 0;
    if(njets=="Njets4") result= 0;
  }
  std::cout << std::endl << std::endl << "N(QCD) from ABCD for " << jetLabel(njets) << ": " << result;
  return result;
}

double getMCEffiencies(TString variable, int bin, int njets, bool loadValues, bool useNLO, TString JES, TString jetTyp, double scaleFactor, TString putSysOn)
{
  // get MC based effiencies for differential plots -> differntial (normalized) cross section
  // if loaded from file: be sure the lines are the wright ones!
  double result =-1;  
  if(!loadValues){
      std::cout << "no effiency correction will be done!" << std::endl;
      return 1.0;
  }
  // consider systematic variations -> read from .txt with different name and other line
  TString file ="crossSectionCalculation";
  if(useNLO      ) file+="NLO";
  file+=JES;
  file+=putSysOn;
  file+=jetTyp;
  file+=".txt";

  int systematic=0;
  if((useNLO)||(JES!="")) systematic=11;

  // print out but only for first bin of every histo
  if((variable=="pt"&&bin==2)||(variable=="eta"&&bin==1)||(variable=="phi"&&bin==0)){
    // a) without btag
      if(njets<4) std::cout << "eff(" << variable << ", N(jets)>=" << njets+1 << ")" << std::endl;
      // b) with btag
      else{
	if(njets==4) std::cout << "eff(" << variable << ", N(jets)>=4 & btags>=1" << ")" << std::endl; 
	if(njets==5) std::cout << "eff(" << variable << ", N(jets)>=3 & btags>=1" << ")" << std::endl; 
      }
  }
  if(loadValues){
    // set start line with Njets1 label for (pt, eta, phi)
    int startLine=0;
    if(variable=="pt" ) startLine=12; // pt -1 because: listing starts with second bin
    if(variable=="eta") startLine=56; 
    if(variable=="phi") startLine=88; // phi +1 because: listing starts with underflow bin
    // set # lines between 2 sets of effiencies= #bins(variable)+1 (jetMuliplicityLabel)
    int dist=0;
    if(variable=="pt" ) dist=7;
    if(variable=="eta") dist=5;
    if(variable=="phi") dist=9;
    // get number from file
    result= readLineFromFile(startLine+dist*njets+bin-systematic, file);
  }
  
  std::cout << "  bin " << bin << ": " << setprecision(3) << fixed << result;
  return scaleFactor*result;
}

TString sampleLabel(unsigned int sample){
  TString result;
  if(sample==kSig    ) result="ttbar signal";
  if(sample==kBkg    ) result="ttbar background";
  if(sample==kSToptW ) result="single top tW";
  if(sample==kSTops  ) result="single top s";
  if(sample==kSTopt  ) result="single top t";
  if(sample==kWjets  ) result="W+jets";
  if(sample==kZjets  ) result="Z+jets";
  if(sample==kDiBos  ) result="DiBoson";
  if(sample==kQCD    ) result="QCD";
  if(sample==kData   ) result="data";
  if(sample==kLepJets) result="all l+jets MC";
  if(sample==kAllMC  ) result="all MC";
  if(sample==kABCD   ) result="QCD from ABCD method";
  return result;
}

double getInclusiveMCEff(TString topORlep, int njets, bool loadValues, bool useNLO, TString JES, TString jetTyp, double scaleFactor, TString putSysOn){
  // get MC based effiencies for inclusive plots -> cross sections
  // if loaded from file: be sure the lines are the wright ones!
  double result =-1;  
  if(!loadValues){
    std::cout << "no efficiency correction will be done!" << std::endl;
    return 1.0;
  }
  // check input
  if((topORlep!="lep")&&(topORlep!="top")){
    std::cout << "incorrect input argument - no efficiency correction will be done!" << std::endl;
    return 1.0;  
  }
  // consider systematic variations -> read from .txt with different name and other line
  TString file ="crossSectionCalculation";
  if(useNLO      ) file+="NLO";
  file+=JES;
  file+=putSysOn;
  file+=jetTyp;
  file+=".txt";

  int systematic=0;
  if((useNLO)||(JES!="")) systematic=11;

  // print out but only for first bin of every histo
  TString label="top";
  if(topORlep=="lep") label="lepton+jets";
  // a) without btag
  if(njets<=4) std::cout << std::endl << "eff(" << label << ", N(jets)>=" << njets << ") :";
  // b) with btag
  else{
    if(njets==5) std::cout << std::endl << "eff(" << label << ", N(jets)>=4 & btags>=1" << ") :"; 
    if(njets==6) std::cout << std::endl << "eff(" << label << ", N(jets)>=3 & btags>=1" << ") :"; 
  }
  if(loadValues){
    // set start line with label for Njets1 (l+jets)
    int startLine = 141;
    // distance to top numbers
    int jumpToTop = 7;
    // get number from file
    if(topORlep=="lep") result= readLineFromFile(startLine+njets-systematic,           file);
    if(topORlep=="top") result= readLineFromFile(startLine+njets-systematic+jumpToTop, file);
  }
  std::cout << setprecision(3) << fixed << result;
  return scaleFactor*result;
}

void DrawLabel(TString text, const double x1, const double y1, const double x2, const double y2, double textSize){
  TPaveLabel *label = new TPaveLabel(x1, y1, x2, y2, text, "br NDC");
  label->SetFillStyle(0);
  label->SetBorderSize(0);
  label->SetTextSize(textSize);
  label->SetTextAlign(12);
  label->Draw("same");
}
 
void scaleByLumi(TH1F* histo, double lumi){
  // for each bin N'=N/L, sN'=sN/L
  for(int bin=0; bin<=histo->GetNbinsX()+1; ++bin){
    histo->SetBinContent(bin, histo->GetBinContent(bin)/lumi);
    histo->SetBinError  (bin, histo->GetBinError  (bin)/lumi);
  }
}

TString getTStringFromDouble(double d){
  int roundedInt = roundToInt(d, true);
  TString number = getTStringFromInt(roundedInt);
  int decimal1   = roundToInt((d-(double)roundedInt)*10);
  TString dec1    = getTStringFromInt(decimal1);
  TString result = number+"."+dec1;
  return result;
}

void drawLine(const double xmin, const double ymin, const double xmax, const double ymax, unsigned int color){
  TLine *line = new TLine();
  line->SetLineWidth(5);
  line->SetLineStyle(1);
  line->SetLineColor(color);
  line->DrawLine(xmin, ymin, xmax, ymax);
}
  //if(finalPlots) systematicError("diffNormXSec"    +variables_[var], mult, *..., variables_[var]);
  //if(finalPlots) systematicError("differentialXSec"+variables_[var], mult, *..., variables_[var]);
  //if(finalPlots) systematicError("ljetsXSec"                       , 6   , *..., "Njets"        );
  //if(finalPlots) systematicError("topXSec"                         , 8   , *..., "1");
  //if(finalPlots) systematicError("topXSec2"                        , 8   , *..., "2");
  //if(finalPlots) systematicError("topXSecInclusive1"               , 8   , *..., "1");
  //if(finalPlots) systematicError("topXSecInclusive2"               , 8   , *..., "2");
  //if(finalPlots) systematicError("differentialTopEta"              , 7   , *..., "eta");
  //if(finalPlots) systematicError("differentialTopPt"               , 7   , *..., "pt" );
  
void systematicError(const TString plot, const int jetMultiplicity, TH1& histo, const TString variable, TString up, TString down){
  // ---
  //    determine systematic errors using the output when doing systematic variations
  // ---
  // the following variations are considered: JES +/- 10%, efficiencies +/- 5%, 
  // ttbar MC-model( MG / NLO ), QCD BKG estimation: +/- 10%, luminosity: +/- 10%
  // the calculation is based on the values saved within the .txt files 
  //-----------------------------------------------------------------------------
  // create jet multiplicity indicator
  std::vector<TString> Njets_;
  TString jets[ 9 ] = { ", Njets1", ", Njets2", ", Njets3", ", Njets4", ", Njets4Btag", ", Njets3Btag", " [Njets]", "", ""};
  Njets_.insert( Njets_.begin(), jets, jets + 9 );
  // print out information about the effected quantity
  std::cout << std::endl << "systematic errors for "+plot;
  std::cout << Njets_[jetMultiplicity]+":" << std::endl;
  // get internal copy of histos
  double sysError=0;
  TH1F*sysHisto=(TH1F*)histo.Clone();
  sysHisto->SetMarkerSize(0.1);
  sysHisto->DrawClone("p e1 X0 same");
  // get line where value is saved
  int line=2;
  // get firstBin, lastBin and binRange(needed to skip between different jet multiplicities)
  int firstBin=1;
  int lastBin=6; 
  if(variable=="pt" ) firstBin=2;
  if(variable=="eta") lastBin=4;
  if(variable=="Njets"){
    firstBin=1;
    lastBin=4;
  }
  if(variable=="1") firstBin=lastBin=1;
  if(variable=="2") firstBin=lastBin=2;
  std::cout << "bin range: ( " << firstBin << " , " << lastBin << " )" << std::endl;
  int binRange=lastBin-firstBin+2;
  // consider chosen jet multiplicity
  if(jetMultiplicity<=5) line +=jetMultiplicity*binRange;
  // calculation for each bin
  int count=-1;
  for(int bin=firstBin; bin<=lastBin; ++bin){
    ++count;
    if((variable=="Njets")&&(bin>firstBin)) ++count;
    std::cout << std::endl << "bin " << bin << " (line " << line+count << " in file ./systematicVariations/"+plot+"...)" << std::endl;
    // load values for all variations                
    double std        = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdSampleWeightStd.txt" );
    double lumiUp     = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiUpEffStdSampleWeightStd.txt"      );
    double lumiDown   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiDownEffStdSampleWeightStd.txt"    );
    double MG         = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdSampleWeightStd.txt" );
    double JESUp      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMC"+up+"LumiNominalEffStdSampleWeightStd.txt");
    double JESDown    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMC"+down+"LumiNominalEffStdSampleWeightStd.txt");
    double JERUp      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCJERupLumiNominalEffStdSampleWeightStd.txt");
    double JERDown    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCJERdownLumiNominalEffStdSampleWeightStd.txt");
    double EffUp      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffUpSampleWeightStd.txt"  );
    double EffDown    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffDownSampleWeightStd.txt");
    double QCDUp      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdQCDestimationUp.txt"  );
    double QCDDown    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdQCDestimationDown.txt");
    double WUp        = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdWjetsEstimationUp.txt"  );
    double WDown      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdWjetsEstimationDown.txt");
    double PileUp     = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCPileUpLumiNominalEffStdSampleWeightStd.txt");
    double ScaleUpV   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCScaleUpVonlyLumiNominalEffStdSampleWeightStd.txt");
    double ScaleUpT   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCScaleUpTTonlyLumiNominalEffStdSampleWeightStd.txt");
    double ScaleDownV = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCScaleDownVonlyLumiNominalEffStdSampleWeightStd.txt");
    double ScaleDownT = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCScaleDownTTonlyLumiNominalEffStdSampleWeightStd.txt");
    double MatchUpV   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCMatchUpVonlyLumiNominalEffStdSampleWeightStd.txt");
    double MatchUpT   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCMatchUpTTonlyLumiNominalEffStdSampleWeightStd.txt");
    double MatchDownV = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCMatchDownVonlyLumiNominalEffStdSampleWeightStd.txt");
    double MatchDownT = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCMatchDownTTonlyLumiNominalEffStdSampleWeightStd.txt");
    double ISRFSRUpT  = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCISRFSRupTTonlyLumiNominalEffStdSampleWeightStd.txt");
    double ISRFSRDownT= readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCISRFSRdownTTonlyLumiNominalEffStdSampleWeightStd.txt");
    double sTopUp     = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdsTopEstimationUp.txt"  );
    double sTopDown   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdsTopEstimationDown.txt");
    double DiBosUp    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdDiBosEstimationUp.txt"  );
    double DiBosDown  = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdDiBosEstimationDown.txt");
    double ZjetsUp    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdZjetsEstimationUp.txt"  );
    double ZjetsDown  = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdZjetsEstimationDown.txt");
    // calculate and print out all systematic errors
    double JESError  = ( std::abs(JESUp-std ) + std::abs(JESDown-std ) ) / 2.0;
    std::cout << "JES: +/- " << setprecision(3) << fixed << "(|"<< JESUp << " - " << std << "|+|"<< JESDown << " - " << std << "|) / 2 = "<< JESError << " = " << 100*JESError/std << "%" << std::endl;
    double JERError  = ( std::abs(JERUp-std ) + std::abs(JERDown-std ) ) / 2.0;
    std::cout << "JER: +/- " << setprecision(3) << fixed << "(|"<< JERUp << " - " << std << "|+|"<< JERDown << " - " << std << "|) / 2 = "<< JERError << " = " << 100*JERError/std << "%" << std::endl;
    double LumiError = ( std::abs(lumiUp-std) + std::abs(lumiDown-std) ) / 2.0;
    std::cout << "lumi: +/- " << setprecision(3) << fixed << "(|"<< lumiUp << " - " << std << "|+|"<< lumiDown << " - " << std << "|) / 2 = " << LumiError << " = " << 100*LumiError/std << "%" << std::endl;
    double EffError  = ( std::abs(EffUp-std ) + std::abs(EffDown-std ) ) / 2.0;
    std::cout << "SF: +/- " << setprecision(3) << fixed << "(|"<< EffUp << " - " << std << "|+|"<< EffDown << " - " << std << "|) / 2 = "<< EffError << " = " << 100*EffError/std << "%" << std::endl;
    double TopMCError= std::abs(MG-std);
    std::cout << "TopMC: +/- " << setprecision(3) << fixed << "|" << MG << "-" << std << "| = " << TopMCError << " = " << 100*TopMCError/std << "%" << std::endl;
    double QCDError=   ( std::abs(QCDUp-std ) + std::abs(QCDDown-std ) ) / 2.0;
    std::cout << "QCDestimation: +/- " << setprecision(3) << fixed << "(|"<< QCDUp << " - " << std << "|+|"<< QCDDown << " - " << std << "|) / 2 = " << QCDError << " = " << 100*QCDError/std << "%" << std::endl;
    double WError=   ( std::abs(WUp-std ) + std::abs(WDown-std ) ) / 2.0;
    std::cout << "top estimate (in W calc): +/- " << setprecision(3) << fixed << "(|"<< WUp << " - " << std << "|+|"<< WDown << " - " << std << "|) / 2 = " << WError << " = " << 100*WError/std << "%" << std::endl;
    double sTopError=   ( std::abs(sTopUp-std ) + std::abs(sTopDown-std ) ) / 2.0;
    std::cout << "single top estimation: +/- " << setprecision(3) << fixed << "(|"<< sTopUp << " - " << std << "|+|"<< sTopDown << " - " << std << "|) / 2 = " << sTopError << " = " << 100*sTopError/std << "%" << std::endl;
    double DiBosError=   ( std::abs(DiBosUp-std ) + std::abs(DiBosDown-std ) ) / 2.0;
    std::cout << "DiBoson estimation: +/- " << setprecision(3) << fixed << "(|"<< DiBosUp << " - " << std << "|+|"<< DiBosDown << " - " << std << "|) / 2 = " << DiBosError << " = " << 100*DiBosError/std << "%" << std::endl;
    double ZjetsError=   ( std::abs(ZjetsUp-std ) + std::abs(ZjetsDown-std ) ) / 2.0;
    std::cout << "Z+jets estimation: +/- " << setprecision(3) << fixed << "(|"<< ZjetsUp << " - " << std << "|+|"<< ZjetsDown << " - " << std << "|) / 2 = " << ZjetsError << " = " << 100*ZjetsError/std << "%" << std::endl;
    double PileUpError =  std::abs(PileUp-std);
    std::cout << "PileUp: +/- " << setprecision(3) << fixed << "|" << PileUp << "-" << std << "| = " << PileUpError << " = " << 100*PileUpError/std << "%" << std::endl;
    double ScaleVError=   ( std::abs(ScaleUpV-std ) + std::abs(ScaleDownV-std ) ) / 2.0;
    std::cout << "Scale W/Z: +/- " << setprecision(3) << fixed << "(|"<< ScaleUpV << " - " << std << "|+|"<< ScaleDownV << " - " << std << "|) / 2 = " << ScaleVError << " = " << 100*ScaleVError/std << "%" << std::endl;
    double ScaleTError=   ( std::abs(ScaleUpT-std ) + std::abs(ScaleDownT-std ) ) / 2.0;
    std::cout << "Scale Top: +/- " << setprecision(3) << fixed << "(|"<< ScaleUpT << " - " << std << "|+|"<< ScaleDownT << " - " << std << "|) / 2 = " << ScaleTError << " = " << 100*ScaleTError/std << "%" << std::endl;
    double ScaleError= std::sqrt( ScaleVError*ScaleVError + ScaleTError*ScaleTError );
    std::cout << "Scale: +/- " << setprecision(3) << fixed << "sqrt("<< ScaleVError << "^2 + "<< ScaleTError << "^2) = " << ScaleError << " = " << 100*ScaleError/std << "%" << std::endl;
    double MatchVError=   ( std::abs(MatchUpV-std ) + std::abs(MatchDownV-std ) ) / 2.0;
    std::cout << "Match W/Z: +/- " << setprecision(3) << fixed << "(|"<< MatchUpV << " - " << std << "|+|"<< MatchDownV << " - " << std << "|) / 2 = " << MatchVError << " = " << 100*MatchVError/std << "%" << std::endl;
    double MatchTError=   ( std::abs(MatchUpT-std ) + std::abs(MatchDownT-std ) ) / 2.0;
    std::cout << "Match Top: +/- " << setprecision(3) << fixed << "(|"<< MatchUpT << " - " << std << "|+|"<< MatchDownT << " - " << std << "|) / 2 = " << MatchTError << " = " << 100*MatchTError/std << "%" << std::endl;
    double MatchError= std::sqrt( MatchVError*MatchVError + MatchTError*MatchTError );
    std::cout << "Match: +/- " << setprecision(3) << fixed << "sqrt("<< MatchVError << "^2 + "<< MatchTError << "^2) = " << MatchError << " = " << 100*MatchError/std << "%" << std::endl;
    double ISRFSRError=   ( std::abs(ISRFSRUpT-std ) + std::abs(ISRFSRDownT-std ) ) / 2.0;
    std::cout << "ISR/FSR Top: +/- " << setprecision(3) << fixed << "(|"<< ISRFSRUpT << " - " << std << "|+|"<< ISRFSRDownT << " - " << std << "|) / 2 = " << ISRFSRError << " = " << 100*ISRFSRError/std << "%" << std::endl;
    // calculate the combined systematic error
    sysError=sqrt(JESError*JESError+JERError*JERError+LumiError*LumiError+TopMCError*TopMCError+EffError*EffError+QCDError*QCDError+WError*WError+sTopError*sTopError+DiBosError*DiBosError+ZjetsError*ZjetsError+PileUpError*PileUpError+ScaleError*ScaleError+MatchError*MatchError+ISRFSRError*ISRFSRError);
    //sysError=sqrt(JESError*JESError+TopMCError*TopMCError+EffError*EffError+QCDError*QCDError+WError*WError);
    std::cout << "total systematic error: +/- " << setprecision(3) << fixed << sysError << " = " << 100*sysError/std << "%" << std::endl;
    // combine systematic and statistic error and Draw combined error
    double statError = sysHisto->GetBinError(bin);
    double combinedError = sqrt(statError*statError+sysError*sysError);
    std::cout << "combined error: sqrt( " << setprecision(3) << fixed << statError;
    std::cout << "^2 + "<< setprecision(3) << fixed << sysError << "^2 ) = ";
    std::cout << setprecision(3) << fixed << combinedError << " = " << 100*combinedError/std << "%" << std::endl;
    sysHisto->SetBinError(bin, combinedError);
  }
  sysHisto->DrawClone("p e X0 same");
}
  
TH1F* systematicHisto(const TString plot, const int jetMultiplicity, TH1& histo, const TString variable, TString up, TString down){
  // ---
  //    determine systematic errors using the output when doing systematic variations
  // ---
  // the following variations are considered: JES +/- 10%, efficiencies +/- 5%, 
  // ttbar MC-model( MG / NLO ), QCD BKG estimation: +/- 10%, luminosity: +/- 10%
  // the calculation is based on the values saved within the .txt files 
  //-----------------------------------------------------------------------------
  // create jet multiplicity indicator
  std::vector<TString> Njets_;
  TString jets[ 9 ] = { ", Njets1", ", Njets2", ", Njets3", ", Njets4", ", Njets4Btag", ", Njets3Btag", " [Njets]", "", ""};
  Njets_.insert( Njets_.begin(), jets, jets + 9 );
  // get internal copy of histos
  double sysError=0;
  TH1F* sysHisto=(TH1F*)histo.Clone();
  // get line where value is saved
  int line=2;
  // get firstBin, lastBin and binRange(needed to skip between different jet multiplicities)
  int firstBin=1;
  int lastBin=6; 
  if(variable=="pt" ) firstBin=2;
  if(variable=="eta") lastBin=4;
  if(variable=="Njets"){
    firstBin=1;
    lastBin=4;
  }
  if(variable=="1") firstBin=lastBin=1;
  if(variable=="2") firstBin=lastBin=2;
  int binRange=lastBin-firstBin+2;
  // consider chosen jet multiplicity
  if(jetMultiplicity<=5) line +=jetMultiplicity*binRange;
  // calculation for each bin
  int count=-1;
  for(int bin=firstBin; bin<=lastBin; ++bin){
    ++count;
    if((variable=="Njets")&&(bin>firstBin)) ++count;
    // load values for all variations                
    double std        = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdSampleWeightStd.txt" );
    double lumiUp     = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiUpEffStdSampleWeightStd.txt"      );
    double lumiDown   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiDownEffStdSampleWeightStd.txt"    );
    double MG         = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdSampleWeightStd.txt" );
    double JESUp      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMC"+up+"LumiNominalEffStdSampleWeightStd.txt");
    double JESDown    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMC"+down+"LumiNominalEffStdSampleWeightStd.txt");
    double JERUp      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCJERupLumiNominalEffStdSampleWeightStd.txt");
    double JERDown    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCJERdownLumiNominalEffStdSampleWeightStd.txt");
    double EffUp      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffUpSampleWeightStd.txt"  );
    double EffDown    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffDownSampleWeightStd.txt");
    double QCDUp      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdQCDestimationUp.txt"  );
    double QCDDown    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdQCDestimationDown.txt");
    double WUp        = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdWjetsEstimationUp.txt"  );
    double WDown      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdWjetsEstimationDown.txt");
    double PileUp     = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCPileUpLumiNominalEffStdSampleWeightStd.txt");
    double ScaleUpV   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCScaleUpVonlyLumiNominalEffStdSampleWeightStd.txt");
    double ScaleUpT   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCScaleUpTTonlyLumiNominalEffStdSampleWeightStd.txt");
    double ScaleDownV = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCScaleDownVonlyLumiNominalEffStdSampleWeightStd.txt");
    double ScaleDownT = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCScaleDownTTonlyLumiNominalEffStdSampleWeightStd.txt");
    double MatchUpV   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCMatchUpVonlyLumiNominalEffStdSampleWeightStd.txt");
    double MatchUpT   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCMatchUpTTonlyLumiNominalEffStdSampleWeightStd.txt");
    double MatchDownV = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCMatchDownVonlyLumiNominalEffStdSampleWeightStd.txt");
    double MatchDownT = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCMatchDownTTonlyLumiNominalEffStdSampleWeightStd.txt");
    double ISRFSRUpT  = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCISRFSRupTTonlyLumiNominalEffStdSampleWeightStd.txt");
    double ISRFSRDownT= readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCISRFSRdownTTonlyLumiNominalEffStdSampleWeightStd.txt");
    double sTopUp     = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdsTopEstimationUp.txt"  );
    double sTopDown   = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdsTopEstimationDown.txt");
    double DiBosUp    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdDiBosEstimationUp.txt"  );
    double DiBosDown  = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdDiBosEstimationDown.txt");
    double ZjetsUp    = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdZjetsEstimationUp.txt"  );
    double ZjetsDown  = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdZjetsEstimationDown.txt");
    // calculate and print out all systematic errors
    double JESError  = ( std::abs(JESUp-std ) + std::abs(JESDown-std ) ) / 2.0;
    double JERError  = ( std::abs(JERUp-std ) + std::abs(JERDown-std ) ) / 2.0;
    double LumiError = ( std::abs(lumiUp-std) + std::abs(lumiDown-std) ) / 2.0;
    double EffError  = ( std::abs(EffUp-std ) + std::abs(EffDown-std ) ) / 2.0;
    double TopMCError= std::abs(MG-std);
    double QCDError=   ( std::abs(QCDUp-std ) + std::abs(QCDDown-std ) ) / 2.0;
    double WError=   ( std::abs(WUp-std ) + std::abs(WDown-std ) ) / 2.0;
    double sTopError=   ( std::abs(sTopUp-std ) + std::abs(sTopDown-std ) ) / 2.0;
    double DiBosError=   ( std::abs(DiBosUp-std ) + std::abs(DiBosDown-std ) ) / 2.0;
    double ZjetsError=   ( std::abs(ZjetsUp-std ) + std::abs(ZjetsDown-std ) ) / 2.0;
    double PileUpError =  std::abs(PileUp-std);
    double ScaleVError=   ( std::abs(ScaleUpV-std ) + std::abs(ScaleDownV-std ) ) / 2.0;
    double ScaleTError=   ( std::abs(ScaleUpT-std ) + std::abs(ScaleDownT-std ) ) / 2.0;
    double ScaleError= std::sqrt( ScaleVError*ScaleVError + ScaleTError*ScaleTError );
    double MatchVError=   ( std::abs(MatchUpV-std ) + std::abs(MatchDownV-std ) ) / 2.0;
    double MatchTError=   ( std::abs(MatchUpT-std ) + std::abs(MatchDownT-std ) ) / 2.0;
    double MatchError= std::sqrt( MatchVError*MatchVError + MatchTError*MatchTError );
    double ISRFSRError=   ( std::abs(ISRFSRUpT-std ) + std::abs(ISRFSRDownT-std ) ) / 2.0;
    // calculate the combined systematic error
    sysError=sqrt(JESError*JESError+JERError*JERError+LumiError*LumiError+TopMCError*TopMCError+EffError*EffError+QCDError*QCDError+WError*WError+sTopError*sTopError+DiBosError*DiBosError+ZjetsError*ZjetsError+PileUpError*PileUpError+ScaleError*ScaleError+MatchError*MatchError+ISRFSRError*ISRFSRError);
    // combine systematic and statistic error and Draw combined error
    double statError = sysHisto->GetBinError(bin);
    double combinedError = sqrt(statError*statError+sysError*sysError);
    sysHisto->SetBinError(bin, combinedError);
  }
  return sysHisto;
}
    
double systematicError2(const TString plot, TH1& histo, int usedBin, TString up, TString down){
  // ---
  //    determine systematic errors using the output when doing systematic variations
  // ---
  // the following variations are considered: JES +/- 10%, efficiencies +/- 5%, 
  // ttbar MC-model( MG / NLO ), QCD BKG estimation: +/- 10%, luminosity: +/- 10%
  // the calculation is based on the values saved within the .txt files 
  //-----------------------------------------------------------------------------
  // print out information about the effected quantity
  std::cout << std::endl << "systematic errors for "+plot << ":" << std::endl;
  std::cout << "bin range: ( " << usedBin << " , " << usedBin << " )" << std::endl;
  std::cout << std::endl << "bin " << usedBin << " (line " << 2 << " in file ./systematicVariations/"+plot+"...)" << std::endl;
  // load values for all variations                
  double std        = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdSampleWeightStd.txt" );
  double lumiUp     = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiUpEffStdSampleWeightStd.txt"      );
  double lumiDown   = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiDownEffStdSampleWeightStd.txt"    );
  double MG         = readLineFromFile(2, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdSampleWeightStd.txt" );
  double JESUp      = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMC"+up+"LumiNominalEffStdSampleWeightStd.txt");
  double JESDown    = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMC"+down+"LumiNominalEffStdSampleWeightStd.txt");
  double JERUp      = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCJERupLumiNominalEffStdSampleWeightStd.txt");
  double JERDown    = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCJERdownLumiNominalEffStdSampleWeightStd.txt");
  double EffUp      = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffUpSampleWeightStd.txt"  );
  double EffDown    = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffDownSampleWeightStd.txt");
  double QCDUp      = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdQCDestimationUp.txt"  );
  double QCDDown    = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdQCDestimationDown.txt");
  double WUp        = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdWjetsEstimationUp.txt"  );
  double WDown      = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdWjetsEstimationDown.txt");
  double PileUp     = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCPileUpLumiNominalEffStdSampleWeightStd.txt");
  double ScaleUpV   = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCScaleUpVonlyLumiNominalEffStdSampleWeightStd.txt");
  double ScaleUpT   = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCScaleUpTTonlyLumiNominalEffStdSampleWeightStd.txt");
  double ScaleDownV = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCScaleDownVonlyLumiNominalEffStdSampleWeightStd.txt");
  double ScaleDownT = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCScaleDownTTonlyLumiNominalEffStdSampleWeightStd.txt");
  double MatchUpV   = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCMatchUpVonlyLumiNominalEffStdSampleWeightStd.txt");
  double MatchUpT   = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCMatchUpTTonlyLumiNominalEffStdSampleWeightStd.txt");
  double MatchDownV = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCMatchDownVonlyLumiNominalEffStdSampleWeightStd.txt");
  double MatchDownT = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCMatchDownTTonlyLumiNominalEffStdSampleWeightStd.txt");
  double ISRFSRUpT  = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCISRFSRupTTonlyLumiNominalEffStdSampleWeightStd.txt");
  double ISRFSRDownT= readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCISRFSRdownTTonlyLumiNominalEffStdSampleWeightStd.txt");
  double sTopUp     = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdsTopEstimationUp.txt"  );
  double sTopDown   = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdsTopEstimationDown.txt");
  double DiBosUp    = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdDiBosEstimationUp.txt"  );
  double DiBosDown  = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdDiBosEstimationDown.txt");
  double ZjetsUp    = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdZjetsEstimationUp.txt"  );
  double ZjetsDown  = readLineFromFile(2, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdZjetsEstimationDown.txt");
  // calculate and print out all systematic errors
  double JESError  = ( std::abs(JESUp-std ) + std::abs(JESDown-std ) ) / 2.0;
  std::cout << "JES: +/- " << setprecision(3) << fixed << "(|"<< JESUp << " - " << std << "|+|"<< JESDown << " - " << std << "|) / 2 = "<< JESError << " = " << 100*JESError/std << "%" << std::endl;
  double JERError  = ( std::abs(JERUp-std ) + std::abs(JERDown-std ) ) / 2.0;
  std::cout << "JER: +/- " << setprecision(3) << fixed << "(|"<< JERUp << " - " << std << "|+|"<< JERDown << " - " << std << "|) / 2 = "<< JERError << " = " << 100*JERError/std << "%" << std::endl;
  double LumiError = ( std::abs(lumiUp-std) + std::abs(lumiDown-std) ) / 2.0;
  std::cout << "lumi: +/- " << setprecision(3) << fixed << "(|"<< lumiUp << " - " << std << "|+|"<< lumiDown << " - " << std << "|) / 2 = " << LumiError << " = " << 100*LumiError/std << "%" << std::endl;
  double EffError  = ( std::abs(EffUp-std ) + std::abs(EffDown-std ) ) / 2.0;
  std::cout << "SF: +/- " << setprecision(3) << fixed << "(|"<< EffUp << " - " << std << "|+|"<< EffDown << " - " << std << "|) / 2 = "<< EffError << " = " << 100*EffError/std << "%" << std::endl;
  double TopMCError= std::abs(MG-std);
  std::cout << "TopMC: +/- " << setprecision(3) << fixed << "|" << MG << "-" << std << "| = " << TopMCError << " = " << 100*TopMCError/std << "%" << std::endl;
  double QCDError=   ( std::abs(QCDUp-std ) + std::abs(QCDDown-std ) ) / 2.0;
  std::cout << "QCDestimation: +/- " << setprecision(3) << fixed << "(|"<< QCDUp << " - " << std << "|+|"<< QCDDown << " - " << std << "|) / 2 = " << QCDError << " = " << 100*QCDError/std << "%" << std::endl;
  double WError=   ( std::abs(WUp-std ) + std::abs(WDown-std ) ) / 2.0;
  std::cout << "top estimate (in W calc): +/- " << setprecision(3) << fixed << "(|"<< WUp << " - " << std << "|+|"<< WDown << " - " << std << "|) / 2 = " << WError << " = " << 100*WError/std << "%" << std::endl;
  double sTopError=   ( std::abs(sTopUp-std ) + std::abs(sTopDown-std ) ) / 2.0;
  std::cout << "single top estimation: +/- " << setprecision(3) << fixed << "(|"<< sTopUp << " - " << std << "|+|"<< sTopDown << " - " << std << "|) / 2 = " << sTopError << " = " << 100*sTopError/std << "%" << std::endl;
  double DiBosError=   ( std::abs(DiBosUp-std ) + std::abs(DiBosDown-std ) ) / 2.0;
  std::cout << "DiBoson estimation: +/- " << setprecision(3) << fixed << "(|"<< DiBosUp << " - " << std << "|+|"<< DiBosDown << " - " << std << "|) / 2 = " << DiBosError << " = " << 100*DiBosError/std << "%" << std::endl;
  double ZjetsError=   ( std::abs(ZjetsUp-std ) + std::abs(ZjetsDown-std ) ) / 2.0;
  std::cout << "Z+jets estimation: +/- " << setprecision(3) << fixed << "(|"<< ZjetsUp << " - " << std << "|+|"<< ZjetsDown << " - " << std << "|) / 2 = " << ZjetsError << " = " << 100*ZjetsError/std << "%" << std::endl;
  double PileUpError =  std::abs(PileUp-std);
  std::cout << "PileUp: +/- " << setprecision(3) << fixed << "|" << PileUp << "-" << std << "| = " << PileUpError << " = " << 100*PileUpError/std << "%" << std::endl;
  double ScaleVError=   ( std::abs(ScaleUpV-std ) + std::abs(ScaleDownV-std ) ) / 2.0;
  std::cout << "(Scale W/Z: +/- " << setprecision(3) << fixed << "(|"<< ScaleUpV << " - " << std << "|+|"<< ScaleDownV << " - " << std << "|) / 2 = " << ScaleVError << " = " << 100*ScaleVError/std << "%)" << std::endl;
  double ScaleTError=   ( std::abs(ScaleUpT-std ) + std::abs(ScaleDownT-std ) ) / 2.0;
  std::cout << "(Scale Top: +/- " << setprecision(3) << fixed << "(|"<< ScaleUpT << " - " << std << "|+|"<< ScaleDownT << " - " << std << "|) / 2 = " << ScaleTError << " = " << 100*ScaleTError/std << "%)" << std::endl;
  double ScaleError= std::sqrt( ScaleVError*ScaleVError + ScaleTError*ScaleTError );
  std::cout << "Scale: +/- " << setprecision(3) << fixed << "sqrt("<< ScaleVError << "^2 + "<< ScaleTError << "^2) = " << ScaleError << " = " << 100*ScaleError/std << "%" << std::endl;
  double MatchVError=   ( std::abs(MatchUpV-std ) + std::abs(MatchDownV-std ) ) / 2.0;
  std::cout << "(Match W/Z: +/- " << setprecision(3) << fixed << "(|"<< MatchUpV << " - " << std << "|+|"<< MatchDownV << " - " << std << "|) / 2 = " << MatchVError << " = " << 100*MatchVError/std << "%)" << std::endl;
  double MatchTError=   ( std::abs(MatchUpT-std ) + std::abs(MatchDownT-std ) ) / 2.0;
  std::cout << "(Match Top: +/- " << setprecision(3) << fixed << "(|"<< MatchUpT << " - " << std << "|+|"<< MatchDownT << " - " << std << "|) / 2 = " << MatchTError << " = " << 100*MatchTError/std << "%)" << std::endl;
  double MatchError= std::sqrt( MatchVError*MatchVError + MatchTError*MatchTError );
  std::cout << "Match: +/- " << setprecision(3) << fixed << "sqrt("<< MatchVError << "^2 + "<< MatchTError << "^2) = " << MatchError << " = " << 100*MatchError/std << "%" << std::endl;
  double ISRFSRError=   ( std::abs(ISRFSRUpT-std ) + std::abs(ISRFSRDownT-std ) ) / 2.0;
  std::cout << "(ISR/FSR Top: +/- " << setprecision(3) << fixed << "(|"<< ISRFSRUpT << " - " << std << "|+|"<< ISRFSRDownT << " - " << std << "|) / 2 = " << ISRFSRError << " = " << 100*ISRFSRError/std << "%)" << std::endl;
  // calculate the combined systematic error
  double sysError=sqrt(JESError*JESError+JERError*JERError+LumiError*LumiError+TopMCError*TopMCError+EffError*EffError+QCDError*QCDError+WError*WError+sTopError*sTopError+DiBosError*DiBosError+ZjetsError*ZjetsError+PileUpError*PileUpError+ScaleError*ScaleError+MatchError*MatchError+ISRFSRError*ISRFSRError);
  //sysError=sqrt(JESError*JESError+TopMCError*TopMCError+EffError*EffError+QCDError*QCDError+WError*WError);
  std::cout << "total systematic error: +/- " << setprecision(3) << fixed << sysError << " = " << 100*sysError/std << "%" << std::endl;
  // combine systematic and statistic error and Draw combined error
  double statError = histo.GetBinError(usedBin);
  double combinedError = sqrt(statError*statError+sysError*sysError);
  std::cout << "combined error: sqrt( " << setprecision(3) << fixed << statError;
  std::cout << "^2 + "<< setprecision(3) << fixed << sysError << "^2 ) = ";
  std::cout << setprecision(3) << fixed << combinedError << " = " << 100*combinedError/std << "%" << std::endl;
  return combinedError;
}
