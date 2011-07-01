import FWCore.ParameterSet.Config as cms

################################################################################
# Dataset: /WW_TuneZ2_7TeV_pythia6_tauola/Summer11-PU_S4_START42_V11-v1/AODSIM #
# Events : 4225916                                                             #
# eff    : 1.0                                                                 #
################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource", fileNames = cms.untracked.vstring( *(


    ) )
)
