import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0A506CB0-26E3-E111-BD74-0030487F1659.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0E2ECE2E-3CE3-E111-9AC4-003048D439AC.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/127A2971-35E3-E111-BF36-003048C693B8.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/18016618-1FE3-E111-9E40-002481E100F8.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/18254444-ECE2-E111-904B-003048D4DEAC.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1C1C773D-29E3-E111-8C55-0030487D5DC3.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2E97BA99-24E3-E111-96B9-003048D3739A.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2EABE7E0-23E3-E111-9416-003048C692CA.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/022EAE99-39E3-E111-AD31-003048C69328.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0AB2DAA7-31E3-E111-9E9A-003048C693F0.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/36D4C568-37E3-E111-BE20-003048C69314.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/14F37399-38E3-E111-A021-0030487E4B8F.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/44A8871C-21E3-E111-B359-0030487D5D8D.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/26B5097D-2CE3-E111-8F53-0030487D814B.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3208DBF8-25E3-E111-9570-0030487E4D11.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4A8218F6-35E3-E111-9506-0030487EBB27.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/34CFD901-23E3-E111-A7E2-003048D436F2.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/500A5D00-3BE3-E111-A76D-002481E100F8.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5450C4A3-3BE3-E111-93B3-003048C68A84.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3ACD1F33-2AE3-E111-AC04-0030487F1A55.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/46BD69C5-33E3-E111-BC9B-0030487D7105.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5A92749E-2FE3-E111-B571-003048C692CA.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4826EC4C-14E3-E111-9FB9-0030487E0A29.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4EF3FEEE-22E3-E111-918D-0030487D5E75.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5EA08046-41E3-E111-9F13-003048C69272.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/60D52976-2CE3-E111-BF13-003048D462DA.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/54BBC36C-2BE3-E111-8DA4-003048C69428.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/66C057AA-3DE3-E111-A85C-003048C69040.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/58425C91-24E3-E111-BB8F-0030487F92E3.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/68B86F19-21E3-E111-81C1-003048C68A92.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6AC481BE-F2E2-E111-8147-0030487F933D.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6C033C53-30E3-E111-9592-0030487F92E3.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5C725805-26E3-E111-B148-003048D43944.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/706605B8-22E3-E111-B57B-0030487F929F.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/720CE7DC-32E3-E111-AA93-002481E0E440.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/727C06D5-3CE3-E111-B588-003048D439AC.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/74E373FF-45E3-E111-9B4C-0030487F1F23.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5C9C2858-29E3-E111-89A5-0030487F9297.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7834EAA1-28E3-E111-B38C-003048C662D4.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/662F6793-44E3-E111-9078-003048C68A98.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7CDF6C8F-27E3-E111-B761-0030487D814D.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7E169CAE-D1E3-E111-BEDF-003048C69328.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6833AAD7-2AE3-E111-A138-003048C68A80.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6CEFD911-2EE3-E111-8316-0030487E54B7.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/765B3B8E-25E3-E111-8156-003048D43996.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7AF39B08-31E3-E111-92A6-002481E94C56.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/82911F05-2EE3-E111-BEB9-0030487D5EA7.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8EAFAFF1-1DE3-E111-AC35-0030487E52A3.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/82EA184D-3EE3-E111-BBDF-0030487E52A3.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/902EC2CC-22E3-E111-A343-003048C68F6A.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/86CAAAC1-3FE3-E111-B332-0030487F92FF.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9611A86E-34E3-E111-B3DD-0030487D5E53.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/961CE3A9-35E3-E111-916D-0030487D7103.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/964DE38F-2DE3-E111-994E-003048C6928E.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8A32A5F3-2EE3-E111-980F-003048D3739C.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8AF30B5F-37E3-E111-AB7C-003048C692FE.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/902ACA45-32E3-E111-8455-002481E0E440.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9C9CD776-20E3-E111-A29F-0030487D5D89.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9069B8DB-28E3-E111-BEF2-003048C693B8.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/98145B8B-7DE3-E111-8439-00266CF2E2C8.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A2DEA174-01E3-E111-B232-0030487F1A55.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A36E28D-1BE3-E111-BBB0-003048C6931C.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A756A3E-30E3-E111-98FE-0030487D5EA9.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A47621EA-35E3-E111-9CA3-003048C693B8.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A4F3C382-37E3-E111-B738-003048C6930E.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9CCFD6EA-1FE3-E111-8DFC-0030487D5D8D.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A0D5D94B-3EE3-E111-B9ED-003048C69040.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A434D549-32E3-E111-9704-0030487F932D.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A4711573-2CE3-E111-AF4B-0030487D83B9.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AAA3D4E2-33E3-E111-910B-003048C693D6.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AC955880-1EE3-E111-A2EF-0030487D5E81.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B0105F64-FBE2-E111-B223-002481E0D2E8.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B25AB3BA-0EE3-E111-904E-0030487D5D89.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B2719662-35E3-E111-B590-0030487FA4C9.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A6F046B9-10E3-E111-915F-0030487D70FF.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B8165148-30E3-E111-8308-003048C68A9E.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BC4AF085-2FE3-E111-BBBC-003048D3739C.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A6F8A86C-1BE3-E111-AFBE-0030487E5399.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BE5489E2-32E3-E111-8B73-003048C65E4A.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BEB53BEF-35E3-E111-B12C-003048C68A92.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A8639FAC-31E3-E111-B6C4-002481E0E440.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AA576483-27E3-E111-A7E4-0030487E4B8F.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CA87D087-2FE3-E111-98A1-003048C69402.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CAD5FED8-3EE3-E111-9C0D-003048D43986.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CC720E6E-2DE3-E111-8A56-0030487E55C5.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B4B1D70A-19E3-E111-9996-0030487E52A3.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BC993A77-27E3-E111-ADC3-0030487F1A73.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D02FD95A-37E3-E111-AE0B-002481E102C6.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C01838F9-2EE3-E111-8487-002481E94C56.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C81D1019-F8E2-E111-8701-0030487D814B.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DA9A786F-2CE3-E111-B57E-003048C693F0.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CCF608AE-19E3-E111-8451-0030487F1657.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CED37BD9-3CE3-E111-9EFB-003048D45FCE.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E67C2877-27E3-E111-B0BD-0030487F91D7.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EE02B67B-39E3-E111-9211-0030487F91D9.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F2442A41-3CE3-E111-90FE-003048C69026.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D2DF5353-1CE3-E111-8328-003048D439B4.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FA8AEE2B-3AE3-E111-99DE-0030487D7109.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D6FE48B2-09E3-E111-8990-003048D47976.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E41539C2-2AE3-E111-A889-0030487D5DC7.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E46B2978-24E3-E111-BA0D-0030487FA60D.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F605C8A9-E9E2-E111-8DE8-003048C6903A.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FA9E2548-32E3-E111-8DE9-002481E0D974.root',
       '/store/mc/Summer12_DR53X/TBarToLeptons_s-channel_scaleup_8TeV-powheg-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FAC23CAA-21E3-E111-A8E7-003048C68A8E.root' ] );


secFiles.extend( [
               ] )

