#include <Math/VectorUtil.h>

#include "mvaStructs.h"
#include "analysisStructs.h"
#include "../../diLeptonic/src/classes.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"





// ----------------------------------------- Methods for MvaInputVariables -----------------------------------------------------------



MvaTopJetsVariables::MvaTopJetsVariables():
bQuarkRecoJetMatched_(MvaVariableInt(name_bQuarkRecoJetMatched_)),
correctCombination_(MvaVariableInt(name_correctCombination_)),
swappedCombination_(MvaVariableInt(name_swappedCombination_)),
eventWeight_(MvaVariableFloat(name_eventWeight_)),
jetChargeDiff_(MvaVariableFloat(name_jetChargeDiff_)),
meanDeltaPhi_b_met_(MvaVariableFloat(name_meanDeltaPhi_b_met_)),
massDiff_recoil_bbbar_(MvaVariableFloat(name_massDiff_recoil_bbbar_)),
pt_b_antiLepton_(MvaVariableFloat(name_pt_b_antiLepton_)),
pt_antiB_lepton_(MvaVariableFloat(name_pt_antiB_lepton_)),
deltaR_b_antiLepton_(MvaVariableFloat(name_deltaR_b_antiLepton_)),
deltaR_antiB_lepton_(MvaVariableFloat(name_deltaR_antiB_lepton_)),
btagDiscriminatorSum_(MvaVariableFloat(name_btagDiscriminatorSum_)),
deltaPhi_antiBLepton_bAntiLepton_(MvaVariableFloat(name_deltaPhi_antiBLepton_bAntiLepton_)),
massDiff_fullBLepton_bbbar_(MvaVariableFloat(name_massDiff_fullBLepton_bbbar_)),
meanMt_b_met_(MvaVariableFloat(name_meanMt_b_met_)),
massSum_antiBLepton_bAntiLepton_(MvaVariableFloat(name_massSum_antiBLepton_bAntiLepton_)),
massDiff_antiBLepton_bAntiLepton_(MvaVariableFloat(name_massDiff_antiBLepton_bAntiLepton_))
{}



MvaTopJetsVariables::MvaTopJetsVariables(const LV& lepton, const LV& antiLepton,
                                         const LV& bJet, const LV& antiBJet,
                                         const double& bJetBtagDiscriminator, const double& antiBJetBtagDiscriminator,
                                         const double& jetChargeDiff,
                                         const LV& jetRecoil, const LV& met,
                                         const bool bQuarkRecoJetMatched,
                                         const bool correctCombination, const bool swappedCombination,
                                         const double& eventWeight):
