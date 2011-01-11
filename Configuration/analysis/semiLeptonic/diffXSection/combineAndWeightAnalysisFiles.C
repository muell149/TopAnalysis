// ---------description----------------------------------------
// ------------------------------------------------------------
// this Makro creates pseudo data by taking the same plot from 
// various MC samples, weighting them concerning luminosity, 
// adding them and applies a poisson smearing for every point
// ------------------------------------------------------------
// adaptions are necessary within areas marked via !!! ... !!! 
// ------------------------------------------------------------

#include <vector>
#include <iostream>
#include <iomanip>
#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TRandom3.h>
#include <string>
#include <TKey.h>
#include <TDirectory.h>

void loadingFiles(TString name);
void loadingHists(TString plot);
void combineFiles(double scalingFactor);
void addAndWeight(TString directory, TString plot, TFile& outputfile, double scalingFactor);
void singleFile(TString name, double scalingFactor);

std::vector<TH1F*> hists_;
std::vector<TFile*> files_;

void combineAndWeightAnalysisFiles(){
  // ---------------------------------------
  // !!! choose your samples and scaling factors !!!
  // ---------------------------------------
  std::vector<TString> name_; 
  // W systematics
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWjetsMadD6TFall10PileUpPF"   );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWjetsMadD6TFall10MatchUpPF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWjetsMadD6TFall10MatchDownPF");
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWjetsMadD6TFall10ScaleUpPF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWjetsMadD6TFall10ScaleDownPF");
  // ttbar systematics
  // a) Sig
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecSigMadD6TFall10ISRFSRdownPF");
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecSigMadD6TFall10ISRFSRupPF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecSigMadD6TFall10MatchDownPF" );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecSigMadD6TFall10MatchUpPF"   );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecSigMadD6TFall10PileUpPF"    );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecSigMadD6TFall10ScaleDownPF" );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecSigMadD6TFall10ScaleUpPF"   );
  // b) Bkg
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecBkgMadD6TFall10ISRFSRdownPF");
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecBkgMadD6TFall10ISRFSRupPF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecBkgMadD6TFall10MatchDownPF" );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecBkgMadD6TFall10MatchUpPF"   );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecBkgMadD6TFall10PileUpPF"    );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecBkgMadD6TFall10ScaleDownPF" );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecBkgMadD6TFall10ScaleUpPF"   );
  // c) All
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecAllMadD6TFall10ISRFSRdownPF");
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecAllMadD6TFall10ISRFSRupPF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecAllMadD6TFall10MatchDownPF" );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecAllMadD6TFall10MatchUpPF"   );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecAllMadD6TFall10PileUpPF"    );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecAllMadD6TFall10ScaleDownPF" );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecAllMadD6TFall10ScaleUpPF"   );
  // DY systematics
  name_.push_back("diffXSecFromSignal/analysisRootFilesGenJetTauBug/muonDiffXSecZjetsMadD6TFall10MatchDownPF");
  name_.push_back("diffXSecFromSignal/analysisRootFilesGenJetTauBug/muonDiffXSecZjetsMadD6TFall10MatchUpPF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesGenJetTauBug/muonDiffXSecZjetsMadD6TFall10ScaleDownPF");
  name_.push_back("diffXSecFromSignal/analysisRootFilesGenJetTauBug/muonDiffXSecZjetsMadD6TFall10ScaleUpPF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesGenJetTauBug/muonDiffXSecZjetsMadD6TFall10PileUpPF"   );
  // single top PU
  // a) s-channel
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecSingleTopSchannelMadZ2Fall10PileUpPF");
  // a) t-channel
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecSingleTopTchannelMadZ2Fall10PileUpPF");
  // a) tw-channel
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecSingleTopTWchannelMadZ2Fall10PileUpPF");
  // VV sample -> scale to 50 / pb
  // WZ
  // a) std
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWZPytia6Z2Fall10PF"       );
  // b) systematics	   
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWZPytia6Z2Fall10JES09PF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWZPytia6Z2Fall10JES11PF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWZPytia6Z2Fall10JERdownPF");
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWZPytia6Z2Fall10JERupPF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWZPytia6Z2Fall10PileUpPF" );
  // WW	
  // a) std
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWWPytia6Z2Fall10PF"       );
  // b) systematics	   
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWWPytia6Z2Fall10JES09PF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWWPytia6Z2Fall10JES11PF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWWPytia6Z2Fall10JERdownPF");
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWWPytia6Z2Fall10JERupPF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecWWPytia6Z2Fall10PileUpPF" );
  // ZZ		
  // a) std
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecZZPytia6Z2Fall10PF"       );
  // b) systematics	   
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecZZPytia6Z2Fall10JES09PF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecZZPytia6Z2Fall10JES11PF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecZZPytia6Z2Fall10JERdownPF");
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecZZPytia6Z2Fall10JERupPF"  );
  name_.push_back("diffXSecFromSignal/analysisRootFilesNoGenJetTauBug/muonDiffXSecZZPytia6Z2Fall10PileUpPF" );

  std::vector<double> scalingFactor_;
  // W+jets
  scalingFactor_.push_back(472.809/471.559);
  scalingFactor_.push_back(472.809/331.174);
  scalingFactor_.push_back(472.809/86.447 );
  scalingFactor_.push_back(472.809/195.384);
  scalingFactor_.push_back(472.809/154.634);
  //ttbar
  // a) Sig
  scalingFactor_.push_back(8293.219/7756.597);
  scalingFactor_.push_back(8293.219/8850.857);
  scalingFactor_.push_back(8293.219/5955.587);
  scalingFactor_.push_back(8293.219/6580.902);
  scalingFactor_.push_back(8293.219/8134.838);
  scalingFactor_.push_back(8293.219/6977.594);
  scalingFactor_.push_back(8293.219/7322.133);
  // b) Bkg
  scalingFactor_.push_back(8293.219/7756.597);
  scalingFactor_.push_back(8293.219/8850.857);
  scalingFactor_.push_back(8293.219/5955.587);
  scalingFactor_.push_back(8293.219/6580.902);
  scalingFactor_.push_back(8293.219/8134.838);
  scalingFactor_.push_back(8293.219/6977.594);
  scalingFactor_.push_back(8293.219/7322.133);
  // c) All
  scalingFactor_.push_back(8293.219/7756.597);
  scalingFactor_.push_back(8293.219/8850.857);
  scalingFactor_.push_back(8293.219/5955.587);
  scalingFactor_.push_back(8293.219/6580.902);
  scalingFactor_.push_back(8293.219/8134.838);
  scalingFactor_.push_back(8293.219/6977.594);
  scalingFactor_.push_back(8293.219/7322.133);
  // DY
  scalingFactor_.push_back(834.556/545.566);
  scalingFactor_.push_back(834.556/547.036);
  scalingFactor_.push_back(834.556/471.178);
  scalingFactor_.push_back(834.556/436.033);
  scalingFactor_.push_back(834.556/833.287);
  // single top PU
  // a) s-channel
  scalingFactor_.push_back(332103.462/332103.462);
  // a) t-channel
  scalingFactor_.push_back(23127.126/23127.126);
  // a) tw-channel
  scalingFactor_.push_back(144118.623/144118.623);
  // WZ
  // a) std
  scalingFactor_.push_back(0.000414625);
  // b) systematics
  scalingFactor_.push_back(0.000414625);
  scalingFactor_.push_back(0.000414625);
  scalingFactor_.push_back(0.000414625);
  scalingFactor_.push_back(0.000414625);
  scalingFactor_.push_back(0.000416349);
  // WW
  // a) std
  scalingFactor_.push_back(0.001042798);
  // b) systematics
  scalingFactor_.push_back(0.001042798);
  scalingFactor_.push_back(0.001042798);
  scalingFactor_.push_back(0.001042798);
  scalingFactor_.push_back(0.001042798);
  scalingFactor_.push_back(0.001042798);
  // ZZ
  // a) std
  scalingFactor_.push_back(0.000139588);
  // b) systematics
  scalingFactor_.push_back(0.000139588);
  scalingFactor_.push_back(0.000139588);
  scalingFactor_.push_back(0.000139588);
  scalingFactor_.push_back(0.000139588);
  scalingFactor_.push_back(0.000139588);

  // do the job
  for(unsigned int idx=0; idx<name_.size(); ++idx){
    singleFile(name_[idx], scalingFactor_[idx]);
  }

}

