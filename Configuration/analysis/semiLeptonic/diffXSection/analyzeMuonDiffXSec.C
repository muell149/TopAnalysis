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
// -----------------------------------------------------

#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
#include <THStack.h>
#include <TPaveLabel.h>
#include <TF1.h>

enum styles {kSig, kBkg, kWjets, kZjets, kQCD, kData, kLepJets, kAllMC, kABCD, kGenSig, kGenBkg, kGenW};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0, int fillStyle=1001); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
template <class T>
void writeToFile(T output, TString file="crossSectionCalculation.txt", bool append=1);
double readLineFromFile(int line, TString file="crossSectionCalculation.txt");
int roundToInt(double value);
TString getTStringFromInt(int i);
TString jetLabel(TString input);
TString samples(int sampleEnum);
TH1F* divideByBinwidth(TH1F* histo, bool calculateError=true);
double getABCDNumbers( TString njets, bool loadValues);
double getMCEffiencies(TString variable, int bin, int njets, bool loadValues);
TString sampleLabel(unsigned int sample);
double getInclusiveMCEff(TString topORlep, int njets, bool loadValues);

void analyzeMuonDiffXSec(double luminosity = 840, bool save = false, bool loadValues = true, TString dataFile="./diffXSecFromSignal/data/data1808json/analyzeDiffXData_840nb_residualJC.root")
{ 
  // ---
  //    main function parameters
  // ---
  // save:       choose whether you want to save every plot as png and all within one ps file
  // loadValues: choose whether you want to load effiency corrections 
  //             and bkg estimation from crossSection.txt file
  // luminosity: choose luminosity for scaling of event numbers 
  //             lum is derived from this and used for legend as entry
  TString lum = getTStringFromInt(roundToInt(luminosity));
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/earlyData/crossSection/";
  // choose whether you want to load effiency corrections and bkg estimation from crossSection.txt file


  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  //  gStyle->SetPalette(1);
  gStyle->SetErrorX(0); 

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;

  TString whichSample = "/spring10Samples/spring10SelV2Sync";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigNloSpring10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgNloSpring10.root"    ) );
  //  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigMadSpring10.root"    ) );
  //  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgMadSpring10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecWjetsMadSpring10.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecZjetsMadSpring10.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecQCDPythiaSpring10.root" ) );
  files_.push_back(new TFile(dataFile                                                             ) );

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
  std::cout << "chosen luminosity: " << lum << std::endl;
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
  lumiweight_.push_back(0.000007940958/50.0*luminosity);
  lumiweight_.push_back(0.000007940958/50.0*luminosity);
  //  lumiweight.push_back(0.000005308736/50.0*luminosity);
  //  lumiweight.push_back(0.000005308736/50.0*luminosity);
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
  //    get QCD bkg from ABCD method
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
    NQCD_ .push_back( getABCDNumbers(Njets_[mult], loadValues) );
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
  //    get efficiencies from MC gen studies
  // ---
  // a) eff. for l+jets bin per bin correction -> differential cross section
  // create container for effiencies
  std::map< TString, std::map <unsigned int, std::map <TString, double> > > efficiency_;
  // example: efficiency_["pt"][(bin)1]["Njets1"]
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
	if(variables_[var]=="phi"&&bin==1) efficiency_[variables_[var]][0][Njets_[mult]] = getMCEffiencies(variables_[var], 0, mult, loadValues);
	efficiency_[variables_[var]][bin][Njets_[mult]] = getMCEffiencies(variables_[var], bin, mult, loadValues);
	// get overflow bin for pt and phi
	if((variables_[var]=="pt"||variables_[var]=="phi")&&bin==histo_[variables_[var]][kSig][Njets_[mult]]->GetNbinsX()){
	efficiency_[variables_[var]][bin+1][Njets_[mult]] = getMCEffiencies(variables_[var], bin+1, mult, loadValues);
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
    ljetsInclusiveEff_. push_back( getInclusiveMCEff("lep", mult+1, loadValues) );
  }
  // c) eff. for top inclusive cross section (N(jets)>=4 && N(BTags)>=1 corresponds to 5)
  std::cout<< std::endl << std::endl << "c) inclusive top";
  double effNjets4Btag = getInclusiveMCEff("top", 5, loadValues);

  // d) eff. for differenial top cross sections >=4 jets and btag
  // (i) pt
  std::vector<double> topPtEff_;
  std::cout << std::endl<< std::endl << "d) differential top (>=4 jets && >=1 btag)";
  std::cout << std::endl << "(i) pt";
  for(int bin=2; bin<=7; ++bin){
    double eff=readLineFromFile(154+bin);
    topPtEff_ .push_back(eff);
    std::cout << std::endl << "bin " << bin << ": " << eff;
  }
  // (ii) eta
  std::vector<double> topEtaEff_;
  std::cout << std::endl << "(i) eta";
  for(int bin=1; bin<=4; ++bin){
    double eff= readLineFromFile(162+bin);
    topEtaEff_ .push_back(eff);
    std::cout << std::endl << "bin " << bin << ": " << eff;
  }
  
  // ---
  //    get W-estimation from charge asymmetry method
  // ---
  double NWestimate = readLineFromFile(171);
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
	// b) substract QCD for data (not for btag-selections)
	if((idx==kData)&&(mult!=4)&&(mult!=5)) histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Add( histo_[variables_[var]][kABCD][Njets_[mult]], -1.0);
	// c) apply efficiency corrections for each bin
	// loop bins (including underflow and overflow)
	for(int bin =0; bin<=histo_[variables_[var]][kData][Njets_[mult]]->GetNbinsX()+1; ++bin){
	  // if efficiency is not 0 correct by division (reco=gen*eff)
	  if(efficiency_[variables_[var]][bin][Njets_[mult]]!=0){
	    double oldError = sqrt( histo_[ljetsXSec_[var]][idx][Njets_[mult]]->GetBinContent(bin) ); 
	    histo_[ljetsXSec_[var]][idx][Njets_[mult]]->SetBinContent(bin, histo_[ljetsXSec_[var]][idx][Njets_[mult]]->GetBinContent(bin) / efficiency_[variables_[var]][bin][Njets_[mult]]);
	    // take care of error: N'=N/e -> sN'= sN/e
	    histo_[ljetsXSec_[var]][idx][Njets_[mult]]->SetBinError(bin, oldError/ efficiency_[variables_[var]][bin][Njets_[mult]]);
	  }
	}
	// d) l+jets differential cross section (without normalization)
	//  i) clone (also for inclusive l+jets xSec)
	histo_[ljetsXSecDiff_     [var]][idx][Njets_[mult]]= (TH1F*)histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Clone();
	histo_[ljetsXSecInclusive_[var]][idx][Njets_[mult]]= (TH1F*)histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Clone();
	//  ii) divide by binwidth (and recalculate errors)
	histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]=divideByBinwidth(histo_[ljetsXSecDiff[var]][idx][Njets_[mult]], true);
	// f) normalize to total cross section
	double NAll = histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Integral(0, histo_[ljetsXSec_[var]][idx][Njets_[mult]]->GetNbinsX()+1);
	histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Scale(1/NAll);
	// g) divide by binwidth
	if(idx==kData)    histo_[ljetsXSec_[var]][idx][Njets_[mult]] = divideByBinwidth(histo_[ljetsXSec_[var]][idx][Njets_[mult]], false);
	if(idx==kLepJets) histo_[ljetsXSec_[var]][idx][Njets_[mult]] = divideByBinwidth(histo_[ljetsXSec_[var]][idx][Njets_[mult]], false);
	// h) calculate error for each bin (gaussian error calculus for Nbin/binWidth * 1/Nhisto) for diff. norm. xsec
	for(int bin =0; bin<=histo_[variables_[var]][kData][Njets_[mult]]->GetNbinsX()+1; ++bin){
	  double Nbin     = histo_[ljetsXSecInclusive_[var]][idx][Njets_[mult]]->GetBinContent(bin);
	  double binWidth = histo_[ljetsXSecInclusive_[var]][idx][Njets_[mult]]->GetBinWidth(bin);
	  double NHisto   = histo_[ljetsXSecInclusive_[var]][idx][Njets_[mult]]->Integral(0, histo_[variables_[var]][kAllMC][Njets_[mult]]->GetNbinsX()+1);
	  double error = sqrt( (sqrt(Nbin)/(binWidth*NHisto))*(sqrt(Nbin)/(binWidth*NHisto))+ (Nbin*sqrt(NHisto)/(binWidth*NHisto*NHisto))*(Nbin*sqrt(NHisto)/(binWidth*NHisto*NHisto)) );
	  histo_[ljetsXSec_[var]][idx][Njets_[mult]]->SetBinError(bin, error);
	}
	// i) print out values for l+jet diff. norm xSec (all bins)
	// loop bins (excluding underflow and overflow-> can not divide by binwidth)
	std::cout << "1) diff norm. cross section l+jets ( "<< jetLabel(Njets_[mult]) << " ):" << std::endl;
	for(int bin =1; bin<=histo_[variables_[var]][kData][Njets_[mult]]->GetNbinsX(); ++bin){
	std::cout << "  bin " << bin << ": ";
	std::cout << setprecision(3) << fixed << histo_[ljetsXSec_[var]][idx][Njets_[mult]]->GetBinContent(bin) << " +/-";
	std::cout << setprecision(3) << fixed << histo_[ljetsXSec_[var]][idx][Njets_[mult]]->GetBinError(bin)   << std::endl;
	}
	// j) print out values for l+jet diff. xSec (all bins)
	std::cout << "2) differential cross section l+jets ( "<< jetLabel(Njets_[mult]) << " ):" << std::endl;
	// loop bins (excluding underflow and overflow-> can not divide by binwidth)
	for(int bin =1; bin<=histo_[variables_[var]][kData][Njets_[mult]]->GetNbinsX(); ++bin){
	std::cout << "  bin " << bin << ": ";
	std::cout << setprecision(3) << fixed << histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->GetBinContent(bin) << " +/-";
	std::cout << setprecision(3) << fixed << histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->GetBinError(bin)   << std::endl;
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
      // create stack-plot: ttbar signal, ttbar other, W+jets
      histo_[ljetsGen_[var]][kGenBkg][Njets_[mult]]->Add( histo_[ljetsGen_[var]][kGenSig][Njets_[mult]] );
      histo_[ljetsGen_[var]][kGenW  ][Njets_[mult]]->Add( histo_[ljetsGen_[var]][kGenBkg][Njets_[mult]] );
    }
  }

  // ---
  //    differential top cross sections (pt & eta) for >=4 jets and >=1 btag
  // ---
  std::cout << std::endl << "differential top cross section" << std::endl;
  // a) data
  // (i) clone plots from data yields
  histo_["pt top" ][kData][Njets_[4]]=(TH1F*)histo_["pt" ][kData][Njets_[4]]->Clone();
  histo_["eta top"][kData][Njets_[4]]=(TH1F*)histo_["eta"][kData][Njets_[4]]->Clone();
  // (ii) bin per bin efficiency corrections
  // pt: start with second bin, include overflow, -2: vector strats with 0
  for(int bin=2; bin<=histo_["pt" ][kData][Njets_[4]]->GetNbinsX()+1; ++bin){
    histo_["pt top" ][kData][Njets_[4]]->SetBinContent(bin,      histo_["pt top" ][kData][Njets_[4]]->GetBinContent(bin) /topPtEff_ [bin-2]);
    histo_["pt top" ][kData][Njets_[4]]->SetBinError  (bin, sqrt(histo_["pt top" ][kData][Njets_[4]]->GetBinContent(bin))/topPtEff_ [bin-2]);
  }
  // eta: start with 1st bin - no overflow -1: vector starts with 0
  for(int bin=1; bin<=histo_["eta" ][kData][Njets_[4]]->GetNbinsX(); ++bin){
    histo_["eta top"][kData][Njets_[4]]->SetBinContent(bin,      histo_["eta top"][kData][Njets_[4]]->GetBinContent(bin) /topEtaEff_[bin-1]);
    histo_["eta top"][kData][Njets_[4]]->SetBinError  (bin, sqrt(histo_["eta top"][kData][Njets_[4]]->GetBinContent(bin))/topEtaEff_[bin-1]);
  }
  // (iii) divide per binwidth
  histo_["pt top" ][kData  ][Njets_[4]]= divideByBinwidth(histo_["pt top" ][kData][Njets_[4]], true);
  histo_["eta top"][kData  ][Njets_[4]]= divideByBinwidth(histo_["eta top"][kData][Njets_[4]], true);
  // b) gen ttbar sig + bkg
  histo_["pt top" ][kGenSig][Njets_[3]]= divideByBinwidth((TH1F*)histo_["pt" ][kGenSig][Njets_[3]]->Clone(), true);
  histo_["pt top" ][kGenBkg][Njets_[3]]= divideByBinwidth((TH1F*)histo_["pt" ][kGenBkg][Njets_[3]]->Clone(), true);
  histo_["eta top"][kGenSig][Njets_[3]]= divideByBinwidth((TH1F*)histo_["eta"][kGenSig][Njets_[3]]->Clone(), true);
  histo_["eta top"][kGenBkg][Njets_[3]]= divideByBinwidth((TH1F*)histo_["eta"][kGenBkg][Njets_[3]]->Clone(), true);
  // do the printout for the values (pt/eta x ttbarsig/ttbarbkg/data)
  std::cout << std::endl << "(i) pt" << std::endl;
  for(int idx=kData; idx<=kGenBkg; ++idx){
    if( (idx== kData) || (idx==kGenSig) || (idx==kGenBkg) ){
      int mult=0;
      idx==kData ? mult=4 : mult=3;
      if(idx==kData  ) std::cout << "data"         << std::endl;
      if(idx==kGenSig) std::cout << "ttbar signal" << std::endl;
      if(idx==kGenBkg) std::cout << "ttbar other"  << std::endl;
      for(int bin=2; bin<=histo_["pt" ][kData][Njets_[4]]->GetNbinsX()+1; ++bin){
	std::cout << "bin " << bin << ": " << histo_["pt top" ][idx][Njets_[mult]]->GetBinContent(bin);
	std::cout << " +/- " << histo_["pt top" ][idx][Njets_[mult]]->GetBinError(bin) << std::endl;
      }
    }
  }	
  std::cout << std::endl << "(ii) eta" << std::endl;
  for(int idx=kData; idx<=kGenBkg; ++idx){
    if( (idx== kData) || (idx==kGenSig) || (idx==kGenBkg) ){
      int mult=0;
      idx==kData ? mult=4 : mult=3;
      if(idx==kData  ) std::cout << "data"         << std::endl;
      if(idx==kGenSig) std::cout << "ttbar signal" << std::endl;
      if(idx==kGenBkg) std::cout << "ttbar other"  << std::endl;
      for(int bin=1; bin<=histo_["eta" ][kData][Njets_[4]]->GetNbinsX(); ++bin){
	std::cout << "bin " << bin << ": " << histo_["eta top" ][idx][Njets_[mult]]->GetBinContent(bin);
	std::cout << " +/- " << histo_["eta top" ][idx][Njets_[mult]]->GetBinError(bin) << std::endl;
      }
    }
  }

  // ---
  //    INCLUSIVE xSec (from data and MC) for chosen phase space
  // ---
  double NTopCorr;
  TH1F *sigmaLjetsInclusiveMCReco   = new TH1F("MCRecoLjets" , "MCRecoLjets" , 4, 0.5, 4.5);
  TH1F *sigmaLjetsInclusiveData     = new TH1F("data"        , "data"        , 4, 0.5, 4.5);
  TH1F *sigmaLjetsInclusiveMCGen    = new TH1F("MCGenLjets"  , "MCGenLjets"  , 4, 0.5, 4.5);
  TH1F *sigmaTopInclusiveDataNoBtag = new TH1F("dataTop1"    , "dataTop1"    , 4, 0.5, 4.5);
  TH1F *sigmaTopInclusiveMCReco     = new TH1F("MCRecoTop"   , "MCRecoTop"   , 4, 0.5, 4.5);
  TH1F *sigmaTopInclusiveMCGen      = new TH1F("MCGenTop"    , "MCGenTop"    , 4, 0.5, 4.5);
  TH1F *sigmaTopInclusiveDataBtag   = new TH1F("dataTop2"    , "dataTop2"    , 4, 0.5, 4.5);
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
	double Nselected = histo_["pt"][idx][Njets_[mult]]->Integral( 0 , histo_["pt"][idx][Njets_[mult]]->GetNbinsX()+1 );
        // (ii) QCD estimation (from ABCD) for data
	double NQCD=0;
        if(idx==kData) NQCD=NQCD_[mult];
        // (iii) calculate cross section (include MC-efficiency and luminosity)
	double Nmeasure = Nselected-NQCD;
        double sigma = Nmeasure/ljetsInclusiveEff_[mult]/luminosity;
	double dLuminosity = 0; //0.11*luminosity;
	double dsigma = sqrt( Nmeasure/(ljetsInclusiveEff_[mult]*ljetsInclusiveEff_[mult]*luminosity*luminosity) + (Nmeasure*Nmeasure)/(ljetsInclusiveEff_[mult]*ljetsInclusiveEff_[mult]*luminosity*luminosity*luminosity*luminosity)*dLuminosity*dLuminosity );
	std::cout << "l+jets:" << setprecision(3) << fixed << sigma << " +/- " << dsigma << " nb" << std::endl;
	// (iv) fill inclusive xSec(Njets) calculated from pt histo (QCD substracted and efficiency correction applied)
	if(idx==kData){
	  sigmaLjetsInclusiveData->SetBinContent(mult+1, sigma );
	  sigmaLjetsInclusiveData->SetBinError  (mult+1, dsigma);
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
	// (i) events after selection ( data / top-MC )
	if(idx==kData){
	  double Nselected =  histo_["pt"][idx][Njets_[mult]]->Integral( 0 , histo_["pt"][idx][Njets_[mult]]->GetNbinsX()+1 );
	  Nmeasure = Nselected;
	}
	if(idx==kLepJets){
	  Nmeasure =  histo_["pt"][kSig][Njets_[mult]]->Integral( 0 , histo_["pt"][kSig][Njets_[mult]]->GetNbinsX()+1 );
	  Nmeasure += histo_["pt"][kBkg][Njets_[mult]]->Integral( 0 , histo_["pt"][kBkg][Njets_[mult]]->GetNbinsX()+1 );
	}
        // (ii) calculate cross section (include MC-efficiency and luminosity, no QCD estimation done (too few statistics!))
	double sigma  = Nmeasure/effNjets4Btag/luminosity;
	double dLuminosity = 0; //0.11*luminosity;
	double dsigma = sqrt( Nmeasure/(effNjets4Btag*effNjets4Btag*luminosity*luminosity) + (Nmeasure*Nmeasure)/(effNjets4Btag*effNjets4Btag*luminosity*luminosity*luminosity*luminosity)*dLuminosity*dLuminosity );
	std::cout << std::endl << "top: " << setprecision(4) << fixed << sigma << " +/- " << dsigma << " /nb" << std::endl;
	// (iii) fill inclusive xSec(Njets) calculated from pt histo (QCD substracted and efficiency correction applied)
	if(idx==kData){
	  sigmaTopInclusiveDataBtag->SetBinContent(1, sigma );
	  sigmaTopInclusiveDataBtag->SetBinError  (1, dsigma);
	}
	if(idx==kLepJets){
	  sigmaTopInclusiveMCReco->SetBinContent(1, sigma );
	  sigmaTopInclusiveMCReco->SetBinError  (1, dsigma);
	}
      }
      // ---
      // b2) >=4jets & W-estimation
      // (substract W-boson bkg estimation from l+jets corrected histogram)
      // loop jet multiplicities
      if(mult==3&&idx==kData){
	// (i) events after selection and l+jets efficiency correction ( data only, no QCD estimation done (too few statistics!) )
	double Nselected = histo_[ljetsXSecInclusive_[0]][idx][Njets_[mult]]->Integral(0, histo_[ljetsXSecInclusive_[0]][idx][Njets_[mult]]->GetNbinsX()+1);
	// (ii) W+jets estimation (from charge asymmetrie method) - need to scale with same efficiency!
	double NW =NWestimate/ljetsInclusiveEff_[mult];
	double Nmeasure = Nselected-NW;
	if(Nmeasure<0){
	  Nmeasure = 0;
	  std::cout << "N(W) from c.a. is larger than N(all events)";
	}
	NTopCorr=Nmeasure;
	// (iii)) calculate cross section (include luminosity, l+jets efficiency already applied)
	double sigma  = Nmeasure/luminosity;
	double dLuminosity = 0; //0.11*luminosity;
	double dsigma = sqrt( Nmeasure/(luminosity*luminosity) + (Nmeasure*Nmeasure)/(luminosity*luminosity*luminosity*luminosity)*dLuminosity*dLuminosity );
	std::cout << "top: " << setprecision(4) << fixed << sigma << " +/- " << dsigma << " nb" << std::endl;
	// (iv) fill inclusive xSec(Njets) calculated from pt histo (QCD substracted and efficiency correction applied)
	sigmaTopInclusiveDataNoBtag->SetBinContent(1, sigma );
	sigmaTopInclusiveDataNoBtag->SetBinError  (1, dsigma);
      }
    }
  }
  // ---
  // c) gen MC
  // ---
  std::cout << std::endl << std::endl << "c) from gen-MC (W+jets && top MC)" << std::endl;
  // loop jet multiplicities (>= 1-4)
  for(unsigned int mult=0; mult<4; ++mult){
    double NTop   = histo_["pt"][kGenSig][Njets_[mult]]->Integral( 0 , histo_["pt"][kGenSig][Njets_[mult]]->GetNbinsX()+1 ); 
    NTop         += histo_["pt"][kGenBkg][Njets_[mult]]->Integral( 0 , histo_["pt"][kGenBkg][Njets_[mult]]->GetNbinsX()+1 ); 
    double NWjets = histo_["pt"][kGenW  ][Njets_[mult]]->Integral( 0 , histo_["pt"][kGenW  ][Njets_[mult]]->GetNbinsX()+1 );
    double NLjets = NWjets + NTop;
    double sigmaLjetsGen = NLjets/luminosity;
    double sigmaTopGen   = NTop  /luminosity;
    if(mult<4 ){
      sigmaLjetsInclusiveMCGen->SetBinContent(mult+1, sigmaLjetsGen);
      std::cout << "gen MC l+jets XSec "+jetLabel(Njets_[mult])+": ";
      std::cout << setprecision(4) << fixed << sigmaLjetsGen << " nb"  << std::endl;
    }
    if(mult==3){
      sigmaTopInclusiveMCGen  ->SetBinContent(1, sigmaTopGen);
      std::cout << "gen MC Top XSec "+jetLabel(Njets_[mult])+": ";
      std::cout << setprecision(4) << fixed  << sigmaTopGen << " nb"  << std::endl;
    }
  }
  std::cout << std::endl;

  // ---
  //    d) extrapolation to whole phase space
  // ---
  // sigma_topMeasure = Nmess(>=4 jets, >=1 btag) / luminosity / extrapolation
  // extrapolation = N(ttbar MC reco >=4 jets, >=1 btag) / N(ttbar theory)
  // N(ttbar theory) depends on the cross section which MUST be the same like it is 
  // used in the calculation of the lumiweight to cancel out in extrapolation factor
  // (i) set theory cross section
  double sigmaTheory = 0.1575;
  // (ii) calculate expected top events for chosen luminosity
  double NTheory = sigmaTheory * luminosity;
  // (iii) get top events after MC reco - selection 
  double NRecoMC  = histo_["pt"][kSig]["Njets4Btag"]->Integral( 0 , histo_["pt"][kSig]["Njets4Btag"]->GetNbinsX()+1 );
         NRecoMC += histo_["pt"][kBkg]["Njets4Btag"]->Integral( 0 , histo_["pt"][kBkg]["Njets4Btag"]->GetNbinsX()+1 );
  double extrapolation = NRecoMC / NTheory;
  // (iv) apply extrapolation factor on data to get the measurement
  double NData = histo_["pt"][kData]["Njets4Btag"]->Integral( 0 , histo_["pt"][kData]["Njets4Btag"]->GetNbinsX()+1 );
  double sigmaData      =       NData   / extrapolation / luminosity;
  double errorSigmaData = sqrt( NData ) / extrapolation / luminosity;
  // (v) fill histos with the calculated values
  TH1F *sigmaTopExtrapolatedData   = new TH1F("sigmaTopExtrapolatedData"  , "sigmaTopExtrapolatedData"  , 4, 0.5, 4.5);
  TH1F *sigmaTopExtrapolatedTheory = new TH1F("sigmaTopExtrapolatedTheory", "sigmaTopExtrapolatedTheory", 4, 0.5, 4.5);
  // scaling with 1000 to have pb as unit
  sigmaTopExtrapolatedData  ->SetBinContent(1, 1000*sigmaData     );
  sigmaTopExtrapolatedData  ->SetBinError  (1, 1000*errorSigmaData);
  sigmaTopExtrapolatedTheory->SetBinContent(1, 1000*sigmaTheory   );
  // (vi) printing to have numbers
  std::cout << std::endl << "total cross section for complete phasespace" << std::endl;
  std::cout << "from data >=4 jets & >=1 btag using (all ttbar gen)/(selection ttbar reco) extrapolation" << std::endl;
  std::cout << "theory: " << setprecision(1) << fixed << sigmaTheory*1000 << std::endl;
  std::cout << "data: "   << setprecision(1) << fixed << sigmaData*1000;
  std::cout << " +/- " << setprecision(1) << fixed << 1000*errorSigmaData << std::endl;

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
  yieldLeg->SetHeader("MC "+lum+" nb^{-1} @ 7TeV");
  yieldLeg->AddEntry( histo_["pt yield"][kSig  ]["Njets1"], "ttbar s.lep.(#mu) MC@NLO"  , "F" );
  yieldLeg->AddEntry( histo_["pt yield"][kBkg  ]["Njets1"], "ttbar other MC@NLO"        , "F" );
  yieldLeg->AddEntry( histo_["pt yield"][kQCD  ]["Njets1"], "QCD PYTHIA"                , "F" );
  yieldLeg->AddEntry( histo_["pt yield"][kWjets]["Njets1"], "W+jets MADGRAPH"           , "F" );
  yieldLeg->AddEntry( histo_["pt yield"][kZjets]["Njets1"], "Z+jets MADGRAPH"           , "F" );
  yieldLeg->AddEntry( histo_["pt yield"][kData ]["Njets1"], "2010 data "+lum+" nb ^{-1}", "PL");
  // c) create legend for l+jets differential cross sections - extra canvas
  TLegend *lJetsXSecLeg = new TLegend(0.01, 0.30, 1.00, 0.92);
  lJetsXSecLeg->SetFillStyle(0);
  lJetsXSecLeg->SetBorderSize(0);
  lJetsXSecLeg->AddEntry(histo_[ljetsXSecDiff_[0]][kData][Njets_[0]], "2010 data "+lum+" nb ^{-1}", "PL");
  lJetsXSecLeg->AddEntry(histo_[ljetsGen_[0]][kGenSig][Njets_[0]], "gen semi #mu t #bar{t} MC@NLO", "L" );
  lJetsXSecLeg->AddEntry(histo_[ljetsGen_[0]][kGenBkg][Njets_[0]], "gen other t #bar{t} MC@NLO"   , "L" );
  lJetsXSecLeg->AddEntry(histo_[ljetsGen_[0]][kGenW  ][Njets_[0]], "gen W+jets Madgraph"          , "L" );
  // d) create legend for l+jets differential Normalized cross sections - extra canvas
  TLegend *lJetsXSecLegNorm = new TLegend(0.01, 0.30, 1.30, 0.92);
  lJetsXSecLegNorm->SetFillStyle(0);
  lJetsXSecLegNorm->SetBorderSize(0);
  if(loadValues)   lJetsXSecLegNorm->SetHeader("after QCD and efficiency correction");
  if(!loadValues)  lJetsXSecLegNorm->SetHeader("without any QCD or efficiency corrections");
  lJetsXSecLegNorm->AddEntry(histo_["pt l+jets diff norm XSec"][kLepJets]["Njets1"], "MC gen (W+jet, top)"      , "PL");
  lJetsXSecLegNorm->AddEntry(histo_["pt l+jets diff norm XSec"][kData   ]["Njets1"], "2010 data "+lum+" nb^{-1}", "PL");
  // e) create legends for event composition
  // part 1)
  TLegend *eventCompositionPart1 = new TLegend(0.15, 0.04, 0.83, 0.96);
  eventCompositionPart1->SetFillStyle(0);
  eventCompositionPart1->SetBorderSize(0);
  eventCompositionPart1->SetHeader("signal composition:");
  eventCompositionPart1->AddEntry( histo_["pt composition"][kSig]["Njets1"], "semi #mu t #bar{t} MC@NLO", "PL");
  eventCompositionPart1->AddEntry( histo_["pt composition"][kBkg]["Njets1"], "other t #bar{t} MC@NLO"   , "PL");
  // part 2) 
  TLegend *eventCompositionPart2 = new TLegend(0.15, 0.18, 0.83, 0.80);
  eventCompositionPart2->SetFillStyle(0);
  eventCompositionPart2->SetBorderSize(0);
  eventCompositionPart2->AddEntry( histo_["pt composition"][kQCD  ]["Njets1"], "QCD Pythia"     , "PL");
  eventCompositionPart2->AddEntry( histo_["pt composition"][kWjets]["Njets1"], "W+jets Madgraph", "PL");
  eventCompositionPart2->AddEntry( histo_["pt composition"][kZjets]["Njets1"], "Z+jets Madgraph", "PL");
  // f) create legends for inclusive cross sections
  // (i) l+jets
  TLegend *inclusiveCrossSectionLjetsLeg = new TLegend(0.45, 0.65, 0.95, 0.89);
  inclusiveCrossSectionLjetsLeg->SetFillStyle(0);
  inclusiveCrossSectionLjetsLeg->SetBorderSize(0);
  inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveData  , "2010 data "+lum+" nb ^{-1}" , "PL");
  inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveMCGen , "gen MC (t #bar{t} & W+jets)",  "P");
  //  inclusiveCrossSectionLjetsLeg->AddEntry( sigmaLjetsInclusiveMCReco, "l+jets reco MC + corrections", "L" );
  // (ii) top
  TLegend *inclusiveCrossSectionTopLeg =  new TLegend(0.39, 0.40, 0.95, 0.78);
  inclusiveCrossSectionTopLeg->SetFillStyle (1001);
  inclusiveCrossSectionTopLeg->SetFillColor(kWhite);
  inclusiveCrossSectionTopLeg->SetBorderSize(0);
  inclusiveCrossSectionTopLeg->SetHeader("top cross section (chosen phase space)");
  inclusiveCrossSectionTopLeg->AddEntry( sigmaTopInclusiveDataBtag  , "2010 data "+lum+" nb ^{-1}, b-tag"   , "PL");
  inclusiveCrossSectionTopLeg->AddEntry( sigmaTopInclusiveDataNoBtag, "2010 data "+lum+" nb ^{-1}, W-estim.", "PL");
  inclusiveCrossSectionTopLeg->AddEntry( sigmaTopInclusiveMCGen     , "gen MC t #bar{t}"                    , "P ");
  //  inclusiveCrossSectionTopLeg->AddEntry( sigmaTopInclusiveMCReco    , "l+jets reco MC +corr., use btag"        , "P ");
  // g)  create legends for DIFFERNTIAL TOP cross sections
  TLegend *differentialTopLeg = new TLegend(0.45, 0.65, 0.95, 0.89);
  differentialTopLeg->SetFillStyle(0);
  differentialTopLeg->SetBorderSize(0);
  differentialTopLeg->AddEntry( histo_["pt top"][kData  ][Njets_[4]]  , "2010 data "+lum+" nb ^{-1}, b-tag", "PL");
  differentialTopLeg->AddEntry( histo_["pt top"][kGenBkg][Njets_[3]]  , "gen t #bar{t} semilept. #mu"      , "F");
  differentialTopLeg->AddEntry( histo_["pt top"][kGenSig][Njets_[3]]  , "gen t #bar{t} other"              , "F");
  // h)  create legends for inclusive TOP cross section extrapolated to whole phase space
