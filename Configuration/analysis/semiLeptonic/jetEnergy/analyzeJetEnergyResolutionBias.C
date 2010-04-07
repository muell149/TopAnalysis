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
  txt->SetFillColor(0);
  txt->SetBorderSize(0);
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
      // check if new fitting range is within range of axis
      if( mean-1.5*sigma >= hist->GetYaxis()->GetXmin() &&
	  mean+1.5*sigma <  hist->GetYaxis()->GetXmax() ) {
	// only perform second gauss fit if sigma > bin width
	if( sigma > hist->GetBinWidth(hist->FindBin(hist->GetBinCenter(hist->GetBin(bx)), mean)) ) {
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
    fitGauss2D(hists[d], means, sigmas);

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
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFontSize(.05);
  gStyle->SetTitleX(.4);
  gStyle->SetTitleY(.995);
  gStyle->SetErrorX(0.);
 
  //
  // get histos from file
  //

  TH1F* pt[2];
  TH1F* ptSmeared[2];
  TH1F* energy[2];
  TH1F* energySmeared[2];
  TH1F* eta[2];
  TH1F* theta[2];

  TH2F* energySmearVsGen;

  TH1F* enResp[6][nSystematicSets];
  TH1F* resp  [6][nSystematicSets];
  TH1F* mW    [6][nSystematicSets];
  TH1F* mT    [6][nSystematicSets];

  TH2F* respPtGen  [6][4];
  TH2F* respPtSmear[6][4];

  TH2F* mWPtGen  [6][4];
  TH2F* mWPtSmear[6][4];

  TH2F* mTPtGen  [6][4];
  TH2F* mTPtSmear[6][4];

  TH3F* massWPt1SmearPt2Smear;
  TH3F* massWE1SmearE2Smear;
  TH3F* ptWPt1SmearPt2Smear;
  TH3F* ptWE1SmearE2Smear;

  TString inDirBase = "analyzeJetEnergyResolutionBias";

  TString dirExt[4] = {"",       // standard pt resolution 
		       "_off",   // no pt smearing
		       "_m20",   // resolution 20% better
		       "_p20"};  // resolution 20% worse

  unsigned iMaxFile = 0;
  if(fileName2 != "")
    iMaxFile = 1;

  for(unsigned iFile=0; iFile <= iMaxFile; ++iFile) {
    pt           [iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/pt" );
    ptSmeared    [iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/ptSmeared");
    energy       [iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/energy" );
    energySmeared[iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/energySmeared");
    eta          [iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/eta");
    theta        [iFile] = cloneObjectFromFile<TH1F*>(file[iFile], inDirBase + "/theta");
  }

  energySmearVsGen = cloneObjectFromFile<TH2F*>(file[0], inDirBase + "/energySmearVsGen");

  for(unsigned i = 0; i < 6; i++) {

    for(unsigned d = 0; d < 4; d++) {

      TString inDir = inDirBase + dirExt[d];

      TString name = inDir + "/energySmearOverGen_"; name += (i*10);
      enResp[i][d] = cloneObjectFromFile<TH1F*>(file[0], name);

      name = inDir + "/resp_"; name += (i*10);
      resp[i][d] = cloneObjectFromFile<TH1F*>(file[0], name);

      name = inDir + "/respPt_"; name += (i*10);
      respPtGen[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);
      name = inDir + "/respPtSmear_"; name += (i*10);
      respPtSmear[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);

      if(inDir.Contains("_off")) {
	name = inDir + "/massWzoom_"; name += (i*10);
	mW[i][d] = cloneObjectFromFile<TH1F*>(file[0], name);
	name = inDir + "/massTzoom_"; name += (i*10);
	mT[i][d] = cloneObjectFromFile<TH1F*>(file[0], name);
      }
      else {
	name = inDir + "/massW_"; name += (i*10);
	mW[i][d] = cloneObjectFromFile<TH1F*>(file[0], name);
	name = inDir + "/massT_"; name += (i*10);
	mT[i][d] = cloneObjectFromFile<TH1F*>(file[0], name);
      }

      name = inDir + "/massWPt_"; name += (i*10);
      mWPtGen[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);
      name = inDir + "/massWPtSmear_"; name += (i*10);
      mWPtSmear[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);
      name = inDir + "/massTPt_"; name += (i*10);
      mTPtGen[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);
      name = inDir + "/massTPtSmear_"; name += (i*10);
      mTPtSmear[i][d] = cloneObjectFromFile<TH2F*>(file[0], name);

    }

  }

  massWPt1SmearPt2Smear = cloneObjectFromFile<TH3F*>(file[0], inDirBase + "/massWPt1SmearPt2Smear");
  massWE1SmearE2Smear   = cloneObjectFromFile<TH3F*>(file[0], inDirBase + "/massWE1SmearE2Smear");
  ptWPt1SmearPt2Smear   = cloneObjectFromFile<TH3F*>(file[0], inDirBase + "/ptWPt1SmearPt2Smear");
  ptWE1SmearE2Smear     = cloneObjectFromFile<TH3F*>(file[0], inDirBase + "/ptWE1SmearE2Smear");

  file[0]->Close();

  if(fileName2 != "") {
    for(unsigned i = 0; i < 6; i++) {
      TString name = inDirBase + "/energySmearOverGen_"; name += (i*10);
      enResp[i][4] = cloneObjectFromFile<TH1F*>(file[1], name);
      name = inDirBase + "/resp_"; name += (i*10);
      resp[i][4] = cloneObjectFromFile<TH1F*>(file[1], name);
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
  TCanvas* canvasEnResp       = new TCanvas("canvasEnResp"      , "canvasEnResp"      , 900, 900);
  TCanvas* canvasResp         = new TCanvas("canvasResp"        , "canvasResp"        , 900, 900);
  TCanvas* canvasRespPtGen    = new TCanvas("canvasRespPtGen"   , "canvasRespPtGen"   , 900, 900);
  TCanvas* canvasRespPtSmear  = new TCanvas("canvasRespPtSmear" , "canvasRespPtSmear" , 900, 900);
  TCanvas* canvasMassW        = new TCanvas("canvasMassW"       , "canvasMassW"       , 900, 900);
  TCanvas* canvasMassWPtGen   = new TCanvas("canvasMassWPtGen"  , "canvasMassWPtGen"  , 900, 900);
  TCanvas* canvasMassWPtSmear = new TCanvas("canvasMassWPtSmear", "canvasMassWPtSmear", 900, 900);
  TCanvas* canvasMassT        = new TCanvas("canvasMassT"       , "canvasMassT"       , 900, 900);
  TCanvas* canvasMassTPtGen   = new TCanvas("canvasMassTPtGen"  , "canvasMassTPtGen"  , 900, 900);
  TCanvas* canvasMassTPtSmear = new TCanvas("canvasMassTPtSmear", "canvasMassTPtSmear", 900, 900);
  TCanvas* canvasW3D          = new TCanvas("canvasMassW3D"     , "canvasMassW3D"     , 900, 900);
  canvasBase        ->Divide(3,3);
  canvasEnResp      ->Divide(3,3);
  canvasResp        ->Divide(3,3);
  canvasRespPtGen   ->Divide(3,3);
  canvasRespPtSmear ->Divide(3,3);
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

  setAxisStyle(pt[0]);
  //  pt[0]->Scale(1./pt[0]->Integral());
  pt[0]->SetTitle("");
  pt[0]->SetXTitle("p_{T}^{gen} (parton) [GeV]");
  pt[0]->SetYTitle("partons");
  pt[0]->SetStats(kFALSE);
  canvasBase->cd(1);
  setPadStyle();
  pt[0]->DrawCopy();
//  if(fileName2!="") {
//    pt[1]->Scale(1./pt[1]->Integral());
//    pt[1]->SetLineColor(kRed);
//    pt[1]->DrawCopy("same");
//  }
  TPaveText* txtPt = new TPaveText(0.5, 0.73, 0.88, 0.88, "NDC");
  setPaveTextStyle(txtPt, 32);
  sprintf(tmpTxt, "Mean = %4.2f #pm", pt[0]->GetMean());
  txtPt->AddText(tmpTxt);
  sprintf(tmpTxt, "%4.2f GeV", pt[0]->GetMeanError());
  txtPt->AddText(tmpTxt);
  txtPt->Draw();
  gPad->Print(outDir + "/ptGen.eps");

  setAxisStyle(energy[0]);
  //  energy[0]->Scale(1./energy[0]->Integral());
  energy[0]->SetTitle("");
  energy[0]->SetXTitle("E^{gen} (parton) [GeV]");
  energy[0]->SetYTitle("partons");
  energy[0]->SetStats(kFALSE);
  canvasBase->cd(2);
  setPadStyle();
  energy[0]->DrawCopy();
//  if(fileName2!="") {
//    energy[1]->Scale(1./energy[1]->Integral());
//    energy[1]->SetLineColor(kRed);
//    energy[1]->DrawCopy("same");
//  }
  TPaveText* txtEnergy = new TPaveText(0.5, 0.73, 0.88, 0.88, "NDC");
  setPaveTextStyle(txtEnergy, 32);
  sprintf(tmpTxt, "Mean = %4.1f #pm", energy[0]->GetMean());
  txtEnergy->AddText(tmpTxt);
  sprintf(tmpTxt, "%4.1f GeV", energy[0]->GetMeanError());
  txtEnergy->AddText(tmpTxt);
  txtEnergy->Draw();
  gPad->Print(outDir + "/energyGen.eps");

  setAxisStyle(eta[0]);
  //  eta[0]->Scale(1./eta[0]->Integral());
  eta[0]->SetTitle("");
  eta[0]->SetXTitle("#eta (parton)");
  eta[0]->SetYTitle("a.u.");
  eta[0]->SetStats(kFALSE);
  canvasBase->cd(3);
  setPadStyle();
  eta[0]->DrawCopy();
//  if(fileName2!="") {
//    eta[1]->Scale(1./eta[1]->Integral());
//    eta[1]->SetLineColor(kRed);
//    eta[1]->DrawCopy("same");
//  }
  gPad->Print(outDir + "/eta.eps");

  setAxisStyle(ptSmeared[0]);
  ptSmeared[0]->SetTitle("");
  ptSmeared[0]->SetXTitle("p_{T}^{smear} (parton) [GeV]");
  ptSmeared[0]->SetYTitle("partons");
  ptSmeared[0]->SetStats(kFALSE);
  canvasBase->cd(4);
  setPadStyle();
  ptSmeared[0]->DrawCopy();
  TPaveText* txtPtSmeared = new TPaveText(0.5, 0.73, 0.88, 0.88, "NDC");
  setPaveTextStyle(txtPtSmeared, 32);
  sprintf(tmpTxt, "Mean = %4.2f #pm", ptSmeared[0]->GetMean());
  txtPtSmeared->AddText(tmpTxt);
  sprintf(tmpTxt, "%4.2f GeV", ptSmeared[0]->GetMeanError());
  txtPtSmeared->AddText(tmpTxt);
  txtPtSmeared->Draw();
  gPad->Print(outDir + "/ptSmeared.eps");

  setAxisStyle(energySmeared[0]);
  energySmeared[0]->SetTitle("");
  energySmeared[0]->SetXTitle("E^{smear} (parton) [GeV]");
  energySmeared[0]->SetYTitle("partons");
  energySmeared[0]->SetStats(kFALSE);
  canvasBase->cd(5);
  setPadStyle();
  energySmeared[0]->DrawCopy();
  TPaveText* txtEnergySmeared = new TPaveText(0.5, 0.73, 0.88, 0.88, "NDC");
  setPaveTextStyle(txtEnergySmeared, 32);
  sprintf(tmpTxt, "Mean = %4.1f #pm", energySmeared[0]->GetMean());
  txtEnergySmeared->AddText(tmpTxt);
  sprintf(tmpTxt, "%4.1f GeV", energySmeared[0]->GetMeanError());
  txtEnergySmeared->AddText(tmpTxt);
  txtEnergySmeared->Draw();
  gPad->Print(outDir + "/energySmeared.eps");

  fitGauss2D(energySmearVsGen, means, sigmas);
  canvasBase->cd(6);
  setPadStyle();
  setAxisStyle(&sigmas);
  sigmas.SetMinimum(.0);
  sigmas.SetMaximum(1.);
  sigmas.SetStats(kFALSE);
  sigmas.SetTitle("");
  sigmas.SetXTitle("E (parton) [GeV]");
  sigmas.SetYTitle("#sigma (E) / E");
  sigmas.DrawCopy("E1");
  if(sigmas.GetEntries() > 0) {
    TF1* f = new TF1("f","sqrt([0]*[0]/(x*x)+[1]*[1]/x+[2]*[2])", 0., 250.);
    sigmas.Fit(f, "0");
    sigmas.GetFunction("f")->SetLineWidth(1);
    sigmas.GetFunction("f")->SetLineColor(kGray);
    sigmas.GetFunction("f")->DrawCopy("same");
    
    TPaveText* txtEsOg = new TPaveText(0.35, 0.68, 0.89, 0.88, "NDC");
    setPaveTextStyle(txtEsOg);
    
    double N     = sigmas.GetFunction("f")->GetParameter(0);
    double N_err = sigmas.GetFunction("f")->GetParError (0);
    double S     = sigmas.GetFunction("f")->GetParameter(1);
    double S_err = sigmas.GetFunction("f")->GetParError (1);
    double C     = sigmas.GetFunction("f")->GetParameter(2);
    double C_err = sigmas.GetFunction("f")->GetParError (2);
    sprintf(tmpTxt, "N = %4.2f #pm %4.2f GeV", N, N_err);
    txtEsOg->AddText(tmpTxt);
    sprintf(tmpTxt, "S = %4.2f #pm %4.2f  #sqrt{GeV}", S, S_err);
    txtEsOg->AddText(tmpTxt);
    sprintf(tmpTxt, "C = %4.2f #pm %4.2f", C, C_err);
    txtEsOg->AddText(tmpTxt);
    
    txtEsOg->Draw();
  }
  gPad->Print(outDir + "/resolution.eps");

  setAxisStyle(theta[0]);
  //  theta[0]->Scale(1./theta[0]->Integral());
  theta[0]->SetStats(kFALSE);
  theta[0]->SetTitle("");
  theta[0]->SetXTitle("#theta_{q #bar{q}}");
  theta[0]->SetYTitle("events");
  canvasBase->cd(7);
  setPadStyle();
  theta[0]->DrawCopy();
//  if(fileName2!="") {
//    theta[1]->Scale(1./theta[1]->Integral());
//    theta[1]->SetLineColor(kRed);
//    theta[1]->DrawCopy("same");
//  }
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

    canvasEnResp->cd(i+1);
    setPadStyle();
    setAxisStyle(enResp[i][0]);
    enResp[i][0]->SetStats(kFALSE);
    enResp[i][0]->SetTitle(title);
    enResp[i][0]->SetXTitle("E^{smear} / E^{gen} (parton)");
    enResp[i][0]->SetYTitle("partons");
    enResp[i][0]->DrawCopy();

    canvasResp->cd(i+1);
    setPadStyle();
    setAxisStyle(resp[i][0]);
    resp[i][0]->SetStats(kFALSE);
    resp[i][0]->SetTitle(title);
    resp[i][0]->SetXTitle("p_{T}^{smear} / p_{T}^{gen} (parton)");
    resp[i][0]->SetYTitle("partons");
    resp[i][0]->DrawCopy();

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

    drawAndFitTwo2D(respPtGen[i], i, .95, 1.9, title,
		    "p_{T}^{gen} (parton) [GeV]", "p_{T}^{smear} / p_{T}^{gen} (parton)", canvasRespPtGen);

    drawAndFitTwo2D(respPtSmear[i], i, .87, 1.06, title,
		    "p_{T}^{smear} (parton) [GeV]", "p_{T}^{smear} / p_{T}^{gen} (parton)", canvasRespPtSmear);

    drawAndFitTwo2D(mWPtGen[i], i, 76., 114., title,
		    "p_{T}^{gen} (parton) [GeV]", "m_{qq} [GeV]", canvasMassWPtGen);

    drawAndFitTwo2D(mWPtSmear[i], i, 73., 86., title,
		    "p_{T}^{smear} (parton) [GeV]", "m_{qq} [GeV]", canvasMassWPtSmear);

    drawAndFitTwo2D(mTPtGen[i], i, 168., 216., title,
		    "p_{T}^{gen} (parton) [GeV]", "m_{qqb} [GeV]", canvasMassTPtGen);

    drawAndFitTwo2D(mTPtSmear[i], i, 163., 181., title,
		    "p_{T}^{smear} (parton) [GeV]", "m_{qqb} [GeV]", canvasMassTPtSmear);

  }

  canvasRespPtGen->cd(7);
  drawAndFitTwo2D(respPtGen[3], 3, .99, 1.09, "p_{T}^{smear} > 30 GeV",
		  "p_{T}^{gen} (parton) [GeV]", "p_{T}^{smear} / p_{T}^{gen} (parton)");

  canvasRespPtSmear->cd(7);
  drawAndFitTwo2D(respPtSmear[3], 3, .99, 1.09, "p_{T}^{smear} > 30 GeV",
		  "p_{T}^{smear} (parton) [GeV]", "p_{T}^{smear} / p_{T}^{gen} (parton)");

  canvasMassWPtGen->cd(7);
  drawAndFitTwo2D(mWPtGen[3], 3, 77., 85., "p_{T}^{smear} > 30 GeV",
		  "p_{T}^{gen} (parton) [GeV]", "m_{qq} [GeV]");

  canvasMassWPtSmear->cd(7);
  drawAndFitTwo2D(mWPtSmear[3], 3, 77., 85., "p_{T}^{smear} > 30 GeV",
		  "p_{T}^{smear} (parton) [GeV]", "m_{qq} [GeV]");

  canvasMassTPtGen->cd(7);
  drawAndFitTwo2D(mTPtGen[3], 3, 165., 180., "p_{T}^{smear} > 30 GeV",
		  "p_{T}^{gen} (parton) [GeV]", "m_{qqb} [GeV]");

  canvasMassTPtSmear->cd(7);
  drawAndFitTwo2D(mTPtSmear[3], 3, 165., 180., "p_{T}^{smear} > 30 GeV",
		  "p_{T}^{smear} (parton) [GeV]", "m_{qqb} [GeV]");

  TH1F* enRespPtCut[nSystematicSets];
  TH1F* respPtCut  [nSystematicSets];
  TH1F* massWptCut [nSystematicSets];
  TH1F* massTptCut [nSystematicSets];
  for(unsigned d = 0; d < nSystematicSets; d++) {
    TString name = "enRespPtCut_"; name += d;
    enRespPtCut [d] = new TH1F(name, name, 6, -5., 55.);
    name = "respPtCut_"; name += d;
    respPtCut [d] = new TH1F(name, name, 6, -5., 55.);
    name = "massWpCut_"; name += d;
    massWptCut[d] = new TH1F(name, name, 6, -5., 55.);
    name = "massTpCut_"; name += d;
    massTptCut[d] = new TH1F(name, name, 6, -5., 55.);

    for(unsigned i = 0; i < 6; i++) {
      bool draw = false;
      if(d==0) draw = true;
      canvasEnResp->cd(i+1);
      fitGauss1D(enResp[i][d], enRespPtCut[d], i+1, draw);
      canvasResp->cd(i+1);
      fitGauss1D(resp[i][d], respPtCut [d], i+1, draw);
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

  canvasEnResp->cd(7);
  setPadStyle();
  setAxisStyle(enRespPtCut[1]);
  enRespPtCut[1]->GetXaxis()->SetNdivisions(205);
  enRespPtCut[1]->SetStats(kFALSE);
  enRespPtCut[1]->SetTitle("");
  enRespPtCut[1]->SetXTitle("p_{T , cut}^{smear} [GeV]");
  enRespPtCut[1]->SetYTitle("E^{smear} / E^{gen} (parton)");
  enRespPtCut[1]->SetMinimum(0.998);
  enRespPtCut[1]->SetMaximum(1.034);
  enRespPtCut[1]->SetLineColor(kBlue);
  enRespPtCut[1]->SetLineStyle(2);
  enRespPtCut[0]->SetFillColor(kGray);
  enRespPtCut[2]->SetFillColor(kGreen);
  enRespPtCut[3]->SetFillColor(kRed);
  enRespPtCut[1]->DrawCopy("hist");
  enRespPtCut[2]->DrawCopy("E3 same");
  enRespPtCut[3]->DrawCopy("E3 same");
  enRespPtCut[0]->DrawCopy("E3 same");
  enRespPtCut[0]->DrawCopy("E1 same");
  TLegend* legend = new TLegend(0.3, 0.69, 0.6, 0.89);
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->AddEntry(enRespPtCut[3], " #sigma +20%", "F");
  legend->AddEntry(enRespPtCut[2], " #sigma -20%", "F");
  legend->Draw();
  gPad->Print(outDir + "/enRespPtCut.eps");

  canvasResp->cd(7);
  setPadStyle();
  setAxisStyle(respPtCut[1]);
  respPtCut[1]->GetXaxis()->SetNdivisions(205);
  respPtCut[1]->SetStats(kFALSE);
  respPtCut[1]->SetTitle("");
  respPtCut[1]->SetXTitle("p_{T , cut}^{smear} [GeV]");
  respPtCut[1]->SetYTitle("p_{T}^{smear} / p_{T}^{gen} (parton)");
  respPtCut[1]->SetMinimum(0.998);
  respPtCut[1]->SetMaximum(1.034);
  respPtCut[1]->SetLineColor(kBlue);
  respPtCut[1]->SetLineStyle(2);
  respPtCut[0]->SetFillColor(kGray);
  respPtCut[2]->SetFillColor(kGreen);
  respPtCut[3]->SetFillColor(kRed);
  respPtCut[1]->DrawCopy("hist");
  respPtCut[2]->DrawCopy("E3 same");
  respPtCut[3]->DrawCopy("E3 same");
  //  respPtCut[4]->SetFillColor(kYellow);
  //  respPtCut[4]->DrawCopy("E3 same");
  respPtCut[0]->DrawCopy("E3 same");
  respPtCut[0]->DrawCopy("E1 same");
  legend->Draw();
  gPad->Print(outDir + "/respPtCut.eps");

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
  //  massWptCut[4]->SetFillColor(kYellow);
  //  massWptCut[4]->DrawCopy("E3 same");
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
  massTptCut[1]->SetMinimum(170.);
  massTptCut[1]->SetMaximum(179.);
  massTptCut[1]->SetLineColor(kBlue);
  massTptCut[1]->SetLineStyle(2);
  massTptCut[0]->SetFillColor(kGray);
  massTptCut[2]->SetFillColor(kGreen);
  massTptCut[3]->SetFillColor(kRed);
  massTptCut[1]->DrawCopy("hist");
  massTptCut[2]->DrawCopy("E3 same");
  massTptCut[3]->DrawCopy("E3 same");
  //  massTptCut[4]->SetFillColor(kYellow);
  //  massTptCut[4]->DrawCopy("E3 same");
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
    canvasRespPtGen->cd(i+1);
    if(i!=0)
      legendUpperRight->Draw();
    TString epsName = outDir+"/respPtGen_means_";
    if(i==6)
      epsName += "30_zoom";
    else
      epsName += (i*10);
    gPad->Print(epsName + ".eps");

    canvasRespPtSmear->cd(i+1);
    epsName = outDir+"/respPtSmear_means_";
    if(i==6) {
      legendUpperRight->Draw();
      epsName += "30_zoom";
    }
    else {
      legendLowerRight->Draw();
      epsName += (i*10);
    }
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
  canvasEnResp      ->Print(psName);
  canvasResp        ->Print(psName);
  canvasRespPtGen   ->Print(psName);
  canvasRespPtSmear ->Print(psName);
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

  double diffEnResp[nSystematicSets];
  double diffResp  [nSystematicSets];
  double diffW     [nSystematicSets];
  double diffT     [nSystematicSets];
  double relDiffW  [nSystematicSets];
  double relDiffT  [nSystematicSets];
  for(unsigned i=0; i<nSystematicSets; i++) {
    diffEnResp[i] = (enRespPtCut[i]->GetBinContent(4) - enRespPtCut[1]->GetBinContent(4)) * 100;
    diffResp  [i] = (respPtCut  [i]->GetBinContent(4) - respPtCut  [1]->GetBinContent(4)) * 100;
    diffW     [i] = massWptCut [i]->GetBinContent(4) - massWptCut [1]->GetBinContent(4);
    diffT     [i] = massTptCut [i]->GetBinContent(4) - massTptCut [1]->GetBinContent(4);
    relDiffW  [i] = diffW[i] / massWptCut[1]->GetBinContent(4) * 100;
    relDiffT  [i] = diffT[i] / massTptCut[1]->GetBinContent(4) * 100;
  }

  std::cout << "==========================================================================" << std::endl;

  std::cout << "Effect on energy response with cut at " << enRespPtCut[0]->GetBinCenter(4) << " GeV" << std::endl
	    << "-------------------------------------" << std::endl;
  std::cout << "Res off : "
	    << enRespPtCut[1]->GetBinContent(4) << " +/- " << enRespPtCut[1]->GetBinError(4) << "   (diff: "
	    << diffEnResp[1] << " %)" << std::endl;
  std::cout << "Res -20 : "
	    << enRespPtCut[2]->GetBinContent(4) << " +/- " << enRespPtCut[2]->GetBinError(4) << "   (diff: "
	    << diffEnResp[2] << " %)" << std::endl;
  std::cout << "Res std : "
	    << enRespPtCut[0]->GetBinContent(4) << " +/- " << enRespPtCut[0]->GetBinError(4) << "   (diff: "
	    << diffEnResp[0] << " %)" << std::endl;
  std::cout << "Res +20 : "
	    << enRespPtCut[3]->GetBinContent(4) << " +/- " << enRespPtCut[3]->GetBinError(4) << "   (diff: "
	    << diffEnResp[3] << " %)" << std::endl;

  std::cout << "-------------------------------------" << std::endl;
  std::cout << "Effect on pt response with cut at " << respPtCut[0]->GetBinCenter(4) << " GeV" << std::endl
	    << "-------------------------------------" << std::endl;
  std::cout << "Res off : "
	    << respPtCut[1]->GetBinContent(4) << " +/- " << respPtCut[1]->GetBinError(4) << "   (diff: "
	    << diffResp[1] << ")" << std::endl;
  std::cout << "Res -20 : "
	    << respPtCut[2]->GetBinContent(4) << " +/- " << respPtCut[2]->GetBinError(4) << "   (diff: "
	    << diffResp[2] << ")" << std::endl;
  std::cout << "Res std : "
	    << respPtCut[0]->GetBinContent(4) << " +/- " << respPtCut[0]->GetBinError(4) << "   (diff: "
	    << diffResp[0] << ")" << std::endl;
  std::cout << "Res +20 : "
	    << respPtCut[3]->GetBinContent(4) << " +/- " << respPtCut[3]->GetBinError(4) << "   (diff: "
	    << diffResp[3] << ")" << std::endl;

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
  std::cout << "Effect on T mass with cut at " << massTptCut[0]->GetBinCenter(4) << " GeV" << std::endl
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

  // E response

  double errStat    = enRespPtCut[0]->GetBinError(4)*100;
  double errResUp   = diffEnResp[3] - diffEnResp[0];
  double errResDown = diffEnResp[2] - diffEnResp[0];
  double errSpect   = 0;
  if(fileName2 != "")
    errSpect = fabs(diffEnResp[4] - diffEnResp[0]);

  std::cout << "E response  --> " << diffEnResp[0]
	    << " +/-" << errStat << " (stat)"
	    << " +" << errResUp << errResDown << " (res)";
  if(fileName2 != "")
    std::cout << " +/-" << errSpect  << " (spect)";
  std::cout << " %" << std::endl;

  std::cout << "              = " << diffEnResp[0]
	    << " +" << addQuadratic(errStat, errResUp, errSpect)
	    << " -" << addQuadratic(errStat, errResDown, errSpect)
	    << " %" << std::endl;

  // Pt response

  errStat    = respPtCut[0]->GetBinError(4)*100;
  errResUp   = diffResp[3] - diffResp[0];
  errResDown = diffResp[2] - diffResp[0];
  errSpect   = 0;
  if(fileName2 != "")
    errSpect = fabs(diffResp[4] - diffResp[0]);

  std::cout << "Pt response --> " << diffResp[0]
	    << " +/-" << errStat << " (stat)"
	    << " +" << errResUp << errResDown << " (res)";
  if(fileName2 != "")
    std::cout << " +/-" << errSpect  << " (spect)";
  std::cout << " %" << std::endl;

  std::cout << "              = " << diffResp[0]
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

  std::cout << "W mass      --> " << diffW[0]
	    << " +/-" << errStat << " (stat)"
	    << " +" << errResUp << errResDown << " (res)";
  if(fileName2 != "")
    std::cout << " +/-" << errSpect  << " (spect)";
  std::cout << " GeV" << std::endl;

  std::cout << "              = " << diffW[0]
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

  std::cout << "            --> " << relDiffW[0]
	    << " +/-" << errStat << " (stat)"
	    << " +" << errResUp << errResDown << " (res)";
  if(fileName2 != "")
    std::cout << " +/-" << errSpect  << " (spect)";
  std::cout << " %" << std::endl;

  std::cout << "              = " << relDiffW[0]
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

  std::cout << "T mass      --> " << diffT[0]
	    << " +/-" << errStat << " (stat)"
	    << " +" << errResUp << errResDown << " (res)";
  if(fileName2 != "")
    std::cout << " +/-" << errSpect  << " (spect)";
  std::cout << " GeV" << std::endl;

  std::cout << "              = " << diffT[0]
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

  std::cout << "            --> " << relDiffT[0]
	    << " +/-" << errStat << " (stat)"
	    << " +" << errResUp << errResDown << " (res)";
  if(fileName2 != "")
    std::cout << " +/-" << errSpect  << " (spect)";
  std::cout << " %" << std::endl;

  std::cout << "              = " << relDiffT[0]
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
