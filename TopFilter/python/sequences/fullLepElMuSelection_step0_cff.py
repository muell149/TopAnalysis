import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.ElecAnalyzer_cfi import analyzeElec
## ------------------------------------------ Elec eta  |  Elec pt  | Muon eta  |  Muon pt  | Jets eta  |  Jets pt
flemElec000 = analyzeElec.clone()          ##     -     |     -     |     -     |     -     |     -     |     -
flemElec100 = analyzeElec.clone()          ##     x     |     -     |     -     |     -     |     -     |     -
flemElec200 = analyzeElec.clone()          ##     x     |     x     |     -     |     -     |     -     |     -
flemElec210 = analyzeElec.clone()          ##     x     |     x     |     x     |     -     |     -     |     -
flemElec220 = analyzeElec.clone()          ##     x     |     x     |     x     |     x     |     -     |     -
flemElec221 = analyzeElec.clone()          ##     x     |     x     |     x     |     x     |     x     |     -
flemElec222 = analyzeElec.clone()          ##     x     |     x     |     x     |     x     |     x     |     x

from TopAnalysis.TopAnalyzer.MuonAnalyzer_cfi import analyzeMuon
## ------------------------------------------ Elec eta  |  Elec pt  | Muon eta  |  Muon pt  | Jets eta  |  Jets pt
flemMuon000 = analyzeMuon.clone()          ##     -     |     -     |     -     |     -     |     -     |     -
flemMuon100 = analyzeMuon.clone()          ##     x     |     -     |     -     |     -     |     -     |     -
flemMuon200 = analyzeMuon.clone()          ##     x     |     x     |     -     |     -     |     -     |     -
flemMuon210 = analyzeMuon.clone()          ##     x     |     x     |     x     |     -     |     -     |     -
flemMuon220 = analyzeMuon.clone()          ##     x     |     x     |     x     |     x     |     -     |     -
flemMuon221 = analyzeMuon.clone()          ##     x     |     x     |     x     |     x     |     x     |     -
flemMuon222 = analyzeMuon.clone()          ##     x     |     x     |     x     |     x     |     x     |     x

from TopAnalysis.TopAnalyzer.JetAnalyzer_cfi  import analyzeJets
## ------------------------------------------ Elec eta  |  Elec pt  | Muon eta  |  Muon pt  | Jets eta  |  Jets pt
flemJets000 = analyzeJets.clone()          ##     -     |     -     |     -     |     -     |     -     |     -
flemJets100 = analyzeJets.clone()          ##     x     |     -     |     -     |     -     |     -     |     -
flemJets200 = analyzeJets.clone()          ##     x     |     x     |     -     |     -     |     -     |     -
flemJets210 = analyzeJets.clone()          ##     x     |     x     |     x     |     -     |     -     |     -
flemJets220 = analyzeJets.clone()          ##     x     |     x     |     x     |     x     |     -     |     -
flemJets221 = analyzeJets.clone()          ##     x     |     x     |     x     |     x     |     x     |     -
flemJets222 = analyzeJets.clone()          ##     x     |     x     |     x     |     x     |     x     |     x


## import selection cuts here
from TopAnalysis.TopFilter.filters.ptEventFilters_cff import *
from TopAnalysis.TopFilter.filters.etaEventFilters_cff import *
from TopAnalysis.TopFilter.selections.fullLepElMuSelection_step0_cff import *

flemFilter100 = filterElecEta.clone(cuts = fullLepElecEta)
flemFilter200 = filterElecPt.clone (cuts = fullLepElecPt )
flemFilter010 = filterMuonEta.clone(cuts = fullLepMuonEta)
flemFilter020 = filterMuonPt.clone (cuts = fullLepMuonPt )
flemFilter001 = filterJetsEta.clone(cuts = fullLepJetsEta)
flemFilter002 = filterJetsPt.clone (cuts = fullLepJetsPt )


## selection sequences w/o monitoring
flemFilterElec = cms.Sequence(flemFilter100  *
                              flemFilter200
                              )

flemFilterMuon = cms.Sequence(flemFilter010  *
                              flemFilter020
                              )

flemFilterJets = cms.Sequence(flemFilter001  *
                              flemFilter002
                              )

flemFilterFull = cms.Sequence(flemFilterElec *
                              flemFilterMuon *
                              flemFilterJets                              
                              )

## selection sequences with monitoring
flemFilterElecMon = cms.Sequence(flemElec000   +
                                 flemMuon000   +
                                 flemJets000   *
                                 flemFilter100 *
                                 flemElec100   +
                                 flemMuon100   +
                                 flemJets100   *
                                 flemFilter200
                                 )

flemFilterMuonMon = cms.Sequence(flemElec200   +
                                 flemMuon200   +
                                 flemJets200   *
                                 flemFilter010 *
                                 flemElec210   +
                                 flemMuon210   +
                                 flemJets210   *
                                 flemFilter020
                                 )

flemFilterJetsMon = cms.Sequence(flemElec220   +
                                 flemMuon220   +
                                 flemJets220   *
                                 flemFilter001 *
                                 flemElec221   +
                                 flemMuon221   +
                                 flemJets221   *
                                 flemFilter002
                                 )

flemFilterFullMon = cms.Sequence(flemFilterElecMon *
                                 flemFilterMuonMon *
                                 flemFilterJetsMon *                                 
                                 flemElec222       +
                                 flemMuon222       +
                                 flemJets222
                                 )
