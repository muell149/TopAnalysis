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

#include "../../common/include/sampleHelpers.h"

class MvaVariableInt;
class MvaVariableFloat;
namespace mvaSetup{
    class MvaSet;
    class MvaConfig;
}




/// Class holding the input variables for MVA,
/// trying to identify the jets coming from (anti)b's from (anti)tops
class MvaFactory{
    
public:
    
    /// Constructor
    MvaFactory(const TString& mvaOutputDir, const char* weightFileDir,
               const std::vector<mvaSetup::MvaSet>& v_mvaSet,
               const TString& mergedTreesFileName);
    
    /// Destructor
    ~MvaFactory(){};
    
    
    
    /// Clear the class instance
    void clear();
    
    
    
    
    
private:
    
    /// Train MVAs for given MVA sets
    void train(const std::vector<mvaSetup::MvaSet>& v_mvaSet);
    
    /// Run the MVA for given parameters
    void runMva(const char* methodPrefix, const TCut& cutSignal, const TCut& cutBackground,
                TTree* treeTraining, TTree* treeTesting,
                const std::vector<mvaSetup::MvaConfig>& v_mvaSet,
                const TString& stepName);
    
    /// Add a variable to the factory of type Int_t
    void addVariable(TMVA::Factory* factory, MvaVariableInt& variable);
    
    /// Add a variable to the factory of type Float_t
    void addVariable(TMVA::Factory* factory, MvaVariableFloat& variable);
    
    /// Add a spectator to the factory of type Int_t
    void addSpectator(TMVA::Factory* factory, MvaVariableInt& variable);
    
    /// Add a spectator to the factory of type Float_t
    void addSpectator(TMVA::Factory* factory, MvaVariableFloat& variable);
    
    
    
    /// Selection steps and corresponding names of trees for which to run the MVA tool
    const std::vector<std::pair<TString, TString> > v_nameStepPair_;
    
    /// The folder where to store the input for MVA
    const TString mvaOutputDir_;
    
    /// The sub-folder where to store MVA weights
    const char* weightFileDir_;
    
    /// Thei file containing the input trees for MVA training
    TFile* mergedTreesFile_;
};







#endif







