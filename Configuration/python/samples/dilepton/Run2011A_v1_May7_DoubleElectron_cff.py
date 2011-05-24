import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_9_1_c5G.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_8_1_tNX.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_7_1_YC5.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_6_1_IyN.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_5_1_iH4.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_4_1_v1X.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_3_1_WWz.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_39_3_NBg.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_38_2_Iui.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_37_1_yeS.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_36_1_rRh.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_35_1_SLK.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_34_1_wFX.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_33_1_UjZ.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_32_1_SMk.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_31_1_2T3.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_30_1_rAL.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_2_1_vrf.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_29_1_LYh.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_28_1_vrT.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_27_1_pBM.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_26_1_UTY.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_25_1_pJ7.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_24_1_a6g.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_23_1_SOB.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_22_1_li8.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_21_1_j9N.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_20_1_JWQ.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_1_1_hO7.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_19_1_SX8.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_18_1_3N2.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_17_1_wCt.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_16_1_6t4.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_15_1_Di7.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_14_1_9MV.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_13_1_mjA.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_12_1_EnO.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_11_1_v95.root',
       '/store/user/blutz/DoubleElectron/Run2011A_PromtReco_v1_413p2_ee_PAT_May7_160404_163757/bff4dbd2d58a34b3eeec10cdab18a416/datapat_10_1_lww.root' ] );


secFiles.extend( [
               ] )

