#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TROOT.h>
#include <TSystem.h>

void setPadStyle()
{

  gPad->SetBorderMode(0);
  gPad->SetLeftMargin(.16);
  gPad->SetRightMargin(.1);
  gPad->SetBottomMargin(.15);
  gPad->SetTopMargin(.1);

}

void setAxisStyle(TH1* hist)
{

  hist->GetXaxis()->SetNdivisions(505);
  hist->GetXaxis()->SetLabelSize(0.05);
  hist->GetXaxis()->SetTitleSize(0.05);
  hist->GetXaxis()->SetTitleOffset(1.2);
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->SetNdivisions(505);
  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.05);
  hist->GetYaxis()->SetTitleOffset(1.4);
  hist->GetYaxis()->CenterTitle();

}

void fitGauss(TH1F* hist)
{

  hist->Fit("gaus", "Q0");
  double mean  = hist->GetFunction("gaus")->GetParameter(1);
  double sigma = hist->GetFunction("gaus")->GetParameter(2);
  hist->Fit("gaus", "QM0", "", mean-1.5*sigma, mean+1.5*sigma);

}

TH1D* fitGauss2D(TH2F* hist)
{

  // fit a gaussian in all bins along x
  hist->FitSlicesY();

  // delete the three histogram that we do not want at the moment
  TString histName = hist->GetName();
  delete (TH1D*) gDirectory->Get( histName+"_0" );
  delete (TH1D*) gDirectory->Get( histName+"_2" );
  delete (TH1D*) gDirectory->Get( histName+"_chi2" );

  // return histo with mean of gaussians
  return (TH1D*) gDirectory->Get( histName+"_1" );

}

void drawHLine(TH1 *thisHisto, Double_t y,
	       Style_t lstyle = 2, Width_t lwidth = 1, Color_t lcolor = kBlack)
{
  Double_t xmin = thisHisto->GetXaxis()->GetXmin();
  Double_t xmax = thisHisto->GetXaxis()->GetXmax();
  TString height = ""; height += y;
  TF1 *f = new TF1("f", height.Data(), xmin, xmax);
  f->SetLineStyle(lstyle);
  f->SetLineWidth(lwidth);
  f->SetLineColor(lcolor);
  f->Draw("L same");
}

//                       (L1)(L2) L3 (L4) L5 (L6) L7
int markerColor[8] = { 2,  6,  6,  4,  6,  1,  6,  8};
int markerStyle[8] = {22, 24, 24, 23, 24, 20, 24, 29};

void drawResponse(TH2F* hist, const unsigned i, const TString xTitle, const TString yTitle, const bool logX=true,
		  const double yMin = 0.4, const double yMax = 1.6, const double yLine = 1.0)
{

  setPadStyle();
  gPad->SetLogx(logX);

  TH1D* histFit = fitGauss2D(hist);

  histFit->SetMarkerColor(markerColor[i]);
  histFit->SetMarkerStyle(markerStyle[i]);
  histFit->SetMinimum(yMin);
  histFit->SetMaximum(yMax);
  histFit->SetTitle("");
  histFit->SetXTitle(xTitle);
  histFit->SetYTitle(yTitle);
  histFit->SetStats(kFALSE);
  setAxisStyle(histFit);

  TString drawOption = "p";
  if(i > 0) drawOption += " same";
  
  histFit->DrawCopy(drawOption);
  drawHLine(histFit, yLine);
  histFit->DrawCopy(drawOption);

}

