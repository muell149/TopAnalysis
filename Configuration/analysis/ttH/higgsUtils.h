#ifndef higgsUtils_h
#define higgsUtils_h

class TH1;
class TString;

namespace Tools{
    void applyFlatWeight(TH1* hist, const double weight);
    TString stepFragmentByToken(const TString& filename, const TString& token);
    TString extractSelectionStep(const TString& filename);
}





#endif //higgsUtils_h







