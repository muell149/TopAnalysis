#include "TopAnalysis/TopAnalyzer/interface/PUEventWeight.h"

double getPUEventWeight(const edm::Event& evt, const edm::InputTag& tag) {
    edm::Handle<double> weightHandle;
    if (tag.label().empty()) return 1; //no weight
    evt.getByLabel(tag, weightHandle);
    return *weightHandle;
}
