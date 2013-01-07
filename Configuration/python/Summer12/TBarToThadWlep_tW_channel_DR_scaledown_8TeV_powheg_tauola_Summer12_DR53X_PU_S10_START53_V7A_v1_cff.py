import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0A5BAF7B-C0DA-E111-897E-003048D436EA.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/169CE991-F5DA-E111-85C9-00266CF32FA0.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1A8D6571-09DB-E111-B0E9-003048C693E2.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/20DAAF6C-0CDB-E111-A862-0030487E5101.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2CE12443-F9DA-E111-9432-00266CF32FA0.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/48107E09-25DB-E111-A2A6-0030487E4B99.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/485F4E71-FDDA-E111-855C-0030487D7103.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/487D6CFB-F0DA-E111-A076-0030487F92B1.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/50A4E3BB-CBDA-E111-B094-003048D47912.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5498D233-12DB-E111-8190-0030487D5E75.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5A19A3A6-F2DA-E111-8126-0030487E4EC7.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6CB7DFF5-F7DA-E111-83B6-0030487E5101.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/069851E8-EBDA-E111-A975-0030487D858B.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/10F99687-00DB-E111-8B29-0030487D5EAF.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/32F5BE12-16DB-E111-A3B8-0030487E52A3.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7E7FD9BE-0ADB-E111-B952-0030487EBB27.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/560D86B1-0FDB-E111-8EF0-003048D4DEBC.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/725B0B83-EADA-E111-B38E-0030487D5DBD.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8E81CFD0-F0DA-E111-A124-003048D4DF80.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/922D9885-FADA-E111-A209-003048D436B2.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/923BAC52-EDDA-E111-91A6-003048C6617E.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/929AF5FD-F3DA-E111-91C2-003048C691DC.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/96FB1A52-1FDB-E111-91B5-0030487F937B.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/74613B4A-0EDB-E111-951D-0030487D5D3F.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9E417E37-15DB-E111-B033-0030487F1307.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A24FE750-EFDA-E111-95DC-003048D43642.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/748FA038-F6DA-E111-A695-0030487F1A57.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8095680D-E8DA-E111-9E23-003048D373CC.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BEBE883D-1CDB-E111-91CD-0030487E54B5.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8445A462-E4DA-E111-9C1F-0030487D83B9.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9ADC337A-1CDB-E111-9364-003048D43980.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C84A5573-FCDA-E111-83E2-003048D4DEA6.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A8498313-13DB-E111-8248-0030487E4ED3.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AA15ABA9-E6DA-E111-B477-0030487F91D9.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C0E1F3AC-BDDA-E111-ADCD-003048C69314.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D6B9C5DE-16DB-E111-A78F-003048C69408.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C4392010-C3DA-E111-ADDC-003048F0E822.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CA630F25-11DB-E111-B5B9-003048F0E80C.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E25DCCC5-19DB-E111-826D-0030487FA4C5.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CEDF0DEF-22DB-E111-B2E7-0030487D70FD.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D46075DD-D2DA-E111-ABA3-0030487D8541.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E22D9309-1CDB-E111-8391-0030487F929B.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E22EB1B8-E9DA-E111-AAFD-0030487F1A49.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E4EC3D78-FBDA-E111-8079-003048F0E426.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EA487597-42DB-E111-96DA-0030487FA629.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EA578C6F-17DB-E111-B705-002481E0E440.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F2FA2072-C6DA-E111-8872-003048D439A6.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EE41E776-F4DA-E111-A6EA-003048C69310.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EEA18BE7-F7DA-E111-BF27-002481E0DAB0.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EEC63C7D-FFDA-E111-AD06-003048CF6336.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FC5EDAFB-D8DA-E111-B2B5-003048D4DCD8.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FCF711A5-18DB-E111-9545-0030487D5DC3.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F2C79016-1CDB-E111-BC01-00237DDCBEA4.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F684C92A-DCDA-E111-A483-0030487D5D67.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F6B8E206-1CDB-E111-83C2-003048D43980.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F86E018A-03DB-E111-9749-0030487DE7C5.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FE3B5811-07DB-E111-B768-002481E0D5CE.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FEB58E29-57DB-E111-8869-0030487E54B7.root' ] );


secFiles.extend( [
               ] )

