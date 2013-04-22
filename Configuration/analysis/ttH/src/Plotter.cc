#include <fstream>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <iomanip>

#include <TCanvas.h>
#include <TLegend.h>
#include <TExec.h>
#include <TStyle.h>
#include <TMath.h>
#include <TROOT.h>
#include <THStack.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH1D.h>
#include <TGaxis.h>
#include <TPaveText.h>
#include <TH1D.h>

#include "Plotter.h"
#include "../../diLeptonic/src/RootFileReader.h"
#include "../../diLeptonic/src/utils.h"
#include "higgsUtils.h"





/// Folder for Control Plots output
constexpr const char* BaseDIR = "Plots";





Plotter::Plotter(const Samples& samples, const double& luminosity, DyScaleFactors::DyScaleFactorMap m_dyScaleFactors, const DrawMode::DrawMode& drawMode):
samples_(samples), luminosity_(luminosity),
m_dyScaleFactors_(m_dyScaleFactors), drawMode_(drawMode),
fileReader_(RootFileReader::getInstance()),
name_("defaultName"),
bins_(0), rebin_(1),
rangemin_(0), rangemax_(3),
ymin_(0), ymax_(0),
YAxis_(""), XAxis_(""),
logX_(false), logY_(false),
doDYScale_(false)
{}



void Plotter::setOptions(TString name, TString specialComment, TString YAxis, TString XAxis, int rebin, bool doDYScale, bool logX, bool logY, double ymin, double ymax, double rangemin, double rangemax, int bins, std::vector<double> XAxisbins, std::vector<double> XAxisbinCenters)
{
    name_ = name; //Variable name you want to plot
    YAxis_ = YAxis; //Y-axis title
    XAxis_ = XAxis; //X-axis title
    rebin_ = rebin; //Nr. of bins to be merged together
    doDYScale_ = doDYScale; //Apply DY scale factor?
    logX_ = logX; //Draw X-axis in Log scale
    logY_ = logY; //Draw Y-axis in Log scale
    ymin_ = ymin; //Min. value in Y-axis
    ymax_ = ymax; //Max. value in Y-axis
    rangemin_ = rangemin; //Min. value in X-axis
    rangemax_ = rangemax; //Max. value in X-axis
    bins_ = bins; //Number of bins to plot
    XAxisbins_.clear(); 
    XAxisbins_ = XAxisbins; // Bins edges=bins+1
    XAxisbinCenters_.clear();
    XAxisbinCenters_ = XAxisbinCenters; //Central point for BinCenterCorrection=bins

    //Modify the X/Y-axis labels
    if(XAxis_.Contains("band#bar{b}")){//Histogram naming convention has to be smarter
        XAxis_.ReplaceAll("band#bar{b}",11,"b and #bar{b}",13);
    }
    if(XAxis_.Contains("tand#bar{t}")){//Histogram naming convention has to be smarter
        XAxis_.ReplaceAll("tand#bar{t}",11,"t and #bar{t}",13);
    }
    if(XAxis_.Contains("l^{+}andl^{-}")){//Histogram naming convention has to be smarter
        XAxis_.ReplaceAll("l^{+}andl^{-}",13,"l^{+} and l^{-}",15);
    }
    if(YAxis_.Contains("Toppairs")){
        YAxis_.ReplaceAll("Toppairs",8,"Top-quark pairs",15);
    }
    if(YAxis_.Contains("Topquarks")){
        YAxis_.ReplaceAll("Topquarks",9, "Top quarks",10);
    }
    if(YAxis_.Contains("Numberof")){
        YAxis_.ReplaceAll("Numberof", 8, "Number of ",10);
    }
}



void
Plotter::producePlots(){
    //std::cout<<"--- Beginning of plot production\n\n";
    
    const SystematicChannelSamples& m_systematicChannelSample(samples_.getSystematicChannelSamples());
    for(auto systematicChannelSamples : m_systematicChannelSample){
        const Systematic::Systematic& systematic(systematicChannelSamples.first);
        for(auto channelSample : systematicChannelSamples.second){
            const Channel::Channel& channel(channelSample.first);
            std::vector<Sample>& v_sample(channelSample.second);
            if(!this->prepareDataset(v_sample)){
                std::cerr<<"ERROR! Cannot find histograms for all datasets, for (channel/systematic): "
                         << Channel::convertChannel(channel) << "/" << Systematic::convertSystematic(systematic)
                         <<"\n... skip this plot\n";
                return;
            }
            this->write(channel, systematic);
        }
    }
    
    //std::cout<<"\n=== Finishing of plot production\n\n";
}



