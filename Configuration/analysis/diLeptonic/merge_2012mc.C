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

void merge(string channel){

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
  
  double topxsec = 225.197;

  map<string,float> MCXsecmap; //map of sample and cross-section
  
  double lumi = 5100.0;

  for(it = list_mc_files.begin(); it != list_mc_files.end(); it++){
  
    filename = *it;
    
    float sf =1;

    //cross-sections (pb), taken from https://twiki.cern.ch/twiki/bin/view/CMS/StandardModelCrossSectionsat8TeV#List_of_processes
    if(filename.find("data")!=string::npos){MCXsecmap[filename] = 1;}//data
    if(filename.find("ttbar")!=string::npos){MCXsecmap[filename] = topxsec;}//ttbar cross-section
    if(filename.find("single")!=string::npos){MCXsecmap[filename] = 22.2;}//single top cross-section
    if(filename.find("ww")!=string::npos){MCXsecmap[filename] = 54.838;}//WW cross-section
    if(filename.find("wz")!=string::npos){MCXsecmap[filename] = 33.21;}//WZ cross-section
    if(filename.find("zz")!=string::npos){MCXsecmap[filename] = 17.654;}//ZZ cross-section
    if(filename.find("1050")!=string::npos){MCXsecmap[filename] = 5745.25;}//DY ll inclusive cross-section m 10-50 #fFrom AN-2012/194 & AN-2012/228
    if(filename.find("50inf")!=string::npos){MCXsecmap[filename] = 3503.71;}//DY ll inclusive cross-section m 50->
    if(filename.find("wtolnu")!=string::npos){MCXsecmap[filename] = 36257.2;}//WJets to lnu cross-section
    if(filename.find("qcdmu15")!=string::npos){MCXsecmap[filename] = 3.64E8*3.7E-4;}//Muon enriched QCD sample (x-sec * FilterEff)
    if(filename.find("qcdmu2030")!=string::npos){MCXsecmap[filename] = 2.87E8*6.5E-3;}//Muon enriched QCD sample (x-sec * FilterEff)
    if(filename.find("qcdmu3050")!=string::npos){MCXsecmap[filename] = 6.609E7*0.0122;}//Muon enriched QCD sample (x-sec * FilterEff)
    if(filename.find("qcdmu5080")!=string::npos){MCXsecmap[filename] = 8.082E6*0.0218;}//Muon enriched QCD sample (x-sec * FilterEff)
    if(filename.find("qcdmu80120")!=string::npos){MCXsecmap[filename] = 1.024e6*0.0395;}//Muon enriched QCD sample (x-sec * FilterEff)
    if(filename.find("qcdmu120170")!=string::npos){MCXsecmap[filename] = 1.578E5*47.3e-3;}//Muon enriched QCD sample (x-sec * FilterEff)
    if(filename.find("qcdem2030")!=string::npos){MCXsecmap[filename] = 2.886E8*10.1e-3;}//EM enrichedpT 20-30GeV QCD sample (x-sec * FilterEff)
    if(filename.find("qcdem3080")!=string::npos){MCXsecmap[filename] = 7.433E7*62.1E-3;}//EM enrichedpT 30-80GeV QCD sample (x-sec * FilterEff)
    if(filename.find("qcdem80170")!=string::npos){MCXsecmap[filename] = 1.191E6*153.9E-3;}//EM enrichedpT 80-170GeV QCD sample (x-sec * FilterEff)
    if(filename.find("qcdbcem2030")!=string::npos){MCXsecmap[filename] = 2.886E8*5.8E-4;}//BCtoE 20-30GeV QCD sample (x-sec * FilterEff)
    if(filename.find("qcdbcem3080")!=string::npos){MCXsecmap[filename] = 7.424E7*2.25E-3;}//BCtoE pT 30-80GeV QCD sample (x-sec * FilterEff)
    if(filename.find("qcdbcem80170")!=string::npos){MCXsecmap[filename] = 1.191E6*10.9E-3;}//BCtoE 80-170GeV QCD sample (x-sec * FilterEff)
    if(filename.find("tth")!=string::npos){MCXsecmap[filename] = 0.08634;} //ttH at 125 GeV https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageAt7TeV#ttH_associate_production

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
    
    double lumiWeight = sf;
    double btagSF = 1.0; //btagSF applied to all one tag events
    double trigEFF;

    //Trigger effs. taken from AN-2012/389 (Jan & Carmen Inclusive ttbar XSection)
    if(channel=="mumu") trigEFF = 1.001;
    if(channel=="emu")  trigEFF = 0.978;
    if(channel=="ee")   trigEFF = 0.955;

    vector<string> Stringing;
    Stringing.push_back(MCSamplemap[filename]);
    vector<string> Channel;
    Channel.push_back(channel);

    TBranch *b_btagSF     = t->Branch("btagSF",&btagSF, "btagSF/D");
    TBranch *b_trigEFF    = t->Branch("trigEFF",&trigEFF, "trigEFF/D");
    TBranch *b_channel    = t->Branch("channel",&Channel[0]);
    TBranch *b_MCSample   = t->Branch("MCSample",&Stringing[0]);
    TBranch *b_lumiWeight = t->Branch("lumiWeight",&lumiWeight, "lumiWeight/D");


    if(filename.find("200")!=string::npos ||filename.find("800")!=string::npos || filename.find("run2012")!=string::npos ){//data
      lumiWeight=1.;
      btagSF=1;
      trigEFF=1;
    }
    else{//MC
    }
    for(int i=0;i<t->GetEntries();i++){
      b_btagSF->Fill();
      b_trigEFF->Fill();
      b_channel->Fill();
      b_MCSample->Fill();
      b_lumiWeight->Fill();
    }
    d->cd();
    t->Write("",TObject::kOverwrite);
  }

  return;
}

int merge_2012mc(){
  
  merge("mumu");
  merge("emu");
  merge("ee");

  return 0;

}
