#include <fstream>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <cmath>
#include <iomanip>

#include <TCanvas.h>
#include <TLegend.h>
#include <TSystem.h>
#include <TExec.h>
#include <TStyle.h>
#include <TMath.h>
#include <TROOT.h>
#include <THStack.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TGaxis.h>
#include <TPaveText.h>
#include <TH1D.h>

#include "plotterclass.h"
#include "../diLeptonic/utils.h"
#include "higgsUtils.h"




Plotter::Plotter(const Samples& samples, const double& luminosity, DyScaleFactors::DyScaleFactorMap m_dyScaleFactors, const DrawMode& drawMode):
samples_(samples), luminosity_(luminosity),
m_dyScaleFactors_(m_dyScaleFactors), drawMode_(drawMode),
fileReader_(RootFileReader::getInstance()),
name_("defaultName"), rangemin_(0), rangemax_(3),
YAxis_("N_{events}")
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
        const Sample::Systematic& systematic(systematicChannelSamples.first);
        for(auto channelSample : systematicChannelSamples.second){
            const Sample::Channel& channel(channelSample.first);
            std::vector<Sample>& v_sample(channelSample.second);
            if(!this->prepareDataset(channel, systematic, v_sample)){
                std::cerr<<"ERROR! Cannot find histograms for all datasets, for (channel/systematic): "
                         << Tools::convertChannel(channel) << "/" << Tools::convertSystematic(systematic)
                         <<"\n... skip this plot\n";
                return;
            }
            this->write(channel, systematic);
        }
    }
    
    //std::cout<<"\n=== Finishing of plot production\n\n";
}



bool Plotter::prepareDataset(const Sample::Channel& channel, const Sample::Systematic&, const std::vector<Sample>& v_sample)
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
            Tools::applyFlatWeight(hist, lumiWeight);
            setHHStyle(*gStyle);
            // Clone histogram directly here
            TH1D* histClone = (TH1D*) hist->Clone();
            p_sampleHist = SampleHistPair(sample, histClone);
        }
        v_sampleHistPair_.push_back(p_sampleHist);
    }
    //std::cout<<"Number of samples used for histogram ("<<name_<<"): "<<v_sampleHistPair_.size()<<"\n";
    
    
    // Set dataset specific subfolders
    outpathPlots_ = "./Plots";
    subfolderChannel_ = Tools::convertChannel(channel);
    subfolderChannel_.Prepend("/");
    subfolderSpecial_ = "";
    
    return allHistosAvailable;
}



 // do scaling, stacking, legending, and write in file 
