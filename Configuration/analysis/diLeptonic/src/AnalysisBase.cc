#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <iomanip>

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

#include "AnalysisBase.h"
#include "HistoListReader.h"
#include "utils.h"
#include "KinReco.h"
#include "JetCorrectorParameters.h"
#include "JetCorrectionUncertainty.h"
#include "PUReweighter.h"







/// Folder for basic analysis output
constexpr const char* BaseDIR = "selectionRoot";

/// Folder for b-tag efficiency file storage
constexpr const char* BTagEffDIR = "selectionRoot/BTagEff";







AnalysisBase::AnalysisBase(TTree*):
samplename_(""), channel_(""), systematic_(""),
isMC_(false), isTopSignal_(false), isHiggsSignal_(false),
isTtbarPlusTauSample_(false), correctMadgraphBR_(false),
channelPdgIdProduct_(0), trueDYchannelCut_(0),
checkZDecayMode_(nullptr), outputfilename_(""),
runViaTau_(false),
pureweighter_(nullptr),
doJesJer_(false), weightKinFit_(0),
binnedControlPlots_(0),
chain_(0), h_weightedEvents(0),
unc_(nullptr), btagFile_(""),
h_bjets(0), h_cjets(0), h_ljets(0),
h_btaggedjets(0), h_ctaggedjets(0), h_ltaggedjets(0),
bEff(0), cEff(0), lEff(0),
h_TrigSFeta(0), h_MuonIDSFpteta(0), h_ElectronIDSFpteta(0),
btag_ptmedian_(0), btag_etamedian_(0),
eventCounter_(0)
{
    this->clearBranches();
    this->clearBranchVariables();
}



/** Prepare some variables before going to the event loop
 * 
 * This function is used to calculate all scale factors and
 * other information that is the same for each event.
 * 
 * For some event-dependent scale factors, histograms for a 
 * lookup are read.
 */
void AnalysisBase::Begin(TTree*)
{
    /// WARNING! In general do not make changes here, but in your analysis' Begin function

    TSelector::Begin(0);
    
    bEff = 0;
    cEff = 0;
    lEff = 0;
    h_TrigSFeta = 0;
    h_MuonIDSFpteta = 0;
    h_ElectronIDSFpteta = 0;
    btag_ptmedian_ = 0;
    btag_etamedian_ = 0;
    h_bjets = 0;
    h_cjets = 0;
    h_ljets = 0;
    h_btaggedjets = 0;
    h_ctaggedjets = 0;
    h_ltaggedjets = 0;
    eventCounter_ = 0;
}



void AnalysisBase::SlaveBegin(TTree*)
{
    /// WARNING! In general do not make changes here, but in your analysis' SlaveBegin function

    TSelector::SlaveBegin(0);
    
    binnedControlPlots_ = new std::map<std::string, std::pair<TH1*, std::vector<std::map<std::string, TH1*> > > >;
}



void AnalysisBase::SlaveTerminate()
{
    /// WARNING! In general do not make changes here, but in your analysis' SlaveTerminate function

    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.
    
    for (auto it = binnedControlPlots_->begin(); it != binnedControlPlots_->end(); ++it) {
        delete (*it).second.first;
    }
    delete binnedControlPlots_;
}



Bool_t AnalysisBase::Process(Long64_t)
{
    /// WARNING! In general do not make changes here, but in your analysis' Process function
    
    if ( ++eventCounter_ % 100000 == 0 ) std::cout << "Event Counter: " << eventCounter_ << std::endl;
    return kTRUE;
}



void AnalysisBase::Terminate()
{
    /// WARNING! In general do not make changes here, but in your analysis' Terminate function
    
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.
    
    
    // Open output file for writing
    std::string f_savename = this->assignFolder(BaseDIR, channel_, systematic_);
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
    delete unc_;
    unc_ = nullptr;
}