/// main function
void analyzeJetEnergyCorrections(TString name = "analyzeJetEnergyCorrections.root")
{

  name.Resize(name.Index(".root"));

  TString levels[8] = {"raw" ,
		       "off" ,  //L1
		       "rel" ,  //L2
		       "abs" ,  //L3
		       "emf" ,  //L4
		       "had" ,  //L5
		       "ue"  ,  //L6
		       "part"}; //L7

  TFile* file = TFile::Open(name + ".root");
  
  if(!file)
    abort();

  gROOT->cd();
  gROOT->SetStyle("Plain");

  TH1F* massW[8];
  TH1F* massT[8];

  TH2F* massW_Pt1[8];
  TH2F* massW_Pt2[8];

  TH2F* massW_Eta1[8];
  TH2F* massW_Eta2[8];

  TH2F* massT_Pt1[8];
  TH2F* massT_Pt2[8];
  TH2F* massT_PtB[8];

  TH2F* massT_Eta1[8];
  TH2F* massT_Eta2[8];
  TH2F* massT_EtaB[8];

  TH2F* respLGenJetPtGenJet       [8];
  TH2F* respLGenJetPtGenJet_barrel[8];
  TH2F* respLGenJetEta            [8];
  TH2F* respLPartonPtParton       [8];
  TH2F* respLPartonPtParton_barrel[8];

  TH2F* respBGenJetPtGenJet       [8];
  TH2F* respBGenJetPtGenJet_barrel[8];
  TH2F* respBGenJetEta            [8];
  TH2F* respBPartonPtParton       [8];
  TH2F* respBPartonPtParton_barrel[8];

  for(unsigned int i = 0; i < 8; i++) {
    TString dirBase = "analyzeJetEnergyCorrections_";

    massW[i] = (TH1F*) file->Get(dirBase + levels[i] + "/mW"  )->Clone();
    massT[i] = (TH1F*) file->Get(dirBase + levels[i] + "/mTop")->Clone();

    massW_Pt1[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mW_Pt1")->Clone();
    massW_Pt2[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mW_Pt2")->Clone();

    massW_Eta1[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mW_Eta1")->Clone();
    massW_Eta2[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mW_Eta2")->Clone();

    massT_Pt1[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_Pt1")->Clone();
    massT_Pt2[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_Pt2")->Clone();
    massT_PtB[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_PtB")->Clone();

    massT_Eta1[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_Eta1")->Clone();
    massT_Eta2[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_Eta2")->Clone();
    massT_EtaB[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_EtaB")->Clone();

    respLGenJetPtGenJet       [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseLGenJetPtGenJet"       )->Clone();
    respLGenJetPtGenJet_barrel[i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseLGenJetPtGenJet_barrel")->Clone();
    respLGenJetEta            [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseLGenJetEta"            )->Clone();
    respLPartonPtParton       [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseLPartonPtParton"       )->Clone();
    respLPartonPtParton_barrel[i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseLPartonPtParton_barrel")->Clone();

    respBGenJetPtGenJet       [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseBGenJetPtGenJet"       )->Clone();
    respBGenJetPtGenJet_barrel[i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseBGenJetPtGenJet_barrel")->Clone();
    respBGenJetEta            [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseBGenJetEta"            )->Clone();
    respBPartonPtParton       [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseBPartonPtParton"       )->Clone();
    respBPartonPtParton_barrel[i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseBPartonPtParton_barrel")->Clone();   
  }

  file->Close();
  
  TString outDir = name;
  gSystem->mkdir(outDir);

  for(unsigned int i = 0; i < 8; i++) {
    massW                     [i]->Sumw2();
    massT                     [i]->Sumw2();
    massW_Pt1                 [i]->Sumw2();
    massW_Pt2                 [i]->Sumw2();
    massW_Eta1                [i]->Sumw2();
    massW_Eta2                [i]->Sumw2();
    massT_Pt1                 [i]->Sumw2();
    massT_Pt2                 [i]->Sumw2();
    massT_PtB                 [i]->Sumw2();
    massT_Eta1                [i]->Sumw2();
    massT_Eta2                [i]->Sumw2();
    massT_EtaB                [i]->Sumw2();
    respLGenJetPtGenJet       [i]->Sumw2();
    respLGenJetPtGenJet_barrel[i]->Sumw2();
    respLGenJetEta            [i]->Sumw2();
    respLPartonPtParton       [i]->Sumw2();
    respLPartonPtParton_barrel[i]->Sumw2();
    respBGenJetPtGenJet       [i]->Sumw2();
    respBGenJetPtGenJet_barrel[i]->Sumw2();
    respBGenJetEta            [i]->Sumw2();
    respBPartonPtParton       [i]->Sumw2();
    respBPartonPtParton_barrel[i]->Sumw2();   
  }

  // create canvases

  TCanvas* canvasMassW      = new TCanvas("canvasMassW"     , "W mass"                        , 900, 900);
  TCanvas* canvasMassT      = new TCanvas("canvasMassT"     , "top mass"                      , 900, 900);
  TCanvas* canvasMassW_perr = new TCanvas("canvasMassW_perr", "W mass (peak error)"           , 900, 900);
  TCanvas* canvasMassT_perr = new TCanvas("canvasMassT_perr", "top mass (peak error)"         , 900, 900);
  TCanvas* canvasMassW_2dim = new TCanvas("canvasMassW_2dim", "W mass (2 dim.)"               , 900, 900);
  TCanvas* canvasMassT_2dim = new TCanvas("canvasMassT_2dim", "top mass (2 dim.)"             , 900, 900);
  TCanvas* canvasRespL      = new TCanvas("canvasRespL"     , "response for light jets"       , 900, 900);
  TCanvas* canvasRespB      = new TCanvas("canvasRespB"     , "response for b jets"           , 900, 900);
  TCanvas* canvasRespL_zoom = new TCanvas("canvasRespL_zoom", "response for light jets (zoom)", 900, 900);
  TCanvas* canvasRespB_zoom = new TCanvas("canvasRespB_zoom", "response for b jets (zoom)"    , 900, 900);
  canvasMassW     ->Divide(3,3);
  canvasMassT     ->Divide(3,3);
  canvasMassW_perr->Divide(3,3);
  canvasMassT_perr->Divide(3,3);
  canvasMassW_2dim->Divide(3,3);
  canvasMassT_2dim->Divide(3,3);
  canvasRespL     ->Divide(3,3);
  canvasRespB     ->Divide(3,3);
  canvasRespL_zoom->Divide(3,3);
  canvasRespB_zoom->Divide(3,3);

  for(unsigned int i = 0; i < 8; i++) {
    massW[i]->SetTitle("JEC level: " + levels[i]);
    massT[i]->SetTitle("JEC level: " + levels[i]);
    massW[i]->SetXTitle("m_{jj} [GeV]" );
    massT[i]->SetXTitle("m_{jjb} [GeV]");
    massW[i]->SetYTitle("events");
    massT[i]->SetYTitle("events");
  }
  
  for(unsigned int i = 0; i < 8; i++) {

    canvasMassW->cd(i+1);
    massW[i]->DrawCopy();

    canvasMassT->cd(i+1);
    massT[i]->DrawCopy();

    canvasMassW_perr->cd(i+1);
    massW[i]->DrawCopy();

    canvasMassT_perr->cd(i+1);
    massT[i]->DrawCopy();

  }  

  TPaveText *txtMassW = new TPaveText(0.28, 0.68, 0.88, 0.88, "NDC");
  TPaveText *txtMassT = new TPaveText(0.23, 0.68, 0.88, 0.88, "NDC");
  char *tmpTxt = new char[100];

  txtMassW->SetTextAlign(32);
  txtMassT->SetTextAlign(32);
  txtMassW->SetFillColor(0);
  txtMassT->SetFillColor(0);
  txtMassW->SetBorderSize(0);
  txtMassT->SetBorderSize(0);

  TPaveText *txtMassW_perr = (TPaveText*) txtMassW->Clone();
  TPaveText *txtMassT_perr = (TPaveText*) txtMassT->Clone();

  for(unsigned int i = 0; i < 8; i++) {

    if(i==1 || i==2 || i==4 || i==6)
      continue;

    if(massW[i]->GetEntries()==0 &&
       massT[i]->GetEntries()==0)
      continue;

    if(massW[i]->Integral())
      massW[i]->Scale(1. / massW[i]->Integral());

    if(massW[i]->Integral())
      massT[i]->Scale(1. / massT[i]->Integral());

    fitGauss(massW[i]);
    fitGauss(massT[i]);
    
    double mean     = massW[i]->GetFunction("gaus")->GetParameter(1);
    double relSigma = massW[i]->GetFunction("gaus")->GetParameter(2) / mean;
    sprintf(tmpTxt, ": #mu = %4.1f GeV ;  #sigma/#mu = %4.2f", mean, relSigma);
    txtMassW->AddText(levels[i] + tmpTxt);

    double mean_err = massW[i]->GetFunction("gaus")->GetParError(1);
    sprintf(tmpTxt, ": #mu = %4.1f GeV #pm %4.1f", mean, mean_err);
    txtMassW_perr->AddText(levels[i] + tmpTxt);
    
    mean     = massT[i]->GetFunction("gaus")->GetParameter(1);
    relSigma = massT[i]->GetFunction("gaus")->GetParameter(2) / mean;
    sprintf(tmpTxt, ": #mu = %4.1f GeV ;  #sigma/#mu = %4.2f", mean, relSigma);
    txtMassT->AddText(levels[i] + tmpTxt);

    mean_err = massT[i]->GetFunction("gaus")->GetParError(1);
    sprintf(tmpTxt, ": #mu = %4.1f GeV #pm %4.1f", mean, mean_err);
    txtMassT_perr->AddText(levels[i] + tmpTxt);

  }

  massW[0]->SetMaximum( 1.5*massW[0]->GetMaximum() );
  massT[0]->SetMaximum( 1.5*massT[0]->GetMaximum() );
  massW[0]->SetTitle("");
  massT[0]->SetTitle("");
  massW[0]->SetYTitle("a.u.");
  massT[0]->SetYTitle("a.u.");
  massW[0]->SetStats(kFALSE);
  massT[0]->SetStats(kFALSE);
  setAxisStyle(massW[0]);
  setAxisStyle(massT[0]);

  for(unsigned int i = 0; i < 8; i++) {

    if(i==1 || i==2 || i==4 || i==6)
      continue;

    TString drawOption = "hist";
    if(i > 0) drawOption += " same";

    canvasMassW->cd(9);
    setPadStyle();
    massW[i]->DrawCopy(drawOption);
    if(massW[i]->GetListOfFunctions()->FindObject("gaus")) {
      massW[i]->GetFunction("gaus")->SetLineWidth(1);
      massW[i]->GetFunction("gaus")->DrawCopy("same");
    }
    txtMassW->Draw();
    if(i==7)
      gPad->Print(outDir+"/massW.eps");

    canvasMassT->cd(9);
    setPadStyle();
    massT[i]->DrawCopy(drawOption);
    if(massT[i]->GetListOfFunctions()->FindObject("gaus")) {
      massT[i]->GetFunction("gaus")->SetLineWidth(1);
      massT[i]->GetFunction("gaus")->DrawCopy("same");
    }
    txtMassT->Draw();
    if(i==7)
      gPad->Print(outDir+"/massT.eps");

    // with error on peak from Gauss fit

    canvasMassW_perr->cd(9);
    setPadStyle();
    massW[i]->DrawCopy(drawOption);
    if(massW[i]->GetListOfFunctions()->FindObject("gaus")) {
      massW[i]->GetFunction("gaus")->SetLineWidth(1);
      massW[i]->GetFunction("gaus")->DrawCopy("same");
    }
    txtMassW_perr->Draw();
    if(i==7)
      gPad->Print(outDir+"/massW_perr.eps");

    canvasMassT_perr->cd(9);
    setPadStyle();
    massT[i]->DrawCopy(drawOption);
    if(massT[i]->GetListOfFunctions()->FindObject("gaus")) {
      massT[i]->GetFunction("gaus")->SetLineWidth(1);
      massT[i]->GetFunction("gaus")->DrawCopy("same");
    }
    txtMassT_perr->Draw();
    if(i==7)
      gPad->Print(outDir+"/massT_perr.eps");

  }

  for(unsigned int i = 0; i < 8; i++) {

    if(i==1 || i==2 || i==4 || i==6)
      continue;

    // W mass
    
    canvasMassW_2dim->cd(1);
    drawResponse(massW_Pt1[i], i, "p_{T,1} [GeV]", "m_{jj} [GeV]", true, 0., 160., 80.4);

    canvasMassW_2dim->cd(2);
    drawResponse(massW_Pt2[i], i, "p_{T,2} [GeV]", "m_{jj} [GeV]", true, 0., 160., 80.4);

    canvasMassW_2dim->cd(4);
    drawResponse(massW_Eta1[i], i, "#eta_{1}", "m_{jj} [GeV]", false, 0., 160., 80.4);

    canvasMassW_2dim->cd(5);
    drawResponse(massW_Eta2[i], i, "#eta_{2}", "m_{jj} [GeV]", false, 0., 160., 80.4);

    // top mass

    canvasMassT_2dim->cd(1);
    drawResponse(massT_Pt1[i], i, "p_{T,1} [GeV]", "m_{jjb} [GeV]", true, 0., 350., 172.5);

    canvasMassT_2dim->cd(2);
    drawResponse(massT_Pt2[i], i, "p_{T,2} [GeV]", "m_{jjb} [GeV]", true, 0., 350., 172.5);

    canvasMassT_2dim->cd(3);
    drawResponse(massT_PtB[i], i, "p_{T,b} [GeV]", "m_{jjb} [GeV]", true, 0., 350., 172.5);

    canvasMassT_2dim->cd(4);
    drawResponse(massT_Eta1[i], i, "#eta_{1}", "m_{jjb} [GeV]", false, 0., 350., 172.5);

    canvasMassT_2dim->cd(5);
    drawResponse(massT_Eta2[i], i, "#eta_{2}", "m_{jjb} [GeV]", false, 0., 350., 172.5);

    canvasMassT_2dim->cd(6);
    drawResponse(massT_EtaB[i], i, "#eta_{b}", "m_{jjb} [GeV]", false, 0., 350., 172.5);

  }

  double yMin_zoom = 0.8;
  double yMax_zoom = 1.2;

  for(unsigned int i = 0; i < 8; i++) {

    if(i==1 || i==2 || i==4 || i==6)
      continue;

    // response light jets

    canvasRespL->cd(1);
    drawResponse(respLGenJetPtGenJet[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)");

    canvasRespL->cd(2);
    drawResponse(respLGenJetPtGenJet_barrel[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)");

    canvasRespL->cd(3);
    drawResponse(respLGenJetEta[i], i, "#eta", "p_{T} (rec) / p_{T} (gen)", false);

    canvasRespL->cd(4);
    drawResponse(respLPartonPtParton[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)");

    canvasRespL->cd(5);
    drawResponse(respLPartonPtParton_barrel[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)");

    // response light jets (zoom)

    canvasRespL_zoom->cd(1);
    drawResponse(respLGenJetPtGenJet[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)",
		 true, yMin_zoom, yMax_zoom);

    canvasRespL_zoom->cd(2);
    drawResponse(respLGenJetPtGenJet_barrel[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)",
		 true, yMin_zoom, yMax_zoom);

    canvasRespL_zoom->cd(3);
    drawResponse(respLGenJetEta[i], i, "#eta", "p_{T} (rec) / p_{T} (gen)",
		 false, yMin_zoom, yMax_zoom);

    canvasRespL_zoom->cd(4);
    drawResponse(respLPartonPtParton[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)",
		 true, yMin_zoom, yMax_zoom);

    canvasRespL_zoom->cd(5);
    drawResponse(respLPartonPtParton_barrel[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)",
		 true, yMin_zoom, yMax_zoom);

    // response b jets

    canvasRespB->cd(1);
    drawResponse(respBGenJetPtGenJet[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)");

    canvasRespB->cd(2);
    drawResponse(respBGenJetPtGenJet_barrel[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)");

    canvasRespB->cd(3);
    drawResponse(respBGenJetEta[i], i, "#eta", "p_{T} (rec) / p_{T} (gen)", false);

    canvasRespB->cd(4);
    drawResponse(respBPartonPtParton[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)");

    canvasRespB->cd(5);
    drawResponse(respBPartonPtParton_barrel[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)");

    // response b jets (zoom)

    canvasRespB_zoom->cd(1);
    drawResponse(respBGenJetPtGenJet[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)",
		 true, yMin_zoom, yMax_zoom);

    canvasRespB_zoom->cd(2);
    drawResponse(respBGenJetPtGenJet_barrel[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)",
		 true, yMin_zoom, yMax_zoom);

    canvasRespB_zoom->cd(3);
    drawResponse(respBGenJetEta[i], i, "#eta", "p_{T} (rec) / p_{T} (gen)",
		 false, yMin_zoom, yMax_zoom);

    canvasRespB_zoom->cd(4);
    drawResponse(respBPartonPtParton[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)",
		 true, yMin_zoom, yMax_zoom);

    canvasRespB_zoom->cd(5);
    drawResponse(respBPartonPtParton_barrel[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)",
		 true, yMin_zoom, yMax_zoom);

  }

  // legend
  
  TLegend* legend = new TLegend(0.75, 0.7, 0.9, 0.9);
  legend->SetFillColor(0);

  TH1F* dummyHist[8];
  
  for(unsigned int i = 0; i < 8; i++) {

    if(i==1 || i==2 || i==4 || i==6)
      continue;
  
    dummyHist[i] = new TH1F();
    dummyHist[i]->SetMarkerColor(markerColor[i]);
    dummyHist[i]->SetMarkerStyle(markerStyle[i]);
    legend->AddEntry(dummyHist[i], levels[i]);

  }

  for(unsigned int i = 1; i < 7; i++) {

    TString suffix = "_";
    suffix += i;
    suffix += ".eps";

    if(i!=3 && i!=6) {
      canvasMassW_2dim->cd(i);
      legend->Draw();
      gPad->Print(outDir+"/massW_2dim" + suffix);
    }

    canvasMassT_2dim->cd(i);
    legend->Draw();
    gPad->Print(outDir+"/massT_2dim" + suffix);

  }

  for(unsigned int i = 1; i < 6; i++) {

    TString suffix = "_";
    suffix += i;
    suffix += ".eps";

    canvasRespL->cd(i);
    legend->Draw();
    gPad->Print(outDir+"/responseLight" + suffix);

    canvasRespL_zoom->cd(i);
    legend->Draw();
    gPad->Print(outDir+"/responseLight_zoom" + suffix);

    canvasRespB->cd(i);
    legend->Draw();
    gPad->Print(outDir+"/responseB" + suffix);

    canvasRespB_zoom->cd(i);
    legend->Draw();
    gPad->Print(outDir+"/responseB_zoom" + suffix);

  }

  // print one ps-file

  TString psName = name + ".ps";

  canvasMassW     ->Print(psName +"(");
  canvasMassW_perr->Print(psName);
  canvasMassW_2dim->Print(psName);
  canvasMassT     ->Print(psName);
  canvasMassT_perr->Print(psName);
  canvasMassT_2dim->Print(psName);
  canvasRespL     ->Print(psName);
  canvasRespL_zoom->Print(psName);
  canvasRespB     ->Print(psName);
  canvasRespB_zoom->Print(psName + ")");

  // clean up

//  delete file;
//  delete canvasMassW;
//  delete canvasMassT;
//  delete canvasRespL;
//  delete canvasRespB;
//  for(unsigned int i = 0; i < 8; i++) {
//    delete massW[i];
//    delete massT[i];
//    delete respLGenJetPtGenJet       [i];
//    delete respLGenJetPtGenJet_barrel[i];
//    delete respLGenJetEta            [i];
//    delete respLPartonPtParton       [i];
//    delete respLPartonPtParton_barrel[i];
//    delete respBGenJetPtGenJet       [i];
//    delete respBGenJetPtGenJet_barrel[i];
//    delete respBGenJetEta            [i];
//    delete respBPartonPtParton       [i];
//    delete respBPartonPtParton_barrel[i];
//    delete dummyHist[i];
//  }
//  delete txtMassW;
//  delete txtMassT;
//  delete tmpTxt;
//  delete legend;

}
