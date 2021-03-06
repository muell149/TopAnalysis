import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1ADDB34C-1CEA-E111-A8FC-00304867920A.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/42E63224-30EA-E111-B161-003048FFD7D4.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/620C6738-33EA-E111-A39C-001A928116C2.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/28B811CD-27EA-E111-9628-0018F3D096F8.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/68BB8376-3CEA-E111-8612-0018F3D0966C.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/341F5D52-2AEA-E111-84A9-0018F3D096F8.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8E5161B9-46EA-E111-97C4-003048FFCC18.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/92068BD1-2DEA-E111-9557-003048FFD756.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9603BFBD-39EA-E111-9D2C-00261894391C.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4E28BA12-26EA-E111-9B00-0018F3D096C0.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4EA87AC0-28EA-E111-A233-0018F3D09628.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CC9E88D5-27EA-E111-9E82-00261894389E.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E2CFD03C-27EA-E111-8F8B-0018F3D09698.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B2926811-28EA-E111-9270-003048FFD770.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6879303A-27EA-E111-8341-0018F3D096F8.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6C1BD1C8-42EA-E111-A683-00261894394F.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9E177567-4AEA-E111-A426-00304867D838.root',
       '/store/mc/Summer12_DR53X/Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F881A002-29EA-E111-B4D8-003048D15D22.root' ] );


secFiles.extend( [
               ] )

