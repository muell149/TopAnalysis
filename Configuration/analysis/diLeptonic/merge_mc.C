 //ls *mumu_*/*.root >list.txt
//cat list.txt | awk -F _ '{print $NF}' | awk '{sub(/.root/,"");print}'>samples.txt
//cat list.txt | awk '{sub(/.root/,".txt");print}' | xargs head -n2 | perl -nle '/Events total =\s*(\d+)/ && print $1' > eventCount.txt
//paste list.txt samples.txt eventCount.txt > lumi.txt
//To get the number of events from many output files use the following command
//ls *txt* | xargs head -n2 | perl -nle '/Events total =\s*(\d+)/ && print $1' | awk '{total+=$1} END{print total}'

#include "TFile.h"
#include "TROOT.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TList.h"
#include "TObjString.h"
#include "TClonesArray.h"
#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <set>
#include <TLorentzVector.h>
#include "Math/GenVector/LorentzVector.h"

using namespace std;

void merge_mc(string channel){

  TList *tlist = new TList();

  map<string,float> MCNumbermap; //map of sample and events
  map<string,string> MCSamplemap; //map of sample and events
  string mcname; 
  float genEvents;

  string lumifile = "lumi_";lumifile.append(channel);lumifile.append(".txt");
  ifstream NameEvents;
  NameEvents.open(lumifile.c_str());
  list<string> list_mc_files;
  string filename;

  while(NameEvents >> filename >> mcname >> genEvents){
    MCNumbermap[filename]=genEvents;
    list_mc_files.push_back(filename);
    MCSamplemap[filename]=mcname;
  }
  
  //scalefactors can go here

  list<string>::iterator it;
  
  double topxsec = 169.9;

  map<string,float> MCXsecmap; //map of sample and cross-section
  
  double lumi = 1143.221;

  for(it = list_mc_files.begin(); it != list_mc_files.end(); it++){
  
    filename = *it;
    
    float sf =1;

    //cross-sections (pb)
    if(filename.find("data")!=string::npos){MCXsecmap[filename] = 1;}//data
    if(filename.find("ttbar")!=string::npos){MCXsecmap[filename] = topxsec;}//ttbar cross-section
    if(filename.find("single")!=string::npos){MCXsecmap[filename] = 7.87;}//single top cross-section
    if(filename.find("ww")!=string::npos){MCXsecmap[filename] = 4.51;}//WW cross-section
    if(filename.find("wz")!=string::npos){MCXsecmap[filename] = 0.61;}//WZ cross-section
    if(filename.find("zz")!=string::npos){MCXsecmap[filename] = 7.4;}//ZZ cross-section
    if(filename.find("1020")!=string::npos){MCXsecmap[filename] = 3457;}//DY 10-20 exclusive cross-section
    if(filename.find("2050")!=string::npos){MCXsecmap[filename] = 1666;}//DY 20-50 exclusive cross-section
    if(filename.find("50inf")!=string::npos){MCXsecmap[filename] = 3048;}//DY ll inclusive cross-section
    if(filename.find("wtolnu")!=string::npos){MCXsecmap[filename] = 3048;}//WJets to lnu cross-section
    if(filename.find("qcdmu15")!=string::npos){MCXsecmap[filename] = 2.966E8*2.855E-4;}//Muon enriched QCD sample (x-sec * FilterEff)
    if(filename.find("qcdem2030")!=string::npos){MCXsecmap[filename] = 2.361E8*0.0106;}//EM enrichedpT 20-30GeV QCD sample (x-sec * FilterEff)
    if(filename.find("qcdem3080")!=string::npos){MCXsecmap[filename] = 5.944E7*0.061;}//EM enrichedpT 30-80GeV QCD sample (x-sec * FilterEff)
    if(filename.find("qcdem80170")!=string::npos){MCXsecmap[filename] = 898200.0*0.159;}//EM enrichedpT 80-170GeV QCD sample (x-sec * FilterEff)
    if(filename.find("qcdbcem2030")!=string::npos){MCXsecmap[filename] = 2.361E8*5.9E-4;}//BCtoE 20-30GeV QCD sample (x-sec * FilterEff)
    if(filename.find("qcdbcem3080")!=string::npos){MCXsecmap[filename] = 5.944E7*0.00242;}//BCtoE pT 30-80GeV QCD sample (x-sec * FilterEff)
    if(filename.find("qcdbcem80170")!=string::npos){MCXsecmap[filename] = 898200.0*0.0105;}//BCtoE 80-170GeV QCD sample (x-sec * FilterEff)

    sf=(lumi*MCXsecmap[filename])/MCNumbermap[filename];

    cout<<"sf = "<<sf<<endl;
    cout<<"lumi = "<<lumi<<endl;
    cout<<"filename: "<<filename<<endl;
    cout<<"MCXSecmap "<<MCXsecmap[filename]<<endl;
    cout<<"MCSamplemap: "<<MCSamplemap[filename]<<endl;
    cout<<"MCNumbermap "<<MCNumbermap[filename]<<endl<<endl;

    TFile *f1 = TFile::Open(filename.data(),"update");
    TDirectory *d = (TDirectory*) f1->Get("NTupDir");
    TTree *t = (TTree*)d->Get("NTuple");

    gROOT->cd();

    //    TTree *tree = new TTree();
    //tree = t->CloneTree(0);
    
    double lumiWeight = sf;
    double btagSF = 0.982; //btagSF applied to all one tag events
    double trigEFF;

    if(channel=="mumu") trigEFF = 0.961;
    if(channel=="emu") trigEFF = 0.987;
    if(channel=="ee") trigEFF = 0.977;

    vector<string> Stringing;
    Stringing.push_back(MCSamplemap[filename]);
    vector<string> Channel;
    Channel.push_back(channel);

    TBranch *b_btagSF = t->Branch("btagSF",&btagSF, "btagSF/D");
    TBranch *b_trigEFF =     t->Branch("trigEFF",&trigEFF, "trigEFF/D");
    TBranch *b_channel = t->Branch("channel",&Channel[0]);
    TBranch *b_MCSample = t->Branch("MCSample",&Stringing[0]);
    TBranch *b_lumiWeight = t->Branch("lumiWeight",&lumiWeight, "lumiWeight/D");


    //TObjString *MCSample = new TObjString(MCSamplemap[filename].c_str());
    if(filename.find("200")!=string::npos ||filename.find("800")!=string::npos || filename.find("run")!=string::npos ){//data
      lumiWeight=1.;
      btagSF=1;
      trigEFF=1;
    }
    else{//MC
    }
    for(int i=0;i<t->GetEntries();i++){
      //      t->GetEntry(i);
      b_btagSF->Fill();
      b_trigEFF->Fill();
      b_channel->Fill();
      b_MCSample->Fill();
      b_lumiWeight->Fill();

      //      t->Fill();
    }
    //    t->Delete();
    //string f_savename;
    //f_savename = "mergedRoot/";
    //f_savename.append(channel+"/");f_savename.append(Stringing[0]);
    //f_savename.append(".root");

    //tlist->Add(tree);
    //TTree *finaltree = TTree::MergeTrees(tlist);
    //TFile *f_save;
    //f_save = new TFile(f_savename.c_str(),"RECREATE");
    //f_save = new TFile("mergedRoot/"+Stringing[0]+".root","RECREATE");
    //    f_save = finaltree->GetCurrentFile();
    d->cd();
    t->Write("",TObject::kOverwrite);
    //f_save->Close();
    //delete f_save;
    //finaltree->Delete();
    //tlist->Delete();
  }

  return;
}

int merge(){
  
  merge_mc("mumu");
  //  merge_mc("emu");
  //merge_mc("ee");

  return 0;

}
/*
void Add(string fname, int mctype, float sf, TList *tlist){

  cout << "Adding "  << fname << " with scale " << sf <<  endl;
  TFile *fmc;// = new TFile(fname.data(),"data");
  TTree *t;// = (TTree*)fmc->Get("NTuple");
  fmc = new TFile(fname.data(),"data");
  if(!fmc->IsOpen()) return;
  if(!fmc->Get("NTuple")) return;
  t = (TTree*)fmc->Get("NTuple");
  
  gROOT->cd();
  TTree *tree = new TTree();
  
  tree = t->CloneTree(0);
  
  t->SetBranchAddress("eventWeight",&eventWeight)

  return;
}
*/
