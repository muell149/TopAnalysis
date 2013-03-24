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
    
// Variables accesing the root-file content (nTuple branches and information stored in TObjStrings and histograms)
protected:    
    
// Variables associated to nTuple branches
    
    /// nTuple branches relevant for reconstruction level
    
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
    
    
    /// nTuple branches of kinematic reconstruction
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
    
    
    /// nTuple branch for PDF weights
    std::vector<double> *weightPDF_;
    
    
    /// nTuple branch for Drell-Yan decay mode
    std::vector<int> *ZDecayMode_;
    #ifndef __CINT__   
    std::function<bool(Long64_t)> checkZDecayMode_;
    #endif
    
    
    /// nTuple branch for Top decay mode
    Int_t topDecayMode_;
    
    
    /// nTuple branches for Top signal samples on generator level
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
    
    
    /// nTuple branches for Higgs signal samples on generator level
    Int_t higgsDecayMode_;
    LV    *GenH_;
    LV    *GenBFromH_;
    LV    *GenAntiBFromH_;
    
    
    
    
    
    
    
    JetCorrectionUncertainty *unc_;
    bool doJesJer_;
    
    // Further variables added from the outside
    TString btagFile_;
    TString channel_;
    int channelPdgIdProduct_;
    TString systematic_;
    TString samplename_;
    bool isTtbarPlusTauSample_;
    bool correctMadgraphBR_;
    TString outputfilename_;
    bool isSignal_;
    bool isHiggsSignal_;
    bool isMC_;
    bool getLeptonPair(size_t& LeadLeptonNumber, size_t& NLeadLeptonNumber);
    bool runViaTau_;
    int pdf_no_;
    int trueDYchannelCut_;
    
    /// Histogram holding the weighted events of the full sample
    TH1* h_weightedEvents;
    
    
    
    
    /// Pileup reweighter
    PUReweighter *pureweighter_;
    
    
    /// Map holding binned control plots
    //binnedControlPlots contains:
    //map of name of differential distribution
    // -> pair( histogram with the binning of the differential distribution,
    //          vector(bin) -> map( control plot name -> TH1*))
    std::map<std::string, std::pair<TH1*, std::vector<std::map<std::string, TH1*> > > > *binnedControlPlots;
    
    
    /// Event counter
    Int_t EventCounter_;
    
    
    
    
    
    
    
// Private member data
private:    
    
    TTree *fChain;   //!pointer to the analyzed TTree or TChain
    
    
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
    
    
    
    
    
protected:
    TH1 *h_ClosureTotalWeight;
    TH1 *h_PDFTotalWeight;
    
    // BEGIN of btag SF stuff
    TH2 *h_bjets, *h_btaggedjets;
    TH2 *h_cjets, *h_ctaggedjets;
    TH2 *h_ljets, *h_ltaggedjets;
    
    //btag calculation
    TH2 *bEff, *cEff, *lEff;
    TH1 *h_PUSF, *h_TrigSF, *h_LepSF, *h_BTagSF, *h_KinRecoSF, *h_EventWeight;

    // END of btag SF stuff
    
    // Trigger and lepton SF
    TH2 *h_TrigSFeta, *h_MuonIDSFpteta, *h_ElectronIDSFpteta;
    
    // Data for b-tag SF
    double btag_ptmedian_, btag_etamedian_;
    
    //Data for other SF
    double weightKinFit_; //this is per channel and does not need to be calculated inside the event loop
    
    // For kinematic reconstruction
    bool kinRecoOnTheFly_;
    
    
    bool doClosureTest_;
#ifndef __CINT__
    std::function<double()> closureFunction_;
#endif
    int closureMaxEvents_;
    
    
