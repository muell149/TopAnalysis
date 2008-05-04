#include "DataFormats/PatCandidates/interface/Jet.h"
#include "TopAnalysis/TopAnalyzer/interface/JetId.h"
#include "TopAnalysis/TopAnalyzer/interface/JetKinematic.h"
#include "TopAnalysis/TopAnalyzer/interface/JetResolution.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonId.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonKinematic.h"
#include "TopAnalysis/TopAnalyzer/interface/MuonResolution.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "TopAnalysis/TopAnalyzer/interface/ElecId.h"
#include "TopAnalysis/TopAnalyzer/interface/ElecKinematic.h"
#include "TopAnalysis/TopAnalyzer/interface/ElecResolution.h"

#include "TopAnalysis/TopAnalyzer/plugins/ObjectAnalyzer.h"
typedef ObjectAnalyzer<std::vector<pat::Jet>, JetId, JetKinematic, JetResolution> JetAnalyzer;
typedef ObjectAnalyzer<std::vector<pat::Muon>, MuonId, MuonKinematic, MuonResolution> MuonAnalyzer;
typedef ObjectAnalyzer<std::vector<pat::Electron>, ElecId, ElecKinematic, ElecResolution> ElecAnalyzer;

#include "TopAnalysis/TopAnalyzer/plugins/EventShapeAnalyzer.h"
typedef EventShapeAnalyzer<std::vector<pat::Muon> > EventShapeAnalyzerMuon;
typedef EventShapeAnalyzer<std::vector<pat::Electron> > EventShapeAnalyzerElec;

#include "TopAnalysis/TopAnalyzer/plugins/PartonMatchAnalyzer.h"

#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE( JetAnalyzer  );
DEFINE_FWK_MODULE( MuonAnalyzer );
DEFINE_FWK_MODULE( ElecAnalyzer );
DEFINE_FWK_MODULE( PartonMatchAnalyzer );
DEFINE_FWK_MODULE( EventShapeAnalyzerMuon );
DEFINE_FWK_MODULE( EventShapeAnalyzerElec );
