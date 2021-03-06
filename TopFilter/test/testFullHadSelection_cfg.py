import FWCore.ParameterSet.Config as cms

#---------------------------------------------------
# test cfg file for the selection of
# fullhadronic ttbar events
#---------------------------------------------------
process = cms.Process("Selection")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 100

#---------------------------------------------------
# process configuration
#---------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/mc/Spring10/TTbar-mcatnlo/AODSIM/START3X_V26_S09-v2/0048/F4F2E9FA-6C4A-DF11-AE26-002618FDA21D.root'
    ),
    skipEvents = cms.untracked.uint32(0)
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

## configure geometry & conditions
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START38_V7::All')

#---------------------------------------------------
# event selection
#---------------------------------------------------

## select events that were generated in the fully hadronic channel
process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

## filter for full-hadronic 
process.load("TopQuarkAnalysis.TopEventProducers.producers.TtDecaySelection_cfi")
process.ttFullHadronicFilter = process.ttDecaySelection.clone()

## apply realistic event selection
process.load("TopAnalysis.TopFilter.sequences.triggerFilter_cff")
process.load("TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff")

## a little speed up as monitoring plots an gen matching are not needed here
from TopAnalysis.TopFilter.sequences.fullHadronicSelection_cff import *
removeMonitoringOfCutflow(process)
process.analyseFullHadronicSelection.remove(process.matchJetsToPartons)

## switch to TCHE b-tagger of the default selection
switchToTCHE(process)

## switch to PF, as this is used in the default selection
runOnPF(process)

## do kinFit of events needed for selection cuts
from TopQuarkAnalysis.TopEventProducers.sequences.ttFullHadEvtBuilder_cff import *

addTtFullHadHypotheses(process, ["kKinFit"])

removeTtFullHadHypGenMatch(process)

#---------------------------------------------------
# pat configuration
#---------------------------------------------------

## std sequence for pat
process.load("PhysicsTools.PatAlgos.patSequences_cff")

## needed as data is 35X but processing is done in 36X
from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run36xOn35xInput
run36xOn35xInput(process)

## add jet collection needed for default analysis
from PhysicsTools.PatAlgos.tools.jetTools import *
switchJetCollection(process,cms.InputTag('ak5PFJets'),
                    doJTA        = True,
                    doBTagging   = True,
                    jetCorrLabel = ('AK5', 'PF'),
                    doType1MET   = False,
                    genJetCollection=None,
                    doJetID      = True
                    )

## remove some elements from sequence, which are not needed here
from PhysicsTools.PatAlgos.tools.coreTools import *
## MC matching not needed for event selection (as this is not available in data)
removeMCMatching(process)

## remove unneeded objects from processing (speed up of whole sequence)
removeAllPATObjectsBut(process, ['Jets'], outputInProcess=False)

## cleaning not neede here
removeCleaning(process, outputInProcess=False)

## embedding of resolutions into the patObjects
process.load("TopQuarkAnalysis.TopObjectResolutions.stringResolutions_etEtaPhi_cff")
process.patJets.addResolutions = True
process.patJets.resolutions = cms.PSet(
    default = cms.string("udscResolutionPF"),
    bjets = cms.string("bjetResolutionPF"),
    )

## setting JEC to desired values
process.patJetCorrFactors.corrSample = 'Spring10'
process.patJetCorrFactors.sampleType = 'ttbar'

## replace jets and met with PFJets and PFMET
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
massSearchReplaceAnyInputTag(process.analyseFullHadronicSelection, 'selectedPatJetsAK5PF', 'selectedPatJets')

#---------------------------------------------------
# the path
#---------------------------------------------------

process.p1 = cms.Path(process.hltQuadJet15U *
                      process.makeGenEvt *
                      process.ttFullHadronicFilter *
                      process.patDefaultSequence *
                      process.analyseFullHadronicSelection
                      )
