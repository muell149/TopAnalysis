####################################################################################################################################
#  
#          dataset name: /WToTauNu_TuneZ2_7TeV-pythia6-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-START38_V12-v1/GEN-SIM-RECO 
#      number of events: 5221750
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
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_2_7Uo.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_99_2_hvS.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_98_2_um0.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_97_1_sv9.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_96_6_zwk.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_95_1_m2x.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_94_2_e91.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_93_2_YNh.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_92_2_Q8I.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_91_2_Xoc.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_90_2_QO9.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_2_9SH.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_89_2_6sb.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_88_1_ynW.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_87_2_MLV.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_86_2_yYO.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_85_2_VR2.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_84_7_6bz.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_83_2_AuA.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_82_1_TrX.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_81_1_CqY.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_80_2_pOC.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_2_zMK.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_79_1_f0r.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_78_6_tm5.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_77_2_Gyf.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_76_2_poz.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_75_7_p8V.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_74_6_bES.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_73_2_akQ.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_72_2_RcM.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_71_2_JDQ.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_70_2_oBX.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_2_TeU.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_69_2_UzJ.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_68_1_vA2.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_67_6_GKm.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_66_2_N6m.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_65_1_1QG.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_64_2_eTD.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_63_1_3fH.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_62_2_rUz.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_61_2_3Vm.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_60_2_a3f.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_2_Vlx.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_59_1_B8z.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_58_1_MzG.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_57_2_Ibw.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_56_2_iAk.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_55_2_eLw.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_54_2_17U.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_53_6_sKx.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_52_2_bU0.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_51_2_omh.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_50_2_rwQ.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_2_J4D.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_49_1_4QM.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_48_2_gOo.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_47_2_dFW.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_46_1_FLq.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_45_2_Zsj.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_44_7_T5D.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_43_2_Lji.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_42_2_7XO.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_41_2_FPf.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_40_2_vVs.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_2_7uY.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_39_1_K6D.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_38_2_g0T.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_37_2_37i.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_36_2_TdK.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_35_2_SF4.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_34_1_iMH.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_33_1_0cJ.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_32_7_OSL.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_31_2_VH6.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_30_2_Qm9.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_6_eC1.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_29_1_8uT.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_28_2_wZs.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_1_3tz.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_6_DrW.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_1_rzk.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_2_i5s.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_1_OGp.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_2_rRQ.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_2_65v.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_2_CsG.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_2_96s.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_2_cdq.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_plB.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_2_x5m.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_1_UCY.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_2_Z1g.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_7_LYP.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_2_SUW.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_2_lQU.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_2_nto.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_2_qxQ.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_106_1_WIL.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_105_2_9rl.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_104_2_Lhi.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_103_2_mph.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_102_2_ApG.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_101_1_Vsr.root',
       '/store/user/dammann/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_100_2_PEU.root' ] );


secFiles.extend( [
               ] )

