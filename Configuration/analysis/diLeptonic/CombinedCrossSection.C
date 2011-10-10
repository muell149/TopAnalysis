#define DILEPTON_MACRO

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <sys/stat.h>
#include <map>
#include "assert.h"
#include "TString.h"
#include "TExec.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TH1D.h"
#include "TH2D.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPostScript.h"
#include "TMath.h"
#include "TPad.h"
#include "TStyle.h"
#include "TGraphAsymmErrors.h"
#include "TPaveText.h"
#include "TopAnalysis/Configuration/analysis/semiLeptonic/diffXSection/basicFunctions.h"
#include "TopAnalysis/Configuration/analysis/semiLeptonic/diffXSection/HHStyle.h"


using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  CONFIGURABLES
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// path to the ingoing root histogram files
const char *USERNAME = getenv("USER");
const TString inpath(!strcmp(USERNAME, "wbehrenh") ? "./" : "/scratch/hh/lustre/cms/user/dammann/TopDileptonDiffXsec/results/standard/");
const TString outpath("plots/");

// output format
const TString outform(".eps");
// output file name for cross section hists
const TString crossOutfileName(outpath+"DiffXS_Histograms.root");
// output file name for cross section hists
const TString unfoldOutfileName(outpath+"Unfold_Histograms.root");
// output file name for kin reconstruction efficiency
const TString kinEffOutfileName(outpath+"KinEfficienies_Histograms.root");
// input file name with systematic errors
TString sysinpath("/afs/naf.desy.de/group/cms/scratch/markusm/Systematics/");

TFile* systematicsInputTotal = TFile::Open("/afs/naf.desy.de/user/w/wbehrenh/cms/systematicsSept21-output/Systematic_Errors_TOTAL.root");
TFile* systematicsInputDiff  = TFile::Open("/afs/naf.desy.de/user/w/wbehrenh/cms/systematicsSept21-output/Systematic_Errors_DIFF.root");

// input file name with Powheg curves
TFile* powhegInput = TFile::Open("~dammann/public/Powheg.root");
// input file name with MC@NLO curves
TFile* mcatnloInput = TFile::Open("~dammann/public/MCatNLO_status3.root");
//(not) constants for background scaling - it is preferred to set them via command line!
Bool_t scaleUpBG = kFALSE;
Bool_t scaleDownBG = kFALSE;
Bool_t scaleUpDY = kFALSE;
Bool_t scaleDownDY = kFALSE;
// if kTRUE the Drell Yan background is corrected by comparing the numbers of events in data and MC in Z veto region
const bool doDYcorrection = kTRUE;
// do you want to print the plots?
const bool doPrintControlPlots = kTRUE;
// do you want a shaded area to show the systematic uncertainty in the control plots?
const bool drawSystematicErrorBand = kTRUE;
// Plots for PAS
const bool PAS = kFALSE;
// do you want a legend in the plots?
const bool drawLegend = kTRUE;
// should there be ratio Ndata/Nmc plots below the actual distributions?
bool drawRatioPlot = kTRUE && !PAS;
// hide integrated value
const bool normaliseToUnitArea = kTRUE;
// preliminary?
const bool isPreliminary = kTRUE;
// luminosity used to normalise MC in plots and to calcutate cross sections
const Double_t lumi = 1143.221;
// relative uncertainty on the luminosity
const Double_t lumierr = 0.045;
// branching fractions for the different decay channels: mm, em, ee, combined (from BTV-11-001)
const Double_t branchingFraction[] = {0.016164, 0.032844, 0.016684, 0.06569};
// inclusive trigger scale factors for the different decay channels: mm, em, ee (from TOP-11-005)
const Double_t triggerSF[] = {0.961, 0.987, 0.977};
// inclusivelepton efficieny scale factors for the different decay channels: mm, em, ee (from TOP-11-005)
const Double_t leptonSF[] = {1., 1., 1.};
// b-tag scale factors
const char *btagSFAlgos[] = {"TCHEL", "TCHEM", "SSVHEM", 0};
const double btagSFValues[] = {0.982, 0.963, 0.973};
std::map <std::string, double> btagSFMap;
// which kin analyzer to use: 
const char *kinAnalyzer = "analyzeKinSolution8/"; //for TCHEL
//const char *kinAnalyzer = "analyzeKinSolution9/"; //for TCHEM
// MC production
const TString MCproduction("SUMMER11");
// hard-coded systematic estimate
const Double_t totalSystematic = 0.10; //default if no systematic hists are available
const Double_t bccAuto = 100000;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  GLOBAL VARABLES
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// number of files to be opened
const size_t Nfiles = 26; // number of ingoing files per channel
const size_t Nplots = 9;  // number of plots after merging

// define enums to avoid madnes while reading the code
enum Channel_t {kMM=0, kEM=1, kEE=2, kCOMBINED=3};
const char *channelName[] = {"mumu", "emu", "ee", "combined"};
const char *channelNameTeX[] = {"#mu#mu", "e#mu", "ee", "Dilepton Combined"};

enum Sample_t  {kDATA=0, kSIG=1, kTTBG=2, kTW=3, kVV=4, kDYT=5, kDYEM=6, kW=7, kQCD=8};
const char *sampleName[] = {"Data", "TTbar signal", "TTbar other", "tW", "VV", "DY tau tau", "DY mumu/ee", "W", "QCD"};
const char *sampleNameTeX[] = {"Data", "\\ttbar\\ signal", "other \\ttbar\\", "tW", "diboson",
                                "DY$\\rightarrow\\tau\\tau$", "DY$\\rightarrow e^+ e^-$", "W", "QCD"};

// input files for all channels and samples
TFile* files[3][Nfiles];
int totalEvents[Nfiles];
double sampleCrossSection[Nfiles];

// list of output root plots
TObjArray diffXsecHistogramList;
TObjArray unfoldHistogramList;
TObjArray kinEffHistogramList;

// corrections scale factors for DY BG are hard coded output from the other macros at the moment
Double_t ROutInEE      = -1.;
Double_t ROutInEEError = -1.;
Double_t ROutInMM      = -1.;
Double_t ROutInMMError = -1.;
Double_t kEff          = -1.;
Double_t kEffError     = -1.;
Double_t zMuNorm7      =  1.;
Double_t zElNorm7      =  1.;
Double_t zMuNorm8      =  1.;
Double_t zElNorm8      =  1.;
Double_t zMuNorm9      =  1.;
Double_t zElNorm9      =  1.;

// visible cross sections used for normlisation (without branching ratio)
Double_t visCrossSections[] = {-1.,-1.,-1.,-1.};
Double_t visCrossSectionsNoFit[] = {-1.,-1.,-1.,-1.};

bool dataIsFakeFromMonteCarlo = false;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  FUNCTIONS
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


TH1* SummedStackHisto(const THStack *stack) 
{
    TList* l = stack->GetHists();
    if (l->GetEntries() == 0) return 0;
    TH1* result = (TH1*) l->At(0)->Clone();
    for (int i = 1; i < l->GetEntries(); ++i) {
        result->Add((TH1*)l->At(i));
    }
    return result;
}



// helper function to draw data/MC ratio into control plots
void DrawRatio(const TH1* histNumerator, THStack* histDenominator, const Double_t ratioMin = 0.5, const Double_t ratioMax = 1.9) {//, int verbose=0, const std::vector<double> err_=std::vector<double>(0)) {
    TH1* stacksum = SummedStackHisto(histDenominator);
    if (!stacksum) {
        stacksum = (TH1*) histNumerator->Clone();
        std::cerr << "Cannot draw ratio plot with empty denominator!\n";
    }
    semileptonic::drawRatio(histNumerator, stacksum, ratioMin, ratioMax, *gStyle);
    if (stacksum->GetNbinsX() < 15 && stacksum->GetBinContent(4) == 0 && TString(stacksum->GetXaxis()->GetTitle()).Contains("N_{muons}")) {
        //multiplicity plot
        int bin = stacksum->GetBinContent(2) != 0 ? 2 : stacksum->GetBinContent(3) != 0 ? 3 : 1;
        std::cout << stacksum->GetXaxis()->GetTitle() << ": Ratio "
            << histNumerator->GetBinContent(bin) << " +- "
            << histNumerator->GetBinError(bin) << " / "
            << stacksum->GetBinContent(bin) << " +- "
            << stacksum->GetBinError(bin)
            << std::endl;
    }
    delete stacksum;
}



// fill legend with data markers and sample colours
void FillLegend(TLegend* leg, TH1* hist[], double factor=1.) {
//     leg->Clear();
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.023);

    char zlabel[200];
    if (factor == 1)
        strcpy(zlabel, "Z/a* #rightarrow ee/#mu#mu       ");
    else
        sprintf(zlabel, "%.2f #times Z/a* #rightarrow ee/#mu#mu", factor);
//         sprintf(zlabel, "#splitline{Z/a* #rightarrow ee/#mu#mu}{(#times %.2f)}", factor);

    if (hist[kDATA])  leg->AddEntry(hist[kDATA], "Data",                       "pe");
    if (hist[kSIG] )  leg->AddEntry(hist[kSIG],  "t#bar{t} signal",            "f" );
    if (hist[kTTBG])  leg->AddEntry(hist[kTTBG], "other t#bar{t}" ,            "f" );
    if (hist[kTW]  )  leg->AddEntry(hist[kTW],   "tW",                         "f" );
    if (hist[kVV]  )  leg->AddEntry(hist[kVV],   "dibosons",                   "f" );
    if (hist[kDYT] )  leg->AddEntry(hist[kDYT],  "Z/a* #rightarrow #tau#tau",  "f" );
    if (hist[kDYEM])  leg->AddEntry(hist[kDYEM], zlabel, "f" );
//     if (hist[kDYEM])  leg->AddEntry(hist[kDYEM], "Z/a* #rightarrow ee/#mu#mu", "f" );
//     if (factor != 1) {
//         sprintf(zlabel, "($times %.2f)", factor);
//         if (hist[kDYEM])  leg->AddEntry(zlabel, "f" );
//     }
    if (hist[kW]   )  leg->AddEntry(hist[kW],    "W+jets",                     "f" );
    if (hist[kQCD] )  leg->AddEntry(hist[kQCD],  "QCD",                        "f" );
    return;
}



// helper function for axis layout
void FormatHisto(TH1 *histo) {
    double max = histo->GetMaximum();
    histo->GetYaxis()->SetNoExponent(max >= 0.5 && max <= 100);
    histo->GetXaxis()->SetNoExponent(kTRUE);
}



// sets the fill colours and line colours for the histograms
void SetPlotFilling(TH1* hist[])
{
    if (hist[kSIG] )  {
        hist[kSIG] ->SetFillColor(kRed+1);
        hist[kSIG] ->SetLineColor(kBlack);
    }
    if (hist[kTTBG])  {
        hist[kTTBG]->SetFillColor(kRed-7);
        hist[kTTBG]->SetLineColor(kBlack);
    }
    if (hist[kTW]  )  {
        hist[kTW]  ->SetFillColor(kMagenta);
        hist[kTW]  ->SetLineColor(kBlack);
    }
    if (hist[kVV]  )  {
        hist[kVV]  ->SetFillColor(10);           // 10 is white, kwhite is transparent (bug in root ?!)
        hist[kVV]  ->SetLineColor(kBlack);
    }
    if (hist[kDYT] )  {
        hist[kDYT] ->SetFillColor(kAzure+8);
        hist[kDYT] ->SetLineColor(kBlack);
    }
    if (hist[kDYEM])  {
        hist[kDYEM]->SetFillColor(kAzure-2);
        hist[kDYEM]->SetLineColor(kBlack);
    }
    if (hist[kW]        )  {
        hist[kW]   ->SetFillColor(kGreen-3);
        hist[kW]   ->SetLineColor(kBlack);
    }
    if (hist[kQCD] )  {
        hist[kQCD] ->SetFillColor(kYellow);
        hist[kQCD] ->SetLineColor(kBlack);
    }
    return;
}



// weights the MC contributions.
// Per default NLO cross sections are used (LO for QCD).
// For DY the contribution can be scaled using a correction factor
void SetWeights(TH1* hist[], Double_t zECorr=1., Double_t zMuCorr=1.)
{
    if (MCproduction=="SUMMER11") {
        for (size_t i=1; i<Nfiles; ++i) {
            double dy = 1;
            if (i >= 12 && i <= 14) dy = zMuCorr;
            if (i >= 15 && i <= 17) dy = zECorr;
            if (hist[i]) hist[i]->Scale(lumi*sampleCrossSection[i]*dy/totalEvents[i]);
        }
    } else {
        std::cout << "ERROR in SetWeights: Unknown MC production!" << std::endl;
    }
}



// Get Clone of a histogram from a file
Int_t GetCloneHist(const TString path, const TString name, const Int_t channel, const Int_t idx, TH1*& hist)
{
    Int_t ok = 1;
    TH1* fhist;

    files[channel][idx]->GetObject(path.Copy().Append(name).Append(";1"), fhist);
    
    if (!fhist)
        ok = 0;
    else
        hist = (TH1*)fhist->Clone();

    if(!ok) cout << "cannot get hist " << path << name << endl;

    //delete fhist;
    return ok;
}



// Add Clone of a histogram from a file to an already existing hist
Int_t AddHist(const TString path, const TString name, const Int_t channel, const Int_t idx, TH1*& hist)
{
    Int_t ok = 1;
    TH1* fhist;
    files[channel][idx]->GetObject(path.Copy().Append(name).Append(";1"), fhist);

    if (!fhist)
        ok = 0;
    else
        hist->Add(fhist);

    if(!ok) cout << "cannot get hist " << path << name << endl;
    
    //delete fhist;
    return ok;
}



// help fuction to get histograms with the same name from an array of files
Int_t GetCloneHistArray(const TString path, const TString name, const Int_t channel, TH1* hists[])
{
    Int_t nhists = 0;

    TH1* fhists[Nfiles];
    TH1* dummyhist = 0;
    for (size_t i=0; i<Nfiles; ++i) {
        if (!files[channel][i]) {
            fhists[i]=0;
            //cout << "WARNING in GetCloneHistArray: File " << i << " , channel " << channel << " not found!" << endl;
            continue;
        }
        TString what(path.Copy().Append(name));
        if (files[channel][i] == 0) cout << what << " error!\n";

	files[channel][i]->GetObject(what.Data(), fhists[i]);
 
        if (!dummyhist) {
            if (!fhists[i]) {
                //std::cerr << "WARNING in GetCloneHistArray: Histogram " << what << " not found!!\n";
                return 0;
            };
            dummyhist = (TH1*)fhists[i]->Clone();
            dummyhist->Reset();
        }
    }
    for (size_t i=0; i<Nfiles; ++i) {
        if (fhists[i]) {
            hists[i] = (TH1*)fhists[i]->Clone();
            nhists++;
        }
        else if (dummyhist) {
            hists[i] = (TH1*)dummyhist->Clone();
            //cout << "WARNING in GetCloneHistArray: Histogram "<< name << " in sample " << i << " , channel " << channel << " not found!" << endl;
        }
        else return 0;
    }
    delete dummyhist;
    if (!nhists) std::cerr << "WARNING in GetCloneHistArray: Histogram " << path << "/" << name
            << " in channel " << channelName[channel] << " not found!" << std::endl;
    return nhists;
}



// help fuction to add histograms with the same name from an array of files to existing array of histograms
Int_t AddHistArray(const TString path, const TString name, const Int_t channel, TH1* hists[])
{
    Int_t nhists = 0;

    TH1* fhists[Nfiles];
    for (size_t i=0; i<Nfiles; ++i) {
        if (!files[channel][i]) {
            fhists[i]=0;
            //cout << "WARNING in AddHistArray: File " << i << " , channel " << channel << " not found!" << endl;
            continue;
        }
        files[channel][i]->GetObject(path.Copy().Append(name).Append(";1"), fhists[i]);

        if (fhists[i]) {
            hists[i]->Add(fhists[i]);
            nhists++;
        }
        //else{
        //  cout << "WARNING in AddHistArray: Histogram "<< name << " in sample " << i << " , channel " << channel << " not found!" << endl;
        //}
    }
    return nhists;
}



// merge the the Nfiles histograms to Nplots histograms
void MergeHistArray(TH1* inhists[], TH1* outhists[])
{
    outhists[kDATA] = inhists[0];    //data

    outhists[kSIG] = inhists[1];     //ttbar signal
    outhists[kSIG]->Add(inhists[2]);

    outhists[kTTBG] = inhists[3];    //ttbar other

    outhists[kTW] = inhists[4];      // tW
    outhists[kTW]->Add(inhists[5]);

    outhists[kVV] = inhists[6];      // vv
    outhists[kVV]->Add(inhists[7]);
    outhists[kVV]->Add(inhists[8]);

    outhists[kDYT] = inhists[9];     //dytautau
    outhists[kDYT]->Add(inhists[10]);
    outhists[kDYT]->Add(inhists[11]);

    outhists[kDYEM] = inhists[12];   //dy ee/mumu
    outhists[kDYEM]->Add(inhists[13]);
    outhists[kDYEM]->Add(inhists[14]);
    outhists[kDYEM]->Add(inhists[15]);
    outhists[kDYEM]->Add(inhists[16]);
    outhists[kDYEM]->Add(inhists[17]);

    outhists[kW] = inhists[18];      // wmu+wtau

    outhists[kQCD] = inhists[19];    //QCD muenriched, 3x eenriched
    outhists[kQCD]->Add(inhists[20]);
    outhists[kQCD]->Add(inhists[21]);
    outhists[kQCD]->Add(inhists[22]);
    outhists[kQCD]->Add(inhists[23]);
    outhists[kQCD]->Add(inhists[24]);
    outhists[kQCD]->Add(inhists[25]);
}



// add a data or weighted MC histogram to one of the output root files
void PutHistToRootFile(const TString path, const TString name, const Int_t channel, TObjArray& objArr, Bool_t data = kTRUE)
{
   TH1* hist;
   
   if(channel!=kCOMBINED){
       if(data){

	   if(GetCloneHist(TString(path).Copy().Append("/"), name, channel, 0, hist)==0){
              cout << "WARNING in PutHistToRootFile: Could not get hist  " << name << "!" << endl;
	      return;  
	   }       
       } else{
	   TH1* fhists[Nfiles];
	   if(GetCloneHistArray(TString(path).Copy().Append("/"), name, channel, fhists)==0){
              cout << "WARNING in PutHistToRootFile: Could not get hists  " << name << "!" << endl;
	      return;  
	   }
	   SetWeights(fhists);
	   TH1* mhists[Nplots];
	   MergeHistArray(fhists, mhists);
	   hist = mhists[1];    
	   for(size_t i=2; i<Nfiles; ++i){
              hist->Add(mhists[i]); 
	   }
       }
   } else {   
       if(data){       
	   if(GetCloneHist(TString(path).Copy().Append("/"), name, kMM, 0, hist)==0){
              cout << "WARNING in PutHistToRootFile: Could not get hist  " << name << "!" << endl;
	      return;  
	   }	   
	   if(AddHist(TString(path).Copy().Append("/"), name, kEM, 0, hist)==0){
              cout << "WARNING in PutHistToRootFile: Could not get hist  " << name << "!" << endl;
	      return;  
	   }	   
	   if(AddHist(TString(path).Copy().Append("/"), name, kEE, 0, hist)==0){
              cout << "WARNING in PutHistToRootFile: Could not get hist  " << name << "!" << endl;
	      return;  
	   }	   	   	            
       } else{
	   TH1* fhists[Nfiles];
	   if(GetCloneHistArray(TString(path).Copy().Append("/"), name, kMM, fhists)==0){
              cout << "WARNING in PutHistToRootFile: Could not get hists  " << name << "!" << endl;
	      return;  
	   }	   
	   if(AddHistArray(TString(path).Copy().Append("/"), name, kEM, fhists)==0){
              cout << "WARNING in PutHistToRootFile: Could not get hists  " << name << "!" << endl;
	      return;  
	   }	   
	   if(AddHistArray(TString(path).Copy().Append("/"), name, kEE, fhists)==0){
              cout << "WARNING in PutHistToRootFile: Could not get hists  " << name << "!" << endl;
	      return;  
	   }	   	   
	   SetWeights(fhists);
	   
	   TH1* mhists[Nplots];	   
	   MergeHistArray(fhists, mhists);	   	   
	   hist = mhists[1];    
	      
	   for(size_t i=2; i<Nplots; ++i){		      
              hist->Add(mhists[i]);	       
	   }   	   
       }      
   }
   
   TString hname(channelName[channel]);
   hname.Append("_");   
   hname.Append(path);   
   hname.Append("_");
   hname.Append(name);   
   if(!data)
     hname.Append("_MC");    
   
   hist->SetName(hname);      
   objArr.Add(hist);         
}



// calculate bin center corrections
TGraphAsymmErrors* BinCenterCorrectedGraph(TH1* dataHist, TH1* sigHist, const Double_t manualBinCenters[])
{
    const Int_t nDataBins = dataHist->GetNbinsX();

    Double_t xval[nDataBins];  // x-values of markers
    Double_t yval[nDataBins];  // y-value of markers
    Double_t xerrl[nDataBins]; // left x-errors of markers
    Double_t xerrr[nDataBins]; // right x-errors of markers
    Double_t yerrl[nDataBins]; // low y-errors of markers
    Double_t yerrh[nDataBins]; // up y-errors of markers
    
    for (Int_t i=1;i<=nDataBins;++i) {
        // Get values of bin edges in data hist...
        Double_t lowEdge= dataHist->GetXaxis()->GetBinLowEdge(i);
        Double_t upEdge = dataHist->GetXaxis()->GetBinUpEdge(i);

        // ... and find corresponding bin numbers in signal MC hist.
        Int_t lowBin= sigHist->GetXaxis()->FindBin(lowEdge);
        Int_t upBin = sigHist->GetXaxis()->FindBin(upEdge);

        // calculated mean value of MC in data bin
        Double_t binAve = 0.;
        for (Int_t j=lowBin; j<upBin; ++j) {
        binAve += sigHist->GetBinContent(j);
        }
        binAve /= (upBin-lowBin);

        Double_t diffNew   = -1000.;
        Double_t diffOld   = -1000.;
        Double_t binCenter = -1000.;

        for (Int_t j=lowBin; j<upBin; ++j) {
        diffNew = sigHist->GetBinContent(j)-binAve;
        if(diffNew>-1000. && diffOld>-1000.){
            if(diffNew*diffOld < 0.){ // fine-binned line crosses average
            binCenter	= sigHist->GetXaxis()->GetBinLowEdge(j);
            }
        }
        diffOld = sigHist->GetBinContent(j)-binAve;
        }

        if(binCenter==-1000.){
        cout << "WARNING in BinCenterCorrectedGraph: bin center could not be found." << endl;
        binCenter = 0.5*(lowBin+upBin);
        }

        // value where the corrected center is
        //binCenter = (lowEdge + ((upEdge-lowEdge)*(binCenter-lowBin))/(upBin-lowBin));

        // set values and errors of point i
        // in case of manualBinCenters, use them
        if (manualBinCenters && manualBinCenters[i-1] != bccAuto) {
            if (manualBinCenters[i-1] > bccAuto/10)
                xval[i-1] = binCenter + manualBinCenters[i-1] - bccAuto;
            else
                xval[i-1] = manualBinCenters[i-1];
        } else {
            xval[i-1]  = binCenter;
        }
        yval[i-1]  = dataHist->GetBinContent(i);
        xerrl[i-1] = binCenter - lowEdge;
        xerrr[i-1] = upEdge - binCenter;
        xerrl[i-1] = 0; xerrr[i-1] = 0;
        yerrl[i-1] = dataHist->GetBinError(i);
        yerrh[i-1] = dataHist->GetBinError(i);
    }
    
    TGraphAsymmErrors* graph = new TGraphAsymmErrors(nDataBins, xval, yval, xerrl, xerrr, yerrl, yerrh);

    return graph;
}



// plot sum of up to three plots (e.g. add pt hists for electrons and muons)
void PrintCombinedPlot(const char* module, const char* plot, const char* module2, const char* plot2, const char* module3, const char* plot3, Int_t channel,
                       const char* xtitle, const char* ytitle, Double_t min, Double_t max, Bool_t logx, Bool_t logy, Int_t rebin) {
    // make canvas
    assert(module);
    assert(module2);
    assert(module3);
    assert(plot);
    assert(plot2);
    assert(plot3);

    TCanvas* Canvas = new TCanvas("plot", "plot", 800, 800);

    TString moduleStr(module);
    TString module2Str(module2);
    TString module3Str(module3);
    TString plotStr(plot);
    TString plotStr2(plot2);
    TString plotStr3(plot3);

    TH1* hists[Nfiles];
    if (channel==kMM || channel==kEM || channel==kEE) {
        if (!GetCloneHistArray(moduleStr.Copy().Append("/"), plotStr, channel, hists)) return;
        if (module2Str.Length()) AddHistArray(module2Str.Copy().Append("/"), plotStr2, channel, hists);
        if (module3Str.Length()) AddHistArray(module3Str.Copy().Append("/"), plotStr3, channel, hists);
    } else if (channel==kCOMBINED) {
        if (!GetCloneHistArray(moduleStr.Copy().Append("/"), plotStr, kMM, hists)) return;
        AddHistArray(moduleStr.Copy().Append("/"), plotStr, kEM, hists);
        AddHistArray(moduleStr.Copy().Append("/"), plotStr, kEE, hists);
        if (module2Str.Length()) {
            AddHistArray(module2Str.Copy().Append("/"), plotStr2, kMM, hists);
            AddHistArray(module2Str.Copy().Append("/"), plotStr2, kEM, hists);
            AddHistArray(module2Str.Copy().Append("/"), plotStr2, kEE, hists);
        }
        if (module3Str.Length()) {
            AddHistArray(module3Str.Copy().Append("/"), plotStr3, kMM, hists);
            AddHistArray(module3Str.Copy().Append("/"), plotStr3, kEM, hists);
            AddHistArray(module3Str.Copy().Append("/"), plotStr3, kEE, hists);
        }
    } else {
        cout << "ERROR in PrintCombinedPlot: index " << channel << " for channel is out of range!" << endl;
        return;
    }

    if (rebin!=1) {
        for (size_t i=0; i<Nfiles; ++i) {
            hists[i]->Rebin(rebin);
        }
    }

    Double_t zMuCorr = 1.;
    Double_t zElCorr = 1.;
    
    if (doDYcorrection) {
      if (moduleStr.Contains("7")) {		    
  	zMuCorr = zMuNorm7;
  	zElCorr = zElNorm7;
      } else if (moduleStr.Contains("8")) {
  	zMuCorr = zMuNorm8;
  	zElCorr = zElNorm8; 
      } else if (moduleStr.Contains("9")) {
  	zMuCorr = zMuNorm9;
  	zElCorr = zElNorm9; 
      } 	 
    }	 
    
    SetWeights(hists, zElCorr, zMuCorr);

    TH1* mergedhists[Nplots];
    MergeHistArray(hists, mergedhists);

    SetPlotFilling(mergedhists);

    THStack* hstack = new THStack("hstack","");
    for (size_t i=1; i<Nplots; ++i) {
        hstack->Add(mergedhists[i]);
    }

    Canvas->Clear();
    hstack->Draw("HIST");
    FormatHisto(hstack->GetHistogram());

    
    // set axis titles
    TAxis *xaxis;
    if (drawRatioPlot) {
        hstack->GetXaxis()->SetTitle("");
        hstack->GetXaxis()->SetLabelSize(0);
        xaxis = static_cast<TH1*>(hstack->GetHists()->At(0))->GetXaxis();
    } else {
        xaxis = hstack->GetXaxis();
    }
    xaxis->SetTitle(xtitle);
    hstack->GetYaxis()->SetTitle(ytitle);
    hstack->GetYaxis()->SetTitleOffset(1.7);

    // set log scale (optional)
    if (logx) {
        gPad->SetLogx(1);
        hstack->GetXaxis()->SetMoreLogLabels(kTRUE);
    }
    if (logy) {
        gPad->SetLogy(1);
    }
    
    // set minimum and maximum: -1 indicated to take default
    if (min>0) hstack->SetMinimum(min);
    if (max>0) hstack->SetMaximum(max);

    // if max =-1 set default maximum    
    else {
        Double_t vspace = 1.3;
        if(logy){
          vspace = 10.;    
        }
        max = vspace*hstack->GetMaximum();
        if (mergedhists[kDATA]->GetMaximum() > max) {
            max = vspace*mergedhists[kDATA]->GetMaximum();
        }
        hstack->SetMaximum(max);
    }
   
    gStyle->SetErrorX(0);
    
    // style data histogram
    mergedhists[kDATA]->SetMarkerStyle(20);
    mergedhists[kDATA]->SetMarkerSize(1.5);
    mergedhists[kDATA]->SetLineWidth(1.5);   
    mergedhists[kDATA]->Draw("same,e1");
    TExec *setex1 = new TExec("setex1","gStyle->SetErrorX(0.5)");
    setex1->Draw();     
    
    TLegend* leg = new TLegend(0.67,0.58,0.92,0.87);
    
    if (channel == kEE) {
      FillLegend(leg, mergedhists, zElCorr);
    }
    else if (channel == kMM) {
      FillLegend(leg, mergedhists, zMuCorr);
    }
    else if (channel == kCOMBINED) {
      // calculate weighted average of ee and mumu correction;
      Double_t w1 = hists[12]->Integral();
      w1 += hists[13]->Integral();
      w1 += hists[14]->Integral();

      Double_t w2 = hists[12]->Integral();
      w2 += hists[13]->Integral();
      w2 += hists[14]->Integral();

      Double_t zCorr = (zMuCorr*w1 + zElCorr*w2)/(w1+w2);

      FillLegend(leg, mergedhists, zCorr);
    }
    else{
      FillLegend(leg, mergedhists);
    }

    // draw systematics error band
    TH1* syshist;
    if(drawSystematicErrorBand){
      syshist = (TH1*)hists[1]->Clone();
      
      for(Int_t i=0; i<=syshist->GetNbinsX(); ++i){
      
        Double_t binc = 0;
	for(size_t j=1; j<Nplots; ++j){
	  binc += mergedhists[j]->GetBinContent(i);
	}    
        syshist->SetBinContent(i, binc);
	
	// calculate uncertainty: lumi uncertainty
	Double_t binerr2 = binc*binc*lumierr*lumierr;
	Double_t bgunc = 0; // 30% uncertainty on BG from MC
	Double_t dyunc = 0; // 50% uncertainty on rescaled DY
	
	for(size_t j=3; j<Nplots; ++j){
	  
	  if(doDYcorrection && (moduleStr.Contains("7") || moduleStr.Contains("8") || moduleStr.Contains("9"))){
            if(j==kDYEM){
	      dyunc += mergedhists[j]->GetBinContent(i)*0.5;
	    }else{
	      bgunc += mergedhists[j]->GetBinContent(i)*0.3;
	    }	  
	  } else{	  
	    bgunc += mergedhists[j]->GetBinContent(i)*0.3;
	  } 
	} 
		
	binerr2 += (bgunc*bgunc);
	binerr2 += (dyunc*dyunc);
	
        syshist->SetBinError(i, TMath::Sqrt(binerr2));      
      }
      
      syshist->SetFillStyle(3004);
      syshist->SetFillColor(kBlack); 
      leg->AddEntry( syshist, "uncertainty", "f" );

      syshist->Draw("same,e2");
      
      TExec *setex2 = new TExec("setex2","gStyle->SetErrorX(0)");
      setex2->Draw();            
    }
            
    if (drawLegend) leg->Draw("same");

    semileptonic::DrawCMSLabels(isPreliminary, lumi);
    semileptonic::DrawDecayChLabel(channelNameTeX[channel]);
    if (plotStr.Contains("multi") && !moduleStr.Contains("Jet") )
        std::cout << outpath.Copy().Append(channelName[channel]).Append("/").
                    Append(channelName[channel]).Append("_").Append(moduleStr).
                    Append("_").Append(plotStr).Append(outform) << std::endl;
    if (drawRatioPlot) DrawRatio(mergedhists[kDATA], hstack, 0.5, 1.9);

    TString plotName(moduleStr.Copy().Append("_").Append(plotStr));
    if (module2Str.Length()) plotName.Append("_plus_").Append(module2Str).Append("_").Append(plotStr2);
    if (module3Str.Length()) plotName.Append("_plus_").Append(module3Str).Append("_").Append(plotStr3);

    Canvas->Print(outpath.Copy().Append(channelName[channel]).Append("/").
                    Append(channelName[channel]).Append("_").Append(plotName).Append(outform));
     
    delete Canvas;
    delete leg;
    delete hstack;
    delete syshist;
    return;
}



