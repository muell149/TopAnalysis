#ifndef MvaValidation_h
#define MvaValidation_h

#include <vector>
#include <map>

class TString;
class TH1;
class TH2D;

#include "AnalysisHistograms.h"
#include "mvaStructs.h"

class JetCategories;
class RecoObjects;
class CommonGenObjects;
class TopGenObjects;
class HiggsGenObjects;
class KinRecoObjects;
class MvaTopJetsVariables;
class MvaReader;
namespace tth{
    class RecoLevelWeights;
    class GenLevelWeights;
    class RecoObjectIndices;
    class GenObjectIndices;
}









/// Class for basic histograms that are filled simultaneously for any step
class MvaValidation : public AnalysisHistogramsBase{

public:

    /// Constructor
    MvaValidation(const char* weightsCorrectFile, const char* weightsSwappedFile,
                  const char* mva2dWeightsDir, const char* mva2dWeightsHisto,
                  const std::vector<TString>& selectionStepsNoCategories,
                  const std::vector<TString>& stepsForCategories =std::vector<TString>(),
                  const JetCategories* jetCategories =0);

    /// Destructor
    ~MvaValidation(){}



private:

    /// Book all histograms for given selection step
    virtual void bookHistos(const TString& step, std::map<TString, TH1*>& m_histogram);

    /// Fill all histograms for given selection step
    virtual void fillHistos(const RecoObjects& recoObjects, const CommonGenObjects& commonGenObjects,
                            const TopGenObjects& topGenObjects, const HiggsGenObjects& higgsGenObjects,
                            const KinRecoObjects& kinRecoObjects,
                            const tth::RecoObjectIndices& recoObjectIndices, const tth::GenObjectIndices& genObjectIndices,
                            const tth::GenLevelWeights& genLevelWeights, const tth::RecoLevelWeights& recoLevelWeights,
                            const double& weight, const TString& step,
                            std::map<TString, TH1*>& m_histogram);


    /// Fill all histograms that are specific to a signel MVA training
    void fillMVASpecificHistograms(const std::vector<float>& v_mvaWeights, const MvaTopJetsVariablesPerEvent& mvaTopJetsVariablesPerEvent,
                                   std::map< TString, TH1* >& m_histogram, const RecoObjects& recoObjects,
                                   const tth::RecoObjectIndices& recoObjectIndices, const tth::GenObjectIndices& genObjectIndices,
                                   std::string mvaName, const double& weight, bool fillGenericHistograms);

    /// Book 1-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void bookHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                            const TString& name, const TString& title,
                            const int& nBinX, const double& xMin, const double& xMax);

    /// Book 2-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void bookHistosInclExcl2D(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                              const TString& name, const TString& title,
                              const int& nBinX, const double& xMin, const double& xMax,
                              const int& nBinY, const double& yMin, const double& yMax);

    /// Fill 1-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void fillHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& name,
                            const float& variable,
                            const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight =1.);

    /// Fill 2-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void fillHistosInclExcl2D(std::map<TString, TH1*>& m_histogram, const TString& name,
                              const float& variable1, const float& variable2,
                              const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight =1.);



    /// MVA weights of correct dijet assignment for top system
    MvaReader* weightsCorrect_;

    /// MVA weights of swapped dijet assignment for top system
    MvaReader* weightsSwapped_;



    TH2D* weights2d_;
};




#endif







