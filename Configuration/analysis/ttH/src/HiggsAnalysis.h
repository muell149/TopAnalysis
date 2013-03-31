#ifndef HiggsAnalysis_h
#define HiggsAnalysis_h

#include <Rtypes.h>

class TTree;
class TH1;
class TString;

#include "../../diLeptonic/src/AnalysisBase.h"
#include "JetCategories.h"
#include "AnalysisHistograms.h"
#include "MvaInputVariables.h"
#include "analysisHelpers.h"


class HiggsAnalysis : public AnalysisBase{

public:
    
    HiggsAnalysis(TTree* =0);
    virtual ~HiggsAnalysis();
    
    virtual void Begin(TTree*);
    virtual void SlaveBegin(TTree*);
    virtual Bool_t Process(Long64_t entry);
    virtual void SlaveTerminate();
    virtual void Terminate();
    
    ClassDef(HiggsAnalysis, 0);
    
    // need to overwrite since everything starting with "ttbar" would be seen as "ttbarsignalplustau"
    virtual void SetSamplename(TString samplename, TString systematic_from_file="");
    
    /// Is it a ttH sample inclusive in Higgs decay
    void SetHiggsInclusiveSample(const bool isInclusiveHiggs);
    
    /// Select H->bbbar or H->other decay from ttH sample inclusive in Higgs decay
    void SetHiggsInclusiveSeparation(const bool bbbarDecayFromInclusiveHiggs);
    
    /// Whether to produce MVA input information
    void SetAnalysisMode(const AnalysisMode::AnalysisMode& analysisMode);
    
    
private:
    
    /// Get indices of generated b jet and anti-b jet for particles with given PDG ID
    /// Returns whether a unique solution is found, and only in this case indices are set unequal to -1
    bool getGenBJetIndices(int& genBJetIndex, int& genAntiBJetIndex, const int pdgId);
    
    /// Match the two generated input jets to the reco jet collection
    bool matchRecoToGenJets(int& matchedBJetIndex, int&matchedAntiBJetIndex, const LV* genBJet, const LV* genAntiBJet);
    
    /// Fill class holding the input variables for MVA, trying to identify the jets coming from (anti)b's from (anti)tops
    void fillMvaInputTopJetsVariables(const LV& lepton, const LV& antilepton,
                                      const int matchedBJetIndex, const int matchedAntiBJetIndex,
                                      const bool successfulMatching, const double& eventWeight);
    
    
    
    /// Enum for analysis modes
    AnalysisMode::AnalysisMode analysisMode_;
    
    
    
    /// Is it a ttH sample inclusive in Higgs decay
    bool isInclusiveHiggs_;
    
    /// Select H->bbbar or H->other decay from ttH sample inclusive in Higgs decay
    bool bbbarDecayFromInclusiveHiggs_;
    
    
    
    /// Class holding the definition and handling of jet categories (# jets, # b-jets)
    JetCategories jetCategories_overview_;
    JetCategories jetCategories_;
    
    /// Class holding the input variables for MVA, trying to identify the jets coming from (anti)b's from (anti)tops
    MvaInputTopJetsVariables mvaInputTopJetsVariables_;
    
    
    
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
    
    TH1* h_events_step9;
    
    /// Histograms for Drell-Yan scaling
    DyScalingHistograms dyScalingHistograms_;
    
    /// Control plots
    TH1* h_jetPt_step8;
    TH1* h_jetChargeGlobalPtWeighted_step8;
    TH1* h_jetChargeRelativePtWeighted_step8;
    
    
    TH1* h_jetMultiplicity_step7;
    TH1* h_jetMultiplicity_step8;
    
    TH1* h_matchedBjetsFromTop_step8;
};





#endif //HiggsAnalysis_h




