#define HiggsAnalysis_cxx

#include <iostream>
#include <cmath>
#include <cstdlib>

#include <TH1.h>
#include <TTree.h>
#include <TString.h>
#include <TFile.h>
#include <TSystem.h>
#include <Math/VectorUtil.h>

#include "HiggsAnalysis.h"
#include "higgsUtils.h"
#include "../../diLeptonic/src/analysisUtils.h"
#include "../../diLeptonic/src/classes.h"





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
constexpr double BtagWP = 0.244;


/// Folder for storage of MVA input TTree
constexpr const char* MvaInputDIR = "mvaInput";










HiggsAnalysis::HiggsAnalysis(TTree*)
{
    // Define categories for analysis
    jetCategories_.clear();
    jetCategories_.addCategory(2,0);
    jetCategories_.addCategory(2,1);
    jetCategories_.addCategory(2,2);
    jetCategories_.addCategory(3,0);
    jetCategories_.addCategory(3,1);
    jetCategories_.addCategory(3,2);
    jetCategories_.addCategory(3,3);
    jetCategories_.addCategory(4,0,true);
    jetCategories_.addCategory(4,1,true);
    jetCategories_.addCategory(4,2,true);
    jetCategories_.addCategory(4,3,true,true);
    std::cout<<"\nNumber of analysis categories: "<<jetCategories_.numberOfCategories()<<"\n";

    // Define categories for overview
    jetCategories_overview_.clear();
    jetCategories_overview_.addCategory(2,0);
    jetCategories_overview_.addCategory(2,1);
    jetCategories_overview_.addCategory(2,2);
    jetCategories_overview_.addCategory(3,0);
    jetCategories_overview_.addCategory(3,1);
    jetCategories_overview_.addCategory(3,2);
    jetCategories_overview_.addCategory(3,3);
    jetCategories_overview_.addCategory(4,0);
    jetCategories_overview_.addCategory(4,1);
    jetCategories_overview_.addCategory(4,2);
    jetCategories_overview_.addCategory(4,3);
    jetCategories_overview_.addCategory(4,4);
    jetCategories_overview_.addCategory(5,0,true);
    jetCategories_overview_.addCategory(5,1,true);
    jetCategories_overview_.addCategory(5,2,true);
    jetCategories_overview_.addCategory(5,3,true);
    jetCategories_overview_.addCategory(5,4,true);
    jetCategories_overview_.addCategory(5,5,true,true);
    std::cout<<"Number of overview categories: "<<jetCategories_overview_.numberOfCategories()<<"\n\n";
}



HiggsAnalysis::~HiggsAnalysis()
{}



void HiggsAnalysis::Begin(TTree*)
{
    // Defaults from AnalysisBase
    AnalysisBase::Begin(0);

    // Prepare things for analysis
    this->prepareTriggerSF();
    this->prepareLeptonIDSF();
    this->prepareJER_JES();
    this->prepareBtagSF();
}




void HiggsAnalysis::Terminate()
{
    // Produce b-tag efficiencies
    if(isTtbarSample_ && isTopSignal_) produceBtagEfficiencies();
    
    // Do everything needed for MVA
    if(analysisMode_ == AnalysisMode::mva){

        // Create output directory for MVA input tree, and produce and write tree
        std::string f_savename = this->assignFolder(MvaInputDIR, channel_, systematic_);
        f_savename.append(outputfilename_);
        mvaInputTopJetsVariables_.produceMvaInputTree(f_savename);
        //mvaInputTopJetsVariables_.produceMvaInputTree(fOutput);

        // Create and store control plots in fOutput
        mvaInputTopJetsVariables_.mvaInputVariablesControlPlots(fOutput);
    }

    // Cleanup
    mvaInputTopJetsVariables_.clear();

    // Defaults from AnalysisBase
    AnalysisBase::Terminate();
}