void Plotter::write(const Sample::Channel& channel, const Sample::Systematic& systematic)
{
    TCanvas * canvas = new TCanvas("","");

    THStack * stack = new THStack("def", "def");
    TLegend * legend = new TLegend(0.70,0.55,0.98,0.85);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetX1NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength() - 0.25);
    legend->SetY1NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength() - 0.05 - legend->GetNRows()*0.04);
    legend->SetX2NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength());
    legend->SetY2NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength());

    int legchange=0;
    legend->Clear();
    canvas->Clear();
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    canvas->SetName("");
    canvas->SetTitle("");
    
    
    // Here fill colors and line width are adjusted
    for(auto sampleHistPair : v_sampleHistPair_){
        TH1D* tmp_hist = sampleHistPair.second;
        if(rebin_>1) tmp_hist->Rebin(rebin_);
        setStyle(sampleHistPair, true);
    }
    
    
    // Check whether Higgs sample should be drawn overlaid and/or scaled
    bool drawHiggsOverlaid(false);
    bool drawHiggsScaled(false);
    if(drawMode_==overlaid){drawHiggsOverlaid = true;}
    else if(drawMode_==scaledoverlaid){drawHiggsOverlaid = true; drawHiggsScaled = true;}
    
    
    
    
    
    // FIXME: where and how to apply DY scale factors ?
    //if(!doDYScale_) return; //need to make a switch for control plots that don't want DYScale
    //DYScale_.at(0) = m_dyScaleFactors_[nameAppendix][Sample::nominal][Sample::ee];
    //DYScale_.at(1) = m_dyScaleFactors_[nameAppendix][Sample::nominal][Sample::mumu];
    //DYScale_.at(2) = 1.;
    //DYScale_.at(3) = (DYScale_.at(0) + DYScale_.at(1))/2;//not correct, but close, fix later


    
    
    // FIXME: keep temporarily and remove later
    std::vector<bool> v_isHiggsSignal;
    for(auto sampleHistPair : v_sampleHistPair_){
        bool isHiggsSignal(false);
        if(sampleHistPair.first.sampleType() == Sample::SampleType::higgssignal)isHiggsSignal = true;
        v_isHiggsSignal.push_back(isHiggsSignal);
    }
    
    
    
    // FIXME: make it a map (of legendEntry) for generalisation
    TH1D* overlayHist(0);
    
    // Here the shape in the legend is adjusted, and black lines are drawn between samples with different legends,
    // and the stack is created
    // FIXME: works only if first histogram is data...
    // FIXME: put this in own method, and get mcStack, dataHist, vector<overlayHist> ?!
    for(auto i_sampleHistPair = v_sampleHistPair_.begin(); i_sampleHistPair != v_sampleHistPair_.end(); ++i_sampleHistPair){
        auto decrementIterator = i_sampleHistPair;
        if(i_sampleHistPair != v_sampleHistPair_.begin())--decrementIterator;
        auto incrementIterator = i_sampleHistPair;
        if(i_sampleHistPair != v_sampleHistPair_.end())++incrementIterator;
        const Sample::SampleType& sampleType = i_sampleHistPair->first.sampleType();
        const TString& legendEntry = i_sampleHistPair->first.legendEntry();
        TH1D* hist = i_sampleHistPair->second;
        //std::cout<<"IsHiggs: "<<int(sampleType==Sample::SampleType::higgssignal)<<" , "<<drawHiggsOverlaid<<"\n";
        if(sampleType!=Sample::SampleType::data && !(sampleType==Sample::SampleType::higgssignal && drawHiggsOverlaid)){
            //std::cout<<"Legend in mc stack: "<<legendEntry<<"\n";
            if(i_sampleHistPair != v_sampleHistPair_.begin()){
                if(legendEntry != decrementIterator->first.legendEntry()){
                    int distance = std::distance(v_sampleHistPair_.begin(), i_sampleHistPair);
                    legchange = distance;
                    legend->AddEntry(hist, legendEntry,"f");
                }
                else{
                    v_sampleHistPair_[legchange].second->Add(hist);
                }
            }
            
            if(incrementIterator != v_sampleHistPair_.end()){
                if(legendEntry != incrementIterator->first.legendEntry()){
                    hist->SetLineColor(1);
                }
            }
            else{
                hist->SetLineColor(1);
            }
            
            if(legendEntry != decrementIterator->first.legendEntry()){
                hist->SetLineColor(1);
                stack->Add(hist);
            }
        }
        else if(sampleType!=Sample::SampleType::data){
            //std::cout<<"Legend in higgs overlaid: "<<legendEntry<<"\n";
            if(!overlayHist)overlayHist = (TH1D*) hist->Clone();
            else overlayHist->Add(hist);
            overlayHist->SetFillStyle(0);
            overlayHist->SetLineWidth(2);
        }
        else{
            //std::cout<<"Legend in data: "<<legendEntry<<"\n";
            if(i_sampleHistPair == v_sampleHistPair_.begin()){
                legend->AddEntry(hist, legendEntry,"pe");
            }
            else{
                if(legendEntry != decrementIterator->first.legendEntry()){
                    legend->AddEntry(hist, legendEntry,"pe");
                }
                else{
                    // requires first Sample in vector to be of type data
                    v_sampleHistPair_[0].second->Add(hist);
                }
            }
        }
    }
    
    
    SampleHistPairsByLegend m_sampleHistPairsByLegend;
    m_sampleHistPairsByLegend = Tools::associateSampleHistPairsByLegend(v_sampleHistPair_);
