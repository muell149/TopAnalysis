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

void addDir(const std::string& path, const std::vector< std::pair< TFile*, float > >& files, TFile *target) 
{
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
      // it's a subdirectory
      
      std::cout << "Found subdirectory " << obj->GetName() << std::endl;
      
      // create a new subdir of same name and title in the target file
      target->cd();
      TDirectory *newdir = target->mkdir( obj->GetName(), obj->GetTitle() );
      
      // newdir is now the starting point of another round of merging
      // newdir still knows its depth within the target file via
      // GetPath(), so we can still figure out where we are in the recursion
      addDir(newdir->GetName(),files,target);
    }
    if ( obj ) {
      target->cd(path.c_str());
      obj->Write( key->GetName() );
    }
  }
  target->Write();
}

void combine(TString whichFiles = "") {

  //  open input files and lumiweight them
  std::vector< std::pair< TFile*, float > >  files_;
  if(whichFiles == "pyt"){
    files_.push_back(make_pair(new TFile("./QCD_PRIVATE.root"), 2.37195452084461));
    //files_.push_back(make_pair(new TFile("./QCD_pt0015.root"), 1.41539455617478e+4));
    //files_.push_back(make_pair(new TFile("./QCD_pt0030.root"), 1.14637289967634e+3));
    //files_.push_back(make_pair(new TFile("./QCD_pt0080.root"), 2.86734123781737e+1));
    files_.push_back(make_pair(new TFile("./QCD_pt0170.root"), 8.02976087264932e-1));
    files_.push_back(make_pair(new TFile("./QCD_pt0300.root"), 3.82615953805825e-2));
    files_.push_back(make_pair(new TFile("./QCD_pt0470.root"), 4.07409688459859e-3));
    files_.push_back(make_pair(new TFile("./QCD_pt0800.root"), 1.00197094009259e-4));
    files_.push_back(make_pair(new TFile("./QCD_pt1400.root"), 9.46816267012314e-7));
  }
  else if(whichFiles == "pyt_offi"){
    files_.push_back(make_pair(new TFile("./QCD_pt0015.root"), 1.41539455617478e+4)); 
    files_.push_back(make_pair(new TFile("./QCD_pt0030.root"), 1.14637289967634e+3));
    files_.push_back(make_pair(new TFile("./QCD_pt0080.root"), 2.86734123781737e+1));
    files_.push_back(make_pair(new TFile("./QCD_pt0170.root"), 8.02976087264932e-1));
    files_.push_back(make_pair(new TFile("./QCD_pt0300.root"), 3.82615953805825e-2));
    files_.push_back(make_pair(new TFile("./QCD_pt0470.root"), 4.07409688459859e-3));
    files_.push_back(make_pair(new TFile("./QCD_pt0800.root"), 1.00197094009259e-4));
    files_.push_back(make_pair(new TFile("./QCD_pt1400.root"), 9.46816267012314e-7));
  }
  else if(whichFiles == "pyt_pf"){
    files_.push_back(make_pair(new TFile("./QCD_PRIVATE_pf.root"), 2.37195452084461));
    //files_.push_back(make_pair(new TFile("./QCD_pt0015_pf.root"), 1.41539455617478e+4));
    //files_.push_back(make_pair(new TFile("./QCD_pt0030_pf.root"), 1.14637289967634e+3));
    //files_.push_back(make_pair(new TFile("./QCD_pt0080_pf.root"), 2.86734123781737e+1));
    files_.push_back(make_pair(new TFile("./QCD_pt0170_pf.root"), 8.02976087264932e-1));
    files_.push_back(make_pair(new TFile("./QCD_pt0300_pf.root"), 3.82615953805825e-2));
    files_.push_back(make_pair(new TFile("./QCD_pt0470_pf.root"), 4.07409688459859e-3));
    files_.push_back(make_pair(new TFile("./QCD_pt0800_pf.root"), 1.00197094009259e-4));
    files_.push_back(make_pair(new TFile("./QCD_pt1400_pf.root"), 9.46816267012314e-7));
  }
  else if(whichFiles == "pyt_offi_pf"){
    files_.push_back(make_pair(new TFile("./QCD_pt0015_pf.root"), 1.41539455617478e+4));
    files_.push_back(make_pair(new TFile("./QCD_pt0030_pf.root"), 1.14637289967634e+3));
    files_.push_back(make_pair(new TFile("./QCD_pt0080_pf.root"), 2.86734123781737e+1));
    files_.push_back(make_pair(new TFile("./QCD_pt0170_pf.root"), 8.02976087264932e-1));
    files_.push_back(make_pair(new TFile("./QCD_pt0300_pf.root"), 3.82615953805825e-2));
    files_.push_back(make_pair(new TFile("./QCD_pt0470_pf.root"), 4.07409688459859e-3));
    files_.push_back(make_pair(new TFile("./QCD_pt0800_pf.root"), 1.00197094009259e-4));
    files_.push_back(make_pair(new TFile("./QCD_pt1400_pf.root"), 9.46816267012314e-7));
  }
  else if(whichFiles == "her"){
    files_.push_back(make_pair(new TFile("./QCD_pt0015_her.root"), 5.91335247300995e+4));
    files_.push_back(make_pair(new TFile("./QCD_pt0030_her.root"), 6.00404639376481e+3));
    files_.push_back(make_pair(new TFile("./QCD_pt0080_her.root"), 1.23988447642564e+2));
    files_.push_back(make_pair(new TFile("./QCD_pt0170_her.root"), 3.13110190658749e+0));
    files_.push_back(make_pair(new TFile("./QCD_pt0300_her.root"), 1.91828463455377e-1));
    files_.push_back(make_pair(new TFile("./QCD_pt0470_her.root"), 2.72181698624664e-2));
    files_.push_back(make_pair(new TFile("./QCD_pt0800_her.root"), 1.10598133714728e-3));
    files_.push_back(make_pair(new TFile("./QCD_pt1400_her.root"), 1.02905145257263e-5));
  }
  else if(whichFiles == "her_pf"){
    files_.push_back(make_pair(new TFile("./QCD_pt0015_her_pf.root"), 5.91335247300995e+4));
    files_.push_back(make_pair(new TFile("./QCD_pt0030_her_pf.root"), 6.00404639376481e+3));
    files_.push_back(make_pair(new TFile("./QCD_pt0080_her_pf.root"), 1.23988447642564e+2));
    files_.push_back(make_pair(new TFile("./QCD_pt0170_her_pf.root"), 3.13110190658749e+0));
    files_.push_back(make_pair(new TFile("./QCD_pt0300_her_pf.root"), 1.91828463455377e-1));
    files_.push_back(make_pair(new TFile("./QCD_pt0470_her_pf.root"), 2.72181698624664e-2));
    files_.push_back(make_pair(new TFile("./QCD_pt0800_her_pf.root"), 1.10598133714728e-3));
    files_.push_back(make_pair(new TFile("./QCD_pt1400_her_pf.root"), 1.02905145257263e-5));
  }
  else if(whichFiles == "mad"){
    files_.push_back(make_pair(new TFile("./QCD_pt0100_mad.root"), 6.43670348093246e+1));
    files_.push_back(make_pair(new TFile("./QCD_pt0250_mad.root"), 3.48053627125875e+0));
    files_.push_back(make_pair(new TFile("./QCD_pt0500_mad.root"), 1.22793205379665e-1));
    files_.push_back(make_pair(new TFile("./QCD_pt1000_mad.root"), 4.99620469029250e-3));
  }
  else if(whichFiles == "mad_pf"){
    files_.push_back(make_pair(new TFile("./QCD_pt0100_mad_pf.root"), 6.43670348093246e+1));
    files_.push_back(make_pair(new TFile("./QCD_pt0250_mad_pf.root"), 3.48053627125875e+0));
    files_.push_back(make_pair(new TFile("./QCD_pt0500_mad_pf.root"), 1.22793205379665e-1));
    files_.push_back(make_pair(new TFile("./QCD_pt1000_mad_pf.root"), 4.99620469029250e-3));
  }
  else{
    std::cout << "whichFiles = " << whichFiles << " not defined, leave empty or choose one of the following: _pf, _offi, _offi_pf" << std::endl;
    return;
  }

  if(files_.empty()){
    std::cout << "No files added, processiong stopped!" << std::endl;
    return;
  }
  
  TFile* output_file = TFile::Open("./QCD_" + whichFiles + ".root", "recreate");
  
  addDir("",files_,output_file);
  output_file->Close();
}



