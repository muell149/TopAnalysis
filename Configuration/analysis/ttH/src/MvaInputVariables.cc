#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#include <TTree.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TString.h>
#include <Math/VectorUtil.h>
#include <TSelectorList.h>
#include <Rtypes.h>
#include <TCut.h>
#include <TMVA/Tools.h>
#include <TMVA/Config.h>
#include <TMVA/Factory.h>
#include <TMVA/Types.h>
#include <TMVA/Reader.h>

#include "MvaInputVariables.h"
#include "analysisStructs.h"
#include "../../diLeptonic/src/sampleHelpers.h"
#include "../../diLeptonic/src/classes.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"




MvaInputTopJetsVariables::Input::Input():
bQuarkRecoJetMatched_(0),
correctCombination_(0),
swappedCombination_(0),
eventWeight_(-999.),
mvaWeightCorrect_(-999.),
mvaWeightSwapped_(-999.),
bestMvaWeightCorrect_(-999.),
bestMvaWeightSwapped_(-999.),
meanDeltaPhi_b_met_(-999.),
massDiff_recoil_bbbar_(-999.),
pt_b_antiLepton_(-999.),
pt_antiB_lepton_(-999.),
deltaR_b_antiLepton_(-999.),
deltaR_antiB_lepton_(-999.),
btagDiscriminatorSum_(-999.),
deltaPhi_antiBLepton_bAntiLepton_(-999.),
massDiff_fullBLepton_bbbar_(-999.),
meanMt_b_met_(-999.),
massSum_antiBLepton_bAntiLepton_(-999.),
massDiff_antiBLepton_bAntiLepton_(-999.)
{}



MvaInputTopJetsVariables::Input::Input(const LV& lepton, const LV& antiLepton,
                                       const LV& bJet, const LV& antiBJet,
                                       const double& bJetBtagDiscriminator, const double& antiBJetBtagDiscriminator,
                                       const double& jetChargeDiff,
                                       const LV& jetRecoil, const LV& met,
                                       const bool bQuarkRecoJetMatched,
                                       const bool correctCombination, const bool swappedCombination,
                                       const double& eventWeight)
{
    using ROOT::Math::VectorUtil::DeltaPhi;
    using ROOT::Math::VectorUtil::DeltaR;
    
    // Helper variables for MVA
    const LV bAntiBSystem = bJet + antiBJet;
    const LV bAntiLeptonSystem = bJet + antiLepton;
    const LV antiBLeptonSystem = antiBJet + lepton;
    const LV fullBLeptonSystem = bAntiLeptonSystem + antiBLeptonSystem;
    
    // Fill the variables for MVA TTree
    bQuarkRecoJetMatched_ = bQuarkRecoJetMatched;
    correctCombination_ = correctCombination;
    swappedCombination_ = swappedCombination;
    eventWeight_ = eventWeight;
    mvaWeightCorrect_ = -999.;
    mvaWeightSwapped_ = -999.;
    bestMvaWeightCorrect_ = -999.;
    bestMvaWeightSwapped_ = -999.;
    jetChargeDiff_ = jetChargeDiff;
    
    meanDeltaPhi_b_met_ = 0.5*(std::abs(DeltaPhi(bJet, met)) + std::abs(DeltaPhi(antiBJet, met)));
    massDiff_recoil_bbbar_ = jetRecoil.M() - bAntiBSystem.M();
    pt_b_antiLepton_ = bAntiLeptonSystem.pt();
    pt_antiB_lepton_ = antiBLeptonSystem.pt();
    deltaR_b_antiLepton_ = DeltaR(bJet, antiLepton);
    deltaR_antiB_lepton_ = DeltaR(antiBJet, lepton);
    btagDiscriminatorSum_ = bJetBtagDiscriminator + antiBJetBtagDiscriminator;
    deltaPhi_antiBLepton_bAntiLepton_ = std::abs(DeltaPhi(antiBLeptonSystem, bAntiLeptonSystem));
    massDiff_fullBLepton_bbbar_ = fullBLeptonSystem.M() - bAntiBSystem.M();
    meanMt_b_met_ = 0.5*((bJet + met).Mt() + (antiBJet + met).Mt());
    massSum_antiBLepton_bAntiLepton_ = antiBLeptonSystem.M() + bAntiLeptonSystem.M();
    massDiff_antiBLepton_bAntiLepton_ = antiBLeptonSystem.M() - bAntiLeptonSystem.M();
}



void MvaInputTopJetsVariables::Input::setMvaWeights(const float weightCorrect, const float weightSwapped)
{
    mvaWeightCorrect_ = weightCorrect;
    mvaWeightSwapped_ = weightSwapped;
}



MvaInputTopJetsVariables::MvaInputTopJetsVariables(const std::vector<TString>& selectionSteps,
                                                   const char* mvaWeightsFile, const char* mvaInputDir):
