    ####################################################################################################################################
#  
#          dataset name: /TTJets_TuneD6T_7TeV-madgraph-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /TTJets_TuneD6T_7TeV-madgraph-tauola/AODSIM
#      number of events: 1306182 -> dilepton preselection 428495
#         cross section: 157.5 
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_10_1_aiR.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_11_1_Cc0.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_1_1_lIJ.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_12_1_hla.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_13_1_U1D.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_14_1_bxN.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_15_1_pSa.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_16_1_nCT.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_17_1_voI.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_18_1_dbi.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_19_1_O0G.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_20_1_arf.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_21_1_kex.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_2_1_Sl6.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_22_1_vwu.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_23_1_ZBV.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_24_1_6dl.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_25_1_4nS.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_26_1_P2B.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_27_1_k6A.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_28_1_bv4.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_29_1_3YO.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_30_1_1Jr.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_31_1_l7h.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_3_1_vCe.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_32_1_UeB.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_33_1_Mk4.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_34_1_ABr.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_35_1_G6m.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_36_1_crx.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_37_1_mHG.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_38_1_4wI.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_39_1_lLf.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_40_1_kbK.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_41_1_tX6.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_4_1_rSf.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_42_1_fZz.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_43_1_BCe.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_44_1_Al5.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_45_1_KQL.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_46_1_p0I.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_47_1_ku0.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_48_1_VTa.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_49_1_JYM.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_50_1_Urk.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_51_1_QOh.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_5_1_o1D.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_52_1_CnK.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_53_1_H6Q.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_54_1_25H.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_55_1_J9A.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_56_1_YJx.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_57_1_yyG.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_58_1_03Q.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_59_1_2ij.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_60_1_E3p.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_61_1_xFO.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_6_1_sZG.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_7_1_PT5.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_8_1_YzS.root',
        '/store/user/wbehrenh/TTJets_TuneD6T_7TeV-madgraph-tauola/Dilepton/434c2dc7404169951255c872ffa24f4a/reduced_9_1_f5p.root',

] );

secFiles.extend( [
               ] )