// print plot for a given channel (MC stack and data markers)
void PrintPlot(const char* module, const char* plot, Int_t channel, const char* xtitle, const char* ytitle, Double_t min=-1., Double_t max=-1., 
               Bool_t logx=kFALSE, Bool_t logy=kFALSE, Int_t rebin=1) {
    PrintCombinedPlot(module, plot, "", "", "", "", channel, xtitle, ytitle, min, max, logx, logy, rebin);
}



// function to print the DY mass in the whole range
void PrintDyPlot(Int_t step, Int_t channel, Double_t min, Double_t max,  Bool_t logx,  Bool_t logy, Int_t rebin) {

    gStyle->SetErrorX(0.5);

    TCanvas* Canvas = new TCanvas("plot", "plot", 800, 800);
    //TLegend* leg = getNewLegend();
    TLegend* leg = new TLegend(0.70,0.58,0.95,0.87);

    TString moduleStr("analyzeLeptonPair");
    moduleStr+=step;
    moduleStr+="/";
    TString moduleStr2("analyzeLeptonPairZvetoRegion");
    moduleStr2+=step;
    moduleStr2+="/";

    TString plotStr("DimassRC_");
    TH1* hists[Nfiles];
    if (channel==kMM) { // full mass range from plots outside and inside z veto region (2 plots are summed)
        plotStr.Append("MM");
        GetCloneHistArray(moduleStr, plotStr, kMM, hists);
        AddHistArray(moduleStr2,     plotStr, kMM, hists);
    }
    else if (channel==kEM) { // emu has no z veto so just normal printing of the invarian mass plot
        plotStr.Append("ME");
        GetCloneHistArray(moduleStr, plotStr, kEM, hists);
    }
    else if (channel==kEE) {
        plotStr.Append("EE");
        GetCloneHistArray(moduleStr, plotStr, kEE, hists);
        AddHistArray(moduleStr2,     plotStr, kEE, hists);
    }
    else if (channel==kCOMBINED) {
        GetCloneHistArray(moduleStr, plotStr.Copy().Append("MM"), kMM, hists);
        AddHistArray(moduleStr2,     plotStr.Copy().Append("MM"), kMM, hists);
        AddHistArray(moduleStr,      plotStr.Copy().Append("ME"), kEM, hists);
        AddHistArray(moduleStr,      plotStr.Copy().Append("EE"), kEE, hists);
        AddHistArray(moduleStr2,     plotStr.Copy().Append("EE"), kEE, hists);
        plotStr.Append("Combined");
    } else {
        cout << "ERROR in PrintDyPlot: index " << channel << " for channel is out of range!" << endl;
        return;
    }

    if (rebin!=1) {
        for (size_t i=0; i<Nfiles; ++i) {
            hists[i]->Rebin(rebin);
        }
    }

    Double_t zMuCorr = 1.;
    Double_t zElCorr = 1.;

    if (doDYcorrection) {
      if (moduleStr.Contains("7")) {		    
  	zMuCorr = zMuNorm7;
  	zElCorr = zElNorm7;
      } else if (moduleStr.Contains("8")) {
  	zMuCorr = zMuNorm8;
  	zElCorr = zElNorm8; 
      } else if (moduleStr.Contains("9")) {
  	zMuCorr = zMuNorm9;
  	zElCorr = zElNorm9; 
      } 	 
    }

    SetWeights(hists, zElCorr, zMuCorr);

    TH1* mergedhists[Nplots];
    MergeHistArray(hists, mergedhists);

    SetPlotFilling(mergedhists);

    THStack* hstack = new THStack("hstack","#mu#mu mass");
    for (size_t i=1; i<Nplots; ++i) {
        hstack->Add(mergedhists[i]);
    }

    if (channel == kEE) {
      FillLegend(leg, mergedhists, zElCorr);
    }
    else if (channel == kMM) {
      FillLegend(leg, mergedhists, zMuCorr);
    }
    else if (channel == kCOMBINED) {
      // calculate weighted average of ee and mumu correction;
      Double_t w1 = hists[12]->Integral();
      w1 += hists[13]->Integral();
      w1 += hists[14]->Integral();

      Double_t w2 = hists[12]->Integral();
      w2 += hists[13]->Integral();
      w2 += hists[14]->Integral();

      Double_t zCorr = (zMuCorr*w1 + zElCorr*w2)/(w1+w2);

      FillLegend(leg, mergedhists, zCorr);
    }
    else{
      FillLegend(leg, mergedhists);
    }

    hstack->Draw("HIST");

    // set axis titles
    char xtitle[20];
    if (channel==kMM)
        sprintf(xtitle,"M_{#mu#mu} [GeV]");
    else if (channel==kEM)
        sprintf(xtitle,"M_{e#mu} [GeV]");
    else if (channel==kEE)
        sprintf(xtitle,"M_{ee} [GeV]");

    TAxis *xaxis;
    if (drawRatioPlot) {
        hstack->GetXaxis()->SetTitle(xtitle);
        hstack->GetXaxis()->SetLabelSize(0);
        xaxis = static_cast<TH1*>(hstack->GetHists()->At(0))->GetXaxis();
    } else {
        xaxis = hstack->GetXaxis();
    }
    xaxis->SetTitle(xtitle);
    hstack->GetYaxis()->SetTitle("N_{evts} / bin");
    hstack->GetYaxis()->SetTitleOffset(1.7);

    // set log scale (optional)
    if (logx) {
        gPad->SetLogx(1);
        hstack->GetXaxis()->SetMoreLogLabels(kTRUE);
    }
    if (logy) {
        gPad->SetLogy(1);
    }
    
    // set minimum and maximum: -1 indicated to take default
    if (min>0) hstack->SetMinimum(min);
    if (max>0) hstack->SetMaximum(max);

    // if max =-1 set default maximum    
    else {
        Double_t vspace = 1.3;
        if(logy){
          vspace = 10.;    
        }
        max = vspace*hstack->GetMaximum();
        if (mergedhists[kDATA]->GetMaximum() > max) {
            max = vspace*mergedhists[kDATA]->GetMaximum();
        }
        hstack->SetMaximum(max);
    }

    // draw systematics error band
    TH1* syshist;
    if(drawSystematicErrorBand){
      syshist = (TH1*)hists[1]->Clone();
      
      for(Int_t i=0; i<=syshist->GetNbinsX(); ++i){
      
        Double_t binc = 0;
	for(size_t j=1; j<Nplots; ++j){
	  binc += mergedhists[j]->GetBinContent(i);
	}    
        syshist->SetBinContent(i, binc);
	
	// calculate uncertainty: lumi uncertainty
	Double_t binerr2 = binc*binc*lumierr*lumierr;
	Double_t bgunc = 0; // 30% uncertainty on BG from MC
	Double_t dyunc = 0; // 50% uncertainty on rescaled DY
	
	for(size_t j=3; j<Nplots; ++j){
	  
	  if(doDYcorrection && (moduleStr.Contains("7") || moduleStr.Contains("8") || moduleStr.Contains("9"))){
            if(j==kDYEM){
	      dyunc += mergedhists[j]->GetBinContent(i)*0.5;
	    }else{
	      bgunc += mergedhists[j]->GetBinContent(i)*0.3;
	    }	  
	  } else{	  
	    bgunc += mergedhists[j]->GetBinContent(i)*0.3;
	  } 
	} 
		
	binerr2 += (bgunc*bgunc);
	binerr2 += (dyunc*dyunc);
	
        syshist->SetBinError(i, TMath::Sqrt(binerr2));     
      }
      syshist->SetFillStyle(3004);
      syshist->SetFillColor(kBlack); 
      leg->AddEntry( syshist, "uncertainty", "f" );

      syshist->Draw("same,e2");
      
      TExec *setex2 = new TExec("setex2","gStyle->SetErrorX(0)");
      setex2->Draw();            
    }

    // style data histogram
    mergedhists[kDATA]->SetMarkerStyle(20);
    mergedhists[kDATA]->SetMarkerSize(1.5);
    mergedhists[kDATA]->SetLineWidth(1.5);
    mergedhists[kDATA]->Draw("same,e1");
    TExec *setex1 = new TExec("setex1","gStyle->SetErrorX(0.5)");
    setex1->Draw(); 

    if (drawLegend) leg->Draw("same");

    // draw 2 lines marking the Z veto region
    TLine l1(76,0,76,max);
    l1.SetLineStyle(2);

    TLine l2(106,0,106,max);
    l2.SetLineStyle(2);

    if (channel!=kEM) {
        l1.Draw("same");
        l2.Draw("same");
    }

    semileptonic::DrawCMSLabels(isPreliminary, lumi);
    semileptonic::DrawDecayChLabel(channelNameTeX[channel]);
    if (drawRatioPlot) DrawRatio(mergedhists[kDATA], hstack, 0.5, 1.9);

    TString titleStr = channelName[channel];
    titleStr += "_analyzeLeptonPair";
    titleStr += step;

    Canvas->Print(outpath.Copy().Append(channelName[channel]).Append("/").
                Append(titleStr).Append("_").Append(plotStr).Append("DY").Append(outform));

    gStyle->SetErrorX(0);

    delete Canvas;
    delete leg;
    delete hstack;
    delete syshist;    
    return;
}



// print the same plot for all decay channels
void PrintPlotAll(const char* module, const char* plot, const char* xtitle, const char* ytitle, Double_t min=-1, Double_t max=-1,
                  Bool_t logx = kFALSE, Bool_t logy = kFALSE, Int_t rebin = 1) {
    for (int i = 0; i <= 3; ++i) {
        PrintPlot(module, plot, i, xtitle, ytitle, min, max, logx, logy, rebin);
    }
}



// give back the argument hist with an added systematic error
TH1* CloneAddSystematics(TH1* histo) {
    TH1 *withsystematics = (TH1*) histo->Clone();
    for (int i = 1; i <= histo->GetNbinsX(); ++i) {
        Double_t olderr = histo->GetBinError(i);
        Double_t syserr = histo->GetBinContent(i)*totalSystematic;
        withsystematics->SetBinError(i, TMath::Sqrt(olderr*olderr + syserr*syserr));
    }
    return withsystematics;
}



// give back the argument hist with an added systematic error
TGraphAsymmErrors* CloneAddSystematics(TGraphAsymmErrors* graph, TString title) {
    TGraphAsymmErrors *withsystematics = (TGraphAsymmErrors*) graph->Clone();
    if (systematicsInputDiff && !systematicsInputDiff->IsZombie()) {
        //std::cout << "Systematics file is open!\n";
        TString upName = title + "_total_sys_error_up";
        TString downName = title + "_total_sys_error_down";
        //currently no difference between up+down errors - so take both from total_sys_error
        upName = title + "_total_sys_error";
        downName = title + "_total_sys_error";
        TH1 *up, *down;

        systematicsInputDiff->GetObject<TH1>(upName, up);
        systematicsInputDiff->GetObject<TH1>(downName, down);
        if (!up || !down) {
            std::cerr << "WARNING! No systematics for " << upName << "/" << downName << " found!\n";
            return withsystematics;
        }

        for (int i = 0; i < graph->GetN(); ++i) {
            Double_t olderrUp   = graph->GetErrorYhigh(i);
            Double_t olderrDown = graph->GetErrorYlow(i);
            Double_t syserrUp = up->GetBinContent(i+1)*graph->GetY()[i];
            Double_t syserrDown = down->GetBinContent(i+1)*graph->GetY()[i];
            //withsystematics->SetPointEYhigh(i, TMath::Sqrt(olderrUp*olderrUp + syserrUp*syserrUp));
            //withsystematics->SetPointEYlow(i, TMath::Sqrt(olderrDown*olderrDown + syserrDown*syserrDown));
            withsystematics->SetPointEYhigh(i, TMath::Sqrt(olderrUp*olderrUp + syserrUp*syserrUp));
            withsystematics->SetPointEYlow(i, TMath::Sqrt(olderrDown*olderrDown + syserrDown*syserrDown));
        }
    } else {
        std::cerr << "!!! NO SYSTEMATICS AVAILABLE!\n"
            << "!!! adding default systematics: "
            << 100*totalSystematic << "%\n";
        for (int i = 0; i < graph->GetN(); ++i) {
            Double_t olderrDown = graph->GetErrorYlow(i);
            Double_t olderrUp   = graph->GetErrorYhigh(i);
            Double_t syserr = (graph->GetY())[i]*totalSystematic;
            withsystematics->SetPointEYlow(i, TMath::Sqrt(olderrDown*olderrDown + syserr*syserr));
            withsystematics->SetPointEYhigh(i, TMath::Sqrt(olderrUp*olderrUp + syserr*syserr));
        }
    }
    return withsystematics;
}



// get new legend
TLegend* getNewLegend() {
    TLegend *leg = new TLegend();
    leg->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.25);
    leg->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.15);
    leg->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength());
    leg->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
    leg->SetTextFont(42);
    leg->SetTextSize(0.04);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextAlign(12);
    return leg;
}



// get generator cross section curve for NLO prediction
TH1* GetNloCurve(const char* particle, const char* quantity, const char* generator){

    TString histname("visible_");
    histname.Append(particle);
    histname.Append(quantity);
    histname.Append("_");
    histname.Append(generator);

    TH1* hist;

    TFile* file = NULL;
    if(strcmp(generator, "MCatNLO")==0){
      file = mcatnloInput;
    } else if(strcmp(generator, "Powheg")==0){
      file = powhegInput;
    } else{
      cerr << "WARNING in GetNloCurve: unknown generator '" << generator << "' specified!" << endl;
    }
   
    if (file && !file->IsZombie()) {
      file->GetObject<TH1>(histname, hist);

      if(!hist){
        cerr << "WARNING in GetNloCurve: input histogram '" << histname << "' could not been opened! Returning dummy!" << endl;
        hist = new TH1D();
        return hist;
      }
      
      TH1* rethist = (TH1*)hist->Clone(); 
    
      TH1* weight;
      file->GetObject<TH1>(TString("total_LeptonsPt_").Append(generator), weight);
      
      Double_t wgt = 1.;      
      if(!weight){
        cerr << "WARNING in GetNloCurve: histogram to extract original number of events could not be opened! No weighting applied!" << endl; 
      } else{
        Double_t nevents = weight->GetEntries();
        Double_t crosssection = 157.5;      
        Double_t binw = hist->GetBinWidth(1);
        wgt = crosssection/nevents/binw;
      }    
      rethist->Scale(wgt);
      return rethist;
    }

    cerr << "WARNING in GetNloCurve: input file could not been opened! Returning dummy!" << endl;
    hist = new TH1F();
    return hist;
}



// open all input files, set event numbers and cross sections
void SetupInputFiles() {

    totalEvents[0] = -1; //never scale data
    totalEvents[1] = 3581947;
    totalEvents[2] = 3581947;
    totalEvents[3] = 3581947;
    totalEvents[4] = 814390;
    totalEvents[5] = 809984;
    totalEvents[6] = 210667;
    totalEvents[7] = 204725;
    totalEvents[8] = 4187885;
    totalEvents[9] = 2200000;
    totalEvents[10] = 2032536;
    totalEvents[11] = 35101516;
    totalEvents[12] = 2186909;
    totalEvents[13] = 2133856;
    totalEvents[14] = 35101516;
    totalEvents[15] = 2121872;
    totalEvents[16] = 2254925;
    totalEvents[17] = 35101516;
    totalEvents[18] = 56789563;
    totalEvents[19] = 20258122;
    totalEvents[20] = 35729669;
    totalEvents[21] = 70392060;
    totalEvents[22] = 8150672;
    totalEvents[23] = 2081560;
    totalEvents[24] = 2030033;
    totalEvents[25] = 1082691;    
    
    
    sampleCrossSection[0] = 1;
    sampleCrossSection[1] = 157.5;
    sampleCrossSection[2] = 157.5;
    sampleCrossSection[3] = 157.5;
    sampleCrossSection[4] = 7.87;
    sampleCrossSection[5] = 7.87;
    sampleCrossSection[6] = 4.51;
    sampleCrossSection[7] = 0.61;
    sampleCrossSection[8] = 7.4;
    sampleCrossSection[9] = 3457;
    sampleCrossSection[10] = 1666;
    sampleCrossSection[11] = 3048;
    sampleCrossSection[12] = 3457;
    sampleCrossSection[13] = 1666;
    sampleCrossSection[14] = 3048;
    sampleCrossSection[15] = 3457;
    sampleCrossSection[16] = 1666;
    sampleCrossSection[17] = 3048;
    sampleCrossSection[18] = 31314;
    sampleCrossSection[19] = 2.966E8*2.855E-4; //see    http://cms.cern.ch/iCMS/prep/requestmanagement?dsn=QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6
    sampleCrossSection[20] = 2.361E8*0.0106; //see    http://cms.cern.ch/iCMS/prep/requestmanagement?dsn=QCD_Pt-20to30_EMEnriched_TuneZ2_7TeV-pythia6
    sampleCrossSection[21] = 5.944E7*0.061; //see    http://cms.cern.ch/iCMS/prep/requestmanagement?dsn=QCD_Pt-30to80_EMEnriched_TuneZ2_7TeV-pythia6
    sampleCrossSection[22] = 898200.0*0.159; //see    http://cms.cern.ch/iCMS/prep/requestmanagement?dsn=QCD_Pt-80to170_EMEnriched_TuneZ2_7TeV-pythia6
    sampleCrossSection[23] = 2.361E8*5.9E-4; //see    http://cms.cern.ch/iCMS/prep/requestmanagement?dsn=QCD_Pt-20to30_BCtoE_TuneZ2_7TeV-pythia6
    sampleCrossSection[24] = 5.944E7*0.00242; //see    http://cms.cern.ch/iCMS/prep/requestmanagement?dsn=QCD_Pt-30to80_BCtoE_TuneZ2_7TeV-pythia6
    sampleCrossSection[25] = 898200.0*0.0105; //see    http://cms.cern.ch/iCMS/prep/requestmanagement?dsn=QCD_Pt-80to170_BCtoE_TuneZ2_7TeV-pythia

    
    // mumu files
    files[kMM][0]= new TFile(inpath.Copy().Append("mumu_1fb.root"));
    files[kMM][1]= new TFile(inpath.Copy().Append("mumu_ttbarsignal.root"));
    files[kMM][2]= new TFile(inpath.Copy().Append("mumu_ttbarviatau.root"));
    files[kMM][3]= new TFile(inpath.Copy().Append("mumu_ttbarbg.root"));
    files[kMM][4]= new TFile(inpath.Copy().Append("mumu_singletop_tw.root"));
    files[kMM][5]= new TFile(inpath.Copy().Append("mumu_singleantitop_tw.root"));
    files[kMM][6]= new TFile(inpath.Copy().Append("mumu_wwto2l2nu.root"));
    files[kMM][7]= new TFile(inpath.Copy().Append("mumu_wzto3lnu.root"));
    files[kMM][8]= new TFile(inpath.Copy().Append("mumu_zztoall.root"));
    files[kMM][9]= new TFile(inpath.Copy().Append("mumu_dytautau1020.root"));
    files[kMM][10]=new TFile(inpath.Copy().Append("mumu_dytautau2050.root"));
    files[kMM][11]=new TFile(inpath.Copy().Append("mumu_dytautau50inf.root"));
    files[kMM][12]=new TFile(inpath.Copy().Append("mumu_dymumu1020.root"));
    files[kMM][13]=new TFile(inpath.Copy().Append("mumu_dymumu2050.root"));
    files[kMM][14]=new TFile(inpath.Copy().Append("mumu_dymumu50inf.root"));
    //files[kMM][15]=new TFile(inpath.Copy().Append("mumu_dyee1020.root"));
    //files[kMM][16]=new TFile(inpath.Copy().Append("mumu_dyee2050.root"));
    //files[kMM][17]=new TFile(inpath.Copy().Append("mumu_dyee50inf.root"));
    files[kMM][18]=new TFile(inpath.Copy().Append("mumu_wtolnu.root"));
    files[kMM][19]=new TFile(inpath.Copy().Append("mumu_qcdmu15.root"));
    //files[kMM][20]=new TFile(inpath.Copy().Append("mumu_qcdem2030.root"));
    //files[kMM][21]=new TFile(inpath.Copy().Append("mumu_qcdem3080.root"));
    //files[kMM][22]=new TFile(inpath.Copy().Append("mumu_qcdem80170.root"));
    //files[kMM][23]=new TFile(inpath.Copy().Append("mumu_qcdbcem2030.root"));
    //files[kMM][24]=new TFile(inpath.Copy().Append("mumu_qcdbcem3080.root"));
    //files[kMM][25]=new TFile(inpath.Copy().Append("mumu_qcdbcem80170.root"));    
    
    // emu files
    files[kEM][0]= new TFile(inpath.Copy().Append("emu_1fb.root"));
    files[kEM][1]= new TFile(inpath.Copy().Append("emu_ttbarsignal.root"));
    files[kEM][2]= new TFile(inpath.Copy().Append("emu_ttbarviatau.root"));
    files[kEM][3]= new TFile(inpath.Copy().Append("emu_ttbarbg.root"));
    files[kEM][4]= new TFile(inpath.Copy().Append("emu_singletop_tw.root"));
    files[kEM][5]= new TFile(inpath.Copy().Append("emu_singleantitop_tw.root"));
    files[kEM][6]= new TFile(inpath.Copy().Append("emu_wwto2l2nu.root"));
    files[kEM][7]= new TFile(inpath.Copy().Append("emu_wzto3lnu.root"));
    files[kEM][8]= new TFile(inpath.Copy().Append("emu_zztoall.root"));
    files[kEM][9]= new TFile(inpath.Copy().Append("emu_dytautau1020.root"));
    files[kEM][10]=new TFile(inpath.Copy().Append("emu_dytautau2050.root"));
    files[kEM][11]=new TFile(inpath.Copy().Append("emu_dytautau50inf.root"));
    files[kEM][12]=new TFile(inpath.Copy().Append("emu_dymumu1020.root"));
    files[kEM][13]=new TFile(inpath.Copy().Append("emu_dymumu2050.root"));
    files[kEM][14]=new TFile(inpath.Copy().Append("emu_dymumu50inf.root"));
    files[kEM][15]=new TFile(inpath.Copy().Append("emu_dyee1020.root"));
    files[kEM][16]=new TFile(inpath.Copy().Append("emu_dyee2050.root"));
    files[kEM][17]=new TFile(inpath.Copy().Append("emu_dyee50inf.root"));
    files[kEM][18]=new TFile(inpath.Copy().Append("emu_wtolnu.root"));
    files[kEM][19]=new TFile(inpath.Copy().Append("emu_qcdmu15.root"));
    files[kEM][20]=new TFile(inpath.Copy().Append("emu_qcdem2030.root"));
    files[kEM][21]=new TFile(inpath.Copy().Append("emu_qcdem3080.root"));
    files[kEM][22]=new TFile(inpath.Copy().Append("emu_qcdem80170.root"));
    files[kEM][23]=new TFile(inpath.Copy().Append("emu_qcdbcem2030.root"));
    files[kEM][24]=new TFile(inpath.Copy().Append("emu_qcdbcem3080.root"));
    files[kEM][25]=new TFile(inpath.Copy().Append("emu_qcdbcem80170.root"));    
    
    // ee files
    files[kEE][0]= new TFile(inpath.Copy().Append("ee_1fb.root"));
    files[kEE][1]= new TFile(inpath.Copy().Append("ee_ttbarsignal.root"));
    files[kEE][2]= new TFile(inpath.Copy().Append("ee_ttbarviatau.root"));
    files[kEE][3]= new TFile(inpath.Copy().Append("ee_ttbarbg.root"));
    files[kEE][4]= new TFile(inpath.Copy().Append("ee_singletop_tw.root"));
    files[kEE][5]= new TFile(inpath.Copy().Append("ee_singleantitop_tw.root"));
    files[kEE][6]= new TFile(inpath.Copy().Append("ee_wwto2l2nu.root"));
    files[kEE][7]= new TFile(inpath.Copy().Append("ee_wzto3lnu.root"));
    files[kEE][8]= new TFile(inpath.Copy().Append("ee_zztoall.root"));
    files[kEE][9]= new TFile(inpath.Copy().Append("ee_dytautau1020.root"));
    files[kEE][10]=new TFile(inpath.Copy().Append("ee_dytautau2050.root"));
    files[kEE][11]=new TFile(inpath.Copy().Append("ee_dytautau50inf.root"));
    //files[kEE][12]=new TFile(inpath.Copy().Append("ee_dymumu1020.root"));
    //files[kEE][13]=new TFile(inpath.Copy().Append("ee_dymumu2050.root"));
    //files[kEE][14]=new TFile(inpath.Copy().Append("ee_dymumu50inf.root"));
    files[kEE][15]=new TFile(inpath.Copy().Append("ee_dyee1020.root"));
    files[kEE][16]=new TFile(inpath.Copy().Append("ee_dyee2050.root"));
    files[kEE][17]=new TFile(inpath.Copy().Append("ee_dyee50inf.root"));
    files[kEE][18]=new TFile(inpath.Copy().Append("ee_wtolnu.root"));
    //files[kEE][19]=new TFile(inpath.Copy().Append("ee_qcdmu15.root"));
    files[kEE][20]=new TFile(inpath.Copy().Append("ee_qcdem2030.root"));
    files[kEE][21]=new TFile(inpath.Copy().Append("ee_qcdem3080.root"));
    files[kEE][22]=new TFile(inpath.Copy().Append("ee_qcdem80170.root"));
    files[kEE][23]=new TFile(inpath.Copy().Append("ee_qcdbcem2030.root"));
    files[kEE][24]=new TFile(inpath.Copy().Append("ee_qcdbcem3080.root"));
    files[kEE][25]=new TFile(inpath.Copy().Append("ee_qcdbcem80170.root"));      
}



void OpenTestAndClose(TFile *file) {
    if (file && file->IsOpen()) file->Close();
}



void CloseFiles() {
    std::cerr << "closing all open files...\n";
    OpenTestAndClose(systematicsInputTotal);
    OpenTestAndClose(systematicsInputDiff);
    for (size_t i = 0; i < Nfiles; ++i) {
        OpenTestAndClose(files[kEE][i]);
        OpenTestAndClose(files[kEM][i]);
        OpenTestAndClose(files[kMM][i]);
    }
}