selectorList_(0),
t_mvaInput_(0),
mvaWeightsReader_(0),
selectionSteps_(selectionSteps),
mvaInputDir_(mvaInputDir)
{
    if(!mvaWeightsFile){
        std::cout<<"--- Beginning setting up production of MVA input\n";
        std::cout<<"=== Finishing setting up production of MVA input\n\n";
        return;
    }
    
    std::cout<<"--- Beginning setting up MVA weights from file\n";
    
    ifstream inputFile(mvaWeightsFile);
    if(inputFile.fail()){
        std::cout<<"Input file containing MVA weights not found: "<<mvaWeightsFile
                 <<"\n...running without MVA weights, i.e. setting them all to 1.\n";
    }
    else{
        mvaWeightsReader_ = new TMVA::Reader("Color");

        Input& mvaInputStruct = mvaWeightsStruct_;
        
        mvaWeightsReader_->AddVariable("jetChargeDiff", &mvaInputStruct.jetChargeDiff_);
        
        mvaWeightsReader_->AddVariable("meanDeltaPhi_b_met", &mvaInputStruct.meanDeltaPhi_b_met_);
        mvaWeightsReader_->AddVariable("massDiff_recoil_bbbar", &mvaInputStruct.massDiff_recoil_bbbar_);
        mvaWeightsReader_->AddVariable("pt_b_antiLepton", &mvaInputStruct.pt_b_antiLepton_);
        mvaWeightsReader_->AddVariable("pt_antiB_lepton", &mvaInputStruct.pt_antiB_lepton_);
        mvaWeightsReader_->AddVariable("deltaR_b_antiLepton", &mvaInputStruct.deltaR_b_antiLepton_);
        mvaWeightsReader_->AddVariable("deltaR_antiB_lepton", &mvaInputStruct.deltaR_antiB_lepton_);
        mvaWeightsReader_->AddVariable("btagDiscriminatorSum", &mvaInputStruct.btagDiscriminatorSum_);
        mvaWeightsReader_->AddVariable("deltaPhi_antiBLepton_bAntiLepton", &mvaInputStruct.deltaPhi_antiBLepton_bAntiLepton_);
        mvaWeightsReader_->AddVariable("massDiff_fullBLepton_bbbar", &mvaInputStruct.massDiff_fullBLepton_bbbar_);
        mvaWeightsReader_->AddVariable("meanMt_b_met", &mvaInputStruct.meanMt_b_met_);
        mvaWeightsReader_->AddVariable("massSum_antiBLepton_bAntiLepton", &mvaInputStruct.massSum_antiBLepton_bAntiLepton_);
        mvaWeightsReader_->AddVariable("massDiff_antiBLepton_bAntiLepton", &mvaInputStruct.massDiff_antiBLepton_bAntiLepton_);

        mvaWeightsReader_->AddSpectator("bQuarkRecoJetMatched", &mvaInputStruct.bQuarkRecoJetMatched_);
        mvaWeightsReader_->AddSpectator("correctCombination", &mvaInputStruct.correctCombination_);
        mvaWeightsReader_->AddSpectator("swappedCombination", &mvaInputStruct.swappedCombination_);

        // FIXME: what is first argument, should it be "BDTG" or "BDT method" ???
        mvaWeightsReader_->BookMVA("BDT method", mvaWeightsFile);
    }
    
    std::cout<<"=== Finishing setting up MVA weights from file\n\n";
}



void MvaInputTopJetsVariables::fillForInputProduction(const RecoObjects& recoObjects,
                                                      const tth::GenObjectIndices& genObjectIndices,
                                                      const tth::RecoObjectIndices& recoObjectIndices,
                                                      const double& weight,
                                                      const TString& selectionStep)
{
    // Check if step exists
    if(std::find(selectionSteps_.begin(), selectionSteps_.end(), selectionStep) == selectionSteps_.end()) return;
    
    // FIXME: which events exactly to fill? For now all with at least 4 jets
    const int numberOfJets = recoObjectIndices.jetIndices_.size();
    if(numberOfJets<4) return;
    
    // Loop over all jet combinations and get MVA input variables
    const std::vector<MvaInputTopJetsVariables::Input>& v_mvaInput =
        MvaInputTopJetsVariables::fillInputStructs(recoObjectIndices, genObjectIndices, recoObjects, weight);
    
    // Fill the MVA TTree
    this->addEntries(v_mvaInput);
}



void MvaInputTopJetsVariables::addEntries(const std::vector<Input>& v_input)
{
    v_inputStruct_.insert(v_inputStruct_.end(), v_input. begin(), v_input.end());
}



void MvaInputTopJetsVariables::addEntries(const std::vector<MvaInputTopJetsVariables::Input>& v_input,
                                          const std::vector<float>& weightsCorrect, const std::vector<float>& weightsSwapped)
{
    float maxWeightCorrect(-999.F);
    for(const float weight : weightsCorrect){
        if(weight > maxWeightCorrect) maxWeightCorrect = weight;
    }
    
    float maxWeightSwapped(-999.F);
    for(const float weight : weightsSwapped){
        if(weight > maxWeightSwapped) maxWeightSwapped = weight;
    }
    
    for(size_t i = 0; i < v_input.size(); ++i){
        Input input = v_input.at(i);
        input.setMvaWeights(weightsCorrect.at(i), weightsSwapped.at(i));
        if(i==0){
            input.bestMvaWeightCorrect_ = maxWeightCorrect;
            input.bestMvaWeightSwapped_ = maxWeightSwapped;
        }
        v_inputStruct_.push_back(input);
    }
}



