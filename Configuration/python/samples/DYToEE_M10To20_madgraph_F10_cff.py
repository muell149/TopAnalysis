####################################################################################################################################
#  
#          dataset name: /DYToEE_M-10To20_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-adc6a4a08f017ca447d42e2ca3c502e8/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM
#      number of events: 1933000
#         cross section: 3457
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_9_1_PbU.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_97_2_vMC.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_96_1_hTt.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_95_1_AN6.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_94_1_R6i.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_93_1_wVV.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_92_1_EjB.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_91_1_DKG.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_90_1_JGO.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_8_1_dsU.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_89_1_mYj.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_88_1_XWn.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_87_1_Q1s.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_86_1_Qcv.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_85_1_JqK.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_84_1_pOz.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_83_1_vZ6.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_82_1_3w5.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_81_1_zuX.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_80_1_CM8.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_7_1_rVo.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_79_1_k93.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_78_1_u7K.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_77_1_4Q3.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_76_1_yz3.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_75_1_39P.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_74_1_DKe.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_73_1_DHP.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_72_1_Loe.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_71_1_gG2.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_70_1_HYv.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_6_1_Mgv.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_69_1_BEF.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_68_1_t7t.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_67_1_i3l.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_66_1_v7D.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_65_1_hXo.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_64_1_Slp.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_63_1_FgO.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_62_1_2MP.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_61_1_jrg.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_60_1_SVf.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_5_1_I9W.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_59_1_O3m.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_58_1_WBs.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_57_1_SrK.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_56_1_xey.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_55_1_RGS.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_54_1_Knc.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_53_1_r2T.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_52_1_sP4.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_51_1_MMR.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_50_1_v3N.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_4_1_3m8.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_49_1_pmz.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_48_1_2Yi.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_47_1_RN4.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_46_1_wad.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_45_1_gJS.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_44_1_Dhi.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_43_1_GTV.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_42_1_5y2.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_41_1_0kB.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_40_1_Mrp.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_3_1_QRe.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_39_1_FOz.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_38_1_pex.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_37_1_FO9.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_36_1_fHh.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_35_1_E4e.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_34_1_Im2.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_33_1_Lgb.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_32_1_Sws.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_31_1_Wcf.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_30_1_eb9.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_2_1_Des.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_29_1_ckp.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_28_1_HSw.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_27_1_RzT.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_26_1_Za0.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_25_1_CGX.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_24_1_Ve8.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_23_1_zxI.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_22_1_VRg.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_21_1_fVp.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_20_1_UHQ.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_1_1_x5B.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_19_1_x7S.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_18_1_5oX.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_17_1_7tb.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_16_1_1Px.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_15_1_oFc.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_14_1_WfW.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_13_1_Ibt.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_12_1_tB6.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_11_1_IiG.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_10_1_xCx.root' ] );


secFiles.extend( [
               ] )

