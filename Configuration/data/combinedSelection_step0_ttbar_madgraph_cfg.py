import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# test cfg file for tqaflayer1 & 2 production from
# fullsim for semi-leptonic ttbar events 
#-------------------------------------------------
process = cms.Process("PatTuple")

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
    fileNames = cms.untracked.vstring('')
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False)
)

## configure geometry
process.load("Configuration.StandardSequences.Geometry_cff")

## configure conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('STARTUP_V7::All')

## Magnetic field now needs to be in the high-level py
process.load("Configuration.StandardSequences.MagneticField_cff")

#-------------------------------------------------
# tqaf configuration; if you want just to produce 
# tqafLayer2 on top of an already existing
# tqafLayer1 just comment the standard tqafLayer1
# production sequence
#-------------------------------------------------

## std sequence for pat tuples
process.load("TopQuarkAnalysis.TopObjectProducers.patTuple_cff")

## necessary fixes to run 2.2.X on 2.1.X data
## comment this when running on samples produced
## with 22X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run22XonSummer08AODSIM
run22XonSummer08AODSIM(process)

## process path
process.pat = cms.Path(process.patTuple_reduced)


#-------------------------------------------------
# private uni Hamburg analysis code
#-------------------------------------------------

## add event weight information
process.load("TopAnalysis.TopUtils.EventWeightPlain_cfi")
process.eventWeight.nevts = 1026391
process.eventWeight.xsec  = 414
process.eventWeight.lumi  = 1000
process.eventWeight.eff   = 1.0

process.wght = cms.Path(process.eventWeight)   

## basic event selection
#process.load("TopAnalysis.TopFilter.sequences.semiLepMuonSelection_step0_cff")
#process.semiLepMuonSelection = cms.Path(process.preselectSemiLepMuon)   

#process.load("TopAnalysis.TopFilter.sequences.fullLepElMuSelection_step0_cff")
#process.fullLepElMuSelection = cms.Path(process.preselectFullLepElMu)

#process.load("TopAnalysis.TopFilter.sequences.fullLepMuonSelection_step0_cff")
#process.fullLepMuonSelection = cms.Path(process.preselectFullLepMuon)

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('combinedSelection_step0_ttbar_madgraph.root')
)

#-------------------------------------------------
# pat tuple event content; first ALL objects
# are dropped in this process; then patTuple
# content is added
#-------------------------------------------------

## define pat tuple event content
from TopQuarkAnalysis.TopObjectProducers.patTuple_EventContent_cff import *
makePatTupleEventContent(process)

## change jet collection
from PhysicsTools.PatAlgos.tools.jetTools import *

switchJetCollection(process, 
                    'sisCone5CaloJets',             # jet collection; must be already in the event when patLayer0 sequence is executed
                    layers       = [0,1],           # if you're not running patLayer1, set 'layers=[0]' 
                    runCleaner   = "CaloJet",       # =None if not to clean
                    doJTA        = True,            # run jet-track association & JetCharge
                    doBTagging   = True,            # run b-tagging
                    jetCorrLabel = ('SC5', 'Calo'), # example jet correction name; set to None for no JEC
                    doType1MET   = True             # recompute Type1 MET using these jets
                    )

## add TopAnalysis specifics
process.topAnalysisEventContent = cms.PSet(
    outputCommands = cms.untracked.vstring('keep *_eventWeight_*_*')  ## event weight
    )
process.patTupleEventContent.outputCommands.extend(process.topAnalysisEventContent.outputCommands)

#-------------------------------------------------
# process output; first the event selection is
# defined: only those events that have passed the
# full production path are selected and written
# to file; the event content has been defined
# above
#-------------------------------------------------

## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('pat')
    )
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    process.patTupleEventContent,
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('patTuple_ttbar_madgraph.root')
)

process.outpath = cms.EndPath(process.out)
