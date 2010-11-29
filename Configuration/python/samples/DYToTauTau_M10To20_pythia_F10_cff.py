####################################################################################################################################
#  
#          dataset name:/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/dammann-Fall10-PAT-v2-43e23e1dee19d970b0c8344e9053309f/USER 
#               DBS URL: https://cmsdbsprod.cern.ch:8443/cms_dbs_ph_analysis_02_writer/servlet/DBSServlet
#            global tag: START38_V13::All
#         mother sample: /DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-START38_V12-v1/AODSIM
#      number of events: 2142450
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
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_O82.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_DbH.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_VLj.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_1_feT.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_imH.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_R0A.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_44_1_XFK.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_43_1_9wq.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_42_1_mCz.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_41_6_dGj.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_40_6_gwn.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_ZuT.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_39_1_wiG.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_38_1_Dm1.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_37_1_Ipm.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_36_7_JRh.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_35_1_jcb.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_34_1_R7X.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_33_6_MCT.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_32_1_TTW.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_31_1_b2H.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_30_7_ypY.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_1_8vI.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_29_1_Te0.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_28_1_kA5.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_1_fSp.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_1_EQA.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_1_r3q.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_kNs.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_1_unm.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_1_XIG.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_6_z1r.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_1_e7a.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_7oB.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_1_ZwQ.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_0SO.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_9To.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_6_JC7.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_6_fHS.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_1_AcJ.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_6_dyf.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_fdJ.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_6_AQi.root',
       '/store/user/dammann/DYToTauTau_M-10To20_TuneZ2_7TeV-pythia6-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_g4E.root' ] );


secFiles.extend( [
               ] )

