#ifndef Playground_h
#define Playground_h

#include <vector>

class TString;

#include "AnalysisHistograms.h"

class RecoObjects;
class CommonGenObjects;
class TopGenObjects;
class HiggsGenObjects;
class KinRecoObjects;
class JetCategories;
namespace tth{
    class GenLevelWeights;
    class RecoLevelWeights;
    class GenObjectIndices;
    class RecoObjectIndices;
}








/// Playground class, test here whatever you want to test
class Playground : public AnalysisHistogramsBase{
    
public:
    
    /// Constructor
    Playground(const std::vector<TString>& selectionStepsNoCategories,
               const std::vector<TString>& stepsForCategories =std::vector<TString>(),
               const JetCategories* jetCategories =0);
    
    /// Destructor
    ~Playground(){}
    
    
    
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
};





#endif







