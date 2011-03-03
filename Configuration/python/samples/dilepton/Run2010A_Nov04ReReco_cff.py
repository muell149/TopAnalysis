import FWCore.ParameterSet.Config as cms

############################################################################################################################################
#                                                                     
#          global tag: GR_R_38X_V13::All
#
#        dataset name:/Mu/dammann-Run2010A-Nov4ReReco-PAT-v2-924c534d4f173e041134b0a34d9fb0e5/USER 
#             DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
# 
#       input sample: /Mu/Run2010A-Nov4ReReco_v1/AOD
#
#           json file: Cert_136033-149442_7TeV_Nov4ReReco_Collisions10_JSON.txt
#															     
#  integrated HF lumi: 3.180532050                                                                                        
#
#    number of events: 1813852
#
#        preselection: HLT_Mu9 AND  (beam scrap and HCAL noise cuts, PV)
#
#            cut flow:  
#		   before:	trigger:	Beam Scrap:	HCAL Noise:	PV:	
#  HLT_Mu9  path: 20868538	1816452		1816451		1815221		1813852	
#  diletopon preselection -> 94657
#                                                  
############################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_10_1_O8H.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_11_1_7xM.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_1_1_qeE.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_12_1_pGu.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_13_1_17m.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_14_1_T9M.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_15_1_Djx.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_16_1_NEp.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_17_1_vhF.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_18_1_gSi.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_19_1_JtA.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_20_1_0SP.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_21_1_xTM.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_2_1_WOZ.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_22_1_Lzs.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_23_1_SBI.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_24_1_51C.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_25_1_tn9.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_26_1_fxl.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_27_1_LKv.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_28_1_ei1.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_29_1_eyc.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_30_1_I7N.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_31_1_EDu.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_3_1_eQF.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_32_1_TL3.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_33_1_oZg.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_34_1_xWK.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_35_1_1VX.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_36_1_z83.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_37_1_NkG.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_38_1_skJ.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_39_1_8df.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_40_1_vc5.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_41_1_Uxm.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_4_1_qg0.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_42_1_svv.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_43_1_IQS.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_44_1_vVy.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_45_1_C0m.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_46_1_NAY.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_47_1_BUv.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_48_1_GN8.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_49_1_Cir.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_50_1_7rf.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_51_1_Z5o.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_5_1_ssY.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_52_1_Gbe.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_53_1_6Mh.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_6_1_zjk.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_7_1_7j3.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_8_1_o8u.root',
        '/store/user/wbehrenh/Mu/Run2010A-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_9_1_0De.root',
] );


secFiles.extend( [
               ] )

