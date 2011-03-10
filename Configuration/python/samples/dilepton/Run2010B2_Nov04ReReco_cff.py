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
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_10_1_F1b.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_11_1_WVC.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_1_1_V17.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_12_1_jPH.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_13_1_vxQ.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_14_1_Kyq.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_15_1_O19.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_16_1_OdV.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_17_1_WfU.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_18_1_Otl.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_19_1_K9J.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_20_1_jCI.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_21_1_U8s.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_2_1_Aix.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_22_1_YsE.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_23_1_2Jv.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_24_1_Bqw.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_25_1_XlG.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_26_1_py9.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_27_1_L3h.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_28_1_GBB.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_29_1_CXB.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_30_1_FA8.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_31_1_OPS.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_3_1_u4s.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_4_1_FWU.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_5_1_nJA.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_6_1_UIs.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_7_1_dZ1.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_8_1_DQl.root',
        '/store/user/wbehrenh/Mu/Run2010B2-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_9_1_uqd.root',
] );

secFiles.extend( [
               ] )

