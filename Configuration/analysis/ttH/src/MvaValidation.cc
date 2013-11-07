#include <iostream>

#include <TH1.h>
#include <TH1D.h>
#include <TH2.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TString.h>

#include "MvaValidation.h"
#include "MvaReader.h"
#include "mvaStructs.h"
#include "analysisStructs.h"
#include "JetCategories.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/classes.h"
#include "../../diLeptonic/src/RootFileReader.h"









MvaValidation::MvaValidation(const char* weightsCorrectFile, const char* weightsSwappedFile,
                             const char* mva2dWeightsDir, const char* mva2dWeightsHisto,
                             const std::vector<TString>& selectionStepsNoCategories,
                             const std::vector<TString>& stepsForCategories,
                             const JetCategories* jetCategories):
AnalysisHistogramsBase("mvaA_", selectionStepsNoCategories, stepsForCategories, jetCategories),
weightsCorrect_(0),
weightsSwapped_(0),
weights2d_(0)
{
    std::cout<<"--- Beginning setting up MVA validation\n";

    weightsCorrect_ = new MvaReader(weightsCorrectFile, selectionStepsNoCategories);
    weightsSwapped_ = new MvaReader(weightsSwappedFile, selectionStepsNoCategories);

    TString weights2dFilename(mva2dWeightsDir);
    weights2dFilename.Append("/weights2d.root");
    TString weights2dHistoname("correctAndSwapped_");
    weights2dHistoname.Append(mva2dWeightsHisto);
    //std::cout<<"Names: "<<weights2dFilename<<" , "<<weights2dHistoname<<"\n\n\n";
    RootFileReader* fileReader(RootFileReader::getInstance());
    weights2d_ = fileReader->GetClone<TH2D>(weights2dFilename, weights2dHistoname);
    const double integral = weights2d_->Integral(0, weights2d_->GetNbinsX()+1, 0, weights2d_->GetNbinsY()+1);
    weights2d_->Scale(1./integral);

    std::cout<<"=== Finishing setting up MVA validation\n\n";
}



