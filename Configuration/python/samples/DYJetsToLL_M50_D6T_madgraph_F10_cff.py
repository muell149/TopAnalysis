####################################################################################################################################
#  
#          dataset name: /DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All 
#         mother sample: /DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/AODSIM
#      number of events: 2543383
#         cross section: 3048
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_qQT.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_2_fa3.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_LJ8.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_1_wPP.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_4kQ.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_56_1_4lM.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_55_1_5Ok.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_54_1_PDE.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_53_1_il4.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_52_2_YUz.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_51_2_vP1.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_50_2_511.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_Qoe.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_49_1_HCt.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_48_2_wCk.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_47_1_AwR.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_46_1_bB3.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_45_1_gp7.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_44_1_2OG.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_43_2_6Ej.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_42_1_fFh.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_41_2_qSR.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_40_1_W8Z.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_SGE.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_39_1_QcW.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_38_1_VKD.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_37_1_6Ju.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_36_1_MnI.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_35_1_QJa.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_34_1_6y9.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_33_2_p0n.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_32_2_AWq.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_31_1_War.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_30_1_yrv.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_1_gsb.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_29_1_QmB.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_28_1_St3.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_1_AYO.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_1_tpr.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_4_l6u.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_2_Bzl.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_1_laa.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_1_C5E.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_1_OJt.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_1_xoL.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_eXu.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_2_KSK.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_f4v.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_mic.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_1_QRU.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_2_xsY.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_1_8Rq.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_itO.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_IgQ.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_Y2j.root',
       '/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_Non.root' ] );


secFiles.extend( [
               ] )

