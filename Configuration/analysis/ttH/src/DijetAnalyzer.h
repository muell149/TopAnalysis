#ifndef DijetAnalyzer_h
#define DijetAnalyzer_h

#include <vector>
#include <string>
#include <map>

class TTree;
class TSelectorList;
class TH1;
class TString;

#include "JetCategories.h"
// #include "AnalysisHistograms.h"
#include "../../diLeptonic/src/storeTemplate.h"
#include "../../diLeptonic/src/classesFwd.h"


/// Class that analyzes all b-jet pairs from the input jet collection
/// In addition produces other plots about input jets, their origin, other properties
class DijetAnalyzer {

public:

    /// Struct holding all input variables used in DiJetAnalyzer
    struct Input{
        Input( const VLV& allJets_, const std::vector<int>& jetsId_, const std::vector<int>& bJetsId_,
               const std::vector<double>& allJetsBtagDiscriminant_, const std::vector<int>& topJetsId_, const VLV& genJets_,
               const std::vector<int>& bHadJetIndex_, const std::vector<int>& bHadFlavour_,
               const LV& met_, const LV& lepton_, const LV& antilepton_
             );
        ~Input(){}

        #ifndef __CINT__
        const VLV& allJets;
        const std::vector<int>& jetsId;
        const std::vector<int>& bJetsId;
        const std::vector<double>& allJetsBtagDiscriminant;
        const std::vector<int>& topJetsId;
        const VLV& genJets;
        const std::vector<int>& bHadJetIndex;
        const std::vector<int>& bHadFlavour;
        const LV& met;
        const LV& lepton;
        const LV& antilepton;
        #endif
    };

    /// Empty constructor
    DijetAnalyzer();

    /// Empty destructor
    ~DijetAnalyzer(){};

    /// Setting Jet categories
    void SetJetCategories(const JetCategories& jetCategories);

    /// Setting the output selectorList
    void setOutputSelectorList(TSelectorList* output);

    /// Fill all histograms
    void fill(const Input& input, const double& weight);

    /// Find index of genJet corresponding to the specified reco jet. Returns -1 if not found
    int genJetIdOfRecoJet(const LV& recoJet, const VLV& genJets, const float dR_max=0.3);

    /// Get vector of indices of hadrons that are associted to the given gen jet
    std::vector<int> bHadIdsInGenJet(const int jetId, const std::vector<int>& hadJetIndices);

    /// Get vector of flavours of hadrons that are associted to the given gen jet
    std::vector<int> bHadFlavoursInGenJet(const int jetId, const std::vector<int>& hadJetIndices,
                                          const std::vector<int>& hadFlavours, const bool absFlavour = true);

    /// Analyze jet pairs of given jets for the given b-jets from top. Returns ration of correct pairs to wrong pairs
    float correctPairFraction(const VLV& allJets, const std::vector<int>& jetsId,
                              const std::vector<int>& bJetsId, const std::vector<double>& jetsBtagDiscriminant,
                              const std::vector<int>& topJetsId, const std::vector<int>& higgsJetsId,
                              const double weight, TH1* h_dijetMass, TH1* h_correctJetMultiplicity, const bool fillAllCombinations = true);

    /// Whether index is in the vector of indices
    bool isInVector(const std::vector<int>& idVector, const int id);

    /// Clearing the class instance
    void clear();


private:

    /// Struct holding the histograms for one jet category
    struct CatHistograms{
        /// Constructor
        CatHistograms(){};
        /// Destructor
        ~CatHistograms(){};

        /// The map with all the histograms for one jet category
        std::map<TString, TH1*> map_histo;
    };

    /// Store the object in the output list and return it
    template<class T> T* store(T* obj){return ttbar::store(obj, selectorList_);}

    /// Pointer for bookkeeping of histograms, trees, etc.
    TSelectorList* selectorList_;

    /// Jet categories for which the plots should be filled
    const JetCategories* jetCategories_;

    /// Histograms for all jet categories
    std::vector<CatHistograms> histograms_;

    /// Book all histograms for all jet categories categories
    void bookAllHistos();

    /// Book histograms for one categoryId with given id and label
    virtual void bookHistos(int cat, const TString& label);


};


#endif // DijetAnalyzer_h