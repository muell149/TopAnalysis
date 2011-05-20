import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
  ## 31 files; 5.07 /pb, JSON May13
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_9_1_4k7.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_8_2_2Vc.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_7_2_VMU.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_6_1_lNE.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_5_1_IMs.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_4_1_BsS.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_3_1_ml7.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_31_1_tDM.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_30_2_z0W.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_2_1_Fup.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_29_1_E1J.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_28_1_HsV.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_27_2_tWY.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_26_1_fFQ.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_25_1_7V2.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_24_2_6L6.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_23_1_GdS.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_22_2_uMk.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_21_1_AlQ.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_20_1_kwq.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_1_1_uwm.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_19_1_9Zz.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_18_1_YEx.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_17_1_K5g.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_16_1_b2k.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_15_1_VKp.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_14_1_Ggp.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_13_1_XDU.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_12_1_Q8V.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_11_1_SwB.root',
        '/store/user/jlange/SingleMu/PAT_Data2011_PromptReco_UHH/3db61b3449ae3442edf2fbc560a5ed3b/Data2011_PromptReco_10_1_E7x.root'
 


      ] );


secFiles.extend( [
               ] )
