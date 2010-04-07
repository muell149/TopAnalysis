
// ---------description---------------------------------
// -----------------------------------------------------
// this Makro calculates Purity, Stability and corresponding
// correction factors for MIGRATION effects within the 
// signal sample and plots gen-reco correlation for pt, 
// eta and phi
// -----------------------------------------------------

#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>

enum styles {kSig};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);
void histStyle2D(TH2& hist, const char* titleHisto="", const char* titleX="", const char* titleY="");

void analyzeMuonDiffXMigration()
{
  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);


  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecSigMcAtNlo7TeV.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> pt_;
  std::vector<TH2F*> corrPt_, corrPhi_, corrEta_;

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    pt_       .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/pt"       ) );
    corrEta_  .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonEta_" ) );
    corrPt_   .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonPt_"  ) );
    corrPhi_  .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonPhi_" ) );
  }

  // ---
  //    create Vector to store output statements
  // ---
  std::vector<TString> output_;
  TString textHelper = "";
  output_.push_back("MC@NLO 7 TeV");

  // ---
  //    define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;

  // for current ttbar 7TeV Mc@Nlo sample 
  lumiweight.push_back(0.0083);

  // ---
  //    do lumiweighting
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    pt_ [idx]->Scale(lumiweight[idx]);
  }
  
  // ---  
  //    print out weighted event numbers for all files
  // ---

  std::vector<double> eventNumbersPt_, eventNumbersEta_, eventNumbersPhi_;

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    eventNumbersPt_.push_back ( lumiweight[idx]*(corrPt_ [idx]->GetEntries()) );
    eventNumbersEta_.push_back( lumiweight[idx]*(corrEta_[idx]->GetEntries()) );
    eventNumbersPhi_.push_back( lumiweight[idx]*(corrPhi_[idx]->GetEntries()) );

    std::cout << "total weighted # of sig events in pt (file " << idx << "): " << eventNumbersPt_[idx] << std::endl;
    textHelper = "total weighted # of sig events in pt (file ";
    textHelper += idx;
    textHelper += "): ";
    textHelper += eventNumbersPt_[idx] ;
    output_ .push_back(textHelper);
  }

  // ---
  //    do scaling with respect to inclusive cross section (taken from same histogram)
  // ---
  
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    pt_ [idx]->Scale(1/eventNumbersPt_[idx]);
  }

  // ---
  //    division by binwidth
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {

    for(int i=1; i<= pt_[idx]->GetNbinsX(); i++){
      pt_[idx]->SetBinContent(i,((double)(pt_[idx]->GetBinContent(i))/(double)(pt_[idx]->GetBinWidth(i)))  );
    }
  }
  
  // ---
  //    configure histograms
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    histogramStyle(*pt_  [idx], idx);
  }

  // ---
  //    calculate stability and purity for pt(Signal) only
  // ---

  // get total number of FILLED bins above cut value of 20 GeV from pt histo
  int totalBinNumber = (pt_[kSig]->GetNbinsX())-1;
  std::cout << "total bin number between 20 and 200 GeV: " << totalBinNumber << std::endl;

  // get binning values from pt histo
  std::vector<int> binValue_;
  for(int i=1; i<= totalBinNumber+2; i++){
    // +2 for underflow bin and upper Edge of last bin
    binValue_.push_back(pt_[kSig]->GetBinLowEdge(i));
    std::cout << "lower edge bin " << i << " :" << binValue_[i-1] << std::endl;
  }

  // add overflow bin
  binValue_.push_back(401);

  // ---
  //    a) calculate number of entries in each (gen,reco)-bin from correlation plot
  // ---

  // store event content in gen-reco correlation fields
  std::vector< std::vector<int> > genRecoBins_;
  std::vector<int> genRecoBins_helper_;
  
  for(unsigned int i=0; i<binValue_.size(); i++){
    genRecoBins_helper_.push_back(0);
  }
  
  for(unsigned int i=0; i<binValue_.size(); i++){
    genRecoBins_.push_back(genRecoBins_helper_);
  }

  // k: adress gen-  pt bin (overflow bin included, no underflowbin because of cut)
  // l: adress reco- pt bin (overflow bin included, no underflowbin because of cut)
  // i,j: loop over k-genBin * l-recoBin- field 

  for(unsigned int k=0; k<(binValue_.size()-1); k++){
    for(unsigned int l=0; l<(binValue_.size()-1); l++){
      int eventsInGenRecoBin=0;
      for(int i=binValue_[k]+1; i<=binValue_[k+1]; i++){
	for(int j=binValue_[l]+1; j<=binValue_[l+1]; j++){
	  eventsInGenRecoBin += corrPt_[kSig]->GetBinContent(i,j);
	}
      }
      (genRecoBins_[k])[l]=eventsInGenRecoBin;
      std::cout << "content (gen,reco) = (" << k << "," << l << ") pt-Bin is " << eventsInGenRecoBin << std::endl;
    }
  }
  
  output_ .push_back("purity / stability (chosen binning, unshifted):");

  // ---
  //    b) calculate stability and purity for pt
  // ---

  std::vector<double> purity_, stability_;
  // i: calculation for each bin i
  for(int i=1; i<=totalBinNumber; i++){
    double genTotalBinI = 0;
    double recoTotalBinI = 0; 
    // j: loop over row/column for whole gen/reco-bin
    for(unsigned int j=0; j<genRecoBins_.size(); j++){
      genTotalBinI  += (genRecoBins_[i])[j];
      recoTotalBinI += (genRecoBins_[j])[i];      
    }
    purity_    .push_back( (double)((genRecoBins_[i])[i]) /  recoTotalBinI );
    stability_ .push_back( (double)((genRecoBins_[i])[i]) /  genTotalBinI  );
    textHelper =  "purity/stability for ";
    textHelper += i;
    textHelper += ". bin : ";
    textHelper += purity_[i-1];
    textHelper += "/";
    textHelper += stability_[i-1];
    output_ .push_back(textHelper);   
  }

  // ---
  //    c) calculate acceptance = purity / stability
  // ---
  std::vector<double> acceptance_;

    output_ .push_back("acceptance for chosen binning:");   

  for(unsigned int i=0; i<purity_.size(); i++){
    acceptance_.push_back(purity_[i] / stability_[i]);
    std::cout << "acceptance for "<< i+1 << ". bin is " << acceptance_[i] << std::endl; 
    textHelper = "acceptance for ";
    textHelper += i+1;
    textHelper += ". bin is ";
    textHelper += acceptance_[i];
    output_ .push_back(textHelper); 
  }

  // ---
  //    d) create histograms with stability, purity 
  //       and aceptance for pt in same binning as pt
  // ---

  // create array with binning values for histograms
  Float_t BinningValuesPt[binValue_.size()];
  for(unsigned int i=0; i<binValue_.size(); i++){
    BinningValuesPt[i]= binValue_[i];
    if(i==1){
      BinningValuesPt[i]= binValue_[i]+1;   
    }
    if(i==binValue_.size()-1){
      BinningValuesPt[i]= binValue_[i]-1;   
    }
  }

  // purity
  TH1F* ptPurity = new TH1F("ptPurity","ptPurity",binValue_.size()-2, BinningValuesPt);
  ptPurity->SetBinContent( 1,0 );
  for(unsigned int i=1; i<binValue_.size()-1; i++){
    ptPurity->SetBinContent( i+1 ,purity_[i-1] );
  }
  
  // stability
  TH1F* ptStability = new TH1F("ptStability","ptStability",binValue_.size()-2, BinningValuesPt);
  ptStability->SetBinContent( 1,0 );
  for(unsigned int i=1; i<binValue_.size()-1; i++){
    ptStability->SetBinContent( i+1 ,stability_[i-1] );
  }

  // acceptance
  TH1F* ptAcceptance = new TH1F("ptAcceptance","ptAcceptance",binValue_.size()-2, BinningValuesPt);
  ptAcceptance->SetBinContent( 1,0 );
  for(unsigned int i=1; i<binValue_.size()-1; i++){
    ptAcceptance->SetBinContent( i+1 ,acceptance_[i-1] );
  }

  // ---
  //    create legends 
  // ---

  // create output slide as two legends, each on one half of side
  TLegend *leg1 = new TLegend(0.35, 0.0, 1.0, 1.0);
  leg1->SetFillStyle(3001);
  leg1->SetBorderSize(0);
  for(unsigned int i= ((unsigned int)(((double)(output_.size()))/2.0)); i< output_.size(); i++){
    leg1->AddEntry( pt_[kSig], output_[i]  , "" );;
  }

  TLegend *leg2 = new TLegend(-0.1, 0.0, 0.5, 1.0);
  leg2->SetFillStyle(3001);
  leg2->SetBorderSize(0);
  for(unsigned int i=0; i< (unsigned int)(((double)(output_.size()))/2.0); i++){
    leg2->AddEntry( pt_[kSig], output_[i]  , "" );;
  }

  // create a legend (migration effects)
  TLegend *leg3 = new TLegend(0.38, 0.50, 0.98, 0.76);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  leg3->SetHeader("migration effects");
  leg3->AddEntry(  ptPurity    , "purity"     , "PL");
  leg3->AddEntry(  ptStability , "stability"  , "PL");
  leg3->AddEntry(  ptAcceptance, "correction" , "PL");

  // ---
  //    do the printing for ptPurity, ptStability and ptAcceptance
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // draw canvas
  canv0->SetTitle("migration for pt ( #mu )");
  canv0->SetGrid(1,1);
  ptPurity->SetTitle("");
  ptPurity->GetXaxis()->SetTitle("p_{t} ( #mu ) [GeV]");
  ptPurity->GetXaxis()->CenterTitle   ( true );
  ptPurity->GetYaxis()->CenterTitle   ( true );
  ptPurity->GetYaxis()->SetTitleOffset(  2.0 );
  ptPurity->GetXaxis()->SetTitleSize  ( 0.05 );
  ptPurity->GetYaxis()->SetTitleSize  ( 0.05 );
  ptPurity->SetStats(kFALSE);
  ptPurity->SetLineColor(kRed);
  ptPurity->SetLineWidth(3);
  ptPurity->SetMarkerStyle(20);
  ptPurity->SetMarkerSize(1.5);
  ptPurity->SetMarkerColor(kRed);
  ptPurity->Draw("");
  ptPurity->Draw("Psame");
  ptStability->SetLineColor(kBlue);
  ptStability->SetLineWidth(3);
  ptStability->SetMarkerStyle(21);
  ptStability->SetMarkerSize(1.5);
  ptStability->SetMarkerColor(kBlue);
  ptStability->Draw("same");
  ptStability->Draw("Psame");
  ptAcceptance->SetLineWidth(3);
  ptAcceptance->SetMarkerStyle(22);
  ptAcceptance->SetMarkerSize(1.5);
  ptAcceptance->Draw("same");
  ptAcceptance->Draw("Psame");
  leg3->Draw("same");

  // ---
  //    do the printing for corrPt_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);
  // draw canvas
  canv1->cd(0);
  canv1->SetTitle("gen-reco correlation of p_{t} ( muon )");
  histStyle2D(*corrPt_[kSig], "gen-reco correlation of p_{t} ( muon )", "p_{t} ( gen #mu ) [GeV]", "p_{t} ( reco #mu ) [GeV]");
  corrPt_[kSig]->Draw("colz");

  // ---
  //    do the printing for corrEta_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);
  // draw canvas
  canv2->cd(0);
  canv2->SetTitle("gen-reco correlation of #eta ( muon )");
  histStyle2D(*corrEta_[kSig], "correlation of #eta ( muon )", "#eta ( gen #mu )", "#eta ( reco #mu )");
  corrEta_[kSig]->Draw("colz");

  // ---
  //    do the printing for corrPhi_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);
  // draw canvas
  canv3->cd(0);
  canv3->SetTitle("gen-reco correlation of #phi ( muon )");
  histStyle2D(*corrPhi_[kSig], "correlation of #phi ( muon )", "#phi ( gen #mu )", "#phi ( reco #mu )");
  corrPhi_[kSig]->Draw("colz");

  // ---
  //    do the printing for the output text
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(*canv4);
  // draw canvas
  canv4->cd(0);
  canv4->SetTitle("detail numbers");
  leg1->Draw("");
  leg2->Draw("same");

}

