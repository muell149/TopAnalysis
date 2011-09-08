import FWCore.ParameterSet.Config as cms

###########################################################################################
# Dataset: Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1 #
# Events : 153971 (11 files)                                                              #
# eff    : 1.0                                                                            #
###########################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/38B8E9C9-01C3-E011-845E-90E6BA19A24C.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/64DE2AEB-06C3-E011-BEA3-E0CB4E19F990.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7465D4F8-12C3-E011-AA7A-485B39800C0C.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7E6793E7-FEC2-E011-90A0-485B39800B83.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9C5B94F7-0DC3-E011-AFEC-90E6BA442F1C.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B0981F35-17C3-E011-A2AE-0030487CDAC6.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C8AC03B9-0AC3-E011-96C1-90E6BA442F30.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D430E833-0CC3-E011-A92C-E0CB4E1A1152.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E8F2EF6A-10C3-E011-9017-485B39800B65.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC353125-0FC3-E011-B797-E0CB4E19F958.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEF5FA79-05C3-E011-8247-E0CB4E1A1197.root"

     ] );

secFiles.extend( [
               ] )

