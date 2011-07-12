import FWCore.ParameterSet.Config as cms

################################################################################################
# Dataset: /T_TuneZ2_s-channel_7TeV-powheg-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM         #                                         
# Events :                                                                                     #
# xSec   : 2.72 (NLO MCFM)                                                                     #
# eff    : 1.0                                                                                 #
################################################################################################


maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource", fileNames = cms.untracked.vstring( *(

    ) )
)
