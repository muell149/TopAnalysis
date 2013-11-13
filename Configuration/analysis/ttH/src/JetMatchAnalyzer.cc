#include <map>
#include <vector>
#include <iostream>

#include <TH1.h>
#include <TH1D.h>
#include <TString.h>
#include <Math/VectorUtil.h>

#include "JetMatchAnalyzer.h"
#include "analysisStructs.h"
#include "JetCategories.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/classes.h"








JetMatchAnalyzer::JetMatchAnalyzer(const std::vector<TString>& selectionStepsNoCategories,
                                   const std::vector<TString>& stepsForCategories,
                                   const JetCategories* jetCategories):
AnalysisHistogramsBase("jetMatch_", selectionStepsNoCategories, stepsForCategories, jetCategories)
{
    std::cout<<"--- Beginning setting up jet match analyzer\n";
    std::cout<<"=== Finishing setting up jet match analyzer\n\n";
}



void JetMatchAnalyzer::bookHistos(const TString& step, std::map<TString, TH1*>& m_histogram)
{
    TString name;
    
    name = "matchedBjetFromTop";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "matchedBjetFromTop;;# events",3,0,3));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "bQuark-genJet fail");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "genJet-recoJet fail");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "Matched");

    name = "unmatchedGenBjetFromTop";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "unmatchedGenBjetFromTop;;# events",4,0,4));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "Top jets overlap");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "2 jets not matched");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "1 jet not matched");
    m_histogram[name]->GetXaxis()->SetBinLabel(4, "Several hadrons");

    name = "unmatchedRecoBjetFromTop";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "unmatchedRecoBjetFromTop;;# events",3,0,3));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "Top jets overlap");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "2 jets not matched");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "1 jet not matched");

    name = "matchedBjetFromHiggs";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "matchedBjetFromHiggs;;# events",3,0,3));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "bQuark-genJet fail");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "genJet-recoJet fail");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "Matched");

    name = "unmatchedGenBjetFromHiggs";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "unmatchedGenBjetFromHiggs;;# events",4,0,4));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "Higgs jets overlap");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "2 jets not matched");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "1 jet not matched");
    m_histogram[name]->GetXaxis()->SetBinLabel(4, "Several hadrons");

    name = "unmatchedRecoBjetFromHiggs";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "unmatchedRecoBjetFromHiggs;;# events",3,0,3));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "Higgs jets overlap");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "2 jets not matched");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "1 jet not matched");

    name = "matchedBjet";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "matchedBjet;;# events",4,0,4));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "Top-Higgs gen overlap");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "Unique gen jets");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "Top-Higgs reco overlap");
    m_histogram[name]->GetXaxis()->SetBinLabel(4, "Unique reco jets");
}



void JetMatchAnalyzer::fillHistos(const RecoObjects&, const CommonGenObjects&,
                                  const TopGenObjects&, const HiggsGenObjects&,
                                  const KinRecoObjects&,
                                  const tth::RecoObjectIndices&, const tth::GenObjectIndices& genObjectIndices,
                                  const tth::GenLevelWeights&, const tth::RecoLevelWeights&,
                                  const double& weight, const TString&,
                                  std::map<TString, TH1*>& m_histogram)
{
    TString name;
    
    name = "matchedBjetFromTop";
    if(!genObjectIndices.uniqueGenTopMatching()) m_histogram[name]->Fill(0., weight);
    else if(!genObjectIndices.uniqueRecoTopMatching()) m_histogram[name]->Fill(1., weight);
    else m_histogram[name]->Fill(2., weight);

    name = "unmatchedGenBjetFromTop";
    if(genObjectIndices.genBjetFromTopIndex_==-2 || genObjectIndices.genAntiBjetFromTopIndex_==-2) m_histogram[name]->Fill(3., weight);
    else if(genObjectIndices.genBjetFromTopIndex_==-1 && genObjectIndices.genAntiBjetFromTopIndex_==-1) m_histogram[name]->Fill(1., weight);
    else if(genObjectIndices.genBjetFromTopIndex_==-1 || genObjectIndices.genAntiBjetFromTopIndex_==-1) m_histogram[name]->Fill(2., weight);
    else if(genObjectIndices.genBjetFromTopIndex_==genObjectIndices.genAntiBjetFromTopIndex_) m_histogram[name]->Fill(0., weight);

    name = "unmatchedRecoBjetFromTop";
    if(genObjectIndices.uniqueGenTopMatching()){
        if(genObjectIndices.recoBjetFromTopIndex_==-1 && genObjectIndices.recoAntiBjetFromTopIndex_==-1) m_histogram[name]->Fill(1., weight);
        else if(genObjectIndices.recoBjetFromTopIndex_==-1 || genObjectIndices.recoAntiBjetFromTopIndex_==-1) m_histogram[name]->Fill(2., weight);
        else if(genObjectIndices.recoBjetFromTopIndex_==genObjectIndices.recoAntiBjetFromTopIndex_) m_histogram[name]->Fill(0., weight);
    }

    name = "matchedBjetFromHiggs";
    if(!genObjectIndices.uniqueGenHiggsMatching()) m_histogram[name]->Fill(0., weight);
    else if(!genObjectIndices.uniqueRecoHiggsMatching()) m_histogram[name]->Fill(1., weight);
    else m_histogram[name]->Fill(2., weight);

    name = "unmatchedGenBjetFromHiggs";
    if(genObjectIndices.genBjetFromHiggsIndex_==-2 || genObjectIndices.genAntiBjetFromHiggsIndex_==-2) m_histogram[name]->Fill(3., weight);
    else if(genObjectIndices.genBjetFromHiggsIndex_==-1 && genObjectIndices.genAntiBjetFromHiggsIndex_==-1) m_histogram[name]->Fill(1., weight);
    else if(genObjectIndices.genBjetFromHiggsIndex_==-1 || genObjectIndices.genAntiBjetFromHiggsIndex_==-1) m_histogram[name]->Fill(2., weight);
    else if(genObjectIndices.genBjetFromHiggsIndex_==genObjectIndices.genAntiBjetFromHiggsIndex_) m_histogram[name]->Fill(0., weight);

    name = "unmatchedRecoBjetFromHiggs";
    if(genObjectIndices.uniqueGenHiggsMatching()){
        if(genObjectIndices.recoBjetFromHiggsIndex_==-1 && genObjectIndices.recoAntiBjetFromHiggsIndex_==-1) m_histogram[name]->Fill(1., weight);
        else if(genObjectIndices.recoBjetFromHiggsIndex_==-1 || genObjectIndices.recoAntiBjetFromHiggsIndex_==-1) m_histogram[name]->Fill(2., weight);
        else if(genObjectIndices.recoBjetFromHiggsIndex_==genObjectIndices.recoAntiBjetFromHiggsIndex_) m_histogram[name]->Fill(0., weight);
    }

    name = "matchedBjet";
    if(genObjectIndices.uniqueGenMatching()){
        m_histogram[name]->Fill(1., weight);
        if(genObjectIndices.uniqueRecoMatching()) m_histogram[name]->Fill(3., weight);
        else if(genObjectIndices.uniqueRecoTopMatching() && genObjectIndices.uniqueRecoHiggsMatching()) m_histogram[name]->Fill(2., weight);
    }
    else if(genObjectIndices.uniqueGenTopMatching() && genObjectIndices.uniqueGenHiggsMatching()) m_histogram[name]->Fill(0., weight);
}








