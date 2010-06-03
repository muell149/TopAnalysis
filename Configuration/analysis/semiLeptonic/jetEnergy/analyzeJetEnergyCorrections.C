#include <TCanvas.h>
#include <TFile.h>
#include <TF1.h>
#include <TGaxis.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLegend.h>
#include <TPad.h>
#include <TPaveText.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TSystem.h>

#include <stdlib.h>
#include <fstream>
#include <iomanip>

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

void cleverRebinning(TH1* hist)
{

  //  if(hist->GetEntries() / hist->GetNbinsX() < 10.) {
  if(hist->GetEntries() / hist->GetNbinsX() < 4.) {
    hist->Rebin(); // reduces number of bins by a factor of two, merging adjacent bins
    cleverRebinning(hist); // recursion
  }

}

void fitGauss(TH1* hist)
{

  cleverRebinning(hist);
  TString fitOptions = "M0E";
  // first iteration
  hist->Fit("gaus", fitOptions);
  // second iteration
  double mean  = hist->GetFunction("gaus")->GetParameter(1);
  double sigma = hist->GetFunction("gaus")->GetParameter(2);
  if(hist->GetEntries() / hist->GetNbinsX() > 10.)
    hist->Fit("gaus", fitOptions, "", mean-1.5*sigma, mean+1.5*sigma);
  else
    hist->Fit("gaus", fitOptions);

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
    // remove x-bins that have less than 20 entries along y
    // (this assumes weight=1 for all entries)
    if(bincontent<20) {
      means->SetBinContent(bx, 0.);
      means->SetBinError  (bx, 0.);
    }
    // perform a second gauss fit for all other bins
    // restricting the fitting range according to
    // mean and sigma from the first gauss fit
    else {
      double mean  = means ->GetBinContent(bx);
      double sigma = sigmas->GetBinContent(bx);
      if( mean-1.5*sigma >= hist->GetYaxis()->GetXmin() &&
	  mean+1.5*sigma <  hist->GetYaxis()->GetXmax() ) {
	TF1* f = new TF1("f","gaus", mean-1.5*sigma, mean+1.5*sigma);
	hist->FitSlicesY(f,bx,bx,0,"QNR",&tmp);
	mean  = ((TH1D*) tmp.FindObject(histName+"_1"))->GetBinContent(bx);
	sigma = ((TH1D*) tmp.FindObject(histName+"_1"))->GetBinError  (bx);
	means->SetBinContent(bx, mean );
	means->SetBinError  (bx, sigma);
	tmp.Delete();
	delete f;
      }
      else {
	means->SetBinContent(bx, 0.);
	means->SetBinError  (bx, 0.);
      }
    }
  }

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

unsigned int getNumberOfHistosOnPad()
{
  TIter iter(gPad->GetListOfPrimitives());
  TObject *obj;
  unsigned int n = 0;
  while( (obj = (TObject*)iter.Next()) ) {
    if(obj->InheritsFrom("TH1"))
      n++;
  }
  return n;
}


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
  if(logX && !xTitle.Contains("jj")) {
    histFit->GetXaxis()->SetNoExponent();
    histFit->GetXaxis()->SetMoreLogLabels();
    histFit->GetXaxis()->SetRange(3., histFit->GetNbinsX());
  }

  TString drawOption = "p";
  if(getNumberOfHistosOnPad() > 0) drawOption += " same";
  
  histFit->DrawCopy(drawOption);
  drawHLine(histFit, yLine);
  histFit->DrawCopy(drawOption);

}

TString title(const TString algo, const TString flavor = "", const TString cut = "")
{
  TString title = algo;
  if(flavor != "") title += ", flavor: " + flavor;
  if(cut    != "") title += ", " + cut;
  return title;
}

