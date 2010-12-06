import FWCore.ParameterSet.Config as cms

############################################################################################################################################
#                                                                     
#          global tag: GR_R_38X_V13::All
#
#        dataset name: /Mu/dammann-Run2010B1-Nov4ReReco-PAT-v2-924c534d4f173e041134b0a34d9fb0e5/USER
#             DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
# 
#       input sample: /Mu/Run2010A-Nov4ReReco_v1/AOD
#
#           json file: Cert_136033-149442_7TeV_Nov4ReReco_Collisions10_JSON.txt
#															     
#  integrated HF lumi: 5.056880071                                                                                    
#
#    number of events: 3120984 
#
#        preselection: (HLT_Mu9 OR HLT_Mu11) AND  (beam scrap and HCAL noise cuts, PV)
#
#            cut flow:  
#		   before:	trigger:	Beam Scrap:	HCAL Noise:	PV:	
#  HLT_Mu9  path: 7808345	3124857		3124846		3122803		3120984
#  HLT_Mu11 path: 7808345	1526350		1526344		1525109		1523978	
#                                                  
############################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_9_1_Kwc.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_8_1_DQj.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_7_1_XvS.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_6_1_JHt.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_5_1_FIv.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_4_1_UXu.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_47_1_v5d.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_46_2_8EJ.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_45_2_y3u.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_44_2_3uU.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_43_2_7Fg.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_42_2_SCc.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_41_2_Ege.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_40_1_Axc.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_3_1_DzT.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_39_1_RdP.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_38_2_q26.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_37_1_cwt.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_36_1_ZBo.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_35_2_dAZ.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_34_1_9Lc.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_33_1_s0C.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_32_2_hik.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_31_2_ft0.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_30_1_wAK.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_2_1_aYA.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_29_1_Kg5.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_28_1_VVj.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_27_1_Vau.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_26_1_T3c.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_25_2_b7i.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_24_1_df1.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_23_1_0E9.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_22_1_liH.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_21_1_iQC.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_20_2_Ome.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_1_1_DlE.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_19_2_rQo.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_18_1_Jqh.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_17_2_3ac.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_16_1_pQh.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_15_1_R59.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_14_1_iTG.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_13_1_FB0.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_12_1_SQy.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_11_1_LRK.root',
       '/store/user/dammann/Mu/Run2010B1-Nov4ReReco-PAT-v2/924c534d4f173e041134b0a34d9fb0e5/datapat_10_2_OW0.root' ] );


secFiles.extend( [
               ] )

