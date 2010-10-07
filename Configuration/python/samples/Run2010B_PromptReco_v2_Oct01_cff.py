import FWCore.ParameterSet.Config as cms

############################################################################################################################################
#                                                                     
#  Contains the Data of the Run2010B-PromptReco_v2 certified till October 1st 2010
#  (+ Jul16thReReco)    
#
#          global tag: GR_R_38X_V13::All
#
#        dataset name: /Mu/dammann-Run2010B-PromptReco-Oct01-Trigger-PAT-f02e17f8210087bf691d3427b81ee1bd/USER
#             DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
# 
#       input sample: /Mu/Run2010B-PromptReco_v2/AOD
#
#           json file: Cert_132440-146729_7TeV_StreamExpress_Collisions10_JSON.txt
#															     
#  integrated HF lumi: 1.005746585/pb                                                                                                                 
#
#    number of events: 828593
#
#        preselection: ( HLT_Mu9  OR  HLT_Mu15 )  AND  (PV, beam scrap and HCAL noise cuts)
#
#            cut flow:  
#		   before:	trigger:	PV:		Beam Scrap:	HCAL Noise:	
#
#  HLT_Mu9  path:  2192691	829865		829203		829203		828593	
#  HLT_Mu11 path:  2192691	405291		404877		404877		404494
#  HLT_Mu15 path:  2192691	     0		     0		     0		     0
#                                                  
############################################################################################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(   
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_10_1_0o7.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_11_1_A0I.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_12_1_bgb.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_13_1_pwf.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_14_1_w78.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_15_1_vWL.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_16_1_zPh.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_17_1_bNj.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_18_1_1mt.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_19_1_WFB.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_1_1_WJq.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_20_1_pc3.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_21_1_hmv.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_22_1_klc.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_23_1_rXR.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_24_1_PZO.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_25_1_IFq.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_26_1_JCb.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_27_1_dJK.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_28_1_c8d.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_29_1_rzX.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_2_1_G8d.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_30_1_j82.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_31_1_8Dy.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_32_1_QGw.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_33_1_Ata.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_34_1_z0t.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_35_1_W7V.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_36_1_JmL.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_37_1_AUL.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_38_1_fDQ.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_39_1_GB7.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_3_1_34f.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_40_1_TJ7.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_41_1_vks.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_42_1_tJH.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_43_1_qTM.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_44_1_jgr.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_45_1_HwO.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_46_1_It8.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_47_1_JSq.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_48_1_nLW.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_49_1_YP1.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_4_1_7Ul.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_50_1_obH.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_51_1_PY8.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_52_1_Nv7.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_53_1_zuq.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_54_1_7kr.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_55_1_VtE.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_56_1_8y8.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_57_1_sk8.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_58_1_1xA.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_59_1_ZZG.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_5_1_vuk.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_60_1_Vhg.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_61_1_876.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_6_1_RKr.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_7_1_29t.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_8_1_Gcw.root',
	'/store/user/dammann/Mu/Run2010B-PromptReco-Oct01-Trigger-PAT/f02e17f8210087bf691d3427b81ee1bd/Run2010B_PromptReco_v2_Oct01_9_1_zjz.root'				
       )
)
