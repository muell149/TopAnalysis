import FWCore.ParameterSet.Config as cms

################################################################################################
# Dataset: T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1           #
# Events : 285972 (17 files)                                                                   #
# eff    : 1.0                                                                                 #
################################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/06A9F276-05C3-E011-A304-E0CB4E29C4BB.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1034F581-03C3-E011-84FA-485B39800C2D.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1ACE229B-04C3-E011-83AE-E0CB4EA0A8DB.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/32673A06-08C3-E011-803A-E0CB4E553644.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/56BD90A4-02C3-E011-A687-90E6BA442F41.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/66C4A4A7-06C3-E011-8BA4-E0CB4E29C519.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6E575AED-06C3-E011-A301-90E6BA442F41.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/942D80E6-04C3-E011-989B-E0CB4E29C519.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/96E636BB-FFC2-E011-9235-E0CB4E1A116C.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A67464E8-06C3-E011-9433-485B39800B9B.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AA5A3658-08C3-E011-8A90-E0CB4E1A1185.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D6783A09-04C3-E011-A781-90E6BA0D09CA.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DC68F9E1-02C3-E011-9AAC-E0CB4E29C4C5.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DCEE5575-05C3-E011-82A1-485B39800C32.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E009E855-3CC3-E011-935B-E0CB4E29C4FB.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E86F1E3A-09C3-E011-89F1-485B39800BFD.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EA57FFBD-05C3-E011-A878-90E6BAE8CC08.root"

     ] );

secFiles.extend( [
               ] )

