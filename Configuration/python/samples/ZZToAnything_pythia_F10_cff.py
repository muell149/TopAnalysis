####################################################################################################################################
#  
#          dataset name: /ZZtoAnything_TuneZ2_7TeV-pythia6-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /ZZtoAnything_TuneZ2_7TeV-pythia6-tauola/Fall10-START38_V12-v1/AODSIM
#      number of events: 110000
#         cross section: 7.4 
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/ZZtoAnything_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_3_Aob.root',
       '/store/user/dammann/ZZtoAnything_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_3_X76.root',
       '/store/user/dammann/ZZtoAnything_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_3_Wdw.root',
       '/store/user/dammann/ZZtoAnything_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_3_d3G.root',
       '/store/user/dammann/ZZtoAnything_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_3_0yR.root',
       '/store/user/dammann/ZZtoAnything_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_3_HyD.root' ] );


secFiles.extend( [
               ] )