void CreateControlPlots() {
    if (PAS) {
        PrintPlot("analyzeJets7", "multi",      kCOMBINED, "N_{jets}",       "events", 0, -1,kFALSE,kTRUE);
        PrintPlot("analyzeJets7", "multiTCHEL", kCOMBINED, "N_{tags,TCHEL}", "events", 0, -1,kFALSE,kTRUE);
        PrintPlot("analyzeJets7", "pt",         kCOMBINED, "p_{T}^{jet} #left[#frac{GeV}{c}#right]","jets", 0, -1,kFALSE,kTRUE, 5);
        PrintPlot("analyzeJets7", "ht",         kCOMBINED, "H_{T} [GeV]","events", 0, -1,kFALSE,kTRUE, 5);
        PrintCombinedPlot("analyzeElecs7", "pt", "analyzeMuons7", "pt", "", "", kCOMBINED, "p_{T}^{l} #left[#frac{GeV}{c}#right]",  "leptons",  0.0, -1,0,kTRUE,5);
//         PrintCombinedPlot("analyzeLeptonPair3", "DimassRC_EE",
//                           "analyzeLeptonPair3", "DimassRC_EM",
//                           "analyzeLeptonPair3", "DimassRC_MM", kCOMBINED, "M^{l^{+}l^{-}} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
			  
        PrintPlot("analyzeJets8", "multi",      kCOMBINED, "N_{jets}",       "events", 0, -1,kFALSE,kTRUE);
        PrintPlot("analyzeJets8", "multiTCHEL", kCOMBINED, "N_{tags,TCHEL}", "events", 0, -1,kFALSE,kTRUE);
        PrintPlot("analyzeJets8", "pt",         kCOMBINED, "p_{T}^{jet} #left[#frac{GeV}{c}#right]","jets", 0, -1,kFALSE,kTRUE, 5);
        PrintPlot("analyzeJets8", "ht",         kCOMBINED, "H_{T} [GeV]", "events", 0, -1,kFALSE,kTRUE, 5);
        PrintCombinedPlot("analyzeElecs8", "pt", "analyzeMuons8", "pt", "", "", kCOMBINED, "p_{T}^{l} #left[#frac{GeV}{c}#right]",  "leptons",  0.0, -1,0,kTRUE,5);
        return;
    };

    PrintPlotAll("analyzeMuons1", "pf_iso", "PF Iso", "N_{events} / bin", 1, -1, kFALSE, kTRUE, 2);
    PrintPlotAll("analyzeMuons1", "multi",     "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons1", "pt",        "p_{T,#mu} [GeV]",  "N_{#mu} / bin",  0.0, -1,0,0,5);
    PrintPlotAll("analyzeMuons1", "eta",       "#eta_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,2);
    PrintPlotAll("analyzeMuons1", "iso_comb2", "pf_iso_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,4);
    PrintPlotAll("analyzeMuons1", "dep_ecal",     "muon dep_ecal",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons1", "dep_hcal",     "muon dep_hcal",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons1", "nhits",        "muon nhits",           "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons1", "n_pixhits",        "muon pix hits",           "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons1", "n_trackerhits",        "muon tracker hits",           "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons1", "n_mustations",        "muon station hits",           "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons1", "n_validmuhits","muon n valid mu hits", "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons1", "chi_norm",     "muon chi norm",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons1", "d0",           "muon d0",              "N_{events} / bin", 0.0, -1,0,0);
    
    PrintPlot("analyzeElecs2", "pf_iso", kEM, "PF Iso", "N_{events} / bin", 1, -1, kFALSE, kTRUE, 4);
    PrintPlot("analyzeElecs2", "pf_iso", kEE, "PF Iso", "N_{events} / bin", 1, -1, kFALSE, kTRUE, 4);
    PrintPlot("analyzeMuons2", "pf_iso", kEM, "PF Iso", "N_{events} / bin", 1, -1, kFALSE, kTRUE, 2);
    PrintPlot("analyzeMuons2", "pf_iso", kMM, "PF Iso", "N_{events} / bin", 1, -1, kFALSE, kTRUE, 2);

    // STEP 3
    PrintPlotAll("analyzeUnscaledVertex", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);
    PrintPlotAll("analyzeVertex2", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);

    PrintPlotAll("analyzeJets3",       "multi",       "N_{jets}",         "N_{events} / bin", 1.0, -1,0,1);
    PrintPlotAll("analyzeJets3",       "multiTCHEM",  "N_{tags,TCHEL}",   "N_{events} / bin", 1.0, -1,0,1);
    PrintPlotAll("analyzeJets3",       "pt",        "p_{T,jet} [GeV]",  "N_{jets} / bin", 0.0, -1,0,0,5);
    PrintPlotAll("analyzeJets3",       "eta",       "#eta_{jet}",       "N_{jets} / bin", 0.0, -1,0,0,2);
    PrintPlotAll("analyzeJets3",       "ht",         "H_{T, all jets} [GeV]", "N_{events} / bin", 0, -1, 0, kTRUE, 5);
    PrintPlotAll("analyzeVertex3", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);

    PrintPlotAll("analyzeMuons3",       "multi",     "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons3",       "pt",        "p_{T,#mu} [GeV]",  "N_{#mu} / bin",  0.0, -1,0,0,5);
    PrintPlotAll("analyzeMuons3",       "eta",       "#eta_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,2);
    PrintPlotAll("analyzeMuons3",       "pf_iso",    "pf_iso_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,4);
    PrintPlotAll("analyzeMuons3",       "iso_comb2", "pf_iso_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,4);
    PrintPlotAll("analyzeMuons3",       "jet_dist",  "jet_dist",      "N_{#mu} / bin",   0.0, -1,0,0,4);

    PrintPlotAll("analyzeElecs3",       "multi",    "N_{e}",           "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeElecs3",       "pt",       "p_{T,e} [GeV]",   "N_{e} / bin",     0.0, -1,0,0,5);
    PrintPlotAll("analyzeElecs3",       "eta",      "#eta_{e}",        "N_{e} / bin",     0.0, -1,0,0,2);

    PrintPlotAll("analyzeElecs3", "jet_dist", "jet distance", "N", 0, 0, 0, 0, 5);
    PrintPlotAll("analyzeElecs3", "convDcot", "convDcot", "N", 0, 0, 0, 0, 5);
    PrintPlotAll("analyzeElecs3", "convDist", "convDist", "N", 0, 0, 0, 0, 5);
    PrintPlotAll("analyzeElecs3", "electronmap", "electronmap", "N");

    PrintCombinedPlot("analyzeElecs3", "pt", "analyzeMuons3", "pt", "", "", kEM, "p_{T,l}", "N_{l} / bin", 0, -1, kFALSE, kFALSE, 5);


    PrintPlotAll("analyzeElecs4", "convDcot", "convDcot", "N", 0, 0, 0, 0, 5);
    PrintPlotAll("analyzeElecs4", "convDist", "convDist", "N", 0, 0, 0, 0, 5);
    PrintPlotAll("analyzeElecs4", "electronmap", "electronmap", "N");
    PrintPlotAll("analyzeVertex4", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);

    PrintPlot("analyzeLeptonPair3", "D_eta_elecsRC", kEE, "eta1-eta2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair3", "D_eta_muonsRC", kMM, "eta1-eta2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair3", "D_phi_elecsRC", kEE, "phi1-phi2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair3", "D_phi_muonsRC", kMM, "phi1-phi2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);

    PrintPlot("analyzeLeptonPair3", "DimassRC_MM", kMM,       "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair3", "DimassRC_MM", kCOMBINED, "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair3", "DimassRC_ME", kEM,       "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair3", "DimassRC_ME", kCOMBINED, "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair3", "DimassRC_EE", kEE,       "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair3", "DimassRC_EE", kCOMBINED, "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);

    PrintPlot("analyzeLeptonPair3SS", "DimassWC_MM", kCOMBINED, "M_{#mu^{#pm}#mu^{#pm}} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair3SS", "DimassWC_ME", kCOMBINED, "M_{e^{#pm}#mu^{#pm}} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair3SS", "DimassWC_EE", kCOMBINED, "M_{e^{#pm}e^{#pm}} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);

    PrintPlotAll("analyzeMuons4",       "multi",     "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlot("analyzeLeptonPair4", "D_eta_elecsRC", kEE, "eta1-eta2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair4", "D_eta_muonsRC", kMM, "eta1-eta2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair4", "D_phi_elecsRC", kEE, "phi1-phi2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair4", "D_phi_muonsRC", kMM, "phi1-phi2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);

    PrintPlotAll("analyzeMuons5",       "multi",     "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);

    // STEP 6
    PrintPlotAll("analyzeJets6",       "multi",        "N_{jets}",         "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets6",       "multiTCHEL",   "N_{tags,TCHEL}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets6",       "multiTCHEM",   "N_{tags,TCHEM}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets6",       "multiSSVHEM",  "N_{tags,SSVHEM}",  "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets6",       "pt",           "p_{T,jet} [GeV]",  "N_{jets} / bin", 0.0, -1,0,0,5);
    PrintPlotAll("analyzeJets6",       "eta",          "#eta_{jet}",       "N_{jets} / bin", 0.0, -1,0,0,2);
    PrintPlotAll("analyzeJets6",       "ht",           "H_{T, all jets} [GeV]", "N_{events} / bin", 0, -1, 0, kTRUE, 5);

    PrintPlotAll("analyzeMuons6",       "multi",       "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons6",       "pt",          "p_{T,#mu} [GeV]",  "N_{#mu} / bin",  0.0, -1,0,0,5);
    PrintPlotAll("analyzeMuons6",       "eta",         "#eta_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,2);
    
    PrintPlotAll("analyzeMuons6SS",       "pt",        "p_{T,#mu} [GeV]",  "N_{#mu} / bin",  0.0, -1,0,0,5);
    PrintPlotAll("analyzeMuons6SS",       "eta",       "#eta_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,2);
    PrintPlotAll("analyzeMuons6SS",       "pf_iso",    "pf_iso_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,4);

    PrintPlotAll("analyzeElecs6",       "multi",       "N_{e}",           "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeElecs6",       "pt",          "p_{T,e} [GeV]",   "N_{e} / bin",     0.0, -1,0,0,5);
    PrintPlotAll("analyzeElecs6",       "eta",         "#eta_{e}",        "N_{e} / bin",     0.0, -1,0,0,2);

    PrintPlotAll("analyzeMet6", "et", "MET", "N/bin", 0, -1, 0, 0, 5);

    PrintPlot("analyzeLeptonPair6", "D_eta_elecsRC", kEE, "eta1-eta2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair6", "D_eta_muonsRC", kMM, "eta1-eta2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair6", "D_phi_elecsRC", kEE, "phi1-phi2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair6", "D_phi_muonsRC", kMM, "phi1-phi2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);

    PrintPlot("analyzeLeptonPair6", "DimassRC_MM", kMM,       "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair6", "DimassRC_MM", kCOMBINED, "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair6", "DimassRC_ME", kEM,       "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair6", "DimassRC_ME", kCOMBINED, "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair6", "DimassRC_EE", kEE,       "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair6", "DimassRC_EE", kCOMBINED, "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);

    PrintPlot("analyzeLeptonPair6SS", "DimassWC_MM", kCOMBINED, "M_{#mu^{#pm}#mu^{#pm}} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair6SS", "DimassWC_ME", kCOMBINED, "M_{e^{#pm}#mu^{#pm}} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair6SS", "DimassWC_EE", kCOMBINED, "M_{e^{#pm}e^{#pm}} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);

    PrintPlotAll("analyzeVertex6", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);

    PrintDyPlot(6, kMM,     0.0, -1., 0, 0, 2);
    PrintDyPlot(6, kEM,     0.0, -1., 0, 0, 2);
    PrintDyPlot(6, kEE,     0.0, -1., 0, 0, 2);
    PrintDyPlot(6, kCOMBINED, 0.0, -1., 0, 0, 2);


    // STEP 7
    PrintPlotAll("analyzeJets7",       "multi",         "N_{jets}",         "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets7",       "multiTCHEL",  "N_{tags,TCHEL}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets7",       "multiTCHEM",  "N_{tags,TCHEM}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets7",       "pt",          "p_{T,jet} [GeV]",  "N_{jets} / bin", 0.0, -1,0,0,5);
    PrintPlotAll("analyzeJets7",       "eta",         "#eta_{jet}",       "N_{jets} / bin", 0.0, -1,0,0,2);
    PrintPlotAll("analyzeJets7",       "ht",          "H_{T, all jets} [GeV]", "N_{events} / bin", 0, -1, 0, kTRUE, 5);

    PrintPlotAll("analyzeMuons7",       "multi",      "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons7",       "pt",         "p_{T,#mu} [GeV]",  "N_{#mu} / bin",  0.0, -1,0,0,5);
    PrintPlotAll("analyzeMuons7",       "eta",        "#eta_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,2);

    PrintPlotAll("analyzeElecs7",       "multi",      "N_{e}",           "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeElecs7",       "pt",         "p_{T,e} [GeV]",   "N_{e} / bin",     0.0, -1,0,0,5);
    PrintPlotAll("analyzeElecs7",       "eta",        "#eta_{e}",        "N_{e} / bin",     0.0, -1,0,0,2);

    PrintPlotAll("analyzeKinSolution7", "kin_TopPt",         "p_{T,t} [GeV]",   "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution7", "kin_TopMass",       "M_{t} [GeV]",     "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution7", "kin_TopRapidity",   "y_{t}",       "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution7", "kin_TtBarPt",       "p_{T,t#bar{t}} [GeV]", "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution7", "kin_TtBarMass",     "M_{t#bar{t}} [GeV]", "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution7", "kin_TtBarRapidity", "y_{t#bar{t}}", "N_{events} / bin",  0.0, -1,0,0,2);

    PrintPlot("analyzeLeptonPair7", "DimassRC_MM", kMM,       "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair7", "DimassRC_MM", kCOMBINED, "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair7", "DimassRC_ME", kEM,       "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair7", "DimassRC_ME", kCOMBINED, "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair7", "DimassRC_EE", kEE,       "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair7", "DimassRC_EE", kCOMBINED, "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);

    PrintPlotAll("analyzeVertex7", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);

    PrintDyPlot(7, kMM,     0.0, -1., 0, 0, 2);
    PrintDyPlot(7, kEM,     0.0, -1., 0, 0, 2);
    PrintDyPlot(7, kEE,     0.0, -1., 0, 0, 2);
    PrintDyPlot(7, kCOMBINED, 0.0, -1., 0, 0, 2);


    // STEP 8
    PrintPlotAll("analyzeJets8",       "multi",       "N_{jets}",         "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets8",       "multiTCHEL",  "N_{tags,TCHEL}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets8",       "multiTCHEM",  "N_{tags,TCHEM}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets8",       "pt",          "p_{T,jet} [GeV]",  "N_{jets} / bin", 0.0, -1,0,0,5);
    PrintPlotAll("analyzeJets8",       "eta",         "#eta_{jet}",       "N_{jets} / bin", 0.0, -1,0,0,2);
    PrintPlotAll("analyzeJets8",       "ht",          "H_{T, all jets} [GeV]", "N_{events} / bin", 0, -1, 0, kTRUE, 5);

    PrintPlotAll("analyzeMuons8",       "multi",      "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons8",       "pt",         "p_{T,#mu} [GeV]",  "N_{#mu} / bin",  0.0, -1,0,0,5);
    PrintPlotAll("analyzeMuons8",       "eta",        "#eta_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,2);

    PrintPlotAll("analyzeElecs8",       "multi",      "N_{e}",           "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeElecs8",       "pt",         "p_{T,e} [GeV]",   "N_{e} / bin",     0.0, -1,0,0,5);
    PrintPlotAll("analyzeElecs8",       "eta",        "#eta_{e}",        "N_{e} / bin",     0.0, -1,0,0,2);

    PrintPlotAll("analyzeKinSolution8", "kin_TopPt",      "p_{T,t} [GeV]",   "N_{events} / bin",  0.0, -1,0,0,4);
    PrintPlotAll("analyzeKinSolution8", "kin_TopMass",    "M_{t} [GeV]",     "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution8", "kin_TopRapidity",      "y_{t}",       "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution8", "kin_TtBarPt",      "p_{T,t#bar{t}} [GeV]", "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution8", "kin_TtBarMass",            "M_{t#bar{t}} [GeV]", "N_{events} / bin",  0.0, -1,0,0,4);
    PrintPlotAll("analyzeKinSolution8", "kin_TtBarRapidity",    "y_{t#bar{t}}", "N_{events} / bin",  0.0, -1,0,0,2);

    PrintPlot("analyzeLeptonPair8", "DimassRC_MM", kMM,       "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair8", "DimassRC_MM", kCOMBINED, "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair8", "DimassRC_ME", kEM,       "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair8", "DimassRC_ME", kCOMBINED, "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair8", "DimassRC_EE", kEE,       "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair8", "DimassRC_EE", kCOMBINED, "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);

    PrintPlotAll("analyzeVertex8", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);

    PrintDyPlot(8, kMM,     0.0, -1., 0, 0, 2);
    PrintDyPlot(8, kEM,     0.0, -1., 0, 0, 2);
    PrintDyPlot(8, kEE,     0.0, -1., 0, 0, 2);
    PrintDyPlot(8, kCOMBINED, 0.0, -1., 0, 0, 2);

    // STEP 9
    PrintPlotAll("analyzeJets9",       "multi",       "N_{jets}",         "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets9",       "multiTCHEL",  "N_{tags,TCHEL}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets9",       "multiTCHEM",  "N_{tags,TCHEM}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets9",       "pt",          "p_{T,jet} [GeV]",  "N_{jets} / bin", 0.0, -1,0,0,5);
    PrintPlotAll("analyzeJets9",       "eta",         "#eta_{jet}",       "N_{jets} / bin", 0.0, -1,0,0,2);
    PrintPlotAll("analyzeJets9",       "ht",          "H_{T, all jets} [GeV]", "N_{events} / bin", 0, -1, 0, kTRUE, 5);

    PrintPlotAll("analyzeMuons9",       "multi",      "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons9",       "pt",         "p_{T,#mu} [GeV]",  "N_{#mu} / bin",  0.0, -1,0,0,5);
    PrintPlotAll("analyzeMuons9",       "eta",        "#eta_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,2);

    PrintPlotAll("analyzeElecs9",       "multi",      "N_{e}",           "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeElecs9",       "pt",         "p_{T,e} [GeV]",   "N_{e} / bin",     0.0, -1,0,0,5);
    PrintPlotAll("analyzeElecs9",       "eta",        "#eta_{e}",        "N_{e} / bin",     0.0, -1,0,0,2);

    PrintPlotAll("analyzeKinSolution9", "kin_TopPt",      "p_{T,t} [GeV]",   "N_{events} / bin",  0.0, -1,0,0,4);
    PrintPlotAll("analyzeKinSolution9", "kin_TopMass",    "M_{t} [GeV]",     "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution9", "kin_TopRapidity",      "y_{t}",       "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution9", "kin_TtBarPt",      "p_{T,t#bar{t}} [GeV]", "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution9", "kin_TtBarMass",            "M_{t#bar{t}} [GeV]", "N_{events} / bin",  0.0, -1,0,0,4);
    PrintPlotAll("analyzeKinSolution9", "kin_TtBarRapidity",    "y_{t#bar{t}}", "N_{events} / bin",  0.0, -1,0,0,2);

    PrintPlot("analyzeLeptonPair9", "DimassRC_MM", kMM,       "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair9", "DimassRC_MM", kCOMBINED, "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair9", "DimassRC_ME", kEM,       "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair9", "DimassRC_ME", kCOMBINED, "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair9", "DimassRC_EE", kEE,       "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair9", "DimassRC_EE", kCOMBINED, "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);

    PrintPlot("analyzeLeptonPair9SS", "DimassWC_MM", kCOMBINED, "M_{#mu^{#pm}#mu^{#pm}} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair9SS", "DimassWC_ME", kCOMBINED, "M_{e^{#pm}#mu^{#pm}} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair9SS", "DimassWC_EE", kCOMBINED, "M_{e^{#pm}e^{#pm}} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);

    PrintPlotAll("analyzeVertex9", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);

    PrintDyPlot(9, kMM,     0.0, -1., 0, 0, 2);
    PrintDyPlot(9, kEM,     0.0, -1., 0, 0, 2);
    PrintDyPlot(9, kEE,     0.0, -1., 0, 0, 2);
    PrintDyPlot(9, kCOMBINED, 0.0, -1., 0, 0, 2);

//********************************************************************************************
//********************************************************************************************
//********************************************************************************************
//********************************************************************************************

    PrintPlotAll("analyzeJets3SS",       "multi",       "N_{jets}",         "N_{events} / bin", 1.0, -1,0,1);
    PrintPlotAll("analyzeJets3SS",       "multiTCHEM",  "N_{tags,TCHEL}",   "N_{events} / bin", 1.0, -1,0,1);
    PrintPlotAll("analyzeJets3SS",       "pt",        "p_{T,jet} [GeV]",  "N_{jets} / bin", 0.0, -1,0,0,5);
    PrintPlotAll("analyzeJets3SS",       "eta",       "#eta_{jet}",       "N_{jets} / bin", 0.0, -1,0,0,2);
    PrintPlotAll("analyzeJets3SS",       "ht",         "H_{T, all jets} [GeV]", "N_{events} / bin", 0, -1, 0, kTRUE, 5);
    PrintPlotAll("analyzeVertex3SS", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);

    PrintPlotAll("analyzeMuons3SS",       "multi",     "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons3SS",       "pt",        "p_{T,#mu} [GeV]",  "N_{#mu} / bin",  0.0, -1,0,0,5);
    PrintPlotAll("analyzeMuons3SS",       "eta",       "#eta_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,2);
    PrintPlotAll("analyzeMuons3SS",       "pf_iso",    "pf_iso_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,4);
    PrintPlotAll("analyzeMuons3SS",       "iso_comb2", "pf_iso_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,4);
    PrintPlotAll("analyzeMuons3SS",       "jet_dist",  "jet_dist",      "N_{#mu} / bin",   0.0, -1,0,0,4);

    PrintPlotAll("analyzeElecs3SS",       "multi",    "N_{e}",           "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeElecs3SS",       "pt",       "p_{T,e} [GeV]",   "N_{e} / bin",     0.0, -1,0,0,5);
    PrintPlotAll("analyzeElecs3SS",       "eta",      "#eta_{e}",        "N_{e} / bin",     0.0, -1,0,0,2);

    PrintPlotAll("analyzeElecs3SS", "jet_dist", "jet distance", "N", 0, 0, 0, 0, 5);
    PrintPlotAll("analyzeElecs3SS", "convDcot", "convDcot", "N", 0, 0, 0, 0, 5);
    PrintPlotAll("analyzeElecs3SS", "convDist", "convDist", "N", 0, 0, 0, 0, 5);
    PrintPlotAll("analyzeElecs3SS", "electronmap", "electronmap", "N");

    PrintPlotAll("analyzeElecs4SS", "convDcot", "convDcot", "N", 0, 0, 0, 0, 5);
    PrintPlotAll("analyzeElecs4SS", "convDist", "convDist", "N", 0, 0, 0, 0, 5);
    PrintPlotAll("analyzeElecs4SS", "electronmap", "electronmap", "N");
    PrintPlotAll("analyzeVertex4SS", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);

    PrintPlot("analyzeLeptonPair3SS", "D_eta_elecsWC", kEE, "eta1-eta2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair3SS", "D_eta_muonsWC", kMM, "eta1-eta2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair3SS", "D_phi_elecsWC", kEE, "phi1-phi2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair3SS", "D_phi_muonsWC", kMM, "phi1-phi2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);

    PrintPlot("analyzeLeptonPair3SS", "DimassWC_MM", kMM,       "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair3SS", "DimassWC_MM", kCOMBINED, "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair3SS", "DimassWC_ME", kEM,       "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair3SS", "DimassWC_ME", kCOMBINED, "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair3SS", "DimassWC_EE", kEE,       "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair3SS", "DimassWC_EE", kCOMBINED, "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);

    PrintPlotAll("analyzeMuons4SS",       "multi",     "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlot("analyzeLeptonPair4SS", "D_eta_elecsWC", kEE, "eta1-eta2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair4SS", "D_eta_muonsWC", kMM, "eta1-eta2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair4SS", "D_phi_elecsWC", kEE, "phi1-phi2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair4SS", "D_phi_muonsWC", kMM, "phi1-phi2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);

    PrintPlotAll("analyzeMuons5SS",       "multi",     "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);

    // STEP 6
    PrintPlotAll("analyzeJets6SS",       "multi",        "N_{jets}",         "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets6SS",       "multiTCHEL",   "N_{tags,TCHEL}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets6SS",       "multiTCHEM",   "N_{tags,TCHEM}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets6SS",       "multiSSVHEM",  "N_{tags,SSVHEM}",  "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets6SS",       "pt",           "p_{T,jet} [GeV]",  "N_{jets} / bin", 0.0, -1,0,0,5);
    PrintPlotAll("analyzeJets6SS",       "eta",          "#eta_{jet}",       "N_{jets} / bin", 0.0, -1,0,0,2);
    PrintPlotAll("analyzeJets6SS",       "ht",           "H_{T, all jets} [GeV]", "N_{events} / bin", 0, -1, 0, kTRUE, 5);

    PrintPlotAll("analyzeMuons6SS",       "multi",       "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons6SS",       "pt",          "p_{T,#mu} [GeV]",  "N_{#mu} / bin",  0.0, -1,0,0,5);
    PrintPlotAll("analyzeMuons6SS",       "eta",         "#eta_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,2);
    
    PrintPlotAll("analyzeElecs6SS",       "multi",       "N_{e}",           "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeElecs6SS",       "pt",          "p_{T,e} [GeV]",   "N_{e} / bin",     0.0, -1,0,0,5);
    PrintPlotAll("analyzeElecs6SS",       "eta",         "#eta_{e}",        "N_{e} / bin",     0.0, -1,0,0,2);

    PrintPlotAll("analyzeMet6SS", "et", "MET", "N/bin", 0, -1, 0, 0, 5);

    PrintPlot("analyzeLeptonPair6SS", "D_eta_elecsWC", kEE, "eta1-eta2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair6SS", "D_eta_muonsWC", kMM, "eta1-eta2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair6SS", "D_phi_elecsWC", kEE, "phi1-phi2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);
    PrintPlot("analyzeLeptonPair6SS", "D_phi_muonsWC", kMM, "phi1-phi2", "N_{events} / bin", -1, -1, kFALSE, kFALSE, 1);

    PrintPlot("analyzeLeptonPair6SS", "DimassWC_MM", kMM,       "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair6SS", "DimassWC_MM", kCOMBINED, "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair6SS", "DimassWC_ME", kEM,       "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair6SS", "DimassWC_ME", kCOMBINED, "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair6SS", "DimassWC_EE", kEE,       "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair6SS", "DimassWC_EE", kCOMBINED, "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);

    PrintPlotAll("analyzeVertex6SS", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);

    // STEP 7
    PrintPlotAll("analyzeJets7SS",       "multi",         "N_{jets}",         "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets7SS",       "multiTCHEL",  "N_{tags,TCHEL}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets7SS",       "multiTCHEM",  "N_{tags,TCHEM}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets7SS",       "pt",          "p_{T,jet} [GeV]",  "N_{jets} / bin", 0.0, -1,0,0,5);
    PrintPlotAll("analyzeJets7SS",       "eta",         "#eta_{jet}",       "N_{jets} / bin", 0.0, -1,0,0,2);
    PrintPlotAll("analyzeJets7SS",       "ht",          "H_{T, all jets} [GeV]", "N_{events} / bin", 0, -1, 0, kTRUE, 5);

    PrintPlotAll("analyzeMuons7SS",       "multi",      "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons7SS",       "pt",         "p_{T,#mu} [GeV]",  "N_{#mu} / bin",  0.0, -1,0,0,5);
    PrintPlotAll("analyzeMuons7SS",       "eta",        "#eta_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,2);


    PrintPlotAll("analyzeElecs7SS",       "multi",      "N_{e}",           "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeElecs7SS",       "pt",         "p_{T,e} [GeV]",   "N_{e} / bin",     0.0, -1,0,0,5);
    PrintPlotAll("analyzeElecs7SS",       "eta",        "#eta_{e}",        "N_{e} / bin",     0.0, -1,0,0,2);

    PrintPlotAll("analyzeKinSolution7SS", "kin_TopPt",         "p_{T,t} [GeV]",   "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeKinSolution7SS", "kin_TopMass",       "M_{t} [GeV]",     "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeKinSolution7SS", "kin_TopRapidity",   "y_{t}",       "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeKinSolution7SS", "kin_TtBarPt",       "p_{T,t#bar{t}} [GeV]", "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeKinSolution7SS", "kin_TtBarMass",     "M_{t#bar{t}} [GeV]", "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeKinSolution7SS", "kin_TtBarRapidity", "y_{t#bar{t}}", "N_{events} / bin",  0.0, -1,0,0);

    PrintPlot("analyzeLeptonPair7SS", "DimassWC_MM", kMM,       "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair7SS", "DimassWC_MM", kCOMBINED, "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair7SS", "DimassWC_ME", kEM,       "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair7SS", "DimassWC_ME", kCOMBINED, "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair7SS", "DimassWC_EE", kEE,       "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair7SS", "DimassWC_EE", kCOMBINED, "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);


    PrintPlotAll("analyzeVertex7SS", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);

    // STEP 8
    PrintPlotAll("analyzeJets8SS",       "multi",       "N_{jets}",         "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets8SS",       "multiTCHEL",  "N_{tags,TCHEL}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets8SS",       "multiTCHEM",  "N_{tags,TCHEM}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets8SS",       "pt",          "p_{T,jet} [GeV]",  "N_{jets} / bin", 0.0, -1,0,0,5);
    PrintPlotAll("analyzeJets8SS",       "eta",         "#eta_{jet}",       "N_{jets} / bin", 0.0, -1,0,0,2);
    PrintPlotAll("analyzeJets8SS",       "ht",          "H_{T, all jets} [GeV]", "N_{events} / bin", 0, -1, 0, kTRUE, 5);

    PrintPlotAll("analyzeMuons8SS",       "multi",      "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons8SS",       "pt",         "p_{T,#mu} [GeV]",  "N_{#mu} / bin",  0.0, -1,0,0,5);
    PrintPlotAll("analyzeMuons8SS",       "eta",        "#eta_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,2);


    PrintPlotAll("analyzeElecs8SS",       "multi",      "N_{e}",           "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeElecs8SS",       "pt",         "p_{T,e} [GeV]",   "N_{e} / bin",     0.0, -1,0,0,5);
    PrintPlotAll("analyzeElecs8SS",       "eta",        "#eta_{e}",        "N_{e} / bin",     0.0, -1,0,0,2);

    PrintPlotAll("analyzeKinSolution8SS", "kin_TopPt",      "p_{T,t} [GeV]",   "N_{events} / bin",  0.0, -1,0,0,4);
    PrintPlotAll("analyzeKinSolution8SS", "kin_TopMass",    "M_{t} [GeV]",     "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeKinSolution8SS", "kin_TopRapidity",      "y_{t}",       "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution8SS", "kin_TtBarPt",      "p_{T,t#bar{t}} [GeV]", "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution8SS", "kin_TtBarMass",            "M_{t#bar{t}} [GeV]", "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution8SS", "kin_TtBarRapidity",    "y_{t#bar{t}}", "N_{events} / bin",  0.0, -1,0,0,2);

    PrintPlot("analyzeLeptonPair8SS", "DimassWC_MM", kMM,       "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair8SS", "DimassWC_MM", kCOMBINED, "M_{#mu#mu} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair8SS", "DimassWC_ME", kEM,       "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair8SS", "DimassWC_ME", kCOMBINED, "M_{e#mu} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair8SS", "DimassWC_EE", kEE,       "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair8SS", "DimassWC_EE", kCOMBINED, "M_{ee} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);


    PrintPlotAll("analyzeVertex8SS", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);

    PrintPlotAll("analyzeJets9SS",       "multi",       "N_{jets}",         "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets9SS",       "multiTCHEL",  "N_{tags,TCHEL}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets9SS",       "multiTCHEM",  "N_{tags,TCHEM}",   "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeJets9SS",       "pt",          "p_{T,jet} [GeV]",  "N_{jets} / bin", 0.0, -1,0,0,5);
    PrintPlotAll("analyzeJets9SS",       "eta",         "#eta_{jet}",       "N_{jets} / bin", 0.0, -1,0,0,2);
    PrintPlotAll("analyzeJets9SS",       "ht",          "H_{T, all jets} [GeV]", "N_{events} / bin", 0, -1, 0, kTRUE, 5);

    PrintPlotAll("analyzeMuons9SS",       "multi",      "N_{muons}",        "N_{events} / bin", 0.0, -1,0,0);
    PrintPlotAll("analyzeMuons9SS",       "pt",         "p_{T,#mu} [GeV]",  "N_{#mu} / bin",  0.0, -1,0,0,5);
    PrintPlotAll("analyzeMuons9SS",       "eta",        "#eta_{#mu}",      "N_{#mu} / bin",   0.0, -1,0,0,2);

    PrintPlotAll("analyzeElecs9SS",       "multi",      "N_{e}",           "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeElecs9SS",       "pt",         "p_{T,e} [GeV]",   "N_{e} / bin",     0.0, -1,0,0,5);
    PrintPlotAll("analyzeElecs9SS",       "eta",        "#eta_{e}",        "N_{e} / bin",     0.0, -1,0,0,2);

    PrintPlotAll("analyzeKinSolution9SS", "kin_TopPt",      "p_{T,t} [GeV]",   "N_{events} / bin",  0.0, -1,0,0,4);
    PrintPlotAll("analyzeKinSolution9SS", "kin_TopMass",    "M_{t} [GeV]",     "N_{events} / bin",  0.0, -1,0,0);
    PrintPlotAll("analyzeKinSolution9SS", "kin_TopRapidity",      "y_{t}",       "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution9SS", "kin_TtBarPt",      "p_{T,t#bar{t}} [GeV]", "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution9SS", "kin_TtBarMass",            "M_{t#bar{t}} [GeV]", "N_{events} / bin",  0.0, -1,0,0,2);
    PrintPlotAll("analyzeKinSolution9SS", "kin_TtBarRapidity",    "y_{t#bar{t}}", "N_{events} / bin",  0.0, -1,0,0,2);

    PrintPlot("analyzeLeptonPair9SS", "DimassWC_MM", kCOMBINED, "M_{#mu^{#pm}#mu^{#pm}} [GeV]", "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair9SS", "DimassWC_ME", kCOMBINED, "M_{e^{#pm}#mu^{#pm}} [GeV]",   "N_{events} / bin", 0.05,-1,0,1,2);
    PrintPlot("analyzeLeptonPair9SS", "DimassWC_EE", kCOMBINED, "M_{e^{#pm}e^{#pm}} [GeV]",     "N_{events} / bin", 0.05,-1,0,1,2);

    PrintPlotAll("analyzeVertex9SS", "multi", "N_{vtx}", "N_{events} / bin", 0, -1, kFALSE, kFALSE);
}



void CreateOutputDirectories() {
    mkdir(outpath.Data(), 0755);
    mkdir(outpath.Copy().Append("btagging").Data(), 0755);
    for (int channel = 0; channel < 4; ++channel)
        mkdir(outpath.Copy().Append(channelName[channel]).Data(), 0755);
}



void PrintCutflowTable() {
    TH1* hists[Nfiles];
    const char* stepname[] = {"", "", "", "", "dilepton", "", "2 jets", "met", "tchel", "tchem", "kinfit"};
    //int steps[] = {4, 6, 7, 8, 9, 10, 0};
    int steps[] = {4, 6, 7, 8, 10, 0};
    int sam[] = {kSIG, kTTBG, kTW, kVV, kW, kDYT, kDYEM, kQCD, kDATA, -1};
    
    for ( int channel = kMM; channel <= kEE; ++channel) {
        std::cout << std::endl << "Cutflow for " << std::setw(4) << channelName[channel] << "\t";
        for (int step = 0; steps[step]; ++step) { std::cout << std::setw(15) << stepname[steps[step]] << "\t";  }
        std::cout << std::endl;
        double mcsum[] = {0,0,0,0,0,0};
        for (int sample = 0; sam[sample] != -1; ++sample) {
            std::cout << std::setw(25) << sampleNameTeX[sam[sample]] << " & \t";
            for (Long_t step = 0; steps[step]; ++step) {
                TString histoname("multi");
                stringstream ss; ss << steps[step];
                TString module("analyzeElecs");
                module.Append(ss.str());
                if (steps[step] == 10) {
                    //for kin fit, there is no filter, thus read from kin fit histogram
                    module = kinAnalyzer;
                    histoname = "kin_TopRapidity";
                }

                GetCloneHistArray(module.Copy().Append("/"), histoname, channel, hists);

                Double_t zMuCorr = 1.;
                Double_t zElCorr = 1.;

                if (doDYcorrection) {
		  if (step == 7) {		
                    zMuCorr = zMuNorm7;
                    zElCorr = zElNorm7;
		  } else if (step == 8) {
                    zMuCorr = zMuNorm8;
                    zElCorr = zElNorm8;	
		  } else if (step == 9) {
                    zMuCorr = zMuNorm9;
                    zElCorr = zElNorm9;	
		  } 	     
                }

                SetWeights(hists, zElCorr, zMuCorr);
                TH1* mergedhists[Nplots];
                MergeHistArray(hists, mergedhists);

                if (sam[sample] != kDATA) {
                    mcsum[step] += mergedhists[sam[sample]]->Integral();
                    std::cout << std::setprecision(1)
                              << mergedhists[sam[sample]]->Integral() << (steps[step+1] ? "\t&\t" : "\t\\\\");
                } else {
                    std::cout << std::setprecision(1)
                              << mergedhists[sam[sample]]->GetEntries() << (steps[step+1] ? "\t&\t" : "\t\\\\");
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::setw(25) << "Sum MC" << " & \t";
        for (int step = 0; steps[step]; ++step) {
            std::cout << std::setprecision(1) << mcsum[step] << (steps[step+1] ? "\t&\t" : "\t\\\\");
        }
        std::cout << std::endl;
    }

}



// save a background-subtracted data hist and a signal MC hist with the gerated vs the reconstructed quantity
void SaveUnfoldingHists(const char* particle, const char* quantity, Int_t channel, const Double_t bins[], const Int_t nbins, 
                        const Double_t finebins[], const Int_t nfinebins) {
    // get histograms of reconstructed quantity and generated signal
    TString plotStr("");
    if (strcmp(particle,"Leptons")==0) {
        plotStr.Append("Lep");
    } else if (strcmp(particle,"Jets")==0) {
        plotStr.Append("B");
    } else if (strcmp(particle,"TopQuarks")==0) {
        plotStr.Append("Top");
    } else {
        plotStr.Append(particle);
    }
    plotStr.Append(quantity);

    TH1* hists[Nfiles];  // for reconstructed quantities
    TH1* genHist;        // genHist needed to calculate the number of unreconstructed events
    TH1* genRec2DHist;   // reconstructed vs generated signal properties. needed  for correlation plot
    TString genTopEvent("analyzeVisibleGenTopEvent/");
    if (channel==kMM) {
        GetCloneHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kMM, hists);

        GetCloneHist(kinAnalyzer, TString("2D_").Append(plotStr), kMM, 1, genRec2DHist);
        AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kMM, 2, genRec2DHist);

        GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
        AddHist(     genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);
    } else if (channel==kEM) {
        GetCloneHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kEM, hists);

        GetCloneHist(kinAnalyzer, TString("2D_").Append(plotStr), kEM, 1, genRec2DHist);
        AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kEM, 2, genRec2DHist);

        GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
        AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
    } else if (channel==kEE) {
        GetCloneHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kEE, hists);

        GetCloneHist(kinAnalyzer, TString("2D_").Append(plotStr), kEE, 1, genRec2DHist);
        AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kEE, 2, genRec2DHist);

        GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
        AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
    } else if (channel==kCOMBINED) {
        GetCloneHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kMM, hists);
        AddHistArray(     kinAnalyzer, TString("kin_").Append(plotStr), kEM, hists);
        AddHistArray(     kinAnalyzer, TString("kin_").Append(plotStr), kEE, hists);

        GetCloneHist(kinAnalyzer, TString("2D_").Append(plotStr), kMM, 1, genRec2DHist);
        AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kMM, 2, genRec2DHist);
        AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kEM, 1, genRec2DHist);
        AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kEM, 2, genRec2DHist);
        AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kEE, 1, genRec2DHist);
        AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kEE, 2, genRec2DHist);

        GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
        AddHist(     genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);
        AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
        AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
        AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
        AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
    } else {
        cout << "ERROR in SaveUnfoldingHists: index " << channel << " for channel is out of range!" << endl;
        return;
    }

    // if particle = Leptons, Jets or TopQuarks then the histogram of the antiparticle is added to that of the particle
    if (strcmp(particle,"Leptons")==0 || strcmp(particle,"Jets")==0 || strcmp(particle,"TopQuarks")==0) {

        plotStr.Clear();
        plotStr = "";

        if (strcmp(particle,"Leptons")==0) {
            plotStr.Append("LepBar");
        } else if (strcmp(particle,"Jets")==0) {
            plotStr.Append("BBar");
        } else if (strcmp(particle,"TopQuarks")==0) {
            plotStr.Append("TopBar");
        }
        plotStr.Append(quantity);

        if (channel==kMM) {
            AddHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kMM, hists);

            AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kMM, 1, genRec2DHist);
            AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kMM, 2, genRec2DHist);

            AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
            AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);
        } else if (channel==kEM) {
            AddHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kEM, hists);

            AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEM, 1, genRec2DHist);
            AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEM, 2, genRec2DHist);

            AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
            AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
        } else if (channel==kEE) {
            AddHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kEE, hists);

            AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEE, 1, genRec2DHist);
            AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEE, 2, genRec2DHist);

            AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
            AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
        } else if (channel==kCOMBINED) {
            AddHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kMM, hists);
            AddHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kEM, hists);
            AddHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kEE, hists);

            AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kMM, 1, genRec2DHist);
            AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kMM, 2, genRec2DHist);
            AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEM, 1, genRec2DHist);
            AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEM, 2, genRec2DHist);
            AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEE, 1, genRec2DHist);
            AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEE, 2, genRec2DHist);

            AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
            AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);
            AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
            AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
            AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
            AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
        }
    }

    // BG SUBTRACTED DATA HIST
    Double_t zElCorr = 1.;
    Double_t zMuCorr = 1.;

    SetWeights(hists, zElCorr, zMuCorr);

    // subtract background from data
    for(size_t i=3; i<Nplots; ++i){
      hists[0]->Add(hists[i],-1.);
    }

    if(strcmp(quantity,"Eta")==0 || strcmp(quantity,"Rapidity")==0){
      // book new hist with additional bin for overflow
      // calculate bins
      Double_t widthExtraBin = finebins[nfinebins]-finebins[nfinebins-1];
      Double_t finebins2[nfinebins+3];
      for(Int_t i=0; i<=nfinebins; ++i){
	finebins2[i+1]=finebins[i];   
      }
      finebins2[0]           = finebins[0]        -widthExtraBin;
      finebins2[nfinebins+2] = finebins[nfinebins]+widthExtraBin;

      // name of data hist
      TString dataStr(channelName[channel]);
      dataStr.Append("_dataHist_");
      dataStr.Append(particle);
      dataStr.Append("_");
      dataStr.Append(quantity);

      // book hist with extra bin
      TH1D* dataHist = new TH1D(dataStr, dataStr, nfinebins+2, finebins2); 

      TH1* oldHist = hists[0]->Rebin(nfinebins, "oldHist", finebins);

      // fill
      for(Int_t i=0; i<=nfinebins+1; ++i){
	if(oldHist->GetBinContent(i)>0.)
          dataHist->SetBinContent(i+1, oldHist->GetBinContent(i));
	else      
          dataHist->SetBinContent(i+1, 0.); // remove bins where content is negative after BG subtraction      
      }  

      // book new rebinned 2-dimensional hist
      TString mcStr(channelName[channel]);
      mcStr.Append("_2dHist_");
      mcStr.Append(particle);
      mcStr.Append("_");
      mcStr.Append(quantity);

      // 2D MC HIST
      TH2D* mcHist = new TH2D(mcStr, mcStr, nfinebins+2, finebins2, nbins, bins);
      
      // fill main entries (swapped axes)   
      for(Int_t j=1; j<=mcHist->GetNbinsY()+1; ++j){
	for(Int_t i=1; i<=mcHist->GetNbinsX(); ++i){
          Int_t x1 = genRec2DHist->GetYaxis()->FindBin(finebins2[i-1]);
          Int_t x2 = genRec2DHist->GetYaxis()->FindBin(finebins2[i]-1);
	  if(i==1)
	    x1 = 0;
	  if(i==mcHist->GetNbinsX())
	    x2 = genRec2DHist->GetNbinsY()+1;

          Int_t y1 = genRec2DHist->GetXaxis()->FindBin(bins[j-1]);
          Int_t y2 = genRec2DHist->GetXaxis()->FindBin(bins[j]-1);
	  if(j==1)
	    y1 = 0;
	  if(j==mcHist->GetNbinsY()+1)
	    y2 = genRec2DHist->GetNbinsX()+1;

	  Double_t n = ((TH2D*)genRec2DHist)->Integral(y1, y2, x1, x2);
          mcHist->SetBinContent(i, j, n);
	}
      }

      // calculate and fill non-reconstructed events
      for(Int_t j=1; j<=mcHist->GetNbinsY(); ++j){            
	// underflow
	Int_t x1 = genHist->GetXaxis()->FindBin(bins[j-1]);
	Int_t x2 = genHist->GetXaxis()->FindBin(bins[j])-1;

	Double_t ngen0 = genHist->Integral(x1, x2);

	Int_t y1 = mcHist->GetYaxis()->FindBin(bins[j-1]);
	Int_t y2 = mcHist->GetYaxis()->FindBin(bins[j])-1;

	Double_t ngen1 = mcHist->Integral(0, mcHist->GetNbinsX(),y1,y2);

	Double_t nnonrec = ngen0 - ngen1;

	mcHist->SetBinContent(0, j, nnonrec);     		     	 
      }
      
//       cout << "UNFOLDING: " << particle << quantity << endl; 
// 
//       // check finebins
//       cout << "Old" << endl;
//       for(Int_t i=0; i<=oldHist->GetNbinsX()+1; ++i){
//         cout << oldHist->GetBinContent(i) << endl;;
//       }        
//       cout << endl;
//       cout << "New" << endl;
//       for(Int_t i=0; i<=dataHist->GetNbinsX()+1; ++i){
//         cout << dataHist->GetBinContent(i) << endl;;
//       }    
//       cout << endl;
// 
// 
//       // check hist
//       for(Int_t j=mcHist->GetNbinsY()+1; j>=0; --j){
//         for(Int_t i=0; i<=mcHist->GetNbinsX()+1; ++i){
//           cout << setw(9) << mcHist->GetBinContent(i,j);
//         }
//         cout << endl;
//       }
//       cout << endl;
//       cout << endl;


      unfoldHistogramList.Add(dataHist);
      unfoldHistogramList.Add(mcHist);                  
    }else{
      // book new hist with additional bin for overflow
      // calculate bins
      Double_t widthExtraBin = finebins[nfinebins]-finebins[nfinebins-1];
      Double_t finebins2[nfinebins+2];
      for(Int_t i=0; i<=nfinebins; ++i){
	finebins2[i]=finebins[i];   
      }
      finebins2[nfinebins+1] = finebins[nfinebins]+widthExtraBin;

      // name of data hist
      TString dataStr(channelName[channel]);
      dataStr.Append("_dataHist_");
      dataStr.Append(particle);
      dataStr.Append("_");
      dataStr.Append(quantity);

      // book hist with extra bin
      TH1D* dataHist = new TH1D(dataStr, dataStr, nfinebins+1, finebins2); 

      TH1* oldHist = hists[0]->Rebin(nfinebins, "oldHist", finebins);

      // fill
      for(Int_t i=0; i<=nfinebins; ++i){
	if(oldHist->GetBinContent(i+1)>0.)
          dataHist->SetBinContent(i+1, oldHist->GetBinContent(i+1));
	else      
          dataHist->SetBinContent(i+1, 0.); // remove bins where content is negative after BG subtraction      
      }  

      // book new rebinned 2-dimensional hist
      TString mcStr(channelName[channel]);
      mcStr.Append("_2dHist_");
      mcStr.Append(particle);
      mcStr.Append("_");
      mcStr.Append(quantity);

      // 2D MC HIST
      TH2D* mcHist = new TH2D(mcStr, mcStr, nfinebins+1, finebins2, nbins, bins);

      // fill main entries (swapped axes)   
      for(Int_t j=1; j<=mcHist->GetNbinsY()+1; ++j){
	for(Int_t i=1; i<=mcHist->GetNbinsX(); ++i){
          Int_t x1 = genRec2DHist->GetYaxis()->FindBin(finebins2[i-1]);
          Int_t x2 = genRec2DHist->GetYaxis()->FindBin(finebins2[i]-1);
	  if(i==mcHist->GetNbinsX())
	    x2 = genRec2DHist->GetNbinsY()+1;

          Int_t y1 = genRec2DHist->GetXaxis()->FindBin(bins[j-1]);   
          Int_t y2 = genRec2DHist->GetXaxis()->FindBin(bins[j]-1);
	  if(j==mcHist->GetNbinsY()+1)
	    y2 = genRec2DHist->GetNbinsX()+1;

	  Double_t n = ((TH2D*)genRec2DHist)->Integral(y1, y2, x1, x2);
          mcHist->SetBinContent(i, j, n);	
	}
      }

      // calculate and fill non-reconstructed events
      for(Int_t j=1; j<=mcHist->GetNbinsY(); ++j){            
	// underflow
	Int_t x1 = genHist->GetXaxis()->FindBin(bins[j-1]);
	Int_t x2 = genHist->GetXaxis()->FindBin(bins[j])-1;

	Double_t ngen0 = genHist->Integral(x1, x2);

	Int_t y1 = mcHist->GetYaxis()->FindBin(bins[j-1]);
	Int_t y2 = mcHist->GetYaxis()->FindBin(bins[j])-1;

	Double_t ngen1 = mcHist->Integral(0, mcHist->GetNbinsX(),y1,y2);

	Double_t nnonrec = ngen0 - ngen1;

	mcHist->SetBinContent(0, j, nnonrec);     		     	 
      }
      
//       cout << "UNFOLDING: " << particle << quantity << endl; 
// 
//       // check finebins
//       cout << "Old" << endl;
//       for(Int_t i=0; i<=oldHist->GetNbinsX()+1; ++i){
//         cout << oldHist->GetBinContent(i) << endl;;
//       }        
//       cout << endl;
//       cout << "New" << endl;
//       for(Int_t i=0; i<=dataHist->GetNbinsX()+1; ++i){
//         cout << dataHist->GetBinContent(i) << endl;;
//       }    
//       cout << endl;
// 
// 
//       // check hist
//       for(Int_t j=mcHist->GetNbinsY()+1; j>=0; --j){
//         for(Int_t i=0; i<=mcHist->GetNbinsX()+1; ++i){
//           cout << setw(10) << mcHist->GetBinContent(i,j);
//         }
//         cout << endl;
//       }
//       cout << endl;
//       cout << endl;


      unfoldHistogramList.Add(dataHist);
      unfoldHistogramList.Add(mcHist);  
    }

}



TFile *incompleteSystematics(TFile *oldFile, TFile *newFile) {
    if (newFile && !newFile->IsZombie()) {
        return newFile;
    } else {
        std::cout << "ERROR!!! INCOMPLETE SYSTEMATICS!!! USING DEFAULT FILE!!!\n";
        return oldFile;
    }
}



// calculate the inclusive cross section for a certain channel and selection step
void CalculateCrossSection(Int_t channel, const char* selection, Double_t& crossS, Double_t& statErr, Double_t& systErrUp, Double_t& systErrDown) {
    cout.precision(3);

    // determine input histograms from selected selection
    TString selModule("analyzeKinSolution7/"); // name of the analyzer module which contains the plot from which selected events are extracted
    TString genModule("analyzeGenTopEvent/");  // name of the analyzer module which contains the plot from which generated events are extracted
    TString selPlot("kin_TopMass");            // name of the plot from which selected events are extracted
    TString genPlot("gen_TopMass");            // name of the plot from which generated events are extracted
    
    Double_t btagSF = 1.;
    Double_t zMuCorr = 1.;
    Double_t zElCorr = 1.;

    if (strcmp(selection,"DEFAULT")==0) {
	zMuCorr = zMuNorm7;
	zElCorr = zElNorm7;
    } else if (strcmp(selection,"TCHEL")==0) {
        selModule = "analyzeKinSolution8/";
	btagSF = btagSFMap["TCHEL"];
	zMuCorr = zMuNorm8;
	zElCorr = zElNorm8;		
    } else if (strcmp(selection,"KINTCHEL")==0) {
        selModule = "analyzeKinSolution9/";
	btagSF = btagSFMap["TCHEL"];
	zMuCorr = zMuNorm9;
	zElCorr = zElNorm9;		
    } else {
        cout << "ERROR in Calculate Cross Section: unknown selection specified: " << selection << endl;
    }

    // variables needed for all cross sections
    Double_t eff    = 0.; // MC efficiency for signal selection
    Double_t nGen   = 0.; // number of generated signal events
    Double_t nSel   = 0.; // number of selected events in signal MC
    Double_t nBg    = 0.; // amount of background
    Double_t errBg  = 0.; // error on the background
    Double_t nSig   = 0.; // number of signal events
    Double_t nTToth = 0.; // number of ttbar other bg
    Double_t nTW    = 0.; // number of single top background events
    Double_t nVV    = 0.; // number of diboson background events
    Double_t nDYtt  = 0.; // number of DY background in tautau channel
    Double_t nDYmm  = 0.; // number of DY background in mumu channel
    Double_t nDYee  = 0.; // number of DY background in ee channel
    Double_t nW     = 0.; // number of W background events
    Double_t nQCD   = 0.; // number of QCD background events

    if ( !(channel==kMM || channel==kEM || channel==kEE || channel==kCOMBINED) ) {
      cout << "ERROR in CalculateCrossSection: channel " << channel << " is out of range!" << endl;
      return;
    }

    Double_t entries[Nfiles]; //here entries[0] is used for bg sum
    for (size_t i=0; i<Nfiles; ++i) {
      entries[i] = 0;
    }

    TH1* countHists[Nfiles];
    TH1* genTopHist;
    if (channel==kMM || channel==kEM || channel==kEE) {
        GetCloneHistArray(selModule.Copy(), selPlot, channel, countHists);

	nSel += triggerSF[channel]*leptonSF[channel]*countHists[1]->Integral();
        nSel += triggerSF[channel]*leptonSF[channel]*countHists[2]->Integral();

        GetCloneHist(genModule.Copy(), genPlot, channel, 1, genTopHist);
        AddHist(genModule.Copy(), genPlot, channel, 2, genTopHist);
    } else if (channel==kCOMBINED) {

        GetCloneHistArray(selModule.Copy(), selPlot, kMM, countHists);
	nSel += (triggerSF[kMM]*leptonSF[kMM]*(countHists[1]->Integral()));
        nSel += (triggerSF[kMM]*leptonSF[kMM]*(countHists[2]->Integral()));

        GetCloneHistArray(selModule.Copy(), selPlot, kEM, countHists); // overwrite counthists with emu
	nSel += (triggerSF[kEM]*leptonSF[kEM]*(countHists[1]->Integral()));
        nSel += (triggerSF[kEM]*leptonSF[kEM]*(countHists[2]->Integral()));

        GetCloneHistArray(selModule.Copy(), selPlot, kEE, countHists); // overwrite counthists with ee
	nSel += (triggerSF[kEE]*leptonSF[kEE]*(countHists[1]->Integral()));
        nSel += (triggerSF[kEE]*leptonSF[kEE]*(countHists[2]->Integral()));

        AddHistArray(selModule.Copy(), selPlot, kEM, countHists); // now emu and mumu are added to ee
        AddHistArray(selModule.Copy(), selPlot, kMM, countHists); // so the combined hist is obtained

        GetCloneHist(genModule.Copy(), genPlot, kMM, 1, genTopHist);
        AddHist(genModule.Copy(), genPlot, kMM, 2, genTopHist);
        AddHist(genModule.Copy(), genPlot, kEM, 1, genTopHist);
        AddHist(genModule.Copy(), genPlot, kEM, 2, genTopHist);
        AddHist(genModule.Copy(), genPlot, kEE, 1, genTopHist);
        AddHist(genModule.Copy(), genPlot, kEE, 2, genTopHist);
    } else {
        cout << "ERROR in CalculateCrossSection: index " << channel << " for channel is out of range!" << endl;
        return;
    }

    nGen += genTopHist ->Integral( 0,genTopHist->GetXaxis()->GetNbins()+1);

    // calculate MC efficiency for mumu and mumu via tau
    eff = btagSF*nSel/nGen;

    SetWeights(countHists);

    cout << endl << endl;
    cout << "    CROSS SECTION" << endl;
    cout << "    selection = " << selection << ", channel = " << channelName[channel] << endl;
    cout << "  --------------------------------------------------------------------------" << endl << endl;
    cout << "  uncorrected MC contributions:" << endl;
    cout << "  -----------------------------------------" << endl;

    for (size_t i=0; i<Nfiles; ++i) {
        entries[i]  = countHists[i]->Integral();
        if (i>=3) nBg += entries[i];
    }

    nSig   = entries[1]+entries[2];
    nTToth = entries[3];
    nTW    = entries[4]+entries[5];
    nVV    = entries[6]+entries[7]+entries[8];
    nDYtt  = entries[9]+entries[10]+entries[11];
    nDYmm  = entries[12]+entries[13]+entries[14];
    nDYee  = entries[15]+entries[16]+entries[17];
    nW     = entries[18];
    nQCD   = entries[19]+entries[20]+entries[21]+entries[22]+entries[23]+entries[24]+entries[25] ;

    cout << "    N signal         : " << setw(10) << nSig         << endl;
    cout << "    N ttbar other    : " << setw(10) << nTToth       << endl;
    cout << "    N single top tW  : " << setw(10) << nTW          << endl;
    cout << "    N VV             : " << setw(10) << nVV          << endl;
    cout << "    N Z -> tau tau   : " << setw(10) << nDYtt        << endl;
    cout << "    N Z -> ee/mumu   : " << setw(10) << nDYmm+nDYee  << endl;
    cout << "    N W              : " << setw(10) << nW           << endl;
    cout << "    QCD              : " << setw(10) << nQCD         << endl;
    cout << "  -----------------------------------------"         << endl;
    cout << "    BG (MC)          : " << setw(10) << nBg          << endl;
    cout << "    S/B (MC)         : " << setw(10) << nSig/nBg     << endl;
    cout << "    significance (MC): " << setw(10) << nSig/TMath::Sqrt(nSig+nBg) << endl;
    cout << "  -----------------------------------------"         << endl << endl;

    //recalculate BG with Z correction
    nBg -= nDYmm;
    nBg -= nDYee;

    nDYmm *= zMuCorr;
    nDYee *= zElCorr;

    nBg += nDYmm;
    nBg += nDYee;

    // assumed errors on background: 30% for backgrounds taken from MC, 50% for DY BG
    cout.precision(2);
    cout << "  corrected MC contributions:"   << endl;
    cout << "  -----------------------------------------" << endl;
    cout << "    N other ttbar    : " << setw(8) << nTToth      << " +- " << setw(6) << nTToth*.3        << endl;
    cout << "    N single top tW  : " << setw(8) << nTW         << " +- " << setw(6) << nTW*.3           << endl;
    cout << "    N VV             : " << setw(8) << nVV         << " +- " << setw(6) << nVV*.3           << endl;
    cout << "    N Z -> tau tau   : " << setw(8) << nDYtt       << " +- " << setw(6) << nDYtt*.3         << endl;
    cout << "    N Z -> ee/mumu   : " << setw(8) << nDYmm+nDYee << " +- " << setw(6) << (nDYmm+nDYee)*.5 << endl;
    cout << "    N W              : " << setw(8) << nW          << " +- " << setw(6) << nW*.3            << endl;
    cout << "    N QCD            : " << setw(8) << nQCD        << " +- " << setw(6) << nQCD*.3          << endl;
    cout << "  -----------------------------------------" << endl;

    // nBg is redefined and contains now only tW, VV and DY. Other backgrounds have to be treated  in a different way.
    nBg = nTToth+nTW+nVV+nDYtt+nDYmm+nDYee+nW+nQCD;
    if (scaleUpBG)   nBg += 0.3*(nTToth+nTW+nVV+nDYtt+nW+nQCD);
    if (scaleDownBG) nBg -= 0.3*(nTToth+nTW+nVV+nDYtt+nW+nQCD);
    if (scaleUpDY)   nBg += 0.5*(nDYmm+nDYee);
    if (scaleDownBG) nBg -= 0.5*(nDYmm+nDYee);
    errBg = ((nTToth+nTW+nVV+nDYtt+nW+nQCD)*.3)*
            ((nTToth+nTW+nVV+nDYtt+nW+nQCD)*.3);
    errBg += ((nDYmm+nDYee)*.5) * ((nDYmm+nDYee)*.5);
    errBg = TMath::Sqrt(errBg);

    cout << "    Sum              : " << setw(8)  << nBg    << " +- " << errBg   << endl; ;
    cout << "  -----------------------------------------" << endl << endl;
    cout.precision(3);

    // calculate s/b, significance and cross section
    Double_t SoverB       = entries[0]/nBg;
    Double_t significance = (entries[0])/TMath::Sqrt(entries[0]+nBg);
    Double_t crosssection = (entries[0]-nBg)/eff/branchingFraction[channel]/lumi;
    Double_t staterr      = TMath::Sqrt(entries[0])/eff/branchingFraction[channel]/lumi;

    cout << "    estimated BG     : " << setw(8) << nBg          << endl;
    cout << "    candidates       : " << setw(8) << entries[0]   << endl;
    cout << "    S/B              : " << setw(8) << SoverB       << endl;
    cout << "    significance     : " << setw(8) << significance << endl;
    cout << "    assumed eff      : " << setw(8) << eff          << endl;

    TString totalXsecName("total_xsec_"); totalXsecName.Append(channelName[channel]).Append("_").Append(selection);
    TH1 *totalXsec = new TH1F(totalXsecName.Data(), totalXsecName.Data(), 1, -0.5, 0.5);
    totalXsec->SetBinContent(1, crosssection);
    totalXsec->SetBinError(1, staterr);
    diffXsecHistogramList.Add(totalXsec);

    TString totalXsecEffName("total_xsec_PSE_"); totalXsecEffName.Append(channelName[channel]).Append("_").Append(selection);
    TH1 *totalXsecEff = new TH1F(totalXsecEffName.Data(), totalXsecEffName.Data(), 1, -0.5, 0.5);
    totalXsecEff->SetBinContent(1, eff);
    diffXsecHistogramList.Add(totalXsecEff);

    Double_t syserrUp   =0;
    Double_t syserrDown =0;

    if (systematicsInputTotal && !systematicsInputTotal->IsZombie()) {
	TString channelStr("combined");
	if (channel==kMM) {
          channelStr = "mumu";
        } else if (channel==kEM) {
          channelStr = "emu";
        } else if (channel==kEE) {
          channelStr = "ee";
        }

        //currently no difference between up+down errors - so take both from total_sys_error
        TString upName = "total_xsec_" + channelStr + "_" + selection + "_total_sys_error";
        TString downName = "total_xsec_" + channelStr + "_" + selection + "_total_sys_error";

        TH1 *up, *down;

        systematicsInputTotal->GetObject<TH1>(upName, up);
        systematicsInputTotal->GetObject<TH1>(downName, down);
        if (!up || !down) {
            std::cerr << "WARNING! No systematics for " << upName << "/" << downName << " found!\n";
        } else{
          syserrUp   = crosssection*(up  ->GetBinContent(1));
          syserrDown = crosssection*(down->GetBinContent(1));
        }
    } else {
        std::cerr << "!!! NO SYSTEMATICS AVAILABLE!\n";
    }

    Double_t totalerrUp   = TMath::Sqrt(staterr*staterr+syserrUp  *syserrUp  );
    //Double_t totalerrDown = TMath::Sqrt(staterr*staterr+syserrDown*syserrDown);

    //cout << "    syst err up      : " << setw(8) << syserrUp      << endl;
    //cout << "    syst err down    : " << setw(8) << syserrDown    << endl;
    //cout << "    total err up     : " << setw(8) << totalerrUp    << endl;
    //cout << "    total err down   : " << setw(8) << totalerrDown  << endl;

    // "return" results
    crossS      = crosssection;
    statErr     = staterr;
    systErrUp   = syserrUp;
    systErrDown = syserrDown;

    // since values for cross section and systematic uncertainty of combination are calculated in a different way
    // this printout is only for mumu, ee, emu
    // cross section for combination is printed in CalculateInclusiveCrossSections
    if(channel==kMM || channel==kEM || channel==kEE){
      cout << "    CROSS SECTION    : " << setw(8) << crosssection << endl;
      cout << "    stat err         : " << setw(8) << staterr      << endl;
      cout << "    syst err         : " << setw(8) << syserrUp      << endl;
      cout << "    total err        : " << setw(8) << totalerrUp    << endl;
      cout << endl << endl << endl;
    }
}



// calculate the inclusive cross section for all channels in a certain selection step and combine them
void CalculateInclusiveCrossSections(const char* selection){

   Double_t crosss[4]       = {0. ,0., 0., 0.};
   Double_t statErr[4]      = {0. ,0., 0., 0.};
   Double_t systErrUp[4]    = {0. ,0., 0., 0.};
   Double_t systErrDown[4]  = {0. ,0., 0., 0.};

   CalculateCrossSection(kMM,       selection, crosss[0], statErr[0], systErrUp[0], systErrDown[0]);
   CalculateCrossSection(kEM,       selection, crosss[1], statErr[1], systErrUp[1], systErrDown[1]);
   CalculateCrossSection(kEE,       selection, crosss[2], statErr[2], systErrUp[2], systErrDown[2]);
   CalculateCrossSection(kCOMBINED, selection, crosss[3], statErr[3], systErrUp[3], systErrDown[3]);

   // calculated total errors for ee, mumu and emu
   Double_t totalErrUp[4]   = {0. ,0., 0., 0.};
   Double_t totalErrDown[4] = {0. ,0., 0., 0.};

   for(Int_t i=0; i<3; ++i){
     totalErrUp[i]   = TMath::Sqrt(statErr[i]*statErr[i]+systErrUp[i]*systErrUp[i]);
     totalErrDown[i] = TMath::Sqrt(statErr[i]*statErr[i]+systErrDown[i]*systErrDown[i]);
   }

   // combined cross section is calculated assuming uncorrelated errors
   statErr[3] = 1./statErr[0]/statErr[0];
   statErr[3]+= 1./statErr[1]/statErr[1];
   statErr[3]+= 1./statErr[2]/statErr[2];

   crosss[3] = crosss[0]/statErr[0]/statErr[0];
   crosss[3]+= crosss[1]/statErr[1]/statErr[1];
   crosss[3]+= crosss[2]/statErr[2]/statErr[2];
   crosss[3]/= statErr[3];

   statErr[3] = 1./TMath::Sqrt(statErr[3]);

   if (systematicsInputTotal && !systematicsInputTotal->IsZombie()) {
       //currently no difference between up+down errors - so take both from total_sys_error
       TString upName   = "total_xsec_combined_" + TString(selection) + "_total_sys_error";
       TString downName = "total_xsec_combined_" + TString(selection) + "_total_sys_error";

       TH1 *up, *down;

       systematicsInputTotal->GetObject<TH1>(upName, up);
       systematicsInputTotal->GetObject<TH1>(downName, down);
       if (!up || !down) {
   	   std::cerr << "WARNING! No systematics for " << upName << "/" << downName << " found!\n";
       } else{
   	 systErrUp[3]   = crosss[3]*(up  ->GetBinContent(1));
   	 systErrDown[3] = crosss[3]*(down->GetBinContent(1));
       }
   } else {
       std::cerr << "!!! NO SYSTEMATICS AVAILABLE!\n";
   }

   totalErrUp[3]   = TMath::Sqrt(statErr[3]*statErr[3] + systErrUp[3]*systErrUp[3]);
   totalErrDown[3] = TMath::Sqrt(statErr[3]*statErr[3] + systErrDown[3]*systErrDown[3]);

   cout << "    CROSS SECTION    : " << setw(8) << crosss[3]     << endl;
   cout << "    stat err         : " << setw(8) << statErr[3]    << endl;
   cout << "    syst err         : " << setw(8) << systErrUp[3]  << endl;
   cout << "    total err        : " << setw(8) << totalErrUp[3] << endl;
   cout << endl << endl << endl;

   // measured results with statistical error
   Double_t mx[]   = {      0.50,       1.50,       2.50,       3.50};
   Double_t mexl[] = {      0.00,       0.00,       0.00,       0.00};
   Double_t mexh[] = {      0.00,       0.00,       0.00,       0.00};

   TGraphAsymmErrors *mplot = new TGraphAsymmErrors(4, mx, crosss, mexl, mexh, statErr, statErr);
   mplot->SetMarkerStyle(20);
   mplot->SetMarkerColor(kBlack);
   mplot->SetMarkerSize(1.5);
   mplot->SetLineColor(kBlack);

   TGraphAsymmErrors *mplotwithsys = new TGraphAsymmErrors(4, mx, crosss, mexl, mexh, totalErrDown, totalErrUp);
   mplotwithsys->SetMarkerStyle(20);
   mplotwithsys->SetMarkerColor(kBlack);
   mplotwithsys->SetMarkerSize(1.5);
   mplotwithsys->SetLineColor(kBlack);

   // mstw
   Double_t mstwmean = 157.5;
   Double_t mstwx[]   = {    -0.5,     0.5,	1.5,	 2.5,	  3.5,     4.5};
   Double_t mstwy[]   = {mstwmean,mstwmean,mstwmean,mstwmean,mstwmean,mstwmean};
   Double_t mstwexl[] = {      .4,	.4,	 .5,	  .5,	   .5,      .5};
   Double_t mstwexh[] = {      .5,	.5,	 .5,	  .5,	   .4,      .4};
   Double_t mstweyl[] = {    24.4,    24.4,    24.4,	24.4,	 24.4,    24.4};
   Double_t mstweyh[] = {    23.2,    23.2,    23.2,	23.2,	 23.2,    23.2};

   TGraphAsymmErrors *mstwplot = new TGraphAsymmErrors(6, mstwx, mstwy, mstwexl, mstwexh, mstweyl, mstweyh);
   mstwplot->SetLineColor(kGreen+1);   
   mstwplot->SetLineWidth(4);   
   mstwplot->SetFillColor(kGreen+1);   
   mstwplot->SetFillStyle(3004);

   // herapdf
   Double_t heramean = 144.156;
   Double_t herapdfx[]   = {	-0.5,	  0.5,     1.5,     2.5,     3.5,     4.5};
   Double_t herapdfy[]   = {heramean,heramean,heramean,heramean,heramean,heramean};
   Double_t herapdfexl[] = {	  .4,	   .4,      .5,      .5,      .5,      .5};
   Double_t herapdfexh[] = {	  .5,	   .5,      .5,      .5,      .4,      .4};
   Double_t herapdfeyl[] = {  13.849,  13.849,  13.849,  13.849,  13.849,  13.849};
   Double_t herapdfeyh[] = {   5.475,	5.475,   5.475,   5.475,   5.475,   5.475};

   TGraphAsymmErrors *herapdfplot = new TGraphAsymmErrors(6, herapdfx, herapdfy, herapdfexl, herapdfexh, herapdfeyl, herapdfeyh);
   herapdfplot->SetLineColor(kBlue+1);   
   herapdfplot->SetLineWidth(4);    
   herapdfplot->SetFillColor(kBlue+1);
   herapdfplot->SetFillStyle(3005);

   TH1F* framehist = new TH1F("framehist","",4,0.,4.);
   framehist->SetMinimum(0);
   framehist->SetMaximum(310);
   framehist->GetXaxis()->SetTickLength(0);
   framehist->GetXaxis()->SetBinLabel(1,"");
   framehist->GetXaxis()->SetBinLabel(2,"");
   framehist->GetXaxis()->SetBinLabel(3,"");
   framehist->GetYaxis()->SetTitle("#sigma [pb]");
   framehist->GetYaxis()->CenterTitle(kTRUE);

   TPaveText* box1 = new TPaveText(0.25,0.33,0.33,0.43,"NDC");
   box1->SetFillColor(10);
   box1->SetTextSize(0.04);
   box1->AddText("#mu#mu");

   TPaveText* box2 = new TPaveText(0.44,0.33,0.52,0.43,"NDC");
   box2->SetFillColor(10);
   box2->SetTextSize(0.04);
   box2->AddText("e#mu");

   TPaveText* box3 = new TPaveText(0.62,0.33,0.72,0.43,"NDC");
   box3->SetFillColor(10);
   box3->SetTextSize(0.04);
   box3->AddText("ee");

   TPaveText* box4 = new TPaveText(0.82,0.33,0.90,0.43,"NDC");
   box4->SetFillColor(10);
   box4->SetTextSize(0.04);
   box4->AddText("combined");

   TLegend* leg = getNewLegend(); // new TLegend( 0.56, 0.18, 0.89, 0.33 );
   leg->SetBorderSize( 0 );
   leg->SetFillColor( 0 );
   leg->SetTextFont(62);
   leg->SetTextSize(0.03);
   leg->AddEntry( mplot,       "Measurements",            "p"  );
   leg->AddEntry( mstwplot,    "MCFM #otimes MSTW08",     "lf" );
   leg->AddEntry( herapdfplot, "MCFM #otimes HERAPDF1.0", "lf" );

   TCanvas* Canvas = new TCanvas("plot", "plot", 1200, 800);
   framehist->Draw();
   herapdfplot->Draw("C,2,SAME");
   mstwplot->Draw("C,2,SAME");
   mplot->Draw("p,SAME");
   mplotwithsys->Draw("p,SAME");
   leg ->Draw("SAME");
   box1->Draw("SAME");
   box2->Draw("SAME");
   box3->Draw("SAME");
   box4->Draw("SAME");
   Canvas->Update();
   Canvas->Print(outpath.Copy().Append("TotalCrossSections_").Append(selection).Append(outform));

   delete framehist;
   delete Canvas;
}



// plot differential cross section with yield plot, purity-stability-efficiency plot and gen-reco correlation for signal
void PlotDifferentialCrossSection(const char* particle, const char* quantity, Int_t channel, const char* xtitle, const char* ytitle, 
                                  const Double_t bins[], const Int_t nbins, Double_t crosss[], Double_t statErr[], Double_t totalErrUp[], 
				  Double_t totalErrDown[], const Double_t binCenters[]=0, const Bool_t useKinFit=kTRUE, const char* specialPrefix=0) {
    
    TString plotStr("");    
    TH1* hists[Nfiles];  // histograms needed for event yields and bg sustraction
    TH1* genHist;	 // genHist needed to calculate the efficiencies
    TH1* genHistSmear = 0;   // for pseudo data
    TH1* genRec2DHist;   // reconstructed vs generated signal properties. needed  for correlation and pse plot
    TString genTopEvent("analyzeVisibleGenTopEvent/");    
    
    if(useKinFit){

	// get histograms of reconstructed quantity and generated signal
	if (strcmp(particle,"Leptons")==0) {
            plotStr.Append("Lep");
	} else if (strcmp(particle,"Jets")==0) {
            plotStr.Append("B");
	} else if (strcmp(particle,"TopQuarks")==0) {
            plotStr.Append("Top");
	} else {
            plotStr.Append(particle);
	}
	plotStr.Append(quantity);

	if (channel==kMM) {
            GetCloneHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kMM, hists);
            GetCloneHist(kinAnalyzer, TString("2D_").Append(plotStr), kMM, 1, genRec2DHist);
            AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kMM, 2, genRec2DHist);
            GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);
	} else if (channel==kEM) {
            GetCloneHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kEM, hists);
            GetCloneHist(kinAnalyzer, TString("2D_").Append(plotStr), kEM, 1, genRec2DHist);
            AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kEM, 2, genRec2DHist);
            GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
            
            GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 0, genHistSmear);
            
	} else if (channel==kEE) {
            GetCloneHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kEE, hists);
            GetCloneHist(kinAnalyzer, TString("2D_").Append(plotStr), kEE, 1, genRec2DHist);
            AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kEE, 2, genRec2DHist);
            GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
	} else if (channel==kCOMBINED) {
            GetCloneHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kMM, hists);
            AddHistArray(     kinAnalyzer, TString("kin_").Append(plotStr), kEM, hists);
            AddHistArray(     kinAnalyzer, TString("kin_").Append(plotStr), kEE, hists);
            GetCloneHist(kinAnalyzer, TString("2D_").Append(plotStr), kMM, 1, genRec2DHist);
            AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kMM, 2, genRec2DHist);
            AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kEM, 1, genRec2DHist);
            AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kEM, 2, genRec2DHist);
            AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kEE, 1, genRec2DHist);
            AddHist(     kinAnalyzer, TString("2D_").Append(plotStr), kEE, 2, genRec2DHist);
            GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
	} else {
            cout << "ERROR in PlotDifferentialCrossSection: index " << channel << " for channel is out of range!" << endl;
            return;
	}

	// if particle = Leptons, Jets or TopQuarks then the histogram of the antiparticle is added to that of the particle
	if (strcmp(particle,"Leptons")==0 || strcmp(particle,"Jets")==0 || strcmp(particle,"TopQuarks")==0) {

            plotStr.Clear();

            if (strcmp(particle,"Leptons")==0) {
        	plotStr = "LepBar";
            } else if (strcmp(particle,"Jets")==0) {
        	plotStr = "BBar";
            } else if (strcmp(particle,"TopQuarks")==0) {
        	plotStr = "TopBar";
            }
            plotStr.Append(quantity);

            if (channel==kMM) {
        	AddHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kMM, hists);

        	AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kMM, 1, genRec2DHist);
        	AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kMM, 2, genRec2DHist);

        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);	    
            } else if (channel==kEM) {
        	AddHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kEM, hists);

        	AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEM, 1, genRec2DHist);
        	AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEM, 2, genRec2DHist);

        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
                
                AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 0, genHistSmear);
            } else if (channel==kEE) {
        	AddHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kEE, hists);

        	AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEE, 1, genRec2DHist);
        	AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEE, 2, genRec2DHist);

        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
            } else if (channel==kCOMBINED) {
        	AddHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kMM, hists);
        	AddHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kEM, hists);
        	AddHistArray(kinAnalyzer, TString("kin_").Append(plotStr), kEE, hists);

        	AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kMM, 1, genRec2DHist);
        	AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kMM, 2, genRec2DHist);
        	AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEM, 1, genRec2DHist);
        	AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEM, 2, genRec2DHist);
        	AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEE, 1, genRec2DHist);
        	AddHist(kinAnalyzer, TString("2D_").Append(plotStr), kEE, 2, genRec2DHist);

        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
            }
	}           
    } else { // no use of kin reconstruction
 
	if(strcmp(particle,"LeptonPair")!=0 && strcmp(particle,"Leptons")!=0){
	    cout << "ERROR in PlotDifferentialCrossSectionNoKinFit: " << particle << " not available without kinematic reconstruction!" << endl;      
	}

	// get gen histograms
	plotStr = "LepPair";
	if (strcmp(particle,"Leptons")==0)
            plotStr = "Lep";
	plotStr.Append(quantity);

	if (channel==kMM) {
            GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);
	} else if (channel==kEM) {
            GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
	} else if (channel==kEE) {
            GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
	} else if (channel==kCOMBINED) {
            GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
            AddHist(     genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
	} else {
            cout << "ERROR in PlotDifferentialCrossSection: index " << channel << " for channel is out of range!" << endl;
            return;
	}

	// if particle = Leptons, Jets or TopQuarks then the histogram of the antiparticle is added to that of the particle
	if (strcmp(particle,"Leptons")==0) {

            plotStr.Clear();

            if (strcmp(particle,"Leptons")==0)
        	plotStr = "LepBar";
            plotStr.Append(quantity);

            if (channel==kMM) {
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);	    
            } else if (channel==kEM) {
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
            } else if (channel==kEE) {
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
            } else if (channel==kCOMBINED) {
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
        	AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
            }
	}

	// get reco histograms   
	if(strcmp(particle,"Leptons")==0){ 

	    plotStr = "pt";
	    if (strcmp(quantity,"Eta")==0)
        	plotStr = "eta";

	    if (channel==kMM) {
        	GetCloneHistArray("analyzeMuons8/", plotStr, kMM, hists);
	    } else if (channel==kEM) {
        	GetCloneHistArray("analyzeElecs8/", plotStr, kEM, hists);
		AddHistArray(     "analyzeMuons8/", plotStr, kEM, hists);
	    } else if (channel==kEE) {
        	GetCloneHistArray("analyzeElecs8/", plotStr, kEE, hists);
	    } else if (channel==kCOMBINED) {
        	GetCloneHistArray("analyzeElecs8/", plotStr, kEE, hists);
        	AddHistArray(     "analyzeElecs8/", plotStr, kEM, hists);
        	AddHistArray(     "analyzeMuons8/", plotStr, kEM, hists);
        	AddHistArray(     "analyzeMuons8/", plotStr, kMM, hists);	
	    } 
	} else{  // if lepton pair
	    if (channel==kMM) {
        	GetCloneHistArray("analyzeLeptonPair8/", "DimassRC_MM", kMM, hists);
	    } else if (channel==kEM) {
        	GetCloneHistArray("analyzeLeptonPair8/", "DimassRC_ME", kEM, hists);
	    } else if (channel==kEE) {
        	GetCloneHistArray("analyzeLeptonPair8/", "DimassRC_EE", kEE, hists);
	    } else if (channel==kCOMBINED) {
        	GetCloneHistArray("analyzeLeptonPair8/", "DimassRC_MM", kMM,  hists);
        	AddHistArray(     "analyzeLeptonPair8/", "DimassRC_ME", kEM,  hists);
        	AddHistArray(     "analyzeLeptonPair8/", "DimassRC_EE", kEE,  hists);	
	    } 
	}    
    }
    
    // get the numbers of the bins corresponding to the given bins
    Int_t intBinsGen[nbins+1];
    for (Int_t i=0; i<nbins+1; ++i) {
        intBinsGen[i] = genHist->GetXaxis()->FindBin(bins[i]);
    }

    Int_t intBinsRec[nbins+1];
    for (Int_t i=0; i<nbins+1; ++i) {
        intBinsRec[i] = hists[0]->GetXaxis()->FindBin(bins[i]);
    }

    // calculate the efficiencies in bins
    Double_t efficiencies[nbins];
    for (Int_t i=0; i<nbins; ++i) {
        Double_t nrec = hists[1]->Integral(intBinsRec[i],intBinsRec[i+1]-1);
        nrec += hists[2]->Integral(intBinsRec[i],intBinsRec[i+1]-1);
        Double_t ngen = genHist ->Integral(intBinsGen[i],intBinsGen[i+1]-1);
        efficiencies[i] = nrec/ngen;		
    }

    Double_t zElCorr = 1.;
    Double_t zMuCorr = 1.;
    Double_t zCorr   = 1.;

    if (doDYcorrection) {
      zElCorr = zElNorm9;
      zMuCorr = zMuNorm9;
      if (channel == kEE) {
        zCorr = zElNorm9;
      }
      else if (channel == kMM) {
        zCorr = zMuNorm9;
      }
      else if (channel == kCOMBINED) {
        // calculate weighted average of ee and mumu correction;
        Double_t w1 = hists[12]->Integral();
        w1 += hists[13]->Integral();
        w1 += hists[14]->Integral();

        Double_t w2 = hists[12]->Integral();
        w2 += hists[13]->Integral();
        w2 += hists[14]->Integral();

        zCorr = (zMuCorr*w1 + zElCorr*w2)/(w1+w2);
      }
    }

    SetWeights(hists, zElCorr, zMuCorr);

    // extract numbers of selected events in all samples and bins
    Double_t nreconstructed[nbins][Nfiles];
    for (Int_t i=0; i<nbins; ++i) {
        for (size_t j=0; j<Nfiles; ++j) {
            nreconstructed[i][j]=hists[j]->Integral(intBinsRec[i],intBinsRec[i+1]-1);
        }
    }

    TH1* binhists[Nfiles];
    for (size_t j=0; j<Nfiles; ++j) {
        binhists[j] = new TH1D("","",nbins,bins);
        for (Int_t i=1; i<=nbins; ++i) {
            binhists[j]->SetBinContent(i,nreconstructed[i-1][j]);
        }
    }

    TH1* mergedhists[Nplots];
    MergeHistArray(binhists, mergedhists);

    SetPlotFilling(mergedhists);

    //scale backgound +-30%
    for (size_t i = 3; i < Nplots; ++i) {
        if (i != kDYEM) {
            if (scaleUpBG) mergedhists[i]->Scale(1.3);
            if (scaleDownBG) mergedhists[i]->Scale(0.7);
        }
    }

    //scale dy +-50%
    if (scaleUpDY) mergedhists[kDYEM]->Scale(1.5);
    if (scaleDownDY) mergedhists[kDYEM]->Scale(0.5);

    TLegend* leg = new TLegend(0.70,0.58,0.95,0.87);
    FillLegend(leg, mergedhists, zCorr);

    TString title("combined_");
    if(useKinFit)
        title.Append("FixedMt_Btag_Yield_");
    else
        title.Append("NoFit_Yield_");    
    title.Append(particle);
    title.Append("_");
    title.Append(quantity);   



    THStack* hstack = new THStack("hstack",title);
    for (size_t i=1; i<Nplots; ++i) {
        hstack->Add(mergedhists[i]);
    }

    // make canvas
    TCanvas* Canvas = new TCanvas("plot", "plot", 800, 800);

    hstack->Draw("HIST");
    FormatHisto(hstack->GetHistogram());

    hstack->SetMaximum(std::max(1.2*hstack->GetMaximum(), 1.2*mergedhists[kDATA]->GetMaximum()));
    hstack->SetMinimum(0);
    hstack->GetXaxis()->SetTitle(xtitle);
    hstack->GetYaxis()->SetTitle("N_{evts}");

    // style data
    //TH1* withSysNoBCC = CloneAddSystematics(mergedhists[kDATA]);     
    //withSysNoBCC->SetMarkerStyle(20);
    //withSysNoBCC->SetMarkerSize(1.5);
    //withSysNoBCC->SetLineWidth(2);
    //withSysNoBCC->Draw("same,P");
        
    mergedhists[kDATA]->SetMarkerStyle(20);
    mergedhists[kDATA]->SetMarkerSize(1.5);
    mergedhists[kDATA]->SetLineWidth(2);   
    mergedhists[kDATA]->Draw("same,E0");
    if (drawLegend) leg->Draw("same");
    semileptonic::DrawCMSLabels(isPreliminary, lumi);
    semileptonic::DrawDecayChLabel(channelNameTeX[channel]);

    if (!specialPrefix) specialPrefix = "";
    Canvas->Print(outpath.Copy().Append(channelName[channel]).Append("/").Append(specialPrefix).Append(title).Append(outform));
    
    mergedhists[kDATA]->SetName(title);
    mergedhists[kDATA]->GetXaxis()->SetTitle(xtitle);
    mergedhists[kDATA]->GetYaxis()->SetTitle("N_{evts}");
    kinEffHistogramList.Add(mergedhists[kDATA]->Clone());
    
    mergedhists[kSIG]->SetName(title.Copy().Append("_signalMC"));
    mergedhists[kSIG]->GetXaxis()->SetTitle(xtitle);
    mergedhists[kSIG]->GetYaxis()->SetTitle("N_{evts}");
    kinEffHistogramList.Add(mergedhists[kSIG]->Clone());    
    //delete withSysNoBCC;

    // histogram for measured cross section
    TH1* crossHist = (TH1*)binhists[0]->Clone();
    crossHist->Reset();

    // histogram for generated cross section
    TH1* genCrossHist = new TH1D("","",nbins,bins);

    cout.precision(3);

    for (Int_t i=1; i<=nbins; ++i) {
        Double_t bgsum=0;
        for (size_t j=3; j<Nplots; ++j) {
            bgsum += mergedhists[j]->GetBinContent(i);
        }
        if (dataIsFakeFromMonteCarlo) bgsum = 0;
        Double_t binw = bins[i]-bins[i-1];
        // set measured cross section
        if (efficiencies[i-1] == 0) { //cannot divide by zero
            cout << "WARNING in PlotDifferentialCrossSection: Efficieny is zero in bin " << i << " while creating " << title << endl;
            crossHist->SetBinContent(i, 0);
            crossHist->SetBinError(i, 0);
        } else {
            crossHist->SetBinContent(i,(binhists[0]->GetBinContent(i)-bgsum)/efficiencies[i-1]/lumi/binw);
            crossHist->SetBinError(i,TMath::Sqrt(binhists[0]->GetBinContent(i))/efficiencies[i-1]/lumi/binw); // statistical error	    
        }
        // set generated cross section
        genCrossHist->SetBinContent(i,genHist->Integral(intBinsGen[i-1],intBinsGen[i]-1)*sampleCrossSection[1]/totalEvents[1]/binw);

        if (strcmp(particle,"Leptons")==0 || strcmp(particle,"Jets")==0 || strcmp(particle,"TopQuarks")==0) {
            crossHist->SetBinContent(i,crossHist->GetBinContent(i)/2);
            crossHist->SetBinError(i,crossHist->GetBinError(i)/2);
            genCrossHist->SetBinContent(i,genCrossHist->GetBinContent(i)/2);
        }
    }
      
    // store the visible cross section for normalisation
    if (strcmp(particle,"Leptons")==0 && strcmp(quantity,"Eta")==0 && channel!=kCOMBINED) {
      if(useKinFit)
        visCrossSections[channel] = crossHist->Integral("width");
      else
        visCrossSectionsNoFit[channel] = crossHist->Integral("width");                  
    }
    cout << "visible cross section (" << channelName[channel] << ") : " << crossHist->Integral("width") << endl;

    gStyle->SetErrorX();

    title = channelName[channel];
    if(useKinFit)
        title.Append("_FixedMt_Btag_Cross_");
    else
        title.Append("_NoFit_Cross_");      
    title.Append(particle);
    title.Append("_");
    title.Append(quantity);

    Canvas->Clear();
    genCrossHist->SetMinimum(0);

    // theory curves
    TH1 *gh = (TH1*) genHist->Clone();
    gh->Scale(sampleCrossSection[1]/totalEvents[1]/gh->GetBinWidth(1));
   
    TH1* mcatnloh = GetNloCurve(particle, quantity, "MCatNLO");
    mcatnloh->Scale(branchingFraction[channel]);
    mcatnloh->Rebin(10); mcatnloh->Scale(0.1);
   
    TH1* powhegh  = GetNloCurve(particle, quantity, "Powheg");
    powhegh->Scale(branchingFraction[channel]);
    powhegh->Rebin(2); powhegh->Scale(0.5);

    //two entries
    if (strcmp(particle,"Leptons")==0 || strcmp(particle,"Jets")==0 || strcmp(particle,"TopQuarks")==0){
      gh      ->Scale(0.5); 
      mcatnloh->Scale(0.5);      
      powhegh ->Scale(0.5);      
    }
    
    if (normaliseToUnitArea) {    
      Double_t scale_data = 1./visCrossSections[channel];
      if(!useKinFit)
          scale_data = 1./visCrossSectionsNoFit[channel];
      crossHist->Scale(scale_data); 
    	
      Double_t scale_gen1 = 1./genCrossHist->Integral("width");
      genCrossHist->Scale(scale_gen1);

      Double_t scale_gen2 = 1./gh->Integral("width");      
      gh->Scale(scale_gen2);
  
      Double_t scale_mcatnlo = 1./mcatnloh->Integral("width");
      mcatnloh->Scale(scale_mcatnlo);
       
      Double_t scale_powheg = 1./powhegh->Integral("width");
      powhegh->Scale(scale_powheg);              
      
      if (genHistSmear) {
        genHistSmear->Sumw2();
        genHistSmear = genHistSmear->Rebin(nbins, "", bins);
        Double_t scale_smear = 1./genHistSmear->Integral("width");
        genHistSmear->Scale(scale_smear);
      }
    }

    //  store Cross Section histograms
    crossHist->SetName(title);
    crossHist->GetXaxis()->SetTitle(xtitle);
    crossHist->GetYaxis()->SetTitle(ytitle);    

    TGraphAsymmErrors* bccCrossGraph = BinCenterCorrectedGraph(crossHist, gh, binCenters);
    
    if(channel!=kCOMBINED){

      Double_t grLmts[4];
      bccCrossGraph->ComputeRange(grLmts[0], grLmts[1], grLmts[2], grLmts[3]);

      genCrossHist->GetXaxis()->SetTitle(xtitle);
      genCrossHist->GetYaxis()->SetTitle(ytitle);
      genCrossHist->SetLineWidth(1);
      genCrossHist->SetLineColor(kRed+1);
      FormatHisto(genCrossHist);
      genCrossHist->Draw();

      // for pt and mass distribution use log scale
      if(strcmp(quantity,"Pt")==0 || strcmp(quantity,"Mass")==0){
        genCrossHist->SetMaximum(std::max(3.*gh->GetMaximum(), 3.*grLmts[3]));   
        genCrossHist->SetMinimum(std::max(0.5*genHist->GetMinimum(), 0.5*grLmts[1]));
        gPad->SetLogy(1);
      } else{
        genCrossHist->SetMaximum(std::max(1.2*gh->GetMaximum(), 1.2*grLmts[3]));      
        genCrossHist->SetMinimum(0);            
      }

      Int_t nrebin = 4.;
      if((strcmp(particle,"Leptons")==0 || strcmp(particle,"Jets")==0) && strcmp(quantity,"Eta")==0){
	nrebin=4;
	mcatnloh->Rebin(2); mcatnloh->Scale(0.5);
      }  
      else if(strcmp(particle,"LepPair")==0 && strcmp(quantity,"Mass")==0)
	nrebin=8;

      gh->SetLineColor(kRed+1);
      gh->SetLineWidth(4);
      gh->Rebin(nrebin); gh->Scale(1./nrebin);
      gh->Draw("same,C");

      mcatnloh->SetLineColor(kAzure);
      mcatnloh->SetLineWidth(2);
      if (mcatnloh->GetEntries()) mcatnloh->Draw("same,HIST,C");

      powhegh->SetLineColor(kGreen+1);
      powhegh->SetLineWidth(2);
      if (powhegh->GetEntries()) powhegh->Draw("same,C");

      if (genHistSmear) {
        genHistSmear->SetLineColor(kBlack);
        genHistSmear->Draw("esame");
      }
      
      //TLegend leg2(0.70,0.70,0.95,0.87);
      TLegend leg2 = *getNewLegend();
      leg2.AddEntry(bccCrossGraph, "Data",    "p");
      leg2.AddEntry(gh,            "Madgraph","l");
      if (mcatnloh->GetEntries()) leg2.AddEntry(mcatnloh,      "MC@NLO",  "l");
      if (powhegh->GetEntries())  leg2.AddEntry(powhegh,       "Powheg",  "l");        
      leg2.SetFillStyle(0);
      leg2.SetBorderSize(0);
      leg2.Draw("same");

      TGraphAsymmErrors* withSys = CloneAddSystematics(bccCrossGraph, title);
      withSys->SetLineWidth(2);
      //withSys->SetLineColor(kBlue);
      withSys->SetLineColor(kBlack);
      withSys->Draw("same,Z");

      bccCrossGraph->SetMarkerStyle(20);
      bccCrossGraph->SetMarkerSize(1.5);
      bccCrossGraph->SetLineWidth(3);
      bccCrossGraph->SetLineColor(1);
      bccCrossGraph->Draw("same,P");
      //crossHist->Draw("same hist"); //data histogram

      semileptonic::DrawCMSLabels(isPreliminary, lumi);
      semileptonic::DrawDecayChLabel(channelNameTeX[channel]);
      Canvas->Print(outpath.Copy().Append(channelName[channel]).Append("/").Append(specialPrefix).Append(title).Append(outform));

      diffXsecHistogramList.Add(crossHist->Clone());

      // fill values for cross section and errors that are then used by PlotDifferentialCrossSection in order to calculate the combined cross section value           
      for(Int_t i=0; i<nbins; ++i){    
	crosss[i]       = (withSys->GetY())[i];
	totalErrUp[i]   = (withSys->GetEYhigh())[i];
	totalErrDown[i] = (withSys->GetEYlow())[i];    
	statErr[i] = (bccCrossGraph->GetEYlow())[i];
      } 

      delete withSys;
      gPad->SetLogy(0);
    }

    delete crossHist;
    
    if(!useKinFit){ // for cross sections without kinematic reconstruction the 2d histogram is not available -> stop here
       delete Canvas;
       return; 
    }
    
    // print 2D correlation plot
    genRec2DHist->GetXaxis()->SetTitle(TString("generated ").Append(xtitle));
    genRec2DHist->GetYaxis()->SetTitle(TString("reconstructed ").Append(xtitle));
    genRec2DHist->GetYaxis()->SetTitleOffset(1.7);

    title = channelName[channel];
    title.Append("_FixedMt_Btag_Correlation_");
    title.Append(particle);
    title.Append("_");
    title.Append(quantity);

    Canvas->Clear();
    genRec2DHist->Draw("BOX");
    FormatHisto(genRec2DHist);

    TString corrstr("correlation = ");

    char corrch[5];
    sprintf(corrch,"%.2f", ((TH2D*)genRec2DHist)->GetCorrelationFactor());

    corrstr += corrch;

    TPaveText* box = new TPaveText(0.65,0.15,0.85,0.23,"NDC");
    box->SetFillStyle(0);
    box->SetBorderSize(0);
    box->SetTextSize(0.03);
    box->AddText(corrstr);
    box->Draw("SAME");
    Canvas->Print(outpath.Copy().Append(channelName[channel]).Append("/").Append(specialPrefix).Append(title).Append(outform));

    TH1* genRecHist = new TH1D("","",nbins,bins);

    Int_t intbins[nbins+1];
    // fill the elements of the main diagonal of the 2d hist into binned 1D histogram
    for (Int_t i=0; i<nbins+1; ++i) {
        intbins[i] = genRec2DHist->GetXaxis()->FindBin(bins[i]);
        if (i>0) {
            genRecHist->SetBinContent(i,((TH2D*)genRec2DHist)->Integral(intbins[i-1],intbins[i]-1,intbins[i-1],intbins[i]-1));
        }
    }

    TH1* genPseHist = ((TH2D*)genRec2DHist)->ProjectionX();
    TH1* recPseHist = ((TH2D*)genRec2DHist)->ProjectionY();

    TH1* genBinHist    = genPseHist->Rebin(nbins,"genBinHist", bins);
    TH1* recBinHist    = recPseHist->Rebin(nbins,"recBinHist", bins);
    genHist = genHist->Rebin(nbins, "genHist", bins);

    genRecHist->SetBinContent(0,      0);
    genRecHist->SetBinContent(nbins+1,0);
    genBinHist->SetBinContent(0,      0);
    genBinHist->SetBinContent(nbins+1,0);
    recBinHist->SetBinContent(0,      0);
    recBinHist->SetBinContent(nbins+1,0);
    genHist   ->SetBinContent(0,      0);
    genHist   ->SetBinContent(nbins+1,0);

    Canvas->Clear();

    // this is realy ugly but necessary:
    // As it seems, somewhere a double is tranformed into a float so that
    // efficiencies can be larger than 1.
    for(Int_t i=1; i<=genRecHist->GetNbinsX(); ++i){
      if(genRecHist->GetBinContent(i) > recBinHist->GetBinContent(i)){
        genRecHist->SetBinContent(i,recBinHist->GetBinContent(i));
	cout << "WARNING in PlotDifferentialCrossSections: number of events generated and reconstructed in bin " << i
	<< " is larger than number of reconstructed events in that bin" << endl;
      }
      if(genRecHist->GetBinContent(i) > genBinHist->GetBinContent(i)){
        genRecHist->SetBinContent(i,genBinHist->GetBinContent(i));
	cout << "WARNING in PlotDifferentialCrossSections: number of events generated and reconstructed in bin " << i
	<< " is larger than number of genrated events in that bin" << endl;
      }
    }

    // efficiency, purity, stability
    TGraphAsymmErrors* grE; // for efficiency
    TGraphAsymmErrors* grP; // for purity
    TGraphAsymmErrors* grS; // for stability

    TH1* efficiency = (TH1*) genHist->Clone();
    efficiency->Divide(recBinHist, genHist);

    // efficiency
    grE = new TGraphAsymmErrors(recBinHist, genHist);
    grE->SetMinimum(0);
    grE->SetMaximum(1);
    grE->SetLineColor(8);
    grE->SetLineWidth(2);
    grE->SetMarkerSize(2);
    grE->SetMarkerStyle(21);
    grE->SetMarkerColor(8);

    // purity
    grP = new TGraphAsymmErrors(genRecHist, recBinHist);
    grP->SetLineColor(4);
    grP->SetLineWidth(2);
    grP->SetMarkerSize(2);
    grP->SetMarkerStyle(23);
    grP->SetMarkerColor(4);

    // stability
    grS = new TGraphAsymmErrors(genRecHist, genBinHist);
    grS->SetLineColor(2);
    grS->SetLineWidth(2);
    grS->SetMarkerSize(2);
    grS->SetMarkerStyle(22);
    grS->SetMarkerColor(2);

    // correct bin center also for these graphs
    for (Int_t i=0; i<bccCrossGraph->GetN();++i) {
      grE->SetPoint(i, (bccCrossGraph->GetX())[i], (grE->GetY())[i]);
      grP->SetPoint(i, (bccCrossGraph->GetX())[i], (grP->GetY())[i]);
      grS->SetPoint(i, (bccCrossGraph->GetX())[i], (grS->GetY())[i]);

      grE->SetPointEXhigh(i, bccCrossGraph->GetErrorXhigh(i));
      grP->SetPointEXhigh(i, bccCrossGraph->GetErrorXhigh(i));
      grS->SetPointEXhigh(i, bccCrossGraph->GetErrorXhigh(i));

      grE->SetPointEXlow(i, bccCrossGraph->GetErrorXlow(i));
      grP->SetPointEXlow(i, bccCrossGraph->GetErrorXlow(i));
      grS->SetPointEXlow(i, bccCrossGraph->GetErrorXlow(i));
    }

    grE->GetXaxis()->SetTitle(xtitle);

    // this is a dummy to get the x axis range corrct
    recBinHist->Reset();
    recBinHist->Draw();
    recBinHist->SetMaximum(1.);
    FormatHisto(recBinHist);
    
    grE->Draw("P,SAME");       
    grP->Draw("P,SAME");
    grS->Draw("P,SAME");

    TLegend* leg3 = getNewLegend(); // new TLegend(0.60,0.73,0.95,0.83);
    leg3->SetFillStyle(0);
    leg3->SetBorderSize(0);
    leg3->AddEntry(grE, "Efficieny", "p" );
    leg3->AddEntry(grP, "Purity",    "p" );
    leg3->AddEntry(grS, "Stability", "p" );
    if (drawLegend) leg3->Draw("SAME");

    title.Clear();
    if (channel==kMM)
        title="mumu_";
    else if (channel==kEM)
        title="emu_";
    else if (channel==kEE)
        title="ee_";
    else
        title="combined_";

    title.Append("FixedMt_Btag_PSE_");
    title.Append(particle);
    title.Append("_");
    title.Append(quantity);

    Canvas->Update();
    Canvas->Print(outpath.Copy().Append(channelName[channel]).Append("/").Append(specialPrefix).Append(title).Append(outform));

    efficiency->SetName(title);
    diffXsecHistogramList.Add(efficiency->Clone());

    delete grE;
    delete grP;
    delete grS;
    delete Canvas;
    delete hstack;
    return;
}



