#include<iostream>
#include<fstream>

void load_long(){

  ifstream infile ("selectionList.txt");
  TString filename;

  while(!infile.eof()){
    infile>>filename;
    if(filename!=""){
      TFile *f1 = TFile::Open(filename);
      TDirectory *d1 = (TDirectory*)f1->Get("NTupDir");
      TTree *t1 = (TTree*)d1->Get("NTuple");
      t1->Process("Analysis.C+");
    }  
  }
}
