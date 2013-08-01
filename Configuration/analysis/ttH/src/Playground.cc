#include <iostream>

#include "TString.h"
#include "TH1.h"
#include "TH1D.h"

#include "Playground.h"
#include "analysisStructs.h"
#include "JetCategories.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"



Playground::Playground(const std::vector<TString>& selectionStepsNoCategories,
                       const std::vector<TString>& stepsForCategories,
                       const JetCategories* jetCategories):
AnalysisHistogramsBase(selectionStepsNoCategories, stepsForCategories, jetCategories)
{
    std::cout<<"--- Beginning setting up playground\n";
    std::cout<<"=== Finishing setting up playground\n\n";
}



void Playground::bookHistos(const TString& step)
{
    constexpr const char* prefix = "test_";
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    TString name;
    
    
    // Book histograms here
    name = "blah1";
    m_histogram[name] = this->store(new TH1D(prefix+name+step,"histo title;x axis;y axis",10,0,100));
    
    name = "blah2_blubb";
    m_histogram[name] = this->store(new TH1D(prefix+name+step,"histo title;x axis;y axis",10,0,100));
}



void Playground::fill(const RecoObjects& recoObjects, const CommonGenObjects& commonGenObjects,
                      const TopGenObjects& topGenObjects, const HiggsGenObjects& higgsGenObjects,
                      const KinRecoObjects& kinRecoObjects,
                      const tth::GenObjectIndices& genObjectIndices, const tth::RecoObjectIndices& recoObjectIndices,
                      const tth::GenLevelWeights& genLevelWeights, const tth::RecoLevelWeights& recoLevelWeights,
                      const double& weight, const TString& stepShort)
{
    // Set up step name and check if step exists
    const bool stepInCategory = stepShort.Contains("_cate");
    const TString step = stepInCategory ? stepShort : this->stepName(stepShort);
    const bool stepExists(this->checkExistence(step));
    if(!stepInCategory && jetCategories_){
        // Here check the individual jet categories
        const int category = jetCategories_->categoryId(recoObjectIndices.jetIndices_.size(), recoObjectIndices.bjetIndices_.size());
        const TString fullStepName = this->stepName(stepShort, category);
        this->fill(recoObjects, commonGenObjects, topGenObjects, higgsGenObjects, kinRecoObjects,
                   genObjectIndices, recoObjectIndices, genLevelWeights, recoLevelWeights, weight, fullStepName);
    }
    if(!stepExists) return;
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    
    
    // Now do calculations and filling of histograms
    m_histogram["blah1"]->Fill(1., weight);
    m_histogram["blah2_blubb"]->Fill(31., weight);
}





