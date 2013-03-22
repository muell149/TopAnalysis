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
protected:    
    // Variables for accessing the nTuple branches
    VLV             *leptons_;
    std::vector<int>     *lepPdgId_;
    std::vector<double>  *lepPfIso_;
    std::vector<double>  *lepCombIso_;
    std::vector<double>  *lepDxyVertex0_;
    VLV             *jets_;
    VLV             *jetsForMET_;
    VLV             *associatedGenJet_;
    VLV             *associatedGenJetForMET_;
    std::vector<double>  *jetJERSF_;
    std::vector<double>  *jetForMETJERSF_;
    std::vector<double>  *jetBTagTCHE_;
    std::vector<double>  *jetBTagCSV_;
    std::vector<double>  *jetBTagSSVHE_;
    std::vector<int>     *jetPartonFlavour_;
    //VLV             *genJets;
    LV              *met_;
    UInt_t          runNumber_;
    UInt_t          lumiBlock_;
    UInt_t          eventNumber_;
    UInt_t          triggerBits_;
    Double_t        weightGenerator_;
    std::vector<double>  *weightPDF_;
    Int_t           vertMulti_;
    Int_t           vertMultiTrue_;

    JetCorrectionUncertainty *unc_;
    bool            doJesJer_;
    
#ifndef __CINT__   
    std::function<bool(Long64_t)> checkZDecayMode_;
#endif
    
    LV              *GenWPlus_;
    LV              *GenWMinus_;
    LV              *GenNeutrino_;
    LV              *GenAntiNeutrino_;
    LV              *GenB_;
    LV              *GenAntiB_;
    LV              *GenLepton_;
    LV              *GenAntiLepton_;
    LV              *GenTop_;
    LV              *GenAntiTop_;
    LV              *GenMet_;
    VLV             *allGenJets_;
    std::vector<int>     *BHadJetIndex_;
    std::vector<int>     *AntiBHadJetIndex_;

    VLV             *BHadrons_;
    VLV             *AntiBHadrons_;
    std::vector<bool>    *BHadronFromTopB_;
    std::vector<bool>    *AntiBHadronFromTopB_;
    std::vector<int>     *BHadronVsJet_;
    std::vector<int>     *AntiBHadronVsJet_;

    /*   VLV           *BHadronJet;
    VLV           *AntiBHadronJet;
    */
    VLV             *HypTop_;
    VLV             *HypAntiTop_;
    VLV             *HypLepton_;
    VLV             *HypAntiLepton_;
    VLV             *HypNeutrino_;
    VLV             *HypAntiNeutrino_;
    VLV             *HypBJet_;
    VLV             *HypAntiBJet_;
//     VLV           *HypWPlus;
//     VLV           *HypWMinus;
    std::vector<int>     *HypJet0index_;
    std::vector<int>     *HypJet1index_;
    Int_t           topDecayMode_;
    std::vector<int>     *ZDecayMode_;
    
    Int_t           higgsDecayMode_;
    LV              *GenH_;
    LV              *GenBFromH_;
    LV              *GenAntiBFromH_;
    
    std::vector<double> *JetChargeGlobalPtWeighted_;
    std::vector<double> *JetChargeRelativePtWeighted_;
    
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
    TH1* h_weightedEvents;
    PUReweighter *pureweighter_;
    
    
    //binnedControlPlots contains:
    //map of name of differential distribution
    // -> pair( histogram with the binning of the differential distribution,
    //          vector(bin) -> map( control plot name -> TH1*))
    std::map<std::string, std::pair<TH1*, std::vector<std::map<std::string, TH1*> > > > *binnedControlPlots;
    
    
    // Event counter
    Int_t           EventCounter_;
    
