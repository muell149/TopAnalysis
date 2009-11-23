
// ---------description----------
// --------------------------
// this Macro analzyes different Qualities of the Muon concerning Isolation: Endeposit in Hcal and Ecal,
// number of Hits around Track, Response in Ecal and Hcal, distance of mu to next jet for different Jet-pt-thresholds
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

enum styles {kAll, kSignal, kBackground, kQCD, kWmunu, kZmumu, kBoson};

void canvasStyle(TCanvas& canv);
void histogramStyle(TH1& hist, unsigned int style);
void axesStyle(TH1& hist, const char* titleX, const char* titleY);


void analyzeMuonIsolation(TString whichMuons = "tight") // choose between: "good" // "tight" // "loose" // "track" // "golden" // "combined" // "unselected"
{

 TString whichJets  = "Good";   // choose between "Unselected" and "Good"
  // ---
  //    set root style 
  // ---
  //gROOT->cd();
  //gROOT->SetStyle("Plain");

  // ---
  //    open input files
  // ---
  std::vector<TFile*> files_;
  files_.push_back(new TFile("./analyzeSemiLeptonicSelection_all.root"  ) );
  files_.push_back(new TFile("./analyzeSemiLeptonicSelection_sig.root"  ) );
  files_.push_back(new TFile("./analyzeSemiLeptonicSelection_bkg.root"  ) );
  files_.push_back(new TFile("./analyzeSemiLeptonicSelection_QCD.root"  ) );
  files_.push_back(new TFile("./analyzeSemiLeptonicSelection_Wmunu.root") );
  files_.push_back(new TFile("./analyzeSemiLeptonicSelection_Zmumu.root") );

  // ---
  //    get histograms
  // ---
  std::vector<TH1F*> relIso_, trkIso_, calIso_, trkIsoN_, eclIsoN_, hclIsoN_, jmudist20_, jmudist30_, jmudist40_;
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    relIso_   .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonQuality/relIso"  ) );
    trkIso_   .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonQuality/trkIso_" ) );
    calIso_   .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonQuality/calIso_" ) );
    trkIsoN_  .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonQuality/trkIsoN_") );
    eclIsoN_  .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonQuality/eclIsoN_") );
    hclIsoN_  .push_back( (TH1F*)files_[idx]->Get(whichMuons+"MuonQuality/hclIsoN_") );
    jmudist20_.push_back( (TH1F*)files_[idx]->Get(whichMuons+"Muon"+whichJets+"JetKinematics/dist20_") );
    jmudist30_.push_back( (TH1F*)files_[idx]->Get(whichMuons+"Muon"+whichJets+"JetKinematics/dist30_") );
    jmudist40_.push_back( (TH1F*)files_[idx]->Get(whichMuons+"Muon"+whichJets+"JetKinematics/dist40_") );
  }

  // ---
  //    close input files
  // ---
  for(unsigned int idx=0; idx<files_.size(); ++idx) {
    //files_[idx]->Close();
  }
  
  // ---
  // define weights concerning luminosity
  // ---
  std::vector<double> lumiweight;

  // add scaling factors here!
  lumiweight.push_back(1.0);
  lumiweight.push_back(1.0);
  lumiweight.push_back(1.0);
  lumiweight.push_back(1.0);
  lumiweight.push_back(1.0);
  lumiweight.push_back(1.0);

  // ttbar (all, bg, sg - coming from the same sample)
  //  lumiweight.push_back(0.0156);
  //  lumiweight.push_back(0.0156);
  // lumiweight.push_back(0.0156);
  // QCD
  //  lumiweight.push_back(1.1161);
  // Wmunu
  //  lumiweight.push_back(0.2212);
  // Zmumu
  //  lumiweight.push_back(0.0458);

  // ---
  // do lumiweighting and adding Vektor Bosons
  // ---
  relIso_[kWmunu     ]->Scale(lumiweight[kWmunu]);
  relIso_[kZmumu     ]->Scale(lumiweight[kZmumu]);
  relIso_.push_back( (TH1F*)relIso_[kWmunu]->Clone());
  relIso_[kBoson     ]->Add(relIso_[kZmumu]);
  relIso_[kQCD       ]->Scale(lumiweight[kQCD]);  
  //  relIso_[kAll]->Scale(lumiweight[kAll]);  
  relIso_[kSignal    ]->Scale(lumiweight[kSignal]); 
  relIso_[kBackground]->Scale(lumiweight[kBackground]); 

  trkIso_[kWmunu     ]->Scale(lumiweight[kWmunu]);
  trkIso_[kZmumu     ]->Scale(lumiweight[kZmumu]);
  trkIso_.push_back( (TH1F*)trkIso_[kWmunu]->Clone());
  trkIso_[kBoson     ]->Add(trkIso_[kZmumu]);
  trkIso_[kQCD       ]->Scale(lumiweight[kQCD]);  
  //  trkIso_[kAll]->Scale(lumiweight[kAll]);  
  trkIso_[kSignal    ]->Scale(lumiweight[kSignal]); 
  trkIso_[kBackground]->Scale(lumiweight[kBackground]); 

  calIso_[kWmunu     ]->Scale(lumiweight[kWmunu]);
  calIso_[kZmumu     ]->Scale(lumiweight[kZmumu]);
  calIso_.push_back( (TH1F*)calIso_[kWmunu]->Clone());
  calIso_[kBoson     ]->Add(calIso_[kZmumu]);
  calIso_[kQCD       ]->Scale(lumiweight[kQCD]);  
  //  calIso_[kAll]->Scale(lumiweight[kAll]);  
  calIso_[kSignal    ]->Scale(lumiweight[kSignal]); 
  calIso_[kBackground]->Scale(lumiweight[kBackground]); 

  trkIsoN_[kWmunu     ]->Scale(lumiweight[kWmunu]);
  trkIsoN_[kZmumu     ]->Scale(lumiweight[kZmumu]);
  trkIsoN_.push_back( (TH1F*)trkIsoN_[kWmunu]->Clone());
  trkIsoN_[kBoson     ]->Add(trkIsoN_[kZmumu]);
  trkIsoN_[kQCD       ]->Scale(lumiweight[kQCD]);  
  //  trkIsoN_[kAll   ]->Scale(lumiweight[kAll]);  
  trkIsoN_[kSignal    ]->Scale(lumiweight[kSignal]); 
  trkIsoN_[kBackground]->Scale(lumiweight[kBackground]);

  eclIsoN_[kWmunu     ]->Scale(lumiweight[kWmunu]);
  eclIsoN_[kZmumu     ]->Scale(lumiweight[kZmumu]);
  eclIsoN_.push_back( (TH1F*)eclIsoN_[kWmunu]->Clone());
  eclIsoN_[kBoson     ]->Add(eclIsoN_[kZmumu]);
  eclIsoN_[kQCD       ]->Scale(lumiweight[kQCD]);  
  //  eclIsoN_[kAll]->Scale(lumiweight[kAll]);  
  eclIsoN_[kSignal    ]->Scale(lumiweight[kSignal]); 
  eclIsoN_[kBackground]->Scale(lumiweight[kBackground]);

  hclIsoN_[kWmunu     ]->Scale(lumiweight[kWmunu]);
  hclIsoN_[kZmumu     ]->Scale(lumiweight[kZmumu]);
  hclIsoN_.push_back( (TH1F*)hclIsoN_[kWmunu]->Clone());
  hclIsoN_[kBoson     ]->Add(hclIsoN_[kZmumu]);
  hclIsoN_[kQCD       ]->Scale(lumiweight[kQCD]);  
  //  hclIsoN_[kAll]->Scale(lumiweight[kAll]);  
  hclIsoN_[kSignal    ]->Scale(lumiweight[kSignal]); 
  hclIsoN_[kBackground]->Scale(lumiweight[kBackground]);

  jmudist20_[kWmunu     ]->Scale(lumiweight[kWmunu]);
  jmudist20_[kZmumu     ]->Scale(lumiweight[kZmumu]);
  jmudist20_.push_back( (TH1F*)jmudist20_[kWmunu]->Clone());
  jmudist20_[kBoson     ]->Add(jmudist20_[kZmumu]);
  jmudist20_[kQCD       ]->Scale(lumiweight[kQCD]);  
  //  jmudist20_[kAll]->Scale(lumiweight[kAll]);  
  jmudist20_[kSignal    ]->Scale(lumiweight[kSignal]); 
  jmudist20_[kBackground]->Scale(lumiweight[kBackground]);

  //  std::cout<<"lumiweighting jmudist20 ok"<<std::endl;

  jmudist30_[kWmunu     ]->Scale(lumiweight[kWmunu]);
  jmudist30_[kZmumu     ]->Scale(lumiweight[kZmumu]);
  jmudist30_.push_back( (TH1F*)jmudist30_[kWmunu]->Clone());
  jmudist30_[kBoson     ]->Add(jmudist30_[kZmumu]);
  jmudist30_[kQCD       ]->Scale(lumiweight[kQCD]);  
  //  jmudist30_[kAll]->Scale(lumiweight[kAll]);  
  jmudist30_[kSignal    ]->Scale(lumiweight[kSignal]); 
  jmudist30_[kBackground]->Scale(lumiweight[kBackground]);

  jmudist40_[kWmunu     ]->Scale(lumiweight[kWmunu]);
  jmudist40_[kZmumu     ]->Scale(lumiweight[kZmumu]);
  jmudist40_.push_back( (TH1F*)jmudist40_[kWmunu]->Clone());
  jmudist40_[kBoson     ]->Add(jmudist40_[kZmumu]);
  jmudist40_[kQCD       ]->Scale(lumiweight[kQCD]);  
  //  jmudist40_[kAll]->Scale(lumiweight[kAll]);  
  jmudist40_[kSignal    ]->Scale(lumiweight[kSignal]); 
  jmudist40_[kBackground]->Scale(lumiweight[kBackground]);

  // ---
  //    configure histograms
  // ---

  // relIso_
  //  histogramStyle(*relIso_ [kAll       ], kAll       );
  histogramStyle(*relIso_ [kSignal    ], kSignal    );
  histogramStyle(*relIso_ [kBackground], kBackground);
  histogramStyle(*relIso_ [kQCD       ], kQCD       );
  //  histogramStyle(*relIso_ [kWmunu     ], kWmunu     );
  //  histogramStyle(*relIso_ [kZmumu     ], kZmumu     );
  histogramStyle(*relIso_ [kBoson     ], kBoson     );

  // trkIso_
  //  histogramStyle(*trkIso_ [kAll       ], kAll       );
  histogramStyle(*trkIso_ [kSignal    ], kSignal    );
  histogramStyle(*trkIso_ [kBackground], kBackground);
  histogramStyle(*trkIso_ [kQCD       ], kQCD       );   
  //  histogramStyle(*trkIso_ [kWmunu     ], kWmunu     );
  //  histogramStyle(*trkIso_ [kZmumu     ], kZmumu     );
  histogramStyle(*trkIso_ [kBoson     ], kBoson     );

  // calIso_
  //  histogramStyle(*calIso_ [kAll       ], kAll       );
  histogramStyle(*calIso_ [kSignal    ], kSignal    );
  histogramStyle(*calIso_ [kBackground], kBackground);
  histogramStyle(*calIso_ [kQCD       ], kQCD       ); 
  //  histogramStyle(*calIso_ [kWmunu     ], kWmunu     );
  //  histogramStyle(*calIso_ [kZmumu     ], kZmumu     );
  histogramStyle(*calIso_ [kBoson     ], kBoson     );

  // trkIsoN_
  //  histogramStyle(*trkIsoN_[kAll       ], kAll       );
  histogramStyle(*trkIsoN_[kSignal    ], kSignal    );
  histogramStyle(*trkIsoN_[kBackground], kBackground);
  histogramStyle(*trkIsoN_[kQCD       ], kQCD       ); 
  //  histogramStyle(*trkIsoN_[kWmunu     ], kWmunu     );
  //  histogramStyle(*trkIsoN_[kZmumu     ], kZmumu     );
  histogramStyle(*trkIsoN_[kBoson     ], kBoson     );

  // eclIsoN_
  //  histogramStyle(*eclIsoN_[kAll       ], kAll       );
  histogramStyle(*eclIsoN_[kSignal    ], kSignal    );
  histogramStyle(*eclIsoN_[kBackground], kBackground);
  histogramStyle(*eclIsoN_[kQCD       ], kQCD       ); 
  //  histogramStyle(*eclIsoN_[kWmunu     ], kWmunu     );
  //  histogramStyle(*eclIsoN_[kZmumu     ], kZmumu     );
  histogramStyle(*eclIsoN_[kBoson     ], kBoson     );

  // hclIsoN_
  //  histogramStyle(*hclIsoN_[kAll       ], kAll       );
  histogramStyle(*hclIsoN_[kSignal    ], kSignal    );
  histogramStyle(*hclIsoN_[kBackground], kBackground);
  histogramStyle(*hclIsoN_[kQCD       ], kQCD       ); 
  //  histogramStyle(*hclIsoN_[kWmunu     ], kWmunu     );
  //  histogramStyle(*hclIsoN_[kZmumu     ], kZmumu     );
  histogramStyle(*hclIsoN_[kBoson     ], kBoson     );

  // jmudist20
  //  histogramStyle(*jmudist20_[kAll       ], kAll       );
  histogramStyle(*jmudist20_[kSignal    ], kSignal    );
  histogramStyle(*jmudist20_[kBackground], kBackground);
  histogramStyle(*jmudist20_[kQCD       ], kQCD       ); 
  //  histogramStyle(*jmudist20_[kWmunu     ], kWmunu     );
  //  histogramStyle(*jmudist20_[kZmumu     ], kZmumu     );
  histogramStyle(*jmudist20_[kBoson     ], kBoson     );

  // jmudist30
  //  histogramStyle(*jmudist30_[kAll       ], kAll       );
  histogramStyle(*jmudist30_[kSignal    ], kSignal    );
  histogramStyle(*jmudist30_[kBackground], kBackground);
  histogramStyle(*jmudist30_[kQCD       ], kQCD       ); 
  histogramStyle(*jmudist30_[kWmunu     ], kWmunu     );
  histogramStyle(*jmudist30_[kZmumu     ], kZmumu     );
  //  histogramStyle(*jmudist30_[kBoson     ], kBoson     );

  // jmudist40
  //  histogramStyle(*jmudist40_[kAll       ], kAll       );
  histogramStyle(*jmudist40_[kSignal    ], kSignal    );
  histogramStyle(*jmudist40_[kBackground], kBackground);
  histogramStyle(*jmudist40_[kQCD       ], kQCD       ); 
  histogramStyle(*jmudist40_[kWmunu     ], kWmunu     );
  histogramStyle(*jmudist40_[kZmumu     ], kZmumu     );
  //  histogramStyle(*jmudist40_[kBoson     ], kBoson );

  // create a legend (in upper right corner)
  TLegend *leg0 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("Top-Antitop(Phythia)");
  //  leg0->AddEntry( relIso_ [kAll       ] , "ttbar inclusive"         , "PL" );
  leg0->AddEntry( relIso_ [kSignal    ] , "ttbar semi-lep. ( #mu )", "PL" );
  leg0->AddEntry( relIso_ [kBackground] , "ttbar other decays"     , "PL" );
  leg0->AddEntry( relIso_ [kQCD       ] , "QCD"                    , "PL" );
  //  leg0->AddEntry( relIso_ [kWmunu     ] , "W#mu#nu"                , "PL" );
  //  leg0->AddEntry( relIso_ [kZmumu     ] , "Z#mu#mu"                , "PL" );
  leg0->AddEntry( relIso_ [kBoson     ] , "W#mu#nu + Z#mu#mu"      , "PL" );

  // create a legend (in upper center)
  TLegend *leg1 = new TLegend(0.35, 0.65, 1.05, 0.9);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Top-Antitop(Phythia)");
  //  leg1->AddEntry( relIso_ [kAll       ] , "ttbar inclusive"         , "PL" );
  leg1->AddEntry( relIso_ [kSignal    ] , "ttbar semi-lep. ( #mu )" , "PL" );
  leg1->AddEntry( relIso_ [kBackground] , "ttbar other decays"      , "PL" );
  leg1->AddEntry( relIso_ [kQCD       ] , "QCD"                     , "PL" );
  //  leg1->AddEntry( relIso_ [kWmunu     ] , "W#mu#nu"                 , "PL" );
  //  leg1->AddEntry( relIso_ [kZmumu     ] , "Z#mu#mu"                 , "PL" );
  leg1->AddEntry( relIso_ [kBoson     ] , "W#mu#nu + Z#mu#mu"       , "PL" );

  // create an info legend containig the used mu-cut
   TLegend *leg2 = new TLegend(0.228, 0.912, 0.7818, 0.997);
  leg2->SetFillStyle(3001);
  leg2->SetBorderSize(0);
  leg2->SetHeader(whichMuons+" #mu");

  // create an info legend containig the used mu-cut and JetCut
   TLegend *leg3 = new TLegend(0.228, 0.912, 0.7818, 1.000);
  leg3->SetFillStyle(3001);
  leg3->SetBorderSize(0);
  leg3->SetHeader(whichMuons+" #mu, "+whichJets+ "Jets");

  // create a legend (in upper right corner)
  TLegend *leg4 = new TLegend(0.45, 0.65, 1.05, 0.9);
  leg4->SetFillStyle(0);
  leg4->SetBorderSize(0);
  leg4->SetHeader("Top-Antitop(Phythia)");
  //  leg0->AddEntry( relIso_ [kAll       ] , "ttbar inclusive"         , "PL" );
  leg4->AddEntry( relIso_ [kSignal    ] , "ttbar semi-lep. ( #mu )", "PL" );
  leg4->AddEntry( relIso_ [kBackground] , "ttbar other decays"     , "PL" );
  leg4->AddEntry( relIso_ [kQCD       ] , "QCD"                    , "PL" );
  leg4->AddEntry( jmudist30_ [kWmunu     ] , "W#mu#nu"                , "PL" );
  leg4->AddEntry( jmudist30_ [kZmumu     ] , "Z#mu#mu"                , "PL" );
  //  leg0->AddEntry( relIso_ [kBoson     ] , "W#mu#nu + Z#mu#mu"      , "PL" );

  // ---
  //    do the printing for relIso_
  // ---
  TCanvas* canv0 = new TCanvas("canv0", "canv0", 600, 600); canvasStyle(*canv0);
  
  // draw canvas
  canv0->cd(0);
  canv0->SetLogy(1);
  canv0->SetTitle("relative Isolation leading " +whichMuons+" #mu");
  axesStyle(*relIso_ [kSignal], "(#Sigma pt_{trk}+ #Sigma pt_{cal} )/pt(#mu), lead #mu", "events");
  double max=relIso_[kSignal]->GetMaximum();
  if(max<relIso_[kQCD       ]->GetMaximum())max=relIso_[kQCD]       ->GetMaximum();
  if(max<relIso_[kBackground]->GetMaximum())max=relIso_[kBackground]->GetMaximum();
  if(max<relIso_[kBoson     ]->GetMaximum())max=relIso_[kBoson     ]->GetMaximum();
  relIso_ [kSignal       ]->SetMinimum(1.);
  relIso_ [kSignal       ]->SetMaximum( 25* max );
  if(whichMuons=="tight"){
    relIso_[kSignal]->GetXaxis()->SetRangeUser(0.,0.08);   
  }
  relIso_ [kSignal       ]->Draw();
  //  relIso_ [kAll    ]->Draw("same");
  relIso_ [kBackground   ]->Draw("same");
  relIso_ [kQCD          ]->Draw("same");
  //  relIso_ [kWmunu     ]->Draw("same");
  //  relIso_ [kZmumu     ]->Draw("same");
  relIso_ [kBoson        ]->Draw("same");
  leg0                    ->Draw("same");
  leg2                    ->Draw("same");

  // ---
  //    do the printing for trkIso_
  // ---
  TCanvas* canv1 = new TCanvas("canv1", "canv1", 600, 600); canvasStyle(*canv1);

  // draw canvas
  canv1->cd(0);
  canv1->SetLogy(1);
  canv1->SetTitle("track Isolation leading " +whichMuons+" #mu");
  axesStyle(*trkIso_ [kSignal], "#Sigma pt_{trk} [GeV], lead #mu", "events");
  trkIso_ [kSignal       ]->SetMinimum(1.);
  max=trkIso_[kSignal]->GetMaximum();
  if(max<trkIso_[kQCD       ]->GetMaximum())max=trkIso_[kQCD]       ->GetMaximum();
  if(max<trkIso_[kBackground]->GetMaximum())max=trkIso_[kBackground]->GetMaximum();
  if(max<trkIso_[kBoson     ]->GetMaximum())max=trkIso_[kBoson     ]->GetMaximum();
  trkIso_ [kSignal       ]->SetMaximum( 25* max );
  trkIso_ [kSignal       ]->Draw();
  //  trkIso_ [kAll    ]->Draw("same");
  trkIso_ [kBackground   ]->Draw("same");
  trkIso_ [kQCD          ]->Draw("same");
  //  trkIso_ [kWmunu     ]->Draw("same");
  //  trkIso_ [kZmumu     ]->Draw("same");
  trkIso_ [kBoson        ]->Draw("same");
  leg0                    ->Draw("same");
  leg2                    ->Draw("same");

  // ---
  //    do the printing for calIso_
  // ---
  TCanvas* canv2 = new TCanvas("canv2", "canv2", 600, 600); canvasStyle(*canv2);

  // draw canvas
  canv2->cd(0);
  canv2->SetLogy(1);
  canv2->SetTitle("calo Isolation leading " +whichMuons+" #mu");
  axesStyle(*calIso_ [kSignal], "#Sigma pt_{cal}  [GeV], lead #mu", "events");
  calIso_ [kSignal       ]->SetMinimum(1.);
  max=calIso_[kSignal]->GetMaximum();
  if(max<calIso_[kQCD       ]->GetMaximum())max=calIso_[kQCD]       ->GetMaximum();
  if(max<calIso_[kBackground]->GetMaximum())max=calIso_[kBackground]->GetMaximum();
  if(max<calIso_[kBoson     ]->GetMaximum())max=calIso_[kBoson     ]->GetMaximum();
  calIso_ [kSignal       ]->SetMaximum( 25* max );
  calIso_ [kSignal       ]->Draw();
  //  calIso_ [kAll          ]->Draw("same");
  calIso_ [kBackground   ]->Draw("same");
  calIso_ [kQCD          ]->Draw("same");
  //  calIso_ [kWmunu     ]->Draw("same");
  //  calIso_ [kZmumu     ]->Draw("same");
  calIso_ [kBoson        ]->Draw("same");
  leg0                    ->Draw("same");
  leg2                    ->Draw("same");

  // ---
  //    do the printing for trkIsoN_
  // ---
  TCanvas* canv3 = new TCanvas("canv3", "canv3", 600, 600); canvasStyle(*canv3);

  // draw canvas
  canv3->cd(0);
  canv3->SetLogy(1);
  canv3->SetTitle("Number of activated Towers around Track " +whichMuons+" #mu");
  axesStyle(*trkIsoN_[kSignal], "#Sigma N_{trk}, lead #mu", "events");
  trkIsoN_[kSignal       ]->SetMinimum(1.);
  max=trkIsoN_[kSignal]->GetMaximum();
  if(max<trkIsoN_[kQCD       ]->GetMaximum())max=trkIsoN_[kQCD]       ->GetMaximum();
  if(max<trkIsoN_[kBackground]->GetMaximum())max=trkIsoN_[kBackground]->GetMaximum();
  if(max<trkIsoN_[kBoson     ]->GetMaximum())max=trkIsoN_[kBoson     ]->GetMaximum();
  trkIsoN_[kSignal       ]->SetMaximum( 100.0* max );
  if(whichMuons=="tight"){
    trkIsoN_[kSignal]->GetXaxis()->SetRangeUser(0.,10.);   
  }
  trkIsoN_[kSignal       ]->Draw();
  // trkIsoN_[kAll    ]->Draw("same");
  trkIsoN_[kBackground]->Draw("same");
  trkIsoN_[kQCD          ]->Draw("same");
  //  trkIsoN_ [kWmunu     ]->Draw("same");
  //  trkIsoN_ [kZmumu     ]->Draw("same");
  trkIsoN_[kBoson        ]->Draw("same");
  leg1                     ->Draw("same");
  leg2                    ->Draw("same");

  // ---
  //    do the printing for eclIsoN_
  // ---
  TCanvas* canv4 = new TCanvas("canv4", "canv4", 600, 600); canvasStyle(*canv4);

  // draw canvas
  canv4->cd(0);
  canv4->SetLogy(1);
  canv4->SetTitle("Number of activated ecalCells " +whichMuons+" #mu");
  axesStyle(*eclIsoN_[kSignal], "#Sigma N_{ecal}, lead #mu", "events");
  eclIsoN_[kSignal       ]->SetMinimum( 1.);
  max=eclIsoN_[kSignal]->GetMaximum();
  if(max<eclIsoN_[kQCD       ]->GetMaximum())max=eclIsoN_[kQCD]       ->GetMaximum();
  if(max<eclIsoN_[kBackground]->GetMaximum())max=eclIsoN_[kBackground]->GetMaximum();
  if(max<eclIsoN_[kBoson     ]->GetMaximum())max=eclIsoN_[kBoson     ]->GetMaximum();
  eclIsoN_[kSignal       ]->SetMaximum( 50.0* max);
  if(whichMuons=="tight"){
    eclIsoN_[kSignal]->GetXaxis()->SetRangeUser(0.,12.);   
  }
  eclIsoN_[kSignal       ]->Draw();
  //  eclIsoN_[kAll          ]->Draw("same");
  eclIsoN_[kBackground   ]->Draw("same");
  eclIsoN_[kQCD          ]->Draw("same");
  //  eclIsoN_ [kWmunu     ]->Draw("same");
  //  eclIsoN_ [kZmumu     ]->Draw("same");
  eclIsoN_[kBoson        ]->Draw("same");
  leg1                    ->Draw("same");
  leg2                    ->Draw("same");

  // ---
  //    do the printing for hclIsoN_
  // ---
  TCanvas* canv5 = new TCanvas("canv5", "canv5", 600, 600); canvasStyle(*canv5);

  // draw canvas
  canv5->cd(0);
  canv5->SetLogy(1);
  canv5->SetTitle("Number of activated hcalCells " +whichMuons+" #mu");
  axesStyle(*hclIsoN_[kSignal], "#Sigma N_{hcal}, lead #mu", "events");
  hclIsoN_[kSignal       ]->SetMinimum( 1. );
  max=hclIsoN_[kSignal]->GetMaximum();
  if(max<hclIsoN_[kQCD       ]->GetMaximum())max=hclIsoN_[kQCD]       ->GetMaximum();
  if(max<hclIsoN_[kBackground]->GetMaximum())max=hclIsoN_[kBackground]->GetMaximum();
  if(max<hclIsoN_[kBoson     ]->GetMaximum())max=hclIsoN_[kBoson     ]->GetMaximum();
  hclIsoN_[kSignal       ]->SetMaximum( 2.5* max );
  if(whichMuons=="tight"){
    hclIsoN_[kSignal]->GetXaxis()->SetRangeUser(0.,7);   
  }
  hclIsoN_[kSignal       ]->Draw();
  //  hclIsoN_[kAll    ]->Draw("same");
  hclIsoN_[kBackground   ]->Draw("same");
  hclIsoN_[kQCD          ]->Draw("same");
  //  hclIsoN_ [kWmunu     ]->Draw("same");
  //  hclIsoN_ [kZmumu     ]->Draw("same");
  hclIsoN_[kBoson        ]->Draw("same");
  leg1                    ->Draw("same");
  leg2                    ->Draw("same");


  // ---
  //    do the printing for jmudist20
  // ---
  TCanvas* canv6 = new TCanvas("canv6", "canv6", 600, 600); canvasStyle(*canv6);

  // draw canvas
  canv6->cd(0);
  canv6->SetLogy(1);
  canv6->SetTitle("distance " +whichMuons+" #mu and " +whichJets+ " Jets, pt> 20");
  axesStyle(*jmudist20_[kSignal], "#DeltaR (#mu - Jet( p_{t}>20 GeV ))", "events");
  //  jmudist20_[kSignal       ]->SetMinimum( 1.);
  max=jmudist20_[kSignal]->GetMaximum();
  if(max<jmudist20_[kQCD       ]->GetMaximum())max=jmudist20_[kQCD]       ->GetMaximum();
  if(max<jmudist20_[kBackground]->GetMaximum())max=jmudist20_[kBackground]->GetMaximum();
  if(max<jmudist20_[kBoson     ]->GetMaximum())max=jmudist20_[kBoson     ]->GetMaximum();
  jmudist20_[kSignal       ]->SetMaximum( 100*max );
  jmudist20_[kSignal       ]->Draw();
  //  jmudist20_[kAll    ]->Draw("same");
  jmudist20_[kBackground   ]->Draw("same");
  jmudist20_[kQCD          ]->Draw("same");
  //  jmudist20_ [kWmunu     ]->Draw("same");
  //  jmudist20_ [kZmumu     ]->Draw("same");
  jmudist20_[kBoson        ]->Draw("same");
  leg0                      ->Draw("same");
  leg3                      ->Draw("same");

  // ---
  //    do the printing for jmudist30
  // ---
  TCanvas* canv7 = new TCanvas("canv7", "canv7", 600, 600); canvasStyle(*canv7);

  // draw canvas
  canv7->cd(0);
  canv7->SetLogy(1);
  canv7->SetTitle("distance " +whichMuons+" #mu and " +whichJets+ " Jets, pt> 30");
  axesStyle(*jmudist30_[kSignal], "#DeltaR (#mu - Jet( p_{t}>30 GeV ))", "events");
  jmudist30_[kSignal      ]->SetMinimum( 1.);
  max=jmudist30_[kSignal]->GetMaximum();
  if(max<jmudist30_[kQCD       ]->GetMaximum())max=jmudist30_[kQCD]       ->GetMaximum();
  if(max<jmudist30_[kBackground]->GetMaximum())max=jmudist30_[kBackground]->GetMaximum();
  if(max<jmudist30_[kWmunu     ]->GetMaximum())max=jmudist30_[kWmunu     ]->GetMaximum();
  if(max<jmudist30_[kZmumu     ]->GetMaximum())max=jmudist30_[kZmumu     ]->GetMaximum();
