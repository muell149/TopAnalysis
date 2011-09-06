import FWCore.ParameterSet.Config as cms

#######################################################################################
# Dataset: /ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1 #
# Events : 1593052 (75 files)                                                         # 
# eff    : 1.0                                                                        # 
#######################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/006F7EC7-29C6-E011-96BA-001A4BA87F02.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/00970243-25C6-E011-B752-0030487C6A1E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0273E283-1CC6-E011-97F3-E0CB4E1A118F.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0EA9C851-21C6-E011-943F-0030487C6A1E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/12ADEC22-24C6-E011-81E9-00221992FF06.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/14931B05-21C6-E011-933E-E0CB4E29C513.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C19214E-21C6-E011-92DF-485B39800BC0.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1C710BF9-38C6-E011-BC44-485B39800BB0.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1E0FB76E-22C6-E011-B6B0-485B39800C23.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1EC032A4-1FC6-E011-BAB2-001A4BA8B3F4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/201AB59D-1FC6-E011-8292-E0CB4E19F95D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/20AC7DF9-18C6-E011-B4B1-001A4BA8B3F4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2252F2E4-1FC6-E011-A53A-485B39800C2D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2412F3D2-28C6-E011-A2C5-0030487C6A1E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/26E51855-1FC6-E011-96C3-90E6BA442F10.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/320BEDE4-1FC6-E011-92A4-485B39800B65.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/32D170F7-1DC6-E011-83B2-00261834B561.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/346C0CA1-13C6-E011-8510-E0CB4E1A11A2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/34B9F3AA-1BC6-E011-A719-E0CB4EA0A909.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/383A1CB8-24C6-E011-867B-0030487CDAC6.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/383EC246-23C6-E011-AD45-E0CB4E1A1189.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3856C640-1CC6-E011-8307-0030487C6A1E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3868EEAB-21C6-E011-9CD3-90E6BA0D0994.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3C582E1F-1BC6-E011-A568-0030487C6A1E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3EC79153-30C6-E011-8106-E0CB4E29C4D7.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4066953B-1CC6-E011-BAD5-E0CB4E1A1144.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/40E75E9D-1FC6-E011-91DA-485B39800C36.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/460D9635-1FC6-E011-A6E6-0030487C6A1E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/50600D35-19C6-E011-9ABF-E0CB4E29C4BD.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/520EFDBC-19C6-E011-90CF-001A4BA54360.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5C07931E-24C6-E011-A91E-485B39800BFD.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5C3DE0F6-1DC6-E011-9F82-E0CB4E29C4C6.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5CF867D6-23C6-E011-997F-E0CB4E1A1144.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/680CE04F-21C6-E011-AC68-485B39800C23.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6ADB1487-25C6-E011-82D2-485B39800C36.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7A2118A4-1DC6-E011-9C6A-485B39800BC0.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/7A5D0BC7-2AC6-E011-9422-0030487C73D4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/88028FDE-27C6-E011-BD88-00221992FF06.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9042696D-26C6-E011-98F5-90E6BA442F15.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A0515946-2FC6-E011-B7AD-E0CB4E29C4D7.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A07083D6-23C6-E011-8D61-485B39800BE3.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A0D15A02-1AC6-E011-862B-00261834B55C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A206534F-3EC6-E011-AA52-485B39800BB0.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A83249CB-1CC6-E011-AE64-E0CB4E29C4BD.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AADA60BC-2DC6-E011-B639-485B39800B9F.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AC7C60B1-21C6-E011-B063-E0CB4E19F9BC.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B075183D-22C6-E011-8765-E0CB4E4408DF.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B0F1F774-20C6-E011-97AA-485B39800BFD.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B64A1E66-6DC6-E011-9D25-E0CB4E553657.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B67FB61A-28C6-E011-8BE6-001A4BA87F02.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B6AD5C64-28C6-E011-8217-0030487C73D4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B8A200A8-26C6-E011-931F-E0CB4E1A118F.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BA22124A-23C6-E011-BF53-00221992FF06.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C0B6034C-2CC6-E011-A563-0030487C73D4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C44D6713-2AC6-E011-82B5-E0CB4E1A118F.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C80E5738-1EC6-E011-8F0A-0030487C6A1E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CA5933DE-21C6-E011-A5B0-485B39800BC0.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CC47B65B-1DC6-E011-A2D2-E0CB4E1A118F.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CCA17D64-1BC6-E011-887D-90E6BA442F04.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CE39046C-1BC6-E011-8F80-90E6BA19A21C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D6307891-23C6-E011-9AB4-90E6BA442F3C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D8010309-21C6-E011-A34A-00221992FF06.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/DCAAFCD5-25C6-E011-A51A-485B39800BE3.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E201CE14-1DC6-E011-96E6-485B39800B65.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E4231D3D-27C6-E011-B236-485B39800BC0.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E6491F94-23C6-E011-A824-E0CB4E553665.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E6BEF231-1FC6-E011-8A5B-485B39800B65.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC1C3A33-22C6-E011-B28B-E0CB4E1A118F.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EE07F369-1DC6-E011-97B6-0030487C6A1E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EED04488-25C6-E011-A73F-90E6BA442F3C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F09EDA64-1AC6-E011-8584-E0CB4E1A11A4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F2179D0E-4CC6-E011-B6B2-E0CB4E29C51F.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F8FB313E-20C6-E011-9F30-0030487C6A1E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FAAE894E-21C6-E011-A555-90E6BA442F3C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaleup_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FC13A600-23C6-E011-B408-90E6BA442F10.root"

      ] );

secFiles.extend( [
               ] )

