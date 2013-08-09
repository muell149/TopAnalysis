#ifndef MvaValidation_h
#define MvaValidation_h

#include <vector>

class TString;

#include "AnalysisHistograms.h"

class JetCategories;
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
    MvaValidation(MvaInputTopJetsVariables* weightsCorrect, MvaInputTopJetsVariables* weightsSwapped,
                  const std::vector<TString>& selectionStepsNoCategories,
                  const std::vector<TString>& stepsForCategories =std::vector<TString>(),
                  const JetCategories* jetCategories =0);
    
    /// Destructor
    ~MvaValidation(){}
    
    /// Fill histograms
    void fill(const RecoObjects& recoObjects,
              const tth::GenObjectIndices& genObjectIndices, const tth::RecoObjectIndices& recoObjectIndices,
              const double& weight, const TString& stepShort);
    
    
    
private:
    
    /// Book all histograms for given selection step
    virtual void bookHistos(const TString& step);
    
    /// MVA weights of correct dijet assignment for top system
    MvaInputTopJetsVariables* weightsCorrect_;
    
    /// MVA weights of swapped dijet assignment for top system
    MvaInputTopJetsVariables* weightsSwapped_;
};




#endif







