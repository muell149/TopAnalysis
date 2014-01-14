#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <sstream>
#include "../include/ScaleFactors.h"

#include <TSystem.h>
#include <TFile.h>
#include <TList.h>
#include <TKey.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH2.h>
#include <TSelectorList.h>
#include <TString.h>
#include <TObjArray.h>
#include <TRandom3.h>
#include <Rtypes.h>
#include <TMath.h>

#include "BTagUtils.h"
#include "classes.h"
#include "utils.h"



BTagSFGeneric::BTagSFGeneric(const char* btagEfficiencyInputDir,
                             const char* btagEfficiencyOutputDir,
                             const std::vector<std::string>& channels,
                             TString systematic):
inputDirName_(btagEfficiencyInputDir),
outputDirName_(btagEfficiencyOutputDir),
fileName_("ttbarsignalplustau.root"),
systematic_(nominal)
{
    std::cout<<"--- Beginning preparation of b-tagging scale factors\n";
    if (systematic == "" || systematic.Contains("PDF") || systematic.Contains("closure")) systematic = "Nominal";
    // Check if all relevant input files are available
    bool allInputFilesAvailable(true);
    for(const auto& channel : channels){
        //FIXME: Change "Nominal" to the enum value when it is implemented
        std::string btagInputFile = common::accessFolder(inputDirName_.c_str(),channel, "Nominal", true).append(channel).append("_").append(fileName_);
        if(btagInputFile.length() < fileName_.length()+channel.length()+2) allInputFilesAvailable = false;

        ifstream inputFileStream;
        if(allInputFilesAvailable) inputFileStream.open(btagInputFile);
        if(!inputFileStream.is_open()){
            std::cout<< "******************************************************\n"
                     << "Required bTag efficiency files don't exist. Running without btagsf!!!\n"
                     << "To create the file, run (for each systematic 'SYST'):\n"
                     << "\t> ./build/load_Analysis -f ttbarsignalplustau.root -c emu -s SYST\n"
                     << "\t> ./build/load_Analysis -f ttbarsignalplustau.root -c ee -s SYST\n"
                     << "\t> ./build/load_Analysis -f ttbarsignalplustau.root -c mumu -s SYST\n"
                     << " and move the selectionRoot/BTagEff directory to the cwd:\n"
                     << "\t> mv selectionRoot/BTagEff .\n"
                     << "This error is NOT fatal, not applying any b-tag rescaling\n"
                     << "*******************************************************\n";
            allInputFilesAvailable = false;
            break;
        }
    }
    if(!allInputFilesAvailable){
        std::cout<<"Not all input files for b-tagging efficiencies available\n"
                 <<"\t-->  Efficiencies will not be used, but produced in Analysis\n";
        setMakeEff(true);
    } else setMakeEff(false);

    // Set systematic if it is an allowed one for btag efficiencies, else set to nominal
    if(systematic == "BTAG_UP") systematic_ = BTagSFGeneric::btag_up;
    else if(systematic == "BTAG_DOWN") systematic_ = BTagSFGeneric::btag_down;
    else if(systematic == "BTAG_PT_UP") systematic_ = BTagSFGeneric::btagPt_up;
    else if(systematic == "BTAG_PT_DOWN") systematic_ = BTagSFGeneric::btagPt_down;
    else if(systematic == "BTAG_ETA_UP") systematic_ = BTagSFGeneric::btagEta_up;
    else if(systematic == "BTAG_ETA_DOWN") systematic_ = BTagSFGeneric::btagEta_down;
    else if(systematic == "BTAG_LJET_UP") systematic_ = BTagSFGeneric::btagLjet_up;
    else if(systematic == "BTAG_LJET_DOWN") systematic_ = BTagSFGeneric::btagLjet_down;
    else if(systematic == "BTAG_LJET_PT_UP") systematic_ = BTagSFGeneric::btagLjetPt_up;
    else if(systematic == "BTAG_LJET_PT_DOWN") systematic_ = BTagSFGeneric::btagLjetPt_down;
    else if(systematic == "BTAG_LJET_ETA_UP") systematic_ = BTagSFGeneric::btagLjetEta_up;
    else if(systematic == "BTAG_LJET_ETA_DOWN") systematic_ = BTagSFGeneric::btagLjetEta_down;
    else if(systematic == "BTAG_BEFF_UP") systematic_ = BTagSFGeneric::btagBeff_up;
    else if(systematic == "BTAG_BEFF_DOWN") systematic_ = BTagSFGeneric::btagBeff_down;
    else if(systematic == "BTAG_CEFF_UP") systematic_ = BTagSFGeneric::btagCeff_up;
    else if(systematic == "BTAG_CEFF_DOWN") systematic_ = BTagSFGeneric::btagCeff_down;
    else if(systematic == "BTAG_LEFF_UP") systematic_ = BTagSFGeneric::btagLeff_up;
    else if(systematic == "BTAG_LEFF_DOWN") systematic_ = BTagSFGeneric::btagLeff_down;
    else systematic_= BTagSFGeneric::nominal;
    
    std::cout<<"=== Finishing preparation of b-tagging scale factors\n\n";
}



