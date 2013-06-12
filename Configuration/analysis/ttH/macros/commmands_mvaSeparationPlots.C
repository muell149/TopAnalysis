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


gROOT->ProcessLine(".L macros/mvaSeparationPlots.C++");



TString inputFileName("mvaOutput/plots.root");



std::vector<TString> histogramNames;
histogramNames.push_back("jetChargeDiff_step8");
histogramNames.push_back("meanDeltaPhi_b_met_step8");
histogramNames.push_back("massDiff_recoil_bbbar_step8");
histogramNames.push_back("pt_b_antiLepton_step8");
histogramNames.push_back("pt_antiB_lepton_step8");
histogramNames.push_back("deltaR_b_antiLepton_step8");
histogramNames.push_back("deltaR_antiB_lepton_step8");
histogramNames.push_back("btagDiscriminatorSum_step8");
histogramNames.push_back("deltaPhi_antiBLepton_bAntiLepton_step8");
histogramNames.push_back("massDiff_fullBLepton_bbbar_step8");
histogramNames.push_back("meanMt_b_met_step8");
histogramNames.push_back("massSum_antiBLepton_bAntiLepton_step8");
histogramNames.push_back("massDiff_antiBLepton_bAntiLepton_step8");
histogramNames.push_back("dijet_mvaWeightCorrect_step8");
histogramNames.push_back("dijet_bestMvaWeightCorrect_step8");
histogramNames.push_back("dijet_mvaWeightSwapped_step8");
histogramNames.push_back("dijet_bestMvaWeightSwapped_step8");


std::vector<TString> combinations;
combinations.push_back("correct");
combinations.push_back("swapped");
combinations.push_back("wrong");

TString outputDirectory = "mvaOutput/aaa/";

mvaSeparationPlots(inputFileName, outputDirectory, histogramNames, combinations);



outputDirectory = "mvaOutput/bbb/";

combinations.clear();
combinations.push_back("correct");
combinations.push_back("wrong");

mvaSeparationPlots(inputFileName, outputDirectory, histogramNames, combinations);





gROOT->ProcessLine(".q");


}
