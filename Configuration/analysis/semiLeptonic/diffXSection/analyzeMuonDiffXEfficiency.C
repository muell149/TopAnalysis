// ---------description---------------------------------
// -----------------------------------------------------
// this Makro determines the inclusive and differential, 
// normalized cross section ( d#sigma/dpt(#mu)/#sigma )
// for pt, eta and phi (of the muon). Additionally, it
// distinguishes between the charge of the muon.
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

enum styles {kttbarReco, kWjetsReco, kZjetsReco, kttbarGen, kWjetsGen, kZjetsGen};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void divideByBinwidth(std::vector<TH1F*> histoVector);
double getMaximumDependingOnNjetsCut(TString plot, TString Njets);

void analyzeMuonDiffXEfficiency()
{
  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  //  gStyle->SetPalette(1);
  gStyle->SetErrorX(0); 

  // ---
  //    choose jet multiplicity you want to see
  // ---
  // "Njets1" / "Njets2" / "Njets3" / "Njets4" / "Btag"
  TString jetMultiplicity ="Btag";

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecRecoAllTtbarMcAtNlo7TeVsummer09.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecWjetsMadgraph7TeV.root"               ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecZjetsMadgraph7TeV.root"               ) );

  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecGenAllTtbarMcAtNlo7TeVspring10.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecGenWjetsMadgraph7TeVspring10.root"   ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecGenZjetsMadgraph7TeVspring10.root"   ) );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> eta_, phi_, pt_;

  for(unsigned int idx=kttbarReco; idx<=kZjetsReco; ++idx) {
    eta_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/eta" ) );
    pt_  .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/pt"  ) );
    phi_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/phi" ) );
  }
  TString jetMultiplicity2= jetMultiplicity;
  if(jetMultiplicity=="Btag") jetMultiplicity2="Njets4";
  for(unsigned int idx=kttbarGen; idx<=kZjetsGen; ++idx) {
    eta_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionGen"+jetMultiplicity2+"/eta" ) );
    pt_  .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionGen"+jetMultiplicity2+"/pt"  ) );
    phi_ .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionGen"+jetMultiplicity2+"/phi" ) );
  }
  
  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;

  // for current summer09 ttbar(all) 7TeV Mc@Nlo sample (full statistics, 50pb-1)
  lumiweight.push_back(0.00830435);
  // for current summer09 W+jets 7TeV MADGRAPH sample (full statistics, 50pb-1)
  lumiweight.push_back(0.13099599);
  // for current summer09 Z+jets 7TeV MADGRAPH sample (full statistics, 50pb-1)
  lumiweight.push_back(0.13099599);

  // for current spring10 ttbar(all) 7TeV Mc@Nlo sample (full statistics, 50pb-1)
  lumiweight.push_back(0.00831910);
  // for current spring10 W+jets 7TeV MADGRAPH sample (full statistics, 50pb-1)
  lumiweight.push_back(0.13904207);
  // for current spring10 Z+jets 7TeV MADGRAPH sample (full statistics, 50pb-1)
  lumiweight.push_back(0.14332841);

  // ---
  // do lumiweighting
  // ---

  for(unsigned int idx=kttbarReco; idx<kZjetsGen; ++idx){
    eta_[idx]->Scale(lumiweight[idx]);
    phi_[idx]->Scale(lumiweight[idx]);
    pt_ [idx]->Scale(lumiweight[idx]);
  }

  // ---  
  //    combination of all MC for gen + reco
  // --- 

  TH1F *ptAllReco = (TH1F*)pt_ [kttbarReco]->Clone(); 
  TH1F *etaAllReco= (TH1F*)eta_[kttbarReco]->Clone(); 
  TH1F *phiAllReco= (TH1F*)phi_[kttbarReco]->Clone(); 

  for(unsigned int idx=kttbarReco+1; idx<=kZjetsReco; ++idx){
    ptAllReco ->Add(pt_ [idx]);
    etaAllReco->Add(eta_[idx]);
    phiAllReco->Add(phi_[idx]);
  }

  TH1F *ptAllGen = (TH1F*)pt_ [kttbarGen]->Clone(); 
  TH1F *etaAllGen= (TH1F*)eta_[kttbarGen]->Clone(); 
  TH1F *phiAllGen= (TH1F*)phi_[kttbarGen]->Clone(); 

  for(unsigned int idx=kttbarGen+1; idx<=kZjetsGen; ++idx){
    ptAllGen ->Add(pt_ [idx]);
    etaAllGen->Add(eta_[idx]);
    phiAllGen->Add(phi_[idx]);
  }

  // ---  
  //    print out #events (gen / reco) for all pt bins
  // ---
  std::cout << " # events (gen/reco) within pt(mu) (" << jetMultiplicity << "):" << std::endl;
  for(int idx =2; idx<=ptAllReco->GetNbinsX()+1; idx++){
  std::cout << "bin "  << idx << ": ( " << ptAllGen->GetBinContent(idx) << " / " <<  ptAllReco->GetBinContent(idx) << " )" << std::endl;
  }

  // ---  
  //    calculate efficiency histos
  // ---

  TH1F *ptEff = (TH1F*)ptAllReco  ->Clone();
  ptEff->Divide((TH1F*)ptAllGen   ->Clone()); 
  TH1F *etaEff = (TH1F*)etaAllReco->Clone();
  etaEff->Divide((TH1F*)etaAllGen ->Clone()); 
  TH1F *phiEff = (TH1F*)phiAllReco->Clone();
  phiEff->Divide((TH1F*)phiAllGen ->Clone()); 

  // ---  
  //    print out numbers for efficiency
  // ---

  std::cout << " efficiency within pt(#mu) (" << jetMultiplicity << "):" << std::endl;
  for(int idx =2; idx<=ptEff->GetNbinsX()+1; idx++){
  std::cout << "bin "  << idx << ": " << ptEff->GetBinContent(idx) << std::endl;
  }
  std::cout << " efficiency within eta(#mu) (" << jetMultiplicity << "):" << std::endl;
  for(int idx =2; idx<=etaEff->GetNbinsX()+1; idx++){
  std::cout << "bin "  << idx << ": " << etaEff->GetBinContent(idx) << std::endl;
  }
  std::cout << " efficiency within phi(#mu) (" << jetMultiplicity << "):" << std::endl;
  for(int idx =2; idx<=phiEff->GetNbinsX()+1; idx++){
  std::cout << "bin "  << idx << ": " << phiEff->GetBinContent(idx) << std::endl;
  }

  // ---
  //    division by binwidth to have natural form of spektrum
  // ---

  for(int i=1; i<= ptAllGen->GetNbinsX(); i++){
    ptAllGen ->SetBinContent(i,((double)(ptAllGen ->GetBinContent(i))/(double)(ptAllGen ->GetBinWidth(i)))  );
    ptAllReco->SetBinContent(i,((double)(ptAllReco->GetBinContent(i))/(double)(ptAllReco->GetBinWidth(i)))  );
  }
  for(int i=1; i<= etaAllGen->GetNbinsX(); i++){
    etaAllGen ->SetBinContent(i,((double)(etaAllGen ->GetBinContent(i))/(double)(etaAllGen ->GetBinWidth(i)))  );
    etaAllReco->SetBinContent(i,((double)(etaAllReco->GetBinContent(i))/(double)(etaAllReco->GetBinWidth(i)))  );
  }
  for(int i=1; i<= phiAllGen->GetNbinsX(); i++){
    phiAllGen ->SetBinContent(i,((double)(phiAllGen ->GetBinContent(i))/(double)(phiAllGen ->GetBinWidth(i)))  );
    phiAllReco->SetBinContent(i,((double)(phiAllReco->GetBinContent(i))/(double)(phiAllReco->GetBinWidth(i)))  );
  }
  divideByBinwidth(pt_ );
  divideByBinwidth(eta_);
  divideByBinwidth(phi_);
  
  // ---
  //    create legends 
  // ---

  TString jetMultiplicity3=jetMultiplicity;
  if(jetMultiplicity=="Btag")jetMultiplicity3=jetMultiplicity+", "+jetMultiplicity2;
  // create a legend (in upper right corner) for gen and reco
  TLegend *leg0 = new TLegend(0.19, 0.72, 1.00, 0.94);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("MC (ttbar, W/Z+jets) "+jetMultiplicity3+"+");
  leg0->AddEntry( ptAllGen  , "gen, l+jets selection", "PL");
  leg0->AddEntry( ptAllReco , "reco, semilept. top selection"   , "PL");

  // create a legend (in upper right corner) for efficiency
  TLegend *leg1 = new TLegend(0.21, 0.74, 0.95, 0.94);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("effiency (reco/gen) "+jetMultiplicity3+"+");
  leg1->AddEntry( ptEff  , "p_{t} (#mu)" , "PL");

  // create a legend (in upper right corner) for efficiency
  TLegend *leg2 = new TLegend(0.21, 0.74, 0.95, 0.94);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetHeader("effiency (reco/gen) "+jetMultiplicity3+"+");
  leg2->AddEntry( etaEff , "#eta (#mu)"  , "PL");

  // create a legend (in upper right corner) for efficiency
  TLegend *leg3 = new TLegend(0.21, 0.74, 0.95, 0.94);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  leg3->SetHeader("effiency (reco/gen) "+jetMultiplicity3+"+");
  leg3->AddEntry( phiEff , "#phi (#mu)"  , "PL");

  // create a legend (in upper right corner) for pt(mu)- gen plot
  TLegend *leg4 = new TLegend(0.41, 0.67, 0.99, 0.94);
  leg4->SetFillStyle(0);
  leg4->SetBorderSize(0);
  leg4->SetHeader("gen l+jets MC ("+jetMultiplicity2+"+)");
  leg4->AddEntry( pt_[kttbarGen] , "ttbar (MC@NLO)"  , "F");
  leg4->AddEntry( pt_[kWjetsGen] , "Wjets (Madgraph)", "F");
  leg4->AddEntry( pt_[kZjetsGen] , "Zjets (Madgraph)", "F");

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<=6; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ---
  //    do the printing for ptAll ( gen + reco )
  // ---
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetTitle("ptMuGenAndReco"+jetMultiplicity+"Lum5pb@7TeV");
  axesStyle(*ptAllGen, "p_{t} ( #mu ) [GeV]", "events / GeV", 0.,  getMaximumDependingOnNjetsCut("pt",jetMultiplicity), 0.06, 1.5); 
  histogramStyle(*ptAllGen , kRed  , 1, 20);
  histogramStyle(*ptAllReco, kBlack, 1, 22);
  ptAllGen ->Draw("HIST");
  ptAllReco->Draw("HIST same");
  ptAllReco->Draw("Psame");
  ptAllGen ->Draw("Psame");
  leg0     ->Draw("same");

  // ---
  //    do the printing for etaAll ( gen + reco )
  // ---
  MyCanvas[1]->cd(0);
  MyCanvas[1]->SetTitle("etaMuGenAndReco"+jetMultiplicity+"Lum5pb@7TeV");
  axesStyle(*etaAllGen, "#eta ( #mu )", "events / binwidth", 0.,  getMaximumDependingOnNjetsCut("eta",jetMultiplicity), 0.06, 1.5); 
  histogramStyle(*etaAllGen , kRed  , 1, 20);
  histogramStyle(*etaAllReco, kBlack, 1, 22);
  etaAllGen ->Draw("HIST");
  etaAllReco->Draw("HIST same");
  etaAllReco->Draw("Psame");
  etaAllGen ->Draw("Psame");
  leg0      ->Draw("same");

  // ---
  //    do the printing for phiAll ( gen + reco )
  // ---
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetTitle("phiMuGenAndReco"+jetMultiplicity+"Lum5pb@7TeV");
  axesStyle(*phiAllGen, "#phi ( #mu )", "events / rad", 0.,  getMaximumDependingOnNjetsCut("phi",jetMultiplicity), 0.06, 1.5); 
  histogramStyle(*phiAllGen , kRed  , 1, 20);
  histogramStyle(*phiAllReco, kBlack, 1, 22);
  phiAllGen ->Draw("HIST");
  phiAllReco->Draw("HIST same");
  phiAllReco->Draw("Psame");
  phiAllGen ->Draw("Psame");
  leg0      ->Draw("same");

  // ---
  //    do the printing for pt-effiency ( gen / reco )
  // ---
  MyCanvas[3]->cd(0);
  MyCanvas[3]->SetTitle("ptEfficiencyMCbased"+jetMultiplicity);
  axesStyle(*ptEff, "( p_{t} ( #mu ) [GeV]" , "#epsilon_{ l+jets}", 0.,  1.5); 
  histogramStyle(*ptEff , kRed  , 1, 20);
  ptEff ->Draw("");
  ptEff ->Draw("Psame");
  leg1  ->Draw("same");

  // ---
  //    do the printing for eta-effiency ( gen / reco )
  // ---
  MyCanvas[4]->cd(0);
  MyCanvas[4]->SetTitle("etaEfficiencyMCbased"+jetMultiplicity);
  axesStyle(*etaEff, "#eta ( #mu )" , "#epsilon_{ l+jets}", 0.,  1.3); 
  histogramStyle(*etaEff, kRed, 1, 22);
  etaEff->Draw("");
  etaEff ->Draw("Psame");
  leg2  ->Draw("same");

  // ---
  //    do the printing for phi-effiency ( gen / reco )
  // ---
  MyCanvas[5]->cd(0);
  MyCanvas[5]->SetTitle("phiEfficiencyMCbased"+jetMultiplicity);
  axesStyle(*phiEff, "#phi ( #mu )" , "#epsilon_{ l+jets}", 0.,  1.3); 
  histogramStyle(*phiEff, kRed, 1, 21);
  phiEff->Draw("");
  phiEff->Draw("Psame");
  leg3  ->Draw("same");

  // ---
  //    do the printing for pt-gen composition
  // ---
  MyCanvas[6]->cd(0);
  MyCanvas[6]->SetTitle("ptGenComposition"+jetMultiplicity);
  pt_[kWjetsGen]->Add(pt_[kttbarGen]);
  pt_[kZjetsGen]->Add(pt_[kWjetsGen]);
  axesStyle(*pt_[kZjetsGen], "p_{t} ( #mu ) [GeV]", "events / GeV", 0., getMaximumDependingOnNjetsCut("pt",jetMultiplicity), 0.06, 1.5); 
  histogramStyle(*pt_[kttbarGen], kRed  , 1, 20, 1.5, 1);
  histogramStyle(*pt_[kWjetsGen], kGreen, 1, 20, 1.5, 1);
  histogramStyle(*pt_[kZjetsGen], 6     , 1, 20, 1.5, 1);
  pt_[kZjetsGen]->Draw("");  
  pt_[kWjetsGen]->Draw("same");
  pt_[kttbarGen]->Draw("same");
  leg4  ->Draw("same");

  //  ---
  //  saving
  //  ---
  
  // ps
  MyCanvas[0]->Print("./diffXSecFromSignal/plots/efficiency"+jetMultiplicity+".ps("  );
  for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
    MyCanvas[idx]->Print("./diffXSecFromSignal/plots/efficiency"+jetMultiplicity+".ps"  );   
  }
  MyCanvas[MyCanvas.size()-1]->Print("./diffXSecFromSignal/plots/efficiency"+jetMultiplicity+".ps)"  );
  
  // png
  for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
    MyCanvas[idx]->Print("./diffXSecFromSignal/plots/"+(TString)(MyCanvas[idx]->GetTitle())+".png"  );      
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

