import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/02CE8352-F8DC-E111-87AF-002354EF3BE4.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/14136B34-46DD-E111-9B7C-0018F3D096A0.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/161E60E3-F4DC-E111-8B7A-00261894387E.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/28D6D1CD-0ADD-E111-A372-003048678B34.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3270CA13-46DD-E111-B858-003048678B84.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/40B07599-12DD-E111-B132-001A92811728.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/42A925BD-11DD-E111-BC75-00304867D836.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/44392A08-12DD-E111-B784-0018F3D0969A.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/108457D0-0FDD-E111-812F-003048678D6C.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4E978449-0EDD-E111-80B2-003048678B0E.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4EDDB30C-08DD-E111-9239-00304867BFC6.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/54AE6FEB-D5DE-E111-AAC4-003048FFD7BE.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5E051D98-F4DC-E111-AF51-001A928116EC.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/32096152-FBDC-E111-958E-0026189438B5.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/70F5350C-F7DC-E111-B7DF-003048678BE6.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/329600B3-FADC-E111-B887-002618943925.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/80806173-F6DC-E111-B7F4-003048FFD7D4.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/44835C44-0EDD-E111-85C3-0030486791F2.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4C326677-0BDD-E111-B037-0018F3D095EA.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/620C9593-F8DC-E111-B81B-003048FFCBB0.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/949A331C-11DD-E111-B761-001A92810AAE.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/960B610A-E6DD-E111-B772-001A92811744.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/743E3383-F9DC-E111-8415-00261894397B.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/841D31F3-FBDC-E111-BB28-003048FFD720.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/86E0AE33-0ADD-E111-9FC1-001A928116DE.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A4833F7C-10DD-E111-B542-003048678B0C.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/90416B83-10DD-E111-BF77-002618943856.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AA249120-46DD-E111-9C41-002618943913.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/984E20F8-FEDC-E111-953A-0018F3D09702.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A1AD88F-0EDD-E111-884A-003048FFD7A2.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9CE23F81-F5DC-E111-93EB-0026189438B0.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A495300B-F7DC-E111-B79F-00261894396E.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C4ECA411-46DD-E111-A1BD-001A928116B2.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C604B915-46DD-E111-9AA6-0018F3D096F6.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CA0F20DE-F8DC-E111-8986-00304867C034.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BE27A993-F9DC-E111-BB22-001A92971AD8.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D4ADE5ED-F8DC-E111-BA3C-003048FFD760.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D4FFEBEF-16DD-E111-8B4D-00261894392C.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BEDD72E2-E9DC-E111-9AB5-002354EF3BDF.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DE6D00BE-0CDD-E111-B6D5-002618943947.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E024A90D-F7DC-E111-9E4E-003048678D86.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BEF51516-46DD-E111-8B4C-002618943958.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F02FB186-0FDD-E111-B14B-001A92810ABA.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C2952F91-F9DC-E111-8C2F-001A9281170E.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D0FA9A3E-09DD-E111-BF45-003048679046.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D6AE49B9-0CDD-E111-8CF5-003048B835A2.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F0F48380-14DD-E111-BA5B-00248C0BE014.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F6A5007C-F9DC-E111-B6B2-003048678DA2.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FA7A5CCA-F3DC-E111-B874-0030486791AA.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FADDE51A-FDDC-E111-B6E3-003048FFCBFC.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FCBE638F-0EDD-E111-BD59-003048FFCBB0.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FEF0601A-0CDD-E111-A754-003048D3C010.root',
       '/store/mc/Summer12_DR53X/Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E63307B0-FADC-E111-9ED4-00248C0BE013.root' ] );


secFiles.extend( [
               ] )

