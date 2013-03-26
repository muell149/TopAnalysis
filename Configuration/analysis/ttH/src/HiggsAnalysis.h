#ifndef HiggsAnalysis_h
#define HiggsAnalysis_h

#include <Rtypes.h>

class TTree;
class TH1;
class TString;

#include "../../diLeptonic/src/AnalysisBase.h"
#include "JetCategories.h"
#include "DyScalingHistograms.h"



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
    
private:
    
    /// Is it a ttH sample inclusive in Higgs decay
    bool isInclusiveHiggs_;
    
    /// Select H->bbbar or H->other decay from ttH sample inclusive in Higgs decay
    bool bbbarDecayFromInclusiveHiggs_;
    
    
    /// Class holding the definition and handling of jet categories (# jets, # b-jets)
    JetCategories jetCategories_overview_;
    JetCategories jetCategories_;
    
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
    TH1* h_jetpT_step8;
    TH1* h_jetChargeGlobalPtWeighted_step8;
    TH1* h_jetChargeRelativePtWeighted_step8;
    
    /// Histograms concerning the variables used for finding b-jets from ttbar system with MVA
    TH1* h_meanDeltaPhi_b_met_step8;
    TH1* h_massDiff_recoil_bbbar_step8;
    TH1* h_pt_b_antiLepton_step8;
    TH1* h_pt_antiB_lepton_step8;
    TH1* h_deltaR_b_antiLepton_step8;
    TH1* h_deltaR_antiB_lepton_step8;
    TH1* h_btagDiscriminatorSum_step8;
    TH1* h_deltaPhi_antiBLepton_bAntiLepton_step8;
    TH1* h_massDiff_fullBLepton_bbbar_step8;
    TH1* h_meanMT_b_met_step8;
    TH1* h_massSum_antiBLepton_bAntiLepton_step8;
    TH1* h_massDiff_antiBLepton_bAntiLepton_step8;
    
    
};




#endif //HiggsAnalysis_h