void divideByBinwidth(std::vector<TH1F*> histoVector)
{
  // loop over every sample of one histo
  for(unsigned int idx=0; idx<histoVector.size(); idx++){
    // loop over every bin    
    for(int bini=1; bini<= histoVector[idx]->GetNbinsX(); bini++){
      histoVector[idx]->SetBinContent(bini,((double)(histoVector[idx]->GetBinContent(bini))/(double)(histoVector[idx]->GetBinWidth(bini)))  );
    }
  } 
}

double getMaximumDependingOnNjetsCut(TString plot, TString Njets)
{
  // create container for histo max values sortet by plot and Njet
  std::map< TString, std::map <TString,double> > maxValues_;  
  // create maximum values for pt, eta, phi ( for 5pb^-1)
  maxValues_["pt" ]["Btag"  ]= 24.; 
  maxValues_["pt" ]["Njets4"]= 24.;  
  maxValues_["pt" ]["Njets3"]= 65.;
  maxValues_["pt" ]["Njets2"]= 320.;
  maxValues_["pt" ]["Njets1"]= 1800.;
  maxValues_["eta"]["Btag"  ]= 400.;  
  maxValues_["eta"]["Njets4"]= 400.;  
  maxValues_["eta"]["Njets3"]= 1100.;
  maxValues_["eta"]["Njets2"]= 4500.;
  maxValues_["eta"]["Njets1"]= 23000.;
  maxValues_["phi"]["Btag"  ]= 260.; 
  maxValues_["phi"]["Njets4"]= 260.;  
  maxValues_["phi"]["Njets3"]= 700.;
  maxValues_["phi"]["Njets2"]= 2500.;
  maxValues_["phi"]["Njets1"]= 14000.;
  // get maximum value
  return maxValues_.find(plot)->second.find(Njets)->second;
}
