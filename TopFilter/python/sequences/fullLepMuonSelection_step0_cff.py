import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.MuonAnalyzer_cfi import analyzeMuon
## ------------------------------------------Muon eta  |  Muon pt  | Jets eta  |  Jets pt
flmmMuon00 = analyzeMuon.clone()          ##     -     |     -     |     -     |     -
flmmMuon10 = analyzeMuon.clone()          ##     x     |     -     |     -     |     -
flmmMuon20 = analyzeMuon.clone()          ##     x     |     x     |     -     |     -
flmmMuon21 = analyzeMuon.clone()          ##     x     |     x     |     x     |     -
flmmMuon22 = analyzeMuon.clone()          ##     x     |     x     |     x     |     x

from TopAnalysis.TopAnalyzer.JetAnalyzer_cfi  import analyzeJets
## ------------------------------------------Muon eta  |  Muon pt  | Jets eta  |  Jets pt
flmmJets00 = analyzeJets.clone()          ##     -     |     -     |     -     |     -
flmmJets10 = analyzeJets.clone()          ##     x     |     -     |     -     |     -
flmmJets20 = analyzeJets.clone()          ##     x     |     x     |     -     |     -
flmmJets21 = analyzeJets.clone()          ##     x     |     x     |     x     |     -
flmmJets22 = analyzeJets.clone()          ##     x     |     x     |     x     |     x


## import selection cuts here
from TopAnalysis.TopFilter.filters.ptEventFilters_cff import *
from TopAnalysis.TopFilter.filters.etaEventFilters_cff import *
from TopAnalysis.TopFilter.selections.fullLepMuonSelection_step0_cff import *

flmmFilter10 = filterMuonEta.clone(cuts = fullLepMuonEta)
flmmFilter01 = filterJetsEta.clone(cuts = fullLepJetsEta)
flmmFilter20 = filterMuonPt.clone (cuts = fullLepMuonPt )
flmmFilter02 = filterJetsPt.clone (cuts = fullLepJetsPt )


## selection sequences w/o monitoring
flmmFilterMuon = cms.Sequence(flmmFilter10  *
                              flmmFilter20
                              )

flmmFilterJets = cms.Sequence(flmmFilter01  *
                              flmmFilter02
                              )

flmmFilterFull = cms.Sequence(flmmFilterMuon *
                              flmmFilterJets
                              )

## selection sequences with monitoring
flmmFilterMuonMon = cms.Sequence(flmmMuon00   +
                                 flmmJets00   *
                                 flmmFilter10 *
                                 flmmMuon10   +
                                 flmmJets10   *
                                 flmmFilter20
                                 )

flmmFilterJetsMon = cms.Sequence(flmmMuon20   +
                                 flmmJets20   *
                                 flmmFilter01 *
                                 flmmMuon21   +
                                 flmmJets21   *
                                 flmmFilter02
                                 )

flmmFilterFullMon = cms.Sequence(flmmFilterMuonMon *
                                 flmmFilterJetsMon *
                                 flmmMuon22        +
                                 flmmJets22
                                 )

