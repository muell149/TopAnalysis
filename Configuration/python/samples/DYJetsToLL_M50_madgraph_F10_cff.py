####################################################################################################################################
#  
#          dataset name: /DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All 
#         mother sample: /DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-START38_V12-v2/AODSIM
#      number of events: 2604559
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
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_Mkw.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_TW9.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_qPi.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_1_CWI.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_wmj.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_55_1_xPm.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_54_1_XSM.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_53_1_oBf.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_52_1_ZOc.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_51_1_IpD.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_50_1_4rL.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_GOu.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_49_1_m7B.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_48_1_swH.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_47_1_TPG.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_46_1_fKp.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_45_1_pFE.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_44_1_0FA.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_43_1_zP5.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_42_1_TGj.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_41_1_qZf.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_40_1_gwW.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_7or.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_39_1_PBH.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_38_1_lC0.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_37_1_UFi.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_36_1_jyt.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_35_1_YMg.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_34_1_qZ9.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_33_1_qdZ.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_32_1_WTX.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_31_1_L8a.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_30_1_w7T.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_1_zhM.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_29_1_oO2.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_28_1_BOy.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_1_fFO.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_1_lEL.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_1_o9s.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_utk.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_1_juo.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_1_lyG.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_1_i2g.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_1_d8s.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_Mar.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_1_vnQ.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_r4T.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_cT9.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_1_sCq.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_1_fA9.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_1_DHf.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_mte.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_Gtu.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_XuK.root',
       '/store/user/dammann/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_Y6y.root' ] );


secFiles.extend( [
               ] )

