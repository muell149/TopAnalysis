import FWCore.ParameterSet.Config as cms

analyzeTtDimuon = cms.EDAnalyzer("TtDiMuonAnalyzer",

    # sources
    muons = cms.InputTag("selectedLayer1Muons"),
    jets = cms.InputTag("selectedLayer1Jets"),
    met = cms.InputTag("selectedLayer1METs"),
    genEvt = cms.InputTag("genEvt"),
    solutions = cms.InputTag("solutions"),
    
    # hist file
    hist = cms.string('TtKin.hist'),
    
    # steerables
    show_Top_Objects = cms.bool(True),
    show_Gen_Event = cms.bool(True),
    show_Kin_Solution = cms.bool(True),
    fit_Top_Mass = cms.bool(False),
    
    # cuts
    leptonPtCut = cms.double(20.0),
    jetPtCut = cms.double(40.0),
    metCut = cms.double(0.0),            
    dilepMassLowZCut = cms.double(80.0),            
    dilepMassHighZCut = cms.double(100.0),
    dilepMassQCDCut = cms.double(5.0)   
)
