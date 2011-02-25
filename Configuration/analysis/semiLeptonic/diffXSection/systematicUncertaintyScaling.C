#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include <TH1F.h>
#include <TH2F.h>
#include <THStack.h>
#include <TROOT.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TPaveLabel.h>
#include <TStyle.h>
#include <typeinfo>

//////////////////////////////////////////////////////////////////////////////////////////////////
////  This Macro analyzes systematic shifts of a) the JES +/- 1%, b) QCD prediction +/- 100%, ////
////  c) W+jets prediction +/- 50%. For this purpose, a sensitive variable is chosen          ////
////  and for every variation is shown, that data is described within this variation          ////  
//////////////////////////////////////////////////////////////////////////////////////////////////

enum styles {kSig, kBkg, kZjets, kWjets, kQCD, kData, kSigJES09, kBkgJES09, kZjetsJES09, kWjetsJES09, kQCDJES09, kSigJES11, kBkgJES11, kZjetsJES11, kWjetsJES11, kQCDJES11, kStd, kJES09, kJES11, kQCDup, kQCDdown, kWup, kWdown};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, int color=kBlack, int lineStyle=1, int markerStyle=20, float markersize=1.5, int filled=0, int fillStyle=1001); 
template <class T>
void axesStyle(T& hist, const char* titleX, const char* titleY, float yMin=-123, float yMax=-123, float yTitleSize=0.07, float yTitleOffset=1.2);
int roundToInt(double value);
TString getTStringFromInt(int i);
double readLineFromFile(int line, TString file="crossSectionCalculation.txt");

