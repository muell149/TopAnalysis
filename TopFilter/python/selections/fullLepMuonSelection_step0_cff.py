import FWCore.ParameterSet.Config as cms

## muon preselection
fullLepMuonEta = cms.PSet(
    mode = cms.uint32 ( 0),
    name = cms.string ('preFullLepMuonEtaMu'),
    min  = cms.vdouble(-2.5,-2.5),
    max  = cms.vdouble( 2.5, 2.5)
)
fullLepMuonPt = cms.PSet(
    mode = cms.uint32 ( 0),    
    name = cms.string ('preFullLepMuonPtMu' ),
    min  = cms.vdouble(  15.0,   15.0),
    max  = cms.vdouble(9999.0, 9999.0)
)

## jets preselection 
## (only one jet is demanded to have a signal free reference sample)
fullLepJetsEta = cms.PSet(
    mode = cms.uint32 ( 0),    
    name = cms.string ('preFullLepMuonEtaJet'),
    min  = cms.vdouble(-3.25,-3.25 ),    
    max  = cms.vdouble( 3.25, 3.25 )  
)
fullLepJetsPt = cms.PSet(
    mode = cms.uint32 ( 0),    
    name = cms.string ('preFullLepMuonPtJet' ),
    min  = cms.vdouble(  10.0,   10.0 ),  
    max  = cms.vdouble(9999.0, 9999.0 )    
)



