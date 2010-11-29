####################################################################################################################################
#  
#          dataset name: /WToENu_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /WToENu_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM
#      number of events: 5104514
#         cross section: 10438 
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_zwA.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_99_1_A9y.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_98_1_N5x.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_97_1_4hC.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_96_1_8oJ.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_95_1_Kbp.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_94_1_GFt.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_93_1_nO6.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_92_1_xQO.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_91_1_KX3.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_90_1_AHc.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_XP9.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_89_1_GCq.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_88_1_qCf.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_87_1_PR4.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_86_1_Mzl.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_85_1_HkU.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_84_1_RYb.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_83_1_DGN.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_82_1_1Sw.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_81_1_E1T.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_80_1_U6W.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_9ow.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_79_1_89t.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_78_1_kG3.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_77_1_4ML.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_76_1_ndK.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_75_1_alg.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_74_1_5jy.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_73_1_mKL.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_72_1_WTI.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_71_1_33Y.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_70_1_6uR.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_1_e9i.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_69_1_C38.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_68_1_1KL.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_67_1_8YQ.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_66_1_d1F.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_65_1_bpX.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_64_1_qFA.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_63_1_7wZ.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_62_1_q4p.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_61_1_iyd.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_60_1_B00.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_285.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_59_1_KoY.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_58_1_yTg.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_57_1_iPf.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_56_1_mb0.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_55_1_wf1.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_54_1_xNg.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_53_1_JMi.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_52_1_2sZ.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_51_1_PdH.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_50_2_R1E.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_sxq.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_49_1_8AP.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_48_1_Ip9.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_47_1_D4O.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_46_1_ep8.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_45_1_m8T.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_44_1_S0f.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_43_1_rmE.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_42_1_Udj.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_41_1_Bjj.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_40_1_8LX.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_ji5.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_39_1_tPD.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_38_1_uLN.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_37_1_6Gp.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_36_1_Nkm.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_35_1_9OP.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_34_1_uvs.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_33_1_yyH.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_32_1_gmi.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_31_1_7tt.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_30_1_hjU.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_1_ynL.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_29_1_jWj.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_28_1_Haz.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_1_XtC.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_1_I11.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_1_GLY.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_z1X.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_1_Q29.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_1_HaP.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_1_l49.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_1_xMH.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_Jt0.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_1_JWz.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_uB7.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_4fT.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_1_pK5.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_1_lOs.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_1_zim.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_YxU.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_xlj.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_pMv.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_kQ4.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_103_1_1fq.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_102_1_amE.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_101_1_uBr.root',
       '/store/user/dammann/WToENu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_100_1_51G.root' ] );


secFiles.extend( [
               ] )

