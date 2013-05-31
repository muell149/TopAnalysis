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


    // Creating a vector of selected jets
    VLV jets(0);
    std::vector<double> jetsBout;
    for(unsigned int iJet_ = 0; iJet_<jetsId.size(); iJet_++) {
        unsigned int iJet = jetsId.at(iJet_);
        LV jet = allJets.at(iJet);
        jets.push_back(jet);
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

    // Analyzing pairs of jets except the ones coming from Top
    for(unsigned int iJet1 = 0; iJet1<nJets; iJet1++) {
        if(std::find(topJetsId.begin(), topJetsId.end(), iJet1) != topJetsId.end()) continue;       // Skip jet if it was assigned to the Top
        if(std::find(bJetsId.begin(), bJetsId.end(), iJet1) != bJetsId.end()) continue;             // Skip jet if it is not b-tagged

        for(unsigned int iJet2 = 0; iJet2<iJet1; iJet2++) {
            if(std::find(bJetsId.begin(), bJetsId.end(), iJet1) != bJetsId.end()) continue;         // Skip jet if it is not b-tagged

            LV dijet = jets.at(iJet1) + jets.at(iJet2);
            histos["dijet_mass_all"]->Fill(dijet.M(),weight);

            // Finding the corresponding genJetId's
            int genJetId1 = genJetIdOfRecoJet(jets.at(iJet1), genJets);
            int genJetId2 = genJetIdOfRecoJet(jets.at(iJet2), genJets);

            if(genJetId1==genJetId2) genJetId2=-1;

            // Finding the flavours of jets
            std::vector<int> flavJet1;
            std::vector<int> flavJet2;
            flavoursGenJet(genJetId1, bHadJetIndex, bHadFlavour, flavJet1);
            flavoursGenJet(genJetId2, bHadJetIndex, bHadFlavour, flavJet2);

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
        if(std::find(bHadJetIndex.begin(),bHadJetIndex.end(),iJet) == bHadJetIndex.end()) continue;
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


    histograms_.push_back(histos);
}


int DijetAnalyzer::genJetIdOfRecoJet(const LV& recoJet, const VLV& genJets)
{
    float dR_min = 999.9;
    int genJetId = -1;
    // Loop over gen jets to find the closest one to reco jet
    for(unsigned int iJet=0, nJets=genJets.size(); iJet<nJets; iJet++) {
        float dR = ROOT::Math::VectorUtil::DeltaR(recoJet,genJets.at(iJet));
        if(dR>=dR_min) continue;
        dR_min = dR;
        genJetId = iJet;
    }

    return genJetId;
}


bool DijetAnalyzer::flavoursGenJet(int genJetId, const std::vector<int>& bHadJetIndex, const std::vector<int>& bHadFlavour, std::vector<int>& flavours)
{
    bool didFind = false;

    if(genJetId<0) return didFind;

    // Loop over bHadrons to find hadron that is matched to this jet
    for(unsigned int iHad=0, nHads=bHadJetIndex.size(); iHad<nHads; iHad++) {
        if(bHadJetIndex.at(iHad) != genJetId) continue;
        didFind = true;
        int flavour = bHadFlavour.at(iHad);
        if(std::find(flavours.begin(), flavours.end(), flavour) != flavours.end()) continue;
        flavours.push_back(flavour);
    }


    return didFind;
}

void DijetAnalyzer::clear()
{
    selectorList_ = 0;
    histograms_.clear();
}

void DijetAnalyzer::SetJetCategories(const JetCategories& jetCategories)
{
//     printf("    DijetAnalyzer::SetJetCategories: Setting Jet Categories\n");
    jetCategories_ = &jetCategories;
}

void DijetAnalyzer::setOutputSelectorList(TSelectorList* output)
{
//     printf("    DijetAnalyzer::setOutputSelectorList: Setting output\n");
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
