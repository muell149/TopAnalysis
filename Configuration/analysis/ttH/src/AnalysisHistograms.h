#ifndef AnalysisHistograms_h
#define AnalysisHistograms_h

#include <map>
#include <vector>

class TString;
class TH1;
class TSelectorList;

#include "../../diLeptonic/src/storeTemplate.h"
#include "../../diLeptonic/src/classesFwd.h"

class RecoObjects;
namespace tth{
    class RecoLevelWeights;
    //class GenLevelWeights;
    class RecoObjectIndices;
}



/// Base class for histograms for analysis, useful to handle same set of histograms for different selection steps
class AnalysisHistogramsBase{

public:

    /// Constructor with setting up selection steps
    AnalysisHistogramsBase(const std::vector<TString>& selectionSteps);

    /// Destructor
    ~AnalysisHistogramsBase(){};
    
    /// Book all histograms for all defined selection steps
    void book(TSelectorList* output);
    
    /// Add a new selection step
    void addStep(const TString& step, TSelectorList* output);

    /// Clear all steps
    void clear();



protected:

    /// Struct holding the histograms for one selection step
    struct StepHistograms{
        /// Constructor
        StepHistograms(){};
        /// Destructor
        ~StepHistograms(){};

        /// The map with all the histograms for one selection step
        std::map<TString, TH1*> m_histogram_;
    };

    /// Book all histograms for given selection step (dummy method, override in inherited AnalysisHistograms)
    virtual void bookHistos(const TString& step);

    /// Check whether a given selection step already exists
    bool checkExistence(const TString& step)const;

    /// Store the object in the output list and return it
    template<class T> T* store(T* obj){return ttbar::store(obj, selectorList_);}

    /// Pointer for bookkeeping of histograms
    TSelectorList* selectorList_;

    /// The map containing all the step histograms for all selection steps
    std::map<TString, StepHistograms> m_stepHistograms_;
    
    /// The vector of all defined selection steps
    const std::vector<TString> selectionSteps_;
};






/// Class for histograms needed for event yields
class EventYieldHistograms : public AnalysisHistogramsBase{
    
public:
    
    /// Constructor
    EventYieldHistograms(const std::vector<TString>& selectionSteps);
    
    /// Destructor
    ~EventYieldHistograms(){}
    
    /// Fill histograms
    void fill(const double& weight, const TString& step);
    
    
    
private:
    
    /// Book all histograms for given selection step
    virtual void bookHistos(const TString& step);
};





/// Class for histograms needed for Drell-Yan reweighting
class DyScalingHistograms : public AnalysisHistogramsBase{

public:

    /// Constructor
    DyScalingHistograms(const std::vector<TString>& selectionSteps, const TString& looseStep);

    /// Destructor
    ~DyScalingHistograms(){}

    /// Fill histograms
    void fill(const RecoObjects& recoObjects, const tth::RecoObjectIndices& recoObjectIndices,
              const double& weight, const TString& step);



private:

    /// Book all histograms for given selection step
    virtual void bookHistos(const TString& step);

    /// Store histogram in output
    TH1* bookHisto(TH1* histo, const TString& name);

    /// The loose selection step used for the estimation of the Drell-Yan background in emu
    const TString& looseStep_;
};






/// Class for basic histograms that are filled simultaneously for any step
class BasicHistograms : public AnalysisHistogramsBase{

public:
    
    /// Constructor
    BasicHistograms(const std::vector<TString>& selectionSteps);

    /// Destructor
    ~BasicHistograms(){}

    /// Fill basic histograms
    void fill(const RecoObjects& recoObjects, const tth::RecoObjectIndices& recoObjectIndices,
              const double& weight, const TString& step);



private:

    /// Book all histograms for given selection step
    virtual void bookHistos(const TString& step);

};




#endif // AnalysisHistograms_h







