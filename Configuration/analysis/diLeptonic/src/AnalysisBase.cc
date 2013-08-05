#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <iomanip>
#include <algorithm>

#include <TROOT.h>
#include <TMath.h>
#include <TSystem.h>
#include <Math/VectorUtil.h>
#include <TLorentzVector.h>
#include <TStyle.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TObjArray.h>
#include <TRandom3.h>

#include "AnalysisBase.h"
#include "HistoListReader.h"
#include "utils.h"
#include "KinReco.h"
#include "JetCorrectorParameters.h"
#include "JetCorrectionUncertainty.h"
#include "PUReweighter.h"
#include "analysisUtils.h"
#include "classes.h"
#include "ScaleFactors.h"
#include "KinematicReconstruction.h"
#include "analysisObjectStructs.h"






AnalysisBase::AnalysisBase(TTree*):
samplename_(""),
channel_(""),
systematic_(""),
isMC_(false),
isTopSignal_(false),
isHiggsSignal_(false),
isTtbarPlusTauSample_(false),
correctMadgraphBR_(false),
channelPdgIdProduct_(0),
trueDYchannelCut_(0),
checkZDecayMode_(nullptr),
outputfilename_(""),
runViaTau_(false),
puReweighter_(nullptr),
leptonScaleFactors_(0),
triggerScaleFactors_(0),
btagScaleFactors_(0),
doJesJer_(false),
weightKinFit_(0),
isTtbarSample_(false),
binnedControlPlots_(0),
chain_(0),
useObjectStructs_(false),
h_weightedEvents(0),
jetCorrectionUncertainty_(nullptr),
eventCounter_(0),
analysisOutputBase_(0),
recoObjects_(0),
commonGenObjects_(0),
topGenObjects_(0),
higgsGenObjects_(0),
kinRecoObjects_(0)
{
    this->clearBranches();
    this->clearBranchVariables();
}



void AnalysisBase::Begin(TTree*)
{
    // WARNING! In general do not make changes here, but in your analysis' Begin function

    TSelector::Begin(0);
    
    eventCounter_ = 0;
}



void AnalysisBase::SlaveBegin(TTree*)
{
    // WARNING! In general do not make changes here, but in your analysis' SlaveBegin function

    TSelector::SlaveBegin(0);
    
    if(useObjectStructs_){
        recoObjects_ = new RecoObjects();
        commonGenObjects_ = new CommonGenObjects();
        topGenObjects_ = new TopGenObjects();
        higgsGenObjects_ = new HiggsGenObjects();
        kinRecoObjects_ = new KinRecoObjects();
    }
    
    binnedControlPlots_ = new std::map<std::string, std::pair<TH1*, std::vector<std::map<std::string, TH1*> > > >;
}



void AnalysisBase::SlaveTerminate()
{
    // WARNING! In general do not make changes here, but in your analysis' SlaveTerminate function

    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.
    
    for (auto it = binnedControlPlots_->begin(); it != binnedControlPlots_->end(); ++it) {
        delete (*it).second.first;
    }
    delete binnedControlPlots_;
    
    if(recoObjects_) delete recoObjects_;
    if(commonGenObjects_) delete commonGenObjects_;
    if(topGenObjects_) delete topGenObjects_;
    if(higgsGenObjects_) delete higgsGenObjects_;
    if(kinRecoObjects_) delete kinRecoObjects_;
}



Bool_t AnalysisBase::Process(Long64_t)
{
    // WARNING! In general do not make changes here, but in your analysis' Process function
    
    if(++eventCounter_ % 100000 == 0)
        std::cout<<"Event Counter: "<<eventCounter_<<"\t--  Channel, Systematic, Sample:"
                 <<std::setw(5)<<channel_<<" ,"<<std::setw(10)<<systematic_<<" , "<<samplename_<<std::endl;
    return kTRUE;
}



void AnalysisBase::Terminate()
{
    // WARNING! In general do not make changes here, but in your analysis' Terminate function
    
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.
    
    
    // Open output file for writing
    if(!analysisOutputBase_){
        std::cerr<<"ERROR! No base directory for analysis output specified\n...break\n"<<std::endl;
        exit(3);
    }
    std::string f_savename = ttbar::assignFolder(analysisOutputBase_, channel_, systematic_);
    f_savename.append(outputfilename_);
    std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!Finishing: "<<samplename_<<"!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    TFile outputFile(f_savename.c_str(), "RECREATE");
    if (outputFile.IsZombie()) {
        std::cerr << "Cannot open " << f_savename << " for writing!\n";
        exit(2);
    }
    
    
    // Write everything held by fOutput
    TIterator* iterator = fOutput->MakeIterator();
    while (TObject* obj = iterator->Next()) {
        obj->Write();
    }
    
    
    // Write additional information into file
    h_weightedEvents->Write();
    TObjString(channel_).Write("channelName");
    TObjString(systematic_).Write("systematicsName");
    TObjString(samplename_).Write("sampleName");
    TObjString(isTopSignal_ ? "1" : "0").Write("isSignal");
    TObjString(isHiggsSignal_ ? "1" : "0").Write("isHiggsSignal");
    TObjString(isMC_ ? "1" : "0").Write("isMC");
    outputFile.Close();
    std::cout<<"Created: \033[1;1m"<<f_savename<<"\033[1;m\n\n";
    
    
    // Cleanup
    fOutput->SetOwner();
    fOutput->Clear();
    delete jetCorrectionUncertainty_;
    jetCorrectionUncertainty_ = nullptr;
}



void AnalysisBase::Init(TTree *tree)
{
    // WARNING! In general do not make changes here, but in your analysis' Init function
    
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).
    
    // Reset all branches and their associated variables
    this->clearBranches();
    this->clearBranchVariables();
    
    // Set branch addresses and branch pointers
    if(!tree) return;
    chain_ = tree;
    chain_->SetMakeClass(0);
    this->SetRecoBranchAddresses();
    this->SetTriggerBranchAddresses();
    if(isMC_) this->SetCommonGenBranchAddresses();
    this->SetKinRecoBranchAddresses();
    if(isMC_) this->SetVertMultiTrueBranchAddress();
    if(isMC_) this->SetWeightGeneratorBranchAddress();
    this->SetPdfBranchAddress();
    this->SetDyDecayBranchAddress();
    this->SetTopDecayBranchAddress();
    if(isHiggsSignal_) this->SetHiggsDecayBranchAddress();
    if(isTopSignal_) this->SetTopSignalBranchAddresses();
    if(isHiggsSignal_) this->SetHiggsSignalBranchAddresses();
}



void AnalysisBase::SetChannel(const TString& channel)
{
    channel_ = channel;
    channelPdgIdProduct_ = 
        channel == "ee" ? -11*11
        : channel == "emu" ? -11*13
        : -13*13;
}



void AnalysisBase::SetTopSignal(const bool isTopSignal)
{
    isTopSignal_ = isTopSignal;
}



void AnalysisBase::SetHiggsSignal(const bool higgsSignal)
{
    isHiggsSignal_ = higgsSignal;
}



void AnalysisBase::SetSystematic(const TString& systematic)
{
    systematic_ = systematic;
}



void AnalysisBase::SetSamplename(const TString& samplename, const TString& systematic_from_file)
{
    samplename_ = samplename;
    isTtbarSample_ = samplename.BeginsWith("ttbar") && !samplename.BeginsWith("ttbarhiggs") && 
                     !(samplename=="ttbarw") && !(samplename=="ttbarz");
    isTtbarPlusTauSample_ = isTtbarSample_ && !samplename.BeginsWith("ttbarbg");
    correctMadgraphBR_ = samplename.BeginsWith("ttbar") && !systematic_from_file.Contains("SPIN") &&
                        !systematic_from_file.Contains("POWHEG") && !systematic_from_file.Contains("MCATNLO");
}



void AnalysisBase::SetMC(const bool isMC)
{
    isMC_ = isMC;
}



void AnalysisBase::SetOutputfilename(const TString& outputfilename)
{
    outputfilename_ = outputfilename;
}



void AnalysisBase::SetWeightedEvents(TH1* weightedEvents)
{
    h_weightedEvents = weightedEvents;
}



void AnalysisBase::SetRunViaTau(const bool runViaTau)
{
    runViaTau_ = runViaTau;
    if (runViaTau) isTopSignal_ = 0;
}



void AnalysisBase::SetAnalysisOutputBase(const char* analysisOutputBase)
{
    analysisOutputBase_ = analysisOutputBase;
}



void AnalysisBase::SetPUReweighter(PUReweighter* puReweighter)
{
    puReweighter_ = puReweighter;
}



void AnalysisBase::SetLeptonScaleFactors(const LeptonScaleFactors& scaleFactors)
{
    leptonScaleFactors_ = &scaleFactors;
}



void AnalysisBase::SetTriggerScaleFactors(const TriggerScaleFactors& scaleFactors)
{
    triggerScaleFactors_ = &scaleFactors;
}



void AnalysisBase::SetBtagScaleFactors(BtagScaleFactors& scaleFactors)
{
    btagScaleFactors_ = &scaleFactors;
}



void AnalysisBase::SetUseObjectStructs(const bool useObjectStructs)
{
    useObjectStructs_ = useObjectStructs;
}



