#include "DataFormats/PatCandidates/interface/Muon.h"

// quality filter expansion for muons (could later be extended for electrons
#include "TopAnalysis/TopFilter/interface/QualityFilter.h"

typedef QualityFilter   <std::vector<pat::Muon>     > MuonQualityFilter;

