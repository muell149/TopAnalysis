import FWCore.ParameterSet.Config as cms

plot = cms.PSet(
## indicate verbosity level for debugging
verbose = cms.bool(True),
## luminosity in pb-1
lumi = cms.double(10),
## vector of input samples
inputs = cms.VPSet(
    cms.PSet(
    ## input file
    file  = cms.string('file:~goerner/semileptonic387/diffXSecFromSignal/analysisRootFiles/muonDiffXSecSigMadD6TFall10PF.root'),
    ## label in legend
    label = cms.string('Top Signal'),
    ## normalization scale (expected to be to 1pb)
    scale = cms.double(1.0)
    ),
    cms.PSet(
    ## input file
    file  = cms.string('file:~goerner/semileptonic387/diffXSecFromSignal/analysisRootFiles/muonDiffXSecBkgMadD6TFall10PF.root'),
    ## label in legend
    label = cms.string('Top Other'),
    ## normalization scale (expected to be to 1pb)
    scale = cms.double(1.0)
    ),
),
## histograms of interest
hists = cms.vstring('centralJetKinematics/pt','centralJetKinematics/eta'),
)