void AnalysisBase::clearBranches()
{
    // nTuple branches relevant for reconstruction level
    // Concerning physics objects
    b_lepton = 0;
    b_lepPdgId = 0;
    b_lepID = 0;
    b_lepPfIso = 0;
    b_lepChargedHadronIso = 0;
    b_lepNeutralHadronIso = 0;
    b_lepPhotonIso = 0;
    b_lepPuChargedHadronIso = 0;
    b_lepCombIso = 0;
    b_lepDxyVertex0 = 0;
    b_lepTrigger = 0;
    b_jet = 0;
    b_jetBTagTCHE = 0;
    b_jetBTagTCHP = 0;
    b_jetBTagSSVHE = 0;
    b_jetBTagSSVHP = 0;
    b_jetBTagJetProbability = 0;
    b_jetBTagJetBProbability = 0;
    b_jetBTagCSV = 0;
    b_jetBTagCSVMVA = 0;
    b_jetChargeGlobalPtWeighted = 0;
    b_jetChargeRelativePtWeighted = 0;
    b_met = 0;
    b_jetJERSF = 0;
    b_jetForMET = 0;
    b_jetForMETJERSF = 0;
    
    // nTuple branches relevant for reconstruction level
    // Concerning event
    b_runNumber = 0;
    b_lumiBlock = 0;
    b_eventNumber = 0;
    b_recoInChannel = 0;
    b_vertMulti = 0;
    
    
    // nTuple branches holding trigger bits
    b_triggerBits = 0;
    b_triggerBitsTau = 0;
    b_firedTriggers = 0;
    
    
    // nTuple branches holding generator information for all MC samples
    // Concerning physics objects
    b_allGenJets = 0;
    b_jetPartonFlavour = 0;
    b_associatedGenJet = 0;
    b_associatedGenJetForMET = 0;
    b_jetAssociatedPartonPdgId = 0;
    b_jetAssociatedParton = 0;
    
    
    // nTuple branches of kinematic reconstruction
    b_HypTop = 0;
    b_HypAntiTop = 0;
    b_HypLepton = 0;
    b_HypAntiLepton = 0;
    b_HypNeutrino = 0;
    b_HypAntiNeutrino = 0;
    b_HypB = 0;
    b_HypAntiB = 0;
    b_HypWPlus = 0;
    b_HypWMinus = 0;
    b_HypJet0index = 0;
    b_HypJet1index = 0;
    
    
    // nTuple branch for true vertex multiplicity
    b_vertMultiTrue = 0;
    
    
    // nTuple branch for generator event weight
    b_weightGenerator = 0;
    
    
    // nTuple branch for PDF weights
    b_weightPDF = 0;
    
    
    // nTuple branch for Drell-Yan decay mode
    b_ZDecayMode = 0;
    
    
    // nTuple branch for Top decay mode
    b_TopDecayMode = 0;
    
    
    // nTuple branch for Higgs decay mode
    b_HiggsDecayMode = 0;
    
    
    // nTuple branches for Top signal samples on generator level
    b_GenMet = 0;
    b_GenTop = 0;
    b_GenAntiTop = 0;
    b_GenLepton = 0;
    b_GenAntiLepton = 0;
    b_GenLeptonPdgId = 0;
    b_GenAntiLeptonPdgId = 0;
    b_GenTau = 0;
    b_GenAntiTau = 0;
    b_GenNeutrino = 0;
    b_GenAntiNeutrino = 0;
    b_GenB = 0;
    b_GenAntiB = 0;
    b_GenWPlus = 0;
    b_GenWMinus = 0;
    b_GenParticleP4 = 0;
    b_GenParticlePdgId = 0;
    b_GenParticleStatus = 0;
    b_BHadJetIndex = 0;
    b_AntiBHadJetIndex = 0;
    b_BHadrons = 0;
    b_AntiBHadrons = 0;
    b_BHadronFromTopB = 0;
    b_AntiBHadronFromTopB = 0;
    b_BHadronVsJet = 0;
    b_AntiBHadronVsJet = 0;
    b_genBHadPlusMothersPdgId = 0;
    b_genBHadPlusMothersStatus = 0;
    b_genBHadPlusMothersIndices = 0;
    b_genBHadPlusMothers = 0;
    b_genBHadIndex = 0;
    b_genBHadFlavour = 0;
    b_genBHadJetIndex = 0;
    
    
    // nTuple branches for Higgs signal samples on generator level
    b_GenH = 0;
    b_GenBFromH = 0;
    b_GenAntiBFromH = 0;
}



void AnalysisBase::clearBranchVariables()
{
    if(useObjectStructs_){
        recoObjects_->clear();
        commonGenObjects_->clear();
        topGenObjects_->clear();
        higgsGenObjects_->clear();
        kinRecoObjects_->clear();
    }
    else{
        // Set values to null for branches relevant for reconstruction level
        // Concerning physics objects
        leptons_ = 0;
        lepPdgId_ = 0;
        //lepID_ = 0;
        lepPfIso_ = 0;
        //lepChargedHadronIso_ = 0;
        //lepNeutralHadronIso_ = 0;
        //lepPhotonIso_ = 0;
        //lepPuChargedHadronIso_ = 0;
        lepCombIso_ = 0;
        lepDxyVertex0_ = 0;
        //lepTrigger_ = 0;
        jets_ = 0;
        jetBTagTCHE_ = 0;
        //jetBTagTCHP_ = 0;
        jetBTagSSVHE_ = 0;
        //jetBTagSSVHP_ = 0;
        //jetBTagJetProbability_ = 0;
        //jetBTagJetBProbability_ = 0;
        jetBTagCSV_ = 0;
        //jetBTagCSVMVA_ = 0;
        jetChargeGlobalPtWeighted_ = 0;
        jetChargeRelativePtWeighted_ = 0;
        met_ = 0;
        jetJERSF_ = 0;
        jetsForMET_ = 0;
        jetForMETJERSF_ = 0;
        
        // Set values to null for branches relevant for reconstruction level
        // Concerning event
        runNumber_ = 0;
        lumiBlock_ = 0;
        eventNumber_ = 0;
        //recoInChannel_ = 0;
        triggerBits_ = 0;
        //triggerBitsTau_ = 0;
        //firedTriggers_ = 0;
        vertMulti_ = 0;
        
        
        // Set values to null for branches holding generator information for all MC samples
        // Concerning physics objects
        allGenJets_ = 0;
        jetPartonFlavour_ = 0;
        associatedGenJet_ = 0;
        associatedGenJetForMET_ = 0;
        //jetAssociatedPartonPdgId_ = 0;
        //jetAssociatedParton_ = 0;
        
        
        // Set values to null for branches of kinematic reconstruction
        HypTop_ = 0;
        HypAntiTop_ = 0;
        HypLepton_ = 0;
        HypAntiLepton_ = 0;
        HypNeutrino_ = 0;
        HypAntiNeutrino_ = 0;
        HypBJet_ = 0;
        HypAntiBJet_ = 0;
        //HypWPlus_ = 0;
        //HypWMinus_ = 0;
        HypJet0index_ = 0;
        HypJet1index_ = 0;
        
        
        // Set values to null for Top signal sample branches
        GenMet_ = 0;
        GenTop_ = 0;
        GenAntiTop_ = 0;
        GenLepton_ = 0;
        GenAntiLepton_ = 0;
        //GenLeptonPdgId_ = 0;
        //GenAntiLeptonPdgId_ = 0;
        //GenTau_ = 0;
        //GenAntiTau_ = 0;
        GenNeutrino_ = 0;
        GenAntiNeutrino_ = 0;
        GenB_ = 0;
        GenAntiB_ = 0;
        //GenWPlus_ = 0;
        //GenWMinus_ = 0;
        //GenParticleP4_= 0;
        //GenParticlePdgId_= 0;
        //GenParticleStatus_= 0;
        BHadJetIndex_ = 0;
        AntiBHadJetIndex_ = 0;
        BHadrons_ = 0;
        AntiBHadrons_ = 0;
        BHadronFromTopB_ = 0;
        AntiBHadronFromTopB_ = 0;
        BHadronVsJet_ = 0;
        AntiBHadronVsJet_ = 0;
        //genBHadPlusMothersPdgId_ = 0;
        //genBHadPlusMothersStatus_ = 0;
        //genBHadPlusMothersIndices_ = 0;
        genBHadPlusMothers_ = 0;
        genBHadIndex_ = 0;
        genBHadFlavour_ = 0;
        genBHadJetIndex_ = 0;
        
        
        // Set values to null for Higgs signal sample branches
        GenH_ = 0;
        GenBFromH_ = 0;
        GenAntiBFromH_ = 0;
    }
    
    
    // Set values to null for true vertex multiplicity
    vertMultiTrue_ = 0;
    
    
    // Set values to null for generator event weight
    weightGenerator_ = 0;
    
    
    // Set values to null for PDF weight
    weightPDF_ = 0;
    
    
    // Set values to null for Drell-Yan decay branch
    ZDecayMode_ = 0;
    
    
    // Set values to null for Top decay branch
    topDecayMode_ = 0;
    
    
    // Set values to null for Higgs decay branch
    higgsDecayMode_ = 0;
    
    
}