void MvaValidation::bookHistos(const TString& step, std::map<TString, TH1*>& m_histogram)
{
    TString name;

    name = "dijet_mass";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "dijetMass;m_{jj} [GeV];# jet pairs", 100, 0, 500));

    name = "dijet_mass_bestCorrect";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "dijetMass_{correct}^{best};m_{jj (best)}^{correct} [GeV];# events", 100, 0, 500));
    name = "dijet_mass_bestSwapped";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "dijetMass_{swapped}^{best};m_{jj (best)}^{swapped} [GeV];# events", 100, 0, 500));
    name = "dijet_mass_bestCombined";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "dijetMass_{combined}^{best};m_{jj (best)}^{combined} [GeV];# events", 100, 0, 500));


    name = "jetsFromTop_bestCorrect";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "jetsFromTop_{correct}^{best};;# events",4,0,4));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "matched Top jets");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "pair from Top");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "correct pair");
    m_histogram[name]->GetXaxis()->SetBinLabel(4, "swapped pair");

    name = "jetsFromTop_bestSwapped";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "jetsFromTop_{swapped}^{best};;# events",4,0,4));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "matched Top jets");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "pair from Top");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "correct pair");
    m_histogram[name]->GetXaxis()->SetBinLabel(4, "swapped pair");


    name = "jetsFromTop_bestCombined";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "jetsFromTop_{combined}^{best};;# events",4,0,4));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "matched Top jets");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "pair from Top");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "correct pair");
    m_histogram[name]->GetXaxis()->SetBinLabel(4, "swapped pair");

    name = "jetsFromHiggs_bestCorrect";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "jetsFromHiggs_{correct}^{best};;# events",4,0,4));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "matched Higgs jets");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "pair from Higgs");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "overlap with Top");
    m_histogram[name]->GetXaxis()->SetBinLabel(4, "Fully solved");


    name = "jetsFromHiggs_bestSwapped";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "jetsFromHiggs_{swapped}^{best};;# events",4,0,4));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "matched Higgs jets");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "pair from Higgs");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "overlap with Top");
    m_histogram[name]->GetXaxis()->SetBinLabel(4, "Fully solved");

    name = "jetsFromHiggs_bestCombined";
    m_histogram[name] = this->store(new TH1D(prefix_+name+step, "jetsFromHiggs_{combined}^{best};;# events",4,0,4));
    m_histogram[name]->GetXaxis()->SetBinLabel(1, "matched Higgs jets");
    m_histogram[name]->GetXaxis()->SetBinLabel(2, "pair from Higgs");
    m_histogram[name]->GetXaxis()->SetBinLabel(3, "overlap with Top");
    m_histogram[name]->GetXaxis()->SetBinLabel(4, "Fully solved");


    name = "dijet_massVsMvaWeightHigh";
    m_histogram[name] = this->store(new TProfile(prefix_+name+step, "dijetMassVsMvaWeightHigh;w_{MVA,1};m_{jj} [GeV]",20, -1.2, 0.2, "s"));
    name = "dijet_massVsMvaWeightDiff";
    m_histogram[name] = this->store(new TProfile(prefix_+name+step, "dijetMassVsMvaWeightDiff;w_{MVA,1} - w_{MVA,2};m_{jj} [GeV]",20, 0, 3, "s"));

    name = "dijet_massVsMvaWeightHigh_bestCorrect";
    m_histogram[name] = this->store(new TProfile(prefix_+name+step, "dijetMassVsMvaWeightHigh_{correct}^{best};w_{MVA,1};m_{jj (best)}^{correct} [GeV]",20, -1.2, 0.2, "s"));
    name = "dijet_massVsMvaWeightHigh_bestSwapped";
    m_histogram[name] = this->store(new TProfile(prefix_+name+step, "dijetMassVsMvaWeightHigh_{swapped}^{best};w_{MVA,1};m_{jj (best)}^{swapped} [GeV]",20, -1.2, 0.2, "s"));
    name = "dijet_massVsMvaWeightHigh_bestCombined";
    m_histogram[name] = this->store(new TProfile(prefix_+name+step, "dijetMassVsMvaWeightHigh_{combined}^{best};w_{MVA,1};m_{jj (best)}^{combined} [GeV]",20, -1.2, 0.2, "s"));

    name = "dijet_massVsMvaWeightDiff_bestCorrect";
    m_histogram[name] = this->store(new TProfile(prefix_+name+step, "dijetMassVsMvaWeightDiff_{correct}^{best};w_{MVA,1} - w_{MVA,2};m_{jj (best)}^{correct} [GeV]",20, 0, 3, "s"));
    name = "dijet_massVsMvaWeightDiff_bestSwapped";
    m_histogram[name] = this->store(new TProfile(prefix_+name+step, "dijetMassVsMvaWeightDiff_{swapped}^{best};w_{MVA,1} - w_{MVA,2};m_{jj (best)}^{swapped} [GeV]",20, 0, 3, "s"));
    name = "dijet_massVsMvaWeightDiff_bestCombined";
    m_histogram[name] = this->store(new TProfile(prefix_+name+step, "dijetMassVsMvaWeightDiff_{combined}^{best};w_{MVA,1} - w_{MVA,2};m_{jj (best)}^{combined} [GeV]",20, 0, 3, "s"));


    name = "mvaWeightCorrect";
    this->bookHistosInclExcl(m_histogram, prefix_, step, name, name+"mvaWeight_{correct};w_{MVA}^{correct};# jet pairs", 80, -1.2, 0.2);

    name = "mvaWeightCorrect_best";
    this->bookHistosInclExcl(m_histogram, prefix_, step, name, name+"best mvaWeight_{correct};w_{MVA,1}^{correct};# events", 80, -1.2, 0.2);


    name = "mvaWeightSwapped";
    this->bookHistosInclExcl(m_histogram, prefix_, step, name, name+"mvaWeight_{swapped};w_{MVA}^{swapped};# jet pairs", 80, -1.2, 0.2);

    name = "mvaWeightSwapped_best";
    this->bookHistosInclExcl(m_histogram, prefix_, step, name, name+"best mvaWeight_{swapped};w_{MVA,1}^{swapped};# events", 80, -1.2, 0.2);


    name = "mvaWeightCombined";
    this->bookHistosInclExcl(m_histogram, prefix_, step, name, name+"mvaWeight_{combined};w_{MVA}^{combined};# jet pairs", 80, 0., 1.);

    name = "mvaWeightCombined_best";
    this->bookHistosInclExcl(m_histogram, prefix_, step, name, name+"best mvaWeight_{combined};w_{MVA,1}^{combined};# events", 80, 0., 1.);


    name = "mvaWeightCorrectVsSwapped";
    this->bookHistosInclExcl2D(m_histogram, prefix_, step, name, name+"mvaWeightCorrectVsSwapped;w_{MVA}^{correct};w_{MVA}^{swapped}", 40, -1.2, 0.2, 40, -1.2, 0.2);

    name = "mvaWeightCorrectVsSwapped_bestCorrectBestSwapped";
    this->bookHistosInclExcl2D(m_histogram, prefix_, step, name, name+"mvaWeightCorrectVsSwapped for best Correct pair;w_{MVA,1}^{correct};w_{MVA,1}^{swapped}", 40, -1.2, 0.2, 40, -1.2, 0.2);
}



