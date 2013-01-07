import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/045CD04C-1ADA-E111-B695-003048C692D4.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0A76C247-12DA-E111-BEFD-003048D3CD92.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0C85F13D-18DA-E111-998F-0030487D5DC3.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0E6FF5BB-FAD9-E111-836C-003048D3C880.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/10812244-DCD9-E111-B522-0030487F1A73.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/16076CD5-10DA-E111-BBF6-0030487DA061.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1CBDC74A-D4D9-E111-B236-0030487E4EC5.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/20646E0A-2CDA-E111-94A5-0030487F171D.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2285C356-2BDA-E111-B113-002481E100F8.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/22FDE49C-DDD9-E111-85D8-0030487F1A73.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/248D6EBA-0DDA-E111-BFE8-0030487F9295.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/125E73B5-0DDA-E111-898D-0030487F1A3F.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/141395DF-F6D9-E111-B791-0030487F1A73.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1C61D43B-05DA-E111-BD0D-0030487D5D4D.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2E5265ED-0ADA-E111-A895-0030487D5D89.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/201E295F-03DA-E111-9EFD-0030487D8635.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/28F3AA2C-E6D9-E111-85FF-0030487E55B9.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/38FAD34F-28DA-E111-A584-003048C693E2.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2C109E83-20DA-E111-8CF0-0030487F16F9.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2C136713-15DA-E111-9294-0030487F1651.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/307A6FEC-E1D9-E111-9017-0030487D5DB7.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/320E0CFF-05DA-E111-A5D3-0030487D5EA1.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/464546ED-E7D9-E111-964F-002481E76372.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/48A864AA-0BDA-E111-9BD2-0030487F92A7.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4A5D093D-FFD9-E111-AA68-0030487F4B8B.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3A509831-1BDA-E111-813A-0030487F1309.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3A637772-24DA-E111-8532-0030487F1655.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/564154F2-22DA-E111-AFA6-0030487D86C9.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3E55F4C5-D6D9-E111-8E74-0030487D83B9.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/42FA9FF4-D0D9-E111-9A08-0030487D5E49.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5CAAA15E-13DA-E111-94D1-0030487DE7C5.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/607D4095-FDD9-E111-8391-0030487D70FF.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4C211F60-19DA-E111-BEA7-003048C68F6A.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6440DC6E-F8D9-E111-8752-0030487D5D6B.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4ED74DCD-06DA-E111-909B-0030487F1A73.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/56C48A47-05DA-E111-A77F-003048C693EA.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6AA70AF3-0ADA-E111-9F04-0030487D5DB5.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6AF98C39-18DA-E111-9024-0030487D5DBB.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6E07254F-2BDA-E111-97D7-0030487F171D.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6E3D945A-20DA-E111-8661-003048C68AA6.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6EDCBB3B-05DA-E111-A1A5-002481E0DC7C.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/58F88DC2-0ADA-E111-A58B-0030487EBB21.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/74137331-25DA-E111-8C01-003048C693E6.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/62B44D95-EED9-E111-9461-003048C693C8.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/647ABB3B-26DA-E111-A269-003048C692C0.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7E3F15C9-F1D9-E111-A0C8-00215AEDFD12.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/863DE72A-2BDA-E111-B5FD-0030487F16C1.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/88AB1902-9DDA-E111-B7DD-0030487E5247.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8AEB8838-1ADA-E111-8BC6-003048D439A8.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/66BFCF6C-21DA-E111-A7E0-003048D439B4.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8C0D0385-DAD9-E111-8C0D-0030487D5DA9.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8CF5BC9C-0CDA-E111-8FD8-0030487F1659.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/740462D4-10DA-E111-AF4A-0030487F1A55.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/744DBCC2-10DA-E111-8F63-003048C69316.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/96F8EB5A-12DA-E111-B563-003048C68A88.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7CEB0610-05DA-E111-8F33-003048C692E2.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8AF4FC82-16DA-E111-AA32-0030487F91DB.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A73E1E2-10DA-E111-A081-0030487CF3F7.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A8FADD4-22DA-E111-8F39-003048C693D2.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9E65C949-12DA-E111-BCE7-003048C66180.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A417D4C6-F5D9-E111-9B95-0030487F1A73.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A430EBDB-0FDA-E111-82E1-0030487F1735.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/92485E0D-06DA-E111-A114-003048C6941C.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9492E170-14DA-E111-BD45-0030487F1651.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B6199830-27DA-E111-B637-0030487D8581.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B6FDAB44-20DA-E111-8CB4-0030487F937B.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/98E28584-03DA-E111-901E-0030487FA60B.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BE4BAA0C-FFD9-E111-B192-002481E0EA70.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BEA27CCB-2FDA-E111-8912-003048C6903C.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C0242BCA-17DA-E111-92BC-0030487F1715.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A275CD8-00DA-E111-ACBE-003048C692AC.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C612ADCA-2DDA-E111-9113-003048D3739A.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B4A539ED-F8D9-E111-917A-0030487D8633.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C8464E67-19DA-E111-BBB9-003048C68A9A.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B4C5D80F-08DA-E111-A652-0030487FA4CB.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BA3AA2ED-08DA-E111-85EB-0030487F92AB.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CACC702E-20DA-E111-95DD-003048C69408.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C2BF34FC-F3D9-E111-B840-0030487F91DB.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D0F6DBA7-97DA-E111-85C5-0030487F92FF.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C6CB3D06-1CDA-E111-BB3A-0030487F1BCD.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D87AEE8A-16DA-E111-AD18-0030487F929B.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DE81E528-01DA-E111-842C-003048C69292.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C8BAFBAE-2DDA-E111-A942-0030487D5E67.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CA2EBCFA-0FDA-E111-B640-0030487F16C1.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E6973F41-02DA-E111-8CBC-0030487D70FF.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D00C4430-14DA-E111-A451-003048D4399E.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EE09E7D3-1BDA-E111-A154-0030487F1309.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F614D3DF-0BDA-E111-B2CD-0030487F1659.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F8589A58-21DA-E111-A7ED-003048C68AA6.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F8C655CC-01DA-E111-B578-0030487FA609.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D2C7C9AA-FCD9-E111-B3DC-003048C69402.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FAADA6DF-1DDA-E111-AD32-0030487F1BD7.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E05937DA-32DA-E111-AA33-0030487D5059.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E2778220-09DA-E111-B7AA-0030487F16BF.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EA0A65F2-1DDA-E111-B2D9-0030487F1653.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FA9762A6-06DA-E111-9933-003048C6941C.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FE76AAF4-0FDA-E111-BA47-0030487D5DBD.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FC96A40E-29DA-E111-8A75-0030487D5EB5.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FCECC2E7-1CDA-E111-B285-0030487FA4C5.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FCF07727-F7D9-E111-8474-0030487D5E75.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_t-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FE215681-EBD9-E111-A094-0030487F1A73.root' ] );


secFiles.extend( [
               ] )