void AnalysisBase::SetRecoBranchAddresses()
{
    if(recoObjects_){
        // Concerning physics objects
        chain_->SetBranchAddress("leptons", &recoObjects_->allLeptons_, &b_lepton);
        chain_->SetBranchAddress("lepPdgId", &recoObjects_->lepPdgId_, &b_lepPdgId);
        //chain_->SetBranchAddress("lepID", &recoObjects_->lepID_, &b_lepID);
        chain_->SetBranchAddress("lepPfIso", &recoObjects_->lepPfIso_, &b_lepPfIso);
        //chain_->SetBranchAddress("lepChargedHadronIso", &recoObjects_->lepChargedHadronIso_, &b_lepChargedHadronIso);
        //chain_->SetBranchAddress("lepNeutralHadronIso", &recoObjects_->lepNeutralHadronIso_, &b_lepNeutralHadronIso);
        //chain_->SetBranchAddress("lepPhotonIso", &recoObjects_->lepPhotonIso_, &b_lepPhotonIso);
        //chain_->SetBranchAddress("lepPuChargedHadronIso", &recoObjects_->lepPuChargedHadronIso_, &b_lepPuChargedHadronIso);
        chain_->SetBranchAddress("lepCombIso", &recoObjects_->lepCombIso_, &b_lepCombIso);
        chain_->SetBranchAddress("lepDxyVertex0", &recoObjects_->lepDxyVertex0_, &b_lepDxyVertex0);
        //chain_->SetBranchAddress("lepTrigger", &recoObjects_->lepTrigger_, &b_lepTrigger);
        chain_->SetBranchAddress("jets", &recoObjects_->jets_, &b_jet);
        chain_->SetBranchAddress("jetBTagTCHE", &recoObjects_->jetBTagTCHE_, &b_jetBTagTCHE);
        //chain_->SetBranchAddress("jetBTagTCHP", &recoObjects_->jetBTagTCHP_, &b_jetBTagTCHP);
        chain_->SetBranchAddress("jetBTagSSVHE", &recoObjects_->jetBTagSSVHE_, &b_jetBTagSSVHE);
        //chain_->SetBranchAddress("jetBTagSSVHP", &recoObjects_->jetBTagSSVHP_, &b_jetBTagSSVHP);
        //chain_->SetBranchAddress("jetBTagJetProbability", &recoObjects_->jetBTagJetProbability_, &b_jetBTagJetProbability);
        //chain_->SetBranchAddress("jetBTagJetBProbability", &recoObjects_->jetBTagJetBProbability_, &b_jetBTagJetBProbability);
        chain_->SetBranchAddress("jetBTagCSV", &recoObjects_->jetBTagCSV_, &b_jetBTagCSV);
        //chain_->SetBranchAddress("jetBTagCSVMVA", &recoObjects_->jetBTagCSVMVA_, &b_jetBTagCSVMVA);
        if(chain_->GetBranch("jetChargeGlobalPtWeighted")) // new variable, keep check a while for compatibility
            chain_->SetBranchAddress("jetChargeGlobalPtWeighted", &recoObjects_->jetChargeGlobalPtWeighted_, &b_jetChargeGlobalPtWeighted);
        else b_jetChargeGlobalPtWeighted = 0;
        if(chain_->GetBranch("jetChargeRelativePtWeighted")) // new variable, keep check a while for compatibility
            chain_->SetBranchAddress("jetChargeRelativePtWeighted", &recoObjects_->jetChargeRelativePtWeighted_, &b_jetChargeRelativePtWeighted);
        else b_jetChargeRelativePtWeighted = 0;
        chain_->SetBranchAddress("met", &recoObjects_->met_, &b_met);
        if(doJesJer_){
            chain_->SetBranchAddress("jetJERSF", &recoObjects_->jetJERSF_, &b_jetJERSF);
            chain_->SetBranchAddress("jetsForMET", &recoObjects_->jetsForMET_, &b_jetForMET);
            chain_->SetBranchAddress("jetForMETJERSF", &recoObjects_->jetForMETJERSF_, &b_jetForMETJERSF);
        }
        
        // Concerning event
        chain_->SetBranchAddress("runNumber", &recoObjects_->runNumber_, &b_runNumber);
        chain_->SetBranchAddress("lumiBlock", &recoObjects_->lumiBlock_, &b_lumiBlock);
        chain_->SetBranchAddress("eventNumber", &recoObjects_->eventNumber_, &b_eventNumber);
        //chain_->SetBranchAddress("recoInChannel", &recoObjects_->recoInChannel_, &b_recoInChannel);
        chain_->SetBranchAddress("vertMulti", &recoObjects_->vertMulti_, &b_vertMulti);
        
        return;
    }
    
    
    // Concerning physics objects
    chain_->SetBranchAddress("leptons", &leptons_, &b_lepton);
    chain_->SetBranchAddress("lepPdgId", &lepPdgId_, &b_lepPdgId);
    //chain_->SetBranchAddress("lepID", &lepID_, &b_lepID);
    chain_->SetBranchAddress("lepPfIso", &lepPfIso_, &b_lepPfIso);
    //chain_->SetBranchAddress("lepChargedHadronIso", &lepChargedHadronIso_, &b_lepChargedHadronIso);
    //chain_->SetBranchAddress("lepNeutralHadronIso", &lepNeutralHadronIso_, &b_lepNeutralHadronIso);
    //chain_->SetBranchAddress("lepPhotonIso", &lepPhotonIso_, &b_lepPhotonIso);
    //chain_->SetBranchAddress("lepPuChargedHadronIso", &lepPuChargedHadronIso_, &b_lepPuChargedHadronIso);
    chain_->SetBranchAddress("lepCombIso", &lepCombIso_, &b_lepCombIso);
    chain_->SetBranchAddress("lepDxyVertex0", &lepDxyVertex0_, &b_lepDxyVertex0);
    //chain_->SetBranchAddress("lepTrigger", &lepTrigger_, &b_lepTrigger);
    chain_->SetBranchAddress("jets", &jets_, &b_jet);
    chain_->SetBranchAddress("jetBTagTCHE", &jetBTagTCHE_, &b_jetBTagTCHE);
    //chain_->SetBranchAddress("jetBTagTCHP", &jetBTagTCHP_, &b_jetBTagTCHP);
    chain_->SetBranchAddress("jetBTagSSVHE", &jetBTagSSVHE_, &b_jetBTagSSVHE);
    //chain_->SetBranchAddress("jetBTagSSVHP", &jetBTagSSVHP_, &b_jetBTagSSVHP);
    //chain_->SetBranchAddress("jetBTagJetProbability", &jetBTagJetProbability_, &b_jetBTagJetProbability);
    //chain_->SetBranchAddress("jetBTagJetBProbability", &jetBTagJetBProbability_, &b_jetBTagJetBProbability);
    chain_->SetBranchAddress("jetBTagCSV", &jetBTagCSV_, &b_jetBTagCSV);
    //chain_->SetBranchAddress("jetBTagCSVMVA", &jetBTagCSVMVA_, &b_jetBTagCSVMVA);
    if(chain_->GetBranch("jetChargeGlobalPtWeighted")) // new variable, keep check a while for compatibility
        chain_->SetBranchAddress("jetChargeGlobalPtWeighted", &jetChargeGlobalPtWeighted_, &b_jetChargeGlobalPtWeighted);
    else b_jetChargeGlobalPtWeighted = 0;
    if(chain_->GetBranch("jetChargeRelativePtWeighted")) // new variable, keep check a while for compatibility
        chain_->SetBranchAddress("jetChargeRelativePtWeighted", &jetChargeRelativePtWeighted_, &b_jetChargeRelativePtWeighted);
    else b_jetChargeRelativePtWeighted = 0;
    chain_->SetBranchAddress("met", &met_, &b_met);
    if(doJesJer_){
        chain_->SetBranchAddress("jetJERSF", &jetJERSF_, &b_jetJERSF);
        chain_->SetBranchAddress("jetsForMET", &jetsForMET_, &b_jetForMET);
        chain_->SetBranchAddress("jetForMETJERSF", &jetForMETJERSF_, &b_jetForMETJERSF);
    }
    
    // Concerning event
    chain_->SetBranchAddress("runNumber", &runNumber_, &b_runNumber);
    chain_->SetBranchAddress("lumiBlock", &lumiBlock_, &b_lumiBlock);
    chain_->SetBranchAddress("eventNumber", &eventNumber_, &b_eventNumber);
    //chain_->SetBranchAddress("recoInChannel", &recoInChannel_, &b_recoInChannel);
    chain_->SetBranchAddress("vertMulti", &vertMulti_, &b_vertMulti);
}



void AnalysisBase::SetTriggerBranchAddresses()
{
    chain_->SetBranchAddress("triggerBits", &triggerBits_, &b_triggerBits);
    //chain_->SetBranchAddress("triggerBitsTau", &triggerBitsTau_, &b_triggerBitsTau);
    //chain_->SetBranchAddress("firedTriggers", &firedTriggers_, &b_firedTriggers);
}



void AnalysisBase::SetCommonGenBranchAddresses()
{
    if(commonGenObjects_){
        // Concerning physics objects
        chain_->SetBranchAddress("allGenJets", &commonGenObjects_->allGenJets_, &b_allGenJets);
        chain_->SetBranchAddress("jetPartonFlavour", &commonGenObjects_->jetPartonFlavour_, &b_jetPartonFlavour);
        chain_->SetBranchAddress("associatedGenJet", &commonGenObjects_->associatedGenJet_, &b_associatedGenJet);
        if(doJesJer_){
            chain_->SetBranchAddress("associatedGenJetForMET", &commonGenObjects_->associatedGenJetForMET_, &b_associatedGenJetForMET);
        }
        //chain_->SetBranchAddress("jetAssociatedPartonPdgId", &commonGenObjects_->jetAssociatedPartonPdgId_, &b_jetAssociatedPartonPdgId);
        //chain_->SetBranchAddress("jetAssociatedParton", &commonGenObjects_->jetAssociatedParton_, &b_jetAssociatedParton);
        
        return;
    }
    
    // Concerning physics objects
    chain_->SetBranchAddress("allGenJets", &allGenJets_, &b_allGenJets);
    chain_->SetBranchAddress("jetPartonFlavour", &jetPartonFlavour_, &b_jetPartonFlavour);
    chain_->SetBranchAddress("associatedGenJet", &associatedGenJet_, &b_associatedGenJet);
    if(doJesJer_){
        chain_->SetBranchAddress("associatedGenJetForMET", &associatedGenJetForMET_, &b_associatedGenJetForMET);
    }
    //chain_->SetBranchAddress("jetAssociatedPartonPdgId", &jetAssociatedPartonPdgId_, &b_jetAssociatedPartonPdgId);
    //chain_->SetBranchAddress("jetAssociatedParton", &jetAssociatedParton_, &b_jetAssociatedParton);
}



