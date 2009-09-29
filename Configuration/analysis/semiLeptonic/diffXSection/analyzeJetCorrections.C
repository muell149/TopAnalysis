#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>

enum styles {kRaw, kL2, kL3, kL5, kL7};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);


void analyzeJetCorrections(bool plotEta=false)
{
  // ---
  //    set root style 
  // ---
  //gROOT->cd();
  //gROOT->SetStyle("Plain");

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  //files_.push_back(new TFile("./rootfiles/analyzeJets_all.root") );
  files_.push_back(new TFile("./rootfiles/analyzeJets_bkg_calib.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> resp_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    if( !plotEta ){
      resp_.push_back( (TH1F*)((TH2F*)files_[idx]->Get("goodJetQuality/ptL0_" ))->ProfileX() );
      resp_.push_back( (TH1F*)((TH2F*)files_[idx]->Get("goodJetQuality/ptL2_" ))->ProfileX() );
      resp_.push_back( (TH1F*)((TH2F*)files_[idx]->Get("goodJetQuality/ptL3_" ))->ProfileX() );
      resp_.push_back( (TH1F*)((TH2F*)files_[idx]->Get("goodJetQuality/ptL5_" ))->ProfileX() );
      resp_.push_back( (TH1F*)((TH2F*)files_[idx]->Get("goodJetQuality/ptL7_" ))->ProfileX() );
    }
    else{
      resp_.push_back( (TH1F*)((TH2F*)files_[idx]->Get("goodJetQuality/etaL0_"))->ProfileX() );
      resp_.push_back( (TH1F*)((TH2F*)files_[idx]->Get("goodJetQuality/etaL2_"))->ProfileX() );
      resp_.push_back( (TH1F*)((TH2F*)files_[idx]->Get("goodJetQuality/etaL3_"))->ProfileX() );
      resp_.push_back( (TH1F*)((TH2F*)files_[idx]->Get("goodJetQuality/etaL5_"))->ProfileX() );
      resp_.push_back( (TH1F*)((TH2F*)files_[idx]->Get("goodJetQuality/etaL7_"))->ProfileX() );
    }
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

  // resp_
  histogramStyle(*resp_ [kRaw], kRaw);
  histogramStyle(*resp_ [kL2 ], kL2 );
  histogramStyle(*resp_ [kL3 ], kL3 );
  histogramStyle(*resp_ [kL5 ], kL5 );
  histogramStyle(*resp_ [kL7 ], kL7 );

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Jet Energy Corrections");
  //leg0->AddEntry( resp_[kRaw] , "Raw"        , "PL" );
  leg0->AddEntry( resp_[kL2 ] , "L2Relative" , "PL" );
  leg0->AddEntry( resp_[kL3 ] , "L3Absolute" , "PL" );
  leg0->AddEntry( resp_[kL5 ] , "L5Hadron"   , "PL" );
  leg0->AddEntry( resp_[kL7 ] , "L7Parton"   , "PL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Jet Energy Corrections");
  //leg1->AddEntry( resp_[kRaw] , "Raw"        , "PL" );
  leg1->AddEntry( resp_[kL2 ] , "L2Relative" , "PL" );
  leg1->AddEntry( resp_[kL3 ] , "L3Absolute" , "PL" );
  leg1->AddEntry( resp_[kL5 ] , "L5Hadron"   , "PL" );
  leg1->AddEntry( resp_[kL7 ] , "L7Parton"   , "PL" );
  
  // prepare axes labels
  if( !plotEta ){
    axesStyle(*resp_ [kL7], "pt( Jet ) [GeV]", "events" );
  }
  else{
    axesStyle(*resp_[kL7], "#eta( Jet )", "events");
  }

  // ---
  //    do the printing for resp0_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // draw canvas
  canv0->cd(0);
  resp_[kL7]->SetMinimum(  0.);
  resp_[kL7]->SetMaximum(1.75*resp_[kL7]->GetMaximum() );
  //resp_[kRaw]->Draw();
  resp_[kL7 ]->Draw();
  resp_[kL3 ]->Draw("same");
  resp_[kL5 ]->Draw("same");
  resp_[kL2 ]->Draw("same");
  leg0->Draw("same");
}

void canvasStyle(TCanvas& canv) 
{
  canv.SetFillStyle   ( 4000);
  canv.SetLeftMargin  ( 0.20);
  canv.SetRightMargin ( 0.05);
  canv.SetBottomMargin( 0.15);
  canv.SetTopMargin   ( 0.05);
}

void histogramStyle(TH1& hist, unsigned int style) 
{
  // pre-defined line style
  std::vector<int> color;
  color.push_back( kBlack ); 
  color.push_back( kRed   ); 
  color.push_back( kBlue  );
  color.push_back( kGreen );
  color.push_back( kYellow);

  // pre-defined fill style
  std::vector<int> fill;
  fill.push_back( 1 ); 
  fill.push_back( 1 ); 
  fill.push_back( 1 ); 
  fill.push_back( 1 ); 
  fill.push_back( 1 ); 

  // pre-defined marker style
  std::vector<int> marker;
  marker.push_back( 20);
  marker.push_back( 21);
  marker.push_back( 22);
  marker.push_back( 23);
  marker.push_back( 24);

  // set line width
  hist.SetLineWidth(5);

  hist.SetStats(kFALSE);
  hist.SetLineColor  (color[style]);
  hist.SetFillColor  (color[style]);
  //hist.SetMarkerColor(color[style]);
  hist.SetFillStyle  (fill [style]);
  //hist.SetMarkerStyle(marker[style]);
  hist.SetMarkerSize (1.4);
}

void axesStyle(TH1& hist, const char* titleX, const char* titleY) 
{
  hist.SetTitle("");

  hist.GetXaxis()->SetTitle(titleX);
  hist.GetXaxis()->CenterTitle();
  hist.GetXaxis()->SetTitleSize  ( 0.06);
  hist.GetXaxis()->SetTitleColor (    1);
  hist.GetXaxis()->SetTitleOffset(  0.8);
  hist.GetXaxis()->SetTitleFont  (   62);
  hist.GetXaxis()->SetLabelSize  ( 0.05);
  hist.GetXaxis()->SetLabelFont  (   62);
  hist.GetXaxis()->SetNdivisions (  505);
  
  hist.GetYaxis()->SetTitle(titleY);
  hist.GetYaxis()->SetTitleSize  ( 0.07);
  hist.GetYaxis()->SetTitleColor (    1);
  hist.GetYaxis()->SetTitleOffset(  1.2);
  hist.GetYaxis()->SetTitleFont  (   62);
  hist.GetYaxis()->SetLabelSize  ( 0.04);
  hist.GetYaxis()->SetLabelFont  (   62);
}
