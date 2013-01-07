import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/085390BB-BDDA-E111-B216-0030487D710F.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/108429A4-A8DA-E111-853B-0030487D5D5B.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/14CA8F22-A7DA-E111-825E-0030487F132D.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0EC023A1-AEDA-E111-A34B-003048C692D4.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/109D7A6E-C4DA-E111-8D33-003048C690A0.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/10F7973D-BFDA-E111-A708-0030487D5E49.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/184D690E-C4DA-E111-B721-00266CF2D5C4.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/186B476D-AFDA-E111-8432-003048C69316.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3A934341-59DA-E111-8209-0030487D5EA9.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/405EEB7C-AEDA-E111-BC26-003048D4365C.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/24BC9511-C4DA-E111-901A-003048C65E4A.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4A2D5CE8-BCDA-E111-98CE-0030487EBB27.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/32A013D4-BEDA-E111-84BA-0030487D7105.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/50CF8959-C6DA-E111-8C90-003048F0E1AC.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/32BF7511-C4DA-E111-931C-003048D436F2.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/38FBF4A8-61DA-E111-906D-0030487D5EA1.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/48585365-9DDA-E111-8206-0030487D86CB.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/78016C92-97DA-E111-B41A-0030487FA4CD.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/80D1300F-D8DA-E111-B38B-0030487F92A7.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4C9A4103-C1DA-E111-B572-0030487D605B.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/84F53B42-C2DA-E111-94BB-0030487E5179.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/900498FC-A4DA-E111-94C7-0030487D814D.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/546319F4-9ADA-E111-B674-0030487D83B9.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/94DAEA7A-9ADA-E111-8B1C-0030487FA4C5.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/985384F1-C6DA-E111-9BFB-0030487F1651.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6CFEE163-BEDA-E111-AC67-0030487D864B.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9AE2164D-38DB-E111-BB66-0030487D5D93.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/764D7C16-C3DA-E111-A357-003048F0E3AE.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B032B6D4-BFDA-E111-83C5-0030487DA061.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B0A38C55-9DDA-E111-8C94-0030487F1731.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C28A4680-97DA-E111-A5BB-0030487F1797.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/849EA6F0-9BDA-E111-8B09-0030487FA4CB.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D4B931E1-BEDA-E111-81FE-003048D462BE.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9412D08C-98DA-E111-B0FA-0030487F1657.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A9587D8-B6DA-E111-9761-003048D437BA.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DE2C74A5-A9DA-E111-9A8D-003048C676E0.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E0620262-9FDA-E111-A44D-0030487F1F2F.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A25B23BB-C4DA-E111-8129-0030487E4EB7.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C4558934-C4DA-E111-9F69-003048D4DEAE.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EC7D0307-B4DA-E111-9CF3-0030487F164D.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F25A759E-B8DA-E111-BD8E-0030487D5E53.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F4969003-A0DA-E111-90E2-003048D438EA.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F4BA9BE0-ACDA-E111-8C84-0030487F910D.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DC6BB79F-C0DA-E111-9827-0030487D7103.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DCC95A5A-5FDA-E111-B8B9-0030487D5EAF.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E280F56F-C4DA-E111-BC89-0030487E55BB.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EC5D013C-BFDA-E111-9A44-002481E94BFE.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F84FDD74-A2DA-E111-A099-003048D437EC.root',
       '/store/mc/Summer12_DR53X/TToThadWlep_tW-channel-DR_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FE756246-B1DA-E111-A687-003048D43994.root' ] );


secFiles.extend( [
               ] )

