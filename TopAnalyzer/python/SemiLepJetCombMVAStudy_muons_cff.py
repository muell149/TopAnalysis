import FWCore.ParameterSet.Config as cms

from TopAnalysis.TopAnalyzer.SemiLepJetCombMVAStudy_common_cff import *

## muon for event selection and final analysis
selectedLayer1Muons.cut = 'pt > 20. & abs(eta) < 2.1 & (trackIso+caloIso)/pt < 0.1'
minLayer1Muons.minNumber = 1
maxLayer1Muons.maxNumber = 1

## filter events with small dR(jet, muon)
filterMuonJetDistance.cuts.min = [0.5]

## configure ttGenEventFilter
ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = False
ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = False
