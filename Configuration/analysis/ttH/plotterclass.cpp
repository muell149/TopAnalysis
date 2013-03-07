#include "plotterclass.h"

#include <fstream>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <cmath>

#include <TCanvas.h>
#include <TLegend.h>
#include <TSystem.h>
#include <TExec.h>
#include <TStyle.h>
#include <TMath.h>
#include <TROOT.h>
#include <TGraphErrors.h>
#include <THStack.h>
#include <TFile.h>
#include <TString.h>
#include <TH1.h>

#include "TGaxis.h"
#include "TPaveText.h"

#include "../diLeptonic/utils.h"
#include "higgsUtils.h"
#include <iomanip>



const double Plotter::topxsec_ = 253.849; //again changes with normalization, must be set outside of the class



void Plotter::setLumi(double newLumi)
{
    this->lumi_ = newLumi;
}



void Plotter::DYScaleFactor(TString SpecialComment){

    DYScale_ = {1,1,1,1}; 

    if(!doDYScale_) return; //need to make a switch for control plots that don't want DYScale

    TString nameAppendix = "";
    if ( !SpecialComment.BeginsWith("_post") &&  SpecialComment != "Standard" ){
        std::cout<<"\n\n*******************************************************************"<<std::endl;
        std::cout<<"ERROR: When calculating the DY Scale factor you must specify in which step you want to calculate the DY SF:"<<std::endl;
        std::cout<<" '_postZcut', '_post2jets', '_postMET', '_post1btag', '_postKinReco' or 'Standard' = _postKinReco"<<std::endl;
        std::cout<<"*******************************************************************\n\n"<<std::endl;
        exit(444);
    }
    if (SpecialComment.BeginsWith("_post")){
        nameAppendix = SpecialComment;
    } else if ( SpecialComment == "Standard") {
        nameAppendix = "_postKinReco";
    }

    std::cout<<"\n\nBegin DYSCALE FACTOR calculation at selection step "<<nameAppendix<<std::endl;
    
    std::vector<TString> Vec_Files = InputFileList(Sample::Channel::combined, Sample::Systematic::nominal);//Read the hardcoded list of files
    if(Vec_Files.size()<1) {std::cout<<"WARNING(in DYScaleFactor)!!! No datasets available to calculate DY SF. EXITING!!"<<std::endl; return;}
    
    double NoutEEDYMC=0, NinEEDYMC=0, NoutMuMuDYMC=0, NinMuMuDYMC=0;//Number of events in/out of z-veto region for the DY MC
    double NinEE=0, NinMuMu=0, NinEMu=0;//Number of events in z-veto region for data
    double NinEEloose=0, NinMuMuloose=0;//Number of data events in Z-Veto region with MET cut
    double NinEEMC=0, NinMuMuMC=0;//All other MC events

    for(size_t i=0; i < Vec_Files.size(); i++){
        double LumiWeight = CalcLumiWeight(Vec_Files.at(i));
        //double lumiWeight = Tools::luminosityWeight(sample, lumi_, fileReader_);
        double allWeights=LumiWeight;//calculate here all the flat-weights we apply: Lumi*others*...
        if(Vec_Files.at(i).Contains("ee") || Vec_Files.at(i).Contains("mumu")){
            if(Vec_Files.at(i).Contains("run")){
                TH1D *htemp = fileReader_->GetClone<TH1D>(Vec_Files.at(i), TString("Zh1").Append(nameAppendix));
                TH1D *htemp1 = fileReader_->GetClone<TH1D>(Vec_Files.at(i), "Looseh1");
                Tools::applyFlatWeight(htemp, allWeights);
                Tools::applyFlatWeight(htemp1, allWeights);
                if(Vec_Files.at(i).Contains("ee")){
                    NinEE+=htemp->Integral();
                    NinEEloose+=htemp1->Integral();
                }
                if(Vec_Files.at(i).Contains("mumu")){
                    NinMuMu+=htemp->Integral();
                    NinMuMuloose+=htemp1->Integral();
                }
            }
            else if(Vec_Files.at(i).Contains("dy")){
                if(Vec_Files.at(i).Contains("50inf")){
                    TH1D *htemp = fileReader_->GetClone<TH1D>(Vec_Files.at(i), TString("Zh1").Append(nameAppendix));
                    TH1D *htemp1 = fileReader_->GetClone<TH1D>(Vec_Files.at(i), TString("TTh1").Append(nameAppendix));
                    Tools::applyFlatWeight(htemp, LumiWeight);
                    Tools::applyFlatWeight(htemp1, LumiWeight);
                    if(Vec_Files.at(i).Contains("ee")){
                        NinEEDYMC+=htemp->Integral();
                        NoutEEDYMC+=htemp1->Integral();
                    }
                    if(Vec_Files.at(i).Contains("mumu")){
                        NinMuMuDYMC+=htemp->Integral();
                        NoutMuMuDYMC+=htemp1->Integral();
                    }
                    delete htemp; delete htemp1;
                }
                else{
                    TH1D *htemp = fileReader_->GetClone<TH1D>(Vec_Files.at(i), TString("TTh1").Append(nameAppendix));
                    Tools::applyFlatWeight(htemp, LumiWeight);
                    if(Vec_Files.at(i).Contains("ee")){   NoutEEDYMC+=htemp->Integral();}
                    if(Vec_Files.at(i).Contains("mumu")){ NoutMuMuDYMC+=htemp->Integral();}
                    delete htemp;
                }
            }
            else{
                TH1D *htemp = fileReader_->GetClone<TH1D>(Vec_Files.at(i), TString("Zh1").Append(nameAppendix));
                Tools::applyFlatWeight(htemp, LumiWeight);
                if(Vec_Files.at(i).Contains("ee")){   NinEEMC+=htemp->Integral();   }
                if(Vec_Files.at(i).Contains("mumu")){ NinMuMuMC+=htemp->Integral(); }
                delete htemp;
            }
        }
        
        if(Vec_Files.at(i).Contains("emu") && Vec_Files.at(i).Contains("run")){
            TH1D *htemp = fileReader_->GetClone<TH1D>(Vec_Files.at(i), TString("Zh1").Append(nameAppendix));
            Tools::applyFlatWeight(htemp, LumiWeight);
            NinEMu+=htemp->Integral();
            delete htemp;
        }

    }
    
    double kee = sqrt(NinEEloose/NinMuMuloose);
    double kmumu = sqrt(NinMuMuloose/NinEEloose);
    
    double RoutinEE = NoutEEDYMC/NinEEDYMC;
    double RoutinMuMu = NoutMuMuDYMC/NinMuMuDYMC;
    
    double NoutMCEE = RoutinEE*(NinEE - 0.5*NinEMu*kee);
    double NoutMCMuMu = RoutinMuMu*(NinMuMu - 0.5*NinEMu*kmumu);

    double DYSFEE = NoutMCEE/NoutEEDYMC;
    double DYSFMuMu = NoutMCMuMu/NoutMuMuDYMC;

    std::cout << std::endl;
    std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << std::endl;
    std::cout << "Calculation of DY Scale Factors for '" << name_ << "'  at selection step "<<nameAppendix << std::endl;

    std::cout<<"DYSFEE:                 "<<DYSFEE<<std::endl;
    std::cout<<"DYSFMuMu:               "<<DYSFMuMu<<std::endl;

    std::cout<<"NinEEloose:             "<<NinEEloose<<std::endl;
    std::cout<<"NinMMloose:             "<<NinMuMuloose<<std::endl;

    std::cout<<"kee:                    "<<kee<<" +- "<<0.5*TMath::Sqrt(1./NinMuMuloose + 1./NinEEloose)<<std::endl;
    std::cout<<"kmumu:                  "<<kmumu<<" +- "<<0.5*TMath::Sqrt(1./NinMuMuloose + 1./NinEEloose)<<std::endl;

    std::cout<<"Rout/Rin ee:            "<<RoutinEE<<std::endl;
    std::cout<<"Rout/Rin Mumu:          "<<RoutinMuMu<<std::endl;

    std::cout<<"Est. From Data(ee):     "<<NoutMCEE<<std::endl;
    std::cout<<"Est. From Data(mumu):   "<<NoutMCMuMu<<std::endl;

    std::cout<<"Est. From MC(ee):       "<<NoutEEDYMC<<std::endl;
    std::cout<<"Est. From MC(mumu):     "<<NoutMuMuDYMC<<std::endl;

    std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << std::endl;
    std::cout << std::endl;

    
    DYScale_.at(0)=DYSFEE;
    DYScale_.at(1)=DYSFMuMu;
    DYScale_.at(2)=1.;
    DYScale_.at(3)=(DYSFEE+DYSFMuMu)/2;//not correct, but close, fix later

    std::cout<<"End DYSCALE FACTOR calculation\n"<<std::endl;

}



