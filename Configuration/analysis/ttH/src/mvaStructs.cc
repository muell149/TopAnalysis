#include <iostream>
#include <cstdlib>

#include <Math/VectorUtil.h>

#include "mvaStructs.h"
#include "analysisStructs.h"
#include "../../diLeptonic/src/classes.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"





// ----------------------------------------- Methods for MvaTopJetsVariables -----------------------------------------------------------



MvaTopJetsVariables::MvaTopJetsVariables():
lastInEvent_(MvaVariableInt(name_lastInEvent_)),
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
                                         const bool lastInEvent,
                                         const double& eventWeight):
lastInEvent_(MvaVariableInt(name_lastInEvent_)),
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
    
    // Needed booleans
    lastInEvent_.value_ = lastInEvent;
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
        // Is it the last entry of an event
        const bool lastInEvent = iJetIndexPairs == jetIndexPairs.size()-1;
        
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
                                           lastInEvent,
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







// ----------------------------------------- Methods for MvaTopJetsVariablesPerEvent -----------------------------------------------------------



MvaTopJetsVariablesPerEvent::MvaTopJetsVariablesPerEvent(const std::vector<MvaTopJetsVariables>& v_mvaInputVariables):
v_mvaTopJetsVariables_(v_mvaInputVariables)
{}



MvaTopJetsVariablesPerEvent::MvaTopJetsVariablesPerEvent(const std::vector<MvaTopJetsVariables>& v_mvaInputVariables,
                                                         const std::map<std::string, std::vector<float> >& m_mvaWeightCorrect,
                                                         const std::map<std::string, std::vector<float> >& m_mvaWeightSwapped,
                                                         const std::map<std::string, std::map<std::string, std::vector<float> > >& m_mvaWeightCombined):
v_mvaTopJetsVariables_(v_mvaInputVariables),
m_weightCorrect_(m_mvaWeightCorrect),
m_weightSwapped_(m_mvaWeightSwapped),
m_weightCombined_(m_mvaWeightCombined)
{
    for(const auto& weights : m_weightCorrect_){
        if(weights.second.size() != v_mvaTopJetsVariables_.size()){
            std::cerr<<"ERROR in constructor of MvaTopJetsVariablesPerEvent! Vector sizes do not match for CORRECT weights (variables, weights): "
                     <<v_mvaInputVariables.size()<<" , "<<weights.second.size()<<"\n...break\n"<<std::endl;
            exit(47);
        }
    }
    for(const auto& weights : m_weightSwapped_){
        if(weights.second.size() != v_mvaTopJetsVariables_.size()){
            std::cerr<<"ERROR in constructor of MvaTopJetsVariablesPerEvent! Vector sizes do not match for SWAPPED weights (variables, weights): "
                     <<v_mvaInputVariables.size()<<" , "<<weights.second.size()<<"\n...break\n"<<std::endl;
            exit(48);
        }
    }
    for(const auto& weights1 : m_weightCombined_){
        for(const auto& weights2 : weights1.second){
            if(weights2.second.size() != v_mvaTopJetsVariables_.size()){
                std::cerr<<"ERROR in constructor of MvaTopJetsVariablesPerEvent! Vector sizes do not match for COMBINED weights (variables, weights): "
                         <<v_mvaInputVariables.size()<<" , "<<weights2.second.size()<<"\n...break\n"<<std::endl;
                exit(49);
            }
        }
    }
}



size_t MvaTopJetsVariablesPerEvent::maxWeightCorrectIndex(const std::string& mvaConfigName)const
{
    const std::vector<float>& v_weight = this->mvaWeightsCorrect(mvaConfigName);
    return ttbar::extremumIndex(v_weight);
}



size_t MvaTopJetsVariablesPerEvent::maxWeightSwappedIndex(const std::string& mvaConfigName)const
{
    const std::vector<float>& v_weight = this->mvaWeightsSwapped(mvaConfigName);
    return ttbar::extremumIndex(v_weight);
}



size_t MvaTopJetsVariablesPerEvent::maxWeightCombinedIndex(const std::string& mvaConfigNameCorrect,
                                                           const std::string& mvaConfigNameSwapped)const
{
    const std::vector<float>& v_weight = this->mvaWeightsCombined(mvaConfigNameCorrect, mvaConfigNameSwapped);
    return ttbar::extremumIndex(v_weight);
}



