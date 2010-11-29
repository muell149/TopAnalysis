####################################################################################################################################
#  
#          dataset name: /WZTo3LNu_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM
#      number of events: 110000
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
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_R3C.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_4_kkE.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_4_Jrw.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_4_bcR.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_uw1.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_4_mmk.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_4_OFa.root' ] );


secFiles.extend( [
               ] )

