import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FEE68C1F-93D9-E111-8926-00215E204766.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FE7CC7CB-65DA-E111-B8F6-00215E204826.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FE1DC274-F8DA-E111-A9AA-00215E21DAAA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FCDADF42-CFDA-E111-BEAE-00215E21D516.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FCD34772-E5D9-E111-9D3A-00215E229636.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FC6903EC-9CD9-E111-BE80-00215E2283FA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FC40B2BB-DCDA-E111-9633-E41F13181A6C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FACCAB85-5DDA-E111-BF1E-E41F131816A0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FAAE211C-60DA-E111-9E0E-001A645C2002.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F8DB2F2A-7ED9-E111-B979-00215E2227D8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F8343E5B-81D9-E111-BA60-00215E221FBC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F8256CAA-DBD9-E111-B641-00215E2283D6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F8230B2F-8DD9-E111-9940-00215E22175E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F815C231-5EDA-E111-B6FA-00215E2221AE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F6BC4F69-95D9-E111-82F3-00215E21F18A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F6B6E9D7-A6D9-E111-B2E9-00215E2223C4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F64788FB-E9D9-E111-BA62-00215E21D4D4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F498C196-E9D9-E111-AE23-00215E21DE7C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F4530733-E3D9-E111-85F9-02215E94EFCF.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F2EA1B38-8AD9-E111-8378-E61F13191CAB.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F2BE966B-ADD9-E111-97AC-00215E21D786.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F2644AF8-48DA-E111-9994-00215E21DB4C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F22AC1F4-83D9-E111-B883-00215E21DBFA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F205C45C-D9D9-E111-A315-E41F131815BC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F0888075-83D9-E111-BE54-00215E228C7C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F00E4F7F-98D9-E111-B3A3-00215E21DA98.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EE6989C3-93D9-E111-8833-00215E222394.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/ECBBEF3B-BAD9-E111-852A-00215E651D7A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EC6541A8-E8D9-E111-84D8-00215E204826.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EAB03AEF-AFD9-E111-866E-E41F13181AB4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EA85A094-F2D9-E111-8867-00215E2218F6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/EA14408E-88DA-E111-ADEC-E41F13181D5C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E8F08DD6-9FDA-E111-B6C2-001A645D5652.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E679C8A1-A5D9-E111-957A-001A645C982C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E671E5EB-B4D9-E111-8C92-02215E94EFCF.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E6618190-E3D9-E111-8F6D-001A645C1B04.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E6466A94-E9D9-E111-97C2-00215E21D8B8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E6303DE3-F1D9-E111-8A2D-00215E93EF34.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E6067F9C-75DA-E111-BCE5-E41F13181704.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E4C85B8C-61DA-E111-AD7D-E41F13181834.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E27424CA-00DB-E111-AE31-00215E22175E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E08743D0-E9D9-E111-8FA5-001A645CAEBE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/E080667C-A8DA-E111-8783-00215E22169E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DEFC1D26-BAD9-E111-9348-00215E21D540.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DEDE75F3-E9D9-E111-9A11-001A645C1C72.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DE98224F-DCD9-E111-9FCE-001A645C1E52.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DC9A5185-8BD9-E111-861D-00215E21D61E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DC5EFD5D-98D9-E111-AD0C-E41F13181834.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DC26E594-A7D9-E111-BE25-00215E21D8E2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DAA62C42-8FD9-E111-8B69-00215E22175E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/DA8B3450-84DA-E111-A147-00215E22185A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D86EF634-DAD9-E111-9283-00215E21D786.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D840A04F-84DA-E111-941D-00215E222790.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D83E0AD6-E0DA-E111-BD8F-00215E21EB7E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D6EFB080-72DA-E111-86F4-00215E222256.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D6BCF812-BCDA-E111-9941-00215E21D540.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D666528B-6ED9-E111-9E63-00215E21DBBE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D6450665-98D9-E111-AFFC-E41F13181590.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D4DF49CE-B7D9-E111-AD6D-00215E21D9A8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D48296C1-9DD9-E111-ADE8-00215E221EC6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D2EDA226-DCD9-E111-8CC7-00215E221FBC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D2D6996B-7ADA-E111-95C5-00215E222292.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D2BFA207-3DDA-E111-BCBB-00215E222250.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D0AE235D-5CD9-E111-BD71-E41F131816D0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D076CAFB-62D9-E111-A601-00215E21DBBE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D05A1161-AAD9-E111-A1C2-E41F13181674.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D04EA7B1-DED9-E111-88CC-00215E222442.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D0145C04-B7D9-E111-B219-00215E21DAAA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CE97A0AF-EBD9-E111-A292-001A645CAEBE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CE9671EB-8AD9-E111-A1D3-E61F13191CAB.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CE4A1CDE-BADA-E111-B72D-00215E229636.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CE342BF0-F1D9-E111-9A96-00215E21DD50.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CE2E1261-AAD9-E111-BD5D-E41F13181674.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CC9EF3EB-BBD9-E111-8DD0-00215E22053A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CC434537-B6D9-E111-BF2B-E41F13181DA4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CC055715-5FD9-E111-A1BD-00215E2223EE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CA3EF2A3-8FD9-E111-AD38-E41F131815AC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CA31B4E2-A0D9-E111-A8C6-00215E221EC6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CA2AEDA7-E5D9-E111-A710-00215E21D948.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/CA1AED5D-8BD9-E111-B1F5-00215E21D93C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C88B3953-8AD9-E111-AB8D-00215E21D9AE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C86890A0-B3D9-E111-9479-00215E25A5E2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C85C8E80-72DA-E111-914D-E41F1318162C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C80E3B02-7FD9-E111-B7E3-00215E221158.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C6CF9341-03DB-E111-B42C-00215E21DC1E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C682BDA5-A5D9-E111-ADA5-00215E228316.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C646A097-8AD9-E111-83A5-001A645C982C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C62DB425-8ED9-E111-A9C1-00215E221812.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C62580D7-F4D9-E111-BF22-00215E222340.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C61C58F2-E7D9-E111-9B86-00215E21D5BE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C421AE97-8AD9-E111-8157-001A645CAEBE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C40B7EEE-46DA-E111-868A-001A645D5826.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C29C00B5-22DB-E111-8743-001A645C8BEA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BEF6BCFB-EDD9-E111-995D-00215E228316.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BEC561CB-13DA-E111-8456-00215E2211EE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BE740E42-8DD9-E111-B754-00215E21E1C4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BE5A6709-BED9-E111-850D-00215E21D9F6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BE086F11-A6D9-E111-AC3D-00215E21D5C4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BC6BB3B9-94D9-E111-A48A-00215E221FB0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BC315CB0-65DA-E111-B33A-00215E204826.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BC19A9F2-99D9-E111-BA0E-00215E21E1C4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BC041D09-FCD9-E111-A5D5-001A645C982C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BAA7862C-92D9-E111-B79D-00215E222256.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BA785F60-E6D9-E111-9E31-00215E2225CE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/BA4F46BB-C7DA-E111-BEC3-00215E222016.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B8EE22C9-D6DA-E111-818F-001A645C0640.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B840CCD9-99D9-E111-9204-00215E21DC90.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B83E9D57-E3D9-E111-9ACB-00215E204766.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B8271FAC-9CD9-E111-AF1F-00215E222256.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B81E8CAC-E7D9-E111-8E6B-00215E22185A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B6FCC93D-5ADA-E111-8AD9-00215E2283D6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B67337B3-79D9-E111-8F3A-00215E21D72C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B62AD73A-82D9-E111-B0B3-00215E21D89A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B618E7EC-90D9-E111-8A92-00215E222262.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B4CAC836-8DD9-E111-B70F-00215E21D6DE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B4895654-96D9-E111-8A2B-00215E222256.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B47C8026-6FDA-E111-9F65-001A645BE078.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B46F246E-86DA-E111-930F-E41F13181D28.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B41D2C26-51D9-E111-A645-E41F131815B8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B25EFEDF-7ADA-E111-A977-00215E2223E2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B2544DAA-A3D9-E111-9E7C-00215E21D64E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B21EBA9A-8ADA-E111-BD19-00215E21DC90.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B21501CE-D7DA-E111-BB06-E41F13181808.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B20A3387-B2D9-E111-BF74-00215E21DFBA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B0F2810D-88DA-E111-8320-E41F13181834.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B0D54C2A-68DA-E111-BEF5-00215E221EEA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B07CA561-A0D9-E111-8BCC-E41F13181030.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/B043954E-C9DA-E111-A4B2-00215E221E7E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AEB50F7F-9BD9-E111-8539-00215E222358.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/ACC45E9F-B0D9-E111-BEAD-001A645BE1F8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/ACACB5E9-25DB-E111-96AF-00215E2211B8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AC524950-77DA-E111-B5A1-00215E2222DA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AC465F91-EBD9-E111-ADA9-001A645C2BC0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AC2CB23A-AAD9-E111-819D-00215E229552.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AC281120-C3DA-E111-A501-E41F13181A5C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AAE29E46-DAD9-E111-BF24-00215E221158.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AA8D9FEA-8AD9-E111-969A-00215E21D894.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AA7D722E-E3D9-E111-9267-E41F1318103C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/AA793EF6-10DB-E111-8787-001A645CAEBE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A85EB3E2-A0D9-E111-ABDB-00215E221EC6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A81164BE-9DD9-E111-8607-00215E221EC6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A6BA6C17-E5D9-E111-8C3E-E41F1318152C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A6AF098C-B1D9-E111-975D-00215E21F32E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A4C89EE1-AAD9-E111-9292-00215E221248.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A4B0F737-A0D9-E111-BC00-00215E2216EC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A4AAEA57-D9D9-E111-9FC5-00215E2208EE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A4A2ECF1-4AD9-E111-BF65-001A645D5652.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A484448E-8CDA-E111-B216-00215E222238.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A472EE38-82D9-E111-85C8-E41F131816D0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A425B4E2-A0D9-E111-8239-00215E221EC6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A40441A6-FDD9-E111-AA45-001A645D5652.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A2D16A89-F3D9-E111-8F86-00215E21DAC2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A26D49DE-9CD9-E111-9170-00215E2283FA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A221BBB1-94D9-E111-A69F-E61F131916C7.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A0C96BDB-7DD9-E111-A4CE-00215E21DD14.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A0AAF5F3-E0D9-E111-B0B3-00215E222796.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A09EF222-8AD9-E111-AAE3-00215E21D972.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A061168B-7CD9-E111-BE2A-001A645C208C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A042F247-6BDA-E111-A0C5-00215E2222DA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A041AD26-92D9-E111-BA6B-001A645CB218.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A02C4CCD-B1D9-E111-B948-001A645BE1F8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A027371E-B7D9-E111-A493-00215E20426E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/A00A9FB9-70DA-E111-91D6-00215E21DD56.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9ED9DC4A-CADA-E111-BCEC-00215E221A28.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9ECD6D2E-4FD9-E111-A25D-00215E22278A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9EA5E189-FBDA-E111-B7F8-00215E21DBD0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9E84ED5E-40DB-E111-8D26-00215E21EB7E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9E5E9901-8DD9-E111-9081-00215E2219E6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9E40143B-BAD9-E111-BDE6-00215E93EF9C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9C68A7B6-8FD9-E111-B78E-00215E2225CE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9AB6C42D-68DA-E111-A7E4-00215E2223E2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A94E0D4-F4D9-E111-B563-001A645C208C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A62A51B-E9D9-E111-91B6-00215E228838.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A0AEDFB-D1DA-E111-8303-001A645C2002.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9A0427D7-DCD9-E111-84CB-00215E22169E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/98AA1D30-7ADA-E111-BE34-00215E221158.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/98A65F80-CDDA-E111-8910-00215E2211B8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/98687D52-45D9-E111-A417-E41F13181A88.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/98634F13-8AD9-E111-A7B4-E41F13181564.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9827A6EF-60D9-E111-8816-00215E20498E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/966394C8-81DA-E111-A949-E41F13181CA4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/965E5D81-ECD9-E111-A742-00215E21DC90.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/94FB527B-89DA-E111-BEF1-001A645C2362.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/94D94EC4-94D9-E111-A874-001A645C97D2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/944A20BF-6FDA-E111-89DB-00215E222850.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/92BF28CA-A3D9-E111-9B92-00215E221EC6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/92329575-5AD9-E111-92F3-00215E21DB22.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/90DCCC49-92D9-E111-AFE7-00215E221098.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9063D195-B0D9-E111-B0C6-E41F1318174C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/9017C58C-29DB-E111-99F7-001A645C2392.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8EFF64C7-ABD9-E111-BA47-00215E21D7C8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8E355604-84D9-E111-88DC-00215E21DD26.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8E2AF012-D7D9-E111-91C1-00215E93EC84.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8E27C789-7CDA-E111-BDF5-001A645BF218.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8E165BC9-ABD9-E111-9331-00215E222358.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8CB188EA-AFD9-E111-AE13-E41F1318158C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8CA4CC23-C6DA-E111-AFB8-E41F131816B8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/8AFE3268-64DA-E111-A9BB-001A645C97D2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/88254FD8-67DA-E111-8333-E41F131816B8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/86CFED1C-8DD9-E111-AB6B-001A645C9BE0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/86BA6A47-E6D9-E111-866E-00215E21D8EE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/869E1755-79DA-E111-B7DF-00215E204784.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/867CA7F5-74DA-E111-A999-00215E222760.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/864B0287-6EDA-E111-BD7C-E41F131817C8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/86457256-B8D9-E111-8EF1-00215E2599A6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/84DB99A5-9ED9-E111-B220-001A645D4F7A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/84706397-8AD9-E111-92FC-001A645C982C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/82F3C6A1-A5D9-E111-BD80-001A645C982C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/82B719D2-E0D9-E111-988F-001A645C2392.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/82AA6CE0-A0D9-E111-A2F0-00215E21D786.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/82451250-E6D9-E111-B7DE-E41F13181710.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/82373852-76DA-E111-B6A9-00215E21E1C4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/80ED9BFB-E7D9-E111-8413-00215E2217CA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/80A094A0-B4DA-E111-AB6E-E41F13181A70.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/80983247-ABD9-E111-84D8-001A645C972A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7E72C29E-69D9-E111-870F-00215E221B48.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7E36C2E5-86D9-E111-A6A4-00215E221BC6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7E211700-73D9-E111-AA99-00215E22223E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7E094EFF-AED9-E111-8FF3-00215E21DD26.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7CF41546-8AD9-E111-B7D8-00215E22275A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7CDFD181-98D9-E111-86B8-00215E203E36.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7C022183-F2D9-E111-822C-00215E2225CE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7C01E85D-E8D9-E111-8964-E41F13181568.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7C01E55B-CEDA-E111-AE39-00215E22158A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7ADA4D48-DAD9-E111-99E2-E41F131815BC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7A7A7034-77D9-E111-BCD3-001A645C97D2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7A2FCBFB-8ADA-E111-8747-00215E21DB58.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7A179B8E-9BD9-E111-9F91-001A645C9BE0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7A0E6551-AED9-E111-9399-00215E21D786.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/78D0C4EB-BCD9-E111-AC95-00215E222442.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/789D659A-27DA-E111-AF6D-00215E221FF2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/786C3EF0-79DA-E111-8A6D-00215E202F8A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/76697747-80DA-E111-8337-00215E21DAB0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7664106B-23DA-E111-8A0B-001A645C1660.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/761C72EA-89DA-E111-BCDE-00215E2222CE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/74FAB1CE-9ED9-E111-8A7F-00215E21DAAA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/74BF1517-E7D9-E111-9F44-00215E21DB3A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/72E3DC6D-83DA-E111-BCA4-E41F13181ADC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/72C5EBEB-D2DA-E111-8FC3-00215E228B20.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/72A2FA4C-A0D9-E111-A642-00215E21DCD8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/70EED7EB-EDD9-E111-B9FA-00215E21D750.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/709B5845-DAD9-E111-9F86-00215E21D9F6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/705F8568-24DB-E111-98F8-E41F13181808.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6EC4736B-95D9-E111-8536-E61F131916C7.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6EA1371E-92D9-E111-91CB-00215E22185A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6CBEE24B-8FD9-E111-A1C2-001A645C8F8C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6C7F965B-92D9-E111-A06E-00215E2283D0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6C306E67-E4D9-E111-A59F-00215E21DD32.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6AF7C3A1-A3D9-E111-AEA0-00215E221EC6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6AABFC78-8EDA-E111-B767-E41F13181030.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6AA24D57-96D9-E111-9DAE-00215E21D948.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6A9CFF17-7EDA-E111-8451-00215E229636.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6A902EA2-68D9-E111-9F5E-00215E2213EC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6A2129A1-FBD9-E111-B7E7-E41F13181D48.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/68AA34C5-71DA-E111-8A8F-001A645C0934.root' ] 
);
readFiles.extend( [

       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/68390452-D7D9-E111-9821-00215E21D9F6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6829D3DF-7ADA-E111-9AC4-00215E221E7E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/66FFB611-B5D9-E111-AEA5-00215E228394.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/66AFD2AE-E2D9-E111-9262-001A645C8E36.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6676616E-EBD9-E111-AF47-E41F131812CC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/667516BC-8FD9-E111-B648-00215E2225CE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6636409F-7FDA-E111-BC08-001A645C1426.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/66067488-83DA-E111-B1D1-02215E94EE47.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/629429A2-98DA-E111-8882-00215E2227D8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/628275E4-B3D9-E111-935C-00215E93C8B0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/60E5DDCC-0ADB-E111-91A6-00215E22284A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/60D48280-7DDA-E111-8AFD-00215E21D56A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6013899A-73DA-E111-AE8D-E41F131815A8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5E6926A4-6EDA-E111-B580-00215E229636.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5CBECDC2-A1D9-E111-8483-00215E222262.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5CA6B89C-B3D9-E111-9659-00215E2225CE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5C70623F-D3DA-E111-B7D6-00215E220918.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5C1C6F31-E3D9-E111-A4AD-E41F13181834.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5AF3E5CE-8FDA-E111-9FCC-00215E259C52.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5AD7C056-76DA-E111-9B34-00215E221938.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5A910291-D7D9-E111-9751-001A645C0E8C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5A8CF68B-E3D9-E111-87A6-E61F131916AB.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5A533DBC-9BD9-E111-B15F-001A645C1132.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5A4B3162-96D9-E111-BCCF-00215E222790.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/58E0F3EF-99D9-E111-A7CF-E61F131916AB.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/583853C8-9BD9-E111-90A2-001A645C1132.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/581EBD0B-9FD9-E111-A9FD-001A645C1132.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/58135953-A8D9-E111-A477-001A645CB218.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/56FB5AB3-83D9-E111-BCB5-00215E21DBF4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/56B8F806-8AD9-E111-BCA6-00215E21DAAA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/56493462-E4D9-E111-A7E4-00215E21D870.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/5645A640-98D9-E111-8D46-E41F1318148C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/561834AC-8FD9-E111-8B11-00215E2225CE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/54DC2606-9AD9-E111-9E06-001A645C2050.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/54CB5C33-E3D9-E111-913B-00215E221170.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/54538E90-71DA-E111-9FC3-00215E22237C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/544D5622-E1DA-E111-A927-00215E21DC2A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/52F154B8-ABD9-E111-A418-E41F131815C0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/50E46DE3-99D9-E111-AAA3-00215E21DBFA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/50D58031-E3D9-E111-AF86-00215E2211D6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/50CD6854-AED9-E111-B42E-00215E21D8E2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/509FB847-7FDA-E111-8AF6-00215E220F78.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/506D60E0-BCD9-E111-B5AE-00215E21D9F6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/500B095D-81D9-E111-8A3B-001A645CAC06.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4EACBD4D-E7D9-E111-AD8B-00215E204664.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4E957511-A6D9-E111-98BB-00215E21D5C4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4E356B65-E4D9-E111-89D9-00215E93EC84.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4E30D53D-79DA-E111-B372-00215E222292.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4C8F8A5A-31DA-E111-800B-00215E222250.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4C778BA5-71D9-E111-8A6E-00215E2216EC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4C69745C-85D9-E111-8125-00215E21DA50.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4C3B1608-A2D9-E111-BACB-001A645C1660.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4C1BF3C7-9DD9-E111-97AC-00215E221EC6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4C15DF1E-8ED9-E111-8C2E-001A645C9BE0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4AE8DA4F-AED9-E111-A0C2-00215E21DD26.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4AE63A35-B6D9-E111-94C8-02215E94EFCF.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4AE38525-B5D9-E111-9E89-02215E94EFCF.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4ABBF95B-E7D9-E111-BD91-001A645C1C72.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4A751F02-BCD9-E111-B8E4-00215E21DB58.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4A663161-AAD9-E111-8C7F-E41F13181674.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4A293ACB-EBDA-E111-97B0-00215E21DD56.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4A1693A8-E2D9-E111-A600-001A645C982C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/48DB834C-B8D9-E111-8BB7-00215E221224.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/48CCA6B6-94D9-E111-9B77-00215E2217BE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/487D17FD-AED9-E111-933A-00215E21D786.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/486F8AB8-93D9-E111-9D3D-00215E2212D2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/46E467B2-8FD9-E111-BC46-00215E204826.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4677F024-7FD9-E111-A4E2-00215E2227F6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/46646627-92D9-E111-A826-00215E204766.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/4657A3E3-AFD9-E111-AAC2-E41F13181AB4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/46409BFA-80D9-E111-8D2D-00215E21D942.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/44ECF1A1-B0D9-E111-B398-00215E222790.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/44E5E7B7-A1D9-E111-80FA-00215E21D786.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/448F703B-AAD9-E111-B674-00215E222382.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/444404C9-73DA-E111-8B1A-00215E2217A0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/42B8879B-C9DA-E111-A733-00215E21D570.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/428F3FEB-AAD9-E111-8CA2-00215E222382.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/426FA4B7-94D9-E111-97CF-00215E22165C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/421750A4-0CDB-E111-96EB-E41F13181834.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/40FBB810-DDDA-E111-8A30-00215E222292.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/40C6D262-ACD9-E111-BE98-00215E222358.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/40A2AED1-94D9-E111-998A-00215E22165C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/40386F9E-9ED9-E111-B3D9-00215E21EBAE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/401E5AB6-E2D9-E111-9C9B-001A645C8E36.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/40007006-B4D9-E111-A4E7-00215E651D7A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3EC7763D-98D9-E111-9641-E41F13181668.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3E230311-FEDA-E111-B716-001A645C9BE0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3C75E952-E1D9-E111-A103-00215E221FF2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3C564152-6CDA-E111-B8FE-00215E21D8B8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3C2946DF-99D9-E111-BAFA-001A645C2362.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3AE9BF78-54DA-E111-9326-00215E259C52.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3AE6A132-A8D9-E111-B1F6-00215E21D62A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3AC410A1-B0D9-E111-BB28-E41F131817EC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3A57143B-8FD9-E111-B960-E41F13181A6C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3A17DC67-85D9-E111-BAF2-00215E222808.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/38B2AE2D-86D9-E111-88F0-00215E2211AC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/38921142-98D9-E111-91F2-E41F1318148C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/383F601B-81DA-E111-84B7-00215E21DBA0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/381E68DC-75D9-E111-AE57-00215E21D61E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/36E61465-EDD9-E111-BA94-00215E228838.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/368B3AF9-BBD9-E111-A757-001A645C3D36.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/34F704C6-A1D9-E111-8C2D-00215E93DCFC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/346F66E3-AFD9-E111-B47E-E41F13181AB4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/341C8BA8-A5D9-E111-9DC7-001A645C982C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/32E351D4-93D9-E111-9A07-001A645C1E52.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/32D86CE5-90D9-E111-83DE-00215E2212D2.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/32BF1D42-8DD9-E111-A64B-00215E21E1C4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/32A2C367-CEDA-E111-8845-00215E21D91E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3220C135-C1DA-E111-8C36-00215E222394.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/32045D81-ECD9-E111-BC86-00215E21DC90.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/30EE2389-8BD9-E111-AD2E-00215E22175E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/30B50AE2-9CDA-E111-8880-00215E21DA44.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3081AF87-9BD9-E111-A119-00215E21DD68.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3076671F-8ED9-E111-A966-00215E204766.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/303B1547-A8D9-E111-ACFB-00215E21DC7E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/301FB75D-ACD9-E111-B798-E41F13181030.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2EC06318-87DA-E111-9311-E41F13181CF8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2EADBE25-BAD9-E111-A469-00215E2211F4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2E903C08-6DD9-E111-BB5B-00215E93F06C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2E57D244-F6D9-E111-8245-00215E21D75C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2CE71EBD-9ED9-E111-9244-00215E222382.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2CCA6C5A-7FDA-E111-B66F-00215E204844.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2C8B2FF9-99D9-E111-983F-001A645C2050.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2C0EF05B-8EDA-E111-9E94-00215E21D516.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2AE16747-04DB-E111-8DB8-00215E2216EC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2A8B1453-85D9-E111-8B80-00215E21D64E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2A4092B1-B7D9-E111-8C1A-00215E21D72C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2A0402D6-9BD9-E111-8296-001A645C1132.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/28F612B7-E6D9-E111-9F08-00215E22165C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/28F25CBB-73DA-E111-AE93-001A645C1B04.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/28898EA9-7CD9-E111-A897-E41F131816D0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2884531A-87DA-E111-AE25-00215E21DA26.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/26BEEF79-EFD9-E111-9A94-00215E21D5C4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/265BDAB2-F2D9-E111-A012-00215E21D61E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/24F06A4B-96D9-E111-8C67-00215E2222DA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/24BF3589-EBD9-E111-ADEC-00215E21EC4A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/24B4FDCA-9CD9-E111-91B5-00215E2283FA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/24B3AC80-ACD9-E111-AE3D-001A645D5406.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/24AE446E-E5D9-E111-82FE-001A645C2BC0.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/247871DB-E0D9-E111-8012-001A645C2392.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/245D57BC-B2D9-E111-B740-00215E651D7A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/224CF4F5-7EDB-E111-9CC0-00215E21DD0E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/2248EAC2-A3D9-E111-ACEC-00215E203E36.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/20E101FE-81DA-E111-8E41-001A645C2002.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/20696A5B-7FDA-E111-AAEE-00215E21D582.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/206641D7-D9DA-E111-B651-00215E21DD3E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/20474CBE-93DA-E111-8704-00215E21DC2A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1EF409CD-86D9-E111-91D4-00215E2217BE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1EA0444D-E8D9-E111-B236-00215E222712.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1E60FEDE-8CD9-E111-BD35-E41F13181CA4.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1AC6B3B2-65D9-E111-BB3F-00215E21D702.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1A9BA399-A5D9-E111-9791-001A645C982C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1A15C412-78DA-E111-A2CC-001A645BE078.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/16C5E82B-B7D9-E111-82E9-E41F13181A6C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/1687F074-95D9-E111-92D0-00215E21EBCC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/166D30F4-90D9-E111-BD84-E41F131816B8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/163E395E-79DA-E111-94B7-001A645C158E.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/14E61563-ACD9-E111-AB9B-00215E21D7C8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/14E42415-8ED9-E111-95BD-00215E21D6A8.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/14145DA1-53D9-E111-ABB2-00215E21DA50.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/12B1102B-8AD9-E111-82FA-00215E2222DA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/126624B8-57D9-E111-A021-00215E21DC60.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/125A7ADB-EED9-E111-99E4-00215E93EC84.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/120F8449-7BDA-E111-9F66-00215E204766.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/10D78CC8-A6D9-E111-A387-00215E222244.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/10AF26D8-E3D9-E111-BC65-00215E2222DA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0EF60912-CCDA-E111-92DE-00215E21DC78.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0EA28A07-8DD9-E111-92CF-E41F13181D30.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0E912DDC-8FD9-E111-BA54-001A645C972A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0E809D49-81DA-E111-988C-001A645CAEBE.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0E73ACD5-80D9-E111-8B65-00215E21DFBA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0E65602D-91DA-E111-962B-00215E21DD98.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0E2D68A1-A3D9-E111-AF07-00215E221EC6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0E06B967-6CDA-E111-8F8A-00215E21DFBA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0CFEC680-77DA-E111-8E51-00215E22185A.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0CBE40F4-74DA-E111-B044-00215E222340.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0AF75AD2-9BD9-E111-99B5-001A645C1132.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0ACDB211-9DD9-E111-99D9-00215E2283FA.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/08BA0C5F-96DA-E111-B989-00215E21DF18.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0894108B-D7DA-E111-99C4-001A645C208C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/067B1559-52DA-E111-AC77-00215E21D786.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0622E5A0-E9D9-E111-9C1A-00215E222226.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/06223675-83D9-E111-8E11-00215E228C7C.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/04CFCDEC-B4D9-E111-8C49-02215E94EFCF.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0465BC74-B2D9-E111-83D2-E41F13181ADC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/041A6882-8EDA-E111-BB65-00215E221938.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/02D2AADF-D9D9-E111-9A50-00215E2048E6.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/02C8F7BA-6FDA-E111-B388-00215E2222EC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/00D5BFD4-D2DA-E111-A0B6-00215E21D702.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0036E360-63DA-E111-9656-00215E2205AC.root',
       
'/store/mc/Summer12_DR53X/ZZJetsTo4L_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0018D5BA-62DA-E111-99A2-E41F13181ADC.root' ] 
);


secFiles.extend( [
               ] )

