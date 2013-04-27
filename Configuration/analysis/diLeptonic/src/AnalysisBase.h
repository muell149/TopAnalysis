#ifndef AnalysisBase_h
#define AnalysisBase_h

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <functional>

#include <TSelector.h>
#include <Rtypes.h>

class TBranch;
class TTree;
class TH1;
class TH2;
class TString;

#include "classesFwd.h"
#include "storeTemplate.h"

class PUReweighter;
class JetCorrectionUncertainty;





class AnalysisBase : public TSelector
{
    
// Protected member data
protected:    
    
    /// Variables associated to nTuple branches relevant for reconstruction level
    // Concerning physics objects
    VLV                 *leptons_;
    std::vector<int>    *lepPdgId_;
    //std::vector<double> *lepID_;
    std::vector<double> *lepPfIso_;
    //std::vector<double> *lepChargedHadronIso_;
    //std::vector<double> *lepNeutralHadronIso_;
    //std::vector<double> *lepPhotonIso_;
    //std::vector<double> *lepPuChargedHadronIso_;
    std::vector<double> *lepCombIso_;
    std::vector<double> *lepDxyVertex0_;
    //std::vector<int>    *lepTrigger_;
    VLV                 *jets_;
    std::vector<double> *jetBTagTCHE_;
    //std::vector<double> *jetBTagTCHP_;
    std::vector<double> *jetBTagSSVHE_;
    //std::vector<double> *jetBTagSSVHP_;
    //std::vector<double> *jetBTagJetProbability_;
    //std::vector<double> *jetBTagJetBProbability_;
    std::vector<double> *jetBTagCSV_;
    //std::vector<double> *jetBTagCSVMVA_;
    std::vector<double> *jetChargeGlobalPtWeighted_;
    std::vector<double> *jetChargeRelativePtWeighted_;
    LV                  *met_;
    std::vector<double> *jetJERSF_;
    VLV                 *jetsForMET_;
    std::vector<double> *jetForMETJERSF_;
    
    // Concerning event
    UInt_t runNumber_;
    UInt_t lumiBlock_;
    UInt_t eventNumber_;
    //int    recoInChannel_;
    Int_t  vertMulti_;
    
    
    /// Variables associated to nTuple branches holding trigger bits
    UInt_t triggerBits_;
    //UInt_t triggerBitsTau_;
    //std::vector<std::string> *firedTriggers_;
    
    
    /// Variables associated to nTuple branches holding generator information for all MC samples
    // Concerning physics objects
    VLV                *allGenJets_;
    std::vector<int>   *jetPartonFlavour_;
    VLV                *associatedGenJet_;
    VLV                *associatedGenJetForMET_;
    //std::vector<int>   *jetAssociatedPartonPdgId_;
    //std::vector<LV>    *jetAssociatedParton_;
    
    
    /// Variables associated to nTuple branches of kinematic reconstruction
    VLV              *HypTop_;
    VLV              *HypAntiTop_;
    VLV              *HypLepton_;
    VLV              *HypAntiLepton_;
    VLV              *HypNeutrino_;
    VLV              *HypAntiNeutrino_;
    VLV              *HypBJet_;
    VLV              *HypAntiBJet_;
    //VLV              *HypWPlus_;
    //VLV              *HypWMinus_;
    std::vector<int> *HypJet0index_;
    std::vector<int> *HypJet1index_;
    
    
    /// Variables associated to nTuple branch of true vertex multiplicity
    Int_t vertMultiTrue_;
    
    
    /// Variables associated to nTuple branch for generator event weight 
    Double_t weightGenerator_;
    
    
    /// Variables associated to nTuple branch for PDF weights
    std::vector<double> *weightPDF_;
    
    
    /// Variables associated to nTuple branch for Drell-Yan decay mode
    std::vector<int> *ZDecayMode_;
    
    
    /// Variables associated to nTuple branch for Top decay mode
    Int_t topDecayMode_;
    
    
    /// Variables associated to nTuple branch for Higgs decay mode
    Int_t higgsDecayMode_;
    
    
    
