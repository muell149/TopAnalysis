import FWCore.ParameterSet.Config as cms

############################################################################################################################################
#                                                                     
#  Contains the Data of the Run2010B-PromptReco_v2 from run 145000 to 147120
#
#          global tag: GR_R_38X_V13::All
#
#        dataset name: /Mu/dammann-Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120-162fe77b59856584f7ae857555e29ea0/USER
#             DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
# 
#       input sample: /Mu/Run2010B-PromptReco_v2/AOD
#
#           json file: subset of Cert_132440-148864_7TeV_StreamExpress_Collisions10_JSON.txt
#															     
#  integrated HF lumi: 4.390660197/pb                                                                                     
#
#    number of events: 2708107
#
#        preselection: ( HLT_Mu9  OR  HLT_Mu 11 )  AND  (beam scrap and HCAL noise cuts, PV)
#
#            cut flow:  
#		   before:	trigger:	Beam Scrap:	HCAL Noise:	PV:	
#
#  HLT_Mu9  path: 6745979	2712218		2712207		2709774		2708107
#  HLT_Mu11 path: 6745979	1324395		1324389		1322846		1321816
#                       
############################################################################################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(  
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_100_1_bnx.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_101_1_3Z4.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_102_1_vRb.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_103_1_K0M.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_104_1_oxh.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_105_1_aOy.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_106_1_YSt.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_107_1_Wuv.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_108_1_pPk.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_109_1_L8z.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_10_1_kA8.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_110_1_9Q2.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_111_1_KnF.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_112_1_83u.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_113_1_l3q.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_114_1_X3c.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_115_1_PLK.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_116_1_pmG.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_117_1_5rd.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_118_1_Fmm.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_119_1_61u.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_11_1_O0J.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_12_1_2uk.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_13_1_jL2.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_14_1_PXr.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_15_1_8sc.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_16_1_76k.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_17_1_MYv.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_18_1_mus.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_19_1_8qt.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_1_1_gCG.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_20_1_6tj.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_21_1_UeB.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_22_1_80A.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_23_1_PnH.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_24_1_gyt.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_25_1_yof.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_26_1_xDb.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_27_1_3Ju.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_28_1_vlS.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_29_1_jfJ.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_2_1_xvW.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_30_1_G1u.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_31_1_TUq.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_32_1_voj.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_33_1_ikN.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_34_1_2TJ.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_35_1_RMv.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_36_1_9Ky.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_37_1_9Ed.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_38_1_TFC.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_39_1_hyh.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_3_1_5ee.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_40_1_1qw.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_41_1_w1Y.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_42_1_yz3.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_43_1_1nR.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_44_1_oYy.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_45_1_jIS.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_46_1_loS.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_47_1_2Cb.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_48_1_7W0.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_49_1_YUK.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_4_1_l9P.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_50_1_TrD.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_51_1_KGs.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_52_1_GwA.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_53_1_VLZ.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_54_1_hBS.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_55_1_8jO.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_56_1_8AY.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_57_1_1pv.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_58_1_zpn.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_59_1_jaU.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_5_1_BH6.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_60_1_QkA.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_61_1_Djo.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_62_1_OUE.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_63_1_odN.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_64_1_Hcb.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_65_1_j3e.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_66_1_DX7.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_67_1_xm6.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_68_1_exM.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_69_1_sUR.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_6_1_wMZ.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_70_1_Pwr.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_71_1_GtJ.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_72_1_lJy.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_73_1_EJl.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_74_1_Yd4.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_75_1_G2k.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_76_1_yGk.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_77_1_Kor.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_78_1_Ii6.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_79_1_sqG.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_7_1_n1F.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_80_1_Yxt.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_81_1_T5u.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_82_1_sEb.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_83_1_ouv.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_84_1_g9S.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_85_1_654.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_86_1_6em.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_87_1_Aan.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_88_1_ylg.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_89_1_Lka.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_8_1_Ukg.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_90_1_BLd.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_91_1_C7I.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_92_1_jgZ.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_93_1_UFv.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_94_1_66X.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_95_1_49r.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_96_1_YKC.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_97_1_NPs.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_98_1_u4P.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_99_1_47y.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-HLT-Oct29-PAT-145000-147120/162fe77b59856584f7ae857555e29ea0/Run2010B_PromptReco_v2_HLT_9_1_HHo.root'
    )
)
