#include <iostream>
#include <algorithm>

#include <TH1.h>
#include <TH1D.h>
#include <TProfile.h>
#include <TString.h>
#include <Math/VectorUtil.h>

#include "MvaValidation.h"
#include "MvaInputVariables.h"
#include "mvaStructs.h"
#include "analysisStructs.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/classes.h"










MvaValidation::MvaValidation(MvaInputTopJetsVariables* weightsCorrect, MvaInputTopJetsVariables* weightsSwapped,
                             const std::vector<TString>& selectionStepsNoCategories,
                             const std::vector<TString>& stepsForCategories,
                             const JetCategories* jetCategories):
AnalysisHistogramsBase(selectionStepsNoCategories, stepsForCategories, jetCategories),
weightsCorrect_(weightsCorrect),
weightsSwapped_(weightsSwapped)
{
    std::cout<<"--- Beginning setting up MVA validation\n";
    std::cout<<"=== Finishing setting up MVA validation\n\n";
}



void MvaValidation::bookHistos(const TString& step)
{
    tth::MvaInputVariables mvaInputVariables;
    tth::MvaInputVariablesPerEvent mvaInputVariablesPerEvent;
    
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    TString name;

    name = "mva_matchedBjetFromTop";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "matchedBjetsFromTop;;# events",3,0,3));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "bQuark-genJet fail");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "genJet-recoJet fail");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "Matched");
    
    name = "mva_matchedBjetFromHiggs";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "matchedBjetsFromHiggs;;# events",3,0,3));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "bQuark-genJet fail");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "genJet-recoJet fail");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "Matched");
    
    
    name = "mva_dijet_mass";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "dijetMass;m_{jj} [GeV];# jet pairs", 100, 0, 500));
    
    
    name = "mvaBest_dijet_mass";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "bestDijetMass;m_{jj} [GeV];# events", 100, 0, 500));
    
    
    name = "mvaBest_jetsFromTop";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "bestJetsFromTop;;# events",4,0,4));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "matched Top jets");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "pair from Top");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "correct pair");
    m_histogram[name]->GetXaxis()->SetBinLabel(4, "swapped pair");
    
    name = "mvaBest_jetsFromHiggs";
    m_histogram[name] = this->store(new TH1D(name+"_step"+step, "bestJetsFromHiggs;;# events",4,0,4));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "matched Higgs jets");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "pair from Higgs");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "overlap with Top");
    m_histogram[name]->GetXaxis()->SetBinLabel(4, "Fully solved");
    
    name = "mva_dijet_massVsMvaWeightHigh";
    m_histogram[name] = this->store(new TProfile(name+"_step"+step, "dijetMassVsMvaWeightHigh;w_{MVA,1};m_{jj} [GeV]",20, -1.2, 0.2, "s"));
    name = "mva_dijet_massVsMvaWeightDiff";
    m_histogram[name] = this->store(new TProfile(name+"_step"+step, "dijetMassVsMvaWeightDiff;w_{MVA,1} - w_{MVA,2};m_{jj} [GeV]",20, 0, 3, "s"));
    
    name = "mvaBest_dijet_massVsMvaWeightHigh";
    m_histogram[name] = this->store(new TProfile(name+"_step"+step, "bestDijetMassVsMvaWeightHigh;w_{MVA,1};m_{jj} [GeV]",20, -1.2, 0.2, "s"));
    name = "mvaBest_dijet_massVsMvaWeightDiff";
    m_histogram[name] = this->store(new TProfile(name+"_step"+step, "bestDijetMassVsMvaWeightDiff;w_{MVA,1} - w_{MVA,2};m_{jj} [GeV]",20, 0, 3, "s"));
}



