#ifndef AnalysisBase_h
#define AnalysisBase_h

#include <vector>
#include <map>
#include <utility>
#include <functional>

#include <TSelector.h>
#include <TSelectorList.h>
#include <TParameter.h>
#include <Rtypes.h>

class TBranch;
class TTree;
class TH1;
class TH2;
class TString;

#include "JetCorrectorParameters.h"
#include "JetCorrectionUncertainty.h"
#include "classes.h"
#include "PUReweighter.h"



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
    std::vector<int>    *jetPartonFlavour_;
    VLV                 *allGenJets_;
    VLV                 *associatedGenJet_;
    std::vector<double> *jetChargeGlobalPtWeighted_;
    std::vector<double> *jetChargeRelativePtWeighted_;
    //std::vector<int>    *jetAssociatedPartonPdgId_;
    //std::vector<LV>     *jetAssociatedParton_;
    LV                  *met_;
    std::vector<double> *jetJERSF_;
    VLV                 *jetsForMET_;
    std::vector<double> *jetForMETJERSF_;
    VLV                 *associatedGenJetForMET_;
    
    // Concerning event
    UInt_t runNumber_;
    UInt_t lumiBlock_;
    UInt_t eventNumber_;
    //int    recoInChannel_;
    UInt_t triggerBits_;
    //UInt_t triggerBitsTau_;
    //std::vector<std::string> *firedTriggers_;
    Int_t  vertMulti_;
    
    // Concerning MC event
    Int_t               vertMultiTrue_;
    Double_t            weightGenerator_;
    
    
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
    
    
    /// Variables associated to nTuple branch for PDF weights
    std::vector<double> *weightPDF_;
    
    
    /// Variables associated to nTuple branch for Drell-Yan decay mode
    std::vector<int> *ZDecayMode_;
    
    
    /// Variables associated to nTuple branch for Top decay mode
    Int_t topDecayMode_;
    
    
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
    std::vector<int>  *genParticlePdg_;
    std::vector<int>  *genParticleStatus_;
    std::vector<std::vector<int> > *genParticleIndices_;
    std::vector<LV>   *genParticle_;
    std::vector<int>  *bHadIndex_;
    std::vector<int>  *bHadFlavour_;
    std::vector<int>  *bHadJetIndex_;
    
    
    /// Variables associated to nTuple branches for Higgs signal samples on generator level
    Int_t higgsDecayMode_;
    LV    *GenH_;
    LV    *GenBFromH_;
    LV    *GenAntiBFromH_;
    
    
    /// Information in nTuple stored in TObjString once per file, but added from outside and potentially configured
    TString samplename_;
    TString channel_;
    TString systematic_;
    bool isMC_;
    bool isSignal_;
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
    PUReweighter *pureweighter_;
    
    
    /// Apply JER/JES systematics
    bool doJesJer_;
    
    
    /// Scale factor due to kinematic reconstruction
    double weightKinFit_; //this is per channel and does not need to be calculated inside the event loop
    
    
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
    TBranch *b_jetPartonFlavour;
    TBranch *b_allGenJets;
    TBranch *b_associatedGenJet;
    TBranch *b_jetChargeGlobalPtWeighted;
    TBranch *b_jetChargeRelativePtWeighted;
    TBranch *b_jetAssociatedPartonPdgId;
    TBranch *b_jetAssociatedParton;
    TBranch *b_met;
    TBranch *b_jetJERSF;
    TBranch *b_jetForMET;
    TBranch *b_jetForMETJERSF;
    TBranch *b_associatedGenJetForMET;
    
    // Concerning event
    TBranch *b_runNumber;
    TBranch *b_lumiBlock;
    TBranch *b_eventNumber;
    TBranch *b_recoInChannel;
    TBranch *b_triggerBits;
    TBranch *b_triggerBitsTau;
    TBranch *b_firedTriggers;
    TBranch *b_vertMulti;
    
    // Concerning MC event
    TBranch *b_vertMultiTrue;
    TBranch *b_weightGenerator;
    
    
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
    
    
    /// nTuple branch for PDF weights
    TBranch *b_weightPDF;
    
    
    /// nTuple branch for Drell-Yan decay mode
    TBranch *b_ZDecayMode;
    
    
    /// nTuple branch for Top decay mode
    TBranch *b_TopDecayMode;
    
    
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
    TBranch *b_genParticlePdg;
    TBranch *b_genParticleStatus;
    TBranch *b_genParticleIndices;
    TBranch *b_genParticle;
    TBranch *b_bHadIndex;
    TBranch *b_bHadFlavour;
    TBranch *b_bHadJetIndex;
    

    /// nTuple branches for Higgs signal samples on generator level
    TBranch *b_HiggsDecayMode;
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
    TH2 *bEff, *cEff, *lEff;
    
    
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
    virtual void SetSamplename(TString samplename, TString systematic_from_file);
    /// Set Channel
    void SetChannel(TString channel);
    /// Set systematic
    void SetSystematic(TString systematic);
    /// Set whether it is MC sample
    void SetMC(bool isMC);
    /// Set whether it is Top signal sample
    void SetSignal(bool isSignal);
    /// Set whether it is Higgs signal sample
    void SetHiggsSignal(const bool higgsSignal);
    
    /// Set Drell-Yan decay channel for selection, access decay mode from nTuple branch
    void SetTrueLevelDYChannel(int dy);
    /// Set name of output file
    void SetOutputfilename(TString outputfilename);
    /// Bool for separating direct dileptonic ttbar decays and decays via intermediate taus
    void SetRunViaTau(bool runViaTau);
    
    /// Set input file for b-tagging efficiencies
    void SetBTagFile(TString btagFile);
    
    /// Set the pileup reweighter
    void SetPUReweighter(PUReweighter *pu);
    
    /// Set histogram containing the number of weighted events in full sample
    void SetWeightedEvents(TH1* weightedEvents);
    
    /// Get version
    //no idea why this is needed! But Process() isn't called otherwise! Argh!
    virtual int Version() const { return 3; }
    
    /// Class definition
    ClassDef(AnalysisBase, 0);
    
    
    
