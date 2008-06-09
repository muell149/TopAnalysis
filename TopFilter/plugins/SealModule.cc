#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

// object filter expansions
#include "TopAnalysis/TopFilter/interface/PtFilter.h"
#include "TopAnalysis/TopFilter/interface/EtaFilter.h"
#include "TopAnalysis/TopFilter/interface/JetIsolationFilter.h"
#include "TopAnalysis/TopFilter/interface/CaloIsolationFilter.h"
#include "TopAnalysis/TopFilter/interface/TrackIsolationFilter.h"

typedef PtFilter            <std::vector<reco::CaloJet> > JetsPtFilterPre;
typedef EtaFilter           <std::vector<reco::CaloJet> > JetsEtaFilterPre;
typedef PtFilter            <std::vector<reco::Muon>    > MuonPtFilterPre;
typedef EtaFilter           <std::vector<reco::Muon>    > MuonEtaFilterPre;
typedef PtFilter            <std::vector<pat::Jet>      > JetsPtFilter;
typedef EtaFilter           <std::vector<pat::Jet>      > JetsEtaFilter;
typedef PtFilter            <std::vector<pat::Muon>     > MuonPtFilter;
typedef EtaFilter           <std::vector<pat::Muon>     > MuonEtaFilter;
typedef JetIsolationFilter  <std::vector<pat::Muon>     > MuonJetIsoFilter;
typedef CaloIsolationFilter <std::vector<pat::Muon>     > MuonCalIsoFilter;
typedef TrackIsolationFilter<std::vector<pat::Muon>     > MuonTrkIsoFilter;
typedef PtFilter            <std::vector<pat::Electron> > ElecPtFilter;
typedef EtaFilter           <std::vector<pat::Electron> > ElecEtaFilter;
typedef JetIsolationFilter  <std::vector<pat::Electron> > ElecJetIsoFilter;
typedef CaloIsolationFilter <std::vector<pat::Electron> > ElecCalIsoFilter;
typedef TrackIsolationFilter<std::vector<pat::Electron> > ElecTrkIsoFilter;

// event filter expansions
#include "TopAnalysis/TopFilter/plugins/EventFilter.h"

typedef EventFilter<std::vector<pat::Jet>,      JetsPtFilter     > JetsPtEvtFilter;
typedef EventFilter<std::vector<pat::Jet>,      JetsEtaFilter    > JetsEtaEvtFilter;
typedef EventFilter<std::vector<pat::Muon>,     MuonPtFilter     > MuonPtEvtFilter;
typedef EventFilter<std::vector<pat::Muon>,     MuonEtaFilter    > MuonEtaEvtFilter;
typedef EventFilter<std::vector<pat::Muon>,     MuonJetIsoFilter > MuonJetIsoEvtFilter;
typedef EventFilter<std::vector<pat::Muon>,     MuonCalIsoFilter > MuonCalIsoEvtFilter;
typedef EventFilter<std::vector<pat::Muon>,     MuonTrkIsoFilter > MuonTrkIsoEvtFilter;
typedef EventFilter<std::vector<pat::Electron>, ElecPtFilter     > ElecPtEvtFilter;
typedef EventFilter<std::vector<pat::Electron>, ElecEtaFilter    > ElecEtaEvtFilter;
typedef EventFilter<std::vector<pat::Electron>, ElecJetIsoFilter > ElecJetIsoEvtFilter;
typedef EventFilter<std::vector<pat::Electron>, ElecCalIsoFilter > ElecCalIsoEvtFilter;
typedef EventFilter<std::vector<pat::Electron>, ElecTrkIsoFilter > ElecTrkIsoEvtFilter;
typedef EventFilter<std::vector<reco::CaloJet>, JetsPtFilterPre  > JetsPtPreFilter;
typedef EventFilter<std::vector<reco::CaloJet>, JetsEtaFilterPre > JetsEtaPreFilter;
typedef EventFilter<std::vector<reco::Muon>,    MuonPtFilterPre  > MuonPtPreFilter;
typedef EventFilter<std::vector<reco::Muon>,    MuonEtaFilterPre > MuonEtaPreFilter;

// n-1 filter expansions
#include "TopAnalysis/TopFilter/plugins/SemiLepFilter.h"

typedef SemiLepFilter<std::vector<pat::Muon>, std::vector<pat::Jet> > SemiLepMuonFilter;


// plugin definition
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( JetsPtPreFilter     );
DEFINE_FWK_MODULE( JetsEtaPreFilter    );
DEFINE_FWK_MODULE( MuonPtPreFilter     );
DEFINE_FWK_MODULE( MuonEtaPreFilter    );
DEFINE_FWK_MODULE( JetsPtEvtFilter     );
DEFINE_FWK_MODULE( JetsEtaEvtFilter    );
DEFINE_FWK_MODULE( MuonPtEvtFilter     );
DEFINE_FWK_MODULE( MuonEtaEvtFilter    );
DEFINE_FWK_MODULE( MuonJetIsoEvtFilter );
DEFINE_FWK_MODULE( MuonCalIsoEvtFilter );
DEFINE_FWK_MODULE( MuonTrkIsoEvtFilter );
DEFINE_FWK_MODULE( ElecPtEvtFilter     );
DEFINE_FWK_MODULE( ElecEtaEvtFilter    );
DEFINE_FWK_MODULE( ElecJetIsoEvtFilter );
DEFINE_FWK_MODULE( ElecCalIsoEvtFilter );
DEFINE_FWK_MODULE( ElecTrkIsoEvtFilter );
DEFINE_FWK_MODULE( SemiLepMuonFilter   );
