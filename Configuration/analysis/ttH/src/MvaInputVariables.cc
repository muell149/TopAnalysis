#include <iostream>
#include <cmath>
#include <cstdlib>

#include <TTree.h>
#include <TSystem.h>
#include <TH1.h>
#include <TFile.h>
#include <Math/VectorUtil.h>
#include <TSelectorList.h>
#include <Rtypes.h>

#include "MvaInputVariables.h"








MvaInputTopJetsVariables::MvaInputTopJetsStruct::MvaInputTopJetsStruct():
bQuarkRecoJetMatched_(false),
correctCombination_(false),
swappedCombination_(false),
meanDeltaPhi_b_met_(-999.),
massDiff_recoil_bbbar_(-999.),
pt_b_antiLepton_(-999.),
pt_antiB_lepton_(-999.),
deltaR_b_antiLepton_(-999.),
deltaR_antiB_lepton_(-999.),
btagDiscriminatorSum_(-999.),
deltaPhi_antiBLepton_bAntiLepton_(-999.),
massDiff_fullBLepton_bbbar_(-999.),
meanMT_b_met_(-999.),
massSum_antiBLepton_bAntiLepton_(-999.),
massDiff_antiBLepton_bAntiLepton_(-999.),
meanMTAlt_b_met_(-999.)
{}




MvaInputTopJetsVariables::MvaInputTopJetsVariables():
selectorList_(0), t_mvaInput_(0)
{}



void MvaInputTopJetsVariables::addEntry(const LV& lepton, const LV& antiLepton,
                                        const LV& bJet, const LV& antiBJet,
                                        const double& bJetBtagDiscriminator, const double& antiBJetBtagDiscriminator,
                                        const double& jetChargeDiff,
                                        const LV& jetRecoil, const LV& met,
                                        const bool bQuarkRecoJetMatched, const bool correctCombination, const bool swappedCombination,
                                        const double& eventWeight)
{
    using ROOT::Math::VectorUtil::DeltaPhi;
    using ROOT::Math::VectorUtil::DeltaR;
    
    // Helper variables for MVA
    const LV bbbarSystem = bJet + antiBJet;
    const LV bAntiLeptonSystem = bJet + antiLepton;
    const LV antiBLeptonSystem = antiBJet + lepton;
    const LV fullBLeptonSystem = bAntiLeptonSystem + antiBLeptonSystem;
    
    // Fill the struct with the variables for MVA TTree
    MvaInputTopJetsStruct mvaInputTopJetsStruct;
    mvaInputTopJetsStruct.bQuarkRecoJetMatched_ = bQuarkRecoJetMatched;
    mvaInputTopJetsStruct.correctCombination_ = correctCombination;
    mvaInputTopJetsStruct.swappedCombination_ = swappedCombination;
    mvaInputTopJetsStruct.eventWeight_ = eventWeight;
    mvaInputTopJetsStruct.jetChargeDiff_ = jetChargeDiff;
    
    mvaInputTopJetsStruct.meanDeltaPhi_b_met_ = 0.5*(std::abs(DeltaPhi(bJet, met)) + std::abs(DeltaPhi(antiBJet, met)));
    mvaInputTopJetsStruct.massDiff_recoil_bbbar_ = jetRecoil.M() - bbbarSystem.M();
    mvaInputTopJetsStruct.pt_b_antiLepton_ = bAntiLeptonSystem.pt();
    mvaInputTopJetsStruct.pt_antiB_lepton_ = antiBLeptonSystem.pt();
    mvaInputTopJetsStruct.deltaR_b_antiLepton_ = DeltaR(bJet, antiLepton);
    mvaInputTopJetsStruct.deltaR_antiB_lepton_ = DeltaR(antiBJet, lepton);
    mvaInputTopJetsStruct.btagDiscriminatorSum_ = bJetBtagDiscriminator + antiBJetBtagDiscriminator;
    mvaInputTopJetsStruct.deltaPhi_antiBLepton_bAntiLepton_ = std::abs(DeltaPhi(antiBLeptonSystem, bAntiLeptonSystem));
    mvaInputTopJetsStruct.massDiff_fullBLepton_bbbar_ = fullBLeptonSystem.M() - bbbarSystem.M();
    mvaInputTopJetsStruct.meanMT_b_met_ = 0.5*((bJet + met).Mt() + (antiBJet + met).Mt());
    mvaInputTopJetsStruct.massSum_antiBLepton_bAntiLepton_ = antiBLeptonSystem.M() + bAntiLeptonSystem.M();
    mvaInputTopJetsStruct.massDiff_antiBLepton_bAntiLepton_ = antiBLeptonSystem.M() - bAntiLeptonSystem.M();
    
    mvaInputTopJetsStruct.meanMTAlt_b_met_ = 0.5*(std::sqrt(2.*bJet.Et()*(met.E())*(1.-std::cos(DeltaPhi(bJet, met))))
                                      + std::sqrt(2.*antiBJet.Et()*(met.E())*(1.-std::cos(DeltaPhi(antiBJet, met)))));
    
    v_mvaInputStruct_.push_back(mvaInputTopJetsStruct);
}



