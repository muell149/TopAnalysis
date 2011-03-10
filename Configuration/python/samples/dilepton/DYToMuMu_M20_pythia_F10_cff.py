####################################################################################################################################
#  
#          dataset name: /DYToMuMu_M-20_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM 
#      number of events: 2289913 reduced to 944717
#         cross section: 1666 
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_10_1_XZE.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_11_1_1Xi.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_1_1_zJr.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_12_1_hVe.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_13_1_9IK.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_14_1_kvd.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_15_1_vV4.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_16_1_Y45.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_17_1_RBS.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_18_1_k9L.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_19_1_K2E.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_20_1_b6p.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_21_1_s1T.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_2_1_gO6.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_22_1_ilY.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_23_1_wFY.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_24_1_8gH.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_25_1_xzV.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_26_1_XMC.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_27_1_pR7.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_28_1_ECF.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_29_1_tMY.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_30_1_us5.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_31_1_2CN.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_3_1_oit.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_32_1_394.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_33_1_8Ad.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_34_1_fti.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_35_1_PDt.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_36_1_aKa.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_37_1_Sih.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_38_1_qwD.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_39_1_gld.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_40_1_0ZQ.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_41_1_DDS.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_4_1_dTs.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_42_1_WpC.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_43_1_cdP.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_44_1_mkH.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_45_1_Km0.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_46_1_Qnt.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_47_1_r7x.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_48_1_raJ.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_49_1_kDE.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_50_1_p3b.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_5_1_0JX.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_51_1_I7p.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_52_1_hys.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_53_1_fux.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_54_1_fac.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_55_1_p9r.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_56_1_cFN.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_57_1_YiY.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_58_1_P1a.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_59_1_8xx.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_60_1_1CD.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_61_1_dxc.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_6_1_8VE.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_7_1_Epz.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_8_1_Gub.root',
        '/store/user/wbehrenh/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_9_1_nlc.root',

] );


secFiles.extend( [
               ] )