bQuarkRecoJetMatched_(MvaVariableInt(name_bQuarkRecoJetMatched_)),
correctCombination_(MvaVariableInt(name_correctCombination_)),
swappedCombination_(MvaVariableInt(name_swappedCombination_)),
eventWeight_(MvaVariableFloat(name_eventWeight_)),
jetChargeDiff_(MvaVariableFloat(name_jetChargeDiff_)),
meanDeltaPhi_b_met_(MvaVariableFloat(name_meanDeltaPhi_b_met_)),
massDiff_recoil_bbbar_(MvaVariableFloat(name_massDiff_recoil_bbbar_)),
pt_b_antiLepton_(MvaVariableFloat(name_pt_b_antiLepton_)),
pt_antiB_lepton_(MvaVariableFloat(name_pt_antiB_lepton_)),
deltaR_b_antiLepton_(MvaVariableFloat(name_deltaR_b_antiLepton_)),
deltaR_antiB_lepton_(MvaVariableFloat(name_deltaR_antiB_lepton_)),
btagDiscriminatorSum_(MvaVariableFloat(name_btagDiscriminatorSum_)),
deltaPhi_antiBLepton_bAntiLepton_(MvaVariableFloat(name_deltaPhi_antiBLepton_bAntiLepton_)),
massDiff_fullBLepton_bbbar_(MvaVariableFloat(name_massDiff_fullBLepton_bbbar_)),
meanMt_b_met_(MvaVariableFloat(name_meanMt_b_met_)),
massSum_antiBLepton_bAntiLepton_(MvaVariableFloat(name_massSum_antiBLepton_bAntiLepton_)),
massDiff_antiBLepton_bAntiLepton_(MvaVariableFloat(name_massDiff_antiBLepton_bAntiLepton_))
{
    using ROOT::Math::VectorUtil::DeltaPhi;
    using ROOT::Math::VectorUtil::DeltaR;
    
    // Helper variables for MVA
    const LV bAntiBSystem = bJet + antiBJet;
    const LV bAntiLeptonSystem = bJet + antiLepton;
    const LV antiBLeptonSystem = antiBJet + lepton;
    const LV fullBLeptonSystem = bAntiLeptonSystem + antiBLeptonSystem;
    
    // Booleans needed for MVA
    bQuarkRecoJetMatched_.value_ = bQuarkRecoJetMatched;
    correctCombination_.value_ = correctCombination;
    swappedCombination_.value_ = swappedCombination;
    
    // Event weight
    eventWeight_.value_ = eventWeight;
    
    // Fill the variables for MVA TTree
    jetChargeDiff_.value_ = jetChargeDiff;
    meanDeltaPhi_b_met_.value_ = 0.5*(std::abs(DeltaPhi(bJet, met)) + std::abs(DeltaPhi(antiBJet, met)));
    massDiff_recoil_bbbar_.value_ = jetRecoil.M() - bAntiBSystem.M();
    pt_b_antiLepton_.value_ = bAntiLeptonSystem.pt();
    pt_antiB_lepton_.value_ = antiBLeptonSystem.pt();
    deltaR_b_antiLepton_.value_ = DeltaR(bJet, antiLepton);
    deltaR_antiB_lepton_.value_ = DeltaR(antiBJet, lepton);
    btagDiscriminatorSum_.value_ = bJetBtagDiscriminator + antiBJetBtagDiscriminator;
    deltaPhi_antiBLepton_bAntiLepton_.value_ = std::abs(DeltaPhi(antiBLeptonSystem, bAntiLeptonSystem));
    massDiff_fullBLepton_bbbar_.value_ = fullBLeptonSystem.M() - bAntiBSystem.M();
    meanMt_b_met_.value_ = 0.5*((bJet + met).Mt() + (antiBJet + met).Mt());
    massSum_antiBLepton_bAntiLepton_.value_ = antiBLeptonSystem.M() + bAntiLeptonSystem.M();
    massDiff_antiBLepton_bAntiLepton_.value_ = antiBLeptonSystem.M() - bAntiLeptonSystem.M();
}



std::vector<MvaTopJetsVariables> MvaTopJetsVariables::fillVariables(const tth::RecoObjectIndices& recoObjectIndices,
                                                                    const tth::GenObjectIndices& genObjectIndices,
                                                                    const RecoObjects& recoObjects,
                                                                    const double& eventWeight)
{
    std::vector<MvaTopJetsVariables> result;
    
    // Access relevant objects and indices
    const VLV& allLeptons(*recoObjects.allLeptons_);
    const VLV& jets(*recoObjects.jets_);
    const LV& met(*recoObjects.met_);
    const std::vector<double>& jetBtag(*recoObjects.jetBTagCSV_);
    const std::vector<double>& jetCharge(*recoObjects.jetChargeRelativePtWeighted_);
    
    const LV& lepton(allLeptons.at(recoObjectIndices.leptonIndex_));
    const LV& antiLepton(allLeptons.at(recoObjectIndices.antiLeptonIndex_));
    
    const int& matchedBjetFromTopIndex = genObjectIndices.recoBjetFromTopIndex_;
    const int& matchedAntiBjetFromTopIndex = genObjectIndices.recoAntiBjetFromTopIndex_;
    const bool& successfulTopMatching = genObjectIndices.uniqueRecoTopMatching();
    
    const tth::IndexPairs& jetIndexPairs = recoObjectIndices.jetIndexPairs_;
    
    // Calculate the jet recoil for each jet pair, and put it in a vector of same size
    const VLV& jetRecoils = MvaTopJetsVariables::recoilForJetPairs(jetIndexPairs, recoObjectIndices.jetIndices_, jets);
    
    
    // Loop over all jet pairs
    for(size_t iJetIndexPairs = 0; iJetIndexPairs < jetIndexPairs.size(); ++iJetIndexPairs){

        // Get the indices of b and anti-b jet defined by jet charge
        const int antiBIndex = jetIndexPairs.at(iJetIndexPairs).first;
        const int bIndex = jetIndexPairs.at(iJetIndexPairs).second;
        
        // Check whether the two jets correspond to the b's from tops, and if the two are correct or swapped
        bool isSwappedPair(false);
        bool isCorrectPair(false);
        if(successfulTopMatching){
            if(matchedBjetFromTopIndex==bIndex && matchedAntiBjetFromTopIndex==antiBIndex){
                isCorrectPair = true;
            }
            else if(matchedBjetFromTopIndex==antiBIndex && matchedAntiBjetFromTopIndex==bIndex){
                isSwappedPair = true;
            }
        }
        
        // Variables for MVA
        const LV& bjet = jets.at(bIndex);
        const LV& antiBjet = jets.at(antiBIndex);
        const double& bjetBtagDiscriminator = jetBtag.at(bIndex);
        const double& antiBjetBtagDiscriminator = jetBtag.at(antiBIndex);
        const double jetChargeDiff = jetCharge.at(antiBIndex) - jetCharge.at(bIndex);
        if(jetChargeDiff<0. || jetChargeDiff>2.){
            std::cerr<<"ERROR! Difference in jet charge is (value = "<<jetChargeDiff
                     <<"), but definition allows only values in [0,2]\n...break\n"<<std::endl;
            exit(555);
        }
        const LV& jetRecoil = jetRecoils.at(iJetIndexPairs);

        const MvaTopJetsVariables mvaInput(lepton, antiLepton,
                                         bjet, antiBjet,
                                         bjetBtagDiscriminator, antiBjetBtagDiscriminator,
                                         jetChargeDiff,
                                         jetRecoil, met,
                                         successfulTopMatching,
                                         isCorrectPair, isSwappedPair,
                                         eventWeight);

        result.push_back(mvaInput);
    }
    
    return result;
}



