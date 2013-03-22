import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/FEE84EA9-2B43-E211-AF67-0017A4770C08.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/FCB14D03-3943-E211-A776-0017A477081C.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/FC2A30AC-2F43-E211-B270-00237DA1DDFC.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/FA0C9F62-3443-E211-9E09-00237DA1ED1C.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/F25EA8BB-3243-E211-850E-00237DA13C16.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/ECCD6D5D-3043-E211-A70D-0017A477081C.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/EA32FBBF-3743-E211-8DEA-1CC1DE040FE8.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/E6D8528A-3743-E211-8F4F-1CC1DE1CE170.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/D67B5DCA-3643-E211-8FD0-1CC1DE1D014A.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/C0F95D8C-2543-E211-B394-1CC1DE1CE128.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/B86F145A-3343-E211-A447-0025B3E0216C.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/B0149802-3843-E211-A19D-0017A4770414.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/A8FB8E1E-3743-E211-8C16-0017A4771020.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/A68B18C6-2C43-E211-970E-1CC1DE046F00.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/9A5741B4-3243-E211-AD3F-1CC1DE1CDCAE.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/92B78D5F-3843-E211-9488-0017A4770C10.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/86976826-3B43-E211-B99D-0025B3E0228C.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/840AC7FF-2D43-E211-800A-AC162DABAF78.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/829F0AA7-3C43-E211-9BF0-0025B3E02292.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/828150C1-3143-E211-8AC5-00237DA1ED1C.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/7CD9B27E-2943-E211-AB38-00237DA12CE8.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/7C031459-4143-E211-BD61-1CC1DE1CE128.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/76ACF461-3243-E211-A029-1CC1DE041F38.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/7205C886-3543-E211-8FDB-1CC1DE1D023A.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/50153962-3243-E211-A96E-1CC1DE1D1FE6.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/44ABCBED-3443-E211-997C-1CC1DE051118.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/428A73D6-3043-E211-8C17-0017A4770C10.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/2C40F73F-3043-E211-9362-0022649F01AA.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/2899374C-3943-E211-9ECF-0017A4770828.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/269F6D6F-2743-E211-86CE-1CC1DE1D03EA.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/2453F1D5-3043-E211-9629-1CC1DE055158.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/22D77298-3343-E211-AD8F-0017A477083C.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/1E594BD3-3843-E211-A651-1CC1DE046F00.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/1ACA2EFE-5343-E211-AEA4-0017A4770020.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/126F92EF-3943-E211-AB5B-0025B3E020D0.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/0C508B29-3643-E211-9D0D-1CC1DE1CEDB2.root',
       '/store/data/Run2012C/MuEG/AOD/EcalRecover_11Dec2012-v1/10000/025B77BF-3A43-E211-AD8D-001F296B9576.root' ] );


secFiles.extend( [
               ] )
