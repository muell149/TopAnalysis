import FWCore.ParameterSet.Config as cms

## configure JetEnergyScale
from TopAnalysis.TopUtils.JetEnergyScale_cfi import *
scaledJetEnergy.scaleFactor = 1.0

## pat sequences
from PhysicsTools.PatAlgos.patSequences_cff import *

## clone selectedLayer1Jets with lowered pt threshold for analysis
selectedLayer1JetsLowPt     = selectedLayer1Jets.clone()
selectedLayer1JetsLowPt.src = "scaledJetEnergy:allLayer1Jets"
selectedLayer1JetsLowPt.cut = 'pt > 20. & abs(eta) < 2.4 & nConstituents > 0 & emEnergyFraction < 0.9'

## jets for event selection
selectedLayer1Jets.src = "scaledJetEnergy:allLayer1Jets"
selectedLayer1Jets.cut = 'pt > 30. & abs(eta) < 2.4 & nConstituents > 0 & emEnergyFraction < 0.9'
countLayer1Jets.minNumber = 4

## use recalculated MET after scaling of jet energy
# FIXME !!!

## filter events with overlapping jets
from TopAnalysis.TopFilter.filters.JetOverlapEventFilter_cfi import *
filterJetOverlapEvent.src    = "selectedLayer1JetsLowPt"
filterJetOverlapEvent.deltaR = 0.6 # 0.0 = no filtering

## import filters for dR(jet, lepton)
## they are enabled in the muon and electron specific cff-files
from TopAnalysis.TopFilter.filters.MuonDistanceEventFilter_cfi import *
from TopAnalysis.TopFilter.filters.ElecDistanceEventFilter_cfi import *
filterMuonJetDistance.useEventWeight = False
filterElecJetDistance.useEventWeight = False
filterMuonJetDistance.cuts.refs      = "selectedLayer1JetsLowPt"
filterElecJetDistance.cuts.refs      = "selectedLayer1JetsLowPt"

## std sequence for ttGenEvent
from TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff import *

## std sequence for ttGenEventFilter
from TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff import *

## configure jet-parton matching
from TopQuarkAnalysis.TopTools.TtSemiLepJetPartonMatch_cfi import *
ttSemiLepJetPartonMatch.jets = "selectedLayer1JetsLowPt"
# 0 = totalMinDist, 1 = minSumDist, 2 = ptOrderedMinDist, 3 = unambiguousOnly
ttSemiLepJetPartonMatch.algorithm  = 3
ttSemiLepJetPartonMatch.useMaxDist = True
ttSemiLepJetPartonMatch.maxDist    = 0.3
ttSemiLepJetPartonMatch.maxNJets   = 5

#-------------------------------------------------
# define sequences
#-------------------------------------------------

patDefaultSequence_withScaledJets = cms.Sequence(beforeLayer1Objects *   # part of the patDefaultSequence
                                                 allLayer1Objects *      # part of the patDefaultSequence
                                                 scaledJetEnergy *
                                                 selectedLayer1Objects * # part of the patDefaultSequence
                                                 cleanLayer1Objects *    # part of the patDefaultSequence
                                                 countLayer1Objects)     # part of the patDefaultSequence

prepareSemiLepJetCombMVAStudy = cms.Sequence(makeGenEvt *
                                             ttSemiLeptonicFilter *
                                             patDefaultSequence_withScaledJets *
                                             filterMuonJetDistance *
                                             filterElecJetDistance *
                                             filterJetOverlapEvent *
                                             ttSemiLepJetPartonMatch)
