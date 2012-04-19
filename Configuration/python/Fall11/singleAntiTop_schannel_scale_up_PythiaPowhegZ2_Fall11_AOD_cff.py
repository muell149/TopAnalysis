import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/047B1E1D-0756-E111-B79F-E0CB4E29C4D6.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/1A83BE58-0356-E111-8723-E0CB4E29C514.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3C60843D-1D56-E111-8E83-20CF305B056C.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4ADA937D-FA55-E111-BE08-20CF3027A629.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/225611F8-2B56-E111-84CB-90E6BA0D09B0.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/267D2020-1056-E111-A45A-20CF305B04F5.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/3098040E-0556-E111-A26B-BCAEC54B302D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/984CA04A-0156-E111-9801-20CF305B0594.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/BAFFD71E-0C56-E111-844E-E0CB4E1A115D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/520599AD-0A56-E111-B15F-E0CB4E1A117F.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/648FDC6C-FD55-E111-8F81-90E6BA19A223.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/88BEBA60-0056-E111-977E-20CF305B0594.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/8C258932-0956-E111-8410-485B39800C31.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C233B34C-1256-E111-84D7-20CF3027A635.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaleup_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C41F94F8-FB55-E111-9F9F-90E6BA0D09BB.root' ] );


secFiles.extend( [
               ] )

