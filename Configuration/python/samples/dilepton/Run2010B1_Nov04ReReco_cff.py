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
# dilepton preselection -> 163887
#                                                  
############################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_10_1_Sop.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_11_1_t33.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_1_1_eAt.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_12_1_e06.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_13_1_fja.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_14_1_Z1k.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_15_1_y3u.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_16_1_65p.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_17_1_pof.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_18_1_v7v.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_19_1_b3i.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_20_1_gpV.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_21_1_ub8.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_2_1_gOG.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_22_1_u9H.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_23_1_9sP.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_24_1_pTs.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_25_1_NBe.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_26_1_spC.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_27_1_TpW.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_28_1_laQ.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_29_1_lh3.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_30_1_6UI.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_31_1_zcd.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_3_1_AIP.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_32_1_5zo.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_33_1_rWa.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_34_1_6RF.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_35_1_iuk.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_36_1_1k5.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_37_1_JJJ.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_38_1_RKw.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_39_1_Gf7.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_40_1_ksy.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_41_1_bSQ.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_4_1_n8f.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_42_1_Yqs.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_43_1_3cD.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_44_1_t3p.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_45_1_wSK.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_46_1_HtQ.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_5_1_66B.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_6_1_jfM.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_7_1_FuY.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_8_1_MxG.root',
        '/store/user/wbehrenh/Mu/Run2010B1-dilepton/7d8ccb9c3294032d2947e73a2d0b4e39/reduced_9_1_HOc.root',
] );


secFiles.extend( [
               ] )

