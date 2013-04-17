#include <iostream>
#include <fstream>

#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TProof.h>
#include <TSelector.h>
#include <TObjString.h>
#include <TChain.h>
#include <TH1.h>

#include "HiggsAnalysis.h"
#include "higgsUtils.h"
#include "sampleHelpers.h"
#include "analysisHelpers.h"
#include "../../diLeptonic/src/utils.h"
#include "../../diLeptonic/src/PUReweighter.h"
#include "../../diLeptonic/src/CommandLineParameters.h"





/// Set pileup distribution file corresponding to data sample in use
/// The file ending is automatically adjusted for different systematics
//constexpr const char* FilePU = "/src/TopAnalysis/TopUtils/data/Data_PUDist_12fb";
constexpr const char* FilePU = "/src/TopAnalysis/Configuration/analysis/diLeptonic/data/Data_PUDist_19624pb";





void load_HiggsAnalysis(const TString validFilenamePattern, 
                        const Channel::Channel channel,
                        const Systematic::Systematic systematic,
                        const int dy,
                        const AnalysisMode::AnalysisMode analysisMode)
{   
    // Access selectionList containing all input sample nTuples
    ifstream infile ("selectionList.txt");
    if (!infile.good()) { 
        std::cerr << "Error! Please check the selectionList.txt file!\n" << std::endl; 
        exit(773); 
    }
    
    // Set up pileup reweighter
    HiggsAnalysis* selector = new HiggsAnalysis();
    PUReweighter* pu = new PUReweighter();
    pu->setMCDistrSum12("S10");
    pu->setDataTruePUInput(pu->getPUPath(Systematic::convertSystematic(systematic), FilePU).c_str());
    selector->SetPUReweighter(pu);
    
    // Loop over all input files
    int filecounter = 0;
    while(!infile.eof()){
        
        // Access nTuple input filename from selectionList
        TString filename;
        infile >> filename;
        if (filename == "" || filename[0] == '#') continue; //empty or commented line? --> skip
        if (!filename.Contains(validFilenamePattern)) continue;
        std::cout << std::endl;
        std::cout << "PROCESSING File " << ++filecounter << " ("<< filename << ") from selectionList.txt" << std::endl;
        std::cout << std::endl;
        
        // Open nTuple file
        TFile file(filename);
        if (file.IsZombie()){
            std::cerr << "Cannot open " << filename << std::endl;
            return;
        }
        
        // Check whether nTuple can be found
        TTree *tree = dynamic_cast<TTree*>(file.Get("writeNTuple/NTuple"));
        if (!tree){
            std::cerr << "Error: Tree not found!\n";
            exit(854);
        }
            
        // Access information about samples, stored in the nTuples
        TObjString *channel_file = dynamic_cast<TObjString*>(file.Get("writeNTuple/channelName"));
        TObjString *systematics_from_file = dynamic_cast<TObjString*>(file.Get("writeNTuple/systematicsName"));
        TObjString *samplename = dynamic_cast<TObjString*>(file.Get("writeNTuple/sampleName"));
        TObjString *o_isSignal = dynamic_cast<TObjString*>(file.Get("writeNTuple/isSignal"));
        TObjString *o_isHiggsSignal = dynamic_cast<TObjString*>(file.Get("writeNTuple/isHiggsSignal"));
        TObjString *o_isMC = dynamic_cast<TObjString*>(file.Get("writeNTuple/isMC"));
        TH1* weightedEvents = dynamic_cast<TH1*>(file.Get("EventsBeforeSelection/weightedEvents"));
        if (!channel_file || !systematics_from_file || !o_isSignal || !o_isMC || !samplename) { 
            std::cout << "Error: info about sample missing!" << std::endl; 
            return;  
        }
        
        // Configure information about samples
        const bool isTopSignal = o_isSignal->GetString() == "1";
        const bool isMC = o_isMC->GetString() == "1";
        const bool isHiggsSignal(o_isHiggsSignal && o_isHiggsSignal->GetString()=="1");
        const bool isHiggsInclusive(isHiggsSignal && samplename->GetString()=="ttbarhiggsinclusive");
        const bool isTtbarV(samplename->GetString()=="ttbarw" || samplename->GetString()=="ttbarz");
        
        if (!isMC && systematic!=Systematic::undefined) {
            std::cout << "Sample is DATA, so not running again for systematic variation\n";
            continue;
        }
        
        //determine the channels to run over
        std::vector<Channel::Channel> channels;
        if(channel_file->GetString() != ""){
            channels.push_back(Channel::convertChannel(static_cast<std::string>(channel_file->GetString())));
        }
        else{
            if(channel != Channel::undefined){
                channels.push_back(channel);
            }
            else{
                channels = Channel::allowedChannelsAnalysis;
            }
        }
        
        // Loop over channels and run selector
        for(const auto& selectedChannel : Channel::convertChannels(channels)){
            
            // Set output file name
            TString outputfilename(filename);
            if (outputfilename.Contains('/')) {
                Ssiz_t last = outputfilename.Last('/');
                outputfilename = outputfilename.Data() + last + 1;
            }
            if (!outputfilename.BeginsWith(selectedChannel + "_")) outputfilename.Prepend(selectedChannel + "_");
            //outputfile is now channel_filename.root
            if (dy) {
                if (outputfilename.First("_dy") == kNPOS) { 
                    std::cerr << "DY variations must be run on DY samples!\n";
                    std::cerr << outputfilename << " must start with 'channel_dy'\n";
                    std::exit(1);
                }
                outputfilename.ReplaceAll("_dy", TString("_dy").Append(dy == 11 ? "ee" : dy == 13 ? "mumu" : "tautau"));
            }
            if(isHiggsInclusive)outputfilename.ReplaceAll("inclusive", "inclusiveOther");
            
            // Configure selector
            selector->SetBTagFile("");
            selector->SetChannel(selectedChannel);
            selector->SetTopSignal(isTopSignal);
            selector->SetHiggsSignal(isHiggsSignal);
            selector->SetMC(isMC);
            selector->SetTrueLevelDYChannel(dy);
            if (systematic == Systematic::undefined){
                selector->SetSystematic(systematics_from_file->GetString());
            }
            else{
                selector->SetSystematic(Systematic::convertSystematic(systematic));
            }
            selector->SetWeightedEvents(weightedEvents);
            // FIXME: correction for MadGraph W decay branching fractions are not correctly applied
            // Recently it is done for W from ttbar decays, set via SetSamplename
            // Needs to be changed: for ttbarW, also correction for 3rd W needs to be applied, for ttbarhiggs corrections for 2 or 4 Ws needed, depending on Higgs decay (H->WW?)
            // and what about Wlnu sample, or possible others ?
            selector->SetSamplename(samplename->GetString(), systematics_from_file->GetString());
            selector->SetOutputfilename(outputfilename);
            selector->SetRunViaTau(0);
            selector->SetHiggsInclusiveSample(isHiggsInclusive);
            selector->SetHiggsInclusiveSeparation(false);
            selector->SetAnalysisMode(analysisMode);
            
            // Set up nTuple chain and run selector
            TChain chain("writeNTuple/NTuple");
            chain.Add(filename);
            // chain.SetProof(); //will work from 5.34 onwards
            chain.Process(selector);
            
            // For splitting of ttbarsignal in component with intermediate taus and without
            if(isTopSignal && !isHiggsSignal && !isTtbarV){
                selector->SetRunViaTau(1);
                outputfilename.ReplaceAll("signalplustau", "bgviatau");
                selector->SetOutputfilename(outputfilename);
                chain.Process(selector);
            }
            
            // For splitting of ttH inclusive decay in H->bb and other decays
            if(isHiggsInclusive){
                selector->SetHiggsInclusiveSeparation(true);
                outputfilename.ReplaceAll("Other", "Bbbar");
                selector->SetOutputfilename(outputfilename);
                chain.Process(selector);
            }
        }
        file.Close();
    }
}



