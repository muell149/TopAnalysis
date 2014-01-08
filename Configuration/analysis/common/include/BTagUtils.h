#ifndef BTagUtils_h
#define BTagUtils_h

#include <string>
#include <vector>


class TString;
class TSelectorList;

#include "classesFwd.h"
#include "TopAnalysis/ZTopUtils/interface/bTagBase.h"




// FIXME: replace these functions with enum type ones
namespace ttbar{

    /// Access an already existing input folder
    std::string fullFilePath(const std::string& baseDir, const std::string& fileName,
                             const std::string& channel, const TString& systematic,
                             const bool createNonExisting = false, const bool allowNonExisting = true);

    /// Builds the path of the file for a given channel and systematic
    std::string partialFilePath(const std::string& fileName, const std::string& channel, const TString& systematic);
}


class BTagSFGeneric : public ztop::bTagBase{

public:

  /// Constructor
  BTagSFGeneric(const char* btagEfficiencyInputDir,
                const char* btagEfficiencyOutputDir,
                const std::vector<std::string>& channels,
                TString systematic);

  /// Destructor
  ~BTagSFGeneric(){}


  /// Enumeration for possible systematics
  enum Systematic{nominal,
  btag_up, btag_down,
  btagPt_up, btagPt_down,
  btagEta_up, btagEta_down,
  btagLjet_up, btagLjet_down,
  btagLjetPt_up, btagLjetPt_down,
  btagLjetEta_up, btagLjetEta_down,
  btagBeff_up, btagBeff_down,
  btagCeff_up, btagCeff_down,
  btagLeff_up, btagLeff_down};



  /// Whether to produce b-tag efficiencies during Analysis
  /// If efficiencies can be found, they are used in the Analysis, but not produced
  /// If efficiencies cannot be found, they are not used in the Analysis, but produced
  bool makeEfficiencies();



  /// Fill histograms needed for b-tag efficiencies
  void fillBtagHistograms(const std::vector<int>& jetIndices,
                          const std::vector<double>& bTagDiscriminant,
                          const VLV& jets,
                          const std::vector<int>& jetPartonFlavours,
                          const double weight);

  /// Produce b-tag efficiencies
  void produceBtagEfficiencies(const std::string& channel);



  /// Get b-tag per-event scale factor
  double calculateBtagSF(const std::vector<int>& jetIndices,
                         const VLV& jets,
                         const std::vector<int>& jetPartonFlavours);

  /// Method takes the indices of b-tagged jets,
  /// and overwrites them with the b-tagged jets after randomised tag flipping
  void indexOfBtags(std::vector<int>& bjetIndices,
                    const std::vector<int>& jetIndices,
                    const VLV& jets,
                    const std::vector<int>& jetPartonFlavours,
                    const std::vector<double>& btagDiscriminants,
                    const double TagCut,
                    const std::string& channel)const;

  /// Prepare b-tagging scale factors (efficiency histograms)
  void prepareBTags(TSelectorList* output, const std::string& channel);



private:

  /// Input directory for files holding histograms of b-tagging efficiencies
  std::string inputDirName_;

  /// Output directory for files holding histograms, in case b-tagging efficiencies are produced in Analysis
  std::string outputDirName_;

  /// Name of the file with btag histograms
  std::string fileName_;

  /// 'Random' decision to tag or not tag a jet.
  /// Method explained in: https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFUtil
  /// and in: https://twiki.cern.ch/twiki/bin/view/CMS/BTagSFMethods#2a_Jet_by_jet_updating_of_the_b
  bool isTagged(const LV& jet, const double tagValue, const int flavour,
                const double tagCut, const std::string& channel)const;


  /// Check if systematic belongs to a specific category
  bool ljetSystematic()const;
  bool ptUpSystematic()const;
  bool ptDownSystematic()const;
  bool etaUpSystematic()const;
  bool etaDownSystematic()const;
  bool absoluteUpSystematic()const;
  bool absoluteDownSystematic()const;



  /// Whether to produce btag efficiencies or whether to read in already produced ones
  bool makeEfficiencies_;

  /// Systematic to be used for btag efficiencies
  Systematic systematic_;

  /// Pointer for bookkeeping of histograms
  TSelectorList* selectorList_;

};




#endif