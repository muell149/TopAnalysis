#include <iostream>
#include <cstdlib>
#include <algorithm>

#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TFile.h>
#include <TString.h>
#include <Rtypes.h>
#include <TCut.h>
#include <TMVA/Tools.h>
#include <TMVA/Config.h>
#include <TMVA/Factory.h>
#include <TMVA/Types.h>

#include "MvaFactory.h"
#include "mvaStructs.h"
#include "higgsUtils.h"




MvaFactory::MvaFactory(const TString& mvaOutputDir, const char* weightFileDir,
                       const std::vector<std::pair<TString, TString> >& v_nameStepPair,
                       TFile* mergedTrees):
v_nameStepPair_(v_nameStepPair),
mvaOutputDir_(mvaOutputDir),
weightFileDir_(weightFileDir),
mergedTrees_(mergedTrees)
{
    std::cout<<"--- Beginning setting up MVA training\n";
    
    if(!mergedTrees_){
        std::cerr<<"ERROR in constructor of MvaFactory! File containing the merged trees not found\n...break\n"<<std::endl;
        exit(123);
    }
    
    std::cout<<"=== Finishing setting up MVA training\n\n";
}



void MvaFactory::clear()
{
    weightFileDir_ = 0;
    mergedTrees_ = 0;
}



void MvaFactory::train(const std::vector<MvaSet>& v_mvaSetCorrect,
                       const std::vector<MvaSet>& v_mvaSetSwapped,
                       const Channel::Channel& channel)
{
    // MVA for correct dijet combinations
    constexpr const char* methodPrefixCorrect = "correct";
    const TCut cutSignalCorrect = "correctCombination != 0";
    const TCut cutBackgroundCorrect = "correctCombination == 0 && swappedCombination == 0";
    
    // MVA for swapped dijet combinations
    constexpr const char* methodPrefixSwapped = "swapped";
    const TCut cutSignalSwapped = "swappedCombination != 0";
    const TCut cutBackgroundSwapped = "correctCombination == 0 && swappedCombination == 0";
    
    // Clean the MVA sets in case they are not selected for training
    const std::vector<MvaSet> v_cleanSetCorrect = this->cleanSets(v_mvaSetCorrect, channel);
    const std::vector<MvaSet> v_cleanSetSwapped = this->cleanSets(v_mvaSetSwapped, channel);
    
    for(const auto& nameStepPair : v_nameStepPair_){
        const std::vector<MvaSet> v_selectedSetCorrect = this->selectSets(v_cleanSetCorrect, nameStepPair.second);
        const std::vector<MvaSet> v_selectedSetSwapped = this->selectSets(v_cleanSetSwapped, nameStepPair.second);
        if(!v_selectedSetCorrect.size() && !v_selectedSetSwapped.size()){
            std::cerr<<"ERROR in train()! Defined step/category has no definitions of MVA sets: "<<nameStepPair.second
                     <<"\n...break\n"<<std::endl;
            exit(139);
        }
        
        TTree* treeTraining = (TTree*)mergedTrees_->Get("training"+nameStepPair.first);
        TTree* treeTesting = (TTree*)mergedTrees_->Get("testing"+nameStepPair.first);
        
        if(v_selectedSetCorrect.size())
            this->runMva(methodPrefixCorrect, cutSignalCorrect, cutBackgroundCorrect, treeTraining, treeTesting, v_selectedSetCorrect, nameStepPair.second);
        if(v_selectedSetSwapped.size())
            this->runMva(methodPrefixSwapped, cutSignalSwapped, cutBackgroundSwapped, treeTraining, treeTesting, v_selectedSetSwapped, nameStepPair.second);
    }
}



