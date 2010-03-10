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
    "/store/user/rwolf/ttbar09/patTuple_all_0_ttbar09.root"
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


## analyze muons
from TopAnalysis.TopAnalyzer.TagAndProbeAnalyzer_cfi import tagAndProbeAnalyzer
process.probeAnalyzer = tagAndProbeAnalyzer.clone(jets = 'selectedJets', muons = 'probeMuons')
process.testAnalyzer  = tagAndProbeAnalyzer.clone(jets = 'selectedJets', muons = 'testMuons' )


## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('analyzeTagAndProbe.root')
)

process.p1 = cms.Path(
    ## apply tag selection
    
    ## create probe and test collections
    process.selectedJets  *
    process.probeMuons    *
    process.testMuons     *
    ## analyze probe and test collections
    process.probeAnalyzer *
    process.testAnalyzer
    )
