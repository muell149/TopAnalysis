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
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_10_1_rDJ.root',
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_11_1_eeC.root',
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_1_1_zED.root',
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_2_1_ekJ.root',
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_3_1_Wyx.root',
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_4_1_BDr.root',
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_5_1_7M1.root',
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_6_1_4et.root',
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_7_1_5BQ.root',
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_8_1_Ozp.root',
        '/store/user/wbehrenh/WToTauNu_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_9_1_Cc3.root',
] );


secFiles.extend( [
               ] )

