#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
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
#include "MvaTreeAnalyzer.h"
#include "higgsUtils.h"
#include "../../diLeptonic/src/sampleHelpers.h"
#include "../../diLeptonic/src/CommandLineParameters.h"
#include "../../diLeptonic/src/utils.h"
#include "../../diLeptonic/src/RootFileReader.h"





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






void trainBdtTopSystemJetAssignment(const std::vector<Channel::Channel>& v_channel,
                                    const std::vector<Systematic::Systematic>& v_systematic,
                                    const std::vector<std::string>& v_mode)
{
    std::cout<<"\n--- Beginning MVA training\n";
    
    // Access all MVA input file names for all systematics and channels
    tth::mvaHelpers::SystematicChannelFileNames m_systematicChannelFileNamesTraining =
        tth::mvaHelpers::systematicChannelFileNames(FileListBASE, v_channel, v_systematic);
    tth::mvaHelpers::SystematicChannelFileNames m_systematicChannelFileNamesTesting =
        tth::mvaHelpers::systematicChannelFileNames(FileListBASE, v_channel, v_systematic, false);
    
    // Define steps for indiviual MVA treatment
    // FIXME: make general selections via steps and categories
    std::vector<TString> v_selectionSteps = {"step8", "step8_cate5"};
    
    // Find all trees of all steps/categories containing MVA input variables from first input file
    const std::vector<std::pair<TString, TString> > v_nameStepPair =
        tth::nameStepPairs(m_systematicChannelFileNamesTraining.at(v_systematic.at(0)).at(v_channel.at(0)).at(0),
                           "mvaInputTopJets_step",
                           v_selectionSteps);
    
    // Loop over all channels and systematics
    for(const auto& systematicChannelFileNamesTraining : m_systematicChannelFileNamesTraining){
        const Systematic::Systematic& systematic = systematicChannelFileNamesTraining.first;
        for(const auto& channelFileNamesTraining : systematicChannelFileNamesTraining.second){
            const Channel::Channel& channel = channelFileNamesTraining.first;
            const std::vector<TString>& v_fileNameTraining = channelFileNamesTraining.second;
            const std::vector<TString>& v_fileNameTesting = m_systematicChannelFileNamesTesting.at(systematic).at(channel);
            std::cout<<"Processing (Channel, Systematic): "<<Channel::convertChannel(channel)<<" , "<<Systematic::convertSystematic(systematic)<<"\n\n";
            
            // Open the input files and access the MVA input training trees
            std::map<TString, TList*> m_stepListTraining;
            for(const auto& fileName : v_fileNameTraining){
                std::cout<<"File for training: "<<fileName<<std::endl;
                // FIXME: need to check whether input file really exists
                TFile* inputFile(0);
                inputFile = TFile::Open(fileName);
                for(const auto& nameStepPair : v_nameStepPair){
                    //std::cout<<"Tree and step: "<<nameStepPair.first<<" , "<<nameStepPair.second<<"\n\n";
                    // FIXME: need to check whether input tree really exists
                    TTree* inputTree = (TTree*)inputFile->Get(nameStepPair.first);
                    if(m_stepListTraining.find(nameStepPair.second) == m_stepListTraining.end()){
                        m_stepListTraining[nameStepPair.second] = new TList;
                    }
                    m_stepListTraining.at(nameStepPair.second)->Add(inputTree);
                }
            }
            std::cout<<std::endl;
            
            // Open the input files and access the MVA input testing trees
            std::map<TString, TList*> m_stepListTesting;
            for(const auto& fileName : v_fileNameTesting){
                std::cout<<"File for testing: "<<fileName<<std::endl;
                // FIXME: need to check whether input file really exists
                TFile* inputFile(0);
                inputFile = TFile::Open(fileName);
                for(const auto& nameStepPair : v_nameStepPair){
                    //std::cout<<"Tree and step: "<<nameStepPair.first<<" , "<<nameStepPair.second<<"\n\n";
                    // FIXME: need to check whether input tree really exists
                    TTree* inputTree = (TTree*)inputFile->Get(nameStepPair.first);
                    if(m_stepListTesting.find(nameStepPair.second) == m_stepListTesting.end()){
                        m_stepListTesting[nameStepPair.second] = new TList;
                    }
                    m_stepListTesting.at(nameStepPair.second)->Add(inputTree);
                }
            }
            std::cout<<std::endl;
            
            // Unfortunately this output file is needed to prevent from strange ROOT message
            TString mergedTreesFileName = ttbar::assignFolder(MvaInputDIR, channel, systematic);
            mergedTreesFileName.Append("/");
            mergedTreesFileName.Append("mergedTrees.root");
            TFile* mergedTrees = new TFile(mergedTreesFileName, "RECREATE");
            for(const auto& nameStepPair : v_nameStepPair){
                TTree* treeTraining = TTree::MergeTrees(m_stepListTraining.at(nameStepPair.second));
                treeTraining->SetName("training_"+nameStepPair.first);
                TTree* treeTesting = TTree::MergeTrees(m_stepListTesting.at(nameStepPair.second));
                treeTesting->SetName("testing_"+nameStepPair.first);
                treeTraining->Write();
                treeTesting->Write();
            }
            mergedTrees->Close();
            
            // Print all separation power plots
            if(std::find(v_mode.begin(), v_mode.end(), "cp") != v_mode.end()){
                TString outputPlots = ttbar::assignFolder(MvaOutputDIR, channel, systematic);
                outputPlots.Append(PlotOutputFILE);
                MvaTreeHandler mvaTreeHandler("", {});
                mvaTreeHandler.importTrees(mergedTreesFileName.Data(), "training_");
                MvaTreeAnalyzer mvaTreeAnalyzer(mvaTreeHandler.stepMvaVariablesMap(), true);
                mvaTreeAnalyzer.plotVariables(outputPlots.Data());
            }
            
            // Run the MVA training
            if(std::find(v_mode.begin(), v_mode.end(), "mva") != v_mode.end()){
                mergedTrees = TFile::Open(mergedTreesFileName);
                std::vector<TString> selectionSteps;
                for(const auto& nameStepPair : v_nameStepPair){
                    selectionSteps.push_back(nameStepPair.second);
                }
                MvaFactory mvaFactory(ttbar::assignFolder(MvaOutputDIR, channel, systematic), MvaWeightFileDIR, selectionSteps);
                
                for(const auto& nameStepPair : v_nameStepPair){
                    TTree* treeTraining = (TTree*)mergedTrees->Get("training_"+nameStepPair.first);
                    TTree* treeTesting = (TTree*)mergedTrees->Get("testing_"+nameStepPair.first);
                    std::cout<<"\n\n\tTrees: "<<treeTraining->GetName()<<" , "<<treeTesting->GetName()<<"\n\n\n";
                    
                    // MVA for correct dijet combinations
                    constexpr const char* mvaOutputFilenameCorrect = "correct.root";
                    constexpr const char* methodNameCorrect = "correct";
                    const TCut cutSignalCorrect = "correctCombination != 0";
                    const TCut cutBackgroundCorrect = "correctCombination == 0 && swappedCombination == 0";
                    
                    mvaFactory.runMva(mvaOutputFilenameCorrect,
                                      methodNameCorrect, cutSignalCorrect, cutBackgroundCorrect,
                                      treeTraining, treeTesting);
                    
                    // MVA for swapped dijet combinations
                    constexpr const char* mvaOutputFilenameSwapped = "swapped.root";
                    constexpr const char* methodNameSwapped = "swapped";
                    const TCut cutSignalSwapped = "swappedCombination != 0";
                    const TCut cutBackgroundSwapped = "correctCombination == 0 && swappedCombination == 0";
                    
                    mvaFactory.runMva(mvaOutputFilenameSwapped,
                                      methodNameSwapped, cutSignalSwapped, cutBackgroundSwapped,
                                      treeTraining, treeTesting);
                }
            }
        }
    }
    
    
    
    
/*    
    // Run the MVA training
    if(std::find(v_mode.begin(), v_mode.end(), "mva") != v_mode.end()){
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
*/    
    
    std::cout<<"=== Finishing MVA training\n\n";
}



