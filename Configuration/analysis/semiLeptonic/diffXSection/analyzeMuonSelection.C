#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>

enum styles {kSignal, kQCD, kWmunu, kZmumu};

void canvasStyle(TCanvas* canv);
void histogramStyle(TH1* hist, unsigned int style);
void axesStyle(TH1* hist, const char* titleX, const char* titleY);
void drawcutline(double cutval, double maximum);

void analyzeMuonSelection(TString whichMuons = "")
{
  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  files_.push_back(new TFile("./analyzeMuons_TTbar_sig.root") );
  files_.push_back(new TFile("./analyzeMuons_QCD.root") );
  files_.push_back(new TFile("./analyzeMuons_Wmunu.root") );
  files_.push_back(new TFile("./analyzeMuons_Zmumu.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TString> thoseMuons;
  if(whichMuons != "")
    for(int i=0; i<6; i++)thoseMuons.push_back(whichMuons);
  else{
    for(int i=0; i<3; i++)thoseMuons.push_back("triggerMuon");
    for(int i=0; i<2; i++)thoseMuons.push_back("goodMuon");
    thoseMuons.push_back("goldenMuon");
  }
    std::vector<TH1F*> nHit_, chi2_, d0_, ecalEn_, hcalEn_, relIso_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    nHit_  .push_back( (TH1F*)files_[idx]->Get(thoseMuons[0]+"Quality/nHit"  )->Clone() );
    chi2_  .push_back( (TH1F*)files_[idx]->Get(thoseMuons[1]+"Quality/chi2"  )->Clone() );
    d0_    .push_back( (TH1F*)files_[idx]->Get(thoseMuons[2]+"Quality/d0"    )->Clone() );
    ecalEn_.push_back( (TH1F*)files_[idx]->Get(thoseMuons[3]+"Quality/ecalEn")->Clone() );
    hcalEn_.push_back( (TH1F*)files_[idx]->Get(thoseMuons[4]+"Quality/hcalEn")->Clone() );
    relIso_.push_back( (TH1F*)files_[idx]->Get(thoseMuons[5]+"Quality/relIso")->Clone() );
  }

  // ---
  //    close input files
  // ---
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    //files_[idx]->Close();
  }
  
  // ---
  //    configure histograms
  // ---

  // nHit_
  histogramStyle(nHit_  [kSignal], kSignal);
  histogramStyle(nHit_  [kQCD   ], kQCD   );
  histogramStyle(nHit_  [kWmunu ], kWmunu );
  histogramStyle(nHit_  [kZmumu ], kZmumu );


  // chi2_
  histogramStyle(chi2_ [kSignal], kSignal);
  histogramStyle(chi2_ [kQCD   ], kQCD   );
  histogramStyle(chi2_ [kWmunu ], kWmunu );
  histogramStyle(chi2_ [kZmumu ], kZmumu );

  // d0_
  histogramStyle(d0_[kSignal], kSignal);
  histogramStyle(d0_[kQCD   ], kQCD   );
  histogramStyle(d0_[kWmunu ], kWmunu );
  histogramStyle(d0_[kZmumu ], kZmumu );

  // ecalEn_
  histogramStyle(ecalEn_[kSignal], kSignal);
  histogramStyle(ecalEn_[kQCD   ], kQCD   );
  histogramStyle(ecalEn_[kWmunu ], kWmunu );
  histogramStyle(ecalEn_[kZmumu ], kZmumu ); 

  // hcalEn_
  histogramStyle(hcalEn_[kSignal], kSignal);
  histogramStyle(hcalEn_[kQCD   ], kQCD   );
  histogramStyle(hcalEn_[kWmunu ], kWmunu );
  histogramStyle(hcalEn_[kZmumu ], kZmumu ); 

  // relIso_
  histogramStyle(relIso_[kSignal], kSignal);
  histogramStyle(relIso_[kQCD   ], kQCD   );
  histogramStyle(relIso_[kWmunu ], kWmunu );
  histogramStyle(relIso_[kZmumu ], kZmumu ); 


  // ---
  //    do the printing for nHit_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(canv0);

  // create a legend (in upper right corner)
  
  TLegend *leg0 = new TLegend(0.55, 0.65, 1.15, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  leg0->AddEntry( nHit_  [kSignal] , "semi-lep. ( #mu )"         , "PL" );
  leg0->AddEntry( nHit_  [kQCD   ] , "QCD" , "FL" );
  leg0->AddEntry( nHit_  [kWmunu ] , "W->#mu#nu"      , "FL" );
  leg0->AddEntry( nHit_  [kZmumu ] , "Z->#mu#mu"      , "FL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 0.95, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  leg1->AddEntry( nHit_  [kSignal] , "semi-lep. ( #mu )"         , "PL" );
  leg1->AddEntry( nHit_  [kQCD   ] , "QCD" , "FL" );
  leg1->AddEntry( nHit_  [kWmunu ] , "W->#mu#nu"      , "FL" );
  leg1->AddEntry( nHit_  [kZmumu ] , "Z->#mu#mu"      , "FL" );
  
  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  axesStyle(nHit_  [kSignal], "NHit_{#mu trk}", "events");
  nHit_  [kSignal]->SetMinimum(1.);
  double max=nHit_[kSignal]->GetMaximum();
  if(max<nHit_[kQCD]->GetMaximum())max=nHit_[kQCD]->GetMaximum();
  if(max<nHit_[kWmunu]->GetMaximum())max=nHit_[kWmunu]->GetMaximum();
  if(max<nHit_[kZmumu]->GetMaximum())max=nHit_[kZmumu]->GetMaximum();
  nHit_  [kSignal]->SetMaximum( 1.7* max );
  nHit_  [kSignal]->Draw();
  nHit_  [kQCD   ]->Draw("same");
  nHit_  [kWmunu]->Draw("same");
  nHit_  [kZmumu]->Draw("same");
  //n_  [kSignal       ]->Draw("esame");
  leg0->Draw("same");
  drawcutline(11., max);

  // ---
  //    do the printing for chi2_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetLogy(1);
  axesStyle(chi2_ [kSignal], "#chi^{2}( #mu ) [GeV]", "events");
  max=chi2_[kSignal]->GetMaximum();
  if(max<chi2_[kQCD]->GetMaximum())max=chi2_[kQCD]->GetMaximum();
  if(max<chi2_[kWmunu]->GetMaximum())max=chi2_[kWmunu]->GetMaximum();
  if(max<chi2_[kZmumu]->GetMaximum())max=chi2_[kZmumu]->GetMaximum();
  chi2_ [kSignal       ]->SetMaximum( 1.7* max );
  chi2_ [kSignal       ]->Draw();
  chi2_ [kQCD    ]->Draw("same");
  chi2_ [kWmunu]->Draw("same");
  chi2_ [kZmumu]->Draw("same");
  leg0->Draw("same");
  drawcutline(10., max);

  // ---
  //    do the printing for d0_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetLogy(1);
  axesStyle(d0_[kSignal], "d0( #mu )", "events");
  //d0_[kSignal       ]->SetMinimum( 0 );
  max=d0_[kSignal]->GetMaximum();
  if(max<d0_[kQCD]->GetMaximum())max=d0_[kQCD]->GetMaximum();
  if(max<d0_[kWmunu]->GetMaximum())max=d0_[kWmunu]->GetMaximum();
  if(max<d0_[kZmumu]->GetMaximum())max=d0_[kZmumu]->GetMaximum();
  d0_[kSignal       ]->SetMaximum( 1.7* max );
  d0_[kSignal       ]->Draw();
  d0_[kQCD    ]->Draw("same");
  d0_[kWmunu]->Draw("same");
  d0_[kZmumu]->Draw("same");
  leg0->Draw("same");
  drawcutline(0.2, max);

  // ---
  //    do the printing for ecalEn_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(canv3);

  // draw canvas
  canv3->cd(0);
  canv3->SetLogy(1);
  axesStyle(ecalEn_[kSignal], "ECal Endergy Deposit( #mu ) [GeV]", "events");
  max=ecalEn_[kSignal]->GetMaximum();
  if(max<ecalEn_[kQCD]->GetMaximum())max=ecalEn_[kQCD]->GetMaximum();
  if(max<ecalEn_[kWmunu]->GetMaximum())max=ecalEn_[kWmunu]->GetMaximum();
  if(max<ecalEn_[kZmumu]->GetMaximum())max=ecalEn_[kZmumu]->GetMaximum();
  ecalEn_[kSignal       ]->SetMaximum( 2.0* max );
  ecalEn_[kSignal       ]->Draw();
  ecalEn_[kQCD    ]->Draw("same");
  ecalEn_[kWmunu]->Draw("same");
  ecalEn_[kZmumu]->Draw("same");
  leg0->Draw("same");
  drawcutline(4., max);

  // ---
  //    do the printing for hcalEn_
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(canv4);

  // draw canvas
  canv4->cd(0);
  canv4->SetLogy(1);
  axesStyle(hcalEn_[kSignal], "HCal Endergy Deposit( #mu ) [GeV]", "events");
  //hcalEn_[kSignal       ]->SetMinimum( 0 );
  max=hcalEn_[kSignal]->GetMaximum();
  if(max<hcalEn_[kQCD]->GetMaximum())max=hcalEn_[kQCD]->GetMaximum();
  if(max<hcalEn_[kWmunu]->GetMaximum())max=hcalEn_[kWmunu]->GetMaximum();
  if(max<hcalEn_[kZmumu]->GetMaximum())max=hcalEn_[kZmumu]->GetMaximum();
  hcalEn_[kSignal       ]->SetMaximum( 2.0* max );
  hcalEn_[kSignal       ]->Draw();
  hcalEn_[kQCD    ]->Draw("same");
  hcalEn_[kWmunu]->Draw("same");
  hcalEn_[kZmumu]->Draw("same");
  leg0->Draw("same");
  drawcutline(6., max);

  // ---
  //    do the printing for relIso_
  // ---
  TCanvas* canv5 = new TCanvas("canv5", "canv5", 600, 600); canvasStyle(canv5);

  // draw canvas
  canv5->cd(0);
  canv5->SetLogy(1);
  axesStyle(relIso_[kSignal], "relIso( #mu )", "events");
  //relIso_[kSignal       ]->SetMinimum( 0 );
  max=relIso_[kSignal]->GetMaximum();
  if(max<relIso_[kQCD]->GetMaximum())max=relIso_[kQCD]->GetMaximum();
  if(max<relIso_[kWmunu]->GetMaximum())max=relIso_[kWmunu]->GetMaximum();
  if(max<relIso_[kZmumu]->GetMaximum())max=relIso_[kZmumu]->GetMaximum();
  relIso_[kSignal       ]->SetMaximum( 2.0* max );
  relIso_[kSignal       ]->Draw();
  relIso_[kQCD    ]->Draw("same");
  relIso_[kWmunu]->Draw("same");
  relIso_[kZmumu]->Draw("same");
  leg0->Draw("same");
  drawcutline(0.05, max);
}

void drawcutline(double cutval, double maximum)
{
  TLine *cut = new TLine();
  cut->SetLineWidth(3);
  cut->SetLineStyle(2);
  cut->SetLineColor(2);
  cut->DrawLine(cutval,0.,cutval,maximum);
}

void canvasStyle(TCanvas* canv) 
{
  canv->SetFillStyle   ( 4000);
  canv->SetLeftMargin  ( 0.20);
  canv->SetRightMargin ( 0.05);
  canv->SetBottomMargin( 0.15);
  canv->SetTopMargin   ( 0.05);
}

void histogramStyle(TH1* hist, unsigned int style) 
{
  // pre-defined line style
  std::vector<int> color;
  color.push_back( kBlack); 
  color.push_back( kRed  ); 
  color.push_back( kBlue );
  color.push_back( kGreen );

  // pre-defined fill style
  std::vector<int> fill;
  fill.push_back(   1); 
  fill.push_back(3004); 
  fill.push_back(3005);
  fill.push_back(3006);

  // pre-defined marker style
  std::vector<int> marker;
  marker.push_back( 20);

  // set line width
  style==kSignal ? hist->SetLineWidth(6) : hist->SetLineWidth(3);
  
  hist->SetStats(kFALSE);
  hist->SetLineColor  (color[style]);
  hist->SetFillColor  (color[style]);
  hist->SetMarkerColor(color[style]);
  hist->SetFillStyle  (fill [style]);

  if(style==kSignal){
    hist->SetMarkerStyle(marker[style]);
    hist->SetMarkerSize(1.4);
  }
}

void axesStyle(TH1* hist, const char* titleX, const char* titleY) 
{
  hist->SetTitle("");

  hist->GetXaxis()->SetTitle(titleX);
  hist->GetXaxis()->CenterTitle();
  hist->GetXaxis()->SetTitleSize  ( 0.06);
  hist->GetXaxis()->SetTitleColor (    1);
  hist->GetXaxis()->SetTitleOffset(  0.8);
  hist->GetXaxis()->SetTitleFont  (   62);
  hist->GetXaxis()->SetLabelSize  ( 0.05);
  hist->GetXaxis()->SetLabelFont  (   62);
  hist->GetXaxis()->SetNdivisions (  505);
  
  hist->GetYaxis()->SetTitle(titleY);
  hist->GetYaxis()->SetTitleSize  ( 0.07);
  hist->GetYaxis()->SetTitleColor (    1);
  hist->GetYaxis()->SetTitleOffset(  1.2);
  hist->GetYaxis()->SetTitleFont  (   62);
  hist->GetYaxis()->SetLabelSize  ( 0.04);
  hist->GetYaxis()->SetLabelFont  (   62);
}