// plot differential cross section in all channels and combine them
void PlotDifferentialCrossSections(const char* particle, const char* quantity, const char* xtitle, const char* ytitle, 
                                   const Double_t bins[], const Int_t nbins, const Double_t binCenters[]=0, const Bool_t useKinFit=kTRUE, const char* specialPrefix=0) {

    Double_t crosssMM[nbins];
    Double_t statErrMM[nbins];
    Double_t totalErrUpMM[nbins];
    Double_t totalErrDownMM[nbins];
    
    Double_t crosssEM[nbins];
    Double_t statErrEM[nbins];
    Double_t totalErrUpEM[nbins];
    Double_t totalErrDownEM[nbins];
    
    Double_t crosssEE[nbins];
    Double_t statErrEE[nbins];
    Double_t totalErrUpEE[nbins];
    Double_t totalErrDownEE[nbins];
    
    Double_t crosssCombined[nbins];
    Double_t statErrCombined[nbins];
    Double_t totalErrUpCombined[nbins];
    Double_t totalErrDownCombined[nbins];  
   
    PlotDifferentialCrossSection(particle, quantity, kMM,	xtitle, ytitle, bins, nbins, crosssMM, statErrMM, totalErrUpMM, totalErrDownMM, binCenters, useKinFit, specialPrefix);
    PlotDifferentialCrossSection(particle, quantity, kEM,       xtitle, ytitle, bins, nbins, crosssEM, statErrEM, totalErrUpEM, totalErrDownEM, binCenters, useKinFit, specialPrefix);
    PlotDifferentialCrossSection(particle, quantity, kEE,       xtitle, ytitle, bins, nbins, crosssEE, statErrEE, totalErrUpEE, totalErrDownEE, binCenters, useKinFit, specialPrefix);
    PlotDifferentialCrossSection(particle, quantity, kCOMBINED, xtitle, ytitle, bins, nbins, crosssCombined, statErrCombined, totalErrUpCombined, totalErrDownCombined, binCenters, useKinFit, specialPrefix);
    
    TString title("combined_");
    if(useKinFit)
        title.Append("FixedMt_Btag_Cross_");
    else
        title.Append("NoFit_Cross_");    
    title.Append(particle);
    title.Append("_");
    title.Append(quantity);   
    
    TCanvas* Canvas = new TCanvas("plot", "plot", 800, 800);     
   
    TH1D* crossHist = new TH1D(title, title, nbins, bins);
    for(Int_t i=0;i<nbins;++i){
//       statErrCombined[i] = 0.;
//       statErrCombined[i] += statErrMM[i]*statErrMM[i];
//       statErrCombined[i] += statErrEM[i]*statErrEM[i];
//       statErrCombined[i] += statErrEE[i]*statErrEE[i];
//       statErrCombined[i] = TMath::Sqrt(statErrCombined[i]);   
// 
//       crosssCombined[i] = crosssMM[i]+crosssEM[i]+crosssEE[i];

      // FIXME: Here the AVERAGE of the three cross sections is calculated but it should be the sum.
      //        The sum is calculated in the commented code above but this causes problems with the Z veto bin.
      //        For NORMALISED cross sections calculating the average is ok
      statErrCombined[i] = 0.;
      if(statErrMM[i]>0.)
        statErrCombined[i] += 1./statErrMM[i]/statErrMM[i];
      if(statErrEM[i]>0.)	
        statErrCombined[i] += 1./statErrEM[i]/statErrEM[i]; 
      if(statErrEE[i]>0.)          
        statErrCombined[i] += 1./statErrEE[i]/statErrEE[i];

      crosssCombined[i] = 0.;      
      if(statErrMM[i]>0.)
        crosssCombined[i] += crosssMM[i]/statErrMM[i]/statErrMM[i];
      if(statErrEM[i]>0.)	
        crosssCombined[i] += crosssEM[i]/statErrEM[i]/statErrEM[i];
      if(statErrEE[i]>0.)          
        crosssCombined[i] += crosssEE[i]/statErrEE[i]/statErrEE[i];      
      crosssCombined[i] /= statErrCombined[i];

      statErrCombined[i] = 1./TMath::Sqrt(statErrCombined[i]); 
      
      crossHist->SetBinContent(i+1, crosssCombined[i]);
      crossHist->SetBinError(i+1, statErrCombined[i]);         
    }

    // store the visible cross section for normalisation
    if (strcmp(particle,"Leptons")==0 && strcmp(quantity,"Eta")==0) {
      if(useKinFit){
        visCrossSections[kCOMBINED] = crossHist->Integral("width");
        cout << "visible cross section combined = " << visCrossSections[kCOMBINED] << endl;
      } else {
        visCrossSectionsNoFit[kCOMBINED] = crossHist->Integral("width");
        cout << "visible cross section combined = " << visCrossSectionsNoFit[kCOMBINED] << endl;      
      }     
    }
    
    // get histograms for madgraph gen curve
    TString plotStr("");
    if (strcmp(particle,"Leptons")==0) {
        plotStr.Append("Lep");
    } else if (strcmp(particle,"Jets")==0) {
        plotStr.Append("B");
    } else if (strcmp(particle,"TopQuarks")==0) {
        plotStr.Append("Top");
    } else {
        plotStr.Append(particle);
    }
    plotStr.Append(quantity);

    TH1* genHist;
    TString genTopEvent("analyzeVisibleGenTopEvent/");
    GetCloneHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
    AddHist(	 genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);
    AddHist(	 genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
    AddHist(	 genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
    AddHist(	 genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
    AddHist(	 genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
    
    // if particle = Leptons, Jets or TopQuarks then the histogram of the antiparticle is added to that of the particle
    if (strcmp(particle,"Leptons")==0 || strcmp(particle,"Jets")==0 || strcmp(particle,"TopQuarks")==0) {

      plotStr.Clear();
      plotStr = "";

      if (strcmp(particle,"Leptons")==0) {
          plotStr.Append("LepBar");
      } else if (strcmp(particle,"Jets")==0) {
          plotStr.Append("BBar");
      } else if (strcmp(particle,"TopQuarks")==0) {
          plotStr.Append("TopBar");
      }
      
      plotStr.Append(quantity);
      AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 1, genHist);
      AddHist(genTopEvent, TString("gen_").Append(plotStr), kMM, 2, genHist);
      AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 1, genHist);
      AddHist(genTopEvent, TString("gen_").Append(plotStr), kEM, 2, genHist);
      AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 1, genHist);
      AddHist(genTopEvent, TString("gen_").Append(plotStr), kEE, 2, genHist);
    }

    genHist->Scale(sampleCrossSection[1]/totalEvents[1]);

    // histogram for generated cross section
    TH1* genHistBinned = new TH1D("","",nbins,bins);
    Int_t intBinsGen[nbins]; 
  
    for (Int_t i=0; i<=nbins; ++i) {    
      intBinsGen[i] = genHist->GetXaxis()->FindBin(bins[i]);  
    
      if(i==0) continue;
      
      Double_t binw = bins[i]-bins[i-1];      
      genHistBinned->SetBinContent(i,genHist->Integral(intBinsGen[i-1],intBinsGen[i]-1)/binw);

      if (strcmp(particle,"Leptons")==0 || strcmp(particle,"Jets")==0 || strcmp(particle,"TopQuarks")==0) {
	genHistBinned->SetBinContent(i,genHistBinned->GetBinContent(i)/2);
      }
    }

    genHist->Scale(1./genHist->GetBinWidth(1));

    TH1* mcatnloh = GetNloCurve(particle, quantity, "MCatNLO");
    mcatnloh->Scale(branchingFraction[kCOMBINED]);
    mcatnloh->Rebin(10); mcatnloh->Scale(0.1);
   
    TH1* powhegh  = GetNloCurve(particle, quantity, "Powheg");
    powhegh->Scale(branchingFraction[kCOMBINED]);    
    //powhegh->Rebin(2); powhegh->Scale(0.5);

    //two entries
    if (strcmp(particle,"Leptons")==0 || strcmp(particle,"Jets")==0 || strcmp(particle,"TopQuarks")==0){
      genHist ->Scale(0.5); 
      mcatnloh->Scale(0.5);      
      powhegh ->Scale(0.5);      
    }
    
    if (normaliseToUnitArea) {	    
      Double_t scale_data = 1./visCrossSections[kCOMBINED];
      if(!useKinFit)
          scale_data = 1./visCrossSectionsNoFit[kCOMBINED];
      crossHist->Scale(scale_data);    
    	
      Double_t scale_gen1 = 1./genHist->Integral("width");
      genHist->Scale(scale_gen1);

      Double_t scale_gen2 = 1./genHistBinned->Integral("width");      
      genHistBinned->Scale(scale_gen2);
  
      Double_t scale_mcatnlo = 1./mcatnloh->Integral("width");
      mcatnloh->Scale(scale_mcatnlo);
       
      Double_t scale_powheg = 1./powhegh->Integral("width");;
      powhegh->Scale(scale_powheg);   
    }

    TGraphAsymmErrors* bccCrossGraph = BinCenterCorrectedGraph(crossHist, genHist, binCenters);
    Double_t grLmts[4];
    bccCrossGraph->ComputeRange(grLmts[0], grLmts[1], grLmts[2], grLmts[3]);    

    genHistBinned->GetXaxis()->SetTitle(xtitle);
    genHistBinned->GetYaxis()->SetTitle(ytitle);
    genHistBinned->SetLineWidth(1);
    genHistBinned->SetLineColor(kRed+1);
    FormatHisto(genHistBinned);
    genHistBinned->Draw();

    // for pt and mass distribution use log scale
    if(strcmp(quantity,"Pt")==0 || strcmp(quantity,"Mass")==0){
      genHistBinned->SetMaximum(std::max(3.*genHist->GetMaximum(), 3.*grLmts[3]));   
      genHistBinned->SetMinimum(std::max(0.5*genHist->GetMinimum(), 0.5*grLmts[1]));
      gPad->SetLogy(1);
    } else{
      genHistBinned->SetMaximum(std::max(1.2*genHist->GetMaximum(), 1.2*grLmts[3]));
      genHistBinned->SetMinimum(0);    
    }

    Int_t nrebin = 2.;
    if((strcmp(particle,"Leptons")==0 || strcmp(particle,"Jets")==0) && strcmp(quantity,"Eta")==0){
      nrebin=4;
      mcatnloh->Rebin(2); mcatnloh->Scale(0.5);
    } else if(strcmp(particle,"LepPair")==0 && strcmp(quantity,"Mass")==0){
      nrebin=8;
    } 
     
    genHist->SetLineColor(kRed+1);
    genHist->SetLineWidth(4);
    genHist->Rebin(nrebin); genHist->Scale(1./nrebin);
    genHist->Draw("same,C");
    
    mcatnloh->SetLineColor(kAzure);
    mcatnloh->SetLineWidth(2);
    if (mcatnloh->GetEntries()) mcatnloh->Draw("same,HIST,C");
    
    powhegh->SetLineColor(kGreen+1);
    powhegh->SetLineWidth(2);
    if (powhegh->GetEntries()) powhegh->Draw("same,C");  

    TGraphAsymmErrors* withSys = CloneAddSystematics(bccCrossGraph, title);
    withSys->SetLineWidth(2);
    withSys->SetLineColor(kBlack);
    withSys->Draw("same,Z");

    bccCrossGraph->SetMarkerStyle(20);
    bccCrossGraph->SetMarkerSize(1.5);
    bccCrossGraph->SetLineWidth(3);
    bccCrossGraph->SetLineColor(1);
    bccCrossGraph->Draw("same,P");

    TLegend leg = *getNewLegend();
    leg.AddEntry(bccCrossGraph, "Data",    "p");
    leg.AddEntry(genHist,       "Madgraph","l");
    if (mcatnloh->GetEntries()) leg.AddEntry(mcatnloh,      "MC@NLO",  "l");
    if (powhegh->GetEntries())  leg.AddEntry(powhegh,       "Powheg",  "l");        
    leg.SetFillStyle(0);
    leg.SetBorderSize(0);
    leg.Draw("same");
    
    semileptonic::DrawCMSLabels(isPreliminary, lumi);
    semileptonic::DrawDecayChLabel(channelNameTeX[kCOMBINED]);

    Canvas->Print(outpath.Copy().Append("combined/").Append(specialPrefix).Append(title).Append(outform));

    crossHist->GetXaxis()->SetTitle(xtitle);
    crossHist->GetYaxis()->SetTitle(ytitle);         
    diffXsecHistogramList.Add(crossHist->Clone());
        
    // print summary table for combined cross section
    std::cout << "BCC Corrections done: " << particle << " " << quantity << std::endl;
    for (int bin = 0; bin < nbins; ++bin) {
      double y = bccCrossGraph->GetY()[bin];
      std::cout << (bccCrossGraph->GetX()[bin]>20 ? std::setprecision(0) : std::setprecision(1))
         << "$" << bccCrossGraph->GetX()[bin] << "$\t&\t"
         << std::setprecision(strcasecmp(quantity, "eta") ? 0:1)
         << "$" << bins[bin] << "$ to $" << bins[bin+1] << "$\t&\t"
         << std::setprecision(5) << y << "\t&\t" << std::setprecision(1)
         << 100*bccCrossGraph->GetErrorYhigh(bin)/y << "\t&\t"
         << TMath::Sqrt(TMath::Power(100*withSys->GetErrorYhigh(bin)/y,2) - TMath::Power(100*bccCrossGraph->GetErrorYhigh(bin)/y,2)) << "\t&\t"
         << 100*withSys->GetErrorYhigh(bin)/y << "\t"
         //<< "+" << 100*bccCrossGraph->GetErrorYhigh(bin)/y << " / -" << 100*bccCrossGraph->GetErrorYlow(bin)/y
         << "\t\\\\" << std::endl;
     }   
        
    delete crossHist;
    delete bccCrossGraph;    
    delete withSys;        
    delete genHist;        
    delete genHistBinned;
    
    gPad->SetLogy(0);    
}



// ratio of events inside and outside the Z veto region in DY MC. ratio for data and all MC samples is printed as cross check
void SetROutIn(const Int_t channel, const Int_t step)
{
    if (channel!=kEE && channel!=kMM) {
        cout << "ERROR in rOutIn: selected channel is neither ee nor mumu!" << endl;
        return;
    }

    if (step!=7 && step!=8 && step!=9) {
        cout << "ERROR in rOutIn: selected step is out of range!" << endl;
        return;
    } 

    TString moduleOutStr("analyzeLeptonPair");
    TString moduleInStr("analyzeLeptonPairZvetoRegion");

    char step_c[2]; 
    sprintf(step_c,"%d",step);

    moduleOutStr.Append(step_c);
    moduleInStr.Append(step_c);     
    
    TString plotStr("DimassRC_");

    if (channel==kMM) {
        cout << "Corrections for DY->mumu cross section (STEP " << step << "):" << endl << endl;
        plotStr.Append("MM");
    }
    else if (channel==kEE) {
        cout << "Corrections for DY->ee cross section (STEP " << step << "):" << endl << endl;
        plotStr.Append("EE");
    }

    TH1* ohists[Nfiles];
    GetCloneHistArray(moduleOutStr.Copy().Append("/"), plotStr.Copy().Append(";1"), channel, ohists);

    TH1* ihists[Nfiles];
    GetCloneHistArray(moduleInStr.Copy().Append("/"), plotStr.Copy().Append(";1"), channel, ihists);

    size_t idx = 14;
    if (channel==kEE)
        idx=17;

    if (!ihists[idx] ||!ohists[idx]) {
        cout << "ERROR in rOutIn: Z sample is missing!" << endl;
        return;
    }

    // variables needed for statistical error
    Double_t a[Nfiles];
    Double_t b[Nfiles];
    for (size_t i=1; i<Nfiles; ++i) {
        a[i] = ohists[i]->Integral(0,ohists[i]->GetNbinsX()+1);
        b[i] = ihists[i]->Integral(0,ihists[i]->GetNbinsX()+1);
    }

    SetWeights(ihists);
    SetWeights(ohists);

    // ratio from whole stack
    Double_t isum =  ihists[0]->Integral(0,ihists[0]->GetNbinsX()+1);
    Double_t osum =  ohists[0]->Integral(0,ohists[0]->GetNbinsX()+1);

    Double_t isumMC = 0;
    Double_t osumMC = 0;

    for (size_t i=1; i<Nfiles; ++i) {
        isumMC += ihists[i]->Integral(0,ihists[i]->GetNbinsX()+1);
        osumMC += ohists[i]->Integral(0,ohists[i]->GetNbinsX()+1);
    }

    cout << "      R(out/in) DATA : " << osum/isum << " +- " << TMath::Sqrt(osum/isum/isum + osum*osum/isum/isum/isum) << endl;

    Double_t w[Nfiles];
    for (size_t i=1; i<Nfiles; ++i) {
        if (a[i]>0)
            w[i] = ohists[i]->Integral(0,ohists[i]->GetNbinsX()+1)/a[i];
        else
            w[i] = 0;
    }

    Double_t wwaSum = 0;
    Double_t waSum = 0;
    Double_t bSum = 0;
    Double_t wbSum = 0;
    for (size_t i=1; i<Nfiles; ++i) {
        wwaSum += w[i]*w[i]*a[i];
        waSum += w[i]*a[i];
        bSum += b[i];
        wbSum += w[i]*b[i];
    }

    Double_t errMC = TMath::Sqrt(wwaSum+(waSum*waSum/bSum))/wbSum;

    cout << "      R(out/in) MC   : " << osumMC/isumMC << " +- " << errMC << endl;

    wwaSum = 0;
    waSum = 0;
    bSum = 0;
    wbSum = 0;
    for (size_t i=idx-2; i<=idx; ++i) {
        wwaSum += w[i]*w[i]*a[i];
        waSum += w[i]*a[i];
        bSum += b[i];
        wbSum += w[i]*b[i];
    }

    Double_t errDY = TMath::Sqrt(wwaSum+(waSum*waSum/bSum))/wbSum;
    Double_t outDY = ohists[idx-2]->Integral(0,ohists[idx-2]->GetNbinsX()+1)+ohists[idx-1]->Integral(0,ohists[idx-1]->GetNbinsX()+1)+ohists[idx]->Integral(0,ohists[idx]->GetNbinsX()+1);
    Double_t inDY  = ihists[idx-2]->Integral(0,ihists[idx-2]->GetNbinsX()+1)+ihists[idx-1]->Integral(0,ihists[idx-1]->GetNbinsX()+1)+ihists[idx]->Integral(0,ihists[idx]->GetNbinsX()+1);

    cout << "      R(out/in) DYMC : " << outDY/inDY    << " +- " << errDY << endl;

    if (channel==kEE) {
        ROutInEE      = outDY/inDY;
        ROutInEEError = errDY;
    } else if (channel==kMM) {
        ROutInMM      = outDY/inDY;
        ROutInMMError = errDY;
    }     
    return;
}



// calculate correction factor to take into account difference between muon and electron selection efficiency
void SetKEff()
{
    TH1* eeHist;
    files[kEE][0]->GetObject("analyzeLeptonPair6/DimassRC_EE;1", eeHist);
    Double_t Nee = eeHist->Integral();

    TH1* mmHist;
    files[kMM][0]->GetObject("analyzeLeptonPair6/DimassRC_MM;1", mmHist);
    Double_t Nmm = mmHist->Integral();

    kEff      = TMath::Sqrt(Nmm/Nee);
    kEffError = TMath::Sqrt(1/4/Nee + Nmm/4/Nee/Nee);

    cout << "Correction for different lepton efficienies:" << endl << endl;
    cout << "            k(mm/ee) : " << kEff    << " +- " << kEffError << endl << endl;

    return;
}



// calculate DY scale factor
void SetDYScaleFactor(const Int_t channel, const Int_t step)
{
    if (channel!=kEE && channel!=kMM) {
        cout << "ERROR in SetDYScaleFactor: selected channel is neither ee nor mumu!" << endl;
        return;
    }
    
    if (step!=7 && step!=8 && step!=9) {
        cout << "ERROR in SetDYScaleFactor: selected step is out of range!" << endl;
        return;
    }    

    TString moduleInStr("analyzeLeptonPairZvetoRegion");
    TString moduleOutStr("analyzeLeptonPair");
    
    char step_c[2]; 
    sprintf(step_c,"%d",step);

    moduleInStr.Append(step_c);
    moduleOutStr.Append(step_c); 
    
    moduleInStr.Append("/");
    moduleOutStr.Append("/");     
       
    TString plotStr("DimassRC_MM");

    Double_t R      = ROutInMM;
    Double_t RError = ROutInMMError;
    Double_t k      = kEff;
    Double_t kErr   = kEffError;
    size_t idx      = 12;

    if (channel==kEE) {
        plotStr = "DimassRC_EE";
        R       = ROutInEE;
        RError  = ROutInEEError;
        k       = 1./k;
        kErr    = kEffError/kEff/kEff;
        idx     = 15;
    }

    TH1* emuHist;
    files[kEM][0]->GetObject(moduleOutStr.Copy().Append("DimassRC_ME;1"), emuHist);
    Double_t NInEMu = emuHist->Integral(emuHist->FindBin(76), emuHist->FindBin(106)-1);

    TH1* inHist;
    files[channel][0]->GetObject(TString(moduleInStr).Append(plotStr).Append(";1"), inHist);
    Double_t NIn = inHist->Integral();

    Double_t NOut      = R*(NIn-.5*k*NInEMu);
    //Double_t NOutError = (NIn-.5*k*NInEMu)*(NIn-.5*k*NInEMu)*(0.5*R)*(0.5*R); // assumed 50% uncertainty on R_out/in
    Double_t NOutError = (NIn-.5*k*NInEMu)*(NIn-.5*k*NInEMu)*(RError)*(RError); // assumed only statistical error on R_out/in
    NOutError += R*R*NIn;
    NOutError += (.5*NInEMu*R)*(.5*NInEMu*R)*(kErr)*(kErr);
    NOutError += (.5*k*R)*(.5*k*R)*NInEMu;
    NOutError = TMath::Sqrt(NOutError);

    TH1* hists[Nfiles];
    GetCloneHistArray(moduleOutStr, plotStr, channel, hists);

    Double_t nevts[3] = {0.,0.,0.};
    for (size_t i=idx; i<=idx+2; ++i) {
        nevts[i-idx] = hists[i]->Integral();
    }

    SetWeights(hists);

    Double_t NOutMC      = 0;
    Double_t NOutMCError = 0;

    for (size_t i=idx; i<=idx+2; ++i) {
        NOutMC += hists[i]->Integral();
        if (nevts[i-idx]>0)
            NOutMCError += hists[i]->Integral()*hists[i]->Integral()/nevts[i-idx];
    }
    NOutMCError = TMath::Sqrt(NOutMCError);  

    if (channel==kMM) {
        if(step==7)
          zMuNorm7 = NOut/NOutMC;
	else if(step==8)
	  zMuNorm8 = NOut/NOutMC;
	else if(step==9)
	  zMuNorm9 = NOut/NOutMC;	  
        Double_t SFError = TMath::Sqrt((NOutError/NOutMC)*(NOutError/NOutMC)+(NOut*NOutError/NOutMC/NOutMC)*(NOut*NOutMCError/NOutMC/NOutMC));
        cout << "            SF(mumu) : " << NOut/NOutMC << " +- " << SFError << endl << endl;
    }
    else if (channel==kEE) {
        if(step==7)
          zElNorm7 = NOut/NOutMC;
	else if(step==8)
	  zElNorm8 = NOut/NOutMC;
	else if(step==9)
	  zElNorm9 = NOut/NOutMC;
        Double_t SFError = TMath::Sqrt((NOutError/NOutMC)*(NOutError/NOutMC)+(NOut*NOutError/NOutMC/NOutMC)*(NOut*NOutMCError/NOutMC/NOutMC));
        cout << "            SF(ee)   : " << NOut/NOutMC << " +- " << SFError << endl << endl;
    }
    return;
}



// helper function to calculate binomial errors
Double_t BinomialError(Double_t numerator, Double_t denominator)
{
    if (numerator>denominator) {
        return 0.;
        cout << "WARNING in BinomialError: efficiency is larger than one!" << endl;
    }

    Double_t error;
    error=TMath::Sqrt((1-numerator/denominator)
                      *numerator/denominator/denominator);

    return error;
}



// function to plot histograms with a ratio (used for b-tagging SF)
void PlotHistsAndRatio(TH1* numeratorHistogram, TH1* denominatorHist, TString title, TString xTitle, TString yTitle) {

    if (!denominatorHist) {
        cout << "ERROR in PlotHistsAndRatio: denominatorHist does not exist" << endl;
    }

    TString yTitle2 = "SF"; // bottom plot y axis title

    TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,800);
    c1->Range(0,0,1,1);

    TH1* nomHist   = (TH1*)numeratorHistogram->Clone();
    TH1* denomHist = (TH1*)denominatorHist->Clone();

    // Create ratio histogram
    TH1* ratioHist = (TH1*)numeratorHistogram->Clone();
    ratioHist->Divide(denomHist);

    // Bottom plot
    TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.32);
    c1_1->Draw();
    c1_1->cd();
    c1_1->SetTopMargin(0.03);
    c1_1->SetBottomMargin(0.3);
    c1_1->SetLeftMargin(0.14);
    c1_1->SetRightMargin(0.04);
    c1_1->SetFillStyle(0);

    ratioHist->Draw();
    ratioHist->SetLineWidth(1.5);
    ratioHist->SetMarkerSize(1.5);
    ratioHist->SetLineColor(kBlack);
    ratioHist->SetMinimum(0.50);
    ratioHist->SetMaximum(1.50);
    ratioHist->GetYaxis()->SetNdivisions(5);
    ratioHist->SetTitle(";"+xTitle+";"+yTitle2);
    ratioHist->GetXaxis()->SetTitleSize(0.14);
    ratioHist->GetXaxis()->SetLabelSize(0.14);
    ratioHist->GetXaxis()->SetTitleOffset(0.9);
    ratioHist->GetYaxis()->SetLabelSize(0.11);
    ratioHist->GetYaxis()->SetTitleSize(0.14);
    ratioHist->GetYaxis()->SetTitleOffset(0.40);
    ratioHist->SetLineWidth(1);
    ratioHist->SetLineColor(kBlack);
    ratioHist->Draw("E1");

    // Top Plot
    c1->cd();
    TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.33,0.99,0.99);
    c1_2->Draw();
    c1_2->cd();
    c1_2->SetTopMargin(0.1);
    c1_2->SetBottomMargin(0.03);
    c1_2->SetLeftMargin(0.14);
    c1_2->SetRightMargin(0.04);
    c1_2->SetFillStyle(0);

    //denominatorHistogram->SetLineWidth(2);
    denomHist->SetLineColor(2);
    denomHist->SetFillColor(2);
    denomHist->SetMarkerSize(0);
    denomHist->Draw("E2");
    denomHist->SetLabelSize(0.0);
    denomHist->GetXaxis()->SetTitleSize(0.00);
    denomHist->GetYaxis()->SetLabelSize(0.07);
    denomHist->GetYaxis()->SetTitleSize(0.08);
    denomHist->GetYaxis()->SetTitleOffset(0.70);
    denomHist->SetMinimum(0.70);
    denomHist->SetMaximum(1.10);
    denomHist->SetTitle(title+";;"+yTitle);
    nomHist  ->SetLineWidth(1.5);
    nomHist  ->SetMarkerSize(1.5);
    nomHist  ->SetLineColor(kBlack);
    nomHist  ->Draw("same");

    c1_2->SetLogy(0);

    c1->Print(outpath.Copy().Append("btagging").Append("/").Append(title));

    delete nomHist;
    delete denomHist;
    delete c1_1;
    delete c1_2;
    delete c1;
    delete ratioHist;
}