Plotter::Plotter()
{
    name_ = "defaultName";
    specialComment_ = "Standard";
    rangemin_ = 0;
    rangemax_ = 3;
    YAxis_ = "N_{events}";

    channelLabel_.insert(channelLabel_.begin(),4, "");
    
    //Ivan: Initialize list of systematics
    fileReader_ = RootFileReader::getInstance();
}



void Plotter::setOptions(TString name, TString specialComment, TString YAxis, TString XAxis, int rebin, bool doDYScale, bool logX, bool logY, double ymin, double ymax, double rangemin, double rangemax, int bins, std::vector<double> XAxisbins, std::vector<double> XAxisbinCenters)
{
    name_ = name; //Variable name you want to plot
    specialComment_ = specialComment; 
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

    DYScale_.insert(DYScale_.begin(), 4, 1.);//Initialize the DY scale-factor to (1., 1., 1., 1.)
}



// This method is only used for DY rescaling
std::vector<TString> Plotter::InputFileList(const Sample::Channel& channel, const Sample::Systematic& systematic)
{
    const TString mode(Tools::convertChannel(channel));
    const TString Systematic(Tools::convertSystematic(systematic));
    
    // Use only nominal samples and do not apply systematics
    
    std::vector<TString> FileVector;
    FileVector.clear();
    
    
    if( mode.CompareTo("combined") && mode.CompareTo("ee") && mode.CompareTo("emu") && mode.CompareTo("mumu")){
        std::cout<<"The decay channel you provided is not supported."<<std::endl;
        std::cout<<"Please use: ee, emu, mumu, combined"<<std::endl;
        return FileVector;
    }
    
    if(!mode.CompareTo("combined")){
        std::vector<TString> eemode   = Plotter::InputFileList(Sample::Channel::ee, systematic);
        std::vector<TString> emumode  = Plotter::InputFileList(Sample::Channel::emu, systematic);
        std::vector<TString> mumumode = Plotter::InputFileList(Sample::Channel::mumu, systematic);
        FileVector.insert(FileVector.end(), eemode.begin(), eemode.end());
        FileVector.insert(FileVector.end(), emumode.begin(), emumode.end());
        FileVector.insert(FileVector.end(), mumumode.begin(), mumumode.end());
        return FileVector;
    }

    //data is only stored in the Nominal directory
    FileVector.push_back(TString("selectionRoot/Nominal/").Append(mode.Copy()).Append("/").Append(mode.Copy()).Append("_run2012A.root"));
    FileVector.push_back(TString("selectionRoot/Nominal/").Append(mode.Copy()).Append("/").Append(mode.Copy()).Append("_run2012Arecover.root"));
    FileVector.push_back(TString("selectionRoot/Nominal/").Append(mode.Copy()).Append("/").Append(mode.Copy()).Append("_run2012B.root"));
    FileVector.push_back(TString("selectionRoot/Nominal/").Append(mode.Copy()).Append("/").Append(mode.Copy()).Append("_run2012C_24Aug.root"));
    FileVector.push_back(TString("selectionRoot/Nominal/").Append(mode.Copy()).Append("/").Append(mode.Copy()).Append("_run2012C_PromptReco.root"));
    
    //MC depends on the specific Systematic: Signal systematics only use different signal samples
    TString tempName;
    tempName = TString("selectionRoot/Nominal/") + mode + "/" + mode;
    
    FileVector.push_back(tempName + "_dyee1050.root");
    FileVector.push_back(tempName + "_dyee50inf.root");
    FileVector.push_back(tempName + "_dymumu1050.root");
    FileVector.push_back(tempName + "_dymumu50inf.root");
    FileVector.push_back(tempName + "_singleantitop_tw.root");
    FileVector.push_back(tempName + "_singletop_tw.root");
    FileVector.push_back(tempName + "_wtolnu.root");
    FileVector.push_back(tempName + "_wwtoall.root");
    FileVector.push_back(tempName + "_wztoall.root");
    FileVector.push_back(tempName + "_zztoall.root");
    FileVector.push_back(tempName + "_dytautau1050.root");
    FileVector.push_back(tempName + "_dytautau50inf.root");
    FileVector.push_back(tempName + "_qcdem2030.root");
    FileVector.push_back(tempName + "_qcdem3080.root");
    FileVector.push_back(tempName + "_qcdem80170.root");
    FileVector.push_back(tempName + "_qcdmu15.root");
    
    TString ttbarsignalplustau = tempName + "_ttbarsignalplustau.root";
    TString ttbarbgviatau      = tempName + "_ttbarbgviatau.root";
    TString ttbarbg            = tempName + "_ttbarbg.root";

    FileVector.push_back(ttbarsignalplustau);
    FileVector.push_back(ttbarbg);
    FileVector.push_back(ttbarbgviatau);
    
    return FileVector;
}



