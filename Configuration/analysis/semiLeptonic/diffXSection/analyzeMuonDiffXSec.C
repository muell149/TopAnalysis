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

void canvasStyle(TCanvas& canv);
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
template <class T>
void writeToFile(T output, TString file="crossSectionCalculation.txt", bool append=1);
double readLineFromFile(int line, TString file="crossSectionCalculation.txt");
int roundToInt(double value, bool roundDown=false);
TString getTStringFromInt(int i);
TString getTStringFromDouble(double d);
TString jetLabel(TString input);
TString samples(int sampleEnum);
TH1F* divideByBinwidth(TH1F* histo, bool calculateError=true);
double getABCDNumbers( TString njets, bool loadValues);
double getMCEffiencies(TString variable, int bin, int njets, bool loadValues, bool useMG=false, TString JES="");
TString sampleLabel(unsigned int sample);
double getInclusiveMCEff(TString topORlep, int njets, bool loadValues, bool useMG=false, TString JES="");
void DrawLabel(TString text, const double x1, const double y1, const double x2, const double y2);
void scaleByLumi(TH1F* histo, double lumi);
void drawLine(const double xmin, const double ymin, const double xmax, const double ymax, unsigned int color=kBlack);
void systematicError(const TString plot, const int jetMultiplicity, TH1& histo, const TString variabl);

