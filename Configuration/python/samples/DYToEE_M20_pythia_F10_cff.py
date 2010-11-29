####################################################################################################################################
#  
#          dataset name: /DYToEE_M-20_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM
#      number of events: 2127607
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
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_4_Gbq.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_8tU.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_NDO.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_4_NNl.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_x3b.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_2_BF9.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_43_1_dvU.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_42_1_To1.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_41_1_K8H.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_40_1_m4v.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_4_850.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_39_2_Z72.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_38_2_RWY.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_37_1_oy5.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_36_1_mrS.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_35_2_3dH.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_34_2_6xV.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_33_1_waV.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_32_1_cZn.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_31_1_nc8.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_30_4_VfG.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_3_0K7.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_29_2_hBO.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_28_1_kcc.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_1_fdG.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_1_eDy.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_1_pjM.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_WqO.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_2_YFK.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_1_tKx.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_2_Mj0.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_2_XCV.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_nfE.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_4_R7e.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_kh3.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_2_gsg.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_1_xQ7.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_1_aXj.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_2_CzV.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_vVN.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_2_gqi.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_r7n.root',
       '/store/user/dammann/DYToEE_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_4_SEj.root' ] );


secFiles.extend( [
               ] )