public:
    AnalysisBase ( TTree * = 0 ) :
        checkZDecayMode_ {nullptr},
        unc_ {nullptr},
        doJesJer_ {false},
        isHiggsSignal_ {false},
        runViaTau_ {false},
        pdf_no_ {-1},
        pureweighter_ {nullptr},
        kinRecoOnTheFly_ {false},
        doClosureTest_ {false},
        closureFunction_ {nullptr}
        {};
    virtual ~AnalysisBase(){};
    virtual void SlaveBegin(TTree *);
    void SetBTagFile(TString btagFile);
    void SetChannel(TString channel);
    void SetSignal(bool isSignal);
    void SetHiggsSignal(const bool higgsSignal);
    void SetSystematic(TString systematic);
    virtual void SetSamplename(TString samplename, TString systematic_from_file);
    void SetOutputfilename(TString outputfilename);
    void SetMC(bool isMC);
    
    /// Set Drell-Yan decay channel for selection, access decay mode from nTuple branch
    void SetTrueLevelDYChannel(int dy);
    
    void SetWeightedEvents(TH1* weightedEvents);
    void SetRunViaTau(bool runViaTau);
    void SetPUReweighter(PUReweighter *pu);
    void SetPDF(int pdf_no);
    void orderLVByPt(LV &leading, LV &Nleading, const LV &lv1, const LV &lv2);
    virtual void SetClosureTest(TString, double) {};
    virtual void Begin (TTree*);
    virtual void Init (TTree *tree);
    virtual void SlaveTerminate();
    virtual void Terminate();

    
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
    
    
    
protected:
    
    // store the object in the output list and return it
    template<class T> T* store(T* obj);
    
    // Create Nbins control plots for the differential distribution h_differential
    // Use h_control for the control plot name and binning
    void CreateBinnedControlPlots(TH1* h_differential, TH1* h_control, const bool fromHistoList =true);
    // h: differential distribution histogram
    // binvalue: the value of the quantity in the differential distribution histogram
    // the control plot histogram
    // the value for the control plot
    // weight: event weight
    void FillBinnedControlPlot(TH1* h_differential, double binvalue, 
                               TH1 *h_control, double value, double weight);
    
    
    // Method which needs to be overwritable
    virtual bool produceBtagEfficiencies();
    
    
    
    /// Access event entry for nTuple branches relevant for reconstruction level
    void GetRecoBranchesEntry(Long64_t &);
    /// Access event entry for nTuple branches of kinematic reconstruction
    void GetKinRecoBranchesEntry(Long64_t &);
    /// Access event entry for nTuple branch for PDF weights
    Int_t GetPDFEntry(Long64_t entry);
    /// Access event entry for nTuple branch for Top decay mode
    void GetTopDecayModeEntry(Long64_t entry);
    /// Access event entry for nTuple branches for Top signal samples on generator level
    void GetTopSignalBranchesEntry(Long64_t &);
    /// Access event entry for nTuple branches for Higgs signal samples on generator level
    void GetHiggsSignalBranchesEntry(Long64_t &);
    
    
    
    
    
    
    void cleanJetCollection(double ptcut, double etacut);
    bool calculateKinReco(const LV &leptonMinus, const LV &leptonPlus);
    
    double getTriggerSF(const LV& lep1, const LV& lep2);
    double getLeptonIDSF(const LV& lep1, const LV& lep2, int x, int y);
    
    double calculateBtagSF();
    double getJetHT(const VLV& jet, int pt_cut);
    
    const std::string topDecayModeString();
    
    void applyJER_JES();
    
    
    // Methods for trigger and lepton SF
    void prepareTriggerSF();
    void prepareLeptonIDSF();
    double get2DSF(TH2* histo, double x, double y);
    
    // Methods for KinReco SF
    void prepareKinRecoSF();
    
    // Methods for JER,JES
    void prepareJER_JES();
    
    // Methods for b-tag SF
    void prepareBtagSF();
    double BJetSF ( double, double );
    double CJetSF ( double, double );
    double LJetSF ( double , double , TString );
    double BJetSFAbsErr ( double );
    double CJetSFAbsErr ( double );
    
    
    //no idea why this is needed! But Process() isn't called otherwise! Argh!
    virtual int Version() const { return 3; }
    
    ClassDef ( AnalysisBase, 0 );

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
