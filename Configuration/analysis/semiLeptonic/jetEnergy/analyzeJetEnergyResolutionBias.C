#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>
#include <TGaxis.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TLegend.h>
#include <TMath.h>
#include <TPaveText.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TSystem.h>

#include <iostream>
#include <iomanip>
#include <stdlib.h>

template <typename T>
T cloneObjectFromFile(TFile* file, TString name)
{
  if(!file->Get(name)) {
    std::cout << "Failed to get object with name " << name << " from file " << file->GetName() << std::endl;
    abort();
  }
  T obj = (T) file->Get(name);
  for(unsigned i=0; i<999999; i++) {
    TString cloneName = (TString) obj->GetName() + "_clone_";
    cloneName += i;
    if(!gDirectory->Get(cloneName)) {
      return (T) file->Get(name)->Clone(cloneName);
    }
  }
  std::cout << "Already more than 999999 clones from object with name " << obj->GetName() << std::endl
	    << "If this is really what you want, you have to increase this hard-coded limit in the macro." << std::endl;
  abort();
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

void setPaveTextStyle(TPaveText* txt, const Short_t txtAlign = 12)
{
  txt->SetTextAlign(txtAlign);
  txt->SetFillStyle(0);
  txt->SetBorderSize(0);
}

void fitGauss1D(TH1F* hist, TH1F* histResult = 0, unsigned bin = 1, bool draw = true)
{
  if(hist->GetRMS() < hist->GetXaxis()->GetBinWidth(1)) {
    histResult->SetBinContent(bin, hist->GetMean()     );
    histResult->SetBinError  (bin, hist->GetMeanError());
    return;
  }
  // first iteration
  hist->Fit("gaus","Q0ME");
  // second iteration (only if sigma > bin width)
  double mean  = hist->GetFunction("gaus")->GetParameter(1);
  double sigma = hist->GetFunction("gaus")->GetParameter(2);
  if( sigma > hist->GetBinWidth(hist->FindBin(mean)) ) {
    TString fitOptions = "QME";
    if(!draw) fitOptions += "0";
    hist->Fit("gaus", fitOptions, "", mean-1.5*sigma, mean+1.5*sigma);
  }
  hist->GetFunction("gaus")->SetLineColor(kGray);
  if(histResult) {
    histResult->SetBinContent(bin, hist->GetFunction("gaus")->GetParameter(1));
    histResult->SetBinError  (bin, hist->GetFunction("gaus")->GetParError (1));
  }
}

void fitGauss2D(TH2F* hist, TH1D& means, TH1D& sigmas, bool simpleMeanInsteadOfFit=false)
{
  if(hist->GetRMS(2) < hist->GetYaxis()->GetBinWidth(1) || simpleMeanInsteadOfFit) {
    means = *hist->ProjectionX();
    for(int bx = 1; bx <= hist->GetNbinsX(); bx++) {
      double bincontent = 0;
      for(int by = 1; by <= hist->GetNbinsY(); by++)
	bincontent += hist->GetBinContent(bx, by);
      if(bincontent > 0) {
	means.SetBinContent(bx, hist->GetMean(2));
	means.SetBinError  (bx, 0.00000000000001);
      }
      else {
	means.SetBinContent(bx, 0.);
	means.SetBinError  (bx, 0.);
      }
    }
    return;
  }

  TString histName = hist->GetName();

  // fit a gaussian in all x-bins
  TObjArray tmp;
  hist->FitSlicesY(0,0,-1,0,"QNRME",&tmp);

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
    // remove x-bins that have less than 40 entries along y
    // (this assumes weight=1 for all entries)
    if(bincontent<40) {
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
      // check if new fitting range is within range of axis
      if( mean-1.5*sigma >= hist->GetYaxis()->GetXmin() &&
	  mean+1.5*sigma <  hist->GetYaxis()->GetXmax() ) {
	// only perform second gauss fit if sigma > bin width
	if( sigma > hist->GetYaxis()->GetBinWidth(hist->GetYaxis()->FindBin(mean)) ) {
	  TF1* f = new TF1("f","gaus", mean-1.5*sigma, mean+1.5*sigma);
	  hist->FitSlicesY(f,bx,bx,0,"QNRME",&tmp);
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
      }
      else {
	means.SetBinContent(bx, 0.);
	means.SetBinError  (bx, 0.);
      }
    }
  }
}

void drawAndFitTwo2D(TH2F** hists, const unsigned i,
		     const double yMin, const double yMax, const TString title,
		     const TString xTitle, const TString yTitle, TCanvas* canvas=0)
{
  if(canvas)
    canvas->cd(i+1);

  setPadStyle();
  gPad->SetLogx();
  int fillClr[4] = {kGray, kBlue, kGreen, kRed};
  for(int d = 3; d >= 0; d--) {
    TH1D means;
    TH1D sigmas;
    bool simpleMeanInsteadOfFit=false;
    if(d==1)
      simpleMeanInsteadOfFit=true;
    fitGauss2D(hists[d], means, sigmas, simpleMeanInsteadOfFit);

    if(!canvas)
      means.GetXaxis()->SetRange(3., means.GetNbinsX());
    
    if(d==3) {
      setAxisStyle(&means);
      means.GetXaxis()->SetMoreLogLabels();
      means.GetXaxis()->SetNoExponent();
      means.SetMinimum(yMin);
      means.SetMaximum(yMax);
      means.SetStats(kFALSE);
      means.SetTitle(title);
      means.SetXTitle(xTitle);
      means.SetYTitle(yTitle);
    }

    if(d==1) {
      means.SetLineColor(kBlue);
      means.SetLineStyle(2);
      means.DrawCopy("hist ][ same");
    }
    else {
      TString drawOption = "E5";
      if(d!=3) drawOption += " same";
      means.SetFillColor(fillClr[d]);
      means.DrawCopy(drawOption);
    }

    if(d==0) {
      means.SetMarkerStyle(20);
      means.DrawCopy("p E1 same");
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

void drawWithRatio(TH1F* hist1, TH1F* hist2,
		   const TString xTitle, const TString yTitle = "a.u.", const TString title = "")
{
  if(!hist1->GetSumw2N())
    hist1->Sumw2();
  if(!hist2->GetSumw2N())
    hist2->Sumw2();

  hist1->SetFillColor(kGray);
  hist1->SetLineColor(kGray);
  hist2->SetLineColor(kBlue);
  hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);

  setPadStyle();
  gPad->SetBottomMargin(0.45);

  hist1->SetStats(kFALSE);
  setAxisStyle(hist1);
  hist1->SetTitle(title);
  hist1->SetXTitle(xTitle);
  hist1->SetYTitle(yTitle);

  TH1F* ratio = (TH1F*) hist1->Clone();
  ratio->Divide(hist2);

  hist1->GetXaxis()->SetLabelSize(0.0);
  hist1->DrawCopy("hist");
  hist2->DrawCopy("hist same");

  TPad* rPad = new TPad("rPad","",0,0,1,1);
  rPad->SetFillStyle(0);
  rPad->Draw();

  rPad->cd();
  setPadStyle();
  rPad->SetTopMargin(0.55);
  ratio->SetYTitle("ratio");
  ratio->SetMaximum(1.19);
  ratio->SetMinimum(0.81);
  ratio->SetMarkerStyle(8);
  ratio->SetMarkerSize(0.5);
  ratio->SetLineColor(kBlack);
  ratio->DrawCopy("p");
  drawHLine(ratio, 1.15, 3);
  drawHLine(ratio, 1.10, 1);
  drawHLine(ratio, 1.05, 3);
  drawHLine(ratio, 1.00, 1);
  drawHLine(ratio, 0.95, 3);
  drawHLine(ratio, 0.90, 1);
  drawHLine(ratio, 0.85, 3);
}

double addQuadratic(double x, double y, double z=0.)
{
  return TMath::Sqrt(x*x+y*y+z*z);
}

int analyzeJetEnergyResolutionBias(TString fileName1 = "analyzeJetEnergyResolutionBias.root",
				   TString fileName2 = "")
{

  TFile* file[2];
  file[0] = TFile::Open(fileName1);
  
  if(!file[0])
    abort();

  unsigned nSystematicSets = 4;
  if(fileName2 != "") {
    file[1] = TFile::Open(fileName2);
    nSystematicSets = 5;
    if(!file[1])
      abort();
  }

  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFontSize(.05);
  gStyle->SetTitleX(.21);
  gStyle->SetTitleY(.985);
  gStyle->SetErrorX(0.);
 
  //
  // get histos from file
  //

  TH1F* ptL     [2];
  TH1F* ptLSmear[2];
  TH1F* ptB     [2];
  TH1F* ptBSmear[2];
  TH1F* enL     [2];
  TH1F* enLSmear[2];
  TH1F* enB     [2];
  TH1F* enBSmear[2];

  TH1F* eta[2];
  TH1F* theta[2];

  TH2F* enSmearVsGen;

  TH1F* respL[6][nSystematicSets];
  TH1F* respB[6][nSystematicSets];
  TH1F* mW   [6][nSystematicSets];
  TH1F* mT   [6][nSystematicSets];

  TH2F* respLPtGen  [6][4];
  TH2F* respLPtSmear[6][4];
  TH2F* respBPtGen  [6][4];
  TH2F* respBPtSmear[6][4];

  TH2F* mWPtGen  [6][4];
  TH2F* mWPtSmear[6][4];

  TH2F* mTPtGen  [6][4];
  TH2F* mTPtSmear[6][4];

  TH3F* massWPt1SmearPt2Smear;
  TH3F* massWE1SmearE2Smear;
  TH3F* ptWPt1SmearPt2Smear;
  TH3F* ptWE1SmearE2Smear;

  TString inDirBase = "analyzeJetEnergyResolutionBias";

  TString dirExt[4] = {"",       // standard energy resolution 
		       "_off",   // no energy smearing
		       "_m20",   // resolution 20% better
		       "_p20"};  // resolution 20% worse

  unsigned iMaxFile = 0;
  if(fileName2 != "")
    iMaxFile = 1;

  for(unsigned iFile=0; iFile <= iMaxFile; ++iFile) {
    ptL     [iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/ptL" );
    ptLSmear[iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/ptLSmear");
    ptB     [iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/ptB" );
    ptBSmear[iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/ptBSmear");
    enL     [iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/enL" );
    enLSmear[iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/enLSmear");
    enB     [iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/enB" );
    enBSmear[iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/enBSmear");
    eta     [iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/eta");
    theta   [iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/theta");
  }

  enSmearVsGen = cloneObjectFromFile<TH2F*>(file[0], inDirBase + "/enSmearVsGen");

  for(unsigned i = 0; i < 6; i++) {

    for(unsigned d = 0; d < 4; d++) {

      TString inDir = inDirBase + dirExt[d];

      TString name = inDir + "/respL_"; name += (i*10);
      respL[i][d] = cloneObjectFromFile<TH1F*>(file[0], name);

      name = inDir + "/respLPt_"; name += (i*10);
      respLPtGen[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);
      name = inDir + "/respLPtSmear_"; name += (i*10);
      respLPtSmear[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);

      name = inDir + "/respB_"; name += (i*10);
      respB[i][d] = cloneObjectFromFile<TH1F*>(file[0], name);

      name = inDir + "/respBPt_"; name += (i*10);
      respBPtGen[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);
      name = inDir + "/respBPtSmear_"; name += (i*10);
      respBPtSmear[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);

      if(inDir.Contains("_off")) {
	name = inDir + "/massWzoom_"; name += (i*10);
	mW[i][d] = cloneObjectFromFile<TH1F*>(file[0], name);
	name = inDir + "/massTzoom_"; name += (i*10);
	mT[i][d] = cloneObjectFromFile<TH1F*>(file[0], name);

	name = inDir + "/massTPtZoom_"; name += (i*10);
	mTPtGen[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);
	name = inDir + "/massTPtSmearZoom_"; name += (i*10);
	mTPtSmear[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);
      }
      else {
	name = inDir + "/massW_"; name += (i*10);
	mW[i][d] = cloneObjectFromFile<TH1F*>(file[0], name);
	name = inDir + "/massT_"; name += (i*10);
	mT[i][d] = cloneObjectFromFile<TH1F*>(file[0], name);

	name = inDir + "/massTPt_"; name += (i*10);
	mTPtGen[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);
	name = inDir + "/massTPtSmear_"; name += (i*10);
	mTPtSmear[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);
      }

      name = inDir + "/massWPt_"; name += (i*10);
      mWPtGen[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);
      name = inDir + "/massWPtSmear_"; name += (i*10);
      mWPtSmear[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);

    }

  }

  massWPt1SmearPt2Smear = cloneObjectFromFile<TH3F*>(file[0], inDirBase + "/massWPt1SmearPt2Smear");
  massWE1SmearE2Smear   = cloneObjectFromFile<TH3F*>(file[0], inDirBase + "/massWE1SmearE2Smear");
  ptWPt1SmearPt2Smear   = cloneObjectFromFile<TH3F*>(file[0], inDirBase + "/ptWPt1SmearPt2Smear");
  ptWE1SmearE2Smear     = cloneObjectFromFile<TH3F*>(file[0], inDirBase + "/ptWE1SmearE2Smear");

  file[0]->Close();

  if(fileName2 != "") {
    for(unsigned i = 0; i < 6; i++) {
      TString name = inDirBase + "/respL_"; name += (i*10);
      respL[i][4] = cloneObjectFromFile<TH1F*>(file[1], name);
      name = inDirBase + "/respB_"; name += (i*10);
      respB[i][4] = cloneObjectFromFile<TH1F*>(file[1], name);
      name = inDirBase + "/massW_"; name += (i*10);
      mW[i][4] = cloneObjectFromFile<TH1F*>(file[1], name);
      name = inDirBase + "/massT_"; name += (i*10);
      mT[i][4] = cloneObjectFromFile<TH1F*>(file[1], name);
    }
    file[1]->Close();
  }
  
  TH1D means;
  TH1D sigmas;

  fileName1.Resize(fileName1.Index(".root"));
  TString outDir = fileName1;
  gSystem->mkdir(outDir);

  //
  // create canvases
  //

  TCanvas* canvasBase         = new TCanvas("canvasBase"        , "canvasBase"        , 900, 900);
  TCanvas* canvasRespL        = new TCanvas("canvasRespL"       , "canvasRespL"       , 900, 900);
  TCanvas* canvasRespB        = new TCanvas("canvasRespB"       , "canvasRespB"       , 900, 900);
  TCanvas* canvasRespLPtGen   = new TCanvas("canvasRespLPtGen"  , "canvasRespLPtGen"  , 900, 900);
  TCanvas* canvasRespLPtSmear = new TCanvas("canvasRespLPtSmear", "canvasRespLPtSmear", 900, 900);
  TCanvas* canvasRespBPtGen   = new TCanvas("canvasRespBPtGen"  , "canvasRespBPtGen"  , 900, 900);
  TCanvas* canvasRespBPtSmear = new TCanvas("canvasRespBPtSmear", "canvasRespBPtSmear", 900, 900);
  TCanvas* canvasMassW        = new TCanvas("canvasMassW"       , "canvasMassW"       , 900, 900);
  TCanvas* canvasMassWPtGen   = new TCanvas("canvasMassWPtGen"  , "canvasMassWPtGen"  , 900, 900);
  TCanvas* canvasMassWPtSmear = new TCanvas("canvasMassWPtSmear", "canvasMassWPtSmear", 900, 900);
  TCanvas* canvasMassT        = new TCanvas("canvasMassT"       , "canvasMassT"       , 900, 900);
  TCanvas* canvasMassTPtGen   = new TCanvas("canvasMassTPtGen"  , "canvasMassTPtGen"  , 900, 900);
  TCanvas* canvasMassTPtSmear = new TCanvas("canvasMassTPtSmear", "canvasMassTPtSmear", 900, 900);
  TCanvas* canvasW3D          = new TCanvas("canvasMassW3D"     , "canvasMassW3D"     , 900, 900);
  canvasBase        ->Divide(3,3);
  canvasRespL       ->Divide(3,3);
  canvasRespB       ->Divide(3,3);
  canvasRespLPtGen  ->Divide(3,3);
  canvasRespLPtSmear->Divide(3,3);
  canvasRespBPtGen  ->Divide(3,3);
  canvasRespBPtSmear->Divide(3,3);
  canvasMassW       ->Divide(3,3);
  canvasMassWPtGen  ->Divide(3,3);
  canvasMassWPtSmear->Divide(3,3);
  canvasMassT       ->Divide(3,3);
  canvasMassTPtGen  ->Divide(3,3);
  canvasMassTPtSmear->Divide(3,3);
  canvasW3D         ->Divide(3,3);

  //
  // configure histos and draw them on pads
  //

  char *tmpTxt = new char[100];

  TPaveText* txtTitleUDSC = new TPaveText(0.2, 0.91, 0.6, 1.0, "NDC");
  TText *txtUDSC = txtTitleUDSC->AddText("flavor: udsc");
  setPaveTextStyle(txtTitleUDSC);
  txtUDSC->SetTextSize(0.07);

  TPaveText* txtTitleB = new TPaveText(0.2, 0.91, 0.6, 1.0, "NDC");
  TText *txtB = txtTitleB->AddText("flavor: b");
  setPaveTextStyle(txtTitleB);
  txtB->SetTextSize(0.07);
		 
  canvasBase->cd(1);
  gPad->SetLogy();
  drawWithRatio(ptLSmear[0], ptL[0], "p_{T} [GeV]", "partons");
  txtTitleUDSC->Draw();
  TPaveText* txtPtL = new TPaveText(0.25, 0.52, 0.63, 0.67, "NDC");
  setPaveTextStyle(txtPtL, 32);
  sprintf(tmpTxt, "Mean = %4.2f #pm", ptL[0]->GetMean());
  txtPtL->AddText(tmpTxt);
  sprintf(tmpTxt, "%4.2f GeV", ptL[0]->GetMeanError());
  txtPtL->AddText(tmpTxt);
  txtPtL->Draw();
  TLegend* legGenSmear = new TLegend(0.7, 0.8, 1., 1.);
  legGenSmear->SetFillColor(0);
  legGenSmear->AddEntry(ptLSmear[0], "smear", "F");
  legGenSmear->AddEntry(ptL     [0], "gen"  , "F");
  legGenSmear->Draw();
  canvasBase->cd(1);
  gPad->Print(outDir + "/ptL.eps");

  canvasBase->cd(2);
  gPad->SetLogy();
  drawWithRatio(enLSmear[0], enL[0], "E [GeV]", "partons");
  txtTitleUDSC->Draw();
  TPaveText* txtEnL = new TPaveText(0.25, 0.52, 0.63, 0.67, "NDC");
  setPaveTextStyle(txtEnL, 32);
  sprintf(tmpTxt, "Mean = %4.1f #pm", enL[0]->GetMean());
  txtEnL->AddText(tmpTxt);
  sprintf(tmpTxt, "%4.1f GeV", enL[0]->GetMeanError());
  txtEnL->AddText(tmpTxt);
  txtEnL->Draw();
  legGenSmear->Draw();
  canvasBase->cd(2);
  gPad->Print(outDir + "/enL.eps");

  setAxisStyle(eta[0]);
  eta[0]->SetTitle("");
  eta[0]->SetXTitle("#eta");
  eta[0]->SetYTitle("partons");
  eta[0]->SetStats(kFALSE);
  canvasBase->cd(3);
  setPadStyle();
  eta[0]->SetFillColor(kGray);
  eta[0]->DrawCopy();
  gPad->Print(outDir + "/eta.eps");

  canvasBase->cd(4);
  gPad->SetLogy();
  drawWithRatio(ptBSmear[0], ptB[0], "p_{T} [GeV]", "partons");
  txtTitleB->Draw();
  TPaveText* txtPtB = new TPaveText(0.25, 0.52, 0.63, 0.67, "NDC");
  setPaveTextStyle(txtPtB, 32);
  sprintf(tmpTxt, "Mean = %4.2f #pm", ptB[0]->GetMean());
  txtPtB->AddText(tmpTxt);
  sprintf(tmpTxt, "%4.2f GeV", ptB[0]->GetMeanError());
  txtPtB->AddText(tmpTxt);
  txtPtB->Draw();
  legGenSmear->Draw();
  canvasBase->cd(4);
  gPad->Print(outDir + "/ptB.eps");

  canvasBase->cd(5);
  gPad->SetLogy();
  drawWithRatio(enBSmear[0], enB[0], "E [GeV]", "partons");
  txtTitleB->Draw();
  TPaveText* txtEnB = new TPaveText(0.25, 0.52, 0.63, 0.67, "NDC");
  setPaveTextStyle(txtEnB, 32);
  sprintf(tmpTxt, "Mean = %4.1f #pm", enB[0]->GetMean());
  txtEnB->AddText(tmpTxt);
  sprintf(tmpTxt, "%4.1f GeV", enB[0]->GetMeanError());
  txtEnB->AddText(tmpTxt);
  txtEnB->Draw();
  legGenSmear->Draw();
  canvasBase->cd(5);
  gPad->Print(outDir + "/enB.eps");

  fitGauss2D(enSmearVsGen, means, sigmas);
  canvasBase->cd(6);
  setPadStyle();
  setAxisStyle(&sigmas);
  sigmas.SetMinimum(.0);
  sigmas.SetMaximum(1.);
  sigmas.SetStats(kFALSE);
  sigmas.SetTitle("");
  sigmas.SetXTitle("E [GeV]");
  sigmas.SetYTitle("#sigma (E) / E");
  sigmas.SetLineColor(kBlue);
  sigmas.DrawCopy("E1");
  if(sigmas.GetEntries() > 0) {
    TF1* f = new TF1("f","sqrt([0]*[0]/(x*x)+[1]*[1]/x+[2]*[2])", 0., 250.);
    sigmas.Fit(f, "0ME");
    sigmas.GetFunction("f")->SetLineWidth(1);
    sigmas.GetFunction("f")->DrawCopy("same");
    
    TPaveText* txtEsOg = new TPaveText(0.35, 0.68, 0.89, 0.88, "NDC");
    setPaveTextStyle(txtEsOg);
    
    double N     = sigmas.GetFunction("f")->GetParameter(0);
    double N_err = sigmas.GetFunction("f")->GetParError (0);
    double S     = sigmas.GetFunction("f")->GetParameter(1);
    double S_err = sigmas.GetFunction("f")->GetParError (1);
    double C     = sigmas.GetFunction("f")->GetParameter(2);
    double C_err = sigmas.GetFunction("f")->GetParError (2);
    sprintf(tmpTxt, "N = %4.3f #pm %4.3f GeV", N, N_err);
    txtEsOg->AddText(tmpTxt);
    sprintf(tmpTxt, "S = %4.3f #pm %4.3f  #sqrt{GeV}", S, S_err);
    txtEsOg->AddText(tmpTxt);
    sprintf(tmpTxt, "C = %4.3f #pm %4.3f", C, C_err);
    txtEsOg->AddText(tmpTxt);
    
    txtEsOg->Draw();
  }
  gPad->Print(outDir + "/resolution.eps");

  setAxisStyle(theta[0]);
  theta[0]->SetStats(kFALSE);
  theta[0]->SetTitle("");
  theta[0]->SetXTitle("#theta_{q #bar{q}}");
  theta[0]->SetYTitle("events");
  theta[0]->SetFillColor(kGray);
  canvasBase->cd(7);
  setPadStyle();
  theta[0]->DrawCopy();
  TPaveText* txtTheta = new TPaveText(0.58, 0.73, 0.9, 0.88, "NDC");
  setPaveTextStyle(txtTheta, 32);
  sprintf(tmpTxt, "Mean = %4.3f", theta[0]->GetMean());
  txtTheta->AddText(tmpTxt);
  sprintf(tmpTxt, "#pm %4.3f", theta[0]->GetMeanError());
  txtTheta->AddText(tmpTxt);
  txtTheta->Draw();
  gPad->Print(outDir + "/theta.eps");

  for(unsigned i = 0; i < 6; i++) {
    TString title = "p_{T}^{smear} > ";
    title += (i*10);
    title += " GeV";

    canvasRespL->cd(i+1);
    setPadStyle();
    setAxisStyle(respL[i][0]);
    respL[i][0]->SetStats(kFALSE);
    respL[i][0]->SetTitle(title);
    respL[i][0]->SetXTitle("p_{T}^{smear} / p_{T}^{gen} (parton)");
    respL[i][0]->SetYTitle("partons (udsc)");
    respL[i][0]->DrawCopy();

    canvasRespB->cd(i+1);
    setPadStyle();
    setAxisStyle(respB[i][0]);
    respB[i][0]->SetStats(kFALSE);
    respB[i][0]->SetTitle(title);
    respB[i][0]->SetXTitle("p_{T}^{smear} / p_{T}^{gen} (parton)");
    respB[i][0]->SetYTitle("partons (b)");
    respB[i][0]->DrawCopy();

    canvasMassW->cd(i+1);
    setPadStyle();
    setAxisStyle(mW[i][0]);
    mW[i][0]->SetStats(kFALSE);
    mW[i][0]->SetTitle(title);
    mW[i][0]->SetXTitle("m_{qq} [GeV]");
    mW[i][0]->SetYTitle("events");
    mW[i][0]->DrawCopy();

    canvasMassT->cd(i+1);
    setPadStyle();
    setAxisStyle(mT[i][0]);
    mT[i][0]->SetStats(kFALSE);
    mT[i][0]->SetTitle(title);
    mT[i][0]->SetXTitle("m_{qqb} [GeV]");
    mT[i][0]->SetYTitle("events");
    mT[i][0]->DrawCopy();

    drawAndFitTwo2D(respLPtGen[i], i, .95, 1.85, "flavor: udsc, "+title,
		    "p_{T}^{gen} (parton) [GeV]", "p_{T}^{smear} / p_{T}^{gen} (parton)", canvasRespLPtGen);

    drawAndFitTwo2D(respLPtSmear[i], i, .81, 1.05, "flavor: udsc, "+title,
		    "p_{T}^{smear} (parton) [GeV]", "p_{T}^{smear} / p_{T}^{gen} (parton)", canvasRespLPtSmear);

    drawAndFitTwo2D(respBPtGen[i], i, .95, 1.55, "flavor: b, "+title,
		    "p_{T}^{gen} (parton) [GeV]", "p_{T}^{smear} / p_{T}^{gen} (parton)", canvasRespBPtGen);

    drawAndFitTwo2D(respBPtSmear[i], i, .81, 1.05, "flavor: b, "+title,
		    "p_{T}^{smear} (parton) [GeV]", "p_{T}^{smear} / p_{T}^{gen} (parton)", canvasRespBPtSmear);

    drawAndFitTwo2D(mWPtGen[i], i, 77., 125., title,
		    "p_{T}^{gen} (parton) [GeV]", "m_{qq} [GeV]", canvasMassWPtGen);

    drawAndFitTwo2D(mWPtSmear[i], i, 73., 85., title,
		    "p_{T}^{smear} (parton) [GeV]", "m_{qq} [GeV]", canvasMassWPtSmear);

    drawAndFitTwo2D(mTPtGen[i], i, 168., 222., title,
		    "p_{T}^{gen} (parton) [GeV]", "m_{qqb} [GeV]", canvasMassTPtGen);

    drawAndFitTwo2D(mTPtSmear[i], i, 165., 181., title,
		    "p_{T}^{smear} (parton) [GeV]", "m_{qqb} [GeV]", canvasMassTPtSmear);

  }

  canvasRespLPtGen->cd(7);
  drawAndFitTwo2D(respLPtGen[3], 3, .94, 1.06, "flavor: udsc, p_{T}^{smear} > 30 GeV",
		  "p_{T}^{gen} (parton) [GeV]", "p_{T}^{smear} / p_{T}^{gen} (parton)");

  canvasRespLPtSmear->cd(7);
  drawAndFitTwo2D(respLPtSmear[3], 3, .94, 1.06, "flavor: udsc, p_{T}^{smear} > 30 GeV",
		  "p_{T}^{smear} (parton) [GeV]", "p_{T}^{smear} / p_{T}^{gen} (parton)");

  canvasRespBPtGen->cd(7);
  drawAndFitTwo2D(respBPtGen[3], 3, .94, 1.06, "flavor: b, p_{T}^{smear} > 30 GeV",
		  "p_{T}^{gen} (parton) [GeV]", "p_{T}^{smear} / p_{T}^{gen} (parton)");

  canvasRespBPtSmear->cd(7);
  drawAndFitTwo2D(respBPtSmear[3], 3, .94, 1.06, "flavor: b, p_{T}^{smear} > 30 GeV",
		  "p_{T}^{smear} (parton) [GeV]", "p_{T}^{smear} / p_{T}^{gen} (parton)");

  canvasMassWPtGen->cd(7);
  drawAndFitTwo2D(mWPtGen[3], 3, 77., 84., "p_{T}^{smear} > 30 GeV",
		  "p_{T}^{gen} (parton) [GeV]", "m_{qq} [GeV]");

  canvasMassWPtSmear->cd(7);
  drawAndFitTwo2D(mWPtSmear[3], 3, 77., 84., "p_{T}^{smear} > 30 GeV",
		  "p_{T}^{smear} (parton) [GeV]", "m_{qq} [GeV]");

  canvasMassTPtGen->cd(7);
  drawAndFitTwo2D(mTPtGen[3], 3, 165., 180., "p_{T}^{smear} > 30 GeV",
		  "p_{T}^{gen} (parton) [GeV]", "m_{qqb} [GeV]");

  canvasMassTPtSmear->cd(7);
  drawAndFitTwo2D(mTPtSmear[3], 3, 165., 180., "p_{T}^{smear} > 30 GeV",
		  "p_{T}^{smear} (parton) [GeV]", "m_{qqb} [GeV]");

  TH1F* respLPtCut[nSystematicSets];
  TH1F* respBPtCut[nSystematicSets];
  TH1F* massWptCut[nSystematicSets];
  TH1F* massTptCut[nSystematicSets];
  for(unsigned d = 0; d < nSystematicSets; d++) {
    TString name = "respLPtCut_"; name += d;
    respLPtCut [d] = new TH1F(name, name, 6, -5., 55.);
    name = "respBPtCut_"; name += d;
    respBPtCut [d] = new TH1F(name, name, 6, -5., 55.);
    name = "massWpCut_"; name += d;
    massWptCut[d] = new TH1F(name, name, 6, -5., 55.);
    name = "massTpCut_"; name += d;
    massTptCut[d] = new TH1F(name, name, 6, -5., 55.);

    for(unsigned i = 0; i < 6; i++) {
      bool draw = false;
      if(d==0) draw = true;
      canvasRespL->cd(i+1);
      fitGauss1D(respL[i][d], respLPtCut[d], i+1, draw);
      canvasRespB->cd(i+1);
      fitGauss1D(respB[i][d], respBPtCut [d], i+1, draw);
      if(d==0) {
	name = outDir + "/resp_"; name += (i*10);
	gPad->Print(name + ".eps");
      }
      canvasMassW->cd(i+1);
      fitGauss1D(mW  [i][d], massWptCut[d], i+1, draw);
      if(d==0) {
	name = outDir + "/massW_"; name += (i*10);
	gPad->Print(name + ".eps");
      }
      canvasMassT->cd(i+1);
      fitGauss1D(mT  [i][d], massTptCut[d], i+1, draw);
      if(d==0) {
	name = outDir + "/massT_"; name += (i*10);
	gPad->Print(name + ".eps");
      }
    }
  }

  canvasRespL->cd(7);
  setPadStyle();
  setAxisStyle(respLPtCut[1]);
  respLPtCut[1]->GetXaxis()->SetNdivisions(205);
  respLPtCut[1]->SetStats(kFALSE);
  respLPtCut[1]->SetTitle("");
  respLPtCut[1]->SetXTitle("p_{T , cut}^{smear} [GeV]");
  respLPtCut[1]->SetYTitle("p_{T}^{smear} / p_{T}^{gen} (partons)");
  respLPtCut[1]->SetMinimum(0.998);
  respLPtCut[1]->SetMaximum(1.038);
  respLPtCut[1]->SetLineColor(kBlue);
  respLPtCut[1]->SetLineStyle(2);
  respLPtCut[0]->SetFillColor(kGray);
  respLPtCut[2]->SetFillColor(kGreen);
  respLPtCut[3]->SetFillColor(kRed);
  respLPtCut[1]->DrawCopy("hist");
  respLPtCut[2]->DrawCopy("E3 same");
  respLPtCut[3]->DrawCopy("E3 same");
  respLPtCut[0]->DrawCopy("E3 same");
  respLPtCut[0]->DrawCopy("E1 same");
  txtTitleUDSC->Draw();

  TLegend* legend = new TLegend(0.3, 0.69, 0.6, 0.89);
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->AddEntry(respLPtCut[3], " #sigma +20%", "F");
  legend->AddEntry(respLPtCut[2], " #sigma -20%", "F");
  legend->Draw();
  gPad->Print(outDir + "/respLPtCut.eps");

  canvasRespB->cd(7);
  setPadStyle();
  setAxisStyle(respBPtCut[1]);
  respBPtCut[1]->GetXaxis()->SetNdivisions(205);
  respBPtCut[1]->SetStats(kFALSE);
  respBPtCut[1]->SetTitle("");
  respBPtCut[1]->SetXTitle("p_{T , cut}^{smear} [GeV]");
  respBPtCut[1]->SetYTitle("p_{T}^{smear} / p_{T}^{gen} (partons)");
  respBPtCut[1]->SetMinimum(0.998);
  respBPtCut[1]->SetMaximum(1.038);
  respBPtCut[1]->SetLineColor(kBlue);
  respBPtCut[1]->SetLineStyle(2);
  respBPtCut[0]->SetFillColor(kGray);
  respBPtCut[2]->SetFillColor(kGreen);
  respBPtCut[3]->SetFillColor(kRed);
  respBPtCut[1]->DrawCopy("hist");
  respBPtCut[2]->DrawCopy("E3 same");
  respBPtCut[3]->DrawCopy("E3 same");
  respBPtCut[0]->DrawCopy("E3 same");
  respBPtCut[0]->DrawCopy("E1 same");
  txtTitleB->Draw();
  legend->Draw();
  gPad->Print(outDir + "/respBPtCut.eps");

  canvasMassW->cd(7);
  setPadStyle();
  setAxisStyle(massWptCut[1]);
  massWptCut[1]->GetXaxis()->SetNdivisions(205);
  massWptCut[1]->SetStats(kFALSE);
  massWptCut[1]->SetTitle("");
  massWptCut[1]->SetXTitle("p_{T , cut}^{smear} [GeV]");
  massWptCut[1]->SetYTitle("m_{qq} [GeV]");
  massWptCut[1]->SetMinimum(79.6);
  massWptCut[1]->SetMaximum(84.0);
  massWptCut[1]->SetLineColor(kBlue);
  massWptCut[1]->SetLineStyle(2);
  massWptCut[0]->SetFillColor(kGray);
  massWptCut[2]->SetFillColor(kGreen);
  massWptCut[3]->SetFillColor(kRed);
  massWptCut[1]->DrawCopy("hist");
  massWptCut[2]->DrawCopy("E3 same");
  massWptCut[3]->DrawCopy("E3 same");
  massWptCut[0]->DrawCopy("E3 same");
  massWptCut[0]->DrawCopy("E1 same");
  legend->Draw();
  gPad->Print(outDir + "/massWptCut.eps");

  canvasMassT->cd(7);
  setPadStyle();
  setAxisStyle(massTptCut[1]);
  massTptCut[1]->GetXaxis()->SetNdivisions(205);
  massTptCut[1]->SetStats(kFALSE);
  massTptCut[1]->SetTitle("");
  massTptCut[1]->SetXTitle("p_{T , cut}^{smear} [GeV]");
  massTptCut[1]->SetYTitle("m_{qqb} [GeV]");
  massTptCut[1]->SetMinimum(171.);
  massTptCut[1]->SetMaximum(180.);
  massTptCut[1]->SetLineColor(kBlue);
  massTptCut[1]->SetLineStyle(2);
  massTptCut[0]->SetFillColor(kGray);
  massTptCut[2]->SetFillColor(kGreen);
  massTptCut[3]->SetFillColor(kRed);
  massTptCut[1]->DrawCopy("hist");
  massTptCut[2]->DrawCopy("E3 same");
  massTptCut[3]->DrawCopy("E3 same");
  massTptCut[0]->DrawCopy("E3 same");
  massTptCut[0]->DrawCopy("E1 same");
  legend->Draw();
  gPad->Print(outDir + "/massTptCut.eps");

  TLegend* legendUpperRight = (TLegend*) legend->Clone();
  legendUpperRight->SetX1NDC(0.64);
  legendUpperRight->SetX2NDC(0.92);

  TLegend* legendLowerRight = (TLegend*) legendUpperRight->Clone();
  legendLowerRight->SetY1NDC(0.29);
  legendLowerRight->SetY2NDC(0.49);

  for(unsigned i = 0; i < 7; i++) {
    canvasRespLPtGen->cd(i+1);
    TString epsName = outDir+"/respLPtGen_means_";
    if(i==6) {
      epsName += "30_zoom";
      legendLowerRight->Draw();
    }
    else {
      epsName += (i*10);
      if(i!=0)
	legendUpperRight->Draw();
    }
    gPad->Print(epsName + ".eps");

    canvasRespLPtSmear->cd(i+1);
    legendLowerRight->Draw();
    epsName = outDir+"/respLPtSmear_means_";
    if(i==6)
      epsName += "30_zoom";
    else
      epsName += (i*10);
    gPad->Print(epsName + ".eps");

    canvasRespBPtGen->cd(i+1);
    epsName = outDir+"/respBPtGen_means_";
    if(i==6) {
      epsName += "30_zoom";
      legendLowerRight->Draw();
    }
    else {
      epsName += (i*10);
      if(i!=0)
	legendUpperRight->Draw();
    }
    gPad->Print(epsName + ".eps");

    canvasRespBPtSmear->cd(i+1);
    legendLowerRight->Draw();
    epsName = outDir+"/respBPtSmear_means_";
    if(i==6)
      epsName += "30_zoom";
    else
      epsName += (i*10);
    gPad->Print(epsName + ".eps");

    canvasMassWPtGen->cd(i+1);
    epsName = outDir+"/massWPtGen_means_";
    if(i==6) {
      legendLowerRight->Draw();
      epsName += "30_zoom";
    }
    else {
      legendUpperRight->Draw();
      epsName += (i*10);
    }
    gPad->Print(epsName + ".eps");

    canvasMassWPtSmear->cd(i+1);
    legendLowerRight->Draw();
    epsName = outDir+"/massWPtSmear_means_";
    if(i==6)
      epsName += "30_zoom";
    else
      epsName += (i*10);
    gPad->Print(epsName + ".eps");

    canvasMassTPtGen->cd(i+1);
    epsName = outDir+"/massTPtGen_means_";
    if(i==6) {
      legendLowerRight->Draw();
      epsName += "30_zoom";
    }
    else {
      legendUpperRight->Draw();
      epsName += (i*10);
    }
    gPad->Print(epsName + ".eps");

    canvasMassTPtSmear->cd(i+1);
    legendLowerRight->Draw();
    epsName = outDir+"/massTPtSmear_means_";
    if(i==6)
      epsName += "30_zoom";
    else
      epsName += (i*10);
    gPad->Print(epsName + ".eps");
  }

//  massWPt1SmearPt2Smear->FitSlicesZ();
//  TString tmpName = massWPt1SmearPt2Smear->GetName();
//  TH2D* w3D = (TH2D*)gDirectory->Get(tmpName+"_1");
//  setAxisStyle(w3D);
//  w3D->SetStats(kFALSE);
//  w3D->SetTitle("m_{qq} [GeV]");
//  w3D->SetXTitle("p_{T,q}^{smear} [GeV]");
//  w3D->SetYTitle("p_{T, #bar{q}}^{smear} [GeV]");
//  canvasW3D->cd(1);
//  setPadStyle();
//  double contLevels[1] = {80.4};
//  w3D->SetContour(1, contLevels);
//  w3D->DrawCopy("cont1");

  TH2* project3D = (TH2*) massWE1SmearE2Smear->Project3D("xy");
  project3D->Rebin2D(4, 4);
  setAxisStyle(project3D);
  project3D->SetStats(kFALSE);
  project3D->SetTitle("");
  project3D->SetXTitle("E_{q}^{smear} [GeV]");
  project3D->SetYTitle("E_{#bar{q}}^{smear} [GeV]");
  canvasW3D->cd(2);
  setPadStyle();
  project3D->DrawCopy("box");
  // theta = 60 degr. ( cos theta = 1/2)
  TF1* fE1E2t60 = new TF1("fE1E2t60", "80.4*80.4/x", 0., 250.);
  fE1E2t60->SetLineColor(kGreen);
  fE1E2t60->DrawCopy("same");
  // theta = 90 degr. ( cos theta = 0)
  TF1* fE1E2t90 = new TF1("fE1E2t90", "80.4*80.4/(2*x)", 0., 250.);
  fE1E2t90->SetLineColor(kBlue);
  fE1E2t90->DrawCopy("same");
  // theta = 180 degr. ( cos theta = -1)
  TF1* fE1E2t120 = new TF1("fE1E2t120", "80.4*80.4/(4*x)", 0., 250.);
  fE1E2t120->SetLineColor(kRed);
  fE1E2t120->DrawCopy("same");
  gPad->Print(outDir + "/massWE1SmearE2Smear.eps");

//  ptWPt1SmearPt2Smear->FitSlicesZ();
//  tmpName = ptWPt1SmearPt2Smear->GetName();
//  w3D = (TH2D*)gDirectory->Get(tmpName+"_1");
//  setAxisStyle(w3D);
//  w3D->SetStats(kFALSE);
//  w3D->SetTitle("p_{T,qq} [GeV]");
//  w3D->SetXTitle("p_{T,q}^{smear} [GeV]");
//  w3D->SetYTitle("p_{T, #bar{q}}^{smear} [GeV]");
//  w3D->SetMinimum(60.);
//  w3D->SetMaximum(100.);
//  canvasW3D->cd(4);
//  setPadStyle();
//  w3D->DrawCopy("cont1");
//
//  ptWE1SmearE2Smear->FitSlicesZ();
//  tmpName = ptWE1SmearE2Smear->GetName();
//  w3D = (TH2D*)gDirectory->Get(tmpName+"_1");
//  setAxisStyle(w3D);
//  w3D->SetStats(kFALSE);
//  w3D->SetTitle("p_{T,qq} [GeV]");
//  w3D->SetXTitle("E_{q}^{smear} [GeV]");
//  w3D->SetYTitle("E_{#bar{q}}^{smear} [GeV]");
//  w3D->SetMinimum(60.);
//  w3D->SetMaximum(100.);
//  canvasW3D->cd(5);
//  setPadStyle();
//  w3D->DrawCopy("cont1");

  //
  // produce one ps-file containing all canvases
  //

  TString psName = outDir + "/catalog.ps";
  canvasBase        ->Print(psName + "(");
  canvasRespL       ->Print(psName);
  canvasRespLPtGen  ->Print(psName);
  canvasRespLPtSmear->Print(psName);
  canvasRespB       ->Print(psName);
  canvasRespBPtGen  ->Print(psName);
  canvasRespBPtSmear->Print(psName);
  canvasMassW       ->Print(psName);
  canvasMassWPtGen  ->Print(psName);
  canvasMassWPtSmear->Print(psName);
  canvasMassT       ->Print(psName);
  canvasMassTPtGen  ->Print(psName);
  canvasMassTPtSmear->Print(psName);
  canvasW3D         ->Print(psName + ")");

  //
  // calculate and print exact bias with errors for a given pt cut value
  //

  double diffRespL[nSystematicSets];
  double diffRespB[nSystematicSets];
  double diffW    [nSystematicSets];
  double diffT    [nSystematicSets];
  double relDiffW [nSystematicSets];
  double relDiffT [nSystematicSets];
  for(unsigned i=0; i<nSystematicSets; i++) {
    diffRespL[i] = (respLPtCut[i]->GetBinContent(4) - respLPtCut[1]->GetBinContent(4)) * 100;
    diffRespB[i] = (respBPtCut[i]->GetBinContent(4) - respBPtCut[1]->GetBinContent(4)) * 100;
    diffW    [i] = massWptCut [i]->GetBinContent(4) - massWptCut[1]->GetBinContent(4);
    diffT    [i] = massTptCut [i]->GetBinContent(4) - massTptCut[1]->GetBinContent(4);
    relDiffW [i] = diffW[i] / massWptCut[1]->GetBinContent(4) * 100;
    relDiffT [i] = diffT[i] / massTptCut[1]->GetBinContent(4) * 100;
  }

  std::cout << "==========================================================================" << std::endl;

  std::cout << "Effect on light quark response with cut at " << respLPtCut[0]->GetBinCenter(4) << " GeV" << std::endl
	    << "-------------------------------------" << std::endl;
  std::cout << "Res off : "
	    << respLPtCut[1]->GetBinContent(4) << " +/- " << respLPtCut[1]->GetBinError(4) << "   (diff: "
	    << diffRespL[1] << " %)" << std::endl;
  std::cout << "Res -20 : "
	    << respLPtCut[2]->GetBinContent(4) << " +/- " << respLPtCut[2]->GetBinError(4) << "   (diff: "
	    << diffRespL[2] << " %)" << std::endl;
  std::cout << "Res std : "
	    << respLPtCut[0]->GetBinContent(4) << " +/- " << respLPtCut[0]->GetBinError(4) << "   (diff: "
	    << diffRespL[0] << " %)" << std::endl;
  std::cout << "Res +20 : "
	    << respLPtCut[3]->GetBinContent(4) << " +/- " << respLPtCut[3]->GetBinError(4) << "   (diff: "
	    << diffRespL[3] << " %)" << std::endl;

  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Effect on b quark response with cut at " << respBPtCut[0]->GetBinCenter(4) << " GeV" << std::endl
	    << "-------------------------------------" << std::endl;
  std::cout << "Res off : "
	    << respBPtCut[1]->GetBinContent(4) << " +/- " << respBPtCut[1]->GetBinError(4) << "   (diff: "
	    << diffRespB[1] << ")" << std::endl;
  std::cout << "Res -20 : "
	    << respBPtCut[2]->GetBinContent(4) << " +/- " << respBPtCut[2]->GetBinError(4) << "   (diff: "
	    << diffRespB[2] << ")" << std::endl;
  std::cout << "Res std : "
	    << respBPtCut[0]->GetBinContent(4) << " +/- " << respBPtCut[0]->GetBinError(4) << "   (diff: "
	    << diffRespB[0] << ")" << std::endl;
  std::cout << "Res +20 : "
	    << respBPtCut[3]->GetBinContent(4) << " +/- " << respBPtCut[3]->GetBinError(4) << "   (diff: "
	    << diffRespB[3] << ")" << std::endl;

  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Effect on W mass with cut at " << massWptCut[0]->GetBinCenter(4) << " GeV" << std::endl
	    << "-------------------------------------" << std::endl;
  std::cout << "Res off : "
	    << massWptCut[1]->GetBinContent(4) << " +/- " << massWptCut[1]->GetBinError(4) << " GeV   (diff: "
	    << diffW[1] << " GeV, " << relDiffW[1] << " %)" << std::endl;
  std::cout << "Res -20 : "
	    << massWptCut[2]->GetBinContent(4) << " +/- " << massWptCut[2]->GetBinError(4) << " GeV   (diff: "
	    << diffW[2] << " GeV, " << relDiffW[2] << " %)" << std::endl;
  std::cout << "Res std : "
	    << massWptCut[0]->GetBinContent(4) << " +/- " << massWptCut[0]->GetBinError(4) << " GeV   (diff: "
	    << diffW[0] << " GeV, " << relDiffW[0] << " %)" << std::endl;
  std::cout << "Res +20 : "
	    << massWptCut[3]->GetBinContent(4) << " +/- " << massWptCut[3]->GetBinError(4) << " GeV   (diff: "
	    << diffW[3] << " GeV, " << relDiffW[3] << " %)" << std::endl;

  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Effect on top mass with cut at " << massTptCut[0]->GetBinCenter(4) << " GeV" << std::endl
	    << "-------------------------------------" << std::endl;
  std::cout << "Res off : "
	    << massTptCut[1]->GetBinContent(4) << " +/- " << massTptCut[1]->GetBinError(4) << " GeV   (diff: "
	    << diffT[1] << " GeV, " << relDiffT[1] << " %)" << std::endl;
  std::cout << "Res -20 : "
	    << massTptCut[2]->GetBinContent(4) << " +/- " << massTptCut[2]->GetBinError(4) << " GeV   (diff: "
	    << diffT[2] << " GeV, " << relDiffT[2] << " %)" << std::endl;
  std::cout << "Res std : "
	    << massTptCut[0]->GetBinContent(4) << " +/- " << massTptCut[0]->GetBinError(4) << " GeV   (diff: "
	    << diffT[0] << " GeV, " << relDiffT[0] << " %)" << std::endl;
  std::cout << "Res +20 : "
	    << massTptCut[3]->GetBinContent(4) << " +/- " << massTptCut[3]->GetBinError(4) << " GeV   (diff: "
	    << diffT[3] << " GeV, " << relDiffT[3] << " %)" << std::endl;

  std::cout << "-------------------------------------" << std::endl;
  std::cout << std::setprecision(3) << std::fixed;

  // Light quark response

  double errStat    = respLPtCut[0]->GetBinError(4)*100;
  double errResUp   = diffRespL[3] - diffRespL[0];
  double errResDown = diffRespL[2] - diffRespL[0];
  double errSpect   = 0;
  if(fileName2 != "")
    errSpect = fabs(diffRespL[4] - diffRespL[0]);

  std::cout << "Light quark resp. --> " << diffRespL[0]
	    << " +/-" << errStat << " (stat)"
	    << " +" << errResUp << errResDown << " (res)";
  if(fileName2 != "")
    std::cout << " +/-" << errSpect  << " (spect)";
  std::cout << " %" << std::endl;

  std::cout << "                    = " << diffRespL[0]
	    << " +" << addQuadratic(errStat, errResUp, errSpect)
	    << " -" << addQuadratic(errStat, errResDown, errSpect)
	    << " %" << std::endl;

  // B quark response

  errStat    = respBPtCut[0]->GetBinError(4)*100;
  errResUp   = diffRespB[3] - diffRespB[0];
  errResDown = diffRespB[2] - diffRespB[0];
  errSpect   = 0;
  if(fileName2 != "")
    errSpect = fabs(diffRespB[4] - diffRespB[0]);

  std::cout << "B quark resp.     --> " << diffRespB[0]
	    << " +/-" << errStat << " (stat)"
	    << " +" << errResUp << errResDown << " (res)";
  if(fileName2 != "")
    std::cout << " +/-" << errSpect  << " (spect)";
  std::cout << " %" << std::endl;

  std::cout << "                    = " << diffRespB[0]
	    << " +" << addQuadratic(errStat, errResUp, errSpect)
	    << " -" << addQuadratic(errStat, errResDown, errSpect)
	    << " %" << std::endl;

  // W mass

  errStat    = addQuadratic(massWptCut[0]->GetBinError(4), massWptCut[1]->GetBinError(4));
  errResUp   = diffW[3] - diffW[0];
  errResDown = diffW[2] - diffW[0];
  errSpect   = 0;
  if(fileName2 != "")
    errSpect = fabs(diffW[4] - diffW[0]);

  std::cout << "W mass            --> " << diffW[0]
	    << " +/-" << errStat << " (stat)"
	    << " +" << errResUp << errResDown << " (res)";
  if(fileName2 != "")
    std::cout << " +/-" << errSpect  << " (spect)";
  std::cout << " GeV" << std::endl;

  std::cout << "                    = " << diffW[0]
	    << " +" << addQuadratic(errStat, errResUp, errSpect)
	    << " -" << addQuadratic(errStat, errResDown, errSpect)
	    << " GeV" << std::endl;

  errStat    = addQuadratic(massWptCut[0]->GetBinError(4)/massWptCut[0]->GetBinContent(4),
			    massWptCut[1]->GetBinError(4)/massWptCut[1]->GetBinContent(4))
    *massWptCut[0]->GetBinContent(4)/massWptCut[1]->GetBinContent(4)*100;
  errResUp   = relDiffW[3] - relDiffW[0];
  errResDown = relDiffW[2] - relDiffW[0];
  errSpect   = 0;
  if(fileName2 != "")
    errSpect = fabs(relDiffW[4] - relDiffW[0]);

  std::cout << "                  --> " << relDiffW[0]
	    << " +/-" << errStat << " (stat)"
	    << " +" << errResUp << errResDown << " (res)";
  if(fileName2 != "")
    std::cout << " +/-" << errSpect  << " (spect)";
  std::cout << " %" << std::endl;

  std::cout << "                    = " << relDiffW[0]
	    << " +" << addQuadratic(errStat, errResUp, errSpect)
	    << " -" << addQuadratic(errStat, errResDown, errSpect)
	    << " %" << std::endl;

  // T mass

  errStat    = addQuadratic(massTptCut[0]->GetBinError(4), massTptCut[1]->GetBinError(4));
  errResUp   = diffT[3] - diffT[0];
  errResDown = diffT[2] - diffT[0];
  errSpect   = 0;
  if(fileName2 != "")
    errSpect = fabs(diffT[4] - diffT[0]);

  std::cout << "Top mass          --> " << diffT[0]
	    << " +/-" << errStat << " (stat)"
	    << " +" << errResUp << errResDown << " (res)";
  if(fileName2 != "")
    std::cout << " +/-" << errSpect  << " (spect)";
  std::cout << " GeV" << std::endl;

  std::cout << "                    = " << diffT[0]
	    << " +" << addQuadratic(errStat, errResUp, errSpect)
	    << " -" << addQuadratic(errStat, errResDown, errSpect)
	    << " GeV" << std::endl;

  errStat    = addQuadratic(massTptCut[0]->GetBinError(4)/massTptCut[0]->GetBinContent(4),
			    massTptCut[1]->GetBinError(4)/massTptCut[1]->GetBinContent(4))
    *massTptCut[0]->GetBinContent(4)/massTptCut[1]->GetBinContent(4)*100;
  errResUp   = relDiffT[3] - relDiffT[0];
  errResDown = relDiffT[2] - relDiffT[0];
  errSpect   = 0;
  if(fileName2 != "")
    errSpect = fabs(relDiffT[4] - relDiffT[0]);

  std::cout << "                  --> " << relDiffT[0]
	    << " +/-" << errStat << " (stat)"
	    << " +" << errResUp << errResDown << " (res)";
  if(fileName2 != "")
    std::cout << " +/-" << errSpect  << " (spect)";
  std::cout << " %" << std::endl;

  std::cout << "                    = " << relDiffT[0]
	    << " +" << addQuadratic(errStat, errResUp, errSpect)
	    << " -" << addQuadratic(errStat, errResDown, errSpect)
	    << " %" << std::endl;

  std::cout << "==========================================================================" << std::endl;

  //
  // the end
  //

  return 0;
}

int main(int argc, char** argv)
{
  return analyzeJetEnergyResolutionBias(argv[1], argv[2]);
}
