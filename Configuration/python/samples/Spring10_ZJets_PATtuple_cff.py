import FWCore.ParameterSet.Config as cms

########################################################################################### 
#
#  Contains PATtuples from Spring 10 MC: ZJets
#  
#  SPECIAL: Reco::muons were matched with genMuons from a Z
#           using TopAnalysis.TopUtils.GenCandSelector_cfi 
# 
#  input samples: /ZJets-madgraph/Spring10-START3X_V26_S09-v1/AODSIM
#
# 
#    number of events: 1084921
#
#
############################################################################################

readFiles = cms.untracked.vstring()

source = cms.Source("PoolSource",
                     fileNames= readFiles
                   )

readFiles.extend( [        	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_1_1_4aO.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_2_3_mQa.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_3_3_xIo.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_4_2_9i9.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_5_1_Z6N.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_6_3_kNA.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_7_3_NG4.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_8_1_74N.root',
	'/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_9_3_PU8.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_10_1_sBG.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_11_1_5sk.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_12_3_p1n.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_13_2_iTs.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_15_1_n5X.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_16_1_XRH.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_17_1_xAD.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_18_3_ZId.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_19_3_j40.root',
	'/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_20_2_USK.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_21_3_7tA.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_22_2_3VQ.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_23_1_BO3.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_24_1_0WO.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_25_2_u32.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_26_2_SxC.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_27_3_Y5l.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_28_3_1sB.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_29_1_jhK.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_30_1_4h8.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_31_3_8he.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_32_1_lfV.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_33_2_y79.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_34_1_MCD.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_35_3_LAG.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_36_1_ziU.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_37_1_rVL.root',
	'/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_38_1_BMO.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_39_3_wdu.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_40_1_fIv.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_41_3_By6.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_42_2_FYg.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_43_1_Wuy.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_44_2_AIx.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_45_1_aVl.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_46_3_EMK.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_47_2_b7T.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_48_2_SGa.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_49_2_F9c.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_50_3_W1T.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_51_1_jO6.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_52_2_a2c.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_53_2_PWl.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_54_1_UXE.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_55_1_X9W.root',
	'/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_56_2_ZjK.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_57_1_DHK.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_58_1_rDj.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_59_1_N8t.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_60_1_JU2.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_61_3_hXv.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_62_2_Qtm.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_63_2_Muz.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_64_3_YI5.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_65_1_Krh.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_66_3_bZA.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_68_3_nkG.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_69_1_zGO.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_70_3_nSE.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_71_1_6Hi.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_72_3_ANA.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_73_1_ys1.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_74_3_Sdo.root',
	'/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_75_1_maU.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_76_2_U8L.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_77_1_5zO.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_78_1_KLB.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_79_3_EEM.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_80_1_iPs.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_81_3_nhv.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_82_3_glE.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_83_2_WAq.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_84_3_JaW.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_85_3_7OF.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_86_2_GDG.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_87_3_7J5.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_88_2_nKG.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_89_1_uKw.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_90_2_6EJ.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_91_1_TJr.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_92_2_x20.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_93_2_HY2.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_94_1_1Of.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_95_2_Laz.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_96_3_a1F.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_97_2_SHE.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_98_3_YnT.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_99_2_7OQ.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_100_1_Cl7.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_101_2_MPP.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_102_1_t1o.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_103_1_P4T.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_104_1_62s.root',
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_105_3_NQW.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_106_2_zqu.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_107_1_gXz.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_108_2_SuF.root',	
        '/store/user/jlange/samples/Spring10/ZJets-madgraph2/PATtuple_109_3_PbN.root'
	] );


















