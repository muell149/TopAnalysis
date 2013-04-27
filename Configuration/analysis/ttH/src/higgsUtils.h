#ifndef tth_utils_h
#define tth_utils_h

class TString;





namespace tth{
    
    /// Get from a TString the selection step of pattern "step*"
    TString extractSelectionStep(const TString& name);
    
    /// Get from a TString the category bin of pattern "bin_*", relevant in case of binned control plots usage
    TString extractCategoryBin(const TString& name);
    
    /// Get from a TString the selection step of pattern "step*", combined with the category of pattern "bin_*",
    /// as it might be needed in case of binned control plots usage
    TString extractSelectionStepAndCategoryBin(const TString& name);
    
    /// Helper functions only needed by functions defined in this file
    namespace helper{
        
        /// Helper function to get the fragment containing the selection step
        /// (needs to be separated by given token)
        TString stepFragmentByToken(const TString& nameFragment, const TString& token);
        
        /// Helper function to get the fragment containing the bin number in case of binned control plots usage
        /// (needs to be separated by given token)
        TString binFragmentByToken(const TString& nameFragment, const TString& token);
    }
}





#endif




