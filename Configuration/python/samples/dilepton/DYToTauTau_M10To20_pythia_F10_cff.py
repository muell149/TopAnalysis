####################################################################################################################################
#  
#          dataset name:/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER 
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-START38_V12-v1/AODSIM
#      number of events: 2142450 reduced to 201
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
        '/store/user/wbehrenh/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_1_1_KLs.root',
        '/store/user/wbehrenh/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_2_1_GVM.root',
        '/store/user/wbehrenh/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_3_1_v9G.root',
        '/store/user/wbehrenh/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_4_1_lSE.root',
        '/store/user/wbehrenh/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_5_1_mGK.root',

] );


secFiles.extend( [
               ] )

