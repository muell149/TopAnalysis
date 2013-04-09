{



gROOT->SetStyle("Plain");
gROOT->ForceStyle();
gStyle->SetOptStat(111110);

gStyle->SetPalette(1);      //Spektralpalette, Default: 0 resp. 50
//gStyle->SetNumberContours(20);  // Default: 20

double width = 600.;

gStyle->SetCanvasDefW(width);
gStyle->SetCanvasDefH(width);

gStyle->SetPadLeftMargin(0.15);
gStyle->SetPadRightMargin(0.10);

gStyle->SetPadTopMargin(0.10);
gStyle->SetPadBottomMargin(0.15);

gStyle->SetTitleOffset(1.4,"Y");
gStyle->SetTitleOffset(1.2,"X");


TGaxis::SetMaxDigits(3);


//TH1::StatOverflows(kTRUE);// compute mean etc including overflow!
//gStyle->SetHistMinimumZero(kTRUE); // no zero-suppression on y-axis
//gStyle->SetOptFit(222);         // 1: Fit-Parameter werden angezeigt
//gStyle->SetCanvasDefX(400);     // canvas (default) upper edge in X
//gStyle->SetCanvasDefY(200);     // canvas (default) upper edge in Y

//gStyle->SetHistLineWidth(2);



gStyle->SetTitleX(0.2);         // move upper left corner of title box to specified value
//gStyle->SetTitleY(0.99);        // move upper left corner of title box to specified value



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++



gStyle->SetTitleXSize(0.05);
gStyle->SetTitleYSize(0.05);
gStyle->SetTitleSize(0.05,"XY");
gStyle->SetLabelSize(0.05,"XY");



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


TCanvas* canvas1;

TFile* file1 = TFile::Open("mvaOutput/plots.root");
//TFile* file2 = TFile::Open("bla2.root");

TH1 *hist1, *hist2;

TLegend* legend1;

TString legendEntry1 = "correct", legendEntry2 = "wrong";
Double_t yMax1, yMax2;
Double_t yMin1, yMin2;
Double_t yMax;
TString outputDirectory = "mvaOutput/aaa/";



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("jetChargeDiff_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("meanDeltaPhi_b_met_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("massDiff_recoil_bbbar_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("pt_b_antiLepton_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("pt_antiB_lepton_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("deltaR_b_antiLepton_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("deltaR_antiB_lepton_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("btagDiscriminatorSum_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("deltaPhi_antiBLepton_bAntiLepton_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("massDiff_fullBLepton_bbbar_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("meanMT_b_met_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("massSum_antiBLepton_bAntiLepton_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("massDiff_antiBLepton_bAntiLepton_step8");
    file1->GetObject("correct_" + histName + ";1", hist1);
    file1->GetObject("wrong_" + histName + ";1", hist2);

  hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  hist1->SetLineColor(2);
  
  hist1->Scale(1./hist1->Integral());
  hist2->Scale(1./hist2->Integral());
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  yMax = (yMax2>yMax1) ? yMax2 : yMax1;
  hist1->GetYaxis()->SetRangeUser(0.,1.4*yMax);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(4);
  //hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  stats2->SetY1NDC(0.58);
  stats2->SetY2NDC(0.78);
  stats2->SetLineColor(2);
  stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.84,0.76,0.99);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + histName);

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++



  hist1->Delete();//hist2->Delete();
  
  file1->Close();//file2->Close();



}
