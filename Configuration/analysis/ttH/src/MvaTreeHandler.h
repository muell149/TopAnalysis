#ifndef MvaTreeHandler_h
#define MvaTreeHandler_h

#include <vector>
#include <string>

class TTree;
class TSelectorList;
class TString;

#include "mvaStructs.h"
#include "../../diLeptonic/src/storeTemplate.h"
#include "../../diLeptonic/src/sampleHelpers.h"

class RecoObjects;
namespace tth{
    //class GenLevelWeights;
    //class RecoLevelWeights;
    class GenObjectIndices;
    class RecoObjectIndices;
}






// For plotting
#include <map>
class TH1;






/// Class for handling the trees of input variables for MVA,
/// trying to identify the jets coming from (anti)b's from (anti)tops
class MvaTreeHandler{
    
public:
    
    
    
    /// Constructor for selection steps
    MvaTreeHandler(const char* mvaInputDir, const std::vector<TString>& selectionSteps);
    
    /// Destructor
    ~MvaTreeHandler(){}
    
    
    
    /// Fill all variables in the event loop
    void fillForInputProduction(const RecoObjects& recoObjects,
                                const tth::GenObjectIndices& genObjectIndices,
                                const tth::RecoObjectIndices& recoObjectIndices,
                                const double& weight,
                                const TString& selectionStep);
    
    /// Create branches for TTree holding the input variables for MVA
    void createMvaInputBranches(TTree* tree);
    
    /// Fill branches of MVA input TTree
    void fillMvaInputBranches();
    
    /// Produce MVA input TTree in own file
    void produceMvaInputTree(const std::string& outputFilename,
                             const Channel::Channel& channel, const Systematic::Systematic& systematic);
    
    /// Produce MVA input TTree owned by a given selectorList
    void produceMvaInputTree(TSelectorList* output);
    
    
    
    /// Import a written TTree
    void importTree(const std::string& f_savename, const std::string& treeName ="mvaInputTopJets");
    
    
    
    /// Clear the class instance
    void clear();
    
    
    
    // For plotting
    /// Plot the variables and write them to the specified folder
    /// If separationPowerPlots==true: plot them exclusively for the cases of correct, swapped and wrong combinations to see separation power
    /// If separationPowerPlots==false: plot them inclusively for data/MC comparisons
    void plotVariables(const std::string& f_savename, const bool separationPowerPlots =false);
    
    /// Plot the variables and store the histograms in the specified TSelectorList
    /// If separationPowerPlots==true: plot them exclusively for the cases of correct, swapped and wrong combinations to see separation power
    /// If separationPowerPlots==false: plot them inclusively for data/MC comparisons
    void plotVariables(TSelectorList* output, const bool separationPowerPlots =false);
    
    
    
    
    
    
private:
    
    /// Store the object in the output list and return it
    template<class T> T* store(T* obj){return ttbar::store(obj, selectorList_);}
    
    
    
    /// Create single branch for TTree based on MvaInputVariables structs of type int
    void createBranch(const MvaVariableInt& variable);
    
    /// Create single branch for TTree based on MvaInputVariables structs of type int
    void createBranch(const MvaVariableFloat& variable);
    
    /// Import all branches from TTree
    void importBranches(TTree* tree);
    
    /// Import branch of type Int_t
    void importBranch(TTree* tree, MvaVariableInt& variable);
    
    /// Import branch of type Float_t
    void importBranch(TTree* tree, MvaVariableFloat& variable);
    
    
    
    /// Pointer for bookkeeping of histograms, trees, etc.
    TSelectorList* selectorList_;
    
    
    
    /// Pointer for steering I/O of MVA input TTree
    TTree* t_mvaInput_;
    
    /// Struct for setting addresses of MVA input tree branches
    MvaTopJetsVariables mvaTopJetsVariables_;
    
    /// Storage of all entries for the MVA
    std::vector<MvaTopJetsVariables> v_mvaTopJetsVariables_;
    
    /// Selection steps for which to run the MVA tool
    const std::vector<TString> selectionSteps_;
    
    /// The folder where to store the input for MVA
    const char* mvaInputDir_;
    
    
    
    
    
    
    // For plotting
    /// Struct holding the histograms for one selection step
    struct StepHistograms{
        /// Constructor
        StepHistograms(){};
        /// Destructor
        ~StepHistograms(){};

        /// The map with all the histograms for one selection step
        std::map<TString, TH1*> m_histogram_;
    };
    
    /// The map containing all the step histograms for all selection steps
    std::map<TString, StepHistograms> m_stepHistograms_;
    
    
    
    /// Book 1-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void bookHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                            const TString& name, const TString& title,
                            const int& nBinX, const double& xMin, const double& xMax);
    
    /// Fill 1-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void fillHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& name,
                            const double& variable,
                            const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight =1.);
    
    /// Whether to produce plots inclusively, or exclusively for correct, swapped and wrong combinations
    bool plotExclusively_;
};







#endif







