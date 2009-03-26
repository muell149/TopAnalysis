import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.MuonAnalyzer_cfi import analyzeMuon
## ------------------------------------------Muon eta  |  Muon pt  | Jets eta  |  Jets pt
fullLepMuonMuon00pre = analyzeMuon.clone()    ##     -     |     -     |     -     |     -
fullLepMuonMuon10pre = analyzeMuon.clone()    ##     x     |     -     |     -     |     -
fullLepMuonMuon20pre = analyzeMuon.clone()    ##     x     |     x     |     -     |     -
fullLepMuonMuon21pre = analyzeMuon.clone()    ##     x     |     x     |     x     |     -
fullLepMuonMuon22pre = analyzeMuon.clone()    ##     x     |     x     |     x     |     x

## put any extra configuration here:

from TopAnalysis.TopAnalyzer.JetAnalyzer_cfi  import analyzeJets
## ------------------------------------------Muon eta  |  Muon pt  | Jets eta  |  Jets pt
fullLepMuonJets00pre = analyzeJets.clone()    ##     -     |     -     |     -     |     -
fullLepMuonJets10pre = analyzeJets.clone()    ##     x     |     -     |     -     |     -
fullLepMuonJets20pre = analyzeJets.clone()    ##     x     |     x     |     -     |     -
fullLepMuonJets21pre = analyzeJets.clone()    ##     x     |     x     |     x     |     -
fullLepMuonJets22pre = analyzeJets.clone()    ##     x     |     x     |     x     |     x

## put any extra configuration here:

## import selection cuts here
from TopAnalysis.TopFilter.selections.fullLepMuonSelection_step0_cff import *

from TopAnalysis.TopFilter.filters.EtaEventFilter_cfi import filterMuonEta
prefilterFullLepMuon10 = filterMuonEta.clone()
from TopAnalysis.TopFilter.filters.EtaEventFilter_cfi import filterJetsEta
prefilterFullLepMuon01 = filterJetsEta.clone()
from TopAnalysis.TopFilter.filters.PtEventFilter_cfi  import filterMuonPt
prefilterFullLepMuon20 = filterMuonPt.clone()
from TopAnalysis.TopFilter.filters.PtEventFilter_cfi  import filterJetsPt
prefilterFullLepMuon02 = filterJetsPt.clone()

## put any extra configuration here:
prefilterFullLepMuon10.cuts = fullLepMuonEta
prefilterFullLepMuon01.cuts = fullLepJetsEta
prefilterFullLepMuon20.cuts = fullLepMuonPt
prefilterFullLepMuon02.cuts = fullLepJetsPt

## define sequences
preselectFullLepMuon = cms.Sequence(fullLepMuonMuon00pre + fullLepMuonJets00pre *
                                    prefilterFullLepMuon10 *
                                    fullLepMuonMuon10pre + fullLepMuonJets10pre *
                                    prefilterFullLepMuon20 *
                                    fullLepMuonMuon20pre + fullLepMuonJets20pre #* # no Jet selection
                                    #prefilterFullLepMuon01 *
                                    #fullLepMuonMuon21pre + fullLepMuonJets21pre *
                                    #prefilterFullLepMuon02 *
                                    #fullLepMuonMuon22pre + fullLepMuonJets22pre
                                   )


