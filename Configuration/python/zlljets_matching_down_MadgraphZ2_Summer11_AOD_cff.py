import FWCore.ParameterSet.Config as cms

############################################################################################
# Dataset: /ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1 #
# Events : 1615032 (72 files)                                                              # 
# eff    : 1.0                                                                             # 
############################################################################################

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [

      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0472AB4A-20C3-E011-903E-E0CB4E29C4E9.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/063ADC3D-23C3-E011-ABFD-0030487CDA68.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/08D076A2-2CC3-E011-A107-003048D29312.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0C9178D8-20C3-E011-B5FB-485B39800B65.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0CD97FBC-1FC3-E011-B5F2-0030487CD9C8.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0E603316-25C3-E011-95F3-0030487CDAC2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/0EA5ABAD-1BC3-E011-8F70-90E6BA442F42.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/185DC166-26C3-E011-ADDA-003048D29312.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1CFAFCD6-29C3-E011-A47D-0030487C73D4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/1EF0F2B6-24C3-E011-9001-003048D28EB2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/20D18545-20C3-E011-8C57-E0CB4E29C504.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/22EEB490-22C3-E011-8C94-0030487CDA68.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2A1814B2-1FC3-E011-AF8A-485B39800B8B.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2A18CB6B-22C3-E011-961F-003048D29312.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/2E1EC5E6-25C3-E011-A6DC-0030487CD6A6.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/325F8877-1EC3-E011-A81C-0030487CDAC2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3296A670-25C3-E011-9D29-E0CB4E19F962.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3435FCBE-26C3-E011-9D2D-003048D28EB2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/38EC7EB1-1EC3-E011-BAC9-0030487CD9C8.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3A282B3B-1EC3-E011-9C90-003048D293B4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/3E3ED9E4-56C3-E011-9CCF-E0CB4E55368D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/42943F66-33C3-E011-937B-90E6BA442EEE.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/44CD1E9D-1EC3-E011-B2CC-0030487CDAC2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4659A39D-24C3-E011-A591-90E6BA442F2B.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/4EBDD44A-20C3-E011-9079-E0CB4E19F958.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/569BCE23-21C3-E011-B848-E0CB4E55366C.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/58DA01DB-22C3-E011-8329-E0CB4E1A1180.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5C27429E-23C3-E011-AF51-0030487CDAC6.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/5EFA9089-23C3-E011-B210-0030487CB568.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/64EC6F02-2EC3-E011-8AE6-0030487CDAC2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/66298A2E-1CC3-E011-A727-0030487C73D2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/6ADCA13F-28C3-E011-AEB5-0030487CD9C8.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/745C55A7-28C3-E011-AAC1-0030487CDAC2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8082C874-1AC3-E011-9A57-0030487CD9C8.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/84B62F6B-2FC3-E011-A5CA-0030487CDA68.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/84B664FD-21C3-E011-8196-00261834B580.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/84D4C2E7-24C3-E011-8161-E0CB4E29C4DC.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/868B5F46-20C3-E011-AD57-E0CB4E553656.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/88F087DB-28C3-E011-A3BF-003048678A04.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/88FB0F59-27C3-E011-A236-003048D2910A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8A9E6A0E-27C3-E011-A9BE-0030487CDAC2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8EC05F9C-23C3-E011-83CC-0030487E3026.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/8EC0F96B-28C3-E011-A2A1-003048D2910A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9014AE9C-29C3-E011-8CD1-0030487CDA66.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9A153AFC-55C3-E011-A8C8-E0CB4E4408CD.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9A99FF72-27C3-E011-923F-E0CB4E29C50D.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9AC45675-1BC3-E011-B583-0030487CDB24.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/9C5C502C-2BC3-E011-961D-0030487CDAC2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A4243B22-2AC3-E011-9393-003048D2910A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/A8335C20-2AC3-E011-9302-0030487CDAC2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B001886B-28C3-E011-9432-0030487C73D4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B03512CD-26C3-E011-8454-003048678A04.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/B6A0F207-1DC3-E011-9D81-0030487C73D4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BA002FDA-22C3-E011-A652-E0CB4E29C4DC.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/BE5DA85E-28C3-E011-AA30-003048D293B4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/CE8BA561-26C3-E011-85EC-003048678948.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D6211DD6-28C3-E011-B333-003048678948.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/D63840FB-23C3-E011-A97E-003048D2910A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E005AADB-20C3-E011-B83A-E0CB4EA0A934.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E0991696-2EC3-E011-A8E1-003048D29312.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E0C2C732-2BC3-E011-AE76-003048D29312.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/E41CC25D-2AC3-E011-8C44-0030487CD6A6.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EC85140C-2CC3-E011-AD1D-003048D2910A.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/EE6E1CB5-21C3-E011-9888-90E6BA0D09EA.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F07240DA-22C3-E011-8040-E0CB4EA0A900.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F29047B4-26C3-E011-915C-003048D28EB2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/F4ED3EC5-2DC3-E011-AAA5-003048D29312.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FC3D1F23-29C3-E011-8D63-0030487CDAC2.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FC90AA91-27C3-E011-8255-003048D29312.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FE94B95C-24C3-E011-911F-003048678948.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEE3128C-29C3-E011-8A95-0030487C73D4.root",
      "/store/mc/Summer11/ZJetsToLL_TuneZ2_matchingdown_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FEFCBFDD-2AC3-E011-B35A-0030487CDAC6.root"

      ] );

secFiles.extend( [
               ] )

