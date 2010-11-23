import FWCore.ParameterSet.Config as cms

generatorTtDileptonFilter = cms.EDFilter("GeneratorTtDileptonFilter",
    leptonPt	        = cms.double(0. ),
    leptonEta           = cms.double(10.),
    bPt		        = cms.double(0. ), 
    bEta	        = cms.double(10.),	    
    met	                = cms.double(0. ),
    invariantLepLepMass = cms.double(0. ),  
    zVeto               = cms.vdouble(0.,0.) 	        
)