int main(int argc, char** argv)
{
    CLParameter<std::string> opt_channel("c", "Specify channel(s), valid: emu, ee, mumu, combined. Default: combined", false, 1, 4,
        ttbar::makeStringCheck(Channel::convertChannels(Channel::allowedChannelsPlotting)));
    CLParameter<std::string> opt_systematic("s", "Systematic variation - default is Nominal", false, 1, 100,
        ttbar::makeStringCheck({"Nominal", ""}));
    CLParameter<std::string> opt_mode("m", "Mode: separation plots (cp), run MVA (mva). Default is cp", false, 1, 2,
        //[](const std::string& m){return m=="" || m=="cp" || m=="mva";});
        ttbar::makeStringCheck({"", "cp", "mva"}));
    CLAnalyser::interpretGlobal(argc, argv);
    
    // Set up channels
    std::vector<Channel::Channel> v_channel({Channel::combined});
    if(opt_channel.isSet()) v_channel = Channel::convertChannels(opt_channel.getArguments());
    std::cout << "Processing channels: ";
    for (auto channel : v_channel)std::cout << Channel::convertChannel(channel) << " ";
    std::cout << "\n\n";
    
    // Set up systematics
    std::vector<Systematic::Systematic> v_systematic({Systematic::nominal});
    if(opt_systematic.isSet()) v_systematic = Systematic::convertSystematics(opt_systematic.getArguments());
    std::cout << "Processing systematics: "; 
    for (auto systematic : v_systematic) std::cout << Systematic::convertSystematic(systematic) << " ";
    std::cout << "\n\n";
    
    // Set up modes
    const std::vector<std::string> v_mode = opt_mode.isSet() ? opt_mode.getArguments() : std::vector<std::string>{"cp"};
    std::cout << "Running following modes: ";
    for (auto mode : v_mode)std::cout << mode << " ";
    std::cout << "\n\n";
    
    trainBdtTopSystemJetAssignment(v_channel, v_systematic, v_mode);
}





