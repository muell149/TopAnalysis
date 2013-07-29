#define HiggsAnalysis_cxx

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <algorithm>

#include <TH1.h>
#include <TTree.h>
#include <TString.h>
#include <TFile.h>
#include <TSystem.h>
#include <Math/VectorUtil.h>
#include <TProfile.h>

#include "HiggsAnalysis.h"
#include "higgsUtils.h"
#include "JetCategories.h"
#include "DijetAnalyzer.h"
#include "analysisStructs.h"
#include "AnalysisHistograms.h"
#include "Playground.h"
#include "MvaInputVariables.h"
#include "MvaValidation.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/analysisObjectStructs.h"
#include "../../diLeptonic/src/classes.h"
#include "../../diLeptonic/src/ScaleFactors.h"





/// Lepton eta selection (absolute value)
constexpr double LeptonEtaCUT = 2.4;

/// Lepton pt selection in GeV
constexpr double LeptonPtCut = 20.;

/// Jet eta selection (absolute value)
constexpr double JetEtaCUT = 2.4;

/// Jet pt selection in GeV
constexpr double JetPtCUT = 30.;

/// b-tag working point
/// CSV Loose: 0.244
/// CSV Medium: 0.679
/// CSV Tight: 0.898
constexpr double BtagWP = 0.244;

/// MET selection for same-flavour channels (ee, mumu)
constexpr double MetCUT = 40.;



// FIXME: move this also to load_HiggsAnalysis
/// Folder for storage of MVA input TTree
constexpr const char* MvaInputDIR = "mvaInput";










HiggsAnalysis::HiggsAnalysis(TTree*):
runWithTtbb_(false),
mvaInputTopJetsVariables_(0),
eventYieldHistograms_(0),
dyScalingHistograms_(0),
basicHistograms_(0),
mvaValidation_(0),
playground_(0),
dijetAnalyzer_(0)
{}



HiggsAnalysis::~HiggsAnalysis()
{}



void HiggsAnalysis::Begin(TTree*)
{
    // Defaults from AnalysisBase
    AnalysisBase::Begin(0);

    // Prepare things for analysis
    this->prepareJER_JES();
}




void HiggsAnalysis::Terminate()
{
    // Produce b-tag efficiencies
    // FIXME: shouldn't we also clear b-tagging efficiency histograms if they are produced ?
    if(this->makeBtagEfficiencies()) btagScaleFactors_->produceBtagEfficiencies(static_cast<std::string>(channel_));
    
    // Do everything needed for MVA
    if(mvaInputTopJetsVariables_){
        // Create output directory for MVA input tree, and produce and write tree
        std::string f_savename = ttbar::assignFolder(MvaInputDIR, channel_, systematic_);
        f_savename.append(outputfilename_);
        mvaInputTopJetsVariables_->produceMvaInputTree(f_savename);
        //mvaInputTopJetsVariables_.produceMvaInputTree(fOutput);

        // Create and store control plots in fOutput
        mvaInputTopJetsVariables_->mvaInputVariablesControlPlots(fOutput);
        
        // Cleanup
        mvaInputTopJetsVariables_->clear();
    }
    
    
    // Defaults from AnalysisBase
    AnalysisBase::Terminate();
}



