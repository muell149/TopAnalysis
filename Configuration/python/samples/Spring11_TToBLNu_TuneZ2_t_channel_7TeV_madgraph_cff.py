import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_9_1_32v.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_8_1_ct5.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_7_1_gNo.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_6_1_iCJ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_5_1_NGp.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_4_1_8OT.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_49_1_dXV.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_48_1_nnN.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_47_1_W9Q.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_46_1_IJy.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_45_1_7qI.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_44_1_X9S.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_43_1_Tnt.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_42_1_ESE.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_41_1_kg3.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_40_1_Typ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_3_1_zzS.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_39_1_qz1.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_38_1_rUi.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_37_1_KMW.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_36_1_xp0.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_35_1_1LA.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_34_1_cRG.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_33_1_exW.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_32_1_UrJ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_31_1_Dvb.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_30_1_BoS.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_2_1_eAi.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_29_1_j51.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_28_1_IRJ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_27_1_5AO.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_26_1_82M.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_25_1_dgi.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_24_1_g3V.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_23_1_Grt.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_22_1_NXz.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_21_1_iRa.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_20_1_a2x.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_1_1_lmJ.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_19_1_ZEN.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_18_1_znn.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_17_1_yXw.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_16_1_QQz.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_15_1_66m.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_14_1_6R7.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_13_1_I1p.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_12_1_N5n.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_11_1_3EW.root',
       '/store/user/wbehrenh/TToBLNu_TuneZ2_t-channel_7TeV-madgraph/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_10_1_1xd.root' ] );


secFiles.extend( [
               ] )

