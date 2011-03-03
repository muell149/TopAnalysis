    ####################################################################################################################################
#  
#          dataset name: /TTJets_TuneD6T_7TeV-madgraph-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /TTJets_TuneD6T_7TeV-madgraph-tauola/AODSIM
#      number of events: 1306182 -> dilepton preselection 428495
#         cross section: 157.5 
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_10_1_1Bf.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_11_1_8Jh.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_1_1_Kok.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_12_1_267.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_13_1_Uzt.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_14_1_Bbm.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_15_1_Jo2.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_16_1_PPn.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_17_1_F9q.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_18_1_uzh.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_19_1_zZ0.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_20_1_POC.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_21_1_pST.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_2_1_mvQ.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_22_1_4LM.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_23_1_Bjz.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_24_1_lny.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_25_1_hLO.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_3_1_q6I.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_4_1_Mos.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_5_1_rkw.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_6_1_0CD.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_7_1_1W8.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_8_1_Ci3.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_9_1_rN2.root',
] );

secFiles.extend( [
               ] )


