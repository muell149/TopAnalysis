####################################################################################################################################
#  
#          dataset name: /DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/AODSIM
#      number of events: 2227840
#         cross section: 3457
#  generator efficiency: 1.0000
#
####################################################################################################################################

import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_3_xQZ.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_2_OFK.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_3_lTF.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_2_ux9.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_4_Lnl.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_2_8Mz.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_45_2_XLO.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_44_3_rDq.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_43_2_E2g.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_42_2_ZyR.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_41_4_nO6.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_40_2_oZ9.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_4_llH.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_39_2_r4o.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_38_6_69n.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_37_6_q3U.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_36_2_yw3.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_35_2_ZO3.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_34_2_u7r.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_33_2_2eJ.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_32_4_5kb.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_31_4_n2Z.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_30_6_Xkk.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_3_1ko.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_29_2_Ppn.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_28_2_ijm.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_2_OFb.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_6_meO.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_2_1un.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_2_CV7.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_2_7ui.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_4_NcX.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_4_OqJ.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_2_CUL.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_6_Qo3.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_5_I0T.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_3_IVp.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_2_o3Q.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_2_80i.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_4_2iE.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_3_mYi.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_6_aVW.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_2_hgN.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_3_kOI.root',
       '/store/user/dammann/DYToMuMu_M-10To20_TuneZ2_7TeV-pythia6/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_3_O7O.root' ] );


secFiles.extend( [
               ] )