    /// Variables associated to nTuple branches for Top signal samples on generator level
    LV                *GenMet_;
    LV                *GenTop_;
    LV                *GenAntiTop_;
    LV                *GenLepton_;
    LV                *GenAntiLepton_;
    //int               GenLeptonPdgId_;
    //int               GenAntiLeptonPdgId_;
    //LV                *GenTau_;
    //LV                *GenAntiTau_;
    LV                *GenNeutrino_;
    LV                *GenAntiNeutrino_;
    LV                *GenB_;
    LV                *GenAntiB_;
    LV                *GenWPlus_;
    LV                *GenWMinus_;
    //std::vector<LV>   *GenParticleP4_;
    //std::vector<int>  *GenParticlePdgId_;
    //std::vector<int>  *GenParticleStatus_;
    std::vector<int>  *BHadJetIndex_;
    std::vector<int>  *AntiBHadJetIndex_;
    VLV               *BHadrons_;
    VLV               *AntiBHadrons_;
    std::vector<bool> *BHadronFromTopB_;
    std::vector<bool> *AntiBHadronFromTopB_;
    std::vector<int>  *BHadronVsJet_;
    std::vector<int>  *AntiBHadronVsJet_;
    //std::vector<int>  *genBHadPlusMothersPdgId_;
    //std::vector<int>  *genBHadPlusMothersStatus_;
    //std::vector<std::vector<int> > *genBHadPlusMothersIndices_;
    std::vector<LV>   *genBHadPlusMothers_;
    std::vector<int>  *genBHadIndex_;
    std::vector<int>  *genBHadFlavour_;
    std::vector<int>  *genBHadJetIndex_;
    
    
    /// Variables associated to nTuple branches for Higgs signal samples on generator level
    LV    *GenH_;
    LV    *GenBFromH_;
    LV    *GenAntiBFromH_;
    
    
    /// Information in nTuple stored in TObjString once per file, but added from outside and potentially configured
    TString samplename_;
    TString channel_;
    TString systematic_;
    bool isMC_;
    bool isTopSignal_;
    bool isHiggsSignal_;
    
    
    /// Further variables added from the outside
    bool isTtbarPlusTauSample_;
    bool correctMadgraphBR_;
    int channelPdgIdProduct_;
    int trueDYchannelCut_;   // is this variable used at all?
    #ifndef __CINT__   
    std::function<bool(Long64_t)> checkZDecayMode_;
    #endif
    TString outputfilename_;
    bool runViaTau_;
    
    
    /// Pileup reweighter, configured from outside
    PUReweighter *puReweighter_;
    
    
    /// Apply JER/JES systematics
    bool doJesJer_;
    
    
    /// Scale factor due to kinematic reconstruction
    double weightKinFit_; //this is per channel and does not need to be calculated inside the event loop
    
    
    /// Whether it is a ttbar sample (and not ttbarH, ttbarW, ttbarZ, or any other thing)
    bool isTtbarSample_;
    
    
    /// Map holding binned control plots
    //binnedControlPlots contains:
    //map of name of differential distribution
    // -> pair( histogram with the binning of the differential distribution,
    //          vector(bin) -> map( control plot name -> TH1*))
    std::map<std::string, std::pair<TH1*, std::vector<std::map<std::string, TH1*> > > > *binnedControlPlots_;
    
    
        
// Private member data
private:    
    
    /// Pointer to the analyzed TTree or TChain
    TTree *chain_;
    
    
    /// nTuple branches relevant for reconstruction level
    // Concerning physics objects
    TBranch *b_lepton;
    TBranch *b_lepPdgId;
    TBranch *b_lepID;
    TBranch *b_lepPfIso;
    TBranch *b_lepChargedHadronIso;
    TBranch *b_lepNeutralHadronIso;
    TBranch *b_lepPhotonIso;
    TBranch *b_lepPuChargedHadronIso;
    TBranch *b_lepCombIso;
    TBranch *b_lepDxyVertex0;
    TBranch *b_lepTrigger;
    TBranch *b_jet;
    TBranch *b_jetBTagTCHE;
    TBranch *b_jetBTagTCHP;
    TBranch *b_jetBTagSSVHE;
    TBranch *b_jetBTagSSVHP;
    TBranch *b_jetBTagJetProbability;
    TBranch *b_jetBTagJetBProbability;
    TBranch *b_jetBTagCSV;
    TBranch *b_jetBTagCSVMVA;
    TBranch *b_jetChargeGlobalPtWeighted;
    TBranch *b_jetChargeRelativePtWeighted;
    TBranch *b_met;
    TBranch *b_jetJERSF;
    TBranch *b_jetForMET;
    TBranch *b_jetForMETJERSF;
    
