import FWCore.ParameterSet.Config as cms

filterFullLepHypothesis = cms.EDAnalyzer("FullLepHypothesesFilter",
    hypoKey = cms.InputTag("ttFullLepHypKinSolution","Key"),
    FullLepEvent = cms.InputTag("ttFullLepEvent"),
    weight = cms.InputTag("eventWeight"),
    jets = cms.InputTag("tightJets"),
        
    ## cuts on muon muon mass
    qcdCut = cms.double(20.),
    zCut   = cms.vdouble(76.,106.),
        
    ## b-tagging (if bDisc has two arguments both jets have 
    ## to pass the cuts, if only one number is given only one jet
    ## has to be tagged.)
    bAlgorithm     = cms.string('simpleSecondaryVertexBJetTags'),
    bDiscriminator = cms.vdouble(1.)
)
