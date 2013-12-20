#ifndef mvaStructs_h
#define mvaStructs_h

#include <map>
#include <vector>
#include <string>

#include <Rtypes.h>

class TBranch;

#include "analysisStructsFwd.h"
#include "../../common/include/classesFwd.h"

class RecoObjects;
namespace tth{
    class RecoObjectIndices;
    class GenObjectIndices;
}






// /// Templated struct which defines all relevant parameters for MVA input variables
// template<class T> struct MvaVariable{
//     MvaVariable(const char* name):
//         branch_(0), name_(name){}
//     
// public:
//     T value_;
//     TBranch* branch_;
//     
//     std::string name()const{return name_;}
//     char type()const{return type_;}
//     
// private:
//     const char* name_;
//     static constexpr char type_ = 'I';
// };



/// Struct which defines all relevant parameters for MVA input variables of type int
struct MvaVariableInt{
    MvaVariableInt(const char* name):
        value_(-999), branch_(0), name_(name){}
    
public:
    Int_t value_;
    TBranch* branch_;
    
    std::string name()const{return name_;}
    const char* type()const{return type_;}
    
private:
    const char* name_;
    static constexpr const char* type_ = "I";
};



/// Struct which defines all relevant parameters for MVA input variables of type float
struct MvaVariableFloat{
    MvaVariableFloat(const char* name):
        value_(-999.F), branch_(0), name_(name){}
    
public:
    Float_t value_;
    TBranch* branch_;
    
    std::string name()const{return name_;}
    const char* type()const{return type_;}
    
private:
    const char* name_;
    static constexpr const char* type_ = "F";
};



/// Stuct holding the input variables for one entry for MVA,
/// i.e. one entry of each quantity per selected jet combination
struct MvaTopJetsVariables{
    
public:
    
    /// Empty constructor
    MvaTopJetsVariables();
    
    /// Constructor setting up input variables from physics objects
    MvaTopJetsVariables(const LV& lepton, const LV& antiLepton,
                        const LV& bJet, const LV& antiBJet,
                        const double& bJetBtagDiscriminator, const double& antiBJetBtagDiscriminator,
                        const double& jetChargeDiff,
                        const LV& jetRecoil, const LV& met,
                        const bool bQuarkRecoJetMatched,
                        const bool correctCombination, const bool swappedCombination,
                        const bool lastInEvent,
                        const double& eventWeight);
    
    /// Destructor
    ~MvaTopJetsVariables(){}
    
    /// Fill the MVA input structs for all jet combinations of one event
    static std::vector<MvaTopJetsVariables> fillVariables(const tth::RecoObjectIndices& recoObjectIndices,
                                                          const tth::GenObjectIndices& genObjectIndices,
                                                          const RecoObjects& recoObjects,
                                                          const double& eventWeight);
    
    /// Calculate the jet recoil for a given jet pair, i.e. vector sum of all jets except selected jet pair
    static VLV recoilForJetPairs(const tth::IndexPairs& jetIndexPairs,
                                 const std::vector<int>& jetIndices,
                                 const VLV& jets);
    
    
    
    // The variables needed for MVA
    
    /// Is it the last dijet combination in the event
    MvaVariableInt lastInEvent_;
    /// Could b quark and anti-b quark be matched to reco jets
    MvaVariableInt bQuarkRecoJetMatched_;
    /// Is it the true correct jet combination
    MvaVariableInt correctCombination_;
    /// Is it the true but swapped jet combination
    MvaVariableInt swappedCombination_;
    
    /// Event weight including all scale factors
    MvaVariableFloat eventWeight_;
    
    /// Difference of the jet charges for (anti-b jet - b jet), i.e. it is within [0,2]
    MvaVariableFloat jetChargeDiff_;
    /// Variables for MVA
    MvaVariableFloat meanDeltaPhi_b_met_;
    MvaVariableFloat massDiff_recoil_bbbar_;
    MvaVariableFloat pt_b_antiLepton_;
    MvaVariableFloat pt_antiB_lepton_;
    MvaVariableFloat deltaR_b_antiLepton_;
    MvaVariableFloat deltaR_antiB_lepton_;
    MvaVariableFloat btagDiscriminatorSum_;
    MvaVariableFloat deltaPhi_antiBLepton_bAntiLepton_;
    MvaVariableFloat massDiff_fullBLepton_bbbar_;
    MvaVariableFloat meanMt_b_met_;
    MvaVariableFloat massSum_antiBLepton_bAntiLepton_;
    MvaVariableFloat massDiff_antiBLepton_bAntiLepton_;
    
    
    
private:
    
    // The names associated to the variables
    
    static constexpr const char* name_lastInEvent_ = "lastInEvent";
    static constexpr const char* name_bQuarkRecoJetMatched_ = "bQuarkRecoJetMatched";
    static constexpr const char* name_correctCombination_ = "correctCombination";
    static constexpr const char* name_swappedCombination_ = "swappedCombination";
    
    static constexpr const char* name_eventWeight_ = "eventWeight";
    
