#ifndef MvaFactory_h
#define MvaFactory_h

#include <vector>
#include <string>
#include <utility>

#include <TMVA/Types.h>

class TFile;
class TTree;
class TString;
class TCut;
namespace TMVA{
    class Factory;
}

#include "../../diLeptonic/src/sampleHelpers.h"

class MvaVariableInt;
class MvaVariableFloat;





/// Class holding the input variables for MVA,
/// trying to identify the jets coming from (anti)b's from (anti)tops
class MvaFactory{
    
public:
    
    /// Struct keeping steering parameters for MVA training
    struct MvaConfig{
        MvaConfig(const TString& options,
                  const TString& methodAppendix,
                  const TMVA::Types::EMVA& mvaType =TMVA::Types::kBDT);
        ~MvaConfig(){}
        
        TMVA::Types::EMVA mvaType_;
        TString methodAppendix_;
        TString options_;
    };
    
    
    
    /// Struct for setting up same set of MvaConfigs in different event selections
    struct MvaSet{
        MvaSet(const std::vector<MvaConfig>& v_mvaConfig,
               const std::vector<int>& v_category,
               const std::vector<Channel::Channel>& channel,// ={Channel::combined},
               const TString& step ="10");
        ~MvaSet(){}
        
        std::vector<TString> stepNames()const;
        
        std::vector<Channel::Channel> v_channel_;
        TString step_;
        std::vector<int> v_category_;
        std::vector<MvaConfig> v_mvaConfig_;
    };
    
    
    
    /// Clean a vector of MVA sets for non-selected ones
    static std::vector<MvaFactory::MvaSet> cleanSets(const std::vector<MvaFactory::MvaSet>& v_mvaSet,
                                                     const std::vector<std::pair<TString, TString> >& v_nameStepPair,
                                                     const Channel::Channel& channel);
    
    /// Select a vector of MVA sets valid for given selection step
    static std::vector<MvaFactory::MvaSet> selectSets(const std::vector<MvaFactory::MvaSet>& v_mvaSet,
                                                      const TString& step);
    
    
    
    /// Constructor
    MvaFactory(const TString& mvaOutputDir, const char* weightFileDir,
               const std::vector<std::pair<TString, TString> >& v_nameStepPair,
               TFile* mergedTrees);
    
    /// Destructor
    ~MvaFactory(){};
    
    
    
    /// Run the MVA training
    void train(const std::vector<MvaSet>& v_mvaSetCorrect, const std::vector<MvaSet>& v_mvaSetSwapped);
    
    /// Clear the class instance
    void clear();
    
    
    
    
    
private:
    
    /// Add a variable to the factory of type Int_t
    void addVariable(TMVA::Factory* factory, MvaVariableInt& variable);
    
    /// Add a variable to the factory of type Float_t
    void addVariable(TMVA::Factory* factory, MvaVariableFloat& variable);
    
    /// Add a spectator to the factory of type Int_t
    void addSpectator(TMVA::Factory* factory, MvaVariableInt& variable);
    
    /// Add a spectator to the factory of type Float_t
    void addSpectator(TMVA::Factory* factory, MvaVariableFloat& variable);
    
    /// Run the MVA for given parameters
    void runMva(const char* methodPrefix, const TCut& cutSignal, const TCut& cutBackground,
                TTree* treeTraining, TTree* treeTesting,
                const std::vector<MvaSet>& v_mvaSet,
                const TString& stepName);
    
    
    
    /// Selection steps and corresponding names of trees for which to run the MVA tool
    const std::vector<std::pair<TString, TString> > v_nameStepPair_;
    
    /// The folder where to store the input for MVA
    const TString mvaOutputDir_;
    
    /// The sub-folder where to store MVA weights
    const char* weightFileDir_;
    
    /// Thei file containing the input trees for MVA training
    TFile* mergedTrees_;
};







#endif







