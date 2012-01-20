import FWCore.ParameterSet.Config as cms

#####################################################################################
# Dataset: /TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM #
# Events : 3701947                                                                  # 
# eff    : 1.0                                                                      # 
#####################################################################################


maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource", fileNames = cms.untracked.vstring(   
'file:/data/group/top/18202867-1D98-E011-A384-0018F3D09600.root'
    ) 
)
