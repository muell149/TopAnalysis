####################################################################################################################################
#  
#          dataset name: /WWTo2L2Nu_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-adc6a4a08f017ca447d42e2ca3c502e8/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM
#      number of events: 110000
#         cross section: 4.51 
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_9_2_x5Z.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_8_1_HRh.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_7_1_PBt.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_6_2_mSq.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_5_1_QrH.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_4_1_POY.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_3_1_XXv.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_2_3_Nj9.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_1_1_Ym6.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_14_1_Qu8.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_13_2_0GF.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_12_2_I0w.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_11_2_ocj.root',
       '/store/user/dammann/WWTo2L2Nu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_10_2_dsH.root' ] );


secFiles.extend( [
               ] )
