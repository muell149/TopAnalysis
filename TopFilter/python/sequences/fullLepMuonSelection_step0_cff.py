import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.MuonAnalyzer_cfi import analyzeMuon
## -------------------------------------Muon eta  |  Muon pt  | Jets eta  |  Jets pt
fullLepMuon00pre = analyzeMuon.clone()    ##     -     |     -     |     -     |     -
fullLepMuon10pre = analyzeMuon.clone()    ##     x     |     -     |     -     |     -
fullLepMuon20pre = analyzeMuon.clone()    ##     x     |     x     |     -     |     -
fullLepMuon01pre = analyzeMuon.clone()    ##     -     |     -     |     x     |     -
fullLepMuon02pre = analyzeMuon.clone()    ##     -     |     -     |     x     |     x
fullLepMuon11pre = analyzeMuon.clone()    ##     x     |     -     |     x     |     -
fullLepMuon12pre = analyzeMuon.clone()    ##     x     |     -     |     x     |     x
fullLepMuon21pre = analyzeMuon.clone()    ##     x     |     x     |     x     |     -
fullLepMuon22pre = analyzeMuon.clone()    ##     x     |     x     |     x     |     x

## put any extra configuration here:

from TopAnalysis.TopAnalyzer.JetAnalyzer_cfi  import analyzeJets
## -------------------------------------Muon eta  |  Muon pt  | Jets eta  |  Jets pt
fullLepJets00pre = analyzeJets.clone()    ##     -     |     -     |     -     |     -
fullLepJets10pre = analyzeJets.clone()    ##     x     |     -     |     -     |     -
fullLepJets20pre = analyzeJets.clone()    ##     x     |     x     |     -     |     -
fullLepJets01pre = analyzeJets.clone()    ##     -     |     -     |     x     |     -
fullLepJets02pre = analyzeJets.clone()    ##     -     |     -     |     x     |     x
fullLepJets11pre = analyzeJets.clone()    ##     x     |     -     |     x     |     -
fullLepJets12pre = analyzeJets.clone()    ##     x     |     -     |     x     |     x
fullLepJets21pre = analyzeJets.clone()    ##     x     |     x     |     x     |     -
fullLepJets22pre = analyzeJets.clone()    ##     x     |     x     |     x     |     x

## put any extra configuration here:


## import selection cuts here
from TopAnalysis.TopFilter.selections.fullLepMuonSelection_step0_cff import *

from TopAnalysis.TopFilter.filters.EtaEventFilter_cfi import filterMuonEta
prefilterFullLep10 = filterMuonEta.clone()
from TopAnalysis.TopFilter.filters.EtaEventFilter_cfi import filterJetsEta
prefilterFullLep01 = filterJetsEta.clone()
from TopAnalysis.TopFilter.filters.PtEventFilter_cfi  import filterMuonPt
prefilterFullLep20 = filterMuonPt.clone()
from TopAnalysis.TopFilter.filters.PtEventFilter_cfi  import filterJetsPt
prefilterFullLep02 = filterJetsPt.clone()

## put any extra configuration here:
prefilterFullLep10.cuts = fullLepMuonEta
prefilterFullLep01.cuts = fullLepJetsEta
prefilterFullLep20.cuts = fullLepMuonPt
prefilterFullLep02.cuts = fullLepJetsPt

## define sequences
preselectFullLepMuon = cms.Sequence(fullLepMuon00pre + fullLepJets00pre *
                                    prefilterFullLep10 *
                                    fullLepMuon10pre + fullLepJets10pre *
                                    prefilterFullLep20 *
                                    fullLepMuon20pre + fullLepJets20pre *
                                    prefilterFullLep01 *
                                    fullLepMuon21pre + fullLepJets21pre *
                                    prefilterFullLep02 *
                                    fullLepMuon22pre + fullLepJets22pre
                                   )


