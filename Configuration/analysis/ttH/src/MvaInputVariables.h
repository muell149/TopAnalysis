#ifndef MvaInputVariables_h
#define MvaInputVariables_h

#include <vector>
#include <string>
#include <map>

#include <Rtypes.h>

class TSelectorList;
class TH1;
class TH2;
class TString;

#include "mvaStructs.h"
#include "../../diLeptonic/src/storeTemplate.h"





/// Class holding the input variables for MVA,
/// trying to identify the jets coming from (anti)b's from (anti)tops
class MvaInputTopJetsVariables{
    
public:
    
    /// Constructor which can optionally set MVA weights and creating TMVA Reader
    MvaInputTopJetsVariables(const std::vector<TString>& selectionStepsNoCategories);
    
    /// Destructor
    ~MvaInputTopJetsVariables(){};
    
    
    
    
    /// Produce control plots for MVA input in own file with given filename
    void mvaInputVariablesControlPlots(const std::string& f_savename);
    
    /// Produce control plots for MVA input owned by a given selector list
    void mvaInputVariablesControlPlots(TSelectorList* output);
    
    /// Clear the class instance
    void clear();
    
    
    
private:
    
    /// Stuct holding 1-D histograms showing the full distributions and the separation power of variables
    struct PlotStruct{
        PlotStruct():
            h_correctCombination(0), h_swappedCombination(0),
            h_wrongCombinations(0), h_allCombinations(0){};
        TH1* h_correctCombination;
        TH1* h_swappedCombination;
        TH1* h_wrongCombinations;
        TH1* h_allCombinations;
    };
    
    /// Stuct holding 2-D histograms showing the full distributions and the separation power of variables
    struct PlotStruct2D{
        PlotStruct2D():
            h_correctCombination(0), h_swappedCombination(0),
            h_wrongCombinations(0), h_allCombinations(0){};
        TH2* h_correctCombination;
        TH2* h_swappedCombination;
        TH2* h_wrongCombinations;
        TH2* h_allCombinations;
    };
    
    
    
    /// Book histograms to be hold by m_histogram_
    void bookHistograms(const TString& name, const TString& title,
                        const int nBin, const double xMin, const double xMax);
    
    /// Book 2-D histograms to be hold by m_histogram_
    void bookHistograms2D(const TString& name, const TString& title,
                          const int nBinX, const double xMin, const double xMax,
                          const int nBinY, const double yMin, const double yMax);
    
    /// Fill 1-D histograms
    void fillHistograms(const TString& name, const Float_t& variable, const MvaTopJetsVariables& mvaTopJetsVariables);
    
    /// Fill 2-D histograms
    void fillHistograms2D(const TString& name, const double& variable1, const double& variable2, const MvaTopJetsVariables& mvaTopJetsVariables);
    
    /// Store the object in the output list and return it
    template<class T> T* store(T* obj){return ttbar::store(obj, selectorList_);}
    
    
    
    /// Pointer for bookkeeping of histograms, trees, etc.
    TSelectorList* selectorList_;
    
    /// Storage of all entries for the MVA
//    std::vector<Input> v_inputStruct_;
    std::vector<MvaTopJetsVariablesPerEvent> v_mvaTopJetsVariablesPerEvent_;
    
    /// Storage for the 1-D histograms to be filled
    std::map<TString, PlotStruct> m_plotStruct_;
    
    /// Storage for the 2-D histograms to be filled
    std::map<TString, PlotStruct2D> m_plotStruct2D_;
    
    
    
    
    /// Selection steps for which to run the MVA tool
    const std::vector<TString> selectionSteps_;
};







#endif // MvaInputVariables_h







