#define HiggsAnalysis_cxx

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <utility>

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
#include "../../diLeptonic/src/analysisUtils.h"
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


// FIXME: move this also to load_HiggsAnalysis
/// Folder for storage of MVA input TTree
constexpr const char* MvaInputDIR = "mvaInput";










HiggsAnalysis::HiggsAnalysis(TTree*):
runWithTtbb_(false),
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
    if(this->makeBtagEfficiencies()) btagScaleFactors_->produceBtagEfficiencies(static_cast<std::string>(channel_));

    // Do everything needed for MVA
    if(analysisMode_ == AnalysisMode::mva){

        // Create output directory for MVA input tree, and produce and write tree
        std::string f_savename = ttbar::assignFolder(MvaInputDIR, channel_, systematic_);
        f_savename.append(outputfilename_);
        mvaInputTopJetsVariables_.produceMvaInputTree(f_savename);
        //mvaInputTopJetsVariables_.produceMvaInputTree(fOutput);

        // Create and store control plots in fOutput
        mvaInputTopJetsVariables_.mvaInputVariablesControlPlots(fOutput);
    }

    // Cleanup
    mvaInputTopJetsVariables_.clear();
    if(dijetAnalyzer_) dijetAnalyzer_->clear();
    // FIXME: shouldn't we also clear b-tagging efficiency histograms if they are produced ?

    // Defaults from AnalysisBase
    AnalysisBase::Terminate();
}



