import FWCore.ParameterSet.Config as cms

############################################################################################################################################
#                                                                     
#  Contains the Data of the Run2010A-Sep17ReReco_v2
#
#          global tag: GR_R_38X_V13::All
#
#        dataset name: /Mu/dammann-Run2010A-Sep17ReReco-HLT-Oct22-PAT-f626a178648aa5f18ef772d7da585a78/USER 
#             DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
# 
#       input sample: /Mu/Run2010A-Sep17ReReco_v2/RECO
#
#           json file: Cert_132440-148058_7TeV_StreamExpress_Collisions10_JSON.txt
#															     
#  integrated HF lumi: 3.068636598                                                                                        
#
#    number of events: 1750284
#
#        preselection: HLT_Mu9 AND  (beam scrap and HCAL noise cuts, PV)
#
#            cut flow:  
#		   before:	trigger:	Beam Scrap:	HCAL Noise:	PV:	
#
#  HLT_Mu9  path: 18560889	1752768		1752767		1751574		1750284			
#                                                  
############################################################################################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(   
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_100_1_EUr.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_101_1_pVU.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_102_1_X8d.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_103_1_c72.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_104_1_lJr.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_105_1_Q9l.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_106_1_OD2.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_107_1_keP.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_108_1_DYk.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_109_1_Et6.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_10_1_ZtX.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_110_1_mqy.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_11_1_aaN.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_12_1_A8T.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_13_1_qXM.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_14_1_MR8.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_15_1_8Qc.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_16_1_Eek.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_17_1_I64.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_18_1_mxU.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_19_1_SRP.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_1_1_BjI.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_20_1_Apx.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_21_1_Y9b.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_22_1_XYI.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_23_1_dhp.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_24_1_Imz.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_25_1_tLm.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_26_1_DbK.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_27_1_FlI.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_28_1_qPU.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_29_1_6f5.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_2_1_wOB.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_30_1_MQn.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_31_1_jpS.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_32_1_xXJ.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_33_1_FCP.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_34_1_muS.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_35_1_AhV.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_36_1_YuH.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_37_1_Zbi.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_38_1_6Ua.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_39_1_Og6.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_3_1_Klz.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_40_1_poR.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_41_1_gt5.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_42_1_125.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_43_1_S8c.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_44_1_WtQ.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_45_1_idF.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_46_1_Khb.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_47_1_NDY.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_48_1_abG.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_49_1_V1H.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_4_1_Xhe.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_50_1_CRv.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_51_1_jzs.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_52_1_klF.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_53_1_ndH.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_54_1_sCf.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_55_1_Sqr.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_56_1_Z1G.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_57_1_en4.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_58_1_XFS.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_59_1_ig8.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_5_1_i8z.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_60_1_vMp.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_61_1_6ut.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_62_1_TMg.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_63_1_907.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_64_1_zZP.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_65_1_lTx.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_66_1_tCJ.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_67_1_Mbe.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_68_1_FAA.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_69_1_ZL2.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_6_1_BoQ.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_70_1_xEU.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_71_1_k73.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_72_1_8Ar.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_73_1_JbT.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_74_1_Wgd.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_75_1_TJZ.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_76_1_Rk3.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_77_1_iqz.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_78_1_oZm.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_79_1_jqO.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_7_1_dST.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_80_1_pZJ.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_81_1_TKZ.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_82_1_dca.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_83_1_31j.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_84_1_JgX.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_85_1_GXU.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_86_1_GdB.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_87_1_Dmt.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_88_1_IGS.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_89_1_Cn3.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_8_1_XDW.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_90_1_JbK.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_91_1_BhM.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_92_1_kf0.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_93_1_7R7.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_94_1_bsf.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_95_1_lLk.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_96_1_AWc.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_97_1_cNK.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_98_1_YUM.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_99_1_ssI.root',
	'/store/user/dammann/Mu/Run2010A-Sep17ReReco-HLT-Oct22-PAT/f626a178648aa5f18ef772d7da585a78/Run2010A_Sep17ReReco_v2_HLT_9_1_vy4.root'	   
       )
)