void analyzeMuonDiffXSec(double luminosity = 2880, bool save = true, bool loadValues = true, TString dataFile="./diffXSecFromSignal/data/data0309/analyzeDiffXData_2900nb_residualJC.root", bool useMG=false, TString JES="", double lumiShift=1.0, double EffScaleFactor=1.0, double QCDVariation=1.0, double WjetsVariation=1.0, bool finalPlots=true, bool logartihmicPlots=true)
{ 

  // ---
  //    define settings for systematic variations
  // ---
  TString TopSample = "Nlo";
  TString JESShift  = "";
  TString LuminosityVariation="Nominal";
  TString EffScale = "EffStd";
  TString QCDScale="QCDestimationStd";
  TString WjetsScale="WjetsEstimationStd";
  if(useMG      ) TopSample ="Mad";
  if(JES=="up"  ) JESShift  ="JES11";
  if(JES=="down") JESShift  ="JES09";
  luminosity*=lumiShift;
  if(lumiShift>1.0) LuminosityVariation = "Up";
  if(lumiShift<1.0) LuminosityVariation = "Down";
  if(EffScaleFactor>1.0) EffScale = "EffUp";
  if(EffScaleFactor<1.0) EffScale = "EffDown";
  if(QCDVariation>1.0) QCDScale = "QCDestimationUp";
  if(QCDVariation<1.0) QCDScale = "QCDestimationDown";
  if(WjetsVariation>1.0) WjetsScale = "WjetsEstimationUp";
  if(WjetsVariation<1.0) WjetsScale = "WjetsEstimationDown";

  // ---
  //    main function parameters
  // ---
  // save       : choose whether you want to save every plot as png and all within one ps file
  // loadValues : choose whether you want to load effiency corrections 
  //              and bkg estimation from crossSection.txt file
  // luminosity : choose luminosity [pb] for scaling of event numbers 
  //              lum is derived from this and used for legend as entry
  TString lum  = getTStringFromDouble(luminosity/1000);
  TString lum2 = getTStringFromInt(roundToInt(luminosity));
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/earlyData/crossSection/";
  // useMG      : if true, MAGRAPH instead of MC@NLO sample is used as reco input
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
  TString whichSample = "/spring10Samples/spring10SelV2Sync";
  for(int ienum = 0; ienum<6; ienum++){
    if(ienum==kSig)  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigNloSpring10"+JESShift+".root"   ) );
    if(ienum==kBkg)  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgNloSpring10"+JESShift+".root"   ) );
    if(ienum==kWjets)files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecWjetsMadSpring10"+JESShift+".root" ) );
    if(ienum==kZjets)files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecZjetsMadSpring10"+JESShift+".root" ) );
    if(ienum==kQCD)  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecQCDPythiaSpring10"+JESShift+".root") );
    if(ienum==kData) files_.push_back(new TFile(dataFile                                                                        ) );
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
    // loop samples
    for(unsigned int idx=kSig; idx<=kData; ++idx) {
      // loop pt, eta and phi
      for(unsigned int var=0; var<variables_.size(); ++var){
	// a) reco
	histo_[variables_[var]][idx][Njets_[mult]] = (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/"+variables_[var]);
	// b) gen from MC (top-sig+bkg&Wjets)
	if(mult<4){
	  if(idx==kSig)   histo_[variables_[var]][kGenSig][Njets_[mult]] = (TH1F*)(files_[idx]->Get("analyzeTightMuonCrossSectionGen"+Njets_[mult]+"/"+variables_[var])->Clone());
	  if(idx==kBkg)   histo_[variables_[var]][kGenBkg][Njets_[mult]] = (TH1F*)(files_[idx]->Get("analyzeTightMuonCrossSectionGen"+Njets_[mult]+"/"+variables_[var])->Clone());
	  if(idx==kWjets) histo_[variables_[var]][kGenW  ][Njets_[mult]] = (TH1F*)(files_[idx]->Get("analyzeTightMuonCrossSectionGen"+Njets_[mult]+"/"+variables_[var])->Clone());
	}
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
  // 7 TeV Monte Carlo spring 10 samples
  // (2*ttbar MC@NLO, 2*ttbar MG, W+jets MG, Z+jets MG, QCD PYTHIA) 
  // -----------------------------------
  if(!useMG){
    lumiweight_.push_back(0.000007940958/50.0*luminosity);
    lumiweight_.push_back(0.000007940958/50.0*luminosity);
  }
  else{
    lumiweight_.push_back(0.000005308736/50.0*luminosity);
    lumiweight_.push_back(0.000005308736/50.0*luminosity);
  }  
  lumiweight_.push_back(0.000155498692/50.0*luminosity);
  lumiweight_.push_back(0.000140471057/50.0*luminosity);
  lumiweight_.push_back(0.000910264515/50.0*luminosity);
  
  // ---
  //    lumiweighting for luminosity, add all MC for combined MC (l+jets and with QCD)
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      // loop samples
      for(unsigned int idx=kSig; idx<=kQCD; ++idx) {
	// scale MC samples to same luminosity
	histo_[variables_[var]][idx][Njets_[mult]]->Scale(lumiweight_[idx]);
	// scaling for gen-plots
	if(mult<4){
	  if(idx==kSig  ) histo_[variables_[var]][kGenSig][Njets_[mult]]->Scale(lumiweight_[idx]);
	  if(idx==kBkg  ) histo_[variables_[var]][kGenBkg][Njets_[mult]]->Scale(lumiweight_[idx]);
	  if(idx==kWjets) histo_[variables_[var]][kGenW  ][Njets_[mult]]->Scale(lumiweight_[idx]);
	}
	// create isolated l+jets combined MC plots
	if(idx==kSig) histo_[variables_[var]][kLepJets][Njets_[mult]] = (TH1F*)histo_[variables_[var]][kSig][Njets_[mult]]->Clone();
	if(idx>=kBkg&&idx<=kZjets) histo_[variables_[var]][kLepJets][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][idx][Njets_[mult]]->Clone() );
	// create all-MC plots (including QCD)
	if(idx==kQCD){
	  histo_[variables_[var]][kAllMC][Njets_[mult]] = (TH1F*)histo_[variables_[var]][kLepJets][Njets_[mult]]->Clone();
	  histo_[variables_[var]][kAllMC][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][kQCD][Njets_[mult]]->Clone() );
	}
      }
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
      for(unsigned int idx=kSig; idx<=kData; ++idx) {
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
    // a) get number
    NQCD_ .push_back( getABCDNumbers(Njets_[mult], loadValues)*QCDVariation );
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
      for(unsigned int idx=kSig; idx<=kAllMC; ++idx) {
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
	if(idx!=kSig&&idx<kData) histo_[yield_[var]][idx][Njets_[mult]]->Add( (TH1F*)histo_[yield_[var]][idx-1][Njets_[mult]]->Clone() );
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
      // loop all samples
      for(unsigned int idx=kSig; idx<=kQCD; ++idx){
	std::cout << sampleLabel(idx) << std::endl;
	// a) clone lumiweigthed MC plots
	histo_[composition_[var]][idx][Njets_[mult]] = (TH1F*)histo_[variables_[var]][idx][Njets_[mult]]->Clone();
	// b) calculate event composition for each bin
	// loop bins (no overflow or underflow)
	for(int bin =1; bin<=histo_[variables_[var]][kSig][Njets_[mult]]->GetNbinsX(); ++bin){
	  // start with 2nd bin for pt!
	  if(variables_[var]=="pt"&&bin==1) ++bin;
	  // get entries for actual sample
	  double Nsample = histo_[composition_[var]][idx][Njets_[mult]]->GetBinContent(bin);
	  // get entries from all sample-> loop sample again
	  double NAll    = 0;
	  for(unsigned int sample=kSig; sample<=kQCD; ++sample){
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

  // ---
  //    get efficiencies from MC gen studies
  // ---
  // a) eff. for l+jets bin per bin correction -> differential cross section
  // create container for effiencies
  std::map< TString, std::map <unsigned int, std::map <TString, double> > > efficiency_;
  // example: efficiency_["pt"][(bin)1]["Njets1"]
  // , useMG, JES
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
	if(variables_[var]=="phi"&&bin==1) efficiency_[variables_[var]][0][Njets_[mult]] = getMCEffiencies(variables_[var], 0, mult, loadValues, useMG, JES)*EffScaleFactor;
	efficiency_[variables_[var]][bin][Njets_[mult]] = getMCEffiencies(variables_[var], bin, mult, loadValues, useMG, JES)*EffScaleFactor;
	// get overflow bin for pt and phi
	if((variables_[var]=="pt"||variables_[var]=="phi")&&bin==histo_[variables_[var]][kSig][Njets_[mult]]->GetNbinsX()){
	  efficiency_[variables_[var]][bin+1][Njets_[mult]] = getMCEffiencies(variables_[var], bin+1, mult, loadValues, useMG, JES)*EffScaleFactor;
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
    ljetsInclusiveEff_. push_back( getInclusiveMCEff("lep", mult+1, loadValues, useMG, JES)*EffScaleFactor );
  }
  // c) eff. for top inclusive cross section 
  // N(jets)>=4 corresponds to 4
  // N(jets)>=4 && N(BTags)>=1 corresponds to 5
  std::cout<< std::endl << std::endl << "c1) inclusive top with b-tag";
  double effNjets4Btag = getInclusiveMCEff("top", 5, loadValues, useMG, JES)*EffScaleFactor;
  std::cout<< std::endl << std::endl << "c2) inclusive top without b-tag";
  double effNjets4     = getInclusiveMCEff("top", 4, loadValues, useMG, JES)*EffScaleFactor;

  // d) eff. for differenial top cross sections >=4 jets and btag
  // consider systematic variations -> read from .txt with different name and other line
  TString file ="crossSectionCalculation";
  if(useMG      ) file+="MG";
  if(JES=="up"  ) file+="JES11";
  if(JES=="down") file+="JES09";
  int systematic=0;
  if((useMG)||(JES=="up")||(JES=="down")) systematic=11;
  file+=".txt";
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
  double NWestimate = readLineFromFile(185)*WjetsVariation;
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
  std::vector<TString> ljetsXSec_, ljetsXSecInclusive_, ljetsXSecDiff_;
  TString ljetsXSec[ 3 ] = { "pt l+jets diff norm XSec", "eta l+jets diff norm XSec", "phi l+jets diff norm XSec" };
  ljetsXSec_.insert( ljetsXSec_.begin(), ljetsXSec, ljetsXSec + 3 );
  TString ljetsXSecDiff[ 3 ] = { "pt l+jets diff XSec", "eta l+jets diff XSec", "phi l+jets diff XSec" };
  ljetsXSecDiff_.insert( ljetsXSecDiff_.begin(), ljetsXSecDiff, ljetsXSecDiff + 3 );
  TString ljetsXSecInclusive[ 3 ] = { "pt l+jets inclusive XSec", "eta l+jets inclusive XSec", "phi l+jets inclusive XSec" };
  ljetsXSecInclusive_.insert( ljetsXSecInclusive_.begin(), ljetsXSecInclusive, ljetsXSecInclusive + 3 );
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
	if((idx==kData)&&(mult!=4)&&(mult!=5)) histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Add( histo_[variables_[var]][kABCD][Njets_[mult]], -1.0);
	// b2) subtract Z+jets from MC prediction
	histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Add( histo_[variables_[var]][kZjets][Njets_[mult]], -1.0);
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
	histo_[ljetsXSecInclusive_[var]][idx][Njets_[mult]]= (TH1F*)histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Clone();
	// ii) divide by binwidth (and recalculate errors)
	histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]=divideByBinwidth(histo_[ljetsXSecDiff[var]][idx][Njets_[mult]], true);
	// iii) divide by luminosity
	scaleByLumi(histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], luminosity*0.001);
	// f) normalize to total cross section
	double NAll = histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Integral(0, histo_[ljetsXSec_[var]][idx][Njets_[mult]]->GetNbinsX()+1);
	histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Scale(1/NAll);
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
	    double NQCDBin=0;
	    if((mult!=4)&&(mult!=5)) NQCDBin =histo_[variables_[var]][kABCD][Njets_[mult]]->GetBinContent(bin);
	    // calculate Ni   = (NdataBin-NQCDbin)/ebin corrected entries in bin
	    double Ni= (NdataBin-NQCDBin)/eBin;
	    // calculate Nges = sum_i(Ni) corrected total number of entries
	    double Nges =NAll;
	    // compare #events(total) in histo when applying efficiency corrections for each bin or global efficiency correction 
	    //	  std::cout << "( " << NAll << " , " <<  histo_[variables_[var]][idx][Njets_[mult]]->Integral(0, histo_[variables_[var]][idx][Njets_[mult]]->GetNbinsX()+1)/ljetsInclusiveEff_[mult] << " )" << std::endl;
	    // calculate two expressions needed in complete error
	    double term1 = (Nges - Ni)*sqrt(NdataBin)/eBin;
	    double term2 = 0;
	    for(int bin2=binMin; bin2<=binMax; ++bin2){
	      if(bin2!=bin) term2 += histo_[variables_[var]][idx][Njets_[mult]]->GetBinContent(bin2) / (efficiency_[variables_[var]][bin2][Njets_[mult]]*efficiency_[variables_[var]][bin2][Njets_[mult]]);
	    }
	    // calculate complete error
	    double diffNormError = 1 / ( Nges*Nges*binwidth );
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
	      writeToFile(ljetsXSec_[var]+Njets_[mult], "systematicVariations/diffNormXSec"+variables_[var]+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", append);
	    }
	    writeToFile(histo_[ljetsXSec_[var]][idx][Njets_[mult]]->GetBinContent(bin), "systematicVariations/diffNormXSec"+variables_[var]+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 1);
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
	      writeToFile(ljetsXSecDiff_[var]+Njets_[mult], "systematicVariations/differentialXSec"+variables_[var]+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", append);
	    }
	    writeToFile(histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->GetBinContent(bin), "systematicVariations/differentialXSec"+variables_[var]+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 1);
	  }
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
      histo_[ljetsGen_[var]][kGenSig][Njets_[mult]] = divideByBinwidth((TH1F*)histo_[variables_[var]][kGenSig][Njets_[mult]]->Clone(), true);
      histo_[ljetsGen_[var]][kGenBkg][Njets_[mult]] = divideByBinwidth((TH1F*)histo_[variables_[var]][kGenBkg][Njets_[mult]]->Clone(), true);
      histo_[ljetsGen_[var]][kGenW  ][Njets_[mult]] = divideByBinwidth((TH1F*)histo_[variables_[var]][kGenW  ][Njets_[mult]]->Clone(), true);
      // divide by luminosity
      scaleByLumi(histo_[ljetsGen_[var]][kGenSig][Njets_[mult]], luminosity*0.001);
      scaleByLumi(histo_[ljetsGen_[var]][kGenBkg][Njets_[mult]], luminosity*0.001);
      scaleByLumi(histo_[ljetsGen_[var]][kGenW  ][Njets_[mult]], luminosity*0.001);
      // create stack-plot: ttbar signal, ttbar other, W+jets
      histo_[ljetsGen_[var]][kGenBkg][Njets_[mult]]->Add( histo_[ljetsGen_[var]][kGenSig][Njets_[mult]] );
      histo_[ljetsGen_[var]][kGenW  ][Njets_[mult]]->Add( histo_[ljetsGen_[var]][kGenBkg][Njets_[mult]] );
    }
  }

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
    histo_["pt BG"   ][kData][Njets_[mult]] =    (TH1F*)histo_["pt"][kWjets]["Njets4Btag"]->Clone();
    histo_["pt BG"   ][kData][Njets_[mult]]->Scale(WjetsVariation);
    histo_["pt BG"   ][kData][Njets_[mult]]->Add((TH1F*)histo_["pt"][kZjets]["Njets4Btag"]->Clone());
    histo_["ptBGQCD" ][kData][Njets_[mult]] =    (TH1F*)histo_["pt"][kQCD  ]["Njets4Btag"]->Clone();
    histo_["ptBGQCD" ][kData][Njets_[mult]]->Scale(QCDVariation);
    histo_["pt BG"   ][kData][Njets_[mult]]->Add(histo_["ptBGQCD"][kData][Njets_[mult]]);
    histo_["eta BG"  ][kData][Njets_[mult]] =    (TH1F*)histo_["eta"][kWjets]["Njets4Btag"]->Clone();
    histo_["eta BG"  ][kData][Njets_[mult]]->Scale(WjetsVariation);
    histo_["eta BG"  ][kData][Njets_[mult]]->Add((TH1F*)histo_["eta"][kZjets]["Njets4Btag"]->Clone());
    histo_["etaBGQCD"][kData][Njets_[mult]] =    (TH1F*)histo_["eta"][kQCD  ]["Njets4Btag"]->Clone();
    histo_["etaBGQCD"][kData][Njets_[mult]]->Scale(QCDVariation);
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
	    if(bin==2) writeToFile("top diffXSec "+Njets_[mult2], "systematicVariations/differentialTopPt"+Njets_[mult2]+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 0);
	    double value = histo_["pt top" ][kData][Njets_[mult2]]->GetBinContent(bin);
	    writeToFile(value, "systematicVariations/differentialTopPt"+Njets_[mult2]+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 1);
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
	    if(bin==1) writeToFile("top diffXSec "+Njets_[mult2], "systematicVariations/differentialTopEta"+Njets_[mult2]+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 0);
	    double value = histo_["eta top"][kData][Njets_[mult2]]->GetBinContent(bin);
	    writeToFile(value, "systematicVariations/differentialTopEta"+Njets_[mult2]+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 1);
	  }
	}
      }
    }
  }

  // ---
  //    INCLUSIVE xSec (from data and MC) for chosen phase space
  // ---
  TH1F *sigmaLjetsInclusiveMCReco   = new TH1F("MCRecoLjets"  , "MCRecoLjets"  , 6, 0.5, 6.5);
  TH1F *sigmaLjetsInclusiveData     = new TH1F("data"         , "data"         , 6, 0.5, 6.5);
  TH1F *sigmaLjetsInclusiveMCGen    = new TH1F("MCGenLjets"   , "MCGenLjets"   , 6, 0.5, 6.5);
  TH1F *sigmaLjetsInclusiveMCGenBkg = new TH1F("MCGenLjetsBkg", "MCGenLjetsBkg", 6, 0.5, 6.5);
  TH1F *sigmaLjetsInclusiveMCGenSig = new TH1F("MCGenLjetsSig", "MCGenLjetsSig", 6, 0.5, 6.5);
  TH1F *sigmaTopInclusiveDataNoBtag = new TH1F("dataTop1"     , "dataTop1"     , 6, 0.5, 6.5);
  TH1F *sigmaTopInclusiveMCReco     = new TH1F("MCRecoTop"    , "MCRecoTop"    , 6, 0.5, 6.5);
  TH1F *sigmaTopInclusiveMCGen      = new TH1F("MCGenTop"     , "MCGenTop"     , 6, 0.5, 6.5);
  TH1F *sigmaTopInclusiveDataBtag   = new TH1F("dataTop2"     , "dataTop2"     , 6, 0.5, 6.5);
  std::cout << std::endl << std::endl << "inclusive cross sections:" << std::endl;
  // loop samples - l+jets MC(W,Z,top) and Data
  for(unsigned int idx=kData; idx<=kLepJets; ++idx){    
    if(idx==kData   ) std::cout << std::endl << std::endl << "a) from data" << std::endl;
    if(idx==kLepJets) std::cout << std::endl << std::endl << "b) from reco-MC (l+jets or top MC)" << std::endl;
    // loop jet multiplicities (no >=3 jets && >= 1 btag)
    for(unsigned int mult=0; mult<Njets_.size()-1; ++mult){
      std::cout << jetLabel(Njets_[mult])+ ": "<< std::endl;
      // ---
      // a) l+jets (no btag)
      // ---
      if(mult<4){
	// (i) events after selection ( data / l+jets-MC )
	double Nselected = histo_["pt"][idx   ][Njets_[mult]]->Integral( 0 , histo_["pt"][idx   ][Njets_[mult]]->GetNbinsX()+1 );
	double NZjets    = histo_["pt"][kZjets][Njets_[mult]]->Integral( 0 , histo_["pt"][kZjets][Njets_[mult]]->GetNbinsX()+1 );
        // (ii) QCD estimation (from ABCD) for data
	double NQCD=0;
        if(idx==kData) NQCD=NQCD_[mult];
        // (iii) calculate cross section (include MC-efficiency and luminosity)
	double Nmeasure = Nselected-NQCD-NZjets;
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
	  writeToFile("l+jets cross section (phase space) "+Njets_[mult], "systematicVariations/ljetsXSec"+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", append);
	  writeToFile(sigma, "systematicVariations/ljetsXSec"+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 1);
	}
	if(idx==kLepJets){
	  sigmaLjetsInclusiveMCReco->SetBinContent(mult+1, sigma );
	  sigmaLjetsInclusiveMCReco->SetBinError  (mult+1, dsigma);
	}
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
	  double NBG  = histo_["pt"][kWjets]["Njets4Btag"]->Integral( 0 , histo_["pt"][kWjets]["Njets4Btag"]->GetNbinsX()+1 )*WjetsVariation;
	  NBG        += histo_["pt"][kZjets]["Njets4Btag"]->Integral( 0 , histo_["pt"][kZjets]["Njets4Btag"]->GetNbinsX()+1 );
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
	  // save top xSec (phase space) results for systematic variations and determination of systematic errors
	  writeToFile("top cross section (phase space) N(jets)>=4 & N(Btags)>=1", "systematicVariations/topXSec"+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 0);
	  writeToFile(sigma, "systematicVariations/topXSec"+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 1);
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
	// (ii) substract QCD and Z+jets (from RECO MC)
	double NQCD      = histo_["pt"][kQCD  ][Njets_[mult]]->Integral( 0 , histo_["pt"][kQCD  ][Njets_[mult]]->GetNbinsX()+1 );
	NQCD*=QCDVariation;
	double NZjets    = histo_["pt"][kZjets][Njets_[mult]]->Integral( 0 , histo_["pt"][kZjets][Njets_[mult]]->GetNbinsX()+1 );
	// (iii) W+jets estimation (from charge asymmetrie method) - need to scale with same efficiency!
	double NW =NWestimate;
	double Nmeasure = Nselected-NQCD-NZjets-NW;
	// if c.a. method is not working: substract W+jets from MC reco
	if(Nmeasure<=0||NW<0){
	  if(Nmeasure<=0) std::cout << "N(W) from c.a. is larger than N(all events), take N(W) from MC gen";
	  if(NW<0)        std::cout << "N(W) from c.a. is negative, take N(W) from MC gen";	
	  double NWMC=histo_["pt"][kWjets][Njets_[mult]]->Integral( 0 , histo_["pt"][kGenW  ][Njets_[mult]]->GetNbinsX()+1 );
	  NWMC*=WjetsVariation;
	  Nmeasure=Nselected-NQCD-NZjets-NWMC;
	}
	// (iv) calculate cross section 
	double sigma  = Nmeasure/(0.001*luminosity*effNjets4);
	double dsigma = sqrt(Nselected)/(luminosity*0.001*effNjets4);
	std::cout << std::endl << "top: " << setprecision(4) << fixed << sigma << " +/- " << dsigma << " pb" << std::endl;
	// (v) fill inclusive xSec(phase space) calculated from >=4 jets histo (QCD and Wjets subtracted, efficiency correction applied)
	sigmaTopInclusiveDataNoBtag->SetBinContent(2, sigma );
	sigmaTopInclusiveDataNoBtag->SetBinError  (2, dsigma);
	// save top xSec (phase space) results for systematic variations and determination of systematic errors
	writeToFile("top cross section (phase space) N(jets)>=4 & W-estimation", "systematicVariations/topXSec2"+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 0);
	writeToFile(sigma, "systematicVariations/topXSec2"+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 1);
	}
      }
    }

  // ---
  // c) l+jets and top gen MC
  // ---
  std::cout << std::endl << std::endl << "c) from gen-MC (W+jets && top MC)" << std::endl;
  // loop jet multiplicities (>= 1-4)
  for(unsigned int mult=0; mult<4; ++mult){
    double NTopSig  = histo_["pt"][kGenSig][Njets_[mult]]->Integral( 0 , histo_["pt"][kGenSig][Njets_[mult]]->GetNbinsX()+1 ); 
    double NTopBkg  = histo_["pt"][kGenBkg][Njets_[mult]]->Integral( 0 , histo_["pt"][kGenBkg][Njets_[mult]]->GetNbinsX()+1 ); 
    double NWjets = histo_["pt"][kGenW  ][Njets_[mult]]->Integral( 0 , histo_["pt"][kGenW  ][Njets_[mult]]->GetNbinsX()+1 );
    double NLjets = NWjets + NTopSig + NTopBkg;
    double sigmaLjetsGen = NLjets/(luminosity*0.001);
    double sigmaLjetsGenSig =NTopSig/(luminosity*0.001);
    double sigmaTopGen      = (NTopSig+NTopBkg) / (luminosity*0.001);
    if(mult<4 ){
      sigmaLjetsInclusiveMCGen   ->SetBinContent(mult+1, sigmaLjetsGen   );
      sigmaLjetsInclusiveMCGenSig->SetBinContent(mult+1, sigmaLjetsGenSig);
      sigmaLjetsInclusiveMCGenBkg->SetBinContent(mult+1, sigmaTopGen     );
      std::cout << "gen MC l+jets XSec "+jetLabel(Njets_[mult])+": ";
      std::cout << setprecision(4) << fixed << sigmaLjetsGen << " pb"  << std::endl;
    }
    if(mult==3){
      sigmaTopInclusiveMCGen  ->SetBinContent(1, sigmaTopGen);
      std::cout << "gen MC Top XSec "+jetLabel(Njets_[mult])+": ";
      std::cout << setprecision(4) << fixed  << sigmaTopGen << " pb"  << std::endl;
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
  double extrapolation = readLineFromFile(180);
  std::cout << "extrapolation factor from chosen to inclusive phase space: " << extrapolation  << std::endl;
  // (iii) apply extrapolation factor on cross section results from phase space
  double sigmaData       = sigmaTopInclusiveDataBtag->GetBinContent(1)   * extrapolation;
  double errorSigmaData  = sigmaTopInclusiveDataBtag->GetBinError(1)     * extrapolation;
  double sigmaData2      = sigmaTopInclusiveDataNoBtag->GetBinContent(2) * extrapolation;
  double errorSigmaData2 = sigmaTopInclusiveDataNoBtag->GetBinError(2)   * extrapolation;
  // (iv) fill histos with the calculated values
  TH1F *sigmaTopExtrapolatedData   = new TH1F("sigmaTopExtrapolatedData"  , "sigmaTopExtrapolatedData"  , 2, 0, 2.0);
  TH1F *sigmaTopExtrapolatedData2  = new TH1F("sigmaTopExtrapolatedData2" , "sigmaTopExtrapolatedData2" , 2, 0, 2.0);
  TH1F *sigmaTopExtrapolatedTheory = new TH1F("sigmaTopExtrapolatedTheory", "sigmaTopExtrapolatedTheory", 2, 0, 2.0);
  sigmaTopExtrapolatedData  ->SetBinContent(1, sigmaData      );
  sigmaTopExtrapolatedData  ->SetBinError  (1, errorSigmaData );
  sigmaTopExtrapolatedData2 ->SetBinContent(2, sigmaData2     );
  sigmaTopExtrapolatedData2 ->SetBinError  (2, errorSigmaData2);
  sigmaTopExtrapolatedTheory->SetBinContent(1, sigmaTheory    );
  // (vii) printing to have numbers
  std::cout << std::endl << "total cross section for complete phasespace" << std::endl;
  std::cout << "theory: " << setprecision(1) << fixed << sigmaTheory << " pb" << std::endl;
  std::cout << "data (use btag): "  << setprecision(1) << fixed << sigmaData;
  std::cout << " +/- " << setprecision(1) << fixed << errorSigmaData << " pb" << std::endl;
  std::cout << "data (no btag ): "  << setprecision(1) << fixed << sigmaData2;
  std::cout << " +/- " << setprecision(1) << fixed << errorSigmaData2 << " pb" << std::endl;
  // (viii) save top xSec (inclusive) results for systematic variations and determination of systematic errors
  writeToFile("top cross section (inclusive) N(jets)>=4 & N(Btags)>=1", "systematicVariations/topXSecInclusive1"+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 0);
  writeToFile(sigmaData,  "systematicVariations/topXSecInclusive1"+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 1);
  writeToFile("top cross section (inclusive) N(jets)>=4 & W-estimation", "systematicVariations/topXSecInclusive2"+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 0);
  writeToFile(sigmaData2, "systematicVariations/topXSecInclusive2"+TopSample+"TopMC"+JESShift+"Lumi"+LuminosityVariation+EffScale+QCDScale+WjetsScale+".txt", 1);

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
    yieldLeg->AddEntry( histo_["pt yield"][kData ]["Njets1"], "2010 data (7TeV), "+lum+" pb ^{-1}"     , "PL");
    yieldLeg->AddEntry( histo_["pt yield"][kSig  ]["Njets1"], "t#bar{t} signal MC@NLO"                 , "F" );
    yieldLeg->AddEntry( histo_["pt yield"][kBkg  ]["Njets1"], "t#bar{t} other MC@NLO"                  , "F" );
    yieldLeg->AddEntry( histo_["pt yield"][kQCD  ]["Njets1"], "QCD PYTHIA"                             , "F" );
    yieldLeg->AddEntry( histo_["pt yield"][kWjets]["Njets1"], "W#rightarrowl#nu MADGRAPH"              , "F" );
    yieldLeg->AddEntry( histo_["pt yield"][kZjets]["Njets1"], "Z/#gamma*#rightarrowl^{+}l^{-} MADGRAPH", "F" );
    // c) create legend for l+jets differential cross sections - extra canvas
    TLegend *lJetsXSecLeg = new TLegend(0.01, 0.30, 0.90, 0.92);
    lJetsXSecLeg->SetFillStyle(0);
    lJetsXSecLeg->SetBorderSize(0);
    lJetsXSecLeg->AddEntry(histo_[ljetsXSecDiff_[0]][kData][Njets_[0]], "2010 data (7TeV), "+lum+" pb ^{-1}", "PL");
    lJetsXSecLeg->AddEntry(histo_[ljetsGen_[0]][kGenSig][Njets_[0]],    "t#bar{t} signal MC@NLO"            , "F" );
    lJetsXSecLeg->AddEntry(histo_[ljetsGen_[0]][kGenBkg][Njets_[0]],    "t#bar{t} other MC@NLO"             , "F" );
    lJetsXSecLeg->AddEntry(histo_[ljetsGen_[0]][kGenW  ][Njets_[0]],    "W#rightarrowl#nu MADGRAPH"         , "F" );
    // d) create legend for l+jets differential Normalized cross sections - extra canvas
    TLegend *lJetsXSecLegNorm = new TLegend(0.01, 0.30, 1.20, 0.92);
    lJetsXSecLegNorm->SetFillStyle(0);
    lJetsXSecLegNorm->SetBorderSize(0);
    if(loadValues)   lJetsXSecLegNorm->SetHeader("after QCD and efficiency correction");
    if(!loadValues)  lJetsXSecLegNorm->SetHeader("without any QCD or efficiency corrections");
    lJetsXSecLegNorm->AddEntry(histo_["pt l+jets diff norm XSec"][kData   ]["Njets1"], "2010 data (7TeV), "+lum+" pb ^{-1}", "PL");
    lJetsXSecLegNorm->AddEntry(histo_["pt l+jets diff norm XSec"][kLepJets]["Njets1"], "MC (W#rightarrowl#nu, t#bar{t})"   , "PL");
    // e) create legends for event composition
    // part 1)
    TLegend *eventCompositionPart1 = new TLegend(0.15, 0.04, 0.83, 0.96);
    eventCompositionPart1->SetFillStyle(0);
    eventCompositionPart1->SetBorderSize(0);
    eventCompositionPart1->SetHeader("signal composition:");
    eventCompositionPart1->AddEntry( histo_["pt composition"][kSig]["Njets1"], "t#bar{t} signal MC@NLO", "PL");
    eventCompositionPart1->AddEntry( histo_["pt composition"][kBkg]["Njets1"], "t#bar{t} other MC@NLO" , "PL");
    // part 2) 
    TLegend *eventCompositionPart2 = new TLegend(0.15, 0.18, 0.83, 0.80);
    eventCompositionPart2->SetFillStyle(0);
    eventCompositionPart2->SetBorderSize(0);
    eventCompositionPart2->AddEntry( histo_["pt composition"][kQCD  ]["Njets1"], "QCD Pythia"                             , "PL");
    eventCompositionPart2->AddEntry( histo_["pt composition"][kWjets]["Njets1"], "W#rightarrowl#nu MADGRAPH"              , "PL");
    eventCompositionPart2->AddEntry( histo_["pt composition"][kZjets]["Njets1"], "Z/#gamma*#rightarrowl^{+}l^{-} MADGRAPH", "PL");
    // f) create legends for inclusive cross sections
    // (i) l+jets
    TLegend *inclusiveCrossSectionLjetsLeg = new TLegend(0.41, 0.70, 0.91, 0.94);
    inclusiveCrossSectionLjetsLeg->SetFillStyle(0);
    inclusiveCrossSectionLjetsLeg->SetBorderSize(0);
    inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveData    , "2010 data (7TeV), "+lum+" pb ^{-1}" , "PL");
    inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveMCGen   , "W#rightarrowl#nu MADGRAPH"          ,  "F");
    inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveMCGenSig, "t#bar{t} signal MC@NLO"             ,  "F");
    inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveMCGenBkg, "t#bar{t} other MC@NLO"              ,  "F");
    //  inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveMCReco, "l+jets reco MC + corrections", "L" );
    // (ii) top
    TLegend *inclusiveCrossSectionTopLeg =  new TLegend(0.25, 0.46, 0.94, 0.94);
    inclusiveCrossSectionTopLeg->SetFillStyle (1001);
    inclusiveCrossSectionTopLeg->SetFillColor(kWhite);
    inclusiveCrossSectionTopLeg->SetBorderSize(0);
    inclusiveCrossSectionTopLeg->SetHeader("top cross section (chosen phase space)");
    inclusiveCrossSectionTopLeg->AddEntry( sigmaTopInclusiveDataBtag  , "2010 data (7TeV), "+lum+" pb ^{-1}, b-tag"   , "PL");
    inclusiveCrossSectionTopLeg->AddEntry( sigmaTopInclusiveDataNoBtag, "2010 data (7TeV), "+lum+" pb ^{-1}, W-estim.", "PL");
    inclusiveCrossSectionTopLeg->AddEntry( sigmaTopInclusiveMCGen     , "t#bar{t} MC@NLO"                            , "L" );
    //  inclusiveCrossSectionTopLeg->AddEntry( sigmaTopInclusiveMCReco    , "l+jets reco MC +corr., use btag"            , "P ");
    // g)  create legends for DIFFERNTIAL TOP cross sections
    // (1) method using b-tag
    TLegend *differentialTopLeg = new TLegend(0.43, 0.59, 0.93, 0.83);
    differentialTopLeg->SetFillStyle(0);
    differentialTopLeg->SetBorderSize(0);
    differentialTopLeg->AddEntry( histo_["pt top"][kData  ][Njets_[4]]  , "2010 data (7TeV), "+lum+" pb ^{-1}, ", "PL");
    differentialTopLeg->AddEntry( histo_["pt top"][kData  ][Njets_[4]]  , " #geq 1 b-tag"                       , ""  );
    differentialTopLeg->AddEntry( histo_["pt top"][kGenSig][Njets_[3]]  , "t#bar{t} signal MC@NLO"      , "F" );
    differentialTopLeg->AddEntry( histo_["pt top"][kGenBkg][Njets_[3]]  , "t#bar{t} other MC@NLO"              , "F" );
    // (2) method using W-estimation
    TLegend *differentialTopLeg2 = new TLegend(0.43, 0.59, 0.93, 0.83);
    differentialTopLeg2->SetFillStyle(0);
    differentialTopLeg2->SetBorderSize(0);
    differentialTopLeg2->AddEntry( histo_["pt top"][kData  ][Njets_[4]]  , "2010 data (7TeV), "+lum+" pb ^{-1}, ", "PL");
    differentialTopLeg2->AddEntry( histo_["pt top"][kData  ][Njets_[4]]  , " W-estimation"                       , ""  );
    differentialTopLeg2->AddEntry( histo_["pt top"][kGenSig][Njets_[3]]  , "t#bar{t} signal MC@NLO"      , "F" );
    differentialTopLeg2->AddEntry( histo_["pt top"][kGenBkg][Njets_[3]]  , "t#bar{t} other MC@NLO"              , "F" );
    // i)  create legends for inclusive TOP cross section extrapolated to whole phase space
    TLegend *inclusiveCrossSectionTopLeg2 =  new TLegend(0.22, 0.56, 0.92, 0.94);
    inclusiveCrossSectionTopLeg2->SetFillStyle (1001);
    inclusiveCrossSectionTopLeg2->SetFillColor(kWhite);
    inclusiveCrossSectionTopLeg2->SetBorderSize(0);
    inclusiveCrossSectionTopLeg2->SetHeader("total cross section ( t#bar{t} )");
    inclusiveCrossSectionTopLeg2->AddEntry( sigmaTopExtrapolatedData  , "2010 data (7TeV), "+lum+" pb ^{-1}, b-tag"   , "PL");
    inclusiveCrossSectionTopLeg2->AddEntry( sigmaTopExtrapolatedData2 , "2010 data (7TeV), "+lum+" pb ^{-1}, W-estim.", "PL");
    inclusiveCrossSectionTopLeg2->AddEntry( sigmaTopExtrapolatedTheory, "#sigma_{NLO} (MCFM, m_{t}=172.5 GeV)"        , "L" );

    // ---
    //    create canvas 
    // ---
    std::vector<TCanvas*> MyCanvas;
    // a) canvas for yield and diff norm xsec (also legends) and event composition
    for(int idx=0; idx<=81; idx++){ 
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
	MyCanvas[canvasNumber]->SetTitle(variables_[var]+"EventYield"+lum2+"nb"+Njets_[mult]+log);
	if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
	// a) MC samples (loop)
	for(int idx=kQCD; idx>=kSig; --idx){
	  double min = 0.;
	  double max = 2*histo_[yield_[var]][kQCD][Njets_[mult]]->GetMaximum();
	  // set axis for plots
	  if(idx==kQCD){
	    if(logartihmicPlots){
	      min=0.1;
	      max*=10.0;
	      if(variables_[var]=="pt" ) min=0.01;
	      if(variables_[var]=="pt" ) max*=0.5;
	    }
	    if(variables_[var]=="phi") axesStyle(*histo_[yield_[var]][kQCD][Njets_[mult]], "#"+variables_[var]+" ( #mu )", "events / rad", min, max, 0.06, 1.4);
	    if(variables_[var]=="eta") axesStyle(*histo_[yield_[var]][kQCD][Njets_[mult]], "#"+variables_[var]+" ( #mu )", "events / binWidth", min, max, 0.06, 1.4);
	    if(variables_[var]=="pt" ) axesStyle(*histo_[yield_[var]][kQCD][Njets_[mult]], "p_{t} ( #mu ) [GeV]", "events / GeV", min, max, 0.06, 1.4);
	  }								
	  // draw MC histos
	  if(idx==kQCD ){
	    // color style
	    histogramStyle(*histo_[yield_[var]][idx][Njets_[mult]], idx);	
	    histo_[yield_[var]][idx][Njets_[mult]]->Draw("HIST");	
	  }
	  else {
	    histogramStyle(*histo_[yield_[var]][idx][Njets_[mult]], idx);		
	    histo_[yield_[var]][idx][Njets_[mult]]->Draw("HIST same");
	  }
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
	MyCanvas[canvasNumber]->SetTitle(variables_[var]+"DiffNormXSec"+lum2+"nb"+Njets_[mult]+log);
	if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
	// loop samples
	for(int idx=kLepJets; idx>=kData; --idx){
	  // set style for histos
	  // a) for MC
	  if(idx==kLepJets){
	    histogramStyle(*histo_[ljetsXSec_[var]][idx][Njets_[mult]], kLepJets, false);
	    // set axis for plots
	    double min = 0.;
	    double max = 0.6;
	    if(variables_[var]=="pt") max=0.035;
	    if(logartihmicPlots){
	      min=0.1;
	      max=1;
	      if(variables_[var]=="pt") max=0.5;
	      if(variables_[var]=="pt") min=0.0001;
	      if(variables_[var]=="phi") max*=0.5;
	      if(variables_[var]=="phi") min*=0.5;
	    }
	    if((variables_[var]=="phi")||(variables_[var]=="eta")){
	      axesStyle(*histo_[ljetsXSec_[var]][idx][Njets_[mult]], "#"+variables_[var]+" ( #mu )", "#frac{1}{#sigma} #frac{d#sigma}{d#"+variables_[var]+" (#mu)} [ 1 / binwidth ]", min, max, 0.055, 1.6);
	    }
	    if(variables_[var]=="pt") {
	      axesStyle(*histo_[ljetsXSec_[var]][idx][Njets_[mult]], "p_{t} ( #mu ) [GeV]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{t} (#mu)} [ 1 / GeV ]", min, max, 0.055, 1.6);
	    }
	  }
	  // b) for data
	  if(idx==kData){
	    histogramStyle(*histo_[ljetsXSec_[var]][idx][Njets_[mult]], kData, false);
	  }
	  // draw histos
	  if(idx==kLepJets) histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Draw("HIST");
	  if(idx==kData   ){
	    histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Draw("p X0 e1 same");
	    if(finalPlots) systematicError("diffNormXSec"+variables_[var], mult, *histo_[ljetsXSec_[var]][kData][Njets_[mult]], variables_[var]);
	  }
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
	MyCanvas[canvasNumber]->SetTitle(variables_[var]+"DiffXSec"+lum2+"nb"+Njets_[mult]+log);
	if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
	// loop samples
	for(int idx=kLepJets; idx>=kData; --idx){
	  // set style for histos
	  // a) for MC
	  if(idx==kLepJets){
	    histogramStyle(*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], kLepJets);
	    // set axis for plots
	    double min = 0.;
	    double max = 2*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->GetMaximum();
	    if(logartihmicPlots){
	      min=1.;
	      max*=100.0;
	      if(variables_[var]=="pt") max=0.1*max;
	      if(variables_[var]=="pt") min=0.005*min;
	      if(variables_[var]!="pt") max=max/(5*mult+1);
	    }
	    if((variables_[var]=="phi")||(variables_[var]=="eta")){
	      axesStyle(*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], "#"+variables_[var]+" ( #mu )", "#frac{d#sigma}{d#"+variables_[var]+" (#mu)} [ pb / binwidth ]", min, max, 0.055, 1.5);
	    }
	    if(variables_[var]=="pt") {
	      axesStyle(*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], "p_{t} ( #mu ) [GeV]", "#frac{d#sigma}{dp_{t} (#mu)} [ pb / GeV ]", min, max, 0.055, 1.5);
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
	      for(int gen=kGenW; gen>=kGenSig; --gen){
		histogramStyle(*histo_[ljetsGen_[var]][gen][Njets_[mult2]], gen-9);
		histo_[ljetsGen_[var]][gen][Njets_[mult2]]->Draw("Hist same");
	      }
	    }
	    //	  if(mult==4) draw scaled MC-reco with Btag;
	  }
	  // b) data
	  if(idx==kData   ){ 
	    histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->Draw("p e1 X0 same");
	    if(finalPlots) systematicError("differentialXSec"+variables_[var], mult, *histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], variables_[var]);
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
	for(int idx=kSig; idx<=kQCD; ++idx){
	  histogramStyle(*histo_[composition_[var]][idx][Njets_[mult]], idx, false); 
	  // axis style
	  if(idx==kSig){
	    if(variables_[var]=="phi"||variables_[var]=="eta"){
	      axesStyle(*histo_[composition_[var]][idx][Njets_[mult]], "#"+variables_[var]+" ( #mu )", "rel. event composition", 0., 1.);
	    }
	    if(variables_[var]=="pt"){
	      axesStyle(*histo_[composition_[var]][idx][Njets_[mult]], "p_{t} ( #mu )", "rel. event composition", 0., 1.);
	    }	  
	  }
	  // draw histos
	  if(idx==kSig){
	    histo_[composition_[var]][idx][Njets_[mult]]->Draw("hist" );
	    histo_[composition_[var]][idx][Njets_[mult]]->Draw("p same");
	  }
	  else{
	    histo_[composition_[var]][idx][Njets_[mult]]->Draw("hist same");
	    histo_[composition_[var]][idx][Njets_[mult]]->Draw("p same"   );
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
    // a) l+jets
    MyCanvas[canvasNumber] ->cd(0);
    MyCanvas[canvasNumber] ->SetTitle("inclusiveCrossSectionLjets"+log);
    if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
    double min = 0.;
    double max = 1100.;
    if(logartihmicPlots){
      min=5;
      max*=100.0;
    }
    axesStyle(*sigmaLjetsInclusiveMCReco, "N(jets) #geq", "#sigma ( l+jets ) [ pb ]", min, max);
    sigmaLjetsInclusiveMCReco->GetXaxis()->SetNdivisions(510);
    histogramStyle(*sigmaLjetsInclusiveMCReco, kData);
    histogramStyle(*sigmaLjetsInclusiveMCGen, kWjets);
    histogramStyle(*sigmaLjetsInclusiveData, kData);
    sigmaLjetsInclusiveMCReco    ->Draw("AXIS" );
    sigmaLjetsInclusiveMCGen     ->DrawClone("histsame" );
    histogramStyle(*sigmaLjetsInclusiveMCGenBkg, kBkg);
    sigmaLjetsInclusiveMCGenBkg  ->Draw("histsame" );
    histogramStyle(*sigmaLjetsInclusiveMCGenSig, kSig);
    sigmaLjetsInclusiveMCGenSig  ->Draw("histsame" );
    sigmaLjetsInclusiveData      ->Draw("p e1 X0 same"); 
    sigmaLjetsInclusiveMCReco    ->Draw("AXIS same" );
    if(finalPlots) systematicError("ljetsXSec", 6, *sigmaLjetsInclusiveData, "Njets");
    inclusiveCrossSectionLjetsLeg->Draw("same" );
    DrawLabel("phase space:"                                , 0.33 , 0.55, 0.82 , 0.75);
    DrawLabel("l#rightarrow#mu: p_{t}>20 GeV, | #eta |<2.1" , 0.43 , 0.45, 0.94 , 0.65);
    DrawLabel("jets: p_{t}>30 GeV, | #eta |<2.4"            , 0.435, 0.35, 0.935, 0.55);
    ++canvasNumber;

    // b) top with & without Btag in phase space
    MyCanvas[canvasNumber]     ->cd(0);
    MyCanvas[canvasNumber]     ->SetTitle("inclusiveCrossSectionTop");
    axesStyle(*sigmaTopInclusiveMCReco, "", "#sigma (t#bar{t}#rightarrow#mu + #geq 4 jets) [ pb ]", 0., 40, 0.05, 1.55);
    histogramStyle(*sigmaTopInclusiveMCReco    , 7,  false);
    histogramStyle(*sigmaTopInclusiveMCGen     , 8,  false);
    histogramStyle(*sigmaTopInclusiveDataNoBtag, 9,  false);
    histogramStyle(*sigmaTopInclusiveDataBtag  , 10, false);
    sigmaTopInclusiveMCReco->GetXaxis()->SetNdivisions (0);
    sigmaTopInclusiveMCReco    ->Draw("AXIS"); 
    double theoryErrorUp  =23.2;
    double theoryErrorDown=24.4;
    // extrapolation: defined in e) extrapolation to whole phase space
    TBox* box2 = new TBox(0.5, (double)sigmaTopInclusiveMCGen->GetBinContent(1)+theoryErrorUp/extrapolation, 2.5, (double)sigmaTopInclusiveMCGen->GetBinContent(1)-theoryErrorDown/extrapolation);
    box2->SetFillColor(38);
    box2->SetFillStyle(1001);
    box2->Draw("same");
    //  sigmaTopInclusiveMCGen     ->Draw("phistsame");
    drawLine(0.5, sigmaTopInclusiveMCGen->GetBinContent(1), 2.5, sigmaTopInclusiveMCGen->GetBinContent(1), sigmaTopInclusiveMCGen->GetLineColor());
    sigmaTopInclusiveDataNoBtag->Draw("p e1 X0 same");
    sigmaTopInclusiveDataBtag  ->Draw("p e1 X0 same");
    if(finalPlots) systematicError("topXSec" , 8, *sigmaTopInclusiveDataBtag  , "1");
    if(finalPlots) systematicError("topXSec2", 8, *sigmaTopInclusiveDataNoBtag, "2");
    inclusiveCrossSectionTopLeg->Draw("same" );
    DrawLabel("phase space:"                   , 0.40, 0.32, 0.89, 0.53);
    DrawLabel("#mu: p_{t}>20 GeV, | #eta |<2.1", 0.45, 0.25, 0.96, 0.43);
    DrawLabel("#geq 4 jets: p_{t}>30 GeV,"     , 0.45, 0.19, 0.94, 0.37);
    DrawLabel("| #eta |<2.4"                   , 0.57, 0.14, 0.92, 0.32);
    sigmaTopInclusiveMCReco    ->Draw("AXIS same");
    ++canvasNumber;

    // c) top with & without b-tag extrapolated to whole phase space
    MyCanvas[canvasNumber]     ->cd(0);
    MyCanvas[canvasNumber]     ->SetTitle("inclusiveCrossSectionTopExtrapolatedWholePhaseSpace");
    axesStyle(*sigmaTopExtrapolatedTheory, "", "#sigma (t#bar{t}) [ pb ]", 0., 400, 0.05, 1.55);
    histogramStyle(*sigmaTopExtrapolatedTheory, 8 , false);
    histogramStyle(*sigmaTopExtrapolatedData  , 10, false);
    histogramStyle(*sigmaTopExtrapolatedData2 , 9 , false);
    sigmaTopExtrapolatedTheory->GetXaxis()->SetNdivisions (0);
    sigmaTopExtrapolatedTheory  ->Draw("AXIS");
    TBox* box = new TBox(0.0, (double)sigmaTopExtrapolatedTheory->GetBinContent(1)+theoryErrorUp, 2.0, (double)sigmaTopExtrapolatedTheory->GetBinContent(1)-theoryErrorDown);
    box->SetFillColor(38);
    box->SetFillStyle(1001);
    box->Draw("same");
    drawLine(0.0, sigmaTopExtrapolatedTheory->GetBinContent(1), 2.0, sigmaTopExtrapolatedTheory->GetBinContent(1), sigmaTopExtrapolatedTheory->GetLineColor());
    sigmaTopExtrapolatedData2   ->Draw("p e1 X0 same");
    sigmaTopExtrapolatedData    ->Draw("p e1 X0 same");
    if(finalPlots) systematicError("topXSecInclusive1", 8   , *sigmaTopExtrapolatedData , "1");
    if(finalPlots) systematicError("topXSecInclusive2", 8   , *sigmaTopExtrapolatedData2, "2");
    inclusiveCrossSectionTopLeg2->Draw("same");
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
      double max = 0.43;
      if(logartihmicPlots){
	min=0.0001;
	max=120.0;
      }
      // Draw gen ttbar sig + bkg as stack and data as points on top
      histo_["pt top" ][kGenSig][Njets_[3]]->Add(histo_["pt top" ][kGenBkg][Njets_[3]]);
      histogramStyle(*histo_["pt top" ][kGenSig][Njets_[3]], kGenSig-9);
      axesStyle(*histo_["pt top" ][kGenSig][Njets_[3]], "p_{t} ( #mu ) [GeV]", "#frac{d#sigma}{dp_{t} (#mu)} (t#bar{t}#rightarrow#mu + #geq 4 jets) [ pb / GeV ]", min, max, 0.05, 1.55);
      histo_["pt top" ][kGenSig][Njets_[3]]->Draw("hist");
      histogramStyle(*histo_["pt top" ][kGenBkg][Njets_[3]],kGenBkg-9);
      histo_["pt top" ][kGenBkg][Njets_[3]]->Draw("hist same");
      histogramStyle(*histo_["pt top" ][kData  ][Njets_[mult]], kData);
      histo_["pt top" ][kData  ][Njets_[mult]]->Draw("p e1  X0 same");
      if(finalPlots) systematicError("differentialTopPt"+Njets_[mult], 7, *histo_["pt top" ][kData  ][Njets_[mult]], "pt");
      histo_["pt top" ][kGenSig][Njets_[3]]->Draw("axis same");
      jetMultiplicity_[3]->Draw("same");
      if(mult==4) differentialTopLeg ->Draw("same");
      if(mult==3) differentialTopLeg2->Draw("same");
      ++canvasNumber;

      // b) eta
      MyCanvas[canvasNumber]->cd(0);
      MyCanvas[canvasNumber]->SetTitle("etaDifferentialTopCrossSection"+Njets_[mult]+log);
      if(logartihmicPlots) MyCanvas[canvasNumber]->SetLogy(1);
      // set axis 
      double min2 = 0.;
      double max2 = 10.;
      if(logartihmicPlots){
	min2=0.05;
	max2=1500.0;
      }
      // Draw gen ttbar sig + bkg as stack and data as points on top
      histo_["eta top" ][kGenSig][Njets_[3]]->Add(histo_["eta top" ][kGenBkg][Njets_[3]]);
      histogramStyle(*histo_["eta top" ][kGenSig][Njets_[3]], kGenSig-9);  
      axesStyle(*histo_["eta top"][kGenSig][Njets_[3]], "#eta ( #mu )", "#frac{d#sigma}{d#eta (#mu)} (t#bar{t}#rightarrow#mu + #geq 4 jets) [ pb / binwidth ]", min2, max2, 0.05, 1.55);
      histo_["eta top" ][kGenSig][Njets_[3]]->Draw("hist");
      histogramStyle(*histo_["eta top" ][kGenBkg][Njets_[3]], kGenBkg-9);
      histo_["eta top" ][kGenBkg][Njets_[3]]->Draw("hist same");
      histogramStyle(*histo_["eta top" ][kData  ][Njets_[mult]], kData);
      histo_["eta top" ][kData  ][Njets_[mult]]->Draw("p e1 X0 same");
      if(finalPlots) systematicError("differentialTopEta"+Njets_[mult], 7, *histo_["eta top"][kData][Njets_[mult]], "eta");
      histo_["eta top" ][kGenSig][Njets_[3]   ]->Draw("axis same");
      jetMultiplicity_[3]->Draw("same");
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

void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin, float yMax, float yTitleSize, float yTitleOffset){
  hist.SetTitle("");
  hist.GetXaxis()->SetTitle(titleX);
  hist.GetXaxis()->CenterTitle();
  hist.GetXaxis()->SetTitleSize  ( 0.06);
  hist.GetXaxis()->SetTitleColor (    1);
  hist.GetXaxis()->SetTitleOffset(  1.0);
  hist.GetXaxis()->SetTitleFont  (   62);
  hist.GetXaxis()->SetLabelSize  ( 0.05);
  hist.GetXaxis()->SetLabelFont  (   62);
  hist.GetXaxis()->SetNdivisions (  505);
  hist.GetYaxis()->SetTitle(titleY);
  hist.GetYaxis()->SetTitleSize  ( yTitleSize );
  hist.GetYaxis()->SetTitleColor (    1);
  hist.GetYaxis()->SetTitleOffset(yTitleOffset);
  hist.GetYaxis()->SetTitleFont  (   62);
  hist.GetYaxis()->SetLabelSize  ( 0.04);
  hist.GetYaxis()->SetLabelFont  (   62);
  hist.GetYaxis()->CenterTitle   ( true);
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

double readLineFromFile(int line, TString file){
  // introduce function to read a double value drom a specific line of a file
  std::ifstream finDouble (file);
  std::string readIn;
  // check if file exists
  if (!finDouble){
    std::cout << "can not open file" << std::endl;
    return -1;
  }
  // loop lines of the file
  for(int l=1; !finDouble.eof(); ++l){
    // save line content in readIn
    getline(finDouble, readIn);
    // convert your chosen line into double and return it
    if(l==line) return atof(readIn.c_str()); 
  }
  // if line is not found
  std::cout << "can not find line" << std::endl;
  return -1.;  
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
  if(sampleEnum==kQCD  ) output ="e) QCD";
  if(sampleEnum==kData ) output ="f) Data";
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

double getABCDNumbers( TString njets, bool loadValues){
  // get N(QCD) from ABCD estimation 
  // if loaded from file: be sure the lines are the wright ones!
  double result = 0;
  if(loadValues){
    if(njets=="Njets1") result= readLineFromFile(8 );
    if(njets=="Njets2") result= readLineFromFile(9 );
    if(njets=="Njets3") result= readLineFromFile(10);
    if(njets=="Njets4") result= readLineFromFile(11);
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

double getMCEffiencies(TString variable, int bin, int njets, bool loadValues, bool useMG, TString JES)
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
  if(useMG      ) file+="MG";
  if(JES=="up"  ) file+="JES11";
  if(JES=="down") file+="JES09";
  int systematic=0;
  if((useMG)||(JES=="up")||(JES=="down")) systematic=11;
  file+=".txt";
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
  return result;
}

TString sampleLabel(unsigned int sample){
  TString result;
  if(sample==kSig    ) result="ttbar signal";
  if(sample==kBkg    ) result="ttbar background";
  if(sample==kWjets  ) result="W+jets";
  if(sample==kZjets  ) result="Z+jets";
  if(sample==kQCD    ) result="QCD";
  if(sample==kData   ) result="data";
  if(sample==kLepJets) result="all l+jets MC";
  if(sample==kAllMC  ) result="all MC";
  if(sample==kABCD   ) result="QCD from ABCD method";
  return result;
}

double getInclusiveMCEff(TString topORlep, int njets, bool loadValues, bool useMG, TString JES){
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
  if(useMG      ) file+="MG";
  if(JES=="up"  ) file+="JES11";
  if(JES=="down") file+="JES09";
  int systematic=0;
  if((useMG)||(JES=="up")||(JES=="down")) systematic=11;
  file+=".txt";
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
  return result;
}

void DrawLabel(TString text, const double x1, const double y1, const double x2, const double y2){
  TPaveLabel *label = new TPaveLabel(x1, y1, x2, y2, text, "br NDC");
  label->SetFillStyle(0);
  label->SetBorderSize(0);
  label->SetTextSize(0.26);
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
  
void systematicError(const TString plot, const int jetMultiplicity, TH1& histo, const TString variable){
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
    double std     = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdQCDestimationStdWjetsEstimationStd.txt" );
    double lumiUp  = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiUpEffStdQCDestimationStdWjetsEstimationStd.txt"      );
    double lumiDown= readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiDownEffStdQCDestimationStdWjetsEstimationStd.txt"    );
    double MG      = readLineFromFile(line+count, "./systematicVariations/"+plot+"MadTopMCLumiNominalEffStdQCDestimationStdWjetsEstimationStd.txt" );
    double JESUp   = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCJES11LumiNominalEffStdQCDestimationStdWjetsEstimationStd.txt");
    double JESDown = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCJES09LumiNominalEffStdQCDestimationStdWjetsEstimationStd.txt");
    double EffUp   = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffUpQCDestimationStdWjetsEstimationStd.txt"  );
    double EffDown = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffDownQCDestimationStdWjetsEstimationStd.txt");
    double QCDUp   = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdQCDestimationUpWjetsEstimationStd.txt"  );
    double QCDDown = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdQCDestimationDownWjetsEstimationStd.txt");
    double WUp     = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdQCDestimationStdWjetsEstimationUp.txt"  );
    double WDown   = readLineFromFile(line+count, "./systematicVariations/"+plot+"NloTopMCLumiNominalEffStdQCDestimationStdWjetsEstimationDown.txt");
    // calculate and print out all systematic errors
    double JESError  = ( std::abs(JESUp-std ) + std::abs(JESDown-std ) ) / 2.0;
    std::cout << "JES: +/- " << setprecision(3) << fixed << "(|"<< JESUp << " - " << std << "|+|"<< JESDown << " - " << std << "|) / 2 = "<< JESError << std::endl;
    double LumiError = ( std::abs(lumiUp-std) + std::abs(lumiDown-std) ) / 2.0;
    std::cout << "lumi: +/- " << setprecision(3) << fixed << "(|"<< lumiUp << " - " << std << "|+|"<< lumiDown << " - " << std << "|) / 2 = " << LumiError << std::endl;
    double EffError  = ( std::abs(EffUp-std ) + std::abs(EffDown-std ) ) / 2.0;
    std::cout << "eff: +/- " << setprecision(3) << fixed << "(|"<< EffUp << " - " << std << "|+|"<< EffDown << " - " << std << "|) / 2 = "<< EffError << std::endl;
    double TopMCError= std::abs(MG-std);
    std::cout << "TopMC: +/- " << setprecision(3) << fixed << "|" << MG << "-" << std << "| = " << TopMCError << std::endl;
    double QCDError=   ( std::abs(QCDUp-std ) + std::abs(QCDDown-std ) ) / 2.0;
    std::cout << "QCDestimation: +/- " << setprecision(3) << fixed << "(|"<< QCDUp << " - " << std << "|+|"<< QCDDown << " - " << std << "|) / 2 = " << QCDError << std::endl;
    double WError=   ( std::abs(WUp-std ) + std::abs(WDown-std ) ) / 2.0;
    std::cout << "Westimation: +/- " << setprecision(3) << fixed << "(|"<< WUp << " - " << std << "|+|"<< WDown << " - " << std << "|) / 2 = " << WError << std::endl;
    // calculate the combined systematic error
    sysError=sqrt(JESError*JESError+LumiError*LumiError+TopMCError*TopMCError+EffError*EffError+QCDError*QCDError+WError*WError);
    //sysError=sqrt(JESError*JESError+TopMCError*TopMCError+EffError*EffError+QCDError*QCDError+WError*WError);
    std::cout << "total systematic error: +/- " << setprecision(3) << fixed << sysError << std::endl;
    // combine systematic and statistic error and Draw combined error
    double statError = sysHisto->GetBinError(bin);
    double combinedError = sqrt(statError*statError+sysError*sysError);
    std::cout << "combined error: sqrt( " << setprecision(3) << fixed << statError;
    std::cout << "^2 + "<< setprecision(3) << fixed << sysError << "^2 ) = ";
    std::cout << setprecision(3) << fixed << combinedError << std::endl;
    sysHisto->SetBinError(bin, combinedError);
  }
  sysHisto->Draw("p e X0 same");
}
