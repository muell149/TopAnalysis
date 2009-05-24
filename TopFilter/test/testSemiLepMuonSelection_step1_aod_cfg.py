import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for semi-leptonic ttbar event
# selection step1
#-------------------------------------------------
process = cms.Process("Step1")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    ## add your favourite file here
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## configure geometry
process.load("Configuration.StandardSequences.Geometry_cff")

## configure conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('STARTUP_V4::All')

## Magnetic field now needs to be in the high-level py
process.load("Configuration.StandardSequences.MagneticField_cff")

#-------------------------------------------------
# tqaf configuration; if you want just to produce 
# tqafLayer2 on top of an already existing
# tqafLayer1 just comment the standard tqafLayer1
# production sequence
#-------------------------------------------------

## std sequence for tqaf layer1
process.load("PhysicsTools.PatAlgos.patSequences_cff")
process.p0 = cms.Path(process.patDefaultSequenceNoCleaning)

## necessary fixes to run 2.2.X on 2.1.X data
## comment this when running on samples produced
## with 22X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run22XonSummer08AODSIM
run22XonSummer08AODSIM(process)

#-------------------------------------------------
# semi-leptonic ttbar selection step0
#-------------------------------------------------

## add event weight information
process.load("TopAnalysis.TopUtils.EventWeightPlain_cfi")

## test basic event selection
process.load("TopAnalysis.TopFilter.sequences.semiLepMuonSelection_step1_cff")

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('semiLepMuonSelection_step1.root')
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('patTuple_semiLepMuonSelection_step1.root')
)

process.p1 = cms.Path(process.eventWeight      *
                      process.slmFilterFullMon *
                      process.out
                      )