void AnalysisBase::Init(TTree *tree)
{
    /// WARNING! In general do not make changes here, but in your analysis' Init function
    
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



void AnalysisBase::SetBTagFile(TString btagFile)
{
    btagFile_ = btagFile;
}



void AnalysisBase::SetChannel(TString channel)
{
    channel_ = channel;
    channelPdgIdProduct_ = 
        channel == "ee" ? -11*11
        : channel == "emu" ? -11*13
        : -13*13;
}



void AnalysisBase::SetTopSignal(bool isTopSignal)
{
    isTopSignal_ = isTopSignal;
}



void AnalysisBase::SetHiggsSignal(const bool higgsSignal)
{
    isHiggsSignal_ = higgsSignal;
}



void AnalysisBase::SetSystematic(TString systematic)
{
    systematic_ = systematic;
}



void AnalysisBase::SetSamplename(TString samplename, TString systematic_from_file)
{
    samplename_ = samplename;
    isTtbarPlusTauSample_ = samplename.BeginsWith("ttbar") && !samplename.BeginsWith("ttbarhiggs") &&
                            !(samplename=="ttbarw") && !(samplename=="ttbarz") &&
                            !samplename.BeginsWith("ttbarbg");
    correctMadgraphBR_ = samplename.BeginsWith("ttbar") && !systematic_from_file.Contains("SPIN") &&
                        !systematic_from_file.Contains("POWHEG") && !systematic_from_file.Contains("MCATNLO");
}



void AnalysisBase::SetMC(bool isMC)
{
    isMC_ = isMC;
}



void AnalysisBase::SetOutputfilename(TString outputfilename)
{
    outputfilename_ = outputfilename;
}



void AnalysisBase::SetWeightedEvents(TH1* weightedEvents)
{
    h_weightedEvents = weightedEvents;
}



void AnalysisBase::SetRunViaTau(bool runViaTau)
{
    runViaTau_ = runViaTau;
    if (runViaTau) isTopSignal_ = 0;
}



void AnalysisBase::SetPUReweighter(PUReweighter* pu)
{
    pureweighter_ = pu;
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
    b_triggerBits = 0;
    b_triggerBitsTau = 0;
    b_firedTriggers = 0;
    b_vertMulti = 0;
    
    
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
    b_genParticlePdg = 0;
    b_genParticleStatus = 0;
    b_genParticleIndices = 0;
    b_genParticle = 0;
    b_bHadIndex = 0;
    b_bHadFlavour = 0;
    b_bHadJetIndex = 0;
    
    
    // nTuple branches for Higgs signal samples on generator level
    b_GenH = 0;
    b_GenBFromH = 0;
    b_GenAntiBFromH = 0;
}



void AnalysisBase::clearBranchVariables()
{
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
    genParticlePdg_ = 0;
    genParticleStatus_ = 0;
    genParticleIndices_ = 0;
    genParticle_ = 0;
    bHadIndex_ = 0;
    bHadFlavour_ = 0;
    bHadJetIndex_ = 0;
    
    
    // Set values to null for Higgs signal sample branches
    GenH_ = 0;
    GenBFromH_ = 0;
    GenAntiBFromH_ = 0;
}



void AnalysisBase::SetRecoBranchAddresses()
{
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
    chain_->SetBranchAddress("triggerBits", &triggerBits_, &b_triggerBits);
    //chain_->SetBranchAddress("triggerBitsTau", &triggerBitsTau_, &b_triggerBitsTau);
    //chain_->SetBranchAddress("firedTriggers", &firedTriggers_, &b_firedTriggers);
    chain_->SetBranchAddress("vertMulti", &vertMulti_, &b_vertMulti);
}



void AnalysisBase::SetCommonGenBranchAddresses()
{
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
    if(chain_->GetBranch("genParticlePdg")) // need to check whether branch exists
        chain_->SetBranchAddress("genParticlePdg", &genParticlePdg_, &b_genParticlePdg);
    if(chain_->GetBranch("genParticleStatus")) // need to check whether branch exists
        chain_->SetBranchAddress("genParticleStatus", &genParticleStatus_, &b_genParticleStatus);
    if(chain_->GetBranch("genParticleIndices")) // need to check whether branch exists
        chain_->SetBranchAddress("genParticleIndices", &genParticleIndices_, &b_genParticleIndices);
    if(chain_->GetBranch("genParticle")) // need to check whether branch exists
        chain_->SetBranchAddress("genParticle", &genParticle_, &b_genParticle);
    if(chain_->GetBranch("bHadIndex")) // need to check whether branch exists
        chain_->SetBranchAddress("bHadIndex", &bHadIndex_, &b_bHadIndex);
    if(chain_->GetBranch("bHadFlavour")) // need to check whether branch exists
        chain_->SetBranchAddress("bHadFlavour", &bHadFlavour_, &b_bHadFlavour);
    if(chain_->GetBranch("bHadJetIndex")) // need to check whether branch exists
        chain_->SetBranchAddress("bHadJetIndex", &bHadJetIndex_, &b_bHadJetIndex);
}



void AnalysisBase::SetHiggsSignalBranchAddresses()
{
    chain_->SetBranchAddress("GenH", &GenH_, &b_GenH);
    chain_->SetBranchAddress("GenBFromH", &GenBFromH_, &b_GenBFromH);
    chain_->SetBranchAddress("GenAntiBFromH", &GenAntiBFromH_, &b_GenAntiBFromH);
}



void AnalysisBase::GetRecoBranchesEntry(Long64_t& entry)
{    
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
    if(b_jetChargeGlobalPtWeighted)b_jetChargeGlobalPtWeighted->GetEntry(entry);
    if(b_jetChargeRelativePtWeighted)b_jetChargeRelativePtWeighted->GetEntry(entry);
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
    //b_recoInChannel
    b_triggerBits->GetEntry(entry);
    //b_triggerBitsTau
    //b_firedTriggers
    b_vertMulti->GetEntry(entry);
}



void AnalysisBase::GetCommonGenBranchesEntry(Long64_t& entry)
{
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



void AnalysisBase::GetKinRecoBranchesEntry(Long64_t& entry){
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



void AnalysisBase::GetVertMultiTrueEntry(Long64_t& entry)
{
    b_vertMultiTrue->GetEntry(entry);
}



void AnalysisBase::GetWeightGeneratorEntry(Long64_t& entry)
{
    b_weightGenerator->GetEntry(entry);
}



void AnalysisBase::GetPDFEntry(Long64_t& entry){
    b_weightPDF->GetEntry(entry);
}



void AnalysisBase::SetTrueLevelDYChannel(int dy)
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



void AnalysisBase::GetTopDecayModeEntry(Long64_t& entry)
{
    b_TopDecayMode->GetEntry(entry);
}



void AnalysisBase::GetHiggsDecayModeEntry(Long64_t& entry)
{
    b_HiggsDecayMode->GetEntry(entry);
}



void AnalysisBase::GetTopSignalBranchesEntry(Long64_t& entry)
{
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
    if(b_genParticlePdg) b_genParticlePdg->GetEntry(entry);
    if(b_genParticleStatus) b_genParticleStatus->GetEntry(entry);
    if(b_genParticleIndices) b_genParticleIndices->GetEntry(entry);
    if(b_genParticle) b_genParticle->GetEntry(entry);
    if(b_bHadIndex) b_bHadIndex->GetEntry(entry);
    if(b_bHadFlavour) b_bHadFlavour->GetEntry(entry);
    if(b_bHadJetIndex) b_bHadJetIndex->GetEntry(entry);
}



void AnalysisBase::GetHiggsSignalBranchesEntry(Long64_t& entry)
{
    b_GenH->GetEntry(entry);
    b_GenBFromH->GetEntry(entry);
    b_GenAntiBFromH->GetEntry(entry);
}



/** determine indices of the two selected leptons in the analysis:
 * 
 * @param LeadLeptonNumber (output) the pt-leading lepton index
 * @param NLeadLeptonNumber (output) the second leading lepton index
 * 
 * @return true iff a the function was able to find a lepton pair
 */
bool AnalysisBase::getLeptonPair(size_t &LeadLeptonNumber, size_t &NLeadLeptonNumber)
{
    //find opposite-charge leading two leptons
    //the first lepton is always at index 0 because we only have two different charges
    
    // ---> this would be true if the electrons and muons had all cuts applied
    auto leptonPassesCut = [](const LV &lep){ return std::abs(lep.eta()) < 2.4 && lep.pt() > 20;};
    
    //find first lepton:
    for (LeadLeptonNumber = 0; LeadLeptonNumber < leptons_->size(); ++LeadLeptonNumber) {
        if (leptonPassesCut(leptons_->at(LeadLeptonNumber))) break;
    }
    
    //find second lepton
    for (size_t i = LeadLeptonNumber + 1; i < leptons_->size(); ++i) {
        if (!leptonPassesCut(leptons_->at(i))) continue;
        int product = lepPdgId_->at(LeadLeptonNumber) * lepPdgId_->at(i);
        if (product < 0) {
            NLeadLeptonNumber = i;
            return product == channelPdgIdProduct_;
        }            
    }
    
    return false;
}



double AnalysisBase::get2DSF(TH2* histo, double x, double y)
{
    int xbin, ybin, dummy;
    histo->GetBinXYZ(histo->FindBin(x, y), xbin, ybin, dummy);
    //overflow to last bin
    xbin = std::min(xbin, histo->GetNbinsX());
    ybin = std::min(ybin, histo->GetNbinsY());
    return histo->GetBinContent(xbin, ybin);
}



double AnalysisBase::getJetHT(const VLV& jet, int pt_cut)
{
    double result = 0;
    for ( size_t i = 0; i < jet.size(); ++i ) {
        double pt = jet.at(i).Pt();
        if (pt < pt_cut) break;
        result += pt;
    }
    return result;
}



void AnalysisBase::prepareTriggerSF()
{
    h_TrigSFeta = nullptr;
    
    TFile trigEfficiencies(DATA_PATH() + "/triggerSummary_" + channel_ + ".root");
    if (trigEfficiencies.IsZombie()) {
        std::cout << "Trigger efficiencies not found. Assuming ScaleFactor = 1.\n";
        std::cout << "Currently triggerEfficieny files can be found in diLeptonic/data folder\n\n";
        return;
    }
    
    //Right now pT efficiency flat ==> Not used
    h_TrigSFeta = dynamic_cast<TH2*>(trigEfficiencies.Get("scalefactor eta2d with syst"));
    if ( !h_TrigSFeta ) {
        std::cout<<"TH2 >>TH scalefactor eta<< is not in the file "<<trigEfficiencies.GetName()<<"\n";
        return;
    }
    
    if (systematic_.BeginsWith("TRIG_")) {
        double factor = systematic_.EndsWith("_UP") ? 1 : -1;
        for (int i = 1; i <= h_TrigSFeta->GetNbinsX(); ++i) {
            for (int j = 1; j <= h_TrigSFeta->GetNbinsY(); ++j) {
                h_TrigSFeta->SetBinContent(i, j,
                    h_TrigSFeta->GetBinContent(i,j) + factor*h_TrigSFeta->GetBinError(i,j));
            }
        }
    }
    
    h_TrigSFeta->SetDirectory(0);
    trigEfficiencies.Close();
}



double AnalysisBase::getTriggerSF(const LV& lep1, const LV& lep2) {
    
    //For 'ee' and 'mumu' channels Xaxis of the 2D plots is the highest pT lepton
    // for the 'emu' channel Xaxis is the electron and Y axis muon
    
    if (!h_TrigSFeta) return 1;
    return get2DSF(h_TrigSFeta, std::abs(lep1.eta()), std::abs(lep2.eta()));
}



double AnalysisBase::getLeptonIDSF(const LV& lep1, const LV& lep2, int lep1pdgId, int lep2pdgId) {
    if (!h_MuonIDSFpteta || !h_ElectronIDSFpteta) return 1;
    if (std::abs(lep1pdgId)==11 && std::abs(lep2pdgId)==11) return get2DSF(h_ElectronIDSFpteta, lep1.Eta(), lep1.pt()) * get2DSF(h_ElectronIDSFpteta, lep2.Eta(), lep2.pt());
    else if (std::abs(lep1pdgId)==13 && std::abs(lep2pdgId)==13) return get2DSF(h_MuonIDSFpteta, lep1.Eta(), lep1.pt()) * get2DSF(h_MuonIDSFpteta, lep2.Eta(), lep2.pt());
    else if (std::abs(lep1pdgId)==13 && std::abs(lep2pdgId)== 11) return get2DSF(h_MuonIDSFpteta, lep1.Eta(), lep1.pt()) * get2DSF(h_ElectronIDSFpteta, lep2.Eta(), lep2.pt());
    else return get2DSF(h_ElectronIDSFpteta, lep1.Eta(), lep1.pt())
        * get2DSF(h_MuonIDSFpteta, lep2.Eta(), lep2.pt());
}



void AnalysisBase::prepareLeptonIDSF() {
    h_MuonIDSFpteta = nullptr;
    h_ElectronIDSFpteta = nullptr;
    
    TFile MuonEfficiencies(DATA_PATH() + "/MuonSFtop12028.root");
    if (MuonEfficiencies.IsZombie()) {
        std::cout << "Muon Id/Iso efficiencies not found. Assuming ScaleFactor = 1.\n";
///        std::cout << "Currently triggerEfficieny files can be found in the HEAD version of diLeptonic folder\n\n";
        return;
    }

    TFile ElecEfficiencies(DATA_PATH() + "/ElectronSFtop12028.root");
    if (ElecEfficiencies.IsZombie()) {
        std::cout << "Electron Id/Iso efficiencies not found. Assuming ScaleFactor = 1.\n";
///        std::cout << "Currently triggerEfficieny files can be found in the HEAD version of diLeptonic folder\n\n";
        return;
    }
    
    //Right now pT efficiency flat ==> Not used
    h_MuonIDSFpteta = dynamic_cast<TH2*>(MuonEfficiencies.Get("MuonSFtop12028"));
    if ( !h_MuonIDSFpteta ) {
        std::cout<<"TH2 >>TH scalefactor << is not in the file "<<MuonEfficiencies.GetName()<<"\n";
        return;
    }

    h_ElectronIDSFpteta = dynamic_cast<TH2*>(ElecEfficiencies.Get("GlobalSF"));
    if ( !h_ElectronIDSFpteta ) {
        std::cout<<"TH2 >>TH scalefactor << is not in the file "<<ElecEfficiencies.GetName()<<"\n";
        return;
    }

    if (systematic_.BeginsWith("LEPT_")) {
        double factor = systematic_.EndsWith("_UP") ? 1 : -1;
        for (int i = 1; i <= h_MuonIDSFpteta->GetNbinsX(); ++i) {
            for (int j = 1; j <= h_MuonIDSFpteta->GetNbinsY(); ++j) {
                h_MuonIDSFpteta->SetBinContent(i, j,
                    h_MuonIDSFpteta->GetBinContent(i,j) + factor*h_MuonIDSFpteta->GetBinError(i,j));
            }
        }

        for (int i = 1; i <= h_ElectronIDSFpteta->GetNbinsX(); ++i) {
            for (int j = 1; j <= h_ElectronIDSFpteta->GetNbinsY(); ++j) {
                h_ElectronIDSFpteta->SetBinContent(i, j,h_ElectronIDSFpteta->GetBinContent(i,j) + factor*h_ElectronIDSFpteta->GetBinError(i,j));
            }
        }
    }

    h_MuonIDSFpteta->SetDirectory(0);
    MuonEfficiencies.Close();
    h_ElectronIDSFpteta->SetDirectory(0);
    ElecEfficiencies.Close();


}



void AnalysisBase::prepareBtagSF()
{
    //some defaults for the median, overwritten if btag files exist
    btag_ptmedian_ = 75;
    btag_etamedian_ = 0.75;

    //By now defined the per-jet SFs vary according to:
    //   BTag_Up   ==> pt>ptmedian vary DOWN, pt<ptmedian vary UP
    //   BTag_Down ==> pt>ptmedian vary UP, pt<ptmedian vary DOWN

    //load per-jet efficienciies file and Histograms
    TFile *bEfficiencies;
    if (btagFile_!="") {
        bEfficiencies = TFile::Open(btagFile_);
    } else {
        std::cout<<"WARNING!!! Provide b tag efficiencies before running\n";
        return;
    }

    if (!bEfficiencies) {
        std::cout << "\n******************************************************\n"
             << "File " << btagFile_ << " does not exist. Running without btagsf!!!\n"
             << "To create the file, run:\n" 
             << "   build/load_Analysis -f ttbarsignalplustau.root -c emu\n"
             << "   build/load_Analysis -f ttbarsignalplustau.root -c ee\n"
             << "   build/load_Analysis -f ttbarsignalplustau.root -c mumu\n"
             << "and copy the selectionRoot/BTagEff directory to the cwd:\n"
             << "   cp -r selectionRoot/BTagEff .\n"
             << "This error is NOT fatal, using a btag SF = 1 everywhere\n"
             << "*******************************************************\n\n";
        return;
    }
    bEff = dynamic_cast<TH2*>(bEfficiencies->Get("BEffPerJet"));
    if (!bEff) {
        std::cout<<"Histogram bEff is not in the file "<<bEfficiencies->GetName();
        return;
    }
    cEff = dynamic_cast<TH2*>(bEfficiencies->Get("CEffPerJet"));
    if (!cEff) {
        std::cout<<"Histogram cEff is not in the file "<<bEfficiencies->GetName();
        return;
    }
    lEff = dynamic_cast<TH2*>(bEfficiencies->Get("LEffPerJet"));
    if (!lEff) {
        std::cout<<"Histogram lEff is not in the file "<<bEfficiencies->GetName();
        return;
    }
    
    TH1* medians = dynamic_cast<TH1*>(bEfficiencies->Get("Medians"));
    btag_ptmedian_ = medians->GetBinContent(1);
    btag_etamedian_ = medians->GetBinContent(2);
    printf("BTagSF: Using medians: pT = %.0f, eta = %.2f\n", btag_ptmedian_, btag_etamedian_);

    //load the histograms in memory, to avoid memory leaks
    bEff->SetDirectory(0);
    cEff->SetDirectory(0);
    lEff->SetDirectory(0);
    bEfficiencies->Close();
    bEfficiencies->Delete();
    // END: BTag SF calculation neccessary stuff

}



double AnalysisBase::calculateBtagSF()
{
    if (!bEff) return 1; //no btag file given, so return 1
    
    double OneMinusEff=1;
    double OneMinusSEff=1;
    double SFPerJet=1, eff=1;
    for ( size_t i = 0; i < jets_->size(); ++i ) {
        double pt = jets_->at(i).Pt();
        double eta = std::abs(jets_->at(i).Eta());
        if ( pt > 30 && eta < 2.4 ) {
            int partonFlavour = std::abs(jetPartonFlavour_->at(i)); //store absolute value
            if (partonFlavour == 0) continue;
            int ptbin, etabin, dummy;
            bEff->GetBinXYZ(bEff->FindBin(pt, eta), ptbin, etabin, dummy);
            //overflow to last bin
            ptbin = std::min(ptbin, bEff->GetNbinsX());
            etabin = std::min(etabin, bEff->GetNbinsY());
            //do the type-jet selection & Eff and SF obtention
            double SF_Error=0;
            if ( partonFlavour == 5 ) { //b-quark
                eff=bEff->GetBinContent ( ptbin, etabin );
                if(systematic_.Contains("BEFF_UP")){eff = eff + bEff->GetBinError ( ptbin, etabin );}
                else if(systematic_.Contains("BEFF_DOWN")){eff = eff - bEff->GetBinError ( ptbin, etabin );} 
                SFPerJet = BJetSF( pt, eta );
                SF_Error = BJetSFAbsErr ( pt );
            } else if ( partonFlavour == 4 ) { //c-quark
                eff=cEff->GetBinContent ( ptbin, etabin );
                if(systematic_.Contains("CEFF_UP")){eff = eff + cEff->GetBinError ( ptbin, etabin );}
                else if(systematic_.Contains("CEFF_DOWN")){eff = eff - cEff->GetBinError ( ptbin, etabin );} 
                SFPerJet = CJetSF( pt, eta );
                SF_Error = CJetSFAbsErr ( pt );
            } else if ( partonFlavour != 0 ) { //l-quark
                eff=lEff->GetBinContent ( ptbin, etabin );
                if(systematic_.Contains("LEFF_UP")){eff = eff + lEff->GetBinError ( ptbin, etabin );}
                else if(systematic_.Contains("LEFF_DOWN")){eff = eff - lEff->GetBinError ( ptbin, etabin );} 
                SFPerJet = LJetSF( pt, eta, "central");
                if ( systematic_.BeginsWith("BTAG_LJET_UP") ) {   //systematic variation of l-jets for inclusive XSection measurement
                    SFPerJet = LJetSF ( pt, eta, "up");
                } else if ( systematic_.BeginsWith("BTAG_LJET_DOWN") ) { //systematic variation of l-jets for inclusive XSection measurement
                    SFPerJet = LJetSF ( pt, eta, "down");
                } else if ( systematic_.BeginsWith("BTAG_LJET_") ){ //systematic variations for differential XSection
                    if ( (systematic_.Contains("PT_UP") && pt>btag_ptmedian_) || (systematic_.Contains("PT_DOWN") && pt<btag_ptmedian_)
                        || (systematic_.Contains("ETA_UP") && eta>btag_etamedian_) || (systematic_.Contains("ETA_DOWN") && eta<btag_etamedian_) ){
                        SFPerJet = LJetSF ( pt, eta, "up");
                    }
                    else {
                        SFPerJet = LJetSF ( pt, eta, "down");
                    }
                }
            } else {
                std::cout<<"I found a jet in event "<<eventNumber_<<" which is not b, c nor light: "<<partonFlavour<<std::endl;
                return kFALSE;
            }
            if ( eff <= 0 ) eff = 1;
            //calculate both numerator and denominator for per-event SF calculation
            //consider also the UP and DOWN variation for systematics calculation. Same procedure as PU
            OneMinusEff = OneMinusEff* ( 1-eff );
            double sf = SFPerJet;
            if ( systematic_.Contains("LJET") ) { SF_Error = 0; } //For l-jet systematics set to 0 the b- and c-jet errors
            if ( systematic_ == "BTAG_UP" ) {
                sf = SFPerJet + SF_Error;
            }
            else if ( systematic_ == "BTAG_DOWN" ) {
                sf = SFPerJet - SF_Error;
            }
            else if ( systematic_ == "BTAG_PT_UP" ) {
                if ( pt>btag_ptmedian_ )  {
                    sf = SFPerJet - 0.5 * SF_Error;
                } else {
                    sf = SFPerJet + 0.5 * SF_Error;
                }
            }
            else if ( systematic_ == "BTAG_PT_DOWN" ) {
                if ( pt>btag_ptmedian_ )  {
                    sf = SFPerJet + 0.5 * SF_Error;
                } else {
                    sf = SFPerJet - 0.5 * SF_Error; 
                }
            }
            else if ( systematic_ == "BTAG_ETA_UP" ) {
                if ( eta>btag_etamedian_ )  {
                    sf = SFPerJet - 0.5 * SF_Error;
                } else {
                    sf = SFPerJet + 0.5 * SF_Error;
                }
            }
            else if ( systematic_ == "BTAG_ETA_DOWN" ) {
                if ( eta>btag_etamedian_ )  {
                    sf = SFPerJet + 0.5 * SF_Error;
                } else {
                    sf = SFPerJet - 0.5 * SF_Error;
                }
            }
            OneMinusSEff *= 1 - eff * sf;
        }
    }

    if( std::abs(1.-OneMinusEff) < 1e-8 || std::abs(1.-OneMinusSEff) < 1e-8 ) return 1;

    //per-event SF calculation (also the UP and DOWN variations)
    double scale_factor = ( 1.-OneMinusSEff ) / ( 1.-OneMinusEff );
    
    if ( std::abs(scale_factor - 1.)>0.05 ){scale_factor = 1;}
    
    return scale_factor;
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
            d2s(pair.first->GetBinLowEdge(i)) + " to " + d2s(pair.first->GetBinLowEdge(i+1));
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



/** Set up the SF for the Kin Reco
 * 
 * Currently a flat per-channel SF is used. For the systematic KIN_UP and KIN_DOWN,
 * the SF is modified by its uncertainty.
 * 
 * To calculate the SF, you need to set the SF to 1 and rerun. Then determine the
 * SF with kinRecoEfficienciesAndSF
 */
void AnalysisBase::prepareKinRecoSF() {
    //uncomment the following line to determine the Kin Reco SFs
    //then make && ./runNominalParallel.sh && ./Histo -t cp -p akr bkr step && ./kinRecoEfficienciesAndSF
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



/** do the kinematic reconstruction 
 * 
 * reconstruct the top quarks and store the result in the 
 * Hyp* member variables
 * 
 * @param leptonMinus 4-vector of the l-
 * @param leptonPlus 4-vector of the l+
 * 
 * @return true iff there is at least one solution.
 */
bool AnalysisBase::calculateKinReco(const LV& leptonMinus, const LV& leptonPlus)
{
    auto sols = GetKinSolutions(leptonMinus, leptonPlus, jets_, jetBTagCSV_, met_);
    if (sols.size()) {
        const TtDilepEvtSolution &sol = sols[0];
        HypTop_->clear();        HypTop_->push_back(TLVtoLV(sol.top));
        HypAntiTop_->clear();    HypAntiTop_->push_back(TLVtoLV(sol.topBar));
        HypLepton_->clear();     HypLepton_->push_back(TLVtoLV(sol.lm));
        HypAntiLepton_->clear(); HypAntiLepton_->push_back(TLVtoLV(sol.lp));
        HypBJet_->clear();       HypBJet_->push_back(TLVtoLV(sol.jetB));
        HypAntiBJet_->clear();   HypAntiBJet_->push_back(TLVtoLV(sol.jetBbar));
        HypNeutrino_->clear();   HypNeutrino_->push_back(TLVtoLV(sol.neutrino));
        HypAntiNeutrino_->clear(); HypAntiNeutrino_->push_back(TLVtoLV(sol.neutrinoBar));
        HypJet0index_->clear();  HypJet0index_->push_back(sol.jetB_index);
        HypJet1index_->clear();  HypJet1index_->push_back(sol.jetBbar_index);
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
    return sols.size() > 0;
}



/** return a string describing the true level W+/W- decays from the ttbar system
 * 
 * @return a string like e/tau->mu describing the decay to the W+/W- from the top/tbar decay
 * 
 * Possible strings are:
 *   e/e  for the ee channel
 *   e/tau->mu for the W+ -> e+ decay and the W- -> tau- -> mu- decay
 *   ... and so on. The first part is from the top/W+, the second from the tbar/W-
 */
const std::string AnalysisBase::topDecayModeString() {
    std::vector<std::string> WMode { "unknown", "hadronic", "e", "mu", "tau->hadron", "tau->e", "tau->mu" };
    int top = topDecayMode_ / 10;
    int antitop = topDecayMode_ % 10;
    std::string result = WMode[top] + "/" + WMode[antitop];
    return result;    
}



/** prepare JER/JES systematics
 * 
 * This function checks if we are asked to run JER or JES. If so,
 * additional branches need to be enabled and a JES uncertainty file
 * needs to be read.
 */
void AnalysisBase::prepareJER_JES()
{    
    TString pathToFile(DATA_PATH() + "/Fall12_V7_DATA_UncertaintySources_AK5PFchs.txt");
    doJesJer_ = false;
    if (systematic_ == "JES_UP" || systematic_ == "JES_DOWN") {
        unc_ = new JetCorrectionUncertainty(JetCorrectorParameters(pathToFile.Data(), "Total"));
        doJesJer_ = true;
    }
    if (systematic_ == "JER_UP" || systematic_ == "JER_DOWN") {
        doJesJer_ = true;
    }
}



/** Apply the JER or JES systematic
 * 
 * This function modifies the jets collection and also scales the MET.
 * It uses the collections stored just for the jet scaling
 */
void AnalysisBase::applyJER_JES()
{
    if (systematic_ == "JER_UP" || systematic_ == "JER_DOWN") {

      double JEC_dpX =0;
      double JEC_dpY =0;
      
      double ResolutionEtaRange[5] = {0.5, 1.1, 1.7, 2.3, 10};
      double ResolutionEtaScaleFactor[5];//nom = {1.052, 1.057, 1.096, 1.134, 1.288};
      
      if(systematic_ == "JER_UP"){
        ResolutionEtaScaleFactor[0] = 1.115;
        ResolutionEtaScaleFactor[1] = 1.114;
        ResolutionEtaScaleFactor[2] = 1.161;
        ResolutionEtaScaleFactor[3] = 1.228;
        ResolutionEtaScaleFactor[4] = 1.488;
      }
      if(systematic_ == "JER_DOWN"){
        ResolutionEtaScaleFactor[0] = 0.990;
        ResolutionEtaScaleFactor[1] = 1.001;
        ResolutionEtaScaleFactor[2] = 1.032;
        ResolutionEtaScaleFactor[3] = 1.042;
        ResolutionEtaScaleFactor[4] = 1.089;
      }

      size_t jetEtaBin = 0;

      double factor = 0;

      //this first loop will correct the jet collection that is used for kinematic reconstruction

      for (size_t i = 0; i < jets_->size(); ++i) {

        for (size_t j = 0; j < 5; ++j){

          if (std::abs(jets_->at(i).eta()) < ResolutionEtaRange[j]){
            jetEtaBin = j;
            break;
          }

        }

        if (jetJERSF_->at(i) != 0.0){
          jets_->at(i) = jets_->at(i)*(1.0/jetJERSF_->at(i));
          
          if ( associatedGenJet_->at(i).pt() != 0.0)  factor = 1.0 + (ResolutionEtaScaleFactor[jetEtaBin] - 1.0)*(1.0 - (associatedGenJet_->at(i).pt()/jets_->at(i).pt()));
          
          if (jetJERSF_->at(i) == 1.0) factor = 1.0;

          jets_->at(i) = jets_->at(i)*factor;
        }
      }

      //this second loop will correct the jet collection that is used to modify the MET

      for (size_t i = 0; i < jetsForMET_->size(); ++i) {

        double dpX = jetsForMET_->at(i).px();
        double dpY = jetsForMET_->at(i).py();
        
        for (size_t j = 0; j < 5; ++j){

          if (std::abs(jetsForMET_->at(i).eta()) < ResolutionEtaRange[j]){
            jetEtaBin = j;
            break;
          }

        }

        if (jetForMETJERSF_->at(i) != 0.0){
          jetsForMET_->at(i) = jetsForMET_->at(i)*(1.0/jetForMETJERSF_->at(i));
          
          if ( associatedGenJetForMET_->at(i).pt() != 0.0)  factor = 1.0 + (ResolutionEtaScaleFactor[jetEtaBin] - 1.0)*(1.0 - (associatedGenJetForMET_->at(i).pt()/jetsForMET_->at(i).pt()));
          
          if (jetForMETJERSF_->at(i) == 1.0) factor = 1.0;

          jetsForMET_->at(i) = jetsForMET_->at(i)*factor;

          JEC_dpX += jetsForMET_->at(i).px() - dpX;
          JEC_dpY += jetsForMET_->at(i).py() - dpY;
          //      if(std::abs(factor - jetForMETJERSF->at(i)) > 0.1){
          //std::cout<<"Scale Factor is: "<<factor<<std::endl;
          // std::cout<<"JERSF is       : "<<jetForMETJERSF->at(i)<<std::endl<<std::endl;
          //}
        }
      }

      double scaledMETPx = met_->px() - JEC_dpX;
      double scaledMETPy = met_->py() - JEC_dpY;
      
      met_->SetPt(sqrt(scaledMETPx*scaledMETPx + scaledMETPy*scaledMETPy));

    }

    //std::cout<<"before: "<<met->pt()<<std::endl;
    if(systematic_ == "JES_UP" || systematic_ == "JES_DOWN"){
        double JEC_dpX =0;
        double JEC_dpY =0;

      //this first loop will correct the jet collection that is used for kinematic reconstruction

        for (size_t i = 0; i < jets_->size(); ++i) {
        
            bool up = true;
            if (systematic_ == "JES_DOWN") up = false;
            
            //std::cout<<"Jet before: "<<jetsForMET->at(i)<<std::endl;

            //      std::cout<<"before: "<<jets->at(i)<<std::endl;
            unc_->setJetPt(jets_->at(i).pt()); 
            unc_->setJetEta(jets_->at(i).eta());
            
            double dunc= unc_->getUncertainty(true);
            
            if (up == true) {jets_->at(i) = jets_->at(i)*(1+dunc);
            }else{jets_->at(i) = jets_->at(i)*(1-dunc);}
        }

      //this second loop will correct the jet collection that is used for modifying MET

        for (size_t i = 0; i < jetsForMET_->size(); ++i) {
        
            bool up = true;
            if (systematic_ == "JES_DOWN") up = false;
            
            //std::cout<<"Jet before: "<<jetsForMET->at(i)<<std::endl;

            //      std::cout<<"before: "<<jets->at(i)<<std::endl;
            double dpX = jetsForMET_->at(i).px();
            double dpY = jetsForMET_->at(i).py();

            unc_->setJetPt(jetsForMET_->at(i).pt()); 
            unc_->setJetEta(jetsForMET_->at(i).eta());
            
            double dunc= unc_->getUncertainty(true);
            
            if (up == true) {jetsForMET_->at(i) = jetsForMET_->at(i)*(1+dunc);
            }else{jetsForMET_->at(i) = jetsForMET_->at(i)*(1-dunc);}

            JEC_dpX += jetsForMET_->at(i).px() - dpX;
            JEC_dpY += jetsForMET_->at(i).py() - dpY;
            //std::cout<<"after : "<<jets->at(i)<<std::endl;
                    
            //std::cout<<"Jet after:  "<<jetsForMET->at(i)<<std::endl;
        }
        double scaledMETPx = met_->px() - JEC_dpX;
        double scaledMETPy = met_->py() - JEC_dpY;
        
        met_->SetPt(sqrt(scaledMETPx*scaledMETPx + scaledMETPy*scaledMETPy));
    }
    //std::cout<<"after : "<<met->pt()<<std::endl;
    //std::cout<<"&%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%&&&&&&&&&&&&&&&&&&&&&\n";
    
}



void AnalysisBase::bookBtagHistograms()
{
    const int PtMax = 11;
    const int EtaMax = 5;
    Double_t ptbins[PtMax+1] = {20.,30.,40.,50.,60.,70.,80.,100.,120.,160.,210.,800.};
    Double_t etabins[EtaMax+1] = {0.0,0.5,1.0,1.5,2.0,2.4};
    
    h_bjets = store(new TH2D("bjets2D", "unTagged Bjets", PtMax, ptbins, EtaMax, etabins));
    h_btaggedjets = store(new TH2D("bjetsTagged2D", "Tagged Bjets", PtMax, ptbins, EtaMax, etabins));
    h_cjets = store(new TH2D("cjets2D", "unTagged Cjets", PtMax, ptbins, EtaMax, etabins));
    h_ctaggedjets = store(new TH2D("cjetsTagged2D", "Tagged Cjets", PtMax, ptbins, EtaMax, etabins));
    h_ljets = store(new TH2D("ljets2D", "unTagged Ljets", PtMax, ptbins, EtaMax, etabins));
    h_ltaggedjets = store(new TH2D("ljetsTagged2D", "Tagged Ljets", PtMax, ptbins, EtaMax, etabins));
    
    h_bjets->Sumw2();
    h_btaggedjets->Sumw2();
    h_cjets->Sumw2();
    h_ctaggedjets->Sumw2();
    h_ljets->Sumw2();    
    h_ltaggedjets->Sumw2();
}



void AnalysisBase::fillBtagHistograms(const double jetPtCut, const double btagWP)
{
    for (size_t i = 0; i < jets_->size(); ++i) {
        if (jets_->at(i).Pt() <= jetPtCut) break;
        double absJetEta = abs(jets_->at(i).Eta());
        if (absJetEta<2.4) {
            int partonFlavour = abs(jetPartonFlavour_->at(i));
            if(partonFlavour == 5){//b-quark
                h_bjets->Fill(jets_->at(i).Pt(), absJetEta);
                if((*jetBTagCSV_)[i]>btagWP){
                    h_btaggedjets->Fill(jets_->at(i).Pt(), absJetEta);
                }
            }
            else if (partonFlavour == 4){//c-quark
                h_cjets->Fill(jets_->at(i).Pt(), absJetEta);
                if((*jetBTagCSV_)[i]>btagWP){
                    h_ctaggedjets->Fill(jets_->at(i).Pt(), absJetEta);
                }
            }
            else if (partonFlavour != 0){//l-quark
                h_ljets->Fill(jets_->at(i).Pt(), absJetEta);
                if((*jetBTagCSV_)[i]>btagWP){
                    h_ltaggedjets->Fill(jets_->at(i).Pt(), absJetEta);
                }
            }
        }
    }
}



void AnalysisBase::produceBtagEfficiencies()
{
    std::cout << "Writing out btag efficiencies\n";
    std::string f_savename = this->assignFolder(BTagEffDIR, channel_, systematic_);
    f_savename.append(outputfilename_);
    
    h_bjets = dynamic_cast<TH2*>( fOutput->FindObject("bjets2D") );
    h_btaggedjets = dynamic_cast<TH2*>( fOutput->FindObject("bjetsTagged2D") );
    h_cjets = dynamic_cast<TH2*>( fOutput->FindObject("cjets2D") );
    h_ctaggedjets = dynamic_cast<TH2*>( fOutput->FindObject("cjetsTagged2D") );
    h_ljets = dynamic_cast<TH2*>( fOutput->FindObject("ljets2D") );
    h_ltaggedjets = dynamic_cast<TH2*>( fOutput->FindObject("ljetsTagged2D") );
    if (!h_bjets || !h_btaggedjets || !h_cjets || !h_ctaggedjets || !h_ljets || !h_ltaggedjets) {
        std::cerr << "At least one of the btag histograms is missing\n";
        exit(4);
    }
    TFile fbtag(f_savename.c_str(),"RECREATE");
    h_bjets->Write();
    h_btaggedjets->Write();
    h_cjets->Write();
    h_ctaggedjets->Write();
    h_ljets->Write();
    h_ltaggedjets->Write();
    
    TH1 *btaggedPt = h_btaggedjets->ProjectionX(); TH1 *btaggedEta = h_btaggedjets->ProjectionY();
    TH1 *ctaggedPt = h_ctaggedjets->ProjectionX(); TH1 *ctaggedEta = h_ctaggedjets->ProjectionY();
    TH1 *ltaggedPt = h_ltaggedjets->ProjectionX(); TH1 *ltaggedEta = h_ltaggedjets->ProjectionY();
    
    TH1 *bUntaggedPt = h_bjets->ProjectionX(); TH1 *bEta = h_bjets->ProjectionY();
    TH1 *cUntaggedPt = h_cjets->ProjectionX(); TH1 *cEta = h_cjets->ProjectionY();
    TH1 *lUntaggedPt = h_ljets->ProjectionX(); TH1 *lEta = h_ljets->ProjectionY();
    
    //Calculate the medians and save them in a txt file
    double PtMedian = Median(btaggedPt);
    double EtaMedian = Median(btaggedEta);
    printf("Median: pT = %.0f, eta = %.2f\n", PtMedian, EtaMedian);
    TH1* medianHist = new TH1D("Medians", "medians", 2, -0.5, 1.5);
    medianHist->GetXaxis()->SetBinLabel(1, "pT");
    medianHist->GetXaxis()->SetBinLabel(2, "eta");
    medianHist->SetBinContent(1, PtMedian);
    medianHist->SetBinContent(2, EtaMedian);
    medianHist->Write();
    
    TH1 *beffPt =(TH1*) btaggedPt->Clone("beffPt");
    TH1 *ceffPt =(TH1*) ctaggedPt->Clone("ceffPt");
    TH1 *leffPt =(TH1*) ltaggedPt->Clone("leffPt");
    
    TH1 *beffEta =(TH1*) btaggedEta->Clone("beffEta");  
    TH1 *ceffEta =(TH1*) ctaggedEta->Clone("ceffEta");  
    TH1 *leffEta =(TH1*) ltaggedEta->Clone("leffEta");  
    
    //Calculate Efficiency: N_tageed/N_all
    //Calculate also the binomial error (option "B" does it)!!
    beffPt->Divide(btaggedPt, bUntaggedPt, 1, 1, "B"); 
    ceffPt->Divide(ctaggedPt, cUntaggedPt, 1, 1, "B"); 
    leffPt->Divide(ltaggedPt, lUntaggedPt, 1, 1, "B");
    beffEta->Divide(btaggedEta, bEta, 1, 1, "B"); 
    ceffEta->Divide(ctaggedEta, cEta, 1, 1, "B"); 
    leffEta->Divide(ltaggedEta, lEta, 1, 1, "B"); 
    h_btaggedjets->Divide(h_btaggedjets, h_bjets, 1, 1, "B"); 
    h_ctaggedjets->Divide(h_ctaggedjets, h_cjets, 1, 1, "B"); 
    h_ltaggedjets->Divide(h_ltaggedjets, h_ljets, 1, 1, "B"); 

    //Save histograms in ROOT file
    beffPt->Write("BEffPt"); 
    ceffPt->Write("CEffPt"); 
    leffPt->Write("LEffPt"); 
    beffEta->Write("BEffEta"); 
    ceffEta->Write("CEffEta"); 
    leffEta->Write("LEffEta"); 
    h_btaggedjets->Write("BEffPerJet");
    h_ctaggedjets->Write("CEffPerJet");
    h_ltaggedjets->Write("LEffPerJet");
    
    fbtag.Close();
    std::cout << "Done.\n\n\n";
}



double AnalysisBase::BJetSF( double pt, double eta )
{
    //CSVL b-jet SF
    //From BTV-11-004 and https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFb-mujet_payload.tptt (ICHEP 2012 prescription)
    //From: https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFb-pt_payload_Moriond13.tptt  (Moriond 2013 prescription)

    if ( std::abs(eta) > 2.4 ) {
        std::cout<<"Jet Eta="<<eta<<" Out of the selected range (|eta|<2.4). Check it\n";
        exit(9);
    }
    if ( pt < 30 ){
        std::cout<<"Jet pT="<<pt<<" Out of the selected range (pt>30GeV). Check it\n";
        exit(9);
    }

    if ( pt < 20 ) pt = 20;
    if ( pt > 800 ) pt = 800;

    return 0.981149*((1.+(-0.000713295*pt))/(1.+(-0.000703264*pt)));
}



double AnalysisBase::CJetSF ( double pt, double eta )
{
    //CSVL c-jet SF
    //From BTV-11-004 and https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagPOG#2012_Data_and_MC (ICHEP 2012 prescription)
    //From https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagPOG#2012_Data_and_MC_Moriond13_presc  (Moriond 2013 prescription)

    return 2 * BJetSF( pt, eta );
}



double AnalysisBase::LJetSF ( double pt, double eta, TString typevar )
{
    //CSVL ligth jet mistag SF. Includes also the SF for variations up and down
    //From BTV-11-004 and https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFlightFuncs.C (ICHEP 2012 prescription)
    //From https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFlightFuncs_Moriond2013.C  (Moriond 2013 prescription)

    double eta_abs = std::abs(eta);
    if ( eta_abs > 2.4 ) {
        std::cout<<"Jet Eta="<<eta<<" Out of the selected range (|eta|<2.4). Check it\n";
        exit(91);
    }
    if ( pt < 30 ){
        std::cout<<"Jet pT="<<pt<<" out of the selected range. Check it\n";
        exit(91);
    }

    if ( pt > 800 && eta_abs <= 1.5 ) {
        pt = 800;
    }    else if (pt > 700 && eta_abs > 1.5 ) {
        pt = 700;
    }

    if ( typevar == "central" ){
        if ( eta_abs <= 0.5 ) {
            return ((1.04901+(0.00152181*pt))+(-3.43568e-06*(pt*pt)))+(2.17219e-09*(pt*(pt*pt)));
        } else if ( eta_abs <= 1.0 ) {
            return ((0.991915+(0.00172552*pt))+(-3.92652e-06*(pt*pt)))+(2.56816e-09*(pt*(pt*pt)));
        } else if ( eta_abs <= 1.5 ) {
            return ((0.962127+(0.00192796*pt))+(-4.53385e-06*(pt*pt)))+(3.0605e-09*(pt*(pt*pt)));
        } else {
            return ((1.06121+(0.000332747*pt))+(-8.81201e-07*(pt*pt)))+(7.43896e-10*(pt*(pt*pt)));
        }
    }  else if ( typevar == "up" ){
        if ( eta_abs <= 0.5 ) {
            return ((1.12424+(0.00201136*pt))+(-4.64021e-06*(pt*pt)))+(2.97219e-09*(pt*(pt*pt)));
        } else if ( eta_abs <= 1.0 ) {
            return ((1.06231+(0.00215815*pt))+(-4.9844e-06*(pt*pt)))+(3.27623e-09*(pt*(pt*pt)));
        } else if ( eta_abs <= 1.5 ) {
            return ((1.02883+(0.00231985*pt))+(-5.57924e-06*(pt*pt)))+(3.81235e-09*(pt*(pt*pt)));
        } else {
            return ((1.1388+(0.000468418*pt))+(-1.36341e-06*(pt*pt)))+(1.19256e-09*(pt*(pt*pt)));
        }
    } else if ( typevar == "down" ){
        if ( eta_abs <= 0.5 ) {
            return ((0.973773+(0.00103049*pt))+(-2.2277e-06*(pt*pt)))+(1.37208e-09*(pt*(pt*pt)));
        } else if ( eta_abs <= 1.0 ) {
            return ((0.921518+(0.00129098*pt))+(-2.86488e-06*(pt*pt)))+(1.86022e-09*(pt*(pt*pt)));
        } else if ( eta_abs <= 1.5 ) {
            return ((0.895419+(0.00153387*pt))+(-3.48409e-06*(pt*pt)))+(2.30899e-09*(pt*(pt*pt)));
        } else {
            return ((0.983607+(0.000196747*pt))+(-3.98327e-07*(pt*pt)))+(2.95764e-10*(pt*(pt*pt)));
        }
    } else {
        std::cout<<"Type of variation not valid. Check it\n";
        exit(92);
    }

}



double AnalysisBase::BJetSFAbsErr ( double pt )
{
    //If needed go to https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagPOG#2012_Data_and_MC
    //this pt range MUST match the binning of the error array provided by the BTV in the above link

    double ptarray[] = {20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600, 800};
    double SFb_error[] = { 0.0484285,  0.0126178,  0.0120027,  0.0141137, 0.0145441, 0.0131145, 0.0168479, 0.0160836, 0.0126209, 0.0136017, 0.019182, 0.0198805, 0.0386531, 0.0392831, 0.0481008, 0.0474291 };

    int ptbin = -1;
    int ptarray_Size = sizeof(ptarray) / sizeof(ptarray[0]);
    int SFb_error_array_Size = sizeof(SFb_error) / sizeof(SFb_error[0]);
    
    if( ptarray_Size != SFb_error_array_Size+1 ) {
        std::cout<<"You wrote 2 arrays with sizes that don't agree together!! Fix this.\n";
        exit(100);
    }
    for ( int i=0; i<(ptarray_Size-1); i++){
        if ( pt > ptarray[i] && pt < ptarray[i+1]) {
            ptbin = i;
            break;
        }
    }

    if ( ptbin > ptarray_Size ) {
        return 2 * SFb_error[ptarray_Size];
    } else if ( ptbin < 0){
        return 2 * SFb_error[0];
    } else {
        return SFb_error[ptbin];
    };
}



double AnalysisBase::CJetSFAbsErr ( double pt)
{
    return 2 * BJetSFAbsErr ( pt );
}



/** order two LorentzVectors by pt
 * 
 * @param leading the LV with the higher pt (output)
 * @param Nleading the LV with the lower pt (output)
 * @param lv1 input LV to compare with lv2
 * @param lv2 input LV to compare with lv1
 * 
 * Compare lv1 and lv2. The LV with the larger pt is copied to leading,
 * the LV with the smaller pt is copied to Nleading
 */
void AnalysisBase::orderLVByPt(LV &leading, LV &Nleading, const LV &lv1, const LV &lv2) {
    if (lv1.Pt() > lv2.Pt()) {
        leading = lv1; Nleading = lv2;
    } else {
        leading = lv2; Nleading = lv1;
    }
}



/// apply pT and eta cuts on our jets
void AnalysisBase::cleanJetCollection(double ptcut, double etacut) {
    for (int i = jets_->size() - 1; i >= 0; --i) {
        if (jets_->at(i).pt() < ptcut || std::abs(jets_->at(i).eta()) > etacut) {
            jets_->erase(begin(*jets_) + i);
            jetBTagCSV_->erase(begin(*jetBTagCSV_) + i);
            if (isMC_) associatedGenJet_->erase(begin(*associatedGenJet_) + i);
        }        
    }
}



std::string AnalysisBase::assignFolder(const char* baseDir, const TString& channel, const TString& systematic)const
{
    std::string path("");
    
    // Create all subdirectories contained in baseDir
    TObjArray* a_subDir = TString(baseDir).Tokenize("/");
    for(Int_t iSubDir = 0; iSubDir < a_subDir->GetEntriesFast(); ++iSubDir){
        const TString& subDir = a_subDir->At(iSubDir)->GetName();
        path.append(subDir);
        path.append("/");
        gSystem->MakeDirectory(path.c_str());
    }
    
    // Create subdirectories for systematic and channel
    path.append(systematic);
    path.append("/");
    gSystem->MakeDirectory(path.c_str());
    path.append(channel);
    path.append("/");
    gSystem->MakeDirectory(path.c_str());
    
    return path;
}



bool AnalysisBase::failsDrellYanGeneratorSelection(Long64_t& entry)const
{
    if(checkZDecayMode_ && !checkZDecayMode_(entry)) return true;
    return false;
}



bool AnalysisBase::failsTopGeneratorSelection(Long64_t& entry)
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



double AnalysisBase::madgraphWDecayCorrection(Long64_t& entry)
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


double AnalysisBase::weightPileup(Long64_t& entry)
{
    if(!isMC_ || !pureweighter_)return 1.;
    this->GetVertMultiTrueEntry(entry);
    return pureweighter_->getPUweight(vertMultiTrue_);
}








