#include<iostream>
#include<fstream>

void load_Analysis(){

  ifstream mumufile ("selectionlist_mumu.txt");
  ifstream emufile ("selectionlist_emu.txt");
  ifstream eefile ("selectionlist_ee.txt");
  
  TString filename;

  while(!mumufile.eof()){
    mumufile>>filename;
    if(filename!=""){
      TFile *f1 = TFile::Open(filename);
      TDirectory *d1 = (TDirectory*)f1->Get("NTupDir");
      TTree *t1 = (TTree*)d1->Get("NTuple");
      t1->Process("Analysis.C+");
    }  
  }
  while(!emufile.eof()){
    emufile>>filename;
    if(filename!=""){
      TFile *f1 = TFile::Open(filename);
      TDirectory *d1 = (TDirectory*)f1->Get("NTupDir");
      TTree *t1 = (TTree*)d1->Get("NTuple");
      t1->Process("Analysis.C+");
    }  
  }
  while(!eefile.eof()){
    eefile>>filename;
    if(filename!=""){
      TFile *f1 = TFile::Open(filename);
      TDirectory *d1 = (TDirectory*)f1->Get("NTupDir");
      TTree *t1 = (TTree*)d1->Get("NTuple");
      t1->Process("Analysis.C+");
    }  
  }
}
