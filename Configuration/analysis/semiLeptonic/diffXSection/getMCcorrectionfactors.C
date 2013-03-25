#include "basicFunctions.h"

void getMCcorrectionfactors(TString func = "exp"){

  // ---
  //    canvas style 
  // ---
  TStyle myStyle("HHStyle","HHStyle");
  setHHStyle(myStyle);
  myStyle.SetErrorX(0.5);
  myStyle.cd();
  gROOT->SetStyle("HHStyle");
  gStyle->SetEndErrorSize(10);
  gStyle->SetOptFit(0);

  // ---
  //    top Pt data / MC ratio
  // ---
  // a) l+jets 7TeV data points
  int NbinsLjets7=7;
  TGraphAsymmErrors* SFljets = new TGraphAsymmErrors(NbinsLjets7);
  //           bin x(BCC)    data  / Madgraph         // BCCNNLO // BCC MG
  SFljets->SetPoint( 0, 28   , 0.004536 / 0.003806 ); //28       // 26.2
  SFljets->SetPoint( 1, 85.6 , 0.006658 / 0.006574 ); //85.6     // 88.8
  SFljets->SetPoint( 2, 125  , 0.004740 / 0.004740 ); //125      // 126.2
  SFljets->SetPoint( 3, 173.6, 0.002501 / 0.002748 ); //173.6    // 173.8
  SFljets->SetPoint( 4, 227.5, 0.001042 / 0.001195 ); //227.5    // 228.8
  SFljets->SetPoint( 5, 287.3, 0.000378 / 0.000454 ); //287.3    // 288.8
  SFljets->SetPoint( 6, 355.8, 0.000120 / 0.000154 ); //355.8    // 356.2
  //                   x errors   rel.err(data) *( data  / Madgraph)
  SFljets->SetPointError( 0, 0., 0., (4.4 /100.)*(0.004536 / 0.003806), (4.4 /100.)*(0.004536 / 0.003806) );
  SFljets->SetPointError( 1, 0., 0., (5.5 /100.)*(0.006658 / 0.006574), (5.5 /100.)*(0.006658 / 0.006574) );
  SFljets->SetPointError( 2, 0., 0., (4.0 /100.)*(0.004740 / 0.004740), (4.0 /100.)*(0.004740 / 0.004740) );
  SFljets->SetPointError( 3, 0., 0., (5.8 /100.)*(0.002501 / 0.002748), (5.8 /100.)*(0.002501 / 0.002748) );
  SFljets->SetPointError( 4, 0., 0., (6.2 /100.)*(0.001042 / 0.001195), (6.2 /100.)*(0.001042 / 0.001195) );
  SFljets->SetPointError( 5, 0., 0., (9.0 /100.)*(0.000378 / 0.000454), (9.0 /100.)*(0.000378 / 0.000454) );
  SFljets->SetPointError( 6, 0., 0., (11.1/100.)*(0.000120 / 0.000154), (11.1/100.)*(0.000120 / 0.000154) );
  //style of ratio
  SFljets->SetLineWidth(3.);
  SFljets->SetMarkerSize(1.5);
  SFljets->SetMarkerStyle(26);
  SFljets->SetMarkerColor(kRed+1);
  SFljets->SetLineColor(kRed+1);

  // b) dilepton 7TeV data points
  int NbinsDilep7=5;
  TGraphAsymmErrors* SFdilep = new TGraphAsymmErrors(NbinsDilep7);
  //           bin x(BCC)    data  / Madgraph               // BCCNNLO // BCC MG
  SFdilep->SetPoint( 0, 33.7,  (0.00509572 / 0.00453114 )  );// 33.7    // 34 
  SFdilep->SetPoint( 1, 107 ,  (0.00626002 / 0.00600115 )  );// 106     // 107
  SFdilep->SetPoint( 2, 162 ,  (0.00296467 / 0.00321705 )  );// 162     // 163
  SFdilep->SetPoint( 3, 242 ,  (0.000701592/ 0.000931674)  );// 242     // 247
  SFdilep->SetPoint( 4, 343 ,  (0.00012036 / 0.000191065)  );// 343     // 350
  //                   x errors   rel.err(data) *( data  / Madgraph)
  SFdilep->SetPointError( 0, 0., 0., 0.0601381*(0.00509572 / 0.00453114 ), 0.0601381*(0.00509572 / 0.00453114 ) );
  SFdilep->SetPointError( 1, 0., 0., 0.0469906*(0.00626002 / 0.00600115 ), 0.0469906*(0.00626002 / 0.00600115 ) );
  SFdilep->SetPointError( 2, 0., 0., 0.0555114*(0.00296467 / 0.00321705 ), 0.0555114*(0.00296467 / 0.00321705 ) );
  SFdilep->SetPointError( 3, 0., 0., 0.071274* (0.000701592/ 0.000931674), 0.071274* (0.000701592/ 0.000931674) );
  SFdilep->SetPointError( 4, 0., 0., 0.0924826*(0.00012036 / 0.000191065), 0.0924826*(0.00012036 / 0.000191065) );
  //style of ratio
  SFdilep->SetLineWidth(3.);
  SFdilep->SetMarkerSize(1.5);
  SFdilep->SetMarkerStyle(22);
  SFdilep->SetMarkerColor(kOrange+7);
  SFdilep->SetLineColor(kOrange+7);

  // c) l+jets 8TeV data points
  int NbinsLjets8=7;
  TGraphAsymmErrors* SFljets8 = new TGraphAsymmErrors(NbinsLjets8);
  //           bin x(BCC)    data  / Madgraph          // BCCNNLO // BCC MG
  SFljets8->SetPoint( 0, 28.  , 0.004350 / 0.003695 ); //28       //26.2
  SFljets8->SetPoint( 1, 86.  , 0.006638 / 0.006477 ); //86       //90
  SFljets8->SetPoint( 2, 125. , 0.004787 / 0.005077 ); //125	  //126.2
  SFljets8->SetPoint( 3, 173. , 0.002629 / 0.002795 ); //173	  //173.8
  SFljets8->SetPoint( 4, 227.3, 0.001069 / 0.001246 ); //227.3	  //228.8
  SFljets8->SetPoint( 5, 288. , 0.000394 / 0.000491 ); //288	  //286.2
  SFljets8->SetPoint( 6, 356. , 0.000126 / 0.000177 ); //356      //356.2
  //                   x errors   rel.err(data) *( data  / Madgraph)

  SFljets8->SetPointError( 0, 0., 0., (4.3 /100.)*(0.004350 / 0.003695), (4.3 /100.)*(0.004350 / 0.003695) );
  SFljets8->SetPointError( 1, 0., 0., (4.0 /100.)*(0.006638 / 0.006477), (4.0 /100.)*(0.006638 / 0.006477) );
  SFljets8->SetPointError( 2, 0., 0., (3.8 /100.)*(0.004787 / 0.005077), (3.8 /100.)*(0.004787 / 0.005077) );
  SFljets8->SetPointError( 3, 0., 0., (5.1 /100.)*(0.002629 / 0.002795), (5.1 /100.)*(0.002629 / 0.002795) );
  SFljets8->SetPointError( 4, 0., 0., (4.6 /100.)*(0.001069 / 0.001246), (4.6 /100.)*(0.001069 / 0.001246) );
  SFljets8->SetPointError( 5, 0., 0., (6.5 /100.)*(0.000394 / 0.000491), (6.5 /100.)*(0.000394 / 0.000491) );
  SFljets8->SetPointError( 6, 0., 0., (9.0 /100.)*(0.000126 / 0.000177), (9.0 /100.)*(0.000126 / 0.000177) );
  whipEmptyBinsAway(SFljets8, 0);

  //style of ratio
  SFljets8->SetLineWidth(3.);
  SFljets8->SetMarkerSize(1.5);
  SFljets8->SetMarkerStyle(24);
  //SFljets8->SetLineStyle(2);
  SFljets8->SetMarkerColor(kBlue);
  SFljets8->SetLineColor(kBlue);


  // d) dilepton 8TeV data points
  int NbinsDilep8=5;
  TGraphAsymmErrors* SFdilep8 = new TGraphAsymmErrors(NbinsDilep8);
  //           bin x(BCC)    data  / Madgraph            // BCCNNLO // BCC MG
  SFdilep8->SetPoint( 0, 35.4, (0.0051166/ 0.00441149 ) );//35.4     // 35
  SFdilep8->SetPoint( 1, 106 , (0.0058072/ 0.00595931 ) );//106      // 105
  SFdilep8->SetPoint( 2, 163 , (0.0030113/ 0.00328498 ) );//163      // 165
  SFdilep8->SetPoint( 3, 242 , (0.00084306/0.000978855) );//242      // 245
  SFdilep8->SetPoint( 4, 343 , (0.00016226/0.000212811) );//343      // 350
  //                   x errors   rel.err(data) *( data  / Madgraph)
  SFdilep8->SetPointError( 0, 0.,0., (5.6 /100.)*(0.0051166 /0.00441149 ), (5.6 /100.)*(0.0051166 /0.00441149 ) );
  SFdilep8->SetPointError( 1, 0.,0., (5.2 /100.)*(0.0058072 /0.00595931 ), (5.2 /100.)*(0.0058072 /0.00595931 ) );
  SFdilep8->SetPointError( 2, 0.,0., (5.61/100.)*(0.0030113 /0.00328498 ), (5.61/100.)*(0.0030113 /0.00328498 ) );
  SFdilep8->SetPointError( 3, 0.,0., (5.29/100.)*(0.00084306/0.000978855), (5.29/100.)*(0.00084306/0.000978855) );
  SFdilep8->SetPointError( 4, 0.,0., (9.31/100.)*(0.00016226/0.000212811), (9.31/100.)*(0.00016226/0.000212811) );

  //style of ratio
  SFdilep8->SetLineWidth(3.);
  SFdilep8->SetMarkerSize(1.5);
  SFdilep8->SetMarkerStyle(20);
  SFdilep8->SetMarkerColor(kAzure+6);
  SFdilep8->SetLineColor(kAzure+6);

  // e) combined 7+8TeV data points
  int Nbins=NbinsLjets7+NbinsDilep7+NbinsLjets8+NbinsDilep8;
  TGraphAsymmErrors* SF = new TGraphAsymmErrors(Nbins);
  //           bin x(BCC)    data  / Madgraph         // BCCNNLO // BCC MG
  SF->SetPoint( 0, 28   , 0.004536 / 0.003806 ); //28       // 26.2
  SF->SetPoint( 1, 85.6 , 0.006658 / 0.006574 ); //85.6     // 88.8
  SF->SetPoint( 2, 125  , 0.004740 / 0.004740 ); //125      // 126.2
  SF->SetPoint( 3, 173.6, 0.002501 / 0.002748 ); //173.6    // 173.8
  SF->SetPoint( 4, 227.5, 0.001042 / 0.001195 ); //227.5    // 228.8
  SF->SetPoint( 5, 287.3, 0.000378 / 0.000454 ); //287.3    // 288.8
  SF->SetPoint( 6, 355.8, 0.000120 / 0.000154 ); //355.8    // 356.2
  SF->SetPoint( 7, 33.7,  (0.00509572 / 0.00453114 )  );// 33.7    // 34 
  SF->SetPoint( 8, 107 ,  (0.00626002 / 0.00600115 )  );// 106     // 107
  SF->SetPoint( 9, 162 ,  (0.00296467 / 0.00321705 )  );// 162     // 163
  SF->SetPoint( 10, 242 ,  (0.000701592/ 0.000931674)  );// 242     // 247
  SF->SetPoint( 11, 343 ,  (0.00012036 / 0.000191065)  );// 343     // 350
  SF->SetPoint( 12, 28.  , 0.004350 / 0.003695 ); //28       //26.2
  SF->SetPoint( 13, 86.  , 0.006638 / 0.006477 ); //86       //90
  SF->SetPoint( 14, 125. , 0.004787 / 0.005077 ); //125	  //126.2
  SF->SetPoint( 15, 173. , 0.002629 / 0.002795 ); //173	  //173.8
  SF->SetPoint( 16, 227.3, 0.001069 / 0.001246 ); //227.3	  //228.8
  SF->SetPoint( 17, 288. , 0.000394 / 0.000491 ); //288	  //286.2
  SF->SetPoint( 18, 356. , 0.000126 / 0.000177 ); //356      //356.2
  SF->SetPoint( 19, 35.4, (0.0051166/ 0.00441149 ) );//35.4     // 35
  SF->SetPoint( 20, 106 , (0.0058072/ 0.00595931 ) );//106      // 105
  SF->SetPoint( 21, 163 , (0.0030113/ 0.00328498 ) );//163      // 165
  SF->SetPoint( 22, 242 , (0.00084306/0.000978855) );//242      // 245
  SF->SetPoint( 23, 343 , (0.00016226/0.000212811) );//343      // 350
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
  SF->SetPointError( 12, 0., 0., (4.3 /100.)*(0.004350 / 0.003695), (4.3 /100.)*(0.004350 / 0.003695) );
  SF->SetPointError( 13, 0., 0., (4.0 /100.)*(0.006638 / 0.006477), (4.0 /100.)*(0.006638 / 0.006477) );
  SF->SetPointError( 14, 0., 0., (3.8 /100.)*(0.004787 / 0.005077), (3.8 /100.)*(0.004787 / 0.005077) );
  SF->SetPointError( 15, 0., 0., (5.1 /100.)*(0.002629 / 0.002795), (5.1 /100.)*(0.002629 / 0.002795) );
  SF->SetPointError( 16, 0., 0., (4.6 /100.)*(0.001069 / 0.001246), (4.6 /100.)*(0.001069 / 0.001246) );
  SF->SetPointError( 17, 0., 0., (6.5 /100.)*(0.000394 / 0.000491), (6.5 /100.)*(0.000394 / 0.000491) );
  SF->SetPointError( 18, 0., 0., (9.0 /100.)*(0.000126 / 0.000177), (9.0 /100.)*(0.000126 / 0.000177) );
  SF->SetPointError( 19, 0.,0., (5.6 /100.)*(0.0051166 /0.00441149 ), (5.6 /100.)*(0.0051166 /0.00441149 ) );
  SF->SetPointError( 20, 0.,0., (5.2 /100.)*(0.0058072 /0.00595931 ), (5.2 /100.)*(0.0058072 /0.00595931 ) );
  SF->SetPointError( 21, 0.,0., (5.61/100.)*(0.0030113 /0.00328498 ), (5.61/100.)*(0.0030113 /0.00328498 ) );
  SF->SetPointError( 22, 0.,0., (5.29/100.)*(0.00084306/0.000978855), (5.29/100.)*(0.00084306/0.000978855) );
  SF->SetPointError( 23, 0.,0., (9.31/100.)*(0.00016226/0.000212811), (9.31/100.)*(0.00016226/0.000212811) );
  //style of ratio
  SF->SetLineWidth(3.);
  SF->SetMarkerSize(0.1);
  SF->SetMarkerStyle(20);
  SF->SetMarkerColor(kWhite);
  SF->SetLineColor(kWhite);

  // f) combined 7 TeV data points
  int Nbins7=NbinsLjets7+NbinsDilep7;
  TGraphAsymmErrors* SF7 = new TGraphAsymmErrors(Nbins7);
  //           bin x(BCC)    data  / Madgraph         // BCCNNLO // BCC MG
  SF7->SetPoint( 0, 28   , 0.004536 / 0.003806 ); //28       // 26.2
  SF7->SetPoint( 1, 85.6 , 0.006658 / 0.006574 ); //85.6     // 88.8
  SF7->SetPoint( 2, 125  , 0.004740 / 0.004740 ); //125      // 126.2
  SF7->SetPoint( 3, 173.6, 0.002501 / 0.002748 ); //173.6    // 173.8
  SF7->SetPoint( 4, 227.5, 0.001042 / 0.001195 ); //227.5    // 228.8
  SF7->SetPoint( 5, 287.3, 0.000378 / 0.000454 ); //287.3    // 288.8
  SF7->SetPoint( 6, 355.8, 0.000120 / 0.000154 ); //355.8    // 356.2
  SF7->SetPoint( 7, 33.7,  (0.00509572 / 0.00453114 )  );// 33.7    // 34 
  SF7->SetPoint( 8, 107 ,  (0.00626002 / 0.00600115 )  );// 106     // 107
  SF7->SetPoint( 9, 162 ,  (0.00296467 / 0.00321705 )  );// 162     // 163
  SF7->SetPoint( 10, 242 ,  (0.000701592/ 0.000931674)  );// 242     // 247
  SF7->SetPoint( 11, 343 ,  (0.00012036 / 0.000191065)  );// 343     // 350
  //                   x errors   rel.err(data) *( data  / Madgraph)
  SF7->SetPointError( 0, 0., 0., (4.4 /100.)*(0.004536 / 0.003806), (4.4 /100.)*(0.004536 / 0.003806) );
  SF7->SetPointError( 1, 0., 0., (5.5 /100.)*(0.006658 / 0.006574), (5.5 /100.)*(0.006658 / 0.006574) );
  SF7->SetPointError( 2, 0., 0., (4.0 /100.)*(0.004740 / 0.004740), (4.0 /100.)*(0.004740 / 0.004740) );
  SF7->SetPointError( 3, 0., 0., (5.8 /100.)*(0.002501 / 0.002748), (5.8 /100.)*(0.002501 / 0.002748) );
  SF7->SetPointError( 4, 0., 0., (6.2 /100.)*(0.001042 / 0.001195), (6.2 /100.)*(0.001042 / 0.001195) );
  SF7->SetPointError( 5, 0., 0., (9.0 /100.)*(0.000378 / 0.000454), (9.0 /100.)*(0.000378 / 0.000454) );
  SF7->SetPointError( 6, 0., 0., (11.1/100.)*(0.000120 / 0.000154), (11.1/100.)*(0.000120 / 0.000154) );
  SF7->SetPointError( 7, 0., 0., 0.0601381*(0.00509572 / 0.00453114 ), 0.0601381*(0.00509572 / 0.00453114 ) );
  SF7->SetPointError( 8, 0., 0., 0.0469906*(0.00626002 / 0.00600115 ), 0.0469906*(0.00626002 / 0.00600115 ) );
  SF7->SetPointError( 9, 0., 0., 0.0555114*(0.00296467 / 0.00321705 ), 0.0555114*(0.00296467 / 0.00321705 ) );
  SF7->SetPointError( 10, 0., 0., 0.071274* (0.000701592/ 0.000931674), 0.071274* (0.000701592/ 0.000931674) );
  SF7->SetPointError( 11, 0., 0., 0.0924826*(0.00012036 / 0.000191065), 0.0924826*(0.00012036 / 0.000191065) );
  //style of ratio
  SF7->SetLineWidth(3.);
  SF7->SetMarkerSize(0.1);
  SF7->SetMarkerStyle(20);
  SF7->SetMarkerColor(kWhite);
  SF7->SetLineColor(kWhite);

  // g) combined 8 TeV data points
  int Nbins8=NbinsLjets8+NbinsDilep8;
  TGraphAsymmErrors* SF8 = new TGraphAsymmErrors(Nbins8);
  //           bin x(BCC)    data  / Madgraph         // BCCNNLO // BCC MG
  SF8->SetPoint( 0 , 28.  , 0.004350 / 0.003695 ); //28       //26.2
  SF8->SetPoint( 1 , 86.  , 0.006638 / 0.006477 ); //86       //90
  SF8->SetPoint( 2 , 125. , 0.004787 / 0.005077 ); //125	  //126.2
  SF8->SetPoint( 3 , 173. , 0.002629 / 0.002795 ); //173	  //173.8
  SF8->SetPoint( 4 , 227.3, 0.001069 / 0.001246 ); //227.3	  //228.8
  SF8->SetPoint( 5 , 288. , 0.000394 / 0.000491 ); //288	  //286.2
  SF8->SetPoint( 6 , 356. , 0.000126 / 0.000177 ); //356      //356.2
  SF8->SetPoint( 7 , 35.4, (0.0051166/ 0.00441149 ) );//35.4     // 35
  SF8->SetPoint( 8 , 106 , (0.0058072/ 0.00595931 ) );//106      // 105
  SF8->SetPoint( 9 , 163 , (0.0030113/ 0.00328498 ) );//163      // 165
  SF8->SetPoint( 10, 242 , (0.00084306/0.000978855) );//242      // 245
  SF8->SetPoint( 11, 343 , (0.00016226/0.000212811) );//343      // 350
  //                   x errors   rel.err(data) *( data  / Madgraph)
  SF8->SetPointError( 0 , 0., 0., (4.3 /100.)*(0.004350 / 0.003695), (4.3 /100.)*(0.004350 / 0.003695) );
  SF8->SetPointError( 1 , 0., 0., (4.0 /100.)*(0.006638 / 0.006477), (4.0 /100.)*(0.006638 / 0.006477) );
  SF8->SetPointError( 2 , 0., 0., (3.8 /100.)*(0.004787 / 0.005077), (3.8 /100.)*(0.004787 / 0.005077) );
  SF8->SetPointError( 3 , 0., 0., (5.1 /100.)*(0.002629 / 0.002795), (5.1 /100.)*(0.002629 / 0.002795) );
  SF8->SetPointError( 4 , 0., 0., (4.6 /100.)*(0.001069 / 0.001246), (4.6 /100.)*(0.001069 / 0.001246) );
  SF8->SetPointError( 5 , 0., 0., (6.5 /100.)*(0.000394 / 0.000491), (6.5 /100.)*(0.000394 / 0.000491) );
  SF8->SetPointError( 6 , 0., 0., (9.0 /100.)*(0.000126 / 0.000177), (9.0 /100.)*(0.000126 / 0.000177) );
  SF8->SetPointError( 7 , 0.,0., (5.6 /100.)*(0.0051166 /0.00441149 ), (5.6 /100.)*(0.0051166 /0.00441149 ) );
  SF8->SetPointError( 8 , 0.,0., (5.2 /100.)*(0.0058072 /0.00595931 ), (5.2 /100.)*(0.0058072 /0.00595931 ) );
  SF8->SetPointError( 9 , 0.,0., (5.61/100.)*(0.0030113 /0.00328498 ), (5.61/100.)*(0.0030113 /0.00328498 ) );
  SF8->SetPointError( 10, 0.,0., (5.29/100.)*(0.00084306/0.000978855), (5.29/100.)*(0.00084306/0.000978855) );
  SF8->SetPointError( 11, 0.,0., (9.31/100.)*(0.00016226/0.000212811), (9.31/100.)*(0.00016226/0.000212811) );
  //style of ratio
  SF8->SetLineWidth(3.);
  SF8->SetMarkerSize(0.1);
  SF8->SetMarkerStyle(20);
  SF8->SetMarkerColor(kWhite);
  SF8->SetLineColor(kWhite);

  // ---
  //    dummy plots for axis
  // ---
  TH1F* dummy= new TH1F("","",1,0.,400);
  histogramStyle(*dummy, kSig);
  dummy->GetXaxis()->SetTitle("p_{T}^{t} [GeV]");
  dummy->GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d#sigma}{dp_{T}^{t}} ratio: (data / MadGraph)");
  dummy->SetMaximum(1.8);
  dummy->SetMinimum(0.5);

  // ---
  //    legend
  // ---
  TLegend *leg0 = new TLegend(0.3, 0.55, 0.93, 0.85);
  leg0->SetFillStyle(0);
  leg0->SetBorderSize(0);
  leg0->SetHeader("#font[22]{data / MadGraph+PYTHIA(CTEQ6L1)}");

  // canvas
  std::vector<TCanvas*> plotCanvas_;
  addCanvas(plotCanvas_);
  plotCanvas_[plotCanvas_.size()-1]->cd(0);
  plotCanvas_[plotCanvas_.size()-1]->SetTitle("data/MC top Pt ratio");
  // drawing
  dummy->Draw("axis");
  SF->Draw("p e1 same");
  SF7->Draw("p e1 same");
  SF8->Draw("p e1 same");
  SFljets->Draw("p e1 same");
  SFdilep->Draw("p e1 same");
  SFljets8->Draw("p e1 same");
  SFdilep8->Draw("p e1 same");
  // fit polynomial or exponential function
  TString def = "";
  if(func=="pol2")def="[0]*x*x+[1]*x+[2]";
  if(func=="exp")def="exp([0]+[1]*x)";
  double fitLowEdge=0.;
  double fitHighEdge=400.;
  // a) to all 8 and 7 TeV points
//   TF1* function=new TF1("function",def,fitLowEdge, fitHighEdge);
//   function->SetLineColor(kMagenta+2);
//   SF->Fit(function,"R","same",fitLowEdge, fitHighEdge);
//   for(int i=0; i<function->GetNumberFreeParameters(); i++){
//     function->SetParameter(i,round(function->GetParameter(i),3));
//   }
//   TString fitEntry="#splitline{}{#splitline{}{#splitline{}{#splitline{combined fit: ";
//   fitEntry+=function->GetExpFormula("p")+",}{                          #chi^{2}/ndof=";
//   fitEntry+=getTStringFromDouble(function->GetChisquare())+"/"+getTStringFromInt(function->GetNDF())+"}}}}";
//   fitEntry.ReplaceAll("+(","");
//   fitEntry.ReplaceAll("))",")");
//   leg0->AddEntry( function, fitEntry, "L");
  // b) to all 7 TeV points
  TF1* function7=new TF1("function7",def,fitLowEdge, fitHighEdge);
  function7->SetLineColor(6);
  function7->SetLineWidth(2);
  SF7->Fit(function7,"R","same",fitLowEdge, fitHighEdge);
  for(int i=0; i<function7->GetNumberFreeParameters(); i++){
    function7->SetParameter(i,round(function7->GetParameter(i),3));
  }
  TString fitEntry7="fit 7 TeV: ";
  fitEntry7+=function7->GetExpFormula("p");
  //fitEntry7+=",  #chi^{2}/ndof=";
  //fitEntry7+=getTStringFromDouble(function7->GetChisquare())+"/"+getTStringFromInt(function7->GetNDF());
  fitEntry7.ReplaceAll("+(","");
  fitEntry7.ReplaceAll("))",")");
  // c) to all 8 TeV points
  TF1* function8=new TF1("function8",def,fitLowEdge, fitHighEdge);
  function8->SetLineWidth(2);
  function8->SetLineColor(kTeal-1);
  SF8->Fit(function8,"R","same",fitLowEdge, fitHighEdge);
  for(int i=0; i<function8->GetNumberFreeParameters(); i++){
    function8->SetParameter(i,round(function8->GetParameter(i),3));
  }
  TString fitEntry8="fit 8 TeV: ";
  fitEntry8+=function8->GetExpFormula("p");
  //fitEntry8+=",  #chi^{2}/ndof=";
  //fitEntry8+=getTStringFromDouble(function8->GetChisquare())+"/"+getTStringFromInt(function8->GetNDF());
  fitEntry8.ReplaceAll("+(","");
  fitEntry8.ReplaceAll("))",")");
  // Draw legend
  leg0->AddEntry(SFljets, "7 TeV e/#mu+jets  (TOP-11-013)"   , "PL");
  leg0->AddEntry(SFdilep, "7 TeV ee/e#mu/#mu#mu (TOP-11-013)", "PL");
  leg0->AddEntry( function7, fitEntry7, "L");
  leg0->AddEntry(SFljets8,"8 TeV e/#mu+jets  (TOP-12-027)"   , "PL");
  leg0->AddEntry(SFdilep8,"8 TeV ee/e#mu/#mu#mu (TOP-12-028)", "PL");
  leg0->AddEntry( function8, fitEntry8, "L");
  leg0->Draw("same");
  // Draw cms label
  TPaveText *label = new TPaveText();
  label -> SetX1NDC(gStyle->GetPadLeftMargin());
  label -> SetY1NDC(1.0-gStyle->GetPadTopMargin());
  label -> SetX2NDC(1.0-gStyle->GetPadRightMargin());
  label -> SetY2NDC(1.0);
  label -> SetTextFont(42);
  label -> AddText("CMS Preliminary, 5/12 fb^{-1} at #sqrt{s} = 7/8 TeV");
  label->SetFillStyle(0);
  label->SetBorderSize(0);
  label->SetTextSize(0.04);
  label->SetTextAlign(32);
  label-> Draw("same");
  // BCC label
  double positionX=400.+0.045*400.*(gStyle->GetCanvasDefW()/600.);
  double positionY=0.5;
  TLatex *bcclabel = new TLatex(positionX,positionY, " (BCC wrt. approx NNLO, arXiv:1205.3453)");
  bcclabel->SetTextAlign(11);
  bcclabel->SetTextAngle(90);
  bcclabel->SetTextSize(0.04);
  bcclabel->Draw("same");

  //saving
  plotCanvas_[plotCanvas_.size()-1]->Print("dataVsMadgraph7and8TeV.eps");
}
