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

enum styles {kSig, kPseudo, kBkg, kWjets, kZjets, kQCD, kLepJets};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void divideByBinwidth(std::vector<TH1F*> histoVector);
double getMaximumDependingOnNjetsCut(TString plot, TString Njets);

void analyzeMuonDiffXSec()
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
  TString jetMultiplicity ="Njets4";

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecSigMcAtNlo7TeV.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal/pseudoData7TeV5pb.root"         ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecBkgMcAtNlo7TeV.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecWjetsMadgraph7TeV.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecZjetsMadgraph7TeV.root" ) );
  files_.push_back(new TFile("./diffXSecFromSignal/diffXSecQCDPythia7TeV.root"     ) );
  // summer09Samples/summer09SamplesNjets3ptBins0704/

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> eta_, phi_, pt_;

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    eta_   .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/eta" ) );
    pt_    .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/pt"  ) );
    phi_   .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRec"+jetMultiplicity+"/phi" ) );
  }

  // get total number of FILLED bins above cut value of 20 GeV from pt histo
  int totalBinNumber = (pt_[kSig]->GetNbinsX())-1;
  std::cout << "total bin number between 20 and 200 GeV: " << totalBinNumber << std::endl;

  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;

  // for current ttbar(lept.mu on gen level) 7TeV Mc@Nlo sample (full statistics, 5pb-1)
  lumiweight.push_back(0.00083);
  // pseudo data
  lumiweight.push_back(1.0);
  // for current ttbar(non lept.mu on gen level) 7TeV Mc@Nlo sample (full statistics, 5pb-1)
  lumiweight.push_back(0.00083);
  // for current W+jets 7TeV MADGRAPH sample (full statistics, 5pb-1)
  lumiweight.push_back(0.01231);
  // for current Z+jets 7TeV MADGRAPH sample (full statistics, 5pb-1)
  lumiweight.push_back(0.01310);
  // for current QCD 7TeV PYTHIA sample (full statistics, 5pb-1)
  lumiweight.push_back(0.10286);

  // ---
  // do lumiweighting
  // ---

  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    eta_[idx]->Scale(lumiweight[idx]);
    phi_[idx]->Scale(lumiweight[idx]);
    pt_ [idx]->Scale(lumiweight[idx]);
  }
 
  // ---  
  //    combine MC to get isolated Lepton + jet MC (no QCD)
  // --- 
  pt_  .push_back((TH1F*)(pt_ [kSig]->Clone()));
  eta_ .push_back((TH1F*)(eta_[kSig]->Clone()));
  phi_ .push_back((TH1F*)(phi_[kSig]->Clone()));
  for(int idx=kBkg; idx<=kZjets; idx++){
    pt_[kLepJets]->Add(pt_[idx]);
    eta_[kLepJets]->Add(eta_[idx]);
    phi_[kLepJets]->Add(phi_[idx]);
  }

  // ---  
  //    clone plots with weighted event numbers
  // ---  
  std::vector<TH1F*> etaEventNumbers_, phiEventNumbers_, ptEventNumbers_;
  
  for(unsigned int idx=0; idx<=files_.size(); ++idx) {
    etaEventNumbers_.push_back( (TH1F*)(eta_[idx]->Clone()) );
    phiEventNumbers_.push_back( (TH1F*)(phi_[idx]->Clone()) );
    ptEventNumbers_.push_back ( (TH1F*)(pt_ [idx]->Clone()) );
  }

  // ---  
  //    print out weighted event numbers for all files
  // ---

  std::vector<double> eventNumbersPt_, eventNumbersEta_, eventNumbersPhi_;

  for(unsigned int idx=0; idx<=files_.size(); ++idx) {
    eventNumbersPt_.push_back ( pt_ [idx]->Integral() );
    eventNumbersEta_.push_back( eta_[idx]->Integral() );
    eventNumbersPhi_.push_back( phi_[idx]->Integral() );
    if(idx<files_.size()){
      //    std::cout << "total weighted # of events in pt (file "  << idx << "): " << eventNumbersPt_[idx]  << std::endl;
      //    std::cout << "total weighted # of events in eta (file " << idx << "): " << eventNumbersEta_[idx] << std::endl;
      //    std::cout << "total weighted # of events in phi (file " << idx << "): " << eventNumbersPhi_[idx] << std::endl;
    }
  }
  std::cout << "S/B for top (" << jetMultiplicity << "):"  << (eventNumbersPt_[0]+eventNumbersPt_[2])/(eventNumbersPt_[3]+eventNumbersPt_[4]+eventNumbersPt_[5])  << std::endl;
 std::cout << "S/B for l+jet (" << jetMultiplicity << "):" << (eventNumbersPt_[0]+eventNumbersPt_[2]+eventNumbersPt_[3]+eventNumbersPt_[4])/(eventNumbersPt_[5])  << std::endl;

  // ---
  //    print out # of events (weighted) for each bin (including overflow) with statistical errors
  // ---
  std::cout << "-------------------------------------------------" << std::endl;
  std::cout << "---------------event composition-----------------" << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;

  std::cout << "-------pt distribution, ttbar signal only-------" << std::endl;
  for(int i=2; i<= pt_[kSig]->GetNbinsX()+1; i++){
    std::cout << "(weighted) # events pt-bin "<< i << ": " <<  ptEventNumbers_[kSig]->GetBinContent(i) << " +/- " << sqrt( (double)(ptEventNumbers_[kSig]->GetBinContent(i)) ) << std::endl;
  }
  std::cout << "total # events: " << eventNumbersPt_[kSig] << std::endl;

  std::cout << "-------pt distribution, ttbar other only-------" << std::endl;
  for(int i=2; i<= pt_[kSig]->GetNbinsX()+1; i++){
    std::cout << "(weighted) # events pt-bin "<< i << ": " <<  ptEventNumbers_[kBkg]->GetBinContent(i) << " +/- " << sqrt( (double)(ptEventNumbers_[kBkg]->GetBinContent(i)) ) << std::endl;
  }
  std::cout << "total # events: " << eventNumbersPt_[kBkg] << std::endl;

  std::cout << "-------pt distribution, W+jets only-------" << std::endl;
  for(int i=2; i<= pt_[kSig]->GetNbinsX()+1; i++){
    std::cout << "(weighted) # events pt-bin "<< i << ": " <<  ptEventNumbers_[kWjets]->GetBinContent(i) << " +/- " << sqrt( (double)(ptEventNumbers_[kWjets]->GetBinContent(i)) ) << std::endl;
  }
  std::cout << "total # events: " << eventNumbersPt_[kWjets] << std::endl;

  std::cout << "-------pt distribution, Z+jets only-------" << std::endl;
  for(int i=2; i<= pt_[kSig]->GetNbinsX()+1; i++){
    std::cout << "(weighted) # events pt-bin "<< i << ": " <<  ptEventNumbers_[kZjets]->GetBinContent(i) << " +/- " << sqrt( (double)(ptEventNumbers_[kZjets]->GetBinContent(i)) ) << std::endl;
  }
  std::cout << "total # events: " << eventNumbersPt_[kZjets] << std::endl;

  std::cout << "-------pt distribution, QCD only-------" << std::endl;
  for(int i=2; i<= pt_[kSig]->GetNbinsX()+1; i++){
    std::cout << "(weighted) # events pt-bin "<< i << ": " <<  ptEventNumbers_[kQCD]->GetBinContent(i) << " +/- " << sqrt( (double)(ptEventNumbers_[kQCD]->GetBinContent(i)) ) << std::endl;
  }
  std::cout << "total # events: " << eventNumbersPt_[kQCD] << std::endl;

  std::cout << "-------pt distribution, pseudo data-------" << std::endl;
  for(int i=2; i<= pt_[kSig]->GetNbinsX()+1; i++){
    std::cout << "(weighted) # events pt-bin "<< i << ": " <<  ptEventNumbers_[kPseudo]->GetBinContent(i) << " +/- " << sqrt( (double)(ptEventNumbers_[kPseudo]->GetBinContent(i)) ) << std::endl;
  }
  std::cout << "total # events: " << eventNumbersPt_[kPseudo] << std::endl;
  std::cout << "for comparism- total # of MC events: " << eventNumbersPt_[kSig]+eventNumbersPt_[kBkg]+eventNumbersPt_[kWjets]+eventNumbersPt_[kZjets]+eventNumbersPt_[kQCD] << std::endl;

  // ---
  //    do scaling with respect to inclusive cross section (taken from same histogram)
  // ---  
  for(unsigned int idx=0; idx<=files_.size(); ++idx) {
    pt_  [idx]->Scale(1/eventNumbersPt_ [idx]);
    eta_ [idx]->Scale(1/eventNumbersEta_[idx]);
    phi_ [idx]->Scale(1/eventNumbersPhi_[idx]);
  }

  // ---
  //    division by binwidth
  // ---

  for(unsigned int idx=0; idx<=files_.size(); ++idx) {

    for(int i=1; i<= pt_[idx]->GetNbinsX(); i++){
      pt_[idx]->SetBinContent(i,((double)(pt_[idx]->GetBinContent(i))/(double)(pt_[idx]->GetBinWidth(i)))  );
    }
    for(int i=1; i<= phi_[idx]->GetNbinsX(); i++){
      phi_[idx]->SetBinContent(i,((double)(phi_[idx]->GetBinContent(i))/(double)(phi_[idx]->GetBinWidth(i)))  );
    }
    for(int i=1; i<= eta_[idx]->GetNbinsX(); i++){
      eta_[idx]->SetBinContent(i,((double)(eta_[idx]->GetBinContent(i))/(double)(eta_[idx]->GetBinWidth(i)))  );
    }
  }

  // ---
  //    calculate statistical errors for differential xSec (pt plots only) via gaussian error calculus
  // ---

  std::vector<double> ptDiffXPseudoError_;  
  std::vector<double> ptDiffXSGError_;  

  for(unsigned int idx=kSig; idx<=kPseudo; idx++){
  // i: calculation for each bin (starting with filled bin which is the 2nd)
    for(int i =2; i<=totalBinNumber+1; i++){
      double result=0.;
      // calculate shortcut expression needed in final formula
      double errorHelperA=0;  
      errorHelperA= ( (double)(pt_[idx]->GetBinWidth(i)) * eventNumbersPt_[idx] ); 
      // final formula
      result = sqrt(  ((double)(ptEventNumbers_ [idx]->GetBinContent(i)) / errorHelperA / errorHelperA) * ( 1.0 - 2.0 * (double)(pt_[idx]->GetBinWidth(i)) / errorHelperA + ( (double)(ptEventNumbers_ [idx]->GetBinContent(i)) * (double)(pt_[idx]->GetBinWidth(i)) * (double)(pt_[idx]->GetBinWidth(i)) * (eventNumbersPt_[idx])  / errorHelperA / errorHelperA) )  );      
      if(idx==kSig){
	ptDiffXSGError_.push_back(result);
	  }
      if(idx==kPseudo){
	ptDiffXPseudoError_.push_back(result);
	  }
    }
  }
  
  // ---
  //    print out diffXValue(pt) for each bin with statistical errors
  // ---
  std::cout << "-------signal only-------" << std::endl;
  for(int i=2; i<= pt_[kSig]->GetNbinsX(); i++){
    std::cout << "(d#sigma)/(dpt(muon) * #sigma) pt-bin "<< i << ": " <<  pt_[kSig]->GetBinContent(i) << " +/- " <<  ptDiffXSGError_[i-2] << std::endl;
  }
  std::cout << "-------pseudo data-------" << std::endl;
  for(int i=2; i<= pt_[kPseudo]->GetNbinsX(); i++){
    std::cout << "(d#sigma)/(dpt(muon) * #sigma) pt-bin "<< i << ": " <<  pt_[kPseudo]->GetBinContent(i) << " +/- " <<  ptDiffXPseudoError_[i-2] << std::endl;
  }

  // ---
  //    divide plots with event numbers by binwidth to have natural form of spektrum
  // ---  

  divideByBinwidth(ptEventNumbers_ );
  divideByBinwidth(etaEventNumbers_);
  divideByBinwidth(phiEventNumbers_);

  // ---
  //    create legends 
  // ---
  
  TString btagJetcutInfo = "";
  // create a legend (in upper right corner) for all MC samples and pseudo data
  TLegend *leg0 = new TLegend(0.21, 0.74, 0.95, 0.94);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  if(jetMultiplicity =="Btag")btagJetcutInfo ="Njets>=4";
  leg0->SetHeader("MC (7TeV @ 5pb^{-1}) , full selection, "+jetMultiplicity+"+"+btagJetcutInfo);
  leg0->AddEntry( pt_[kSig]    , "ttbar MC@NLO semi-lep.( #mu )" , "PL");
  leg0->AddEntry( pt_[kLepJets], "all lepton+jets MC"            , "PL");
  leg0->AddEntry( pt_[kPseudo] , "pseudo data from all MC"       , "P" );
  leg0->AddEntry( pt_[kPseudo] , "(ttbar + Wjets + Zjets + QCD)" , ""  );

  // create a legend (in upper right corner) for all MC samples and pseudo data
  TLegend *leg1 = new TLegend(0.21, 0.66, 1.0, 0.95);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("MC (7TeV @ 5pb^{-1}) , full selection, "+jetMultiplicity+"+"+btagJetcutInfo);
  leg1->AddEntry( ptEventNumbers_[kSig], "ttbar MC@NLO semi-lep.( #mu )"    , "F");
  leg1->AddEntry( ptEventNumbers_[kBkg]  , "ttbar other"        , "F");
  leg1->AddEntry( ptEventNumbers_[kWjets], "W+jets MADGRAPH"    , "F");
  leg1->AddEntry( ptEventNumbers_[kZjets], "Z+jets MADGRAPH"    , "F");
  leg1->AddEntry( ptEventNumbers_[kQCD]  , "QCD PYHTIA"         , "F");
  leg1->AddEntry( pt_[kPseudo], "pseudo data from all MC"       , "P");
  leg1->AddEntry( pt_[kPseudo], "(ttbar + Wjets + Zjets + QCD)" , "" );

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<=5; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }

  // ---
  //    do the printing for pt_ ( Signal, lepton+jets, pseudo data )
  // ---
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetTitle("ptDiffNormXafterSelection"+jetMultiplicity+"Lum5pb@7TeV");
  axesStyle(*pt_ [kSig], "p_{t} ( #mu ) [GeV]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{t}(#mu)} [GeV^{-1}]", 0., 0.05, 0.055, 1.5);
  histogramStyle(*pt_ [kSig]    , kRed  , 1, 20, 0.1);
  histogramStyle(*pt_ [kPseudo] , kBlack, 1, 22);
  histogramStyle(*pt_ [kLepJets], kBlack, 1, 20, 0.1);
  pt_ [kSig]->SetBinError( 1, 0. );
  for(int i =2; i<= totalBinNumber+1; i++){
    pt_ [kSig]->SetBinError( i, ptDiffXSGError_[i-2] );
    pt_ [kPseudo]->SetBinError( i, ptDiffXPseudoError_[i-2] );
  }
  pt_ [kSig    ]->Draw("HIST");
  pt_ [kLepJets]->Draw("HIST same");
  pt_ [kPseudo ]->Draw("Psame");
  leg0          ->Draw("same");

  // ---
  //    do the printing for eta_ ( Signal, lepton+jets, pseudo data )
  // ---
  MyCanvas[1]->cd(0);
  MyCanvas[1]->SetTitle("etaDiffNormXafterSelection"+jetMultiplicity+"Lum5pb@7TeV");
  axesStyle(*eta_ [kSig], "#eta ( #mu )", "#frac{1}{#sigma} #frac{d#sigma}{d#eta (#mu)}", 0., 0.65, 0.055, 1.5);
  histogramStyle(*eta_[kSig    ], kRed  , 1, 20, 0.1);
  histogramStyle(*eta_[kPseudo ], kBlack, 1, 22);
  histogramStyle(*eta_[kLepJets], kBlack, 1, 20, 0.1);
  eta_ [kSig    ]->Draw("HIST");
  eta_ [kLepJets]->Draw("HIST same");
  eta_ [kPseudo ]->Draw("Psame");
  leg0           ->Draw("same");

  // ---
  //    do the printing for phi_ ( Signal, lepton+jets, pseudo data )
  // ---
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetTitle("phiDiffNormXafterSelection"+jetMultiplicity+"Lum5pb@7TeV");
  axesStyle(*phi_ [kSig], "#phi ( #mu )", "#frac{1}{#sigma} #frac{d#sigma}{d#phi (#mu)}} [rad^{-1}]", 0., 0.65, 0.055, 1.5);
  histogramStyle(*phi_[kSig    ], kRed  , 1, 20, 0.1);
  histogramStyle(*phi_[kPseudo ], kBlack, 1, 22);
  histogramStyle(*phi_[kLepJets], kBlack, 1, 20, 0.1);
  phi_ [kSig    ]->Draw("HIST");
  phi_ [kLepJets]->Draw("HIST same");
  phi_ [kPseudo ]->Draw("Psame");
  leg0           ->Draw("same");

  // ---
  //    do the printing for ptEventNumbers_
  // ---
  MyCanvas[3]->cd(0);
  MyCanvas[3]->SetTitle("ptInclusiveXafterSelection"+jetMultiplicity+"Lum5pb@7TeV");
  // add different contribution for stack plots
  ptEventNumbers_ [kBkg]  ->Add(ptEventNumbers_ [kSig]);   
  ptEventNumbers_ [kWjets]->Add(ptEventNumbers_ [kBkg]);   
  ptEventNumbers_ [kZjets]->Add(ptEventNumbers_ [kWjets]); 
  ptEventNumbers_ [kQCD]  ->Add(ptEventNumbers_ [kZjets]);   
  // plot style
  axesStyle(*ptEventNumbers_ [kQCD], "p_{t} ( #mu ) [GeV]", "events / GeV", 0.,  getMaximumDependingOnNjetsCut("pt",jetMultiplicity), 0.06, 1.5); 
  histogramStyle(*ptEventNumbers_ [kSig]   , kRed  , 1, 20, 0.1, 1);
  histogramStyle(*ptEventNumbers_ [kPseudo], kBlack, 1, 22);
  histogramStyle(*ptEventNumbers_ [kBkg]   , kBlue , 1, 20, 0.1, 1);
  histogramStyle(*ptEventNumbers_ [kWjets] , kGreen, 1, 20, 0.1, 1);
  histogramStyle(*ptEventNumbers_ [kZjets] , 6     , 1, 20, 0.1, 1);
  histogramStyle(*ptEventNumbers_ [kQCD]   , 14    , 1, 20, 0.1, 1);
  // set error bars
  for(unsigned int idx=kSig; idx<=kPseudo; idx++){
    ptEventNumbers_ [idx]->SetBinError( 1, 0. );
    for(int i =2; i<= totalBinNumber+1; i++){
      ptEventNumbers_ [idx]->SetBinError(  i, sqrt( (double)(ptEventNumbers_[idx]->GetBinContent(i)) ) / sqrt( (double)(ptEventNumbers_[idx]->GetBinWidth(i)) )  );
    }
  }
  // drawing
  ptEventNumbers_[kQCD   ]->Draw("HIST");
  ptEventNumbers_[kZjets ]->Draw("HIST same");
  ptEventNumbers_[kWjets ]->Draw("HIST same");
  ptEventNumbers_[kBkg   ]->Draw("HIST same");
  ptEventNumbers_[kSig   ]->Draw("HIST same");
  ptEventNumbers_[kPseudo]->Draw("Psame");
  leg1                    ->Draw("same");

  // ---
  //    do the printing for etaEventNumbers_
  // ---
  MyCanvas[4]->cd(0);
  MyCanvas[4]->SetTitle("etaInclusiveXafterSelection"+jetMultiplicity+"Lum5pb@7TeV");
  // add different contribution for stack plots
  etaEventNumbers_ [kBkg]  ->Add(etaEventNumbers_ [kSig]);   
  etaEventNumbers_ [kWjets]->Add(etaEventNumbers_ [kBkg]);   
  etaEventNumbers_ [kZjets]->Add(etaEventNumbers_ [kWjets]); 
  etaEventNumbers_ [kQCD]  ->Add(etaEventNumbers_ [kZjets]); 
  // plot style 
  axesStyle(*etaEventNumbers_ [kQCD], "#eta ( #mu )", "events / binWidth", 0., getMaximumDependingOnNjetsCut("eta",jetMultiplicity), 0.06, 1.5); 
  histogramStyle(*etaEventNumbers_ [kSig], kRed, 1, 20, 0.1, 1);
  histogramStyle(*etaEventNumbers_ [kPseudo], kBlack, 1, 22);
  histogramStyle(*etaEventNumbers_  [kBkg]   , kBlue , 1, 20, 0.1, 1);
  histogramStyle(*etaEventNumbers_  [kWjets] , kGreen, 1, 20, 0.1, 1);
  histogramStyle(*etaEventNumbers_  [kZjets] , 6     , 1, 20, 0.1, 1);
  histogramStyle(*etaEventNumbers_  [kQCD]   , 14    , 1, 20, 0.1, 1);
  // drawing
  etaEventNumbers_[kQCD    ]->Draw("HIST");
  etaEventNumbers_[kZjets  ]->Draw("HIST same");
  etaEventNumbers_[kWjets  ]->Draw("HIST same");
  etaEventNumbers_[kBkg    ]->Draw("HIST same");
  etaEventNumbers_[kSig   ]->Draw("HIST same");
  etaEventNumbers_[kPseudo]->Draw("Psame");
  leg1                     ->Draw("same");

  // ---
  //    do the printing for phiEventNumbers_
  // ---
  MyCanvas[5]->cd(0);
  MyCanvas[5]->SetTitle("phiInclusiveXafterSelection"+jetMultiplicity+"Lum5pb@7TeV");
  // add different contribution for stack plots
  phiEventNumbers_ [kBkg]  ->Add(phiEventNumbers_ [kSig]);   
  phiEventNumbers_ [kWjets]->Add(phiEventNumbers_ [kBkg]);   
  phiEventNumbers_ [kZjets]->Add(phiEventNumbers_ [kWjets]); 
  phiEventNumbers_ [kQCD]  ->Add(phiEventNumbers_ [kZjets]);
  // plot style
  axesStyle(*phiEventNumbers_ [kQCD], "#phi ( #mu )", "events / rad", 0.,  getMaximumDependingOnNjetsCut("phi",jetMultiplicity), 0.06, 1.5);
  histogramStyle(*phiEventNumbers_ [kSig], kRed, 1, 20, 0.1, 1);
  histogramStyle(*phiEventNumbers_ [kPseudo], kBlack, 1, 22);
  histogramStyle(*phiEventNumbers_  [kBkg]   , kBlue , 1, 20, 0.1, 1);
  histogramStyle(*phiEventNumbers_  [kWjets] , kGreen, 1, 20, 0.1, 1);
  histogramStyle(*phiEventNumbers_  [kZjets] , 6     , 1, 20, 0.1, 1);
  histogramStyle(*phiEventNumbers_  [kQCD]   , 14    , 1, 20, 0.1, 1);
  // drawing
  phiEventNumbers_[kQCD    ]->Draw("HIST");
  phiEventNumbers_[kZjets  ]->Draw("HIST same");
  phiEventNumbers_[kWjets  ]->Draw("HIST same");
  phiEventNumbers_[kBkg    ]->Draw("HIST same");
  phiEventNumbers_[kSig   ]->Draw("HIST same");
  phiEventNumbers_[kPseudo]->Draw("Psame");
  leg1                     ->Draw("same");

  // ---
  // saving
  // ---
  
