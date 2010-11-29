import FWCore.ParameterSet.Config as cms

from TopQuarkAnalysis.TopObjectResolutions.stringResolutions_etEtaPhi_cff import *

analyzeFullHadQCDEstimation = cms.EDAnalyzer("FullHadQCDEstimationAnalyzer",
    ## input collection                             
    src = cms.InputTag("selectedPatJets"),
    ## special parameters for 
    ## QCD background estimation for
    ## fully hadronic ttbar events
    analyze   = cms.PSet(
      ## choose TTree for output instead of histograms, if applicable
      useTree  = cms.bool(False),
      # ------------------------------------------------
      # resolutions used for the kinematic fit
      # ------------------------------------------------
      udscResolutions = udscResolution.functions,
      bResolutions    = bjetResolution.functions
    )
)