void AnalysisBase::SetKinRecoBranchAddresses()
{
    if(kinRecoObjects_){
        chain_->SetBranchAddress("HypTop", &kinRecoObjects_->HypTop_, &b_HypTop);
        chain_->SetBranchAddress("HypAntiTop", &kinRecoObjects_->HypAntiTop_, &b_HypAntiTop);
        chain_->SetBranchAddress("HypLepton", &kinRecoObjects_->HypLepton_, &b_HypLepton);
        chain_->SetBranchAddress("HypAntiLepton", &kinRecoObjects_->HypAntiLepton_, &b_HypAntiLepton);
        chain_->SetBranchAddress("HypNeutrino", &kinRecoObjects_->HypNeutrino_, &b_HypNeutrino);
        chain_->SetBranchAddress("HypAntiNeutrino", &kinRecoObjects_->HypAntiNeutrino_, &b_HypAntiNeutrino);
        chain_->SetBranchAddress("HypB", &kinRecoObjects_->HypBJet_, &b_HypB);
        chain_->SetBranchAddress("HypAntiB", &kinRecoObjects_->HypAntiBJet_, &b_HypAntiB);
        //chain_->SetBranchAddress("HypWPlus", &kinRecoObjects_->HypWPlus_, &b_HypWPlus_);
        //chain_->SetBranchAddress("HypWMinus", &kinRecoObjects_->HypWMinus_, &b_HypWMinus_);
        chain_->SetBranchAddress("HypJet0index", &kinRecoObjects_->HypJet0index_, &b_HypJet0index);
        chain_->SetBranchAddress("HypJet1index", &kinRecoObjects_->HypJet1index_, &b_HypJet1index);
        
        return;
    }
    
    chain_->SetBranchAddress("HypTop", &HypTop_, &b_HypTop);
    chain_->SetBranchAddress("HypAntiTop", &HypAntiTop_, &b_HypAntiTop);
    chain_->SetBranchAddress("HypLepton", &HypLepton_, &b_HypLepton);
    chain_->SetBranchAddress("HypAntiLepton", &HypAntiLepton_, &b_HypAntiLepton);
    chain_->SetBranchAddress("HypNeutrino", &HypNeutrino_, &b_HypNeutrino);
    chain_->SetBranchAddress("HypAntiNeutrino", &HypAntiNeutrino_, &b_HypAntiNeutrino);
    chain_->SetBranchAddress("HypB", &HypBJet_, &b_HypB);
    chain_->SetBranchAddress("HypAntiB", &HypAntiBJet_, &b_HypAntiB);
    //chain_->SetBranchAddress("HypWPlus", &HypWPlus_, &b_HypWPlus_);
    //chain_->SetBranchAddress("HypWMinus", &HypWMinus_, &b_HypWMinus_);
    chain_->SetBranchAddress("HypJet0index", &HypJet0index_, &b_HypJet0index);
    chain_->SetBranchAddress("HypJet1index", &HypJet1index_, &b_HypJet1index);
}



void AnalysisBase::SetVertMultiTrueBranchAddress()
{
    chain_->SetBranchAddress("vertMultiTrue", &vertMultiTrue_, &b_vertMultiTrue);
}



void AnalysisBase::SetWeightGeneratorBranchAddress()
{
    chain_->SetBranchAddress("weightGenerator", &weightGenerator_, &b_weightGenerator);
}



void AnalysisBase::SetPdfBranchAddress()
{
    if(chain_->GetBranch("pdfWeights")) chain_->SetBranchAddress("pdfWeights", &weightPDF_, &b_weightPDF);
}



void AnalysisBase::SetDyDecayBranchAddress()
{
    chain_->SetBranchAddress("ZDecayMode", &ZDecayMode_, &b_ZDecayMode);
}



void AnalysisBase::SetTopDecayBranchAddress()
{
    chain_->SetBranchAddress("TopDecayMode", &topDecayMode_, &b_TopDecayMode);
}



void AnalysisBase::SetHiggsDecayBranchAddress()
{
    chain_->SetBranchAddress("HiggsDecayMode", &higgsDecayMode_, &b_HiggsDecayMode);
}



void AnalysisBase::SetTopSignalBranchAddresses()
{
    if(topGenObjects_){
        chain_->SetBranchAddress("GenMET", &topGenObjects_->GenMet_, &b_GenMet);
        chain_->SetBranchAddress("GenTop", &topGenObjects_->GenTop_, &b_GenTop);
        chain_->SetBranchAddress("GenAntiTop", &topGenObjects_->GenAntiTop_, &b_GenAntiTop);
        chain_->SetBranchAddress("GenLepton", &topGenObjects_->GenLepton_, &b_GenLepton);
        chain_->SetBranchAddress("GenAntiLepton", &topGenObjects_->GenAntiLepton_, &b_GenAntiLepton);
        //chain_->SetBranchAddress("GenLeptonPdgId", &topGenObjects_->GenLeptonPdgId_, &b_GenLeptonPdgId);
        //chain_->SetBranchAddress("GenAntiLeptonPdgId", &topGenObjects_->GenAntiLeptonPdgId_, &b_GenAntiLeptonPdgId);
        //chain_->SetBranchAddress("GenTau", &topGenObjects_->GenTau_, &b_GenTau);
        //chain_->SetBranchAddress("GenAntiTau", &topGenObjects_->GenAntiTau_, &b_GenAntiTau);
        chain_->SetBranchAddress("GenNeutrino", &topGenObjects_->GenNeutrino_, &b_GenNeutrino);
        chain_->SetBranchAddress("GenAntiNeutrino", &topGenObjects_->GenAntiNeutrino_, &b_GenAntiNeutrino);
        chain_->SetBranchAddress("GenB", &topGenObjects_->GenB_, &b_GenB);
        chain_->SetBranchAddress("GenAntiB", &topGenObjects_->GenAntiB_, &b_GenAntiB);
        //chain_->SetBranchAddress("GenWPlus", &topGenObjects_->GenWPlus_, &b_GenWPlus);
        //chain_->SetBranchAddress("GenWMinus", &topGenObjects_->GenWMinus_, &b_GenWMinus);
        //chain_->SetBranchAddress("GenWPlus.fCoordinates.fX", &topGenObjects_->GenWPluspX, &b_GenWPluspX);
        //chain_->SetBranchAddress("GenWMinus.fCoordinates.fX", &topGenObjects_->GenWMinuspX, &b_GenWMinuspX);
        //chain_->SetBranchAddress("GenParticleP4", &topGenObjects_->GenParticleP4_, &b_GenParticleP4);
        //chain_->SetBranchAddress("GenParticlePdgId", &topGenObjects_->GenParticlePdgId_, &b_GenParticlePdgId);
        //chain_->SetBranchAddress("GenParticleStatus", &topGenObjects_->GenParticleStatus_, &b_GenParticleStatus);
        chain_->SetBranchAddress("BHadJetIndex", &topGenObjects_->BHadJetIndex_, &b_BHadJetIndex);
        chain_->SetBranchAddress("AntiBHadJetIndex", &topGenObjects_->AntiBHadJetIndex_, &b_AntiBHadJetIndex);
        chain_->SetBranchAddress("BHadrons", &topGenObjects_->BHadrons_, &b_BHadrons);
        chain_->SetBranchAddress("AntiBHadrons", &topGenObjects_->AntiBHadrons_, &b_AntiBHadrons);
        chain_->SetBranchAddress("BHadronFromTop", &topGenObjects_->BHadronFromTopB_, &b_BHadronFromTopB);
        chain_->SetBranchAddress("AntiBHadronFromTopB", &topGenObjects_->AntiBHadronFromTopB_, &b_AntiBHadronFromTopB);
        chain_->SetBranchAddress("BHadronVsJet", &topGenObjects_->BHadronVsJet_, &b_BHadronVsJet);
        chain_->SetBranchAddress("AntiBHadronVsJet", &topGenObjects_->AntiBHadronVsJet_, &b_AntiBHadronVsJet);
        //if(chain_->GetBranch("genBHadPlusMothersPdgId")) // need to check whether branch exists
        //    chain_->SetBranchAddress("genBHadPlusMothersPdgId", &topGenObjects_->genBHadPlusMothersPdgId_, &b_genBHadPlusMothersPdgId);
        //if(chain_->GetBranch("genBHadPlusMothersStatus")) // need to check whether branch exists
        //    chain_->SetBranchAddress("genBHadPlusMothersStatus", &topGenObjects_->genBHadPlusMothersStatus_, &b_genBHadPlusMothersStatus);
        //if(chain_->GetBranch("genBHadPlusMothersIndices")) // need to check whether branch exists
        //    chain_->SetBranchAddress("genBHadPlusMothersIndices", &topGenObjects_->genBHadPlusMothersIndices_, &b_genBHadPlusMothersIndices);
        if(chain_->GetBranch("genBHadPlusMothers")) // need to check whether branch exists
            chain_->SetBranchAddress("genBHadPlusMothers", &topGenObjects_->genBHadPlusMothers_, &b_genBHadPlusMothers);
        if(chain_->GetBranch("genBHadIndex")) // need to check whether branch exists
            chain_->SetBranchAddress("genBHadIndex", &topGenObjects_->genBHadIndex_, &b_genBHadIndex);
        if(chain_->GetBranch("genBHadFlavour")) // need to check whether branch exists
            chain_->SetBranchAddress("genBHadFlavour", &topGenObjects_->genBHadFlavour_, &b_genBHadFlavour);
        if(chain_->GetBranch("genBHadJetIndex")) // need to check whether branch exists
            chain_->SetBranchAddress("genBHadJetIndex", &topGenObjects_->genBHadJetIndex_, &b_genBHadJetIndex);
        
        return;
    }
    
    
    chain_->SetBranchAddress("GenMET", &GenMet_, &b_GenMet);
    chain_->SetBranchAddress("GenTop", &GenTop_, &b_GenTop);
    chain_->SetBranchAddress("GenAntiTop", &GenAntiTop_, &b_GenAntiTop);
    chain_->SetBranchAddress("GenLepton", &GenLepton_, &b_GenLepton);
    chain_->SetBranchAddress("GenAntiLepton", &GenAntiLepton_, &b_GenAntiLepton);
    //chain_->SetBranchAddress("GenLeptonPdgId", &GenLeptonPdgId_, &b_GenLeptonPdgId);
    //chain_->SetBranchAddress("GenAntiLeptonPdgId", &GenAntiLeptonPdgId_, &b_GenAntiLeptonPdgId);
    //chain_->SetBranchAddress("GenTau", &GenTau_, &b_GenTau);
    //chain_->SetBranchAddress("GenAntiTau", &GenAntiTau_, &b_GenAntiTau);
    chain_->SetBranchAddress("GenNeutrino", &GenNeutrino_, &b_GenNeutrino);
    chain_->SetBranchAddress("GenAntiNeutrino", &GenAntiNeutrino_, &b_GenAntiNeutrino);
    chain_->SetBranchAddress("GenB", &GenB_, &b_GenB);
    chain_->SetBranchAddress("GenAntiB", &GenAntiB_, &b_GenAntiB);
    //chain_->SetBranchAddress("GenWPlus", &GenWPlus_, &b_GenWPlus);
    //chain_->SetBranchAddress("GenWMinus", &GenWMinus_, &b_GenWMinus);
    //chain_->SetBranchAddress("GenWPlus.fCoordinates.fX", &GenWPluspX, &b_GenWPluspX);
    //chain_->SetBranchAddress("GenWMinus.fCoordinates.fX", &GenWMinuspX, &b_GenWMinuspX);
    //chain_->SetBranchAddress("GenParticleP4", &GenParticleP4_, &b_GenParticleP4);
    //chain_->SetBranchAddress("GenParticlePdgId", &GenParticlePdgId_, &b_GenParticlePdgId);
    //chain_->SetBranchAddress("GenParticleStatus", &GenParticleStatus_, &b_GenParticleStatus);
    chain_->SetBranchAddress("BHadJetIndex", &BHadJetIndex_, &b_BHadJetIndex);
    chain_->SetBranchAddress("AntiBHadJetIndex", &AntiBHadJetIndex_, &b_AntiBHadJetIndex);
    chain_->SetBranchAddress("BHadrons", &BHadrons_, &b_BHadrons);
    chain_->SetBranchAddress("AntiBHadrons", &AntiBHadrons_, &b_AntiBHadrons);
    chain_->SetBranchAddress("BHadronFromTop", &BHadronFromTopB_, &b_BHadronFromTopB);
    chain_->SetBranchAddress("AntiBHadronFromTopB", &AntiBHadronFromTopB_, &b_AntiBHadronFromTopB);
    chain_->SetBranchAddress("BHadronVsJet", &BHadronVsJet_, &b_BHadronVsJet);
    chain_->SetBranchAddress("AntiBHadronVsJet", &AntiBHadronVsJet_, &b_AntiBHadronVsJet);
    //if(chain_->GetBranch("genBHadPlusMothersPdgId")) // need to check whether branch exists
    //    chain_->SetBranchAddress("genBHadPlusMothersPdgId", &genBHadPlusMothersPdgId_, &b_genBHadPlusMothersPdgId);
    //if(chain_->GetBranch("genBHadPlusMothersStatus")) // need to check whether branch exists
    //    chain_->SetBranchAddress("genBHadPlusMothersStatus", &genBHadPlusMothersStatus_, &b_genBHadPlusMothersStatus);
    //if(chain_->GetBranch("genBHadPlusMothersIndices")) // need to check whether branch exists
    //    chain_->SetBranchAddress("genBHadPlusMothersIndices", &genBHadPlusMothersIndices_, &b_genBHadPlusMothersIndices);
    if(chain_->GetBranch("genBHadPlusMothers")) // need to check whether branch exists
        chain_->SetBranchAddress("genBHadPlusMothers", &genBHadPlusMothers_, &b_genBHadPlusMothers);
    if(chain_->GetBranch("genBHadIndex")) // need to check whether branch exists
        chain_->SetBranchAddress("genBHadIndex", &genBHadIndex_, &b_genBHadIndex);
    if(chain_->GetBranch("genBHadFlavour")) // need to check whether branch exists
        chain_->SetBranchAddress("genBHadFlavour", &genBHadFlavour_, &b_genBHadFlavour);
    if(chain_->GetBranch("genBHadJetIndex")) // need to check whether branch exists
        chain_->SetBranchAddress("genBHadJetIndex", &genBHadJetIndex_, &b_genBHadJetIndex);
}



