import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B47F0018-0D32-E111-98A2-90E6BA19A223.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/74330A33-F231-E111-9368-20CF300E9ED3.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/B4A83810-1832-E111-A522-E0CB4E19F981.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/7ED8B973-0232-E111-A523-E0CB4E19F9AC.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/C297D30D-0532-E111-B443-E0CB4E19F970.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/DE3F2021-0932-E111-8864-001EC9D7FF37.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/F0EFD34A-FB31-E111-BB44-BCAEC54B3067.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/96024EC7-F631-E111-8637-20CF3027A60F.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4C7A6A1C-FD31-E111-91EC-E0CB4E55364D.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/4C9C21E5-0032-E111-89F0-001EC9D7DF62.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/5E20D036-ED31-E111-B82A-20CF3027A577.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/60AC69B6-2232-E111-8850-001EC9D825A9.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/98FFE4D6-2D32-E111-95FB-90E6BA0D0987.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/AE16F260-0F32-E111-AE10-20CF305B0521.root',
       '/store/mc/Fall11/Tbar_TuneZ2_scaledown_s-channel_7TeV-powheg-tauola/AODSIM/PU_S6_START42_V14B-v1/0000/340062A4-1432-E111-83D0-E0CB4E19F981.root' ] );


secFiles.extend( [
               ] )

