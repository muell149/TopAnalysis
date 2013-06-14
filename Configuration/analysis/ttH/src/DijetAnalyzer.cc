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
#include "../../diLeptonic/src/classes.h"


DijetAnalyzer::DijetAnalyzer():
selectorList_(0)
{}

DijetAnalyzer::Input::Input(const VLV& allJets_, const std::vector<int>& jetsId_, const std::vector<int>& bJetsId_,
                            const std::vector<int>& topJetsId_, const VLV& genJets_,
                            const std::vector<int>& bHadJetIndex_, const std::vector<int>& bHadFlavour_,
                            const LV& met_, const LV& lepton_, const LV& antilepton_):
allJets(allJets_),
jetsId(jetsId_),
bJetsId(bJetsId_),
topJetsId(topJetsId_),
genJets(genJets_),
bHadJetIndex(bHadJetIndex_),
bHadFlavour(bHadFlavour_),
met(met_),
lepton(lepton_),
antilepton(antilepton_)
{}


void DijetAnalyzer::fill(const Input& input, const double& weight)
{

    // Extracting input data to more comfortable variables
    const VLV allJets = input.allJets;
    const LV lepton = input.lepton;
    const LV antilepton = input.antilepton;
    const LV met = input.met;
    const std::vector<int> jetsId = input.jetsId;
    const std::vector<int> bJetsId = input.bJetsId;
    const std::vector<int> topJetsId = input.topJetsId;

    // Setting variables of gen. level if available
    const VLV genJets = (&input.genJets!=0)?input.genJets:VLV(0);
    const std::vector<int> bHadJetIndex = (&input.bHadJetIndex!=0)?input.bHadJetIndex:std::vector<int>(0);
    const std::vector<int> bHadFlavour = (&input.bHadFlavour!=0)?input.bHadFlavour:std::vector<int>(0);
    std::vector<int> trueTopJetsId;
    std::vector<int> trueHiggsJetsId;


    // Identifying numbers of jets and b-jets
    unsigned int nAllJets = allJets.size();
    unsigned int nGenJets = genJets.size();
    unsigned int nBJets = bJetsId.size();
    unsigned int nJets = jetsId.size();

    // Identifying the category
    int jetCatId = jetCategories_->categoryId(nJets,nBJets);
    if(jetCatId>=jetCategories_->numberOfCategories() || jetCatId<0) return;        // Skipping if category with such Id doesn't exist


    // Extracting map of histograms for the current jet category
    std::map<TString, TH1*> histos = histograms_.at(jetCatId).map_histo;


    // Creating a vector of selected jets
    VLV jets(0);
    int nJetsPtLt30 = 0;
    int nBJetsPtLt30 = 0;
    for(unsigned int iJet = 0, iJetN=jetsId.size(); iJet<iJetN; iJet++) {
        unsigned int iAllJet = jetsId.at(iJet);
        LV jet = allJets.at(iAllJet);
        jets.push_back(jet);

        // Checking if the jet contains b-hadron from top
        int genJetId = genJetIdOfRecoJet(jet, genJets);
        std::vector<int> hadIds = bHadFlavoursInGenJet(genJetId, bHadJetIndex, bHadFlavour, true);
        bool hasTopHadron = isInVector(hadIds, 6);
        if(hasTopHadron) trueTopJetsId.push_back(iJet);
        bool hasHiggsHadron = isInVector(hadIds, 25);
        if(hasHiggsHadron) trueHiggsJetsId.push_back(iJet);


        // Analyzing only jets with Pt<30
        if(jet.Pt()>=30) continue;
        nJetsPtLt30++;
        if(isInVector(bJetsId, iJet)) nBJetsPtLt30++;

        // Finding the corresponding genJetId and its flavours
        int genJetId1 = genJetIdOfRecoJet(jet, genJets);
        std::vector<int> flavJet = bHadFlavoursInGenJet(genJetId1, bHadJetIndex, bHadFlavour, true);
        for(unsigned int iFlav = 0, iFlavN = flavJet.size(); iFlav<iFlavN; iFlav++) {
            histos["jet_PtLt30_flavour"]->Fill(flavJet.at(iFlav), weight);
            if(!isInVector(bJetsId,iJet)) continue;            // Skip jet if it is not b-tagged
            histos["bJet_PtLt30_flavour"]->Fill(flavJet.at(iFlav), weight);
            if(isInVector(topJetsId, iJet)) continue;          // Skip jet if it was assigned to the Top
        }       // End of loop over flavours of the jet
    }       // End of loop over all reco jets in the event


    histos["allJet_multiplicity"]->Fill(nAllJets, weight);
    histos["jet_multiplicity"]->Fill(nJets, weight);
    histos["bJet_multiplicity"]->Fill(nBJets, weight);
    histos["genJet_multiplicity"]->Fill(nGenJets, weight);
    histos["topJet_multiplicity_true"]->Fill(trueTopJetsId.size(), weight);
    histos["higgsJet_multiplicity_true"]->Fill(trueHiggsJetsId.size(), weight);
    histos["jet_PtLt30_multiplicity"]->Fill(nJetsPtLt30, weight);
    histos["bJet_PtLt30_multiplicity"]->Fill(nBJetsPtLt30, weight);
    histos["weight"]->Fill(weight, weight);

    std::vector<int> emptyVector;

    // Analyzing jet pairs for all jet combinations
    float correctPairFraction_all = correctPairFraction(jets, bJetsId, emptyVector, trueHiggsJetsId, weight, histos["dijet_mass_all"], histos["dijet_correctJet_multiplicity_all"]);
    histos["dijet_correctPairFraction_all"]->Fill(correctPairFraction_all, weight);

    // Analyzing jet pairs for all jet combinations except true b-jets from top
    float correctPairFraction_trueTopJets = correctPairFraction(jets, bJetsId, trueTopJetsId, trueHiggsJetsId, weight, histos["dijet_mass_trueTopJets"], histos["dijet_correctJet_multiplicity_trueTopJets"]);
    histos["dijet_correctPairFraction_trueTopJets"]->Fill(correctPairFraction_trueTopJets, weight);

    // Analyzing jet pairs for all jet combinations except reco b-jets from top found by kinematic reconstruction
    float correctPairFraction_recoTopJets = correctPairFraction(jets, bJetsId, topJetsId, trueHiggsJetsId, weight, histos["dijet_mass_recoTopJets"], histos["dijet_correctJet_multiplicity_recoTopJets"]);
    histos["dijet_correctPairFraction_recoTopJets"]->Fill(correctPairFraction_recoTopJets, weight);


    // Counting number of gen b-jets
    int nGenBjets = 0;
    int nGenBhads = bHadJetIndex.size();
    int nGenBhadsNoG = 0;
    // Finding jets that are matched to b-hadrons
    for(unsigned int iJet=0, nJets=genJets.size(); iJet<nJets; iJet++) {
        if(!isInVector(bHadJetIndex, iJet)) continue;
        nGenBjets++;
    }
    // Finding hadrons come not from gluons
    for(unsigned int iHad=0, nHads=bHadFlavour.size(); iHad<nHads; iHad++) {
        if(bHadFlavour.at(iHad)==21) continue;
        nGenBhadsNoG++;
    }
    histos["genBJet_multiplicity"]->Fill(nGenBjets,weight);
    histos["genBHad_multiplicity"]->Fill(nGenBhads,weight);
    histos["genBHadNoG_multiplicity"]->Fill(nGenBhadsNoG,weight);
    ((TH2*)histos["genBHadVsBJet_multiplicity"])->Fill(nGenBhads,nBJets,weight);

}