void AnalysisBase::SetHiggsSignalBranchAddresses()
{
    if(higgsGenObjects_){
        chain_->SetBranchAddress("GenH", &higgsGenObjects_->GenH_, &b_GenH);
        chain_->SetBranchAddress("GenBFromH", &higgsGenObjects_->GenBFromH_, &b_GenBFromH);
        chain_->SetBranchAddress("GenAntiBFromH", &higgsGenObjects_->GenAntiBFromH_, &b_GenAntiBFromH);
        
        return;
    }
    
    chain_->SetBranchAddress("GenH", &GenH_, &b_GenH);
    chain_->SetBranchAddress("GenBFromH", &GenBFromH_, &b_GenBFromH);
    chain_->SetBranchAddress("GenAntiBFromH", &GenAntiBFromH_, &b_GenAntiBFromH);
}



void AnalysisBase::GetRecoBranchesEntry(const Long64_t& entry)const
{    
    // Check if branches' entry is already read
    if(recoObjects_){
        if(recoObjects_->valuesSet_) return;
        recoObjects_->valuesSet_ = true;
    }
    
    // Concerning physics objects
    b_lepton->GetEntry(entry);
    b_lepPdgId->GetEntry(entry);
    //b_lepID->GetEntry(entry);
    //b_lepPfIso->GetEntry(entry);
    //b_lepChargedHadronIso->GetEntry(entry);
    //b_lepNeutralHadronIso->GetEntry(entry);
    //b_lepPhotonIso->GetEntry(entry);
    //b_lepPuChargedHadronIso->GetEntry(entry);
    //b_lepCombIso->GetEntry(entry);
    //b_lepDxyVertex0->GetEntry(entry);
    //b_lepTrigger->GetEntry(entry);
    b_jet->GetEntry(entry);
    //b_jetBTagTCHE->GetEntry(entry);
    //b_jetBTagTCHP->GetEntry(entry);
    //b_jetBTagSSVHE->GetEntry(entry);
    //b_jetBTagSSVHP->GetEntry(entry);
    //b_jetBTagJetProbability->GetEntry(entry);
    //b_jetBTagJetBProbability->GetEntry(entry);
    b_jetBTagCSV->GetEntry(entry);
    //b_jetBTagCSVMVA->GetEntry(entry);
    if(b_jetChargeGlobalPtWeighted) b_jetChargeGlobalPtWeighted->GetEntry(entry);
    if(b_jetChargeRelativePtWeighted) b_jetChargeRelativePtWeighted->GetEntry(entry);
    b_met->GetEntry(entry);
    if(doJesJer_){
        b_jetJERSF->GetEntry(entry);
        b_jetForMET->GetEntry(entry);
        b_jetForMETJERSF->GetEntry(entry);
    }
    
    // Concerning event
    b_runNumber->GetEntry(entry);
    b_lumiBlock->GetEntry(entry);
    b_eventNumber->GetEntry(entry);
    //b_recoInChannel->GetEntry(entry);
    b_vertMulti->GetEntry(entry);
}



void AnalysisBase::GetTriggerBranchesEntry(const Long64_t& entry)const
{
    b_triggerBits->GetEntry(entry);
    //b_triggerBitsTau->GetEntry(entry);
    //b_firedTriggers->GetEntry(entry); 
}



void AnalysisBase::GetCommonGenBranchesEntry(const Long64_t& entry)const
{
    // Check if branches' entry is already read
    if(commonGenObjects_){
        if(commonGenObjects_->valuesSet_) return;
        commonGenObjects_->valuesSet_ = true;
    }
    
    // Concerning physics objects
    b_allGenJets->GetEntry(entry);
    b_jetPartonFlavour->GetEntry(entry);
    b_associatedGenJet->GetEntry(entry);
    if(doJesJer_){
        b_associatedGenJetForMET->GetEntry(entry);
    }
    //if(b_jetAssociatedPartonPdgId)b_jetAssociatedPartonPdgId->GetEntry(entry);
    //if(b_jetAssociatedParton)b_jetAssociatedParton->GetEntry(entry);
}



void AnalysisBase::GetKinRecoBranchesEntry(const Long64_t& entry)const
{
    // Check if branches' entry is already read
    if(kinRecoObjects_){
        if(kinRecoObjects_->valuesSet_) return;
        kinRecoObjects_->valuesSet_ = true;
    }
    
    b_HypTop->GetEntry(entry);
    b_HypAntiTop->GetEntry(entry);
    b_HypLepton->GetEntry(entry);
    b_HypAntiLepton->GetEntry(entry);
    b_HypNeutrino->GetEntry(entry);
    b_HypAntiNeutrino->GetEntry(entry);
    b_HypB->GetEntry(entry);
    b_HypAntiB->GetEntry(entry);
    //b_HypWPlus->GetEntry(entry);
    //b_HypWMinus->GetEntry(entry);
    b_HypJet0index->GetEntry(entry);
    b_HypJet1index->GetEntry(entry);
}



void AnalysisBase::GetVertMultiTrueEntry(const Long64_t& entry)const
{
    b_vertMultiTrue->GetEntry(entry);
}



void AnalysisBase::GetWeightGeneratorEntry(const Long64_t& entry)const
{
    b_weightGenerator->GetEntry(entry);
}



void AnalysisBase::GetPDFEntry(const Long64_t& entry)const
{
    b_weightPDF->GetEntry(entry);
}



void AnalysisBase::SetTrueLevelDYChannel(const int dy)
{
    trueDYchannelCut_ = dy;
    if (dy) {
        std::cout << "Include true-level filter for Z decay to pdgid " << dy << "\n";
        
        //create function to check the DY decay channel
        checkZDecayMode_ = [&, dy](Long64_t entry) -> bool {
            b_ZDecayMode->GetEntry(entry);
            bool pass = false;
            for (const auto decayMode : *ZDecayMode_) {
                if ((dy == 15 && decayMode > 15110000) ||
                    (dy == 13 && decayMode == 1313) ||
                    (dy == 11 && decayMode == 1111))
                {
                    pass = true;
                    break;
                }
            }
            return pass;
        };
        
    } else {
        checkZDecayMode_ = nullptr;
    }
}



void AnalysisBase::GetTopDecayModeEntry(const Long64_t& entry)const
{
    b_TopDecayMode->GetEntry(entry);
}



void AnalysisBase::GetHiggsDecayModeEntry(const Long64_t& entry)const
{
    b_HiggsDecayMode->GetEntry(entry);
}



