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
#include "mvaSetup.h"
#include "higgsUtils.h"
#include "../../diLeptonic/src/sampleHelpers.h"
#include "../../diLeptonic/src/CommandLineParameters.h"
#include "../../diLeptonic/src/utils.h"
#include "../../diLeptonic/src/RootFileReader.h"





/// The MVA input base folder
constexpr const char* MvaInputDIR = "mvaInput";

/// The MVA output base folder
constexpr const char* MvaOutputDIR = "mvaOutput";

/// The MVA output sub-folder for weights
constexpr const char* MvaWeightFileDIR = "weights";



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
    std::vector<TString> v_selectionSteps = {"_step8", "_step8_cate1", "_step8_cate5"};
    
    // Find all trees of all steps/categories containing MVA input variables from first input file
    const std::vector<std::pair<TString, TString> > v_nameStepPair =
        tth::nameStepPairs(m_systematicChannelFileNamesTraining.at(v_systematic.at(0)).at(v_channel.at(0)).at(0),
                           "mvaInputTopJets_step",
                           v_selectionSteps);
    
    // Loop over all channels and systematics and merge trees
    tth::mvaHelpers::SystematicChannelFileNames m_systematicChannelMergedFiles = 
        tth::mvaHelpers::mergeTrees(MvaInputDIR,
                                    m_systematicChannelFileNamesTraining,
                                    m_systematicChannelFileNamesTesting,
                                    v_nameStepPair);
    
    // Loop over all channels and systematics and run MVA
    for(const auto& systematicChannelMergedFiles : m_systematicChannelMergedFiles){
        const Systematic::Systematic& systematic = systematicChannelMergedFiles.first;
        for(const auto& channelMergedFiles : systematicChannelMergedFiles.second){
            const Channel::Channel& channel = channelMergedFiles.first;
            const TString& fileName = channelMergedFiles.second.at(0);
            std::cout<<"Processing (Channel, Systematic): "<<Channel::convertChannel(channel)<<" , "<<Systematic::convertSystematic(systematic)<<"\n\n";
            
            // Print all separation power plots
            if(std::find(v_mode.begin(), v_mode.end(), "cp") != v_mode.end()){
                TString outputPlots = ttbar::assignFolder(MvaOutputDIR, channel, systematic);
                outputPlots.Append(PlotOutputFILE);
                MvaTreeHandler mvaTreeHandler("", {});
                mvaTreeHandler.importTrees(fileName.Data(), "training_");
                MvaTreeAnalyzer mvaTreeAnalyzer(mvaTreeHandler.stepMvaVariablesMap(), true);
                mvaTreeAnalyzer.plotVariables(outputPlots.Data());
            }
            
            // Run the MVA training
            if(std::find(v_mode.begin(), v_mode.end(), "mva") != v_mode.end()){
                TFile* mergedTrees = TFile::Open(fileName);
                const TString folder = ttbar::assignFolder(MvaOutputDIR, channel, systematic);
                MvaFactory mvaFactory(folder, MvaWeightFileDIR,
                                      v_nameStepPair, mergedTrees);
                mvaFactory.train(mvaSetups::v_mvaSetCorrect, mvaSetups::v_mvaSetSwapped, channel);
                mergedTrees->Close();
            }
        }
    }
    
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





