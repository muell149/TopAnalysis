import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_9_1_ck4.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_8_1_0ye.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_7_1_6ky.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_6_2_Izk.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_5_1_sQB.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_4_2_Jf7.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_3_2_0JM.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_2_2_iGd.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_24_1_xBV.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_23_1_NH7.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_22_4_IyQ.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_21_2_78z.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_20_1_Sls.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_2_16v.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_19_1_Pxk.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_18_1_SkU.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_17_1_ZyX.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_16_4_yuD.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_15_2_TCb.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_14_2_BcT.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_13_2_aag.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_12_1_hHF.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_11_1_3VA.root',
       '/store/user/dammann/TTJets_TuneD6T_matchingdown_7TeV-madgraph-tauola/Fall10withPU-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_10_1_aI9.root' ] );


secFiles.extend( [
               ] )