//   // ps
//   MyCanvas[0]->Print("./diffXSecFromSignal/plots/diffX7TeV5pb"+jetMultiplicity+".ps("  );
//   for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
//     MyCanvas[idx]->Print("./diffXSecFromSignal/plots/diffX7TeV5pb"+jetMultiplicity+".ps"  );   
//   }
//   MyCanvas[MyCanvas.size()-1]->Print("./diffXSecFromSignal/plots/diffX7TeV5pb"+jetMultiplicity+".ps)"  );
  
//   // png
//   for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
//     MyCanvas[idx]->Print("./diffXSecFromSignal/plots/"+(TString)(MyCanvas[idx]->GetTitle())+".png"  );      
//   }
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
  maxValues_["pt" ]["Btag"  ]= 1.5;
  maxValues_["pt" ]["Njets4"]= 1.5;   //  50pb: 20000 / 4000 / 800 / 230 divide by app.15 because of events / GeV
  maxValues_["pt" ]["Njets3"]= 3.0;
  maxValues_["pt" ]["Njets2"]= 32.;
  maxValues_["pt" ]["Njets1"]= 235.;
  maxValues_["eta"]["Btag"  ]= 35.;
  maxValues_["eta"]["Njets4"]= 35.;   //  50pb: 15000 / 3500 / 800 / 210 divide by app.15 because of events / GeV
  maxValues_["eta"]["Njets3"]= 120.;
  maxValues_["eta"]["Njets2"]= 450.;
  maxValues_["eta"]["Njets1"]= 2300.;
  maxValues_["phi"]["Btag"  ]= 24.;
  maxValues_["phi"]["Njets4"]= 24.;   //  50pb: 12000 / 2000 / 600 / 140 divide by app.15 because of events / GeV
  maxValues_["phi"]["Njets3"]= 75.;
  maxValues_["phi"]["Njets2"]= 250.;
  maxValues_["phi"]["Njets1"]= 1400.;
  // get maximum value
  return maxValues_.find(plot)->second.find(Njets)->second;
}
