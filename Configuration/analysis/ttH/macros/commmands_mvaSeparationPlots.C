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



TString inputFileName("mvaOutput/Nominal/combined/plots.root");


TString step = "7"; // which step to plot
std::vector<int> categories; // which merged categories, need to be in increasing order (empty vector for step without categories)
categories.push_back(5);
categories.push_back(6);
categories.push_back(7);



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


TString prefix("mvaP_");


step.Prepend("_step");


for(std::vector<int>::const_iterator i_category = categories.begin(); i_category != categories.end(); ++i_category){
    std::ostringstream convert;
    convert<<(*i_category);
    step.Append("_cate").Append(convert.str());
}
std::cout<<"\n\n\tStep: "<<step<<"\n\n\n";



std::vector<TString> histogramNames;
histogramNames.push_back(prefix+"jetChargeDiff"+step);
histogramNames.push_back(prefix+"meanDeltaPhi_b_met"+step);
histogramNames.push_back(prefix+"massDiff_recoil_bbbar"+step);
histogramNames.push_back(prefix+"pt_b_antiLepton"+step);
histogramNames.push_back(prefix+"pt_antiB_lepton"+step);
histogramNames.push_back(prefix+"deltaR_b_antiLepton"+step);
histogramNames.push_back(prefix+"deltaR_antiB_lepton"+step);
histogramNames.push_back(prefix+"btagDiscriminatorSum"+step);
histogramNames.push_back(prefix+"deltaPhi_antiBLepton_bAntiLepton"+step);
histogramNames.push_back(prefix+"massDiff_fullBLepton_bbbar"+step);
histogramNames.push_back(prefix+"meanMt_b_met"+step);
histogramNames.push_back(prefix+"massSum_antiBLepton_bAntiLepton"+step);
histogramNames.push_back(prefix+"massDiff_antiBLepton_bAntiLepton"+step);



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





//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++



gROOT->ProcessLine(".q");


}
