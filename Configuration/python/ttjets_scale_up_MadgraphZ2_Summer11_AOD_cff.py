import FWCore.ParameterSet.Config as cms

#######################################################
# Dataset: TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola #
# Events : 930483 (60 files)                          # 
# eff    : 1.0                                        #
#######################################################


maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/047163CC-33DB-E011-87A6-001A647894C4.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/085F3ED5-35DB-E011-960B-001A64789E00.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/08D4AA2F-31DB-E011-B2C6-001A64789D20.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1039ED13-3EDB-E011-A9A1-001A64789E20.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/10A03180-4EDB-E011-A500-0025902008F0.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/127CF5C6-42DB-E011-9BD7-0025902008F0.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/12A1CB53-51DB-E011-88ED-002590200984.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/12DD1AC6-3FDB-E011-BDD7-0025902008F0.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1434BD82-50DB-E011-B392-002590200810.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/14ACADEA-2FDB-E011-981C-001A6478949C.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C6F2EFE-2ADB-E011-BE19-002590200868.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2041319B-4BDB-E011-AA77-0025901248FA.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2AB5DDDC-4DDB-E011-AE7A-002590200A80.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2E0ADAC7-49DB-E011-8590-003048673F9E.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/30251771-28DB-E011-B3C5-001A64789DEC.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/303BE445-4DDB-E011-A712-0025902008AC.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/32DC4D4F-41DB-E011-A227-001A64789CF0.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/386279E9-ADDB-E011-AB88-003048673FEA.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3C9F3A5B-C6DB-E011-B80C-0025902009CC.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3E8720A8-2CDB-E011-99E6-001A64789D10.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/405D7376-4CDB-E011-9658-002590147CA2.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/485B1CA3-2FDB-E011-9000-001A647894C4.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/48A76BA7-2BDB-E011-866D-001A64789334.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/524B059A-4BDB-E011-9E80-002590200858.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5874409E-41DB-E011-939D-002590200B6C.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5E547B24-4ADB-E011-8DCA-001A64789DEC.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/62F6C688-30DB-E011-A2CE-001A6478949C.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/68DD7130-32DB-E011-92F2-001A64789E18.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/68FAD6DA-46DB-E011-9FEE-002590200AE0.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6AFCA961-48DB-E011-9127-001A6478945C.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6CF6CA5D-43DB-E011-9EDE-001A6478945C.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7C46A8E1-BDDB-E011-8D45-003048673E9A.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/82D56C50-46DB-E011-9ED8-001A6478ABB4.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/86034D5F-48DB-E011-ABD1-001A64787064.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/88DB63D2-52DB-E011-B58A-002590200A54.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/941839CA-32DB-E011-8425-001A64789448.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9C424B17-29DB-E011-8F91-001A64789D6C.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A0CA6C5B-2DDB-E011-9BDC-001A64789334.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A8A11FED-4ADB-E011-A3F0-002590200898.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B0B09E04-E3DB-E011-AED1-0025902009B8.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B0E7C3EB-4FDB-E011-A215-001A64789DEC.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BC2AAF24-37DB-E011-84E1-002590200900.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BEE57DB1-2DDB-E011-97AA-0030486740BA.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BEF8113F-44DB-E011-A977-002590200A18.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C290A7BE-47DB-E011-BDEB-001A64789E18.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C2FA906D-45DB-E011-AE82-001A6478945C.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C8DACB3D-54DB-E011-B694-0025902008F0.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CCD8C74D-46DB-E011-B775-001A64789CF0.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CE180792-44DB-E011-8994-001A647894DC.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D24807C9-29DB-E011-8A22-001A64789D20.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D898A7FF-2EDB-E011-A07C-001A6478945C.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E62B6367-29DB-E011-93AF-001A64789D54.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E6BADE01-4DDB-E011-8C48-002590200B68.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E8542DFD-48DB-E011-95F5-001A64789CF0.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E87C55DD-31DB-E011-869E-001A647894A0.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EE4F994D-4FDB-E011-A250-002590200B78.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FA29C119-57DB-E011-9C2A-0025902008AC.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FCC0D834-45DB-E011-918C-002590200964.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FCC5FB9C-4BDB-E011-9946-002590200B78.root",
"/store/mc/Summer11/TTjets_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FE328D6F-55DB-E011-B775-002590200A40.root"

     ] );

secFiles.extend( [
               ] )