bool Plotter::prepareDataset(Sample::Channel& channel, Sample::Systematic& systematic, std::vector<Sample>& v_sample)
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
            double lumiWeight = Tools::luminosityWeight(sample, lumi_, fileReader_);
            Tools::applyFlatWeight(hist, lumiWeight);
            setHHStyle(*gStyle);
            // Clone histogram directly here
            TH1D* histClone = (TH1D*) hist->Clone();
            p_sampleHist = SampleHistPair(sample, histClone);
        }
        v_sampleHistPair_.push_back(p_sampleHist);
    }
    //std::cout<<"Number of samples used for histogram ("<<name_<<"): "<<v_sampleHistPair_.size()<<"\n";
    
    // Adjustments for different channels
    if(channelLabel_.size()<4){channelLabel_.insert(channelLabel_.begin(), 4, "");}
    
    if(channel == Sample::ee){channelType_=0; channelLabel_.at(0)="ee";}
    if(channel == Sample::mumu){channelType_=1; channelLabel_.at(1)="#mu#mu";}
    if(channel == Sample::emu){channelType_=2; channelLabel_.at(2)="e#mu";}
    if(channel == Sample::combined){channelType_=3; channelLabel_.at(3)="Dilepton Combined";}
    
    // Set dataset specific subfolders
    outpathPlots_ = "./Plots";
    subfolderChannel_ = Tools::convertChannel(channel);
    subfolderChannel_.Prepend("/");
    subfolderSpecial_ = "";
    if ( specialComment_.CompareTo("Standard") != 0 ) {
        //subfolderSpecial_ = specialComment_.Prepend("/");
    }
    
    // FIXME: this variable is completely useless, or ?
    DYEntry_ = "Z / #gamma* #rightarrow ee/#mu#mu";
    

    return allHistosAvailable;
}