void MvaValidation::fillHistos(const RecoObjects& recoObjects, const CommonGenObjects&,
                               const TopGenObjects&, const HiggsGenObjects&,
                               const KinRecoObjects&,
                               const tth::RecoObjectIndices& recoObjectIndices, const tth::GenObjectIndices& genObjectIndices,
                               const tth::GenLevelWeights&, const tth::RecoLevelWeights&,
                               const double& weight, const TString&,
                               std::map<TString, TH1*>& m_histogram)
{
    // Loop over all jet combinations and get MVA input variables
    const std::vector<MvaTopJetsVariables> v_mvaTopJetsVariables =
            MvaTopJetsVariables::fillVariables(recoObjectIndices, genObjectIndices, recoObjects, weight);

    // Get the MVA weights from weights file as vector, one entry per jet pair
    const std::vector<float> v_mvaWeightsCorrect = weightsCorrect_->mvaWeights(v_mvaTopJetsVariables);
    const std::vector<float> v_mvaWeightsSwapped = weightsSwapped_->mvaWeights(v_mvaTopJetsVariables);

    // Get the combined weight from 2D histogram
    const std::vector<float> v_mvaWeightsCombined = MvaReader::combinedWeight(weights2d_,
                                                                              v_mvaWeightsCorrect,
                                                                              v_mvaWeightsSwapped);

    // Fill all variables and associated MVA weights per event
    const MvaTopJetsVariablesPerEvent mvaTopJetsVariablesPerEvent(v_mvaTopJetsVariables,
                                                                  v_mvaWeightsCorrect,
                                                                  v_mvaWeightsSwapped,
                                                                  v_mvaWeightsCombined);

    // Fill histograms specific for the correct MVA weights
    fillMVASpecificHistograms(v_mvaWeightsCorrect, mvaTopJetsVariablesPerEvent, m_histogram, recoObjects, recoObjectIndices, genObjectIndices,
                              "Correct", weight, true);
    // Fill histograms specific for the swapped MVA weights
    fillMVASpecificHistograms(v_mvaWeightsSwapped, mvaTopJetsVariablesPerEvent, m_histogram, recoObjects, recoObjectIndices, genObjectIndices,
                              "Swapped", weight, false);
    // Fill histograms specific for the combined MVA weights
    fillMVASpecificHistograms(v_mvaWeightsCombined, mvaTopJetsVariablesPerEvent, m_histogram, recoObjects, recoObjectIndices, genObjectIndices,
                              "Combined", weight, false);


    // Fill the generator level histograms
    TString name;

    for(size_t index = 0; index<mvaTopJetsVariablesPerEvent.variables().size(); ++index){
        const MvaTopJetsVariables& mvaTopJetsVariables = mvaTopJetsVariablesPerEvent.variables().at(index);

        const float mvaWeightCorrect = mvaTopJetsVariablesPerEvent.mvaWeightsCorrect().at(index);
        const float mvaWeightSwapped = mvaTopJetsVariablesPerEvent.mvaWeightsSwapped().at(index);

        name = "mvaWeightCorrectVsSwapped";
        this->fillHistosInclExcl2D(m_histogram, name, mvaWeightCorrect, mvaWeightSwapped, mvaTopJetsVariables, weight);

        name = "mvaWeightCorrectVsSwapped_bestCorrectBestSwapped";
        if(index==0){
            const float maxWeightCorrect = mvaTopJetsVariablesPerEvent.maxWeightCorrect();
            const float maxWeightSwapped = mvaTopJetsVariablesPerEvent.maxWeightSwapped();
            this->fillHistosInclExcl2D(m_histogram, name, maxWeightCorrect, maxWeightSwapped, mvaTopJetsVariables, weight);
        }
    }
}


