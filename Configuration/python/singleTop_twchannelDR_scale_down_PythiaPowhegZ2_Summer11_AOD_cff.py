import FWCore.ParameterSet.Config as cms

############################################################################################
# Dataset: T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1 #
# Events : 437819 (26 files)                                                               #
# eff    : 1.0                                                                             #
############################################################################################


maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C8A5120-1FC3-E011-A398-E0CB4E29C4DB.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/24114A3E-1AC3-E011-BD3F-E0CB4E19F985.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2656EA70-23C3-E011-81BA-485B39800B65.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/26A127EA-17C3-E011-9D5C-E0CB4E5536BE.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/281B35D7-1EC3-E011-A8A0-003048D2910A.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/28E218FB-1DC3-E011-8110-0030487CD9C8.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2C8A984F-20C3-E011-AC6A-E0CB4E4408E9.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3455214B-19C3-E011-B634-0030487C6A1E.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/38D5C2A2-1EC3-E011-9704-0030487C6A1E.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/407F53F9-1BC3-E011-836F-90E6BA19A22E.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/58FCEB47-18C3-E011-89A6-0030487CDB24.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6E707531-1BC3-E011-8316-0030487CDA66.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/769B00AF-1BC3-E011-BA3D-E0CB4E1A1187.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/86266061-19C3-E011-B01D-E0CB4E1A1169.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8664192C-16C3-E011-834C-E0CB4E29C4FA.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/90EAF936-4FC3-E011-B8AE-E0CB4E1A119E.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/963F47AE-1BC3-E011-B5E0-00261834B51D.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/98648AF8-1BC3-E011-9282-485B39800BBE.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9A03397A-22C3-E011-AB51-003048678A04.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A48C906B-14C3-E011-9EF8-485B39800B8B.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A62A9202-1DC3-E011-A3C0-0030487CDAC2.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C23B0EA6-1BC3-E011-A683-003048678A04.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C8D9B29F-24C3-E011-88FE-003048678A04.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D047B934-18C3-E011-9163-E0CB4E1A1152.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E4022F08-1EC3-E011-B04D-003048D2910A.root",
    "/store/mc/Summer11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FCCB36AE-1BC3-E011-9559-E0CB4E1A1150.root"

     ] );

secFiles.extend( [
               ] )

