####################################################################################################################################
#  
#          dataset name: /DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM
#      number of events: 2227840 reduced to 38046
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
        '/store/user/wbehrenh/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_1_1_DUk.root',
        '/store/user/wbehrenh/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_2_1_iPv.root',
        '/store/user/wbehrenh/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_3_1_DnF.root',
        '/store/user/wbehrenh/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_4_2_2OB.root',

] );


secFiles.extend( [
               ] )

