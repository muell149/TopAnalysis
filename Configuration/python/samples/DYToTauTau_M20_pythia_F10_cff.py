####################################################################################################################################
#  
#          dataset name: /DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/dammann-Fall10-PAT-adc6a4a08f017ca447d42e2ca3c502e8/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /DYToTauTau_M-20_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM 
#      number of events: 2037446
#         cross section: 1666 
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_9_1_ETo.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_99_1_0NT.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_98_1_Gu5.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_97_1_cjc.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_96_3_aYC.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_95_1_Nqn.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_94_1_Aik.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_93_1_tUT.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_92_1_M2L.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_91_1_sNl.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_90_1_YUB.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_8_1_DiB.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_89_1_FV0.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_87_1_O1L.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_86_1_fyd.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_85_2_1wL.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_84_1_DEi.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_83_1_q73.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_82_1_GxD.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_81_1_CtI.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_80_3_yuq.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_7_1_po6.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_79_1_IL2.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_78_1_tP0.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_77_1_gDr.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_76_1_Chn.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_75_1_cNp.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_74_1_RRx.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_73_1_axk.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_72_1_cqk.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_71_1_brO.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_70_1_j5d.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_6_1_LUr.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_69_1_I80.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_68_1_7ZK.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_67_3_Js1.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_66_1_VaN.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_65_3_BBH.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_64_1_eGR.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_63_1_rit.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_62_1_AAL.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_61_2_DM1.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_60_1_6Nt.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_5_1_tqa.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_59_1_gkZ.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_58_1_nTN.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_57_1_JIi.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_56_1_2y1.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_55_2_hD3.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_54_1_a5D.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_53_2_FX9.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_52_1_6ry.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_51_1_r4X.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_50_3_Kx5.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_4_1_MyY.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_49_2_XE1.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_48_1_UFr.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_47_2_quj.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_46_1_UJW.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_45_2_gRK.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_44_1_kBd.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_43_2_Sun.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_42_1_t1U.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_41_1_Zag.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_40_1_IxR.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_3_2_mfu.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_39_1_buv.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_38_1_N2Y.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_37_1_d1o.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_36_4_Yf8.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_35_1_pmd.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_34_1_vJR.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_33_1_zlz.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_32_1_mBu.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_31_1_hvq.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_30_1_D1o.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_2_2_kTL.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_29_1_SYX.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_28_1_QSL.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_27_1_C4i.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_26_1_t7E.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_25_1_9j9.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_24_1_i4C.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_23_1_a9S.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_22_1_Atf.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_21_1_44u.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_20_1_RqW.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_1_1_EzE.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_19_1_pGX.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_18_1_2i0.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_17_1_JhC.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_16_1_6LA.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_15_1_r9q.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_14_2_S1G.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_13_1_8oq.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_12_3_2i5.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_11_1_EnX.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_10_1_yG1.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_103_1_DBH.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_102_1_SXG.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_101_1_3aw.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_100_1_U9L.root' ] );


secFiles.extend( [
               ] )

