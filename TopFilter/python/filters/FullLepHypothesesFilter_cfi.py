import FWCore.ParameterSet.Config as cms

filterFullLepHypothesis = cms.EDFilter("FullLepHypothesesFilter",
    hypoKey = cms.InputTag("ttFullLepHypKinSolution","Key"),
    FullLepEvent = cms.InputTag("ttFullLepEvent"),

    ## accept only events with leading jets
    useLeadingJets  = cms.bool(False),
    
    ## cut on the probability weight of the solutions
    weightCut = cms.double(0),
    
    jets = cms.InputTag("hardJets"),
        
    ## b-tagging (if bDisc has two arguments both jets have 
    ## to pass the cuts, if only one number is given only one jet
    ## has to be tagged.)
    bAlgorithm     = cms.string('simpleSecondaryVertexBJetTags'),
    bDiscriminator = cms.vdouble()
)