void MvaInputTopJetsVariables::createMvaInputBranches(TTree* tree)
{
    t_mvaInput_ = tree;
    
    t_mvaInput_->Branch("eventWeight", &inputStruct_.eventWeight_, "eventWeight/F");
    
    t_mvaInput_->Branch("mvaWeightCorrect", &inputStruct_.mvaWeightCorrect_, "mvaWeightCorrect/F");
    t_mvaInput_->Branch("mvaWeightSwapped", &inputStruct_.mvaWeightSwapped_, "mvaWeightSwapped/F");
    t_mvaInput_->Branch("bestMvaWeightCorrect", &inputStruct_.bestMvaWeightCorrect_, "bestMvaWeightCorrect/F");
    t_mvaInput_->Branch("bestMvaWeightSwapped", &inputStruct_.bestMvaWeightSwapped_, "bestMvaWeightSwapped/F");
    
    t_mvaInput_->Branch("bQuarkRecoJetMatched", &inputStruct_.bQuarkRecoJetMatched_, "bQuarkRecoJetMatched/I");
    t_mvaInput_->Branch("correctCombination", &inputStruct_.correctCombination_, "correctCombination/I");
    t_mvaInput_->Branch("swappedCombination", &inputStruct_.swappedCombination_, "swappedCombination/I");
    
    t_mvaInput_->Branch("jetChargeDiff", &inputStruct_.jetChargeDiff_, "jetChargeDiff/F");
    
    t_mvaInput_->Branch("meanDeltaPhi_b_met", &inputStruct_.meanDeltaPhi_b_met_, "meanDeltaPhi_b_met/F");
    t_mvaInput_->Branch("massDiff_recoil_bbbar", &inputStruct_.massDiff_recoil_bbbar_, "massDiff_recoil_bbbar/F");
    t_mvaInput_->Branch("pt_b_antiLepton", &inputStruct_.pt_b_antiLepton_, "pt_b_antiLepton/F");
    t_mvaInput_->Branch("pt_antiB_lepton", &inputStruct_.pt_antiB_lepton_, "pt_antiB_lepton/F");
    t_mvaInput_->Branch("deltaR_b_antiLepton", &inputStruct_.deltaR_b_antiLepton_, "deltaR_b_antiLepton/F");
    t_mvaInput_->Branch("deltaR_antiB_lepton", &inputStruct_.deltaR_antiB_lepton_, "deltaR_antiB_lepton/F");
    t_mvaInput_->Branch("btagDiscriminatorSum", &inputStruct_.btagDiscriminatorSum_, "btagDiscriminatorSum/F");
    t_mvaInput_->Branch("deltaPhi_antiBLepton_bAntiLepton", &inputStruct_.deltaPhi_antiBLepton_bAntiLepton_, "deltaPhi_antiBLepton_bAntiLepton/F");
    t_mvaInput_->Branch("massDiff_fullBLepton_bbbar", &inputStruct_.massDiff_fullBLepton_bbbar_, "massDiff_fullBLepton_bbbar/F");
    t_mvaInput_->Branch("meanMt_b_met", &inputStruct_.meanMt_b_met_, "meanMt_b_met/F");
    t_mvaInput_->Branch("massSum_antiBLepton_bAntiLepton", &inputStruct_.massSum_antiBLepton_bAntiLepton_, "massSum_antiBLepton_bAntiLepton/F");
    t_mvaInput_->Branch("massDiff_antiBLepton_bAntiLepton", &inputStruct_.massDiff_antiBLepton_bAntiLepton_, "massDiff_antiBLepton_bAntiLepton/F");
}



std::vector<MvaInputTopJetsVariables::Input> MvaInputTopJetsVariables::fillInputStructs(const tth::RecoObjectIndices& recoObjectIndices,
                                                                                        const tth::GenObjectIndices& genObjectIndices,
                                                                                        const RecoObjects& recoObjects,
                                                                                        const double& eventWeight)
{
    std::vector<MvaInputTopJetsVariables::Input> result;
    
    // Access relevant objects and indices
    const VLV& allLeptons(*recoObjects.allLeptons_);
    const VLV& jets(*recoObjects.jets_);
    const LV& met(*recoObjects.met_);
    const std::vector<double>& jetBtag(*recoObjects.jetBTagCSV_);
    const std::vector<double>& jetCharge(*recoObjects.jetChargeRelativePtWeighted_);
    
    const LV& lepton(allLeptons.at(recoObjectIndices.leptonIndex_));
    const LV& antiLepton(allLeptons.at(recoObjectIndices.antiLeptonIndex_));
    
    const int& matchedBjetFromTopIndex = genObjectIndices.recoBjetFromTopIndex_;
    const int& matchedAntiBjetFromTopIndex = genObjectIndices.recoAntiBjetFromTopIndex_;
    const bool& successfulTopMatching = genObjectIndices.uniqueRecoTopMatching();
    
    const tth::IndexPairs& jetIndexPairs = recoObjectIndices.jetIndexPairs_;
    
    // Calculate the jet recoil for each jet pair, and put it in a vector of same size
    const VLV& jetRecoils = MvaInputTopJetsVariables::recoilForJetPairs(jetIndexPairs, recoObjectIndices.jetIndices_, jets);
    
    
    // Loop over all jet pairs
    for(size_t iJetIndexPairs = 0; iJetIndexPairs < jetIndexPairs.size(); ++iJetIndexPairs){

        // Get the indices of b and anti-b jet defined by jet charge
        const int antiBIndex = jetIndexPairs.at(iJetIndexPairs).first;
        const int bIndex = jetIndexPairs.at(iJetIndexPairs).second;
        
        // Check whether the two jets correspond to the b's from tops, and if the two are correct or swapped
        bool isSwappedPair(false);
        bool isCorrectPair(false);
        if(successfulTopMatching){
            if(matchedBjetFromTopIndex==bIndex && matchedAntiBjetFromTopIndex==antiBIndex){
                isCorrectPair = true;
            }
            else if(matchedBjetFromTopIndex==antiBIndex && matchedAntiBjetFromTopIndex==bIndex){
                isSwappedPair = true;
            }
        }
        
        // Variables for MVA
        const LV& bjet = jets.at(bIndex);
        const LV& antiBjet = jets.at(antiBIndex);
        const double& bjetBtagDiscriminator = jetBtag.at(bIndex);
        const double& antiBjetBtagDiscriminator = jetBtag.at(antiBIndex);
        const double jetChargeDiff = jetCharge.at(antiBIndex) - jetCharge.at(bIndex);
        if(jetChargeDiff<0. || jetChargeDiff>2.){
            std::cerr<<"ERROR! Difference in jet charge is (value = "<<jetChargeDiff
                     <<"), but definition allows only values in [0,2]\n...break\n"<<std::endl;
            exit(555);
        }
        const LV& jetRecoil = jetRecoils.at(iJetIndexPairs);

        const MvaInputTopJetsVariables::Input mvaInput(lepton, antiLepton,
                                                       bjet, antiBjet,
                                                       bjetBtagDiscriminator, antiBjetBtagDiscriminator,
                                                       jetChargeDiff,
                                                       jetRecoil, met,
                                                       successfulTopMatching,
                                                       isCorrectPair, isSwappedPair,
                                                       eventWeight);

        result.push_back(mvaInput);
    }
    
    
   return result; 
}



