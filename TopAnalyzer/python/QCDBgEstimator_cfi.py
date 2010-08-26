import FWCore.ParameterSet.Config as cms

estimateQCDBg = cms.EDAnalyzer("QCDBgEstimator",
    # source
    muons = cms.InputTag("selectedPatMuons"),     

    # iso bins of the worse isolated muon's isolation
    isoBins = cms.vdouble(0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0), 
    
    # invariant mass bins
    massBins = cms.vdouble(15.,76.,106.)
)


