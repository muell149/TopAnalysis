#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "TopAnalysis/TopFilter/interface/PtFilter.h"
typedef PtFilter<std::vector<pat::Jet> > JetPtFilter;
typedef PtFilter<std::vector<pat::Muon> > MuonPtFilter;
typedef PtFilter<std::vector<pat::Electron> > ElecPtFilter;

#include "TopAnalysis/TopFilter/interface/EtaFilter.h"
typedef EtaFilter<std::vector<pat::Jet> > JetEtaFilter;
typedef EtaFilter<std::vector<pat::Muon> > MuonEtaFilter;
typedef EtaFilter<std::vector<pat::Electron> > ElecEtaFilter;

#include "TopAnalysis/TopFilter/plugins/EventFilter.h"
typedef EventFilter<std::vector<pat::Jet>, JetPtFilter > JetPtEvtFilter;
typedef EventFilter<std::vector<pat::Muon>, MuonPtFilter > MuonPtEvtFilter;
typedef EventFilter<std::vector<pat::Electron>, ElecPtFilter > ElecPtEvtFilter;

typedef EventFilter<std::vector<pat::Jet>, JetEtaFilter > JetEtaEvtFilter;
typedef EventFilter<std::vector<pat::Muon>, MuonEtaFilter > MuonEtaEvtFilter;
typedef EventFilter<std::vector<pat::Electron>, ElecEtaFilter > ElecEtaEvtFilter;

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( JetPtEvtFilter   );
DEFINE_FWK_MODULE( MuonPtEvtFilter  );
DEFINE_FWK_MODULE( ElecPtEvtFilter  );
DEFINE_FWK_MODULE( JetEtaEvtFilter  );
DEFINE_FWK_MODULE( MuonEtaEvtFilter );
DEFINE_FWK_MODULE( ElecEtaEvtFilter );
