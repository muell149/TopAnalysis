import FWCore.ParameterSet.Config as cms

########################################################################################
# Dataset: T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1 #      
# Events : 285602 (18 files)                                                           #
# eff    : 1.0                                                                         #
########################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/02405BE7-43C3-E011-A9C0-E0CB4E1A1181.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/02F26E3F-26C3-E011-BD4F-0030487C73D4.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/06BDE538-23C3-E011-8C30-0030487CDA4C.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1E89EBEE-41C3-E011-9A1C-0019BB3FF3A6.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/34591DB1-62C3-E011-AD72-E0CB4E1A1169.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/569D40D2-3AC3-E011-8B6E-001A4BA5FF74.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/56BD7FA9-31C3-E011-A64C-90E6BA442F24.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/58E19BF7-37C3-E011-A060-003048D29312.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/72B37A97-27C3-E011-A723-003048D2910A.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/86633678-2BC3-E011-8935-003048D293B4.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8684C37D-40C3-E011-9626-E0CB4E553646.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8870E36A-2CC3-E011-A745-003048D29312.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/92E71350-45C3-E011-BF1E-E0CB4E553639.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9622791B-3FC3-E011-8ED0-90E6BAE8CC20.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A064860E-3EC3-E011-84D4-0019BB3FF3A6.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C2133392-28C3-E011-B166-003048678948.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C2B2C811-2EC3-E011-947A-003048D2910A.root",
	"/store/mc/Summer11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D6D91CBF-3CC3-E011-9937-E0CB4E29C4FB.root"

     ] );

secFiles.extend( [
               ] )

