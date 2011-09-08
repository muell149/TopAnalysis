import FWCore.ParameterSet.Config as cms

#########################################################################################
# Dataset: Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1 #
# Events : 565520 (33 files)                                                            #
# eff    : 1.0                                                                          #
#########################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
	
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/066B2DFC-0AC3-E011-8A5B-90E6BA19A23E.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0CD498D7-0EC3-E011-8C98-E0CB4E55367D.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1283AFF5-10C3-E011-9D4B-90E6BA442EFA.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/18C882F8-12C3-E011-BDE7-E0CB4E1A116D.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C814E83-09C3-E011-BF26-90E6BA19A258.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3C69A17F-07C3-E011-B39C-E0CB4E1A11A1.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4ADE2A60-10C3-E011-B2CF-90E6BA442F0F.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/50F04B16-12C3-E011-B8D5-E0CB4E19F9A1.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/54193BBB-0FC3-E011-960F-E0CB4E1A1150.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/54ABA1CA-11C3-E011-9CFB-485B39800BB9.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5A671ACC-0CC3-E011-8D29-E0CB4E29C4B6.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/62FC4E4C-0BC3-E011-B14B-90E6BA442F41.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/66C089DC-13C3-E011-A91C-0030487CB568.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/68115E90-0BC3-E011-B24F-E0CB4E29C512.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/687F52F4-0DC3-E011-956C-485B39800B65.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6CA768FB-0AC3-E011-AE06-90E6BA0D09BB.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/70C67E2F-0CC3-E011-8771-E0CB4E1A11A1.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/72DBE59A-04C3-E011-B05F-90E6BA0D09BB.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7ADB7B5F-10C3-E011-B075-E0CB4E29C51D.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AE9318D8-0EC3-E011-B559-90E6BA442F1E.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B0F2C7D1-09C3-E011-A144-90E6BA19A232.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BA102DA0-08C3-E011-8503-E0CB4E19F965.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BCC532CB-0CC3-E011-AF4B-E0CB4E1A1174.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BCD47CE6-06C3-E011-AD91-E0CB4E55363B.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C21F7807-17C3-E011-92A8-E0CB4E1A1189.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C2FD0A21-0FC3-E011-AD5B-485B39800BFD.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C8F628A6-0DC3-E011-83B9-E0CB4E1A1150.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CC061ECB-11C3-E011-A0F0-485B39800B90.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D4ADA15B-08C3-E011-9A2F-E0CB4E1A1144.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DA3C511F-0AC3-E011-9F50-485B39800B73.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC81CC0A-06C3-E011-8009-E0CB4E1A1144.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F6096B40-0EC3-E011-8255-90E6BA442EFA.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FADB9B91-0BC3-E011-B1E7-90E6BA442F32.root"

     ] );

secFiles.extend( [
               ] )

