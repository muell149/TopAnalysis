#include <map>
#include <vector>
#include <utility>
#include <iostream>

#include "basicFunctions.h"

#include "TDirectory.h"
#include "TClass.h"
#include "TTree.h"

void cpPlots(TFile* infile, TFile* outfile, const std::string& path, int verbose);
//void scanTree(TFile*, const std::string& path, int verbose);
void oneDplotsOnly(int verbose=1, TString file="/scratch/hh/current/cms/user/goerner/combinedDiffXSecSigFall11PFLarge.root") {
  // A load input file
  TFile*inFile = TFile::Open(file, "read");
  if(!inFile||inFile->IsZombie()){
    std::cout << "there seems to be a problem with the chosen input file " << file << std::endl;
    exit(0);
  }
  // B output file
  TString outputFileName=file;
  outputFileName.ReplaceAll(".root", "_noTree.root");
  //inFile->Cp(file, outputFileName);
  //inFile->TFile::Close();
  TFile* outfile = TFile::Open(outputFileName, "RECREATE");
  // C copy plots
  cpPlots(inFile, outfile, "", verbose);
  //scanTree(outfile, "", verbose);
  outfile->TFile::Close();
}

void cpPlots(TFile* infile, TFile* outfile, const std::string& path, int verbose){
  // loop all objects in the file
  infile->cd(path.c_str());
  TIter nextkey(gDirectory->GetListOfKeys());
  TKey *key=0;
  while ( (key = (TKey*)nextkey())) {
    TObject *obj = key->ReadObj();
    if ( (obj->IsA()->InheritsFrom( "TH1" ) && !(obj->IsA()->InheritsFrom( "TH2" )) ) ) {
      // if object is TH1: save it
      if(verbose>1) std::cout << "found object " << path << "/" << obj->GetName() << std::endl;
      outfile->cd(path.c_str());
      obj->Write( key->GetName() );
      // return to input file
      infile->cd(path.c_str());
    }
    else if (obj->IsA()->InheritsFrom( "TDirectory"  ) ) {
      // for a subdirectory:
      if(verbose>0) std::cout << "found subdirectory " << obj->GetName() << std::endl;
      // create foler in output file
      outfile->cd();
      TDirectory *newdir = outfile->mkdir( obj->GetName(), obj->GetTitle() );
      // return to input file
      infile->cd(path.c_str());
      // bubble up
      cpPlots(infile, outfile, newdir->GetName(), verbose);
    }
    delete obj;
  }
}

// void scanTree(TFile* outfile, const std::string& path, int verbose){
//   // loop all objects in the file
//   outfile->cd(path.c_str());
//   TIter nextkey(gDirectory->GetListOfKeys());
//   TKey *key=0;
//   while ( (key = (TKey*)nextkey())) {
//     TObject *obj = key->ReadObj();
//     if ( obj->IsA()->InheritsFrom( "TTree" ) ) {
//       // if object is tree: delete it
//       if(verbose>0) std::cout << "found tree " << path << "/" << obj->GetName() << std::endl;
//     }
//     else if (obj->IsA()->InheritsFrom( "TDirectory"  ) ) {
//       // for a subdirectory: bubble up
//       //if(verbose>0) std::cout << "found subdirectory " << obj->GetName() << std::endl;
//       scanTree(outfile, obj->GetName(), verbose);
//     }
//     else delete obj;
//   }
// }