void singleFile(TString name, double scalingFactor){
  // get the files
  loadingFiles(name); 
  // ---------------------------------------
  // !!! definition of output file(name) !!!
  // ---------------------------------------
  std::string path = (string)(name);
  size_t separator = path.find_last_of("/");
  TString file = (TString)(path.substr(separator+1));
  //  std::cout << "path: " << path << std::endl;
  //  std::cout << "separator: " << separator << std::endl;
  //  std::cout << "file: " << file << std::endl;

  TFile f("./diffXSecFromSignal/analysisRootFiles/"+file+".root", "recreate");
  std::cout << "output file: " << "./diffXSecFromSignal/analysisRootFiles/"+file+".root" << std::endl;
  std::cout << "scaling factor: " << setprecision(9) << fixed << scalingFactor;
  // ---------------------------------------------------------
  // !!! list of plots you want to combine !!!
  // and their directories within the input samples
  // example: addAndWeight("MyPlotFolder", "MyPlot", luminosity, f)
  // ---------------------------------------------------------
  TString folder ="";
  TString plot = "";
  // loop files
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    // go to file
    files_[idx]->cd();
    // loop objects in file
    TIter fileIterator(gDirectory->GetListOfKeys());
    TKey *fileKey;
    while( fileKey = (TKey*)fileIterator() ) {
      TObject *fileObject = fileKey->ReadObj(); 
      // check if object is a directory
      if(fileObject->InheritsFrom("TDirectory")){
	folder = (TString)fileObject->GetName();
	std::cout << std::endl << " - folder: " << folder << std::endl << "   plots: ";
	// go to directory
	((TDirectory*)fileObject)->cd();
	// loop objects in directory
	TIter folderIterator(gDirectory->GetListOfKeys());
	TKey *folderKey;
	while( folderKey = (TKey*)folderIterator() ) {
	  TObject *folderObject = folderKey->ReadObj(); 
	  // check if object is a TH1 or TH2
	  if( (folderObject->InheritsFrom("TH1")) || (folderObject->InheritsFrom("TH2"))){
	    plot = folderObject->GetName();
	    addAndWeight(folder, plot, f, scalingFactor);
	  }
	}
      }
    }
    files_[idx]->Close();
  }

  f.Close();
}