void AnalysisBase::GetTopSignalBranchesEntry(const Long64_t& entry)const
{
    // Check if branches' entry is already read
    if(topGenObjects_){
        if(topGenObjects_->valuesSet_) return;
        topGenObjects_->valuesSet_ = true;
    }
    
    b_GenMet->GetEntry(entry);
    b_GenTop->GetEntry(entry);
    b_GenAntiTop->GetEntry(entry);
    b_GenLepton->GetEntry(entry);
    b_GenAntiLepton->GetEntry(entry);
    //b_GenLeptonPdgId->GetEntry(entry);
    //b_GenAntiLeptonPdgId->GetEntry(entry);
    //b_GenTau->GetEntry(entry);
    //b_GenAntiTau->GetEntry(entry);
    b_GenNeutrino->GetEntry(entry);
    b_GenAntiNeutrino->GetEntry(entry);
    b_GenB->GetEntry(entry);
    b_GenAntiB->GetEntry(entry);
    //b_GenWPlus->GetEntry(entry);
    //b_GenWMinus->GetEntry(entry);
    //b_GenParticleP4->GetEntry(entry);
    //b_GenParticlePdgId->GetEntry(entry);
    //b_GenParticleStatus->GetEntry(entry);
    b_BHadJetIndex->GetEntry(entry);
    b_AntiBHadJetIndex->GetEntry(entry);
    b_BHadrons->GetEntry(entry);
    b_AntiBHadrons->GetEntry(entry);
    b_BHadronFromTopB->GetEntry(entry);
    b_AntiBHadronFromTopB->GetEntry(entry);
    b_BHadronVsJet->GetEntry(entry);
    b_AntiBHadronVsJet->GetEntry(entry);
    if(b_genBHadPlusMothersPdgId) b_genBHadPlusMothersPdgId->GetEntry(entry);
    if(b_genBHadPlusMothersStatus) b_genBHadPlusMothersStatus->GetEntry(entry);
    if(b_genBHadPlusMothersIndices) b_genBHadPlusMothersIndices->GetEntry(entry);
    if(b_genBHadPlusMothers) b_genBHadPlusMothers->GetEntry(entry);
    if(b_genBHadIndex) b_genBHadIndex->GetEntry(entry);
    if(b_genBHadFlavour) b_genBHadFlavour->GetEntry(entry);
    if(b_genBHadJetIndex) b_genBHadJetIndex->GetEntry(entry);
}



void AnalysisBase::GetHiggsSignalBranchesEntry(const Long64_t& entry)const
{
    // Check if branches' entry is already read
    if(higgsGenObjects_){
        if(higgsGenObjects_->valuesSet_) return;
        higgsGenObjects_->valuesSet_ = true;
    }
    
    b_GenH->GetEntry(entry);
    b_GenBFromH->GetEntry(entry);
    b_GenAntiBFromH->GetEntry(entry);
}



double AnalysisBase::getJetHT(const std::vector<int>& jetIndices, const VLV& jets)const
{
    double result = 0;
    for(const int index : jetIndices){
        const double pt = jets.at(index).pt();
        result += pt;
    }
    return result;
}



void AnalysisBase::CreateBinnedControlPlots(TH1* h_differential, TH1* h_control, const bool fromHistoList)
{
    auto &pair = (*binnedControlPlots_)[h_differential->GetName()];
    if(fromHistoList){
        HistoListReader histoList("HistoList");
        if(histoList.IsZombie()) { std::cout << "Need a HistoList to create binned control plots!\n"; exit(273); }
        pair.first = histoList.getPlotProperties(h_differential->GetName()).getClonedHistogram();
    }
    else{
        bool old = TH1::AddDirectoryStatus();
        TH1::AddDirectory(false);
        TH1* clone = static_cast<TH1*>(h_differential->Clone());
        TH1::AddDirectory(old);
        pair.first = clone;
    }
    std::string name = "bcp_";
    name.append(h_differential->GetName()).append("_bin_");
    //create maps if we are called for the first time with a certain h_differential
    if (pair.second.size() == 0) {
        for (int i = 0; i <= pair.first->GetNbinsX() + 1; ++i)
            pair.second.push_back(std::map<std::string, TH1*>());
    }
    //now really create the histograms
    for (int i = 0; i <= pair.first->GetNbinsX() + 1; ++i) {
        std::string binning = 
            i == 0 ? "underflow" :
            i == pair.first->GetNbinsX() + 1 ? "overflow" :
            ttbar::d2s(pair.first->GetBinLowEdge(i)) + " to " + ttbar::d2s(pair.first->GetBinLowEdge(i+1));
        binning = std::string(" (") + h_differential->GetName() + " " + binning + ")";
        std::string n = name + std::to_string(i) + "_" + h_control->GetName();
        pair.second[i][h_control->GetName()] = store(
            new TH1D(n.c_str(), (std::string(h_control->GetName())+binning).c_str(), 
                     h_control->GetNbinsX(), h_control->GetBinLowEdge(1), 
                     h_control->GetBinLowEdge(h_control->GetNbinsX()+1)));
    }
}



void AnalysisBase::FillBinnedControlPlot(TH1* h_differential, double binvalue, 
                                         TH1* h_control, double value, double weight)
{
    auto pair = (*binnedControlPlots_)[h_differential->GetName()];
    auto bin = pair.first->FindBin(binvalue);
    auto m = pair.second.at(bin);
    TH1* h = m[h_control->GetName()];
    if (!h) { 
        std::cerr << "Error: please CreateBinnedControlPlots for " << h_differential->GetName() 
            << " and " << h_control->GetName() << std::endl;
        exit(911);
    }
    h->Fill(value, weight);
}



void AnalysisBase::prepareKinRecoSF()
{
    // --> uncomment the following line to determine the Kin Reco SFs
    // --> then make && ./runNominalParallel.sh && ./Histo -t cp -p akr bkr step && ./kinRecoEfficienciesAndSF
//     weightKinFit=1; return;
    
    if (!isMC_) { weightKinFit_ = 1; return; }
    //SF for mass(top) = 100..300 GeV
    const static std::map<TString, double> sfNominal { {"ee", 0.9779}, {"emu", 0.9871}, {"mumu", 0.9879} };
    const static std::map<TString, double> sfUnc { {"ee", 0.0066}, {"emu", 0.0032}, {"mumu", 0.0056} };
    
    //SF for mass(top) = 173 GeV
//     const static std::map<TString, double> sfNominal { {"ee", 0.9696}, {"emu", 0.9732}, {"mumu", 0.9930} };
//     const static std::map<TString, double> sfUnc { {"ee", 0.0123}, {"emu", 0.0060}, {"mumu", 0.0105} };
    
    weightKinFit_ = sfNominal.at(channel_);
    if (systematic_ == "KIN_UP") weightKinFit_ += sfUnc.at(channel_);
    else if (systematic_ == "KIN_DOWN") weightKinFit_ -= sfUnc.at(channel_);
}



bool AnalysisBase::calculateKinReco(const int leptonIndex, const int antiLeptonIndex, const std::vector<int>& jetIndices,
                                    const VLV& allLeptons, const VLV& jets,
                                    const std::vector<double>& jetBTagCSV, const LV& met)
{
    // Clean the results of the kinematic reconstruction as stored in the nTuple
    if(useObjectStructs_){
        kinRecoObjects_->HypTop_->clear();
        kinRecoObjects_->HypAntiTop_->clear();
        kinRecoObjects_->HypLepton_->clear();
        kinRecoObjects_->HypAntiLepton_->clear();
        kinRecoObjects_->HypBJet_->clear();
        kinRecoObjects_->HypAntiBJet_->clear();
        kinRecoObjects_->HypNeutrino_->clear();
        kinRecoObjects_->HypAntiNeutrino_->clear();
        kinRecoObjects_->HypJet0index_->clear();
        kinRecoObjects_->HypJet1index_->clear();
        
        kinRecoObjects_->valuesSet_ = false;
    }
    else{
        HypTop_->clear();
        HypAntiTop_->clear();
        HypLepton_->clear();
        HypAntiLepton_->clear();
        HypBJet_->clear();
        HypAntiBJet_->clear();
        HypNeutrino_->clear();
        HypAntiNeutrino_->clear();
        HypJet0index_->clear();
        HypJet1index_->clear();
    }
    
    // The physics objects needed as input
    const LV& leptonMinus(allLeptons.at(leptonIndex));
    const LV& leptonPlus(allLeptons.at(antiLeptonIndex));
    VLV selectedJets;
    std::vector<double> btagValues;
    for(const int index : jetIndices){
        selectedJets.push_back(jets.at(index));
        btagValues.push_back(jetBTagCSV.at(index));
    }
    
    
    
    // 2 lines needed for OLD kinReco
    const auto& sols = GetKinSolutions(leptonMinus, leptonPlus, &selectedJets, &btagValues, &met);
    const int nSolution = sols.size();
    
    // 2 lines needed for NEW kinReco
//    const KinematicReconstruction new_topsol(leptonMinus, leptonPlus, &selectedJets, &btagValues, &met); //Option true - mass_loop ON; Option false - smearing ON; NO boolean option - weighted average
//    const int nSolution = new_topsol.GetNSol();
    
    
    if(nSolution == 0) return false;
    
    // 1 line needed for OLD kinReco
    const auto& sol = sols.at(0);
    
    // 1 line needed for NEW kinReco
//    const auto& sol = new_topsol.GetSol();
    
    // Fill the results of the on-the-fly kinematic reconstruction
    if(useObjectStructs_){
        kinRecoObjects_->HypTop_->push_back(ttbar::TLVtoLV(sol.top));
        kinRecoObjects_->HypAntiTop_->push_back(ttbar::TLVtoLV(sol.topBar));
        kinRecoObjects_->HypLepton_->push_back(ttbar::TLVtoLV(sol.lm));
        kinRecoObjects_->HypAntiLepton_->push_back(ttbar::TLVtoLV(sol.lp));
        kinRecoObjects_->HypBJet_->push_back(ttbar::TLVtoLV(sol.jetB));
        kinRecoObjects_->HypAntiBJet_->push_back(ttbar::TLVtoLV(sol.jetBbar));
        kinRecoObjects_->HypNeutrino_->push_back(ttbar::TLVtoLV(sol.neutrino));
        kinRecoObjects_->HypAntiNeutrino_->push_back(ttbar::TLVtoLV(sol.neutrinoBar));
        kinRecoObjects_->HypJet0index_->push_back(sol.jetB_index);
        kinRecoObjects_->HypJet1index_->push_back(sol.jetBbar_index);
        
        kinRecoObjects_->valuesSet_ = true;
    }
    else{
        HypTop_->push_back(ttbar::TLVtoLV(sol.top));
        HypAntiTop_->push_back(ttbar::TLVtoLV(sol.topBar));
        HypLepton_->push_back(ttbar::TLVtoLV(sol.lm));
        HypAntiLepton_->push_back(ttbar::TLVtoLV(sol.lp));
        HypBJet_->push_back(ttbar::TLVtoLV(sol.jetB));
        HypAntiBJet_->push_back(ttbar::TLVtoLV(sol.jetBbar));
        HypNeutrino_->push_back(ttbar::TLVtoLV(sol.neutrino));
        HypAntiNeutrino_->push_back(ttbar::TLVtoLV(sol.neutrinoBar));
        HypJet0index_->push_back(sol.jetB_index);
        HypJet1index_->push_back(sol.jetBbar_index);
    }
    
    //check for strange events
    if (false && HypTop_->size()) {
        double Ecm = (HypTop_->at(0) + HypAntiTop_->at(0) 
                        + HypLepton_->at(0) + HypAntiLepton_->at(0)
                        + HypNeutrino_->at(0) + HypAntiNeutrino_->at(0)).E();
        //does event's CM energy exceed LHC's energy?
        if (Ecm > 8000) {
            static int seCounter = 0;
            std::cout << "\n" << ++seCounter << " - Strange event: " << runNumber_<<":"<<lumiBlock_<<":"<<eventNumber_
            << "\ntop:  " << HypTop_->at(0) << " tbar: " << HypAntiTop_->at(0)
            << "\nNeutrino:  " << HypNeutrino_->at(0) << " NeutrinoBar: " << HypAntiNeutrino_->at(0)
            <<"\n";
        }
    }
    
    return true;
}



