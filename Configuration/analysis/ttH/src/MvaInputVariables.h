#ifndef MvaInputVariables_h
#define MvaInputVariables_h

#include <vector>
#include <string>
#include <map>

#include <Rtypes.h>

class TTree;
class TSelectorList;
class TH1;
class TString;

namespace TMVA{
    class Reader;
}

#include "../../diLeptonic/src/storeTemplate.h"
#include "../../diLeptonic/src/classesFwd.h"





/// Class holding the input variables for MVA,
/// trying to identify the jets coming from (anti)b's from (anti)tops
class MvaInputTopJetsVariables{
    
public:
    
    /// Stuct holding the input variables for one entry for MVA,
    /// i.e. one entry of each quantity per selected jet combination
    struct Input{
        
        /// Empty constructor
        Input();
        
        /// Constructor setting up input variables from physics objects
        Input(const LV& lepton, const LV& antiLepton,
              const LV& bJet, const LV& antiBJet,
              const double& bJetBtagDiscriminator, const double& antiBJetBtagDiscriminator,
              const double& jetChargeDiff,
              const LV& jetRecoil, const LV& met,
              const bool bQuarkRecoJetMatched,
              const bool correctCombination, const bool swappedCombination,
              const double& eventWeight =1.);
        
        /// Destructor
        ~Input(){}
        
        /// Could b quark and anti-b quark be matched to reco jets
        Int_t bQuarkRecoJetMatched_;
        /// Is it the true correct jet combination
        Int_t correctCombination_;
        /// Is it the true but swapped jet combination
        Int_t swappedCombination_;
        
        /// Estimated event weight including all scale factors
        Float_t eventWeight_;
        
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
    
    
    
    /// Empty constructor
    MvaInputTopJetsVariables();
    
    /// Constructor for setting input file MVA weights, and creating TMVA Reader
    MvaInputTopJetsVariables(const char* mvaWeightsFile);
    
    /// Destructor
    ~MvaInputTopJetsVariables(){};
    
    
    
    /// Add entries to the stored MVA input structs
    void addEntries(const std::vector<Input>& v_input);
    
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
    std::vector<Input> inputStructs()const;
    
    
    
    /// Get the MVA weights for all jet pairs from weights file
    std::vector<float> mvaWeights(const std::vector<Input>& v_input);
    
    
    
private:
    
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
    
    
    
    /// Import all branches from TTree
    void importBranches(TTree* tree);
    
    /// Book histograms to be hold by m_histogram_
    void bookHistograms(const TString& name, const TString& title, const int nBin, const double xMin, const double xMax);
    
    /// Fill histograms held by m_histogram_
    void fillHistograms(const TString& name, const double& variable, const Input& mvaInputTopJetsStruct);
    
    /// Store the object in the output list and return it
    template<class T> T* store(T* obj){return ttbar::store(obj, selectorList_);}
    
    
    
    /// Pointer for bookkeeping of histograms, trees, etc.
    TSelectorList* selectorList_;
    
    /// Pointer for steering I/O of MVA input TTree
    TTree* t_mvaInput_;
    
    /// Struct for setting addresses of MVA input tree branches
    Input inputStruct_;
    
    /// Storage of all entries for the MVA
    std::vector<Input> v_inputStruct_;
    
    /// Storage for the histograms to be filled
    std::map<TString, PlotStruct> m_plotStruct_;
    
    
    
    
    /// Pointer to TMVA Reader, i.e. tool for reading in MVA weights
    TMVA::Reader* mvaWeightsReader_;
    
    
    /// Struct for setting addresses of variables for mvaWeightsReader_
    Input mvaWeightsStruct_;
};







#endif // MvaInputVariables_h