    static constexpr const char* name_jetChargeDiff_ = "jetChargeDiff";
    static constexpr const char* name_meanDeltaPhi_b_met_ = "meanDeltaPhi_b_met";
    static constexpr const char* name_massDiff_recoil_bbbar_ = "massDiff_recoil_bbbar";
    static constexpr const char* name_pt_b_antiLepton_ = "pt_b_antiLepton";
    static constexpr const char* name_pt_antiB_lepton_ = "pt_antiB_lepton";
    static constexpr const char* name_deltaR_b_antiLepton_ = "deltaR_b_antiLepton";
    static constexpr const char* name_deltaR_antiB_lepton_ = "deltaR_antiB_lepton";
    static constexpr const char* name_btagDiscriminatorSum_ = "btagDiscriminatorSum";
    static constexpr const char* name_deltaPhi_antiBLepton_bAntiLepton_ = "deltaPhi_antiBLepton_bAntiLepton";
    static constexpr const char* name_massDiff_fullBLepton_bbbar_ = "massDiff_fullBLepton_bbbar";
    static constexpr const char* name_meanMt_b_met_ = "meanMt_b_met";
    static constexpr const char* name_massSum_antiBLepton_bAntiLepton_ = "massSum_antiBLepton_bAntiLepton";
    static constexpr const char* name_massDiff_antiBLepton_bAntiLepton_ = "massDiff_antiBLepton_bAntiLepton";
};




/// Stuct holding the input variables for all jet combinations of one event for MVA,
/// potentially together with estimated MVA weights for correct and swapped combinations
struct MvaTopJetsVariablesPerEvent{
    
public:
    
    /// Constructor setting up mvaInputVariables
    MvaTopJetsVariablesPerEvent(const std::vector<MvaTopJetsVariables>& v_mvaInputVariables);
    
    /// Constructor setting up mvaInputVariables together with MVA weights for correct and for swapped combinations
    MvaTopJetsVariablesPerEvent(const std::vector<MvaTopJetsVariables>& v_mvaInputVariables,
                                const std::map<std::string, std::vector<float> >& m_weightCorrect,
                                const std::map<std::string, std::vector<float> >& m_weightSwapped,
                                const std::map<std::string, std::map<std::string, std::vector<float> > >& m_weightCombined);
    
    /// Destructor
    ~MvaTopJetsVariablesPerEvent(){}
    
    
    
    /// Index of dijet combination with maximum correct MVA weight for given config name
    size_t maxWeightCorrectIndex(const std::string& mvaConfigName)const;
    
    /// Index of dijet combination with maximum swapped MVA weight for given config name
    size_t maxWeightSwappedIndex(const std::string& mvaConfigName)const;
    
    /// Index of dijet combination with maximum combined MVA weight for given config names
    size_t maxWeightCombinedIndex(const std::string& mvaConfigNameCorrect, const std::string& mvaConfigNameSwapped)const;
    
    /// Returns the maximum correct MVA weight per event for given config name
    float maxWeightCorrect(const std::string& mvaConfigName)const;
    
    /// Returns the maximum swapped MVA weight per event for given config name
    float maxWeightSwapped(const std::string& mvaConfigName)const;
    
    /// Returns the maximum combined MVA weight per event for given config names
    float maxWeightCombined(const std::string& mvaConfigNameCorrect, const std::string& mvaConfigNameSwapped)const;
    
    /// Does the same dijet combination have the maximum correct and the maximum swapped weight per event for given config names
    bool isSameMaxCombination(const std::string& mvaConfigNameCorrect, const std::string& mvaConfigNameSwapped)const;
    
    /// Get the vector of MVA variables
    std::vector<MvaTopJetsVariables> variables()const;
    
    /// Get the vector of MVA correct weights for given config name
    std::vector<float> mvaWeightsCorrect(const std::string& mvaConfigName)const;
    
    /// Get the vector of MVA swapped weights for given config name
    std::vector<float> mvaWeightsSwapped(const std::string& mvaConfigName)const;
    
    /// Get the vector of MVA combined weights for given config names
    std::vector<float> mvaWeightsCombined(const std::string& mvaConfigNameCorrect, const std::string& mvaConfigNameSwapped)const;
    
    /// Get the vector of MVA correct weights
    std::map<std::string, std::vector<float> > mvaWeightsCorrectMap()const;
    
    /// Get the vector of MVA swapped weights
    std::map<std::string, std::vector<float> > mvaWeightsSwappedMap()const;
    
    /// Get the vector of MVA combined weights
    std::map<std::string, std::map<std::string, std::vector<float> > > mvaWeightsCombinedMap()const;
    
    
    
private:
    
    /// Vector containing MVA input variables for all dijet pairs per event
    std::vector<MvaTopJetsVariables> v_mvaTopJetsVariables_;
    
    /// Map MVA config name to the vector containing correct MVA weights for all dijet pairs per event
    std::map<std::string, std::vector<float> > m_weightCorrect_;
    
    /// Map MVA config name to the vector containing swapped MVA weights for all dijet pairs per event
    std::map<std::string, std::vector<float> > m_weightSwapped_;
    
    /// Map MVA config name to the vector containing swapped MVA weights for all dijet pairs per event
    std::map<std::string, std::map<std::string, std::vector<float> > > m_weightCombined_;
};









#endif







