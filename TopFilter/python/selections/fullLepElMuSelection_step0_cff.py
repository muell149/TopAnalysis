import FWCore.ParameterSet.Config as cms

## electron preselection
fullLepElecEta = cms.PSet(
    mode = cms.uint32 ( 0),
    name = cms.string ('preFullLepElMuEtaEl'),
    min  = cms.vdouble(-2.5),
    max  = cms.vdouble( 2.5)
)
fullLepElecPt = cms.PSet(
    mode = cms.uint32 ( 0),    
    name = cms.string ('preFullLepElMuPtEl' ),
    min  = cms.vdouble(  15.0),
    max  = cms.vdouble(9999.0)
)

## muon preselection
fullLepMuonEta = cms.PSet(
    mode = cms.uint32 ( 0),
    name = cms.string ('preFullLepElMuEtaMu'),
    min  = cms.vdouble(-2.5),
    max  = cms.vdouble( 2.5)
)
fullLepMuonPt = cms.PSet(
    mode = cms.uint32 ( 0),    
    name = cms.string ('preFullLepElMuPtMu' ),
    min  = cms.vdouble(  15.0),
    max  = cms.vdouble(9999.0)
)

## jets preselection 
## (only one jet is demanded to have a signal free reference sample)
fullLepJetsEta = cms.PSet(
    mode = cms.uint32 ( 0),    
    name = cms.string ('preFullLepElMuEtaJet'),
    min  = cms.vdouble(-3.25,-3.25 ),    
    max  = cms.vdouble( 3.25, 3.25 )    
)
fullLepJetsPt = cms.PSet(
    mode = cms.uint32 ( 0),    
    name = cms.string ('preFullLepElMuPtJet' ),
    min  = cms.vdouble(  10.0,   10.0 ),  
    max  = cms.vdouble(9999.0, 9999.0 )   
)




