#ifndef HiggsAnalysis_h
#define HiggsAnalysis_h

#include "TH1.h"

#include "../diLeptonic/Analysis.h"
#include "JetCategories.h"
#include "dyScalingHistograms.h"



class HiggsAnalysis : public Analysis
{
public:
    HiggsAnalysis(TTree* =0);
    virtual ~HiggsAnalysis();
    
    // need to overwrite since everything starting with "ttbar" would be seen as "ttbarsignalplustau"
    virtual void SetSamplename(TString samplename, TString systematic_from_file="");
    ClassDef(HiggsAnalysis,0);
    
private:
    
    virtual void SlaveBegin(TTree *);
    virtual Bool_t Process(Long64_t entry);
    
    virtual bool produceBtagEfficiencies();
    
    // FIXME: where to set branches for Higgs generator information stored in nTuples, here or in Analysis.h ?
    
    
    /// Map for the binned control plots
    //std::map<std::string, std::pair<TH1*, std::vector<std::map<std::string, TH1*> > > >* binnedControlPlots_;
    
    
    /// Class holding the definition and handling of jet categories (# jets, # b-jets)
    JetCategories jetCategories_overview_;
    JetCategories jetCategories_;
    
    /// Histograms for the jet categories
    TH1* h_jetCategories_overview_step0;
    TH1* h_jetCategories_overview_step1;
    TH1* h_jetCategories_overview_step2;
    TH1* h_jetCategories_overview_step3;
    TH1* h_jetCategories_overview_step4;
    TH1* h_jetCategories_overview_step5;
    TH1* h_jetCategories_overview_step6;
    TH1* h_jetCategories_overview_step7;
    TH1* h_jetCategories_overview_step8;
    
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
    
    // FIXME: remove ___XX after Analysis.h is split from DileptonAnalysis.h
    TH1 *h_jetpT___XX;
    
    
    
    
    
    
};




#endif //HiggsAnalysis_h