void Plotter::write(Sample::Channel channel, Sample::Systematic systematic, DrawMode drawMode, std::vector<Sample> v_sample) // do scaling, stacking, legending, and write in file 
{
    if(!prepareDataset(channel, systematic, v_sample)){
        std::cerr<<"ERROR! Cannot find histograms for all datasets, for (channel/systematic): " << Tools::convertChannel(channel) << "/" << Tools::convertSystematic(systematic)
                 <<"\n... skip this plot\n";
        return;
    }
    
    
    TCanvas * canvas = new TCanvas("","");

    THStack * stack = new THStack("def", "def");
    TLegend * legend = new TLegend(0.70,0.55,0.98,0.85);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->SetX1NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength() - 0.25);
    legend->SetY1NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength() - 0.05 - legend->GetNRows()*0.04);
    legend->SetX2NDC(1.0 - gStyle->GetPadRightMargin() - gStyle->GetTickLength());
    legend->SetY2NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength());

    //std::stringstream ss;
    //ss << DYScale_[channelType_];
    //TString scale;
    //scale=(TString)ss.str();
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
    if(drawMode==overlaid){drawHiggsOverlaid = true;}
    else if(drawMode==scaledoverlaid){drawHiggsOverlaid = true; drawHiggsScaled = true;}
    
    
    
    
    
    
    
    
    
    
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