bool Plotter::prepareDataset(const std::vector<Sample>& v_sample)
{
    
    bool allHistosAvailable(true);
    
    // Associate histogram to dataset if histogram can be found
    v_sampleHistPair_.clear();
    TH1::AddDirectory(kFALSE);
    for(auto sample : v_sample){
        SampleHistPair p_sampleHist;
        TH1D *hist = fileReader_->GetClone<TH1D>(sample.inputFile(), name_, true);
        if (!hist){
            std::cout<<"Histogram ("<<name_<<") not found in file ("<<sample.inputFile()<<")\n";
            p_sampleHist = SampleHistPair(sample, 0);
            allHistosAvailable = false;
        }
        else{
            //Rescaling to the data luminosity
            double lumiWeight = Tools::luminosityWeight(sample, luminosity_, fileReader_);
            if(sample.sampleType() != Sample::data)Tools::applyFlatWeight(hist, lumiWeight);
            // Set style
            setHHStyle(*gStyle);
            // FIXME: do DY reweighting
            if(sample.sampleType() == Sample::dyll && doDYScale_){
                // FIXME: what about sampleType == Sample::dytautau ?
                
                //DYScale_.at(0) = m_dyScaleFactors_[nameAppendix][Sample::nominal][Sample::ee];
                //DYScale_.at(1) = m_dyScaleFactors_[nameAppendix][Sample::nominal][Sample::mumu];
                //DYScale_.at(2) = 1.;
                //DYScale_.at(3) = (DYScale_.at(0) + DYScale_.at(1))/2;//not correct, but close, fix later
            }
            // Clone histogram directly here
            TH1D* histClone = (TH1D*) hist->Clone();
            p_sampleHist = SampleHistPair(sample, histClone);
        }
        v_sampleHistPair_.push_back(p_sampleHist);
    }
    //std::cout<<"Number of samples used for histogram ("<<name_<<"): "<<v_sampleHistPair_.size()<<"\n";
    
    
    return allHistosAvailable;
}



 // do scaling, stacking, legending, and write in file 
