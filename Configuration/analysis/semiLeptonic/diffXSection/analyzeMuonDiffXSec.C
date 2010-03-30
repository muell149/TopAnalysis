
// ---------description---------------------------------
// -----------------------------------------------------
// this Makro collects distrubutions for the Determination
// of the differntial cross sectionsuch as eta, phi,
// pt (all for muon), Correlation gen - reco, 
// purity and stability from MuonDiffXSec class analyzer
// and  plots d#sigma/dpt(#mu)/#sigma
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

void analyzeMuonDiffXSec()
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
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecSigMcAtNlo7TeV.root"      ) );

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
  // create Vector to store output statements
  // ---
  std::vector<TString> output_;
  TString textHelper = "";
  output_.push_back("MC@NLO 7 TeV");

  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;

  // for current 7TeV Mc@Nlo sample (shifted, unshifted and background)
  lumiweight.push_back(0.0083);

  // ---
  // do lumiweighting
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    eta_[idx]->Scale(lumiweight[idx]);
    phi_[idx]->Scale(lumiweight[idx]);
    pt_ [idx]->Scale(lumiweight[idx]);
    etaGen_[idx]->Scale(lumiweight[idx]);
    phiGen_[idx]->Scale(lumiweight[idx]);
    ptGen_ [idx]->Scale(lumiweight[idx]);
    etaMuPlus_[idx]->Scale(lumiweight[idx]);
    phiMuPlus_[idx]->Scale(lumiweight[idx]);
    ptMuPlus_ [idx]->Scale(lumiweight[idx]);
    etaMuMinus_[idx]->Scale(lumiweight[idx]);
    phiMuMinus_[idx]->Scale(lumiweight[idx]);
    ptMuMinus_ [idx]->Scale(lumiweight[idx]);
  }

  // ---  
  //    clone plots with weighted event numbers
  // ---
  
  std::vector<TH1F*> etaEventNumbers_, phiEventNumbers_, ptEventNumbers_, etaGenEventNumbers_, phiGenEventNumbers_, ptGenEventNumbers_, etaMuPlusEventNumbers_, phiMuPlusEventNumbers_, ptMuPlusEventNumbers_ , etaMuMinusEventNumbers_, phiMuMinusEventNumbers_, ptMuMinusEventNumbers_;
  
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    etaEventNumbers_.push_back( (TH1F*)(eta_[idx]->Clone()) );
    phiEventNumbers_.push_back( (TH1F*)(phi_[idx]->Clone()) );
    ptEventNumbers_.push_back ( (TH1F*)(pt_ [idx]->Clone()) );
    etaGenEventNumbers_.push_back( (TH1F*)(etaGen_[idx]->Clone()) );
    phiGenEventNumbers_.push_back( (TH1F*)(phiGen_[idx]->Clone()) );
    ptGenEventNumbers_.push_back ( (TH1F*)(ptGen_ [idx]->Clone()) );
    etaMuPlusEventNumbers_.push_back( (TH1F*)(etaMuPlus_[idx]->Clone()) );
    phiMuPlusEventNumbers_.push_back(  (TH1F*)(phiMuPlus_[idx]->Clone()) );
    ptMuPlusEventNumbers_.push_back (  (TH1F*)(ptMuPlus_ [idx]->Clone()) );
    etaMuMinusEventNumbers_.push_back(  (TH1F*)(etaMuMinus_[idx]->Clone()) );
    phiMuMinusEventNumbers_.push_back(  (TH1F*)(phiMuMinus_[idx]->Clone()) );
    ptMuMinusEventNumbers_.push_back (  (TH1F*)(ptMuMinus_ [idx]->Clone()) );
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
    ptGen_ [idx]->Scale(1/eventNumbersPt_[idx]);
    ptMuPlus_ [idx]->Scale(1/eventNumbersPt_[idx]);
    ptMuMinus_ [idx]->Scale(1/eventNumbersPt_[idx]);
    
    eta_ [idx]->Scale(1/eventNumbersEta_[idx]);
    etaGen_ [idx]->Scale(1/eventNumbersEta_[idx]);
    etaMuPlus_ [idx]->Scale(1/eventNumbersEta_[idx]);
    etaMuMinus_ [idx]->Scale(1/eventNumbersEta_[idx]);
      
    phi_ [idx]->Scale(1/eventNumbersPhi_[idx]);
    phiGen_ [idx]->Scale(1/eventNumbersPhi_[idx]);
    phiMuPlus_ [idx]->Scale(1/eventNumbersPhi_[idx]);
    phiMuMinus_ [idx]->Scale(1/eventNumbersPhi_[idx]);
  }

  // ---
  //    division by binwidth
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {

    for(int i=1; i<= pt_[idx]->GetNbinsX(); i++){
      pt_[idx]->SetBinContent(i,((double)(pt_[idx]->GetBinContent(i))/(double)(pt_[idx]->GetBinWidth(i)))  );
      ptGen_[idx]->SetBinContent(i,((double)(ptGen_[idx]->GetBinContent(i))/(double)(ptGen_[idx]->GetBinWidth(i)))  );
      ptMuPlus_[idx]->SetBinContent(i,((double)(ptMuPlus_[idx]->GetBinContent(i))/(double)(ptMuPlus_[idx]->GetBinWidth(i)))  );
      ptMuMinus_[idx]->SetBinContent(i,((double)(ptMuMinus_[idx]->GetBinContent(i))/(double)(ptMuMinus_[idx]->GetBinWidth(i)))  );
    }
    
    for(int i=1; i<= phi_[idx]->GetNbinsX(); i++){
      phi_[idx]->SetBinContent(i,((double)(phi_[idx]->GetBinContent(i))/(double)(phi_[idx]->GetBinWidth(i)))  );
      phiGen_[idx]->SetBinContent(i,((double)(phiGen_[idx]->GetBinContent(i))/(double)(phiGen_[idx]->GetBinWidth(i)))  );
      phiMuPlus_[idx]->SetBinContent(i,((double)(phiMuPlus_[idx]->GetBinContent(i))/(double)(phiMuPlus_[idx]->GetBinWidth(i)))  );
      phiMuMinus_[idx]->SetBinContent(i,((double)(phiMuMinus_[idx]->GetBinContent(i))/(double)(phiMuMinus_[idx]->GetBinWidth(i)))  );
    }
    
    for(int i=1; i<= eta_[idx]->GetNbinsX(); i++){
      eta_[idx]->SetBinContent(i,((double)(eta_[idx]->GetBinContent(i))/(double)(eta_[idx]->GetBinWidth(i)))  );
      etaGen_[idx]->SetBinContent(i,((double)(etaGen_[idx]->GetBinContent(i))/(double)(etaGen_[idx]->GetBinWidth(i)))  );
      etaMuPlus_[idx]->SetBinContent(i,((double)(etaMuPlus_[idx]->GetBinContent(i))/(double)(etaMuPlus_[idx]->GetBinWidth(i)))  );
      etaMuMinus_[idx]->SetBinContent(i,((double)(etaMuMinus_[idx]->GetBinContent(i))/(double)(etaMuMinus_[idx]->GetBinWidth(i)))  );
    }
  }

  // ---
  //    configure histograms
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    histogramStyle(*eta_ [idx], idx);
    histogramStyle(*phi_ [idx], idx);
    histogramStyle(*pt_  [idx], idx);
    histogramStyle(*etaGen_ [idx], idx);
    histogramStyle(*phiGen_ [idx], idx);
    histogramStyle(*ptGen_  [idx], idx);
    histogramStyle(*etaMuPlus_ [idx], idx);
    histogramStyle(*phiMuPlus_ [idx], idx);
    histogramStyle(*ptMuPlus_  [idx], idx);
    histogramStyle(*etaMuMinus_ [idx], idx);
    histogramStyle(*phiMuMinus_ [idx], idx);
    histogramStyle(*ptMuMinus_  [idx], idx);
    histogramStyle(*etaEventNumbers_ [idx], idx);
    histogramStyle(*phiEventNumbers_ [idx], idx);
    histogramStyle(*ptEventNumbers_  [idx], idx);
    histogramStyle(*etaGenEventNumbers_ [idx], idx);
    histogramStyle(*phiGenEventNumbers_ [idx], idx);
    histogramStyle(*ptGenEventNumbers_  [idx], idx);
    histogramStyle(*etaMuPlusEventNumbers_ [idx], idx);
    histogramStyle(*phiMuPlusEventNumbers_ [idx], idx);
    histogramStyle(*ptMuPlusEventNumbers_  [idx], idx);
    histogramStyle(*etaMuMinusEventNumbers_ [idx], idx);
    histogramStyle(*phiMuMinusEventNumbers_ [idx], idx);
    histogramStyle(*ptMuMinusEventNumbers_ [idx], idx);
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
  //    calculate statistical error for differential xSec from signal sample via gaussian error calculus
  // ---

  std::vector<double> ptDiffXError_;

  // i: calculation for each bin (starting with filled bin which is the 2nd)

  for(int i =2; i<=totalBinNumber+1; i++){

    // calculate shortcut expression needed in final formula
    double errorHelperA=0;  
    errorHelperA= ( (double)(pt_[kSig]->GetBinWidth(i)) * eventNumbersPt_[kSig] ); 

    // final formula
    ptDiffXError_.push_back(   sqrt(  ((double)(ptEventNumbers_ [kSig]->GetBinContent(i)) / errorHelperA / errorHelperA) * ( 1.0 - 2.0 * (double)(pt_[kSig]->GetBinWidth(i)) / errorHelperA + ( (double)(ptEventNumbers_ [kSig]->GetBinContent(i)) * (double)(pt_[kSig]->GetBinWidth(i)) * (double)(pt_[kSig]->GetBinWidth(i)) * (eventNumbersPt_[kSig])  / errorHelperA / errorHelperA) )  )   );
  }

  // ---
  //    print out # of events (weighted) for each bin (including overflow) with statistical errors
  // ---

  for(int i=2; i<= pt_[kSig]->GetNbinsX()+1; i++){
    std::cout << "(weighted) # events pt-bin "<< i << ": " <<  ptEventNumbers_[kSig]->GetBinContent(i) << " +/- " << sqrt( (double)(ptEventNumbers_[kSig]->GetBinContent(i)) ) << std::endl;
    textHelper = "(weighted) # events pt-bin ";
    textHelper += i ;
    textHelper += ": ";
    textHelper += ptEventNumbers_[kSig]->GetBinContent(i);
    textHelper += " +/- " ;
    textHelper += sqrt( (double)(ptEventNumbers_[kSig]->GetBinContent(i)) );
    output_ .push_back(textHelper);
  }

  // ---
  //    print out diffXValue(pt) for each bin with statistical errors
  // ---

  for(int i=2; i<= pt_[kSig]->GetNbinsX(); i++){
    std::cout << "(d#sigma)/(dpt(muon) * #sigma) pt-bin "<< i << ": " <<  pt_[kSig]->GetBinContent(i) << " +/- " <<  ptDiffXError_[i-2] << std::endl;
    textHelper = "(weighted) # events pt-bin ";
    textHelper += i ;
    textHelper += ": ";
    textHelper += pt_[kSig]->GetBinContent(i);
    textHelper += " +/- " ;
    textHelper += ptDiffXError_[i-2];
    output_ .push_back(textHelper);
  }

  // ---
  //    create legends 
  // ---

  // create a legend (in upper right corner) for Signal, #mu+/-
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop (MC @ NLO 7TeV)");
  leg0->AddEntry( pt_[kSig], "all semi-lep. ( #mu )"  , "PL");
  leg0->AddEntry( ptMuMinus_[kSig], "only  #mu^{-} "  , "PL");
  leg0->AddEntry( ptMuPlus_ [kSig], "only  #mu^{+} "  , "PL");

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
  //    do the printing for pt_ ( Signal, mu+/- )
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);

  // draw canvas
  canv0->cd(0);
  canv0->SetTitle("diffX pt distribution tight  #mu after Selection");
  axesStyle(*pt_ [kSig], "p_{t} ( tight #mu ) [GeV]", "#frac{1}{#sigma} * #frac{d#sigma}{dp_{t}(#mu)}");
  pt_ [kSig]->GetYaxis()->SetTitleSize  ( 0.04 );
  pt_ [kSig]->GetYaxis()->SetTitleOffset( 2.0  );
  pt_ [kSig]->SetMinimum(0.);
  pt_ [kSig]->SetMaximum(1.5* pt_ [kSig]->GetMaximum() );
  pt_ [kSig]->SetBinError( 1, 0. );
  for(int i =2; i<= totalBinNumber+1; i++){
    pt_ [kSig]->SetBinError(  i, ptDiffXError_[i-2]  );
  }
  pt_ [kSig]->Draw(); 
  ptMuMinus_ [kSig]->SetLineColor (kBlue);
  ptMuMinus_ [kSig]->SetLineStyle(3);
  ptMuMinus_ [kSig]->Draw("same");
  ptMuPlus_  [kSig]->SetLineColor (kRed);
  ptMuPlus_  [kSig]->SetLineStyle(2);
  ptMuPlus_  [kSig]->Draw("same");
  leg0             ->Draw("same");

  // ---
  //    do the printing for eta_ ( Signal, mu+/- )
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetTitle("diffX eta distribution tight  #mu after Selection");
  axesStyle(*eta_ [kSig], "#eta ( tight #mu )", "#frac{1}{#sigma} * #frac{d#sigma}{dp_{t}(#mu)}");
  eta_ [kSig]->GetYaxis()->SetTitleSize  ( 0.04 );
  eta_ [kSig]->GetYaxis()->SetTitleOffset( 2.0  );
  eta_ [kSig]->SetMinimum(0.);
  eta_ [kSig]->SetMaximum(1.8* eta_ [kSig]->GetMaximum() );
  eta_ [kSig]->Draw();
  etaMuMinus_ [kSig]->SetLineColor (kBlue);
  etaMuMinus_ [kSig]->SetLineStyle(3);
  etaMuMinus_ [kSig]->Draw("same");
  etaMuPlus_  [kSig]->SetLineColor (kRed);
  etaMuPlus_  [kSig]->SetLineStyle(2);
  etaMuPlus_  [kSig]->Draw("same");
  leg0              ->Draw("same");

  // ---
  //    do the printing for phi_ ( Signal, mu+/- )
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetTitle("diffX phi distribution tight  #mu after Selection");
  axesStyle(*phi_ [kSig], "#phi ( tight #mu )", "#frac{1}{#sigma} * #frac{d#sigma}{dp_{t}(#mu)}");
  phi_ [kSig]->GetYaxis()->SetTitleSize  ( 0.04 );
  phi_ [kSig]->GetYaxis()->SetTitleOffset( 2.0  );
  phi_ [kSig]->SetMinimum(0.);
  phi_ [kSig]->SetMaximum(1.8* phi_ [kSig]->GetMaximum() );
  phi_ [kSig]->Draw();
  phiMuMinus_ [kSig]->SetLineColor (kBlue);
  phiMuMinus_ [kSig]->SetLineStyle(3);
  phiMuMinus_ [kSig]->Draw("same");
  phiMuPlus_  [kSig]->SetLineColor (kRed);
  phiMuPlus_  [kSig]->SetLineStyle(2);
  phiMuPlus_  [kSig]->Draw("same");
  leg0            ->Draw("same");

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
  corrPt_[kSig]->Draw("colz");


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
  //    do the printing for ptPurity, ptStability and ptAcceptance
  // ---
  TCanvas* canv7 = new TCanvas("canv7", "canv7", 600, 600); canvasStyle(*canv7);

  // draw canvas
  canv7->SetTitle("migration for pt ( #mu )");
  canv7->SetGrid(1,1);
  ptPurity->SetTitle("");
  ptPurity->GetXaxis()->SetTitle("p_{t} ( #mu ) [GeV]");
  //  ptPurity->GetYaxis()->SetTitle("");
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
  //    do the printing for ptEventNumbers_
  // ---
  TCanvas* canv10 = new TCanvas("canv10", "canv10", 600, 600); canvasStyle(*canv10);

  // draw canvas
  canv10->cd(0);
  canv10->SetTitle("pt distribution tight  #mu after Selection");
  axesStyle(*ptEventNumbers_ [kSig], "p_{t} ( tight #mu ) [GeV]", "events");
  ptEventNumbers_ [kSig]->SetMinimum(0.);
  ptEventNumbers_ [kSig]->SetMaximum(1.2* ptEventNumbers_ [kSig]->GetMaximum() );
  ptEventNumbers_ [kSig]->SetBinError( 1, 0. );
  for(int i =2; i<= totalBinNumber+1; i++){
    ptEventNumbers_ [kSig]->SetBinError(  i, sqrt( (double)(ptEventNumbers_[kSig]->GetBinContent(i)) )  );
  }
  ptEventNumbers_       [kSig]->Draw();
  ptMuPlusEventNumbers_ [kSig]->SetLineColor (kBlue);
  ptMuPlusEventNumbers_ [kSig]->SetLineStyle(3);
  ptMuPlusEventNumbers_ [kSig]->Draw("same");
  ptMuMinusEventNumbers_[kSig]->SetLineColor (kRed);
  ptMuMinusEventNumbers_[kSig]->SetLineStyle(2);
  ptMuMinusEventNumbers_[kSig]->Draw("same");
  leg0                        ->Draw("same");

  // ---
  //    do the printing for etaEventNumbers_
  // ---
  TCanvas* canv11 = new TCanvas("canv11", "canv11", 600, 600); canvasStyle(*canv11);

  // draw canvas
  canv11->cd(0);
  canv11->SetTitle("eta distribution tight  #mu after Selection");
  axesStyle(*etaEventNumbers_ [kSig], "#eta ( tight #mu )", "events");
  etaEventNumbers_ [kSig]->SetMinimum(0.);
  etaEventNumbers_ [kSig]->SetMaximum(1.8* etaEventNumbers_ [kSig]->GetMaximum() );
  etaEventNumbers_ [kSig]->Draw();
  etaMuPlusEventNumbers_ [kSig]->SetLineColor (kBlue);
  etaMuPlusEventNumbers_ [kSig]->SetLineStyle(3);
  etaMuPlusEventNumbers_ [kSig]->Draw("same");
  etaMuMinusEventNumbers_[kSig]->SetLineColor (kRed);
  etaMuMinusEventNumbers_[kSig]->SetLineStyle(2);
  etaMuMinusEventNumbers_[kSig]->Draw("same");
  leg0                         ->Draw("same");

  // ---
  //    do the printing for phiEventNumbers_
  // ---
  TCanvas* canv12 = new TCanvas("canv12", "canv12", 600, 600); canvasStyle(*canv12);

  // draw canvas
  canv12->cd(0);
  canv12->SetTitle("phi distribution tight  #mu after Selection");
  axesStyle(*phiEventNumbers_ [kSig], "#phi ( tight #mu )", "events");
  phiEventNumbers_ [kSig]->SetMinimum(0.);
  phiEventNumbers_ [kSig]->SetMaximum(1.8* phiEventNumbers_ [kSig]->GetMaximum() );
  phiEventNumbers_ [kSig]->Draw();
  phiMuPlusEventNumbers_ [kSig]->SetLineColor (kBlue);
  phiMuPlusEventNumbers_ [kSig]->SetLineStyle(3);
  phiMuPlusEventNumbers_ [kSig]->Draw("same");
  phiMuMinusEventNumbers_[kSig]->SetLineColor (kRed);
  phiMuMinusEventNumbers_[kSig]->SetLineStyle(2);
  phiMuMinusEventNumbers_[kSig]->Draw("same");
  leg0                         ->Draw("same");

  // ---
  // saving
  // ---
  
  // ps
