#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#include <TTree.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TString.h>
#include <Math/VectorUtil.h>
#include <TSelectorList.h>
#include <Rtypes.h>

#include "DijetAnalyzer.h"
#include "analysisStructs.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/classes.h"


DijetAnalyzer::DijetAnalyzer(const std::vector<TString>& selectionStepsNoCategories,
                             const std::vector<TString>& stepsForCategories,
                             const JetCategories* jetCategories):
AnalysisHistogramsBase(selectionStepsNoCategories, stepsForCategories, jetCategories)
{
    std::cout<<"--- Beginning setting up dijet analyzer\n";
    std::cout<<"=== Finishing setting up dijet analyzer\n\n";
}



void DijetAnalyzer::fill(const RecoObjects& recoObjects, const CommonGenObjects& commonGenObjects,
                         const TopGenObjects& topGenObjects, const HiggsGenObjects& higgsGenObjects,
                         const KinRecoObjects& kinRecoObjects,
                         const tth::GenObjectIndices& genObjectIndices, const tth::RecoObjectIndices& recoObjectIndices,
                         const double& weight, const TString& stepShort)
{
    // Number of selected jets and bjets
    const int numberOfJets = recoObjectIndices.jetIndices_.size();
    const int numberOfBjets = recoObjectIndices.bjetIndices_.size();
    
    // Set up step name and check if step exists
    const bool stepInCategory = stepShort.Contains("_cate");
    const TString step = stepInCategory ? stepShort : this->stepName(stepShort);
    const bool stepExists(this->checkExistence(step));
    if(!stepInCategory && jetCategories_){
        // Here check the individual jet categories
        const int categoryId = jetCategories_->categoryId(numberOfJets, numberOfBjets);
        const TString fullStepName = this->stepName(stepShort, categoryId);
        this->fill(recoObjects, commonGenObjects, topGenObjects, higgsGenObjects, kinRecoObjects,
                   genObjectIndices, recoObjectIndices, weight, fullStepName);
    }
    if(!stepExists) return;
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    
    
    
    // Extracting input data to more comfortable variables
    const VLV& allJets = *recoObjects.jets_;
    const LV& lepton = recoObjects.allLeptons_->at(recoObjectIndices.leptonIndex_);
    const LV& antilepton = recoObjects.allLeptons_->at(recoObjectIndices.antiLeptonIndex_);
    const LV& met = *recoObjects.met_;
    const std::vector<int>& jetsId = recoObjectIndices.jetIndices_;           // Point to jets from allJets
    const std::vector<int>& bJetsId = recoObjectIndices.bjetIndices_;         // Point to jets from allJets
    std::vector<int> topJetsId;
//    if(kinRecoObjects.HypJet0index_) topJetsId.push_back(kinRecoObjects.HypJet0index_->at(0));
//    if(kinRecoObjects.HypJet1index_) topJetsId.push_back(kinRecoObjects.HypJet1index_->at(0));
    const std::vector<double>& allJetsBtagDiscriminant = *recoObjects.jetBTagCSV_;

    // Setting variables of gen. level if available
    const VLV& genJets = (commonGenObjects.valuesSet_) ? *commonGenObjects.allGenJets_ : VLV(0);
    const std::vector<int>& bHadJetIndex = (topGenObjects.valuesSet_) ? *topGenObjects.genBHadJetIndex_ : std::vector<int>(0);
    const std::vector<int>& bHadFlavour = (topGenObjects.valuesSet_) ? *topGenObjects.genBHadFlavour_ : std::vector<int>(0);
    std::vector<int> trueTopJetsId;             // Point to jets from allJets
    std::vector<int> trueHiggsJetsId;           // Point to jets from allJets
    std::vector<int> trueTopBJetsId;            // Point to b-tagged jets from allJets
    std::vector<int> trueHiggsBJetsId;          // Point to b-tagged jets from allJets
    std::vector<int> topBJetsId;                // Point to b-tagged jets from allJets

    // Selecting b-tagged jets among top jets from KinReco
    for(unsigned int iJet=0, iJetN=topJetsId.size(); iJet<iJetN; iJet++) {
        int iAllJet = topJetsId.at(iJet);
        if(!isInVector(bJetsId,iAllJet)) continue;
        topBJetsId.push_back(iAllJet);
    }



    // Identifying numbers of jets and b-jets
    unsigned int nAllJets = allJets.size();
    unsigned int nGenJets = genJets.size();
    unsigned int nBJets = bJetsId.size();
    unsigned int nJets = jetsId.size();

    // Identifying the category
    int jetCatId = jetCategories_->categoryId(nJets,nBJets);
    if(jetCatId>=jetCategories_->numberOfCategories() || jetCatId<0) return;        // Skipping if category with such Id doesn't exist



    // Analyzing selected jets
    int nJetsPtLt30 = 0;
    int nBJetsPtLt30 = 0;
    for(unsigned int iJet = 0, iJetN=jetsId.size(); iJet<iJetN; iJet++) {
        unsigned int iAllJet = jetsId.at(iJet);
        LV jet = allJets.at(iAllJet);

        // Checking if the jet contains b-hadron from top
        int genJetId = genJetIdOfRecoJet(jet, genJets);
        std::vector<int> hadIds = bHadFlavoursInGenJet(genJetId, bHadJetIndex, bHadFlavour, true);
        if(isInVector(hadIds, 6)) {
            trueTopJetsId.push_back(iAllJet);
            if(isInVector(bJetsId,iAllJet)) trueTopBJetsId.push_back(iAllJet);
        }
        if(isInVector(hadIds, 25)) {
            trueHiggsJetsId.push_back(iAllJet);
            if(isInVector(bJetsId,iAllJet)) trueHiggsBJetsId.push_back(iAllJet);
        }

        // Filling information about the jets
        m_histogram["jet_pt"]->Fill(jet.Pt(), weight);
        m_histogram["jet_eta"]->Fill(jet.Eta(), weight);
        m_histogram["jet_btagDiscriminator"]->Fill(allJetsBtagDiscriminant.at(iAllJet), weight);

        // Filling information about b-tagged jets
        if(isInVector(bJetsId, iAllJet)) {
            m_histogram["bJet_pt"]->Fill(jet.Pt(), weight);
            m_histogram["bJet_eta"]->Fill(jet.Eta(), weight);
            m_histogram["bJet_btagDiscriminator"]->Fill(allJetsBtagDiscriminant.at(iAllJet), weight);
        }


        // Analyzing only jets with Pt<30
        if(jet.Pt()>=30) continue;
        nJetsPtLt30++;
        m_histogram["jet_PtLt30_btagDiscriminator"]->Fill(allJetsBtagDiscriminant.at(iAllJet), weight);
        if(isInVector(bJetsId, iAllJet)) {
            nBJetsPtLt30++;
            m_histogram["bJet_PtLt30_btagDiscriminator"]->Fill(allJetsBtagDiscriminant.at(iAllJet), weight);
        }

        // Finding the corresponding genJetId and its flavours
        int genJetId1 = genJetIdOfRecoJet(jet, genJets);
        std::vector<int> flavJet = bHadFlavoursInGenJet(genJetId1, bHadJetIndex, bHadFlavour, true);
        if(!isInVector(bJetsId,iAllJet)) continue;            // Skip jet if it is not b-tagged
        for(unsigned int iFlav = 0, iFlavN = flavJet.size(); iFlav<iFlavN; iFlav++) {
            m_histogram["jet_PtLt30_flavour"]->Fill(flavJet.at(iFlav), weight);
            m_histogram["bJet_PtLt30_flavour"]->Fill(flavJet.at(iFlav), weight);
            if(isInVector(topJetsId, iAllJet)) continue;          // Skip jet if it was assigned to the Top
        }       // End of loop over flavours of the jet
    }       // End of loop over all reco jets in the event


    m_histogram["allJet_multiplicity"]->Fill(nAllJets, weight);
    m_histogram["jet_multiplicity"]->Fill(nJets, weight);
    m_histogram["bJet_multiplicity"]->Fill(nBJets, weight);
    m_histogram["genJet_multiplicity"]->Fill(nGenJets, weight);
    m_histogram["topJet_multiplicity_true"]->Fill(trueTopJetsId.size(), weight);
    m_histogram["topJet_multiplicity_reco"]->Fill(topJetsId.size(), weight);
    m_histogram["topBJet_multiplicity_true"]->Fill(trueTopBJetsId.size(), weight);
    m_histogram["topBJet_multiplicity_reco"]->Fill(topBJetsId.size(), weight);
    m_histogram["higgsJet_multiplicity_true"]->Fill(trueHiggsJetsId.size(), weight);
    m_histogram["higgsBJet_multiplicity_true"]->Fill(trueHiggsBJetsId.size(), weight);
    m_histogram["jet_PtLt30_multiplicity"]->Fill(nJetsPtLt30, weight);
    m_histogram["bJet_PtLt30_multiplicity"]->Fill(nBJetsPtLt30, weight);
    m_histogram["weight"]->Fill(weight, weight);

    std::vector<int> emptyVector;

    const bool fillAllCombinations = true;
    // Analyzing jet pairs for all jet combinations
    float correctPairFraction_all = correctPairFraction(allJets, jetsId, bJetsId, allJetsBtagDiscriminant, emptyVector, trueHiggsJetsId, weight, m_histogram["dijet_mass_all"], m_histogram["dijet_correctJet_multiplicity_all"], fillAllCombinations);
    m_histogram["dijet_correctPairFraction_all"]->Fill(correctPairFraction_all, weight);
//     if(bJetsId.size()>3) printf("Cat: %d\tFrac: %.2f\n",jetCatId,correctPairFraction_all);

    // Analyzing jet pairs for all jet combinations except true b-jets from top
    float correctPairFraction_trueTopJets = correctPairFraction(allJets, jetsId, bJetsId, allJetsBtagDiscriminant, trueTopJetsId, trueHiggsJetsId, weight, m_histogram["dijet_mass_trueTopJets"], m_histogram["dijet_correctJet_multiplicity_trueTopJets"], fillAllCombinations);
    m_histogram["dijet_correctPairFraction_trueTopJets"]->Fill(correctPairFraction_trueTopJets, weight);

    // Analyzing jet pairs for all jet combinations except reco b-jets from top found by kinematic reconstruction
    float correctPairFraction_recoTopJets = correctPairFraction(allJets, jetsId, bJetsId, allJetsBtagDiscriminant, topJetsId, trueHiggsJetsId, weight, m_histogram["dijet_mass_recoTopJets"], m_histogram["dijet_correctJet_multiplicity_recoTopJets"], fillAllCombinations);
    m_histogram["dijet_correctPairFraction_recoTopJets"]->Fill(correctPairFraction_recoTopJets, weight);


    // Counting number of gen b-jets
    int nGenBjets = 0;
    int nGenBhads = bHadJetIndex.size();
    int nGenBhadsNoG = 0;
    int nGenBhadsNoT = 0;
    // Finding jets that are matched to b-hadrons
    for(unsigned int iJet=0, nJets=genJets.size(); iJet<nJets; iJet++) {
        if(!isInVector(bHadJetIndex, iJet)) continue;
        nGenBjets++;
        m_histogram["genBJet_pt"]->Fill(genJets.at(iJet).Pt(), weight);
        m_histogram["genBJet_eta"]->Fill(genJets.at(iJet).Eta(), weight);
    }
    // Getting number of hadrons of different flavours
    for(unsigned int iHad=0, nHads=bHadFlavour.size(); iHad<nHads; iHad++) {
        if(std::abs(bHadFlavour.at(iHad))!=21) nGenBhadsNoG++;
        if(std::abs(bHadFlavour.at(iHad))!=6) nGenBhadsNoT++;
        m_histogram["bHad_flavour"]->Fill(bHadFlavour.at(iHad),weight);
    }
    m_histogram["genBJet_multiplicity"]->Fill(nGenBjets,weight);
    m_histogram["bHad_multiplicity"]->Fill(nGenBhads,weight);
    m_histogram["bHadNoG_multiplicity"]->Fill(nGenBhadsNoG,weight);
    ((TH2*)m_histogram["bHadVsBJet_multiplicity"])->Fill(nGenBhads,nBJets,weight);
    ((TH2*)m_histogram["bHadVsBHadNoT_multiplicity"])->Fill(nGenBhads,nGenBhadsNoT,weight);

}


