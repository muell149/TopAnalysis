
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
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void histStyle2D(TH2& hist, const char* titleHisto="", const char* titleX="", const char* titleY="");

void analyzeMuonDiffXMigration()
{
  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);

  // choose jet multiplicity you want to see: "Njets1" / "Njets2" / "Njets3" / "Njets4" / "Njets3Btag" / "Njets4Btag" 
  TString jetMultiplicity ="Njets4";
  // choose luminosity for scaling of event numbers and for legend as entry
  int luminosity = 50;
  TString lum = "50";
  // choose whether you want to save every plot as png and all within one ps file
  bool save = false;
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/migration/";

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  //  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecSigMcAtNlo7TeV.root") );
  files_.push_back(new TFile("./analyzeDiffXSec_testSig.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> pt_;
  std::vector<TH2F*> corrPt_, corrPhi_, corrEta_;

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    pt_       .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/pt"   ) );
    corrEta_  .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/eta_" ) );
    corrPt_   .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/pt_"  ) );
    corrPhi_  .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/phi_" ) );
  }

  // ---
  //    define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;

  // for current ttbar 7TeV Mc@Nlo sample 
  lumiweight.push_back(0.0083/50.0*(double)luminosity);

  // ---
  //    do lumiweighting
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    pt_ [idx]->Scale(lumiweight[idx]);
  }
  
  std::cout << "-------------------" << std::endl; 
  std::cout << " chosen binning is:" << std::endl;
  std::cout << "-------------------" << std::endl; 

  // get total number of FILLED bins above cut value of 20 GeV from pt histo
  int totalBinNumber = (pt_[kSig]->GetNbinsX());
  std::cout << "total bin number:" << totalBinNumber << std::endl;

  // get binning values from pt histo
  std::vector<int> binValue_;
  for(int i=1; i<= totalBinNumber+1; i++){
    // +1 because of overflow bin
    binValue_.push_back(pt_[kSig]->GetBinLowEdge(i));
    std::cout << "lower edge bin " << i << " :" << binValue_[i-1] << std::endl;
  }

  // add upper edge of overflow bin
  binValue_.push_back(401);

  // ---
  //    a) calculate number of entries in each (gen,reco)-bin from correlation plot
  // ---

  // set up mechanism to store event content in gen-reco correlation fields
  std::vector< std::vector<int> > genRecoBins_;
  std::vector<int> genRecoBins_helper_;  
  for(unsigned int i=0; i<binValue_.size(); i++){
    genRecoBins_helper_.push_back(0);
  }  
  for(unsigned int i=0; i<binValue_.size(); i++){
    genRecoBins_.push_back(genRecoBins_helper_);
  }

  std::cout << "------------------------------------"  << std::endl; 
  std::cout << " content in for each (gen,reco)-bin:"  << std::endl;
  std::cout << "------------------------------------"  << std::endl;

  // -------- calculation ----------
  // -------------------------------
  // k: adress gen-  pt bin (overflow bin included, no underflowbin because of cut)
  // l: adress reco- pt bin (overflow bin included, no underflowbin because of cut)
    // -1 because in binValue_ there are two entries for the overflow bin (lower and upper bin edge)
  // i,j: loop over k-genBin * l-recoBin- field 
    // +1 because bin counting starts with 1, and vector binValue_ with 0
  for(unsigned int k=0; k<(binValue_.size()-1); k++){
    for(unsigned int l=0; l<(binValue_.size()-1); l++){
      int eventsInGenRecoBin=0;
      for(int i=binValue_[k]+1; i<=binValue_[k+1]; i++){
	for(int j=binValue_[l]+1; j<=binValue_[l+1]; j++){
	  eventsInGenRecoBin += corrPt_[kSig]->GetBinContent(i,j);
	}
      }
      (genRecoBins_[k])[l]=eventsInGenRecoBin;
      std::cout << "("<< k << "," << l << ") pt-Bin is " << eventsInGenRecoBin << std::endl;
    }
  }
  std::cout << "------------------------------------"  << std::endl; 
  std::cout << "purity / stability (chosen binning):"  << std::endl;
  std::cout << "------------------------------------"  << std::endl; 

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
    std::cout << "for " << i << ". bin : " << purity_[i-1] << " / " << stability_[i-1]  << std::endl; ;
  }

  // ---
  //    c) calculate acceptance = purity / stability
  // ---
  std::vector<double> acceptance_;

  for(unsigned int i=0; i<purity_.size(); i++){
    acceptance_.push_back(purity_[i] / stability_[i]);
    std::cout << "acceptance for "<< i+1 << ". bin is " << acceptance_[i] << std::endl; 
  }

  // ---
  //    d) create histograms with stability, purity 
  //       and aceptance for pt
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
  //    create legend
  // ---

  TLegend *leg0 = new TLegend(0.38, 0.50, 0.98, 0.76);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("migration effects "+jetMultiplicity+"+ , "+lum+" pb^{-1}");
  leg0->AddEntry(  ptPurity    , "purity"     , "PL");
  leg0->AddEntry(  ptStability , "stability"  , "PL");
  leg0->AddEntry(  ptAcceptance, "correction" , "PL");

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<=3; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ---
  //    do the printing for ptPurity, ptStability and ptAcceptance
  // ---
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetTitle("migrationPtMu");
  MyCanvas[0]->SetGrid(1,1);
  axesStyle(*ptPurity, "p_{t} ( #mu ) [GeV]", "", 0, 1.2, 0.05, 2.0);
  histogramStyle(*ptPurity    , kRed ,  1, 20, 1.5);
  histogramStyle(*ptStability , kBlue,  1, 21, 1.5);
  histogramStyle(*ptAcceptance, kBlack, 1, 22, 1.5);
  ptPurity    ->Draw("");
  ptPurity    ->Draw("Psame");
  ptStability ->Draw("same" );
  ptStability ->Draw("Psame");
  ptAcceptance->Draw("same" );
  ptAcceptance->Draw("Psame");
  leg0        ->Draw("same" );

  // ---
  //    do the printing for corrPt_
  // ---
  MyCanvas[1]->cd(0);
  MyCanvas[1]->SetTitle("genRecoCorrelationPtMu");
  histStyle2D(*corrPt_[kSig], "gen-reco correlation of p_{t} ( muon )", "p_{t} ( gen #mu ) [GeV]", "p_{t} ( reco #mu ) [GeV]");
  corrPt_[kSig]->Draw("colz");

  // ---
  //    do the printing for corrEta_
  // ---
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetTitle("genRecoCorrelationEtaMu");
  histStyle2D(*corrEta_[kSig], "correlation of #eta ( muon )", "#eta ( gen #mu )", "#eta ( reco #mu )");
  corrEta_[kSig]->Draw("colz");

  // ---
  //    do the printing for corrPhi_
  // ---
  MyCanvas[3]->cd(0);
  MyCanvas[3]->SetTitle("genRecoCorrelationEtaMu");
  histStyle2D(*corrPhi_[kSig], "correlation of #phi ( muon )", "#phi ( gen #mu )", "#phi ( reco #mu )");
  corrPhi_[kSig]->Draw("colz");

  // ---
  // saving
  // ---
  if(save){   
    // ps
    MyCanvas[0]->Print(saveTo+"migration"+lum+"pb"+jetMultiplicity+".ps(");
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+"migration"+lum+"pb"+jetMultiplicity+".ps");   
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+"migration"+lum+"pb"+jetMultiplicity+".ps)");
  
    // png
    for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
      MyCanvas[idx]->Print(saveTo+(TString)(MyCanvas[idx]->GetTitle())+".png");      
    }
  }
}