// Protected methods
protected:
    
    /// Set global normalisation factors (needs to be overwritable)
    virtual double overallGlobalNormalisationFactor();
    
    /// Access event entry for nTuple branches relevant for reconstruction level
    void GetRecoBranchesEntry(Long64_t&);
    /// Access event entry for nTuple branches of kinematic reconstruction
    void GetKinRecoBranchesEntry(Long64_t&);
    /// Access event entry for nTuple branch for PDF weights
    void GetPDFEntry(Long64_t&);
    /// Access event entry for nTuple branch for Top decay mode
    void GetTopDecayModeEntry(Long64_t&);
    /// Access event entry for nTuple branches for Top signal samples on generator level
    void GetTopSignalBranchesEntry(Long64_t&);
    /// Access event entry for nTuple branches for Higgs signal samples on generator level
    void GetHiggsSignalBranchesEntry(Long64_t&);
    
    /// Get string telling the Top decay mode
    const std::string topDecayModeString();
    
    /// Book histograms needed for b-tag efficiencies
    void bookBtagHistograms();
    /// Fill histograms needed for b-tag efficiencies
    void fillBtagHistograms(const double jetPtCut, const double btagWP);
    /// Produce b-tag efficiencies
    void produceBtagEfficiencies();
    
    /// Prepare trigger scale factor
    void prepareTriggerSF();
    /// Get trigger per-event scale factor
    double getTriggerSF(const LV& lep1, const LV& lep2);
    
    /// Prepare lepton scale factor
    void prepareLeptonIDSF();
    /// Get lepton per-event scale factor
    double getLeptonIDSF(const LV& lep1, const LV& lep2, int x, int y);
    
    /// Prepare b-tagging scale factor
    void prepareBtagSF();
    /// Get b-tag per-event scale factor
    double calculateBtagSF();
    
    /// Prepare kinematic reconstruction scale factor
    void prepareKinRecoSF();
    /// Calculate the kinematic reconstruction and return whether at least one solution exists
    bool calculateKinReco(const LV &leptonMinus, const LV &leptonPlus);
    
    /// Prepare JER/JES systematics
    void prepareJER_JES();
    /// Apply JER/JES systematics
    void applyJER_JES();
    
    /// Get 2-dimensional scale factor from histogram
    double get2DSF(TH2* histo, double x, double y);
    
    /// Order two Lorentz vectors by pt
    void orderLVByPt(LV &leading, LV &Nleading, const LV &lv1, const LV &lv2);
    /// Find lepton leading in pt, and next-to-leading lepton
    bool getLeptonPair(size_t& LeadLeptonNumber, size_t& NLeadLeptonNumber);
    /// Clean the jet collection for given cuts on pt, eta
    void cleanJetCollection(double ptcut, double etacut);
    /// Get H_t of jets
    double getJetHT(const VLV& jet, int pt_cut);
    
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
    
    /// Store the object in the output list and return it
    template<class T> T* store(T* obj);
    
    
    
// Private methods
private:
    
    /// Clear all branches
    void clearBranches();
    /// Clear all variables assigned to branches
    void clearBranchVariables();
    
    /// Set addresses of nTuple branches relevant for reconstruction level
    void SetRecoBranchAddresses();
    /// Set addresses of nTuple branches of kinematic reconstruction
    void SetKinRecoBranchAddresses();
    /// Set address of nTuple branch for PDF weights
    void SetPdfBranchAddress();
    /// Set address of nTuple branch for Drell-Yan decay mode
    void SetDyDecayBranchAddress();
    /// Set address of nTuple branch for Top decay mode
    void SetTopDecayBranchAddress();
    /// Set addresses of nTuple branches for Top signal samples on generator level
    void SetTopSignalBranchAddresses();
    /// Set addresses of nTuple branches for Higgs signal samples on generator level
    void SetHiggsSignalBranchAddresses();
    
    /// Methods needed for b-tag scale factor calculation
    double BJetSF(double, double);
    double CJetSF(double, double);
    double LJetSF(double, double, TString);
    double BJetSFAbsErr(double);
    double CJetSFAbsErr(double);
};



/** helper function to store a TObject in the output list
 * 
 * @param obj a pointer to a TObject (or any type inheriting from TObject)
 * @return returns the parameter (and the same type)
 * 
 * This function just adds a histogram to the output list and returns 
 * it in a typesafe way. Used to save some typing.
 */
template<class T>
inline T* AnalysisBase::store(T* obj)
{
    fOutput->Add(obj);
    return obj;
}





#endif
