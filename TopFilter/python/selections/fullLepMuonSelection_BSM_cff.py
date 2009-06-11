import FWCore.ParameterSet.Config as cms

## muon selection
firstLepMuonEta = cms.PSet(
    mode = cms.uint32 (0),
    name = cms.string ('fullLepMuonEta'),
    min  = cms.vdouble(-2.1),
    max  = cms.vdouble( 2.1)
)

fullLepMuonEta = cms.PSet(
    mode = cms.uint32 (0),
    name = cms.string ('fullLepMuonEta'),
    min  = cms.vdouble(-2.1,-2.1),
    max  = cms.vdouble( 2.1, 2.1)
)

firstLepMuonPt = cms.PSet(
    mode = cms.uint32 (0),    
    name = cms.string ('firstLepMuonPt'),
    min  = cms.vdouble(   20.0),
    max  = cms.vdouble( 9999.0)
)

fullLepMuonPt = cms.PSet(
    mode = cms.uint32 (0),    
    name = cms.string ('fullLepMuonPt'),
    min  = cms.vdouble(   20.0,   20.0),
    max  = cms.vdouble( 9999.0, 9999.0)
)

## jets selection
firstLepJetsEta = cms.PSet(
    mode = cms.uint32 ( 0),    
    name = cms.string ('firstLepJetsEta'),
    min  = cms.vdouble(-2.4),
    max  = cms.vdouble( 2.4)
)
fullLepJetsEta = cms.PSet(
    mode = cms.uint32 ( 0),    
    name = cms.string ('fullLepJetsEta'),
    min  = cms.vdouble(-2.4, -2.4),
    max  = cms.vdouble( 2.4,  2.4)
)

firstLepJetsPt = cms.PSet(
    mode = cms.uint32 ( 0),    
    name = cms.string ('firstLepJetsPt'),
    min  = cms.vdouble(  40.0),
    max  = cms.vdouble(9999.0)
)

fullLepJetsPt = cms.PSet(
    mode = cms.uint32 ( 0),    
    name = cms.string ('fullLepJetsPt'),
    min  = cms.vdouble(  40.0,   40.0),
    max  = cms.vdouble(9999.0, 9999.0)
)

## isolation selection
firstLepCombIsolation = cms.PSet(
    type = cms.uint32 (  4  ),
    mode = cms.uint32 (  0  ),    
    name = cms.string('firstLepMuonCombIso'),
    min  = cms.vdouble(  -0.025),
    max  = cms.vdouble(  0.1)   
)  

fullLepCombIsolation = cms.PSet(
    type = cms.uint32 (  4  ),
    mode = cms.uint32 (  0  ),    
    name = cms.string('fullLepMuonCombIso'),
    min  = cms.vdouble(  -0.025, -0.025),
    max  = cms.vdouble( 0.1, 0.1)   
)   

## BSM cuts
fullLepJetsnr = cms.PSet(
    mode = cms.uint32 ( 0),    
    name = cms.string ('fullLepJetsnr'),
    min  = cms.vdouble(  40.0, 40.0, 30.0, 30.0),
    max  = cms.vdouble(9999.0,9999.0,9999.0,9999.0)
    )

fullLepMET = cms.PSet(
    mode = cms.uint32 (0),    
    name = cms.string ('fullLepMET'),
    min  = cms.vdouble(   180.0),
    max  = cms.vdouble( 9999.0)
    )




