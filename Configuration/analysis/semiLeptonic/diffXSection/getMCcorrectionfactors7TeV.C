#include "basicFunctions.h"

void getMCcorrectionfactors(TString func = "exp"){

  // ---
  //    canvas style 
  // ---
  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  myStyle.cd();
  gROOT->SetStyle("HHStyle");

  // ---
  //    top Pt data / MC ratio
  // ---
  // a) l+jets data points
  int NbinsLjets=7;
  TGraphAsymmErrors* SFljets = new TGraphAsymmErrors(NbinsLjets);
  //           bin x(BCC)    data  / Madgraph 
  SFljets->SetPoint( 0, 26.2 , 0.004536 / 0.003806 );
  SFljets->SetPoint( 1, 88.8 , 0.006658 / 0.006574 );
  SFljets->SetPoint( 2, 126.2, 0.004740 / 0.004740 );
  SFljets->SetPoint( 3, 173.8, 0.002501 / 0.002748 );
  SFljets->SetPoint( 4, 228.8, 0.001042 / 0.001195 );
  SFljets->SetPoint( 5, 288.8, 0.000378 / 0.000454 );
  SFljets->SetPoint( 6, 356.2, 0.000120 / 0.000154 );
  //                   x errors   rel.err(data) *( data  / Madgraph)
  SFljets->SetPointError( 0, 0., 0., (4.4 /100.)*(0.004536 / 0.003806), (4.4 /100.)*(0.004536 / 0.003806) );
  SFljets->SetPointError( 1, 0., 0., (5.5 /100.)*(0.006658 / 0.006574), (5.5 /100.)*(0.006658 / 0.006574) );
  SFljets->SetPointError( 2, 0., 0., (4.0 /100.)*(0.004740 / 0.004740), (4.0 /100.)*(0.004740 / 0.004740) );
  SFljets->SetPointError( 3, 0., 0., (5.8 /100.)*(0.002501 / 0.002748), (5.8 /100.)*(0.002501 / 0.002748) );
  SFljets->SetPointError( 4, 0., 0., (6.2 /100.)*(0.001042 / 0.001195), (6.2 /100.)*(0.001042 / 0.001195) );
  SFljets->SetPointError( 5, 0., 0., (9.0 /100.)*(0.000378 / 0.000454), (9.0 /100.)*(0.000378 / 0.000454) );
  SFljets->SetPointError( 6, 0., 0., (11.1/100.)*(0.000120 / 0.000154), (11.1/100.)*(0.000120 / 0.000154) );
  //style of ratio
  SFljets->SetLineWidth(3);
  SFljets->SetMarkerSize(1.5);
  SFljets->SetMarkerStyle(20);
  SFljets->SetMarkerColor(kBlue);
  SFljets->SetLineColor(kBlue);

  // b) dilepton data points
  int NbinsDilep=5;
  TGraphAsymmErrors* SFdilep = new TGraphAsymmErrors(NbinsDilep);
  //           bin x(BCC)    data  / Madgraph 
  SFdilep->SetPoint( 0, 34 ,  (0.00509572 / 0.00453114 )  );
  SFdilep->SetPoint( 1, 106,  (0.00626002 / 0.00600115 )  );
  SFdilep->SetPoint( 2, 163,  (0.00296467 / 0.00321705 )  );
  SFdilep->SetPoint( 3, 247,  (0.000701592/ 0.000931674)  );
  SFdilep->SetPoint( 4, 350,  (0.00012036 / 0.000191065)  );
  //                   x errors   rel.err(data) *( data  / Madgraph)
  SFdilep->SetPointError( 0, 0., 0., 0.0601381*(0.00509572 / 0.00453114 ), 0.0601381*(0.00509572 / 0.00453114 ) );
  SFdilep->SetPointError( 1, 0., 0., 0.0469906*(0.00626002 / 0.00600115 ), 0.0469906*(0.00626002 / 0.00600115 ) );
  SFdilep->SetPointError( 2, 0., 0., 0.0555114*(0.00296467 / 0.00321705 ), 0.0555114*(0.00296467 / 0.00321705 ) );
  SFdilep->SetPointError( 3, 0., 0., 0.071274* (0.000701592/ 0.000931674), 0.071274* (0.000701592/ 0.000931674) );
  SFdilep->SetPointError( 4, 0., 0., 0.0924826*(0.00012036 / 0.000191065), 0.0924826*(0.00012036 / 0.000191065) );
  //style of ratio
  SFdilep->SetLineWidth(3);
  SFdilep->SetMarkerSize(1.5);
  SFdilep->SetMarkerStyle(22);
  SFdilep->SetMarkerColor(kGreen+2);
  SFdilep->SetLineColor(kGreen+2);

  // c) combined data points
  int Nbins=NbinsLjets+NbinsDilep;
  TGraphAsymmErrors* SF = new TGraphAsymmErrors(Nbins);
  //           bin x(BCC)    data  / Madgraph 
  SF->SetPoint( 0, 26.2 , 0.004536 / 0.003806 );
  SF->SetPoint( 1, 88.8 , 0.006658 / 0.006574 );
  SF->SetPoint( 2, 126.2, 0.004740 / 0.004740 );
  SF->SetPoint( 3, 173.8, 0.002501 / 0.002748 );
  SF->SetPoint( 4, 228.8, 0.001042 / 0.001195 );
  SF->SetPoint( 5, 288.8, 0.000378 / 0.000454 );
  SF->SetPoint( 6, 356.2, 0.000120 / 0.000154 );
  SF->SetPoint( 7, 34 ,  (0.00509572 / 0.00453114 )  );
  SF->SetPoint( 8, 106,  (0.00626002 / 0.00600115 )  );
  SF->SetPoint( 9, 163,  (0.00296467 / 0.00321705 )  );
  SF->SetPoint( 10, 247,  (0.000701592/ 0.000931674)  );
  SF->SetPoint( 11, 350,  (0.00012036 / 0.000191065)  );

  //                   x errors   rel.err(data) *( data  / Madgraph)
  SF->SetPointError( 0, 0., 0., (4.4 /100.)*(0.004536 / 0.003806), (4.4 /100.)*(0.004536 / 0.003806) );
  SF->SetPointError( 1, 0., 0., (5.5 /100.)*(0.006658 / 0.006574), (5.5 /100.)*(0.006658 / 0.006574) );
  SF->SetPointError( 2, 0., 0., (4.0 /100.)*(0.004740 / 0.004740), (4.0 /100.)*(0.004740 / 0.004740) );
  SF->SetPointError( 3, 0., 0., (5.8 /100.)*(0.002501 / 0.002748), (5.8 /100.)*(0.002501 / 0.002748) );
  SF->SetPointError( 4, 0., 0., (6.2 /100.)*(0.001042 / 0.001195), (6.2 /100.)*(0.001042 / 0.001195) );
  SF->SetPointError( 5, 0., 0., (9.0 /100.)*(0.000378 / 0.000454), (9.0 /100.)*(0.000378 / 0.000454) );
  SF->SetPointError( 6, 0., 0., (11.1/100.)*(0.000120 / 0.000154), (11.1/100.)*(0.000120 / 0.000154) );
  SF->SetPointError( 7, 0., 0., 0.0601381*(0.00509572 / 0.00453114 ), 0.0601381*(0.00509572 / 0.00453114 ) );
  SF->SetPointError( 8, 0., 0., 0.0469906*(0.00626002 / 0.00600115 ), 0.0469906*(0.00626002 / 0.00600115 ) );
  SF->SetPointError( 9, 0., 0., 0.0555114*(0.00296467 / 0.00321705 ), 0.0555114*(0.00296467 / 0.00321705 ) );
  SF->SetPointError( 10, 0., 0., 0.071274* (0.000701592/ 0.000931674), 0.071274* (0.000701592/ 0.000931674) );
  SF->SetPointError( 11, 0., 0., 0.0924826*(0.00012036 / 0.000191065), 0.0924826*(0.00012036 / 0.000191065) );

  //style of ratio
  SF->SetLineWidth(1);
  SF->SetMarkerSize(0.1);
  SF->SetMarkerStyle(20);
  SF->SetMarkerColor(kWhite);
  SF->SetLineColor(kWhite);

  // ---
  //    dummy plots for axis
  // ---
  TH1F* dummy= new TH1F("","",1,0.,400);
  histogramStyle(*dummy, kSig);
  dummy->GetXaxis()->SetTitle("p_{T} (top quark)");
  dummy->GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d#sigma}{dp_{T}^{t}}:  2011 data / Madgraph");
  dummy->SetMaximum(1.5);
  dummy->SetMinimum(0.5);

  // ---
  //    legend
  // ---
  TLegend *leg0 = new TLegend(0.4, 0.65, 0.9, 0.8);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("CMS 2011 dataset (5 fb^{-1})");
  leg0->AddEntry(SFljets, "e/#mu+Jets"    , "P");
  leg0->AddEntry(SFdilep, "ee/e#mu/#mu#mu", "P");

  // canvas
  std::vector<TCanvas*> plotCanvas_;
  addCanvas(plotCanvas_);
  plotCanvas_[plotCanvas_.size()-1]->cd(0);
  plotCanvas_[plotCanvas_.size()-1]->SetTitle("data/MC top Pt ratio");
  // drawing
  dummy->Draw("axis");
  SF->Draw("e same");
  SFljets->Draw("ep same");
  SFdilep->Draw("ep same");
  // fit polynomial or exponential function
  TString def = "";
  if(func=="pol2")def="[0]*x*x+[1]*x+[2]";
  if(func=="exp")def="exp([0]+[1]*x)";
  double fitLowEdge=0.;
  double fitHighEdge=400.;
  TF1* function=new TF1("function",def,fitLowEdge, fitHighEdge);
  SF->Fit(function,"R","same",fitLowEdge, fitHighEdge);
  for(int i=0; i<function->GetNumberFreeParameters(); i++){
    function->SetParameter(i,round(function->GetParameter(i),3));
  }
  leg0->AddEntry( function, "fit ("+function->GetExpFormula("p")+")", "L");
  leg0->Draw("same");
}
