#ifndef AnalysisHistograms_h
#define AnalysisHistograms_h

#include <map>

class TString;
class TH1D;
class TSelectorList;

#include "higgsUtils.h"
#include "../../diLeptonic/src/classes.h"





/// Base class for histograms for analysis, useful to handle same set of histograms for different selection steps
class AnalysisHistogramsBase{

public:

    /// Empty constructor
    AnalysisHistogramsBase():selectorList_(0){};

    /// Destructor
    ~AnalysisHistogramsBase(){};

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
        std::map<TString, TH1D*> m_histogram_;
    };

    /// Book all histograms for given selection step (dummy method, override in inherited AnalysisHistograms)
    virtual void bookHistos(const TString& step);

    /// Check whether a given selection step already exists
    bool checkExistence(const TString& step)const;

    /// Store the object in the output list and return it
    template<class T> T* store(T* obj){return Tools::store(obj, selectorList_);}

    /// Pointer for bookkeeping of histograms
    TSelectorList* selectorList_;

    /// The map containing all the step histograms for all selection steps
    std::map<TString, StepHistograms> m_stepHistograms_;

};







/// Class for histograms needed for Drell-Yan reweighting
class DyScalingHistograms : public AnalysisHistogramsBase{

public:

    /// Empty constructor
    DyScalingHistograms():h_loose_(0){}

    /// Destructor
    ~DyScalingHistograms(){}

    /// Fill loose histogram
    void fillLoose(const double& dileptonMass, const double& weight)const;

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






/// Class for basic histograms that are filled simultaneously for any step
class AnalysisBasicHistograms : public AnalysisHistogramsBase{

public:

    /// Empty constructor
    AnalysisBasicHistograms(){}

    /// Destructor
    ~AnalysisBasicHistograms(){}

    /// Fill histograms for the Z veto region, i.e. outside the Z window
    void fill(const VLV* leptons, const int& LeadLeptonId, const int& NLeadLeptonId, const VLV* jets, const std::vector<int>* SelJetIds, const std::vector<double>* bTagOutput, const double& BTagWP, const LV* MEt, const double& weight, const TString& step);



private:

    /// Book all histograms for given selection step
    virtual void bookHistos(const TString& step);

};




#endif // AnalysisHistograms_h







