import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/066EEEC3-590A-E211-A95E-0025B3E05DFE.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/06F2FBEE-4C0A-E211-ADAF-002590200844.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/0E88BBA7-400A-E211-8F78-003048D47A14.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/12945582-250A-E211-8DCB-001E6739753A.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/1CF415A4-3D0A-E211-9D5C-002590200978.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/1EDFCF87-2B0A-E211-94F8-002481E14F8C.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/229A5F37-370A-E211-98A4-0025B3E05C6E.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/00ACD800-4B0A-E211-8E74-0025902009E4.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/06B38BCA-3E0A-E211-9440-002590200B68.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/28E1D949-170A-E211-8FA5-002481E150C2.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/2A0A1C72-3B0A-E211-84A0-003048D46024.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/0864F3ED-2D0A-E211-B24C-0025902009BC.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/122E31B6-3F0A-E211-9E18-002590200850.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/249DF3A4-350A-E211-91A0-002590200814.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/2660D580-300A-E211-B7D9-003048D47A0E.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/34B630F7-450A-E211-ABDD-0025B3E063BA.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/2E3AB855-190A-E211-A0A7-003048D47A6C.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/36A172D8-760A-E211-9009-001E67397CB0.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/303F16A6-4F0A-E211-B6B2-003048670B64.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/3EE8C6A9-2F0A-E211-B559-0025902008AC.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/44737DB0-2C0A-E211-A977-003048D47A40.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/30A0BB32-490A-E211-8FDB-002590200934.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/3240E220-290A-E211-841B-9C8E991A143E.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/368B8349-5B0A-E211-B525-002590200A30.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/3AB8D1F7-4B0A-E211-AC24-0025902008D8.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/4A5BF7F1-2D0A-E211-914B-001E673971C5.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/4EF04CC6-330A-E211-950E-001E6739687E.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/50269492-470A-E211-A966-001E67396DEC.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/50BA6D05-440A-E211-8F4A-003048D4624A.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/46493B2E-370A-E211-8678-003048D4609E.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/48D88445-360A-E211-800E-002590200B6C.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/5A9CF386-230A-E211-986B-0025902009E4.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/5ADDED97-090A-E211-B089-003048D47A1A.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/605C66C4-B10A-E211-A415-001E67396CFC.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/4A22C045-630A-E211-9F60-003048D460C0.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/4A24DBBB-1B0A-E211-87E4-003048D46124.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/56421587-3C0A-E211-B529-0025B3E0654E.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/5A73F802-580A-E211-B315-002590200A1C.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/663F775F-5E0A-E211-A271-0025B3E05BBE.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/6206CA4D-2D0A-E211-994B-003048D47A4C.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/6AE3414D-260A-E211-BC87-002590200AE8.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/769D1FE1-2A0A-E211-93B2-003048D45F3C.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/62949F59-310A-E211-87C8-0025902009E4.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/78A7DFFC-4C0A-E211-9EDF-0025902008EC.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/641E158E-320A-E211-9D1D-003048D47786.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/7E6E2720-420A-E211-84CA-0025901248FA.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/64EDD4D6-320A-E211-BD37-0025B3E0651C.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/82016798-390A-E211-A452-003048D46098.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/665F2C07-460A-E211-8F1E-002590200850.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/78630816-4A0A-E211-8EF6-002590200B14.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/84813F39-5C0A-E211-8CA1-D8D385FF4ABA.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/8814F2DF-4D0A-E211-B6C5-002481E0D6A0.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/8E1A76C2-3F0A-E211-B7A4-B499BAA2AC54.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/7AB8DAD5-2E0A-E211-8618-002590200828.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/808F40CF-330A-E211-915A-003048D460BC.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/94EA34BA-3F0A-E211-9134-002590200A30.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/82D8A564-480A-E211-81F2-002590200930.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/86372D93-390A-E211-B964-002481E151B8.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/9002A1F0-290A-E211-B898-002590200B08.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/90AF3AFA-380A-E211-B6BA-002481E151B8.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/9E39DD4D-410A-E211-A5A9-002590200984.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/A02998D2-320A-E211-A094-002481E15070.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/9633B6DA-4D0A-E211-9E4C-002590200A7C.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/964960D1-5A0A-E211-A96F-002590200974.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/AC50E58E-500A-E211-ABE0-0025B3E05D40.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/ACF2109D-470A-E211-BF8E-002590200A94.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/AEE372BC-460A-E211-82B5-002590200A94.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/9698CD5A-100A-E211-979B-001E6739825A.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/A652E455-480A-E211-A748-0025902009E4.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/A6963B91-2B0A-E211-8A2E-0025B31E3C28.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/B6D8741E-4A0A-E211-B71D-984BE1089EB8.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/A89034B6-AC0A-E211-8427-0025902009E8.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/B2E360FC-4B0A-E211-AAE0-002590200AD0.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/BE795BEE-760A-E211-819B-001E67397ADA.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/C41FD441-220A-E211-A245-002590200AC4.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/C4E7CE85-520A-E211-9BD1-0025902009C8.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/C6436BC9-460A-E211-9B26-002590200938.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/B47C2445-270A-E211-AE2C-003048D46038.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/CA09586B-480A-E211-9534-002590200A94.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/B4E07FF9-440A-E211-B44A-002481E15522.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/BE231605-4C0A-E211-BF48-001E6739665D.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/BE344A10-380A-E211-969B-002481E14E56.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/C6EFAB1F-130A-E211-8FCC-003048C8EE58.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/CEBD7EE6-200A-E211-8A99-001E67396DEC.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/D0D0AAB8-350A-E211-BF80-003048D46040.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/D0FA05AD-610A-E211-B2C2-00304867407E.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/D2F76D7E-510A-E211-BAE5-002590200850.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/CADBEE7D-180A-E211-A82C-001E6739753A.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/CC332FD2-2E0A-E211-AEB4-0025B31E3C1C.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/CCF3DAA4-2C0A-E211-A359-002590200A30.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/D6BF37E7-4D0A-E211-88F6-003048C8EE58.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/E44E9BA6-240A-E211-AB29-002590200AC4.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/E4A357B2-340A-E211-8571-984BE1089EB8.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/CE5F4F27-4A0A-E211-8D04-002590200AC0.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/D4001857-2D0A-E211-8821-001E67396DEC.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/E8727C43-1F0A-E211-896C-0025B3E05C6E.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/E8F1760F-160A-E211-9BA5-0025B3E05C74.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/ECD9FB8B-500A-E211-B50C-002481E153FA.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/EE17A680-3A0A-E211-AB03-001E673986B0.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/EE5BC320-430A-E211-98BD-003048D45F8A.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/F0225920-440A-E211-814F-001E673986B0.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/D4A7B3E0-290A-E211-9C95-003048D45F24.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/D68EE6A8-1D0A-E211-9E17-002590200930.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/E646808F-520A-E211-9599-002590200B6C.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/E81605F5-4A0A-E211-A803-002481E14E30.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/F2104E11-280A-E211-A5A6-003048673F12.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/F25FB0F1-540A-E211-B37C-003048670B66.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/F615275C-1E0A-E211-891E-003048D45F9A.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/F2C187C3-5D0A-E211-A317-003048D46040.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/F8FB46A6-300A-E211-8F2B-0025B31E3C04.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/F441E81F-420A-E211-AB86-0025B3E064B0.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/F4CCD6E4-530A-E211-9247-001E67398C1E.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/FA680FFD-380A-E211-9C4D-0025B3E06548.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/FCAD616F-3C0A-E211-9568-002481E150EE.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/FE57C497-320A-E211-8918-001E6739687E.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/FA26B4FB-450A-E211-A99F-0025B3E05D76.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/2ADB26F8-3D0A-E211-8E05-002590200948.root',
       '/store/mc/Summer12_DR53X/TTH_Inclusive_M-140_8TeV_pythia6/AODSIM/PU_S10_START53_V7A-v1/00000/F86D97F4-4C0A-E211-89E4-002590200A98.root' ] );


secFiles.extend( [
               ] )

