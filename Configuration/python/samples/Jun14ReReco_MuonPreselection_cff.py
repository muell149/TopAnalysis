import FWCore.ParameterSet.Config as cms

###########################################################################################
#  
#  NOT YET COMPLETE! ABOUT 25 - 30 NB6\^-1
#
#          global tag: GR_R_36X_V12::All
# 
#       input samples: 
#                       
#
#           json file:
#                                                                                                                                                   
#  integrated HF lumi:                                                                                                                   
#
#    number of events: 230763
#
#        preselection: general qualtity cuts (see below)  AND 
#                      ( 1 global muon with pt > 5GeV  OR  2 global muons )
#
#            cut flow: 
#
#                                              
###########################################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(	
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_10_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_11_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_12_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_13_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_14_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_15_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_16_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_17_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_18_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_19_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_1_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_20_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_21_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_22_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_23_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_24_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_25_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_26_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_27_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_28_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_29_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_2_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_30_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_31_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_32_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_33_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_34_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_35_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_36_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_37_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_3_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_4_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_5_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_6_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_7_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_8_0.root',
        '/store/user/dammann/36X/Collisions10/Jun14thSkim_9_0.root',
	
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_10_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_1_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_2_2.root',
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_3_2.root',
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_4_2.root',
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_5_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_6_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_7_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_8_1.root',
        '/store/user/dammann/36X/Collisions10/Jun14thReReco_9_1.root',

        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_10_2.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_11_0.root',
	'/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_12_2.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_14_0.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_15_0.root',
	'/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_16_1.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_18_0.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_19_0.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_20_0.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_24_2.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_25_0.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_26_0.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_28_2.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_30_1.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_31_1.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_6_3.root',
        '/store/user/dammann/36X/Collisions10/MuRun2010A_v4a_9_0.root'        
       )
)
