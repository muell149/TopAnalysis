####################################################################################################################################
#  
#          dataset name: /WToTauNu_TuneZ2_7TeV-pythia6-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-START38_V12-v1/GEN-SIM-RECO 
#      number of events: 5221750 dilepton passed 17470
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
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_1_2_KSX.root',
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_2_2_CKH.root',

] );


secFiles.extend( [
               ] )

