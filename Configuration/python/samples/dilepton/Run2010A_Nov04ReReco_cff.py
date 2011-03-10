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
        '/store/user/wbehrenh/Mu/Run2010A-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_10_1_Vrt.root',
        '/store/user/wbehrenh/Mu/Run2010A-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_1_1_kti.root',
        '/store/user/wbehrenh/Mu/Run2010A-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_2_1_yOh.root',
        '/store/user/wbehrenh/Mu/Run2010A-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_3_1_Z0G.root',
        '/store/user/wbehrenh/Mu/Run2010A-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_4_1_g2c.root',
        '/store/user/wbehrenh/Mu/Run2010A-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_5_1_1f3.root',
        '/store/user/wbehrenh/Mu/Run2010A-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_6_1_kv7.root',
        '/store/user/wbehrenh/Mu/Run2010A-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_7_1_OMg.root',
        '/store/user/wbehrenh/Mu/Run2010A-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_8_1_3N8.root',
        '/store/user/wbehrenh/Mu/Run2010A-Dilepton/1ede7305c3ad77ba3f9f43a35db094f4/reduced_9_1_rwP.root',
] );


secFiles.extend( [
               ] )

