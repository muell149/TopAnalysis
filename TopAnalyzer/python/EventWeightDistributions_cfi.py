import FWCore.ParameterSet.Config as cms

# ============================
#  Default Configuration
# ============================

EventWeightDistributions = cms.EDAnalyzer('EventWeightAnalyzer',
                                           EventWeightSrc = cms.InputTag("EventWeightMC"),
                                         )
