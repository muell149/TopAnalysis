#ifndef MvaWeightsAnalyzer_h
#define MvaWeightsAnalyzer_h

#include <vector>
#include <string>
#include <map>

class TSelectorList;
class TString;
class TH1;

#include "mvaStructs.h"
#include "MvaFactory.h"
#include "../../diLeptonic/src/storeTemplate.h"





/// Class for plotting input variables for MVA,
/// trying to identify the jets coming from (anti)b's from (anti)tops
class MvaWeightsAnalyzer{
    
public:
    
    /// Constructor for selection steps
    MvaWeightsAnalyzer(const std::map<TString, std::vector<MvaTopJetsVariables> >& m_stepMvaVariables,
                       const char* mvaWeightFileDirectory,
                       const std::vector<MvaFactory::MvaSet>& v_mvaSetCorrect,
                       const std::vector<MvaFactory::MvaSet>& v_mvaSetSwapped,
                       const bool separationPowerPlots =false);
    
    /// Destructor
    ~MvaWeightsAnalyzer(){}
    
    
    
    /// Clear the class instance
    void clear();
    
    
    
    /// Plot the variables and write them to the specified folder
    /// If separationPowerPlots==true: plot them exclusively for the cases of correct, swapped and wrong combinations to see separation power
    /// If separationPowerPlots==false: plot them inclusively for data/MC comparisons
    void plotVariables(const std::string& f_savename);
    
    /// Plot the variables and store the histograms in the specified TSelectorList
    /// If separationPowerPlots==true: plot them exclusively for the cases of correct, swapped and wrong combinations to see separation power
    /// If separationPowerPlots==false: plot them inclusively for data/MC comparisons
    void plotVariables(TSelectorList* output);
    
    
    
private:
    
    /// Struct holding the histograms for one selection step
    struct StepHistograms{
        /// Constructor
        StepHistograms(){};
        /// Destructor
        ~StepHistograms(){};

        /// The map with all the histograms for one selection step
        std::map<TString, TH1*> m_histogram_;
    };
    
    
    
    /// Book and fill histograms for given selection step
    void plotStep(const TString& step, const std::vector<MvaTopJetsVariables>& v_mvaTopJetsVariables);
    
    /// Book 1-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void bookHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                            const TString& name, const TString& title,
                            const int& nBinX, const double& xMin, const double& xMax);
    
    /// Book 2-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void bookHistosInclExcl2D(std::map<TString, TH1*>& m_histogram, const TString& prefix, const TString& step,
                              const TString& name, const TString& title,
                              const int& nBinX, const double& xMin, const double& xMax,
                              const int& nBinY, const double& yMin, const double& yMax);
    
    /// Fill 1-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void fillHistosInclExcl(std::map<TString, TH1*>& m_histogram, const TString& name,
                            const double& variable,
                            const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight =1.);
    
    /// Fill 2-D histograms exclusively for correct, swapped and wrong combinations, and inclusively
    void fillHistosInclExcl2D(std::map<TString, TH1*>& m_histogram, const TString& name,
                              const float& variable1, const float& variable2,
                              const MvaTopJetsVariables& mvaTopJetsVariables, const double& weight =1.);
    
    
    
    /// Store the object in the output list and return it
    template<class T> T* store(T* obj){return ttbar::store(obj, selectorList_);}
    
    
    
    /// Pointer for bookkeeping of histograms, trees, etc.
    TSelectorList* selectorList_;
    
    /// The map containing all the vectors of MVA variables for all selection steps
    const std::map<TString, std::vector<MvaTopJetsVariables> >& m_stepMvaVariables_;
    
    /// The map containing all the step histograms for all selection steps
    std::map<TString, StepHistograms> m_stepHistograms_;
    
    /// Whether to produce plots inclusively, or exclusively for correct, swapped and wrong combinations
    const bool plotExclusively_;
    
    
    
    const char* mvaWeightFileDirectory_;
    const std::vector<MvaFactory::MvaSet>& v_mvaSetCorrect_;
    const std::vector<MvaFactory::MvaSet>& v_mvaSetSwapped_;
};







#endif