bool BTagSFGeneric::makeEfficiencies()
{
    return getMakeEff();
}



void BTagSFGeneric::prepareBTags(TSelectorList* output, const std::string& channel)
{
    //FIXME: Change "Nominal" to the enum value when it is implemented
    std::string inputFileName;
    if(!getMakeEff()) inputFileName = common::accessFolder(inputDirName_.c_str(), channel, "Nominal", true).append(channel).append("_").append(fileName_);
    else inputFileName = common::assignFolder(outputDirName_.c_str(), channel, "Nominal").append(channel).append("_").append(fileName_);
    std::string sampleName(inputFileName);
    sampleName.erase(0,inputDirName_.length());
    while(sampleName.at(0) == '/') sampleName.erase(0,1);

    // Set pointer to output, so that histograms are owned by it
    selectorList_ = output;

    // Stopping if no efficiency histograms need to be read (production mode)
    if(getMakeEff()) {
        setSampleName(sampleName);
        return;
    }


    std::vector<TH2D> histos;
    std::vector<TH2D> effhistos;
    std::vector<float> medians;

    // Load per-jet efficiencies file
    TFile file(inputFileName.c_str(),"READ");

    // Disabling referencing histograms to gDirectory to prevent crashing when closing the root file
    TH1::AddDirectory(false);
    TH2D* tempHisto;
    // Reading the tag and efficiency histograms from the file and adding them to the maps in proper order
    for(int id = 0; ; ++id) {
        std::string histoName = histoNameAtId(id, histoTypes::tag);
        if(histoName != "") {
            file.GetObject(histoName.c_str(), tempHisto);
            if(!tempHisto) 
                throw std::runtime_error("BTagSFGeneric::prepareBTags Couldn't find all [tag] histograms in the input root file");
            histos.push_back(*tempHisto);
            tempHisto = 0;
        }
        
        std::string effHistoName = histoNameAtId(id, histoTypes::eff);
        if(effHistoName != "") {
            file.GetObject(effHistoName.c_str(), tempHisto);
            if(!tempHisto) 
                throw std::runtime_error("BTagSFGeneric::prepareBTags Couldn't find all [eff] histograms in the input root file");
            effhistos.push_back(*tempHisto);
        }
        
        if(histoName == "" && effHistoName == "") break;
    }
    // Reading and extracting madian values from the histogram
    TH1* medianHisto;
    file.GetObject("medians", medianHisto);
    if(!medianHisto) throw std::runtime_error("BTagSFGeneric::prepareBTags Couldn't find [medians] histogram in the input root file");
    for(int i = 0; i<medianHisto->GetNbinsX(); ++i) medians.push_back((float)medianHisto->GetBinContent(i+1));

    histos_[sampleName] = histos;
    effhistos_[sampleName] = effhistos;
    medianMap_[sampleName] = medians;

    file.Close();

    if(setSampleName(sampleName) < 0) throw std::runtime_error("BTagSFGeneric::prepareBTags Tried to set a non-existing sampleName");

}