void Plotter::write(const Channel::Channel& channel, const Systematic::Systematic& systematic)
{
    // Prepare canvas and legend
    TCanvas* canvas = new TCanvas("","");
    TLegend* legend = new TLegend(0.70,0.55,0.98,0.85);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetX1NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength() - 0.25);
    legend->SetY1NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength() - 0.05 - legend->GetNRows()*0.04);
    legend->SetX2NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength());
    legend->SetY2NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength());
    legend->Clear();
    canvas->Clear();
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    canvas->SetName("");
    canvas->SetTitle("");
    
    
    // Here fill colors and line width are adjusted, and potentially rebinning applied
    for(auto sampleHistPair : v_sampleHistPair_){
        TH1* tmp_hist = sampleHistPair.second;
        if(rebin_>1) tmp_hist->Rebin(rebin_);
        setStyle(sampleHistPair, true);
    }
    
    // Check whether Higgs sample should be drawn overlaid and/or scaled
    bool drawHiggsOverlaid(false);
    bool drawHiggsScaled(false);
    if(drawMode_ == DrawMode::overlaid){drawHiggsOverlaid = true;}
    else if(drawMode_ == DrawMode::scaledoverlaid){drawHiggsOverlaid = true; drawHiggsScaled = true;}
    
    // Loop over all samples and add those with identical legendEntry
    // And sort them into the categories data, Higgs, other
    LegendHistPair dataHist;
    std::vector<LegendHistPair> higgsHists;
    std::vector<LegendHistPair> stackHists;
    TH1D* tmpHist(0);
    for(std::vector<SampleHistPair>::iterator i_sampleHistPair = v_sampleHistPair_.begin();
        i_sampleHistPair != v_sampleHistPair_.end(); ++i_sampleHistPair)
    {
        const Sample::SampleType& sampleType(i_sampleHistPair->first.sampleType());
        const TString& legendEntry(i_sampleHistPair->first.legendEntry());
        TH1* hist = i_sampleHistPair->second;
        
        std::vector<SampleHistPair>::iterator incrementIterator(i_sampleHistPair);
        ++incrementIterator;
        const bool lastHist(incrementIterator == v_sampleHistPair_.end());
        const bool newHist(!tmpHist);
        
        if(newHist)tmpHist = (TH1D*)hist->Clone();
        
        if(lastHist || (legendEntry!=incrementIterator->first.legendEntry())){
            if(!newHist)tmpHist->Add(hist);
            if(sampleType == Sample::data) dataHist = LegendHistPair(legendEntry, tmpHist);
            else if(sampleType == Sample::higgssignal) higgsHists.push_back(LegendHistPair(legendEntry, tmpHist));
            else stackHists.push_back(LegendHistPair(legendEntry, tmpHist));
            tmpHist = 0;
        }
        else{
            if(!newHist)tmpHist->Add(hist);
        }
    }
    
    // Create histogram corresponding to the sum of all stacked histograms
    TH1D* stacksum = (TH1D*) stackHists.at(0).second->Clone();
    for (unsigned int i = 1; i < stackHists.size(); ++i) { stacksum->Add((TH1D*)stackHists.at(i).second);}
    if(!drawHiggsOverlaid) for(auto higgsHist :higgsHists) {stacksum->Add((TH1D*)higgsHist.second);}
    
    // If Higgs signal scaled: scale sample and modify legend entry
    if(drawHiggsScaled){
        for(auto& higgsHist : higgsHists){
            std::stringstream ss_scaleFactor;
            const double signalScaleFactor = stacksum->Integral()/higgsHist.second->Integral();
            if(isnan(signalScaleFactor) || isinf(signalScaleFactor))continue;
            const int precision(signalScaleFactor>=100 ? 0 : 1);
            ss_scaleFactor<<" x"<<std::fixed<<std::setprecision(precision)<<signalScaleFactor;
            higgsHist.second->Scale(signalScaleFactor);
            higgsHist.first.Append(ss_scaleFactor.str());
        }
    }
    
    // If Higgs samples should be stacked, add them to stack histograms and clear Higgs vector
    if(!drawHiggsOverlaid){
        stackHists.insert(stackHists.end(), higgsHists.begin(), higgsHists.end());
        higgsHists.clear();
    }
    
    // Create the stack and add entries to legend
    THStack* stack = new THStack("def", "def");
    legend->AddEntry(dataHist.second, dataHist.first,"pe");
    for(auto stackHist : stackHists){
        stackHist.second->SetLineColor(1);
        legend->AddEntry(stackHist.second, stackHist.first,"f");
        stack->Add(stackHist.second);
    }
    for(auto higgsHist : higgsHists){
        higgsHist.second->SetFillStyle(0);
        higgsHist.second->SetLineWidth(2);
        legend->AddEntry(higgsHist.second, higgsHist.first,"l");
    }
    
    // In fact the legend is filled oppositely than the stack, so this is used for turning the order (but not completely)
