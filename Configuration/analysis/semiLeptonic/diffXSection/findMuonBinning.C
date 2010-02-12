
// ---------description------
// --------------------------
// this Makro calculates a binning for ptmu 
// with respect to a equal number of events
// in each bin and calculates then purity,
// stability and acceptance for this binning 
// --------------------------
// --------------------------

#include <vector>
#include <iostream>

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>

enum styles {kSig};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);
void drawBinningValue(double binval, double maximum);
void drawFixBinningValue(double binval, double maximum);
void drawYBinningValue(double binval, double maximum);
void drawYFixBinningValue(double binval, double maximum);

void findMuonBinning()
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
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecSigMadgraph7TeV.root"  ) );
  //  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecSigPythia10TeV.root"  ) );

  // ---
  //    get histograms
  // ---
  std::vector<TH2F*> corrPt_, corrPhi_, corrEta_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    corrEta_   .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonEta_"   ) );
    corrPt_    .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonPt_"    ) );
    corrPhi_   .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonPhi_"   ) );
  }
  
  // optional choices: number of toal bins
  int totalBinNumber = 4;
    
  // create 1D pt histo for reco Muons as projection of correlation plot

  std::vector<TH1F*> ptMuReco_;  
  for(unsigned int idx=0; idx<files_.size(); ++idx){
    ptMuReco_   .push_back  ((TH1F*)corrPt_[idx]->ProjectionY());
  }


   // 1st step: calculate total number of events

  int totalEventNumber = 0;
  for(int i=0; i<=401; i++){
      totalEventNumber+= ptMuReco_[kSig]->GetBinContent(i);

  }
  std::cout << "" << std::endl;
  std::cout << "statistics of sample:" << std::endl;
  std::cout << "unweighted total number of events: " << totalEventNumber << std::endl;

  // 2nd step: calculate events per bin

  double eventsPerBin = (double)totalEventNumber/(double)totalBinNumber; 


  // 3rd step calculate bin values and entries for each bin

  std::vector<int> binContent_, binValue_;
  // starting point for underflow bin
  binValue_ .push_back(0);
  // start at 19 GeV with counting
  binValue_ .push_back(19);

  std::cout << "aspired (unweighted) events per bin: " << eventsPerBin << std::endl;
  std::cout << "" << std::endl;
  std::cout << "best binning:" << std::endl;
  std::cout << "1st bin starts at " << binValue_[1]+1 << " (chosen by hand)" << std::endl;

  // j: calculate upper limit value for each bin
  for(int j=0; j<(totalBinNumber-1); j++){

    int binValue   = 0;
    int binContent = 0;
 
    // i: sum bin contents until events/ bin reached
    for(int i=binValue_[j+1]+1; binContent < eventsPerBin; i++){
      binContent += ptMuReco_[kSig]->GetBinContent(i);
      binValue = i+1;
    }
    
    // store number of events in the bin
    binContent_ .push_back(binContent);
    // store upper limit value for the bin
    binValue_   .push_back(binValue);
    
    
    std::cout << "bin content of " << j+1 << ". bin: " << binContent_[j] << std::endl;
    std::cout << "upper limit for " << j+1 << ". bin is " << binValue_[j+2] << " GeV" << std::endl;
  }

  // set end of last bin per hand due to keep it at handy size
  binValue_.push_back(200);  
  std::cout << "upper limit for " << binValue_.size()-2 << ". bin is " << binValue_[(binValue_.size()-1)] << " GeV (chosen by hand) " << std::endl;
  int lastBinContent =0;
  for(int i= binValue_[(binValue_.size()-2)]+1; i<=binValue_[(binValue_.size()-1)]; i++){
    lastBinContent+=ptMuReco_[kSig]->GetBinContent(i);
  }
  std::cout << "bin content within last bin is " << lastBinContent << std::endl;
  std::cout << "task was: find " << totalBinNumber << " bins within " << binValue_[1]+1 << " and " << binValue_[binValue_.size()-1] << " GeV with equal event numbers per bin" << std::endl;

  // ---
  // 4th step: calculate number of entries in each (gen,reco)-bin from correlation plot
  // ---

  // add last bin for Overflow
  binValue_   .push_back(401);

  // store event content in gen-reco correlation fields
  std::vector< std::vector<int> > genRecoBins_;
  std::vector<int> genRecoBins_helper_;
  
  for(unsigned int i=0; i<binValue_.size(); i++){
    genRecoBins_helper_.push_back(0);
  }
  
  for(unsigned int i=0; i<binValue_.size(); i++){
    genRecoBins_.push_back(genRecoBins_helper_);
  }

  std::cout << "" << std::endl;
  std::cout << "# events in (gen,reco) bins:" << std::endl;
 
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
      
      std::cout << "content (gen,reco) = (" << k << "," << l  << ") pt-Bin is " << eventsInGenRecoBin << std::endl;
    }
  }
  
  std::cout << "" << std::endl;
  std::cout << "purity and stability for optimal binning:" << std::endl;

  // ---
  // 5th step: calculate stability and purity for pt
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
    std::cout << "purity and stability for "<< i << ". bin are " << purity_[i-1] << " and " << stability_[i-1] << std::endl;
  }

  // ---
  // 6th step: calculate acceptance = purity / stability
  // ---
  std::vector<double> acceptance_;

  std::cout << "" << std::endl;
  std::cout << "acceptance for optimal binning:" << std::endl;

  for(unsigned int i=0; i<purity_.size(); i++){
    acceptance_.push_back(purity_[i] / stability_[i]);
    std::cout << "acceptance for "<< i+1 << ". bin is " << acceptance_[i] << std::endl; 
  }

  // ---
  // 7th step: create histograms with stability,
  // purity and aceptance for pt in variable binning
  // ---

  // create binning values for histograms
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
  //    do the printing for ptMuReco_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // draw canvas
  canv0->cd(0);
  canv0->SetTitle("binning of p_{t} ( muon )");
  ptMuReco_[kSig]->Draw("");
  for(unsigned int j=0; j<(binValue_.size()-3); j++){
    drawBinningValue(binValue_[j+2], ptMuReco_[kSig]->GetMaximum()); 
    }
  drawFixBinningValue(binValue_[1], ptMuReco_[kSig]->GetMaximum()); 
  drawFixBinningValue(binValue_[binValue_.size()-2], ptMuReco_[kSig]->GetMaximum()); 
  
  ptMuReco_[kSig]->SetTitle("binning of p_{t} ( muon )");
  ptMuReco_[kSig]->GetXaxis()->SetTitle("p_{t} ( reco #mu ) [GeV]");
  ptMuReco_[kSig]->GetXaxis()->SetTitleSize ( 0.05 );
  ptMuReco_[kSig]->GetXaxis()->SetLabelColor(  1   );
  ptMuReco_[kSig]->GetXaxis()->SetLabelFont ( 62   );
  ptMuReco_[kSig]->GetXaxis()->SetLabelSize ( 0.04 );
  ptMuReco_[kSig]->GetXaxis()->SetNdivisions(  505 );
  ptMuReco_[kSig]->GetXaxis()->CenterTitle  ( true );

  ptMuReco_[kSig]->GetYaxis()->SetTitle("events");
  ptMuReco_[kSig]->GetYaxis()->SetTitleSize  ( 0.05 );
  ptMuReco_[kSig]->GetYaxis()->SetTitleColor (    1 );
  ptMuReco_[kSig]->GetYaxis()->SetTitleOffset(  1.1 );
  ptMuReco_[kSig]->GetYaxis()->SetTitleFont  (   62 );
  ptMuReco_[kSig]->GetYaxis()->SetLabelSize  ( 0.04 );
  ptMuReco_[kSig]->GetYaxis()->SetLabelFont  (   62 );
  ptMuReco_[kSig]->GetYaxis()->SetNdivisions (  505 );
  ptMuReco_[kSig]->GetYaxis()->CenterTitle   ( true );

  ptMuReco_[kSig]->SetStats(kFALSE);


  // ---
  //    do the printing for corrPt_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetTitle("gen-reco correlation of p_{t} ( muon )");

  corrPt_[kSig]->SetTitle("correlation of p_{t} ( muon )");
  corrPt_[kSig]->GetXaxis()->SetTitle("p_{t} ( gen #mu ) [GeV]");
  corrPt_[kSig]->GetXaxis()->SetTitleSize ( 0.05 );
  corrPt_[kSig]->GetXaxis()->SetLabelColor(  1   );
  corrPt_[kSig]->GetXaxis()->SetLabelFont ( 62   );
  corrPt_[kSig]->GetXaxis()->SetLabelSize ( 0.04 );
  corrPt_[kSig]->GetXaxis()->SetNdivisions(  505 );
  corrPt_[kSig]->GetXaxis()->CenterTitle  ( true );

  corrPt_[kSig]->GetYaxis()->SetTitle("p_{t} ( reco #mu ) [GeV]");
  corrPt_[kSig]->GetYaxis()->SetTitleSize  ( 0.05 );
  corrPt_[kSig]->GetYaxis()->SetTitleColor (    1 );
  corrPt_[kSig]->GetYaxis()->SetTitleOffset(  1.1 );
  corrPt_[kSig]->GetYaxis()->SetTitleFont  (   62 );
  corrPt_[kSig]->GetYaxis()->SetLabelSize  ( 0.04 );
  corrPt_[kSig]->GetYaxis()->SetLabelFont  (   62 );
  corrPt_[kSig]->GetYaxis()->SetNdivisions (  505 );
  corrPt_[kSig]->GetYaxis()->CenterTitle   ( true );

  corrPt_[kSig]->SetStats(kFALSE);
  corrPt_[kSig]->SetFillColor( kRed );
  corrPt_[kSig]->Draw("");

  for(unsigned int j=0; j<(binValue_.size()-3); j++){
    drawBinningValue(binValue_[j+2], 400); 
    }
  drawFixBinningValue(binValue_[1], 400); 
  drawFixBinningValue(binValue_[binValue_.size()-2], 400); 
  
  for(unsigned int j=0; j<(binValue_.size()-3); j++){
    drawYBinningValue(binValue_[j+2], 400); 
    }
  drawYFixBinningValue(binValue_[1], 400); 
  drawYFixBinningValue(binValue_[binValue_.size()-2], 400); 

  // ---
  //    do the printing for ptPurity
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->SetTitle("purity for pt ( #mu )");
  ptPurity->SetTitle("purity for pt ( #mu )");
  ptPurity->GetXaxis()->SetTitle("p_{t} ( #mu ) [GeV]");
  ptPurity->GetYaxis()->SetTitle("purity");
  ptPurity->GetXaxis()->CenterTitle   ( true );
  ptPurity->GetYaxis()->CenterTitle   ( true );
  ptPurity->GetYaxis()->SetTitleOffset(  2.0 );
  ptPurity->GetXaxis()->SetTitleSize  ( 0.05 );
  ptPurity->GetYaxis()->SetTitleSize  ( 0.05 );
  ptPurity->SetStats(kFALSE);
  ptPurity->Draw("");
 
  // ---
  //    do the printing for ptStability
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->SetTitle("stability for pt ( #mu )");
  ptStability->SetTitle("stability for pt ( #mu )");
  ptStability->GetXaxis()->SetTitle("p_{t} ( #mu ) [GeV]");
  ptStability->GetYaxis()->SetTitle("stability");
  ptStability->GetXaxis()->CenterTitle   ( true );
  ptStability->GetYaxis()->CenterTitle   ( true );
  ptStability->GetYaxis()->SetTitleOffset(  2.0 );
  ptStability->GetXaxis()->SetTitleSize  ( 0.05 );
  ptStability->GetYaxis()->SetTitleSize  ( 0.05 );
  ptStability->SetStats(kFALSE);
  ptStability->Draw("");

  // ---
  //    do the printing for ptAcceptance
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(*canv4);

  // draw canvas
  canv4->SetTitle("acceptance for pt ( #mu )");
  ptAcceptance->SetTitle("acceptance for pt ( #mu )");
  ptAcceptance->GetXaxis()->SetTitle("p_{t} ( #mu ) [GeV]");
  ptAcceptance->GetYaxis()->SetTitle("acceptance");
  ptAcceptance->GetXaxis()->CenterTitle   ( true );
  ptAcceptance->GetYaxis()->CenterTitle   ( true );
  ptAcceptance->GetYaxis()->SetTitleOffset(  2.0 );
  ptAcceptance->GetXaxis()->SetTitleSize  ( 0.05 );
  ptAcceptance->GetYaxis()->SetTitleSize  ( 0.05 );
  ptAcceptance->SetStats(kFALSE);
  ptAcceptance->Draw("");

}

