#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "TopAnalysis/TopFilter/interface/CaloIsolationFilter.h"
typedef CaloIsolationFilter<std::vector<pat::Muon>     > MuonCaloIsolationFilter;
typedef CaloIsolationFilter<std::vector<pat::Electron> > ElecCaloIsolationFilter;

