
// ---------description------
// --------------------------
// this Makro collects distrubutions for the Determination of the differntial cross section
// such as eta, phi, pt muon, Correlation gen - reco, purity and stability
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

enum styles {kSig};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);

void analyzeMuonDiffXSec(TString sample = "Madgraph 7 TeV")
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
  std::vector<TH1F*> eta_, phi_, pt_, etaGen_, phiGen_, ptGen_, etaMuPlus_, phiMuPlus_, ptMuPlus_ , etaMuMinus_, phiMuMinus_, ptMuMinus_;
  std::vector<TH2F*> corrPt_, corrPhi_, corrEta_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    eta_   .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/eta"   ) );
    pt_    .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/pt"    ) );
    phi_   .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/phi"   ) );
    etaGen_.push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/etaGen") );
    ptGen_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/ptGen" ) );
    phiGen_.push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/phiGen") );
    etaMuMinus_.push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/etaMuMinus") );
    ptMuMinus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/ptMuMinus" ) );
    phiMuMinus_.push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/phiMuMinus") );
    etaMuPlus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/etaMuPlus" ) );
    ptMuPlus_  .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/ptMuPlus"  ) );
    phiMuPlus_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSection/phiMuPlus" ) );

    corrEta_   .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonEta_"   ) );
    corrPt_    .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonPt_"    ) );
    corrPhi_   .push_back( (TH2F*)files_[idx]->Get("analyzeTightMuonCrossSection/muonPhi_"   ) );
  }


  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;

  // for current 10 TeV Pythia sample
  //    lumiweight.push_back(0.0391);

  // for current 7TeV Madgraph sample
  lumiweight.push_back(0.0088);

  // for current 7TeV Mc@Nlo sample
  lumiweight.push_back(0.0094);

  // ---
  // do lumiweighting
  // ---

  eta_[kSig]->Scale(lumiweight[kSig]);
  phi_[kSig]->Scale(lumiweight[kSig]);
  pt_ [kSig]->Scale(lumiweight[kSig]);
  etaGen_[kSig]->Scale(lumiweight[kSig]);
  phiGen_[kSig]->Scale(lumiweight[kSig]);
  ptGen_ [kSig]->Scale(lumiweight[kSig]);
  etaMuPlus_[kSig]->Scale(lumiweight[kSig]);
  phiMuPlus_[kSig]->Scale(lumiweight[kSig]);
  ptMuPlus_ [kSig]->Scale(lumiweight[kSig]);
  etaMuMinus_[kSig]->Scale(lumiweight[kSig]);
  phiMuMinus_[kSig]->Scale(lumiweight[kSig]);
  ptMuMinus_ [kSig]->Scale(lumiweight[kSig]);

  // ---
  //    configure histograms
  // ---

  histogramStyle(*eta_ [kSig], kSig);
  histogramStyle(*phi_ [kSig], kSig);
  histogramStyle(*pt_  [kSig], kSig);
  histogramStyle(*etaGen_ [kSig], kSig);
  histogramStyle(*phiGen_ [kSig], kSig);
  histogramStyle(*ptGen_  [kSig], kSig);
  histogramStyle(*etaMuPlus_ [kSig], kSig);
  histogramStyle(*phiMuPlus_ [kSig], kSig);
  histogramStyle(*ptMuPlus_  [kSig], kSig);
  histogramStyle(*etaMuMinus_ [kSig], kSig);
  histogramStyle(*phiMuMinus_ [kSig], kSig);
  histogramStyle(*ptMuMinus_  [kSig], kSig);

  // ---
  //    calculate stability and purity
  // ---

  // create Vector to store output statements
  std::vector<TString> output_;
  TString textHelper = "";

  // get total number of filled bins above cut value of 20 GeV from pt histo
  int totalBinNumber = (pt_[kSig]->GetNbinsX())-1;
  std::cout << totalBinNumber << std::endl;

  // get binning values from pt histo
  std::vector<int> binValue_;
  for(int i=1; i<= totalBinNumber+2; i++){
    // +2 for underflow bin and upper Edge of last bin
    binValue_.push_back(pt_[kSig]->GetBinLowEdge(i));
    std::cout << binValue_[i-1] << std::endl;
  }

  // add overflow bin
  binValue_.push_back(401);

  // ---
  // calculate number of entries in each (gen,reco)-bin from correlation plot
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
      
      textHelper =  "content (gen,reco) = (";
      textHelper += k;
      textHelper += ",";
      textHelper += l;
      textHelper += ") pt-Bin is ";
      textHelper += eventsInGenRecoBin;
      output_ .push_back(textHelper);
    }
  }
  
    output_ .push_back("purity and stability for optimal binning:");

  // ---
  // step: calculate stability and purity for pt
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
  // calculate acceptance = purity / stability
  // ---
  std::vector<double> acceptance_;

    output_ .push_back("acceptance for optimal binning:");   

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
  //    create legends 
  // ---

    // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop("+sample+")");
  leg0->AddEntry( pt_[kSig], "all semi-lep. ( #mu )"  , "PL");
  leg0->AddEntry( ptMuMinus_[kSig], "only  #mu^{-} "  , "PL");
  leg0->AddEntry( ptMuPlus_ [kSig], "only  #mu^{+} "  , "PL");

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

  // ---
  //    do the printing for pt_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // draw canvas
  canv0->cd(0);
  canv0->SetTitle("pt distribution tight  #mu after Selection");
  axesStyle(*pt_ [kSig], "p_{t} ( tight #mu ) [GeV]", "events");
  pt_ [kSig]->SetMinimum(0.);
  pt_ [kSig]->SetMaximum(1.8* pt_ [kSig]->GetMaximum() );
  pt_ [kSig]->Draw();
  ptMuPlus_  [kSig]->SetLineColor (kBlue);
  //  ptMuPlus_  [kSig]->SetLineStyle(2);
  ptMuPlus_  [kSig]->Draw("same");
  ptMuMinus_ [kSig]->SetLineColor (kRed);
  ptMuMinus_ [kSig]->SetLineStyle(2);
  ptMuMinus_ [kSig]->Draw("same");
  leg0                 ->Draw("same");

  // ---
  //    do the printing for eta_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetTitle("eta distribution tight  #mu after Selection");
  axesStyle(*eta_ [kSig], "#eta ( tight #mu )", "events");
  eta_ [kSig]->SetMinimum(0.);
  eta_ [kSig]->SetMaximum(1.8* eta_ [kSig]->GetMaximum() );
  eta_ [kSig]->Draw();
  etaMuPlus_  [kSig]->SetLineColor (kBlue);
  //  etaMuPlus_  [kSig]->SetLineStyle(2);
  etaMuPlus_  [kSig]->Draw("same");
  etaMuMinus_ [kSig]->SetLineColor (kRed);
  etaMuMinus_ [kSig]->SetLineStyle(2);
  etaMuMinus_ [kSig]->Draw("same");
  leg0                 ->Draw("same");

  // ---
  //    do the printing for phi_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetTitle("phi distribution tight  #mu after Selection");
  axesStyle(*phi_ [kSig], "#phi ( tight #mu )", "events");
  phi_ [kSig]->SetMinimum(0.);
  phi_ [kSig]->SetMaximum(1.8* phi_ [kSig]->GetMaximum() );
  phi_ [kSig]->Draw();
  phiMuPlus_  [kSig]->SetLineColor (kBlue);
  //  phiMuPlus_  [kSig]->SetLineStyle(2);
  phiMuPlus_  [kSig]->Draw("same");
  phiMuMinus_ [kSig]->SetLineColor (kRed);
  phiMuMinus_ [kSig]->SetLineStyle(2);
  phiMuMinus_ [kSig]->Draw("same");
  leg0                  ->Draw("same");

  // ---
  //    do the printing for corrPt_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  canv3->SetTitle("gen-reco correlation of p_{t} ( muon )");
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


  // ---
  //    do the printing for corrEta_
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(*canv4);

  // draw canvas
  canv4->cd(0);
  canv4->SetTitle("gen-reco correlation of #eta ( muon )");
  corrEta_[kSig]->SetTitle("correlation of #eta ( muon )");
  corrEta_[kSig]->GetXaxis()->SetTitle("#eta ( gen #mu )");
  corrEta_[kSig]->GetXaxis()->SetTitleSize ( 0.05 );
  corrEta_[kSig]->GetXaxis()->SetLabelColor(  1   );
  corrEta_[kSig]->GetXaxis()->SetLabelFont ( 62   );
  corrEta_[kSig]->GetXaxis()->SetLabelSize ( 0.04 );
  corrEta_[kSig]->GetXaxis()->SetNdivisions(  505 );
  corrEta_[kSig]->GetXaxis()->CenterTitle  ( true );

  corrEta_[kSig]->GetYaxis()->SetTitle("#eta ( reco #mu )");
  corrEta_[kSig]->GetYaxis()->SetTitleSize  ( 0.05 );
  corrEta_[kSig]->GetYaxis()->SetTitleColor (    1 );
  corrEta_[kSig]->GetYaxis()->SetTitleOffset(  1.1 );
  corrEta_[kSig]->GetYaxis()->SetTitleFont  (   62 );
  corrEta_[kSig]->GetYaxis()->SetLabelSize  ( 0.04 );
  corrEta_[kSig]->GetYaxis()->SetLabelFont  (   62 );
  corrEta_[kSig]->GetYaxis()->SetNdivisions (  505 );
  corrEta_[kSig]->GetYaxis()->CenterTitle   ( true );

  corrEta_[kSig]->SetStats(kFALSE);
  corrEta_[kSig]->SetFillColor( kRed );
  corrEta_[kSig]->Draw("");

  // ---
  //    do the printing for corrPhi_
  // ---
  TCanvas* canv5 = new TCanvas("canv5", "canv5", 600, 600); canvasStyle(*canv5);

  // draw canvas
  canv5->cd(0);
  canv5->SetTitle("gen-reco correlation of #phi ( muon )");
  corrPhi_[kSig]->SetTitle("correlation of #phi ( muon )");
  corrPhi_[kSig]->GetXaxis()->SetTitle("#phi ( gen #mu )");
  corrPhi_[kSig]->GetXaxis()->SetTitleSize ( 0.05 );
  corrPhi_[kSig]->GetXaxis()->SetLabelColor(  1   );
  corrPhi_[kSig]->GetXaxis()->SetLabelFont ( 62   );
  corrPhi_[kSig]->GetXaxis()->SetLabelSize ( 0.04 );
  corrPhi_[kSig]->GetXaxis()->SetNdivisions(  505 );
  corrPhi_[kSig]->GetXaxis()->CenterTitle  ( true );

  corrPhi_[kSig]->GetYaxis()->SetTitle("#phi ( reco #mu )");
  corrPhi_[kSig]->GetYaxis()->SetTitleSize  ( 0.05 );
  corrPhi_[kSig]->GetYaxis()->SetTitleColor (    1 );
  corrPhi_[kSig]->GetYaxis()->SetTitleOffset(  1.1 );
  corrPhi_[kSig]->GetYaxis()->SetTitleFont  (   62 );
  corrPhi_[kSig]->GetYaxis()->SetLabelSize  ( 0.04 );
  corrPhi_[kSig]->GetYaxis()->SetLabelFont  (   62 );
  corrPhi_[kSig]->GetYaxis()->SetNdivisions (  505 );
  corrPhi_[kSig]->GetYaxis()->CenterTitle   ( true );

  corrPhi_[kSig]->SetStats(kFALSE);
  corrPhi_[kSig]->SetFillColor( kRed );
  corrPhi_[kSig]->Draw("");


  // ---
  //    do the printing for the output text
  // ---
  TCanvas* canv6 = new TCanvas("canv6", "canv6", 600, 600); canvasStyle(*canv6);

  // draw canvas
  canv6->cd(0);
  canv6->SetTitle("detail numbers");
  leg1->Draw("");
  leg2->Draw("same");



  // ---
  // saving
  // ---
  

  // // ps
//   canv0->Print("./diffXSecFromSignal/diffXStuffMadgraph7TeV.ps(");
//   canv1->Print("./diffXSecFromSignal/diffXStuffMadgraph7TeV.ps" );
//   canv2->Print("./diffXSecFromSignal/diffXStuffMadgraph7TeV.ps" );
//   canv3->Print("./diffXSecFromSignal/diffXStuffMadgraph7TeV.ps" );
//   canv4->Print("./diffXSecFromSignal/diffXStuffMadgraph7TeV.ps" );
//   canv5->Print("./diffXSecFromSignal/diffXStuffMadgraph7TeV.ps" );
//   canv6->Print("./diffXSecFromSignal/diffXStuffMadgraph7TeV.ps" );
//   canv7->Print("./diffXSecFromSignal/diffXStuffMadgraph7TeV.ps" );
//   canv8->Print("./diffXSecFromSignal/diffXStuffMadgraph7TeV.ps)");

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
