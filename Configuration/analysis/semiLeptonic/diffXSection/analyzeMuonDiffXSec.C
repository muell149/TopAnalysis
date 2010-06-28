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
#include <THStack.h>
#include <TPaveLabel.h>

enum styles {kSig, kData, kBkg, kWjets, kZjets, kQCD, kLepJets};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0, int fillStyle=1001); 
void axesStyle(TH1& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.05, float yTitleOffset=1.2);
void divideByBinwidth(std::vector<TH1F*> histoVector);
double getMaximumDependingOnNjetsCut(TString plot, TString Njets);
string getStringFromInt(int i);

void analyzeMuonDiffXSec(TString jetMultiplicity ="Njets4")
{ //choose jet multiplicity you want to see: "Njets1" / "Njets2" / "Njets3" / "Njets4" / "Njets4Btag" / "Njets3Btag"

  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  //  gStyle->SetPalette(1);
  gStyle->SetErrorX(0); 

  // choose luminosity for scaling of event numbers and for legend as entry
  int luminosity = 12.38;
  TString lum = "12";
  // choose whether you want to save every plot as png and all within one ps file
  bool save = true;
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/earlyData/jetMultiplicityStudies/";

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;

  TString whichSample = "/spring10Samples/spring10SelV2Sync";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigNloSpring10.root"    ) );
//  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecSigMadSpring10.root"    ) );
//  files_.push_back(new TFile("./diffXData2010.root"));
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecQCDPythiaSpring10.root" ) );
// ---------------
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgNloSpring10.root"    ) );
//   files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecBkgMadSpring10.root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecWjetsMadSpring10.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecZjetsMadSpring10.root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/diffXSecQCDPythiaSpring10.root" ) );

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

  // 7 TeV Monte Carlo spring 10 samples
  // -----------------------------------
  // for current ttbar(lept.mu on gen level) Mc@Nlo 
  lumiweight.push_back(0.00000831910/50.0*(double)luminosity);
  // for current ttbar(lept.mu on gen level) Madgraph 
  //  lumiweight.push_back(0.00556153/50.0*(double)luminosity);
  //  data
  lumiweight.push_back(1.0);
  // for current ttbar(non lept.mu on gen level) Mc@Nlo
  lumiweight.push_back(0.00000831910/50.0*(double)luminosity);
  // for current ttbar(non lept.mu on gen level) Madraph
  //  lumiweight.push_back(0.00556153/50.0*(double)luminosity);
  // for current W+jets MADGRAPH sample
  lumiweight.push_back(0.00013904207/50.0*(double)luminosity);
  // for current Z+jets MADGRAPH sample
  lumiweight.push_back(0.00014332841/50.0*(double)luminosity);
  // for current QCD PYTHIA sample
  lumiweight.push_back(0.00125483558/50.0*(double)luminosity);

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
    pt_ [kLepJets]->Add(pt_ [idx]);
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

  std::cout << "-------pt distribution,  data-------" << std::endl;
  for(int i=2; i<= pt_[kSig]->GetNbinsX()+1; i++){
    std::cout << "(weighted) # events pt-bin "<< i << ": " <<  ptEventNumbers_[kData]->GetBinContent(i) << " +/- " << sqrt( (double)(ptEventNumbers_[kData]->GetBinContent(i)) ) << std::endl;
  }
  std::cout << "total # events: " << eventNumbersPt_[kData] << std::endl;
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
  //    calculate statistical errors for differential xSec via gaussian error calculus
  // ---
  // a) pt
  std::vector<double> ptDiffXDataError_;  
  std::vector<double> ptDiffXSGError_;  

  for(unsigned int idx=kSig; idx<=kData; idx++){
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
      if(idx==kData){
	ptDiffXDataError_.push_back(result);
	  }
    }
  }

  // b) eta
  for(int i =1; i<=eta_[kData]->GetNbinsX(); i++){
      double result=0.;
      // calculate shortcut expression needed in final formula
      double errorHelperA=0;  
      errorHelperA= ( (double)(eta_[kData]->GetBinWidth(i)) * eventNumbersEta_[kData] ); 
      // final formula
      result = sqrt(  ((double)(etaEventNumbers_ [kData]->GetBinContent(i)) / errorHelperA / errorHelperA) * ( 1.0 - 2.0 * (double)(eta_[kData]->GetBinWidth(i)) / errorHelperA + ( (double)(etaEventNumbers_ [kData]->GetBinContent(i)) * (double)(eta_[kData]->GetBinWidth(i)) * (double)(pt_[kData]->GetBinWidth(i)) * (eventNumbersPt_[kData])  / errorHelperA / errorHelperA) )  );      
      eta_ [kData]->SetBinError( i, result );
  }


  // c) phi
  for(int i =1; i<=phi_[kData]->GetNbinsX(); i++){
      double result=0.;
      // calculate shortcut expression needed in final formula
      double errorHelperA=0;  
      errorHelperA= ( (double)(phi_[kData]->GetBinWidth(i)) * eventNumbersPhi_[kData] ); 
      // final formula
      result = sqrt(  ((double)(phiEventNumbers_ [kData]->GetBinContent(i)) / errorHelperA / errorHelperA) * ( 1.0 - 2.0 * (double)(phi_[kData]->GetBinWidth(i)) / errorHelperA + ( (double)(phiEventNumbers_ [kData]->GetBinContent(i)) * (double)(phi_[kData]->GetBinWidth(i)) * (double)(pt_[kData]->GetBinWidth(i)) * (eventNumbersPt_[kData])  / errorHelperA / errorHelperA) )  );      
      phi_ [kData]->SetBinError( i, result );
  }
  
  // ---
  //    print out diffXValue(pt) for each bin with statistical errors
  // ---
  std::cout << "-------signal only-------" << std::endl;
  for(int i=2; i<= pt_[kSig]->GetNbinsX(); i++){
    std::cout << "(d#sigma)/(dpt(muon) * #sigma) pt-bin "<< i << ": " <<  pt_[kSig]->GetBinContent(i) << " +/- " <<  ptDiffXSGError_[i-2] << std::endl;
  }
  std::cout << "------- data-------" << std::endl;
  for(int i=2; i<= pt_[kData]->GetNbinsX(); i++){
    std::cout << "(d#sigma)/(dpt(muon) * #sigma) pt-bin "<< i << ": " <<  pt_[kData]->GetBinContent(i) << " +/- " <<  ptDiffXDataError_[i-2] << std::endl;
  }

  // ---
  //     calculate relative event composition (with respect to total bin entries)
  // ---

  std::vector<TH1F*> ptEventNumbersRel_, etaEventNumbersRel_;
  for(int idx=kSig; idx<=kQCD; idx++){
    ptEventNumbersRel_  .push_back( (TH1F*)ptEventNumbers_ [idx]->Clone() );
    etaEventNumbersRel_ .push_back( (TH1F*)etaEventNumbers_[idx]->Clone() );
  
    // calculate value for each pt-bin i
    for(int i=2; i<=pt_[kSig]->GetNbinsX(); i++){
      ptEventNumbersRel_[idx]->SetBinContent(  i, (ptEventNumbersRel_[idx]->GetBinContent(i) ) / ( ptEventNumbers_[kSig]->GetBinContent(i)+ptEventNumbers_[kWjets]->GetBinContent(i)+ptEventNumbers_[kBkg]->GetBinContent(i)+ptEventNumbers_[kZjets]->GetBinContent(i)+ptEventNumbers_[kQCD]->GetBinContent(i) )  );
      ptEventNumbersRel_[idx]->SetBinError( i, 0.);
    }
    // calculate value for each eta-bin i
    for(int i=1; i<=eta_[kSig]->GetNbinsX(); i++){
      etaEventNumbersRel_[idx]->SetBinContent(  i, (etaEventNumbersRel_[idx]->GetBinContent(i) ) / ( etaEventNumbers_[kSig]->GetBinContent(i)+etaEventNumbers_[kWjets]->GetBinContent(i)+etaEventNumbers_[kBkg]->GetBinContent(i)+etaEventNumbers_[kZjets]->GetBinContent(i)+etaEventNumbers_[kQCD]->GetBinContent(i) )  );
      etaEventNumbersRel_[idx]->SetBinError( i, 0.);
    }
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
  TString jetMultiplicityLabel="";
  TString jetMultiplicityLabelbtag="";
  if(jetMultiplicity=="Njets1")jetMultiplicityLabel="N(Jets) #geq 1";
  if(jetMultiplicity=="Njets2")jetMultiplicityLabel="N(Jets) #geq 2";
  if(jetMultiplicity=="Njets3"||jetMultiplicity=="Njets3Btag")jetMultiplicityLabel="N(Jets) #geq 3";
  if(jetMultiplicity=="Njets4"||jetMultiplicity=="Njets4Btag")jetMultiplicityLabel="N(Jets) #geq 4";
  if(jetMultiplicity=="Njets4Btag"||jetMultiplicity=="Njets3Btag")jetMultiplicityLabelbtag="N(bTags) #geq 1";

  // create a legend (in upper right corner) for all MC samples and  data
  TLegend *leg0 = new TLegend(0.21, 0.74, 0.95, 0.94);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("MC (7TeV @ "+lum+"nb^{-1}) , full selection, "+jetMultiplicityLabel+" "+jetMultiplicityLabelbtag);
  leg0->AddEntry( pt_[kSig]    , "ttbar MC@NLO semi-lep.( #mu )" , "PL");
  leg0->AddEntry( pt_[kLepJets], "all lepton+jets MC"            , "PL");
  leg0->AddEntry( pt_[kData] , "2010 data"       , "P" );

  // create a legend (in upper right corner) for all MC samples and  data
  TLegend *leg1 = new TLegend(0.21, 0.66, 1.0, 0.95);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("MC (7TeV @ "+lum+"nb^{-1}) , full selection, "+jetMultiplicityLabel+" "+jetMultiplicityLabelbtag);
  leg1->AddEntry( ptEventNumbers_[kSig]  , "ttbar MC@NLO semi-lep.( #mu )"    , "F");
  leg1->AddEntry( ptEventNumbers_[kBkg]  , "ttbar other"        , "F");
  leg1->AddEntry( ptEventNumbers_[kWjets], "W+jets MADGRAPH"    , "F");
  leg1->AddEntry( ptEventNumbers_[kZjets], "Z+jets MADGRAPH"    , "F");
  leg1->AddEntry( ptEventNumbers_[kQCD]  , "QCD PYHTIA"         , "F");
  leg1->AddEntry( pt_[kData], "2010 data"                       , "PL");

  // create part 1 of legend for relative plot with underground
  //  TLegend *leg2 = new TLegend(0.22, 0.70, 0.70, 0.95);
  TLegend *leg2 = new TLegend(0.15, 0.04, 0.83, 0.96);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetHeader("MC samples @ 7TeV");
  leg2->AddEntry( ptEventNumbersRel_[kSig]   , "semi #mu ttbar Mc@Nlo", "PL");
  leg2->AddEntry( ptEventNumbersRel_[kBkg]   , "other ttbar Mc@Nlo"   , "PL");
  
  // create part 2 of legend for relative plot with underground
  TLegend *leg6 = new TLegend(0.15, 0.18, 0.83, 0.80);
  leg6->SetFillStyle(0);
  leg6->SetBorderSize(0);
  leg6->AddEntry( ptEventNumbersRel_[kQCD]   , "QCD Pythia"           , "PL");
  leg6->AddEntry( ptEventNumbersRel_[kWjets] , "Wjets Madgraph"       , "PL");
  leg6->AddEntry( ptEventNumbersRel_[kZjets] , "Zjets Madgraph"       , "PL");

  // create a legend for all MC samples and  data for special canvas
  TLegend *leg3 = new TLegend(0.03, 0.15, 1.0, 0.91);
  leg3->SetFillStyle(0);
  leg3->SetBorderSize(0);
  leg3->SetHeader("MC (7TeV @ "+lum+"nb^{-1}) , full selection, ");
  leg3->AddEntry( ptEventNumbers_[kSig]  , "ttbar MC@NLO semi-lep.( #mu )", "F");
  leg3->AddEntry( ptEventNumbers_[kBkg]  , "ttbar other"        , "F");
  leg3->AddEntry( ptEventNumbers_[kWjets], "W+jets MADGRAPH"    , "F");
  leg3->AddEntry( ptEventNumbers_[kZjets], "Z+jets MADGRAPH"    , "F");
  leg3->AddEntry( ptEventNumbers_[kQCD]  , "QCD PYHTIA"         , "F");
  leg3->AddEntry( pt_[kData], "2010 data"                       , "PL");

  // create jet multiplicity label  
  TPaveLabel *leg4 = new TPaveLabel(0.50, 0.74, 1.0, 1.0, jetMultiplicityLabel, "br NDC");
  leg4->SetFillStyle(0);
  leg4->SetBorderSize(0);
  leg4->SetTextSize(0.26);
  // create btag label
  TPaveLabel *leg5 = new TPaveLabel(0.50, 0.65, 1.0, 0.90, jetMultiplicityLabelbtag, "br NDC");
  leg5->SetFillStyle(0);
  leg5->SetBorderSize(0);
  leg5->SetTextSize(0.26);

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;

  for(int idx=0; idx<=8; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }
  MyCanvas.push_back( new TCanvas( "canv"+(TString)getStringFromInt(MyCanvas.size()), "canv"+(TString)getStringFromInt(MyCanvas.size()), 600, 200) );
  canvasStyle(*MyCanvas[MyCanvas.size()-1]);
  MyCanvas.push_back( new TCanvas( "canv"+(TString)getStringFromInt(MyCanvas.size()), "canv"+(TString)getStringFromInt(MyCanvas.size()), 600, 200) );
  canvasStyle(*MyCanvas[MyCanvas.size()-1]);	    

  // ---
  //    do the printing for pt_ ( Signal, lepton+jets,  data )
  // ---
  MyCanvas[0]->cd(0);
  MyCanvas[0]->SetTitle("ptDiffNormXafterSelection"+jetMultiplicity+"Lum"+lum+"nb@7TeV");
  axesStyle(*pt_ [kSig], "p_{t} ( #mu ) [GeV]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{t}(#mu)} [GeV^{-1}]", 0., 0.09, 0.055, 1.5);
  histogramStyle(*pt_ [kSig]    , kRed  , 1, 20, 0.1);
  histogramStyle(*pt_ [kData] , kBlack, 1, 22);
  histogramStyle(*pt_ [kLepJets], kBlack, 1, 20, 0.1);
  pt_ [kSig]->SetBinError( 1, 0. );
  for(int i =2; i<= totalBinNumber+1; i++){
    pt_ [kSig]->SetBinError( i, ptDiffXSGError_[i-2] );
    pt_ [kData]->SetBinError( i, ptDiffXDataError_[i-2] );
  }
  pt_ [kSig    ]->Draw("HIST");
  pt_ [kLepJets]->Draw("HIST same");
  pt_ [kData ]->Draw("Psame");
  leg0          ->Draw("same");

  // ---
  //    do the printing for eta_ ( Signal, lepton+jets,  data )
  // ---
  MyCanvas[1]->cd(0);
  MyCanvas[1]->SetTitle("etaDiffNormXafterSelection"+jetMultiplicity+"Lum"+lum+"nb@7TeV");
  axesStyle(*eta_ [kSig], "#eta ( #mu )", "#frac{1}{#sigma} #frac{d#sigma}{d#eta (#mu)}", 0., 1.4, 0.055, 1.5);
  histogramStyle(*eta_[kSig    ], kRed  , 1, 20, 0.1);
  histogramStyle(*eta_[kData ], kBlack, 1, 22);
  histogramStyle(*eta_[kLepJets], kBlack, 1, 20, 0.1);
  eta_ [kSig    ]->Draw("HIST");
  eta_ [kLepJets]->Draw("HIST same");
  eta_ [kData ]->Draw("Psame");
  leg0           ->Draw("same");

  // ---
  //    do the printing for phi_ ( Signal, lepton+jets,  data )
  // ---
  MyCanvas[2]->cd(0);
  MyCanvas[2]->SetTitle("phiDiffNormXafterSelection"+jetMultiplicity+"Lum"+lum+"nb@7TeV");
  axesStyle(*phi_ [kSig], "#phi ( #mu )", "#frac{1}{#sigma} #frac{d#sigma}{d#phi (#mu)}} [rad^{-1}]", 0., 1.4, 0.055, 1.5);
  histogramStyle(*phi_[kSig    ], kRed  , 1, 20, 0.1);
  histogramStyle(*phi_[kData   ], kBlack, 1, 22);
  histogramStyle(*phi_[kLepJets], kBlack, 1, 20, 0.1);
  phi_ [kSig    ]->Draw("HIST");
  phi_ [kLepJets]->Draw("HIST same");
  phi_ [kData   ]->Draw("Psame");
  leg0           ->Draw("same");

  // ---
  //    do the printing for ptEventNumbers_
  // ---
  MyCanvas[3]->cd(0);
  MyCanvas[3]->SetTitle("ptInclusiveXafterSelection"+jetMultiplicity+"Lum"+lum+"nb@7TeV");
  // add different contribution for stack plots
  ptEventNumbers_ [kBkg]  ->Add(ptEventNumbers_ [kSig]);   
  ptEventNumbers_ [kWjets]->Add(ptEventNumbers_ [kBkg]);   
  ptEventNumbers_ [kZjets]->Add(ptEventNumbers_ [kWjets]); 
  ptEventNumbers_ [kQCD]  ->Add(ptEventNumbers_ [kZjets]);   
  // plot style
  axesStyle(*ptEventNumbers_ [kQCD], "p_{t} ( #mu ) [GeV]", "events / GeV",  0.55/*0.5*ptEventNumbers_[kSig]->GetMinimum() 0.*/, 1.3*ptEventNumbers_[kQCD]->GetMaximum()/*getMaximumDependingOnNjetsCut("pt",jetMultiplicity)*/, 0.06, 1.5); 
  histogramStyle(*ptEventNumbers_ [kSig]   , 10, 1, 20, 0.1, 1, 1001);
  histogramStyle(*ptEventNumbers_ [kBkg]   , 10, 1, 20, 0.1, 1, 1001);
  histogramStyle(*ptEventNumbers_ [kWjets] , 10, 1, 20, 0.1, 1, 1001);
  histogramStyle(*ptEventNumbers_ [kZjets] , 10, 1, 20, 0.1, 1, 1001);
  histogramStyle(*ptEventNumbers_ [kQCD]   , 17, 1, 20, 0.1, 1, 1001);
  histogramStyle(*ptEventNumbers_ [kData]  , kBlack, 1, 22);
  // set error bars
  for(unsigned int idx=kSig; idx<=kData; idx++){
    ptEventNumbers_  [idx]->SetBinError( 1, 0. );
    for(int i =2; i<= totalBinNumber+1; i++){
      ptEventNumbers_ [idx]->SetBinError(  i, sqrt( (double)(ptEventNumbers_[idx]->GetBinContent(i)) ) / sqrt( (double)(ptEventNumbers_[idx]->GetBinWidth(i)) )  );
    }
    for(int i =1; i<= etaEventNumbers_ [idx]->GetNbinsX(); i++){
      etaEventNumbers_ [idx]->SetBinError(  i, sqrt( (double)(etaEventNumbers_[idx]->GetBinContent(i)) ) / sqrt( (double)(etaEventNumbers_[idx]->GetBinWidth(i)) )  );    
    }
    for(int i =1; i<= phiEventNumbers_ [idx]->GetNbinsX(); i++){
      phiEventNumbers_ [idx]->SetBinError(  i, sqrt( (double)(phiEventNumbers_[idx]->GetBinContent(i)) ) / sqrt( (double)(phiEventNumbers_[idx]->GetBinWidth(i)) )  );    
    }
  }
  
  // drawing
  ptEventNumbers_[kQCD   ]->Draw("HIST");
  ptEventNumbers_[kZjets ]->DrawClone(" HIST same");
  histogramStyle(*ptEventNumbers_ [kZjets] , 6     , 1, 20, 0.1, 1, 3005);
  ptEventNumbers_[kZjets ]->Draw("HIST same");
  ptEventNumbers_[kWjets ]->DrawClone("HIST same");
  histogramStyle(*ptEventNumbers_ [kWjets] , kGreen, 1, 20, 0.1, 1, 3004);
  ptEventNumbers_[kWjets ]->Draw("HIST same");
  ptEventNumbers_[kBkg   ]->DrawClone("HIST same");
  histogramStyle(*ptEventNumbers_ [kBkg]   , kBlue , 1, 20, 0.1, 1, 3007);
  ptEventNumbers_[kBkg   ]->Draw("HIST same");
  ptEventNumbers_[kSig   ]->DrawClone("HIST same");
  histogramStyle(*ptEventNumbers_ [kSig]   , kRed  , 1, 20, 0.1, 1, 3006);
  ptEventNumbers_[kSig   ]->Draw("HIST same");
  ptEventNumbers_[kData  ]->Draw("Psame");
  ptEventNumbers_[kQCD   ]->Draw("AXIS same");
  //  leg1                    ->Draw("same");
  leg4                    ->Draw("same");
  leg5                    ->Draw("same");

  // ---
  //    do the printing for etaEventNumbers_
  // ---
  MyCanvas[4]->cd(0);
  MyCanvas[4]->SetTitle("etaInclusiveXafterSelection"+jetMultiplicity+"Lum"+lum+"nb@7TeV");
  // add different contribution for stack plots
  etaEventNumbers_ [kBkg]  ->Add(etaEventNumbers_ [kSig]);   
  etaEventNumbers_ [kWjets]->Add(etaEventNumbers_ [kBkg]);   
  etaEventNumbers_ [kZjets]->Add(etaEventNumbers_ [kWjets]); 
  etaEventNumbers_ [kQCD]  ->Add(etaEventNumbers_ [kZjets]); 
  // plot style 
  axesStyle(*etaEventNumbers_ [kQCD], "#eta ( #mu )", "events / binWidth", 5.0/*0.5*etaEventNumbers_[kSig]->GetMinimum() 0.*/, 1.8*etaEventNumbers_[kQCD]->GetMaximum()/*getMaximumDependingOnNjetsCut("eta",jetMultiplicity)*/, 0.06, 1.5); 
  histogramStyle(*etaEventNumbers_ [kSig]   , 10, 1, 20, 0.1, 1, 1001);
  histogramStyle(*etaEventNumbers_ [kBkg]   , 10, 1, 20, 0.1, 1, 1001);
  histogramStyle(*etaEventNumbers_ [kWjets] , 10, 1, 20, 0.1, 1, 1001);
  histogramStyle(*etaEventNumbers_ [kZjets] , 10, 1, 20, 0.1, 1, 1001);
  histogramStyle(*etaEventNumbers_ [kQCD]   , 17, 1, 20, 0.1, 1, 1001);
  histogramStyle(*etaEventNumbers_ [kData]  , kBlack, 1, 22);
  // drawing
  etaEventNumbers_[kQCD   ]->Draw("HIST");
  etaEventNumbers_[kZjets ]->DrawClone(" HIST same");
  histogramStyle(*etaEventNumbers_ [kZjets] , 6     , 1, 20, 0.1, 1, 3005);
  etaEventNumbers_[kZjets ]->Draw("HIST same");
  etaEventNumbers_[kWjets ]->DrawClone("HIST same");
  histogramStyle(*etaEventNumbers_ [kWjets] , kGreen, 1, 20, 0.1, 1, 3004);
  etaEventNumbers_[kWjets ]->Draw("HIST same");
  etaEventNumbers_[kBkg   ]->DrawClone("HIST same");
  histogramStyle(*etaEventNumbers_ [kBkg]   , kBlue , 1, 20, 0.1, 1, 3007);
  etaEventNumbers_[kBkg   ]->Draw("HIST same");
  etaEventNumbers_[kSig   ]->DrawClone("HIST same");
  histogramStyle(*etaEventNumbers_ [kSig]   , kRed  , 1, 20, 0.1, 1, 3006);
  etaEventNumbers_[kSig   ]->Draw("HIST same");
  etaEventNumbers_[kData  ]->Draw("Psame");
  etaEventNumbers_[kQCD   ]->Draw("AXIS same");
  //  leg1                    ->Draw("same");
  leg4                    ->Draw("same");
  leg5                    ->Draw("same");

  // ---
  //    do the printing for phiEventNumbers_
  // ---
  MyCanvas[5]->cd(0);
  MyCanvas[5]->SetTitle("phiInclusiveXafterSelection"+jetMultiplicity+"Lum"+lum+"nb@7TeV");
  // add different contribution for stack plots
  phiEventNumbers_ [kBkg]  ->Add(phiEventNumbers_ [kSig]);   
  phiEventNumbers_ [kWjets]->Add(phiEventNumbers_ [kBkg]);   
  phiEventNumbers_ [kZjets]->Add(phiEventNumbers_ [kWjets]); 
  phiEventNumbers_ [kQCD]  ->Add(phiEventNumbers_ [kZjets]);
  // plot style
  axesStyle(*phiEventNumbers_ [kQCD], "#phi ( #mu )", "events / rad", 5.5/*0.5*phiEventNumbers_[kSig]->GetMinimum() 0.*/, 1.8*phiEventNumbers_[kQCD]->GetMaximum() /*getMaximumDependingOnNjetsCut("phi",jetMultiplicity)*/, 0.06, 1.5);
  histogramStyle(*phiEventNumbers_ [kSig]   , 10, 1, 20, 0.1, 1, 1001);
  histogramStyle(*phiEventNumbers_ [kBkg]   , 10, 1, 20, 0.1, 1, 1001);
  histogramStyle(*phiEventNumbers_ [kWjets] , 10, 1, 20, 0.1, 1, 1001);
  histogramStyle(*phiEventNumbers_ [kZjets] , 10, 1, 20, 0.1, 1, 1001);
  histogramStyle(*phiEventNumbers_ [kQCD]   , 17, 1, 20, 0.1, 1, 1001);
  histogramStyle(*phiEventNumbers_ [kData]  , kBlack, 1, 22);
  // drawing
  phiEventNumbers_[kQCD   ]->Draw("HIST");
  phiEventNumbers_[kZjets ]->DrawClone(" HIST same");
  histogramStyle(*phiEventNumbers_ [kZjets] , 6     , 1, 20, 0.1, 1, 3005);
  phiEventNumbers_[kZjets ]->Draw("HIST same");
  phiEventNumbers_[kWjets ]->DrawClone("HIST same");
  histogramStyle(*phiEventNumbers_ [kWjets] , kGreen, 1, 20, 0.1, 1, 3004);
  phiEventNumbers_[kWjets ]->Draw("HIST same");
  phiEventNumbers_[kBkg   ]->DrawClone("HIST same");
  histogramStyle(*phiEventNumbers_ [kBkg]   , kBlue , 1, 20, 0.1, 1, 3007);
  phiEventNumbers_[kBkg   ]->Draw("HIST same");
  phiEventNumbers_[kSig   ]->DrawClone("HIST same");
  histogramStyle(*phiEventNumbers_ [kSig]   , kRed  , 1, 20, 0.1, 1, 3006);
  phiEventNumbers_[kSig   ]->Draw("HIST same");
  phiEventNumbers_[kData  ]->Draw("Psame");
  phiEventNumbers_[kQCD   ]->Draw("AXIS same");
  //  leg1                     ->Draw("same");
  leg4                     ->Draw("same");
  leg5                     ->Draw("same");

  // ---
  //    relative event composition as function of pt(mu)
  // ---
  float maxRel =1.0;
  if(jetMultiplicity=="Njets1"||jetMultiplicityLabelbtag!=""||jetMultiplicity=="Njets2")maxRel =1.5;
  MyCanvas[6]->cd(0);
  MyCanvas[6]->SetTitle("eventCompositionRelativePtMu"+lum+"nb"+jetMultiplicity);
  MyCanvas[6]->SetGrid(1,1);
  // plot style
  axesStyle(*ptEventNumbersRel_[kSig] , "p_{t} ( #mu ) [GeV]", "fraction (events)", 0., maxRel);
  histogramStyle(*ptEventNumbersRel_[kSig  ], kRed  , 1, 22, 1.5, 0);
  histogramStyle(*ptEventNumbersRel_[kWjets], kGreen, 1, 20, 1.5, 0);
  histogramStyle(*ptEventNumbersRel_[kBkg  ], kBlue,  1, 23, 1.5, 0);
  histogramStyle(*ptEventNumbersRel_[kZjets], 6,      1, 21, 1.5, 0);
  histogramStyle(*ptEventNumbersRel_[kQCD  ], 14,     1, 29, 1.5, 0); 
  // drawing
  ptEventNumbersRel_[kSig]->Draw("");
  for(unsigned int idx=0; idx<ptEventNumbersRel_.size(); idx++){
    if(idx!=kData){
      ptEventNumbersRel_ [idx]->Draw("same" );
      ptEventNumbersRel_ [idx]->Draw("Psame");
    }
  }
  //  leg2->Draw("same");
  leg4->Draw("same");
  leg5->Draw("same");

  // ---
  //    relative event composition as function of eta(mu)
  // ---
  maxRel =1.0;
  if(jetMultiplicity=="Njets1"||jetMultiplicity=="Btag"||jetMultiplicity=="Njets2")maxRel =1.5;
  MyCanvas[7]->cd(0);
  MyCanvas[7]->SetTitle("eventCompositionRelativeEtaMu"+lum+"nb"+jetMultiplicity);
  MyCanvas[7]->SetGrid(1,1);
  // plot style
  axesStyle(*etaEventNumbersRel_[kSig], "#eta ( #mu )", "fraction (events)", 0., maxRel);
  histogramStyle(*etaEventNumbersRel_[kSig  ], kRed  , 1, 22, 1.5, 0);
  histogramStyle(*etaEventNumbersRel_[kWjets], kGreen, 1, 20, 1.5, 0);
  histogramStyle(*etaEventNumbersRel_[kBkg  ], kBlue,  1, 23, 1.5, 0);
  histogramStyle(*etaEventNumbersRel_[kZjets], 6,      1, 21, 1.5, 0);
  histogramStyle(*etaEventNumbersRel_[kQCD  ], 14,     1, 29, 1.5, 0); 
  // drawing
  etaEventNumbersRel_[kSig]->Draw("");
  for(unsigned int idx=0; idx<etaEventNumbersRel_.size(); idx++){
    if(idx!=kData){
      etaEventNumbersRel_[idx]->Draw("same" );
      etaEventNumbersRel_[idx]->Draw("Psame");
    }
  }
  //  leg2->Draw("same");
  leg4->Draw("same");
  leg5->Draw("same");

  // ---
  //    do the printing for the common event numbers legend
  // ---
  MyCanvas[8]->cd(0);
  MyCanvas[8]->SetTitle("legendEventYieldLum"+lum+"nb@7TeV");
  leg3->Draw("");

  // ---
  //    do the printing for the common realtive event numbers legend
  // ---
  MyCanvas[MyCanvas.size()-1]->cd(0);
  MyCanvas[MyCanvas.size()-1]->SetTitle("legendPart1EventCompositionLum"+lum+"nb@7TeV");
  leg2->Draw("");

  // ---
  //    do the printing for the common realtive event numbers legend
  // ---
  MyCanvas[MyCanvas.size()-2]->cd(0);
  MyCanvas[MyCanvas.size()-2]->SetTitle("legendPart2EventCompositionLum"+lum+"nb@7TeV");
  leg6->Draw("");


  // ---
  // saving
  // ---
  if(save){   
    // ps
    MyCanvas[0]->Print(saveTo+"diffX7TeV"+lum+"nb"+jetMultiplicity+".ps(");
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+"diffX7TeV"+lum+"nb"+jetMultiplicity+".ps");   
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+"diffX7TeV"+lum+"nb"+jetMultiplicity+".ps)");
  
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

