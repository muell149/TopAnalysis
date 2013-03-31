#ifndef AnalysisHistograms_h
#define AnalysisHistograms_h

#include <map>

#include <TSelectorList.h>

class TString;
class TH1D;




/// Base class for histograms for analysis, useful to handle same set of histograms for different selection steps
class AnalysisHistogramsBase{
    
public:
    
    /// Empty constructor
    AnalysisHistogramsBase():selectorList_(0){};
    
    /// Destructor
    ~AnalysisHistogramsBase(){};
    
    /// Add a new selection step
    void addStep(const TString& step);
    
    
protected:
    
    /// Struct holding the histograms for one selection step
    struct StepHistograms{
        /// Constructor
        StepHistograms(){};
        /// Destructor
        ~StepHistograms(){};
        
        /// The map with all the histograms for one selection step
        std::map<TString, TH1D*> m_histogram_;
    };
    
    /// Book all histograms for given selection step (dummy method, override in specific AnalysisHistograms)
    virtual void bookHistos(const TString& step);
    
    /// Check whether a given selection step already exists
    bool checkExistence(const TString& step);
    
    /// Store the object in the output list and return it
    template<class T> T* store(T* obj);
    
    /// Pointer for bookkeeping of histograms
    TSelectorList* selectorList_;
    
    /// The map containing all the step histograms for all selection steps
    std::map<TString, StepHistograms> m_stepHistograms_;
    
};




template<class T>
inline T* AnalysisHistogramsBase::store(T* obj){
    selectorList_->Add(obj);
    return obj;
}







class DyScalingHistograms : public AnalysisHistogramsBase{
    
public:
    
    /// Empty constructor
    DyScalingHistograms():h_loose_(0){}
    
    /// Constructor initialising the output list
    DyScalingHistograms(TSelectorList* selectorList):h_loose_(0)
    {
        selectorList_ = selectorList;
    }
    
    /// Destructor
    ~DyScalingHistograms(){}
    
    /// Fill loose histogram
    void fillLoose(const double& dileptonMass, const double& weight);
    
    /// Fill histograms inside the Z window
    void fillZWindow(const double& dileptonMass, const double& weight, const TString& step);
    
    /// Fill histograms for the Z veto region, i.e. outside the Z window
    void fillZVeto(const double& dileptonMass, const double& weight, const TString& step);
    
    
    
private:
    
    /// Book all histograms for given selection step
    virtual void bookHistos(const TString& step);
    
    /// Store histogram in output
    TH1D* bookHisto(TH1D* histo, const TString& name);
    
    /// Loose histogram, required only once, thus not part of histograms for specific selection steps
    TH1D* h_loose_;
    
};






#endif // AnalysisHistograms_h







