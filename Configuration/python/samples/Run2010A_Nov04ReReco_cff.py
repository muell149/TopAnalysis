import FWCore.ParameterSet.Config as cms

############################################################################################################################################
#                                                                     
#          global tag: GR_R_38X_V13::All
#
#        dataset name:/Mu/dammann-Run2010A-Nov4ReReco-PAT-v2-924c534d4f173e041134b0a34d9fb0e5/USER 
#             DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
# 
#       input sample: /Mu/Run2010A-Nov4ReReco_v1/AOD
#
#           json file: Cert_136033-149442_7TeV_Nov4ReReco_Collisions10_JSON.txt
#															     
#  integrated HF lumi: 3.180532050                                                                                        
#
#    number of events: 1813852
#
#        preselection: HLT_Mu9 AND  (beam scrap and HCAL noise cuts, PV)
#
#            cut flow:  
#		   before:	trigger:	Beam Scrap:	HCAL Noise:	PV:	
#  HLT_Mu9  path: 20868538	1816452		1816451		1815221		1813852	
#                                                  
############################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_9_1_6QA.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_99_1_7tR.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_98_1_jgp.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_97_1_jj7.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_96_1_VQD.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_95_1_nZN.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_94_1_sdd.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_93_1_bPo.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_92_1_Hbm.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_91_1_JJS.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_90_1_18k.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_8_1_VFd.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_89_1_PhF.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_88_1_k1x.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_87_1_7We.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_86_1_YHI.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_85_1_qGE.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_84_1_jqx.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_83_1_MY8.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_82_1_RgD.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_81_1_Q5i.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_80_1_PDv.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_7_1_E4s.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_79_1_Yv4.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_78_1_SWa.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_77_1_dfL.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_76_2_J00.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_75_1_IVP.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_74_1_mky.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_73_1_KvQ.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_72_1_dB8.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_71_1_IRQ.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_70_1_sx0.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_6_1_TNt.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_69_1_UgM.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_68_1_zQs.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_67_1_iJl.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_66_1_55R.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_65_1_Fmu.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_64_1_ZXZ.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_63_1_IPT.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_62_1_RzZ.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_61_1_Kup.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_60_1_HNu.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_5_1_fOW.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_59_1_e35.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_58_1_i5J.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_57_1_kJU.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_56_1_rMF.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_55_1_Q6O.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_54_1_FjN.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_53_1_Xmj.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_52_1_dmD.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_51_1_yZm.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_50_1_7uS.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_4_1_8XS.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_49_1_IDD.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_48_1_51o.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_47_1_HUx.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_46_1_Clf.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_45_1_A94.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_44_1_hTD.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_43_1_id3.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_42_1_PXh.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_41_1_kOq.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_40_1_WjG.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_3_1_Fi3.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_39_1_2sS.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_38_1_uSP.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_37_1_Bxx.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_36_1_8rT.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_35_3_Lwc.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_34_1_B0S.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_33_2_1aU.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_32_1_oeY.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_31_1_MkK.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_30_1_eKV.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_2_1_GY1.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_29_2_JB1.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_28_2_YV8.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_27_1_RtV.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_26_2_eAx.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_25_2_L53.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_24_1_XTu.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_23_1_xUZ.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_22_1_b2q.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_21_2_qyc.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_20_2_LKC.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_1_1_xD9.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_19_1_JQM.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_18_1_5XY.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_17_1_6k1.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_16_1_UGf.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_15_2_f1B.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_156_1_zd6.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_155_2_JBI.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_154_2_ERj.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_153_2_i0E.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_152_2_w5o.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_151_1_YOt.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_150_1_slA.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_14_2_gdJ.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_149_1_Zp4.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_148_1_Csa.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_147_1_i5D.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_146_1_885.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_145_2_wqM.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_144_2_ydC.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_143_2_qDk.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_142_1_QLd.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_141_2_fxE.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_140_2_7HQ.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_13_1_1BW.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_139_2_4wY.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_138_1_uKo.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_137_1_ht5.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_136_1_QGa.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_135_2_L3C.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_134_1_bCS.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_133_1_tta.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_132_1_s4g.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_131_1_T8v.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_130_1_F4A.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_12_1_PP1.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_129_1_CYZ.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_128_1_HPb.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_127_2_kR4.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_126_2_6Tg.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_125_1_MgV.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_124_1_nAb.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_123_1_Ks6.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_122_1_Xor.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_121_1_esa.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_120_2_QEi.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_11_1_JRt.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_119_2_jyC.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_118_1_r97.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_117_1_vdg.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_116_1_h7G.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_115_1_1Id.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_114_1_1hS.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_113_1_C60.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_112_1_upe.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_111_1_pJp.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_110_1_FLY.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_10_2_Egk.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_109_1_sVm.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_108_1_l0s.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_107_1_7Pi.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_106_1_TUq.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_105_1_B31.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_104_1_01X.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_103_1_Sxm.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_102_1_b2n.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_101_1_cBA.root',
       '/store/user/dammann/Mu/Run2010A-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_100_1_7eM.root' ] );


secFiles.extend( [
               ] )

