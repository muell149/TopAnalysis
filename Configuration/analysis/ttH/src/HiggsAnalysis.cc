#define HiggsAnalysis_cxx

#include <TH1.h>

#include "HiggsAnalysis.h"



// Values to be used in analysis
constexpr double JETPTCUT = 30;
constexpr double JETETACUT = 2.4;

// CSV Loose working point
constexpr double BtagWP = 0.244;




HiggsAnalysis::HiggsAnalysis(TTree*){
    
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



HiggsAnalysis::~HiggsAnalysis(){}



void
HiggsAnalysis::Begin(TTree*){
    AnalysisBase::Begin(0);
    
    prepareTriggerSF();
    prepareLeptonIDSF();
    prepareJER_JES();
}



void
HiggsAnalysis::Terminate(){
    AnalysisBase::Terminate();
}



void
HiggsAnalysis::SlaveBegin(TTree *){
    
    // Defaults from AnalysisBase
    AnalysisBase::SlaveBegin(0);
    
    
    // Analysis categories
    const int numberOfCategories(jetCategories_.numberOfCategories());
    
    h_jetCategories_step8 = store(new TH1D("JetCategories_step8","Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));
    
    const std::vector<TString> v_binLabel(jetCategories_.binLabels());
    for(std::vector<TString>::const_iterator i_binLabel = v_binLabel.begin(); i_binLabel != v_binLabel.end(); ++i_binLabel){
        const TString binLabel(*i_binLabel);
        int position = std::distance(v_binLabel.begin(), i_binLabel) +1;
        h_jetCategories_step8->GetXaxis()->SetBinLabel(position, binLabel);
    }
    
    
    // Overview categories
    const int numberOfCategories_overview(jetCategories_overview_.numberOfCategories());
    
    h_jetCategories_overview_step0 = store(new TH1D("JetCategories_overview_step0","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step1 = store(new TH1D("JetCategories_overview_step1","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step2 = store(new TH1D("JetCategories_overview_step2","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step3 = store(new TH1D("JetCategories_overview_step3","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step4 = store(new TH1D("JetCategories_overview_step4","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step5 = store(new TH1D("JetCategories_overview_step5","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step6 = store(new TH1D("JetCategories_overview_step6","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step7 = store(new TH1D("JetCategories_overview_step7","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    h_jetCategories_overview_step8 = store(new TH1D("JetCategories_overview_step8","Jet categories;# jets/b-jets; # events", numberOfCategories_overview, 0, numberOfCategories_overview));
    
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
    h_events_step0a = store(new TH1D("events_step0a","event count (no weight)",8,0,8));
    h_events_step0b = store(new TH1D("events_step0b","event count (no weight)",8,0,8));
    h_events_step1 = store(new TH1D("events_step1","event count (no weight)",8,0,8));
    h_events_step2 = store(new TH1D("events_step2","event count (no weight)",8,0,8));
    h_events_step3 = store(new TH1D("events_step3","event count (no weight)",8,0,8));
    h_events_step4 = store(new TH1D("events_step4","event count at after 2lepton",8,0,8));
    h_events_step5 = store(new TH1D("events_step5","event count at after Zcut",8,0,8));
    h_events_step6 = store(new TH1D("events_step6","event count at after 2jets",8,0,8));
    h_events_step7 = store(new TH1D("events_step7","event count at after MET",8,0,8));
    h_events_step8 = store(new TH1D("events_step8","event count at after 1btag",8,0,8));
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
    
    // FIXME: make event counts dependent on bins (in addition to steps)
    h_events_step9 = store(new TH1D("events_step9","event count for specific bin",8,0,8));
    h_events_step9->Sumw2();
    
    
    // Histograms needed for data-driven scaling of Z samples
    dyScalingHistograms_ = DyScalingHistograms(fOutput);
    dyScalingHistograms_.addStep("4");
    dyScalingHistograms_.addStep("5");
    dyScalingHistograms_.addStep("6");
    dyScalingHistograms_.addStep("7");
    dyScalingHistograms_.addStep("8");
    
    
    // Control plots
    h_jetpT = store(new TH1D ( "jetpT", "jet pT", 40, 0, 400 ));
    h_jetChargeGlobalPtWeighted = store(new TH1D("jetChargeGlobalPtWeighted", "jetChargeGlobalPtWeighted", 110, -1.1, 1.1));
    h_jetChargeRelativePtWeighted = store(new TH1D("jetChargeRelativePtWeighted", "jetChargeRelativePtWeighted", 110, -1.1, 1.1));
    
    
    // Binned control plots
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetpT, false);
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetChargeGlobalPtWeighted, false);
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetChargeRelativePtWeighted, false);
}


void HiggsAnalysis::SlaveTerminate()
{
    AnalysisBase::SlaveTerminate();
}



Bool_t
HiggsAnalysis::Process(Long64_t entry){
    
    if (++EventCounter_ % 100000 == 0) std::cout << "Event Counter: " << EventCounter_ << std::endl;
    
    // Histogram for controlling correctness of h_events_step1, which should be the same for all samples except Zjets and ttbarsignalplustau
    h_events_step0a->Fill(1, 1);
    
    if(isHiggsSignal_)GetHiggsSignalBranchesEntry(entry);
    if(isInclusiveHiggs_ && !bbbarDecayFromInclusiveHiggs_ && higgsDecayMode_==5)return kTRUE;
    if(isInclusiveHiggs_ && bbbarDecayFromInclusiveHiggs_ && higgsDecayMode_!=5)return kTRUE;
    
    //do we have a DY true level cut?
    if (checkZDecayMode_ && !checkZDecayMode_(entry)) return kTRUE;
    
    if (isTtbarPlusTauSample_ || correctMadgraphBR_) GetTopDecayModeEntry(entry);
    //decayMode contains the decay of the top (*10) + the decay of the antitop
    //1=hadron, 2=e, 3=mu, 4=tau->hadron, 5=tau->e, 6=tau->mu
    //i.e. 23 == top decays to e, tbar decays to mu
    if (isTtbarPlusTauSample_) {
        bool isViaTau = topDecayMode_ > 40 || ( topDecayMode_ % 10 > 4 );
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
            case -13*13: isCorrectChannel = topDecayMode_ == 33
                            || topDecayMode_ == 36 || topDecayMode_ == 63
                            || topDecayMode_ == 66; break;
            default: std::cerr << "Invalid channel! Product = " << channelPdgIdProduct_ << "\n";
        };
        bool isBackgroundInSignalSample = !isCorrectChannel || isViaTau;
        if (runViaTau_ != isBackgroundInSignalSample) return kTRUE;
    }
    
    GetRecoBranchesEntry(entry);
    //We must correct for the madGraph branching fraction being 1/9 for dileptons (PDG average is .108)
    if ( correctMadgraphBR_ ) {
        if ( topDecayMode_ == 11 ) { //all hadronic decay
            weightGenerator_ *= (0.676*1.5) * (0.676*1.5);
        } else if ( topDecayMode_< 20 || ( topDecayMode_ % 10 == 1) ) { //semileptonic Decay
            weightGenerator_ *= (0.108*9) * (0.676*1.5);
        } else {//dileptonic decay (including taus!)
            weightGenerator_ *= (0.108*9) * (0.108*9);
        }
    }
    
    
    
    
    
    
    // FIXME: here were PDF variations, not needed now, and perhaps never
    
    
    // FIXME: corrections to jet energy resolution/scale, also here ?
    //if(doJesJer)applyJER_JES();
    
    
    // apply all jet cuts
    cleanJetCollection(JETPTCUT, JETETACUT);
    
    
    double weightPU = 1;
    if (isMC_ && pureweighter_)weightPU = pureweighter_->getPUweight(vertMultiTrue_);
    
    
    // FIXME: something was done about matching of BHadron to jets for ttbar sample, not needed now
    
    
    
    std::vector<int> v_bJetIndex;
    for ( std::vector<double>::iterator it = jetBTagCSV_->begin(); it<jetBTagCSV_->end(); it++ ) {
        if ( *it > BtagWP) {
            v_bJetIndex.push_back((it-jetBTagCSV_->begin())); //change asked by Tyler
        }
    }
    const int numberOfBJets = v_bJetIndex.size();
    
    // FIXME: here was dealt with ttbar generator information, not needed now
    
    
    
    //===CUT===
    // this is step0, so no cut application
    
    h_events_step0b->Fill(1, 1);
    
    // ++++ Control Plots ++++
    
    h_jetCategories_overview_step0->Fill(jetCategories_overview_.categoryId(jets_->size(),numberOfBJets), 1);
    
    // is this histo needed for anything ?
    //h_PUSF->Fill(weightPU, 1);
    
    
    
    //===CUT===
    // check if event was triggered
    //our triggers (bits: see the ntuplewriter!)
    constexpr int mumuTriggers = 0x8 + 0x20; //17/8 + 17Tr8
    constexpr int emuTriggers = 0x2000 + 0x4000;
    constexpr int eeTriggers = 0x40000;
    
    if (!(((triggerBits_ & mumuTriggers) && channelPdgIdProduct_ == -13*13)    //mumu triggers in rightmost byte
          ||((triggerBits_ & emuTriggers) && channelPdgIdProduct_ == -11*13)     //emu in 2nd byte
          ||((triggerBits_ & eeTriggers) && channelPdgIdProduct_ == -11*11)))    //ee in 3rd byte
    {
        return kTRUE;
    }
    
    size_t LeadLeptonNumber = 0;
    size_t NLeadLeptonNumber = 0;
    bool hasLeptonPair = getLeptonPair(LeadLeptonNumber, NLeadLeptonNumber);
    
    h_events_step1->Fill(1, 1);
    
    // ++++ Control Plots ++++
    
    h_jetCategories_overview_step1->Fill(jetCategories_overview_.categoryId(jets_->size(),numberOfBJets), 1);
    
    
    
    //===CUT===
    // we need an OS lepton pair
    if (! hasLeptonPair) return kTRUE;
    // lepton pt cut > 20, sufficient to test the second leading lepton
    if (leptons_->at(NLeadLeptonNumber).pt() <= 20) return kTRUE;
    
    LV dilepton = leptons_->at(LeadLeptonNumber) + leptons_->at(NLeadLeptonNumber);
    
    h_events_step2->Fill(1, 1);
    
    // ++++ Control Plots ++++
    
    h_jetCategories_overview_step2->Fill(jetCategories_overview_.categoryId(jets_->size(),numberOfBJets), 1);
    
    
    
    //===CUT===
    //with at least 20 GeV invariant mass
    if (dilepton.M() < 20) return kTRUE;
    
    // find l+ and l-
    LV leptonPlus;
    LV leptonMinus;
    if (lepPdgId_->at(LeadLeptonNumber) < 0) {
        leptonPlus = leptons_->at(LeadLeptonNumber);
        leptonMinus = leptons_->at(NLeadLeptonNumber);
    } else {
        leptonMinus = leptons_->at(LeadLeptonNumber);
        leptonPlus = leptons_->at(NLeadLeptonNumber);
    }

    //This is necessary due to the ordering in the trigger 2D-plots
    LV leptonX, leptonY;
    if ( abs( lepPdgId_->at(LeadLeptonNumber) ) == abs( lepPdgId_->at(NLeadLeptonNumber) ) ){
        //in ee and mumu channel leptonX must be the highest pT lepton
        leptonX = leptons_->at(LeadLeptonNumber);
        leptonY = leptons_->at(NLeadLeptonNumber);
    } else {
        // in emu channel lepX should be electron
        if (abs(lepPdgId_->at(LeadLeptonNumber)) == 11) {
            leptonX = leptons_->at(LeadLeptonNumber);
            leptonY = leptons_->at(NLeadLeptonNumber);
        } else {
            leptonX = leptons_->at(NLeadLeptonNumber);
            leptonY = leptons_->at(LeadLeptonNumber);
        }
    }
    
    int LleptonId = lepPdgId_->at(LeadLeptonNumber);
    int NLleptonId = lepPdgId_->at(NLeadLeptonNumber);
    //Now determine the lepton trigger and ID scale factors
    double weightLepSF = isMC_ ? getLeptonIDSF(leptons_->at(LeadLeptonNumber), leptons_->at(NLeadLeptonNumber), LleptonId, NLleptonId) : 1;  
    double weightTrigSF = isMC_ ? getTriggerSF(leptonX, leptonY) : 1;
    
    //First control plots after dilepton selection (without Z cut)
    double weight = weightGenerator_*weightTrigSF*weightLepSF;
    
    //weight even without PU reweighting --- FIXME: commented plot probably interesting
    //h_vertMulti_noPU->Fill(vertMulti, weight);
    
    //apply PU reweighting - continue with control plots --- FIXME: commented plot probably interesting
    weight *= weightPU;
    //h_vertMulti->Fill(vertMulti, weight);
    
    h_events_step3->Fill(1, weight);
    
    // ****************************************
    //handle inverted Z cut
    // Fill loose dilepton mass histogram before any jet cuts
    bool isZregion = dilepton.M() > 76 && dilepton.M() < 106;
    // FIXME: define jet pt cut and select with following line
    //bool hasJets = jets_->size() > 1 && jets->at(1).Pt() > JETPTCUT;
    bool hasJets = jets_->size() > 1;
    bool hasMetOrEmu = channel_ == "emu" || met_->Pt() > 40;
    bool hasBtag = v_bJetIndex.size() > 0;
    //bool hasSolution = HypTop->size() > 0;
    bool hasSolution = calculateKinReco(leptonMinus, leptonPlus);
    
    // Z window plots need to be filled here, in order to rescale the contribution to data
    if ( isZregion ) {
        double fullWeights = weightGenerator_*weightPU*weightTrigSF*weightLepSF;
        dyScalingHistograms_.fillZWindow(dilepton.M(), fullWeights, "4");
        
        if ( hasJets ) {
            dyScalingHistograms_.fillLoose(dilepton.M(), fullWeights);
            dyScalingHistograms_.fillZWindow(dilepton.M(), fullWeights, "5");
            
            if ( hasMetOrEmu ) {
                dyScalingHistograms_.fillZWindow(dilepton.M(), fullWeights, "6");
                
                if ( hasBtag ) {
                    // FIXME: do not use b-tag scale factor
                    //weightBtagSF = isMC ? calculateBtagSF() : 1;
                    //fullWeights *= weightBtagSF;
                    dyScalingHistograms_.fillZWindow(dilepton.M(), fullWeights, "7");
                    
                    if ( hasSolution ) {
                        // FIXME: weightKinFit is just a constant, but is it valid for each event selection (jetCategories) and can be used here?
                        //fullWeights *= weightKinFit;
                        dyScalingHistograms_.fillZWindow(dilepton.M(), fullWeights, "8");
                    }
                }
            }
        }
    }
    
    // ++++ Control Plots ++++
    
    h_jetCategories_overview_step3->Fill(jetCategories_overview_.categoryId(jets_->size(),numberOfBJets), weight);
    
    
    
    //=== CUT ===
    //Exclude the Z window
    if (channel_!="emu" && isZregion) return kTRUE;
    
    h_events_step4->Fill(1, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "4");
    }
    
    // ++++ Control Plots ++++
    
    h_jetCategories_overview_step4->Fill(jetCategories_overview_.categoryId(jets_->size(),numberOfBJets), weight);
    
    
    
    //=== CUT ===
    //Require at least two jets > 30 GeV (check for > 30 needed because we might have 20 GeV jets in our NTuple)
    if (! hasJets) return kTRUE;
    
    h_events_step5->Fill(1, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "5");
    }
    
    // ++++ Control Plots ++++
    
    h_jetCategories_overview_step5->Fill(jetCategories_overview_.categoryId(jets_->size(),numberOfBJets), weight);
    
    
    
    //=== CUT ===
    //Require MET > 40 GeV in non-emu channels
    if (!hasMetOrEmu) return kTRUE;
    
    h_events_step6->Fill(1, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "6");
    }
    
    // ++++ Control Plots ++++
    
    h_jetCategories_overview_step6->Fill(jetCategories_overview_.categoryId(jets_->size(),numberOfBJets), weight);
    
    
    
    //=== CUT ===
    //Require at least one b tagged jet
    if (!hasBtag) return kTRUE;
    
    // FIXME: if b-tagging scale factor is desired, calculate it here ?
    // weight *= weightBtagSF;
    
    h_events_step7->Fill(1, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "7");
    }
    
    // ++++ Control Plots ++++
    
    h_jetCategories_overview_step7->Fill(jetCategories_overview_.categoryId(jets_->size(),numberOfBJets), weight);
    
    
    
    //=== CUT ===
    //Require at least one solution for the kinematic event reconstruction
    if (!hasSolution) return kTRUE;
    // FIXME: weightKinFit is just a constant, but is it valid for each event selection (jetCategories) and can be used here?
    //weight *= weightKinFit;
    
    h_events_step8->Fill(1, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        dyScalingHistograms_.fillZVeto(dilepton.M(), weight, "8");
    }
    
    // ++++ Control Plots ++++
    
    if(jetCategories_.categoryId(jets_->size(),numberOfBJets) == 10)h_events_step9->Fill(1, weight);
        
    h_jetCategories_step8->Fill(jetCategories_.categoryId(jets_->size(),numberOfBJets), weight);
    h_jetCategories_overview_step8->Fill(jetCategories_overview_.categoryId(jets_->size(),numberOfBJets), weight);
    for(unsigned int iJet = 0; iJet < jets_->size(); ++iJet){
        FillBinnedControlPlot(h_jetCategories_step8, jetCategories_.categoryId(jets_->size(),numberOfBJets), h_jetpT, jets_->at(iJet).Pt(), weight);
    }
    
    
    for(auto jetChargeGlobalPtWeighted : *jetChargeGlobalPtWeighted_){
        h_jetChargeGlobalPtWeighted->Fill(jetChargeGlobalPtWeighted, weight);
        FillBinnedControlPlot(h_jetCategories_step8, jetCategories_.categoryId(jets_->size(),numberOfBJets), h_jetChargeGlobalPtWeighted, jetChargeGlobalPtWeighted, weight);
    }
    
    for(auto jetChargeRelativePtWeighted : *jetChargeRelativePtWeighted_){
        h_jetChargeRelativePtWeighted->Fill(jetChargeRelativePtWeighted, weight);
        FillBinnedControlPlot(h_jetCategories_step8, jetCategories_.categoryId(jets_->size(),numberOfBJets), h_jetChargeRelativePtWeighted, jetChargeRelativePtWeighted, weight);
    }
    
    
    
    
    
    
    
    
    return kTRUE;
}



void HiggsAnalysis::SetSamplename(TString samplename, TString)
{
    samplename_ = samplename;
    isTtbarPlusTauSample_ = samplename.BeginsWith("ttbar") && !samplename.BeginsWith("ttbarhiggs") && !(samplename=="ttbarw") && !(samplename=="ttbarz") && !samplename.Contains("bg");
    // FIXME: for ttbarW, also correction for 3rd W needs to be applied, for ttbarhiggs corrections for 2 or 4 Ws needed, depending on Higgs decay (H->WW?)
    // FIXME: and what about Wlnu sample ?
    correctMadgraphBR_ = samplename.BeginsWith("ttbar") && !samplename.BeginsWith("ttbarhiggs");
}



void HiggsAnalysis::SetHiggsInclusiveSample(const bool isInclusiveHiggs){
    isInclusiveHiggs_ = isInclusiveHiggs;
}



void HiggsAnalysis::SetHiggsInclusiveSeparation(const bool bbbarDecayFromInclusiveHiggs){
    bbbarDecayFromInclusiveHiggs_ = bbbarDecayFromInclusiveHiggs;
}
