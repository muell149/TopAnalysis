import FWCore.ParameterSet.Config as cms

############################################################################################################################################
#                                                                     
#          global tag: GR_R_38X_V13::All
#
#        dataset name: /Mu/dammann-Run2010B2-Nov4ReReco-PAT-v2-924c534d4f173e041134b0a34d9fb0e5/USER 
#             DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
# 
#       input sample: /Mu/Run2010A-Nov4ReReco_v1/AOD
#
#           json file: Cert_136033-149442_7TeV_Nov4ReReco_Collisions10_JSON.txt 
#															     
#  integrated HF lumi: 27.907588871                                                                                     
#
#    number of events: 5498448
#
#        preselection: (HLT_Mu9 OR HLT_Mu11 OR HLT_Mu15) AND  (beam scrap and HCAL noise cuts, PV)
#
#            cut flow:  
#		   before:	trigger:	Beam Scrap:	HCAL Noise:	PV:	
#  HLT_Mu9  path: 20387348	 884958		 884955		 884378		 883985
#  HLT_Mu11 path: 20387348 	3217005		3216995		3214537		3212610
#  HLT_Mu15 path: 20387348 	2792576		2792548		2789600		2786855
# dilepton preselection -> 427560
#                                                  
############################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_10_1_4Db.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_11_1_pHE.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_1_1_y72.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_12_1_64J.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_13_1_aVg.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_14_1_2Bi.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_15_1_t7R.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_16_1_elJ.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_17_1_6tP.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_18_1_bfD.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_19_1_ChL.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_20_1_GHD.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_21_1_SDU.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_2_1_due.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_22_1_QJs.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_23_1_bTm.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_24_1_qPG.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_25_1_LGF.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_26_1_nj1.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_27_1_1cZ.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_28_1_iZv.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_29_1_uli.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_30_1_hb7.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_31_1_XH5.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_3_1_sgB.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_32_1_q9G.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_33_1_c9B.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_34_1_5Ls.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_35_1_7ZC.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_36_1_heJ.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_37_1_FpD.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_38_1_Pmf.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_39_1_d64.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_40_1_OZg.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_41_1_uhN.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_4_1_BuW.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_42_1_pHC.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_43_1_BDZ.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_44_1_qpo.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_45_1_gNd.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_46_1_5eP.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_47_1_izH.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_48_1_eMT.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_49_1_ZUG.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_50_1_Wfw.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_51_1_o45.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_5_1_6BJ.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_52_1_lGH.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_53_1_u15.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_54_1_Md9.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_55_1_el1.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_56_1_zsB.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_57_1_knz.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_58_1_irt.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_59_1_4rx.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_60_1_mZT.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_61_1_18B.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_6_1_bGU.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_7_1_byX.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_8_1_Lus.root',
       '/store/user/wbehrenh/Mu/Run2010B2-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_9_1_B9m.root',
] );

secFiles.extend( [
               ] )

