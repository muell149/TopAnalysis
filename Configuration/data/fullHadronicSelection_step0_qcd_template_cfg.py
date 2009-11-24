import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for preselected pat layer1 object 
# creation
#-------------------------------------------------
process = cms.Process("PatTuple")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
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
    wantSummary = cms.untracked.bool(True)
)

## configure geometry
process.load("Configuration.StandardSequences.Geometry_cff")

## configure conditions
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('MC_31X_V9::All')

## Magnetic field now needs to be in the high-level py
process.load("Configuration.StandardSequences.MagneticField_cff")

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## process path
process.pat = cms.Path(process.patDefaultSequence)


#-------------------------------------------------
# event weight configuration
#-------------------------------------------------

## add event weight information
process.load("TopAnalysis.TopUtils.EventWeightPlain_cfi")
process.eventWeight.nevts= 1
process.eventWeight.xsec = 1.
process.eventWeight.eff  = 1.
process.eventWeight.lumi = 1.

process.wght = cms.Path(process.eventWeight)

#-------------------------------------------------
# configuration of additional jet collections
#-------------------------------------------------

from PhysicsTools.PatAlgos.tools.jetTools import *

addJetID(process, "iterativeCone5CaloJets", "ic5")
addJetCollection(process,cms.InputTag('iterativeCone5CaloJets'),
                 'IC5',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('IC5', 'Calo'),
                 doType1MET   = True,
                 doL1Cleaning = False,                 
                 doL1Counters = False,
                 genJetCollection=cms.InputTag("iterativeCone5GenJets"),
                 doJetID      = False,
                 jetIdLabel   = "ic5"
                 )

addJetID( process, "sisCone5CaloJets", "sc5")
addJetCollection(process,cms.InputTag('sisCone5CaloJets'),
                 'SC5',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('SC5','Calo'),
                 doType1MET   = True,
                 doL1Cleaning = False,                                  
                 doL1Counters = False,
                 genJetCollection=cms.InputTag("sisCone5GenJets"),
                 doJetID      = False,
                 jetIdLabel   = "sc5"                 
                 )

#-------------------------------------------------
# preselection paths (involved jet collections
# need to be known first)
#-------------------------------------------------

## preselection for ak5 jets 
process.selectedLayer1Jets.cut = 'abs(eta) < 3.0 & pt>20'
process.countLayer1JetsAK5 = process.countLayer1Jets.clone(src = 'selectedLayer1Jets'   , minNumber = 6)
process.ak5Selection = cms.Path(process.countLayer1JetsAK5 )   

## preselection for ic5 jets 
process.selectedLayer1JetsIC5.cut = 'abs(eta) < 3.0 & pt>20'
process.countLayer1JetsIC5 = process.countLayer1Jets.clone(src = 'selectedLayer1JetsIC5', minNumber = 6)
process.ic5Selection = cms.Path(process.countLayer1JetsIC5 )   

## preselection for sc5 jets 
process.selectedLayer1JetsSC5.cut = 'abs(eta) < 3.0 & pt>20'
process.countLayer1JetsSC5 = process.countLayer1Jets.clone(src = 'selectedLayer1JetsSC5', minNumber = 6)
process.sc5Selection = cms.Path(process.countLayer1JetsSC5 )   

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
        SelectEvents = cms.vstring('ak5Selection', 'ic5Selection', 'sc5Selection')
    )
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('patTuple_qcd_template.root')
)

#-------------------------------------------------
# further workflow configurartion (process.out
# needs to be known first)
#-------------------------------------------------

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *
# run the 3.3.x software on Summer 09 MC from 3.1.x:
#   - change the name from "ak" (3.3.x) to "antikt) (3.1.x)
#   - run jet ID (not run in 3.1.x)
run33xOn31xMC( process,
               jetSrc = cms.InputTag("antikt5CaloJets"),
               jetIdTag = "antikt5"
               )

## add selectedLayer1Candidates
from PhysicsTools.PatAlgos.tools.coreTools import removeCleaning
removeCleaning(process)

# save PAT Layer 1 output
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentNoLayer1Cleaning
process.out.outputCommands += ["keep *_selectedLayer1Jets*_*_*",
                               "keep *_layer1METs*_*_*"]
process.out.outputCommands += ["keep *_eventWeight_*_*"]
# drop stuff which is not needed
process.out.outputCommands += ["drop *_towerMaker_*_*"]

process.outpath = cms.EndPath(process.out)
