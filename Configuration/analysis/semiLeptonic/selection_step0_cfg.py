import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for semi-leptonic ttbar event
# selection step0
#-------------------------------------------------
process = cms.Process("Step0")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.categories.append('topFilter')
process.MessageLogger.cout = cms.untracked.PSet(
 INFO = cms.untracked.PSet(
   limit     = cms.untracked.int32( 0 ),
   topFilter = cms.untracked.PSet( limit = cms.untracked.int32(10) )
  )
)
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
    ## reduce memory consumption    
    fileMode = cms.untracked.string('FULLMERGE'),
    ## switch event summary off
    wantSummary = cms.untracked.bool(False)
)

#-------------------------------------------------
# semi-leptonic ttbar selection step0
#-------------------------------------------------

## add event weight information
process.load("TopAnalysis.TopUtils.EventWeightPlain_cfi")
## ttbar madgraph fullsim
## process.eventWeight.nevts = 1028322
## process.eventWeight.xsec  = 414
## process.eventWeight.lumi  = 1000
## process.eventWeight.eff   = 1.0

## wjets madgraph fastsim
## process.eventWeight.nevts = 101467739
## process.eventWeight.xsec  = 35000
## process.eventWeight.lumi  = 1000
## process.eventWeight.eff   = 1.0

## zjets madgraph fastsim
## process.eventWeight.nevts = 9964055
## process.eventWeight.xsec  = 3700
## process.eventWeight.lumi  = 1000
## process.eventWeight.eff   = 1.0

## qcd pythia preselected
process.eventWeight.nevts = 6238383
process.eventWeight.xsec  = 509100000
process.eventWeight.lumi  = 1000
process.eventWeight.eff   = 0.000239

## test basic event selection
process.load("TopAnalysis.TopFilter.sequences.semiLepMuonSelection_step0_cff")
process.p0 = cms.Path(process.preselectSemiLepMuon)
    
## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('selection_step0.root')
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
##  outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents   = cms.untracked.PSet( SelectEvents = cms.vstring('p0') ),
    fileName       = cms.untracked.string('selection_step0.root')
)

process.p1 = cms.EndPath(process.out)
