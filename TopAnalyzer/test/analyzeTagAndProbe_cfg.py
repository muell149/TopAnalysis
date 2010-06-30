import FWCore.ParameterSet.Config as cms

#-------------------------------------------------
# cfg file for the analysis of selected muon
# quantities
#-------------------------------------------------
process = cms.Process("TagAndProbe")

## configure message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
## process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-------------------------------------------------
# process configuration
#-------------------------------------------------

## define input
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(    
    ## add your favourite file here
    ##"/store/user/rwolf/ttbar09/patTuple_all_0_ttbar09.root"
    ## for testing at cern
    '/store/mc/Spring10/TTbarJets-madgraph/AODSIM/START3X_V26_S09-v1/0005/0210B899-9C46-DF11-A10F-003048C69294.root'
    ##'/store/relval/CMSSW_3_3_0/RelValTTbar/GEN-SIM-RECO/STARTUP31X_V8-v1/0001/3291E09D-67B7-DE11-9ED6-003048678C9A.root'
    )
)

## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

#-------------------------------------------------
# tagAndProbeAnalysis analysis
#-------------------------------------------------

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import selectedPatJets

## produce collection of well defined jets
process.selectedJets = selectedPatJets.clone(src = 'selectedPatJets',
                                                cut = 'pt>30 & abs(eta)<3 & emEnergyFraction<0.95'
                                                )

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import selectedPatMuons

## as probe requirement choose standalonMuon 
process.probeMuons = selectedPatMuons.clone(src = 'selectedPatMuons',
                                               cut = 'standAloneMuon.isNull=0'
                                               )

## as test requirement choose combinedMuon 
process.testMuons = selectedPatMuons.clone(src = 'probeMuons',
                                              cut = 'combinedMuon.isNull=0'
                                              )


## pat sequences

## Geometry and Detector Conditions (needed for a few patTuple production steps)
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
## global tag for 33X
## process.GlobalTag.globaltag = cms.string('STARTUP31X_V1::All')
## global tag for 34X
process.GlobalTag.globaltag = cms.string('STARTUP3XY_V9::All')
process.load("Configuration.StandardSequences.MagneticField_cff")

## Standard PAT Configuration File
process.load("PhysicsTools.PatAlgos.patSequences_cff")


## analyze muons
process.load("TopAnalysis.TopAnalyzer.TagAndProbeAnalyzer_cfi")
process.tagAndProbeAnalyzer.tests  = "testMuons"
process.tagAndProbeAnalyzer.probes = "probeMuons"
process.tagAndProbeAnalyzer.jets = "selectedJets"

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeTagAndProbe.root')
)

## Needed for redoing the ak5GenJets
process.load("TopAnalysis.TopUtils.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff")

from PhysicsTools.PatAlgos.tools.cmsswVersionTools import run36xOn35xInput
run36xOn35xInput(process)

process.p1 = cms.Path(
    process.genJetParticles *
    process.ak5GenJets *
    ## apply tag selection
    process.patDefaultSequence *
    ## create probe and test collections
    process.selectedJets  *
    process.probeMuons    *
    process.testMuons     *
    ## analyze probe and test collections
    process.tagAndProbeAnalyzer
    )
