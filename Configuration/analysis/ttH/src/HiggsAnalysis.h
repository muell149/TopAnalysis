#ifndef HiggsAnalysis_h
#define HiggsAnalysis_h

#include <Rtypes.h>

class TTree;
class TString;

#include "analysisHelpers.h"
#include "analysisStructsFwd.h"
#include "../../diLeptonic/src/AnalysisBase.h"
#include "../../diLeptonic/src/classesFwd.h"

class MvaTreeHandler;
class MvaValidation;
class DijetAnalyzer;
class BasicHistograms;
class EventYieldHistograms;
class DyScalingHistograms;
class Playground;
class RecoObjects;
class CommonGenObjects;
class TopGenObjects;
class HiggsGenObjects;
class KinRecoObjects;
namespace tth{
    class GenLevelWeights;
    class RecoLevelWeights;
    class GenObjectIndices;
    class RecoObjectIndices;
}




/// Class for the analysis step of the Higgs analysis, reading the nTuples
class HiggsAnalysis : public AnalysisBase{

public:

    /// Constructor
    HiggsAnalysis(TTree* =0);

    /// Destructor
    virtual ~HiggsAnalysis();

    /// Methods inherited from AnalysisBase
    virtual void Begin(TTree*);
    virtual void SlaveBegin(TTree*);
    virtual Bool_t Process(Long64_t entry);
    virtual void SlaveTerminate();
    virtual void Terminate();

    /// Class definition
    ClassDef(HiggsAnalysis, 0);
    
    /// Is it a ttH sample inclusive in Higgs decay
    void SetHiggsInclusiveSample(const bool isInclusiveHiggs);
    
    /// Select H->bbbar or H->other decay from ttH sample inclusive in Higgs decay
    void SetHiggsInclusiveSeparation(const bool bbbarDecayFromInclusiveHiggs);
    
    /// Set up production of MVA input
    void SetMvaInputProduction(MvaTreeHandler* mvaTreeHandler);
    
    /// Set up validation of MVA
    void SetMvaValidation(MvaValidation* mvaValidation);
    
    /// Set the pointer to DijetAnalyzer
    void SetDijetAnalyzer(DijetAnalyzer* analyzer);
    
    /// Set event yield histograms
    void SetEventYieldHistograms(EventYieldHistograms* eventYieldHistograms);
    
    /// Set histograms for Drell-Yan scaling
    void SetDyScalingHistograms(DyScalingHistograms* dyScalingHistograms);
    
    /// Set basic histograms
    void SetBasicHistograms(BasicHistograms* basicHistograms);
    
    /// Set playground for histograms
    void SetPlayground(Playground* playground);
    
    /// Bool for separating ttbar+bbar events and ttbar+other events
    void SetRunWithTtbb(const bool runWithTtbb_);
    
    
    
private:
    
    
    /// Select events from Higgs signal samples which need to be removed due to generator selection
    bool failsHiggsGeneratorSelection(const Long64_t&)const;
    
    /// Select events from Top signal that satisfy flavour of the additional jets
    bool failsAdditionalJetFlavourSelection(const Long64_t&)const;
    
    
    
    /// Get indices of generated b jet and anti-b jet for particles with given PDG ID
    /// Returns whether a unique solution is found, and only in this case indices are set unequal to -1
    bool getGenBjetIndices(int& genBjetIndex, int& genAntiBjetIndex,
                           const TopGenObjects& topGenObjects, const int pdgId);
    
    /// Match the two generated input jets to the reco jet collection
    bool matchRecoToGenJets(int& matchedBjetIndex, int& matchedAntiBjetIndex,
                            const std::vector<int>& jetIndices,
                            const VLV& jets,
                            const LV* genBjet, const LV* genAntiBjet);
    
    
    
    /// Return vector of pair of indices for dijet combinations, each pair ordered by jet charge
    tth::IndexPairs chargeOrderedJetPairIndices(const std::vector<int>& jetIndices,
                                                const std::vector<double>& jetCharges);

    
    
    /// Fill all analysers and histograms in one method
    void fillAll(const std::string& selectionStep,
                 const RecoObjects& recoObjects, const CommonGenObjects& commonGenObjects,
                 const TopGenObjects& topGenObjects, const HiggsGenObjects& higgsGenObjects,
                 const KinRecoObjects& kinRecoObjects,
                 const tth::GenObjectIndices& genObjectIndices, const tth::RecoObjectIndices& recoObjectIndices,
                 const tth::GenLevelWeights& genLevelWeights, const tth::RecoLevelWeights& recoLevelWeights,
                 const double& defaultWeight)const;
    
    /// Book all histograms of all analysers for all steps in one method
    void bookAll();
    
    /// Clear all analysers in one method
    void clearAll();
    
    
    
    /// Is it a ttH sample inclusive in Higgs decay
    bool isInclusiveHiggs_;
    
    /// Select H->bbbar or H->other decay from ttH sample inclusive in Higgs decay
    bool bbbarDecayFromInclusiveHiggs_;
    
    /// Select tt+bb or tt+other events
    bool runWithTtbb_;
    
    
    
    /// Class for steering the I/O of MVA input tree, trying to identify the jets coming from (anti)b's from (anti)tops
    MvaTreeHandler* mvaTreeHandler_;
    
    
    
    /// Event yield histograms
    EventYieldHistograms* eventYieldHistograms_;
    
    /// Histograms for Drell-Yan scaling
    DyScalingHistograms* dyScalingHistograms_;
    
    /// Basic histograms
    BasicHistograms* basicHistograms_;
    
    /// MVA validation histograms
    MvaValidation* mvaValidation_;
    
    /// Playground
    Playground* playground_;
    
    /// Class that analyzes dijet pairs from jets that pass selection cuts
    DijetAnalyzer* dijetAnalyzer_;
};





#endif




