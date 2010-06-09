import FWCore.ParameterSet.Config as cms

######################################################################
#                                                                     
#       /Mu/Run2010A-PromptReco-v1/RECO           
#                                                                     
#                                                                                                                    
#     int lumi: 1.78/nb
# preselection: 1 selPatMuon, pt > 5GeV
#
#  first run: 135808
#   last run: 136086
#                                              
######################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_1.root',		
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_2.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_3.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_4.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_5.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_6.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_7.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_8.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_9.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_10.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_11.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_12.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_v1_5GeVMuon_13.root'
       )
)
