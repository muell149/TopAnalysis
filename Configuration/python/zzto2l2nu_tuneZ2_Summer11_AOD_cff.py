import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/FE4718C2-5F98-E011-8DE4-002354EF3BD0.root',
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/FACEE8CC-9C98-E011-B4F9-00304867C034.root',
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F2ADFF9B-9998-E011-A8EE-001A92971AAA.root',
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/B46C934B-9998-E011-93A9-001A928116FC.root',
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/B009C44E-9A98-E011-A030-002618943856.root',
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/A0C6D2F0-9698-E011-898C-00304867D446.root',
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/9E2E8995-B298-E011-AFD1-002618943945.root',
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/904642C5-9298-E011-AF54-001A92810ACA.root',
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7819050D-9698-E011-94F4-00261894385D.root',
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/6A017914-9198-E011-ADB7-001A928116DE.root',
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/3A1E52F1-B698-E011-88C4-001A92810ACA.root',
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/28AEA81A-E198-E011-A943-002618943939.root',
       '/store/mc/Summer11/ZZTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/1090BA56-C498-E011-B904-002618943856.root' ] );


secFiles.extend( [
               ] )

