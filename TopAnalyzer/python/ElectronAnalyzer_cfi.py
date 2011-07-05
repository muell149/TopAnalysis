import FWCore.ParameterSet.Config as cms

analyzeElectrons = cms.EDAnalyzer("ElectronAnalyzer",

    # Source
    electrons = cms.InputTag("selectedPatElectrons"),
    jets  = cms.InputTag("selectedPatJets"),

    verbosity = cms.bool(False),
    # only muons from first to last index
    from_to = cms.vint32(0,1),
    weight = cms.InputTag('eventWeightPU')
)

