####################################################################################################################################
#  
#          dataset name: /QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM
#      number of events: 29504866 reduced to 3140367
#         cross section: 296600000
#  generator efficiency: 0.0002855
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_10_1_ljX.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_11_1_77V.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_1_1_SYD.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_12_1_Fpz.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_13_1_Gb7.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_14_1_dVs.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_15_1_gSJ.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_16_1_3if.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_17_1_PWx.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_18_1_N9I.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_19_1_fi5.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_20_1_trK.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_21_1_WpI.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_2_1_lFQ.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_22_1_u4A.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_23_1_Ify.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_24_1_R41.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_25_1_tiE.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_26_1_XAQ.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_27_1_iWd.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_28_1_rUS.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_29_1_hjr.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_30_1_SgP.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_31_1_PMe.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_3_1_UGB.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_32_1_l0p.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_33_1_3KT.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_34_1_UXX.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_35_1_Llr.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_36_1_YLS.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_37_1_p2v.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_38_1_BTk.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_39_1_Vrl.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_40_1_Ftn.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_41_1_TVQ.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_4_1_fZf.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_42_1_RR6.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_43_1_jpS.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_44_1_Gjg.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_45_1_BUR.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_46_1_asq.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_47_1_lxv.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_48_1_sXi.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_49_1_8FQ.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_50_1_1Pu.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_51_1_n3q.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_5_1_YyC.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_52_1_EOo.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_53_1_gg9.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_54_1_7oU.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_55_1_CNw.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_56_1_5xY.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_57_1_WjF.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_58_1_ddv.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_59_1_J1W.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_60_1_r1M.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_6_1_Ygj.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_7_1_OqX.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_8_1_Vtf.root',
        '/store/user/wbehrenh/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6/Fall10-PAT-dilepton/0e884a0df8f72902043010e3e3276b73/reduced_9_1_XOB.root',
] );


secFiles.extend( [
               ] )