void HiggsAnalysis::SlaveBegin(TTree *)
{
    // Defaults from AnalysisBase
    AnalysisBase::SlaveBegin(0);

    // Setting the output for DijetAnalyzer
    if(dijetAnalyzer_) dijetAnalyzer_->setOutputSelectorList(fOutput);


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


    // Histograms needed for cutflow tables
    h_events_step0a = store(new TH1D("events_step0a","event count (no weight);;# events",8,0,8));
    h_events_step0b = store(new TH1D("events_step0b","event count (no weight);;# events",8,0,8));
    h_events_step1 = store(new TH1D("events_step1","event count (no weight);;# events",8,0,8));
    h_events_step2 = store(new TH1D("events_step2","event count (no weight);;# events",8,0,8));
    h_events_step3 = store(new TH1D("events_step3","event count (no weight);;# events",8,0,8));
    h_events_step4 = store(new TH1D("events_step4","event count at after 2lepton;;# events",8,0,8));
    h_events_step5 = store(new TH1D("events_step5","event count at after Zcut;;# events",8,0,8));
    h_events_step6 = store(new TH1D("events_step6","event count at after 2jets;;# events",8,0,8));
    h_events_step7 = store(new TH1D("events_step7","event count at after MET;;# events",8,0,8));
    h_events_step8 = store(new TH1D("events_step8","event count at after 1btag;;# events",8,0,8));
    h_events_step0a->Sumw2();
    h_events_step0b->Sumw2();
    h_events_step1->Sumw2();
    h_events_step2->Sumw2();
    h_events_step3->Sumw2();
    h_events_step4->Sumw2();
    h_events_step5->Sumw2();
    h_events_step6->Sumw2();
    h_events_step7->Sumw2();
    h_events_step8->Sumw2();


    // Histograms needed for data-driven scaling of Z samples
    dyScalingHistograms_.addStep("4", fOutput);
    dyScalingHistograms_.addStep("5", fOutput);
    dyScalingHistograms_.addStep("6", fOutput);
    dyScalingHistograms_.addStep("7", fOutput);
    dyScalingHistograms_.addStep("8", fOutput);


    // Basic histograms
    basicHistograms_.addStep("1", fOutput);
    basicHistograms_.addStep("2", fOutput);
    basicHistograms_.addStep("3", fOutput);
    basicHistograms_.addStep("4", fOutput);
    basicHistograms_.addStep("5", fOutput);
    basicHistograms_.addStep("6", fOutput);
    basicHistograms_.addStep("7", fOutput);
    basicHistograms_.addStep("8", fOutput);


    // Control plots
    h_jetPt_step8 = store(new TH1D("jetPt_step8", "jet pt;p_{t}  [GeV];# jets", 40, 0, 400));
    h_jetChargeGlobalPtWeighted_step8 = store(new TH1D("jetChargeGlobalPtWeighted_step8", "jetChargeGlobalPtWeighted; c_{jet}^{glob};# jets", 110, -1.1, 1.1));
    h_jetChargeRelativePtWeighted_step8 = store(new TH1D("jetChargeRelativePtWeighted_step8", "jetChargeRelativePtWeighted; c_{jet}^{rel};# jets", 110, -1.1, 1.1));

    h_matchedBjetsFromTop_step8 = store(new TH1D("matchedBjetsFromTop_step8","matchedBjetsFromTop;;# events",3,0,3));
    h_matchedBjetsFromTop_step8->GetXaxis()->SetBinLabel(1, "bQuark-genJet fail");
    h_matchedBjetsFromTop_step8->GetXaxis()->SetBinLabel(2, "genJet-recoJet fail");
    h_matchedBjetsFromTop_step8->GetXaxis()->SetBinLabel(3, "Matched");

    h_matchedBjetsFromHiggs_step8 = store(new TH1D("matchedBjetsFromHiggs_step8","matchedBjetsFromHiggs;;# events",3,0,3));
    h_matchedBjetsFromHiggs_step8->GetXaxis()->SetBinLabel(1, "bQuark-genJet fail");
    h_matchedBjetsFromHiggs_step8->GetXaxis()->SetBinLabel(2, "genJet-recoJet fail");
    h_matchedBjetsFromHiggs_step8->GetXaxis()->SetBinLabel(3, "Matched");

    h_mvaBasedJetsFromTop_step8 = store(new TH1D("mvaBasedJetsFromTop_step8","mvaBasedJetsFromTop;;# events",4,0,4));
    h_mvaBasedJetsFromTop_step8->GetXaxis()->SetBinLabel(1, "matched Top jets");
    h_mvaBasedJetsFromTop_step8->GetXaxis()->SetBinLabel(2, "pair from Top");
    h_mvaBasedJetsFromTop_step8->GetXaxis()->SetBinLabel(3, "correct pair");
    h_mvaBasedJetsFromTop_step8->GetXaxis()->SetBinLabel(4, "swapped pair");

    h_mvaBasedJetsFromHiggs_step8 = store(new TH1D("mvaBasedJetsFromHiggs_step8","mvaBasedJetsFromHiggs;;# events",4,0,4));
    h_mvaBasedJetsFromHiggs_step8->GetXaxis()->SetBinLabel(1, "matched Higgs jets");
    h_mvaBasedJetsFromHiggs_step8->GetXaxis()->SetBinLabel(2, "pair from Higgs");
    h_mvaBasedJetsFromHiggs_step8->GetXaxis()->SetBinLabel(3, "overlap with Top");
    h_mvaBasedJetsFromHiggs_step8->GetXaxis()->SetBinLabel(4, "Fully solved");

    h_dijetMass_step8 = store(new TH1D("dijetMass_step8", "dijetMass;m_{jj} [GeV];# events", 100, 0, 500));
    h_mvaBasedDijetMass_step8 = store(new TH1D("mvaBasedDijetMass_step8", "mvaBasedDijetMass;m_{jj} [GeV];# events", 100, 0, 500));

    p_dijetMassVsJetCategories = store(new TProfile("dijetMassVsJetCategories", "dijetMassVsJetCategories;# jets/b-jets;m_{jj} [GeV]",numberOfCategories_overview, 0, numberOfCategories_overview, "s"));
    p_dijetMassVsMvaWeightHigh = store(new TProfile("dijetMassVsMvaWeightHigh", "dijetMassVsMvaWeightHigh;w_{MVA,1};m_{jj} [GeV]",20, -1, 0, "s"));
    p_dijetMassVsMvaWeightDiff = store(new TProfile("dijetMassVsMvaWeightDiff", "dijetMassVsMvaWeightDiff;w_{MVA,1} - w_{MVA,2};m_{jj} [GeV]",20, 0, 2, "s"));

    p_mvaBasedDijetMassVsJetCategories = store(new TProfile("mvaBasedDijetMassVsJetCategories", "mvaBasedDijetMassVsJetCategories;# jets/b-jets;m_{jj} [GeV]",numberOfCategories_overview, 0, numberOfCategories_overview, "s"));
    p_mvaBasedDijetMassVsMvaWeightHigh = store(new TProfile("mvaBasedDijetMassVsMvaWeightHigh", "mvaBasedDijetMassVsMvaWeightHigh;w_{MVA,1};m_{jj} [GeV]",20, -1, 0, "s"));
    p_mvaBasedDijetMassVsMvaWeightDiff = store(new TProfile("mvaBasedDijetMassVsMvaWeightDiff", "mvaBasedDijetMassVsMvaWeightDiff;w_{MVA,1} - w_{MVA,2};m_{jj} [GeV]",20, 0, 2, "s"));

    for(std::vector<TString>::const_iterator i_binLabel = v_binLabel_overview.begin(); i_binLabel != v_binLabel_overview.end(); ++i_binLabel){
        const TString binLabel(*i_binLabel);
        int position = std::distance(v_binLabel_overview.begin(), i_binLabel) +1;
        p_dijetMassVsJetCategories->GetXaxis()->SetBinLabel(position, binLabel);
        p_mvaBasedDijetMassVsJetCategories->GetXaxis()->SetBinLabel(position, binLabel);
    }

    // Binned control plots
    CreateBinnedControlPlots(h_jetCategories_step8, h_events_step8, false);
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetPt_step8, false);
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetChargeGlobalPtWeighted_step8, false);
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetChargeRelativePtWeighted_step8, false);

    // Histograms for b-tagging efficiencies
    if(this->makeBtagEfficiencies()) btagScaleFactors_->bookBtagHistograms(fOutput, static_cast<std::string>(channel_));
}



void HiggsAnalysis::SlaveTerminate()
{
    dyScalingHistograms_.clear();
    basicHistograms_.clear();

    // Defaults from AnalysisBase
    AnalysisBase::SlaveTerminate();
}



