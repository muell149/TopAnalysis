
// ---------description------
// --------------------------
// this Makro collects distrubutions for the Determination of the differntial cross section
// such as eta, phi, pt muon, Correlation gen - reco, Puirity and stability
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

enum styles {kSigPy10};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);

void analyzeMuonDiffXSec()
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
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecSigPythia10TeV.root"  ) );

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
    lumiweight.push_back(0.0391);

  // ---
  // do lumiweighting
  // ---

  eta_[kSigPy10]->Scale(lumiweight[kSigPy10]);
  phi_[kSigPy10]->Scale(lumiweight[kSigPy10]);
  pt_ [kSigPy10]->Scale(lumiweight[kSigPy10]);
  etaGen_[kSigPy10]->Scale(lumiweight[kSigPy10]);
  phiGen_[kSigPy10]->Scale(lumiweight[kSigPy10]);
  ptGen_ [kSigPy10]->Scale(lumiweight[kSigPy10]);
  etaMuPlus_[kSigPy10]->Scale(lumiweight[kSigPy10]);
  phiMuPlus_[kSigPy10]->Scale(lumiweight[kSigPy10]);
  ptMuPlus_ [kSigPy10]->Scale(lumiweight[kSigPy10]);
  etaMuMinus_[kSigPy10]->Scale(lumiweight[kSigPy10]);
  phiMuMinus_[kSigPy10]->Scale(lumiweight[kSigPy10]);
  ptMuMinus_ [kSigPy10]->Scale(lumiweight[kSigPy10]);

  // ---
  //    configure histograms
  // ---

  histogramStyle(*eta_ [kSigPy10], kSigPy10);
  histogramStyle(*phi_ [kSigPy10], kSigPy10);
  histogramStyle(*pt_  [kSigPy10], kSigPy10);
  histogramStyle(*etaGen_ [kSigPy10], kSigPy10);
  histogramStyle(*phiGen_ [kSigPy10], kSigPy10);
  histogramStyle(*ptGen_  [kSigPy10], kSigPy10);
  histogramStyle(*etaMuPlus_ [kSigPy10], kSigPy10);
  histogramStyle(*phiMuPlus_ [kSigPy10], kSigPy10);
  histogramStyle(*ptMuPlus_  [kSigPy10], kSigPy10);
  histogramStyle(*etaMuMinus_ [kSigPy10], kSigPy10);
  histogramStyle(*phiMuMinus_ [kSigPy10], kSigPy10);
  histogramStyle(*ptMuMinus_  [kSigPy10], kSigPy10);

  // ---
  //    calculate stability and purity
  // ---

  // do it for pt
  // binning range
  double pt0= 0;
  double pt1= 20;
  double pt2= 40;
  double pt3= 65;
  double pt4= 150;
  double pt5= 400;

  // content in condensed bins
  double ptBinA1 = 0;
  double ptBinA2 = 0;
  double ptBinA3 = 0;
  double ptBinA4 = 0;
  double ptBinA5 = 0;
  double ptBinB1 = 0;
  double ptBinB2 = 0;
  double ptBinB3 = 0;
  double ptBinB4 = 0;
  double ptBinB5 = 0;
  double ptBinC1 = 0;
  double ptBinC2 = 0;
  double ptBinC3 = 0;
  double ptBinC4 = 0;
  double ptBinC5 = 0;
  double ptBinD1 = 0;
  double ptBinD2 = 0;
  double ptBinD3 = 0;
  double ptBinD4 = 0;
  double ptBinD5 = 0;
  double ptBinE1 = 0; 
  double ptBinE2 = 0;
  double ptBinE3 = 0;
  double ptBinE4 = 0;
  double ptBinE5 = 0;

  // calculation of each bin square in correlation plot
  for(int i=pt0; i<=pt1; i++){
    for(int j=pt0; j<=pt1; j++){
      ptBinA1+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of A1 pt-Bin is " << ptBinA1 << std::endl;

  for(int i=pt0; i<=pt1; i++){
    for(int j=pt1; j<=pt2; j++){
      ptBinA2+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of A2 pt-Bin is " << ptBinA2 << std::endl;

  for(int i=pt0; i<=pt1; i++){
    for(int j=pt2; j<=pt3; j++){
      ptBinA3+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of A3 pt-Bin is " << ptBinA3 << std::endl;

  for(int i=pt0; i<=pt1; i++){
    for(int j=pt3; j<=pt4; j++){
      ptBinA4+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of A4 pt-Bin is " << ptBinA4 << std::endl;

  for(int i=pt0; i<=pt1; i++){
    for(int j=pt4; j<=pt5; j++){
      ptBinA5+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of A5 pt-Bin is " << ptBinA5 << std::endl;

  for(int i=pt1; i<=pt2; i++){
    for(int j=pt0; j<=pt1; j++){
      ptBinB1+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of B1 pt-Bin is " << ptBinB1 << std::endl;

  for(int i=pt1; i<=pt2; i++){
    for(int j=pt1; j<=pt2; j++){
      ptBinB2+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of B2 pt-Bin is " << ptBinB2 << std::endl;

  for(int i=pt1; i<=pt2; i++){
    for(int j=pt2; j<=pt3; j++){
      ptBinB3+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of B3 pt-Bin is " << ptBinB3 << std::endl;

  for(int i=pt1; i<=pt2; i++){
    for(int j=pt3; j<=pt4; j++){
      ptBinB4+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }

  std::cout << "content of B4 pt-Bin is " << ptBinB4 << std::endl;

  for(int i=pt1; i<=pt2; i++){
    for(int j=pt4; j<=pt5; j++){
      ptBinB5+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }

  std::cout << "content of B5 pt-Bin is " << ptBinB5 << std::endl;

  for(int i=pt2; i<=pt3; i++){
    for(int j=pt0; j<=pt1; j++){
      ptBinC1+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of C1 pt-Bin is " << ptBinC1 << std::endl;

  for(int i=pt2; i<=pt3; i++){
    for(int j=pt1; j<=pt2; j++){
      ptBinC2+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of C2 pt-Bin is " << ptBinC2 << std::endl;

  for(int i=pt2; i<=pt3; i++){
    for(int j=pt2; j<=pt3; j++){
      ptBinC3+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of C3 pt-Bin is " << ptBinC3 << std::endl;

  for(int i=pt2; i<=pt3; i++){
    for(int j=pt3; j<=pt4; j++){
      ptBinC4+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }

  std::cout << "content of C4 pt-Bin is " << ptBinC4 << std::endl;

  for(int i=pt2; i<=pt3; i++){
    for(int j=pt4; j<=pt5; j++){
      ptBinC5+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }

  std::cout << "content of C5 pt-Bin is " << ptBinC5 << std::endl;

  for(int i=pt3; i<=pt4; i++){
    for(int j=pt0; j<=pt1; j++){
      ptBinD1+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of D1 pt-Bin is " << ptBinD1 << std::endl;

  for(int i=pt3; i<=pt4; i++){
    for(int j=pt1; j<=pt2; j++){
      ptBinD2+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of D2 pt-Bin is " << ptBinD2 << std::endl;

  for(int i=pt3; i<=pt4; i++){
    for(int j=pt2; j<=pt3; j++){
      ptBinD3+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of D3 pt-Bin is " << ptBinD3 << std::endl;

  for(int i=pt3; i<=pt4; i++){
    for(int j=pt3; j<=pt4; j++){
      ptBinD4+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }

  std::cout << "content of D4 pt-Bin is " << ptBinD4 << std::endl;

  for(int i=pt3; i<=pt4; i++){
    for(int j=pt4; j<=pt5; j++){
      ptBinD5+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }

  std::cout << "content of D5 pt-Bin is " << ptBinD5 << std::endl;

 for(int i=pt4; i<=pt5; i++){
    for(int j=pt0; j<=pt1; j++){
      ptBinE1+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of E1 pt-Bin is " << ptBinE1 << std::endl;

  for(int i=pt4; i<=pt5; i++){
    for(int j=pt1; j<=pt2; j++){
      ptBinE2+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of E2 pt-Bin is " << ptBinE2 << std::endl;

  for(int i=pt4; i<=pt5; i++){
    for(int j=pt2; j<=pt3; j++){
      ptBinE3+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of E3 pt-Bin is " << ptBinE3 << std::endl;

  for(int i=pt4; i<=pt5; i++){
    for(int j=pt3; j<=pt4; j++){
      ptBinE4+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }

  std::cout << "content of E4 pt-Bin is " << ptBinE4 << std::endl;

  for(int i=pt4; i<=pt5; i++){
    for(int j=pt4; j<=pt5; j++){
      ptBinE5+= corrPt_[kSigPy10]->GetBinContent(i,j);
    }
  }
  std::cout << "content of E5 pt-Bin is " << ptBinE5 << std::endl;
  
  // Get Purity
  double PurityPtBin1 =  ptBinA1/(ptBinA1+ptBinA2+ptBinA3+ptBinA4+ptBinA5);
  std::cout << "putity of 1st pt-Bin is " << PurityPtBin1 << std::endl;
  double PurityPtBin2 =  ptBinB2/(ptBinB1+ptBinB2+ptBinB3+ptBinB4+ptBinB5);
  std::cout << "putity of 2nd pt-Bin is " << PurityPtBin2 << std::endl;
  double PurityPtBin3 =  ptBinC3/(ptBinC1+ptBinC2+ptBinC3+ptBinC4+ptBinC5);
  std::cout << "putity of 3rd pt-Bin is " << PurityPtBin3 << std::endl;
  double PurityPtBin4 =  ptBinD4/(ptBinD1+ptBinD2+ptBinD3+ptBinD4+ptBinD5);
  std::cout << "putity of 4th pt-Bin is " << PurityPtBin4 << std::endl;
  double PurityPtBin5 =  ptBinE5/(ptBinE1+ptBinE2+ptBinE3+ptBinE4+ptBinE5);
  std::cout << "putity of 5th pt-Bin is " << PurityPtBin5 << std::endl;

  // Get Stability
  double StabilityPtBin1 = ptBinA1/(ptBinA1+ptBinB1+ptBinC1+ptBinD1+ptBinE1);
  std::cout << "stability of 1st pt-Bin is " << StabilityPtBin1 << std::endl;
  double StabilityPtBin2 = ptBinB2/(ptBinA2+ptBinB2+ptBinC2+ptBinD2+ptBinE2);
  std::cout << "stability of 2nd pt-Bin is " << StabilityPtBin2 << std::endl;
  double StabilityPtBin3 = ptBinC3/(ptBinA3+ptBinB3+ptBinC3+ptBinD3+ptBinE3);
  std::cout << "stability of 3rd pt-Bin is " << StabilityPtBin3 << std::endl;
  double StabilityPtBin4 = ptBinD4/(ptBinA4+ptBinB4+ptBinC4+ptBinD4+ptBinE4);
  std::cout << "stability of 4th pt-Bin is " << StabilityPtBin4 << std::endl;
  double StabilityPtBin5 = ptBinE5/(ptBinA5+ptBinB5+ptBinC5+ptBinD5+ptBinE5);
  std::cout << "stability of 5th pt-Bin is " << StabilityPtBin5 << std::endl;

  // ---
  //    create legends 
  // ---

    // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia, 10TeV)");
  leg0->AddEntry( pt_[kSigPy10], "all semi-lep. ( #mu )"  , "PL");
  leg0->AddEntry( ptMuMinus_[kSigPy10], "only  #mu^{-} "  , "PL");
  leg0->AddEntry( ptMuPlus_ [kSigPy10], "only  #mu^{+} "  , "PL");


  // ---
  //    do the printing for pt_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // draw canvas
  canv0->cd(0);
  canv0->SetTitle("pt distribution tight  #mu after Selection");
  axesStyle(*pt_ [kSigPy10], "p_{t} ( tight #mu ) [GeV]", "events");
  pt_ [kSigPy10]->SetMinimum(0.);
  pt_ [kSigPy10]->SetMaximum(1.8* pt_ [kSigPy10]->GetMaximum() );
  pt_ [kSigPy10]->Draw();
  ptMuPlus_  [kSigPy10]->SetLineColor (kBlue);
  //  ptMuPlus_  [kSigPy10]->SetLineStyle(2);
  ptMuPlus_  [kSigPy10]->Draw("same");
  ptMuMinus_ [kSigPy10]->SetLineColor (kRed);
  ptMuMinus_ [kSigPy10]->SetLineStyle(2);
  ptMuMinus_ [kSigPy10]->Draw("same");
  leg0                 ->Draw("same");

  // ---
  //    do the printing for eta_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetTitle("eta distribution tight  #mu after Selection");
  axesStyle(*eta_ [kSigPy10], "#eta ( tight #mu )", "events");
  eta_ [kSigPy10]->SetMinimum(0.);
  eta_ [kSigPy10]->SetMaximum(1.8* eta_ [kSigPy10]->GetMaximum() );
  eta_ [kSigPy10]->Draw();
  etaMuPlus_  [kSigPy10]->SetLineColor (kBlue);
  //  etaMuPlus_  [kSigPy10]->SetLineStyle(2);
  etaMuPlus_  [kSigPy10]->Draw("same");
  etaMuMinus_ [kSigPy10]->SetLineColor (kRed);
  etaMuMinus_ [kSigPy10]->SetLineStyle(2);
  etaMuMinus_ [kSigPy10]->Draw("same");
  leg0                 ->Draw("same");

  // ---
  //    do the printing for phi_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetTitle("phi distribution tight  #mu after Selection");
  axesStyle(*phi_ [kSigPy10], "#phi ( tight #mu )", "events");
  phi_ [kSigPy10]->SetMinimum(0.);
  phi_ [kSigPy10]->SetMaximum(1.8* phi_ [kSigPy10]->GetMaximum() );
  phi_ [kSigPy10]->Draw();
  phiMuPlus_  [kSigPy10]->SetLineColor (kBlue);
  //  phiMuPlus_  [kSigPy10]->SetLineStyle(2);
  phiMuPlus_  [kSigPy10]->Draw("same");
  phiMuMinus_ [kSigPy10]->SetLineColor (kRed);
  phiMuMinus_ [kSigPy10]->SetLineStyle(2);
  phiMuMinus_ [kSigPy10]->Draw("same");
  leg0                  ->Draw("same");

  // ---
  //    do the printing for corrPt_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  canv3->SetTitle("gen-reco correlation of p_{t} ( muon )");
  corrPt_[kSigPy10]->SetTitle("correlation of p_{t} ( muon )");
  corrPt_[kSigPy10]->GetXaxis()->SetTitle("p_{t} ( gen #mu ) [GeV]");
  corrPt_[kSigPy10]->GetXaxis()->SetTitleSize ( 0.05 );
  corrPt_[kSigPy10]->GetXaxis()->SetLabelColor(  1   );
  corrPt_[kSigPy10]->GetXaxis()->SetLabelFont ( 62   );
  corrPt_[kSigPy10]->GetXaxis()->SetLabelSize ( 0.04 );
  corrPt_[kSigPy10]->GetXaxis()->SetNdivisions(  505 );
  corrPt_[kSigPy10]->GetXaxis()->CenterTitle  ( true );

  corrPt_[kSigPy10]->GetYaxis()->SetTitle("p_{t} ( reco #mu ) [GeV]");
  corrPt_[kSigPy10]->GetYaxis()->SetTitleSize  ( 0.05 );
  corrPt_[kSigPy10]->GetYaxis()->SetTitleColor (    1 );
  corrPt_[kSigPy10]->GetYaxis()->SetTitleOffset(  1.1 );
  corrPt_[kSigPy10]->GetYaxis()->SetTitleFont  (   62 );
  corrPt_[kSigPy10]->GetYaxis()->SetLabelSize  ( 0.04 );
  corrPt_[kSigPy10]->GetYaxis()->SetLabelFont  (   62 );
  corrPt_[kSigPy10]->GetYaxis()->SetNdivisions (  505 );
  corrPt_[kSigPy10]->GetYaxis()->CenterTitle   ( true );

  corrPt_[kSigPy10]->SetStats(kFALSE);
  corrPt_[kSigPy10]->SetFillColor( kRed );
  corrPt_[kSigPy10]->Draw("");


  // ---
  //    do the printing for corrEta_
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(*canv4);

  // draw canvas
  canv4->cd(0);
  canv4->SetTitle("gen-reco correlation of #eta ( muon )");
  corrEta_[kSigPy10]->SetTitle("correlation of #eta ( muon )");
  corrEta_[kSigPy10]->GetXaxis()->SetTitle("#eta ( gen #mu )");
  corrEta_[kSigPy10]->GetXaxis()->SetTitleSize ( 0.05 );
  corrEta_[kSigPy10]->GetXaxis()->SetLabelColor(  1   );
  corrEta_[kSigPy10]->GetXaxis()->SetLabelFont ( 62   );
  corrEta_[kSigPy10]->GetXaxis()->SetLabelSize ( 0.04 );
  corrEta_[kSigPy10]->GetXaxis()->SetNdivisions(  505 );
  corrEta_[kSigPy10]->GetXaxis()->CenterTitle  ( true );

  corrEta_[kSigPy10]->GetYaxis()->SetTitle("#eta ( reco #mu )");
  corrEta_[kSigPy10]->GetYaxis()->SetTitleSize  ( 0.05 );
  corrEta_[kSigPy10]->GetYaxis()->SetTitleColor (    1 );
  corrEta_[kSigPy10]->GetYaxis()->SetTitleOffset(  1.1 );
  corrEta_[kSigPy10]->GetYaxis()->SetTitleFont  (   62 );
  corrEta_[kSigPy10]->GetYaxis()->SetLabelSize  ( 0.04 );
  corrEta_[kSigPy10]->GetYaxis()->SetLabelFont  (   62 );
  corrEta_[kSigPy10]->GetYaxis()->SetNdivisions (  505 );
  corrEta_[kSigPy10]->GetYaxis()->CenterTitle   ( true );

  corrEta_[kSigPy10]->SetStats(kFALSE);
  corrEta_[kSigPy10]->SetFillColor( kRed );
  corrEta_[kSigPy10]->Draw("");

  // ---
  //    do the printing for corrPhi_
  // ---
  TCanvas* canv5 = new TCanvas("canv5", "canv5", 600, 600); canvasStyle(*canv5);

  // draw canvas
  canv5->cd(0);
  canv5->SetTitle("gen-reco correlation of #phi ( muon )");
  corrPhi_[kSigPy10]->SetTitle("correlation of #phi ( muon )");
  corrPhi_[kSigPy10]->GetXaxis()->SetTitle("#phi ( gen #mu )");
  corrPhi_[kSigPy10]->GetXaxis()->SetTitleSize ( 0.05 );
  corrPhi_[kSigPy10]->GetXaxis()->SetLabelColor(  1   );
  corrPhi_[kSigPy10]->GetXaxis()->SetLabelFont ( 62   );
  corrPhi_[kSigPy10]->GetXaxis()->SetLabelSize ( 0.04 );
  corrPhi_[kSigPy10]->GetXaxis()->SetNdivisions(  505 );
  corrPhi_[kSigPy10]->GetXaxis()->CenterTitle  ( true );

  corrPhi_[kSigPy10]->GetYaxis()->SetTitle("#phi ( reco #mu )");
  corrPhi_[kSigPy10]->GetYaxis()->SetTitleSize  ( 0.05 );
  corrPhi_[kSigPy10]->GetYaxis()->SetTitleColor (    1 );
  corrPhi_[kSigPy10]->GetYaxis()->SetTitleOffset(  1.1 );
  corrPhi_[kSigPy10]->GetYaxis()->SetTitleFont  (   62 );
  corrPhi_[kSigPy10]->GetYaxis()->SetLabelSize  ( 0.04 );
  corrPhi_[kSigPy10]->GetYaxis()->SetLabelFont  (   62 );
  corrPhi_[kSigPy10]->GetYaxis()->SetNdivisions (  505 );
  corrPhi_[kSigPy10]->GetYaxis()->CenterTitle   ( true );

  corrPhi_[kSigPy10]->SetStats(kFALSE);
  corrPhi_[kSigPy10]->SetFillColor( kRed );
  corrPhi_[kSigPy10]->Draw("");


  // Create stability_ histogramm

  Float_t BinningValuesPt[6];
  BinningValuesPt[0]= pt0 ;
  BinningValuesPt[1]= pt1 ;
  BinningValuesPt[2]= pt2 ;
  BinningValuesPt[3]= pt3 ;
  BinningValuesPt[4]= pt4 ;
  BinningValuesPt[5]= pt5 ;

  TH1F* ptStability = new TH1F("ptStability","ptStability",5, BinningValuesPt);

  ptStability->SetBinContent( 1, 0               );
  ptStability->SetBinContent( 2, StabilityPtBin2 );
  ptStability->SetBinContent( 3, StabilityPtBin3 );
  ptStability->SetBinContent( 4, StabilityPtBin4 );
  ptStability->SetBinContent( 5, StabilityPtBin5 );

  // ---
  //    do the printing for ptStability
  // ---
  TCanvas* canv6 = new TCanvas("canv6", "canv6", 600, 600); canvasStyle(*canv6);

  // draw canvas
  canv6->SetTitle("stability for pt ( #mu )");
  ptStability->SetTitle("stability for pt ( #mu )");
  ptStability->GetXaxis()->SetTitle("p_{t} ( #mu ) [GeV]");
  ptStability->GetYaxis()->SetTitle("stablility");
  ptStability->GetXaxis()->CenterTitle   ( true );
  ptStability->GetYaxis()->CenterTitle   ( true );
  ptStability->GetYaxis()->SetTitleOffset(  2.0 );
  ptStability->GetXaxis()->SetTitleSize  ( 0.05 );
  ptStability->GetYaxis()->SetTitleSize  ( 0.05 );
  ptStability->SetStats(kFALSE);
  ptStability->Draw("");


  // Create purity_ histogramm

  TH1F* ptPurity = new TH1F("ptPurity","ptPurity",5, BinningValuesPt);

  ptPurity->SetBinContent( 1, 0               );
  ptPurity->SetBinContent( 2, PurityPtBin2 );
  ptPurity->SetBinContent( 3, PurityPtBin3 );
  ptPurity->SetBinContent( 4, PurityPtBin4 );
  ptPurity->SetBinContent( 5, PurityPtBin5 );

  // ---
  //    do the printing for ptPurity
  // ---
  TCanvas* canv7 = new TCanvas("canv7", "canv7", 600, 600); canvasStyle(*canv7);

  // draw canvas
  canv7->SetTitle("purity for pt ( #mu )");
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
  // saving
  // ---
  

  // ps
  canv0->Print("./diffXSecFromSignal/diffXStuff.ps(");
  canv1->Print("./diffXSecFromSignal/diffXStuff.ps");
  canv2->Print("./diffXSecFromSignal/diffXStuff.ps");
  canv3->Print("./diffXSecFromSignal/diffXStuff.ps");
  canv4->Print("./diffXSecFromSignal/diffXStuff.ps");
  canv5->Print("./diffXSecFromSignal/diffXStuff.ps");
  canv6->Print("./diffXSecFromSignal/diffXStuff.ps");
  canv7->Print("./diffXSecFromSignal/diffXStuff.ps)");

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