/// main function
int analyzeJetEnergyCorrections(TString name = "analyzeJetEnergyCorrections.root",
				TString hypoClass = "GenMatch")
{

  name.Resize(name.Index(".root"));

  TString algo = "AK5";
  if(name.Contains("IC5", TString::kIgnoreCase)) algo = "IC5";
  if(name.Contains("KT4", TString::kIgnoreCase)) algo = "KT4";
  if(name.Contains("SC5", TString::kIgnoreCase)) algo = "SC5";

  TString dirs[8] = {"raw" ,
		     "off" ,  //L1
		     "rel" ,  //L2
		     "abs" ,  //L3
		     "emf" ,  //L4
		     "had" ,  //L5
		     "ue"  ,  //L6
		     "part"}; //L7

  // just to have the freedom of choosing the lables different from the directory names
  TString levels[8] = {"raw" ,
		       "off" ,  //L1
		       "rel" ,  //L2
		       "abs" ,  //L3
		       "emf" ,  //L4
		       "had",   //L5
		       "ue"  ,  //L6
		       "part"}; //L7

  TFile* file = TFile::Open(name + ".root");
  
  if(!file)
    abort();

  gROOT->cd();
  gROOT->SetStyle("Plain");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFontSize(.05);
  gStyle->SetTitleX(.4);
  gStyle->SetTitleY(.98);

  TH1F* massW[8];
  TH1F* massT[8];
  TH1D* deltaM[8];

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

    massW[i] = (TH1F*) file->Get(dirBase + dirs[i] + "/mW"  )->Clone();
    massT[i] = (TH1F*) file->Get(dirBase + dirs[i] + "/mTop")->Clone();

    massW_Pt1[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mW_Pt1")->Clone();
    massW_Pt2[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mW_Pt2")->Clone();
    massW_PtW[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mW_PtW")->Clone();

    massW_Eta1[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mW_Eta1")->Clone();
    massW_Eta2[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mW_Eta2")->Clone();
    massW_EtaW[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mW_EtaW")->Clone();

    massT_Pt1[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mTop_Pt1"  )->Clone();
    massT_Pt2[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mTop_Pt2"  )->Clone();
    massT_PtB[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mTop_PtB"  )->Clone();
    massT_PtT[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mTop_PtTop")->Clone();

    massT_Eta1[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mTop_Eta1"  )->Clone();
    massT_Eta2[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mTop_Eta2"  )->Clone();
    massT_EtaB[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mTop_EtaB"  )->Clone();
    massT_EtaT[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/mTop_EtaTop")->Clone();

    deltaM_PtB [i] = (TH2F*) file->Get(dirBase + dirs[i] + "/deltaM_PtB" )->Clone();
    deltaM_EtaB[i] = (TH2F*) file->Get(dirBase + dirs[i] + "/deltaM_EtaB")->Clone();

    respLGenJetPtGenJet       [i]  = (TH2F*) file->Get(dirBase + dirs[i] + "/responseLGenJetPtGenJet"       )->Clone();
    respLGenJetPtGenJet_barrel[i]  = (TH2F*) file->Get(dirBase + dirs[i] + "/responseLGenJetPtGenJet_barrel")->Clone();
    respLGenJetEta            [i]  = (TH2F*) file->Get(dirBase + dirs[i] + "/responseLGenJetEta"            )->Clone();
    respLPartonPtParton       [i]  = (TH2F*) file->Get(dirBase + dirs[i] + "/responseLPartonPtParton"       )->Clone();
    respLPartonPtParton_barrel[i]  = (TH2F*) file->Get(dirBase + dirs[i] + "/responseLPartonPtParton_barrel")->Clone();
    respLPartonEta            [i]  = (TH2F*) file->Get(dirBase + dirs[i] + "/responseLPartonEta"            )->Clone();

    respBGenJetPtGenJet       [i]  = (TH2F*) file->Get(dirBase + dirs[i] + "/responseBGenJetPtGenJet"       )->Clone();
    respBGenJetPtGenJet_barrel[i]  = (TH2F*) file->Get(dirBase + dirs[i] + "/responseBGenJetPtGenJet_barrel")->Clone();
    respBGenJetEta            [i]  = (TH2F*) file->Get(dirBase + dirs[i] + "/responseBGenJetEta"            )->Clone();
    respBPartonPtParton       [i]  = (TH2F*) file->Get(dirBase + dirs[i] + "/responseBPartonPtParton"       )->Clone();
    respBPartonPtParton_barrel[i]  = (TH2F*) file->Get(dirBase + dirs[i] + "/responseBPartonPtParton_barrel")->Clone();
    respBPartonEta            [i]  = (TH2F*) file->Get(dirBase + dirs[i] + "/responseBPartonEta"            )->Clone();
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

  for(unsigned int i = 0; i < 8; i++) {
    TString name = "_"; name += i;
    deltaM[i] = deltaM_EtaB[i]->ProjectionY(name);
  }

  // create canvases

  TCanvas* canvasMassW      = new TCanvas("canvasMassW"     , "W mass"                        , 900, 900);
  TCanvas* canvasMassT      = new TCanvas("canvasMassT"     , "top mass"                      , 900, 900);
  TCanvas* canvasMassW_2dim = new TCanvas("canvasMassW_2dim", "W mass (2 dim.)"               , 900, 900);
  TCanvas* canvasMassT_2dim = new TCanvas("canvasMassT_2dim", "top mass (2 dim.)"             , 900, 900);
  TCanvas* canvasRespL      = new TCanvas("canvasRespL"     , "response for light jets"       , 900, 900);
  TCanvas* canvasRespB      = new TCanvas("canvasRespB"     , "response for b jets"           , 900, 900);
  canvasMassW     ->Divide(3,3);
  canvasMassT     ->Divide(3,3);
  canvasMassW_2dim->Divide(3,3);
  canvasMassT_2dim->Divide(3,3);
  canvasRespL     ->Divide(3,3);
  canvasRespB     ->Divide(3,3);

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

  TPaveText* txtMassW = new TPaveText(0.22, 0.68, 0.89, 0.88, "NDC");
  char *tmpTxt = new char[100];

  txtMassW->SetTextAlign(32);
  txtMassW->SetFillColor(0);
  txtMassW->SetBorderSize(0);

  TPaveText* txtMassT  = (TPaveText*) txtMassW->Clone();
  TPaveText* txtDeltaM = (TPaveText*) txtMassW->Clone();

  ofstream outfile(baseName + "results.txt");

  outfile << "-----------------------------------------" << std::endl
	  << "level           mW-80.4          mT-172.5" << std::endl
	  << "-----------------------------------------" << std::endl;
  outfile << setiosflags(std::ios::fixed | std::ios::showpos);

  for(unsigned int i = 0; i < 8; i++) {

    if(i==1 || i==2 || i==4 || i==6)
      continue;

    if(massW[i]->GetEntries()==0 ||
       massT[i]->GetEntries()==0)
      continue;

    fitGauss(massW [i]);
    fitGauss(massT [i]);
    fitGauss(deltaM[i]);

    massW [i]->SetLineColor(markerColor[i]);
    massT [i]->SetLineColor(markerColor[i]);
    deltaM[i]->SetLineColor(markerColor[i]);

    TText* ttxt = 0;
    
    double mean     = massW[i]->GetFunction("gaus")->GetParameter(1);
    double mean_err = massW[i]->GetFunction("gaus")->GetParError (1);
    double relSigma = massW[i]->GetFunction("gaus")->GetParameter(2) / mean;

    outfile << std::setw(5) << levels[i]
	    << std::setw(7) << std::setprecision(1) << mean-80.4 << " GeV"
	    << " (" << std::setw(3) << std::setprecision(0) << (mean/80.4-1)*100 << "%)";

    sprintf(tmpTxt, ": #mu = %4.1f#pm%4.1f GeV; #sigma/#mu = %4.2f", mean, mean_err, relSigma);
    ttxt = txtMassW->AddText(levels[i] + tmpTxt);
    ttxt->SetTextColor(markerColor[i]);
  
    mean     = massT[i]->GetFunction("gaus")->GetParameter(1);
    mean_err = massT[i]->GetFunction("gaus")->GetParError (1);
    relSigma = massT[i]->GetFunction("gaus")->GetParameter(2) / mean;

    outfile << std::setw(7) << std::setprecision(1) << mean-172.5-1 << " GeV"
	    << " (" <<std::setw(3) << std::setprecision(0) << (mean/172.5-1)*100 << "%)" << std::endl;

    sprintf(tmpTxt, ": #mu = %4.1f#pm%4.1f GeV; #sigma/#mu = %4.2f", mean, mean_err, relSigma);
    ttxt = txtMassT->AddText(levels[i] + tmpTxt);
    ttxt->SetTextColor(markerColor[i]);

    mean     = deltaM[i]->GetFunction("gaus")->GetParameter(1);
    mean_err = deltaM[i]->GetFunction("gaus")->GetParError (1);
    relSigma = deltaM[i]->GetFunction("gaus")->GetParameter(2) / mean;

    sprintf(tmpTxt, ": #mu = %4.1f#pm%4.1f GeV; #sigma/#mu = %4.2f", mean, mean_err, relSigma);
    ttxt = txtDeltaM->AddText(levels[i] + tmpTxt);
    ttxt->SetTextColor(markerColor[i]);

  }

  outfile.close();

  massW [0]->SetMaximum( 1.5*massW [0]->GetMaximum() );
  massT [0]->SetMaximum( 1.5*massT [0]->GetMaximum() );
  deltaM[0]->SetMaximum( 1.5*deltaM[0]->GetMaximum() );
  massW [0]->SetTitle("       " + algo);
  massT [0]->SetTitle("       " + algo);
  deltaM[0]->SetTitle("       " + algo);
  deltaM[0]->SetXTitle("m_{jjb}-m_{jj} [GeV]");
  deltaM[0]->SetYTitle("events");
  massW [0]->SetStats(kFALSE);
  massT [0]->SetStats(kFALSE);
  deltaM[0]->SetStats(kFALSE);
  setAxisStyle(massW [0]);
  setAxisStyle(massT [0]);
  setAxisStyle(deltaM[0]);

  for(unsigned int i = 0; i < 8; i++) {

    if(i==1 || i==2 || i==4 | i==6)
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

    canvasMassT->cd(9);
    setPadStyle();
    massT[i]->DrawCopy(drawOption);
    if(massT[i]->GetListOfFunctions()->FindObject("gaus")) {
      massT[i]->GetFunction("gaus")->SetLineWidth(1);
      massT[i]->GetFunction("gaus")->SetLineColor(markerColor[i]);
      massT[i]->GetFunction("gaus")->DrawCopy("same");
    }
    txtMassT->Draw();

    canvasMassT_2dim->cd(9);
    setPadStyle();
    deltaM[i]->DrawCopy(drawOption);
    if(deltaM[i]->GetListOfFunctions()->FindObject("gaus")) {
      deltaM[i]->GetFunction("gaus")->SetLineWidth(1);
      deltaM[i]->GetFunction("gaus")->SetLineColor(markerColor[i]);
      deltaM[i]->GetFunction("gaus")->DrawCopy("same");
    }
    txtDeltaM->Draw();

  }

  canvasMassW->cd(9);
  gPad->Print(baseName+"massW.eps");

  canvasMassT->cd(9);
  gPad->Print(baseName+"massT.eps");

  canvasMassT_2dim->cd(9);
  gPad->Print(baseName+"deltaM.eps");

  gStyle->SetTitleX(.2);

  for(unsigned int i = 0; i < 8; i++) {

    if(!(i==0 || i==3 || i==7))
      continue;

    TString space = "                       ";

    // W mass
    
    canvasMassW_2dim->cd(1);
    drawResponse(massW_Pt1[i], i, "p_{T,j} (rec) [GeV]", "m_{jj} [GeV]", space+algo, true, 35., 125., 80.4);

    canvasMassW_2dim->cd(2);
    drawResponse(massW_Eta1[i], i, "#eta_{j} (rec)", "m_{jj} [GeV]", space+algo, false, 35., 125., 80.4);

    canvasMassW_2dim->cd(3);
    drawResponse(massW_PtW[i], i, "p_{T,jj} (rec) [GeV]", "m_{jj} [GeV]", space+algo, true, 35., 125., 80.4);

    canvasMassW_2dim->cd(6);
    drawResponse(massW_EtaW[i], i, "#eta_{jj} (rec)", "m_{jj} [GeV]", space+algo, false, 35., 125., 80.4);

    // top mass

    canvasMassT_2dim->cd(1);
    drawResponse(massT_Pt1[i], i, "p_{T,j} (rec) [GeV]", "m_{jjb} [GeV]", space+algo, true, 80., 260., 172.5);

    canvasMassT_2dim->cd(2);
    drawResponse(massT_Eta1[i], i, "#eta_{j} (rec)", "m_{jjb} [GeV]", space+algo, false, 80., 260., 172.5);

    canvasMassT_2dim->cd(3);
    drawResponse(massT_PtT[i], i, "p_{T,jjb} (rec) [GeV]", "m_{jjb} [GeV]", space+algo, true, 80., 260., 172.5);

    canvasMassT_2dim->cd(4);
    drawResponse(massT_PtB[i], i, "p_{T,b} (rec) [GeV]", "m_{jjb} [GeV]", space+algo, true, 80., 260., 172.5);

    canvasMassT_2dim->cd(5);
    drawResponse(massT_EtaB[i], i, "#eta_{b} (rec)", "m_{jjb} [GeV]", space+algo, false, 80., 260., 172.5);

    canvasMassT_2dim->cd(6);
    drawResponse(massT_EtaT[i], i, "#eta_{jjb} (rec)", "m_{jjb} [GeV]", space+algo, false, 80., 260., 172.5);

    canvasMassT_2dim->cd(7);
    drawResponse(deltaM_PtB[i], i, "p_{T,b} (rec) [GeV]", "m_{jjb}-m_{jj} [GeV]", space+algo, true, 30., 150., 92.1);

    canvasMassT_2dim->cd(8);
    drawResponse(deltaM_EtaB[i], i, "#eta_{b} (rec)", "m_{jjb}-m_{jj} [GeV]", space+algo, false, 30., 150., 92.1);

  }

  double yMin_zoom = 0.9;
  double yMax_zoom = 1.2;

  for(unsigned int i = 0; i < 8; i++) {

    if(i==1 || i==2 || i==4 || i==6)
      continue;

    // response light jets

    if(i!=7) {

      canvasRespL->cd(1);
      drawResponse(respLGenJetPtGenJet[i], i, "p_{T} (had) [GeV]", "p_{T} (rec) / p_{T} (had)", title(algo,"udsc"));
    
      canvasRespL->cd(2);
      drawResponse(respLGenJetPtGenJet_barrel[i], i,
		   "p_{T} (had) [GeV]", "p_{T} (rec) / p_{T} (had)", title(algo,"udsc","|#eta| < 1.3"));

      canvasRespL->cd(3);
      drawResponse(respLGenJetEta[i], i, "#eta (had)", "p_{T} (rec) / p_{T} (had)", title(algo,"udsc","p_{T} > 30 GeV"), false);

    }
    
    if(i!=7) {

      canvasRespL->cd(4);
      drawResponse(respLGenJetPtGenJet[i], i, "p_{T} (had) [GeV]", "p_{T} (rec) / p_{T} (had)", title(algo,"udsc"),
		   true, yMin_zoom, yMax_zoom);

      canvasRespL->cd(5);
      drawResponse(respLGenJetPtGenJet_barrel[i], i,
		   "p_{T} (had) [GeV]", "p_{T} (rec) / p_{T} (had)", title(algo,"udsc","|#eta| < 1.3"),
		   true, yMin_zoom, yMax_zoom);

      canvasRespL->cd(6);
      drawResponse(respLGenJetEta[i], i, "#eta (had)", "p_{T} (rec) / p_{T} (had)", title(algo,"udsc","p_{T} > 30 GeV"),
		   false, yMin_zoom, yMax_zoom);

    }

    if(i==5 || i==7) {

      canvasRespL->cd(7);
      drawResponse(respLPartonPtParton[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)", title(algo,"udsc"),
		   true, yMin_zoom, yMax_zoom);

      canvasRespL->cd(8);
      drawResponse(respLPartonPtParton_barrel[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)",
		   title(algo,"udsc","|#eta| < 1.3"), true, yMin_zoom, yMax_zoom);

      canvasRespL->cd(9);
      drawResponse(respLPartonEta[i], i, "#eta (parton)", "p_{T} (rec) / p_{T} (parton)", title(algo,"udsc","p_{T} > 30 GeV"),
		   false, yMin_zoom, yMax_zoom);

    }

    // response b jets

    if(i!=7) {

      canvasRespB->cd(1);
      drawResponse(respBGenJetPtGenJet[i], i, "p_{T} (had) [GeV]", "p_{T} (rec) / p_{T} (had)", title(algo,"b"));
    
      canvasRespB->cd(2);
      drawResponse(respBGenJetPtGenJet_barrel[i], i,
		   "p_{T} (had) [GeV]", "p_{T} (rec) / p_{T} (had)", title(algo,"b","|#eta| < 1.3"));

      canvasRespB->cd(3);
      drawResponse(respBGenJetEta[i], i, "#eta (had)", "p_{T} (rec) / p_{T} (had)", title(algo,"b","p_{T} > 30 GeV"), false);

    }

    if(i!=7) {

      canvasRespB->cd(4);
      drawResponse(respBGenJetPtGenJet[i], i, "p_{T} (had) [GeV]", "p_{T} (rec) / p_{T} (had)", title(algo,"b"),
		   true, yMin_zoom, yMax_zoom);

      canvasRespB->cd(5);
      drawResponse(respBGenJetPtGenJet_barrel[i], i,
		   "p_{T} (had) [GeV]", "p_{T} (rec) / p_{T} (had)", title(algo,"b","|#eta| < 1.3"),
		   true, yMin_zoom, yMax_zoom);

      canvasRespB->cd(6);
      drawResponse(respBGenJetEta[i], i, "#eta (had)", "p_{T} (rec) / p_{T} (had)", title(algo,"b","p_{T} > 30 GeV"),
		   false, yMin_zoom, yMax_zoom);

    }

    if(i==5 || i==7) {
      
      canvasRespB->cd(7);
      drawResponse(respBPartonPtParton[i], i, "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)", title(algo,"b"),
		   true, yMin_zoom, yMax_zoom);

      canvasRespB->cd(8);
      drawResponse(respBPartonPtParton_barrel[i], i,
		   "p_{T} (parton) [GeV]", "p_{T} (rec) / p_{T} (parton)", title(algo,"b","|#eta| < 1.3"),
		   true, yMin_zoom, yMax_zoom);

      canvasRespB->cd(9);
      drawResponse(respBPartonEta[i], i, "#eta (parton)", "p_{T} (rec) / p_{T} (parton)", title(algo,"b","p_{T} > 30 GeV"),
		   false, yMin_zoom, yMax_zoom);

    }

  }

  // legend
  
  TLegend* legend_035 = new TLegend(0.75, 0.66, 0.9, 0.9);
  legend_035->SetFillColor(0);

  TLegend* legend_037 = (TLegend*) legend_035->Clone();

  TLegend* legend_35 = (TLegend*) legend_035->Clone();
  legend_35->SetY1(0.74);

  TLegend* legend_57 = (TLegend*) legend_35->Clone();

  TH1F* dummyHist[8];
  
  for(unsigned int i = 0; i < 8; i++) {

    if(i==1 || i==2 || i==4 || i==6)
      continue;
  
    dummyHist[i] = new TH1F();
    dummyHist[i]->SetMarkerColor(markerColor[i]);
    dummyHist[i]->SetMarkerStyle(markerStyle[i]);

    if(i==0 || i==3 || i==5)
      legend_035->AddEntry(dummyHist[i], levels[i]);

    if(i==0 || i==3 || i==7)
      legend_037->AddEntry(dummyHist[i], levels[i]);

    if(i==3 || i==5)
      legend_35->AddEntry(dummyHist[i], levels[i]);

    if(i==5 || i==7)
      legend_57->AddEntry(dummyHist[i], levels[i]);

  }

  for(unsigned int i = 1; i < 9; i++) {

    TString suffix = "_";
    suffix += i;
    suffix += ".eps";

    if(i<4 || i==6) {
      canvasMassW_2dim->cd(i);
      legend_037->Draw();
      gPad->Print(baseName+"massW_2dim" + suffix);
    }

    canvasMassT_2dim->cd(i);
    legend_037->Draw();
    gPad->Print(baseName+"massT_2dim" + suffix);

  }

  for(unsigned int i = 1; i <= 9; i++) {

    TString suffix = "_";
    suffix += i;
    suffix += ".eps";

    canvasRespL->cd(i);
    if(i <= 3)
      legend_035->Draw();
    else if(i <= 6)
      legend_35->Draw();
    else
      legend_57->Draw();
    gPad->Print(baseName+"responseLight" + suffix);

    canvasRespB->cd(i);
    if(i <= 3)
      legend_035->Draw();
    else if(i <= 6)
      legend_35->Draw();
    else
      legend_57->Draw();
    gPad->Print(baseName+"responseB" + suffix);

  }

  // print one ps-file

  TString psName = outDir + "/" + name + "_" + hypoClass + ".ps";

  canvasMassW     ->Print(psName + "(");
  canvasMassW_2dim->Print(psName);
  canvasMassT     ->Print(psName);
  canvasMassT_2dim->Print(psName);
  canvasRespL     ->Print(psName);
  canvasRespB     ->Print(psName + ")");

  // clean-up

  delete canvasMassW;
  delete canvasMassW_2dim;
  delete canvasMassT;
  delete canvasMassT_2dim;
  delete canvasRespL;
  delete canvasRespB;

  return 0;
}

int main(int argc, char** argv)
{
  return analyzeJetEnergyCorrections(argv[1], argv[2]);
}
