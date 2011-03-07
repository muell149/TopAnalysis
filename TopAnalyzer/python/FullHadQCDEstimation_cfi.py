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
      useTree    = cms.bool(False),
      ## choose b-tagging algorithm and working point to be used
      ## available are the following so far:
      ## 1. TCHEM (TCHE algo @ medium WP)
      ## 2. TCHPT (TCHP algo @ tight WP)
      bTagAlgoWP = cms.string("TCHEM"),
      # ------------------------------------------------
      # resolutions used for the kinematic fit
      # ------------------------------------------------
      udscResolutions = udscResolution.functions,
      bResolutions    = bjetResolution.functions
    )
)



