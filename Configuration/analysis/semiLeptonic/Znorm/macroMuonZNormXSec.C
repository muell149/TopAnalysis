// calculates the Z cross section from the yields and the efficiences

#include "macroBasicFunctions.h"

void macroMuonZNormXSec(TString sys="sysNo", bool output=true, bool append=false)
{
  // detailed output for debugging
  int verbose=1;
  applySystematicVariations(sys);
  fillXSecTTbarIncl_();
  if(verbose) std::cout<<"systematic variation: " <<sys<< "; lumi="<<luminosity<<"; effSF="<<effSFAB<<std::endl;
    
  // ------------------------------------------------------------------------------------
  //    open efficiency input files, get efficiencies and correct with effSF
  // ------------------------------------------------------------------------------------
  
  // file with efficiency histos
  TFile *effFile = new TFile(folderResults+whichFile+"_efficiencyHistos.root");
  // map of doubles as container for individual efficiencies
  std::map< TString, double> efficiencies_;
  // name of efficiencies
  TString effNames_[] = {"effRecoVisibleMad","effRecoInclMad","effRecoInclPow"};
  unsigned int NEff = sizeof(effNames_)/sizeof(TString);
  std::cout << "size of effPlots_ array: " << NEff << std::endl;
  // loop over efficiencies except Powheg
  for(unsigned int iEff=0; iEff<NEff-1; iEff++)
  {
    // get efficiencies from histo
    efficiencies_[effNames_[iEff]] = ((TH1F*)effFile->Get(effNames_[iEff]))->GetBinContent(1);
    if(verbose) std::cout<<"Before SF correction: "<<effNames_[iEff]<<": "<<efficiencies_[effNames_[iEff]]<<std::endl;
    // correct efficiencies with effSF
    efficiencies_[effNames_[iEff]] *= effSFAB;
    if(verbose) std::cout<<"After SF correction: "<<effNames_[iEff]<<": "<<efficiencies_[effNames_[iEff]]<<std::endl;
  }
  // calculate total efficiency corrected by Powheg acceptance
  efficiencies_["effRecoInclPow"] = efficiencies_["effRecoInclMad"]*effAccRatioPowOverMad;
  if(verbose) std::cout<<"effRecoInclPow"<<": "<<efficiencies_["effRecoInclPow"]<<std::endl;
  
  // histo with acceptance for Madgraph (not needed, just to save)
  double effAccKinMad = ((TH1F*)effFile->Get("effAccKinMad"))->GetBinContent(1);
  if(verbose) std::cout<<"effAccKinMad: "<<effAccKinMad<<std::endl;
  
  // ------------------------------------------------------------------------------------
  //    open yield input files and get yields
  // ------------------------------------------------------------------------------------
  
  // file with yield histos
  TFile *yieldFile = new TFile(folderResults+whichFile+"_lumiweightedAndAddedHistos.root");
  // map of doubles as container for individual efficiencies
  std::map< int, double> yields_;
  // yield map entry for the summed background (arbitrary number 86)
  yields_[86] = 0;
  for(int idx=kZMuMu; idx<=kData; idx++){
    // get yield from the muon multiplicity bin 2 (i.e. bin #3)
    yields_[idx] = ((TH1F*)yieldFile->Get(sampleEnum(idx)+"_"+"tightMuonPair2ZRes_nMu"))->GetBinContent(3);
    // sum up background
    if(idx!=kZMuMu && idx!= kData) yields_[86] +=yields_[idx];
    if(verbose) std::cout<<"yield("<<sampleEnum(idx)<<") = "<<yields_[idx]<<std::endl;
  }
  if(verbose) std::cout<<"yield(background) = "<<yields_[86]<<std::endl;
  
  // ------------------------------------------------------------------------------------
  //    calculate cross sections from yields and efficiencies
  // ------------------------------------------------------------------------------------
  
  // map of doubles as container for cross sections and cross section ratios
  std::map< TString, double> xSecZ_;
  std::map< TString, double> xSecZRatioMeasOverTheo_;
  std::map< TString, double> xSecRatioTTbarInclOverZ_;
  std::map< TString, double> xSecRatioTTbarVisOverZ_;
  std::map< TString, double> xSecTTbarNorm_;
  double xSecStatErr = 0.;
  // name of efficiencies
  TString xSecNames_[] = {"xSecVisibleMad","xSecInclMad","xSecInclPow"};
  unsigned int NxSec = sizeof(xSecNames_)/sizeof(TString);
  std::cout << "size of xSecPlots_ array: " << NxSec << std::endl;
  
  for(unsigned int iEff=0; iEff<NxSec; iEff++){
    // calculate the Z cross section with the master formula
    xSecZ_[ xSecNames_[iEff]] = (yields_[kData] - yields_[86]) / (efficiencies_[effNames_[iEff]] * luminosity);
    if(verbose) std::cout<<"Z cross section ("<<xSecNames_[iEff]<<") = "<<xSecZ_[ xSecNames_[iEff]]<<std::endl;
    // calculate the ratio between measured and theoretical Z cross section
    xSecZRatioMeasOverTheo_[ xSecNames_[iEff]] = xSecZ_[ xSecNames_[iEff]] / xSecZTheo;
    if(verbose) std::cout<<"Z cross section ratio (meas/theo) ("<<xSecNames_[iEff]<<") = "<<xSecZRatioMeasOverTheo_[ xSecNames_[iEff]]<<std::endl;
    // calculate the ratio between ttbar (inclusive) and Z cross section
    xSecRatioTTbarInclOverZ_[ xSecNames_[iEff]] = xSecTTbarIncl_[sys] / xSecZ_[ xSecNames_[iEff]];
    if(verbose) std::cout<<"Cross section ratio (ttbar inclusive/Z) ("<<xSecNames_[iEff]<<") = "<<xSecRatioTTbarInclOverZ_[ xSecNames_[iEff]]<<std::endl;
    // calculate the ratio between ttbar (visible) and Z cross section
    xSecRatioTTbarVisOverZ_[ xSecNames_[iEff]] = xSecTTbarVisible / xSecZ_[ xSecNames_[iEff]];
    if(verbose) std::cout<<"Cross section ratio (ttbar visible/Z) ("<<xSecNames_[iEff]<<") = "<<xSecRatioTTbarVisOverZ_[ xSecNames_[iEff]]<<std::endl;
    
    // calculate ttbar cross section by normalization to Z cross section
    if(xSecNames_[iEff]!="xSecVisibleMad"){
      xSecTTbarNorm_[ xSecNames_[iEff]] = xSecRatioTTbarInclOverZ_[ xSecNames_[iEff]] * xSecZTheo;
      if(verbose) std::cout<<"***** Normalized ttbar cross section (ttbar meas/Z meas * Z theo) ("<<xSecNames_[iEff]<<") = "<<xSecTTbarNorm_[ xSecNames_[iEff]]<<std::endl;
    }
  }
  // calculate statistical cross section error in %
  xSecStatErr = TMath::Sqrt(yields_[kData]) / (yields_[kData] - yields_[86]);
  if(verbose) std::cout << "Statistical xSec Err= " << xSecStatErr << std::endl;

  // ------------------------------------------------------------------------------------
  //    write and save output
  // ------------------------------------------------------------------------------------
  
  // saves the most important output parameters into text files:
  // fXSec       -> _xSecResults.txt     : cross section values
  // fEffYield   -> _effYieldResults.txt : efficiencies and yields 
  
  if(output){
    std::ofstream fXSec, fEffYield;
    if(append){
      fXSec.open(folderResults+whichFile+"_xSecResults.txt", ios::app);
      fEffYield.open(folderResults+whichFile+"_effYieldResults.txt", ios::app);
    }
    else{
      fXSec.open(folderResults+whichFile+"_xSecResults.txt");
      fEffYield.open(folderResults+whichFile+"_effYieldResults.txt");
      // writing headlines at the beginning
      fXSec << "sysVariation" 
	  <<tab<< "xSecZVisMad" <<tab<< "xSecZInclMad" <<tab<< "xSecZInclPow"
	  <<tab<< "xSecStatErr[%]"
	  <<tab<< "ttbarVis(noVar)" <<tab<< "ttbarIncl"
	  <<tab<< "ttbarOverZMad vis" <<tab<< "ttbarOverZMad incl" <<tab<< "ttbarOverZPow incl"
	  <<tab<< "ZmeasOverTheoMad" <<tab<< "ZmeasOverTheoPow"
	  <<tab<< "ttbarNormMad" <<tab<< "ttbarNormPow"
	  << std::endl;
      fEffYield << "sysVariation"
	  <<tab<< "effRecoVisMad" <<tab<< "effAccKinMad" <<tab<< "effRecoInclMad" <<tab<< "effRecoInclPow"
	  <<tab<< "NData" <<tab<< "NZMuMu" <<tab<< "NBg" <<tab<< "NZTauTau" <<tab<< "NTTbar" <<tab << "NWjets"
	  <<tab<< "NQCD" <<tab<< "NSTop" <<tab<< "NDiBos"
	  << std::endl;
    }
    fXSec << sys 
	// Z cross section
	<<tab<< xSecZ_["xSecVisibleMad"] <<tab<< xSecZ_["xSecInclMad"] <<tab<< xSecZ_["xSecInclPow"]
	// statistical Z cross section error [%]
	<<tab<< xSecStatErr
	// ttbar cross section (visible without sysVar, inclusive with sysVar)
	<<tab<< xSecTTbarVisible <<tab<< xSecTTbarIncl_[sys]
	// ttbar / Z cross section
	<<tab<< xSecRatioTTbarVisOverZ_["xSecVisibleMad"] <<tab<< xSecRatioTTbarInclOverZ_["xSecInclMad"] 
	<<tab<< xSecRatioTTbarInclOverZ_["xSecInclPow"]
	// Z_meas / Z_theo cross section	
	<<tab<< xSecZRatioMeasOverTheo_["xSecInclMad"] <<tab<< xSecZRatioMeasOverTheo_["xSecInclPow"]
	// normalized ttbar cross section
	<<tab<< xSecTTbarNorm_["xSecInclMad"] <<tab<< xSecTTbarNorm_["xSecInclPow"]
	<<std::endl;
    fEffYield << sys
	// efficiencies
	<<tab<< efficiencies_["effRecoVisibleMad"] <<tab<< effAccKinMad 
	<<tab<< efficiencies_["effRecoInclMad"]	<<tab<< efficiencies_["effRecoInclPow"]
	// yields
	<<tab<< yields_[kData] <<tab<< yields_[kZMuMu] <<tab<< yields_[86] <<tab<< yields_[kZTauTau]
	<<tab<< yields_[kTTbar] <<tab<< yields_[kWjets] <<tab<< yields_[kQCD] <<tab<< yields_[kSTop]
	<<tab<< yields_[kDiBos]
	<<std::endl;
    fXSec.close();
    fEffYield.close();
    std::cout << "Output files " << folderResults+whichFile+"_xSecResults.txt" << " and _effYieldResults.txt written"
	      << std::endl;
  }
  else std::cout << "No output file written" << std::endl;
  
}
