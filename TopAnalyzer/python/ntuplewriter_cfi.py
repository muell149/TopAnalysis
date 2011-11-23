import FWCore.ParameterSet.Config as cms
#from TopAnalysis.TopUtils.EventWeightPU_cfi import *

writeNTuple = cms.EDAnalyzer('NTupleWriter',
                       hypoKey = cms.InputTag("ttFullLepHypKinSolution","Key"),
                       genParticles = cms.InputTag("genParticles"),
                       FullLepEvent = cms.InputTag("ttFullLepEvent"),
                       src = cms.InputTag("genEvt"),
                       muons = cms.InputTag("muons"),
                       elecs = cms.InputTag("elecs"),
                       jets      = cms.InputTag("jets"),
                       met       = cms.InputTag("met"),
                       vertices  = cms.InputTag('offlinePrimaryVertices'),
                       weightPU    =  cms.InputTag('eventWeightPU', 'eventWeightPU'),
                       weightLepSF =  cms.InputTag('eventWeightDileptonSF', 'eventWeightDileptonSF'),
                       weightKinFit = cms.InputTag("eventWeightKinEffForNtuple", "eventWeightDileptonKinEffSF"),
                       datatype  =  cms.InputTag("data"),
                       includeTrigger = cms.bool(False),
                       triggerResults = cms.InputTag('TriggerResults','','HLT'),
                       decayMode = cms.InputTag("generatorTopFilter", "decayMode"),
                       isTtBarSample = cms.bool(True),
                       #directory = cms.string(""), #../NTupDir
                       directory = cms.string("../NTupDir"), #../NTupDir
)

