import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/16A33D84-3256-E111-B952-20CF3056171D.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/20119B24-4956-E111-B9B5-485B39800BFB.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/32C98BD1-4056-E111-BB0C-485B39800B8D.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/10C4822F-4F56-E111-BBCD-0030487C6A1E.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/1AB5524A-4B56-E111-9613-E0CB4E55363A.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/204B7D60-5556-E111-A07D-E0CB4E1A1176.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/5C2D1E53-5356-E111-A713-0030487CDA66.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/26858E21-4D56-E111-B931-0030487CDA66.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/64BDECAA-5856-E111-8867-001EC9D51CE7.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3A604BDE-4856-E111-8D91-001EC9D8D49F.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7269F951-3156-E111-8BF2-20CF30561726.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3AAD702B-4356-E111-AE3E-E0CB4E1A117D.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8A1F0719-5256-E111-AFD0-0030487CDA66.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/905F26F2-5E56-E111-8DD1-001EC9D51CE7.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/9E5D718D-4E56-E111-A320-0030487C6A1E.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4A16B139-6256-E111-BB58-001EC9D51CE7.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/62F2715E-3356-E111-A627-20CF30561716.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/70561AE1-4556-E111-9E92-002618FDA18F.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/74B56C39-5156-E111-B728-0030487C6A1E.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B01D754B-6A56-E111-A5D5-20CF305B0534.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A2396212-5D56-E111-870B-001E4F3F3556.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B42FE682-3856-E111-A46D-20CF3027A598.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/BC037C52-5656-E111-969F-001EC9D8A8D8.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A830784B-6156-E111-972F-001EC9D51CE7.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C691DCF0-3C56-E111-B831-001EC9D8D49F.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/CA502DFA-4756-E111-B6FE-0030487CDA66.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D2989C17-5C56-E111-9F99-001EC9D7F203.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A8BD12FA-5856-E111-ADD8-001EC9D825B5.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D8337766-5056-E111-A8A7-001EC9D8D079.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F0F93164-4156-E111-9873-485B39800B8D.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/AE31C30B-5E56-E111-9C50-001EC9D51CE7.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B0FDBE0A-6D56-E111-9EDF-20CF305B0534.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C428CBEA-5A56-E111-B01A-001EC9D51CE7.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D6075BAF-4756-E111-ACE6-001EC9D8D49F.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F25A8A96-5356-E111-9F08-001E4F2F0D1E.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F84A9B11-3656-E111-B8C5-20CF3056171D.root',
       '/store/mc/Fall11/T_TuneZ2_scaleup_tW-channel-DR_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F87DDC98-3A56-E111-9596-001EC9D8D49F.root' ] );


secFiles.extend( [
               ] )