TLegend *inclusiveCrossSectionTopLeg2 =  new TLegend(0.39, 0.40, 0.95, 0.78);
  inclusiveCrossSectionTopLeg2->SetFillStyle (1001);
  inclusiveCrossSectionTopLeg2->SetFillColor(kWhite);
  inclusiveCrossSectionTopLeg2->SetBorderSize(0);
  inclusiveCrossSectionTopLeg2->SetHeader("inclusive cross section ( t #bar{t} )");
  inclusiveCrossSectionTopLeg2->AddEntry( sigmaTopExtrapolatedData  , "2010 data "+lum+" nb ^{-1}, b-tag,", "PL");
  inclusiveCrossSectionTopLeg2->AddEntry( sigmaTopExtrapolatedTheory, "theory"                            , "PL");

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;
  // a) canvas for yield and diff norm xsec (also legends) and event composition
  for(int idx=0; idx<=79; idx++){ 
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
  //    define styling for yield plots [MC sample]
  // ---
  std::vector<int> color_, fillstyle_, markerStyle_, filled_;
  std::vector<double> markerSize_;
  // set values:             ( kSig, kBkg , kWjets, kZjets, kQCD , kData  )
  int    color       [ 6 ] = { kRed, kBlue, 8     , 6     , 17   , kBlack };
  int    fillstyle   [ 6 ] = { 3006, 3007 , 3004  , 3005  , 1001 , 1001   };
  int    markerStyle [ 6 ] = { 22  , 20   , 23    , 21    , 29   , 22     };
  double markerSize  [ 6 ] = { 1.0 , 1.0  , 1.0   , 1.0   , 1.0  , 1.8    };
  int    filled      [ 6 ] = { 1   , 1    , 1     , 1     , 1    , 0      };
  color_      .insert( color_      .begin(), color      , color       + 6 );
  fillstyle_  .insert( fillstyle_  .begin(), fillstyle  , fillstyle   + 6 );
  markerStyle_.insert( markerStyle_.begin(), markerStyle, markerStyle + 6 );
  markerSize_ .insert( markerSize_ .begin(), markerSize , markerSize  + 6 );
  filled_     .insert( filled_     .begin(), filled     , filled      + 6 );

  // ---
  //    do the printing for event yield plots (all MC samples, all jet multiplicities and all variables)
  // ---
  // loop jet multiplicities (also btag)
  for(int mult=0; mult<6; ++mult){
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      // adress canvas with correct name
      MyCanvas[canvasNumber]->cd(0);
      MyCanvas[canvasNumber]->SetTitle(variables_[var]+"EventYield"+lum+"nb"+Njets_[mult]);
      // a) MC samples (loop)
      for(int idx=kQCD; idx>=kSig; --idx){
	// set axis for plots
	if(idx==kQCD){
	  if(variables_[var]=="phi") axesStyle(*histo_[yield_[var]][kQCD][Njets_[mult]], "#"+variables_[var]+" ( #mu )", "events / binWidth", 0., 2*(histo_[yield_[var]][kQCD][Njets_[mult]]->GetMaximum()), 0.06, 1.4);
	  if(variables_[var]=="eta") axesStyle(*histo_[yield_[var]][kQCD][Njets_[mult]], "#"+variables_[var]+" ( #mu )", "events / binWidth", 0., 2*(histo_[yield_[var]][kQCD][Njets_[mult]]->GetMaximum()), 0.06, 1.4);
	  if(variables_[var]=="pt" ) axesStyle(*histo_[yield_[var]][kQCD][Njets_[mult]], "p_{t} ( #mu )", "events / binWidth", 0., 2*histo_[yield_[var]][kQCD][Njets_[mult]]->GetMaximum(), 0.06, 1.4);
	   }									
	// draw MC histos
	if(idx==kQCD ){
	  // color style
	  histogramStyle(*histo_[yield_[var]][idx][Njets_[mult]], color_[idx], 1 ,markerStyle_[idx], markerSize_[idx], filled_[idx], fillstyle_[idx]);	
	  histo_[yield_[var]][idx][Njets_[mult]]->Draw("HIST");	
	}
	else {
	  // white style to have no overlapping
	  histogramStyle(*histo_[yield_[var]][idx][Njets_[mult]], 10, 1 ,markerStyle_[idx], markerSize_[idx], filled_[idx], 1001);
	  histo_[yield_[var]][idx][Njets_[mult]]->DrawClone("HIST same");
	  // color style
	  histogramStyle(*histo_[yield_[var]][idx][Njets_[mult]], color_[idx], 1 ,markerStyle_[idx], markerSize_[idx], filled_[idx], fillstyle_[idx]);		
	  histo_[yield_[var]][idx][Njets_[mult]]->Draw("HIST same");
	}
      }
	// b) data
	histogramStyle(*histo_[yield_[var]][kData][Njets_[mult]], color_[kData], 1 ,markerStyle_[kData], markerSize_[kData], filled_[kData], fillstyle_[kData]);
	histo_[yield_[var]][kData][Njets_[mult]]->Draw("psame");
	// c) redraw axis
	histo_[yield_[var]][kQCD][Njets_[mult]]->Draw("AXIS same");
	// d) draw jet multiplicity label
	jetMultiplicity_[mult]->Draw("same");
	// move to next canvas
	++canvasNumber;	
    }
  }

  // ---
  //    do the printing for DIFFERENTIAL NORMALIZED l+jets cross section (all l+jets MC and data )
  // ---
  // loop jet multiplicities (also btag)
  for(int mult=0; mult<6; ++mult){
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      // adress canvas with correct name
      MyCanvas[canvasNumber]->cd(0);
      MyCanvas[canvasNumber]->SetTitle(variables_[var]+"DiffNormXSec"+lum+"nb"+Njets_[mult]);
      // loop samples
      for(int idx=kLepJets; idx>=kData; --idx){
	// set style for histos
	// a) for MC
	if(idx==kLepJets){
	  histogramStyle(*histo_[ljetsXSec_[var]][idx][Njets_[mult]], kRed, 1 , 23, markerSize_[kData], 0, 1001);
	  // set axis for plots

	  if((variables_[var]=="phi")||(variables_[var]=="eta")){
	    axesStyle(*histo_[ljetsXSec_[var]][idx][Njets_[mult]], "#"+variables_[var]+" ( #mu )", "#frac{1}{#sigma} #frac{d#sigma}{d#"+variables_[var]+" (#mu)}", 0., 0.6, 0.055, 1.5);
	  }
	  if(variables_[var]=="pt") {
	    axesStyle(*histo_[ljetsXSec_[var]][idx][Njets_[mult]], "p_{t} ( #mu )", "#frac{1}{#sigma} #frac{d#sigma}{dp_{t} (#mu)}", 0., 0.04, 0.055, 1.5);
	  }
	}
	// b) for data
	if(idx==kData){
	  histogramStyle(*histo_[ljetsXSec_[var]][idx][Njets_[mult]], kBlack, 1 , 22, markerSize_[kData], 0, 1001);
	}
	// draw histos
	if(idx==kLepJets) histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Draw("HIST");
	if(idx==kData   ) histo_[ljetsXSec_[var]][idx][Njets_[mult]]->Draw("psame");
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
      MyCanvas[canvasNumber]->SetTitle(variables_[var]+"DiffXSec"+lum+"nb"+Njets_[mult]);
      // loop samples
      for(int idx=kLepJets; idx>=kData; --idx){
	// set style for histos
	// a) for MC
	if(idx==kLepJets){
	  histogramStyle(*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], kRed, 1 , 23, markerSize_[kData], 0, 1001);
	  // set axis for plots

	  if((variables_[var]=="phi")||(variables_[var]=="eta")){
	    axesStyle(*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], "#"+variables_[var]+" ( #mu )", "#frac{d#sigma}{d#"+variables_[var]+" (#mu)}", 0., 2*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->GetMaximum(), 0.055, 1.5);
	  }
	  if(variables_[var]=="pt") {
	    axesStyle(*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], "p_{t} ( #mu )", "#frac{d#sigma}{dp_{t} (#mu)}", 0., 2*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->GetMaximum(), 0.055, 1.5);
	  }
	}
	// b) for data
	if(idx==kData){
	  histogramStyle(*histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]], kBlack, 1 , 22, markerSize_[kData], 0, 1001);
	}
	// draw histos
	// a) MC
	if(idx==kLepJets){
	  histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->Draw("HIST");
	  if(mult<4){
	    for(int gen=kGenW; gen>=kGenSig; --gen){
	      // white style ->Draw ->colour syle ->Draw to have no overlapping
	      histogramStyle(*histo_[ljetsGen_[var]][gen][Njets_[mult]], 10, 1 ,markerStyle_[gen-9], markerSize_[gen-9], filled_[gen-9], 1001);
	      histo_[ljetsGen_[var]][gen][Njets_[mult]]->DrawClone("Hist same");
	      histogramStyle(*histo_[ljetsGen_[var]][gen][Njets_[mult]], color_[gen-9], 1 ,markerStyle_[gen-9], markerSize_[gen-9], filled_[gen-9], fillstyle_[gen-9]);
	      histo_[ljetsGen_[var]][gen][Njets_[mult]]->Draw("Hist same");
	    }
	  }
	}
	// b) data
	if(idx==kData   ) histo_[ljetsXSecDiff_[var]][idx][Njets_[mult]]->Draw("psame");
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
	histogramStyle(*histo_[composition_[var]][idx][Njets_[mult]], color_[idx], 1, markerStyle_[idx], 2.0, 0, 1001); 
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
	  histo_[composition_[var]][idx][Njets_[mult]]->Draw("psame");
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
  MyCanvas[canvasNumber] ->SetTitle("inclusiveCrossSectionLjets");
  axesStyle(*sigmaLjetsInclusiveMCReco, "N(jets) #geq", "#sigma ( l+jets ), l:p_{t}>20 GeV & |#eta|<2.1, jets: p_{t}>30GeV) [nb]", 0., 1.1);
  histogramStyle(*sigmaLjetsInclusiveMCReco, kRed  , 1 , 20, 1.0, 0);
  histogramStyle(*sigmaLjetsInclusiveMCGen , kBlue , 1 , 20, 1.0, 0);
  histogramStyle(*sigmaLjetsInclusiveData  , kBlack, 1 , 22, 1.0, 0);
  sigmaLjetsInclusiveMCReco    ->Draw("AXIS" );
  sigmaLjetsInclusiveMCGen     ->Draw("histsame");
  sigmaLjetsInclusiveMCGen     ->Draw("phistsame");
  sigmaLjetsInclusiveData      ->Draw("esame"); 
  inclusiveCrossSectionLjetsLeg->Draw("same" );
  ++canvasNumber;

  // b) top without & without Btag
  MyCanvas[canvasNumber]     ->cd(0);
  MyCanvas[canvasNumber]     ->SetTitle("inclusiveCrossSectionTop");
  axesStyle(*sigmaTopInclusiveMCReco, "", "#sigma (t #bar{t}->#mu (p_{t}>20 GeV & |#eta|<2.1) + #geq 4 jets (p_{t}>30GeV)) [nb]", 0., 0.04, 0.05, 1.55);
  histogramStyle(*sigmaTopInclusiveMCReco    , kRed  , 1 , 21, 1.8, 0);
  histogramStyle(*sigmaTopInclusiveMCGen     , kBlue , 1 , 20, 1.8, 0);
  histogramStyle(*sigmaTopInclusiveDataNoBtag, kBlack, 1 , 23, 1.8, 0);
  histogramStyle(*sigmaTopInclusiveDataBtag  , kBlack, 1 , 22, 1.8, 0);
  sigmaTopInclusiveMCReco->GetXaxis()->SetNdivisions (0);
  sigmaTopInclusiveMCReco    ->Draw("AXIS"); 
  sigmaTopInclusiveMCGen     ->Draw("phistsame");
  sigmaTopInclusiveDataNoBtag->Draw("esame");
  sigmaTopInclusiveDataBtag  ->Draw("esame");
  inclusiveCrossSectionTopLeg->Draw("same" );
  ++canvasNumber;

  // c) top with b-tag extrapolated to whole phase space
  MyCanvas[canvasNumber]     ->cd(0);
  MyCanvas[canvasNumber]     ->SetTitle("inclusiveCrossSectionTopExtrapolatedWholePhaseSpace");
  axesStyle(*sigmaTopExtrapolatedTheory, "", "#sigma (t #bar{t}) [pb]", 0., 250, 0.05, 1.55);
  histogramStyle(*sigmaTopExtrapolatedTheory, kRed  , 1 , 20, 1.8, 0);
  histogramStyle(*sigmaTopExtrapolatedData  , kBlack, 1 , 22, 1.8, 0);
  sigmaTopExtrapolatedTheory->GetXaxis()->SetNdivisions (0);
  sigmaTopExtrapolatedTheory  ->Draw("p hist");
  sigmaTopExtrapolatedData    ->Draw("p same");
  inclusiveCrossSectionTopLeg2->Draw("same"  );
  ++canvasNumber;

  // ---
  //    do the printing for the DIFFERENTIAL TOP cross sections
  // --- 
  // a) pt 
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("ptDifferentialTopCrossSectionNjetsFrom4Btag");
  // Draw gen ttbar sig + bkg as stack and data as points on top
  histo_["pt top" ][kGenSig][Njets_[3]]->Add(histo_["pt top" ][kGenBkg][Njets_[3]]);
  axesStyle(*histo_["pt top" ][kGenSig][Njets_[3]], "p_{t} ( #mu )", "#frac{d#sigma}{dp_{t} (#mu)} (t #bar{t})", 0., 2.0*histo_["pt top"][kGenSig][Njets_[3]]->GetMaximum(), 0.05, 1.55);
  histogramStyle(*histo_["pt top" ][kGenSig][Njets_[3]], color_[kGenSig-9] , 1 ,markerStyle_[kGenSig-9], markerSize_[kGenSig-9], filled_[kGenSig-9], fillstyle_[kGenSig-9]);  
  histo_["pt top" ][kGenSig][Njets_[3]]->Draw("hist");
  histogramStyle(*histo_["pt top" ][kGenBkg][Njets_[3]], 10, 1 ,markerStyle_[kGenBkg-9], markerSize_[kGenBkg-9], filled_[kGenBkg-9], 1001);
  histo_["pt top" ][kGenBkg][Njets_[3]]->DrawClone("hist same");
  histogramStyle(*histo_["pt top" ][kGenBkg][Njets_[3]], color_[kGenBkg-9], 1 ,markerStyle_[kGenBkg-9], markerSize_[kGenBkg-9], filled_[kGenBkg-9], fillstyle_[kGenBkg-9]);
  histo_["pt top" ][kGenBkg][Njets_[3]]->Draw("hist same");
  histogramStyle(*histo_["pt top" ][kData  ][Njets_[4]], color_[kData], 1 ,markerStyle_[kData], markerSize_[kData], filled_[kData], fillstyle_[kData]);
  histo_["pt top" ][kData  ][Njets_[4]]->Draw("psame");
  histo_["pt top" ][kGenSig][Njets_[3]]->Draw("axis same");
  jetMultiplicity_[3]->Draw("same");
  differentialTopLeg ->Draw("same");
  ++canvasNumber;
				       
  // b) eta
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("etaDifferentialTopCrossSectionNjetsFrom4Btag");
  // Draw gen ttbar sig + bkg as stack and data as points on top
  histo_["eta top" ][kGenSig][Njets_[3]]->Add(histo_["eta top" ][kGenBkg][Njets_[3]]);
  axesStyle(*histo_["eta top"][kGenSig][Njets_[3]], "#eta ( #mu )", "#frac{d#sigma}{d#eta (#mu)} (t #bar{t})", 0., 2.0*histo_["eta top"][kGenSig][Njets_[3]]->GetMaximum(), 0.05, 1.55);
  histogramStyle(*histo_["eta top" ][kGenSig][Njets_[3]], color_[kGenSig-9] , 1 ,markerStyle_[kGenSig-9], markerSize_[kGenSig-9], filled_[kGenSig-9], fillstyle_[kGenSig-9]);  
  histo_["eta top" ][kGenSig][Njets_[3]]->Draw("hist");
  histogramStyle(*histo_["eta top" ][kGenBkg][Njets_[3]], 10, 1 ,markerStyle_[kGenBkg-9], markerSize_[kGenBkg-9], filled_[kGenBkg-9], 1001);
  histo_["eta top" ][kGenBkg][Njets_[3]]->DrawClone("hist same");
  histogramStyle(*histo_["eta top" ][kGenBkg][Njets_[3]], color_[kGenBkg-9], 1 ,markerStyle_[kGenBkg-9], markerSize_[kGenBkg-9], filled_[kGenBkg-9], fillstyle_[kGenBkg-9]);
  histo_["eta top" ][kGenBkg][Njets_[3]]->Draw("hist same");
  histogramStyle(*histo_["eta top" ][kData  ][Njets_[4]], color_[kData], 1 ,markerStyle_[kData], markerSize_[kData], filled_[kData], fillstyle_[kData]);
  histo_["eta top" ][kData  ][Njets_[4]]->Draw("psame");
