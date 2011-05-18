import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_FTp.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_2_BZv.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_91p.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_2_Wsv.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_2_hF9.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_1_wzR.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_2_HLK.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_2_FQm.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_26_1_N5S.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_25_2_wvQ.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_9Tj.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_1_774.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_1_S1O.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_2_i5q.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_2_6Ls.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_wbX.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_1_gzX.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_lPe.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_PCh.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_1_0D1.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_1_8Vk.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_2_WqE.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_2_41c.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_sRM.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_7V3.root',
       '/store/user/dammann/TTJets_TuneD6T_scaleup_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_qZd.root' ] );


secFiles.extend( [
               ] )
