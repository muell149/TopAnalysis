import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       ## 22 files
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/062EB220-AFF8-E011-B0EA-E0CB4E29C4D3.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/06CBA3CC-BAF8-E011-BF05-00221992FF06.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/1EFA9C08-94F8-E011-AD5D-90E6BA19A252.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/20512CDA-9DF8-E011-9C7C-485B39800B75.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/2C118FD7-99F8-E011-822C-E0CB4EA0A937.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3656ABB1-95F8-E011-9EDB-E0CB4E55367B.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/44EEF839-97F8-E011-8835-E0CB4E1A118D.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/462E2B4B-A3F8-E011-9AE6-003048D28EB2.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4AFCDFDA-9BF8-E011-A2B9-20CF30561716.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4CEF998A-A1F8-E011-99BC-485B39800BB3.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/68783D01-A1F8-E011-9F09-003048D29312.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/6CDED563-91F8-E011-B885-0022198F5D7B.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7C58EFB6-95F8-E011-9082-E0CB4E1A116E.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8662B029-A3F8-E011-B6A9-90E6BA0D09A7.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8AE04744-92F8-E011-9CA4-90E6BA19A22D.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/90DBC872-AAF8-E011-98C9-E0CB4E19F962.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/9A6F742F-95F8-E011-8D54-90E6BA442F2B.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/A654EBC9-6EF9-E011-B64D-0030487C6A90.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B4D6E32B-99F8-E011-B642-E0CB4E29C51E.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/BCE7783E-BAF8-E011-8C3C-00261834B565.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/E61585DB-9FF8-E011-9E08-E0CB4E29C4EC.root',
       '/store/mc/Fall11/T_TuneZ2_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F4C31935-A0F8-E011-9828-003048678948.root' ] );


secFiles.extend( [
               ] )

