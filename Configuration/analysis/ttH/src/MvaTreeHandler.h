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




/// Class holding the input variables for MVA,
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
    
    /// Clear the class instance
    void clear();
    
    /// Import a written TTree
    void importTree(const std::string& f_savename, const std::string& treeName ="mvaInputTopJets");
    
    /// Get the MVA input structs
//    std::vector<Input> inputStructs()const;
    
    
    
private:
    
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
    
    /// Store the object in the output list and return it
    template<class T> T* store(T* obj){return ttbar::store(obj, selectorList_);}
    
    
    
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
    
};







#endif







