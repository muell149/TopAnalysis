import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.MuonAnalyzer_cfi import analyzeMuon
## -------------------------------------Muon eta  |  Muon pt  | Jets eta  |  Jets pt
slmMuon00 = analyzeMuon.clone()      ##     -     |     -     |     -     |     -
slmMuon10 = analyzeMuon.clone()      ##     x     |     -     |     -     |     -
slmMuon20 = analyzeMuon.clone()      ##     x     |     x     |     -     |     -
slmMuon01 = analyzeMuon.clone()      ##     -     |     -     |     x     |     -
slmMuon02 = analyzeMuon.clone()      ##     -     |     -     |     x     |     x
slmMuon11 = analyzeMuon.clone()      ##     x     |     -     |     x     |     -
slmMuon12 = analyzeMuon.clone()      ##     x     |     -     |     x     |     x
slmMuon21 = analyzeMuon.clone()      ##     x     |     x     |     x     |     -
slmMuon22 = analyzeMuon.clone()      ##     x     |     x     |     x     |     x

from TopAnalysis.TopAnalyzer.JetAnalyzer_cfi  import analyzeJets
## -------------------------------------Muon eta  |  Muon pt  | Jets eta  |  Jets pt
slmJets00 = analyzeJets.clone()      ##     -     |     -     |     -     |     -
slmJets10 = analyzeJets.clone()      ##     x     |     -     |     -     |     -
slmJets20 = analyzeJets.clone()      ##     x     |     x     |     -     |     -
slmJets01 = analyzeJets.clone()      ##     -     |     -     |     x     |     -
slmJets02 = analyzeJets.clone()      ##     -     |     -     |     x     |     x
slmJets11 = analyzeJets.clone()      ##     x     |     -     |     x     |     -
slmJets12 = analyzeJets.clone()      ##     x     |     -     |     x     |     x
slmJets21 = analyzeJets.clone()      ##     x     |     x     |     x     |     -
slmJets22 = analyzeJets.clone()      ##     x     |     x     |     x     |     x


## import filters & selection cuts here
from TopAnalysis.TopFilter.filters.ptEventFilters_cff import *
from TopAnalysis.TopFilter.filters.etaEventFilters_cff import *
from TopAnalysis.TopFilter.selections.semiLepMuonSelection_step0_cff import *

slmFilter10 = filterMuonEta.clone(cuts = semiLepMuonEta)
slmFilter20 = filterMuonPt.clone (cuts = semiLepMuonPt )
slmFilter01 = filterJetsEta.clone(cuts = semiLepJetsEta)
slmFilter02 = filterJetsPt.clone (cuts = semiLepJetsPt )


## selection sequences w/o monitoring
slmFilterMuon = cms.Sequence(slmFilter10   *
                             slmFilter20
                             )

slmFilterJets = cms.Sequence(slmFilter01   *
                             slmFilter02
                             )

slmFilterFull = cms.Sequence(slmFilterMuon *
                             slmFilterJets
                             )

## selection sequences with monitoring
slmFilterMuonMon = cms.Sequence(slmMuon00     +
                                slmJets00     *
                                slmFilter10   *
                                slmMuon10     +
                                slmJets10     *
                                slmFilter20
                                )

slmFilterJetsMon = cms.Sequence(slmMuon20     +
                                slmJets20     *
                                slmFilter01   *
                                slmMuon21     +
                                slmJets21     *
                                slmFilter02
                                )

slmFilterFullMon = cms.Sequence(slmFilterMuonMon *
                                slmFilterJetsMon *
                                slmMuon22        +
                                slmJets22
                                )
