#ifndef MvaValidation_h
#define MvaValidation_h

#include <vector>

class TString;

#include "AnalysisHistograms.h"

class RecoObjects;
class MvaInputTopJetsVariables;
namespace tth{
    class RecoObjectIndices;
    class GenObjectIndices;
}









/// Class for basic histograms that are filled simultaneously for any step
class MvaValidation : public AnalysisHistogramsBase{

public:
    
    /// Constructor
    MvaValidation(const std::vector<TString>& selectionSteps,
                  MvaInputTopJetsVariables* weightsCorrect, MvaInputTopJetsVariables* weightsSwapped);
    
    /// Destructor
    ~MvaValidation(){}
    
    /// Fill histograms
    void fill(const RecoObjects& recoObjects,
              const tth::GenObjectIndices& genObjectIndices, const tth::RecoObjectIndices& recoObjectIndices,
              const double& weight, const TString& step);
    
    
    
private:
    
    /// Book all histograms for given selection step
    virtual void bookHistos(const TString& step);
    
    /// MVA weights of correct dijet assignment for top system
    MvaInputTopJetsVariables* weightsCorrect_;
    
    /// MVA weights of swapped dijet assignment for top system
    MvaInputTopJetsVariables* weightsSwapped_;
};




#endif







