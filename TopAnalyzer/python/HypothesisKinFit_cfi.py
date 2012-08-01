import FWCore.ParameterSet.Config as cms

analyzeHypothesisKinFit = cms.EDAnalyzer("HypothesisKinFitAnalyzer",
    ## input collection                             
    src = cms.InputTag("ttSemiLepEvent"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
      ## hypothesis key on reco level
      hypoKey = cms.string("kKinFit"),
      ## lepton flavour in semileptonic event: muon (default) or electron
      lepton = cms.string("muon"),
      ## choose if you want to have a tree
      wantTree = cms.bool(False),
      ## number of jets considered in Kinematic fit
      ## (needed for the classification of permutations)
      maxNJets = cms.int32(4),
      ## number degrees of freedom used to calculate fit probability.
      ## ndof=2 is correct for the kinfit configuration with
      ## fixed W masses, equal top masses and neutrino eta resolution=inf.
      ## use negative value to get the ndof provided by TKinFitter
      ndof = cms.int32(2)
    )
)



