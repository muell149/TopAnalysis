import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_9_1_X6Z.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_8_1_fpV.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_7_2_CAz.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_6_2_bw0.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_5_2_BD0.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_4_2_3p3.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_3_1_M05.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_2_2_WVh.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_1_1_vND.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_19_2_kUP.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_18_2_413.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_17_2_93Z.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_16_2_zVi.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_15_2_OIw.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_14_1_jyj.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_13_2_JE2.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_12_1_jUV.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_11_2_HPU.root',
       '/store/user/blutz/MuEG/Run2011A_PromtReco_v1_413p2_emu_PAT_May7_160404_163757/ff994a794bcc4e69b8f55abe5d119a58/datapat_10_1_DHi.root' ] );


secFiles.extend( [
               ] )

