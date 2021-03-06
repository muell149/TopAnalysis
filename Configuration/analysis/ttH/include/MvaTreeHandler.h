#ifndef MvaTreeHandler_h
#define MvaTreeHandler_h

#include <vector>
#include <string>
#include <map>

class TTree;
class TSelectorList;
class TString;

#include "mvaStructs.h"
#include "../../common/include/storeTemplate.h"
#include "../../common/include/sampleHelpers.h"

class JetCategories;
class RecoObjects;
namespace tth{
    //class GenLevelWeights;
    //class RecoLevelWeights;
    class GenObjectIndices;
    class RecoObjectIndices;
}






/// Class for handling the trees of input variables for MVA,
/// trying to identify the jets coming from (anti)b's from (anti)tops
class MvaTreeHandler{
    
public:
    
    /// Constructor for selection steps
    MvaTreeHandler(const char* mvaInputDir,
                   const std::vector<TString>& selectionStepsNoCategories,
                   const std::vector<TString>& stepsForCategories =std::vector<TString>(),
                   const JetCategories* jetCategories =0);
    
    /// Destructor
    ~MvaTreeHandler(){}
    
    
    
    /// Book the vector of MVA variables for each requested selection step
    void book();
    
    /// Fill the vector of MVA variables for given selection step
    void fill(const RecoObjects& recoObjects,
              const tth::GenObjectIndices& genObjectIndices, const tth::RecoObjectIndices& recoObjectIndices,
              const double& weight, const TString& stepShort);
    
    /// Write trees with MVA input variables in own file
    void writeTrees(const std::string& outputFilename,
                    const Channel::Channel& channel, const Systematic::Systematic& systematic);
    
    /// Write trees with MVA input variables owned by a given selectorList
    void writeTrees(TSelectorList* output);
    
    /// Return a constant reference to the map containing all the vectors of MVA variables for all selection steps
    const std::map<TString, std::vector<MvaTopJetsVariables> >& stepMvaVariablesMap()const;
    
    /// Import written TTrees
    void importTrees(const std::string& f_savename, const std::string& prefix ="");
    
    
    
    /// Clear the class instance
    void clear();
    
    
    
private:
    
    /// Store the object in the output list and return it
    template<class T> T* store(T* obj){return common::store(obj, selectorList_);}
    
    
    
    /// Add a new selection step
    void addStep(const TString& step);
    
    /// Check if selection step exists
    bool checkExistence(const TString& step)const;
    
    /// Create branches for TTree holding the input variables for MVA
    void createBranches(TTree* tree, const MvaTopJetsVariables& mvaTopJetsVariables)const;
    
    /// Create single branch for TTree based on MvaInputVariables structs of type int
    void createBranch(TTree* tree, const MvaVariableInt& variable)const;
    
    /// Create single branch for TTree based on MvaInputVariables structs of type int
    void createBranch(TTree* tree, const MvaVariableFloat& variable)const;
    
    /// Fill branches of MVA input TTree
    void fillBranches(TTree* tree, MvaTopJetsVariables& mvaTopJetsVariables,
                      const std::vector<MvaTopJetsVariables>& v_mvaTopJetsVariables)const;
    
    /// Import all branches from TTree
    void importBranches(TTree* tree, std::vector<MvaTopJetsVariables>& mvaTopJetsVariables);
    
    /// Import branch of type Int_t
    void importBranch(TTree* tree, MvaVariableInt& variable);
    
    /// Import branch of type Float_t
    void importBranch(TTree* tree, MvaVariableFloat& variable);
    
    
    
    /// Pointer for bookkeeping of histograms, trees, etc.
    TSelectorList* selectorList_;
    
    /// The map containing all the vectors of MVA variables for all selection steps
    std::map<TString, std::vector<MvaTopJetsVariables> > m_stepMvaVariables_;
    
    /// Selection steps for which to run the MVA tool
    const std::vector<TString> selectionSteps_;
    
    /// The vector of selection steps where analysis should also be performed in individual jet categories
    const std::vector<TString> stepsForCategories_;
    
    /// The categories in no. of jets and b-jets
    const JetCategories* jetCategories_;
    
    /// The folder where to store the input for MVA
    const char* mvaInputDir_;
};





namespace tth{
    namespace mvaHelpers{
        typedef std::map<Systematic::Systematic, std::map<Channel::Channel, std::vector<TString> > > SystematicChannelFileNames;
        
        SystematicChannelFileNames systematicChannelFileNames(const char* fileListBase,
                                                              const std::vector<Channel::Channel>& v_channel,
                                                              const std::vector<Systematic::Systematic>& v_systematic,
                                                              const bool forTraining =true);
        
        SystematicChannelFileNames mergeTrees(const char* mvaInputDir,
                                              const SystematicChannelFileNames& m_systematicChannelFileNamesTraining,
                                              const SystematicChannelFileNames& m_systematicChannelFileNamesTesting,
                                              const std::vector<std::pair<TString, TString> >& v_nameStepPair);
    }
}






#endif