Bool_t HiggsAnalysis::Process(Long64_t entry)
{
    // Defaults from AnalysisBase
    if(!AnalysisBase::Process(entry))return kFALSE;


    // Use utilities without namespaces
    using namespace ttbar;



    //===CUT===
    // this is step0a, no cut application

    // ++++ Control Plots ++++

    // Histogram for controlling correctness of af workflow,
    // which should be the same as h_events_step0b for all samples except those preselected on generator level
    h_events_step0a->Fill(1, 1);



    //===CUT===
    // this is step0b, select events on generator level and access true level weights

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

    // ++++ Control Plots ++++

    h_events_step0b->Fill(1, 1);



    //===CUT===
    // Check if event was triggered with the same dilepton trigger as the specified analysis channel
    if(this->failsDileptonTrigger(entry)) return kTRUE;



    // === FULL OBJECT SELECTION === (can thus be used at each selection step)

    // Access reco information
    this->GetRecoBranchesEntry(entry);

    // Access generator information common to all MC samples
    if(isMC_) this->GetCommonGenBranchesEntry(entry);

    // Systematics for jet energy resolution/scale
    // Corrections for: jets_, jetsForMET_, met_
    //if(doJesJer_)applyJER_JES();

    // Get allLepton indices, apply selection cuts and order them by pt (beginning with the highest value)
    std::vector<int> allLeptonIndices = initialiseIndices(*leptons_);
    selectIndices(allLeptonIndices, *leptons_, LVeta, LeptonEtaCUT, false);
    selectIndices(allLeptonIndices, *leptons_, LVeta, -LeptonEtaCUT);
    selectIndices(allLeptonIndices, *leptons_, LVpt, LeptonPtCut);
    orderIndices(allLeptonIndices, *leptons_, LVpt);
    const int numberOfAllLeptons = allLeptonIndices.size();

    // Get indices of leptons and antiLeptons separated by charge, and get the leading ones if they exist
    std::vector<int> leptonIndices = allLeptonIndices;
    std::vector<int> antiLeptonIndices = allLeptonIndices;
    selectIndices(leptonIndices, *lepPdgId_, 0);
    selectIndices(antiLeptonIndices, *lepPdgId_, 0, false);
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
        orderIndices(leadingLeptonIndex, nLeadingLeptonIndex, *leptons_, LVpt);
    }
    const bool hasLeptonPair = this->hasLeptonPair(leadingLeptonIndex, nLeadingLeptonIndex);

    // Get two indices of the two leptons in the right order for trigger scale factor, if existing
    int leptonXIndex(leadingLeptonIndex);
    int leptonYIndex(nLeadingLeptonIndex);
    if(hasLeptonPair){
        //in ee and mumu channel leptonX must be the highest pt lepton, i.e. this is already correct
        // in emu channel leptonX must be electron
        if(std::abs(lepPdgId_->at(leptonXIndex)) != std::abs(lepPdgId_->at(leptonYIndex))){
            orderIndices(leptonYIndex, leptonXIndex, *lepPdgId_, true);
        }
    }

    // Get dilepton system, if existing
    const LV dummyLV(0.,0.,0.,0.);
    const LV dilepton(hasLeptonPair ? leptons_->at(leadingLeptonIndex)+leptons_->at(nLeadingLeptonIndex) : dummyLV);

    // Get jet indices, apply selection cuts and order them by pt (beginning with the highest value)
    std::vector<int> jetIndices = initialiseIndices(*jets_);
    selectIndices(jetIndices, *jets_, LVeta, JetEtaCUT, false);
    selectIndices(jetIndices, *jets_, LVeta, -JetEtaCUT);
    selectIndices(jetIndices, *jets_, LVpt, JetPtCUT);
    orderIndices(jetIndices, *jets_, LVpt);
    const int numberOfJets = jetIndices.size();
    const bool has2Jets = numberOfJets > 1;

    // Get b-jet indices, apply selection cuts
    // and order b-jets by btag discriminator (beginning with the highest value)
    std::vector<int> bjetIndices = jetIndices;
    selectIndices(bjetIndices, *jetBTagCSV_, BtagWP);
    if (isMC_ && !(btagScaleFactors_->makeEfficiencies())){
        // Apply b-tag efficiency MC correction using random number based tag flipping
        btagScaleFactors_->indexOfBtags(bjetIndices, jetIndices,
                                        *jets_, *jetPartonFlavour_, *jetBTagCSV_,
                                        BtagWP, static_cast<std::string>(channel_));
    }
    orderIndices(bjetIndices, *jetBTagCSV_);
    const int numberOfBjets = bjetIndices.size();
    const bool hasBtag = numberOfBjets > 0;

    // Get MET
    const LV& met(*met_);
    const bool hasMetOrEmu = channel_=="emu" || met.Pt()>40;

    const int jetCategoryId_overview = jetCategories_overview_->categoryId(numberOfJets,numberOfBjets);
    const int jetCategoryId = jetCategories_->categoryId(numberOfJets,numberOfBjets);
    const BasicHistograms::Input basicHistogramsInput(leptonIndices, antiLeptonIndices,
                                                      jetIndices, bjetIndices,
                                                      *leptons_, *jets_, met,
                                                      *jetBTagCSV_);


    // Determine all reco level weights
    const double weightLeptonSF = this->weightLeptonSF(leadingLeptonIndex, nLeadingLeptonIndex);
    const double weightTriggerSF = this->weightTriggerSF(leptonXIndex, leptonYIndex);
    const double weightNoPileup = trueLevelWeightNoPileup*weightTriggerSF*weightLeptonSF;
    // We do not apply a b-tag scale factor
    //const double weightBtagSF = ReTagJet ? 1. : this->weightBtagSF(jetIndices);
    constexpr double weightBtagSF = 1.;

    // The weight to be used for filling the histograms
    double weight = weightNoPileup*weightPU;


    // ++++ Control Plots ++++

    h_events_step1->Fill(1, 1);
    basicHistograms_.fill(basicHistogramsInput, 1, "1");
    h_jetCategories_overview_step1->Fill(jetCategoryId_overview, 1);



    //===CUT===
    // we need an OS lepton pair
    if (!hasLeptonPair) return kTRUE;

    // ++++ Control Plots ++++

    // FIXME: should also here apply weights
    h_events_step2->Fill(1, 1);
    basicHistograms_.fill(basicHistogramsInput, 1, "2");
    h_jetCategories_overview_step2->Fill(jetCategoryId_overview, 1);



    //===CUT===
    // with at least 20 GeV invariant mass
    if (dilepton.M() < 20.) return kTRUE;

    // ++++ Control Plots ++++

    h_events_step3->Fill(1, weight);
    basicHistograms_.fill(basicHistogramsInput, weight, "3");
    h_jetCategories_overview_step3->Fill(jetCategoryId_overview, weight);



    // ****************************************
    //handle inverted Z cut
    const bool isZregion = dilepton.M() > 76 && dilepton.M() < 106;
    const bool hasSolution = calculateKinReco(leptonIndex, antiLeptonIndex, jetIndices, met);

    // Z window plots need to be filled here, in order to rescale the contribution to data
    if(isZregion){
        double fullWeights = weight;
        dyScalingHistograms_.fillZWindow(dilepton.M(), fullWeights, "4");

        if(has2Jets){
            // Fill loose dilepton mass histogram before any jet cuts
            dyScalingHistograms_.fillLoose(dilepton.M(), fullWeights);
            dyScalingHistograms_.fillZWindow(dilepton.M(), fullWeights, "5");

            if(hasMetOrEmu){
                dyScalingHistograms_.fillZWindow(dilepton.M(), fullWeights, "6");

                if(hasBtag){
                    // FIXME: do not use b-tag scale factor
                    //weightBtagSF = isMC ? calculateBtagSF() : 1;
                    //fullWeights *= weightBtagSF;
                    dyScalingHistograms_.fillZWindow(dilepton.M(), fullWeights, "7");

                    if(hasSolution){
                        // FIXME: weightKinFit is just a constant, but is it valid for each event selection (jetCategories) and can be used here?
                        //fullWeights *= weightKinFit;
                        dyScalingHistograms_.fillZWindow(dilepton.M(), fullWeights, "8");
                    }
                }
            }
        }
    }



    //=== CUT ===
    //Exclude the Z window
    if(channel_!="emu" && isZregion) return kTRUE;

    // ++++ Control Plots ++++

    if(!isZregion){ //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "4");
    }
    h_events_step4->Fill(1, weight);
    basicHistograms_.fill(basicHistogramsInput, weight, "4");
    h_jetCategories_overview_step4->Fill(jetCategoryId_overview, weight);



    //=== CUT ===
    //Require at least two jets > 30 GeV
    if(!has2Jets) return kTRUE;

    // ++++ Control Plots ++++

    if(!isZregion){ //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "5");
    }
    h_events_step5->Fill(1, weight);
    basicHistograms_.fill(basicHistogramsInput, weight, "5");
    h_jetCategories_overview_step5->Fill(jetCategoryId_overview, weight);



    //=== CUT ===
    //Require MET > 40 GeV in non-emu channels
    if(!hasMetOrEmu) return kTRUE;

    // ++++ Control Plots ++++

    if(!isZregion){ //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "6");
    }
    h_events_step6->Fill(1, weight);
    basicHistograms_.fill(basicHistogramsInput, weight, "6");
    h_jetCategories_overview_step6->Fill(jetCategoryId_overview, weight);

    // Fill the b-tagging efficiency plots
    if(this->makeBtagEfficiencies()){
        btagScaleFactors_->fillBtagHistograms(jetIndices, bjetIndices,
                                              *jets_, *jetPartonFlavour_,
                                              weight, static_cast<std::string>(channel_));
    }



    //=== CUT ===
    //Require at least one b tagged jet
    if(!hasBtag) return kTRUE;

    weight *= weightBtagSF;

    // ++++ Control Plots ++++

    if(!isZregion){ //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "7");
    }
    h_events_step7->Fill(1, weight);
    basicHistograms_.fill(basicHistogramsInput, weight, "7");
    h_jetCategories_overview_step7->Fill(jetCategoryId_overview, weight);




    //=== CUT ===
    //Require at least one solution for the kinematic event reconstruction
    if(!hasSolution) return kTRUE;
    // FIXME: weightKinFit is just a constant, but is it valid for each event selection (jetCategories) and can be used here?
    //weight *= weightKinFit;

    // ++++ Control Plots ++++

    if (!isZregion) { //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "8");
    }
    h_events_step8->Fill(1, weight);
    basicHistograms_.fill(basicHistogramsInput, weight, "8");
    FillBinnedControlPlot(h_jetCategories_step8, jetCategoryId, h_events_step8, 1, weight);

    h_jetCategories_step8->Fill(jetCategoryId, weight);
    h_jetCategories_overview_step8->Fill(jetCategoryId_overview, weight);

    // Fill jet quantities
    for(const auto& index : jetIndices){
        h_jetPt_step8->Fill(jets_->at(index).Pt(), weight);
        h_jetChargeGlobalPtWeighted_step8->Fill(jetChargeGlobalPtWeighted_->at(index), weight);
        h_jetChargeRelativePtWeighted_step8->Fill(jetChargeRelativePtWeighted_->at(index), weight);
        FillBinnedControlPlot(h_jetCategories_step8, jetCategoryId, h_jetPt_step8, jets_->at(index).Pt(), weight);
        FillBinnedControlPlot(h_jetCategories_step8, jetCategoryId, h_jetChargeGlobalPtWeighted_step8, jetChargeGlobalPtWeighted_->at(index), weight);
        FillBinnedControlPlot(h_jetCategories_step8, jetCategoryId, h_jetChargeRelativePtWeighted_step8, jetChargeRelativePtWeighted_->at(index), weight);
    }




    // Passing information to DijetAnalyzer
    if(dijetAnalyzer_) {
        if(isTopSignal_) this->GetTopSignalBranchesEntry(entry);
        // Push_back indices of top b-jets identified by kinematic reconstruction
        std::vector<int> topJetIds;
        if(HypJet0index_->size()>0) topJetIds.push_back(HypJet0index_->at(0));
        if(HypJet1index_->size()>0) topJetIds.push_back(HypJet1index_->at(0));

        DijetAnalyzer::Input dijetInput(*jets_, jetIndices, bjetIndices,
                                        *jetBTagCSV_, topJetIds, *allGenJets_,
                                        *genBHadJetIndex_, *genBHadFlavour_,
                                        met, leptons_->at(leptonIndex), leptons_->at(antiLeptonIndex)
                                       );

        dijetAnalyzer_->fill(dijetInput,weight);
    }



    if(analysisMode_ != AnalysisMode::mva)return kTRUE;

    // FIXME: which events exactly to fill? For now all with at least 4 jets
    if(numberOfJets<4)return kTRUE;


    // Find b jet and anti-b jet corresponding to (anti)b from (anti)top
    LV* genBjetFromTop(0);
    LV* genAntiBjetFromTop(0);
    if(isTopSignal_){
        this->GetTopSignalBranchesEntry(entry);
        int genBjetIndex(-1);
        int genAntiBjetIndex(-1);
        // FIXME: should one clean the genJetCollection to remove low-pt (or low-eta) jets?
        if(this->getGenBJetIndices(genBjetIndex, genAntiBjetIndex, 6)){
            genBjetFromTop = &(allGenJets_->at(genBjetIndex));
            genAntiBjetFromTop = &(allGenJets_->at(genAntiBjetIndex));
        }
        else{
            h_matchedBjetsFromTop_step8->Fill(0.1, weight);
        }
    }

    // Match recoJets to the two selected genJets from (anti)top
    int matchedBjetFromTopIndex(-1);
    int matchedAntiBjetFromTopIndex(-1);
    bool successfulTopMatching(false);
    if(genBjetFromTop && genAntiBjetFromTop){
        successfulTopMatching = this->matchRecoToGenJets(matchedBjetFromTopIndex, matchedAntiBjetFromTopIndex,
                                                         jetIndices,
                                                         genBjetFromTop, genAntiBjetFromTop);
        if(!successfulTopMatching) h_matchedBjetsFromTop_step8->Fill(1.1, weight);
        else h_matchedBjetsFromTop_step8->Fill(2.1, weight);
    }

    // Fill a vector with all jet pair indices, while sorting each pair by the jet charge:
    // first entry is antiBIndex i.e. with higher jet charge, second entry is bIndex
    const IndexPairs& jetIndexPairs = this->chargeOrderedJetPairIndices(jetIndices, *jetChargeRelativePtWeighted_);

    // Calculate the jet recoil for each jet pair, and put it in a vector of same size
    const VLV& jetRecoils = this->recoilForJetPairs(jetIndexPairs, jetIndices, *jets_);

    // Loop over all jet combinations and get MVA input variables
    const std::vector<MvaInputTopJetsVariables::Input>& v_mvaInput =
                        this->fillMvaInputTopJetsVariables(leptonIndex, antiLeptonIndex,
                                                           jetIndexPairs, jetRecoils,
                                                           matchedBjetFromTopIndex, matchedAntiBjetFromTopIndex,
                                                           met,
                                                           successfulTopMatching, weight);

    // Get the MVA weights from weights file as vector, one entry per jet pair
    const std::vector<float>& mvaWeightsCorrect = mvaWeightsCorrect_->mvaWeights(v_mvaInput);
    const std::vector<float>& mvaWeightsSwapped = mvaWeightsSwapped_->mvaWeights(v_mvaInput);

    // Fill the MVA TTree
    mvaInputTopJetsVariables_.addEntries(v_mvaInput, mvaWeightsCorrect, mvaWeightsSwapped);

    // Get the indices of the jet pairs and order them by MVA weights, biggest value first
    std::vector<int> jetIndexPairsIndices = initialiseIndices(jetIndexPairs);
    orderIndices(jetIndexPairsIndices, mvaWeightsCorrect);



    // Get jet pair leading in MVA weight, and extract bIndex and antiBIndex
    const std::pair<int, int>& leadingJetIndexPair = jetIndexPairs.at(jetIndexPairsIndices.at(0));
    const int antiBFromTopIndex = leadingJetIndexPair.first;
    const int bFromTopIndex = leadingJetIndexPair.second;

    // Check whether the two jets correspond to the b's from tops, and if the two are correct or swapped
    bool isSwappedPairFromTop(false);
    bool isCorrectPairFromTop(false);
    if(successfulTopMatching){
        h_mvaBasedJetsFromTop_step8->Fill(0.1, weight);
        if(matchedBjetFromTopIndex==bFromTopIndex && matchedAntiBjetFromTopIndex==antiBFromTopIndex){
            isCorrectPairFromTop = true;
            h_mvaBasedJetsFromTop_step8->Fill(1.1, weight);
            h_mvaBasedJetsFromTop_step8->Fill(2.1, weight);
        }
        else if(matchedBjetFromTopIndex==antiBFromTopIndex && matchedAntiBjetFromTopIndex==bFromTopIndex){
            isSwappedPairFromTop = true;
            h_mvaBasedJetsFromTop_step8->Fill(1.1, weight);
            h_mvaBasedJetsFromTop_step8->Fill(3.1, weight);
        }
    }
    else{
        h_mvaBasedJetsFromTop_step8->Fill(-999., weight);
    }
