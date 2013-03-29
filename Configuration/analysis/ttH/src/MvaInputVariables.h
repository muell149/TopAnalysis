#ifndef MvaInputVariables_h
#define MvaInputVariables_h

#include <vector>

#include <TSelectorList.h>

class TTree;

#include "../../diLeptonic/src/classes.h"





/// Class holding the input variables for MVA, trying to identify the jets coming from (anti)b's from (anti)tops
class MvaInputTopJetsVariables{
    
public:
    
    struct MvaInputTopJetsStruct{
        MvaInputTopJetsStruct();
        
        /// Could b quark and anti-b quark be matched to reco jets
        bool bQuarkRecoJetMatched_;
        /// Is it the true correct jet combination
        bool correctCombination_;
        /// Is it the true but swapped jet combination
        bool swappedCombination_;
        
        /// Estimated event weight including all scale factors, at least for plotting needed
        double eventWeight_;
        
        /// Variables for MVA
        double meanDeltaPhi_b_met_;
        double massDiff_recoil_bbbar_;
        double pt_b_antiLepton_;
        double pt_antiB_lepton_;
        double deltaR_b_antiLepton_;
        double deltaR_antiB_lepton_;
        double btagDiscriminatorSum_;
        double deltaPhi_antiBLepton_bAntiLepton_;
        double massDiff_fullBLepton_bbbar_;
        double meanMT_b_met_;
        double massSum_antiBLepton_bAntiLepton_;
        double massDiff_antiBLepton_bAntiLepton_;
        double meanMTAlt_b_met_;
    };
    
    
    
    
    /// Empty constructor
    MvaInputTopJetsVariables();
    
    /// Constructor for writing via selector
    MvaInputTopJetsVariables(TSelectorList* selectorList);
        
    /// Destructor
    ~MvaInputTopJetsVariables(){};

    /// Create branches for TTree holding the input variables for MVA
    void createMvaInputBranches(TTree* tree);
    
    void addEntry(const LV& lepton, const LV& antiLepton,
                  const LV& bJet, const LV& antiBJet,
                  const double& bJetBtagDiscriminator, const double& antiBJetBtagDiscriminator,
                  const LV& jetRecoil, const LV& met,
                  const bool bQuarkRecoJetMatched, const bool correctCombination, const bool swappedCombination,
                  const double& eventWeight);
    
    std::vector<MvaInputTopJetsStruct> mvaInputStructs()const;
    
    void clear();
    
    void fillMvaInputBranches();
    
    void produceMvaInputTree(const std::string& f_savename);
    
    void mvaInputTopJetsVariablesControlPlots();
    
    
    
private:
    
    void addEntry(const MvaInputTopJetsStruct& mvaInputTopJetsStruct);
    
    
    // store the object in the output list and return it
    template<class T> T* store(T* obj);
    
    TTree* t_mvaInput_;
    
    MvaInputTopJetsStruct mvaInputStruct_;
    
    std::vector<MvaInputTopJetsStruct> v_mvaInputStruct_;
    
    TSelectorList* selectorList_;
};




template<class T>
inline T* MvaInputTopJetsVariables::store(T* obj){
    selectorList_->Add(obj);
    return obj;
}





#endif // MvaInputVariables_h






