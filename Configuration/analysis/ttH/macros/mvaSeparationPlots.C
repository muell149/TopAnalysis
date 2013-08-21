#include <vector>
#include <algorithm>
#include <iostream>

#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <TLegend.h>
#include <TString.h>
#include <TPaveStats.h>
#include <Rtypes.h>



void mvaSeparationPlots(const TString& inputFileName, const TString& outputDirectory,
                        const std::vector<TString>& histogramNames, const std::vector<TString>& combinations)
{

TFile* inputFile = TFile::Open(inputFileName);

TCanvas* canvas(0);

TLegend* legend(0);



const TString labelCorrect = "correct";
const TString labelSwapped = "swapped";
const TString labelWrong = "wrong";

const bool drawCorrect = std::find(combinations.begin(), combinations.end(), labelCorrect) != combinations.end();
const bool drawSwapped = std::find(combinations.begin(), combinations.end(), labelSwapped) != combinations.end();
const bool drawWrong = std::find(combinations.begin(), combinations.end(), labelWrong) != combinations.end();





//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++







for(std::vector<TString>::const_iterator i_histName = histogramNames.begin(); i_histName != histogramNames.end(); ++i_histName){
    
    const TString& histName(*i_histName);
    
    // Set up canvas
    canvas = new TCanvas("canvas1");
    canvas->cd();
    //canvas->SetLogy();
    
    // Set up legend
    legend = new TLegend(0.41,0.84,0.76,0.99);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetTextSize(0.04);
    legend->SetMargin(0.12);
    legend->SetFillStyle(1001);
    
    // set up histograms
    std::vector<TH1*> v_hist;
    if(drawCorrect){
        TH1* hist(0);
        inputFile->GetObject(labelCorrect + "_" + histName + ";1", hist);
        hist->SetLineColor(4);
        legend->AddEntry(hist, labelCorrect, "l");
        v_hist.push_back(hist);
    }
    if(drawSwapped){
        TH1* hist(0);
        inputFile->GetObject(labelSwapped + "_" + histName + ";1", hist);
        hist->SetLineColor(3);
        legend->AddEntry(hist, labelSwapped, "l");
        v_hist.push_back(hist);
    }
    if(drawWrong){
        TH1* hist(0);
        inputFile->GetObject(labelWrong + "_" + histName + ";1", hist);
        hist->SetLineColor(2);
        legend->AddEntry(hist, labelWrong, "l");
        v_hist.push_back(hist);
    }
    
    
    // Scale histograms and get minimum and maximum value
    Double_t yMin(99999.);
    Double_t yMax(-99999.);
    for(std::vector<TH1*>::iterator i_hist = v_hist.begin(); i_hist != v_hist.end(); ++i_hist){
        TH1* hist = *i_hist;
        hist->Scale(1./hist->Integral(0, hist->GetNbinsX()+1));
        
        const Double_t yMinHist = hist->GetMinimum();
        const Double_t yMaxHist = hist->GetMaximum();
        if(yMin > yMinHist) yMin = yMinHist;
        if(yMax < yMaxHist) yMax = yMaxHist;
    }
    
    
    // Draw the histograms
    for(std::vector<TH1*>::iterator i_hist = v_hist.begin(); i_hist != v_hist.end(); ++i_hist){
        TH1* hist = *i_hist;
        const bool firstHist = i_hist==v_hist.begin();
        hist->SetLineWidth(2);
        
        if(firstHist){
            hist->SetTitle("");
            hist->GetYaxis()->SetRangeUser(0.,1.4*yMax);
            hist->Draw();
            
            canvas->Modified();
            canvas->Update();
        }
        else{
            hist->Draw("sameS");
            
            canvas->Modified();
            canvas->Update();
        }
    }
    
    // Adjust stats boxes, has to be done only after drawing
    std::vector<TPaveStats*> v_stats;
    for(size_t iHist = 0; iHist < v_hist.size(); ++iHist){
        TH1* hist = v_hist.at(iHist);
        
        TPaveStats* stats = (TPaveStats*)hist->GetListOfFunctions()->FindObject("stats");
        const double y2ndc = 0.99 - static_cast<double>(iHist)*0.21;
        stats->SetY2NDC(y2ndc);
        stats->SetY1NDC(y2ndc-0.2);
        stats->SetLineColor(hist->GetLineColor());
        
        canvas->Modified();
        canvas->Update();
    }
    
    legend->Draw("same");
    canvas->Modified();
    canvas->Update();
    
    const TString plotName(outputDirectory + histName);
    
    canvas->Print(plotName + ".eps");
    canvas->Print(plotName + ".png");
    
    legend->Delete();
    for(size_t iHist = 0; iHist < v_hist.size(); ++iHist) v_hist.at(iHist)->Delete();
    v_hist.clear();
    for(size_t iStats = 0; iStats < v_stats.size(); ++iStats) v_stats.at(iStats)->Delete();
    v_stats.clear();
    canvas->Close();
}

inputFile->Close();

}
