import FWCore.ParameterSet.Config as cms

analyzeTrigger = cms.EDAnalyzer("TriggerAnalyzer",

    TriggerResults = cms.InputTag('TriggerResults',         '','HLT'),
    TriggerEvent   = cms.InputTag('hltTriggerSummaryAOD',   '','HLT'),
    TriggerFilter  = cms.InputTag('hltSingleMu9L3Filtered9','','HLT'),
    ### 
    hltPaths       = cms.vstring('HLT_Mu9','HLT_Mu11','HLT_Mu13','HLT_Mu13_v1','HLT_Mu15','HLT_Mu15_v1',
                                 'HLT_IsoMu3','HLT_IsoMu9','HLT_DoubleMu3_v2','HLT_DoubleMu5_v1',
                                 'HLT_Ele10_LW_L1R','HLT_Ele15_LW_L1R','HLT_Ele20_LW_L1R'),
    hltPaths_sig   = cms.vstring('HLT_IsoMu3', 'HLT_Mu9', 'HLT_Mu11', 'HLT_IsoMu9', 'HLT_DoubleMu3_v2', 'HLT_DoubleMu5_v1'),
    hltPaths_trig  = cms.vstring('HLT_Mu5',    'HLT_Mu5', 'HLT_Mu9',  'HLT_Mu9',    'HLT_Mu5',          'HLT_Mu5'),
    ### 
    vertexCollection = cms.InputTag('offlinePrimaryVertices'),
    vertex_X_cut     = cms.double(  1.0 ),
    vertex_Y_cut     = cms.double(  1.0 ),
    vertex_Z_cut     = cms.double( 24.0 ),
    ### 
    muonCollection = cms.InputTag('selectedPatMuons'),
    # muonCollection = cms.InputTag('muons'),
    muon_pT_cut    = cms.double( 20.0  ),
    muon_eta_cut   = cms.double(  2.4  ),
    muon_iso_cut   = cms.double(  0.15 ),
    ### 
    MassWindow_up   = cms.double( 106.0 ),
    MassWindow_down = cms.double(  76.0 )

)
