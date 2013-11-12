import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/02484A50-E0FC-E111-AA0C-E41F1318099C.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/0E6206A3-E7FC-E111-8F93-E41F13181D28.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/22E8A302-E2FC-E111-ADA6-00215E21DC1E.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/3023AA5C-E3FC-E111-92F9-001A645C984A.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/30E793D4-EFFC-E111-8A7E-E41F13181568.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/52EFFD4A-EAFC-E111-84E0-00215E93DCFC.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/6C578504-E6FC-E111-B4D3-00215E2220F4.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/7A32E2D0-BFFC-E111-9920-00215E22181E.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/80F69B9F-C7FC-E111-89B2-00215E21D6DE.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/C6C7C30B-DBFC-E111-8DE8-E41F13181600.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D0C38635-A7FC-E111-BB9E-00215E21D78C.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/D6778137-B4FC-E111-A77B-E41F13180A64.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/ECB85F92-E2FC-E111-BF98-00215E221E7E.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/F26E1E5B-E5FC-E111-8F32-00215E2220F4.root',
       '/store/mc/Summer12_DR53X/ZPrimeToTTJets_M1000GeV_W100GeV_TuneZ2star_8TeV-madgraph-tauola/AODSIM/PU_S10_START53_V7A-v1/0000/FCC867AA-DEFC-E111-992F-E41F13181A6C.root' ] );


secFiles.extend( [
               ] )
