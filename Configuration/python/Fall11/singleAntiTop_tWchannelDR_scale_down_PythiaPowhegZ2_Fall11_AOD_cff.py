import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/1CE99261-4A56-E111-9106-0030487CDA66.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/04BF6E31-4056-E111-8F61-001EC9D8D49F.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3CCA2629-4356-E111-9883-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/10F964D6-4056-E111-BCB4-001EC9D8D49F.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/160DE880-3556-E111-BC1F-20CF3056171D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/466E3BDB-3756-E111-AD40-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4849920E-3F56-E111-A29A-001EC9D8D49F.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/34BBFDD5-3A56-E111-B942-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3A3D7B5D-4456-E111-A1C9-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/520024E1-4B56-E111-A0E7-0030487C6A1E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3CFC1659-4B56-E111-9092-0030487C73D4.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4E87FEC3-3D56-E111-A79E-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3E53C31D-4F56-E111-9DDC-E0CB4EA0A934.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/5EEA4AF6-4156-E111-9B50-485B39800B8D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/783E8B02-4B56-E111-9433-0030487C6A1E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/785BCDBD-3056-E111-891E-20CF30561726.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/60BD91AE-3656-E111-8A4B-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/663B7DCF-2856-E111-857B-20CF305B053E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/66D9A8E7-3C56-E111-9682-BCAEC53F6D4E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8251DB4C-3456-E111-8B55-20CF30561711.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8286E87F-4656-E111-9617-001EC9D7F1E7.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/74775A91-5356-E111-9FB7-E0CB4EA0A8FC.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/88887B24-3E56-E111-AB96-BCAEC5097203.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7C39BA8A-4E56-E111-AEB9-001EC9D7FA1C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/94051D81-2A56-E111-B608-90E6BA0D09B0.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/982722F2-3856-E111-AA91-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/9C025D9C-4256-E111-82D4-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A4C862ED-3156-E111-A0AE-20CF30561716.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7C4A3416-3356-E111-93BE-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7E1B6D11-3656-E111-9C54-20CF30561716.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/82A17D87-6B56-E111-9B64-20CF305B0534.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/BC35E18A-2256-E111-8196-BCAEC54B302D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D621F3C2-5456-E111-B141-20CF3056171D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/DE3F1219-4156-E111-B0AE-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/9090AC5B-3956-E111-B69A-20CF305B057E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A68FD6D8-5956-E111-A372-001EC9D7F203.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/AC00C190-2C56-E111-B367-90E6BA0D09B0.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B22ED083-5F56-E111-8E33-001EC9D51CE7.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/E0421613-3956-E111-99B5-485B39800B8D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/EC07BC6C-3B56-E111-9014-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F67018CE-3256-E111-9AE1-20CF30561716.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F82DC513-4A56-E111-A6B6-0030487C73D4.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/FA6BA06B-4F56-E111-8A2E-90E6BA0D09AD.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/FE8D1934-3D56-E111-9355-20CF3027A626.root' ] );


secFiles.extend( [
               ] )

