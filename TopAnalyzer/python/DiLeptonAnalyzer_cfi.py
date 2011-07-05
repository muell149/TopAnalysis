import FWCore.ParameterSet.Config as cms

analyzeLeptonPair = cms.EDAnalyzer("DiLeptonAnalyzer",

    fileOutput = cms.bool(False),
    outputFile = cms.untracked.string('DiLeptonEvents.txt'),
    ###
    vertexCollection = cms.InputTag('offlinePrimaryVertices'),
    vertex_X_cut     = cms.double(  1.0 ),
    vertex_Y_cut     = cms.double(  1.0 ),
    vertex_Z_cut     = cms.double( 24.0 ),
    ###
    loose_muons = cms.InputTag('selectedPatMuons'),
    muons       = cms.InputTag('selectedPatMuons'),
    elecs       = cms.InputTag('goodIdElectrons'),
    jets        = cms.InputTag('goodIdJetsPF'),
    ###
    muon_iso_cut   = cms.double( 1000.),
    elec_iso_cut   = cms.double( 1000.),
    ###
    MassWindow_up   = cms.double( 9999. ),
    MassWindow_down = cms.double(   12. ),

    weight = cms.InputTag('eventWeightPU')
)