//  if(max<jmudist30_[kBoson     ]->GetMaximum())max=jmudist30_[kBoson     ]->GetMaximum();
  jmudist30_[kSignal      ]->SetMaximum( 100*max );
  jmudist30_[kSignal      ]->Draw();
  //  jmudist30_[kAll    ]->Draw("same");
  jmudist30_[kBackground  ]->Draw("same");
  jmudist30_[kQCD         ]->Draw("same");
  jmudist30_ [kWmunu     ]->Draw("same");
  jmudist30_ [kZmumu     ]->Draw("same");
  //  jmudist30_[kBoson       ]->Draw("same");
  leg4                     ->Draw("same");
  leg3                     ->Draw("same");

  // ---
  //    do the printing for jmudist40
  // ---
  TCanvas* canv8 = new TCanvas("canv8", "canv8", 600, 600); canvasStyle(*canv8);

  // draw canvas
  canv8->cd(0);
  canv8->SetLogy(1);
  canv8->SetTitle("distance " +whichMuons+" #mu and " +whichJets+ " Jets, pt> 40");
  axesStyle(*jmudist40_[kSignal], "#DeltaR (#mu - Jet( p_{t}>40 GeV ))", "events");
  jmudist40_[kSignal      ]->SetMinimum( 1.);
  max=jmudist40_[kSignal]->GetMaximum();
  if(max<jmudist40_[kQCD       ]->GetMaximum())max=jmudist40_[kQCD]       ->GetMaximum();
  if(max<jmudist40_[kBackground]->GetMaximum())max=jmudist40_[kBackground]->GetMaximum();
  if(max<jmudist40_[kWmunu     ]->GetMaximum())max=jmudist40_[kWmunu     ]->GetMaximum();
  if(max<jmudist40_[kZmumu     ]->GetMaximum())max=jmudist40_[kZmumu     ]->GetMaximum();
  //  if(max<jmudist40_[kBoson     ]->GetMaximum())max=jmudist40_[kBoson     ]->GetMaximum();
  jmudist40_[kSignal      ]->SetMaximum( 100*max );
  jmudist40_[kSignal      ]->Draw();
  //  jmudist40_[kAll    ]->Draw("same");
  jmudist40_[kBackground  ]->Draw("same");
  jmudist40_[kQCD         ]->Draw("same");
  jmudist40_ [kWmunu     ]->Draw("same");
  jmudist40_ [kZmumu     ]->Draw("same");
  //  jmudist40_[kBoson       ]->Draw("same");
  leg4                     ->Draw("same");
  leg3                     ->Draw("same");

  // ---
  // saving
  // ---

 //pictures