void DijetAnalyzer::bookHistos(const TString& step)
{
    constexpr const char* prefix = "dijet_";
    std::map<TString, TH1*>& m_histogram = m_stepHistograms_[step].m_histogram_;
    TString name;
    
    TString label("bla");

    name = "allJet_multiplicity";
    m_histogram[name] = store(new TH1D(prefix+name+step, "All jet multiplicity;N jets_{all} ["+label+"];Events",20,0,20));
    name = "jet_multiplicity";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Jet multiplicity;N jets_{reco} ["+label+"];Events",20,0,20));
    name = "jet_pt";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Jet Pt;jet Pt{reco} ["+label+"];Jets",30,0,300));
    name = "jet_eta";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Jet Eta;jet #eta{reco} ["+label+"];Jets",30,-2.6,2.6));
    name = "jet_btagDiscriminator";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Jet btagDiscriminator d;jet d{reco} ["+label+"];Jets",36,-0.1,1.1));

    name = "bJet_multiplicity";
    m_histogram[name] = store(new TH1D(prefix+name+step, "B-jet multiplicity;N b-jets_{reco} ["+label+"];Events",20,0,20));
    name = "bJet_pt";
    m_histogram[name] = store(new TH1D(prefix+name+step, "B-jet Pt;bJet Pt{reco} ["+label+"];Jets",30,0,300));
    name = "bJet_eta";
    m_histogram[name] = store(new TH1D(prefix+name+step, "B-jet Eta;bJet #eta{reco} ["+label+"];Jets",30,-2.6,2.6));
    name = "bJet_btagDiscriminator";
    m_histogram[name] = store(new TH1D(prefix+name+step, "B-jet btagDiscriminator d;jet d{reco} ["+label+"];Jets",36,-0.1,1.1));

    name = "genJet_multiplicity";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Gen. jet multiplicity;N jets_{gen} ["+label+"];Events",50,0,50));
    name = "genBJet_multiplicity";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Gen. b-jet multiplicity;N(b-jet)_{gen} ["+label+"];Events",15,0,15));
    name = "genBJet_pt";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Gen. b-jet Pt;bJet Pt{gen} ["+label+"];Jets",30,0,300));
    name = "genBJet_eta";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Gen. b-jet Eta;bJet #eta{gen} ["+label+"];Jets",30,-2.6,2.6));
    name = "bHad_multiplicity";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Gen. b-had multiplicity;N(b-had)_{gen} ["+label+"];Events",15,0,15));
    name = "bHad_flavour";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Gen. b-had flavour;Flavour(b-had)_{gen} ["+label+"];B-hadrons",60,-30,30));
    name = "bHadNoG_multiplicity";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Gen. b-had multiplicity (not from gluons);N(b-had NoG)_{gen} ["+label+"];Events",15,0,15));
    name = "bHadVsBJet_multiplicity";
    m_histogram[name] = store(new TH2D(prefix+name+step, "Gen. b-had/b-jet multiplicity;N(b-had)_{gen} ["+label+"];N(b-jet)_{reco}",15,0,15,15,0,15));
    name = "bHadVsBHadNoT_multiplicity";
    m_histogram[name] = store(new TH2D(prefix+name+step, "Gen. b-had/b-had^{not t#bar{t}} multiplicity;N(b-had)_{all} ["+label+"];N(b-had)_{not t#bar{t}}",15,0,15,15,0,15));

    name = "topJet_multiplicity_true";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Top jet multiplicity (true);N jets_{top}^{true} ["+label+"];Events",5,0,5));
    name = "topJet_multiplicity_reco";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Top jet multiplicity (reco);N jets_{top}^{reco} ["+label+"];Events",5,0,5));
    name = "topBJet_multiplicity_true";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Top b-jet multiplicity (true);N b-tagged jets_{top}^{true} ["+label+"];Events",5,0,5));
    name = "topBJet_multiplicity_reco";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Top b-jet multiplicity (true);N b-tagged jets_{top}^{reco} ["+label+"];Events",5,0,5));
    name = "higgsJet_multiplicity_true";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Higgs jet multiplicity (true);N jets_{higgs}^{true} ["+label+"];Events",5,0,5));
    name = "higgsBJet_multiplicity_true";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Higgs b-jet multiplicity (true);N b-tagged jets_{higgs}^{true} ["+label+"];Events",5,0,5));

    name = "dijet_correctJet_multiplicity_all";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Number of correct jets;N jets_{correct}^{all} ["+label+"];Jet pairs",4,0,4));
    name = "dijet_correctJet_multiplicity_trueTopJets";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Number of correct jets;N jets_{correct}^{trueTopJets} ["+label+"];Jet pairs",4,0,4));
    name = "dijet_correctJet_multiplicity_recoTopJets";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Number of correct jets;N jets_{correct}^{recoTopJets} ["+label+"];Jet pairs",4,0,4));

    name = "dijet_correctPairFraction_all";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Correct pair fraction;correct/all (all) ["+label+"];Events",15,-0.3,1.2));
    name = "dijet_correctPairFraction_trueTopJets";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Correct pair fraction;correct/all (trueTopJets) ["+label+"];Events",15,-0.3,1.2));
    name = "dijet_correctPairFraction_recoTopJets";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Correct pair fraction;correct/all (recoTopJets) ["+label+"];Events",15,-0.3,1.2));

    name = "dijet_mass_all";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Dijet mass;M(dijet)_{all} ["+label+"];Jet pairs",25,0,500));
    name = "dijet_mass_trueTopJets";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Dijet mass;M(dijet)_{trueTopJets} ["+label+"];Jet pairs",25,0,500));
    name = "dijet_mass_recoTopJets";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Dijet mass;M(dijet)_{recoTopJets} ["+label+"];Jet pairs",25,0,500));

    name = "jet_PtLt30_multiplicity";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Jet multiplicity (Pt<30);N jets_{reco}^{Pt<30} ["+label+"];Events",20,0,20));
    name = "bJet_PtLt30_multiplicity";
    m_histogram[name] = store(new TH1D(prefix+name+step, "B-jet multiplicity (Pt<30);N b-jets_{reco}^{Pt<30} ["+label+"];Events",20,0,20));
    name = "jet_PtLt30_flavour";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Jet flavour (Pt<30);flavour(jet)_{Pt<30} ["+label+"];Jets",30,0,30));
    name = "bJet_PtLt30_flavour";
    m_histogram[name] = store(new TH1D(prefix+name+step, "B-jet flavour (Pt<30);flavour(b-jet)_{Pt<30} ["+label+"];B-tagged jets",30,0,30));
    name = "jet_PtLt30_btagDiscriminator";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Jet btagDiscriminator d (Pt<30);d_{reco}^{Pt<30} ["+label+"];Jets",20,0,1));
    name = "bJet_PtLt30_btagDiscriminator";
    m_histogram[name] = store(new TH1D(prefix+name+step, "B-jet btagDiscriminator d (Pt<30);d_{reco}^{Pt<30} ["+label+"];B-tagged jets",20,0,1));

    name = "weight";
    m_histogram[name] = store(new TH1D(prefix+name+step, "Weight of the event;weight ["+label+"];Events",30,0,3));

}


