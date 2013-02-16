#include "basicFunctions.h"
#include "TObjArray.h"

void createEntry(TString infostream, std::vector<TString> fileList_, bool save, unsigned int verbose);

void addDistributions(bool save = true, unsigned int verbose=2, 
		      TString inputFolderName="RecentAnalysisRun8TeV",
		      TString dataFile= "/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV/analyzeDiffXData2012ABCAllElec.root:/afs/naf.desy.de/group/cms/scratch/tophh/RecentAnalysisRun8TeV/analyzeDiffXData2012ABCAllMuon.root",
		      std::string decayChannel = "combined"){

  // ============================
  //  Prescription
  // ============================
  // The intention of this macro is to add all plots needed 
  // for the calculation of an additional cross section
  // to the analysis rootfiles (e.g.: reco Plot, gen Plot, 
  // gen-reco correlation plot for MC AND Data)

  // ============================
  //  Set ROOT Style
  // ============================
 
  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  TGaxis::SetMaxDigits(2);
  myStyle.cd();
  gROOT->SetStyle("HHStyle");
  gROOT->ForceStyle();	
  
  // ============================
  //  Name Conventions
  // ============================
  // a) enumerator sample convention (as defined in basicFunctions.h)
  //    kSig,    kBkg,    kZjets,  kWjets, 
  //    kQCD,    kSTop,   kDiBos,  kData, 
  //    kQCDEM1, kQCDEM2, kQCDEM3, kQCDBCE1, kQCDBCE2, kQCDBCE3,  
  //    kWW,     kWZ,     kZZ, 
  //    kSTops,  kSATops, kSTopt,  kSATopt,  kSToptW , kSAToptW};
  //
  // b) decayChannel convention: "elec", "muon"
  //
  // c) enumerator systematic Variations (as defined in basicFunctions.h)
  //
  //         0: sysNo                                                       
  //         1: sysLumiUp                   2: sysLumiDown                 
  //         3: sysPUUp                     4: sysPUDown                   
  //         5: sysJESUp                    6: sysJESDown                  
  //         7: sysJERUp                    8: sysJERDown                  
  //         9: sysLepEffSFNormUp          10: sysLepEffSFNormDown         
  //        11: sysLepEffSFShapeUpEta      12: sysLepEffSFShapeDownEta     
  //        13: sysLepEffSFShapeUpPt       14: sysLepEffSFShapeDownPt      
  //        15: sysBtagSFUp                16: sysBtagSFDown               
  //        17: sysBtagSFShapeUpPt65       18: sysBtagSFShapeDownPt65      
  //        19: sysBtagSFShapeUpEta0p7     20: sysBtagSFShapeDownEta0p7    
  //        21: sysMisTagSFUp              22: sysMisTagSFDown             
  //        23: sysTopScaleUp              24: sysTopScaleDown             
  //        25: sysVBosonScaleUp           26: sysVBosonScaleDown          
  //        27: sysSingleTopScaleUp        28: sysSingleTopScaleDown       
  //        29: sysTopMatchUp              30: sysTopMatchDown             
  //        31: sysVBosonMatchUp           32: sysVBosonMatchDown          
  //        33: sysTopMassUp               34: sysTopMassDown              
  //        35: sysQCDUp                   36: sysQCDDown                  
  //        37: sysSTopUp                  38: sysSTopDown                 
  //        39: sysDiBosUp                 40: sysDiBosDown                
  //        41: sysPDFUp                   42: sysPDFDown                  
  //        43: sysHadUp                   44: sysHadDown                  
  //        45: sysGenMCatNLO              46: sysGenPowheg  
  //        47: ENDOFSYSENUM
  


  // ===========================================
  //  Part A: get list of all relevant rootfiles
  // ===========================================
  TString inputFolder= "/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName;
  std::vector <std::string> decayChannels_;
  if(decayChannel=="combined"){
    decayChannels_.push_back("muon"    );
    decayChannels_.push_back("electron");
  }
  else{
    if(decayChannel=="electron") decayChannels_.push_back("electron");
    if(decayChannel=="muon"    ) decayChannels_.push_back("muon"    );
  }
  std::vector <TString> rootFiles_; 
  // loop decay channels
  for(int channelix =0; channelix<(int)decayChannels_.size(); ++channelix){
    std::string channel=decayChannels_[channelix];
    // all default samples + ttbar Powheg/MC@NLO
    for(int sample = kSig; sample<=kBkgMca; sample++){
      if(!(sample>kQCD&&sample<=kData)&&!((sample==kQCD&&channel.compare("electron")==0)||(sample>=kQCDEM1&&sample<=kQCDBCE3&&channel.compare("muon")==0))) rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysNo, channel));
    }
    // JES+JER for all samples
    for(int sample = kSig; sample<=kSAToptW; sample++){
      for(int sys=sysJESUp; sys<=sysJERDown; ++sys){
	if(!(sample>kQCD&&sample<=kData)&&!((sample==kQCD&&channel.compare("electron")==0)||(sample>=kQCDEM1&&sample<=kQCDBCE3&&channel.compare("muon")==0))) rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sys, channel));
      }
    }
    //Ttbar Scale, Matching and Mass samples
    for(int sample = kSig; sample<=kBkg; sample++){
      rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysTopScaleUp  , channel));       
      rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysTopScaleDown, channel));
      rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysTopMatchUp  , channel));
      rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysTopMatchDown, channel));
      rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysTopMassUp   , channel));
      rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysTopMatchDown, channel));
    }
    // V+jets Scale and Matching Sample
    for(int sample = kZjets; sample<=kWjets; sample++){
      rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysVBosonScaleUp  , channel)); 
      rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysVBosonScaleDown, channel)); 
      rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysVBosonMatchUp  , channel)); 
      rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysVBosonMatchDown, channel));
    }
    // single Top Scale Sample
    for(int sample = kSToptW1; sample<=kSAToptW3; sample++){
      rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysTopScaleUp  , channel)); 
      rootFiles_.push_back(inputFolder+"/"+TopFilename(sample, sysTopScaleDown, channel)); 
    }
  }
  // data
  if(!dataFile.Contains(":")){
    rootFiles_.push_back(dataFile);
  }
  else{
    rootFiles_.push_back(getStringEntry(dataFile,1 , ":"));
    rootFiles_.push_back(getStringEntry(dataFile,42, ":"));
  }
  
  // FIXME: for testing
  TString testfile="./muonDiffXSecSigSummer12PF.root";
  if(testfile!=""){
    rootFiles_.clear();
    rootFiles_.push_back(testfile);
    if(rootFiles_.size()>1){
      std::cout << "ERROR in testfile setup" << std::endl;
      exit(0);
    }
  }
    
  // info output
  if(verbose==1){
    std::cout << "The following files will be considered:" << std::endl;
    for(unsigned int file=0; file<rootFiles_.size(); ++file){
      std::cout << rootFiles_[file] << std::endl;
    }
  }

  // ===========================================
  //  Part B: get list of plots you want to add
  // ===========================================
  TString recoTreeLocation="analyzeTopRecoKinematicsKinFit";
  TString genTreeLocation ="analyzeTopPartonLevelKinematics";
  TString outputRecoFolderLocation=recoTreeLocation;
  TString outputGenFolderLocation=genTreeLocation;
  TString newVarName="topSquarePt";
  TString newVarBinning="16000,0,160000";
  TString expression="topPt*topPt";
  TString eventWeight="weight";
  TString withCondition=" ";
  TString infostream=recoTreeLocation+":"+genTreeLocation+":"+outputRecoFolderLocation+":"+outputGenFolderLocation+":"+newVarName+":"+newVarBinning+":"+expression+":"+eventWeight+":"+withCondition;
  if(verbose>0) std::cout << infostream << std::endl;

  // ===================
  //  Part C: do the job
  // ===================

  createEntry(infostream, rootFiles_, save, verbose);
}

