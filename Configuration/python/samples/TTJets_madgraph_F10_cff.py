####################################################################################################################################
#  
#          dataset name: /TTJets_TuneZ2_7TeV-madgraph-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-START38_V12-v2/AODSIM
#      number of events: 1156119
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
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_Ihy.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_ciI.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_zeH.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_1_Dz1.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_TSf.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_20Y.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_QPM.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_1_KCT.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_1_9ve.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_Gjg.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_1_ORZ.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_1_RSa.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_1_BrS.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_1_g9b.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_kXO.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_1_JBb.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_yhS.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_1tN.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_1_ZAa.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_1_1xi.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_1_gtl.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_SdN.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_D5t.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_JSk.root',
       '/store/user/dammann/TTJets_TuneZ2_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_BGe.root' ] );


secFiles.extend( [
               ] )