void MvaInputTopJetsVariables::createMvaInputBranches(TTree* tree)
{
    t_mvaInput_ = tree;
    
    t_mvaInput_->Branch("eventWeight", &mvaInputStruct_.eventWeight_, "eventWeight/D");
    
    t_mvaInput_->Branch("bQuarkRecoJetMatched", &mvaInputStruct_.bQuarkRecoJetMatched_, "bQuarkRecoJetMatched/O");
    t_mvaInput_->Branch("correctCombination", &mvaInputStruct_.correctCombination_, "correctCombination/O");
    t_mvaInput_->Branch("swappedCombination", &mvaInputStruct_.swappedCombination_, "swappedCombination/O");
    
    t_mvaInput_->Branch("jetChargeDiff", &mvaInputStruct_.jetChargeDiff_, "jetChargeDiff/D");
    
    t_mvaInput_->Branch("meanDeltaPhi_b_met", &mvaInputStruct_.meanDeltaPhi_b_met_, "meanDeltaPhi_b_met/D");
    t_mvaInput_->Branch("massDiff_recoil_bbbar", &mvaInputStruct_.massDiff_recoil_bbbar_, "massDiff_recoil_bbbar/D");
    t_mvaInput_->Branch("pt_b_antiLepton", &mvaInputStruct_.pt_b_antiLepton_, "pt_b_antiLepton/D");
    t_mvaInput_->Branch("pt_antiB_lepton", &mvaInputStruct_.pt_antiB_lepton_, "pt_antiB_lepton/D");
    t_mvaInput_->Branch("deltaR_b_antiLepton", &mvaInputStruct_.deltaR_b_antiLepton_, "deltaR_b_antiLepton/D");
    t_mvaInput_->Branch("deltaR_antiB_lepton", &mvaInputStruct_.deltaR_antiB_lepton_, "deltaR_antiB_lepton/D");
    t_mvaInput_->Branch("btagDiscriminatorSum", &mvaInputStruct_.btagDiscriminatorSum_, "btagDiscriminatorSum/D");
    t_mvaInput_->Branch("deltaPhi_antiBLepton_bAntiLepton", &mvaInputStruct_.deltaPhi_antiBLepton_bAntiLepton_, "deltaPhi_antiBLepton_bAntiLepton/D");
    t_mvaInput_->Branch("massDiff_fullBLepton_bbbar", &mvaInputStruct_.massDiff_fullBLepton_bbbar_, "massDiff_fullBLepton_bbbar/D");
    t_mvaInput_->Branch("meanMT_b_met", &mvaInputStruct_.meanMT_b_met_, "meanMT_b_met/D");
    t_mvaInput_->Branch("massSum_antiBLepton_bAntiLepton", &mvaInputStruct_.massSum_antiBLepton_bAntiLepton_, "massSum_antiBLepton_bAntiLepton/D");
    t_mvaInput_->Branch("massDiff_antiBLepton_bAntiLepton", &mvaInputStruct_.massDiff_antiBLepton_bAntiLepton_, "massDiff_antiBLepton_bAntiLepton/D");
    
    t_mvaInput_->Branch("meanMTAlt_b_met", &mvaInputStruct_.meanMTAlt_b_met_, "meanMTAlt_b_met/D");
}