//    legend = ControlLegend(dataHist, stackHists, higgsHists, legend);
    
    
    
    // FIXME: is this histo for error band on stack? but it is commented out ?!
    TH1D* syshist =0;
    syshist = (TH1D*)stacksum->Clone();
    for(Int_t i=0; i<=syshist->GetNbinsX(); ++i){
        Double_t binc = 0;
        binc += stacksum->GetBinContent(i);
        syshist->SetBinContent(i, binc);
    }
    syshist->SetFillStyle(3004);
    syshist->SetFillColor(kBlack);
    
    // Set x and y axis
    if(logY_)canvas->SetLogy();

    dataHist.second->SetMinimum(ymin_);

    if(rangemin_!=0 || rangemax_!=0) {dataHist.second->SetAxisRange(rangemin_, rangemax_, "X");}

    if(ymax_==0){
        if(logY_){dataHist.second->SetMaximum(18  * dataHist.second->GetBinContent(dataHist.second->GetMaximumBin()));}
        else{dataHist.second->SetMaximum(1.5 * dataHist.second->GetBinContent(dataHist.second->GetMaximumBin()));}
    }
    else{dataHist.second->SetMaximum(ymax_);}

    dataHist.second->GetXaxis()->SetNoExponent(kTRUE);

    TGaxis::SetMaxDigits(2);


    //Add the binwidth to the yaxis in yield plots (FIXME: works only correctly for equidistant bins)
    TString ytitle = TString(dataHist.second->GetYaxis()->GetTitle()).Copy();
    double binwidth = dataHist.second->GetXaxis()->GetBinWidth(1);
    std::ostringstream width;
    width<<binwidth;
    if(name_.Contains("Rapidity") || name_.Contains("Eta")){ytitle.Append(" / ").Append(width.str());}
    else if(name_.Contains("pT") || name_.Contains("Mass") || name_.Contains("mass") || name_.Contains("MET") || name_.Contains("HT")){ytitle.Append(" / ").Append(width.str()).Append(" GeV");};
    dataHist.second->GetYaxis()->SetTitle(ytitle);
    
    // Draw data histogram and stack and error bars
    dataHist.second->Draw("e1");
    stack->Draw("same HIST");
    gPad->RedrawAxis();
    TExec *setex1 = new TExec("setex1","gStyle->SetErrorX(0.5)");//this is frustrating and stupid but apparently necessary...
    setex1->Draw();  // error bars for data
    syshist->SetMarkerStyle(0);
    //syshist->Draw("same,E2");  // error bars for stack (which, stat or combined with syst ?)
    TExec *setex2 = new TExec("setex2","gStyle->SetErrorX(0.)");
    setex2->Draw();  // remove error bars for data in x-direction
    dataHist.second->Draw("same,e1");
    for(auto higgsHist : higgsHists){
        higgsHist.second->Draw("same");
    }
    
    // Put additional stuff to histogram
    drawCmsLabels(1, 8);
    drawDecayChannelLabel(channel);
    legend->Draw("SAME");
    drawRatio(dataHist.second, stacksum, 0.5, 1.7);

    // Create Directory for Output Plots and write them
    const TString eventFileString = Tools::assignFolder(BaseDIR, channel, systematic);
    canvas->Print(eventFileString+name_+".eps");
    
    // Prepare additional histograms for root-file
    TH1 *sumMC = 0; 
    TH1 *sumSignal = 0;
    for(auto sampleHistPair : v_sampleHistPair_){
        if(sampleHistPair.first.sampleType() == Sample::SampleType::higgssignal){
            if (sumSignal) sumSignal->Add(sampleHistPair.second);
            else sumSignal = static_cast<TH1*>(sampleHistPair.second->Clone());
            // Do not add Higgs samples to sumMC (all MC samples) in case of overlaid drawing
            if(drawHiggsOverlaid)continue;
        }
        if(sampleHistPair.first.sampleType() != Sample::SampleType::data){
            if (sumMC) sumMC->Add(sampleHistPair.second);
            else sumMC = static_cast<TH1*>(sampleHistPair.second->Clone());
        }
    }
    sumMC->SetName(name_);
    
    //save Canvas AND sources in a root file
    TFile out_root(eventFileString+name_+"_source.root", "RECREATE");
    dataHist.second->Write(name_+"_data");
    sumSignal->Write(name_+"_signalmc");
    sumMC->Write(name_+"_allmc");
    canvas->Write(name_ + "_canvas");
    out_root.Close();
    
    canvas->Clear();
    legend->Clear();
    delete canvas;
    delete legend;
}



void Plotter::setStyle(SampleHistPair& sampleHistPair, bool isControlPlot)
{
    TH1* hist(sampleHistPair.second);
    
    hist->SetFillColor(sampleHistPair.first.color());
    hist->SetLineColor(sampleHistPair.first.color());
    hist->SetLineWidth(1);
    
    if(XAxis_ == "-")XAxis_ = hist->GetXaxis()->GetTitle();
    if(YAxis_ == "-")YAxis_ = hist->GetYaxis()->GetTitle();
    
    if(sampleHistPair.first.sampleType() == Sample::SampleType::data){
        hist->SetFillColor(0);
        hist->SetMarkerStyle(20);
        hist->SetMarkerSize(1.);
        hist->SetLineWidth(1);
        hist->GetXaxis()->SetLabelFont(42);
        hist->GetYaxis()->SetLabelFont(42);
        hist->GetXaxis()->SetTitleFont(42);
        hist->GetYaxis()->SetTitleFont(42);
        hist->GetYaxis()->SetTitleOffset(1.7);
        hist->GetXaxis()->SetTitleOffset(1.25);
        if ((name_.Contains("pT") || name_.Contains("Mass")) && !name_.Contains("Rapidity")) {
            hist->GetXaxis()->SetTitle(XAxis_+" #left[GeV#right]");
            hist->GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d#sigma}{d"+XAxis_+"}"+" #left[GeV^{-1}#right]"); 
        } else {
            hist->GetXaxis()->SetTitle(XAxis_);
            hist->GetYaxis()->SetTitle("#frac{1}{#sigma} #frac{d#sigma}{d"+XAxis_+"}");     
        }
        if (isControlPlot) hist->GetYaxis()->SetTitle(YAxis_);
    }
}



