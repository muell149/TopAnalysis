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
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_10_1_tgd.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_11_1_KEA.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_1_1_vCO.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_12_1_Du6.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_13_1_iYl.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_14_1_BII.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_15_1_Wo6.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_16_1_npd.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_17_1_hld.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_18_1_bus.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_19_1_S3F.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_20_1_u7T.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_21_1_ifl.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_2_1_tgN.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_22_1_da3.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_23_1_Otm.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_24_1_ADk.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_25_1_6lL.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_26_2_W85.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_27_1_yzK.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_28_1_5Wz.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_29_1_gWo.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_30_1_NxH.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_31_1_dng.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_3_1_Dsd.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_32_1_J0g.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_33_2_V3F.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_34_1_bon.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_35_1_UJk.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_36_1_xbB.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_37_1_yWQ.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_38_1_QMz.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_39_1_tUU.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_40_1_TYR.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_41_1_lR2.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_42_1_INn.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_4_2_HhY.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_43_1_zVc.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_44_1_g6H.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_45_1_90o.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_46_1_hh4.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_47_1_Skc.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_48_1_ynj.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_49_1_gBV.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_50_1_cYt.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_51_1_Y65.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_5_1_5r0.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_52_1_0Cm.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_53_1_ipr.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_54_1_mUk.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_55_1_Er6.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_56_2_xNy.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_57_1_B1x.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_58_1_t3h.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_59_1_JRi.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_60_1_ZGS.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_61_1_wJa.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_6_1_IXK.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_7_1_EaV.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_8_1_hiJ.root',
        '/store/user/wbehrenh/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_9_1_zAq.root',

] );


secFiles.extend( [
               ] )

