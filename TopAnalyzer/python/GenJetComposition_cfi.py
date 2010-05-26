import FWCore.ParameterSet.Config as cms

analyzeGenJetComposition= cms.EDAnalyzer("GenJetCompositionAnalyzer",
    ## input collection                             
    src = cms.InputTag("ak5GenJets"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
    ## index for the leading, 2. leading, 3. leading jet
    ## that will be considered when filling histograms
    ## 0 means leading jet
    ## -1 means all jets
    index = cms.int32(-1)
    )
)
