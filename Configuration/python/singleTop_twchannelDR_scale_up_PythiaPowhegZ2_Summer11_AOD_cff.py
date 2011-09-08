import FWCore.ParameterSet.Config as cms

##########################################################################################
# Dataset: T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1 #
# Events : 437736 (28 files)                                                             # 
# eff    : 1.0                                                                           #
##########################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0011E121-14C3-E011-BF95-90E6BA442EF1.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/00D1F9B9-16C3-E011-9AC0-E0CB4E4408EF.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/00E8906D-14C3-E011-B246-485B39800BD7.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0A3133C4-18C3-E011-86E1-00261834B51D.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1083D991-15C3-E011-9EA3-E0CB4E29C4FA.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C31E06D-14C3-E011-9832-485B39800BC0.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1E4CCD60-12C3-E011-9BFE-E0CB4E29C4B6.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/409C9661-12C3-E011-B380-E0CB4E29C4F9.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/423A3CE1-15C3-E011-9740-E0CB4E29C4F9.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/44AC8E23-17C3-E011-B61B-0030487C73D2.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/46EC9E95-20C3-E011-B393-485B39800C08.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4A390167-1EC3-E011-B547-0030487CDB24.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4ED6D8E7-10C3-E011-BCC0-E0CB4E29C514.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5A8557CB-11C3-E011-B37B-90E6BA442F11.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5CF89546-15C3-E011-A23B-E0CB4E1A1183.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/60FF294A-13C3-E011-9A78-485B39800BB9.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6A08C83E-13C3-E011-B83E-90E6BA19A240.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/70C40150-15C3-E011-9E4C-0030487C73D4.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/76C6C2CB-11C3-E011-B883-90E6BA19A22E.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/843F1C3A-18C3-E011-A2AC-E0CB4E1A1150.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B805D8F7-12C3-E011-9F6F-485B39800BBB.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CA926FA6-14C3-E011-8B7A-0030487CDAF6.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D0A46F5B-10C3-E011-B5A2-E0CB4E19F99B.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D600D3A6-13C3-E011-A44A-90E6BA19A240.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D8E9DEB8-0FC3-E011-A8A4-E0CB4E1A1188.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DAE74072-12C3-E011-8A2D-0030487CB568.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E62821B1-14C3-E011-958C-E0CB4E19F989.root",
	"/store/mc/Summer11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC44375A-15C3-E011-B4E7-0030487C6A1E.root"

     ] );

secFiles.extend( [
               ] )