void addAndWeight(TString directory, TString plot, TFile& outputfile, double scalingFactor)
{
  // get the histograms, erase existing at the beginning
  hists_.clear();
  loadingHists(directory+"/"+plot);  
  // normalize to luminosity (and add samples)
  combineFiles(scalingFactor);
  // define output plot
  TH1F* weightedPlot=(TH1F*)hists_[files_.size()]->Clone(); 
  // write output to directory
  if(outputfile.GetDirectory(directory)==0){
    outputfile.mkdir(directory);
    outputfile.cd(directory);
  }
  weightedPlot->Write(plot);
  std::cout << " " << plot;
}

void loadingFiles(TString name)
{
  // -----------------------------------------
  // !!! add all contributing samples here !!!
  // -----------------------------------------
  files_.clear();
  files_.push_back(new TFile("./"+name+".root"    ) );
  std::cout << std::endl << std::endl << "input file: " << "./"+name+".root" << std::endl;

}

void loadingHists(TString plot)
{  
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    hists_ .push_back( (TH1F*)files_[idx]->Get(plot) );
  }
}

void combineFiles(double scalingFactor)
{
  // --------------------------------------------
  // !!! define weights concerning luminosity !!!
  // --------------------------------------------
  std::vector<double> weight_;  
  // use scaling factor from above
  // -----------------------------------

  weight_.push_back(scalingFactor);

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    hists_ [idx]->Scale(weight_[idx]);
  }

  hists_ .push_back(hists_[0]);

  for(unsigned int idx=1; idx<files_.size(); ++idx) {
    hists_[files_.size()]->Add(hists_[idx]);
  }

}


