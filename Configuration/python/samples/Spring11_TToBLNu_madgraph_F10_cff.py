import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_9_1_QIk.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_8_1_TVZ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_7_1_Bp2.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_6_1_SnF.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_5_1_m6l.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_4_1_Ovq.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_49_1_FEm.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_48_1_sCp.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_47_1_vZv.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_46_1_D0o.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_45_1_OK9.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_44_1_XwA.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_43_1_Yzg.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_42_1_SbL.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_41_1_dvZ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_40_1_NzN.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_3_1_aZD.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_39_1_5zc.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_38_1_xUU.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_37_1_s8H.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_36_1_WtT.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_35_1_20H.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_34_1_rQ1.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_33_2_w28.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_32_1_EV8.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_31_1_eUY.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_30_1_aG8.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_2_1_hxh.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_29_1_3Cx.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_28_1_yYF.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_27_1_WYj.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_26_1_qlw.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_25_1_FgY.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_24_1_gaH.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_23_1_J8n.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_22_1_EAw.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_21_1_Te8.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_20_1_inT.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_1_1_oBw.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_19_1_O9i.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_18_1_NrR.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_17_1_6aB.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_16_1_BhD.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_15_1_LM2.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_14_1_60A.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_13_1_FFV.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_12_1_yNp.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_11_1_9Qt.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Summer11-PAT-v1g1/6e6559812e09b52af172f27db20ae337/mc2pat_10_1_495.root' ] );


secFiles.extend( [
               ] )

