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
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_10_1_CfW.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_11_1_laM.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_1_1_U3n.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_12_1_EpM.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_13_1_SI4.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_14_1_ySu.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_15_1_wlF.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_16_1_Iav.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_2_1_UOr.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_3_1_ek4.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_4_1_Dh5.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_5_1_qVL.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_6_1_qr7.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_7_1_VoZ.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_8_1_quY.root',
        '/store/user/wbehrenh/Mu/Run2010B1-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_9_1_bnq.root',
] );


secFiles.extend( [
               ] )

