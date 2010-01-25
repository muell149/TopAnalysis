#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>
#include <TGaxis.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TPaveText.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TSystem.h>

#include <iostream>

template <typename T>
T cloneObjectFromFile(TFile* file, TString name)
{
  if(!file->Get(name)) {
    std::cout << "Failed to get object with name " << name << " from file " << file->GetName() << std::endl;
    abort();
  }
  return (T) file->Get(name)->Clone();
}

void setPadStyle()
{
  gPad->SetBorderMode(0);
  gPad->SetLeftMargin(.21);
  gPad->SetRightMargin(.07);
  gPad->SetBottomMargin(.21);
  gPad->SetTopMargin(.1);
  TGaxis::SetMaxDigits(3);
}

void setAxisStyle(TH1* hist)
{
  hist->GetXaxis()->SetNdivisions(505);
  hist->GetXaxis()->SetLabelSize(0.07);
  hist->GetXaxis()->SetTitleSize(0.07);
  hist->GetXaxis()->SetTitleOffset(1.2);
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->SetNdivisions(505);
  hist->GetYaxis()->SetLabelSize(0.07);
  hist->GetYaxis()->SetTitleSize(0.07);
  hist->GetYaxis()->SetTitleOffset(1.4);
  hist->GetYaxis()->CenterTitle();
}

void fitGauss1D(TH1F* hist, TH1F* histResult = 0, unsigned bin = 1, bool draw = true)
{
  if(hist->GetRMS() == 0.) {
    histResult->SetBinContent(bin, hist->GetMean()     );
    histResult->SetBinError  (bin, hist->GetMeanError());
    return;
  }
  // first iteration
  hist->Fit("gaus","Q0");
  // second iteration
  double mean  = hist->GetFunction("gaus")->GetParameter(1);
  double sigma = hist->GetFunction("gaus")->GetParameter(2);
  TString fitOptions = "Q";
  if(!draw) fitOptions += "0";
  hist->Fit("gaus", fitOptions, "", mean-1.5*sigma, mean+1.5*sigma);
  hist->GetFunction("gaus")->SetLineColor(kGray);
  if(histResult) {
    histResult->SetBinContent(bin, hist->GetFunction("gaus")->GetParameter(1));
    histResult->SetBinError  (bin, hist->GetFunction("gaus")->GetParError (1));
  }
}

