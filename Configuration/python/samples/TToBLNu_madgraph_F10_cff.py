####################################################################################################################################
#  
#          dataset name: /TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/dammann-Fall10-PAT-adc6a4a08f017ca447d42e2ca3c502e8/USER 
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-START38_V12-v2/AODSIM
#      number of events: 494961
#         cross section: 10.6
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_9_2_hr9.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_8_2_YoW.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_7_2_szb.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_6_2_RQv.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_5_2_zGL.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_54_2_0jc.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_53_2_n3P.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_52_2_y5V.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_51_2_BOE.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_50_2_CBO.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_4_2_ouK.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_49_2_QzC.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_48_2_dzJ.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_47_2_Hjb.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_46_2_hUF.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_45_2_25U.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_44_2_HAw.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_43_2_cmv.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_42_2_tTi.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_41_2_gV9.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_40_2_pDW.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_3_2_tl6.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_39_2_JFR.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_38_2_028.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_37_2_5iO.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_36_2_P6p.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_35_2_ZWu.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_34_2_lDW.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_33_2_GLr.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_32_2_Pot.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_31_2_sSv.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_30_2_POy.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_2_2_DIz.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_29_2_b2w.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_28_2_iDk.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_27_2_tWe.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_26_2_5nW.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_25_2_Xcf.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_24_2_SqQ.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_23_2_Ez3.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_22_2_Spo.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_21_2_Lrw.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_20_2_ZRB.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_1_2_JxD.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_19_2_uhQ.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_18_2_ROv.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_17_2_PPW.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_16_2_wQX.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_15_2_Tpd.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_14_2_feO.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_13_2_XcY.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_12_2_nQT.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_11_2_2PS.root',
       '/store/user/dammann/TToBLNu_TuneZ2_tW-channel_7TeV-madgraph/Fall10-PAT/adc6a4a08f017ca447d42e2ca3c502e8/mcpat_10_2_jtA.root' ] );


secFiles.extend( [
               ] )