float DijetAnalyzer::correctPairFraction(const VLV& allJets, const std::vector<int>& jetsId,
                                         const std::vector<int>& bJetsId, const std::vector<double>& jetsBtagDiscriminant,
                                         const std::vector<int>& topJetsId, const std::vector<int>& higgsJetsId,
                                         const double weight, TH1* h_dijetMass, TH1* h_correctJetMultiplicity, bool fillAllCombinations)
{
    unsigned int nJets = jetsId.size();
    int nCorrectJetPairs = 0;
    int nAllJetPairs = 0;


    std::vector<int> higgsJetCandidatesId(0);

    for(unsigned int iJet1 = 0; iJet1<nJets; iJet1++) {
        const int iAllJet1 = jetsId.at(iJet1);
        if(isInVector(topJetsId, iAllJet1)) continue;              // Skip jet if it was assigned to the Top
        if(!isInVector(bJetsId, iAllJet1)) continue;               // Skip jet if it is not b-tagged

        for(unsigned int iJet2 = 0; iJet2<iJet1; iJet2++) {
            const int iAllJet2 = jetsId.at(iJet2);
            if(isInVector(topJetsId, iAllJet2)) continue;          // Skip jet if it was assigned to the Top
            if(!isInVector(bJetsId, iAllJet2)) continue;           // Skip jet if it is not b-tagged

            int nCorrectJets = 0;
            if(fillAllCombinations) {
                // Filling the dijet mass
                LV dijet = allJets.at(iAllJet1) + allJets.at(iAllJet2);
                h_dijetMass->Fill(dijet.M(),weight);

                if(isInVector(higgsJetsId, iAllJet1)) nCorrectJets++;
                if(isInVector(higgsJetsId, iAllJet2)) nCorrectJets++;
                // Filling the number of correct jets in the dijet pair
                h_correctJetMultiplicity->Fill(nCorrectJets, weight);
            }       // If fill all combinations of jets

            // Adding the 2 jets to the list of candidates for b-jets from Higgs
            if(!isInVector(higgsJetCandidatesId,iAllJet1)) higgsJetCandidatesId.push_back(iAllJet1);
            if(!isInVector(higgsJetCandidatesId,iAllJet2)) higgsJetCandidatesId.push_back(iAllJet2);

            // Updating the number of correct/wrong pairs
            if(nCorrectJets>=2) nCorrectJetPairs++;
            nAllJetPairs++;

        }       // End of the second loop over jets
    }       // End of the first loop over jets

    float correctPairFraction;
    if(higgsJetCandidatesId.size()<2) {
        correctPairFraction = -0.19;                   // If less than 2 true Higgs jets in acceptance
        return correctPairFraction;
    }

    correctPairFraction = (float)nCorrectJetPairs/nAllJetPairs;
//     if(bJetsId.size()>3 && topJetsId.size()==0) printf("All: %d\tCor: %d\tFrac: %.2f\n",nAllJetPairs,nCorrectJetPairs,correctPairFraction);

    if(higgsJetsId.size()<2) correctPairFraction = -0.09;          // If less than 2 candidates were found

    // Stopping if best combination is not needed
    if(fillAllCombinations) return correctPairFraction;

    // Finding the two jets that are assumed to come from the Higgs
    // Ordering jets by b-tagging discriminant if there are more than 2 of them
    if(higgsJetCandidatesId.size()>2) ttbar::orderIndices(higgsJetCandidatesId, jetsBtagDiscriminant);
    LV dijet = allJets.at(higgsJetCandidatesId.at(0)) + allJets.at(higgsJetCandidatesId.at(1));
    h_dijetMass->Fill(dijet.M(), weight);


    // Counting the number of correct higgs jets among the candidates
    int nCorrectJets = 0;
    for(unsigned int iJet=0; iJet<higgsJetsId.size(); iJet++) {
        int allJetId = higgsJetsId.at(iJet);
        if(!isInVector(higgsJetCandidatesId, allJetId)) continue;
        nCorrectJets++;
    }
    h_correctJetMultiplicity->Fill(nCorrectJets, weight);

    if(higgsJetsId.size()>=2)  {
        correctPairFraction = (int)(isInVector(higgsJetsId, higgsJetCandidatesId.at(0)) && isInVector(higgsJetsId, higgsJetCandidatesId.at(1)));
    }

    return correctPairFraction;
}