// plot b-tag efficiency
void GetBtagEfficiencyInBins(const char* algo, const char* particle, const char* quantity, const char* xtitle, const Double_t bins[], const Int_t nbins)
{
    TString plotStr("correlation_nBtags");
    plotStr.Append(algo);
    plotStr.Append("Vs");
    plotStr.Append(particle);
    plotStr.Append(quantity);

    TH1* hists[Nfiles];
    
    if(GetCloneHistArray("analyzeKinSolutionNoBtagging7/", plotStr, kEM, hists)==0){
      cerr << "WARNING in GetBtagEfficiencyInBins: Histogram " << plotStr << " not found!" << endl;
      return;
    }

    // get the numbers of the bins corresponding to the given bins
    Int_t intBins[nbins+1];
    for (Int_t i=0; i<nbins+1; ++i) {
        intBins[i] = hists[0]->GetYaxis()->FindBin(bins[i]);
    }

    // book output histogram that will be printed
    TH1D* effDataHist = new TH1D("effDataHist","effDataHist",nbins,bins);
    TH1D* effMCHist   = new TH1D("effMCHist",  "effMCHist",  nbins,bins);

    TH1D* eff2DataHist = new TH1D("eff2DataHist","eff2DataHist",nbins,bins);
    TH1D* eff2MCHist   = new TH1D("eff2MCHist",  "eff2MCHist",  nbins,bins);

    plotStr = "correlation_nMatchesVs";
    plotStr.Append(particle);
    plotStr.Append(quantity);

    TH1* nMatchVsNTagsHist;
    GetCloneHist("analyzeKinSolutionNoBtagging7/", plotStr, kEM, 1, nMatchVsNTagsHist);
    AddHist("analyzeKinSolutionNoBtagging7/",      plotStr, kEM, 2, nMatchVsNTagsHist);

    // for each bin and sample a single histogram
    TH1* hists1d[nbins][Nfiles];
    for (Int_t i=0; i<nbins; ++i) {
        for (size_t j=0; j<Nfiles; ++j) {
            TString histname("hists1d_");
            histname.Append(particle).Append(quantity).Append("_");
            histname += i;
            histname.Append("_");
            histname += j;
            hists1d[i][j] = (TH1*)((TH2*)hists[j])->ProjectionX(histname.Data(), intBins[i],intBins[i+1]-1);
        }

        // get fractions alpha_i of events where i jets are matched to the b-jets from ttbar decay
        // nmatch = N(2 leading jets are to b-jets (gen))
        // NTags = #b-tags in 2 leading jets
        Double_t a1 = ((TH2*)nMatchVsNTagsHist)->Integral(2,2,intBins[i],intBins[i+1]-1)/((TH2*)nMatchVsNTagsHist)->Integral(1,3,intBins[i],intBins[i+1]-1);
        Double_t a2 = ((TH2*)nMatchVsNTagsHist)->Integral(3,3,intBins[i],intBins[i+1]-1)/((TH2*)nMatchVsNTagsHist)->Integral(1,3,intBins[i],intBins[i+1]-1);

        Double_t N1 = hists1d[i][1]->Integral(2,3)
                      + hists1d[i][2]->Integral(2,3)
                      + hists1d[i][3]->Integral(2,3); //number of events with >1 b-tag

        Double_t N2 = hists1d[i][1]->Integral(3,3)
                      + hists1d[i][2]->Integral(3,3)
                      + hists1d[i][3]->Integral(3,3); //number of events with 2 b-tags

        Double_t efficiencyMC = 0;
        Double_t effErrorMC   = 0;
        if (N1>0 && N2>=0) {
            efficiencyMC = (2*a2+a1)*N2 / (a2*(N1+N2));
            effErrorMC = (2*a2+a1)/a2 * TMath::Sqrt(N1*N2/(N1+N2)/(N1+N2)/(N1+N2));
        }
        Double_t effMC2      = 1.-(1.-efficiencyMC)*(1.-efficiencyMC);
        Double_t effErrorMC2 = 2*(1.-efficiencyMC)*effErrorMC;

        SetWeights(hists1d[i]);

        N1 = hists1d[i][0]->Integral(2,3);
        N2 = hists1d[i][0]->Integral(3,3);
        Double_t Nbg  = 0;
        for (size_t k=4; k<Nfiles; ++k) {
            Nbg += hists1d[i][k]->Integral(2,3);
        }

        N1 -= Nbg;
        Double_t efficiency = 0;
        Double_t effError   = 0;
        if (N1>0 && N2>=0) {
            efficiency = (2*a2+a1)*N2 / (a2*(N1+N2));
            effError = (2*a2+a1)/a2 * TMath::Sqrt(N1*N2/(N1+N2)/(N1+N2)/(N1+N2));
        }
        Double_t eff2      = 1.-(1.-efficiency)*(1.-efficiency);
        Double_t effError2 = 2*(1.-efficiency)*effError;

        // fill now output histos
        effDataHist->SetBinContent(i+1,efficiency);
        effDataHist->SetBinError(i+1,effError);
        effMCHist->SetBinContent(i+1,efficiencyMC);
        effMCHist->SetBinError(i+1,effErrorMC);

        eff2DataHist->SetBinContent(i+1,eff2);
        eff2DataHist->SetBinError(i+1,effError2);
        eff2MCHist->SetBinContent(i+1,effMC2);
        eff2MCHist->SetBinError(i+1,effErrorMC2);

//         cout.precision(1);
//         cout << "bins number " << i << " from (" << bins[i] << " to " << bins[i+1] << "):" << endl;
//         cout.precision(5);
//         cout << "b-tagging efficiency in MC   = " << efficiencyMC << " +- " << effErrorMC << endl;
//         cout << "b-tagging efficiency in data = " << efficiency << " +- " << effError << endl << endl;
    }

    TString title("btagSF_");
    title.Append(algo);
    title.Append("_");
    title.Append(particle);
    title.Append("_");
    title.Append(quantity);
    title.Append(outform);

    TString ytitle("#epsilon (");
    ytitle.Append(algo);
    ytitle.Append(")");

    PlotHistsAndRatio(effDataHist,effMCHist, title, TString(xtitle), ytitle);

    delete effDataHist;
    delete effMCHist;

    title = "btagSF2_";
    title.Append(algo);
    title.Append("_");
    title.Append(particle);
    title.Append("_");
    title.Append(quantity);
    title.Append(outform);

    ytitle = "1 - (1-#epsilon)^{2} (";
    ytitle.Append(algo);
    ytitle.Append(")");

    PlotHistsAndRatio(eff2DataHist,eff2MCHist, title, TString(xtitle), ytitle);

    delete eff2DataHist;
    delete eff2MCHist;
}



