import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.MuonAnalyzer_cfi import analyzeMuon
## -------------------------------------Muon eta  |  Muon pt  |   Jet eta |  Jet pt   | muon iso  |  muon dist
fullLepMuon00 = analyzeMuon.clone()    ##     -     |     -     |     -     |     -     |     -     |     -
fullLepMuon10 = analyzeMuon.clone()    ##     x     |     -     |     -     |     -     |     -     |     -
fullLepMuon20 = analyzeMuon.clone()    ##     x     |     x     |     -     |     -     |     -     |     -
fullLepMuon01 = analyzeMuon.clone()    ##     -     |     -     |     x     |     -     |     -     |     -
fullLepMuon02 = analyzeMuon.clone()    ##     -     |     -     |     x     |     x     |     -     |     -
fullLepMuon11 = analyzeMuon.clone()    ##     x     |     -     |     x     |     -     |     -     |     -
fullLepMuon12 = analyzeMuon.clone()    ##     x     |     -     |     x     |     x     |     -     |     -
fullLepMuon21 = analyzeMuon.clone()    ##     x     |     x     |     x     |     -     |     -     |     -
fullLepMuon22 = analyzeMuon.clone()    ##     x     |     x     |     x     |     x     |     -     |     -
fullLepMuon32 = analyzeMuon.clone()    ##     x     |     x     |     x     |     x     |     x     |     -
fullLepMuon42 = analyzeMuon.clone()    ##     x     |     x     |     x     |     x     |     x     |     x

## put any extra configuration here:

from TopAnalysis.TopAnalyzer.JetAnalyzer_cfi  import analyzeJets
## -------------------------------------Muon eta  |  Muon pt  | Jets eta  |  Jets pt  | muon iso  |  muon dist
fullLepJets00 = analyzeJets.clone()    ##     -     |     -     |     -     |     -     |     -     |     -
fullLepJets10 = analyzeJets.clone()    ##     x     |     -     |     -     |     -     |     -     |     -
fullLepJets20 = analyzeJets.clone()    ##     x     |     x     |     -     |     -     |     -     |     -
fullLepJets01 = analyzeJets.clone()    ##     -     |     -     |     x     |     -     |     -     |     -
fullLepJets02 = analyzeJets.clone()    ##     -     |     -     |     x     |     x     |     -     |     -
fullLepJets11 = analyzeJets.clone()    ##     x     |     -     |     x     |     -     |     -     |     -
fullLepJets12 = analyzeJets.clone()    ##     x     |     -     |     x     |     x     |     -     |     -
fullLepJets21 = analyzeJets.clone()    ##     x     |     x     |     x     |     -     |     -     |     -
fullLepJets22 = analyzeJets.clone()    ##     x     |     x     |     x     |     x     |     -     |     -
fullLepJets32 = analyzeJets.clone()    ##     x     |     x     |     x     |     x     |     x     |     -
fullLepJets42 = analyzeJets.clone()    ##     x     |     x     |     x     |     x     |     x     |     x

## put any extra configuration here:
fullLepMuon00.input = cms.InputTag("selectedLayer1Muons")
fullLepMuon00.doKin = cms.bool(False)                        # doKin is set to 'false' since this features requires
fullLepMuon10.input = cms.InputTag("selectedLayer1Muons")    # the allLayer1Jets collection which is dropped in the 
fullLepMuon10.doKin = cms.bool(False)                        # PAT tuple. Alternatively you can replace
fullLepMuon20.input = cms.InputTag("selectedLayer1Muons")    # fullLepMuonXY.kin = cms.PSet(
fullLepMuon20.doKin = cms.bool(False)                        #     jets = cms.InputTag("allLayer1Jets")
fullLepMuon01.input = cms.InputTag("selectedLayer1Muons")    # )
fullLepMuon01.doKin = cms.bool(False)                        # but i don't know if this would make sense.
fullLepMuon02.input = cms.InputTag("selectedLayer1Muons")
fullLepMuon02.doKin = cms.bool(False)
fullLepMuon11.input = cms.InputTag("selectedLayer1Muons")
fullLepMuon11.doKin = cms.bool(False)
fullLepMuon12.input = cms.InputTag("selectedLayer1Muons")
fullLepMuon12.doKin = cms.bool(False)
fullLepMuon21.input = cms.InputTag("selectedLayer1Muons")
fullLepMuon21.doKin = cms.bool(False)
fullLepMuon22.input = cms.InputTag("selectedLayer1Muons")
fullLepMuon22.doKin = cms.bool(False)
fullLepMuon32.input = cms.InputTag("selectedLayer1Muons")
fullLepMuon32.doKin = cms.bool(False)
fullLepMuon42.input = cms.InputTag("selectedLayer1Muons")
fullLepMuon42.doKin = cms.bool(False)

