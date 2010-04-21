import FWCore.ParameterSet.Config as cms

analyzeCrossSectionRecMuon = cms.EDAnalyzer("MuonCrossSectionAnalyzer",
    ## input collection. This can be generator or reco level, 
    ## it should be reco level if srcB exists as a parameter
    srcA = cms.InputTag("selectedPatMuons"),
    ## special parameters                                            
    analyze   = cms.PSet(
      ## fill histograms for 1.,2.,3.,... leading
      ## counting starts with 0=leading Muon! 
      ## muon? -1 corresponds to 'all'
      index = cms.int32(0)
    )                                       
)

analyzeCrossSectionGenMuon = cms.EDAnalyzer("MuonCrossSectionAnalyzer",
    ## input collection. This can be generator or reco level, 
    ## it should be reco level if match exists as a parameter
    srcA = cms.InputTag("genParticles"),
    ## special parameters
    analyze   = cms.PSet(
      ## fill histograms for 1.,2.,3.,... leading
      ## counting starts with 0=leading Muon! 
      ## muon? -1 corresponds to 'all'
      index = cms.int32(0)
    )                                       
)

analyzeCrossSectionMuonCorrelations = cms.EDAnalyzer("MuonCrossSectionAnalyzer",
    ## input collection. This can be generator or reco level, 
    ## it should be reco level if match exists as a parameter
    srcA = cms.InputTag("selectedPatMuons"),
    ## input collection for stability and purity determination
    ## is an optional parameter; if given it should be
    ## filled with generator particles though
    srcB = cms.InputTag("genParticles"),                                         
    ## special parameters
    analyze   = cms.PSet(
      ## index parameter has no effect when filling the correlation plots but is expected by the module
      index = cms.int32(-1)
    )                                       
)