std::vector<MvaInputTopJetsVariables::Input> MvaInputTopJetsVariables::inputStructs()const
{
    return v_inputStruct_;
}



void MvaInputTopJetsVariables::clear()
{
    v_inputStruct_.clear();
    t_mvaInput_ = 0;
    selectorList_ = 0;
    m_plotStruct_.clear();
    m_plotStruct2D_.clear();
    if(mvaWeightsReader_){
        mvaWeightsReader_->Clear();
        mvaWeightsReader_->Delete();
    }
}



void MvaInputTopJetsVariables::fillMvaInputBranches()
{
    for(const auto& inputStruct : v_inputStruct_){
        inputStruct_ = inputStruct;
        t_mvaInput_->Fill();
    }
}



void MvaInputTopJetsVariables::produceMvaInputTree(const std::string& outputFilename,
                                                   const Channel::Channel& channel, const Systematic::Systematic& systematic)
{
    // Create output file for MVA tree
    std::string f_savename = static_cast<std::string>(ttbar::assignFolder(mvaInputDir_, channel, systematic));
    f_savename.append(outputFilename);
    TFile outputFile(f_savename.c_str(),"RECREATE");
    std::cout<<"\nOutput file for MVA input tree: "<<f_savename<<"\n";
    
    // Produce MVA input TTree and store it in output
    TSelectorList* output = new TSelectorList();
    this->produceMvaInputTree(output);
    
    // Write file and cleanup
    TIterator* it = output->MakeIterator();
    while(TObject* obj = it->Next()){
        obj->Write();
    }
    outputFile.Close();
    output->SetOwner();
    output->Clear();
}



void MvaInputTopJetsVariables::produceMvaInputTree(TSelectorList* output)
{
    std::cout<<"--- Beginning production of MVA input tree\n";
    
    // Set pointer to output, so that TTree is owned by it
    selectorList_ = output;
    
    // TTree for MVA input
    TTree* tree(0);
    tree = store(new TTree("mvaInputTopJets", "mvaInputTopJets"));
    //tree = dynamic_cast<TTree*>(output->FindObject("mvaInputTopJets"));
    
    // Create branches and fill tree
    this->createMvaInputBranches(tree);
    this->fillMvaInputBranches();
    
    std::cout<<"Number of dijet combinations for MVA: "<<this->inputStructs().size()<<"\n";
    std::cout<<"=== Finishing production of MVA input tree\n\n";
}



void MvaInputTopJetsVariables::mvaInputVariablesControlPlots(const std::string& f_savename)
{
    // Output file
    TFile outputFile(f_savename.c_str(),"RECREATE");
    std::cout<<"\nOutput file for MVA input control plots: "<<f_savename<<"\n";
    
    // Produce MVA input control plots and store them in output
    TSelectorList* output = new TSelectorList();
    this->mvaInputVariablesControlPlots(output);
    
    // Write file and cleanup
    TIterator* it = output->MakeIterator();
    while(TObject* obj = it->Next()){
        obj->Write();
    }
    outputFile.Close();
    output->SetOwner();
    output->Clear();
}



