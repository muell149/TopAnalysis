import FWCore.ParameterSet.Config as cms

topSignal = cms.PSet(
    ## input file
    file  = cms.string('file:~goerner/semileptonic387/diffXSecFromSignal/analysisRootFiles/muonDiffXSecSigMadD6TFall10PF.root'),
    ## label in legend
    label = cms.string('Top Signal'),
    ## normalization scale (expected to be to 1pb) [optional]
    scale = cms.double(1.0),
    ## the following block of paramters is completely optinal
    fillColor   = cms.int(1),
    fillStyle   = cms.int(1),
    lineColor   = cms.int(1),
    lineStyle   = cms.int(1),
    markerColor = cms.int(1),
    markerStyle = cms.int(1),
    )

topBG     = cms.PSet(
    ## input file
    file  = cms.string('file:~goerner/semileptonic387/diffXSecFromSignal/analysisRootFiles/muonDiffXSecBkgMadD6TFall10PF.root'),
    ## label in legend
    label = cms.string('Top Other'),
    ## normalization scale (expected to be to 1pb)
    scale = cms.double(1.0)
    )
