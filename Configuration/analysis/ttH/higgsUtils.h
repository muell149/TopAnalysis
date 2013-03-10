#ifndef higgsUtils_h
#define higgsUtils_h

class TH1;
class TString;

namespace Tools{
    
    /// Apply a flat (i.e. constant) weight to a histogram
    void applyFlatWeight(TH1* hist, const double weight);
    
    /// Get from a TString the selection step of pattern "step*"
    TString extractSelectionStep(const TString& filename);
    
    /// Helper function to get the fragment containing the selection step (needs to be separated by "_" or ".")
    TString stepFragmentByToken(const TString& filename, const TString& token);
}





#endif //higgsUtils_h