VLV MvaTopJetsVariables::recoilForJetPairs(const tth::IndexPairs& jetIndexPairs, const std::vector<int>& jetIndices, const VLV& jets)
{
    VLV result;

    for(const auto& jetIndexPair : jetIndexPairs){
        const int antiBIndex = jetIndexPair.first;
        const int bIndex = jetIndexPair.second;

        LV jetRecoil;
        for(const int index : jetIndices){
            if(index == bIndex || index == antiBIndex) continue;
            jetRecoil += jets.at(index);
        }

        result.push_back(jetRecoil);
    }

    return result;
}







// ----------------------------------------- Methods for MvaInputVariablesPerEvent -----------------------------------------------------------



MvaTopJetsVariablesPerEvent::MvaTopJetsVariablesPerEvent(const std::vector<MvaTopJetsVariables>& v_mvaInputVariables):
v_mvaTopJetsVariables_(v_mvaInputVariables)
{}



MvaTopJetsVariablesPerEvent::MvaTopJetsVariablesPerEvent(const std::vector<MvaTopJetsVariables>& v_mvaInputVariables,
                                                         const std::vector<float>& v_mvaWeightCorrect,
                                                         const std::vector<float>& v_mvaWeightSwapped):
v_mvaTopJetsVariables_(v_mvaInputVariables),
v_mvaWeightCorrect_(v_mvaWeightCorrect),
v_mvaWeightSwapped_(v_mvaWeightSwapped)
{}



int MvaTopJetsVariablesPerEvent::maxWeightCorrectIndex()const
{
    return ttbar::extremumIndex(v_mvaWeightCorrect_);
}



int MvaTopJetsVariablesPerEvent::maxWeightSwappedIndex()const
{
    return ttbar::extremumIndex(v_mvaWeightSwapped_);
}



float MvaTopJetsVariablesPerEvent::maxWeightCorrect()const
{
    return v_mvaWeightCorrect_.at(this->maxWeightCorrectIndex());
}



float MvaTopJetsVariablesPerEvent::maxWeightSwapped()const
{
    return v_mvaWeightSwapped_.at(this->maxWeightSwappedIndex());
}



bool MvaTopJetsVariablesPerEvent::isSameMaxCombination() const
{
    return ttbar::extremumIndex(v_mvaWeightCorrect_) == ttbar::extremumIndex(v_mvaWeightSwapped_);
}



std::vector<MvaTopJetsVariables> MvaTopJetsVariablesPerEvent::variables()const
{
    return v_mvaTopJetsVariables_;
}








