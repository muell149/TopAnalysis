import FWCore.ParameterSet.Config as cms

selectDiLeptons = cms.EDFilter('DiLeptonCountFilter',
                      dileptons  = cms.InputTag("dileptons"),   
                      minnumber  = cms.int32(1)             
)
