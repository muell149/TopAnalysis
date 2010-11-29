####################################################################################################################################
#  
#          dataset name: /DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /DYToTauTau_M-20_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM 
#      number of events: 2007446
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
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_6_b2e.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_6_JVk.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_2_asC.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_2_JWp.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_2_UVE.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_2_VOe.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_42_1_8Qp.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_41_2_xrw.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_40_2_XSp.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_ToN.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_39_2_qMW.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_38_2_fZz.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_37_6_QXr.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_36_5_THr.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_35_2_y6Z.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_34_2_9dO.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_33_2_sai.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_32_2_Ufj.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_31_2_lRF.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_30_2_0AN.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_2_hc1.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_29_2_n2V.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_28_2_ilo.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_2_JXY.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_6_3AD.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_2_d6U.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_2_ykd.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_5_292.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_2_TV7.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_6_cFY.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_uFq.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_2_DXQ.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_6_52l.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_2_OCj.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_6_V8d.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_2_UnL.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_1_UKl.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_ZDb.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_2_HMi.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_2_wzT.root',
       '/store/user/dammann/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_2_Jav.root' ] );


secFiles.extend( [
               ] )

