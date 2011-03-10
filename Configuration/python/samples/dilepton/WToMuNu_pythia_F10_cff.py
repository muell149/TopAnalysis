####################################################################################################################################
#  
#          dataset name: /WToMuNu_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /WToMuNu_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM
#      number of events: 5323040 dilepton passed 64554
#         cross section: 10438
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_1_2_uVn.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_2_1_dYe.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_3_2_duy.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_4_2_EuP.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_5_1_tbb.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_6_1_YcT.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_7_1_5rD.root',

] );


secFiles.extend( [
               ] )

