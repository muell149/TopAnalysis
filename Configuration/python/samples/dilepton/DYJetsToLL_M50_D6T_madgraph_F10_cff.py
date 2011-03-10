####################################################################################################################################
#  
#          dataset name: /DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All 
#         mother sample: /DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/AODSIM
#      number of events: 2543383 reduced to 887394
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
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_10_1_mAl.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_11_1_8b5.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_1_1_hI7.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_12_1_isx.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_13_1_CtC.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_14_1_z48.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_15_1_CFm.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_16_1_0JW.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_17_1_qCv.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_18_1_X1i.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_19_1_HVP.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_20_1_eg0.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_21_1_Ymg.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_2_1_pNj.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_22_1_0wq.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_23_1_ykF.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_24_1_G02.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_25_1_SyY.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_26_1_xuK.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_27_1_Wt5.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_28_1_F10.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_29_1_8vq.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_30_1_NQl.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_31_1_QNf.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_3_1_1Yr.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_32_1_ohI.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_33_1_uUZ.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_34_1_57h.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_35_1_40u.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_36_1_1Yc.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_37_1_ums.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_38_1_aDw.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_39_1_Imh.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_40_1_PO6.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_41_1_ooZ.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_4_1_UCy.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_42_1_Iz2.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_43_1_xYv.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_44_1_4BC.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_45_1_TNA.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_46_1_nTH.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_47_1_GwW.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_48_1_lwO.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_49_1_OcK.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_50_1_75B.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_5_1_0BN.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_51_1_PCl.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_52_1_aHc.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_53_1_2PI.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_54_1_vAq.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_55_1_KTd.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_56_1_IeS.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_57_1_e1V.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_58_1_Ieb.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_59_1_70I.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_60_1_EA2.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_61_1_3XZ.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_6_1_dgO.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_7_1_wmZ.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_8_1_cmd.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_9_1_Nm4.root',
] );

secFiles.extend( [
               ] )
