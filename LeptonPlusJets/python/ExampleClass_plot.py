import FWCore.ParameterSet.Config as cms

from TopAnalysis.LeptonPlusJets.samples_plt import topSignal, topBG

plot = cms.PSet(
    ## indicate verbosity level for debugging
    verbose = cms.bool(True),
    ## luminosity in pb-1
    lumi    = cms.double(10),
    ## vector of input samples
    inputs  = cms.VPSet( topSignal, topBG ),
    ## histograms of interest
    hists   = cms.vstring('centralJetKinematics/pt','centralJetKinematics/eta', 'test/myHist'),
    )
