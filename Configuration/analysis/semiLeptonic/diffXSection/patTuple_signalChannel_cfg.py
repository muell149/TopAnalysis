import FWCore.ParameterSet.Config as cms

process = cms.Process("Signal")

## Message Logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
##process.MessageLogger.cerr.FwkReport.reportEvery = 100

## Options and Output Report
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

## Source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/afs/naf.desy.de/user/r/rwolf/data/samples/ttbar09/patTuple_ttbar09_all_0_ttbar09.root'
    )
)
## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

## ---------------------------------------------------------------------------------
##
## Path Definition
##
## ---------------------------------------------------------------------------------

## std sequence to produce the ttGenEvt
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## semi-leptonic decay filter
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttSemiLeptonicFilter = process.ttDecaySelection.clone()
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchA.muon = True
process.ttSemiLeptonicFilter.allowedTopDecays.decayBranchB.muon = False

process.p = cms.Path(process.makeGenEvt *
                     process.ttSemiLeptonicFilter
                     )

## Output Module Configuration
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('patTuple_signal.root'),
                               # save only events passing the full path
                               SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               # save output (comment to keep everything...)
                               #outputCommands = cms.untracked.vstring('drop *',) 
                               )
process.outpath = cms.EndPath(process.out)
