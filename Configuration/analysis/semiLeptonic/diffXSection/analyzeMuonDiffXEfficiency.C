// ---------description---------------------------------
// -----------------------------------------------------
// this Makro determines the inclusive and differential, 
// normalized cross section ( d#sigma/dpt(#mu)/#sigma )
// for pt, eta and phi (of the muon). Additionally, it
// distinguishes between the charge of the muon.
// -----------------------------------------------------

#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TF1.h>

enum styles {kttbarReco, kWjetsReco, kttbarGen, kWjetsGen};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.8, int filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
TH1F* divideByBinwidth(TH1F* histo);
double getMaximumDependingOnNjetsCut(TString plot, TString Njets);
TString jetLabel(TString input);
template <class T>
void writeToFile(T output, TString file="crossSectionCalculation.txt", bool append=1);
TString getTStringFromInt(int i);

void analyzeMuonDiffXEfficiency(double luminosity = 5, bool save = false, bool textoutput=false, bool useNLO=false, TString JES="", TString jetType = "PF")
{
  // ---
  //    main function parameters
  // ---
  // save:       choose whether you want to save every plot as png and all within one ps file
  // textoutput: choose whether you want to save the estimated number of QCD events for data 
  //             in .txt file to share it with other parts of the Analysis
  // luminosity: choose luminosity for scaling of event numbers 
  //             lum is derived from this and used for legend as entry
  TString lum = getTStringFromInt((int)luminosity);
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/efficiency/";
  
  //---
  //   efficiency correction by scale factor (SF) from Tag&Probe
  //---
  // enter SF here (total product of SFs for ID/Iso and trigger efficiency)
  // SF of Nov4ReReco wrt Fall10MC:
  // SF(mu Trigger) = 0.969 +/- 0.002 (RunA and B combined -> think about splitting!!!)
  // SF(muIDIso)    = 0.995 +/- 0.003
  // systematic uncertainty approx. 2-3%
  const double effSF = 0.964155;
  
  // ---
  //    systematic variations
  // ---
  // to absorb systematic variations of JES and top MC
  // within efficiencies, the following parameters exist:
  // bool useNLO=true/false to use MC@NLO / MADGRAPH
  // TString JES=""/"JES11"/"JES09" for an JES-shift of 0/+10/-10 %
  TString TopSample = "Mad";
  if(useNLO) TopSample = "Nlo";

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
  TString whichSample = "/analysisRootFiles";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecAll"+TopSample+"D6TFall10"+JES+jetType+".root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecWjetsMadD6TFall10"+JES+jetType+".root") );
  //files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecZjetsMadFall10"+JES+jetType+".root") );

  // ---
  //    get histograms
  // ---
  // create jet multiplicity indicator
  std::vector<TString> Njets_;
  TString jets[ 6 ] = { "Njets1", "Njets2", "Njets3", "Njets4", "Njets4Btag", "Njets3Btag" };
  Njets_.insert( Njets_.begin(), jets, jets + 6 );
  // create container for all histos
  std::map< TString, std::map <unsigned int, std::map <TString, TH1F*> > > histo_;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // get reco plots
    for(unsigned int idx=kttbarReco; idx<=kWjetsReco; ++idx) {
      histo_["eta"][idx][Njets_[mult]] = (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/eta" );
      histo_["pt" ][idx][Njets_[mult]] = (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/pt"  );
      histo_["phi"][idx][Njets_[mult]] = (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/phi" );
    }
    // get gen plots
    unsigned int multgen = mult;
    // take into account that there are no btag - gen plots
    // -1: Njets4Btag -> Njets4
    // -3: Njets3Btag -> Njets3
    if(multgen==Njets_.size()-2) multgen=mult-1;
    if(multgen==Njets_.size()-1) multgen=mult-3;
    // -3 because plots are within the same rootfile
    for(unsigned int idx=kttbarGen; idx<=kWjetsGen; ++idx) {
      histo_["eta"][idx][Njets_[mult]] = (TH1F*)(files_[idx-2]->Get("analyzeTightMuonCrossSectionGen"+Njets_[multgen]+"/eta")->Clone());
      histo_["pt" ][idx][Njets_[mult]] = (TH1F*)(files_[idx-2]->Get("analyzeTightMuonCrossSectionGen"+Njets_[multgen]+"/pt" )->Clone());
      histo_["phi"][idx][Njets_[mult]] = (TH1F*)(files_[idx-2]->Get("analyzeTightMuonCrossSectionGen"+Njets_[multgen]+"/phi")->Clone()); 
    }
  }
  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;
  // for current spring10 7TeV Mc@Nlo sample (50pb-1)
  // a) Reco
  // ttbar(all) sample 
  if(!useNLO) lumiweight.push_back(0.006029022/50.0*(double)luminosity);
  if(useNLO)  lumiweight.push_back(0.006755505/50.0*(double)luminosity);
  // W+jets MADGRAPH sample
  lumiweight.push_back(0.000105750913/50.0*(double)luminosity);
  // b) Gen
  // ttbar(all) sample 
  if(!useNLO) lumiweight.push_back(0.006029022/50.0*(double)luminosity);
  if(useNLO)  lumiweight.push_back(0.006755505/50.0*(double)luminosity);
  // W+jets MADGRAPH sample
  lumiweight.push_back(0.105750913/50.0*(double)luminosity);

  // create variable indicator for easy handling of pt, eta and phi
  std::vector<TString> variables_;
  variables_.push_back("pt");
  variables_.push_back("eta");
  variables_.push_back("phi");

  // ---
  // do lumiweighting for reco and gen plots
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop gen and reco samples
    for(int idx=kttbarReco; idx<=kWjetsGen; ++idx){
      // loop pt, eta and phi
      for(unsigned int var=0; var<variables_.size(); ++var){
	histo_[variables_[var]][idx][Njets_[mult]]->Scale(lumiweight[idx]);
      }
    }
  }

  // ---  
  //    combination of all MC for gen + reco
  // --- 
  // create additional numerator as indicator for all MC gen/reco plots
  unsigned int allReco = 42;
  unsigned int allGen  = 42*42;
  // 1) create separate MC histos by cloning ttbar plots
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      histo_[variables_[var]][allReco][Njets_[mult]] = (TH1F*)histo_[variables_[var]][kttbarReco][Njets_[mult]]->Clone(); 
      histo_[variables_[var]][allGen ][Njets_[mult]] = (TH1F*)histo_[variables_[var]][kttbarGen ][Njets_[mult]]->Clone(); 
    }
  }

  // 2) add all other MC histos
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      // a) reco    
      for(unsigned int idx=kttbarReco+1; idx<=kWjetsReco; ++idx){
	histo_[variables_[var]][allReco][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][idx][Njets_[mult]]->Clone());
      }
      // b) gen
      for(unsigned int idx=kttbarGen+1; idx<=kWjetsGen; ++idx){
	histo_[variables_[var]][allGen][Njets_[mult]]->Add( (TH1F*)histo_[variables_[var]][idx][Njets_[mult]]->Clone());
      }
    }
  }
  
  // ---  
  //    print out #events (gen / reco) for all pt bins and jet multiplicities
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    std::cout << " # events (gen/reco) within pt(mu) (" << Njets_[mult] << "):" << std::endl;
    // loop bins of pt histogram, start with 2nd!
    for(int idx =2; idx<=histo_["pt" ][allReco][Njets_[mult]]->GetNbinsX()+1; idx++){
      std::cout << "bin "  << idx << ": ( " << histo_["pt"][allGen][Njets_[mult]]->GetBinContent(idx) << " / " <<  histo_["pt"][allReco][Njets_[mult]]->GetBinContent(idx) << " )" << std::endl;
    }
  }
  
  // ---  
  //    calculate efficiency histos via reco / gen
  // ---
  // create additional numerator as indicator for efficiency plots
  //efficiency before SF correction
  unsigned int effNoSF    = 565;
  unsigned int topEffNoSF = 765;
  //efficiency after SF correction
  unsigned int eff    = 566;
  unsigned int topEff = 766;
  // loop jet multiplicities  
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      // differential l+jets efficiencies
      histo_[variables_[var]][effNoSF][Njets_[mult]]=        (TH1F*)histo_[variables_[var]][allReco][Njets_[mult]]->Clone();
      histo_[variables_[var]][effNoSF][Njets_[mult]]->Divide((TH1F*)histo_[variables_[var]][allGen ][Njets_[mult]]->Clone());
      histo_[variables_[var]][eff][Njets_[mult]]    = (TH1F*)histo_[variables_[var]][effNoSF][Njets_[mult]]->Clone();
      histo_[variables_[var]][eff][Njets_[mult]]    ->Scale(effSF);
       // differential top efficiencies
      histo_[variables_[var]][topEffNoSF][Njets_[mult]]=        (TH1F*)histo_[variables_[var]][kttbarReco][Njets_[mult]]->Clone();
      histo_[variables_[var]][topEffNoSF][Njets_[mult]]->Divide((TH1F*)histo_[variables_[var]][kttbarGen ][Njets_[mult]]->Clone());
      histo_[variables_[var]][topEff][Njets_[mult]]    = (TH1F*)histo_[variables_[var]][topEffNoSF][Njets_[mult]]->Clone();
      histo_[variables_[var]][topEff][Njets_[mult]]    ->Scale(effSF);
    }
  }

  // ---  
  //    print out calculated efficiencies l+jets
  // ---
  std::cout << std::endl << "l+jets efficiencies"        << std::endl;
  std::cout << "---------------------------------------" << std::endl;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      std::cout << " efficiency within "+variables_[var]+"(mu) (" << Njets_[mult] << "):" << std::endl;
      // loop bins, start with 2nd for pt!
      for(int idx =1; idx<=histo_[variables_[var]][eff][Njets_[mult]]->GetNbinsX(); idx++){
	if(variables_[var]=="pt"&&idx==1) ++idx;
	// print out effiencies, for pt with overflow bin, for phi with underflow and overflow bin
	if(variables_[var]=="phi"&&idx==1) std::cout << "underflow bin "  << idx-1 << ": " << 
	"noSF: " << histo_[variables_[var]][effNoSF][Njets_[mult]]->GetBinContent(0) <<
	"; with SF: " << histo_[variables_[var]][eff][Njets_[mult]]->GetBinContent(0) <<
	"; SF=" << effSF << std::endl;
	std::cout << "bin "  << idx << ": " << 
	"noSF: " << histo_[variables_[var]][effNoSF][Njets_[mult]]->GetBinContent(idx) <<
	"; with SF: " << histo_[variables_[var]][eff][Njets_[mult]]->GetBinContent(idx) <<
	"; SF=" << effSF << std::endl;
	if((variables_[var]=="pt"||variables_[var]=="phi")&&idx==histo_[variables_[var]][eff][Njets_[mult]]->GetNbinsX()) std::cout << "overflow bin "  << idx+1 << ": " <<
	"noSF: " << histo_[variables_[var]][effNoSF][Njets_[mult]]->GetBinContent(idx+1) <<
	"; with SF: " << histo_[variables_[var]][eff][Njets_[mult]]->GetBinContent(idx+1) <<
	"; SF=" << effSF << std::endl;
      }
    }
  }

  // ---  
  //    print out calculated efficiencies top
  // ---
  // loop jet multiplicities
  std::cout << std::endl << "top efficiencies" << std::endl;
  std::cout << "---------------------------------------" << std::endl;
  // calculation with(4) and without btag(3)
  for(unsigned int mult=4; mult>=3; --mult){
    if(mult==3) std::cout << std::endl << "b) N(jets)>=4:"  << std::endl;
    if(mult==4) std::cout << "a) N(jets)>=4 & N(btags)>=1:" << std::endl;
    // loop pt, eta and phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      std::cout << " efficiency within "+variables_[var]+"(mu) (" << Njets_[mult] << "):" << std::endl;
      // loop bins, start with 2nd for pt!
      for(int idx =1; idx<=histo_[variables_[var]][topEff][Njets_[mult]]->GetNbinsX(); idx++){
	if(variables_[var]=="pt"&&idx==1) ++idx;
	// print out effiencies, for pt with overflow bin, for phi with underflow and overflow bin
	if(variables_[var]=="phi"&&idx==1) std::cout << "underflow bin "  << idx-1 << ": " <<
	"noSF: " << histo_[variables_[var]][topEffNoSF][Njets_[mult]]->GetBinContent(0) <<
	"; with SF: " << histo_[variables_[var]][topEff][Njets_[mult]]->GetBinContent(0) <<
	"; SF=" << effSF << std::endl;
	std::cout << "bin "  << idx << ": " << 
	"noSF: " << histo_[variables_[var]][topEffNoSF][Njets_[mult]]->GetBinContent(idx) <<
	"; with SF: " << histo_[variables_[var]][topEff][Njets_[mult]]->GetBinContent(idx) <<
	"; SF=" << effSF << std::endl;
	if((variables_[var]=="pt"||variables_[var]=="phi")&&idx==histo_[variables_[var]][topEff][Njets_[mult]]->GetNbinsX()) std::cout << "overflow bin "  << idx+1 << ": " <<
	"noSF: " << histo_[variables_[var]][topEffNoSF][Njets_[mult]]->GetBinContent(idx+1) <<
	"; with SF: " << histo_[variables_[var]][topEff][Njets_[mult]]->GetBinContent(idx+1) <<
	"; SF=" << effSF << std::endl;
      }
    }
  }
  
  // ---
  //    calculate inclusive efficiencies for all jet multiplicities (l+jets and top)
  // ---
  std::cout << std::endl << "inclusive efficiencies (N_reco, N_gen, effNoSF, eff)" << std::endl << std::endl;
  std::vector<double> topEffNoSF_, lepEffNoSF_, topEff_, lepEff_;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // get entries
    double allTopGen  = histo_["pt"][kttbarGen ][Njets_[mult]]->Integral(0, histo_["pt"][kttbarGen ][Njets_[mult]]->GetNbinsX()+1);
    double allTopReco = histo_["pt"][kttbarReco][Njets_[mult]]->Integral(0, histo_["pt"][kttbarReco][Njets_[mult]]->GetNbinsX()+1);
    double allLepGen  = histo_["pt"][allGen    ][Njets_[mult]]->Integral(0, histo_["pt"][allGen    ][Njets_[mult]]->GetNbinsX()+1);
    double allLepReco = histo_["pt"][allReco   ][Njets_[mult]]->Integral(0, histo_["pt"][allReco   ][Njets_[mult]]->GetNbinsX()+1); 
    // calculate efficiencies
    // before SF correction
    topEffNoSF_.push_back( allTopReco / allTopGen );
    lepEffNoSF_.push_back( allLepReco / allLepGen );
    // after SF correction
    topEff_.push_back( allTopReco / allTopGen * effSF );
    lepEff_.push_back( allLepReco / allLepGen * effSF );
    // do printout
    std::cout << " --- " << Njets_[mult] << " ---" << std::endl;
    std::cout << "a) l+jets: ( " << allLepReco << " , " << allLepGen << " , " 
              << lepEffNoSF_[mult] << " , " << lepEff_[mult] << " )" << std::endl;
    std::cout << "b) top:    ( " << allTopReco << " , " << allTopGen << " , " 
              << topEffNoSF_[mult] << " , " << topEff_[mult] << " )" << std::endl;
  }

  // ---
  //    calculate and print extrapolation factor for top from chosen to total phase space
  // ---
  // extrapolation = N(ttbar MC gen >=3 jets) / N(ttbar theory)
  // N(ttbar theory) depends on the cross section which MUST be the same like it is 
  // used in the calculation of the lumiweight to cancel out in extrapolation factor
  // (i) set theory cross section
  double sigmaTheory = 157.5;
  // (ii) calculate expected top events for chosen luminosity
  double NTheory = sigmaTheory * luminosity;
  // (iii) calculate number of top events in chosen phase space (gen level)
  double NTop   = histo_["pt"][kttbarGen]["Njets4"]->Integral( 0 , histo_["pt"][kttbarGen]["Njets4"]->GetNbinsX()+1 ); 
  // (iv) get extrapolation factor from chosen to inclusive phase space
  double extrapolation = NTheory / NTop;
  std::cout << "extrapolation factor for top from chosen to inclusive phase space: " << extrapolation  << std::endl;

  // ---       
  //    if textoutput==true: save efficiencies within .txt-file
  // ---  
  // save within different .txt files for systematic variations
  TString MG = "";
  if(useNLO) MG="NLO";
  TString file ="crossSectionCalculation"+MG+JES+jetType+".txt";
  bool append=1;
  // save values
  if(textoutput){
    // a) l+jets pt/eta/phi -efficiency values for each bin -> differential (normalized) lepton + jets cross section
    // loop variables pt, eta, phi
    for(unsigned int var=0; var<variables_.size(); ++var){
      // loop jet multiplicities
      for(unsigned int mult=0; mult<Njets_.size(); ++mult){
	// loop bins
	for(int idx =1; idx<=histo_[variables_[var]][eff][Njets_[mult]]->GetNbinsX(); idx++){
	  // clear existing content of .txt for systematic shifts 
	  if(((useNLO)||(JES!=""))&&var==0) append =0;
	  else append =1; 
	  if(mult==0&&idx==1) writeToFile("MC based l+jets correction factors for "+variables_[var]+"(#mu) in chosen binning:", file, append);
	  if(idx==1)writeToFile("--- "+Njets_[mult]+" ---", file);
	  // start with 2nd bin for pt!
	  if(variables_[var]=="pt"&&idx==1) ++idx;
	  // write effiencies to file, for pt with overflow bin, for phi with underflow and overflow bin
	  if(variables_[var]=="phi"&&idx==1) writeToFile(histo_[variables_[var]][eff][Njets_[mult]]->GetBinContent(0), file);
	  writeToFile(histo_[variables_[var]][eff][Njets_[mult]]->GetBinContent(idx), file);
	  if((variables_[var]=="pt"||variables_[var]=="phi")&&idx==histo_[variables_[var]][eff][Njets_[mult]]->GetNbinsX()) writeToFile(histo_[variables_[var]][eff][Njets_[mult]]->GetBinContent(idx+1), file);
	}
      }
    }
    // b) save efficiencies for inclusive l+jets [Njets] correction -> lepton + jets cross section
    writeToFile("MC based l+jets correction factors inclusive l+jets [N(jets)1-4,4+btag,3+btag]", file);
    // loop jet multiplicities
    for(unsigned int mult=0; mult<Njets_.size(); ++mult){
      writeToFile(lepEff_[mult], file);	
    }
    // c) save efficiencies for inclusive top [Njets] correction -> top cross section
    writeToFile("MC based l+jets correction factors inclusive top [N(jets)1-4,4+btag,3+btag]", file);
    // loop jet multiplicities
    for(unsigned int mult=0; mult<Njets_.size(); ++mult){
      writeToFile(topEff_[mult], file);	
    }    





 
    // d) save efficiencies for differential top correction 
    // (>=4 jets / and + >=1 btag)-> differtential top cross section
    // in two ways: with(4) and without btag(3)
    for(unsigned int mult=4; mult>=3; --mult){
      TString multiplicity = " N(jets)>=4:";
      if(mult==4) multiplicity= " N(jets)>=4 & N(btags)>=1:";
      // (i) pt
      writeToFile("MC based top correction factor differential (PT) for"+multiplicity, file);
      // loop bins (start with 2nd bin, include overflow)
      for(int idx =2; idx<=histo_["pt"][topEff][Njets_[mult]]->GetNbinsX()+1; idx++){
	writeToFile(histo_["pt"][topEff][Njets_[mult]]->GetBinContent(idx), file);	
      }
      // (ii) eta
      writeToFile("MC based top correction factor differential (ETA) for"+multiplicity, file);
      // loop bins
      for(int idx =1; idx<=histo_["eta"][topEff][Njets_[mult]]->GetNbinsX(); idx++){
	writeToFile(histo_["eta"][topEff][Njets_[mult]]->GetBinContent(idx), file);	
      }
    }
    // e) save extrapolation factor to whole phase space
    writeToFile("extrapolation factor top gen >=4 jets -> inclusive", file);
    writeToFile(extrapolation, file);
  }
  
  // ---
  //    division by binwidth to have natural form of spectrum for all histos
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // loop variables
    for(unsigned int var=0; var<variables_.size(); ++var){
      // a) for all MC (gen and reco)  
      divideByBinwidth( histo_[variables_[var]][allGen ][Njets_[mult]]);
      divideByBinwidth( histo_[variables_[var]][allReco][Njets_[mult]]);  
      // b) for single MC plots (gen and reco)
      for(unsigned int idx=kttbarReco; idx<=kWjetsGen; ++idx) {
	divideByBinwidth( histo_[variables_[var]][idx][Njets_[mult]]);
      }
    }
  }

  // ---
  //    set plot style for efficiency plots
  // ---
  // a) colors for different MC plots
  std::vector<int> color_;
  int colors[ 6 ] = { kRed, 6, kBlue, kBlack, kGreen, 14 };
  color_.insert( color_.begin(), colors, colors + 6 );
  // b) markers for different MC plots
  std::vector<int> marker_;
  int markers[ 6 ] = { 20, 21, 23, 22, 29, 29};
  marker_.insert( marker_.begin(), markers, markers + 6 );
  // c) set style of MC plots
  // loop jet multiplicities  
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
     // loop variables
    for(unsigned int var=0; var<variables_.size(); ++var){   
      histogramStyle(*histo_[variables_[var]][eff][Njets_[mult]] , color_[mult]  , 1, marker_[mult]);
    }
  }

  // ---
  //    create legends 
  // ---

  // create a legend (in upper right corner) for gen and reco
  std::vector<TLegend*> genRecoLegend_;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    TLegend *legend = new TLegend(0.24, 0.72, 0.98, 0.93);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    TString jetMultiplicity2=jetLabel(Njets_[mult]);
    legend->SetHeader("MC ("+lum+"pb ^{-1}, "+jetMultiplicity2+")");
    legend->AddEntry( histo_["pt"][allGen ][Njets_[mult]], "gen, #mu+jets selection, (t#bar{t} & W)"         , "PL");
    legend->AddEntry( histo_["pt"][allReco][Njets_[mult]], "reco, semilept.(#mu) selection (t#bar{t}, W & Z)", "PL");
    genRecoLegend_.push_back( legend );
  }

  // create a legend (in upper right corner) for l+jets efficiencies
  TLegend *legendLjets = new TLegend(0.24, 0.86, 0.98, 0.95);
  legendLjets->SetFillStyle(0);
  legendLjets->SetBorderSize(0);
  legendLjets->SetTextSize(0.06);
  legendLjets->SetHeader("t#bar{t} + W#rightarrowl#nu");

  // create a legend (in upper right corner) for top efficiencies
  TLegend *legendTop = new TLegend(0.24, 0.86, 0.98, 0.95);
  legendTop->SetFillStyle(0);
  legendTop->SetBorderSize(0);
  legendTop->SetTextSize(0.06);
  legendTop->SetHeader("t#bar{t} signal");
  //legendTop->AddEntry(histo_["pt"][topEff][Njets_[3]], "N(jets) #geq 4"                 , "PL");
  //legendTop->AddEntry(histo_["pt"][topEff][Njets_[4]], "N(jets) #geq 4, N(btags) #geq 1", "PL");
  
  // create a legend containing all jet multiplicities part 1
  TLegend *leg1 = new TLegend(0.15, 0.05, 0.99, 0.89);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  // N(jets) 1-3
  for(unsigned int mult=0; mult<Njets_.size()-3; ++mult){
    leg1->AddEntry( histo_["pt"][eff][Njets_[mult]], jetLabel(Njets_[mult]), "PL");
  }

  // create a legend containing all jet multiplicities part 2
  TLegend *leg2 = new TLegend(0.01, 0.05, 0.99, 0.89);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  // N(jets) 4, 3+btag, 4+btag
  for(unsigned int mult=Njets_.size()-3; mult<Njets_.size()-1; ++mult){
    leg2->AddEntry( histo_["pt"][eff][Njets_[mult]], jetLabel(Njets_[mult]), "PL");
  }

  // create a legend (in upper right corner) for pt(mu)- gen plot
  std::vector<TLegend*> genLegend_;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    TLegend *legend = new TLegend(0.41, 0.67, 0.99, 0.94);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    TString jetMultiplicity2=jetLabel(Njets_[mult]);
    legend->SetHeader("gen: #mu+jets ("+lum+" pb ^{-1}, "+jetMultiplicity2+")" );
    legend->AddEntry( histo_["pt"][kttbarGen][Njets_[mult]] , "t#bar{t} (MC@NLO)"            , "F");
    legend->AddEntry( histo_["pt"][kWjetsGen][Njets_[mult]] , "W#rightarrowl#nu (Madgraph)"  , "F");
    genLegend_.push_back(legend);
  }
  
  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;
  for(int idx=0; idx<=26; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }
  // canvas for splitted jet multiplicity legends
  MyCanvas.push_back( new TCanvas( "canv"+getTStringFromInt(MyCanvas.size()), "canv"+getTStringFromInt(MyCanvas.size()), 600, 200) );
  canvasStyle(*MyCanvas[MyCanvas.size()-1]);
  MyCanvas.push_back( new TCanvas( "canv"+getTStringFromInt(MyCanvas.size()), "canv"+getTStringFromInt(MyCanvas.size()), 600, 200) );
  canvasStyle(*MyCanvas[MyCanvas.size()-1]);

  // introduce counter for Canvas
  int canvasNumber=0;

  // ---
  //    do the printing for L+JETS inclusive pt ( gen + reco ) (all jet multiplicities)
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    MyCanvas[canvasNumber]->cd(0);
    MyCanvas[canvasNumber]->SetTitle("ptMuGenAndReco"+Njets_[mult]+"Lum5pb@7TeV");
    axesStyle(*histo_["pt"][allGen][Njets_[mult]], "p_{t}(#mu) [GeV]", "events / GeV", 0.,  getMaximumDependingOnNjetsCut("pt",Njets_[mult])/5.0*luminosity, 0.06, 1.5); 
    histogramStyle(*histo_["pt"][allGen ][Njets_[mult]] , kRed  , 1, 20);
    histogramStyle(*histo_["pt"][allReco][Njets_[mult]] , kBlack, 1, 22);
    histo_["pt"][allGen ][Njets_[mult]]->Draw("HIST");
    histo_["pt"][allReco][Njets_[mult]]->Draw("HIST same");
    histo_["pt"][allReco][Njets_[mult]]->Draw("Psame");
    histo_["pt"][allGen ][Njets_[mult]]->Draw("Psame");
    genRecoLegend_[mult]->Draw("same");
    ++canvasNumber;
  }

  // ---
  //    do the printing for L+JETS inclusive eta ( gen + reco )
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("etaMuGenAndReco"+Njets_[mult]+"Lum5pb@7TeV");
  axesStyle(*histo_["eta" ][allGen][Njets_[mult]], "#eta(#mu)", "events", 0.,  getMaximumDependingOnNjetsCut("eta",Njets_[mult])/5.0*luminosity, 0.06, 1.5); 
  histogramStyle(*histo_["eta"][allGen ][Njets_[mult]] , kRed  , 1, 20);
  histogramStyle(*histo_["eta"][allReco][Njets_[mult]] , kBlack, 1, 22);
  histo_["eta"][allGen ][Njets_[mult]]->Draw("HIST");
  histo_["eta"][allReco][Njets_[mult]]->Draw("HIST same");
  histo_["eta"][allReco][Njets_[mult]]->Draw("Psame");
  histo_["eta"][allGen ][Njets_[mult]]->Draw("Psame");
  genRecoLegend_[mult]->Draw("same"); 
  ++canvasNumber;
  }

  // ---
  //    do the printing for L+JETS inclusive phi ( gen + reco )
  // ---
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("phiMuGenAndReco"+Njets_[mult]+"Lum5pb@7TeV");
  axesStyle(*histo_["phi"][allGen][Njets_[mult]], "#phi(#mu)", "events", 0.,  getMaximumDependingOnNjetsCut("phi",Njets_[mult])/8.0*luminosity, 0.06, 1.5); 
  histogramStyle(*histo_["phi"][allGen ][Njets_[mult]] , kRed  , 1, 20);
  histogramStyle(*histo_["phi"][allReco][Njets_[mult]] , kBlack, 1, 22);
  histo_["phi"][allGen ][Njets_[mult]]->Draw("HIST");
  histo_["phi"][allReco][Njets_[mult]]->Draw("HIST same");
  histo_["phi"][allReco][Njets_[mult]]->Draw("Psame");
  histo_["phi"][allGen ][Njets_[mult]]->Draw("Psame");
  genRecoLegend_[mult]->Draw("same");
  ++canvasNumber;
  }

  // ---
  //    do the printing for L+JETS pt-efficiency ( gen / reco ) for all jet multiplicities
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetGrid(1,1);
  MyCanvas[canvasNumber]->SetTitle("ptEfficiencyMCbasedAllJetMultiplicities");
  axesStyle(*histo_["pt" ][eff][Njets_[0]], "p_{t}(#mu) [GeV]" , "#epsilon_{ l+jets}", 0.,  1.); 
  histo_["pt"][eff][Njets_[0]] ->Draw("");
  for(unsigned int mult=0; mult<Njets_.size()-1; ++mult){
    histo_["pt"][eff][Njets_[mult]]->Draw("same");
    histo_["pt"][eff][Njets_[mult]]->Draw("Psame");
  }
  legendLjets->Draw("same");
  ++canvasNumber;

  // ---
  //    do the printing for TOP pt-efficiency ( gen / reco ) >=4 jets with and without btag
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetGrid(1,1);
  MyCanvas[canvasNumber]->SetTitle("ptEfficiencyTopMCbased");
  axesStyle(*histo_["pt" ][topEff][Njets_[4]], "p_{t}(#mu) [GeV]" , "#epsilon_{ t#bar{t}}", 0.,  1.);
  histogramStyle(*histo_["pt"][topEff][Njets_[4]] , color_[4], 1, 29);
  histogramStyle(*histo_["pt"][topEff][Njets_[3]] , color_[3], 1, 22);
  histo_["pt"][topEff][Njets_[4]]->Draw("");
  histo_["pt"][topEff][Njets_[4]]->Draw("Psame");
  histo_["pt"][topEff][Njets_[3]]->Draw("same" );
  histo_["pt"][topEff][Njets_[3]]->Draw("Psame");
  legendTop                      ->Draw("same");
  ++canvasNumber;

  // ---
  //    do the printing for L+JETS eta-efficiency ( gen / reco ) for all jet multiplicities
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetGrid(1,1);
  MyCanvas[canvasNumber]->SetTitle("etaEfficiencyMCbasedAllJetMultiplicities");
  axesStyle(*histo_["eta" ][eff][Njets_[0]], "#eta(#mu)" , "#epsilon_{ l+jets}", 0.,  1.); 
  histo_["eta"][eff][Njets_[0]]->Draw("");
  for(unsigned int mult=0; mult<Njets_.size()-1; ++mult){
    histo_["eta"][eff][Njets_[mult]]->Draw("same");
    histo_["eta"][eff][Njets_[mult]]->Draw("Psame");
  }
  legendLjets->Draw("same");
  ++canvasNumber;

  // ---
  //    do the printing for TOP eta-efficiency ( gen / reco ) >=4 jets with and without btag
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetGrid(1,1);
  MyCanvas[canvasNumber]->SetTitle("etaEfficiencyTopMCbased");
  axesStyle(*histo_["eta" ][topEff][Njets_[4]], "#eta(#mu)" , "#epsilon_{ t#bar{t}}", 0.,  1.); 
  histogramStyle(*histo_["eta"][topEff][Njets_[4]], color_[4], 1, 29);
  histogramStyle(*histo_["eta"][topEff][Njets_[3]], color_[3], 1, 22);
  histo_["eta"][topEff][Njets_[4]]->Draw("");
  histo_["eta"][topEff][Njets_[4]]->Draw("Psame");
  histo_["eta"][topEff][Njets_[3]]->Draw("same" );
  histo_["eta"][topEff][Njets_[3]]->Draw("Psame");
  legendTop                       ->Draw("same" );
  ++canvasNumber;

  // ---
  //    do the printing for L+JETS phi-efficiency ( gen / reco ) for all jet multiplicities
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetGrid(1,1);
  MyCanvas[canvasNumber]->SetTitle("phiEfficiencyMCbasedAllJetMultiplicities");
  axesStyle(*histo_["phi"][eff][Njets_[0]], "#phi(#mu)" , "#epsilon_{ l+jets}", 0.,  1.); 
  histo_["phi"][eff][Njets_[0]]->Draw("");
  for(unsigned int mult=0; mult<Njets_.size()-1; ++mult){
    histo_["phi"][eff][Njets_[mult]]->Draw("same");
    histo_["phi"][eff][Njets_[mult]]->Draw("Psame");
  }
  legendLjets->Draw("same");
  ++canvasNumber;

  // ---
  //    do the printing for L+JETS pt-gen composition
  // ---
  // loop jet multiplicities 
  // -2 : no btag on gen level
  for(unsigned int mult=0; mult<Njets_.size()-2; ++mult){
    MyCanvas[canvasNumber]->cd(0);
    MyCanvas[canvasNumber]->SetTitle("ptGenComposition"+Njets_[mult]);
    histo_["pt"][kWjetsGen][Njets_[mult]]->Add(histo_["pt"][kttbarGen][Njets_[mult]]);
    axesStyle(*histo_["pt"][kWjetsGen][Njets_[mult]], "p_{t}(#mu) [GeV]", "events / GeV", 0., getMaximumDependingOnNjetsCut("pt",Njets_[mult])/8.0*luminosity, 0.06, 1.5); 
    histogramStyle(*histo_["pt"][kWjetsGen][Njets_[mult]], kGreen, 1, 20, 1.5, 1);
    histogramStyle(*histo_["pt"][kttbarGen][Njets_[mult]], kRed  , 1, 20, 1.5, 1);
    histo_["pt"][kWjetsGen][Njets_[mult]]->Draw("");
    histo_["pt"][kttbarGen][Njets_[mult]]->Draw("same");
    genLegend_[mult]->Draw("same");
    ++canvasNumber;
  }
  
  // ---
  //    do the printing for the splitted jet multiplicity legend part 1
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("legendPart1Effiency");
  leg1->Draw("");
  ++canvasNumber;
  
  // ---
  //     do the printing for the splitted jet multiplicity legend part 2
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("legendPart2Effiency");
  leg2->Draw("");

  //  ---
  //  saving
  //  ---
  if(save){  
    // ps
    MyCanvas[0]->Print(saveTo+"efficiencyAllNjets.ps(");
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+"efficiencyAllNjets.ps"  );   
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+"efficiencyAllNjets.ps)"  );
  
    // png
    for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
      MyCanvas[idx]->Print(saveTo+(TString)(MyCanvas[idx]->GetTitle())+".png"  );      
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