void MvaFactory::runMva(const char* methodPrefix, const TCut& cutSignal, const TCut& cutBackground,
                        TTree* treeTraining, TTree* treeTesting,
                        const std::vector<MvaSet>& v_mvaSet,
                        const TString& stepName)
{
    
    // Get a TMVA instance
    TMVA::Tools::Instance();
    
    // Create a ROOT output file for TMVA
    TString mvaOutputFilename(mvaOutputDir_);
    mvaOutputFilename.Append(methodPrefix);
    mvaOutputFilename.Append(stepName);
    mvaOutputFilename.Append(".root");
    TFile* outputFile = TFile::Open(mvaOutputFilename, "RECREATE");
    
    // Set the output directory for the weights (if not specified, default is "weights")
    TString mvaOutputWeightsFilename(mvaOutputDir_);
    mvaOutputWeightsFilename.Append(weightFileDir_);
    (TMVA::gConfig().GetIONames()).fWeightFileDir = mvaOutputWeightsFilename;
    
    // Create the factory
    TMVA::Factory* factory(0);
    TString factoryName(methodPrefix);
    factoryName.Append(stepName);
    factory = new TMVA::Factory(factoryName, outputFile, "!V:!Silent");
    
    // Set all branches of MVA input which should be used for training
    MvaTopJetsVariables mvaTopJetsVariables;
    
    this->addVariable(factory, mvaTopJetsVariables.jetChargeDiff_);
    this->addVariable(factory, mvaTopJetsVariables.meanDeltaPhi_b_met_);
    this->addVariable(factory, mvaTopJetsVariables.massDiff_recoil_bbbar_);
    this->addVariable(factory, mvaTopJetsVariables.pt_b_antiLepton_);
    this->addVariable(factory, mvaTopJetsVariables.pt_antiB_lepton_);
    this->addVariable(factory, mvaTopJetsVariables.deltaR_b_antiLepton_);
    this->addVariable(factory, mvaTopJetsVariables.deltaR_antiB_lepton_);
    this->addVariable(factory, mvaTopJetsVariables.btagDiscriminatorSum_);
    this->addVariable(factory, mvaTopJetsVariables.deltaPhi_antiBLepton_bAntiLepton_);
    this->addVariable(factory, mvaTopJetsVariables.massDiff_fullBLepton_bbbar_);
    this->addVariable(factory, mvaTopJetsVariables.meanMt_b_met_);
    this->addVariable(factory, mvaTopJetsVariables.massSum_antiBLepton_bAntiLepton_);
    this->addVariable(factory, mvaTopJetsVariables.massDiff_antiBLepton_bAntiLepton_);
    
    // Set all branches of MVA input which should NOT be used for training,
    // but are needed otherwise (e.g. for defining separation cuts)
    this->addSpectator(factory, mvaTopJetsVariables.bQuarkRecoJetMatched_);
    this->addSpectator(factory, mvaTopJetsVariables.correctCombination_);
    this->addSpectator(factory, mvaTopJetsVariables.swappedCombination_);
    
    // Set global weights for individual input
    Double_t signalWeight = 1.;
    Double_t backgroundWeight = 1.;
    
    // Register the training trees
    factory->AddSignalTree(treeTraining, signalWeight, TMVA::Types::kTraining);
    factory->AddBackgroundTree(treeTraining, backgroundWeight, TMVA::Types::kTraining);
    
    // Register the testing trees
    factory->AddSignalTree(treeTesting, signalWeight, TMVA::Types::kTesting);
    factory->AddBackgroundTree(treeTesting, backgroundWeight, TMVA::Types::kTesting);
    
    // Set the branch from which the event weight is taken
    factory->SetSignalWeightExpression(mvaTopJetsVariables.eventWeight_.name());
    factory->SetBackgroundWeightExpression(mvaTopJetsVariables.eventWeight_.name());
    
    // Prepare the training and test trees
    factory->PrepareTrainingAndTestTree(cutSignal, cutBackground,
                                        "SplitMode=Block:SplitSeed=0:NormMode=NumEvents:!V" );
    
    // Book the MVA methods (e.g. boosted decision tree with specific setup)
    for(const auto& mvaSet : v_mvaSet){
        for(const auto& mvaConfig : mvaSet.v_mvaConfig_){
            const TString methodTitle(mvaConfig.methodAppendix_);
            factory->BookMethod(mvaConfig.mvaType_,
                                methodTitle,
                                mvaConfig.options_);
        }
    }
    
    // Run factory
    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();
    
    // Cleanup
    outputFile->Close();
    delete factory;
}



