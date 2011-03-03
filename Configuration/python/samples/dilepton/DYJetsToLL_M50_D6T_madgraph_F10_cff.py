####################################################################################################################################
#  
#          dataset name: /DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All 
#         mother sample: /DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/AODSIM
#      number of events: 2543383 reduced to 887394
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
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_1_1_xGR.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_2_1_Npf.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_3_1_JoK.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_4_1_62S.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_5_1_iJh.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_6_1_HbX.root',

] );

secFiles.extend( [
               ] )
