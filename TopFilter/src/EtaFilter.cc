#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "TopAnalysis/TopFilter/interface/EtaFilter.h"
typedef EtaFilter<std::vector<pat::Jet>      > JetEtaFilter;
typedef EtaFilter<std::vector<pat::Muon>     > MuonEtaFilter;
typedef EtaFilter<std::vector<pat::Electron> > ElecEtaFilter;

