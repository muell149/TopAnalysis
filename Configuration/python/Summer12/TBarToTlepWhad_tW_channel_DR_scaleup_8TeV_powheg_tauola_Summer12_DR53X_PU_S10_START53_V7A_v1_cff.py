import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/18437FF7-D8DA-E111-84F8-0030487DA061.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/22200282-E4DA-E111-BA2F-003048C6941E.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/24CA3B24-D5DA-E111-8F9A-003048D3C7DC.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/28059CD5-15DB-E111-84A6-003048D4DFA4.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0AF40574-E2DA-E111-9C44-0030487F907F.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2C195FC3-C5DA-E111-BFB0-003048C693E4.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/34FC36CE-F7DA-E111-988E-0030487F1C4F.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/387AE3FB-36DB-E111-988D-0030487F1A73.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0EDDE172-E3DA-E111-AAAF-002481E15204.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3EC5BE6F-BFDA-E111-B59B-0030487D7105.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/16A23220-DCDA-E111-A480-00266CF3322C.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/48EE9989-D8DA-E111-A6D7-003048D3C7DC.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4A7D79C9-EBDA-E111-8799-003048D3CD6C.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4E0FA772-EDDA-E111-9D3C-0030487D814B.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4E7D87B4-FDDA-E111-B56E-0030487E5399.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4EA15118-DEDA-E111-BEB7-0030487D858B.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2A0F594C-E0DA-E111-99BD-003048C68F6A.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2A577982-E2DA-E111-A04D-0030487F164F.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3A4DBCB6-DDDA-E111-A807-0030487F1BE5.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/605E893B-F0DA-E111-8DFE-003048D4399C.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/46CA4C02-D3DA-E111-B3CD-003048C64787.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5C4ADDA7-F2DA-E111-91CA-0030487F92A9.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/741E84C1-04DB-E111-BFDC-003048D4399E.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6007934C-C8DA-E111-887F-003048F0E522.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/76F285FD-EBDA-E111-9850-0030487D5EB1.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6016D874-E7DA-E111-8CE2-003048C693E8.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8CD71891-CADA-E111-B70D-0030487F929D.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6246CE4A-E9DA-E111-BD16-0030487D814D.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/70D1E015-E1DA-E111-95AD-0030487F1A49.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/76B6EF3F-94DB-E111-ACD1-0030487F1309.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9E3100FF-EADA-E111-B783-003048D3CD6C.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9E5068CA-DEDA-E111-8278-0030487FA609.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/884244EA-EDDA-E111-A5A1-0030487F1717.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A8405A30-C4DA-E111-B3A7-0030487FA629.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B2DAFB3F-D8DA-E111-97DB-003048C6930E.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/902271CD-F0DA-E111-96F0-00237DDCBEA4.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/98E9CF1E-CCDA-E111-81B1-003048C693EE.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9AA0F73C-D7DA-E111-89C0-002481E0DAB0.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A63B9B34-C2DA-E111-8AB0-002481E15176.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B8B8186D-E6DA-E111-ADA3-002481E0DE08.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BAFB45AC-DADA-E111-9725-0030487F91D9.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C0C34268-D1DA-E111-9C17-0030487F1309.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D03B3500-CEDA-E111-9384-003048C68AA6.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D8B9F91C-E9DA-E111-B485-003048F0E3B0.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EC9841D6-EADA-E111-82E6-0030487F1665.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DE819B3F-DEDA-E111-BDE6-003048D3C7DC.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F62DCBCD-33DB-E111-94D1-0030487F1C51.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F8A16B3D-3FDB-E111-AB04-00237DDC5E96.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E0DD0CBD-F0DA-E111-B6C8-003048F0E3B0.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FCD13CEC-E5DA-E111-9D46-0030487D5D7B.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E228FAB0-F4DA-E111-B1C4-0030487F9151.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E46F993C-B8DA-E111-A23E-002481E94BCA.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EE673752-D0DA-E111-9C60-003048C693F8.root',
       '/store/mc/Summer12_DR53X/TBarToTlepWhad_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F8A9FB64-E4DA-E111-A3AB-0030487E4EBF.root' ] );


secFiles.extend( [
               ] )

