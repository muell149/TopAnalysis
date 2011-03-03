####################################################################################################################################
#  
#          dataset name: /DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All 
#         mother sample: /DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-START38_V12-v2/AODSIM
#      number of events: 2604559 reduced to 912644
#         cross section: 3048
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_10_1_THw.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_11_1_uMg.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_1_1_pa3.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_12_1_BAj.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_13_1_SfH.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_14_1_lmc.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_15_1_53E.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_16_1_BdE.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_17_1_tN4.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_18_1_WWm.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_19_1_w5g.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_20_1_DFZ.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_21_1_DlK.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_2_1_jiz.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_22_1_1r0.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_23_1_XJ3.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_24_1_sTm.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_25_1_2oC.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_26_1_7p9.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_27_1_Ras.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_28_1_Ema.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_29_1_6XM.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_30_1_4pa.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_31_1_XUO.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_3_1_94x.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_32_1_jtE.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_33_1_mlN.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_34_1_6jJ.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_35_1_5ES.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_36_1_FYL.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_37_1_WSz.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_38_1_O5I.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_39_1_UFY.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_40_1_0I0.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_41_1_qLZ.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_4_1_aRl.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_42_1_Zkz.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_43_1_l8A.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_44_1_sxL.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_45_1_9Ia.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_46_1_3PK.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_47_1_XRT.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_48_1_Hym.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_49_1_lxJ.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_50_1_amn.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_5_1_TEG.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_6_1_Njj.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_7_1_aUN.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_8_1_Tkr.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Fall10-PAT-dilepton/7c5885cec7be1acc054f3cfa0506b8b8/reduced_9_1_UMS.root',
] );


secFiles.extend( [
               ] )