int DijetAnalyzer::genJetIdOfRecoJet(const LV& recoJet, const VLV& genJets, const float dR_max)
{
    float dR_min = 999.9;
    int genJetId = -1;
    // Loop over gen jets to find the closest one to reco jet
    for(unsigned int iJet=0, nJets=genJets.size(); iJet<nJets; iJet++) {
        float dR = ROOT::Math::VectorUtil::DeltaR(recoJet,genJets.at(iJet));
        if(dR>=dR_min) continue;
        if(dR>=dR_max) continue;
        dR_min = dR;
        genJetId = iJet;
    }

    return genJetId;
}


std::vector<int> DijetAnalyzer::bHadIdsInGenJet(const int jetId, const std::vector<int>& hadJetIndices)
{
    std::vector<int> hadIndices;

    if(jetId<0) return hadIndices;

    for(unsigned int iHad=0, nHads=hadJetIndices.size(); iHad<nHads; iHad++) {
        if(hadJetIndices.at(iHad)!=jetId) continue;
        hadIndices.push_back(iHad);
    }

    return hadIndices;
}


std::vector<int> DijetAnalyzer::bHadFlavoursInGenJet(const int jetId, const std::vector<int>& hadJetIndices,
                                                     const std::vector<int>& hadFlavours, const bool absFlavour)
{
    std::vector<int> flavours;
    std::vector<int> hadIndices = bHadIdsInGenJet(jetId, hadJetIndices);

    for(unsigned int iHad=0, nHads=hadIndices.size(); iHad<nHads; iHad++) {
        int hadId = hadIndices.at(iHad);
        int flavour = hadFlavours.at(hadId);
        if(absFlavour) flavour = std::abs(flavour);

        if(isInVector(flavours,flavour)) continue;

        flavours.push_back(flavour);
    }

    return flavours;
}


bool DijetAnalyzer::isInVector(const std::vector<int>& idVector, const int id)
{
    bool isIn = std::find(idVector.begin(), idVector.end(), id) != idVector.end();

    return isIn;
}



