#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TROOT.h>
#include <TStyle.h>
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

  TString histName = hist->GetName();

  // fit a gaussian in all x-bins
  TObjArray tmp;
  hist->FitSlicesY(0,0,-1,0,"QNR",&tmp);

  // get histos with mean and sigma of gaussians and clone them
  TH1D* means  = (TH1D*) tmp.FindObject(histName+"_1")->Clone(histName+"_1_0");
  TH1D* sigmas = (TH1D*) tmp.FindObject(histName+"_2")->Clone(histName+"_2_0");

  // clean-up
  tmp.Delete();

  // loop over all x-bins
  for(int bx = 1; bx <= hist->GetNbinsX(); bx++) {
    // sum bin contents along y-axis
    double bincontent = 0;
    for(int by = 1; by <= hist->GetNbinsY(); by++)
      bincontent += hist->GetBinContent(bx, by);
    ////// hist->GetXaxis()->SetRange(bx, bx);
    // remove x-bins that have less than 20 entries along y
    // (this assumes weight=1 for all entries)
    if(bincontent<20) { ////// || hist->GetMean(2) / hist->GetRMS(2) <= 3
      means->SetBinContent(bx, 0.);
      means->SetBinError  (bx, 0.);
    }
    // perform a second gauss fit for all other bins
    // restricting the fitting range according to
    // mean and sigma from the first gauss fit
    else {
      double mean  = means ->GetBinContent(bx);
      double sigma = sigmas->GetBinContent(bx);
      TF1* f = new TF1("f","gaus", mean-1.5*sigma, mean+1.5*sigma);
      hist->FitSlicesY(f,bx,bx,0,"QNR",&tmp);
      mean  = ((TH1D*) tmp.FindObject(histName+"_1"))->GetBinContent(bx);
      sigma = ((TH1D*) tmp.FindObject(histName+"_1"))->GetBinError  (bx);
      means->SetBinContent(bx, mean );
      means->SetBinError  (bx, sigma);
      tmp.Delete();
    }
  }
  // reset range
  ////// hist->GetXaxis()->SetRange(1, hist->GetNbinsX());

  // clean-up
  delete sigmas;

  // return result
  return means;

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

void hatch_bin(TH1 *thisHisto, Int_t bin, TString option = "", Double_t ymax_fac = 1.)
{

  Double_t xmin = thisHisto->GetBinLowEdge(bin);
  Double_t xmax = xmin + thisHisto->GetBinWidth(bin);
  Double_t ymin = thisHisto->GetMinimum();
  Double_t ymax = ymax_fac*thisHisto->GetMaximum();
  // draw box
  TBox *box = new TBox();
  box->SetFillStyle(3944);
  box->SetFillColor(kGray);
  box->DrawBox(xmin, ymin, xmax, ymax);
  // draw lines at left and right border if desired
  if(option.Contains("bl") || option.Contains("br")) {
    TLine *line = new TLine();
    line->SetLineColor(40);
    line->SetLineStyle(2);
    if(option.Contains("bl")) line->DrawLine(xmin, ymin, xmin, ymax);
    if(option.Contains("br")) line->DrawLine(xmax, ymin, xmax, ymax);
  }
  gPad->RedrawAxis();

}

//                       (L1)(L2) L3 (L4) L5 (L6) L7
int markerColor[8] = { 2,  6,  6,  4,  6,  1,  6,  8};
int markerStyle[8] = {22, 24, 24, 23, 24, 20, 24, 29};

