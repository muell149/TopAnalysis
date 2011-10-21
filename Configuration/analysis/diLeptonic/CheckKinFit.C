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
const TString outform(".png");

TH1* DividedHist(TH1* nom, TH1* denom){
  
  if( nom->GetNbinsX()!=denom->GetNbinsX() ){
    cout << "WARNING in DivideHist: incompatible binning!"  << endl;
  }
  
  TH1* res = (TH1*)nom->Clone();
  res->Reset();
  res->SetFillStyle(0);  
  
  
  for(Int_t i=1;i<=res->GetNbinsX();++i){
    Double_t a = nom->GetBinContent(i);
    Double_t b = denom->GetBinContent(i);
    Double_t c = a/b;
    Double_t dc = TMath::Sqrt(a/b/b + a*a/b/b/b);
    
    res->SetBinContent(i,c);
    res->SetBinError(i,dc);  
  }
  
  return res;
}


void CompareDataMC(TH1* dataHist, TH1* mcHist, const char* name){

  TCanvas* Canvas = new TCanvas("plot", "plot", 800, 800);
  
  dataHist->SetMarkerStyle(21);
  dataHist->SetMarkerColor(1);  
  dataHist->SetLineColor(1); 
  dataHist->SetLineWidth(2);
  
  mcHist->SetLineColor(2);
  mcHist->SetLineWidth(2);
  mcHist->SetMinimum(0.);
  mcHist->SetMaximum(1.);
  
  mcHist->Draw("Hist");
  dataHist->Draw("E1,SAME");

  TLegend leg(.4,.2,.6,.4);
  leg.SetFillStyle(0);
  leg.SetBorderSize(0);
  leg.AddEntry(dataHist, "Data - BG", "p");
  leg.AddEntry(mcHist,   "Signal MC", "l");  
  leg.Draw("SAME");
  
  Canvas->Print(TString("plots/kineff/").Append(name).Append(outform));
  
  delete Canvas;
}



// function to plot histograms with a ratio
void PlotHistsAndRatio(TH1* nomHist, TH1* denomHist, const char* name, const char* legtext1, const char* legtext2) {

    TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,800);
    c1->Range(0,0,1,1);

    // Create ratio histogram
    TH1* ratioHist = (TH1*)nomHist->Clone();
    ratioHist->Divide(denomHist);

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
    ratioHist->SetMinimum(0.50);
    ratioHist->SetMaximum(1.50);
    ratioHist->GetYaxis()->SetNdivisions(5);
    ratioHist->GetYaxis()->SetTitle("Ratio");
    ratioHist->GetXaxis()->SetNoExponent(kTRUE);
    ratioHist->GetXaxis()->SetTitleSize(0.14);
    ratioHist->GetXaxis()->SetLabelSize(0.14);
    ratioHist->GetXaxis()->SetTitleOffset(0.9);
    ratioHist->GetYaxis()->SetLabelSize(0.11);
    ratioHist->GetYaxis()->SetTitleSize(0.14);
    ratioHist->GetYaxis()->SetTitleOffset(0.40);
    ratioHist->SetLineWidth(1);
    ratioHist->SetLineColor(kBlack);
    ratioHist->Draw("HIST");

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

    //denominatorHistogram->SetLineWidth(2);
    denomHist->SetLineColor(2);
    denomHist->SetLineWidth(2);    
    denomHist->Draw("HIST");
    denomHist->SetLabelSize(0.0);
    denomHist->GetXaxis()->SetTitleSize(0.00);
    denomHist->GetYaxis()->SetLabelSize(0.07);       
    denomHist->GetYaxis()->SetTitleSize(0.08);
    denomHist->GetYaxis()->SetTitleOffset(0.70);
    denomHist->SetMinimum(0.00);
    denomHist->SetMaximum(maximum);
    nomHist->SetLineColor(4);
    nomHist->SetLineWidth(2); 
    nomHist  ->SetMarkerSize(1.5);
    nomHist  ->Draw("HIST,SAME");

    TLegend leg(.4,.1,.6,.3);
    leg.SetFillStyle(0);
    leg.SetBorderSize(0);
    leg.AddEntry(nomHist,   legtext1, "l");
    leg.AddEntry(denomHist, legtext2, "l");  
    leg.Draw("SAME");			

    c1_2->SetLogy(0);

    c1->Print(TString("plots/kineff/").Append(name).Append(outform));

    delete c1_1;
    delete c1_2;
    delete c1;
    delete ratioHist;
}



