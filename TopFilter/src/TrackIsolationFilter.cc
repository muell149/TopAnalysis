#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "TopAnalysis/TopFilter/interface/TrackIsolationFilter.h"
typedef TrackIsolationFilter<std::vector<pat::Muon> > MuonTrackIsolationFilter;
typedef TrackIsolationFilter<std::vector<pat::Electron> > ElecTrackIsolationFilter;

