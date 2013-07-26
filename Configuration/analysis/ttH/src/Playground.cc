#include <iostream>

#include "TString.h"
#include "TH1.h"
#include "TH1D.h"

#include "Playground.h"
#include "analysisStructs.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"



Playground::Playground(const std::vector<TString>& selectionSteps):
AnalysisHistogramsBase(selectionSteps)
{
    std::cout<<"--- Beginning setting up playground\n";
    std::cout<<"=== Finishing setting up playground\n\n";
}



void Playground::bookHistos(const TString& step)
{
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    
    // Book histograms here
    m_histogram["test"] = this->store(new TH1D("test_step"+step,"histo title;x axis;y axis",10,0,100));
}



void Playground::fill(const RecoObjects& recoObjects, const CommonGenObjects& commonGenObjects,
                      const TopGenObjects& topGenObjects, const HiggsGenObjects& higgsGenObjects,
                      const KinRecoObjects& kinRecoObjects,
                      const tth::GenObjectIndices& genObjectIndices, const tth::RecoObjectIndices& recoObjectIndices,
                      const tth::GenLevelWeights& genLevelWeights, const tth::RecoLevelWeights& recoLevelWeights,
                      const double& weight, const TString& step)
{
    // Check if step exists
    const bool stepExists(this->checkExistence(step));
    if(!stepExists) return;
    
    // Now do calculations and filling of histograms
    m_stepHistograms_[step].m_histogram_["test"]->Fill(1., weight);
}





