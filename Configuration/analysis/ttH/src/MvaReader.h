#ifndef MvaReader_h
#define MvaReader_h

#include <vector>

#include <Rtypes.h>

class TString;

namespace TMVA{
    class Reader;
}

#include "mvaStructs.h"





/// Class for reading MVA weights from file,
/// based on set of MVA input variables per event
class MvaReader{
    
public:
    
    /// Constructor which sets MVA weights and creating TMVA Reader
    MvaReader(const char* mvaWeightsFile, const std::vector<TString>& selectionSteps);
    
    /// Destructor
    ~MvaReader(){};
    
    
    
    /// Clear the class instance
    void clear();
    
    /// Get the MVA input structs
//    std::vector<Input> inputStructs()const;
    
    
    
    /// Get the MVA weights for all jet pairs from weights file
    std::vector<float> mvaWeights(const std::vector<MvaTopJetsVariables>& v_mvaTopJetsVariables);
    
    
    
private:
    
    /// Add a variable to MVA reader of type Int_t
    void addVariable(MvaVariableInt& variable);
    
    /// Add a variable to MVA reader of type Float_t
    void addVariable(MvaVariableFloat& variable);
    
    /// Add a spectator to MVA reader of type Int_t
    void addSpectator(MvaVariableInt& variable);
    
    /// Add a spectator to MVA reader of type Float_t
    void addSpectator(MvaVariableFloat& variable);
    
    
    
    /// Storage of all entries for the MVA
    std::vector<MvaTopJetsVariablesPerEvent> v_mvaTopJetsVariablesPerEvent_;
    
    /// Pointer to TMVA Reader, i.e. tool for reading in MVA weights
    TMVA::Reader* mvaWeightsReader_;
    
    /// Struct for setting addresses of variables for mvaWeightsReader_
    MvaTopJetsVariables mvaTopJetsVariables_;
    
    
    /// Selection steps for which to run the MVA tool
    const std::vector<TString> selectionSteps_;
};







#endif







