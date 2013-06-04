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

        if(jet.Pt()>=30) continue;
        // Analyzing jets with Pt<30
        nJetsPtLt30++;
        if(isInVector(bJetsId, iJet)) nBJetsPtLt30++;
    }

    // Identifying numbers of jets and b-jets
    unsigned int nAllJets = allJets.size();
    unsigned int nGenJets = genJets.size();
    unsigned int nBJets = bJetsId.size();
    unsigned int nJets = jets.size();

    // Identifying the category
    int jetCatId = jetCategories_->categoryId(nJets,nBJets);
    if(jetCatId>=jetCategories_->numberOfCategories() || jetCatId<0) return;        // Skipping if category with such Id doesn't exist

    // Extracting map of histograms for the current jet category
    std::map<TString, TH1*> histos = histograms_.at(jetCatId).map_histo;

    histos["allJet_multiplicity"]->Fill(nAllJets,weight);
    histos["jet_multiplicity"]->Fill(nJets,weight);
    histos["bJet_multiplicity"]->Fill(nBJets,weight);
    histos["genJet_multiplicity"]->Fill(nGenJets,weight);
    histos["topJet_multiplicity_true"]->Fill(trueTopJetsId.size(), weight);
    histos["jet_PtLt30_multiplicity"]->Fill(nJetsPtLt30, weight);
    histos["bJet_PtLt30_multiplicity"]->Fill(nBJetsPtLt30, weight);

    // Analyzing pairs of jets except the ones coming from Top
    for(unsigned int iJet1 = 0; iJet1<nJets; iJet1++) {
        if(isInVector(topJetsId, iJet1)) continue;              // Skip jet if it was assigned to the Top
        if(!isInVector(bJetsId, iJet1)) continue;               // Skip jet if it is not b-tagged

        // Finding the corresponding genJetId and its flavours
        int genJetId1 = genJetIdOfRecoJet(jets.at(iJet1), genJets);
        std::vector<int> flavJet1 = bHadFlavoursInGenJet(genJetId1, bHadJetIndex, bHadFlavour, true);
        for(unsigned int iFlav = 0, iFlavN = flavJet1.size(); iFlav<iFlavN; iFlav++) {
            histos["jet_PtLt30_flavour"]->Fill(flavJet1.at(iFlav), weight);
            if(!isInVector(bJetsId,iJet1)) continue;
            histos["bJet_PtLt30_flavour"]->Fill(flavJet1.at(iFlav), weight);
        }

        for(unsigned int iJet2 = 0; iJet2<iJet1; iJet2++) {
            if(isInVector(topJetsId, iJet2)) continue;          // Skip jet if it was assigned to the Top
            if(!isInVector(bJetsId, iJet2)) continue;           // Skip jet if it is not b-tagged

            // Filling the dijet mass
            LV dijet = jets.at(iJet1) + jets.at(iJet2);
            histos["dijet_mass_all"]->Fill(dijet.M(),weight);

            // Filling the number of correct jets in the dijet pair
            int nCorrectJets = 0;
            if(isInVector(trueHiggsJetsId, iJet1)) nCorrectJets++;
            if(isInVector(trueHiggsJetsId, iJet2)) nCorrectJets++;
            histos["dijet_correctJet_multiplicity"]->Fill(nCorrectJets,weight);

            // Finding the corresponding genJetId's
            int genJetId1 = genJetIdOfRecoJet(jets.at(iJet1), genJets);
            int genJetId2 = genJetIdOfRecoJet(jets.at(iJet2), genJets);

            if(genJetId1==genJetId2) genJetId2=-1;

            // Finding the flavours of the jets
            std::vector<int> flavJet2 = bHadFlavoursInGenJet(genJetId2, bHadJetIndex, bHadFlavour, true);

            // Filling flavours of the jets to hitograms in or outside 60-100 GeV mass peak
            bool inWpeak = (dijet.M() > 60.0 && dijet.M() < 100.0)?true:false;
            TH1* hToFill = (inWpeak)?histos["dijet_flavour_inpeak"]:histos["dijet_flavour_outpeak"];
            for(std::vector<int>::iterator it = flavJet1.begin(); it!=flavJet1.end(); ++it) {
                hToFill->Fill(*it,weight);
            }
            for(std::vector<int>::iterator it = flavJet2.begin(); it!=flavJet2.end(); ++it) {
                hToFill->Fill(*it,weight);
            }
            if(flavJet1.size()<1 && flavJet2.size()<1) hToFill->Fill(-40.0,weight);

        }       // End of the second loop over jets
    }       // End of the first loop over jets

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
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Gen. jet multiplicity;N jets_{gen} ["+label+"];Events",20,0,20));
    name = "dijet_mass_all";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Dijet mass;M(dijet)_{all} ["+label+"];Events",25,0,500));
    name = "dijet_flavour_inpeak";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Jet flavour in dijet;flavour(dijet)_{inpeak} ["+label+"];Events",100,-50,50));
    name = "dijet_flavour_outpeak";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Jet flavour in dijet;flavour(dijet)_{outpeak} ["+label+"];Events",100,-50,50));
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
    name = "dijet_correctJet_multiplicity";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Number of correct jets in dijet pair;N jets_{correct} ["+label+"];Dijet pairs",4,0,4));
    name = "jet_PtLt30_multiplicity";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Jet multiplicity (Pt<30);N jets_{reco}^{Pt<30} ["+label+"];Events",20,0,20));
    name = "bJet_PtLt30_multiplicity";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "B-jet multiplicity (Pt<30);N b-jets_{reco}^{Pt<30} ["+label+"];Events",20,0,20));
    name = "jet_PtLt30_flavour";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "Jet flavour (Pt<30);flavour(jet)_{Pt<30} ["+label+"];Events",30,0,30));
    name = "bJet_PtLt30_flavour";
    histos.map_histo[name] = store(new TH1D(base+name+"_"+=cat, "B-jet flavour (Pt<30);flavour(b-jet)_{Pt<30} ["+label+"];Events",30,0,30));


    histograms_.push_back(histos);
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
