#include <map>
#include <vector>
#include <iostream>

#include <TH1.h>
#include <TH1D.h>
#include <TString.h>
#include <Math/VectorUtil.h>

#include "JetChargeAnalyzer.h"
#include "analysisStructs.h"
#include "JetCategories.h"
#include "../../common/include/analysisObjectStructs.h"
#include "../../common/include/analysisUtils.h"
#include "../../common/include/classes.h"








JetChargeAnalyzer::JetChargeAnalyzer(const std::vector<TString>& selectionStepsNoCategories,
                                     const std::vector<TString>& stepsForCategories,
                                     const JetCategories* jetCategories):
AnalysisHistogramsBase("jetCharge_", selectionStepsNoCategories, stepsForCategories, jetCategories)
{
    std::cout<<"--- Beginning setting up jet charge analyzer\n";
    std::cout<<"=== Finishing setting up jet charge analyzer\n\n";
}



void JetChargeAnalyzer::bookHistos(const TString& step, std::map<TString, TH1*>& m_histogram)
{
    TString name;
    
    
}



void JetChargeAnalyzer::fillHistos(const RecoObjects& recoObjects, const CommonGenObjects&,
                                   const TopGenObjects&, const HiggsGenObjects&,
                                   const KinRecoObjects&,
                                   const tth::RecoObjectIndices& recoObjectIndices, const tth::GenObjectIndices&,
                                   const tth::GenLevelWeights&, const tth::RecoLevelWeights&,
                                   const double& weight, const TString&,
                                   std::map<TString, TH1*>& m_histogram)
{
    TString name;
    
    
}