//    std::cout<<"Legends: "<<m_sampleHistPairsByLegend.size()<<std::endl;
    THStack* stack2(0);
    std::vector<TH1D*> overlayHists;
    TH1D* dataHist(0);
    TLegend* legend2;
    for(auto sampleHistPairsByLegend : m_sampleHistPairsByLegend){
        const TString& legendEntry(sampleHistPairsByLegend.first);
//        std::cout<<" bla : "<<legendEntry<<"\n";
        TH1D* legendHist(0);
        for(SampleHistPair sampleHistPair : sampleHistPairsByLegend.second){
            if(!legendHist)legendHist = sampleHistPair.second;
            else legendHist->Add(sampleHistPair.second);
        }
        // First scale all the histograms, but what with overlay ones, cannot be scaled beforehand...
        
    }
    
    
    
    TList* list = stack->GetHists();
    //std::cout<<"\nSizes: "<<v_sampleHistPair_.size()<<" , "<<list->GetEntries()<<"\n";
    // Create a histogram with the sum of all stacked hists
    TH1D* stacksum = (TH1D*) list->At(0)->Clone();
    for (int i = 1; i < list->GetEntries(); ++i) { stacksum->Add((TH1D*)list->At(i));}
    // If Higgs signal overlaid: add legend entry
    // If Higgs signal scaled: scale sample and add modified legend entry
    double signalScaleFactor(1);
    std::vector<TString> v_higgsLabel;
    if(drawHiggsScaled){
        std::stringstream ss_scaleFactor;
        signalScaleFactor = stacksum->Integral()/overlayHist->Integral();
        const int precision(signalScaleFactor>=100 ? 0 : 1);
        ss_scaleFactor<<" x"<<std::fixed<<std::setprecision(precision)<<signalScaleFactor;
        overlayHist->Scale(signalScaleFactor);
        for(auto sampleHistPair : v_sampleHistPair_){
            if(sampleHistPair.first.sampleType() == Sample::SampleType::higgssignal){
                TString label(sampleHistPair.first.legendEntry());
                label.Append(ss_scaleFactor.str());
                v_higgsLabel.push_back(label);
                legend->AddEntry(overlayHist, label, "l");
            }
        }
    }
    
    // FIXME: why using this at all (legends are ordered but stack stays the same), isn't it better to have input correctly ?
    // in fact the legend is filled oppositely than the stack, so it is used for turning the order (but not completely, sth. is messed up !?)
    legend = ControlLegend(v_sampleHistPair_, legend, drawHiggsOverlaid, v_higgsLabel);
    
    
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

    v_sampleHistPair_[0].second->SetMinimum(ymin_);

    if(rangemin_!=0 || rangemax_!=0) {v_sampleHistPair_[0].second->SetAxisRange(rangemin_, rangemax_, "X");}

    if(ymax_==0){
        if(logY_){v_sampleHistPair_[0].second->SetMaximum(18  * v_sampleHistPair_[0].second->GetBinContent(v_sampleHistPair_[0].second->GetMaximumBin()));}
        else{v_sampleHistPair_[0].second->SetMaximum(1.5 * v_sampleHistPair_[0].second->GetBinContent(v_sampleHistPair_[0].second->GetMaximumBin()));}
    }
    else{v_sampleHistPair_[0].second->SetMaximum(ymax_);}

    v_sampleHistPair_[0].second->GetXaxis()->SetNoExponent(kTRUE);

    TGaxis::SetMaxDigits(2);


    //Add the binwidth to the yaxis in yield plots (FIXME: works only correctly for equidistant bins)
    TString ytitle = TString(v_sampleHistPair_[0].second->GetYaxis()->GetTitle()).Copy();
    double binwidth = v_sampleHistPair_[0].second->GetXaxis()->GetBinWidth(1);
    std::ostringstream width;
    width<<binwidth;
    if(name_.Contains("Rapidity") || name_.Contains("Eta")){ytitle.Append(" / ").Append(width.str());}
    else if(name_.Contains("pT") || name_.Contains("Mass") || name_.Contains("mass") || name_.Contains("MET") || name_.Contains("HT")){ytitle.Append(" / ").Append(width.str()).Append(" GeV");};
    v_sampleHistPair_[0].second->GetYaxis()->SetTitle(ytitle);
    
    // Draw data histogram and stack and error bars
    v_sampleHistPair_[0].second->Draw("e1");
    stack->Draw("same HIST");
    gPad->RedrawAxis();
    TExec *setex1 = new TExec("setex1","gStyle->SetErrorX(0.5)");//this is frustrating and stupid but apparently necessary...
    setex1->Draw();  // error bars for data
    syshist->SetMarkerStyle(0);
    //syshist->Draw("same,E2");  // error bars for stack (which, stat or combined with syst ?)
    TExec *setex2 = new TExec("setex2","gStyle->SetErrorX(0.)");
    setex2->Draw();  // remove error bars for data in x-direction
    v_sampleHistPair_[0].second->Draw("same,e1");
    if(overlayHist)overlayHist->Draw("same");
    
    // Put additional stuff to histogram
    drawCmsLabels(1, 8);
    drawDecayChannelLabel(channel);
    legend->Draw("SAME");
    drawRatio(v_sampleHistPair_[0].second, stacksum, 0.5, 1.7);

    // Create Directory for Output Plots 
    gSystem->mkdir(outpathPlots_+"/"+subfolderChannel_+"/"+Tools::convertSystematic(systematic), true);
    canvas->Print(outpathPlots_+subfolderChannel_+"/"+Tools::convertSystematic(systematic)+"/"+name_+".eps");
    
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
    TFile out_root(outpathPlots_+subfolderChannel_+"/"+Tools::convertSystematic(systematic)+"/"+name_+"_source.root", "RECREATE");
    v_sampleHistPair_[0].second->Write(name_+"_data");
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