void MvaInputTopJetsVariables::mvaInputVariablesControlPlots(TSelectorList* output)
{
    std::cout<<"--- Beginning control plots for MVA variables\n";
    
    // Set pointer to output, so that histograms are owned by it
    selectorList_ = output;
    
    // Book histograms concerning MVA
    TH1* h_trueStatus_step8 = store(new TH1D("trueStatus_step8", "True status of matched jets;Status;# jet pairs",2,0,2));
    h_trueStatus_step8->GetXaxis()->SetBinLabel(1, "swapped");
    h_trueStatus_step8->GetXaxis()->SetBinLabel(2, "correct");
    
    this->bookHistograms("jetChargeDiff_step8", "jetChargeDiff_step8;#Deltac_{rel}^{jet};# jet pairs",50,0,2);
    
    this->bookHistograms("meanDeltaPhi_b_met_step8", "meanDeltaPhi_b_met;0.5(|#Delta#phi(b,MET)|+|#Delta#phi(#bar{b},MET)|)  [rad];# jet pairs",20,0,3.2);
    this->bookHistograms("massDiff_recoil_bbbar_step8", "massDiff_recoil_Bbbar; m_{recoil}^{jets}-m^{b#bar{b}}  [GeV];# jet pairs",16,-600,600);
    this->bookHistograms("pt_b_antiLepton_step8", "pt_b_antiLepton; p_{T}^{bl^{+}}  [GeV];# jet pairs",20,0,500);
    this->bookHistograms("pt_antiB_lepton_step8", "pt_antiB_lepton; p_{T}^{#bar{b}l^{-}}  [GeV];# jet pairs",20,0,500);
    this->bookHistograms("deltaR_b_antiLepton_step8", "deltaR_b_antiLepton; #DeltaR(b,l^{+});# jet pairs",25,0,5);
    this->bookHistograms("deltaR_antiB_lepton_step8", "deltaR_antiB_lepton; #DeltaR(#bar{b},l^{-});# jet pairs",25,0,5);
    this->bookHistograms("btagDiscriminatorSum_step8", "btagDiscriminatorSum; d^{b}+d^{#bar{b}};# jet pairs",20,0,2);
    this->bookHistograms("deltaPhi_antiBLepton_bAntiLepton_step8", "deltaPhi_antiBLepton_bAntiLepton; |#Delta#phi(bl^{+},#bar{b}l^{-})|  [rad];# jet pairs",10,0,3.2);
    this->bookHistograms("massDiff_fullBLepton_bbbar_step8", "massDiff_fullBLepton_bbbar; m^{b#bar{b}l^{+}l^{-}}-m^{b#bar{b}}  [GeV];# jet pairs",13,0,1050);
    this->bookHistograms("meanMt_b_met_step8", "meanMt_b_met; 0.5(m_{T}^{b,MET}+m_{T}^{#bar{b},MET)}  [GeV];# jet pairs",21,0,630);
    this->bookHistograms("massSum_antiBLepton_bAntiLepton_step8", "massSum_antiBLepton_bAntiLepton; m^{#bar{b}l^{-}}+m^{bl^{+}}  [GeV];# jet pairs",21,0,840);
    this->bookHistograms("massDiff_antiBLepton_bAntiLepton_step8", "massDiff_antiBLepton_bAntiLepton; m^{#bar{b}l^{-}}-m^{bl^{+}}  [GeV];# jet pairs",41,-400,420);
    
    this->bookHistograms("dijet_mvaWeightCorrect_step8", "dijet MVA weight correct;w_{MVA}^{correct};# jet pairs", 80, -1.2, 0.2);
    this->bookHistograms("dijet_bestMvaWeightCorrect_step8", "dijet best MVA weight correct;w_{MVA,1}^{correct};# events", 80, -1.2, 0.2);
    this->bookHistograms("dijet_mvaWeightSwapped_step8", "dijet MVA weight swapped;w_{MVA}^{swapped};# jet pairs", 80, -1.2, 0.2);
    this->bookHistograms("dijet_bestMvaWeightSwapped_step8", "dijet best MVA weight swapped;w_{MVA,1}^{swapped};# events", 80, -1.2, 0.2);
    
    this->bookHistograms2D("dijet_mvaWeightCorrectVsSwapped_step8", "dijet MVA weight correct vs. swapped;w_{MVA}^{correct};w_{MVA}^{swapped}", 40, -1.2, 0.2, 40, -1.2, 0.2);
    this->bookHistograms2D("dijet_bestMvaWeightCorrectVsSwapped_step8", "dijet best MVA weight correct vs. swapped;w_{MVA,1}^{correct};w_{MVA,1}^{swapped}", 40, -1.2, 0.2, 40, -1.2, 0.2);
    
    // Fill histograms
    for(const auto& mvaInputTopJetsStruct : this->inputStructs()){
        //const bool bQuarkRecoJetMatched = mvaInputTopJetsStruct.bQuarkRecoJetMatched_;
        const double eventWeight(mvaInputTopJetsStruct.eventWeight_);
        if(mvaInputTopJetsStruct.swappedCombination_)h_trueStatus_step8->Fill(0.1, eventWeight);
        if(mvaInputTopJetsStruct.correctCombination_)h_trueStatus_step8->Fill(1.1, eventWeight);
        
        this->fillHistograms("jetChargeDiff_step8", mvaInputTopJetsStruct.jetChargeDiff_, mvaInputTopJetsStruct);
        
        this->fillHistograms("meanDeltaPhi_b_met_step8", mvaInputTopJetsStruct.meanDeltaPhi_b_met_, mvaInputTopJetsStruct);
        this->fillHistograms("massDiff_recoil_bbbar_step8", mvaInputTopJetsStruct.massDiff_recoil_bbbar_, mvaInputTopJetsStruct);
        this->fillHistograms("pt_b_antiLepton_step8", mvaInputTopJetsStruct.pt_b_antiLepton_, mvaInputTopJetsStruct);
        this->fillHistograms("pt_antiB_lepton_step8", mvaInputTopJetsStruct.pt_antiB_lepton_, mvaInputTopJetsStruct);
        this->fillHistograms("deltaR_b_antiLepton_step8", mvaInputTopJetsStruct.deltaR_b_antiLepton_, mvaInputTopJetsStruct);
        this->fillHistograms("deltaR_antiB_lepton_step8", mvaInputTopJetsStruct.deltaR_antiB_lepton_, mvaInputTopJetsStruct);
        this->fillHistograms("btagDiscriminatorSum_step8", mvaInputTopJetsStruct.btagDiscriminatorSum_, mvaInputTopJetsStruct);
        this->fillHistograms("deltaPhi_antiBLepton_bAntiLepton_step8", mvaInputTopJetsStruct.deltaPhi_antiBLepton_bAntiLepton_, mvaInputTopJetsStruct);
        this->fillHistograms("massDiff_fullBLepton_bbbar_step8", mvaInputTopJetsStruct.massDiff_fullBLepton_bbbar_, mvaInputTopJetsStruct);
        this->fillHistograms("meanMt_b_met_step8", mvaInputTopJetsStruct.meanMt_b_met_, mvaInputTopJetsStruct);
        this->fillHistograms("massSum_antiBLepton_bAntiLepton_step8", mvaInputTopJetsStruct.massSum_antiBLepton_bAntiLepton_, mvaInputTopJetsStruct);
        this->fillHistograms("massDiff_antiBLepton_bAntiLepton_step8", mvaInputTopJetsStruct.massDiff_antiBLepton_bAntiLepton_, mvaInputTopJetsStruct);
        
        this->fillHistograms("dijet_mvaWeightCorrect_step8", mvaInputTopJetsStruct.mvaWeightCorrect_, mvaInputTopJetsStruct);
        if(mvaInputTopJetsStruct.bestMvaWeightCorrect_>-990.) this->fillHistograms("dijet_bestMvaWeightCorrect_step8", mvaInputTopJetsStruct.bestMvaWeightCorrect_, mvaInputTopJetsStruct);
        this->fillHistograms("dijet_mvaWeightSwapped_step8", mvaInputTopJetsStruct.mvaWeightSwapped_, mvaInputTopJetsStruct);
        if(mvaInputTopJetsStruct.bestMvaWeightSwapped_>-990.) this->fillHistograms("dijet_bestMvaWeightSwapped_step8", mvaInputTopJetsStruct.bestMvaWeightSwapped_, mvaInputTopJetsStruct);
        
        this->fillHistograms2D("dijet_mvaWeightCorrectVsSwapped_step8", mvaInputTopJetsStruct.mvaWeightCorrect_, mvaInputTopJetsStruct.mvaWeightSwapped_, mvaInputTopJetsStruct);
        if(mvaInputTopJetsStruct.bestMvaWeightCorrect_>-990. && mvaInputTopJetsStruct.bestMvaWeightSwapped_>-990.)
            this->fillHistograms2D("dijet_bestMvaWeightCorrectVsSwapped_step8", mvaInputTopJetsStruct.bestMvaWeightCorrect_, mvaInputTopJetsStruct.bestMvaWeightSwapped_, mvaInputTopJetsStruct);
    }
    
    std::cout<<"=== Finishing control plots for MVA variables\n\n";
}



