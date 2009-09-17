#include <iostream>

#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TROOT.h>

void setHistoStyle(TH1* hist1, TH1* hist2, unsigned int i, bool norm = false);
void setAxesStyle(TH1& hist, const char* titleX, const char* titleY);

void analyzeMuonCutFlow()
{

  // open input files

  TFile* fileSig = new TFile("analyzeMuonCutFlow_sig.root");
  TFile* fileBkg = new TFile("analyzeMuonCutFlow_bkg.root");

  const int nrOfDirs = 10;

  TString directories[2*nrOfDirs] = {"analyzeMuonQuality",
				     "QualityCombinedMuons",
				     "QualityHighptMuons",
				     "QualityCentralMuons",   
				     "QualityEnoughHitsMuons",
				     "QualitySignificantMuons",
				     "QualityReliableFitMuons",
				     "QualityLowEcalMuons",    
				     "QualityLowHcalMuons",    
				     "QualityIsolatedMuons",
				     "analyzeMuonKinematics",
				     "KinematicsCombinedMuons",
				     "KinematicsHighptMuons",
				     "KinematicsCentralMuons",   
				     "KinematicsEnoughHitsMuons",
				     "KinematicsSignificantMuons",
				     "KinematicsReliableFitMuons",
				     "KinematicsLowEcalMuons",    
				     "KinematicsLowHcalMuons",    
				     "KinematicsIsolatedMuons"};

  gROOT->cd();
  gROOT->SetStyle("Plain");

  //  
  // get histograms
  //
  
  // histograms for selection variables

  TH1F* nHit_sig  [nrOfDirs];
  TH1F* chi2_sig  [nrOfDirs];
  TH1F* d0_sig    [nrOfDirs];
  TH1F* eisoEn_sig[nrOfDirs];
  TH1F* hisoEn_sig[nrOfDirs];
  TH1F* relIso_sig[nrOfDirs];

  TH1F* nHit_bkg  [nrOfDirs];
  TH1F* chi2_bkg  [nrOfDirs];
  TH1F* d0_bkg    [nrOfDirs];
  TH1F* eisoEn_bkg[nrOfDirs];
  TH1F* hisoEn_bkg[nrOfDirs];
  TH1F* relIso_bkg[nrOfDirs];

  for(unsigned int i = 0; i < nrOfDirs; i++) {
    nHit_sig  [i] = (TH1F*) fileSig->Get(directories[i]+"/nHit"  )->Clone();
    chi2_sig  [i] = (TH1F*) fileSig->Get(directories[i]+"/chi2"  )->Clone();
    d0_sig    [i] = (TH1F*) fileSig->Get(directories[i]+"/d0"    )->Clone();
    eisoEn_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/ecalEn")->Clone();
    hisoEn_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/hcalEn")->Clone();
    relIso_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/relIso")->Clone();

    nHit_bkg  [i] = (TH1F*) fileBkg->Get(directories[i]+"/nHit"  )->Clone();
    chi2_bkg  [i] = (TH1F*) fileBkg->Get(directories[i]+"/chi2"  )->Clone();
    d0_bkg    [i] = (TH1F*) fileBkg->Get(directories[i]+"/d0"    )->Clone();
    eisoEn_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/ecalEn")->Clone();
    hisoEn_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/hcalEn")->Clone();
    relIso_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/relIso")->Clone();
  }

  // histograms for monitoring variables

  TH1F* calCmp_sig[nrOfDirs];
  TH1F* ecalEn_sig[nrOfDirs];
  TH1F* ecalS9_sig[nrOfDirs];
  TH1F* hcalEn_sig[nrOfDirs];
  TH1F* hcalS9_sig[nrOfDirs];
  TH1F* houtEn_sig[nrOfDirs];
  TH1F* houtS9_sig[nrOfDirs];

  TH1F* calCmp_bkg[nrOfDirs];
  TH1F* ecalEn_bkg[nrOfDirs];
  TH1F* ecalS9_bkg[nrOfDirs];
  TH1F* hcalEn_bkg[nrOfDirs];
  TH1F* hcalS9_bkg[nrOfDirs];
  TH1F* houtEn_bkg[nrOfDirs];
  TH1F* houtS9_bkg[nrOfDirs];

  for(unsigned int i = 0; i < nrOfDirs; i++) {
    calCmp_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/calCmp_")->Clone();
    ecalEn_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/ecalEn_")->Clone();
    ecalS9_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/ecalS9_")->Clone();
    hcalEn_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/hcalEn_")->Clone();
    hcalS9_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/hcalS9_")->Clone();
    houtEn_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/houtEn_")->Clone();
    houtS9_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/houtS9_")->Clone();
	   
    calCmp_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/calCmp_")->Clone();
    ecalEn_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/ecalEn_")->Clone();
    ecalS9_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/ecalS9_")->Clone();
    hcalEn_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/hcalEn_")->Clone();
    hcalS9_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/hcalS9_")->Clone();
    houtEn_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/houtEn_")->Clone();
    houtS9_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/houtS9_")->Clone();
  }

  // histograms for isolation monitoring variables

  TH1F* trkIsoN_sig[nrOfDirs];
  TH1F* trkIso_sig [nrOfDirs];
  TH1F* eclIsoN_sig[nrOfDirs];
  TH1F* hclIsoN_sig[nrOfDirs];
  TH1F* calIso_sig [nrOfDirs];

  TH1F* trkIsoN_bkg[nrOfDirs];
  TH1F* trkIso_bkg [nrOfDirs];
  TH1F* eclIsoN_bkg[nrOfDirs];
  TH1F* hclIsoN_bkg[nrOfDirs];
  TH1F* calIso_bkg [nrOfDirs];

  for(unsigned int i = 0; i < nrOfDirs; i++) {
    trkIsoN_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/trkIsoN_")->Clone();
    trkIso_sig [i] = (TH1F*) fileSig->Get(directories[i]+"/trkIso_" )->Clone();
    eclIsoN_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/eclIsoN_")->Clone();
    hclIsoN_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/hclIsoN_")->Clone();
    calIso_sig [i] = (TH1F*) fileSig->Get(directories[i]+"/calIso_" )->Clone();

    trkIsoN_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/trkIsoN_")->Clone();
    trkIso_bkg [i] = (TH1F*) fileBkg->Get(directories[i]+"/trkIso_" )->Clone();
    eclIsoN_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/eclIsoN_")->Clone();
    hclIsoN_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/hclIsoN_")->Clone();
    calIso_bkg [i] = (TH1F*) fileBkg->Get(directories[i]+"/calIso_" )->Clone();
  }

  // histograms for energy & object flow variables

  TH1F* trkDRN_sig[nrOfDirs];
  TH1F* trkDR_sig [nrOfDirs];
  TH1F* eclDRN_sig[nrOfDirs];
  TH1F* hclDRN_sig[nrOfDirs];
  TH1F* calDR_sig [nrOfDirs];

  TH1F* trkDRN_bkg[nrOfDirs];
  TH1F* trkDR_bkg [nrOfDirs];
  TH1F* eclDRN_bkg[nrOfDirs];
  TH1F* hclDRN_bkg[nrOfDirs];
  TH1F* calDR_bkg [nrOfDirs];

  for(unsigned int i = 0; i < nrOfDirs; i++) {
    trkDRN_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/trkDRN_")->Clone();
    trkDR_sig [i] = (TH1F*) fileSig->Get(directories[i]+"/trkDR_" )->Clone();
    eclDRN_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/eclDRN_")->Clone();
    hclDRN_sig[i] = (TH1F*) fileSig->Get(directories[i]+"/hclDRN_")->Clone();
    calDR_sig [i] = (TH1F*) fileSig->Get(directories[i]+"/calDR_" )->Clone();
    		  					  	      
    trkDRN_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/trkDRN_")->Clone();
    trkDR_bkg [i] = (TH1F*) fileBkg->Get(directories[i]+"/trkDR_" )->Clone();
    eclDRN_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/eclDRN_")->Clone();
    hclDRN_bkg[i] = (TH1F*) fileBkg->Get(directories[i]+"/hclDRN_")->Clone();
    calDR_bkg [i] = (TH1F*) fileBkg->Get(directories[i]+"/calDR_" )->Clone();
  }

  // histograms for kinematic variables

  TH1F* en_sig [nrOfDirs];
  TH1F* pt_sig [nrOfDirs];
  TH1F* eta_sig[nrOfDirs];
  TH1F* phi_sig[nrOfDirs];
  TH1F* n_sig  [nrOfDirs];

  TH1F* en_bkg [nrOfDirs];
  TH1F* pt_bkg [nrOfDirs];
  TH1F* eta_bkg[nrOfDirs];
  TH1F* phi_bkg[nrOfDirs];
  TH1F* n_bkg  [nrOfDirs];

  for(unsigned int i = 0; i < nrOfDirs; i++) {
    en_sig [i] = (TH1F*) fileSig->Get(directories[i+nrOfDirs]+"/en" )->Clone();
    pt_sig [i] = (TH1F*) fileSig->Get(directories[i+nrOfDirs]+"/pt" )->Clone();
    eta_sig[i] = (TH1F*) fileSig->Get(directories[i+nrOfDirs]+"/eta")->Clone();
    phi_sig[i] = (TH1F*) fileSig->Get(directories[i+nrOfDirs]+"/phi")->Clone();
    n_sig  [i] = (TH1F*) fileSig->Get(directories[i+nrOfDirs]+"/n"  )->Clone();
    	       	  					  	            
    en_bkg [i] = (TH1F*) fileBkg->Get(directories[i+nrOfDirs]+"/en" )->Clone();
    pt_bkg [i] = (TH1F*) fileBkg->Get(directories[i+nrOfDirs]+"/pt" )->Clone();
    eta_bkg[i] = (TH1F*) fileBkg->Get(directories[i+nrOfDirs]+"/eta")->Clone();
    phi_bkg[i] = (TH1F*) fileBkg->Get(directories[i+nrOfDirs]+"/phi")->Clone();
    n_bkg  [i] = (TH1F*) fileBkg->Get(directories[i+nrOfDirs]+"/n"  )->Clone();
  }

  // close input files

  fileSig->Close();
  fileBkg->Close();

  //
  // configure histograms
  //
  
  // histograms for selection variables

  for(unsigned int i = 0; i < nrOfDirs; i++) {
    setHistoStyle(nHit_sig  [i], nHit_bkg  [i], i);
    setHistoStyle(chi2_sig  [i], chi2_bkg  [i], i);
    setHistoStyle(d0_sig    [i], d0_bkg    [i], i);
    setHistoStyle(eisoEn_sig[i], eisoEn_bkg[i], i);
    setHistoStyle(hisoEn_sig[i], hisoEn_bkg[i], i);
    setHistoStyle(relIso_sig[i], relIso_bkg[i], i);
  }

  // histograms for monitoring variables

  for(unsigned int i = 0; i < nrOfDirs; i++) {
    setHistoStyle(calCmp_sig[i], calCmp_bkg[i], i);
    setHistoStyle(ecalEn_sig[i], ecalEn_bkg[i], i);
    setHistoStyle(ecalS9_sig[i], ecalS9_bkg[i], i);
    setHistoStyle(hcalEn_sig[i], hcalEn_bkg[i], i);
    setHistoStyle(hcalS9_sig[i], hcalS9_bkg[i], i);
    setHistoStyle(houtEn_sig[i], houtEn_bkg[i], i);
    setHistoStyle(houtS9_sig[i], houtS9_bkg[i], i);
  }

  // histograms for isolation monitoring variables

  for(unsigned int i = 0; i < nrOfDirs; i++) {
    setHistoStyle(trkIsoN_sig[i], trkIsoN_bkg[i], i);
    setHistoStyle(trkIso_sig [i], trkIso_bkg [i], i);
    setHistoStyle(eclIsoN_sig[i], eclIsoN_bkg[i], i);
    setHistoStyle(hclIsoN_sig[i], hclIsoN_bkg[i], i);
    setHistoStyle(calIso_sig [i], calIso_bkg [i], i);
  }

  // histograms for energy & object flow variables

  for(unsigned int i = 0; i < nrOfDirs; i++) {
    setHistoStyle(trkDRN_sig[i], trkDRN_bkg[i], i);
    setHistoStyle(trkDR_sig [i], trkDR_bkg [i], i);
    setHistoStyle(eclDRN_sig[i], eclDRN_bkg[i], i);
    setHistoStyle(hclDRN_sig[i], hclDRN_bkg[i], i);
    setHistoStyle(calDR_sig [i], calDR_bkg [i], i);
  }

  // histograms for kinematic variables

  for(unsigned int i = 0; i < nrOfDirs; i++) {
    setHistoStyle(en_sig [i], en_bkg [i], i);
    setHistoStyle(pt_sig [i], pt_bkg [i], i);
    setHistoStyle(eta_sig[i], eta_bkg[i], i);
    setHistoStyle(phi_sig[i], phi_bkg[i], i);
    setHistoStyle(n_sig  [i], n_bkg  [i], i);
  }

  // create a legend

  TLegend *legend = new TLegend(0.1, 0.65, 0.9, 0.9);
  legend->SetFillStyle(0);
  legend->AddEntry(nHit_sig[0], "Signal"    , "L");
  legend->AddEntry(nHit_bkg[0], "Background", "L");
  legend->SetTextSize(0.04);
  
  //
  // draw canvas
  //

  TCanvas* canvasSelVar = new TCanvas("canvasSelVar", "selection variables", 900, 600);
  canvasSelVar->Divide(3,2);

  TCanvas* canvasMonVar = new TCanvas("canvasMonVar", "monitoring variables", 1200, 600);
  canvasMonVar->Divide(4,2);

  TCanvas* canvasIsoMonVar = new TCanvas("canvasIsoMonVar", "isolation monitoring variables", 900, 600);
  canvasIsoMonVar->Divide(3,2);

  TCanvas* canvasFlowVar = new TCanvas("canvasFlowVar", "energy & object flow variables", 900, 600);
  canvasFlowVar->Divide(3,2);

  TCanvas* canvasKinVar = new TCanvas("canvasKinVar", "kinematic variables", 900, 600);
  canvasKinVar->Divide(3,2);

  char cutChar[30];

  for(unsigned int i = 0; i < nrOfDirs; i++) {

    // canvas for selection variables

    sprintf(cutChar,"selection variables after %i cuts",i);
    legend->SetHeader(cutChar);

    canvasSelVar->cd(1);
    nHit_sig[i]->Draw("");
    nHit_bkg[i]->Draw("same");
  
    canvasSelVar->cd(2);
    chi2_sig[i]->Draw("");
    chi2_bkg[i]->Draw("same");
    legend->Draw();

    canvasSelVar->cd(3);
    d0_sig[i]->Draw("");
    d0_bkg[i]->Draw("same");

    canvasSelVar->cd(4);
    eisoEn_sig[i]->Draw("");
    eisoEn_bkg[i]->Draw("same");

    canvasSelVar->cd(5);
    hcalEn_sig[i]->Draw("");
    hcalEn_bkg[i]->Draw("same");

    canvasSelVar->cd(6);
    relIso_sig[i]->Draw("");
    relIso_bkg[i]->Draw("same");

    if(i == 0)canvasSelVar->Print("analyzeMuonCutFlow.ps(");
    else canvasSelVar->Print("analyzeMuonCutFlow.ps");

    // canvas for monitoring variables

    sprintf(cutChar,"monitoring variables after %i cuts",i);
    legend->SetHeader(cutChar);

    canvasMonVar->cd(1);
    calCmp_sig[i]->Draw("");
    calCmp_bkg[i]->Draw("same");
  
    canvasMonVar->cd(2);
    ecalEn_sig[i]->Draw("");
    ecalEn_bkg[i]->Draw("same");
    legend->Draw();

    canvasMonVar->cd(3);
    ecalS9_sig[i]->Draw("");
    ecalS9_bkg[i]->Draw("same");

    canvasMonVar->cd(4);
    hcalEn_sig[i]->Draw("");
    hcalEn_bkg[i]->Draw("same");

    canvasMonVar->cd(5);
    hcalS9_sig[i]->Draw("");
    hcalS9_bkg[i]->Draw("same");

    canvasMonVar->cd(6);
    houtEn_sig[i]->Draw("");
    houtEn_bkg[i]->Draw("same");

    canvasMonVar->cd(7);
    houtS9_sig[i]->Draw("");
    houtS9_bkg[i]->Draw("same");

    canvasMonVar->Print("analyzeMuonCutFlow.ps");

    // canvas for isolation monitoring variables

    sprintf(cutChar,"isolation monitoring variables after %i cuts",i);
    legend->SetHeader(cutChar);

    canvasIsoMonVar->cd(1);
    trkIsoN_sig[i]->Draw("");
    trkIsoN_bkg[i]->Draw("same");
  
    canvasIsoMonVar->cd(2);
    trkIso_sig[i]->Draw("");
    trkIso_bkg[i]->Draw("same");
    legend->Draw();

    canvasIsoMonVar->cd(3);
    eclIsoN_sig[i]->Draw("");
    eclIsoN_bkg[i]->Draw("same");

    canvasIsoMonVar->cd(4);
    hclIsoN_sig[i]->Draw("");
    hclIsoN_bkg[i]->Draw("same");

    canvasIsoMonVar->cd(5);
    calIso_sig[i]->Draw("");
    calIso_bkg[i]->Draw("same");

    canvasIsoMonVar->Print("analyzeMuonCutFlow.ps");

    // canvas for energy & object flow variables

    sprintf(cutChar,"energy & object flow variables after %i cuts",i);
    legend->SetHeader(cutChar);

    canvasFlowVar->cd(1);
    trkDRN_sig[i]->Draw("");
    trkDRN_bkg[i]->Draw("same");
  
    canvasFlowVar->cd(2);
    trkDR_sig[i]->Draw("");
    trkDR_bkg[i]->Draw("same");
    legend->Draw();

    canvasFlowVar->cd(3);
    eclDRN_sig[i]->Draw("");
    eclDRN_bkg[i]->Draw("same");

    canvasFlowVar->cd(4);
    hclDRN_sig[i]->Draw("");
    hclDRN_bkg[i]->Draw("same");

    canvasFlowVar->cd(5);
    calDR_sig[i]->Draw("");
    calDR_bkg[i]->Draw("same");

    canvasFlowVar->Print("analyzeMuonCutFlow.ps");

    // canvas for kinematic variables

    sprintf(cutChar,"kinematic variables after %i cuts",i);
    legend->SetHeader(cutChar);

    canvasKinVar->cd(1);
    en_sig[i]->Draw("");
    en_bkg[i]->Draw("same");
  
    canvasKinVar->cd(2);
    pt_sig[i]->Draw("");
    pt_bkg[i]->Draw("same");
    legend->Draw();

    canvasKinVar->cd(3);
    eta_sig[i]->Draw("");
    eta_bkg[i]->Draw("same");

    canvasKinVar->cd(4);
    phi_sig[i]->Draw("");
    phi_bkg[i]->Draw("same");

    canvasKinVar->cd(5);
    n_sig[i]->Draw("");
    n_bkg[i]->Draw("same");

    if(i == nrOfDirs)canvasKinVar->Print("analyzeMuonCutFlow.ps)");
    else canvasKinVar->Print("analyzeMuonCutFlow.ps");

  }

}

