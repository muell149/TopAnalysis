/// This macro calculates efficiencies (factorised into kinematical acceptance, reconstruction, ID and Iso eff.)
/// No SF is applied at this stage, MC only


#include "macroBasicFunctions.h"

void macroMuonZNormEfficiencies(TString sys="sysNo", bool save = true)
{

    // save all plots into the following folder
    TString saveTo = "./Analysis/results/";
    TString whichFile = "analyzeMuonZNorm";
    // detailed output for debugging
    int verbose=1;
    
  // enum and TString for the 2 different samples (Madgraph and Powheg DY samples)
  enum effSample {kMad, kPow};
  TString strEffSample[]={"Mad","Pow"};

  // ------------------------------------------------------------------------------------
  //    open input files
  // ------------------------------------------------------------------------------------
  std::map<unsigned int, TFile*> files_;
  // for Madgraph the file with the right systematic variation is loaded, for Powheg the only available one
  files_[kMad]=new TFile(getFilename(kZMuMu, whichFile, sys));
  files_[kPow]=new TFile(
         "./Analysis/DYZ2MuMuPowhegOnlyGenStudies/res/analyzeMuonZNorm_DYZ2MuMuPowhegOnlyGenStudies.root");

  // ------------------------------------------------------------------------------------
  //    get histograms
  // ------------------------------------------------------------------------------------
  // a) setup structure
  // create container for all histos (generator, reco and efficiency)
  std::map< TString, std::map <unsigned int, TH1F*> > genHisto_;
  std::map< TString, std::map <unsigned int, TH1F*> > recoHisto_;
  // example: histo_["plotName"][sampleNr]
  // set plot names - same as in .root files
  TString genPlots_[] = {"GeneratorZmumuAnalyzerDiMuFilter/GeneratedZ/h_massZ",
                         "GeneratorZmumuAnalyzerDiMuMassFilter/GeneratedZ/h_massZ",
			 "GeneratorZmumuAnalyzerEtaFilter/GeneratedZ/h_massZ",
			 "GeneratorZmumuAnalyzerPtFilter/GeneratedZ/h_massZ"};
  TString recoPlots_[] ={"tightMuonPair2ZRes/nMu"};

  //std::vector<TString> plots_;
  //plots_.insert( plots_.begin(), plots1D, plots1D + 11 );
  //unsigned int Nplots = Nplots;
  unsigned int NGenPlots = sizeof(genPlots_)/sizeof(TString);
  unsigned int NRecoPlots = sizeof(recoPlots_)/sizeof(TString);
  std::cout << "size of genPlots_ array: " << NGenPlots << std::endl;
  std::cout << "size of recoPlots_ array: " << NRecoPlots << std::endl;

  // b) get histos from files
  // needs: plots_, histo_
  // loop over genPlots
  for(unsigned int plot=0; plot<NGenPlots; ++plot){    
    // loop sample
    for(unsigned int idx=kMad; idx<=kPow; ++idx) {
	  // create plot container
	  TH1* targetPlot;
	  if(files_.count(idx)){
	    files_[idx]->GetObject(genPlots_[plot], targetPlot);
	    // Check if plot exits
	    if(targetPlot){
	      // save plot in corresponding map
	      genHisto_ [genPlots_[plot]][idx] = (TH1F*)files_[idx]->Get(genPlots_[plot]);
	    }
	    else std::cout << "can not find plot "+genPlots_[plot] << " in file "+(TString)(files_[idx]->GetName()) << std::endl;
          }
          else std::cout << "can not find files_["<<idx<<"]" << std::endl;
    }
  }

  // loop over recoPlots for kMad
  for(unsigned int plot=0; plot<NRecoPlots; ++plot){
	  // create plot container
	  TH1* targetPlot;
	  int idx=kMad;
	  if(files_.count(idx)){
	    files_[idx]->GetObject(recoPlots_[plot], targetPlot);
	    // Check if plot exits
	    if(targetPlot){
	      // save plot in corresponding map
	      recoHisto_ [recoPlots_[plot]][idx] = (TH1F*)files_[idx]->Get(recoPlots_[plot]);
	    }
	    else std::cout << "can not find plot "+recoPlots_[plot] << " in file "+(TString)(files_[idx]->GetName()) << std::endl;
          }
          else std::cout << "can not find files_["<<idx<<"]" << std::endl;
  }

  // ------------------------------------------------------------------------------------
  //    calculate efficiencies
  // ------------------------------------------------------------------------------------
  
  // efficiency containers
  std::map< TString, std::map <unsigned int, TH1F*> > effHisto_;
  TString effPlots_ [] = {"effAccDiMuMass", "effAccEta","effAccKin", //acceptances 
                          "effRecoVisible","effRecoInclMad","effRecoVisibleXAcc","effRecoVisibleXAcc", //reco eff
			  "effAccRatioPowOverMad"}; //acceptance ratio mad/pow
  unsigned int NEffPlots = sizeof(effPlots_)/sizeof(TString);
  std::cout << "size of effPlots_ array: " << NEffPlots << std::endl;
  
  //calculate acceptance for samples with genHisots
  for (int idx=kMad; idx<=kPow; idx++){

    //acc of mass constraint wrt total Z-> mu mu  events
    make1BinEffHisto(effHisto_["effAccDiMuMass"][idx], "effAccDiMuMass"+strEffSample[idx], 
		     genHisto_[genPlots_[1]][idx]->GetEntries(),
		     genHisto_[genPlots_[0]][idx]->GetEntries(), verbose);
    
    //acc of eta constraint wrt mass cut
    make1BinEffHisto(effHisto_["effAccEta"][idx], "effAccEta"+strEffSample[idx], 
		      genHisto_[genPlots_[2]][idx]->GetEntries(),
		      genHisto_[genPlots_[1]][idx]->GetEntries(), verbose);
    
    //acc of kinematics (eta, pt) constraint wrt mass cut
    make1BinEffHisto(effHisto_["effAccKin"][idx], "effAccKin"+strEffSample[idx], 
		      genHisto_[genPlots_[3]][idx]->GetEntries(),
		      genHisto_[genPlots_[1]][idx]->GetEntries(), verbose);
  }
  
  // calculate reco and selection efficiency (total, i.e. wrt to all genZEvents in mass window, and visible,
  // i.e. wrt genZEvents in mass window and kinematical acceptance;
  // Madgraph only
  
  //eff of reco events wrt genZEvents in mass window and kinematical acceptance
  make1BinEffHisto(effHisto_["effRecoVisible"][kMad], "effRecoVisible"+strEffSample[kMad], 
		    recoHisto_[recoPlots_[0]][kMad]->GetEntries(),
		    genHisto_ [genPlots_[3]][kMad]->GetEntries(), verbose);
  
  //eff of reco events wrt genZEvents in mass window
  make1BinEffHisto(effHisto_["effRecoInclMad"][kMad], "effRecoIncl"+strEffSample[kMad], 
		    recoHisto_[recoPlots_[0]][kMad]->GetEntries(),
		    genHisto_ [genPlots_[1]][kMad]->GetEntries(), verbose);

  //calculate total efficiency by multiplying visible Mad eff with acceptance (Madgraph)
  effHisto_["effRecoVisibleXAcc"][kMad]=(TH1F*)effHisto_["effRecoVisible"][kMad]->Clone();
  effHisto_["effRecoVisibleXAcc"][kMad]->Multiply(effHisto_["effAccKin"][kMad]);
  effHisto_["effRecoVisibleXAcc"][kMad]->SetName("effRecoVisibleXAccMad");
  effHisto_["effRecoVisibleXAcc"][kMad]->SetTitle("effRecoVisibleXAccMad");
  if(verbose) std::cout<<"effRecoVisibleXAccMad="<<effHisto_["effRecoVisibleXAcc"][kMad]->GetBinContent(1)
	                         <<std::endl;
  
   //calculate total efficiency by multiplying visible Mad eff with acceptance (Powheg)
  effHisto_["effRecoVisibleXAcc"][kPow]=(TH1F*)effHisto_["effRecoVisible"][kMad]->Clone();
  effHisto_["effRecoVisibleXAcc"][kPow]->Multiply(effHisto_["effAccKin"][kPow]);
  effHisto_["effRecoVisibleXAcc"][kPow]->SetName("effRecoVisibleXAccPow");
  effHisto_["effRecoVisibleXAcc"][kPow]->SetTitle("effRecoVisibleXAccPow");
  if(verbose) std::cout<<"effRecoVisibleXAccPow="<<effHisto_["effRecoVisibleXAcc"][kPow]->GetBinContent(1)
	                         <<std::endl;
  
  //calculate ratio of acceptance between Powheg and Madgraph
  effHisto_["effAccRatioPowOverMad"][kMad]=(TH1F*)effHisto_["effAccKin"][kPow]->Clone();
  effHisto_["effAccRatioPowOverMad"][kMad]->Divide(effHisto_["effAccKin"][kMad]);
  effHisto_["effAccRatioPowOverMad"][kMad]->SetName("effAccRatioPowOverMad");
  effHisto_["effAccRatioPowOverMad"][kMad]->SetTitle("effAccRatioPowOverMad");
  if(verbose) std::cout<<"effAccRatioPowOverMad="<<effHisto_["effAccRatioPowOverMad"][kMad]->GetBinContent(1)
	<<std::endl;
  
  // ------------------------------------------------------------------------------------
  //    save and write efficiencies
  // ------------------------------------------------------------------------------------
  
  //save eff histos in root file:
  if(save){
    TFile fOut(saveTo+whichFile+"_efficiencyHistos.root", "recreate");
    for(unsigned int iHistos=0; iHistos<NEffPlots; iHistos++){
      for(int idx=kMad; idx <=kPow; idx++){
	if (effHisto_.count(effPlots_[iHistos])>0 && effHisto_[effPlots_[iHistos]].count(idx)>0)
	  effHisto_[effPlots_[iHistos]][idx]->Write();
      }
    }
    if(verbose) std::cout<<saveTo<<whichFile<<"_efficiencyHistos.root written"<<std::endl;
    fOut.Close();
  }



}