void DijetAnalyzer::bookHistos(int cat,const TString& label)
{
    CatHistograms histos;
    TString base = "diJetAn_";
    TString name;

    name = "allJet_multiplicity";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "All jet multiplicity;N jets_{all} ["+label+"];Events",20,0,20));
    name = "jet_multiplicity";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Jet multiplicity;N jets_{reco} ["+label+"];Events",20,0,20));
    name = "bJet_multiplicity";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "B-jet multiplicity;N b-jets_{reco} ["+label+"];Events",20,0,20));
    name = "genJet_multiplicity";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Gen. jet multiplicity;N jets_{gen} ["+label+"];Events",50,0,50));
    name = "genBJet_multiplicity";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Gen. b-jet multiplicity;N(b-jet)_{gen} ["+label+"];Events",15,0,15));
    name = "genBHad_multiplicity";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Gen. b-had multiplicity;N(b-had)_{gen} ["+label+"];Events",15,0,15));
    name = "genBHadNoG_multiplicity";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Gen. b-had multiplicity (not from gluons);N(b-had NoG)_{gen} ["+label+"];Events",15,0,15));
    name = "genBHadVsBJet_multiplicity";
    histos.map_histo[name] = store(new TH2D(base+name+"_"+=cat, "Gen. b-had/b-jet multiplicity;N(b-had)_{gen} ["+label+"];N(b-jet)_{reco}",15,0,15,15,0,15));
    name = "topJet_multiplicity_true";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Top jet multiplicity (true);N jets_{top}^{true} ["+label+"];Events",20,0,20));
    name = "higgsJet_multiplicity_true";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Higgs jet multiplicity (true);N jets_{higgs}^{true} ["+label+"];Events",20,0,20));
    name = "topJet_multiplicity_reco";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Top jet multiplicity (reco);N jets_{top}^{reco} ["+label+"];Events",20,0,20));
    name = "dijet_correctJet_multiplicity_all";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Number of correct jets;N jets_{correct}^{all} ["+label+"];Jet pairs",4,0,4));
    name = "dijet_correctJet_multiplicity_trueTopJets";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Number of correct jets;N jets_{correct}^{trueTopJets} ["+label+"];Jet pairs",4,0,4));
    name = "dijet_correctJet_multiplicity_recoTopJets";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Number of correct jets;N jets_{correct}^{recoTopJets} ["+label+"];Jet pairs",4,0,4));
    name = "dijet_correctPairFraction_all";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Correct pair fraction;correct/all (all) ["+label+"];Events",24,0,1.2));
    name = "dijet_correctPairFraction_trueTopJets";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Correct pair fraction;correct/all (trueTopJets) ["+label+"];Events",24,0,1.2));
    name = "dijet_correctPairFraction_recoTopJets";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Correct pair fraction;correct/all (recoTopJets) ["+label+"];Events",24,0,1.2));
    name = "jet_PtLt30_multiplicity";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Jet multiplicity (Pt<30);N jets_{reco}^{Pt<30} ["+label+"];Events",20,0,20));
    name = "bJet_PtLt30_multiplicity";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "B-jet multiplicity (Pt<30);N b-jets_{reco}^{Pt<30} ["+label+"];Events",20,0,20));
    name = "dijet_mass_all";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Dijet mass;M(dijet)_{all} ["+label+"];Jet pairs",25,0,500));
    name = "dijet_mass_trueTopJets";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Dijet mass;M(dijet)_{trueTopJets} ["+label+"];Jet pairs",25,0,500));
    name = "dijet_mass_recoTopJets";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Dijet mass;M(dijet)_{recoTopJets} ["+label+"];Jet pairs",25,0,500));
    name = "jet_PtLt30_flavour";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Jet flavour (Pt<30);flavour(jet)_{Pt<30} ["+label+"];Jets",30,0,30));
    name = "bJet_PtLt30_flavour";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "B-jet flavour (Pt<30);flavour(b-jet)_{Pt<30} ["+label+"];B-tagged jets",30,0,30));
    name = "weight";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Weight of the event;weight ["+label+"];Events",30,0,3));


    histograms_.push_back(histos);
}