// function to plot histograms with a ratio
void PlotHistsAndRatio(TH1* nomHist, TH1* denomHist, TH1* nomHistMC, TH1* denomHistMC, 
    const char* name, const char* legtext1, const char* legtext2, const char* xtitle="",const char* ytitle="", const char* ytitle2="") {

    TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,800);
    c1->Range(0,0,1,1);

    // Create ratio histogram
    TH1* ratioHist   = DividedHist(nomHist,   denomHist  );
    TH1* ratioHistMC = DividedHist(nomHistMC, denomHistMC);    
  
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
    if(strcmp(xtitle,""))
        ratioHist->GetXaxis()->SetTitle(xtitle);
    ratioHist->GetYaxis()->SetTitle("Ratio");
    if(strcmp(ytitle2,""))
        ratioHist->GetYaxis()->SetTitle(ytitle2);    
    ratioHist->SetLineWidth(2);
    ratioHist->SetMarkerStyle(21);
    ratioHist->SetLineColor(kBlack);
    ratioHist->SetMinimum(0.5*ratioHist->GetMinimum());
    ratioHist->SetMaximum(1.5*ratioHist->GetMaximum());
    ratioHist->GetYaxis()->SetNdivisions(5);
    ratioHist->GetXaxis()->SetNoExponent(kTRUE);
    ratioHist->GetXaxis()->SetTitleSize(0.14);
    ratioHist->GetXaxis()->SetLabelSize(0.14);
    ratioHist->GetXaxis()->SetTitleOffset(0.9);
    ratioHist->GetYaxis()->SetLabelSize(0.11);
    ratioHist->GetYaxis()->SetTitleSize(0.14);
    ratioHist->GetYaxis()->SetTitleOffset(0.40);
    ratioHist->SetLineWidth(1);
    ratioHist->SetLineColor(kBlack);
    ratioHist->Draw("E0");
    
    ratioHistMC->SetLineWidth(2);
    ratioHistMC->SetLineColor(kBlack);       
    ratioHistMC->SetFillStyle(0);        
    ratioHistMC->Draw("SAME,HIST");
    
    TLegend leg1(.15,.75,.3,.95);
    leg1.SetFillStyle(0);
    leg1.SetBorderSize(0);
    leg1.AddEntry(ratioHist,   "data", "p");
    leg1.AddEntry(ratioHistMC, "MC",   "l");
    leg1.Draw("SAME");						     


    for(Int_t i=1; i<=ratioHist->GetNbinsX(); ++i){
       cout << "SF = " << ratioHist->GetBinContent(i) / ratioHistMC->GetBinContent(i) << endl;
    }

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
    if(1.3*nomHistMC->GetMaximum()>maximum) maximum=1.3*nomHistMC->GetMaximum();
    if(1.3*denomHistMC->GetMaximum()>maximum) maximum=1.3*denomHistMC->GetMaximum();        

    if(strcmp(ytitle,""))
        denomHistMC->GetYaxis()->SetTitle(ytitle); 
    denomHistMC->SetLabelSize(0.0);
    denomHistMC->GetXaxis()->SetTitleSize(0.00);
    denomHistMC->GetYaxis()->SetLabelSize(0.07);       
    denomHistMC->GetYaxis()->SetTitleSize(0.08);
    denomHistMC->GetYaxis()->SetTitleOffset(0.70);
    denomHistMC->SetMinimum(0.00);
    denomHistMC->SetMaximum(maximum);
    
    denomHistMC->SetLineColor(2);
    denomHistMC->SetLineWidth(3); 
    denomHistMC->SetFillStyle(0);            
    denomHistMC->Draw("HIST");    
    nomHistMC->SetLineColor(4);
    nomHistMC->SetLineWidth(3); 
    nomHistMC->SetFillStyle(0);         
    nomHistMC->Draw("SAME,HIST");
    
    denomHist->SetLineColor(2);
    denomHist->SetLineWidth(2);
    denomHist->SetMarkerStyle(22); 
    denomHist->SetMarkerColor(2);            
    denomHist->Draw("SAME,E0");    
    nomHist->SetLineColor(4);
    nomHist->SetLineWidth(2); 
    nomHist->SetMarkerStyle(23); 
    nomHist->SetMarkerColor(4);      
    nomHist->Draw("SAME,E0");    
    
    TLegend leg2(.7,.65,.9,.85);
    leg2.SetFillStyle(0);
    leg2.SetBorderSize(0);
    leg2.AddEntry(nomHist,   legtext1, "p");
    leg2.AddEntry(denomHist, legtext2, "p");
    leg2.AddEntry(nomHist,   TString(legtext1).Append(" (MC)"), "l");
    leg2.AddEntry(denomHist, TString(legtext2).Append(" (MC)"), "l");		      
    leg2.Draw("SAME");  		

    c1_2->SetLogy(0);

    c1->Print(TString("plots/kineff/").Append(name).Append(outform));

    delete c1_1;
    delete c1_2;
    delete c1;
    delete ratioHist;
}




