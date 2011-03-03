####################################################################################################################################
#  
#          dataset name: /DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /DYToTauTau_M-20_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM 
#      number of events: 2007446 reduced to 46512
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
        '/store/user/wbehrenh/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_1_1_NDU.root',
        '/store/user/wbehrenh/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_2_1_kvR.root',
        '/store/user/wbehrenh/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_3_1_4p0.root',
        '/store/user/wbehrenh/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_4_1_a5p.root',
        '/store/user/wbehrenh/DYToTauTau_M-20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_5_1_q6U.root',

] );


secFiles.extend( [
               ] )

