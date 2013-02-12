#define HiggsAnalysis_cxx

#include "HiggsAnalysis.h"



// FIXME: are these values taken from Analysis.C? and can they been overwritten here?
//constexpr double JETPTCUT = 30;
//constexpr double JETETACUT = 2.4;



HiggsAnalysis::HiggsAnalysis(TTree*)
{
}



HiggsAnalysis::~HiggsAnalysis(){}




void
HiggsAnalysis::SlaveBegin(TTree *){
    
    // FIXME: shouldn't the jetCategories_ declaration be in the constructor?
    jetCategories_.clear();
    jetCategories_.addCategory(2,0);
    jetCategories_.addCategory(2,1);
    jetCategories_.addCategory(2,2);
    jetCategories_.addCategory(3,0);
    jetCategories_.addCategory(3,1);
    jetCategories_.addCategory(3,2);
    jetCategories_.addCategory(3,3);
    jetCategories_.addCategory(4,0);
    jetCategories_.addCategory(4,1);
    jetCategories_.addCategory(4,2);
    jetCategories_.addCategory(4,3);
    jetCategories_.addCategory(4,4);
    jetCategories_.addCategory(5,0,true);
    jetCategories_.addCategory(5,1,true);
    jetCategories_.addCategory(5,2,true);
    jetCategories_.addCategory(5,3,true);
    jetCategories_.addCategory(5,4,true);
    jetCategories_.addCategory(5,5,true,true);
    const int numberOfCategories(jetCategories_.numberOfCategories());
    //std::cout<<"\n\tNumber of categories: "<<numberOfCategories<<"\n\n";
    
    h_jetCategories_step0 = Analysis::store(new TH1D("JetCategories_step0","Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));
    h_jetCategories_step1 = store(new TH1D("JetCategories_step1","Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));
    h_jetCategories_step2 = store(new TH1D("JetCategories_step2","Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));
    h_jetCategories_step3 = store(new TH1D("JetCategories_step3","Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));
    h_jetCategories_step4 = store(new TH1D("JetCategories_step4","Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));
    h_jetCategories_step5 = store(new TH1D("JetCategories_step5","Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));
    h_jetCategories_step6 = store(new TH1D("JetCategories_step6","Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));
    h_jetCategories_step7 = store(new TH1D("JetCategories_step7","Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));
    h_jetCategories_step8 = store(new TH1D("JetCategories_step8","Jet categories;# jets/b-jets; # events", numberOfCategories, 0, numberOfCategories));
    
    const std::vector<TString> v_binLabel(jetCategories_.binLabels());
    for(std::vector<TString>::const_iterator i_binLabel = v_binLabel.begin(); i_binLabel != v_binLabel.end(); ++i_binLabel){
        const TString binLabel(*i_binLabel);
	int position = std::distance(v_binLabel.begin(), i_binLabel) +1;
	h_jetCategories_step0->GetXaxis()->SetBinLabel(position, binLabel);
	h_jetCategories_step1->GetXaxis()->SetBinLabel(position, binLabel);
	h_jetCategories_step2->GetXaxis()->SetBinLabel(position, binLabel);
	h_jetCategories_step3->GetXaxis()->SetBinLabel(position, binLabel);
	h_jetCategories_step4->GetXaxis()->SetBinLabel(position, binLabel);
	h_jetCategories_step5->GetXaxis()->SetBinLabel(position, binLabel);
	h_jetCategories_step6->GetXaxis()->SetBinLabel(position, binLabel);
	h_jetCategories_step7->GetXaxis()->SetBinLabel(position, binLabel);
	h_jetCategories_step8->GetXaxis()->SetBinLabel(position, binLabel);
	//std::cout<<"Bin, label: "<<position<<" , "<<binLabel<<"\n";
    }
    
    
    // Histograms needed for cutflow tables
    // FIXME: why not using histogram with single bin ???
    h_step0 = store(new TH1D("step0","event count (no weight)",10,0,10));
    h_step1 = store(new TH1D("step1","event count (no weight)",10,0,10));
    h_step2 = store(new TH1D("step2","event count (no weight)",10,0,10));
    h_step3 = store(new TH1D("step3","event count (no weight)",10,0,10));
    h_step4 = store(new TH1D("step4","event count at after 2lepton",10,0,10));
    h_step5 = store(new TH1D("step5","event count at after Zcut",10,0,10));
    h_step6 = store(new TH1D("step6","event count at after 2jets",10,0,10));
    h_step7 = store(new TH1D("step7","event count at after MET",10,0,10));
    h_step8 = store(new TH1D("step8","event count at after 1btag",10,0,10));
    h_step9 = store(new TH1D("step9","event count at step after KinReco",10,0,10));
    h_step0->Sumw2();
    h_step1->Sumw2();
    h_step2->Sumw2();
    h_step3->Sumw2();
    h_step4->Sumw2();
    h_step5->Sumw2();
    h_step6->Sumw2();
    h_step7->Sumw2();
    h_step8->Sumw2();
    h_step9->Sumw2();
    
    
    // Histograms needed for data-driven scaling of Z samples
    Allh1_postZcut = store(new TH1D("Allh1_postZcut","DiLepton Mass",40,0,400));
    Zh1_postZcut = store(new TH1D("Zh1_postZcut","DiLepton Mass in Z Window",40,0,400));
    TTh1_postZcut = store(new TH1D("TTh1_postZcut","DiLepton Mass out of Z Window",40,0,400));
    Allh1_post2jets = store(new TH1D("Allh1_post2jets","DiLepton Mass",40,0,400));
    Zh1_post2jets = store(new TH1D("Zh1_post2jets","DiLepton Mass in Z Window",40,0,400));
    TTh1_post2jets = store(new TH1D("TTh1_post2jets","DiLepton Mass out of Z Window",40,0,400));
    Allh1_postMET = store(new TH1D("Allh1_postMET","DiLepton Mass",40,0,400));
    Zh1_postMET = store(new TH1D("Zh1_postMET","DiLepton Mass in Z Window",40,0,400));
    TTh1_postMET = store(new TH1D("TTh1_postMET","DiLepton Mass out of Z Window",40,0,400));
    Allh1_post1btag = store(new TH1D("Allh1_post1btag","DiLepton Mass",40,0,400));
    Zh1_post1btag = store(new TH1D("Zh1_post1btag","DiLepton Mass in Z Window",40,0,400));
    TTh1_post1btag = store(new TH1D("TTh1_post1btag","DiLepton Mass out of Z Window",40,0,400));
    Allh1_postKinReco = store(new TH1D("Allh1_postKinReco","DiLepton Mass",40,0,400));
    Zh1_postKinReco = store(new TH1D("Zh1_postKinReco","DiLepton Mass in Z Window",40,0,400));
    TTh1_postKinReco = store(new TH1D("TTh1_postKinReco","DiLepton Mass out of Z Window",40,0,400));
    Looseh1 = store(new TH1D("Looseh1","DiLepton Mass",40,0,400));
    
    
    // Map for binned control plots
    binnedControlPlots = new std::map<std::string, std::pair<TH1*, std::vector<std::map<std::string, TH1*> > > >;
    
    // FIXME: remove ___XX after Analysis.h is split from DileptonAnalysis.h
    h_jetpT___XX = store(new TH1D ( "jetpT", "jet pT", 80, 0, 400 ));
    // FIXME: now needs HistoList, to be changed
    CreateBinnedControlPlots(h_jetCategories_step8, h_jetpT___XX);
    
    
    // FIXME: nothing yet about b-tagging scale factors, ever needed ?
}




Bool_t
HiggsAnalysis::Process(Long64_t entry){
    
    if (++EventCounter % 100000 == 0) std::cout << "Event Counter: " << EventCounter << std::endl;
    
    // Histogram for controlling correctness of h_step1, which should be the same for all samples except Zjets and ttbarsignalplustau
    h_step0->Fill(1, 1);
    
    //do we have a DY true level cut?
    if (checkZDecayMode && !checkZDecayMode(entry)) return kTRUE;
    
    if (isTtbarPlusTauSample || correctMadgraphBR) b_TopDecayMode->GetEntry(entry);
    //decayMode contains the decay of the top (*10) + the decay of the antitop
    //1=hadron, 2=e, 3=mu, 4=tau->hadron, 5=tau->e, 6=tau->mu
    //i.e. 23 == top decays to e, tbar decays to mu
    if (isTtbarPlusTauSample) {
        bool isViaTau = topDecayMode > 40 || ( topDecayMode % 10 > 4 );
        bool isCorrectChannel = false;
        switch (channelPdgIdProduct) {
            case -11*13: isCorrectChannel = topDecayMode == 23 || topDecayMode == 32 //emu prompt
                            || topDecayMode == 53 || topDecayMode == 35 //e via tau, mu prompt
                            || topDecayMode == 26 || topDecayMode == 62 //e prompt, mu via tau
                            || topDecayMode == 56 || topDecayMode == 65; //both via tau
                            break;
            case -11*11: isCorrectChannel = topDecayMode == 22  //ee prompt
                            || topDecayMode == 52 || topDecayMode == 25 //e prompt, e via tau
                            || topDecayMode == 55; break; //both via tau
            case -13*13: isCorrectChannel = topDecayMode == 33
                            || topDecayMode == 36 || topDecayMode == 63
                            || topDecayMode == 66; break;
            default: cerr << "Invalid channel! Product = " << channelPdgIdProduct << "\n";
        };
        bool isBackgroundInSignalSample = !isCorrectChannel || isViaTau;
        if (runViaTau != isBackgroundInSignalSample) return kTRUE;
    }

    GetRecoBranches(entry);
    //We must correct for the madGraph branching fraction being 1/9 for dileptons (PDG average is .108)
    if ( correctMadgraphBR ) {
        if ( topDecayMode == 11 ) { //all hadronic decay
            weightGenerator *= (0.676*1.5) * (0.676*1.5);
        } else if ( topDecayMode< 20 || ( topDecayMode % 10 == 1) ) { //semileptonic Decay
            weightGenerator *= (0.108*9) * (0.676*1.5);
        } else {//dileptonic decay (including taus!)
            weightGenerator *= (0.108*9) * (0.108*9);
        }
    }
    
    
    // FIXME: here were PDF variations, not needed now, and perhaps never
    
    
    // FIXME: corrections to jet energy resolution/scale, also here ?
    //if(doJesJer)applyJER_JES();
    
    
    // apply all jet cuts
    cleanJetCollection();
    
    
    double weightPU = 1;
    if (isMC && pureweighter)weightPU = pureweighter->getPUweight(vertMultiTrue);
    
    
    // FIXME: something was done about matching of BHadron to jets for ttbar sample, not needed now
    
    
    // CSV Loose working point
    double BtagWP = 0.244;
    vector<int> BJetIndex;
    for ( vector<double>::iterator it = jetBTagCSV->begin(); it<jetBTagCSV->end(); it++ ) {
        if ( *it > BtagWP) {
            //BJetIndex.push_back ( *it );
            BJetIndex.push_back((it-jetBTagCSV->begin())); //change asked by Tyler
        }
    }
    
    
    // FIXME: here was dealt with ttbar generator information, not needed now
    
    
    
    //===CUT===
    // this is step0, so no cut application
    
    h_step1->Fill(1, 1);
    
    // ++++ Control Plots ++++
    
    h_jetCategories_step0->Fill(jetCategories_.categoryId(jets->size(),NumberOfBJets(jetBTagCSV)), 1);
    
    // is this histo needed for anything ?
    //h_PUSF->Fill(weightPU, 1);
    
    
    
    //===CUT===
    // check if event was triggered
    //our triggers (bits: see the ntuplewriter!)
    constexpr int mumuTriggers = 0x8 + 0x20; //17/8 + 17Tr8
    constexpr int emuTriggers = 0x2000 + 0x4000;
    constexpr int eeTriggers = 0x40000;
    
    if (!(((triggerBits & mumuTriggers) && channelPdgIdProduct == -13*13)    //mumu triggers in rightmost byte
          ||((triggerBits & emuTriggers) && channelPdgIdProduct == -11*13)     //emu in 2nd byte
          ||((triggerBits & eeTriggers) && channelPdgIdProduct == -11*11)))    //ee in 3rd byte
    {
        return kTRUE;
    }
    
    size_t LeadLeptonNumber = 0;
    size_t NLeadLeptonNumber = 0;
    bool hasLeptonPair = getLeptonPair(LeadLeptonNumber, NLeadLeptonNumber);
    
    h_step2->Fill(1, 1);
    
    // ++++ Control Plots ++++
    
    h_jetCategories_step1->Fill(jetCategories_.categoryId(jets->size(),NumberOfBJets(jetBTagCSV)), 1);
    
    
    
    //===CUT===
    // we need an OS lepton pair
    if (! hasLeptonPair) return kTRUE;
    // lepton pt cut > 20, sufficient to test the second leading lepton
    if (leptons->at(NLeadLeptonNumber).pt() <= 20) return kTRUE;
    
    LV dilepton = leptons->at(LeadLeptonNumber) + leptons->at(NLeadLeptonNumber);
    
    h_step3->Fill(1, 1);
    
    // ++++ Control Plots ++++
    
    h_jetCategories_step2->Fill(jetCategories_.categoryId(jets->size(),NumberOfBJets(jetBTagCSV)), 1);
    
    
    
    //===CUT===
    //with at least 20 GeV invariant mass
    if (dilepton.M() < 20) return kTRUE;
    
    // find l+ and l-
    LV leptonPlus;
    LV leptonMinus;
    if (lepPdgId->at(LeadLeptonNumber) < 0) {
        leptonPlus = leptons->at(LeadLeptonNumber);
        leptonMinus = leptons->at(NLeadLeptonNumber);
    } else {
        leptonMinus = leptons->at(LeadLeptonNumber);
        leptonPlus = leptons->at(NLeadLeptonNumber);
    }

    //This is necessary due to the ordering in the trigger 2D-plots
    LV leptonX, leptonY;
    if ( abs( lepPdgId->at(LeadLeptonNumber) ) == abs( lepPdgId->at(NLeadLeptonNumber) ) ){
        //in ee and mumu channel leptonX must be the highest pT lepton
        leptonX = leptons->at(LeadLeptonNumber);
        leptonY = leptons->at(NLeadLeptonNumber);
    } else {
        // in emu channel lepX should be electron
        if (abs(lepPdgId->at(LeadLeptonNumber)) == 11) {
            leptonX = leptons->at(LeadLeptonNumber);
            leptonY = leptons->at(NLeadLeptonNumber);
        } else {
            leptonX = leptons->at(NLeadLeptonNumber);
            leptonY = leptons->at(LeadLeptonNumber);
        }
    }
    
    int LleptonId = lepPdgId->at(LeadLeptonNumber);
    int NLleptonId = lepPdgId->at(NLeadLeptonNumber);
    //Now determine the lepton trigger and ID scale factors
    double weightLepSF = isMC ? getLeptonIDSF(leptons->at(LeadLeptonNumber), leptons->at(NLeadLeptonNumber), LleptonId, NLleptonId) : 1;  
    double weightTrigSF = isMC ? getTriggerSF(leptonX, leptonY) : 1;
    
    //First control plots after dilepton selection (without Z cut)
    double weight = weightGenerator*weightTrigSF*weightLepSF;
    
    //weight even without PU reweighting --- FIXME: commented plot probably interesting
    //h_vertMulti_noPU->Fill(vertMulti, weight);
    
    //apply PU reweighting - continue with control plots --- FIXME: commented plot probably interesting
    weight *= weightPU;
    //h_vertMulti->Fill(vertMulti, weight);
    
    h_step4->Fill(1, weight);
    
    //****************************************
    //handle inverted Z cut
    // Fill loose dilepton mass histogram before any jet cuts
    bool isZregion = dilepton.M() > 76 && dilepton.M() < 106;
    // FIXME: define jet pt cut and select with following line
    //bool hasJets = jets->size() > 1 && jets->at(1).Pt() > JETPTCUT;
    bool hasJets = jets->size() > 1;
    bool hasMetOrEmu = channel == "emu" || met->Pt() > 40;
    bool hasBtag = BJetIndex.size() > 0;
    //bool hasSolution = HypTop->size() > 0;
    bool hasSolution = calculateKinReco(leptonMinus, leptonPlus);
    
    // Z window plots need to be filled here, in order to rescale the contribution to data
    if ( isZregion ) {
        double fullWeights = weightGenerator*weightPU*weightTrigSF*weightLepSF;
        Zh1_postZcut->Fill(dilepton.M(), fullWeights);
        Allh1_postZcut->Fill(dilepton.M(), fullWeights);
        
        if ( hasJets ) {
            Looseh1->Fill(dilepton.M(), fullWeights);
            Zh1_post2jets->Fill(dilepton.M(), fullWeights);
            Allh1_post2jets->Fill(dilepton.M(), fullWeights);
            
            if ( hasMetOrEmu ) {
                Zh1_postMET->Fill(dilepton.M(), fullWeights);
                Allh1_postMET->Fill(dilepton.M(), fullWeights);
                
                if ( hasBtag ) {
                    // FIXME: do not use b-tag scale factor
		    //weightBtagSF = isMC ? calculateBtagSF() : 1;
                    //fullWeights *= weightBtagSF;
                    Zh1_post1btag->Fill(dilepton.M(), fullWeights);
                    Allh1_post1btag->Fill(dilepton.M(), fullWeights);
                    
                    if ( hasSolution ) {
                        // FIXME: weightKinFit is just a constant, but is it valid for each event selection (jetCategories) and can be used here?
			//fullWeights *= weightKinFit;
                        Zh1_postKinReco->Fill(dilepton.M(), fullWeights);
                        Allh1_postKinReco->Fill(dilepton.M(), fullWeights);
                    }
                }
            }
        }
    }
    
    // ++++ Control Plots ++++
    
    h_jetCategories_step3->Fill(jetCategories_.categoryId(jets->size(),NumberOfBJets(jetBTagCSV)), weight);
    
    
    
    //=== CUT ===
    //Exclude the Z window
    if (channel != "emu" && isZregion) return kTRUE;
    
    h_step5->Fill(1, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        TTh1_postZcut->Fill(dilepton.M(), weight);
        Allh1_postZcut->Fill(dilepton.M(), weight);  //this is also filled in the Z region in the code above
    }
    
    // ++++ Control Plots ++++
    
    h_jetCategories_step4->Fill(jetCategories_.categoryId(jets->size(),NumberOfBJets(jetBTagCSV)), weight);
    
    
    
    //=== CUT ===
    //Require at least two jets > 30 GeV (check for > 30 needed because we might have 20 GeV jets in our NTuple)
    if (! hasJets) return kTRUE;
    
    h_step6->Fill(1, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        TTh1_post2jets->Fill(dilepton.M(), weight);
        Allh1_post2jets->Fill(dilepton.M(), weight);  //this is also filled in the Z region in the code above
    }
    
    // ++++ Control Plots ++++
    
    h_jetCategories_step5->Fill(jetCategories_.categoryId(jets->size(),NumberOfBJets(jetBTagCSV)), weight);
    
    
    
    //=== CUT ===
    //Require MET > 40 GeV in non-emu channels
    if (!hasMetOrEmu) return kTRUE;
    
    h_step7->Fill(1, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        TTh1_postMET->Fill(dilepton.M(), weight);
        Allh1_postMET->Fill(dilepton.M(), weight);  //this is also filled in the Z region in the code above
    }
    
    // ++++ Control Plots ++++
    
    h_jetCategories_step6->Fill(jetCategories_.categoryId(jets->size(),NumberOfBJets(jetBTagCSV)), weight);
    
    
    
    //=== CUT ===
    //Require at least one b tagged jet
    if (!hasBtag) return kTRUE;
    
    // FIXME: if b-tagging scale factor is desired, calculate it here ?
    // weight *= weightBtagSF;
    
    h_step8->Fill(1, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        TTh1_post1btag->Fill(dilepton.M(), weight);
        Allh1_post1btag->Fill(dilepton.M(), weight);  //this is also filled in the Z region in the code above
    }
    
    // ++++ Control Plots ++++
    
    h_jetCategories_step7->Fill(jetCategories_.categoryId(jets->size(),NumberOfBJets(jetBTagCSV)), weight);
    
    
    
    //=== CUT ===
    //Require at least one solution for the kinematic event reconstruction
    if (!hasSolution) return kTRUE;
    // FIXME: weightKinFit is just a constant, but is it valid for each event selection (jetCategories) and can be used here?
    //weight *= weightKinFit;
    
    h_step9->Fill(1, weight);
    
    if (!isZregion) { //also apply Z cut in emu!
        TTh1_postKinReco->Fill(dilepton.M(), weight);
        Allh1_postKinReco->Fill(dilepton.M(), weight);  //this is also filled in the Z region in the code above
    }
    
    // ++++ Control Plots ++++
    
    h_jetCategories_step8->Fill(jetCategories_.categoryId(jets->size(),NumberOfBJets(jetBTagCSV)), weight);
    for(unsigned int iJet = 0; iJet < jets->size(); ++iJet){
        FillBinnedControlPlot(h_jetCategories_step8, jetCategories_.categoryId(jets->size(),NumberOfBJets(jetBTagCSV)), h_jetpT___XX, jets->at(iJet).Pt(), weight);
    }
    
    
    
    return kTRUE;
}



void HiggsAnalysis::SetSamplename(TString samplename)
{
    this->samplename = samplename;
    isTtbarPlusTauSample = samplename.BeginsWith("ttbar") && !samplename.BeginsWith("ttbarhiggs") && !(samplename=="ttbarw") && !(samplename=="ttbarz") && !samplename.Contains("bg");
    // FIXME: for ttbarW, also correction for 3rd W needs to be applied
    // FIXME: and what about Wlnu sample ?
    correctMadgraphBR = samplename.BeginsWith("ttbar") && !samplename.BeginsWith("ttbarhiggs");
}



bool HiggsAnalysis::produceBtagEfficiencies(){
    return false;
}


