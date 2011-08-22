#include <map>
#include <vector>
#include <utility>
#include <iostream>

#include "TDirectory.h"
#include "TString.h"
#include "TClass.h"
#include "TFile.h"
#include "TKey.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"

using std::make_pair;
void addDir(const std::string& path, const std::vector< std::pair< TFile*, float > >& files, TFile *target, int verbose);
double subSampleLumiweight(TString sample, TString decayChannel, int verbose);

void combineMCsamples(TString sysTag="", TString whichFiles = "singleTop", TString decayChannel="muon", int verbose=1, TString inputFolderName="TOP2011/110819_AnalysisRun") {
  // whichFiles: "singleTop", diBoson, or QCD (only electron)
  // decayChannel: "muon" or "electron"
  std::vector< std::pair< TFile*, float > > files_;
  if(verbose>0){
    std::cout << "chosen decay channel: " << decayChannel << std::endl;
    std::cout << "chosen sample: " << decayChannel << std::endl;    
  }
  TString pathname = "/afs/naf.desy.de/group/cms/scratch/tophh/"+inputFolderName;
  TString samplePreName="";
  if(decayChannel=="muon"    ) samplePreName="muon";
  if(decayChannel=="electron") samplePreName="elec";
  TString outputFilename=pathname+"/"+samplePreName+"DiffXSec";

  // ---
  //    list all files to be added
  // ---
  // single top files
  if(whichFiles == "singleTop"){
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecSingleTopSchannelMadZ2Summer11"+sysTag+"PF.root"),
			       subSampleLumiweight("stopS", decayChannel, verbose)));                         
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecSingleAntiTopSchannelMadZ2Summer11"+sysTag+"PF.root" ), 
			       subSampleLumiweight("santiTopS" , decayChannel, verbose)));
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecSingleTopTchannelMadZ2Summer11"+sysTag+"PF.root"     ), 
			       subSampleLumiweight("stopT"     , decayChannel, verbose)));
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecSingleAntiTopTchannelMadZ2Summer11"+sysTag+"PF.root" ), 
			       subSampleLumiweight("santiTopT" , decayChannel, verbose)));
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecSingleTopTWchannelMadZ2Summer11"+sysTag+"PF.root"    ), 
			       subSampleLumiweight("stopTW"    , decayChannel, verbose)));
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecSingleAntiTopTWchannelMadZ2Summer11"+sysTag+"PF.root"), 
			       subSampleLumiweight("santiTopTW", decayChannel, verbose)));
    outputFilename+="SingleTopMadZ2Summer11"+sysTag+"PF.root";
  }
  // DiBoson files
  else if(whichFiles == "diBoson"){
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecWWPytia6Z2Summer11"+sysTag+"PF.root"), 
			       subSampleLumiweight("WW", decayChannel, verbose)));
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecWZPytia6Z2Summer11"+sysTag+"PF.root"), 
			       subSampleLumiweight("WZ", decayChannel, verbose)));
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecZZPytia6Z2Summer11"+sysTag+"PF.root"),
			       subSampleLumiweight("ZZ", decayChannel, verbose)));               
    outputFilename+="VVPytia6Z2Summer11"+sysTag+"PF.root";
  } 
  // QCD files
  else if(whichFiles == "QCD"&&decayChannel=="electron"){
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecQCDPythiaEM1Z2Summer11"+sysTag+"PF.root" ), 
			       subSampleLumiweight("QCDEM1" , decayChannel, verbose))); 
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecQCDPythiaEM2Z2Summer11"+sysTag+"PF.root" ), 
			       subSampleLumiweight("QCDEM2" , decayChannel, verbose)));
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecQCDPythiaEM3Z2Summer11"+sysTag+"PF.root" ), 
			       subSampleLumiweight("QCDEM3" , decayChannel, verbose)));
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecQCDPythiaBCE1Z2Summer11"+sysTag+"PF.root"), 
			       subSampleLumiweight("QCDBCE1", decayChannel, verbose)));
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecQCDPythiaBCE2Z2Summer11"+sysTag+"PF.root"), 
			       subSampleLumiweight("QCDBCE2", decayChannel, verbose)));
    files_.push_back(make_pair(new TFile(pathname+"/"+samplePreName+"DiffXSecQCDPythiaBCE3Z2Summer11"+sysTag+"PF.root"), 
			       subSampleLumiweight("QCDBCE3", decayChannel, verbose)));
    outputFilename+="QCDPythiaZ2Summer11"+sysTag+"PF.root";
  }
  // ERROR: undefined sample/decayChannel combination
  else{
    std::cout << "ERROR: the combination whichFiles = " << whichFiles << " and " << decayChannel << " is not defined" << std::endl;
    std::cout << "choose whichFiles= singleTop (and decayChannel=muon or electron), QCD (and decayChannel=electron) ";
    std::cout << "or diBoson (and decayChannel=muon or electron)" << std::endl;
    exit(0);
  }
  // ERROR: files not found
  if(files_.empty()){
    std::cout << "ERROR: No files added, will not continue" << std::endl;
    exit(0);
  }
  // define output file
  if(verbose>0) std::cout << "chosen output file: " << outputFilename << std::endl;
  TFile* output_file = TFile::Open(outputFilename, "recreate");
  //  open input files and lumiweight them
  addDir("",files_,output_file, verbose);
  // close output files
  output_file->Close();
}

