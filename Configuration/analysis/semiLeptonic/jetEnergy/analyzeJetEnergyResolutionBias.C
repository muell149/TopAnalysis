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

void fitGauss1D(TH1F* hist, TH1F* histResult = 0, unsigned bin = 1)
{
  // first iteration
  hist->Fit("gaus","Q0");
  // second iteration
  double mean  = hist->GetFunction("gaus")->GetParameter(1);
  double sigma = hist->GetFunction("gaus")->GetParameter(2);
  hist->Fit("gaus", "Q", "", mean-1.5*sigma, mean+1.5*sigma);
  hist->GetFunction("gaus")->SetLineColor(kGray);
  if(histResult) {
    histResult->SetBinContent(bin, hist->GetFunction("gaus")->GetParameter(1));
    histResult->SetBinError  (bin, hist->GetFunction("gaus")->GetParError (1));
  }
}

void fitGauss2D(TH2F* hist, TH1D& means, TH1D& sigmas)
{

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

  TH1F* pt;
  TH1F* eta;

  TH1F* resp  [6];
  TH2F* respPt[6];

  TH1F* mW[6];
  TH1F* mT[6];

  pt  = (TH1F*) file->Get("analyzeJetEnergyResolutionBias/pt" )->Clone();
  eta = (TH1F*) file->Get("analyzeJetEnergyResolutionBias/eta")->Clone();

  for(unsigned i = 0; i < 6; i++) {
    TString name = "analyzeJetEnergyResolutionBias/resp_"; name += (i*10);
    resp  [i] = (TH1F*) file->Get(name)->Clone();
    name = "analyzeJetEnergyResolutionBias/respPt_"; name += (i*10);
    respPt[i] = (TH2F*) file->Get(name)->Clone();
    name = "analyzeJetEnergyResolutionBias/massW_"; name += (i*10);
    mW[i] = (TH1F*) file->Get(name)->Clone();
    name = "analyzeJetEnergyResolutionBias/massT_"; name += (i*10);
    mT[i] = (TH1F*) file->Get(name)->Clone();
  }

  file->Close();
  
  TString outDir = "analyzeJetEnergyResolutionBias";
  gSystem->mkdir(outDir);

  TCanvas* canvasBase   = new TCanvas("canvasBase"  , "canvasBase"  , 900, 900);
  TCanvas* canvasResp   = new TCanvas("canvasResp"  , "canvasResp"  , 900, 900);
  TCanvas* canvasRespPt = new TCanvas("canvasRespPt", "canvasRespPt", 900, 900);
  TCanvas* canvasRespPtMeans  = new TCanvas("canvasRespPtMeans" , "canvasRespPtMeans" , 900, 900);
  TCanvas* canvasRespPtSigmas = new TCanvas("canvasRespPtSigmas", "canvasRespPtSigmas", 900, 900);
  TCanvas* canvasMassW  = new TCanvas("canvasMassW", "canvasMassW", 900, 900);
  TCanvas* canvasMassT  = new TCanvas("canvasMassT", "canvasMassT", 900, 900);
  canvasBase  ->Divide(3,3);
  canvasResp  ->Divide(3,3);
  canvasRespPt->Divide(3,3);
  canvasRespPtMeans ->Divide(3,3);
  canvasRespPtSigmas->Divide(3,3);
  canvasMassW->Divide(3,3);
  canvasMassT->Divide(3,3);

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

  canvasBase->cd(2);
  setPadStyle();
  eta->DrawCopy();

  TH1F* respPtCut  = new TH1F("respPtCut" , "respPtCut" , 6, 0., 60.);
  TH1F* massWptCut = new TH1F("massWptCut", "massWptCut", 6, 0., 60.);
  TH1F* massTptCut = new TH1F("massTptCut", "massTptCut", 6, 0., 60.);

  for(unsigned i = 0; i < 6; i++) {
    TString title = "p_{T}^{cut} = ";
    title += (i*10);
    title += " GeV";

    canvasResp->cd(i+1);
    setPadStyle();
    setAxisStyle(resp[i]);
    resp[i]->SetStats(kFALSE);
    resp[i]->SetTitle(title);
    resp[i]->SetXTitle("p_{T}^{smeared} / p_{T}^{gen} (parton)");
    resp[i]->SetYTitle("partons");
    resp[i]->DrawCopy();
    fitGauss1D(resp[i], respPtCut, i+1);

    canvasRespPt->cd(i+1);
    setPadStyle();
    setAxisStyle(respPt[i]);
    respPt[i]->SetStats(kFALSE);
    respPt[i]->SetTitle(title);
    respPt[i]->SetXTitle("p_{T} (parton) [GeV]");
    respPt[i]->SetYTitle("p_{T}^{smeared} / p_{T}^{gen} (parton)");
    respPt[i]->DrawCopy("box");

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
    means.DrawCopy();

    canvasRespPtSigmas->cd(i+1);
    setPadStyle();
    setAxisStyle(&sigmas);
    sigmas.SetMinimum(.0);
    sigmas.SetMaximum(1.);
    sigmas.SetStats(kFALSE);
    sigmas.SetTitle(title);
    sigmas.SetYTitle("#sigma (p_{T})");
    sigmas.DrawCopy();

    if(i==0) {
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

    canvasMassW->cd(i+1);
    setPadStyle();
    setAxisStyle(mW[i]);
    mW[i]->SetStats(kFALSE);
    mW[i]->SetTitle(title);
    mW[i]->SetXTitle("m_{qq} [GeV]");
    mW[i]->SetYTitle("events");
    mW[i]->DrawCopy();
    fitGauss1D(mW[i], massWptCut, i+1);

    canvasMassT->cd(i+1);
    setPadStyle();
    setAxisStyle(mT[i]);
    mT[i]->SetStats(kFALSE);
    mT[i]->SetTitle(title);
    mT[i]->SetXTitle("m_{qqb} [GeV]");
    mT[i]->SetYTitle("events");
    mT[i]->DrawCopy();
    fitGauss1D(mT[i], massTptCut, i+1);
  }

  canvasResp->cd(7);
  setPadStyle();
  setAxisStyle(respPtCut);
  respPtCut->SetStats(kFALSE);
  respPtCut->SetTitle("");
  respPtCut->SetXTitle("p_{T}^{cut} [GeV]");
  respPtCut->SetYTitle("p_{T}^{smeared} / p_{T}^{gen} (parton)");
  respPtCut->DrawCopy();
  drawHLine(respPtCut, 1.0);

  canvasMassW->cd(7);
  setPadStyle();
  setAxisStyle(massWptCut);
  massWptCut->SetStats(kFALSE);
  massWptCut->SetTitle("");
  massWptCut->SetXTitle("p_{T}^{cut} [GeV]");
  massWptCut->SetYTitle("m_{qq} [GeV]");
  massWptCut->DrawCopy();
  drawHLine(massWptCut, 80.4);

  canvasMassT->cd(7);
  setPadStyle();
  setAxisStyle(massTptCut);
  massTptCut->SetStats(kFALSE);
  massTptCut->SetTitle("");
  massTptCut->SetXTitle("p_{T}^{cut} [GeV]");
  massTptCut->SetYTitle("m_{qqb} [GeV]");
  massTptCut->DrawCopy();
  drawHLine(massTptCut, 172.5);

  TString psName = outDir + "/catalog.ps";
  canvasBase  ->Print(psName + "(");
  canvasResp  ->Print(psName);
  canvasRespPt->Print(psName);
  canvasRespPtMeans ->Print(psName);
  canvasRespPtSigmas->Print(psName);
  canvasMassW->Print(psName);
  canvasMassT->Print(psName + ")");

  return 0;
}

int main()
{
  return analyzeJetEnergyResolutionBias();
}