//    std::cout<<"Matching Top: "<<successfulTopMatching<<" , "<<isCorrectPairFromTop<<" , "<<isSwappedPairFromTop<<"\n";

    // Get all jets except the ones assigned to ttbar system, and order them by b-tag discriminator value
    std::vector<int> remainingJetIndices;
    for(const int index : jetIndices){
        if(index==antiBFromTopIndex || index==bFromTopIndex) continue;
        remainingJetIndices.push_back(index);
    }
    orderIndices(remainingJetIndices, *jetBTagCSV_);

    // Get the two jets assigned to Higgs
    const int jet1FromHiggsIndex = remainingJetIndices.at(0);
    const int jet2FromHiggsIndex = remainingJetIndices.at(1);
//    std::cout<<"Btag values: "<<jetBTagCSV_->at(remainingJetIndices.at(0))
//             <<" ,\t"<<jetBTagCSV_->at(remainingJetIndices.at(1))<<"\n\n";


    // Find b jet and anti-b jet corresponding to (anti)b from Higgs
    LV* genBjetFromHiggs(0);
    LV* genAntiBjetFromHiggs(0);
    if(isHiggsSignal_){
        int genBjetIndex(-1);
        int genAntiBjetIndex(-1);
        // FIXME: should one clean the genJetCollection to remove low-pt (or low-eta) jets?
        if(this->getGenBJetIndices(genBjetIndex, genAntiBjetIndex, 25)){
            genBjetFromHiggs = &(allGenJets_->at(genBjetIndex));
            genAntiBjetFromHiggs = &(allGenJets_->at(genAntiBjetIndex));
        }
        else{
            h_matchedBjetsFromHiggs_step8->Fill(0.1, weight);
        }
    }