void MvaValidation::fillMVASpecificHistograms(const std::vector<float>& v_mvaWeights, const MvaTopJetsVariablesPerEvent& mvaTopJetsVariablesPerEvent,
                                              std::map< TString, TH1* >& m_histogram, const RecoObjects& recoObjects,
                                              const tth::RecoObjectIndices& recoObjectIndices, const tth::GenObjectIndices& genObjectIndices,
                                              std::string mvaName, const double& weight, bool fillGenericHistograms)
{
    TString name;
    // Get the indices of the jet pairs and order them by MVA weights, biggest value first
    const tth::IndexPairs& jetIndexPairs = recoObjectIndices.jetIndexPairs_;
    std::vector<int> jetIndexPairsIndices = ttbar::initialiseIndices(jetIndexPairs);
    ttbar::orderIndices(jetIndexPairsIndices, v_mvaWeights);

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
    
    // FIXME: needs to check whether 4 jets are present
    if(recoObjectIndices.jetIndices_.size()<4) return;
    
    // Get the two jets assigned to Higgs
    const int jet1FromHiggsIndex = remainingJetIndices.at(0);
    const int jet2FromHiggsIndex = remainingJetIndices.at(1);

    // Check whether the two jets correspond to the b's from Higgs
    const bool isPairFromHiggs(genObjectIndices.isPairFromHiggs(jet1FromHiggsIndex, jet2FromHiggsIndex));

    if(fillGenericHistograms) {
        for(const auto& jetIndexPair : jetIndexPairs){
            const LV dijet = recoObjects.jets_->at(jetIndexPair.first) + recoObjects.jets_->at(jetIndexPair.second);
            name = "dijet_mass";
            m_histogram[name]->Fill(dijet.M(), weight);
            name = "dijet_massVsMvaWeightHigh";
            ((TProfile*)m_histogram[name])->Fill(v_mvaWeights.at(0), dijet.M(), weight);
            name = "dijet_massVsMvaWeightDiff";
            ((TProfile*)m_histogram[name])->Fill(v_mvaWeights.at(0)-v_mvaWeights.at(1), dijet.M(), weight);
        }
    }


    const LV dijet = recoObjects.jets_->at(jet1FromHiggsIndex) + recoObjects.jets_->at(jet2FromHiggsIndex);
    name = "dijet_mass_best"+mvaName;
    m_histogram[name]->Fill(dijet.M(), weight);
    name = "dijet_massVsMvaWeightHigh_best"+mvaName;
    ((TProfile*)m_histogram[name])->Fill(v_mvaWeights.at(0), dijet.M(), weight);
    name = "dijet_massVsMvaWeightDiff_best"+mvaName;
    ((TProfile*)m_histogram[name])->Fill(v_mvaWeights.at(0)-v_mvaWeights.at(1), dijet.M(), weight);


    name = "jetsFromTop_best"+mvaName;
    if(genObjectIndices.uniqueRecoTopMatching()){
        m_histogram[name]->Fill(0., weight);
        if(isCorrectPairFromTop){
            m_histogram[name]->Fill(1., weight);
            m_histogram[name]->Fill(2., weight);
        }
        else if(isSwappedPairFromTop){
            m_histogram[name]->Fill(1., weight);
            m_histogram[name]->Fill(3., weight);
        }
    }
    else{
        m_histogram[name]->Fill(-999., weight);
    }


    name = "jetsFromHiggs_best"+mvaName;
    if(genObjectIndices.uniqueRecoHiggsMatching()){
        m_histogram[name]->Fill(0., weight);
        if(isPairFromHiggs){
            m_histogram[name]->Fill(1., weight);
            if(!genObjectIndices.uniqueRecoMatching()) m_histogram[name]->Fill(2., weight);
            else if(isPairFromTop) m_histogram[name]->Fill(3., weight);
        }
    }
    else{
        m_histogram[name]->Fill(-999., weight);
    }


    for(size_t index = 0; index<mvaTopJetsVariablesPerEvent.variables().size(); ++index){
        const MvaTopJetsVariables& mvaTopJetsVariables = mvaTopJetsVariablesPerEvent.variables().at(index);

        const float mvaWeight = v_mvaWeights.at(index);
        const bool isMaxWeight = (int)index==ttbar::extremumIndex(v_mvaWeights);

        name = "mvaWeight"+mvaName;
        this->fillHistosInclExcl(m_histogram, name, mvaWeight, mvaTopJetsVariables, weight);

        name = "mvaWeight"+mvaName+"_best";
        if(isMaxWeight) this->fillHistosInclExcl(m_histogram, name, mvaWeight, mvaTopJetsVariables, weight);
    }

}


