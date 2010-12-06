####################################################################################################################################
#  
#          dataset name: /TTJets_TuneD6T_7TeV-madgraph-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /TTJets_TuneD6T_7TeV-madgraph-tauola/AODSIM
#      number of events: 1306182
#         cross section: 157.5 
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_CQ7.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_2_tNW.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_pfn.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_2_cx8.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_kt6.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_KRU.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_vjO.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_30_1_QEQ.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_1_1EJ.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_29_1_P8Q.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_28_1_4Om.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_1_1WU.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_1_smP.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_1_M1c.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_nUc.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_1_gXQ.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_2_yNs.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_1_JdU.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_1_20W.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_Gvp.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_1_fta.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_4SO.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_VnU.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_1_1Dk.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_1_67o.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_1_ucO.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_f75.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_TMy.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_2_IWV.root',
       '/store/user/dammann/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_o5I.root' ] );


secFiles.extend( [
               ] )


