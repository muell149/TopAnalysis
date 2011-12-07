{
  TString sample = "wtolnu";
  TFile *f1 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d1 = (TDirectory*)f1->Get("NTupDir");
  TTree *t1 = (TTree*)d1->Get("NTuple");
  t1->Process("Analysis.C+");

  TString sample = "wwto2l2nu";
  TFile *f3 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d3 = (TDirectory*)f3->Get("NTupDir");
  TTree *t3 = (TTree*)d3->Get("NTuple");
  t3->Process("Analysis.C+");

  TString sample = "wzto3lnu";
  TFile *f4 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d4 = (TDirectory*)f4->Get("NTupDir");
  TTree *t4 = (TTree*)d4->Get("NTuple");
  t4->Process("Analysis.C+");

  TString sample = "zztoall";
  TFile *f5 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d5 = (TDirectory*)f5->Get("NTupDir");
  TTree *t5 = (TTree*)d5->Get("NTuple");
  t5->Process("Analysis.C+");

  TString sample = "run2011av1v2";
  //TString sample = "200rereco";
  TFile *f6 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d6 = (TDirectory*)f6->Get("NTupDir");
  TTree *t6 = (TTree*)d6->Get("NTuple");
  t6->Process("Analysis.C+");

  TString sample = "run2011a_v4";
  //TString sample = "800prompt";
  TFile *f7 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d7 = (TDirectory*)f7->Get("NTupDir");
  TTree *t7 = (TTree*)d7->Get("NTuple");
  t7->Process("Analysis.C+");

  TString sample = "dymumu1020";
  TFile *f8 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d8 = (TDirectory*)f8->Get("NTupDir");
  TTree *t8 = (TTree*)d8->Get("NTuple");
  t8->Process("Analysis.C+");

  TString sample = "dymumu2050";
  TFile *f9 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d9 = (TDirectory*)f9->Get("NTupDir");
  TTree *t9 = (TTree*)d9->Get("NTuple");
  t9->Process("Analysis.C+");

  TString sample = "dymumu50inf";
  TFile *f10 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d10 = (TDirectory*)f10->Get("NTupDir");
  TTree *t10 = (TTree*)d10->Get("NTuple");
  t10->Process("Analysis.C+");

  TString sample = "dytautau2050";
  TFile *f11 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d11 = (TDirectory*)f11->Get("NTupDir");
  TTree *t11 = (TTree*)d11->Get("NTuple");
  t11->Process("Analysis.C+");

  TString sample = "dytautau50inf";
  TFile *f12 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d12 = (TDirectory*)f12->Get("NTupDir");
  TTree *t12 = (TTree*)d12->Get("NTuple");
  t12->Process("Analysis.C+");

  TString sample = "dytautau1020";
  TFile *f13 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d13 = (TDirectory*)f13->Get("NTupDir");
  TTree *t13 = (TTree*)d13->Get("NTuple");
  t13->Process("Analysis.C+");

  TString sample = "qcdmu15";
  TFile *f14 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d14 = (TDirectory*)f14->Get("NTupDir");
  TTree *t14 = (TTree*)d14->Get("NTuple");
  t14->Process("Analysis.C+");

  //  TString sample = "run161119";
  //TFile *f15 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  //TDirectory *d15 = (TDirectory*)f15->Get("NTupDir");
  //TTree *t15 = (TTree*)d15->Get("NTuple");
  //t15->Process("Analysis.C+");

  TString sample = "ttbarbg";
  TFile *f16 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d16 = (TDirectory*)f16->Get("NTupDir");
  TTree *t16 = (TTree*)d16->Get("NTuple");
  t16->Process("Analysis.C+");

  //  TString sample = "ttbarsignal";
  //TFile *f17 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  //TDirectory *d17 = (TDirectory*)f17->Get("NTupDir");
  //TTree *t17 = (TTree*)d17->Get("NTuple");
  //t17->Process("Analysis.C+");

  //TString sample = "ttbarviatau";
  //TFile *f18 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  //TDirectory *d18 = (TDirectory*)f18->Get("NTupDir");
  //TTree *t18 = (TTree*)d18->Get("NTuple");
  //t18->Process("Analysis.C+");

  TString sample = "singletop_tw";
  TFile *f19 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d19 = (TDirectory*)f19->Get("NTupDir");
  TTree *t19 = (TTree*)d19->Get("NTuple");
  t19->Process("Analysis.C+");

  TString sample = "singleantitop_tw";
  TFile *f20 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d20 = (TDirectory*)f20->Get("NTupDir");
  TTree *t20 = (TTree*)d20->Get("NTuple");
  t20->Process("Analysis.C+");

  TString sample = "ttbarsignalplustau";
  TFile *f2 = TFile::Open("mergedRoot/mumu/mumu_"+sample+".root");
  TDirectory *d2 = (TDirectory*)f2->Get("NTupDir");
  TTree *t2 = (TTree*)d2->Get("NTuple");
  t2->Process("Analysis.C+");

}