histo_["eta top" ][kGenSig][Njets_[3]]->Draw("axis same");
  jetMultiplicity_[3]->Draw("same");
  differentialTopLeg ->Draw("same");
  ++canvasNumber;

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
    MyCanvas[0]->Print(saveTo+"diffX7TeV"+lum+"nbAllJetMultiplicities.pdf(", "pdf");
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+"diffX7TeV"+lum+"nbAllJetMultiplicities.pdf", "pdf");   
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+"diffX7TeV"+lum+"nbAllJetMultiplicities.pdf)", "pdf");
    
    // png
    for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
      MyCanvas[idx]->Print(saveTo+(TString)(MyCanvas[idx]->GetTitle())+".png");      
    }
  }
}

void canvasStyle(TCanvas& canv) 
{
  canv.SetFillStyle   ( 4000 );
  canv.SetLeftMargin  ( 0.20 );
  canv.SetRightMargin ( 0.05 );
  canv.SetBottomMargin( 0.15 );
  canv.SetTopMargin   ( 0.05 );
}

void histogramStyle(TH1& hist, int color, int lineStyle, int markerStyle, float markersize, int filled, int fillStyle) 
{
  hist.SetLineWidth(3);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color);
  hist.SetMarkerColor(color);  
  hist.SetMarkerStyle(markerStyle);
  hist.SetMarkerSize(markersize);
  hist.SetLineStyle(lineStyle);
  if(filled==1){
    hist.SetFillColor(color);
    hist.SetFillStyle(fillStyle);
  }
  else{
    hist.SetFillStyle(0);
  }
}

