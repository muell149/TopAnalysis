import FWCore.ParameterSet.Config as cms

generatorTtDileptonFilter = cms.EDFilter("GeneratorTtDileptonFilter",
   # src                 = cms.InputTag("genParticles"), ##pythia
    src                 = cms.InputTag("genEvt"),       ##herwig
    leptonPt	        = cms.double(0. ),
    centralLeptonEta    = cms.double(100),
    leptonEta           = cms.double(100),
    bPt		        = cms.double(0. ),
    bEta	        = cms.double(100),
    met	                = cms.double(0. ),
    invariantLepLepMass = cms.double(0. ),
    zVeto               = cms.vdouble(0.,0.)
)