void MvaValidation::bookHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                                       const TString& name, const TString& title,
                                       const int& nBinX, const double& xMin, const double& xMax)
{
    const TString correct("_correct");
    const TString swapped("_swapped");
    const TString wrong("_wrong");

    m_histogram[name] = this->store(new TH1D(prefix+name+step, title, nBinX, xMin, xMax));

    m_histogram[name+correct] = this->store(new TH1D(prefix+name+correct+step, title, nBinX, xMin, xMax));
    m_histogram[name+swapped] = this->store(new TH1D(prefix+name+swapped+step, title, nBinX, xMin, xMax));
    m_histogram[name+wrong] = this->store(new TH1D(prefix+name+wrong+step, title, nBinX, xMin, xMax));
}



void MvaValidation::bookHistosInclExcl2D(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                                         const TString& name, const TString& title,
                                         const int& nBinX, const double& xMin, const double& xMax,
                                         const int& nBinY, const double& yMin, const double& yMax)
{
    const TString correct("_correct");
    const TString swapped("_swapped");
    const TString wrong("_wrong");

    m_histogram[name] = this->store(new TH2D(prefix+name+step, title, nBinX, xMin, xMax, nBinY, yMin, yMax));

    m_histogram[name+correct] = this->store(new TH2D(prefix+name+correct+step, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    m_histogram[name+swapped] = this->store(new TH2D(prefix+name+swapped+step, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    m_histogram[name+wrong] = this->store(new TH2D(prefix+name+wrong+step, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
}



void MvaValidation::fillHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& name,
                                       const float& variable,
                                       const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight)
{
    const TString correct("_correct");
    const TString swapped("_swapped");
    const TString wrong("_wrong");

    m_histogram[name]->Fill(variable, weight);

    if(mvaTopJetsVariables.correctCombination_.value_) m_histogram[name+correct]->Fill(variable, weight);
    else if(mvaTopJetsVariables.swappedCombination_.value_) m_histogram[name+swapped]->Fill(variable, weight);
    else m_histogram[name+wrong]->Fill(variable, weight);
}



void MvaValidation::fillHistosInclExcl2D(std::map<TString, TH1*>& m_histogram, const TString& name,
                                         const float& variable1, const float& variable2,
                                         const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight)
{
    const TString correct("_correct");
    const TString swapped("_swapped");
    const TString wrong("_wrong");

    ((TH2*)m_histogram[name])->Fill(variable1, variable2, weight);

    if(mvaTopJetsVariables.correctCombination_.value_) ((TH2*)m_histogram[name+correct])->Fill(variable1, variable2, weight);
    else if(mvaTopJetsVariables.swappedCombination_.value_) ((TH2*)m_histogram[name+swapped])->Fill(variable1, variable2, weight);
    else ((TH2*)m_histogram[name+wrong])->Fill(variable1, variable2, weight);
}










