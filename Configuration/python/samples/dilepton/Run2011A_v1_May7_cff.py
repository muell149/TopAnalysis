import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_9_1_kaS.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_8_1_NrW.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_7_1_yGj.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_6_1_ypg.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_5_1_63c.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_4_1_9Ag.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_3_1_WLv.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_2_1_EVj.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_27_1_zHr.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_26_1_3Gp.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_25_1_FCH.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_24_1_QCr.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_23_1_ojK.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_22_1_PFK.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_21_1_uLr.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_20_1_0G2.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_1_2_SBt.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_19_1_YBk.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_18_1_07d.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_17_1_0DR.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_16_1_qeu.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_15_1_uPB.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_14_1_cFY.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_13_1_Umn.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_12_1_wii.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_11_1_T81.root',
       '/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_10_3_uv0.root' ] );


secFiles.extend( [
               ] )