fullLepJets00.input = cms.InputTag("selectedLayer1Jets")
fullLepJets10.input = cms.InputTag("selectedLayer1Jets")
fullLepJets20.input = cms.InputTag("selectedLayer1Jets")
fullLepJets01.input = cms.InputTag("selectedLayer1Jets")
fullLepJets02.input = cms.InputTag("selectedLayer1Jets")
fullLepJets11.input = cms.InputTag("selectedLayer1Jets")
fullLepJets12.input = cms.InputTag("selectedLayer1Jets")
fullLepJets21.input = cms.InputTag("selectedLayer1Jets")
fullLepJets22.input = cms.InputTag("selectedLayer1Jets")
fullLepJets32.input = cms.InputTag("selectedLayer1Jets")
fullLepJets42.input = cms.InputTag("selectedLayer1Jets")

## import selection cuts here
from TopAnalysis.TopFilter.selections.fullLepMuonSelection_step1_cff import *

from TopAnalysis.TopFilter.filters.EtaEventFilter_cfi       import filterMuonEta
filterFullLep10 = filterMuonEta.clone()
from TopAnalysis.TopFilter.filters.EtaEventFilter_cfi       import filterJetsEta
filterFullLep01 = filterJetsEta.clone()
from TopAnalysis.TopFilter.filters.PtEventFilter_cfi        import filterMuonPt
filterFullLep20 = filterMuonPt.clone()
from TopAnalysis.TopFilter.filters.PtEventFilter_cfi        import filterJetsPt
filterFullLep02 = filterJetsPt.clone()
from TopAnalysis.TopFilter.filters.IsolationEventFilter_cfi import filterMuonIsolation
filterFullLep30 = filterMuonIsolation.clone()
from TopAnalysis.TopFilter.filters.DistanceEventFilter_cfi  import filterMuonDistance
filterFullLep40 = filterMuonDistance.clone()

## put any extra configuration here:
filterFullLep10.cuts = fullLepMuonEta
filterFullLep01.cuts = fullLepJetsEta
filterFullLep20.cuts = fullLepMuonPt
filterFullLep02.cuts = fullLepJetsPt
filterFullLep30.cuts = fullLepCombIsolation
filterFullLep40.cuts = fullLepMuonJetDistance

## define sequences
makeFullMuonMuonKinematics = cms.Sequence(fullLepMuon00 + fullLepJets00 *
                                          filterFullLep10 *
                                          fullLepMuon10 + fullLepJets10 *
                                          filterFullLep20 *
                                          fullLepMuon20 + fullLepJets20 
                                         )

makeFullMuonJetsKinematics = cms.Sequence(filterFullLep01 *
                                          fullLepMuon21 + fullLepJets21 *
                                          filterFullLep02 *
                                          fullLepMuon22 + fullLepJets22 
                                         )

makeFullMuonMuonIsolation  = cms.Sequence(filterFullLep30 *
                                          fullLepMuon32 + fullLepJets32 *
                                          filterFullLep40 *
                                          fullLepMuon42 + fullLepJets42 
                                         )

selectFullLepMuon = cms.Sequence(makeFullMuonMuonKinematics *
                                 makeFullMuonJetsKinematics * 
                                 makeFullMuonMuonIsolation
                                )