// retrieve the number of events per sample from the TrigReport
// if available, else take default value from fullNEvents.
// If fullNEvents == 0, always take number from TrigReport
Double_t IncompleteSampleScale(Channel_t ch, Int_t fileNo){//, int nEvents) {
    TString filename = files[ch][fileNo]->GetName();
    std::cout << filename << std::endl;
    return 1;
}



// Calculate the efficiency of the kinematic event reconstruction in bins of particle's generated quantities
void PlotKinFitEfficiencyInGeneratorBins(const char* particle, const char* quantity, Int_t channel, const char* xtitle, const Double_t bins[], const Int_t nbins) {

    TString moduleStr("analyzeGenTopEvent");
    TString plotStr("gen_");        
    if (strcmp(particle,"Leptons")==0) {
        plotStr.Append("Lep");
    } else if (strcmp(particle,"Jets")==0) {
        plotStr.Append("B");
    } else if (strcmp(particle,"TopQuarks")==0) {
        plotStr.Append("Top");
    } else {
        plotStr.Append(particle);
    }
    plotStr.Append(quantity);
         
    TH1* hist1; // before kin solution
    TH1* hist2; // after kin solution
    if (channel==kMM) {
        GetCloneHist(moduleStr.Copy().Append("8/"), plotStr, kMM, 1, hist1);
        AddHist(moduleStr.Copy().Append("8/"), plotStr, kMM, 2, hist1);		
        GetCloneHist(moduleStr.Copy().Append("9/"), plotStr, kMM, 1, hist2);
        AddHist(moduleStr.Copy().Append("9/"), plotStr, kMM, 2, hist2);		
    } else if (channel==kEM) {
        GetCloneHist(moduleStr.Copy().Append("8/"), plotStr, kEM, 1, hist1);
        AddHist(moduleStr.Copy().Append("8/"), plotStr, kEM, 2, hist1);		
        GetCloneHist(moduleStr.Copy().Append("9/"), plotStr, kEM, 1, hist2);
        AddHist(moduleStr.Copy().Append("9/"), plotStr, kEM, 2, hist2);	
    } else if (channel==kEE) {
        GetCloneHist(moduleStr.Copy().Append("8/"), plotStr, kEE, 1, hist1);
        AddHist(moduleStr.Copy().Append("8/"), plotStr, kEE, 2, hist1);		
        GetCloneHist(moduleStr.Copy().Append("9/"), plotStr, kEE, 1, hist2);
        AddHist(moduleStr.Copy().Append("9/"), plotStr, kEE, 2, hist2);	
    } else if (channel==kCOMBINED) {
        GetCloneHist(moduleStr.Copy().Append("8/"), plotStr, kMM, 1, hist1);
        AddHist(moduleStr.Copy().Append("8/"), plotStr, kEM, 1, hist1);
        AddHist(moduleStr.Copy().Append("8/"), plotStr, kEE, 1, hist1);
        AddHist(moduleStr.Copy().Append("8/"), plotStr, kMM, 2, hist1);
        AddHist(moduleStr.Copy().Append("8/"), plotStr, kEM, 2, hist1);
        AddHist(moduleStr.Copy().Append("8/"), plotStr, kEE, 2, hist1);		
        GetCloneHist(moduleStr.Copy().Append("9/"), plotStr, kMM, 1, hist2);
        AddHist(moduleStr.Copy().Append("9/"), plotStr, kEM, 1, hist2);
        AddHist(moduleStr.Copy().Append("9/"), plotStr, kEE, 1, hist2);
        AddHist(moduleStr.Copy().Append("9/"), plotStr, kMM, 2, hist2);
        AddHist(moduleStr.Copy().Append("9/"), plotStr, kEM, 2, hist2);
        AddHist(moduleStr.Copy().Append("9/"), plotStr, kEE, 2, hist2);	   		
    } else {
        cout << "ERROR in PlotDifferentialCrossSection: index " << channel << " for channel is out of range!" << endl;
        return;
    }

    if (strcmp(particle,"Leptons")==0 || strcmp(particle,"Jets")==0 || strcmp(particle,"TopQuarks")==0) {

        plotStr = "gen_";

        if (strcmp(particle,"Leptons")==0) {
            plotStr = "LepBar";
        } else if (strcmp(particle,"Jets")==0) {
            plotStr = "BBar";
        } else if (strcmp(particle,"TopQuarks")==0) {
            plotStr = "TopBar";
        }
        plotStr.Append(quantity);

    	if (channel==kMM) {
    	    AddHist(moduleStr.Copy().Append("8/"), plotStr, kMM, 1, hist1);
    	    AddHist(moduleStr.Copy().Append("8/"), plotStr, kMM, 2, hist1);	    
    	    AddHist(moduleStr.Copy().Append("9/"), plotStr, kMM, 1, hist2);
    	    AddHist(moduleStr.Copy().Append("9/"), plotStr, kMM, 2, hist2);	    
    	} else if (channel==kEM) {
    	    AddHist(moduleStr.Copy().Append("8/"), plotStr, kEM, 1, hist1);
    	    AddHist(moduleStr.Copy().Append("8/"), plotStr, kEM, 2, hist1);	    
    	    AddHist(moduleStr.Copy().Append("9/"), plotStr, kEM, 1, hist2);
    	    AddHist(moduleStr.Copy().Append("9/"), plotStr, kEM, 2, hist2);   
    	} else if (channel==kEE) {
    	    AddHist(moduleStr.Copy().Append("8/"), plotStr, kEE, 1, hist1);
    	    AddHist(moduleStr.Copy().Append("8/"), plotStr, kEE, 2, hist1);	    
    	    AddHist(moduleStr.Copy().Append("9/"), plotStr, kEE, 1, hist2);
    	    AddHist(moduleStr.Copy().Append("9/"), plotStr, kEE, 2, hist2);   
    	} else if (channel==kCOMBINED) {
    	    AddHist(moduleStr.Copy().Append("8/"), plotStr, kMM, 1, hist1);
    	    AddHist(moduleStr.Copy().Append("8/"), plotStr, kEM, 1, hist1);
    	    AddHist(moduleStr.Copy().Append("8/"), plotStr, kEE, 1, hist1);
    	    AddHist(moduleStr.Copy().Append("8/"), plotStr, kMM, 2, hist1);
    	    AddHist(moduleStr.Copy().Append("8/"), plotStr, kEM, 2, hist1);
    	    AddHist(moduleStr.Copy().Append("8/"), plotStr, kEE, 2, hist1);	    
    	    AddHist(moduleStr.Copy().Append("9/"), plotStr, kMM, 1, hist2);
    	    AddHist(moduleStr.Copy().Append("9/"), plotStr, kEM, 1, hist2);
    	    AddHist(moduleStr.Copy().Append("9/"), plotStr, kEE, 1, hist2);
    	    AddHist(moduleStr.Copy().Append("9/"), plotStr, kMM, 2, hist2);
    	    AddHist(moduleStr.Copy().Append("9/"), plotStr, kEM, 2, hist2);
    	    AddHist(moduleStr.Copy().Append("9/"), plotStr, kEE, 2, hist2);		    
    	}
    }
    
    // rebin histograms
    TH1* binned1 = hist1->Rebin(nbins, "binned1", bins);
    TH1* binned2 = hist2->Rebin(nbins, "binned2", bins);    
    
    TH1* effHist =  (TH1*)binned1->Clone();
    effHist->Reset();
        
    // don't trust the divide function
    for(Int_t i=1; i<=effHist->GetNbinsX(); ++i){
      Double_t content = binned2->GetBinContent(i)/binned1->GetBinContent(i);
      Double_t error = BinomialError(binned2->GetBinContent(i), binned1->GetBinContent(i));
      effHist->SetBinContent(i,content);
      effHist->SetBinError(i,error);
    }

    effHist->GetXaxis()->SetTitle(xtitle);
    effHist->GetYaxis()->SetTitle("#epsilon_{kin}");    
               
    TString title("kinEfficiency_gen");
    title.Append(particle);
    title.Append(quantity);
    effHist->SetName(title); 
    kinEffHistogramList.Add(effHist);
      
    delete binned1;
    delete binned2;
}