TLegend* Plotter::ControlLegend(std::vector<SampleHistPair>& v_sampleHistPair, TLegend* leg, bool drawHiggsOverlaid, std::vector<TString> v_higgsLabel){
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
    // HIGGSING
    v_orderedLegend.push_back("t#bar{t}H (incl.)");
    v_orderedLegend.push_back("t#bar{t}H (b#bar{b})");
    // ENDHIGGSING
    
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
        for(auto sampleHistPair : v_sampleHistPair){
            const TString& legendEntry(sampleHistPair.first.legendEntry());
            if(orderedLegend != legendEntry)continue;
            const Sample::SampleType& sampleType(sampleHistPair.first.sampleType());
            if(sampleType==Sample::SampleType::data){
                leg->AddEntry(sampleHistPair.second, orderedLegend, "pe");
                break;
            }
            else if(sampleType==Sample::SampleType::higgssignal){
                TString legendTitle(orderedLegend);
                TString legendOptions("f");
                if(drawHiggsOverlaid)legendOptions = "l";
                for(std::vector<TString>::const_iterator i_higgsLabel = v_higgsLabel.begin(); i_higgsLabel != v_higgsLabel.end(); ++i_higgsLabel){
                    if(i_higgsLabel->Contains(legendTitle))legendTitle = *i_higgsLabel;
                }
                leg->AddEntry(sampleHistPair.second, legendTitle, legendOptions);
                break;
            }
            else{
                leg->AddEntry(sampleHistPair.second, orderedLegend, "f");
                break;
            }
        }
    }
    return leg;
}



// Draw label for Decay Channel in upper left corner of plot
void Plotter::drawDecayChannelLabel(const Sample::Channel& channel, double textSize) {
    TPaveText *decayChannel = new TPaveText();

    decayChannel->AddText(Tools::channelLabel(channel).c_str());

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









Plotter::DrawMode
Tools::convertDrawMode(const std::string& drawMode){
    if (drawMode == "stacked") return Plotter::stacked;
    else if (drawMode == "overlaid") return Plotter::overlaid;
    else if (drawMode == "scaledoverlaid") return Plotter::scaledoverlaid;
    else return Plotter::undefined;
}


std::string
Tools::convertDrawMode(const Plotter::DrawMode& drawMode){
    if (drawMode == Plotter::stacked) return "stacked";
    else if (drawMode == Plotter::overlaid) return "overlaid";
    else if (drawMode == Plotter::scaledoverlaid) return "scaledoverlaid";
    else return "";
}



