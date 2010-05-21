execfile("TopAnalysis/Configuration/analysis/semiLeptonic/sync/synchronizationExercise_cfg.py")

## put genEvent filter that only selects the ttbar muon+jets channel in front of normal selection sequences

process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEventFilters_cff")
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.electron = False
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon     = True
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.tau      = False

process.looseSelection.replace(process.looseSequence,
                               process.makeGenEvt *
                               process.ttSemiLeptonicFilter *
                               process.looseSequence)

process.tightSelection.replace(process.tightSequence,
                               process.makeGenEvt *
                               process.ttSemiLeptonicFilter *
                               process.tightSequence)

## create two additional paths that have the inverted genEvent filter

process.looseSelection_ttbarOther = cms.Path(process.looseSequence)

process.tightSelection_ttbarOther = cms.Path(process.tightSequence)

process.looseSelection_ttbarOther.replace(process.looseSequence,
                                          process.makeGenEvt *
                                          ~process.ttSemiLeptonicFilter *
                                          process.looseSequence)

process.tightSelection_ttbarOther.replace(process.tightSequence,
                                          process.makeGenEvt *
                                          ~process.ttSemiLeptonicFilter *
                                          process.tightSequence)
