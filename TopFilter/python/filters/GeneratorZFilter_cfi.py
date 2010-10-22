import FWCore.ParameterSet.Config as cms

generatorZFilter = cms.EDFilter('GeneratorZFilter',
    # generator particle collection
    src = cms.InputTag("genParticles"),
        
    # filter on Z decay mode via PDG-id: default is muon
    zDecayModes = cms.vint32(13), 
    
    # filter only specific tau decays (ee,emu,mumu)
    tauDecays = cms.vstring(), 
    
    # filter on invariant mass (use intervals w/ even no. of elements, do not filter if empty)
    diLeptonMassIntervals = cms.vdouble()
)
