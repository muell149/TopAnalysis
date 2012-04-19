import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/1C59B64E-5656-E111-8DB6-001EC9D81A4E.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/224D05BE-5256-E111-90D3-0030487CDA4C.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3A6DA6E9-4D56-E111-85A3-E0CB4EA0A934.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/44BA3F18-5C56-E111-9092-001EC9D8B55E.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/506071AF-3656-E111-BE80-20CF3027A598.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2CF6D231-5456-E111-BD13-001EC9D7FA1C.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7EFC980A-6C56-E111-B0E7-20CF305B0534.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/40D6409E-3F56-E111-A307-E0CB4E553663.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8EE6939B-4556-E111-87B4-001EC9D8D49F.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/9A4E10E5-4256-E111-B24D-90E6BA19A25D.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/443DDE71-4F56-E111-ABB2-0030487CDA66.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A4150B08-3156-E111-BE11-20CF3027A629.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/44CBAE6D-3B56-E111-AC93-20CF3027A631.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A6955EF8-4756-E111-B48D-0030487CDAC2.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/728B97B3-4156-E111-BB5E-001EC9D8D49F.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/AA681425-3E56-E111-8C43-485B39800B8D.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/88B28037-3D56-E111-AF4F-90E6BA19A205.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A0D9352C-4056-E111-BE3A-485B39800B8D.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/CAC717A3-4256-E111-9E42-001EC9D8D49F.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D6B1238A-4056-E111-9FFD-E0CB4E553663.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/E80B7828-4656-E111-AFAD-E0CB4E29C4D2.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A4CCD73B-4C56-E111-99E4-0030487CDAC2.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A89DA4DE-4856-E111-A74A-001EC9D80F9A.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/AEFDD282-3856-E111-97F4-20CF3056171D.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C620F457-4D56-E111-9C96-E0CB4EA0A934.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F0EFC03B-4E56-E111-88B3-90E6BA0D09AD.root' ] );


secFiles.extend( [
               ] )

