import FWCore.ParameterSet.Config as cms

## std sequence for tqaf layer1
from TopQuarkAnalysis.TopObjectProducers.tqafLayer1_cff import *
selectedLayer1Jets.cut  = 'pt > 40. & abs(eta) < 2.4 & nConstituents > 0'
selectedLayer1Muons.cut = 'pt > 30. & abs(eta) < 2.1 & (trackIso+caloIso)/pt < 0.1'
minLayer1Jets .minNumber = 4
minLayer1Muons.minNumber = 1
maxLayer1Muons.maxNumber = 1

## std sequence for ttGenEvent
from TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff import *

## configure ttGenEventFilter
from TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff import *
ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = False
ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = False

## configure jet parton matching
from TopQuarkAnalysis.TopTools.TtSemiLepJetPartonMatch_cfi import *
ttSemiLepJetPartonMatch.algorithm  = 3 # 1 = minSumDist, 3 = unambiguousOnly
ttSemiLepJetPartonMatch.useMaxDist = True
ttSemiLepJetPartonMatch.maxDist    = 0.3
ttSemiLepJetPartonMatch.maxNJets   = 5

## define some sequences
prepareSemiLepJetCombMVAStudy = cms.Sequence(tqafLayer1 *
                                             makeGenEvt *
                                             ttSemiLeptonicFilter *
                                             ttSemiLepJetPartonMatch)
