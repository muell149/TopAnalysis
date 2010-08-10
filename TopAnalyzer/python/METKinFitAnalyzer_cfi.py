import FWCore.ParameterSet.Config as cms

analyzeMETKinFit = cms.EDAnalyzer("METKinFitAnalyzer",
   METSrc = cms.InputTag('patMETs'),
   JetSrc = cms.InputTag('selectedPatJets'),
   FitSrc = cms.InputTag('ttFullHadEvent'),
)



