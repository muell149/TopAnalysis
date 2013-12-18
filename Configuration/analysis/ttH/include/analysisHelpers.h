#ifndef analysisHelpers_h
#define analysisHelpers_h

#include <string>
#include <vector>





namespace AnalysisMode{
    
    /// Analysis modes for analysis
    enum AnalysisMode{
        cp,         // Basic control plots
        mvaP,       // Produce MVA input
        mvaA,       // Access MVA output
        dijet,      // Dijet analyser
        charge,     // Jet charge analyser
        match,      // Jet matching analyser
        playg,      // Playground
        undefined   // Undefined mode
    };
    
    
    
    /// All analysis modes allowed for analysis
    const std::vector<AnalysisMode> allowedAnalysisModes
        {cp, mvaP, mvaA, dijet, charge, match, playg};
    
    
    
    /// Convert an AnalysisMode from string to typedef
    AnalysisMode convertAnalysisMode(const std::string& analysisMode);
    
    /// Convert an AnalysisMode from typedef to string
    std::string convertAnalysisMode(const AnalysisMode& analysisMode);
    
    /// Convert a vector of AnalysisModes from string to typedef
    std::vector<AnalysisMode> convertAnalysisModes(const std::vector<std::string>& analysisModes);
    
    /// Convert a vector of AnalysisModes from typedef to string
    std::vector<std::string> convertAnalysisModes(const std::vector<AnalysisMode>& analysisModes);
}










#endif // analysisHelpers_h