void MvaValidation::fill(const RecoObjects& recoObjects,
                         const tth::GenObjectIndices& genObjectIndices, const tth::RecoObjectIndices& recoObjectIndices,
                         const double& weight, const TString& step)
{
    // Check if step exists
    const bool stepExists(this->checkExistence(step));
    if(!stepExists) return;
    
    // FIXME: which events exactly to fill? For now all with at least 4 jets
    const int numberOfJets = recoObjectIndices.jetIndices_.size();
    if(numberOfJets<4) return;
    
    // Loop over all jet combinations and get MVA input variables
    const std::vector<MvaInputTopJetsVariables::Input>& v_mvaInput =
            MvaInputTopJetsVariables::fillInputStructs(recoObjectIndices, genObjectIndices, recoObjects, weight);
    
    // Get the MVA weights from weights file as vector, one entry per jet pair
    const std::vector<float>& mvaWeightsCorrect = weightsCorrect_->mvaWeights(v_mvaInput);
    const std::vector<float>& mvaWeightsSwapped = weightsSwapped_->mvaWeights(v_mvaInput);
    
    // Get the indices of the jet pairs and order them by MVA weights, biggest value first
    const tth::IndexPairs& jetIndexPairs = recoObjectIndices.jetIndexPairs_;
    std::vector<int> jetIndexPairsIndices = ttbar::initialiseIndices(jetIndexPairs);
    ttbar::orderIndices(jetIndexPairsIndices, mvaWeightsCorrect);
    
    // Get jet pair leading in MVA weight, and extract bIndex and antiBIndex
    const std::pair<int, int>& leadingJetIndexPair = jetIndexPairs.at(jetIndexPairsIndices.at(0));
    const int antiBFromTopIndex = leadingJetIndexPair.first;
    const int bFromTopIndex = leadingJetIndexPair.second;
    
    // Check whether the two jets correspond to the b's from tops, and if the two are correct or swapped
    const bool isSwappedPairFromTop(genObjectIndices.isSwappedPairFromTop(bFromTopIndex, antiBFromTopIndex));
    const bool isCorrectPairFromTop(genObjectIndices.isCorrectPairFromTop(bFromTopIndex, antiBFromTopIndex));
    const bool isPairFromTop(genObjectIndices.isPairFromTop(bFromTopIndex, antiBFromTopIndex));
    
    // Get all jets except the ones assigned to ttbar system, and order them by b-tag discriminator value
    std::vector<int> remainingJetIndices;
    for(const int index : recoObjectIndices.jetIndices_){
        if(index==antiBFromTopIndex || index==bFromTopIndex) continue;
        remainingJetIndices.push_back(index);
    }
    ttbar::orderIndices(remainingJetIndices, *recoObjects.jetBTagCSV_);
    
    // Get the two jets assigned to Higgs
    const int jet1FromHiggsIndex = remainingJetIndices.at(0);
    const int jet2FromHiggsIndex = remainingJetIndices.at(1);
    
    // Check whether the two jets correspond to the b's from Higgs
    const bool isPairFromHiggs(genObjectIndices.isPairFromHiggs(jet1FromHiggsIndex, jet2FromHiggsIndex));
    
    
    
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    
    if(!genObjectIndices.uniqueGenTopMatching()) m_histogram["mva_matchedBjetFromTop"]->Fill(0., weight);
    else if(!genObjectIndices.uniqueRecoTopMatching()) m_histogram["mva_matchedBjetFromTop"]->Fill(1., weight);
    else m_histogram["mva_matchedBjetFromTop"]->Fill(2., weight);
    
    if(!genObjectIndices.uniqueGenHiggsMatching()) m_histogram["mva_matchedBjetFromHiggs"]->Fill(0., weight);
    else if(!genObjectIndices.uniqueRecoHiggsMatching()) m_histogram["mva_matchedBjetFromHiggs"]->Fill(1., weight);
    else m_histogram["mva_matchedBjetFromHiggs"]->Fill(2., weight);
    
    
    
    for(const auto& jetIndexPair : jetIndexPairs){
        const LV dijet = recoObjects.jets_->at(jetIndexPair.first) + recoObjects.jets_->at(jetIndexPair.second);
        m_histogram["mva_dijet_mass"]->Fill(dijet.M(), weight);
        ((TProfile*)m_histogram["mva_dijet_massVsMvaWeightHigh"])->Fill(mvaWeightsCorrect.at(0), dijet.M(), weight);
        ((TProfile*)m_histogram["mva_dijet_massVsMvaWeightDiff"])->Fill(mvaWeightsCorrect.at(0)-mvaWeightsCorrect.at(1), dijet.M(), weight);
    }
    
    
    const LV dijet = recoObjects.jets_->at(jet1FromHiggsIndex) + recoObjects.jets_->at(jet2FromHiggsIndex);
    m_histogram["mvaBest_dijet_mass"]->Fill(dijet.M(), weight);
    ((TProfile*)m_histogram["mvaBest_dijet_massVsMvaWeightHigh"])->Fill(mvaWeightsCorrect.at(0), dijet.M(), weight);
    ((TProfile*)m_histogram["mvaBest_dijet_massVsMvaWeightDiff"])->Fill(mvaWeightsCorrect.at(0)-mvaWeightsCorrect.at(1), dijet.M(), weight);
    
    
    
    if(genObjectIndices.uniqueRecoTopMatching()){
        m_histogram["mvaBest_jetsFromTop"]->Fill(0., weight);
        if(isCorrectPairFromTop){
            m_histogram["mvaBest_jetsFromTop"]->Fill(1., weight);
            m_histogram["mvaBest_jetsFromTop"]->Fill(2., weight);
        }
        else if(isSwappedPairFromTop){
            m_histogram["mvaBest_jetsFromTop"]->Fill(1., weight);
            m_histogram["mvaBest_jetsFromTop"]->Fill(3., weight);
        }
    }
    else{
        m_histogram["mvaBest_jetsFromTop"]->Fill(-999., weight);
    }
    
    
    if(genObjectIndices.uniqueRecoHiggsMatching()){
        m_histogram["mvaBest_jetsFromHiggs"]->Fill(0., weight);
        if(isPairFromHiggs){
            m_histogram["mvaBest_jetsFromHiggs"]->Fill(1., weight);
            if(!genObjectIndices.uniqueRecoMatching()) m_histogram["mvaBest_jetsFromHiggs"]->Fill(2., weight);
            else if(isPairFromTop) m_histogram["mvaBest_jetsFromHiggs"]->Fill(3., weight);
        }
    }
    else{
        m_histogram["mvaBest_jetsFromHiggs"]->Fill(-999., weight);
    }
    
    
}