//    std::cout<<"Gen b jets: "<<genBjetFromHiggs<<" , "<<genAntiBjetFromHiggs<<"\n";

    // Match recoJets to the two selected genJets from Higgs
    int matchedBjetFromHiggsIndex(-1);
    int matchedAntiBjetFromHiggsIndex(-1);
    bool successfulHiggsMatching(false);
    if(higgsDecayMode_==5 && (genBjetFromHiggs && genAntiBjetFromHiggs)){
        successfulHiggsMatching = this->matchRecoToGenJets(matchedBjetFromHiggsIndex, matchedAntiBjetFromHiggsIndex,
                                                           jetIndices,
                                                           genBjetFromHiggs, genAntiBjetFromHiggs);
        if(!successfulHiggsMatching) h_matchedBjetsFromHiggs_step8->Fill(1.1, weight);
        else h_matchedBjetsFromHiggs_step8->Fill(2.1, weight);
    }
//    std::cout<<"Indices: "<<matchedBjetFromHiggsIndex<<" , "<<matchedAntiBjetFromHiggsIndex<<"\n";

    // Check whether the two jets correspond to the b's from Higgs
    bool isPairFromHiggs(false);
    if(successfulHiggsMatching){
        if(matchedBjetFromHiggsIndex==jet1FromHiggsIndex && matchedAntiBjetFromHiggsIndex==jet2FromHiggsIndex){
            isPairFromHiggs = true;
        }
        else if(matchedBjetFromHiggsIndex==jet2FromHiggsIndex && matchedAntiBjetFromHiggsIndex==jet1FromHiggsIndex){
            isPairFromHiggs = true;
        }
    }

    // Check whether the b jets from Higgs are identical to those from (anti)top
    bool ambiguousJetMatchings(false);
    if(!successfulTopMatching || !successfulHiggsMatching) ambiguousJetMatchings = true;
    else if(matchedBjetFromTopIndex==matchedBjetFromHiggsIndex || matchedAntiBjetFromTopIndex==matchedBjetFromHiggsIndex ||
            matchedBjetFromTopIndex==matchedAntiBjetFromHiggsIndex ||matchedAntiBjetFromTopIndex==matchedAntiBjetFromHiggsIndex)
        ambiguousJetMatchings = true;
