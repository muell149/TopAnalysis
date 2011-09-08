import FWCore.ParameterSet.Config as cms

###############################################################################################
# Dataset: Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1 #
# Events : 437863 (27 files)                                                                  # 
# eff    : 1.0                                                                                #
###############################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0E1F3371-1FC3-E011-81EC-0030487C73D4.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/121E1DF7-1FC3-E011-8558-0030487C6A32.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/18B44740-1AC3-E011-B292-90E6BA19A240.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C0D43B6-1EC3-E011-8ED2-0030487CDA66.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/20CE6E56-24C3-E011-A690-E0CB4EA0A8EC.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/22267B94-25C3-E011-8DE4-0030487CDAF6.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/229B3467-15C3-E011-A601-E0CB4E1A1152.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/264B8F20-25C3-E011-99D9-0030487CB568.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/28DDF0FA-1DC3-E011-BF79-90E6BA442EEE.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3EF000FB-1BC3-E011-B285-90E6BA0D09EA.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/424878B8-21C3-E011-9D09-485B39800B65.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5086DD8C-1EC3-E011-862B-E0CB4E5536BE.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/520BC6FA-1DC3-E011-B4FE-90E6BAE8CC1F.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/70B3518E-29C3-E011-B32E-0030487CDA66.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/72728E91-19C3-E011-8016-003048678A04.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7A055C56-23C3-E011-99C0-0030487C6A1E.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/80FE7DB0-1BC3-E011-B3BA-E0CB4E29C504.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8A340673-22C3-E011-8F68-0030487CDB2C.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/94BC965A-27C3-E011-ADD5-0030487CD6A6.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AAACAB56-24C3-E011-B5D8-485B39800BBB.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AAF473E2-32C3-E011-A606-90E6BA442EEE.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B001FA60-2AC3-E011-B3AE-003048D29312.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C264635D-27C3-E011-9F56-003048D293B4.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DEFEF3B3-1BC3-E011-8BEC-485B39800B94.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC2A7E92-19C3-E011-A2ED-0030487CDB2C.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F0579834-18C3-E011-834E-E0CB4E29C4D9.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FC109DE8-17C3-E011-BBB2-90E6BA0D09EA.root"

     ] );

secFiles.extend( [
               ] )