void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin, float yMax, float yTitleSize, float yTitleOffset) 
{
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

int roundToInt(double value){
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
  //  value-result >=0.5 ? return result+1 : return result;
  if((value-result) >=0.5) return (result+1);
  return result;
}

TString getTStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return (TString)result;
}

TString jetLabel(TString input)
{
  TString label="";
  if(input=="Njets1") label="N(jets) #geq 1";
  if(input=="Njets2") label="N(jets) #geq 2";
  if(input=="Njets3") label="N(jets) #geq 3";
  if(input=="Njets4") label="N(jets) #geq 4";
  if(input=="Njets4Btag") label="N(jets) #geq 4, N(bTags) #geq 1";
  if(input=="Njets3Btag") label="N(jets) #geq 3, N(bTags) #geq 1";
  return label;
}

TString samples(int sampleEnum)
{
  TString output="";
  if(sampleEnum==kSig  ) output ="a) ttbar signal";
  if(sampleEnum==kBkg  ) output ="b) ttbar background";
  if(sampleEnum==kWjets) output ="c) W+jets";
  if(sampleEnum==kZjets) output ="d) Z+jets";
  if(sampleEnum==kQCD  ) output ="e) QCD";
  if(sampleEnum==kData ) output ="f) Data";
  return output;
}