void drawResponse(TH2F* hist, const unsigned i, const TString xTitle, const TString yTitle, const TString hTitle,
		  const bool logX=true, const double yMin = 0.4, const double yMax = 1.6, const double yLine = 1.0)
{

  setPadStyle();
  gPad->SetLogx(logX);

  TH1D* histFit = fitGauss2D(hist);

  histFit->SetMarkerColor(markerColor[i]);
  histFit->SetMarkerStyle(markerStyle[i]);
  histFit->SetMinimum(yMin);
  histFit->SetMaximum(yMax);
  histFit->SetTitle(hTitle);
  histFit->SetXTitle(xTitle);
  histFit->SetYTitle(yTitle);
  histFit->SetStats(kFALSE);
  setAxisStyle(histFit);

  TString drawOption = "p";
  if(i > 0) drawOption += " same";
  
  histFit->DrawCopy(drawOption);
  drawHLine(histFit, yLine);
  if(logX && !xTitle.Contains("jj")) {
    hatch_bin(histFit, 1);
    hatch_bin(histFit, 2);
  }
  histFit->DrawCopy(drawOption);

}

TString title(const TString algo, const TString flavor = "", const TString eta = "")
{
  TString title = "";
  if(flavor != "") title += "flavor: " + flavor + ", ";
  title += "algo: " + algo;
  if(eta != "") title += ", #eta < " + eta;
  return title;
}