std::vector<MvaInputTopJetsVariables::MvaInputTopJetsStruct> MvaInputTopJetsVariables::mvaInputStructs()const
{
    return v_mvaInputStruct_;
}



void MvaInputTopJetsVariables::clear()
{
    v_mvaInputStruct_.clear();
    t_mvaInput_ = 0;
    selectorList_ = 0;
}




void MvaInputTopJetsVariables::fillMvaInputBranches()
{
    for(const auto& mvaInputStruct : v_mvaInputStruct_){
        mvaInputStruct_ = mvaInputStruct;
        t_mvaInput_->Fill();
    }
}




void MvaInputTopJetsVariables::produceMvaInputTree(const std::string& f_savename)
{
    
    // Output file
    TFile outputFile(f_savename.c_str(),"RECREATE");
    std::cout<<"\nOutput file for MVA input tree: "<<f_savename<<"\n";
    
    // Produce MVA input TTree and store it in output
    TSelectorList* output = new TSelectorList();
    this->produceMvaInputTree(output);
    
    // Write file and cleanup
    TIterator* it = output->MakeIterator();
    while (TObject* obj = it->Next()) {
        obj->Write();
    }
    outputFile.Close();
    output->SetOwner();
    output->Clear();
}



void MvaInputTopJetsVariables::produceMvaInputTree(TSelectorList* output)
{
    std::cout<<"--- Beginning production MVA input tree\n";
    
    // Set pointer to output, so that TTree is owned by it
    selectorList_ = output;
    
    // TTree for MVA input
    TTree* tree(0);
    tree = store(new TTree("mvaInputTopJets", "mvaInputTopJets"));
    //tree = dynamic_cast<TTree*>(output->FindObject("mvaInputTopJets"));
    
    // Create branches and fill tree
    this->createMvaInputBranches(tree);
    this->fillMvaInputBranches();
    std::cout<<"Number of variables for MVA: "<<this->mvaInputStructs().size()<<"\n";
    std::cout<<"=== Finishing production MVA input tree\n\n";
}



void MvaInputTopJetsVariables::mvaInputTopJetsVariablesControlPlots(const std::string& f_savename)
{
    // Output file
    TFile outputFile(f_savename.c_str(),"RECREATE");
    std::cout<<"\nOutput file for MVA input control plots: "<<f_savename<<"\n";
    
    // Produce MVA input control plots and store them in output
    TSelectorList* output = new TSelectorList();
    this->mvaInputTopJetsVariablesControlPlots(output);
    
    // Write file and cleanup
    TIterator* it = output->MakeIterator();
    while (TObject* obj = it->Next()) {
        obj->Write();
    }
    outputFile.Close();
    output->SetOwner();
    output->Clear();
}