void setHistoStyle(TH1* hist1, TH1* hist2, unsigned int i, bool norm) {

  hist1->SetLineWidth(2);
  hist2->SetLineWidth(2);
  hist1->SetLineColor(kRed);
  hist2->SetLineColor(kBlue);

  setAxesStyle(*hist1, hist1->GetTitle(), "events");
  hist1->SetStats(kFALSE);

  double max = hist2->GetMaximum();
  if(max>hist1->GetMaximum())hist1->SetMaximum(1.1*max);

  if(norm) {
    hist1->Scale(1./hist1->Integral());
    hist2->Scale(1./hist2->Integral());
    hist1->SetYTitle("a.u.");
  }

}

void setAxesStyle(TH1& hist, const char* titleX, const char* titleY) {
	hist.SetTitle("");

	hist.GetXaxis()->SetTitle(titleX);
	hist.GetXaxis()->SetTitleSize( 0.06);
	hist.GetXaxis()->SetTitleColor( 1);
	hist.GetXaxis()->SetTitleOffset( 0.8);
	hist.GetXaxis()->SetTitleFont( 62);
	hist.GetXaxis()->SetLabelSize( 0.05);
	hist.GetXaxis()->SetLabelFont( 62);
	hist.GetXaxis()->CenterTitle();
	hist.GetXaxis()->SetNdivisions( 505);

	hist.GetYaxis()->SetTitle(titleY);
	hist.GetYaxis()->SetTitleSize( 0.07);
	hist.GetYaxis()->SetTitleColor( 1);
	hist.GetYaxis()->SetTitleOffset( 0.9);
	hist.GetYaxis()->SetTitleFont( 62);
	hist.GetYaxis()->SetLabelSize( 0.05);
	hist.GetYaxis()->SetLabelFont( 62);
}