void HiggsAnalysis::SlaveBegin(TTree *)
{
    // Defaults from AnalysisBase
    AnalysisBase::SlaveBegin(0);


    // Analysis categories
    const int numberOfCategories(jetCategories_->numberOfCategories());

    h_jetCategories_step8 = store(new TH1D("jetCategories_step8","Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));

    const std::vector<TString> v_binLabel(jetCategories_->binLabels());
    for(std::vector<TString>::const_iterator i_binLabel = v_binLabel.begin(); i_binLabel != v_binLabel.end(); ++i_binLabel){
        const TString binLabel(*i_binLabel);
        int position = std::distance(v_binLabel.begin(), i_binLabel) +1;
        h_jetCategories_step8->GetXaxis()->SetBinLabel(position, binLabel);
    }


    // Overview categories
    const int numberOfCategories_overview(jetCategories_overview_->numberOfCategories());

    h_jetCategories_overview_step1 = store(new TH1D("jetCategories_overview_step1","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step2 = store(new TH1D("jetCategories_overview_step2","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step3 = store(new TH1D("jetCategories_overview_step3","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step4 = store(new TH1D("jetCategories_overview_step4","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step5 = store(new TH1D("jetCategories_overview_step5","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step6 = store(new TH1D("jetCategories_overview_step6","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step7 = store(new TH1D("jetCategories_overview_step7","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step8 = store(new TH1D("jetCategories_overview_step8","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));

    const std::vector<TString> v_binLabel_overview(jetCategories_overview_->binLabels());
    for(std::vector<TString>::const_iterator i_binLabel = v_binLabel_overview.begin(); i_binLabel != v_binLabel_overview.end(); ++i_binLabel){
        const TString binLabel(*i_binLabel);
        int position = std::distance(v_binLabel_overview.begin(), i_binLabel) +1;
        h_jetCategories_overview_step1->GetXaxis()->SetBinLabel(position, binLabel);
        h_jetCategories_overview_step2->GetXaxis()->SetBinLabel(position, binLabel);
        h_jetCategories_overview_step3->GetXaxis()->SetBinLabel(position, binLabel);
        h_jetCategories_overview_step4->GetXaxis()->SetBinLabel(position, binLabel);
        h_jetCategories_overview_step5->GetXaxis()->SetBinLabel(position, binLabel);
        h_jetCategories_overview_step6->GetXaxis()->SetBinLabel(position, binLabel);
        h_jetCategories_overview_step7->GetXaxis()->SetBinLabel(position, binLabel);
        h_jetCategories_overview_step8->GetXaxis()->SetBinLabel(position, binLabel);
        //std::cout<<"Bin, label: "<<position<<" , "<<binLabel<<"\n";
    }

/*
    // Histograms needed for cutflow tables
    h_events_step8 = store(new TH1D("events_step8","event count at after 1btag;;# events",8,0,8));
    h_events_step8->Sumw2();
*/
    
    
    // Control plots
    h_jetPt_step8 = store(new TH1D("jetPt_step8", "jet pt;p_{t}  [GeV];# jets", 40, 0, 400));
    h_jetChargeGlobalPtWeighted_step8 = store(new TH1D("jetChargeGlobalPtWeighted_step8", "jetChargeGlobalPtWeighted; c_{jet}^{glob};# jets", 110, -1.1, 1.1));
    h_jetChargeRelativePtWeighted_step8 = store(new TH1D("jetChargeRelativePtWeighted_step8", "jetChargeRelativePtWeighted; c_{jet}^{rel};# jets", 110, -1.1, 1.1));


    // Binned control plots
//    CreateBinnedControlPlots(h_jetCategories_step8, h_events_step8, false);
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetPt_step8, false);
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetChargeGlobalPtWeighted_step8, false);
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetChargeRelativePtWeighted_step8, false);

    // Histograms for b-tagging efficiencies
    if(this->makeBtagEfficiencies()) btagScaleFactors_->bookBtagHistograms(fOutput, static_cast<std::string>(channel_));
    
    
    this->bookAll();
}



void HiggsAnalysis::SlaveTerminate()
{
    this->clearAll();
    
    // Defaults from AnalysisBase
    AnalysisBase::SlaveTerminate();
}



Bool_t HiggsAnalysis::Process(Long64_t entry)
{
    // Defaults from AnalysisBase
    if(!AnalysisBase::Process(entry))return kFALSE;
    
    
    // Use utilities without namespaces
    using namespace ttbar;
    
    
    // Entry for object structs are not yet read, so reset
    this->resetObjectStructEntry();
    
    
    // Define the selection steps as strings
    std::string selectionStep("");
    
    
    //===CUT===
    // this is step0a, no cut application
    selectionStep = "0a";
    
    // ++++ Control Plots ++++

    
    
    //===CUT===
    // this is step0b, select events on generator level and access true level weights
    selectionStep = "0b";
    
    // Separate DY dilepton decays in lepton flavours
    if(this->failsDrellYanGeneratorSelection(entry)) return kTRUE;

    // Separate dileptonic ttbar decays via tau
    //if(this->failsTopGeneratorSelection(entry)) return kTRUE;

    // Separate inclusive ttH sample in decays H->bbbar and others
    if(this->failsHiggsGeneratorSelection(entry)) return kTRUE;

    // Separate tt+bb from tt+other
    if(this->failsAdditionalJetFlavourSelection(entry)) return kTRUE;
    
    // Correct for the MadGraph branching fraction being 1/9 for dileptons (PDG average is .108)
    const double weightMadgraphCorrection = this->madgraphWDecayCorrection(entry);

    // Get weight due to pileup reweighting
    const double weightPU = this->weightPileup(entry);

    // Get weight due to generator weights
    const double weightGenerator = this->weightGenerator(entry);

    // Get true level weights
    const double trueLevelWeightNoPileup = weightGenerator*weightMadgraphCorrection;
    const double trueLevelWeight = trueLevelWeightNoPileup*weightPU;
    
    const tth::GenLevelWeights genLevelWeights(weightMadgraphCorrection, weightPU, weightGenerator,
                                               trueLevelWeightNoPileup, trueLevelWeight);
    
    // ++++ Control Plots ++++
    
    
    
    //===CUT===
    selectionStep = "1";
    
    // Check if event was triggered with the same dilepton trigger as the specified analysis channel
    if(this->failsDileptonTrigger(entry)) return kTRUE;



    // === FULL RECO OBJECT SELECTION === (can thus be used at each selection step)

    // Access reco objects, and common generator objects
    const RecoObjects& recoObjects = this->getRecoObjects(entry);
    const CommonGenObjects& commonGenObjects = this->getCommonGenObjects(entry);
    
    // Create dummies for other objects, non-dummies are created only as soon as needed
    const KinRecoObjects kinRecoObjectsDummy;
    const TopGenObjects topGenObjectsDummy;
    const HiggsGenObjects higgsGenObjectsDummy;
    
    // Get allLepton indices, apply selection cuts and order them by pt (beginning with the highest value)
    const VLV& allLeptons = *recoObjects.allLeptons_;
    std::vector<int> allLeptonIndices = initialiseIndices(allLeptons);
    selectIndices(allLeptonIndices, allLeptons, LVeta, LeptonEtaCUT, false);
    selectIndices(allLeptonIndices, allLeptons, LVeta, -LeptonEtaCUT);
    selectIndices(allLeptonIndices, allLeptons, LVpt, LeptonPtCut);
    orderIndices(allLeptonIndices, allLeptons, LVpt);
    const int numberOfAllLeptons = allLeptonIndices.size();
    
    // Get indices of leptons and antiLeptons separated by charge, and get the leading ones if they exist
    const std::vector<int>& lepPdgId = *recoObjects.lepPdgId_;
    std::vector<int> leptonIndices = allLeptonIndices;
    std::vector<int> antiLeptonIndices = allLeptonIndices;
    selectIndices(leptonIndices, lepPdgId, 0);
    selectIndices(antiLeptonIndices, lepPdgId, 0, false);
    const int numberOfLeptons = leptonIndices.size();
    const int numberOfAntiLeptons = antiLeptonIndices.size();
    const int leptonIndex = numberOfLeptons>0 ? leptonIndices.at(0) : -1;
    const int antiLeptonIndex = numberOfAntiLeptons>0 ? antiLeptonIndices.at(0) : -1;
    
    // In case of an existing opposite-charge dilepton system,
    // get their indices for leading and next-to-leading lepton
    int leadingLeptonIndex(-1);
    int nLeadingLeptonIndex(-1);
    if(numberOfLeptons>0 && numberOfAntiLeptons>0){
        leadingLeptonIndex = leptonIndex;
        nLeadingLeptonIndex = antiLeptonIndex;
        orderIndices(leadingLeptonIndex, nLeadingLeptonIndex, allLeptons, LVpt);
    }
    const bool hasLeptonPair = this->hasLeptonPair(leadingLeptonIndex, nLeadingLeptonIndex, lepPdgId);
    
    // Get two indices of the two leptons in the right order for trigger scale factor, if existing
    int leptonXIndex(leadingLeptonIndex);
    int leptonYIndex(nLeadingLeptonIndex);
    if(hasLeptonPair){
        //in ee and mumu channel leptonX must be the highest pt lepton, i.e. this is already correct
        // in emu channel leptonX must be electron
        if(std::abs(lepPdgId.at(leptonXIndex)) != std::abs(lepPdgId.at(leptonYIndex))){
            orderIndices(leptonYIndex, leptonXIndex, lepPdgId, true);
        }
    }
    
    // Get dilepton system, if existing
    const LV dummyLV(0.,0.,0.,0.);
    const LV dilepton(hasLeptonPair ? allLeptons.at(leadingLeptonIndex)+allLeptons.at(nLeadingLeptonIndex) : dummyLV);
    
    // Get jet indices, apply selection cuts and order them by pt (beginning with the highest value)
    const VLV& jets = *recoObjects.jets_;
    std::vector<int> jetIndices = initialiseIndices(jets);
    selectIndices(jetIndices, jets, LVeta, JetEtaCUT, false);
    selectIndices(jetIndices, jets, LVeta, -JetEtaCUT);
    selectIndices(jetIndices, jets, LVpt, JetPtCUT);
    orderIndices(jetIndices, jets, LVpt);
    const int numberOfJets = jetIndices.size();
    const bool has2Jets = numberOfJets > 1;
    
    // Fill a vector with all jet pair indices, while sorting each pair by the jet charge:
    // first entry is antiBIndex i.e. with higher jet charge, second entry is bIndex
    //const std::vector<double>& jetChargeGlobalPtWeighted = *recoObjects.jetChargeGlobalPtWeighted_;
    const std::vector<double>& jetChargeRelativePtWeighted = *recoObjects.jetChargeRelativePtWeighted_;
    const tth::IndexPairs& jetIndexPairs = this->chargeOrderedJetPairIndices(jetIndices, jetChargeRelativePtWeighted);
    
    // Get b-jet indices, apply selection cuts
    // and order b-jets by btag discriminator (beginning with the highest value)
    const std::vector<double>& jetBTagCSV = *recoObjects.jetBTagCSV_;
    const std::vector<int>& jetPartonFlavour = *commonGenObjects.jetPartonFlavour_;
    std::vector<int> bjetIndices = jetIndices;
    selectIndices(bjetIndices, jetBTagCSV, BtagWP);
    if (isMC_ && !(btagScaleFactors_->makeEfficiencies())){
        // Apply b-tag efficiency MC correction using random number based tag flipping
        btagScaleFactors_->indexOfBtags(bjetIndices, jetIndices,
                                        jets, jetPartonFlavour, jetBTagCSV,
                                        BtagWP, static_cast<std::string>(channel_));
    }
    orderIndices(bjetIndices, jetBTagCSV);
    const int numberOfBjets = bjetIndices.size();
    const bool hasBtag = numberOfBjets > 0;
    
    // Get MET
    const LV& met = *recoObjects.met_;
    const bool hasMetOrEmu = channel_=="emu" || met.pt()>MetCUT;
    
    const tth::RecoObjectIndices recoObjectIndices(allLeptonIndices,
                                                   leptonIndices, antiLeptonIndices,
                                                   leptonIndex, antiLeptonIndex,
                                                   leadingLeptonIndex, nLeadingLeptonIndex,
                                                   leptonXIndex, leptonYIndex,
                                                   jetIndices, jetIndexPairs,
                                                   bjetIndices);
    
    const tth::GenObjectIndices genObjectIndicesDummy(-1, -1, -1, -1, -1, -1, -1, -1);
    
    const int jetCategoryId_overview = jetCategories_overview_->categoryId(numberOfJets,numberOfBjets);
    const int jetCategoryId = jetCategories_->categoryId(numberOfJets,numberOfBjets);
    
    
    // Determine all reco level weights
    const double weightLeptonSF = this->weightLeptonSF(leadingLeptonIndex, nLeadingLeptonIndex, allLeptons, lepPdgId);
    const double weightTriggerSF = this->weightTriggerSF(leptonXIndex, leptonYIndex, allLeptons);
    const double weightNoPileup = trueLevelWeightNoPileup*weightTriggerSF*weightLeptonSF;
    // We do not apply a b-tag scale factor
    //const double weightBtagSF = ReTagJet ? 1. : this->weightBtagSF(jetIndices, jets, jetPartonFlavour);
    constexpr double weightBtagSF = 1.;

    // The weight to be used for filling the histograms
    double weight = weightNoPileup*weightPU;
    
    
    tth::RecoLevelWeights recoLevelWeights(weightLeptonSF, weightTriggerSF, weightBtagSF,
                                           weightNoPileup, weight);
    
    
    // ++++ Control Plots ++++
    
    this->fillAll(selectionStep,
                  recoObjects, commonGenObjects,
                  topGenObjectsDummy, higgsGenObjectsDummy,
                  kinRecoObjectsDummy,
                  genObjectIndicesDummy, recoObjectIndices,
                  genLevelWeights, recoLevelWeights,
                  1.);
    
    h_jetCategories_overview_step1->Fill(jetCategoryId_overview, 1);



    //===CUT===
    selectionStep = "2";
    
    // we need an OS lepton pair matching the trigger selection...
    if (!hasLeptonPair) return kTRUE;

    // ++++ Control Plots ++++
    
    this->fillAll(selectionStep,
                  recoObjects, commonGenObjects,
                  topGenObjectsDummy, higgsGenObjectsDummy,
                  kinRecoObjectsDummy,
                  genObjectIndicesDummy, recoObjectIndices,
                  genLevelWeights, recoLevelWeights,
                  weight);
    
    // FIXME: should also here apply weights
    h_jetCategories_overview_step2->Fill(jetCategoryId_overview, 1);



    //===CUT===
    selectionStep = "3";
    
    // ...with at least 20 GeV invariant mass
    if (dilepton.M() < 20.) return kTRUE;
    
    const bool isZregion = dilepton.M() > 76 && dilepton.M() < 106;
    KinRecoObjects* kinRecoObjectsPtr(0);
    const bool hasSolution = this->calculateKinReco(leptonIndex, antiLeptonIndex, jetIndices,
                                                    allLeptons, jets, jetBTagCSV, met,
                                                    kinRecoObjectsPtr);
    
    
    
    // ++++ Control Plots ++++
    
    this->fillAll(selectionStep,
                  recoObjects, commonGenObjects,
                  topGenObjectsDummy, higgsGenObjectsDummy,
                  *kinRecoObjectsPtr,
                  genObjectIndicesDummy, recoObjectIndices,
                  genLevelWeights, recoLevelWeights,
                  weight);
    
    h_jetCategories_overview_step3->Fill(jetCategoryId_overview, weight);
    
    
    
    // ****************************************
    //handle inverted Z cut
    // Z window plots need to be filled here, in order to rescale the contribution to data
    if(isZregion){
        selectionStep = "4zWindow";
        
        this->fillAll(selectionStep,
                      recoObjects, commonGenObjects,
                      topGenObjectsDummy, higgsGenObjectsDummy,
                      kinRecoObjectsDummy,
                      genObjectIndicesDummy, recoObjectIndices,
                      genLevelWeights, recoLevelWeights,
                      weight);
        
        if(has2Jets){
            selectionStep = "5zWindow";
            
            this->fillAll(selectionStep,
                          recoObjects, commonGenObjects,
                          topGenObjectsDummy, higgsGenObjectsDummy,
                          kinRecoObjectsDummy,
                          genObjectIndicesDummy, recoObjectIndices,
                          genLevelWeights, recoLevelWeights,
                          weight);
            
            if(hasMetOrEmu){
                selectionStep = "6zWindow";
                
                this->fillAll(selectionStep,
                              recoObjects, commonGenObjects,
                              topGenObjectsDummy, higgsGenObjectsDummy,
                              kinRecoObjectsDummy,
                              genObjectIndicesDummy, recoObjectIndices,
                              genLevelWeights, recoLevelWeights,
                              weight);
                
                if(hasBtag){
                    selectionStep = "7zWindow";
                    
                    // FIXME: do not use b-tag scale factor
                    //weightBtagSF = isMC ? calculateBtagSF() : 1;
                    //fullWeights *= weightBtagSF;
                    
                    this->fillAll(selectionStep,
                                  recoObjects, commonGenObjects,
                                  topGenObjectsDummy, higgsGenObjectsDummy,
                                  kinRecoObjectsDummy,
                                  genObjectIndicesDummy, recoObjectIndices,
                                  genLevelWeights, recoLevelWeights,
                                  weight);
                    
                    if(hasSolution){
                        selectionStep = "8zWindow";
                        
                        // FIXME: weightKinFit is just a constant, but is it valid for each event selection (jetCategories) and can be used here?
                        //fullWeights *= weightKinFit;
                        
                        this->fillAll(selectionStep,
                                      recoObjects, commonGenObjects,
                                      topGenObjectsDummy, higgsGenObjectsDummy,
                                      kinRecoObjectsDummy,
                                      genObjectIndicesDummy, recoObjectIndices,
                                      genLevelWeights, recoLevelWeights,
                                      weight);
                    }
                }
            }
        }
    }
    
    
    
    //=== CUT ===
    selectionStep = "4";
    
    //Exclude the Z window
    if(channel_!="emu" && isZregion) return kTRUE;

    // ++++ Control Plots ++++
    
    this->fillAll(selectionStep,
                  recoObjects, commonGenObjects,
                  topGenObjectsDummy, higgsGenObjectsDummy,
                  *kinRecoObjectsPtr,
                  genObjectIndicesDummy, recoObjectIndices,
                  genLevelWeights, recoLevelWeights,
                  weight);
    
    h_jetCategories_overview_step4->Fill(jetCategoryId_overview, weight);
    
    
    
    //=== CUT ===
    selectionStep = "5";
    
    //Require at least two jets
    if(!has2Jets) return kTRUE;

    // ++++ Control Plots ++++
    
    this->fillAll(selectionStep,
                  recoObjects, commonGenObjects,
                  topGenObjectsDummy, higgsGenObjectsDummy,
                  *kinRecoObjectsPtr,
                  genObjectIndicesDummy, recoObjectIndices,
                  genLevelWeights, recoLevelWeights,
                  weight);
    
    h_jetCategories_overview_step5->Fill(jetCategoryId_overview, weight);



    //=== CUT ===
    selectionStep = "6";
    
    //Require MET > 40 GeV in non-emu channels
    if(!hasMetOrEmu) return kTRUE;

    // ++++ Control Plots ++++
    
    this->fillAll(selectionStep,
                  recoObjects, commonGenObjects,
                  topGenObjectsDummy, higgsGenObjectsDummy,
                  *kinRecoObjectsPtr,
                  genObjectIndicesDummy, recoObjectIndices,
                  genLevelWeights, recoLevelWeights,
                  weight);
    
    h_jetCategories_overview_step6->Fill(jetCategoryId_overview, weight);

    // Fill the b-tagging efficiency plots
    if(this->makeBtagEfficiencies()){
        btagScaleFactors_->fillBtagHistograms(jetIndices, bjetIndices,
                                              jets, jetPartonFlavour,
                                              weight, static_cast<std::string>(channel_));
    }
    
    
    
    //=== CUT ===
    selectionStep = "7";
    
    //Require at least one b tagged jet
    if(!hasBtag) return kTRUE;

    weight *= weightBtagSF;

    // ++++ Control Plots ++++
    
    this->fillAll(selectionStep,
                  recoObjects, commonGenObjects,
                  topGenObjectsDummy, higgsGenObjectsDummy,
                  *kinRecoObjectsPtr,
                  genObjectIndicesDummy, recoObjectIndices,
                  genLevelWeights, recoLevelWeights,
                  weight);
    
    h_jetCategories_overview_step7->Fill(jetCategoryId_overview, weight);




    //=== CUT ===
    selectionStep = "8";
    
    //Require at least one solution for the kinematic event reconstruction
    if(!hasSolution) return kTRUE;
    // FIXME: weightKinFit is just a constant, but is it valid for each event selection (jetCategories) and can be used here?
    //weight *= weightKinFit;
    
    
    
    // === FULL GEN OBJECT SELECTION ===
    
    // Access top generator object struct, and higgs generator object struct
    const TopGenObjects& topGenObjects = this->getTopGenObjects(entry);
    const HiggsGenObjects& higgsGenObjects = this->getHiggsGenObjects(entry);
    
    // Do jet matchings for ttbar system
    int genBjetFromTopIndex(-1);
    int genAntiBjetFromTopIndex(-1);
    int matchedBjetFromTopIndex(-1);
    int matchedAntiBjetFromTopIndex(-1);
    if(isTopSignal_){
        const VLV& allGenJets = *commonGenObjects.allGenJets_;
        // Find gen-level b jet and anti-b jet corresponding to (anti)b from (anti)top
        // FIXME: should one clean the genJetCollection to remove low-pt (or high-eta) jets?
        if(this->getGenBjetIndices(genBjetFromTopIndex, genAntiBjetFromTopIndex, topGenObjects, 6)){
            // Match recoJets to the two selected genJets from (anti)top
            this->matchRecoToGenJets(matchedBjetFromTopIndex, matchedAntiBjetFromTopIndex,
                                     jetIndices,
                                     jets,
                                     &allGenJets.at(genBjetFromTopIndex), &allGenJets.at(genAntiBjetFromTopIndex));
        }
    }
    
    // Do jet matchings for Higgs system
    int genBjetFromHiggsIndex(-1);
    int genAntiBjetFromHiggsIndex(-1);
    int matchedBjetFromHiggsIndex(-1);
    int matchedAntiBjetFromHiggsIndex(-1);
    // FIXME: should not use higgsDecayMode_, but specific method
    if(isHiggsSignal_ && higgsDecayMode_==5){
        const VLV& allGenJets = *commonGenObjects.allGenJets_;
        // Find gen-level b jet and anti-b jet corresponding to (anti)b from Higgs
        // FIXME: should one clean the genJetCollection to remove low-pt (or high-eta) jets?
        if(this->getGenBjetIndices(genBjetFromHiggsIndex, genAntiBjetFromHiggsIndex, topGenObjects, 25)){
            // Match recoJets to the two selected genJets from Higgs
            this->matchRecoToGenJets(matchedBjetFromHiggsIndex, matchedAntiBjetFromHiggsIndex,
                                     jetIndices,
                                     jets,
                                     &allGenJets.at(genBjetFromHiggsIndex), &allGenJets.at(genAntiBjetFromHiggsIndex));
        }
    }

    const tth::GenObjectIndices genObjectIndices(genBjetFromTopIndex, genAntiBjetFromTopIndex,
                                                 matchedBjetFromTopIndex, matchedAntiBjetFromTopIndex,
                                                 genBjetFromHiggsIndex, genAntiBjetFromHiggsIndex,
                                                 matchedBjetFromHiggsIndex, matchedAntiBjetFromHiggsIndex);
    
    
    
    // ++++ Control Plots ++++
    
    this->fillAll(selectionStep,
                  recoObjects, commonGenObjects,
                  topGenObjects, higgsGenObjects,
                  *kinRecoObjectsPtr,
                  genObjectIndices, recoObjectIndices,
                  genLevelWeights, recoLevelWeights,
                  weight);
    
//    FillBinnedControlPlot(h_jetCategories_step8, jetCategoryId, h_events_step8, 1, weight);

    h_jetCategories_step8->Fill(jetCategoryId, weight);
    h_jetCategories_overview_step8->Fill(jetCategoryId_overview, weight);

    // Fill jet quantities
    for(const auto& index : jetIndices){
        h_jetPt_step8->Fill(jets.at(index).pt(), weight);
//        h_jetChargeGlobalPtWeighted_step8->Fill(jetChargeGlobalPtWeighted.at(index), weight);
        h_jetChargeRelativePtWeighted_step8->Fill(jetChargeRelativePtWeighted.at(index), weight);
        FillBinnedControlPlot(h_jetCategories_step8, jetCategoryId, h_jetPt_step8, jets.at(index).pt(), weight);
//        FillBinnedControlPlot(h_jetCategories_step8, jetCategoryId, h_jetChargeGlobalPtWeighted_step8, jetChargeGlobalPtWeighted.at(index), weight);
        FillBinnedControlPlot(h_jetCategories_step8, jetCategoryId, h_jetChargeRelativePtWeighted_step8, jetChargeRelativePtWeighted.at(index), weight);
    }
    
    
    // Passing information to DijetAnalyzer
    if(dijetAnalyzer_) {
        const VLV& allGenJets = *commonGenObjects.allGenJets_;
        const std::vector<int>& genBHadJetIndex = *topGenObjects.genBHadJetIndex_;
        const std::vector<int>& genBHadFlavour = *topGenObjects.genBHadFlavour_;
        
        // Push_back indices of top b-jets identified by kinematic reconstruction
        std::vector<int> topJetIds;
        if(kinRecoObjectsPtr){
            topJetIds.push_back(kinRecoObjectsPtr->HypJet0index_->at(0));
            topJetIds.push_back(kinRecoObjectsPtr->HypJet1index_->at(0));
        }
        
        DijetAnalyzer::Input dijetInput(jets, jetIndices, bjetIndices,
                                        jetBTagCSV, topJetIds, allGenJets,
                                        genBHadJetIndex, genBHadFlavour,
                                        met, allLeptons.at(leptonIndex), allLeptons.at(antiLeptonIndex)
                                       );

        dijetAnalyzer_->fill(dijetInput, weight);
    }
    
    
    return kTRUE;
}



tth::IndexPairs HiggsAnalysis::chargeOrderedJetPairIndices(const std::vector<int>& jetIndices,
                                                           const std::vector<double>& jetCharges)
{
    tth::IndexPairs result;
    if(jetIndices.size() < 2) return result;
    
    // Loop over all jet combinations
    for(std::vector<int>::const_iterator i_jetIndex = jetIndices.begin(); i_jetIndex != --(jetIndices.end()); ++i_jetIndex){
        std::vector<int>::const_iterator incrementIterator(i_jetIndex);
        ++incrementIterator;
        for(std::vector<int>::const_iterator j_jetIndex = incrementIterator; j_jetIndex != jetIndices.end(); ++j_jetIndex){
            // Get the indices of b and anti-b jet defined by jet charge
            int bIndex = *i_jetIndex;
            int antiBIndex = *j_jetIndex;
            ttbar::orderIndices(antiBIndex, bIndex, jetCharges);
            
            result.push_back(std::make_pair(antiBIndex, bIndex));
        }
    }
    
    return result;
}



bool HiggsAnalysis::getGenBjetIndices(int& genBjetIndex, int& genAntiBjetIndex,
                                      const TopGenObjects& topGenObjects, const int pdgId)
{
    if(!pdgId>0){
        std::cerr<<"ERROR! Method getGenBJetIndices needs a pdgId>0, but used is: "<<pdgId
                 <<"\n...break\n\n";
        exit(71);
    }
    
    const std::vector<int>& genBHadFlavour(*topGenObjects.genBHadFlavour_);
    const std::vector<int>& genBHadJetIndex(*topGenObjects.genBHadJetIndex_);
    
    for(size_t iBHadron=0; iBHadron<genBHadFlavour.size(); ++iBHadron){
        const int flavour = genBHadFlavour.at(iBHadron);
        if(abs(flavour) != abs(pdgId)) continue;     // Skipping hadrons with the wrong flavour
        // Assigning jet index of corresponding hadron. Set to -2 if >1 hadrons found for the same flavour
        if(flavour>0) genBjetIndex = (genBjetIndex==-1) ? genBHadJetIndex.at(iBHadron) : -2;
        else if(flavour<0) genAntiBjetIndex = (genAntiBjetIndex==-1) ? genBHadJetIndex.at(iBHadron) : -2;
    }

    // If no unique match of jets from (anti)b from (anti)top is found, return false
    if(genBjetIndex<0 || genAntiBjetIndex<0){
        return false;
    }
    return true;
}



bool HiggsAnalysis::matchRecoToGenJets(int& matchedBjetIndex, int& matchedAntiBjetIndex,
                                       const std::vector<int>& jetIndices,
                                       const VLV& jets,
                                       const LV* genBjet, const LV* genAntiBjet)
{
    using ROOT::Math::VectorUtil::DeltaR;

    // Find closest jet and its distance in deltaR
    double deltaRBjet(999.);
    double deltaRAntiBjet(999.);
    for(const auto& index : jetIndices){
        float deltaR = DeltaR(*genBjet, jets.at(index));
        if(deltaR < deltaRBjet){
            deltaRBjet = deltaR;
            matchedBjetIndex = index;
        }
        deltaR = DeltaR(*genAntiBjet, jets.at(index));
        if(deltaR < deltaRAntiBjet){
            deltaRAntiBjet = deltaR;
            matchedAntiBjetIndex = index;
        }
    }

    // Call a jet matched if it is close enough (should this be a configurable parameter?)
    if(deltaRBjet>0.3) matchedBjetIndex = -1;
    if(deltaRAntiBjet>0.3) matchedAntiBjetIndex = -1;

    // Check if both gen jets are successfully matched to different reco jets
    if(matchedBjetIndex==-1 || matchedAntiBjetIndex==-1 || matchedBjetIndex == matchedAntiBjetIndex) return false;

    return true;
}



void HiggsAnalysis::SetHiggsInclusiveSample(const bool isInclusiveHiggs)
{
    isInclusiveHiggs_ = isInclusiveHiggs;
}



void HiggsAnalysis::SetHiggsInclusiveSeparation(const bool bbbarDecayFromInclusiveHiggs)
{
    bbbarDecayFromInclusiveHiggs_ = bbbarDecayFromInclusiveHiggs;
}



void HiggsAnalysis::SetAnalysisModes(const std::vector<AnalysisMode::AnalysisMode>& analysisModes)
{
    analysisModes_ = analysisModes;
}



void HiggsAnalysis::SetJetCategoriesOverview(const JetCategories& jetCategories)
{
    jetCategories_overview_ = &jetCategories;
}



void HiggsAnalysis::SetMvaInputProduction(MvaInputTopJetsVariables* mvaInputTopJetsVariables)
{
    mvaInputTopJetsVariables_ = mvaInputTopJetsVariables;
}



void HiggsAnalysis::SetJetCategoriesAnalysis(const JetCategories& jetCategories)
{
    jetCategories_ = &jetCategories;
}



bool HiggsAnalysis::failsHiggsGeneratorSelection(const Long64_t& entry)const
{
    if(!isHiggsSignal_) return false;
    GetHiggsDecayModeEntry(entry);
    // Separate ttH events from inclusve decay into H->bbbar and other decays
    // FIXME: do not use directly higgsDecayMode_, but a function
    if(isInclusiveHiggs_ && !bbbarDecayFromInclusiveHiggs_ && higgsDecayMode_==5) return true;
    if(isInclusiveHiggs_ && bbbarDecayFromInclusiveHiggs_ && higgsDecayMode_!=5) return true;
    return false;
}



bool HiggsAnalysis::failsAdditionalJetFlavourSelection(const Long64_t& entry)const
{
    if(!isTopSignal_) return false;
    if(isHiggsSignal_) return false;
    
    // FIXME: this is a workaround as long as there is no specific additional jet flavour info written to nTuple
    const TopGenObjects& topGenObjects = this->getTopGenObjects(entry);
    const int nGenBJets = topGenObjects.genBHadIndex_->size();
    if(runWithTtbb_ && nGenBJets<=2) return true;
    if(!runWithTtbb_ && nGenBJets>2) return true;
    
    return false;
}



void HiggsAnalysis::SetEventYieldHistograms(EventYieldHistograms* eventYieldHistograms)
{
    eventYieldHistograms_ = eventYieldHistograms;
}



void HiggsAnalysis::SetDyScalingHistograms(DyScalingHistograms* dyScalingHistograms)
{
    dyScalingHistograms_ = dyScalingHistograms;
}



void HiggsAnalysis::SetBasicHistograms(BasicHistograms* basicHistograms)
{
    basicHistograms_ = basicHistograms;
}



void HiggsAnalysis::SetMvaValidation(MvaValidation* mvaValidation)
{
    mvaValidation_ = mvaValidation;
}



void HiggsAnalysis::SetPlayground(Playground* playground)
{
    playground_ = playground;
}



void HiggsAnalysis::SetDijetAnalyzer(DijetAnalyzer* analyzer)
{
    dijetAnalyzer_ = analyzer;
}



void HiggsAnalysis::SetRunWithTtbb(const bool runWithTtbb)
{
    runWithTtbb_ = runWithTtbb;
}



void HiggsAnalysis::fillAll(const std::string& selectionStep,
                            const RecoObjects& recoObjects, const CommonGenObjects& commonGenObjects,
                            const TopGenObjects& topGenObjects, const HiggsGenObjects& higgsGenObjects,
                            const KinRecoObjects& kinRecoObjects,
                            const tth::GenObjectIndices& genObjectIndices, const tth::RecoObjectIndices& recoObjectIndices,
                            const tth::GenLevelWeights& genLevelWeights, const tth::RecoLevelWeights& recoLevelWeights,
                            const double& defaultWeight)const
{
    if(eventYieldHistograms_) eventYieldHistograms_->fill(defaultWeight, selectionStep);
    if(dyScalingHistograms_) dyScalingHistograms_->fill(recoObjects, recoObjectIndices, defaultWeight, selectionStep);
    if(basicHistograms_) basicHistograms_->fill(recoObjects, recoObjectIndices, defaultWeight, selectionStep);
    if(playground_) playground_->fill(recoObjects, commonGenObjects, topGenObjects, higgsGenObjects, kinRecoObjects,
                                      genObjectIndices, recoObjectIndices,
                                      genLevelWeights, recoLevelWeights, defaultWeight,
                                      selectionStep);
    if(mvaInputTopJetsVariables_) mvaInputTopJetsVariables_->fillForInputProduction(recoObjects,
                                                                                    genObjectIndices, recoObjectIndices,
                                                                                    defaultWeight, selectionStep);

    if(mvaValidation_) mvaValidation_->fill(recoObjects, genObjectIndices, recoObjectIndices, defaultWeight, selectionStep);
}



void HiggsAnalysis::bookAll()
{
    if(eventYieldHistograms_) eventYieldHistograms_->book(fOutput);
    if(dyScalingHistograms_) dyScalingHistograms_->book(fOutput);
    if(basicHistograms_) basicHistograms_->book(fOutput);
    if(mvaValidation_) mvaValidation_->book(fOutput);
    if(playground_) playground_->book(fOutput);
    
    // Setting the output for DijetAnalyzer
    // FIXME: where are the steps for dijet analyzer set? not existing ???
    if(dijetAnalyzer_) dijetAnalyzer_->setOutputSelectorList(fOutput);
}



void HiggsAnalysis::clearAll()
{
    if(eventYieldHistograms_) eventYieldHistograms_->clear();
    if(dyScalingHistograms_) dyScalingHistograms_->clear();
    if(basicHistograms_) basicHistograms_->clear();
    if(mvaValidation_) mvaValidation_->clear();
    if(playground_) playground_->clear();
    if(dijetAnalyzer_) dijetAnalyzer_->clear();
}








