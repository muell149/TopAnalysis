####################################################################################################################################
#  
#          dataset name: /DYToMuMu_M-20_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM 
#      number of events: 2289913
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
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_Ke4.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_2_Bx2.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_2_Q5B.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_1_moB.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_jNs.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_Vhv.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_46_1_zS4.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_45_5_KpS.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_44_2_cig.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_43_2_2vj.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_42_2_7Ll.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_41_4_PK0.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_40_2_ofg.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_2_wO8.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_39_2_nSC.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_38_2_ZI2.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_37_1_sI5.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_36_2_9HL.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_35_4_U9t.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_34_2_cNm.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_33_4_qBo.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_32_2_skA.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_31_2_VLi.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_30_2_m1H.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_2_K59.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_29_1_OdU.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_28_4_WsB.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_5_Cef.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_2_dBD.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_2_xG7.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_Y67.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_2_41W.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_4_NWl.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_2_LUd.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_2_0lT.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_UM0.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_2_UIi.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_4_AzM.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_4_tVn.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_2_vzr.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_2_rkX.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_2_7nR.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_2_XVZ.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_4_SIQ.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_esU.root',
       '/store/user/dammann/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_2_K8H.root' ] );


secFiles.extend( [
               ] )

