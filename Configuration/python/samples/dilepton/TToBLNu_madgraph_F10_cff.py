####################################################################################################################################
#  
#          dataset name: /TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER 
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-START38_V12-v2/AODSIM
#      number of events: 494961 -> 119117
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
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_10_1_HrP.root',
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_11_1_Qnk.root',
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_1_1_wax.root',
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_12_1_tKd.root',
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_13_1_Uhw.root',
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_2_1_dk8.root',
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_3_1_5E1.root',
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_4_1_0Iq.root',
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_5_1_AHF.root',
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_6_1_VPX.root',
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_7_1_kul.root',
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_8_1_BdS.root',
        '/store/user/wbehrenh/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_9_1_WCn.root',

] );


secFiles.extend( [
               ] )

