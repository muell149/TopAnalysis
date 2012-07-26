#include "TH1.h"
#include "TMath.h"
#include <vector>
#include <TFile.h>
#include <cstdio>

double Median(TH1D * h1) { 

   int n = h1->GetXaxis()->GetNbins();  
   std::vector<double>  x(n);
   h1->GetXaxis()->GetCenter( &x[0] );
   const double * y = h1->GetArray(); 
   // exclude underflow/overflows from bin content array y
   return TMath::Median(n, &x[0], &y[1]); 
}



int CalcMedian(){

    printf("========================================================================\n");
    //mumu channel
    TFile *f=TFile::Open("BTagEff/mumu/ttbarsignalplustau.root");
    TH1D *mumu = (TH1D*)f->Get("BEffPt");
    printf("Calculating the Median using %s\n", f->GetName());
    double mumuMedian=Median(mumu);
    printf("mumu b-Jet pT median is %.4f\n \n", mumuMedian);
    f->Close();
    f->Delete();
    //emu channel
    TFile *f=TFile::Open("BTagEff/emu/ttbarsignalplustau.root");
    TH1D *emu = (TH1D*)f->Get("BEffPt");
    printf("Calculating the Median using %s\n", f->GetName());
    double emuMedian=Median(emu);
    printf("emu b-Jet pT median is %.4f\n \n", emuMedian);
    f->Close();
    f->Delete();
    //ee channel
    TFile *f=TFile::Open("BTagEff/ee/ttbarsignalplustau.root");
    TH1D *ee = (TH1D*)f->Get("BEffPt");
    printf("Calculating the Median using %s\n", f->GetName());
    double eeMedian=Median(ee);
    printf("ee b-Jet pT median is %.4f\n \n", eeMedian);


}