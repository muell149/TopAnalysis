import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A2B27BB2-3E56-E111-B919-485B39800B8D.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/16E9F6EE-3156-E111-9DE0-20CF3027A602.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/209E65C4-6056-E111-958A-001EC9D51CE7.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/264A24AF-4156-E111-B5F5-BCAEC5097203.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3480390E-5256-E111-B83F-E0CB4E55363A.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/1E0E01D7-3A56-E111-A1EE-BCAEC53F6D4E.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2426C739-3556-E111-A69E-20CF30561716.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4236FAA1-3956-E111-8BCB-90E6BA19A21C.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2A3E5872-4D56-E111-A99E-0030487C6A1E.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F2DE6EDB-3756-E111-9E63-20CF3027A598.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/BC4CFAD4-4356-E111-841D-001EC9D8D49F.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/52B978B6-3B56-E111-A640-485B39800B8D.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/74F95361-4456-E111-AF52-001EC9D8D49F.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F82028A5-3F56-E111-B05F-001EC9D8D49F.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8667E12F-4F56-E111-922C-0030487CDAC2.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2AB27773-4056-E111-B7A5-20CF3027A626.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C2689DDC-5356-E111-BE08-0030487CDA4C.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D4792D28-4656-E111-B04B-485B39800BFB.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D6D62506-3456-E111-B8EF-20CF3056171D.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F466FB82-4C56-E111-8C77-0030487CDA66.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F8E9E578-4956-E111-BEA1-0030487CDA66.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A4D4D42F-3056-E111-9993-BCAEC5364CBE.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/98E46256-4A56-E111-BD5F-90E6BA19A25D.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/888534F8-6356-E111-BE7F-20CF305B0509.root' ] );


secFiles.extend( [
               ] )