    // Concerning event
    TBranch *b_runNumber;
    TBranch *b_lumiBlock;
    TBranch *b_eventNumber;
    TBranch *b_recoInChannel;
    TBranch *b_vertMulti;
    
    
    /// nTuple branches holding trigger bits
    TBranch *b_triggerBits;
    TBranch *b_triggerBitsTau;
    TBranch *b_firedTriggers;
    
    
    /// nTuple branches holding generator information for all MC samples
    // Concerning physics objects
    TBranch *b_allGenJets;
    TBranch *b_jetPartonFlavour;
    TBranch *b_associatedGenJet;
    TBranch *b_associatedGenJetForMET;
    TBranch *b_jetAssociatedPartonPdgId;
    TBranch *b_jetAssociatedParton;
    
    
    /// nTuple branches of kinematic reconstruction
    TBranch *b_HypTop;
    TBranch *b_HypAntiTop;
    TBranch *b_HypLepton;
    TBranch *b_HypAntiLepton;
    TBranch *b_HypNeutrino;
    TBranch *b_HypAntiNeutrino;
    TBranch *b_HypB;
    TBranch *b_HypAntiB;
    TBranch *b_HypWPlus;
    TBranch *b_HypWMinus;
    TBranch *b_HypJet0index;
    TBranch *b_HypJet1index;
    
    
    /// nTuple branch of true vertex multiplicity
    TBranch *b_vertMultiTrue;
    
    
    /// nTuple branch for generator event weight
    TBranch *b_weightGenerator;
    
    
    /// nTuple branch for PDF weights
    TBranch *b_weightPDF;
    
    
    /// nTuple branch for Drell-Yan decay mode
    TBranch *b_ZDecayMode;
    
    
    /// nTuple branch for Top decay mode
    TBranch *b_TopDecayMode;
    
    
    /// nTuple branch for Higgs decay mode
    TBranch *b_HiggsDecayMode;
    
    
    /// nTuple branches for Top signal samples on generator level
    TBranch *b_GenMet;
    TBranch *b_GenTop;
    TBranch *b_GenAntiTop;
    TBranch *b_GenLepton;
    TBranch *b_GenAntiLepton;
    TBranch *b_GenLeptonPdgId;
    TBranch *b_GenAntiLeptonPdgId;
    TBranch *b_GenTau;
    TBranch *b_GenAntiTau;
    TBranch *b_GenNeutrino;
    TBranch *b_GenAntiNeutrino;
    TBranch *b_GenB;
    TBranch *b_GenAntiB;
    TBranch *b_GenWPlus;
    TBranch *b_GenWMinus;
    TBranch *b_GenParticleP4;
    TBranch *b_GenParticlePdgId;
    TBranch *b_GenParticleStatus;
    TBranch *b_BHadJetIndex;
    TBranch *b_AntiBHadJetIndex;
    TBranch *b_BHadrons;
    TBranch *b_AntiBHadrons;
    TBranch *b_BHadronFromTopB;
    TBranch *b_AntiBHadronFromTopB;
    TBranch *b_BHadronVsJet;
    TBranch *b_AntiBHadronVsJet;
    TBranch *b_genBHadPlusMothersPdgId;
    TBranch *b_genBHadPlusMothersStatus;
    TBranch *b_genBHadPlusMothersIndices;
    TBranch *b_genBHadPlusMothers;
    TBranch *b_genBHadIndex;
    TBranch *b_genBHadFlavour;
    TBranch *b_genBHadJetIndex;
    