//   canv0->Print("./analyzeMuonCutflow/relIso"+whichMuons+"Muons.png"                );
//   canv1->Print("./analyzeMuonCutflow/trackIso"+whichMuons+"Muons.png"              );
//   canv2->Print("./analyzeMuonCutflow/caloIso"+whichMuons+"Muons.png"               );
//   canv3->Print("./analyzeMuonCutflow/trackIsoNum"+whichMuons+"Muons.png"           );
//   canv4->Print("./analyzeMuonCutflow/ecalIsoN"+whichMuons+"Muons.png"              );
//   canv5->Print("./analyzeMuonCutflow/hcalIsoN"+whichMuons+"Muons.png"              );
//   canv6->Print("./analyzeMuonCutflow/dist20"+whichMuons+"Muons"+whichJets+"Jet.png");  
//   canv7->Print("./analyzeMuonCutflow/dist40"+whichMuons+"Muons"+whichJets+"Jet.png");  
  

  //psfile

  canv0->Print("./analyzeMuonCutflow/Isolation"+whichMuons+"Muons"+whichJets+"Jet.ps(");
  canv1->Print("./analyzeMuonCutflow/Isolation"+whichMuons+"Muons"+whichJets+"Jet.ps" );
  canv2->Print("./analyzeMuonCutflow/Isolation"+whichMuons+"Muons"+whichJets+"Jet.ps" );
  canv3->Print("./analyzeMuonCutflow/Isolation"+whichMuons+"Muons"+whichJets+"Jet.ps" );
  canv4->Print("./analyzeMuonCutflow/Isolation"+whichMuons+"Muons"+whichJets+"Jet.ps" );
  canv5->Print("./analyzeMuonCutflow/Isolation"+whichMuons+"Muons"+whichJets+"Jet.ps" );
  canv6->Print("./analyzeMuonCutflow/Isolation"+whichMuons+"Muons"+whichJets+"Jet.ps" );
  canv7->Print("./analyzeMuonCutflow/Isolation"+whichMuons+"Muons"+whichJets+"Jet.ps" );
  canv8->Print("./analyzeMuonCutflow/Isolation"+whichMuons+"Muons"+whichJets+"Jet.ps)");

}

void canvasStyle(TCanvas& canv) 
{
  //  canv.SetFillStyle   ( 4000);
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
  color.push_back( kBlack );
  color.push_back( kBlack );



  // pre-defined fill style
  std::vector<int> fill;
  fill.push_back( 1   ); 
  fill.push_back( 3004); 
  fill.push_back( 1   );
  fill.push_back( 1   );
  fill.push_back( 1   );
  fill.push_back( 1   );
  fill.push_back( 1   );

  // pre-defined marker style
  std::vector<int> marker;
  marker.push_back( 20);

  // set line width
  style==kAll ? hist.SetLineWidth(6) : hist.SetLineWidth(3);

  hist.SetStats(kFALSE);
  hist.SetLineColor  (color[style]);
  hist.SetFillColor  (color[style]);
  hist.SetMarkerColor(color[style]);
  hist.SetFillStyle  (fill [style]);

  if(style==kAll){
    hist.SetMarkerStyle(marker[style]);
    hist.SetMarkerSize(1.4);
  }
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
