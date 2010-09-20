import FWCore.ParameterSet.Config as cms

filterFullLepHypothesis = cms.EDFilter("FullLepHypothesesFilter",
    hypoKey = cms.InputTag("ttFullLepHypKinSolution","Key"),
    FullLepEvent = cms.InputTag("ttFullLepEvent"),
    jets = cms.InputTag("hardJets"),
        
    ## b-tagging (if bDisc has two arguments both jets have 
    ## to pass the cuts, if only one number is given only one jet
    ## has to be tagged.)
    bAlgorithm     = cms.string('simpleSecondaryVertexBJetTags'),
    bDiscriminator = cms.vdouble(1.)
)
