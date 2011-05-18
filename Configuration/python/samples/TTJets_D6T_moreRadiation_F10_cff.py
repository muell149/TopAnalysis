import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_dfv.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_2_9Dk.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_Qey.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_2_XnQ.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_PrF.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_5pw.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_1_lMT.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_33_1_fYX.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_32_1_26f.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_31_2_8pS.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_30_4_z0R.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_2_6Op.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_29_1_tvL.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_28_1_SO6.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_27_4_nSY.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_2_GyK.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_4_j12.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_uXq.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_2_nuF.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_2_JFT.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_4_340.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_2_ZrT.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_rlL.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_3_Y7i.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_2sg.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_yvr.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_1_cFW.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_1_t2y.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_1_AsC.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_1_OE3.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_2_2zg.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_dVW.root',
       '/store/user/dammann/TTJets_TuneD6T_largerISRFSR_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_h1f.root' ] );


secFiles.extend( [
               ] )
