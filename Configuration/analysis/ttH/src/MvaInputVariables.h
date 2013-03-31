#ifndef MvaInputVariables_h
#define MvaInputVariables_h

#include <vector>

#include <TSelectorList.h>

class TTree;

#include "../../diLeptonic/src/classes.h"





/// Class holding the input variables for MVA,
/// trying to identify the jets coming from (anti)b's from (anti)tops
class MvaInputTopJetsVariables{
    
private:
    
    /// Stuct holding the input variables for one entry for MVA,
    /// i.e. one entry of each quantity per selected jet combination
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
    
    
public:
    
    /// Empty constructor
    MvaInputTopJetsVariables();
    
    /// Destructor
    ~MvaInputTopJetsVariables(){};
    
    
    
    /// Add an entry
    void addEntry(const LV& lepton, const LV& antiLepton,
                  const LV& bJet, const LV& antiBJet,
                  const double& bJetBtagDiscriminator, const double& antiBJetBtagDiscriminator,
                  const LV& jetRecoil, const LV& met,
                  const bool bQuarkRecoJetMatched, const bool correctCombination, const bool swappedCombination,
                  const double& eventWeight);
    
    /// Create branches for TTree holding the input variables for MVA
    void createMvaInputBranches(TTree* tree);
    
    /// Fill branches of MVA input TTree
    void fillMvaInputBranches();
    
    /// Produce MVA input TTree in own file with given filename
    void produceMvaInputTree(const std::string& f_savename);
    
    /// Produce MVA input TTree owned by a given selectorList
    void produceMvaInputTree(TSelectorList* output);
    
    /// Produce control plots  for MVA input in own file with given filename
    void mvaInputTopJetsVariablesControlPlots(const std::string& f_savename);
    
    /// Produce control plots  for MVA input owned by a given selector list
    void mvaInputTopJetsVariablesControlPlots(TSelectorList* output);
    
    /// Clear the class instance
    void clear();
    
    
    
    /// Get the MVA input structs
    std::vector<MvaInputTopJetsStruct> mvaInputStructs()const;
    
    
    
private:
    
    /// Store the object in the output list and return it
    template<class T> T* store(T* obj);
    
    
    
    /// Pointer for bookkeeping of histograms, trees, etc.
    TSelectorList* selectorList_;
    
    /// Pointer for steering I/O of MVA input TTree
    TTree* t_mvaInput_;
    
    /// Struct for setting addresses of MVA input tree branches
    MvaInputTopJetsStruct mvaInputStruct_;
    
    /// Storage of all entries for the MVA
    std::vector<MvaInputTopJetsStruct> v_mvaInputStruct_;
};






template<class T>
inline T* MvaInputTopJetsVariables::store(T* obj){
    selectorList_->Add(obj);
    return obj;
}





#endif // MvaInputVariables_h







