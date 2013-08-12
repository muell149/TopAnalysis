#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#include <TTree.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TString.h>
#include <Math/VectorUtil.h>
#include <TSelectorList.h>
#include <Rtypes.h>
#include <TCut.h>
#include <TMVA/Tools.h>
#include <TMVA/Config.h>
#include <TMVA/Factory.h>
#include <TMVA/Types.h>
#include <TMVA/Reader.h>

#include "MvaFactory.h"
#include "mvaStructs.h"
#include "analysisStructs.h"
#include "../../diLeptonic/src/sampleHelpers.h"
#include "../../diLeptonic/src/classes.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"







MvaFactory::MvaFactory(const char* mvaOutputDir, const std::vector<TString>& selectionSteps):
selectionSteps_(selectionSteps),
mvaOutputDir_(mvaOutputDir)
{
    std::cout<<"--- Beginning setting up MVA training\n";
    std::cout<<"=== Finishing setting up MVA training\n\n";
}



void MvaFactory::clear()
{
    mvaOutputDir_ = 0;
}



void MvaFactory::runMva(const char* outputDir, const char* weightFileDir, const char* outputFileName,
                        const char* methodName, const TCut& cutSignal, const TCut& cutBackground,
                        TTree* treeTraining, TTree* treeTesting)
{
    // Get a TMVA instance
    TMVA::Tools::Instance();
    
    // Create a ROOT output file for TMVA
    TString mvaOutputFilename(outputDir);
    mvaOutputFilename.Append("/");
    gSystem->MakeDirectory(mvaOutputFilename);
    mvaOutputFilename.Append(outputFileName);
    TFile* outputFile = TFile::Open(mvaOutputFilename, "RECREATE");
    
    // Set the output directory for the weights (if not specified, default is "weights")
    TString mvaOutputWeightsFilename(outputDir);
    mvaOutputWeightsFilename.Append(weightFileDir);
    (TMVA::gConfig().GetIONames()).fWeightFileDir = mvaOutputWeightsFilename;
    
    // Create the factory
    TMVA::Factory* factory(0);
    factory = new TMVA::Factory("MVA", outputFile, "!V:!Silent");
    
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
    
    // Book the MVA method (e.g. boosted decision tree with specific setup)
    factory->BookMethod(TMVA::Types::kBDT,
                        methodName,
                        "!H:!V:NTrees=600:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.45:UseRandomisedTrees=False:UseNVars=13:nCuts=1000:PruneMethod=CostComplexity:PruneStrength=-1");
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









