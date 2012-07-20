#include "basicFunctions.h"
#include "TTree.h"

void checkSample(TString inputFolderName, unsigned int sample, unsigned int sys, const std::string decayChannel, unsigned int verbose);

void checkDuplicatedMCEvents(TString inputFolderName="RecentAnalysisRun", unsigned int verbose=0){
  
  //a) leptons
  std::vector<std::string> leptons_;
  leptons_.push_back("muon"    );
  leptons_.push_back("electron");
  // b) BG processes
  //    (based on enum samples in basicFunctions.h)
  std::vector<int> samples_;
  samples_.push_back(kSig);
  samples_.push_back(kBkg);
  samples_.push_back(kWjets);
  // c) systematic variations
  //    (based on enum systematicVariation in basicFunctions.h)
  std::vector<int> sysVariation_;
  sysVariation_.push_back(sysNo);
  sysVariation_.push_back(sysTopScaleUp);
  sysVariation_.push_back(sysTopScaleDown);
  sysVariation_.push_back(sysVBosonScaleUp);
  sysVariation_.push_back(sysVBosonScaleDown);
  //sysVariation_.push_back(sysSingleTopScaleUp);
  //sysVariation_.push_back(sysSingleTopScaleDown);
  sysVariation_.push_back(sysTopMatchUp);
  sysVariation_.push_back(sysTopMatchDown);
  sysVariation_.push_back(sysVBosonMatchUp);
  sysVariation_.push_back(sysVBosonMatchDown);
  // ---
  //    do the combination
  // ---
  // loop all combinations for the parameters
  for(unsigned int lepton=0; lepton<leptons_.size(); ++lepton){
    for(unsigned int sample=0; sample<samples_.size(); ++sample){
      for(unsigned int sys=0; sys<sysVariation_.size(); ++sys){
	// take care of non existing combinations
	if(!(
	     // non ttbar systematics
	     ((samples_[sample]==kSig||samples_[sample]==kSig)&&
	      (sysVariation_[sys]==sysVBosonScaleUp||sysVariation_[sys]==sysVBosonScaleDown||sysVariation_[sys]==sysVBosonMatchUp||sysVariation_[sys]==sysVBosonMatchDown||sysVariation_[sys]==sysSingleTopScaleUp||sysVariation_[sys]==sysSingleTopScaleDown)
	      )
	     // non W+jets statistics
	     ||((samples_[sample]==kWjets)&&
		(sysVariation_[sys]==sysTopScaleUp||sysVariation_[sys]==sysTopScaleDown||sysVariation_[sys]==sysTopMatchUp||sysVariation_[sys]==sysTopMatchDown||sysVariation_[sys]==sysSingleTopScaleUp||sysVariation_[sys]==sysSingleTopScaleDown)
		)
	     )){
	  checkSample(inputFolderName, samples_[sample], sysVariation_[sys], leptons_[lepton], verbose);
	}
      }
    }
  }
}

void checkSample(TString inputFolderName, unsigned int sample, unsigned int sys, const std::string decayChannel, unsigned int verbose){
  // container for values read from tree
  std::map< TString, float > value_;
  // names
  TString analysisFileName="/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName+"/"+TopFilename(sample, sys, decayChannel); 
  TString folder="analyzeTopRecoKinematicsKinFit";
  if(sample==kSig) folder="analyzeTopPartonLevelKinematics";
  // load input file
  TFile* inFile= new TFile(analysisFileName, "read");
  // loading trees
  TTree* tree=(TTree*)(inFile->Get(folder+"/tree"));
  if(!tree||tree->IsZombie()){
    std::cout << "there seems to be a problem with the chosen tree " << folder+"/tree" << std::endl;
    exit(0);  
  }
  // set relevant entries
  tree->SetBranchStatus("*",0);
  tree->SetBranchStatus("eventNumber",1);
  tree->SetBranchAddress("eventNumber",(&value_["eventNumber"]));
  TH1F* evNum=new TH1F("evNum","evNum", 20000000, 0, 20000000.);
  // fill histo
  for(unsigned int event=0; event<tree->GetEntries(); ++event){
    tree->GetEntry(event);
    evNum->Fill(value_["eventNumber"],1);
  }
  if(evNum->GetMaximum()!=1){
    std::cout << std::endl << "ERROR: duplicated events found in " << TopFilename(sample, sys, decayChannel) << "/" << folder << std::endl << std::endl;
  }
  else{
    std::cout << TopFilename(sample, sys, decayChannel) << "/" << folder << " OK" << std::endl;
  }
  //std::vector<TCanvas*> plotCanvas_;
  //addCanvas(plotCanvas_);
  //plotCanvas_[0]->cd();
  //evNum->Draw("");
  //plotCanvas_[0]->Print("test.png");


}
