import FWCore.ParameterSet.Config as cms

############################################################################################################################################
#                                                                     
#          global tag: GR_R_38X_V13::All
#
#        dataset name: /Mu/dammann-Run2010B2-Nov4ReReco-PAT-v2-924c534d4f173e041134b0a34d9fb0e5/USER 
#             DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
# 
#       input sample: /Mu/Run2010A-Nov4ReReco_v1/AOD
#
#           json file: Cert_136033-149442_7TeV_Nov4ReReco_Collisions10_JSON.txt 
#															     
#  integrated HF lumi: 27.907588871                                                                                     
#
#    number of events: 5498448
#
#        preselection: (HLT_Mu9 OR HLT_Mu11 OR HLT_Mu15) AND  (beam scrap and HCAL noise cuts, PV)
#
#            cut flow:  
#		   before:	trigger:	Beam Scrap:	HCAL Noise:	PV:	
#  HLT_Mu9  path: 20387348	 884958		 884955		 884378		 883985
#  HLT_Mu11 path: 20387348 	3217005		3216995		3214537		3212610
#  HLT_Mu15 path: 20387348 	2792576		2792548		2789600		2786855
#                                                  
############################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_9_1_LjM.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_99_2_3tQ.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_98_1_T55.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_97_1_6LK.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_96_1_QPF.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_95_1_ZuK.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_94_1_Z0Z.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_93_1_rqo.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_92_1_FBr.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_91_1_LAd.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_90_2_Ty8.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_8_1_HIT.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_89_2_ANe.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_88_2_Js2.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_87_2_WBB.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_86_2_28j.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_85_1_o9x.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_84_1_L1U.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_83_1_3ud.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_82_1_PZV.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_81_1_UEP.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_80_1_UJq.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_7_1_Eil.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_79_1_QZC.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_78_1_Llr.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_77_1_Keg.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_76_1_Jms.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_75_2_tmd.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_74_1_buf.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_73_1_hEJ.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_72_3_H4r.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_71_2_XHM.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_70_2_PL0.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_6_1_TDC.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_69_2_XQF.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_68_1_xCE.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_67_2_D36.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_66_1_pA1.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_65_2_wo7.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_64_2_KUt.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_63_3_pee.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_62_1_nQ7.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_61_2_yEn.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_60_1_GLU.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_5_2_Iiq.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_59_1_7Gx.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_58_2_vQR.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_57_1_FN8.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_56_1_iKd.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_55_1_Ppm.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_54_1_Lwg.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_53_3_INV.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_52_1_NAB.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_51_1_Z4A.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_50_2_UXH.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_4_1_2Zv.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_49_2_IAi.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_48_2_PzC.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_47_1_kCS.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_46_1_5yR.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_45_2_Hdn.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_44_2_MuB.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_43_1_TLe.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_42_2_XtG.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_41_1_fqY.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_40_1_sbh.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_3_1_GxN.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_39_1_Xjy.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_38_1_Gph.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_37_2_Fsr.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_36_1_chS.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_35_1_5ZB.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_34_1_p3W.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_33_3_Q5W.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_32_1_smf.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_31_1_a3i.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_30_2_J5j.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_2_2_SGR.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_29_2_Ub7.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_28_1_2Gm.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_27_2_aLS.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_26_1_Ogf.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_25_1_S8F.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_24_2_Jyj.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_23_2_Pur.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_22_1_qiG.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_21_1_hxB.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_20_1_ZcT.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_1_1_3rP.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_19_1_tcL.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_18_1_86x.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_17_1_kvW.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_16_1_mTN.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_15_1_qNK.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_14_2_Msb.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_13_2_MU5.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_12_1_oSA.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_122_1_g2t.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_121_2_fmL.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_120_2_6uy.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_11_1_DDJ.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_119_1_BOL.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_118_1_f3E.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_117_1_iTE.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_116_1_uRY.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_115_2_t5Y.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_114_2_qmB.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_113_1_PyP.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_112_1_7B9.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_111_1_8mi.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_110_2_SZe.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_10_1_gWL.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_109_2_oKb.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_108_1_fE9.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_107_1_SKD.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_106_1_Al6.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_105_1_o86.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_104_2_XVk.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_103_1_aaN.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_102_1_Xdr.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_101_1_W6O.root',
       '/store/user/dammann/Mu/Run2010B2-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_100_1_SFa.root' ] );


secFiles.extend( [
               ] )

