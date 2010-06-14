// ---------description---------------------------------
// -----------------------------------------------------
// this Makro determines the inclusive and differential, 
// normalized cross section ( d#sigma/dpt(#mu)/#sigma )
// for pt, eta and phi (of the muon). Additionally, it
// distinguishes between the charge of the muon.
// -----------------------------------------------------

#include <vector>
#include <map>
#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>

enum styles {kttbarReco, kWjetsReco, kZjetsReco, kttbarGen, kWjetsGen};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
TH1F* divideByBinwidth(TH1F* histo);
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

  // choose jet multiplicity you want to see: "Njets1" / "Njets2" / "Njets3" / "Njets4" 
  TString jetMultiplicity ="Njets4";
  // choose whether you want to save every plot as png and all within one ps file
  bool save = true;
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/effiency/";
  // choose luminosity for scaling of event numbers and for legend as entry
  int luminosity = 50;
  TString lum = "50";
  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/spring10Samples/spring10SelV2Sync";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecAllTtbarMcAtNloSpring10.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecWjetsMadSpring10.root"        ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecZjetsMadSpring10.root"        ) );

  // ---
  //    get histograms
  // ---
  // create jet multiplicity indicator
  std::vector<TString> Njets_;
  Njets_.push_back("Njets1");
  Njets_.push_back("Njets2");
  Njets_.push_back("Njets3");
  Njets_.push_back("Njets4");
  Njets_.push_back("Njets4Btag");
  Njets_.push_back("Njets3Btag");
  // create container for all histos
  std::map< TString, std::map <unsigned int, std::map <TString, TH1F*> > > histo_;
  // loop jet multiplicities
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // get reco plots
    for(unsigned int idx=kttbarReco; idx<=kZjetsReco; ++idx) {
      histo_["eta"][idx][Njets_[mult]] = (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/eta" );
      histo_["pt" ][idx][Njets_[mult]] = (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/pt"  );
      histo_["phi"][idx][Njets_[mult]] = (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+Njets_[mult]+"/phi" );
    }
    // get gen plots
    unsigned int multgen = mult;
    // take into account that there are no btag - gen plots
    if(multgen==Njets_.size()-2) multgen=mult-1;
    if(multgen==Njets_.size()-1) multgen=mult-3;
    // -3 because plots are within the same rootfile
    for(unsigned int idx=kttbarGen; idx<=kWjetsGen; ++idx) {
      histo_["eta"][idx][Njets_[mult]] = (TH1F*)(files_[idx-3]->Get("analyzeTightMuonCrossSectionGen"+Njets_[multgen]+"/eta")->Clone());
      histo_["pt" ][idx][Njets_[mult]] = (TH1F*)(files_[idx-3]->Get("analyzeTightMuonCrossSectionGen"+Njets_[multgen]+"/pt" )->Clone());
      histo_["phi"][idx][Njets_[mult]] = (TH1F*)(files_[idx-3]->Get("analyzeTightMuonCrossSectionGen"+Njets_[multgen]+"/phi")->Clone());
    }
  }

  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;
  // for current spring10 7TeV Mc@Nlo sample (50pb-1)
  // a) Reco
  // ttbar(all) Mc@Nlo sample 
  lumiweight.push_back(0.00831910/50.0*(double)luminosity);
  // W+jets MADGRAPH sample
  lumiweight.push_back(0.13904207/50.0*(double)luminosity);
  // Z+jets MADGRAPH sample
  lumiweight.push_back(0.14332841/50.0*(double)luminosity);
  // b) Gen
  // ttbar(all) Mc@Nlo sample 
  lumiweight.push_back(0.00831910/50.0*(double)luminosity);
  // W+jets MADGRAPH sample
  lumiweight.push_back(0.13904207/50.0*(double)luminosity);

//   std::cout << "lumifactors:" << std::endl;
//   for(int idx=kttbarReco; idx<=kWjetsGen; ++idx){
//     std::cout << lumiweight[idx] << std::endl;
//   }
  std::cout << "" << std::endl;
  std::cout << " before weighting: ttbar pt-(reco/gen) Njets4, bin3: " << histo_["pt" ][kttbarReco][Njets_[3]]->GetBinContent(3) << " / " << histo_["pt" ][kttbarGen][Njets_[3]]->GetBinContent(3) << std::endl;
  std::cout << "" << std::endl;

  // ---
  // do lumiweighting for reco and gen plots
  // ---
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    for(int idx=kttbarReco; idx<=kWjetsGen; ++idx){
      if(mult==3&&idx==kttbarGen){std::cout << histo_["pt"][kttbarGen][Njets_[mult]]->GetBinContent(3) << " * " << lumiweight[idx] << " = ";}
      histo_["pt" ][idx][Njets_[mult]]->Scale(lumiweight[idx]);
      histo_["eta"][idx][Njets_[mult]]->Scale(lumiweight[idx]);
      histo_["phi"][idx][Njets_[mult]]->Scale(lumiweight[idx]);
      if(mult==3&&idx==kttbarGen){std::cout << histo_["pt"][kttbarGen][Njets_[mult]]->GetBinContent(3) << std::endl;}
    }
  }
  std::cout << "" << std::endl;
  std::cout << " after weighting: ttbar pt-(reco/gen) Njets4, bin3: " << histo_["pt" ][kttbarReco][Njets_[3]]->GetBinContent(3) << " / " << histo_["pt" ][kttbarGen][Njets_[3]]->GetBinContent(3) << std::endl;
  std::cout << "" << std::endl;

  // ---  
  //    combination of all MC for gen + reco
  // --- 
  unsigned int allReco = 42;
  unsigned int allGen  = 42*42;
  // create separate histos
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    histo_["pt" ][allReco][Njets_[mult]] = (TH1F*)histo_["pt" ][kttbarReco][Njets_[mult]]->Clone(); 
    histo_["eta"][allReco][Njets_[mult]] = (TH1F*)histo_["eta"][kttbarReco][Njets_[mult]]->Clone(); 
    histo_["phi"][allReco][Njets_[mult]] = (TH1F*)histo_["phi"][kttbarReco][Njets_[mult]]->Clone();
    histo_["pt" ][allGen ][Njets_[mult]] = (TH1F*)histo_["pt" ][kttbarGen ][Njets_[mult]]->Clone(); 
    histo_["eta"][allGen ][Njets_[mult]] = (TH1F*)histo_["eta"][kttbarGen ][Njets_[mult]]->Clone(); 
    histo_["phi"][allGen ][Njets_[mult]] = (TH1F*)histo_["phi"][kttbarGen ][Njets_[mult]]->Clone();
  }

  // add all histos
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    // reco    
    for(unsigned int idx=kttbarReco+1; idx<=kZjetsReco; ++idx){
      histo_["pt" ][allReco][Njets_[mult]]->Add( (TH1F*)histo_["pt" ][idx][Njets_[mult]]->Clone());
      histo_["eta"][allReco][Njets_[mult]]->Add( (TH1F*)histo_["eta"][idx][Njets_[mult]]->Clone());
      histo_["phi"][allReco][Njets_[mult]]->Add( (TH1F*)histo_["phi"][idx][Njets_[mult]]->Clone());
    }
    // gen
    for(unsigned int idx=kttbarGen+1; idx<=kWjetsGen; ++idx){
      histo_["pt" ][allGen][Njets_[mult]]->Add( (TH1F*)histo_["pt" ][idx][Njets_[mult]]->Clone());
      histo_["eta"][allGen][Njets_[mult]]->Add( (TH1F*)histo_["eta"][idx][Njets_[mult]]->Clone());
      histo_["phi"][allGen][Njets_[mult]]->Add( (TH1F*)histo_["phi"][idx][Njets_[mult]]->Clone());
    }
  }
  
  // ---  
  //    print out #events (gen / reco) for all pt bins and jet multiplicities
  // ---
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    std::cout << " # events (gen/reco) within pt(mu) (" << Njets_[mult] << "):" << std::endl;
    for(int idx =2; idx<=histo_["pt" ][allReco][Njets_[mult]]->GetNbinsX()+1; idx++){
      std::cout << "bin "  << idx << ": ( " << histo_["pt"][allGen][Njets_[mult]]->GetBinContent(idx) << " / " <<  histo_["pt"][allReco][Njets_[mult]]->GetBinContent(idx) << " )" << std::endl;
    }
  }
  
  // ---  
  //    calculate efficiency histos
  // ---
  unsigned int eff = 566;
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
  histo_["pt" ][eff][Njets_[mult]]= (TH1F*)histo_["pt" ][allReco][Njets_[mult]]->Clone();
  histo_["pt" ][eff][Njets_[mult]]->Divide((TH1F*)histo_["pt" ][allGen ][Njets_[mult]]->Clone()); 
  histo_["eta"][eff][Njets_[mult]]= (TH1F*)histo_["eta"][allReco][Njets_[mult]]->Clone();
  histo_["eta"][eff][Njets_[mult]]->Divide((TH1F*)histo_["eta"][allGen ][Njets_[mult]]->Clone()); 
  histo_["phi"][eff][Njets_[mult]]= (TH1F*)histo_["phi"][allReco][Njets_[mult]]->Clone();
  histo_["phi"][eff][Njets_[mult]]->Divide((TH1F*)histo_["phi"][allGen ][Njets_[mult]]->Clone()); 
  }

  // ---  
  //    print out numbers for efficiency
  // ---

  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    std::cout << " efficiency within pt(mu) (" << Njets_[mult] << "):" << std::endl;
    for(int idx =2; idx<=histo_["pt"][eff][Njets_[mult]]->GetNbinsX()+1; idx++){
      std::cout << "bin "  << idx << ": " << histo_["pt"][eff][Njets_[mult]]->GetBinContent(idx) << std::endl;
    }
    std::cout << " efficiency within eta(mu) (" << Njets_[mult] << "):" << std::endl;
    for(int idx =2; idx<=histo_["eta"][eff][Njets_[mult]]->GetNbinsX()+1; idx++){
      std::cout << "bin "  << idx << ": " << histo_["eta"][eff][Njets_[mult]]->GetBinContent(idx) << std::endl;
    }
    std::cout << " efficiency within phi(mu) (" << Njets_[mult] << "):" << std::endl;
    for(int idx =2; idx<=histo_["phi"][eff][Njets_[mult]]->GetNbinsX()+1; idx++){
      std::cout << "bin "  << idx << ": " << histo_["phi"][eff][Njets_[mult]]->GetBinContent(idx) << std::endl;
    }
  }

  // ---
  //    division by binwidth to have natural form of spektrum for all histos
  // ---
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    divideByBinwidth( histo_["pt" ][allGen ][Njets_[mult]]);
    divideByBinwidth( histo_["eta"][allGen ][Njets_[mult]]); 
    divideByBinwidth( histo_["phi"][allGen ][Njets_[mult]]);
    divideByBinwidth( histo_["pt" ][allReco][Njets_[mult]]);
    divideByBinwidth( histo_["eta"][allReco][Njets_[mult]]); 
    divideByBinwidth( histo_["phi"][allReco][Njets_[mult]]);

    for(unsigned int idx=kttbarReco; idx<=kWjetsGen; ++idx) {
      divideByBinwidth( histo_["pt" ][idx][Njets_[mult]]);
      divideByBinwidth( histo_["eta"][idx][Njets_[mult]]); 
      divideByBinwidth( histo_["phi"][idx][Njets_[mult]]);
    }
  }

  // ---
  //    set plot style for effiency plots
  // ---
  std::vector<int> color_;
  color_ .push_back(kRed);
  color_ .push_back(6);
  color_ .push_back(kBlue);
  color_ .push_back(kBlack);
  color_ .push_back(kGreen);
  color_ .push_back(14);
  std::vector<int> marker_;
  marker_ .push_back(20);
  marker_ .push_back(21);
  marker_ .push_back(23);
  marker_ .push_back(22);
  marker_ .push_back(29);
  marker_ .push_back(29);
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    histogramStyle(*histo_["pt" ][eff][Njets_[mult]] , color_[mult]  , 1, marker_[mult]);
    histogramStyle(*histo_["eta"][eff][Njets_[mult]] , color_[mult]  , 1, marker_[mult]);
    histogramStyle(*histo_["phi"][eff][Njets_[mult]] , color_[mult]  , 1, marker_[mult]);
  }

  // ---
  //    create legends 
  // ---

  // create a legend (in upper right corner) for gen and reco
  TLegend *leg0 = new TLegend(0.24, 0.72, 0.98, 0.93);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("MC ("+lum+"pb^{-1}, "+jetMultiplicity+"+)");
  leg0->AddEntry( histo_["pt"][allGen ][jetMultiplicity], "gen, #mu+jets selection, (t#bar{t} & W)"         , "PL");
  leg0->AddEntry( histo_["pt"][allReco][jetMultiplicity], "reco, semilept.(#mu) selection (t#bar{t}, W & Z)", "PL");

  // create a legend (in upper right corner) for efficiency (ptMu) - all jet multiplicities
  //  TLegend *leg1 = new TLegend(0.22, 0.67, 1.00, 1.00);
  TLegend *leg1 = new TLegend(0.46, 0.62, 1.00, 0.95);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  //  leg1->SetHeader("#epsilon(p_{t}(#mu)) for different jet multiplicities");
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    leg1->AddEntry( histo_["pt"][eff][Njets_[mult]], Njets_[mult]+"+" , "PL");
  }
  // create a legend (in upper right corner) for efficiency (etaMu) - all jet multiplicities
  TLegend *leg2 = new TLegend(0.46, 0.62, 1.00, 0.95);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  //  leg2->SetHeader("#epsilon(#eta(#mu)) for different jet multiplicities");
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    leg2->AddEntry( histo_["eta"][eff][Njets_[mult]], Njets_[mult]+"+" , "PL");
  }
  // create a legend (in upper right corner) for efficiency (phiMu) - all jet multiplicities
  TLegend *leg3 = new TLegend(0.46, 0.62, 1.00, 0.95);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  //  leg3->SetHeader("#epsilon(#phi(#mu)) for different jet multiplicities");
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    leg3->AddEntry( histo_["phi"][eff][Njets_[mult]], Njets_[mult]+"+" , "PL");
  }
  // create a legend (in upper right corner) for pt(mu)- gen plot
  TString jetMultiplicity2=jetMultiplicity;
  if(jetMultiplicity=="Njets4Btag") jetMultiplicity2="Njets4";
  if(jetMultiplicity=="Njets3Btag") jetMultiplicity2="Njets3";
  TLegend *leg4 = new TLegend(0.41, 0.67, 0.99, 0.94);
  leg4->SetFillStyle(0);
  leg4->SetBorderSize(0);
  leg4->SetHeader("gen: #mu+jets ("+lum+" pb^{-1}, "+jetMultiplicity2+"+)" );
  leg4->AddEntry( histo_["pt"][kttbarGen][jetMultiplicity] , "ttbar (MC@NLO)"  , "F");
  leg4->AddEntry( histo_["pt"][kWjetsGen][jetMultiplicity] , "Wjets (Madgraph)", "F");

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
  //    do the printing for inclusive pt ( gen + reco )
  // ---
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetTitle("ptMuGenAndReco"+jetMultiplicity+"Lum5pb@7TeV");
  axesStyle(*histo_["pt"][allGen][jetMultiplicity], "p_{t} ( #mu ) [GeV]", "events / GeV", 0.,  getMaximumDependingOnNjetsCut("pt",jetMultiplicity), 0.06, 1.5); 
  histogramStyle(*histo_["pt"][allGen ][jetMultiplicity] , kRed  , 1, 20);
  histogramStyle(*histo_["pt"][allReco][jetMultiplicity] , kBlack, 1, 22);
  histo_["pt"][allGen ][jetMultiplicity]->Draw("HIST");
  histo_["pt"][allReco][jetMultiplicity]->Draw("HIST same");
  histo_["pt"][allReco][jetMultiplicity]->Draw("Psame");
  histo_["pt"][allGen ][jetMultiplicity]->Draw("Psame");
  leg0->Draw("same");

  // ---
  //    do the printing for inclusive eta ( gen + reco )
  // ---
  MyCanvas[1]->cd(0);
  MyCanvas[1]->SetTitle("etaMuGenAndReco"+jetMultiplicity+"Lum5pb@7TeV");
  axesStyle(*histo_["eta" ][allGen][jetMultiplicity], "#eta ( #mu )", "events / binwidth", 0.,  getMaximumDependingOnNjetsCut("eta",jetMultiplicity), 0.06, 1.5); 
  histogramStyle(*histo_["eta"][allGen ][jetMultiplicity] , kRed  , 1, 20);
  histogramStyle(*histo_["eta"][allReco][jetMultiplicity] , kBlack, 1, 22);
  histo_["eta"][allGen ][jetMultiplicity]->Draw("HIST");
  histo_["eta"][allReco][jetMultiplicity]->Draw("HIST same");
  histo_["eta"][allReco][jetMultiplicity]->Draw("Psame");
  histo_["eta"][allGen ][jetMultiplicity]->Draw("Psame");
  //  leg0->Draw("same");

  // ---
  //    do the printing for inclusive phi ( gen + reco )
  // ---
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetTitle("phiMuGenAndReco"+jetMultiplicity+"Lum5pb@7TeV");
  axesStyle(*histo_["phi"][allGen][jetMultiplicity], "#phi ( #mu )", "events / rad", 0.,  getMaximumDependingOnNjetsCut("phi",jetMultiplicity), 0.06, 1.5); 
  histogramStyle(*histo_["phi"][allGen ][jetMultiplicity] , kRed  , 1, 20);
  histogramStyle(*histo_["phi"][allReco][jetMultiplicity] , kBlack, 1, 22);
  histo_["phi"][allGen ][jetMultiplicity]->Draw("HIST");
  histo_["phi"][allReco][jetMultiplicity]->Draw("HIST same");
  histo_["phi"][allReco][jetMultiplicity]->Draw("Psame");
  histo_["phi"][allGen ][jetMultiplicity]->Draw("Psame");
  //  leg0->Draw("same");

  // ---
  //    do the printing for pt-effiency ( gen / reco ) for all jet multiplicities
  // ---
  MyCanvas[3]->cd(0);
  MyCanvas[3]->SetGrid(1,1);
  MyCanvas[3]->SetTitle("ptEfficiencyMCbasedAllJetMultiplicities");
  axesStyle(*histo_["pt" ][eff][Njets_[0]], "p_{t} ( #mu ) [GeV]" , "#epsilon_{ l+jets}", 0.,  1.8); 
  histo_["pt"][eff][Njets_[0]] ->Draw("");
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
  histo_["pt"][eff][Njets_[mult]]->Draw("same");
  histo_["pt"][eff][Njets_[mult]]->Draw("Psame");
  }
  leg1  ->Draw("same");

  // ---
  //    do the printing for eta-effiency ( gen / reco ) for all jet multiplicities
  // ---
  MyCanvas[4]->cd(0);
  MyCanvas[4]->SetGrid(1,1);
  MyCanvas[4]->SetTitle("etaEfficiencyMCbasedAllJetMultiplicities");
  axesStyle(*histo_["eta" ][eff][Njets_[0]], "#eta ( #mu )" , "#epsilon_{ l+jets}", 0.,  1.8); 
  histo_["eta"][eff][Njets_[0]]->Draw("");
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    histo_["eta"][eff][Njets_[mult]]->Draw("same");
    histo_["eta"][eff][Njets_[mult]]->Draw("Psame");
  }
  leg2  ->Draw("same");

  // ---
  //    do the printing for phi-effiency ( gen / reco ) for all jet multiplicities
  // ---
  MyCanvas[5]->cd(0);
  MyCanvas[5]->SetGrid(1,1);
  MyCanvas[5]->SetTitle("phiEfficiencyMCbasedAllJetMultiplicities");
  axesStyle(*histo_["phi"][eff][Njets_[0]], "#phi ( #mu )" , "#epsilon_{ l+jets}", 0.,  1.8); 
  histo_["phi"][eff][Njets_[0]]->Draw("");
  for(unsigned int mult=0; mult<Njets_.size(); ++mult){
    histo_["phi"][eff][Njets_[mult]]->Draw("same");
    histo_["phi"][eff][Njets_[mult]]->Draw("Psame");
  }
  leg3  ->Draw("same");

  // ---
  //    do the printing for pt-gen composition
  // ---
  MyCanvas[6]->cd(0);
  MyCanvas[6]->SetTitle("ptGenComposition"+jetMultiplicity);
  histo_["pt"][kWjetsGen][jetMultiplicity]->Add(histo_["pt"][kttbarGen][jetMultiplicity]);
  axesStyle(*histo_["pt"][kWjetsGen][jetMultiplicity], "p_{t} ( #mu ) [GeV]", "events / GeV", 0., getMaximumDependingOnNjetsCut("pt",jetMultiplicity), 0.06, 1.5); 
  histogramStyle(*histo_["pt"][kWjetsGen][jetMultiplicity], kGreen, 1, 20, 1.5, 1);
  histogramStyle(*histo_["pt"][kttbarGen][jetMultiplicity], kRed  , 1, 20, 1.5, 1);
  histo_["pt"][kWjetsGen][jetMultiplicity]->Draw("");
  histo_["pt"][kttbarGen][jetMultiplicity]->Draw("same");
  leg4  ->Draw("same");

  //  ---
  //  saving
  //  ---
  if(save){  
    // ps
    MyCanvas[0]->Print(saveTo+"efficiency"+jetMultiplicity+".ps(");
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+"efficiency"+jetMultiplicity+".ps"  );   
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+"efficiency"+jetMultiplicity+".ps)"  );
  
    // png
    for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
      MyCanvas[idx]->Print(saveTo+(TString)(MyCanvas[idx]->GetTitle())+".png"  );      
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

