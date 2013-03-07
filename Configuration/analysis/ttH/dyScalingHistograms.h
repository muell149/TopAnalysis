#ifndef dyScalingHistograms_h
#define dyScalingHistograms_h

#include <map>

#include "TH1.h"
#include "TH1D.h"
#include "TString.h"
#include "TSelectorList.h"


class DyScalingHistograms{

public:
    DyScalingHistograms():h_loose_(0), selectorList_(0){};
    DyScalingHistograms(TSelectorList* selectorList):h_loose_(0), selectorList_(selectorList){};
    ~DyScalingHistograms(){};
    
    void addStep(const TString& step);
    void fillLoose(const double& dileptonMass, const double& weight);
    void fillZWindow(const double& dileptonMass, const double& weight, const TString& step);
    void fillZVeto(const double& dileptonMass, const double& weight, const TString& step);
private:
    struct DyStepHistograms{
        DyStepHistograms():h_zWindow_(0), h_zVeto_(0), h_all_(0){};
        ~DyStepHistograms(){};
        
        TH1D* h_zWindow_;
        TH1D* h_zVeto_;
        TH1D* h_all_;
    };
    
    void bookHistos(const TString& step);
    TH1D* bookHisto(TH1D* histo, const TString& name);
    
    bool checkExistence(const TString& step);
    
    // store the object in the output list and return it
    template<class T> T* store(T* obj);
    
    TH1D* h_loose_;
    std::map<TString, DyStepHistograms> m_stepHistograms_;
    
    TSelectorList* selectorList_;
};




template<class T>
inline T* DyScalingHistograms::store(T* obj){
    selectorList_->Add(obj);
    return obj;
}








#endif //dyScalingHistograms_h



