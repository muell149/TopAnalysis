#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

#include "TCut.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TList.h"

#include "MvaFactory.h"
#include "MvaTreeHandler.h"
#include "../../diLeptonic/src/sampleHelpers.h"
#include "../../diLeptonic/src/CommandLineParameters.h"
#include "../../diLeptonic/src/utils.h"




/// The MVA input base folder
constexpr const char* MvaInputDIR = "mvaInput";

/// The MVA output base folder
constexpr const char* MvaOutputDIR = "mvaOutput";

/// The MVA weights output folder
constexpr const char* MvaWeightFileDIR = "/weights";



/// Input base for the file lists containing the samples to be processed
constexpr const char* FileListBASE = "FileLists_mva/HistoFileList_";


/// The output file name for the control and separation power plots
constexpr const char* PlotOutputFILE = "plots.root";






void trainBdtTopSystemJetAssignment(const std::vector<std::string>& modes)
{
    std::cout<<"\n--- Beginning MVA training\n";
    
    // Access all MVA input file names
    std::vector<TString> v_inputFileNameTraining;
    std::vector<TString> v_inputFileNameTesting;
    for(const auto& systematic : Systematic::allowedSystematicsHiggsPlotting){
        const Channel::Channel channel(Channel::combined);
        
        // Access FileList containing list of input root files
        // FIXME: almost same functionality as in Samples.cc, unify after MVA training is established
        const TString histoListName(FileListBASE + Systematic::convertSystematic(systematic) + "_" + Channel::convertChannel(channel) + ".txt");
        //std::cout << "Reading file: " << histoListName << std::endl;
        ifstream fileList(histoListName);
        if(fileList.fail()){
            std::cerr<<"Error reading file: "<<histoListName<<std::endl;
            exit(1);
        }
        while(!fileList.eof()){
            TString filename;
            fileList>>filename;
            if(filename==""){continue;} // Skip empty lines
            if(filename.BeginsWith("#")){continue;} // Comment lines in FileList with '#'
            
            if(filename.Contains("ttbarH") && filename.Contains("inclusiveBbbar"))
                v_inputFileNameTraining.push_back(filename);
            else if(filename.Contains("ttbarH") && filename.Contains("tobbbar"))
                v_inputFileNameTesting.push_back(filename);
            else continue;
        }
    }
    
    // Open the input files and access the MVA input training trees
    TList* listTraining = new TList;
    for(const auto& inputFileName : v_inputFileNameTraining){
        std::cout<<"File for training: "<<inputFileName<<std::endl;
        
        // FIXME: need to check whether input file and input tree really exist
        TFile* inputFile(0);
        inputFile = TFile::Open(inputFileName);
        TTree* inputTree = (TTree*)inputFile->Get("mvaInputTopJets");
        listTraining->Add(inputTree);
    }
    std::cout<<std::endl;
    
    // Open the input files and access the MVA input testing trees
    TList* listTesting = new TList;
    for(const auto& inputFileName : v_inputFileNameTesting){
        std::cout<<"File for testing: "<<inputFileName<<std::endl;
        
        // FIXME: need to check whether input file and input tree really exist
        TFile* inputFile(0);
        inputFile = TFile::Open(inputFileName);
        TTree* inputTree = (TTree*)inputFile->Get("mvaInputTopJets");
        listTesting->Add(inputTree);
    }
    
    // Unfortunately this output file is needed to prevent from strange ROOT message
    TString mergedTreesName(MvaOutputDIR);
    mergedTreesName.Append("/");
    gSystem->MakeDirectory(mergedTreesName);
    mergedTreesName.Append("mergedTrees.root");
    TFile* mergedTrees = new TFile(mergedTreesName, "RECREATE");
    TTree* treeTraining = TTree::MergeTrees(listTraining);
    treeTraining->SetName("mvaInputTopJets_training");
    TTree* treeTesting = TTree::MergeTrees(listTesting);
    treeTesting->SetName("mvaInputTopJets_testing");
    treeTraining->Write();
    treeTesting->Write();
    mergedTrees->Close();
    
    // Print all separation power plots
    if(std::find(modes.begin(), modes.end(), "cp") != modes.end()){
        TString outputPlots(MvaOutputDIR);
        outputPlots.Append("/").Append(PlotOutputFILE);
        MvaTreeHandler mvaTreeHandler("", {});
        mvaTreeHandler.importTree(mergedTreesName.Data(), "mvaInputTopJets_training");
        mvaTreeHandler.plotVariables(outputPlots.Data(), true);
    }
    
    // Run the MVA training
    if(std::find(modes.begin(), modes.end(), "mva") != modes.end()){
        mergedTrees = TFile::Open(mergedTreesName);
        treeTraining = (TTree*)mergedTrees->Get("mvaInputTopJets_training");
        treeTesting = (TTree*)mergedTrees->Get("mvaInputTopJets_testing");
        
        MvaFactory mvaFactory(0, {});
        
        // MVA for correct dijet combinations
        constexpr const char* mvaOutputFilenameCorrect = "correct.root";
        constexpr const char* methodNameCorrect = "correct";
        
        const TCut cutSignalCorrect = "correctCombination != 0";
        const TCut cutBackgroundCorrect = "correctCombination == 0 && swappedCombination == 0";
        
        mvaFactory.runMva(MvaOutputDIR, MvaWeightFileDIR, mvaOutputFilenameCorrect,
                          methodNameCorrect, cutSignalCorrect, cutBackgroundCorrect,
                          treeTraining, treeTesting);
        
        
        // MVA for swapped dijet combinations
        constexpr const char* mvaOutputFilenameSwapped = "swapped.root";
        constexpr const char* methodNameSwapped = "swapped";
        
        const TCut cutSignalSwapped = "swappedCombination != 0";
        const TCut cutBackgroundSwapped = "correctCombination == 0 && swappedCombination == 0";
        
        mvaFactory.runMva(MvaOutputDIR, MvaWeightFileDIR, mvaOutputFilenameSwapped,
                          methodNameSwapped, cutSignalSwapped, cutBackgroundSwapped,
                          treeTraining, treeTesting);
    }
    
    
    std::cout<<"=== Finishing MVA training\n\n";
}



int main(int argc, char** argv)
{
    CLParameter<std::string> opt_mode("m", "Mode: separation plots (cp), run MVA (mva). Default is cp", false, 1, 2,
            //[](const std::string& m){return m=="" || m=="cp" || m=="mva";});
            ttbar::makeStringCheck({"", "cp", "mva"}));
    CLAnalyser::interpretGlobal(argc, argv);
    
    
    const std::vector<std::string> modes = opt_mode.isSet() ? opt_mode.getArguments() : std::vector<std::string>{"cp"};
    
    trainBdtTopSystemJetAssignment(modes);
}





