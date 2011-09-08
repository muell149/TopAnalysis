import FWCore.ParameterSet.Config as cms

#############################################################################################
# Dataset: Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1 #
# Events : 437798 (27 files)                                                                #
# eff    : 1.0                                                                              #
#############################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1CC4360B-06C3-E011-8DA6-485B39800BED.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2EA3E13E-0EC3-E011-ABAA-E0CB4E19F97C.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4283609F-08C3-E011-80A2-485B39800C16.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4E3FC52C-03C3-E011-A4F1-E0CB4E1A11A1.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/561D0AFF-0AC3-E011-94FC-E0CB4E1A116C.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/58143BA7-06C3-E011-A14A-E0CB4E1A11A1.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/60FD5951-10C3-E011-A9DE-E0CB4E1A11A4.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/64FFEF62-12C3-E011-A650-485B39800BD7.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6CF81284-09C3-E011-86FA-E0CB4E19F990.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/72E88EE7-06C3-E011-B375-90E6BA0D09DC.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/740EAB1D-0AC3-E011-A4B7-E0CB4E1A1182.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9291D23C-09C3-E011-B23A-E0CB4E19F959.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B0327AF4-0DC3-E011-A124-485B39800B9B.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B4F65A10-08C3-E011-8A0A-485B39800B66.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BC577C57-04C3-E011-9AB0-485B39800B65.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BE8FC671-01C3-E011-9A14-90E6BA0D09B0.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C20326CB-0CC3-E011-9F37-E0CB4E29C4F1.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C2EF6343-0BC3-E011-86F1-485B39800C0C.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C6260976-0CC3-E011-83C8-00261834B5D2.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C83C0359-08C3-E011-A9DA-E0CB4E29C4BA.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C8CE0AE1-04C3-E011-81CC-E0CB4E19F982.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CE63E96B-14C3-E011-835B-E0CB4E19F961.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E2A6D8B6-0FC3-E011-9488-E0CB4E553657.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EE22047A-07C3-E011-AA91-90E6BA19A25A.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EE85EE79-05C3-E011-B7EA-485B39800C0F.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FCC1220D-0DC3-E011-8141-485B39800BD1.root",
	"/store/mc/Summer11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FE4466CF-0EC3-E011-A076-E0CB4E29C4E7.root"

     ] );

secFiles.extend( [
               ] )