float MvaTopJetsVariablesPerEvent::maxWeightCorrect(const std::string& mvaConfigName)const
{
    const size_t maxWeightIndex = this->maxWeightCorrectIndex(mvaConfigName);
    return m_weightCorrect_.at(mvaConfigName).at(maxWeightIndex);
}



float MvaTopJetsVariablesPerEvent::maxWeightSwapped(const std::string& mvaConfigName)const
{
    const size_t maxWeightIndex = this->maxWeightSwappedIndex(mvaConfigName);
    return m_weightSwapped_.at(mvaConfigName).at(maxWeightIndex);
}



float MvaTopJetsVariablesPerEvent::maxWeightCombined(const std::string& mvaConfigNameCorrect, const std::string& mvaConfigNameSwapped)const
{
    const size_t maxWeightIndex = this->maxWeightCombinedIndex(mvaConfigNameCorrect, mvaConfigNameSwapped);
    return m_weightCombined_.at(mvaConfigNameCorrect).at(mvaConfigNameSwapped).at(maxWeightIndex);
}



bool MvaTopJetsVariablesPerEvent::isSameMaxCombination(const std::string& mvaConfigNameCorrect, const std::string& mvaConfigNameSwapped)const
{
    return this->maxWeightCorrectIndex(mvaConfigNameCorrect) == this->maxWeightSwappedIndex(mvaConfigNameSwapped);
}



std::vector<MvaTopJetsVariables> MvaTopJetsVariablesPerEvent::variables()const
{
    return v_mvaTopJetsVariables_;
}



std::vector<float> MvaTopJetsVariablesPerEvent::mvaWeightsCorrect(const std::string& mvaConfigName)const
{
    if(m_weightCorrect_.find(mvaConfigName) == m_weightCorrect_.end()){
        std::cerr<<"ERROR in mvaWeightsCorrect()! No weights found for mvaConfigName: "
                 <<mvaConfigName<<"\n...break\n"<<std::endl;
        exit(50);
    }
    
    return m_weightCorrect_.at(mvaConfigName);
}



std::vector<float> MvaTopJetsVariablesPerEvent::mvaWeightsSwapped(const std::string& mvaConfigName)const
{
    if(m_weightSwapped_.find(mvaConfigName) == m_weightSwapped_.end()){
        std::cerr<<"ERROR in mvaWeightsSwapped()! No weights found for mvaConfigName: "
                 <<mvaConfigName<<"\n...break\n"<<std::endl;
        exit(50);
    }
    
    return m_weightSwapped_.at(mvaConfigName);
}



std::vector<float> MvaTopJetsVariablesPerEvent::mvaWeightsCombined(const std::string& mvaConfigNameCorrect,
                                                                   const std::string& mvaConfigNameSwapped)const
{
    if(m_weightCombined_.find(mvaConfigNameCorrect) == m_weightCombined_.end() || 
        m_weightCombined_.at(mvaConfigNameCorrect).find(mvaConfigNameSwapped) == m_weightCombined_.at(mvaConfigNameCorrect).end()){
        std::cerr<<"ERROR in mvaWeightsCorrect()! No weights found for mvaConfigName (correct, swapped): "
                 <<mvaConfigNameCorrect<<" , "<<mvaConfigNameSwapped<<"\n...break\n"<<std::endl;
        exit(50);
    }
    
    return m_weightCombined_.at(mvaConfigNameCorrect).at(mvaConfigNameSwapped);
}



std::map<std::string, std::vector<float> > MvaTopJetsVariablesPerEvent::mvaWeightsCorrectMap()const
{
    return m_weightCorrect_;
}



std::map<std::string, std::vector<float> > MvaTopJetsVariablesPerEvent::mvaWeightsSwappedMap()const
{
    return m_weightSwapped_;
}



std::map<std::string, std::map<std::string, std::vector<float> > > MvaTopJetsVariablesPerEvent::mvaWeightsCombinedMap()const
{
    return m_weightCombined_;
}