    /// nTuple branches for Higgs signal samples on generator level
    TBranch *b_GenH;
    TBranch *b_GenBFromH;
    TBranch *b_GenAntiBFromH;
    
    
    /// Histogram holding the number of weighted events of the full sample, configured from outside
    TH1* h_weightedEvents;
    
    
    /// Uncertainty for JES systematics
    JetCorrectionUncertainty *unc_;
    
    
    /// Filename of file holding b-tag efficiency histograms, configured from outside
    TString btagFile_;
    
    
    /// Histograms for writing out b-tagging efficiencies
    TH2 *h_bjets, *h_cjets, *h_ljets;
    TH2 *h_btaggedjets, *h_ctaggedjets, *h_ltaggedjets;
    
    
    /// Histograms of per-jet b-tagging efficiencies, used to calculate per-event SF
    /// Need to be written out to file previously
    TH2 *h2_bEff, *h2_cEff, *h2_lEff;
    
    
    /// Trigger and lepton scale factors differential in eta, pt
    TH2 *h_TrigSFeta, *h_MuonIDSFpteta, *h_ElectronIDSFpteta;
    
    
    /// Medians in eta, pt for b-tag SF
    double btag_ptmedian_, btag_etamedian_;
    
    
    /// Event counter
    Int_t eventCounter_;
    
    

// Public methods
public:
    
    /// Constructor
    AnalysisBase(TTree* =0);
    
    /// Destructor
    virtual ~AnalysisBase(){};
    
    /// Inherited TSelector methods
    virtual void Begin(TTree*);
    virtual void SlaveBegin(TTree*);
    virtual Bool_t Process(Long64_t);
    virtual void Init(TTree*);
    virtual void SlaveTerminate();
    virtual void Terminate();
    
    /// Set sample name
    void SetSamplename(const TString& samplename, const TString& systematic_from_file);
    /// Set Channel
    void SetChannel(const TString& channel);
    /// Set systematic
    void SetSystematic(const TString& systematic);
    /// Set whether it is MC sample
    void SetMC(const bool isMC);
    /// Set whether it is Top signal sample
    void SetTopSignal(const bool isTopSignal);
    /// Set whether it is Higgs signal sample
    void SetHiggsSignal(const bool higgsSignal);
    
    /// Set Drell-Yan decay channel for selection, access decay mode from nTuple branch
    void SetTrueLevelDYChannel(const int dy);
    /// Set name of output file
    void SetOutputfilename(const TString& outputfilename);
    /// Bool for separating direct dileptonic ttbar decays and decays via intermediate taus
    void SetRunViaTau(const bool runViaTau);
    
    /// Set input file for b-tagging efficiencies
    void SetBTagFile(const TString& btagFile);
    
    /// Set the pileup reweighter
    void SetPUReweighter(PUReweighter* puReweighter);
    
    /// Set histogram containing the number of weighted events in full sample
    void SetWeightedEvents(TH1* weightedEvents);
    
    /// Get version
    //no idea why this is needed! But Process() isn't called otherwise! Argh!
    virtual int Version() const { return 3; }
    
    /// Class definition
    ClassDef(AnalysisBase, 0);
    
    
    
// Protected methods
protected:
    
    /// Access event entry for nTuple branches relevant for reconstruction level
    void GetRecoBranchesEntry(const Long64_t&)const;
    /// Access event entry for nTuple branches for trigger bits
    void GetTriggerBranchesEntry(const Long64_t&)const;
    /// Access event entry for nTuple branches holding generator information for all MC samples
    void GetCommonGenBranchesEntry(const Long64_t&)const;
    /// Access event entry for nTuple branches of kinematic reconstruction
    void GetKinRecoBranchesEntry(const Long64_t&)const;
    /// Access event entry for nTuple branch of true vertex multiplicity
    void GetVertMultiTrueEntry(const Long64_t&)const;
    /// Access event entry for nTuple branch for generator event weight
    void GetWeightGeneratorEntry(const Long64_t&)const;
    /// Access event entry for nTuple branch for PDF weights
    void GetPDFEntry(const Long64_t&)const;
    /// Access event entry for nTuple branch for Top decay mode
    void GetTopDecayModeEntry(const Long64_t&)const;
    /// Access event entry for nTuple branch for Higgs decay mode
    void GetHiggsDecayModeEntry(const Long64_t&)const;
    /// Access event entry for nTuple branches for Top signal samples on generator level
    void GetTopSignalBranchesEntry(const Long64_t&)const;
    /// Access event entry for nTuple branches for Higgs signal samples on generator level
    void GetHiggsSignalBranchesEntry(const Long64_t&)const;
    
