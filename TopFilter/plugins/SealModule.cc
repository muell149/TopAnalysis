#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "TopAnalysis/TopFilter/interface/PtFilter.h"
#include "TopAnalysis/TopFilter/interface/EtaFilter.h"
#include "TopAnalysis/TopFilter/interface/JetIsolationFilter.h"
#include "TopAnalysis/TopFilter/interface/CaloIsolationFilter.h"
#include "TopAnalysis/TopFilter/interface/TrackIsolationFilter.h"

// object filter expansions
typedef PtFilter            <std::vector<reco::CaloJet> > CaloJetPtFilter;
typedef EtaFilter           <std::vector<reco::CaloJet> > CaloJetEtaFilter;
typedef PtFilter            <std::vector<pat::Jet>      > JetPtFilter;
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

#include "TopAnalysis/TopFilter/plugins/EventFilter.h"

// event filter expansions
typedef EventFilter<std::vector<reco::CaloJet>, CaloJetPtFilter          > JetPtEventPreFilter;
typedef EventFilter<std::vector<reco::CaloJet>, CaloJetEtaFilter         > JetEtaEventPreFilter;
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

#include "TopAnalysis/TopFilter/plugins/SemiLepNMinusOneFilter.h"

// n-1 filter expansions
typedef SemiLepNMinusOneFilter<std::vector<pat::Muon>, std::vector<pat::Jet> > SemiLepMuonNMinusOneFilter;


// plugin definition
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( JetPtEventPreFilter           );
DEFINE_FWK_MODULE( JetEtaEventPreFilter          );
DEFINE_FWK_MODULE( JetPtEventFilter              );
DEFINE_FWK_MODULE( JetEtaEventFilter             );
DEFINE_FWK_MODULE( MuonPtEventFilter             );
DEFINE_FWK_MODULE( MuonEtaEventFilter            );
DEFINE_FWK_MODULE( MuonJetIsolationEventFilter   );
DEFINE_FWK_MODULE( MuonCaloIsolationEventFilter  );
DEFINE_FWK_MODULE( MuonTrackIsolationEventFilter );
DEFINE_FWK_MODULE( ElecPtEventFilter             );
DEFINE_FWK_MODULE( ElecEtaEventFilter            );
DEFINE_FWK_MODULE( ElecJetIsolationEventFilter   );
DEFINE_FWK_MODULE( ElecCaloIsolationEventFilter  );
DEFINE_FWK_MODULE( ElecTrackIsolationEventFilter );
DEFINE_FWK_MODULE( SemiLepMuonNMinusOneFilter    );