void HiggsAnalysis::SlaveBegin(TTree *)
{
    // Defaults from AnalysisBase
    AnalysisBase::SlaveBegin(0);


    // Analysis categories
    const int numberOfCategories(jetCategories_.numberOfCategories());

    h_jetCategories_step8 = store(new TH1D("jetCategories_step8","Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));

    const std::vector<TString> v_binLabel(jetCategories_.binLabels());
    for(std::vector<TString>::const_iterator i_binLabel = v_binLabel.begin(); i_binLabel != v_binLabel.end(); ++i_binLabel){
        const TString binLabel(*i_binLabel);
        int position = std::distance(v_binLabel.begin(), i_binLabel) +1;
        h_jetCategories_step8->GetXaxis()->SetBinLabel(position, binLabel);
    }


    // Overview categories
    const int numberOfCategories_overview(jetCategories_overview_.numberOfCategories());

    h_jetCategories_overview_step0 = store(new TH1D("jetCategories_overview_step0","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step1 = store(new TH1D("jetCategories_overview_step1","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step2 = store(new TH1D("jetCategories_overview_step2","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step3 = store(new TH1D("jetCategories_overview_step3","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step4 = store(new TH1D("jetCategories_overview_step4","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step5 = store(new TH1D("jetCategories_overview_step5","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step6 = store(new TH1D("jetCategories_overview_step6","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step7 = store(new TH1D("jetCategories_overview_step7","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step8 = store(new TH1D("jetCategories_overview_step8","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));

    const std::vector<TString> v_binLabel_overview(jetCategories_overview_.binLabels());
    for(std::vector<TString>::const_iterator i_binLabel = v_binLabel_overview.begin(); i_binLabel != v_binLabel_overview.end(); ++i_binLabel){
        const TString binLabel(*i_binLabel);
        int position = std::distance(v_binLabel_overview.begin(), i_binLabel) +1;
        h_jetCategories_overview_step0->GetXaxis()->SetBinLabel(position, binLabel);
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

    // Binned control plots
    CreateBinnedControlPlots(h_jetCategories_step8, h_events_step8, false);
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetPt_step8, false);
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetChargeGlobalPtWeighted_step8, false);
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetChargeRelativePtWeighted_step8, false);
    
    // Histograms for b-tagging efficiencies
    this->bookBtagHistograms();
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
    if(failsDrellYanGeneratorSelection(entry)) return kTRUE;
    
    // Separate dileptonic ttbar decays via tau
    if(failsTopGeneratorSelection(entry)) return kTRUE;
    
    // Separate inclusive ttH sample in decays H->bbbar and others
    if(failsHiggsGeneratorSelection(entry)) return kTRUE;
    
    // Correct for the MadGraph branching fraction being 1/9 for dileptons (PDG average is .108)
    const double weightMadgraphCorrection = madgraphWDecayCorrection(entry);

    // Get weight due to pileup reweighting
    const double weightPU = this->weightPileup(entry);

    // Access weightGenerator_ and modify it
    if(isMC_){
        GetWeightGeneratorEntry(entry);
        weightGenerator_ *= weightMadgraphCorrection;
    }
    else{
        // Since weights are also filled for data, this value needs to be set
        weightGenerator_ = 1.;
    }
    
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
    selectIndices(leptonIndices, *lepPdgId_, 0, false);
    selectIndices(antiLeptonIndices, *lepPdgId_, 0);
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
    
    // Get b-jet indices, apply selection cuts and order them by btag discriminator (beginning with the highest value)
    std::vector<int> bjetIndices = jetIndices;
    selectIndices(bjetIndices, *jetBTagCSV_, BtagWP);
    orderIndices(bjetIndices, *jetBTagCSV_);
    
    // Apply b-tag efficiency MC correction using random number based tag flipping
    if (isMC_ && !makeeffs){
        //If b-tag efficiencies do not exit ==> do not re-tag the jets' b-tag value
        bjetIndices.clear();
        bjetIndices = indexOfBtags(jetIndices, BtagWP);
        orderIndices(bjetIndices, *jetBTagCSV_);
    }
    const int numberOfBjets = bjetIndices.size();
    
    // Get MET
    const LV& met(*met_);
    
    BasicHistograms::Input basicHistogramsInput(leptonIndices, antiLeptonIndices,
                                                jetIndices, bjetIndices,
                                                *leptons_, *jets_, met,
                                                *jetBTagCSV_);
    
    
    // ++++ Control Plots ++++
    
    h_events_step1->Fill(1, 1);
    basicHistograms_.fill(basicHistogramsInput, 1, "1");
    h_jetCategories_overview_step1->Fill(jetCategories_overview_.categoryId(numberOfJets,numberOfBjets), 1);
    
    
    
    //===CUT===
    // we need an OS lepton pair
    if (!hasLeptonPair) return kTRUE;
    
    // ++++ Control Plots ++++
    
    h_events_step2->Fill(1, 1);
    basicHistograms_.fill(basicHistogramsInput, 1, "2");
    h_jetCategories_overview_step2->Fill(jetCategories_overview_.categoryId(numberOfJets,numberOfBjets), 1);



    //===CUT===
    // with at least 20 GeV invariant mass
    if (dilepton.M() < 20.) return kTRUE;

    // Now determine the lepton trigger and ID scale factors
    double weightLepSF = isMC_ ? getLeptonIDSF(leadingLeptonIndex, nLeadingLeptonIndex) : 1.;
    double weightTrigSF = isMC_ ? getTriggerSF(leptonXIndex, leptonYIndex) : 1.;
    
    // First control plots after dilepton selection (without Z cut)
    double weight = weightGenerator_*weightTrigSF*weightLepSF;

    //apply PU reweighting
    weight *= weightPU;
    
    // ++++ Control Plots ++++
    
    h_events_step3->Fill(1, weight);
    basicHistograms_.fill(basicHistogramsInput, weight, "3");
    h_jetCategories_overview_step3->Fill(jetCategories_overview_.categoryId(numberOfJets,numberOfBjets), weight);
    
    
    
    // ****************************************
    //handle inverted Z cut
    // Fill loose dilepton mass histogram before any jet cuts
    bool isZregion = dilepton.M() > 76 && dilepton.M() < 106;
    // FIXME: define jet pt cut and select with following line
    //bool hasJets = numberOfJets > 1 && jets->at(1).Pt() > JETPTCUT;
    bool hasJets = numberOfJets > 1;
    bool hasMetOrEmu = channel_ == "emu" || met.Pt() > 40;
    bool hasBtag = numberOfBjets > 0;
    bool hasSolution = calculateKinReco(leptonIndex, antiLeptonIndex, jetIndices, met);
    
    // Z window plots need to be filled here, in order to rescale the contribution to data
    if(isZregion){
        double fullWeights = weightGenerator_*weightPU*weightTrigSF*weightLepSF;
        dyScalingHistograms_.fillZWindow(dilepton.M(), fullWeights, "4");

        if(hasJets){
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
    h_jetCategories_overview_step4->Fill(jetCategories_overview_.categoryId(numberOfJets,numberOfBjets), weight);
    
    
    
    //=== CUT ===
    //Require at least two jets > 30 GeV (check for > 30 needed because we might have 20 GeV jets in our NTuple)
    if(!hasJets) return kTRUE;
    
    // ++++ Control Plots ++++
    
    if(!isZregion){ //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "5");
    }
    h_events_step5->Fill(1, weight);
    basicHistograms_.fill(basicHistogramsInput, weight, "5");
    h_jetCategories_overview_step5->Fill(jetCategories_overview_.categoryId(numberOfJets,numberOfBjets), weight);
    
    
    
    //=== CUT ===
    //Require MET > 40 GeV in non-emu channels
    if(!hasMetOrEmu) return kTRUE;

    // ++++ Control Plots ++++
    
    if(!isZregion){ //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "6");
    }
    h_events_step6->Fill(1, weight);
    basicHistograms_.fill(basicHistogramsInput, weight, "6");
    h_jetCategories_overview_step6->Fill(jetCategories_overview_.categoryId(numberOfJets,numberOfBjets), weight);
    
    // Fill the b-tagging efficiency plots
    if(isTtbarSample_ && isTopSignal_ && makeeffs){
        this->fillBtagHistograms(jetIndices, bjetIndices, weight);
    }
    
    
    
    //=== CUT ===
    //Require at least one b tagged jet
    if(!hasBtag) return kTRUE;

    // FIXME: if b-tagging scale factor is desired, calculate it here ?
    // weight *= weightBtagSF;

    

    // ++++ Control Plots ++++

    if(!isZregion){ //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "7");
    }
    h_events_step7->Fill(1, weight);
    basicHistograms_.fill(basicHistogramsInput, weight, "7");
    h_jetCategories_overview_step7->Fill(jetCategories_overview_.categoryId(numberOfJets,numberOfBjets), weight);
    
    
    
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
    FillBinnedControlPlot(h_jetCategories_step8, jetCategories_.categoryId(numberOfJets,numberOfBjets), h_events_step8, 1, weight);

    h_jetCategories_step8->Fill(jetCategories_.categoryId(numberOfJets,numberOfBjets), weight);
    h_jetCategories_overview_step8->Fill(jetCategories_overview_.categoryId(numberOfJets,numberOfBjets), weight);
    
    // Fill jet quantities
    for(const auto& index : jetIndices){
        h_jetPt_step8->Fill(jets_->at(index).Pt(), weight);
        h_jetChargeGlobalPtWeighted_step8->Fill(jetChargeGlobalPtWeighted_->at(index), weight);
        h_jetChargeRelativePtWeighted_step8->Fill(jetChargeRelativePtWeighted_->at(index), weight);
        FillBinnedControlPlot(h_jetCategories_step8, jetCategories_.categoryId(numberOfJets,numberOfBjets), h_jetPt_step8, jets_->at(index).Pt(), weight);
        FillBinnedControlPlot(h_jetCategories_step8, jetCategories_.categoryId(numberOfJets,numberOfBjets), h_jetChargeGlobalPtWeighted_step8, jetChargeGlobalPtWeighted_->at(index), weight);
        FillBinnedControlPlot(h_jetCategories_step8, jetCategories_.categoryId(numberOfJets,numberOfBjets), h_jetChargeRelativePtWeighted_step8, jetChargeRelativePtWeighted_->at(index), weight);
    }
    
    
    
    if(analysisMode_ != AnalysisMode::mva)return kTRUE;



    // FIXME: which events exactly to fill? For now all with at least 4 jets
    if(numberOfJets<4)return kTRUE;
    
    
    // Find b jet and anti-b jet corresponding to (anti)b from (anti)top
    LV* genBjet(0);
    LV* genAntiBjet(0);
    if(isTopSignal_){
        this->GetTopSignalBranchesEntry(entry);
        int genBjetIndex(-1);
        int genAntiBjetIndex(-1);
        // FIXME: should one clean the genJetCollection to remove low-pt (or low-eta) jets?
        if(this->getGenBJetIndices(genBjetIndex, genAntiBjetIndex, 6)){
            genBjet = &(allGenJets_->at(genBjetIndex));
            genAntiBjet = &(allGenJets_->at(genAntiBjetIndex));
        }
        else{
            h_matchedBjetsFromTop_step8->Fill(0.1, weight);
        }
    }

    // Match recoJets to the two selected genJets
    int matchedBjetIndex(-1);
    int matchedAntiBjetIndex(-1);
    bool successfulMatching(false);
    if(genBjet && genAntiBjet){
        successfulMatching = this->matchRecoToGenJets(matchedBjetIndex, matchedAntiBjetIndex, jetIndices, genBjet, genAntiBjet);
        if(!successfulMatching)h_matchedBjetsFromTop_step8->Fill(1.1, weight);
        else h_matchedBjetsFromTop_step8->Fill(2.1, weight);
    }

    // Loop over all jet combinations and fill the MVA TTree
    this->fillMvaInputTopJetsVariables(leptonIndex, antiLeptonIndex,
                                       jetIndices,
                                       matchedBjetIndex, matchedAntiBjetIndex,
                                       met,
                                       successfulMatching, weight);

    return kTRUE;
}



void HiggsAnalysis::fillMvaInputTopJetsVariables(const int leptonIndex, const int antiLeptonIndex,
                                                 const std::vector<int>& jetIndices,
                                                 const int matchedBjetIndex, const int matchedAntiBjetIndex,
                                                 const LV& met,
                                                 const bool successfulMatching, const double& eventWeight)
{
    const LV& lepton(leptons_->at(leptonIndex));
    const LV& antiLepton(leptons_->at(antiLeptonIndex));
    
    // Loop over all jet combinations
    for(std::vector<int>::const_iterator i_jetIndex = jetIndices.begin(); i_jetIndex != --(jetIndices.end()); ++i_jetIndex){
        std::vector<int>::const_iterator incrementIterator(i_jetIndex);
        ++incrementIterator;
        for(std::vector<int>::const_iterator j_jetIndex = incrementIterator; j_jetIndex != jetIndices.end(); ++j_jetIndex){
            
            // Get the indices of b and anti-b jet defined by jet charge
            int bIndex = *i_jetIndex;
            int antiBIndex = *j_jetIndex;
            ttbar::orderIndices(antiBIndex, bIndex, *jetChargeRelativePtWeighted_);
            const double jetChargeDiff = jetChargeRelativePtWeighted_->at(antiBIndex) - jetChargeRelativePtWeighted_->at(bIndex);
            if(jetChargeDiff<0. || jetChargeDiff>2.){
                std::cerr<<"ERROR! Difference in jet charge is (value = "<<jetChargeDiff
                         <<"), but definition allows only values in [0,2]\n...break\n"<<std::endl;
                exit(555);
            }
            
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
            VLV recoilJets;
            for(const int index : jetIndices){
                if(index == bIndex || index == antiBIndex) continue;
                recoilJets.push_back(jets_->at(index));
            }
            LV jetRecoil;
            for(auto recoilJet : recoilJets)jetRecoil += recoilJet;
            const double& bjetBtagDiscriminator = jetBTagCSV_->at(bIndex);
            const double& antiBjetBtagDiscriminator = jetBTagCSV_->at(antiBIndex);

            // Add entry to MVA input
            mvaInputTopJetsVariables_.addEntry(lepton, antiLepton,
                                               bjet, antiBjet,
                                               bjetBtagDiscriminator, antiBjetBtagDiscriminator,
                                               jetChargeDiff,
                                               jetRecoil, met,
                                               successfulMatching, isCorrectPair, isSwappedPair,
                                               eventWeight);
        }
    }
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



bool HiggsAnalysis::failsHiggsGeneratorSelection(Long64_t& entry)
{
    if(!isHiggsSignal_) return false;
    GetHiggsDecayModeEntry(entry);
    // Separate ttH events from inclusve decay into H->bbbar and other decays
    if(isInclusiveHiggs_ && !bbbarDecayFromInclusiveHiggs_ && higgsDecayMode_==5) return true;
    if(isInclusiveHiggs_ && bbbarDecayFromInclusiveHiggs_ && higgsDecayMode_!=5) return true;
    return false;
}









