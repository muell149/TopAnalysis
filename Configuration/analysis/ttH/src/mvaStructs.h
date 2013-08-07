#ifndef mvaStructs_h
#define mvaStructs_h

#include <vector>

#include <Rtypes.h>

#include "../../diLeptonic/src/classesFwd.h"





namespace tth{
    
    /// Struct for holding the input variables as used in the MVA for top jets assignment
    struct MvaInputVariables{
        
    public:
        
        /// Empty constructor
        MvaInputVariables();
        
        /// Constructor setting up input variables from physics objects
        MvaInputVariables(const LV& lepton, const LV& antiLepton,
                          const LV& bJet, const LV& antiBJet,
                          const double& bJetBtagDiscriminator, const double& antiBJetBtagDiscriminator,
                          const double& jetChargeDiff,
                          const LV& jetRecoil, const LV& met,
                          const bool bQuarkRecoJetMatched,
                          const bool correctCombination, const bool swappedCombination,
                          const double& eventWeight =1.);
        
        /// Destructor
        ~MvaInputVariables(){}
        
        
        
    private:
        
        /// Could b quark and anti-b quark be matched to reco jets
        const Int_t bQuarkRecoJetMatched_;
        /// Is it the true correct jet combination
        const Int_t correctCombination_;
        /// Is it the true but swapped jet combination
        const Int_t swappedCombination_;
        
        /// Event weight including all scale factors
        const Float_t eventWeight_;
        
        /// Difference of the jet charges for (anti-b jet - b jet), i.e. it is within [0,2]
        Float_t jetChargeDiff_;
        /// Variables for MVA
        Float_t meanDeltaPhi_b_met_;
        Float_t massDiff_recoil_bbbar_;
        Float_t pt_b_antiLepton_;
        Float_t pt_antiB_lepton_;
        Float_t deltaR_b_antiLepton_;
        Float_t deltaR_antiB_lepton_;
        Float_t btagDiscriminatorSum_;
        Float_t deltaPhi_antiBLepton_bAntiLepton_;
        Float_t massDiff_fullBLepton_bbbar_;
        Float_t meanMt_b_met_;
        Float_t massSum_antiBLepton_bAntiLepton_;
        Float_t massDiff_antiBLepton_bAntiLepton_;
    };
    
    
    
    
    struct MvaInputVariablesPerEvent{
        
    public:
        
        /// Empty constructor
        MvaInputVariablesPerEvent();
        
        /// Constructor setting up mvaInputVariables together with MVA weights for correct and for swapped combinations
        MvaInputVariablesPerEvent(const std::vector<MvaInputVariables>& v_mvaInputVariables,
                                  const std::vector<float>& v_mvaWeightCorrect,
                                  const std::vector<float>& v_mvaWeightSwapped);
        
        /// Destructor
        ~MvaInputVariablesPerEvent(){}
        
        
        
        /// Returns the maximum correct MVA weight per event
        float maxWeightCorrect()const;
        
        /// Returns the maximum swapped MVA weight per event
        float maxWeightSwapped()const;
        
        /// Does the same dijet combination have the maximum correct and the maximum swapped weight per event
        bool isSameMaxCombination()const;
        
        
        
        
    private:
        
        /// Vector containing MVA input variables for all dijet pairs per event
        const std::vector<MvaInputVariables> v_mvaInputVariables_;
        
        /// Vector containing correct MVA weights for all dijet pairs per event
        const std::vector<Float_t> v_mvaWeightCorrect_;
        
        /// Vector containing swapped MVA weights for all dijet pairs per event
        const std::vector<Float_t> v_mvaWeightSwapped_;
        
        /// Index of dijet combination with maximum correct MVA weight
        const int maxWeightCorrectIndex_;
        
        /// Index of dijet combination with maximum swapped MVA weight
        const int maxWeightSwappedIndex_;
    };
}








#endif







