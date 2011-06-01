import FWCore.ParameterSet.Config as cms

muonCollection = cms.InputTag("isolatedMuons")
elecCollection = cms.InputTag("isolatedElectrons")
jetCollection  = cms.InputTag("hardJets")


from TopAnalysis.TopAnalyzer.DiLeptonAnalyzer_cfi import *

analyzeLeptonPair0a            = analyzeLeptonPair.clone()
analyzeLeptonPair0a.fileOutput = False
analyzeLeptonPair0a.outputFile = cms.untracked.string('DiLepton0a.txt')
analyzeLeptonPair0a.elecs      = cms.InputTag("selectedPatElectrons")
analyzeLeptonPair0a.jets       = cms.InputTag("selectedPatJetsAK5PF")

analyzeLeptonPair0             = analyzeLeptonPair.clone()
analyzeLeptonPair0.fileOutput  = False
analyzeLeptonPair0.outputFile  = cms.untracked.string('DiLepton0.txt')
analyzeLeptonPair0.muons       = cms.InputTag("hardMuons")

analyzeLeptonPair1             = analyzeLeptonPair.clone()
analyzeLeptonPair1.fileOutput  = False
analyzeLeptonPair1.outputFile  = cms.untracked.string('DiLepton1.txt')
analyzeLeptonPair1.muons       = muonCollection

analyzeLeptonPair2             = analyzeLeptonPair.clone()
analyzeLeptonPair2.fileOutput  = False
analyzeLeptonPair2.outputFile  = cms.untracked.string('DiLepton2.txt')
analyzeLeptonPair2.muons       = muonCollection
analyzeLeptonPair2.elecs       = elecCollection

analyzeLeptonPair3             = analyzeLeptonPair.clone()
analyzeLeptonPair3.fileOutput  = False
analyzeLeptonPair3.outputFile  = cms.untracked.string('DiLepton3.txt')
analyzeLeptonPair3.muons       = muonCollection
analyzeLeptonPair3.elecs       = elecCollection
analyzeLeptonPair3.jets        = jetCollection

analyzeLeptonPair4            = analyzeLeptonPair.clone()
analyzeLeptonPair4.fileOutput = False
analyzeLeptonPair4.outputFile = cms.untracked.string('DiLepton4.txt')
analyzeLeptonPair4.muons      = muonCollection
analyzeLeptonPair4.elecs      = elecCollection
analyzeLeptonPair4.jets       = jetCollection

analyzeLeptonPair5            = analyzeLeptonPair.clone()
analyzeLeptonPair5.fileOutput = False
analyzeLeptonPair5.outputFile = cms.untracked.string('DiLepton5.txt')
analyzeLeptonPair5.muons      = muonCollection
analyzeLeptonPair5.elecs      = elecCollection
analyzeLeptonPair5.jets       = jetCollection

analyzeLeptonPair6            = analyzeLeptonPair.clone()
analyzeLeptonPair6.fileOutput = False
analyzeLeptonPair6.outputFile = cms.untracked.string('DiLepton6.txt')
analyzeLeptonPair6.muons      = muonCollection
analyzeLeptonPair6.elecs      = elecCollection
analyzeLeptonPair6.jets       = jetCollection
