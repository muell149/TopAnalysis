import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0AF218E4-0EDD-E111-8F1F-003048F0E1AC.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1E1C00BE-46DD-E111-BC1D-00266CF2AACC.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/025735BF-46DD-E111-AFD1-003048D479C0.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2C859564-0CDD-E111-AF7F-002481E946EE.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2E57B162-46DD-E111-92A4-0030487F16F7.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/06357A1B-00DD-E111-A22C-0030487F92AB.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/323C04CC-46DD-E111-9630-0030487D5E53.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/34DDEC6F-F9DC-E111-9EDD-0030487D5E73.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/082D8965-16DD-E111-9237-0030487F1C57.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0EF4D2CD-46DD-E111-9BA9-003048F0E424.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3ED19B1F-15DD-E111-AF19-0030487F164F.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3EDDF276-46DD-E111-A32D-003048C6941C.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/464F33F3-0FDD-E111-87B1-003048D43734.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/52C2CEAB-46DD-E111-A547-003048C690A2.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/52ED07F9-0DDD-E111-9152-003048D4365C.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/26BD4717-FDDC-E111-B36E-002481E94BFE.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/686251A0-05DD-E111-983D-0030487D5EA9.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6E35797C-46DD-E111-A872-003048D4363C.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2EE5C41C-FADC-E111-9041-0030487D5EBD.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/38586C6A-46DD-E111-86D3-0030487D5DC3.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3869C36B-46DD-E111-BD78-0030487D8563.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5C29F57D-46DD-E111-B670-003048D436CA.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/708C81BB-46DD-E111-81A9-00266CF32A20.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/70CDDD6C-11DD-E111-8AE9-002481E7628E.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/801D7B94-46DD-E111-B3D7-002481E14F2A.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8AD99379-46DD-E111-8D5E-0030487FA60D.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/92809B90-46DD-E111-8EBF-00266CF25320.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/96BA9D4D-03DD-E111-B441-003048D436F2.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8CE315AF-46DD-E111-ADD0-0030487EA3DD.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8E731B3E-F8DC-E111-8622-0030487E510B.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A861E75B-01DD-E111-B43D-00215AD4D670.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AA572899-17DD-E111-96E3-0030487F16FB.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AABFBB00-5FDD-E111-916C-003048F0E824.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AED062EB-17DD-E111-80A2-0030487F92B3.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9056889D-46DD-E111-A621-003048F0E3BC.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/90FB3573-46DD-E111-9342-0030487D5E5F.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A081F9A5-46DD-E111-AED8-0030487F9381.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D260F962-46DD-E111-805B-0030487F1C55.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A26DE472-46DD-E111-834C-0030487E4EB7.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E019A482-46DD-E111-B558-0030487F91D9.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E06D1CC5-46DD-E111-B7B0-0030487D5E73.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E20B8FA3-46DD-E111-BCB4-0030487F16BF.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B8595770-10DD-E111-A728-0030487D5D8D.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B8C8E39F-12DD-E111-9C31-003048C33984.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C6FBB698-46DD-E111-BB39-003048C68A88.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F2B70801-FFDC-E111-9D2B-003048D3C8FC.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D6B53BD1-14DD-E111-A36A-0030487F1659.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E4F22FB4-FCDC-E111-BF59-002481E94BFE.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FAB6FA8D-46DD-E111-B43F-002481E10D3E.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E680AD70-46DD-E111-A06B-0030487D5E75.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F2A95E7C-4ADD-E111-97B2-0030487D5D7B.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F4EDD903-11DD-E111-8538-0030487F1C51.root',
       '/store/mc/Summer12_DR53X/TBarToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FA2DB83B-14DD-E111-B425-003048D3CB3C.root' ] );


secFiles.extend( [
               ] )