void drawBinningValue(double cutval, double maximum)
{
  TLine *cut = new TLine();
  cut->SetLineWidth(2);
  cut->SetLineStyle(1);
  cut->SetLineColor(4);
  cut->DrawLine(cutval,0.,cutval,maximum);
}

void drawFixBinningValue(double cutval, double maximum)
{
  TLine *cut = new TLine();
  cut->SetLineWidth(2);
  cut->SetLineStyle(1);
  cut->SetLineColor(2);
  cut->DrawLine(cutval,0.,cutval,maximum);
}

void drawYBinningValue(double cutval,  double maximum)
{
  TLine *cut = new TLine();
  cut->SetLineWidth(2);
  cut->SetLineStyle(1);
  cut->SetLineColor(4);
  cut->DrawLine(0.,cutval,maximum,cutval);
}

void drawYFixBinningValue(double cutval,  double maximum)
{
  TLine *cut = new TLine();
  cut->SetLineWidth(2);
  cut->SetLineStyle(1);
  cut->SetLineColor(2);
  cut->DrawLine(0.,cutval,maximum,cutval);
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
  color.push_back(   5    );


  // pre-defined fill style
  std::vector<int> fill;
  fill.push_back( 1   ); 
  fill.push_back( 1   ); 
  fill.push_back( 1   );
  fill.push_back( 1   );
  fill.push_back( 1   );
  fill.push_back( 1   );
  fill.push_back( 1   );

  // pre-defined marker style
  std::vector<int> marker;
  marker.push_back( 20);

  // set line width
  

  hist.SetLineWidth(3);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color[style]);
  //  hist.SetFillColor  (color[style]);
  hist.SetMarkerColor(color[style]);
  //  hist.SetFillStyle  (fill [style]);

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
