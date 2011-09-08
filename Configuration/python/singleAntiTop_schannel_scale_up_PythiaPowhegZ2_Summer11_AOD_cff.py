import FWCore.ParameterSet.Config as cms

#########################################################################################
# Dataset: Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1 #
# Events : 153981 (11 files)                                                            # 
# eff    : 1.0                                                                          #
#########################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/123E016F-12C3-E011-8E74-E0CB4E1A1187.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/14A5550E-10C3-E011-A74D-485B39800BB1.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/28EA23EB-10C3-E011-B671-90E6BA19A240.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/424AA2B7-14C3-E011-B6E9-E0CB4E29C512.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/54E901C8-0CC3-E011-B66E-485B39800B62.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6C7A3BD9-0EC3-E011-9F0F-485B39800B74.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7AFB23F4-0DC3-E011-B122-90E6BA442F41.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9EB1A632-18C3-E011-B270-485B39800BBB.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/ACC81B00-0BC3-E011-B9E4-485B39800B67.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C834894D-13C3-E011-B4B4-0030487CB568.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EA55E67C-0CC3-E011-BB31-90E6BA442F0C.root"

     ] );

secFiles.extend( [
               ] )