void MvaInputTopJetsVariables::mvaInputTopJetsVariablesControlPlots(TSelectorList* output)
{
    std::cout<<"--- Beginning control plots for MVA variables\n";
    
    // Set pointer to output, so that histograms are owned by it
    selectorList_ = output;
    
    // Book histograms concerning MVA
    TH1* h_trueStatus_step8 = store(new TH1D("trueStatus_step8", "True status of matched jets;Status;# jet pairs",2,0,2));
    h_trueStatus_step8->GetXaxis()->SetBinLabel(1, "swapped");
    h_trueStatus_step8->GetXaxis()->SetBinLabel(2, "correct");
    
    TH1* h_jetChargeDiff_step8 = store(new TH1D("jetChargeDiff_step8", "jetChargeDiff_step8;#Deltac_{jet};# jet pairs",50,0,2));
    
    TH1* h_meanDeltaPhi_b_met_step8 = store(new TH1D("meanDeltaPhi_b_met_step8", "meanDeltaPhi_b_met;0.5(|#Delta#phi(b,MET)|+|#Delta#phi(#bar{b},MET)|)  [rad];# jet pairs",20,0,3.2));
    TH1* h_massDiff_recoil_bbbar_step8 = store(new TH1D("massDiff_recoil_bbbar_step8", "massDiff_recoil_Bbbar; m_{jets}^{recoil}-m_{b#bar{b}}  [GeV];# jet pairs",16,-600,600));
    TH1* h_pt_b_antiLepton_step8 = store(new TH1D("pt_b_antiLepton_step8", "pt_b_antiLepton; p_{T}(b,l^{+})  [GeV];# jet pairs",20,0,500));
    TH1* h_pt_antiB_lepton_step8 = store(new TH1D("pt_antiB_lepton_step8", "pt_antiB_lepton; p_{T}(#bar{b},l^{-})  [GeV];# jet pairs",20,0,500));
    TH1* h_deltaR_b_antiLepton_step8 = store(new TH1D("deltaR_b_antiLepton_step8", "deltaR_b_antiLepton; #Delta{R}(b,l^{+});# jet pairs",25,0,5));
    TH1* h_deltaR_antiB_lepton_step8 = store(new TH1D("deltaR_antiB_lepton_step8", "deltaR_antiB_lepton; #Delta{R}(#bar{b},l^{-});# jet pairs",25,0,5));
    TH1* h_btagDiscriminatorSum_step8 = store(new TH1D("btagDiscriminatorSum_step8", "btagDiscriminatorSum; d(b)+d(#bar{b});# jet pairs",20,0,2));
    TH1* h_deltaPhi_antiBLepton_bAntiLepton_step8 = store(new TH1D("deltaPhi_antiBLepton_bAntiLepton_step8", "deltaPhi_antiBLepton_bAntiLepton; |#Delta#phi(bl^{+},#bar{b}l^{-})|  [rad];# jet pairs",10,0,3.2));
    TH1* h_massDiff_fullBLepton_bbbar_step8 = store(new TH1D("massDiff_fullBLepton_bbbar_step8", "massDiff_fullBLepton_bbbar; m_{b#bar{b}l^{+}l^{-}}-m_{b#bar{b}}  [GeV];# jet pairs",13,0,1050));
    TH1* h_meanMT_b_met_step8 = store(new TH1D("meanMT_b_met_step8", "meanMT_b_met; 0.5(m_{T}(b,MET)+m_{T}(#bar{b},MET))  [GeV];# jet pairs",21,0,420));
    TH1* h_massSum_antiBLepton_bAntiLepton_step8 = store(new TH1D("massSum_antiBLepton_bAntiLepton_step8", "massSum_antiBLepton_bAntiLepton; m_{#bar{b}l^{-}}+m_{bl^{+}}  [GeV];# jet pairs",21,0,840));
    TH1* h_massDiff_antiBLepton_bAntiLepton_step8 = store(new TH1D("massDiff_antiBLepton_bAntiLepton_step8", "massDiff_antiBLepton_bAntiLepton; m_{#bar{b}l^{-}}-m_{bl^{+}}  [GeV];# jet pairs",41,-400,420));
    
    TH1* h_meanMTAlt_b_met_step8 = store(new TH1D("meanMTAlt_b_met_step8", "meanMTAlt_b_met; 0.5(m_{T}(b,MET)+m_{T}(#bar{b},MET))  [GeV];# jet pairs",21,0,420));
    
    // Fill histograms
    for(const auto& mvaInputTopJetsStruct : this->mvaInputStructs()){
        //const bool bQuarkRecoJetMatched = mvaInputTopJetsStruct.bQuarkRecoJetMatched_;
        const double eventWeight(mvaInputTopJetsStruct.eventWeight_);
        if(mvaInputTopJetsStruct.swappedCombination_)h_trueStatus_step8->Fill(0.1, eventWeight);
        if(mvaInputTopJetsStruct.correctCombination_)h_trueStatus_step8->Fill(1.1, eventWeight);
        
        h_jetChargeDiff_step8->Fill(mvaInputTopJetsStruct.jetChargeDiff_, eventWeight);
        
        h_meanDeltaPhi_b_met_step8->Fill(mvaInputTopJetsStruct.meanDeltaPhi_b_met_, eventWeight);
        h_massDiff_recoil_bbbar_step8->Fill(mvaInputTopJetsStruct.massDiff_recoil_bbbar_, eventWeight);
        h_pt_b_antiLepton_step8->Fill(mvaInputTopJetsStruct.pt_b_antiLepton_, eventWeight);
        h_pt_antiB_lepton_step8->Fill(mvaInputTopJetsStruct.pt_antiB_lepton_, eventWeight);
        h_deltaR_b_antiLepton_step8->Fill(mvaInputTopJetsStruct.deltaR_b_antiLepton_, eventWeight);
        h_deltaR_antiB_lepton_step8->Fill(mvaInputTopJetsStruct.deltaR_antiB_lepton_, eventWeight);
        h_btagDiscriminatorSum_step8->Fill(mvaInputTopJetsStruct.btagDiscriminatorSum_, eventWeight);
        h_deltaPhi_antiBLepton_bAntiLepton_step8->Fill(mvaInputTopJetsStruct.deltaPhi_antiBLepton_bAntiLepton_, eventWeight);
        h_massDiff_fullBLepton_bbbar_step8->Fill(mvaInputTopJetsStruct.massDiff_fullBLepton_bbbar_, eventWeight);
        h_meanMT_b_met_step8->Fill(mvaInputTopJetsStruct.meanMT_b_met_, eventWeight);
        h_massSum_antiBLepton_bAntiLepton_step8->Fill(mvaInputTopJetsStruct.massSum_antiBLepton_bAntiLepton_, eventWeight);
        h_massDiff_antiBLepton_bAntiLepton_step8->Fill(mvaInputTopJetsStruct.massDiff_antiBLepton_bAntiLepton_, eventWeight);
        
        h_meanMTAlt_b_met_step8->Fill(mvaInputTopJetsStruct.meanMTAlt_b_met_, eventWeight);
    }
    std::cout<<"=== Finishing control plots for MVA variables\n\n";
}



