####################################################################################################################################
#  
#          dataset name: /DYToEE_M-10To20_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
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
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_2_g3p.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_2_9A5.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_cBm.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_2_0Sj.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_HPS.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_2_PHF.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_WUy.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_39_2_dpS.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_38_1_yvN.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_37_2_BLy.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_36_1_086.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_35_2_ryb.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_34_1_dks.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_33_2_htA.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_32_1_Xkk.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_31_2_4hY.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_30_2_SVE.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_2_pbl.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_29_1_RXd.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_28_1_Itc.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_2_Hv7.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_1_kQF.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_2_1UC.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_VuR.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_2_4aO.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_2_1rg.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_1_7gS.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_2_9lx.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_2_IpE.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_1_2AX.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_2_0k8.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_2_UeM.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_2_4SE.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_1_7T7.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_2_hMw.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_2_3Qa.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_2_3r8.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_2_fBE.root',
       '/store/user/dammann/DYToEE_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_CWU.root' ] );


secFiles.extend( [
               ] )