TH1F* divideByBinwidth(TH1F* histo)
{
  // create output histo
  TH1F* output = (TH1F*)histo->Clone();
  // loop over bins    
  for(int bini=1; bini<= output->GetNbinsX(); bini++){
    output->SetBinContent(bini,((double)(output->GetBinContent(bini))/(double)(output->GetBinWidth(bini)))  );   
  } 
  return output;
}

double getMaximumDependingOnNjetsCut(TString plot, TString Njets)
{
  // create container for histo max values sortet by plot and Njet
  std::map< TString, std::map <TString,double> > maxValues_;  
  // create maximum values for pt, eta, phi ( for 5pb^-1)
  maxValues_["pt" ]["Njets4Btag"]= 40.; 
  maxValues_["pt" ]["Njets3Btag"]= 100.; 
  maxValues_["pt" ]["Njets4"]= 500.;  
  maxValues_["pt" ]["Njets3"]= 1000.;
  maxValues_["pt" ]["Njets2"]= 3200.;
  maxValues_["pt" ]["Njets1"]= 18000.;
  maxValues_["eta"]["Njets4Btag"]= 650.;  
  maxValues_["eta"]["Njets3Btag"]= 1500.; 
  maxValues_["eta"]["Njets4"]= 650.;  
  maxValues_["eta"]["Njets3"]= 1500.;
  maxValues_["eta"]["Njets2"]= 4500.;
  maxValues_["eta"]["Njets1"]= 23000.;
  maxValues_["phi"]["Njets4Btag"]= 400.;
  maxValues_["phi"]["Njets3Btag"]= 1000.; 
  maxValues_["phi"]["Njets4"]= 400.;  
  maxValues_["phi"]["Njets3"]= 1000.;
  maxValues_["phi"]["Njets2"]= 2500.;
  maxValues_["phi"]["Njets1"]= 14000.;
  // get maximum value
  return maxValues_.find(plot)->second.find(Njets)->second;
}
