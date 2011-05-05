####################################################################################################################################
#  
#          dataset name: /WZTo3LNu_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM
#      number of events: 110000 -> 69620
#         cross section: 0.61 
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_1_1_gn6.root',
        '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_2_1_SMT.root',
        '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_3_1_AXt.root',
        '/store/user/wbehrenh/WZTo3LNu_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_4_1_PRC.root',

] );


secFiles.extend( [
               ] )

