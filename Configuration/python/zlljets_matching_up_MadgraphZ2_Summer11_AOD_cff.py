import FWCore.ParameterSet.Config as cms

##########################################################################################
# Dataset: /ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1 #
# Events : 1641367 (74 files)                                                            # 
# eff    : 1.0                                                                           # 
##########################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/04040FE7-A4C5-E011-83AA-E0CB4E4408E9.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/046923C5-9DC5-E011-85B7-E0CB4E19F975.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0805F7AF-99C5-E011-BD72-E0CB4E1A116A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/08CB4804-E7C5-E011-85B7-003048D28EB2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0A8986B1-A0C5-E011-ADD0-E0CB4E19F96E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0AA7E950-A3C5-E011-8AB3-90E6BA19A1FE.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0C282D99-9EC5-E011-AAC9-E0CB4E29C4C8.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0C37E163-ACC5-E011-B7F1-E0CB4E29C4DE.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0EFD214B-9EC5-E011-B4C2-90E6BA19A212.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/14A528C1-A5C5-E011-A3D8-E0CB4E5536EF.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/18214D9C-9EC5-E011-937A-0030487CB568.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/18FD5FD4-DBC5-E011-B31C-E0CB4E19F981.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1AD105B2-A0C5-E011-9558-E0CB4E29C4E5.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C17230E-9EC5-E011-AF37-E0CB4E1A1188.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1E58BC68-99C5-E011-9ADE-485B39800BBF.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1EF3BC83-DDC5-E011-A93D-90E6BA19A243.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1EFFC922-99C5-E011-A382-E0CB4E1A116A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/20CB40FE-EBC5-E011-95E2-485B39897259.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/225EC64E-9AC5-E011-AA31-00261834B55F.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2A75DF7E-9BC5-E011-9790-90E6BA442F05.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2E191CE4-9CC5-E011-9F00-485B39800BBE.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2E41E66D-99C5-E011-9EE7-E0CB4E553657.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/30BF1F7B-AFC5-E011-AFB1-90E6BA19A258.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/346A2946-C2C5-E011-96CF-90E6BA442F0C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/349DC862-A6C5-E011-9362-E0CB4E19F985.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/34AA6928-A1C5-E011-AE45-90E6BA19A25A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/34C3A63C-FFC5-E011-A1A1-003048678A04.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3CF02BD0-A7C5-E011-BE70-001EC9D7F213.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3E5551C3-A5C5-E011-BCEE-90E6BA442F0E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3EA86DFD-E2C5-E011-B87A-0030487CDAC2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3EE12581-9BC5-E011-B84B-90E6BA19A21C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4CCC81C2-A5C5-E011-A6CE-E0CB4E553691.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5021D22C-ABC5-E011-85A8-90E6BA442F00.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/54EAC847-A9C5-E011-8D1C-485B39800B7D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5A2899F4-97C5-E011-B71C-E0CB4E1A115D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5CECDF4E-A4C5-E011-9EE9-485B39800C13.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6213914A-F7C5-E011-97D7-90E6BA0D09EA.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/66834D41-94C5-E011-ADFC-00261834B586.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6699E34D-A4C5-E011-A76C-90E6BA442F08.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7236E44C-9CC5-E011-ACF2-90E6BA442F41.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/72371677-B2C5-E011-8D54-90E6BA19A25E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/766DC465-95C5-E011-9F3C-90E6BAE8CC07.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/78F041F9-A4C5-E011-B5E0-001A4BA9B0BC.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/809FDBBD-8FC5-E011-A688-E0CB4E29C505.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8690902A-9FC5-E011-A204-485B39800C00.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/885A840C-A8C5-E011-865B-E0CB4EA0A8FE.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8C0FB619-97C5-E011-B69C-485B39800C3D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8C1A4C5F-A6C5-E011-8BF1-485B39800BDF.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/963A2C19-97C5-E011-8711-E0CB4E553644.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9A30904E-A4C5-E011-9123-00261834B5D2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A881CA93-98C5-E011-B974-90E6BA19A20E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AAC1384C-A3C5-E011-8C0E-90E6BA0D09B8.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AED35234-9FC5-E011-9F3B-E0CB4E29C4C4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B0D2FDC7-9BC5-E011-9F1F-485B39800B62.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B4E88130-9FC5-E011-91E0-90E6BA19A214.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BC45680A-A2C5-E011-9956-E0CB4E55364D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C0A8502A-A1C5-E011-867E-E0CB4E19F96B.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C4C3FA53-9AC5-E011-B62E-E0CB4E19F95E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C6993DE8-A4C5-E011-A203-E0CB4E553686.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C69A0245-96C5-E011-BCAD-E0CB4E29C4C9.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C8B9844F-A2C5-E011-9F81-00261834B55C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CA96D980-B5C5-E011-B6DF-E0CB4E19F971.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CAE3A12A-A1C5-E011-9E2B-E0CB4E1A1186.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D0C1A287-AAC5-E011-BAED-90E6BA0D09D7.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D45FC392-D7C5-E011-9232-485B39800B84.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DA7EBAF7-97C5-E011-8A7E-90E6BA442EF4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E4146DF7-95C5-E011-944B-90E6BA442F2C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E4176D7B-AAC5-E011-BBCA-E0CB4E19F972.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E83A44C1-9DC5-E011-A3A4-90E6BA0D09AF.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E8440FE8-A6C5-E011-A9B6-485B39800BBE.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F48A6CC9-A7C5-E011-AD9D-90E6BA19A266.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F4A38A90-9AC5-E011-8C56-E0CB4E29C4F6.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F8F6B506-A2C5-E011-ABF3-90E6BA442EF8.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FE5E5BCC-A5C5-E011-BFAF-001EC9D7F213.root"

      ] );

secFiles.extend( [
               ] )

