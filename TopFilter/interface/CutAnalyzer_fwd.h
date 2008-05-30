//filter classes
#include "TopAnalysis/TopFilter/interface/PtFilter.h"
#include "TopAnalysis/TopFilter/interface/EtaFilter.h"
#include "TopAnalysis/TopFilter/interface/JetIsolationFilter.h"
#include "TopAnalysis/TopFilter/interface/CaloIsolationFilter.h"
#include "TopAnalysis/TopFilter/interface/TrackIsolationFilter.h"


#include "TopAnalysis/TopFilter/plugins/EventFilter.h"

//object filter
typedef PtFilter            <std::vector<pat::Jet>   > JetPtFilter;
typedef EtaFilter           <std::vector<pat::Jet>      > JetEtaFilter;
typedef PtFilter            <std::vector<pat::Muon>     > MuonPtFilter;
typedef EtaFilter           <std::vector<pat::Muon>     > MuonEtaFilter;
typedef JetIsolationFilter  <std::vector<pat::Muon>     > MuonJetIsolationFilter;
typedef CaloIsolationFilter <std::vector<pat::Muon>     > MuonCaloIsolationFilter;
typedef TrackIsolationFilter<std::vector<pat::Muon>     > MuonTrackIsolationFilter;
typedef PtFilter            <std::vector<pat::Electron> > ElecPtFilter;
typedef EtaFilter           <std::vector<pat::Electron> > ElecEtaFilter;
typedef JetIsolationFilter  <std::vector<pat::Electron> > ElecJetIsolationFilter;
typedef CaloIsolationFilter <std::vector<pat::Electron> > ElecCaloIsolationFilter;
typedef TrackIsolationFilter<std::vector<pat::Electron> > ElecTrackIsolationFilter;

//event filter
typedef EventFilter<std::vector<pat::Jet>,      JetPtFilter              > JetPtEventFilter;
typedef EventFilter<std::vector<pat::Jet>,      JetEtaFilter             > JetEtaEventFilter;
typedef EventFilter<std::vector<pat::Muon>,     MuonPtFilter             > MuonPtEventFilter;
typedef EventFilter<std::vector<pat::Muon>,     MuonEtaFilter            > MuonEtaEventFilter;
typedef EventFilter<std::vector<pat::Muon>,     MuonJetIsolationFilter   > MuonJetIsolationEventFilter;
typedef EventFilter<std::vector<pat::Muon>,     MuonCaloIsolationFilter  > MuonCaloIsolationEventFilter;
typedef EventFilter<std::vector<pat::Muon>,     MuonTrackIsolationFilter > MuonTrackIsolationEventFilter;
typedef EventFilter<std::vector<pat::Electron>, ElecPtFilter             > ElecPtEventFilter;
typedef EventFilter<std::vector<pat::Electron>, ElecEtaFilter            > ElecEtaEventFilter;
typedef EventFilter<std::vector<pat::Electron>, ElecJetIsolationFilter   > ElecJetIsolationEventFilter;
typedef EventFilter<std::vector<pat::Electron>, ElecCaloIsolationFilter  > ElecCaloIsolationEventFilter;
typedef EventFilter<std::vector<pat::Electron>, ElecTrackIsolationFilter > ElecTrackIsolationEventFilter;
