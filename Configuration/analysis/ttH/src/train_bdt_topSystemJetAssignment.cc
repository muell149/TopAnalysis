#include <iostream>
#include <fstream>

#include "TCut.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"

#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/Types.h"
#include "TMVA/Config.h"

#include "sampleHelpers.h"

//#include "TMVAGui.C"





/// The MVA input base folder
constexpr const char* MvaInputDIR = "mvaInput";

/// The MVA output base folder
constexpr const char* MvaOutputDIR = "mvaOutput";

/// Input base for the file lists containing the samples to be processed
constexpr const char* FileListBASE = "FileLists_mva/HistoFileList_";





void trainBdtTopSystemJetAssignment()
{
    std::cout<<"\n--- Beginning MVA training\n";
    
    // Get a TMVA instance
    TMVA::Tools::Instance();
    
    // Create a ROOT output file for TMVA
    TString mvaOutputFilename(MvaOutputDIR);
    mvaOutputFilename.Append("/");
    gSystem->MakeDirectory(mvaOutputFilename);
    mvaOutputFilename.Append("test1.root");
    TFile* outputFile = TFile::Open(mvaOutputFilename, "RECREATE");
    
    // Set the output directory for the weights (if not specified, default is "weights")
    TString mvaOutputWeightsFilename(MvaOutputDIR);
    mvaOutputWeightsFilename.Append("/weights");
    (TMVA::gConfig().GetIONames()).fWeightFileDir = mvaOutputWeightsFilename;
    
    // Create the factory
    TMVA::Factory* factory(0);
    factory = new TMVA::Factory( "MVA", outputFile, "!V:!Silent");
    
    // Set all branches of MVA input which should be used for training
    factory->AddVariable("meanDeltaPhi_b_met", 'F');
    factory->AddVariable("massDiff_recoil_bbbar", 'F');
    factory->AddVariable("pt_b_antiLepton", 'F');
    factory->AddVariable("pt_antiB_lepton", 'F');
    factory->AddVariable("deltaR_b_antiLepton", 'F');
    factory->AddVariable("deltaR_antiB_lepton", 'F');
    factory->AddVariable("btagDiscriminatorSum", 'F');
    factory->AddVariable("deltaPhi_antiBLepton_bAntiLepton", 'F');
    factory->AddVariable("massDiff_fullBLepton_bbbar", 'F');
    factory->AddVariable("meanMT_b_met", 'F');
    factory->AddVariable("massSum_antiBLepton_bAntiLepton", 'F');
    factory->AddVariable("massDiff_antiBLepton_bAntiLepton", 'F');
    
    // Set all branches of MVA input which should NOT be used for training,
    // but are needed otherwise (e.g. for defining separation cuts)
    factory->AddSpectator("bQuarkRecoJetMatched", 'I');
    factory->AddSpectator("correctCombination", 'I');
    factory->AddSpectator("swappedCombination", 'I');
    
    // Access all MVA input file names
    std::vector<TString> v_inputFileNameTraining;
    std::vector<TString> v_inputFileNameTesting;
    for(const auto& systematic : Systematic::allowedSystematicsPlotting){
        const Channel::Channel channel(Channel::combined);
        
        // Access FileList containing list of input root files
        // FIXME: almost same functionality as in Samples.cc, unify after MVA training is established
        const TString histoListName(FileListBASE + Systematic::convertSystematic(systematic) + "_" + Channel::convertChannel(channel) + ".txt");
        std::cout << "Reading file: " << histoListName << std::endl;
        ifstream fileList(histoListName);
        if (fileList.fail()) {
            std::cerr << "Error reading file: " << histoListName << std::endl;
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
    std::vector<TTree*> v_treeTraining;
    for(const auto& inputFileName : v_inputFileNameTraining){
        // FIXME: need to check whether input file and input tree really exist
        TFile* inputFile(0);
        inputFile = TFile::Open(inputFileName);
        TTree* inputTree = (TTree*)inputFile->Get("mvaInputTopJets");
        v_treeTraining.push_back(inputTree);
    }
    
    // Open the input files and access the MVA input testing trees
    std::vector<TTree*> v_treeTesting;
    for(const auto& inputFileName : v_inputFileNameTraining){
        // FIXME: need to check whether input file and input tree really exist
        TFile* inputFile(0);
        inputFile = TFile::Open(inputFileName);
        TTree* inputTree = (TTree*)inputFile->Get("mvaInputTopJets");
        v_treeTesting.push_back(inputTree);
    }
    
    // Set global weights for individual input
    Double_t signalWeight = 1.;
    Double_t backgroundWeight = 1.;
    
    // Register the training trees
    for(const auto& treeTraining : v_treeTraining){
        factory->AddSignalTree(treeTraining, signalWeight, TMVA::Types::kTraining);
        factory->AddBackgroundTree(treeTraining, backgroundWeight, TMVA::Types::kTraining);
    }
    
    // Register the testing trees
    for(const auto& treeTesting : v_treeTesting){
        factory->AddSignalTree(treeTesting, signalWeight, TMVA::Types::kTesting);
        factory->AddBackgroundTree(treeTesting, backgroundWeight, TMVA::Types::kTesting);
    }
    
    // Set the branch from which the event weight is taken
    factory->SetSignalWeightExpression("eventWeight");
    factory->SetBackgroundWeightExpression("eventWeight");
    
    // Apply additional cuts on the signal and background samples
    // If cut is empty (""), no selection is applied
    TCut cutSignal = "correctCombination != 0";
    TCut cutBackground = "correctCombination == 0";
    
    // Prepare the training and test trees
    factory->PrepareTrainingAndTestTree(cutSignal, cutBackground,
                                        "SplitMode=Block:SplitSeed=0:NormMode=NumEvents:!V" );
    
    // Book the MVA method (e.g. boosted decision tree with specific setup)
    factory->BookMethod(TMVA::Types::kBDT,
                        "test2",
                        "!H:!V:NTrees=600:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.45:UseRandomisedTrees=False:UseNVars=6:nCuts=1000:PruneMethod=CostComplexity:PruneStrength=-1");
    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();
    
    // Cleanup
    outputFile->Close();
    delete factory;
    
    std::cout<<"=== Finishing MVA training\n\n";
}



int main(int argc, char** argv) {
    trainBdtTopSystemJetAssignment();
}