void canvasStyle(TCanvas& canv) 
{
  canv.SetFillStyle   ( 4000 );
  canv.SetLeftMargin  ( 0.20 );
  canv.SetRightMargin ( 0.05 );
  canv.SetBottomMargin( 0.15 );
  canv.SetTopMargin   ( 0.05 );
}

void histogramStyle(TH1& hist, int color, int lineStyle, int markerStyle, float markersize, int filled) 
{
  hist.SetLineWidth(3);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color);
  hist.SetMarkerColor(color);  
  hist.SetMarkerStyle(markerStyle);
  hist.SetMarkerSize(markersize);
  hist.SetLineStyle(lineStyle);
  if(filled==1){
  hist.SetFillStyle(1001);
  hist.SetFillColor(color);
  }
  else{
    hist.SetFillStyle(0);
  }
}

void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin, float yMax, float yTitleSize, float yTitleOffset) 
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
  hist.GetYaxis()->SetTitleSize  ( yTitleSize );
  hist.GetYaxis()->SetTitleColor (    1);
  hist.GetYaxis()->SetTitleOffset(yTitleOffset);
  hist.GetYaxis()->SetTitleFont  (   62);
  hist.GetYaxis()->SetLabelSize  ( 0.04);
  hist.GetYaxis()->SetLabelFont  (   62);
  hist.GetYaxis()->CenterTitle   ( true);
  if(yMin!=-123) hist.SetMinimum(yMin);
  if(yMax!=-123) hist.SetMaximum(yMax);
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