void MvaFactory::addVariable(TMVA::Factory* factory, MvaVariableInt& variable)
{
    factory->AddVariable(variable.name().data(), *variable.type());
}



void MvaFactory::addVariable(TMVA::Factory* factory, MvaVariableFloat& variable)
{
    factory->AddVariable(variable.name().data(), *variable.type());
}



void MvaFactory::addSpectator(TMVA::Factory* factory, MvaVariableInt& variable)
{
    factory->AddSpectator(variable.name().data(), *variable.type());
}



void MvaFactory::addSpectator(TMVA::Factory* factory, MvaVariableFloat& variable)
{
    factory->AddSpectator(variable.name().data(), *variable.type());
}



std::vector<MvaFactory::MvaSet> MvaFactory::cleanSets(const std::vector<MvaFactory::MvaSet>& v_mvaSet,
                                                      const Channel::Channel& channel)const
{
    std::vector<MvaFactory::MvaSet> result;
    
    for(const MvaFactory::MvaSet& mvaSet : v_mvaSet){
        // Check if set is valid for processed channel
        if(std::find(mvaSet.v_channel_.begin(), mvaSet.v_channel_.end(), channel) == mvaSet.v_channel_.end()) continue;
        
        // Check if set is valid for any of the chosen selection steps and cateogories
        bool selectedStepCategory(false);
        const std::vector<TString> v_stepName = mvaSet.stepNames();
        for(const auto& nameStepPair : v_nameStepPair_){
            if(std::find(v_stepName.begin(), v_stepName.end(), nameStepPair.second) != v_stepName.end()){
                selectedStepCategory = true;
                break;
            }
        }
        if(!selectedStepCategory) continue;
        
        result.push_back(mvaSet);
    }
    if(!result.size()){
        std::cerr<<"ERROR in cleanSets()! All MVA sets are deselected, no valid configuration found\n...break\n"<<std::endl;
        exit(137);
    }
    
    return result;
}



std::vector<MvaFactory::MvaSet> MvaFactory::selectSets(const std::vector<MvaFactory::MvaSet>& v_mvaSet,
                                                       const TString& step)const
{
    std::vector<MvaFactory::MvaSet> result;
    
    for(const MvaFactory::MvaSet& mvaSet : v_mvaSet){
        const std::vector<TString> v_stepName = mvaSet.stepNames();
        if(std::find(v_stepName.begin(), v_stepName.end(), step) == v_stepName.end()) continue;
        result.push_back(mvaSet);
    }
    
    return result;
}








MvaFactory::MvaConfig::MvaConfig(const TString& options,
                                 const TString& methodAppendix,
                                 const TMVA::Types::EMVA& mvaType):
mvaType_(mvaType),
methodAppendix_(methodAppendix),
options_(options)
{}



MvaFactory::MvaSet::MvaSet(const std::vector<MvaConfig>& v_mvaConfig,
                           const std::vector<int>& v_category,
                           const std::vector<Channel::Channel>& v_channel,
                           const TString& step):
v_channel_(v_channel),
step_(step),
v_category_(v_category),
v_mvaConfig_(v_mvaConfig)
{
    for(const int category : v_category_){
        if(category<0){
            std::cerr<<"ERROR in constructor of MvaSet! jetCategories contain value <0: "<<category
                     <<"\n...break\n"<<std::endl;
            exit(136);
        }
    }
}



std::vector<TString> MvaFactory::MvaSet::stepNames()const
{
    std::vector<TString> v_stepName;
    
    if(v_category_.size()){
        for(const int category : v_category_){
            TString step = tth::stepName(step_, category);
            v_stepName.push_back(step);
        }
    }
    else{
        TString step = tth::stepName(step_);
        v_stepName.push_back(step);
    }
    
    return v_stepName;
}