const std::string AnalysisBase::topDecayModeString()const
{
    const std::vector<std::string> WMode {"unknown", "hadronic", "e", "mu", "tau->hadron", "tau->e", "tau->mu"};
    int top = topDecayMode_ / 10;
    int antitop = topDecayMode_ % 10;
    std::string result = WMode[top] + "/" + WMode[antitop];
    return result;    
}



void AnalysisBase::prepareJER_JES()
{    
    const TString pathToFile(ttbar::DATA_PATH() + "/Fall12_V7_DATA_UncertaintySources_AK5PFchs.txt");
    doJesJer_ = false;
    if (systematic_ == "JES_UP" || systematic_ == "JES_DOWN") {
        jetCorrectionUncertainty_ = new JetCorrectionUncertainty(JetCorrectorParameters(pathToFile.Data(), "Total"));
        doJesJer_ = true;
    }
    if (systematic_ == "JER_UP" || systematic_ == "JER_DOWN") {
        doJesJer_ = true;
    }
}



void AnalysisBase::applyJER_JES()const
{
    if(systematic_=="JER_UP" || systematic_=="JER_DOWN")
        this->applyJerSystematics(jets_, jetsForMET_, met_,
                                  jetJERSF_, jetForMETJERSF_,
                                  associatedGenJet_, associatedGenJetForMET_);
    
    if (systematic_ == "JES_UP" || systematic_ == "JES_DOWN")
        this->applyJesSystematics(jets_, jetsForMET_, met_);
}



void AnalysisBase::applyJerSystematics(VLV* jets, VLV* jetsForMET, LV* met,
                                       const std::vector<double>* jetJERSF, const std::vector<double>* jetForMETJERSF,
                                       const VLV* associatedGenJet, const VLV* associatedGenJetForMET)const
{
    // Set the eta ranges and the corresponding scale factors for Jet Energy Resolution
    constexpr double ResolutionEtaRange[5] = {0.5, 1.1, 1.7, 2.3, 10};
    double ResolutionEtaScaleFactor[5];//nom = {1.052, 1.057, 1.096, 1.134, 1.288};
    if(systematic_ == "JER_UP"){
        ResolutionEtaScaleFactor[0] = 1.115;
        ResolutionEtaScaleFactor[1] = 1.114;
        ResolutionEtaScaleFactor[2] = 1.161;
        ResolutionEtaScaleFactor[3] = 1.228;
        ResolutionEtaScaleFactor[4] = 1.488;
    }
    else if(systematic_ == "JER_DOWN"){
        ResolutionEtaScaleFactor[0] = 0.990;
        ResolutionEtaScaleFactor[1] = 1.001;
        ResolutionEtaScaleFactor[2] = 1.032;
        ResolutionEtaScaleFactor[3] = 1.042;
        ResolutionEtaScaleFactor[4] = 1.089;
    }
    else{
        std::cerr<<"ERROR in applyJerSystematics()! Requested systematic not allowed: "<<systematic_
                 <<"\n...break\n"<<std::endl;
        exit(81);
    }
    
    // This first loop will correct the jet collection that is used for jet selections
    for(size_t i = 0; i < jets->size(); ++i){
        size_t jetEtaBin = 0;
        for(size_t j = 0; j < 5; ++j){
            if(std::fabs(jets->at(i).eta()) < ResolutionEtaRange[j]){
                jetEtaBin = j;
                break;
            }
        }

        if(jetJERSF_->at(i) != 0.){
            jets->at(i) *= 1./jetJERSF->at(i);
            
            // FIXME: should this factor really be =0. in case no associatedGenJet is found ?
            double factor = 0.;
            if(associatedGenJet->at(i).pt() != 0.) factor = 1. + (ResolutionEtaScaleFactor[jetEtaBin] - 1.)*(1. - (associatedGenJet->at(i).pt()/jets->at(i).pt()));
            if(jetJERSF->at(i) == 1.) factor = 1.;
            
            jets->at(i) *= factor;
        }
    }

    // This second loop will correct the jet collection that is used to modify the MET
    double JEC_dpX =0.;
    double JEC_dpY =0.;
    for(size_t i = 0; i < jetsForMET->size(); ++i){
        size_t jetEtaBin = 0;
        for(size_t j = 0; j < 5; ++j){
            if(std::fabs(jetsForMET->at(i).eta()) < ResolutionEtaRange[j]){
                jetEtaBin = j;
                break;
            }
        }
        
        if(jetForMETJERSF->at(i) != 0.){
            const double dpX = jetsForMET->at(i).px();
            const double dpY = jetsForMET->at(i).py();
            jetsForMET->at(i) *= 1./jetForMETJERSF->at(i);
            
            // FIXME: should this factor really be =0. in case no associatedGenJet is found ?
            double factor = 0.;
            if(associatedGenJetForMET->at(i).pt() != 0.) factor = 1. + (ResolutionEtaScaleFactor[jetEtaBin] - 1.)*(1. - (associatedGenJetForMET->at(i).pt()/jetsForMET->at(i).pt()));
            if(jetForMETJERSF->at(i) == 1.) factor = 1.;
            
            jetsForMET->at(i) *= factor;
            JEC_dpX += jetsForMET->at(i).px() - dpX;
            JEC_dpY += jetsForMET->at(i).py() - dpY;
        }
    }
    
    // Adjust the MET
    const double scaledMETPx = met->px() - JEC_dpX;
    const double scaledMETPy = met->py() - JEC_dpY;
    met->SetPt(std::sqrt(scaledMETPx*scaledMETPx + scaledMETPy*scaledMETPy));
}



void AnalysisBase::applyJesSystematics(VLV* jets, VLV* jetsForMET, LV* met)const
{
    const bool varyUp = systematic_=="JES_UP" ? true : false;
    if(!varyUp && systematic_!="JES_DOWN"){
        std::cerr<<"ERROR in applyJesSystematics()! Requested systematic not allowed: "<<systematic_
                 <<"\n...break\n"<<std::endl;
        exit(82);
    }
    
    // This first loop will correct the jet collection that is used for jet selections
    for(size_t i = 0; i < jets->size(); ++i){
        jetCorrectionUncertainty_->setJetPt(jets->at(i).pt()); 
        jetCorrectionUncertainty_->setJetEta(jets->at(i).eta());
        const double dunc = jetCorrectionUncertainty_->getUncertainty(true);
        
        if(varyUp) jets->at(i) *= 1. + dunc;
        else jets->at(i) *= 1. - dunc;
    }

    // This second loop will correct the jet collection that is used for modifying MET
    double JEC_dpX =0.;
    double JEC_dpY =0.;
    for(size_t i = 0; i < jetsForMET->size(); ++i){

        const double dpX = jetsForMET->at(i).px();
        const double dpY = jetsForMET->at(i).py();

        jetCorrectionUncertainty_->setJetPt(jetsForMET->at(i).pt()); 
        jetCorrectionUncertainty_->setJetEta(jetsForMET->at(i).eta());
        const double dunc = jetCorrectionUncertainty_->getUncertainty(true);

        if(varyUp) jetsForMET->at(i) *= 1. + dunc;
        else jetsForMET->at(i) *= 1. - dunc;

        JEC_dpX += jetsForMET->at(i).px() - dpX;
        JEC_dpY += jetsForMET->at(i).py() - dpY;
    }

    // Adjust the MET
    const double scaledMETPx = met->px() - JEC_dpX;
    const double scaledMETPy = met->py() - JEC_dpY;
    met->SetPt(std::sqrt(scaledMETPx*scaledMETPx + scaledMETPy*scaledMETPy));
}



bool AnalysisBase::failsDrellYanGeneratorSelection(const Long64_t& entry)const
{
    if(checkZDecayMode_ && !checkZDecayMode_(entry)) return true;
    return false;
}



