import FWCore.ParameterSet.Config as cms

filterRunRange = cms.EDFilter("RunRangeFilter",
                              minRunNumber =  cms.untracked.uint32(0),
                              maxRunNumber =  cms.untracked.uint32(0)
                              )