void fitGauss2D(TH2F* hist, TH1D& means, TH1D& sigmas)
{

  if(hist->GetRMS(2) == 0.) {
    for(int bx = 1; bx <= hist->GetNbinsX(); bx++) {
      means .SetBinContent(bx, hist->GetMean     (2));
      means .SetBinError  (bx, hist->GetMeanError(2));
    }
    return;
  }

  TString histName = hist->GetName();

  // fit a gaussian in all x-bins
  TObjArray tmp;
  hist->FitSlicesY(0,0,-1,0,"QNR",&tmp);

  // get histos with mean and sigma of gaussians and clone them
  means  = *((TH1D*) tmp.FindObject(histName+"_1")->Clone(histName+"_1_0"));
  sigmas = *((TH1D*) tmp.FindObject(histName+"_2")->Clone(histName+"_2_0"));

  // clean-up
  tmp.Delete();

  // loop over all x-bins
  for(int bx = 1; bx <= hist->GetNbinsX(); bx++) {
    // sum bin contents along y-axis
    double bincontent = 0;
    for(int by = 1; by <= hist->GetNbinsY(); by++)
      bincontent += hist->GetBinContent(bx, by);
    // remove x-bins that have less than 20 entries along y
    // (this assumes weight=1 for all entries)
    if(bincontent<20) {
      means .SetBinContent(bx, 0.);
      means .SetBinError  (bx, 0.);
      sigmas.SetBinContent(bx, 0.);
      sigmas.SetBinError  (bx, 0.);
    }
    // perform a second gauss fit for all other bins
    // restricting the fitting range according to
    // mean and sigma from the first gauss fit
    else {
      double mean  = means .GetBinContent(bx);
      double sigma = sigmas.GetBinContent(bx);
      if( mean-1.5*sigma >= hist->GetYaxis()->GetXmin() &&
	  mean+1.5*sigma <  hist->GetYaxis()->GetXmax() ) {
	TF1* f = new TF1("f","gaus", mean-1.5*sigma, mean+1.5*sigma);
	hist->FitSlicesY(f,bx,bx,0,"QNR",&tmp);
	mean           = ((TH1D*) tmp.FindObject(histName+"_1"))->GetBinContent(bx);
	double meanErr = ((TH1D*) tmp.FindObject(histName+"_1"))->GetBinError  (bx);
	means.SetBinContent(bx, mean   );
	means.SetBinError  (bx, meanErr);
	sigma           = ((TH1D*) tmp.FindObject(histName+"_2"))->GetBinContent(bx);
	double sigmaErr = ((TH1D*) tmp.FindObject(histName+"_2"))->GetBinError  (bx);
	sigmas.SetBinContent(bx, sigma   );
	sigmas.SetBinError  (bx, sigmaErr);
	tmp.Delete();
	delete f;
      }
      else {
	means.SetBinContent(bx, 0.);
	means.SetBinError  (bx, 0.);
      }
    }
  }
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

int analyzeJetEnergyResolutionBias()
{

  TFile* file = TFile::Open("analyzeJetEnergyResolutionBias.root");
  
  if(!file)
    abort();

  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFontSize(.05);
  gStyle->SetTitleX(.4);
  gStyle->SetTitleY(.995);
  gStyle->SetErrorX(0.);
 
  //
  // get histos from file
  //

  TH1F* pt;
  TH1F* eta;
  TH1F* ptSmeared;
  TH2F* energySmearedOverGen;

  TH1F* resp[6][4];
  TH2F* respPtGen  [6];
  TH2F* respPtSmear[6];

  TH1F* mW[6][4];
  TH1F* mT[6][4];

  TH2F* mWPtGen  [6];
  TH2F* mWPtSmear[6];
  TH2F* mTPtGen  [6];
  TH2F* mTPtSmear[6];

  TH3F* massWPt1SmearPt2Smear;
  TH3F* massWE1SmearE2Smear;
  TH3F* ptWPt1SmearPt2Smear;
  TH3F* ptWE1SmearE2Smear;

  TString inDirBase = "analyzeJetEnergyResolutionBias";

  TString dirExt[4] = {"",       // standard pt resolution 
		       "_off",   // no pt smearing
		       "_m20",   // resolution 20% better
		       "_p20"};  // resolution 20% worse

  pt  = cloneObjectFromFile<TH1F*>(file, inDirBase + "/pt" );
  eta = cloneObjectFromFile<TH1F*>(file, inDirBase + "/eta");

  ptSmeared = cloneObjectFromFile<TH1F*>(file, inDirBase + "/ptSmeared");

  energySmearedOverGen = cloneObjectFromFile<TH2F*>(file, inDirBase + "/energySmearedOverGen");

  for(unsigned i = 0; i < 6; i++) {

    TString inDir = inDirBase;

    TString name = inDir + "/respPt_"; name += (i*10);
    respPtGen[i] = cloneObjectFromFile<TH2F*>(file, name);
    name = inDir + "/respPtSmear_"; name += (i*10);
    respPtSmear[i] = cloneObjectFromFile<TH2F*>(file, name);

    for(unsigned d = 0; d < 4; d++) {

      inDir = inDirBase + dirExt[d];

      name = inDir + "/resp_"; name += (i*10);
      resp[i][d] = cloneObjectFromFile<TH1F*>(file, name);

      if(inDir.Contains("_off")) {
	name = inDir + "/massWzoom_"; name += (i*10);
	mW[i][d] = cloneObjectFromFile<TH1F*>(file, name);
	name = inDir + "/massTzoom_"; name += (i*10);
	mT[i][d] = cloneObjectFromFile<TH1F*>(file, name);
      }
      else {
	name = inDir + "/massW_"; name += (i*10);
	mW[i][d] = cloneObjectFromFile<TH1F*>(file, name);
	name = inDir + "/massT_"; name += (i*10);
	mT[i][d] = cloneObjectFromFile<TH1F*>(file, name);
      }

    }

    name = inDir + "/massWPt_"; name += (i*10);
    mWPtGen[i] = cloneObjectFromFile<TH2F*>(file, name);
    name = inDir + "/massWPtSmear_"; name += (i*10);
    mWPtSmear[i] = cloneObjectFromFile<TH2F*>(file, name);
    name = inDir + "/massTPt_"; name += (i*10);
    mTPtGen[i] = cloneObjectFromFile<TH2F*>(file, name);
    name = inDir + "/massTPtSmear_"; name += (i*10);
    mTPtSmear[i] = cloneObjectFromFile<TH2F*>(file, name);

  }

  massWPt1SmearPt2Smear = cloneObjectFromFile<TH3F*>(file, inDirBase + "/massWPt1SmearPt2Smear");
  massWE1SmearE2Smear   = cloneObjectFromFile<TH3F*>(file, inDirBase + "/massWE1SmearE2Smear");
  ptWPt1SmearPt2Smear   = cloneObjectFromFile<TH3F*>(file, inDirBase + "/ptWPt1SmearPt2Smear");
  ptWE1SmearE2Smear     = cloneObjectFromFile<TH3F*>(file, inDirBase + "/ptWE1SmearE2Smear");

  file->Close();
  
  TH1D means;
  TH1D sigmas;

  TString outDir = "analyzeJetEnergyResolutionBias";
  gSystem->mkdir(outDir);

  //
  // create canvases
  //

  TCanvas* canvasBase = new TCanvas("canvasBase", "canvasBase", 900, 900);
  TCanvas* canvasResp = new TCanvas("canvasResp", "canvasResp", 900, 900);
  TCanvas* canvasRespPtGen        = new TCanvas("canvasRespPtGen"       , "canvasRespPtGen"       , 900, 900);
  TCanvas* canvasRespPtGenMeans   = new TCanvas("canvasRespPtGenMeans"  , "canvasRespPtGenMeans"  , 900, 900);
  TCanvas* canvasRespPtSmearMeans = new TCanvas("canvasRespPtSmearMeans", "canvasRespPtSmearMeans", 900, 900);
  TCanvas* canvasMassW        = new TCanvas("canvasMassW"       , "canvasMassW"       , 900, 900);
  TCanvas* canvasMassWPtGen   = new TCanvas("canvasMassWPtGen"  , "canvasMassWPtGen"  , 900, 900);
  TCanvas* canvasMassWPtSmear = new TCanvas("canvasMassWPtSmear", "canvasMassWPtSmear", 900, 900);
  TCanvas* canvasMassT        = new TCanvas("canvasMassT"       , "canvasMassT"       , 900, 900);
  TCanvas* canvasMassTPtGen   = new TCanvas("canvasMassTPtGen"  , "canvasMassTPtGen"  , 900, 900);
  TCanvas* canvasMassTPtSmear = new TCanvas("canvasMassTPtSmear", "canvasMassTPtSmear", 900, 900);
  TCanvas* canvasW3D = new TCanvas("canvasMassW3D", "canvasMassW3D", 900, 900);
  canvasBase->Divide(3,3);
  canvasResp->Divide(3,3);
  canvasRespPtGen       ->Divide(3,3);
  canvasRespPtGenMeans  ->Divide(3,3);
  canvasRespPtSmearMeans->Divide(3,3);
  canvasMassW       ->Divide(3,3);
  canvasMassWPtGen  ->Divide(3,3);
  canvasMassWPtSmear->Divide(3,3);
  canvasMassT       ->Divide(3,3);
  canvasMassTPtGen  ->Divide(3,3);
  canvasMassTPtSmear->Divide(3,3);
  canvasW3D->Divide(3,3);

  //
  // configure histos and draw them on pads
  //

  setAxisStyle(pt);
  pt->SetTitle("");
  pt->SetXTitle("p_{T}^{gen} (parton) [GeV]");
  pt->SetYTitle("partons");
  pt->SetStats(kFALSE);
  canvasBase->cd(1);
  setPadStyle();
  pt->DrawCopy();
  gPad->Print(outDir + "/ptGen.eps");

  setAxisStyle(eta);
  eta->SetTitle("");
  eta->SetXTitle("#eta (parton)");
  eta->SetYTitle("partons");
  eta->SetStats(kFALSE);
  canvasBase->cd(2);
  setPadStyle();
  eta->DrawCopy();
  gPad->Print(outDir + "/eta.eps");

  setAxisStyle(ptSmeared);
  ptSmeared->SetTitle("");
  ptSmeared->SetXTitle("p_{T}^{smear} (parton) [GeV]");
  ptSmeared->SetYTitle("partons");
  ptSmeared->SetStats(kFALSE);
  canvasBase->cd(4);
  setPadStyle();
  ptSmeared->DrawCopy();
  gPad->Print(outDir + "/ptSmeared.eps");

  fitGauss2D(energySmearedOverGen, means, sigmas);
  canvasBase->cd(5);
  setPadStyle();
  setAxisStyle(&sigmas);
  sigmas.SetMinimum(.0);
  sigmas.SetMaximum(1.);
  sigmas.SetStats(kFALSE);
  sigmas.SetTitle("");
  sigmas.SetXTitle("E [GeV]");
  sigmas.SetYTitle("#sigma (E) / E");
  sigmas.DrawCopy("E1");
  if(sigmas.GetEntries() > 0) {
    TF1* f = new TF1("f","sqrt([0]*[0]/(x*x)+[1]*[1]/x+[2]*[2])", 0., 250.);
    sigmas.Fit(f, "0");
    sigmas.GetFunction("f")->SetLineWidth(1);
    sigmas.GetFunction("f")->SetLineColor(kGray);
    sigmas.GetFunction("f")->DrawCopy("same");
    
    TPaveText* txt = new TPaveText(0.35, 0.68, 0.89, 0.88, "NDC");
    char *tmpTxt = new char[100];
    txt->SetTextAlign(12);
    txt->SetFillColor(0);
    txt->SetBorderSize(0);
    
    double N     = sigmas.GetFunction("f")->GetParameter(0);
    double N_err = sigmas.GetFunction("f")->GetParError (0);
    double S     = sigmas.GetFunction("f")->GetParameter(1);
    double S_err = sigmas.GetFunction("f")->GetParError (1);
    double C     = sigmas.GetFunction("f")->GetParameter(2);
    double C_err = sigmas.GetFunction("f")->GetParError (2);
    sprintf(tmpTxt, "N = %4.2f #pm %4.2f GeV", N, N_err);
    txt->AddText(tmpTxt);
    sprintf(tmpTxt, "S = %4.2f #pm %4.2f  #sqrt{GeV}", S, S_err);
    txt->AddText(tmpTxt);
    sprintf(tmpTxt, "C = %4.2f #pm %4.2f", C, C_err);
    txt->AddText(tmpTxt);
    
    txt->Draw();
  }
  gPad->Print(outDir + "/resolution.eps");

  for(unsigned i = 0; i < 6; i++) {
    TString title = "p_{T}^{cut} = ";
    title += (i*10);
    title += " GeV";

    canvasResp->cd(i+1);
    setPadStyle();
    setAxisStyle(resp[i][0]);
    resp[i][0]->SetStats(kFALSE);
    resp[i][0]->SetTitle(title);
    resp[i][0]->SetXTitle("p_{T}^{smear} / p_{T}^{gen} (parton)");
    resp[i][0]->SetYTitle("partons");
    resp[i][0]->DrawCopy();

    canvasRespPtGen->cd(i+1);
    setPadStyle();
    setAxisStyle(respPtGen[i]);
    respPtGen[i]->SetStats(kFALSE);
    respPtGen[i]->SetTitle(title);
    respPtGen[i]->SetXTitle("p_{T}^{gen} (parton) [GeV]");
    respPtGen[i]->SetYTitle("p_{T}^{smear} / p_{T}^{gen} (parton)");
    respPtGen[i]->DrawCopy("box");
    TString name = outDir + "/respPtGen_"; name += (i*10);
    gPad->Print(name + ".eps");

    fitGauss2D(respPtGen[i], means, sigmas);

    canvasRespPtGenMeans->cd(i+1);
    setPadStyle();
    setAxisStyle(&means);
    means.SetMinimum(.9);
    means.SetMaximum(2.);
    means.SetStats(kFALSE);
    means.SetTitle(title);
    means.SetYTitle("p_{T}^{smear} / p_{T}^{gen} (parton)");
    means.DrawCopy("E1");
    name = outDir + "/respPtGen_means_"; name += (i*10);
    gPad->Print(name + ".eps");

    fitGauss2D(respPtSmear[i], means, sigmas);

    canvasRespPtSmearMeans->cd(i+1);
    setPadStyle();
    setAxisStyle(&means);
    means.SetMinimum(.0);
    means.SetMaximum(1.1);
    means.SetStats(kFALSE);
    means.SetTitle(title);
    means.SetXTitle("p_{T}^{smear} [GeV]");
    means.SetYTitle("p_{T}^{smear} / p_{T}^{gen} (parton)");
    means.DrawCopy("E1");
    name = outDir + "/respPtSmear_means_"; name += (i*10);
    gPad->Print(name + ".eps");

    canvasMassW->cd(i+1);
    setPadStyle();
    setAxisStyle(mW[i][0]);
    mW[i][0]->SetStats(kFALSE);
    mW[i][0]->SetTitle(title);
    mW[i][0]->SetXTitle("m_{qq} [GeV]");
    mW[i][0]->SetYTitle("events");
    mW[i][0]->DrawCopy();

    canvasMassWPtGen->cd(i+1);
    setPadStyle();
    fitGauss2D(mWPtGen[i], means, sigmas);
    setAxisStyle(&means);
    means.SetMinimum(75.);
    means.SetMaximum(135.);
    means.SetStats(kFALSE);
    means.SetTitle(title);
    means.SetXTitle("p_{T}^{gen} (parton)");
    means.SetYTitle("m_{qq} [GeV]");
    means.DrawCopy("E1");
    name = outDir + "/massWPtGen_means_"; name += (i*10);
    gPad->Print(name + ".eps");

    canvasMassWPtSmear->cd(i+1);
    setPadStyle();
    fitGauss2D(mWPtSmear[i], means, sigmas);
    setAxisStyle(&means);
    means.SetMinimum(30.);
    means.SetMaximum(90.);
    means.SetStats(kFALSE);
    means.SetTitle(title);
    means.SetXTitle("p_{T}^{smear} (parton)");
    means.SetYTitle("m_{qq} [GeV]");
    means.DrawCopy("E1");
    name = outDir + "/massWPtSmear_means_"; name += (i*10);
    gPad->Print(name + ".eps");

    canvasMassT->cd(i+1);
    setPadStyle();
    setAxisStyle(mT[i][0]);
    mT[i][0]->SetStats(kFALSE);
    mT[i][0]->SetTitle(title);
    mT[i][0]->SetXTitle("m_{qqb} [GeV]");
    mT[i][0]->SetYTitle("events");
    mT[i][0]->DrawCopy();

    canvasMassTPtGen->cd(i+1);
    setPadStyle();
    fitGauss2D(mTPtGen[i], means, sigmas);
    setAxisStyle(&means);
    means.SetMinimum(165.);
    means.SetMaximum(210.);
    means.SetStats(kFALSE);
    means.SetTitle(title);
    means.SetXTitle("p_{T}^{gen} (parton)");
    means.SetYTitle("m_{qqb} [GeV]");
    means.DrawCopy("E1");
    name = outDir + "/massTPtGen_means_"; name += (i*10);
    gPad->Print(name + ".eps");

    canvasMassTPtSmear->cd(i+1);
    setPadStyle();
    fitGauss2D(mTPtSmear[i], means, sigmas);
    setAxisStyle(&means);
    means.SetMinimum(140.);
    means.SetMaximum(185.);
    means.SetStats(kFALSE);
    means.SetTitle(title);
    means.SetXTitle("p_{T}^{smear} (parton)");
    means.SetYTitle("m_{qqb} [GeV]");
    means.DrawCopy("E1");
    name = outDir + "/massTPtSmear_means_"; name += (i*10);
    gPad->Print(name + ".eps");
  }

  TH1F* respPtCut [4];
  TH1F* massWptCut[4];
  TH1F* massTptCut[4];
  for(unsigned d = 0; d < 4; d++) {
    TString name = "respPtCut_"; name += d;
    respPtCut [d] = new TH1F(name, name, 6, -5., 55.);
    name = "massWpCut_"; name += d;
    massWptCut[d] = new TH1F(name, name, 6, -5., 55.);
    name = "massTpCut_"; name += d;
    massTptCut[d] = new TH1F(name, name, 6, -5., 55.);

    for(unsigned i = 0; i < 6; i++) {
      bool draw = false;
      if(d==0) draw = true;
      canvasResp->cd(i+1);
      fitGauss1D(resp[i][d], respPtCut [d], i+1, draw);
      canvasMassW->cd(i+1);
      fitGauss1D(mW  [i][d], massWptCut[d], i+1, draw);
      canvasMassT->cd(i+1);
      fitGauss1D(mT  [i][d], massTptCut[d], i+1, draw);
    }
  }

  canvasResp->cd(7);
  setPadStyle();
  setAxisStyle(respPtCut[1]);
  respPtCut[1]->SetStats(kFALSE);
  respPtCut[1]->SetTitle("");
  respPtCut[1]->SetXTitle("p_{T}^{cut} [GeV]");
  respPtCut[1]->SetYTitle("p_{T}^{smear} / p_{T}^{gen} (parton)");
  respPtCut[1]->SetMinimum(0.998);
  respPtCut[1]->SetMaximum(1.03);
  respPtCut[1]->SetLineStyle(2);
  respPtCut[0]->SetFillColor(kGray);
  respPtCut[2]->SetFillColor(kGreen);
  respPtCut[3]->SetFillColor(kRed);
  respPtCut[1]->DrawCopy("hist");
  respPtCut[2]->DrawCopy("E3 same");
  respPtCut[3]->DrawCopy("E3 same");
  respPtCut[0]->DrawCopy("E3 same");
  respPtCut[0]->DrawCopy("E1 same");
  gPad->Print(outDir + "/respPtCut.eps");

  canvasMassW->cd(7);
  setPadStyle();
  setAxisStyle(massWptCut[1]);
  massWptCut[1]->SetStats(kFALSE);
  massWptCut[1]->SetTitle("");
  massWptCut[1]->SetXTitle("p_{T}^{cut} [GeV]");
  massWptCut[1]->SetYTitle("m_{qq} [GeV]");
  massWptCut[1]->SetMinimum(79.6);
  massWptCut[1]->SetMaximum(83.6);
  massWptCut[1]->SetLineStyle(2);
  massWptCut[0]->SetFillColor(kGray);
  massWptCut[2]->SetFillColor(kGreen);
  massWptCut[3]->SetFillColor(kRed);
  massWptCut[1]->DrawCopy("hist");
  massWptCut[2]->DrawCopy("E3 same");
  massWptCut[3]->DrawCopy("E3 same");
  massWptCut[0]->DrawCopy("E3 same");
  massWptCut[0]->DrawCopy("E1 same");
  gPad->Print(outDir + "/massWptCut.eps");

  canvasMassT->cd(7);
  setPadStyle();
  setAxisStyle(massTptCut[1]);
  massTptCut[1]->SetStats(kFALSE);
  massTptCut[1]->SetTitle("");
  massTptCut[1]->SetXTitle("p_{T}^{cut} [GeV]");
  massTptCut[1]->SetYTitle("m_{qqb} [GeV]");
  massTptCut[1]->SetMinimum(170.);
  massTptCut[1]->SetMaximum(178.);
  massTptCut[1]->SetLineStyle(2);
  massTptCut[0]->SetFillColor(kGray);
  massTptCut[2]->SetFillColor(kGreen);
  massTptCut[3]->SetFillColor(kRed);
  massTptCut[1]->DrawCopy("hist");
  massTptCut[2]->DrawCopy("E3 same");
  massTptCut[3]->DrawCopy("E3 same");
  massTptCut[0]->DrawCopy("E3 same");
  massTptCut[0]->DrawCopy("E1 same");
  gPad->Print(outDir + "/massTptCut.eps");

  massWPt1SmearPt2Smear->FitSlicesZ();
  TString tmpName = massWPt1SmearPt2Smear->GetName();
  TH2D* w3D = (TH2D*)gDirectory->Get(tmpName+"_1");
  setAxisStyle(w3D);
  w3D->SetStats(kFALSE);
  w3D->SetTitle("m_{qq} [GeV]");
  w3D->SetXTitle("p_{T,q}^{smear} [GeV]");
  w3D->SetYTitle("p_{T, #bar{q}}^{smear} [GeV]");
  canvasW3D->cd(1);
  setPadStyle();
  double contLevels[1] = {80.4};
  w3D->SetContour(1, contLevels);
  w3D->DrawCopy("cont1");

  massWE1SmearE2Smear->FitSlicesZ();
  tmpName = massWE1SmearE2Smear->GetName();
  w3D = (TH2D*)gDirectory->Get(tmpName+"_1");
  setAxisStyle(w3D);
  w3D->SetStats(kFALSE);
  w3D->SetTitle("m_{qq} [GeV]");
  w3D->SetXTitle("E_{q}^{smear} [GeV]");
  w3D->SetYTitle("E_{#bar{q}}^{smear} [GeV]");
  w3D->SetMinimum(60.);
  w3D->SetMaximum(100.);
  canvasW3D->cd(2);
  setPadStyle();
  w3D->SetContour(1, contLevels);
  w3D->DrawCopy("cont1");

  ptWPt1SmearPt2Smear->FitSlicesZ();
  tmpName = ptWPt1SmearPt2Smear->GetName();
  w3D = (TH2D*)gDirectory->Get(tmpName+"_1");
  setAxisStyle(w3D);
  w3D->SetStats(kFALSE);
  w3D->SetTitle("p_{T,qq} [GeV]");
  w3D->SetXTitle("p_{T,q}^{smear} [GeV]");
  w3D->SetYTitle("p_{T, #bar{q}}^{smear} [GeV]");
  w3D->SetMinimum(60.);
  w3D->SetMaximum(100.);
  canvasW3D->cd(4);
  setPadStyle();
  w3D->DrawCopy("cont1");

  ptWE1SmearE2Smear->FitSlicesZ();
  tmpName = ptWE1SmearE2Smear->GetName();
  w3D = (TH2D*)gDirectory->Get(tmpName+"_1");
  setAxisStyle(w3D);
  w3D->SetStats(kFALSE);
  w3D->SetTitle("p_{T,qq} [GeV]");
  w3D->SetXTitle("E_{q}^{smear} [GeV]");
  w3D->SetYTitle("E_{#bar{q}}^{smear} [GeV]");
  w3D->SetMinimum(60.);
  w3D->SetMaximum(100.);
  canvasW3D->cd(5);
  setPadStyle();
  w3D->DrawCopy("cont1");

  //
  // produce one ps-file containing all canvases
  //

  TString psName = outDir + "/catalog.ps";
  canvasBase->Print(psName + "(");
  canvasResp->Print(psName);
  canvasRespPtGen       ->Print(psName);
  canvasRespPtGenMeans  ->Print(psName);
  canvasRespPtSmearMeans->Print(psName);
  canvasMassW       ->Print(psName);
  canvasMassWPtGen  ->Print(psName);
  canvasMassWPtSmear->Print(psName);
  canvasMassT       ->Print(psName);
  canvasMassTPtGen  ->Print(psName);
  canvasMassTPtSmear->Print(psName);
  canvasW3D->Print(psName + ")");

  return 0;
}

int main()
{
  return analyzeJetEnergyResolutionBias();
}
