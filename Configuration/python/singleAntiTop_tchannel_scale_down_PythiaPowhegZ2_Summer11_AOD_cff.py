import FWCore.ParameterSet.Config as cms

###########################################################################################
# Dataset: Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1 #
# Events : 565454 (32 files)                                                              #
# eff    : 1.0                                                                            #
###########################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/060257E8-17C3-E011-8C7E-E0CB4E1A114C.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0ADA3CBE-16C3-E011-A906-00261834B586.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1046CF3D-1AC3-E011-96D8-E0CB4E1A118B.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/12D15BBE-16C3-E011-A398-00261834B51D.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3EF644A8-15C3-E011-BFA1-E0CB4E1A1152.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4013624B-18C3-E011-8AA7-0030487CDA66.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/422A976F-14C3-E011-A510-485B39800B65.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4AEFF795-15C3-E011-AE9F-E0CB4E29C4B6.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4E83C0A1-1CC3-E011-83AC-0030487CDA66.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/50F28D0C-19C3-E011-8F32-0030487CDA4C.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/54703862-19C3-E011-8139-90E6BA19A20A.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/78D98A95-15C3-E011-9A56-485B39800BD5.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7A95E23A-14C3-E011-B26D-0030487CDB24.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/805BF409-17C3-E011-9C7C-485B39800BD5.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9E007A01-1DC3-E011-8BC1-0030487CB568.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A40C6F4A-13C3-E011-84FC-E0CB4E1A1172.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A844E0E5-15C3-E011-A6C9-485B39800B9B.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AE04DCF2-19C3-E011-BFB3-485B39800B65.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B83D4BF8-1BC3-E011-BCB7-90E6BA19A203.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B859043B-18C3-E011-BFC0-90E6BA0D09EA.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BE5C83F9-12C3-E011-A51C-E0CB4E29C4FA.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C0E3D1CE-1AC3-E011-84FC-0030487C73D2.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C24EDB6D-14C3-E011-8A82-90E6BA442F04.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C6924D67-1FC3-E011-B0A2-E0CB4E19F9A0.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C8075F12-19C3-E011-BB82-485B39800BFD.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CA475D65-12C3-E011-93D5-485B39800B9B.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E074125B-1AC3-E011-99DE-0030487CDB2C.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC4C8925-18C3-E011-BF1D-0030487C73D2.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC9943E9-10C3-E011-80B3-90E6BA442EEC.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/ECF1273B-5AC3-E011-BC75-E0CB4E55368D.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EE6DC87E-1BC3-E011-AB91-0030487CDA4C.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F6759009-18C3-E011-8BB6-0030487CDAC2.root"

     ] );

secFiles.extend( [
               ] )

