#ifndef analysisHelpers_h
#define analysisHelpers_h

#include <string>
#include <vector>





namespace AnalysisMode{
    
    /// Draw modes for Higgs samples for analysis
    enum AnalysisMode{cp, mva, undefined};
    
    
    
    /// All draw modes allowed for Higgs samples for analysis
    const std::vector<AnalysisMode> allowedAnalysisModes
        {cp, mva};
    
    
    
    /// Convert a DrawMode from string to typedef
    AnalysisMode convertAnalysisMode(const std::string& analysisMode);
    
    /// Convert a DrawMode from typedef to string
    std::string convertAnalysisMode(const AnalysisMode& analysisMode);
    
    /// Convert a vector of DrawModes from string to typedef
    std::vector<AnalysisMode> convertAnalysisModes(const std::vector<std::string>& analysisModes);
    
    /// Convert a vector of DrawModes from typedef to string
    std::vector<std::string> convertAnalysisModes(const std::vector<AnalysisMode>& analysisModes);
}










#endif // analysisHelpers_h








