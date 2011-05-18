import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
  ## 20 files; 5.1 /pb, JSON May13
  '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_9_1_lEI.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_8_1_f8d.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_7_1_Xut.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_6_1_aud.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_5_1_OIK.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_4_1_wsi.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_3_1_lUQ.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_2_1_zRT.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_20_1_1zy.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_1_1_6Se.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_19_1_f6z.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_18_1_p3e.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_17_1_M3O.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_16_1_BQz.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_15_1_q0l.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_14_1_zWu.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_13_1_LEo.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_12_1_xxl.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_11_1_10q.root',
        '/store/user/jlange/MuHad/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_10_1_4FE.root'

      ] );


secFiles.extend( [
               ] )