//    std::cout<<"Matching Higgs: "<<successfulHiggsMatching<<" , "<<isPairFromHiggs<<" ,\tAmbiguity: "<<ambiguousJetMatchings<<"\n";

    if(successfulHiggsMatching){
        h_mvaBasedJetsFromHiggs_step8->Fill(0.1, weight);
        if(isPairFromHiggs){
            h_mvaBasedJetsFromHiggs_step8->Fill(1.1, weight);
            if(ambiguousJetMatchings) h_mvaBasedJetsFromHiggs_step8->Fill(2.1, weight);
            else if(isCorrectPairFromTop || isSwappedPairFromTop) h_mvaBasedJetsFromHiggs_step8->Fill(3.1, weight);
        }
    }
    else{
        h_mvaBasedJetsFromHiggs_step8->Fill(-999., weight);
    }

    for(const auto& jetIndexPair : jetIndexPairs){
        const LV dijet = jets_->at(jetIndexPair.first) + jets_->at(jetIndexPair.second);
        h_dijetMass_step8->Fill(dijet.M(), weight);
        p_dijetMassVsJetCategories->Fill(jetCategoryId_overview, dijet.M(), weight);
        p_dijetMassVsMvaWeightHigh->Fill(mvaWeightsCorrect.at(0), dijet.M(), weight);
        p_dijetMassVsMvaWeightDiff->Fill(mvaWeightsCorrect.at(0)-mvaWeightsCorrect.at(1), dijet.M(), weight);
    }

    const LV dijet = jets_->at(jet1FromHiggsIndex) + jets_->at(jet2FromHiggsIndex);
    h_mvaBasedDijetMass_step8->Fill(dijet.M(), weight);
    p_mvaBasedDijetMassVsJetCategories->Fill(jetCategoryId_overview, dijet.M(), weight);
    p_mvaBasedDijetMassVsMvaWeightHigh->Fill(mvaWeightsCorrect.at(0), dijet.M(), weight);
    p_mvaBasedDijetMassVsMvaWeightDiff->Fill(mvaWeightsCorrect.at(0)-mvaWeightsCorrect.at(1), dijet.M(), weight);

    return kTRUE;
}