// Calculate the efficiency of the kinematic event reconstruction in bins of particle's reconstructed quantities
void PlotKinFitEfficiencyInRecoBins(const char* particle, const char* quantity, Int_t channel, const char* xtitle, const Double_t bins[], const Int_t nbins) {

    if(strcmp(particle,"Leptons")!=0){
      cout << "ERROR in PlotKinFitEfficiencyInRecoBins: particle '" << particle << "' is not allowed! Up to now only 'Leptons' is implemented!" << endl;
    }

    // get histograms of reconstructed quantity and generated signal
    TString moduleStr("analyzeMuons");
    TString plotStr(quantity);
    plotStr.ToLower();

    TH1* hists1[Nfiles];  // histograms before
    TH1* hists2[Nfiles];  // histograms after  
    
    if (channel==kMM) {
    	GetCloneHistArray(moduleStr.Copy().Append("8/"), plotStr, kMM, hists1);
    	GetCloneHistArray(moduleStr.Copy().Append("9/"), plotStr, kMM, hists2);
    } else if (channel==kEM) {
    	GetCloneHistArray(moduleStr.Copy().Append("8/"), plotStr, kEM, hists1);
    	GetCloneHistArray(moduleStr.Copy().Append("9/"), plotStr, kEM, hists2);
    } else if (channel==kEE) {
    	GetCloneHistArray(moduleStr.Copy().Append("8/"), plotStr, kEE, hists1);
    	GetCloneHistArray(moduleStr.Copy().Append("9/"), plotStr, kEE, hists2);
    } else if (channel==kCOMBINED) {
    	GetCloneHistArray(moduleStr.Copy().Append("8/"), plotStr, kMM, hists1);
    	AddHistArray(moduleStr.Copy().Append("8/"), plotStr, kEM, hists1);
    	AddHistArray(moduleStr.Copy().Append("8/"), plotStr, kEE, hists1);
    	GetCloneHistArray(moduleStr.Copy().Append("9/"), plotStr, kMM, hists2);
    	AddHistArray(moduleStr.Copy().Append("9/"), plotStr, kEM, hists2);
    	AddHistArray(moduleStr.Copy().Append("9/"), plotStr, kEE, hists2);
    } else {
        cout << "ERROR in PlotDifferentialCrossSection: index " << channel << " for channel is out of range!" << endl;
        return;
    }

    // if particle = Leptons then muons and electrons have to be summed
    if (strcmp(particle,"Leptons")==0) {

        moduleStr = "analyzeElecs";	

        if (strcmp(particle,"Leptons")==0) {
            plotStr = "LepBar";
        } else if (strcmp(particle,"Jets")==0) {
            plotStr = "BBar";
        } else if (strcmp(particle,"TopQuarks")==0) {
            plotStr = "TopBar";
        }
        plotStr.Append(quantity);

        if (channel==kMM) {
            AddHistArray(moduleStr.Copy().Append("8/"), plotStr, kMM, hists1);
            AddHistArray(moduleStr.Copy().Append("9/"), plotStr, kMM, hists2);
        } else if (channel==kEM) {
            AddHistArray(moduleStr.Copy().Append("8/"), plotStr, kEM, hists1);
            AddHistArray(moduleStr.Copy().Append("9/"), plotStr, kEM, hists2);
        } else if (channel==kEE) {
            AddHistArray(moduleStr.Copy().Append("8/"), plotStr, kEE, hists1);
            AddHistArray(moduleStr.Copy().Append("9/"), plotStr, kEE, hists2);
        } else if (channel==kCOMBINED) {
            AddHistArray(moduleStr.Copy().Append("8/"), plotStr, kMM, hists1);
            AddHistArray(moduleStr.Copy().Append("8/"), plotStr, kEM, hists1);
            AddHistArray(moduleStr.Copy().Append("8/"), plotStr, kEE, hists1);
            AddHistArray(moduleStr.Copy().Append("9/"), plotStr, kMM, hists2);
            AddHistArray(moduleStr.Copy().Append("9/"), plotStr, kEM, hists2);
            AddHistArray(moduleStr.Copy().Append("9/"), plotStr, kEE, hists2);
        }
    }
    
    Double_t zElCorr = 1.;
    Double_t zMuCorr = 1.;
    Double_t zCorr   = 1.;

    // set weights for histogram before kin reconstruction
    if (doDYcorrection) {
      zElCorr = zElNorm8;
      zMuCorr = zMuNorm8;
      if (channel == kEE) {
        zCorr = zElNorm8;
      }
      else if (channel == kMM) {
        zCorr = zMuNorm8;
      }
      else if (channel == kCOMBINED) {
        // calculate weighted average of ee and mumu correction;
        Double_t w1 = hists1[12]->Integral();
        w1 += hists1[13]->Integral();
        w1 += hists1[14]->Integral();

        Double_t w2 = hists1[12]->Integral();
        w2 += hists1[13]->Integral();
        w2 += hists1[14]->Integral();

        zCorr = (zMuCorr*w1 + zElCorr*w2)/(w1+w2);
      }
    }

    SetWeights(hists1, zElCorr, zMuCorr);    

    // set weights for histogram after kin reconstruction    
    if (doDYcorrection) {
      zElCorr = zElNorm9;
      zMuCorr = zMuNorm9;
      if (channel == kEE) {
        zCorr = zElNorm9;
      }
      else if (channel == kMM) {
        zCorr = zMuNorm9;
      }
      else if (channel == kCOMBINED) {
        // calculate weighted average of ee and mumu correction;
        Double_t w1 = hists2[12]->Integral();
        w1 += hists2[13]->Integral();
        w1 += hists2[14]->Integral();

        Double_t w2 = hists2[12]->Integral();
        w2 += hists2[13]->Integral();
        w2 += hists2[14]->Integral();

        zCorr = (zMuCorr*w1 + zElCorr*w2)/(w1+w2);
      }
    }

    SetWeights(hists2, zElCorr, zMuCorr);      

    // bg-subtracted data hists
    TH1* dataHist1 = hists1[0];
    TH1* dataHist2 = hists2[0];
    
    for(size_t i=3; i<Nfiles; ++i){
      dataHist1->Add(hists1[i],-1.);
      dataHist2->Add(hists2[i],-1.);      
    }
    
    // signal MC hists
    TH1* signalHist1 = hists1[1];
    signalHist1->Add(hists1[2]);
    TH1* signalHist2 = hists2[1];
    signalHist2->Add(hists2[2]);        
          
    // rebin histograms
    dataHist1 = dataHist1->Rebin(nbins, "dataHist1", bins);    
    dataHist2 = dataHist2->Rebin(nbins, "dataHist2", bins);    
    signalHist1 = signalHist1->Rebin(nbins, "signalHist1", bins);
    signalHist2 = signalHist2->Rebin(nbins, "signalHist2", bins);  
     
    TH1* effDataHist =  (TH1*)dataHist1->Clone();
    effDataHist->Reset();
    
    TH1* effSignalHist =  (TH1*)signalHist1->Clone();
    effSignalHist->Reset();    
            
    // don't trust the divide function
    for(Int_t i=1; i<=effDataHist->GetNbinsX(); ++i){
      Double_t content = dataHist2->GetBinContent(i)/dataHist1->GetBinContent(i);
      Double_t error = BinomialError(dataHist2->GetBinContent(i), dataHist1->GetBinContent(i));      
      effDataHist->SetBinContent(i,content);
      effDataHist->SetBinError(i,error);
      
      content = signalHist2->GetBinContent(i)/signalHist1->GetBinContent(i);
      error = BinomialError(signalHist2->GetBinContent(i), signalHist1->GetBinContent(i));      
      effSignalHist->SetBinContent(i,content);
      effSignalHist->SetBinError(i,error);           
    }

    effDataHist->GetXaxis()->SetTitle(xtitle);
    effDataHist->GetYaxis()->SetTitle("#epsilon_{kin}");   

    effSignalHist->GetXaxis()->SetTitle(xtitle);
    effSignalHist->GetYaxis()->SetTitle("#epsilon_{kin}");    
               
    TString title("kinEfficiency_data_");
    title.Append(particle);
    title.Append(quantity);
    effDataHist->SetName(title);    
     
    kinEffHistogramList.Add(effDataHist);
    
    title = "kinEfficiency_signal_";
    title.Append(particle);
    title.Append(quantity);
    effSignalHist->SetName(title);     

    kinEffHistogramList.Add(effSignalHist);

    delete dataHist1;
    delete dataHist2;    
    delete signalHist1;
    delete signalHist2;
    //delete effHist;    
}