void histogramStyle(TH1& hist, int color, int lineStyle, int markerStyle, float markersize, int filled) 
{
  hist.SetLineWidth(3);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color);
  hist.SetMarkerColor(color);  
  hist.SetMarkerStyle(markerStyle);
  hist.SetMarkerSize(markersize);
  hist.SetLineStyle(lineStyle);
  if(filled==1){
  hist.SetFillStyle(1001);
  hist.SetFillColor(color);
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

TH1F* divideByBinwidth(TH1F* histo)
{
  // create output histo
  TH1F* output = (TH1F*)histo->Clone();
  // loop over bins    
  for(int bini=1; bini<= output->GetNbinsX(); bini++){
    output->SetBinContent(bini,((double)(output->GetBinContent(bini))/(double)(output->GetBinWidth(bini)))  );   
  } 
  return output;
}

double getMaximumDependingOnNjetsCut(TString plot, TString Njets)
{
  // create container for histo max values sortet by plot and Njet
  std::map< TString, std::map <TString,double> > maxValues_;  
  // create maximum values for pt, eta, phi ( for 5pb^-1)
  maxValues_["pt" ]["Njets4Btag"]= 55.; 
  maxValues_["pt" ]["Njets3Btag"]= 130.; 
  maxValues_["pt" ]["Njets4"]= 55.;  
  maxValues_["pt" ]["Njets3"]= 130.;
  maxValues_["pt" ]["Njets2"]= 400.;
  maxValues_["pt" ]["Njets1"]= 2200.;
  maxValues_["eta"]["Njets4Btag"]= 60.;  
  maxValues_["eta"]["Njets3Btag"]= 140.; 
  maxValues_["eta"]["Njets4"]= 65.;  
  maxValues_["eta"]["Njets3"]= 140.;
  maxValues_["eta"]["Njets2"]= 450.;
  maxValues_["eta"]["Njets1"]= 2300.;
  maxValues_["phi"]["Njets4Btag"]= 40.;
  maxValues_["phi"]["Njets3Btag"]= 80.; 
  maxValues_["phi"]["Njets4"]= 35.;  
  maxValues_["phi"]["Njets3"]= 80.;
  maxValues_["phi"]["Njets2"]= 260.;
  maxValues_["phi"]["Njets1"]= 1200.;
  // get maximum value
  return maxValues_.find(plot)->second.find(Njets)->second;
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

TString getTStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return (TString)result;
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