void systematicUncertaintyScaling(double luminosity = 36100, bool save = true, TString dataFile="./diffXSecFromSignal/data/DiffXSecData_Nov15PF.root", bool logartihmicPlots=false, TString jetType = "PF", TString up = "JES11", TString down = "JES09")
{

  // ---
  //    main function parameters
  // ---
  // save:       choose whether you want to save every plot as png and all within one ps file
  // luminosity: choose luminosity for scaling of event numbers 
  //             lum.lum2 is derived from this and used for legend as entry
  TString lum  = getTStringFromInt(roundToInt(luminosity/1000));
  // choose target directory for saving
  TString saveTo = "./diffXSecFromSignal/plots/systematicVariations/";
  // logartihmicPlots: choose whether you want to see the plots with logarithmic axis
  TString log = "";
  if(logartihmicPlots) log = "Log";
  // ---
  //     parameters for systematic scaling
  // ---
  // JES: done by using corresponding root files
  // wScale: choose W+jets scaling factor
  double wscale= 0.4;
  // qcdScale: choose QCD scaling factor
  double qcdScale= 0.5;

  // ---
  //    set root style 
  // ---
  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetErrorX(0); 

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  TString whichSample = "/analysisRootFiles";
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecSigMadD6TFall10"+jetType+".root"         ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecBkgMadD6TFall10"+jetType+".root"         ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecZjetsMadD6TFall10"+jetType+".root"       ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecWjetsMadD6TFall10"+jetType+".root"       ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecQCDPythiaZ2Fall10"+jetType+".root"       ) );

  files_.push_back(new TFile(dataFile                                                                  ) );

  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecSigMadD6TFall10"+down+jetType+".root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecBkgMadD6TFall10"+down+jetType+".root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecZjetsMadD6TFall10"+down+jetType+".root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecWjetsMadD6TFall10"+down+jetType+".root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecQCDPythiaZ2Fall10"+jetType+".root"       ) );

  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecSigMadD6TFall10"+up+jetType+".root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecBkgMadD6TFall10"+up+jetType+".root"    ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecZjetsMadD6TFall10"+up+jetType+".root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecWjetsMadD6TFall10"+up+jetType+".root"  ) );
  files_.push_back(new TFile("./diffXSecFromSignal"+whichSample+"/muonDiffXSecQCDPythiaZ2Fall10"+jetType+".root"     ) );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> relIso_, ptlead1Jet_, ptlead2Jet_, ptlead3Jet_, ptlead4Jet_, yieldPt_;
  for(unsigned int idx=0; idx<files_.size(); ++idx){
    // muon Isolation for QCD 
    relIso_    .push_back( (TH1F*)files_[idx]->Get("noIsoMuonQuality/relIso"    )->Clone()   );
    // lead jet pt for W+jets and JES			       
    ptlead1Jet_.push_back( (TH1F*)files_[idx]->Get("noPtLead_0_JetKinematics/pt")->Clone()   );
    ptlead2Jet_.push_back( (TH1F*)files_[idx]->Get("noPtLead_1_JetKinematics/pt")->Clone()   );
    ptlead3Jet_.push_back( (TH1F*)files_[idx]->Get("noPtLead_2_JetKinematics/pt")->Clone()   );
    ptlead4Jet_.push_back( (TH1F*)files_[idx]->Get("noPtLead_3_JetKinematics/pt")->Clone()   );
    // muon pt for QCD from HTLepFit estimation
    yieldPt_   .push_back( (TH1F*)files_[idx]->Get("analyzeTightMuonCrossSectionRecNjets1/pt") );
  }

  // ---
  //    define weights concerning luminosity
  // ---
  std::vector<double> lumiweight_;
  // add scaling factors here!

  // 7 TeV Monte Carlo spring 10 samples
  // -----------------------------------
  // for current ttbar(lept.mu on gen level and other) Madgraph 
  lumiweight_.push_back(0.000006029022/50.0*(double)luminosity);
  lumiweight_.push_back(0.000006029022/50.0*(double)luminosity);
  // for current Z+jets MADGRAPH sample
  lumiweight_.push_back(0.000059912090/50.0*(double)luminosity);
  // for current W+jets MADGRAPH sample
  lumiweight_.push_back(0.000105750913/50.0*(double)luminosity);
  // for current QCD PYTHIA sample
  lumiweight_.push_back(0.000143500567/50.0*(double)luminosity);
    // for data
  lumiweight_.push_back(1.0);
  
  // apply weighting
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    // use correct lumiweights for JES - sample
    unsigned int index = idx;
    if((kSigJES09<=idx)&&(idx<=kQCDJES09)) index = idx-6;
    if((kSigJES11<=idx)&&(idx<=kQCDJES11)) index = idx-11;
    //   std::cout << "file " << idx << ", weighting factor: " << lumiweight_[index] << std::endl;
    relIso_    [idx]->Scale(lumiweight_[index]);
    ptlead1Jet_[idx]->Scale(lumiweight_[index]);
    ptlead2Jet_[idx]->Scale(lumiweight_[index]);
    ptlead3Jet_[idx]->Scale(lumiweight_[index]);
    ptlead4Jet_[idx]->Scale(lumiweight_[index]); 
    yieldPt_   [idx]->Scale(lumiweight_[index]); 
    // scale QCD with weights from MET-fit
    if((idx==kQCD)||(idx==kQCDJES09)||(idx==kQCDJES11)){
      ptlead1Jet_[idx]->Scale(1.5);
      ptlead2Jet_[idx]->Scale(1.9);
      ptlead3Jet_[idx]->Scale(2.0);
      ptlead4Jet_[idx]->Scale(1.8);
      yieldPt_   [idx]->Scale(1.5); 
    }
    // create combined MC plots
    if((idx==kSig)||(idx==kSigJES09)||(idx==kSigJES11)){
      relIso_    .push_back( (TH1F*)(relIso_    [idx]->Clone()) );
      ptlead1Jet_.push_back( (TH1F*)(ptlead1Jet_[idx]->Clone()) );
      ptlead2Jet_.push_back( (TH1F*)(ptlead2Jet_[idx]->Clone()) );
      ptlead3Jet_.push_back( (TH1F*)(ptlead3Jet_[idx]->Clone()) );
      ptlead4Jet_.push_back( (TH1F*)(ptlead4Jet_[idx]->Clone()) );
      yieldPt_   .push_back( (TH1F*)(yieldPt_   [idx]->Clone()) );
    }
    else if(idx!=kData){
      unsigned int combined = kStd;
      if((kSigJES09<=idx)&&(idx<=kQCDJES09)) combined=kJES09;
      if((kSigJES11<=idx)&&(idx<=kQCDJES11)) combined=kJES11;
      relIso_    [combined]->Add( (TH1F*)(relIso_    [idx]->Clone()) );
      ptlead1Jet_[combined]->Add( (TH1F*)(ptlead1Jet_[idx]->Clone()) );
      ptlead2Jet_[combined]->Add( (TH1F*)(ptlead2Jet_[idx]->Clone()) );
      ptlead3Jet_[combined]->Add( (TH1F*)(ptlead3Jet_[idx]->Clone()) );
      ptlead4Jet_[combined]->Add( (TH1F*)(ptlead4Jet_[idx]->Clone()) );
      yieldPt_   [combined]->Add( (TH1F*)(yieldPt_   [idx]->Clone()) );
      // yield ohne QCD
      //if((idx!=kQCD)&&(idx!=kQCDJES09)&&(idx!=kQCDJES11)) 
    }
  }

  // do the QCD and W+jets shifts
  // a) clone all MC plots
  for(unsigned int idx=kQCDup; idx<=kWdown; ++idx){
    relIso_    .push_back( (TH1F*)(relIso_    [kStd]->Clone()) );
    ptlead1Jet_.push_back( (TH1F*)(ptlead1Jet_[kStd]->Clone()) );
    ptlead2Jet_.push_back( (TH1F*)(ptlead2Jet_[kStd]->Clone()) );
    ptlead3Jet_.push_back( (TH1F*)(ptlead3Jet_[kStd]->Clone()) );
    ptlead4Jet_.push_back( (TH1F*)(ptlead4Jet_[kStd]->Clone()) );
    if((idx==kQCDup)||(idx==kQCDdown)) yieldPt_   .push_back( (TH1F*)(yieldPt_   [kStd]->Clone()) );
  }
  // b) QCD/W+jets MC shift
  for(unsigned int idx=kQCDup; idx<=kWdown; ++idx){
    unsigned int subract=0;
    double scale=0;
    if((idx==kQCDup)||(idx==kQCDdown)){
      subract=kQCD;
      if(idx==kQCDup  ) scale=+qcdScale;
      if(idx==kQCDdown) scale=-qcdScale;
    }
    if((idx==kWup  )||(idx==kWdown  )){
      subract=kWjets;
      if(idx==kWup    ) scale=+wscale;
      if(idx==kWdown  ) scale=-wscale;
    }
    // subtract std QCD/W+jets
    relIso_    [idx]->Add( (TH1F*)(relIso_    [subract]->Clone()), -1 );
    ptlead1Jet_[idx]->Add( (TH1F*)(ptlead1Jet_[subract]->Clone()), -1 );
    ptlead2Jet_[idx]->Add( (TH1F*)(ptlead2Jet_[subract]->Clone()), -1 );
    ptlead3Jet_[idx]->Add( (TH1F*)(ptlead3Jet_[subract]->Clone()), -1 );
    ptlead4Jet_[idx]->Add( (TH1F*)(ptlead4Jet_[subract]->Clone()), -1 );
    if((idx==kQCDup)||(idx==kQCDdown)) yieldPt_   [idx]->Add( (TH1F*)(yieldPt_   [subract]->Clone()), -1 );
    // add shifted QCD/W+jets
    TH1F* help1 = ((TH1F*)relIso_    [subract]->Clone());
    help1->Scale(1+scale);
    TH1F* help2 = ((TH1F*)ptlead1Jet_[subract]->Clone());
    help2->Scale(1+scale);
    TH1F* help3 = ((TH1F*)ptlead2Jet_[subract]->Clone());
    help3->Scale(1+scale);
    TH1F* help4 = ((TH1F*)ptlead3Jet_[subract]->Clone());
    help4->Scale(1+scale);
    TH1F* help5 = ((TH1F*)ptlead4Jet_[subract]->Clone());
    help5->Scale(1+scale);   
    relIso_    [idx]->Add( help1 );
    ptlead1Jet_[idx]->Add( help2 );
    ptlead2Jet_[idx]->Add( help3 );
    ptlead3Jet_[idx]->Add( help4 );
    ptlead4Jet_[idx]->Add( help5 );   
    if((idx==kQCDup)||(idx==kQCDdown)){
      TH1F* help6 = ((TH1F*)yieldPt_   [subract]->Clone());
      help6->Scale(1+scale);
      yieldPt_[idx]->Add( help6 );
    } 
    // std::cout << "file " << idx << ", modify: " << subract;
    // std::cout << " with factor: " << scale << std::endl;
  }

  // ---
  //    create legends 
  // ---
  TLegend *JESleg = new TLegend(0.38, 0.64, 0.94, 0.93);
  JESleg->SetFillStyle(0);
  JESleg->SetBorderSize(0);
  JESleg->AddEntry( ptlead1Jet_[kStd  ], "MC"                          , "PL");
  JESleg->AddEntry( ptlead1Jet_[kJES11], "JES up"                      , "PL");
  JESleg->AddEntry( ptlead1Jet_[kJES09], "JES down"                    , "PL");
  JESleg->AddEntry( ptlead1Jet_[kData ], "2010 data "+lum+" pb ^{-1}"  , "P" );

  TLegend *Wjetsleg = new TLegend(0.40, 0.56, 0.94, 0.96);
  Wjetsleg->SetFillStyle(0);
  Wjetsleg->SetBorderSize(0);
  Wjetsleg->AddEntry( ptlead1Jet_[kStd  ], "MC"                         , "PL");
  Wjetsleg->AddEntry( ptlead1Jet_[kWup  ], "+ 40% W#rightarrowl#nu"     , "PL");
  Wjetsleg->AddEntry( ptlead1Jet_[kWdown], "- 40% W#rightarrowl#nu"     , "PL");
  Wjetsleg->AddEntry( ptlead1Jet_[kData ], "2010 data "+lum+" pb ^{-1}" , "P" );
  
  TLegend *QCDleg = new TLegend(0.33, 0.62, 0.93, 0.95);
  QCDleg->SetFillStyle(0);
  QCDleg->SetBorderSize(0);
  QCDleg->AddEntry( relIso_[kStd    ], "MC"                        , "PL");
  QCDleg->AddEntry( relIso_[kQCDup  ], "+ 50% QCD"                 , "PL");
  QCDleg->AddEntry( relIso_[kQCDdown], "- 50% QCD"                 , "PL");
  QCDleg->AddEntry( relIso_[kData   ], "2010 data "+lum+" pb ^{-1}", "P" );

  TLegend *ABCDleg = new TLegend(0.31, 0.69, 0.96, 0.93);
  ABCDleg->SetFillStyle(0);
  ABCDleg->SetBorderSize(0);
  ABCDleg->AddEntry( yieldPt_[kStd    ], "MC + QCD(MET)"             , "PL");
  ABCDleg->AddEntry( yieldPt_[kQCDup  ], "+ 50% QCD"                 , "PL");
  ABCDleg->AddEntry( yieldPt_[kQCDdown], "- 50% QCD"                 , "PL");
  ABCDleg->AddEntry( yieldPt_[kData   ], "2010 data "+lum+" pb ^{-1}", "P" );

  // ---
  //    create canvas 
  // ---
  std::vector<TCanvas*> MyCanvas;
  for(int idx=0; idx<7; idx++){ 
    char canvname[10];
    sprintf(canvname,"canv%i",idx);    
    MyCanvas.push_back( new TCanvas( canvname, canvname, 600, 600) );
    canvasStyle(*MyCanvas[idx]);
  }
  // create canvas indicator
  int canvasNumber=0;
  // ---
  //    do the printing for the QCD variation
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("QCDvariation"+log);
  if(logartihmicPlots)MyCanvas[canvasNumber]->SetLogy(1);
  histogramStyle(*relIso_[kStd    ], kBlack, 1, 20, 0.5, 0);
  histogramStyle(*relIso_[kQCDup  ], kBlue , 1, 20, 0.5, 0);
  histogramStyle(*relIso_[kQCDdown], kRed  , 1, 20, 0.5, 0);
  histogramStyle(*relIso_[kData   ], kBlack, 1, 22, 1.8, 0);
  if(!logartihmicPlots) axesStyle(*relIso_[kStd], "relIso(#mu)" , "events", 0, 1.05*relIso_[kStd]->GetMaximum());
  if(logartihmicPlots) axesStyle(*relIso_[kStd], "relIso(#mu)" , "events", 0.1, 250.*relIso_[kQCDup]->GetMaximum());
  relIso_[kStd         ]->Draw(""        );
  relIso_[kQCDup       ]->Draw("hist same"); 
  relIso_[kQCDdown     ]->Draw("hist same");
  relIso_[kData        ]->Draw("p e1 same");
  QCDleg                ->Draw("same");
  ++canvasNumber;	

  // ---
  //    do the printing for the W variation
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("Wvariation"+log);
  if(logartihmicPlots)MyCanvas[canvasNumber]->SetLogy(1);  
  histogramStyle(*ptlead1Jet_[kStd  ], kBlack, 1, 20, 0.5, 0);
  histogramStyle(*ptlead1Jet_[kWup  ], kBlue , 1, 20, 0.5, 0);
  histogramStyle(*ptlead1Jet_[kWdown], kRed  , 1, 20, 0.5, 0);
  histogramStyle(*ptlead1Jet_[kData ], kBlack, 1, 22, 1.8, 0);
  if(!logartihmicPlots) axesStyle(*ptlead1Jet_[kStd], "p_{t}(jet 1)" , "events", 0, 1.1*ptlead1Jet_[kWup]->GetBinContent(7));
  double min = 0.3*luminosity/1000.;
  double max = ptlead1Jet_[kData]->GetBinContent(7);
  if(logartihmicPlots) axesStyle(*ptlead1Jet_[kStd], "p_{t}(jet 1)" , "events", min, exp(1.4*(std::log(max)-std::log(min))+std::log(min)));
  ptlead1Jet_[kStd     ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead1Jet_[kJES11   ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead1Jet_[kJES09   ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead1Jet_[kData    ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead1Jet_[kStd     ]->DrawClone("");
  ptlead1Jet_[kWup     ]->Draw("hist same"); 
  ptlead1Jet_[kWdown   ]->Draw("hist same");
  ptlead1Jet_[kData    ]->Draw("p e1 same");
  Wjetsleg              ->Draw("same");
  ++canvasNumber;	

  // ---
  //    do the printing for the JES variations 1
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("JESvariationLead1Jet"+log);
  if(logartihmicPlots)MyCanvas[canvasNumber]->SetLogy(1);
  histogramStyle(*ptlead1Jet_[kStd  ], kBlack, 1, 20, 0.5, 0);
  histogramStyle(*ptlead1Jet_[kJES11], kBlue , 1, 20, 0.5, 0);
  histogramStyle(*ptlead1Jet_[kJES09], kRed  , 1, 20, 0.5, 0);
  histogramStyle(*ptlead1Jet_[kData ], kBlack, 1, 22, 1.8, 0);
  if(!logartihmicPlots) axesStyle(*ptlead1Jet_[kStd], "p_{t}(jet 1)" , "events", 0, 1.1*ptlead1Jet_[kJES11]->GetBinContent(7));
  if(logartihmicPlots) axesStyle(*ptlead1Jet_[kStd], "p_{t}(jet 1)" , "events", 0.3*luminosity/1000., 10*ptlead1Jet_[kJES11]->GetBinContent(7));
  ptlead1Jet_[kStd     ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead1Jet_[kJES11   ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead1Jet_[kJES09   ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead1Jet_[kData    ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead1Jet_[kStd     ]->DrawClone("");
  ptlead1Jet_[kJES11   ]->Draw("same"); 
  ptlead1Jet_[kJES09   ]->Draw("same");
  ptlead1Jet_[kData    ]->Draw("p e1 same");
  JESleg                ->Draw("same");
  ++canvasNumber;

  // ---
  //    do the printing for the JES variations 2
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("JESvariationLead2Jet"+log);
  if(logartihmicPlots)MyCanvas[canvasNumber]->SetLogy(1);
  histogramStyle(*ptlead2Jet_[kStd  ], kBlack, 1, 20, 0.5, 0);
  histogramStyle(*ptlead2Jet_[kJES11], kBlue , 1, 20, 0.5, 0);
  histogramStyle(*ptlead2Jet_[kJES09], kRed  , 1, 20, 0.5, 0);
  histogramStyle(*ptlead2Jet_[kData ], kBlack, 1, 22, 1.8, 0);
  if(!logartihmicPlots) axesStyle(*ptlead2Jet_[kStd], "p_{t}(jet 2)" , "events", 0, 1.2*ptlead2Jet_[kJES11]->GetBinContent(7));
  if(logartihmicPlots) axesStyle(*ptlead2Jet_[kStd], "p_{t}(jet 2)" , "events", 0.03*luminosity/1000., 10*ptlead2Jet_[kJES11]->GetBinContent(7));
  ptlead2Jet_[kStd     ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead2Jet_[kJES11   ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead2Jet_[kJES09   ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead2Jet_[kData    ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead2Jet_[kStd     ]->Draw("");
  ptlead2Jet_[kJES11   ]->Draw("same"); 
  ptlead2Jet_[kJES09   ]->Draw("same");
  ptlead2Jet_[kData    ]->Draw("p e1 same");
  JESleg                ->Draw("same");
  ++canvasNumber;

  // ---
  //    do the printing for the JES variations 3
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("JESvariationLead3Jet"+log);
  if(logartihmicPlots)MyCanvas[canvasNumber]->SetLogy(1);
  histogramStyle(*ptlead3Jet_[kStd  ], kBlack, 1, 20, 0.5, 0);
  histogramStyle(*ptlead3Jet_[kJES11], kBlue , 1, 20, 0.5, 0);
  histogramStyle(*ptlead3Jet_[kJES09], kRed  , 1, 20, 0.5, 0);
  histogramStyle(*ptlead3Jet_[kData ], kBlack, 1, 22, 1.8, 0);
  if(!logartihmicPlots) axesStyle(*ptlead3Jet_[kStd], "p_{t}(jet 3)" , "events", 0, 1.2*ptlead3Jet_[kJES11]->GetBinContent(7));
  if(logartihmicPlots) axesStyle(*ptlead3Jet_[kStd], "p_{t}(jet 3)" , "events", 0.003*luminosity/1000., 10*ptlead3Jet_[kJES11]->GetBinContent(7));
  ptlead3Jet_[kStd     ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead3Jet_[kJES11   ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead3Jet_[kJES09   ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead3Jet_[kData    ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead3Jet_[kStd     ]->Draw("");
  ptlead3Jet_[kJES11   ]->Draw("same"); 
  ptlead3Jet_[kJES09   ]->Draw("same");
  ptlead3Jet_[kData    ]->Draw("p e1 same");
  JESleg                ->Draw("same");
  ++canvasNumber;

  // ---
  //    do the printing for the JES variations 4
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("JESvariationLead4Jet"+log);
  if(logartihmicPlots)MyCanvas[canvasNumber]->SetLogy(1);
  histogramStyle(*ptlead4Jet_[kStd  ], kBlack, 1, 20, 0.5, 0);
  histogramStyle(*ptlead4Jet_[kJES11], kBlue , 1, 20, 0.5, 0);
  histogramStyle(*ptlead4Jet_[kJES09], kRed  , 1, 20, 0.5, 0);
  histogramStyle(*ptlead4Jet_[kData ], kBlack, 1, 22, 1.8, 0);
  if(!logartihmicPlots) axesStyle(*ptlead4Jet_[kStd], "p_{t}(jet 4)" , "events", 0, 1.2*ptlead4Jet_[kJES11]->GetBinContent(7));
  if(logartihmicPlots) axesStyle(*ptlead4Jet_[kStd], "p_{t}(jet 4)" , "events", 0.0003*luminosity/1000., 10*ptlead4Jet_[kJES11]->GetBinContent(7));
  ptlead4Jet_[kStd     ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead4Jet_[kJES11   ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead4Jet_[kJES09   ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead4Jet_[kData    ]->GetXaxis()->SetRangeUser(30.,200.);
  ptlead4Jet_[kStd     ]->Draw("");
  ptlead4Jet_[kJES11   ]->Draw("same"); 
  ptlead4Jet_[kJES09   ]->Draw("same");
  ptlead4Jet_[kData    ]->Draw("p e1 same");
  JESleg                ->Draw("same");
  ++canvasNumber;

  // ---
  //    do the printing for the MET variation
  // ---
  MyCanvas[canvasNumber]->cd(0);
  MyCanvas[canvasNumber]->SetTitle("ABCDvariation"+log);
  if(logartihmicPlots)MyCanvas[canvasNumber]->SetLogy(1);
  histogramStyle(*yieldPt_[kStd    ], kBlack, 1, 20, 0.5, 0);
  histogramStyle(*yieldPt_[kQCDup  ], kBlue , 1, 20, 0.5, 0);
  histogramStyle(*yieldPt_[kQCDdown], kRed  , 1, 20, 0.5, 0);
  histogramStyle(*yieldPt_[kData   ], kBlack, 1, 22, 1.8, 0);
  if(!logartihmicPlots) axesStyle(*yieldPt_[kStd], "p_{t}(#mu)" , "events", 0, 1.6*yieldPt_[kStd]->GetMaximum());
  if(logartihmicPlots) axesStyle(*yieldPt_[kStd], "p_{t}(#mu)" , "events", 15., 10.*yieldPt_[kQCDup]->GetMaximum());
  yieldPt_[kStd         ]->Draw(""        );
  yieldPt_[kQCDup       ]->Draw("hist same"); 
  yieldPt_[kQCDdown     ]->Draw("hist same");
  yieldPt_[kData        ]->Draw("p e1 same");
  ABCDleg                ->Draw("same");
  ++canvasNumber;

  // ---
  // saving
  // ---
  if(save){   
    // ps
    MyCanvas[0]->Print(saveTo+"systematicShift"+lum+"nb"+log+".pdf(", "pdf");
    for(unsigned int idx=1; idx<MyCanvas.size()-1; idx++){
      MyCanvas[idx]->Print(saveTo+"systematicShift"+lum+"nb"+log+".pdf", "pdf");   
    }
    MyCanvas[MyCanvas.size()-1]->Print(saveTo+"systematicShift"+lum+"nb"+log+".pdf)", "pdf");
    
    // png
    for(unsigned int idx=0; idx<MyCanvas.size(); idx++){
      MyCanvas[idx]->Print(saveTo+(TString)(MyCanvas[idx]->GetTitle())+".png");      
    }
  }
}

void canvasStyle(TCanvas& canv) 
{
  canv.SetFillStyle   ( 4000);
  canv.SetLeftMargin  ( 0.20);
  canv.SetRightMargin ( 0.05);
  canv.SetBottomMargin( 0.15);
  canv.SetTopMargin   ( 0.05);
}

void histogramStyle(TH1& hist, int color, int lineStyle, int markerStyle, float markersize, int filled, int fillStyle) 
{
  hist.SetLineWidth(4);
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

template <class T>
void axesStyle(T& hist, const char* titleX, const char* titleY, float yMin, float yMax, float yTitleSize, float yTitleOffset) 
{
  hist.SetTitle("");
  hist.GetXaxis()->SetTitle(titleX);
  hist.GetXaxis()->CenterTitle();
  hist.GetXaxis()->SetTitleSize  ( 0.06);
  hist.GetXaxis()->SetTitleColor (    1);
  hist.GetXaxis()->SetTitleOffset(  1.0);
  hist.GetXaxis()->SetTitleFont  (   62);
  if((TString)typeid(hist).name()=="4TH1F"){
    hist.GetXaxis()->SetLabelSize  ( 0.05);
    hist.GetXaxis()->SetLabelFont  (   62);
    hist.GetXaxis()->SetNdivisions (  505);
  }
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

int roundToInt(double value){
  int result=0;
  // take care of negative numbers
  if(value<0){
    std::cout << "no negative numbers allowed in roundToInt" << std::endl;
    return 0;
  }
  // get [value]
  for(int x=0; value>x; ++x){
    result=x;
  }
  // see if rest is > 0.5
  //  value-result >=0.5 ? return result+1 : return result;
  if((value-result) >=0.5) return (result+1);
  return result;
}

TString getTStringFromInt(int i){
  char result[20];
  sprintf(result, "%i", i);
  return (TString)result;
}

double readLineFromFile(int line, TString file){
  // introduce function to read a double value drom a specific line of a file
  std::ifstream finDouble (file);
  std::string readIn;
  // check if file exists
  if (!finDouble){
    std::cout << "can not open file" << std::endl;
    return -1;
  }
  // loop lines of the file
  for(int l=1; !finDouble.eof(); ++l){
    // save line content in readIn
    getline(finDouble, readIn);
    // convert your chosen line into double and return it
    if(l==line) return atof(readIn.c_str()); 
  }
  // if line is not found
  std::cout << "can not find line" << std::endl;
  return -1.;  
}
