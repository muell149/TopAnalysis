#ifndef HiggsAnalysis_h
#define HiggsAnalysis_h

#include "TH1.h"

#include "../diLeptonic/Analysis.h"
#include "JetCategories.h"




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
    
    
    //std::map<std::string, std::pair<TH1*, std::vector<std::map<std::string, TH1*> > > >* binnedControlPlots_;
    
    /// Class holding the definition and handling of jet categories (# jets, # b-jets)
    JetCategories jetCategories_;
    
    TH1* h_jetCategories_step0;
    TH1* h_jetCategories_step1;
    TH1* h_jetCategories_step2;
    TH1* h_jetCategories_step3;
    TH1* h_jetCategories_step4;
    TH1* h_jetCategories_step5;
    TH1* h_jetCategories_step6;
    TH1* h_jetCategories_step7;
    TH1* h_jetCategories_step8;
    
    /// Histograms for cutflow tables which are not contained in Analysis.h
    TH1 *h_step0, *h_step1, *h_step2;
    
    // FIXME: remove ___XX after Analysis.h is split from DileptonAnalysis.h
    TH1 *h_jetpT___XX;
    
    
    
    
    
    
};




#endif //HiggsAnalysis_h
