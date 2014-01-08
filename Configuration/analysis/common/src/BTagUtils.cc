#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <sstream>

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



std::string ttbar::fullFilePath(const std::string& baseDir, const std::string& fileName,
                                const std::string& channel, const TString& systematic,
                                const bool createNonExisting, const bool allowNonExisting)
{
    // Creating full path
    std::string path(baseDir);
    path.append("/");
    path.append(ttbar::partialFilePath(fileName, channel, systematic));

    TString pathStr(path);

    // Creating the string of the folder path (without root file name)
    TString folderPathStr(pathStr);
    folderPathStr.Remove(pathStr.Last('/'));

    // Creating all subdirectories needed to store the root file
    if(createNonExisting) {
        TObjArray* a_subDir = folderPathStr.Tokenize("/");
        std::string sequentialFolderPath("");
        for(Int_t iSubDir = 0; iSubDir < a_subDir->GetEntriesFast(); ++iSubDir){
            const TString& subDir = a_subDir->At(iSubDir)->GetName();
            sequentialFolderPath.append(subDir);
            sequentialFolderPath.append("/");
            gSystem->MakeDirectory(sequentialFolderPath.c_str());
        }
    }

    // Check if directory really exists
    if(!gSystem->OpenDirectory(folderPathStr)){
        if(allowNonExisting){
            // It is allowed to request a folder which does not exist, so return empty string silently
            return "";
        }
        else{
            std::cerr<<"ERROR! Request to access directory is not possible, because it does not exist. Directory name: "<<path
                     <<"\n...break\n"<<std::endl;
            exit(237);
        }
    }

    return path;
}

std::string ttbar::partialFilePath(const std::string& fileName, const std::string& channel, const TString& systematic)
{
    std::string path(systematic);
    path.append("/");
    path.append(channel);
    path.append("/");
    path.append(channel);
    path.append("_");
    path.append(fileName);

    return path;

}





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
        std::string btagInputFile = ttbar::fullFilePath(inputDirName_, fileName_, channel, systematic);
        if(btagInputFile == "") allInputFilesAvailable = false;

        ifstream inputFileStream;
        if(allInputFilesAvailable) inputFileStream.open(btagInputFile);
        if(!inputFileStream.is_open()){
            std::cout<< "******************************************************\n"
                     << "File " << btagInputFile << " does not exist. Running without btagsf!!!\n"
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
    std::string sampleName = ttbar::partialFilePath(fileName_, channel, "Nominal");
    std::string inputFileName = ttbar::fullFilePath(inputDirName_,fileName_, channel, "Nominal");

    // Set pointer to output, so that histograms are owned by it
    selectorList_ = output;

    // Stopping if no efficiency histograms need to be read (production mode)
    if(getMakeEff()) {
        setSampleName(sampleName);
        return;
    }


    std::vector<TH2D> histos;
    std::vector<TH2D> effhistos;

    // Load per-jet efficiencies file
    TFile file(inputFileName.c_str(),"READ");

    // Generating the list of all objects, stored in the root file to find the efficiency histograms
    TList *list = file.GetListOfKeys();
    for ( int keyNum=0; keyNum<list->GetSize(); keyNum++ ) {
        TKey* key = ( TKey* ) list->At ( keyNum );

        TString objType ( key->GetClassName() );
        TString objName ( key->GetName() );
        if(!objType.EqualTo("TH2D")) continue;

        if(objName.Contains("eff")) {
            effhistos.push_back(*(TH2D*)(file.Get(objName)) );
        } else histos.push_back(*(TH2D*)(file.Get(objName)) );

    }

    histos_[sampleName] = histos;
    effhistos_[sampleName] = effhistos;

    file.Close();

    setSampleName(sampleName);

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
    //FIXME: Change "Nominal" to real systematic name specified in the initializer
    std::string outputFileName = ttbar::fullFilePath(outputDirName_,fileName_, channel, "Nominal", true);
    std::string sampleName = ttbar::partialFilePath(fileName_, channel, "Nominal");

    TFile file(outputFileName.c_str(),"RECREATE");

    // Creating the histograms
    makeEffs();

    // Writing each histogram to file
    std::vector<TH2D> histos = histos_.at(sampleName);
    for(TH2D histo : histos){
        histo.Write();
    }

    // Writing each efficiency hitogram to file
    std::vector<TH2D> effhistos = effhistos_.at(sampleName);
    for(TH2D histo : effhistos) {
        histo.Write();
    }

    file.Close();


    std::cout<<"Done with production of b-tag efficiency file: "<< outputFileName
             <<"\n\n"<<std::endl;
}