// main function
void CombinedCrossSection(char* systematicVariation = 0, int nevents = 0, double xsec = 157.5) {
    for (int i = 0; btagSFAlgos[i]; ++i)
        btagSFMap[btagSFAlgos[i]] = btagSFValues[i];

    CreateOutputDirectories();
    SetupInputFiles();
    
    if (systematicVariation) {
        std::cout << "Systematics: " << systematicVariation << std::endl;
        if (!strcmp(systematicVariation, "scaleUpBG")) scaleUpBG = 1;
        else if (!strcmp(systematicVariation, "scaleDownBG")) scaleDownBG = 1;
        else if (!strcmp(systematicVariation, "scaleUpDY")) scaleUpDY = 1;
        else if (!strcmp(systematicVariation, "scaleDownDY")) scaleDownDY = 1;
        else if (TString(systematicVariation).BeginsWith("fakedata=")) {
            files[kEM][0]= new TFile(systematicVariation+9);
            std::cout << "using file as data: " << files[kEM][0]->GetName() << std::endl;
            dataIsFakeFromMonteCarlo = true;
        }
        else if (nevents > 0) {
            //We have systematics!
            files[kMM][1]=incompleteSystematics(files[kMM][1], new TFile(sysinpath.Copy().Append("mumu_ttbarsignal_").Append(systematicVariation).Append(".root")));
            files[kMM][2]=incompleteSystematics(files[kMM][2], new TFile(sysinpath.Copy().Append("mumu_ttbarviatau_").Append(systematicVariation).Append(".root")));
//             files[kMM][3]=incompleteSystematics(files[kMM][3], new TFile(sysinpath.Copy().Append("mumu_ttbarbg_").Append(systematicVariation).Append(".root")));
            files[kEM][1]=incompleteSystematics(files[kEM][1], new TFile(sysinpath.Copy().Append("emu_ttbarsignal_").Append(systematicVariation).Append(".root")));
            files[kEM][2]=incompleteSystematics(files[kEM][2], new TFile(sysinpath.Copy().Append("emu_ttbarviatau_").Append(systematicVariation).Append(".root")));
//             files[kEM][3]=incompleteSystematics(files[kEM][3], new TFile(sysinpath.Copy().Append("emu_ttbarbg_").Append(systematicVariation).Append(".root")));
            files[kEE][1]=incompleteSystematics(files[kEE][1], new TFile(sysinpath.Copy().Append("ee_ttbarsignal_").Append(systematicVariation).Append(".root")));
            files[kEE][2]=incompleteSystematics(files[kEE][2], new TFile(sysinpath.Copy().Append("ee_ttbarviatau_").Append(systematicVariation).Append(".root")));
//             files[kEE][3]=incompleteSystematics(files[kEE][3], new TFile(sysinpath.Copy().Append("ee_ttbarbg_").Append(systematicVariation).Append(".root")));
            totalEvents[1]=nevents; sampleCrossSection[1]=xsec;
            totalEvents[2]=nevents; sampleCrossSection[2]=xsec;
        }
    }

    // Calculate Z correction SF and rOutIn
    if (doDYcorrection) {
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << endl;
	
	SetKEff();
        SetROutIn(kMM,7);       
        SetDYScaleFactor(kMM,7);
        SetROutIn(kEE,7); 	
        SetDYScaleFactor(kEE,7);
        cout << endl;
		
        SetROutIn(kMM,8);       
        SetDYScaleFactor(kMM,8);
        SetROutIn(kEE,8); 	
        SetDYScaleFactor(kEE,8);
        cout << endl;
		
        SetROutIn(kMM,9);
        SetDYScaleFactor(kMM,9);
        SetROutIn(kEE,9);
        SetDYScaleFactor(kEE,9);
	cout << endl;
        
        zElNorm8 = zElNorm7;
        zElNorm9 = zElNorm7;
        
        zMuNorm8 = zMuNorm7;
        zMuNorm9 = zMuNorm7;
    }

    setHHStyle(*gStyle);
    
    // Print control plots
    if (doPrintControlPlots) CreateControlPlots();
    
    // Calculate differential cross sections
    TGaxis::SetMaxDigits(2);

    // leptons
    const Int_t nbinsLepEta = 6;
    const Double_t binsLepEta[nbinsLepEta+1] = {-2.4, -1.5, -0.8, 0.0, 0.8, 1.5, 2.4};
    const Double_t binCenterLepEta[nbinsLepEta] = {bccAuto-.05, bccAuto-.05, bccAuto+.05, bccAuto+.05, bccAuto+.04, bccAuto+.03};
    PlotDifferentialCrossSections("Leptons", "Eta", "#eta^{l^{+} and l^{-}}",	"#frac{1}{#sigma} #frac{d#sigma}{d#eta^{l^{+} and l^{-}}} ", binsLepEta, nbinsLepEta, binCenterLepEta ); 
    PlotDifferentialCrossSections("Leptons", "Eta", "#eta^{l^{+} and l^{-}}",	"#frac{1}{#sigma} #frac{d#sigma}{d#eta^{l^{+} and l^{-}}} ", binsLepEta, nbinsLepEta, binCenterLepEta, kFALSE ); 
    PlotKinFitEfficiencyInRecoBins("Leptons", "Eta", kCOMBINED, "#eta^{l^{+} and l^{-}}", binsLepEta, nbinsLepEta);
    GetBtagEfficiencyInBins("TCHEL",  "Leptons", "Eta", "#eta^{l^{+} and l^{-}}", binsLepEta, nbinsLepEta);
    
    const Int_t nbinsLepPt = 5;
    const Double_t binsLepPt[nbinsLepPt+1] = {20, 40, 70, 120, 180, 400};
    const Double_t binCenterLepPt[nbinsLepPt] = {bccAuto-2., bccAuto,  bccAuto+3.,  bccAuto+3., bccAuto};    
    PlotDifferentialCrossSections("Leptons", "Pt", "p_{T}^{l^{+} and l^{-}} #left[#frac{GeV}{c}#right]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{T}^{l^{+} and l^{-}}} #left[(#frac{GeV}{c})^{-1}#right]", binsLepPt, nbinsLepPt, binCenterLepPt );
    PlotDifferentialCrossSections("Leptons", "Pt", "p_{T}^{l^{+} and l^{-}} #left[#frac{GeV}{c}#right]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{T}^{l^{+} and l^{-}}} #left[(#frac{GeV}{c})^{-1}#right]", binsLepPt, nbinsLepPt, binCenterLepPt, kFALSE );    
    PlotKinFitEfficiencyInRecoBins("Leptons", "Pt", kCOMBINED, "p_{T}^{l^{+} and l^{-}}", binsLepPt, nbinsLepPt);
    GetBtagEfficiencyInBins("TCHEL",  "Leptons",  "Pt", "p_{T}^{l^{+} and l^{-}}", binsLepPt, nbinsLepPt);
    
    const Int_t nfinebinsLepPt = 10;
    const Double_t finebinsLepPt[nfinebinsLepPt+1] = {20, 30, 40, 55, 70, 95, 120, 160, 180, 250, 400};
    SaveUnfoldingHists("Leptons", "Pt", kMM, binsLepPt, nbinsLepPt, finebinsLepPt, nfinebinsLepPt);
    SaveUnfoldingHists("Leptons", "Pt", kEM, binsLepPt, nbinsLepPt, finebinsLepPt, nfinebinsLepPt);
    SaveUnfoldingHists("Leptons", "Pt", kEE, binsLepPt, nbinsLepPt, finebinsLepPt, nfinebinsLepPt);
    SaveUnfoldingHists("Leptons", "Pt", kCOMBINED, binsLepPt, nbinsLepPt, finebinsLepPt, nfinebinsLepPt);


    // lepton pair
    const Int_t nbinsLepPairPt = 7;
    const Double_t binsLepPairPt[nbinsLepPairPt+1] = {0, 10, 20, 40, 60, 100, 150, 400};
    const Double_t binCenterLepPairPt[nbinsLepPairPt] = {bccAuto, bccAuto, bccAuto, bccAuto+2., bccAuto, bccAuto-2., bccAuto};    
    PlotDifferentialCrossSections("LepPair", "Pt", "p_{T}^{l^{+}l^{-}} #left[#frac{GeV}{c}#right]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{T}^{l^{+}l^{-}}} #left[(#frac{GeV}{c})^{-1}#right]", binsLepPairPt, nbinsLepPairPt, binCenterLepPairPt );
    GetBtagEfficiencyInBins("TCHEL",  "DiLepton", "Pt", "p_{T}^{l^{+}l^{-}} #left[#frac{GeV}{c}#right]", binsLepPairPt, nbinsLepPairPt);

    const Int_t nbinsLepPairMass = 5;
    const Double_t binsLepPairMass[nbinsLepPairMass+1] = {12, 50, 76, 106, 200, 400};
    const Double_t binCenterLepPairMass[nbinsLepPairMass] = {bccAuto-1., bccAuto, bccAuto+2., bccAuto+2., bccAuto};    
    PlotDifferentialCrossSections("LepPair", "Mass", "M^{l^{+}l^{-}} #left[#frac{GeV}{c^{2}}#right]", "#frac{1}{#sigma} #frac{d#sigma}{dM^{l^{+}l^{-}}} #left[(#frac{GeV}{c^{2}})^{-1}#right]", binsLepPairMass, nbinsLepPairMass, binCenterLepPairMass );
    PlotDifferentialCrossSections("LepPair", "Mass", "M^{l^{+}l^{-}} #left[#frac{GeV}{c^{2}}#right]", "#frac{1}{#sigma} #frac{d#sigma}{dM^{l^{+}l^{-}}} #left[(#frac{GeV}{c^{2}})^{-1}#right]", binsLepPairMass, nbinsLepPairMass, binCenterLepPairMass, kFALSE );    
    GetBtagEfficiencyInBins("TCHEL",  "DiLepton", "Mass", "M^{l^{+}l^{-}} #left[#frac{GeV}{c^{2}}#right]", binsLepPairMass, nbinsLepPairMass);

    //const Int_t nbinsLepPairMassJohannes = 2;
    //const Double_t binsLepPairMassJohannes[nbinsLepPairMassJohannes+1] = {60, 120, 400};
    //const Double_t binCenterMassJohannes[nbinsLepPairMassJohannes] = {bccAuto, bccAuto};
    //PlotDifferentialCrossSections("LepPair", "Mass", "M^{l^{+}l^{-}} [GeV]", "#frac{1}{#sigma} #frac{d#sigma}{dM^{l^{+}l^{-}}} #left[(#frac{GeV}{c^{2}})^{-1}#right]", binsLepPairMassJohannes, nbinsLepPairMassJohannes, binCenterMassJohannes, "Johannes_");


    // jets
    const Int_t nbinsJetEta = 6;
    const Double_t binsJetEta[nbinsJetEta+1] = {-2.4, -1.5, -0.8, 0.0, 0.8, 1.5, 2.4};
    const Double_t binCenterJetEta[nbinsJetEta] = {bccAuto, bccAuto-0.05, bccAuto+0.05, bccAuto+0.05, bccAuto+0.05, bccAuto};
    PlotDifferentialCrossSections("Jets", "Eta", "#eta^{b and #bar{b}}", "#frac{1}{#sigma} #frac{d#sigma}{d#eta^{b and #bar{b}}} ", binsJetEta, nbinsJetEta, binCenterJetEta );
    GetBtagEfficiencyInBins("TCHEL", "Jets", "Eta", "#eta_{b/#bar{b}}", binsJetEta, nbinsJetEta);   
    
    const Int_t nbinsJetPt = 5;
    const Double_t binsJetPt[nbinsJetPt+1] = {30, 50, 70, 120, 180, 400};
    const Double_t binCenterJetPt[nbinsJetPt] = {bccAuto, bccAuto, bccAuto, bccAuto, bccAuto};    
    PlotDifferentialCrossSections("Jets", "Pt", "p_{T}^{b and #bar{b}} #left[#frac{GeV}{c}#right]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{T}^{b and #bar{b}}} #left[(#frac{GeV}{c})^{-1}#right]", binsJetPt, nbinsJetPt, binCenterJetPt );
    GetBtagEfficiencyInBins("TCHEL",  "Jets", "Pt", "p_{T,l}", binsJetPt, nbinsJetPt);

  
    // top
    const Int_t nbinsTopRapidity = 4;
    const Double_t binsTopRapidity[nbinsTopRapidity+1] = {-2.5, -1.2, 0.0, 1.2, 2.5};
    const Double_t binCenterTopRapidity[nbinsTopRapidity] = {bccAuto, bccAuto, bccAuto, bccAuto-0.05};    
    PlotDifferentialCrossSections("TopQuarks", "Rapidity", "y^{t and #bar{t}}", "#frac{1}{#sigma} #frac{d#sigma}{dy^{t and #bar{t}}} ", binsTopRapidity, nbinsTopRapidity, binCenterTopRapidity );
    PlotKinFitEfficiencyInGeneratorBins("Top", "Rapidity", kCOMBINED, "generated y^{t and #bar{t}}", binsTopRapidity, nbinsTopRapidity);
   GetBtagEfficiencyInBins("TCHEL",  "Top", "Rapidity", "y^{t and #bar{t}}", binsTopRapidity, nbinsTopRapidity);
    
    const Int_t nbinsTopPt = 4;
    const Double_t binsTopPt[nbinsTopPt+1] = {0, 70, 140, 240, 400};
    const Double_t binCenterTopPt[nbinsTopPt] = {bccAuto-2., bccAuto+3., bccAuto+3., bccAuto+3.};
    PlotDifferentialCrossSections("TopQuarks", "Pt", "p_{T}^{t and #bar{t}} #left[#frac{GeV}{c}#right]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{T}^{t and #bar{t}}} #left[(#frac{GeV}{c})^{-1}#right]", binsTopPt, nbinsTopPt, binCenterTopPt );
    PlotKinFitEfficiencyInGeneratorBins("Top", "Pt", kCOMBINED, "generated p_{T}^{t and #bar{t}} #left[#frac{GeV}{c}#right]", binsTopPt, nbinsTopPt);
    GetBtagEfficiencyInBins("TCHEL",  "Top", "Pt", "p_{T}^{t and #bar{t}} #left[#frac{GeV}{c}#right]", binsTopPt, nbinsTopPt);
    
    const Int_t nfinebinsTopPt = 8;
    const Double_t finebinsTopPt[nfinebinsTopPt+1] = {0, 40, 70, 100, 140, 180, 240, 300, 400};    
    SaveUnfoldingHists("TopQuarks", "Pt", kMM, binsTopPt, nbinsTopPt, finebinsTopPt, nfinebinsTopPt );
    SaveUnfoldingHists("TopQuarks", "Pt", kEM, binsTopPt, nbinsTopPt, finebinsTopPt, nfinebinsTopPt );
    SaveUnfoldingHists("TopQuarks", "Pt", kEE, binsTopPt, nbinsTopPt, finebinsTopPt, nfinebinsTopPt );
    SaveUnfoldingHists("TopQuarks", "Pt", kCOMBINED, binsTopPt, nbinsTopPt, finebinsTopPt, nfinebinsTopPt );


    // ttbar quantities
    const Int_t nbinsTtBarRapidity = 4;
    const Double_t binsTtBarRapidity[nbinsTtBarRapidity+1] = {-2.5, -1.2, 0.0, 1.2, 2.5};
    const Double_t binCenterTtBarRapidity[nbinsTtBarRapidity] = {-1.7, -0.65, 0.72, 1.65};
    PlotDifferentialCrossSections("TtBar", "Rapidity", "y^{t#bar{t}}", "#frac{1}{#sigma} #frac{d#sigma}{dy^{t#bar{t}}}", binsTtBarRapidity, nbinsTtBarRapidity, binCenterTtBarRapidity );
    PlotKinFitEfficiencyInGeneratorBins("TtBar", "Rapidity", kCOMBINED, "generated y^{t#bar{t}}", binsTtBarRapidity, nbinsTtBarRapidity);
    GetBtagEfficiencyInBins("TCHEL",  "TtBar", "Rapidity", "y^{t#bar{t}}", binsTtBarRapidity, nbinsTtBarRapidity);
    
    const Int_t nbinsTtBarPt = 4;
    const Double_t binsTtBarPt[nbinsTtBarPt+1] = {0, 20, 60, 120, 500};
    const Double_t binCenterTtBarPt[nbinsTtBarPt] = {bccAuto, bccAuto, bccAuto, bccAuto};    
    PlotDifferentialCrossSections("TtBar", "Pt", "p_{T}^{t#bar{t}} #left[#frac{GeV}{c}#right]", "#frac{1}{#sigma} #frac{d#sigma}{dp_{T}^{t#bar{t}}} #left[(#frac{GeV}{c})^{-1}#right]", binsTtBarPt, nbinsTtBarPt, binCenterTtBarPt );
    PlotKinFitEfficiencyInGeneratorBins("TtBar", "Pt", kCOMBINED, "generated p_{T}^{t#bar{t}} #left[#frac{GeV}{c}#right]", binsTtBarPt, nbinsTtBarPt);
    GetBtagEfficiencyInBins("TCHEL",  "TtBar", "Pt", "p_{T}^{t#bar{t}} #left[#frac{GeV}{c}#right]", binsTtBarPt, nbinsTtBarPt);

    const Int_t nbinsTtBarMass = 5;
    const Double_t binsTtBarMass[nbinsTtBarMass+1] = {345, 400, 475, 550, 700, 1000};
    const Double_t binCenterTtBarMass[nbinsTtBarMass] = {365, 445, 498, bccAuto, bccAuto};
    PlotDifferentialCrossSections("TtBar", "Mass", "M^{t#bar{t}} #left[#frac{GeV}{c^{2}}#right]", "#frac{1}{#sigma} #frac{d#sigma}{dM^{t#bar{t}}} #left[(#frac{GeV}{c^{2}})^{-1}#right]", binsTtBarMass, nbinsTtBarMass, binCenterTtBarMass );
    PlotKinFitEfficiencyInGeneratorBins("TtBar", "Mass", kCOMBINED, "generated M^{t#bar{t}} #left[#frac{GeV}{c^{2}}#right]", binsTtBarMass, nbinsTtBarMass);
    GetBtagEfficiencyInBins("TCHEL",  "TtBar", "Mass", "M^{t#bar{t}} #left[#frac{GeV}{c^{2}}#right]", binsTtBarMass, nbinsTtBarMass);

    // Calculate inclusive cross sections
    TGaxis::SetMaxDigits(3);    
    
    CalculateInclusiveCrossSections("DEFAULT");
    CalculateInclusiveCrossSections("TCHEL");
    CalculateInclusiveCrossSections("KINTCHEL");


    // put some extra hists to output file
    PutHistToRootFile("analyzeElecs8", "pt", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeElecs8", "pt", kCOMBINED, kinEffHistogramList, kFALSE);    
    
    PutHistToRootFile("analyzeElecs8", "eta", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeElecs8", "eta", kCOMBINED, kinEffHistogramList, kFALSE); 
    
    PutHistToRootFile("analyzeMuons8", "pt", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeMuons8", "pt", kCOMBINED, kinEffHistogramList, kFALSE);    
    
    PutHistToRootFile("analyzeMuons8", "eta", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeMuons8", "eta", kCOMBINED, kinEffHistogramList, kFALSE);         

    PutHistToRootFile("analyzeLeptonPair8", "DimassRC_MM", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeLeptonPair8", "DimassRC_ME", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeLeptonPair8", "DimassRC_EE", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeLeptonPair8", "DimassRC_MM", kCOMBINED, kinEffHistogramList, kFALSE);
    PutHistToRootFile("analyzeLeptonPair8", "DimassRC_ME", kCOMBINED, kinEffHistogramList, kFALSE);
    PutHistToRootFile("analyzeLeptonPair8", "DimassRC_EE", kCOMBINED, kinEffHistogramList, kFALSE);    
    
    
    PutHistToRootFile("analyzeElecs9", "pt", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeElecs9", "pt", kCOMBINED, kinEffHistogramList, kFALSE);    
    
    PutHistToRootFile("analyzeElecs9", "eta", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeElecs9", "eta", kCOMBINED, kinEffHistogramList, kFALSE);      
    
    PutHistToRootFile("analyzeMuons9", "pt", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeMuons9", "pt", kCOMBINED, kinEffHistogramList, kFALSE);    
    
    PutHistToRootFile("analyzeMuons9", "eta", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeMuons9", "eta", kCOMBINED, kinEffHistogramList, kFALSE);
    
    PutHistToRootFile("analyzeLeptonPair9", "DimassRC_MM", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeLeptonPair9", "DimassRC_ME", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeLeptonPair9", "DimassRC_EE", kCOMBINED, kinEffHistogramList);
    PutHistToRootFile("analyzeLeptonPair9", "DimassRC_MM", kCOMBINED, kinEffHistogramList, kFALSE);
    PutHistToRootFile("analyzeLeptonPair9", "DimassRC_ME", kCOMBINED, kinEffHistogramList, kFALSE);
    PutHistToRootFile("analyzeLeptonPair9", "DimassRC_EE", kCOMBINED, kinEffHistogramList, kFALSE);     
    
          
    

    std::cout << ">>> " << "-------------------------------------------" << std::endl;
    std::cout << ">>> " << "Final size of diffXsecHistogramList: " << diffXsecHistogramList.GetEntries() << std::endl << std::endl << std::endl;

    TFile crossOutFile(crossOutfileName,"recreate");
    diffXsecHistogramList.Write();
    crossOutFile.Close();

    std::cout << ">>> " << "-------------------------------------------" << std::endl;
    std::cout << ">>> " << "Final size of unfoldHistogramList: " << unfoldHistogramList.GetEntries() << std::endl << std::endl << std::endl;

    TFile unfoldOutFile(unfoldOutfileName,"recreate");
    unfoldHistogramList.Write();
    unfoldOutFile.Close();

    std::cout << ">>> " << "-------------------------------------------" << std::endl;
    std::cout << ">>> " << "Final size of kinEffHistogramList: " << kinEffHistogramList.GetEntries() << std::endl << std::endl << std::endl;
    
    TFile kinEffOutFile(kinEffOutfileName,"recreate");
    kinEffHistogramList.Write();
    kinEffOutFile.Close();    

    PrintCutflowTable();

    CloseFiles();
}


int main() {
    CombinedCrossSection();
}
