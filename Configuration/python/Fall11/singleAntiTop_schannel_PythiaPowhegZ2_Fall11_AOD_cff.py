import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       ## 11 files
       '/store/mc/Fall11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/221D32A1-B1F9-E011-8573-00261894386F.root',
       '/store/mc/Fall11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/466A0042-7CF9-E011-85BD-002354EF3BD0.root',
       '/store/mc/Fall11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/46B53FDC-6BF9-E011-A378-0018F3D096EA.root',
       '/store/mc/Fall11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4C6908C2-53F9-E011-B278-0026189438FD.root',
       '/store/mc/Fall11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/6401B243-5AF9-E011-8BF2-0018F3D096E0.root',
       '/store/mc/Fall11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/72108A34-51F9-E011-9B96-003048D15D22.root',
       '/store/mc/Fall11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/943B3F5A-6FF9-E011-8801-003048679046.root',
       '/store/mc/Fall11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C8ACC78F-66F9-E011-99D2-001A92811718.root',
       '/store/mc/Fall11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/E05D2765-59F9-E011-84B8-0026189438B8.root',
       '/store/mc/Fall11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F058FD51-4FF9-E011-8E7D-002618943874.root',
       '/store/mc/Fall11/Tbar_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F4D77C89-79F9-E011-82E8-001A92811746.root' ] );


secFiles.extend( [
               ] )