double Plotter::CalcLumiWeight(const TString& WhichSample){
    if (WhichSample.Contains("run")) return 1;
    double lumiWeight=0;
    if(WhichSample!=""){
        double XSection = SampleXSection(WhichSample);
        if(XSection <= 0.){
            std::cout<<"Sample XSection is <0. Can't calculate luminosity weight!! returning"<<std::endl;
            return 0;
        }
        
        //From 'filename' get the number of weighted (MC weights) event processed.
        const TH1 *h_NrOfEvts = fileReader_->Get<TH1>(WhichSample, "weightedEvents");
        double NrOfEvts = h_NrOfEvts->GetBinContent(1);
        lumiWeight = lumi_*XSection/NrOfEvts;
    }
    
    if (lumiWeight == 0) {
        std::cout << WhichSample << " has lumi weight 0\n";
    }

    return lumiWeight;
}



double Plotter::SampleXSection(const TString& filename){
    
    //MC cross sections taken from:
    //  https://twiki.cern.ch/twiki/bin/view/CMS/StandardModelCrossSectionsat8TeV
    //  AN-12/194    AN-12/228
    
    if(filename.Contains("run"))              {return 1;}
    // HIGGSING
    //else if(filename.Contains("ttbar"))       {return topxsec;}
    else if(filename.Contains("ttbar") && !filename.Contains("ttbarH") && !filename.Contains("ttbarW") && !filename.Contains("ttbarZ")){return topxsec_;}
    // ENDHIGGSING
    else if(filename.Contains("single"))      {return 11.1;}
    else if(filename.Contains("ww"))          {return 54.838;}
    else if(filename.Contains("wz"))          {return 33.21;}
    else if(filename.Contains("zz"))          {return 17.654;}
    else if(filename.Contains("1050"))        {return 860.5;}
    else if(filename.Contains("50inf"))       {return 3532.8;}
    else if(filename.Contains("wtolnu"))      {return 36257.2;}
    else if(filename.Contains("qcdmu15"))     {return 3.640E8*3.7E-4;}
    else if(filename.Contains("qcdmu2030"))   {return 2.870E8*6.500E-3;}
    else if(filename.Contains("qcdmu3050"))   {return 6.609E7*12.20E-3;}
    else if(filename.Contains("qcdmu5080"))   {return 8.802E6*21.80E-3;}
    else if(filename.Contains("qcdmu80120"))  {return 1.024E6*39.50E-3;}
    else if(filename.Contains("qcdmu120170")) {return 1.578E5*47.30E-3;}
    else if(filename.Contains("qcdem2030"))   {return 2.886E8*10.10E-3;}
    else if(filename.Contains("qcdem3080"))   {return 7.433E7*62.10E-3;}
    else if(filename.Contains("qcdem80170"))  {return 1.191E6*153.9E-3;}
    else if(filename.Contains("qcdbcem2030")) {return 2.886E8*5.800E-4;}
    else if(filename.Contains("qcdbcem3080")) {return 7.424E7*2.250E-3;}
    else if(filename.Contains("qcdbcem80170")){return 1.191E6*10.90E-3;}
    // HIGGSING
    else if(filename.Contains("ttbarH125inclusive")){return 0.1302;}
    else if(filename.Contains("ttbarH125tobbbar")){return 0.1302*0.577;}
    // ENDHIGGSING
    
    return -1;
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
    label->AddText(Form(text, lumi_/1000, energy));
    label->SetFillStyle(0);
    label->SetBorderSize(0);
    if (textSize!=0) label->SetTextSize(textSize);
    label->SetTextAlign(32);
    label->Draw("same");
}