/// main function
void analyzeJetEnergyCorrections(TString name = "analyzeJetEnergyCorrections.root",
				 TString hypoClass = "GenMatch")
{

  name.Resize(name.Index(".root"));

  TString algo = "AK5";
  if(name.Contains("IC5", TString::kIgnoreCase)) algo = "IC5";
  if(name.Contains("KT4", TString::kIgnoreCase)) algo = "KT4";
  if(name.Contains("SC5", TString::kIgnoreCase)) algo = "SC5";

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
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFontSize(.05);
  gStyle->SetTitleX(.18);
  gStyle->SetTitleY(.97);

  TH1F* massW[8];
  TH1F* massT[8];

  TH2F* massW_Pt1[8];
  TH2F* massW_Pt2[8];
  TH2F* massW_PtW[8];

  TH2F* massW_Eta1[8];
  TH2F* massW_Eta2[8];
  TH2F* massW_EtaW[8];

  TH2F* massT_Pt1[8];
  TH2F* massT_Pt2[8];
  TH2F* massT_PtB[8];
  TH2F* massT_PtT[8];

  TH2F* massT_Eta1[8];
  TH2F* massT_Eta2[8];
  TH2F* massT_EtaB[8];
  TH2F* massT_EtaT[8];

  TH2F* deltaM_PtB [8];
  TH2F* deltaM_EtaB[8];

  TH2F* respLGenJetPtGenJet       [8];
  TH2F* respLGenJetPtGenJet_barrel[8];
  TH2F* respLGenJetEta            [8];
  TH2F* respLPartonPtParton       [8];
  TH2F* respLPartonPtParton_barrel[8];
  TH2F* respLPartonEta            [8];

  TH2F* respBGenJetPtGenJet       [8];
  TH2F* respBGenJetPtGenJet_barrel[8];
  TH2F* respBGenJetEta            [8];
  TH2F* respBPartonPtParton       [8];
  TH2F* respBPartonPtParton_barrel[8];
  TH2F* respBPartonEta            [8];

  for(unsigned int i = 0; i < 8; i++) {
    TString dirBase = "analyzeJetEnergy" + hypoClass + "_";

    massW[i] = (TH1F*) file->Get(dirBase + levels[i] + "/mW"  )->Clone();
    massT[i] = (TH1F*) file->Get(dirBase + levels[i] + "/mTop")->Clone();

    massW_Pt1[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mW_Pt1")->Clone();
    massW_Pt2[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mW_Pt2")->Clone();
    massW_PtW[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mW_PtW")->Clone();

    massW_Eta1[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mW_Eta1")->Clone();
    massW_Eta2[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mW_Eta2")->Clone();
    massW_EtaW[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mW_EtaW")->Clone();

    massT_Pt1[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_Pt1"  )->Clone();
    massT_Pt2[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_Pt2"  )->Clone();
    massT_PtB[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_PtB"  )->Clone();
    massT_PtT[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_PtTop")->Clone();

    massT_Eta1[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_Eta1"  )->Clone();
    massT_Eta2[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_Eta2"  )->Clone();
    massT_EtaB[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_EtaB"  )->Clone();
    massT_EtaT[i] = (TH2F*) file->Get(dirBase + levels[i] + "/mTop_EtaTop")->Clone();

    deltaM_PtB [i] = (TH2F*) file->Get(dirBase + levels[i] + "/deltaM_PtB" )->Clone();
    deltaM_EtaB[i] = (TH2F*) file->Get(dirBase + levels[i] + "/deltaM_EtaB")->Clone();

    respLGenJetPtGenJet       [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseLGenJetPtGenJet"       )->Clone();
    respLGenJetPtGenJet_barrel[i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseLGenJetPtGenJet_barrel")->Clone();
    respLGenJetEta            [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseLGenJetEta"            )->Clone();
    respLPartonPtParton       [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseLPartonPtParton"       )->Clone();
    respLPartonPtParton_barrel[i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseLPartonPtParton_barrel")->Clone();
    respLPartonEta            [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseLPartonEta"            )->Clone();

    respBGenJetPtGenJet       [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseBGenJetPtGenJet"       )->Clone();
    respBGenJetPtGenJet_barrel[i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseBGenJetPtGenJet_barrel")->Clone();
    respBGenJetEta            [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseBGenJetEta"            )->Clone();
    respBPartonPtParton       [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseBPartonPtParton"       )->Clone();
    respBPartonPtParton_barrel[i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseBPartonPtParton_barrel")->Clone();
    respBPartonEta            [i]  = (TH2F*) file->Get(dirBase + levels[i] + "/responseBPartonEta"            )->Clone();
  }

  file->Close();
  
  TString outDir = name;
  gSystem->mkdir(outDir);

  TString baseName = outDir + "/" + hypoClass + "_";

  for(unsigned int i = 0; i < 8; i++) {
    double scaleFactor = 1.;
    //    double scaleFactor = 0.039; //50 pb^-1 at 10 TeV
    //    double scaleFactor = 0.014; //50 pb^-1 at 7 TeV
    massW                     [i]->Scale(scaleFactor);
    massT                     [i]->Scale(scaleFactor);
    massW_Pt1                 [i]->Scale(scaleFactor);
    massW_Pt2                 [i]->Scale(scaleFactor);
    massW_PtW                 [i]->Scale(scaleFactor);
    massW_Eta1                [i]->Scale(scaleFactor);
    massW_Eta2                [i]->Scale(scaleFactor);
    massW_EtaW                [i]->Scale(scaleFactor);
    massT_Pt1                 [i]->Scale(scaleFactor);
    massT_Pt2                 [i]->Scale(scaleFactor);
    massT_PtB                 [i]->Scale(scaleFactor);
    massT_PtT                 [i]->Scale(scaleFactor);
    massT_Eta1                [i]->Scale(scaleFactor);
    massT_Eta2                [i]->Scale(scaleFactor);
    massT_EtaB                [i]->Scale(scaleFactor);
    massT_EtaT                [i]->Scale(scaleFactor);
    deltaM_PtB                [i]->Scale(scaleFactor);
    deltaM_EtaB               [i]->Scale(scaleFactor);
    respLGenJetPtGenJet       [i]->Scale(scaleFactor);
    respLGenJetPtGenJet_barrel[i]->Scale(scaleFactor);
    respLGenJetEta            [i]->Scale(scaleFactor);
    respLPartonPtParton       [i]->Scale(scaleFactor);
    respLPartonPtParton_barrel[i]->Scale(scaleFactor);
    respLPartonEta            [i]->Scale(scaleFactor);
    respBGenJetPtGenJet       [i]->Scale(scaleFactor);
    respBGenJetPtGenJet_barrel[i]->Scale(scaleFactor);
    respBGenJetEta            [i]->Scale(scaleFactor);
    respBPartonPtParton       [i]->Scale(scaleFactor);
    respBPartonPtParton_barrel[i]->Scale(scaleFactor);
    respBPartonEta            [i]->Scale(scaleFactor);
    massW                     [i]->Sumw2();
    massT                     [i]->Sumw2();
    massW_Pt1                 [i]->Sumw2();
    massW_Pt2                 [i]->Sumw2();
    massW_PtW                 [i]->Sumw2();
    massW_Eta1                [i]->Sumw2();
    massW_Eta2                [i]->Sumw2();
    massW_EtaW                [i]->Sumw2();
    massT_Pt1                 [i]->Sumw2();
    massT_Pt2                 [i]->Sumw2();
    massT_PtB                 [i]->Sumw2();
    massT_PtT                 [i]->Sumw2();
    massT_Eta1                [i]->Sumw2();
    massT_Eta2                [i]->Sumw2();
    massT_EtaB                [i]->Sumw2();
    massT_EtaT                [i]->Sumw2();
    deltaM_PtB                [i]->Sumw2();
    deltaM_EtaB               [i]->Sumw2();
    respLGenJetPtGenJet       [i]->Sumw2();
    respLGenJetPtGenJet_barrel[i]->Sumw2();
    respLGenJetEta            [i]->Sumw2();
    respLPartonPtParton       [i]->Sumw2();
    respLPartonPtParton_barrel[i]->Sumw2();
    respLPartonEta            [i]->Sumw2();
    respBGenJetPtGenJet       [i]->Sumw2();
    respBGenJetPtGenJet_barrel[i]->Sumw2();
    respBGenJetEta            [i]->Sumw2();
    respBPartonPtParton       [i]->Sumw2();
    respBPartonPtParton_barrel[i]->Sumw2();
    respBPartonEta            [i]->Sumw2();
  }

  for(unsigned int i = 0; i < 8; i++) {
    massW_Pt1 [i]->Add(massW_Pt2 [i]);
    massW_Eta1[i]->Add(massW_Eta2[i]);
    massT_Pt1 [i]->Add(massT_Pt2 [i]);
    massT_Eta1[i]->Add(massT_Eta2[i]);
  }

  // create canvases

  TCanvas* canvasMassW      = new TCanvas("canvasMassW"     , "W mass"                        , 900, 900);
  TCanvas* canvasMassT      = new TCanvas("canvasMassT"     , "top mass"                      , 900, 900);
  TCanvas* canvasMassW_2dim = new TCanvas("canvasMassW_2dim", "W mass (2 dim.)"               , 900, 900);
  TCanvas* canvasMassT_2dim = new TCanvas("canvasMassT_2dim", "top mass (2 dim.)"             , 900, 900);
  TCanvas* canvasRespL      = new TCanvas("canvasRespL"     , "response for light jets"       , 900, 900);
  TCanvas* canvasRespB      = new TCanvas("canvasRespB"     , "response for b jets"           , 900, 900);
  TCanvas* canvasRespL_zoom = new TCanvas("canvasRespL_zoom", "response for light jets (zoom)", 900, 900);
  TCanvas* canvasRespB_zoom = new TCanvas("canvasRespB_zoom", "response for b jets (zoom)"    , 900, 900);
  canvasMassW     ->Divide(3,3);
  canvasMassT     ->Divide(3,3);
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

  }  

  TPaveText *txtMassW = new TPaveText(0.22, 0.68, 0.9, 0.88, "NDC");
  TPaveText *txtMassT = new TPaveText(0.17, 0.68, 0.9, 0.88, "NDC");
  char *tmpTxt = new char[100];

  txtMassW->SetTextAlign(32);
  txtMassT->SetTextAlign(32);
  txtMassW->SetFillStyle(0);
  txtMassT->SetFillStyle(0);
  txtMassW->SetBorderSize(0);
  txtMassT->SetBorderSize(0);

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

    massW[i]->SetLineColor(markerColor[i]);
    massT[i]->SetLineColor(markerColor[i]);

    TText* ttxt = 0;
    
    double mean     = massW[i]->GetFunction("gaus")->GetParameter(1);
    double mean_err = massW[i]->GetFunction("gaus")->GetParError (1);
    double relSigma = massW[i]->GetFunction("gaus")->GetParameter(2) / mean;

    sprintf(tmpTxt, ": #mu = %4.1f#pm%4.1f GeV; #sigma/#mu = %4.2f", mean, mean_err, relSigma);
    ttxt = txtMassW->AddText(levels[i] + tmpTxt);
    ttxt->SetTextColor(markerColor[i]);
    
    mean     = massT[i]->GetFunction("gaus")->GetParameter(1);
    mean_err = massT[i]->GetFunction("gaus")->GetParError (1);
    relSigma = massT[i]->GetFunction("gaus")->GetParameter(2) / mean;

    sprintf(tmpTxt, ": #mu = %4.1f#pm%4.1f GeV; #sigma/#mu = %4.2f", mean, mean_err, relSigma);
    ttxt = txtMassT->AddText(levels[i] + tmpTxt);
    ttxt->SetTextColor(markerColor[i]);

  }

  massW[0]->SetMaximum( 1.5*massW[0]->GetMaximum() );
  massT[0]->SetMaximum( 1.5*massT[0]->GetMaximum() );
  massW[0]->SetTitle("algo: " + algo);
  massT[0]->SetTitle("algo: " + algo);
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
      massW[i]->GetFunction("gaus")->SetLineColor(markerColor[i]);
      massW[i]->GetFunction("gaus")->DrawCopy("same");
    }
    txtMassW->Draw();
    if(i==7) {
      massW[0]->DrawCopy("sameaxis");
      gPad->Print(baseName+"massW.eps");
    }

    canvasMassT->cd(9);
    setPadStyle();
    massT[i]->DrawCopy(drawOption);
    if(massT[i]->GetListOfFunctions()->FindObject("gaus")) {
      massT[i]->GetFunction("gaus")->SetLineWidth(1);
      massT[i]->GetFunction("gaus")->SetLineColor(markerColor[i]);
      massT[i]->GetFunction("gaus")->DrawCopy("same");
    }
    txtMassT->Draw();
    if(i==7) {
      massT[0]->DrawCopy("sameaxis");
      gPad->Print(baseName+"massT.eps");
    }

  }

  for(unsigned int i = 0; i < 8; i++) {

    if(i==1 || i==2 || i==4 || i==6)
      continue;

    // W mass
    
    canvasMassW_2dim->cd(1);
    drawResponse(massW_Pt1[i], i, "p_{T,j} (rec) [GeV]", "m_{jj} [GeV]", title(algo), true, 30., 130., 80.4);

    canvasMassW_2dim->cd(2);
    drawResponse(massW_Eta1[i], i, "#eta_{j} (rec)", "m_{jj} [GeV]", title(algo), false, 30., 130., 80.4);

    canvasMassW_2dim->cd(3);
    drawResponse(massW_PtW[i], i, "p_{T,jj} (rec) [GeV]", "m_{jj} [GeV]", title(algo), true, 30., 130., 80.4);

    canvasMassW_2dim->cd(6);
    drawResponse(massW_EtaW[i], i, "#eta_{jj} (rec)", "m_{jj} [GeV]", title(algo), false, 30., 130., 80.4);

    // top mass

    canvasMassT_2dim->cd(1);
    drawResponse(massT_Pt1[i], i, "p_{T,j} (rec) [GeV]", "m_{jjb} [GeV]", title(algo), true, 60., 290., 172.5);

    canvasMassT_2dim->cd(2);
    drawResponse(massT_Eta1[i], i, "#eta_{j} (rec)", "m_{jjb} [GeV]", title(algo), false, 60., 290., 172.5);

    canvasMassT_2dim->cd(3);
    drawResponse(massT_PtT[i], i, "p_{T,jjb} (rec) [GeV]", "m_{jjb} [GeV]", title(algo), true, 60., 290., 172.5);

    canvasMassT_2dim->cd(4);
    drawResponse(massT_PtB[i], i, "p_{T,b} (rec) [GeV]", "m_{jjb} [GeV]", title(algo), true, 60., 290., 172.5);

    canvasMassT_2dim->cd(5);
    drawResponse(massT_EtaB[i], i, "#eta_{b} (rec)", "m_{jjb} [GeV]", title(algo), false, 60., 290., 172.5);

    canvasMassT_2dim->cd(6);
    drawResponse(massT_EtaT[i], i, "#eta_{jjb} (rec)", "m_{jjb} [GeV]", title(algo), false, 60., 290., 172.5);

    canvasMassT_2dim->cd(7);
    drawResponse(deltaM_PtB[i], i, "p_{T,b} (rec) [GeV]", "m_{jjb}-m_{jj} [GeV]", title(algo), true, 30., 150., 92.1);

    canvasMassT_2dim->cd(8);
    drawResponse(deltaM_EtaB[i], i, "#eta_{b} (rec)", "m_{jjb}-m_{jj} [GeV]", title(algo), false, 30., 150., 92.1);

  }

  double yMin_zoom = 0.8;
  double yMax_zoom = 1.2;

  for(unsigned int i = 0; i < 8; i++) {

    if(i==1 || i==2 || i==4 || i==6)
      continue;

    // response light jets

    canvasRespL->cd(1);
    drawResponse(respLGenJetPtGenJet[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)", title(algo,"udsc"));

    canvasRespL->cd(2);
    drawResponse(respLGenJetPtGenJet_barrel[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)", title(algo,"udsc","1.3"));

    canvasRespL->cd(3);
    drawResponse(respLGenJetEta[i], i, "#eta (gen)", "p_{T} (rec) / p_{T} (gen)", title(algo,"udsc"), false);

    canvasRespL->cd(4);
    drawResponse(respLPartonPtParton[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)", title(algo,"udsc"));

    canvasRespL->cd(5);
    drawResponse(respLPartonPtParton_barrel[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)", title(algo,"udsc","1.3"));

    canvasRespL->cd(6);
    drawResponse(respLPartonEta[i], i, "#eta (parton)", "p_{T} (rec) / p_{T} (parton)", title(algo,"udsc"), false);

    // response light jets (zoom)

    canvasRespL_zoom->cd(1);
    drawResponse(respLGenJetPtGenJet[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)", title(algo,"udsc"),
		 true, yMin_zoom, yMax_zoom);

    canvasRespL_zoom->cd(2);
    drawResponse(respLGenJetPtGenJet_barrel[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)", title(algo,"udsc","1.3"),
		 true, yMin_zoom, yMax_zoom);

    canvasRespL_zoom->cd(3);
    drawResponse(respLGenJetEta[i], i, "#eta (gen)", "p_{T} (rec) / p_{T} (gen)", title(algo,"udsc"),
		 false, yMin_zoom, yMax_zoom);

    canvasRespL_zoom->cd(4);
    drawResponse(respLPartonPtParton[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)", title(algo,"udsc"),
		 true, yMin_zoom, yMax_zoom);

    canvasRespL_zoom->cd(5);
    drawResponse(respLPartonPtParton_barrel[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)", title(algo,"udsc","1.3"),
		 true, yMin_zoom, yMax_zoom);

    canvasRespL_zoom->cd(6);
    drawResponse(respLPartonEta[i], i, "#eta (parton)", "p_{T} (rec) / p_{T} (parton)", title(algo,"udsc"),
		 false, yMin_zoom, yMax_zoom);

    // response b jets

    canvasRespB->cd(1);
    drawResponse(respBGenJetPtGenJet[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)", title(algo,"b"));

    canvasRespB->cd(2);
    drawResponse(respBGenJetPtGenJet_barrel[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)", title(algo,"b","1.3"));

    canvasRespB->cd(3);
    drawResponse(respBGenJetEta[i], i, "#eta (gen)", "p_{T} (rec) / p_{T} (gen)", title(algo,"b"), false);

    canvasRespB->cd(4);
    drawResponse(respBPartonPtParton[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)", title(algo,"b"));

    canvasRespB->cd(5);
    drawResponse(respBPartonPtParton_barrel[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)", title(algo,"b","1.3"));

    canvasRespB->cd(6);
    drawResponse(respBPartonEta[i], i, "#eta (parton)", "p_{T} (rec) / p_{T} (parton)", title(algo,"b"), false);

    // response b jets (zoom)

    canvasRespB_zoom->cd(1);
    drawResponse(respBGenJetPtGenJet[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)", title(algo,"b"),
		 true, yMin_zoom, yMax_zoom);

    canvasRespB_zoom->cd(2);
    drawResponse(respBGenJetPtGenJet_barrel[i], i, "p_{T} (gen) [GeV]", "p_{T} (rec) / p_{T} (gen)", title(algo,"b","1.3"),
		 true, yMin_zoom, yMax_zoom);

    canvasRespB_zoom->cd(3);
    drawResponse(respBGenJetEta[i], i, "#eta (gen)", "p_{T} (rec) / p_{T} (gen)", title(algo,"b"),
		 false, yMin_zoom, yMax_zoom);

    canvasRespB_zoom->cd(4);
    drawResponse(respBPartonPtParton[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)", title(algo,"b"),
		 true, yMin_zoom, yMax_zoom);

    canvasRespB_zoom->cd(5);
    drawResponse(respBPartonPtParton_barrel[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)", title(algo,"b","1.3"),
		 true, yMin_zoom, yMax_zoom);

    canvasRespB_zoom->cd(6);
    drawResponse(respBPartonEta[i], i, "#eta (parton)", "p_{T} (rec) / p_{T} (parton)", title(algo,"b"),
		 false, yMin_zoom, yMax_zoom);

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

  for(unsigned int i = 1; i < 9; i++) {

    TString suffix = "_";
    suffix += i;
    suffix += ".eps";

    if(i<4 || i==6) {
      canvasMassW_2dim->cd(i);
      legend->Draw();
      gPad->Print(baseName+"massW_2dim" + suffix);
    }

    canvasMassT_2dim->cd(i);
    legend->Draw();
    gPad->Print(baseName+"massT_2dim" + suffix);

  }

  for(unsigned int i = 1; i < 7; i++) {

    TString suffix = "_";
    suffix += i;
    suffix += ".eps";

    canvasRespL->cd(i);
    legend->Draw();
    gPad->Print(baseName+"responseLight" + suffix);

    canvasRespL_zoom->cd(i);
    legend->Draw();
    gPad->Print(baseName+"responseLight_zoom" + suffix);

    canvasRespB->cd(i);
    legend->Draw();
    gPad->Print(baseName+"responseB" + suffix);

    canvasRespB_zoom->cd(i);
    legend->Draw();
    gPad->Print(baseName+"responseB_zoom" + suffix);

  }

  // print one ps-file

  TString psName = outDir + "/" + name + "_" + hypoClass + ".ps";

  canvasMassW     ->Print(psName + "(");
  canvasMassW_2dim->Print(psName);
  canvasMassT     ->Print(psName);
  canvasMassT_2dim->Print(psName);
  canvasRespL     ->Print(psName);
  canvasRespL_zoom->Print(psName);
  canvasRespB     ->Print(psName);
  canvasRespB_zoom->Print(psName + ")");

  // clean-up

  delete canvasMassW;
  delete canvasMassW_2dim;
  delete canvasMassT;
  delete canvasMassT_2dim;
  delete canvasRespL;
  delete canvasRespL_zoom;
  delete canvasRespB;
  delete canvasRespB_zoom;

}
