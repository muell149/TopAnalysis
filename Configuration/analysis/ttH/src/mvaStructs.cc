#include <Math/VectorUtil.h>

#include "mvaStructs.h"
#include "../../diLeptonic/src/classes.h"
#include "../../diLeptonic/src/analysisUtils.h"





// ----------------------------------------- Methods for MvaInputVariables -----------------------------------------------------------



tth::MvaInputVariables::MvaInputVariables():
bQuarkRecoJetMatched_(0),
correctCombination_(0),
swappedCombination_(0),
eventWeight_(-999.),
meanDeltaPhi_b_met_(-999.),
massDiff_recoil_bbbar_(-999.),
pt_b_antiLepton_(-999.),
pt_antiB_lepton_(-999.),
deltaR_b_antiLepton_(-999.),
deltaR_antiB_lepton_(-999.),
btagDiscriminatorSum_(-999.),
deltaPhi_antiBLepton_bAntiLepton_(-999.),
massDiff_fullBLepton_bbbar_(-999.),
meanMt_b_met_(-999.),
massSum_antiBLepton_bAntiLepton_(-999.),
massDiff_antiBLepton_bAntiLepton_(-999.)
{}



tth::MvaInputVariables::MvaInputVariables(const LV& lepton, const LV& antiLepton,
                                          const LV& bJet, const LV& antiBJet,
                                          const double& bJetBtagDiscriminator, const double& antiBJetBtagDiscriminator,
                                          const double& jetChargeDiff,
                                          const LV& jetRecoil, const LV& met,
                                          const bool bQuarkRecoJetMatched,
                                          const bool correctCombination, const bool swappedCombination,
                                          const double& eventWeight):
bQuarkRecoJetMatched_(bQuarkRecoJetMatched),
correctCombination_(correctCombination),
swappedCombination_(swappedCombination),
eventWeight_(eventWeight)
{
    using ROOT::Math::VectorUtil::DeltaPhi;
    using ROOT::Math::VectorUtil::DeltaR;
    
    // Helper variables for MVA
    const LV bAntiBSystem = bJet + antiBJet;
    const LV bAntiLeptonSystem = bJet + antiLepton;
    const LV antiBLeptonSystem = antiBJet + lepton;
    const LV fullBLeptonSystem = bAntiLeptonSystem + antiBLeptonSystem;
    
    // Fill the variables for MVA TTree
    jetChargeDiff_ = jetChargeDiff;
    meanDeltaPhi_b_met_ = 0.5*(std::abs(DeltaPhi(bJet, met)) + std::abs(DeltaPhi(antiBJet, met)));
    massDiff_recoil_bbbar_ = jetRecoil.M() - bAntiBSystem.M();
    pt_b_antiLepton_ = bAntiLeptonSystem.pt();
    pt_antiB_lepton_ = antiBLeptonSystem.pt();
    deltaR_b_antiLepton_ = DeltaR(bJet, antiLepton);
    deltaR_antiB_lepton_ = DeltaR(antiBJet, lepton);
    btagDiscriminatorSum_ = bJetBtagDiscriminator + antiBJetBtagDiscriminator;
    deltaPhi_antiBLepton_bAntiLepton_ = std::abs(DeltaPhi(antiBLeptonSystem, bAntiLeptonSystem));
    massDiff_fullBLepton_bbbar_ = fullBLeptonSystem.M() - bAntiBSystem.M();
    meanMt_b_met_ = 0.5*((bJet + met).Mt() + (antiBJet + met).Mt());
    massSum_antiBLepton_bAntiLepton_ = antiBLeptonSystem.M() + bAntiLeptonSystem.M();
    massDiff_antiBLepton_bAntiLepton_ = antiBLeptonSystem.M() - bAntiLeptonSystem.M();
}







// ----------------------------------------- Methods for MvaInputVariablesPerEvent -----------------------------------------------------------



tth::MvaInputVariablesPerEvent::MvaInputVariablesPerEvent():
maxWeightCorrectIndex_(-1),
maxWeightSwappedIndex_(-1)
{}



tth::MvaInputVariablesPerEvent::MvaInputVariablesPerEvent(const std::vector<tth::MvaInputVariables>& v_mvaInputVariables,
                                                          const std::vector<float>& v_mvaWeightCorrect,
                                                          const std::vector<float>& v_mvaWeightSwapped):
v_mvaInputVariables_(v_mvaInputVariables),
v_mvaWeightCorrect_(v_mvaWeightCorrect),
v_mvaWeightSwapped_(v_mvaWeightSwapped),
maxWeightCorrectIndex_(ttbar::extremumIndex(v_mvaWeightCorrect)),
maxWeightSwappedIndex_(ttbar::extremumIndex(v_mvaWeightSwapped))
{}











