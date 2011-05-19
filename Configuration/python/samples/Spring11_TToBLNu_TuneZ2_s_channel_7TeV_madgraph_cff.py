import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_9_1_Wwq.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_8_1_ICa.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_7_1_Kiq.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_6_1_cL4.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_5_1_vY0.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_50_1_r5y.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_4_1_Gnr.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_49_1_GvF.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_48_1_6Lg.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_47_1_Zdf.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_46_1_6jg.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_45_1_2ja.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_44_1_jwp.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_43_1_RYI.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_42_1_h4s.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_41_1_02b.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_40_1_Kd7.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_3_1_n3j.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_39_1_PIX.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_38_1_AJJ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_37_1_tsZ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_36_1_LSG.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_35_1_4dQ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_34_1_Yvz.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_33_1_sZL.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_32_1_V8d.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_31_1_U2w.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_30_1_H8c.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_2_1_TO5.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_29_1_B03.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_28_1_IkH.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_27_1_neE.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_26_1_yFD.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_25_1_kk1.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_24_1_qwD.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_23_1_SyI.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_22_1_dC4.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_21_1_uUa.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_20_1_vel.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_1_1_2RD.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_19_1_e8P.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_18_1_Wci.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_17_1_UPL.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_16_1_DkL.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_15_1_2wk.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_14_1_Co8.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_13_1_3Gl.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_12_1_8Q1.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_11_1_ClC.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_s-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_10_1_DPr.root' ] );


secFiles.extend( [
               ] )