void MvaInputTopJetsVariables::importTree(const std::string& f_savename)
{
    std::cout<<"--- Beginning import of TTree for MVA variables\n";
    
    TFile* inputFile = TFile::Open(f_savename.c_str());
    if(inputFile->IsZombie()){
        std::cerr<<"ERROR! Cannot open input file to import TTree, filename is: "<<f_savename<<"\n...break\n"<<std::endl;
        exit(77);
    }
    
    constexpr const char* treeName("mvaInputTopJets");
    TTree* tree(0);
    tree = dynamic_cast<TTree*>(inputFile->Get(treeName));
    if (!tree){
        std::cerr << "ERROR: TTree not found in file, tree name is: "<<treeName<<"\n...break\n"<<std::endl;
        exit(78);
    }
    
    this->importBranches(tree);
    
    tree = 0;
    inputFile->Close();
    std::cout<<"=== Finishing import of TTree for MVA variables\n\n";
}




void MvaInputTopJetsVariables::importBranches(TTree* tree)
{
    // Set up variables struct and branches
    MvaInputTopJetsStruct mvaInputStruct;
    
    TBranch* b_eventWeight(0);
    
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
    TBranch* b_meanMT_b_met(0);
    TBranch* b_massSum_antiBLepton_bAntiLepton(0);
    TBranch* b_massDiff_antiBLepton_bAntiLepton(0);
    
    TBranch* b_meanMTAlt_b_met(0);
    
    // Set branch addresses
    tree->SetBranchAddress("eventWeight", &mvaInputStruct.eventWeight_, &b_eventWeight);
    
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
    tree->SetBranchAddress("meanMT_b_met", &mvaInputStruct.meanMT_b_met_, &b_meanMT_b_met);
    tree->SetBranchAddress("massSum_antiBLepton_bAntiLepton", &mvaInputStruct.massSum_antiBLepton_bAntiLepton_, &b_massSum_antiBLepton_bAntiLepton);
    tree->SetBranchAddress("massDiff_antiBLepton_bAntiLepton", &mvaInputStruct.massDiff_antiBLepton_bAntiLepton_, &b_massDiff_antiBLepton_bAntiLepton);
    
    tree->SetBranchAddress("meanMTAlt_b_met", &mvaInputStruct.meanMTAlt_b_met_, &b_meanMTAlt_b_met);
    
    // Loop over all tree entries and fill vector of structs
    v_mvaInputStruct_.clear();
    for(Long64_t iEntry = 0; iEntry < tree->GetEntries(); ++iEntry){
        tree->GetEntry(iEntry);
        v_mvaInputStruct_.push_back(mvaInputStruct);
    }
}






