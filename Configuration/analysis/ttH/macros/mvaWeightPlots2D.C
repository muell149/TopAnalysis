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





//TString inputFileName("mvaOutput/plots.root");
TString inputFileName("selectionRoot/Nominal/emu/emu_ttbarH125tobbbar.root");

TString outputDirectory = "mvaOutput/ccc/";




TString prefix("mvaA_");

TString step = "8";

step.Prepend("_step");






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++





TFile* file1 = TFile::Open(inputFileName);

TCanvas* canvas1(0);

TH2* hist1(0);

TString histName;



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++



canvas1 = new TCanvas("canvas1");
canvas1->cd();


histName = "correct_"+prefix+"mvaWeightCorrectVsSwapped"+step;
file1->GetObject(histName + ";1", hist1);

hist1->Draw("box");

canvas1->Modified();
canvas1->Update();

TString plotName(outputDirectory + histName);

canvas1->Print(plotName + ".eps");
canvas1->Print(plotName + ".png");

canvas1->Close();




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




canvas1 = new TCanvas("canvas1");
canvas1->cd();


histName = "swapped_"+prefix+"mvaWeightCorrectVsSwapped"+step;
file1->GetObject(histName + ";1", hist1);

hist1->Draw("box");

canvas1->Modified();
canvas1->Update();

TString plotName(outputDirectory + histName);

canvas1->Print(plotName + ".eps");
canvas1->Print(plotName + ".png");

canvas1->Close();




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++



canvas1 = new TCanvas("canvas1");
canvas1->cd();


histName = "wrong_"+prefix+"mvaWeightCorrectVsSwapped"+step;
file1->GetObject(histName + ";1", hist1);

hist1->Draw("box");

canvas1->Modified();
canvas1->Update();

TString plotName(outputDirectory + histName);

canvas1->Print(plotName + ".eps");
canvas1->Print(plotName + ".png");

canvas1->Close();




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++



canvas1 = new TCanvas("canvas1");
canvas1->cd();


histName = "correct_"+prefix+"best_mvaWeightCorrectVsSwapped"+step;
file1->GetObject(histName + ";1", hist1);

hist1->Draw("box");

canvas1->Modified();
canvas1->Update();

TString plotName(outputDirectory + histName);

canvas1->Print(plotName + ".eps");
canvas1->Print(plotName + ".png");

canvas1->Close();




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




canvas1 = new TCanvas("canvas1");
canvas1->cd();


histName = "swapped_"+prefix+"best_mvaWeightCorrectVsSwapped"+step;
file1->GetObject(histName + ";1", hist1);

hist1->Draw("box");

canvas1->Modified();
canvas1->Update();

TString plotName(outputDirectory + histName);

canvas1->Print(plotName + ".eps");
canvas1->Print(plotName + ".png");

canvas1->Close();




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++



canvas1 = new TCanvas("canvas1");
canvas1->cd();


histName = "wrong_"+prefix+"best_mvaWeightCorrectVsSwapped"+step;
file1->GetObject(histName + ";1", hist1);

hist1->Draw("box");

canvas1->Modified();
canvas1->Update();

TString plotName(outputDirectory + histName);

canvas1->Print(plotName + ".eps");
canvas1->Print(plotName + ".png");

canvas1->Close();




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++





hist1->Delete();


file1->Close();


gROOT->ProcessLine(".q");


}
