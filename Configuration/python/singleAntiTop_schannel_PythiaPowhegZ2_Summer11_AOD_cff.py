import FWCore.ParameterSet.Config as cms

################################################################################################
# Dataset: /Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM      #                                         
# Events : 137980                                                                              #
# xSec   : 1.49 (NLO MCFM)                                                                     #
# eff    : 1.0                                                                                 #
################################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource", fileNames = cms.untracked.vstring( *(
'/store/mc/Summer11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D8E8569C-1DAB-E011-A5BD-002618943896.root',
'/store/mc/Summer11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C83ED275-1EAB-E011-8B1D-0026189438CF.root',
'/store/mc/Summer11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B22E3B06-23AB-E011-8DC1-001A9281170C.root',
'/store/mc/Summer11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8E267041-1BAB-E011-BFB7-0030486790BE.root',
'/store/mc/Summer11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7A98780F-14AB-E011-8EE6-00261894387A.root',
'/store/mc/Summer11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/46BC7F9B-1DAB-E011-A5CB-0026189438A2.root',
'/store/mc/Summer11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/42D8A5CB-86AB-E011-BD3D-0026189437EB.root',
'/store/mc/Summer11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3A59BE07-14AB-E011-82F3-002618943913.root',
'/store/mc/Summer11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1E3A3CC9-14AB-E011-9FAF-003048D15E2C.root'
    ) )
)
