#ifndef HiggsAnalysis_h
#define HiggsAnalysis_h

#include <utility>

#include <Rtypes.h>

class TTree;
class TH1;
class TString;
class TProfile;

#include "AnalysisHistograms.h"
#include "MvaInputVariables.h"
#include "analysisHelpers.h"
#include "../../diLeptonic/src/AnalysisBase.h"
#include "../../diLeptonic/src/classesFwd.h"

class JetCategories;
class DijetAnalyzer;





/// Class for the analysis step of the Higgs analysis, reading the nTuples
class HiggsAnalysis : public AnalysisBase{

public:

    /// Constructor
    HiggsAnalysis(TTree* =0);

    /// Destructor
    virtual ~HiggsAnalysis();

    /// Methods inherited from AnalysisBase
    virtual void Begin(TTree*);
    virtual void SlaveBegin(TTree*);
    virtual Bool_t Process(Long64_t entry);
    virtual void SlaveTerminate();
    virtual void Terminate();

    /// Class definition
    ClassDef(HiggsAnalysis, 0);

    /// Is it a ttH sample inclusive in Higgs decay
    void SetHiggsInclusiveSample(const bool isInclusiveHiggs);

    /// Select H->bbbar or H->other decay from ttH sample inclusive in Higgs decay
    void SetHiggsInclusiveSeparation(const bool bbbarDecayFromInclusiveHiggs);

    /// Whether to produce MVA input information
    void SetAnalysisMode(const AnalysisMode::AnalysisMode& analysisMode);

    /// Set up the jet categories (# jets, # b-jets) for overview
    void SetJetCategoriesOverview(const JetCategories& jetCategories);

    /// Set up the jet categories (# jets, # b-jets) for analysis
    void SetJetCategoriesAnalysis(const JetCategories& jetCategories);

    /// Set up the MVA weights input for correct jet combinations of ttbar system
    void SetMvaWeightsCorrect(MvaInputTopJetsVariables& mvaInputTopJetsVariables);
    
    /// Set up the MVA weights input for swapped jet combinations of ttbar system
    void SetMvaWeightsSwapped(MvaInputTopJetsVariables& mvaInputTopJetsVariables);

    /// Set the pointer to DijetAnalyzer
    void SetDijetAnalyzer(DijetAnalyzer* analyzer);

    /// Bool for separating ttbar+bbar events and ttbar+other events
    void SetRunWithTtbb(const bool runWithTtbb_);



private:

    /// Typedef for simple treatment of pair of indices of a vector
    typedef std::vector<std::pair<int, int> > IndexPairs;


    /// Select events from Higgs signal samples which need to be removed due to generator selection
    bool failsHiggsGeneratorSelection(Long64_t&);

    /// Select events from Top signal that satisfy flavour of the additional jets
    bool failsAdditionalJetFlavourSelection(const Long64_t&)const;



    /// Get indices of generated b jet and anti-b jet for particles with given PDG ID
    /// Returns whether a unique solution is found, and only in this case indices are set unequal to -1
    bool getGenBJetIndices(int& genBjetIndex, int& genAntiBjetIndex, const int pdgId);

    /// Match the two generated input jets to the reco jet collection
    bool matchRecoToGenJets(int& matchedBjetIndex, int& matchedAntiBjetIndex,
                            const std::vector<int>& jetIndices,
                            const LV* genBjet, const LV* genAntiBjet);

    /// Fill class holding the input variables for MVA, trying to identify the jets coming from (anti)b's from (anti)tops
    std::vector<MvaInputTopJetsVariables::Input> fillMvaInputTopJetsVariables(
                                      const int leptonIndex, const int antiLeptonIndex,
                                      const IndexPairs& jetIndexPairs, const VLV& jetRecoils,
                                      const int matchedBjetIndex, const int matchedAntiBjetIndex,
                                      const LV& met,
                                      const bool successfulMatching, const double& eventWeight)const;



