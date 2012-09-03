#include<iostream>
#include<fstream>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>

void load_Analysis(){
   
  int filecounter = 0;

  ifstream infile ("selectionList.txt");
  TString filename;

  while(!infile.eof()){
    infile>>filename;
    filecounter++;    

    TString file="";
    //channel selection for later BTag eff
    if(filename!=""){
        std::cout << std::endl;
        std::cout << "PROCESSING File " << filecounter << " ("<< filename << ") from selectionList.txt" << std::endl;
        std::cout << std::endl;
  
        if(filename.Contains("/mumu/"))    {file = TString("BTagEff/mumu/ttbarsignalplustau.root");}
        else if(filename.Contains("/emu/")){file = TString("BTagEff/emu/ttbarsignalplustau.root");}
        else if(filename.Contains("/ee/")) {file = TString("BTagEff/ee/ttbarsignalplustau.root");}
        else{file = TString("BTagEff/mumu/ttbarsignalplustau.root");}

        TFile *f1 = TFile::Open(filename);
        TDirectory *d1 = (TDirectory*)f1->Get("NTupDir");
        TTree *t1 = (TTree*)d1->Get("NTuple");
        t1->Process("Analysis.C+", file);
    }
  }
}
