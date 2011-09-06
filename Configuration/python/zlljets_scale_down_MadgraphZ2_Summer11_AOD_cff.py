import FWCore.ParameterSet.Config as cms

#########################################################################################
# Dataset: /ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1 #
# Events : 1658995 (81 files)                                                           # 
# eff    : 1.0                                                                          # 
#########################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/02FAC445-A1C5-E011-90E6-E0CB4E19F9BB.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/063E665E-A4C5-E011-B177-0030487C6A1E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0E9C2163-A6C5-E011-B5C5-485B39771789.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/10610297-A2C5-E011-9BE9-90E6BAE8CC20.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/10A85E72-A6C5-E011-89A5-0022198F58D7.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/140666FB-A4C5-E011-AC5F-E0CB4E29C4BD.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/184DC9E1-9CC5-E011-95A6-90E6BA442F29.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1A383ACB-A5C5-E011-BC29-E0CB4E29C4F5.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1A60F489-AAC5-E011-BDE3-E0CB4E29C4FA.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2026B814-E0C5-E011-A67B-485B39800B95.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/204EABE5-9EC5-E011-AEFF-E0CB4E29C51A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/20981C9D-AEC5-E011-B74B-E0CB4E19F9A3.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/22139543-9FC5-E011-B1F0-00261834B579.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3041821B-9EC5-E011-8466-0030487CDB2C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/306D4EF9-95C5-E011-B447-E0CB4E55366E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/308DE214-A8C5-E011-AE59-0030487C6A32.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/381B3282-9BC5-E011-8739-E0CB4EA0A92A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3A224A72-99C5-E011-B03D-E0CB4EA0A934.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3CE459B5-A0C5-E011-8282-E0CB4E55364D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3E5352DC-ECC5-E011-B6C5-90E6BA19A25A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/42701371-99C5-E011-ADD8-001E4F328185.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/42D12F23-B0C5-E011-89F5-E0CB4EA0A91A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/441CDD57-9AC5-E011-AB8D-E0CB4E1A116A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/46E2E899-D9C5-E011-9F38-0030487C6A32.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/48FD4645-9FC5-E011-9E48-90E6BA19A23E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4C5561CB-A7C5-E011-B668-E0CB4E19F981.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4EF83B01-D4C5-E011-AD05-E0CB4E29C51A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/50241099-9EC5-E011-ABBA-485B39800C1B.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/50D6600D-E6C5-E011-9395-E0CB4E1A1188.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/525EAF7F-AAC5-E011-87A0-90E6BA0D09B8.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/54D8C204-A0C5-E011-B4DA-485B39800C3B.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5E3847F3-A4C5-E011-B926-E0CB4E29C4DE.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6292A2FE-99C5-E011-8B87-E0CB4E1A1177.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/66BED088-E3C5-E011-8FF1-E0CB4EA0A92E.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/685970BF-9DC5-E011-B941-485B39800C37.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6C0B8BCC-A1C5-E011-A48A-485B39800B7D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6C62EBEF-8FC5-E011-BEEB-E0CB4EA0A91A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6CCA9ACC-A5C5-E011-BEEA-E0CB4E29C4D6.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/705D63BF-99C5-E011-9E05-485B39800B65.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/72AE27C9-A5C5-E011-875A-90E6BA442F43.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/74105036-A7C5-E011-B936-E0CB4EA0A932.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/741EB16A-95C5-E011-BFEC-485B39897259.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/82E208C7-A5C5-E011-952F-485B39800BFB.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/84CA802C-ACC5-E011-A2DC-E0CB4E1A1152.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/86FCAD49-9CC5-E011-B68A-485B39800BDE.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8C36D4CB-D6C5-E011-B826-90E6BA19A248.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8C3D5AAC-FAC5-E011-B501-E0CB4E19F9A2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8C9B0709-06C6-E011-9E73-001A4BA87394.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8E27D003-9CC5-E011-9A3E-90E6BA0D09AF.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8E3558E5-9CC5-E011-98C0-E0CB4E5536F7.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/94B8E7B8-97C5-E011-A2D4-485B39800BBA.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/94D89150-A4C5-E011-8CD6-E0CB4E1A1192.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/94E575C7-A5C5-E011-933B-E0CB4E55366C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9686F0C1-C4C5-E011-84E1-E0CB4E4408DD.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/96BAF744-98C5-E011-A164-E0CB4E1A1177.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/981A9250-A9C5-E011-A050-E0CB4EA0A8ED.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9EFFA2A0-9EC5-E011-8CF0-E0CB4E1A1150.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A45C57CB-A7C5-E011-AE43-E0CB4E1A1147.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A867844C-A9C5-E011-B0B7-90E6BA442EF2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AA8D6E49-A9C5-E011-8B6F-E0CB4E55364D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AAF5AED5-DDC5-E011-ABE5-E0CB4E1A118D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AC07F364-A6C5-E011-96C4-E0CB4E553682.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AE668685-B4C5-E011-800E-E0CB4E19F96D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/AE906A34-A7C5-E011-8459-90E6BA0D09AC.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B056FA55-ABC5-E011-9CC9-00261834B5C1.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B2A362A7-B6C5-E011-91C7-00261834B55F.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BA88A6DD-9FC5-E011-A7C6-E0CB4E29C4BF.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BA96C35D-A4C5-E011-82D0-90E6BA0D09EA.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C0EAE8BC-9DC5-E011-9D9F-E0CB4E5536AA.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C258088F-AAC5-E011-BB87-90E6BA19A21C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C6AA64C3-A5C5-E011-94DC-485B39800BBF.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/C6BA4CCF-B0C5-E011-9313-90E6BA442F28.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CA915C44-A1C5-E011-9E12-E0CB4E19F98A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CC8A808A-AAC5-E011-B656-001A4BA81FB8.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D8F8929B-E9C5-E011-B307-0030487CD9C8.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E420001A-A2C5-E011-8A13-90E6BA0D09EC.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E4A41350-A2C5-E011-86D5-90E6BA442F21.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EA81A0E5-A6C5-E011-8142-E0CB4E4408DF.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EAFEE85A-A3C5-E011-839E-E0CB4E1A1179.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC9FD0EC-A4C5-E011-8910-E0CB4E553640.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_scaledown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FA9D4965-ACC5-E011-B94A-90E6BA0D09CB.root"

      ] );

secFiles.extend( [
               ] )