TLegend* Plotter::ControlLegend(const LegendHistPair& dataHist, const std::vector<LegendHistPair>& stackHists, const std::vector<LegendHistPair>& higgsHists, TLegend* leg){
    //hardcoded ControlPlot legend
    std::vector<TString> v_orderedLegend;
    v_orderedLegend.push_back("Data");
    v_orderedLegend.push_back("t#bar{t} Signal");
    v_orderedLegend.push_back("t#bar{t} Other");
    v_orderedLegend.push_back("Single Top");
    v_orderedLegend.push_back("W+Jets");
    v_orderedLegend.push_back("Z / #gamma* #rightarrow ee/#mu#mu");
    v_orderedLegend.push_back("Z / #gamma* #rightarrow #tau#tau");
    v_orderedLegend.push_back("Diboson");
    v_orderedLegend.push_back("QCD Multijet");
    v_orderedLegend.push_back("t#bar{t}H (incl.)");
    v_orderedLegend.push_back("t#bar{t}H (b#bar{b})");
    
    leg->Clear();
    leg->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.25);
    leg->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.30);
    leg->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength());
    leg->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
    leg->SetTextFont(42);
    leg->SetTextSize(0.03);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextAlign(12);
    for(auto orderedLegend : v_orderedLegend){
        if(dataHist.first.Contains(orderedLegend)){
            leg->AddEntry(dataHist.second, dataHist.first, "pe");
            continue;
        }
        for(auto stackHist : stackHists){
            if(stackHist.first.Contains(orderedLegend)){
                leg->AddEntry(stackHist.second, stackHist.first, "f");
                break;
            }
        }
        for(auto higgsHist : higgsHists){
            if(higgsHist.first.Contains(orderedLegend)){
                leg->AddEntry(higgsHist.second, higgsHist.first, "l");
                break;
            }
        }
    }
    return leg;
}



// Draw label for Decay Channel in upper left corner of plot
void Plotter::drawDecayChannelLabel(const Channel::Channel& channel, double textSize) {
    TPaveText *decayChannel = new TPaveText();

    decayChannel->AddText(Channel::channelLabel(channel).c_str());

    decayChannel->SetX1NDC(      gStyle->GetPadLeftMargin() + gStyle->GetTickLength()        );
    decayChannel->SetY1NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength() - 0.05 );
    decayChannel->SetX2NDC(      gStyle->GetPadLeftMargin() + gStyle->GetTickLength() + 0.15 );
    decayChannel->SetY2NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength()        );

    decayChannel->SetFillStyle(0);
    decayChannel->SetBorderSize(0);
    if (textSize!=0) decayChannel->SetTextSize(textSize);
    decayChannel->SetTextAlign(12);
    decayChannel->Draw("same");
}



// Draw official labels (CMS Preliminary, luminosity and CM energy) above plot
void Plotter::drawCmsLabels(int cmsprelim, double energy, double textSize) {

    const char *text;
    if(cmsprelim ==2 ) {//Private work for PhDs students
        text = "Private Work, %2.1f fb^{-1} at #sqrt{s} = %2.f TeV";
    } else if (cmsprelim==1) {//CMS preliminary label
        text = "CMS Preliminary, %2.1f fb^{-1} at #sqrt{s} = %2.f TeV";
    } else {//CMS label
        text = "CMS, %2.1f fb^{-1} at #sqrt{s} = %2.f TeV";
    }
    
    TPaveText *label = new TPaveText();
    label->SetX1NDC(gStyle->GetPadLeftMargin());
    label->SetY1NDC(1.0-gStyle->GetPadTopMargin());
    label->SetX2NDC(1.0-gStyle->GetPadRightMargin());
    label->SetY2NDC(1.0);
    label->SetTextFont(42);
    label->AddText(Form(text, luminosity_/1000, energy));
    label->SetFillStyle(0);
    label->SetBorderSize(0);
    if (textSize!=0) label->SetTextSize(textSize);
    label->SetTextAlign(32);
    label->Draw("same");
}










