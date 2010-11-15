####################################################################################################################################
#  
#          dataset name: /WZTo3LNu_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-adc6a4a08f017ca447d42e2ca3c502e8/USER
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
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_9_1_Qxp.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_8_2_p9l.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_7_2_nxz.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_6_2_gaw.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_5_2_hfQ.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_4_2_cKc.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_3_1_MA1.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_2_1_k6J.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_1_1_kUn.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_12_1_R4i.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_11_3_F00.root',
       '/store/user/dammann/WZTo3LNu_TuneZ2_7TeV-pythia6/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_10_1_Ggv.root' ] );


secFiles.extend( [
               ] )

