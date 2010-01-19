#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>
#include <TGaxis.h>
#include <TH1F.h>
#include <TH2F.h>
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
  gPad->SetLeftMargin(.2);
  gPad->SetRightMargin(.1);
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

  TH1F* resp  [6][4];
  TH2F* respPt[6];

  TH1F* mW[6][4];
  TH1F* mT[6][4];

  TH2F* mWPt[6];
  TH2F* mTPt[6];

  TString inDirBase = "analyzeJetEnergyResolutionBias";

  TString dirExt[4] = {"",       // standard pt resolution 
		       "_off",   // no pt smearing
		       "_m20",   // resolution 20% better
		       "_p20"};  // resolution 20% worse

  pt  = cloneObjectFromFile<TH1F*>(file, inDirBase + "/pt" );
  eta = cloneObjectFromFile<TH1F*>(file, inDirBase + "/eta");

  for(unsigned i = 0; i < 6; i++) {

    TString inDir = inDirBase;

    TString name = inDir + "/respPt_"; name += (i*10);
    respPt[i] = cloneObjectFromFile<TH2F*>(file, name);

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
    mWPt[i] = cloneObjectFromFile<TH2F*>(file, name);
    name = inDir + "/massTPt_"; name += (i*10);
    mTPt[i] = cloneObjectFromFile<TH2F*>(file, name);

  }

  file->Close();
  
  TString outDir = "analyzeJetEnergyResolutionBias";
  gSystem->mkdir(outDir);

  //
  // create canvases
  //

  TCanvas* canvasBase   = new TCanvas("canvasBase"  , "canvasBase"  , 900, 900);
  TCanvas* canvasResp   = new TCanvas("canvasResp"  , "canvasResp"  , 900, 900);
  TCanvas* canvasRespPt = new TCanvas("canvasRespPt", "canvasRespPt", 900, 900);
  TCanvas* canvasRespPtMeans  = new TCanvas("canvasRespPtMeans" , "canvasRespPtMeans" , 900, 900);
  TCanvas* canvasRespPtSigmas = new TCanvas("canvasRespPtSigmas", "canvasRespPtSigmas", 900, 900);
  TCanvas* canvasMassW   = new TCanvas("canvasMassW"  , "canvasMassW"  , 900, 900);
  TCanvas* canvasMassWPt = new TCanvas("canvasMassWPt", "canvasMassWPt", 900, 900);
  TCanvas* canvasMassT   = new TCanvas("canvasMassT"  , "canvasMassT"  , 900, 900);
  TCanvas* canvasMassTPt = new TCanvas("canvasMassTPt", "canvasMassTPt", 900, 900);
  canvasBase  ->Divide(3,3);
  canvasResp  ->Divide(3,3);
  canvasRespPt->Divide(3,3);
  canvasRespPtMeans ->Divide(3,3);
  canvasRespPtSigmas->Divide(3,3);
  canvasMassW  ->Divide(3,3);
  canvasMassWPt->Divide(3,3);
  canvasMassT  ->Divide(3,3);
  canvasMassTPt->Divide(3,3);

  //
  // configure histos and draw them on pads
  //

  setAxisStyle(pt);
  pt->SetTitle("");
  pt->SetXTitle("p_{T} (parton) [GeV]");
  pt->SetYTitle("partons");
  pt->SetStats(kFALSE);

  setAxisStyle(eta);
  eta->SetTitle("");
  eta->SetXTitle("#eta (parton)");
  eta->SetYTitle("partons");
  eta->SetStats(kFALSE);

  canvasBase->cd(1);
  setPadStyle();
  pt->DrawCopy();
  gPad->Print(outDir + "/pt.eps");

  canvasBase->cd(2);
  setPadStyle();
  eta->DrawCopy();
  gPad->Print(outDir + "/eta.eps");

  for(unsigned i = 0; i < 6; i++) {
    TString title = "p_{T}^{cut} = ";
    title += (i*10);
    title += " GeV";

    canvasResp->cd(i+1);
    setPadStyle();
    setAxisStyle(resp[i][0]);
    resp[i][0]->SetStats(kFALSE);
    resp[i][0]->SetTitle(title);
    resp[i][0]->SetXTitle("p_{T}^{smeared} / p_{T}^{gen} (parton)");
    resp[i][0]->SetYTitle("partons");
    resp[i][0]->DrawCopy();

    canvasRespPt->cd(i+1);
    //    respPt[i]->RebinX(2);
    setPadStyle();
    setAxisStyle(respPt[i]);
    respPt[i]->SetStats(kFALSE);
    respPt[i]->SetTitle(title);
    respPt[i]->SetXTitle("p_{T} (parton) [GeV]");
    respPt[i]->SetYTitle("p_{T}^{smeared} / p_{T}^{gen} (parton)");
    respPt[i]->DrawCopy("box");
    TString name = outDir + "/respPt_"; name += (i*10);
    gPad->Print(name + ".eps");

    TH1D means;
    TH1D sigmas;
    fitGauss2D(respPt[i], means, sigmas);

    canvasRespPtMeans->cd(i+1);
    setPadStyle();
    setAxisStyle(&means);
    means.SetMinimum(0.);
    means.SetMaximum(2.);
    means.SetStats(kFALSE);
    means.SetTitle(title);
    means.SetYTitle("p_{T}^{smeared} / p_{T}^{gen} (parton)");
    means.DrawCopy("E1");
    name = outDir + "/respPt_means_"; name += (i*10);
    gPad->Print(name + ".eps");

    canvasRespPtSigmas->cd(i+1);
    setPadStyle();
    setAxisStyle(&sigmas);
    sigmas.SetMinimum(.0);
    sigmas.SetMaximum(1.);
    sigmas.SetStats(kFALSE);
    sigmas.SetTitle(title);
    sigmas.SetYTitle("#sigma (p_{T})");
    sigmas.DrawCopy("E1");
    if(i == 0 && sigmas.GetEntries() > 0) {
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

      double S     = sigmas.GetFunction("f")->GetParameter(0);
      double S_err = sigmas.GetFunction("f")->GetParError (0);
      double N     = sigmas.GetFunction("f")->GetParameter(1);
      double N_err = sigmas.GetFunction("f")->GetParError (1);
      double C     = sigmas.GetFunction("f")->GetParameter(2);
      double C_err = sigmas.GetFunction("f")->GetParError (2);
      sprintf(tmpTxt, "S = %4.2f #pm %4.2f  #sqrt{GeV}", S, S_err);
      txt->AddText(tmpTxt);
      sprintf(tmpTxt, "N = %4.2f #pm %4.2f GeV", N, N_err);
      txt->AddText(tmpTxt);
      sprintf(tmpTxt, "C = %4.2f #pm %4.2f", C, C_err);
      txt->AddText(tmpTxt);

      txt->Draw();
    }
    if(i==0)
      gPad->Print(outDir + "/resolution.eps");

    canvasMassW->cd(i+1);
    setPadStyle();
    setAxisStyle(mW[i][0]);
    mW[i][0]->SetStats(kFALSE);
    mW[i][0]->SetTitle(title);
    mW[i][0]->SetXTitle("m_{qq} [GeV]");
    mW[i][0]->SetYTitle("events");
    mW[i][0]->DrawCopy();

    canvasMassWPt->cd(i+1);
    setPadStyle();
    fitGauss2D(mWPt[i], means, sigmas);
    setAxisStyle(&means);
    means.SetMinimum(30.);
    means.SetMaximum(90.);
    means.SetStats(kFALSE);
    means.SetTitle(title);
    means.SetXTitle("p_{T} (parton)");
    means.SetYTitle("m_{qq} [GeV]");
    means.DrawCopy("E1");

    canvasMassT->cd(i+1);
    setPadStyle();
    setAxisStyle(mT[i][0]);
    mT[i][0]->SetStats(kFALSE);
    mT[i][0]->SetTitle(title);
    mT[i][0]->SetXTitle("m_{qqb} [GeV]");
    mT[i][0]->SetYTitle("events");
    mT[i][0]->DrawCopy();

    canvasMassTPt->cd(i+1);
    setPadStyle();
    fitGauss2D(mTPt[i], means, sigmas);
    setAxisStyle(&means);
    means.SetMinimum(135.);
    means.SetMaximum(185.);
    means.SetStats(kFALSE);
    means.SetTitle(title);
    means.SetXTitle("p_{T} (parton)");
    means.SetYTitle("m_{qqb} [GeV]");
    means.DrawCopy("E1");
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
  respPtCut[1]->GetYaxis()->SetNdivisions(503, kFALSE);
  respPtCut[1]->SetStats(kFALSE);
  respPtCut[1]->SetTitle("");
  respPtCut[1]->SetXTitle("p_{T}^{cut} [GeV]");
  respPtCut[1]->SetYTitle("p_{T}^{smeared} / p_{T}^{gen} (parton)");
  respPtCut[1]->SetMinimum(0.998);
  respPtCut[1]->SetMaximum(1.04);
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
  massWptCut[1]->SetMinimum(79.4);
  massWptCut[1]->SetMaximum(85.);
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
  massTptCut[1]->SetMinimum(169.5);
  massTptCut[1]->SetMaximum(181.);
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

  //
  // produce one ps-file containing all canvases
  //

  TString psName = outDir + "/catalog.ps";
  canvasBase  ->Print(psName + "(");
  canvasResp  ->Print(psName);
  canvasRespPt->Print(psName);
  canvasRespPtMeans ->Print(psName);
  canvasRespPtSigmas->Print(psName);
  canvasMassW  ->Print(psName);
  canvasMassWPt->Print(psName);
  canvasMassT  ->Print(psName);
  canvasMassTPt->Print(psName + ")");

  return 0;
}

int main()
{
  return analyzeJetEnergyResolutionBias();
}
