import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/00F8501B-4FE6-E111-99F5-00266CF32F14.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1AE08B53-4DE6-E111-A45A-0030487F1667.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/00981C37-40E6-E111-918F-0025901D42BC.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2C3A6BA2-49E6-E111-8508-00266CFFA124.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/38A803C6-3BE6-E111-9B4A-003048D4DEAC.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0C0E4FDB-37E6-E111-B84F-0030487D5D7B.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3E293793-4AE6-E111-93EF-003048D43982.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/46D31EB3-45E6-E111-BFF5-0025901D4D20.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/508CA988-4AE6-E111-AF1E-00266CF326A8.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/561E3564-46E6-E111-8328-003048D3C8FC.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0ED0BA96-42E6-E111-AACD-003048D4DFBC.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1EBCD59E-46E6-E111-92FD-003048D4363C.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/62318C54-3FE6-E111-A7EB-0025901D4D64.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/242ED225-4BE6-E111-B483-003048C693FE.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3A0FEEA5-3FE6-E111-864B-003048D4DFBA.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/56A6D3BF-41E6-E111-9A47-003048CF6346.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/608F0125-3EE6-E111-AD22-002590494CC4.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/787F8AA1-35E6-E111-A02F-0025904B1426.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/644099C3-3EE6-E111-A73A-00266CFFA68C.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7ADBF489-48E6-E111-85FA-003048D3739C.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7CBFEAF9-47E6-E111-B306-003048D43980.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/66F68561-42E6-E111-8800-0030487E55C5.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6AD5F41B-45E6-E111-8D7D-002481E1070E.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8C53FDCF-56E6-E111-AC78-00266CFFA6F8.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8CD81F25-41E6-E111-AAF5-0025901D4B20.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6C4E9A96-68E6-E111-9D37-0030487F92A9.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7A9D5A03-39E6-E111-82F1-003048C69316.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/92175406-32E6-E111-88AF-0025904B12FC.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/869C0438-40E6-E111-A1C3-003048CF6346.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8A5B10C2-4BE6-E111-A972-003048F0E188.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/90F06085-3DE6-E111-A753-0025901D4D64.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/920D1330-4EE6-E111-85FF-0025901D4B06.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B46DF3DC-43E6-E111-BC51-002590494CC2.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/92306DB9-4CE6-E111-9D20-00266CFFA6F8.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9C7CF585-33E6-E111-8A45-003048C6942A.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A0CC48B8-45E6-E111-B76D-0030487D814D.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CA6B4016-45E6-E111-9A64-0025901D4844.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AA2210DE-43E6-E111-8CEA-003048D439BE.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D4AA6155-46E6-E111-AE5A-0025901D4940.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D8943487-44E6-E111-8B2F-00266CFFA630.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BC72D7AE-49E6-E111-BF6E-0030487D5EAF.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EC37F542-43E6-E111-A307-002590494CC2.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F61C5A84-3AE6-E111-AC65-003048C692BA.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C08D7566-48E6-E111-84EE-0025901D4B04.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FEC9AA2A-52E6-E111-8127-0030487D5E73.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FEF7DC60-61E6-E111-9EBF-0025901D4C3C.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C822219A-49E6-E111-ACDC-003048D3739C.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D209FDC5-41E6-E111-9AB4-00266CFFA6F8.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DEF7E2D0-47E6-E111-BCB0-0025901D4B4C.root',
       '/store/mc/Summer12_DR53X/TToTlepWhad_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FE5F6EB5-45E6-E111-A508-0025901D4844.root' ] );


secFiles.extend( [
               ] )

