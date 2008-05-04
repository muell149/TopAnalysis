#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "TopAnalysis/TopFilter/interface/PtFilter.h"
typedef PtFilter<std::vector<pat::Jet> > JetPtFilter;
typedef PtFilter<std::vector<pat::Muon> > MuonPtFilter;
typedef PtFilter<std::vector<pat::Electron> > ElecPtFilter;

