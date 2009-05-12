import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.SemiLepJetCombMVAStudy_common_cff import *

## electron for event selection and final analysis
selectedLayer1Electrons.cut = 'pt > 20. & abs(eta) < 2.4 & (trackIso+caloIso)/et < 0.1 & electronID("eidRobustTight")'
countLayer1Electrons.minNumber = 1
countLayer1Electrons.maxNumber = 1

## filter events with small dR(jet, electron)
filterElecJetDistance.cuts.min = [0.5]

## configure ttGenEventFilter
ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = True
ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = False
ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = False
