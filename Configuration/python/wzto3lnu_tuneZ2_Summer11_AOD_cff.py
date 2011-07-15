import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/FA03D682-8D9D-E011-BCCD-0026189438C1.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F09BBFF3-449E-E011-88BD-0026189438C0.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/EA9EDAA5-CB9D-E011-901D-003048679076.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/D69407EB-8B9D-E011-96FF-001A92810A98.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/D63DAB0D-B39D-E011-9DB7-0018F3D096BA.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/BE039889-B09D-E011-891B-001BFCDBD160.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/90E0B319-889D-E011-B784-0026189438AD.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/82C2D94A-A89D-E011-8A29-00261894386D.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7C080F32-A19D-E011-BEE5-003048679296.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/56E25FBD-4C9E-E011-9DCA-00261894398D.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/485E2549-CA9D-E011-B95C-001A92810AE2.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/3AF236E1-A49D-E011-A2E1-00261894388B.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/304ADAC0-979D-E011-A272-003048679296.root',
       '/store/mc/Summer11/WZTo3LNu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/06E4F2A8-9A9D-E011-BBCD-001A92971AD0.root' ] );


secFiles.extend( [
               ] )