void BTagSFGeneric::indexOfBtags(std::vector<int>& bjetIndices,
                                 const std::vector<int>& jetIndices,
                                 const VLV& jets,
                                 const std::vector<int>& jetPartonFlavours,
                                 const std::vector<double>& btagDiscriminants)const
{
    bjetIndices.clear();

    std::vector<int> tagged_indices;
    for(const int index : jetIndices){
        //Skip jets where there is no partonFlavour
        if(jetPartonFlavours.at(index) == 0) continue;
        LV jet = jets.at(index);

        // Preparing a seed for the random jet retagging
        const unsigned int seed = std::abs( static_cast<int>( 1.e6*sin( 1.e6*jet.Phi() ) ) );
        bool isTagged = jetIsTagged( jet.pt(), std::fabs(jet.eta()), jetPartonFlavours.at(index), btagDiscriminants.at(index), seed );
        if(isTagged) tagged_indices.push_back(index);
    }
    bjetIndices = tagged_indices;
}




double BTagSFGeneric::calculateBtagSF(const std::vector<int>& jetIndices,
                                      const VLV& jets,
                                      const std::vector<int>& jetPartonFlavours)
{
    resetCounter();
    for(const int index : jetIndices){
        countJet(jets.at(index).pt(), std::fabs(jets.at(index).eta()), jetPartonFlavours.at(index));
    }

    // per-event SF calculation
    double scale_factor = getEventSF();

    if(std::fabs(scale_factor-1.) > 0.05) scale_factor = 1.;

    return scale_factor;
}




void BTagSFGeneric::fillBtagHistograms(const std::vector<int>& jetIndices,
                                          const std::vector<double>& bTagDiscriminant,
                                          const VLV& jets,
                                          const std::vector<int>& jetPartonFlavours,
                                          const double weight)
{
    for(const int index : jetIndices){
        fillEff(jets.at(index).pt(), std::fabs(jets.at(index).eta()), std::abs(jetPartonFlavours.at(index)), bTagDiscriminant.at(index), weight);
    }
}



void BTagSFGeneric::produceBtagEfficiencies(const std::string& channel)
{
    //FIXME: Change "Nominal" to the enum value when it is implemented
    std::string outputFileName = common::assignFolder(outputDirName_.c_str(), channel, "Nominal").append(channel).append("_").append(fileName_);
    std::string sampleName(outputFileName);
    sampleName.erase(0, outputDirName_.length());
    while(sampleName.at(0) == '/') sampleName.erase(0, 1);

    TFile file(outputFileName.c_str(),"RECREATE");

    // Creating the histograms
    makeEffs();

    // Writing each histogram to file
    std::vector<TH2D> histos = histos_.at(sampleName);
    for(TH2D histo : histos) {
        histo.Write();
    }

    // Writing each efficiency hitogram to file
    std::vector<TH2D> effhistos = effhistos_.at(sampleName);
    for(TH2D histo : effhistos) {
        histo.Write();
    }
    
    // Writing medians to the histogram and then to the file
    size_t nMedians = (size_t)medians::length_median;
    TH1D histo("medians","Medians;Property id;Median value",nMedians, 0, nMedians);
    
    if(nMedians != medianMap_.at(sampleName).size()) {
        throw std::range_error("BTagSFGeneric::produceBtagEfficiencies Numbers of stored and designed median values differ");
    }
    
    for(size_t i = 0; i<nMedians; ++i) {
        histo.SetBinContent(i+1, medianMap_.at(sampleName).at(i));
    }
    histo.Write();

    
    file.Close();


    std::cout<<"Done with production of b-tag efficiency file: "<< outputFileName
             <<"\n\n"<<std::endl;
}