void canvasStyle(TCanvas& canv) 
{
  canv.SetFillStyle   ( 4000 );
  canv.SetLeftMargin  ( 0.20 );
  canv.SetRightMargin ( 0.05 );
  canv.SetBottomMargin( 0.15 );
  canv.SetTopMargin   ( 0.05 );
}

void histogramStyle(TH1& hist, unsigned int style) 
{
  // pre-defined line style
  std::vector<int> color;
  color.push_back( kBlack ); 
  color.push_back( kRed   ); 
  color.push_back( kBlue  );
  color.push_back( 14     );
  color.push_back( 46     );
  color.push_back( kRed   );
  color.push_back( kBlue  );

 // pre-defined fill style
  std::vector<int> fill;
  fill.push_back( 1   ); 
  fill.push_back( 1   ); 
  fill.push_back( 1   );
  fill.push_back( 2   );
  fill.push_back( 2   );
  fill.push_back( 2   );
  fill.push_back( 2   );

  // pre-defined marker style
  std::vector<int> marker;
  marker.push_back( 20);

  // set line width  
  hist.SetLineWidth(3);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color[style]);
  hist.SetMarkerColor(color[style]);

}

void axesStyle(TH1& hist, const char* titleX, const char* titleY) 
{
  hist.SetTitle("");

  hist.GetXaxis()->SetTitle(titleX);
  hist.GetXaxis()->CenterTitle();
  hist.GetXaxis()->SetTitleSize  ( 0.06);
  hist.GetXaxis()->SetTitleColor (    1);
  hist.GetXaxis()->SetTitleOffset(  1.0);
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
  hist.GetYaxis()->CenterTitle   ( true);
}

void histStyle2D(TH2& hist, const char* titleHisto, const char* titleX, const char* titleY) 
{
  hist.SetTitle(titleHisto);
  hist.GetXaxis()->SetTitle(titleX);
  hist.GetXaxis()->SetTitleSize ( 0.05 );
  hist.GetXaxis()->SetLabelColor(  1   );
  hist.GetXaxis()->SetLabelFont ( 62   );
  hist.GetXaxis()->SetLabelSize ( 0.04 );
  hist.GetXaxis()->SetNdivisions(  505 );
  hist.GetXaxis()->CenterTitle  ( true );
  hist.GetYaxis()->SetTitle(titleY);
  hist.GetYaxis()->SetTitleSize  ( 0.05 );
  hist.GetYaxis()->SetTitleColor (    1 );
  hist.GetYaxis()->SetTitleOffset(  1.1 );
  hist.GetYaxis()->SetTitleFont  (   62 );
  hist.GetYaxis()->SetLabelSize  ( 0.04 );
  hist.GetYaxis()->SetLabelFont  (   62 );
  hist.GetYaxis()->SetNdivisions (  505 );
  hist.GetYaxis()->CenterTitle   ( true );
  hist.SetStats(kFALSE);
}
