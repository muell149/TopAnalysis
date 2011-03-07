import FWCore.ParameterSet.Config as cms

analyzePDFUncertainty = cms.EDAnalyzer("PDFUncertaintyAnalyzer",
    ## input collection                             
    src = cms.InputTag("generator"),
    ## analyzer specific configurables
    analyze   = cms.PSet(
    ## nothing to choose right now
    )
)