float DijetAnalyzer::correctPairFraction(const VLV& jets, const std::vector<int>& bJetsId,
                                      const std::vector<int>& topJetsId, const std::vector<int>& higgsJetsId,
                                      const double weight, TH1* h_dijetMass, TH1* h_correctJetMultiplicity)
{
    unsigned int nJets = jets.size();
    int nCorrectJetPairs = 0;
    int nAllJetPairs = 0;
    for(unsigned int iJet1 = 0; iJet1<nJets; iJet1++) {
        if(isInVector(topJetsId, iJet1)) continue;              // Skip jet if it was assigned to the Top
        if(!isInVector(bJetsId, iJet1)) continue;               // Skip jet if it is not b-tagged

        for(unsigned int iJet2 = 0; iJet2<iJet1; iJet2++) {
            if(isInVector(topJetsId, iJet2)) continue;          // Skip jet if it was assigned to the Top
            if(!isInVector(bJetsId, iJet2)) continue;           // Skip jet if it is not b-tagged

            // Filling the dijet mass
            LV dijet = jets.at(iJet1) + jets.at(iJet2);
            h_dijetMass->Fill(dijet.M(),weight);

            // Filling the number of correct jets in the dijet pair
            int nCorrectJets = 0;
            if(isInVector(higgsJetsId, iJet1)) nCorrectJets++;
            if(isInVector(higgsJetsId, iJet2)) nCorrectJets++;
            h_correctJetMultiplicity->Fill(nCorrectJets,weight);

            // Updating the number of correct/wrong pairs
            if(nCorrectJets>=2) nCorrectJetPairs++;
            nAllJetPairs++;

        }       // End of the second loop over jets
    }       // End of the first loop over jets

    if(nAllJetPairs<1) return -1;

    return (float)nCorrectJetPairs/nAllJetPairs;
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



void DijetAnalyzer::clear()
{
    selectorList_ = 0;
    histograms_.clear();
}


void DijetAnalyzer::SetJetCategories(const JetCategories& jetCategories)
{
    jetCategories_ = &jetCategories;
}


void DijetAnalyzer::setOutputSelectorList(TSelectorList* output)
{
    selectorList_ = output;
    this->bookAllHistos();
}


void DijetAnalyzer::bookAllHistos()
{
    const std::vector<TString> v_binLabel(jetCategories_->binLabels());
    int cat = 0;
    for(std::vector<TString>::const_iterator i_binLabel = v_binLabel.begin(); i_binLabel != v_binLabel.end(); ++i_binLabel){
        const TString binLabel(*i_binLabel);
        bookHistos(cat,binLabel);
        cat++;
    }

}
