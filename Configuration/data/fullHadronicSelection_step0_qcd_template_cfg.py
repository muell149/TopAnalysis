import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for preselected pat layer1 object 
# creation
#-------------------------------------------------
process = cms.Process("PAT")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/mc/Summer09/QCD_Pt1400/GEN-SIM-RECO/MC_31X_V3_7TeV-v1/0004/2874E107-F69E-DE11-AC8E-003048C757D4.root')
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
process.GlobalTag.globaltag = cms.string('MC_3XY_V18::All')

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

#addJetID only for CaloJets
#addJetID(process, "antikt5PFJets", "pf")
addJetCollection(process,cms.InputTag('antikt5PFJets'),'PF',
                 doJTA        = True,
                 doBTagging   = True,
                 jetCorrLabel = ('AK5', 'PF'),
                 doType1MET   = False,
                 doL1Cleaning = False,
                 doL1Counters = False,
                 genJetCollection=cms.InputTag("antikt5GenJets"),
                 doJetID      = False
                 )

## sample type used for flavour dependend jet corrections
process.jetCorrFactors.corrSample   = 'Summer09_7TeV'
process.jetCorrFactors.sampleType   = 'ttbar'
process.jetCorrFactorsPF.corrSample = 'Summer09_7TeV'
process.jetCorrFactorsPF.sampleType = 'ttbar'

## embedding of jet constituents into the jets
process.allLayer1Jets.embedCaloTowers = True
process.allLayer1JetsPF.embedPFCandidates = True

#-------------------------------------------------
# preselection paths (involved jet collections
# need to be known first)
#-------------------------------------------------

## preselection for ak5 jets 
process.selectedLayer1Jets.cut = 'abs(eta) < 3.0 & pt>20'
process.countLayer1JetsAK5 = process.countLayer1Jets.clone(src = 'selectedLayer1Jets' , minNumber = 6)
process.ak5Selection = cms.Path(process.countLayer1JetsAK5 )   

## preselection for ak5 pf jets 
process.selectedLayer1JetsPF.cut = 'abs(eta) < 3.0 & pt>20'
process.countLayer1JetsAK5PF = process.countLayer1Jets.clone(src = 'selectedLayer1JetsPF' , minNumber = 6)
process.ak5PfSelection = cms.Path(process.countLayer1JetsAK5PF )   

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
        SelectEvents = cms.vstring('ak5PfSelection', 'ak5Selection')
    )
)

## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('patTuple.root')
)

#-------------------------------------------------
# further workflow configurartion (process.out
# needs to be known first)
#-------------------------------------------------

## embedding of trigger information into the pat tuple
process.jetTriggerMatchHLTJets = cms.EDFilter( "PATTriggerMatcherDRLessByR",
                                 src     = cms.InputTag( "selectedLayer1Jets" ),
                                 matched = cms.InputTag( "patTrigger" ),
                                 andOr          = cms.bool( False ),
                                 filterIdsEnum  = cms.vstring( 'TriggerJet' ),
                                 filterIds      = cms.vint32( 0 ), # This is for CMSSW_3_1_X; '85' would be the code for HLT jet here.
                                 filterLabels   = cms.vstring( '*' ),
                                 pathNames      = cms.vstring( '*' ),
                                 collectionTags = cms.vstring( '*' ),
                                 #maxDPtRel = cms.double( 0.5 ),
                                 maxDeltaR = cms.double( 0.5 ),
                                 resolveAmbiguities    = cms.bool( True ),
                                 resolveByMatchQuality = cms.bool( False )
                                 )

process.pfJetTriggerMatchHLTJets = process.jetTriggerMatchHLTJets.clone(src = "selectedLayer1JetsPF")

from PhysicsTools.PatAlgos.tools.trigTools import *
switchOnTrigger( process , 'selected')

process.patTriggerEvent.patTriggerMatches = ['jetTriggerMatchHLTJets', 'pfJetTriggerMatchHLTJets']

process.patTriggerMatcher += process.jetTriggerMatchHLTJets
process.patTriggerMatcher += process.pfJetTriggerMatchHLTJets

process.patTriggerMatcher.remove( process.electronTriggerMatchHltElectrons)
process.patTriggerMatcher.remove( process.electronTriggerMatchHltElectrons)
process.patTriggerMatcher.remove( process.electronTriggerMatchL1Electrons)
process.patTriggerMatcher.remove( process.tauTriggerMatchTriggerTaus)
process.patTriggerMatcher.remove( process.muonTriggerMatchL1Muons)
process.patTriggerMatcher.remove( process.muonTriggerMatchAll)
process.patTriggerMatcher.remove( process.muonTriggerMatchNone)

process.triggerMatchedSelectedLayer1Jets = cms.EDProducer("PATTriggerMatchJetEmbedder",
                                                          matches = cms.VInputTag("jetTriggerMatchHLTJets"),
                                                          src = cms.InputTag("selectedLayer1Jets")
                                                          )

process.triggerMatchedSelectedLayer1JetsPF = cms.EDProducer("PATTriggerMatchJetEmbedder",
                                                            matches = cms.VInputTag("pfJetTriggerMatchHLTJets"),
                                                            src = cms.InputTag("selectedLayer1JetsPF")
                                                            )

process.patDefaultSequence += process.triggerMatchedSelectedLayer1Jets
process.patDefaultSequence += process.triggerMatchedSelectedLayer1JetsPF

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import *
# run the 3.3.x software on Summer 09 MC from 3.1.x:
#   - change the name from "ak" (3.3.x) to "antikt) (3.1.x)
#   - run jet ID (not run in 3.1.x)
run33xOn31xMC( process,
               jetSrc = 'antikt5CaloJets',
               jetIdTag = 'antikt5'
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
process.out.outputCommands += ['keep *_triggerMatchedSelectedLayer1Jets_*_*']
process.out.outputCommands += ['keep *_triggerMatchedSelectedLayer1Jets*_*_*']
# drop stuff which is not needed
process.out.outputCommands += ["drop *_towerMaker_*_*"]

process.outpath = cms.EndPath(process.out)