//   canv10->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps(");
//   canv11->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps" );
//   canv12->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps" );
//   canv0->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps"  );
//   canv1->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps"  );
//   canv2->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps"  );
//   canv3->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps"  );
//   canv4->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps"  );
//   canv5->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps"  );
//   canv6->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps"  );
//   canv7->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps"  );
//   canv10->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps" );
//   canv11->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps" );
//   canv12->Print("./diffXSecFromSignal/plots/diffXStuffMcatnlo7TeV.ps)");

//   // png
//   canv0->Print("./diffXSecFromSignal/plots/ptDiffXSecMcatnlo7TeV.png"           );
//   canv1->Print("./diffXSecFromSignal/plots/etaDiffXSecMcatnlo7TeV.png"          );
//   canv2->Print("./diffXSecFromSignal/plots/phiDiffXSecMcatnlo7TeV.png"          );
//   canv3->Print("./diffXSecFromSignal/plots/ptGenRecoCorrelationMcatnlo7TeV.png" );
//   canv4->Print("./diffXSecFromSignal/plots/etaGenRecoCorrelationMcatnlo7TeV.png");
//   canv5->Print("./diffXSecFromSignal/plots/phiGenRecoCorrelationMcatnlo7TeV.png");
//   canv6->Print("./diffXSecFromSignal/plots/ptOutputMcatnlo7TeV.png"             );
//   canv7->Print("./diffXSecFromSignal/plots/ptMigrationMcatnlo7TeV.png"          );
//   canv10->Print("./diffXSecFromSignal/plots/ptInclusiveMcatnlo7TeV.png"         );
//   canv11->Print("./diffXSecFromSignal/plots/etaInclusiveMcatnlo7TeV.png"        );
//   canv12->Print("./diffXSecFromSignal/plots/phiInclusiveMcatnlo7TeV.png"        );
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
