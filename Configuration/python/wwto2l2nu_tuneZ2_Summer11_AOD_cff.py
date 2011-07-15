import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/F00F18C9-B29D-E011-9DB9-0018F3D096AE.root',
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/E8B866F0-739D-E011-8335-001A928116D8.root',
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/E0349F24-709D-E011-AAE3-0018F3D096DC.root',
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/D86A3222-669D-E011-9108-00304867BED8.root',
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/C0E13D9D-719D-E011-BCE7-001BFCDBD11E.root',
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/98A2C68D-699D-E011-834B-00304867918A.root',
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7CCD79FA-6C9D-E011-9BB3-002618943966.root',
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/7C66F5C0-8C9D-E011-B4DF-0018F3D0962C.root',
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/667345D6-679D-E011-9BF6-001A92971B8A.root',
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/5C46BA7A-6C9D-E011-A210-003048679076.root',
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/282B5866-969D-E011-8C38-0018F3D09614.root',
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/12DE108D-6F9D-E011-91E4-002354EF3BE3.root',
       '/store/mc/Summer11/WWTo2L2Nu_TuneZ2_7TeV_pythia6_tauola/AODSIM/PU_S4_START42_V11-v1/0000/0EF8F163-6A9D-E011-B7EE-002618943821.root' ] );


secFiles.extend( [
               ] )

