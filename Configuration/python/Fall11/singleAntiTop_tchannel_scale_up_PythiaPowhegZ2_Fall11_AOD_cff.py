import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/04443246-F755-E111-9F4E-0030487C6A90.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/18690FF9-FB55-E111-A17F-E0CB4E19F9A2.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/1A6855A5-F955-E111-8355-20CF305B056D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/1E0E9F90-F755-E111-A69B-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2AB905B5-1456-E111-AE9C-20CF305B056C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2C3B9749-0156-E111-A5B2-E0CB4E1A11A3.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2CD137AA-0056-E111-AC0D-485B39897219.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3066842A-FF55-E111-9824-E0CB4E553686.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/36827BA3-0856-E111-A956-001EC9D7FA14.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3AD08617-F655-E111-A1B0-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/406DC01C-0056-E111-A138-485B39897219.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/44D1656C-FD55-E111-9CA1-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/44DC7D6C-F855-E111-B66F-90E6BA19A224.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/48247DD6-0656-E111-8086-E0CB4E1A1193.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4C3DF3AD-0A56-E111-822C-90E6BA0D09EA.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4C9D3DEA-0556-E111-9432-E0CB4E19F9A1.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/5202A119-0D56-E111-B143-E0CB4E1A117F.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/620CECE5-F455-E111-9AE7-20CF305B059C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/6AAF5520-0A56-E111-B425-485B39800C13.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/6E30CF02-0156-E111-B9E2-E0CB4E1A1187.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/70DBEBCB-FA55-E111-A667-E0CB4E29C4E0.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7852C4F2-2156-E111-9766-BCAEC54B302D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7A15CC4E-EF55-E111-93BA-E0CB4E19F982.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7A66109B-0356-E111-9435-002618FDA1BD.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7E5C7932-0956-E111-9CBB-90E6BA0D09EA.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7EB69EC9-ED55-E111-B094-20CF3027A5E2.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7EF14DA9-FB55-E111-8428-90E6BA19A204.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8814BAA6-F655-E111-A691-90E6BA442F1A.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8EBBDE5E-4456-E111-92F1-E0CB4E29C4D2.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/90B16D74-1156-E111-A2BC-20CF305B052B.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/947E08CA-0456-E111-AB58-90E6BA442F0C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/960E825E-FB55-E111-B7E1-20CF305B056D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/9C57BDD7-0B56-E111-911C-E0CB4E1A117F.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/9E5EC136-FA55-E111-BBD0-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A4420C44-FE55-E111-860D-485B39800C23.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A83A8E61-F955-E111-8F61-90E6BA442F1A.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/AC915889-FC55-E111-A88F-90E6BA442F0A.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B42730D7-F755-E111-B255-E0CB4E29C4C5.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B63D8F30-0456-E111-8C12-001EC9D80AB9.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/BAF5ACF5-4156-E111-B491-20CF3027A626.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D02F47B4-0256-E111-ADC1-E0CB4E1A116A.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D233E75B-F155-E111-81C5-90E6BA0D09A7.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/D4BF2166-F655-E111-80E6-E0CB4E19F987.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/DC2631B8-FD55-E111-AE7F-485B39800BFB.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/E46F0A16-FD55-E111-94C2-E0CB4E553663.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/E6523722-0256-E111-822F-E0CB4E29C510.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F43D2CAC-F355-E111-8AC2-E0CB4E29C4C5.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/FC939753-EC55-E111-AADD-E0CB4E55363D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_t-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/FEA9BDDF-FE55-E111-AD5E-485B39800C23.root' ] );


secFiles.extend( [
               ] )

