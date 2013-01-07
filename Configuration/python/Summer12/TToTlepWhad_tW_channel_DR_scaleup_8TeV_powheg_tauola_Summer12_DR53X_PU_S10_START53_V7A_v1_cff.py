import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/041C8D8D-9EF2-E111-A85A-003048D4365C.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/108CC343-8BF2-E111-B321-00266CFFA148.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/164F0827-95F2-E111-8D5C-0025901D4932.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1C507532-98F2-E111-BC17-002590494CC2.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/20865645-88F2-E111-85F9-0030487F1BCD.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/222E4C23-9CF2-E111-8DAD-002590494C74.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/228EF8BF-A2F2-E111-95AF-00266CFFA344.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/22F35F8E-99F2-E111-ADA2-00266CFFA2B8.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3033B726-A2F2-E111-AA00-00266CFFA654.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/36F1A052-96F2-E111-9372-00266CFFA6F0.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3CEC8797-91F2-E111-9C53-0025901D4138.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0878C13C-A1F2-E111-9ADB-0025901D4ADE.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/18A685F3-97F2-E111-847A-0030487DA061.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/28DC75D3-A4F2-E111-A1BA-00266CFFA2EC.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2EB49B34-9FF2-E111-BE1A-00266CFFA604.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/626C2CC9-9CF2-E111-A2DB-00266CFFA2B8.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/66633605-8EF2-E111-BFC4-0025904B12B2.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/68872602-A3F2-E111-A683-00266CFFA3EC.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/40DDE9EC-A3F2-E111-BB57-00266CFFA6DC.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/74233401-9EF2-E111-A2BB-003048D43944.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5229D5F1-9BF2-E111-BCD3-00266CFFA25C.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5602CEE7-8EF2-E111-A23C-002590494C92.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/866622C9-92F2-E111-AE24-0025904B1364.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/886E3E8B-9BF2-E111-A43E-0025904B12A4.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5EE1768D-A4F2-E111-A352-00266CFFA6DC.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8E32F862-7CF2-E111-BE4F-0030487F1309.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/943E2669-A9F2-E111-B84D-0025904B1448.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9EC4E57B-92F2-E111-94A4-0025901D493E.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6CD02B91-94F2-E111-8021-00266CFFB390.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7CAB5665-A0F2-E111-B15A-00266CFFA148.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AEFF280E-9AF2-E111-A6D1-002481E0D9BC.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B658BC74-A8F2-E111-92E9-00266CF326A8.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/827CDEA4-9DF2-E111-82A1-003048F0E528.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BA1F19C7-9CF2-E111-B550-002481E0D500.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BED1CF8F-99F2-E111-9FD2-0030487DE7C5.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C0D88009-A7F2-E111-8804-0030487E52A5.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/88919A1C-90F2-E111-9CBF-00266CF2AE10.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A867CB41-80F2-E111-9D66-0025904B0F96.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D270D6B8-A2F2-E111-874E-00266CFFA120.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D4725FC0-9FF2-E111-9285-0030487F1C57.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AA928F9E-9BF2-E111-8C37-0030487E52A5.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B6BAC418-9AF2-E111-B543-002481E0DE08.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CEC53DD1-95F2-E111-BDEF-0025901D493A.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D26E7666-75F2-E111-BC3F-003048C6931E.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F0736D9F-9AF2-E111-BB2C-00266CF32F14.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D4B4FAB4-A5F2-E111-9EEB-00266CFFB1F4.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E0ADFFFF-A0F2-E111-A293-00266CFFA120.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E0FB5B01-91F2-E111-84EC-0025901D493E.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E867E50C-A6F2-E111-A957-00266CFFA2EC.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FCA32A75-99F2-E111-846A-0025904B1026.root' ] );


secFiles.extend( [
               ] )

