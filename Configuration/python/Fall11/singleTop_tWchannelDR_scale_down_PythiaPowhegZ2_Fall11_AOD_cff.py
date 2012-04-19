import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/08C91ABD-3B56-E111-982F-001EC9D8D49F.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/0C4E4916-4456-E111-8985-485B39800BFB.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/0E26F6BC-5256-E111-B4BC-0030487CDA66.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/168C42C6-5756-E111-BAC5-0030487CDA4C.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/1E450740-4E56-E111-A30F-001EC9D8D079.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/225B9416-4456-E111-B35C-E0CB4E1A117D.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/26C29B80-3556-E111-A33E-20CF3027A626.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2CC33DF0-5856-E111-BB5E-001EC9D8B55E.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2EE3D273-2D56-E111-B654-20CF3027A596.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/34EA0D24-4956-E111-8B9F-20CF3027A626.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/42D3431E-3B56-E111-BA4F-001EC9D8D49F.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/48C3011C-5C56-E111-B449-001EC9D51CE7.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4C0F0D34-4356-E111-A8EC-001EC9D7DF62.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/5C83B882-3856-E111-9C53-20CF3027A626.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/6410EE17-6F56-E111-9385-20CF305B0534.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/64691D9A-5056-E111-9DBD-90E6BA0D09AD.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/84E93C58-5056-E111-AB8A-E0CB4EA0A934.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/864D659F-3956-E111-AE02-20CF3056171D.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/88D40B12-4756-E111-99AF-0030487CDAC2.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8A9BDE95-4556-E111-97A1-E0CB4E1A117D.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8E2CC90D-3F56-E111-85D2-90E6BA19A205.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8E5F1B9C-3F56-E111-A17A-20CF3027A626.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/904F6E7C-4C56-E111-8D8F-001EC9D7FA1C.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/9063EF37-5156-E111-8BAD-0030487CDAC2.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/947062BD-3356-E111-8DA7-20CF30561711.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/98EC2DD8-4056-E111-A063-90E6BA19A25D.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/9AD2B9C7-6956-E111-8147-20CF305B0534.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B0EF4E9E-4D56-E111-BDF8-E0CB4E55363A.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/BAEBD6AE-3656-E111-A8F9-20CF3056171D.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C00602E3-4256-E111-AD27-485B39800BFB.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C0C3E5E5-3F56-E111-9F8E-90E6BA19A257.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C0D31E55-3C56-E111-BA78-001EC9D8D49F.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C601170D-4E56-E111-95F6-0030487CDAC2.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C6BDD479-3056-E111-A8CE-20CF3027A5C9.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C8D711FC-4A56-E111-AFDB-0030487CDA66.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D095D003-3C56-E111-A267-20CF3027A626.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D46319DC-4856-E111-8436-001EC9D7F1E7.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/DC926128-4656-E111-8FA0-E0CB4E1A117D.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/EACDCE46-3A56-E111-AD9C-20CF3027A626.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F05BB1AC-4456-E111-BCBB-E0CB4E1A117D.root',
       '/store/mc/Fall11/T_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F4CA8516-5256-E111-9A2E-001EC9D7FA1C.root' ] );


secFiles.extend( [
               ] )