    /// Enum for analysis modes
    AnalysisMode::AnalysisMode analysisMode_;



    /// Is it a ttH sample inclusive in Higgs decay
    bool isInclusiveHiggs_;

    /// Select H->bbbar or H->other decay from ttH sample inclusive in Higgs decay
    bool bbbarDecayFromInclusiveHiggs_;

    /// Select tt+bb or tt+other events
    bool runWithTtbb_;



    /// Class holding the definition and handling of jet categories (# jets, # b-jets) for overview
    const JetCategories* jetCategories_overview_;

    /// Class holding the definition and handling of jet categories (# jets, # b-jets) for analysis
    const JetCategories* jetCategories_;

    /// Class holding the input variables for MVA, trying to identify the jets coming from (anti)b's from (anti)tops
    MvaInputTopJetsVariables mvaInputTopJetsVariables_;

    /// Class holding the weights as calculated by MVA for correct combinations
    MvaInputTopJetsVariables* mvaWeightsCorrect_;
    
    /// Class holding the weights as calculated by MVA for swapped combinations
    MvaInputTopJetsVariables* mvaWeightsSwapped_;

    /// Class that analyzes dijet pairs from jets that pass selection cuts
    DijetAnalyzer* dijetAnalyzer_;



    ///
    IndexPairs chargeOrderedJetPairIndices(const std::vector<int>& jetIndices,
                                           const std::vector<double>& jetCharges);

    /// Calculate the jet recoil for a given jet pair, i.e. vector sum of all jets except selected jet pair
    VLV recoilForJetPairs(const IndexPairs& jetIndexPairs,
                          const std::vector<int>& jetIndices,
                          const VLV& jets);



    /// Histograms for the overview jet categories
    TH1* h_jetCategories_overview_step0;
    TH1* h_jetCategories_overview_step1;
    TH1* h_jetCategories_overview_step2;
    TH1* h_jetCategories_overview_step3;
    TH1* h_jetCategories_overview_step4;
    TH1* h_jetCategories_overview_step5;
    TH1* h_jetCategories_overview_step6;
    TH1* h_jetCategories_overview_step7;
    TH1* h_jetCategories_overview_step8;

    /// Histograms for the analysis jet categories
    TH1* h_jetCategories_step8;

    /// Histograms for cutflow tables which are not contained in Analysis.h
    TH1* h_events_step0a;
    TH1* h_events_step0b;
    TH1* h_events_step1;
    TH1* h_events_step2;
    TH1* h_events_step3;
    TH1* h_events_step4;
    TH1* h_events_step5;
    TH1* h_events_step6;
    TH1* h_events_step7;
    TH1* h_events_step8;

    /// Histograms for Drell-Yan scaling
    DyScalingHistograms dyScalingHistograms_;

    /// Basic histograms
    BasicHistograms basicHistograms_;

    /// Control plots
    TH1* h_jetPt_step8;
    TH1* h_jetChargeGlobalPtWeighted_step8;
    TH1* h_jetChargeRelativePtWeighted_step8;


    TH1* h_matchedBjetsFromTop_step8;
    TH1* h_matchedBjetsFromHiggs_step8;

    TH1* h_mvaBasedJetsFromTop_step8;
    TH1* h_mvaBasedJetsFromHiggs_step8;

    TH1* h_dijetMass_step8;
    TH1* h_mvaBasedDijetMass_step8;

    TProfile* p_dijetMassVsJetCategories;
    TProfile* p_dijetMassVsMvaWeightHigh;
    TProfile* p_dijetMassVsMvaWeightDiff;

    TProfile* p_mvaBasedDijetMassVsJetCategories;
    TProfile* p_mvaBasedDijetMassVsMvaWeightHigh;
    TProfile* p_mvaBasedDijetMassVsMvaWeightDiff;
};





#endif //HiggsAnalysis_h




