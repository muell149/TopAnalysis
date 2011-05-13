import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_9_1_kQs.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_8_1_w7D.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_7_1_FXJ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_6_1_wmZ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_5_1_IWZ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_4_1_D1g.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_49_1_QAi.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_48_1_Ww5.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_47_1_1cp.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_46_1_RcL.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_45_1_pcK.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_44_1_qIW.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_43_1_err.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_42_1_h6g.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_41_1_hII.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_40_1_izN.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_3_1_VHp.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_39_1_VRm.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_38_1_Ysb.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_37_1_7h7.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_36_1_VDV.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_35_1_Ui2.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_34_1_sbM.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_33_1_xM2.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_32_1_Rb3.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_31_1_gJ6.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_30_1_xcR.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_2_1_HQs.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_29_1_AHU.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_28_1_YDI.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_27_1_pRs.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_26_1_iJ9.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_25_1_SXy.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_24_1_bbM.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_23_1_U9c.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_22_1_oBm.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_21_1_dMA.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_20_1_1R5.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_1_1_yMY.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_19_1_hvi.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_18_1_IKh.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_17_1_2qP.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_16_1_Npw.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_15_1_VBY.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_14_1_XvH.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_13_1_UC7.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_12_1_81d.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_11_1_7fg.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_10_1_IJD.root' ] );


secFiles.extend( [
               ] )