    /** Return a string describing the true level W+/W- decays from the ttbar system
     * 
     * @return a string like e/tau->mu describing the decay to the W+/W- from the top/tbar decay
     * 
     * Possible strings are:
     *   e/e  for the ee channel
     *   e/tau->mu for the W+ -> e+ decay and the W- -> tau- -> mu- decay
     *   ... and so on. The first part is from the top/W+, the second from the tbar/W-
     */
    const std::string topDecayModeString()const;
    
    /// Book histograms needed for b-tag efficiencies
    void bookBtagHistograms();
    /// Fill histograms needed for b-tag efficiencies
    void fillBtagHistograms(const std::vector<int>& jetIndices, const std::vector<int>& bjetIndices, const double weight = 1);
    /// Produce b-tag efficiencies
    void produceBtagEfficiencies();
    
    /// Prepare trigger scale factor
    void prepareTriggerSF();
    /// Get trigger per-event scale factor
    double getTriggerSF(const int leptonXIndex, const int leptonYIndex)const;
    
    /// Prepare lepton scale factor
    void prepareLeptonIDSF();
    /// Get lepton per-event scale factor
    double getLeptonIDSF(const int leadingLeptonIndex, const int nLeadingLeptonIndex)const;
    
    /// Prepare b-tagging scale factor (efficiency histograms and medians of jet eta, pt)
    void prepareBtagSF();
    /// Get b-tag per-event scale factor
    double calculateBtagSF(const std::vector<int>& jetIndices)const;
    
    
    
    // FIXME: these methods will be moved to own b-tagging class (several anyway would be private)
    /// Return the indexes of the jet that are b-tagged after randomization
    std::vector<int> indexOfBtags(const std::vector<int>& jetIndices, const double TagCut = 0.244);
    /// 'Random' decision to tag or not tag a jet.
    /// Method explained in: https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFUtil
    /// and in: https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods#2a_Jet_by_jet_updating_of_the_b
    bool isTagged(LV Jet, double TagValue, int Flavour, double TagCut = 0.244);
    double getEfficiency(LV jet, int partonFlavour);
    double getSF(double pt, double abs_eta, int flavour);
    /// Decide wich type of BTag variation is going to be done according to 
    ///   systematics name 
    ///   median value (if applicable)
    double varySF(double pt, double eta, int flavour, double ptmedian, double etamedian);
    bool makeeffs;
    
    

    /** Set up the scale factor for the Kinematic Reconstruction
     * 
     * Currently a flat per-channel SF is used. For the systematic KIN_UP and KIN_DOWN,
     * the SF is modified by its uncertainty.
     * 
     * To calculate the SF, you need to set the SF to 1 and rerun. Then determine the
     * SF with kinRecoEfficienciesAndSF
     */
    void prepareKinRecoSF();
    /** Calculate the kinematic reconstruction and return whether at least one solution exists
     * 
     * reconstruct the top quarks and store the result in the 
     * Hyp* member variables
     * 
     * @param leptonMinus 4-vector of the l-
     * @param leptonPlus 4-vector of the l+
     * 
     * @return true if there is at least one solution
     */
    bool calculateKinReco(const int leptonIndex, const int antiLeptonIndex,
                          const std::vector<int>& jetIndices, const LV& met);
    