private:    
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain

    // List of branches
    TBranch        *b_lepton;   //!
    TBranch        *b_lepPdgId;   //!
    TBranch        *b_lepPfIso;   //!
    TBranch        *b_lepCombIso;   //!
    TBranch        *b_lepDxyVertex0;
    TBranch        *b_associatedGenJet;   //!
    TBranch        *b_associatedGenJetForMET;
    TBranch        *b_jet;   //!
    TBranch        *b_jetJERSF;   //!
    TBranch        *b_jetForMET;   //!
    TBranch        *b_jetForMETJERSF;   //!
    TBranch        *b_jetBTagTCHE;   //!
    TBranch        *b_jetBTagCSV;   //!
    TBranch        *b_jetBTagSSVHE;   //!
    TBranch        *b_jetPartonFlavour;   //!
    //TBranch        *b_genJet;   //!
    TBranch        *b_met;   //!
    TBranch        *b_runNumber;   //!
    TBranch        *b_lumiBlock;   //!
    TBranch        *b_eventNumber;   //!
    TBranch        *b_triggerBits;   //!
    TBranch        *b_weightGenerator;   //!
    TBranch        *b_weightPDF;
    TBranch        *b_vertMulti;   //!
    TBranch        *b_vertMultiTrue;

    TBranch        *b_GenTop;   //!
    TBranch        *b_GenAntiTop;   //!
    TBranch        *b_GenLepton;   //!
    TBranch        *b_GenAntiLepton;   //!
    TBranch        *b_GenNeutrino;   //!
    TBranch        *b_GenAntiNeutrino;   //!
    TBranch        *b_GenB;   //!
    TBranch        *b_GenAntiB;   //!
    TBranch        *b_GenWPlus;   //!
    TBranch        *b_GenWMinus;   //!
    TBranch        *b_allGenJets;   //!
    TBranch        *b_BHadJetIndex;   //!
    TBranch        *b_AntiBHadJetIndex;   //!
    TBranch        *b_GenMet;

    TBranch        *b_BHadrons;   //!
    TBranch        *b_AntiBHadrons;   //!
    TBranch        *b_BHadronFromTopB;   //!
    TBranch        *b_AntiBHadronFromTopB;   //!
    TBranch        *b_BHadronVsJet;   //!
    TBranch        *b_AntiBHadronVsJet;   //!

    //TBranch        *b_BHadronJet_;   //!
    //TBranch        *b_AntiBHadronJet_;   //!

    TBranch        *b_HypTop;   //!
    TBranch        *b_HypAntiTop;   //!
    TBranch        *b_HypLepton;   //!
    TBranch        *b_HypAntiLepton;   //!
    TBranch        *b_HypNeutrino;   //!
    TBranch        *b_HypAntiNeutrino;   //!
    TBranch        *b_HypB;   //!
    TBranch        *b_HypAntiB;   //!
    TBranch        *b_HypWPlus;   //!
    TBranch        *b_HypWMinus;   //!
    TBranch        *b_HypJet0index;   //!
    TBranch        *b_HypJet1index;   //!
    TBranch        *b_TopDecayMode;   //!
    TBranch        *b_ZDecayMode;
    
    TBranch        *b_HiggsDecayMode;
    TBranch        *b_GenH;
    TBranch        *b_GenBFromH;
    TBranch        *b_GenAntiBFromH;
    
    TBranch        *b_JetChargeGlobalPtWeighted;
    TBranch        *b_JetChargeRelativePtWeighted;
    
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
        unc_ {nullptr}, doJesJer_ {false},
        checkZDecayMode_ {nullptr},
        isHiggsSignal_ {false},
        runViaTau_ {false}, pdf_no_ {-1}, pureweighter_ {nullptr}, kinRecoOnTheFly_ {false},
        doClosureTest_ {false}, closureFunction_ {nullptr}
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

    
protected:
    
    // store the object in the output list and return it
    template<class T> 
    T* store(T* obj);
    
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
    
    
    // Methods which need to be overwritable
    virtual bool produceBtagEfficiencies();
    
    // Other methods which need to be protected
    void GetRecoBranches ( Long64_t & );
    void GetSignalBranches ( Long64_t & );
    void GetHiggsSignalBranches ( Long64_t & );
    
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
    
    Int_t GetTopDecayModeEntry(Long64_t entry);
    Int_t GetPDFEntry(Long64_t entry);
    
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
