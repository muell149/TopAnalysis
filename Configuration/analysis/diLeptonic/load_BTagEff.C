#include<iostream>
#include<fstream>
#include<stdio.h>
#include<TString.h>
#include<TFile.h>
#include<TTree.h>
#include <stdio.h>


void load_BTagEff(){

    std::vector<TString> channel;
    channel.push_back("mumu"); channel.push_back("emu"); channel.push_back("ee"); 
     
    TString file=TString("BTagJetEff.txt");
    remove(file);
    std::cout<<file<<" removed"<<std::endl;
//     remove("BTagJetEff.txt");
//     std::cout<<"file removed"<<std::endl;
    
    for (int i=0; i<(int)channel.size(); ++i){
        TFile *f1 = TFile::Open("mergedRoot/Nominal/"+channel[i]+"/"+channel[i]+"_ttbarsignalplustau.root");
        TDirectory *d1 = (TDirectory*)f1->Get("NTupDir");
        TTree *t1 = (TTree*)d1->Get("NTuple");
        t1->Process("BTagEff.C+");
        f1->Close();
    }

}