// function to plot ratios
void PlotHistsAndRatio(TH1* h1, TH1* h2, TH1* h3, TH1* h4, TH1* g1, TH1* g2, TH1* g3, TH1* g4, const char* name) {

    TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,800);
    c1->Range(0,0,1,1);

    // 1=b,free
    // 2=b,fixed
    // 3=leading,free
    // 4=leading,fixed

    // Create ratio histogram
    TH1* r2 = DividedHist(h2, h1);
    TH1* r3 = DividedHist(h3, h1);
    TH1* r4 = DividedHist(h4, h1);    
    
    TH1* r2MC = DividedHist(g2, g1);
    TH1* r3MC = DividedHist(g3, g1);
    TH1* r4MC = DividedHist(g4, g1);
    
    r2->SetMarkerStyle(21);
    r2->SetMarkerColor(kRed+2);    
    r2->SetLineColor(kRed+2);
    
    r3->SetMarkerStyle(22);
    r3->SetMarkerColor(kGreen+2);     
    r3->SetLineColor(kGreen+2);
    
    r4->SetMarkerStyle(23);
    r4->SetMarkerColor(kBlue+2);    
    r4->SetLineColor(kBlue+2);
    
    r2MC->SetLineColor(kRed);    
    r3MC->SetLineColor(kGreen);    
    r4MC->SetLineColor(kBlue);    
                  
    r2MC->SetMinimum(0);
    r2MC->SetMaximum(1.6);
    
    r2MC->GetYaxis()->SetLabelSize(0.04);        
    r2MC->GetYaxis()->SetTitleSize(0.04);
    r2MC->GetYaxis()->SetTitleOffset(1.4); 
    r2MC->GetYaxis()->SetTitle("Ratio");            
    r2MC->GetXaxis()->SetLabelSize(0.04);    
    r2MC->GetXaxis()->SetTitleSize(0.04);    
    r2MC->GetXaxis()->SetNoExponent(kTRUE);    
      
    r2MC->Draw("HIST");
    r3MC->Draw("SAME,HIST");   
    r4MC->Draw("SAME,HIST");
    
    r2->Draw("SAME,E0");
    r3->Draw("SAME,E0");   
    r4->Draw("SAME,E0");
    
    
    TLegend leg1(.18,.70,.58,.90);
    leg1.SetFillStyle(0);
    leg1.SetBorderSize(0);
    leg1.AddEntry(r2, "b-tag, fixed m_{t} / b-tag, free m_{t} ",      "p");
    leg1.AddEntry(r3, "lead. jets, fixed m_{t} / b-tag, free m_{t} ", "p");
    leg1.AddEntry(r4, "lead. jets, free m_{t} / b-tag, free m_{t} ",  "p"); 
    leg1.Draw("SAME"); 
    
    TLegend leg2(.59,.706,.64,.906);
    leg2.SetFillStyle(0);
    leg2.SetBorderSize(0);
    leg2.AddEntry(r2MC, "MC", "l");
    leg2.AddEntry(r3MC, "MC", "l");
    leg2.AddEntry(r4MC, "MC", "l");
    leg2.Draw("SAME");     
    		
    
    c1->Print(TString("plots/kineff/").Append(name).Append(outform));
    
    delete r2;
    delete r3;    
    delete r4;    
    
    delete r2MC;
    delete r3MC;
    delete r4MC;
    
    delete c1;
}