// helper function to add and weight files
void addDir(const std::string& path, const std::vector< std::pair< TFile*, float > >& files, TFile *target, int verbose) 
{
  // loop all objects ion the file
  std::vector< std::pair< TFile*, float > >::const_iterator first=files.begin();
  first->first->cd(path.c_str());
  TIter nextkey(gDirectory->GetListOfKeys());
  TKey *key;
  while ( (key = (TKey*)nextkey())) {
    // read object from first source file
    first->first->cd(path.c_str());
    TObject *obj = key->ReadObj();
    
    if ( obj->IsA()->InheritsFrom( "TH1" ) ) {
      // descendant of TH1 -> merge it
      TH1 *h1 = (TH1*)obj;
      h1->Sumw2();
      h1->Scale(first->second);
      // loop over all source files and add the content of the
      // correspondant histogram to the one pointed to by "h1"
      for(std::vector< std::pair< TFile*, float > >::const_iterator file=first+1; file!=files.end(); ++file) {
	       
	// make sure we are at the correct directory level by cd'ing to path
	file->first->cd(path.c_str());
	TH1 *h2 = (TH1*)gDirectory->Get( h1->GetName() );
	if ( h2 ) {
	  h2->Sumw2();
	  h1->Add(h2,file->second);
	  delete h2; // don't know if this is necessary, i.e. if
	  // h2 is created by the call to gDirectory above.
	}
      }
    }
    else if (obj->IsA()->InheritsFrom( "TDirectory"  ) ) {
      // for a subdirectory
      
      std::cout << "Found subdirectory " << obj->GetName() << std::endl;
      
      // create a new subdir of same name and title in the target file
      target->cd();
      TDirectory *newdir = target->mkdir( obj->GetName(), obj->GetTitle() );
      
      // newdir is now the starting point of another round of merging
      // newdir still knows its depth within the target file via
      // GetPath(), so we can still figure out where we are in the recursion
      addDir(newdir->GetName(),files,target, verbose);
    }
    if ( obj ) {
      target->cd(path.c_str());
      obj->Write( key->GetName() );
    }
  }
  target->Write();
}

// helper function to get the event weights
double subSampleLumiweight(TString sample, TString decayChannel, int verbose)
{
  // this function derives the lumiweight for the 
  // chosen MC "sample" based on the theoretical cross 
  // section, the number of generated events and the 
  // chosen "luminosity"
  // FIXME: need to add systematic variations
  
  // valid decayChannel entered?
  if(!(decayChannel=="muon" || decayChannel=="electron")){
    std::cout << "ERROR: chosen decaychannel does not correspond to electron or muon, no scaling will be done" << std::endl;
    exit(1);
  }
  // b) define in/output for weight calculation
  double crossSection=1;
  double Nevents=0;
  double weight =0;

  // c) fill #events in sample and cross sections (in / pb)
  // QCD e+jets weights 
  if(sample=="QCDEM1"&&decayChannel=="electron"){
    crossSection=0.0106*236100000; // generator prefilter efficiency * LO PYTHIA crossSection
    Nevents     =35729669;
  }
  else if(sample=="QCDEM2"&&decayChannel=="electron"){
    crossSection=0.061*59440000; // generator prefilter efficiency * LO PYTHIA crossSection
    Nevents     =70392060;
  }
  else if(sample=="QCDEM3"&&decayChannel=="electron"){
    crossSection=0.159*898200; // generator prefilter efficiency * LO PYTHIA crossSection
    Nevents     =8150672;
  }
  else if(sample=="QCDBCE1"&&decayChannel=="electron"){
    crossSection=0.00059*236100000; // generator prefilter efficiency * LO PYTHIA crossSection
    Nevents     =2081560;
  }
  else if(sample=="QCDBCE2"&&decayChannel=="electron"){
    crossSection=0.00242*59440000; // generator prefilter efficiency * LO PYTHIA crossSection
    Nevents     =2030033;
  }
  else if(sample=="QCDBCE3"&&decayChannel=="electron"){
    crossSection=0.0105*898200; // generator prefilter efficiency * LO PYTHIA crossSection
    Nevents     =1082691;
  }
  // single top weights
  else if(sample=="santiTopS"){
    crossSection=1.44;
    Nevents     =137980;
  }
  else if(sample=="stopS"){
    crossSection=3.19;
    Nevents     =259971; 
  }
  else if(sample=="santiTopT"){
    crossSection=22.65;
    Nevents     =1944826;
  }
  else if(sample=="stopT"){
    crossSection=41.92;
    Nevents     =3900171;
  }
  else if(sample=="santiTopTW"){
    crossSection=7.87;
    Nevents     =809984;
  }
  else if(sample=="stopTW"){
    crossSection=7.87;
    Nevents     =814390;
  }
  // diboson weights
  else if(sample=="WW"){
    crossSection=43;
    Nevents     =4225916;
  }
  else if(sample=="WZ"){
    crossSection=18.2;
    Nevents     =4265243;
  }
  else if(sample=="ZZ"){
    crossSection=5.9;
    Nevents     =4187885; 
  }
  else {
    std::cout << "ERROR: unknown sample " << sample << std::endl;
    exit(0);
  }
  // d) calculate weight for 1/pb 
  weight = 1 / ( Nevents / crossSection );
  if(verbose>0){
    std::cout << "sample: "        << sample       << std::endl;
    std::cout << "decay channel: " << decayChannel << std::endl;
    std::cout << "weight: "        << weight       << std::endl;
  }
  return weight;
}