void createEntry(TString infostream, std::vector<TString> fileList_, bool save, unsigned int verbose){

  // extract relavant information from infostream
  TString recoTreeLocation        =getStringEntry(infostream,1,":");
  TString genTreeLocation         =getStringEntry(infostream,2,":");
  TString outputRecoFolderLocation=getStringEntry(infostream,3,":");
  TString outputGenFolderLocation =getStringEntry(infostream,4,":");
  TString newVarName              =getStringEntry(infostream,5,":");
  TString newVarBinning           =getStringEntry(infostream,6,":");
  TString fillFrom                =getStringEntry(infostream,7,":");
  TString eventWeight             =getStringEntry(infostream,8,":");
  TString withCondition           =getStringEntry(infostream,9,":");

  //loop files
  for(unsigned int fileix=0; fileix<fileList_.size(); ++fileix){
    TString name=fileList_[fileix];
    if(verbose>1) std::cout  << std::endl << "processing file " << name << std::endl;
    // check if ttbarSG file is processed
    bool ttbarSG= (name.Contains("Sig")) ? true : false;
    bool ttbarCentral = (ttbarSG&&!(name.Contains("Up")||name.Contains("Down")||name.Contains("Mcatnlo")||name.Contains("Powheg"))) ? true : false;
    // container for values read from tree
    std::map< TString, float > value_;

    // create objects for saving later
    TTree *recotreeSv=0;
    TTree *gentreeSv=0;
    TH1F* newRecPlotSv=0;
    TH2F* newRecGenPlotSv=0;
    TH1F* newGenPlotSv=0;

    // A open file
    TFile* file = TFile::Open(name, "UPDATE");
    if(!file||file->IsZombie()) std::cout << "ERROR: file " << name << " does not exist or is broken" << std::endl;
    else{
      file->cd();
      // B1 open reco tree
      TTree* recotree=(TTree*)(file->Get(recoTreeLocation+"/tree")->Clone());
      if(!recotree||recotree->IsZombie()){
	std::cout << "ERROR: can not load the chosen recotree " << recoTreeLocation+"/tree in file " << name << std::endl;
      }
      else{
	// info output
	if(fileix==0&&verbose>1) std::cout << "recotree: " << recoTreeLocation+"/tree" << std::endl;
	// activate all branches
	recotree->SetBranchStatus("*",1);
	// get all branches from recotree
	TObjArray* branches=recotree->GetListOfBranches();
	// loop all branches
	TObjArrayIter branch(branches);
	TObject* object;
	while ( ( object = branch() ) ) {
	  // get single branch
	  TString branchname=(TString)object->GetName();
	  // info output
	  if(fileix==0&&verbose>1) std::cout << "->reco branch : " << branchname << std::endl;	  
	  // set branch address for access
	  recotree->SetBranchAddress(branchname,(&value_[branchname]));
	}
	// B2a create reco histo
	int nbins =(getStringEntry(newVarBinning,1,",")).Atoi();
	double min=(getStringEntry(newVarBinning,2,",")).Atof();
	double max=(getStringEntry(newVarBinning,3,",")).Atof();
	TH1F* newRecPlot=new TH1F( newVarName, newVarName, nbins , min , max);
	// B2b create reco branch entry 
	Float_t newRec1;
	Float_t newRec2;
	TBranch *newRecBranch1 = recotree->Branch(newVarName+"Lep", &newRec1, newVarName+"Lep"+"/F");
	TBranch *newRecBranch2 = recotree->Branch(newVarName+"Had", &newRec2, newVarName+"Had"+"/F");
	// info output
	if(fileix==0&&verbose>1){
	  std::cout << "will add new reco plot: new TH1F(" << newVarName << ", " << newVarName;
	  std::cout << ", " << nbins <<  ", " << min << ", " << max << ") in " << outputRecoFolderLocation << std::endl;
	  std::cout << "will add new branches " << newVarName+"Lep" << " and " << newVarName+"Had";
	  std::cout << ") in tree " << recoTreeLocation+"/tree" << std::endl;
	}
	// B3a create gen-reco histo
	TH2F* newRecGenPlot;
	Float_t newRecGen1;
	Float_t newRecGen2;
	TBranch *newRecGenBranch1 =0;
	TBranch *newRecGenBranch2 =0;
	if(ttbarSG){
	  newRecGenPlot=new TH2F( newVarName+"_", newVarName+"_", nbins , min , max, nbins , min , max);
	  if(fileix==0&&verbose>1){
	    std::cout << "will add new gen-reco plot: new TH2F(" << newVarName+"_" << ", " << newVarName+"_";
	    std::cout << ", " << nbins <<  ", " << min << ", " << max << ", " << std::endl;
	    std::cout << ", " << nbins <<  ", " << min << ", " << max << ")" << std::endl;
	  }
	  // B3b create gen branch entry 
	  newRecGenBranch1 = recotree->Branch(newVarName+"Lep"+"PartonTruth", &newRecGen1, newVarName+"Lep"+"PartonTruth"+"/F");
	  newRecGenBranch2 = recotree->Branch(newVarName+"Had"+"PartonTruth", &newRecGen2, newVarName+"Had"+"PartonTruth"+"/F");
	}
	// B4 fill reco plots from tree
	// loop recotree
	for(unsigned int event=0; event<recotree->GetEntries(); ++event){
	  recotree->GetEntry(event);
	  // B4a fill rec branch
	  newRec1=value_["topPtLep"]*value_["topPtLep"];
	  newRec2=value_["topPtHad"]*value_["topPtHad"];
	  newRecBranch1->Fill();
	  newRecBranch2->Fill();
	  // B4b fill rec plot
	  newRecPlot->Fill(newRec1, value_["weight"]);
	  newRecPlot->Fill(newRec2, value_["weight"]);
	  // fill rec-gen plot
	  if(newRecGenPlot){
	    newRecGen1=value_["topPtLepPartonTruth"]*value_["topPtLepPartonTruth"];
	    newRecGen2=value_["topPtHadPartonTruth"]*value_["topPtHadPartonTruth"];
	    newRecGenBranch1->Fill();
	    newRecGenBranch2->Fill();
	    newRecGenPlot->Fill(newRecGen1, newRec1, value_["weight"]);
	    newRecGenPlot->Fill(newRecGen2, newRec2, value_["weight"]);	    
	  }
	}
	// copy results
	recotreeSv=(TTree *)recotree->Clone();
	newRecPlotSv=(TH1F*)newRecPlot->Clone();
	newRecGenPlotSv=(TH2F*)newRecGenPlot->Clone();
      } // end if recotree
      if(ttbarSG){
	if(verbose>1) std::cout << "-> ttbarSG file! gen and reco-gen will be derived" << std::endl;
	// C open gen tree
	TTree* gentree=(TTree*)(file->Get(genTreeLocation+"/tree")->Clone());
	if(!gentree||gentree->IsZombie()){
	  std::cout << "ERROR: can not load the chosen gentree " << genTreeLocation+"/tree in file " << name << std::endl;
	}
	else{
	  // info output
	  if(fileix==0&&verbose>1) std::cout << "gentree: " << genTreeLocation+"/tree" << std::endl;
	  // activate all branches
	  gentree->SetBranchStatus("*",1);
	  // get all branches from recotree
	  TObjArray* branches=gentree->GetListOfBranches();
	  // loop all branches
	  TObjArrayIter branch(branches);
	  TObject* object;
	  while ( ( object = branch() ) ) {
	    // get single branch
	    TString branchname=(TString)object->GetName();
	    // info output
	    if(fileix==0&&verbose>1) std::cout << "->gen branch : " << branchname << std::endl;	  
	    // set branch address for access
	    gentree->SetBranchAddress(branchname,(&value_[branchname]));
	  }
	  // C2a create gen histo
	  int nbins =(getStringEntry(newVarBinning,1,",")).Atoi();
	  double min=(getStringEntry(newVarBinning,2,",")).Atof();
	  double max=(getStringEntry(newVarBinning,3,",")).Atof();
	  TH1F* newGenPlot=new TH1F( newVarName, newVarName, nbins , min , max);
	  // C2b create gen branch entry 
	  Float_t newGen1;
	  Float_t newGen2;
	  TBranch *newGenBranch1 = gentree->Branch(newVarName+"Lep", &newGen1, newVarName+"Lep"+"/F");
	  TBranch *newGenBranch2 = gentree->Branch(newVarName+"Had", &newGen2, newVarName+"Had"+"/F");
	  // info output
	  if(fileix==0&&verbose>1){
	    std::cout << "will add new gen plot: new TH1F(" << newVarName << ", " << newVarName;
	    std::cout << ", " << nbins <<  ", " << min << ", " << max << ")" << std::endl;
	  }
	  // C3 fill gen plots from tree
	  // loop gentree
	  for(unsigned int event=0; event<gentree->GetEntries(); ++event){
	    gentree->GetEntry(event);
	    // C3a fill gen branches
	    newGen1=value_["topPtLep"]*value_["topPtLep"];
	    newGen2=value_["topPtHad"]*value_["topPtHad"];
	    newGenBranch1->Fill();
	    newGenBranch2->Fill();
	    // C3b fill gen plot
	    newGenPlot->Fill(newGen1, value_["weight"]);
	    newGenPlot->Fill(newGen2, value_["weight"]);
	  }
	  // D process additional folders
	  if(verbose>1&&ttbarCentral) std::cout << "   -> central ttbarSG file! need to process additional folders for systematic variations" << std::endl;
	  // copy results
	  gentreeSv=(TTree *)gentree->Clone();
	  newGenPlotSv=(TH1F*)newGenPlot->Clone();
	} // end if gentree
      } // end if ttbarSG
      // close file
      std::cout << "TEST3: " << newRecGenPlotSv->GetTitle() << std::endl;   
      file->Close();
      std::cout << "TEST4: " << newRecGenPlotSv->GetTitle() << std::endl;
    } // end if file
    // E saving 
    if(save){
      // E1 for debugging
      std::cout << "E1" << std::endl;
      if(fileList_.size()==1){
	TString debugName=((getStringEntry(name, 42, "/")).ReplaceAll(".root", ""));
	std::cout << "a)" << std::endl;
	if(newRecPlotSv   ) saveToRootFile("test.root", newRecPlotSv   , true, 1, outputRecoFolderLocation+"/"+debugName);
	std::cout << "b)" << std::endl;
	if(newRecGenPlotSv){
	  std::cout << "b1)" << std::endl;
	  std::cout << newRecGenPlotSv->GetTitle() << std::endl;
	  std::cout << "b2)" << std::endl;
	  saveToRootFile("test.root", newRecGenPlotSv, true, 1, outputRecoFolderLocation+"/"+debugName);
	}
	std::cout << "c)" << std::endl;
	if(newGenPlotSv   ) saveToRootFile("test.root", newGenPlotSv   , true, 1, outputGenFolderLocation+"/"+debugName );
      }
      // E2 1D rec 
      std::cout << "E2" << std::endl;
      if(newRecPlotSv   ) saveToRootFile(name, newRecPlotSv   , true, 1, outputRecoFolderLocation);
      // E3 2D rec-gen
      std::cout << "E3" << std::endl;
      if(newRecGenPlotSv) saveToRootFile(name, newRecGenPlotSv, true, 1, outputRecoFolderLocation);
      // E4 1D gen
      std::cout << "E4" << std::endl;
      if(newGenPlotSv   ) saveToRootFile(name, newGenPlotSv   , true, 1, outputGenFolderLocation );
      // E5 reco tree
      std::cout << "E5" << std::endl;
      if(recotreeSv) saveToRootFile(name, recotreeSv, true, 1, outputRecoFolderLocation);
      // E6 gen tree
      std::cout << "E6" << std::endl;
      if(gentreeSv ) saveToRootFile(name, gentreeSv , true, 1, outputGenFolderLocation );
    } // end if save
  } // end loop files
}
