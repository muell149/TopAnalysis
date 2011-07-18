#include "TopAnalysis/TopAnalyzer/interface/PUEventWeight.h"

/// return the PU event weight for the MC events;
/// return 1 for data, raise exception if weight does not exist in MC
double getPUEventWeight(const edm::Event& evt, const edm::InputTag& tag) {
    if (evt.isRealData()) return 1;
    edm::Handle<double> weightHandle;
    if (tag.label().empty()) return 1; //no weight
    evt.getByLabel(tag, weightHandle);
    // if (weightHandle.failedToGet()) return 1; //no weight
    return *weightHandle;
}
