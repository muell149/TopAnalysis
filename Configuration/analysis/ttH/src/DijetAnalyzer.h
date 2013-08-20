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
#include "AnalysisHistograms.h"
#include "../../diLeptonic/src/storeTemplate.h"
#include "../../diLeptonic/src/classesFwd.h"

class RecoObjects;
class CommonGenObjects;
class TopGenObjects;
class HiggsGenObjects;
class KinRecoObjects;
namespace tth{
    class RecoObjectIndices;
    class GenObjectIndices;
}


/// Class that analyzes all b-jet pairs from the input jet collection
/// In addition produces other plots about input jets, their origin, other properties
class DijetAnalyzer : public AnalysisHistogramsBase{

public:


    /// Constructor for given jet categories
    DijetAnalyzer(const std::vector<TString>& selectionStepsNoCategories,
                  const std::vector<TString>& stepsForCategories =std::vector<TString>(),
                  const JetCategories* jetCategories =0);

    /// Empty destructor
    ~DijetAnalyzer(){};

    /// Fill all histograms
    void fill(const RecoObjects& recoObjects, const CommonGenObjects& commonGenObjects,
              const TopGenObjects& topGenObjects, const HiggsGenObjects& higgsGenObjects,
              const KinRecoObjects& kinRecoObjects,
              const tth::GenObjectIndices& genObjectIndices, const tth::RecoObjectIndices& recoObjectIndices,
              const double& weight, const TString& stepShort);

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



private:

    /// Book histograms for one categoryId with given id and label
    virtual void bookHistos(const TString& step);
    
    
    
    /// Struct holding the histograms for one jet category
    struct CatHistograms{
        /// Constructor
        CatHistograms(){};
        /// Destructor
        ~CatHistograms(){};

        /// The map with all the histograms for one jet category
        std::map<TString, TH1*> map_histo;
    };

    /// Histograms for all jet categories
    std::vector<CatHistograms> histograms_;

};


#endif // DijetAnalyzer_h