bool AnalysisBase::failsTopGeneratorSelection(const Long64_t& entry)const
{
    if(!isTtbarPlusTauSample_) return false;
    GetTopDecayModeEntry(entry);
    
    //decayMode contains the decay of the top (*10) + the decay of the antitop
    //1=hadron, 2=e, 3=mu, 4=tau->hadron, 5=tau->e, 6=tau->mu
    //i.e. 23 == top decays to e, tbar decays to mu
    bool isViaTau = topDecayMode_ > 40 || (topDecayMode_ % 10 > 4);
    bool isCorrectChannel = false;
    switch (channelPdgIdProduct_) {
        case -11*13: isCorrectChannel = topDecayMode_ == 23 || topDecayMode_ == 32 //emu prompt
                        || topDecayMode_ == 53 || topDecayMode_ == 35 //e via tau, mu prompt
                        || topDecayMode_ == 26 || topDecayMode_ == 62 //e prompt, mu via tau
                        || topDecayMode_ == 56 || topDecayMode_ == 65; //both via tau
                        break;
        case -11*11: isCorrectChannel = topDecayMode_ == 22  //ee prompt
                        || topDecayMode_ == 52 || topDecayMode_ == 25 //e prompt, e via tau
                        || topDecayMode_ == 55; break; //both via tau
        case -13*13: isCorrectChannel = topDecayMode_ == 33  //mumu prompt
                        || topDecayMode_ == 36 || topDecayMode_ == 63 //mu prompt, mu via tau
                        || topDecayMode_ == 66; break; //both via tau
        default: std::cerr << "Invalid channel! Product = " << channelPdgIdProduct_ << "\n";
    };
    bool isBackgroundInSignalSample = !isCorrectChannel || isViaTau;
    if(runViaTau_ != isBackgroundInSignalSample) return true;
    return false;
}



double AnalysisBase::madgraphWDecayCorrection(const Long64_t& entry)const
{
    if(!correctMadgraphBR_) return 1.;
    GetTopDecayModeEntry(entry);
    
    // We must correct for the madGraph branching fraction being 1/9 for dileptons (PDG average is .108)
    if(topDecayMode_ == 11){ //all hadronic decay
        return (0.676*1.5) * (0.676*1.5);
    }
    else if(topDecayMode_< 20 || ( topDecayMode_ % 10 == 1)){ //semileptonic Decay
        return (0.108*9.) * (0.676*1.5);
    }
    else{ //dileptonic decay (including taus!)
        return (0.108*9.) * (0.108*9.);
    }
}



double AnalysisBase::weightPileup(const Long64_t& entry)const
{
    if(!isMC_ || !puReweighter_)return 1.;
    this->GetVertMultiTrueEntry(entry);
    return puReweighter_->getPUweight(vertMultiTrue_);
}



double AnalysisBase::weightGenerator(const Long64_t& entry)const
{
    if(!isMC_) return 1.;
    GetWeightGeneratorEntry(entry);
    return weightGenerator_;
}



double AnalysisBase::weightTopPtReweighting(const double& topPt, const double& antiTopPt)const
{
    if(!isMC_ && !isTopSignal_ && !isTtbarSample_) return 1.;
    return TMath::Sqrt(this->topPtReweightValue(topPt) * this->topPtReweightValue(antiTopPt));
}



double AnalysisBase::weightLeptonSF(const int leadingLeptonIndex, const int nLeadingLeptonIndex,
                                    const VLV& allLeptons, const std::vector<int>& lepPdgId)const
{
    if(!isMC_) return 1.;
    if(leadingLeptonIndex<0 || nLeadingLeptonIndex<0) return 1.;
    return leptonScaleFactors_->getLeptonIDSF(leadingLeptonIndex, nLeadingLeptonIndex, allLeptons, lepPdgId);
}



double AnalysisBase::weightTriggerSF(const int leptonXIndex, const int leptonYIndex,
                                     const VLV& allLeptons)const
{
    if(!isMC_) return 1.;
    if(leptonXIndex<0 || leptonYIndex<0) return 1.;
    return triggerScaleFactors_->getTriggerSF(leptonXIndex, leptonYIndex, allLeptons, channel_);
}



double AnalysisBase::weightBtagSF(const std::vector<int>& jetIndices,
                                  const VLV& jets, const std::vector<int>& jetPartonFlavour)const
{
    if(!isMC_) return 1.;
    if(btagScaleFactors_->makeEfficiencies()) return 1.;
    return btagScaleFactors_->calculateBtagSF(jetIndices, jets,
                                              jetPartonFlavour, static_cast<std::string>(channel_));
}



bool AnalysisBase::hasLeptonPair(const int leadingLeptonIndex, const int nLeadingLeptonIndex,
                                 const std::vector<int>& lepPdgId)const
{
    bool hasLeptonPair(false);
    if(leadingLeptonIndex!=-1 && nLeadingLeptonIndex!=-1){
        // Check if lepton pair is correct flavour combination for the specified analysis channel (ee, emu, mumu)
        const int pdgIdProduct = lepPdgId.at(leadingLeptonIndex) * lepPdgId.at(nLeadingLeptonIndex);
        if(pdgIdProduct == channelPdgIdProduct_) hasLeptonPair = true;
    }
    return hasLeptonPair;
}



bool AnalysisBase::failsDileptonTrigger(const Long64_t& entry)const
{
    this->GetTriggerBranchesEntry(entry);
    
    //our triggers (bits: see the ntuplewriter!)
    constexpr int mumuTriggers = 0x8 + 0x20; //17/8 + 17Tr8
    constexpr int emuTriggers = 0x2000 + 0x4000;
    constexpr int eeTriggers = 0x40000;

    if (((triggerBits_ & mumuTriggers) && channelPdgIdProduct_ == -13*13)     // mumu triggers in rightmost byte
        || ((triggerBits_ & emuTriggers) && channelPdgIdProduct_ == -11*13)   // emu in 2nd byte
        || ((triggerBits_ & eeTriggers) && channelPdgIdProduct_ == -11*11))  // ee in 3rd byte
    {
        return false;
    }
    return true;
}



bool AnalysisBase::makeBtagEfficiencies()const
{
    return btagScaleFactors_->makeEfficiencies() && isTtbarSample_ && isTopSignal_;
}



double AnalysisBase::topPtReweightValue(const double& pt)const
{
    return TMath::Exp(0.156-0.00137*pt);
}










const RecoObjects& AnalysisBase::getRecoObjects(const Long64_t& entry)const
{
    if(recoObjects_->valuesSet_) return *recoObjects_;
    
    this->GetRecoBranchesEntry(entry);
    
    if(isMC_ && doJesJer_){
        
        // Get references for all relevant reco objects which are modified by JER/JES systematics
        VLV* jets = recoObjects_->jets_;
        VLV* jetsForMET = recoObjects_->jetsForMET_;
        LV* met = recoObjects_->met_;
        
        if(systematic_=="JER_UP" || systematic_=="JER_DOWN"){
            // Get references for all relevant reco objects which are NOT modified
            const std::vector<double>* jetJERSF = recoObjects_->jetJERSF_;
            const std::vector<double>* jetForMETJERSF = recoObjects_->jetForMETJERSF_;
            
            // Get references for all relevant gen objects which are NOT modified
            if(!commonGenObjects_->valuesSet_) this->GetCommonGenBranchesEntry(entry);
            const VLV* associatedGenJet = commonGenObjects_->associatedGenJet_;
            const VLV* associatedGenJetForMet = commonGenObjects_->associatedGenJetForMET_;
            
            this->applyJerSystematics(jets, jetsForMET, met,
                                      jetJERSF, jetForMETJERSF,
                                      associatedGenJet, associatedGenJetForMet);
        }
        
        if(systematic_=="JES_UP" || systematic_=="JES_DOWN"){
            this->applyJesSystematics(jets, jetsForMET, met);
        }
    }
    
    return *recoObjects_;
}





const CommonGenObjects& AnalysisBase::getCommonGenObjects(const Long64_t& entry)const
{
    if(!isMC_) return *commonGenObjects_;
    if(commonGenObjects_->valuesSet_) return *commonGenObjects_;
    
    this->GetCommonGenBranchesEntry(entry);
    return *commonGenObjects_;
}



const TopGenObjects& AnalysisBase::getTopGenObjects(const Long64_t& entry)const
{
    if(!isTopSignal_) return *topGenObjects_;
    if(topGenObjects_->valuesSet_) return *topGenObjects_;
    
    this->GetTopSignalBranchesEntry(entry);
    return *topGenObjects_;
}



const HiggsGenObjects& AnalysisBase::getHiggsGenObjects(const Long64_t& entry)const
{
    if(!isHiggsSignal_) return *higgsGenObjects_;
    if(higgsGenObjects_->valuesSet_) return *higgsGenObjects_;
    
    this->GetHiggsSignalBranchesEntry(entry);
    return *higgsGenObjects_;
}



const KinRecoObjects& AnalysisBase::getKinRecoObjects(const Long64_t& entry)const
{
    if(kinRecoObjects_->valuesSet_) return *kinRecoObjects_;
    if(kinRecoObjects_->HypTop_->size() > 0) this->GetKinRecoBranchesEntry(entry);
    
    return *kinRecoObjects_;
}



const KinRecoObjects& AnalysisBase::getKinRecoObjectsOnTheFly(const int leptonIndex, const int antiLeptonIndex, const std::vector<int>& jetIndices,
                                                              const VLV& allLeptons, const VLV& jets, const std::vector<double>& jetBTagCSV,
                                                              const LV& met)
{
    this->calculateKinReco(leptonIndex, antiLeptonIndex, jetIndices, allLeptons, jets, jetBTagCSV, met);
    
    return *kinRecoObjects_;
}



void AnalysisBase::resetObjectStructEntry()const
{
    recoObjects_->valuesSet_ = false;
    commonGenObjects_->valuesSet_ = false;
    topGenObjects_->valuesSet_ = false;
    higgsGenObjects_->valuesSet_ = false;
    kinRecoObjects_->valuesSet_ = false;
}















