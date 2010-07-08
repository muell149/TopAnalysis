import FWCore.ParameterSet.Config as cms

###########################################################################################
#  
#          global tag: GR_R_36X_V11A::All
# 
#       input samples: /MinimumBias/Commissioning10-May27thSkim_SD_Mu-v2/RECO
#                      /Mu/Run2010A-May27thReReco_v2/RECO  
#
#           json file: Cert_132440-136119_7TeV_May27thReReco_Collisions10_JSON.txt
#                                                                                                                                                   
#  integrated HF lumi: 11.39/nb                                                                                                                  
# integrated VTX lumi: 11.67/nb
#
#    number of events: 89229
#
#        preselection: general qualtity cuts (see below)  AND 
#                      ( 1 global muon with pt > 5GeV  OR  2 global muons )
#
#            cut flow: not available yet
#
#                                              
###########################################################################################

source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(	
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_10_1_ZGc.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_11_1_0y0.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_12_2_NAb.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_13_1_isx.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_14_1_Jjf.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_15_1_eyz.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_16_1_20x.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_17_1_V00.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_18_1_iAh.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_19_1_XdF.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_1_2_zMp.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_20_2_P5B.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_21_1_4Mj.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_22_1_s7S.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_23_1_zv7.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_24_1_f5s.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_25_1_kbL.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_26_1_DLX.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_27_1_iyQ.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_28_1_ET2.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_29_1_av8.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_2_1_JoX.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_30_1_OCh.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_31_1_mhk.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_32_1_arQ.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_33_1_PbN.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_34_1_2fN.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_35_1_p0t.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_36_1_Ofp.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_3_1_2Vc.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_4_1_r8K.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_5_1_z4T.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_6_1_Gud.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_7_3_1xg.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_8_1_Air.root',
        '/store/user/dammann/36X/Collisions10/Commissioning10_May27thSkim_SD_Mu_v2b_9_1_q8w.root',
	
        '/store/user/dammann/36X/Collisions10/Run2010A_May27thReReco_Mu_v2b_1_1_JBd.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_May27thReReco_Mu_v2b_2_1_Mko.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_May27thReReco_Mu_v2b_3_5_lTd.root',
        '/store/user/dammann/36X/Collisions10/Run2010A_May27thReReco_Mu_v2b_4_1_JTP.root'
       )
)