void histogramStyle(TH1& hist, int color, int lineStyle, int markerStyle, float markersize, int filled, int fillStyle) 
{
  hist.SetLineWidth(3);
  hist.SetStats(kFALSE);
  hist.SetLineColor  (color);
  hist.SetMarkerColor(color);  
  hist.SetMarkerStyle(markerStyle);
  hist.SetMarkerSize(markersize);
  hist.SetLineStyle(lineStyle);
  if(filled==1){
    hist.SetFillColor(color);
    hist.SetFillStyle(fillStyle);
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
  maxValues_["pt" ]["Njets4Btag"]= 0.8;
  maxValues_["pt" ]["Njets3Btag"]= 1.8;
  maxValues_["pt" ]["Njets4"]= 1.6;   
  maxValues_["pt" ]["Njets3"]= 5.5;
  maxValues_["pt" ]["Njets2"]= 25.;
  maxValues_["pt" ]["Njets1"]= 170.;
  maxValues_["eta"]["Njets4Btag"]= 16.;
  maxValues_["eta"]["Njets3Btag"]= 45.;
  maxValues_["eta"]["Njets4"]= 30.;   
  maxValues_["eta"]["Njets3"]= 80.;
  maxValues_["eta"]["Njets2"]= 300.;
  maxValues_["eta"]["Njets1"]= 1600.;
  maxValues_["phi"]["Njets4Btag"]= 12.;
  maxValues_["phi"]["Njets3Btag"]= 35.;
  maxValues_["phi"]["Njets4"]= 18.;   
  maxValues_["phi"]["Njets3"]= 60.;
  maxValues_["phi"]["Njets2"]= 250.;
  maxValues_["phi"]["Njets1"]= 1400.;
  // get maximum value
  return maxValues_.find(plot)->second.find(Njets)->second;
}

string getStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return result;
}
