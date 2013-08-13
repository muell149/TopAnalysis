#include <iostream>
#include <cstdlib>
#include <algorithm>

#include <TTree.h>
#include <TFile.h>
#include <TString.h>
#include <TSelectorList.h>
#include <Rtypes.h>

#include "MvaTreeHandler.h"
#include "mvaStructs.h"
#include "analysisStructs.h"
#include "../../diLeptonic/src/sampleHelpers.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"





MvaTreeHandler::MvaTreeHandler(const char* mvaInputDir, const std::vector<TString>& selectionSteps):
selectorList_(0),
t_mvaInput_(0),
selectionSteps_(selectionSteps),
mvaInputDir_(mvaInputDir)
{
    std::cout<<"--- Beginning setting up MVA input tree handler\n";
    std::cout<<"=== Finishing setting up MVA input tree handler\n\n";
}



void MvaTreeHandler::fillForInputProduction(const RecoObjects& recoObjects,
                                            const tth::GenObjectIndices& genObjectIndices,
                                            const tth::RecoObjectIndices& recoObjectIndices,
                                            const double& weight,
                                            const TString& selectionStep)
{
    // Check if step exists
    if(std::find(selectionSteps_.begin(), selectionSteps_.end(), selectionStep) == selectionSteps_.end()) return;
    
    // FIXME: which events exactly to fill? For now all with at least 4 jets
    const int numberOfJets = recoObjectIndices.jetIndices_.size();
    if(numberOfJets<4) return;
    
    // Loop over all jet combinations and get MVA input variables
    const std::vector<MvaTopJetsVariables>& v_mvaTopJetsVariables = 
            MvaTopJetsVariables::fillVariables(recoObjectIndices, genObjectIndices, recoObjects, weight);
    
    // Fill the MVA TTree
    v_mvaTopJetsVariables_.insert(v_mvaTopJetsVariables_.end(), v_mvaTopJetsVariables.begin(), v_mvaTopJetsVariables.end());
}



void MvaTreeHandler::createMvaInputBranches(TTree* tree)
{
    t_mvaInput_ = tree;
    
    this->createBranch(mvaTopJetsVariables_.eventWeight_);
    this->createBranch(mvaTopJetsVariables_.bQuarkRecoJetMatched_);
    this->createBranch(mvaTopJetsVariables_.correctCombination_);
    this->createBranch(mvaTopJetsVariables_.swappedCombination_);
    this->createBranch(mvaTopJetsVariables_.jetChargeDiff_);
    this->createBranch(mvaTopJetsVariables_.meanDeltaPhi_b_met_);
    this->createBranch(mvaTopJetsVariables_.massDiff_recoil_bbbar_);
    this->createBranch(mvaTopJetsVariables_.pt_b_antiLepton_);
    this->createBranch(mvaTopJetsVariables_.pt_antiB_lepton_);
    this->createBranch(mvaTopJetsVariables_.deltaR_b_antiLepton_);
    this->createBranch(mvaTopJetsVariables_.deltaR_antiB_lepton_);
    this->createBranch(mvaTopJetsVariables_.btagDiscriminatorSum_);
    this->createBranch(mvaTopJetsVariables_.deltaPhi_antiBLepton_bAntiLepton_);
    this->createBranch(mvaTopJetsVariables_.massDiff_fullBLepton_bbbar_);
    this->createBranch(mvaTopJetsVariables_.meanMt_b_met_);
    this->createBranch(mvaTopJetsVariables_.massSum_antiBLepton_bAntiLepton_);
    this->createBranch(mvaTopJetsVariables_.massDiff_antiBLepton_bAntiLepton_);
    
//    t_mvaInput_->Branch("mvaWeightCorrect", &inputStruct_.mvaWeightCorrect_, "mvaWeightCorrect/F");
//    t_mvaInput_->Branch("mvaWeightSwapped", &inputStruct_.mvaWeightSwapped_, "mvaWeightSwapped/F");
//    t_mvaInput_->Branch("bestMvaWeightCorrect", &inputStruct_.bestMvaWeightCorrect_, "bestMvaWeightCorrect/F");
//    t_mvaInput_->Branch("bestMvaWeightSwapped", &inputStruct_.bestMvaWeightSwapped_, "bestMvaWeightSwapped/F");
}



void MvaTreeHandler::createBranch(const MvaVariableInt& variable)
{
    const char* name(variable.name().data());
    std::string nameType(name);
    nameType.append("/").append(variable.type());
    t_mvaInput_->Branch(name, (Long_t)&variable.value_, nameType.data());
}



void MvaTreeHandler::createBranch(const MvaVariableFloat& variable)
{
    const char* name(variable.name().data());
    std::string nameType(name);
    nameType.append("/").append(variable.type());
    t_mvaInput_->Branch(name, (Long_t)&variable.value_, nameType.data());
}



void MvaTreeHandler::clear()
{
    v_mvaTopJetsVariables_.clear();
    t_mvaInput_ = 0;
    selectorList_ = 0;
}



void MvaTreeHandler::fillMvaInputBranches()
{
    for(const auto& mvaTopJetsVariables : v_mvaTopJetsVariables_){
        mvaTopJetsVariables_ = mvaTopJetsVariables;
        t_mvaInput_->Fill();
    }
}



