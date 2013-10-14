#include <iostream>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <algorithm>

#include <TString.h>
#include <TH1.h>
#include <TH1D.h>
#include <Math/VectorUtil.h>
#include <TProfile.h>

#include "Playground.h"
#include "analysisStructs.h"
#include "JetCategories.h"
#include "higgsUtils.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"
#include "../../diLeptonic/src/classes.h"





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



void Playground::fillHistos(const RecoObjects& recoObjects, const CommonGenObjects& commonGenObjects,
                            const TopGenObjects& topGenObjects, const HiggsGenObjects& higgsGenObjects,
                            const KinRecoObjects& kinRecoObjects,
                            const tth::RecoObjectIndices& recoObjectIndices, const tth::GenObjectIndices& genObjectIndices,
                            const tth::GenLevelWeights& genLevelWeights, const tth::RecoLevelWeights& recoLevelWeights,
                            const double& weight, const TString& step, std::map<TString, TH1*>& m_histogram)
{
    // Do calculations and filling of histograms
    m_histogram["blah1"]->Fill(1., weight);
    m_histogram["blah2_blubb"]->Fill(31., weight);
}






