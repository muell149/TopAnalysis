import FWCore.ParameterSet.Config as cms

################################################################################################
# Dataset: /T_TuneZ2_s-channel_7TeV-powheg-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM         #                                         
# Events : 259971                                                                              #
# xSec   : 2.72 (NLO MCFM)                                                                     #
# eff    : 1.0                                                                                 #
################################################################################################


maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource", fileNames = cms.untracked.vstring( *(

"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/001A7F2D-B2B8-E011-90EB-E0CB4E1A1185.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2CFF38DD-B4B8-E011-A310-003048D29312.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/467EDB6B-BDB8-E011-B20B-0030487E3026.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/58F2AC35-BAB8-E011-8B80-90E6BA442EEE.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/660A8D15-BBB8-E011-ADB2-E0CB4E29C51B.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6676C69C-C0B8-E011-BA7D-003048678A04.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/74C06A35-B8B8-E011-B0C1-E0CB4E1A1152.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7675D6A2-B9B8-E011-96F4-0030487CDB2C.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8007FC1C-B0B8-E011-867B-485B39800C10.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/92D2E18F-B1B8-E011-B7BA-90E6BA442F05.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9A1C54EA-B5B8-E011-8667-90E6BA442EF1.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A054DDCA-B8B8-E011-8958-E0CB4E1A1167.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C618A8BE-B5B8-E011-BE68-0030487CDAF6.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D0D03613-06B9-E011-A529-001EC9D7F68B.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D455A9FD-BBB8-E011-A4D7-0030487CDAF6.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E04B1F5D-B7B8-E011-A42A-E0CB4E1A1152.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E442BFD8-09B9-E011-B90C-E0CB4E55363D.root",
"/store/mc/Summer11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC712E07-B3B8-E011-AA71-0030487E3026.root"

    ) )
)
