####################################################################################################################################
#  
#          dataset name: /TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER 
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-START38_V12-v2/AODSIM
#      number of events: 494961
#         cross section: 10.6
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_GXL.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_IG0.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_Eag.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_1_Pm8.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_wpp.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_KgG.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_Kzz.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_1_NIl.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_Hom.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_wOB.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_Jzw.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_h4C.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_SoG.root' ] );


secFiles.extend( [
               ] )

