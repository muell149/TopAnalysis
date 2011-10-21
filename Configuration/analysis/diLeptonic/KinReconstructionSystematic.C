#include <iostream>
#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TMath.h"
#include "TStyle.h"

#include "TopAnalysis/Configuration/analysis/semiLeptonic/diffXSection/HHStyle.h"

using namespace std;

// output format
const TString outform(".eps");


TH1* DividedHist(TH1* nom, TH1* denom){
  
    if( nom->GetNbinsX()!=denom->GetNbinsX() ){
        cout << "WARNING in DivideHist: incompatible binning!"  << endl;
    }
  
    TH1* res = (TH1*)nom->Clone();
    res->Reset();
    res->SetFillStyle(0);  
    
    for(Int_t i=1;i<=res->GetNbinsX();++i){
        Double_t a  = nom->GetBinContent(i);
        Double_t b  = denom->GetBinContent(i);
        Double_t da = nom->GetBinError(i);
        Double_t db = denom->GetBinError(i);        
        Double_t c  = a/b;
        Double_t dc = TMath::Sqrt(da*da/b/b + a*a*db*db/b/b/b/b);
    
        res->SetBinContent(i,c);
        res->SetBinError(i,dc);  
    }
  
    return res;
}


// function to plot histograms with a ratio
void PlotHistsAndRatio(TH1* nomHist, TH1* denomHist, const char* name) {

    TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,800);
    c1->Range(0,0,1,1);

    // Create ratio histogram
    TH1* ratioHist = DividedHist(nomHist, denomHist);

    // Bottom plot
    TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.32);
    c1_1->Draw();
    c1_1->cd();
    c1_1->SetTopMargin(0.03);
    c1_1->SetBottomMargin(0.3);
    c1_1->SetLeftMargin(0.14);
    c1_1->SetRightMargin(0.04);
    c1_1->SetFillStyle(0);

    ratioHist->Draw();
    ratioHist->SetLineWidth(1.5);
    ratioHist->SetMarkerSize(1.5);
    ratioHist->SetLineColor(kBlack);
    ratioHist->SetMinimum(0.70);
    ratioHist->SetMaximum(1.20);
    ratioHist->GetYaxis()->SetNdivisions(5);
    ratioHist->GetYaxis()->SetTitle("Ratio");
    ratioHist->GetXaxis()->SetNoExponent(kTRUE);
    ratioHist->GetXaxis()->SetTitleSize(0.11);
    ratioHist->GetXaxis()->SetLabelSize(0.11);
    ratioHist->GetXaxis()->SetTitleOffset(1.10);
    ratioHist->GetYaxis()->SetLabelSize(0.11);
    ratioHist->GetYaxis()->SetTitleSize(0.11);
    ratioHist->GetYaxis()->SetTitleOffset(0.50);
    ratioHist->SetLineWidth(1);
    ratioHist->SetLineColor(kBlack);
    ratioHist->Draw("E0");

    // Top Plot
    c1->cd();
    TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.33,0.99,0.99);
    c1_2->Draw();
    c1_2->cd();
    c1_2->SetTopMargin(0.1);
    c1_2->SetBottomMargin(0.03);
    c1_2->SetLeftMargin(0.14);
    c1_2->SetRightMargin(0.04);
    c1_2->SetFillStyle(0);

    Double_t maximum = 1.3*TMath::Max(nomHist->GetMaximum(), denomHist->GetMaximum());
    Double_t minimum = 0.;
    
    if(strcmp(name,"KinRecoSystematic_LepPt")==0){
      gPad->SetLogy(1);
      maximum = 3.*TMath::Max(nomHist->GetMaximum(), denomHist->GetMaximum());
      minimum = .3*TMath::Max(nomHist->GetMinimum(), denomHist->GetMinimum());   
    }

    denomHist->SetLineColor(2);
    denomHist->SetLineWidth(2);
    denomHist->SetMarkerStyle(22);
    denomHist->SetMarkerColor(2);
    denomHist->SetMarkerSize(1.5);            
    denomHist->Draw("E0");
    denomHist->SetLabelSize(0.0);
    denomHist->GetXaxis()->SetTitleSize(0.00);
    denomHist->GetYaxis()->SetLabelSize(0.05);       
    denomHist->GetYaxis()->SetTitleSize(0.05);
    denomHist->GetYaxis()->SetTitleOffset(1.20);
    denomHist->SetMinimum(minimum);
    denomHist->SetMaximum(maximum);
    nomHist->SetLineColor(4);
    nomHist->SetLineWidth(2);
    nomHist->SetMarkerStyle(23);
    nomHist->SetMarkerColor(4);
    nomHist->SetMarkerSize(1.5);         
    nomHist  ->Draw("E0,SAME");

    TLegend leg(.64,.65,.94,.85);
    leg.SetFillStyle(0);
    leg.SetBorderSize(0);
    leg.AddEntry(nomHist,   "kin reco (b-tagging, fixed m_{t})", "p");
    leg.AddEntry(denomHist, "w/o kin reco",  "p");  
    leg.Draw("SAME");			

    c1->Print(TString("plots/kineff/").Append(name).Append(outform));

    delete c1_1;
    delete c1_2;
    delete c1;
    delete ratioHist;
}



void KinReconstructionSystematic(){

    setHHStyle(*gStyle);
    gStyle->SetErrorX(0.5);
    TGaxis::SetMaxDigits(2);
  
    TFile* file;  
    file = new TFile("plots/DiffXS_Histograms_standard.root");
  
    TH1* LepPtHist;		file->GetObject("combined_FixedMt_Btag_Cross_Leptons_Pt;1", 	LepPtHist);
    TH1* LepPtNoFitHist;	file->GetObject("combined_NoFit_Cross_Leptons_Pt;1", 		LepPtNoFitHist);   
    TH1* LepEtaHist;		file->GetObject("combined_FixedMt_Btag_Cross_Leptons_Eta;1", 	LepEtaHist);  
    TH1* LepEtaNoFitHist;	file->GetObject("combined_NoFit_Cross_Leptons_Eta;1", 		LepEtaNoFitHist);    
    TH1* LepPairMassHist;	file->GetObject("combined_FixedMt_Btag_Cross_LepPair_Mass;1",	LepPairMassHist);  
    TH1* LepPairMassNoFitHist;	file->GetObject("combined_NoFit_Cross_LepPair_Mass;1", 		LepPairMassNoFitHist);  
  
    PlotHistsAndRatio(LepPtHist, 	LepPtNoFitHist, 	"KinRecoSystematic_LepPt_standard");
    PlotHistsAndRatio(LepEtaHist, 	LepEtaNoFitHist, 	"KinRecoSystematic_LepEta_standard");  
    PlotHistsAndRatio(LepPairMassHist,	LepPairMassNoFitHist,	"KinRecoSystematic_LepPairMass_standard");   
}
