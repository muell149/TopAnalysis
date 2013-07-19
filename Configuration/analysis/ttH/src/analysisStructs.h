#ifndef analysisStructs_h
#define analysisStructs_h

#include <string>
#include <vector>





namespace tth{
    
    struct GenLevelWeights{
        GenLevelWeights(const double& weightMadgraphCorrection, const double& weightPileup, const double& weightGenerator,
                        const double& trueLevelWeightNoPileup, const double& trueLevelWeight);
        ~GenLevelWeights(){}
        
        #ifndef __CINT__
        const double& weightMadgraphCorrection_;
        const double& weightPileup_;
        const double& weightGenerator_;
        
        const double& trueLevelWeightNoPileup_;
        const double& trueLevelWeight_;
        #endif
    };
    
    
    
    struct RecoLevelWeights{
        RecoLevelWeights(const double& weightLeptonSF, const double& weightTriggerSF, const double& weightBtagSF,
                         const double& weightNoPileup, double& weight);
        ~RecoLevelWeights(){}
        
        #ifndef __CINT__
        const double& weightLeptonSF_;
        const double& weightTriggerSF_;
        const double& weightBtagSF_;
        
        const double& weightNoPileup_;
        double& weight_;
        #endif
    };
    
    
    
    struct ObjectIndices{
        ObjectIndices(const std::vector<int>& allLeptonIndices,
                      const std::vector<int>& leptonIndices, const std::vector<int>& antiLeptonIndices,
                      const int& leptonIndex, const int& antiLeptonIndex,
                      const int& leadingLeptonIndex, const int& nLeadingLeptonIndex,
                      const int& leptonXIndex, const int& leptonYIndex,
                      const std::vector<int>& jetIndices, const std::vector<int>& bjetIndices);
        ~ObjectIndices(){}
        
        #ifndef __CINT__
        const std::vector<int>& allLeptonIndices_;
        const std::vector<int>& leptonIndices_;
        const std::vector<int>& antiLeptonIndices_;
        const int& leptonIndex_;
        const int& antiLeptonIndex_;
        const int& leadingLeptonIndex_;
        const int& nLeadingLeptonIndex_;
        const int& leptonXIndex_;
        const int& leptonYIndex_;
        
        const std::vector<int>& jetIndices_;
        
        const std::vector<int>& bjetIndices_;
        
        //const std::vector<int>& _;
        //const std::vector<int>& _;
        //const std::vector<int>& _;
        //const std::vector<int>& _;
        #endif
    };
    
}










#endif








