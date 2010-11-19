####################################################################################################################################
#  
#          dataset name: ---
#               DBS URL: ---
#            global tag: START38_V13::All
#         mother sample: /DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/slava77-Fall10-START38_
#                        V12-v2-TopReferencePass6-7da0dde13a8e2397b448259411a72ca2/USER 
#      number of events: 5000
#         cross section: 3048 
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_10_1_Shl.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_11_1_892.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_12_1_r1F.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_13_1_86w.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_13_2_asH.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_14_1_EM2.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_15_1_shj.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_16_1_Ulf.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_17_1_Z5V.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_18_1_51d.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_19_1_2Wl.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_1_1_fFI.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_20_1_q7i.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_21_1_PxS.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_22_1_pQY.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_23_1_5JH.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_24_1_ElW.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_25_1_eFQ.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_26_1_CqM.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_27_1_qtB.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_28_1_kJF.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_29_1_CH7.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_2_1_vGM.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_30_1_efW.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_31_1_fvg.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_32_1_tVp.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_33_1_7sy.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_34_1_bbU.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_35_1_79b.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_36_1_Wjp.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_37_1_p2o.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_38_1_b2E.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_39_1_wZA.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_3_1_QM6.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_40_1_JQR.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_41_1_0RC.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_42_1_IJG.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_43_1_SOA.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_44_1_pwm.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_45_1_dJb.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_46_1_AZK.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_47_1_guL.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_48_1_e0T.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_49_1_YdJ.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_4_1_0Al.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_50_1_vSs.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_5_1_1kJ.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_6_1_BXD.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_7_1_xK6.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_8_1_qnh.root',
		'/store/user/dammann/38X/Synchronisation/zjets_mad_sync_9_1_Q7w.root'] );


secFiles.extend( [
               ] )