TH1F* divideByBinwidth(TH1F* histo, bool calculateError)
{
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

double getABCDNumbers( TString njets, bool loadValues)
{
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

double getMCEffiencies(TString variable, int bin, int njets, bool loadValues)
{
  // get MC based effiencies for differential plots -> differntial (normalized) cross section
  // if loaded from file: be sure the lines are the wright ones!
  double result =-1;  
  if(!loadValues){
    std::cout << "no effiency correction will be done!" << std::endl;
    return 1.0;
  }
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
    if(variable=="phi") startLine=88; // phi +1 because: listing starts with second bin
    // set # lines between 2 sets of effiencies= #bins(variable)+1 (jetMuliplicityLabel)
    int dist=0;
    if(variable=="pt" ) dist=7;
    if(variable=="eta") dist=5;
    if(variable=="phi") dist=9;
    // get number from file
    result= readLineFromFile(startLine+dist*njets+bin);
  }

  std::cout << "  bin " << bin << ": " << setprecision(3) << fixed << result;
  return result;
}

TString sampleLabel(unsigned int sample)
{
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

double getInclusiveMCEff(TString topORlep, int njets, bool loadValues)
{
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
    if(topORlep=="lep") result= readLineFromFile(startLine+njets);
    if(topORlep=="top") result= readLineFromFile(startLine+jumpToTop+njets);
  }
  std::cout << setprecision(3) << fixed << result;
  return result;
}