void MvaTreeHandler::produceMvaInputTree(const std::string& outputFilename,
                                                   const Channel::Channel& channel, const Systematic::Systematic& systematic)
{
    // Create output file for MVA tree
    std::string f_savename = static_cast<std::string>(ttbar::assignFolder(mvaInputDir_, channel, systematic));
    f_savename.append(outputFilename);
    TFile outputFile(f_savename.c_str(),"RECREATE");
    std::cout<<"\nOutput file for MVA input tree: "<<f_savename<<"\n";
    
    // Produce MVA input TTree and store it in output
    TSelectorList* output = new TSelectorList();
    this->produceMvaInputTree(output);
    
    // Write file and cleanup
    TIterator* it = output->MakeIterator();
    while(TObject* obj = it->Next()){
        obj->Write();
    }
    outputFile.Close();
    output->SetOwner();
    output->Clear();
}



void MvaTreeHandler::produceMvaInputTree(TSelectorList* output)
{
    std::cout<<"--- Beginning production of MVA input tree\n";
    
    // Set pointer to output, so that TTree is owned by it
    selectorList_ = output;
    
    // TTree for MVA input
    TTree* tree(0);
    tree = store(new TTree("mvaInputTopJets", "mvaInputTopJets"));
    //tree = dynamic_cast<TTree*>(output->FindObject("mvaInputTopJets"));
    
    // Create branches and fill tree
    this->createMvaInputBranches(tree);
    this->fillMvaInputBranches();
    
    std::cout<<"Number of dijet combinations for MVA: "<<v_mvaTopJetsVariables_.size()<<"\n";
    std::cout<<"=== Finishing production of MVA input tree\n\n";
}



void MvaTreeHandler::importTree(const std::string& f_savename, const std::string& treeName)
{
    std::cout<<"--- Beginning import of TTree for MVA variables\n";
    
    TFile* inputFile = TFile::Open(f_savename.c_str());
    if(inputFile->IsZombie()){
        std::cerr<<"ERROR! Cannot open input file to import TTree, filename is: "<<f_savename<<"\n...break\n"<<std::endl;
        exit(77);
    }
    
    TTree* tree(0);
    tree = dynamic_cast<TTree*>(inputFile->Get(treeName.c_str()));
    if (!tree){
        std::cerr << "ERROR: TTree not found in file, tree name is: "<<treeName<<"\n...break\n"<<std::endl;
        exit(78);
    }
    
    this->importBranches(tree);
    
    tree = 0;
    inputFile->Close();
    std::cout<<"\nNumber of entries: "<<v_mvaTopJetsVariables_.size()<<"\n\n";
    std::cout<<"=== Finishing import of TTree for MVA variables\n\n";
}



void MvaTreeHandler::importBranches(TTree* tree)
{
    // Set up variables struct and branches
    MvaTopJetsVariables mvaTopJetsVariables;
    
    // Set branch addresses
    this->importBranch(tree, mvaTopJetsVariables.eventWeight_);
    this->importBranch(tree, mvaTopJetsVariables.bQuarkRecoJetMatched_);
    this->importBranch(tree, mvaTopJetsVariables.correctCombination_);
    this->importBranch(tree, mvaTopJetsVariables.swappedCombination_);
    this->importBranch(tree, mvaTopJetsVariables.jetChargeDiff_);
    this->importBranch(tree, mvaTopJetsVariables.meanDeltaPhi_b_met_);
    this->importBranch(tree, mvaTopJetsVariables.massDiff_recoil_bbbar_);
    this->importBranch(tree, mvaTopJetsVariables.pt_b_antiLepton_);
    this->importBranch(tree, mvaTopJetsVariables.pt_antiB_lepton_);
    this->importBranch(tree, mvaTopJetsVariables.deltaR_b_antiLepton_);
    this->importBranch(tree, mvaTopJetsVariables.deltaR_antiB_lepton_);
    this->importBranch(tree, mvaTopJetsVariables.btagDiscriminatorSum_);
    this->importBranch(tree, mvaTopJetsVariables.deltaPhi_antiBLepton_bAntiLepton_);
    this->importBranch(tree, mvaTopJetsVariables.massDiff_fullBLepton_bbbar_);
    this->importBranch(tree, mvaTopJetsVariables.meanMt_b_met_);
    this->importBranch(tree, mvaTopJetsVariables.massSum_antiBLepton_bAntiLepton_);
    this->importBranch(tree, mvaTopJetsVariables.massDiff_antiBLepton_bAntiLepton_);
    
    // Loop over all tree entries and fill vector of structs
    v_mvaTopJetsVariables_.clear();
    for(Long64_t iEntry = 0; iEntry < tree->GetEntries(); ++iEntry){
        tree->GetEntry(iEntry);
        v_mvaTopJetsVariables_.push_back(mvaTopJetsVariables);
    }
}



void MvaTreeHandler::importBranch(TTree* tree, MvaVariableInt& variable)
{
    tree->SetBranchAddress(variable.name().data(), &variable.value_, &variable.branch_);
}



void MvaTreeHandler::importBranch(TTree* tree, MvaVariableFloat& variable)
{
    tree->SetBranchAddress(variable.name().data(), &variable.value_, &variable.branch_);
}


