int main(int argc, char** argv) {
    CLParameter<std::string> opt_filenamePattern("f", "Restrict to filename pattern, e.g. ttbar", false, 1, 1);
    CLParameter<std::string> opt_channel("c", "Specify a certain channel (ee, emu, mumu). No channel specified = run on all channels", false, 1, 1,
            Tools::makeStringCheck(Channel::convertChannels(Channel::allowedChannelsAnalysis)));
    CLParameter<std::string> opt_systematic("s", "Run with a systematic that runs on the nominal ntuples, e.g. 'PU_UP'", false, 1, 1,
            Tools::makeStringCheck(Systematic::convertSystematics(Systematic::allowedSystematicsAnalysis)));
    CLParameter<int> opt_dy("d", "Drell-Yan mode (11 for ee, 13 for mumu, 15 for tautau)", false, 1, 1,
            [](int dy){return dy == 11 || dy == 13 || dy == 15;});
    CLParameter<std::string> opt_mode("m", "Mode of analysis: control plots (cp), MVA input (mva). Default is cp", false, 1, 1,
            Tools::makeStringCheck(AnalysisMode::convertAnalysisModes(AnalysisMode::allowedAnalysisModes)));
    CLAnalyser::interpretGlobal(argc, argv);
    
    // Set up a pattern for selecting only files from selectionList containing that pattern in filename
    const TString validFilenamePattern = opt_filenamePattern.isSet() ? opt_filenamePattern[0] : "";
    
    // Set up channel
    Channel::Channel channel(Channel::undefined);
    if(opt_channel.isSet()) channel = Channel::convertChannel(opt_channel[0]);
    
    // Set up systematic
    Systematic::Systematic systematic(Systematic::undefined);
    if(opt_systematic.isSet()) systematic = Systematic::convertSystematic(opt_systematic[0]);
    
    // Set up Drell-Yan mode
    const int dy = opt_dy.isSet() ? opt_dy[0] : 0;
    
    // Set up analysis mode
    AnalysisMode::AnalysisMode analysisMode(AnalysisMode::cp);
    if(opt_mode.isSet()) analysisMode = AnalysisMode::convertAnalysisMode(opt_mode[0]);
    
    // Start plotting
    //TProof* p = TProof::Open(""); // not before ROOT 5.34
    load_HiggsAnalysis(validFilenamePattern, channel, systematic, dy, analysisMode);
    //delete p;
}