void CheckKinFit(){

  setHHStyle(*gStyle);
  //gStyle->SetErrorX(0.5);
  TGaxis::SetMaxDigits(2);  

  TFile* files[4];
  files[0] = new TFile("plots/KinEfficienies_Histograms_standard.root");
  files[1] = new TFile("plots/KinEfficienies_Histograms_freeMass.root");  
  files[2] = new TFile("plots/KinEfficienies_Histograms_leadingJets.root");  
  files[3] = new TFile("plots/KinEfficienies_Histograms_leadingJets_freeMass.root");    

  TH1* LepPtDataHist[4];
  TH1* LepEtaDataHist[4];
  TH1* LepPtSignalHist[4];
  TH1* LepEtaSignalHist[4];
  TH1* GenTopPtHist[4];
  TH1* GenTopRapidityHist[4];
  TH1* GenTtBarPtHist[4];
  TH1* GenTtBarRapidityHist[4];
  TH1* GenTtBarMassHist[4];
  TH1* YieldLepPtHist[4];
  TH1* YieldLepEtaHist[4];
  TH1* YieldTopPtHist[4];
  TH1* YieldTopRapidityHist[4];
  TH1* YieldSigMcLepPtHist[4];
  TH1* YieldSigMcLepEtaHist[4];
  TH1* YieldSigMcTopPtHist[4];
  TH1* YieldSigMcTopRapidityHist[4];
    
  TH1* ElecPt8[4];
  TH1* ElecEta8[4];
  TH1* MuonPt8[4];
  TH1* MuonEta8[4];
  TH1* LepPairMassMM8[4];
  TH1* LepPairMassEM8[4];
  TH1* LepPairMassEE8[4];
  
  TH1* ElecPt8MC[4];
  TH1* ElecEta8MC[4];
  TH1* MuonPt8MC[4];
  TH1* MuonEta8MC[4];
  TH1* LepPairMassMM8MC[4];
  TH1* LepPairMassEM8MC[4];
  TH1* LepPairMassEE8MC[4];  

  TH1* ElecPt9[4];
  TH1* ElecEta9[4];
  TH1* MuonPt9[4];
  TH1* MuonEta9[4];
  TH1* LepPairMassMM9[4];
  TH1* LepPairMassEM9[4]; 
  TH1* LepPairMassEE9[4];
  
  TH1* ElecPt9MC[4];
  TH1* ElecEta9MC[4];
  TH1* MuonPt9MC[4];
  TH1* MuonEta9MC[4];
  TH1* LepPairMassMM9MC[4];
  TH1* LepPairMassEM9MC[4]; 
  TH1* LepPairMassEE9MC[4];

  
  // same histos binned
  TH1* ElecPtBinned8[4];
  TH1* ElecEtaBinned8[4];
  TH1* MuonPtBinned8[4];
  TH1* MuonEtaBinned8[4];
  TH1* LepPairMassMMBinned8[4];
  TH1* LepPairMassEMBinned8[4];
  TH1* LepPairMassEEBinned8[4];
  
  TH1* ElecPtBinned8MC[4];
  TH1* ElecEtaBinned8MC[4];
  TH1* MuonPtBinned8MC[4];
  TH1* MuonEtaBinned8MC[4];
  TH1* LepPairMassMMBinned8MC[4];
  TH1* LepPairMassEMBinned8MC[4];
  TH1* LepPairMassEEBinned8MC[4];  

  TH1* ElecPtBinned9[4];
  TH1* ElecEtaBinned9[4];
  TH1* MuonPtBinned9[4];
  TH1* MuonEtaBinned9[4];
  TH1* LepPairMassMMBinned9[4];
  TH1* LepPairMassEMBinned9[4]; 
  TH1* LepPairMassEEBinned9[4];
  
  TH1* ElecPtBinned9MC[4];
  TH1* ElecEtaBinned9MC[4];
  TH1* MuonPtBinned9MC[4];
  TH1* MuonEtaBinned9MC[4];
  TH1* LepPairMassMMBinned9MC[4];
  TH1* LepPairMassEMBinned9MC[4]; 
  TH1* LepPairMassEEBinned9MC[4];  
  
  
  // combinations of the hists above
  TH1* LepPt8[4];
  TH1* LepEta8[4];
  TH1* LepPairMass8[4];
  TH1* LepPt8MC[4];
  TH1* LepEta8MC[4];
  TH1* LepPairMass8MC[4]; 
  
  TH1* LepPt9[4];
  TH1* LepEta9[4];
  TH1* LepPairMass9[4];
  TH1* LepPt9MC[4];
  TH1* LepEta9MC[4];
  TH1* LepPairMass9MC[4];

  const Int_t nbinsLepPt = 5;
  const Double_t binsLepPt[nbinsLepPt+1] = {20, 40, 70, 120, 180, 400};
  
  const Int_t nbinsLepEta = 6;
  const Double_t binsLepEta[nbinsLepEta+1] = {-2.4, -1.5, -0.8, 0.0, 0.8, 1.5, 2.4};
  
  const Int_t nbinsLepPairMass = 5;
  const Double_t binsLepPairMass[nbinsLepPairMass+1] = {12, 50, 76, 106, 200, 300};
  
  for(Int_t i=0; i<4; ++i){

    files[i]->GetObject("kinEfficiency_data_LeptonsPt;1", 		 	  LepPtDataHist[i]	         );
    files[i]->GetObject("kinEfficiency_data_LeptonsEta;1",		 	  LepEtaDataHist[i]	         );
    files[i]->GetObject("kinEfficiency_signal_LeptonsPt;1",		 	  LepPtSignalHist[i]	         );
    files[i]->GetObject("kinEfficiency_signal_LeptonsEta;1",		 	  LepEtaSignalHist[i]	         );
    files[i]->GetObject("kinEfficiency_genTopPt;1",			 	  GenTopPtHist[i]	         );
    files[i]->GetObject("kinEfficiency_genTopRapidity;1", 			  GenTopRapidityHist[i]          );
    files[i]->GetObject("kinEfficiency_genTtBarPt;1",			 	  GenTtBarPtHist[i]	         );
    files[i]->GetObject("kinEfficiency_genTtBarRapidity;1",			  GenTtBarRapidityHist[i]        );	 
    files[i]->GetObject("kinEfficiency_genTtBarMass;1",				  GenTtBarMassHist[i]	         );
    files[i]->GetObject("combined_FixedMt_Btag_Yield_Leptons_Pt;1",		  YieldLepPtHist[i]	         );
    files[i]->GetObject("combined_FixedMt_Btag_Yield_Leptons_Eta;1",		  YieldLepEtaHist[i]	         );
    files[i]->GetObject("combined_FixedMt_Btag_Yield_TopQuarks_Pt;1",	 	  YieldTopPtHist[i]	         );
    files[i]->GetObject("combined_FixedMt_Btag_Yield_TopQuarks_Rapidity;1",	  YieldTopRapidityHist[i]        );
    files[i]->GetObject("combined_FixedMt_Btag_Yield_Leptons_Pt_signalMC;1",	  YieldSigMcLepPtHist[i]         );
    files[i]->GetObject("combined_FixedMt_Btag_Yield_Leptons_Eta_signalMC;1",	  YieldSigMcLepEtaHist[i]        );
    files[i]->GetObject("combined_FixedMt_Btag_Yield_TopQuarks_Pt_signalMC;1",	  YieldSigMcTopPtHist[i]         );
    files[i]->GetObject("combined_FixedMt_Btag_Yield_TopQuarks_Rapidity_signalMC;1",YieldSigMcTopRapidityHist[i] );
        
    files[i]->GetObject("combined_analyzeElecs8_pt;1", 			ElecPt8[i] );    
    files[i]->GetObject("combined_analyzeElecs8_eta;1",	 		ElecEta8[i] );    
    files[i]->GetObject("combined_analyzeMuons8_pt;1", 			MuonPt8[i] );    
    files[i]->GetObject("combined_analyzeMuons8_eta;1",	 		MuonEta8[i] );      
    files[i]->GetObject("combined_analyzeLeptonPair8_DimassRC_MM;1",	LepPairMassMM8[i] );     
    files[i]->GetObject("combined_analyzeLeptonPair8_DimassRC_ME;1",	LepPairMassEM8[i] );      
    files[i]->GetObject("combined_analyzeLeptonPair8_DimassRC_EE;1",	LepPairMassEE8[i] );      
    
    files[i]->GetObject("combined_analyzeElecs8_pt_MC;1", 		ElecPt8MC[i] );    
    files[i]->GetObject("combined_analyzeElecs8_eta_MC;1",	 	ElecEta8MC[i] );    
    files[i]->GetObject("combined_analyzeMuons8_pt_MC;1", 		MuonPt8MC[i] );    
    files[i]->GetObject("combined_analyzeMuons8_eta;1",	 		MuonEta8MC[i] );      
    files[i]->GetObject("combined_analyzeLeptonPair8_DimassRC_MM_MC;1",	LepPairMassMM8MC[i] );     
    files[i]->GetObject("combined_analyzeLeptonPair8_DimassRC_ME_MC;1",	LepPairMassEM8MC[i] );      
    files[i]->GetObject("combined_analyzeLeptonPair8_DimassRC_EE_MC;1",	LepPairMassEE8MC[i] );      
    
    files[i]->GetObject("combined_analyzeElecs9_pt;1", 			ElecPt9[i] );    
    files[i]->GetObject("combined_analyzeElecs9_eta;1",	 		ElecEta9[i] );    
    files[i]->GetObject("combined_analyzeMuons9_pt;1", 			MuonPt9[i] );    
    files[i]->GetObject("combined_analyzeMuons9_eta;1",	 		MuonEta9[i] );  
    files[i]->GetObject("combined_analyzeLeptonPair9_DimassRC_MM;1",	LepPairMassMM9[i] );     
    files[i]->GetObject("combined_analyzeLeptonPair9_DimassRC_ME;1",	LepPairMassEM9[i] );      
    files[i]->GetObject("combined_analyzeLeptonPair9_DimassRC_EE;1",	LepPairMassEE9[i] );      
    
    files[i]->GetObject("combined_analyzeElecs9_pt_MC;1", 		ElecPt9MC[i] );    
    files[i]->GetObject("combined_analyzeElecs9_eta_MC;1",	 	ElecEta9MC[i] );    
    files[i]->GetObject("combined_analyzeMuons9_pt_MC;1", 		MuonPt9MC[i] );    
    files[i]->GetObject("combined_analyzeMuons9_eta;1",	 		MuonEta9MC[i] );      
    files[i]->GetObject("combined_analyzeLeptonPair9_DimassRC_MM_MC;1",	LepPairMassMM9MC[i] );     
    files[i]->GetObject("combined_analyzeLeptonPair9_DimassRC_ME_MC;1",	LepPairMassEM9MC[i] );      
    files[i]->GetObject("combined_analyzeLeptonPair9_DimassRC_EE_MC;1",	LepPairMassEE9MC[i] );
    

    ElecPtBinned8[i] = ElecPt8[i]->Rebin(nbinsLepPt,TString(ElecPt8[i]->GetName())+=i,binsLepPt);  
    ElecEtaBinned8[i] = ElecEta8[i]->Rebin(nbinsLepEta,TString(ElecEta8[i]->GetName())+=i,binsLepEta);     
    MuonPtBinned8[i] = MuonPt8[i]->Rebin(nbinsLepPt,TString(MuonPt8[i]->GetName())+=i,binsLepPt); 
    MuonEtaBinned8[i] = MuonEta8[i]->Rebin(nbinsLepEta,TString(MuonEta8[i]->GetName())+=i,binsLepEta);      
    LepPairMassMMBinned8[i] = LepPairMassMM8[i]->Rebin(nbinsLepPairMass,TString(LepPairMassMM8[i]->GetName())+=i,binsLepPairMass);      
    LepPairMassEMBinned8[i] = LepPairMassEM8[i]->Rebin(nbinsLepPairMass,TString(LepPairMassEM8[i]->GetName())+=i,binsLepPairMass);        
    LepPairMassEEBinned8[i] = LepPairMassEE8[i]->Rebin(nbinsLepPairMass,TString(LepPairMassEE8[i]->GetName())+=i,binsLepPairMass);        

    ElecPtBinned8MC[i] = ElecPt8MC[i]->Rebin(nbinsLepPt,TString(ElecPt8MC[i]->GetName())+=i,binsLepPt);
    ElecEtaBinned8MC[i] = ElecEta8MC[i]->Rebin(nbinsLepEta,TString(ElecEta8MC[i]->GetName())+=i,binsLepEta);           
    MuonPtBinned8MC[i] = MuonPt8MC[i]->Rebin(nbinsLepPt,TString(MuonPt8MC[i]->GetName())+=i,binsLepPt);
    MuonEtaBinned8MC[i] = MuonEta8MC[i]->Rebin(nbinsLepEta,TString(MuonEta8MC[i]->GetName())+=i,binsLepEta);              
    LepPairMassMMBinned8MC[i] = LepPairMassMM8MC[i]->Rebin(nbinsLepPairMass,TString(LepPairMassMM8MC[i]->GetName())+=i,binsLepPairMass);  
    LepPairMassEMBinned8MC[i] = LepPairMassEM8MC[i]->Rebin(nbinsLepPairMass,TString(LepPairMassEM8MC[i]->GetName())+=i,binsLepPairMass);    
    LepPairMassEEBinned8MC[i] = LepPairMassEE8MC[i]->Rebin(nbinsLepPairMass,TString(LepPairMassEE8MC[i]->GetName())+=i,binsLepPairMass);  

    ElecPtBinned9[i] = ElecPt9[i]->Rebin(nbinsLepPt,TString(ElecPt9[i]->GetName())+=i,binsLepPt);
    ElecEtaBinned9[i] = ElecEta9[i]->Rebin(nbinsLepEta,TString(ElecEta9[i]->GetName())+=i,binsLepEta); 
    MuonPtBinned9[i] = MuonPt9[i]->Rebin(nbinsLepPt,TString(MuonPt9[i]->GetName())+=i,binsLepPt);
    cout << (TString(MuonEta9[i]->GetName())+=i) << endl;               
    MuonEtaBinned9[i] = MuonEta9[i]->Rebin(nbinsLepEta,TString(MuonEta9[i]->GetName())+=i,binsLepEta);             
    LepPairMassMMBinned9[i] = LepPairMassMM9[i]->Rebin(nbinsLepPairMass,TString(LepPairMassMM9[i]->GetName())+=i,binsLepPairMass); 
    LepPairMassEMBinned9[i] = LepPairMassEM9[i]->Rebin(nbinsLepPairMass,TString(LepPairMassEM9[i]->GetName())+=i,binsLepPairMass); 
    LepPairMassEEBinned9[i] = LepPairMassEE9[i]->Rebin(nbinsLepPairMass,TString(LepPairMassEE9[i]->GetName())+=i,binsLepPairMass);         

    ElecPtBinned9MC[i] = ElecPt9MC[i]->Rebin(nbinsLepPt,TString(ElecPt9MC[i]->GetName())+=i,binsLepPt);
    ElecEtaBinned9MC[i] = ElecEta9MC[i]->Rebin(nbinsLepEta,TString(ElecEta9MC[i]->GetName())+=i,binsLepEta); 
    MuonPtBinned9MC[i] = MuonPt9MC[i]->Rebin(nbinsLepPt,TString(MuonPt9MC[i]->GetName())+=i,binsLepPt);
    MuonEtaBinned9MC[i] = MuonEta9MC[i]->Rebin(nbinsLepEta,TString(MuonEta9MC[i]->GetName())+=i,binsLepEta);  
    LepPairMassMMBinned9MC[i] = LepPairMassMM9MC[i]->Rebin(nbinsLepPairMass,TString(LepPairMassMM9MC[i]->GetName())+=i,binsLepPairMass);    
    LepPairMassEMBinned9MC[i] = LepPairMassEM9MC[i]->Rebin(nbinsLepPairMass,TString(LepPairMassEM9MC[i]->GetName())+=i,binsLepPairMass);         
    LepPairMassEEBinned9MC[i] = LepPairMassEE9MC[i]->Rebin(nbinsLepPairMass,TString(LepPairMassEE9MC[i]->GetName())+=i,binsLepPairMass);  
   
    LepPt8[i] = (TH1*)ElecPtBinned8[i]->Clone();
    LepPt8[i]->Add(MuonPtBinned8[i]);
    
    LepEta8[i] = (TH1*)ElecEtaBinned8[i]->Clone();
    LepEta8[i]->Add(MuonEtaBinned8[i]);
    
    LepPairMass8[i] = (TH1*)LepPairMassMMBinned8[i]->Clone();
    LepPairMass8[i]->Add(LepPairMassEMBinned8[i]);    
    LepPairMass8[i]->Add(LepPairMassEEBinned8[i]);    
        

    LepPt8MC[i] = (TH1*)ElecPtBinned8MC[i]->Clone();
    LepPt8MC[i]->Add(MuonPtBinned8MC[i]);
    
    LepEta8MC[i] = (TH1*)ElecEtaBinned8MC[i]->Clone();
    LepEta8MC[i]->Add(MuonEtaBinned8MC[i]);
    
    LepPairMass8MC[i] = (TH1*)LepPairMassMMBinned8MC[i]->Clone();
    LepPairMass8MC[i]->Add(LepPairMassEMBinned8MC[i]);    
    LepPairMass8MC[i]->Add(LepPairMassEEBinned8MC[i]); 


    LepPt9[i] = (TH1*)ElecPtBinned9[i]->Clone();
    LepPt9[i]->Add(MuonPtBinned9[i]);
    
    LepEta9[i] = (TH1*)ElecEtaBinned9[i]->Clone();
    LepEta9[i]->Add(MuonEtaBinned9[i]);
    
    LepPairMass9[i] = (TH1*)LepPairMassMMBinned9[i]->Clone();
    LepPairMass9[i]->Add(LepPairMassEMBinned9[i]);    
    LepPairMass9[i]->Add(LepPairMassEEBinned9[i]);    
        

    LepPt9MC[i] =(TH1*) ElecPtBinned9MC[i]->Clone();
    LepPt9MC[i]->Add(MuonPtBinned9MC[i]);
    
    LepEta9MC[i] = (TH1*)ElecEtaBinned9MC[i]->Clone();
    LepEta9MC[i]->Add(MuonEtaBinned9MC[i]);
    
    LepPairMass9MC[i] = (TH1*)LepPairMassMMBinned9MC[i]->Clone();
    LepPairMass9MC[i]->Add(LepPairMassEMBinned9MC[i]);    
    LepPairMass9MC[i]->Add(LepPairMassEEBinned9MC[i]);                
  }
  
  

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // make plots  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // data vs. mc
  //CompareDataMC(LepPtDataHist[0],  LepPtSignalHist[0],  "KinEff_LepPt_DataMC");
  //CompareDataMC(LepEtaDataHist[0], LepEtaSignalHist[0], "KinEff_LepEta_DataMC");
  
  //CompareDataMC(LepPtDataHist[1],  LepPtSignalHist[1],  "KinEff_LepPt_DataMC_freeMass");
  //CompareDataMC(LepEtaDataHist[1], LepEtaSignalHist[1], "KinEff_LepEta_DataMC_freeMass"); 
  
  //CompareDataMC(LepPtDataHist[2],  LepPtSignalHist[2],  "KinEff_LepPt_DataMC_leadingJets");
  //CompareDataMC(LepEtaDataHist[2], LepEtaSignalHist[2], "KinEff_LepEta_DataMC_leadingJets");   
  
  //CompareDataMC(LepPtDataHist[3],  LepPtSignalHist[3],  "KinEff_LepPt_DataMC_leadingJets_freeMass");
  //CompareDataMC(LepEtaDataHist[3], LepEtaSignalHist[3], "KinEff_LepEta_DataMC_leadingJets_freeMass");


  // kin efficiencies: comparison of efficiencies with different settings in bins of top quantities
  //PlotHistsAndRatio(GenTopRapidityHist[0], GenTopRapidityHist[1], "KinEff_genTopRapidity_standardPlusFreeMass",    "b-tagging, m_{t} fixed", "b-tagging, m_{t} free"   );
  //PlotHistsAndRatio(GenTopRapidityHist[0], GenTopRapidityHist[2], "KinEff_genTopRapidity_standardPlusLeadingJets", "b-tagging, m_{t} fixed", "leading jets, m_{t} free");

  //PlotHistsAndRatio(GenTopPtHist[0], GenTopPtHist[1], "KinEff_genTopPt_standardPlusFreeMass",    "b-tagging, m_{t} fixed", "b-tagging, m_{t} free"   );
  //PlotHistsAndRatio(GenTopPtHist[0], GenTopPtHist[2], "KinEff_genTopPt_standardPlusLeadingJets", "b-tagging, m_{t} fixed", "leading jets, m_{t} free");
  
  //PlotHistsAndRatio(GenTtBarRapidityHist[0], GenTtBarRapidityHist[1], "KinEff_genTtBarRapidity_standardPlusFreeMass",    "b-tagging, m_{t} fixed", "b-tagging, m_{t} free"   );
  //PlotHistsAndRatio(GenTtBarRapidityHist[0], GenTtBarRapidityHist[2], "KinEff_genTtBarRapidity_standardPlusLeadingJets", "b-tagging, m_{t} fixed", "leading jets, m_{t} free");

  //PlotHistsAndRatio(GenTtBarPtHist[0], GenTtBarPtHist[1], "KinEff_genTtBarPt_standardPlusFreeMass",    "b-tagging, m_{t} fixed", "b-tagging, m_{t} free"   );
  //PlotHistsAndRatio(GenTtBarPtHist[0], GenTtBarPtHist[2], "KinEff_genTtBarPt_standardPlusLeadingJets", "b-tagging, m_{t} fixed", "leading jets, m_{t} free");

  //PlotHistsAndRatio(GenTtBarMassHist[0], GenTtBarMassHist[1], "KinEff_genTtBarMass_standardPlusFreeMass",    "b-tagging, m_{t} fixed", "b-tagging, m_{t} free"   );
  //PlotHistsAndRatio(GenTtBarMassHist[0], GenTtBarMassHist[2], "KinEff_genTtBarMass_standardPlusLeadingJets", "b-tagging, m_{t} fixed", "leading jets, m_{t} free");


  // kin efficiencies: comparison of yields with different settings in bins of top quantities
  PlotHistsAndRatio(YieldLepPtHist[0],       YieldLepPtHist[1],	  "YieldEff_LepPt_standard",       "b-tagging, m_{t} fixed", "b-tagging, m_{t} free");
  
  


  PlotHistsAndRatio(YieldLepPtHist[0],       YieldLepPtHist[1],       YieldSigMcLepPtHist[0],       YieldSigMcLepPtHist[1],	  "YieldRatio_LepPt_standardPlusFreeMass",       "b-tagging, m_{t} fixed", "b-tagging, m_{t} free");
  PlotHistsAndRatio(YieldLepEtaHist[0],      YieldLepEtaHist[1],      YieldSigMcLepEtaHist[0],      YieldSigMcLepEtaHist[1],	  "YieldRatio_LepEta_standardPlusFreeMass",      "b-tagging, m_{t} fixed", "b-tagging, m_{t} free");
  PlotHistsAndRatio(YieldTopPtHist[0],       YieldTopPtHist[1],       YieldSigMcTopPtHist[0],       YieldSigMcTopPtHist[1],	  "YieldRatio_TopPt_standardPlusFreeMass",       "b-tagging, m_{t} fixed", "b-tagging, m_{t} free");
  PlotHistsAndRatio(YieldTopRapidityHist[0], YieldTopRapidityHist[1], YieldSigMcTopRapidityHist[0], YieldSigMcTopRapidityHist[1], "YieldRatio_TopRapidity_standardPlusFreeMass", "b-tagging, m_{t} fixed", "b-tagging, m_{t} free");

  PlotHistsAndRatio(YieldLepPtHist[1], YieldLepPtHist[0], YieldLepPtHist[2], YieldLepPtHist[3], 
                    YieldSigMcLepPtHist[1], YieldSigMcLepPtHist[0], YieldSigMcLepPtHist[2], YieldSigMcLepPtHist[3], "YieldRatios_LepPt");		    
  PlotHistsAndRatio(YieldLepEtaHist[1], YieldLepEtaHist[0], YieldLepEtaHist[2], YieldLepEtaHist[3], 
                    YieldSigMcLepEtaHist[1], YieldSigMcLepEtaHist[0], YieldSigMcLepEtaHist[2], YieldSigMcLepEtaHist[3], "YieldRatios_LepEta");		    		    
  PlotHistsAndRatio(YieldTopPtHist[1], YieldTopPtHist[0], YieldTopPtHist[2], YieldTopPtHist[3], 
                    YieldSigMcTopPtHist[1], YieldSigMcTopPtHist[0], YieldSigMcTopPtHist[2], YieldSigMcTopPtHist[3], "YieldRatios_TopPt");		    
  PlotHistsAndRatio(YieldTopRapidityHist[1], YieldTopRapidityHist[0], YieldTopRapidityHist[2], YieldTopRapidityHist[3], 
                    YieldSigMcTopRapidityHist[1], YieldSigMcTopRapidityHist[0], YieldSigMcTopRapidityHist[2], YieldSigMcTopRapidityHist[3], "YieldRatios_TopRapidity");
		    
		    
		    
  PlotHistsAndRatio(LepPt9[0], LepPt8[0], LepPt9MC[0], LepPt8MC[0], "KinEff_LepPt_standard", "after kin reco", "before kin reco", "p_{T}^{l^{+} and l^{-}} #left[#frac{GeV}{c}#right]", "N_{evts}", "#epsilon_{kin}");
  PlotHistsAndRatio(LepEta9[0], LepEta8[0], LepEta9MC[0], LepEta8MC[0], "KinEff_LepEta_standard", "after kin reco", "before kin reco", "#eta^{l^{+} and l^{-}}", "N_{evts}", "#epsilon_{kin}");
  PlotHistsAndRatio(LepPairMass9[0], LepPairMass8[0], LepPairMass9MC[0], LepPairMass8MC[0], "KinEff_LepPairMass_standard", "after kin reco", "before kin reco", "M^{l^{+}l^{-}} #left[#frac{GeV}{c^{2}}#right]", "N_{evts}", "#epsilon_{kin}");

  
  PlotHistsAndRatio(LepPt9[1], LepPt8[1], LepPt9MC[1], LepPt8MC[1], "KinEff_LepPt_freeMass", "after kin reco", "before kin reco", "p_{T}^{l^{+} and l^{-}} #left[#frac{GeV}{c}#right]", "N_{evts}", "#epsilon_{kin}");
  PlotHistsAndRatio(LepEta9[1], LepEta8[1], LepEta9MC[1], LepEta8MC[1], "KinEff_LepEta_freeMass", "after kin reco", "before kin reco", "#eta^{l^{+} and l^{-}}", "N_{evts}", "#epsilon_{kin}");
  PlotHistsAndRatio(LepPairMass9[1], LepPairMass8[1], LepPairMass9MC[1], LepPairMass8MC[1], "KinEff_LepPairMass_freeMass", "after kin reco", "before kin reco", "M^{l^{+}l^{-}} #left[#frac{GeV}{c^{2}}#right]", "N_{evts}", "#epsilon_{kin}");

  PlotHistsAndRatio(LepPt9[2], LepPt8[2], LepPt9MC[2], LepPt8MC[2], "KinEff_LepPt_leadingJets", "after kin reco", "before kin reco", "p_{T}^{l^{+} and l^{-}} #left[#frac{GeV}{c}#right]", "N_{evts}", "#epsilon_{kin}");
  PlotHistsAndRatio(LepEta9[2], LepEta8[2], LepEta9MC[2], LepEta8MC[2], "KinEff_LepEta_leadingJets", "after kin reco", "before kin reco", "#eta^{l^{+} and l^{-}}", "N_{evts}", "#epsilon_{kin}");
  PlotHistsAndRatio(LepPairMass9[2], LepPairMass8[2], LepPairMass9MC[2], LepPairMass8MC[2], "KinEff_LepPairMass_leadingJets", "after kin reco", "before kin reco", "M^{l^{+}l^{-}} #left[#frac{GeV}{c^{2}}#right]", "N_{evts}", "#epsilon_{kin}");

  PlotHistsAndRatio(LepPt9[3], LepPt8[3], LepPt9MC[3], LepPt8MC[3], "KinEff_LepPt_leadingJets_freeMass", "after kin reco", "before kin reco", "p_{T}^{l^{+} and l^{-}} #left[#frac{GeV}{c}#right]", "N_{evts}", "#epsilon_{kin}");
  PlotHistsAndRatio(LepEta9[3], LepEta8[3], LepEta9MC[3], LepEta8MC[3], "KinEff_LepEta_leadingJets_freeMass", "after kin reco", "before kin reco", "#eta^{l^{+} and l^{-}}", "N_{evts}", "#epsilon_{kin}");
  PlotHistsAndRatio(LepPairMass9[3], LepPairMass8[3], LepPairMass9MC[3], LepPairMass8MC[3], "KinEff_LepPairMass_leadingJets_freeMass", "after kin reco", "before kin reco", "M^{l^{+}l^{-}} #left[#frac{GeV}{c^{2}}#right]", "N_{evts}", "#epsilon_{kin}");
		    
}