void MvaInputTopJetsVariables::importTree(const std::string& f_savename, const std::string& treeName)
{
    std::cout<<"--- Beginning import of TTree for MVA variables\n";
    
    TFile* inputFile = TFile::Open(f_savename.c_str());
    if(inputFile->IsZombie()){
        std::cerr<<"ERROR! Cannot open input file to import TTree, filename is: "<<f_savename<<"\n...break\n"<<std::endl;
        exit(77);
    }
    
    TTree* tree(0);
    tree = dynamic_cast<TTree*>(inputFile->Get(treeName.c_str()));
    if (!tree){
        std::cerr << "ERROR: TTree not found in file, tree name is: "<<treeName<<"\n...break\n"<<std::endl;
        exit(78);
    }
    
    this->importBranches(tree);
    
    tree = 0;
    inputFile->Close();
    std::cout<<"\nNUMBER: "<<v_inputStruct_.size()<<"\n\n";
    std::cout<<"=== Finishing import of TTree for MVA variables\n\n";
}



void MvaInputTopJetsVariables::importBranches(TTree* tree)
{
    // Set up variables struct and branches
    Input mvaInputStruct;
    
    TBranch* b_eventWeight(0);
    
    TBranch* b_mvaWeightCorrect(0);
    TBranch* b_mvaWeightSwapped(0);
    TBranch* b_bestMvaWeightCorrect(0);
    TBranch* b_bestMvaWeightSwapped(0);
    
    TBranch* b_bQuarkRecoJetMatched(0);
    TBranch* b_correctCombination(0);
    TBranch* b_swappedCombination(0);
    
    TBranch* b_jetChargeDiff(0);
    
    TBranch* b_meanDeltaPhi_b_met(0);
    TBranch* b_massDiff_recoil_bbbar(0);
    TBranch* b_pt_b_antiLepton(0);
    TBranch* b_pt_antiB_lepton(0);
    TBranch* b_deltaR_b_antiLepton(0);
    TBranch* b_deltaR_antiB_lepton(0);
    TBranch* b_btagDiscriminatorSum(0);
    TBranch* b_deltaPhi_antiBLepton_bAntiLepton(0);
    TBranch* b_massDiff_fullBLepton_bbbar(0);
    TBranch* b_meanMt_b_met(0);
    TBranch* b_massSum_antiBLepton_bAntiLepton(0);
    TBranch* b_massDiff_antiBLepton_bAntiLepton(0);
    
    // Set branch addresses
    tree->SetBranchAddress("eventWeight", &mvaInputStruct.eventWeight_, &b_eventWeight);
    
    tree->SetBranchAddress("mvaWeightCorrect", &mvaInputStruct.mvaWeightCorrect_, &b_mvaWeightCorrect);
    tree->SetBranchAddress("mvaWeightSwapped", &mvaInputStruct.mvaWeightSwapped_, &b_mvaWeightSwapped);
    tree->SetBranchAddress("bestMvaWeightCorrect", &mvaInputStruct.bestMvaWeightCorrect_, &b_bestMvaWeightCorrect);
    tree->SetBranchAddress("bestMvaWeightSwapped", &mvaInputStruct.bestMvaWeightSwapped_, &b_bestMvaWeightSwapped);
    
    tree->SetBranchAddress("bQuarkRecoJetMatched", &mvaInputStruct.bQuarkRecoJetMatched_, &b_bQuarkRecoJetMatched);
    tree->SetBranchAddress("correctCombination", &mvaInputStruct.correctCombination_, &b_correctCombination);
    tree->SetBranchAddress("swappedCombination", &mvaInputStruct.swappedCombination_, &b_swappedCombination);
    
    tree->SetBranchAddress("jetChargeDiff", &mvaInputStruct.jetChargeDiff_, &b_jetChargeDiff);
    
    tree->SetBranchAddress("meanDeltaPhi_b_met", &mvaInputStruct.meanDeltaPhi_b_met_, &b_meanDeltaPhi_b_met);
    tree->SetBranchAddress("massDiff_recoil_bbbar", &mvaInputStruct.massDiff_recoil_bbbar_, &b_massDiff_recoil_bbbar);
    tree->SetBranchAddress("pt_b_antiLepton", &mvaInputStruct.pt_b_antiLepton_, &b_pt_b_antiLepton);
    tree->SetBranchAddress("pt_antiB_lepton", &mvaInputStruct.pt_antiB_lepton_, &b_pt_antiB_lepton);
    tree->SetBranchAddress("deltaR_b_antiLepton", &mvaInputStruct.deltaR_b_antiLepton_, &b_deltaR_b_antiLepton);
    tree->SetBranchAddress("deltaR_antiB_lepton", &mvaInputStruct.deltaR_antiB_lepton_, &b_deltaR_antiB_lepton);
    tree->SetBranchAddress("btagDiscriminatorSum", &mvaInputStruct.btagDiscriminatorSum_, &b_btagDiscriminatorSum);
    tree->SetBranchAddress("deltaPhi_antiBLepton_bAntiLepton", &mvaInputStruct.deltaPhi_antiBLepton_bAntiLepton_, &b_deltaPhi_antiBLepton_bAntiLepton);
    tree->SetBranchAddress("massDiff_fullBLepton_bbbar", &mvaInputStruct.massDiff_fullBLepton_bbbar_, &b_massDiff_fullBLepton_bbbar);
    tree->SetBranchAddress("meanMt_b_met", &mvaInputStruct.meanMt_b_met_, &b_meanMt_b_met);
    tree->SetBranchAddress("massSum_antiBLepton_bAntiLepton", &mvaInputStruct.massSum_antiBLepton_bAntiLepton_, &b_massSum_antiBLepton_bAntiLepton);
    tree->SetBranchAddress("massDiff_antiBLepton_bAntiLepton", &mvaInputStruct.massDiff_antiBLepton_bAntiLepton_, &b_massDiff_antiBLepton_bAntiLepton);
    
    // Loop over all tree entries and fill vector of structs
    v_inputStruct_.clear();
    for(Long64_t iEntry = 0; iEntry < tree->GetEntries(); ++iEntry){
        tree->GetEntry(iEntry);
        v_inputStruct_.push_back(mvaInputStruct);
    }
}