    /** prepare JER/JES systematics
     * 
     * This function checks if we are asked to run JER or JES. If so,
     * additional branches need to be enabled and a JES uncertainty file
     * needs to be read.
     */
    void prepareJER_JES();
    /// Apply the JER or JES systematic
    /// This function modifies the jets collection and also scales the MET.
    /// It uses the collections stored just for the jet scaling
    void applyJER_JES();
    
    /// Get 2-dimensional scale factor from histogram
    double get2DSF(TH2* histo, const double x, const double y)const;
    
    /// Check if opposite-charge dilepton combination exists,
    /// and check if lepton pair is correct flavour combination for the specified analysis channel (ee, emu, mumu)
    bool hasLeptonPair(const int leadingLeptonIndex, const int nLeadingLeptonIndex)const;
    
    /// Check if event was triggered with the same dilepton trigger as the specified analysis channel
    bool failsDileptonTrigger(const Long64_t&)const;
    
    /// Get H_t of jets
    double getJetHT(const std::vector<int>& jetIndices, const VLV& jets)const;
    
    
    
    /// Select events from Drell-Yan samples which need to be removed due to generator selection
    bool failsDrellYanGeneratorSelection(const Long64_t&)const;
    
    /// Select events from Top signal samples which need to be removed due to generator selection
    bool failsTopGeneratorSelection(const Long64_t&)const;
    
    /// Correct branching ratios of W decays in MadGraph samples
    double madgraphWDecayCorrection(const Long64_t&)const;
    
    /// Get weight due to pileup reweighting
    double weightPileup(const Long64_t&)const;
    
    
    
    /// Create binned control plots
    // Create Nbins control plots for the differential distribution h_differential
    // Use h_control for the control plot name and binning
    void CreateBinnedControlPlots(TH1* h_differential, TH1* h_control, const bool fromHistoList =true);
    
    /// Fill binned control plots
    // h: differential distribution histogram
    // binvalue: the value of the quantity in the differential distribution histogram
    // the control plot histogram
    // the value for the control plot
    // weight: event weight
    void FillBinnedControlPlot(TH1* h_differential, double binvalue, 
                               TH1 *h_control, double value, double weight);
    
    /// Assign a folder depending on channel and systematic
    std::string assignFolder(const char* baseDir, const TString& channel, const TString& systematic)const;
    
    /// Store the object in the output list and return it
    template<class T> T* store(T* obj){return ttbar::store(obj, fOutput);}
    
    
    
// Private methods
private:
    
    /// Clear all branches
    void clearBranches();
    /// Clear all variables assigned to branches
    void clearBranchVariables();
    
    /// Set addresses of nTuple branches relevant for reconstruction level
    void SetRecoBranchAddresses();
    /// Set address of nTuple branches for trigger bits
    void SetTriggerBranchAddresses();
    /// Set addresses of nTuple branches holding generator information for all MC samples
    void SetCommonGenBranchAddresses();
    /// Set addresses of nTuple branches of kinematic reconstruction
    void SetKinRecoBranchAddresses();
    /// Set address of nTuple branch of true vertex multiplicity
    void SetVertMultiTrueBranchAddress();
    /// Set address of nTuple branch for generator event weight
    void SetWeightGeneratorBranchAddress();
    /// Set address of nTuple branch for PDF weights
    void SetPdfBranchAddress();
    /// Set address of nTuple branch for Drell-Yan decay mode
    void SetDyDecayBranchAddress();
    /// Set address of nTuple branch for Top decay mode
    void SetTopDecayBranchAddress();
    /// Set address of nTuple branch for Higgs decay mode
    void SetHiggsDecayBranchAddress();
    /// Set addresses of nTuple branches for Top signal samples on generator level
    void SetTopSignalBranchAddresses();
    /// Set addresses of nTuple branches for Higgs signal samples on generator level
    void SetHiggsSignalBranchAddresses();
    
    /// Methods needed for b-tag scale factor calculation
    double BJetSF(const double&, const double&)const;
    double CJetSF(const double&, const double&)const;
    double LJetSF(const double&, const double&, const TString&)const;
    double BJetSFAbsErr(const double&)const;
    double CJetSFAbsErr(const double&)const;
};





#endif




