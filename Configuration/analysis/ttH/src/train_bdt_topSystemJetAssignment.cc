#include <iostream>

#include "TCut.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"

#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/Types.h"



//#include "TMVAGui.C"



#include "TMVA/Config.h"


/// The MVA input base folder
constexpr const char* MvaInputDIR = "selectionRoot/mvaInput";

/// The MVA output base folder
constexpr const char* MvaOutputDIR = "mvaOutput";






void trainBdtTopSystemJetAssignment()
{
    std::cout << std::endl;
    std::cout << "==> Start TMVAClassification" << std::endl;
    
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
    
    // Set up MVA input directory
    TString inputtt(MvaInputDIR);
    TString channel("emu");
    TString systematic("Nominal");
    inputtt.Append("/");
    inputtt.Append(systematic);
    inputtt.Append("/");
    inputtt.Append(channel);
    inputtt.Append("/");
    inputtt.Append(channel);
    inputtt.Append("_");
    
    // Open the input files
    TFile* inputFile_ee_ttbarH125inclusiveBbbar(0);
    TFile* inputFile_emu_ttbarH125inclusiveBbbar(0);
    TFile* inputFile_mumu_ttbarH125inclusiveBbbar(0);
    
    TFile* inputFile_ee_ttbarH125tobbbar(0);
    TFile* inputFile_emu_ttbarH125tobbbar(0);
    TFile* inputFile_mumu_ttbarH125tobbbar(0);
    
    inputFile_emu_ttbarH125inclusiveBbbar = TFile::Open(inputtt.Copy().Append("ttbarH125inclusiveBbbar.root"));
    inputFile_emu_ttbarH125tobbbar = TFile::Open(inputtt.Copy().Append("ttbarH125tobbbar.root"));
    
    // Set global weights for individual input
    Double_t signalWeight = 1.;
    Double_t backgroundWeight = 1.;
    
    // Register the training trees
    TTree* treeTraining = (TTree*)inputFile_emu_ttbarH125inclusiveBbbar->Get("mvaInputTopJets");
    factory->AddSignalTree(treeTraining, signalWeight, TMVA::Types::kTraining);
    factory->AddBackgroundTree(treeTraining, backgroundWeight, TMVA::Types::kTraining);
    
    // Register the testing trees
    TTree* treeTesting = (TTree*)inputFile_emu_ttbarH125tobbbar->Get("mvaInputTopJets");    
    factory->AddSignalTree(treeTesting, signalWeight, TMVA::Types::kTesting);
    factory->AddBackgroundTree(treeTesting, backgroundWeight, TMVA::Types::kTesting);
    
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
}



int main(int argc, char** argv) {
    trainBdtTopSystemJetAssignment();
}





