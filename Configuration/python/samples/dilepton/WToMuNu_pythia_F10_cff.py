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
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_10_1_Eq5.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_11_1_uBt.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_1_1_vn3.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_12_1_diV.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_2_1_OUD.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_3_1_a5J.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_4_1_dZM.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_5_1_jLB.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_6_1_yR7.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_7_1_LdM.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_8_1_fl1.root',
        '/store/user/wbehrenh/WToMuNu_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_9_1_tVB.root',

] );


secFiles.extend( [
               ] )

