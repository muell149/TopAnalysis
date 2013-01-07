import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/00556BE1-3DE2-E111-99E0-0030487F910D.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/04AF1A56-16E2-E111-ACB4-0030487F910D.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0EB4EB76-06E2-E111-BEEB-0030487EBB25.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/14FD23CD-46E2-E111-B1F5-003048C692A2.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/16AB61EA-36E2-E111-B668-003048C68A9E.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2088BF07-24E3-E111-BBB1-0030487D5E73.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/24E81EFC-44E2-E111-80AD-0030487F1715.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/028D0DDB-3AE2-E111-879A-0030487F1667.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2A181C43-34E2-E111-9BA9-0030487D5D67.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2A472958-1FE2-E111-B85C-0030487F1307.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/308970FE-02E2-E111-9C22-0030487D5E81.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0A914AC0-3EE2-E111-83D9-0030487F1A4F.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/105AD30F-10E2-E111-AE6F-0030487D814D.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/28447A68-27E2-E111-BA9C-0030487FA4CD.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3C4382E7-A5E2-E111-9C1B-0030487FA623.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/28F54DDA-1CE2-E111-8065-003048C6929C.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/401F9B3B-13E2-E111-9A60-0030487E55C5.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4278014C-0AE2-E111-A87B-0030487F938F.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/34D3526B-2EE2-E111-AC37-0030487F1661.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/509051C2-72E2-E111-ACF8-003048C33984.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/56FB7D2C-39E2-E111-B518-0030487F907F.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/38655CA6-3FE2-E111-94C5-0030487F1C51.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/58FF3ECE-34E2-E111-B14E-0030487D5D67.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/66337BC8-3EE2-E111-8FC5-002481E94BCA.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/66674355-3DE2-E111-B346-0030487D5DBB.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3A6C5CFF-3CE2-E111-AA28-003048C693EE.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/70548989-0DE2-E111-A262-0030487D5DA5.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8AE1580E-2BE2-E111-B7AB-0030487D710F.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8C631067-41E2-E111-B5DF-0030487F1A57.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3C9851E7-31E2-E111-8036-0030487E4EC5.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/90D4AC50-32E2-E111-B410-0030487E55BB.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4A5A8F14-42E2-E111-9379-0030487F1A57.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/58EB55D9-08E2-E111-A77F-0030487D5EA1.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A81BE5C-44E2-E111-9E6A-0030487F1715.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6C2D3273-4BE2-E111-A7EF-0030487F929F.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8E916FC7-38E2-E111-97FB-003048D3739A.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AAA78FB2-32E2-E111-A3B1-0030487E4ED3.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B4AAEBC0-42E2-E111-8970-0030487F1A57.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B69854E7-36E2-E111-B3A5-0030487EBB21.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/92E42518-3AE2-E111-B0C1-003048C69036.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A5A718E-22E2-E111-8A8D-0030487D5E75.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BC9C6FF1-39E2-E111-86EC-003048C69294.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A65E9E78-46E2-E111-863F-003048D3C8FC.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C0E3293D-2AE2-E111-814D-0030487F16C1.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CA175947-35E2-E111-AABD-0030487D5D67.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CA9FACCE-3BE2-E111-9FC1-00215AD4D670.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D22A54F7-00E2-E111-90E6-0030487E0A29.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E6DE1A1F-40E2-E111-A6BF-003048C69310.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A66DB178-33E2-E111-9E3C-0030487D5D67.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B828CA85-3BE2-E111-8A01-003048D4385C.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BA9B16E2-2CE2-E111-8C1B-0030487EBB21.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BEF423B7-7EE2-E111-8128-0030487D5E45.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FCA406DC-3DE2-E111-A250-0030487D5DA9.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EC4432E2-17E2-E111-A688-002481E0EA06.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/ECE7D38E-3AE2-E111-B94E-003048C69294.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FC08AB44-40E2-E111-AE46-0030487F1C51.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaledown_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FC6F3909-3BE2-E111-9109-003048C69314.root' ] );


secFiles.extend( [
               ] )

