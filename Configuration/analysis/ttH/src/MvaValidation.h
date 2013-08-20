#ifndef MvaValidation_h
#define MvaValidation_h

#include <vector>
#include <map>

class TString;
class TH1;

#include "AnalysisHistograms.h"

class MvaTopJetsVariables;
class JetCategories;
class RecoObjects;
class MvaReader;
namespace tth{
    class RecoObjectIndices;
    class GenObjectIndices;
}









/// Class for basic histograms that are filled simultaneously for any step
class MvaValidation : public AnalysisHistogramsBase{

public:
    
    /// Constructor
    MvaValidation(const char* weightsCorrectFile, const char* weightsSwappedFile,
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
    
    /// Book 1-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void bookHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                            const TString& name, const TString& title,
                            const int& nBinX, const double& xMin, const double& xMax);
    
    /// Book 1-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void bookHistosInclExcl2D(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                              const TString& name, const TString& title,
                              const int& nBinX, const double& xMin, const double& xMax,
                              const int& nBinY, const double& yMin, const double& yMax);
    
    /// Fill 1-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void fillHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& name,
                            const float& variable,
                            const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight =1.);
    
    /// Fill 1-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void fillHistosInclExcl2D(std::map<TString, TH1*>& m_histogram, const TString& name,
                              const float& variable1, const float& variable2,
                              const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight =1.);
    
    /// MVA weights of correct dijet assignment for top system
    MvaReader* weightsCorrect_;
    
    /// MVA weights of swapped dijet assignment for top system
    MvaReader* weightsSwapped_;
};




#endif







