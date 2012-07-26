#include<iostream>
#include<fstream>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>

void load_Analysis(){

  ifstream infile ("selectionList.txt");
  TString filename;

  while(!infile.eof()){
    infile>>filename;
    TString file="";
    //channel selection for later BTag eff
    if(filename!=""){
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
