#ifndef MvaInputVariables_h
#define MvaInputVariables_h

#include <vector>
#include <string>
#include <map>

class TTree;
class TSelectorList;
class TH1;
class TString;

#include "../../diLeptonic/src/classes.h"
#include "higgsUtils.h"





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
        
        /// Estimated event weight including all scale factors
        double eventWeight_;
        
        /// Difference of the jet charges for (anti-b jet - b jet), i.e. it is within [0,2]
        double jetChargeDiff_;
        
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
    
    /// Stuct holding histograms showing the full distributions and the separation power of variables
    struct PlotStruct{
        PlotStruct():
            h_correctCombination(0), h_swappedCombination(0),
            h_wrongCombinations(0), h_allCombinations(0){};
        TH1* h_correctCombination;
        TH1* h_swappedCombination;
        TH1* h_wrongCombinations;
        TH1* h_allCombinations;
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
                  const double& jetChargeDiff,
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
    
    /// Produce control plots for MVA input in own file with given filename
    void mvaInputVariablesControlPlots(const std::string& f_savename);
    
    /// Produce control plots for MVA input owned by a given selector list
    void mvaInputVariablesControlPlots(TSelectorList* output);
    
    /// Clear the class instance
    void clear();
    
    /// Import a written TTree
    void importTree(const std::string& f_savename, const std::string& treeName ="mvaInputTopJets");
    
    /// Get the MVA input structs
    std::vector<MvaInputTopJetsStruct> mvaInputStructs()const;
    
    
    
private:
    
    /// Import all branches from TTree
    void importBranches(TTree* tree);
    
    /// Book histograms to be hold by m_histogram_
    void bookHistograms(const TString& name, const TString& title, const int nBin, const double& xMin, const double& xMax);
    
    /// Fill histograms held by m_histogram_
    void fillHistograms(const TString& name, const double& variable, const MvaInputTopJetsStruct& mvaInputTopJetsStruct);
    
    /// Store the object in the output list and return it
    template<class T> T* store(T* obj){return Tools::store(obj, selectorList_);}
    
    
    
    /// Pointer for bookkeeping of histograms, trees, etc.
    TSelectorList* selectorList_;
    
    /// Pointer for steering I/O of MVA input TTree
    TTree* t_mvaInput_;
    
    /// Struct for setting addresses of MVA input tree branches
    MvaInputTopJetsStruct mvaInputStruct_;
    
    /// Storage of all entries for the MVA
    std::vector<MvaInputTopJetsStruct> v_mvaInputStruct_;
    
    /// Storage for the histograms to be filled
    std::map<TString, PlotStruct> m_plotStruct_;
};







#endif // MvaInputVariables_h







