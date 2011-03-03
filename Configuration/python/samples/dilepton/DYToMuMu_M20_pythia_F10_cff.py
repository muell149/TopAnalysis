####################################################################################################################################
#  
#          dataset name: /DYToMuMu_M-20_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM 
#      number of events: 2289913 reduced to 944717
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
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_1_1_C7T.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_2_1_jHD.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_3_1_8hU.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_4_1_KKG.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_5_1_r5G.root',

] );


secFiles.extend( [
               ] )

