import FWCore.ParameterSet.Config as cms

## configure JetEnergyScale
from TopAnalysis.TopUtils.JetEnergyScale_cfi import *
scaledJetEnergy.scaleFactor = 1.0

## tqafLayer1
from TopQuarkAnalysis.TopObjectProducers.tqafLayer1_cff import *

## muon for event selection and final analysis
selectedLayer1Muons.cut = 'pt > 20. & abs(eta) < 2.1 & (trackIso+caloIso)/pt < 0.1'
minLayer1Muons.minNumber = 1
maxLayer1Muons.maxNumber = 1

## clone selectedLayer1Jets with lowered pt threshold for analysis
selectedLayer1JetsLowPt     = selectedLayer1Jets.clone()
selectedLayer1JetsLowPt.src = "scaledJetEnergy:allLayer1Jets"
selectedLayer1JetsLowPt.cut = 'pt > 20. & abs(eta) < 2.4 & nConstituents > 0'

## jets for event selection
selectedLayer1Jets.src = "scaledJetEnergy:allLayer1Jets"
selectedLayer1Jets.cut = 'pt > 30. & abs(eta) < 2.4 & nConstituents > 0'
minLayer1Jets.minNumber = 4

## use recalculated MET after scaling of jet energy
selectedLayer1METs.src = "scaledJetEnergy:allLayer1METs"

## filter events with overlapping jets
from TopAnalysis.TopFilter.filters.JetOverlapEventFilter_cfi import *
filterJetOverlapEvent.src    = "selectedLayer1JetsLowPt"
filterJetOverlapEvent.deltaR = 0.0 # 0.0 = no filtering

## std sequence for ttGenEvent
from TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff import *

## configure ttGenEventFilter
from TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff import *
ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = False
ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = False

## configure jet parton matching
from TopQuarkAnalysis.TopTools.TtSemiLepJetPartonMatch_cfi import *
ttSemiLepJetPartonMatch.jets = "selectedLayer1JetsLowPt"
# 0 = totalMinDist, 1 = minSumDist, 2 = ptOrderedMinDist, 3 = unambiguousOnly
ttSemiLepJetPartonMatch.algorithm  = 3
ttSemiLepJetPartonMatch.useMaxDist = True
ttSemiLepJetPartonMatch.maxDist    = 0.3
ttSemiLepJetPartonMatch.maxNJets   = 5

#-------------------------------------------------
# define some sequences
#-------------------------------------------------

patLayer1_allObjects = cms.Sequence(allLayer1Muons +
                                    allLayer1Electrons +
                                    allLayer1Taus +
                                    allLayer1Photons +
                                    allLayer1Jets +
                                    allLayer1METs)

patLayer1_selectedObjects = cms.Sequence(selectedLayer1Muons * countLayer1Muons *
                                         selectedLayer1Electrons * countLayer1Electrons *
                                         selectedLayer1Taus * countLayer1Taus *
                                         selectedLayer1Photons * countLayer1Photons *
                                         selectedLayer1JetsLowPt * selectedLayer1Jets * countLayer1Jets *
                                         selectedLayer1METs *
                                         selectedLayer1Hemispheres)

patLayer1_withScaledJets = cms.Sequence(patLayer1_allObjects*
                                        scaledJetEnergy *
                                        patLayer1_selectedObjects)

prepareSemiLepJetCombMVAStudy = cms.Sequence(patLayer0_patTuple *
                                             patLayer1_withScaledJets *
                                             filterJetOverlapEvent *
                                             makeGenEvt *
                                             ttSemiLeptonicFilter *
                                             ttSemiLepJetPartonMatch)
