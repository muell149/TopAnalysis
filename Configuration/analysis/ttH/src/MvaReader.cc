#include <iostream>
#include <fstream>

#include <TString.h>
#include <TMVA/Reader.h>

#include "MvaReader.h"
#include "mvaStructs.h"





MvaReader::MvaReader(const char* mvaWeightsFile, const std::vector<TString>& selectionSteps):
mvaWeightsReader_(0),
selectionSteps_(selectionSteps)
{
    std::cout<<"--- Beginning setting up MVA weights from file\n";
    
    ifstream inputFile(mvaWeightsFile);
    if(inputFile.fail()){
        std::cout<<"Input file containing MVA weights not found: "<<mvaWeightsFile
                 <<"\n...running without MVA weights, i.e. setting them all to 1.\n";
    }
    else{
        mvaWeightsReader_ = new TMVA::Reader("Color");

        MvaTopJetsVariables& mvaTopJetsVariables = mvaTopJetsVariables_;
        
        this->addVariable(mvaTopJetsVariables.jetChargeDiff_);
        this->addVariable(mvaTopJetsVariables.meanDeltaPhi_b_met_);
        this->addVariable(mvaTopJetsVariables.massDiff_recoil_bbbar_);
        this->addVariable(mvaTopJetsVariables.pt_b_antiLepton_);
        this->addVariable(mvaTopJetsVariables.pt_antiB_lepton_);
        this->addVariable(mvaTopJetsVariables.deltaR_b_antiLepton_);
        this->addVariable(mvaTopJetsVariables.deltaR_antiB_lepton_);
        this->addVariable(mvaTopJetsVariables.btagDiscriminatorSum_);
        this->addVariable(mvaTopJetsVariables.deltaPhi_antiBLepton_bAntiLepton_);
        this->addVariable(mvaTopJetsVariables.massDiff_fullBLepton_bbbar_);
        this->addVariable(mvaTopJetsVariables.meanMt_b_met_);
        this->addVariable(mvaTopJetsVariables.massSum_antiBLepton_bAntiLepton_);
        this->addVariable(mvaTopJetsVariables.massDiff_antiBLepton_bAntiLepton_);
        
        this->addSpectator(mvaTopJetsVariables.bQuarkRecoJetMatched_);
        this->addSpectator(mvaTopJetsVariables.correctCombination_);
        this->addSpectator(mvaTopJetsVariables.swappedCombination_);
        
        // FIXME: what is first argument, should it be "BDTG" or "BDT method" ???
        mvaWeightsReader_->BookMVA("BDT method", mvaWeightsFile);
    }
    
    std::cout<<"=== Finishing setting up MVA weights from file\n\n";
}



void MvaReader::addVariable(MvaVariableInt& variable)
{
    mvaWeightsReader_->AddVariable(variable.name().data(), &variable.value_);
}



void MvaReader::addVariable(MvaVariableFloat& variable)
{
    mvaWeightsReader_->AddVariable(variable.name().data(), &variable.value_);
}



void MvaReader::addSpectator(MvaVariableInt& variable)
{
    mvaWeightsReader_->AddSpectator(variable.name().data(), &variable.value_);
}



void MvaReader::addSpectator(MvaVariableFloat& variable)
{
    mvaWeightsReader_->AddSpectator(variable.name().data(), &variable.value_);
}



void MvaReader::clear()
{
    v_mvaTopJetsVariablesPerEvent_.clear();
    if(mvaWeightsReader_){
        mvaWeightsReader_->Clear();
        mvaWeightsReader_->Delete();
    }
}



std::vector<float> MvaReader::mvaWeights(const std::vector<MvaTopJetsVariables>& v_mvaTopJetsVariables)
{
    std::vector<float> result;
    
    for(const MvaTopJetsVariables& mvaTopJetsVariables : v_mvaTopJetsVariables){
        if(!mvaWeightsReader_){
            result.push_back(1.);
            continue;
        }
        mvaTopJetsVariables_ = mvaTopJetsVariables;
        const float weight = mvaWeightsReader_->EvaluateMVA("BDT method");
        result.push_back(weight);
    }
    
    return result;
}