HiggsAnalysis::IndexPairs HiggsAnalysis::chargeOrderedJetPairIndices(const std::vector<int>& jetIndices,
                                                                     const std::vector<double>& jetCharges)
{
    IndexPairs result;

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



VLV HiggsAnalysis::recoilForJetPairs(const HiggsAnalysis::IndexPairs& jetIndexPairs,
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


std::vector<MvaInputTopJetsVariables::Input> HiggsAnalysis::fillMvaInputTopJetsVariables(
                                                const int leptonIndex, const int antiLeptonIndex,
                                                const IndexPairs& jetIndexPairs, const VLV& jetRecoils,
                                                const int matchedBjetIndex, const int matchedAntiBjetIndex,
                                                const LV& met,
                                                const bool successfulMatching, const double& eventWeight)const
{
    std::vector<MvaInputTopJetsVariables::Input> result;

    const LV& lepton(leptons_->at(leptonIndex));
    const LV& antiLepton(leptons_->at(antiLeptonIndex));

    // Loop over all jet pairs
    for(size_t iJetIndexPairs = 0; iJetIndexPairs < jetIndexPairs.size(); ++iJetIndexPairs){

        // Get the indices of b and anti-b jet defined by jet charge
        const int antiBIndex = jetIndexPairs.at(iJetIndexPairs).first;
        const int bIndex = jetIndexPairs.at(iJetIndexPairs).second;

        // Check whether the two jets correspond to the b's from tops, and if the two are correct or swapped
        bool isSwappedPair(false);
        bool isCorrectPair(false);
        if(successfulMatching){
            if(matchedBjetIndex==bIndex && matchedAntiBjetIndex==antiBIndex){
                isCorrectPair = true;
            }
            else if(matchedBjetIndex==antiBIndex && matchedAntiBjetIndex==bIndex){
                isSwappedPair = true;
            }
        }

        // Variables for MVA
        const LV& bjet = jets_->at(bIndex);
        const LV& antiBjet = jets_->at(antiBIndex);
        const double& bjetBtagDiscriminator = jetBTagCSV_->at(bIndex);
        const double& antiBjetBtagDiscriminator = jetBTagCSV_->at(antiBIndex);
        const double jetChargeDiff = jetChargeRelativePtWeighted_->at(antiBIndex) - jetChargeRelativePtWeighted_->at(bIndex);
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
                                                       successfulMatching,
                                                       isCorrectPair, isSwappedPair,
                                                       eventWeight);

        result.push_back(mvaInput);
    }

    return result;
}



bool HiggsAnalysis::getGenBJetIndices(int& genBjetIndex, int& genAntiBjetIndex, const int pdgId)
{
    if(!pdgId>0){
        std::cerr<<"ERROR! Method getGenBJetIndices needs a pdgId>0, but used is: "<<pdgId
                 <<"\n...break\n\n";
        exit(71);
    }

    for(size_t iBHadron=0; iBHadron<genBHadFlavour_->size(); ++iBHadron){
        const int flavour = genBHadFlavour_->at(iBHadron);
        if(abs(flavour) != abs(pdgId)) continue;     // Skipping hadrons with the wrong flavour
        // Assigning jet index of corresponding hadron. Set to -2 if >1 hadrons found for the same flavour
        if(flavour>0) genBjetIndex = (genBjetIndex==-1) ? genBHadJetIndex_->at(iBHadron) : -2;
        else if(flavour<0) genAntiBjetIndex = (genAntiBjetIndex==-1) ? genBHadJetIndex_->at(iBHadron) : -2;
    }

    // If no unique match of jets from (anti)b from (anti)top is found, return false
    if(genBjetIndex<0 || genAntiBjetIndex<0){
        return false;
    }
    return true;
}



bool HiggsAnalysis::matchRecoToGenJets(int& matchedBjetIndex, int& matchedAntiBjetIndex,
                                       const std::vector<int>& jetIndices,
                                       const LV* genBjet, const LV* genAntiBjet)
{
    using ROOT::Math::VectorUtil::DeltaR;

    // Find closest jet and its distance in deltaR
    double deltaRBjet(999.);
    double deltaRAntiBjet(999.);
    for(const auto& index : jetIndices){
        float deltaR = DeltaR(*genBjet, jets_->at(index));
        if(deltaR < deltaRBjet){
            deltaRBjet = deltaR;
            matchedBjetIndex = index;
        }
        deltaR = DeltaR(*genAntiBjet, jets_->at(index));
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



void HiggsAnalysis::SetAnalysisMode(const AnalysisMode::AnalysisMode& analysisMode)
{
    analysisMode_ = analysisMode;
}



void HiggsAnalysis::SetJetCategoriesOverview(const JetCategories& jetCategories)
{
    jetCategories_overview_ = &jetCategories;
}



void HiggsAnalysis::SetMvaWeightsCorrect(MvaInputTopJetsVariables& mvaInputTopJetsVariables)
{
    mvaWeightsCorrect_ = &mvaInputTopJetsVariables;
}



void HiggsAnalysis::SetMvaWeightsSwapped(MvaInputTopJetsVariables& mvaInputTopJetsVariables)
{
    mvaWeightsSwapped_ = &mvaInputTopJetsVariables;
}



void HiggsAnalysis::SetJetCategoriesAnalysis(const JetCategories& jetCategories)
{
    jetCategories_ = &jetCategories;
}



bool HiggsAnalysis::failsHiggsGeneratorSelection(Long64_t& entry)
{
    if(!isHiggsSignal_) return false;
    GetHiggsDecayModeEntry(entry);
    // Separate ttH events from inclusve decay into H->bbbar and other decays
    if(isInclusiveHiggs_ && !bbbarDecayFromInclusiveHiggs_ && higgsDecayMode_==5) return true;
    if(isInclusiveHiggs_ && bbbarDecayFromInclusiveHiggs_ && higgsDecayMode_!=5) return true;
    return false;
}


void HiggsAnalysis::SetDijetAnalyzer(DijetAnalyzer* analyzer)
{
    dijetAnalyzer_ = analyzer;
}


bool HiggsAnalysis::failsAdditionalJetFlavourSelection(const Long64_t& entry)const
{
    if(!isTopSignal_) return false;
    if(isHiggsSignal_) return false;

    this->GetTopSignalBranchesEntry(entry);

    int nGenBJets = genBHadIndex_->size();
    if(runWithTtbb_ && nGenBJets<=2) return true;
    if(!runWithTtbb_ && nGenBJets>2) return true;

    return false;
}



void HiggsAnalysis::SetRunWithTtbb(const bool runWithTtbb)
{
    runWithTtbb_ = runWithTtbb;
}







