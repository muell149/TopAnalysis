import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/02B75968-5556-E111-BCF0-001EC9D81A4E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/06CF50D0-4356-E111-BD3B-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/0E23F47C-6056-E111-B22E-001E4F3F3556.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/18E2C852-5656-E111-9EF0-0030487CDA66.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/20090313-5556-E111-8C94-00261834B569.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2A8F2747-5856-E111-B425-0030487CDA4C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3C6792EA-5056-E111-AA6E-0030487CDA4C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/18FFF412-6156-E111-88FC-001E4F3F228E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/22CBF31F-5756-E111-9E43-20CF3056171D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/5EA3AD99-5056-E111-9636-E0CB4E55363A.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/30AC82A4-4A56-E111-8536-0030487C73D4.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/6C49229B-BC56-E111-B455-485B39800BD7.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3E80CD9C-5C56-E111-B226-001EC9D51CE7.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7045D337-6556-E111-A192-20CF305B0534.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/44CDA687-4056-E111-BEC7-BCAEC5097203.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/74A7ECC5-5C56-E111-8E08-001EC9D8B55E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/44EB4647-5956-E111-A57E-001EC9D51CE7.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/607DE78F-5356-E111-AE68-001EC9D7FA1C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/6E1AA42E-4D56-E111-81DE-0030487CDAC2.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/969AFD85-6C56-E111-84A3-20CF305B0534.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/9A0E252C-5456-E111-921C-E0CB4E1A1176.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/9C7049FA-5256-E111-BFFD-001EC9D7FA1C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/704AB04A-3456-E111-8C2B-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/AAB2FCE9-5A56-E111-A8B6-001EC9D7F203.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B4E65235-6256-E111-849D-E0CB4E553640.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/80F3333A-4E56-E111-B25B-E0CB4E55363A.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B8D8C4ED-5A56-E111-A105-001EC9D8B55E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/BCB59EDE-4556-E111-9827-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/845E72E2-4856-E111-BEFE-0030487CDA66.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D4FC16A8-5E56-E111-89F9-001E4F3F228E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D81560E1-4B56-E111-8842-0030487CDA66.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/DC4BE3E9-5856-E111-A3A4-001EC9D7F203.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/84EB20D3-4E56-E111-AF8D-0030487CDA66.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/E4FEB937-5156-E111-8361-0030487CDA66.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A4ADCE25-4956-E111-BB62-002618FDA18F.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B8D7CBA8-5856-E111-84FD-001EC9D282A8.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C0BA5636-6956-E111-B449-20CF305B0534.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/E006768B-4C56-E111-97D8-0030487C6A1E.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/FC4D2E10-5256-E111-8E38-90E6BA0D09AD.root' ] );


secFiles.extend( [
               ] )