void MvaInputTopJetsVariables::bookHistograms(const TString& name, const TString& title,
                                              const int nBin, const double xMin, const double xMax)
{
    // Check if histograms with given name already exist
    if(m_plotStruct_.find(name) != m_plotStruct_.end()){
        std::cerr<<"ERROR! Trial of booking already existing histogram with name: "<<name
                 <<"\n...break\n"<<std::endl;
        exit(876);
    }
    
    const TString nameCorrect("correct_" + name);
    const TString nameSwapped("swapped_" + name);
    const TString nameWrong("wrong_" + name);
    
    // Book histograms
    PlotStruct plotStruct;
    plotStruct.h_correctCombination = store(new TH1D(nameCorrect, title, nBin, xMin, xMax));
    plotStruct.h_swappedCombination = store(new TH1D(nameSwapped, title, nBin, xMin, xMax));
    plotStruct.h_wrongCombinations = store(new TH1D(nameWrong, title, nBin, xMin, xMax));
    plotStruct.h_allCombinations = store(new TH1D(name, title, nBin, xMin, xMax));
    m_plotStruct_[name] = plotStruct;
}



void MvaInputTopJetsVariables::bookHistograms2D(const TString& name, const TString& title, const int nBinX, const double xMin, const double xMax, const int nBinY, const double yMin, const double yMax)
{
    // Check if histograms with given name already exist
    if(m_plotStruct2D_.find(name) != m_plotStruct2D_.end()){
        std::cerr<<"ERROR! Trial of booking already existing histogram with name: "<<name
                 <<"\n...break\n"<<std::endl;
        exit(876);
    }
    
    const TString nameCorrect("correct_" + name);
    const TString nameSwapped("swapped_" + name);
    const TString nameWrong("wrong_" + name);
    
    // Book histograms
    PlotStruct2D plotStruct;
    plotStruct.h_correctCombination = store(new TH2D(nameCorrect, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    plotStruct.h_swappedCombination = store(new TH2D(nameSwapped, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    plotStruct.h_wrongCombinations = store(new TH2D(nameWrong, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    plotStruct.h_allCombinations = store(new TH2D(name, title, nBinX, xMin, xMax, nBinY, yMin, yMax));
    m_plotStruct2D_[name] = plotStruct;
}



void MvaInputTopJetsVariables::fillHistograms(const TString& name, const double& variable, const MvaInputTopJetsVariables::Input& mvaInputTopJetsStruct)
{
    // Check if histograms with given name already exist
    if(m_plotStruct_.find(name) == m_plotStruct_.end()){
        std::cerr<<"ERROR! Trial of filling non-existing histogram with name: "<<name
                 <<"\n...break\n"<<std::endl;
        exit(876);
    }
    PlotStruct& plotStruct = m_plotStruct_.at(name);
    
    // Access relevant information
    const double& eventWeight(mvaInputTopJetsStruct.eventWeight_);
    const bool correctCombination(mvaInputTopJetsStruct.correctCombination_);
    const bool swappedCombination(mvaInputTopJetsStruct.swappedCombination_);
    
    // Fill histograms
    if(correctCombination) plotStruct.h_correctCombination->Fill(variable, eventWeight);
    else if(swappedCombination) plotStruct.h_swappedCombination->Fill(variable, eventWeight);
    else plotStruct.h_wrongCombinations->Fill(variable, eventWeight);
    plotStruct.h_allCombinations->Fill(variable, eventWeight);
}



void MvaInputTopJetsVariables::fillHistograms2D(const TString& name, const double& variable1, const double& variable2, const MvaInputTopJetsVariables::Input& mvaInputTopJetsStruct)
{
    // Check if histograms with given name already exist
    if(m_plotStruct2D_.find(name) == m_plotStruct2D_.end()){
        std::cerr<<"ERROR! Trial of filling non-existing histogram with name: "<<name
                 <<"\n...break\n"<<std::endl;
        exit(876);
    }
    PlotStruct2D& plotStruct = m_plotStruct2D_.at(name);
    
    // Access relevant information
    const double& eventWeight(mvaInputTopJetsStruct.eventWeight_);
    const bool correctCombination(mvaInputTopJetsStruct.correctCombination_);
    const bool swappedCombination(mvaInputTopJetsStruct.swappedCombination_);
    
    // Fill histograms
    if(correctCombination) plotStruct.h_correctCombination->Fill(variable1, variable2, eventWeight);
    else if(swappedCombination) plotStruct.h_swappedCombination->Fill(variable1, variable2, eventWeight);
    else plotStruct.h_wrongCombinations->Fill(variable1, variable2, eventWeight);
    plotStruct.h_allCombinations->Fill(variable1, variable2, eventWeight);
}



std::vector<float> MvaInputTopJetsVariables::mvaWeights(const std::vector<MvaInputTopJetsVariables::Input>& v_input)
{
    std::vector<float> result;
    
    for(const Input& input : v_input){
        if(!mvaWeightsReader_){
            result.push_back(1.);
            continue;
        }
        mvaWeightsStruct_ = input;
        const float weight = mvaWeightsReader_->EvaluateMVA("BDT method");
        result.push_back(weight);
    }
    
    return result;
}



void MvaInputTopJetsVariables::runMva(const char* outputDir, const char* weightFileDir, const char* outputFileName,
                                      const char* methodName, const TCut& cutSignal, const TCut& cutBackground,
                                      TTree* treeTraining, TTree* treeTesting)
{
    // Get a TMVA instance
    TMVA::Tools::Instance();
    
    // Create a ROOT output file for TMVA
    TString mvaOutputFilename(outputDir);
    mvaOutputFilename.Append("/");
    gSystem->MakeDirectory(mvaOutputFilename);
    mvaOutputFilename.Append(outputFileName);
    TFile* outputFile = TFile::Open(mvaOutputFilename, "RECREATE");
    
    // Set the output directory for the weights (if not specified, default is "weights")
    TString mvaOutputWeightsFilename(outputDir);
    mvaOutputWeightsFilename.Append(weightFileDir);
    (TMVA::gConfig().GetIONames()).fWeightFileDir = mvaOutputWeightsFilename;
    
    // Create the factory
    TMVA::Factory* factory(0);
    factory = new TMVA::Factory( "MVA", outputFile, "!V:!Silent");
    
    // Set all branches of MVA input which should be used for training
    factory->AddVariable("jetChargeDiff", 'F');
    
    factory->AddVariable("meanDeltaPhi_b_met", 'F');
    factory->AddVariable("massDiff_recoil_bbbar", 'F');
    factory->AddVariable("pt_b_antiLepton", 'F');
    factory->AddVariable("pt_antiB_lepton", 'F');
    factory->AddVariable("deltaR_b_antiLepton", 'F');
    factory->AddVariable("deltaR_antiB_lepton", 'F');
    factory->AddVariable("btagDiscriminatorSum", 'F');
    factory->AddVariable("deltaPhi_antiBLepton_bAntiLepton", 'F');
    factory->AddVariable("massDiff_fullBLepton_bbbar", 'F');
    factory->AddVariable("meanMt_b_met", 'F');
    factory->AddVariable("massSum_antiBLepton_bAntiLepton", 'F');
    factory->AddVariable("massDiff_antiBLepton_bAntiLepton", 'F');
    
    // Set all branches of MVA input which should NOT be used for training,
    // but are needed otherwise (e.g. for defining separation cuts)
    factory->AddSpectator("bQuarkRecoJetMatched", 'I');
    factory->AddSpectator("correctCombination", 'I');
    factory->AddSpectator("swappedCombination", 'I');
    
    // Set global weights for individual input
    Double_t signalWeight = 1.;
    Double_t backgroundWeight = 1.;
    
    // Register the training trees
    factory->AddSignalTree(treeTraining, signalWeight, TMVA::Types::kTraining);
    factory->AddBackgroundTree(treeTraining, backgroundWeight, TMVA::Types::kTraining);
    
    // Register the testing trees
    factory->AddSignalTree(treeTesting, signalWeight, TMVA::Types::kTesting);
    factory->AddBackgroundTree(treeTesting, backgroundWeight, TMVA::Types::kTesting);
    
    // Set the branch from which the event weight is taken
    factory->SetSignalWeightExpression("eventWeight");
    factory->SetBackgroundWeightExpression("eventWeight");
    
    // Prepare the training and test trees
    factory->PrepareTrainingAndTestTree(cutSignal, cutBackground,
                                        "SplitMode=Block:SplitSeed=0:NormMode=NumEvents:!V" );
    
    // Book the MVA method (e.g. boosted decision tree with specific setup)
    factory->BookMethod(TMVA::Types::kBDT,
                        methodName,
                        "!H:!V:NTrees=600:nEventsMin=400:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.45:UseRandomisedTrees=False:UseNVars=13:nCuts=1000:PruneMethod=CostComplexity:PruneStrength=-1");
    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();
    
    // Cleanup
    outputFile->Close();
    delete factory;
}



VLV MvaInputTopJetsVariables::recoilForJetPairs(const tth::IndexPairs& jetIndexPairs,
                                     const std::vector<int>& jetIndices,
                                     const VLV& jets)
{
    VLV result;

    for(const auto& jetIndexPair : jetIndexPairs){
        const int antiBIndex = jetIndexPair.first;
        const int bIndex = jetIndexPair.second;

        LV jetRecoil;
        for(const int index : jetIndices){
            if(index == bIndex || index == antiBIndex) continue;
            jetRecoil += jets.at(index);
        }

        result.push_back(jetRecoil);
    }

    return result;
}









